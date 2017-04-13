/**********************************************************************/
/*                                                                    */
/*      MULTCON.H  - Dispatch IME Sub Task                            */
/*                                                                    */
/*      Copyright (c) 1995-1996  Microsoft Corporation                     */
/*                                                                    */
/**********************************************************************/

#define WMCOMMANDWPARAM(w) LOWORD(w)

#define DEFIMC1     0
#define DEFIMC2     1
#define IMC1        2
#define IMC2        3
#define IMCUI1      4
#define IMCUI2      5

#define MAXSIZE_STR             1024

#define WNDEXTRA_NOUINOIMC      8
#define WNDEXTRA_NOUIOWNIMC     12
#define WNDEXTRA_OWNUIOWNIMC    16

#define MYGWL_FONT   0
#define MYGWL_LPSTR  4
#define MYGWL_IMC    8
#define MYGWL_IMEWND 12

extern HANDLE hInst;
extern HWND hWndMain;

extern HWND hWndDef1;
extern HWND hWndDef2;
extern HWND hWndIMC1;
extern HWND hWndIMC2;
extern HWND hWndIMCUI1;
extern HWND hWndIMCUI2;

/* multiui.c */
int  APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
BOOL InitApplication(HANDLE);
BOOL InitInstance(HANDLE, int);
long FAR PASCAL MainWndProc(HWND, UINT, WPARAM, LPARAM);

/* dlgs.c     */
BOOL FAR PASCAL AboutDlg(HWND, UINT, WPARAM, LPARAM);

/* multiwnd.c */
long FAR PASCAL NoUINoIMCWndProc(HWND, UINT, WPARAM, LPARAM);
long FAR PASCAL NoUIOwnIMCWndProc(HWND, UINT, WPARAM, LPARAM);
long FAR PASCAL OwnUIOwnIMCWndProc(HWND, UINT, WPARAM, LPARAM);
HFONT GetDefaultGUIFont(void);
