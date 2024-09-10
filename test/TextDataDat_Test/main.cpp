#include <print>
#include <iostream>
#include <Zut/ZxJson.h>
#include <ReVN/RxPJADV/Core/Bin_TextData.h>

namespace RxPJADV { using namespace ZQF::ReVN::RxPJADV; }


auto main(void) -> int
{
	try
	{
		RxPJADV::Script::TextDataDat text_dat{ "textdata.dat" };
		const auto json{ text_dat.SaveViaJson(932) };
		ZxJson::StoreViaFile("textdata.json", json, true, true);

	}
	catch (const std::exception& err)
	{
		std::println(std::cerr, "std::exception: {}", err.what());
	}
}