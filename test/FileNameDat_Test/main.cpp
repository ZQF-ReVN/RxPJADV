#include <print>
#include <iostream>
#include <ReVN/RxPJADV/Core/Bin_FileName.h>

namespace RxPJADV { using namespace ZQF::ReVN::RxPJADV; }


auto main(void) -> int
{
	try
	{
		RxPJADV::Script::FileNameDat file_name_dat{ "filename.dat", 932 };
	}
	catch (const std::exception& err)
	{
		std::println(std::cerr, "std::exception: {}", err.what());
	}
}