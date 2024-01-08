#include <ranges>
#include <iostream>
#include <filesystem>

#include "../../lib/Rut/RxMem.h"
#include "../../lib/Rut/RxFile.h"
#include "../../lib/PJADV/Bin.h"


static void DebugMain()
{
	Rut::RxMem::Auto text_data_mem{ "textdata.bin" };
	PJADV::Bin::TextDataDat::XorBytes(text_data_mem, 0xC5);
	text_data_mem.SaveData("textdata.bin.dec");
}


int main()
{
	::DebugMain();

	try
	{

	}
	catch (const std::runtime_error& err)
	{
		std::cerr << err.what() << std::endl;
	}
}


