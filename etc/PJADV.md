# PJADV Engine (-2023)

## Producers

- [Lillian](https://vndb.org/p379)

  - [ティンクル☆くるせいだーす -Passion Star Stream-](https://vndb.org/v5937) 
  - [ティンクル☆くるせいだーす ミラクルディスク](https://vndb.org/v1478)

- [Pajamas Soft](https://vndb.org/p144)

  - [夏の終わりのニルヴァーナ](https://vndb.org/v11193)
  
- [Omochi Soft](https://vndb.org/p6839)
  
  - [あるいは恋という名の魔法](https://vndb.org/v21121)
  
- [bootUP!](https://vndb.org/p173)
  
  - [ははむす外伝 水晶の女王フィーナ](https://vndb.org/v46287)
  
## Reference
https://github.com/Doddler/PrismArkTools

## Structures

```C
struct PAJ_ArchiveManager_Vector
{
  uint32_t uiUn0;
  PAJ_STD_Str *pBeg;
  PAJ_STD_Str *pEnd;
  uint32_t *pReserve;
};

struct PAJ_ArchiveManager_Map_Node_Pair
{
  PAJ_ArchiveManager_Map_Node_Pair *_Left;
  PAJ_ArchiveManager_Map_Node_Pair *_Parent;
  PAJ_ArchiveManager_Map_Node_Pair *_Right;
  PAJ_STD_Str msFileName;
  uint32_t uiPackSeq;
  uint8_t _Color;
  uint8_t ucIsNull;
};

struct PAJ_ArchiveManager_Map
{
  PAJ_ArchiveManager_Map_Node_Pair *pNode;
  PAJ_ArchiveManager_Map_Node_Pair *pHeader;
  uint32_t uiSize;
};

struct PAJ_ArchiveManager
{
  uint32_t *pVtable;
  PAJ_ArchiveManager_Vector Vector;
  PAJ_ArchiveManager_Map Map;
};

struct PAJ_INI_List
{
  PAJ_INI_List_Node *pNext;
  PAJ_INI_List_Node *pPrev;
  uint32_t uiSize;
};

struct PAJ_INI_List_Node
{
  PAJ_INI_List_Node *pNext;
  PAJ_INI_List_Node *pPrev;
  PAJ_STD_Str Value;
};

struct PAJ_DirectoryManager
{
  PAJ_DirectoryManager_Folder_Map *pFolderMap;
  PAJ_DirectoryManager_Path_Map *pPathMap;
};

struct PAJ_DirectoryManager_Folder_Map
{
  PAJ_DirectoryManager_Folder_Map_Node_Pair *pNode;
  PAJ_DirectoryManager_Folder_Map_Node_Pair *pHeader;
  uint32_t uiSize;
};

struct PAJ_ArchiveManager_Map_Ite
{
  PAJ_ArchiveManager_Map *pMap;
  PAJ_ArchiveManager_Map_Node_Pair *pPairs;
};

struct __declspec(align(4)) PAJ_DirectoryManager_Folder_Map_Node_Pair
{
  PAJ_DirectoryManager_Folder_Map_Node_Pair *_Left;
  PAJ_DirectoryManager_Folder_Map_Node_Pair *_Parent;
  PAJ_DirectoryManager_Folder_Map_Node_Pair *_Right;
  PAJ_STD_Str Value;
  char _Color;
  char _Isnil;
};

struct PAJ_DirectoryManager_Folder_Map_Ite
{
  PAJ_DirectoryManager_Folder_Map *pMap;
  PAJ_DirectoryManager_Folder_Map_Node_Pair *pPairs;
};

struct PAJ_DirectoryManager_Path_Map
{
  PAJ_DirectoryManager_Path_Map_Node_Pair *pNode;
  PAJ_DirectoryManager_Path_Map_Node_Pair *pHeader;
  uint32_t uiSize;
};

struct __declspec(align(4)) PAJ_DirectoryManager_Path_Map_Node_Pair
{
  PAJ_DirectoryManager_Path_Map_Node_Pair *_Left;
  PAJ_DirectoryManager_Path_Map_Node_Pair *_Parent;
  PAJ_DirectoryManager_Path_Map_Node_Pair *_Right;
  PAJ_STD_Str msFileName;
  PAJ_STD_Str msFilePath;
  char _Color;
  char _Isnil;
};

struct PAJ_DirectoryManager_Path_Map_Ite
{
  PAJ_DirectoryManager_Path_Map *pMap;
  PAJ_DirectoryManager_Path_Map_Node_Pair *pPairs;
};

struct PAJ_STD_Str
{
  uint32_t uiAlig;
  char aStr[16];
  uint32_t uiLen;
  uint32_t uiReserve;
};

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
    char     aSignature[12]; // "GAMEDAT PAC2"
    uint32_t uiFileCount;
};

struct PAJ_Pack_HDR
{
	PAJ_Pack_HDR_Info  Info;
	PAJ_Pack_File_Name FileNameList[uiFileCount];
	PAJ_Pack_File_Info FileInfoList[uiFileCount];
};

struct PAJ_Pack
{
    PAJ_Pack_HDR HDR;
    uint8_t aData[??];
};

using PAJ_FileName_Dat_Entry = PAJ_Pack_File_Name
struct PAJ_FileName_Dat
{
	char                   aSignature[12]; // "PJADV_FL0001"
	uint32_t               uiNameCount;
	PAJ_FileName_Dat_Entry aFileNameIndex[uiNameCount];
};

struct PAJ_TextData_Dat
{
	char     aSignature[12]; // "PJADV_TF0001"
	uint32_t uiTextCount;
	char     aText[??][uiTextCount]; // end with "\0\0"
};

struct PAJ_OPCode
{
    uint8_t  ucCount; // ucCount*sizeof(uint32_t) = (command size) or (move to next command)
    uint8_t  ucUn0;
    uint16_t usUn1;
};
// 03230001 22000000 10000000 : ucCount = 03 -> command size = 3*4= 12

struct PAJ_Command
{
    PAJ_OPCode OPCode;
    uint32_t   Append[OP.ucCodeCount - 1];
};

struct PAJ_Scenario_Dat
{
    char        aSignature[12]; // "PJADV_SF0001"
    uint32_t    uiMsgCount;
    uint8_t     aUnData[16];
    PAJ_Command CommandList[??];
};

struct PAJ_VM_Init_Info
{
  uint32_t uiUn0;
  uint32_t uiScenarioDataCount;
  uint32_t uiFileNameDataCount;
};

struct PAJ_VFS
{
    uint32_t uiType; // 0 -> read via dir / 1 -> read via pack
    HANDLE   hFile;
    uint32_t uiFOA;
    uint32_t uiFileSize;
    uint32_t uiFileSize_;
    uint32_t uiReadSize;
};

struct PAJ_EPA
{
    uint32_t uiSignature; 
    uint32_t uiUn0;
    uint32_t uiWidth;
    uint32_t uiHeigh;
    uint8_t aData[??];
};

struct PAJ_FontData_Entry
{
    uint16_t usCharValue;
    uint8_t aGlyphData[uiGlyphDataSize];
};

struct PAJ_FontData_File
{
    uint8_t aSignature[0xC]; // 'PF001Lillian'
    uint32_t uiEntryCount;
    uint32_t uiFontRectSize;
    uint32_t uiFontRectSize_Half;
    uint32_t uiGlyphDataSize;
    uint32_t uiGlyphDataSize_Half;
    PAJ_FontData_Entry aEntryList[uiEntryCount];
};

struct PAJ_FontData_List
{
  PAJ_FontData_List_Node *pHeader;
};

struct PAJ_FontData_List_Node_Entry
{
  uint16_t usCharValue;
  uint8_t *pGlyphData;
};

struct PAJ_FontData_List_Node
{
  PAJ_FontData_List_Node *pPrev;
  PAJ_FontData_List_Node *pNext;
  uint32_t uiFontSeq;
  uint8_t *pFontFile;
  PAJ_FontData_List_Node_Entry *pIndex;
  uint32_t uiGlyphCount;
  uint32_t uiGlyphDataSize;
  uint32_t uiGlyphDataSize_Half;
  uint32_t uiFontRect;
  uint32_t uiFontRect_Half;
};

```



## Command

```asm
0xF001300D
    0D3001F0

0x1002401 [open VolumeMixer]
    struct
    {
        dword: op
    }
    example:
        01240001

0x1002303 [open explorer.exe]
    struct
    {
        dword: op
        dword: index_in_filename_dat
        dword: foa_in_textdata_dat
    }
    example:
        03230001 22000000 10000000 (explorer.exe accessory\index.html)
        03230001 00000000 1BB11200 (explorer.exe http://www.lillian.jp/)

0x80000307 [text_box_text]
	struct
	{
		dword: OP
		dword: nSeq 
		dword: foa_in_text_data(chara name)
		dword: foa_in_text_data(msg text)
		dword: nSeq
		dword: un2
		dword: un3
	}
    example:
	    07030080 00000000 00000000 4C000000 01000000 00000300 01000000
	    07030080 00000000 00000000 A4000000 02000000 00000300 01000000
	    07030080 81050000 BA000000 C2000000 05000000 00000300 01000000
	    07030080 82050000 D4000000 DA000000 06000000 00000300 01000000
	    07030080 83050000 BA000000 E6000000 07000000 00000300 01000000
	    07030080 84050000 BA000000 28010000 08000000 00000300 01000000

0x01010101

0x01010804 [select text][あるいは恋という名の魔法]
    struct
    {
      	dword: OP
		dword: foa_in_text_data(select text)
		dword: un1
		dword: un2
    }
    example:
        04080101 EA000000 8C780000 00000000
	
0x01010203
	[op:dword][un0:dword][foa_in_text_data(txt):dword]
	03230001 22000000 10000000
	
0x01000D02 [chapter text]
	[op:dword][foa_in_text_data(txt):dword]
	020D0001 1C000000
	
0x03000303
	
0xF0080102

0xF0080002

0xF0080402

0xF0080502

0xF0080601

03230001 00000000 1BB11200
```



## 字体绘制控制

在 0048BAB0 引擎会创建一个绘制对象

里面有两个关键成员 ，一个是hfont和hdc(CreateCompatibleDC)

但hfont通过PAJ::Font::Create创建，该函数有两个参数，一个是字体类型，一个字体大小(注意这个大小，可能会造成间距过小，要把这个大小调低，因为fontdata传递的大小可能不一定适合gdi)

字体类型1，2，3，4调用GDI的CreateFontIndirectA创建字体，大于这个类型就不创建hfont

大于4的情况用于fontdata，也就是使用游戏自己的字体格式来绘制

在绘制字符的时候，会有个PAJ::Font::FontData::FontExist函数来检查，当前字符是否在内部加载的字体文件中，如果有就直接使用内部加载的字体文件来绘制，如果没有就调用GDI来绘制

但直接NOP这个函数来强制使用GDI是绘制不出字体的，因为进入GDI绘制的分支时会检查当前函数的hdc参数，如果绘制是为字体文件fontdata准备的，就不会有hfont，但hdc不为0，也就不会自动重新创建，所以这样就会出现游戏文本框没绘制任何东西的情况，而且这个引擎绘制的字体还会缓存，导致后续这些已经绘制过的字体就算给hdc选入的hfont也没办法显示，因为前面绘制的数据被它缓存起来了。

所以hook PAJ::Font::Create让引擎为fontdata绘制的对象也加载上hfont，然后把PAJ::Font::FontData::FontExist改成默认返回0，就可以重定向GDI绘制了，或者是直接不让fontdata文件加载，即nop掉PAJ::Font::FontData::Load

PAJ::Font::Create调用和虚拟机有关，也可以从虚拟机脚本入手

0B000003

03100003 pram:slot , param:font_size

