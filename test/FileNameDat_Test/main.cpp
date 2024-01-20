#include <iostream>

#include "../../lib/PJADV/Bin.h"


static void DebugMain()
{
	PJADV::Bin::FileNameDat file_name_dat("filename.dat");

	std::cout << file_name_dat[1] << std::endl;
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


