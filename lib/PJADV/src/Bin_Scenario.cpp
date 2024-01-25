#include "Bin_Scenario.h"
#include "PJADV_Types.h"

#include "lib/Rut/RxFile.h"

#include <ranges>
#include <iostream>


namespace PJADV::Bin
{
	ScenarioDat::ScenarioDat()
	{

	}

	ScenarioDat::ScenarioDat(const std::filesystem::path& phScenarioDat)
	{
		this->Load(phScenarioDat);
	}

	void ScenarioDat::Load(const std::filesystem::path& phScenarioDat)
	{
		m_amScenario.LoadFile(phScenarioDat);
		if (memcmp(m_amScenario.GetPtr(), "PJADV_SF0001", 12)) { throw std::runtime_error("ScenarioDat::Load: Unknow File Format!"); }
		uint32_t command_count = *(uint32_t*)(m_amScenario.GetPtr() + 12);

		uint8_t* max_ptr = m_amScenario.GetPtr() + m_amScenario.GetSize() - 28;
		uint8_t* command_seg_ptr = (m_amScenario.GetPtr() + 32);

		while (command_seg_ptr <= max_ptr)
		{
			PAJ_OPCode* opcode_ptr = (PAJ_OPCode*)command_seg_ptr;
			command_seg_ptr += opcode_ptr->ucCount * 4;
			m_vcCodePtr.emplace_back((uint32_t*)opcode_ptr);
		}
	}

	void ScenarioDat::Save(const std::filesystem::path& phScenarioDat)
	{
		m_amScenario.SaveData(phScenarioDat);
	}

	void ScenarioDat::ShowCommand(uint32_t uiOpcode)
	{
		std::wstring text;
		wchar_t buffer[100];
		for (auto command_ptr : m_vcCodePtr)
		{
			if (command_ptr[0] == 0x80000307)
			{
				swprintf(buffer, 100, L"0x%08x, 0x%08x, 0x%08x, 0x%08x, 0x%08x, 0x%08x, 0x%08x\n", command_ptr[0], command_ptr[1], command_ptr[2], command_ptr[3], command_ptr[4], command_ptr[5], command_ptr[6]);
				text.append(buffer);
			}
			//else if (command_ptr[0] == 0x01010804)
			//{
			//	swprintf(buffer, 100, L"0x%08x, 0x%08x, 0x%08x, 0x%08x\n", command_ptr[0], command_ptr[1], command_ptr[2], command_ptr[3]);
			//	text.append(buffer);
			//}
		}

		Rut::RxFile::Text ofs{ L"command.txt", Rut::RIO_WRITE, Rut::RFM_UTF8 };
		ofs.WriteLine(text);
	}

	const std::vector<uint32_t*>& ScenarioDat::GetPtrs()
	{
		return m_vcCodePtr;
	}
}