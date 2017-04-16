// pecframe.cpp : implementation file
//

#include "stdafx.h"
#include "viewfile.h"

#include "fileview.h"
#include "viewfdoc.h"

#define PEHEADERS
#include "headers.h"
#undef PEHEADERS

#include "peview.h"

#include "childfrm.h"
#include "pecframe.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPECFrame

IMPLEMENT_DYNCREATE(CPECFrame, CChildFrame)

CPECFrame::CPECFrame()
{
}

CPECFrame::~CPECFrame()
{
}


BEGIN_MESSAGE_MAP(CPECFrame, CChildFrame)
	//{{AFX_MSG_MAP(CPECFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPECFrame message handlers

BOOL CPECFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{  m_iNumberRows = 3;
   m_iNumberCols = 2;
   m_ViewClass = RUNTIME_CLASS(CPEView);
	
if (!CChildFrame::OnCreateClient(lpcs, pContext)) return FALSE;

_try {
CPEView *cfMyPointer = (CPEView *)m_wndSplitter.GetPane(0,0);
PIMAGE_DOS_HEADER lpImage = (PIMAGE_DOS_HEADER)m_AssociatedDocument->AdjustPointerAbsolute(0);
PIMAGE_FILE_HEADER lpPEHeader = (PIMAGE_FILE_HEADER)(((CHAR *)lpImage)+lpImage->e_lfanew+sizeof(DWORD));
cfMyPointer->FillInTaggedData((unsigned char *)lpPEHeader,&tlPEHeader);
cfMyPointer->DetermineCharacteristics(lpPEHeader->Characteristics,alPEChars,sizeof(alPEChars)/sizeof(ANYELEMENT));
cfMyPointer->FillInTaggedData((unsigned char *)lpPEHeader+sizeof(IMAGE_FILE_HEADER),&tlPEOptionalHeader);

cfMyPointer = (CPEView *)m_wndSplitter.GetPane(1,0);
PIMAGE_OPTIONAL_HEADER pOptionalHeader = (PIMAGE_OPTIONAL_HEADER)(&lpPEHeader[1]);
PIMAGE_DATA_DIRECTORY pDataDirectories= pOptionalHeader->DataDirectory;
cfMyPointer->DumpDataDirectories(pDataDirectories,pOptionalHeader->NumberOfRvaAndSizes,DirectoryString);

cfMyPointer = (CPEView *)m_wndSplitter.GetPane(0,1);
cfMyPointer->DumpSectionTable((PIMAGE_SECTION_HEADER)(&pDataDirectories[IMAGE_NUMBEROF_DIRECTORY_ENTRIES]),lpPEHeader->NumberOfSections,TRUE);

// resources
cfMyPointer = (CPEView *)m_wndSplitter.GetPane(1,1);

PIMAGE_SECTION_HEADER pHeader = cfMyPointer->GetSectionHdrByName(lpImage,".rsrc");
if (pHeader)
{PIMAGE_RESOURCE_DIRECTORY pResDir = (PIMAGE_RESOURCE_DIRECTORY)(pHeader->PointerToRawData+(char *)lpImage);
cfMyPointer->DumpResourceDirectory(pResDir,(DWORD)pResDir,0,0);
}; 

cfMyPointer = (CPEView *)m_wndSplitter.GetPane(2,0);
pHeader = cfMyPointer->GetSectionHdrByName(lpImage,".idata");
if (pHeader)
  cfMyPointer->DumpImportsSection((char *)lpImage,pHeader);

//cfMyPointer = (CPEView *)m_wndSplitter.GetPane(2,1);
pHeader = cfMyPointer->GetSectionHdrByName(lpImage,".edata");
if (pHeader)
  cfMyPointer->DumpExportsSection((char *)lpImage,pHeader);

// now do the debug stuff... in order not to clog up the splitter window, we
// cram this info into the NE header window...

cfMyPointer = (CPEView *)m_wndSplitter.GetPane(0,0);
pHeader = cfMyPointer->GetSectionHdrByName(lpImage,".debug");
if (pHeader)
  cfMyPointer->DumpDebugDirectory((char *)lpImage,pHeader,pOptionalHeader->DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG]);
}
_except (GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION?
         EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
	{ AfxMessageBox("corrupted file; can not display all information");
	}


return TRUE;
}

CPEView *CPECFrame::GetDLLPane(void)
{ return (CPEView *)m_wndSplitter.GetPane(2,1);
};
