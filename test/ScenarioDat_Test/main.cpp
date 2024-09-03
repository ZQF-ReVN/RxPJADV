#include <print>
#include <iostream>
#include <RxPJADV/Core/Bin_Scenario.h>


auto main(void) -> int
{
	try
	{
		ZQF::RxPJADV::Script::ScenarioDat scn_dat{ "scenario.dat" };

	}
	catch (const std::exception& err)
	{
		std::println(std::cerr, "std::exception: {}", err.what());
	}
}