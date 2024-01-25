#include "Bin_TextData.h"
#include "lib/Rut/RxStr.h"
#include "lib/Rut/RxFile.h"

#include <ranges>
#include <cassert>


namespace PJADV::Bin
{
	TextDataDat::TextDataDat()
	{

	}

	TextDataDat::TextDataDat(const std::filesystem::path& phTextDataBin)
	{
		this->Load(phTextDataBin);
	}

	void TextDataDat::Load(const std::filesystem::path& phTextDataBin)
	{
		if (m_vcTextData.size()) { m_vcTextData.clear(); }

		Rut::RxMem::Auto textdata_mem(phTextDataBin);
		if (textdata_mem.GetSize() < 12) { throw std::runtime_error("TextDataDat::Load: Unknow File Format!"); }

		size_t textdata_offset = 0;
		const uint8_t* const textdata_ptr = textdata_mem.GetPtr();
		
		// check signature
		if (memcmp(textdata_ptr, "PJADV_TF0001", 12)) { throw std::runtime_error("TextDataDat::Load: Unknow File Format!"); }
		textdata_offset += 12;

		// get text count
		size_t text_count = (size_t)(*(uint32_t*)(textdata_ptr + textdata_offset));
		textdata_offset += 4;

		// read all text
		for (auto ite_text : std::views::iota(0u, text_count))
		{
			m_mpOffsetToIndex[textdata_offset] = ite_text;
			std::string_view text{ (char*)(textdata_ptr + textdata_offset) };
			textdata_offset += text.size() + 2;
			m_vcTextData.emplace_back(text);
		}

		m_nEndIndex = text_count;
		m_nEndOffset = textdata_offset;
	}

	void TextDataDat::Save(const std::filesystem::path& phScenarioDat)
	{
		Rut::RxFile::Binary ofs{ phScenarioDat, Rut::RIO_WRITE };
		
		ofs.Write("PJADV_TF0001", 12);
		uint32_t text_count = (uint32_t)m_vcTextData.size();
		ofs.Write(&text_count, sizeof(uint32_t));

		for (auto& text : m_vcTextData)
		{
			ofs.Write(text.data(), text.size());
			ofs.Write("\0\0", 2);
		}
	}

	size_t TextDataDat::MapNext()
	{
		size_t old_offset = m_nEndOffset;
		size_t last_text_len = m_vcTextData[m_nEndIndex].size();
		m_nEndIndex = m_nEndIndex + 1;
		m_nEndOffset = m_nEndOffset + last_text_len + 2;
		m_mpOffsetToIndex[m_nEndOffset] = m_nEndIndex;
		return old_offset;
	}

	uint32_t TextDataDat::AddText(std::string&& msText)
	{
		m_vcTextData.emplace_back(std::move(msText));
		return (uint32_t)this->MapNext();
	}

	uint32_t TextDataDat::AddText(const std::string& msText)
	{
		m_vcTextData.emplace_back(msText);
		return (uint32_t)this->MapNext();
	}

	uint32_t TextDataDat::AddText(std::wstring_view wsText, size_t nCodePage)
	{
		return this->AddText(Rut::RxStr::ToMBCS(wsText, nCodePage));
	}

	const std::string& TextDataDat::operator[](size_t nOffset)
	{
		const size_t index = m_mpOffsetToIndex.operator[](nOffset);
		return m_vcTextData.operator[](index);
	}

	void TextDataDat::XorBytes(std::span<uint8_t> spData, uint8_t ucKey)
	{
		for (auto& ite_byte : spData)
		{
			ite_byte ^= ucKey;
			ucKey += 0x5C;
		}
	}
}