// DSAddIn.h : header file
//

#if !defined(AFX_DSADDIN_H__1433431C_B34A_11D0_A217_244106C10000__INCLUDED_)
#define AFX_DSADDIN_H__1433431C_B34A_11D0_A217_244106C10000__INCLUDED_

#include "commands.h"

// {14334309-B34A-11D0-A217-244106C10000}
DEFINE_GUID(CLSID_DSAddIn,
0x14334309, 0xb34a, 0x11d0, 0xa2, 0x17, 0x24, 0x41, 0x6, 0xc1, 0, 0);

/////////////////////////////////////////////////////////////////////////////
// CDSAddIn

class CDSAddIn : 
	public IDSAddIn,
	public CComObjectRoot,
	public CComCoClass<CDSAddIn, &CLSID_DSAddIn>
{
public:
	DECLARE_REGISTRY(CDSAddIn, "ReplAll.DSAddIn.1",
		"REPLALL Developer Studio Add-in", IDS_REPLALL_LONGNAME,
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

#endif // !defined(AFX_DSADDIN_H__1433431C_B34A_11D0_A217_244106C10000__INCLUDED)
