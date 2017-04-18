#include "resource.h"
#include "commdlg.h"

#define     GlobalSizePtr(lp)		\
                (GlobalUnlockPtr(lp), (BOOL)GlobalSize(GlobalPtrHandle(lp)))

#define  APPNAME	 "Metafile Decoder"	

#define  DESTDISPLAY     0
#define  DESTMETA        1

int      iDestDC;
//
//common dialog structures and constants 
//
#define MAXFILTERLEN 256

typedef struct tagFOCHUNK  {
        OPENFILENAME of;
        char szFile[256];
        char szFileTitle[256];
} FOCHUNK;

typedef FOCHUNK FAR *LPFOCHUNK;
typedef FOCHUNK FAR *LPFSCHUNK; 
typedef WORD (CALLBACK* FARHOOK)(HWND,UINT,WPARAM,LPARAM);
//
//structure of ptrs to global memory for emf header and 
//description string
//
typedef struct tagEHNMETAMEMPTR  {
        LPENHMETAHEADER lpEMFHdr;
		LPTSTR			lpDescStr;
		LPPALETTEENTRY  lpPal;
		WORD			palNumEntries;
} EHNMETAMEMPTR, *PEHNMETAMEMPTR, *LPEHNMETAMEMPTR;
//
//clipboard data definitions 
//
#define      CLP_ID         0xC350
#define      CLP_NT_ID      0xC351
#define      CLPBK_NT_ID    0xC352
#define      CLPMETANAMEMAX 79
//
//NT clipboard file header
//
typedef struct  {
   WORD        FileIdentifier;
   WORD        FormatCount;
} NTCLIPFILEHEADER;
//
// NT clipboard file format header
//
typedef struct  {
   DWORD FormatID;
   DWORD DataLen;
   DWORD DataOffset;
   WCHAR  Name[CLPMETANAMEMAX];
} NTCLIPFILEFORMAT, *LPNTCLIPFILEFORMAT;

//
//Win 3.1 clipboard file header
//
#pragma pack(1)
typedef struct {
        WORD FileIdentifier;
        WORD FormatCount;
} CLIPFILEHEADER;
//
//Win 3.1 clipboard format header 
//
typedef struct {
        WORD  FormatID;
        DWORD DataLen;
        DWORD DataOffset;
        char  Name[CLPMETANAMEMAX];
} CLIPFILEFORMAT, FAR *LPCLIPFILEFORMAT;
//
//Win 3.1 metafilepict structure 
//
typedef struct tagOLDMETAFILEPICT {
	short	   mm;
	short	   xExt;
	short	   yExt;
	WORD	   hMF;
} OLDMETAFILEPICT;

typedef OLDMETAFILEPICT FAR *LPOLDMETAFILEPICT;
//
//placeable metafile data definitions 
//
typedef struct tagOLDRECT
{
    short   left;
    short   top;
    short   right;
    short   bottom;
} OLDRECT;
//
//placeable metafile header 
//
typedef struct {
        DWORD   key;
        WORD	hmf;
        OLDRECT	bbox;
        WORD    inch;
        DWORD   reserved;
        WORD    checksum;
}ALDUSMFHEADER;
#pragma pack()

#define  ALDUSKEY	 0x9AC6CDD7
//
//metafile function table lookup data definitions 
//
#define  NUMMETAFUNCTIONS 71
typedef struct tagEMFMETARECORDS {
		char *szRecordName;
		DWORD iType;
} EMFMETARECORDS, *LPEMFMETARECORDS;

#define  NUMENHMETARECORDS 97
typedef struct tagMETAFUNCTIONS {
        char *szFuncName;
        WORD value;
} METAFUNCTIONS;

typedef LPWORD  LPPARAMETERS;
typedef LPDWORD LPEMFPARAMETERS;
//
//global vars for main module 
//
#ifdef MAIN

HANDLE hInst;
HANDLE CurrenthDlg;
HANDLE hSaveCursor;
HWND   hWndMain;
HWND   hWndList;

LPPARAMETERS lpMFParams;
LPEMFPARAMETERS lpEMFParams;
HANDLE hMem;
HANDLE hSelMem;
int FAR *lpSelMem;
EHNMETAMEMPTR EmfPtr;
//
//flags
//
BOOL bInPaint;
BOOL bPlayRec;
BOOL bPlayItAll;
BOOL bBadFile      = FALSE;
BOOL bValidFile    = FALSE;
BOOL bEnhMeta      = FALSE;
BOOL bMetaFileOpen = FALSE;
BOOL bMetaInRam    = FALSE;
BOOL bAldusMeta    = FALSE;
BOOL bPlayList     = FALSE;
BOOL bPlaySelList  = TRUE;
BOOL bEnumRange;

int  iEnumAction;
int  iStartRange;
int  iEndRange;

DWORD iCount = 0;               //index into lpSelMem
DWORD iNumSel = 0;               //number of listbox selections

//
//common fo dialog vars
//
char gszSaveEMFFilter[MAXFILTERLEN]="Enhanced MetaFile(*.EMF)\0*.EMF\0\0";
char gszSaveWMFFilter[MAXFILTERLEN]="Windows MetaFile(*.WMF)\0*.WMF\0\0";
char gszFilter[MAXFILTERLEN]="Enhanced MetaFiles(*.EMF)\0*.EMF\0Windows Metafiles(*.WMF)\0*.WMF\0Clipboard Pictures(*.CLP)\0*.CLP\0\0";
char gszBuffer[MAXFILTERLEN];
int  nFileOffset;
int  nExtOffset;
//
//file io related vars
//
char                  OpenName[144];
char                  SaveName[144];
char                  str[255];
OFSTRUCT              ofStruct;
DWORD                 iLBItemsInBuf;
char                  fnameext[20];
//
//metafile related vars
//
HANDLE                hMF;
HENHMETAFILE		  hemf;
METAFILEPICT          MFP;
METARECORD            MetaRec;
METAHEADER            mfHeader;
ALDUSMFHEADER         aldusMFHeader;
ENHMETAHEADER		  emfHeader;
ENHMETARECORD		  emfMetaRec;
WORD                  iRecNum = 0;
HANDLE                hMFP;
LPMETAFILEPICT	      lpMFP = NULL;
LPOLDMETAFILEPICT     lpOldMFP = NULL;
HGLOBAL               hMFBits;
LPSTR                 lpMFBits = NULL;
//
//lookup table for EMF and WMF metafile records 
//
EMFMETARECORDS emfMetaRecords[] = {
     "EMR_HEADER"                      ,1,
     "EMR_POLYBEZIER"                  ,2,
     "EMR_POLYGON"                     ,3,
     "EMR_POLYLINE"                    ,4,
     "EMR_POLYBEZIERTO"                ,5,
     "EMR_POLYLINETO"                  ,6,
     "EMR_POLYPOLYLINE"                ,7,
     "EMR_POLYPOLYGON"                 ,8,
     "EMR_SETWINDOWEXTEX"              ,9,
     "EMR_SETWINDOWORGEX"              ,10,
     "EMR_SETVIEWPORTEXTEX"            ,11,
     "EMR_SETVIEWPORTORGEX"            ,12,
     "EMR_SETBRUSHORGEX"               ,13,
     "EMR_EOF"                         ,14,
     "EMR_SETPIXELV"                   ,15,
     "EMR_SETMAPPERFLAGS"              ,16,
     "EMR_SETMAPMODE"                  ,17,
     "EMR_SETBKMODE"                   ,18,
     "EMR_SETPOLYFILLMODE"             ,19,
     "EMR_SETROP2"                     ,20,
     "EMR_SETSTRETCHBLTMODE"           ,21,
     "EMR_SETTEXTALIGN"                ,22,
     "EMR_SETCOLORADJUSTMENT"          ,23,
     "EMR_SETTEXTCOLOR"                ,24,
     "EMR_SETBKCOLOR"                  ,25,
     "EMR_OFFSETCLIPRGN"               ,26,
     "EMR_MOVETOEX"                    ,27,
     "EMR_SETMETARGN"                  ,28,
     "EMR_EXCLUDECLIPRECT"             ,29,
     "EMR_INTERSECTCLIPRECT"           ,30,
     "EMR_SCALEVIEWPORTEXTEX"          ,31,
     "EMR_SCALEWINDOWEXTEX"            ,32,
     "EMR_SAVEDC"                      ,33,
     "EMR_RESTOREDC"                   ,34,
     "EMR_SETWORLDTRANSFORM"           ,35,
     "EMR_MODIFYWORLDTRANSFORM"        ,36,
     "EMR_SELECTOBJECT"                ,37,
     "EMR_CREATEPEN"                   ,38,
     "EMR_CREATEBRUSHINDIRECT"         ,39,
     "EMR_DELETEOBJECT"                ,40,
     "EMR_ANGLEARC"                    ,41,
     "EMR_ELLIPSE"                     ,42,
     "EMR_RECTANGLE"                   ,43,
     "EMR_ROUNDRECT"                   ,44,
     "EMR_ARC"                         ,45,
     "EMR_CHORD"                       ,46,
     "EMR_PIE"                         ,47,
     "EMR_SELECTPALETTE"               ,48,
     "EMR_CREATEPALETTE"               ,49,
     "EMR_SETPALETTEENTRIES"           ,50,
     "EMR_RESIZEPALETTE"               ,51,
     "EMR_REALIZEPALETTE"              ,52,
     "EMR_EXTFLOODFILL"                ,53,
     "EMR_LINETO"                      ,54,
     "EMR_ARCTO"                       ,55,
     "EMR_POLYDRAW"                    ,56,
     "EMR_SETARCDIRECTION"             ,57,
     "EMR_SETMITERLIMIT"               ,58,
     "EMR_BEGINPATH"                   ,59,
     "EMR_ENDPATH"                     ,60,
     "EMR_CLOSEFIGURE"                 ,61,
     "EMR_FILLPATH"                    ,62,
     "EMR_STROKEANDFILLPATH"           ,63,
     "EMR_STROKEPATH"                  ,64,
     "EMR_FLATTENPATH"                 ,65,
     "EMR_WIDENPATH"                   ,66,
     "EMR_SELECTCLIPPATH"              ,67,
     "EMR_ABORTPATH"                   ,68,
     "EMR_GDICOMMENT"                  ,70,
     "EMR_FILLRGN"                     ,71,
     "EMR_FRAMERGN"                    ,72,
     "EMR_INVERTRGN"                   ,73,
     "EMR_PAINTRGN"                    ,74,
     "EMR_EXTSELECTCLIPRGN"            ,75,
     "EMR_BITBLT"                      ,76,
     "EMR_STRETCHBLT"                  ,77,
     "EMR_MASKBLT"                     ,78,
     "EMR_PLGBLT"                      ,79,
     "EMR_SETDIBITSTODEVICE"           ,80,
     "EMR_STRETCHDIBITS"               ,81,
     "EMR_EXTCREATEFONTINDIRECTW"      ,82,
     "EMR_EXTTEXTOUTA"                 ,83,
     "EMR_EXTTEXTOUTW"                 ,84,
     "EMR_POLYBEZIER16"                ,85,
     "EMR_POLYGON16"                   ,86,
     "EMR_POLYLINE16"                  ,87,
     "EMR_POLYBEZIERTO16"              ,88,
     "EMR_POLYLINETO16"                ,89,
     "EMR_POLYPOLYLINE16"              ,90,
     "EMR_POLYPOLYGON16"               ,91,
     "EMR_POLYDRAW16"                  ,92,
     "EMR_CREATEMONOBRUSH"             ,93,
     "EMR_CREATEDIBPATTERNBRUSHPT"     ,94,
     "EMR_EXTCREATEPEN"                ,95,
     "EMR_POLYTEXTOUTA"                ,96,
     "EMR_POLYTEXTOUTW"                ,97,
};

METAFUNCTIONS MetaFunctions[] = {

     "SETBKCOLOR",           0x0201,
     "SETBKMODE",            0x0102,
     "SETMAPMODE",           0x0103,
     "SETROP2",              0x0104,
     "SETRELABS",            0x0105,
     "SETPOLYFILLMODE",      0x0106,
     "SETSTRETCHBLTMODE",    0x0107,
     "SETTEXTCHAREXTRA",     0x0108,
     "SETTEXTCOLOR",         0x0209,
     "SETTEXTJUSTIFICATION", 0x020A,
     "SETWINDOWORG",         0x020B,
     "SETWINDOWEXT",         0x020C,
     "SETVIEWPORTORG",       0x020D,
     "SETVIEWPORTEXT",       0x020E,
     "OFFSETWINDOWORG",      0x020F,
     "SCALEWINDOWEXT",       0x0400,
     "OFFSETVIEWPORTORG",    0x0211,
     "SCALEVIEWPORTEXT",     0x0412,
     "LINETO",               0x0213,
     "MOVETO",               0x0214,
     "EXCLUDECLIPRECT",      0x0415,
     "INTERSECTCLIPRECT",    0x0416,
     "ARC",                  0x0817,
     "ELLIPSE",              0x0418,
     "FLOODFILL",            0x0419,
     "PIE",                  0x081A,
     "RECTANGLE",            0x041B,
     "ROUNDRECT",            0x061C,
     "PATBLT",               0x061D,
     "SAVEDC",               0x001E,
     "SETPIXEL",             0x041F,
     "OFFSETCLIPRGN",        0x0220,
     "TEXTOUT",              0x0521,
     "BITBLT",               0x0922,
     "STRETCHBLT",           0x0B23,
     "POLYGON",              0x0324,
     "POLYLINE",             0x0325,
     "ESCAPE",               0x0626,
     "RESTOREDC",            0x0127,
     "FILLREGION",           0x0228,
     "FRAMEREGION",          0x0429,
     "INVERTREGION",         0x012A,
     "PAINTREGION",          0x012B,
     "SELECTCLIPREGION",     0x012C,
     "SELECTOBJECT",         0x012D,
     "SETTEXTALIGN",         0x012E,
     "DRAWTEXT",             0x062F,
     "CHORD",                0x0830,
     "SETMAPPERFLAGS",       0x0231,
     "EXTTEXTOUT",           0x0a32,
     "SETDIBTODEV",          0x0d33,
     "SELECTPALETTE",        0x0234,
     "REALIZEPALETTE",       0x0035,
     "ANIMATEPALETTE",       0x0436,
     "SETPALENTRIES",        0x0037,
     "POLYPOLYGON",          0x0538,
     "RESIZEPALETTE",        0x0139,
     "DIBBITBLT",            0x0940,
     "DIBSTRETCHBLT",        0x0b41,
     "DIBCREATEPATTERNBRUSH",0x0142,
     "STRETCHDIB",           0x0f43,
     "DELETEOBJECT",         0x01f0,
     "CREATEPALETTE",        0x00f7,
     "CREATEBRUSH",          0x00F8,
     "CREATEPATTERNBRUSH",   0x01F9,
     "CREATEPENINDIRECT",    0x02FA,
     "CREATEFONTINDIRECT",   0x02FB,
     "CREATEBRUSHINDIRECT",  0x02FC,
     "CREATEBITMAPINDIRECT", 0x02FD,
     "CREATEBITMAP",         0x06FE,
     "CREATEREGION",         0x06FF,
};
//
//printer variables 
//
HDC                   hPr;                 // handle for printer device context
POINT                 PhysPageSize;        // information about the page
BOOL                  bAbort;              // FALSE if user cancels printing
HWND                  hAbortDlgWnd;
FARPROC               lpAbortDlg;
FARPROC               lpAbortProc;

#endif /* if defined MAIN */
//
//externs 
//
#ifndef MAIN

extern HANDLE         hInst;
extern HANDLE         CurrenthDlg;
extern HANDLE         hSaveCursor;
extern HWND           hWndMain;
extern HWND           hWndList;

extern LPPARAMETERS   lpMFParams;
extern LPEMFPARAMETERS lpEMFParams;
extern HANDLE         hMem;
extern HANDLE         hSelMem;
extern int FAR        *lpSelMem;
extern EHNMETAMEMPTR  EmfPtr;
//
//flags
//
extern BOOL           bInPaint;
extern BOOL           bPlayRec;
extern BOOL           bPlayItAll;
extern BOOL           bBadFile;
extern BOOL           bValidFile;
extern BOOL           bEnhMeta;
extern BOOL           bMetaFileOpen;
extern BOOL           bMetaInRam;
extern BOOL           bAldusMeta;
extern BOOL           bPlayList;
extern BOOL           bPlaySelList;
extern BOOL           bEnumRange;

extern int            iEnumAction;
extern int            iStartRange;
extern int            iEndRange;

extern DWORD          iCount;              //index into lpSelMem
extern DWORD          iNumSel;             //number of listbox selections
//
//common dialog vars
//
extern char gszSaveEMFFilter[MAXFILTERLEN];
extern char gszSaveWMFFilter[MAXFILTERLEN];
extern char gszFilter[MAXFILTERLEN];
extern char gszBuffer[MAXFILTERLEN];
extern int  nFileOffset;
extern int  nExtOffset;
//
//file io related vars
//
extern char           OpenName[144];
extern char           SaveName[144];
extern char           str[256];
extern OFSTRUCT       ofStruct;
extern DWORD          iLBItemsInBuf;
extern char           fnameext[20];
//
//metafile related vars
//
extern HANDLE         hMF;
extern HENHMETAFILE   hemf;
extern METAFILEPICT   MFP;
extern METARECORD     MetaRec;
extern METAHEADER     mfHeader;
extern ALDUSMFHEADER  aldusMFHeader;
extern ENHMETAHEADER  emfHeader;
extern ENHMETARECORD  emfMetaRec;
extern WORD           iRecNum;
extern EMFMETARECORDS emfMetaRecords[];
extern METAFUNCTIONS  MetaFunctions[];
extern HANDLE	      hMFP;
extern LPMETAFILEPICT lpMFP;
extern LPOLDMETAFILEPICT lpOldMFP;
extern HGLOBAL	      hMFBits;
extern LPSTR	      lpMFBits;
//
//printer variables
//
extern HDC            hPr;                 // handle for printer device context
extern POINT          PhysPageSize;        // information about the page
extern BOOL           bAbort;              // FALSE if user cancels printing
extern HWND           hAbortDlgWnd;

#endif /* if !defined MAIN */
//
//function prototypes 
//
//
//MFDCOD32.C 

int    APIENTRY WinMain(HANDLE, HANDLE, LPSTR, int);
BOOL   InitApplication(HANDLE);
BOOL   InitInstance(HANDLE, int);
long   CALLBACK	MainWndProc(HWND, UINT, WPARAM, LPARAM);
HANDLE FAR PASCAL OpenDlg(HWND, unsigned, WORD, LONG);
void   WaitCursor(BOOL);
//
//WMFMETA.C 
//
int    CALLBACK EnhMetaFileEnumProc(HDC, LPHANDLETABLE, LPENHMETARECORD, int, LPARAM);
int    CALLBACK MetaEnumProc(HDC, LPHANDLETABLE, LPMETARECORD, int, LPARAM);
void   GetMetaFileAndEnum(HDC, int);
BOOL   LoadParameterLB(HWND, DWORD, int);
BOOL   PlayMetaFileToDest(HWND, int);
BOOL   RenderClipMeta(LPVOID, int, WORD);
BOOL   RenderPlaceableMeta(int);
void   SetPlaceableExts(HDC, ALDUSMFHEADER, int);
VOID   SetClipMetaExts(HDC, LPMETAFILEPICT, LPOLDMETAFILEPICT, int);
BOOL   ProcessFile(HWND, LPSTR);
BOOL   ProcessWMF(HWND hWnd, LPSTR lpFileName);
BOOL   ProcessCLP(HWND hWnd, LPSTR lpFileName);
BOOL   ProcessEMF(HWND hWnd, LPSTR lpFileName);
BOOL   GetEMFCoolStuff(void);
BOOL   GetEMFCoolStuff(void);
int    EnumMFIndirect(HDC hDC, LPHANDLETABLE lpHTable, 
                      LPMETARECORD lpMFR, 
                      LPENHMETARECORD lpEMFR, 
                      int nObj, LPARAM lpData);
BOOL ConvertWMFtoEMF(HMETAFILE hmf, LPSTR lpszFileName);
BOOL ConvertEMFtoWMF(HDC hrefDC, HENHMETAFILE hEMF, LPSTR lpszFileName);
//
//DLGPROC.C 
//
BOOL CALLBACK WMFRecDlgProc(HWND, unsigned, WPARAM, LPARAM);
BOOL CALLBACK EnhMetaHeaderDlgProc(HWND, unsigned, WPARAM, LPARAM);
BOOL CALLBACK HeaderDlgProc(HWND, unsigned, WPARAM, LPARAM);
BOOL CALLBACK ClpHeaderDlgProc(HWND, unsigned, WPARAM, LPARAM);
BOOL CALLBACK AldusHeaderDlgProc(HWND, unsigned, WPARAM, LPARAM);
BOOL CALLBACK EnumRangeDlgProc(HWND, unsigned, WPARAM, LPARAM);
BOOL CALLBACK ListDlgProc(HWND, unsigned, WPARAM, LPARAM);
BOOL CALLBACK PlayFromListDlgProc(HWND, unsigned, WPARAM, LPARAM);
BOOL CALLBACK About(HWND, unsigned, WPARAM, LPARAM);
//
//WMFPRINT.C 
//
BOOL   PrintWMF(void);
HANDLE GetPrinterDC(void);
int    CALLBACK AbortDlg(HWND, unsigned, WPARAM, LPARAM);
int    CALLBACK AbortProc(HDC, int);
//
//CMNDLG.C 
//
void InitializeStruct(WORD, LPSTR, LPSTR);
int  OpenFileDialog(LPSTR);
int  SaveFileDialog(LPSTR, LPSTR);
void SplitPath( LPSTR, LPSTR, LPSTR, LPSTR, LPSTR);
