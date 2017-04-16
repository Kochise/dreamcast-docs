         .386p
         include vmm.inc
         include debug.inc

Declare_Virtual_Device TELEPATH, 1, 0, TELEPATH_Control, \
                       Undefined_Device_ID, Undefined_Init_Order

Begin_Control_Dispatch TELEPATH

    Control_Dispatch Sys_Dynamic_Device_Init, _OnSysDynamicDeviceInit, cCall
    Control_Dispatch Sys_Dynamic_Device_Exit, _OnSysDynamicDeviceExit, cCall
    Control_Dispatch PNP_New_Devnode, _OnPnpNewDevnode, cCall, <ebx, edx>

End_Control_Dispatch TELEPATH

         end
