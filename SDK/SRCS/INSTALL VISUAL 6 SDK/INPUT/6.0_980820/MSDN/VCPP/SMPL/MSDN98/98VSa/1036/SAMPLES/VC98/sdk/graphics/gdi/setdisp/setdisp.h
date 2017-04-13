/**************************************************************\
*                                                              * 
*   Header file for SetDisp.c                                 * 
*                                                              *
\**************************************************************/
#define STRICT

#define _INC_OLE
#include <windows.h>
#undef  _INC_OLE


/**************************************************************\
*                                                              * 
*   Misc contants to control app behaviour                     *
*                                                              * 
\**************************************************************/
#define MYWM_NOTIFYICON		(WM_APP+100)
#define VERIFY_RESCHANGE  1

//Milliseconds  -- set to 10 seconds
#define VERIFY_TIMEOUT         10000

#define MAX_MODES              40
#define MIN_FREQUENCY          60
#define MIN_WIDTH              400

/**************************************************************\
*                                                              * 
*   Global to everybody...                                     *
*                                                              * 
\**************************************************************/
HINSTANCE g_hinst       = NULL;

PDEVMODE  gpDevModes    = NULL;
PDEVMODE  gpCurrentMode = NULL;

HANDLE    ghVerifyDlg   = NULL;

INT       gnModes       = -1;
UINT      gnCurrentMode =  0;  //Default to the first until 
                               //we determine which it really is


/**************************************************************\
*                                                              * 
*  Function Prototypes                                         *
*                                                              * 
\**************************************************************/
BOOL CALLBACK SetDispDlgProc (HWND hDlg, UINT uMsg,
                               WPARAM wParam, LPARAM lParam);
 
VOID CALLBACK VerifyTimerProc(HWND hwnd, UINT uMsg, 
                              UINT idEvent,DWORD dwTime);

BOOL CALLBACK VerifyDlgProc (HWND hDlg, UINT uMsg, 
                             WPARAM wParam, LPARAM lParam);

BOOL APIENTRY About (HWND hDlg, UINT message,
                     UINT wParam, LONG lParam);

VOID APIENTRY HandlePopupMenu (HWND   hwnd, POINT point);


BOOL SetResolutionMenu (HWND hwnd);
BOOL ChangeResolution (UINT nNewMode, HWND hwnd);

BOOL GetDevModes (HWND hWnd);

int CompareDevModes (DEVMODE *leftDM, DEVMODE *rightDM);


BOOL TrayMessage (HWND hDlg, DWORD dwMessage, UINT uID,
                  HICON hIcon, PSTR pszTip );

void NotifyAdd (HWND hDlg, UINT uIndex);
void NotifyDelete (HWND hDlg, UINT uIndex);

BOOL IsNT(void);




