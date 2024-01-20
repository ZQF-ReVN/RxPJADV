#include <iostream>

#include "../../lib/Rut/RxCmd.h"
#include "../../lib/PJADV/Pack.h"


static void UserMain(int argc, wchar_t* argv[])
{
	try
	{
		Rut::RxCmd::Parser cmd;
		cmd.AddCmd(L"-dat", L".dat path");
		cmd.AddCmd(L"-folder", L"folder path");
		cmd.AddCmd(L"-mode", L"mode [extract]:extract files, [pack]:pack files");
		cmd.AddExample(L"-mode extract -dat archive.dat -folder archive/ ");
		cmd.AddExample(L"-mode pack -folder archive/ -dat archive.dat ");
		if (cmd.Load(argc, argv) == false) { return; }

		if (cmd.GetValue(L"-mode") == L"extract")
		{
			PJADV::Pack::Extract(cmd.GetValue(L"-dat"), cmd.GetValue(L"-folder"));
		}
		else if (cmd.GetValue(L"-mode") == L"pack")
		{
			PJADV::Pack::Pack(cmd.GetValue(L"-folder"), cmd.GetValue(L"-dat"));
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


