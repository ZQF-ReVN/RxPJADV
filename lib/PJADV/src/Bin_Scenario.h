#pragma once
#include <vector>
#include <filesystem>

#include "lib/Rut/RxMem.h"


namespace PJADV::Bin
{
	class ScenarioDat
	{
	private:
		Rut::RxMem::Auto m_amScenario;
		std::vector<uint32_t*> m_vcCodePtr;

	public:
		ScenarioDat();
		ScenarioDat(const std::filesystem::path& phScenarioDat);
		void Load(const std::filesystem::path& phScenarioDat);
		void Save(const std::filesystem::path& phScenarioDat);
		void ShowCommand(uint32_t uiOpcode);

	public:
		const std::vector<uint32_t*>& GetPtrs();
	};
}