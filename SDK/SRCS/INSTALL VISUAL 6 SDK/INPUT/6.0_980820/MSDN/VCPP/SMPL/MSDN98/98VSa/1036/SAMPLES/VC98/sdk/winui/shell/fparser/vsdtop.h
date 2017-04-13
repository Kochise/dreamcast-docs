#ifdef WIN32
#define WINDOWS
#endif

#ifdef _WINDOWS /* MS C 7.0 predefined */
#ifndef WIN32
#define WINDOWS
#define WIN16
#endif
#endif

#ifdef WINDOWS
#pragma message("Windows")
#endif

#ifdef WIN16
#pragma message("Win16")
#endif

#ifdef WIN32
#pragma message("Win32")
#endif

	/*
	|	 Include windows and scc definitions
	*/

#include "entry.h"
#include <stdlib.h>
#include <windows.h>

typedef signed char  *	LPCHAR;
typedef signed short  *	LPSHORT;

typedef DWORD HIOFILE;

/*
|
|   Typedef for FI information and get structure
|
*/

typedef struct FIINFOtag
   {
   WORD      fiId;			/* FI Id */
   WORD      fiFlags;		    /* flags for the Id */
   BYTE      fiName[26];	    /* name of the Id, for example "WordPerfect 5.0" */
   } FIINFO;

typedef struct FIGETSTRUCTtag
   {
   HANDLE   gsRes;
   WORD     gsIndex;
   } FIGETSTRUCT;



__declspec(dllexport) WORD __cdecl FIIdFile(DWORD,LPSTR,DWORD,WORD  *);
__declspec(dllexport) WORD __cdecl FIIdHandle(HIOFILE,WORD  *);
__declspec(dllexport) void __cdecl FIGetFirstId(FIGETSTRUCT  *, FIINFO  *);
__declspec(dllexport) void __cdecl FIGetNextId(FIGETSTRUCT  *, FIINFO  *);



#include "sodefs.h"




typedef void  * HPROC;

typedef struct fdesc
	{
	SHORT	 FilterId;
	CHAR	 FilterType;
	CHAR	 FileDescription[40];
	} FILTER_DESC;

typedef struct VWINFOtag
	{
	DWORD	 VwCheck;
	WORD	 VwSaveSize;
	WORD	 VwDynamicSize;
	WORD	 VwStaticSize;
	WORD	 VwSpecLevel;
	WORD	 VwFilterLevel;
	WORD	 VwIdCount;
	WORD	 VwIds[15];
	BYTE	 VwDate[12];
	BYTE	 VwTime[10];
	WORD	 VwUserSaveSize;
	} VWINFO;


typedef struct VWRTNStag
	{
	SHORT	 (__cdecl * StreamOpen)(SOFILE, SHORT, BYTE  *, SOFILTERINFO  * ,HPROC);
	SHORT	 (__cdecl * StreamSection)(SOFILE,HPROC);
	SHORT	 (__cdecl * StreamRead)(SOFILE, HPROC);
	SHORT	 (__cdecl * StreamTell)(SOFILE, HPROC);
	SHORT	 (__cdecl * StreamSeek)(SOFILE, HPROC);
	BOOL	 (__cdecl * GetInfo)(void  *, WORD, HPROC);
	void	 (__cdecl * GetData)(void  *, HPROC);
	void	 (__cdecl * SetData)(void  *, HPROC);
	void	 (__cdecl * LocalUp)(HIOFILE, SOFILE  *, HPROC);
	void	 (__cdecl * LocalDown)(SOFILE, HIOFILE  *, HPROC);
	HPROC	 (__cdecl * AllocProc)(void);
	void	 (__cdecl * FreeProc)(HPROC);
	void	 (__cdecl * SetUser)(DWORD,DWORD,HPROC);
	void	 (__cdecl * SetSoRtn)(SHORT, void (__cdecl *)(), HPROC);
	void	 (__cdecl * StreamClose)(SOFILE, HPROC);
	void	 (__cdecl * GetSectionData)(void  *, HPROC);
	void	 (__cdecl * SetSectionData)(void  *, HPROC);
	void	 (__cdecl * StreamReadRecord)(SOFILE, DWORD, HPROC);
	void	 (__cdecl * DoSpecial)(SOFILE, DWORD, DWORD, DWORD, DWORD, DWORD, HPROC);
	} VWRTNS;

