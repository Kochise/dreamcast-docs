// containerMFCDoc.cpp : implementation of the CContainerMFCDoc class
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.


#include "stdafx.h"
#include "containerMFC.h"

#include "containerMFCDoc.h"
#include "CntrItem.h"
#include <io.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CContainerMFCDoc

IMPLEMENT_DYNCREATE(CContainerMFCDoc, COleDocument)

BEGIN_MESSAGE_MAP(CContainerMFCDoc, COleDocument)
	//{{AFX_MSG_MAP(CContainerMFCDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Enable default OLE container implementation
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, COleDocument::OnUpdatePasteMenu)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE_LINK, COleDocument::OnUpdatePasteLinkMenu)
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_CONVERT, COleDocument::OnUpdateObjectVerbMenu)
	ON_COMMAND(ID_OLE_EDIT_CONVERT, COleDocument::OnEditConvert)
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, COleDocument::OnUpdateEditLinksMenu)
	ON_COMMAND(ID_OLE_EDIT_LINKS, COleDocument::OnEditLinks)
	ON_UPDATE_COMMAND_UI(ID_OLE_VERB_FIRST, COleDocument::OnUpdateObjectVerbMenu)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CContainerMFCDoc construction/destruction

CContainerMFCDoc::CContainerMFCDoc()
: m_bNewFile(false), m_bStayOnTop(true), m_bNoSaveOnExit(false)
{
	// Use OLE compound files
	EnableCompoundFile();

	m_strSaveFileName.LoadString(IDS_SAVE_FILE_NAME_MFC);
}

CContainerMFCDoc::~CContainerMFCDoc()
{
}

BOOL CContainerMFCDoc::OnNewDocument()
{
	if (!COleDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CContainerMFCDoc serialization

// Persist window position and control.
//
void CContainerMFCDoc::Serialize(CArchive& ar)
{
	CRect           r;
	if (ar.IsStoring())
	{
		((CFrameWnd*)AfxGetMainWnd())->GetWindowRect(&r);
		ar << r;
		ar << (WORD)(m_bStayOnTop ? 1 : 0);
		if (m_stockTickerCtrl.GetSafeHwnd())
			m_stockTickerCtrl.WriteControl(ar);
	}
	else
	{
		ar >> m_windowRect;
		WORD        w;
		ar >> w;
		m_bStayOnTop = w == 1 ? true : false;
		DWORD       dwCtlDataSize;

		ar >> dwCtlDataSize;

		LPBYTE      pBytes = new BYTE[dwCtlDataSize];
		ar.Read(pBytes, dwCtlDataSize);
		CMemFile    fileCtlData(pBytes, dwCtlDataSize);

		POSITION    pos = GetFirstViewPosition();
		CView*      pFirstView = GetNextView(pos);
		pFirstView->GetClientRect(&r);
		BOOL b = m_stockTickerCtrl.CreateControl(m_stockTickerCtrl.GetClsid(),
												 NULL, WS_VISIBLE, r, pFirstView, 0,
												 &fileCtlData, TRUE);
		delete[] pBytes;
		if (!b)
		{
			CreateControlFailed();
			return;
		}
	}

	// Calling the base class COleDocument enables serialization
	//  of the container document's COleClientItem objects.
	COleDocument::Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CContainerMFCDoc diagnostics

#ifdef _DEBUG
void CContainerMFCDoc::AssertValid() const
{
	COleDocument::AssertValid();
}

void CContainerMFCDoc::Dump(CDumpContext& dc) const
{
	COleDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CContainerMFCDoc commands

// Create control and move window to previously saved position. If no data
// file was found then create from scratch.
//
void CContainerMFCDoc::CreateControl(CView* pView, const CRect & r)
{
	bool    bResize = true;     // does the app need to be positioned and sized?

	if (!m_stockTickerCtrl.GetSafeHwnd())
	{
		CFrameWnd*  pMF = (CFrameWnd*)AfxGetMainWnd();
		ASSERT_VALID(pMF);
		pMF->ShowWindow(SW_HIDE);
		if (_access(m_strSaveFileName, 0) != 0)
		{
			m_bNewFile = true;
			pMF->GetWindowRect(&m_windowRect);
			BOOL b = m_stockTickerCtrl.Create(NULL, WS_VISIBLE, r, pView, 0);
			ASSERT(b);
			if (!b)
			{
				CreateControlFailed();
				return;
			}
			bResize = false;
		}
		else
		{
			// More than one instance can't use the same data file.
			//
			if (!OnOpenDocument(m_strSaveFileName))
			{
				OpenDocFileFailed();
				return;
			}
		}
	}
	FinishCreate(bResize);
	UpdateAllViews(NULL);
}

CStockTickerCtrl* CContainerMFCDoc::GetControl()
{
	return &m_stockTickerCtrl;
}

// Save everything to file.
//
void CContainerMFCDoc::Save()
{
	if (m_bNoSaveOnExit)
		return;

	if (m_bNewFile)
		DoSave(m_strSaveFileName);
	else
		SaveToStorage(0);
}

// Toggle the stay on top feature on and off.
//
void CContainerMFCDoc::SetStayOnTop(CFrameWnd* pFrameWnd, bool bStayOnTop, UINT flags)
{
	m_bStayOnTop = bStayOnTop;

	pFrameWnd->SetWindowPos(m_bStayOnTop ? &CWnd::wndTopMost : &CWnd::wndNoTopMost,
							m_windowRect.left, m_windowRect.top,
							m_windowRect.Width(), m_windowRect.Height(),
							flags);
}

// Are we currently in the stay on top state?
//
bool CContainerMFCDoc::IsStayOnTopSet()
{
	return m_bStayOnTop;
}

// Display error messages.
//
void CContainerMFCDoc::CreateControlFailed()
{
	CString     strError;
	CString     strTitle;
	VERIFY(strError.LoadString(IDS_CREATE_CONTROL_FAILED));
	VERIFY(strTitle.LoadString(AFX_IDS_APP_TITLE));
	AfxGetMainWnd()->MessageBox(strError, strTitle, MB_OK|MB_ICONERROR);
	m_bNoSaveOnExit = true;
	::PostQuitMessage(1);
}

void CContainerMFCDoc::OpenDocFileFailed()
{
	CString     strError;
	CString     strTitle;
	VERIFY(strError.LoadString(IDS_OPEN_DOC_FILE_FAILED));
	VERIFY(strTitle.LoadString(AFX_IDS_APP_TITLE));
	AfxGetMainWnd()->MessageBox(strError, strTitle, MB_OK|MB_ICONERROR);
	m_bNoSaveOnExit = true;
	::PostQuitMessage(1);
}

// Check that window is still visible. Set stay on top state, also sets window
// position.
//
void CContainerMFCDoc::FinishCreate(bool bResize)
{
	int     dtX = ::GetSystemMetrics(SM_CXSCREEN);
	int     dtY = ::GetSystemMetrics(SM_CYSCREEN);

	if (m_windowRect.right > dtX)
		m_windowRect.OffsetRect(-m_windowRect.Width(), 0);
	if (m_windowRect.bottom > dtY)
		m_windowRect.OffsetRect(0, -m_windowRect.Height());

	UINT    uWPFlags = SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE;

	if (bResize)
		uWPFlags = SWP_SHOWWINDOW;

	SetStayOnTop((CFrameWnd*)AfxGetMainWnd(), m_bStayOnTop, uWPFlags);
}
