// dldmfdoc.cpp : implementation of the CPetriNetDoc class
//

#include "stdafx.h"

#include "dldetect.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPetriNetDoc

IMPLEMENT_DYNCREATE(CPetriNetDoc, CDocument)

BEGIN_MESSAGE_MAP(CPetriNetDoc, CDocument)
	//{{AFX_MSG_MAP(CPetriNetDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPetriNetDoc construction/destruction

CPetriNetDoc::CPetriNetDoc()
{
cmvAttachedView=(CMatrixView *)0;
cnvAttachedView=(CNetView *)0;
m_mCurrentMatrix= (matrix *)0;
}

CPetriNetDoc::~CPetriNetDoc()
{
}



void CPetriNetDoc::DeleteContents(void)
{
if (m_mCurrentMatrix!=(matrix *)0) delete m_mCurrentMatrix;
m_mCurrentMatrix= (matrix *)0;

}
// I would love to do the serialization method here, but the Serialize
// function only lets me work on a CArchive object, and I need file
// mappings, which I can not access via a CArchive. So I bypass his
// serialization chain and grab the attempt to open a file here. Oh, well...


BOOL CPetriNetDoc::OnOpenDocument(const char* pszPathName)
{
CView *cvNext;
POSITION pos;
pos=GetFirstViewPosition();
while (pos!=NULL)
{ cvNext= GetNextView(pos);
  if (cvNext->IsKindOf(RUNTIME_CLASS(CNetView)))
   { cnvAttachedView=(CNetView *)cvNext;
	break;
   };
};


HANDLE hFile;
if (!SaveModified())
 return(FALSE); 
// cnvAttachedView->NukeNet();
//cfdFileOpen.m_ofn.lpstrFilter = "Petri Net Files\0*.pnt\0\0";
if (INVALID_HANDLE_VALUE==(hFile=CreateFile(pszPathName,GENERIC_READ|GENERIC_READ,NULL,NULL,
					   	OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL)))
 {
 AfxMessageBox("File Open failed - check if the path name provided is correct!",MB_OK);

// probably something along the lines of ReportSaveLoadException goes here...
//MessageBox(pszPathName,"Error opening file:",MB_OK);
 return(FALSE);
 };
theApp.AddToRecentFileList(pszPathName);
HANDLE hFileMap;
LPVOID  lpFileView;
hFileMap = CreateFileMapping(hFile,NULL,PAGE_WRITECOPY,0,0,NULL);
if (!hFileMap) 
{
 AfxMessageBox("Could not create file mapping -- possible security problem",MB_OK);
 CloseHandle(hFile);
 return(FALSE);
};
lpFileView = MapViewOfFile(hFileMap,FILE_MAP_COPY,0,0,0);
if (!lpFileView) 
 {CloseHandle(hFileMap);
  CloseHandle(hFile);
 AfxMessageBox("Could not map view of file -- possible memory problem",MB_OK);
 return(FALSE);
 };
m_mCurrentMatrix = GrabFromFile(lpFileView);

if (m_mCurrentMatrix==(matrix *)0) 
 return(FALSE);
ConvertMatrixToNet(lpFileView,m_mCurrentMatrix);

UnmapViewOfFile(lpFileView);
CloseHandle(hFileMap);

CloseHandle(hFile);
SetPathName(pszPathName);
UpdateAllViews(NULL,0,NULL);

  return (TRUE);
}

BOOL CPetriNetDoc::OnSaveDocument(const char* pszPathName)
{
HANDLE hFile;


if (!(hFile=CreateFile(pszPathName,GENERIC_WRITE,NULL,NULL,
					   	CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL)))
	{
     AfxMessageBox("Error opening file",MB_OK);
     return(FALSE);
    };
// add logic here to have the view participate in dumping the file data
if (IsModified())
{
DeleteContents();
m_mCurrentMatrix=ConvertNetToMatrix();
};
if (m_mCurrentMatrix)
 {DumpToFile(hFile,m_mCurrentMatrix);
  cnvAttachedView->DumpCoordinateData(hFile);
 };
CloseHandle(hFile);
SetPathName(pszPathName);
SetModifiedFlag(FALSE);
return (TRUE);
}


/////////////////////////////////////////////////////////////////////////////
// CPetriNetDoc serialization

void CPetriNetDoc::Serialize(CArchive& ar)
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
// CPetriNetDoc diagnostics

#ifdef _DEBUG
void CPetriNetDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPetriNetDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPetriNetDoc commands



////////////////////////////////////////////////////////////////////////////
// Helper functions

CString CPetriNetDoc::GrabNameFromNet(BOOL bType, int iIndex)
{ 
CString csResult= cnvAttachedView->GrabNameFromNet(bType, iIndex);
if (csResult.GetLength() <5)
   csResult+="     ";
return csResult;
}


matrix *CPetriNetDoc::GrabFromFile(LPVOID  lpFileView)
{
 int iRows,iColumns,iC,iR;
 matrix *mResult;
 char *chToken;
 chToken = strtok((char *)lpFileView," \n\t\r");
 if (!chToken || (strncmp(chToken,"PNT",3)!=0))
   {
// inform the user of fishyness here...
MessageBeep(-1);
//MessageBox("File is not a valid Petri Net file!","Error:",MB_OK);
    return (matrix *)0;
   };
 iRows = atoi(strtok(NULL," \n\t\r"));
 iColumns = atoi(strtok(NULL," \n\t\r"));
// now build and fill in the matrix...
 mResult = new matrix(iRows,iColumns);
 if (!mResult) return mResult;
 for(iR=0;iR<iRows;iR++)
  for(iC=0;iC<iColumns;iC++)
    mResult->SetElement(iR,iC,atoi(strtok(NULL," \n\t\r")));
return (mResult);
}

#define DUMPIT WriteFile(hFile,lpMem,strlen(lpMem),&iWritten,NULL)


void CPetriNetDoc::DumpToFile(HANDLE hFile, matrix *mMatrix)
{ char lpMem[20];
  unsigned long iWritten;
  int iR,iC;
  wsprintf(lpMem,"PNT\n\0");      /* magic cookie for petri net files */
  DUMPIT;
  wsprintf(lpMem,"%d %d\n\0",mMatrix->iRows,mMatrix->iColumns);
  DUMPIT;
  for (iR=0;iR<mMatrix->iRows;iR++)
   {for (iC=0;iC<mMatrix->iColumns;iC++)
     {wsprintf(lpMem,"%-d \0",mMatrix->GetElement(iR,iC));
	  DUMPIT;
	 };
	wsprintf(lpMem,"\n\0");
  DUMPIT;
   };
}

matrix *CPetriNetDoc::ConvertNetToMatrix()
/* This function will first traverse the list of places and transitions
   and assign each an ordinal (which will just be its position in the
   chain). It will then traverse the associated connection lists for each
   object and make an entry in the matrix.  */
{matrix *mResult;
 TP *anchor;
 transition *anchort;
 int iRowCount=0, iColumnCount=0;
 anchor = cnvAttachedView->m_places;
/* places are the rows, so we start with the row count...*/
 while (anchor != (TP *)NULL)
   { 
     anchor->iOrdinal= iRowCount;
	 iRowCount++;
	 anchor = anchor->Succ();
   };
 anchor = cnvAttachedView->m_transitions;
 while (anchor != (TP *)NULL)
   { 
     anchor->iOrdinal= iColumnCount;
	 iColumnCount++;
	 anchor = anchor->Succ();
   };
 if (!iRowCount || !iColumnCount) return ((matrix *)NULL);
 mResult = new matrix(iRowCount,iColumnCount);
 anchort=cnvAttachedView->m_transitions;
 while (anchort != (TP *)NULL)
  {	TPLIST *tpLConnect = anchort->GetConnections(TRUE);
    while (tpLConnect != (TPLIST *)NULL)
	  {mResult->SetElement(tpLConnect->tpElement->iOrdinal,anchort->iOrdinal,1);
	   tpLConnect = tpLConnect->Succ();
	  };
	tpLConnect = anchort->GetConnections(FALSE);
    while (tpLConnect != (TPLIST *)NULL)
	  {mResult->SetElement(tpLConnect->tpElement->iOrdinal,anchort->iOrdinal,-1);
	   tpLConnect = tpLConnect->Succ();
	  };

	anchort = (transition *)anchort->Succ();
  };
 return mResult;
}

void CPetriNetDoc::ConvertMatrixToNet(LPVOID lpFileView, matrix *mt)
{
int iRows,iColumns,iC,iR;
LPVOID lpMemory;
int iTPx, iTPy;
iRows=mt->iRows;
iColumns=mt->iColumns;
lpMemory = VirtualAlloc(0,(sizeof(TP *))*(iColumns+iRows),MEM_COMMIT,PAGE_READWRITE);
// first build a new list of elements according to how many rows&columns 
// there are...


for (iR=0;iR<iRows;iR++)
{ char *chToken1;
  place *newElement;
  newElement= new place(0,0);
  newElement->iOrdinal=atoi(strtok(NULL," \n\t\r"));
  chToken1=strtok(NULL," \n\t\r");
  if (!strcmp(chToken1,"no")) chToken1 = "";
  newElement->Name(CString(chToken1));
  iTPx= atoi(strtok(NULL," \n\t\r"));
  iTPy= atoi(strtok(NULL," \n\t\r"));
  newElement->Reposition(iTPx,iTPy);
  cnvAttachedView->RecalcScrollDimensions(iTPx,iTPy,TRUE);

  if (iR==0)  
    cnvAttachedView->m_places = newElement;
  else
    cnvAttachedView->m_places->AppendAtEnd(newElement);
((TP **)lpMemory)[iR]=newElement;
};


for (iC=0;iC<iColumns;iC++)
{ char *chToken1; 
  transition *newElement;
  newElement= new transition(0,0); 
  newElement->iOrdinal=atoi(strtok(NULL," \n\t\r"));
  chToken1=strtok(NULL," \n\t\r");
  if (!strcmp(chToken1,"no")) chToken1 = "";
  newElement->Name(CString(chToken1));
  iTPx= atoi(strtok(NULL," \n\t\r"));
  iTPy= atoi(strtok(NULL," \n\t\r"));
  newElement->Reposition(iTPx,iTPy);
  cnvAttachedView->RecalcScrollDimensions(iTPx,iTPy,TRUE);

  if (iC==0)
    cnvAttachedView->m_transitions = newElement;
  else
    cnvAttachedView->m_transitions->AppendAtEnd(newElement);
  ((TP **)lpMemory)[iR+iC+1]=newElement;
// at this point, we can already determine all connections for the current column
  for (iR=0;iR<iRows;iR++)
    switch (mt->GetElement(iR,iC))
	{ case 1: newElement->Connect((((TP **)lpMemory)[iR])); break;
	  case -1: ((TP **)lpMemory)[iR]->Connect(newElement); break;
	};

};
VirtualFree(lpMemory,(sizeof(TP *))*(iColumns+iRows),MEM_DECOMMIT); 
return;
}

void CPetriNetDoc::UpdateAllViews(CView *pSender, LPARAM lHint, CObject* pHint)
{
DeleteContents();
m_mCurrentMatrix=ConvertNetToMatrix();
CDocument::UpdateAllViews(pSender, lHint,pHint);
}

void CPetriNetDoc::ReflectChanges(void)
{
if (IsModified())
 UpdateAllViews(cnvAttachedView,0,NULL);
}
