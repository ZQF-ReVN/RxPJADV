#include <print>
#include <iostream>
#include <ReVN/RxPJADV/Core/Pack_V2.h>

namespace RxPJADV { using namespace ZQF::ReVN::RxPJADV; }


auto main(void) -> int
{
	try
	{
		// RxPJADV::PackV2::Export("archive.dat", "archive/");
		RxPJADV::PackV2::Import("archive/", "archive.dat.new");
	}
	catch (const std::exception& err)
	{
		std::println(std::cerr, "std::exception: {}", err.what());
	}
}