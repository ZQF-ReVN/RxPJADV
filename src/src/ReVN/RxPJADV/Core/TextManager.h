#pragma once
#include <string_view>


namespace ZQF::ReVN::RxPJADV::Script
{
	class TextManager
	{
	public:
		static auto Export(const std::string_view msTextDataBinPath, const std::string_view msScenarioDataBinPath, const std::string_view msMsgJsonPath, const std::string_view msSeqJsonPath, const std::size_t nCodePage) -> void;
		static auto Import(const std::string_view msTextDataBinPath, const std::string_view msScenarioDataBinPath, const std::string_view msMsgJsonPath, const std::string_view msSeqJsonPath, const std::size_t nCodePage) -> void;
	};
} // namespace ZQF::ReVN::RxPJADV::Script