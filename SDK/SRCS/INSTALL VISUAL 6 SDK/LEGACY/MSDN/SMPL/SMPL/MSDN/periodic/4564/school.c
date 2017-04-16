///////////////////////////////////////////////////////////////////////////////
//
//	  SCHOOL.C -- Bus Enumerator for the School Bus
//
///////////////////////////////////////////////////////////////////////////////

#define WANTVXDWRAPS
#include <basedef.h>
#include <vmm.h>
#include <debug.h>
#include <vmmreg.h>
#include <vwin32.h>
#include <vxdwraps.h>
#include <configmg.h>
#include <regstr.h>

#ifdef DEBUG
	#define ASSERT(e) if(!(e)){Debug_Printf("Assertion failure in " __FILE__ ", line %d: " #e "\r\n", __LINE__);\
		_asm int 1\
		}
#else
	#define ASSERT(e)
#endif

// Dummy private resource identifier. This would be appropriate for the fifth
// resource created by an OEM to whom Microsoft had assigned OEM ID 0x10.
// DON'T JUST USE THIS ID FOR YOUR OWN PRIVATE RESOURCE!

#define ResType_Telepath ((0x10 << 5) | 5)

typedef struct
	{							// telepath resource description
	int allocated;				// index of allocated channel (-1 means none)
	ULONG requested;			// mask for requested channels
	} TELEPATH_RESOURCE;		// telepath resource description

#pragma CM_PAGEABLE_DATA
#pragma CM_PAGEABLE_CODE

CONFIGRET CM_HANDLER OnEnumerate(CONFIGFUNC cf, SUBCONFIGFUNC scf, DEVNODE tonode, DEVNODE aboutnode, ULONG flags);
CONFIGRET CM_HANDLER OnArbitrateTelepath(ARBFUNC af, ULONG refdata, DEVNODE devnode,
	NODELIST_HEADER h);

REGISTERID arbid;

BOOL OnSysDynamicDeviceInit()
	{							// OnSysDynamicDeviceInit
	CM_Register_Arbitrator(&arbid, ResType_Telepath,
		OnArbitrateTelepath, 0, NULL, ARB_GLOBAL);
	return TRUE;
	}							// OnSysDynamicDeviceInit

BOOL OnSysDynamicDeviceExit()
	{							// OnSysDynamicDeviceExit
	if (arbid)
		CM_Deregister_Arbitrator(arbid, 0);
	return TRUE;
	}							// OnSysDynamicDeviceExit

CONFIGRET OnPnpNewDevnode(DEVNODE devnode, DWORD loadtype)
	{							// OnPnpNewDevnode
	CONFIGRET code;
	switch (loadtype)
		{						// select function to perform

	case DLVXD_LOAD_DEVLOADER:	// loadtype == 1
		code = CM_Register_Enumerator(devnode, OnEnumerate,
			CM_REGISTER_ENUMERATOR_HARDWARE);
		if (code != CR_SUCCESS)
			return code;
		return CM_Register_Device_Driver(devnode, NULL, 0,
			CM_REGISTER_DEVICE_DRIVER_REMOVABLE);

		}						// select function to perform

	return CR_DEFAULT;
	}							// OnPnpNewDevnode

CONFIGRET CM_HANDLER OnEnumerate(CONFIGFUNC cf, SUBCONFIGFUNC scf,
	DEVNODE tonode, DEVNODE aboutnode, ULONG flags)
	{							// OnEnumerate
	CONFIGRET code;

#ifdef DEBUG
	char toid[MAX_DEVICE_ID_LEN], aboutid[MAX_DEVICE_ID_LEN];
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

	CM_Get_Device_ID(tonode, toid, sizeof(toid), 0);
	CM_Get_Device_ID(aboutnode, aboutid, sizeof(aboutid), 0);
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
	if (cf < NUM_CONFIG_COMMANDS)
		Debug_Printf("SCHOOL ENUMERATOR: %s(%s), to %s, about %s\r\n", lpszConfigName[cf], subfunc, toid, aboutid);
	else
		Debug_Printf("SCHOOL ENUMERATOR: %X(%X), to %s, about %s\r\n", cf, toid, aboutid);
#endif

	switch (cf)
		{						// select on function code

	case CONFIG_SETUP:
		{						// CONFIG_SETUP
		ULONG length;			// length of class name
		char class[64];			// device class

		// The very first time we add the device to the hardware
		// tree, CONFIGMG will launch the device installer to load
		// a driver. To avoid having the initial dialog say the
		// device class is "Unknown", force the class in the
		// registry key to be "System" instead. Similarly force
		// the hardware ID so the installer knows which driver to
		// install. This knowledge is similar to what you'd discover
		// from a real Plug and Play device.
		
		length = sizeof(class);
		code = CM_Read_Registry_Value(aboutnode, NULL, "Class",
			REG_SZ, class, &length, CM_REGISTRY_HARDWARE);
		if (code == CR_NO_SUCH_VALUE)
			{					// new device
			CM_Write_Registry_Value(aboutnode, NULL, "Class",
				REG_SZ, "System", 6, CM_REGISTRY_HARDWARE);
			CM_Write_Registry_Value(aboutnode, NULL, "HardwareID",
				REG_SZ, "WCO1234", 6, CM_REGISTRY_HARDWARE);
			}					// new device
		return CR_SUCCESS;
		}						// CONFIG_SETUP

	case CONFIG_ENUMERATE:		// cf == 5
		{						// CONFIG_ENUMERATE
		DEVNODE device;			// DEVNODE for device
		LOG_CONF logconf;		// logical configuration
		RES_DES resource;		// resource descriptor handle

		static IRQ_RESOURCE irq = {{0, 0, 0xFFFF, 0}};
		static TELEPATH_RESOURCE telepath = {-1, 0xFF};
		
		// Create a DEVNODE for one device. In real life, we'd
		// either use a hardware detection scheme to enumerate
		// devices attached to the bus, or else we'd enumerate
		// a subkey of the registry (e.g., ENUM\SCHOOL) to locate
		// devices.
		
		code = CM_Create_DevNode(&device, "SCHOOL\\WCO1234\\0000",
			tonode, 0);
		if (code == CR_ALREADY_SUCH_DEVNODE)
			return CR_SUCCESS;	// nothing to do on reenumeration

		// Create a logical configuration for our one device.
		// Pretend the device needs an IRQ and one telepathic channel

		CM_Add_Empty_Log_Conf(&logconf, device, LCPRI_NORMAL,
			BASIC_LOG_CONF | PRIORITY_EQUAL_LAST);
		CM_Add_Res_Des(&resource, logconf, ResType_IRQ,
			&irq, sizeof(irq), 0);
		CM_Add_Res_Des(&resource, logconf, ResType_Telepath,
			&telepath, sizeof(telepath), 0);

		return CR_SUCCESS;
		}						// CONFIG_ENUMERATE

	default:
		return CR_DEFAULT;
		}						// select on function code
	}							// OnEnumerate

DWORD OnDeviceIoControl(PDIOCPARAMETERS p)
	{							// OnDeviceIoControl
	switch (p->dwIoControlCode)
		{						// select on function code
	
	case 1:
		Debug_Printf("Issuing CM_Callback_Enumerator call\r\n");
		CM_CallBack_Enumerator(OnEnumerate, 0);
		break;
		}						// select on function code
	
	return 0;
	}							// OnDeviceIoControl

///////////////////////////////////////////////////////////////////////
// Telepathic I/O channel resource arbitrator

typedef struct nodelistheader_s *NODELISTHEADER;
typedef struct nodelist_s *PNODE;

typedef struct
	{							// allocation placeholder
	PNODE node;					// current node
	TELEPATH_RESOURCE* pres;	// current resource descriptor
	} ALLOCPLACE, *PALLOCPLACE;	// allocation placeholder

// SORTNODES sorts the node list into increasing order by flexibility of
// allocation demands.

int bitcount(ULONG mask)
	{							// bitcount
	int nbits = 0;
	while (mask)
		{						// count bits
		if (mask & 1)
			++nbits;
		mask >>= 1;
		}						// count bits
	return nbits;
	}							// bitcount

void sortnodes(NODELISTHEADER h)
	{							// sortnodes
	PNODE node = h->nlh_Head;
	while (node)
		{						// for each node
		RES_DES hres = (RES_DES) node->nl_Test_Req;
		#define pres ((TELEPATH_RESOURCE *) hres)

		node->nl_ulSortDWord = 0;
		while (CM_Get_Next_Res_Des(&hres, hres, ResType_Telepath, NULL, 0) == CR_SUCCESS)
			node->nl_ulSortDWord += bitcount(pres->requested);
		node = node->nl_Next;

		#undef pres
		}						// for each node
	CM_Sort_NodeList((NODELIST_HEADER) h, 0);
	}							// sortnodes

// RELEASE walks through the node list to release assigned resources

void release(NODELISTHEADER h, PULONG pmap)
	{							// release
	PNODE node = h->nlh_Head;
	while (node)
		{						// for each node
		LOG_CONF logconf;

		// Find the allocated configuration (if any) for this devnode. Then loop over
		// its resource descriptors to find the ones for our resource and release
		// the assignment(s)

		if (CM_Get_First_Log_Conf(&logconf, (DEVNODE) node->nl_ItsDevNode, ALLOC_LOG_CONF) == CR_SUCCESS)
			{					// release this device's channel(s)
			RES_DES hres = (RES_DES) logconf;
			#define pres ((TELEPATH_RESOURCE *) hres)
			while (CM_Get_Next_Res_Des(&hres, hres, ResType_Telepath, NULL, 0) == CR_SUCCESS)
				if (pres->allocated >= 0)
					*pmap |= 1 << pres->allocated; // release the one assigned to this log conf
			#undef pres
			}					// release this device's channel(s)
		node = node->nl_Next;
		}						// for each node
	}							// release

// ALLOCATE attempts to allocate resources to devices using the requested possibilities
// recorded in the logical configurations.

BOOL nextres(PALLOCPLACE p)
	{							// nextres
	ASSERT(p->node && p->node->nl_Test_Req);
	if (!p->pres)
		p->pres = (TELEPATH_RESOURCE *) p->node->nl_Test_Req;
	while (CM_Get_Next_Res_Des((RES_DES*) &p->pres, (RES_DES) p->pres, ResType_Telepath, NULL, 0) != CR_SUCCESS)
		{						// no more descriptors of our resource
		if (!(p->node = p->node->nl_Next))
			return FALSE;		// no more nodes in the list
		p->pres = (TELEPATH_RESOURCE *) p->node->nl_Test_Req;
		}						// no more descriptors of our resource
	return TRUE;
	}							// nextres

BOOL allocate(PALLOCPLACE p, PULONG pmap)
	{							// allocate
	int channel;				// next channel to try allocating

	if (!nextres(p))
		return TRUE;			// no more of our resource needed, so we've succeeded

	for (p->pres->allocated = -1, channel = 0; channel < 32; ++channel)
		{						// try to allocate a channel
		ALLOCPLACE place = *p;
		ULONG mask = 1 << channel;
		ULONG tempmap = *pmap;
		if (!(tempmap & mask) || !(place.pres->requested & mask))
			continue;			// try next channel because this one isn't free or usable
		tempmap &= ~mask;		// do trial allocation
		if (allocate(&place, &tempmap))
			{					// successful allocation
			*pmap = tempmap;
			p->pres->allocated = channel;
			return TRUE;
			}					// successful allocation
		}						// try to allocate a channel
	}							// allocate

// REALLOCATE attempts to reallocate the same resources without regard to which
// alternative possibilities exist

BOOL reallocate(NODELISTHEADER h, PULONG pmap, BOOL forced)
	{							// reallocate
	PNODE node = h->nlh_Head;
	
	while (node)
		{						// for each node
		RES_DES hres = (RES_DES) node->nl_Test_Req;
		#define pres ((TELEPATH_RESOURCE *) hres)

		while (CM_Get_Next_Res_Des(&hres, hres, ResType_Telepath, NULL, 0) == CR_SUCCESS)
			{					// requires our resource
			ULONG mask;

			ASSERT(pres->allocated >= 0);
			mask = 1 << pres->allocated;
			if ((*pmap & mask) && !forced)
				return FALSE;	// one or more still in use
			*pmap &= ~mask;
			}					// requires our resource
		node = node->nl_Next;

		#undef pres
		}						// for each node
	return TRUE;
	}							// reallocate

// OnArbitrateTelepath is the resource arbitrator for telepathic I/O channels

CONFIGRET CM_HANDLER OnArbitrateTelepath(ARBFUNC af, ULONG refdata, DEVNODE devnode,
	NODELIST_HEADER h)
	{							// OnArbitrateTelepath
	static ULONG free_map = 0xFF; // real allocation map
	static ULONG free_copy = 0xDEADBEEF; // copy of allocation map

	switch (af)
		{						// select on arbitration function

	// TEST function: Examine each of our resource descriptors in the node list and
	// try to allocated one of the possible choices

	case ARB_TEST_ALLOC:		// af == 0
		{						// ARB_TEST_ALLOC
		ALLOCPLACE place = {((NODELISTHEADER)h)->nlh_Head, NULL};
		sortnodes((NODELISTHEADER) h);
		free_copy = free_map;
		release((NODELISTHEADER) h, &free_copy);

		if (allocate(&place, &free_copy))
			return CR_SUCCESS;
		else
			return CR_FAILURE;
		}						// ARB_TEST_ALLOC

	// RETEST and FORCE functions: Examine each of our resource descriptors in the node
	// list and allocate the one which is marked allocated in the test config. This
	// differs from TEST by (a) not sorting the node list because it makes no difference,
	// and (b) not even looking at the possible alternative allocations
	
	case ARB_RETEST_ALLOC:		// af == 1
	case ARB_FORCE_ALLOC:		// af == 6
		free_copy = free_map;
		release((NODELISTHEADER) h, &free_copy);

		if (reallocate((NODELISTHEADER) h, &free_copy, af == ARB_FORCE_ALLOC))
			return CR_SUCCESS;
		else
			return CR_FAILURE;

	// SET commits the previous trial allocation	
	
	case ARB_SET_ALLOC:			// af == 2
		ASSERT(free_copy != 0xDEADBEEF);
		free_map = free_copy;
		free_copy = 0xDEADBEEF;
		return CR_SUCCESS;

	// RELEASE discards the previous trial allocation
	
	case ARB_RELEASE_ALLOC:		// af == 3
		free_copy = 0xDEADBEEF;
		return CR_SUCCESS;

	// QUERY_FREE returns free resource information in our internal format. The
	// caller has to know what to expect.
	
	case ARB_QUERY_FREE:		// af == 4
		{						// ARB_QUERY_FREE
		struct arbitfree_s *p = (struct arbitfree_s *) h; // ugh!
		p->af_SizeOfInfo = sizeof(ULONG);
		p->af_PointerToInfo = (PVOID*) &free_map;
		return CR_SUCCESS;
		}						// ARB_QUERY_FREE

	case ARB_REMOVE:			// af == 5
		return CR_SUCCESS;

	default:
		return CR_DEFAULT;
		}						// select on arbitration function
	}							// OnArbitrateTelepath
