#pragma once
#include <filesystem>


namespace PJADV::Pack
{
	void Extract(const std::filesystem::path& phPackPath, const std::filesystem::path& phSaveFolder);
	void Pack(const std::filesystem::path& phFileFolder, const std::filesystem::path& phSavePath);
}