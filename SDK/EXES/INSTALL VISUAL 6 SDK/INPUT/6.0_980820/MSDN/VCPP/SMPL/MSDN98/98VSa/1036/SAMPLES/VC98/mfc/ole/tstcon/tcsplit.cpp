// TCSplitter.Cpp : implementation file
//

#include "StdAfx.H"
#include "TestCon.H"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTCSplitter

IMPLEMENT_DYNAMIC( CTCSplitter, CSplitterWnd )

CTCSplitter::CTCSplitter()
{
}

CTCSplitter::~CTCSplitter()
{
}

BEGIN_MESSAGE_MAP(CTCSplitter, CSplitterWnd)
	//{{AFX_MSG_MAP(CTCSplitter)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
   ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCSplitter message handlers

HBRUSH CTCSplitter::OnCtlColor( CDC* pDC, CWnd* pWnd, UINT nCtlColor )
{
   if( nCtlColor == CTLCOLOR_STATIC )
   {
	  return( GetSysColorBrush( COLOR_WINDOW ) );
   }

   return( CSplitterWnd::OnCtlColor( pDC, pWnd, nCtlColor ) );
}
