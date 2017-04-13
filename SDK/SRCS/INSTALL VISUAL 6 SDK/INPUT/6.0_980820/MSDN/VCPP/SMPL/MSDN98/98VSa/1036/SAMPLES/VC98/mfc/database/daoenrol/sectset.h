// sectset.h : interface of the CsectionSet class
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

class CsectionSet : public CDaoRecordset
{
public:
	CsectionSet(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CsectionSet)

// Field/Param Data
	//{{AFX_FIELD(CsectionSet, CDaoRecordset)
	CString m_CourseID;
	CString m_SectionNo;
	CString m_InstructorID;
	CString m_RoomNo;
	CString m_Schedule;
	short   m_Capacity;
	//}}AFX_FIELD
	CString m_strCourseIDParam;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CsectionSet)
	public:
	virtual CString GetDefaultSQL();    // default SQL for Recordset
	virtual void DoFieldExchange(CDaoFieldExchange* pFX);   // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};
