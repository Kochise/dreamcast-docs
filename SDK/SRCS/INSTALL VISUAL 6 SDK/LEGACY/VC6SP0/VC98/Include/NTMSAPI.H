/*++

  Copyright (c) 1996-1997 Microsoft Corporation
  Copyright (c) 1996-1997 Highground Systems

  Module Name:

	NtmsApi.h

  Abstract:

	This module contains the NTMS API prototypes and public definitions
	supported in the API.  The NTMS API provide a "C" interface to NTMS.
	This header can be included in "C" and "C++" code.

  Author:

	Tom Hansen (thansen@highground.com) 25-Nov-1996

  Revision History:

--*/

#ifndef _INCL_NTMSAPI_H_
#define _INCL_NTMSAPI_H_

#pragma pack(8)

#ifdef __cplusplus
extern "C" {
#endif

typedef GUID NTMS_GUID;
typedef GUID* LPNTMS_GUID;
#define NTMS_NULLGUID  {0,0,0,{0,0,0,0,0,0,0,0}}
#define NTMS_IS_NULLGUID(id) ((id.Data1==0)&&(id.Data2==0)&&(id.Data3==0)&&\
							  (id.Data4[0]==0)&&(id.Data4[1]==0)&&(id.Data4[2]==0)&&\
							  (id.Data4[3]==0)&&(id.Data4[4]==0)&&(id.Data4[5]==0)&&\
							  (id.Data4[6]==0)&&(id.Data4[7]==0))
     
#ifndef NTMS_NOREDEF
// WARNING : The object types are provided as an ordered list of NTMS
// database objects.  DO NOT change the order without also changing the
// object metadata table in obmeta.cpp.
enum NtmsObjectsTypes {
	NTMS_UNKNOWN = 0,
	NTMS_OBJECT,
    NTMS_CHANGER,
    NTMS_CHANGER_TYPE,
    NTMS_COMPUTER,
    NTMS_DRIVE,
    NTMS_DRIVE_TYPE,
    NTMS_IEDOOR,
    NTMS_IEPORT,
    NTMS_LIBRARY,
    NTMS_LIBREQUEST,
    NTMS_LOGICAL_MEDIA,
    NTMS_MEDIA_POOL,
    NTMS_MEDIA_TYPE,
    NTMS_PARTITION,
    NTMS_PHYSICAL_MEDIA,
    NTMS_STORAGESLOT,
	NTMS_OPREQUEST,

	NTMS_NUMBER_OF_OBJECT_TYPES
};

// define unicode/ascii specific functions.  This include functions that
// get or return strings.
#ifdef UNICODE
#define OpenNtmsSession OpenNtmsSessionW
#define GetNtmsDeviceName GetNtmsDeviceNameW
#define GetNtmsObjectInformation GetNtmsObjectInformationW
#define SetNtmsObjectInformation SetNtmsObjectInformationW
#define CreateNtmsMediaPool CreateNtmsMediaPoolW
#define GetNtmsMediaPoolName GetNtmsMediaPoolNameW
#define GetNtmsObjectAttribute GetNtmsObjectAttributeW
#define SetNtmsObjectAttribute SetNtmsObjectAttributeW
#define SubmitNtmsOperatorRequest SubmitNtmsOperatorRequestW
#else
#define OpenNtmsSession OpenNtmsSessionA
#define GetNtmsDeviceName GetNtmsDeviceNameA
#define GetNtmsObjectInformation GetNtmsObjectInformationA
#define SetNtmsObjectInformation SetNtmsObjectInformationA
#define CreateNtmsMediaPool CreateNtmsMediaPoolA
#define GetNtmsMediaPoolName GetNtmsMediaPoolNameA
#define GetNtmsObjectAttribute GetNtmsObjectAttributeA
#define SetNtmsObjectAttribute SetNtmsObjectAttributeA
#define SubmitNtmsOperatorRequest SubmitNtmsOperatorRequestA
#endif

#endif	// NTMS_NOREDEF
//=======================================================================
// SESSION ESTABLISHMENT
//=======================================================================

#ifndef MIDL_PASS

enum NtmsSessionOptions {
	NTMS_SESSION_QUERYEXPEDITE = 0x1
};
HANDLE WINAPI OpenNtmsSessionW(
	LPCWSTR lpServer,
	LPCWSTR lpApplication,
	DWORD	dwOptions
	);

HANDLE WINAPI OpenNtmsSessionA(
	LPCSTR lpServer,
	LPCSTR lpApplication,
	DWORD	dwOptions
	);

DWORD WINAPI CloseNtmsSession(
	HANDLE hSession
	);

#endif	// MIDL_PASS

#ifndef NTMS_NOREDEF
//=======================================================================
// MOUNT DEFINITIONS
//=======================================================================
enum NtmsMountOptions {
	NTMS_MOUNT_READ = 0x0001,
	NTMS_MOUNT_WRITE = 0x0002,
	NTMS_MOUNT_ERROR_NOT_AVAILABLE = 0x0004,
	NTMS_MOUNT_ERROR_IF_UNAVAILABLE = 0x0004,
	NTMS_MOUNT_ERROR_OFFLINE = 0x0008,
	NTMS_MOUNT_ERROR_IF_OFFLINE = 0x0008,
	NTMS_MOUNT_SPECIFIC_DRIVE = 0x0010,
	NTMS_MOUNT_NOWAIT = 0x0020
};

enum NtmsDismountOptions {
	NTMS_DISMOUNT_DEFERRED = 0x0001
};

enum NtmsMountPriority {
	NTMS_PRIORITY_DEFAULT = 50,
	NTMS_PRIORITY_HIGHEST = 1,
	NTMS_PRIORITY_HIGH    = 25,
	NTMS_PRIORITY_NORMAL  = 50,
	NTMS_PRIORITY_LOW     = 75,
	NTMS_PRIORITY_LOWEST  = 100
};

#endif	// NTMS_NOREDEF
//=======================================================================
// MOUNT AND DISMOUNT APIS
//=======================================================================

#ifndef MIDL_PASS
DWORD WINAPI MountNtmsMedia(
	HANDLE hSession,
	LPNTMS_GUID lpMediaId,
	LPNTMS_GUID lpDriveId,
	DWORD dwCount,
	DWORD dwOptions,
	DWORD dwPriority,
	DWORD dwTimeout
	);

DWORD WINAPI DismountNtmsMedia(
	HANDLE hSession,
	LPNTMS_GUID lpMediaId,
	DWORD dwCount,
	DWORD dwOptions
	);

#endif	// MIDL_PASS

#ifndef NTMS_NOREDEF
//=======================================================================
// ALLOCATE DEFINITIONS
//=======================================================================
enum NtmsAllocateOptions {
	NTMS_ALLOCATE_NEW = 0x0001,
	NTMS_ALLOCATE_NEXT = 0x0002,
	NTMS_ALLOCATE_ERROR_IF_UNAVAILABLE = 0x0004
};

#endif

//=======================================================================
// ALLOCATE AND DEALLOCATE APIS
//=======================================================================
#ifndef MIDL_PASS
DWORD WINAPI AllocateNtmsMedia(
	HANDLE hSession,
    LPNTMS_GUID lpMediaPool,
	LPNTMS_GUID	lpPartition,	// optional
	LPNTMS_GUID	lpMediaId,	// OUTPUT, media id or operator request id
	DWORD dwOptions,
	DWORD dwTimeout
	);

DWORD WINAPI DeallocateNtmsMedia(
	HANDLE hSession,
	LPNTMS_GUID lpMediaId,
	DWORD dwOptions
	);

DWORD WINAPI SwapNtmsMedia( 
	HANDLE hSession, 
	LPNTMS_GUID lpMediaId1,
	LPNTMS_GUID lpMediaId2
	);

//=======================================================================
// MEDIA STATES
//=======================================================================
DWORD WINAPI DecommissionNtmsMedia(
	HANDLE hSession,
	LPNTMS_GUID lpMediaId
	);

DWORD WINAPI SetNtmsMediaComplete(
	HANDLE hSession,
	LPNTMS_GUID lpMediaId
	);

DWORD WINAPI DeleteNtmsMedia(
	HANDLE hSession,
	LPNTMS_GUID lpMediaId
	);
#endif	// MIDL_PASS

#ifndef NTMS_NOREDEF
//=======================================================================
// MEDIA POOLS
//=======================================================================
enum NtmsCreateOptions {
	NTMS_OPEN_EXISTING = 0x0001,
	NTMS_CREATE_NEW = 0x0002,
	NTMS_OPEN_ALWAYS = 0x0003
};
#endif	// NTMS_NOREDEF

#ifndef MIDL_PASS
#ifdef PRE_SEVIL
DWORD WINAPI CreateNtmsMediaPool(
	HANDLE hSession,
	LPCTSTR lpPoolName,
	LPNTMS_GUID lpMediaType,
	DWORD dwAction,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	LPNTMS_GUID lpPoolId		// OUT
	);
#endif
// SEVILIA
DWORD WINAPI CreateNtmsMediaPoolA(
	HANDLE hSession,
	LPCSTR lpPoolName,
	LPNTMS_GUID lpMediaType,
	DWORD dwAction,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	LPNTMS_GUID lpPoolId
	);

DWORD WINAPI CreateNtmsMediaPoolW(
	HANDLE hSession,
	LPCWSTR lpPoolName,
	LPNTMS_GUID lpMediaType,
	DWORD dwAction,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	LPNTMS_GUID lpPoolId
	);

DWORD WINAPI GetNtmsMediaPoolNameA(
	HANDLE hSession,
	LPNTMS_GUID lpPoolId,
	char *lpBufName,
	LPDWORD lpdwNameSize
	);

DWORD WINAPI GetNtmsMediaPoolNameW(
	HANDLE hSession,
	LPNTMS_GUID lpPoolId,
	wchar_t *lpBufName,
	LPDWORD lpdwNameSize
	);

DWORD WINAPI MoveToNtmsMediaPool(
	HANDLE hSession,
	LPNTMS_GUID lpMediaId,
	LPNTMS_GUID lpPoolId
	);

DWORD WINAPI DeleteNtmsMediaPool(
	HANDLE hSession,
	LPNTMS_GUID lpPoolId
	);

DWORD WINAPI DeleteNtmsLibrary(
	HANDLE hSession,
	LPNTMS_GUID lpLibraryId
	);

#endif	// MIDL_PASS

#ifndef NTMS_NOREDEF

//======================================================================
// OBJECT INFORMATION STRUCTURES
//======================================================================
enum NtmsDriveState {
	NTMS_DRIVESTATE_DISMOUNTED		= 0,
	NTMS_DRIVESTATE_MOUNTED			= 1,
	NTMS_DRIVESTATE_LOADED			= 2,
	NTMS_DRIVESTATE_UNLOADED		= 5,
	NTMS_DRIVESTATE_BEING_CLEANED	= 6,
	NTMS_DRIVESTATE_DISMOUNTABLE	= 7
};

#define NTMS_DEVICENAME_LENGTH		64
#define NTMS_SERIALNUMBER_LENGTH	32
#define NTMS_REVISION_LENGTH		32

#ifdef UNICODE 
#define _NTMS_DRIVEINFORMATION _NTMS_DRIVEINFORMATIONW
#define NTMS_DRIVEINFORMATION NTMS_DRIVEINFORMATIONW
#else
#define _NTMS_DRIVEINFORMATION _NTMS_DRIVEINFORMATIONA
#define NTMS_DRIVEINFORMATION NTMS_DRIVEINFORMATIONA
#endif 

typedef struct _NTMS_DRIVEINFORMATIONA {
    DWORD		Number;
    DWORD		State;
    NTMS_GUID	DriveType;
	CHAR		szDeviceName[NTMS_DEVICENAME_LENGTH];
    CHAR		szSerialNumber[NTMS_SERIALNUMBER_LENGTH];
    CHAR		szRevision[NTMS_REVISION_LENGTH];
    WORD		ScsiPort;
    WORD		ScsiBus;
    WORD		ScsiTarget;
    WORD		ScsiLun;
    DWORD		dwMountCount;
    SYSTEMTIME	LastCleanedTs;
    NTMS_GUID	SavedPartitionId;
    NTMS_GUID	Library;
	GUID		Reserved;
	DWORD		dwDeferDismountDelay;
} NTMS_DRIVEINFORMATIONA;

typedef struct _NTMS_DRIVEINFORMATIONW {
    DWORD		Number;
    DWORD		State;
    NTMS_GUID	DriveType;
	WCHAR		szDeviceName[NTMS_DEVICENAME_LENGTH];
    WCHAR		szSerialNumber[NTMS_SERIALNUMBER_LENGTH];
    WCHAR		szRevision[NTMS_REVISION_LENGTH];
    WORD		ScsiPort;
    WORD		ScsiBus;
    WORD		ScsiTarget;
    WORD		ScsiLun;
    DWORD		dwMountCount;
    SYSTEMTIME	LastCleanedTs;
    NTMS_GUID	SavedPartitionId;
    NTMS_GUID	Library;
	GUID		Reserved;
	DWORD		dwDeferDismountDelay;
} NTMS_DRIVEINFORMATIONW;

enum NtmsLibraryType {
	NTMS_LIBRARYTYPE_UNKNOWN	= 0,
	NTMS_LIBRARYTYPE_OFFLINE	= 1,
	NTMS_LIBRARYTYPE_ONLINE		= 2,
	NTMS_LIBRARYTYPE_STANDALONE = 3
};

enum NtmsInventoryMethod {
	NTMS_INVENTORY_NONE			= 0,
	NTMS_INVENTORY_FAST			= 1,
	NTMS_INVENTORY_OMID			= 2,
	NTMS_INVENTORY_DEFAULT			= 3,
	NTMS_INVENTORY_MAX
};

typedef struct _NTMS_LIBRARYINFORMATION {
    DWORD		LibraryType;
    NTMS_GUID	CleanerSlot;
	NTMS_GUID	CleanerSlotDefault;
	BOOL		LibrarySupportsDriveCleaning;
	BOOL		BarCodeReaderInstalled;
	DWORD		InventoryMethod;
	DWORD		dwCleanerUsesRemaining;
	DWORD		FirstDriveNumber;
	DWORD		dwNumberOfDrives;
	DWORD		FirstSlotNumber;
	DWORD		dwNumberOfSlots;
	DWORD		FirstDoorNumber;
	DWORD		dwNumberOfDoors;
	DWORD		FirstPortNumber;
	DWORD		dwNumberOfPorts;
	DWORD		FirstChangerNumber;
	DWORD		dwNumberOfChangers;
	DWORD		dwNumberOfMedia;
	DWORD		dwNumberOfMediaTypes;
	DWORD		dwNumberOfLibRequests;
	GUID		Reserved;
} NTMS_LIBRARYINFORMATION;

#ifdef UNICODE
#define _NTMS_CHANGERINFORMATION _NTMS_CHANGERINFORMATIONW
#define NTMS_CHANGERINFORMATION NTMS_CHANGERINFORMATIONW
#else
#define _NTMS_CHANGERINFORMATION _NTMS_CHANGERINFORMATIONA
#define NTMS_CHANGERINFORMATION NTMS_CHANGERINFORMATIONA
#endif

typedef struct _NTMS_CHANGERINFORMATIONA {
	DWORD		Number;
    NTMS_GUID	ChangerType;
    CHAR		szSerialNumber[NTMS_SERIALNUMBER_LENGTH];
    CHAR		szRevision[NTMS_REVISION_LENGTH];
    CHAR		szDeviceName[NTMS_DEVICENAME_LENGTH];
    WORD		ScsiPort;
    WORD		ScsiBus;
    WORD		ScsiTarget;
    WORD		ScsiLun;
    NTMS_GUID	Library;
} NTMS_CHANGERINFORMATIONA;

typedef struct _NTMS_CHANGERINFORMATIONW {
	DWORD		Number;
    NTMS_GUID	ChangerType;
    WCHAR		szSerialNumber[NTMS_SERIALNUMBER_LENGTH];
    WCHAR		szRevision[NTMS_REVISION_LENGTH];
    WCHAR		szDeviceName[NTMS_DEVICENAME_LENGTH];
    WORD		ScsiPort;
    WORD		ScsiBus;
    WORD		ScsiTarget;
    WORD		ScsiLun;
    NTMS_GUID	Library;
} NTMS_CHANGERINFORMATIONW;

enum NtmsSlotState {
	NTMS_SLOTSTATE_UNKNOWN			= 0,
	NTMS_SLOTSTATE_FULL				= 1,
	NTMS_SLOTSTATE_EMPTY			= 2,
	NTMS_SLOTSTATE_NOTPRESENT		= 3,   
	NTMS_SLOTSTATE_NEEDSINVENTORY	= 4
};

typedef struct _NTMS_STORAGESLOTINFORMATION {
    DWORD		Number;
    DWORD		State;
    NTMS_GUID	Library;
} NTMS_STORAGESLOTINFORMATION;

enum NtmsDoorState {
	NTMS_DOORSTATE_UNKNOWN		= 0,
	NTMS_DOORSTATE_CLOSED		= 1,
	NTMS_DOORSTATE_OPEN			= 2
};

typedef struct _NTMS_IEDOORINFORMATION {
    DWORD		Number;
    DWORD		State;
    WORD		MaxOpenSecs;
    NTMS_GUID	Library;
} NTMS_IEDOORINFORMATION;

enum NtmsPortPosition {
	NTMS_PORTPOSITION_UNKNOWN	= 0,
	NTMS_PORTPOSITION_EXTENDED	= 1,
	NTMS_PORTPOSITION_RETRACTED	= 2
};

enum NtmsPortContent {
	NTMS_PORTCONTENT_UNKNOWN	= 0,
	NTMS_PORTCONTENT_FULL		= 1,
	NTMS_PORTCONTENT_EMPTY		= 2
};

typedef struct _NTMS_IEPORTINFORMATION {
    DWORD		Number;
	DWORD		Content;
	DWORD		Position;
    WORD		MaxExtendSecs;
    NTMS_GUID	Library;
} NTMS_IEPORTINFORMATION;

enum NtmsBarCodeState {
	NTMS_BARCODESTATE_OK			= 1,
	NTMS_BARCODESTATE_UNREADABLE	= 2
};

enum NtmsMediaState {
	NTMS_MEDIASTATE_IDLE		= 0,
	NTMS_MEDIASTATE_INUSE		= 1,
	NTMS_MEDIASTATE_MOUNTED		= 2,
	NTMS_MEDIASTATE_LOADED		= 3,
	NTMS_MEDIASTATE_UNLOADED	= 4,
	NTMS_MEDIASTATE_OPERROR		= 5,
	// media is waiting for operator request servicing
	NTMS_MEDIASTATE_OPREQ		= 6
};

#define NTMS_BARCODE_LENGTH		64
#define NTMS_SEQUENCE_LENGTH	32

#ifdef UNICODE
#define _NTMS_PMIDINFORMATION _NTMS_PMIDINFORMATIONW
#define NTMS_PMIDINFORMATION NTMS_PMIDINFORMATIONW
#else
#define _NTMS_PMIDINFORMATION _NTMS_PMIDINFORMATIONA
#define NTMS_PMIDINFORMATION NTMS_PMIDINFORMATIONA
#endif

typedef struct _NTMS_PMIDINFORMATIONA {
	NTMS_GUID	CurrentLibrary;	// the current library
	NTMS_GUID	MediaPool;		// media pool that the media belongs to
	NTMS_GUID	Location;		// actual location of the media
	DWORD		LocationType;
	NTMS_GUID	MediaType;
	NTMS_GUID	HomeSlot;		// home slot for online media
	CHAR		szBarCode[NTMS_BARCODE_LENGTH];	// bar code string
	DWORD		BarCodeState;	// current state of the bar code
	CHAR		szSequenceNumber[NTMS_SEQUENCE_LENGTH];
	DWORD		MediaState;		// current media state
	DWORD		dwNumberOfPartitions;
} NTMS_PMIDINFORMATIONA;

typedef struct _NTMS_PMIDINFORMATIONW {
	NTMS_GUID	CurrentLibrary;	// the current library
	NTMS_GUID	MediaPool;		// media pool that the media belongs to
	NTMS_GUID	Location;		// actual location of the media
	DWORD		LocationType;
	NTMS_GUID	MediaType;
	NTMS_GUID	HomeSlot;		// home slot for online media
	WCHAR		szBarCode[NTMS_BARCODE_LENGTH];	// bar code string
	DWORD		BarCodeState;	// current state of the bar code
	WCHAR		szSequenceNumber[32];
	DWORD		MediaState;		// current media state
	DWORD		dwNumberOfPartitions;
} NTMS_PMIDINFORMATIONW;

typedef struct _NTMS_LMIDINFORMATION {
	NTMS_GUID	MediaPool;
	DWORD		dwNumberOfPartitions;
} NTMS_LMIDINFORMATION;

enum NtmsPartitionState {
	NTMS_PARTSTATE_UNKNOWN			= 0,
	NTMS_PARTSTATE_UNPREPARED		= 1,
	NTMS_PARTSTATE_INCOMPATIBLE		= 2,		
	NTMS_PARTSTATE_DECOMMISSIONED	= 3,
	NTMS_PARTSTATE_AVAILABLE		= 4,
	NTMS_PARTSTATE_ALLOCATED		= 5,
	NTMS_PARTSTATE_COMPLETE         = 6,
	NTMS_PARTSTATE_FOREIGN          = 7,
    NTMS_PARTSTATE_IMPORT           = 8,
	NTMS_PARTSTATE_RESERVED			= 9
};
// define the new state as the unknown state for now.
#define NTMS_PARTSTATE_NEW NTMS_PARTSTATE_UNKNOWN

#ifdef UNICODE
#define _NTMS_PARTITIONINFORMATION _NTMS_PARTITIONINFORMATIONW
#define NTMS_PARTITIONINFORMATION NTMS_PARTITIONINFORMATIONW
#else
#define _NTMS_PARTITIONINFORMATION _NTMS_PARTITIONINFORMATIONA
#define NTMS_PARTITIONINFORMATION NTMS_PARTITIONINFORMATIONA
#endif

typedef struct _NTMS_PARTITIONINFORMATIONA {
    NTMS_GUID	PhysicalMedia;
    NTMS_GUID	LogicalMedia;
	DWORD		State;
	WORD		Side;
	DWORD		dwOmidLabelIdLength;	// binary id
	BYTE		OmidLabelId[255];
	CHAR		szOmidLabelType[64];	// type string
	CHAR		szOmidLabelInfo[256];	// info string
	DWORD		dwMountCount;
	DWORD		dwAllocateCount;
} NTMS_PARTITIONINFORMATIONA;


typedef struct _NTMS_PARTITIONINFORMATIONW {
    NTMS_GUID	PhysicalMedia;
    NTMS_GUID	LogicalMedia;
	DWORD		State;
	WORD		Side;
	DWORD		dwOmidLabelIdLength;	// binary id
	BYTE		OmidLabelId[255];
	WCHAR		szOmidLabelType[64];	// type string
	WCHAR		szOmidLabelInfo[256];	// info string
	DWORD		dwMountCount;
	DWORD		dwAllocateCount;
} NTMS_PARTITIONINFORMATIONW;

enum NtmsPoolType {
	NTMS_POOLTYPE_UNKNOWN			= 0,
	NTMS_POOLTYPE_SCRATCH			= 1,
	NTMS_POOLTYPE_FOREIGN			= 2,
	NTMS_POOLTYPE_IMPORT			= 3,
	NTMS_POOLTYPE_APPLICATION		= 1000
};


enum NtmsAllocationPolicy {
	NTMS_ALLOCATE_FROMSCRATCH = 1
};

enum NtmsDeallocationPolicy {
	NTMS_DEALLOCATE_TOSCRATCH = 1
};

typedef struct _NTMS_MEDIAPOOLINFORMATION {
     DWORD		PoolType;
     NTMS_GUID	MediaType;
	 NTMS_GUID	Parent;
	 DWORD		AllocationPolicy;
	 DWORD		DeallocationPolicy;
	 DWORD		dwMaxAllocates;
	 DWORD		dwNumberOfPhysicalMedia;
	 DWORD		dwNumberOfLogicalMedia;
	 DWORD		dwNumberOfMediaPools;
} NTMS_MEDIAPOOLINFORMATION;

enum NtmsReadWriteCharacteristics {
	NTMS_MEDIARW_UNKNOWN	= 0,
	NTMS_MEDIARW_REWRITABLE	= 1,
	NTMS_MEDIARW_WRITEONCE	= 2,
	NTMS_MEDIARW_READONLY	= 3
};

#define NTMS_VENDORNAME_LENGTH		32
#define NTMS_PRODUCTNAME_LENGTH		32

typedef struct _NTMS_MEDIATYPEINFORMATION {
	DWORD	MediaType;	// MediaTypeCodes
	DWORD	NumberOfSides;
	DWORD	ReadWriteCharacteristics;
	DWORD	DeviceType;
} NTMS_MEDIATYPEINFORMATION;

#ifdef UNICODE
#define _NTMS_DRIVETYPEINFORMATION _NTMS_DRIVETYPEINFORMATIONW
#define NTMS_DRIVETYPEINFORMATION NTMS_DRIVETYPEINFORMATIONW
#else
#define _NTMS_DRIVETYPEINFORMATION _NTMS_DRIVETYPEINFORMATIONA
#define NTMS_DRIVETYPEINFORMATION NTMS_DRIVETYPEINFORMATIONA
#endif

typedef struct _NTMS_DRIVETYPEINFORMATIONA {
	CHAR	szVendor[NTMS_VENDORNAME_LENGTH];
	CHAR	szProduct[NTMS_PRODUCTNAME_LENGTH];
	DWORD	NumberOfHeads;
	DWORD	DeviceType;
} NTMS_DRIVETYPEINFORMATIONA;

typedef struct _NTMS_DRIVETYPEINFORMATIONW {
	WCHAR	szVendor[NTMS_VENDORNAME_LENGTH];
	WCHAR	szProduct[NTMS_PRODUCTNAME_LENGTH];
	DWORD	NumberOfHeads;
	DWORD	DeviceType;
} NTMS_DRIVETYPEINFORMATIONW;

#ifdef UNICODE
#define _NTMS_CHANGERTYPEINFORMATION _NTMS_CHANGERTYPEINFORMATIONW
#define NTMS_CHANGERTYPEINFORMATION NTMS_CHANGERTYPEINFORMATIONW
#else
#define _NTMS_CHANGERTYPEINFORMATION _NTMS_CHANGERTYPEINFORMATIONA
#define NTMS_CHANGERTYPEINFORMATION NTMS_CHANGERTYPEINFORMATIONA
#endif

typedef struct _NTMS_CHANGERTYPEINFORMATIONA {
	CHAR	szVendor[NTMS_VENDORNAME_LENGTH];
	CHAR	szProduct[NTMS_PRODUCTNAME_LENGTH];
	DWORD	DeviceType;
} NTMS_CHANGERTYPEINFORMATIONA;

typedef struct _NTMS_CHANGERTYPEINFORMATIONW {
	WCHAR	szVendor[NTMS_VENDORNAME_LENGTH];
	WCHAR	szProduct[NTMS_PRODUCTNAME_LENGTH];
	DWORD	DeviceType;
} NTMS_CHANGERTYPEINFORMATIONW;

#define NTMS_USERNAME_LENGTH		64
#define NTMS_APPLICATIONNAME_LENGTH	64
#define NTMS_COMPUTERNAME_LENGTH	64


enum NtmsLmOperation {
    NTMS_LM_REMOVE          = 0,
    NTMS_LM_DISABLECHANGER  = 1,
    NTMS_LM_ENABLECHANGER   = 2,
    NTMS_LM_DISABLEDRIVE    = 3,
    NTMS_LM_ENABLEDRIVE     = 4,
    NTMS_LM_DISABLEMEDIA    = 5,
    NTMS_LM_ENABLEMEDIA     = 6,
    NTMS_LM_UPDATEOMID      = 7,
    NTMS_LM_INVENTORY       = 8,
    NTMS_LM_DOORACCESS      = 9,
    NTMS_LM_EJECT           = 10,
    NTMS_LM_EJECTCLEANER    = 11,
    NTMS_LM_INJECT          = 12,
    NTMS_LM_INJECTCLEANER   = 13,
    NTMS_LM_PROCESSOMID     = 14,
    NTMS_LM_CLEANDRIVE      = 15,
    NTMS_LM_DISMOUNT        = 16,
    NTMS_LM_MOUNT           = 17,
    NTMS_LM_WRITESCRATCH    = 18,
    NTMS_LM_CLASSIFY        = 19,
    NTMS_LM_RESERVECLEANER  = 20,
    NTMS_LM_RELEASECLEANER  = 21,
    NTMS_LM_MAXWORKITEM 
};

enum NtmsLmState {
	NTMS_LM_QUEUED		= 0,
	NTMS_LM_INPROCESS	= 1,
	NTMS_LM_PASSED		= 2,
	NTMS_LM_FAILED		= 3,
	NTMS_LM_INVALID		= 4,
	NTMS_LM_WAITING		= 5,
	NTMS_LM_DEFFERED    = 6,
	NTMS_LM_CANCELLED	= 7,
	NTMS_LM_STOPPED		= 8
};

#ifdef UNICODE
#define _NTMS_LIBREQUESTINFORMATION _NTMS_LIBREQUESTINFORMATIONW
#define NTMS_LIBREQUESTINFORMATION NTMS_LIBREQUESTINFORMATIONW
#else
#define _NTMS_LIBREQUESTINFORMATION _NTMS_LIBREQUESTINFORMATIONA
#define NTMS_LIBREQUESTINFORMATION NTMS_LIBREQUESTINFORMATIONA
#endif

typedef struct _NTMS_LIBREQUESTINFORMATIONA {
	DWORD		OperationCode;
	DWORD		OperationOption;
	DWORD		State;
	NTMS_GUID	PartitionId;
	NTMS_GUID	DriveId;
	NTMS_GUID	PhysMediaId;
	NTMS_GUID	Library;
	NTMS_GUID	SlotId;
	SYSTEMTIME	TimeQueued;
	SYSTEMTIME	TimeCompleted;
	CHAR		szApplication[NTMS_APPLICATIONNAME_LENGTH];
	CHAR		szUser[NTMS_USERNAME_LENGTH];
	CHAR		szComputer[NTMS_COMPUTERNAME_LENGTH];
} NTMS_LIBREQUESTINFORMATIONA;

typedef struct _NTMS_LIBREQUESTINFORMATIONW {
	DWORD		OperationCode;
	DWORD		OperationOption;
	DWORD		State;
	NTMS_GUID	PartitionId;
	NTMS_GUID	DriveId;
	NTMS_GUID	PhysMediaId;
	NTMS_GUID	Library;
	NTMS_GUID	SlotId;
	SYSTEMTIME	TimeQueued;
	SYSTEMTIME	TimeCompleted;
	WCHAR		szApplication[NTMS_APPLICATIONNAME_LENGTH];
	WCHAR		szUser[NTMS_USERNAME_LENGTH];
	WCHAR		szComputer[NTMS_COMPUTERNAME_LENGTH];
} NTMS_LIBREQUESTINFORMATIONW;

#define NTMS_MESSAGE_LENGTH		127

enum NtmsOpreqCommand {
	NTMS_OPREQ_UNKNOWN			= 0,
	NTMS_OPREQ_NEWMEDIA			= 1,
	NTMS_OPREQ_CLEANER			= 2,
	NTMS_OPREQ_DEVICESERVICE	= 3,
	NTMS_OPREQ_MOVEMEDIA		= 4,
	NTMS_OPREQ_MESSAGE			= 5
};

enum NtmsOpreqState {
	NTMS_OPSTATE_UNKNOWN		= 0,
	NTMS_OPSTATE_SUBMITTED		= 1,
	NTMS_OPSTATE_ACTIVE			= 2,
	NTMS_OPSTATE_INPROGRESS		= 3,
	NTMS_OPSTATE_REFUSED		= 4,
	NTMS_OPSTATE_COMPLETE		= 5
};

#ifdef UNICODE
#define _NTMS_OPREQUESTINFORMATION _NTMS_OPREQUESTINFORMATIONW
#define NTMS_OPREQUESTINFORMATION NTMS_OPREQUESTINFORMATIONW
#else
#define _NTMS_OPREQUESTINFORMATION _NTMS_OPREQUESTINFORMATIONA
#define NTMS_OPREQUESTINFORMATION NTMS_OPREQUESTINFORMATIONA
#endif

typedef struct _NTMS_OPREQUESTINFORMATIONA {
	DWORD		Request;
	SYSTEMTIME	Submitted;
	DWORD		State;
	CHAR		szMessage[NTMS_MESSAGE_LENGTH];
	DWORD		Arg1Type;
	NTMS_GUID	Arg1;
	DWORD		Arg2Type;
	NTMS_GUID	Arg2;
	CHAR		szApplication[NTMS_APPLICATIONNAME_LENGTH];
	CHAR		szUser[NTMS_USERNAME_LENGTH];
	CHAR		szComputer[NTMS_COMPUTERNAME_LENGTH];
} NTMS_OPREQUESTINFORMATIONA;

typedef struct _NTMS_OPREQUESTINFORMATIONW {
	DWORD		Request;
	SYSTEMTIME	Submitted;
	DWORD		State;
	WCHAR		szMessage[NTMS_MESSAGE_LENGTH];
	DWORD		Arg1Type;
	NTMS_GUID	Arg1;
	DWORD		Arg2Type;
	NTMS_GUID	Arg2;
	WCHAR		szApplication[NTMS_APPLICATIONNAME_LENGTH];
	WCHAR		szUser[NTMS_USERNAME_LENGTH];
	WCHAR		szComputer[NTMS_COMPUTERNAME_LENGTH];
} NTMS_OPREQUESTINFORMATIONW;

#define NTMS_OBJECTNAME_LENGTH	64
#define NTMS_DESCRIPTION_LENGTH 127

#ifdef UNICODE
#define _NTMS_OBJECTINFORMATION _NTMS_OBJECTINFORMATIONW
#define NTMS_OBJECTINFORMATION NTMS_OBJECTINFORMATIONW
#define LPNTMS_OBJECTINFORMATION LPNTMS_OBJECTINFORMATIONW
#else
#define _NTMS_OBJECTINFORMATION _NTMS_OBJECTINFORMATIONA
#define NTMS_OBJECTINFORMATION NTMS_OBJECTINFORMATIONA
#define LPNTMS_OBJECTINFORMATION LPNTMS_OBJECTINFORMATIONA
#endif

enum NtmsOperationalState {
	NTMS_READY  = 0,
	NTMS_NEEDS_SERVICE = 20,
	NTMS_NOT_PRESENT = 21
};

typedef struct _NTMS_OBJECTINFORMATIONA {
	DWORD		dwSize;
	DWORD		dwType;
	SYSTEMTIME	Created;
	SYSTEMTIME	Modified;
	NTMS_GUID	ObjectGuid;
	BOOL		Enabled;
	DWORD		dwOperationalState;
	CHAR		szName[NTMS_OBJECTNAME_LENGTH];
	CHAR		szDescription[NTMS_DESCRIPTION_LENGTH];
#ifdef MIDL_PASS
	[switch_is(dwType)] union {
		[case(NTMS_DRIVE)] 			NTMS_DRIVEINFORMATIONA Drive;
		[case(NTMS_DRIVE_TYPE)]		NTMS_DRIVETYPEINFORMATIONA DriveType;
		[case(NTMS_LIBRARY)]		NTMS_LIBRARYINFORMATION Library;
		[case(NTMS_CHANGER)]		NTMS_CHANGERINFORMATIONA Changer;
		[case(NTMS_CHANGER_TYPE)]	NTMS_CHANGERTYPEINFORMATIONA ChangerType;
		[case(NTMS_STORAGESLOT)]	NTMS_STORAGESLOTINFORMATION StorageSlot;
		[case(NTMS_IEDOOR)]			NTMS_IEDOORINFORMATION IEDoor;
		[case(NTMS_IEPORT)]			NTMS_IEPORTINFORMATION IEPort;
		[case(NTMS_PHYSICAL_MEDIA)]	NTMS_PMIDINFORMATIONA PhysicalMedia;
		[case(NTMS_LOGICAL_MEDIA)]	NTMS_LMIDINFORMATION LogicalMedia;
		[case(NTMS_PARTITION)]		NTMS_PARTITIONINFORMATIONA Partition;
		[case(NTMS_MEDIA_POOL)]		NTMS_MEDIAPOOLINFORMATION MediaPool;
		[case(NTMS_MEDIA_TYPE)]		NTMS_MEDIATYPEINFORMATION MediaType;
		[case(NTMS_LIBREQUEST)]		NTMS_LIBREQUESTINFORMATIONA LibRequest;
		[case(NTMS_OPREQUEST)]		NTMS_OPREQUESTINFORMATIONA OpRequest;
		[default]					;
	} Info;
#else
	union {
		NTMS_DRIVEINFORMATIONA Drive;
		NTMS_DRIVETYPEINFORMATIONA DriveType;
		NTMS_LIBRARYINFORMATION Library;
		NTMS_CHANGERINFORMATIONA Changer;
		NTMS_CHANGERTYPEINFORMATIONA ChangerType;
		NTMS_STORAGESLOTINFORMATION StorageSlot;
		NTMS_IEDOORINFORMATION IEDoor;
		NTMS_IEPORTINFORMATION IEPort;
		NTMS_PMIDINFORMATIONA PhysicalMedia;
		NTMS_LMIDINFORMATION LogicalMedia;
		NTMS_PARTITIONINFORMATIONA Partition;
		NTMS_MEDIAPOOLINFORMATION MediaPool;
		NTMS_MEDIATYPEINFORMATION MediaType;
		NTMS_LIBREQUESTINFORMATIONA LibRequest;
		NTMS_OPREQUESTINFORMATIONA OpRequest;
	} Info;
#endif	// MIDL_PASS
} NTMS_OBJECTINFORMATIONA, *LPNTMS_OBJECTINFORMATIONA;


typedef struct _NTMS_OBJECTINFORMATIONW {
	DWORD		dwSize;
	DWORD		dwType;
	SYSTEMTIME	Created;
	SYSTEMTIME	Modified;
	NTMS_GUID	ObjectGuid;
	BOOL		Enabled;
	DWORD		dwOperationalState;
	WCHAR		szName[NTMS_OBJECTNAME_LENGTH];
	WCHAR		szDescription[NTMS_DESCRIPTION_LENGTH];
#ifdef MIDL_PASS
	[switch_is(dwType)] union {
		[case(NTMS_DRIVE)] 			NTMS_DRIVEINFORMATIONW Drive;
		[case(NTMS_DRIVE_TYPE)]		NTMS_DRIVETYPEINFORMATIONW DriveType;
		[case(NTMS_LIBRARY)]		NTMS_LIBRARYINFORMATION Library;
		[case(NTMS_CHANGER)]		NTMS_CHANGERINFORMATIONW Changer;
		[case(NTMS_CHANGER_TYPE)]	NTMS_CHANGERTYPEINFORMATIONW ChangerType;
		[case(NTMS_STORAGESLOT)]	NTMS_STORAGESLOTINFORMATION StorageSlot;
		[case(NTMS_IEDOOR)]			NTMS_IEDOORINFORMATION IEDoor;
		[case(NTMS_IEPORT)]			NTMS_IEPORTINFORMATION IEPort;
		[case(NTMS_PHYSICAL_MEDIA)]	NTMS_PMIDINFORMATIONW PhysicalMedia;
		[case(NTMS_LOGICAL_MEDIA)]	NTMS_LMIDINFORMATION LogicalMedia;
		[case(NTMS_PARTITION)]		NTMS_PARTITIONINFORMATIONW Partition;
		[case(NTMS_MEDIA_POOL)]		NTMS_MEDIAPOOLINFORMATION MediaPool;
		[case(NTMS_MEDIA_TYPE)]		NTMS_MEDIATYPEINFORMATION MediaType;
		[case(NTMS_LIBREQUEST)]		NTMS_LIBREQUESTINFORMATIONW LibRequest;
		[case(NTMS_OPREQUEST)]		NTMS_OPREQUESTINFORMATIONW OpRequest;
		[default]					;
	} Info;
#else
	union {
		NTMS_DRIVEINFORMATIONW Drive;
		NTMS_DRIVETYPEINFORMATIONW DriveType;
		NTMS_LIBRARYINFORMATION Library;
		NTMS_CHANGERINFORMATIONW Changer;
		NTMS_CHANGERTYPEINFORMATIONW ChangerType;
		NTMS_STORAGESLOTINFORMATION StorageSlot;
		NTMS_IEDOORINFORMATION IEDoor;
		NTMS_IEPORTINFORMATION IEPort;
		NTMS_PMIDINFORMATIONW PhysicalMedia;
		NTMS_LMIDINFORMATION LogicalMedia;
		NTMS_PARTITIONINFORMATIONW Partition;
		NTMS_MEDIAPOOLINFORMATION MediaPool;
		NTMS_MEDIATYPEINFORMATION MediaType;
		NTMS_LIBREQUESTINFORMATIONW LibRequest;
		NTMS_OPREQUESTINFORMATIONW OpRequest;
	} Info;
#endif	// MIDL_PASS
} NTMS_OBJECTINFORMATIONW, *LPNTMS_OBJECTINFORMATIONW;

#endif	// NTMS_NOREDEF

#ifndef MIDL_PASS
//======================================================================
// OBJECT MANAGEMENT APIS
//======================================================================
#ifdef PRE_SEVIL
DWORD WINAPI GetNtmsObjectInformation(
	HANDLE hSession,
	LPNTMS_GUID lpObjectId,
	LPNTMS_OBJECTINFORMATION lpInfo
	);

DWORD WINAPI SetNtmsObjectInformation(
	HANDLE hSession,
	LPNTMS_GUID lpObjectId,
	LPNTMS_OBJECTINFORMATION lpInfo
	);
#endif
// Added by SEvilia
DWORD WINAPI GetNtmsObjectInformationA(
	HANDLE hSession,
	LPNTMS_GUID lpObjectId,
	LPNTMS_OBJECTINFORMATIONA lpInfo
	);

DWORD WINAPI GetNtmsObjectInformationW(
	HANDLE hSession,
	LPNTMS_GUID lpObjectId,
	LPNTMS_OBJECTINFORMATIONW lpInfo
	);

DWORD WINAPI SetNtmsObjectInformationA(
	HANDLE hSession,
	LPNTMS_GUID lpObjectId,
	LPNTMS_OBJECTINFORMATIONA lpInfo
	);

DWORD WINAPI SetNtmsObjectInformationW(
	HANDLE hSession,
	LPNTMS_GUID lpObjectId,
	LPNTMS_OBJECTINFORMATIONW lpInfo
	);
// END of SEVILIA

DWORD WINAPI EnumerateNtmsObject(
	HANDLE hSession,
	const LPNTMS_GUID lpContainerId,
	LPNTMS_GUID lpList,
	LPDWORD lpdwListSize,
	DWORD dwType,
	DWORD dwOptions
	);

DWORD WINAPI DisableNtmsObject(
	HANDLE hSession,
	DWORD dwType,
	LPNTMS_GUID lpObjectId
	);

DWORD WINAPI EnableNtmsObject(
	HANDLE hSession,
	DWORD dwType,
	LPNTMS_GUID lpObjectId
	);

enum NtmsEjectOperation {
	NTMS_EJECT_START	= 0,
	NTMS_EJECT_STOP		= 1
};

DWORD WINAPI EjectNtmsMedia(
	HANDLE hSession,
	LPNTMS_GUID lpMediaId,
	LPNTMS_GUID lpEjectOperation,
	DWORD dwAction
	);

enum NtmsInjectOperation {
	NTMS_INJECT_START	= 0,
	NTMS_INJECT_STOP		= 1
};

DWORD WINAPI InjectNtmsMedia(
	HANDLE hSession,
	LPNTMS_GUID lpLibraryId,
	LPNTMS_GUID lpInjectOperation,
	DWORD dwAction
	);

DWORD WINAPI AccessNtmsLibraryDoor(
	HANDLE hSession,
	LPNTMS_GUID lpLibraryId,
	DWORD dwAction
	);

DWORD WINAPI CleanNtmsDrive(
	HANDLE hSession,
	LPNTMS_GUID lpDriveId
	);

DWORD WINAPI DismountNtmsDrive(
	HANDLE hSession,
	LPNTMS_GUID lpDriveId
	);

DWORD WINAPI InventoryNtmsLibrary(
	HANDLE hSession,
	LPNTMS_GUID lpLibraryId,
	DWORD dwAction
	);

// definitions for the UpdateNtmsOmidInfo ...
#define NTMS_OMID_TYPE_RAW_LABEL	0x01
#define NTMS_OMID_TYPE_FILESYSTEM_INFO  0x02

typedef struct 
{
	WCHAR FileSystemType[64] ;
	WCHAR VolumeName[256] ;
	DWORD SerialNumber ;
} NTMS_FILESYSTEM_INFO ;

DWORD WINAPI UpdateNtmsOmidInfo( 
	HANDLE hSession, 
	LPNTMS_GUID lpMediaId,
	DWORD labelType,
	DWORD numberOfBytes,
	LPVOID lpBuffer
	);

DWORD WINAPI CancelNtmsLibraryRequest(
	HANDLE hSession,
	LPNTMS_GUID lpRequestId
	);

DWORD WINAPI ReserveNtmsCleanerSlot ( 
	HANDLE hSession, 
	LPNTMS_GUID lpLibrary,
	LPNTMS_GUID lpSlot
	);

DWORD WINAPI ReleaseNtmsCleanerSlot ( 
	HANDLE hSession, 
	LPNTMS_GUID lpLibrary
	);

DWORD WINAPI InjectNtmsCleaner ( 
	HANDLE hSession, 
	LPNTMS_GUID lpLibrary,
	LPNTMS_GUID lpInjectOperation,
	DWORD dwNumberOfCleansLeft,
	DWORD dwAction
	);

DWORD WINAPI EjectNtmsCleaner ( 
	HANDLE hSession, 
	LPNTMS_GUID lpLibrary,
	LPNTMS_GUID lpEjectOperation,
	DWORD dwAction
	);

#endif	// MIDL_PASS

#ifndef NTMS_NOREDEF
enum NtmsDriveType {
	NTMS_UNKNOWN_DRIVE = 0	
};

#endif	// NTMS_NOREDEF

#ifndef MIDL_PASS
// Security for NTMS API
DWORD WINAPI GetNtmsObjectSecurity(
	HANDLE hSession,
	LPNTMS_GUID lpObjectId,
	DWORD dwType,
	SECURITY_INFORMATION RequestedInformation,
	PSECURITY_DESCRIPTOR lpSecurityDescriptor,
	DWORD nLength,
	LPDWORD lpnLengthNeeded
	);
	
DWORD WINAPI SetNtmsObjectSecurity(
	HANDLE hSession,
	LPNTMS_GUID lpObjectId,
	DWORD dwType,
	SECURITY_INFORMATION SecurityInformation,
	PSECURITY_DESCRIPTOR lpSecurityDescriptor
	);

// Security Access Control Masks :
// NTMS_USE_ACCESS is required to use an NTMS object.  For example,
// you will need this access to a library in order to mount media
// within it.
// NTMS_MODIFY_ACCESS is required to make changes to an NTMS object.
// For example, you will need modify access in order to change the name
// of an object or change its attributes.
// NTMS_CONTROL_ACCESS is required to control an NTMS object.  For
// example, you will need control access to a library in order to 
// inject media, eject media, clean or open the door.
//
enum NtmsAccessMask {
	NTMS_USE_ACCESS		= 0x1,
	NTMS_MODIFY_ACCESS	= 0x2,
	NTMS_CONTROL_ACCESS	= 0x4
};

// Generic Mappings :
#define NTMS_GENERIC_READ    NTMS_USE_ACCESS
#define NTMS_GENERIC_WRITE   NTMS_USE_ACCESS | NTMS_MODIFY_ACCESS
#define NTMS_GENERIC_EXECUTE NTMS_USE_ACCESS | NTMS_MODIFY_ACCESS | NTMS_CONTROL_ACCESS
#define NTMS_GENERIC_ALL     NTMS_USE_ACCESS | NTMS_MODIFY_ACCESS | NTMS_CONTROL_ACCESS

// Maximum attribute size for NTMS Object attribute API's
#define NTMS_MAXATTR_LENGTH 0x10000

// Object extensions for NTMS API
DWORD WINAPI GetNtmsObjectAttributeA( 
	HANDLE hSession,
	LPNTMS_GUID lpObjectId,
	DWORD dwType,
	LPCSTR lpAttributeName,
	LPVOID lpAttributeData,
	LPDWORD lpAttributeSize
	);

DWORD WINAPI GetNtmsObjectAttributeW( 
	HANDLE hSession,
	LPNTMS_GUID lpObjectId,
	DWORD dwType,
	LPCWSTR lpAttributeName,
	LPVOID lpAttributeData,
	LPDWORD lpAttributeSize
	);

DWORD WINAPI SetNtmsObjectAttributeA(
	HANDLE hSession,
	LPNTMS_GUID lpObjectId,
	DWORD dwType,
	LPCSTR lpAttributeName,
	LPVOID lpAttributeData,
	DWORD dwAttributeSize
	);

DWORD WINAPI SetNtmsObjectAttributeW(
	HANDLE hSession,
	LPNTMS_GUID lpObjectId,
	DWORD dwType,
	LPCWSTR lpAttributeName,
	LPVOID lpAttributeData,
	DWORD AttributeSize
	);

// Operator Requests
DWORD WINAPI SubmitNtmsOperatorRequestW( 
	HANDLE hSession,
	DWORD dwRequest,
	LPCWSTR lpMessage,
	LPNTMS_GUID lpArg1Id,
	LPNTMS_GUID lpArg2Id,
	LPNTMS_GUID lpRequestId
	);

DWORD WINAPI SubmitNtmsOperatorRequestA( 
	HANDLE hSession,
	DWORD dwRequest,
	LPCSTR lpMessage,
	LPNTMS_GUID lpArg1Id,
	LPNTMS_GUID lpArg2Id,
	LPNTMS_GUID lpRequestId
	);

DWORD WINAPI WaitForNtmsOperatorRequest( 
	HANDLE hSession,
	LPNTMS_GUID lpRequestId,
	DWORD dwTimeout
	);

DWORD WINAPI CancelNtmsOperatorRequest(
	HANDLE hSession,
	LPNTMS_GUID lpRequestId
	);

DWORD WINAPI SatisfyNtmsOperatorRequest(
	HANDLE hSession,
	LPNTMS_GUID lpRequestId
	);

#endif	// MIDL_PASS

#ifndef NTMS_NOREDEF

enum NtmsNotificationOperations {
	NTMS_OBJ_UPDATE = 1,
	NTMS_OBJ_INSERT = 2,
	NTMS_OBJ_DELETE = 3
};

// object notification
typedef struct _NTMS_NOTIFICATIONINFORMATION {
	DWORD dwOperation;
	NTMS_GUID ObjectId;
} NTMS_NOTIFICATIONINFORMATION, *LPNTMS_NOTIFICATIONINFORMATION;

#endif	// NTMS_NOREDEF

#ifndef MIDL_PASS

DWORD WINAPI ImportNtmsDatabase(
	HANDLE hSession
	);

DWORD WINAPI ExportNtmsDatabase(
	HANDLE hSession
	);

#endif	// MIDL_PASS

#ifndef MIDL_PASS

HANDLE WINAPI OpenNtmsNotification( 
	HANDLE hSession,
	DWORD dwType
	);

DWORD WINAPI WaitForNtmsNotification( 
//	HANDLE hSession,					//SEVILIA
	HANDLE hNotification,
	LPNTMS_NOTIFICATIONINFORMATION lpNotificationInformation,
	DWORD dwTimeout
	);

DWORD WINAPI CloseNtmsNotification( 
//	HANDLE hSession,					//SEVILIA
	HANDLE hNotification
	);

#endif	// MIDL_PASS

#ifdef __cplusplus
} // end extern "C"
#endif

#pragma pack()

#endif // _INCL_NTMSAPI_H_
