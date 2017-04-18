/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/


// DSAddIn.h : header file
//

#if !defined(AFX_DSADDIN_H__6A06C136_4748_11D1_BC91_0000010016A6__INCLUDED_)
#define AFX_DSADDIN_H__6A06C136_4748_11D1_BC91_0000010016A6__INCLUDED_

#include "commands.h"

struct AddInCmd
{ 
    LPCTSTR szCommand; 
    int     idCmdString; 
    bool    bToolBarByDefault;
};

extern const AddInCmd AddInCommands[];
extern const int cAddInCommands;


// {6A06C123-4748-11D1-BC91-0000010016A6}
DEFINE_GUID(CLSID_DSAddIn,
0x6a06c123, 0x4748, 0x11d1, 0xbc, 0x91, 0, 0, 0x1, 0, 0x16, 0xa6);

/////////////////////////////////////////////////////////////////////////////
// CDSAddIn

class CDSAddIn : 
    public IDSAddIn,
    public CComObjectRoot,
    public CComCoClass<CDSAddIn, &CLSID_DSAddIn>
{
public:
    DECLARE_REGISTRY(CDSAddIn, "Window Tabs",
        "WNDTABS Developer Studio Add-in", IDS_WNDTABS_LONGNAME,
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

#endif // !defined(AFX_DSADDIN_H__6A06C136_4748_11D1_BC91_0000010016A6__INCLUDED)
