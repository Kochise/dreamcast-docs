
extern "C"
{

#include "ntddk.h"

}

#include "drvclass.h"


void * __cdecl operator new(unsigned int nSize, POOL_TYPE iType)
{ 
 return ExAllocatePool(iType,nSize);
 };

void __cdecl operator delete(void* p)
{ 
  ExFreePool(p);
};


// derived class Unicode string

#define TYPE_SYSTEM_ALLOCATED 0
#define TYPE_DRIVER_ALLOCATED 1

CUString::CUString(int nSize)
{
 m_status = STATUS_INSUFFICIENT_RESOURCES;
 m_bType = TYPE_DRIVER_ALLOCATED;
 RtlInitUnicodeString(&m_String,NULL);
 m_String.MaximumLength = nSize;
 m_String.Buffer = (unsigned short *)ExAllocatePool(PagedPool,nSize);
 if (!m_String.Buffer) return;  // leaving status the way it is
 RtlZeroMemory(m_String.Buffer,m_String.MaximumLength);
 m_status = STATUS_SUCCESS;

};

CUString::CUString(PWCHAR uszString)
{
 m_status = STATUS_SUCCESS;
 m_bType = TYPE_SYSTEM_ALLOCATED;
 RtlInitUnicodeString(&m_String,uszString);
};

CUString::CUString(int iVal, int iBase)  
{
 m_status = STATUS_INSUFFICIENT_RESOURCES;
 m_bType = TYPE_DRIVER_ALLOCATED;
 RtlInitUnicodeString(&m_String,NULL);
 int iSize=1;
 int iValCopy=(!iVal)?1:iVal;
 while (iValCopy>=1)
 {
  iValCopy/=iBase;
  iSize++;
 };   // now iSize carries the number of digits

 iSize*=sizeof(WCHAR);
 
 m_String.MaximumLength = iSize;
 m_String.Buffer = (unsigned short *)ExAllocatePool(PagedPool,iSize);
 if (!m_String.Buffer) return;
 RtlZeroMemory(m_String.Buffer,m_String.MaximumLength);
 m_status = RtlIntegerToUnicodeString(iVal, iBase, &m_String);
};


CUString::~CUString()
{
 if ((m_bType == TYPE_DRIVER_ALLOCATED) && m_String.Buffer) ExFreePool(m_String.Buffer);
};

void CUString::Append(UNICODE_STRING *uszString)
{
 m_status = RtlAppendUnicodeStringToString(&m_String,uszString);
};

void CUString::CopyTo(CUString *pTarget)
{
 RtlCopyUnicodeString(&pTarget->m_String,&m_String);
}


BOOL CUString::operator==(CUString cuArg)
{
return (!RtlCompareUnicodeString(&m_String,&cuArg.m_String,FALSE));
}


// the registry access class

CRegistry::CRegistry(int iSize)
{ m_status = STATUS_INSUFFICIENT_RESOURCES;
  m_pTable = (PRTL_QUERY_REGISTRY_TABLE)
		ExAllocatePool(PagedPool,sizeof(RTL_QUERY_REGISTRY_TABLE)*(iSize+1));
  if(m_pTable)
   {
    m_status = STATUS_SUCCESS;
    RtlZeroMemory(m_pTable,sizeof(RTL_QUERY_REGISTRY_TABLE)*(iSize+1)); //this will terminate the table
   };                                                                  // appropriately

};
CRegistry::~CRegistry()
{    
 if (m_pTable) ExFreePool(m_pTable);
};
BOOL CRegistry::QueryDirect(CUString *location,CUString *key, void **pReceiveBuffer, ULONG uType)
{
   ULONG zero = 0;

m_pTable[0].Flags = RTL_QUERY_REGISTRY_DIRECT;
m_pTable[0].Name = key->m_String.Buffer;
m_pTable[0].EntryContext = *pReceiveBuffer;
m_pTable[0].DefaultType = uType;
m_pTable[0].DefaultData = &zero;
m_pTable[0].DefaultLength = sizeof(ULONG); // there must be something here, but we need to know what...
if (STATUS_SUCCESS!=
    RtlQueryRegistryValues(RTL_REGISTRY_ABSOLUTE,location->m_String.Buffer,m_pTable,NULL,NULL))
  return FALSE;
return TRUE; 
};

BOOL CRegistry::QueryWithCallback(PRTL_QUERY_REGISTRY_ROUTINE callback,ULONG RelativeTo,PWSTR Path,PVOID Context, PVOID Environment)
{
m_pTable[0].QueryRoutine = callback;
m_pTable[0].Name = NULL;
m_status = RtlQueryRegistryValues(RelativeTo|RTL_REGISTRY_OPTIONAL,Path,m_pTable,Context,Environment);
return NT_SUCCESS(m_status);
};

BOOL CRegistry::WriteString(ULONG relativeTo, CUString *pBuffer, CUString *pPath, CUString *pKey)
{
 return NT_SUCCESS(RtlWriteRegistryValue(relativeTo, pPath->GetString(), pKey->GetString(),REG_SZ,pBuffer->GetString(),pBuffer->GetLength()+sizeof(UNICODE_NULL)));
};

BOOL CRegistry::WriteDWord(ULONG relativeTo, void *pBuffer,CUString *pPath,CUString *pKey)
{
 return NT_SUCCESS(RtlWriteRegistryValue(relativeTo, pPath->GetString(), pKey->GetString(),REG_DWORD,pBuffer,sizeof(REG_DWORD)));
};

 
CErrorLogEntry::CErrorLogEntry(PVOID pSource, ULONG errorCode, USHORT dumpDataSize, ULONG uniqueErrorValue,
                    NTSTATUS status, ULONG *dumpData, UCHAR FunctionCode)
{
m_pPacket = (PIO_ERROR_LOG_PACKET)
    IoAllocateErrorLogEntry(pSource, (UCHAR) (sizeof(IO_ERROR_LOG_PACKET)+
	                                          (dumpDataSize * sizeof(ULONG))));
if (!m_pPacket) return;
int i;
m_pPacket->ErrorCode = errorCode;
m_pPacket->DumpDataSize = dumpDataSize * sizeof(ULONG);
m_pPacket->SequenceNumber = 0;
m_pPacket->MajorFunctionCode = FunctionCode;
m_pPacket->IoControlCode = 0;
m_pPacket->RetryCount = 0;
m_pPacket->UniqueErrorValue = uniqueErrorValue;
m_pPacket->FinalStatus = status;
for (i = 0; i < dumpDataSize; i++)
   m_pPacket->DumpData[i] = dumpData[i];
IoWriteErrorLogEntry(m_pPacket);
};


CErrorLogEntry::~CErrorLogEntry()
{
};

