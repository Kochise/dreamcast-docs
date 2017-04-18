// peview.cpp : implementation file
//

#include "stdafx.h"
#include "viewfile.h"
#include "fileview.h"
#include "peview.h"

#include "childfrm.h"
#include "pecframe.h"

#include <windows.h>

#include "headers.h"

#include "injlib.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


extern CViewfileApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CPEView

IMPLEMENT_DYNCREATE(CPEView, CFileView)

CPEView::CPEView()
{
}

CPEView::~CPEView()
{
}


BEGIN_MESSAGE_MAP(CPEView, CFileView)
    ON_MESSAGE(WMC_DEBUGEVENT, OnLoadDLL)
	ON_MESSAGE(WMC_REFRESH, OnRefresh)
	//{{AFX_MSG_MAP(CPEView)
	ON_COMMAND(ID_FILE_EXECUTE, OnFileExecute)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPEView drawing

void CPEView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CPEView diagnostics

#ifdef _DEBUG
void CPEView::AssertValid() const
{
	CView::AssertValid();
}

void CPEView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPEView message handlers

void CPEView::OnInitialUpdate() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CFileView::OnInitialUpdate();
	GetParentFrame()->SetWindowText("PE file header: "+GetDocument()->GetPathName());
}

// helper functions





void CPEView::DetermineCharacteristics(WORD wCharacteristics,ANYELEMENT *aTags,WORD wLength)
{
WORD wLoop;
for (wLoop=0;wLoop<wLength;wLoop++)
{ if (aTags[wLoop].iTag&wCharacteristics)
  AddStringandAdjust(aTags[wLoop].cIfPresent);
  else
  AddStringandAdjust(aTags[wLoop].cIfNotPresent);
};
};

void CPEView::DumpDataDirectories(PIMAGE_DATA_DIRECTORY pDataDirectories,int iSize,char *szTemplate[])
{
 int iLoop;
 for (iLoop=0;iLoop<iSize;iLoop++)
   { wsprintf(m_szBuf,"%s @ %#x, length %#x",szTemplate[iLoop],pDataDirectories[iLoop].VirtualAddress,
                                                                    pDataDirectories[iLoop].Size);
     AddStringandAdjust(m_szBuf);
   };
}

DWORD_FLAG_DESCRIPTIONS SectionCharacteristics[] = 
{
{ IMAGE_SCN_CNT_CODE, "CODE" },
{ IMAGE_SCN_CNT_INITIALIZED_DATA, "INITIALIZED_DATA" },
{ IMAGE_SCN_CNT_UNINITIALIZED_DATA, "UNINITIALIZED_DATA" },
{ IMAGE_SCN_LNK_INFO, "LNK_INFO" },
//{ IMAGE_SCN_LNK_OVERLAY, "LNK_OVERLAY" },
{ IMAGE_SCN_LNK_REMOVE, "LNK_REMOVE" },
{ IMAGE_SCN_LNK_COMDAT, "LNK_COMDAT" },
{ IMAGE_SCN_MEM_DISCARDABLE, "MEM_DISCARDABLE" },
{ IMAGE_SCN_MEM_NOT_CACHED, "MEM_NOT_CACHED" },
{ IMAGE_SCN_MEM_NOT_PAGED, "MEM_NOT_PAGED" },
{ IMAGE_SCN_MEM_SHARED, "MEM_SHARED" },
{ IMAGE_SCN_MEM_EXECUTE, "MEM_EXECUTE" },
{ IMAGE_SCN_MEM_READ, "MEM_READ" },
{ IMAGE_SCN_MEM_WRITE, "MEM_WRITE" },
};

#define NUMBER_SECTION_CHARACTERISTICS \
	(sizeof(SectionCharacteristics) / sizeof(DWORD_FLAG_DESCRIPTIONS))


void CPEView::DumpSectionTable(PIMAGE_SECTION_HEADER section,unsigned cSections,BOOL IsEXE)
{
	unsigned i, j;

	AddStringandAdjust("Section Table");
	
	for ( i=1; i <= cSections; i++, section++ )
	{
		wsprintf(m_szBuf,"%-8.8s[%02X]  @ %08X, %s  %08X ",
				 section->Name,i,section->VirtualAddress,
				IsEXE ? "VirtSize" : "PhysAddr",
				section->Misc.VirtualSize );
		for ( j=0; j < NUMBER_SECTION_CHARACTERISTICS; j++ )
		{
			if ( section->Characteristics & 
				SectionCharacteristics[j].flag )
				{lstrcat(m_szBuf, SectionCharacteristics[j].name );
				 lstrcat(m_szBuf,",");
				};
		};

		AddStringandAdjust(m_szBuf);
		wsprintf( m_szBuf,"    raw data offs:   %08X  raw data size: %08X",
				section->PointerToRawData, section->SizeOfRawData );
		AddStringandAdjust(m_szBuf);
		wsprintf( m_szBuf,"    relocation offs: %08X  relocations:   %08X",
				section->PointerToRelocations, section->NumberOfRelocations );
 		AddStringandAdjust(m_szBuf);
		wsprintf( m_szBuf,"    line # offs:     %08X  line #'s:      %08X",
				section->PointerToLinenumbers, section->NumberOfLinenumbers );
 		AddStringandAdjust(m_szBuf);
	}
}


PIMAGE_SECTION_HEADER CPEView::GetSectionHdrByName (LPVOID lpImage,char *szSection)
{
    PIMAGE_SECTION_HEADER    psh;
    int nSections = ((int)((PIMAGE_FILE_HEADER)PEFHDROFFSET (lpImage))->NumberOfSections);
    int i;


    if ((psh = (PIMAGE_SECTION_HEADER)SECHDROFFSET (lpImage)) != NULL)
	{
	/* find the section by name */
	for (i=0; i<nSections; i++)
	    {
	    if (!strcmp ((const char *)psh->Name, szSection))
		{
		/* copy data to header */
		return psh;
		}
	    else
		psh++;
	    }
	}

    return (PIMAGE_SECTION_HEADER)NULL;
}



// this is stolen from Matt Pietrek...


// The predefined resource types
char *SzResourceTypes[] = {
"???_0", "CURSOR", "BITMAP", "ICON", "MENU", "DIALOG", "STRING", "FONTDIR",
"FONT", "ACCELERATORS", "RCDATA", "MESSAGETABLE", "GROUP_CURSOR",
"???_13", "GROUP_ICON", "???_15", "VERSION"
};

// Get an ASCII string representing a resource type
void CPEView::GetResourceTypeName(DWORD type, PSTR buffer, UINT cBytes)
{
	if ( type <= 16 )
		strncpy(buffer, SzResourceTypes[type], cBytes);
	else
		wsprintf(buffer, "%X", type);
}

//
// If a resource entry has a string name (rather than an ID), go find
// the string and convert it from unicode to ascii.
//
void CPEView::GetResourceNameFromId
(
	DWORD id, DWORD resourceBase, PSTR buffer, UINT cBytes
)
{
	PIMAGE_RESOURCE_DIR_STRING_U prdsu;

	// If it's a regular ID, just format it.
	if ( !(id & IMAGE_RESOURCE_NAME_IS_STRING) )
	{
		wsprintf(buffer, "%X", id);
		return;
	}
	
	id &= 0x7FFFFFFF;
	prdsu = (PIMAGE_RESOURCE_DIR_STRING_U)(resourceBase + id);

	// prdsu->Length is the number of unicode characters
	WideCharToMultiByte(CP_ACP, 0, prdsu->NameString, prdsu->Length,
						buffer, cBytes,	0, 0);
	buffer[ min(cBytes-1,prdsu->Length) ] = 0;	// Null terminate it!!!
}

//
// Dump the information about one resource directory entry.  If the
// entry is for a subdirectory, call the directory dumping routine
// instead of printing information in this routine.
//
void CPEView::DumpResourceEntry
(
	PIMAGE_RESOURCE_DIRECTORY_ENTRY resDirEntry,
	DWORD resourceBase,
	DWORD level
)
{
	UINT i;
	char nameBuffer[128];
		
	if ( resDirEntry->OffsetToData & IMAGE_RESOURCE_DATA_IS_DIRECTORY )
	{
		DumpResourceDirectory( (PIMAGE_RESOURCE_DIRECTORY)
			((resDirEntry->OffsetToData & 0x7FFFFFFF) + resourceBase),
			resourceBase, level, resDirEntry->Name);
		return;
	}
	strcpy(m_szBuf,"");
	// Spit out the spacing for the level indentation
	for ( i=0; i < level; i++ )
		strcat(m_szBuf,"    ");

	if ( resDirEntry->Name & IMAGE_RESOURCE_NAME_IS_STRING )
	{
		GetResourceNameFromId(resDirEntry->Name, resourceBase, nameBuffer,
							  sizeof(nameBuffer));
		wsprintf(&m_szBuf[strlen(m_szBuf)],"Name: %s  Offset: %08X",
			nameBuffer, resDirEntry->OffsetToData);
	}
	else
	{
		wsprintf(&m_szBuf[strlen(m_szBuf)],"ID: %08X  Offset: %08X",
				resDirEntry->Name, resDirEntry->OffsetToData);
	};
  AddStringandAdjust(m_szBuf);
}

//
// Dump the information about one resource directory.
//
void CPEView::DumpResourceDirectory
(
	PIMAGE_RESOURCE_DIRECTORY resDir,
	DWORD resourceBase,
	DWORD level,
	DWORD resourceType
)
{
	PIMAGE_RESOURCE_DIRECTORY_ENTRY resDirEntry;
	char szType[64];
	UINT i;
	strcpy(m_szBuf,"");
	// Spit out the spacing for the level indentation
	for ( i=0; i < level; i++ )
		strcat(m_szBuf,"    ");

	// Level 1 resources are the resource types
	if ( level == 1 && !(resourceType & IMAGE_RESOURCE_NAME_IS_STRING) )
	{
		GetResourceTypeName( resourceType, szType, sizeof(szType) );
	}
	else	// Just print out the regular id or name
	{
		GetResourceNameFromId( resourceType, resourceBase, szType,
							   sizeof(szType) );
	}
	
	wsprintf(&m_szBuf[strlen(m_szBuf)],
		"ResDir (%s) Named:%02X ID:%02X TimeDate:%08X Vers:%u.%02u Char:%X",
		szType,	resDir->NumberOfNamedEntries, resDir->NumberOfIdEntries,
		resDir->TimeDateStamp, resDir->MajorVersion,
		resDir->MinorVersion,resDir->Characteristics);
	AddStringandAdjust(m_szBuf);
	resDirEntry = (PIMAGE_RESOURCE_DIRECTORY_ENTRY)(resDir+1);
	
	for ( i=0; i < resDir->NumberOfNamedEntries; i++, resDirEntry++ )
		DumpResourceEntry(resDirEntry, resourceBase, level+1);

	for ( i=0; i < resDir->NumberOfIdEntries; i++, resDirEntry++ )
		DumpResourceEntry(resDirEntry, resourceBase, level+1);
};

void CPEView::DumpImportsSection(char *base, PIMAGE_SECTION_HEADER pHeader)
{
	PIMAGE_IMPORT_DESCRIPTOR importDesc;
	PIMAGE_THUNK_DATA thunk;
	PIMAGE_IMPORT_BY_NAME pOrdinalName;
	DWORD exportsStartRVA, exportsEndRVA;
	
	INT delta;

	importDesc = (PIMAGE_IMPORT_DESCRIPTOR)(pHeader->PointerToRawData + (DWORD)base);
 
	delta = (INT)(pHeader->VirtualAddress - pHeader->PointerToRawData);
	
 	AddStringandAdjust("Imports Table:");
	
	while ( 1 )
	{
		// See if we've reached an empty IMAGE_IMPORT_DESCRIPTOR
		if ( (importDesc->TimeDateStamp==0 ) && (importDesc->Name==0) )
			break;
		
		wsprintf(m_szBuf,"  %s", (PBYTE)(importDesc->Name) - delta + (int)base);
		AddStringandAdjust(m_szBuf);
		wsprintf(m_szBuf,"  Hint/Name Table: %08X", importDesc->Characteristics);
		AddStringandAdjust(m_szBuf);
        wsprintf(m_szBuf,"  TimeDateStamp:   %08X", importDesc->TimeDateStamp);
		AddStringandAdjust(m_szBuf);
        wsprintf(m_szBuf,"  ForwarderChain:  %08X", importDesc->ForwarderChain);
 		AddStringandAdjust(m_szBuf);
 		wsprintf(m_szBuf,"  First thunk RVA: %08X", importDesc->FirstThunk);
		AddStringandAdjust(m_szBuf);
	
		thunk = (PIMAGE_THUNK_DATA)importDesc->FirstThunk;
		thunk = (PIMAGE_THUNK_DATA)( (PBYTE)thunk - delta + (int)base);
		
		// If the pointer that thunk points to is outside of the .idata
		// section, it looks like this file is "pre-fixed up" with regards
		// to the thunk table.  In this situation, we'll need to fall back
		// to the hint-name (aka, the "Characteristics") table.
		exportsStartRVA = pHeader->VirtualAddress;
		exportsEndRVA= exportsStartRVA + pHeader->SizeOfRawData;
		if ( (*(PDWORD)thunk <= exportsStartRVA) ||
			 (*(PDWORD)thunk >= exportsEndRVA) )
		{
			if ( importDesc->Characteristics == 0 )	// Borland doesn't have
				return;								// this table!!!
					
			thunk = (PIMAGE_THUNK_DATA)importDesc->Characteristics;
			if ( ((DWORD)thunk <= exportsStartRVA) ||
				 ((DWORD)thunk >= exportsEndRVA) )
				return;

			thunk = (PIMAGE_THUNK_DATA)( (PBYTE)thunk - delta + (int) base);
		}

		
		while ( 1 )	// Loop forever (or until we break out)
		{
			if ( thunk->u1.AddressOfData == 0 )
				break;

			if ( thunk->u1.Ordinal & IMAGE_ORDINAL_FLAG )
			{
				wsprintf(m_szBuf,"  Ordinal:%4u", thunk->u1.Ordinal & 0xFFFF);
				break;
			}
			else
			{
				pOrdinalName = thunk->u1.AddressOfData;
				pOrdinalName = (PIMAGE_IMPORT_BY_NAME)
								((PBYTE)pOrdinalName - delta + (int)base);
					
				wsprintf(m_szBuf,"  %s @ %4u",pOrdinalName->Name, pOrdinalName->Hint );
			};
			AddStringandAdjust(m_szBuf);
			
			thunk++;			// Advance to next thunk
		}

		importDesc++;	// advance to next IMAGE_IMPORT_DESCRIPTOR
	}
}

void CPEView::DumpExportsSection(char *base, PIMAGE_SECTION_HEADER pHeader)
{
	PIMAGE_EXPORT_DIRECTORY exportDir;
	INT delta; 
	PSTR filename;
	DWORD i;
	PDWORD functions;
	PWORD ordinals;
	PSTR *name;

	exportDir = (PIMAGE_EXPORT_DIRECTORY) (((int)base)+((int)pHeader->PointerToRawData));
	delta = (INT)(pHeader->VirtualAddress - pHeader->PointerToRawData);
	
	filename = (PSTR)(exportDir->Name - delta + base);
		
 	AddStringandAdjust("Exports table:");
	wsprintf(m_szBuf,"  Name:            %s", filename);
    AddStringandAdjust(m_szBuf);
	wsprintf(m_szBuf,"  Characteristics: %08X", exportDir->Characteristics);
    AddStringandAdjust(m_szBuf);
	wsprintf(m_szBuf,"  TimeDateStamp:   %08X", exportDir->TimeDateStamp);
    AddStringandAdjust(m_szBuf);
	wsprintf(m_szBuf,"  Version:         %u.%02u", exportDir->MajorVersion,
			exportDir->MinorVersion);
    AddStringandAdjust(m_szBuf);
	wsprintf(m_szBuf,"  Ordinal base:    %08X", exportDir->Base);
    AddStringandAdjust(m_szBuf);
	wsprintf(m_szBuf,"  # of functions:  %08X", exportDir->NumberOfFunctions);
    AddStringandAdjust(m_szBuf);
	wsprintf(m_szBuf,"  # of Names:      %08X", exportDir->NumberOfNames);
    AddStringandAdjust(m_szBuf);
	
	functions = (PDWORD)((DWORD)exportDir->AddressOfFunctions - delta + base);
	ordinals = (PWORD)((DWORD)exportDir->AddressOfNameOrdinals - delta + base);
	name = (PSTR *)((DWORD)exportDir->AddressOfNames - delta + base);

	printf("\n  Entry Pt  Ordn  Name\n");
	for ( i=0; i < exportDir->NumberOfNames; i++ )
	{
		wsprintf(m_szBuf,"  %s @ %4u; entry %08X", (*name - delta + (int)base),
		                                   *ordinals + exportDir->Base,
		                                   *functions);
        AddStringandAdjust(m_szBuf);
        name++;			// Bump each pointer to the next array element
		ordinals++;
		functions++;
	}
};

char *SzDebugFormats[] = {
"UNKNOWN/BORLAND","COFF","CODEVIEW","FPO","MISC","EXCEPTION","FIXUP" };



void CPEView::DumpDebugDirectory(char *base, PIMAGE_SECTION_HEADER pHeader, IMAGE_DATA_DIRECTORY va_debug_dir)
{
	PIMAGE_DEBUG_DIRECTORY debugDir;
	unsigned cDebugFormats, i;
	DWORD offsetInto_rdata;
	PSTR szDebugFormat;

	// This line was so long that we had to break it up

	// If we found a .debug section, and the debug directory is at the
	// beginning of this section, it looks like a Borland file
	if ( pHeader && (pHeader->VirtualAddress == va_debug_dir.VirtualAddress) )
	{
		debugDir = (PIMAGE_DEBUG_DIRECTORY)((int)pHeader->PointerToRawData+(int)base);
		cDebugFormats = va_debug_dir.Size;
	}
	else	// Look for microsoft debug directory in the .rdata section
	{
		pHeader = GetSectionHdrByName(base,".rdata");
		if ( !pHeader )
			return;

		// See if there's even any debug directories to speak of...
		cDebugFormats = va_debug_dir.Size
						/ sizeof(IMAGE_DEBUG_DIRECTORY);
		if ( cDebugFormats == 0 )
			return;
	
		offsetInto_rdata = va_debug_dir.VirtualAddress - pHeader->VirtualAddress;
		debugDir = (PIMAGE_DEBUG_DIRECTORY)((int)base+pHeader->PointerToRawData + offsetInto_rdata);
	}
    	
    AddStringandAdjust("Debug Info:");
	
	for ( i=0; i < cDebugFormats; i++ )
	{
		szDebugFormat = (debugDir->Type <= 6)
						? SzDebugFormats[debugDir->Type] : "???";

		wsprintf(m_szBuf,"  Type:%-15s; size: %08X @ %08X; file ptr: %08X; flags: %08X; time: %08X; version: %u.%02u",
			szDebugFormat, debugDir->SizeOfData, debugDir->AddressOfRawData,
			debugDir->PointerToRawData, debugDir->Characteristics,
			debugDir->TimeDateStamp, debugDir->MajorVersion,
			debugDir->MinorVersion);


        AddStringandAdjust(m_szBuf);

		// If COFF debug info, save its address away for later.  We
		// do the check for "PointerToSymbolTable" because some files
		// have bogus values for the COFF header offset.
/*		if ( (debugDir->Type == IMAGE_DEBUG_TYPE_COFF) &&
		     pNTHeader->FileHeader.PointerToSymbolTable )
		{
			PCOFFDebugInfo =
				(PIMAGE_DEBUG_INFO)(base+ debugDir->PointerToRawData);
		}
*/		
		debugDir++;
	}
}


long WINAPI DebugTreadFunction(CPEView *cpe) 
{  
  BOOL bRunning=TRUE;
  STARTUPINFO sa;
  PROCESS_INFORMATION pi;
  DEBUG_EVENT  DebugEvent;
  memset((LPVOID)&sa,'\0',sizeof(STARTUPINFO));
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
                 DEBUG_PROCESS,NULL,NULL,&sa,&pi))
   return FALSE;
  while(bRunning)
  { WaitForDebugEvent(&DebugEvent,INFINITE);
    switch(DebugEvent.dwDebugEventCode)
    { case CREATE_PROCESS_DEBUG_EVENT:
        cpe->PostMessage(WMC_REFRESH,0,0);	
		 break;
      case LOAD_DLL_DEBUG_EVENT:
      case UNLOAD_DLL_DEBUG_EVENT:
//       first create a new node (note that it is the responsibility of the 
// main thread to free the memory), then post the node back
         {
          HLOCAL hMem=LocalAlloc(LMEM_MOVEABLE,sizeof(DebugEvent));
          PVOID pNewMem=LocalLock(hMem);
          CopyMemory(pNewMem,(void *)&DebugEvent,sizeof(DEBUG_EVENT));
          LocalUnlock(hMem);
          cpe->PostMessage(WMC_DEBUGEVENT,(WPARAM)hMem,pi.dwProcessId);
         };
		 break;
       case EXIT_PROCESS_DEBUG_EVENT:
       case DBG_TERMINATE_PROCESS:
                bRunning = FALSE;     // fall through to process the event here
      default:
	  break;
    };
    ContinueDebugEvent(DebugEvent.dwProcessId, DebugEvent.dwThreadId,DBG_CONTINUE );

  };
 GetLastError();
 cpe->PostMessage(WMC_REFRESH,0,0);	
 return TRUE;
};
extern "C"
{

#pragma check_stack (off)

static DWORD WINAPI RemoteThreadFunc (THREADFNSTRUCT *pStruct) 
{
 pStruct->fnGetModuleFileName(pStruct->dwInstance,pStruct->chPathName,_MAX_PATH);
 return 0;
}

static void AfterThreadFunc (void) {
}
#pragma check_stack 
}

long CPEView::OnLoadDLL(WPARAM wParam, LPARAM lParam)
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
  if (hProcess == NULL) 
  {
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
          pdwCodeRemote = (PDWORD) AllocProcessMemory(hProcess, cbMemSize);
          if (pdwCodeRemote == NULL) __leave;

// Change the page protection of the allocated memory
// to executable, read, and write.
          fOk = VirtualProtectEx(hProcess, pdwCodeRemote, cbMemSize,
	            PAGE_EXECUTE_READWRITE, &dwOldProtect);
          if (!fOk) __leave;

// Write a copy of ThreadFunc to the remote process.
          fOk = WriteProcessMemory(hProcess, pdwCodeRemote,
               (LPVOID) RemoteThreadFunc, cbCodeSize, &dwNumBytesXferred);
          if (!fOk) __leave;


// Write a copy of InjLibInfo to the remote process
// (the structure MUST start on an even 32-bit bourdary).

          pInjLibInfoRemote = (THREADFNSTRUCT *) 
             (pdwCodeRemote + ((cbCodeSize + 4) & ~3));

// Put InjLibInfo in remote thread's memory block.
          fOk = WriteProcessMemory(hProcess, pInjLibInfoRemote,
             &tfRemote, sizeof(THREADFNSTRUCT), &dwNumBytesXferred);
          if (!fOk) __leave;
          hThread = CreateRemoteThread(hProcess, NULL, 0, 
                   (LPTHREAD_START_ROUTINE) pdwCodeRemote,pInjLibInfoRemote, 0, &dwThreadId);
          if (hThread == NULL) __leave;
          WaitForSingleObject(hThread, INFINITE);
         }	// __try
   __finally 
         {
          if (hThread != NULL) 
          {
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

		    
void CPEView::OnFileExecute() 
{
 DWORD idThread;      
 CloseHandle(CreateThread(NULL,9,(LPTHREAD_START_ROUTINE)DebugTreadFunction,
 (LPVOID)GetDLLPane(),
 0,&idThread));
}

CPEView *CPEView::GetDLLPane()
{ 
 return ((CPECFrame*)GetParentFrame())->GetDLLPane();
}


void CPEView::DispatchDoubleClick(int iVal)
{ 
// m_Selection contains the selected string; take it apart and see what's in there...
 char szBuf[MAX_PATH];
 int iDelimiter = strlen("loaded DLL ");
 size_t iEndofFileName;
 if (!_strnicmp("loaded DLL ",m_Selection,iDelimiter))
 {
  iEndofFileName = strcspn(&m_Selection[iDelimiter]," "); // this hoses us badly w/ long file names
  strncpy(szBuf,&m_Selection[iDelimiter],iEndofFileName);
  theApp.OpenDocumentFile(szBuf);
 };
};

BOOL CPEView::IsMyKindOfFile(BYTE *lpImage)
{ 
 return (*(USHORT *)lpImage == IMAGE_DOS_SIGNATURE) &&
        (*(DWORD *)NTSIGNATURE (lpImage) == IMAGE_NT_SIGNATURE);
};


afx_msg long CPEView::OnRefresh(WPARAM wParam, LPARAM lParam)
{
 theApp.RefreshProcessList();
 return 0;
};
