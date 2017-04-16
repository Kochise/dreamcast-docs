	Title callback.asm
;==========================================================================
;
;  Ruediger Asche, Microsoft Developer Network Group.
;  This is the stub entry for the callback device id.
;
;--------------------------------------------------------------------------

	.386p



;==========================================================================
; INCLUDES
;--------------------------------------------------------------------------
	.xlist
	include vmm.inc
	include debug.inc
	.list

;==========================================================================
; Declare Virtual Device
;--------------------------------------------------------------------------

callback_DYNAMIC equ 1

EXTERN _callback_Control:FAR

Declare_Virtual_Device callback, 1, 0, _callback_Control,,,


VxD_LOCKED_CODE_SEG

;==========================================================================
;
; callback_Control: dispatch control calls.
;
;--------------------------------------------------------------------------
;BeginProc callback_Control

; Note that we push the appropriate argument on the stack upon each
; notification. This way, it is up to the handler function to sort out the
; information it needs.

;	Control_Dispatch Sys_Dynamic_Device_Init, callback_Device_Init, sCall, <edx>
;    Control_Dispatch Sys_Dynamic_Device_Exit, callback_Device_Exit, sCall, <edx>
;	Control_Dispatch Create_Thread, callback_Create_Thread,sCall, <edi>
;	Control_Dispatch Create_VM, callback_Create_VM,sCall, <ebx>
;	Control_Dispatch Destroy_Thread, callback_Destroy_Thread,sCall, <edi>
;	Control_Dispatch Destroy_VM, callback_Destroy_VM,sCall, <ebx>
;	clc
;	ret

;EndProc callback_Control


VXD_LOCKED_CODE_ENDS


	END


