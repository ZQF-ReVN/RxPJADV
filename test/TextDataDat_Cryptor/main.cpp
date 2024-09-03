#include <iostream>
#include <span>

#include <Rut/RxCmd.h>
#include <Rut/RxMem.h>
#include <PJADV/Bin_TextData.h>


static void UserMain(int argc, wchar_t* argv[])
{
	try
	{
		Rut::RxCmd::Arg arg;
		arg.AddCmd(L"-bin", L"textdata file path");
		arg.AddCmd(L"-save", L"textdata save path");
		arg.AddExample(L"-bin textdata.bin -save textdata.bin.dec");
		if (arg.Load(argc, argv) == false) { return; }

		Rut::RxMem::Auto text_data_mem{ arg[L"-bin"].ToWStrView()};
		PJADV::Bin::TextDataDat::XorBytes(text_data_mem, 0xC5);
		text_data_mem.SaveData(arg[L"-save"]);
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
	//::DebugMain();
}


