#include <iostream>

#include "../../lib/PJADV/Pack.h"


static void DebugMain()
{
	PJADV::Pack::Extract(u8"archive.dat", u8"archive/");
	//::Pack(u8"bgm/", u8"1.dat");
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


