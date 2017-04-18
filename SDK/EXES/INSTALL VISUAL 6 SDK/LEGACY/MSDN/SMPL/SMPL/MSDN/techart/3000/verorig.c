//------------------------------------------------------------------------
// File name: verstamp.c                            Creation date: 911204
//
// Abstract:  Sample to demonstrate version information API from VER.DLL
//
// Demonstrates the following functions:
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
#include <windows.h>
#include <commdlg.h>                  // Common dialog header
#include <ver.h>                      // version info header
#include <stdlib.h>                   // for _MAX_PATH
#include "verstamp.h"                 // Header for this program

//-------------------------------------------------------------------------
//
// Function:    WinMain()
//
// Purpose:     Main window procedure - initializes window data
//
// Parameters:  hInstance
//              hPrevious
//              lpCmdLine
//              nCmdShow
//
// Return Val:  msg.wParam
//
// Comments:    Used a dialog for the main window.  This is modeled
//              after Petzold's hexcalc program.  The important things
//              to remember are:
//              1) use DLGWINDOWEXTRA in the cbWndExtra member of the
//                 window class
//              2) make sure the class statement in the rc file matches
//                 classname member of the window class structure
//
// Date      Reason
// ----      ------
// 911204    Function created
//
//--------------------------------------------------------------------------
int PASCAL WinMain(HANDLE hInstance,
                   HANDLE hPrevInstance,
                   LPSTR  lpCmdLine,
                   int    nCmdShow)
{
  WNDCLASS  WndClass;                 // window class structure
  HWND      hWnd;                     // window handle
  MSG       msg;                      // message

  if (!hPrevInstance)
    {
    WndClass.style          = 0;
    WndClass.lpfnWndProc    = WndProc;
    WndClass.cbClsExtra     = 0;
    WndClass.cbWndExtra     = DLGWINDOWEXTRA;
    WndClass.hInstance      = hInstance;
    WndClass.hIcon          = LoadIcon(hInstance, "VerStampIcon");
    WndClass.hCursor        = LoadCursor(NULL, IDC_ARROW);
    WndClass.hbrBackground  = COLOR_WINDOW+1;
    WndClass.lpszMenuName   = "VerStampMenu";
    WndClass.lpszClassName  = gszAppName;

    RegisterClass(&WndClass);
    }

  // Use this call to create the window.  Be sure to allocate
  // extra bytes for the window using DLGWINDOWEXTRA and make
  // sure that the class is included in the rc file.

  if (!(hWnd = CreateDialog(hInstance, gszAppName, 0, NULL)))
    return FALSE;

  ghInst  = hInstance;                // Set global instance handle

  ShowWindow(hWnd, nCmdShow);
  while (GetMessage(&msg,NULL,NULL,NULL))
    {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
    }
  return (msg.wParam);
}

//------------------------------------------------------------------------
//
//     Function:  WndProc()
//
//      Purpose:  Window procedure for version info sample
//
//   Parameters:  hWnd    - Window handle
//                wMsg    - Message
//                wParam  - Word parameter
//                lParam  - Long parameter
//
// Return Value:  DefWindowProc()
//                NULL
//
//     Comments:
//
// Date      Reason
// ----      ------
// 911204    Function created
//
//-------------------------------------------------------------------------
long FAR PASCAL __export WndProc(HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam)
{
  FARPROC lpProcAbout;                // About function ptr
  FARPROC lpProcMoreVerInfo;          // About function ptr
  WORD    wRes;                       // WORD ret value
  DWORD   dwRes;                      // DWORD ret value

  switch (wMsg)
    {
    case WM_CREATE:

      // Get the files in the windows/system directory.
      // The sample uses this as a default directory to
      // obtain version stamp information.  Could have
      // just as easily used the current directory.  DOS
      // programs would use the GetSystemDir function.
      GetSystemDirectory((LPSTR) gszSrcDir, (BUFLEN - 1));
      break;

    case WM_COMMAND:
	    switch (wParam)
		    {
		    case IDM_ABOUT:
          // Do the about dialog box

          lpProcAbout = MakeProcInstance(About, ghInst);
          DialogBox(ghInst, "AboutBox", hWnd, lpProcAbout);
          FreeProcInstance(lpProcAbout);
          break;

        case IDM_FILEOPEN:
          // Open the file using the common dialog open file
          // and get the version information

          gszSrcFile[0] = '\0';       // For GetOpenFileName

          // Do the open file dialog to get the source file name
          // and the source directory name.  The file name will
          // only have the file and extension, not the path.

          if (MyGetOpenFileName(hWnd, gszSrcDir, gszSrcFile))

            // Show the version stamp info in the dialog

            if (ShowVerInfo(hWnd, gszSrcDir, gszSrcFile, DLG_SRCFILENAME))
              {
              // Since we have version stamp information, turn
              // on the VerInstall button in the dialog.

              EnableWindow(GetDlgItem(hWnd, IDD_VERINSTALL), TRUE);
              EnableWindow(GetDlgItem(hWnd, IDD_MOREINFO),   TRUE);

              // Put the focus on the More info... button
              SetFocus(GetDlgItem(hWnd, IDD_MOREINFO));
              }

            else
              {
              // Since we don't have version stamp info, be sure to
              // turn off the VerInstall button.

              EnableWindow (GetDlgItem(hWnd, IDD_MOREINFO),   FALSE);
              EnableWindow (GetDlgItem(hWnd, IDD_VERINSTALL), FALSE);
              }

          break;

        case IDD_MOREINFO:
          // Show the dialog that contains the string information
          // about the file

          lpProcMoreVerInfo = MakeProcInstance(MoreVerInfo, ghInst);
          DialogBox(ghInst, "MoreVerInfo", hWnd, lpProcMoreVerInfo);
          FreeProcInstance(lpProcMoreVerInfo);
          break;

        case IDD_VERINSTALL:
          // Attempt to install the file.  Since we don't want anyone
          // to overwrite a file inadvertently, we take care to proceed
          // with caution.

          // Look to see where Windows thinks you should install the file
          wRes = MyVerFindFile(hWnd, gszSrcDir, gszSrcFile, gszDstDir);

          // Show whatever information you can for the target file in
          // the destination side of the directory.

          ShowVerInfo(hWnd, gszDstDir, gszSrcFile, DLG_DSTFILENAME);

          // Show information about the return value off VerFindFile
          // and determine if the user wants to continue.

          if (HandleVerFindFileRes(hWnd, wRes, gszDstDir, gszSrcFile))
            {
            // Either the user has said that it is okay to continue
            // or VerFindFile has returned a 0 indicating that there
            // is no problem with proceeding to the call to VerInstall-
            // File.

            dwRes = MyVerInstallFile(gszSrcDir, gszSrcFile, gszDstDir);

            // If everything went ok - indicated by a zero return
            // value - then this is where you would perform any post
            // processing that needs to be done on the destination
            // file.  For instance, marking it as read only.  In our
            // particular case, we just let the user know that the
            // file was installed.

            if (!dwRes)
              PostInstallProcessing(hWnd, gszDstDir, gszSrcFile);

            else
              // If everything didn't go okay then we need to
              // deal with it.

              HandleVerInstallFileRes(hWnd, dwRes, gszDstDir, gszSrcFile);
            }

          // Disable the buttons and clear the dialog

          EnableWindow (GetDlgItem(hWnd, IDD_MOREINFO),   FALSE);
          EnableWindow (GetDlgItem(hWnd, IDD_VERINSTALL), FALSE);
          ClearDlgVer  (hWnd, DLG_DSTFILENAME);
          ClearDlgVer  (hWnd, DLG_SRCFILENAME);

          break;

        case IDM_EXIT:                // All done
          DestroyWindow(hWnd);
          break;

        default:
          return (DefWindowProc(hWnd, wMsg, wParam, lParam));
		    }
	    break;

    case WM_DESTROY:
      PostQuitMessage(0);
      break;

    case WM_PAINT:
      if (bFirst)                     // Do this on the 1st time through
        {
        // Set windows directory in dialog box.  DOS installation
        // programs would use the GetWindowsDir.
        GetWindowsDirectory((LPSTR) gszWinDir, (BUFLEN - 1));
        SetDlgItemText(hWnd, DLG_WINDIR, gszWinDir);

        // Set system subdirectory in dialog box

        GetSystemDirectory((LPSTR) gszSysDir, (BUFLEN - 1));
        SetDlgItemText(hWnd, DLG_SYSDIR, gszSysDir);

        bFirst = FALSE;               // Only the first paint message
        }                             // !! Drop through to DefWindowProc

    default:
      return (DefWindowProc(hWnd, wMsg, wParam, lParam));
    }

  return (NULL);
}

//------------------------------------------------------------------------
//
//     Function:  About()
//
//      Purpose:  Show the about box for the version info sample
//
//   Parameters:  hDlg    - Handle to the dialog Window
//                wMsg    - Message
//                wParam  - Word parameter
//                lParam  - Long parameter
//
// Return Value:  TRUE
//                FALSE
//
//     Comments:  Standard about box dialog
//
// Date      Reason
// ----      ------
// 911204    Function created
//
//--------------------------------------------------------------------------
BOOL FAR PASCAL __export About(HWND hDlg,      // Window handle for dialog
		      unsigned wMsg,	  // Dialog message
                      WORD wParam,    // Word parameter
                      LONG lParam)    // Long parameter

{
  switch (wMsg)
	  {
    case WM_INITDIALOG:               // Initialize dialog
      return (TRUE);

    case WM_COMMAND:                  // Look for dialog command message
		  switch(wParam)
			  {
    	  case IDOK:                    // User pressed OK button
			  case IDCANCEL:                // Dialog's been canceled
				  EndDialog(hDlg, TRUE);
				  return TRUE;

			  default:
				  break;
  		  }
		  break;

	  default:
		  break;
	  }
  return FALSE;                       // Not done yet
}


//--------------------------------------------------------------------------
//
//     Function:  MyGetOpenFileName
//
//      Purpose:  Fills in the directory and file using the
//                GetOpenFileName API in the common dialog.
//
//   Parameters:  hWnd    - handle to the window
//                szDir   - pointer to the string that will
//                          be filled in with the dir name.
//                          If this is initialized coming into
//                          the function, it will be used as the
//                          default directory.
//                szFile  - pointer to the string that will
//                          be filled with the file name,
//                          including the extension
//
//     Comments:  The filter that this function uses for the call
//                to the open file dialog is initialized to DLL's,
//                .EXE's, and .DRV.
//
// Return Value:  TRUE or FALSE
//
// Date      Reason
// ----      ------
// 911207    Function created
//
//------------------------------------------------------------------------
BOOL MyGetOpenFileName(HWND  hWnd, LPSTR szDir, LPSTR szFile)
{
  OPENFILENAME  ofn;
  char          szofnFile[BUFLEN];
  char          szofnDir[_MAX_PATH];
  char          szFileTitle[BUFLEN];
  char         *szFilter [] = {"EXE's, DLL's, and DRV'S",
                                "*.exe; *.dll; *.drv", ""};

  // Initialize the OPENFILENAME members
  lstrcpy(szofnDir, szDir);           // Use as default

  szofnFile[0]           =  '\0';

  ofn.lStructSize        = sizeof(OPENFILENAME);
  ofn.hwndOwner          = hWnd;
  ofn.lpstrFilter        = szFilter[0];
  ofn.lpstrCustomFilter  = (LPSTR) NULL;
  ofn.nMaxCustFilter     = 0L;
  ofn.nFilterIndex       = 1L;
  ofn.lpstrFile          = szofnFile;
  ofn.nMaxFile           = sizeof(szofnFile);
  ofn.lpstrFileTitle     = szFileTitle;
  ofn.nMaxFileTitle      = sizeof(szFileTitle);
  ofn.lpstrInitialDir    = szofnDir;
  ofn.lpstrTitle         = gszAppName;
  ofn.Flags              = OFN_SHOWHELP | OFN_PATHMUSTEXIST |
                              OFN_FILEMUSTEXIST;
  ofn.nFileOffset        = 0;
  ofn.nFileExtension     = 0;
  ofn.lpstrDefExt        = (LPSTR) NULL;

  // Call GetOpenFilename to fill in the filename and dirname
  if (GetOpenFileName(&ofn))
    {
    // Copy the results into the file
    lstrcpy(szFile, &ofn.lpstrFile[ofn.nFileOffset]);

    // Get the dir.  Since the ofn.file has the path and the
    // file we have to truncate the path at the ofn.fileoffset
    // character.
    lstrcpy(szDir, ofn.lpstrFile);
    szDir[ofn.nFileOffset - 1] = '\0';

    return TRUE;                      // Success
    }

  else
    return FALSE;                     // Failure
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
BOOL ShowVerInfo(HWND hWnd, LPSTR szDir, LPSTR szFile, WORD wDlgItem)
{
  DWORD dwVerInfoSize;
  DWORD dwVerHnd;
  char szFullPath[_MAX_PATH];

  // Get file name in dialog control
  SetDlgItemText(hWnd, wDlgItem++,szFile);

  // Pick off directory name for dialog control
  SetDlgItemText(hWnd, wDlgItem++, szDir);

  // Make full path and file name for call to GetFileVersionInfoSize
  lstrcpy(szFullPath, szDir);
  lstrcat(szFullPath, "\\");
  lstrcat(szFullPath, szFile);

  // You must fine the file size first before getting any file info
  dwVerInfoSize =
    GetFileVersionInfoSize(szFullPath, &dwVerHnd);

  if (dwVerInfoSize)
    {
    LPSTR   lpstrVffInfo;             // Pointer to block to hold info
    HANDLE  hMem;                     // handle to mem alloc'ed

    // Get a block big enough to hold version info
    hMem          = GlobalAlloc(GMEM_MOVEABLE, dwVerInfoSize);
    lpstrVffInfo  = GlobalLock(hMem);

    // Get the info and fill in the pertinent dialog components
    if(GetFileVersionInfo(szFullPath, 0L, dwVerInfoSize, lpstrVffInfo))
      FillVerDialog(hWnd, (VS_VERSION FAR *)lpstrVffInfo, wDlgItem);

    // Let go of the memory
    GlobalUnlock(hMem);
    GlobalFree(hMem);
    return TRUE;                      // return success
    }

  else
    {
    // Clear the dialog if version info
    ClearDlgVer(hWnd, wDlgItem);
    wsprintf(gszUserMsg, "No Version info for %s", (LPSTR) szFullPath);
    MessageBox(hWnd, gszUserMsg, "VerStamp", MB_OK);
    return FALSE;                     // return failure
    }
}

//-----------------------------------------------------------------------
//
//     Function:  ClearDlgVer()
//
//      Purpose:  Clears the dialog of version information
//
//   Parameters:  hWnd    - window handle
//                DlgItem - dialog item to start with
//
// Return Value:  void
//
// Date      Reason
// ----      ------
// 911207    Function created
//-----------------------------------------------------------------------
void ClearDlgVer(HWND hWnd, int nDlgItem)
{
  int i;
  int nDlgGroupLimit;

  // See if the starting dialog item is in the source column

  if (nDlgItem >= DLG_SRCFILENAME && nDlgItem <= DLG_SRCLANGUAGE)
    nDlgGroupLimit = DLG_SRCLANGUAGE;

  // Default to the limit being in the destination info column
  else
    nDlgGroupLimit = DLG_DSTLANGUAGE;

  // Clear everything from the startin point to the ending point
  for (i=nDlgItem;  i<=nDlgGroupLimit; i++)
    SetDlgItemText(hWnd, i, gszDlgClear);
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
void FillVerDialog(HWND hWnd, VS_VERSION FAR *pVerInfo, WORD wDlgItem)
{
  DWORD           dwNum;              // to make this more readable
  UINT		  wNum; 	      // for call to VerQueryValue
  LANGANDCP FAR   *lpTrans;           // holds lang and codepage

  // fill in the file version
  wsprintf(gszUserMsg,
            "%d.%d.%d.%d",
            HIWORD(pVerInfo->vffInfo.dwFileVersionMS),
            LOWORD(pVerInfo->vffInfo.dwFileVersionMS),
            HIWORD(pVerInfo->vffInfo.dwFileVersionLS),
            LOWORD(pVerInfo->vffInfo.dwFileVersionLS));
  SetDlgItemText(hWnd, wDlgItem, gszUserMsg);

  // fill in the product version
  wsprintf(gszUserMsg,
            "%d.%d.%d.%d",
            HIWORD(pVerInfo->vffInfo.dwProductVersionMS),
            LOWORD(pVerInfo->vffInfo.dwProductVersionMS),
            HIWORD(pVerInfo->vffInfo.dwProductVersionLS),
            LOWORD(pVerInfo->vffInfo.dwProductVersionLS));
  SetDlgItemText(hWnd, ++wDlgItem, gszUserMsg);

  // File flags are bitwise or'ed so there can be more than one.
  // dwNum is used to make this easier to read
  dwNum = pVerInfo->vffInfo.dwFileFlags;
  wsprintf(gszUserMsg, "%s %s %s %s %s %s %s",
           (LPSTR) (VS_FF_DEBUG         & dwNum ? "Debug"   : ""),
           (LPSTR) (VS_FF_PRERELEASE    & dwNum ? "PreRel"  : ""),
           (LPSTR) (VS_FF_PATCHED       & dwNum ? "Patched" : ""),
           (LPSTR) (VS_FF_PRIVATEBUILD  & dwNum ? "Private" : ""),
           (LPSTR) (VS_FF_INFOINFERRED  & dwNum ? "Info"    : ""),
           (LPSTR) (VS_FF_DEBUG         & dwNum ? "Special" : ""),
           (LPSTR) (0xFFFFFF00L         & dwNum ? "Unknown" : ""));
  SetDlgItemText(hWnd, ++wDlgItem, gszUserMsg);

  // OS type - there should be only one of these
  switch (pVerInfo->vffInfo.dwFileOS)
    {
    case VOS_DOS_WINDOWS16:
      lstrcpy(gszUserMsg, "DOS-Win16");
      break;

    case VOS_DOS_WINDOWS32:
      lstrcpy(gszUserMsg, "DOS-Win32");
      break;

    case VOS_OS216_PM16:
      lstrcpy(gszUserMsg, "OS/2-16 PM-16");
      break;

    case VOS_OS232_PM32:
      lstrcpy(gszUserMsg, "OS/2-32 PM-32");
      break;

    case VOS_NT_WINDOWS32:
      lstrcpy(gszUserMsg, "NT-Win32");
      break;

    case VOS_UNKNOWN:
    default:
      lstrcpy(gszUserMsg, "Unknown");
      break;
    }
  SetDlgItemText(hWnd, ++wDlgItem, gszUserMsg);

  // Type of file
  switch (pVerInfo->vffInfo.dwFileType)
    {
    case VFT_APP:
      lstrcpy(gszUserMsg, "App");
      break;

    case VFT_DLL:
      lstrcpy(gszUserMsg, "DLL");
      break;

    case VFT_DRV:
      lstrcpy(gszUserMsg, "Driver");
      break;

    case VFT_FONT:
      lstrcpy(gszUserMsg, "Font");
      break;

    case VFT_VXD:
      lstrcpy(gszUserMsg, "VxD");
      break;

    case VFT_STATIC_LIB:
      lstrcpy(gszUserMsg, "Lib");
      break;

    case VFT_UNKNOWN:
    default:
      lstrcpy(gszUserMsg, "Unknown");
      break;

    }
  SetDlgItemText(hWnd, ++wDlgItem, gszUserMsg);

  // Depending on the file type we look at a subset of file subtypes
  switch (pVerInfo->vffInfo.dwFileType)
    {
    case VFT_FONT:
      switch (pVerInfo->vffInfo.dwFileSubtype)
        {
        case VFT2_FONT_RASTER:
          lstrcpy(gszUserMsg, "Raster font");
          break;

        case VFT2_FONT_VECTOR:
          lstrcpy(gszUserMsg, "Vector font");
          break;

        case VFT2_FONT_TRUETYPE:
          lstrcpy(gszUserMsg, "TrueType font");
          break;
        }
      break;

    case VFT_DRV:
      switch (pVerInfo->vffInfo.dwFileSubtype)
        {
        case VFT2_DRV_PRINTER:
          lstrcpy(gszUserMsg, "Printer drv");
          break;

        case VFT2_DRV_KEYBOARD:
          lstrcpy(gszUserMsg, "Keyboard drv");
          break;

        case VFT2_DRV_LANGUAGE:
          lstrcpy(gszUserMsg, "Language drv");
          break;

        case VFT2_DRV_DISPLAY:
          lstrcpy(gszUserMsg, "Display drv");
          break;

        case VFT2_DRV_MOUSE:
          lstrcpy(gszUserMsg, "Mouse drv");
          break;

        case VFT2_DRV_NETWORK:
          lstrcpy(gszUserMsg, "Network drv");
          break;

        case VFT2_DRV_SYSTEM:
          lstrcpy(gszUserMsg, "System drv");
          break;

        case VFT2_DRV_INSTALLABLE:
          lstrcpy(gszUserMsg, "Installable");
          break;

        case VFT2_DRV_SOUND:
          lstrcpy(gszUserMsg, "Sound drv");
          break;

        case VFT2_DRV_COMM:
          lstrcpy(gszUserMsg, "Comm drv");
          break;

        case VFT2_UNKNOWN:
        default:
          lstrcpy(gszUserMsg, "Unknown");
          break;
        }
      break;

      default:
        lstrcpy(gszUserMsg, gszDlgClear);
        break;
    }
  SetDlgItemText(hWnd, ++wDlgItem, gszUserMsg);

  // Finally, show the language of the file.  First query the
  // verinfo block for the translation and then pass this onto
  // the VerLanguageName to get the string.  Finally, set the
  // dialog item.
  VerQueryValue   (pVerInfo, (LPCSTR)gszTrans, (void FAR* FAR*)&lpTrans,(UINT FAR*) &wNum);
  VerLanguageName (lpTrans->wLanguage, gszUserMsg, BUFLEN - 1);
  SetDlgItemText  (hWnd, ++wDlgItem, gszUserMsg);
}

//---------------------------------------------------------------------------
//
//     Function:  WORD MyVerFindFile
//
//   Parameters:  hWnd      - Window handle
//                szSrcDir  - Source directory
//                szFile    - file name
//                szDstDir  - destination directory where VerFindFile
//                            thinks the file ought to be installed
//
//      Purpose:  A wrapper function for the call to VerFindFile.
//                Since we are not using the current dir in this
//                sample.
//
//     Comments:  VerFindFile was not working correctly for earlier
//                beta versions of 3.1.  It would return the windows
//                system subdirectory in inappropriate cases - that
//                is anytime you would specify a destination dir.
//
// Return Value:  VerFindFile - The return value is a bitmask that
//                indicates the status of the file.
//
// Date      Reason
// ----      ------
// 920108    Function created
//
//---------------------------------------------------------------------------
WORD MyVerFindFile(HWND   hWnd,
                   LPSTR  szSrcDir,
                   LPSTR  szFile,
                   LPSTR  szDstDir)
{
  WORD wCurDirLen = _MAX_PATH;
  WORD wDstDirLen = _MAX_PATH;

  // By default, the flag is set to 0.  If you were installing a
  // redistributable component of Window or if your file is to be
  // shared by other apps then you would want to set it to
  // VFFF_ISSHAREDFILE to make sure that it goes into the windows
  // system directory.

  return (VerFindFile(0,
                      szFile,
                      gszWinDir,
                      szSrcDir,
                      (LPSTR) gszCurDir,
                      (LPWORD) &wCurDirLen,
                      (LPSTR) szDstDir,
                      (LPWORD) &wDstDirLen));
}

//------------------------------------------------------------------------
//
//     Function:  DWORD MyVerInstallFile
//
//   Parameters:  szSrcDir  - source directory
//                szSrcFile - file name
//                szDstDir  - the destination dir
//
//      Purpose:  A wrapper function for the call to VerInstallFile
//
//      Comment:  This is a very simplified call to VerInstallFile.
//                In this sample we do now allow the user to change
//                the destination path.
//
// Return Value:  dwRet which is the return value from VerInstallFile.
//                This is a bit mask which indicates information about
//                the installation attemp.
//
// Date      Reason
// ----      ------
// 920108    Function created
//
//----------------------------------------------------------------------------
DWORD MyVerInstallFile(LPSTR szSrcDir,
                       LPSTR szSrcFile,
                       LPSTR szDstDir)
{
  char  szTmpFile[_MAX_PATH];         // VerInstallFile may create a temp file
  WORD  wTmpFileLen = _MAX_PATH;
  WORD  wVerFlags;
  DWORD dwRet;

  // Don't get rid of old file - afterall, this is a sample.  We don't
  // want to do anything too drastic.

  wVerFlags = VIFF_DONTDELETEOLD;

  // The VerInstallFile function attempts to install a file based
  // on information returned from the VerFindFile function.
  // VerInstallFile uncompresses the file with LZcopy and checks
  // for errors, such as outdated files.

  // The source and file names are the same in all cases for this
  // sample.

  dwRet = VerInstallFile(wVerFlags,
                         szSrcFile, szSrcFile,
                         szSrcDir,  szDstDir,
                         gszCurDir, szTmpFile, (LPWORD) &wTmpFileLen);
  return dwRet;
}

//---------------------------------------------------------------------------
//
//     Function:  MoreVerInfo()
//
//      Purpose:  Shows the user additional version information about
//                the file.
//
//   Parameters:  hDlg    -   handle to the dialog window
//                wMsg    -   dialog message
//                wParam  -   word parameter
//                lParam  -   long parameter
//
// Return Value:  TRUE or FALSE
//
//     Comments:  Uses the globals gszSrcDir and gszSrcFile
//
// Date      Reason
// ----      ------
// 911227    Function created
//
//-------------------------------------------------------------------------
BOOL FAR PASCAL __export MoreVerInfo
                     (HWND hDlg,    // Window handle for dialog
		      unsigned wMsg,	// Dialog message
                      WORD wParam,  // Word parameter
                      LONG lParam)  // Long parameter
{
  LPSTR   lpVersion;
  DWORD   dwVerInfoSize;
  DWORD   dwVerHnd;
  WORD    wVersionLen;
  WORD    wRootLen;
  BOOL    bRetCode;
  int     i;
  char    szFullPath[_MAX_PATH];
  char    szResult[BUFLEN];
  char    szGetName[BUFLEN];

  switch (wMsg)
	  {
    case WM_INITDIALOG:
      // Initialize dialog with the filename
      lstrcpy(szFullPath, gszSrcDir);
      lstrcat(szFullPath, "\\");
      lstrcat(szFullPath, gszSrcFile);

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
        // Keep track of the string length for easy updating.
        // 040904E4 represents the language ID and the four
        // least significant digits represent the codepage for
        // which the data is formatted.  The language ID is
        // composed of two parts: the low ten bits represent
        // the major language and the high six bits represent
        // the sub language.

        lstrcpy(szGetName, "\\StringFileInfo\\040904E4\\");
        wRootLen = lstrlen(szGetName);

        // Get data item from Ver structure.  This uses the
        // gszVerString array to get the various component
        // ver strings.  The contents of the gszVerString are:

        // "Illegal string"  "CompanyName"   "FileDescription",
        // "FileVersion"     "InternalName"  "LegalCopyright"
        // "LegalTrademarks" "ProductName"   "ProductVersion

        for (i = 1; i <= 8; i++)
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
            lstrcpy(szResult, lpVersion);
            SetDlgItemText(hDlg, DLG_COMPANYNAME + (i - 1) , szResult);
            }

          else if (i == 1)
            {
            // This is an attempt to special case the multimedia
            // extensions.  I think they paid attention to the
            // original docs which suggested that they use the
            // 0409 language ID and 0 codepage which indicates
            // 7 bit ASCII.

            lstrcpy(szGetName, "\\StringFileInfo\\04090000\\");
            i = 0;                    // be sure to reset the counter
            }

          // Be sure to reset to NULL so that we can concat
          szGetName[wRootLen] = NULL;
          }

        GlobalUnlock(hMem);
        GlobalFree(hMem);
        }

      return (TRUE);

    case WM_COMMAND:                  // Look for dialog command message
		  switch(wParam)
			  {
    	  case IDOK:                    // User pressed OK button
			  case IDCANCEL:                // Dialog's been canceled
				  EndDialog(hDlg, TRUE);
				  return TRUE;

			  default:
				  break;
  		  }
		  break;

	  default:
		  break;
	  }
  return FALSE;                       // Not done yet
}

//----------------------------------------------------------------------
//
//     Function:  HandleVerFindFileRes()
//
//      Purpose:  Handles the return from VerFindFile - showing asking the
//                user if they want to continue.
//
//   Parameters:  hWnd    - Handle to the window
//                wRes    - the return value from the call to
//                          VerFindFile
//                szDir   - the directory specification
//                szFile  - the file name
//
// Return Value:  TRUE    - if the user wants to continue
//                FALSE   - if the user doesn't want to continue
//
// Date      Reason
// ----      ------
// 911231    Function created
//
//-------------------------------------------------------------------------
BOOL PASCAL HandleVerFindFileRes(HWND   hWnd,
                                 WORD   wRes,
                                 LPSTR  szDir,
                                 LPSTR  szFile)
{
  char szBuf[BUFLEN];

  // If the return value from VerFindFile is 0 then everything
  // is okay and we can proceed to VerInstallFile right away

  if (!wRes)
    return TRUE;

  // Make sure that we are starting with no message
  gszUserMsg[0] = '\0';

  // Is the file in recommended destination directory?
  // Beta versions of VerFindFile would always report that
  // the file wasn't where it was supposed to be.

  if (VFF_CURNEDEST & wRes)
    {
    wsprintf(szBuf,
             "%s\\%s is not in the recomended destination:",
              szDir, szFile);
    lstrcat(gszUserMsg, szBuf);
    }

  // Is the file currently in use?
  if (VFF_FILEINUSE & wRes)
    {
    wsprintf(szBuf,
             " %s\\%s is currently in use:",
             (LPSTR) gszCurDir, szFile);
    lstrcat(gszUserMsg, szBuf);
    }

  // Are the buffers too small to hold the directory names?
  if (VFF_BUFFTOOSMALL & wRes)
    {
    wsprintf(szBuf,
             " Buffer size is too small to hold dir strings:");
    lstrcat(gszUserMsg, szBuf);
    }

  // Ask the user if they want to continue.

  lstrcat(gszUserMsg, " Do you wish to continue?");
  if (IDYES == MessageBox(hWnd, gszUserMsg, gszAppName, MB_YESNO))
    return TRUE;

  // If the user is in doubt about proceeding then we return
  // FALSE and do not proceed with the call to VerInstallFile
  return FALSE;
}

//---------------------------------------------------------------------------
//
//     Function:  PostInstallProcessing()
//
//      Purpose:  This procedure performs any post processing that
//                would need to be done after the call to VerInstallFile.
//                An example of this would be to mark a file as read
//                only.  In this particular case, all we are doing is
//                letting the user know that the install went okay.
//
//   Parameters:  hWnd    - a handle to the window
//                szDir   - the dir path where the file is installed
//                szFile  - the name of file
//
// Return Value:  void
//
// Date      Reason
// ----      ------
// 920103    Function created
//
//--------------------------------------------------------------------------
void PostInstallProcessing(HWND hWnd, LPSTR szDir, LPSTR szFile)
{
  wsprintf(gszUserMsg, "%s\\%s was installed.",
           szDir, szFile);
  MessageBox(hWnd, gszUserMsg, gszAppName, MB_OK);
}

//-------------------------------------------------------------------------
//
//     Function:  void HandleVerInstallFileRes
//
//   Parameters:  hWnd    - handle to the windos
//                dwRes   - return value from VerInstallFile
//                szDir   - destination dir
//                szFile  - file name
//
//      Purpose:  Handles the return value from the call to
//                VerInstallFile.
//
// Return Value:  void
//
// Date      Reason
// ----      ------
// 920103    Function created
//
//------------------------------------------------------------------------
void HandleVerInstallFileRes(HWND   hWnd,
                             DWORD  dwRes,
                             LPSTR  szDir,
                             LPSTR  szFile)
{
  // VerInstallFile leaves the temporary file in the destination
  // directory. If all of the error codes are recoverable, the
  // installation program can override the error by calling
  // VerInstallFile again with the VIFF_FORCEINSTALL flag. In
  // this case, lpszSrcFileName should point to the name of the
  // temporary file.  Then, VerInstallFile deletes the preexisting
  // file and renames the temporary file to the name specified by
  // lpszSrcFileName.

  // If an installation program attempts to force installation
  // after a non-recoverable error, such as VIF_CANNOTREADSRC,
  // VerInstallFile will not install the file.

  if (dwRes & VIF_MISMATCH)
    {
    // In the case of a robust installation program you could notify
    // the user of the mismatch.  You would do this using a dialog showing
    // all the version stamp information from both files.  You would
    // let the user decide whether they want to over-ride VerInstallFile
    // or not.  If they decide to proceed, you would make a second call
    // to VerInstallFile with the same parameters except with the
    // VIFF_FORCEINSTALL flag set.

    wsprintf(gszUserMsg,
             "Install failed with these flags: %s %s %s %s %s %s",
              (LPSTR) (VIF_MISMATCH   & dwRes ? "VIF_MISMATCH "    : ""),
              (LPSTR) (VIF_TEMPFILE   & dwRes ? "VIF_TEMPFILE "    : ""),
              (LPSTR) (VIF_SRCOLD     & dwRes ? "VIF_SRCOLD "      : ""),
              (LPSTR) (VIF_DIFFLANG   & dwRes ? "VIF_DIFFLANG "    : ""),
              (LPSTR) (VIF_DIFFCODEPG & dwRes ? "VIF_DIFFCODEPG "  : ""),
              (LPSTR) (VIF_DIFFTYPE   & dwRes ? "VIF_DIFFTYPE "    : ""));
    MessageBox(hWnd, gszUserMsg, gszAppName, MB_OK);
    return;
    }

  else
    {
    wsprintf(gszUserMsg,
             "Install failed with these flags: %s %s %s %s %s %s %s %s %s %s",
              (LPSTR) (VIF_WRITEPROT        & dwRes ? "VIF_WRITEPROT "    : ""),
              (LPSTR) (VIF_FILEINUSE        & dwRes ? "VIF_FILEINUSE "    : ""),
              (LPSTR) (VIF_OUTOFSPACE       & dwRes ? "VIF_OUTOFSPACE "      : ""),
              (LPSTR) (VIF_ACCESSVIOLATION  & dwRes ? "VIF_ACCESSVIOLATION "    : ""),
              (LPSTR) (VIF_SHARINGVIOLATION & dwRes ? "VIF_SHARINGVIOLATION "  : ""),
              (LPSTR) (VIF_CANNOTCREATE     & dwRes ? "VIF_CANNOTCREATE "  : ""),
              (LPSTR) (VIF_OUTOFMEMORY      & dwRes ? "VIF_OUTOFMEMORY "  : ""),
              (LPSTR) (VIF_CANNOTREADSRC    & dwRes ? "VIF_CANNOTREADSRC "  : ""),
              (LPSTR) (VIF_CANNOTREADDST    & dwRes ? "VIF_CANNOTREADDST "  : ""),
              (LPSTR) (VIF_BUFFTOOSMALL     & dwRes ? "VIF_BUFFTOOSMALL "  : ""));
    MessageBox(hWnd, gszUserMsg, gszAppName, MB_OK);
    }
  return ;
}
