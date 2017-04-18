/* QuickCase:W KNB Version 1.00 */
#include <windows.h>
#include <windowsx.h>

#define IDM_CLOSE                 100

#define IDM_OWNEDEXAMPLE          1000
#define IDM_CREATEORAMA           2000

#define ERR_REGISTER_CLASS   1
#define ERR_CREATE_WINDOW    2

char szString[128];   /* variable to load resource strings         */
char szAppName[20];   /* class name for the window               */

typedef struct _TLWnd {
    HWND hWnd;
    char szName[32];
    struct _TLWnd FAR *lpTLWndNext;
} TLWnd;

int nTLWnds = 0;
TLWnd FAR *lpTLWndList = NULL;

#define LASTNAME 20

/* Macro to get a random integer within a specified range */
#define getrandom( min, max ) ((rand() % (int)(((max)+1) - (min))) + (min))

HINSTANCE hInst;
HWND hWndMain;
HWND hWndCurrent;
HMENU hMenu;

void cwCenter(HWND, int);

LRESULT FAR PASCAL WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT FAR PASCAL CREATEMsgProc(HWND, WORD, WPARAM, LPARAM);
LRESULT FAR PASCAL SubWndProc(HWND, WORD, WPARAM, LPARAM);

void SetDefaults(HWND);
void UpdateDlgDisplay(HWND);
void AddTLWnd(char *, HWND);
HWND FindTLWndByName(char *);
void FindTLWndByHWnd(HWND, char *);
void RemoveTLWnd(HWND);

int nCwRegisterClasses(void);
void CwUnRegisterClasses(void);
