#include <iostream>

#include "../../lib/Rut/RxCmd.h"
#include "../../lib/PJADV/Pack.h"


static void UserMain(int argc, wchar_t* argv[])
{
	try
	{
		Rut::RxCmd::Arg arg;
		arg.AddCmd(L"-dat", L".dat path");
		arg.AddCmd(L"-folder", L"folder path");
		arg.AddCmd(L"-mode", L"mode [extract]:extract files, [pack]:pack files");
		arg.AddExample(L"-mode extract -dat archive.dat -folder archive/ ");
		arg.AddExample(L"-mode pack -folder archive/ -dat archive.dat ");
		if (arg.Load(argc, argv) == false) { return; }

		if (arg.GetValue(L"-mode") == L"extract")
		{
			PJADV::Pack::Extract(arg.GetValue(L"-dat"), arg.GetValue(L"-folder"));
		}
		else if (arg.GetValue(L"-mode") == L"pack")
		{
			PJADV::Pack::Pack(arg.GetValue(L"-folder"), arg.GetValue(L"-dat"));
		}
	}
	catch (const std::runtime_error& err)
	{
		std::cerr << err.what() << std::endl;
	}
}

static void DebugMain()
{
	PJADV::Pack::Extract(u8"archive.dat", u8"archive/");
	//::Pack(u8"bgm/", u8"1.dat");
}


int wmain(int argc, wchar_t* argv[])
{
	::UserMain(argc, argv);
}


