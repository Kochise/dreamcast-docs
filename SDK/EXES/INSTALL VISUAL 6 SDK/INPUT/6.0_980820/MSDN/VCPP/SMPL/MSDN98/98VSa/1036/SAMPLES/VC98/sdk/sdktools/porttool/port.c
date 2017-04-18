#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include "portpriv.h"
#include "port.h"

// redefine dbcs versions of common string functions
#ifdef strnicmp
#undef strnicmp
#endif
#define strnicmp    My_mbsnicmp
#define strncmp     My_mbsncmp
#define strncpy     My_mbsncpy
#define strtok      My_mbstok

/* globals for this module */
HANDLE	  hMMFile = 0;
HANDLE	  hDLL;
BOOL	  bInit = FALSE;

/* function prototypes for private module functions */
void WINAPI FreePortData ();
int  WINAPI GetFirstToken (LPPORT *);
int  WINAPI GetNextToken (LPPORT *);
void WINAPI IgnoreToken (char *, LPPORT);
BOOL WINAPI LoadSection (char *, char *, DWORD, int *, char *);
BOOL WINAPI GetIniFile (HANDLE, char *, char *);

/****************************************************************************
    My_mbschr:  strchr() DBCS version
****************************************************************************/
unsigned char * _CRTAPI1 My_mbschr(
    unsigned char *psz, unsigned short uiSep)
{
    while (*psz != '\0' && *psz != uiSep) {
        psz = CharNext(psz);
    }
    if (*psz == '\0' && uiSep != '\0') {
        return NULL;
    } else {
        return psz;
    }
}
/****************************************************************************
    My_mbstok:  strtok() DBCS version
****************************************************************************/
unsigned char * _CRTAPI1 My_mbstok(
    unsigned char *pszSrc, unsigned char *pszSep)
{
    static char *pszSave = NULL;
    char *pszHead;
    char *psz;

    if (pszSrc == NULL) {
        if (pszSave == NULL) {
            return NULL;
        } else {
            psz = pszSave;
        }
    } else {
        psz = pszSrc;
    }

    /*********************************************/
    /* Skip delimiters to find a head of a token */
    /*********************************************/
    while (*psz) {
        if (IsDBCSLeadByte(*psz)) {
            break;
        } else if (NULL == My_mbschr(pszSep, *psz)) {
            break;
        }
        psz++;
    }
    if (*psz == '\0') {
        //No more token
        return (pszSave = NULL);
    }
    pszHead = psz;

    /******************************/
    /* Search a Tail of the token */
    /******************************/
    while (*psz) {
        if (IsDBCSLeadByte(*psz)) {
            psz += 2;
            continue;
        } else if (NULL != My_mbschr(pszSep, *psz)) {
            break;
        }
        psz++;
    }
    if (*psz == '\0') {
        pszSave = NULL;
    } else {
        //Found next delimiter
        pszSave = psz + 1;
        *psz = '\0';
    }
    return pszHead;
}
/****************************************************************************
    My_mbsnicmp:strnicmp() DBCS version
                If 'nLen' splits a DBC, this function compares
                the DBC's 2nd byte also.
****************************************************************************/
int _CRTAPI1 My_mbsnicmp(
    const unsigned char *psz1, const unsigned char *psz2, size_t Length)
{
    int nLen = (int)Length;

    while (0 < nLen) {
        if ('\0' == *psz1 || '\0' == *psz2) {
            return *psz1 - *psz2;
        }
        if (IsDBCSLeadByte(*psz1) || IsDBCSLeadByte(*psz2)) {
            if (*psz1 != *psz2 || *(psz1+1) != *(psz2+1)) {
                return *psz1 - *psz2;
            }
            psz1 += 2;
            psz2 += 2;
            nLen -= 2;
        } else {
            if((BYTE)CharUpper((LPSTR)*psz1) != (BYTE)CharUpper((LPSTR)*psz2)){
                return *psz1 - *psz2;
            }
            psz1++;
            psz2++;
            nLen--;
        }
    }
    return 0;
}
/****************************************************************************
    My_mbsncmp: strncmp() DBCS version
                If 'nLen' splits a DBC, this function compares
                the DBC's 2nd byte also.
****************************************************************************/
int _CRTAPI1 My_mbsncmp(
    const unsigned char *psz1, const unsigned char *psz2, size_t Length)
{
    int nLen = (int)Length;

    while (0 < nLen) {
        if ('\0' == *psz1 || '\0' == *psz2) {
            return *psz1 - *psz2;
        }
        if (IsDBCSLeadByte(*psz1) || IsDBCSLeadByte(*psz2)) {
            if (*psz1 != *psz2 || *(psz1+1) != *(psz2+1)) {
                return *psz1 - *psz2;
            }
            psz1 += 2;
            psz2 += 2;
            nLen -= 2;
        } else {
            if (*psz1 != *psz2) {
                return *psz1 - *psz2;
            }
            psz1++;
            psz2++;
            nLen--;
        }
    }
    return 0;
}
/****************************************************************************
    My_mbsncpy:
****************************************************************************/
unsigned char * _CRTAPI1 My_mbsncpy(
    unsigned char *psz1, const unsigned char *psz2, size_t Length)
{
    int nLen = (int)Length;
    unsigned char *pszSv = psz1;

    while (0 < nLen) {
        if (*psz2 == '\0') {
            *psz1++ = '\0';
            nLen--;
        } else if (IsDBCSLeadByte(*psz2)) {
            if (nLen == 1) {
                *psz1 = '\0';
            } else {
                *psz1++ = *psz2++;
                *psz1++ = *psz2++;
            }
            nLen -= 2;
        } else {
            *psz1++ = *psz2++;
            nLen--;
        }
    }
    return pszSv;
}

/* entry point for DLL loading and unloading */
BOOL WINAPI DllMain (
    HANDLE    hModule,
    DWORD     dwFunction,
    LPVOID    lpNot)
{
#ifdef DEBUG
DebugBreak ();
#endif

    switch (dwFunction)
	{
	case DLL_PROCESS_ATTACH:
		hDLL = hModule;
	    break;

	case DLL_PROCESS_DETACH:
	    FreePortData ();
	default:
	    break;
	}

    return TRUE;
}



/* function initializes port structures */
BOOL WINAPI InitPortData (
	char	  *szIniFileName
	)
{
    char	szSection[MAX_PATH];
    char	szIniFilePath[MAX_PATH];
    char	szMapFileName[MAX_PATH];
    OFSTRUCT	of;
    HANDLE	hFile;
    DWORD	nFileSize;
    int 	nOffset = 0;
    char	*lpMMFile;

	/* Initialize Flag off */
	bInit = FALSE;

    /* load name for global file mapping */
    LoadString (hDLL, IDS_MAPFILENAME, szMapFileName, MAX_PATH);

    /* after first process initializes port data */
    if ((hMMFile = OpenFileMapping (FILE_MAP_WRITE, FALSE, szMapFileName)))
	/* exit now since initialization was already performed by another process */
	return TRUE;

    /* retrive path and file for ini file */
	if (!GetIniFile (hDLL, szIniFileName, szIniFilePath))
	return FALSE;

    /* test for ini file existance and get length of file */
    if ((int)(hFile = (HANDLE)OpenFile (szIniFilePath, &of, OF_READ)) == -1)
	return FALSE;
    else
	{
	nFileSize = GetFileSize (hFile, NULL);
	CloseHandle (hFile);
	}

    /* allocate a segment of the swap file for shared memory 2*Size of ini file */
    if (!(hMMFile = CreateFileMapping ((HANDLE)0xffffffff,
				   NULL,
				   PAGE_READWRITE,
				   0,
				   nFileSize * 2,
				   szMapFileName)))
	return FALSE;

    /* map a view of this file for writing */
    lpMMFile = (char *)MapViewOfFile (hMMFile, FILE_MAP_WRITE, 0, 0, 0);

    /* load tokens for APIS section */
    LoadString (hDLL, IDS_PORTAPIS, szSection, MAX_PATH);
    if (!LoadSection (szIniFilePath, szSection, PT_APIS, &nOffset, lpMMFile))
	{
	/* clean up memory mapped file */
	UnmapViewOfFile (lpMMFile);
	CloseHandle (hMMFile);
	return FALSE;
	}

    /* load tokens for MESSAGES section */
    LoadString (hDLL, IDS_PORTMESSAGES, szSection, MAX_PATH);
    if (!LoadSection (szIniFilePath, szSection, PT_MESSAGES, &nOffset, lpMMFile))
	{
	/* clean up memory mapped file */
	UnmapViewOfFile (lpMMFile);
	CloseHandle (hMMFile);
	return FALSE;
	}

    /* load tokens for STRUCTURES section */
    LoadString (hDLL, IDS_PORTSTRUCTURES, szSection, MAX_PATH);
    if (!LoadSection (szIniFilePath, szSection, PT_STRUCTURES, &nOffset, lpMMFile))
	{
	/* clean up memory mapped file */
	UnmapViewOfFile (lpMMFile);
	CloseHandle (hMMFile);
	return FALSE;
	}

    /* load tokens for TYPES section */
    LoadString (hDLL, IDS_PORTTYPES, szSection, MAX_PATH);
    if (!LoadSection (szIniFilePath, szSection, PT_TYPES, &nOffset, lpMMFile))
	{
	/* clean up memory mapped file */
	UnmapViewOfFile (lpMMFile);
	CloseHandle (hMMFile);
	return FALSE;
	}

    /* load tokens for MACROS section */
    LoadString (hDLL, IDS_PORTMACROS, szSection, MAX_PATH);
    if (!LoadSection (szIniFilePath, szSection, PT_MACROS, &nOffset, lpMMFile))
	{
	/* clean up memory mapped file */
	UnmapViewOfFile (lpMMFile);
	CloseHandle (hMMFile);
	return FALSE;
	}

    /* load tokens for CONSTANTS section */
    LoadString (hDLL, IDS_PORTCONSTANTS, szSection, MAX_PATH);
    if (!LoadSection (szIniFilePath, szSection, PT_CONSTANTS, &nOffset, lpMMFile))
	{
	/* clean up memory mapped file */
	UnmapViewOfFile (lpMMFile);
	CloseHandle (hMMFile);
	return FALSE;
	}

    /* load tokens for CUSTOM section */
    LoadString (hDLL, IDS_PORTCUSTOM, szSection, MAX_PATH);
    if (!LoadSection (szIniFilePath, szSection, PT_CUSTOM, &nOffset, lpMMFile))
	{
	/* clean up memory mapped file */
	UnmapViewOfFile (lpMMFile);
	CloseHandle (hMMFile);
	return FALSE;
	}

    /* release WRITE view of memory mapped file */
    UnmapViewOfFile (lpMMFile);

	/* success */
	bInit = TRUE;
    return TRUE;
}



/* release memory mapped file view */
void WINAPI FreePortData ()
	{
	if ( ! bInit )
		return;

    /* release memory mapped file */
    CloseHandle (hMMFile);
    }



/* external function to check a string for porting issues */
BOOL WINAPI CheckString (
    char	*lpszSrc,
    DWORD	dwSearch,
    LPRESULT	lprIssue)
{
    BOOL      bRet = FALSE;
    LPPORT    lpToken;
    char      *lpStr = lpszSrc;
    int       nSrcLen = strlen (lpszSrc);
    int       nTokLen;
    char      *lpMMFile = (char *)MapViewOfFile (hMMFile, FILE_MAP_WRITE, 0, 0, 0);


	if ( ! bInit )
	   return FALSE;

	/* if view of file failed */
    if (!lpMMFile)
	return FALSE;

    /* if ignore token */
    if (dwSearch & PT_IGNORETOKEN)
	/* flag token as ignored */
	IgnoreToken (lpszSrc, (LPPORT)lpMMFile);

    else
	/* loop through all characters in string */
	while ((lpStr-lpszSrc) < nSrcLen)
	    {
	    /* initialize lpToken to beginning of list */
	    lpToken = (LPPORT)lpMMFile;

        /* loop thru all tokens */
	    if (nTokLen = GetFirstToken (&lpToken))
	    do
        {
        /* filter tokens for search criteria */
        if (!(lpToken->dwType & PT_IGNORED) &&
            !(dwSearch & lpToken->dwType) &&
            ((dwSearch & PT_IGNORECASE &&
              !strnicmp ((char *)lpToken+lpToken->nPosToken, lpStr, nTokLen)) ||
             !strncmp ((char *)lpToken+lpToken->nPosToken, lpStr, nTokLen)))
            {
            /* token found in line, return ISSUE struct */
            strncpy (lprIssue->lpszToken,
                 (char *)lpToken+lpToken->nPosToken,
                 *(WORD *)lprIssue->lpszToken);
            strncpy (lprIssue->lpszHelpStr,
                 (char *)lpToken+lpToken->nPosHelpStr,
                 *(WORD *)lprIssue->lpszHelpStr);
            strncpy (lprIssue->lpszIssue,
                 (char *)lpToken+lpToken->nPosIssue,
                 *(WORD *)lprIssue->lpszIssue);
            strncpy (lprIssue->lpszSuggest,
                 (char *)lpToken+lpToken->nPosSuggest,
                 *(WORD *)lprIssue->lpszSuggest);
            lprIssue->nPosToken = (int)(lpStr - lpszSrc);

		    bRet = TRUE;
		    goto DONE;
		    }
		}
	    while ((nTokLen = GetNextToken (&lpToken)));

        lpStr = CharNext(lpStr);
        }

DONE:

    /* unmap view of memory mapped file */
    UnmapViewOfFile (lpMMFile);

    return bRet;
}



/* function get's the first token in the list */
int WINAPI GetFirstToken (
    LPPORT    *lpToken)
{
    /* increment to next non-ignored token in list */
    while (((((LPPORT)*lpToken)->dwType) == PT_IGNORED) &&
	   ((((LPPORT)*lpToken)->nSize) != 0))
	(char *)*lpToken += ((LPPORT)*lpToken)->nSize;

    /* if at end of list, reset list to null */
    if ((((LPPORT)*lpToken)->nSize) == 0)
	{
	*lpToken = 0;
	return 0;
	}

    /* return length of token */
    return (strlen ((char *)*lpToken + ((LPPORT)*lpToken)->nPosToken));
}


/* function get's the next token in the list */
int WINAPI GetNextToken (
    LPPORT    *lpToken)
{
    /* increment to next non-ignored token in list */
    do
	(char *)*lpToken += ((LPPORT)*lpToken)->nSize;
    while (((((LPPORT)*lpToken)->dwType) == PT_IGNORED) &&
	   ((((LPPORT)*lpToken)->nSize) != 0));

    /* if at end of list, reset list to null */
    if ((((LPPORT)*lpToken)->nSize) == 0)
	{
	*lpToken = 0;
	return 0;
	}

    /* return length of token */
    return (strlen ((char *)*lpToken + ((LPPORT)*lpToken)->nPosToken));
}



/* function sets the ignore flag on the specified token */
void WINAPI IgnoreToken (
    char    *lpszToken,
    LPPORT  lpToken)
{
    /* search for token in list */
    while (lpToken->nSize != 0)
	/* if same token */
	if (!strcmp ((char *)((char *)lpToken + lpToken->nPosToken), lpszToken))
	    {
	    lpToken->dwType |= PT_IGNORED;
	    break;
	    }
	/* increment to  next token */
	else
	    (char *)lpToken += lpToken->nSize;
}




/* load tokens from a section of ini file */
BOOL WINAPI LoadSection (
    char    *lpszIniFile,
    char    *lpszSection,
    DWORD   dwType,
    int     *nOffset,
    char    *lpMMFile)
{
    char    *lpszKeyNames;
    char    *lpKey;
    char    *lpszValue;
    char    *lpVal;
    char    *lpszToken;
    char    lpszDefault[] = "Default";
    char    *lpMem = lpMMFile + *nOffset;
    int     nList;


    /* allocate lots of memory off heap to save calling applications' stack */
    if (!(lpszKeyNames = (char *)LocalAlloc (LPTR, FIFTY_K_LINE)))
	return FALSE;
    if (!(lpszValue = (char *)LocalAlloc (LPTR, TWO_K_LINE)))
	{
	LocalFree ((HLOCAL)lpszKeyNames);
	return FALSE;
	}
    if (!(lpszToken = (char *)LocalAlloc (LPTR, MAXTOKENLEN)))
	{
	LocalFree ((HLOCAL)lpszKeyNames);
	LocalFree ((HLOCAL)lpszValue);
	return FALSE;
	}

    /* get all keynames in section */
    if (((nList = GetPrivateProfileString (lpszSection,
					   NULL,
					   lpszDefault,
					   lpszKeyNames,
					   FIFTY_K_LINE,
					   lpszIniFile)) == (int)(strlen (lpszDefault))) &&
	!strcmp (lpszDefault, lpszKeyNames))
	{
	LocalFree ((HLOCAL)lpszKeyNames);
	LocalFree ((HLOCAL)lpszValue);
	LocalFree ((HLOCAL)lpszToken);
	return FALSE;
	}

    /* initialize token pointer and first token */
    lpKey = lpszKeyNames;

    /* loop through all keynames */
    while (TRUE)
	{
	/* get next token */
	strcpy (lpszToken, lpKey);

	/* get value for token */
	if ((GetPrivateProfileString (lpszSection,
				     lpszToken,
				     lpszDefault,
				     lpszValue,
				     TWO_K_LINE,
				     lpszIniFile) == strlen (lpszDefault)) &&
	    !strcmp (lpszDefault, lpszValue))
	    {
	    LocalFree ((HLOCAL)lpszKeyNames);
	    LocalFree ((HLOCAL)lpszValue);
	    LocalFree ((HLOCAL)lpszToken);
	    return FALSE;
	    }
	else
	    {
	    /* break line up into components */
	    ((LPPORT)lpMem)->nPosToken = sizeof (PORT);
	    strcpy ((char *)(lpMem + ((LPPORT)lpMem)->nPosToken), lpszToken);

	    ((LPPORT)lpMem)->nPosHelpStr =
		    ((LPPORT)lpMem)->nPosToken + strlen ((char *)(lpMem + ((LPPORT)lpMem)->nPosToken)) + 1;
	    if (lpVal = strtok (lpszValue, ";"))
		strcpy ((char *)(lpMem + ((LPPORT)lpMem)->nPosHelpStr), lpVal);
	    else
		*(lpMem + ((LPPORT)lpMem)->nPosHelpStr) = 0;

	    ((LPPORT)lpMem)->nPosIssue =
		    ((LPPORT)lpMem)->nPosHelpStr + strlen ((char *)(lpMem + ((LPPORT)lpMem)->nPosHelpStr)) + 1;
	    if (lpVal = strtok (NULL, ";"))
		strcpy ((char *)(lpMem + ((LPPORT)lpMem)->nPosIssue), lpVal);
	    else
		*(lpMem + ((LPPORT)lpMem)->nPosIssue) = 0;

	    ((LPPORT)lpMem)->nPosSuggest =
		    ((LPPORT)lpMem)->nPosIssue + strlen ((char *)(lpMem + ((LPPORT)lpMem)->nPosIssue)) + 1;
	    if (lpVal = strtok (NULL, ";"))
		strcpy ((char *)(lpMem + ((LPPORT)lpMem)->nPosSuggest), lpVal);
	    else
		*(lpMem + ((LPPORT)lpMem)->nPosSuggest) = 0;

	    /* set size of dynamic token structure */
	    ((LPPORT)lpMem)->nSize = (((LPPORT)lpMem)->nPosSuggest +
		 strlen ((char *)(lpMem + ((LPPORT)lpMem)->nPosSuggest)) + 1);

	    /* adjust nSize for DWORD alignment */
            ((LPPORT)lpMem)->nSize = ((((LPPORT)lpMem)->nSize) + 3) & ~3;

	    /* set token type */
	    ((LPPORT)lpMem)->dwType = dwType;

	    /* adjust list pointer to point beginning of next list element */
	    lpMem += ((LPPORT)lpMem)->nSize;
	    }

	/* increment token pointer and test for end of list */
	if (((lpKey += strlen (lpszToken) + 1) - lpszKeyNames) >= (nList - 1))
	    {
	    /* indicate end of list by setting size of next element to 0 */
	    ((LPPORT)lpMem)->nSize = 0;
	    break;
	    }
	}

    /* got to end of section, clean up and go away */
    LocalFree ((HLOCAL)lpszKeyNames);
    LocalFree ((HLOCAL)lpszValue);
    LocalFree ((HLOCAL)lpszToken);

    /* recalculate offset */
    *nOffset = lpMem - lpMMFile;

    /* return successful load */
    return TRUE;
}


/* retrieve ini file and path */
BOOL WINAPI GetIniFile (
	HANDLE	hDLL,
	char	*lpszFileName,
    char    *lpszFile)
{
    char    lpszPath[MAX_PATH];
    char    *lpPath;
	// char	 lpszFileName[MAX_PATH];
	OFSTRUCT	of;

	// Is this a full path ? If so there must be a : or \ in there somewhere.
	lpPath = lpszFileName;
	while ( *lpPath )
	{
	   if ( *lpPath == '\\' || *lpPath == ':' )
	   {
		  if ((OpenFile (lpszFileName, &of, OF_EXIST)))
		  {
			 // Name passed in is OK.
			 strcpy (lpszFile, lpszFileName);
			 return TRUE;
		  }

	   }
	   lpPath = CharNext(lpPath);
	}

	// OK, not a full path, we must build one

    /* get module directory and path */
    GetModuleFileName (hDLL, lpszPath, MAX_PATH);
    lpPath = lpszPath + strlen (lpszPath);

    /* find end of path by searching backwards from end to first '\' or ':' */
    while (lpPath > lpszPath)
    {
    if (*lpPath == '\\' ||
        *lpPath == ':')
        {
        lpPath++;
        break;
        }
    lpPath = CharPrev(lpszPath, lpPath);
    }

    /* terminate at end of path */
    *lpPath = 0;

    /* append ini filename to path */
	strcat (lpPath, lpszFileName);

	// check for an extension ( look for '.' before '\' )
	lpPath = lpszPath+strlen(lpszPath);
	while ( lpPath > lpszPath && 
            *lpPath != '\\' && 
            *lpPath != ':')
	{
	   if ( *lpPath == '.')
		  break;
	   lpPath = CharPrev(lpszPath, lpPath);
	}

	if ( *lpPath != '.' )
	{
	   // No extension, supply one
	   strcat (lpszPath, ".INI");
	}


    /* test for existance */
    if (!(OpenFile (lpszPath, &of, OF_EXIST)))
	{
	GetWindowsDirectory (lpszPath, MAX_PATH);
	strcat (lpszPath, lpszFileName);
	if (!(OpenFile (lpszPath, &of, OF_EXIST)))
	{
		return FALSE;
	}
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
