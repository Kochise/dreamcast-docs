/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    CFlash.cpp

Abstract:

    Member functions for the CFlash class.

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "VMU_Flash.hpp"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CFlash::CFlash

Description:

    Constructor for CFlash Class.

Arguments:

    GUID        guidFlash    - GUID of the Flash device

    int         iConn        - Connection this device is attached to

Return Value:

    None

-------------------------------------------------------------------*/
CFlash::CFlash(GUID guidFlash, int iConn)
{
    m_guidFlash = guidFlash;
    m_pFlashApi = NULL;
    m_iConn = iConn;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CFlash::~CFlash

Description:

    Destructor for CFlash class.

Arguments:

    None

Return Value:

    None

-------------------------------------------------------------------*/
CFlash::~CFlash()
{
    if (m_pFlashApi != NULL)
        m_pFlashApi->Release();
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CFlash::Initialize

Description:

    Initializes the CFlash object.

Arguments:

    None

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL
CFlash::Initialize()
{
    IUnknown *pIUnknown;

    g_errLast = MapleCreateDevice(&m_guidFlash, &pIUnknown);
    if (CheckError(TEXT("Create Maple Device")))
        return FALSE;

    pIUnknown->QueryInterface(_uuidof(IFlashDevice), (PVOID*)&m_pFlashApi);
    pIUnknown->Release();
    if (m_pFlashApi == NULL)
        return FALSE;

    return TRUE;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CFlash::Format

Description:

    Format the contents of the flash device

Arguments:

    None

Return Value:

    None

-------------------------------------------------------------------*/
void
CFlash::Format()
{
    FSDEVICEDESC    devdesc;
    HRESULT         hr;
    int             i;
    BYTE            monoicon[128] = {
                        0xFF,   0xFF,   0xFF,   0xFF,
                        0xFF,   0xFF,   0xFF,   0xFF,
                        0xFF,   0xFF,   0xFF,   0xFF,
                        0xFF,   0xFF,   0xFF,   0xFF,
                        0xF0,   0x00,   0x00,   0x0F,
                        0xF0,   0x00,   0x00,   0x0F,
                        0xF0,   0x00,   0x00,   0x0F,
                        0xF0,   0x00,   0x00,   0x0F,
                        0xF0,   0xFF,   0xFF,   0x0F,
                        0xF0,   0xFF,   0xFF,   0x0F,
                        0xF0,   0xFF,   0xFF,   0x0F,
                        0xF0,   0xFF,   0xFF,   0x0F,
                        0xF0,   0xF0,   0x0F,   0x0F,
                        0xF0,   0xF0,   0x0F,   0x0F,
                        0xF0,   0xF0,   0x0F,   0x0F,
                        0xF0,   0xF0,   0x0F,   0x0F,
                        0xF0,   0xF0,   0x0F,   0x0F,
                        0xF0,   0xF0,   0x0F,   0x0F,
                        0xF0,   0xF0,   0x0F,   0x0F,
                        0xF0,   0xF0,   0x0F,   0x0F,
                        0xF0,   0xFF,   0xFF,   0x0F,
                        0xF0,   0xFF,   0xFF,   0x0F,
                        0xF0,   0xFF,   0xFF,   0x0F,
                        0xF0,   0xFF,   0xFF,   0x0F,
                        0xF0,   0x00,   0x00,   0x0F,
                        0xF0,   0x00,   0x00,   0x0F,
                        0xF0,   0x00,   0x00,   0x0F,
                        0xF0,   0x00,   0x00,   0x0F,
                        0xFF,   0xFF,   0xFF,   0xFF,
                        0xFF,   0xFF,   0xFF,   0xFF,
                        0xFF,   0xFF,   0xFF,   0xFF,
                        0xFF,   0xFF,   0xFF,   0xFF};

    BYTE            coloricon[512] = {
                        0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xAA,0xBB,0xCC,0xDD,0xEE,0xFF,
                        0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xAA,0xBB,0xCC,0xDD,0xEE,0xFF,
                        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                        0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,
                        0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,
                        0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x00,0x00,
                        0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x00,
                        0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0x00,
                        0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,
                        0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,
                        0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,
                        0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,
                        0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,
                        0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0x00,
                        0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x00,
                        0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,
                        0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x00,0x00,
                        0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,
                        0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x0F,0xFF,0xF0,0x00,0x00,0x00,0x00,0x00,
                        0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,
                        0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x0F,0xFF,0xF0,0x00,0x00,0x00,0x00,
                        0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,
                        0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0xFF,0xF0,0x00,0x00,0x00,
                        0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,
                        0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0xFF,0xF0,0x00,0x00,
                        0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,
                        0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0xFF,0xF0,0x00,
                        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                        0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xAA,0xBB,0xCC,0xDD,0xEE,0xFF,
                        0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xAA,0xBB,0xCC,0xDD,0xEE,0xFF};



    if (m_pFlashApi)
    {
        memset (&devdesc, 0, sizeof(devdesc));
        devdesc.dwSize = sizeof(devdesc);
        devdesc.dwFlags = FSDD_COLOR_VMS | FSDD_VOLUME_ICON;
        devdesc.colorVMS = MAKE_FSARGB8(0xff, 0x80, 0x00, 0x80);

        devdesc.fsvolumeicon.fUsePredefinedIcon = FALSE;
        memcpy (devdesc.fsvolumeicon.imagedata.pixelsMonochrome, monoicon, 128);
        devdesc.fsvolumeicon.imagedata.fHasColor = TRUE;

        for (i = 0 ; i < 15 ; i++)
            devdesc.fsvolumeicon.imagedata.palette[i] = MAKE_FSARGB4(0xff, 128 + i*8, 0, 0);
            
        memcpy (devdesc.fsvolumeicon.imagedata.pixelsColor, coloricon, 512);

        hr = m_pFlashApi->DoFormat (&devdesc);
    }
}

#define BYTESINAROW         16
int g_cFiles;

BOOL
EnumFileDump(IFlashDevice *pIFlashDevice, FSFILEID fsfileid, LPCFSFILEDESC lpcfsfiledesc, void *pvContext)
{
    FSFILEDESC   fsfiledesc;
    FSDEVICEDESC fsdevicedesc;
    IFlashFile   *pIFlashFile = NULL;
    BYTE         *pbyFile;
    TCHAR        tszFileName[MAX_FLASH_FILE_NAME];
    TCHAR        tszOutput[100];
    TCHAR        tszOneByte[10];
    int          i, j;
    BYTE         onebyte;
    
    fsdevicedesc.dwSize = sizeof(fsdevicedesc);
    fsdevicedesc.dwFlags = FSDD_ALL;
    g_errLast = pIFlashDevice->GetDeviceDesc (&fsdevicedesc);
    if (CheckError(TEXT("Get Device Description")))
        return FALSE;

    // Open the file on the Flash device
    g_errLast = pIFlashDevice->OpenFlashFile(&pIFlashFile, fsfileid);
    if (CheckError(TEXT("Open Flash File")))
        return FALSE;

    fsfiledesc.dwSize = sizeof(FSFILEDESC);
    fsfiledesc.dwFlags = FSFD_FULL_QUERY;
    g_errLast = pIFlashFile->GetFileDesc (&fsfiledesc);
    if (CheckError(TEXT("Get File Description")))
    {
        pIFlashFile->Release ();
        return FALSE;
    }

    // Allocate space for the file buffer
    pbyFile = (BYTE*) LocalAlloc (LPTR, fsfiledesc.dwTotalBytes);
    if (!pbyFile)
    {
        RetailOutput(TEXT("Failed to allocate memory for file\r\n"));
        pIFlashFile->Release ();
        return FALSE;
    }

    // Read the file from the Flash device
    g_errLast = pIFlashFile->Read (0, fsfiledesc.dwTotalBytes, pbyFile);
    if (CheckError(TEXT("Read file")))
    {
        LocalFree(pbyFile);
        pIFlashFile->Release ();
        return FALSE;
    }

    pIFlashFile->Release ();

    // Get and output the file name from the file description (Convert to 
    // unicode for output)
    for (i = 0; i < MAX_FLASH_FILE_NAME; i++)
        tszFileName[i] = (TCHAR) fsfiledesc.szFileName[i];

    RetailOutput(TEXT("Dumping first six blocks of file %s:\r\n"), tszFileName);

    // Dump the contents of the file to the debugger
    for (i = 0; i < (int) fsfiledesc.dwTotalBytes; i += BYTESINAROW)
    {
        // TODO: Not sure why this is here
        if ((i / fsdevicedesc.dwBlockSize) > 5)
            break;

        if ((i % fsdevicedesc.dwBlockSize) == 0)
            RetailOutput(TEXT("\r\n"));

        wsprintf (tszOutput, TEXT("    0x%08x    "), i);
        RetailOutput(tszOutput);

        _tcscpy (tszOutput, TEXT(""));

        for (j = 0 ; j < BYTESINAROW ; j++)
        {
            onebyte = ((i + j) < (int) fsfiledesc.dwTotalBytes) ? pbyFile[i + j] : 0;
            wsprintf (tszOneByte, TEXT("%02x "), onebyte);
            _tcscat (tszOutput, tszOneByte);
        }

        RetailOutput(tszOutput);
        RetailOutput(TEXT("    "));

        for (j = 0 ; j < BYTESINAROW ; j++)
        {
            onebyte = ((i + j) < (int) fsfiledesc.dwTotalBytes) ? pbyFile[i + j] : 0;
            if ((onebyte >= 32) && (onebyte <= 126))
                tszOutput[j] = (TCHAR) onebyte;
            else
                tszOutput[j] = TEXT('.');
        }

        tszOutput[BYTESINAROW] = TEXT('\0');
        RetailOutput(tszOutput);
        RetailOutput(TEXT("\r\n"));
    }

    RetailOutput(TEXT("\r\n"));
    RetailOutput(TEXT("\r\n"));
        
    // Free the buffer used to store the file
    LocalFree ((HLOCAL) pbyFile);

    g_cFiles++;
    return TRUE;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CFlash::DumpInfo

Description:

    Dump the contents of the flash device

Arguments:

    None

Return Value:

    None

-------------------------------------------------------------------*/
void
CFlash::DumpInfo()
{
    g_cFiles = 0;

    // Enumerate all of the files on the device; dump all of them.
    m_pFlashApi->EnumFlashFiles(EnumFileDump, NULL);

    if (g_cFiles == 0)
        RetailOutput(TEXT("No files in device\r\n"));
}

#define BYTESINAROW         16
BOOL
EnumFileCopy(IFlashDevice *pIFlashDeviceSrc, FSFILEID fsfileid, LPCFSFILEDESC lpcfsfiledesc, void *pvContext)
{
    FSFILEDESC   fsfiledesc;
    IFlashFile   *pIFlashFile = NULL;
    IFlashFile   *pIFlashFileNew = NULL;
    BYTE         *pbyFile;
    TCHAR        tszFileName[MAX_FLASH_FILE_NAME];
    int          i;
    IFlashDevice *pIFlashDeviceDest = (IFlashDevice *)pvContext;

    // Open the file on the Flash device
    g_errLast = pIFlashDeviceSrc->OpenFlashFile(&pIFlashFile, fsfileid);
    if (CheckError(TEXT("Open Flash File")))
        return FALSE;

    fsfiledesc.dwSize = sizeof(FSFILEDESC);
    fsfiledesc.dwFlags = FSFD_FULL_QUERY;
    g_errLast = pIFlashFile->GetFileDesc (&fsfiledesc);
    if (CheckError(TEXT("Get File Description")))
    {
        pIFlashFile->Release ();
        return FALSE;
    }

    // Print out the filename.  Convert to wide characters first.
    for (i = 0; i < MAX_FLASH_FILE_NAME; i++)
        tszFileName[i] = (TCHAR) fsfiledesc.szFileName[i];

    RetailOutput(TEXT("    Found file %s"), tszFileName);

    // Allocate space for the file buffer
    pbyFile = (BYTE*) LocalAlloc (LPTR, fsfiledesc.dwTotalBytes);
    if (!pbyFile)
    {
        RetailOutput(TEXT("Failed to allocate memory for file\r\n"));
        pIFlashFile->Release ();
        return FALSE;
    }

    // Read the file from the Flash device
    g_errLast = pIFlashFile->Read (0, fsfiledesc.dwTotalBytes, pbyFile);
    if (CheckError(TEXT("Read file")))
    {
        LocalFree(pbyFile);
        pIFlashFile->Release ();
        return FALSE;
    }

    if (pIFlashDeviceDest)
    {
        fsfiledesc.dwBytesRequired = fsfiledesc.dwTotalBytes;
        fsfiledesc.dwFlags = FSFD_CREATE_FILE | FSFD_VISDATA;
        g_errLast = pIFlashDeviceDest->CreateFlashFile (&pIFlashFileNew, &fsfiledesc);
        if (CheckError(TEXT("Create new file on device")))
        {
            RetailOutput (TEXT("    Could not create new file on device.\r\n"));
            LocalFree ((HLOCAL) pbyFile);
            pIFlashFile->Release ();
            return FALSE;
        }

        RetailOutput(TEXT("    Writing file to device in connection 1 ...\r\n"));

        g_errLast = pIFlashFileNew->Write (0, fsfiledesc.dwTotalBytes, pbyFile);
        if (CheckError(TEXT("Write file to device")))
        {
            RetailOutput (TEXT("        QueryInterface failed.\r\n"));
            pIFlashFileNew->Release();
            pIFlashFile->Release ();
            LocalFree ((HLOCAL) pbyFile);
            return FALSE;
        }
    }
        
    pIFlashFileNew->Release();
    pIFlashFile->Release ();

    // Free the buffer used to store the file
    LocalFree ((HLOCAL) pbyFile);

    return TRUE;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CFlash::CopyContentsTo

Description:

    Copy the contents of the flash device to the specified flash device

Arguments:

    CFlash *pflashDest      - The Flash device to which we will write 
                              the contents of this flash device

Return Value:

    None

-------------------------------------------------------------------*/
void
CFlash::CopyContentsTo(CFlash *pflashDest)
{
    // Enumerate all of the files on the device; copy all of them.
    m_pFlashApi->EnumFlashFiles(EnumFileCopy, pflashDest->m_pFlashApi);
}
