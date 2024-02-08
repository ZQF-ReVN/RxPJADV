#pragma once
#include <vector>
#include <string>
#include <filesystem>


namespace PJADV::Bin
{
	class FileNameDat
	{
	private:
		std::vector<std::string> m_vcName;

	public:
		FileNameDat();
		FileNameDat(const std::filesystem::path& phFileNameBin);
		void Load(const std::filesystem::path& phFileNameBin);

	public:
		const std::string& operator[](size_t nIndex);
	};
}