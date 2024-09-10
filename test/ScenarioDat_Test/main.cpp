#include <print>
#include <iostream>
#include <ReVN/RxPJADV/Core/Bin_Scenario.h>

namespace RxPJADV { using namespace ZQF::ReVN::RxPJADV; }


auto main(void) -> int
{
	try
	{
		RxPJADV::Script::ScenarioDat scn_dat{ "scenario.dat" };

	}
	catch (const std::exception& err)
	{
		std::println(std::cerr, "std::exception: {}", err.what());
	}
}