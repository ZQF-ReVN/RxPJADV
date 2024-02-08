#include <iostream>

#include <Rut/RxFile.h>
#include <PJADV/Bin_Scenario.h>


int main()
{
	uint32_t uix = 0x6e64;
	auto e = (((uix + 7) >> 3) + 3) & 0xFFFFFFFC;
	PJADV::Bin::ScenarioDat scn_dat;
	scn_dat.Load("scenario.dat");
	scn_dat.ShowCommand(0x80000307);

	int a = 0;
}


