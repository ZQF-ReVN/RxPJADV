#pragma once
#include <filesystem>


namespace PJADV::Pack
{
	void Extract(std::filesystem::path phPackPath, std::filesystem::path phSaveFolder);
	void Pack(std::filesystem::path phFileFolder, std::filesystem::path phSavePath);
}