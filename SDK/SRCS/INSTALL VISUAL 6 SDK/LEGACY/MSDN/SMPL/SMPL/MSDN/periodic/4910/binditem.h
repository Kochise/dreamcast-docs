// binditem.h : interface of the DocObject OLE server item class
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1995 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#ifndef __BINDITEM_H__
#define __BINDITEM_H__

#include "binddoc.h"    // for CDocObjectServerDoc definition

class CDocObjectServerItem : public COleServerItem
{
	DECLARE_DYNAMIC(CDocObjectServerItem)

// Constructors
protected:
	CDocObjectServerItem(COleServerDoc* pServerDoc, BOOL bAutoDelete);

// Attributes
public:
	CDocObjectServerDoc* GetDocument() const
		{ return (CDocObjectServerDoc*)COleServerItem::GetDocument(); }

// Overridables
public:

// Implementation
public:
	virtual ~CDocObjectServerItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

   // Overrides
protected:
   virtual void OnHide();
   virtual void OnOpen();
   virtual void OnShow();
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDocObjectServerItem)
	//}}AFX_VIRTUAL

};

/////////////////////////////////////////////////////////////////////////////

#endif // __BINDITEM_H__
