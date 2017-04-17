/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    VRAMLayout.cpp

Abstract:

    VRAMLayout Application

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include <tchar.h>
#include <windows.h>

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    SetDisplayValue

Description:

    Set the given registry key using the given value.

Arguments:

    LPCWSTR szName           - Name of the registry key to set

    DWORD dwValue            - Value to set the key with

    LPDWORD pdwOldValue      - Contains the old value of the registry key
                               on return

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL
SetDisplayValue(LPCWSTR szName, DWORD dwValue, LPDWORD pdwOldValue)
{
    HKEY  hKey;
    DWORD dwType;
    DWORD dwSize;
    bool  bRet = false;

    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"DisplaySettings", 0, 0, &hKey) == ERROR_SUCCESS)
    {
        if (pdwOldValue)
        {
            DWORD dwOldValue;
            dwSize = sizeof(DWORD);
            if (RegQueryValueEx(hKey, szName, NULL, &dwType, (LPBYTE)&dwOldValue, &dwSize) == ERROR_SUCCESS)
                *pdwOldValue = dwOldValue;
        }

        if (RegSetValueEx(hKey, szName, 0, REG_DWORD, (LPBYTE)&dwValue, sizeof(DWORD)) == ERROR_SUCCESS)
            bRet = true;

        RegCloseKey(hKey);
    }

    return bRet;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    WinMain

Description:

    This is the entrypoint for this sample app.

Arguments:

    hInstance           - HInstance of the process

    hPrev               - HInstance of another process running the program

    LPTSTR lpCmdLine    - Pointer to command line string

    nCmdShow            - Whether the app should be shown (ignored)

Return Value:

    We normally return the wParam value from the WM_QUIT message.  If
    there's a failure upon initialization, we just return 0.

-------------------------------------------------------------------*/
extern "C" int APIENTRY 
WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    DWORD dwVertexBufferSize;
    DWORD dwPolygonBufferSize;

    // Set the size of the Vertex Buffer
    SetDisplayValue(TEXT("CommandVertexBufferSize"), 0x001E0000, &dwVertexBufferSize);

    // Set the size of the Polygon Buffer
    SetDisplayValue(TEXT("CommandPolygonBufferSize"), 0x0030000, &dwPolygonBufferSize);

    OutputDebugString(TEXT("\r\nApp exited...\r\n"));

    return 0;
}
