#include "TextManager.h"
#include <ranges>
#include <string_view>
#include <ZxJson/JValue.h>
#include <ZxJson/JIO.h>
#include <ZxCvt/ZxCvt.h>
#include <RxPJADV/Core/Bin_Scenario.h>
#include <RxPJADV/Core/Bin_TextData.h>


namespace ZQF::RxPJADV::Script
{
	auto TextManager::Export(const std::string_view msTextDataBinPath, const std::string_view msScenarioDataBinPath, const std::string_view msMsgJsonPath, const std::string_view msSeqJsonPath, const std::size_t nCodePage) -> void
	{
		Script::TextDataDat text_dat{ msTextDataBinPath };
		Script::ScenarioDat scen_dat{ msScenarioDataBinPath };

		ZxJson::JArray_t json_msg_array;
		ZxJson::JArray_t json_seq_array;

		ZxCvt cvt;
		for (auto&& [idx, code_ptr] : std::views::enumerate(scen_dat.GetPtrs()))
		{
			switch (code_ptr[0])
			{
			case 0x80000406: // [text_box_text]
			case 0x80000307:
			{
				const auto name_text_offset = code_ptr[2];
				const auto msg_text_offset = code_ptr[3];

				ZxJson::JObject_t msg_entry;

				if (name_text_offset)
				{
					const auto char_name_text_u8 = cvt.MBCSToUTF8(text_dat.GetText(name_text_offset), nCodePage);
					msg_entry["chr_org"] = char_name_text_u8;
					msg_entry["chr_tra"] = char_name_text_u8;
				}

				if (msg_text_offset)
				{
					const auto msg_text_u8 = cvt.MBCSToUTF8(text_dat.GetText(msg_text_offset), nCodePage);
					msg_entry["msg_org"] = msg_text_u8;
					msg_entry["msg_tra"] = msg_text_u8;
				}

				json_seq_array.emplace_back(idx);
				json_msg_array.emplace_back(std::move(msg_entry));
			}
			break;

			case 0x01010203: // [select text]
			case 0x01010804:
			{
				const auto select_text_offset = code_ptr[1];
				if (select_text_offset)
				{
					const auto select_text_u8 = cvt.MBCSToUTF8(text_dat.GetText(select_text_offset), nCodePage);
					json_seq_array.emplace_back(idx);
					json_msg_array.emplace_back(ZxJson::JObject_t{ { "sel_org", select_text_u8 }, { "sel_tra", select_text_u8 } });
				}
			}
			break;

			case 0x01000D02: // [chapter text]
			{
				const auto chapter_text_offset = code_ptr[1];
				if (chapter_text_offset)
				{
					const auto chapter_text_u8 = cvt.MBCSToUTF8(text_dat.GetText(chapter_text_offset), nCodePage);
					json_seq_array.push_back(idx);
					json_msg_array.emplace_back(ZxJson::JObject_t{ { "chp_org", chapter_text_u8 }, { "chp_tra", chapter_text_u8 } });
				}
			}
			break;

			case 0x03000303: // [save load comment]
			{
				const auto comment_text_offset = code_ptr[2];
				if (comment_text_offset)
				{
					const auto comment_text_u8 = cvt.MBCSToUTF8(text_dat.GetText(comment_text_offset), nCodePage);
					json_seq_array.push_back(idx);
					json_msg_array.emplace_back(ZxJson::JObject_t{ { "com_org", comment_text_u8 }, { "com_tra", comment_text_u8 } });
				}
			}
			break;
			}
		}

		ZxJson::StoreViaFile(msMsgJsonPath, json_msg_array, true, true);
		ZxJson::StoreViaFile(msSeqJsonPath, json_seq_array, true, true);
	}

	auto TextManager::Import(const std::string_view msTextDataBinPath, const std::string_view msScenarioDataBinPath, const std::string_view msMsgJsonPath, const std::string_view msSeqJsonPath, const std::size_t nCodePage) -> void
	{
		Script::TextDataDat text_dat{ msTextDataBinPath };
		Script::ScenarioDat scen_dat{ msScenarioDataBinPath };

		const auto json_seq_array{ ZxJson::LoadViaFile(msSeqJsonPath) };
		const auto json_msg_array{ ZxJson::LoadViaFile(msMsgJsonPath) };

		ZxCvt cvt;
		for (auto&& [msg, seq] : std::views::zip(json_msg_array.GetArray(), json_seq_array.GetArray()))
		{
			const auto code_ptr{ scen_dat.GetPtrs()[seq.GetNum()] };

			auto fn_append_text = [&nCodePage, &text_dat, &cvt, &msg](const std::string_view msKey) -> std::uint32_t
				{
					const auto org_sv{ msg.At(msKey).GetStrView() };
					const auto cvt_sv{ cvt.UTF8ToMBCS(org_sv, nCodePage) };
					return static_cast<std::uint32_t>(text_dat.AppendText(cvt_sv));
				};

			switch (code_ptr[0])
			{
			case 0x80000406: // [text_box_text]
			case 0x80000307:
			{
				if (code_ptr[2]) { code_ptr[2] = fn_append_text("chr_tra"); }
				if (code_ptr[3]) { code_ptr[3] = fn_append_text("msg_tra"); }
			}
			break;

			case 0x01010203: // [select text]
			case 0x01010804:
			{
				if (code_ptr[1]) { code_ptr[1] = fn_append_text("sel_tra"); }
			}
			break;

			case 0x01000D02: // [chapter text]
			{
				if (code_ptr[1]) { code_ptr[1] = fn_append_text("chp_tra"); }
			}
			break;

			case 0x03000303: // [save load comment]
			{
				if (code_ptr[2]) { code_ptr[2] = fn_append_text("com_tra"); }
			}
			break;
			}
		}

		text_dat.Save(std::string{ msTextDataBinPath }.append(".new"));
		scen_dat.Save(std::string{ msScenarioDataBinPath }.append(".new"));
	}
}

