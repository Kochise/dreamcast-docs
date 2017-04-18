//////////////////
// Typical view implementation, nothing special
//
#include "stdafx.h"
#include "doc.h"
#include "view.h"

IMPLEMENT_DYNCREATE(CMyView, CView)

BEGIN_MESSAGE_MAP(CMyView, CView)
	//{{AFX_MSG_MAP(CMyView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CMyView::CMyView()
{
}

CMyView::~CMyView()
{
}

void CMyView::OnDraw(CDC* pDC)
{
	const char* msg = "Double click on toolbar";
	CRect rc;
	GetClientRect(&rc);
	pDC->DrawText(msg, strlen(msg), &rc, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
}

