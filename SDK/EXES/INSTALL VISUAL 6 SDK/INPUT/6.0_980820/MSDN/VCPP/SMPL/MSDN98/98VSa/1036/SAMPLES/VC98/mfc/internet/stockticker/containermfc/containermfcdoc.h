// containerMFCDoc.h : interface of the CContainerMFCDoc class
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

#if !defined(AFX_CONTAINERMFCDOC_H__925782CD_9815_11D0_944C_00A0C903487E__INCLUDED_)
#define AFX_CONTAINERMFCDOC_H__925782CD_9815_11D0_944C_00A0C903487E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "_stocktickerctrl.h"

class CContainerMFCDoc : public COleDocument
{
protected: // create from serialization only
	CContainerMFCDoc();
	DECLARE_DYNCREATE(CContainerMFCDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CContainerMFCDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	bool                IsStayOnTopSet();
	void                SetStayOnTop(CFrameWnd* pFrameWnd, bool bStayOnTop,
									 UINT flags =
									 SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE);
	void                Save();
	CStockTickerCtrl*   GetControl();
	void                CreateControl(CView* pView, const CRect& r);

	virtual ~CContainerMFCDoc();
#ifdef _DEBUG
	virtual void        AssertValid() const;
	virtual void        Dump(CDumpContext& dc) const;
#endif

protected:
	CStockTickerCtrl    m_stockTickerCtrl;
	CRect               m_windowRect;
	bool                m_bNewFile;
	CString             m_strSaveFileName;
	bool                m_bStayOnTop;
	bool                m_bNoSaveOnExit;

// Generated message map functions
protected:
	void                CreateControlFailed();
	void                OpenDocFileFailed();
	void                FinishCreate(bool bResize = false);

	//{{AFX_MSG(CContainerMFCDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONTAINERMFCDOC_H__925782CD_9815_11D0_944C_00A0C903487E__INCLUDED_)
