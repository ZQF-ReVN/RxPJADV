#include "Pack_V2.h"
#include "PJADV_Types.h"
#include "../../Rut/RxMem.h"
#include "../../Rut/RxFile.h"

#include <ranges>


namespace PJADV::Pack
{
	void Extract(std::filesystem::path phPackPath, std::filesystem::path phSaveFolder)
	{
		Rut::RxFile::Binary ifs{ phPackPath, Rut::RIO_READ };

		PAJ_Pack_HDR_Info hdr_info = ifs.ReadViaType<PAJ_Pack_HDR_Info>();
		std::vector<PAJ_Pack_File_Name> file_name_list;
		std::vector<PAJ_Pack_File_Info> file_info_list;

		for (auto ite : std::views::iota(0u, hdr_info.uiFileCount))
		{
			file_name_list.emplace_back(ifs.ReadViaType<PAJ_Pack_File_Name>());
		}

		for (auto ite : std::views::iota(0u, hdr_info.uiFileCount))
		{
			file_info_list.emplace_back(ifs.ReadViaType<PAJ_Pack_File_Info>());
		}

		Rut::RxMem::Auto buffer;
		for (auto [name, info] : std::views::zip(file_name_list, file_info_list))
		{
			buffer.ReadData(ifs, info.uiSize);
			buffer.SaveData(phSaveFolder / name.aFileName);
		}
	}

	void Pack(std::filesystem::path phFileFolder, std::filesystem::path phSavePath)
	{
		PAJ_Pack_HDR_Info hdr_info{ 0 };
		std::vector<PAJ_Pack_File_Name> file_name_list;
		std::vector<PAJ_Pack_File_Info> file_info_list;

		uint32_t offset = 0;
		for (auto& entry : std::filesystem::directory_iterator(phFileFolder))
		{
			if (entry.is_regular_file() == false) { continue; }
			const std::filesystem::path& file_path = entry.path();

			std::string file_name = file_path.filename().string();
			if (file_name.size() > sizeof(PAJ_Pack_File_Name)) { throw std::runtime_error("File Name Too Long"); }

			PAJ_Pack_File_Name paj_file_name{ 0 };
			memcpy(paj_file_name.aFileName, file_name.data(), file_name.size() + 1);
			file_name_list.push_back(paj_file_name);

			uint32_t file_size = (uint32_t)std::filesystem::file_size(file_path);
			PAJ_Pack_File_Info paj_file_info{ offset, file_size };
			file_info_list.push_back(paj_file_info);
			offset += file_size;
		}

		memcpy(hdr_info.aSignature, "GAMEDAT PAC2", sizeof(hdr_info.aSignature));
		hdr_info.uiFileCount = (uint32_t)file_name_list.size();

		Rut::RxFile::Binary ofs{ phSavePath, Rut::RIO_WRITE };

		ofs << hdr_info;

		for (auto& name : file_name_list)
		{
			ofs << name;
		}

		for (auto& info : file_info_list)
		{
			ofs << info;
		}

		Rut::RxMem::Auto buffer;
		for (auto& name : file_name_list)
		{
			buffer.LoadFile(phFileFolder.parent_path() / name.aFileName);
			buffer.WriteData(ofs);
		}
	}
}