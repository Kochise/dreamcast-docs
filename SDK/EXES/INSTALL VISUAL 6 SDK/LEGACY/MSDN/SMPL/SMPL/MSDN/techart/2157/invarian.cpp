// invarian.cpp : implementation file
//

#include "stdafx.h"
#include "dldetect.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInvariantDoc

IMPLEMENT_SERIAL(CInvariantDoc, CPetriNetDoc, 0 /* schema number*/ )

CInvariantDoc::CInvariantDoc()
{
}

BOOL CInvariantDoc::OnNewDocument()
{
	if (!CPetriNetDoc::OnNewDocument())
		return FALSE;
	return TRUE;
}

CInvariantDoc::~CInvariantDoc()
{
}


BEGIN_MESSAGE_MAP(CInvariantDoc, CPetriNetDoc)
	//{{AFX_MSG_MAP(CInvariantDoc)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ASANET, OnUpdateViewAsanet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInvariantDoc serialization

void CInvariantDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CInvariantDoc commands

CString CInvariantDoc::GrabNameFromNet(BOOL bType, int iIndex)
{ 
if (bType)
{CString csResult= cnvAttachedView->GrabNameFromNet(bType, iIndex);
if (csResult.GetLength() <5)
   csResult+="     ";
return csResult;
}
else 
{char szBuf[5];
 sprintf(szBuf,"I%d",iIndex);
 CString csResult = (CString)szBuf;
 BOOL bToggle=FALSE;
 while (csResult.GetLength() < 5) 
  {if (bToggle)
   csResult=" "+csResult;
   else
   csResult+=" ";
   bToggle=!bToggle;
  };
 return csResult;
};
}

void CInvariantDoc::OnUpdateViewAsanet(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(FALSE);
	// TODO: Add your command update UI handler code here
	
}
