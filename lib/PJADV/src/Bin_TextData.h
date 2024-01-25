#pragma once
#include <map>
#include <span>
#include <vector>
#include <filesystem>

#include "lib/Rut/RxMem.h"


namespace PJADV::Bin
{
	class TextDataDat
	{
	private:
		size_t m_nEndIndex = 0;
		size_t m_nEndOffset = 0;
		std::vector<std::string> m_vcTextData;
		std::map<size_t, size_t> m_mpOffsetToIndex;

	private:
		size_t MapNext();

	public:
		TextDataDat();
		TextDataDat(const std::filesystem::path& phTextDataBin);
		void Load(const std::filesystem::path& phTextDataBin);
		void Save(const std::filesystem::path& phScenarioDat);

	public:
		uint32_t AddText(std::string&& msText);
		uint32_t AddText(const std::string& msText);
		uint32_t AddText(std::wstring_view wsText, size_t nCodePage);
		const std::string& operator[](size_t nOffset);

	public:
		static void XorBytes(std::span<uint8_t> spData, uint8_t ucKey);
	};

}