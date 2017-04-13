// CntrItem.h : interface of the CContainerMFCCntrItem class
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


#if !defined(AFX_CNTRITEM_H__925782D2_9815_11D0_944C_00A0C903487E__INCLUDED_)
#define AFX_CNTRITEM_H__925782D2_9815_11D0_944C_00A0C903487E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CContainerMFCDoc;
class CContainerMFCView;

class CContainerMFCCntrItem : public COleClientItem
{
	DECLARE_SERIAL(CContainerMFCCntrItem)

// Constructors
public:
	CContainerMFCCntrItem(CContainerMFCDoc* pContainer = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE.
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer.

// Attributes
public:
	CContainerMFCDoc* GetDocument()
		{ return (CContainerMFCDoc*)COleClientItem::GetDocument(); }
	CContainerMFCView* GetActiveView()
		{ return (CContainerMFCView*)COleClientItem::GetActiveView(); }

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CContainerMFCCntrItem)
	public:
	virtual void OnChange(OLE_NOTIFICATION wNotification, DWORD dwParam);
	virtual void OnActivate();
	protected:
	virtual void OnGetItemPosition(CRect& rPosition);
	virtual void OnDeactivateUI(BOOL bUndoable);
	virtual BOOL OnChangeItemPosition(const CRect& rectPos);
	//}}AFX_VIRTUAL

// Implementation
public:
	~CContainerMFCCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	virtual void Serialize(CArchive& ar);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNTRITEM_H__925782D2_9815_11D0_944C_00A0C903487E__INCLUDED_)
