#include <iostream>
#include <ranges>
#include <RxPJADV/Core/TextManager.h>


auto main(void) -> int
{
	try
	{
		ZQF::RxPJADV::Script::TextManager::Export("textdata.dat", "scenario.dat", "scenario_msg.json", "scenario_seq.json", 932);
		//ZQF::RxPJADV::Script::TextManager::Import("textdata.dat", "scenario.dat", "scenario_msg.json", "scenario_seq.json", 932);
	}
	catch (const std::exception& err)
	{
		std::println(std::cerr, "std::exception: {}", err.what());
	}
}