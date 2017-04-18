// DlgProxy.h : header file
//

#if !defined(AFX_DLGPROXY_H__74234460_F528_11D0_A980_0020182A7050__INCLUDED_)
#define AFX_DLGPROXY_H__74234460_F528_11D0_A980_0020182A7050__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CLevelViewerDlg;

/////////////////////////////////////////////////////////////////////////////
// CLevelViewerDlgAutoProxy command target

class CLevelViewerDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CLevelViewerDlgAutoProxy)

	CLevelViewerDlgAutoProxy();           // protected constructor used by dynamic creation

// Attributes
public:
	CLevelViewerDlg* m_pDialog;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLevelViewerDlgAutoProxy)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CLevelViewerDlgAutoProxy();

	// Generated message map functions
	//{{AFX_MSG(CLevelViewerDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CLevelViewerDlgAutoProxy)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CLevelViewerDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPROXY_H__74234460_F528_11D0_A980_0020182A7050__INCLUDED_)
