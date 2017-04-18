/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/


// Utils.h  --  Utility functions header file

#ifndef __UTILS_H
#define __UTILS_H

// format an attribute string for a specified file (i.e. [-a--])
// returns: success
BOOL FormatAttributesString(CString &oAttributesString, 
                            LPCTSTR lpszFileName);

// loads a popup embedded in a menu.  properly displays icons from toolbars
// returns: success
BOOL LoadPopupMenu(int nResourceID, CMenu& pMenu, CMenu *& pPopup);

// sets the current directory to that of a certain module
void GoToModuleDirectory(HINSTANCE hInst);

// saves the current directory and restores it while going out of context
class CPushCurrentDirectory
{
    CString sCurrDir;

public:
    CPushCurrentDirectory();
    ~CPushCurrentDirectory();
};

CString GetBareOSVersion();

// == Support for Grouping == //

// returns index file's extension in the string, according to user prefs.
int GetExtensionPos(CString& cStr);

// extracts the "group" section of a file name
void GetGroupString(CString& cStr);

#endif // __UTILS_H
