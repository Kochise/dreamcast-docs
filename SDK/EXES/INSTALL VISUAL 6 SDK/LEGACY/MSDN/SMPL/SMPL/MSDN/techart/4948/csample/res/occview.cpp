// OCCSampView.cpp : implementation of the COCCSampView class
//

#include "stdafx.h"
#include "OCCSamp.h"

#include "OCCDoc.h"
#include "OCCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IDC_FileList 1000

/////////////////////////////////////////////////////////////////////////////
// COCCSampView

IMPLEMENT_DYNCREATE(COCCSampView, CView)

BEGIN_MESSAGE_MAP(COCCSampView, CView)
	//{{AFX_MSG_MAP(COCCSampView)
	ON_COMMAND(IDC_PROPERTIES, OnProperties)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COCCSampView construction/destruction

COCCSampView::COCCSampView()
{
	// TODO: add construction code here
	m_fDocListCreated = FALSE;
}

COCCSampView::~COCCSampView()
{
}

BOOL COCCSampView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// COCCSampView drawing

void COCCSampView::OnDraw(CDC* pDC)
{
	COCCSampDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// COCCSampView diagnostics

#ifdef _DEBUG
void COCCSampView::AssertValid() const
{
	CView::AssertValid();
}

void COCCSampView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COCCSampDoc* COCCSampView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COCCSampDoc)));
	return (COCCSampDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COCCSampView message handlers

void COCCSampView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	CRect rect(10,10,400,100);

	if (!m_fDocListCreated)
	{
		if (m_docList.Create(LBS_NOTIFY|LBS_DISABLENOSCROLL|LBS_STANDARD|LBS_NOINTEGRALHEIGHT|LBS_WANTKEYBOARDINPUT, 
								rect, this, IDC_FileList))
		{
			m_fDocListCreated = TRUE;
			m_docList.ShowWindow(SW_SHOWNA);
		}
	}

}

void COCCSampView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	int i;

	COCCSampDoc *pDoc = GetDocument();

	if (m_docList != NULL)
	{
		m_docList.ResetContent();

		for (i = 0; i < pDoc->m_rgstrFileList.GetSize(); i++)
		{
			m_docList.AddString(pDoc->m_rgstrFileList[i]);
		}
	}
}


void COCCSampView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	COCCSampDoc *pDoc = GetDocument();

	if (pDoc->m_pJournalEntry != NULL)
		pDoc->m_pJournalEntry->Print();
	
	CView::OnPrint(pDC, pInfo);
}

#include "DocProps.h"

void COCCSampView::OnProperties() 
{
	// TODO: Add your command handler code here
	IMsocDocProps *pDocProps;

	if (m_docList == NULL || m_docList.GetCurSel() == LB_ERR || vpOC == NULL)
		return;

	CString strPathName;

	m_docList.GetText( m_docList.GetCurSel(), strPathName);

	pDocProps = vpOC->PidpCreateDocProps();

	if (pDocProps == NULL)
		return;

	LPCWSTR pwzPathName = ConvertToUnicode(strPathName);
	HRESULT hr;

	hr = pDocProps->Load(pwzPathName);

	if (FAILED(hr))
	{
		pDocProps->Release();
		return;
	}

	IMsocBuiltinDocProps* pBuiltInDocProps;

	if (FAILED(pDocProps->GetBuiltinDocProps(&pBuiltInDocProps)))
	{
		pDocProps->Release();
		return;
	}

	COleVariant varComments;

	if (FAILED(pBuiltInDocProps->GetProp(PROP_COMMENTS, &varComments)))
	{
		pDocProps->Release();
		return;
	}

	LPCSTR pszComments = ConvertToAnsi(varComments.bstrVal);

	CDocProps propsDlg;
	propsDlg.m_EditComments	= pszComments;
	propsDlg.m_pDocProps = pDocProps;
	propsDlg.m_pBuiltInDocProps = pBuiltInDocProps;

	propsDlg.DoModal();

	LPCWSTR pwzComments = ConvertToUnicode(propsDlg.m_EditComments);

	varComments = pwzComments;

	pBuiltInDocProps->SetProp(PROP_COMMENTS, &varComments);

	pwzPathName = ConvertToUnicode(strPathName);
	pDocProps->Save(pwzPathName, msocfDefault);

	varComments.Clear();

	pDocProps->Release();
}
