/*
 *  SYSCTRL.C - System Control Message Support for SAMPLE
 *
 *  Notes:
 *
 *	This file processes all the control messages sent by VMM.
 */

#include <memory.h>
#include <string.h>

#include <stdio.h>

#define	WANTVXDWRAPS

#include <basedef.h>
#include <vmm.h>
#include <debug.h>


#include <vmmreg.h>
#include <vxdwraps.h>
#include <configmg.h>
#include <shell.h>
#include <ifs.h>    // for MAX_PATH...

#include "helper.h"

void callback_Control(void); // extern in callback.obj

//If we were to go C only, we would use this declaration instead of the assembler stub
/*
struct VxD_Desc_Block callback_DDB = 
                              { NULL,
                                DDK_VERSION,
								UNDEFINED_DEVICE_ID,
								1,0,
								NULL,
								"callback",
								UNDEFINED_INIT_ORDER,
								(ULONG)callback_Control,
								NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
*/
void Int_60h_Hook_Procedure(void);

#pragma VxD_IDATA_SEG

char szKeyName[] = "DLLLocation";
char *szProfile;

#pragma VxD_PAGEABLE_DATA_SEG


HVM hSystemVM;

char szDLLName[MAX_PATH];
CONTBLOCK pArgs;
DWORD dRing3Address;

#ifdef DEBUG 

char szDebugStr[]="VxD loaded #EBX times...";   

#endif // DEBUG

#ifdef DEBUG

#pragma VxD_STATIC_DATA_SEG

DWORD dOpenCount = 0;

#endif // DEBUG


#pragma VxD_ICODE_SEG

/****************************************************************************
 *
 *	Device_Init - This procedure gets called every time the VxD
 *		      is loaded
 *
 *	Exported.
 *
 *	ENTRY:	DevInf is a pointer to the VXDLDR device info packet.
 *
 *	EXIT:	VXD_SUCCESS or VXD_FAILURE.
 *
 ***************************************************************************/

#pragma intrinsic(memcpy,strlen)

CM_VXD_RESULT CM_SYSCTRL
callback_Device_Init(struct DeviceInfo *DevInf)
{   
#ifdef DEBUG    
    dOpenCount++;
#endif // DEBUG
    hSystemVM = Get_Sys_VM_Handle();
// Build a selector for the data stuff that the 16-bit DLL can see...
// first build a descriptor dword to pass to Allocate_LDT_Selector
	_asm xor eax,eax;  // flags
	_asm push eax;
	_asm mov eax,D_GRAN_BYTE; // DESCSize
	_asm push eax;
	_asm mov eax,R_DATA_TYPE; // DESCType -- DPL is ignored 
	_asm push eax;
	_asm mov eax, size CONTBLOCK;      // descriptor limit...
	_asm push eax;
	_asm mov eax, offset pArgs;  // base...
	_asm push eax;
	VMMCall(_BuildDescriptorDWORDs);
// Now build a selector on behalf of the system VM that points to pArgs
	_asm add esp,5*4;
	_asm xor ecx,ecx;      // flags
	_asm push ecx;      
	_asm inc ecx;          // count
	_asm push ecx;
	_asm push eax;         // returned from previous call
	_asm push edx;         // dito...
	_asm mov eax,[hSystemVM];
	_asm push eax;
    VMMCall(_Allocate_LDT_Selector);  // in reality, check return values here...
// store the returned selector in dRing3Address.
    _asm add esp,4*5;
    _asm mov ecx,offset dRing3Address;
    _asm mov word ptr [ecx+2],ax;
// we want offset 0 because the base of the descriptor already points to dRing3Address.
    _asm xor ax,ax;
    _asm mov word ptr [ecx],0;

// now allocate a V86 mode interrupt hook so that we can communicate info
// from the VM to the VxD...
    _asm mov eax,60h;
    _asm mov esi, OFFSET Int_60h_Hook_Procedure;
    VMMCall (Hook_V86_Int_Chain);
// here demonstrate the use of static segments.
#ifdef DEBUG
    _asm mov esi, offset szDebugStr;
    _asm mov ebx, dOpenCount;
    _asm pushfd;
    _asm pushad;
    VMMCall(Out_Debug_String);
    _asm popad;
    _asm popfd;
#endif // DEBUG
    return(VXD_SUCCESS);

}

/****************************************************************************
 *
 *	Device_Exit - This procedure gets called every time the VxD
 *		      is unloaded
 *
 *	Exported.
 *
 *	ENTRY:	DevInf is a pointer to the VXDLDR device info packet.
 *
 *	EXIT:	VXD_SUCCESS or VXD_FAILURE.
 *
 ***************************************************************************/


#pragma VxD_PAGEABLE_CODE_SEG

void __declspec(naked) Int_60h_Hook_Procedure(void)
{ WORD wDX,wAX;
  char *dwAddress;
  VxD_Prolog
  _asm int 3;
  wDX = crRegs->Client_DX;
  wAX = crRegs->Client_AX;
  _asm xor eax,eax;
  _asm push eax;       // flags
  _asm movzx eax,[wDX];
  _asm push eax;
  _asm mov eax,[hSystemVM];
  _asm push eax;
  VMMCall(_SelectorMapFlat);
  _asm add esp, 3*4;
  _asm mov [dwAddress],eax;
  dwAddress+=wAX;
  memcpy(szDLLName,dwAddress,strlen(dwAddress));
  VxD_Epilog
}

CM_VXD_RESULT CM_SYSCTRL
callback_Device_Exit(struct DeviceInfo *DevInf)
{
	// Clean up here...
	// 
    _asm xor eax,eax;
    _asm push eax;
    _asm mov eax, OFFSET dRing3Address;
    _asm xor ecx,ecx;
    _asm mov cx, WORD PTR [eax+2];
    _asm push ecx;
    _asm mov eax,[hSystemVM];
    _asm push eax;
    VMMCall(_Free_LDT_Selector);
    _asm add esp,3*4; 
	return(VXD_SUCCESS);
}

// This is the appy callback function. It copies the current CONTBLOCK packet
// (which was filled in by the notification handlers) into the pArgs
// block, which the ring 3 application can see. It then calls the DLL which
// copies the data into a queue of its own for display. The callback also
// deletes the previously allocated chunk of heap.


APPY_CALLBACK AppyCallBack(PVOID dwRef)
{
CONTBLOCK *cb = (CONTBLOCK *)dwRef;
memcpy((void *)&pArgs,dwRef,sizeof(CONTBLOCK));
#ifdef DEBUG
if (!
#endif // DEBUG
     _SHELL_CallDll(szDLLName,"ReceiveDisplayString",4,&dRing3Address)
#ifdef DEBUG 
   )
    Debug_Printf("failed call to _SHELL_CallDll...\n\r");
    else 
    Debug_Printf("finished Appy time processing...\n\r");
#endif // DEBUG
    _HeapFree(cb,0);
}

// these functions catch the thread and VM creation and destruction
// notifications. Each time one of them is invoked, a new chunk of memory
// the size of a CONTBLOCK is allocated which is then filled with the
// desired info and passed to the appy callback.


CM_VXD_RESULT CM_SYSCTRL
callback_Create_Thread(PTCB iThreadHandle)
{ CONTBLOCK *cb;
  cb=(CONTBLOCK *)_HeapAllocate(sizeof(CONTBLOCK),HEAPZEROINIT);
  cb->ThreadHandle=iThreadHandle;
  cb->VMHandle=iThreadHandle->TCB_VMHandle;
  cb->dwFlags=CREATE_THREAD;
#ifdef DEBUG
  if (!
#endif
  _SHELL_CallAtAppyTime(AppyCallBack,cb,0)
#ifdef DEBUG
  )
    Debug_Printf("Failed call at appy time event...\n\r");
#endif
  return (VXD_SUCCESS);
}

CM_VXD_RESULT CM_SYSCTRL
callback_Create_VM(ULONG iVMHandle)
{
  PTCB iThreadHandle;
  CONTBLOCK *cb;
  _asm mov ebx,[iVMHandle];
  VMMCall(Get_Initial_Thread_Handle);
  _asm mov [iThreadHandle],edi;
  cb=(CONTBLOCK *)_HeapAllocate(sizeof(CONTBLOCK),HEAPZEROINIT);
  cb->ThreadHandle=iThreadHandle;
  cb->VMHandle=iThreadHandle->TCB_VMHandle;
  cb->dwFlags=CREATE_VM;
#ifdef DEBUG
  if (!
#endif
     _SHELL_CallAtAppyTime(AppyCallBack,cb,0)
#ifdef DEBUG     
     )
     Debug_Printf("Failed call at appy time event...\n\r");
#endif
  return (VXD_SUCCESS);
}

CM_VXD_RESULT CM_SYSCTRL
callback_Destroy_VM(ULONG iVMHandle)
{
  PTCB iThreadHandle;
  CONTBLOCK *cb;
  cb=(CONTBLOCK *)_HeapAllocate(sizeof(CONTBLOCK),HEAPZEROINIT);
  cb->VMHandle=iVMHandle;
  cb->dwFlags=DESTROY_VM;
#ifdef DEBUG
  if (!
#endif  
  _SHELL_CallAtAppyTime(AppyCallBack,cb,0)
#ifdef DEBUG  
  )
     Debug_Printf("Failed call at appy time event...\n\r");
#endif
  return (VXD_SUCCESS);
}

CM_VXD_RESULT CM_SYSCTRL
callback_Destroy_Thread(PTCB iThreadHandle)
{ CONTBLOCK *cb;
  cb=(CONTBLOCK *)_HeapAllocate(sizeof(CONTBLOCK),HEAPZEROINIT);
  cb->ThreadHandle=iThreadHandle;
  cb->VMHandle=iThreadHandle->TCB_VMHandle;
  cb->dwFlags=DESTROY_THREAD;
#ifdef DEBUG
  if (!
#endif  
  _SHELL_CallAtAppyTime(AppyCallBack,cb,0)
#ifdef DEBUG  
  )
     Debug_Printf("Failed call at appy time event...\n\r");
#endif
  return (VXD_SUCCESS);
}


#pragma VxD_LOCKED_CODE_SEG


void __declspec(naked) callback_Control(void)
{ DWORD dwControlCode;
  DWORD dwArg;
// stripped-down VxD_Prolog
    _asm mov ebp,esp;
    _asm sub esp, __LOCAL_SIZE;
	_asm mov [dwControlCode],eax;
// function body
    switch (dwControlCode)
	{ case SYS_DYNAMIC_DEVICE_INIT:
         _asm mov [dwArg],edx;
         callback_Device_Init(dwArg);
         break;  
      case SYS_DYNAMIC_DEVICE_EXIT:
	     _asm mov [dwArg],edx;
		 callback_Device_Exit(dwArg);
		 break;
      case CREATE_THREAD:
	     _asm mov [dwArg],edi;
		 callback_Create_Thread(dwArg);
		 break;
      case CREATE_VM:
	     _asm mov [dwArg],ebx;
		 callback_Create_VM(dwArg);
		 break;
	  case DESTROY_THREAD:
	     _asm mov [dwArg],edi;
		 callback_Destroy_Thread(dwArg);
		 break;
	  case DESTROY_VM:
	     _asm mov [dwArg],ebx;
		 callback_Destroy_VM(dwArg);
		 break;
	  default: 
	     _asm clc;
		 _asm mov esp, ebp;
		 _asm ret;
	};
// stripped-down VxD epilog
    _asm mov esp, ebp;
	_asm cmp eax,1;
    _asm ret;

}

