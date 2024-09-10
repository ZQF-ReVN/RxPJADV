#include "Bin_TextData.h"
#include "Types.h"
#include <Zut/ZxMem.h>
#include <Zut/ZxCvt.h>
#include <Zut/ZxFile.h>
#include <ranges>
#include <utility>
#include <cassert>


namespace ZQF::RxPJADV::Script
{
	TextDataDat::TextDataDat()
	{

	}

	TextDataDat::TextDataDat(const std::string_view msTextDataBinPath):
		m_TextDat{ msTextDataBinPath }
	{
		if (std::memcmp(m_TextDat.PtrCur(), "PJADV_TF0001", 12)) { throw std::runtime_error("RxPJADV::Bin::TextDataDat::Load(): unknown file format!"); }
		m_nLastOffset = m_TextDat.SizeBytes();
	}

	auto TextDataDat::Save(const std::string_view msScenarioDatPath) const -> void
	{
		ZxFile ofs{ msScenarioDatPath, ZxFile::OpenMod::WriteForce };

		ofs << std::span{ "PJADV_TF0001", 12 };
		ofs << static_cast<std::uint32_t>(m_vcAppend.size() + m_TextDat.Ptr<Script::TextData_HDR*>()->nTextCount);
		ofs << std::span{ m_TextDat.Ptr() + Script::TextData_HDR::SizeBytes(), m_TextDat.SizeBytes() - Script::TextData_HDR::SizeBytes() };

		for (const auto& text : m_vcAppend)
		{
			ofs << std::span{ text.data(), text.size() };
			ofs << std::span{ "\0\0", 2 };
		}
	}

	auto TextDataDat::SaveViaJson(const std::size_t nCodePage) const -> ZxJson::JValue
	{
		ZxCvt cvt;
		ZxJson::JArray_t texts;

		const auto text_cnt{ m_TextDat.Ptr<Script::TextData_HDR*>()->nTextCount };
		auto text_ptr{ m_TextDat.Ptr<char*>() + Script::TextData_HDR::SizeBytes() };
		for ([[maybe_unused]] const auto idx : std::views::iota(0u, text_cnt))
		{
			const std::string_view text_sv{ text_ptr };
			texts.emplace_back(cvt.MBCSToUTF8(text_sv, nCodePage));
			text_ptr += text_sv.size() + 2;
		}

		for (const auto& msg : m_vcAppend)
		{
			texts.emplace_back(cvt.MBCSToUTF8(msg, nCodePage));
		}

		return ZxJson::JObject_t
		{ 
			{ "info", ZxJson::JObject_t{ { "signature", "PJADV_TF0001" }, { "text_count", m_vcAppend.size() + text_cnt } } },
			{ "texts", std::move(texts) } 
		};
	}

	auto TextDataDat::GetText(const std::size_t nOffset) const -> std::string_view
	{
		if (nOffset > m_TextDat.SizeBytes()) { throw std::runtime_error("RxPJADV::Bin::TextDataDat::GetText(): out of size!"); }
		return m_TextDat.Ptr<char*>() + nOffset;
	}

	auto TextDataDat::AppendText(const std::string_view msText) -> std::size_t
	{
		m_vcAppend.emplace_back(msText);
		return std::exchange(m_nLastOffset, m_nLastOffset + msText.size() + 2);
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