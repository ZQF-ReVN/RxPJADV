#include <iostream>
#include <ranges>

#include "../../lib/Rut/RxJson.h"
#include "../../lib/Rut/RxStr.h"
#include "../../lib/PJADV/Bin.h"

static void Export(const std::filesystem::path& phTextDataBin, const std::filesystem::path& phScenarioDataBin)
{
	PJADV::Bin::TextDataDat text_dat(phTextDataBin);
	PJADV::Bin::ScenarioDat scen_dat(phScenarioDataBin);

	Rut::RxJson::JArray json_msg_array;
	Rut::RxJson::JArray json_seq_array;
	int ite_code = 0;
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

			json_seq_array.push_back(ite_code);
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

				json_seq_array.push_back(ite_code);
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

				json_seq_array.push_back(ite_code);
				json_msg_array.emplace_back(std::move(msg_entry));
			}
		}
		break;
		}

		ite_code++;
	}

	Rut::RxJson::Parser::Save(json_msg_array, phScenarioDataBin.filename().wstring() + L"_msg.json", true);
	Rut::RxJson::Parser::Save(json_seq_array, phScenarioDataBin.filename().wstring() + L"_seq.json", true);
}

static void Import(const std::filesystem::path& phTextDataBin, const std::filesystem::path& phScenarioDataBin, const std::filesystem::path& phMsgJson, const std::filesystem::path& phSeqJson, size_t nCodePage)
{
	PJADV::Bin::TextDataDat text_dat(phTextDataBin);
	PJADV::Bin::ScenarioDat scen_dat(phScenarioDataBin);

	Rut::RxJson::JArray json_seq_array = Rut::RxJson::Parser{}.Load(phSeqJson);
	Rut::RxJson::JArray json_msg_array = Rut::RxJson::Parser{}.Load(phMsgJson);

	const std::vector<uint32_t*>& code_list = scen_dat.GetPtrs();
	for (auto [msg, seq] : std::views::zip(json_msg_array, json_seq_array))
	{
		uint32_t* code_ptr = code_list[seq.ToInt()];
		switch (code_ptr[0])
		{
		case 0x80000307:  // [text_box_text]
		{
			if (code_ptr[2])
			{
				code_ptr[2] = text_dat.AddText(msg[L"cha_tra"], nCodePage);
			}

			if (code_ptr[3])
			{
				code_ptr[3] = text_dat.AddText(msg[L"msg_tra"], nCodePage);
			}
		}
		break;

		case 0x01010804:  // [select text]
		{
			if (code_ptr[1])
			{
				code_ptr[1] = text_dat.AddText(msg[L"sel_tra"], nCodePage);
			}
		}
		break;

		case 0x01000D02: // [chapter text]
		{
			if (code_ptr[1])
			{
				code_ptr[1] = text_dat.AddText(msg[L"chapter_tra"], nCodePage);
			}
		}
		break;
		}
	}

	text_dat.Save(phTextDataBin.wstring() + L".new");
	scen_dat.Save(phScenarioDataBin.wstring() + L".new");
}


static void DebugMain()
{
	//::Export(L"textdata.bin", L"scenario.dat");
	//::Import(L"textdata.bin", L"scenario.dat", L"scenario_msg.json", L"scenario_seq.json", 932);
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


