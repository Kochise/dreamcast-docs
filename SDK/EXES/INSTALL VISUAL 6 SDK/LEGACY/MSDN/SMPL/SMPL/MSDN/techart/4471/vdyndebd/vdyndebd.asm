; VDYNDEBD, simple dynamically loadable VxD for Microsoft (R)
; Windows(R) 95 that supplies external debugger commands

.386p

INCLUDE Vmm.Inc
INCLUDE Debug.Inc

; virtual device declaration
Declare_Virtual_Device VDYNDEBD, 4, 0, VdyndebD_Control, Undefined_Device_ID

VxD_LOCKED_CODE_SEG
    ; control procedure
    BeginProc VdyndebD_Control
        Control_Dispatch Debug_Query, VdyndebD_DebugQuery
        Control_Dispatch SYS_DYNAMIC_DEVICE_INIT, VdyndebD_Dynamic_Init
        Control_Dispatch SYS_DYNAMIC_DEVICE_EXIT, VdyndebD_Dynamic_Exit
        Control_Dispatch W32_DEVICEIOCONTROL, VdyndebD_DeviceIOControl
        clc
        ret
    EndProc VdyndebD_Control

    ; Debug_Query message handler
    BeginProc VdyndebD_DebugQuery
        ; send menu to debug terminal
        Trace_Out " "
        Trace_Out "*** VDYNDEBD DEBUG INFORMATON ***"
        Trace_Out " "
        Trace_Out "[1] Option 1"
        Trace_Out "[2] Option 2"
        Trace_Out "[3] Option 3"
        Trace_Out " "
        Trace_Out "Please select an option: ", nocrlf

        ; read response from debug terminal
        VMMcall In_Debug_Chr
        
        ; jump to selected label
        Trace_Out " "
        Trace_Out " "
        jz   short DebugDone
        cmp  al, '1'
        jz   short DebugOption1
        cmp  al, '2'
        jz   short DebugOption2
        cmp  al, '3'
        jz   short DebugOption3
        Trace_Out "Invalid VDYNDEBD debug option"
        Trace_Out " "

      DebugDone:
        clc
        ret

      DebugOption1:
        Trace_Out "VDYNDEBD debug option 1"
        Trace_Out " "
        jmp  short DebugDone

      DebugOption2:
        Trace_Out "VDYNDEBD debug option 2"
        Trace_Out " "
        jmp  short DebugDone

      DebugOption3:
        Trace_Out "VDYNDEBD debug option 3"
        Trace_Out " "
        jmp  short DebugDone
    EndProc VdyndebD_DebugQuery

    ; W32_DEVICEIOCONTROL message handler
    BeginProc VdyndebD_DeviceIOControl
        ; load DIOCParams.dwIoControl into EAX
        mov  eax, [esi+12]
        
        ; jump corresponding to the dwIOControl member
        cmp  eax, DIOC_OPEN
        jz   short DeviceIOControlOpen
        cmp  eax, DIOC_CLOSEHANDLE
        jz   short DeviceIOControlCloseHandle

        ; output message, set return value to ERROR_NOT_SUPPORTED (50)
        Trace_Out "VDYNDEBD: Device IO Control Code 0x#eax is not supported"
        mov  eax, 50
      
      DeviceIOControlDone:
        clc
        ret

      DeviceIOControlOpen:
        ; must return 0 in EAX
        xor  eax, eax
        jmp  short DeviceIOControlDone

      DeviceIOControlCloseHandle:
        ; must return VXD_SUCCESS in EAX
        mov  eax, VXD_SUCCESS
        jmp  short DeviceIOControlDone
    EndProc VdyndebD_DeviceIOControl

    ; SYS_DYNAMIC_DEVICE_EXIT message handler
    BeginProc VdyndebD_Dynamic_Exit
        mov  eax, 1
        clc
        ret
    EndProc VdyndebD_Dynamic_Exit
VxD_LOCKED_CODE_ENDS

VxD_ICODE_SEG
    ; SYS_DYNAMIC_DEVICE_INIT message handler
    BeginProc VdyndebD_Dynamic_Init
        mov  eax, 1
        clc
        ret
    EndProc VdyndebD_Dynamic_Init
VxD_ICODE_ENDS
    END
