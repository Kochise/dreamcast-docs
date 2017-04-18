/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    CFlash.hpp

Abstract:

   CFlash class declaration

-------------------------------------------------------------------*/

// ++++ Classes +++++++++++++++++++++++++++++++++++++++++++++++++++++

class CController;

class CFlash
{
public:
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
	int GetConn() {return m_iConn;}

private:
    // The GUID of the Flash device
    GUID m_guidFlash;

    IFlashDevice  *m_pFlashApi;

	int m_iConn;
};    

