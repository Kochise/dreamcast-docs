int WINAPI ClientWndProc   (HWND, UINT, DWORD, LONG);
HWND CreateMDI(HANDLE, char *, char *);
int ChangeIcon(HANDLE, int);
BOOL CALLBACK EnumCloseGhosts(HWND, LPARAM);
BOOL CALLBACK EnumClearBuffers(HWND, LPARAM);
