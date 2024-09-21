#include <iostream>
#include <ranges>
#include <ReVN/RxPJADV/Core/TextManager.h>

namespace RxPJADV { using namespace ZQF::ReVN::RxPJADV; }


auto main(void) -> int
{
	try
	{
		//RxPJADV::Script::TextManager::Export("textdata.dat", "scenario.dat", "scenario_msg.json", "scenario_seq.json", 932);
		RxPJADV::Script::TextManager::Import("textdata.bin", "scenario.dat", "scenario_msg.json", "scenario_seq.json", 932);
	}
	catch (const std::exception& err)
	{
		std::println(std::cerr, "std::exception: {}", err.what());
	}
}