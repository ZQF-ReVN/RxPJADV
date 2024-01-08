#include <iostream>

#include "../../lib/Rut/RxFile.h"
#include "../../lib/PJADV/Bin.h"


static void DebugMain()
{
	uint32_t uix = 0x6e64;
	auto e = (((uix + 7) >> 3) + 3) & 0xFFFFFFFC;
	PJADV::Bin::ScenarioDat scn_dat;
	scn_dat.Load("scenario.dat");
	scn_dat.ShowCommand(0x80000307);

	int a = 0;
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


