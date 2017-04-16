// ptappvw.cpp : implementation of the CPtappView class
//

#include "stdafx.h"
#include "easyview.h"

#include "ptapp.h"

#include "ptappdoc.h"
#include "ptappvw.h"

#include <winnt.h>

#include "getname.h"

#define DLLNAME "pagetest.dll"
#define MUTEXNAME "PageTest"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPtappView

IMPLEMENT_DYNCREATE(CPtappView, CEasyOutputView)

BEGIN_MESSAGE_MAP(CPtappView, CEasyOutputView)
	//{{AFX_MSG_MAP(CPtappView)
	ON_COMMAND(IDC_LOADDLL, OnLoaddll)
	ON_COMMAND(IDC_LOCKRANGE, OnLockrange)
	ON_COMMAND(IDC_UNLOADDLL, OnUnloaddll)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_COMMAND(IDC_UNLOCKRANGE, OnUnlockrange)
	ON_COMMAND(IDC_MULTIPLETESTS, OnMultipletests)
	ON_COMMAND(IDC_HOGMEMORY, OnHogmemory)
	ON_COMMAND(IDC_UNHOGMEM, OnUnhogmem)
	ON_COMMAND(IDC_SMALLDLL, OnSmalldll)
	ON_COMMAND(IDC_LARGEFIXED, OnLargefixed)
	ON_COMMAND(IDC_LARGENOFIXUPS, OnLargenofixups)
	ON_COMMAND(IDC_CRTSUPPORT, OnCrtsupport)
	ON_COMMAND(IDC_FINISHDLL, OnFinishdll)
	ON_UPDATE_COMMAND_UI(IDC_CRTSUPPORT, OnUpdateCrtsupport)
	ON_UPDATE_COMMAND_UI(IDC_LARGEFIXED, OnUpdateLargefixed)
	ON_UPDATE_COMMAND_UI(IDC_LARGENOFIXUPS, OnUpdateLargenofixups)
	ON_UPDATE_COMMAND_UI(IDC_SMALLDLL, OnUpdateSmalldll)
	ON_COMMAND(IDC_RUNHOGGING, OnRunhogging)
	ON_COMMAND(IDC_LOCKRANEGMULTIPLE, OnLockranegmultiple)
	ON_COMMAND(IDC_LOADDLLNOFIXUPS, OnLoaddllnofixups)
	ON_COMMAND(IDC_DYNCRTPRE, OnDyncrtpre)
	ON_UPDATE_COMMAND_UI(IDC_DYNCRTPRE, OnUpdateDyncrtpre)
	ON_COMMAND(IDC_HASEXPORTS, OnHasexports)
	ON_UPDATE_COMMAND_UI(IDC_HASEXPORTS, OnUpdateHasexports)
	ON_COMMAND(IDC_BATCH, OnBatch)
	ON_COMMAND(IDC_CUSTOMDLL, OnCustomdll)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPtappView construction/destruction

CPtappView::CPtappView()
{
}

CPtappView::~CPtappView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CPtappView drawing

void CPtappView::OnDraw(CDC* pDC)
{
	CPtappDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

/////////////////////////////////////////////////////////////////////////////
// CPtappView diagnostics

#ifdef _DEBUG
void CPtappView::AssertValid() const
{
	CEasyOutputView::AssertValid();
}

void CPtappView::Dump(CDumpContext& dc) const
{
	CEasyOutputView::Dump(dc);
}

CPtappDoc* CPtappView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPtappDoc)));
	return (CPtappDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPtappView message handlers


int ThreadRoutine(CPtappView *cpObj)
{
 WaitForSingleObject(cpObj->m_hMutex,NULL);
 QueryPerformanceCounter(&cpObj->m_liNewVal);
 ReleaseMutex(cpObj->m_hMutex);
 return 0;
};

void CPtappView::OnLoaddll() 
{
  OnLoadDllHelper(TRUE);
}

void CPtappView::OnLoadDllHelper(BOOL bDisplayResults)
{
 // we now know what the preferred base address of the DLL is. Next we create a named
 // pipe and measure the time how long it takes the DLL to answer to the pipe.
 DWORD id;
 WaitForSingleObject(m_hMutex,INFINITE);
 HANDLE hThread=::CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ThreadRoutine,
                               (LPVOID)this,0,&id);
 if (!hThread) return; 
 if (!QueryPerformanceCounter(&m_liOldVal)) return;  // here's the current value...
// we must use m_pstrDLL here to force the system to look through the path...
 m_hDLLInstance = LoadLibrary(m_pstrDLL);
 WaitForSingleObject(hThread,INFINITE);
  
 m_liDiffVal.HighPart = m_liNewVal.HighPart-m_liOldVal.HighPart;
 m_liDiffVal.LowPart = m_liNewVal.LowPart-m_liOldVal.LowPart;

 if (bDisplayResults)
 {
 if (m_dwImageBase == (unsigned long)m_hDLLInstance)
  sprintf(m_szBuf,"DLL was loaded at preferred address %x",m_dwImageBase);
 else
 sprintf(m_szBuf,"DLL was based at %x but loaded at %x",m_dwImageBase,m_hDLLInstance);
 AddStringandAdjust(m_szBuf);
// sprintf(m_szBuf,"began counting at %d %8lu",m_liOldVal.HighPart,m_liOldVal.LowPart);
// AddStringandAdjust(m_szBuf);
// sprintf(m_szBuf,"Library loaded at %d %8lu",m_liNewVal.HighPart,m_liNewVal.LowPart);	
// AddStringandAdjust(m_szBuf);
 sprintf(m_szBuf,"load time: %d %8lu",m_liDiffVal.HighPart,m_liDiffVal.LowPart);
 AddStringandAdjust(m_szBuf);
 };	

}


void CPtappView::OnLockrange() 
{
 LPVOID lpHogAddress;

 MapFile(m_pstrDLL);
 // Note: The performance counter queries are made in MapFile().
 m_liDiffVal.HighPart = m_liNewVal.HighPart-m_liOldVal.HighPart;
 m_liDiffVal.LowPart = m_liNewVal.LowPart-m_liOldVal.LowPart;

 sprintf(m_szBuf,"time spent locking memory range: %d %8lu",m_liDiffVal.HighPart,m_liDiffVal.LowPart);
 AddStringandAdjust(m_szBuf);	

}

void CPtappView::OnUnlockrange() 
{
 UnmapFile();
}


void CPtappView::OnUnloaddll() 
{
 FreeLibrary(m_hDLLInstance);
	
}

BOOL CPtappView::MapFile(LPCTSTR lpszFileName)
{ m_bObtainedMemoryThroughVirtualAlloc =FALSE;
// the file might not be in the current directory, so we go through a little extra work
// here in order to retrieve the real location...
  LPTSTR lpFileNamePortion;
  DWORD dwPathLength=
   SearchPath(NULL,lpszFileName,NULL,MAX_PATH,m_pstrFullPathDLL,&lpFileNamePortion);
  if (!dwPathLength || dwPathLength>MAX_PATH)
  {
   AfxMessageBox("Failed to locate DLL in search path");
   return FALSE;
  };
  sprintf(m_szBuf,"Found DLL at %s",m_pstrFullPathDLL);
  AddStringandAdjust(m_szBuf);
  if (INVALID_HANDLE_VALUE==(m_hFile=CreateFile(m_pstrFullPathDLL,GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,
					   	OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL)))
  {
   char szBuf[100];
   sprintf(szBuf,"file open failed with error code %d",GetLastError());
   AfxMessageBox(szBuf,MB_OK);
   return(FALSE);
  };
  QueryPerformanceCounter(&m_liOldVal); 
  m_hFileMapping = CreateFileMapping(m_hFile,NULL,PAGE_READONLY,0,0,NULL);
  if (!m_hFileMapping) 
  {
   AfxMessageBox("Could not create file mapping -- possible security problem",MB_OK);
   goto ErrorExit;
  };
 // watch out here - the function is somewhat overloaded; if called from OnLockRange(),
 // m_dwImageBase is already assigned the current image base, so the file gets mapped
 // to the current image. If called from OnFinishDll(), m_dwImageBase is 0, so that 
 // the OS chooses the address. Thus, the VirtualAlloc case must consider both cases...
  m_lpImage = (char *)MapViewOfFileEx(m_hFileMapping,FILE_MAP_READ,0,0,0,(char *)m_dwImageBase);
  if (m_lpImage)
  {
   QueryPerformanceCounter(&m_liNewVal);  // here's the current value...
   sprintf(m_szBuf,"Successfully mapped view of file to %8lx",m_lpImage);
   AddStringandAdjust(m_szBuf);
  }
  else 
  {
   DWORD dwFileSizeLo,dwFileSizeHigh,dwBytesRead,dwBytesRequested;
   char *lpAddress=NULL;
   GetLastError();
   CloseHandle(m_hFileMapping);
   if (m_dwImageBase)
   {
    lpAddress=(char *)m_dwImageBase;
	dwBytesRequested=m_dwImageSize;
   }
   else
   {
    dwFileSizeLo=GetFileSize(m_hFile,&dwFileSizeHigh);
    dwBytesRequested=dwFileSizeLo;
   };
   QueryPerformanceCounter(&m_liOldVal); 
   m_lpImage=(char *)VirtualAlloc(lpAddress,dwBytesRequested,MEM_RESERVE|MEM_COMMIT,PAGE_READWRITE);
   QueryPerformanceCounter(&m_liNewVal);  // here's the current value...

   if (!m_lpImage)
   {
    DWORD dwError=GetLastError();
	sprintf(m_szBuf,"Could not allocate %d bytes @%8lx due to error %d",dwBytesRequested,lpAddress,dwError);
	AddStringandAdjust(m_szBuf);
    goto ErrorExit;
   }
   else
   {
    m_bObtainedMemoryThroughVirtualAlloc = TRUE;
   	if (ReadFile(m_hFile,m_lpImage,dwBytesRequested,&dwBytesRead,NULL))
	{
	 sprintf(m_szBuf,"read %d bytes into location %8lx",dwBytesRead,m_lpImage);
	 AddStringandAdjust(m_szBuf);
	}
	else
	{
	 sprintf(m_szBuf,"failed to read DLL image into memory due to error %d",GetLastError());
	 AddStringandAdjust(m_szBuf);
     VirtualFree(m_lpImage,0,MEM_RELEASE);
	 CloseHandle(m_hFile);
	 return FALSE;
	};
   };
  };

/*
 // this one doesn't work because a library loaded as a datafile is not normally based
 // at its preferred address  
  m_lpImage=(char *)LoadLibraryEx(lpszFileName,NULL,LOAD_LIBRARY_AS_DATAFILE);
  if (!m_lpImage) 
  {
   AfxMessageBox("Could not load DLL image -- possible memory problem",MB_OK);
   return(FALSE);
  };
*/
  sprintf(m_szBuf,"Mapped DLL image to address %8lx",m_lpImage);
  AddStringandAdjust(m_szBuf);

  return TRUE;
  ErrorExit:
  CloseHandle(m_hFile);
  return FALSE;
};

BOOL CPtappView::UnmapFile()
{
 if (m_bObtainedMemoryThroughVirtualAlloc) 
 {
  VirtualFree(m_lpImage,0,MEM_RELEASE);
 }
 else
 {
  UnmapViewOfFile(m_lpImage);
  CloseHandle(m_hFileMapping);
 };
 CloseHandle(m_hFile);
 return TRUE;
}

int CPtappView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CEasyOutputView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
 m_hMutex = CreateMutex (NULL,FALSE,MUTEXNAME); // we own the mutex initially...
 if (m_hMutex == NULL)
 {
  AddStringandAdjust("Failed to Create Mutex");
  return -1;     
 };
 if (!QueryPerformanceFrequency(&m_liOldVal))
 {
  AddStringandAdjust("performance counting not supported...");
  return -1;
 };
 sprintf(m_szBuf,"Resolution supported by counter: %d %8lu",m_liOldVal.HighPart,m_liOldVal.LowPart);
 AddStringandAdjust(m_szBuf);
 for (int i=0;i<8;i++)
  m_bTypeFlags[i]=0;
 strcpy(m_pstrDLL,"nnnnnnnn.dll");
 return 0;
}

void CPtappView::OnDestroy() 
{
	CEasyOutputView::OnDestroy();
	
	CloseHandle(m_hMutex);	
}


#define NUMBEROFTESTS 100

void CPtappView::OnMultipletests() 
{AddStringandAdjust("Running initial loading test...");
 OnLoaddll();   // throw away results of first loading
 OnUnloaddll();
 AddStringandAdjust("Now running test...");
 LARGE_INTEGER liMax,liMin;
 m_liSum.LowPart=0;
 m_liSum.HighPart=0;
 liMin.LowPart=0;
 liMin.HighPart=10000;   // RAc - change this
 liMax.LowPart=0;
 liMax.HighPart=0;

 for (int i = 0; i<NUMBEROFTESTS; i++)
 {
  sprintf(m_szBuf,"Running test #%d",i);
  OnLoadDllHelper(FALSE);
  m_liSum.LowPart+=m_liDiffVal.LowPart;
  m_liSum.HighPart+=m_liDiffVal.HighPart;
  if (m_liDiffVal.HighPart>liMax.HighPart || (m_liDiffVal.HighPart==liMax.HighPart && m_liDiffVal.LowPart>liMax.LowPart))
  {
   liMax.HighPart=m_liDiffVal.HighPart;
   liMax.LowPart=m_liDiffVal.LowPart;
  };
  if (m_liDiffVal.HighPart<liMin.HighPart || (m_liDiffVal.HighPart==liMin.HighPart && m_liDiffVal.LowPart<liMin.LowPart))
  {
   liMin.HighPart=m_liDiffVal.HighPart;
   liMin.LowPart=m_liDiffVal.LowPart;
  };

  OnUnloaddll();
 };
 m_liSum.LowPart=m_liSum.LowPart/NUMBEROFTESTS;
 m_liSum.HighPart=m_liSum.HighPart/NUMBEROFTESTS;
 sprintf(m_szBuf,"Average is %d %8lu",m_liSum.HighPart,m_liSum.LowPart);
 AddStringandAdjust(m_szBuf);
 sprintf(m_szBuf,"Max is %d %8lu, Min is %d %8lu",liMax.HighPart,liMax.LowPart,liMin.HighPart,liMin.LowPart);
 AddStringandAdjust(m_szBuf);

  		
}

void CPtappView::OnHogmemory() 
{
#define PAGESIZE 4096
  m_lpMem = 0;
  for (m_dwMemSize = 0x4000000;m_dwMemSize>0;m_dwMemSize-=PAGESIZE)
  {
   m_lpMem=VirtualAlloc(NULL,m_dwMemSize,MEM_COMMIT,PAGE_READWRITE);
   if (m_lpMem) break;
  };
  if (m_lpMem)
  {
  sprintf(m_szBuf,"Allocating %8lu bytes of memory @ %8lu",m_dwMemSize,m_lpMem);
  AddStringandAdjust(m_szBuf);
  char *lpMaxAddress=(char *)(m_dwMemSize+(char *)m_lpMem);
   for (char *lpLoop=(char *)m_lpMem;lpLoop<lpMaxAddress;lpLoop+=PAGESIZE)
    lpLoop[PAGESIZE/2]='a';
    return;
   };
  AddStringandAdjust("couldn't hog memory...");	
}

void CPtappView::OnUnhogmem() 
{
//   VirtualUnlock(m_lpMem,m_dwMemSize);
   VirtualFree(m_lpMem,/*m_dwMemSize*/0,MEM_RELEASE);
   GetLastError();
//   SetProcessWorkingSetSize(GetCurrentProcess(),m_dwMinWorkSize,m_dwMaxWorkSize);
	
}

void CPtappView::OnSmalldll() 
{
 m_bTypeFlags[0]=0;
}

void CPtappView::OnLargefixed() 
{
 m_bTypeFlags[0]=2;
}

void CPtappView::OnLargenofixups() 
{
 m_bTypeFlags[0]=1;
}

void CPtappView::OnCrtsupport() 
{
 m_bTypeFlags[1]=(m_bTypeFlags[1]!=1?1:0);

}


void CPtappView::OnDyncrtpre() 
{
 m_bTypeFlags[1]=(m_bTypeFlags[1]!=2?2:0);
}

void CPtappView::OnHasexports() 
{
 m_bTypeFlags[2]=(m_bTypeFlags[2]?0:1);
}


void CPtappView::OnFinishdll() 
{
 m_dwImageBase=0;    // we need this to make sure VirtualAlloc() in MapFile doesn't get confused
                     // when we select a new DLL
 m_pstrDLL[0]=(!m_bTypeFlags[0]?'s':((m_bTypeFlags[0]==1) ? 'l' :'f'));
 m_pstrDLL[1]=(!m_bTypeFlags[1]?'n':((m_bTypeFlags[1]==1) ?'c':'d'));
 m_pstrDLL[2]=m_bTypeFlags[2]?'e':'n';
 MapandSetupDllStuff();
}

void CPtappView::MapandSetupDllStuff()
{
 sprintf(m_szBuf,"Attempting to load Dll %s",m_pstrDLL);
 AddStringandAdjust(m_szBuf);
 if (!MapFile(m_pstrDLL))
 {
  UnmapFile();
  AddStringandAdjust("failed to open library to extract information");
  return;
 };
 PIMAGE_FILE_HEADER lpPEHeader = 
  (PIMAGE_FILE_HEADER)(m_lpImage+((PIMAGE_DOS_HEADER)m_lpImage)->e_lfanew+sizeof(DWORD));
 PIMAGE_OPTIONAL_HEADER lpOptHeader = 
  (PIMAGE_OPTIONAL_HEADER)((char *)lpPEHeader+sizeof(IMAGE_FILE_HEADER)); 
 m_dwImageBase = lpOptHeader->ImageBase;
 m_dwImageSize = lpOptHeader->SizeOfImage;
 UnmapFile();
}

// These are the flags to update the command UI... boring but necessary...


void CPtappView::OnUpdateCrtsupport(CCmdUI* pCmdUI) 
{
 pCmdUI->SetCheck(m_bTypeFlags[1]==1?1:0);	
}


void CPtappView::OnUpdateDyncrtpre(CCmdUI* pCmdUI) 
{
 pCmdUI->SetCheck(m_bTypeFlags[1]==2?1:0);
}


void CPtappView::OnUpdateLargefixed(CCmdUI* pCmdUI) 
{
 pCmdUI->SetCheck(m_bTypeFlags[0]==2?1:0);	
}

void CPtappView::OnUpdateLargenofixups(CCmdUI* pCmdUI) 
{
 pCmdUI->SetCheck(m_bTypeFlags[0]==1?1:0);
}

void CPtappView::OnUpdateSmalldll(CCmdUI* pCmdUI) 
{
 pCmdUI->SetCheck(m_bTypeFlags[0]?0:1);
}

void CPtappView::OnUpdateHasexports(CCmdUI* pCmdUI) 
{
 pCmdUI->SetCheck(m_bTypeFlags[2]?1:0);
}


void CPtappView::OnRunhogging() 
{AddStringandAdjust("Now running multiple hogging test...");
 LARGE_INTEGER liSum,liMax,liMin;
 liSum.LowPart=0;
 liSum.HighPart=0;
 liMin.LowPart=0;
 liMin.HighPart=10000;   // RAc - change this
 liMax.LowPart=0;
 liMax.HighPart=0;
 for (int i = 0; i<NUMBEROFTESTS; i++)
 {
  sprintf(m_szBuf,"Running test #%d",i);
  OnLoaddll();
  liSum.LowPart+=m_liDiffVal.LowPart;
  liSum.HighPart+=m_liDiffVal.HighPart;
  if (m_liDiffVal.HighPart>liMax.HighPart || (m_liDiffVal.HighPart==liMax.HighPart && m_liDiffVal.LowPart>liMax.LowPart))
  {
   liMax.HighPart=m_liDiffVal.HighPart;
   liMax.LowPart=m_liDiffVal.LowPart;
  };
  if (m_liDiffVal.HighPart<liMin.HighPart || (m_liDiffVal.HighPart==liMin.HighPart && m_liDiffVal.LowPart<liMin.LowPart))
  {
   liMin.HighPart=m_liDiffVal.HighPart;
   liMin.LowPart=m_liDiffVal.LowPart;
  };

  OnUnloaddll();
  OnHogmemory();
  OnUnhogmem();
 };
 liSum.LowPart=liSum.LowPart/NUMBEROFTESTS;
 liSum.HighPart=liSum.HighPart/NUMBEROFTESTS;
 sprintf(m_szBuf,"Average is %d %8lu",liSum.HighPart,liSum.LowPart);
 AddStringandAdjust(m_szBuf);
 sprintf(m_szBuf,"Max is %d %8lu, Min is %d %8lu",liMax.HighPart,liMax.LowPart,liMin.HighPart,liMin.LowPart);
 AddStringandAdjust(m_szBuf);
}

void CPtappView::OnLockranegmultiple() 
{AddStringandAdjust("Now running multiple memory allocation tests...");
 LARGE_INTEGER liSum,liMax,liMin;
 liSum.LowPart=0;
 liSum.HighPart=0;
 liMin.LowPart=0;
 liMin.HighPart=10000;   // RAc - change this
 liMax.LowPart=0;
 liMax.HighPart=0;
 for (int i = 0; i<NUMBEROFTESTS; i++)
 {
  sprintf(m_szBuf,"Running test #%d",i);
  OnLockrange();
  liSum.LowPart+=m_liDiffVal.LowPart;
  liSum.HighPart+=m_liDiffVal.HighPart;
  if (m_liDiffVal.HighPart>liMax.HighPart || (m_liDiffVal.HighPart==liMax.HighPart && m_liDiffVal.LowPart>liMax.LowPart))
  {
   liMax.HighPart=m_liDiffVal.HighPart;
   liMax.LowPart=m_liDiffVal.LowPart;
  };
  if (m_liDiffVal.HighPart<liMin.HighPart || (m_liDiffVal.HighPart==liMin.HighPart && m_liDiffVal.LowPart<liMin.LowPart))
  {
   liMin.HighPart=m_liDiffVal.HighPart;
   liMin.LowPart=m_liDiffVal.LowPart;
  };

  OnUnlockrange();
//  OnHogmemory();
//  OnUnhogmem();
 };
 liSum.LowPart=liSum.LowPart/NUMBEROFTESTS;
 liSum.HighPart=liSum.HighPart/NUMBEROFTESTS;
 sprintf(m_szBuf,"Average is %d %8lu",liSum.HighPart,liSum.LowPart);
 AddStringandAdjust(m_szBuf);
 sprintf(m_szBuf,"Max is %d %8lu, Min is %d %8lu",liMax.HighPart,liMax.LowPart,liMin.HighPart,liMin.LowPart);
 AddStringandAdjust(m_szBuf);
}

void CPtappView::OnLoaddllnofixups() 
{
 DWORD id;
 WaitForSingleObject(m_hMutex,INFINITE);
 HANDLE hThread=::CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ThreadRoutine,
                               (LPVOID)this,0,&id);
 if (!hThread) return; 
 if (!QueryPerformanceCounter(&m_liOldVal)) return;  // here's the current value...
 m_hDLLInstance = LoadLibraryEx(m_pstrFullPathDLL,NULL,LOAD_LIBRARY_AS_DATAFILE);
 WaitForSingleObject(hThread,INFINITE);
 if (m_dwImageBase == (unsigned long)m_hDLLInstance)
 sprintf(m_szBuf,"DLL was loaded at preferred address %x",m_dwImageBase);
 else
 sprintf(m_szBuf,"DLL was based at %x but loaded at %x",m_dwImageBase,m_hDLLInstance);
 AddStringandAdjust(m_szBuf);
 sprintf(m_szBuf,"began counting at %d %8lu",m_liOldVal.HighPart,m_liOldVal.LowPart);
 AddStringandAdjust(m_szBuf);
 sprintf(m_szBuf,"Library loaded at %d %8lu",m_liNewVal.HighPart,m_liNewVal.LowPart);	
 AddStringandAdjust(m_szBuf);
 m_liDiffVal.HighPart = m_liNewVal.HighPart-m_liOldVal.HighPart;
 m_liDiffVal.LowPart = m_liNewVal.LowPart-m_liOldVal.LowPart;
 sprintf(m_szBuf,"difference: %d %8lu",m_liDiffVal.HighPart,m_liDiffVal.LowPart);
 AddStringandAdjust(m_szBuf);
}

void CPtappView::DoMultipletests(Libtypes lT,runtimesupport rS,exports eX)
{
 OnFinishdll();
 OnMultipletests();
 m_liResults[lT][preferred_base][rS][eX].HighPart=m_liSum.HighPart;
 m_liResults[lT][preferred_base][rS][eX].LowPart=m_liSum.LowPart;
 m_iReference=min(m_iReference,m_liSum.LowPart);
 OnLockrange();
 OnMultipletests();
 m_liResults[lT][rebased_base][rS][eX].HighPart=m_liSum.HighPart;
 m_liResults[lT][rebased_base][rS][eX].LowPart=m_liSum.LowPart;
 m_iReference=min(m_iReference,m_liSum.LowPart);
 OnUnlockrange();
}

 
void CPtappView::OnBatch() 
{
  m_iReference=(unsigned long)-1;      // RAc - looks pretty arbitrary
 // first, run all tests for the small DLLs
 // small DLL, no CRT support, no exports
  OnSmalldll();
  DoMultipletests(small_dll,no_runtime,no_exports);
 // small DLL, static runtime support, no exports
  OnCrtsupport();
  DoMultipletests(small_dll,static_runtime,no_exports);
 // small DLL, dynamic runtime support, no exports
  OnDyncrtpre();
  DoMultipletests(small_dll,dynamic_runtime,no_exports);
 // small DLL, dynamic runtime support, has exports
  OnHasexports();
  DoMultipletests(small_dll,dynamic_runtime,yes_exports);
 // small DLL, static runtime support, has exports
  OnCrtsupport();
  DoMultipletests(small_dll,static_runtime,yes_exports);
// small DLL, no runtime support, has exports
  OnCrtsupport();	// this will clear the runtime support stuff...
  DoMultipletests(small_dll,no_runtime,yes_exports);
// now clear the has exports flag...
  OnHasexports();
// do the same thing for large DLL.../////////////////////////////////////////////
  OnLargenofixups();
  DoMultipletests(large_dll,no_runtime,no_exports);
 // large DLL, static runtime support, no exports
  OnCrtsupport();
  DoMultipletests(large_dll,static_runtime,no_exports);
 // large DLL, dynamic runtime support, no exports
  OnDyncrtpre();
  DoMultipletests(large_dll,dynamic_runtime,no_exports);
 // large DLL, dynamic runtime support, has exports
  OnHasexports();
  DoMultipletests(large_dll,dynamic_runtime,yes_exports);
 // large DLL, static runtime support, has exports
  OnCrtsupport();
  DoMultipletests(large_dll,static_runtime,yes_exports);
// large DLL, no runtime support, has exports
  OnCrtsupport();	// this will clear the runtime support stuff...
  DoMultipletests(large_dll,no_runtime,yes_exports);
// now clear the has exports flag...
  OnHasexports();
// now do the same thing with the large DLL and fixups
  OnLargefixed();
  DoMultipletests(largefixup_dll,no_runtime,no_exports);
 // large fixed DLL, static runtime support, no exports
  OnCrtsupport();
  DoMultipletests(largefixup_dll,static_runtime,no_exports);
 // large fixed DLL, dynamic runtime support, no exports
  OnDyncrtpre();
  DoMultipletests(largefixup_dll,dynamic_runtime,no_exports);
 // large fixed, dynamic runtime support, has exports
  OnHasexports();
  DoMultipletests(largefixup_dll,dynamic_runtime,yes_exports);
 // large fixed, static runtime support, has exports
  OnCrtsupport();
  DoMultipletests(largefixup_dll,static_runtime,yes_exports);
// large fixed DLL, no runtime support, has exports
  OnCrtsupport();	// this will clear the runtime support stuff...
  DoMultipletests(largefixup_dll,no_runtime,yes_exports);
// now clear the has exports flag...
  OnHasexports();
// now display the results...
for (Basetypes bt=preferred_base;bt<=rebased_base;bt=(enum Basetypes)(bt+1))
{
 for (runtimesupport rt=no_runtime;rt<=dynamic_runtime;rt=(enum runtimesupport)(rt+1))
 {
  sprintf(m_szBuf,"small DLL: %u %8lu (%.2f)/ large DLL: %u %8lu (%.2f)/ fixups: %u %8lu (%.2f)",
          m_liResults[small_dll][bt][rt][no_exports].HighPart,
          m_liResults[small_dll][bt][rt][no_exports].LowPart,
		  (double)m_liResults[small_dll][bt][rt][no_exports].LowPart/(double)m_iReference,
          m_liResults[large_dll][bt][rt][no_exports].HighPart,
          m_liResults[large_dll][bt][rt][no_exports].LowPart,
		  (double)m_liResults[large_dll][bt][rt][no_exports].LowPart/(double)m_iReference,
          m_liResults[largefixup_dll][bt][rt][no_exports].HighPart,
          m_liResults[largefixup_dll][bt][rt][no_exports].LowPart,
		  (double)m_liResults[largefixup_dll][bt][rt][no_exports].LowPart/(double)m_iReference);
  AddStringandAdjust(m_szBuf);
  sprintf(m_szBuf,"small DLL: %u %8lu (%.2f)/ large DLL: %u %8lu (%.2f)/ fixups: %u %8lu (%.2f)",
          m_liResults[small_dll][bt][rt][yes_exports].HighPart,
          m_liResults[small_dll][bt][rt][yes_exports].LowPart,
		  (double)m_liResults[small_dll][bt][rt][yes_exports].LowPart/(double)m_iReference,
          m_liResults[large_dll][bt][rt][yes_exports].HighPart,
          m_liResults[large_dll][bt][rt][yes_exports].LowPart,
		  (double)m_liResults[large_dll][bt][rt][yes_exports].LowPart/(double)m_iReference,
          m_liResults[largefixup_dll][bt][rt][yes_exports].HighPart,
          m_liResults[largefixup_dll][bt][rt][yes_exports].LowPart,
		  (double)m_liResults[largefixup_dll][bt][rt][yes_exports].LowPart/(double)m_iReference);
  AddStringandAdjust(m_szBuf);
  };
  AddStringandAdjust("------------------------------------------------------------------");
 };
};        

void CPtappView::OnCustomdll() 
{
 CGetName cN;
 if (cN.DoModal()!=IDOK) return;
 strcpy(m_pstrDLL,cN.m_DllName);
 MapandSetupDllStuff();	
}
