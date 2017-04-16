// necframe.cpp : implementation file
//

#include "stdafx.h"
#include "viewfile.h"

#include "fileview.h"
#include "viewfdoc.h"

#define NEHEADERS
#include "headers.h"
#undef NEHEADERS

#include "neview.h"


#include "childfrm.h"
#include "necframe.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNECFrame

IMPLEMENT_DYNCREATE(CNECFrame, CChildFrame)

CNECFrame::CNECFrame()
{
}

CNECFrame::~CNECFrame()
{
}


BEGIN_MESSAGE_MAP(CNECFrame, CChildFrame)
	//{{AFX_MSG_MAP(CNECFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CNECFrame message handlers

BOOL CNECFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{  
 m_iNumberRows = 3;
 m_iNumberCols = 2;
 m_ViewClass = RUNTIME_CLASS(CNEView);
 if (!CChildFrame::OnCreateClient(lpcs,pContext)) return FALSE;

 _try {

//
// the following code extracts the new exe header from the mapped file image
// and displays it in the first pane.
//

       CNEView *cfMyPointer = (CNEView *)m_wndSplitter.GetPane(0,0);
       PIMAGE_DOS_HEADER lpImage = (PIMAGE_DOS_HEADER)m_AssociatedDocument->AdjustPointerAbsolute(0);
       PIMAGE_OS2_HEADER lpNewHeader = (PIMAGE_OS2_HEADER)(unsigned char *)m_AssociatedDocument->AdjustPointerAbsolute(lpImage->e_lfanew);
       cfMyPointer->FillInTaggedData((unsigned char *)lpNewHeader,&tlNEHeader);

//
// the following code extracts the  imported name table from the mapped file image
// and displays it in the second pane.
//


       int iModuleEntries = lpNewHeader->ne_cmod;
       HEADERTEMPLATE hT = {"Imported Names: ","%s"};
       unsigned char *pImportTable;
       pImportTable = m_AssociatedDocument->AdjustPointerRelative(lpNewHeader->ne_imptab);
       unsigned char *pModuleTable;
       pModuleTable = (unsigned char *)lpNewHeader;
       pModuleTable+=((PIMAGE_OS2_HEADER)pModuleTable)->ne_modtab;
       cfMyPointer = (CNEView *)m_wndSplitter.GetPane(0,1);
       cfMyPointer->FillInChainedStructures(iModuleEntries, &hT,(WORD *)pModuleTable,pImportTable);

//
// the following code extracts the resident name table from the mapped file image
// and displays it in the third pane.
//
       HEADERTEMPLATE htTemplateResident = {"Resident names: ","%s @ ordinal %d"};
       cfMyPointer->FillInFlatStructures(&htTemplateResident, ((unsigned char *)lpNewHeader)+lpNewHeader->ne_restab);

// the following code extracts the non-resident name table.

       HEADERTEMPLATE htTemplateNonResident = {"Non-resident names: ","%s @ ordinal %d"};
       cfMyPointer->FillInFlatStructures(&htTemplateNonResident, ((unsigned char *)lpImage)+lpNewHeader->ne_nrestab);

// now do the entry table

       cfMyPointer = (CNEView *)m_wndSplitter.GetPane(1,0);
       cfMyPointer->FillInEntryTable((unsigned char *)lpNewHeader+lpNewHeader->ne_enttab);

// now do the segment table...

       cfMyPointer = (CNEView *)m_wndSplitter.GetPane(1,1);
       cfMyPointer->FillInSegmentTable((SEGENTRY *)((unsigned char *)lpNewHeader+lpNewHeader->ne_segtab),lpNewHeader->ne_cseg,lpNewHeader->ne_align);
       cfMyPointer = (CNEView *)m_wndSplitter.GetPane(2,0);
       cfMyPointer->FillInResourceTable((unsigned char *)lpNewHeader+lpNewHeader->ne_rsrctab);

      }
 _except (GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
	{ 
	 AfxMessageBox("corrupted file; can not display all information");
	}
 return TRUE;
};

CNEView *CNECFrame::GetDLLPane(void)
{ 
 return (CNEView *)m_wndSplitter.GetPane(2,1);
};

