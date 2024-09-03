#include "Bin_TextData.h"
#include <ZxFile/ZxFile.h>
#include <ZxMem/ZxMem.h>
#include <ZxCvt/ZxCvt.h>
#include <ranges>
#include <cassert>


namespace ZQF::RxPJADV::Bin
{
	TextDataDat::TextDataDat()
	{

	}

	TextDataDat::TextDataDat(const std::string_view msTextDataBinPath, const std::size_t nCodePage)
	{
		this->Load(msTextDataBinPath, nCodePage);
	}

	auto TextDataDat::Load(const std::string_view msTextDataBinPath, const std::size_t nCodePage) -> void
	{
		if (m_vcTextData.size()) { m_vcTextData.clear(); }

		ZxMem textdata_mem{ msTextDataBinPath };
		if (textdata_mem.SizeBytes() < 12) { throw std::runtime_error("RxPJADV::Bin::TextDataDat::Load(): unknown file format!"); }
		
		// check signature
		if (std::memcmp(textdata_mem.PtrCur(), "PJADV_TF0001", 12)) { throw std::runtime_error("RxPJADV::Bin::TextDataDat::Load(): unknown file format!"); }
		textdata_mem.PosInc(12);

		// get text count
		const auto text_count{ static_cast<std::size_t>(textdata_mem.Get<std::uint32_t>()) };

		const auto text_table_ptr{ textdata_mem.PtrCur<char*>() };

		// read all text
		ZxCvt cvt;
		std::size_t textdata_offset{};
		for (auto idx : std::views::iota(0u, text_count))
		{
			m_mpOffsetToIndex[textdata_offset] = idx;
			const std::string_view text{ text_table_ptr + textdata_offset };
			textdata_offset += text.size() + 2;
			m_vcTextData.emplace_back(cvt.MBCSToUTF8(text, nCodePage));
		}

		m_nEndIndex = text_count;
		m_nEndOffset = textdata_offset;
	}

	auto TextDataDat::Save(const std::string_view msScenarioDatPath, const std::size_t nCodePage) const -> void
	{
		ZxFile ofs{ msScenarioDatPath, ZxFile::OpenMod::WriteForce };
		
		ofs << std::span{ "PJADV_TF0001", 12 };
		ofs << static_cast<std::uint32_t>(m_vcTextData.size());

		ZxCvt cvt;
		for (const auto& text : m_vcTextData)
		{
			const auto text_enc{ cvt.UTF8ToMBCS(text, nCodePage) };
			ofs << std::span{ text_enc.data(), text_enc.size() };
			ofs << std::span{ "\0\0", 2 };
		}
	}

	auto RxPJADV::Bin::TextDataDat::SaveViaJson() const -> ZxJson::JValue
	{
		ZxJson::JObject_t info
		{
			{ "signature", "PJADV_TF0001" },
			{ "text_count", m_vcTextData.size() }
		};

		ZxJson::JArray_t texts;
		for (const auto& msg : m_vcTextData)
		{
			texts.emplace_back(msg);
		}

		return ZxJson::JObject_t{ { "info", std::move(info) },{"texts", std::move(texts) }};
	}

	auto TextDataDat::MapNext() -> std::size_t
	{
		std::size_t old_offset = m_nEndOffset;
		std::size_t last_text_len = m_vcTextData[m_nEndIndex].size();
		m_nEndIndex = m_nEndIndex + 1;
		m_nEndOffset = m_nEndOffset + last_text_len + 2;
		m_mpOffsetToIndex[m_nEndOffset] = m_nEndIndex;
		return old_offset;
	}

	auto TextDataDat::AddText(const std::string_view msText) -> std::uint32_t
	{
		m_vcTextData.emplace_back(msText);
		return static_cast<std::uint32_t>(this->MapNext());
	}

	auto TextDataDat::operator[](const std::size_t nOffset) const -> const std::string&
	{
		const auto index = m_mpOffsetToIndex.at(nOffset);
		return m_vcTextData[index];
	}

	auto TextDataDat::XorBytes(const std::span<std::uint8_t> spData, const std::uint8_t ucKey) -> void
	{
		auto key{ ucKey };
		for (auto& byte : spData)
		{
			byte ^= key;
			key += 0x5C;
		}
	}
}