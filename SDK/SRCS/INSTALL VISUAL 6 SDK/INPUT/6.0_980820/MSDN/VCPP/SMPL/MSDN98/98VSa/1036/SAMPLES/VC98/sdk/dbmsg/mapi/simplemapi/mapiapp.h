/* QuickCase:W KNB Version 1.00 */
#include <windows.h>
#include <string.h>
#define IDM_ACCESS                1000
#define IDM_A_LOGON                    1050
#define IDM_A_LOGOFF                   1100
#define IDM_SEND                  2000
#define IDM_S_MAIL                     2050
#define IDM_S_DOCUMENT                 2100
#define IDM_MANIPULATE            3000
#define IDM_M_FINDFIRST           3040
#define IDM_M_FINDNEXT                 3050
#define IDM_M_READ                     3100
#define IDM_M_DELETE                   3150

#define IDS_ERR_REGISTER_CLASS   1
#define IDS_ERR_CREATE_WINDOW    2
#define IDS_FROM                 3 
#define IDS_TO                   4
#define IDS_DATE                 5
#define IDS_SUBJECT              6
#define IDS_MESSAGE              7
#define IDS_RETURNED_ERROR       8
#define IDS_FAILED               9
#define IDS_GOOD_JOB            10
#define IDS_SUCCESS             11
#define IDS_ERR_NO_MEMORY       12
#define IDS_APP_TITLE           13


char szString[128];   /* variable to load resource strings         */

char szAppName[20];   /* class name for the window               */
HINSTANCE hInst;
HWND hWndMain;


LONG FAR PASCAL WndProc(HWND, UINT, WPARAM, LPARAM);
int nCwRegisterClasses(void);
void CwUnRegisterClasses(void);
LPTSTR GetStringRes (int id);