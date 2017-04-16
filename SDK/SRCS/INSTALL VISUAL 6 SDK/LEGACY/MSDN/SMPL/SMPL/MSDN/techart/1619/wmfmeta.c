/***********************************************************************

  MODULE     : WMFMETA.C

  FUNCTIONS  : MetaEnumProc
               GetMetaFileAndEnum
               LoadParameterLB
               PlayMetaFileToDest
               RenderClipMeta
               RenderPlaceableMeta
               SetPlaceableExts
               SetClipMetaExts
               ProcessFile

  COMMENTS   :

************************************************************************/

#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <string.h>
#include "mfdcod32.h"

/***********************************************************************

  FUNCTION   : MetaEnumProc

  PARAMETERS : HDC           hDC
               LPHANDLETABLE lpHTable
               LPMETARECORD  lpMFR
               int           nObj
               LPARAM        lpClientData


  PURPOSE    : callback for EnumMetaFile.  
  
  CALLS      : EnumMFIndirect()
  
  MESSAGES   : none

  RETURNS    : int

  COMMENTS   : 
  
  HISTORY    : 1/16/91 - created - drc
               5/6/93  - modified for Win32 - denniscr

************************************************************************/

int CALLBACK MetaEnumProc(hDC, lpHTable, lpMFR, nObj, lpClientData)
HDC           hDC;
LPHANDLETABLE lpHTable;
LPMETARECORD  lpMFR;
int           nObj;
LPARAM        lpClientData;

{
  return EnumMFIndirect(hDC, lpHTable, lpMFR, NULL, nObj, lpClientData);
}

/***********************************************************************

  FUNCTION   : GetMetaFileAndEnum

  PARAMETERS : HDC hDC

  PURPOSE    : load the metafile if it has not already been loaded and
               begin enumerating it

  CALLS      : WINDOWS
                 GetMetaFile
                 MakeProcInstance
                 EnumMetaFile
                 FreeProcInstance
                 DeleteMetaFile
                 MessageBox

  MESSAGES   : none

  RETURNS    : void

  COMMENTS   :

  HISTORY    : 1/16/91 - created - drc
               7/1/93 - modified to work with EMFs - denniscr

************************************************************************/

void GetMetaFileAndEnum(hDC, iAction)
HDC hDC;
int iAction;
{
   iEnumAction = iAction;
   //
   //if this is an enhanced metafile (emf)
   //
   if (bEnhMeta)
   {
	 RECT rc;

     if (hemf)
	 {
       LPLOGPALETTE lpLogPal;
   	   HPALETTE hPal;
	   int i;
	   //
	   //allocate memory for the logical palette including the array of
	   //palette entries
	   //
       lpLogPal = (LPLOGPALETTE) GlobalAllocPtr( GHND,  sizeof(LOGPALETTE) + 
                                               (sizeof (PALETTEENTRY) * EmfPtr.palNumEntries));
	   if (lpLogPal)
	   {
	     GetClientRect(hWndMain, &rc);
	     //
	     //proceed only if there is a valid ptr to logical palette
	     //and a palette array obtained from the emf
	     //
	     if (EmfPtr.lpPal)
	     {
		   lpLogPal->palVersion = 0x300;
		   lpLogPal->palNumEntries = EmfPtr.palNumEntries;
		   //
		   //copy palette entries into palentry array
		   //
		   for (i = 0; i < EmfPtr.palNumEntries; i++)
		     lpLogPal->palPalEntry[i] = *EmfPtr.lpPal++;
		   //
		   //reposition the ptr back to the beginning should we call this
		   //code again
		   //
		   EmfPtr.lpPal -= EmfPtr.palNumEntries;
		   //
		   //create, select and realize the palette
		   //
	       if ((hPal = CreatePalette((LPLOGPALETTE)lpLogPal)))
	       {
	         SelectPalette(hDC, hPal, FALSE);
		     RealizePalette(hDC);
		   }
	     } 
	     //
	     //enumerate the EMF.  this is a bit odd simply because PlayEnhMetaFile
	     //really obviates the need for doing this (this cannot be said for WMFs). 
	     //this app does it simply because it may be stepping the metafile records.  
	     //Most apps are generally not concerned about doing this.
	     //
	     EnumEnhMetaFile(hDC, hemf, (ENHMFENUMPROC)EnhMetaFileEnumProc, NULL, &rc);
	     //
	     //free palette memory
	     //
	     GlobalFreePtr(lpLogPal);
	   }
	 }
   }
   else
   {
     //
     //if there is a valid handle to a metafile begin enumerating it 
     //
     if (hMF) 
       EnumMetaFile(hDC, hMF, MetaEnumProc, (LPARAM) 0);
     else
       MessageBox(hWndMain, "Invalid metafile handle",
                  NULL, MB_OK | MB_ICONHAND);
   }
   return;
}

/***********************************************************************

  FUNCTION   : LoadParameterLB

  PARAMETERS : HWND  hDlg
	       DWORD dwParams
	       int   nRadix - HEX to display contents in base 16
			      DEC to display contents in base 10

  PURPOSE    : display the parameters of the metafile record in
	       the parameter listbox

  CALLS      : WINDOWS
		 GlobalLock
		 GlobalUnlock
		 SendDlgItemMessage
		 wsprintf
		 lstrlen

  MESSAGES   : WM_SETREDRAW
	       WM_RESETCONTENT
	       LB_ADDSTRING

  RETURNS    : BOOL

  COMMENTS   :

  HISTORY    : 1/16/91 - created - drc

************************************************************************/

BOOL LoadParameterLB(hDlg, dwParams, nRadix)
HWND         hDlg;
DWORD        dwParams;
int          nRadix;
{
  DWORD i;
  BYTE nHiByte, nLoByte;
  WORD wHiWord, wLoWord;
  char szBuffer[40];
  char szDump[100];
  int  iValue = 0;
  DWORD dwValue = 0;

  switch (nRadix)  /* if nRadix is not a valid value, return FALSE */
  {
    case IDB_HEX:
    case IDB_DEC:
    case IDB_CHAR:
        break;

    default :
        return FALSE;
  }
  //
  //init the strings 
  //
  *szBuffer = '\0';
  *szDump = '\0';
  //
  //turn off redrawing of the listbox 
  //
  SendDlgItemMessage(hDlg, IDL_PARAMETERS, WM_SETREDRAW, FALSE, 0L);
  //
  //reset the contents of the listbox 
  //
  SendDlgItemMessage(hDlg, IDL_PARAMETERS, LB_RESETCONTENT, 0, 0L);

  if (bEnhMeta)
  {
	//
    //lock the memory where the parameters can be found 
	//
    if (NULL == (lpEMFParams = (LPEMFPARAMETERS)GlobalLock(hMem)))
      return (FALSE);
	//
    //loop through the metafile record parameters 
	//
    for (i = 0; i < dwParams; i++)        
    {

      /* get the high and low byte of the parameter word */
      wHiWord = HIWORD(lpEMFParams[i]);
      wLoWord = LOWORD(lpEMFParams[i]);

      switch (nRadix)
      {
        case IDB_HEX: /* if we are to display as hexadecimal */
           /* format the bytes for the hex part of dump */
           wsprintf((LPSTR)szBuffer, (LPSTR)"%08x ", lpEMFParams[i]);
           break;

        case IDB_DEC:
           /* format the bytes for the decimal part of dump */
           dwValue = lpEMFParams[i];
           wsprintf((LPSTR)szBuffer, (LPSTR)"%lu ", dwValue );
           break;

        case IDB_CHAR:
           wsprintf((LPSTR)szBuffer, (LPSTR)"%lc%lc",
                    (wLoWord > 0x20) ? wLoWord : 0x2E,
                    (wHiWord > 0x20) ? wHiWord : 0x2E);
           break;

        default :
          return FALSE;
      }


      /* concatenate it onto whatever we have already formatted */
      lstrcat((LPSTR)szDump, (LPSTR)szBuffer);

      /* use every 8 words for hex/dec dump */
      if (!((i + 1) % 4)) 
      {

        /*add the string to the listbox */
        SendDlgItemMessage(hDlg, IDL_PARAMETERS, LB_ADDSTRING, 0, (LONG)(LPSTR)szDump);

        /* re-init the hex/dec strings in preparation for next 8 words */
        *szDump = '\0';
      }
    }


  }
  else
  {
    /* lock the memory where the parameters can be found */
    if (NULL == (lpMFParams = (LPPARAMETERS)GlobalLock(hMem)))
      return (FALSE);

    /* loop through the metafile record parameters */
    for (i = 0; i < dwParams; i++)        
    {

      /* get the high and low byte of the parameter word */
      nHiByte = HIBYTE(lpMFParams[i]);
      nLoByte = LOBYTE(lpMFParams[i]);

      switch (nRadix)
      {
        case IDB_HEX: /* if we are to display as hexadecimal */
           /* format the bytes for the hex part of dump */
           wsprintf((LPSTR)szBuffer, (LPSTR)"%02x %02x ", nLoByte, nHiByte);
           break;

        case IDB_DEC:
           /* format the bytes for the decimal part of dump */
           iValue = lpMFParams[i];
           wsprintf((LPSTR)szBuffer, (LPSTR)"%d ", iValue );
           break;

        case IDB_CHAR:
           wsprintf((LPSTR)szBuffer, (LPSTR)"%c%c",
                    (nLoByte > 0x20) ? nLoByte : 0x2E,
                    (nHiByte > 0x20) ? nHiByte : 0x2E);
           break;

        default :
          return FALSE;
      }


      /* concatenate it onto whatever we have already formatted */
      lstrcat((LPSTR)szDump, (LPSTR)szBuffer);

      /* use every 8 words for hex/dec dump */
      if (!((i + 1) % 8)) 
      {

        /*add the string to the listbox */
        SendDlgItemMessage(hDlg, IDL_PARAMETERS, LB_ADDSTRING, 0, (LONG)(LPSTR)szDump);

        /* re-init the hex/dec strings in preparation for next 8 words */
        *szDump = '\0';
      }
    }
  } //else
  //
  //dump any leftover hex/dec dump 
  //
  if (lstrlen((LPSTR)szDump))
    SendDlgItemMessage(hDlg, IDL_PARAMETERS, LB_ADDSTRING, 0, (LONG)(LPSTR)szDump);
  //
  //enable redraw to the listbox 
  //
  SendDlgItemMessage(hDlg, IDL_PARAMETERS, WM_SETREDRAW, TRUE, 0L);
  //
  //redraw it 
  //
  InvalidateRect(GetDlgItem(hDlg,IDL_PARAMETERS), NULL, TRUE);
  //
  //unlock the memory used for the parameters 
  //
  GlobalUnlock(hMem);

  return (TRUE);

}

/***********************************************************************

  FUNCTION   : PlayMetaFileToDest

  PARAMETERS : HWND hWnd
               int  nDest - DC to play metafile to
                 DESTDISPLAY - play to the display
                 DESTMETA    - play into another metafile

  PURPOSE    : begin the enumeration of the metafile to the user selected
               destination.  Perform the housekeeping needs appropriate
               to that destination.

  CALLS      : WINDOWS
                 GetClientRect
                 InvalidateRect
                 GetDC
                 SetMapMode
                 OpenFileDialog
                 MessageBox
                 CreateMetaFile
                 DeleteMetaFile
                 CloseMetaFile

               APP
                 WaitCursor
                 SetClipMetaExts
                 SetPlaceableExts
                 GetMetaFileAndEnum

  MESSAGES   : none

  RETURNS    : int

  COMMENTS   :

  HISTORY    : 1/16/91 - created - drc

************************************************************************/

BOOL PlayMetaFileToDest(hWnd, nDest)
HWND hWnd;
int  nDest;
{
  HDC hDC;
  RECT rect;
  int iSaveRet;
  //
  //if the file opened contained a valid metafile 
  //
  if (bValidFile) 
  {
	//
    //init the record count 
	//
    iRecNum = 0;
	//
    //if we are stepping the metafile then clear the client area 
	//
    if (!bPlayItAll) 
    {
      GetClientRect(hWnd, (LPRECT)&rect);
      InvalidateRect(hWnd, (LPRECT)&rect, TRUE);
    }


    switch (nDest) 
    {
	  //
      //playing metafile to the display 
	  //
	  case DESTDISPLAY:
        WaitCursor(TRUE);
	    hDC = GetDC(hWnd);
		//
        //metafile read in from a clipboard file 
		//
	    if ( bMetaInRam && !bAldusMeta && !bEnhMeta)
	      SetClipMetaExts(hDC, lpMFP, lpOldMFP, WMFDISPLAY);
		//
        //Windows placeable metafile 
		//
        if (bAldusMeta && !bEnhMeta)
            SetPlaceableExts(hDC, aldusMFHeader, WMFDISPLAY);
		//
        //Windows metafile 
		//
        if (!bMetaInRam && !bEnhMeta)
          SetMapMode(hDC, MM_TEXT);
		//
        //begin the enumeration of the metafile 
		//
        GetMetaFileAndEnum(hDC, ENUMMFSTEP);

	    ReleaseDC(hWnd, hDC);
        WaitCursor(FALSE);
	    break;

	case DESTMETA:
		//
        //get a name of a file to play the metafile into 
		//
	    iSaveRet = SaveFileDialog((LPSTR)SaveName, (LPSTR)gszSaveEMFFilter);
		//
        //if the file selected is this metafile then warn user 
		//
        if (!lstrcmp((LPSTR)OpenName, (LPSTR)SaveName))
          MessageBox(hWnd, (LPSTR)"Cannot overwrite the opened metafile!",
                           (LPSTR)"Play to Metafile", MB_OK | MB_ICONEXCLAMATION);

        else
		  //
          //the user didn't hit the cancel button 
		  //
	      if (iSaveRet) 
	      {
            WaitCursor(TRUE);
			//
            //create a disk based metafile 
			//
	        hDC = (bEnhMeta) ? CreateEnhMetaFile(NULL, (LPSTR)SaveName, NULL, NULL)
	                         : CreateMetaFile((LPSTR)SaveName);
			//
            //begin the enumeration of the metafile 
			//
            GetMetaFileAndEnum(hDC, ENUMMFSTEP);
			//
            //done playing so close the metafile and delete the handle 
			//
			if (bEnhMeta)
			  DeleteEnhMetaFile(CloseEnhMetaFile(hDC));
			else
  	          DeleteMetaFile(CloseMetaFile(hDC));

            WaitCursor(FALSE);
          }

	    break;

	default:
	    break;
    }
	//
    //if playing list records then free the memory used for the list of
    //selected records 
	//
    if (bPlayList) 
    {
      GlobalUnlock(hSelMem);
      GlobalFree(hSelMem);
      bPlayList = FALSE;
    }
	//
	//success 
	//
    return (TRUE);
  }
  else
    //
    //not a valid metafile 
	//
    return (FALSE);
}

/***********************************************************************

  FUNCTION   : RenderClipMeta

  PARAMETERS : CLIPFILEFORMAT	*ClipHeader
               int	        fh

  PURPOSE    : read metafile bits, metafilepict and metafile header
               of the metafile contained within a clipboard file

  CALLS      : WINDOWS
                 GlobalAlloc
                 GlobalLock
                 GlobalUnlock
                 GlobalFree
                 MessageBox
                 _llseek
                 _lread
                 _lclose
                 SetMetaFileBits

  MESSAGES   : none

  RETURNS    : BOOL

  COMMENTS   :

  HISTORY    : 1/16/91 - created - drc
               5/23/93 - ported to NT.	it must handle 3.1 clipboard
                         as well as NT clipboard files - drc

************************************************************************/

BOOL RenderClipMeta(LPVOID lpvClipHeader, int fh, WORD ClipID)
{
  int  	            wBytesRead;
  long              lBytesRead;
  long              lSize;
  DWORD             lOffset;
  DWORD             dwSizeOfMetaFilePict;
  BOOL              bEMF = FALSE;
  LPNTCLIPFILEFORMAT lpNTClp;
  LPCLIPFILEFORMAT    lpClp;
  //
  //cast the void ptr to the clipfile header appropriately
  //
  if (bEnhMeta)
  {
    lpNTClp = (LPNTCLIPFILEFORMAT)lpvClipHeader;  
	bEMF = TRUE;
  }
  else
    lpClp = (LPCLIPFILEFORMAT)lpvClipHeader;  
  //
  //obtain the appropriate size of the metafilepict. win16 vs win32
  //
  dwSizeOfMetaFilePict = (ClipID == CLP_ID) ?
			  sizeof(OLDMETAFILEPICT) :
			  sizeof(METAFILEPICT);
  //
  //free any memory already allocated for the METAFILEPICT 
  //
  if (lpMFP != NULL || lpOldMFP != NULL) 
  {
    GlobalFreePtr(lpMFP);
	lpMFP = NULL;
  }
  //
  //allocate enough memory to read the metafile bits into 
  //
  if (!(lpMFBits = GlobalAllocPtr(GHND, ((bEMF) ? lpNTClp->DataLen 
                                            : lpClp->DataLen - dwSizeOfMetaFilePict))))
    return(FALSE);
  //
  //offset to the metafile bits 
  //
  lOffset = ((bEMF) ? lpNTClp->DataOffset : lpClp->DataOffset + dwSizeOfMetaFilePict );
  //
  //size of metafile bits
  //
  lSize = (long)( ((bEMF) ? lpNTClp->DataLen : lpClp->DataLen - dwSizeOfMetaFilePict));
  //
  //seek to the beginning of the metafile bits 
  //
  _llseek(fh, lOffset, 0);
  //
  //read the metafile bits 
  //
  lBytesRead = _hread(fh, lpMFBits, lSize);
  //
  //if unable to read the metafile bits bail out
  //
  if( lBytesRead == -1 || lBytesRead < lSize)  
  {
    GlobalFreePtr(lpMFBits);
    MessageBox(hWndMain, "Unable to read metafile bits",
                     NULL, MB_OK | MB_ICONHAND);
    return(FALSE);
  }
  //
  //return to beginning to read metafile header 
  //
  _llseek(fh, lOffset, 0);
  //
  //read the metafile header 
  //
  if (!bEMF)
    wBytesRead = _lread(fh, (LPSTR)&mfHeader, sizeof(METAHEADER));
  else
    wBytesRead = _lread(fh, (LPSTR)&emfHeader, sizeof(ENHMETAHEADER));
  //
  //if unable to read the header return 
  //
  if( wBytesRead == -1 || (WORD)wBytesRead < ((bEMF) ? sizeof(ENHMETAHEADER) : sizeof(METAHEADER)) )  
  {
    MessageBox(hWndMain, "Unable to read metafile header",
                     NULL, MB_OK | MB_ICONHAND);
    return(FALSE);
  }
  //
  //set the metafile bits to the memory allocated for that purpose 
  //
  if (bEMF)
    //
	//win32
	//
    hemf = SetEnhMetaFileBits(GlobalSizePtr(lpMFBits), lpMFBits);
  else
    //
	//win16
	//
    hMF  = SetMetaFileBitsEx(GlobalSizePtr(lpMFBits), lpMFBits);

  if ( NULL == ((bEMF) ? hemf : hMF))
  {
    MessageBox(hWndMain, "Unable to set metafile bits",
               NULL, MB_OK | MB_ICONHAND);

    return(FALSE);
  }
  //
  //allocate memory for the metafile pict structure 
  //
  if (!(hMFP = GlobalAlloc(GHND, dwSizeOfMetaFilePict)))  
  {
    MessageBox(hWndMain, "Unable allocate memory for metafile pict",
                     NULL, MB_OK | MB_ICONHAND);
    return(FALSE);
  }
  //
  //lock the memory 
  //
  if (ClipID == CLP_ID)
    lpOldMFP = (LPOLDMETAFILEPICT)GlobalLock(hMFP);
  else
    lpMFP = (LPMETAFILEPICT)GlobalLock(hMFP);

  if (!lpMFP && !lpOldMFP)
    {
      MessageBox(hWndMain, "unable to lock metafile pict memory",
                     NULL, MB_OK | MB_ICONHAND);
      GlobalFree(hMFP);
      return(FALSE);
    }
  //
  //reposition to the start of the METAFILEPICT header. 
  //
  _llseek(fh, ((bEMF) ? lpNTClp->DataOffset : lpClp->DataOffset), 0);
  //
  //read the metafile pict structure 
  //
  wBytesRead = _lread(fh, ((ClipID == CLP_ID) ? (LPVOID)lpOldMFP : (LPVOID)lpMFP),
		      dwSizeOfMetaFilePict);
  //
  //if unable to read, return 
  //
  if( wBytesRead == -1 || wBytesRead < (long)dwSizeOfMetaFilePict)	{
    MessageBox(hWndMain, "Unable to read metafile pict",
		     NULL, MB_OK | MB_ICONHAND);
    GlobalUnlock(hMFP);
    GlobalFree(hMFP);
    return(FALSE);
  }

  if (bEnhMeta)
    GetEMFCoolStuff();
//DENNIS - check this out....

  /* update metafile handle */
  if (ClipID == CLP_ID)
     lpOldMFP->hMF = (WORD)hMF;
  else
     lpMFP->hMF = hemf;

  return(TRUE);
}

/***********************************************************************

  FUNCTION   : RenderPlaceableMeta

  PARAMETERS : int fh - filehandle to the placeable metafile

  PURPOSE    : read the metafile bits, metafile header and placeable
               metafile header of a placeable metafile.

  CALLS      : WINDOWS
                 GlobalAlloc
                 GlobalLock
                 Global
                 DeleteMetaFile
                 SetMetaFileBits
                 _llseek
                 _lread
                 _lclose
                 MessageBox


  MESSAGES   : none

  RETURNS    : BOOL

  COMMENTS   :

  HISTORY    : 1/16/91 - created - drc
               7/1/93 - modified for win32 - denniscr

************************************************************************/

BOOL RenderPlaceableMeta(fh)
int	fh;
{
  int      wBytesRead;
  long	   lBytesRead;
  DWORD    dwSize;
  //
  //if there is currently a metafile loaded, get rid of it 
  //
  if (bMetaInRam && hMF && !bEnhMeta)
    DeleteMetaFile(hMF);
  //
  //seek to beginning of file and read aldus header 
  //
  _llseek(fh, 0, 0);
  //
  //read the placeable header 
  //
  wBytesRead = _lread(fh, (LPSTR)&aldusMFHeader, sizeof(ALDUSMFHEADER));
  //
  //if there is an error, return 
  //
  if( wBytesRead == -1 || wBytesRead < sizeof(ALDUSMFHEADER) )	{
    MessageBox(hWndMain, "Unable to read placeable header",
                     NULL, MB_OK | MB_ICONHAND);
    return(FALSE);
  }
  //
  //return to read metafile header 
  //
  _llseek(fh, sizeof(aldusMFHeader), 0);
  //
  //read the metafile header 
  //
  wBytesRead = _lread(fh, (LPSTR)&mfHeader, sizeof(METAHEADER));
  //
  //if there is an error return 
  //
  if( wBytesRead == -1 || wBytesRead < sizeof(METAHEADER) )  {
    MessageBox(hWndMain, "Unable to read metafile header",
                     NULL, MB_OK | MB_ICONHAND);
    return(FALSE);
  }
  //
  //allocate memory for the metafile bits 
  //
  if (!(lpMFBits = GlobalAllocPtr(GHND, (mfHeader.mtSize * 2L))))  
  {
    MessageBox(hWndMain, "Unable to allocate memory for metafile bits",
                     NULL, MB_OK | MB_ICONHAND);
    return(FALSE);
  }
  //
  //seek to the metafile bits 
  //
  _llseek(fh, sizeof(aldusMFHeader), 0);
  //
  //read metafile bits 
  //
  lBytesRead = _hread(fh, lpMFBits, (WORD)(mfHeader.mtSize * 2));
  //
  //if there was an error 
  //
  if( lBytesRead == -1 )  
  {
     MessageBox(hWndMain, "Unable to read metafile bits",
                NULL, MB_OK | MB_ICONHAND);
     GlobalFreePtr(lpMFBits);
     return(FALSE);
  }
  //
  //set the metafile bits to the memory that we allocated 
  //
  dwSize = GlobalSizePtr(lpMFBits);

  if (!(hMF = SetMetaFileBitsEx(dwSize, lpMFBits)))
    return(FALSE);

  return(TRUE);
}

/***********************************************************************

  FUNCTION   : SetPlaceableExts

  PARAMETERS : HDC           hDC
               ALDUSMFHEADER ahdr
               int           nDest

  PURPOSE    : set the origins and extents on the DC to correspond with
               the origins and extents specified within the placeable
               metafile header

  CALLS      : WINDOWS
                 GetClientRect
                 SetMapMode
                 SetWindowOrg
                 SetWindowExt
                 SetViewportOrg
                 SetViewportExt

               C runtime
                 labs

  MESSAGES   : none

  RETURNS    : void

  COMMENTS   :

  HISTORY    : 1/16/91 - created - drc

************************************************************************/

void SetPlaceableExts(HDC hDC, ALDUSMFHEADER ahdr, int nDest)
{
  RECT	      rect;
  POINT	      lpPT;
  SIZE	      lpSize;

  /* if setting the extents on the display DC */
  if (nDest != WMFPRINTER)
    GetClientRect(hWndMain, &rect);

  SetMapMode(hDC, MM_ANISOTROPIC);

  /* set the windows origin to correspond to the bounding box origin
     contained in the placeable header */
  SetWindowOrgEx(hDC, ahdr.bbox.left, ahdr.bbox.top, &lpPT);

  /* set the window extents based on the abs value of the bbox coords */
  SetWindowExtEx(hDC,abs(ahdr.bbox.left) + abs(ahdr.bbox.right),
		   abs(ahdr.bbox.top) + abs(ahdr.bbox.bottom),
		   &lpSize);

  /* set the viewport origin and extents */
  if (nDest != WMFPRINTER)
    {
      SetViewportOrgEx(hDC, 0, 0, &lpPT);
      SetViewportExtEx(hDC, rect.right, rect.bottom, &lpSize);
    }
  else
    {
      SetViewportOrgEx(hPr, 0, 0, &lpPT);
      SetViewportExtEx(hPr,GetDeviceCaps(hPr, HORZRES),
			 GetDeviceCaps(hPr, VERTRES),
			 &lpSize);
    }
}

/***********************************************************************

  FUNCTION   : SetClipMetaExts

  PARAMETERS : HDC          hDC
               METAFILEPICT MFP
               int          nDest

  PURPOSE    : set the extents to the client rect for clipboard metafiles

  CALLS      : WINDOWS
                 GetClientRect
                 IntersectClipRect
                 SetMapMode
                 SetViewportOrg
                 SetViewportExt
                 SetWindowExt

  MESSAGES   : none

  RETURNS    : void

  COMMENTS   : this is not as robust as it could be.  A more complete
               approach might be something like Petzold discusses in
               his Programming Windows book on page 793 in the
               function PrepareMetaFile().

  HISTORY    : 1/16/91 - created - drc

************************************************************************/

void SetClipMetaExts(hDC, lpMFP, lpOldMFP, nDest)
HDC		  hDC;
LPMETAFILEPICT	  lpMFP;
LPOLDMETAFILEPICT lpOldMFP;
int		  nDest;
{
  int	cx, cy;
  RECT	rect;
  POINT lpPT;
  SIZE	lpSize;
  long	lmm;
  long	lxExt;
  long	lyExt;

  /* extents for the display DC */
  if (nDest != WMFPRINTER)
    {
      GetClientRect(hWndMain, &rect);
      cx = rect.right - rect.left;
      cy = rect.bottom - rect.top;
      IntersectClipRect(hDC, rect.left, rect.top, rect.right, rect.bottom);
    }

  SetMapMode(hDC, ((lpOldMFP != NULL) ? lpOldMFP->mm : lpMFP->mm));

  /* set physical origin to 0, 0 */
  SetViewportOrgEx(hDC, 0, 0, &lpPT);

  /* given the mapping mode specified in the metafilepict */
  lmm = (lpOldMFP != NULL) ? lpOldMFP->mm : lpMFP->mm;
  lxExt = (lpOldMFP != NULL) ? lpOldMFP->xExt : lpMFP->xExt;
  lyExt = (lpOldMFP != NULL) ? lpOldMFP->yExt : lpMFP->yExt;

  switch (lmm)	{
    case MM_ISOTROPIC:
      if (lxExt && lyExt)
	SetWindowExtEx(hDC, lxExt, lyExt, &lpSize);

        /* fall through */

    case MM_ANISOTROPIC:
      if (nDest != WMFPRINTER)
	SetViewportExtEx(hDC, cx, cy, &lpSize);
      else
	SetViewportExtEx(hDC, GetDeviceCaps(hDC, HORZRES),
			    GetDeviceCaps(hDC, VERTRES), &lpSize );
    break;

    default:
      break;
  }

}

/***********************************************************************

  FUNCTION   : ProcessFile

  PARAMETERS : HWND  hWnd
               LPSTR lpFileName

  PURPOSE    : open the metafile, determine if it contains a valid
               metafile, decide what type of metafile it is (wmf,
               clipboard, or placeable) and take care of some menu
               housekeeping tasks.

  CALLS      :
  
  MESSAGES   : none

  RETURNS    : BOOL

  COMMENTS   :

  HISTORY    : 1/16/91 - created - drc

************************************************************************/

BOOL ProcessFile(hWnd, lpFileName)
HWND  hWnd;
LPSTR lpFileName;
{
  //
  //for openfiledialog 
  //
  char drive[3];
  char dir[130];
  char fname[13];
  char ext[5];

  char * pchCorrectSir;
  //
  //initialize these global handles to metafiles
  //
  if (hMF && !bMetaInRam)
  {
    DeleteMetaFile(hMF);
	hMF = NULL;
  }
  if (hemf && !bMetaInRam)
  {
    DeleteEnhMetaFile(hemf);
    hemf = NULL;
  }

  if (lpMFBits)
  {
    GlobalFreePtr(lpMFBits);
	lpMFBits = NULL;
    hemf = NULL;
	hMF = NULL;
  }

  bEnhMeta = FALSE;
  //
  //split the fully qualified filename into its components 
  //
  SplitPath( lpFileName, (LPSTR)drive,
	      (LPSTR)dir, (LPSTR)fname, (LPSTR)ext);

  pchCorrectSir = _strupr( _strdup( ext ) );
  //
  //if the memory for the emf header, desc string and palette
  //is still around then nuke it
  //
  if (EmfPtr.lpEMFHdr)
    GlobalFreePtr(EmfPtr.lpEMFHdr);
  if (EmfPtr.lpDescStr)
    GlobalFreePtr(EmfPtr.lpDescStr);
  if (EmfPtr.lpPal)
    GlobalFreePtr(EmfPtr.lpPal);
  //
  //if the file is an enhanced metafile
  //
  if (lstrcmp((LPSTR)pchCorrectSir, (LPSTR)"CLP") == 0)	
    return ProcessCLP(hWnd, lpFileName);
  //
  //if the file is a Windows metafile or a Windows or placeable metafile
  //as per the normal naming conventions 
  //
  if (lstrcmp((LPSTR)pchCorrectSir, (LPSTR)"WMF") == 0)	
    return ProcessWMF(hWnd, lpFileName);
  //
  //if the file is a clipboard file
  //
  if (lstrcmp((LPSTR)pchCorrectSir, (LPSTR)"EMF") == 0)	
    return ProcessEMF(hWnd, lpFileName);
}

/***********************************************************************

  FUNCTION   : ProcessWMF

  PARAMETERS : HWND  hWnd
               LPSTR lpFileName

  PURPOSE    : open the metafile and determine if it is a Windows metafile or
               placeable metafile.  Then take care of some menu housekeeping 
               tasks.

  CALLS      : 

  MESSAGES   : none

  RETURNS    : BOOL

  COMMENTS   :

  HISTORY    : 6/23/93 - created - drc

************************************************************************/

BOOL ProcessWMF(HWND hWnd, LPSTR lpFileName)
{
  int		 fh;
  int		 wBytesRead;
  DWORD      dwIsAldus;
  char       szCaption[144];

  /* for openfiledialog */
  char drive[3];
  char dir[130];
  char fname[13];
  char ext[5];
  char * pchCorrectSir;
    //
    //split the fully qualified filename into its components 
    //
    SplitPath( lpFileName, (LPSTR)drive,
	        (LPSTR)dir, (LPSTR)fname, (LPSTR)ext);

    pchCorrectSir = _strupr( _strdup( ext ) );
	//
    //try to open the file.  It's existence has already been
    //checked by OpenFileDialog 
	//
    fh = _lopen(lpFileName, OF_READ);
    //
    //if opened successfully
	//
    if (fh != -1)  
    {
	  //
      //always disable the clipboard and EMF header menu if we get here 
	  //
      EnableMenuItem(GetMenu(hWnd), IDM_CLIPHDR, MF_DISABLED | MF_GRAYED);
      EnableMenuItem(GetMenu(hWnd), IDM_ENHHEADER, MF_DISABLED | MF_GRAYED);
	  //
      // read the first dword of the file to see if it is a placeable wmf 
	  //
      wBytesRead = _lread(fh,(LPSTR)&dwIsAldus, sizeof(dwIsAldus));

      if (wBytesRead == -1 || wBytesRead < sizeof(dwIsAldus))
      {
        _lclose(fh);
        MessageBox(hWndMain, "unable to read file", NULL,
                   MB_OK | MB_ICONEXCLAMATION);
        return (FALSE);

      }
	  //
      // if this is windows metafile, not a placeable wmf 
	  //
      if (dwIsAldus != ALDUSKEY)  
      {
        //  if (!bMetaInRam)
        hMF = GetMetaFile((LPSTR)OpenName);
		//
        //disable aldus header menu item 
		//
        EnableMenuItem(GetMenu(hWnd), IDM_ALDUSHDR, MF_DISABLED|MF_GRAYED);
		//
        //seek to the beginning of the file 
		//
        _llseek(fh, 0, 0);
		//
        //read the wmf header 
		//
	    wBytesRead = _lread(fh, (LPSTR)&mfHeader, sizeof(METAHEADER));
		//
        //done with file so close it 
		//
        _lclose(fh);
		//
        //if read failed 
		//
	    if (wBytesRead == -1 || wBytesRead < sizeof(dwIsAldus))  
	    {
          MessageBox(hWndMain, "unable to read metafile header", NULL,
                     MB_OK | MB_ICONEXCLAMATION);
          return (FALSE);
        }
      }
	  //
      //this is a placeable metafile 
	  //
      else  
      {
		//
        //enable the placeable header menu item 
		//
        EnableMenuItem(GetMenu(hWnd), IDM_ALDUSHDR, MF_ENABLED);
		//
        //convert the placeable format into something that can
        //be used with GDI metafile functions 
		//
        RenderPlaceableMeta(fh);
		//
        //close the file 
		//
        _lclose(fh);

      }
	  //
      //at this point we have a metafile header regardless of whether
      //the metafile was a windows metafile or a placeable metafile
      //so check to see if it is valid.  There is really no good
      //way to do this so just make sure that the mtType is either
      //1 or 2 (memory or disk file) 
	  //
      if ( (mfHeader.mtType != 1) && (mfHeader.mtType != 2) )  
      {
		//
        //set the program flags appropriately 
		//
        bBadFile = TRUE;
        bMetaFileOpen = FALSE;
        bValidFile = FALSE;
		//
        //let the user know that this is an invalid metafile 
		//
        MessageBox(hWndMain, "This file is not a valid metafile",
                   NULL, MB_OK | MB_ICONEXCLAMATION);
		//
        //restore the caption text to the default 
		//
        SetWindowText(hWnd, (LPSTR)APPNAME);
		//
        //disable menu items, indicating that a valid metafile has not been
        //loaded 
		//
        EnableMenuItem(GetMenu(hWnd), IDM_VIEW, MF_DISABLED|MF_GRAYED|MF_BYPOSITION);
        EnableMenuItem(GetMenu(hWnd), IDM_PLAY, MF_DISABLED|MF_GRAYED|MF_BYPOSITION);
        EnableMenuItem(GetMenu(hWnd), IDM_PRINT, MF_DISABLED|MF_GRAYED);
	    EnableMenuItem(GetMenu(hWnd), IDM_SAVEAS, MF_DISABLED|MF_GRAYED);
		//
        //refresh the menu bar to reflect above changes 
		//
        DrawMenuBar(hWnd);
      }
	  //
      //this is a valid metafile...at least based on the above criteria 
	  //
      else  
      {
		//
        //modify and update the caption text 
		//
	    wsprintf((LPSTR)szCaption, (LPSTR)"%s - %s.%s",
                 (LPSTR)APPNAME, (LPSTR)fname, (LPSTR)ext);
		//
        //this could be used by the printing routines if unable to print 
		//
        wsprintf((LPSTR)fnameext, (LPSTR)"%s.%s", (LPSTR)fname, (LPSTR)ext);

        SetWindowText(hWnd, (LPSTR)szCaption);
		//
        //enable the appropriate menu items 
		//
        EnableMenuItem(GetMenu(hWnd), IDM_VIEW, MF_ENABLED|MF_BYPOSITION);
        EnableMenuItem(GetMenu(hWnd), IDM_PLAY, MF_ENABLED|MF_BYPOSITION);
        EnableMenuItem(GetMenu(hWnd), IDM_PRINT, MF_ENABLED);
	    EnableMenuItem(GetMenu(hWnd), IDM_SAVEAS, MF_ENABLED);
        EnableMenuItem(GetMenu(hWnd), IDM_HEADER, MF_ENABLED);
		//
        //refresh the menu bar to reflect above changes 
		//
        DrawMenuBar(hWnd);
		//
        //set global flags appropriately 
		//
        bValidFile = TRUE;
	    bMetaFileOpen = TRUE;

	    if (dwIsAldus != ALDUSKEY)  
	    {
	      bAldusMeta = FALSE;
	      bMetaInRam = FALSE;
	    }
	    else  
	    {
	      bAldusMeta = TRUE;
	      bMetaInRam = TRUE;
	    }
      }
      return (TRUE);

    } //if fh != -1
    else
      return (FALSE);
}

/***********************************************************************

  FUNCTION   : ProcessCLP

  PARAMETERS : HWND  hWnd
               LPSTR lpFileName

  PURPOSE    : open the metafile contained in the clipboard file and 
               take care of some menu housekeeping tasks.

  CALLS      : 

  MESSAGES   : none

  RETURNS    : BOOL

  COMMENTS   :

  HISTORY    : 6/23/93 - created - drc

************************************************************************/


BOOL ProcessCLP(HWND hWnd, LPSTR lpFileName)
{
  WORD             i;
  int              fh;
  DWORD            HeaderPos;
  DWORD            nSizeOfClipHeader;
  DWORD            nSizeOfClipFormat;
  NTCLIPFILEHEADER NTFileHeader;
  NTCLIPFILEFORMAT NTClipHeader;
  CLIPFILEHEADER   FileHeader;
  CLIPFILEFORMAT   ClipHeader;
  char             szCaption[144];
  WORD             wFileID;
  BOOL             bMetaFound = FALSE;
  LPVOID           lpvAddressOfHdr;

  /* for openfiledialog */
  char drive[3];
  char dir[130];
  char fname[13];
  char ext[5];
  char * pchCorrectSir;
    //
    //split the fully qualified filename into its components 
    //
    SplitPath( lpFileName, (LPSTR)drive,
	        (LPSTR)dir, (LPSTR)fname, (LPSTR)ext);

    pchCorrectSir = _strupr( _strdup( ext ) );
	//
    //try to open the file.  It's existence has already been
    //checked by OpenFileDialog 
    fh = _lopen(lpFileName, OF_READ);
	//
    //if opened successfully 
    if (fh != -1 )  
    {
	  //
      // read the clipboard fileidentifier  
	  //
      wFileID = 0;
      _lread(fh, (LPSTR)&wFileID, sizeof(WORD));
	  _llseek(fh, 0, 0);
	  //
      //if this is not a valid clipboard file based on the file
      //identifier of the file header 
	  //
	  if (wFileID != CLP_ID && wFileID != CLP_NT_ID && wFileID != CLPBK_NT_ID)
	  {

        _lclose(fh);
        MessageBox(hWndMain, "This file is not a valid clipboard file",
                   NULL, MB_OK | MB_ICONEXCLAMATION);
        return (FALSE);
      }
	  switch (wFileID)  
	  {
	    case CLP_ID:
            _lread(fh, (LPSTR)&FileHeader, sizeof(CLIPFILEHEADER));
			nSizeOfClipHeader = sizeof(CLIPFILEHEADER);
			nSizeOfClipFormat = sizeof(CLIPFILEFORMAT);
	        HeaderPos = nSizeOfClipHeader;
		  break;

	    case CLP_NT_ID:
		case CLPBK_NT_ID:
            NTFileHeader.FormatCount = 0;
            _lread(fh, (LPSTR)&NTFileHeader, sizeof(NTCLIPFILEHEADER));
			nSizeOfClipHeader = sizeof(NTCLIPFILEHEADER);
			nSizeOfClipFormat = sizeof(NTCLIPFILEFORMAT);
	        HeaderPos = nSizeOfClipHeader;
		  break;

		default:
		  break;
	  }
	  //
	  //search the formats contained within the clipboard file looking
      //for a metafile.  Break if and when it is found 
      //
      for (i=0; 
           i < ((wFileID == CLP_ID) ? FileHeader.FormatCount : NTFileHeader.FormatCount); 
           i++)  
      {

        _llseek(fh, HeaderPos, 0);
		//
        //read the clipboard header found at current position 
		//
		lpvAddressOfHdr = (wFileID == CLP_ID) ? (LPVOID)&ClipHeader : (LPVOID)&NTClipHeader;

        if(_lread(fh, (LPSTR)lpvAddressOfHdr, nSizeOfClipFormat) < nSizeOfClipFormat)  
        //if(_lread(fh, (LPSTR)&ClipHeader, nSizeOfClipHeader) < nSizeOfClipHeader)  
        {
          _lclose(fh);
          MessageBox(hWndMain, "read of clipboard header failed",
                       NULL, MB_OK | MB_ICONEXCLAMATION);
          return (FALSE);
        }
		//
        //increment the file offset to data
		//
        HeaderPos += nSizeOfClipFormat;
		//
        //if a metafile was found break... 
		//this break assumes that CF_METAFILEPICT formats are always written before CF_ENHMETAFILE
		//formats.
		//
        if (wFileID == CLP_ID && ClipHeader.FormatID == CF_METAFILEPICT)
		{
		  bMetaFound = TRUE;
          break;
		}

		if (wFileID == CLP_NT_ID || wFileID == CLPBK_NT_ID) 
		{    
		  if (NTClipHeader.FormatID == CF_ENHMETAFILE)
//		    HeaderPos += NTClipHeader.DataLen;
	      //else
		  {
		    bMetaFound = TRUE;
			break;
		  }
		}

      }  //for i < formatcount

      if (bMetaFound)  
      {
		//
        //if there is currently a metafile loaded delete it.  
		//
		if (wFileID == CLP_ID)
		{
          if ((bMetaInRam) && (hMF))
		  {
            DeleteMetaFile(hMF);
			hMF = NULL;
		  }
		}
		else
		{
          if ((bMetaInRam) && (hemf))
		  {
            DeleteEnhMetaFile(hemf);
			hemf = NULL;
		  }
		}
		 
		//
        //modify and update the caption text 
		//
	    wsprintf((LPSTR)szCaption, (LPSTR)"%s - %s.%s",
                   (LPSTR)APPNAME, (LPSTR)fname, (LPSTR)ext);
		//
        //this could be used by the printing routines if unable to print 
		//
	    wsprintf((LPSTR)fnameext, (LPSTR)"%s.%s", (LPSTR)fname, (LPSTR)ext);

        SetWindowText(hWnd, (LPSTR)szCaption);
		//
        //enable the appropriate menu items 
		//
		if (wFileID == CLP_ID)
		{
          EnableMenuItem(GetMenu(hWnd), IDM_ENHHEADER, MF_DISABLED | MF_GRAYED);
          EnableMenuItem(GetMenu(hWnd), IDM_HEADER, MF_ENABLED);
		}
	    else
		{
          EnableMenuItem(GetMenu(hWnd), IDM_ENHHEADER, MF_ENABLED);
          EnableMenuItem(GetMenu(hWnd), IDM_HEADER, MF_DISABLED | MF_GRAYED);
		}

        EnableMenuItem(GetMenu(hWnd), IDM_ALDUSHDR, MF_DISABLED|MF_GRAYED);
        EnableMenuItem(GetMenu(hWnd), IDM_CLIPHDR, MF_ENABLED);
        EnableMenuItem(GetMenu(hWnd), IDM_VIEW, MF_ENABLED|MF_BYPOSITION);
        EnableMenuItem(GetMenu(hWnd), IDM_PLAY, MF_ENABLED|MF_BYPOSITION);
	    EnableMenuItem(GetMenu(hWnd), IDM_PRINT, MF_ENABLED);
	    EnableMenuItem(GetMenu(hWnd), IDM_SAVEAS, MF_ENABLED);
		//
        //refresh the menu bar 
		//
        DrawMenuBar(hWnd);
		//
        //set the program flags appropriately 
		//
        bValidFile = TRUE;
        bMetaFileOpen = TRUE;
	    bMetaInRam = TRUE;
	    bAldusMeta = FALSE;
		bEnhMeta = (wFileID == CLP_ID) ? FALSE : TRUE;
		//
		//convert the metafile contained within the clipboard file into
        //a format useable with GDI metafile functions 
		//
	    if (!RenderClipMeta(((wFileID == CLP_ID)? (LPVOID)&ClipHeader : (LPVOID)&NTClipHeader), 
	                          fh, 
	                          FileHeader.FileIdentifier))

          MessageBox(hWndMain, "Unable to render format",
                       NULL, MB_OK | MB_ICONEXCLAMATION);
        _lclose(fh);

      }
	  //
      //a metafile was not found within the clipboard file 
	  //
      else  
      {
        bBadFile = TRUE;
        bMetaFileOpen = FALSE;
        bValidFile = FALSE;
		bEnhMeta = FALSE;
		//
		//let the user know 
		//
        MessageBox(hWndMain, "This CLP file doesn't contain a valid metafile",
                     NULL, MB_OK | MB_ICONEXCLAMATION);
		//
        //restore the caption text to default 
		//
        SetWindowText(hWnd, (LPSTR)APPNAME);
		//
        //disable previously enabled menu items 
		//
        EnableMenuItem(GetMenu(hWnd), IDM_VIEW, MF_DISABLED|MF_GRAYED|MF_BYPOSITION);
        EnableMenuItem(GetMenu(hWnd), IDM_PLAY, MF_DISABLED|MF_GRAYED|MF_BYPOSITION);
        EnableMenuItem(GetMenu(hWnd), IDM_PRINT, MF_DISABLED|MF_GRAYED);
	    EnableMenuItem(GetMenu(hWnd), IDM_SAVEAS, MF_DISABLED|MF_GRAYED);
		//
        //refresh the menu bar to reflect these changes 
		//
        DrawMenuBar(hWnd);
        _lclose(fh);
      }
      return (TRUE);
    }
    else
      return (FALSE);
}

/***********************************************************************

  FUNCTION   : ProcessEMF

  PARAMETERS : HWND  hWnd
               LPSTR lpFileName

  PURPOSE    : open the metafile contained in the clipboard file and 
               take care of some menu housekeeping tasks.

  CALLS      : 

  MESSAGES   : none

  RETURNS    : BOOL

  COMMENTS   :

  HISTORY    : 6/23/93 - created - drc

************************************************************************/


BOOL ProcessEMF(HWND hWnd, LPSTR lpFileName)
{
  char           szCaption[144];

  /* for openfiledialog */
  char drive[3];
  char dir[130];
  char fname[13];				
  char ext[5];
  char * pchCorrectSir;

  bEnhMeta = FALSE;
    //
    //split the fully qualified filename into its components 
    //
    SplitPath( lpFileName, (LPSTR)drive,
	        (LPSTR)dir, (LPSTR)fname, (LPSTR)ext);

    pchCorrectSir = _strupr( _strdup( ext ) );
    //
    //always disable the clipboard, WMF and Placeable header menu if we get here 
	//
    EnableMenuItem(GetMenu(hWnd), IDM_CLIPHDR, MF_DISABLED | MF_GRAYED);
    EnableMenuItem(GetMenu(hWnd), IDM_HEADER, MF_DISABLED | MF_GRAYED);
    EnableMenuItem(GetMenu(hWnd), IDM_ALDUSHDR, MF_DISABLED|MF_GRAYED);
	//
	//if emf was successfully opened
	//
	if (!hemf)
	  hemf = GetEnhMetaFile(lpFileName);

	if (hemf)
	{
	  GetEMFCoolStuff();
	  //
      //modify and update the caption text 
	  //
	  wsprintf((LPSTR)szCaption, (LPSTR)"%s - %s.%s",
                 (LPSTR)APPNAME, (LPSTR)fname, (LPSTR)ext);
	  //
      //this could be used by the printing routines if unable to print 
	  //
	  wsprintf((LPSTR)fnameext, (LPSTR)"%s.%s", (LPSTR)fname, (LPSTR)ext);

      SetWindowText(hWnd, (LPSTR)szCaption);
	  //
      //enable the appropriate menu items 
	  //
      EnableMenuItem(GetMenu(hWnd), IDM_ENHHEADER, MF_ENABLED);
      EnableMenuItem(GetMenu(hWnd), IDM_VIEW, MF_ENABLED|MF_BYPOSITION);
      EnableMenuItem(GetMenu(hWnd), IDM_PLAY, MF_ENABLED|MF_BYPOSITION);
	  EnableMenuItem(GetMenu(hWnd), IDM_PRINT, MF_ENABLED);
	  EnableMenuItem(GetMenu(hWnd), IDM_SAVEAS, MF_ENABLED);
	  //
      //refresh the menu bar 
	  //
      DrawMenuBar(hWnd);
	  //
      //set the program flags appropriately 
	  //
	  bValidFile = TRUE;
      bMetaFileOpen = TRUE;
	  bEnhMeta = TRUE;
	  bMetaInRam = FALSE;
	  bAldusMeta = FALSE;

	}
//	  DeleteEnhMetaFile(hemf);
	else
	{
	  bEnhMeta = FALSE;
	  bValidFile = FALSE;
      bBadFile = TRUE;
      bMetaFileOpen = FALSE;
	  //
	  //let the user know 
	  //
      MessageBox(hWndMain, "This EMF file doesn't contain a valid metafile",
                     NULL, MB_OK | MB_ICONEXCLAMATION);
	  //
      //restore the caption text to default 
	  //
      SetWindowText(hWnd, (LPSTR)APPNAME);
	  //
      //disable previously enabled menu items 
	  //
      EnableMenuItem(GetMenu(hWnd), IDM_VIEW, MF_DISABLED|MF_GRAYED|MF_BYPOSITION);
      EnableMenuItem(GetMenu(hWnd), IDM_PLAY, MF_DISABLED|MF_GRAYED|MF_BYPOSITION);
      EnableMenuItem(GetMenu(hWnd), IDM_PRINT, MF_DISABLED|MF_GRAYED);
	  EnableMenuItem(GetMenu(hWnd), IDM_SAVEAS, MF_DISABLED|MF_GRAYED);
	  //
      //refresh the menu bar to reflect these changes 
	  //
      DrawMenuBar(hWnd);
	}

    return TRUE;
}

/***********************************************************************

  FUNCTION   : GetEMFCoolStuff

  PARAMETERS : 

  PURPOSE    :  
  
  CALLS      : 

  MESSAGES   : 

  RETURNS    : 

  COMMENTS   : 
  
  HISTORY    : created 7/8/93 - denniscr

************************************************************************/
BOOL GetEMFCoolStuff()
{
	//
	//init these ptrs
	//
    EmfPtr.lpEMFHdr  = NULL;
    EmfPtr.lpDescStr = NULL;
    EmfPtr.lpPal     = NULL;

	if (hemf)
	{
	  //
	  //obtain the sizes of the emf header, description string and palette
	  //
	  UINT uiHdrSize = GetEnhMetaFileHeader(hemf, 0, NULL);
	  UINT uiDescStrSize = GetEnhMetaFileDescription(hemf, 0, NULL);
	  UINT uiPalEntries = GetEnhMetaFilePaletteEntries(hemf, 0, NULL);
	  //
	  //if these are lengths > 0 then allocate memory to store them
	  //
	  if (uiHdrSize)
	    EmfPtr.lpEMFHdr = (LPENHMETAHEADER)GlobalAllocPtr(GHND, uiHdrSize);
	  if (uiDescStrSize)
	    EmfPtr.lpDescStr = (LPTSTR)GlobalAllocPtr(GHND, uiDescStrSize);
	  if (uiPalEntries)
	    EmfPtr.lpPal = (LPPALETTEENTRY)GlobalAllocPtr(GHND, uiPalEntries * sizeof(PALETTEENTRY));
	  //
	  //so far the emf seems to be valid so continue
	  //
	  if (uiHdrSize)
	  {
  	    //
	    //get the actual emf header and description string
	    //
	    if (!GetEnhMetaFileHeader(hemf, uiHdrSize, EmfPtr.lpEMFHdr))
	    {
          MessageBox(hWndMain, "unable to read enhanced metafile header", NULL,
                   MB_OK | MB_ICONEXCLAMATION);
		  bValidFile = FALSE;
          return (FALSE);
        }
		else
		{
		  //
		  //get the description string if it exists
		  //
		  if (uiDescStrSize)
		    GetEnhMetaFileDescription(hemf, uiDescStrSize, EmfPtr.lpDescStr);
		  //
		  //get the palette if it exists
		  //
		  if (uiPalEntries)
		  {
		    GetEnhMetaFilePaletteEntries(hemf, uiPalEntries, EmfPtr.lpPal);
		    EmfPtr.palNumEntries = (WORD)uiPalEntries;
		  }
		}
      }
   }
   return (TRUE);
}

/***********************************************************************

  FUNCTION   : EnhMetaFileEnumProc

  PARAMETERS : HDC           hDC
               LPHANDLETABLE lpHTable
               LPMETARECORD  lpMFR
               int           nObj
               LPARAM        lpData


  PURPOSE    : callback for EnumEnhMetaFile.  
  
  CALLS      : EnumMFIndirect()

  MESSAGES   : none

  RETURNS    : int

  COMMENTS   : 
  
  HISTORY    : created 6/30/93 - denniscr

************************************************************************/
int CALLBACK EnhMetaFileEnumProc(HDC hDC, LPHANDLETABLE lpHTable, 
                                 LPENHMETARECORD lpEMFR, int nObj, LPARAM lpData)
{
  return EnumMFIndirect(hDC, lpHTable, NULL, lpEMFR, nObj, lpData);
}

/***********************************************************************

  FUNCTION   : EnumMFIndirect

  PARAMETERS : HDC             hDC
               LPHANDLETABLE   lpHTable
               LPMETARECORD    lpMFR
			   LPENHMETARECORD lpEMFR
               int             nObj
               LPARAM          lpData


  PURPOSE    : called by EnumMetaFile and EnumEnhMetaFile.  Handles the stepping of
               each metafile record.

  MESSAGES   : none

  RETURNS    : int

  COMMENTS   : ENUMMFSTEP is used whenever records are to be played,
               regardless of whether you are playing records from the
               list, stepping all, or stepping a range.

               ENUMMFLIST is used when you need to add strings to a listbox
               that describe the type of reocrd.

  HISTORY    : created 7/1/93 - denniscr

************************************************************************/

int EnumMFIndirect(HDC hDC, LPHANDLETABLE lpHTable, 
                            LPMETARECORD lpMFR, 
                            LPENHMETARECORD lpEMFR, 
                            int nObj, LPARAM lpData)
{
  WORD i;
  char szMetaFunction[50];
  static BOOL iMapModeSet = FALSE;
  BOOL DlgRet = TRUE;
  //
  // what is the enumeration action that we are taking? 
  //
  switch (iEnumAction) 
  {
	//
    //if the enumeration was entered ala the step metafile menu selection 
	//
    case ENUMMFSTEP:
	   //	
       //keep track of the current metafile record number 
	   //
       iRecNum++;
	   //
       //allocate memory for the record.  this memory will be used by
       //other functions that need to use the contents of the record 
	   //
       hMem = GlobalAlloc(GHND, ((bEnhMeta) ? (LONG)lpEMFR->nSize : (LONG)lpMFR->rdSize * 2));
	   //
       //if the memory was successfully allocated 
	   //
       if (hMem) 
       {				
	     if (bEnhMeta)
		 {
		   //
           //obtain a long pointer to this memory 
		   //
           lpEMFParams = (LPEMFPARAMETERS)GlobalLock(hMem);
		   //
           //copy the contents of the record to the global memory 
		   //
           emfMetaRec.nSize = lpEMFR->nSize;
           emfMetaRec.iType = lpEMFR->iType;
           for (i = 0;(DWORD)i < (lpEMFR->nSize - sizeof(emfMetaRec.nSize) - 
                sizeof(emfMetaRec.iType))/sizeof(DWORD); i++)
             *lpEMFParams++ = lpEMFR->dParm[i];

		 }
         else
		 {
            /* obtain a long pointer to this memory */
	        lpMFParams = (LPPARAMETERS)GlobalLock(hMem);
			  							  
            /* copy the contents of the record to the global memory */
            MetaRec.rdSize = lpMFR->rdSize;
            MetaRec.rdFunction = lpMFR->rdFunction;
	        for (i = 0; (DWORD)i < lpMFR->rdSize - 3; i++)
              *lpMFParams++ = lpMFR->rdParm[i];
		 }
         GlobalUnlock(hMem);
		 //
         //if STEPPING through metafile records that have been selected
         //by selecting the menu options Play - Step - All, Play - Step -
         //Range, or selecting records from the View - List listbox 
		 //
         if ( !bPlayItAll
              || ( bEnumRange && iRecNum >= (WORD)iStartRange && iRecNum <= (WORD)iEndRange )
              || ( bPlayList && !bPlayItAll ) )
	     {
		   //
           //if playing records selected from the View - List
           //listbox of records
	       if (bPlayList)  
	       {
			 //
             //if playing the selected records 
			 //
		     if (bPlaySelList)  
		     {
			   //
               //if done playing the selected records then stop the enumeration
			   //
		       if (iCount == iNumSel)
		       return(0);
			   //
               //if this is a selected record then play it 
			   //
		       if ((WORD)lpSelMem[iCount] == iRecNum - 1)	
		       {
				 //
                 //initialize flag 
				 //
			     bPlayRec = FALSE;
				 //
                 //increment the count 
				 //
			     iCount = (iCount < iLBItemsInBuf) ? ++iCount : iCount;
				 //
                 //call the dialog box that lets you play or ignore this record */
				 //
			     DlgRet = DialogBox(hInst, (LPSTR)"WMFDLG", hWndMain, WMFRecDlgProc);
		       }
		       else
			     //
                 //initialize flag and do nothing else 
				 //
			     bPlayRec = FALSE;
             }
			 //
             //playing the unselected records 
			 //
		     else  
		     {
			   //
			   //if this is one of the selected records then increment
               //the record count and init a flag but do nothing else 
			   //
		       if ((WORD)lpSelMem[iCount] == iRecNum - 1)	{
			   //
			   //set count to next selected record in listbox 
			   //
			   iCount = (iCount < iLBItemsInBuf) ? ++iCount : iCount;
			   bPlayRec = FALSE;
		      }
			  //
              //this is not one of the selected records which is what we
              //want in this case.  So, init a flag give the user the
              //opportunity to play the record 
			  //
		      else  
		      {
			    bPlayRec = FALSE;
			    DlgRet = DialogBox(hInst, (LPSTR)"WMFDLG", hWndMain, WMFRecDlgProc);
		      }
            }

	       } //bPlayList
		   //
           //stepping records from the Play - Step menu option 
		   //
	       else  
	       {
			 //
             //init a flag and show the record contents 
			 //
	         bPlayRec = FALSE;
	         iCount = (iCount < iLBItemsInBuf) ? ++iCount : iCount;
	         DlgRet = DialogBox(hInst, (LPSTR)"WMFDLG", hWndMain, WMFRecDlgProc);
	       }
         } //end of STEPPING the metafile
		 //
         //bPlayItAll is TRUE.  This is set when the user either
         //selects the menu option Play - All or pushes the GO button
         //in the view record dialog box 
		 //
	     else  
	     {
		   //
           //we were stepping records selected from the listbox and
           //the user pressed the GO button
		   //
	       //Don't bother returning 0 to stop enumeration.  We need to
	       //play to the end of the metafile in this case anyway 
		   //
           if (bPlayList)  
           {
			 //
             //we were playing the selected records 
			 //
	         if (bPlaySelList)  
	         {
			   //
               //if all of the selected records have been played then
               //stop the enumeration 
			   //
		       if (iCount == iNumSel)
		         return(0);
			   //
               //set bPlayRec so the record will be played without user
               //interation and then update the record counter 
			   //
		       if ((WORD)lpSelMem[iCount] == iRecNum - 1)  
		       {
		         bPlayRec = TRUE;
		         iCount = (iCount < iLBItemsInBuf) ? ++iCount : iCount;
		       }
		       else
				 //
                 //it wasn't one of the selected records so don't play 
				 //
		         bPlayRec = FALSE;
		     }
			 //
             //we were playing the unselected records 
			 //
	         else  
	         {
			   //
               //if it is a selected record then set bPlayRec to FALSE
               //so the record is not played 
			   //
		       if ((WORD)lpSelMem[iCount] == iRecNum - 1)	
		       {
		         bPlayRec = FALSE;
		         iCount = (iCount < iLBItemsInBuf) ? ++iCount : iCount;
		       }
		       else
			     //
                 //play the record 
				 //
		         bPlayRec = TRUE;
	         }
	       } //bPlayList
         } //GO button pushed
		 //
	     //Stop the enumeration if you were stepping a range and have
         //finished playing that range OR the user selected pushed
         //the STOP button in the view record dialog box 
		 //
	     if ( ((bEnumRange) && (iRecNum > (WORD)iEndRange)) || (!DlgRet) )	
	     {
            bPlayRec = FALSE;
			//
			//stop enumeration
			//
            return(0);
         }

       } //if (hMem)
       else
		  //
          //we were unable to allocate memory for the record 
		  //
          MessageBox(hWndMain, "Memory allocation failed",
                     NULL, MB_OK | MB_ICONHAND);
       //
       //Regardless of the method the user elected to play the
       //records, check the flag.  If it is set then play the
       //record 
	   //
       if (bPlayRec)
	     if (bEnhMeta)
           PlayEnhMetaFileRecord(hDC, lpHTable, lpEMFR, (UINT)nObj);
		 else
		   PlayMetaFileRecord(hDC, lpHTable, lpMFR, (UINT)nObj);
	   //
       //done with the record so get rid of it 
	   //
       GlobalFree(hMem);
	   //
       //if we made it this far then continue the enumeration 
	   //
       return(1);
       break;

    case ENUMMFLIST:
       iRecNum++;
	   //
       //format the listbox string 
	   //
       wsprintf((LPSTR)szMetaFunction, (LPSTR)"%d - ", iRecNum);
	   //
	   //get the function number contained in the record 
	   //
	   if (bEnhMeta)
         emfMetaRec.iType = lpEMFR->iType;
	   else
	     MetaRec.rdFunction = lpMFR->rdFunction;
	   //
	   //lookup the function number in the structure MetaFunctions 
	   //
       for (i = 0; i < ((bEnhMeta) ? NUMENHMETARECORDS : NUMMETAFUNCTIONS); i++)  
       {
	     if (bEnhMeta)
		 {
           if ((DWORD)lpEMFR->iType == emfMetaRecords[i].iType)
             break;
		 }
		 else
		 {
	       if ((DWORD)lpMFR->rdFunction == MetaFunctions[i].value)
             break;
		 }
       }
	   //
       //if the function number is not found then describe this record
       //as an "Unknown" type otherwise use the corresponding name
       //found in the lookup 
	   //
	   if (bEnhMeta)
	   {
         if (emfMetaRec.iType != emfMetaRecords[i].iType)
           lstrcat((LPSTR)szMetaFunction, (LPSTR)"Unknown");
         else
           lstrcat((LPSTR)szMetaFunction,(LPSTR)emfMetaRecords[i].szRecordName);
	   }
	   else
	   {
         if (MetaRec.rdFunction != MetaFunctions[i].value)
           lstrcat((LPSTR)szMetaFunction, (LPSTR)"Unknown");
         else
           lstrcat((LPSTR)szMetaFunction,(LPSTR)MetaFunctions[i].szFuncName);
	   }
	   //
       //add the string to the listbox 
	   //
       SendDlgItemMessage(CurrenthDlg, IDL_LBREC, LB_ADDSTRING, 0,
                          (LONG)(LPSTR)szMetaFunction);
	   //
       //keep enumerating 
	   //
       return(1);

       break;
  }
}

/***********************************************************************

  FUNCTION   : ConvertEMFtoWMF

  PARAMETERS : HENHMETAFILE hEMF - handle to enhanced metafile
               LPSTR lpszFileName - filename of disked based metafile


  PURPOSE    : Convert an Windows metafile to an enhanced metafile

  MESSAGES   : none

  RETURNS    : int

  COMMENTS   : 
  
  HISTORY    : created 7/22/93 - denniscr

************************************************************************/

BOOL ConvertWMFtoEMF(HMETAFILE hmf, LPSTR lpszFileName)
{
  LPSTR        lpWinMFBits;
  UINT         uiSizeBuf;
  HENHMETAFILE hEnhMF;
  BOOL         bRet = TRUE;
  //
  //get the size of the Windows metafile associated with hMF
  //
  if ((uiSizeBuf = GetMetaFileBitsEx(hMF, 0, NULL)))
  {
    //
    //allocate enough memory to hold metafile bits
    //
    lpWinMFBits = GlobalAllocPtr(GHND, uiSizeBuf);
    //
    //get the bits of the Windows metafile associated with hMF
    //
    if (lpWinMFBits && GetMetaFileBitsEx(hMF, uiSizeBuf, (LPVOID)lpWinMFBits))
    {
      //
      //copy the bits into a memory based enhanced metafile
      //
      hEnhMF = SetWinMetaFileBits(uiSizeBuf, (LPBYTE)lpWinMFBits, NULL, NULL);
      //
      //copy the enhanced metafile to a disk based enhanced metafile
      //
      CopyEnhMetaFile(hEnhMF, lpszFileName);
      //
      //done with the memory base enhanced metafile so get rid of it
      //
      DeleteEnhMetaFile(hEnhMF);
      //
      //done with the actual memory used to store bits so nuke it
      //
      GlobalFreePtr(lpWinMFBits);
    }
    else
      bRet = FALSE;
  }
  else
    bRet = FALSE;
  return (bRet);
}

/***********************************************************************

  FUNCTION   : ConvertEMFtoWMF

  PARAMETERS : HENHMETAFILE hEMF - handle to enhanced metafile
               LPSTR lpszFileName - filename of disked based metafile


  PURPOSE    : Convert an enhanced metafile to an Windows metafile

  MESSAGES   : none

  RETURNS    : int

  COMMENTS   : 
  
  HISTORY    : created 7/22/93 - denniscr

************************************************************************/

BOOL ConvertEMFtoWMF(HDC hrefDC, HENHMETAFILE hEMF, LPSTR lpszFileName)
{
  LPSTR        lpEMFBits;
  UINT         uiSizeBuf;
  HMETAFILE    hWMF;
  BOOL         bRet = TRUE;
  //
  //get the size of the Windows metafile associated with hMF
  //
  if ((uiSizeBuf = GetWinMetaFileBits(hemf, 0, NULL, MM_TEXT, hrefDC)))
  {
    //
    //allocate enough memory to hold metafile bits
    //
    lpEMFBits = GlobalAllocPtr(GHND, uiSizeBuf);
    //
    //get the bits of the enhanced metafile associated with hEMF
    //
    if (lpEMFBits && GetWinMetaFileBits(hEMF, uiSizeBuf,(LPBYTE)lpEMFBits, 
                                        MM_TEXT, hrefDC))

    {
      //
      //copy the bits into a memory based Windows metafile
      //
      hWMF = SetMetaFileBitsEx(uiSizeBuf, (LPBYTE)lpEMFBits);
      //
      //copy the Windows metafile to a disk based Windows metafile
      //
      CopyMetaFile(hWMF, lpszFileName);
      //
      //done with the memory base enhanced metafile so get rid of it
      //
      DeleteMetaFile(hMF);
      //
      //done with the actual memory used to store bits so nuke it
      //
      GlobalFreePtr(lpEMFBits);
    }
    else 
      bRet = FALSE;
  }
  else
    bRet = FALSE;
  return (bRet);
}
