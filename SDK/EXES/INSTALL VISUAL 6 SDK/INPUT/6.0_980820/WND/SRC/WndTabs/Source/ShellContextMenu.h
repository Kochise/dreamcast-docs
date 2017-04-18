/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/


// ShellContextMenu.h : header file
//

#if !defined(AFX_SHELLCONTEXTMENU_H__24BAC666_2B03_11D3_B9C1_0000861DFCE7__INCLUDED_)
#define AFX_SHELLCONTEXTMENU_H__24BAC666_2B03_11D3_B9C1_0000861DFCE7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define IDM_SHELLCTXFIRST      20000
#define IDM_SHELLCTXLAST       29999
//#define IDM_SHELLSENDTO        (IDM_SHELLCTXFIRST+28)

class CShellContextMenu
{
    LPCONTEXTMENU                   m_lpcm;
    CString                         m_sAbsPath;
    HWND                            m_hWnd;

	LPSTR m_pBuffer;
	int m_iLeftOfText;

    CImageList                      m_ilMenuImages;
	// map items to their own image (index in the image list)
    CMap<HMENU, HMENU, int, int>    m_mapMenuToFirstIndex;
	CArray<int, int>                m_arrIndexToImage;
	int                             m_iLastIndex;

public:    
    CShellContextMenu(HWND m_hWnd, const CString& sAbsPath);
    ~CShellContextMenu();

	bool GetCommandDescription(UINT nCmdID, CString& rText);
    bool IsMenuCommand(int iCmd) const;
    void InvokeCommand(int iCmd) const;
    bool GetCommandImage(CMenu* pMenu, int item, CImageList *&pil, int& image);
	bool SelectItem(CMenu *pMenu, int idx);

    void SetMenu(CMenu *pMenu);

protected:    
	static int CALLBACK EnhMetaFileProc(
	  HDC hDC,                      // handle to DC
	  HANDLETABLE *lpHTable,        // metafile handle table
	  CONST ENHMETARECORD *lpEMFR,  // metafile record
	  int nObj,                     // count of objects
	  LPARAM lpData                 // optional data
	);

	void SetCheckMarkImage(CMenu* pMenu, int idx);
	bool SetOwnerDrawStringAndImage(CMenu* pMenu, int idx);
	bool PopulateOwnerDrawSubMenu(CMenu *pSubMenu, int idxSubMenu);
	void FixOwnerDrawItems(CMenu* pMenu);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHELLCONTEXTMENU_H__24BAC666_2B03_11D3_B9C1_0000861DFCE7__INCLUDED_)
