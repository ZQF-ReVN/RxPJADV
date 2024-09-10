#include "Pack_V2.h"
#include "Types.h"
#include <Zut/ZxMem.h>
#include <Zut/ZxFile.h>
#include <Zut/ZxFS.h>
#include <vector>
#include <ranges>


namespace ZQF::RxPJADV::PackV2
{
	auto Export(const std::string_view msPackPath, const std::string_view msSaveDir) -> void
	{
		ZxFile ifs{ msPackPath, ZxFile::OpenMod::ReadSafe };

		const auto hdr_info{ ifs.Get<PackV2::HDR_Info>() };

		const auto file_name_table_bytes{ hdr_info.nFileCount * RxPJADV::PackV2::File_Name::SizeBytes() };
		const auto file_info_table_bytes{ hdr_info.nFileCount * RxPJADV::PackV2::File_Info::SizeBytes() };

		ZxMem file_name_table_mem{ file_name_table_bytes };
		ifs >> file_name_table_mem.Span();

		ZxMem file_info_table_mem{ file_info_table_bytes };
		ifs >> file_info_table_mem.Span();

		const auto hdr_bytes{ RxPJADV::PackV2::HDR_Info::SizeBytes() + file_name_table_bytes + file_info_table_bytes };

		ZxMem cache;
		for (auto&& [name, info] : std::views::zip(file_name_table_mem.Span<const PackV2::File_Name>(), file_info_table_mem.Span<const PackV2::File_Info>()))
		{
			cache.Resize(static_cast<std::size_t>(info.nBytes));
			ifs.Seek(hdr_bytes + static_cast<std::size_t>(info.nOffset), ZxFile::MoveWay::Set);
			ifs.Read(cache.Span());
			cache.Save(std::string{ msSaveDir }.append(name.aFileName));
		}
	}

	auto Import(const std::string_view msFileDir, const std::string_view msSavePath) -> void
	{
		std::vector<PackV2::File_Name> file_name_vec;
		std::vector<PackV2::File_Info> file_info_vec;

		std::uint32_t offset{};
		for (ZxFS::Walker walker{ msFileDir }; walker.NextFile();)
		{
			const auto file_name{ walker.GetName() };
			if (file_name.size() > sizeof(PackV2::File_Name::aFileName)) { throw std::runtime_error("RxPJADV::Pack::Import(): file name too long"); }
			file_name_vec.emplace_back(PackV2::File_Name{});
			std::memcpy(file_name_vec.back().aFileName, file_name.data(), file_name.size());
			file_name_vec.back().aFileName[file_name.size()] = {};

			const auto file_path{ walker.GetPath() };
			const auto file_bytes_opt{ ZxFS::FileSize(file_path) };
			if (file_bytes_opt.has_value() == false) { throw std::runtime_error(std::string{ "RxPJADV::Pack::Import(): get file size error -> " }.append(file_path)); }
			const auto file_bytes{ static_cast<std::uint32_t>(*file_bytes_opt) };
			file_info_vec.emplace_back(PackV2::File_Info{ .nOffset = offset, .nBytes = file_bytes });
			offset += file_bytes;
		}

		ZxFile ofs{ msSavePath, ZxFile::OpenMod::WriteForce };

		ZxMem cache;
		{
			const auto hdr_bytes{ HDR_Info::SizeBytes() + file_name_vec.size() * PackV2::File_Name::SizeBytes() + file_info_vec.size() * PackV2::File_Info::SizeBytes() };
			auto& hdr_mem = cache.Resize(hdr_bytes);

			hdr_mem << PackV2::HDR_Info::Make(file_name_vec.size());
			for (const auto& name : file_name_vec) { hdr_mem << name; }
			for (const auto& info : file_info_vec) { hdr_mem << info; }

			ofs << hdr_mem.Span();
		}

		std::string file_path{ msFileDir };
		for (const auto& name : file_name_vec)
		{
			cache.Load(file_path.append(name.aFileName));
			ofs.Write(cache.Span());
			file_path.resize(msFileDir.size());
		}
	}
}