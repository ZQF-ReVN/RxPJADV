#pragma once
#include <string_view>


namespace ZQF::ReVN::RxPJADV::PackV2
{
	auto Export(const std::string_view msPackPath, const std::string_view msSaveDir) -> void;
	auto Import(const std::string_view msFileFolder, const std::string_view msSavePath) -> void;
} // namespace ZQF::ReVN::RxPJADV::PackV2