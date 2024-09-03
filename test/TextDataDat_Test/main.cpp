#include <print>
#include <iostream>
#include <ZxJson/JIO.h>
#include <RxPJADV/Core/Bin_TextData.h>


auto main(void) -> int
{
	try
	{
		ZQF::RxPJADV::Bin::TextDataDat text_dat{ "textdata.dat", 932 };
		const auto json{ text_dat.SaveViaJson() };
		ZQF::ZxJson::StoreViaFile("textdata.json", json, true, true);

	}
	catch (const std::exception& err)
	{
		std::println(std::cerr, "std::exception: {}", err.what());
	}
}