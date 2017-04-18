/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/


// ShellContextMenu.cpp : implementation file
//
// Handles the creation of the shell context menu, including the "Send To..."
// sub-menu.  
// Personal note: I think that MS should have made the code to populate and
// handle the "Send To..." sub-menu a part of the shell context menu code.  
// But they didn't, so now we're forced to write a whole lot of spaghetti COM 
// code to do what should have been a trivial part of the OS.  See the code 
// below and judge for yourself.
//
// Additions/Fixes by Philip Oldaker (philip@masmex.com)

#include "stdafx.h"
#include "ShellContextMenu.h"
#include "PIDL.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CShellContextMenu::CShellContextMenu(HWND hWnd, const CString& sAbsPath) : 
    m_hWnd(hWnd), m_sAbsPath(sAbsPath), m_pBuffer(NULL)
{
    m_lpcm = NULL;
    if (!m_ilMenuImages.Create(16, 16, ILC_COLOR32 | ILC_MASK, 0, 4))
	    if (!m_ilMenuImages.Create(16, 16, ILC_COLOR24 | ILC_MASK, 0, 4))
			m_ilMenuImages.Create(16, 16, ILC_COLORDDB | ILC_MASK, 0, 4);
}

CShellContextMenu::~CShellContextMenu()
{
    if (m_lpcm) m_lpcm->Release();
}

bool CShellContextMenu::IsMenuCommand(int iCmd) const
{
    return (IDM_SHELLCTXFIRST <= iCmd  &&  iCmd <= IDM_SHELLCTXLAST);
}

void CShellContextMenu::InvokeCommand(int iCmd) const
{
    if (!IsMenuCommand(iCmd))
    {
		ASSERT(FALSE);
        return;
    }

    // Shell command

    CMINVOKECOMMANDINFO cmi;
    cmi.cbSize       = sizeof(cmi);
    cmi.fMask        = 0;
    cmi.hwnd         = m_hWnd;
    cmi.lpVerb       = MAKEINTRESOURCE(iCmd - IDM_SHELLCTXFIRST);
    cmi.lpParameters = NULL;
    cmi.lpDirectory  = NULL;
    cmi.nShow        = SW_SHOWNORMAL;
    cmi.dwHotKey     = 0;
    cmi.hIcon        = NULL;
    m_lpcm->InvokeCommand(&cmi);
}

bool CShellContextMenu::GetCommandImage(CMenu* pMenu, int item,
    CImageList *&pil, int& image)
{
	int startIndex = -1;
	if (!m_mapMenuToFirstIndex.Lookup(pMenu->GetSafeHmenu(), startIndex))
		return false;

	ASSERT(0 <= startIndex && startIndex < m_iLastIndex);

	image = m_arrIndexToImage.GetAt(startIndex + item);
	pil = &m_ilMenuImages;
	return (image >= 0);
}

// retrieves the shell context menu for a file
void CShellContextMenu::SetMenu(CMenu *pMenu)
{
    HRESULT         hr;
    CPIDL           pidl;

    m_lpcm = NULL;

    if (m_sAbsPath.GetLength() == 0)
    {
        return;
    }

    if (SUCCEEDED(hr = pidl.Set(m_sAbsPath)))
    {
        hr = pidl.GetUIObjectOf(IID_IContextMenu, (LPVOID *)&m_lpcm, m_hWnd);
    }

    if (SUCCEEDED(hr))
    {
        pMenu->DeleteMenu(0, MF_BYPOSITION);
        hr = m_lpcm->QueryContextMenu(*pMenu, 0, IDM_SHELLCTXFIRST, 
            IDM_SHELLCTXLAST, CMF_NODEFAULT | CMF_EXPLORE);

		m_iLastIndex = 0;
		FixOwnerDrawItems(pMenu);
    }

    return;
}

bool CShellContextMenu::PopulateOwnerDrawSubMenu(CMenu *pSubMenu, int idxSubMenu)
{
	IContextMenu2 *lpcm2 = NULL;
	HRESULT hr = m_lpcm->QueryInterface(IID_IContextMenu2, (LPVOID*)&lpcm2);
	if (!SUCCEEDED(hr))
	{
		lpcm2->Release();
		return false;
	}
	// force population of submenus
	hr = lpcm2->HandleMenuMsg(WM_INITMENUPOPUP,
		(WPARAM)pSubMenu->GetSafeHmenu(), idxSubMenu);
	lpcm2->Release();

	return SUCCEEDED(hr);
}

void CShellContextMenu::FixOwnerDrawItems(CMenu *pMenu)
{
    int count = pMenu->GetMenuItemCount();

	// update menu map
	int startIndex = m_iLastIndex;
	m_mapMenuToFirstIndex.SetAt(pMenu->GetSafeHmenu(), startIndex);
	m_iLastIndex += count;

	// catch owner-draw items
    for (int i = 0; i < count; i++)
    {
		m_arrIndexToImage.SetAtGrow(startIndex + i, -1); // init image map

        UINT state = pMenu->GetMenuState(i, MF_BYPOSITION);
		if (state == (UINT)-1)
			continue;

		CString str;
		pMenu->GetMenuString(i, str, MF_BYPOSITION);
		TRACE("Fixing: %s\n", str);

		if (state & MF_OWNERDRAW)
		{
			if (state & MF_POPUP)
			{
				// populate owner-draw submenus
				if (!PopulateOwnerDrawSubMenu(pMenu->GetSubMenu(i), i))
				{
					// remove item, if failed
					if (pMenu->DeleteMenu(i, MF_BYPOSITION))
					{
						--i;
						--count;
					}
				}
				else // and then fix them
					FixOwnerDrawItems(pMenu->GetSubMenu(i));
			}
			else
			{
				// set item text
				if (!SetOwnerDrawStringAndImage(pMenu, i))
				{
					// remove item, if failed
					if (pMenu->DeleteMenu(i, MF_BYPOSITION))
					{
						--i;
						--count;
					}
				}
			}
		}
		else // not owner-draw
		{
			// see if there's a checkmark-bitmap
			SetCheckMarkImage(pMenu, i);

			if (state & MF_POPUP)
			{
				// fix submenu's owner-draw items
				FixOwnerDrawItems(pMenu->GetSubMenu(i));
			}
		}
	}
}

int CALLBACK CShellContextMenu::EnhMetaFileProc(
  HDC hDC,                      // handle to DC
  HANDLETABLE *lpHTable,        // metafile handle table
  CONST ENHMETARECORD *lpEMFR,  // metafile record
  int nObj,                     // count of objects
  LPARAM lpData                 // optional data
)
{
	EMREXTTEXTOUTA& emrTOA = *(EMREXTTEXTOUTA*)lpEMFR;
	EMREXTTEXTOUTW& emrTOW = *(EMREXTTEXTOUTW*)lpEMFR;
	CShellContextMenu* pThis = (CShellContextMenu*)lpData;

	switch (lpEMFR->iType)
	{
	case EMR_EXTTEXTOUTA:
		if (emrTOA.emrtext.nChars > 0)
		{
			pThis->m_iLeftOfText = emrTOA.rclBounds.left;
			lstrcpynA(pThis->m_pBuffer, (LPSTR)((LPBYTE)lpEMFR + emrTOA.emrtext.offString),
				__min(emrTOA.emrtext.nChars, MAX_PATH));
			return FALSE; // stop enum
		}
		break;

	case EMR_EXTTEXTOUTW:
		if (emrTOW.emrtext.nChars > 0)
		{
			pThis->m_iLeftOfText = emrTOW.rclBounds.left;
			WideCharToMultiByte(CP_ACP, 0, (LPWSTR)((LPBYTE)lpEMFR + emrTOW.emrtext.offString),
				emrTOW.emrtext.nChars, pThis->m_pBuffer, MAX_PATH, NULL, NULL);
			return FALSE; // stop enum
		}
		break;
	}
	
	return TRUE; // go on
}

// true if string found
bool CShellContextMenu::SetOwnerDrawStringAndImage(CMenu *pMenu, int idx)
{
	UINT nID = pMenu->GetMenuItemID(idx);

	// get item data
	MENUITEMINFO mii;
	ZeroMemory(&mii, sizeof(MENUITEMINFO));
	mii.cbSize = sizeof(MENUITEMINFO);
	mii.fMask = MIIM_DATA;
	if (!GetMenuItemInfo(pMenu->GetSafeHmenu(), idx, TRUE, &mii)) // can't use MFC
		return false;

    IContextMenu2 *lpcm2 = NULL;
    HRESULT hr = m_lpcm->QueryInterface(IID_IContextMenu2, (LPVOID*)&lpcm2);
    if (!SUCCEEDED(hr))
    {
		lpcm2->Release();
		return false;
	}

	// get item dimensions
	MEASUREITEMSTRUCT mis;
	ZeroMemory(&mis, sizeof(MEASUREITEMSTRUCT));
	mis.CtlType = ODT_MENU;
	mis.itemData = mii.dwItemData;
	mis.itemID = nID;
	// fake ownerdraw msg
	hr = lpcm2->HandleMenuMsg(WM_MEASUREITEM, 0, (LPARAM)&mis);
    if (!SUCCEEDED(hr))
    {
		lpcm2->Release();
		return false;
	}

	// draw item on a metafile
	CRect rectItem(0, 0, mis.itemWidth, mis.itemHeight);
	HDC hDC = CreateEnhMetaFile(NULL, NULL, NULL, NULL);
	if (hDC == NULL)
		return false;

	DRAWITEMSTRUCT dis;
	ZeroMemory(&dis, sizeof(DRAWITEMSTRUCT));
	dis.CtlType = ODT_MENU;
	dis.itemID = nID;
	dis.itemData = mii.dwItemData;
	dis.itemAction = ODA_DRAWENTIRE;
	dis.hwndItem = (HWND)pMenu->GetSafeHmenu();
	dis.hDC = hDC;
	dis.rcItem = rectItem;
	// fake ownerdraw msg
	hr = lpcm2->HandleMenuMsg(WM_DRAWITEM, 0, (LPARAM)&dis);

	HENHMETAFILE hEMF = CloseEnhMetaFile(hDC);
    if (!SUCCEEDED(hr))
    {
		lpcm2->Release();
		DeleteEnhMetaFile(hEMF);
		return false;
	}

	// enum metafile records and search for strings
	char buf[MAX_PATH] = { 0 };
	m_pBuffer = buf;
	m_iLeftOfText = 0;
	EnumEnhMetaFile(NULL, hEMF, EnhMetaFileProc, this, NULL);
	DeleteEnhMetaFile(hEMF);
	m_pBuffer = NULL;

	if (buf[0] == 0 || !pMenu->ModifyMenu(idx, MF_BYPOSITION|MF_STRING, nID, buf))
		return false; // not found or couldn't modify item text

	// try to capture image on the left of text
	int startIndex = -1;
	if (m_mapMenuToFirstIndex.Lookup(pMenu->GetSafeHmenu(), startIndex))
	{
		// should be the first and only time
		ASSERT(m_arrIndexToImage.GetAt(startIndex + idx) < 0);

		// obtain image rect
		CRect rectImage;
		if (m_iLeftOfText > 0) // calc icon rect
		{
			rectImage.left = (m_iLeftOfText-16)/2;
			rectImage.top = (mis.itemHeight-16)/2;
		}
		else // guess
		{
			rectImage.top = (mis.itemHeight-16)/2;
			rectImage.left = rectImage.top;
		}
		rectImage.right = rectImage.left + 16;
		rectImage.bottom = rectImage.top + 16;

		// draw item on a bitmap
		COLORREF crBack = ::GetSysColor(COLOR_MENU);
		CDC dcMem;
		dcMem.CreateCompatibleDC(NULL);
		CBitmap bmImage;
		bmImage.CreateCompatibleBitmap(CDC::FromHandle(::GetDC(NULL)), 16, 16);
		CBitmap* pbmOld = dcMem.SelectObject(&bmImage);
		dcMem.SetWindowOrg(rectImage.TopLeft());
		dcMem.FillSolidRect(0, 0, 16, 16, crBack);
		// fake ownerdraw msg
		dis.hDC = dcMem.GetSafeHdc();
		hr = lpcm2->HandleMenuMsg(WM_DRAWITEM, 0, (LPARAM)&dis);
		dcMem.SelectObject(pbmOld);

		// add the bitmap to the image list
		int idxImg = m_ilMenuImages.Add(&bmImage, crBack);
		if (idxImg >= 0)
			m_arrIndexToImage.SetAt(startIndex + idx, idxImg);
	}

	lpcm2->Release();
	return true;
}


bool CShellContextMenu::SelectItem(CMenu *pMenu, int idx)
{
	UINT nID = pMenu->GetMenuItemID(idx);

	// get item data
	MENUITEMINFO mii;
	ZeroMemory(&mii, sizeof(MENUITEMINFO));
	mii.cbSize = sizeof(MENUITEMINFO);
	mii.fMask = MIIM_DATA;
	if (!GetMenuItemInfo(pMenu->GetSafeHmenu(), idx, TRUE, &mii)) // can't use MFC
		return false;

    IContextMenu2 *lpcm2 = NULL;
    HRESULT hr = m_lpcm->QueryInterface(IID_IContextMenu2, (LPVOID*)&lpcm2);
    if (!SUCCEEDED(hr))
    {
		lpcm2->Release();
		return false;
	}

	// get item dimensions
	MEASUREITEMSTRUCT mis;
	ZeroMemory(&mis, sizeof(MEASUREITEMSTRUCT));
	mis.CtlType = ODT_MENU;
	mis.itemData = mii.dwItemData;
	mis.itemID = nID;
	// fake ownerdraw msg
	hr = lpcm2->HandleMenuMsg(WM_MEASUREITEM, 0, (LPARAM)&mis);
    if (!SUCCEEDED(hr))
    {
		lpcm2->Release();
		return false;
	}

	// draw item on a metafile
	CRect rectItem(0, 0, mis.itemWidth, mis.itemHeight);
	HDC hDC = CreateCompatibleDC(NULL);
	if (hDC == NULL)
		return false;

	DRAWITEMSTRUCT dis;
	ZeroMemory(&dis, sizeof(DRAWITEMSTRUCT));
	dis.CtlType = ODT_MENU;
	dis.itemID = nID;
	dis.itemData = mii.dwItemData;
	dis.itemAction = ODA_DRAWENTIRE;
	dis.itemState = ODS_SELECTED;
	dis.hwndItem = (HWND)pMenu->GetSafeHmenu();
	dis.hDC = hDC;
	dis.rcItem = rectItem;
	// fake ownerdraw msg
	hr = lpcm2->HandleMenuMsg(WM_DRAWITEM, 0, (LPARAM)&dis);
	lpcm2->Release();
	DeleteDC(hDC);

	return true;
}

void CShellContextMenu::SetCheckMarkImage(CMenu *pMenu, int idx)
{
	// get item data
	MENUITEMINFO mii;
	ZeroMemory(&mii, sizeof(MENUITEMINFO));
	mii.cbSize = sizeof(MENUITEMINFO);
	mii.fMask = MIIM_CHECKMARKS;
	if (!GetMenuItemInfo(pMenu->GetSafeHmenu(), idx, TRUE, &mii)) // can't use MFC
		return;

	CBitmap bmp;
	if (mii.hbmpChecked != NULL)
		bmp.Attach(mii.hbmpChecked);
	else if (mii.hbmpUnchecked != NULL)
		bmp.Attach(mii.hbmpUnchecked);
	else
		return; // nothing to do

	// For an explaination of the following call
	// see this TECHNICAL ARTICLE:
	// "Give Me a Handle, and I'll Show You an Object"
	// by Ruediger Asche
	// Created: July 15, 1993

	// copy the handle from another "process" (Shell Extension)
	bmp.Attach(CopyImage(bmp.Detach(), IMAGE_BITMAP, 0, 0, 0));
	if (bmp.m_hObject == NULL)
		return;

	int startIndex = -1;
	if (m_mapMenuToFirstIndex.Lookup(pMenu->GetSafeHmenu(), startIndex))
	{
		// should be the first and only time
		ASSERT(m_arrIndexToImage.GetAt(startIndex + idx) < 0);

		// get bitmap size
		BITMAP bm;
		bmp.GetBitmap(&bm);
		// draw item on a bitmap
		COLORREF crBack = ::GetSysColor(COLOR_MENU);
		CDC dcMem, dcBmp;
		dcMem.CreateCompatibleDC(NULL);
		dcBmp.CreateCompatibleDC(NULL);
		CBitmap bmImage;
		bmImage.CreateCompatibleBitmap(CDC::FromHandle(::GetDC(NULL)), 16, 16);
		CBitmap* pbmOld1 = dcMem.SelectObject(&bmImage);
		CBitmap* pbmOld2 = dcBmp.SelectObject(&bmp);
		dcMem.FillSolidRect(0, 0, 16, 16, crBack);
		// center bitmap
		dcMem.BitBlt((16-bm.bmWidth)/2, (16-bm.bmHeight)/2,
			bm.bmWidth, bm.bmHeight, &dcBmp, 0, 0, SRCCOPY);
		dcMem.SelectObject(pbmOld1);
		dcBmp.SelectObject(pbmOld2);

		// add the bitmap to the image list
		int idxImg = m_ilMenuImages.Add(&bmImage, crBack);
		if (idxImg >= 0)
			m_arrIndexToImage.SetAt(startIndex + idx, idxImg);
	}
}

bool CShellContextMenu::GetCommandDescription(UINT nCmdID, CString& rText)
{
	if (!IsMenuCommand(nCmdID))
		return FALSE;

	// make a buffer large enough to hold either a Unicode or Ansi
	// string and initialize it to zeroes, because some shell
	// extensions return success even when they don't copy anything
	// to the buffer. Conversion is achieved by a CString object.
	WCHAR szHelpText[MAX_PATH+1];
	ZeroMemory(szHelpText, sizeof(WCHAR) * (MAX_PATH+1));

	// try with Unicode first (it seems Explorer does so)
	HRESULT hr = m_lpcm->GetCommandString(nCmdID - IDM_SHELLCTXFIRST,
		GCS_HELPTEXTW, NULL, (LPSTR)szHelpText, MAX_PATH);
	if (*(LPWSTR)szHelpText != 0)	// buffer was used
		rText = (LPWSTR)szHelpText;
	else
	{
		// otherwise try with Ansi
		hr = m_lpcm->GetCommandString(nCmdID - IDM_SHELLCTXFIRST,
			GCS_HELPTEXTA, NULL, (LPSTR)szHelpText, MAX_PATH);
		if (*(LPSTR)szHelpText != 0)	// buffer was used
			rText = (LPSTR)szHelpText;
	}

	return SUCCEEDED(hr);
}
