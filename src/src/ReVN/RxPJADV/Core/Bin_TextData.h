#pragma once
#include <span>
#include <string>
#include <vector>
#include <unordered_map>
#include <Zut/ZxMem.h>
#include <Zut/ZxJson.h>


namespace ZQF::ReVN::RxPJADV::Script
{
	class TextDataDat
	{
	private:
		ZxMem m_TextDat;
		std::size_t m_nLastOffset{};
		std::vector<std::string> m_vcAppend;

	public:
		TextDataDat();
		TextDataDat(const std::string_view msTextDataBinPath);

	public:
		auto Save(const std::string_view msScenarioDatPath) const -> void;
		auto SaveViaJson(const std::size_t nCodePage) const -> ZxJson::JValue;

	public:
		auto GetText(const std::size_t nOffset) const-> std::string_view;
		auto AppendText(const std::string_view msText) -> std::size_t;

	public:
		static auto XorBytes(const std::span<std::uint8_t> spData, const std::uint8_t ucKey) -> void;
	};
} // namespace ZQF::ReVN::RxPJADV::Script