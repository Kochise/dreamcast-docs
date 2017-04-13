//*---------------------------------------------------------------------------------
//|  ODBC System Administrator
//|
//|  This code is furnished on an as-is basis as part of the ODBC SDK and is
//|  intended for example purposes only.
//|
//*---------------------------------------------------------------------------------
#ifndef satool_DEFS
#define satool_DEFS

#include <windows.h>
#include <windowsx.h>
#include <string.h>
#include <commdlg.h>
#include "child.h"
#include "menu.h"
#include "standard.h"
#include "errcheck.h"
#include "results.h"
#include "execute.h"
#include "info.h"
#include "ctl3d.h"


//------------------------------------------------------------------------
//  Defines
//------------------------------------------------------------------------
typedef  void FAR * lpVOID;
typedef BOOL (FAR PASCAL *FPROC)(void FAR * parm);

#define  TABLES            1
#define  PROCS             2

#define  IDD_ABOUTBOX      2000

#define USER_INITAPP       (WM_USER + 100)
#define USER_RESETHANDLE   (WM_USER + 101)

#define  IDB_ABOUTOK       200
#define  IDBIT_PICT        201

#define  CONNECTION_WINDOW    1
#define  RESULTS_WINDOW       2

#define  DISCONNECTED      0
#define  CONNECTED         1


#define VSZFile static char vszFile[]=__FILE__;

#define GetText(h,s)                                                    \
   {                                                                    \
   SendMessage(h, WM_GETTEXT,                                           \
               (WORD)SendMessage(h, WM_GETTEXTLENGTH, 0, 0L) + 1,       \
               (LPARAM)(LPSTR)s);                                       \
   }
#define IsRadioButtonOn(hwnd) SendMessage(hwnd, BM_GETCHECK, 0, 0L)

extern dCSEG(char) szOPENFILE[];



//------------------------------------------------------------------------
//  Declare function prototypes
//------------------------------------------------------------------------
void Busy(int flag);
LPSTR iLoadString(int id, LPSTR str, int len);
void FAR PASCAL CenterDialog(HWND hdlg);
HWND INTFUN GetEditWindow(CHILDINFO FAR * ci);



#endif
