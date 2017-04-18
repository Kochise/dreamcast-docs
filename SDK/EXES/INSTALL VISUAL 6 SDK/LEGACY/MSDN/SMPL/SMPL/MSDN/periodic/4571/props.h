/////////////////////////////////////////////////////////////////////////////
// Props.h : header file
//
// This class defines custom modal property sheet 
// CWebProps.
//
// This is a part of the Webster HTTP Server application
// for Microsoft Systems Journal
//
 
#ifndef __PROPS_H__
#define __PROPS_H__

#include "Config.h"

/////////////////////////////////////////////////////////////////////////////
// CWebProps

class CWebProps : public CPropertySheet
{
	DECLARE_DYNAMIC(CWebProps)

// Construction
public:
	CWebProps(CWnd* pParentWnd = NULL);

// Attributes
public:
	CServer		m_Page1;
	CHTML		m_Page2;
	CLogging	m_Page3;
	CStatus		m_Page4;
	CAlert		m_Page5;

// Operations
public:
	void GetProps ( void ) ;
	void SetProps ( void ) ;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWebProps)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWebProps();

// Generated message map functions
protected:
	//{{AFX_MSG(CWebProps)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif	// __PROPS_H__