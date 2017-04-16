// plist.cpp -- implements the process enumerator


#include "stdafx.h"
#include <winperf.h>

#include "viewfile.h"

#include "fileview.h"
#include "pview.h"


#include "plist.h"

// helper functions -- stolen from the PVIEW app...


HKEY ghPerfKey = HKEY_PERFORMANCE_DATA;  // get perf data from this key
HKEY ghMachineKey = HKEY_LOCAL_MACHINE;  // get title index from this key

DWORD   PX_PROCESS;
/*
DWORD   PX_PROCESS_CPU;
DWORD   PX_PROCESS_PRIV;
DWORD   PX_PROCESS_USER;
DWORD   PX_PROCESS_WORKING_SET;
DWORD   PX_PROCESS_PEAK_WS;
DWORD   PX_PROCESS_PRIO;
DWORD   PX_PROCESS_ELAPSE;
*/
DWORD   PX_PROCESS_ID;
/*
DWORD   PX_PROCESS_PRIVATE_PAGE;
DWORD   PX_PROCESS_VIRTUAL_SIZE;
DWORD   PX_PROCESS_PEAK_VS;
DWORD   PX_PROCESS_FAULT_COUNT;
DWORD   PX_PROCESS_PAGED_POOL_QUOTA;
DWORD   PX_PROCESS_PEAK_PAGED_POOL_QUOTA;
DWORD   PX_PROCESS_NONPAGED_POOL_QUOTA;
DWORD   PX_PROCESS_PEAK_PAGED_POOL;
DWORD   PX_PROCESS_PEAK_NONPAGED_POOL;
DWORD   PX_PROCESS_CUR_PAGED_POOL;
DWORD   PX_PROCESS_CUR_NONPAGED_POOL;
DWORD   PX_PROCESS_PAGED_POOL_LIMIT;
DWORD   PX_PROCESS_NONPAGED_POOL_LIMIT;

*/
DWORD   PX_THREAD;
/*
DWORD   PX_THREAD_CPU;
DWORD   PX_THREAD_PRIV;
DWORD   PX_THREAD_USER;
DWORD   PX_THREAD_START;
DWORD   PX_THREAD_SWITCHES;
DWORD   PX_THREAD_PRIO;
DWORD   PX_THREAD_BASE_PRIO;
DWORD   PX_THREAD_ELAPSE;

DWORD   PX_THREAD_DETAILS;
DWORD   PX_THREAD_PC;

DWORD   PX_IMAGE;
DWORD   PX_IMAGE_NOACCESS;
DWORD   PX_IMAGE_READONLY;
DWORD   PX_IMAGE_READWRITE;
DWORD   PX_IMAGE_WRITECOPY;
DWORD   PX_IMAGE_EXECUTABLE;
DWORD   PX_IMAGE_EXE_READONLY;
DWORD   PX_IMAGE_EXE_READWRITE;
DWORD   PX_IMAGE_EXE_WRITECOPY;


DWORD   PX_PROCESS_ADDRESS_SPACE;
DWORD   PX_PROCESS_PRIVATE_NOACCESS;
DWORD   PX_PROCESS_PRIVATE_READONLY;
DWORD   PX_PROCESS_PRIVATE_READWRITE;
DWORD   PX_PROCESS_PRIVATE_WRITECOPY;
DWORD   PX_PROCESS_PRIVATE_EXECUTABLE;
DWORD   PX_PROCESS_PRIVATE_EXE_READONLY;
DWORD   PX_PROCESS_PRIVATE_EXE_READWRITE;
DWORD   PX_PROCESS_PRIVATE_EXE_WRITECOPY;


DWORD   PX_PROCESS_MAPPED_NOACCESS;
DWORD   PX_PROCESS_MAPPED_READONLY;
DWORD   PX_PROCESS_MAPPED_READWRITE;
DWORD   PX_PROCESS_MAPPED_WRITECOPY;
DWORD   PX_PROCESS_MAPPED_EXECUTABLE;
DWORD   PX_PROCESS_MAPPED_EXE_READONLY;
DWORD   PX_PROCESS_MAPPED_EXE_READWRITE;
DWORD   PX_PROCESS_MAPPED_EXE_WRITECOPY;


DWORD   PX_PROCESS_IMAGE_NOACCESS;
DWORD   PX_PROCESS_IMAGE_READONLY;
DWORD   PX_PROCESS_IMAGE_READWRITE;
DWORD   PX_PROCESS_IMAGE_WRITECOPY;
DWORD   PX_PROCESS_IMAGE_EXECUTABLE;
DWORD   PX_PROCESS_IMAGE_EXE_READONLY;
DWORD   PX_PROCESS_IMAGE_EXE_READWRITE;
DWORD   PX_PROCESS_IMAGE_EXE_WRITECOPY;
*/


PPERF_OBJECT_TYPE FirstObject (PPERF_DATA_BLOCK pData)
{
 if (pData) return ((PPERF_OBJECT_TYPE) ((PBYTE) pData + pData->HeaderLength));
  else return NULL;
}


PPERF_OBJECT_TYPE NextObject (PPERF_OBJECT_TYPE pObject)
{
 if (pObject) return ((PPERF_OBJECT_TYPE) ((PBYTE) pObject + pObject->TotalByteLength));
  else return NULL;
}


PPERF_OBJECT_TYPE FindObject (PPERF_DATA_BLOCK pData, DWORD TitleIndex)
{
 PPERF_OBJECT_TYPE pObject;
 DWORD        i = 0;
 if (pObject = FirstObject (pData))
 while (i < pData->NumObjectTypes)
 {
  if (pObject->ObjectNameTitleIndex == TitleIndex) return pObject;
  pObject = NextObject (pObject);
  i++;
 }
 return NULL;
}

DWORD GetPerfTitleSz (HKEY    hKeyMachine,HKEY hKeyPerf,LPTSTR  *TitleBuffer,
                      LPTSTR  *TitleSz[],DWORD   *TitleLastIdx)
{
 HKEY	  hKey1;
 HKEY    hKey2;
 DWORD   Type;
 DWORD   DataSize;
 DWORD   dwR;
 DWORD   Len;
 DWORD   Index;
 DWORD   dwTemp;
 BOOL    bNT10;
 LPTSTR  szCounterValueName;
 LPTSTR  szTitle;
// Initialize
 hKey1        = NULL;
 hKey2        = NULL;
 *TitleBuffer = NULL;
 *TitleSz     = NULL;
// Open the perflib key to find out the last counter's index and system version.
 dwR = RegOpenKeyEx (hKeyMachine,
                     TEXT("software\\microsoft\\windows nt\\currentversion\\perflib"),
                     0,KEY_READ,&hKey1);
 if (dwR != ERROR_SUCCESS) goto done;
// Get the last counter's index so we know how much memory to allocate for TitleSz
 DataSize = sizeof (DWORD);
 dwR = RegQueryValueEx (hKey1, TEXT("Last Counter"), 0, &Type, (LPBYTE)TitleLastIdx, &DataSize);
 if (dwR != ERROR_SUCCESS) goto done;
// Find system version, for system earlier than 1.0a, there's no version value.
 dwR = RegQueryValueEx (hKey1, TEXT("Version"), 0, &Type, (LPBYTE)&dwTemp, &DataSize);
 if (dwR != ERROR_SUCCESS) bNT10 = TRUE; // unable to read the value, assume NT 1.0
  else bNT10 = FALSE; // found the value, so, NT 1.0a or later
 if (bNT10)
 {
  szCounterValueName = TEXT("Counters");
  dwR = RegOpenKeyEx (hKeyMachine,
                      TEXT("software\\microsoft\\windows nt\\currentversion\\perflib\\009"),
                      0,KEY_READ,&hKey2);
  if (dwR != ERROR_SUCCESS) goto done;
 }
 else
 {
  szCounterValueName = TEXT("Counter 009");
  hKey2 = hKeyPerf;
 }
 dwR = RegQueryValueEx (hKey2, szCounterValueName, 0, &Type, 0, &DataSize);
 if (dwR != ERROR_SUCCESS) goto done;
 *TitleBuffer = (LPTSTR)LocalAlloc (LMEM_FIXED, DataSize);
 if (!*TitleBuffer)
 {
  dwR = ERROR_NOT_ENOUGH_MEMORY;
  goto done;
 }
 *TitleSz = (LPTSTR *)LocalAlloc (LPTR, (*TitleLastIdx+1) * sizeof (LPTSTR));
 if (!*TitleSz)
 {
  dwR = ERROR_NOT_ENOUGH_MEMORY;
  goto done;
 }
 dwR = RegQueryValueEx (hKey2, szCounterValueName, 0, &Type, (BYTE *)*TitleBuffer, &DataSize);
 if (dwR != ERROR_SUCCESS) goto done;
 szTitle = *TitleBuffer;
 while (Len = lstrlen (szTitle))
 {
  Index = atoi (szTitle);
  szTitle = szTitle + Len +1;
  if (Index <= *TitleLastIdx) (*TitleSz)[Index] = szTitle;
  szTitle = szTitle + lstrlen (szTitle) +1;
 }
 done:
 if (dwR != ERROR_SUCCESS)
 {
  if (*TitleBuffer) LocalFree (*TitleBuffer);
  if (*TitleSz)     LocalFree (*TitleSz);
 }
 if (hKey1) RegCloseKey (hKey1);
 if (hKey2 && hKey2 != hKeyPerf) RegCloseKey (hKey2);
 return dwR;
}

DWORD GetPerfData(HKEY hPerfKey,LPTSTR szObjectIndex,PPERF_DATA_BLOCK *ppData,DWORD *pDataSize)
{
 DWORD   DataSize;
 DWORD   dwR;
 DWORD   Type;
 if (!*ppData) *ppData = (PPERF_DATA_BLOCK) LocalAlloc (LMEM_FIXED, *pDataSize);
 do  
  {
   DataSize = *pDataSize;
   dwR = RegQueryValueEx (hPerfKey,szObjectIndex,NULL,&Type,(BYTE *)*ppData,&DataSize);
   if (dwR == ERROR_MORE_DATA)
   {
    LocalFree (*ppData);
    *pDataSize += 1024;
    *ppData = (PPERF_DATA_BLOCK) LocalAlloc (LMEM_FIXED, *pDataSize);
   }
   if (!*ppData)
   {
    LocalFree (*ppData);
    return ERROR_NOT_ENOUGH_MEMORY;
   }
  } while (dwR == ERROR_MORE_DATA);
 return dwR;
}



PPERF_DATA_BLOCK RefreshPerfData (HKEY hPerfKey,LPTSTR szObjectIndex,PPERF_DATA_BLOCK pData,DWORD *pDataSize)
{
 if (GetPerfData (hPerfKey, szObjectIndex, &pData, pDataSize) == ERROR_SUCCESS)
   return pData;
  else
   return NULL;
}

//********************************************************
//
//  GetTitleIdx
//
//      Searches Titles[] for Name.  Returns the index found.
//
DWORD   GetTitleIdx (LPTSTR Title[], DWORD LastIndex, LPTSTR Name)
{
 DWORD   Index;
 for (Index = 0; Index <= LastIndex; Index++)
  if (Title[Index])
   if (!lstrcmpi (Title[Index], Name))
    return Index;
  return 0;
}

BOOL SetPerfIndexes (TCHAR *tc)
{
 LPTSTR  TitleBuffer;
 LPTSTR  *Title;
 DWORD   Last;
 DWORD   dwR;
 dwR = GetPerfTitleSz (ghMachineKey, ghPerfKey, &TitleBuffer, &Title, &Last);
 if (dwR != ERROR_SUCCESS)
   return FALSE;
 PX_PROCESS = GetTitleIdx ( Title, Last, PN_PROCESS);
 PX_PROCESS_ID = GetTitleIdx (Title, Last, PN_PROCESS_ID);
 PX_THREAD = GetTitleIdx (Title, Last, PN_THREAD);
 wsprintf (tc, TEXT("%ld %ld"), PX_PROCESS, PX_THREAD);
 LocalFree (TitleBuffer);
 LocalFree (Title);
 return TRUE;
}


PPERF_COUNTER_DEFINITION FindCounter (PPERF_OBJECT_TYPE pObject, DWORD TitleIndex)
{
 PPERF_COUNTER_DEFINITION pCounter;
 DWORD i = 0;
 if (pCounter = (PPERF_COUNTER_DEFINITION)((PCHAR) pObject + pObject->HeaderLength))
  while (i < pObject->NumCounters)
  {
   if (pCounter->CounterNameTitleIndex == TitleIndex)
     return pCounter;
   pCounter = (PPERF_COUNTER_DEFINITION)((PCHAR) pCounter + pCounter->ByteLength);
   i++;
  }
 return NULL;
}

// class library begins here...

CPerfData::CPerfData()
{};

CPerfData::~CPerfData()
{};

long WINAPI PViewEnumThread(CPView *cpTarget)
{// local variables
 static char szListText[] = "%#x : %ls";
 static TCHAR szProcessStrings[2*INDEX_STR_LEN];
 DWORD gPerfDataSize = 50*1024;            // start with 50K
 PPERF_DATA_BLOCK gpPerfData = (PPERF_DATA_BLOCK)0;
 PPERF_INSTANCE_DEFINITION  pInstance;
 PPERF_COUNTER_DEFINITION pCounterProcID;
 DWORD *pdwProcID;
 INT InstanceIndex = 0;
 PPERF_OBJECT_TYPE gpProcessObject;                    // pointer to process objects
 PPERF_OBJECT_TYPE gpThreadObject;                     // pointer to thread objects

 if (!SetPerfIndexes(szProcessStrings))
   return FALSE;	                      // the only purpose in life of this call is
                                          // to fill in the string...
 gpPerfData = RefreshPerfData (ghPerfKey, szProcessStrings, gpPerfData, &gPerfDataSize);
 gpProcessObject = FindObject (gpPerfData, PX_PROCESS);
 gpThreadObject  = FindObject (gpPerfData, PX_THREAD);
 pInstance = (PPERF_INSTANCE_DEFINITION)((PCHAR) gpProcessObject + gpProcessObject->DefinitionLength);
 pCounterProcID = FindCounter (gpProcessObject, PX_PROCESS_ID);
 while (pInstance && InstanceIndex < gpProcessObject->NumInstances)
 { // figure out what goes into the string
  PERF_COUNTER_BLOCK *pCounterBlock;
  pCounterBlock = (PERF_COUNTER_BLOCK *)((PCHAR) pInstance + pInstance->ByteLength);
  pdwProcID = (DWORD *)((PCHAR)pCounterBlock + pCounterProcID->CounterOffset);
  HANDLE hMem=LocalAlloc(LMEM_MOVEABLE,sizeof(szListText));
  LPSTR lpMem = (char *)LocalLock(hMem);
  wsprintf (lpMem,szListText,*pdwProcID,(LPTSTR) ((PCHAR) pInstance + pInstance->NameOffset));
  LocalUnlock(hMem);
  cpTarget->PostMessage(WMC_NEXTENTRY,(WPARAM)hMem,NULL);
  pInstance = (PPERF_INSTANCE_DEFINITION)((PCHAR) pCounterBlock + pCounterBlock->ByteLength);
  InstanceIndex++;
 };
 cpTarget->PostMessage(WMC_FINISHED,NULL,NULL);
 return TRUE;
};

BOOL CPerfData::Initialize(CPView *cpTarget)
{ HANDLE hThread;
  DWORD id;
  hThread =::CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)PViewEnumThread,cpTarget,0,&id);
  if (!hThread) return FALSE;
  else 
  {
   CloseHandle(hThread);
   return TRUE;
  };
};


BOOL CPerfData::KillProcessEntry(int iID)
{ HANDLE hProcess;
  hProcess = OpenProcess (PROCESS_ALL_ACCESS, FALSE, iID);
  if (!hProcess) return FALSE;
  if (!TerminateProcess (hProcess, 99))
  {
   CloseHandle (hProcess);
   return FALSE;
  };
  WaitForSingleObject(hProcess,INFINITE);
  CloseHandle (hProcess);
  return TRUE;
};

   
