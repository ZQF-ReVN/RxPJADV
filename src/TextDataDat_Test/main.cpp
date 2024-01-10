#include <iostream>

#include "../../lib/Rut/RxFile.h"
#include "../../lib/PJADV/Bin.h"


static void DebugMain()
{
	PJADV::Bin::TextDataDat textdata_dat("textdata.bin");
	std::string x = "123";
	textdata_dat.AddText(std::move(x));
	textdata_dat.Save("1.bin");
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


