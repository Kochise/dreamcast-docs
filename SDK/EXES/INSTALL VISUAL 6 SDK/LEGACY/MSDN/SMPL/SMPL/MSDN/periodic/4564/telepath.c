///////////////////////////////////////////////////////////////////////////////
//
//	  TELEPATH.C: Example device driver
//
///////////////////////////////////////////////////////////////////////////////

#define WANTVXDWRAPS
#include <basedef.h>
#include <vmm.h>
#include <debug.h>
#include <vmmreg.h>
#include <vxdwraps.h>
#include <configmg.h>
#include <regstr.h>

static BYTE irq;			// allocated IRQ

CONFIGRET OnConfigure(CONFIGFUNC cf, SUBCONFIGFUNC scf,
	DEVNODE devnode, DWORD refdata, ULONG flags);

BOOL OnSysDynamicDeviceInit()
	{							// OnSysDynamicDeviceInit
	return TRUE;
	}							// OnSysDynamicDeviceInit

BOOL OnSysDynamicDeviceExit()
	{							// OnSysDynamicDeviceExit
	return TRUE;
	}							// OnSysDynamicDeviceExit

CONFIGRET OnPnpNewDevnode(DEVNODE devnode, DWORD loadtype)
	{							// OnPnpNewDevnode
	switch (loadtype)
		{						// select function to perform

	case DLVXD_LOAD_DEVLOADER:		// loadtype == 2
		return CM_Register_Device_Driver(devnode, OnConfigure, 0,
			(CM_REGISTER_DEVICE_DRIVER_REMOVABLE
			| CM_REGISTER_DEVICE_DRIVER_DISABLEABLE));
		}						// select function to perform

	return CR_DEFAULT;
	}							// OnPnpNewDevnode

CONFIGRET OnConfigure(CONFIGFUNC cf, SUBCONFIGFUNC scf,
	DEVNODE devnode, DWORD refdata, ULONG flags)
	{							// OnConfigure

#ifdef DEBUG
	char id[MAX_DEVICE_ID_LEN];
	DEBUG_CONFIG_NAMES
	char *subfunc = "";
	static char *substart[] = {"DYNAMIC_START", "FIRST_START"};
	static char *substop[] = {"DYNAMIC_STOP", "HAS_PROBLEM"};
	static char *subremove[] = {"DYNAMIC", "SHUTDOWN", "REBOOT"};
	static char *subtest[] = {"CAN_STOP", "CAN_REMOVE"};
	static char *subapm[] = {"TEST_STANDBY", "TEST_SUSPEND",
		"TEST_STANDBY_FAILED", "TEST_SUSPEND_FAILED",
		"TEST_STANDBY_SUCCEEDED", "TEST_SUSPEND_SUCCEEDED",
		"RESUME_STANDBY", "RESUME_SUSPEND", "RESUME_CRITICAL",
		"UI_ALLOWED"};

	switch (cf)
		{						// get subfunction name
	case CONFIG_START:
		subfunc = substart[scf];
		break;
	case CONFIG_STOP:
		subfunc = substop[scf];
		break;
	case CONFIG_REMOVE:
		subfunc = subremove[scf];
		break;
	case CONFIG_TEST:
		subfunc = subtest[scf];
		break;
	case CONFIG_APM:
		subfunc = subapm[scf];
		break;
		}						// get subfunction name

	CM_Get_Device_ID(devnode, id, sizeof(id), 0);
	if (cf < NUM_CONFIG_COMMANDS)
		Debug_Printf("TELEPATH DRIVER: %s(%s), %s\r\n", lpszConfigName[cf], subfunc, id);
	else
		Debug_Printf("TELEPATH DRIVER: %X(%X), %s\r\n", cf, scf, id);
#endif

	switch (cf)
		{						// select on function code

	case CONFIG_START:			// cf == 1
		{						// CONFIG_START
		
		// This is the normal way to obtain a configuration that
		// only includes the standard resources:
		
		CMCONFIG config;
		CM_Get_Alloc_Log_Conf(&config, devnode,
			CM_GET_ALLOC_LOG_CONF_ALLOC);
		irq = config.bIRQRegisters[0];

		// This is how to get a configuration that includes a
		// private resource:

		{
		#define ResType_Telepath ((0x10 << 5) | 5)

		typedef struct
			{							// telepath resource description
			ULONG allocated;			// mask for allocated channel
			ULONG requested;			// mask for requested channels
			} TELEPATH_RESOURCE;		// telepath resource description

		LOG_CONF logconf;
		RES_DES hres;
		#define pres ((TELEPATH_RESOURCE*) hres)

		CM_Get_First_Log_Conf(&logconf, devnode, ALLOC_LOG_CONF);
		if (CM_Get_Next_Res_Des(&hres, (RES_DES) logconf,
			ResType_Telepath, NULL, 0) == CR_SUCCESS)
			{						// has telepath channel
			// do something with pres->allocated
			}						// has telepath channel

		#undef pres
		}

		// Here we would initialize the device, doing things
		// like VPICD_Virtualize_IRQ, etc.

		return CR_SUCCESS;
		}						// CONFIG_START

	case CONFIG_REMOVE:			// cf == 4
	case CONFIG_STOP:			// cf == 2
		
		// Here we would disable the device and do things
		// like unvirtualizing our IRQ
		
		irq = 255;
		return CR_SUCCESS;

	default:
		return CR_DEFAULT;
		}						// select on function code
	}							// OnConfigure
