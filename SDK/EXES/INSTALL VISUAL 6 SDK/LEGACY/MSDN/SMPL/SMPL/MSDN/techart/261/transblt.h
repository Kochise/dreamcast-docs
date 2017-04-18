#define IDM_ABOUT 100

#define IDM_MASK1	200
#define IDM_MASK2	201
#define IDM_MASK3	202

#define IDM_BLACK	300
#define IDM_RED		301
#define IDM_DRED	302
#define IDM_GREEN	303
#define IDM_CYAN	304

int PASCAL WinMain(HANDLE, HANDLE, LPSTR, int);
BOOL InitApplication(HANDLE);
BOOL InitInstance(HANDLE, int);
long FAR PASCAL MainWndProc(HWND, unsigned, WORD, LONG);
BOOL FAR PASCAL About(HWND, unsigned, WORD, LONG);
