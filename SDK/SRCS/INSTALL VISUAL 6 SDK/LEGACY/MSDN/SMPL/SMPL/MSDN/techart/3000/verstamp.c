// This code was derived from:
//------------------------------------------------------------------------
// File name: verstamp.c                            Creation date: 911204
//
// Abstract:  Sample to demonstrate version information API from VER.DLL
//
// Which Demonstrates the following functions:
//
//    GetFileVersionInfo      - Returns version information about a file
//    GetFileVersionInfoSize  - Returns the size of a file's version
//                              information
//    GetSystemDirectory      - Returns the Windows system subdirectory
//    GetWindowsDirectory     - Returns the Windows directory
//    VerFindFile             - Determines where to install a file
//    VerInstallFile          - Installs a file using version info
//    VerLanguageName         - Converts a binary language ID into a string
//    VerQueryValue           - Returns version information about a block
//
// Written by Microsoft Product Support Services, Windows Developer Support.
//
// Copyright (c) 1991 Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------
// Modified for native VB Functions by
// Ken Lassesen
// Microsoft Developers Network
#include <windows.h>
#include <ver.h>                      // version info header
#include <stdlib.h>                   // for _MAX_PATH
#include <stdio.h>                   // for _MAX_PATH
#include <vbapi.h>			// for HLSTR etc.
#include  <string.h>			// for strLen
#include "nativevb.h"
#include "verstamp.h"                 // Header for this program


// Determines if the file has version information   
//---------------------------------------------------------------------------
//
//     Function:  HasVerInfo()
//
//      Purpose:  Allows User to determine if integration should occur.
//
//   Parameters: szFullPath     - File to check
//
// Return Value:  True/False
//
//     Comments:
//
// Date      Reason
// ----      ------
// 940803    Function created
//
//-------------------------------------------------------------------------
int Len;                 

#define BUFFERLEN 4096 //Because of arrays of strings!
char szBuffer[BUFFERLEN];
BOOL __export _pascal HasVerInfo(LPSTR szFullPath)
{
  DWORD dwVerInfoSize;
  DWORD dwVerHnd;
  
  // You must find the file size first before getting any file info
  dwVerInfoSize =
    GetFileVersionInfoSize(szFullPath, &dwVerHnd);

  if (dwVerInfoSize)
    {
    return TRUE;                      // return success
    }

  else
    {
    return FALSE;                     // return failure
    }
}

                                                                           
HLSTR _pascal __export vbGetVerInfo(LPSTR szFullPath, int item)
{
	switch (item)
	{                    
	 	case 0:// "1-8 Returned"     ,
		case 1://"CompanyName"
		case 2://"FileDescription"
		case 3://"FileVersion"
		case 4:// "InternalName" 
		case 5:// "LegalCopyright"
		case 6://"LegalTrademarks"  
		case 7://"ProductName"
		case 8://"ProductVersion
			return MoreVerInfo(szFullPath,item);
		default:                                
			return ShowVerInfo(szFullPath,item);
	}
}	
		
		
//---------------------------------------------------------------------------
//
//     Function:  ShowVerInfo()
//
//      Purpose:  Called after there is a file to get version info on
//
//   Parameters:  hWnd      - handle to the window that owns the dialog
//                szDir     - path
//                szFile    - file name
//                wDlgItem  - the starting dialog item
//
// Return Value:  void
//
//     Comments:
//
// Date      Reason
// ----      ------
// 911207    Function created
//
//-------------------------------------------------------------------------
HLSTR  ShowVerInfo(LPSTR szFullPath, int item)
{
  DWORD dwVerInfoSize;
  DWORD dwVerHnd;
  
  // You must find the file size first before getting any file info
  dwVerInfoSize =
    GetFileVersionInfoSize(szFullPath, &dwVerHnd);

  if (dwVerInfoSize)
    {
    LPSTR   lpstrVffInfo;             // Pointer to block to hold info
    HANDLE  hMem;                     // handle to mem alloc'ed
    HLSTR hlstr;
    // Get a block big enough to hold version info
    hMem          = GlobalAlloc(GMEM_MOVEABLE, dwVerInfoSize);
    lpstrVffInfo  = GlobalLock(hMem);

    // Get the info and fill in the pertinent dialog components
    if(GetFileVersionInfo(szFullPath, 0L, dwVerInfoSize, lpstrVffInfo))
    	hlstr=FillVerDialog((VS_VERSION FAR *)lpstrVffInfo, item);
    else
    	hlstr=NULL;
    

    // Let go of the memory
    GlobalUnlock(hMem);
    GlobalFree(hMem);
    return hlstr;                      // return success
    }

  else
    {
    return NULL;                     // return failure
    }
}


//---------------------------------------------------------------------------
//
//     Function:  void FillVerDialog
//
//   Parameters:  hWnd      - window handle
//                *pVerInfo - points to ver info block
//                wDlgItem  - starting point to fill dialog items
//
//      Purpose:  fills in the dialog components with the version
//                info.
//
// Return Value:  void
//
// Date      Reason
// ----      ------
// 920108    Function created
//
//--------------------------------------------------------------------------
HLSTR FillVerDialog( VS_VERSION FAR *pVerInfo, int i)
{
  DWORD           dwNum;              // to make this more readable
  UINT		  wNum; 	      // for call to VerQueryValue
  LANGANDCP FAR   *lpTrans;           // holds lang and codepage
  HLSTR hlstr;
 switch (i) 
 {
	case 9:  
  	// fill in the file version
  	Len = sprintf(szBuffer,
            "%d.%d.%d.%d",
            HIWORD(pVerInfo->vffInfo.dwFileVersionMS),
            LOWORD(pVerInfo->vffInfo.dwFileVersionMS),
            HIWORD(pVerInfo->vffInfo.dwFileVersionLS),
            LOWORD(pVerInfo->vffInfo.dwFileVersionLS));    
            hlstr = VBCreateTempHlstr(szBuffer, Len);
	  		VALIDHLSTR(hlstr); 
	  		return hlstr;

	case 10:
  	// fill in the product version
  	Len = sprintf(szBuffer,
            "%d.%d.%d.%d",
            HIWORD(pVerInfo->vffInfo.dwProductVersionMS),
            LOWORD(pVerInfo->vffInfo.dwProductVersionMS),
            HIWORD(pVerInfo->vffInfo.dwProductVersionLS),
            LOWORD(pVerInfo->vffInfo.dwProductVersionLS));
            hlstr = VBCreateTempHlstr(szBuffer, Len);
	  		VALIDHLSTR(hlstr); 
	  		return hlstr;
	case 11:
  	// File flags are bitwise or'ed so there can be more than one.
  	// dwNum is used to make this easier to read
  	dwNum = pVerInfo->vffInfo.dwFileFlags;
  	Len = sprintf(szBuffer, "%s %s %s %s %s %s %s",
           (LPSTR) (VS_FF_DEBUG         & dwNum ? "Debug"   : ""),
           (LPSTR) (VS_FF_PRERELEASE    & dwNum ? "PreRel"  : ""),
           (LPSTR) (VS_FF_PATCHED       & dwNum ? "Patched" : ""),
           (LPSTR) (VS_FF_PRIVATEBUILD  & dwNum ? "Private" : ""),
           (LPSTR) (VS_FF_INFOINFERRED  & dwNum ? "Info"    : ""),
           (LPSTR) (VS_FF_DEBUG         & dwNum ? "Special" : ""),
           (LPSTR) (0xFFFFFF00L         & dwNum ? "Unknown" : ""));
            hlstr = VBCreateTempHlstr(szBuffer, Len);
	  		VALIDHLSTR(hlstr); 
	  		return hlstr;
	case 12:                           
  	// OS type - there should be only one of these
  	switch (pVerInfo->vffInfo.dwFileOS)
    {
    case VOS_DOS_WINDOWS16:
      Len = sprintf(szBuffer, "DOS-Win16");
      break;

    case VOS_DOS_WINDOWS32:
      Len = sprintf(szBuffer, "DOS-Win32");
      break;

    case VOS_OS216_PM16:
      Len = sprintf(szBuffer, "OS/2-16 PM-16");
      break;

    case VOS_OS232_PM32:
      Len = sprintf(szBuffer, "OS/2-32 PM-32");
      break;

    case VOS_NT_WINDOWS32:
      Len = sprintf(szBuffer, "NT-Win32");
      break;

    case VOS_UNKNOWN:
    default:
      Len = sprintf(szBuffer, "Unknown");
      break;
    }
              hlstr = VBCreateTempHlstr(szBuffer, Len);
	  		VALIDHLSTR(hlstr); 
	  		return hlstr;

case 13:
  // Type of file
  switch (pVerInfo->vffInfo.dwFileType)
    {
    case VFT_APP:
      Len = sprintf(szBuffer, "App");
      break;

    case VFT_DLL:
      Len = sprintf(szBuffer, "DLL");
      break;

    case VFT_DRV:
      Len = sprintf(szBuffer, "Driver");
      break;

    case VFT_FONT:
      Len = sprintf(szBuffer, "Font");
      break;

    case VFT_VXD:
      Len = sprintf(szBuffer, "VxD");
      break;

    case VFT_STATIC_LIB:
      Len = sprintf(szBuffer, "Lib");
      break;

    case VFT_UNKNOWN:
    default:
      Len = sprintf(szBuffer, "Unknown");
      break;

    }
              hlstr = VBCreateTempHlstr(szBuffer, Len);
	  		VALIDHLSTR(hlstr); 
	  		return hlstr;

case 14:
  // Depending on the file type we look at a subset of file subtypes
  switch (pVerInfo->vffInfo.dwFileType)
    {
    case VFT_FONT:
      switch (pVerInfo->vffInfo.dwFileSubtype)
        {
        case VFT2_FONT_RASTER:
          Len = sprintf(szBuffer, "Raster font");
          break;

        case VFT2_FONT_VECTOR:
          Len = sprintf(szBuffer, "Vector font");
          break;

        case VFT2_FONT_TRUETYPE:
          Len = sprintf(szBuffer, "TrueType font");
          break;
        }
      break;

    case VFT_DRV:
      switch (pVerInfo->vffInfo.dwFileSubtype)
        {
        case VFT2_DRV_PRINTER:
          Len = sprintf(szBuffer, "Printer drv");
          break;

        case VFT2_DRV_KEYBOARD:
          Len = sprintf(szBuffer, "Keyboard drv");
          break;

        case VFT2_DRV_LANGUAGE:
          Len = sprintf(szBuffer, "Language drv");
          break;

        case VFT2_DRV_DISPLAY:
          Len = sprintf(szBuffer, "Display drv");
          break;

        case VFT2_DRV_MOUSE:
          Len = sprintf(szBuffer, "Mouse drv");
          break;

        case VFT2_DRV_NETWORK:
          Len = sprintf(szBuffer, "Network drv");
          break;

        case VFT2_DRV_SYSTEM:
          Len = sprintf(szBuffer, "System drv");
          break;

        case VFT2_DRV_INSTALLABLE:
          Len = sprintf(szBuffer, "Installable");
          break;

        case VFT2_DRV_SOUND:
          Len = sprintf(szBuffer, "Sound drv");
          break;

        case VFT2_DRV_COMM:
          Len = sprintf(szBuffer, "Comm drv");
          break;

        case VFT2_UNKNOWN:
        default:
          Len = sprintf(szBuffer, "Unknown");
          break;
        }
      break;

      default:
        Len = sprintf(szBuffer, "Unknown");
        break;
    }
              hlstr = VBCreateTempHlstr(szBuffer, Len);
	  		VALIDHLSTR(hlstr); 
	  		return hlstr;
case 15:

  // Finally, show the language of the file.  First query the
  // verinfo block for the translation and then pass this onto
  // the VerLanguageName to get the string.  Finally, set the
  // dialog item.
  VerQueryValue   (pVerInfo, (LPCSTR)gszTrans, (void FAR* FAR*)&lpTrans,(UINT FAR*) &wNum);
  VerLanguageName (lpTrans->wLanguage, szBuffer, BUFFERLEN- 1);
              hlstr = VBCreateTempHlstr(szBuffer, Len);
	  		VALIDHLSTR(hlstr); 
	  		return hlstr;      
}                       
return NULL;
}

HLSTR FAR PASCAL MoreVerInfo (LPSTR szFullPath, int i)  
{
  LPSTR   lpVersion;
  DWORD   dwVerInfoSize;
  DWORD   dwVerHnd;
  WORD    wVersionLen;
  BOOL    bRetCode;  
  HLSTR hlstr=NULL;
 char    szGetName[BUFFERLEN];
      // Get the file version info size
      dwVerInfoSize = GetFileVersionInfoSize(szFullPath, &dwVerHnd);

      if (dwVerInfoSize)
        {
        LPSTR   lpstrVffInfo;
        HANDLE  hMem;

        // allocate memory to hold the verinfo block
        hMem          = GlobalAlloc(GMEM_MOVEABLE, dwVerInfoSize);
        lpstrVffInfo  = GlobalLock(hMem);

        GetFileVersionInfo(szFullPath, dwVerHnd,
           dwVerInfoSize, lpstrVffInfo);

        // Do this the American english translation be default.
        // Keep track of the string Length for easy updating.
        // 040904E4 represents the language ID and the four
        // least significant digits represent the codepage for
        // which the data is formatted.  The language ID is
        // composed of two parts: the low ten bits represent
        // the major language and the high six bits represent
        // the sub language.

        sprintf(szGetName, "\\StringFileInfo\\040904E4\\");

        // Get data item from Ver structure.  This uses the
        // gszVerString array to get the various component
        // ver strings.  The contents of the gszVerString are:

        // "Illegal string"  "CompanyName"   "FileDescription",
        // "FileVersion"     "InternalName"  "LegalCopyright"
        // "LegalTrademarks" "ProductName"   "ProductVersion

        if ((i >= 1) && (i <= 8))
          {
          lstrcat(szGetName, gszVerString[i]);
          wVersionLen   = 0;
          lpVersion     = NULL;

          // Look for the corresponding string.
          bRetCode      =  VerQueryValue((LPVOID)lpstrVffInfo,
					  (LPSTR)szGetName,
					  (void FAR* FAR*)&lpVersion,
					  (UINT FAR *) &wVersionLen);

          if ( bRetCode && wVersionLen && lpVersion)
            {
            Len = sprintf(szBuffer,"%s", lpVersion);
            hlstr = VBCreateTempHlstr(szBuffer, Len);
	  		VALIDHLSTR(hlstr); 
            }
          }
		if( i < 1)    // Put all in with the string!
		{  
		  Len=0;
		  for(i=1; i < 9; i++)
		  {
		  	sprintf(szGetName, "\\StringFileInfo\\040904E4\\");
          	lstrcat(szGetName, gszVerString[i]);
          	wVersionLen   = 0;
          	lpVersion     = NULL;
            // Look for the corresponding string.
          	bRetCode      =  VerQueryValue((LPVOID)lpstrVffInfo,
					  (LPSTR)szGetName,
					  (void FAR* FAR*)&lpVersion,
					  (UINT FAR *) &wVersionLen);
		    if (lpVersion) //must not be null
            if (Len + strlen(lpVersion) < BUFFERLEN) //Make sure no overrun
          		if ( bRetCode && wVersionLen && lpVersion)
                  	Len += sprintf(szBuffer+Len,"%s\t", lpVersion);
            	else                                                  
              		Len += sprintf(szBuffer+Len,"\t");
	        
	       }
    	   	hlstr = VBCreateTempHlstr(szBuffer, Len);
	  		VALIDHLSTR(hlstr); 
          }
        GlobalUnlock(hMem);
        GlobalFree(hMem);
        }
		return hlstr;
}

