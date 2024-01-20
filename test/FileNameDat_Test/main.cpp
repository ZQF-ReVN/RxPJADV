#include <iostream>

#include "../../lib/PJADV/Bin.h"


int main()
{
	PJADV::Bin::FileNameDat file_name_dat("filename.dat");

	std::cout << file_name_dat[1] << std::endl;
}


