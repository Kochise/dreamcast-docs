/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/


// Utils.cpp : Utility functions
//

#include "stdafx.h"
#include "WndTabs.h"
#include "Utils.h"
#include "Config.h"
#include "TabsWindow.h"

//avoid hardcoding, following the MS docs here
#define WT_GET_FILE_ATTRIBUTES_ERROR	0xFFFFFFFF

#define WT_FILE_ATTR_STRING_FORMAT		"[%s%s%s%s]"
#define WT_FILE_ATTR_TXT_NONE			"-"
#define WT_FILE_ATTR_TXT_READONLY		"r"
#define WT_FILE_ATTR_TXT_ARCHIVE		"a"
#define WT_FILE_ATTR_TXT_HIDDEN			"h"
#define WT_FILE_ATTR_TXT_SYSTEM			"s"

// format an attribute string for a specified file (i.e. [-a--])
// function courtesy of Jerzy Kaczorowski [kaczoroj@hotmail.com]
BOOL FormatAttributesString(CString &oAttributesString, LPCTSTR lpszFileName)
{
	BOOL bRes = FALSE;
	DWORD dwFileAttributes;

	dwFileAttributes = GetFileAttributes(lpszFileName);

	if( dwFileAttributes != WT_GET_FILE_ATTRIBUTES_ERROR )
	{
		oAttributesString.Format( WT_FILE_ATTR_STRING_FORMAT,
			dwFileAttributes & FILE_ATTRIBUTE_READONLY	? WT_FILE_ATTR_TXT_READONLY	: WT_FILE_ATTR_TXT_NONE,
			dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE	? WT_FILE_ATTR_TXT_ARCHIVE	: WT_FILE_ATTR_TXT_NONE,
			dwFileAttributes & FILE_ATTRIBUTE_HIDDEN	? WT_FILE_ATTR_TXT_HIDDEN	: WT_FILE_ATTR_TXT_NONE,
			dwFileAttributes & FILE_ATTRIBUTE_SYSTEM	? WT_FILE_ATTR_TXT_SYSTEM	: WT_FILE_ATTR_TXT_NONE );

		bRes = TRUE;
	}

	return bRes;
}

// loads a popup embedded in a menu.  properly displays icons from toolbars
BOOL LoadPopupMenu(int nResourceID, CMenu& menu, CMenu *& pPopup)
{
    if (menu.LoadMenu(nResourceID))
    {
        pPopup = (CMenu *)menu.GetSubMenu(0);
//        g_CoolMenuManager.ConvertMenu(pPopup, 0, 0, TRUE);
/*        pPopup->LoadToolbar(IDR_ICONS);
        pPopup->LoadToolbar(IDR_TOOLBAR_MEDIUM);
*/
        return TRUE;
    }

    return FALSE;
}

// sets the current directory to that of a certain module
void GoToModuleDirectory(HINSTANCE hInst)
{
    char path[512], *p;
    GetModuleFileName(hInst, path, sizeof(path));
    p = strrchr(path, '\\');
    if (p)
    {
        // trim file name
        *p = '\0';

        // make AddInComm.dll's directory the current directory
        SetCurrentDirectory(path);
    }
}

// returns index file's extension in the string
int GetExtensionPos(CString& cStr)
{
    int nBSPos, nDotPos, len;

    nBSPos = cStr.ReverseFind('\\');

    if (cfg_bUseRightMostDot)
    {
        nDotPos = cStr.ReverseFind('.');
        if (nDotPos >= nBSPos)
            return nDotPos;
    }
    else
    {
        if (nBSPos < 0)
        {
            return cStr.Find('.');
        }
    }

    nDotPos = nBSPos;
    len = cStr.GetLength();
    while (nDotPos < len)
    {
        if (cStr[nDotPos] == '.')
            return nDotPos;
        nDotPos++;
    }

    return -1;
}


// extracts the "group" section of a file name
void GetGroupString(CString& cStr)
{
    int nPos;

    if (cfg_bGroupDiffPaths  && 
        (nPos = cStr.ReverseFind('\\')) >= 0)
    {
        cStr = cStr.Mid(nPos + 1);
    }

    if ((nPos = GetExtensionPos(cStr)) >= 0)
    {
        cStr = cStr.Left(nPos);
    }

    cStr.MakeUpper();
}


CString GetBareOSVersion()
{
    CString         cStr;
    OSVERSIONINFO   osvi;

    osvi.dwOSVersionInfoSize = sizeof(osvi);
    GetVersionEx(&osvi);

    cStr.Format("%s %d.%d %s", 
        (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT)? "NT" : "9x", 
        osvi.dwMajorVersion, osvi.dwMinorVersion, osvi.szCSDVersion);

    return cStr;
}

CPushCurrentDirectory::CPushCurrentDirectory()
{
    ::GetCurrentDirectory(1024, sCurrDir.GetBuffer(1024));
    sCurrDir.ReleaseBuffer();
}

CPushCurrentDirectory::~CPushCurrentDirectory()
{
    if (!sCurrDir.IsEmpty())
    {
        ::SetCurrentDirectory(sCurrDir);
    }
}
