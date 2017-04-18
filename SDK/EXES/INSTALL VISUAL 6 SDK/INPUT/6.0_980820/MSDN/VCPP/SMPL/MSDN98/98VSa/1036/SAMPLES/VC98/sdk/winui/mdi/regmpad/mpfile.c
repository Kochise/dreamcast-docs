/***************************************************************************
 *									   *
 *  MODULE    : MpFile.c						   *
 *									   *
 *  PURPOSE   : Contains the code for File I/O for Multipad.		   *
 *									   *
 *  FUNCTIONS : AlreadyOpen   - Determines if a file is already open.	   *
 *									   *
 *		AddFile       - Creates a new MDI window and, if specified,*
 *				loads a file into it.			   *
 *									   *
 *		LoadFile      - Loads a file into a MDI window. 	   *
 *									   *
 *		MyReadFile    - Calls File/Open dialog and appropriately   *
 *				responds to the user's input.              *
 *									   *
 *		SaveFile      - Saves the contents of a MDI window's edit  *
 *				control to a file.			   *
 *									   *
 *		SetSaveFrom   - Formats the "Save 'file' to" string.       *
 *									   *
 *		SaveAsDlgProc - Dialog function for the File/SaveAs dialog.*
 *									   *
 *		ChangeFile    - Calls File/SaveAs dialog.		   *
 *									   *
 ***************************************************************************/
#include "multipad.h"
#include <fcntl.h>
#include <SYS\types.h>
#include <SYS\stat.h>
#include <io.h>
#include <string.h>

VOID APIENTRY GetFileName(PSTR);
//INT APIENTRY DialogBoxParam(HANDLE,LPSTR,HWND,FARPROC,LONG);
//LPSTR WINAPI AnsiUpper(LPSTR);

OFSTRUCT	of;
/****************************************************************************
 *									    *
 *  FUNCTION   : AlreadyOpen(szFile)					    *
 *									    *
 *  PURPOSE    : Checks to see if the file described by the string pointed  *
 *		 to by 'szFile' is already open.                            *
 *									    *
 *  RETURNS    : a handle to the described file's window if that file is    *
 *		 already open;	NULL otherwise. 			    *
 *									    *
 ****************************************************************************/

HWND APIENTRY AlreadyOpen(CHAR *szFile)
{
    BOOL    fFound;
    HWND    hwndCheck;
    CHAR    szChild[MAX_PATH+1];
    LPSTR   lpChild, lpFile, lp;

    /* Open the file with the OF_PARSE flag to obtain the fully qualified
     * pathname in the OFSTRUCT structure.
     */
    if (HFILE_ERROR == OpenFile((LPSTR)szFile, (LPOFSTRUCT)&of, OF_PARSE))
       return NULL;

    lpFile= CharUpper(of.szPathName);

    /* Check each MDI child window in Multipad */
    for (   hwndCheck = GetWindow(hwndMDIClient, GW_CHILD);
	    hwndCheck;
	    hwndCheck = GetWindow(hwndCheck, GW_HWNDNEXT)   ) {
	/* Initialization  for comparison */
	lpChild = szChild;

	/* Skip icon title windows */
	if (GetWindow(hwndCheck, GW_OWNER))
	    continue;

	/* Get current child window's name */
	GetWindowText(hwndCheck, lpChild, MAX_PATH+1);

	CharUpper(lpChild);

	for (fFound= TRUE, lp= lpFile; (*lpChild) || (*lp); ++lpChild, ++lp)
	   if (*lpChild != *lp)
	   {
	      fFound= FALSE;
	      break;
	   }

	if (fFound) return(hwndCheck);
    }
    /* No match found -- file is not open -- return NULL handle */
    return(NULL);
}

/****************************************************************************
 *									    *
 *  FUNCTION   : AddFile (lpName)					    *
 *									    *
 *  PURPOSE    : Creates a new MDI window. If the lpName parameter is not   *
 *		 NULL, it loads a file into the window. 		    *
 *									    *
 *  RETURNS    : HWND  - A handle to the new window.			    *
 *									    *
 ****************************************************************************/

HWND APIENTRY AddFile(CHAR * pName)
{
    HWND hwnd;

    CHAR	    sz[160];
    MDICREATESTRUCT mcs;

    if (!pName) {
	/* The pName parameter is NULL -- load the "Untitled" string from */
	/* STRINGTABLE and set the title field of the MDI CreateStruct.    */
	LoadString (hInst, IDS_UNTITLED, sz, sizeof(sz));
	mcs.szTitle = (LPSTR)sz;
    }
    else
	/* Title the window with the fully qualified pathname obtained by
	 * calling OpenFile() with the OF_PARSE flag (in function
	 * AlreadyOpen(), which is called before AddFile().
	 */
	mcs.szTitle = of.szPathName;

    mcs.szClass = szChild;
    mcs.hOwner	= hInst;

    /* Use the default size for the window */
    mcs.x = mcs.cx = CW_USEDEFAULT;
    mcs.y = mcs.cy = CW_USEDEFAULT;

    /* Set the style DWORD of the window to default */
    mcs.style = styleDefault;

    /* tell the MDI Client to create the child */
    hwnd = (HWND)SendMessage (hwndMDIClient,
			      WM_MDICREATE,
			      0,
			      (LONG)(LPMDICREATESTRUCT)&mcs);

    /* Did we get a file? Read it into the window */
    if (pName){
	if (!LoadFile(hwnd, pName)){
	    /* File couldn't be loaded -- close window */
	    SendMessage(hwndMDIClient, WM_MDIDESTROY, (DWORD) hwnd, 0L);
	}
    }

    return hwnd;
}

/****************************************************************************
 *									    *
 *  FUNCTION   : LoadFile (lpName)					    *
 *									    *
 *  PURPOSE    : Given the handle to a MDI window and a filename, reads the *
 *		 file into the window's edit control child.                 *
 *									    *
 *  RETURNS    : TRUE  - If file is sucessfully loaded. 		    *
 *		 FALSE - Otherwise.					    *
 *									    *
 ****************************************************************************/

INT APIENTRY LoadFile (
	HWND hwnd,
	CHAR * pName)
{
    LONG   wLength;
    HANDLE hT;
    LPSTR  lpB;
    HWND   hwndEdit;
    HFILE  fh;
	OFSTRUCT  of;
    hwndEdit = (HWND)GetWindowLong (hwnd, GWL_HWNDEDIT);

    /* The file has a title, so reset the UNTITLED flag. */
    SetWindowWord(hwnd, GWW_UNTITLED, FALSE);

    fh = OpenFile(pName, &of, OF_READ);  /* JAP was 0, which is OF_READ)*/

    /* Make sure file has been opened correctly */
    if ( fh < 0 )
	goto error;

    /* Find the length of the file */
    wLength = (DWORD)_llseek(fh, 0L, 2);
    _llseek(fh, 0L, 0);

    /* Attempt to reallocate the edit control's buffer to the file size */
    hT = (HANDLE)SendMessage (hwndEdit, EM_GETHANDLE, 0, 0L);
    if (LocalReAlloc(hT, wLength+1, LHND) == NULL) {
	/* Couldn't reallocate to new size -- error */
	_lclose(fh);
	goto error;
    }

    /* read the file into the buffer */
    if (wLength != (LONG)_lread(fh, (lpB = (LPSTR)LocalLock (hT)), (UINT)wLength))
	MPError (hwnd, MB_OK|MB_ICONHAND, IDS_CANTREAD, (LPSTR)pName);

    /* Zero terminate the edit buffer */
    lpB[wLength] = 0;
    LocalUnlock (hT);

    SendMessage (hwndEdit, EM_SETHANDLE, (UINT)hT, 0L);
    _lclose(fh);

    return TRUE;

error:
    /* Report the error and quit */
    MPError(hwnd, MB_OK | MB_ICONHAND, IDS_CANTOPEN, (LPSTR)pName);
    return FALSE;
}

/****************************************************************************
 *									    *
 *  FUNCTION   : MyReadFile(hwnd)					    *
 *									    *
 *  PURPOSE    : Called in response to a File/Open menu selection. It asks  *
 *		 the user for a file name and responds appropriately.	    *
 *									    *
 ****************************************************************************/

VOID APIENTRY MyReadFile(HWND hwnd)
{
    CHAR    szFile[128];
    HWND    hwndFile;

    GetFileName (szFile);

    /* If the result is not the empty string -- take appropriate action */
    if (*szFile) {
	    /* Is file already open?? */
	    if (hwndFile = AlreadyOpen(szFile)) {
	        /* Yes -- bring the file's window to the top */
	        BringWindowToTop(hwndFile);
	    }
	    else {
	        /* No -- make a new window and load file into it */
	        AddFile(szFile);
	    }
    }
	UNREFERENCED_PARAMETER(hwnd);
}

/****************************************************************************
 *									    *
 *  FUNCTION   : SaveFile (hwnd)					    *
 *									    *
 *  PURPOSE    : Saves contents of current edit control to disk.	    *
 *									    *
 ****************************************************************************/

VOID APIENTRY SaveFile(HWND hwnd)
{
    HANDLE   hT;
    LPSTR    lpT;
    CHAR     szFile[128];
    INT      cch;
    INT      fh;
//    OFSTRUCT of;
    HWND     hwndEdit;

    PSTR     pch;

    hwndEdit = (HWND)GetWindowLong ( hwnd, GWL_HWNDEDIT);
    GetWindowText (hwnd, szFile, sizeof(szFile));

    /* If there is no extension (control is 'Untitled') add .TXT as extension */
    for (cch = FALSE, lpT = szFile; *lpT; lpT = CharNext(lpT))
	switch (*lpT){
	    case '.':
		 cch = TRUE;
		 break;

	    case '\\':
	    case ':' :
		 cch = FALSE;
		 break;
	}
    if (!cch)
	LoadString (hInst, IDS_ADDEXT, lpT, lpT - (LPSTR)szFile);

    fh = open(szFile, O_BINARY | O_WRONLY | O_CREAT, S_IWRITE);

    /* If file could not be opened, quit */
    if (fh < 0){
	MPError (hwnd, MB_OK | MB_ICONHAND, IDS_CANTCREATE, (LPSTR)szFile);
	return;
    }

    /* Find out the length of the text in the edit control */
    cch = GetWindowTextLength (hwndEdit);

    /* Obtain a handle to the text buffer */
    hT	= (HANDLE)SendMessage (hwndEdit, EM_GETHANDLE, 0, 0L);
    lpT = (LPSTR)LocalLock (hT);

    /* Write out the contents of the buffer to the file. */
    if (cch != write(fh, lpT, cch))
	MPError (hwnd, MB_OK | MB_ICONHAND, IDS_CANTWRITE, (LPSTR)szFile);

    /* Clean up */
    LocalUnlock (hT);
    SendMessage (hwndEdit, EM_SETHANDLE, (UINT)hT, 0L);

    close(fh);

    return;
	UNREFERENCED_PARAMETER(pch);
}

/****************************************************************************
 *									    *
 *  FUNCTION   : SetSaveFrom () 					    *
 *									    *
 *  PURPOSE    : Formats the "Save 'file' to .." string.                    *
 *									    *
 ****************************************************************************/

VOID NEAR PASCAL SetSaveFrom (
	HWND hwnd,
	PSTR psz)
{
    CHAR szFmt[32];
    CHAR szText[160];

    /* The text string in the .RC file contains the format string... */
    GetDlgItemText( hwnd, IDD_SAVEFROM, szFmt, sizeof(szFmt));

    /* NOTE: this (LPSTR) cast MUST be here... wsprintf() is a cdecl
     * (C calling conventions) function with varying args... there is
     * no way for the compiler to know that all strings must be LPSTR's
     * and do the conversion, so we have to be careful about wsprintf()'s.
     */
    wsprintf ( szText, szFmt, (LPSTR)psz);

    /* set the text in the static control */
    SetDlgItemText (hwnd, IDD_SAVEFROM, szText);
}

/****************************************************************************
 *									    *
 *  FUNCTION   : SaveAsDlgProc(hwnd, message, wParam, lParam)		    *
 *									    *
 *  PURPOSE    : Dialog function File/SaveAs. It waits for a filename, and  *
 *		 then calls SaveFile or cancels the operation.		    *
 *									    *
 ****************************************************************************/

BOOL APIENTRY SaveAsDlgProc(
	HWND hwnd,
	UINT message,
	UINT wParam,
	LONG lParam)
{
    CHAR   sz[64];
    CHAR   *pch;
    BOOL   fExt;
    HWND   hwndSave;

    switch (message){

	case WM_INITDIALOG:

	    /* Identify the window whose contents we're saving */
#ifdef ORGCODE
	    hwndSave = LOWORD (lParam);
#else
		hwndSave = (HWND)lParam;		/*passed in from another procedure*/
#endif
	    /* Set it's name in the property list */
	    SetProp (hwnd, PROP_FILENAME, hwndSave);

	    GetWindowText (hwndSave, sz, sizeof(sz));

	    /* Set the save from string... */
	    SetSaveFrom (hwnd,sz);

	    /* Generate a filename complete with extension */
	    CharUpper (sz);
	    for (fExt = FALSE, pch = sz; *pch; pch = CharNext(pch))
		if (*pch == '.')
		    fExt = TRUE;
		else if (*pch == '\\')
		    fExt = FALSE;
	    if (!fExt)
		LoadString (hInst, IDS_ADDEXT, (LPSTR)pch, pch - sz);

	    /* Display the filename in the edit control */
	    SetDlgItemText (hwnd, IDD_SAVETO, sz);

	    /* Select the entire range of text */
	    SendMessage(GetDlgItem(hwnd, IDD_SAVETO), EM_SETSEL, GET_EM_SETSEL_MPS(0, 100));

	    DlgDirList (hwnd, "*.*", (INT)IDD_DIRS, (INT)IDD_PATH, (WORD)ATTR_DIRS);

	    /* enable OK butto iff edit control is nonempty */
	    if (!*sz)
		EnableWindow (GetDlgItem (hwnd, IDOK), FALSE);
	    break;

	case WM_COMMAND:
	    switch (LOWORD(wParam)){
		case IDCANCEL:
		    /* Abort operation */
		    EndDialog(hwnd,1);
		    break;

		case IDOK:
		   /*  Just change the title of the MDI child. The calling
		    *  function of ChangeFile(), which uses the title text
		    *  for the filename, will do the actual save.
		    */
		    hwndSave = GetProp (hwnd, PROP_FILENAME);
		    GetDlgItemText (hwnd, IDD_SAVETO, sz, sizeof(sz));
		    CharUpper ((LPSTR)sz);
		    SetWindowText (hwndSave, sz);
		    EndDialog (hwnd, 0);
		    break;

		case IDD_SAVETO:
		   /* If the edit control changes, check to see if its empty.
		    * enable OK if it contains something
		    */
		    if (HIWORD (lParam) != EN_CHANGE)
			return FALSE;
		    EnableWindow (GetDlgItem (hwnd, IDOK),
				SendDlgItemMessage (hwnd,
						   IDD_SAVETO,
						   WM_GETTEXTLENGTH,
						   0,
						   0L));
		    break;

		case IDD_DIRS:
		    if (HIWORD(lParam)==LBN_DBLCLK){
			CHAR szT[64];

			DlgDirSelectEx(hwnd, szT, 64, IDD_DIRS);
			lstrcat ( szT, "*.*");
			DlgDirList (hwnd, szT, (INT)IDD_DIRS, (INT)IDD_PATH, (WORD)ATTR_DIRS);
			break;
		    }
		    return FALSE;

		default:
		    return FALSE;
	    }

	default:
	    return FALSE;
    }
    return TRUE;
}

/****************************************************************************
 *									    *
 *  FUNCTION   : ChangeFile (hwnd)					    *
 *									    *
 *  PURPOSE    : Invokes the File/SaveAs dialog.			    *
 *									    *
 *  RETURNS    : TRUE  - if user selected OK or NO.			    *
 *		 FALSE - otherwise.					    *
 *									    *
 ****************************************************************************/

BOOL APIENTRY ChangeFile (HWND hwnd)
{
    INT     i;

#ifdef NOTCOMMONDIALOGS
    i = DialogBoxParam (hInst, IDD_SAVEAS, hwnd, SaveAsDlgProc, (LONG)hwnd);
    if (!i)
	    SetWindowWord (hwnd, GWW_UNTITLED, 0);
    return !i;
#else
    OPENFILENAME ofn;
    CHAR szFilterSpec[128];                       /* file type filters */
    CHAR szBuffer[128];

    #define MAXFILENAME 256
    CHAR szFileName[MAXFILENAME];
    CHAR szFileTitle[MAXFILENAME];

	LoadString(hInst, IDS_SAVEFILTERSPEC, szFilterSpec, sizeof (szFilterSpec));
	LoadString(hInst, IDS_SAVEFILETITLE, szBuffer, sizeof (szBuffer));

    strcpy(szFileName, "");   /* these need be NULL*/
    strcpy(szFileTitle, "");

    /* fill in non-variant fields of OPENFILENAME struct. */
    ofn.lStructSize       = sizeof(OPENFILENAME);
    ofn.hwndOwner	      = hwnd;
    ofn.lpstrFilter	      = szFilterSpec;
    ofn.lpstrCustomFilter = NULL;
    ofn.nMaxCustFilter	  = 0;
    ofn.nFilterIndex	  = 0;
    ofn.lpstrFile         = szFileName;
    ofn.nMaxFile	      = MAXFILENAME;
    ofn.lpstrInitialDir   = NULL;
    ofn.lpstrFileTitle    = szFileTitle;
    ofn.nMaxFileTitle     = MAXFILENAME;
    ofn.lpstrTitle        = szBuffer;
    ofn.lpstrDefExt       = "TXT";
    ofn.Flags             = OFN_HIDEREADONLY;
    /* Use standard open dialog */
    i = GetSaveFileName ((LPOPENFILENAME)&ofn);
	CharUpper ((LPSTR)ofn.lpstrFile);
	SetWindowText (hwnd, ofn.lpstrFile);
    if (i)
	    SetWindowWord (hwnd, GWW_UNTITLED, 0);
    return i;
#endif

}
