// mclasses.cpp - implements the device extension class for the mouse class device

extern "C"
{

#include "stdarg.h"
#include "stdio.h"
#include "ntddk.h"
#ifdef MOUSECLASSTYPE
#include "mouclass.h"
#include "kbdmou.h"
#include "moulog.h"
#else
#include "kbdclass.h"
#include "kbdmou.h"
#include "kbdlog.h"
#endif

}

#include "drvclass.h"


CInputClassDeviceExt::CInputClassDeviceExt(CGlobalInputClassData *cGlobal) 
{
 m_status = STATUS_INSUFFICIENT_RESOURCES;
 m_iStructureSize = sizeof(INPUT_DATA);
 m_InputData = 0;
 cData = cGlobal;
  
 KeInitializeSpinLock(&SpinLock);
 RequestIsPending = FALSE;
 CleanupWasInitiated = FALSE;
 m_InputData = 
        (PCHAR)ExAllocatePool(
            NonPagedPool,cData->InputAttributes.InputDataQueueLength);
 if (!m_InputData) return;   
 m_status = STATUS_SUCCESS;
 FlushDataQueue();
};



void CInputClassDeviceExt::FlushDataQueue()
{
 KIRQL oldIrql;
 KeAcquireSpinLock(&SpinLock, &oldIrql);
 InputCount = 0;
 m_DataIn = m_InputData;
 m_DataOut = m_InputData;
 OkayToLogOverflow = TRUE;
 KeReleaseSpinLock(&SpinLock, oldIrql);
};

CInputClassDeviceExt::~CInputClassDeviceExt()
{
 if (m_InputData) ExFreePool(m_InputData);
};

int CInputClassDeviceExt::Insert(PCHAR source, int iSize)
{
 int iSpaceLeft = cData->InputAttributes.InputDataQueueLength - (InputCount * m_iStructureSize);
 if ((!iSpaceLeft) && OkayToLogOverflow)
 { 
   OkayToLogOverflow = FALSE;
   // in the shipping version, we need to log an error entry here, specifying
   // INPUT_ERROR_BASE+210 as the error, and bytesToMove and QueueSize as the attributes...
   DbgPrint("Losing data!!!!\n");
   return 0;
 };
 iSize = (iSize < iSpaceLeft)?iSize:iSpaceLeft;
 int iEmptyBuffer = (PCHAR) m_InputData + cData->InputAttributes.InputDataQueueLength -
                     (PCHAR) m_DataIn;
 // now move the first chunk (between the pointer and end of buffer)
 int iWeWillMoveThese = (iSize < iEmptyBuffer)?iSize:iEmptyBuffer;
 RtlMoveMemory(m_DataIn, source, iWeWillMoveThese);
 source+=iWeWillMoveThese;
 m_DataIn+=iWeWillMoveThese;
 // wrap buffer if necessary
 if (m_DataIn>= m_InputData+cData->InputAttributes.InputDataQueueLength)
     m_DataIn = m_InputData;
 // now determine other chunk of memory (from buffer veginning to current pointer)
 if (iSize > iWeWillMoveThese)
 { 
   iWeWillMoveThese = iSize - iWeWillMoveThese;
   RtlMoveMemory(m_DataIn,source, iWeWillMoveThese);
   m_DataIn+=iWeWillMoveThese;
 };
 InputCount+= iSize/m_iStructureSize;
 return iSize;
};

int CInputClassDeviceExt::Remove(PCHAR dest, int iSize)
{
 int iCurrentQueueSize= InputCount*m_iStructureSize;
 iSize = (iSize<iCurrentQueueSize)?iSize:iCurrentQueueSize;
 // do first chunk (from CurrentPointer backwards to beg. of buffer)
 int iCurrentEnd = m_InputData+cData->InputAttributes.InputDataQueueLength - m_DataOut;
 int iWeWillRemoveThese = (iSize<iCurrentEnd)?iSize:iCurrentEnd;
 RtlMoveMemory(dest,m_DataOut,iWeWillRemoveThese);
 dest+=iWeWillRemoveThese;
 // now check if we need to wrap the buffer around...
 if (iSize > iWeWillRemoveThese)
 { 
  iWeWillRemoveThese = iSize - iWeWillRemoveThese;
  RtlMoveMemory(dest,m_InputData,iWeWillRemoveThese);
  m_DataOut = m_InputData+iWeWillRemoveThese;
 }
 else
  m_DataOut += iWeWillRemoveThese;
 InputCount -= iSize/m_iStructureSize;
 if (!InputCount) OkayToLogOverflow = TRUE;
 return iSize;
};
 
CGlobalInputClassData::CGlobalInputClassData(void)
{
};

CGlobalInputClassData::~CGlobalInputClassData(void)
{
 ExFreePool(PortDeviceObjectList);
};


// we need to initialize this member after the registry has been read.
// There ought to be a better way to do it - let's check...
// also see if this data member can be relocated into a different
// object as it is shared by all copied of the root object.

BOOLEAN CGlobalInputClassData::InitializePortDeviceObjectList(void)
{
 PortDeviceObjectList = 
        (PDEVICE_OBJECT *) ExAllocatePool(NonPagedPool,
            sizeof(PDEVICE_OBJECT) * MaximumPortsServiced);
 if (!PortDeviceObjectList) return FALSE;
 return TRUE;
};
