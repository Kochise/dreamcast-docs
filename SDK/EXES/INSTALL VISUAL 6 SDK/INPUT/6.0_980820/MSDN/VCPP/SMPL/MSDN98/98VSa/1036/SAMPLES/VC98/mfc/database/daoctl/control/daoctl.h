// DaoEditCtl.h : Declaration of the CDaoEditCtrl OLE control class.
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

/////////////////////////////////////////////////////////////////////////////
// CDaoEditCtrl : See DaoEditCtl.cpp for implementation.

class CDaoEditCtrl : public COleControl
{
	DECLARE_DYNCREATE(CDaoEditCtrl)

// Constructor
public:
	CDaoEditCtrl();

// Overrides

	// Drawing function
	virtual void OnDraw(
				CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);

	// Persistence
	virtual void DoPropExchange(CPropExchange* pPX);

	// Reset control state
	virtual void OnResetState();

// Implementation
protected:
	~CDaoEditCtrl();

	DECLARE_OLECREATE_EX(CDaoEditCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CDaoEditCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CDaoEditCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CDaoEditCtrl)        // Type name and misc status

	// Subclassed control support
	BOOL PreCreateWindow(CREATESTRUCT& cs);
	BOOL IsSubclassedControl();
	LRESULT OnOcmCommand(WPARAM wParam, LPARAM lParam);

// Implementation
	BOOL m_bDirty;

// Message maps
	//{{AFX_MSG(CDaoEditCtrl)
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CDaoEditCtrl)
	CString m_strFieldName;
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CDaoEditCtrl)
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CDaoEditCtrl)
	dispidFieldName = 1L,
	//}}AFX_DISP_ID
	};
};
