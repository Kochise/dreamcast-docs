/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/

// SetupWizard.h : header file
//

#if !defined(AFX_SETUPWIZARD_H__535A1E78_ACF6_4FAC_9495_0F8DAF81FA08__INCLUDED_)
#define AFX_SETUPWIZARD_H__535A1E78_ACF6_4FAC_9495_0F8DAF81FA08__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define CPropertySheet CPropertySheetEx
#define CPropertyPage  CSWPageBase

/////////////////////////////////////////////////////////////////////////////
// CSWPageBase 

class CSWPageBase : public CPropertyPageEx
{
	DECLARE_DYNAMIC(CSWPageBase)

// Construction
public:
	CSWPageBase(UINT nIDTemplate, UINT nIDHeaderTitle = 0, 
        UINT nIDHeaderSubTitle = 0);
	~CSWPageBase();

// Dialog Data
	//{{AFX_DATA(CSWPageBase)
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSWPageBase)
	public:
	virtual BOOL OnQueryCancel();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSWPageBase)
	virtual BOOL OnInitDialog();
	virtual LRESULT OnWizardNext();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    CFont m_fontBold;
};



/////////////////////////////////////////////////////////////////////////////
// CSWWelcomePage dialog

class CSWWelcomePage : public CPropertyPage
{
// Construction
public:
	CSWWelcomePage();

// Dialog Data
	//{{AFX_DATA(CSWWelcomePage)
	enum { IDD = IDD_SW_WELCOME };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSWWelcomePage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSWWelcomePage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CSWKbdPage dialog

class CSWKbdPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CSWKbdPage)

// Construction
public:
	CSWKbdPage();
	~CSWKbdPage();

// Dialog Data
	//{{AFX_DATA(CSWKbdPage)
	enum { IDD = IDD_SW_KBD };
	CBCGButton	m_btnTabActivation;
	CBCGButton	m_btnCommonCommands;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSWKbdPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSWKbdPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnKeyboardCust();
	afx_msg void OnKeyboardCustTabActivation();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


/////////////////////////////////////////////////////////////////////////////
// CSWDonePage dialog

class CSWDonePage : public CPropertyPage
{
	DECLARE_DYNCREATE(CSWDonePage)

// Construction
public:
	CSWDonePage();
	~CSWDonePage();

// Dialog Data
	//{{AFX_DATA(CSWDonePage)
	enum { IDD = IDD_SW_DONE };
	BOOL	m_bTour;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSWDonePage)
	public:
	virtual BOOL OnWizardFinish();
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardBack();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSWDonePage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


/////////////////////////////////////////////////////////////////////////////
// CSetupWizard

class CSetupWizard : public CPropertySheet
{
	DECLARE_DYNAMIC(CSetupWizard)

// Construction
public:
	CSetupWizard(HBITMAP hbmWatermark, HBITMAP hbmHeader);

// Attributes
public:

    CSWWelcomePage  m_WelcomePage;
    CSWKbdPage      m_KbdPage;
    CSWDonePage     m_DonePage;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetupWizard)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSetupWizard();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSetupWizard)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#undef CPropertySheet
#undef CPropertyPage

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETUPWIZARD_H__535A1E78_ACF6_4FAC_9495_0F8DAF81FA08__INCLUDED_)
