#include <print>
#include <iostream>
#include <Zut/ZxJson.h>
#include <RxPJADV/Core/Bin_TextData.h>


auto main(void) -> int
{
	try
	{
		ZQF::RxPJADV::Script::TextDataDat text_dat{ "textdata.dat" };
		const auto json{ text_dat.SaveViaJson(932) };
		ZxJson::StoreViaFile("textdata.json", json, true, true);

	}
	catch (const std::exception& err)
	{
		std::println(std::cerr, "std::exception: {}", err.what());
	}
}