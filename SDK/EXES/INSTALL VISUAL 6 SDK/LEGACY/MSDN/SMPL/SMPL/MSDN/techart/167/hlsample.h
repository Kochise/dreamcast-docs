#include <windows.h>
#include <windowsx.h>

// Public declarations

int PASCAL WinMain(HINSTANCE hinst, HINSTANCE hinstPrev, LPSTR lpszCmdLine, int cmdShow);
LRESULT CALLBACK MainWnd_WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK AboutDlg_DlgProc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam);

// Public globals
extern HINSTANCE _hInstance;
extern HINSTANCE _hPrevInstance;
extern int _cmdShow;
extern HWND g_hwndMain;


// Internal Functions
VOID AboutDlg_Do(HWND hwndOwner);
VOID MainWnd_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT code);
VOID MainWnd_OnClose(HWND hwnd);
int  HLDialog_Do(HWND hwndOwner);
VOID HLSystemColorChange(VOID);



// Menu

#define IDR_MAINMENU            1

// File menu

#define CMD_DIALOG              100
#define CMD_FILEEXIT            130

//
// Help Menu
//
#define CMD_HELPABOUT           901


// Bitmap resource IDs
#define IDR_LISTICONS           999

// Icon resource IDs

#define IDR_MAINICON            100

// AboutDlg definitions

#define IDR_ABOUTDLG            200

// Sample Dialog definitions
#define IDHEIRDLG                   100
#define IDLIST                      101
