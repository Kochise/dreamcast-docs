// MFCRowView.h : interface of the CMFCRowView class
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

#if !defined(AFX_MFCROWVIEW_H__2B60A704_22FC_11D1_8FD3_000000000000__INCLUDED_)
#define AFX_MFCROWVIEW_H__2B60A704_22FC_11D1_8FD3_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CMFCRowSet;

class CMFCRowView : public COleDBRecordView
{
protected: // create from serialization only
	CMFCRowView();
	DECLARE_DYNCREATE(CMFCRowView)

public:
	//{{AFX_DATA(CMFCRowView)
	enum { IDD = IDD_MFCROW_FORM };
	CMFCRowSet* m_pSet;
	//}}AFX_DATA

// Attributes
public:
	CMFCRowDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCRowView)
	public:
	virtual CRowset* OnGetRowset();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMFCRowView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMFCRowView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MFCRowView.cpp
inline CMFCRowDoc* CMFCRowView::GetDocument()
   { return (CMFCRowDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCROWVIEW_H__2B60A704_22FC_11D1_8FD3_000000000000__INCLUDED_)
