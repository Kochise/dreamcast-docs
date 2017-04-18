/////////////////////////////////////////////////////////////////////////////
//
//	Copyright (c) 1997 <company name>
//
//	Module Name:
//		ResProp.h
//
//	Abstract:
//		Definition of the resource extension property page classes.
//
//	Implementation File:
//		ResProp.cpp
//
//	Author:
//		<name> (<e-mail name>) Mmmm DD, 1997
//
//	Revision History:
//
//	Notes:
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _RESPROP_H_
#define _RESPROP_H_

/////////////////////////////////////////////////////////////////////////////
// Include Files
/////////////////////////////////////////////////////////////////////////////

#ifndef _BASEPAGE_H_
#include "BasePage.h"	// for CBasePropertyPage
#endif

#ifndef _PROPLIST_H_
#include "PropList.h"	// for CObjectPropert
#endif

/////////////////////////////////////////////////////////////////////////////
// Forward Class Declarations
/////////////////////////////////////////////////////////////////////////////

class CSmbSmpParamsPage;

/////////////////////////////////////////////////////////////////////////////
// External Class Declarations
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//
//	CSmbSmpParamsPage
//
//	Purpose:
//		Parameters page for resources.
//
/////////////////////////////////////////////////////////////////////////////

class CSmbSmpParamsPage : public CBasePropertyPage
{
	DECLARE_DYNCREATE(CSmbSmpParamsPage)

// Construction
public:
	CSmbSmpParamsPage(void);

// Dialog Data
	//{{AFX_DATA(CSmbSmpParamsPage)
	enum { IDD = IDD_PP_SMBSMP_PARAMETERS };
	CEdit	m_editShareName;
	CEdit	m_editPath;
	CString	m_strShareName;
	CString	m_strPath;
	CString	m_strRemark;
	//}}AFX_DATA
	CString	m_strPrevShareName;
	CString	m_strPrevPath;
	CString	m_strPrevRemark;

protected:
	enum
	{
		epropShareName,
		epropPath,
		epropRemark,
		epropMAX
	};
	CObjectProperty		m_rgProps[epropMAX];

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSmbSmpParamsPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	virtual const CObjectProperty *	Pprops(void) const	{ return m_rgProps; }
	virtual DWORD					Cprops(void) const	{ return sizeof(m_rgProps) / sizeof(CObjectProperty); }

// Implementation
protected:
	BOOL	BAllRequiredFieldsPresent(void) const;

	// Generated message map functions
	//{{AFX_MSG(CSmbSmpParamsPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeRequiredField();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};  //*** class CSmbSmpParamsPage

/////////////////////////////////////////////////////////////////////////////

#endif // _RESPROP_H_
