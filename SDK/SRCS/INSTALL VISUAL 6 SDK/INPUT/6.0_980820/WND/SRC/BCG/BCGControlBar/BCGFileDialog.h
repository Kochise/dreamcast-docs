//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This source code is a part of BCGControlBar library.
// You may use, compile or redistribute it as part of your application 
// for free. You cannot redistribute it as a part of a software development 
// library without the agreement of the author. If the sources are 
// distributed along with the application, you should leave the original 
// copyright notes in the source code without any changes.
// This code can be used WITHOUT ANY WARRANTIES on your own risk.
// 
// For the latest updates to this library, check my site:
// http://welcome.to/bcgsoft
// 
// Stas Levin <bcgsoft@yahoo.com>
//*******************************************************************************

#if !defined(AFX_BCGFILEDIALOG_H__6975A857_62DC_11D2_8BF2_00A0C9B05590__INCLUDED_)
#define AFX_BCGFILEDIALOG_H__6975A857_62DC_11D2_8BF2_00A0C9B05590__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// BCGFileDialog.h : header file
//

#include "bcgcontrolbar.h"

/////////////////////////////////////////////////////////////////////////////
// CBCGFileDialog dialog

class BCGCONTROLBARDLLEXPORT CBCGFileDialog : public CFileDialog
{
	DECLARE_DYNAMIC(CBCGFileDialog)

public:
	//----------------
	// Initialization:
	//----------------
	CBCGFileDialog (LPCTSTR lpszCaption,
		BOOL bNewPage,
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL);
	virtual ~CBCGFileDialog ();

	void SetDlgIcon (HICON hIconBig, HICON hIconSmall = NULL);

	void SetNewImagesList (CImageList* pImagesNew)
	{
		m_pImagesNew = pImagesNew;
	}

	void SetLogoBitmap (CBitmap* pBmpLogo)
	{
		m_pBmpLogo = pBmpLogo;
	}

    //fdncred
    void SetExtraWidth(int iExtraWidth)
    {
        m_iExtraWidth = iExtraWidth;
    }

    void SetExtraHeight(int iExtraHeight)
    {
        m_iExtraHeight = iExtraHeight;
    }

	void AddNewItem (LPCTSTR lpszName, int iIconIndex);

	//---------
	// Results:
	//---------
	enum SelectedPage
	{
		BCGFileNew,
		BCGFileOpen,
		BCGFileRecent
	};

	SelectedPage GetPage () const
	{
		return m_nPage;
	}

	const CString& GetRecentFilePath () const
	{
		ASSERT (m_nPage == BCGFileRecent);
		return m_strRecentFilePath;
	}

	int GetNewItemIndex () const
	{
		ASSERT (m_nPage == BCGFileNew);
		return m_iNewItemIndex;
	}

protected:

	//------------------------
	// Internal notifications:
	//------------------------
	void OnTabSelchange ();
	void OnItemDblClick ();
	void CollectControls ();

	static LRESULT CALLBACK WindowProcNew(HWND hwnd,UINT message, WPARAM wParam, LPARAM lParam);

protected:
	//{{AFX_MSG(CBCGFileDialog)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	virtual void OnInitDone();

// Attributes:
public:
	static WNDPROC m_wndProc;

protected:
	CTabCtrl			m_wndTab;
	CListCtrl			m_wndNewList;
	CListCtrl			m_wndRecentList;
	CList<HWND, HWND>	m_lstFDControls;

	CImageList*			m_pImagesNew;
	CImageList			m_ImagesRecent;

	CObList				m_lstNewItems;
	BOOL				m_bNewPage;
	SelectedPage		m_nPage;

	CString				m_strCaption;

	CString				m_strRecentFilePath;
	int					m_iNewItemIndex;

	CBitmap*			m_pBmpLogo;
	CRect				m_rectLogo;

	HICON				m_hIconBig;
	HICON				m_hIconSmall;

	int					m_iLogoAreaHeight;
    //fdncred
    int                 m_iExtraWidth;
    int                 m_iExtraHeight;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGFILEDIALOG_H__6975A857_62DC_11D2_8BF2_00A0C9B05590__INCLUDED_)
