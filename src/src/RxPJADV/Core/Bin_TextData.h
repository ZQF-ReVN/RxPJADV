#pragma once
#include <span>
#include <string>
#include <vector>
#include <unordered_map>
#include <ZxJson/JValue.h>


namespace ZQF::RxPJADV::Bin
{
	class TextDataDat
	{
	private:
		std::size_t m_nEndIndex{};
		std::size_t m_nEndOffset{};
		std::vector<std::string> m_vcTextData;
		std::unordered_map<std::size_t, std::size_t> m_mpOffsetToIndex;

	private:
		auto MapNext() -> std::size_t;

	public:
		TextDataDat();
		TextDataDat(const std::string_view msTextDataBinPath, const std::size_t nCodePage);

	public:
		auto operator[](const std::size_t nOffset) const -> const std::string&;

	public:
		auto Load(const std::string_view msTextDataBinPath, const std::size_t nCodePage) -> void;
		auto Save(const std::string_view msScenarioDatPath, const std::size_t nCodePage) const -> void;
		auto SaveViaJson() const -> ZxJson::JValue;

	public:
		auto AddText(const std::string_view msText) -> std::uint32_t;

	public:
		static auto XorBytes(const std::span<std::uint8_t> spData, const std::uint8_t ucKey) -> void;
	};

}