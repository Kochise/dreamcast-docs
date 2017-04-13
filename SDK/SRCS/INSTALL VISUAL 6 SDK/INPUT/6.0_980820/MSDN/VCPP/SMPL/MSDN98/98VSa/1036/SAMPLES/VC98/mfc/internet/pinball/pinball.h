#if !defined(AFX_PINBALL_H__2DB22EF2_A50F_11D1_8E53_00AA00A4BCA9__INCLUDED_)
#define AFX_PINBALL_H__2DB22EF2_A50F_11D1_8E53_00AA00A4BCA9__INCLUDED_

// PINBALL.H - Header file for your Internet Server
//    Pinball Extension
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

#include "resource.h"

class CPinballExtension : public CHttpServer
{
public:
	CPinballExtension();
	~CPinballExtension();

	// implementation
protected:
	BOOL SendGIFFile(CHttpServerContext* pCtxt, LPCTSTR pstrFile, LPCTSTR pstrPath);
	BOOL SendAFile(CHttpServerContext* pCtxt, LPCTSTR pstrFullPath, LPCTSTR pstrContentType);
	BOOL SendJPGFile(CHttpServerContext* pCtxt, LPCTSTR pstrFile, LPCTSTR pstrPath);

// Overrides
	// ClassWizard generated virtual function overrides
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//{{AFX_VIRTUAL(CPinballExtension)
	public:
	virtual BOOL GetExtensionVersion(HSE_VERSION_INFO* pVer);
	//}}AFX_VIRTUAL
	virtual BOOL TerminateExtension(DWORD dwFlags);

	BOOL LoadLongResource(CString& str, UINT nID);

	void GetImage(CHttpServerContext* pCtxt, long dwChoice);
	void Default(CHttpServerContext* pCtxt);

	DECLARE_PARSE_MAP()

	//{{AFX_MSG(CPinballExtension)
	//}}AFX_MSG
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PINBALL_H__2DB22EF2_A50F_11D1_8E53_00AA00A4BCA9__INCLUDED)
