#include "Bin_FileName.h"
#include "Types.h"
#include <ZxCvt/ZxCvt.h>
#include <ZxMem/ZxMem.h>


namespace ZQF::RxPJADV::Bin
{
	FileNameDat::FileNameDat()
	{

	}

	FileNameDat::FileNameDat(const std::string_view msFileNameBinPath, const std::size_t nCodePage)
	{
		this->Load(msFileNameBinPath, nCodePage);
	}

	auto FileNameDat::Load(const std::string_view msFileNameBinPath, const std::size_t nCodePage) -> void
	{
		ZxMem bin_mem{ msFileNameBinPath };

		if (std::memcmp(bin_mem.PtrCur(), "PJADV_FL0001", 12) != 0) { throw std::runtime_error("RxPJADV::Bin::FileNameDat::Load(): unknown file format!"); }
		bin_mem.PosInc(12);

		const auto name_count{ bin_mem.Get<std::uint32_t>() };
		const auto name_table_sp{ bin_mem.SpanCur<Script::File_Name>() };
		if (name_count != name_table_sp.size()) { throw std::runtime_error("RxPJADV::Bin::FileNameDat::Load(): file name count mismatch!"); }

		ZxCvt cvt;
		for (auto& entry : name_table_sp)
		{
			m_vcName.emplace_back(cvt.MBCSToUTF8(entry.aFileName, nCodePage));
		}
	}

	auto FileNameDat::operator[](std::size_t nIndex) -> const std::string&
	{
		return m_vcName.operator[](nIndex);
	}
}