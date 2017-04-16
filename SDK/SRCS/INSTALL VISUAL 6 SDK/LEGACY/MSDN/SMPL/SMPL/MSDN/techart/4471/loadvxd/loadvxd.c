/*
    
    LOADVXD, simple Win32 based application to load and unload the
    VDYNDEBD virtual device driver.

    Note:
    VDYNDEBD.VXD must reside either in the directory of the application
    or in the Windows 95 system directory.

*/

#include "windows.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
		LPSTR lpszCmdLine, int nCmdShow)
{
    HANDLE hVxD = 0;
    char   szMsg[255];

    // dynamically load and open our VxD
    hVxD = CreateFile("\\\\.\\VDYNDEBD.VXD", 0, 0, NULL, OPEN_EXISTING,
                      FILE_FLAG_DELETE_ON_CLOSE, 0);

    // check for an error, display error message on error
    if (hVxD == INVALID_HANDLE_VALUE) {
        wsprintf(szMsg, "Unable to open VDYNDEBD.VXD, Error code: %lx\n",
                 GetLastError());
        MessageBox(GetActiveWindow(), szMsg, "LoadVxD", MB_OK | MB_ICONSTOP);
        return 1;
    }

    // display message
    wsprintf(szMsg, "VDYNDEBD.VXD loaded.\n\nIn WDEB386 try the '.vdyndebd' command now."
    "\n\nClick 'OK' to unload the driver.");
    MessageBox(GetActiveWindow(), szMsg, "LoadVxD", MB_OK | MB_ICONINFORMATION);

    // close and dynamically unload our VxD
    CloseHandle(hVxD);
    return 0;
}
