/***************************************************************************
 *									   *
 *  MODULE	: MpOpen.c						   *
 *									   *
 *  PURPOSE	: Contains the file open dialog function and it's helper   *
 *		  functions.						   *
 *									   *
 *  FUNCTIONS	: IsWild ()	      - Ascertains that the input string   *
 *					contains a DOS wildcard character. *
 *									   *
 *		  SelectFile()	      - If filename supplied contains a    *
 *					wildcard, this function fills the  *
 *					listboxes in File/Open dialog, else*
 *					the dialog is closed.		   *
 *									   *
 *		  FileOpenDlgProc()   - Dialog funcion for the File/Open   *
 *					dialog. 			   *
 *									   *
 *		  GetFileName ()      - Gets a file name from the user.    *
 *									   *
 ***************************************************************************/
#include "multipad.h"
#include <fcntl.h>
#include <io.h>
#include <string.h>
CHAR szPropertyName [] = "FILENAME";/* Name of the File name property list item */



/****************************************************************************
 *									    *
 *  FUNCTION   : IsWild ( psz ) 					    *
 *									    *
 *  PURPOSE    : Checks if the string (referenced by a NEAR pointer)	    *
 *		 contains a DOS wildcard character ("*" or "?").            *
 *									    *
 *  RETURNS    : TRUE  - iff the string contains a wildcard character.	    *
 *		 FALSE - otherwise.				     .	    *
 *									    *
 ****************************************************************************/
BOOL NEAR PASCAL IsWild(register PSTR psz)
{
    for(;;)
	switch (*psz){
	    case '*':
	    case '?':
		/* Found wildcard */
		return TRUE;

	    case 0:
		/* Reached end of string */
		return FALSE;

	    default:
		break;
	}
        psz = CharNext(psz);
}

/****************************************************************************
 *									    *
 *  FUNCTION   : FileExists(pch)					    *
 *									    *
 *  PURPOSE    : Checks to see if a file exists with the path/filename	    *
 *		 described by the string pointed to by 'pch'.               *
 *									    *
 *  RETURNS    : TRUE  - if the described file does exist.		    *
 *		 FALSE - otherwise.					    *
 *									    *
 ****************************************************************************/


BOOL FileExists(PSTR pch)
{
	int fh;

	if ((fh = open(pch, O_RDONLY)) < 0)
	     return(FALSE);

	_lclose(fh);
	return(TRUE);
}

/****************************************************************************
 *									    *
 *  FUNCTION   : SelectFile ( hwnd )					    *
 *									    *
 *  PURPOSE    : Reads the string in the edit control of the File/Open	    *
 *		 dialog. If it contains a wildcard, then it attempts to     *
 *		 fill the listboxes in the File/Open dialog. Othewise it    *
 *		 ends the dialog. Modifies the FILENAME item in the property*
 *		 list of the window.					    *
 *									    *
 ****************************************************************************/

VOID NEAR PASCAL SelectFile(register HWND hwnd)
{
    register PSTR pch;
    PSTR	  pch2;

    /* Get handle (near address) to filename data in window's property list */
    pch = (PSTR)GetProp (hwnd, PROP_FILENAME);

    /* Get the text from the dialog's edit control into this address */
    GetDlgItemText (hwnd, IDD_FILENAME, pch, 64);

    if ( IsWild (pch)){
	/* Select the directory and make a listing of the directories */
	DlgDirList(hwnd, (LPSTR)pch, (int)IDD_DIRS, (int)IDD_PATH, (WORD)ATTR_DIRS);

	/* Obtain the filename-only part of the path in the edit control */
	for (pch2 = pch; *pch; pch = CharNext(pch))
	    if (*pch == '\\' || *pch == ':')
		pch2 = pch + 1;

	/* List the files in this directory based on the wildcard. */
	DlgDirList(hwnd, (LPSTR)pch2, IDD_FILES, IDD_PATH, ATTR_FILES);

	/* Set the dialog's edit control to the filename part of path
	 * string.
	 */
	SetDlgItemText (hwnd, IDD_FILENAME, pch2);
    }
    else
    {
	/* The filename in the property list is not a wildcard */
	if (FileExists (pch)){

	    RemoveProp (hwnd, PROP_FILENAME);
	    EndDialog (hwnd, 0);
	}
	else{
	    MPError ( hwnd, MB_OK | MB_SYSTEMMODAL, IDS_CANTOPEN, (LPSTR) pch);
	    SetActiveWindow (hwnd);
	}
    }
}



/****************************************************************************
 *									    *
 *  FUNCTION   : FileOpenDlgProc()					    *
 *									    *
 *  PURPOSE    : Dialog function for the File/Open dialog. Takes care of    *
 *		 calling the appropriate functions for extracting the	    *
 *		 filename and wildcard, filling the listboxes and changing  *
 *		 the FILENAME item in the property list for the window.     *
 *									    *
 ****************************************************************************/

BOOL APIENTRY FileOpenDlgProc (
	register HWND hwnd,
	WORD	      message,
	register UINT wParam,
	LONG	      lParam)
{
    PSTR pch;

    switch (message){

	case WM_INITDIALOG:
	    /* Set the default file extension on edit window, and try to
	     * get a listing of the files and directories.
	     */
	    SetDlgItemText ( hwnd, IDD_FILENAME, DEFFILESEARCH);
	    SetProp (hwnd, PROP_FILENAME, (HANDLE) lParam);
	    SendDlgItemMessage (hwnd, IDD_FILENAME, EM_LIMITTEXT, 64, 0L);
	    SelectFile (hwnd);
	    break;

	case WM_COMMAND:
	    switch (LOWORD(wParam)) {
		case IDOK:
		    SelectFile(hwnd);
		    break;

		case IDCANCEL:
		    /* Set the filename in the prop. list to NULL and quit */
		    pch  = (PSTR) GetProp (hwnd, PROP_FILENAME);
		    *pch = 0;
		    EndDialog (hwnd, 0);
		    break;

		case IDD_FILENAME:
		    /* Enable the OK button if the edit control has text. */
		    EnableWindow ( GetDlgItem (hwnd, IDOK),
				   GetWindowTextLength (GET_WM_COMMAND_HWND(wParam, lParam)));
		    break;

		case IDD_FILES:

		    /* The files listbox. If file selection has changed, fill
		     * the new filename into the property list buffer and set
		     * text in edit control.
		     */
		    if (GET_WM_COMMAND_CMD(wParam, lParam) == LBN_SELCHANGE){
			    pch = (PSTR) GetProp (hwnd, PROP_FILENAME);
			    DlgDirSelectEx(hwnd, (LPSTR)pch, 128, IDD_FILES);
			    SetDlgItemText (hwnd, IDD_FILENAME, (LPSTR)pch);
		    }
		    else if (GET_WM_COMMAND_CMD(wParam, lParam) == LBN_DBLCLK)
			    /* if the item was double-clicked, try to open it */
			    SelectFile(hwnd);
		    break;

		case IDD_DIRS:

		    /* The directories listbox. Append current filename in edit
		     * control (stripped of the path prefix) to the name from
		     * the property list and set the new string in the edit
		     * control.
		     */
		    if (GET_WM_COMMAND_CMD(wParam, lParam) == LBN_SELCHANGE) {

			    PSTR pch2, pchT, pchS;

			    pch = (PSTR) GetProp (hwnd, PROP_FILENAME);

			    /* Get the new drive/dir */
			    DlgDirSelectEx(hwnd, pch, 128, IDD_DIRS);
			    pch2 = pch + lstrlen(pch);

			    /* Fetch current contents of dialog's edit control and append
			     * it to name from property list... */
			    GetDlgItemText(hwnd,IDD_FILENAME,(LPSTR)pch2,64);
			    if (*pch2 == 0){
			        SetDlgItemText(hwnd, IDD_FILENAME, DEFFILESEARCH);
			        GetDlgItemText(hwnd,IDD_FILENAME,(LPSTR)pch2,64);
			    }
			    else {
			        pchS = pch;
			        for (pchT = pch = pch2; *pch; pch++) {
				        if (*pch == '\\' || *pch == ':') {
				            pchT = pch2;
                        }
                        else if (IsDBCSLeadByte(*pch)) {
                            *pchT++ = *pch++;
                            *pchT++ = *pch;
                        }
				        else
				            *pchT++ = *pch;
			        }
			        *pchT = 0;
			        pch = pchS;
			    }

			    /* Set the edit control with new string */
			    SetDlgItemText (hwnd, IDD_FILENAME, (LPSTR)pch);
		    }
		    else if (GET_WM_COMMAND_CMD(wParam, lParam) == LBN_DBLCLK)
			    SelectFile (hwnd);
		    break;

		default:
		    return FALSE;
	    }
	    break;

	default:
	    return FALSE;
    }
    return TRUE;
}

/****************************************************************************
 *									    *
 *  FUNCTION   : GetFilename ( pstr )					    *
 *									    *
 *  PURPOSE    : Gets a filename from the user by calling the File/Open     *
 *		 dialog.						    *
 *									    *
 ****************************************************************************/
VOID APIENTRY GetFileName(PSTR pstr)
{
#ifdef NOTCOMMONDIALOGS
    DialogBoxParam (hInst, IDD_FILEOPEN, hwndFrame, FileOpenDlgProc, (LONG)pstr);
#else
    OPENFILENAME ofn;
    CHAR szFilterSpec[128];                       /* file type filters */
	CHAR szBuffer[128];

    #define MAXFILENAME 256
    CHAR szFileName[MAXFILENAME];
    CHAR szFileTitle[MAXFILENAME];
	
	LoadString (hInst,IDS_FILTERSPEC, szFilterSpec, sizeof (szFilterSpec));
    LoadString (hInst,IDS_OFNSTRTITLE, szBuffer, sizeof (szBuffer));

    strcpy(szFileName, "");   /* these need be NULL*/
    strcpy(szFileTitle, "");

    /* fill in non-variant fields of OPENFILENAME struct. */
    ofn.lStructSize       = sizeof(OPENFILENAME);
    ofn.hwndOwner	      = NULL;
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
    ofn.Flags             = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;

    /* Use standard open dialog */
    if (!GetOpenFileName ((LPOPENFILENAME)&ofn)){
        *pstr = 0;
		LoadString(hInst, IDS_OPENFAILMSG, szBuffer, sizeof (szBuffer));
        MessageBox(hwndFrame, szBuffer, "Multipad", MB_OK | IDOK);
    }
    else{
        strcpy(pstr, ofn.lpstrFile);
    }
 
#endif
   return;

}
