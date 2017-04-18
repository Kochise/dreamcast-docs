// splitfrm.cpp : implementation file
//

#include "stdafx.h"
#include "subsplit.h"

#include "comclass.h"

//#include "protocol.h"

#include "splitfrm.h"

#include "commcdoc.h"
#include "commcvw.h"



#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// csplitframe

IMPLEMENT_DYNCREATE(csplitframe, CMDIChildWnd)

csplitframe::csplitframe()
{ m_wndSplitter = new csubsplit();
}

csplitframe::~csplitframe()
{ delete(m_wndSplitter);
}

BOOL csplitframe::OnCreateClient(LPCREATESTRUCT /*lpcs*/, CCreateContext* pContext)
{	
	if (!m_wndSplitter->CreateStatic(this,2, 1))
	    return FALSE;
	m_wndSplitter->CreateView(0,0,RUNTIME_CLASS(CWriterView),CSize(10,10),pContext);
//    ((CCommView *)(m_wndSplitter->GetPane(0,0)))->m_pFrame = this;
//    m_wndSplitter->Backlink((CCommView *)m_wndSplitter->GetPane(0,0));
    m_wndSplitter->CreateView(1,0,RUNTIME_CLASS(CReaderView),CSize(10,10),pContext);
    ((CEditView *)(m_wndSplitter->GetPane(1,0)))->GetEditCtrl().SetReadOnly(TRUE);
    ((CCommchatDoc *)pContext->m_pCurrentDoc)->m_WriterView=(CWriterView *)m_wndSplitter->GetPane(0,0);
	((CCommchatDoc *)pContext->m_pCurrentDoc)->m_ReaderView=(CReaderView *)m_wndSplitter->GetPane(1,0);
	return TRUE;
}

BEGIN_MESSAGE_MAP(csplitframe, CMDIChildWnd)
	//{{AFX_MSG_MAP(csplitframe)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// csplitframe message handlers


void csplitframe::OnSize(UINT nType, int cx, int cy)
{	RECT rcSize;
	GetClientRect(&rcSize);
    m_wndSplitter->SetRowInfo(0,rcSize.bottom/2,10);
	m_wndSplitter->RecalcLayout();
	CMDIChildWnd::OnSize(nType, cx, cy);
	
}

