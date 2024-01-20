#include <iostream>

#include "../../lib/Rut/RxCmd.h"
#include "../../lib/Rut/RxMem.h"
#include "../../lib/PJADV/Bin.h"


static void UserMain(int argc, wchar_t* argv[])
{
	try
	{
		Rut::RxCmd::Parser cmd;
		cmd.AddCmd(L"-bin", L"textdata file path");
		cmd.AddCmd(L"-out", L"textdata save path");
		cmd.AddExample(L"-bin textdata.bin -out textdata.bin.dec");
		if (cmd.Load(argc, argv) == false) { return; }

		Rut::RxMem::Auto text_data_mem{ cmd.GetValue(L"-bin") };
		PJADV::Bin::TextDataDat::XorBytes(text_data_mem, 0xC5);
		text_data_mem.SaveData(cmd.GetValue(L"-out"));
	}
	catch (const std::runtime_error& err)
	{
		std::cerr << err.what() << std::endl;
	}
}

static void DebugMain()
{
	Rut::RxMem::Auto text_data_mem{ "textdata.bin" };
	PJADV::Bin::TextDataDat::XorBytes(text_data_mem, 0xC5);
	text_data_mem.SaveData("textdata.bin.dec");
}


int wmain(int argc, wchar_t* argv[])
{
	::UserMain(argc, argv);
}


