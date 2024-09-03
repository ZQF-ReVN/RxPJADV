#pragma once
#include <vector>
#include <string_view>
#include <ZxMem/ZxMem.h>


namespace ZQF::RxPJADV::Script
{
	class ScenarioDat
	{
	private:
		ZxMem m_amScenario;
		std::vector<std::uint32_t*> m_vcCodePtr;

	public:
		ScenarioDat();
		ScenarioDat(const std::string_view msScenarioDatPath);

	public:
		auto Load(const std::string_view msScenarioDatPath) -> void;
		auto Save(const std::string_view msScenarioDatPath) -> void;

	public:
		auto ShowCommand(std::uint32_t uiOpcode) -> void;

	public:
		auto GetPtrs() -> const std::vector<std::uint32_t*>&;
	};
}