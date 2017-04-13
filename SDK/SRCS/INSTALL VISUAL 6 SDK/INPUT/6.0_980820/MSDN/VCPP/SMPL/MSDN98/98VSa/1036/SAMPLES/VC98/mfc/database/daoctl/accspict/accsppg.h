// AccsPpg.h : Declaration of the CAccessPictPropPage property page class.
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

////////////////////////////////////////////////////////////////////////////
// CAccessPictPropPage : See AccsPpg.cpp.cpp for implementation.

class CAccessPictPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CAccessPictPropPage)
	DECLARE_OLECREATE_EX(CAccessPictPropPage)

// Constructor
public:
	CAccessPictPropPage();

// Dialog Data
	//{{AFX_DATA(CAccessPictPropPage)
	enum { IDD = IDD_PROPPAGE_ACCESSPICT };
	BOOL    m_bStretch;
	BOOL    m_bPreserve;
	CString m_strCaption;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CAccessPictPropPage)
	afx_msg void OnStretch();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
