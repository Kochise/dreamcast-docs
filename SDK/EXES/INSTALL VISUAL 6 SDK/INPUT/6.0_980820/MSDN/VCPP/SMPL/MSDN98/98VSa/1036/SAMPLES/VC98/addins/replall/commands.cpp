// Commands.cpp : implementation file
//

#include "stdafx.h"
#include "ReplAll.h"
#include "Commands.h"
#include "replacedlg.h"

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

STDMETHODIMP CCommands::ReplAllCommandMethod() 
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	VERIFY_OK(m_pApplication->EnableModeless(VARIANT_FALSE));
	CReplaceDlg RepDlg;
	CComPtr<IDispatch> pTextEditorDisp;
	m_pApplication->get_TextEditor(&pTextEditorDisp);
	CComQIPtr<ITextEditor, &IID_ITextEditor> pTextEditor(pTextEditorDisp);
	pTextEditor->get_Emulation(&RepDlg.m_lEmulation);
	CComPtr<IDispatch> pActiveDocumentDisp;
	m_pApplication->get_ActiveDocument(&pActiveDocumentDisp);
	CComQIPtr<ITextDocument, &IID_ITextDocument> 
			pActiveDocument(pActiveDocumentDisp);
	if (pActiveDocument)
	{
		CComPtr<IDispatch> pTextSelectionDisp;
		pActiveDocument->get_Selection(&pTextSelectionDisp);
		CComQIPtr<ITextSelection, &IID_ITextSelection> 
				pTextSelection(pTextSelectionDisp);
		CComBSTR bstrText;
		pTextSelection->get_Text(&bstrText);
		RepDlg.m_strFindString = bstrText;
	}
	else
		RepDlg.m_strFindString = _T("");
	if (RepDlg.DoModal() == IDOK)
	{
		CComBSTR bstrFind = RepDlg.m_strFindString;
		CComBSTR bstrReplace = RepDlg.m_strReplaceString;

		CComPtr<IDispatch> pDocsDisp;
		m_pApplication->get_Documents(&pDocsDisp);
		CComQIPtr<IDocuments, &IID_IDocuments> pDocs(pDocsDisp);

		short stmp = 0;
		 
		if (RepDlg.m_bMatchCase == true)
			stmp += dsMatchCase;
		if (RepDlg.m_bRegularExpression == true)
			stmp += dsMatchRegExpCur;
		if (RepDlg.m_bMatchWholeWord == true)
			stmp += dsMatchWord;

		CComVariant varFlags = stmp;

		long lDocCount;
		pDocs->get_Count(&lDocCount);
		for (long lIndex = 1 ; lIndex <= lDocCount ; lIndex++)
		{
			CComVariant varItemNum = lIndex;
			CComPtr<IDispatch> pDocDisp;
			pDocs->Item(varItemNum, &pDocDisp);
			CComQIPtr<ITextDocument, &IID_ITextDocument> pTextDoc(pDocDisp);
			VARIANT_BOOL varRetVal;
			pTextDoc->ReplaceText(bstrFind, bstrReplace, varFlags, &varRetVal);
		}
	}

	VERIFY_OK(m_pApplication->EnableModeless(VARIANT_TRUE));
	
	return S_OK;
}
