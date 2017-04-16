// data structures


extern "C"
{
NTSTATUS
DriverEntry(
    IN PDRIVER_OBJECT DriverObject,
    IN PUNICODE_STRING RegistryPath
    );

NTSTATUS CreateDevices(
    IN PDRIVER_OBJECT DriverObject,
	IN PUNICODE_STRING RegistryPath
	);
}    // extern "C"


// Note that there is no entry point for this routine in the DriverObject.
// The address of this routine must be passed to IoStart Packet.

VOID
$$SAFE_ROOT$$Cancel(
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
    );

$$BEGINLOOP(NUM_OPS)
$$IF(OPERATION)
NTSTATUS                
$$SAFE_ROOT$$$$OPERATION$$(
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
    );

$$ENDIF
$$ENDLOOP

$$IF(MACBIOCTL)
NTSTATUS
$$SAFE_ROOT$$IoControl(
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
    );
$$ENDIF


VOID
$$SAFE_ROOT$$StartIo(
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
    );

$$IF(MACBHASUNLOADROUTINE)
VOID
$$SAFE_ROOT$$Unload(
    IN PDRIVER_OBJECT DriverObject
    );
$$ENDIF

$$IF(MACBHASISR)
extern "C"
{
BOOLEAN
$$SAFE_ROOT$$InterruptService(
    IN PKINTERRUPT Interrupt,
    IN PVOID Context
    );
}
$$ENDIF


