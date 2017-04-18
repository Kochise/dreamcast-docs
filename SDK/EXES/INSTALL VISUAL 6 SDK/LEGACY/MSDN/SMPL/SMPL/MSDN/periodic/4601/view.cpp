////////////////////////////////////////////////////////////////
// VIEW.CPP: Content-impaired implementation of three views.
//
#include "stdafx.h"
#include "enumdoc.h"
#include "doc.h"
#include "view.h"

IMPLEMENT_DYNAMIC(CBaseView, CView)
IMPLEMENT_DYNCREATE(CViewA, CBaseView)
IMPLEMENT_DYNCREATE(CViewB, CBaseView)

void CBaseView::OnDraw(CDC* pDC)
{
}

void CViewA::OnDraw(CDC* pDC)
{
}

void CViewB::OnDraw(CDC* pDC)
{
}
