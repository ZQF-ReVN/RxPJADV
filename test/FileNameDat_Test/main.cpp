#include <print>
#include <iostream>
#include <RxPJADV/Core/Bin_FileName.h>


auto main(void) -> int
{
	try
	{
		ZQF::RxPJADV::Script::FileNameDat file_name_dat{ "filename.dat", 932 };
	}
	catch (const std::exception& err)
	{
		std::println(std::cerr, "std::exception: {}", err.what());
	}
}