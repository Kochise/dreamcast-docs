// subsplit.cpp : implementation file
//

#include "stdafx.h"

#include "protocol.h"

#include "commchat.h"

#include "subsplit.h"

#include "comclass.h"


#include "commcdoc.h"
#include "commcvw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#include "afxres.h"
#define ID_SENDBOX AFX_IDW_PANE_FIRST
#define ID_RECEIVEBOX ID_SENDBOX+1       // hardcode ?!?!?!?!

extern CCommchatApp NEAR theApp;



/////////////////////////////////////////////////////////////////////////////
// csubsplit

IMPLEMENT_DYNCREATE(csubsplit, CSplitterWnd)

csubsplit::csubsplit()
{ }

csubsplit::~csubsplit()
{
}


BEGIN_MESSAGE_MAP(csubsplit, CSplitterWnd)
	//{{AFX_MSG_MAP(csubsplit)
 	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
     ON_EN_CHANGE(ID_SENDBOX,OnTextTyped)


END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// csubsplit message handlers

void csubsplit::OnTextTyped()
{
((CWriterView *)GetPane(0,0))->ReactToChanges(); 
//  m_ParentView->ReactToChanges();
};


void csubsplit::OnDestroy()
{
	CSplitterWnd::OnDestroy();
	delete (((CWriterView *)GetPane(0,0))->GetDocument()->cpProtocol);
    if (((CWriterView *)GetPane(0,0))->GetDocument()->m_bAreWeServer)
	  theApp.SetupListeningThread();
	// TODO: Add your message handler code here
	
}

