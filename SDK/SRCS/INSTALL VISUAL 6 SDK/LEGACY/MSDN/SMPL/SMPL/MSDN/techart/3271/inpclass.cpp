
/*++

Copyright (c) 1990, 1991, 1992, 1993  Microsoft Corporation

Module Name:

    inpclass.cpp

Abstract:

    Generic input class driver.

Environment:

    Kernel mode only.

Notes:

    NOTES:  (Future/outstanding issues)

    - Powerfail not implemented.

    - Consolidate duplicate code, where possible and appropriate.

    - Unload not implemented.  We don't want to allow this driver
      to unload.

Revision History:

RAc, January 1995: Rewrote for C++

--*/



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

extern "C"
{

NTSTATUS
DriverEntry(
    IN PDRIVER_OBJECT DriverObject,
    IN PUNICODE_STRING RegistryPath
    );

VOID
InputClassCancel(
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
    );

NTSTATUS
InputClassCleanup(
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
    );

NTSTATUS
InputClassDeviceControl(
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
    );

NTSTATUS
InputClassFlush(
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
    );

NTSTATUS
InputClassOpenClose(
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
    );

NTSTATUS
InputClassRead(
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
    );

VOID
InputClassServiceCallback(
    IN PDEVICE_OBJECT DeviceObject,
    IN PINPUT_DATA InputDataStart,
    IN PINPUT_DATA InputDataEnd,
    IN OUT PULONG InputDataConsumed
    );

VOID
InputClassStartIo(
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
    );

VOID
InputClassUnload(
    IN PDRIVER_OBJECT DriverObject
    );

BOOLEAN
InputCancelRequest(
    IN PVOID Context
    );

NTSTATUS
InputConfiguration(
    IN CGlobalInputClassData *DeviceExtension,
    IN CUString *RegistryPath,
    IN CUString *DeviceName
    );


NTSTATUS
InputConnectToPort(
    IN PDEVICE_OBJECT ClassDeviceObject,
    IN PUNICODE_STRING FullPortName,
    IN ULONG PortIndex
    );

NTSTATUS
InputCreateClassObject(
    IN PDRIVER_OBJECT DriverObject,
    IN CGlobalInputClassData *TmpDeviceExtension,
    IN PUNICODE_STRING RegistryPath,
    IN PUNICODE_STRING FullDeviceName,
    IN PUNICODE_STRING BaseDeviceName,
    IN PDEVICE_OBJECT *ClassDeviceObject
    );

#if DBG

VOID
InputDebugPrint(
    ULONG DebugPrintLevel,
    PCCHAR DebugMessage,
    ...
    );

//
// Declare the global debug flag for this driver.
//

ULONG InputDebug = 0;
#define InputPrint(x) InputDebugPrint x
#else
#define InputPrint(x)
#endif
NTSTATUS 
InputDeviceMapQueryCallback(
    IN PWSTR ValueName,
    IN ULONG ValueType,
    IN PVOID ValueData,
    IN ULONG ValueLength,
    IN PVOID Context,
    IN PVOID EntryContext
    );

NTSTATUS
InputEnableDisablePort(
    IN PDEVICE_OBJECT DeviceObject,
    IN BOOLEAN EnableFlag,
    IN ULONG PortIndex
    );
NTSTATUS
InputSendConnectRequest(
    IN PDEVICE_OBJECT DeviceObject,
    IN PVOID ServiceCallback,
    IN ULONG PortIndex
    );

//
// Use the alloc_text pragma to specify the driver initialization routines
// (they can be paged out).
//

#ifdef ALLOC_PRAGMA
#pragma alloc_text(INIT,DriverEntry)
#pragma alloc_text(INIT,InputConfiguration)
#pragma alloc_text(INIT,InputCreateClassObject)
#pragma alloc_text(INIT,InputDeviceMapQueryCallback)
#pragma alloc_text(INIT,InputConnectToPort)
#pragma alloc_text(INIT,InputSendConnectRequest)
#endif

} // extern "C"


NTSTATUS
DriverEntry(
    IN PDRIVER_OBJECT DriverObject,
    IN PUNICODE_STRING RegistryPath
    )

/*++

Routine Description:

    This routine initializes the Input class driver.

Arguments:

    DriverObject - Pointer to driver object created by system.

    RegistryPath - Pointer to the Unicode name of the registry path
        for this driver.

Return Value:

    The function value is the final status from the initialization operation.

--*/

{
    CGlobalInputClassData *cGlobalData;
    PDEVICE_OBJECT classDeviceObject = NULL;
    CInputClassDeviceExt *cExtAllocated;
    NTSTATUS status;
    ULONG i;
    ULONG portConnectionSuccessful;
// initialize a whole bunch of literal strings here for later use 
 #define NAME_MAX 256
    CUString baseClassName(NAME_MAX);
    CUString registryPath(RegistryPath->Length + sizeof(UNICODE_NULL));
    CUString portString(L"Port");
    CUString deviceString(L"\\Device\\");
    cGlobalData = new (NonPagedPool) CGlobalInputClassData();
    if ((!OK_ALLOCATED(&baseClassName))  // error logging should be done implicitly... 
     || (!OK_ALLOCATED(&registryPath))
     || (!OK_ALLOCATED(&deviceString))
     || (!OK_ALLOCATED(&portString))
     || (!cGlobalData))
    return STATUS_INSUFFICIENT_RESOURCES;

    registryPath.Append(RegistryPath);

    // this fills in baseClassName from the registry
    status = InputConfiguration(cGlobalData,&registryPath,&baseClassName);
	if (!NT_SUCCESS(status)) 
	 { 
	   delete cGlobalData;
	   return status;
	 };
	int iStrLength=deviceString.GetLength()+baseClassName.GetLength()+sizeof(L"99");
    // we assume here that no more than 100 ports are supported... remove this limit
	// later on
    CUString fullClassName(iStrLength);
    CUString fullPortName(iStrLength);
    CUString basePortName(baseClassName.GetString());
	
	if ((!OK_ALLOCATED(&fullClassName))
     || (!OK_ALLOCATED(&basePortName))
     || (!OK_ALLOCATED(&fullPortName))
     || (!NT_SUCCESS(status)))
    {
     delete(cGlobalData); 
     return STATUS_INSUFFICIENT_RESOURCES;
	};

    fullClassName.Append(&deviceString.m_String);
    fullClassName.Append(&baseClassName.m_String);

    //
    // Set up the base device name for the associated port device.
    // It is the same as the base class name, with "Class" replaced
    // by "Port".
    //
    // this should be taken caren of by a member function...


    basePortName.SetLength(basePortName.GetLength() - sizeof(L"Class")+sizeof(UNICODE_NULL));
	basePortName.Append(&portString.m_String);
    fullPortName.Append(&deviceString.m_String);
    fullPortName.Append(&basePortName.m_String); 
 
 
    ULONG uniqueErrorValue;
    USHORT dumpCount = 0;
    NTSTATUS errorCode = STATUS_SUCCESS;

#define DUMP_COUNT 4
    ULONG dumpData[DUMP_COUNT];

    InputPrint((1,"\n\nINPUTCLASS-InputClassInitialize: enter\n"));

    //
    // Determine how many ports this class driver is to service.
    //
/*
    This section reads the DEVICEMAP portion of the registry to determine
    how many ports the class driver is to service.  Depending on the
    value of DeviceExtension->ConnectOneClassToOnePort, the class driver 
    will eventually create one device object per port device serviced, or
    one class device object that connects to multiple port device objects. 
    
    Assumptions:

        1.  If the base device name for the class driver is "PointerClass",
                                                                    ^^^^^
            then the port drivers it can service are found under the
            "PointerPort" subkey in the DEVICEMAP portion of the registry.
                    ^^^^

        2.  The port device objects are created with suffixes in strictly
            ascending order, starting with suffix 0.  E.g., 
            \Device\PointerPort0 indicates the first pointer port device, 
            \Device\PointerPort1 the second, and so on.  There are no gaps 
            in the list.

        3.  If ConnectOneClassToOnePort is non-zero, there is a 1:1 
            correspondence between class device objects and port device 
            objects.  I.e., \Device\PointerClass0 will connect to 
            \Device\PointerPort0, \Device\PointerClass1 to
            \Device\PointerPort1, and so on.

        4.  If ConnectOneClassToOnePort is zero, there is a 1:many
            correspondence between class device objects and port device 
            objects.  I.e., \Device\PointerClass0 will connect to 
            \Device\PointerPort0, and \Device\PointerPort1, and so on.


    Note that for Product 1, the Raw Input Thread (Windows USER) will
    only deign to open and read from one pointing device.  Hence, it is 
    safe to make simplifying assumptions because the driver is basically 
    providing  much more functionality than the RIT will use.
*/            



     i = 0;
 	 CRegistry cQueryPorts(1);
	 status = STATUS_INSUFFICIENT_RESOURCES;
     if (OK_ALLOCATED(&cQueryPorts))
	 {
	 cQueryPorts.QueryWithCallback(InputDeviceMapQueryCallback,RTL_REGISTRY_DEVICEMAP,
	                              basePortName.GetString(),(PVOID)&i,
								  NULL);
	 status = cQueryPorts.m_status;
        if (!NT_SUCCESS(status)) {
            InputPrint((
                1,
                "INPUTCLASS-InputDeterminePortsServiced: RtlQueryRegistryValues failed with 0x%x\n",
                status
                ));
        };
	  };
   


    if (NT_SUCCESS(status)) 
    {
     if (i < cGlobalData->MaximumPortsServiced)
            cGlobalData->MaximumPortsServiced = i;
    }

    status = STATUS_SUCCESS;

   if (!cGlobalData->InitializePortDeviceObjectList())
   {
        //
        // Could not allocate memory for the port device object pointers.
        //

        InputPrint((
            1,
            "INPUTCLASS-InputClassInitialize: Could not allocate PortDeviceObjectList for %ws\n",
            fullClassName.GetString()
            ));

        status = STATUS_INSUFFICIENT_RESOURCES;
        errorCode = INPUTCLASS_INSUFFICIENT_RESOURCES;
        uniqueErrorValue = INPUT_ERROR_VALUE_BASE + 10;
        dumpData[0] = (ULONG) (sizeof(PDEVICE_OBJECT) * cGlobalData->MaximumPortsServiced);
        dumpData[1] = (ULONG) cGlobalData->MaximumPortsServiced;
        dumpCount = 2;

        goto InputClassInitializeExit;
    }
  
    //
    // Set up the class device object(s) to handle the associated 
    // port devices.
    //

    portConnectionSuccessful = 0;

    CUString *cuSuffix;

    for (i = 0; i < cGlobalData->MaximumPortsServiced; i++) 
    {   cuSuffix = new(PagedPool) CUString(i,10);
    
        //
        // Append the suffix to the device object name string.  E.g., turn
        // \Device\PointerClass into \Device\PointerClass0.  Then attempt
        // to create the device object.  If the device object already
        // exists increment the suffix and try again.
        //
        if (!OK_ALLOCATED(cuSuffix))
		{
         errorCode = STATUS_INSUFFICIENT_RESOURCES;
         dumpCount = 0;
         break;
		};

		fullClassName.Append(&cuSuffix->m_String);
		fullPortName.Append(&cuSuffix->m_String);
 
        //
        // Create the class device object.
        //

        if (cGlobalData->ConnectOneClassToOnePort 
                || (classDeviceObject == NULL)) {
            classDeviceObject = NULL;
            status = InputCreateClassObject(
                         DriverObject,
                         cGlobalData,
                         &registryPath.m_String,
                         &fullClassName.m_String,
                         &baseClassName.m_String,
                         &classDeviceObject
                         );
        }

        //
        // Connect to the port device.
        //

        if (NT_SUCCESS(status)) {
            status = InputConnectToPort(
                         classDeviceObject,
                         &fullPortName.m_String,
                         i
                         );
        }

        if (NT_SUCCESS(status)) {

            portConnectionSuccessful += 1;

            if (cGlobalData->ConnectOneClassToOnePort 
                    || (portConnectionSuccessful == 1)) {

                //
                // Load the device map information into the registry so 
                // that setup can determine which Input class driver is active.  
                //
            
            CRegistry crWriter(1);
			if (!crWriter.WriteString(RTL_REGISTRY_DEVICEMAP,&registryPath,&baseClassName,&fullClassName))
			 {
                
                    InputPrint((
                        1, 
                        "INPUTCLASS-InputClassInitialize: Could not store %ws in DeviceMap\n",
                        fullClassName.GetString()
                            ));
                
                
                    //
                    // Stop making connections, and log an error.
                    //
    
                    errorCode = INPUTCLASS_NO_DEVICEMAP_CREATED;
                    uniqueErrorValue = INPUT_ERROR_VALUE_BASE + 14;
                    dumpCount = 0;

                    //
                    // N.B. 'break' should cause execution to
                    // go to KeyboardClassInitializeExit (otherwise
                    // do an explicit 'goto').
                    //

                    break;
            
                } else {
                
                    InputPrint((
                        1, 
                        "INPUTCLASS-InputClassInitialize: Stored %ws in DeviceMap\n",
                        fullClassName.GetString()
                        ));
                }
            }

            //
            // Try the next one.
            //

            fullClassName.SetLength(fullClassName.GetLength() - cuSuffix->GetLength());
            fullPortName.SetLength(fullPortName.GetLength() - cuSuffix->GetLength());

        } else if (cGlobalData->ConnectOneClassToOnePort) {

            //
            // Stop doing 1:1 class-port connections if there is
            // a failure.
            //
            // Note that if we are doing 1:many class-port connections
            // and we encounter an error, we continue to try to connect 
            // to port devices. 
            //

            break;
        }
	  delete cuSuffix;

    }

    if (!portConnectionSuccessful) {

        //
        // The class driver was unable to connect to any port devices.
        // Log a warning message.
        //

        errorCode = INPUTCLASS_NO_PORT_DEVICE_OBJECT;
        uniqueErrorValue = INPUT_ERROR_VALUE_BASE + 18;

    }

InputClassInitializeExit:

    if (errorCode != STATUS_SUCCESS) {

        //
        // The initialization failed in some way.  Log an error.
        //
	delete (new (PagedPool) CErrorLogEntry((classDeviceObject == NULL) ? 
                    (PVOID) DriverObject : (PVOID) classDeviceObject,errorCode,dumpCount,
					                          INPUT_ERROR_VALUE_BASE+10,status,dumpData,0));
     }

 
    if ((cGlobalData->ConnectOneClassToOnePort 
             && (!NT_SUCCESS(status))) ||
         !portConnectionSuccessful) {

        //
        // Clean up leftover resources.  If we're doing 1:1 class-port
        // connections, then we may have created a class device object
        // for which the connect failed.  If we're doing 1:many
        // connections, we may have created a class device object but
        // failed to make ANY connections.  In either case, we
        // free the ring buffer and delete the class device object.
        //

        if (classDeviceObject) {
		    cExtAllocated =
                (CInputClassDeviceExt *) classDeviceObject->DeviceExtension;
            if (cExtAllocated) delete (cExtAllocated);
            IoDeleteDevice(classDeviceObject);
        }
    }

    //
    // If we successfully connected to at least one pointer port device,
    // this driver's initialization was successful.
    //

    if (portConnectionSuccessful) {

        //
        // Set up the device driver entry points.
        //

        DriverObject->DriverStartIo = InputClassStartIo;
        DriverObject->MajorFunction[IRP_MJ_CREATE] = InputClassOpenClose;
        DriverObject->MajorFunction[IRP_MJ_CLOSE]  = InputClassOpenClose;
        DriverObject->MajorFunction[IRP_MJ_READ]   = InputClassRead;
        DriverObject->MajorFunction[IRP_MJ_FLUSH_BUFFERS]  =
                                                 InputClassFlush;
        DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] =
                                                 InputClassDeviceControl;
        DriverObject->MajorFunction[IRP_MJ_CLEANUP] = InputClassCleanup;

        //
        // NOTE: Don't allow this driver to unload.  Otherwise, we would set
        // DriverObject->DriverUnload = InputClassUnload.
        //

        status = STATUS_SUCCESS;
    }

    InputPrint((1,"INPUTCLASS-InputClassInitialize: exit\n"));

    return(status);

}

VOID
InputClassCancel(
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
    )

/*++

Routine Description:

    This routine is the class cancellation routine.  It is
    called from the I/O system when a request is cancelled.  Read requests
    are currently the only cancellable requests.

    N.B.  The cancel spinlock is already held upon entry to this routine.

Arguments:

    DeviceObject - Pointer to class device object.

    Irp - Pointer to the request packet to be cancelled.

Return Value:

    None.

--*/

{
    CInputClassDeviceExt *cExtension;
    KIRQL currentIrql;
    KIRQL cancelIrql;

    InputPrint((2,"INPUTCLASS-InputClassCancel: enter\n"));

    cExtension = (CInputClassDeviceExt *) DeviceObject->DeviceExtension;

    //
    // Release the cancel spinlock and grab the Input class spinlock (it
    // protects the RequestIsPending flag).
    //

    IoReleaseCancelSpinLock(Irp->CancelIrql);
    KeAcquireSpinLock(&cExtension->SpinLock, &currentIrql);
    
    if ((cExtension->RequestIsPending) 
        && (Irp == DeviceObject->CurrentIrp)) {

        //
        // The current request is being cancelled.  Set the CurrentIrp to
        // null, clear the RequestIsPending flag, and release the Input class 
        // spinlock before starting the next packet.
        //

        DeviceObject->CurrentIrp = NULL;
        cExtension->RequestIsPending = FALSE;
        KeReleaseSpinLock(&cExtension->SpinLock, currentIrql);
        IoStartNextPacket(DeviceObject, TRUE);
    } else {

        //
        // Cancel a request in the device queue.  Reacquire the cancel
        // spinlock, remove the request from the queue, and release the 
        // cancel spinlock.  Release the Input class spinlock.
        //

        IoAcquireCancelSpinLock(&cancelIrql);
        if (TRUE != KeRemoveEntryDeviceQueue(
                        &DeviceObject->DeviceQueue,
                        &Irp->Tail.Overlay.DeviceQueueEntry
                        )) {
            InputPrint((
                1, 
                "INPUTCLASS-InputClassCancel: Irp 0x%x not in device queue?!?\n",
                Irp
                ));
        }
        IoReleaseCancelSpinLock(cancelIrql);
        KeReleaseSpinLock(&cExtension->SpinLock, currentIrql);
    }

    //
    // Complete the request with STATUS_CANCELLED.
    //

    Irp->IoStatus.Status = STATUS_CANCELLED;
    Irp->IoStatus.Information = 0;
    IoCompleteRequest (Irp, IO_INPUT_INCREMENT);

    InputPrint((2,"INPUTCLASS-InputClassCancel: exit\n"));

    return;
}

NTSTATUS
InputClassCleanup(
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
    )

/*++

Routine Description:

    This routine is the dispatch routine for cleanup requests.
    All requests queued to the Input class device (on behalf of
    the thread for whom the cleanup request was generated) are 
    completed with STATUS_CANCELLED.

Arguments:

    DeviceObject - Pointer to class device object.

    Irp - Pointer to the request packet.

Return Value:

    Status is returned.

--*/

{
    KIRQL spinlockIrql;
    KIRQL cancelIrql;
    CInputClassDeviceExt *cExtension;
    PKDEVICE_QUEUE_ENTRY packet;
    PIRP  currentIrp = NULL;
    PIO_STACK_LOCATION irpSp;

    InputPrint((2,"INPUTCLASS-InputClassCleanup: enter\n"));

    cExtension = (CInputClassDeviceExt *) DeviceObject->DeviceExtension;

    //
    // Acquire the Input class spinlock and the cancel spinlock.
    //

    KeAcquireSpinLock(&cExtension->SpinLock, &spinlockIrql);
    IoAcquireCancelSpinLock(&cancelIrql);

    //
    // Get a pointer to the current stack location for this request.  
    //

    irpSp = IoGetCurrentIrpStackLocation(Irp);

    //
    // If the file object's FsContext is non-null, then the cleanup 
    // request is being executed by the trusted subsystem.  Since the 
    // trusted subsystem is the only one with sufficient privilege to make 
    // Read requests to the driver, and since only Read requests get queued 
    // to the device queue, a cleanup request from the trusted subsystem is 
    // handled by cancelling all queued requests.
    // 
    // If the FsContext is null, there is no cleanup work to perform
    // (only read requests can be cancelled).
    // 
    // NOTE:  If this driver is to allow more than one trusted subsystem 
    //        to make read requests to the same device object some day in
    //        the future, then there needs to be a mechanism that
    //        allows Cleanup to remove only those queued requests that
    //        were made by threads using the same FileObject as the
    //        file object in the Cleanup request.
    //

    if (irpSp->FileObject->FsContext) {

        //
        // Indicate that the cleanup routine has been called (StartIo cares
        // about this).
        //

        cExtension->CleanupWasInitiated = TRUE;

        //
        // Complete all requests queued by this thread with STATUS_CANCELLED.
        // Start with the real CurrentIrp, and run down the list of requests 
        // in the device queue.  Be sure to set the real CurrentIrp to NULL 
        // and the RequestIsPending flag to FALSE, so that the class
        // service callback routine won't attempt to complete CurrentIrp.  
        // Note that we can really only trust CurrentIrp when RequestIsPending.
        //

        currentIrp = DeviceObject->CurrentIrp;
        DeviceObject->CurrentIrp = NULL;
        cExtension->RequestIsPending = FALSE;
    
        while (currentIrp != NULL) {
    
            //
            // Remove the CurrentIrp from the cancellable state.
            //
            //
    
            IoSetCancelRoutine(currentIrp, NULL);
    
            //
            // Set Status to CANCELLED, release the spinlocks,
            // and complete the request.  Note that the IRQL is reset to
            // DISPATCH_LEVEL when we release the spinlocks.
            //
    
            currentIrp->IoStatus.Status = STATUS_CANCELLED;
            currentIrp->IoStatus.Information = 0;
    
            IoReleaseCancelSpinLock(cancelIrql);
            KeReleaseSpinLock(&cExtension->SpinLock, spinlockIrql);
            IoCompleteRequest(currentIrp, IO_INPUT_INCREMENT);
    
            //
            // Reacquire the spinlocks.
            //
    
            KeAcquireSpinLock(&cExtension->SpinLock, &spinlockIrql);
            IoAcquireCancelSpinLock(&cancelIrql);
    
            //
            // Dequeue the next packet (IRP) from the device work queue.
            //
    
            packet = KeRemoveDeviceQueue(&DeviceObject->DeviceQueue);
            if (packet != NULL) {
                currentIrp =
                    CONTAINING_RECORD(packet, IRP, Tail.Overlay.DeviceQueueEntry);
            } else {
                currentIrp = (PIRP) NULL;
            }
    
        } // end while
    }

    //
    // Release the spinlocks and lower IRQL.
    //

    IoReleaseCancelSpinLock(cancelIrql);
    KeReleaseSpinLock(&cExtension->SpinLock, spinlockIrql);

    //
    // Complete the cleanup request with STATUS_SUCCESS.
    //

    Irp->IoStatus.Status = STATUS_SUCCESS;
    Irp->IoStatus.Information = 0;
    IoCompleteRequest (Irp, IO_NO_INCREMENT);

    InputPrint((2,"INPUTCLASS-InputClassCleanup: exit\n"));

    return(STATUS_SUCCESS);

}

NTSTATUS
InputClassDeviceControl(
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
    )

/*++

Routine Description:

    This routine is the dispatch routine for device control requests.
    All device control subfunctions are passed, asynchronously, to the 
    connected port driver for processing and completion.

Arguments:

    DeviceObject - Pointer to class device object.

    Irp - Pointer to the request packet.

Return Value:

    Status is returned.

--*/

{
    PIO_STACK_LOCATION irpSp;
    PIO_STACK_LOCATION nextSp;
    CInputClassDeviceExt *cExtension;
    NTSTATUS status = STATUS_SUCCESS;
    ULONG unitId;

    InputPrint((2,"INPUTCLASS-InputClassDeviceControl: enter\n"));

    //
    // Get a pointer to the device extension.
    //

    cExtension = (CInputClassDeviceExt *) DeviceObject->DeviceExtension;

    //
    // Get a pointer to the current parameters for this request.  The
    // information is contained in the current stack location.
    //

    irpSp = IoGetCurrentIrpStackLocation(Irp);

    //
    // Check for adequate input buffer length.  The input buffer
    // should, at a minimum, contain the unit ID specifying one of
    // the connected port devices.  If there is no input buffer (i.e.,
    // the input buffer length is zero), then we assume the unit ID 
    // is zero (for backwards compatibility).
    //

    if (irpSp->Parameters.DeviceIoControl.InputBufferLength == 0) {
        unitId = 0;
    } else if (irpSp->Parameters.DeviceIoControl.InputBufferLength <
                  sizeof(INPUT_UNIT_ID_PARAMETER)) {
        status = STATUS_BUFFER_TOO_SMALL;
        
    } else {
        unitId = ((PINPUT_UNIT_ID_PARAMETER)
                     Irp->AssociatedIrp.SystemBuffer)->UnitId;
        if (unitId >= cExtension->cData->MaximumPortsServiced) {
            status = STATUS_INVALID_PARAMETER; 
        }
    }

    if (NT_SUCCESS(status)) {

        //
        // Pass the device control request on to the port driver,
        // asynchronously.  Get the next IRP stack location and copy the 
        // input parameters to the next stack location.  Change the major 
        // function to internal device control.
        //
    
        nextSp = IoGetNextIrpStackLocation(Irp);
        ASSERT(nextSp != NULL);
        nextSp->Parameters.DeviceIoControl = 
            irpSp->Parameters.DeviceIoControl;
        nextSp->MajorFunction = IRP_MJ_INTERNAL_DEVICE_CONTROL;
    
        //
        // Mark the packet pending.
        //
    
        IoMarkIrpPending(Irp);
    
        //
        // Pass the IRP on to the connected port device (specified by 
        // the unit ID).  The port device driver will process the request.
        //
    
        status = IoCallDriver(
                     cExtension->cData->PortDeviceObjectList[unitId], 
                     Irp
                     );
    } else {

        //
        // Complete the request.
        //

        Irp->IoStatus.Status = status;
        Irp->IoStatus.Information = 0;
        IoCompleteRequest(Irp, IO_NO_INCREMENT);
    } 

    InputPrint((2,"INPUTCLASS-InputClassDeviceControl: exit\n"));

    return(status);

}

NTSTATUS
InputClassFlush(
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
    )

/*++

Routine Description:

    This routine is the dispatch routine for flush requests.  The class
    input data queue is reinitialized.

Arguments:

    DeviceObject - Pointer to class device object.

    Irp - Pointer to the request packet.

Return Value:

    Status is returned.

--*/

{
    CInputClassDeviceExt *cExtension;
    NTSTATUS status = STATUS_SUCCESS;

    InputPrint((2,"INPUTCLASS-InputClassFlush: enter\n"));

    //
    // Get a pointer to the device extension.
    //

    cExtension = (CInputClassDeviceExt *) DeviceObject->DeviceExtension;
    //
    // Initialize Input class input data queue.
    //

    cExtension->FlushDataQueue();

    //
    // Complete the request and return status.
    //

    Irp->IoStatus.Status = status;
    Irp->IoStatus.Information = 0;
    IoCompleteRequest(Irp, IO_NO_INCREMENT);

    InputPrint((2,"INPUTCLASS-InputClassFlush: exit\n"));

    return(status);

} // end InputClassFlush

NTSTATUS
InputClassOpenClose(
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
    )

/*++

Routine Description:

    This routine is the dispatch routine for create/open and close requests.
    Open/close requests are completed here.

Arguments:

    DeviceObject - Pointer to class device object.

    Irp - Pointer to the request packet.

Return Value:

    Status is returned.

--*/

{
    PIO_STACK_LOCATION irpSp;
    CInputClassDeviceExt *cExtension;
    KIRQL oldIrql;
    BOOLEAN enableFlag = FALSE;
    NTSTATUS status = STATUS_SUCCESS;
    BOOLEAN SomeEnableDisableSucceeded = FALSE;
    ULONG i;

    InputPrint((2,"INPUTCLASS-InputClassOpenClose: enter\n"));

    //
    // Get a pointer to the device extension.
    //


    cExtension = (CInputClassDeviceExt *) DeviceObject->DeviceExtension;

    //
    // Get a pointer to the current parameters for this request.  The
    // information is contained in the current stack location.
    //

    irpSp = IoGetCurrentIrpStackLocation(Irp);

    //
    // Case on the function that is being performed by the requestor.
    //

    switch (irpSp->MajorFunction) {

        //
        // For the create/open operation, send a Input_ENABLE internal 
        // device control request to the port driver to enable interrupts.
        //

        case IRP_MJ_CREATE:

            //
            // First, if the requestor is the trusted subsystem (the single
            // reader), reset the the cleanup indicator and set the file
            // object's FsContext to non-null (InputClassRead uses
            // FsContext to determine if the requestor has sufficient
            // privilege to perform the read operation).
            //

            if (SeSinglePrivilegeCheck(RtlConvertLongToLargeInteger(
                                                 SE_TCB_PRIVILEGE),
                                                 Irp->RequestorMode 
                                                 )) {

                KeAcquireSpinLock(&cExtension->SpinLock, &oldIrql);
                cExtension->CleanupWasInitiated = FALSE;
                irpSp->FileObject->FsContext = (PVOID) 1;
                KeReleaseSpinLock(&cExtension->SpinLock, oldIrql);
            }

            enableFlag = TRUE;

            break;

        //
        // For the close operation, send a Input_DISABLE internal device
        // control request to the port driver to disable interrupts.
        //

        case IRP_MJ_CLOSE:

            break;
    }

    //
    // Enable/disable interrupts via port driver.
    //

    for (i = 0; i < cExtension->cData->MaximumPortsServiced; i++) {

        status = InputEnableDisablePort(DeviceObject, enableFlag, i);

        if (status != STATUS_SUCCESS) {

            InputPrint((
                0,
                "INPUTCLASS-InputClassOpenClose: Could not enable/disable interrupts for port device object @ 0x%x\n",
                cExtension->cData->PortDeviceObjectList[i]
                ));

            //
            // Log an error.
            //
 	delete (new (PagedPool) 
 	        CErrorLogEntry(DeviceObject,
 	                       enableFlag? INPUTCLASS_PORT_INTERRUPTS_NOT_ENABLED:
                                       INPUTCLASS_PORT_INTERRUPTS_NOT_DISABLED,
                           0,
					       INPUT_ERROR_VALUE_BASE+120,
					       status,
					       (ULONG *)0,
					       irpSp->MajorFunction  // to go into MajorFunctionCode member
					       ));
 
   
        } else {
            SomeEnableDisableSucceeded = TRUE;
        }
    }

    //
    // Complete the request and return status.
    //
    // NOTE: We complete the request successfully if any one of the
    //       connected port devices successfully handled the request.
    //       The RIT only knows about one pointing device.
    //

    if (SomeEnableDisableSucceeded) {
        status = STATUS_SUCCESS;
    }

    Irp->IoStatus.Status = status;
    Irp->IoStatus.Information = 0;
    IoCompleteRequest(Irp, IO_NO_INCREMENT);

    InputPrint((2,"INPUTCLASS-InputClassOpenClose: exit\n"));

    return(status);
}

NTSTATUS
InputClassRead(
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
    )

/*++

Routine Description:

    This routine is the dispatch routine for read requests.  Valid read
    requests are marked pending, and started via IoStartPacket.

Arguments:

    DeviceObject - Pointer to class device object.

    Irp - Pointer to the request packet.

Return Value:

    Status is returned.

--*/

{
    NTSTATUS status;
    PIO_STACK_LOCATION irpSp;

    InputPrint((2,"INPUTCLASS-InputClassRead: enter\n"));

    irpSp = IoGetCurrentIrpStackLocation(Irp);

    //
    // Validate the read request parameters.  The read length should be an
    // integral number of INPUT_DATA structures.
    //


    if (irpSp->Parameters.Read.Length == 0) {
        status = STATUS_SUCCESS;
    }
    else if (irpSp->Parameters.Read.Length % sizeof(INPUT_DATA)) {
        status = STATUS_BUFFER_TOO_SMALL;
    } 
    else if (irpSp->FileObject->FsContext) {

        //
        // If the file object's FsContext is non-null, then we've already 
        // done the Read privilege check once before for this thread.  Skip 
        // the privilege check.
        //

        status = STATUS_PENDING;
    }
    else {

        //
        // We only allow a trusted subsystem with the appropriate privilege 
        // level to execute a Read call.
        //

        status = STATUS_PRIVILEGE_NOT_HELD;


    }

    //
    // If status is pending, mark the packet pending and start the packet
    // in a cancellable state.  Otherwise, complete the request.
    //

    Irp->IoStatus.Status = status;
    Irp->IoStatus.Information = 0;
    if (status == STATUS_PENDING) {
        IoMarkIrpPending(Irp);
        IoStartPacket(DeviceObject, Irp, (PULONG)NULL, InputClassCancel);
    } else {
        IoCompleteRequest(Irp, IO_NO_INCREMENT);
    }

    InputPrint((2,"INPUTCLASS-InputClassRead: exit\n"));

    return(status);

}

VOID
InputClassServiceCallback(
    IN PDEVICE_OBJECT DeviceObject,
    IN PINPUT_DATA InputDataStart,
    IN PINPUT_DATA InputDataEnd,
    IN OUT PULONG InputDataConsumed
    )

/*++

Routine Description:

    This routine is the class service callback routine.  It is
    called from the port driver's interrupt service DPC.  If there is an
    outstanding read request, the request is satisfied from the port input
    data queue.  Unsolicited Input input is moved from the port input
    data queue to the class input data queue.

    N.B.  This routine is entered at DISPATCH_LEVEL IRQL from the port
          driver's ISR DPC routine.

Arguments:

    DeviceObject - Pointer to class device object.

    InputDataStart - Pointer to the start of the data in the port input
        data queue.

    InputDataEnd - Points one input data structure past the end of the
        valid port input data.

    InputDataConsumed - Pointer to storage in which the number of input
        data structures consumed by this call is returned.

    NOTE:  Could pull the duplicate code out into a called procedure.

Return Value:

    None.

--*/

{
    CInputClassDeviceExt *cExtension;
    PIO_STACK_LOCATION irpSp;
    PIRP  irp;
    KIRQL cancelIrql;
    ULONG bytesInQueue;
    ULONG bytesToMove;
    ULONG moveSize;
    BOOLEAN satisfiedPendingReadRequest = FALSE;
//    PIO_ERROR_LOG_PACKET errorLogEntry;

    InputPrint((2,"INPUTCLASS-InputClassServiceCallback: enter\n"));

    cExtension = (CInputClassDeviceExt *) DeviceObject->DeviceExtension;
    bytesInQueue = (PCHAR) InputDataEnd - (PCHAR) InputDataStart;
    moveSize = 0;
    *InputDataConsumed = 0;

    //
    // Acquire the spinlock that  protects the class device extension 
    // (so we can look at RequestIsPending synchronously).  If there is
    // a pending read request, satisfy it.
    //
    // N.B. We can use KeAcquireSpinLockAtDpcLevel, instead of
    //      KeAcquireSpinLock, because this routine is already running
    //      at DISPATCH_IRQL.
    //

    KeAcquireSpinLockAtDpcLevel(&cExtension->SpinLock);

    if (cExtension->RequestIsPending) {

        //
        // Acquire the cancel spinlock, remove the request from the 
        // cancellable state, and free the cancel spinlock.
        //
        IoAcquireCancelSpinLock(&cancelIrql);
        irp = DeviceObject->CurrentIrp;
        IoSetCancelRoutine(irp, NULL);
        DeviceObject->CurrentIrp = NULL;
        IoReleaseCancelSpinLock(cancelIrql);

        //
        // An outstanding read request exists.   Clear the RequestIsPending 
        // flag to indicate there is no longer an outstanding read request 
        // pending.
        //

        cExtension->RequestIsPending = FALSE;

        //
        // Copy as much of the input data possible from the port input
        // data queue to the SystemBuffer to satisfy the read.
        //

        irpSp = IoGetCurrentIrpStackLocation(irp);
        bytesToMove = irpSp->Parameters.Read.Length;
        moveSize = (bytesInQueue < bytesToMove) ?
                                   bytesInQueue:bytesToMove;
        *InputDataConsumed += (moveSize / sizeof(INPUT_DATA));

    
        RtlMoveMemory(
            irp->AssociatedIrp.SystemBuffer,
            (PCHAR) InputDataStart,
            moveSize
            );

        //
        // Set the flag so that we start the next packet and complete 
        // this read request (with STATUS_SUCCESS) prior to return.
        //

        irp->IoStatus.Status = STATUS_SUCCESS;
        irp->IoStatus.Information = moveSize;
        irpSp->Parameters.Read.Length = moveSize;
        satisfiedPendingReadRequest = TRUE;

    }

    //
    // If there is still data in the port input data queue, move it to the class
    // input data queue.
    //
	if (bytesInQueue - moveSize > 0)
	{ 
	 bytesToMove = cExtension->Insert((PCHAR)InputDataStart+moveSize,bytesInQueue-moveSize);
     *InputDataConsumed += (bytesToMove / sizeof(INPUT_DATA));
	};
   // this code should be in the class... or?
  
    //
    // Release the class input data queue spinlock.
    //

    KeReleaseSpinLockFromDpcLevel(&cExtension->SpinLock);

    // 
    // If we satisfied an outstanding read request, start the next
    // packet and complete the request.
    // 

    if (satisfiedPendingReadRequest) {

        IoStartNextPacket(DeviceObject, TRUE);
        IoCompleteRequest(irp, IO_INPUT_INCREMENT);
    }

    InputPrint((2,"INPUTCLASS-InputClassServiceCallback: exit\n"));

    return;

}

VOID
InputClassStartIo(
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
    )

/*++

Routine Description:

    This routine is the StartIo routine.  It is invoked to start a Read
    request.  If the class input data queue contains input data, the input
    data is copied to the SystemBuffer to satisfy the read.

    N.B.  Requests enter InputClassStartIo in a cancellable state.  Also,
          there is an implicit assumption that only read requests are
          queued to the device queue (and handled by StartIo).  If this
          changes in the future, the InputClassCleanup routine will
          be impacted.

    NOTE:  Could pull the duplicate code out into a called procedure.

Arguments:

    DeviceObject - Pointer to class device object.

    Irp - Pointer to the request packet.

Return Value:

    None.

--*/

{
    CInputClassDeviceExt *cExtension;
    PIO_STACK_LOCATION irpSp;
    KIRQL cancelIrql;
    PCHAR destination;
//    ULONG bytesInQueue;
    ULONG bytesToMove;
//    ULONG moveSize;

    InputPrint((2,"INPUTCLASS-InputClassStartIo: enter\n"));

    cExtension = (CInputClassDeviceExt *) DeviceObject->DeviceExtension;

    //
    // Bump the error log sequence number.
    //

    cExtension->SequenceNumber += 1;

    //
    // Acquire the spinlock to protect the input data queue and associated
    // pointers.  Note that StartIo is already running at DISPATCH_LEVEL
    // IRQL, so we can use KeAcquireSpinLockAtDpcLevel instead of
    // KeAcquireSpinLock.
    //

    KeAcquireSpinLockAtDpcLevel(&cExtension->SpinLock);

    //
    // Acquire the cancel spinlock and verify that the Irp has not been
    // cancelled and that cleanup is not in progress.
    //

    IoAcquireCancelSpinLock(&cancelIrql);
    if (Irp->Cancel || cExtension->CleanupWasInitiated) {
        IoReleaseCancelSpinLock(cancelIrql);
        KeReleaseSpinLockFromDpcLevel(&cExtension->SpinLock);
        return;
    }

    //
    // If the input data queue is non-empty, satisfy the read request.
    // Otherwise, hold the request pending.
    //
	  if (cExtension->InputCount > 0)        // pre-check whether there is a chance to do
	   {                                      // anything at all...the order seems to be  
        IoSetCancelRoutine(Irp, NULL);		  // crucial here...
        DeviceObject->CurrentIrp = NULL;
        IoReleaseCancelSpinLock(cancelIrql);

        irpSp = IoGetCurrentIrpStackLocation(Irp);

        //
        // bytesToMove <- MIN(Number of filled bytes in class input data queue,
        //                    Requested read length).
        //
        destination = (char *)Irp->AssociatedIrp.SystemBuffer;
        bytesToMove = irpSp->Parameters.Read.Length;
        int iRemoved =
        cExtension->Remove(destination,bytesToMove);
        cExtension->RequestIsPending = FALSE;

         //
         // Release the class input data queue spinlock.
         //

         KeReleaseSpinLockFromDpcLevel(&cExtension->SpinLock);

         //
         // Start the next packet, and complete this read request
         // with STATUS_SUCCESS.
         //

         Irp->IoStatus.Status = STATUS_SUCCESS;
		 // make sure to let the caller know how many bytes were received eventually...
         Irp->IoStatus.Information = iRemoved;
         irpSp->Parameters.Read.Length = iRemoved;

         IoStartNextPacket(DeviceObject, TRUE);
         IoCompleteRequest(Irp, IO_INPUT_INCREMENT);

        } 
        else 
        {

         //
         // Set the RequestIsPending flag to indicate this request is
         // held pending for the callback routine to complete.
         //

         cExtension->RequestIsPending = TRUE;

         //
         // Hold the read request pending.  It remains in the cancellable
         // state.  When new input is received, the class service
         // callback routine will eventually complete the request.  For now,
         // merely free the cancel spinlock and the class input data queue
         // spinlock.
         //

         IoReleaseCancelSpinLock(cancelIrql);
         KeReleaseSpinLockFromDpcLevel(&cExtension->SpinLock);
        } 

    InputPrint((2,"INPUTCLASS-InputClassStartIo: exit\n"));

    return;

}

VOID
InputClassUnload(
    IN PDRIVER_OBJECT DriverObject
    )

/*++

Routine Description:

    This routine is the class driver unload routine.

    NOTE:  Not currently implemented.

Arguments:

    DeviceObject - Pointer to class device object.

Return Value:

    None.

--*/

{
    UNREFERENCED_PARAMETER(DriverObject);

    InputPrint((2,"INPUTCLASS-InputClassUnload: enter\n"));
    InputPrint((2,"INPUTCLASS-InputClassUnload: exit\n"));

    return;
}

NTSTATUS
InputConfiguration(
    IN CGlobalInputClassData *GlobalData,
    IN CUString *RegistryPath,
    IN CUString *DeviceName
)

/*++

Routine Description:

    This routine stores the configuration information for this device.

Arguments:

    DeviceExtension - Pointer to the device extension.

    RegistryPath - Pointer to the null-terminated Unicode name of the 
        registry path for this driver.

    DeviceName - Pointer to the Unicode string that will receive
        the port device name.

Return Value:

    None.  As a side-effect, sets fields in DeviceExtension->InputAttributes.

--*/

{
    CUString parameterString(L"\\Parameters");
    CUString cuDataQueueSize(QSIZESTRING);
    CUString cuMaximumPortsServiced(SERVICEDNOSTRING);
    CUString cuPointerDeviceBaseName(BASENAMESTRING);
    CUString cuMultiple(CONNECTMULTIPLESTRING);
    CUString defaultUnicodeName(DD_POINTER_CLASS_BASE_NAME_U);
    CRegistry crQueryTable(1);
    
    if ( (!OK_ALLOCATED(&parameterString))
       ||(!OK_ALLOCATED(&cuDataQueueSize))
       ||(!OK_ALLOCATED(&cuMaximumPortsServiced))
       ||(!OK_ALLOCATED(&cuPointerDeviceBaseName))
       ||(!OK_ALLOCATED(&cuMultiple))
       ||(!OK_ALLOCATED(&defaultUnicodeName))
       ||(!OK_ALLOCATED(&crQueryTable)))
      return STATUS_INSUFFICIENT_RESOURCES; 

    CUString parametersPath(RegistryPath->m_String.Length +parameterString.m_String.Length+sizeof(UNICODE_NULL));
	if (!OK_ALLOCATED(&parametersPath))
	  return STATUS_INSUFFICIENT_RESOURCES;

    parametersPath.Append(&RegistryPath->m_String);
	parametersPath.Append(&parameterString.m_String);

    ULONG defaultDataQueueSize = DATA_QUEUE_SIZE;
    ULONG defaultMaximumPortsServiced = 1;
    ULONG defaultConnectMultiplePorts = 0;
    NTSTATUS status = STATUS_SUCCESS;
//    UNICODE_STRING defaultUnicodeName;
        //

	void *pContextAddress;
    pContextAddress=&GlobalData->InputAttributes.InputDataQueueLength;
	if (!crQueryTable.QueryDirect(&parametersPath,&cuDataQueueSize,&pContextAddress,REG_DWORD))
	 GlobalData->InputAttributes.InputDataQueueLength = defaultDataQueueSize;
    pContextAddress=&GlobalData->MaximumPortsServiced;
	if (!crQueryTable.QueryDirect(&parametersPath,&cuMaximumPortsServiced,&pContextAddress,REG_DWORD))
	 GlobalData->MaximumPortsServiced = defaultMaximumPortsServiced;
    pContextAddress=&GlobalData->ConnectOneClassToOnePort;
	if (!crQueryTable.QueryDirect(&parametersPath,&cuMultiple,&pContextAddress,REG_DWORD))
	 GlobalData->ConnectOneClassToOnePort = defaultConnectMultiplePorts;
    pContextAddress=&DeviceName->m_String;
    if (!crQueryTable.QueryDirect(&parametersPath,&cuPointerDeviceBaseName,&pContextAddress,REG_SZ))
     defaultUnicodeName.CopyTo(DeviceName);

// now tweak the values
 
    if (GlobalData->InputAttributes.InputDataQueueLength == 0) 
    {
     InputPrint((
            1,
            "INPUTCLASS-InputConfiguration: overriding InputDataQueueLength = 0x%x\n",
            GlobalData->InputAttributes.InputDataQueueLength
            ));

     GlobalData->InputAttributes.InputDataQueueLength = 
            defaultDataQueueSize;
    }

    GlobalData->InputAttributes.InputDataQueueLength *= 
        sizeof(INPUT_DATA);

    InputPrint((
        1,
        "INPUTCLASS-InputConfiguration: InputDataQueueLength = 0x%x\n",
        GlobalData->InputAttributes.InputDataQueueLength
        ));

    InputPrint((
        1,
        "INPUTCLASS-InputConfiguration: MaximumPortsServiced = %d\n",
        GlobalData->MaximumPortsServiced
        ));

    //
    // Invert the flag that specifies the type of class/port connections.
    // We used it in the RtlQuery call in an inverted fashion.
    //

    GlobalData->ConnectOneClassToOnePort = 
        !GlobalData->ConnectOneClassToOnePort;

    InputPrint((
        1,
        "INPUTCLASS-InputConfiguration: Connection Type = %d\n",
        GlobalData->ConnectOneClassToOnePort
        ));
  return STATUS_SUCCESS;
}

NTSTATUS
InputConnectToPort(
    IN PDEVICE_OBJECT ClassDeviceObject,
    IN PUNICODE_STRING FullPortName,
    IN ULONG PortIndex
    )

/*++

Routine Description:

    This routine creates the Input class device object and connects
    to the port device.  
    

Arguments:

    ClassDeviceObject - Pointer to the device object for the class device.

    FullPortName - Pointer to the Unicode string that is the full path name
        for the port device object.

    PortIndex - The index into the PortDeviceObjectList[] for the 
        current connection.

Return Value:

    The function value is the final status from the operation.

--*/

{
    CInputClassDeviceExt *cExtension;
    NTSTATUS status;
    PFILE_OBJECT fileObject = NULL;
    PDEVICE_OBJECT portDeviceObject = NULL;
    ULONG uniqueErrorValue;

    InputPrint((1,"\n\nINPUTCLASS-InputConnectToPort: enter\n"));

    //
    // Get a pointer to the port device object.
    //

    InputPrint((
        2,
        "INPUTCLASS-InputConnectToPort: Pointer port name %ws\n", 
        FullPortName->Buffer
        ));
    status = IoGetDeviceObjectPointer(
                 FullPortName,
                 FILE_READ_ATTRIBUTES,
                 &fileObject,
                 &portDeviceObject
                 );

    if (status != STATUS_SUCCESS) {
        InputPrint((
            1,
            "INPUTCLASS-InputConnectToPort: Could not get port device object %ws\n",
            FullPortName->Buffer
            ));

        goto InputConnectToPortExit;
    }

    cExtension = (CInputClassDeviceExt *) ClassDeviceObject->DeviceExtension;

    cExtension->cData->PortDeviceObjectList[PortIndex] = portDeviceObject;

    //
    // Set the IRP stack size (add 1 for the class layer).
    //
    // NOTE:  This is a bit funky for 1:many connections (we end up setting
    //        StackSize each time through this routine). Note also that 
    //        there is an assumption that the number of layers in the 
    //        class/port driver model is always the same (i.e., if there is 
    //        a layer between the class and the port driver for one device, 
    //        that is true for every device).
    //

    ClassDeviceObject->StackSize =
        (CCHAR) cExtension->cData->PortDeviceObjectList[PortIndex]->StackSize + 1;

    //
    // Connect to port device.
    //

    status = InputSendConnectRequest(
                ClassDeviceObject,
                (PVOID)InputClassServiceCallback,
                PortIndex
                );

    if (status != STATUS_SUCCESS) {
        InputPrint((
            1,
            "INPUTCLASS-InputConnectToPort: Could not connect to port device %ws\n",
            FullPortName->Buffer
            ));

        //
        // Log an error.
        //

        status = INPUTCLASS_NO_PORT_CONNECT;
        uniqueErrorValue = INPUT_ERROR_VALUE_BASE + 30;
    }

InputConnectToPortExit:

    if (status != STATUS_SUCCESS) {

        //
        // Some part of the initialization failed.  Log an error, and 
        // clean up the resources for the failed part of the initialization.
        //
	delete (new (PagedPool) 
 	        CErrorLogEntry(ClassDeviceObject,
                           status,
                           0,
					       uniqueErrorValue,
					       status,
					       (ULONG *)0,
					       0  // to go into MajorFunctionCode member
					       ));
    
        if (fileObject) {
            ObDereferenceObject(fileObject);
        }

        //
        // We count on the caller to free the ring buffer and delete
        // the class device object.
        //
    }
    
    InputPrint((1,"INPUTCLASS-InputConnectToPort: exit\n"));
    
    return(status);

}

NTSTATUS
InputCreateClassObject(
    IN PDRIVER_OBJECT DriverObject,
    IN CGlobalInputClassData *cGlobalData,
    IN PUNICODE_STRING RegistryPath,
    IN PUNICODE_STRING FullDeviceName,
    IN PUNICODE_STRING BaseDeviceName,
    IN PDEVICE_OBJECT *ClassDeviceObject
    )

/*++

Routine Description:

    This routine creates the  class device object.
    

Arguments:

    DriverObject - Pointer to driver object created by system.

    TmpDeviceExtension - Pointer to the template device extension.
        
    RegistryPath - Pointer to the null-terminated Unicode name of the 
        registry path for this driver.

    FullDeviceName - Pointer to the Unicode string that is the full path name
        for the class device object.

    BaseDeviceName - Pointer to the Unicode string that is the base path name
        for the class device.

    ClassDeviceObject - Pointer to a pointer to the class device object.

Return Value:

    The function value is the final status from the operation.

--*/

{	
    NTSTATUS status;
 //   PIO_ERROR_LOG_PACKET errorLogEntry;
    ULONG uniqueErrorValue;
    NTSTATUS errorCode = STATUS_SUCCESS;

    InputPrint((1,"\n\nINPUTCLASS-InputCreateClassObject: enter\n"));

    //
    // Create a non-exclusive device object for the class device.
    //

    InputPrint((
        1,
        "INPUTCLASS-InputCreateClassObject: Creating device object named %ws\n",
        FullDeviceName->Buffer
        ));

    status = IoCreateDevice(
                 DriverObject,
                 sizeof(CInputClassDeviceExt *),
                 FullDeviceName,
                 FILE_DEVICE_INPUT,
                 0,
                 FALSE,
                 ClassDeviceObject
                 );

    if (!NT_SUCCESS(status)) {
        InputPrint((
            1,
            "INPUTCLASS-InputCreateClassObject: Could not create class device object = %ws\n",
            FullDeviceName->Buffer
            ));
        goto InputCreateClassObjectExit;
      
    } 

    //
    // Do buffered I/O.  I.e., the I/O system will copy to/from user data
    // from/to a system buffer.
    //

    (*ClassDeviceObject)->Flags |= DO_BUFFERED_IO;

    // this call makes a copy of the root extension object...
    
    (*ClassDeviceObject)->DeviceExtension = new(NonPagedPool) CInputClassDeviceExt(cGlobalData);
  	if (!OK_ALLOCATED((CInputClassDeviceExt *)((*ClassDeviceObject)->DeviceExtension)))
	{
	    status = STATUS_INSUFFICIENT_RESOURCES;
	    errorCode = INPUTCLASS_NO_BUFFER_ALLOCATED;
        uniqueErrorValue = INPUT_ERROR_VALUE_BASE + 20;

    };
InputCreateClassObjectExit:

    if (status != STATUS_SUCCESS) {

        //
        // Some part of the initialization failed.  Log an error, and 
        // clean up the resources for the failed part of the initialization.
        //

	delete (new (PagedPool) 
 	        CErrorLogEntry((*ClassDeviceObject == NULL) ? 
                           (PVOID) DriverObject : (PVOID) *ClassDeviceObject,
                           errorCode,
                           0,
					       uniqueErrorValue,
					       status,
					       (ULONG *)0,
					       0  // to go into MajorFunctionCode member
					       ));

         
    
        if (*ClassDeviceObject) 
         {
          if ((*ClassDeviceObject)->DeviceExtension)
		  delete (*ClassDeviceObject)->DeviceExtension;
          IoDeleteDevice(*ClassDeviceObject);
          *ClassDeviceObject = NULL;
         };
    }
    
    InputPrint((1,"INPUTCLASS-InputCreateClassObject: exit\n"));
    
    return(status);

}

#if DBG

VOID
InputDebugPrint(
    ULONG DebugPrintLevel,
    PCCHAR DebugMessage,
    ...
    )

/*++

Routine Description:

    Debug print routine.

Arguments:

    Debug print level between 0 and 3, with 3 being the most verbose.

Return Value:

    None.

--*/

{
    va_list ap;

    va_start(ap, DebugMessage);

    if (DebugPrintLevel <= InputDebug) {

        char buffer[256];

        (VOID) vsprintf(buffer, DebugMessage, ap);

        DbgPrint(buffer);
    }

    va_end(ap);

} 
#endif

NTSTATUS 
InputDeviceMapQueryCallback(
    IN PWSTR ValueName,
    IN ULONG ValueType,
    IN PVOID ValueData,
    IN ULONG ValueLength,
    IN PVOID Context,
    IN PVOID EntryContext
    )

/*++

Routine Description:

    This is the callout routine specified in a call to
    RtlQueryRegistryValues.  It increments the value pointed
    to by the Context parameter.
            
Arguments:

    ValueName - Unused.

    ValueType - Unused.

    ValueData - Unused.

    ValueLength - Unused.

    Context - Pointer to a count of the number of times this
        routine has been called.  This is the number of ports
        the class driver needs to service.

    EntryContext - Unused.

Return Value:

    The function value is the final status from the operation.  

--*/

{
    *(PULONG)Context += 1;

    return(STATUS_SUCCESS);
}

NTSTATUS
InputEnableDisablePort(
    IN PDEVICE_OBJECT DeviceObject,
    IN BOOLEAN EnableFlag,
    IN ULONG PortIndex
    )

/*++

Routine Description:

    This routine sends an enable or a disable request to the port driver.

Arguments:

    DeviceObject - Pointer to class device object.

    EnableFlag - If TRUE, send an ENABLE request; otherwise, send DISABLE.

    PortIndex - Index into the PortDeviceObjectList[] for the current
        enable/disable request.

Return Value:

    Status is returned.

--*/

{
    PIRP irp;
    IO_STATUS_BLOCK ioStatus;
    NTSTATUS status;
    KEVENT event;
    CInputClassDeviceExt *cExtension;

    InputPrint((2,"INPUTCLASS-InputEnableDisablePort: enter\n"));

    //
    // Get a pointer to the device extension.
    //

    cExtension = (CInputClassDeviceExt *) DeviceObject->DeviceExtension;

    //
    // Create notification event object to be used to signal the
    // request completion.
    //

    KeInitializeEvent(&event, NotificationEvent, FALSE);

    //
    // Build the synchronous request to be sent to the port driver
    // to perform the request.  Allocate an IRP to issue the port internal
    // device control Enable/Disable call.  
    //

    irp = IoBuildDeviceIoControlRequest(
            EnableFlag? IOCTL_INTERNAL_INPUT_ENABLE:
                        IOCTL_INTERNAL_INPUT_DISABLE,
            cExtension->cData->PortDeviceObjectList[PortIndex],
            NULL,
            0,
            NULL,
            0,
            TRUE,
            &event,
            &ioStatus
            );

    //
    // Call the port driver to perform the operation.  If the returned status
    // is PENDING, wait for the request to complete.
    //

    status = IoCallDriver(
                 cExtension->cData->PortDeviceObjectList[PortIndex],
                 irp
                 );

    if (status == STATUS_PENDING) {
        (VOID) KeWaitForSingleObject(
                   &event,
                   Suspended,
                   KernelMode,
                   FALSE,
                   NULL
                   );
    } else {

        //
        // Ensure that the proper status value gets picked up.
        //

        ioStatus.Status = status;
    }

    InputPrint((2,"INPUTCLASS-InputEnableDisablePort: exit\n"));

    return(ioStatus.Status);

}


NTSTATUS
InputSendConnectRequest(
    IN PDEVICE_OBJECT DeviceObject,
    IN PVOID ServiceCallback,
    IN ULONG PortIndex
    )

/*++

Routine Description:

    This routine sends a connect request to the port driver.

Arguments:

    DeviceObject - Pointer to class device object.

    ServiceCallback - Pointer to the class service callback routine.

    PortIndex - The index into the PortDeviceObjectList[] for the current
        connect request.

Return Value:

    Status is returned.

--*/

{
    PIRP irp;
    IO_STATUS_BLOCK ioStatus;
    NTSTATUS status;
    KEVENT event;
    CInputClassDeviceExt *cExtension;
    CONNECT_DATA connectData;

    InputPrint((2,"INPUTCLASS-InputSendConnectRequest: enter\n"));

    //
    // Get a pointer to the device extension.
    //

    cExtension = (CInputClassDeviceExt *) DeviceObject->DeviceExtension;

    //
    // Create notification event object to be used to signal the
    // request completion.
    //

    KeInitializeEvent(&event, NotificationEvent, FALSE);

    //
    // Build the synchronous request to be sent to the port driver
    // to perform the request.  Allocate an IRP to issue the port internal
    // device control connect call.  The connect parameters are passed in
    // the input buffer.
    //

    connectData.ClassDeviceObject = DeviceObject;
    connectData.ClassService = ServiceCallback;

    irp = IoBuildDeviceIoControlRequest(
            IOCTL_INTERNAL_INPUT_CONNECT,
            cExtension->cData->PortDeviceObjectList[PortIndex],
            &connectData,
            sizeof(CONNECT_DATA),
            NULL,
            0,
            TRUE,
            &event,
            &ioStatus
            );

    //
    // Call the port driver to perform the operation.  If the returned status
    // is PENDING, wait for the request to complete.
    //

    status = IoCallDriver(
                 cExtension->cData->PortDeviceObjectList[PortIndex],
                 irp
                 );

    if (status == STATUS_PENDING) {
        (VOID) KeWaitForSingleObject(
                   &event,
                   Suspended,
                   KernelMode,
                   FALSE,
                   NULL
                   );
    } else {

        //
        // Ensure that the proper status value gets picked up.
        //

        ioStatus.Status = status;
    }

    InputPrint((2,"INPUTCLASS-InputSendConnectRequest: exit\n"));

    return(ioStatus.Status);

} // end InputSendConnectRequest()
