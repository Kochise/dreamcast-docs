// addform.h : interface of the CAddForm class
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

class CAddForm : public CDaoRecordView
{
protected:
	CAddForm(UINT nIDTemplate);
	DECLARE_DYNAMIC(CAddForm)

protected:
	BOOL m_bAddMode;

// Operations
public:
	virtual BOOL OnMove(UINT nIDMoveCommand);
	virtual BOOL RecordAdd();
	virtual BOOL RecordRefresh();
	virtual BOOL RecordDelete();

// Implementation
public:
	virtual ~CAddForm();
// Generated message map functions
protected:
	afx_msg void OnRecordAdd();
	afx_msg void OnRecordRefresh();
	afx_msg void OnRecordDelete();
	afx_msg void OnUpdateRecordFirst(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
};
