// Commands.cpp : implementation file
//
// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.


#include "stdafx.h"
#include "API2Help.h"
#include "Commands.h"
#include "Welcome.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCommands

CCommands::CCommands()
{
	m_pApplication = NULL;
}

CCommands::~CCommands()
{
	ASSERT (m_pApplication != NULL);
	m_pApplication->Release();
}

void CCommands::SetApplicationObject(IApplication* pApplication)
{
	// This function assumes pApplication has already been AddRef'd
	//  for us, which CDSAddIn did in its QueryInterface call
	//  just before it called us.
	m_pApplication = pApplication;
}


/////////////////////////////////////////////////////////////////////////////
// CCommands methods

STDMETHODIMP CCommands::API2HelpCommandMethod()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	VERIFY_OK(m_pApplication->EnableModeless(VARIANT_FALSE));
	CComBSTR bStr;
	CComPtr<IDispatch> lpDispActDoc, lpDispSel;
	VERIFY_OK(m_pApplication->get_ActiveDocument(&lpDispActDoc));
	if (lpDispActDoc == NULL)
		AfxMessageBox(IDS_NODOC_WARN);
	else
	{
		CComQIPtr<ITextDocument, &IID_ITextDocument> lpActDoc(lpDispActDoc);
		if (FAILED(lpActDoc->get_Selection(&lpDispSel)))
			AfxMessageBox(IDS_NOTEXTSEL);
		else
		{
			CComQIPtr<ITextSelection, &IID_ITextSelection> lpSel(lpDispSel);
			if (FAILED(lpSel->get_Text(&bStr)))
				AfxMessageBox(IDS_COULDNOTRETRIEVE);
			else
			{
				CString cStr = bStr;
				if (cStr == "")
					AfxMessageBox(IDS_NODOC_WARN);
				else
				{
					CWelcome WelcomeDlg(cStr, NULL);
					WelcomeDlg.DoModal();
				}
			}
		}
	}
	VERIFY_OK(m_pApplication->EnableModeless(VARIANT_TRUE));
	return S_OK;
}
