// Commands.h : header file
//

// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.


#if !defined(AFX_COMMANDS_H__17A222A8_431B_11D0_B88F_00C04FD7A0F0__INCLUDED_)
#define AFX_COMMANDS_H__17A222A8_431B_11D0_B88F_00C04FD7A0F0__INCLUDED_

#include "API2HelpTypes.h"

class CCommands :
	public CComDualImpl<ICommands, &IID_ICommands, &LIBID_API2Help>,
	public CComObjectRoot,
	public CComCoClass<CCommands, &CLSID_Commands>
{
protected:
	IApplication* m_pApplication;

public:
	CCommands();
	~CCommands();
	void SetApplicationObject(IApplication* m_pApplication);

	BEGIN_COM_MAP(CCommands)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ICommands)
	END_COM_MAP()
	DECLARE_NOT_AGGREGATABLE(CCommands)

public:
// ICommands methods
	STDMETHOD(API2HelpCommandMethod)(THIS);
};

typedef CComObject<CCommands> CCommandsObj;

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMMANDS_H__17A222A8_431B_11D0_B88F_00C04FD7A0F0__INCLUDED)
