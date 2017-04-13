// coursese.h : header file
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
// CCourseSet DAO recordset

class CCourseSet : public CDaoRecordset
{
public:
	CCourseSet(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CCourseSet)

// Field/Param Data
	//{{AFX_FIELD(CCourseSet, CDaoRecordset)
	CString m_CourseID;
	CString m_CourseTitle;
	short   m_Hours;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCourseSet)
	public:
	virtual CString GetDefaultSQL();        // Default SQL for Recordset
	virtual void DoFieldExchange(CDaoFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};
