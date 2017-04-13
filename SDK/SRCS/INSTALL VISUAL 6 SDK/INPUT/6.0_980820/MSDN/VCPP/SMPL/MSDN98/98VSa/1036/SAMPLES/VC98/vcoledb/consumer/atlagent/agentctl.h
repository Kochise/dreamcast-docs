// AgentCtl.h : Declaration of the CAgentCtl
//
// This is a part of the Active Template Library.
// Copyright (C) 1996-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Active Template Library Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Active Template Library product.

#ifndef __AGENTCTL_H_
#define __AGENTCTL_H_

#include "resource.h"       // main symbols
// Change the directory names here if you have installed the Microsoft Agent
// files into a different location
#import "C:\Program Files\Microsoft Agent\agentsvr.exe" no_namespace
#define AGENT_CHARACTER "C:\\Program Files\\Microsoft Agent\\merlinsfx.acs"

// Accessor to bring back the instructions from the database
class CInstruction
{
public:
	TCHAR   szCommand[11];
	TCHAR   szText[256];

BEGIN_COLUMN_MAP(CInstruction)
	COLUMN_ENTRY(2, szCommand)
	COLUMN_ENTRY(3, szText)
END_COLUMN_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CAgentCtl
class ATL_NO_VTABLE CAgentCtl :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAgentCtl, &CLSID_AgentCtl>,
	public IDispatchImpl<IAgentCtl, &IID_IAgentCtl, &LIBID_ATLAGENTLib>,
	public IObjectSafetyImpl<CAgentCtl, INTERFACESAFE_FOR_UNTRUSTED_CALLER>
{
public:
	CAgentCtl()
	{
		m_nSpeed = 10;
	}
	HRESULT FinalConstruct()
	{
		HRESULT hr = InitializeAgent();
		if (FAILED(hr))
		{
			TCHAR szText[129];
			wsprintf(szText, _T("Couldn't start Agent (0x%X)"), hr);
			MessageBox(NULL, szText, _T("ATLAgent"), 0);
			return hr;
		}

		hr = OpenDatabase();
		if (FAILED(hr))
		{
			TCHAR szText[129];
			wsprintf(szText, _T("Couldn't open Agent database (0x%X)"), hr);
			MessageBox(NULL, szText, _T("ATLAgent"), 0);
		}
		return hr;
	}
	HRESULT InitializeAgent()
	{
		HRESULT hr;
		long    lCharID;
		CComPtr<IDispatch>  pdCharacter;
		hr = m_pAgent.CreateInstance(__uuidof(AgentServer));
		if (FAILED(hr))
			return hr;

		hr = m_pAgent->Load(AGENT_CHARACTER, &lCharID, &m_nRequestID);
		if (FAILED(hr))
			return hr;

		hr = m_pAgent->GetCharacter(lCharID, &pdCharacter);
		if (FAILED(hr))
			return hr;

		m_pCharacter = pdCharacter;
		return S_OK;
	}
	HRESULT OpenDatabase()
	{
		CDataSource     db;

		// Open the database and create a session
		HRESULT hr = db.Open(_T("MSDASQL"), _T("Agent"), _T("Admin"));
		if (FAILED(hr))
			return hr;

		return m_session.Open(db);
	}

DECLARE_REGISTRY_RESOURCEID(IDR_AGENTCTL)

BEGIN_COM_MAP(CAgentCtl)
	COM_INTERFACE_ENTRY(IAgentCtl)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// IAgentCtl
public:
	STDMETHOD(Stop)();
	STDMETHOD(Animate)(/*[in]*/ BSTR Animation);
	STDMETHOD(get_Speed)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_Speed)(/*[in]*/ long newVal);
	STDMETHOD(SpeakText)(BSTR Text);
	STDMETHOD(SpeakFile)(BSTR FileName);
	STDMETHOD(Play)();
	void ProcessInstruction(const CInstruction& instruction);

	// Microsoft Agent stuff
	IAgentPtr           m_pAgent;
	IAgentCharacterPtr  m_pCharacter;
	long                m_nSpeed;
	long                m_nRequestID;
	// DTL stuff
	CSession            m_session;
};

#endif //__AGENTCTL_H_
