#include <iostream>

#include "../../lib/Rut/RxFile.h"
#include "../../lib/PJADV/Bin.h"


int main()
{
	PJADV::Bin::TextDataDat textdata_dat("textdata.bin");
	std::string x = "123";
	textdata_dat.AddText(std::move(x));
	textdata_dat.Save("1.bin");
}


