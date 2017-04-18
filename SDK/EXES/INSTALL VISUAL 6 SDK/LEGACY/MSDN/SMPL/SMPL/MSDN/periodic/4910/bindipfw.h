// bindipfw.h : interface of the DocObject in-place frame window class
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1995 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#ifndef __BINDIPFW_H__
#define __BINDIPFW_H__

class CDocObjectIPFrameWnd : public COleIPFrameWnd
{
	DECLARE_DYNCREATE(CDocObjectIPFrameWnd)

// Constructors
public:
	CDocObjectIPFrameWnd();

// Attributes
public:

// Operations
public:

// Overridables
protected:

// Implementation
public:
	virtual ~CDocObjectIPFrameWnd();
#ifdef _DEBUG
   virtual void AssertValid() const;
   virtual void Dump(CDumpContext& dc) const;
#endif

   // Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDocObjectIPFrameWnd)
	//}}AFX_VIRTUAL
protected:
	virtual void OnRequestPositionChange(LPCRECT lpRect);
   virtual void RecalcLayout(BOOL bNotify = TRUE);

   // Menu Merging support
   HMENU m_hMenuHelpPopup;
   virtual BOOL BuildSharedMenu();
   virtual void DestroySharedMenu();

	// Generated message map functions
	//{{AFX_MSG(CDocObjectIPFrameWnd)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

   friend class CDocObjectServerDoc;
};

/////////////////////////////////////////////////////////////////////////////

#endif   // #ifndef __BINDIPFW_H__

