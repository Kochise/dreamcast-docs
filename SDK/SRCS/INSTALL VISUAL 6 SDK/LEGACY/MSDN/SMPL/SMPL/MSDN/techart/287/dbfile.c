#include "debug.h"
#include <commdlg.h>


// global file name variables
char	szExeFilterSpec[128] = "Executable Files (*.EXE)\0*.EXE\0";
char	szLogFilterSpec[128] = "Debug Log Files (*.LOG)\0*.LOG\0";


// call the OpenFile common dialog to get a filename
BOOL WINAPI GetFileName (
    HWND    hWnd,
    char    *lpszFilePath)
{
    OPENFILENAME    ofn;
    char	    szFileOpen[25];
    char	    szExt[10];
    char	    szTitle[MAX_PATH];

    *szTitle = 0;
    LoadString ((HANDLE)GetModuleHandle (NULL),
	IDS_EXEFILEEXT,
	szExt,
	sizeof (szExt));
    LoadString ((HANDLE)GetModuleHandle (NULL),
        IDS_FILEOPENTITLE,
	szFileOpen,
	sizeof (szFileOpen));

    ofn.lStructSize	  = sizeof (OPENFILENAME);
    ofn.hwndOwner	  = NULL;
    ofn.lpstrFilter	  = szExeFilterSpec;
    ofn.lpstrCustomFilter = NULL;
    ofn.nMaxCustFilter    = 0;
    ofn.nFilterIndex      = 0;
    ofn.lpstrFile	  = lpszFilePath;
    ofn.nMaxFile	  = MAX_PATH;
    ofn.lpstrInitialDir   = NULL;
    ofn.lpstrFileTitle	  = szTitle;
    ofn.nMaxFileTitle     = MAX_PATH;
    ofn.lpstrTitle	  = szFileOpen;
    ofn.lpstrDefExt	  = szExt;
    ofn.Flags		  = OFN_FILEMUSTEXIST;

    // call common open dialog and return result
    return (GetOpenFileName ((LPOPENFILENAME)&ofn));
}



// invokes the saveas common dialog to retrieve a file name
BOOL WINAPI SaveAsFileName (
    HWND    hWnd,
    char    *lpszFilePath)
{
    OPENFILENAME    ofn;
    char	    szSaveAs[25];
    char	    szExt[10];

    *lpszFilePath = 0;

    // load strings from resource string table
    LoadString ((HANDLE)GetModuleHandle (NULL),
	IDS_LOGFILEEXT,
	szExt,
	sizeof (szExt));
    LoadString ((HANDLE)GetModuleHandle (NULL),
        IDS_SAVEASTITLE,
	szSaveAs,
	sizeof (szSaveAs));

    // fill in non-variant fields of OPENFILENAME struct.
    ofn.lStructSize	  = sizeof (OPENFILENAME);
    ofn.hwndOwner	  = hWnd;
    ofn.lpstrFilter	  = szLogFilterSpec;
    ofn.lpstrCustomFilter = NULL;
    ofn.nMaxCustFilter    = 0;
    ofn.nFilterIndex      = 0;
    ofn.lpstrFile	  = lpszFilePath;
    ofn.nMaxFile	  = MAX_PATH;
    ofn.lpstrInitialDir   = NULL;
    ofn.lpstrFileTitle	  = NULL;
    ofn.nMaxFileTitle     = MAX_PATH;
    ofn.lpstrTitle	  = szSaveAs;
    ofn.lpstrDefExt	  = szExt;
    ofn.Flags		  = 0;

    // call common saveas dialog and return success
    return (GetSaveFileName ((LPOPENFILENAME)&ofn));
}




// function retrieves the filename from the path
void WINAPI GetFileFromPath (
    char    *lpszFullPath,
    char    *lpszFile)
{
    char    *lpPtr = lpszFullPath + strlen (lpszFullPath);

    // file is at end of path, so search backwards to first \ or : char
    while (lpPtr > lpszFullPath)
    {
    if (*lpPtr == '\\' ||
        *lpPtr == ':')
        {
        lpPtr++;
        break;
        }
    lpPtr--;
    }

    // return filename if found, or full path passed in
    strcpy (lpszFile, lpPtr);
}



// save file to disk
BOOL WINAPI SaveFile (
    HWND    hWnd)
{
    HANDLE   hEditData;
    int      nLength;
    DWORD    dwWritten;
    HANDLE   hFile;
    HWND     hWndEdit = GetWindow (hWnd, GW_CHILD);
    char     *lpEditData;
    char     szFilePath[MAX_PATH];


    // call common file dialog to get file name
    if (!SaveAsFileName (hWnd, szFilePath))
	return FALSE;

    // open the file for writing
    hFile = CreateFile (szFilePath,
            GENERIC_WRITE,
            0,
            NULL,
            CREATE_ALWAYS,
            FILE_ATTRIBUTE_NORMAL,
            NULL);

    // validate file handle
    if (!hFile)
	return FALSE;

    // find out the length of the text in the edit control
    nLength = GetWindowTextLength (hWndEdit);

    // get handle to Edit text and lock pointer
    hEditData  = (HANDLE)SendMessage (hWndEdit, EM_GETHANDLE, 0, 0);
    lpEditData = (char *)LocalLock (hEditData);

    // write edit data to file.
    if (!WriteFile(hFile, lpEditData, nLength, &dwWritten, NULL))
	{
	// unlock memory, restore edit handle, close file and return error
	LocalUnlock (hEditData);
	CloseHandle (hFile);
	return FALSE;
	}

    // clean up and go away
    LocalUnlock (hEditData);
    CloseHandle (hFile);

    return TRUE;
}









#if 0
// retrieve ini file and path
BOOL GetIniFile (
    char    *lpszFile)
{
    char    lpszPath[MAX_PATH];
    char    *lpPath;
    char    lpszFileName[MAX_PATH];
    OFSTRUCT    of;

    // get module directory and path
    GetModuleFileName (NULL, lpszPath, MAX_PATH);
    lpPath = lpszPath + strlen (lpszPath);

    // find end of path by searching backwards from end to first '\' or ':'
    while (lpPath > lpszPath)
	{
	if (*lpPath == '\\' ||
	    *lpPath == ':')
	    {
	    lpPath++;
	    break;
	    }
	lpPath--;
	}

    //terminate at end of path
    *lpPath = 0;

    // append ini filename to path
    LoadString (GetModuleHandle (NULL), IDS_INIFILE, lpszFileName, MAX_PATH);
    strcat (lpPath, lpszFileName);

    // test for existance
    if (!(OpenFile (lpszPath, &of, OF_EXIST)))
	{
	GetWindowsDirectory (lpszPath, MAX_PATH);
	strcat (lpszPath, lpszFileName);
	if (!(OpenFile (lpszPath, &of, OF_EXIST)))
	    return FALSE;
	else
	    {
	    strcpy (lpszFile, lpszPath);
	    return TRUE;
	    }
	}
    else
	{
	strcpy (lpszFile, lpszPath);
	return TRUE;
	}
}
#endif
