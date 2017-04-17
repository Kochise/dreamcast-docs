/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    CFlash.cpp

Abstract:

    Member functions for the CFlash class.

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "SaveGame.hpp"
#include "Icon.hpp"

#define EMPTY _T("Empty")	// String to be displayed in an empty savegame slot 
#define CHAR_NUM 5			// Delimiter character  

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

	// Initialize all VMU Savegame slots to EMPTY
	for ( int i = 0; i < MAX_SAVE_FILES; i++ )
	{
		_tcscpy( m_szFileName[i], EMPTY );
	}

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
	// If we are destroying the VMU being used to save game, notify app
	if ( g_pFlash == this ) 
	{
		g_pFlash = NULL;
		PostMessage( g_hwndApp, WM_INITVMU, 0, 0 );
	}
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

	// Find what files are on this device using FastEnumFlashFiles
	if ( FAILED( m_pFlashApi->FastEnumFlashFiles( CFlash::FileEnum, this ) ) )
	{
        RetailOutput (TEXT("Fast File enumeration failed.  Device not initialized\n"));
		m_pFlashApi->Release();
		m_pFlashApi = NULL;
		return FALSE;
	}


    return TRUE;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CFlash::FileEnum

Description:

    Enumerate all files on the device to find SAVE_X.SAV ( X = 0..9 ).
	Since it results from the call to FastEnumFlashFiles, only fsfileid 
	and lpcfsfiledesc->szFileName is valid.
	Fill the file name table.

Return Value:

    TRUE continue enumerating files, FALSE stops enumeration.
-------------------------------------------------------------------*/
BOOL
CFlash::FileEnum(IFlashDevice *pIFlashDeviceSrc, FSFILEID fsfileid, LPCFSFILEDESC lpcfsfiledesc, void *pvContext)
{
	CFlash *pThis = (CFlash*)pvContext;
	if ( !strncmp( lpcfsfiledesc->szFileName, "SAVE_", CHAR_NUM ) && !strncmp( &lpcfsfiledesc->szFileName[CHAR_NUM+1], ".SAV",4) )
	{
		if ( 
			(lpcfsfiledesc->szFileName[CHAR_NUM] - '0' < 10 ) && 
			(lpcfsfiledesc->szFileName[CHAR_NUM] - '0' >= 0 )
		   )
		{
			mbstowcs( pThis->m_szFileName[lpcfsfiledesc->szFileName[CHAR_NUM] - '0'], lpcfsfiledesc->szFileName, MAX_FLASH_FILE_NAME ); 
		}
	}
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

Note: This is not used in this sample

-------------------------------------------------------------------*/
void
CFlash::Format()
{
    FSDEVICEDESC    devdesc;
    HRESULT         hr;
    int             i;

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

Note: This is not used in this sample

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

Note: This is not used in this sample

-------------------------------------------------------------------*/
void
CFlash::CopyContentsTo(CFlash *pflashDest)
{
    // Enumerate all of the files on the device; copy all of them.
    m_pFlashApi->EnumFlashFiles(EnumFileCopy, pflashDest->m_pFlashApi);
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CFlash::PrintFiles()

Description:

    Print the name of the files on the VMU that matches the pattern ( SAVE_X.SAV )

Arguments:

    None

Return Value:

    None

-------------------------------------------------------------------*/
void
CFlash::PrintFiles()
{
	TCHAR szBuf[MAX_FLASH_FILE_NAME+4];
	
	for ( int i = 0; i < MAX_SAVE_FILES; i++ )
	{
		wsprintf( szBuf, _T("%i: %s\n"),i,m_szFileName[i]);
		RetailOutput(szBuf);
	}
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CFlash::FlashValid()

Description:

    Verify that the VMU is still valid ( not been removed, damaged,... )
	by calling into it. Doing a flush is not intrusive nor damaging.

Arguments:

    None

Return Value:

    None

-------------------------------------------------------------------*/
BOOL
CFlash::FlashValid()
{
	if ( !m_pFlashApi )
		return FALSE;
	
	// Calling into the VMU to validate that it is still there and working
	if ( FAILED( m_pFlashApi->Flush() ))
		return FALSE;
	return TRUE;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CFlash::Save(DWORD in_dwSlot)

Description:

    Save the game into one of the 10 savegame slot.  If the file does not
	exist, create it. If it does, overwrite.  Disable the Reboot on GDRom
	door opening during this operation to avoid data loss.

Arguments:

    DWORD in_dwSlot.  Savegame slot.

Return Value:

    None

-------------------------------------------------------------------*/
HRESULT 
CFlash::Save(DWORD in_dwSlot)
{
	TCHAR			szBuf[MAX_FLASH_FILE_NAME+4];
	char			szBuf2[MAX_FLASH_FILE_NAME+1];
	IFlashFile		*l_pFile;
	HRESULT			l_hr;
    FSFILEDESC		fsfiledesc;

	// Disable reboot if GDRom door opened
	ChangeRebootType( FALSE );

	// Verify if this is an empty slot.
	if ( !_tcscmp( EMPTY, m_szFileName[in_dwSlot] ) )
	{

		memset (&fsfiledesc, 0, sizeof(fsfiledesc));
		fsfiledesc.dwSize = sizeof(fsfiledesc);
		fsfiledesc.dwFlags = FSFD_CREATE_FILE | FSFD_VISDATA;
		fsfiledesc.dwBytesRequired = 3*512;
		strcpy (fsfiledesc.szFileName, "SAVE_0.SAV");
		fsfiledesc.szFileName[CHAR_NUM] = (char)in_dwSlot+'0';
		strcpy (fsfiledesc.szVMSComment, "Sample Savegame");
		strcpy (fsfiledesc.szBootROMComment, "Sample Savegame");
		strcpy (fsfiledesc.szGameName, "SaveGame");
		fsfiledesc.bStatus = FS_STATUS_DATA_FILE;
		fsfiledesc.bCopy = 0;

		fsfiledesc.fsfileicon.bAnimationFrames = 3;
		fsfiledesc.fsfileicon.bAnimationDelay = 10;
		memcpy (&fsfiledesc.fsfileicon.palette, fileiconpalette, 32);
		memcpy (&fsfiledesc.fsfileicon.pixelsFrame1, fileiconpixels, 3 * 512);

		fsfiledesc.fsvisdata.bVisualType = FSVISDATA_TYPE_B;
		memcpy (&fsfiledesc.fsvisdata.typeB.palette, visualiconpalette, 512);
		memcpy (&fsfiledesc.fsvisdata.typeB.pixels, visualiconpixels, 4032);

		// Convert from ANSI to UNICODE
		mbstowcs( m_szFileName[in_dwSlot],fsfiledesc.szFileName,MAX_FLASH_FILE_NAME );

		// Create the file
		if ( FAILED( l_hr = m_pFlashApi->CreateFlashFile( &l_pFile, &fsfiledesc )))
		{
			wsprintf( szBuf, _T("Failed to create  %s, hr = 0x%x\n"),m_szFileName[in_dwSlot],l_hr);
			_tcscpy( m_szFileName[in_dwSlot], EMPTY );
			RetailOutput(szBuf);
			goto CleanupBody;
		}

		// Write Data into the file into one big block.  
		// Another possibility would be to write many small chunks of data.  Since there
		// is caching mechanism, this would be as efficient for total data under 1K.
		// Starting at 1K, it is more efficient to do 1 big write.
		if ( FAILED( l_hr = l_pFile->Write( 0, 3*512, fileiconpixels ) ) )
		{
			wsprintf( szBuf, _T("Failed to write file  %s, hr = 0x%x\n"),m_szFileName[in_dwSlot],l_hr);
			RetailOutput(szBuf);
			l_pFile->Release();
			goto CleanupBody;
		}

		// Since we are release the file right away, there is no need to flush the cache as it
		// will be done by the release.  If we wanted to keep the file pointer, we should flush 
		// the cache to ensure that the data is actually written on the device. 
		// i.e. IFLashFile->Flush()
		l_pFile->Release();
	}
	else
	{
		// convert from UNICODE to ANSI
		wcstombs( szBuf2, m_szFileName[in_dwSlot], MAX_FLASH_FILE_NAME ); 

		// Open the file based on its filename.  This is done to demonstrate the functionality
		// It would be slightly more efficient to remember the fileid and OpenFlashFile( fileid )
		if ( FAILED(l_hr = m_pFlashApi->OpenFlashFileByName( &l_pFile, szBuf2 )))
		{
			wsprintf( szBuf, _T("Failed to open  %s, hr = 0x%x\n"),m_szFileName[in_dwSlot],l_hr);
			RetailOutput(szBuf);
			goto CleanupBody;
		}

		// Write Data into the file into one big block.  
		// Another possibility would be to write many small chunks of data.  Since there
		// is a caching mechanism, this would be as efficient for total data under 1K.
		// Starting at 1K, it is more efficient to do 1 big write.
		if ( FAILED( l_hr = l_pFile->Write( 0, 3*512, fileiconpixels ) ) )
		{
			wsprintf( szBuf, _T("Failed to write file  %s, hr = 0x%x\n"),m_szFileName[in_dwSlot],l_hr);
			RetailOutput(szBuf);
			l_pFile->Release();
			goto CleanupBody;
		}

		// Since we are release the file right away, there is no need to flush the cache as it
		// will be done by the release.  If we wanted to keep the file pointer, we should flush 
		// the cache to ensure that the data is actually written on the device. 
		// i.e. IFLashFile->Flush()
		l_pFile->Release();
	}

CleanupBody:
	// Switch back to reboot on GDRom door opening
	ChangeRebootType( TRUE );

	// Tell the app we are done with the writing so it can reboot if the GDRom door was opened 
	// during writing.  This MUST be done AFTER ChangeRebootType( TRUE ).
    PostMessage(g_hwndApp, WM_FINISHED_WRITING, 0, 0);

	return l_hr;
}
