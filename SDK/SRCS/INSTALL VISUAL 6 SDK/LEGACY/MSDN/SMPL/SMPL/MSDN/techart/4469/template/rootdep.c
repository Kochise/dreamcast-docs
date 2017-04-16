#include "ntddk.h"
#include "$$SAFE_ROOT$$dep.h"


#ifdef ALLOC_PRAGMA
// all auxiliary routines that are called during initialization should go in here.
#pragma alloc_text(INIT,DriverEntry)
#pragma alloc_text(INIT,CreateDevices)
#endif



NTSTATUS
DriverEntry(
    IN PDRIVER_OBJECT DriverObject,
    IN PUNICODE_STRING RegistryPath
    )
{
 NTSTATUS status;

// TODO: The driver initialization code goes here


// Each driver MUST create at least one device object

status = CreateDevices(DriverObject,RegistryPath);


/***********************************************************************************/
/*                                                                                 */
/*   successful initialization - now fill in the slots for the functions in        */
/*   the Driver object and return.                                                 */
/*   Note that it is perfectly fine to collapse several entry points into the      */
/*   same function that dispatches internally, if you so wish.                     */
/*                                                                                 */
/***********************************************************************************/


$$IF(MACBHASSTARTIO)
        DriverObject->DriverStartIo = $$SAFE_ROOT$$StartIo;
$$ENDIF
$$IF(MACBHASUNLOADROUTINE)
        DriverObject->DriverUnload = $$SAFE_ROOT$$Unload;
$$ENDIF
$$BEGINLOOP(NUM_OPS)
$$IF(OPERATION)
        DriverObject->MajorFunction[IRP_MJ_$$IRPCODE$$] = $$SAFE_ROOT$$$$OPERATION$$;
$$ENDIF
$$ENDLOOP

        status = STATUS_SUCCESS;
    return(status);

}

$$BEGINLOOP(NUM_OPS)
$$IF(OPERATION)
NTSTATUS                
$$SAFE_ROOT$$$$OPERATION$$(
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
    )
{  
 NTSTATUS status;
$$IF(MACBHASSTARTIO)
    Irp->IoStatus.Status = STATUS_PENDING;
// After this point, you can't touch the IRP anymore.
// All hell breaks loose if you dare to
// return a different value than the one in the IRP...
    IoMarkIrpPending(Irp);
    IoStartPacket(
            DeviceObject,
            Irp,
            (PULONG)NULL,
            NULL
            );

    return STATUS_PENDING;
$$ELSE
// This prefix sets up a pointer to the device extension for you
// C specific code - note that DEVICE_EXTENSION must be defined in your .h file
    PDEVICE_EXTENSION deviceExtension;
    deviceExtension = (PDEVICE_EXTENSION) DeviceObject->DeviceExtension;
// TODO: Here add the code that implements the functionality
$$IF(MACBHASIOCTL)
// For the IOCTl function, you can use this code skeleton to obtain the
// IOCtl code...
    PIO_STACK_LOCATION curIRPStack;
    curIRPStack = IoGetCurrentIrpStackLocation(Irp);
    switch (curIRPStack->Parameters.DeviceIoControl.IoControlCode)
     {   case  1: // here handle the IOCTl calls
         break;
         default:
         status = STATUS_IO_DEVICE_ERROR;
     };
$$ENDIF
    Irp->IoStatus.Status = status;
    Irp->IoStatus.Information = 0;

// TODO: Depending on what happens here, either mark Irp pending or complete
// IoMarkIrpPending(Irp);
// IoCompleteRequest(Irp, IO_NO_INCREMENT);
 return(status);
$$ENDIF
}
$$ENDIF
$$ENDLOOP

NTSTATUS
CreateDevices(
    IN PDRIVER_OBJECT DriverObject,
	PUNICODE_STRING RegistryPath
	)
{
 NTSTATUS status;
 UNICODE_STRING usName;   
 UNICODE_STRING usLinkName;
 PDEVICE_OBJECT deviceObject[$$NUMDEVICES$$];

// Ideally, we would like to have a loop like this one in the code. However, 
// the macro processor does not allow dynamic checking of iterators in the
// expansion. You will have to tweak the code by hand...
/*
 for (int i=0; i<$$NUMDEVICES$$; i++)
 {
     status = IoCreateDevice(
                 DriverObject,
                 sizeof(DEVICE_EXTENSION),
                 &<uniNameString>,
                 DEVICE_TYPE_XXX,
                 <0>,
                 <TRUE>,
                 &deviceObject
                 );
};   
*/

// For each device, we have to at least create one device object,
// optionally also create a symbolic link and/or register an
// interrupt handler.

$$BEGINLOOP(NUMDEVICES)
// next device...

$$IF(MACBSUPPLIESNAME)
RtlInitUnicodeString(&usName,L"\\Device\\$$DEVICENAME$$");
$$ELSEIF(MACBCOMPUTESNAME)
// TODO: Here add the code to determine the device's name programatically
$$ENDIF
status = IoCreateDevice(
            DriverObject,
			sizeof(DEVICE_EXTENSION),
$$IF(MACBUNNAMED)
            NULL,
$$ELSE
            &usName,
$$ENDIF
            FILE_DEVICE_UNKNOWN,    // TODO: Adapt this to your type
			0,                      // TODO: U might want to tweak these...
$$IF(MACBEXCLUSIVE)
            TRUE,                  // exclusive use
$$ELSE
            FALSE,                 // not an exclusive device
$$ENDIF
            &deviceObject[$$INDEX$$]    
		    );
if (!NT_SUCCESS(status));          // TODO: Add error handling

$$IF(MACBBUFFERED)
        deviceObject[$$INDEX$$]->Flags |= DO_BUFFERED_IO;
$$ENDIF


$$IF(!MACBLUNNAMED)
// There will be a symbolic link object. Determine how to
// obtain it.
$$IF(MACBSUPPLIESLNAME)
   RtlInitUnicodeString (&usLinkName,L"\\DosDevices\\$$LINKNAME$$");
$$ELSEIF(MACBCOMPUTESNAME)
// TODO: Compute the name for the link and assign it to usLinkName.
$$ENDIF
   status = IoCreateSymbolicLink (&usLinkName,&usName);
   if (!NT_SUCCESS(status));       // TODO: Add error handling
$$ENDIF  //MACBLUNNAMED


$$IF(MACBHASISR)
//  This is only a very crude outline of the steps involved in registering an ISR.
//  You will normally store the returned interrupt object pointer into the 
//  device extension, but there is no requirement to do that.
//  Everything in angel brackets must be supplied by you in the following code.
//  You will probably also want to register one or more DPCs at this point.
/*
{
 ULONG interruptVector;
 KIRQL interruptLevel;
 KAFFINITY affinity;
 interruptVector = HalGetInterruptVector(
                          <InterfaceType>,
                          <BusNumber>,
                          <Interrupt.Level>,
                          <Interrupt.Vector>,
                          &interruptLevel,
                          &affinity
                          );
 status = IoConnectInterrupt(
                 &<InterruptObject>,
                 (PKSERVICE_ROUTINE) $$SAFE_ROOT$$InterruptService,
                 <portDeviceObject>,
                 <KSPIN_LOCK object>,
                 interruptVector,
                 interruptLevel,
                 interruptLevel,
                 <Latched or LevelSensitive>, 
                 <ShareDisposition>,
                 affinity,
                 <FloatingSave>
                 );
};
*/
$$ENDIF


$$ENDLOOP
return (status);

}

$$IF(MACBHASSTARTIO)
VOID
$$SAFE_ROOT$$StartIo(
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
    )
{
// C specific code - note that DEVICE_EXTENSION must be defined in your .h file
    NTSTATUS status;
    PDEVICE_EXTENSION deviceExtension;
    PIO_STACK_LOCATION irpSp = IoGetCurrentIrpStackLocation(Irp);
    deviceExtension = (PDEVICE_EXTENSION) DeviceObject->DeviceExtension;
    switch (irpSp->MajorFunction)
       {
$$IF(MACBHASIOCTL_ALL)
        case IRP_MJ_DEVICE_CONTROL:
// For the IOCTl function, you can use this code skeleton to obtain the
// IOCtl code...
        {
         PIO_STACK_LOCATION curIRPStack;
         curIRPStack = IoGetCurrentIrpStackLocation(Irp);
         switch (curIRPStack->Parameters.DeviceIoControl.IoControlCode)
         {   
		   case  1: // here handle the IOCTl calls
              break;
              default:
              status = STATUS_IO_DEVICE_ERROR;
         };
         Irp->IoStatus.Status = status;
         IoStartNextPacket(DeviceObject,TRUE);
    	 IoCompleteRequest(Irp,0);
		};
        break;
$$ENDIF
$$BEGINLOOP(NUM_OPSNOIOCTL)
$$IF(OPERATION)
        case IRP_MJ_$$IRPCODE$$:
// TODO: Add code for handling $$IRPCODE$$ requests
    	 IoStartNextPacket(DeviceObject,TRUE);
    	 IoCompleteRequest(Irp,0);
         break;
$$ENDIF
$$ENDLOOP
// TODO: Handle the other case here too
        default:;// this shouldn't normally happen.
       };


// end of C Specific code
// TODO: Add the code for queueing requests here

 return;
}
$$ENDIF
$$IF(MACBHASUNLOADROUTINE)
VOID
$$SAFE_ROOT$$Unload(
    IN PDRIVER_OBJECT DriverObject
    )
{
 return;
}
$$ENDIF

void                // There is no entry for this in the DriverObject...
$$SAFE_ROOT$$Cancel(
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
    )
{
// This prefix sets up a pointer to the device extension for you
// C specific code - note that DEVICE_EXTENSION must be defined in your .h file
    PDEVICE_EXTENSION deviceExtension;
    deviceExtension = (PDEVICE_EXTENSION) DeviceObject->DeviceExtension;
// TODO: Here add the code that implements the functionality

    Irp->IoStatus.Status = STATUS_CANCELLED;
    Irp->IoStatus.Information = 0;

 return;
}

$$IF(MACBHASISR)
BOOLEAN
$$SAFE_ROOT$$InterruptService(
    IN PKINTERRUPT Interrupt,
    IN PVOID Context
    )

{
/*
Arguments:

    Interrupt - A pointer to the interrupt object for this interrupt.

    Context - A pointer to the device object.

Return Value:

    Returns TRUE if the interrupt was expected (and therefore processed);
    otherwise, FALSE is returned.
*/
    PDEVICE_EXTENSION deviceExtension;
    PDEVICE_OBJECT deviceObject;
    //
    // Get the device extension.
    //
    deviceObject = (PDEVICE_OBJECT) Context;
    deviceExtension = (PDEVICE_EXTENSION) deviceObject->DeviceExtension;

    //TODO: Here add the ISR functionality
   //
  
   // After finishing the critical code, you should queue a DPC to request 
   // post-processing of the interrupt when it is convenient.
   /*   
            KeInsertQueueDpc(
                &deviceExtension->IsrDpc,
                deviceObject->CurrentIrp,
                NULL
                );
    */
  
    return(TRUE);
}
$$ENDIF  
