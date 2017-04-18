/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    CFlash.hpp

Abstract:

   CFlash class declaration

-------------------------------------------------------------------*/

#ifndef CFLASH_HPP
#define CFLASH_HPP

// ++++ Defines +++++++++++++++++++++++++++++++++++++++++++++++++++++
#define MAX_SAVE_FILES		10

// ++++ Classes +++++++++++++++++++++++++++++++++++++++++++++++++++++

class CController;

class CFlash
{

friend class CController;

public:
	HRESULT Save( DWORD in_dwSlot );
    CFlash(GUID FlashGuid, int iConn);
    ~CFlash();

    // Initialize the Flash object
    BOOL Initialize(void);

    // Format the contents of the flash device
    void Format();

    // Dump the contents of the flash device
    void DumpInfo();

    // Copy the contents of the flash device to the specified flash device
    void CopyContentsTo(CFlash *pflashDest);

	// Return the number of the connection that this device is plugged in to.
	int GetConn() {return m_iConn;};

	// Print the filenames of the savegame slots
	void PrintFiles();

	// Verify if the VMU is still there and valid
	BOOL FlashValid();

private:
    // The GUID of the Flash device
    GUID m_guidFlash;

	// File Enum callback
	static BOOL FileEnum(IFlashDevice *pIFlashDeviceSrc, FSFILEID fsfileid, LPCFSFILEDESC lpcfsfiledesc, void *pvContext);

    IFlashDevice  *m_pFlashApi;

	// File names of the 10 savegame slots
	TCHAR m_szFileName[MAX_SAVE_FILES][MAX_FLASH_FILE_NAME];

	int m_iConn;

};    

#endif
