// cstm$$ITERATOR$$dlg.cpp : implementation file
//

#include "stdafx.h"
#include "$$root$$.h"
#include "cstm$$ITERATOR$$dlg.h"
#include "$$filebase$$aw.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustom$$ITERATOR$$Dlg dialog


CCustom$$ITERATOR$$Dlg::CCustom$$ITERATOR$$Dlg()
	: CAppWizStepDlg(CCustom$$ITERATOR$$Dlg::IDD)
{
	//{{AFX_DATA_INIT(CCustom$$ITERATOR$$Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCustom$$ITERATOR$$Dlg::DoDataExchange(CDataExchange* pDX)
{
	CAppWizStepDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustom$$ITERATOR$$Dlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

// This is called whenever the user presses Next, Back, or Finish with this step
//  present.  Do all validation & data exchange from the dialog in this function.
BOOL CCustom$$ITERATOR$$Dlg::OnDismiss()
{
	if (!UpdateData(TRUE))
		return FALSE;

	// TODO: Set template variables based on the dialog's data.

	return TRUE;    // return FALSE if the dialog shouldn't be dismissed
}


BEGIN_MESSAGE_MAP(CCustom$$ITERATOR$$Dlg, CAppWizStepDlg)
	//{{AFX_MSG_MAP(CCustom$$ITERATOR$$Dlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CCustom$$ITERATOR$$Dlg message handlers
