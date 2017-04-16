#include "PortTool.h"
#include <string.h>

/* global file name variables */
char    lpszFilePath[MAX_PATH];
char    lpszFilterSpec[128] =      /* load here since resource compiler hoses it */
	  "C Source Files (*.C)\0*.C\0C Header Files (*.H)\0*.H\0All Files (*.*)\0*.*\0";

char	lpszPortIniFilePath[MAX_PATH];
char	lpszPortIniFilterSpec[128] =
	  "Port Information Files (*.INI)\0*.INI\0All Files (*.*)\0*.*\0";

/* call the OpenFile common dialog to get a porttool Information filename */


/* call the OpenFile common dialog to get a filename */
BOOL WINAPI GetFileName (
    HWND    hWnd,
    char    *lpszFileTitle,
    char    *lpszFilePath)
{
    OPENFILENAME    ofn;
    char        lpszFileOpen[25];
    char        lpszExt[10];

	memset(&ofn, 0, sizeof(OPENFILENAME));
	strcpy (lpszFileTitle, "");

    LoadString ((HANDLE)GetModuleHandle (NULL),
	IDS_DEFAULTFILEEXT,
	lpszExt,
	sizeof (lpszExt));

    LoadString ((HANDLE)GetModuleHandle (NULL),
	IDS_FILEOPENTITLE,
	lpszFileOpen,
	sizeof (lpszFileOpen));

    /* fill in non-variant fields of OPENFILENAME struct. */
    ofn.lStructSize       = sizeof(OPENFILENAME);
	ofn.hwndOwner		  = hWnd;
	ofn.lpstrFilter 	  = lpszFilterSpec;
    ofn.lpstrCustomFilter = NULL;
    ofn.nMaxCustFilter    = 0;
    ofn.nFilterIndex      = 0;
	ofn.lpstrFile		  = lpszFilePath;
	ofn.nMaxFile		  = MAX_PATH;
    ofn.lpstrInitialDir   = NULL;
    ofn.lpstrFileTitle    = lpszFileTitle;
    ofn.nMaxFileTitle     = MAX_PATH;
	ofn.lpstrTitle		  = lpszFileOpen;
	ofn.lpstrDefExt 	  = lpszExt;
	ofn.Flags			  = OFN_FILEMUSTEXIST;

    /* call common open dialog and return result */
	return (GetOpenFileName ((LPOPENFILENAME)&ofn));
}

BOOL WINAPI GetPortIniFileName (
    HWND    hWnd,
    char    *lpszFileTitle,
    char    *lpszFilePath)
{
    OPENFILENAME    ofn;
	char		lpszFileOpen[64];
    char        lpszExt[10];

	memset(&ofn, 0, sizeof(OPENFILENAME));
	strcpy (lpszFileTitle, "");

	/* load strings from resource string table */
    LoadString ((HANDLE)GetModuleHandle (NULL),
	IDS_DEFAULTPORTEXT,
	lpszExt,
	sizeof (lpszExt));

    LoadString ((HANDLE)GetModuleHandle (NULL),
	IDS_PORTFILEOPENTITLE,
	lpszFileOpen,
	sizeof (lpszFileOpen));

    /* fill in non-variant fields of OPENFILENAME struct. */
    ofn.lStructSize       = sizeof(OPENFILENAME);
	ofn.hwndOwner		  = hWnd;
	ofn.lpstrFilter 	  = lpszPortIniFilterSpec;
    ofn.lpstrCustomFilter = NULL;
    ofn.nMaxCustFilter    = 0;
    ofn.nFilterIndex      = 0;
	ofn.lpstrFile		  = lpszFilePath;
	ofn.nMaxFile		  = MAX_PATH;
    ofn.lpstrInitialDir   = NULL;
    ofn.lpstrFileTitle    = lpszFileTitle;
    ofn.nMaxFileTitle     = MAX_PATH;
	ofn.lpstrTitle		  = lpszFileOpen;
	ofn.lpstrDefExt 	  = lpszExt;
	ofn.Flags			  = 0;

    /* call common open dialog and return result */
	return (GetOpenFileName ((LPOPENFILENAME)&ofn));
}


/* function retrieves the filename from the path */
BOOL WINAPI GetFileFromPath (
    char    *lpszFullPath,
    char    *lpszFile)
{
    char    *lpPtr = lpszFullPath + strlen (lpszFullPath);

    /* file is at end of path, so search backwards to first \ or : char */
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

    /* return filename if found, or full path passed in */
    strcpy (lpszFile, lpPtr);

    return (lpPtr > lpszFullPath);
}




/* open a file and load into edit control */
int WINAPI LoadFile (
    HWND    hWnd,
    char    *lpszName)
{
    LONG    lLength;
    HWND    hWndEdit = (HWND)GetWindowLong (hWnd, WL_HWNDEDIT);
    HANDLE  hEditData;
    char    *lpEditData;
	HFILE	hFile;

    /* open file for read & write */
	if ((hFile = (HFILE)CreateFile (lpszName, GENERIC_READ | GENERIC_WRITE,
									0, NULL, OPEN_EXISTING,
									FILE_ATTRIBUTE_NORMAL, NULL))
			   == (HFILE)INVALID_HANDLE_VALUE) {
	/* return error */
	return 0-IDS_OPENFAILED;
    }

    /* get file length */
    if (lLength = _llseek(hFile, 0L, 2))
       _llseek(hFile, 0L, 0);
    else
    {
    /* close file and return error */
    CloseHandle ((HANDLE)hFile);
	return 0-IDS_NOSIZE;
    }

#if !defined (WIN32)

    /* get the edit control's memory handle */
    if (!(hEditData = (HANDLE)SendMessage (hWndEdit, EM_GETHANDLE, 0, 0L)))
    {
    /* close file and return error */
    CloseHandle ((HANDLE)hFile);
	return 0-IDS_GETHANDLEFAILED;
    }

    /* realloc the memory to fit the new file size */
    if (((hEditData = LocalReAlloc(hEditData, lLength+1, LHND)) == NULL) ||

#else

    if (((hEditData = LocalAlloc (LHND, lLength+1)) == NULL) ||

#endif

    (!(lpEditData = (char *)LocalLock (hEditData))))
    {
    /* close file and return error */
    CloseHandle ((HANDLE)hFile);
	return 0-IDS_REALLOCFAILED;
    }


    /* read the file into hEditData buffer */
    if (_lread(hFile, lpEditData, lLength) == -1)
    {
    /* close file and return error */
    CloseHandle ((HANDLE)hFile);
	return 0-IDS_READFAILED;
    }

    /* null terminate edit buffer */
    lpEditData[lLength] = 0;
    LocalUnlock (hEditData);

    /* load buffer into edit control and close file */

#if !defined(WIN32)

    SendMessage (hWndEdit, EM_SETHANDLE, (UINT)hEditData, 0L);

#else

    lpEditData = LocalLock (hEditData);
    SendMessage (hWndEdit, WM_SETTEXT, 0, (LPARAM)lpEditData);
    GetLastError();
    LocalUnlock (hEditData);
    // LocalFree (hEditData); // Isn't there a synchronization issue with this?

#endif

    CloseHandle ((HANDLE)hFile);

    /* return success */
    return TRUE;
}



/* save file to disk */
int WINAPI SaveFile (
    HWND    hWnd,
    char    *lpszFile)
{
    HANDLE   hEditData;
    int      nLength;
    DWORD    dwWritten;
    HANDLE   hFile;
    HWND     hWndEdit = (HWND)GetWindowLong (hWnd, WL_HWNDEDIT);
    char     *lpEditData;


    /* open the file for writing */
    hFile = CreateFile (lpszFile,
	    GENERIC_WRITE,
	    0,
	    NULL,
	    CREATE_ALWAYS,
	    FILE_ATTRIBUTE_NORMAL,
	    NULL);

    /* validate file handle */
    if (!hFile)
    return IDS_WRITEOPENFAILED;

    /* find out the length of the text in the edit control */
    nLength = GetWindowTextLength (hWndEdit);

#if !defined (WIN32)

    /* get handle to Edit text and lock pointer */
    hEditData  = (HANDLE)SendMessage (hWndEdit, EM_GETHANDLE, 0, 0);
    lpEditData = (char *)LocalLock (hEditData);

#else

    hEditData = LocalAlloc (LHND, nLength+1);
    lpEditData = (char *) LocalLock (hEditData);
    GetWindowText (hWndEdit, lpEditData, nLength+1);

#endif

    /* write edit data to file. */
    if (!WriteFile(hFile, lpEditData, nLength, &dwWritten, NULL))
    {
    /* unlock memory, restore edit handle, close file and return error */
    LocalUnlock (hEditData);
    CloseHandle (hFile);
    return IDS_WRITEFAILED;
    }

    /* clean up and go away */
    LocalUnlock (hEditData);
    CloseHandle (hFile);

    return TRUE;
}


/* invokes the saveas common dialog to retrieve a file name */
BOOL WINAPI SaveAsFileName (
    HWND    hWnd,
    char    *lpszFileTitle,
    char    *lpszFilePath)
{
    OPENFILENAME    ofn;
    char        lpszSaveAs[25];
    char        lpszExt[10];

	memset(&ofn, 0, sizeof(OPENFILENAME));
    *lpszFileTitle = 0;
    *lpszFilePath = 0;

    /* load strings from resource string table */
    LoadString ((HANDLE)GetModuleHandle (NULL),
	IDS_DEFAULTFILEEXT,
	lpszExt,
	sizeof (lpszExt));
    LoadString ((HANDLE)GetModuleHandle (NULL),
	IDS_SAVEASTITLE,
	lpszSaveAs,
	sizeof (lpszSaveAs));

    /* fill in non-variant fields of OPENFILENAME struct. */
    ofn.lStructSize   = sizeof (OPENFILENAME);
    ofn.hwndOwner     = hWnd;
    ofn.lpstrFilter   = lpszFilterSpec;
    ofn.lpstrCustomFilter = NULL;
    ofn.nMaxCustFilter    = 0;
    ofn.nFilterIndex      = 0;
    ofn.lpstrFile     = lpszFilePath;
    ofn.nMaxFile      = MAX_PATH;
    ofn.lpstrInitialDir   = NULL;
    ofn.lpstrFileTitle    = lpszFileTitle;
    ofn.nMaxFileTitle     = MAX_PATH;
    ofn.lpstrTitle    = lpszSaveAs;
    ofn.lpstrDefExt   = lpszExt;
    ofn.Flags         = 0;

    /* call common saveas dialog and return success */
    return (GetSaveFileName ((LPOPENFILENAME)&ofn));
}
