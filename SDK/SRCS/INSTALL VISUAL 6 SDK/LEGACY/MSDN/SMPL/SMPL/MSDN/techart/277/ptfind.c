#include "PortTool.h"

/* global search string */
char    lpszSearch[MAXSEARCHSTRING+1] = "";
HWND    hDlgSearch;

FINDREPLACE    frSearch;


/* compare two substrings */
BOOL WINAPI RealSlowCompare (WORD, char *, char *);
BOOL WINAPI RealSlowCompare (
    WORD    wCase,
    char    *lpszSubject,
    char    *lpszTarget)
{
    if (wCase)
	{
	while (*lpszTarget)
	    if (*lpszTarget++ != *lpszSubject++)
		return FALSE;
	}
    else
	{
	/* convert to lower case before comparing */
	CharLower ((char *)lpszTarget);
	while (*lpszTarget)
	    if (*lpszTarget++ != (CHAR)(DWORD)CharLower ((char *)(DWORD)(BYTE)*lpszSubject++))
		return FALSE;
	}
    return TRUE;
}




/* invoke the common search/replace dialog */
BOOL WINAPI FindDialog (
    HWND    hWnd,
    WORD    wCase,
    WORD    wDir,
    char    *lpszInit)
{
    frSearch.lStructSize      = sizeof (FINDREPLACE);
    frSearch.hwndOwner        = hWnd;
    frSearch.hInstance        = (HANDLE)GetWindowLong (hWnd, GWL_HINSTANCE);
    frSearch.Flags            = 0;

    /* if wCase, case sensitive */
    if (wCase)
	frSearch.Flags        |= FR_MATCHCASE;
    /* if wDir, search forward */
    if (wDir)
	frSearch.Flags        |= FR_DOWN;

    frSearch.lpstrFindWhat    = lpszInit;
    frSearch.lpstrReplaceWith = NULL;
    frSearch.wFindWhatLen     = MAXSEARCHSTRING+1;
    frSearch.wReplaceWithLen  = 0;
    frSearch.lCustData        = 0;
    frSearch.lpfnHook         = NULL;
    frSearch.lpTemplateName   = NULL;

    /* call common search dialog */
    if (hDlgSearch = FindText (&frSearch))
	return TRUE;
    else
	return FALSE;
}



/* perform the actual text searching in the edit control data */
BOOL WINAPI LocateText (
    HWND        hWnd,
    WORD        wCase,
    WORD        wDir,
    char        *lpszStr)
{
    UINT    uBegSel, uEndSel, uOrgBegSel, uOrgEndSel;
    HANDLE  hEditData;
    HWND    hWndEdit = (HANDLE)GetWindowLong (hWnd, WL_HWNDEDIT);
    char    *lpEditData;
    UINT    uLen;
    int     nStrLen = strlen (lpszStr);
    int     nChars;

    /* test for valid string */
    if (!*lpszStr)
	return FALSE;

    /* locate beginning of selected text */
    SendMessage (hWndEdit, EM_GETSEL, (UINT)&uBegSel, (UINT)&uEndSel);
    uOrgBegSel = uBegSel;
    uOrgEndSel = uEndSel;

    /* get length of the text */
    uLen = (UINT)SendMessage (hWndEdit, WM_GETTEXTLENGTH, 0, 0);

    /* Get handle to edit text data and lock it */

#if !defined (WIN32)

    hEditData = (HANDLE)SendMessage (hWndEdit, EM_GETHANDLE, 0, 0);
    lpEditData = LocalLock (hEditData);

#else

    hEditData = LocalAlloc (LHND, uLen);
    lpEditData = LocalLock (hEditData);
    GetWindowText (hWndEdit, lpEditData, uLen);

#endif

    /* advance starting point past selection one char */
    lpEditData += (wDir ? ++uBegSel : --uBegSel);

    /* count characters to search (either forward to end of file or back to beginning) */
    if (wDir)
	nChars = (int)(uLen - uBegSel + 1 - nStrLen);
    else
	nChars = (int)uBegSel;

    /* compare character by character for a substring match */
    while (nChars >= nStrLen)
	{
	/* compare this substring for a match */
	if (RealSlowCompare (wCase, lpEditData, lpszStr))
	    {
	    /* string found, cleanup and go away */
	    LocalUnlock(hEditData);

	    /* scroll parent edit control and select offending text */
	    SendMessage (hWndEdit, EM_LINESCROLL, 0,
		SendMessage (hWndEdit, EM_LINEFROMCHAR, uBegSel, 0) -
		SendMessage (hWndEdit, EM_GETFIRSTVISIBLELINE, 0, 0));

	    /* Select the located string */
	    uEndSel = uBegSel + nStrLen;
	    SendMessage(hWndEdit, EM_SETSEL, uBegSel, uEndSel);

	    /* return success */
	    return TRUE;
	    }

	nChars--;

	/* increment/decrement start position by 1 */
	lpEditData += (wDir ? 1 : -1);
	wDir ? uBegSel++ : uBegSel--;
	}

    LocalUnlock (hEditData);
    SendMessage (hWndEdit, EM_SETSEL, uOrgBegSel, uOrgEndSel);

    /* return failed search  */
    return FALSE;
}
