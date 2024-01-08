#pragma once
#include <vector>
#include <ranges>
#include <filesystem>

#include "../../Rut/RxMem.h"
#include "../../Rut/RxStr.h"


namespace PJADV::Bin
{
	class TextDataDat
	{
	private:
		Rut::RxMem::Auto m_amTextData;

	public:
		TextDataDat();
		TextDataDat(const std::filesystem::path& phTextDataBin);
		void Load(const std::filesystem::path& phTextDataBin);

	public:
		void MakeList(std::vector<std::string>& vcTexts);
		void MakeList(std::vector<std::wstring>& vcTexts, size_t uCodePage);
		const char* operator[](size_t nIndex);

	public:
		static void XorBytes(Rut::RxMem::Auto& amMem, uint8_t ucKey);
		static void XorBytes(uint8_t* pData, size_t nSize, uint8_t ucKey);
	};

	TextDataDat::TextDataDat()
	{

	}

	TextDataDat::TextDataDat(const std::filesystem::path& phTextDataBin)
	{
		this->Load(phTextDataBin);
	}

	void TextDataDat::Load(const std::filesystem::path& phTextDataBin)
	{
		m_amTextData.LoadFile(phTextDataBin);
		if (memcmp(m_amTextData.GetPtr(), "PJADV_TF0001", 12)) { throw std::runtime_error("TextDataDat::Load: Unknow File Format!"); }


	}

	void TextDataDat::MakeList(std::vector<std::string>& vcTexts)
	{
		if (vcTexts.size()) { vcTexts.clear(); }

		uint8_t* cur_ptr = m_amTextData.GetPtr() + 12;

		uint32_t text_count = *(uint32_t*)(cur_ptr);
		cur_ptr += 4;

		for (auto ite_text : std::views::iota(0u, text_count))
		{
			std::string text{ (char*)cur_ptr };
			cur_ptr += text.size() + 2;
			vcTexts.emplace_back(std::move(text));
		}
	}

	void TextDataDat::MakeList(std::vector<std::wstring>& vcTexts, size_t uCodePage)
	{
		if (vcTexts.size()) { vcTexts.clear(); }

		uint8_t* cur_ptr = m_amTextData.GetPtr() + 12;

		uint32_t text_count = *(uint32_t*)(cur_ptr);
		cur_ptr += 4;

		for (auto ite_text : std::views::iota(0u, text_count))
		{
			std::string text{ (char*)cur_ptr };
			cur_ptr += text.size() + 2;
			vcTexts.emplace_back(Rut::RxStr::ToWCS(text, uCodePage));
		}
	}

	const char* TextDataDat::operator[](size_t nIndex)
	{
		return m_amTextData.GetPtr<char*>() + nIndex;
	}

	void TextDataDat::XorBytes(Rut::RxMem::Auto& amMem, uint8_t ucKey)
	{
		TextDataDat::XorBytes(amMem.GetPtr(), amMem.GetSize(), 0xC5);
	}

	void TextDataDat::XorBytes(uint8_t* pData, size_t nSize, uint8_t ucKey)
	{
		for (auto ite_byte : std::views::iota(0u, nSize))
		{
			pData[ite_byte] ^= ucKey;
			ucKey += 0x5C;
		}
	}
}