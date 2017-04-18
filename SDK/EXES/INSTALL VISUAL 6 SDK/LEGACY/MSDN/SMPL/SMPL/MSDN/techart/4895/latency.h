//
//  latency.h
//


// Constants
#define APPNAME				"Latency"

#define IDC_STATIC			-1

#define DLG_VERFIRST        400
#define IDC_COMPANY			DLG_VERFIRST
#define IDC_FILEDESC       	DLG_VERFIRST+1
#define IDC_PRODVER         DLG_VERFIRST+2
#define IDC_COPYRIGHT       DLG_VERFIRST+3
#define IDC_OSVERSION       DLG_VERFIRST+4
#define IDC_TRADEMARK       DLG_VERFIRST+5
#define DLG_VERLAST         DLG_VERFIRST+5
#define IDC_LABEL           DLG_VERLAST+1


// Prototypes
ATOM MyRegisterClass(CONST WNDCLASS*);
BOOL InitApplication(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK About(HWND, UINT, WPARAM, LPARAM);
BOOL CenterWindow (HWND, HWND);
void MyTextOut (HDC, int, int, LPCTSTR);

