#include <print>
#include <iostream>
#include <RxPJADV/Core/Pack_V2.h>


auto main(void) -> int
{
	try
	{
		// ZQF::RxPJADV::PackV2::Export("archive.dat", "archive/");
		ZQF::RxPJADV::PackV2::Import("archive/", "archive.dat.new");
	}
	catch (const std::exception& err)
	{
		std::println(std::cerr, "std::exception: {}", err.what());
	}
}