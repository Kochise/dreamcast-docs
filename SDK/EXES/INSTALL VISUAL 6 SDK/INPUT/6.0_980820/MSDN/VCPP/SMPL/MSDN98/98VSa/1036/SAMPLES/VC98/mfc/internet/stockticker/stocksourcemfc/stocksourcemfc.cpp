// STOCKSOURCEMFC.CPP - Implementation file for your Internet Server
//    StockSourceMFC Extension
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

#include "stdafx.h"
#include "stocksourceMFC.h"

///////////////////////////////////////////////////////////////////////
// The one and only CWinApp object
// NOTE: You may remove this object if you alter your project to no
// longer use MFC in a DLL.

CWinApp theApp;

///////////////////////////////////////////////////////////////////////
// command-parsing map

BEGIN_PARSE_MAP(CStockSourceMFCExtension, CHttpServer)
	// TODO: insert your ON_PARSE_COMMAND() and
	// ON_PARSE_COMMAND_PARAMS() here to hook up your commands.
	// For example:

	DEFAULT_PARSE_COMMAND(Default, CStockSourceMFCExtension)
	ON_PARSE_COMMAND(QueryForStock, CStockSourceMFCExtension, ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Symbol=~")
END_PARSE_MAP(CStockSourceMFCExtension)


///////////////////////////////////////////////////////////////////////
// The one and only CStockSourceMFCExtension object

CStockSourceMFCExtension theExtension;


///////////////////////////////////////////////////////////////////////
// CStockSourceMFCExtension implementation

CStockSourceMFCExtension::CStockSourceMFCExtension()
{
}

CStockSourceMFCExtension::~CStockSourceMFCExtension()
{
}

BOOL CStockSourceMFCExtension::GetExtensionVersion(HSE_VERSION_INFO* pVer)
{
	// Call default implementation for initialization
	CHttpServer::GetExtensionVersion(pVer);

	// Load description string
	TCHAR sz[HSE_MAX_EXT_DLL_NAME_LEN+1];
	ISAPIVERIFY(::LoadString(AfxGetResourceHandle(),
			IDS_SERVER, sz, HSE_MAX_EXT_DLL_NAME_LEN));
	_tcscpy(pVer->lpszExtensionDesc, sz);
	return TRUE;
}

///////////////////////////////////////////////////////////////////////
// CStockSourceMFCExtension command handlers

void CStockSourceMFCExtension::Default(CHttpServerContext* pCtxt)
{
	StartContent(pCtxt);
	WriteTitle(pCtxt);

	*pCtxt << _T("This default message was produced by the Internet");
	*pCtxt << _T(" Server DLL Wizard. Edit your CStockSourceMFCExtension::Default()");
	*pCtxt << _T(" implementation to change it.\r\n");

	EndContent(pCtxt);
}


// Load stock symbol file and query for stock information. If the symbol is new then
// it is added to the list.  Save the list to the data file when finished.
//
void CStockSourceMFCExtension::QueryForStock(CHttpServerContext* pCtxt,
											 LPCTSTR pstrString)
{
	StartContent(pCtxt);
	WriteTitle(pCtxt);

	m_stockDataMgr.LoadStockSymbols();

	CStockData                  sd;
	m_stockDataMgr.LookUp(pstrString, sd);

	TCHAR   numBuf1[20];
	TCHAR   numBuf2[20];

	_stprintf(numBuf1, "%.3f", sd.m_fCur);
	_stprintf(numBuf2, "%.3f", sd.m_fChange);

	*pCtxt << _T("\n<h1>Query For Stock:</h1><hr>\n")
		   << _T("Current: ") << numBuf1 << _T("<P>\n")
		   << _T("Change: ") << numBuf2 << _T("<P>")
		   << _T("<hr>");

	EndContent(pCtxt);
	m_stockDataMgr.SaveStockSymbols();
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CStockSourceMFCExtension, CHttpServer)
	//{{AFX_MSG_MAP(CStockSourceMFCExtension)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif  // 0

///////////////////////////////////////////////////////////////////////
// If your extension will not use MFC, you'll need this code to make
// sure the extension objects can find the resource handle for the
// module.  If you convert your extension to not be dependent on MFC,
// remove the comments arounn the following AfxGetResourceHandle()
// and DllMain() functions, as well as the g_hInstance global.

/****

static HINSTANCE g_hInstance;

HINSTANCE AFXISAPI AfxGetResourceHandle()
{
	return g_hInstance;
}

BOOL WINAPI DllMain(HINSTANCE hInst, ULONG ulReason,
					LPVOID lpReserved)
{
	if (ulReason == DLL_PROCESS_ATTACH)
	{
		g_hInstance = hInst;
	}

	return TRUE;
}

****/
