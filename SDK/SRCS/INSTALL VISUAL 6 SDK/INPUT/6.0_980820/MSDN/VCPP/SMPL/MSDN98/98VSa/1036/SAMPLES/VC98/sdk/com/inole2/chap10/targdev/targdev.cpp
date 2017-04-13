/*
 * TARGDEV.CPP
 *
 * Sample target device structure handling functions.  This file
 * is intended to be a small repository of functions that might
 * be useful in development:
 *  TargetDeviceToDC          Creates a DC or IC from a
 *                            DVTARGETDEVICE structure.
 *  TargetDeviceFromPrintDlg  Creates a DVTARGETDEVICE structure
 *                            from PrintDlg information.
 *  TargetDeviceCopy          Makes a binary copy of a DVTARGETDEVICE
 *                            structure.
 *  TargerDeviceCompare       Compares two DVTARGETDEVICE structures
 *                            for equality.
 *
 * Copyright (c)1992-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#define INC_OLE2
#include <windows.h>
#include <ole2.h>
#include <ole2ver.h>
#include <memory.h>
#ifndef WIN32
#include <print.h>
#endif


/*
 * TargetDeviceToDC
 *
 * Purpose:
 *  Given an OLE DVTARGETDEVICE structure, create an hDC for that
 *  device, where that hDC can optionally be an IC only.
 *
 * Parameters:
 *  ptd             DVTARGETDEVICE * describing the device.
 *  fICOnly         BOOL indicating that the caller wants an IC
 *                  not a DC.
 *
 * Return Value:
 *  HDC             Valid DC for the device or NULL.
 */

STDAPI_(HDC) TargetDeviceToDC(DVTARGETDEVICE *ptd, BOOL fICOnly)
    {
    LPDEVNAMES pDevNames;
    LPDEVMODE  pDevMode;
    LPTSTR     pszDriver;
    LPTSTR     pszDevice;
    LPTSTR     pszPort;

    //Screen DC for a NULL device.
    if (NULL==ptd)
        {
        if (fICOnly)
            return CreateIC(TEXT("DISPLAY"), NULL, NULL, NULL);
        else
            return CreateDC(TEXT("DISPLAY"), NULL, NULL, NULL);
        }

    pDevNames=(LPDEVNAMES)ptd; // offset for size field

    pDevMode=(ptd->tdExtDevmodeOffset==0) ? NULL
        : (LPDEVMODE)((LPSTR)ptd+ptd->tdExtDevmodeOffset);

    pszDriver=(LPTSTR)pDevNames+ptd->tdDriverNameOffset;
    pszDevice=(LPTSTR)pDevNames+ptd->tdDeviceNameOffset;
    pszPort  =(LPTSTR)pDevNames+ptd->tdPortNameOffset;

    if (fICOnly)
        return CreateIC(pszDriver, pszDevice, pszPort, pDevMode);
    else
        return CreateDC(pszDriver, pszDevice, pszPort, pDevMode);
    }




/*
 * TargetDeviceFromPrintDlg
 *
 * Purpose:
 *  Creates an OLE DVTARGETDEVICE structure from a PRINTDLG
 *  structure as returned from the common dialog API PrintDlg,
 *  which is commonly used for Printer Setup.
 *
 * Parameters:
 *  pPD             LPPRINTDLG containing device information.
 *
 * Return Value:
 *  DVTARGETDEVICE * pointing to the new structure.  This is
 *  allocated with the task memory allocator and should be
 *  freed with CoTaskMemFree.
 */

STDAPI_(DVTARGETDEVICE *)TargetDeviceFromPrintDlg(LPPRINTDLG pPD)
    {
    DVTARGETDEVICE  *ptd=NULL;
    LPDEVNAMES       pDevNames, pDN;
    LPDEVMODE        pDevMode, pDM;
    UINT             nMaxOffset;
    LPTSTR           pszName;
    DWORD            dwDevNamesSize, dwDevModeSize, dwPtdSize;

    pDN=(LPDEVNAMES)GlobalLock(pPD->hDevNames);

    if (NULL==pDN)
        return NULL;

    pDM=(LPDEVMODE)GlobalLock(pPD->hDevMode);

    if (NULL==pDM)
        {
        GlobalUnlock(pPD->hDevNames);
        return NULL;
        }

    nMaxOffset=(pDN->wDriverOffset > pDN->wDeviceOffset)
        ? pDN->wDriverOffset : pDN->wDeviceOffset ;

    nMaxOffset=(pDN->wOutputOffset > nMaxOffset)
        ? pDN->wOutputOffset : nMaxOffset ;

    pszName=(LPTSTR)pDN+nMaxOffset;

    dwDevNamesSize=(DWORD)(nMaxOffset+lstrlen(pszName)+1);
    dwDevModeSize=(DWORD) (pDM->dmSize+pDM->dmDriverExtra);

    dwPtdSize=sizeof(DWORD)+dwDevNamesSize+dwDevModeSize;

    ptd=(DVTARGETDEVICE *)CoTaskMemAlloc(dwPtdSize);

    if (NULL!=ptd)
        {
       	ptd->tdSize=(UINT)dwPtdSize;

       	pDevNames=(LPDEVNAMES) &ptd->tdDriverNameOffset;
       #ifdef WIN32
        memcpy(pDevNames, pDN, (size_t)dwDevNamesSize);
       #else
       	_fmemcpy(pDevNames, pDN, (size_t)dwDevNamesSize);
       #endif

       	pDevMode=(LPDEVMODE)((LPTSTR)&ptd->tdDriverNameOffset
            + dwDevNamesSize);
       #ifdef WIN32
       	memcpy(pDevMode, pDM, (size_t)dwDevModeSize);
       #else
        _fmemcpy(pDevMode, pDM, (size_t)dwDevModeSize);
       #endif

        ptd->tdDriverNameOffset +=4 ;
        ptd->tdDeviceNameOffset +=4 ;
        ptd->tdPortNameOffset   +=4 ;
        ptd->tdExtDevmodeOffset=(UINT)dwDevNamesSize+4 ;
        }

    GlobalUnlock(pPD->hDevNames);
    GlobalUnlock(pPD->hDevMode);
    return ptd;
    }





/*
 * TargetDeviceCopy
 *
 * Purpose:
 *  Duplicate a DVTARGETDEVICE structure, allocating new memory
 *  for the copy which the caller must free with CoTaskMemFree.
 *
 * Parameters:
 *  ptdSrc          DVTARGETDEVICE * to copy
 *
 * Return Value:
 *  DVTARGETDEVICE * to the copy, NULL if copy fails or ptdSrc
 *                  is NULL.
 */

STDAPI_(DVTARGETDEVICE *) TargetDeviceCopy(DVTARGETDEVICE * ptdSrc)
    {
    DVTARGETDEVICE * ptdDest=NULL;

    if (NULL==ptdSrc)
	    return NULL;

    ptdDest=(DVTARGETDEVICE *)CoTaskMemAlloc(ptdSrc->tdSize);

    if (NULL!=ptdDest)
       #ifdef WIN32
        memcpy(ptdDest, ptdSrc, (size_t)ptdSrc->tdSize);
       #else
        _fmemcpy(ptdDest, ptdSrc, (size_t)ptdSrc->tdSize);
       #endif

    return ptdDest;
    }





/*
 * TargetDeviceCompare
 *
 * Purpose:
 *  Checks if two DVTARGETDEVICE structures are equivalent.
 *
 * Parameters:
 *  ptdLeft         DVTARGETDEVICE to one structure.
 *  ptdRight        DVTARGETDEVICE to another structure.
 *
 * Return Value:
 *  BOOL            TRUE if the structures are equivalent,
 *                  FALSE otherwise.
 */

STDAPI_(BOOL) TargetDeviceCompare(DVTARGETDEVICE *ptdLeft
    , DVTARGETDEVICE * ptdRight)
    {
    //Same address, same devices
    if (ptdLeft==ptdRight)
        return TRUE;

    //Either is NULL but not the other, not equal
    if (NULL==ptdLeft || NULL==ptdRight)
        return FALSE;

    //Different sizes, not equal
    if (ptdLeft->tdSize!=ptdRight->tdSize)
        return FALSE;

    //Fo a binary compare
   #ifdef WIN32
    if (0!=memcmp(ptdLeft, ptdRight, ptdLeft->tdSize))
   #else
    if (0!=_fmemcmp(ptdLeft, ptdRight, (int)ptdLeft->tdSize))
   #endif
    return FALSE;

    return TRUE;
    }
