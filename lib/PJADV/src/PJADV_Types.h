#pragma once
#include <cstdio>


namespace PJADV
{
	struct PAJ_Pack_File_Name
	{
		char aFileName[0x20];
	};

	struct PAJ_Pack_File_Info
	{
		uint32_t uiOffset; // skip HDR
		uint32_t uiSize;
	};

	struct PAJ_Pack_HDR_Info
	{
		char aSignature[12]; // "GAMEDAT PAC2"
		uint32_t uiFileCount;
	};

#pragma pack(1)
	struct PAJ_OPCode
	{
		uint8_t ucCount;
		uint8_t ucUn0;
		uint8_t ucUn1;
		uint8_t ucUn2;
	};
#pragma pack()
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