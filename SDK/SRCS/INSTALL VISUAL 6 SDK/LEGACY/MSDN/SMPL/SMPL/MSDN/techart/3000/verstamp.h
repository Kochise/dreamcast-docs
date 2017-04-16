/*------------------------------------------------------------------------|
  | Copyright (c) 1990, MicroSoft Corporation                             |
  |                                                                       |
  | verstamp.h - Header file for version fuction sample                    |
  |-----------------------------------------------------------------------|
  | modification history                                                  |
  | Date    Reason                                                        |
  | 911201  Creation date                                                 |
  |------------------------------------------------------------------------*/

#define VERINFOLEN    512             // Bytes to hold version info resource
#define BUFLEN        256             // Buffer lengths


DWORD gdwVerInfo       = 0L;           // Global data
BOOL  bFirst           = TRUE;

typedef struct tagVS_VERSION
  {
    WORD wTotLen;
    WORD wValLen;
    char szSig[16];
    VS_FIXEDFILEINFO vffInfo;
  } VS_VERSION;

typedef struct tagLANGANDCP
  {
    WORD wLanguage;
    WORD wCodePage;
  } LANGANDCP;

HANDLE  ghInst;

char gszUserMsg[BUFLEN];

char  gszCurDir[_MAX_PATH],
      gszWinDir[_MAX_PATH],           // Windows directory
      gszSysDir[_MAX_PATH],           // Windows system directory
      gszSrcDir[_MAX_PATH],           // source dir name
      gszSrcFile[BUFLEN],             // source file name
      gszTrgDir[_MAX_PATH],
      gsqTrgFile[BUFLEN],
      gszCurDir[_MAX_PATH],
      gszDstDir[_MAX_PATH];


WORD  gwCurDirLen = _MAX_PATH;
WORD  gwDstDirLen = _MAX_PATH;


char gszDlgClear[] = ".";               // Indicates no info
char gszTrans[] = "\\VarFileInfo\\Translation";
char *gszVerString[] =
  {
  "Illegal string",
  "CompanyName",
  "FileDescription",
  "FileVersion",
  "InternalName",
  "LegalCopyright",
  "LegalTrademarks",
  "ProductName",
  "ProductVersion"
  };
char gszAppName[] = "VerStamp";
HLSTR _pascal __export vbGetVerInfo(LPSTR szFullPath, int item);
BOOL __export _pascal HasVerInfo(LPSTR szFullPath);
HLSTR  ShowVerInfo(LPSTR szFullPath, int item);
HLSTR FillVerDialog( VS_VERSION FAR *pVerInfo, int i);
HLSTR FAR PASCAL MoreVerInfo (LPSTR szFullPath, int i);

