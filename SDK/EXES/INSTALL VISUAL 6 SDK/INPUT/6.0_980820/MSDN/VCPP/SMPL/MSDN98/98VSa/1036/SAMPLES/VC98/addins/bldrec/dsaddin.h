// DSAddIn.h : header file
//

#if !defined(AFX_DSADDIN_H__36FDE874_EA61_11D0_B595_00A0C91BC942__INCLUDED_)
#define AFX_DSADDIN_H__36FDE874_EA61_11D0_B595_00A0C91BC942__INCLUDED_

#include "commands.h"

// {36FDE861-EA61-11D0-B595-00A0C91BC942}
DEFINE_GUID(CLSID_DSAddIn,
0x36fde861, 0xea61, 0x11d0, 0xb5, 0x95, 0, 0xa0, 0xc9, 0x1b, 0xc9, 0x42);

/////////////////////////////////////////////////////////////////////////////
// CDSAddIn

class CDSAddIn : 
	public IDSAddIn,
	public CComObjectRoot,
	public CComCoClass<CDSAddIn, &CLSID_DSAddIn>
{
public:
	DECLARE_REGISTRY(CDSAddIn, "Bldrec.DSAddIn.1",
		"BLDREC Developer Studio Add-in", IDS_BLDREC_LONGNAME,
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

#endif // !defined(AFX_DSADDIN_H__36FDE874_EA61_11D0_B595_00A0C91BC942__INCLUDED)
