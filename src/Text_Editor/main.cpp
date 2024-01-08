#include <iostream>

#include "../../lib/Rut/RxJson.h"
#include "../../lib/Rut/RxStr.h"
#include "../../lib/PJADV/Bin.h"


static void DebugMain()
{
	PJADV::Bin::TextDataDat text_dat("textdata.bin");
	PJADV::Bin::ScenarioDat scen_dat("scenario.dat");

	Rut::RxJson::JArray json_msg_array;
	for (auto code_ptr : scen_dat.GetPtrs())
	{
		switch (code_ptr[0])
		{
		case 0x80000307:  // [text_box_text]
		{
			uint32_t name_text_offset = code_ptr[2];
			uint32_t msg_text_offset = code_ptr[3];

			Rut::RxJson::JObject msg_entry;

			if (name_text_offset)
			{
				std::wstring char_name_text = Rut::RxStr::ToWCS(text_dat[name_text_offset], 932);
				msg_entry[L"cha_org"] = char_name_text;
				msg_entry[L"cha_tra"] = std::move(char_name_text);
			}

			if (msg_text_offset)
			{
				std::wstring msg_text = Rut::RxStr::ToWCS(text_dat[msg_text_offset], 932);
				msg_entry[L"msg_org"] = msg_text;
				msg_entry[L"msg_tra"] = std::move(msg_text);
			}

			json_msg_array.emplace_back(std::move(msg_entry));
		}
		break;

		case 0x01010804:  // [select text]
		{
			uint32_t select_text_offset = code_ptr[1];
			if (select_text_offset)
			{
				Rut::RxJson::JObject msg_entry;
				std::wstring select_text = Rut::RxStr::ToWCS(text_dat[select_text_offset], 932);
				msg_entry[L"sel_org"] = select_text;
				msg_entry[L"sel_tra"] = std::move(select_text);
				json_msg_array.emplace_back(std::move(msg_entry));
			}
		}
		break;

		case 0x01000D02: // [chapter text]
		{
			uint32_t chapter_text_offset = code_ptr[1];
			if (chapter_text_offset)
			{
				Rut::RxJson::JObject msg_entry;
				std::wstring chapter_text = Rut::RxStr::ToWCS(text_dat[chapter_text_offset], 932);
				msg_entry[L"chapter_org"] = chapter_text;
				msg_entry[L"chapter_tra"] = std::move(chapter_text);
				json_msg_array.emplace_back(std::move(msg_entry));
			}
		}
		break;
		}
	}

	Rut::RxJson::Parser::Save(json_msg_array, L"scenario.json",true);
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


