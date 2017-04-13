#if !defined(AFX_EVENTLOGGINGPAGE_H__CAC42500_E29A_11D0_8E15_00C04FB68D60__INCLUDED_)
#define AFX_EVENTLOGGINGPAGE_H__CAC42500_E29A_11D0_8E15_00C04FB68D60__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// EventLoggingPage.H : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEventLoggingPage dialog

class CEventLoggingPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CEventLoggingPage)

// Construction
public:
	CEventLoggingPage();
	~CEventLoggingPage();

// Dialog Data
	//{{AFX_DATA(CEventLoggingPage)
	enum { IDD = IDD_CONTROLLOGGING_EVENTS };
	CCheckListBox   m_lbEvents;
	//}}AFX_DATA

   CStringArray m_astrEventNames;
   CUIntArray m_atLogFlags;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CEventLoggingPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CEventLoggingPage)
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EVENTLOGGINGPAGE_H__CAC42500_E29A_11D0_8E15_00C04FB68D60__INCLUDED_)
