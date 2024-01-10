#pragma once
#include <map>
#include <vector>
#include <filesystem>

#include "../../Rut/RxMem.h"


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
		void MapNext();

	public:
		TextDataDat();
		TextDataDat(const std::filesystem::path& phTextDataBin);
		void Load(const std::filesystem::path& phTextDataBin);
		void Save(const std::filesystem::path& phScenarioDat);

	public:
		size_t AddText(std::string&& msText);
		size_t AddText(const std::string& msText);
		size_t AddText(std::wstring_view wsText, size_t nCodePage);
		const std::string& operator[](size_t nOffset);

	public:
		static void XorBytes(Rut::RxMem::Auto& amMem, uint8_t ucKey);
		static void XorBytes(uint8_t* pData, size_t nSize, uint8_t ucKey);
	};

}