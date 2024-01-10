#include "Bin_FileName.h"
#include "../../Rut/RxMem.h"
#include "../../Rut/RxFile.h"

#include <array>
#include <ranges>


namespace PJADV::Bin
{
	FileNameDat::FileNameDat()
	{

	}

	FileNameDat::FileNameDat(const std::filesystem::path& phFileNameBin)
	{
		this->Load(phFileNameBin);
	}

	void FileNameDat::Load(const std::filesystem::path& phFileNameBin)
	{
		Rut::RxFile::Binary ifs{ phFileNameBin, Rut::RIO_READ };

		std::array<uint8_t, 12> signature = ifs.ReadViaType<std::array<uint8_t, 12>>();
		if (memcmp(signature.data(), "PJADV_FL0001", 12)) { throw std::runtime_error("FileNameDat::Load: Unknow File Format!"); }

		uint32_t entry_count = ifs.ReadViaType<uint32_t>();

		std::array<char, 32> file_name_buffer;
		for (auto ite_entry : std::views::iota(0u, entry_count))
		{
			file_name_buffer = ifs.ReadViaType<std::array<char, 32>>();
			m_vcName.emplace_back(file_name_buffer.data());
		}
	}

	const std::string& FileNameDat::operator[](size_t nIndex)
	{
		return m_vcName.operator[](nIndex);
	}
}