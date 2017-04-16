// neview.cpp : implementation file
//

#include "stdafx.h"
#include "viewfile.h"
#include "fileview.h"

#include "headers.h"

#include "neview.h"

#include "childfrm.h"
#include "necframe.h"

#include "injlib.h"


extern CViewfileApp theApp;

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNEView

IMPLEMENT_DYNCREATE(CNEView, CFileView)

CNEView::CNEView()
{
}

CNEView::~CNEView()
{
}


BEGIN_MESSAGE_MAP(CNEView, CFileView)
    ON_MESSAGE(WMC_DEBUGEVENT, OnLoadDLL)
	ON_MESSAGE(WMC_REFRESH, OnRefresh)
	//{{AFX_MSG_MAP(CNEView)
		// NOTE - the ClassWizard will add and remove mapping macros here.

	ON_COMMAND(ID_FILE_EXECUTE, OnFileExecute)

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CNEView drawing

void CNEView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CNEView diagnostics

#ifdef _DEBUG
void CNEView::AssertValid() const
{
	CView::AssertValid();
}

void CNEView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CNEView message handlers

void CNEView::OnInitialUpdate() 
{
 CFileView::OnInitialUpdate();
 GetParentFrame()->SetWindowText("NE file header: "+GetDocument()->GetPathName());
}

// helper functions

void CNEView::FillInEntryTable(unsigned char *lpEntryTable)
{
 WORD  wIndex=1;
 WORD  wI;
 BYTE  bBundles;
 BYTE  bFlags;
 AddStringandAdjust("Entry table: ");
 wsprintf(m_szBuf,"Dummy");
 while (TRUE)
 {
  bBundles = (BYTE)*lpEntryTable++;
  if (bBundles==0) break;    // End of the table
  bFlags= (BYTE)*lpEntryTable++;
  switch (bFlags)
  {
   case 0x00:      // Placeholders
     if (bBundles == 1) wsprintf( m_szBuf, "%d Placeholder",wIndex );
      else wsprintf( m_szBuf, "%d-%d Placeholders", wIndex, wIndex + bBundles - 1 ); 
     AddStringandAdjust(m_szBuf); 
     wIndex += bBundles;
     break;
   case 0xFF:      // MOVEABLE segments
     for (wI=0; wI<(WORD)bBundles; wI++)
     {
      PMENTRY pe = (PMENTRY)lpEntryTable;
      WORD    wS = ((WORD)pe->bFlags)>>2;
      wsprintf( m_szBuf, "%d %#04x     %#04x   %#04x        MOVEABLE  ",
               wIndex, pe->bSegNumber, pe->wSegOffset, wS );
      if (pe->bFlags & EXPORTED) lstrcat( m_szBuf, "EXPORTED " );
       else lstrcat( m_szBuf, "         " );
      if (pe->bFlags & SHAREDDATA) lstrcat( m_szBuf, "SHARED_DATA" ); 
      AddStringandAdjust(m_szBuf);  
      wIndex++;
      lpEntryTable += sizeof( MENTRY );
     }
     break;
   default:        // FIXED Segments
     for (wI=0; wI<(WORD)bBundles; wI++)
     {
      PFENTRY pe = (PFENTRY)lpEntryTable;
      WORD    wS = ((WORD)pe->bFlags)>>2;
      wsprintf( m_szBuf, "%d %#04x     %#04x   %#04x        FIXED     ",
               wIndex, bFlags, pe->wSegOffset, wS );
      if (pe->bFlags & EXPORTED) lstrcat( m_szBuf, "EXPORTED  " );
       else lstrcat( m_szBuf, "         " );
      if (pe->bFlags & SHAREDDATA) lstrcat( m_szBuf, "SHARED_DATA" ); 
      AddStringandAdjust(m_szBuf);   
      wIndex++;  
      lpEntryTable += sizeof( FENTRY );
     }
   break;
   }
 }
}

void CNEView::FillInSegmentTable(PSEGENTRY lpSegmentTable,int iEntries, WORD wAlign)
{
 int       i=0;
 if (wAlign == 0) wAlign = 9;
 AddStringandAdjust("Segment table:");
 for (i=0;i<iEntries;i++)
 { 
  PSEGENTRY pE = &lpSegmentTable[i];
  wsprintf( m_szBuf, " %s seg: Selector(<<align): %#08lx ;Length: %#04x ;Memory: %#04x ",
            pE->wFlags & F_DATASEG?"DATA":"CODE",((LONG)pE->wSector)<<wAlign,pE->wLength, pE->wMinAlloc );
  if (pE->wFlags & F_PRELOAD) lstrcat( m_szBuf, "PRELOAD " );
  if (pE->wFlags & F_MOVEABLE) lstrcat( m_szBuf, "(moveable) " );
  if (pE->wFlags & F_DISCARDABLE) lstrcat( m_szBuf, "(discardable)" );
  AddStringandAdjust(m_szBuf);
 };
};


// this code only to be executed if the file is not an OS/2 executable...

void CNEView::FillInResourceTable(BYTE *lpResourceTable)
{
char *rc_types[] = {
    "<unknown>",
    "CURSOR",
    "BITMAP",
    "ICON",
    "MENU",
    "DIALOG",
    "STRING",
    "FONTDIR",
    "FONT",
    "ACCELERATOR",
    "RCDATA",
    "<unknown>",
    "GROUP CURSOR",
    "<unknown>",
    "GROUP ICON",
    "NAME TABLE",
	"<unknown>"
};

 BYTE *lpMovingPointer = lpResourceTable;
 RTYPE *prt;
 WORD      wResSize;
 WORD wShiftCount=((WORD *)lpMovingPointer)[0];
 lpMovingPointer+= sizeof(WORD);
 AddStringandAdjust("Resource Table:");
    // Read all the resource types    
 while (TRUE)    
 {
  prt = (RTYPE *)lpMovingPointer;
  lpMovingPointer+=sizeof(RTYPE);
  if (prt->wType==0) break;   // end of table
  BYTE szNameBuf[255];   // change this!!!
  if (!(prt->wType&0x8000))    // this is a  custom resource type
  { 
   FillInSizedString(szNameBuf,lpResourceTable+prt->wType);
  }
  else
  {
   WORD wType = prt->wType&0x7fff;
   if (wType>15) wType=16;
   strcpy((char *)szNameBuf,rc_types[wType]);
  }; 
// Allocate buffer for 'Count' resources of this type
  wResSize = prt->wCount * sizeof( RINFO ); 
  int iInnerLoop;
  for (iInnerLoop=0;iInnerLoop<prt->wCount;iInnerLoop++)
  { 
   RINFO *pCurrentResInfo = (RINFO *)lpMovingPointer;
   BYTE szNameBuff[255];
// figure out what to make of the ID
   if (!(pCurrentResInfo->wID & 0x8000))
    FillInSizedString(szNameBuff,lpResourceTable+pCurrentResInfo->wID);  
   else wsprintf((char *)szNameBuff,"%#x",pCurrentResInfo->wID);
   char szFlags[30];
   wsprintf(szFlags," ");
  if (pCurrentResInfo->wFlags&F_MOVEABLE) lstrcat(szFlags,"<moveable> ");
  if (pCurrentResInfo->wFlags&F_SHAREABLE) lstrcat(szFlags,"<pure> ");
  if (pCurrentResInfo->wFlags&F_PRELOAD) lstrcat(szFlags,"<preload> ");
  wsprintf(m_szBuf,"%s [%s] @%#x; length: %#x; %s",szNameBuff,szNameBuf,
           pCurrentResInfo->wOffset<<wShiftCount,
           pCurrentResInfo->wLength<<wShiftCount,
           szFlags); 
  AddStringandAdjust(m_szBuf);
  lpMovingPointer+=sizeof(RINFO);
  };
};
   /*
    // Now that the resources are read, read the names
    prt = pExeInfo->pResTable;

    while (prt)
    {
        if (prt->wType & 0x8000)        // Pre-defined type
            prt->pResourceType = NULL;

        // Now do Resource Names for this type
        pri = prt->pResInfoArray;

        wI = 0;
        while ( wI < prt->wCount )
        {
            if (pri->wID & 0x8000)  // Integer resource
                pri->pResourceName = NULL;
            else                    // Named resource
            {
                // wID is offset from beginning of Resource Table
                _llseek( fFile, lResTable + pri->wID, 0 );

                wResSize = 0;
                // Read string size
                if (_lread(fFile, (LPSTR)&wResSize, 1)!=1)
                    return LERR_READINGFILE;

                // +1 for the null terminator
                pri->pResourceName = (PSTR)LocalAlloc(LPTR, wResSize+1);
                if (!pri->pResourceName)
                    return LERR_MEMALLOC;

                // Read string
                if (_lread(fFile, (LPSTR)pri->pResourceName, wResSize)!=wResSize)
                    return LERR_READINGFILE;
                pri->pResourceName[ wResSize ] = 0;   // Null terminate string;
            }
            pri++;
            wI++;
        }
        prt = prt->pNext;
    }
*/

}


long WINAPI DebugTreadFunction(CNEView *cpe) 
{  
 BOOL bRunning=TRUE;
 STARTUPINFO sa;
 PROCESS_INFORMATION pi;
 DEBUG_EVENT  DebugEvent;
 memset((LPVOID)&sa,'\0',sizeof(STARTUPINFO));
//   GetStartupInfo(&sa);  // clone caller's startup info...
 sa.cb          = sizeof( STARTUPINFO );
 sa.lpDesktop   = NULL;
 sa.lpTitle     = "";
 sa.dwX         = 0;
 sa.dwY         = 0;
 sa.dwXSize     = 0;
 sa.dwYSize     = 0;
 sa.dwFlags     = (DWORD) NULL;
 sa.wShowWindow = SW_SHOWDEFAULT;
 if (!CreateProcess(cpe->GetDocument()->GetPathName(),NULL,NULL,NULL,TRUE,
            DEBUG_PROCESS|CREATE_SEPARATE_WOW_VDM,NULL,NULL,&sa,&pi))
 return FALSE;
 while(bRunning)
 { 
  if( !WaitForDebugEvent( &DebugEvent, INFINITE ) ) break;
  switch(DebugEvent.dwDebugEventCode)
  { 
   case CREATE_PROCESS_DEBUG_EVENT:
         cpe->PostMessage(WMC_REFRESH,0,0);	
		 // fall through

    case EXCEPTION_BREAKPOINT:
         ContinueDebugEvent( DebugEvent.dwProcessId, DebugEvent.dwThreadId,
                             DBG_CONTINUE );
		 break;
	case LOAD_DLL_DEBUG_EVENT:
    case UNLOAD_DLL_DEBUG_EVENT:
//       first create a new node (note that it is the responsibility of the 
// main thread to free the memory)
         {HLOCAL hMem=LocalAlloc(LMEM_MOVEABLE,sizeof(DebugEvent));
		  PVOID pNewMem=LocalLock(hMem);
		  CopyMemory(pNewMem,(void *)&DebugEvent,sizeof(DEBUG_EVENT));
		  LocalUnlock(hMem);
		  cpe->PostMessage(WMC_DEBUGEVENT,(WPARAM)hMem,pi.dwProcessId);
		 };
         ContinueDebugEvent( DebugEvent.dwProcessId, DebugEvent.dwThreadId,
                             DBG_CONTINUE );
		 break;

    case EXIT_PROCESS_DEBUG_EVENT:
         cpe->PostMessage(WMC_REFRESH,0,0);	

	case DBG_TERMINATE_PROCESS:
		 bRunning = FALSE;     // fall through to process the event here
	default:
         ContinueDebugEvent( DebugEvent.dwProcessId, DebugEvent.dwThreadId,
                             DBG_CONTINUE );
  };
};
 return TRUE;

};
//
// this is the thread function that is called in the context of the remote thread
//


extern "C"
{

#pragma check_stack (off)

static DWORD WINAPI RemoteThreadFunc (THREADFNSTRUCT *pStruct) {
//_asm int 3;
pStruct->fnGetModuleFileName(pStruct->dwInstance,pStruct->chPathName,_MAX_PATH);
//SuspendThread(GetCurrentThread());   // so that the buffer doesn't disappear...

return 0;
}

static void AfterThreadFunc (void) {
}
#pragma check_stack 
};


long CNEView::OnLoadDLL(WPARAM wParam, LPARAM lParam)
{ 
 HLOCAL hMem = (HLOCAL)wParam;
 DEBUG_EVENT *pEvent=(DEBUG_EVENT *)LocalLock(hMem);
 if (pEvent->dwDebugEventCode == LOAD_DLL_DEBUG_EVENT)
 {
 DWORD dwProcessId=(DWORD)lParam;
 HANDLE hProcess;
// this code is mostly taken from Jeffrey Richter's injlib sample...
// first try to open the process
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessId);
	if (hProcess == NULL) {
		AfxMessageBox((GetLastError() == 5) ? "Insufficient access to process" :"Invalid process Id");
    return FALSE;
	};
// The address where code will be copied to in the remote process.
	PDWORD pdwCodeRemote = NULL;

	// Calculate the number of bytes in the ThreadFunc function.
	const int cbCodeSize = ((LPBYTE) AfterThreadFunc - (LPBYTE) RemoteThreadFunc);
// The number of bytes written to the remote process.
	DWORD dwNumBytesXferred = 0;
	THREADFNSTRUCT tfRemote;

	tfRemote.dwInstance=(HINSTANCE)pEvent->u.LoadDll.lpBaseOfDll;
	// assume ANSI at this point -- adjust later on for unicode apps!!!
	tfRemote.fnGetModuleFileName=(DWORD (WINAPI *)(HMODULE,LPTSTR,DWORD))GetProcAddress(GetModuleHandle(__TEXT("KERNEL32")),"GetModuleFileNameA");
	// The handle and Id of the thread executing the remote copy of ThreadFunc.
	THREADFNSTRUCT *pInjLibInfoRemote = NULL;

	DWORD dwThreadId = 0;
	const DWORD cbMemSize = cbCodeSize + sizeof(THREADFNSTRUCT) + 3;
	HANDLE hThread = NULL;
	HINSTANCE hinstDLLRemote = NULL;

	BOOL fOk = FALSE;
	DWORD dwOldProtect;
	__try {

		// Allocate memory in the remote process's address space large 
		// enough to hold our ThreadFunc function and a InjLibInfo structure.
		pdwCodeRemote = (PDWORD) AllocProcessMemory(hProcess, 
			cbMemSize);

		if (pdwCodeRemote == NULL)
			{char szBuf[40];
			 wsprintf(szBuf,"Reason for failure of APM: %d",GetLastError());
			 OutputDebugString(szBuf);
			 __leave;};

		// Change the page protection of the allocated memory
		// to executable, read, and write.
		fOk = VirtualProtectEx(hProcess, pdwCodeRemote, cbMemSize,
				PAGE_EXECUTE_READWRITE, &dwOldProtect);
		if (!fOk)
			{char szBuf[40];
			 wsprintf(szBuf,"Reason for failure of VPE: %d",GetLastError());
			 OutputDebugString(szBuf);
			 __leave;};

		// Write a copy of ThreadFunc to the remote process.
		fOk = WriteProcessMemory(hProcess, pdwCodeRemote,
			(LPVOID) RemoteThreadFunc, cbCodeSize, &dwNumBytesXferred);
		if (!fOk)
			{char szBuf[40];
			 wsprintf(szBuf,"Reason for failure of WPM: %d",GetLastError());
			 OutputDebugString(szBuf);
			 __leave;};


		// Write a copy of InjLibInfo to the remote process
		// (the structure MUST start on an even 32-bit bourdary).

		pInjLibInfoRemote = (THREADFNSTRUCT *) 
			(pdwCodeRemote + ((cbCodeSize + 4) & ~3));

		// Put InjLibInfo in remote thread's memory block.
		fOk = WriteProcessMemory(hProcess, pInjLibInfoRemote,
			&tfRemote, sizeof(THREADFNSTRUCT), &dwNumBytesXferred);
		if (!fOk)
			{char szBuf[40];
			 wsprintf(szBuf,"Reason for failure of WPM2: %d",GetLastError());
			 OutputDebugString(szBuf);
			 

			__leave;};


		hThread = CreateRemoteThread(hProcess, NULL, 0, 
			(LPTHREAD_START_ROUTINE) pdwCodeRemote,
			pInjLibInfoRemote, 0, &dwThreadId);
		if (hThread == NULL)
			{char szBuf[40];
			 wsprintf(szBuf,"Reason for failure of CRT: %d",GetLastError());
			 OutputDebugString(szBuf);
			 __leave;
			};
		if (WaitForSingleObject(hThread, INFINITE)==WAIT_FAILED)
			{char szBuf[40];
			 wsprintf(szBuf,"Reason for failure of WFSO: %d",GetLastError());
			 OutputDebugString(szBuf);
			 };
		   ;
	}	// __try
	__finally {
		if (hThread != NULL) {
			GetExitCodeThread(hThread, (PDWORD) &hinstDLLRemote);
			CloseHandle(hThread);
			DWORD bytesRead;
			ReadProcessMemory(hProcess,pInjLibInfoRemote,(void *)&tfRemote,sizeof(THREADFNSTRUCT),&bytesRead);
		    FreeProcessMemory(hProcess,pdwCodeRemote);
			wsprintf(m_szBuf,"loaded DLL %s @ %#x",(char *)&tfRemote.chPathName,pEvent->u.LoadDll.lpBaseOfDll);
			AddStringandAdjust(m_szBuf);
// just to force the listbox to adjust its size 
			RECT rcWindow;
			GetClientRect(&rcWindow);
			OnSize(SIZE_RESTORED,rcWindow.right,rcWindow.bottom);
            CloseHandle(hProcess);
		};
	}	//__finally


 LocalUnlock(hMem);
 LocalFree(hMem);
 return TRUE;
 }	 // end of LOAD_DLL_DEBUG_EVENT code
 else
 {
  			wsprintf(m_szBuf,"Unloaded DLL @ %#x",pEvent->u.UnloadDll.lpBaseOfDll);
			AddStringandAdjust(m_szBuf);
			RECT rcWindow;
			GetClientRect(&rcWindow);
			OnSize(SIZE_RESTORED,rcWindow.right,rcWindow.bottom);
			return TRUE;
 };
};

		    
void CNEView::OnFileExecute() 
{
 DWORD idThread;      
 CloseHandle(CreateThread(NULL,9,(LPTHREAD_START_ROUTINE)DebugTreadFunction,
 (LPVOID)GetDLLPane(),
 0,&idThread));
 }

CNEView *CNEView::GetDLLPane()
{ return ((CNECFrame*)GetParentFrame())->GetDLLPane();
}


void CNEView::DispatchDoubleClick(int iVal)
{ 
// m_Selection contains the selected string; take it apart and see what's in there...
char szBuf[MAX_PATH];
int iDelimiter = strlen("loaded DLL ");
size_t iEndofFileName;
if (!_strnicmp("loaded DLL ",m_Selection,iDelimiter))
   {iEndofFileName = strcspn(&m_Selection[iDelimiter]," "); // this hoses us badly w/ long file names
    strncpy(szBuf,&m_Selection[iDelimiter],iEndofFileName);
	theApp.OpenDocumentFile(szBuf);
   };
};

BOOL CNEView::IsMyKindOfFile(BYTE *lpImage)
{    
 return (*(USHORT *)lpImage == IMAGE_DOS_SIGNATURE) &&
        (LOWORD (*(DWORD *)NTSIGNATURE (lpImage)) == IMAGE_OS2_SIGNATURE);
 };


afx_msg long CNEView::OnRefresh(WPARAM wParam, LPARAM lParam)
{
 theApp.RefreshProcessList();
 return 0;
};
