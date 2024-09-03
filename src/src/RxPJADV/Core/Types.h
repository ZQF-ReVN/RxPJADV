#pragma once
#include <cstdio>

namespace ZQF::RxPJADV::PackV2
{
#pragma pack(push,1)
	struct File_Name
	{
		char aFileName[32];

		static auto SizeBytes() -> std::size_t
		{
			return sizeof(aFileName);
		}
	};

	struct File_Info
	{
		std::uint32_t nOffset; // skip HDR
		std::uint32_t nBytes;

		static auto SizeBytes() -> std::size_t
		{
			return sizeof(nOffset) + sizeof(nBytes);
		}
	};

	struct HDR_Info
	{
		char aSignature[12];       // "GAMEDAT PAC2"
		std::uint32_t nFileCount;

		static auto Make(const std::size_t nFileCnt) -> HDR_Info
		{
			PackV2::HDR_Info hdr_info{ .nFileCount{ static_cast<std::uint32_t>(nFileCnt) } };
			std::memcpy(hdr_info.aSignature, "GAMEDAT PAC2", 12);
			return hdr_info;
		}

		static auto SizeBytes() -> std::size_t
		{
			return sizeof(aSignature) + sizeof(nFileCount);
		}
	};
#pragma pack(pop)
}

namespace ZQF::RxPJADV::Script
{
#pragma pack(push,1)
	struct OPCode
	{
		std::uint8_t ucCount;
		std::uint8_t ucUn0;
		std::uint8_t ucUn1;
		std::uint8_t ucUn2;
	};

	using File_Name = PackV2::File_Name;
#pragma pack(pop)
}

namespace ZQF::RxPJADV
{
	//using PAJ_FileName_Dat_Entry = PAJ_Pack_File_Name
	//struct PAJ_FileName_Dat
	//{
	//	char                   aSignature[12]; // "PJADV_FL0001"
	//	uint32_t               uiNameCount;
	//	PAJ_FileName_Dat_Entry aFileNameIndex[uiNameCount];
	//}

	//struct PAJ_Pack_HDR
	//{
	//	PAJ_Pack_HDR_Info  Info;
	//	PAJ_Pack_File_Name FileNameList[uiFileCount];
	//	PAJ_Pack_File_Info FileInfoList[uiFileCount];
	//};
}