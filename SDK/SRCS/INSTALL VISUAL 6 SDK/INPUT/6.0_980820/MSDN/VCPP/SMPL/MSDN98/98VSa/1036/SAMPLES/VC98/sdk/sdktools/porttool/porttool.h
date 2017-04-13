
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples. 
*       Copyright (C) 1993-1997 Microsoft Corporation.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/

#include <windows.h>
#include <commdlg.h>
#include <string.h>
#include <stdlib.h>

#define strncpy     My_mbsncpy
#define strtok      My_mbstok
unsigned char * _cdecl My_mbsncpy(
                        unsigned char *, const unsigned char *, size_t);
unsigned char * _cdecl My_mbstok(unsigned char *, unsigned char *);

#ifdef RC_INVOKED
#define ID(id)			 id
#else
#define ID(id)			 MAKEINTRESOURCE(id)
#endif

#undef EDIT_FIXED

// resource ID's
#define IDPortTool		 ID(1)
#define IDBkPort		 ID(2)

#define IDA_PORTTOOL		 1

// edit control child window ID
#define IDC_EDIT		 1000

// max string lengths
#define MAXSEARCHSTRING 	 80
#define MAXPTRDEFINITION	 200
#define MAXPTRDEVICE		 50
#define MAXPTRDRIVER		 50
#define MAXPTRPORT		 50

// extra byte window word and long definitions
#define WL_HWNDEDIT		 0
#define WW_SCROLL		 4
#define WW_UNTITLED		 6
#define WW_SEARCHCASE		 8
#define WW_SEARCHDN		 10
#define WL_HPTRDEVNAMES 	 12
#define CBWNDEXTRA		 16

// menuitem IDs, file submenu
#define IDM_FILENEW		 	 1001
#define IDM_FILEOPEN		 1002
#define IDM_FILESAVE		 1003
#define IDM_FILESAVEAS		 1004
#define IDM_FILEPRINT		 1005
#define IDM_FILESETUP		 1006
#define IDM_FILEEXIT		 1007
#define IDM_FILEABOUT		 1008
// edit submenu
#define IDM_EDITUNDO		 2000
#define IDM_EDITCUT		 	 2001
#define IDM_EDITCOPY		 2002
#define IDM_EDITPASTE		 2003
#define IDM_EDITCLEAR		 2004
#define IDM_EDITSELECT		 2005
#define IDM_EDITWRAP		 2006
#define IDM_EDITSCROLL		 2007
#define IDM_EDITFONT		 2008
// search submenu
#define IDM_SEARCHFIND		 3001
#define IDM_SEARCHNEXT		 3002
#define IDM_SEARCHPREV		 3003
// port submenu
#define IDM_PORTCURFILE 	 4000
#define IDM_PORTBKGND		 4001

#define IDM_FUNCTION1		 5000
#define IDM_FUNCTION2		 5001
#define IDM_FUNCTION3		 5002
#define IDM_FUNCTION4		 5003
#define IDM_FUNCTION5		 5004

// dialog & control IDs

// about dialog
#define IDD_ABOUT		 ID(300)
#define IDC_SYSTEM       301
#define IDC_APP          302
#define IDC_VERSION      303
#define IDC_COPYRIGHT    304
#define IDC_OSVERSION    305

// cancel print dialog
#define IDD_CANCELDLG		 ID(400)
#define IDC_PRINTDEVICE 	 401
#define IDC_PRINTPORT		 402
#define IDC_PRINTTITLE		 403

// port options dialog
#define IDD_OPTIONSDLG		 ID(500)
#define IDC_NOAPIS		 501
#define IDC_NOMESSAGES		 502
#define IDC_NOSTRUCTURES	 503
#define IDC_NOMACROS		 504
#define IDC_NOCONSTANTS 	 505
#define IDC_NOTYPES		 506
#define IDC_NOCUSTOM		 507
#define IDC_IGNORECASE		 508
#define IDC_CURTOKEN		 509
#define IDC_IGNORETOKEN 	 510

// port current file dialog
#define IDD_PORTDIALOG		 ID(600)
#define IDC_SEARCHFOUND 	 601
#define IDC_ISSUECNT		 602
#define IDC_LINENO		 603
#define IDC_LINE		 604
#define IDC_ISSUE		 605
#define IDC_CONTINUE		 606
#define IDC_SUGGESTION		 608
#define IDC_SUGGESTLABEL	 609
#define IDC_OPTIONS		 610
#define IDC_DONE		 611
#define IDC_HELPM		 612
#define IDC_RESTART		 613

// background port status dialog
#define IDD_BKPORTDIALOG	 ID(700)
#define IDC_BKNOAPIS		 702
#define IDC_BKNOMESSAGES	 703
#define IDC_BKNOSTRUCTURES	 704
#define IDC_BKNOMACROS		 705
#define IDC_BKNOCONSTANTS	 706
#define IDC_BKNOTYPES		 707
#define IDC_BKNOCUSTOM		 708
#define IDC_BKIGNORECASE	 709
#define IDC_CHANGEOPTIONS	 710
#define IDC_ADDFILE		 711
#define IDC_COMPLETE		 712
#define IDC_LINES		 713
#define IDC_ISSUES		 714
#define IDC_ABORTFILE		 715
#define IDC_FILEPATH		 716
#define IDC_FILELIST		 717
#define IDC_BKDONE		 718


// file I/O error stringtable entries
#define IDS_OPENFAILED		  WM_USER+101
#define IDS_NOSIZE		  WM_USER+102
#define IDS_READFAILED		  WM_USER+103
#define IDS_REALLOCFAILED	  WM_USER+104
#define IDS_EDITWNDFAILED	  WM_USER+105
#define IDS_GETHANDLEFAILED	  WM_USER+106
#define IDS_WRITEOPENFAILED	  WM_USER+107
#define IDS_WRITEFAILED 	  WM_USER+108
#define IDS_PTRCOMMDLGFAILED	  WM_USER+109
#define IDS_PRINTABORTED	  WM_USER+110
#define IDS_STARTDOCFAILED	  WM_USER+111
#define IDS_SETABORTPROCFAILED	  WM_USER+112
#define IDS_CANCELDLGFAILED	  WM_USER+113
#define IDS_PTRCONFIGFAILED	  WM_USER+114
#define IDS_NOFILETOPORT	  WM_USER+115
#define IDS_PORTINITFAILED	  WM_USER+116
#define IDS_MEMORYFAILED	  WM_USER+117
#define IDS_FONTFAILEDTOCREATE	  WM_USER+118
#define IDS_LOADPORTFAILED	  WM_USER+119
#define IDS_PROCADDRESSFAILED	  WM_USER+120
#define IDS_UNTITLED		  WM_USER+201
#define IDS_APPNAME		  WM_USER+202
#define IDS_PRINTJOB		  WM_USER+203
#define IDS_PRINTERROR		  WM_USER+204
#define IDS_DATACHANGED 	  WM_USER+205
#define IDS_DEFAULTFILEEXT	  WM_USER+206
#define IDS_SAVEASTITLE 	  WM_USER+207
#define IDS_FILEOPENTITLE	  WM_USER+208
#define IDS_STRINGNOTFOUND	  WM_USER+209
#define IDS_SEARCHDLGFAILED	  WM_USER+210
#define IDS_WINDOWSAPPNAME	  WM_USER+211
#define IDS_DEVICENAME		  WM_USER+212
#define IDS_PORTFILE		  WM_USER+213
#define IDS_SEARCHING		  WM_USER+214
#define IDS_FOUND		  WM_USER+215
#define IDS_NOMOREPORTISSUES	  WM_USER+216
#define IDS_INIFILE		  WM_USER+217
#define IDS_WINHELP		  WM_USER+218
#define IDS_NOTYETIMPLEMENTED	  WM_USER+219
#define IDS_NOT 		  WM_USER+220
#define IDS_PORTDLLFILE 	  WM_USER+221
#define IDS_CHECKSTRING 	  WM_USER+222
#define IDS_BKPORTNEWLINE	  WM_USER+223
#define IDS_BKPORTHEADER	  WM_USER+224
#define IDS_BKPORTTOKEN 	  WM_USER+225
#define IDS_BKPORTISSUE 	  WM_USER+226
#define IDS_BKPORTSUGGEST	  WM_USER+227
#define IDS_BKPORTHELP		  WM_USER+228
#define IDS_BKPORTHELPFILE	  WM_USER+229
#define IDS_BKPORTEOL		  WM_USER+230
#define IDS_BKPORTABORT 	  WM_USER+231
#define IDS_BKPORTSTATUS	  WM_USER+232
#define IDS_BKPORTCANCEL	  WM_USER+233
#define IDS_BKPORTSTARTFAILED	  WM_USER+234
#define IDS_CANTBUILDFILELIST	  WM_USER+235
#define IDS_PORTFILEBACKMSG	  WM_USER+236
#define IDS_DEFAULTPORTEXT    WM_USER+237
#define IDS_PORTFILEOPENTITLE    WM_USER+238
#define IDS_UNKNOWN_ERROR         WM_USER+239
#define IDS_ERR_INVALID_THREADHND WM_USER+240
#define IDS_CANCEL_BKGND_PROCESS  WM_USER+241
#define IDS_ABORT_TITLE           WM_USER+242
#define IDS_FILE_FILTER_SPEC1     WM_USER+243
#define IDS_EXT_FILTER_SPEC1      WM_USER+244
#define IDS_FILE_FILTER_SPEC2     WM_USER+245
#define IDS_EXT_FILTER_SPEC2      WM_USER+246
#define IDS_FILE_FILTER_SPEC3     WM_USER+247
#define IDS_EXT_FILTER_SPEC3      WM_USER+248
#define IDS_FILE_FILTER_SPEC4     WM_USER+249
#define IDS_EXT_FILTER_SPEC4      WM_USER+250
#define IDS_FILE_FILTER_SPEC5     WM_USER+251
#define IDS_EXT_FILTER_SPEC5      WM_USER+252

// define background porting handle array indexes
#define BKPORT_ABORT	0
#define BKPORT_STATUS	1
#define nBKPORTEVENTS	2

#define MAXBKTHREADS	20

// define structure used in background porting
typedef struct tagBkPortFile
    {
    char    szFile[MAX_PATH];
    char    szFilePath[MAX_PATH];
    DWORD   dwPTFlags;
    HANDLE  hThread;
    HWND    hDlg;
    }BKPORTFILESTRUCT, * LPBKPORTFILESTRUCT;


// linked list structure defines background files being ported
typedef struct _BKFILELIST
    {
    BKPORTFILESTRUCT	bkFile;
    HANDLE		hEvents[nBKPORTEVENTS];
    LPVOID		Next;
    }BKFILELIST, * LPBKFILELIST;


// function prototypes defined in PORTTOOL.C
#define UM_SAVEFILE		 WM_USER+1
VOID	WINAPI ErrorNotify (HWND, int);
LONG	WINAPI MainWndProc (HWND, UINT, UINT, LONG);
BOOL	WINAPI AboutDlgProc (HWND, UINT, UINT, LONG);

// globals and function prototypes defined in PTFILE.C
extern	char	lpszFilePath[MAX_PATH];
BOOL	WINAPI GetFileName(HWND, char *, char *);
BOOL	WINAPI GetFileFromPath (char *, char *);
BOOL	WINAPI GetIniFile (char *);
int	WINAPI SaveFile (HWND, char *);
BOOL	WINAPI SaveAsFileName (HWND, char *, char *);
int	WINAPI LoadFile (HWND, char *);
BOOL WINAPI GetPortIniFileName ( HWND, char *, char *);

// globals and function prototypes defined in PTFIND.C
extern	char	lpszSearch[MAXSEARCHSTRING+1];
extern	HWND	hDlgSearch;
BOOL	WINAPI FindDialog (HWND, WORD, WORD, char *);
BOOL	WINAPI LocateText (HWND, WORD, WORD, char *);

// globals and function prototypes defined in PTPRINT.C
#define UM_CANCELPRINT		  WM_USER+2
int	WINAPI PrintFile (HWND);
int	WINAPI PrinterSetup (HWND);
BOOL	WINAPI GetPrinterConfig (HWND);

// globals and function prototypes defined in PTDLGS.C
BOOL	WINAPI OptionsDlgProc (HWND, UINT, UINT, LONG);
BOOL	WINAPI PortDlgProc (HWND, UINT, UINT, LONG);
BOOL	WINAPI BkPortDlgProc (HWND, UINT, UINT, LONG);

// globals and function prototypes defined in PTBKPORT.C
#define UM_THREADCOMPLETE	 WM_USER+2
#define UM_STATUSUPDATE 	 WM_USER+3
HANDLE	WINAPI StartBkPortThread (LPBKPORTFILESTRUCT);
BOOL	WINAPI CreateEvents (HANDLE *, LPBKPORTFILESTRUCT);
void	WINAPI DestroyEvents (HANDLE *);

BOOL WINAPI InitPortData(CHAR *);

CHAR                lpszPortIniFilePath[MAX_PATH];
