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
#if !defined(AFX_STOCKSOURCEMFC_H__2B3B4A85_AD59_11D0_9476_00A0C903487E__INCLUDED_)
#define AFX_STOCKSOURCEMFC_H__2B3B4A85_AD59_11D0_9476_00A0C903487E__INCLUDED_

// STOCKSOURCEMFC.H - Header file for your Internet Server
//    StockSourceMFC Extension

#include "resource.h"
#include "stockdatamgr.h"

class CStockSourceMFCExtension : public CHttpServer
{
public:
	CStockSourceMFCExtension();
	~CStockSourceMFCExtension();

// Overrides
	// ClassWizard generated virtual function overrides
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//{{AFX_VIRTUAL(CStockSourceMFCExtension)
	public:
	virtual BOOL GetExtensionVersion(HSE_VERSION_INFO* pVer);
	//}}AFX_VIRTUAL

	// TODO: Add handlers for your commands here.
	// For example:

	void Default(CHttpServerContext* pCtxt);
	void QueryForStock(CHttpServerContext* pCtxt, LPCTSTR pstrString);

	DECLARE_PARSE_MAP()

	//{{AFX_MSG(CStockSourceMFCExtension)
	//}}AFX_MSG

protected:

	CStockDataMgr   m_stockDataMgr;
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STOCKSOURCEMFC_H__2B3B4A85_AD59_11D0_9476_00A0C903487E__INCLUDED)
