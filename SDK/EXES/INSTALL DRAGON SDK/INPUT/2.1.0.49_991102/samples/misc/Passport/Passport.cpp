/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    Passport.cpp

Abstract:

    Passport Application

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "Passport.hpp"

void
DebugDump(void *pvBuffer, DWORD dwLength)
{
    BYTE  *pbyLine;
    BYTE  *pbyCur = (BYTE*)pvBuffer;
    DWORD dwOffset = 0;

    // Dump each of the BYTEs
    while (dwLength-- > 0)
    {
        if ((dwOffset & 0xf) == 0)
        {
            RetailOutput(TEXT("%08x: "), dwOffset);
            pbyLine = (BYTE*)pbyCur;
        }

        RetailOutput(TEXT("%02x "), *pbyCur++);

        if (dwLength == 0) {
            while ((dwOffset & 0xf) != 0xf) {
                RetailOutput(TEXT("   "));
                dwOffset++;
            }
        }

        if ((dwOffset & 0xf) == 0xf)
        {
            while (pbyLine != pbyCur)
            {
                if (*pbyLine >= 0x20 && *pbyLine <= 0x7e)
                    RetailOutput(TEXT("%hc"), *pbyLine);
                else
                    RetailOutput(TEXT("."));

                pbyLine++;
            }
            RetailOutput(TEXT("\r\n"));
        }

        dwOffset++;
    }
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
    NetworkInfo networkinfo; // Passport information data structure
    BYTE  *pbySerialNumber;  // Buffer to hold serial number
    DWORD dwSize = 0;        // Size of the serial number buffer
    DWORD dwType;            // Type of data read from registry
    BOOL  fSuccess;          // Error code
    HKEY  hkeyInfo;          // Registry key info handle
    int   nError;            // Error code
    DWORD cInfoSize;         // Size of the structure passed back by the registry
    int   i;                 // Counter

    // First we need to query for the buffer size necessary to store the
    // serial number; do this by passing a NULL pointer for the buffer.
    FirmwareGetSerialNumber(NULL, &dwSize);

    pbySerialNumber = (LPBYTE)LocalAlloc(LMEM_FIXED, dwSize);
    if (pbySerialNumber == NULL) {
        RetailOutput(TEXT("LocalAlloc failed\r\n"));
        return 1;
    }

    // Now that we have a buffer of the appropriate size, call down again,
    // but this time pass a pointer to that buffer.
    FirmwareGetSerialNumber(pbySerialNumber, &dwSize);

    // Output the User ID as a string of hexadecimal numbers
    RetailOutput(TEXT("User ID: "));
    for (i = 0; i < (int)dwSize; i++)
        RetailOutput(TEXT("%02X"), pbySerialNumber[i]);

    RetailOutput(TEXT("\r\n\r\n"));

    // We no longer need the serial number buffer, so release it
    LocalFree(pbySerialNumber);

    // Load passport info into registry (overwriting the existing one)
    // NOTE: This is not necessary because WinCE automatically does this at
    // system startup time.  It is included here to demonstrate how to reload
    // the registry for applications that modify it at run-time.
    fSuccess = FlashLoadNetworkInfo(NULL, sizeof(NetworkInfo), NULL);
    if (!fSuccess)
    {
        nError = GetLastError();
        if (nError == ERROR_INVALID_DATA)
        {
            RetailOutput(TEXT("\r\nFlashLoadNetworkInfo failed with error 'ERROR_INVALID_DATA',\r\n"));
            RetailOutput(TEXT("most likely because you have not yet written anything in there.\r\n"));
            RetailOutput(TEXT("Please do that first and then rerun this sample.\r\n"));
        }
        else
            RetailOutput(TEXT("FlashLoadNetworkInfo failed with unknown error %d\r\n"), GetLastError());

        return 1;
    }

    // Now that the registry is updated, Open up the Passport info key for reading
    nError = RegOpenKeyEx(HKEY_LOCAL_MACHINE, REG_KEY_NETWORK_INFO, 0, KEY_READ, &hkeyInfo);
    if (nError != ERROR_SUCCESS)
    {
        RetailOutput(TEXT("error: RegOpenKeyEx failed with error code %d\r\n"), nError);
        return 1;
    }

    // The key's open, so now we'll read the Passport info data.
    cInfoSize = sizeof(NetworkInfo);
    nError = RegQueryValueEx(hkeyInfo, REG_VAL_NETWORK_INFO, 0, &dwType, (LPBYTE)&networkinfo, &cInfoSize);
    if (nError != ERROR_SUCCESS)
    {
        RetailOutput(TEXT("no valid passport found\r\n"));
        return 1;
    }

    // We've read the data - verify that it is a valid Passport form
    if (dwType != REG_BINARY || cInfoSize != sizeof(NetworkInfo))
    {
        RetailOutput(TEXT("unknown passport format\r\n"));
        return 1;
    }

    RetailOutput(TEXT("Sega Passport:\r\n"));
    DebugDump(&networkinfo, sizeof(NetworkInfo));

    // We're done with the Passport info key, so close it.
    RegCloseKey(hkeyInfo);

    return 0;
}
