#include <iostream>

#include "../../lib/Rut/RxFile.h"
#include "../../lib/PJADV/Bin.h"


static void DebugMain()
{
	PJADV::Bin::TextDataDat text_data_dat;
	text_data_dat.Load("textdata.bin");

	std::vector<std::wstring> text_list;
	text_data_dat.MakeList(text_list, 932);

	Rut::RxFile::Text ofs_text{ "1.txt",Rut::RIO_WRITE,Rut::RFM_UTF8 };
	ofs_text.WriteAllLine(text_list);

	const char* str_ptr = text_data_dat[0x4C];

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


