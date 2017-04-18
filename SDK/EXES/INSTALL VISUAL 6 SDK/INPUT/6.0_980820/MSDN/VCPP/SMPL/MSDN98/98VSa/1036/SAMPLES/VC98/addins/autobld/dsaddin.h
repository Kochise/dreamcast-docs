// DSAddIn.h : header file
//

// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.

#if !defined(AFX_DSADDIN_H__D93F3A16_3DA9_11D0_B889_00C04FD7A0F0__INCLUDED_)
#define AFX_DSADDIN_H__D93F3A16_3DA9_11D0_B889_00C04FD7A0F0__INCLUDED_

#include "commands.h"

// {D93F3A03-3DA9-11D0-B889-00C04FD7A0F0}
DEFINE_GUID(CLSID_DSAddIn,
0xd93f3a03, 0x3da9, 0x11d0, 0xb8, 0x89, 0, 0xc0, 0x4f, 0xd7, 0xa0, 0xf0);

/////////////////////////////////////////////////////////////////////////////
// CDSAddIn

class CDSAddIn :
	public IDSAddIn,
	public CComObjectRoot,
	public CComCoClass<CDSAddIn, &CLSID_DSAddIn>
{
public:
	DECLARE_REGISTRY(CDSAddIn, "AutoBld.DSAddIn.1",
		"AUTOBLD Developer Studio Add-in", IDS_AUTOBLD_LONGNAME,
		THREADFLAGS_BOTH)

	CDSAddIn() {}
	BEGIN_COM_MAP(CDSAddIn)
		COM_INTERFACE_ENTRY(IDSAddIn)
	END_COM_MAP()
	DECLARE_NOT_AGGREGATABLE(CDSAddIn)

// IDSAddIns
public:
	STDMETHOD(OnConnection)(THIS_ IApplication* pApp, VARIANT_BOOL bFirstTime,
		long dwCookie, VARIANT_BOOL* OnConnection);
	STDMETHOD(OnDisconnection)(THIS_ VARIANT_BOOL bLastTime);

protected:
	CCommandsObj* m_pCommands;
	DWORD m_dwCookie;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DSADDIN_H__D93F3A16_3DA9_11D0_B889_00C04FD7A0F0__INCLUDED)
