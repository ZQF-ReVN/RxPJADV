#include "Bin_Scenario.h"
#include "PJADV_Struct.h"
#include <Zut/ZxFile.h>
#include <ranges>
#include <format>


namespace ZQF::ReVN::RxPJADV::Script
{
	ScenarioDat::ScenarioDat()
	{

	}

	ScenarioDat::ScenarioDat(const std::string_view msScenarioDatPath)
	{
		this->Load(msScenarioDatPath);
	}

	auto ScenarioDat::Load(const std::string_view msScenarioDatPath) -> void
	{
		m_amScenario.Load(msScenarioDatPath);

		if (std::memcmp(m_amScenario.Ptr(), "PJADV_SF0001", 12) != 0) { throw std::runtime_error("RxPJADV::Bin::ScenarioDat::Load(): unknown file format!"); }
		m_amScenario.PosInc(12);

		[[maybe_unused]] auto flag{ m_amScenario.Get<std::uint32_t>() };

		m_amScenario.PosInc(16); // skip unknown data

		auto cmd_ptr{ m_amScenario.PtrCur() };
		auto max_ptr{ m_amScenario.PtrCur() + m_amScenario.SizeBytesCur() };
		while (cmd_ptr != max_ptr)
		{
			if (cmd_ptr > max_ptr) { throw std::runtime_error("RxPJADV::Bin::ScenarioDat::Load(): scan cmd error!"); }

			const auto cur_cmd_ptr = reinterpret_cast<Struct::Script::OPCode*>(cmd_ptr);
			cmd_ptr += (cur_cmd_ptr->ucCount == 0) ? (4) : (cur_cmd_ptr->ucCount * 4);
			m_vcCodePtr.push_back(reinterpret_cast<std::uint32_t*>(cur_cmd_ptr));
		}

	}

	auto ScenarioDat::Save(const std::string_view msScenarioDatPath) -> void
	{
		m_amScenario.Save(msScenarioDatPath);
	}

	auto ScenarioDat::ShowCommand(std::uint32_t /*uiOpcode*/) -> void
	{
		std::string text;
		for (auto cmd_ptr : m_vcCodePtr)
		{
			if (cmd_ptr[0] == 0x80000307)
			{
				text.append(std::format("{:#010x}, {:#010x}, {:#010x}, {:#010x}, {:#010x}, {:#010x}, {:#010x}\n", cmd_ptr[0], cmd_ptr[1], cmd_ptr[2], cmd_ptr[3], cmd_ptr[4], cmd_ptr[5], cmd_ptr[6]));
			}
			//else if (command_ptr[0] == 0x01010804)
			//{
			//	swprintf(buffer, 100, L"0x%08x, 0x%08x, 0x%08x, 0x%08x\n", command_ptr[0], command_ptr[1], command_ptr[2], command_ptr[3]);
			//	text.append(buffer);
			//}
		}

		ZxFile{ "command.txt",ZxFile::OpenMod::WriteForce }.Write(std::span{ text });
	}

	auto ScenarioDat::GetPtrs() -> const std::vector<std::uint32_t*>&
	{
		return m_vcCodePtr;
	}
} // namespace ZQF::ReVN::RxPJADV::Script