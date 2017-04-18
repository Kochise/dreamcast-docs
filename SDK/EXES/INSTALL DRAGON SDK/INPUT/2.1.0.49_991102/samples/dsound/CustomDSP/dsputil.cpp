/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    DSPUtil.cpp

Abstract:

    DSP functionality

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "CustomDSP.hpp"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    LoadDSPFiles

Description:

    Loads the specified DSP files

Arguments:

    TCHAR *tszDSPCodeFile       - The DSP Code file name
    
    TCHAR *tszMixerFile         - The DSP mixer file name
    
    PBYTE *ppbFile1             - pointer to where the DSP code is copied 
                                  (This space is allocated by this function!)
    
    DWORD *pcbFile1             - Size of the DSP code file
    
    PBYTE *ppbFile2             - pointer to where the DSP mixer is copied
                                  (This space is allocated by this function!)
    
    DWORD *pcbFile2             - Size of the DSP mixer file
  
Return Value:

    TRUE on success, FALSE on failure

-------------------------------------------------------------------*/
BOOL
LoadDSPFiles(TCHAR *tszDSPCodeFile, TCHAR *tszMixerFile, PBYTE *ppbFile1, DWORD *pcbFile1, PBYTE *ppbFile2, DWORD *pcbFile2)
{
    PBYTE pbFile;
    HANDLE hFile;
    DWORD cbFile, cbRead;

    // Open the DSP Code file
    hFile = CreateFile(tszDSPCodeFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        RetailOutput(TEXT("ERROR: CreateFile on DSP code file (%s) failed\r\n"), tszDSPCodeFile);
        return FALSE;
    }

    cbFile = GetFileSize(hFile, NULL);
    if (cbFile == 0xFFFFFFFF)
    {
        RetailOutput(TEXT("ERROR: GetFileSize failed"));
        CloseHandle(hFile);
        return FALSE;
    }

    // Allocate memory to hold the DSP code file
    pbFile =  (PBYTE )LocalAlloc(LMEM_FIXED, cbFile);
    if (!pbFile)
    {
        RetailOutput(TEXT("ERROR: Out of memory in LoadDSPFiles\r\n"));
        CloseHandle(hFile);
        return FALSE;
    }

    *pcbFile1 = cbFile;
    *ppbFile1 = pbFile;

    // Read the actual DSP code file.
    ReadFile (hFile, pbFile, cbFile, &cbRead, NULL);
    if (cbRead == 0)
    {
        RetailOutput(TEXT("ERROR: Failed to read DSP code file in LoadDSPFiles\r\n"));
        CloseHandle(hFile);
        LocalFree(pbFile);
        return FALSE;
    }
    CloseHandle(hFile);

    // Open the DSP Mixer file
    hFile = CreateFile(tszMixerFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        RetailOutput(TEXT("ERROR:Failed to open Mixed file (%s)\r\n"), tszMixerFile);
        return FALSE;
    }

    cbFile = GetFileSize(hFile, NULL);
    if (cbFile == 0xFFFFFFFF)
    {
        RetailOutput(TEXT("ERROR: GetFileSize failed"));
        CloseHandle(hFile);
        return FALSE;
    }

    pbFile =  (PBYTE )LocalAlloc(LMEM_FIXED, cbFile);
    if (!pbFile)
    {
        RetailOutput(TEXT("ERROR: Out of memory in LoadDSPFiles\r\n"));
        CloseHandle(hFile);
        return FALSE;
    }

    *pcbFile2 = cbFile;
    *ppbFile2 = pbFile;

    // Read the actual DSP code file.
    ReadFile (hFile, pbFile , cbFile , &cbRead, NULL);
    if (cbRead == 0)
    {
        RetailOutput(TEXT("ERROR: Failed to read DSP mixer file in LoadDSPFiles\r\n"));
        CloseHandle(hFile);
        LocalFree(pbFile);
        return FALSE;
    }
    CloseHandle(hFile);

    return TRUE;
}
