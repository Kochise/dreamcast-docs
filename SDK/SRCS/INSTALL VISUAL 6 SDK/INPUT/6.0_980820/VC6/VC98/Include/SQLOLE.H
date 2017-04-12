/////////////////////////////////////////////////////////////////////////////////////////
// Header file for SQLOLE C/C++ Client Component Object interfaces.
// Copyright 1994-1995 Microsoft Corporation.
/////////////////////////////////////////////////////////////////////////////////////////
#ifndef _SQLOLE_H_
#define _SQLOLE_H_

// SQLOLE versions supported for this header file.  
#define SQLOLEVERSION_600		0x00060000
#define SQLOLEVERSION_650		0x00063200

// Current version of sqlole for this header file (matches sp_MSSQLOLE_version).
#define SQLOLEVERSION_CURRENT	SQLOLEVERSION_650

/////////////////////////////////////////////////////////////////////////////////////////
// Constant enumerations.
/////////////////////////////////////////////////////////////////////////////////////////
#ifndef _SQLOLE_CONSTANTS_
#define _SQLOLE_CONSTANTS_

#ifdef _SQLOLE_ODL_		// Generate helpids if in ODL file.
#define SQLOLE_HELPID(id) [helpcontext(H_##id)]
#else
#define SQLOLE_HELPID(id)
#endif

typedef SQLOLE_HELPID(SQLOLE_OBJECT_TYPE) enum {
	SQLOLEObj_Unknown = 16384,		// Make it the only bit set
	SQLOLEObj_Application = 0,

	// Database objects, value is power(2, sysobjects.sysstat & 0x0f), plus UDDTs in 0.
	// These values can be bitmasked together for object listings.
	SQLOLEObj_UserDefinedDatatype = 1,
	SQLOLEObj_SystemTable = 2,
	SQLOLEObj_View = 4,
	SQLOLEObj_UserTable = 8,
	SQLOLEObj_StoredProcedure = 16,
	SQLOLEObj_Default = 64,
	SQLOLEObj_Rule = 128,
	SQLOLEObj_Trigger = 256,
	SQLOLEObj_AllDatabaseUserObjects = 0x01fd,
	SQLOLEObj_AllDatabaseObjects = 0x01ff,

	// Other Database objects (not in sysobjects)
	SQLOLEObj_SystemDatatype = 10021,
	SQLOLEObj_User = 10022,
	SQLOLEObj_Group = 10023,
	SQLOLEObj_Index = 10024,
	SQLOLEObj_Key = 10025,
	SQLOLEObj_Column = 10026,
	SQLOLEObj_DBObject = 10027,
	SQLOLEObj_DBOption = 10028,
	SQLOLEObj_ProcedureParameter = 10029,
	SQLOLEObj_Permission = 10033,
	SQLOLEObj_IntegratedSecurity = 10034,
	SQLOLEObj_Check = 10035,
	SQLOLEObj_DRIDefault = 10036,

	// Objects not in databases.
	SQLOLEObj_SQLServer = 10050,
	SQLOLEObj_Database = 10051,
	SQLOLEObj_Device = 10052,
	SQLOLEObj_Login = 10054,
	SQLOLEObj_Language = 10055,
	SQLOLEObj_RemoteServer = 10056,
	SQLOLEObj_RemoteLogin = 10057,

	SQLOLEObj_Configuration = 10059,
	SQLOLEObj_ConfigValue = 10060,
	SQLOLEObj_AlertSystem = 10061,
	SQLOLEObj_Executive = 10062,
	SQLOLEObj_QueryResults = 10063,
	SQLOLEObj_TransactionLog = 10064,
	SQLOLEObj_Registry = 10065,
	SQLOLEObj_Transfer = 10066,
	SQLOLEObj_Backup = 10067,
	SQLOLEObj_Task = 10068,
	SQLOLEObj_Alert = 10069,
	SQLOLEObj_Operator = 10070,
	SQLOLEObj_HistoryFilter = 10071,
	SQLOLEObj_Publication = 10072,
	SQLOLEObj_Article = 10073,
	SQLOLEObj_Subscription = 10074,
	SQLOLEObj_SubscriberInfo = 10075,
	SQLOLEObj_AutoProperty = 10076,		// Automation property or properties collection.
	SQLOLEObj_ServerGroup = 10077,
	SQLOLEObj_RegisteredServer = 10078,
	SQLOLEObj_BulkCopy = 10079
} SQLOLE_OBJECT_TYPE;

typedef SQLOLE_HELPID(SQLOLE_KEY_TYPE) enum {
	SQLOLEKey_Unknown = 0,
	SQLOLEKey_Primary = 1,
	SQLOLEKey_Unique = 2,
	SQLOLEKey_Foreign = 3
} SQLOLE_KEY_TYPE;

typedef SQLOLE_HELPID(SQLOLE_DEVICE_TYPE) enum {
	SQLOLEDevice_Unknown = 100,
	SQLOLEDevice_Database = 0,
	SQLOLEDevice_DiskDump = 2,
	SQLOLEDevice_FloppyADump = 3,
	SQLOLEDevice_FloppyBDump = 4,
	SQLOLEDevice_TapeDump = 5,
	SQLOLEDevice_PipeDump = 6,
	SQLOLEDevice_CDROM = 7
} SQLOLE_DEVICE_TYPE;

typedef SQLOLE_HELPID(SQLOLE_MIRROR_TYPE) enum {
	// Mirror states:
	// 	None = no mirror specified
	//	Inactive = mirror specified but not active
	//  RunningOnMirror = mirror device is functioning as the active device (after SwitchToMirrorTemp)
	//	Active = mirror is specified and actively mirroring the device.
	SQLOLEMirror_None = 0,
	SQLOLEMirror_Inactive = 64,
	SQLOLEMirror_RunningOnMirror = 320,
	SQLOLEMirror_Active = 576
} SQLOLE_MIRROR_TYPE;

typedef SQLOLE_HELPID(SQLOLE_PRIVILEGE_TYPE) enum {
	SQLOLEPriv_Unknown = 0,

	// Privilege values, different from sysprotects as we need to bitmask.
	// Object privileges.
	SQLOLEPriv_Select = 1,
	SQLOLEPriv_Insert = 2,
	SQLOLEPriv_Update = 4,
	SQLOLEPriv_Delete = 8,
	SQLOLEPriv_Execute = 16,
	SQLOLEPriv_References = 32,
	SQLOLEPriv_AllObjectPrivs = 63,
	
	// Database (statement) privileges.
	SQLOLEPriv_CreateTable = 128,
	SQLOLEPriv_CreateDatabase = 256,
	SQLOLEPriv_CreateView = 512,
	SQLOLEPriv_CreateProcedure = 1024,
	SQLOLEPriv_DumpDatabase = 2048,
	SQLOLEPriv_CreateDefault = 4096,
	SQLOLEPriv_DumpTransaction = 8192,
	SQLOLEPriv_CreateRule = 16384,
	SQLOLEPriv_AllDatabasePrivs = 32640
} SQLOLE_PRIVILEGE_TYPE;

typedef SQLOLE_HELPID(SQLOLE_PROCEDURE_TYPE) enum {
	SQLOLEProc_Unknown = 0,
	SQLOLEProc_Standard = 1,
	SQLOLEProc_Extended = 2,
	SQLOLEProc_Macro = 3,
	SQLOLEProc_ReplicationFilter = 4
} SQLOLE_PROCEDURE_TYPE;

// Trigger types may be OR'd together.
typedef SQLOLE_HELPID(SQLOLE_TRIGGER_TYPE) enum {
	SQLOLETrig_Unknown = 0,
	SQLOLETrig_Insert = 1,
	SQLOLETrig_Update = 2,
	SQLOLETrig_Delete = 4,
	SQLOLETrig_All = 7
} SQLOLE_TRIGGER_TYPE;

typedef SQLOLE_HELPID(SQLOLE_INDEX_TYPE) enum {							// SQLOLE Internal:  sync with ntinc\index.h
	// Index type values as in sysindexes.status.
	SQLOLEIndex_Default = 0x0000,
	SQLOLEIndex_IgnoreDupKey = 0x0001,
	SQLOLEIndex_Unique = 0x0002,
	SQLOLEIndex_IgnoreDupRow = 0x0004,
	SQLOLEIndex_Clustered = 0x0010,
	SQLOLEIndex_AllowDupRow = 0x0040,
	SQLOLEIndex_SortedData = 0x0200,
	SQLOLEIndex_SortedDataReorg = 0x2000,	// 6.0-only; sorted-data with reorganization
	SQLOLEIndex_Valid = 0x2257,				// Any of foregoing (writable) types
	SQLOLEIndex_DRIPrimaryKey = 0x0800,		// 6.0-only, readonly; DRI-generated types
	SQLOLEIndex_DRIUniqueKey = 0x1000,
	SQLOLEIndex_DRIIndex = 0x1800			// Index implements DRI (DRIPrimaryKey | DRIUniqueKey)
} SQLOLE_INDEX_TYPE;

typedef SQLOLE_HELPID(SQLOLE_QUERY_DATATYPE) enum {
   // Indexed as per ..\common\inc\sql.hpp and sqlfront.h datatype constants.
	SQLOLE_DTypeUnknown = 0,
	SQLOLE_DTypeChar 	= 0x2f,
	SQLOLE_DTypeText 	= 0x23,
	SQLOLE_DTypeVarchar 	= 0x27,
	SQLOLE_DTypeVarBinary= 0x25,
	SQLOLE_DTypeBinary 	= 0x2d,
	SQLOLE_DTypeImage 	= 0x22,
	SQLOLE_DTypeFloat4 	= 0x3b,
	SQLOLE_DTypeFloat8 	= 0x3e,
	SQLOLE_DTypeInt1 	= 0x30,
	SQLOLE_DTypeInt2 	= 0x34,
	SQLOLE_DTypeInt4		= 0x38,
	SQLOLE_DTypeMoney4	= 0x7a,
	SQLOLE_DTypeMoney	= 0x3c,
	SQLOLE_DTypeDateTime	= 0x3d,
	SQLOLE_DTypeDateTime4= 0x3a,
	SQLOLE_DTypeBit		= 0x32
} SQLOLE_QUERY_DATATYPE;

typedef SQLOLE_HELPID(SQLOLE_AUDIT_TYPE) enum {
	SQLOLEAudit_None = 0,
	SQLOLEAudit_Success = 1,
	SQLOLEAudit_Failure = 2,
	SQLOLEAudit_All = 3
} SQLOLE_AUDIT_TYPE;

typedef SQLOLE_HELPID(SQLOLE_SECURITY_TYPE) enum {
	SQLOLESecurity_Min = 0,
	SQLOLESecurity_Normal = 0,
	SQLOLESecurity_Integrated = 1,
	SQLOLESecurity_Mixed = 2,
	SQLOLESecurity_Max = 2
} SQLOLE_SECURITY_TYPE;

typedef SQLOLE_HELPID(SQLOLE_MEDIA_TYPE) enum {
	SQLOLEMedia_Floppy = 1,
	SQLOLEMedia_FixedDisk = 2,
	SQLOLEMedia_Tape = 4,
	SQLOLEMedia_CDROM = 8,
	SQLOLEMedia_All = 15
} SQLOLE_MEDIA_TYPE;

typedef SQLOLE_HELPID(SQLOLE_PERFMON_TYPE) enum {
	SQLOLEPerfmon_None = 1000,					// No perfmon integration
	SQLOLEPerfmon_MinSet = 0,
	SQLOLEPerfmon_Continuous = 0,
	SQLOLEPerfmon_OnDemand = 1,
	SQLOLEPerfmon_MaxSet = 1
} SQLOLE_PERFMON_TYPE;

typedef SQLOLE_HELPID(SQLOLE_STARTSRV_TYPE) enum {
	SQLOLEStart_NoServiceControl = 1,
	SQLOLEStart_NTErrorLogging = 2,
	SQLOLEStart_SingleUser = 4,
	SQLOLEStart_StartAndConnect = 8,
	SQLOLEStart_RealTime = 16,
	SQLOLEStart_Defaults = 10					// ServiceControl, StartAndConnect, and NTErrorLogging
} SQLOLE_STARTSRV_TYPE;

typedef SQLOLE_HELPID(SQLOLE_DBSTATUS_TYPE) enum {
	SQLOLEDBStat_Normal = 0x0000,
	SQLOLEDBStat_Loading = 0x0020,
	SQLOLEDBStat_Recovering = 0x00c0,			// 0x40 | 0x80
	SQLOLEDBStat_Suspect = 0x0100,
	SQLOLEDBStat_Offline = 0x0200,
	SQLOLEDBStat_Inaccessible = 0x03e0,			// Loading | Recovering | Suspect | Offline
	SQLOLEDBStat_EmergencyMode = 0x8000,
	SQLOLEDBStat_All = 0x83e0
} SQLOLE_DBSTATUS_TYPE;

typedef SQLOLE_HELPID(SQLOLE_COPYDATA_TYPE) enum {
	SQLOLECopyData_False = 0,
	SQLOLECopyData_Replace = 1,
	SQLOLECopyData_Append = 2
} SQLOLE_COPYDATA_TYPE;

typedef SQLOLE_HELPID(SQLOLE_DATAFILE_TYPE) enum {
	// Bulk-copy datafile options (Table/View.Export and Table.Import).  These are mutually exclusive.
	SQLOLEDataFile_CommaDelimitedChar = 		0x00000001,	// ColumnDelimiter == Comma, RowDelimiter == <CRLF>
	SQLOLEDataFile_Default = 					0x00000001,	// Default == csv
	SQLOLEDataFile_TabDelimitedChar = 			0x00000002,	// ColumnDelimiter == <TAB>, RowDelimiter == <CRLF>
	SQLOLEDataFile_SpecialDelimitedChar = 		0x00000003,	// Set BulkCopy.ColumnDelimiter and .RowDelimiter
	SQLOLEDataFile_NativeFormat = 				0x00000004,	// Use native datatype formats
	SQLOLEDataFile_UseFormatFile = 				0x00000005,	// Use an existing format file.
} SQLOLE_DATAFILE_TYPE;

typedef SQLOLE_HELPID(SQLOLE_STATUSINFO_TYPE) enum {
	SQLOLEStatInfo_Unknown = 0,					// Initialization value, not valid as a parameter
	SQLOLEStatInfo_DatabaseStatus = 0x0001,		// Database.Status
	SQLOLEStatInfo_DatabaseSpace = 0x0002,		// Database.SpaceAvailable
	SQLOLEStatInfo_AutoVerifyConnection = 0x0004,	// Server.VerifyConnection done automatically.
	SQLOLEStatInfo_All = 0x0007					// All the foregoing
} SQLOLE_STATUSINFO_TYPE;

typedef SQLOLE_HELPID(SQLOLE_SCRIPT_TYPE) enum {
	// What's included in the Script method output.
	SQLOLEScript_Default = 0x0004,				// Object creation only
	SQLOLEScript_Drops = 0x0001,				// Include object drops
	SQLOLEScript_ObjectPermissions = 0x0002,	// Include object permissions
	SQLOLEScript_PrimaryObject = 0x0004,		// Include object creation
	SQLOLEScript_ClusteredIndexes = 0x0008,		// Include clustered index creation (table only)
	SQLOLEScript_Triggers = 0x0010,				// Include trigger creation (table only)
	SQLOLEScript_DatabasePermissions = 0x0020,	// Database (statement) permissions
	SQLOLEScript_Permissions = 0x0022,			// Both database and object permissions (for scripting users).
	SQLOLEScript_ToFileOnly = 0x0040,			// If not set, a string is returned (if file nonnull, both are done)
	SQLOLEScript_Bindings = 0x0080,				// Include rule/default bindings (table only)
	SQLOLEScript_AppendToFile = 0x0100,			// Append to output file if it already exists.
	SQLOLEScript_NoDRI = 0x0200,				// Do not include DRI (intended for use if targeting pre-6.0 server with scripts)
	SQLOLEScript_UDDTsToBaseType = 0x0400,		// Convert UserDefinedDatatypes to base type when creating columns (table only)
	SQLOLEScript_42Syntax = 0x0800,				// Use SQL 4.2x syntax (convert numerics, skip identity, etc.)
	SQLOLEScript_ODBCSyntax = 0x0E00,			// Use ODBC syntax (strip SQL-specifics); includes NoDRI, UDDTsToBaseTypes.
	SQLOLEScript_IncludeIfNotExists = 0x1000,	// Include "if not exists" on object creation.
	SQLOLEScript_NonClusteredIndexes = 0x2000,	// Include nonclustered index creation (table only)
	SQLOLEScript_Indexes = 0x12008,				// Include all index creation (table only)
	SQLOLEScript_Aliases = 0x4000,				// For users, script aliases
	SQLOLEScript_NoCommandTerm = 0x8000,		// Do not append "GO" to commands.
	SQLOLEScript_DRIIndexes = 0x10000,			// Script DRI-generated indexes as indexes if NoDRI is specified.
	SQLOLEScript_IncludeHeaders = 0x20000,		// Include descriptive header in individual object script output.
	SQLOLEScript_OwnerQualify = 0x40000,		// Owner-qualify DROP statements (and CREATE where possible).
	SQLOLEScript_TimestampToBinary = 0x80000,	// Convert timestamp columns to binary(8) (for replication, etc.).
	SQLOLEScript_SortedData = 0x100000, 		// If the index or constraint was clustered, append sorted_data
	SQLOLEScript_SortedDataReorg = 0x200000,	// Same as SQLOLEScript_SortedData, but Reorg is used to preserve fillfactor.

	SQLOLEScript_TransferDefault = 0x670ff,		//The default script type for Transfer. This is combination of following flags:
												//SQLOLEScript_PrimaryObject | SQLOLEScript_Bindings | SQLOLEScript_ClusteredIndexes | SQLOLEScript_NonClusteredIndexes | 
												//SQLOLEScript_Triggers| SQLOLEScript_ToFileOnly|SQLOLEScript_Permissions| SQLOLEScript_IncludeHeaders|
												//SQLOLEScript_Aliases|SQLOLEScript_IncludeIfNotExists|SQLOLEScript_OwnerQualify

	// DRI-restrictive flags.  These may be combined with PrimaryObject as desired.
	// These are to be used to include or exclude specific DRI components, such
	// as for multi-pass scripting.
	SQLOLEScript_DRI_NonClustered = 	0x00400000,
	SQLOLEScript_DRI_Clustered = 		0x00800000,
	SQLOLEScript_DRI_Checks = 			0x01000000,
	SQLOLEScript_DRI_Defaults = 		0x02000000,
	SQLOLEScript_DRI_UniqueKeys = 		0x04000000,
	SQLOLEScript_DRI_ForeignKeys = 		0x08000000,
	SQLOLEScript_DRI_PrimaryKey = 		0x10000000,
	SQLOLEScript_DRI_AllKeys =			0x1c000000, // Bitmask of all key types (PK, FK, Unique).
	SQLOLEScript_DRI_AllConstraints = 	0x1f000000,	// Bitmask of all constraint types (PK, FK, Unique, Check, Default).
	SQLOLEScript_DRI_All = 				0x1fc00000,	// All the foregoing (specifying this and not PrimaryObject gets just DRI output).

	SQLOLEScript_DRIWithNoCheck = 		0x20000000,	// Script DRI with nocheck (not included in _DRI_All).
	SQLOLEScript_NoIdentity = 			0x40000000,	// Script with no IDENTITY attribute (e.g. for Replication).

	// Scripts with quoted identifiers. Also will cause Transfer to SET QUOTED_IDENTIFIER ON on the destination.
	SQLOLEScript_UseQuotedIdentifiers =	0x80000000
} SQLOLE_SCRIPT_TYPE;

typedef SQLOLE_HELPID(SQLOLE_XFRSCRIPTMODE_TYPE) enum {
	// How many files the XFR Script is to written to.
	SQLOLEXfrFile_Default = 0x0001,	
	SQLOLEXfrFile_SummaryFiles	= 0x0001,		// One files per class of objects transferred/dropped
	SQLOLEXfrFile_SingleFile	= 0x0002,		// All scripts go to same file
	SQLOLEXfrFile_SingleFilePerObject = 0x0004	// One file per object
} SQLOLE_XFRSCRIPTMODE_TYPE;

typedef SQLOLE_HELPID(SQLOLE_DEPENDENCY_TYPE) enum {
	SQLOLEDep_Parents = 0,						// Default:  return all parents of input object
	SQLOLEDep_FullHierarchy = 0x10000,			// Return full hierarchy; multiple rows of object and parents/children
	SQLOLEDep_OrderDescending = 0x20000,		// Order return in descending order
	SQLOLEDep_Children = 0x40000,				// Return children of input object
	SQLOLEDep_ReturnInputObject = 0x80000,		// Include input object in the return set
	SQLOLEDep_FirstLevelOnly = 0x100000,		// Return only immediate parents/children
	SQLOLEDep_DRIOnly = 0x200000,				// Return DRI dependencies only.
	SQLOLEDep_Valid = 0x3f0000					// All valid options.
} SQLOLE_DEPENDENCY_TYPE;

typedef SQLOLE_HELPID(SQLOLE_OBJSORT_TYPE) enum {
	SQLOLEObjSort_Name = 0,
	SQLOLEObjSort_Type = 1,
	SQLOLEObjSort_Owner = 2,
	SQLOLEObjSort_Date = 3
} SQLOLE_OBJSORT_TYPE;

// May be bitmasked.
typedef SQLOLE_HELPID(SQLOLE_COMPLETION_TYPE) enum {
	SQLOLEComp_Unknown = 0x1000,		// Only bit set
	SQLOLEComp_None = 0x0000,
	SQLOLEComp_Success = 0x0001,
	SQLOLEComp_Failure = 0x0002,
	SQLOLEComp_Always = 0x0003,
	SQLOLEComp_Running = 0x0004,
	SQLOLEComp_Aborted = 0x0008,
	SQLOLEComp_Skipped = 0x0010,
	SQLOLEComp_All = 0x001f
} SQLOLE_COMPLETION_TYPE;

typedef SQLOLE_HELPID(SQLOLE_EVENT_TYPE) enum {
	SQLOLEEvent_Unknown = 0x0000,
	SQLOLEEvent_Info = 0x0001,
	SQLOLEEvent_Warning = 0x0002,
	SQLOLEEvent_Error = 0x0004,
	SQLOLEEvent_AuditSuccess = 0x0008,
	SQLOLEEvent_AuditFailure = 0x0010,
	SQLOLEEvent_All = 0x001f
} SQLOLE_EVENT_TYPE;

typedef SQLOLE_HELPID(SQLOLE_SVCSTATUS_TYPE) enum {
	SQLOLESvc_Unknown = 0,
	SQLOLESvc_Running = 1,
	SQLOLESvc_Paused = 2,
	SQLOLESvc_Stopped = 3,
	SQLOLESvc_Starting = 4,
	SQLOLESvc_Stopping = 5,
	SQLOLESvc_Continuing = 6,
	SQLOLESvc_Pausing = 7
} SQLOLE_SVCSTATUS_TYPE;

typedef SQLOLE_HELPID(SQLOLE_FREQUENCY_TYPE) enum {							// SQLOLE Internal:  sync with qsched.h
	SQLOLEFreq_Unknown = 0x0000,
	SQLOLEFreq_OneTime = 0x0001,
	SQLOLEFreq_OnDemand = 0x0002,
	SQLOLEFreq_Daily = 0x0004,
	SQLOLEFreq_Weekly = 0x0008,
	SQLOLEFreq_Monthly = 0x0010,
	SQLOLEFreq_MonthlyRelative = 0x0020,
	SQLOLEFreq_Autostart = 0x0040,
	SQLOLEFreq_Recurring = 0x007c,		// Any recurring type
	SQLOLEFreq_Valid = 0x007f			// All valid frequency types
} SQLOLE_FREQUENCY_TYPE;

typedef SQLOLE_HELPID(SQLOLE_FREQSUB_TYPE) enum {							// SQLOLE Internal:  sync with qsched.h
	SQLOLEFreqSub_Unknown = 0x0000,
	SQLOLEFreqSub_Once = 0x0001,
	SQLOLEFreqSub_Minute = 0x0004,
	SQLOLEFreqSub_Hour = 0x0008,
	SQLOLEFreqSub_Valid = 0x000d		// All valid frequency subtypes
} SQLOLE_FREQSUB_TYPE;

typedef SQLOLE_HELPID(SQLOLE_FREQRELATIVE_TYPE) enum {						// SQLOLE Internal:  sync with qsched.h
	SQLOLEFreqRel_Unknown = 0x0000,
	SQLOLEFreqRel_First = 0x0001,
	SQLOLEFreqRel_Second = 0x0002,
	SQLOLEFreqRel_Third = 0x0004,
	SQLOLEFreqRel_Fourth = 0x0008,
	SQLOLEFreqRel_Last = 0x0010,
	SQLOLEFreqRel_Valid = 0x001f		// All valid Relative frequencies.
} SQLOLE_FREQRELATIVE_TYPE;

typedef SQLOLE_HELPID(SQLOLE_WEEKDAY_TYPE) enum {							// SQLOLE Internal:  sync with qsched.h
	// Specify for SQLOLEFreq_Weekly; bitmask
	SQLOLEWeek_Unknown = 0x0000,
	SQLOLEWeek_Sunday = 0x0001,
	SQLOLEWeek_Monday = 0x0002,
	SQLOLEWeek_Tuesday = 0x0004,
	SQLOLEWeek_Wednesday = 0x0008,
	SQLOLEWeek_Thursday = 0x0010,
	SQLOLEWeek_Friday = 0x0020,
	SQLOLEWeek_Saturday = 0x0040,
	SQLOLEWeek_WeekDays = 0x003e,		// Monday - Friday
	SQLOLEWeek_WeekEnds = 0x0041,		// Saturday - Sunday
	SQLOLEWeek_EveryDay = 0x007f
} SQLOLE_WEEKDAY_TYPE;

typedef SQLOLE_HELPID(SQLOLE_MONTHDAY_TYPE) enum {							// SQLOLE Internal:  sync with qsched.h
	// Specify for SQLOLEFreq_MonthlyRelative; single-value.
	// This is the relative interval SQLOLE_FREQRELATIVE_TYPE;
	// e.g., on the xth Monday of the month.
	SQLOLEMonth_Unknown = 0,
	SQLOLEMonth_MinValid = 1,
	SQLOLEMonth_Sunday = 1,
	SQLOLEMonth_Monday = 2,
	SQLOLEMonth_Tuesday = 3,
	SQLOLEMonth_Wednesday = 4,
	SQLOLEMonth_Thursday = 5,
	SQLOLEMonth_Friday = 6,
	SQLOLEMonth_Saturday = 7,
	SQLOLEMonth_Day = 8,				// xth day
	SQLOLEMonth_WeekDay = 9,			// xth weekday
	SQLOLEMonth_WeekEndDay = 10,		// xth weekendday
	SQLOLEMonth_MaxValid = 10
} SQLOLE_MONTHDAY_TYPE;

typedef SQLOLE_HELPID(SQLOLE_SRVOPTION_TYPE) enum {
	SQLOLESrvOpt_Unknown = 0x0000,
	SQLOLESrvOpt_RPC = 0x0001,
	SQLOLESrvOpt_Publisher = 0x0002,
	SQLOLESrvOpt_Subscriber = 0x0004,
	SQLOLESrvOpt_Distributor = 0x0008,
	SQLOLESrvOpt_DistPublisher = 0x0010,	// Separate from Publisher and Distributor; dpub bit set
	SQLOLESrvOpt_ODBCDatasource = 0x0020,	// Server is an ODBC datasource
	SQLOLESrvOpt_Valid = 0x003f
} SQLOLE_SRVOPTION_TYPE;

typedef SQLOLE_HELPID(SQLOLE_SUBSCRIBERINFO_TYPE) enum {
	SQLOLESubInfo_SQLServer = 0x00000000,		// Current version of MS SQLServer.
	SQLOLESubInfo_ODBCDatasource = 0x00000001	// ODBC Datasource
} SQLOLE_SUBSCRIBERINFO_TYPE;

typedef SQLOLE_HELPID(SQLOLE_TABLEATT_TYPE) enum {
	// Values from sysobjects.category.
	SQLOLETabAtt_Identity = 	0x0001,		// Table has an identity column
	SQLOLETabAtt_SystemObject =	0x0002,		// Table is a Microsoft system-required object
	SQLOLETabAtt_ForeignKey = 	0x0004, 	// Table has a foreign key
	SQLOLETabAtt_Referenced = 	0x0008,		// Table is referenced by another table's foreign key
	SQLOLETabAtt_Published = 	0x0020,		// Table is published
	SQLOLETabAtt_Replicated =	0x0040,		// Table has an active subscriber
	SQLOLETabAtt_Check = 		0x0080,		// Table has a check constraint
	SQLOLETabAtt_Replica = 		0x0100,		// Table is actively subscribed to a publisher
	SQLOLETabAtt_PrimaryKey = 	0x0200,		// Table has a primary key
	SQLOLETabAtt_Unique = 		0x0400,		// Table has a unique constraint
	SQLOLETabAtt_Default = 		0x0800,		// Table has a DRI default
	SQLOLETabAtt_ReplCheck = 	0x1000,		// Table has a check constraint that excludes replication
	SQLOLETabAtt_HasConstraint =0x1c84		// Table has at least one DRI constraint
} SQLOLE_TABLEATT_TYPE;

typedef SQLOLE_HELPID(SQLOLE_INITIALSYNC_TYPE) enum {
	SQLOLEInitSync_Unknown = 10,     // Pick your favourite invalid number
	SQLOLEInitSync_Min = 0,
	SQLOLEInitSync_BCPNative = 0,
	SQLOLEInitSync_BCPChar = 1,
	SQLOLEInitSync_TableDumpLoad = 2,
	SQLOLEInitSync_Max = 2
} SQLOLE_INITIALSYNC_TYPE;

typedef SQLOLE_HELPID(SQLOLE_REPFREQ_TYPE) enum {
	SQLOLERepFreq_Unknown = 1000,		// Tinyint out-of-range
	SQLOLERepFreq_Min = 0,
	SQLOLERepFreq_Continuous = 0,
	SQLOLERepFreq_Snapshot = 1,
	SQLOLERepFreq_Max = 1
} SQLOLE_REPFREQ_TYPE;

typedef SQLOLE_HELPID(SQLOLE_REPLICATION_TYPE) enum {
	SQLOLERep_Unknown = 0x100, 						// Tinyint out-of-range
	SQLOLERep_LogBased = 0x0001,					// Base for all LogBased replication types.
	SQLOLERep_ManualFilterProc = 0x0002,			// Bit for manually created (not auto-generated) filter proc
	SQLOLERep_LogBasedManualFilterProc = 0x0003,	// Log based, with manually created sync view.
	SQLOLERep_ManualSyncView = 0x0004,				// Bit for manually created (not auto-generated) filter proc.
	SQLOLERep_LogBasedManualSyncView = 0x0005,		// Log based, with manually created filter proc.
	SQLOLERep_LogBasedManualBoth = 0x0007,			// Log based, with manually created sync view and filter proc.
	SQLOLERep_Valid = 7
} SQLOLE_REPLICATION_TYPE;

typedef SQLOLE_HELPID(SQLOLE_SUBSYNC_TYPE) enum {
	SQLOLESubSync_Unknown = 1000,		// Tinyint out-of-range
	SQLOLESubSync_Min = 0,
	SQLOLESubSync_Manual = 0,
	SQLOLESubSync_Auto = 1,
	SQLOLESubSync_Default = 1,			// Auto is default.
	SQLOLESubSync_None = 2,
	SQLOLESubSync_Max = 2
} SQLOLE_SUBSYNC_TYPE;

typedef SQLOLE_HELPID(SQLOLE_PREARTICLE_TYPE) enum {
	// Article pre-creation methods on destination table.
	SQLOLEPreArt_Min = 0,
	SQLOLEPreArt_None = 0,				// Do nothing
	SQLOLEPreArt_DropTable = 1,			// Drop and re-create table
	SQLOLEPreArt_DeleteRows = 2,		// Delete rows (logged)
	SQLOLEPreArt_TruncateTable = 3,		// Truncate table (nonlogged)
	SQLOLEPreArt_Max = 3
} SQLOLE_PREARTICLE_TYPE;

typedef SQLOLE_HELPID(SQLOLE_SUBSTATUS_TYPE) enum {
	SQLOLESubStat_Unknown = 1000,		// Tinyint out-of-range
	SQLOLESubStat_Default = 1000,		// Use default
	SQLOLESubStat_Min = 0,
	SQLOLESubStat_Inactive = 0,
	SQLOLESubStat_Unsynced = 1,
	SQLOLESubStat_Active = 2,
	SQLOLESubStat_Max = 2
} SQLOLE_SUBSTATUS_TYPE;

typedef SQLOLE_HELPID(SQLOLE_RUNPRIORITY_TYPE) enum {
	// These must match the NT ThreadPriority values.
	SQLOLERunPri_Unknown = 100,			// Invalid ThreadPriority
	SQLOLERunPri_Min = 1,
	SQLOLERunPri_Idle = -15,
	SQLOLERunPri_Lowest = -2,
	SQLOLERunPri_BelowNormal = -1,
	SQLOLERunPri_Normal = 0,
	SQLOLERunPri_AboveNormal = 1,
	SQLOLERunPri_Highest = 2,
	SQLOLERunPri_TimeCritical = 15,
} SQLOLE_RUNPRIORITY_TYPE;

typedef SQLOLE_HELPID(SQLOLE_INTSECLOGIN_TYPE) enum {
	SQLOLEIntSecLogin_Unknown = 0,
	SQLOLEIntSecLogin_Min = 1,
	SQLOLEIntSecLogin_Admin = 1,
	SQLOLEIntSecLogin_User = 2,
	SQLOLEIntSecLogin_Replication = 3,
	SQLOLEIntSecLogin_Max = 3
} SQLOLE_INTSECLOGIN_TYPE;

typedef SQLOLE_HELPID(SQLOLE_NOTIFY_TYPE) enum {
	SQLOLENotify_None = 0x0000,
	SQLOLENotify_Email = 0x0001,
	SQLOLENotify_Pager = 0x0002,
	SQLOLENotify_Both = 0x0003,
	SQLOLENotify_Valid = 0x0003
} SQLOLE_NOTIFY_TYPE;

typedef SQLOLE_HELPID(SQLOLE_ENUMNOTIFY_TYPE) enum {
	SQLOLEEnumNotify_Min = 1,
	SQLOLEEnumNotify_All = 1,			// All operators/alerts
	SQLOLEEnumNotify_Actual = 2,		// Only operators/alerts receiving notifications for this alert/operator
	SQLOLEEnumNotify_Target = 3,		// Specifically named target alert/operator(s)
	SQLOLEEnumNotify_Max = 3
} SQLOLE_ENUMNOTIFY_TYPE;

typedef SQLOLE_HELPID(SQLOLE_VERIFYCONN_TYPE) enum {
	SQLOLEConn_LastState = 0x0001,			// State of conn at end of last operation.
	SQLOLEConn_CurrentState = 0x0002,		// Actual current state (checks pipe, etc.)
	SQLOLEConn_ReconnectIfDead = 0x0006,	// Reconnect if we've been disconnected (0x0004 | CurrentState)..
	SQLOLEConn_Valid = 0x0007				// All valid conn operations.
} SQLOLE_VERIFYCONN_TYPE;

typedef SQLOLE_HELPID(SQLOLE_EXEC_TYPE) enum {
	// For ExecuteImmediate, tells how to handle multi-batch commands.
	SQLOLEExec_Default = 0x0000,			// None of the following
	SQLOLEExec_NoCommandTerm = 0x0001,		// No command-terminator parsing (i.e. don't check for "GO"; exec as single batch)
	SQLOLEExec_ContinueOnError = 0x0002,	// Continue batch on all but broken-connection errors.
	SQLOLEExec_NoExec = 0x0004,				// SET NOEXEC ON/OFF
	SQLOLEExec_ParseOnly = 0x0008			// SET PARSEONLY ON/OFF
} SQLOLE_EXEC_TYPE;

typedef SQLOLE_HELPID(SQLOLE_CONFIGVALUE_TYPE) enum {
	SQLOLEConfig_RecoveryInterval = 101,
	SQLOLEConfig_AllowUpdates = 102,
	SQLOLEConfig_UserConnections = 103,
	SQLOLEConfig_Memory = 104,
	SQLOLEConfig_OpenDatabases = 105,
	SQLOLEConfig_Locks = 106,
	SQLOLEConfig_OpenObjects = 107,
	SQLOLEConfig_ProcedureCache = 108,
	SQLOLEConfig_FillFactor = 109,
	SQLOLEConfig_DatabaseSize = 111,
	SQLOLEConfig_MediaRetention = 112,
	SQLOLEConfig_RecoveryFlags = 113,
	SQLOLEConfig_NestedTriggers = 115,
	SQLOLEConfig_RemoteAccess = 117,
	SQLOLEConfig_DefaultLanguage = 124,
	SQLOLEConfig_LanguageInCache = 125,
	SQLOLEConfig_TempdbInRamMB = 501,
	SQLOLEConfig_MaxAsyncIO = 502,
	SQLOLEConfig_MaxWorkerThreads = 503,
	SQLOLEConfig_NetworkPacketSize = 505,
	SQLOLEConfig_RAWorkerThreads = 508,
	SQLOLEConfig_ShowAdvancedOption = 518,
	SQLOLEConfig_LEThresholdPercent = 521,
	SQLOLEConfig_LEThresholdMaximum = 523,
	SQLOLEConfig_BackupThreads = 540,
	SQLOLEConfig_BackupBufferSize = 541,
	SQLOLEConfig_RemoteProcTrans = 542,
	SQLOLEConfig_RemoteConnTimeout = 543,
	SQLOLEConfig_TimeSlice = 1110,
	SQLOLEConfig_RemoteSites = 1119,
	SQLOLEConfig_DefaultSortorderId = 1123,
	SQLOLEConfig_HashBuckets = 1504,
	SQLOLEConfig_SortPages = 1505,
	SQLOLEConfig_MaxLazywriteIO = 1506,
	SQLOLEConfig_RASlotsPerThread = 1509,
	SQLOLEConfig_RAPrefetches = 1510,
	SQLOLEConfig_RADelay = 1511,
	SQLOLEConfig_RACacheMissLimit = 1512,
	SQLOLEConfig_RACacheHitLimit = 1513,
	SQLOLEConfig_SpinCounter = 1514,
	SQLOLEConfig_FreeBuffers = 1515,
	SQLOLEConfig_SMPConcurrency = 1516,
	SQLOLEConfig_PriorityBoost = 1517,
	SQLOLEConfig_RemoteLoginTimeout = 1519,
	SQLOLEConfig_RemoteQueryTimeout = 1520,
	SQLOLEConfig_LEThresholdMinimum = 1522,
	SQLOLEConfig_LogwriteSleepMS = 1530,
	SQLOLEConfig_CursorThreshold = 1531,
	SQLOLEConfig_SetWorkingSetSize = 1532,
	SQLOLEConfig_ResourceTimeout = 1533,
	SQLOLEConfig_UserOptions = 1534,
	SQLOLEConfig_ProcessorAffinityMask = 1535,
	SQLOLEConfig_MaxTextReplSize = 1536
} SQLOLE_CONFIGVALUE_TYPE;

typedef SQLOLE_HELPID(SQLOLE_SRVUSERPROFILE_TYPE) enum {
	// Output from Server.GetUserProfile
	SQLOLESrvUserProf_None = 0x0000,
	SQLOLESrvUserProf_SaLogin = 0x0001,						// User is System Administrator
	SQLOLESrvUserProf_CreateDatabase = 0x0002,				// User has privilege to do this
	SQLOLESrvUserProf_CreateXP = 0x0004,					// User can create Extended Stored Procedures

	SQLOLESrvUserProf_AllProfileBits = 0x0007				// All server profile bits
} SQLOLE_SRVUSERPROFILE_TYPE;

typedef SQLOLE_HELPID(SQLOLE_DBUSERPROFILE_TYPE) enum {
	// Output from Database.GetUserProfile
	SQLOLEDbUserProf_None = 0x0000,
	SQLOLEDbUserProf_DboLogin = 0x0001,						// User is Database Owner
	SQLOLEDbUserProf_CreateTable = 0x0002,					// User has these privileges
	SQLOLEDbUserProf_CreateView = 0x0004,
	SQLOLEDbUserProf_CreateProcedure = 0x0008,
	SQLOLEDbUserProf_DumpDatabase = 0x0010,
	SQLOLEDbUserProf_CreateDefault = 0x0020,
	SQLOLEDbUserProf_DumpTransaction = 0x0040,
	SQLOLEDbUserProf_CreateRule = 0x0080,

	SQLOLEDbUserProf_AllProfileBits = 0x00ff,				// All DB-valid profile bits

	SQLOLEDbUserProf_InvalidLogin = 0x40000000,				// Current login not a valid user in this database.
	SQLOLEDbUserProf_InaccessibleDb = 0x80000000,			// Database Loading | Recovering | Suspect | Offline
	SQLOLEDbUserProf_DbNotAvailable = 0xc0000000			// All Database-not-accessible bits.
} SQLOLE_DBUSERPROFILE_TYPE;

typedef SQLOLE_HELPID(SQLOLE_ERROR_TYPE) enum {
	// Error values.  (MS-Internal:  See usa.rc for the string representation of these (OSQL_S_*)).
	// DBLib uses 10000 (0x2710) to 10200 (0x27D8).
	SQLOLE_E_DBLIBFIRSTERROR = 0x2710,
	SQLOLE_E_DBLIBLASTERROR = 0x27D8,

	// SQL Server itself sends errors back which may be up to 20000 (0x4E20).
	// SQLOLE-detected errors are in the range SQLOLE_E_FIRSTERROR to SQLOLE_E_LASTERROR.
	// Each SQLOLE_ECAT (Error CATegory) summarizes its specific errorcodes.
	SQLOLE_E_FIRSTERROR = 0x5000,

// All error categories masked off by this.
SQLOLE_ECAT_MASK = 0x5F00,

// Errors indicating an operation that is valid but not in the given context.
SQLOLE_ECAT_INVALIDCONTEXT = 0x5000,
	SQLOLE_E_ALREADYCONN = 0x5000,
	SQLOLE_E_ALREADYCOLL = 0x5001,
	SQLOLE_E_NOTCONN = 0x5002,
	SQLOLE_E_CANTDROPSERVER = 0x5003,
	SQLOLE_E_NOCOMPLEXALTER = 0x5004,
	SQLOLE_E_PROPNEEDSCREATE = 0x5005,
	SQLOLE_E_COLTYPEFIXED = 0x5006,
	SQLOLE_E_COLTYPENONNULL = 0x5007,
	SQLOLE_E_CANTCHANGEUDDT = 0x5008,
	SQLOLE_E_BASETYPEFIXED = 0x5009,
	SQLOLE_E_BASETYPENONNULL = 0x500A,
	SQLOLE_E_ENUMORDINAL = 0x500B,
	SQLOLE_E_CANTRENAMEUSER = 0x500C,
	SQLOLE_E_CANTRENAMEGROUP = 0x500D,
	SQLOLE_E_CANTRENAMELOGIN = 0x500E,
	SQLOLE_E_CANTRENAMEDEVICE = 0x500F,
	SQLOLE_E_NOTDUMPPROP = 0x5010,
	SQLOLE_E_NOSERVERASSOC = 0x5011,
	SQLOLE_E_NOTCOLLTYPE = 0x5012,
	SQLOLE_E_CANTMODIFYDRIINDEX = 0x5013,
	SQLOLE_E_CANTCHANGEPROCTYPE = 0x5014,
	SQLOLE_E_CANTMODIFYINDEX = 0x5015,
	SQLOLE_E_INVALIDPRIVOBJ = 0x5016,
	SQLOLE_E_CANTCHANGETRIGTYPE = 0x5017,
	SQLOLE_E_NOVIEWCOLALTER = 0x5018,
	SQLOLE_E_CANTRENAMELANGUAGE = 0x5019,
	SQLOLE_E_CANTRENAMERSERVER = 0x501A,
	SQLOLE_E_CANTRENAMERLOGIN = 0x501B,
	SQLOLE_E_MUSTBEDBDEV = 0x501C,
	SQLOLE_E_NOINACTIVEMIRROR = 0x501D,
	SQLOLE_E_NOACTIVEMIRROR = 0x501E,
	SQLOLE_E_NOMIRROR = 0x501F,
	SQLOLE_E_SERVERDISCONNECTED = 0x5020,
	SQLOLE_E_CANTRENAMESERVER = 0x5021,
	SQLOLE_E_CANTMODIFYTEXT = 0x5022,
	SQLOLE_E_CANTMODIFYSYSTABLE = 0x5023,
	SQLOLE_E_LOGINALREADYALIASED = 0x5024,
	SQLOLE_E_LOGINALREADYUSER = 0x5025,
	SQLOLE_E_CACHENORESULTS = 0x5026,
	SQLOLE_E_ALREADYCREATED = 0x5027,
	SQLOLE_E_NOTDISCONN = 0x5028,
	SQLOLE_E_CANTMODIFYARTTABLE = 0x5029,
	SQLOLE_E_CANTMODIFYSUBSERVER = 0x502A,
	SQLOLE_E_BASETYPENOTNUMERIC = 0x502B,
	SQLOLE_E_TOFILEBUTNOFILENAME = 0x502C,
	SQLOLE_E_MUSTBEDISTSERVER = 0x502D,
	SQLOLE_E_CANTMODIFYKEY = 0x502E,
	SQLOLE_E_LISTCANTREFRESH = 0x502F,
	SQLOLE_E_NOCOLTABLE = 0x5030,
	SQLOLE_E_MUSTBEINALTER = 0x5031,
	SQLOLE_E_CANTUNDEDICATELOGDEVICE = 0x5032,
	SQLOLE_E_CANTRENAMESERVERGROUP = 0x5033,
	SQLOLE_E_CANTRENAMEREGISTEREDSERVER = 0x5034,
	SQLOLE_E_INDEXREBUILDKEYTYPE = 0x5035,
	SQLOLE_E_REBUILDINDEXOPTIONS = 0x5036,
	SQLOLE_E_IMPERSONATEXPONLY = 0x5037,

// Errors indicating that the OLE object is not (or is no longer) valid in SQLOLE.
SQLOLE_ECAT_INVALIDOBJECT = 0x5100,
	SQLOLE_E_OBJECTDROPPED = 0x5100,
	SQLOLE_E_NOTSQLOLEOBJECT = 0x5101,
	SQLOLE_E_OBJECTDETACHED = 0x5102,
	SQLOLE_E_SERVERCLOSED = 0x5103,

// Errors indicating that an attempt was made to create an object (usually to add an object
// to a collection) but that its definition (property settings) were incomplete or inconsistent.
SQLOLE_ECAT_INVALIDOBJECTDEFINITION = 0x5200,
	SQLOLE_E_NOCOLUMNSADDED = 0x5200,
	SQLOLE_E_COLUMNINCOMPLETE = 0x5201,
	SQLOLE_E_TABLEINCOMPLETE = 0x5202,
	SQLOLE_E_UDDTINCOMPLETE = 0x5203,
	SQLOLE_E_RULEINCOMPLETE = 0x5204,
	SQLOLE_E_DEFAULTINCOMPLETE = 0x5205,
	SQLOLE_E_VIEWINCOMPLETE = 0x5206,
	SQLOLE_E_USERINCOMPLETE = 0x5207,
	SQLOLE_E_GROUPINCOMPLETE = 0x5208,
	SQLOLE_E_PROCINCOMPLETE = 0x5209,
	SQLOLE_E_USERALREADYEXISTS = 0x520A,
	SQLOLE_E_GROUPALREADYEXISTS = 0x520B,
	SQLOLE_E_COLUMNALREADYEXISTS = 0x520C,
	SQLOLE_E_OBJECTALREADYEXISTS = 0x520D,
	SQLOLE_E_INDEXALREADYEXISTS = 0x520E,
	SQLOLE_E_DBALREADYEXISTS = 0x520F,
	SQLOLE_E_LOGINALREADYEXISTS = 0x5210,
	SQLOLE_E_DEVICEALREADYEXISTS = 0x5211,
	SQLOLE_E_SKIPONLYTAPE = 0x5212,
	SQLOLE_E_DEVICEINCOMPLETE = 0x5213,
	SQLOLE_E_PROCALREADYEXISTS = 0x5214,
	SQLOLE_E_UDDTALREADYEXISTS = 0x5215,
	SQLOLE_E_TABLEALREADYEXISTS = 0x5216,
	SQLOLE_E_RULEALREADYEXISTS = 0x5217,
	SQLOLE_E_DEFAULTALREADYEXISTS = 0x5218,
	SQLOLE_E_VIEWALREADYEXISTS = 0x5219,
	SQLOLE_E_INDEXINCOMPLETE = 0x521A,
	SQLOLE_E_TRIGINCOMPLETE = 0x521B,
	SQLOLE_E_TRIGALREADYEXISTS = 0x521C,
	SQLOLE_E_LANGUAGEINCOMPLETE = 0x521D,
	SQLOLE_E_LANGUAGEALREADYEXISTS = 0x521E,
	SQLOLE_E_LOGININCOMPLETE = 0x521F,
	SQLOLE_E_RSERVERINCOMPLETE = 0x5220,
	SQLOLE_E_RSERVERALREADYEXISTS = 0x5221,
	SQLOLE_E_NULLRLOGINALREADYEXISTS = 0x5222,
	SQLOLE_E_RLOGINALREADYEXISTS = 0x5223,
	SQLOLE_E_REMOTENEEDSLOCAL = 0x5224,
	SQLOLE_E_BACKUPNEEDSDEVICE = 0x5225,
	SQLOLE_E_NEEDMANUALFILTERNAME = 0x5226,
	SQLOLE_E_TASKINCOMPLETE = 0x5227,
	SQLOLE_E_ARTINCOMPLETE = 0x5228,
	SQLOLE_E_PUBINCOMPLETE = 0x5229,
	SQLOLE_E_SUBINCOMPLETE = 0x522A,
	SQLOLE_E_ALERTINCOMPLETE = 0x522B,
	SQLOLE_E_OPERATORINCOMPLETE = 0x522C,
	SQLOLE_E_NAMEMUSTMATCH = 0x522D,
	SQLOLE_E_TRIGREQTABLENAME = 0x522E,
	SQLOLE_E_MUSTBESYNCTASK = 0x522F,
	SQLOLE_E_NOEVENTCOMPLETION = 0x5230,
	SQLOLE_E_FKEYINCOMPLETE = 0x5231,
	SQLOLE_E_KEYINCOMPLETE = 0x5232,
	SQLOLE_E_KEYALREADYEXISTS = 0x5233,
	SQLOLE_E_CHECKINCOMPLETE = 0x5234,
	SQLOLE_E_DRIDEFAULTINCOMPLETE = 0x5235,
	SQLOLE_E_CHECKALREADYEXISTS = 0x5236,
	SQLOLE_E_ONLYONEPRIMARYKEY = 0x5237,
	SQLOLE_E_NEEDMANUALVIEWNAME = 0x5238,
	SQLOLE_E_SERVERGROUPINCOMPLETE = 0x5239,
	SQLOLE_E_REGISTEREDSERVERINCOMPLETE = 0x523A,
	SQLOLE_E_SERVERGROUPALREADYEXISTS = 0x523B,
	SQLOLE_E_REGISTEREDSERVERALREADYEXISTS = 0x523C,
	SQLOLE_E_NEEDLOADTABLENAME = 0x523D,

// Errors indicating an invalid parameter passed to a method or property, or other unexpected condition.
SQLOLE_ECAT_INVALIDPARAMETER = 0x5300,
	SQLOLE_E_BADCOLLEN = 0x5300,
	SQLOLE_E_INVALIDPERFMONSET = 0x5301,
	SQLOLE_E_BADDEVICETYPE = 0x5302,
	SQLOLE_E_SIZEGREATERTHAN0 = 0x5303,
	SQLOLE_E_RESULTSETOUTOFRANGE = 0x5304,
	SQLOLE_E_OUTPUTPARAMREQUIRED = 0x5305,
	SQLOLE_E_PROPTEXTNONNULL = 0x5306,
	SQLOLE_E_BADPROCTYPE = 0x5307,
	SQLOLE_E_BADFILLFACTOR = 0x5308,
	SQLOLE_E_INVALIDINDEXTYPE = 0x5309,
	SQLOLE_E_INVALIDPRIVTYPE = 0x530A,
	SQLOLE_E_BADTRIGTYPE = 0x530B,
	SQLOLE_E_INVALIDDAYOFWEEK = 0x530C,
	SQLOLE_E_INVALIDMONTH = 0x530D,
	SQLOLE_E_BADDAYCOUNT = 0x530E,
	SQLOLE_E_BADMONTHCOUNT = 0x530F,
	SQLOLE_E_BADCONFIGVALUE = 0x5310,
	SQLOLE_E_INVALIDPARAMINDEX = 0x5311,
	SQLOLE_E_INVALIDPARAMRANGE = 0x5312,
	SQLOLE_E_INVALIDDBOBJTYPE = 0x5313,
	SQLOLE_E_ROWCOLOUTOFRANGE = 0x5314,
	SQLOLE_E_NONUNIQUENAME = 0x5315,
	SQLOLE_E_NOTIMESTAMPUDDT = 0x5316,
	SQLOLE_E_INVALIDNAME = 0x5317,
	SQLOLE_E_INVALIDCOMPLETION = 0x5318,
	SQLOLE_E_NAMETOOLONG = 0x5319,
	SQLOLE_E_INVALIDFREQTYPE = 0x531A,
	SQLOLE_E_INVALIDFREQSUBDAY = 0x531B,
	SQLOLE_E_INVALIDFREQRELINTERVAL = 0x531C,
	SQLOLE_E_BADWEEKLYINTERVAL = 0x531D,
	SQLOLE_E_BADMONTHLYINTERVAL = 0x531E,
	SQLOLE_E_BADMONTHLYRELINTERVAL = 0x531F,
	SQLOLE_E_INVALIDSRVOPTION = 0x5320,
	SQLOLE_E_INVALIDRUNPRIORITY = 0x5321,
	SQLOLE_E_DBNAMEREQUIRED = 0x5322,
	SQLOLE_E_PUBNAMEREQUIRED = 0x5323,
	SQLOLE_E_PROPINDEXOUTOFRANGE = 0x5324,
	SQLOLE_E_INVALIDNOTIFYTYPE = 0x5325,
	SQLOLE_E_INVALIDENUMNOTIFYTYPE = 0x5326,
	SQLOLE_E_INVALIDWEEKDAY = 0x5327,
	SQLOLE_E_INVALIDOBJECTTYPE = 0x5328,
	SQLOLE_E_OBJECTREQUIRED = 0x5329,
	SQLOLE_E_INVALIDEVENTTYPE = 0x532A,
	SQLOLE_E_INVALIDCOMPLETIONTYPE = 0x532B,
	SQLOLE_E_INVALIDKEYTYPE = 0x532C,
	SQLOLE_E_TABLEMUSTBECREATED = 0x532D,
	SQLOLE_E_INVALIDPREARTICLE = 0x532E,
	SQLOLE_E_INVALIDSECURITYMODE = 0x532F,
	SQLOLE_E_INVALIDPREC = 0x5330,
	SQLOLE_E_INVALIDDEPENDENCYTYPE = 0x5331,
	SQLOLE_E_INVALIDVERIFYCONNTYPE = 0x5332,
	SQLOLE_E_INVALIDSTATUSINFOTYPE = 0x5333,
	SQLOLE_E_INVALIDFORWARDINGSEVERITY = 0x5334,
	SQLOLE_E_INVALIDFORWARDINGSERVER = 0x5335,
	SQLOLE_E_INVALIDRESTARTINTERVAL = 0x5336,
	SQLOLE_E_INVALIDHISTORYROWSMAX = 0x5337,
	SQLOLE_E_NAMETOOSHORT = 0x5338,
	SQLOLE_E_UNEXPECTED = 0x5339,
	SQLOLE_E_INVALIDHISTORYROWSPERTASKMAX = 0x533A,
	SQLOLE_E_INVALIDOBJSORTTYPE = 0x533B,
	SQLOLE_E_INVALIDEXECTYPE = 0x533C,

// Errors indicating that either the connected SQL Server is an invalid version,
// or the client platform is invalid, or a combination of those; or that the
// server has not been set up properly for SQLOLE (the required stored procedures
// are not installed)..
SQLOLE_ECAT_INVALIDPLATFORM = 0x5400,
	SQLOLE_E_BACKUPSQL60ONLY = 0x5400,
	SQLOLE_E_MSSQLONLY = 0x5401,
	SQLOLE_E_WIN95REQUIRESCONN = 0x5402,
	SQLOLE_E_NOTONWIN95 = 0x5403,
	SQLOLE_E_SQL60ONLY = 0x5404,
	SQLOLE_E_REPLSQL60ONLY = 0x5405,
	SQLOLE_E_STARTUPPROCSQL60ONLY = 0x5406,
	SQLOLE_E_NEEDSQLOLEPROCS = 0x5407,
	SQLOLE_E_ALTERSQL60ONLY = 0x5408,
	SQLOLE_E_SORTEDDATAREORGSQL60ONLY = 0x5409,
	SQLOLE_E_MSSQLNTONLY = 0x540A,
	SQLOLE_E_WIN95REQUIRESSQL60 = 0x540B,
	SQLOLE_E_BACKUPSQL65ONLY = 0x540C,
	SQLOLE_E_SQL65ONLY = 0x540D,
	SQLOLE_E_ALERTSQL65ONLY = 0x540E,
	SQLOLE_E_REMOTESQL65ONLY = 0x540F,
	SQLOLE_E_PIPEDEVSQL60ONLY = 0x5410,
	SQLOLE_E_FKEYSQL65ONLY = 0x5411,
	SQLOLE_E_XPIMPERSONATESQL65ONLY = 0x5412,

// Errors indicating that the named object was not found in the collection, or 
// that the ordinal passed as a collection index was out of range.
SQLOLE_ECAT_ITEMNOTFOUND = 0x5500,
	SQLOLE_E_RULENOTFOUND = 0x5500,
	SQLOLE_E_DEFAULTNOTFOUND = 0x5501,
	SQLOLE_E_TYPENOTFOUND = 0x5502,
	SQLOLE_E_LOGINNOTFOUND = 0x5503,
	SQLOLE_E_GROUPNOTFOUND = 0x5504,
	SQLOLE_E_LANGNOTFOUND = 0x5505,
	SQLOLE_E_DBNOTFOUND = 0x5506,
	SQLOLE_E_DEVICENOTFOUND = 0x5507,
	SQLOLE_E_COLUMNNOTFOUND = 0x5508,
	SQLOLE_E_ORDOUTOFRANGE = 0x5509,
	SQLOLE_E_NAMENOTFOUND = 0x550A,
	SQLOLE_E_USERNOTFOUND = 0x550B,
	SQLOLE_E_NAMENOTINCACHE = 0x550C,
	SQLOLE_E_PROPNAMENOTFOUND = 0x550D,
	SQLOLE_E_IDNOTFOUND = 0x550E,

// Errors indicating that the current login does not have sufficient privilege
// to perform the requested operation.
SQLOLE_ECAT_UNPRIVILEGEDLOGIN = 0x5600,
	SQLOLE_E_MUSTBESAORDBO = 0x5600,
	SQLOLE_E_MUSTBESAORLOGIN = 0x5601,
	SQLOLE_E_MUSTBESA = 0x5602,

// Errors indicating a query execution error or an inaccessible database.
SQLOLE_ECAT_EXECUTION = 0x5700,
	SQLOLE_E_SYSPROCERROR = 0x5700,
	SQLOLE_E_CACHEEXECERROR = 0x5701,
	SQLOLE_E_INACCESSIBLEDB = 0x5702,
	SQLOLE_E_BATCHCOMPLETEWITHERRORS = 0x5703,

// Errors indicating the connection to SQL Server cannot be restored.  SQLOLE will
// automatically reconnect (as determined by the SQLServer.AutoReconnect property)
// but the network may be down or the server not started.
SQLOLE_ECAT_CONNECTION = 0x5800,
	SQLOLE_E_CANTRECONNDEADCONN = 0x5800,

// Errors indicating insufficient resources either locally or on the server.
SQLOLE_ECAT_RESOURCE = 0x5900,
	SQLOLE_E_OUTOFMEMORY = 0x5900,
	SQLOLE_E_NOMOREDEVNOS = 0x5901,

// Errors indicating termination of Transfer.
SQLOLE_ECAT_TRANSFER = 0x5A00,
	SQLOLE_E_USERABORTED = 0x5A00,			//User aborted transfer
	SQLOLE_E_FILEPATHREQUIRED = 0x5A01,		//User should specify path for script file

// Error indicating failure of bulk copy
SQLOLE_ECAT_BCP = 0x5B00,
	SQLOLE_E_INCOMPATIBLEPROPS = 0x5B00,	//Some of the bcp object properties are incompatible.
	SQLOLE_E_BCPEXECFAILED	= 0x5B01,		//dblib bcp_exec function failed
	SQLOLE_E_BCPINITFAILED = 0x5B02,		//dblib bcp_init function failed
	SQLOLE_E_BCPCONTROLFAILED = 0x5B03,		//dblib bcp_control function failed
	SQLOLE_E_BCPCOLFMTFAILED = 0x5B04, 		//dblib bcp_colfmt failed.
	SQLOLE_E_SUSPENDINDEX = 0x5B05, 		//Error trying to suspend indexing
	SQLOLE_E_RESUMEINDEX = 0x5B06,			//Error trying to resume suspended indexing

	SQLOLE_E_LASTERROR = 0x5AFF
} SQLOLE_ERROR_TYPE;

// SQLOLE_ERROR #defines.  These are categories, not severities; there is no
// mathematical relationship between groupings.
#ifndef _SQLOLE_ODL_		// Not done in .ODL file.

// Switch on SQLOLE_ECAT to determine the category of a returned error code.
// Use long cast as lint can complain about an enum-vs.-int.
#define SQLOLE_ECAT(scode) (scode & (long)SQLOLE_ECAT_MASK)

#endif

// Constant values.
typedef SQLOLE_HELPID(SQLOLE_CONSTANTS_TYPE) enum {
	SQLOLE_NOENDDATE =				99991231,	// For task dates/times
	SQLOLE_NOENDTIME =				235959,		// For task dates/times
	SQLOLE_USEEXISTINGFILLFACTOR =	0			// For Table.RebuildIndexes
} SQLOLE_CONSTANTS_TYPE;

#endif	// _SQLOLE_CONSTANTS_

/////////////////////////////////////////////////////////////////////////////////////////
// Interface definitions.
/////////////////////////////////////////////////////////////////////////////////////////
#ifndef _SQLOLE_ODL_		// Skip if in .odl file.

// Optional parameter definitions.  For C explicit values will have to be specified,
// as indicated within the CPPDEFAULT() expansion.
//
// SQLOLE Parameter sequencing is as follows ("optional" in accordance with C++ usage):
// 	Nonoptional parameters
//		Nonoptional Return value if any
//		Optional additional parameters
//		Optional return value, if any
//
#ifdef __cplusplus
#define CPPDEFAULT(DefaultParamValue)	DefaultParamValue
#else
#define CPPDEFAULT(DefaultParamValue)
#endif

// Windows.h should define these...
typedef BOOL *LPBOOL;
typedef float *LPFLOAT;
typedef double *LPDOUBLE;

///////////////////////////////////////////////////////////////////////////////////////
// Forward declarations and typedefs, allowing for UNICODE or ANSI clients.
///////////////////////////////////////////////////////////////////////////////////////
#undef SQLOLE_LPCSTR
#undef SQLOLE_BSTR
#undef SQLOLE_LPBSTR
#undef SQLOLEFreeString

// Carry over the Ansi definition of BSTR.
typedef char __RPC_FAR * BSTRA;
typedef BSTRA __RPC_FAR *LPBSTRA;

#if defined (UNICODE) || defined (_UNICODE)
#define SQLOLE_UNICODE
#define SQLOLE_LPCSTR   LPCWSTR
#define SQLOLE_BSTR     BSTR
#define SQLOLE_LPBSTR   LPBSTR
#define SQLOLEFreeString(bstr) SysFreeString(bstr)
#else	// !UNICODE
#define SQLOLE_LPCSTR  	LPCSTR
#define SQLOLE_BSTR     BSTRA
#define SQLOLE_LPBSTR   LPBSTRA
#define SQLOLEFreeString(bstr) SysFreeString((BSTR)bstr)
#endif

#ifdef __cplusplus
#define TYPEDEFINTERFACE typedef
#else
#define TYPEDEFINTERFACE typedef interface
#endif

// Forward declarations.  Base classes...
#undef LPSQLOLESTDOBJECT 
#undef ISQLOLEStdObject 
#undef IID_ISQLOLEStdObject 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEStdObject;			TYPEDEFINTERFACE IWSQLOLEStdObject *				LPWSQLOLESTDOBJECT;
#define LPSQLOLESTDOBJECT LPWSQLOLESTDOBJECT
#define ISQLOLEStdObject IWSQLOLEStdObject
#define IID_ISQLOLEStdObject IID_IWSQLOLEStdObject 
#else
interface IASQLOLEStdObject;			TYPEDEFINTERFACE IASQLOLEStdObject *				LPASQLOLESTDOBJECT;
#define LPSQLOLESTDOBJECT LPASQLOLESTDOBJECT
#define ISQLOLEStdObject IASQLOLEStdObject
#define IID_ISQLOLEStdObject IID_IASQLOLEStdObject 
#endif

#undef LPSQLOLESTDCOLLECTION 
#undef ISQLOLEStdCollection 
#undef IID_ISQLOLEStdCollection 
#ifdef SQLOLE_UNICODE
TYPEDEFINTERFACE IWSQLOLEStdObject * LPWSQLOLESTDCOLLECTION;	// Auto-documenting for collection management
#define LPSQLOLESTDCOLLECTION LPWSQLOLESTDCOLLECTION
#define ISQLOLEStdCollection IWSQLOLEStdCollection
#define IID_ISQLOLEStdCollection IID_IWSQLOLEStdCollection 
#else
TYPEDEFINTERFACE IASQLOLEStdObject * LPASQLOLESTDCOLLECTION;	// Auto-documenting for collection management
#define LPSQLOLESTDCOLLECTION LPASQLOLESTDCOLLECTION
#define ISQLOLEStdCollection IASQLOLEStdCollection
#define IID_ISQLOLEStdCollection IID_IASQLOLEStdCollection 
#endif

// ... and derived classes.
#undef LPSQLOLEAPPLICATION 
#undef ISQLOLEApplication 
#undef IID_ISQLOLEApplication 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEApplication;		TYPEDEFINTERFACE IWSQLOLEApplication *			LPWSQLOLEAPPLICATION;
#define LPSQLOLEAPPLICATION LPWSQLOLEAPPLICATION
#define ISQLOLEApplication IWSQLOLEApplication
#define IID_ISQLOLEApplication IID_IWSQLOLEApplication 
#else
interface IASQLOLEApplication;		TYPEDEFINTERFACE IASQLOLEApplication *			LPASQLOLEAPPLICATION;
#define LPSQLOLEAPPLICATION LPASQLOLEAPPLICATION
#define ISQLOLEApplication IASQLOLEApplication
#define IID_ISQLOLEApplication IID_IASQLOLEApplication 
#endif

#undef LPSQLOLESERVERS 
#undef ISQLOLEServers 
#undef IID_ISQLOLEServers 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEServers;			TYPEDEFINTERFACE IWSQLOLEServers *				LPWSQLOLESERVERS;
#define LPSQLOLESERVERS LPWSQLOLESERVERS
#define ISQLOLEServers IWSQLOLEServers
#define IID_ISQLOLEServers IID_IWSQLOLEServers 
#else
interface IASQLOLEServers;			TYPEDEFINTERFACE IASQLOLEServers *				LPASQLOLESERVERS;
#define LPSQLOLESERVERS LPASQLOLESERVERS
#define ISQLOLEServers IASQLOLEServers
#define IID_ISQLOLEServers IID_IASQLOLEServers 
#endif

#undef LPSQLOLESERVER 
#undef ISQLOLEServer 
#undef IID_ISQLOLEServer 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEServer;			TYPEDEFINTERFACE IWSQLOLEServer *					LPWSQLOLESERVER;
#define LPSQLOLESERVER LPWSQLOLESERVER
#define ISQLOLEServer IWSQLOLEServer
#define IID_ISQLOLEServer IID_IWSQLOLEServer 
#else
interface IASQLOLEServer;			TYPEDEFINTERFACE IASQLOLEServer *					LPASQLOLESERVER;
#define LPSQLOLESERVER LPASQLOLESERVER
#define ISQLOLEServer IASQLOLEServer
#define IID_ISQLOLEServer IID_IASQLOLEServer 
#endif

#undef LPSQLOLEDATABASES 
#undef ISQLOLEDatabases 
#undef IID_ISQLOLEDatabases 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEDatabases;			TYPEDEFINTERFACE IWSQLOLEDatabases *				LPWSQLOLEDATABASES;
#define LPSQLOLEDATABASES LPWSQLOLEDATABASES
#define ISQLOLEDatabases IWSQLOLEDatabases
#define IID_ISQLOLEDatabases IID_IWSQLOLEDatabases 
#else
interface IASQLOLEDatabases;			TYPEDEFINTERFACE IASQLOLEDatabases *				LPASQLOLEDATABASES;
#define LPSQLOLEDATABASES LPASQLOLEDATABASES
#define ISQLOLEDatabases IASQLOLEDatabases
#define IID_ISQLOLEDatabases IID_IASQLOLEDatabases 
#endif

#undef LPSQLOLEDATABASE 
#undef ISQLOLEDatabase 
#undef IID_ISQLOLEDatabase 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEDatabase;			TYPEDEFINTERFACE IWSQLOLEDatabase *				LPWSQLOLEDATABASE;
#define LPSQLOLEDATABASE LPWSQLOLEDATABASE
#define ISQLOLEDatabase IWSQLOLEDatabase
#define IID_ISQLOLEDatabase IID_IWSQLOLEDatabase 
#else
interface IASQLOLEDatabase;			TYPEDEFINTERFACE IASQLOLEDatabase *				LPASQLOLEDATABASE;
#define LPSQLOLEDATABASE LPASQLOLEDATABASE
#define ISQLOLEDatabase IASQLOLEDatabase
#define IID_ISQLOLEDatabase IID_IASQLOLEDatabase 
#endif

#undef LPSQLOLEDEVICES 
#undef ISQLOLEDevices 
#undef IID_ISQLOLEDevices 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEDevices;			TYPEDEFINTERFACE IWSQLOLEDevices *				LPWSQLOLEDEVICES;
#define LPSQLOLEDEVICES LPWSQLOLEDEVICES
#define ISQLOLEDevices IWSQLOLEDevices
#define IID_ISQLOLEDevices IID_IWSQLOLEDevices 
#else
interface IASQLOLEDevices;			TYPEDEFINTERFACE IASQLOLEDevices *				LPASQLOLEDEVICES;
#define LPSQLOLEDEVICES LPASQLOLEDEVICES
#define ISQLOLEDevices IASQLOLEDevices
#define IID_ISQLOLEDevices IID_IASQLOLEDevices 
#endif

#undef LPSQLOLEDEVICE 
#undef ISQLOLEDevice 
#undef IID_ISQLOLEDevice 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEDevice;			TYPEDEFINTERFACE IWSQLOLEDevice *					LPWSQLOLEDEVICE;
#define LPSQLOLEDEVICE LPWSQLOLEDEVICE
#define ISQLOLEDevice IWSQLOLEDevice
#define IID_ISQLOLEDevice IID_IWSQLOLEDevice 
#else
interface IASQLOLEDevice;			TYPEDEFINTERFACE IASQLOLEDevice *					LPASQLOLEDEVICE;
#define LPSQLOLEDEVICE LPASQLOLEDEVICE
#define ISQLOLEDevice IASQLOLEDevice
#define IID_ISQLOLEDevice IID_IASQLOLEDevice 
#endif

#undef LPSQLOLELOGINS 
#undef ISQLOLELogins 
#undef IID_ISQLOLELogins 
#ifdef SQLOLE_UNICODE
interface IWSQLOLELogins;			TYPEDEFINTERFACE IWSQLOLELogins *					LPWSQLOLELOGINS;
#define LPSQLOLELOGINS LPWSQLOLELOGINS
#define ISQLOLELogins IWSQLOLELogins
#define IID_ISQLOLELogins IID_IWSQLOLELogins 
#else
interface IASQLOLELogins;			TYPEDEFINTERFACE IASQLOLELogins *					LPASQLOLELOGINS;
#define LPSQLOLELOGINS LPASQLOLELOGINS
#define ISQLOLELogins IASQLOLELogins
#define IID_ISQLOLELogins IID_IASQLOLELogins 
#endif

#undef LPSQLOLELOGIN 
#undef ISQLOLELogin 
#undef IID_ISQLOLELogin 
#ifdef SQLOLE_UNICODE
interface IWSQLOLELogin;				TYPEDEFINTERFACE IWSQLOLELogin *					LPWSQLOLELOGIN;
#define LPSQLOLELOGIN LPWSQLOLELOGIN
#define ISQLOLELogin IWSQLOLELogin
#define IID_ISQLOLELogin IID_IWSQLOLELogin 
#else
interface IASQLOLELogin;				TYPEDEFINTERFACE IASQLOLELogin *					LPASQLOLELOGIN;
#define LPSQLOLELOGIN LPASQLOLELOGIN
#define ISQLOLELogin IASQLOLELogin
#define IID_ISQLOLELogin IID_IASQLOLELogin 
#endif

#undef LPSQLOLELANGUAGES 
#undef ISQLOLELanguages 
#undef IID_ISQLOLELanguages 
#ifdef SQLOLE_UNICODE
interface IWSQLOLELanguages;			TYPEDEFINTERFACE IWSQLOLELanguages *				LPWSQLOLELANGUAGES;
#define LPSQLOLELANGUAGES LPWSQLOLELANGUAGES
#define ISQLOLELanguages IWSQLOLELanguages
#define IID_ISQLOLELanguages IID_IWSQLOLELanguages 
#else
interface IASQLOLELanguages;			TYPEDEFINTERFACE IASQLOLELanguages *				LPASQLOLELANGUAGES;
#define LPSQLOLELANGUAGES LPASQLOLELANGUAGES
#define ISQLOLELanguages IASQLOLELanguages
#define IID_ISQLOLELanguages IID_IASQLOLELanguages 
#endif

#undef LPSQLOLELANGUAGE 
#undef ISQLOLELanguage 
#undef IID_ISQLOLELanguage 
#ifdef SQLOLE_UNICODE
interface IWSQLOLELanguage;			TYPEDEFINTERFACE IWSQLOLELanguage *				LPWSQLOLELANGUAGE;
#define LPSQLOLELANGUAGE LPWSQLOLELANGUAGE
#define ISQLOLELanguage IWSQLOLELanguage
#define IID_ISQLOLELanguage IID_IWSQLOLELanguage 
#else
interface IASQLOLELanguage;			TYPEDEFINTERFACE IASQLOLELanguage *				LPASQLOLELANGUAGE;
#define LPSQLOLELANGUAGE LPASQLOLELANGUAGE
#define ISQLOLELanguage IASQLOLELanguage
#define IID_ISQLOLELanguage IID_IASQLOLELanguage 
#endif

#undef LPSQLOLEREMOTESERVERS 
#undef ISQLOLERemoteServers 
#undef IID_ISQLOLERemoteServers 
#ifdef SQLOLE_UNICODE
interface IWSQLOLERemoteServers;		TYPEDEFINTERFACE IWSQLOLERemoteServers *			LPWSQLOLEREMOTESERVERS;
#define LPSQLOLEREMOTESERVERS LPWSQLOLEREMOTESERVERS
#define ISQLOLERemoteServers IWSQLOLERemoteServers
#define IID_ISQLOLERemoteServers IID_IWSQLOLERemoteServers 
#else
interface IASQLOLERemoteServers;		TYPEDEFINTERFACE IASQLOLERemoteServers *			LPASQLOLEREMOTESERVERS;
#define LPSQLOLEREMOTESERVERS LPASQLOLEREMOTESERVERS
#define ISQLOLERemoteServers IASQLOLERemoteServers
#define IID_ISQLOLERemoteServers IID_IASQLOLERemoteServers 
#endif

#undef LPSQLOLEREMOTESERVER 
#undef ISQLOLERemoteServer 
#undef IID_ISQLOLERemoteServer 
#ifdef SQLOLE_UNICODE
interface IWSQLOLERemoteServer;		TYPEDEFINTERFACE IWSQLOLERemoteServer *			LPWSQLOLEREMOTESERVER;
#define LPSQLOLEREMOTESERVER LPWSQLOLEREMOTESERVER
#define ISQLOLERemoteServer IWSQLOLERemoteServer
#define IID_ISQLOLERemoteServer IID_IWSQLOLERemoteServer 
#else
interface IASQLOLERemoteServer;		TYPEDEFINTERFACE IASQLOLERemoteServer *			LPASQLOLEREMOTESERVER;
#define LPSQLOLEREMOTESERVER LPASQLOLEREMOTESERVER
#define ISQLOLERemoteServer IASQLOLERemoteServer
#define IID_ISQLOLERemoteServer IID_IASQLOLERemoteServer 
#endif

#undef LPSQLOLETABLES 
#undef ISQLOLETables 
#undef IID_ISQLOLETables 
#ifdef SQLOLE_UNICODE
interface IWSQLOLETables;			TYPEDEFINTERFACE IWSQLOLETables *					LPWSQLOLETABLES;
#define LPSQLOLETABLES LPWSQLOLETABLES
#define ISQLOLETables IWSQLOLETables
#define IID_ISQLOLETables IID_IWSQLOLETables 
#else
interface IASQLOLETables;			TYPEDEFINTERFACE IASQLOLETables *					LPASQLOLETABLES;
#define LPSQLOLETABLES LPASQLOLETABLES
#define ISQLOLETables IASQLOLETables
#define IID_ISQLOLETables IID_IASQLOLETables 
#endif

#undef LPSQLOLETABLE 
#undef ISQLOLETable 
#undef IID_ISQLOLETable 
#ifdef SQLOLE_UNICODE
interface IWSQLOLETable;				TYPEDEFINTERFACE IWSQLOLETable *					LPWSQLOLETABLE;
#define LPSQLOLETABLE LPWSQLOLETABLE
#define ISQLOLETable IWSQLOLETable
#define IID_ISQLOLETable IID_IWSQLOLETable 
#else
interface IASQLOLETable;				TYPEDEFINTERFACE IASQLOLETable *					LPASQLOLETABLE;
#define LPSQLOLETABLE LPASQLOLETABLE
#define ISQLOLETable IASQLOLETable
#define IID_ISQLOLETable IID_IASQLOLETable 
#endif

#undef LPSQLOLECOLUMNS 
#undef ISQLOLEColumns 
#undef IID_ISQLOLEColumns 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEColumns;			TYPEDEFINTERFACE IWSQLOLEColumns *				LPWSQLOLECOLUMNS;
#define LPSQLOLECOLUMNS LPWSQLOLECOLUMNS
#define ISQLOLEColumns IWSQLOLEColumns
#define IID_ISQLOLEColumns IID_IWSQLOLEColumns 
#else
interface IASQLOLEColumns;			TYPEDEFINTERFACE IASQLOLEColumns *				LPASQLOLECOLUMNS;
#define LPSQLOLECOLUMNS LPASQLOLECOLUMNS
#define ISQLOLEColumns IASQLOLEColumns
#define IID_ISQLOLEColumns IID_IASQLOLEColumns 
#endif

#undef LPSQLOLECOLUMN 
#undef ISQLOLEColumn 
#undef IID_ISQLOLEColumn 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEColumn;			TYPEDEFINTERFACE IWSQLOLEColumn *					LPWSQLOLECOLUMN;
#define LPSQLOLECOLUMN LPWSQLOLECOLUMN
#define ISQLOLEColumn IWSQLOLEColumn
#define IID_ISQLOLEColumn IID_IWSQLOLEColumn 
#else
interface IASQLOLEColumn;			TYPEDEFINTERFACE IASQLOLEColumn *					LPASQLOLECOLUMN;
#define LPSQLOLECOLUMN LPASQLOLECOLUMN
#define ISQLOLEColumn IASQLOLEColumn
#define IID_ISQLOLEColumn IID_IASQLOLEColumn 
#endif

#undef LPSQLOLERULES 
#undef ISQLOLERules 
#undef IID_ISQLOLERules 
#ifdef SQLOLE_UNICODE
interface IWSQLOLERules;				TYPEDEFINTERFACE IWSQLOLERules *					LPWSQLOLERULES;
#define LPSQLOLERULES LPWSQLOLERULES
#define ISQLOLERules IWSQLOLERules
#define IID_ISQLOLERules IID_IWSQLOLERules 
#else
interface IASQLOLERules;				TYPEDEFINTERFACE IASQLOLERules *					LPASQLOLERULES;
#define LPSQLOLERULES LPASQLOLERULES
#define ISQLOLERules IASQLOLERules
#define IID_ISQLOLERules IID_IASQLOLERules 
#endif

#undef LPSQLOLERULE 
#undef ISQLOLERule 
#undef IID_ISQLOLERule 
#ifdef SQLOLE_UNICODE
interface IWSQLOLERule;				TYPEDEFINTERFACE IWSQLOLERule *					LPWSQLOLERULE;
#define LPSQLOLERULE LPWSQLOLERULE
#define ISQLOLERule IWSQLOLERule
#define IID_ISQLOLERule IID_IWSQLOLERule 
#else
interface IASQLOLERule;				TYPEDEFINTERFACE IASQLOLERule *					LPASQLOLERULE;
#define LPSQLOLERULE LPASQLOLERULE
#define ISQLOLERule IASQLOLERule
#define IID_ISQLOLERule IID_IASQLOLERule 
#endif

#undef LPSQLOLEDEFAULTS 
#undef ISQLOLEDefaults 
#undef IID_ISQLOLEDefaults 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEDefaults;			TYPEDEFINTERFACE IWSQLOLEDefaults *				LPWSQLOLEDEFAULTS;
#define LPSQLOLEDEFAULTS LPWSQLOLEDEFAULTS
#define ISQLOLEDefaults IWSQLOLEDefaults
#define IID_ISQLOLEDefaults IID_IWSQLOLEDefaults 
#else
interface IASQLOLEDefaults;			TYPEDEFINTERFACE IASQLOLEDefaults *				LPASQLOLEDEFAULTS;
#define LPSQLOLEDEFAULTS LPASQLOLEDEFAULTS
#define ISQLOLEDefaults IASQLOLEDefaults
#define IID_ISQLOLEDefaults IID_IASQLOLEDefaults 
#endif

#undef LPSQLOLEDEFAULT 
#undef ISQLOLEDefault 
#undef IID_ISQLOLEDefault 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEDefault;			TYPEDEFINTERFACE IWSQLOLEDefault *				LPWSQLOLEDEFAULT;
#define LPSQLOLEDEFAULT LPWSQLOLEDEFAULT
#define ISQLOLEDefault IWSQLOLEDefault
#define IID_ISQLOLEDefault IID_IWSQLOLEDefault 
#else
interface IASQLOLEDefault;			TYPEDEFINTERFACE IASQLOLEDefault *				LPASQLOLEDEFAULT;
#define LPSQLOLEDEFAULT LPASQLOLEDEFAULT
#define ISQLOLEDefault IASQLOLEDefault
#define IID_ISQLOLEDefault IID_IASQLOLEDefault 
#endif

#undef LPSQLOLEUSERDEFINEDDATATYPES 
#undef ISQLOLEUserDefinedDatatypes 
#undef IID_ISQLOLEUserDefinedDatatypes 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEUserDefinedDatatypes;	TYPEDEFINTERFACE IWSQLOLEUserDefinedDatatypes *	LPWSQLOLEUSERDEFINEDDATATYPES;
#define LPSQLOLEUSERDEFINEDDATATYPES LPWSQLOLEUSERDEFINEDDATATYPES
#define ISQLOLEUserDefinedDatatypes IWSQLOLEUserDefinedDatatypes
#define IID_ISQLOLEUserDefinedDatatypes IID_IWSQLOLEUserDefinedDatatypes 
#else
interface IASQLOLEUserDefinedDatatypes;	TYPEDEFINTERFACE IASQLOLEUserDefinedDatatypes *	LPASQLOLEUSERDEFINEDDATATYPES;
#define LPSQLOLEUSERDEFINEDDATATYPES LPASQLOLEUSERDEFINEDDATATYPES
#define ISQLOLEUserDefinedDatatypes IASQLOLEUserDefinedDatatypes
#define IID_ISQLOLEUserDefinedDatatypes IID_IASQLOLEUserDefinedDatatypes 
#endif

#undef LPSQLOLEUSERDEFINEDDATATYPE 
#undef ISQLOLEUserDefinedDatatype 
#undef IID_ISQLOLEUserDefinedDatatype 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEUserDefinedDatatype;	TYPEDEFINTERFACE IWSQLOLEUserDefinedDatatype *	LPWSQLOLEUSERDEFINEDDATATYPE;
#define LPSQLOLEUSERDEFINEDDATATYPE LPWSQLOLEUSERDEFINEDDATATYPE
#define ISQLOLEUserDefinedDatatype IWSQLOLEUserDefinedDatatype
#define IID_ISQLOLEUserDefinedDatatype IID_IWSQLOLEUserDefinedDatatype 
#else
interface IASQLOLEUserDefinedDatatype;	TYPEDEFINTERFACE IASQLOLEUserDefinedDatatype *	LPASQLOLEUSERDEFINEDDATATYPE;
#define LPSQLOLEUSERDEFINEDDATATYPE LPASQLOLEUSERDEFINEDDATATYPE
#define ISQLOLEUserDefinedDatatype IASQLOLEUserDefinedDatatype
#define IID_ISQLOLEUserDefinedDatatype IID_IASQLOLEUserDefinedDatatype 
#endif

#undef LPSQLOLESYSTEMDATATYPES 
#undef ISQLOLESystemDatatypes 
#undef IID_ISQLOLESystemDatatypes 
#ifdef SQLOLE_UNICODE
interface IWSQLOLESystemDatatypes;	TYPEDEFINTERFACE IWSQLOLESystemDatatypes *		LPWSQLOLESYSTEMDATATYPES;
#define LPSQLOLESYSTEMDATATYPES LPWSQLOLESYSTEMDATATYPES
#define ISQLOLESystemDatatypes IWSQLOLESystemDatatypes
#define IID_ISQLOLESystemDatatypes IID_IWSQLOLESystemDatatypes 
#else
interface IASQLOLESystemDatatypes;	TYPEDEFINTERFACE IASQLOLESystemDatatypes *		LPASQLOLESYSTEMDATATYPES;
#define LPSQLOLESYSTEMDATATYPES LPASQLOLESYSTEMDATATYPES
#define ISQLOLESystemDatatypes IASQLOLESystemDatatypes
#define IID_ISQLOLESystemDatatypes IID_IASQLOLESystemDatatypes 
#endif

#undef LPSQLOLESYSTEMDATATYPE 
#undef ISQLOLESystemDatatype 
#undef IID_ISQLOLESystemDatatype 
#ifdef SQLOLE_UNICODE
interface IWSQLOLESystemDatatype;	TYPEDEFINTERFACE IWSQLOLESystemDatatype *			LPWSQLOLESYSTEMDATATYPE;
#define LPSQLOLESYSTEMDATATYPE LPWSQLOLESYSTEMDATATYPE
#define ISQLOLESystemDatatype IWSQLOLESystemDatatype
#define IID_ISQLOLESystemDatatype IID_IWSQLOLESystemDatatype 
#else
interface IASQLOLESystemDatatype;	TYPEDEFINTERFACE IASQLOLESystemDatatype *			LPASQLOLESYSTEMDATATYPE;
#define LPSQLOLESYSTEMDATATYPE LPASQLOLESYSTEMDATATYPE
#define ISQLOLESystemDatatype IASQLOLESystemDatatype
#define IID_ISQLOLESystemDatatype IID_IASQLOLESystemDatatype 
#endif

#undef LPSQLOLEVIEWS 
#undef ISQLOLEViews 
#undef IID_ISQLOLEViews 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEViews;				TYPEDEFINTERFACE IWSQLOLEViews *					LPWSQLOLEVIEWS;
#define LPSQLOLEVIEWS LPWSQLOLEVIEWS
#define ISQLOLEViews IWSQLOLEViews
#define IID_ISQLOLEViews IID_IWSQLOLEViews 
#else
interface IASQLOLEViews;				TYPEDEFINTERFACE IASQLOLEViews *					LPASQLOLEVIEWS;
#define LPSQLOLEVIEWS LPASQLOLEVIEWS
#define ISQLOLEViews IASQLOLEViews
#define IID_ISQLOLEViews IID_IASQLOLEViews 
#endif

#undef LPSQLOLEVIEW 
#undef ISQLOLEView 
#undef IID_ISQLOLEView 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEView;				TYPEDEFINTERFACE IWSQLOLEView *					LPWSQLOLEVIEW;
#define LPSQLOLEVIEW LPWSQLOLEVIEW
#define ISQLOLEView IWSQLOLEView
#define IID_ISQLOLEView IID_IWSQLOLEView 
#else
interface IASQLOLEView;				TYPEDEFINTERFACE IASQLOLEView *					LPASQLOLEVIEW;
#define LPSQLOLEVIEW LPASQLOLEVIEW
#define ISQLOLEView IASQLOLEView
#define IID_ISQLOLEView IID_IASQLOLEView 
#endif

#undef LPSQLOLESTOREDPROCEDURES 
#undef ISQLOLEStoredProcedures 
#undef IID_ISQLOLEStoredProcedures 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEStoredProcedures;	TYPEDEFINTERFACE IWSQLOLEStoredProcedures *		LPWSQLOLESTOREDPROCEDURES;
#define LPSQLOLESTOREDPROCEDURES LPWSQLOLESTOREDPROCEDURES
#define ISQLOLEStoredProcedures IWSQLOLEStoredProcedures
#define IID_ISQLOLEStoredProcedures IID_IWSQLOLEStoredProcedures 
#else
interface IASQLOLEStoredProcedures;	TYPEDEFINTERFACE IASQLOLEStoredProcedures *		LPASQLOLESTOREDPROCEDURES;
#define LPSQLOLESTOREDPROCEDURES LPASQLOLESTOREDPROCEDURES
#define ISQLOLEStoredProcedures IASQLOLEStoredProcedures
#define IID_ISQLOLEStoredProcedures IID_IASQLOLEStoredProcedures 
#endif

#undef LPSQLOLESTOREDPROCEDURE 
#undef ISQLOLEStoredProcedure 
#undef IID_ISQLOLEStoredProcedure 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEStoredProcedure;	TYPEDEFINTERFACE IWSQLOLEStoredProcedure *		LPWSQLOLESTOREDPROCEDURE;
#define LPSQLOLESTOREDPROCEDURE LPWSQLOLESTOREDPROCEDURE
#define ISQLOLEStoredProcedure IWSQLOLEStoredProcedure
#define IID_ISQLOLEStoredProcedure IID_IWSQLOLEStoredProcedure 
#else
interface IASQLOLEStoredProcedure;	TYPEDEFINTERFACE IASQLOLEStoredProcedure *		LPASQLOLESTOREDPROCEDURE;
#define LPSQLOLESTOREDPROCEDURE LPASQLOLESTOREDPROCEDURE
#define ISQLOLEStoredProcedure IASQLOLEStoredProcedure
#define IID_ISQLOLEStoredProcedure IID_IASQLOLEStoredProcedure 
#endif

#undef LPSQLOLETRIGGERS 
#undef ISQLOLETriggers 
#undef IID_ISQLOLETriggers 
#ifdef SQLOLE_UNICODE
interface IWSQLOLETriggers;			TYPEDEFINTERFACE IWSQLOLETriggers *				LPWSQLOLETRIGGERS;
#define LPSQLOLETRIGGERS LPWSQLOLETRIGGERS
#define ISQLOLETriggers IWSQLOLETriggers
#define IID_ISQLOLETriggers IID_IWSQLOLETriggers 
#else
interface IASQLOLETriggers;			TYPEDEFINTERFACE IASQLOLETriggers *				LPASQLOLETRIGGERS;
#define LPSQLOLETRIGGERS LPASQLOLETRIGGERS
#define ISQLOLETriggers IASQLOLETriggers
#define IID_ISQLOLETriggers IID_IASQLOLETriggers 
#endif

#undef LPSQLOLETRIGGER 
#undef ISQLOLETrigger 
#undef IID_ISQLOLETrigger 
#ifdef SQLOLE_UNICODE
interface IWSQLOLETrigger;			TYPEDEFINTERFACE IWSQLOLETrigger *				LPWSQLOLETRIGGER;
#define LPSQLOLETRIGGER LPWSQLOLETRIGGER
#define ISQLOLETrigger IWSQLOLETrigger
#define IID_ISQLOLETrigger IID_IWSQLOLETrigger 
#else
interface IASQLOLETrigger;			TYPEDEFINTERFACE IASQLOLETrigger *				LPASQLOLETRIGGER;
#define LPSQLOLETRIGGER LPASQLOLETRIGGER
#define ISQLOLETrigger IASQLOLETrigger
#define IID_ISQLOLETrigger IID_IASQLOLETrigger 
#endif

#undef LPSQLOLEUSERS 
#undef ISQLOLEUsers 
#undef IID_ISQLOLEUsers 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEUsers;				TYPEDEFINTERFACE IWSQLOLEUsers *					LPWSQLOLEUSERS;
#define LPSQLOLEUSERS LPWSQLOLEUSERS
#define ISQLOLEUsers IWSQLOLEUsers
#define IID_ISQLOLEUsers IID_IWSQLOLEUsers 
#else
interface IASQLOLEUsers;				TYPEDEFINTERFACE IASQLOLEUsers *					LPASQLOLEUSERS;
#define LPSQLOLEUSERS LPASQLOLEUSERS
#define ISQLOLEUsers IASQLOLEUsers
#define IID_ISQLOLEUsers IID_IASQLOLEUsers 
#endif

#undef LPSQLOLEUSER 
#undef ISQLOLEUser 
#undef IID_ISQLOLEUser 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEUser;				TYPEDEFINTERFACE IWSQLOLEUser *					LPWSQLOLEUSER;
#define LPSQLOLEUSER LPWSQLOLEUSER
#define ISQLOLEUser IWSQLOLEUser
#define IID_ISQLOLEUser IID_IWSQLOLEUser 
#else
interface IASQLOLEUser;				TYPEDEFINTERFACE IASQLOLEUser *					LPASQLOLEUSER;
#define LPSQLOLEUSER LPASQLOLEUSER
#define ISQLOLEUser IASQLOLEUser
#define IID_ISQLOLEUser IID_IASQLOLEUser 
#endif

#undef LPSQLOLEGROUPS 
#undef ISQLOLEGroups 
#undef IID_ISQLOLEGroups 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEGroups;			TYPEDEFINTERFACE IWSQLOLEGroups *					LPWSQLOLEGROUPS;
#define LPSQLOLEGROUPS LPWSQLOLEGROUPS
#define ISQLOLEGroups IWSQLOLEGroups
#define IID_ISQLOLEGroups IID_IWSQLOLEGroups 
#else
interface IASQLOLEGroups;			TYPEDEFINTERFACE IASQLOLEGroups *					LPASQLOLEGROUPS;
#define LPSQLOLEGROUPS LPASQLOLEGROUPS
#define ISQLOLEGroups IASQLOLEGroups
#define IID_ISQLOLEGroups IID_IASQLOLEGroups 
#endif

#undef LPSQLOLEGROUP 
#undef ISQLOLEGroup 
#undef IID_ISQLOLEGroup 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEGroup;				TYPEDEFINTERFACE IWSQLOLEGroup *					LPWSQLOLEGROUP;
#define LPSQLOLEGROUP LPWSQLOLEGROUP
#define ISQLOLEGroup IWSQLOLEGroup
#define IID_ISQLOLEGroup IID_IWSQLOLEGroup 
#else
interface IASQLOLEGroup;				TYPEDEFINTERFACE IASQLOLEGroup *					LPASQLOLEGROUP;
#define LPSQLOLEGROUP LPASQLOLEGROUP
#define ISQLOLEGroup IASQLOLEGroup
#define IID_ISQLOLEGroup IID_IASQLOLEGroup 
#endif

#undef LPSQLOLEINDEXES 
#undef ISQLOLEIndexes 
#undef IID_ISQLOLEIndexes 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEIndexes;			TYPEDEFINTERFACE IWSQLOLEIndexes *				LPWSQLOLEINDEXES;
#define LPSQLOLEINDEXES LPWSQLOLEINDEXES
#define ISQLOLEIndexes IWSQLOLEIndexes
#define IID_ISQLOLEIndexes IID_IWSQLOLEIndexes 
#else
interface IASQLOLEIndexes;			TYPEDEFINTERFACE IASQLOLEIndexes *				LPASQLOLEINDEXES;
#define LPSQLOLEINDEXES LPASQLOLEINDEXES
#define ISQLOLEIndexes IASQLOLEIndexes
#define IID_ISQLOLEIndexes IID_IASQLOLEIndexes 
#endif

#undef LPSQLOLEINDEX 
#undef ISQLOLEIndex 
#undef IID_ISQLOLEIndex 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEIndex;				TYPEDEFINTERFACE IWSQLOLEIndex *					LPWSQLOLEINDEX;
#define LPSQLOLEINDEX LPWSQLOLEINDEX
#define ISQLOLEIndex IWSQLOLEIndex
#define IID_ISQLOLEIndex IID_IWSQLOLEIndex 
#else
interface IASQLOLEIndex;				TYPEDEFINTERFACE IASQLOLEIndex *					LPASQLOLEINDEX;
#define LPSQLOLEINDEX LPASQLOLEINDEX
#define ISQLOLEIndex IASQLOLEIndex
#define IID_ISQLOLEIndex IID_IASQLOLEIndex 
#endif

#undef LPSQLOLETRIGGERS 
#undef ISQLOLETriggers 
#undef IID_ISQLOLETriggers 
#ifdef SQLOLE_UNICODE
interface IWSQLOLETriggers;			TYPEDEFINTERFACE IWSQLOLETriggers *				LPWSQLOLETRIGGERS;
#define LPSQLOLETRIGGERS LPWSQLOLETRIGGERS
#define ISQLOLETriggers IWSQLOLETriggers
#define IID_ISQLOLETriggers IID_IWSQLOLETriggers 
#else
interface IASQLOLETriggers;			TYPEDEFINTERFACE IASQLOLETriggers *				LPASQLOLETRIGGERS;
#define LPSQLOLETRIGGERS LPASQLOLETRIGGERS
#define ISQLOLETriggers IASQLOLETriggers
#define IID_ISQLOLETriggers IID_IASQLOLETriggers 
#endif

#undef LPSQLOLETRIGGER 
#undef ISQLOLETrigger 
#undef IID_ISQLOLETrigger 
#ifdef SQLOLE_UNICODE
interface IWSQLOLETrigger;			TYPEDEFINTERFACE IWSQLOLETrigger *				LPWSQLOLETRIGGER;
#define LPSQLOLETRIGGER LPWSQLOLETRIGGER
#define ISQLOLETrigger IWSQLOLETrigger
#define IID_ISQLOLETrigger IID_IWSQLOLETrigger 
#else
interface IASQLOLETrigger;			TYPEDEFINTERFACE IASQLOLETrigger *				LPASQLOLETRIGGER;
#define LPSQLOLETRIGGER LPASQLOLETRIGGER
#define ISQLOLETrigger IASQLOLETrigger
#define IID_ISQLOLETrigger IID_IASQLOLETrigger 
#endif

#undef LPSQLOLEREMOTELOGINS 
#undef ISQLOLERemoteLogins 
#undef IID_ISQLOLERemoteLogins 
#ifdef SQLOLE_UNICODE
interface IWSQLOLERemoteLogins;		TYPEDEFINTERFACE IWSQLOLERemoteLogins *			LPWSQLOLEREMOTELOGINS;
#define LPSQLOLEREMOTELOGINS LPWSQLOLEREMOTELOGINS
#define ISQLOLERemoteLogins IWSQLOLERemoteLogins
#define IID_ISQLOLERemoteLogins IID_IWSQLOLERemoteLogins 
#else
interface IASQLOLERemoteLogins;		TYPEDEFINTERFACE IASQLOLERemoteLogins *			LPASQLOLEREMOTELOGINS;
#define LPSQLOLEREMOTELOGINS LPASQLOLEREMOTELOGINS
#define ISQLOLERemoteLogins IASQLOLERemoteLogins
#define IID_ISQLOLERemoteLogins IID_IASQLOLERemoteLogins 
#endif

#undef LPSQLOLEREMOTELOGIN 
#undef ISQLOLERemoteLogin 
#undef IID_ISQLOLERemoteLogin 
#ifdef SQLOLE_UNICODE
interface IWSQLOLERemoteLogin;		TYPEDEFINTERFACE IWSQLOLERemoteLogin *			LPWSQLOLEREMOTELOGIN;
#define LPSQLOLEREMOTELOGIN LPWSQLOLEREMOTELOGIN
#define ISQLOLERemoteLogin IWSQLOLERemoteLogin
#define IID_ISQLOLERemoteLogin IID_IWSQLOLERemoteLogin 
#else
interface IASQLOLERemoteLogin;		TYPEDEFINTERFACE IASQLOLERemoteLogin *			LPASQLOLEREMOTELOGIN;
#define LPSQLOLEREMOTELOGIN LPASQLOLEREMOTELOGIN
#define ISQLOLERemoteLogin IASQLOLERemoteLogin
#define IID_ISQLOLERemoteLogin IID_IASQLOLERemoteLogin 
#endif

#undef LPSQLOLETASKS 
#undef ISQLOLETasks 
#undef IID_ISQLOLETasks 
#ifdef SQLOLE_UNICODE
interface IWSQLOLETasks;			TYPEDEFINTERFACE IWSQLOLETasks *					LPWSQLOLETASKS;
#define LPSQLOLETASKS LPWSQLOLETASKS
#define ISQLOLETasks IWSQLOLETasks
#define IID_ISQLOLETasks IID_IWSQLOLETasks 
#else
interface IASQLOLETasks;			TYPEDEFINTERFACE IASQLOLETasks *					LPASQLOLETASKS;
#define LPSQLOLETASKS LPASQLOLETASKS
#define ISQLOLETasks IASQLOLETasks
#define IID_ISQLOLETasks IID_IASQLOLETasks 
#endif

#undef LPSQLOLETASK 
#undef ISQLOLETask 
#undef IID_ISQLOLETask 
#ifdef SQLOLE_UNICODE
interface IWSQLOLETask;				TYPEDEFINTERFACE IWSQLOLETask *					LPWSQLOLETASK;
#define LPSQLOLETASK LPWSQLOLETASK
#define ISQLOLETask IWSQLOLETask
#define IID_ISQLOLETask IID_IWSQLOLETask 
#else
interface IASQLOLETask;				TYPEDEFINTERFACE IASQLOLETask *					LPASQLOLETASK;
#define LPSQLOLETASK LPASQLOLETASK
#define ISQLOLETask IASQLOLETask
#define IID_ISQLOLETask IID_IASQLOLETask 
#endif

#undef LPSQLOLEALERTS 
#undef ISQLOLEAlerts 
#undef IID_ISQLOLEAlerts 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEAlerts;			TYPEDEFINTERFACE IWSQLOLEAlerts *					LPWSQLOLEALERTS;
#define LPSQLOLEALERTS LPWSQLOLEALERTS
#define ISQLOLEAlerts IWSQLOLEAlerts
#define IID_ISQLOLEAlerts IID_IWSQLOLEAlerts 
#else
interface IASQLOLEAlerts;			TYPEDEFINTERFACE IASQLOLEAlerts *					LPASQLOLEALERTS;
#define LPSQLOLEALERTS LPASQLOLEALERTS
#define ISQLOLEAlerts IASQLOLEAlerts
#define IID_ISQLOLEAlerts IID_IASQLOLEAlerts 
#endif

#undef LPSQLOLEALERT 
#undef ISQLOLEAlert 
#undef IID_ISQLOLEAlert 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEAlert;				TYPEDEFINTERFACE IWSQLOLEAlert *					LPWSQLOLEALERT;
#define LPSQLOLEALERT LPWSQLOLEALERT
#define ISQLOLEAlert IWSQLOLEAlert
#define IID_ISQLOLEAlert IID_IWSQLOLEAlert 
#else
interface IASQLOLEAlert;				TYPEDEFINTERFACE IASQLOLEAlert *					LPASQLOLEALERT;
#define LPSQLOLEALERT LPASQLOLEALERT
#define ISQLOLEAlert IASQLOLEAlert
#define IID_ISQLOLEAlert IID_IASQLOLEAlert 
#endif

#undef LPSQLOLEOPERATORS 
#undef ISQLOLEOperators 
#undef IID_ISQLOLEOperators 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEOperators;			TYPEDEFINTERFACE IWSQLOLEOperators *					LPWSQLOLEOPERATORS;
#define LPSQLOLEOPERATORS LPWSQLOLEOPERATORS
#define ISQLOLEOperators IWSQLOLEOperators
#define IID_ISQLOLEOperators IID_IWSQLOLEOperators 
#else
interface IASQLOLEOperators;			TYPEDEFINTERFACE IASQLOLEOperators *					LPASQLOLEOPERATORS;
#define LPSQLOLEOPERATORS LPASQLOLEOPERATORS
#define ISQLOLEOperators IASQLOLEOperators
#define IID_ISQLOLEOperators IID_IASQLOLEOperators 
#endif

#undef LPSQLOLEOPERATOR 
#undef ISQLOLEOperator 
#undef IID_ISQLOLEOperator 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEOperator;				TYPEDEFINTERFACE IWSQLOLEOperator *					LPWSQLOLEOPERATOR;
#define LPSQLOLEOPERATOR LPWSQLOLEOPERATOR
#define ISQLOLEOperator IWSQLOLEOperator
#define IID_ISQLOLEOperator IID_IWSQLOLEOperator 
#else
interface IASQLOLEOperator;				TYPEDEFINTERFACE IASQLOLEOperator *					LPASQLOLEOPERATOR;
#define LPSQLOLEOPERATOR LPASQLOLEOPERATOR
#define ISQLOLEOperator IASQLOLEOperator
#define IID_ISQLOLEOperator IID_IASQLOLEOperator 
#endif

#undef LPSQLOLEPUBLICATIONS 
#undef ISQLOLEPublications 
#undef IID_ISQLOLEPublications 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEPublications;			TYPEDEFINTERFACE IWSQLOLEPublications *					LPWSQLOLEPUBLICATIONS;
#define LPSQLOLEPUBLICATIONS LPWSQLOLEPUBLICATIONS
#define ISQLOLEPublications IWSQLOLEPublications
#define IID_ISQLOLEPublications IID_IWSQLOLEPublications 
#else
interface IASQLOLEPublications;			TYPEDEFINTERFACE IASQLOLEPublications *					LPASQLOLEPUBLICATIONS;
#define LPSQLOLEPUBLICATIONS LPASQLOLEPUBLICATIONS
#define ISQLOLEPublications IASQLOLEPublications
#define IID_ISQLOLEPublications IID_IASQLOLEPublications 
#endif

#undef LPSQLOLEPUBLICATION 
#undef ISQLOLEPublication 
#undef IID_ISQLOLEPublication 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEPublication;				TYPEDEFINTERFACE IWSQLOLEPublication *					LPWSQLOLEPUBLICATION;
#define LPSQLOLEPUBLICATION LPWSQLOLEPUBLICATION
#define ISQLOLEPublication IWSQLOLEPublication
#define IID_ISQLOLEPublication IID_IWSQLOLEPublication 
#else
interface IASQLOLEPublication;				TYPEDEFINTERFACE IASQLOLEPublication *					LPASQLOLEPUBLICATION;
#define LPSQLOLEPUBLICATION LPASQLOLEPUBLICATION
#define ISQLOLEPublication IASQLOLEPublication
#define IID_ISQLOLEPublication IID_IASQLOLEPublication 
#endif

#undef LPSQLOLEARTICLES 
#undef ISQLOLEArticles 
#undef IID_ISQLOLEArticles 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEArticles;			TYPEDEFINTERFACE IWSQLOLEArticles *					LPWSQLOLEARTICLES;
#define LPSQLOLEARTICLES LPWSQLOLEARTICLES
#define ISQLOLEArticles IWSQLOLEArticles
#define IID_ISQLOLEArticles IID_IWSQLOLEArticles 
#else
interface IASQLOLEArticles;			TYPEDEFINTERFACE IASQLOLEArticles *					LPASQLOLEARTICLES;
#define LPSQLOLEARTICLES LPASQLOLEARTICLES
#define ISQLOLEArticles IASQLOLEArticles
#define IID_ISQLOLEArticles IID_IASQLOLEArticles 
#endif

#undef LPSQLOLEARTICLE 
#undef ISQLOLEArticle 
#undef IID_ISQLOLEArticle 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEArticle;				TYPEDEFINTERFACE IWSQLOLEArticle *					LPWSQLOLEARTICLE;
#define LPSQLOLEARTICLE LPWSQLOLEARTICLE
#define ISQLOLEArticle IWSQLOLEArticle
#define IID_ISQLOLEArticle IID_IWSQLOLEArticle 
#else
interface IASQLOLEArticle;				TYPEDEFINTERFACE IASQLOLEArticle *					LPASQLOLEARTICLE;
#define LPSQLOLEARTICLE LPASQLOLEARTICLE
#define ISQLOLEArticle IASQLOLEArticle
#define IID_ISQLOLEArticle IID_IASQLOLEArticle 
#endif

#undef LPSQLOLESUBSCRIPTIONS 
#undef ISQLOLESubscriptions 
#undef IID_ISQLOLESubscriptions 
#ifdef SQLOLE_UNICODE
interface IWSQLOLESubscriptions;			TYPEDEFINTERFACE IWSQLOLESubscriptions *					LPWSQLOLESUBSCRIPTIONS;
#define LPSQLOLESUBSCRIPTIONS LPWSQLOLESUBSCRIPTIONS
#define ISQLOLESubscriptions IWSQLOLESubscriptions
#define IID_ISQLOLESubscriptions IID_IWSQLOLESubscriptions 
#else
interface IASQLOLESubscriptions;			TYPEDEFINTERFACE IASQLOLESubscriptions *					LPASQLOLESUBSCRIPTIONS;
#define LPSQLOLESUBSCRIPTIONS LPASQLOLESUBSCRIPTIONS
#define ISQLOLESubscriptions IASQLOLESubscriptions
#define IID_ISQLOLESubscriptions IID_IASQLOLESubscriptions 
#endif

#undef LPSQLOLESUBSCRIPTION 
#undef ISQLOLESubscription 
#undef IID_ISQLOLESubscription 
#ifdef SQLOLE_UNICODE
interface IWSQLOLESubscription;				TYPEDEFINTERFACE IWSQLOLESubscription *					LPWSQLOLESUBSCRIPTION;
#define LPSQLOLESUBSCRIPTION LPWSQLOLESUBSCRIPTION
#define ISQLOLESubscription IWSQLOLESubscription
#define IID_ISQLOLESubscription IID_IWSQLOLESubscription 
#else
interface IASQLOLESubscription;				TYPEDEFINTERFACE IASQLOLESubscription *					LPASQLOLESUBSCRIPTION;
#define LPSQLOLESUBSCRIPTION LPASQLOLESUBSCRIPTION
#define ISQLOLESubscription IASQLOLESubscription
#define IID_ISQLOLESubscription IID_IASQLOLESubscription 
#endif

#undef LPSQLOLESUBSCRIBERINFO 
#undef ISQLOLESubscriberInfo 
#undef IID_ISQLOLESubscriberInfo 
#ifdef SQLOLE_UNICODE
interface IWSQLOLESubscriberInfo;				TYPEDEFINTERFACE IWSQLOLESubscriberInfo *					LPWSQLOLESUBSCRIBERINFO;
#define LPSQLOLESUBSCRIBERINFO LPWSQLOLESUBSCRIBERINFO
#define ISQLOLESubscriberInfo IWSQLOLESubscriberInfo
#define IID_ISQLOLESubscriberInfo IID_IWSQLOLESubscriberInfo 
#else
interface IASQLOLESubscriberInfo;				TYPEDEFINTERFACE IASQLOLESubscriberInfo *					LPASQLOLESUBSCRIBERINFO;
#define LPSQLOLESUBSCRIBERINFO LPASQLOLESUBSCRIBERINFO
#define ISQLOLESubscriberInfo IASQLOLESubscriberInfo
#define IID_ISQLOLESubscriberInfo IID_IASQLOLESubscriberInfo 
#endif

#undef LPSQLOLEHISTORYFILTER 
#undef ISQLOLEHistoryFilter 
#undef IID_ISQLOLEHistoryFilter 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEHistoryFilter;			TYPEDEFINTERFACE IWSQLOLEHistoryFilter *				LPWSQLOLEHISTORYFILTER;
#define LPSQLOLEHISTORYFILTER LPWSQLOLEHISTORYFILTER
#define ISQLOLEHistoryFilter IWSQLOLEHistoryFilter
#define IID_ISQLOLEHistoryFilter IID_IWSQLOLEHistoryFilter 
#else
interface IASQLOLEHistoryFilter;			TYPEDEFINTERFACE IASQLOLEHistoryFilter *				LPASQLOLEHISTORYFILTER;
#define LPSQLOLEHISTORYFILTER LPASQLOLEHISTORYFILTER
#define ISQLOLEHistoryFilter IASQLOLEHistoryFilter
#define IID_ISQLOLEHistoryFilter IID_IASQLOLEHistoryFilter 
#endif

#undef LPSQLOLEDBOBJECTS 
#undef ISQLOLEDBObjects 
#undef IID_ISQLOLEDBObjects 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEDBObjects;			TYPEDEFINTERFACE IWSQLOLEDBObjects *				LPWSQLOLEDBOBJECTS;
#define LPSQLOLEDBOBJECTS LPWSQLOLEDBOBJECTS
#define ISQLOLEDBObjects IWSQLOLEDBObjects
#define IID_ISQLOLEDBObjects IID_IWSQLOLEDBObjects 
#else
interface IASQLOLEDBObjects;			TYPEDEFINTERFACE IASQLOLEDBObjects *				LPASQLOLEDBOBJECTS;
#define LPSQLOLEDBOBJECTS LPASQLOLEDBOBJECTS
#define ISQLOLEDBObjects IASQLOLEDBObjects
#define IID_ISQLOLEDBObjects IID_IASQLOLEDBObjects 
#endif

#undef LPSQLOLEDBOBJECT 
#undef ISQLOLEDBObject 
#undef IID_ISQLOLEDBObject 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEDBObject;			TYPEDEFINTERFACE IWSQLOLEDBObject *				LPWSQLOLEDBOBJECT;
#define LPSQLOLEDBOBJECT LPWSQLOLEDBOBJECT
#define ISQLOLEDBObject IWSQLOLEDBObject
#define IID_ISQLOLEDBObject IID_IWSQLOLEDBObject 
#else
interface IASQLOLEDBObject;			TYPEDEFINTERFACE IASQLOLEDBObject *				LPASQLOLEDBOBJECT;
#define LPSQLOLEDBOBJECT LPASQLOLEDBOBJECT
#define ISQLOLEDBObject IASQLOLEDBObject
#define IID_ISQLOLEDBObject IID_IASQLOLEDBObject 
#endif

#undef LPSQLOLEDBOPTION 
#undef ISQLOLEDBOption 
#undef IID_ISQLOLEDBOption 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEDBOption;			TYPEDEFINTERFACE IWSQLOLEDBOption *				LPWSQLOLEDBOPTION;
#define LPSQLOLEDBOPTION LPWSQLOLEDBOPTION
#define ISQLOLEDBOption IWSQLOLEDBOption
#define IID_ISQLOLEDBOption IID_IWSQLOLEDBOption 
#else
interface IASQLOLEDBOption;			TYPEDEFINTERFACE IASQLOLEDBOption *				LPASQLOLEDBOPTION;
#define LPSQLOLEDBOPTION LPASQLOLEDBOPTION
#define ISQLOLEDBOption IASQLOLEDBOption
#define IID_ISQLOLEDBOption IID_IASQLOLEDBOption 
#endif

#undef LPSQLOLECONFIGURATION 
#undef ISQLOLEConfiguration 
#undef IID_ISQLOLEConfiguration 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEConfiguration;		TYPEDEFINTERFACE IWSQLOLEConfiguration *			LPWSQLOLECONFIGURATION;
#define LPSQLOLECONFIGURATION LPWSQLOLECONFIGURATION
#define ISQLOLEConfiguration IWSQLOLEConfiguration
#define IID_ISQLOLEConfiguration IID_IWSQLOLEConfiguration 
#else
interface IASQLOLEConfiguration;		TYPEDEFINTERFACE IASQLOLEConfiguration *			LPASQLOLECONFIGURATION;
#define LPSQLOLECONFIGURATION LPASQLOLECONFIGURATION
#define ISQLOLEConfiguration IASQLOLEConfiguration
#define IID_ISQLOLEConfiguration IID_IASQLOLEConfiguration 
#endif

#undef LPSQLOLECONFIGVALUES 
#undef ISQLOLEConfigValues 
#undef IID_ISQLOLEConfigValues 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEConfigValues;		TYPEDEFINTERFACE IWSQLOLEConfigValues *				LPWSQLOLECONFIGVALUES;
#define LPSQLOLECONFIGVALUES LPWSQLOLECONFIGVALUES
#define ISQLOLEConfigValues IWSQLOLEConfigValues
#define IID_ISQLOLEConfigValues IID_IWSQLOLEConfigValues 
#else
interface IASQLOLEConfigValues;		TYPEDEFINTERFACE IASQLOLEConfigValues *				LPASQLOLECONFIGVALUES;
#define LPSQLOLECONFIGVALUES LPASQLOLECONFIGVALUES
#define ISQLOLEConfigValues IASQLOLEConfigValues
#define IID_ISQLOLEConfigValues IID_IASQLOLEConfigValues 
#endif

#undef LPSQLOLECONFIGVALUE 
#undef ISQLOLEConfigValue 
#undef IID_ISQLOLEConfigValue 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEConfigValue;		TYPEDEFINTERFACE IWSQLOLEConfigValue *				LPWSQLOLECONFIGVALUE;
#define LPSQLOLECONFIGVALUE LPWSQLOLECONFIGVALUE
#define ISQLOLEConfigValue IWSQLOLEConfigValue
#define IID_ISQLOLEConfigValue IID_IWSQLOLEConfigValue 
#else
interface IASQLOLEConfigValue;		TYPEDEFINTERFACE IASQLOLEConfigValue *				LPASQLOLECONFIGVALUE;
#define LPSQLOLECONFIGVALUE LPASQLOLECONFIGVALUE
#define ISQLOLEConfigValue IASQLOLEConfigValue
#define IID_ISQLOLEConfigValue IID_IASQLOLEConfigValue 
#endif

#undef LPSQLOLEEXECUTIVE 
#undef ISQLOLEExecutive 
#undef IID_ISQLOLEExecutive 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEExecutive;			TYPEDEFINTERFACE IWSQLOLEExecutive *				LPWSQLOLEEXECUTIVE;
#define LPSQLOLEEXECUTIVE LPWSQLOLEEXECUTIVE
#define ISQLOLEExecutive IWSQLOLEExecutive
#define IID_ISQLOLEExecutive IID_IWSQLOLEExecutive 
#else
interface IASQLOLEExecutive;			TYPEDEFINTERFACE IASQLOLEExecutive *				LPASQLOLEEXECUTIVE;
#define LPSQLOLEEXECUTIVE LPASQLOLEEXECUTIVE
#define ISQLOLEExecutive IASQLOLEExecutive
#define IID_ISQLOLEExecutive IID_IASQLOLEExecutive 
#endif

#undef LPSQLOLEQUERYRESULTS 
#undef ISQLOLEQueryResults 
#undef IID_ISQLOLEQueryResults 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEQueryResults;		TYPEDEFINTERFACE IWSQLOLEQueryResults *			LPWSQLOLEQUERYRESULTS;
#define LPSQLOLEQUERYRESULTS LPWSQLOLEQUERYRESULTS
#define ISQLOLEQueryResults IWSQLOLEQueryResults
#define IID_ISQLOLEQueryResults IID_IWSQLOLEQueryResults 
#else
interface IASQLOLEQueryResults;		TYPEDEFINTERFACE IASQLOLEQueryResults *			LPASQLOLEQUERYRESULTS;
#define LPSQLOLEQUERYRESULTS LPASQLOLEQUERYRESULTS
#define ISQLOLEQueryResults IASQLOLEQueryResults
#define IID_ISQLOLEQueryResults IID_IASQLOLEQueryResults 
#endif

#undef LPSQLOLETRANSACTIONLOG 
#undef ISQLOLETransactionLog 
#undef IID_ISQLOLETransactionLog 
#ifdef SQLOLE_UNICODE
interface IWSQLOLETransactionLog;	TYPEDEFINTERFACE IWSQLOLETransactionLog *			LPWSQLOLETRANSACTIONLOG;
#define LPSQLOLETRANSACTIONLOG LPWSQLOLETRANSACTIONLOG
#define ISQLOLETransactionLog IWSQLOLETransactionLog
#define IID_ISQLOLETransactionLog IID_IWSQLOLETransactionLog 
#else
interface IASQLOLETransactionLog;	TYPEDEFINTERFACE IASQLOLETransactionLog *			LPASQLOLETRANSACTIONLOG;
#define LPSQLOLETRANSACTIONLOG LPASQLOLETRANSACTIONLOG
#define ISQLOLETransactionLog IASQLOLETransactionLog
#define IID_ISQLOLETransactionLog IID_IASQLOLETransactionLog 
#endif

#undef LPSQLOLEREGISTRY 
#undef ISQLOLERegistry 
#undef IID_ISQLOLERegistry 
#ifdef SQLOLE_UNICODE
interface IWSQLOLERegistry;			TYPEDEFINTERFACE IWSQLOLERegistry *				LPWSQLOLEREGISTRY;
#define LPSQLOLEREGISTRY LPWSQLOLEREGISTRY
#define ISQLOLERegistry IWSQLOLERegistry
#define IID_ISQLOLERegistry IID_IWSQLOLERegistry 
#else
interface IASQLOLERegistry;			TYPEDEFINTERFACE IASQLOLERegistry *				LPASQLOLEREGISTRY;
#define LPSQLOLEREGISTRY LPASQLOLEREGISTRY
#define ISQLOLERegistry IASQLOLERegistry
#define IID_ISQLOLERegistry IID_IASQLOLERegistry 
#endif

#undef LPSQLOLEBACKUP 
#undef ISQLOLEBackup 
#undef IID_ISQLOLEBackup 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEBackup;			TYPEDEFINTERFACE IWSQLOLEBackup *					LPWSQLOLEBACKUP;
#define LPSQLOLEBACKUP LPWSQLOLEBACKUP
#define ISQLOLEBackup IWSQLOLEBackup
#define IID_ISQLOLEBackup IID_IWSQLOLEBackup 
#else
interface IASQLOLEBackup;			TYPEDEFINTERFACE IASQLOLEBackup *					LPASQLOLEBACKUP;
#define LPSQLOLEBACKUP LPASQLOLEBACKUP
#define ISQLOLEBackup IASQLOLEBackup
#define IID_ISQLOLEBackup IID_IASQLOLEBackup 
#endif

#undef LPSQLOLEBULKCOPY 
#undef ISQLOLEBulkCopy 
#undef IID_ISQLOLEBulkCopy 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEBulkCopy;			TYPEDEFINTERFACE IWSQLOLEBulkCopy *					LPWSQLOLEBULKCOPY;
#define LPSQLOLEBULKCOPY LPWSQLOLEBULKCOPY
#define ISQLOLEBulkCopy IWSQLOLEBulkCopy
#define IID_ISQLOLEBulkCopy IID_IWSQLOLEBulkCopy 
#else
interface IASQLOLEBulkCopy;			TYPEDEFINTERFACE IASQLOLEBulkCopy *					LPASQLOLEBULKCOPY;
#define LPSQLOLEBULKCOPY LPASQLOLEBULKCOPY
#define ISQLOLEBulkCopy IASQLOLEBulkCopy
#define IID_ISQLOLEBulkCopy IID_IASQLOLEBulkCopy 
#endif

#undef LPSQLOLEOBJECTLIST 
#undef ISQLOLEObjectList 
#undef IID_ISQLOLEObjectList 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEObjectList;		TYPEDEFINTERFACE IWSQLOLEObjectList *				LPWSQLOLEOBJECTLIST;
#define LPSQLOLEOBJECTLIST LPWSQLOLEOBJECTLIST
#define ISQLOLEObjectList IWSQLOLEObjectList
#define IID_ISQLOLEObjectList IID_IWSQLOLEObjectList 
#else
interface IASQLOLEObjectList;		TYPEDEFINTERFACE IASQLOLEObjectList *				LPASQLOLEOBJECTLIST;
#define LPSQLOLEOBJECTLIST LPASQLOLEOBJECTLIST
#define ISQLOLEObjectList IASQLOLEObjectList
#define IID_ISQLOLEObjectList IID_IASQLOLEObjectList 
#endif

#undef LPSQLOLENAMES 
#undef ISQLOLENames 
#undef IID_ISQLOLENames 
#ifdef SQLOLE_UNICODE
interface IWSQLOLENames;		TYPEDEFINTERFACE IWSQLOLENames *				LPWSQLOLENAMES;
#define LPSQLOLENAMES LPWSQLOLENAMES
#define ISQLOLENames IWSQLOLENames
#define IID_ISQLOLENames IID_IWSQLOLENames 
#else
interface IASQLOLENames;		TYPEDEFINTERFACE IASQLOLENames *				LPASQLOLENAMES;
#define LPSQLOLENAMES LPASQLOLENAMES
#define ISQLOLENames IASQLOLENames
#define IID_ISQLOLENames IID_IASQLOLENames 
#endif

#undef LPSQLOLENAMELIST 
#undef ISQLOLENameList 
#undef IID_ISQLOLENameList 
#ifdef SQLOLE_UNICODE
interface IWSQLOLENameList;		TYPEDEFINTERFACE IWSQLOLENameList *				LPWSQLOLENAMELIST;
#define LPSQLOLENAMELIST LPWSQLOLENAMELIST
#define ISQLOLENameList IWSQLOLENameList
#define IID_ISQLOLENameList IID_IWSQLOLENameList 
#else
interface IASQLOLENameList;		TYPEDEFINTERFACE IASQLOLENameList *				LPASQLOLENAMELIST;
#define LPSQLOLENAMELIST LPASQLOLENAMELIST
#define ISQLOLENameList IASQLOLENameList
#define IID_ISQLOLENameList IID_IASQLOLENameList 
#endif

#undef LPSQLOLEPERMISSION 
#undef ISQLOLEPermission 
#undef IID_ISQLOLEPermission 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEPermission;		TYPEDEFINTERFACE IWSQLOLEPermission *				LPWSQLOLEPERMISSION;
#define LPSQLOLEPERMISSION LPWSQLOLEPERMISSION
#define ISQLOLEPermission IWSQLOLEPermission
#define IID_ISQLOLEPermission IID_IWSQLOLEPermission 
#else
interface IASQLOLEPermission;		TYPEDEFINTERFACE IASQLOLEPermission *				LPASQLOLEPERMISSION;
#define LPSQLOLEPERMISSION LPASQLOLEPERMISSION
#define ISQLOLEPermission IASQLOLEPermission
#define IID_ISQLOLEPermission IID_IASQLOLEPermission 
#endif

#undef LPSQLOLEINTEGRATEDSECURITY 
#undef ISQLOLEIntegratedSecurity 
#undef IID_ISQLOLEIntegratedSecurity 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEIntegratedSecurity;	TYPEDEFINTERFACE IWSQLOLEIntegratedSecurity *	LPWSQLOLEINTEGRATEDSECURITY;
#define LPSQLOLEINTEGRATEDSECURITY LPWSQLOLEINTEGRATEDSECURITY
#define ISQLOLEIntegratedSecurity IWSQLOLEIntegratedSecurity
#define IID_ISQLOLEIntegratedSecurity IID_IWSQLOLEIntegratedSecurity 
#else
interface IASQLOLEIntegratedSecurity;	TYPEDEFINTERFACE IASQLOLEIntegratedSecurity *	LPASQLOLEINTEGRATEDSECURITY;
#define LPSQLOLEINTEGRATEDSECURITY LPASQLOLEINTEGRATEDSECURITY
#define ISQLOLEIntegratedSecurity IASQLOLEIntegratedSecurity
#define IID_ISQLOLEIntegratedSecurity IID_IASQLOLEIntegratedSecurity 
#endif

#undef LPSQLOLEKEYS 
#undef ISQLOLEKeys 
#undef IID_ISQLOLEKeys 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEKeys;			TYPEDEFINTERFACE IWSQLOLEKeys *					LPWSQLOLEKEYS;
#define LPSQLOLEKEYS LPWSQLOLEKEYS
#define ISQLOLEKeys IWSQLOLEKeys
#define IID_ISQLOLEKeys IID_IWSQLOLEKeys 
#else
interface IASQLOLEKeys;			TYPEDEFINTERFACE IASQLOLEKeys *					LPASQLOLEKEYS;
#define LPSQLOLEKEYS LPASQLOLEKEYS
#define ISQLOLEKeys IASQLOLEKeys
#define IID_ISQLOLEKeys IID_IASQLOLEKeys 
#endif

#undef LPSQLOLEKEY 
#undef ISQLOLEKey 
#undef IID_ISQLOLEKey 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEKey;				TYPEDEFINTERFACE IWSQLOLEKey *					LPWSQLOLEKEY;
#define LPSQLOLEKEY LPWSQLOLEKEY
#define ISQLOLEKey IWSQLOLEKey
#define IID_ISQLOLEKey IID_IWSQLOLEKey 
#else
interface IASQLOLEKey;				TYPEDEFINTERFACE IASQLOLEKey *					LPASQLOLEKEY;
#define LPSQLOLEKEY LPASQLOLEKEY
#define ISQLOLEKey IASQLOLEKey
#define IID_ISQLOLEKey IID_IASQLOLEKey 
#endif

#undef LPSQLOLECHECKS 
#undef ISQLOLEChecks 
#undef IID_ISQLOLEChecks 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEChecks;			TYPEDEFINTERFACE IWSQLOLEChecks *					LPWSQLOLECHECKS;
#define LPSQLOLECHECKS LPWSQLOLECHECKS
#define ISQLOLEChecks IWSQLOLEChecks
#define IID_ISQLOLEChecks IID_IWSQLOLEChecks 
#else
interface IASQLOLEChecks;			TYPEDEFINTERFACE IASQLOLEChecks *					LPASQLOLECHECKS;
#define LPSQLOLECHECKS LPASQLOLECHECKS
#define ISQLOLEChecks IASQLOLEChecks
#define IID_ISQLOLEChecks IID_IASQLOLEChecks 
#endif

#undef LPSQLOLECHECK 
#undef ISQLOLECheck 
#undef IID_ISQLOLECheck 
#ifdef SQLOLE_UNICODE
interface IWSQLOLECheck;				TYPEDEFINTERFACE IWSQLOLECheck *					LPWSQLOLECHECK;
#define LPSQLOLECHECK LPWSQLOLECHECK
#define ISQLOLECheck IWSQLOLECheck
#define IID_ISQLOLECheck IID_IWSQLOLECheck 
#else
interface IASQLOLECheck;				TYPEDEFINTERFACE IASQLOLECheck *					LPASQLOLECHECK;
#define LPSQLOLECHECK LPASQLOLECHECK
#define ISQLOLECheck IASQLOLECheck
#define IID_ISQLOLECheck IID_IASQLOLECheck 
#endif

#undef LPSQLOLEDRIDEFAULT 
#undef ISQLOLEDRIDefault 
#undef IID_ISQLOLEDRIDefault 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEDRIDefault;				TYPEDEFINTERFACE IWSQLOLEDRIDefault *					LPWSQLOLEDRIDEFAULT;
#define LPSQLOLEDRIDEFAULT LPWSQLOLEDRIDEFAULT
#define ISQLOLEDRIDefault IWSQLOLEDRIDefault
#define IID_ISQLOLEDRIDefault IID_IWSQLOLEDRIDefault 
#else
interface IASQLOLEDRIDefault;				TYPEDEFINTERFACE IASQLOLEDRIDefault *					LPASQLOLEDRIDEFAULT;
#define LPSQLOLEDRIDEFAULT LPASQLOLEDRIDEFAULT
#define ISQLOLEDRIDefault IASQLOLEDRIDefault
#define IID_ISQLOLEDRIDefault IID_IASQLOLEDRIDefault 
#endif

#undef LPSQLOLEALERTSYSTEM 
#undef ISQLOLEAlertSystem 
#undef IID_ISQLOLEAlertSystem 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEAlertSystem;				TYPEDEFINTERFACE IWSQLOLEAlertSystem *					LPWSQLOLEALERTSYSTEM;
#define LPSQLOLEALERTSYSTEM LPWSQLOLEALERTSYSTEM
#define ISQLOLEAlertSystem IWSQLOLEAlertSystem
#define IID_ISQLOLEAlertSystem IID_IWSQLOLEAlertSystem 
#else
interface IASQLOLEAlertSystem;				TYPEDEFINTERFACE IASQLOLEAlertSystem *					LPASQLOLEALERTSYSTEM;
#define LPSQLOLEALERTSYSTEM LPASQLOLEALERTSYSTEM
#define ISQLOLEAlertSystem IASQLOLEAlertSystem
#define IID_ISQLOLEAlertSystem IID_IASQLOLEAlertSystem 
#endif

#undef LPSQLOLESERVERGROUPS 
#undef ISQLOLEServerGroups 
#undef IID_ISQLOLEServerGroups 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEServerGroups;			TYPEDEFINTERFACE IWSQLOLEServerGroups *					LPWSQLOLESERVERGROUPS;
#define LPSQLOLESERVERGROUPS LPWSQLOLESERVERGROUPS
#define ISQLOLEServerGroups IWSQLOLEServerGroups
#define IID_ISQLOLEServerGroups IID_IWSQLOLEServerGroups 
#else
interface IASQLOLEServerGroups;			TYPEDEFINTERFACE IASQLOLEServerGroups *					LPASQLOLESERVERGROUPS;
#define LPSQLOLESERVERGROUPS LPASQLOLESERVERGROUPS
#define ISQLOLEServerGroups IASQLOLEServerGroups
#define IID_ISQLOLEServerGroups IID_IASQLOLEServerGroups 
#endif

#undef LPSQLOLESERVERGROUP 
#undef ISQLOLEServerGroup 
#undef IID_ISQLOLEServerGroup 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEServerGroup;				TYPEDEFINTERFACE IWSQLOLEServerGroup *					LPWSQLOLESERVERGROUP;
#define LPSQLOLESERVERGROUP LPWSQLOLESERVERGROUP
#define ISQLOLEServerGroup IWSQLOLEServerGroup
#define IID_ISQLOLEServerGroup IID_IWSQLOLEServerGroup 
#else
interface IASQLOLEServerGroup;				TYPEDEFINTERFACE IASQLOLEServerGroup *					LPASQLOLESERVERGROUP;
#define LPSQLOLESERVERGROUP LPASQLOLESERVERGROUP
#define ISQLOLEServerGroup IASQLOLEServerGroup
#define IID_ISQLOLEServerGroup IID_IASQLOLEServerGroup 
#endif

#undef LPSQLOLEREGISTEREDSERVERS 
#undef ISQLOLERegisteredServers 
#undef IID_ISQLOLERegisteredServers 
#ifdef SQLOLE_UNICODE
interface IWSQLOLERegisteredServers;			TYPEDEFINTERFACE IWSQLOLERegisteredServers *					LPWSQLOLEREGISTEREDSERVERS;
#define LPSQLOLEREGISTEREDSERVERS LPWSQLOLEREGISTEREDSERVERS
#define ISQLOLERegisteredServers IWSQLOLERegisteredServers
#define IID_ISQLOLERegisteredServers IID_IWSQLOLERegisteredServers 
#else
interface IASQLOLERegisteredServers;			TYPEDEFINTERFACE IASQLOLERegisteredServers *					LPASQLOLEREGISTEREDSERVERS;
#define LPSQLOLEREGISTEREDSERVERS LPASQLOLEREGISTEREDSERVERS
#define ISQLOLERegisteredServers IASQLOLERegisteredServers
#define IID_ISQLOLERegisteredServers IID_IASQLOLERegisteredServers 
#endif

#undef LPSQLOLEREGISTEREDSERVER 
#undef ISQLOLERegisteredServer 
#undef IID_ISQLOLERegisteredServer 
#ifdef SQLOLE_UNICODE
interface IWSQLOLERegisteredServer;				TYPEDEFINTERFACE IWSQLOLERegisteredServer *					LPWSQLOLEREGISTEREDSERVER;
#define LPSQLOLEREGISTEREDSERVER LPWSQLOLEREGISTEREDSERVER
#define ISQLOLERegisteredServer IWSQLOLERegisteredServer
#define IID_ISQLOLERegisteredServer IID_IWSQLOLERegisteredServer 
#else
interface IASQLOLERegisteredServer;				TYPEDEFINTERFACE IASQLOLERegisteredServer *					LPASQLOLEREGISTEREDSERVER;
#define LPSQLOLEREGISTEREDSERVER LPASQLOLEREGISTEREDSERVER
#define ISQLOLERegisteredServer IASQLOLERegisteredServer
#define IID_ISQLOLERegisteredServer IID_IASQLOLERegisteredServer 
#endif

#undef LPSQLOLETRANSFER 
#undef ISQLOLETransfer 
#undef IID_ISQLOLETransfer 
#ifdef SQLOLE_UNICODE
interface IWSQLOLETransfer;						TYPEDEFINTERFACE IWSQLOLETransfer *				LPWSQLOLETRANSFER;
#define LPSQLOLETRANSFER LPWSQLOLETRANSFER
#define ISQLOLETransfer IWSQLOLETransfer
#define IID_ISQLOLETransfer IID_IWSQLOLETransfer 
#else
interface IASQLOLETransfer;						TYPEDEFINTERFACE IASQLOLETransfer *				LPASQLOLETRANSFER;
#define LPSQLOLETRANSFER LPASQLOLETRANSFER
#define ISQLOLETransfer IASQLOLETransfer
#define IID_ISQLOLETransfer IID_IASQLOLETransfer 
#endif

////////////////////////////////////////////////////////////////////////////////////////
// Event Sink Interfaces
////////////////////////////////////////////////////////////////////////////////////////
#undef LPSQLOLETRANSFERSINK 
#undef ISQLOLETransferSink
#undef IID_ISQLOLETransferSink 
#ifdef SQLOLE_UNICODE
interface IWSQLOLETransferSink;						TYPEDEFINTERFACE IWSQLOLETransferSink *				LPWSQLOLETRANSFERSINK;
#define LPSQLOLETRANSFERSINK LPWSQLOLETRANSFERSINK
#define ISQLOLETransferSink IWSQLOLETransferSink
#define IID_ISQLOLETransferSink IID_IWSQLOLETransferSink
#else
interface IASQLOLETransferSink;						TYPEDEFINTERFACE IASQLOLETransferSink *				LPASQLOLETRANSFERSINK;
#define LPSQLOLETRANSFERSINK LPASQLOLETRANSFERSINK
#define ISQLOLETransferSink IASQLOLETransferSink
#define IID_ISQLOLETransferSink IID_IASQLOLETransferSink
#endif

#undef LPSQLOLESERVERSINK 
#undef ISQLOLEServerSink
#undef IID_ISQLOLEServerSink 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEServerSink;						TYPEDEFINTERFACE IWSQLOLEServerSink *				LPWSQLOLESERVERSINK;
#define LPSQLOLESERVERSINK LPWSQLOLESERVERSINK
#define ISQLOLEServerSink IWSQLOLEServerSink
#define IID_ISQLOLEServerSink IID_IWSQLOLEServerSink
#else
interface IASQLOLEServerSink;						TYPEDEFINTERFACE IASQLOLEServerSink *				LPASQLOLESERVERSINK;
#define LPSQLOLESERVERSINK LPASQLOLESERVERSINK
#define ISQLOLEServerSink IASQLOLEServerSink
#define IID_ISQLOLEServerSink IID_IASQLOLEServerSink
#endif

#undef LPSQLOLEBACKUPSINK 
#undef ISQLOLEBackupSink
#undef IID_ISQLOLEBackupSink 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEBackupSink;						TYPEDEFINTERFACE IWSQLOLEBackupSink *				LPWSQLOLEBACKUPSINK;
#define LPSQLOLEBACKUPSINK LPWSQLOLEBACKUPSINK
#define ISQLOLEBackupSink IWSQLOLEBackupSink
#define IID_ISQLOLEBackupSink IID_IWSQLOLEBackupSink
#else
interface IASQLOLEBackupSink;						TYPEDEFINTERFACE IASQLOLEBackupSink *				LPASQLOLEBACKUPSINK;
#define LPSQLOLEBACKUPSINK LPASQLOLEBACKUPSINK
#define ISQLOLEBackupSink IASQLOLEBackupSink
#define IID_ISQLOLEBackupSink IID_IASQLOLEBackupSink
#endif

#undef LPSQLOLEBULKCOPYSINK 
#undef ISQLOLEBulkCopySink
#undef IID_ISQLOLEBulkCopySink 
#ifdef SQLOLE_UNICODE
interface IWSQLOLEBulkCopySink;						TYPEDEFINTERFACE IWSQLOLEBulkCopySink *				LPWSQLOLEBULKCOPYSINK;
#define LPSQLOLEBULKCOPYSINK LPWSQLOLEBULKCOPYSINK
#define ISQLOLEBulkCopySink IWSQLOLEBulkCopySink
#define IID_ISQLOLEBulkCopySink IID_IWSQLOLEBulkCopySink
#else
interface IASQLOLEBulkCopySink;						TYPEDEFINTERFACE IASQLOLEBulkCopySink *				LPASQLOLEBULKCOPYSINK;
#define LPSQLOLEBULKCOPYSINK LPASQLOLEBULKCOPYSINK
#define ISQLOLEBulkCopySink IASQLOLEBulkCopySink
#define IID_ISQLOLEBulkCopySink IID_IASQLOLEBulkCopySink
#endif

// Auto-documenting names for these... They return an LPSQLOLEOBJECTLIST
// of the specified <objecttype>LIST objects.. e.g. LPSQLOLECOLUMNLIST
// returns a list of LPSQLOLECOLUMN objects.
#undef LPSQLOLEDBOBJECTLIST
#define LPSQLOLEDBOBJECTLIST LPSQLOLEOBJECTLIST
#define LPWSQLOLEDBOBJECTLIST LPWSQLOLEOBJECTLIST
#define LPASQLOLEDBOBJECTLIST LPASQLOLEOBJECTLIST
#undef LPSQLOLEPERMISSIONLIST
#define LPSQLOLEPERMISSIONLIST LPSQLOLEOBJECTLIST
#define LPWSQLOLEPERMISSIONLIST LPWSQLOLEOBJECTLIST
#define LPASQLOLEPERMISSIONLIST LPASQLOLEOBJECTLIST
#undef LPSQLOLECONFIGVALUELIST
#define LPSQLOLECONFIGVALUELIST LPSQLOLEOBJECTLIST
#define LPWSQLOLECONFIGVALUELIST LPWSQLOLEOBJECTLIST
#define LPASQLOLECONFIGVALUELIST LPASQLOLEOBJECTLIST
#undef LPSQLOLEDEVICELIST
#define LPSQLOLEDEVICELIST LPSQLOLEOBJECTLIST
#define LPWSQLOLEDEVICELIST LPWSQLOLEOBJECTLIST
#define LPASQLOLEDEVICELIST LPASQLOLEOBJECTLIST
#undef LPSQLOLECOLUMNLIST
#define LPSQLOLECOLUMNLIST LPSQLOLEOBJECTLIST
#define LPWSQLOLECOLUMNLIST LPWSQLOLEOBJECTLIST
#define LPASQLOLECOLUMNLIST LPASQLOLEOBJECTLIST
#undef LPSQLOLEUSERDEFINEDDATATYPELIST
#define LPSQLOLEUSERDEFINEDDATATYPELIST LPSQLOLEOBJECTLIST
#define LPWSQLOLEUSERDEFINEDDATATYPELIST LPWSQLOLEOBJECTLIST
#define LPASQLOLEUSERDEFINEDDATATYPELIST LPASQLOLEOBJECTLIST
#undef LPSQLOLESTOREDPROCEDURELIST
#define LPSQLOLESTOREDPROCEDURELIST LPSQLOLEOBJECTLIST
#define LPWSQLOLESTOREDPROCEDURELIST LPWSQLOLEOBJECTLIST
#define LPASQLOLESTOREDPROCEDURELIST LPASQLOLEOBJECTLIST
#undef LPSQLOLELOGINLIST
#define LPSQLOLELOGINLIST LPSQLOLEOBJECTLIST
#define LPWSQLOLELOGINLIST LPWSQLOLEOBJECTLIST
#define LPASQLOLELOGINLIST LPASQLOLEOBJECTLIST
#undef LPSQLOLEUSERLIST
#define LPSQLOLEUSERLIST LPSQLOLEOBJECTLIST
#define LPWSQLOLEUSERLIST LPWSQLOLEOBJECTLIST
#define LPASQLOLEUSERLIST LPASQLOLEOBJECTLIST
#undef LPSQLOLEDATABASELIST
#define LPSQLOLEDATABASELIST LPSQLOLEOBJECTLIST
#define LPWSQLOLEDATABASELIST LPWSQLOLEOBJECTLIST
#define LPASQLOLEDATABASELIST LPASQLOLEOBJECTLIST
#undef LPSQLOLETASKLIST
#define LPSQLOLETASKLIST LPSQLOLEOBJECTLIST
#define LPWSQLOLETASKLIST LPWSQLOLEOBJECTLIST
#define LPASQLOLETASKLIST LPASQLOLEOBJECTLIST
#undef LPSQLOLEARTICLELIST
#define LPSQLOLEARTICLELIST LPSQLOLEOBJECTLIST
#define LPWSQLOLEARTICLELIST LPWSQLOLEOBJECTLIST
#define LPASQLOLEARTICLELIST LPASQLOLEOBJECTLIST
#undef LPSQLOLEKEYLIST
#define LPSQLOLEKEYLIST LPSQLOLEOBJECTLIST
#define LPWSQLOLEKEYLIST LPWSQLOLEOBJECTLIST
#define LPASQLOLEKEYLIST LPASQLOLEOBJECTLIST

// This is the base class for all SQLOLE objects.  It is never instantiated by itself.
// The members must be copied into all derived classes so that C clients can reference
// them, since the DECLARE_INTERFACE_ macro doesn't provide inheritance in C.  The
// undef/def of INTERFACE is likewise required for C programmers.
#undef INTERFACE
#define INTERFACE ISQLOLEStdObject
DECLARE_INTERFACE_(INTERFACE, IUnknown)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;
};

#ifdef __cplusplus
#ifndef CTEMPOLEREF_DEFINED
#define CTEMPOLEREF_DEFINED
// This is a utility class that takes an IUnknown-derived pointer as input and automatically
// Release()s it in dtor.  Use this as a stack variable which will hold objects and
// Release() them when they go out of scope; useful if multiple exit points.
template < class OLEPTR> class CTempOLERef {
	OLEPTR m_oleptr;

	// Private copy operators -- we don't want these used due to refcounting issues.
	// Since they can't therefore be called, no need to assign a body.
	CTempOLERef(const CTempOLERef<OLEPTR>& Src);
	OLEPTR  operator = (const CTempOLERef<OLEPTR>& Src);

public:
	CTempOLERef() {m_oleptr = NULL;}
	CTempOLERef(OLEPTR pIn) {m_oleptr = pIn;}
	~CTempOLERef() {if (m_oleptr) m_oleptr->Release();}
	OLEPTR p() {return m_oleptr;}				// Alternative to casting (better for cut 'n paste).

	operator OLEPTR () {return m_oleptr;}		// Return the input pointer on a cast
	operator LPUNKNOWN () {return m_oleptr;}
	operator void *() {return (void *)m_oleptr;}
	operator BOOL () {return m_oleptr ? TRUE : FALSE;}
	OLEPTR  operator = (OLEPTR pIn) {if (m_oleptr) m_oleptr->Release(); return m_oleptr = pIn;}
	OLEPTR * operator & () {return &m_oleptr;}	// Overload address-of operator
	BOOL operator ! () {return m_oleptr ? FALSE : TRUE;}
	OLEPTR operator -> () {return m_oleptr;}	// Pass operator-> thru to m_oleptr; allows tempxxxRef->xxxSpecificMember();

	// Apps should not Release() this object directly as it is intended to do so as it goes out of scope,
	// hence as a safety feature to avoid double-Release() clear the pointer if it's called directly.
	void Release() {if (m_oleptr) m_oleptr->Release(); m_oleptr = NULL;}
};

// Similar to above, for use with SQLOLE_BSTR's
class CTempBSTR {
	SQLOLE_BSTR m_bstr;

	// Private copy operators -- we don't want these used due to refcounting issues.
	// Since they can't therefore be called, no need to assign a body.
	CTempBSTR(const CTempBSTR& Src);
	SQLOLE_BSTR  operator = (const CTempBSTR& Src);

public:
	CTempBSTR() {m_bstr = NULL;}
	CTempBSTR(SQLOLE_BSTR bstrIn) {m_bstr = bstrIn;}
	~CTempBSTR() {Free();}
	void Free() {if (m_bstr) {SQLOLEFreeString(m_bstr); m_bstr = NULL;}}
	SQLOLE_BSTR b() {return m_bstr;}

	operator SQLOLE_LPCSTR () {return (SQLOLE_LPCSTR)m_bstr;}
	operator void *() {return (void *)m_bstr;}
	SQLOLE_BSTR operator = (SQLOLE_BSTR bstrIn) {Free(); return m_bstr = bstrIn;}
	SQLOLE_BSTR * operator & () {return &m_bstr;}		// Overload address-of operator
	BOOL operator ! () {return m_bstr ? FALSE : TRUE;}
};

#endif  // CTEMPOLEREF_DEFINED
#endif	// __cplusplus

///////////////////////////
// Collection interfaces.
///////////////////////////
#undef INTERFACE
#define INTERFACE ISQLOLEServers
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

    //*** SQLOLE standard enumeration properties
	STDMETHOD(GetItemByOrd)(THIS_ long lOrdinal, LPSQLOLESERVER *ppObj) PURE;
	STDMETHOD(GetItemByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLESERVER *ppObj) PURE;
    STDMETHOD(GetItemByID)(THIS_ long lID, LPSQLOLESERVER *ppObj) PURE;
	STDMETHOD(GetCount)(THIS_ LPLONG plCount) PURE;
};

// Generic enumerator object.
#undef INTERFACE
#define INTERFACE ISQLOLEObjectList
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

    //*** SQLOLE standard enumeration properties.  The object returned must be
    //*** cast to the appropriate object type; the type to cast to is indicated
    //*** by the LPSQLOLE<objecttype>LIST typedef of the returned list object.
    //*** e.g. LPSQLOLECOLUMNLIST returns a list of objects which cast to LPSQLOLECOLUMN.
	STDMETHOD(GetItemByOrd)(THIS_ long lOrdinal, LPSQLOLESTDOBJECT *ppObject) PURE;
	STDMETHOD(GetItemByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLESTDOBJECT *ppObject) PURE;
	STDMETHOD(GetCount)(THIS_ LPLONG plCount) PURE;
	STDMETHOD(Refresh)(THIS) PURE;
};

// Names collection object (LPSQLOLENAMES).
#undef INTERFACE
#define INTERFACE ISQLOLENames
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

    //*** SQLOLE standard enumeration properties
	STDMETHOD(GetItemByOrd)(THIS_ long lOrdinal, SQLOLE_LPBSTR pRetVal) PURE;
	STDMETHOD(GetCount)(THIS_ LPLONG plCount) PURE;

    //*** SQLOLE standard collection methods
	STDMETHOD(Add)(THIS_ SQLOLE_LPCSTR szName) PURE;
	STDMETHOD(RemoveByOrd)(THIS_ long lOrdinal) PURE;
	STDMETHOD(RemoveByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
	STDMETHOD(Refresh)(THIS) PURE;
	STDMETHOD(InsertByOrd)(THIS_ SQLOLE_LPCSTR szName, long lOrdinal) PURE;
	STDMETHOD(InsertByName)(THIS_ SQLOLE_LPCSTR szName, SQLOLE_LPCSTR szBeforeName) PURE;
	STDMETHOD(ReplaceByOrd)(THIS_ SQLOLE_LPCSTR szName, long lOrdinal) PURE;
	STDMETHOD(ReplaceByName)(THIS_ SQLOLE_LPCSTR szName, SQLOLE_LPCSTR szReplaceName) PURE;
	STDMETHOD(FindName)(THIS_ SQLOLE_LPCSTR szName, LPLONG pRetVal) PURE;
};

// Names enumerator object (LPSQLOLENAMELIST).
#undef INTERFACE
#define INTERFACE ISQLOLENameList
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

    //*** SQLOLE standard enumeration properties
	STDMETHOD(GetItemByOrd)(THIS_ long lOrdinal, SQLOLE_LPBSTR pRetVal) PURE;
	STDMETHOD(GetCount)(THIS_ LPLONG plCount) PURE;

    //*** SQLOLE standard collection methods
	STDMETHOD(Refresh)(THIS) PURE;
	STDMETHOD(FindName)(THIS_ SQLOLE_LPCSTR szName, LPLONG pRetVal) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLEDatabases
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

    //*** SQLOLE standard enumeration properties
	STDMETHOD(GetItemByOrd)(THIS_ long lOrdinal, LPSQLOLEDATABASE *ppObj) PURE;
	STDMETHOD(GetItemByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLEDATABASE *ppObj) PURE;
    STDMETHOD(GetItemByID)(THIS_ long lID, LPSQLOLEDATABASE *ppObj) PURE;
	STDMETHOD(GetCount)(THIS_ LPLONG plCount) PURE;

    //*** SQLOLE standard collection methods
	STDMETHOD(Add)(THIS_ LPSQLOLEDATABASE Object) PURE;
	STDMETHOD(RemoveByOrd)(THIS_ long lOrdinal) PURE;
	STDMETHOD(RemoveByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
	STDMETHOD(Refresh)(THIS_ BOOL bReleaseMemberObjects CPPDEFAULT(= FALSE)) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLETasks
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

    //*** SQLOLE standard enumeration properties
	STDMETHOD(GetItemByOrd)(THIS_ long lOrdinal, LPSQLOLETASK *ppObj) PURE;
	STDMETHOD(GetItemByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLETASK *ppObj) PURE;
    STDMETHOD(GetItemByID)(THIS_ long lID, LPSQLOLETASK *ppObj) PURE;
	STDMETHOD(GetCount)(THIS_ LPLONG plCount) PURE;

    //*** SQLOLE standard collection methods
	STDMETHOD(Add)(THIS_ LPSQLOLETASK Object) PURE;
	STDMETHOD(RemoveByOrd)(THIS_ long lOrdinal) PURE;
	STDMETHOD(RemoveByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
	STDMETHOD(Refresh)(THIS_ BOOL bReleaseMemberObjects CPPDEFAULT(= FALSE)) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLEAlerts
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

    //*** SQLOLE standard enumeration properties
	STDMETHOD(GetItemByOrd)(THIS_ long lOrdinal, LPSQLOLEALERT *ppObj) PURE;
	STDMETHOD(GetItemByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLEALERT *ppObj) PURE;
    STDMETHOD(GetItemByID)(THIS_ long lID, LPSQLOLEALERT *ppObj) PURE;
	STDMETHOD(GetCount)(THIS_ LPLONG plCount) PURE;

    //*** SQLOLE standard collection methods
	STDMETHOD(Add)(THIS_ LPSQLOLEALERT Object) PURE;
	STDMETHOD(RemoveByOrd)(THIS_ long lOrdinal) PURE;
	STDMETHOD(RemoveByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
	STDMETHOD(Refresh)(THIS_ BOOL bReleaseMemberObjects CPPDEFAULT(= FALSE)) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLEOperators
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

    //*** SQLOLE standard enumeration properties
	STDMETHOD(GetItemByOrd)(THIS_ long lOrdinal, LPSQLOLEOPERATOR *ppObj) PURE;
	STDMETHOD(GetItemByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLEOPERATOR *ppObj) PURE;
    STDMETHOD(GetItemByID)(THIS_ long lID, LPSQLOLEOPERATOR *ppObj) PURE;
	STDMETHOD(GetCount)(THIS_ LPLONG plCount) PURE;

    //*** SQLOLE standard collection methods
	STDMETHOD(Add)(THIS_ LPSQLOLEOPERATOR Object) PURE;
	STDMETHOD(RemoveByOrd)(THIS_ long lOrdinal) PURE;
	STDMETHOD(RemoveByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
	STDMETHOD(Refresh)(THIS_ BOOL bReleaseMemberObjects CPPDEFAULT(= FALSE)) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLEPublications
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

    //*** SQLOLE standard enumeration properties
	STDMETHOD(GetItemByOrd)(THIS_ long lOrdinal, LPSQLOLEPUBLICATION *ppObj) PURE;
	STDMETHOD(GetItemByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLEPUBLICATION *ppObj) PURE;
    STDMETHOD(GetItemByID)(THIS_ long lID, LPSQLOLEPUBLICATION *ppObj) PURE;
	STDMETHOD(GetCount)(THIS_ LPLONG plCount) PURE;

    //*** SQLOLE standard collection methods
	STDMETHOD(Add)(THIS_ LPSQLOLEPUBLICATION Object) PURE;
	STDMETHOD(RemoveByOrd)(THIS_ long lOrdinal) PURE;
	STDMETHOD(RemoveByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
	STDMETHOD(Refresh)(THIS_ BOOL bReleaseMemberObjects CPPDEFAULT(= FALSE)) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLEArticles
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

    //*** SQLOLE standard enumeration properties
	STDMETHOD(GetItemByOrd)(THIS_ long lOrdinal, LPSQLOLEARTICLE *ppObj) PURE;
	STDMETHOD(GetItemByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLEARTICLE *ppObj) PURE;
    STDMETHOD(GetItemByID)(THIS_ long lID, LPSQLOLEARTICLE *ppObj) PURE;
	STDMETHOD(GetCount)(THIS_ LPLONG plCount) PURE;

    //*** SQLOLE standard collection methods
	STDMETHOD(Add)(THIS_ LPSQLOLEARTICLE Object) PURE;
	STDMETHOD(RemoveByOrd)(THIS_ long lOrdinal) PURE;
	STDMETHOD(RemoveByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
	STDMETHOD(Refresh)(THIS_ BOOL bReleaseMemberObjects CPPDEFAULT(= FALSE)) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLESubscriptions
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

    //*** SQLOLE standard enumeration properties
	STDMETHOD(GetItemByOrd)(THIS_ long lOrdinal, LPSQLOLESUBSCRIPTION *ppObj) PURE;
	STDMETHOD(GetItemByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLESUBSCRIPTION *ppObj) PURE;
	STDMETHOD(GetCount)(THIS_ LPLONG plCount) PURE;

    //*** SQLOLE standard collection methods
	STDMETHOD(Add)(THIS_ LPSQLOLESUBSCRIPTION Object) PURE;
	STDMETHOD(RemoveByOrd)(THIS_ long lOrdinal) PURE;
	STDMETHOD(RemoveByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
	STDMETHOD(Refresh)(THIS_ BOOL bReleaseMemberObjects CPPDEFAULT(= FALSE)) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLEDevices
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

    //*** SQLOLE standard enumeration properties
	STDMETHOD(GetItemByOrd)(THIS_ long lOrdinal, LPSQLOLEDEVICE *ppObj) PURE;
	STDMETHOD(GetItemByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLEDEVICE *ppObj) PURE;
	STDMETHOD(GetCount)(THIS_ LPLONG plCount) PURE;

    //*** SQLOLE standard collection methods
	STDMETHOD(Add)(THIS_ LPSQLOLEDEVICE Object) PURE;
	STDMETHOD(RemoveByOrd)(THIS_ long lOrdinal) PURE;
	STDMETHOD(RemoveByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
	STDMETHOD(Refresh)(THIS_ BOOL bReleaseMemberObjects CPPDEFAULT(= FALSE)) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLELogins
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

    //*** SQLOLE standard enumeration properties
	STDMETHOD(GetItemByOrd)(THIS_ long lOrdinal, LPSQLOLELOGIN *ppObj) PURE;
	STDMETHOD(GetItemByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLELOGIN *ppObj) PURE;
    STDMETHOD(GetItemByID)(THIS_ long lID, LPSQLOLELOGIN *ppObj) PURE;
	STDMETHOD(GetCount)(THIS_ LPLONG plCount) PURE;

    //*** SQLOLE standard collection methods
	STDMETHOD(Add)(THIS_ LPSQLOLELOGIN Object) PURE;
	STDMETHOD(RemoveByOrd)(THIS_ long lOrdinal) PURE;
	STDMETHOD(RemoveByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
	STDMETHOD(Refresh)(THIS_ BOOL bReleaseMemberObjects CPPDEFAULT(= FALSE)) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLELanguages
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

    //*** SQLOLE standard enumeration properties
	STDMETHOD(GetItemByOrd)(THIS_ long lOrdinal, LPSQLOLELANGUAGE *ppObj) PURE;
	STDMETHOD(GetItemByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLELANGUAGE *ppObj) PURE;
    STDMETHOD(GetItemByID)(THIS_ long lID, LPSQLOLELANGUAGE *ppObj) PURE;
	STDMETHOD(GetCount)(THIS_ LPLONG plCount) PURE;

    //*** SQLOLE standard collection methods
	STDMETHOD(Add)(THIS_ LPSQLOLELANGUAGE Object) PURE;
	STDMETHOD(RemoveByOrd)(THIS_ long lOrdinal) PURE;
	STDMETHOD(RemoveByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
	STDMETHOD(Refresh)(THIS_ BOOL bReleaseMemberObjects CPPDEFAULT(= FALSE)) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLETables
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

    //*** SQLOLE standard enumeration properties
	STDMETHOD(GetItemByOrd)(THIS_ long lOrdinal, LPSQLOLETABLE *ppObj) PURE;
	STDMETHOD(GetItemByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLETABLE *ppObj) PURE;
    STDMETHOD(GetItemByID)(THIS_ long lID, LPSQLOLETABLE *ppObj) PURE;
	STDMETHOD(GetCount)(THIS_ LPLONG plCount) PURE;

    //*** SQLOLE standard collection methods
	STDMETHOD(Add)(THIS_ LPSQLOLETABLE Object) PURE;
	STDMETHOD(RemoveByOrd)(THIS_ long lOrdinal) PURE;
	STDMETHOD(RemoveByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
	STDMETHOD(Refresh)(THIS_ BOOL bReleaseMemberObjects CPPDEFAULT(= FALSE)) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLEViews
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

    //*** SQLOLE standard enumeration properties
	STDMETHOD(GetItemByOrd)(THIS_ long lOrdinal, LPSQLOLEVIEW *ppObj) PURE;
	STDMETHOD(GetItemByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLEVIEW *ppObj) PURE;
    STDMETHOD(GetItemByID)(THIS_ long lID, LPSQLOLEVIEW *ppObj) PURE;
	STDMETHOD(GetCount)(THIS_ LPLONG plCount) PURE;

    //*** SQLOLE standard collection methods
	STDMETHOD(Add)(THIS_ LPSQLOLEVIEW Object) PURE;
	STDMETHOD(RemoveByOrd)(THIS_ long lOrdinal) PURE;
	STDMETHOD(RemoveByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
	STDMETHOD(Refresh)(THIS_ BOOL bReleaseMemberObjects CPPDEFAULT(= FALSE)) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLERules
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

    //*** SQLOLE standard enumeration properties
	STDMETHOD(GetItemByOrd)(THIS_ long lOrdinal, LPSQLOLERULE *ppObj) PURE;
	STDMETHOD(GetItemByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLERULE *ppObj) PURE;
    STDMETHOD(GetItemByID)(THIS_ long lID, LPSQLOLERULE *ppObj) PURE;
	STDMETHOD(GetCount)(THIS_ LPLONG plCount) PURE;

    //*** SQLOLE standard collection methods
	STDMETHOD(Add)(THIS_ LPSQLOLERULE Object) PURE;
	STDMETHOD(RemoveByOrd)(THIS_ long lOrdinal) PURE;
	STDMETHOD(RemoveByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
	STDMETHOD(Refresh)(THIS_ BOOL bReleaseMemberObjects CPPDEFAULT(= FALSE)) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLEDefaults
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

    //*** SQLOLE standard enumeration properties
	STDMETHOD(GetItemByOrd)(THIS_ long lOrdinal, LPSQLOLEDEFAULT *ppObj) PURE;
	STDMETHOD(GetItemByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLEDEFAULT *ppObj) PURE;
    STDMETHOD(GetItemByID)(THIS_ long lID, LPSQLOLEDEFAULT *ppObj) PURE;
	STDMETHOD(GetCount)(THIS_ LPLONG plCount) PURE;

    //*** SQLOLE standard collection methods
	STDMETHOD(Add)(THIS_ LPSQLOLEDEFAULT Object) PURE;
	STDMETHOD(RemoveByOrd)(THIS_ long lOrdinal) PURE;
	STDMETHOD(RemoveByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
	STDMETHOD(Refresh)(THIS_ BOOL bReleaseMemberObjects CPPDEFAULT(= FALSE)) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLEColumns
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

    //*** SQLOLE standard enumeration properties
	STDMETHOD(GetItemByOrd)(THIS_ long lOrdinal, LPSQLOLECOLUMN *ppObj) PURE;
	STDMETHOD(GetItemByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLECOLUMN *ppObj) PURE;
    STDMETHOD(GetItemByID)(THIS_ long lID, LPSQLOLECOLUMN *ppObj) PURE;
	STDMETHOD(GetCount)(THIS_ LPLONG plCount) PURE;

    //*** SQLOLE standard collection methods
	STDMETHOD(Add)(THIS_ LPSQLOLECOLUMN Object) PURE;
	STDMETHOD(RemoveByOrd)(THIS_ long lOrdinal) PURE;
	STDMETHOD(RemoveByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
	STDMETHOD(Refresh)(THIS_ BOOL bReleaseMemberObjects CPPDEFAULT(= FALSE)) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLEIndexes
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

    //*** SQLOLE standard enumeration properties
	STDMETHOD(GetItemByOrd)(THIS_ long lOrdinal, LPSQLOLEINDEX *ppObj) PURE;
	STDMETHOD(GetItemByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLEINDEX *ppObj) PURE;
    STDMETHOD(GetItemByID)(THIS_ long lID, LPSQLOLEINDEX *ppObj) PURE;
	STDMETHOD(GetCount)(THIS_ LPLONG plCount) PURE;

    //*** SQLOLE standard collection methods
	STDMETHOD(Add)(THIS_ LPSQLOLEINDEX Object) PURE;
	STDMETHOD(RemoveByOrd)(THIS_ long lOrdinal) PURE;
	STDMETHOD(RemoveByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
	STDMETHOD(Refresh)(THIS_ BOOL bReleaseMemberObjects CPPDEFAULT(= FALSE)) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLEKeys
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

    //*** SQLOLE standard enumeration properties
	STDMETHOD(GetItemByOrd)(THIS_ long lOrdinal, LPSQLOLEKEY *ppObj) PURE;
	STDMETHOD(GetItemByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLEKEY *ppObj) PURE;
	STDMETHOD(GetCount)(THIS_ LPLONG plCount) PURE;

    //*** SQLOLE standard collection methods
	STDMETHOD(Add)(THIS_ LPSQLOLEKEY Object) PURE;
	STDMETHOD(RemoveByOrd)(THIS_ long lOrdinal) PURE;
	STDMETHOD(RemoveByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
	STDMETHOD(Refresh)(THIS_ BOOL bReleaseMemberObjects CPPDEFAULT(= FALSE)) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLEStoredProcedures
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

    //*** SQLOLE standard enumeration properties
	STDMETHOD(GetItemByOrd)(THIS_ long lOrdinal, LPSQLOLESTOREDPROCEDURE *ppObj) PURE;
	STDMETHOD(GetItemByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLESTOREDPROCEDURE *ppObj) PURE;
    STDMETHOD(GetItemByID)(THIS_ long lID, LPSQLOLESTOREDPROCEDURE *ppObj) PURE;
	STDMETHOD(GetCount)(THIS_ LPLONG plCount) PURE;

    //*** SQLOLE standard collection methods
	STDMETHOD(Add)(THIS_ LPSQLOLESTOREDPROCEDURE Object) PURE;
	STDMETHOD(RemoveByOrd)(THIS_ long lOrdinal) PURE;
	STDMETHOD(RemoveByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
	STDMETHOD(Refresh)(THIS_ BOOL bReleaseMemberObjects CPPDEFAULT(= FALSE)) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLEUserDefinedDatatypes
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

    //*** SQLOLE standard enumeration properties
	STDMETHOD(GetItemByOrd)(THIS_ long lOrdinal, LPSQLOLEUSERDEFINEDDATATYPE *ppObj) PURE;
	STDMETHOD(GetItemByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLEUSERDEFINEDDATATYPE *ppObj) PURE;
    STDMETHOD(GetItemByID)(THIS_ long lID, LPSQLOLEUSERDEFINEDDATATYPE *ppObj) PURE;
	STDMETHOD(GetCount)(THIS_ LPLONG plCount) PURE;

    //*** SQLOLE standard collection methods
	STDMETHOD(Add)(THIS_ LPSQLOLEUSERDEFINEDDATATYPE Object) PURE;
	STDMETHOD(RemoveByOrd)(THIS_ long lOrdinal) PURE;
	STDMETHOD(RemoveByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
	STDMETHOD(Refresh)(THIS_ BOOL bReleaseMemberObjects CPPDEFAULT(= FALSE)) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLEUsers
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

    //*** SQLOLE standard enumeration properties
	STDMETHOD(GetItemByOrd)(THIS_ long lOrdinal, LPSQLOLEUSER *ppObj) PURE;
	STDMETHOD(GetItemByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLEUSER *ppObj) PURE;
    STDMETHOD(GetItemByID)(THIS_ long lID, LPSQLOLEUSER *ppObj) PURE;
	STDMETHOD(GetCount)(THIS_ LPLONG plCount) PURE;

    //*** SQLOLE standard collection methods
	STDMETHOD(Add)(THIS_ LPSQLOLEUSER Object) PURE;
	STDMETHOD(RemoveByOrd)(THIS_ long lOrdinal) PURE;
	STDMETHOD(RemoveByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
	STDMETHOD(Refresh)(THIS_ BOOL bReleaseMemberObjects CPPDEFAULT(= FALSE)) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLEGroups
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

    //*** SQLOLE standard enumeration properties
	STDMETHOD(GetItemByOrd)(THIS_ long lOrdinal, LPSQLOLEGROUP *ppObj) PURE;
	STDMETHOD(GetItemByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLEGROUP *ppObj) PURE;
    STDMETHOD(GetItemByID)(THIS_ long lID, LPSQLOLEGROUP *ppObj) PURE;
	STDMETHOD(GetCount)(THIS_ LPLONG plCount) PURE;

    //*** SQLOLE standard collection methods
	STDMETHOD(Add)(THIS_ LPSQLOLEGROUP Object) PURE;
	STDMETHOD(RemoveByOrd)(THIS_ long lOrdinal) PURE;
	STDMETHOD(RemoveByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
	STDMETHOD(Refresh)(THIS_ BOOL bReleaseMemberObjects CPPDEFAULT(= FALSE)) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLETriggers
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

    //*** SQLOLE standard enumeration properties
	STDMETHOD(GetItemByOrd)(THIS_ long lOrdinal, LPSQLOLETRIGGER *ppObj) PURE;
	STDMETHOD(GetItemByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLETRIGGER *ppObj) PURE;
    STDMETHOD(GetItemByID)(THIS_ long lID, LPSQLOLETRIGGER *ppObj) PURE;
	STDMETHOD(GetCount)(THIS_ LPLONG plCount) PURE;

    //*** SQLOLE standard collection methods
	STDMETHOD(Add)(THIS_ LPSQLOLETRIGGER Object) PURE;
	STDMETHOD(RemoveByOrd)(THIS_ long lOrdinal) PURE;
	STDMETHOD(RemoveByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
	STDMETHOD(Refresh)(THIS_ BOOL bReleaseMemberObjects CPPDEFAULT(= FALSE)) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLERemoteServers
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

    //*** SQLOLE standard enumeration properties
	STDMETHOD(GetItemByOrd)(THIS_ long lOrdinal, LPSQLOLEREMOTESERVER *ppObj) PURE;
	STDMETHOD(GetItemByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLEREMOTESERVER *ppObj) PURE;
    STDMETHOD(GetItemByID)(THIS_ long lID, LPSQLOLEREMOTESERVER *ppObj) PURE;
	STDMETHOD(GetCount)(THIS_ LPLONG plCount) PURE;

    //*** SQLOLE standard collection methods
	STDMETHOD(Add)(THIS_ LPSQLOLEREMOTESERVER Object) PURE;
	STDMETHOD(RemoveByOrd)(THIS_ long lOrdinal) PURE;
	STDMETHOD(RemoveByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
	STDMETHOD(Refresh)(THIS_ BOOL bReleaseMemberObjects CPPDEFAULT(= FALSE)) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLERemoteLogins
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

    //*** SQLOLE standard enumeration properties
	STDMETHOD(GetItemByOrd)(THIS_ long lOrdinal, LPSQLOLEREMOTELOGIN *ppObj) PURE;
	STDMETHOD(GetItemByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLEREMOTELOGIN *ppObj) PURE;
	STDMETHOD(GetCount)(THIS_ LPLONG plCount) PURE;

    //*** SQLOLE standard collection methods
	STDMETHOD(Add)(THIS_ LPSQLOLEREMOTELOGIN Object) PURE;
	STDMETHOD(RemoveByOrd)(THIS_ long lOrdinal) PURE;
	STDMETHOD(RemoveByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
	STDMETHOD(Refresh)(THIS_ BOOL bReleaseMemberObjects CPPDEFAULT(= FALSE)) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLESystemDatatypes
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

    //*** SQLOLE standard enumeration properties
	STDMETHOD(GetItemByOrd)(THIS_ long lOrdinal, LPSQLOLESYSTEMDATATYPE *ppObj) PURE;
	STDMETHOD(GetItemByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLESYSTEMDATATYPE *ppObj) PURE;
	STDMETHOD(GetCount)(THIS_ LPLONG plCount) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLEChecks
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

    //*** SQLOLE standard enumeration properties
	STDMETHOD(GetItemByOrd)(THIS_ long lOrdinal, LPSQLOLECHECK *ppObj) PURE;
	STDMETHOD(GetItemByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLECHECK *ppObj) PURE;
	STDMETHOD(GetCount)(THIS_ LPLONG plCount) PURE;

    //*** SQLOLE standard collection methods
	STDMETHOD(Add)(THIS_ LPSQLOLECHECK Object) PURE;
	STDMETHOD(RemoveByOrd)(THIS_ long lOrdinal) PURE;
	STDMETHOD(RemoveByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
	STDMETHOD(Refresh)(THIS_ BOOL bReleaseMemberObjects CPPDEFAULT(= FALSE)) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLEServerGroups
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

    //*** SQLOLE standard enumeration properties
	STDMETHOD(GetItemByOrd)(THIS_ long lOrdinal, LPSQLOLESERVERGROUP *ppObj) PURE;
	STDMETHOD(GetItemByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLESERVERGROUP *ppObj) PURE;
	STDMETHOD(GetCount)(THIS_ LPLONG plCount) PURE;

    //*** SQLOLE standard collection methods
	STDMETHOD(Add)(THIS_ LPSQLOLESERVERGROUP Object) PURE;
	STDMETHOD(RemoveByOrd)(THIS_ long lOrdinal) PURE;
	STDMETHOD(RemoveByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
	STDMETHOD(Refresh)(THIS_ BOOL bReleaseMemberObjects CPPDEFAULT(= FALSE)) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLERegisteredServers
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

    //*** SQLOLE standard enumeration properties
	STDMETHOD(GetItemByOrd)(THIS_ long lOrdinal, LPSQLOLEREGISTEREDSERVER *ppObj) PURE;
	STDMETHOD(GetItemByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLEREGISTEREDSERVER *ppObj) PURE;
	STDMETHOD(GetCount)(THIS_ LPLONG plCount) PURE;

    //*** SQLOLE standard collection methods
	STDMETHOD(Add)(THIS_ LPSQLOLEREGISTEREDSERVER Object) PURE;
	STDMETHOD(RemoveByOrd)(THIS_ long lOrdinal) PURE;
	STDMETHOD(RemoveByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
	STDMETHOD(Refresh)(THIS_ BOOL bReleaseMemberObjects CPPDEFAULT(= FALSE)) PURE;
};

///////////////////////////
// Noncollection interfaces.
///////////////////////////
#undef INTERFACE
#define INTERFACE ISQLOLEApplication
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

	//*** properties
    STDMETHOD(GetName)(THIS_ SQLOLE_LPBSTR pbstrName) PURE;
    STDMETHOD(GetFullName)(THIS_ SQLOLE_LPBSTR pbstrName) PURE;
    STDMETHOD(GetDBLibraryVersionString)(THIS_ SQLOLE_LPBSTR pbstrVersion) PURE;
    STDMETHOD(GetVersionMajor)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetVersionMinor)(THIS_ LPLONG pRetVal) PURE;

	// Collection properties
    STDMETHOD(GetSQLServers)(THIS_ LPSQLOLESERVERS *pServers) PURE;
    STDMETHOD(GetSQLServerByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLESERVER *ppSQLServer) PURE;
    STDMETHOD(GetSQLServerByOrd)(THIS_ long lOrdinal, LPSQLOLESERVER *ppSQLServer) PURE;
    STDMETHOD(RemoveSQLServerByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
    STDMETHOD(RemoveSQLServerByOrd)(THIS_ long lOrdinal) PURE;
    STDMETHOD(AddSQLServer)(THIS_ LPSQLOLESERVER pSQLServer) PURE;
    STDMETHOD(GetSQLServerCount)(THIS_ LPLONG plCount) PURE;

	//*** methods
    STDMETHOD(Quit)(THIS) PURE;

   // Post-6.0 additions.
    STDMETHOD(GetGroupRegistrationServer)(THIS_ SQLOLE_LPBSTR pbstrVersion) PURE;
    STDMETHOD(SetGroupRegistrationServer)(THIS_ SQLOLE_LPCSTR pbstrVersion) PURE;
    STDMETHOD(GetGroupRegistrationVersion)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetUseCurrentUserServerGroups)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetUseCurrentUserServerGroups)(THIS_ BOOL pRetVal) PURE;
    STDMETHOD(GetVersionBuild)(THIS_ LPLONG pRetVal) PURE;

    STDMETHOD(GetServerGroups)(THIS_ LPSQLOLESERVERGROUPS *ppServerGroups) PURE;
    STDMETHOD(GetServerGroupByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLESERVERGROUP *ppServerGroup) PURE;
    STDMETHOD(GetServerGroupByOrd)(THIS_ long lOrdinal, LPSQLOLESERVERGROUP *ppServerGroup) PURE;
    STDMETHOD(RemoveServerGroupByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
    STDMETHOD(RemoveServerGroupByOrd)(THIS_ long lOrdinal) PURE;
    STDMETHOD(AddServerGroup)(THIS_ LPSQLOLESERVERGROUP pServerGroup) PURE;
    STDMETHOD(GetServerGroupCount)(THIS_ LPLONG plCount) PURE;

    STDMETHOD(ListLocallyConfiguredSQLServers)(THIS_ LPSQLOLENAMELIST *ppServerNames) PURE;
    STDMETHOD(ListAnnouncedNetworkSQLServers)(THIS_ LPSQLOLENAMELIST *ppServerNames) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLEServer
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

	//*** properties
    STDMETHOD(GetApplicationName)(THIS_ SQLOLE_LPBSTR pbstrAppName) PURE;
    STDMETHOD(SetApplicationName)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetConnectionID)(THIS_ LPLONG plConnectionID) PURE;
    STDMETHOD(GetHostName)(THIS_ SQLOLE_LPBSTR pbstrHostName) PURE;
    STDMETHOD(SetHostName)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetLanguage)(THIS_ SQLOLE_LPBSTR pbstrLanguage) PURE;
    STDMETHOD(SetLanguage)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetLogin)(THIS_ SQLOLE_LPBSTR pbstrLogin) PURE;
    STDMETHOD(SetLogin)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetName)(THIS_ SQLOLE_LPBSTR pbstrName) PURE;
    STDMETHOD(SetName)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetNextDeviceNumber)(THIS_ LPLONG plNextDeviceNumber) PURE;
    STDMETHOD(GetQueryTimeout)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetQueryTimeout)(THIS_ long NewValue) PURE;
    STDMETHOD(GetLoginTimeout)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetLoginTimeout)(THIS_ long NewValue) PURE;
    STDMETHOD(GetLoginSecure)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetLoginSecure)(THIS_ BOOL NewValue) PURE;
    STDMETHOD(GetNetPacketSize)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetNetPacketSize)(THIS_ long NewValue) PURE;
    STDMETHOD(GetPassword)(THIS_ SQLOLE_LPBSTR pbstrPassword) PURE;
    STDMETHOD(SetPassword)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetProcessID)(THIS_ LPLONG plProcessID) PURE;
    STDMETHOD(GetStatus)(THIS_ SQLOLE_SVCSTATUS_TYPE *pStatus) PURE;
    STDMETHOD(GetUserProfile)(THIS_ SQLOLE_SRVUSERPROFILE_TYPE *pProfileBits) PURE;
    STDMETHOD(GetMaxNumericPrecision)(THIS_ LPLONG pMaxPrec) PURE;
    STDMETHOD(GetTrueLogin)(THIS_ SQLOLE_LPBSTR pbstrTrueLogin) PURE;
    STDMETHOD(GetTrueName)(THIS_ SQLOLE_LPBSTR pbstrTrueName) PURE;
    STDMETHOD(GetVersionString)(THIS_ SQLOLE_LPBSTR pbstrVersion) PURE;
    STDMETHOD(GetVersionMajor)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetVersionMinor)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetCommandTerminator)(THIS_ SQLOLE_LPBSTR pbstrName) PURE;
    STDMETHOD(SetCommandTerminator)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetProcessInputBuffer)(THIS_ long lProcessID, SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(GetProcessOutputBuffer)(THIS_ long lProcessID, SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(GetDistributionWorkingDirectory)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetDistributionWorkingDirectory)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetDistributionServer)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(GetDistributionDatabase)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(GetAutoReConnect)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetAutoReConnect)(THIS_ BOOL NewValue) PURE;
    STDMETHOD(GetStatusInfoRefetchInterval)(THIS_ SQLOLE_STATUSINFO_TYPE StatusInfoType, LPLONG pRefetchSeconds) PURE;
    STDMETHOD(SetStatusInfoRefetchInterval)(THIS_ SQLOLE_STATUSINFO_TYPE StatusInfoType, long RefetchSeconds) PURE;
    STDMETHOD(GetSaLogin)(THIS_ LPBOOL pRetVal) PURE;

	//*** Object properties
    STDMETHOD(GetConfiguration)(THIS_ LPSQLOLECONFIGURATION *ppConfig) PURE;
    STDMETHOD(GetIntegratedSecurity)(THIS_ LPSQLOLEINTEGRATEDSECURITY *ppIntSec) PURE;
    STDMETHOD(GetRegistry)(THIS_ LPSQLOLEREGISTRY *ppRegistry) PURE;
    STDMETHOD(GetExecutive)(THIS_ LPSQLOLEEXECUTIVE *ppExecutive) PURE;

	//*** collection properties
    STDMETHOD(GetDatabases)(THIS_ LPSQLOLEDATABASES *ppDatabases) PURE;
    STDMETHOD(GetDatabaseByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLEDATABASE *ppDatabase) PURE;
    STDMETHOD(GetDatabaseByOrd)(THIS_ long lOrdinal, LPSQLOLEDATABASE *ppDatabase) PURE;
    STDMETHOD(RemoveDatabaseByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
    STDMETHOD(RemoveDatabaseByOrd)(THIS_ long lOrdinal) PURE;
    STDMETHOD(AddDatabase)(THIS_ LPSQLOLEDATABASE pDatabase) PURE;
    STDMETHOD(GetDatabaseCount)(THIS_ LPLONG plCount) PURE;

    STDMETHOD(GetDevices)(THIS_ LPSQLOLEDEVICES *ppDevices) PURE;
    STDMETHOD(GetDeviceByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLEDEVICE *ppDevice) PURE;
    STDMETHOD(GetDeviceByOrd)(THIS_ long lOrdinal, LPSQLOLEDEVICE *ppDevice) PURE;
    STDMETHOD(RemoveDeviceByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
    STDMETHOD(RemoveDeviceByOrd)(THIS_ long lOrdinal) PURE;
    STDMETHOD(AddDevice)(THIS_ LPSQLOLEDEVICE pDevice) PURE;
    STDMETHOD(GetDeviceCount)(THIS_ LPLONG plCount) PURE;

    STDMETHOD(GetLogins)(THIS_ LPSQLOLELOGINS *ppLogins) PURE;
    STDMETHOD(GetLoginByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLELOGIN *ppLogin) PURE;
    STDMETHOD(GetLoginByOrd)(THIS_ long lOrdinal, LPSQLOLELOGIN *ppLogin) PURE;
    STDMETHOD(RemoveLoginByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
    STDMETHOD(RemoveLoginByOrd)(THIS_ long lOrdinal) PURE;
    STDMETHOD(AddLogin)(THIS_ LPSQLOLELOGIN pLogin) PURE;
    STDMETHOD(GetLoginCount)(THIS_ LPLONG plCount) PURE;

    STDMETHOD(GetLanguages)(THIS_ LPSQLOLELANGUAGES *ppLanguages) PURE;
    STDMETHOD(GetLanguageByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLELANGUAGE *ppLanguage) PURE;
    STDMETHOD(GetLanguageByOrd)(THIS_ long lOrdinal, LPSQLOLELANGUAGE *ppLanguage) PURE;
    STDMETHOD(RemoveLanguageByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
    STDMETHOD(RemoveLanguageByOrd)(THIS_ long lOrdinal) PURE;
    STDMETHOD(AddLanguage)(THIS_ LPSQLOLELANGUAGE pLanguage) PURE;
    STDMETHOD(GetLanguageCount)(THIS_ LPLONG plCount) PURE;

    STDMETHOD(GetRemoteServers)(THIS_ LPSQLOLEREMOTESERVERS *ppRemoteServers) PURE;
    STDMETHOD(GetRemoteServerByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLEREMOTESERVER *ppRemoteServer) PURE;
    STDMETHOD(GetRemoteServerByOrd)(THIS_ long lOrdinal, LPSQLOLEREMOTESERVER *ppRemoteServer) PURE;
    STDMETHOD(RemoveRemoteServerByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
    STDMETHOD(RemoveRemoteServerByOrd)(THIS_ long lOrdinal) PURE;
    STDMETHOD(AddRemoteServer)(THIS_ LPSQLOLEREMOTESERVER pRemoteServer) PURE;
    STDMETHOD(GetRemoteServerCount)(THIS_ LPLONG plCount) PURE;

    STDMETHOD(GetAlerts)(THIS_ LPSQLOLEALERTS *ppAlerts) PURE;
    STDMETHOD(GetAlertByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLEALERT *ppAlert) PURE;
    STDMETHOD(GetAlertByOrd)(THIS_ long lOrdinal, LPSQLOLEALERT *ppAlert) PURE;
    STDMETHOD(RemoveAlertByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
    STDMETHOD(RemoveAlertByOrd)(THIS_ long lOrdinal) PURE;
    STDMETHOD(AddAlert)(THIS_ LPSQLOLEALERT pAlert) PURE;
    STDMETHOD(GetAlertCount)(THIS_ LPLONG plCount) PURE;

    STDMETHOD(GetOperators)(THIS_ LPSQLOLEOPERATORS *ppOperators) PURE;
    STDMETHOD(GetOperatorByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLEOPERATOR *ppOperator) PURE;
    STDMETHOD(GetOperatorByOrd)(THIS_ long lOrdinal, LPSQLOLEOPERATOR *ppOperator) PURE;
    STDMETHOD(RemoveOperatorByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
    STDMETHOD(RemoveOperatorByOrd)(THIS_ long lOrdinal) PURE;
    STDMETHOD(AddOperator)(THIS_ LPSQLOLEOPERATOR pOperator) PURE;
    STDMETHOD(GetOperatorCount)(THIS_ LPLONG plCount) PURE;

	//*** methods
    STDMETHOD(Connect)(THIS_ SQLOLE_LPCSTR szServerName CPPDEFAULT(= NULL), SQLOLE_LPCSTR szLogin CPPDEFAULT(= NULL), SQLOLE_LPCSTR szPassword CPPDEFAULT(= NULL)) PURE;
    STDMETHOD(Close)(THIS) PURE;
    STDMETHOD(DisConnect)(THIS) PURE;
    STDMETHOD(ReConnect)(THIS) PURE;
    STDMETHOD(KillProcess)(THIS_ long lProcessID) PURE;
    STDMETHOD(ExecuteImmediate)(THIS_ SQLOLE_LPCSTR Command, SQLOLE_EXEC_TYPE ExecType CPPDEFAULT(= SQLOLEExec_Default)) PURE;
    STDMETHOD(ExecuteWithResults)(THIS_ SQLOLE_LPCSTR Command, LPSQLOLEQUERYRESULTS *ppResults) PURE;
    STDMETHOD(EnumHistory)(THIS_ LPSQLOLEQUERYRESULTS *ppResults, LPSQLOLEHISTORYFILTER pFilter CPPDEFAULT(= NULL)) PURE;
    STDMETHOD(PurgeHistory)(THIS_ LPSQLOLEHISTORYFILTER pFilter CPPDEFAULT(= NULL)) PURE;
    STDMETHOD(UnloadODSDLL)(THIS_ SQLOLE_LPCSTR DLLName) PURE;
    STDMETHOD(KillDatabase)(THIS_ SQLOLE_LPCSTR DatabaseName) PURE;
    STDMETHOD(ReadErrorLog)(THIS_ LPSQLOLEQUERYRESULTS *ppResults, long lLogNumber CPPDEFAULT(= 0)) PURE;
    STDMETHOD(EnumErrorLogs)(THIS_ LPSQLOLEQUERYRESULTS *ppResults) PURE;
    STDMETHOD(EnumProcesses)(THIS_ LPSQLOLEQUERYRESULTS *ppResults, SQLOLE_LPCSTR szWho CPPDEFAULT(= NULL), long lWho CPPDEFAULT(= -1)) PURE;
    STDMETHOD(EnumLocks)(THIS_ LPSQLOLEQUERYRESULTS *ppResults, long lWho CPPDEFAULT(= -1)) PURE;
    STDMETHOD(ReadBackupHeader)(THIS_ LPSQLOLEBACKUP LoadSpec, LPSQLOLEQUERYRESULTS *ppResults) PURE;
    STDMETHOD(EnumPublicationDatabases)(THIS_ LPSQLOLEQUERYRESULTS *ppResults) PURE;
    STDMETHOD(EnumSubscriptionDatabases)(THIS_ LPSQLOLEQUERYRESULTS *ppResults) PURE;
    STDMETHOD(EnumSubscriberSubscriptions)(THIS_ SQLOLE_LPCSTR Subscriber, LPSQLOLEQUERYRESULTS *ppResults, SQLOLE_LPCSTR SourceDatabase CPPDEFAULT(= NULL)) PURE;
    STDMETHOD(RemoveSubscriberSubscriptions)(THIS_ SQLOLE_LPCSTR Subscriber, SQLOLE_LPCSTR SourceDatabase CPPDEFAULT(= NULL)) PURE;
    STDMETHOD(EnumAvailableMedia)(THIS_ LPSQLOLEQUERYRESULTS *ppResults, SQLOLE_MEDIA_TYPE MediaType CPPDEFAULT(= SQLOLEMedia_All)) PURE;
    STDMETHOD(EnumDirectories)(THIS_ SQLOLE_LPCSTR PathName, LPSQLOLEQUERYRESULTS *ppResults) PURE;
    STDMETHOD(EnumServerAttributes)(THIS_ LPSQLOLEQUERYRESULTS *ppResults) PURE;
    STDMETHOD(EnumVersionInfo)(THIS_ LPSQLOLEQUERYRESULTS *ppResults, SQLOLE_LPCSTR szPrefixes CPPDEFAULT(= NULL)) PURE;
    STDMETHOD(BeginTransaction)(THIS_ SQLOLE_LPCSTR szTransactionName CPPDEFAULT(= NULL)) PURE;
    STDMETHOD(CommitTransaction)(THIS_ SQLOLE_LPCSTR TransactionName CPPDEFAULT(= NULL)) PURE;
    STDMETHOD(SaveTransaction)(THIS_ SQLOLE_LPCSTR SavepointName) PURE;
    STDMETHOD(RollbackTransaction)(THIS_ SQLOLE_LPCSTR TransactionOrSavepointName CPPDEFAULT(= NULL)) PURE;
    STDMETHOD(CommandShellImmediate)(THIS_ SQLOLE_LPCSTR Command) PURE;
    STDMETHOD(CommandShellWithResults)(THIS_ SQLOLE_LPCSTR Command, LPSQLOLEQUERYRESULTS *ppResults) PURE;
    STDMETHOD(Pause)(THIS) PURE;
    STDMETHOD(Continue)(THIS) PURE;
    STDMETHOD(Shutdown)(THIS_ BOOL Wait CPPDEFAULT(= TRUE)) PURE;
    STDMETHOD(Start)(THIS_ SQLOLE_LPCSTR Server CPPDEFAULT(= NULL), SQLOLE_LPCSTR Login CPPDEFAULT(= NULL), SQLOLE_LPCSTR Password CPPDEFAULT(= NULL),
    				 SQLOLE_LPCSTR MasterDBPath CPPDEFAULT(= NULL), SQLOLE_LPCSTR ErrorLogPath CPPDEFAULT(= NULL), SQLOLE_LPCSTR MasterMirrorPath CPPDEFAULT(= NULL),
    				 SQLOLE_STARTSRV_TYPE StartMode CPPDEFAULT(= SQLOLEStart_Defaults)) PURE;
    STDMETHOD(VerifyConnection)(THIS_ LPBOOL pRetVal, SQLOLE_VERIFYCONN_TYPE VerifyType CPPDEFAULT(= SQLOLEConn_ReconnectIfDead)) PURE;

	// List methods
    STDMETHOD(ListStartupProcedures)(THIS_ LPSQLOLESTOREDPROCEDURELIST * ppList) PURE;

	// Post-6.0 additions
    STDMETHOD(ExecuteWithResultsAndMessages)(THIS_ SQLOLE_LPCSTR Command, LPSQLOLEQUERYRESULTS *ppResults, SQLOLE_LPBSTR ppszMessages CPPDEFAULT(= 0)) PURE;
    STDMETHOD(GetNetName)(THIS_ SQLOLE_LPBSTR pbstrNetName) PURE;
    STDMETHOD(EnumLoginMappings)(THIS_ LPSQLOLEQUERYRESULTS *ppResults) PURE;
    STDMETHOD(UninstallPublishing)(THIS) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLERegistry
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

	//*** properties
    STDMETHOD(GetAutostartMail)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetAutostartMail)(THIS_ BOOL NewValue) PURE;
    STDMETHOD(GetAutostartServer)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetAutostartServer)(THIS_ BOOL NewValue) PURE;
    STDMETHOD(GetCaseSensitive)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(GetCharacterSet)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(GetErrorLogPath)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetErrorLogPath)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetMailAccountName)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetMailAccountName)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetMailPassword)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetMailPassword)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetMasterDBPath)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetMasterDBPath)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetNTEventLogging)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(GetNumberOfProcessors)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetPerfMonMode)(THIS_ SQLOLE_PERFMON_TYPE *pRetVal) PURE;
    STDMETHOD(SetPerfMonMode)(THIS_ SQLOLE_PERFMON_TYPE NewValue) PURE;
    STDMETHOD(GetPhysicalMemory)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetAutostartLicensing)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetAutostartLicensing)(THIS_ BOOL NewValue) PURE;
    STDMETHOD(GetRegisteredOrganization)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(GetRegisteredOwner)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(GetSortOrder)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(GetSQLRootPath)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetSQLRootPath)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetTapeLoadWaitTime)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetTapeLoadWaitTime)(THIS_ long NewValue) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLEDatabase
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

	//*** properties
    STDMETHOD(GetName)(THIS_ SQLOLE_LPBSTR pbstrName) PURE;
    STDMETHOD(SetName)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetOwner)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetOwner)(THIS_ SQLOLE_LPCSTR NewValue, BOOL bTransferAliases CPPDEFAULT(= FALSE), BOOL bOverrideIfAlreadyUser CPPDEFAULT(= FALSE)) PURE;
    STDMETHOD(GetVersion)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetCreateDate)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(GetUserName)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetUserName)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetSize)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetSpaceAvailable)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetID)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetSystemObject)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(GetUserProfile)(THIS_ SQLOLE_DBUSERPROFILE_TYPE *pProfileBits) PURE;
    STDMETHOD(GetDataSpaceUsage)(THIS_ LPFLOAT pRetVal) PURE;
    STDMETHOD(GetStatus)(THIS_ SQLOLE_DBSTATUS_TYPE *pRetVal) PURE;
    STDMETHOD(GetIndexSpaceUsage)(THIS_ LPFLOAT pRetVal) PURE;
    STDMETHOD(GetSpaceAvailableInMB)(THIS_ LPFLOAT pRetVal) PURE;
    STDMETHOD(GetSpaceAllocatedOnDevice)(THIS_ SQLOLE_LPCSTR DeviceName, LPLONG pRetVal) PURE;
    STDMETHOD(GetCreateForLoad)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetCreateForLoad)(THIS_ BOOL NewValue) PURE;
    STDMETHOD(ManualSyncPending)(THIS_ SQLOLE_LPCSTR szPubServerName, SQLOLE_LPCSTR szPubDatabaseName, SQLOLE_LPCSTR szPublicationName, SQLOLE_LPCSTR szArticleName, LPBOOL pRetVal) PURE;
    STDMETHOD(GetMinimumSize)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetDboLogin)(THIS_ LPBOOL pRetVal) PURE;

	//*** Object Properties
    STDMETHOD(GetDBOption)(THIS_ LPSQLOLEDBOPTION *ppDBOption) PURE;
    STDMETHOD(GetTransactionLog)(THIS_ LPSQLOLETRANSACTIONLOG * ppTransactionLog) PURE;

	//*** Collection properties
    STDMETHOD(GetTables)(THIS_ LPSQLOLETABLES * ppTables) PURE;
    STDMETHOD(GetTableByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLETABLE *ppTable) PURE;
    STDMETHOD(GetTableByOrd)(THIS_ long lOrdinal, LPSQLOLETABLE *ppTable) PURE;
    STDMETHOD(RemoveTableByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
    STDMETHOD(RemoveTableByOrd)(THIS_ long lOrdinal) PURE;
    STDMETHOD(AddTable)(THIS_ LPSQLOLETABLE pTable) PURE;
    STDMETHOD(GetTableCount)(THIS_ LPLONG plCount) PURE;

    STDMETHOD(GetViews)(THIS_ LPSQLOLEVIEWS * ppViews) PURE;
    STDMETHOD(GetViewByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLEVIEW *ppView) PURE;
    STDMETHOD(GetViewByOrd)(THIS_ long lOrdinal, LPSQLOLEVIEW *ppView) PURE;
    STDMETHOD(RemoveViewByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
    STDMETHOD(RemoveViewByOrd)(THIS_ long lOrdinal) PURE;
    STDMETHOD(AddView)(THIS_ LPSQLOLEVIEW pView) PURE;
    STDMETHOD(GetViewCount)(THIS_ LPLONG plCount) PURE;

    STDMETHOD(GetStoredProcedures)(THIS_ LPSQLOLESTOREDPROCEDURES * ppProcs) PURE;
    STDMETHOD(GetStoredProcedureByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLESTOREDPROCEDURE *ppProc) PURE;
    STDMETHOD(GetStoredProcedureByOrd)(THIS_ long lOrdinal, LPSQLOLESTOREDPROCEDURE *ppProc) PURE;
    STDMETHOD(RemoveStoredProcedureByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
    STDMETHOD(RemoveStoredProcedureByOrd)(THIS_ long lOrdinal) PURE;
    STDMETHOD(AddStoredProcedure)(THIS_ LPSQLOLESTOREDPROCEDURE pProc) PURE;
    STDMETHOD(GetStoredProcedureCount)(THIS_ LPLONG plCount) PURE;

    STDMETHOD(GetDefaults)(THIS_ LPSQLOLEDEFAULTS * ppDefaults) PURE;
    STDMETHOD(GetDefaultByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLEDEFAULT *ppDefault) PURE;
    STDMETHOD(GetDefaultByOrd)(THIS_ long lOrdinal, LPSQLOLEDEFAULT *ppDefault) PURE;
    STDMETHOD(RemoveDefaultByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
    STDMETHOD(RemoveDefaultByOrd)(THIS_ long lOrdinal) PURE;
    STDMETHOD(AddDefault)(THIS_ LPSQLOLEDEFAULT pDefault) PURE;
    STDMETHOD(GetDefaultCount)(THIS_ LPLONG plCount) PURE;

    STDMETHOD(GetRules)(THIS_ LPSQLOLERULES * ppRules) PURE;
    STDMETHOD(GetRuleByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLERULE *ppRule) PURE;
    STDMETHOD(GetRuleByOrd)(THIS_ long lOrdinal, LPSQLOLERULE *ppRule) PURE;
    STDMETHOD(RemoveRuleByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
    STDMETHOD(RemoveRuleByOrd)(THIS_ long lOrdinal) PURE;
    STDMETHOD(AddRule)(THIS_ LPSQLOLERULE pRule) PURE;
    STDMETHOD(GetRuleCount)(THIS_ LPLONG plCount) PURE;

    STDMETHOD(GetUserDefinedDatatypes)(THIS_ LPSQLOLEUSERDEFINEDDATATYPES * ppUDDTs) PURE;
    STDMETHOD(GetUserDefinedDatatypeByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLEUSERDEFINEDDATATYPE *ppUDDT) PURE;
    STDMETHOD(GetUserDefinedDatatypeByOrd)(THIS_ long lOrdinal, LPSQLOLEUSERDEFINEDDATATYPE *ppUDDT) PURE;
    STDMETHOD(RemoveUserDefinedDatatypeByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
    STDMETHOD(RemoveUserDefinedDatatypeByOrd)(THIS_ long lOrdinal) PURE;
    STDMETHOD(AddUserDefinedDatatype)(THIS_ LPSQLOLEUSERDEFINEDDATATYPE pUDDT) PURE;
    STDMETHOD(GetUserDefinedDatatypeCount)(THIS_ LPLONG plCount) PURE;

    STDMETHOD(GetUsers)(THIS_ LPSQLOLEUSERS * ppUsers) PURE;
    STDMETHOD(GetUserByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLEUSER *ppUser) PURE;
    STDMETHOD(GetUserByOrd)(THIS_ long lOrdinal, LPSQLOLEUSER *ppUser) PURE;
    STDMETHOD(RemoveUserByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
    STDMETHOD(RemoveUserByOrd)(THIS_ long lOrdinal) PURE;
    STDMETHOD(AddUser)(THIS_ LPSQLOLEUSER pUser) PURE;
    STDMETHOD(GetUserCount)(THIS_ LPLONG plCount) PURE;

    STDMETHOD(GetGroups)(THIS_ LPSQLOLEGROUPS * ppGroups) PURE;
    STDMETHOD(GetGroupByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLEGROUP *ppGroup) PURE;
    STDMETHOD(GetGroupByOrd)(THIS_ long lOrdinal, LPSQLOLEGROUP *ppGroup) PURE;
    STDMETHOD(RemoveGroupByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
    STDMETHOD(RemoveGroupByOrd)(THIS_ long lOrdinal) PURE;
    STDMETHOD(AddGroup)(THIS_ LPSQLOLEGROUP pGroup) PURE;
    STDMETHOD(GetGroupCount)(THIS_ LPLONG plCount) PURE;

    STDMETHOD(GetPublications)(THIS_ LPSQLOLEPUBLICATIONS * ppPublications) PURE;
    STDMETHOD(GetPublicationByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLEPUBLICATION *ppPublication) PURE;
    STDMETHOD(GetPublicationByOrd)(THIS_ long lOrdinal, LPSQLOLEPUBLICATION *ppPublication) PURE;
    STDMETHOD(RemovePublicationByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
    STDMETHOD(RemovePublicationByOrd)(THIS_ long lOrdinal) PURE;
    STDMETHOD(AddPublication)(THIS_ LPSQLOLEPUBLICATION pPublication) PURE;
    STDMETHOD(GetPublicationCount)(THIS_ LPLONG plCount) PURE;

    STDMETHOD(GetSystemDatatypes)(THIS_ LPSQLOLESYSTEMDATATYPES * ppSDTs) PURE;
    STDMETHOD(GetSystemDatatypeByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLESYSTEMDATATYPE *ppSDT) PURE;
    STDMETHOD(GetSystemDatatypeByOrd)(THIS_ long lOrdinal, LPSQLOLESYSTEMDATATYPE *ppSDT) PURE;
    STDMETHOD(GetSystemDatatypeCount)(THIS_ LPLONG plCount) PURE;

	//*** Methods
    STDMETHOD(Grant)(THIS_ SQLOLE_PRIVILEGE_TYPE iPrivileges, SQLOLE_LPCSTR GranteeNames) PURE;
    STDMETHOD(Revoke)(THIS_ SQLOLE_PRIVILEGE_TYPE iPrivileges, SQLOLE_LPCSTR RevokeeNames) PURE;
    STDMETHOD(ExecuteImmediate)(THIS_ SQLOLE_LPCSTR Command, SQLOLE_EXEC_TYPE ExecType CPPDEFAULT(= SQLOLEExec_Default)) PURE;
    STDMETHOD(ExecuteWithResults)(THIS_ SQLOLE_LPCSTR Command, LPSQLOLEQUERYRESULTS *ppResults) PURE;
    STDMETHOD(Checkpoint)(THIS) PURE;
    STDMETHOD(CheckTables)(THIS_ SQLOLE_LPBSTR pResult) PURE;
    STDMETHOD(CheckAllocations)(THIS_ SQLOLE_LPBSTR pResult) PURE;
    STDMETHOD(CheckCatalog)(THIS_ SQLOLE_LPBSTR pResult) PURE;
    STDMETHOD(CheckTextAllocsFast)(THIS_ SQLOLE_LPBSTR pResult) PURE;
    STDMETHOD(CheckTextAllocsFull)(THIS_ SQLOLE_LPBSTR pResult) PURE;
    STDMETHOD(GetMemoryUsage)(THIS_ SQLOLE_LPBSTR pResult) PURE;
    STDMETHOD(EnumLocks)(THIS_ LPSQLOLEQUERYRESULTS *ppResults, long lWho CPPDEFAULT(= -1)) PURE;
    STDMETHOD(Remove)(THIS) PURE;
    STDMETHOD(ExtendOnDevices)(THIS_ SQLOLE_LPCSTR DeviceNames) PURE;
    STDMETHOD(Dump)(THIS_ LPSQLOLEBACKUP DumpSpec) PURE;
    STDMETHOD(Load)(THIS_ LPSQLOLEBACKUP LoadSpec) PURE;
    STDMETHOD(GenerateBackupSQL)(THIS_ LPSQLOLEBACKUP DumpSpec, SQLOLE_LPBSTR pSQLStatement) PURE;
    STDMETHOD(GetObjectByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLEDBOBJECT *ppDBObject, SQLOLE_OBJECT_TYPE lType CPPDEFAULT(= SQLOLEObj_AllDatabaseObjects)) PURE;
    STDMETHOD(GetDatatypeByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLESTDOBJECT *ppDBObject) PURE;
    STDMETHOD(ManualSyncCompleted)(THIS_ SQLOLE_LPCSTR szPubServerName, SQLOLE_LPCSTR szPubDatabaseName, SQLOLE_LPCSTR szPublicationName, SQLOLE_LPCSTR szArticleName CPPDEFAULT(= NULL)) PURE;
    STDMETHOD(EnumCandidateKeys)(THIS_ LPSQLOLEQUERYRESULTS * ppResults) PURE;
    STDMETHOD(IsValidKeyDatatype)(THIS_ SQLOLE_LPCSTR szKeyColType, LPBOOL pRetVal, SQLOLE_LPCSTR szReferencingColType CPPDEFAULT(= NULL)) PURE;
    STDMETHOD(Shrink)(THIS_ long lNewSizeInMB) PURE;
    STDMETHOD(RecalcSpaceUsage)(THIS) PURE;
    STDMETHOD(EnumDependencies)(THIS_ LPSQLOLEQUERYRESULTS *ppResults, SQLOLE_DEPENDENCY_TYPE DependencyType CPPDEFAULT(= SQLOLEDep_Parents)) PURE;

	//*** List methods
    STDMETHOD(ListObjectPermissions)(THIS_ LPSQLOLEPERMISSIONLIST * ppList, SQLOLE_PRIVILEGE_TYPE lPrivilegeTypes CPPDEFAULT(= SQLOLEPriv_AllObjectPrivs)) PURE;
    STDMETHOD(ListDatabasePermissions)(THIS_ LPSQLOLEPERMISSIONLIST * ppList, SQLOLE_PRIVILEGE_TYPE lPrivilegeTypes CPPDEFAULT(= SQLOLEPriv_AllDatabasePrivs)) PURE;
    STDMETHOD(ListDevices)(THIS_ LPSQLOLEDEVICELIST * ppList) PURE;
    STDMETHOD(ListObjects)(THIS_ LPSQLOLEDBOBJECTLIST * ppList, SQLOLE_OBJECT_TYPE lObjectTypes CPPDEFAULT(= SQLOLEObj_AllDatabaseObjects), SQLOLE_OBJSORT_TYPE SortBy CPPDEFAULT(= SQLOLEObjSort_Name)) PURE;

	// Post-6.0 additions
    STDMETHOD(Transfer)(THIS_ LPSQLOLETRANSFER TransferSpec) PURE;
    STDMETHOD(ScriptTransfer)(THIS_ LPSQLOLETRANSFER TransferSpec, SQLOLE_XFRSCRIPTMODE_TYPE ScriptFileMode CPPDEFAULT(= SQLOLEXfrFile_Default), SQLOLE_LPCSTR ScriptFilePath CPPDEFAULT(= NULL), SQLOLE_LPBSTR ScriptText CPPDEFAULT(= NULL)) PURE;
	STDMETHOD(CheckIdentityValues)(THIS) PURE;
    STDMETHOD(ExecuteWithResultsAndMessages)(THIS_ SQLOLE_LPCSTR Command, LPSQLOLEQUERYRESULTS *ppResults, SQLOLE_LPBSTR ppszMessages CPPDEFAULT(= 0)) PURE;
    STDMETHOD(Script)(THIS_ SQLOLE_SCRIPT_TYPE ScriptType CPPDEFAULT(= SQLOLEScript_Default), SQLOLE_LPCSTR ScriptFilePath CPPDEFAULT(= NULL), SQLOLE_LPBSTR ScriptText CPPDEFAULT(= NULL)) PURE;
    STDMETHOD(CheckTablesDataOnly)(THIS_ SQLOLE_LPBSTR pResult) PURE;
    STDMETHOD(CheckAllocationsDataOnly)(THIS_ SQLOLE_LPBSTR pResult) PURE;
	STDMETHOD(UpdateIndexStatistics)(THIS) PURE;
    STDMETHOD(EnumLoginMappings)(THIS_ LPSQLOLEQUERYRESULTS *ppResults) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLEDevice
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

	//*** properties
    STDMETHOD(GetName)(THIS_ SQLOLE_LPBSTR pbstrName) PURE;
    STDMETHOD(SetName)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetPhysicalLocation)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetPhysicalLocation)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetType)(THIS_ SQLOLE_DEVICE_TYPE *pRetVal) PURE;
    STDMETHOD(SetType)(THIS_ SQLOLE_DEVICE_TYPE NewValue) PURE;
    STDMETHOD(GetStatus)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetFirstPage)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetLastPage)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetSize)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetSize)(THIS_ long NewValue) PURE;
    STDMETHOD(GetSpaceAvailable)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetDeviceNumber)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetMirrorState)(THIS_ SQLOLE_MIRROR_TYPE *pRetVal) PURE;
    STDMETHOD(GetMirrorName)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(GetDefault)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetDefault)(THIS_ BOOL NewValue) PURE;
    STDMETHOD(GetSkipTapeLabel)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetSkipTapeLabel)(THIS_ BOOL NewValue) PURE;
    STDMETHOD(GetSystemObject)(THIS_ LPBOOL pRetVal) PURE;

	//*** methods
    STDMETHOD(Mirror)(THIS_ SQLOLE_LPCSTR MirrorPathName) PURE;
    STDMETHOD(ReMirror)(THIS) PURE;
    STDMETHOD(SwitchToMirrorDevice)(THIS) PURE;
    STDMETHOD(SwitchToMirrorTemp)(THIS) PURE;
    STDMETHOD(UnMirrorDevice)(THIS) PURE;
    STDMETHOD(UnMirrorTemp)(THIS) PURE;
    STDMETHOD(Remove)(THIS) PURE;
    STDMETHOD(ReadBackupHeader)(THIS_ LPSQLOLEQUERYRESULTS *ppResults) PURE;

	// List methods
    STDMETHOD(ListDatabases)(THIS_ LPSQLOLEDATABASELIST * ppList) PURE;

	// Post-6.0 Additions
    STDMETHOD(Script)(THIS_ SQLOLE_SCRIPT_TYPE ScriptType CPPDEFAULT(= SQLOLEScript_Default), SQLOLE_LPCSTR ScriptFilePath CPPDEFAULT(= NULL), SQLOLE_LPCSTR NewPhysicalLocation CPPDEFAULT(= NULL), SQLOLE_LPBSTR ScriptText CPPDEFAULT(= NULL)) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLELogin
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

	//*** properties
    STDMETHOD(GetName)(THIS_ SQLOLE_LPBSTR pbstrName) PURE;
    STDMETHOD(SetName)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetID)(THIS_ LPLONG plID) PURE;
    STDMETHOD(GetSystemObject)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(GetLanguage)(THIS_ SQLOLE_LPBSTR pbstrLanguage) PURE;
    STDMETHOD(SetLanguage)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetDatabase)(THIS_ SQLOLE_LPBSTR pbstrDatabase) PURE;
    STDMETHOD(SetDatabase)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetUserName)(THIS_ SQLOLE_LPCSTR DatabaseName, SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(GetAliasName)(THIS_ SQLOLE_LPCSTR DatabaseName, SQLOLE_LPBSTR pRetVal) PURE;

   //*** methods
    STDMETHOD(ListTasks)(THIS_ LPSQLOLETASKLIST * ppList) PURE;
    STDMETHOD(Remove)(THIS) PURE;
    STDMETHOD(Script)(THIS_ SQLOLE_SCRIPT_TYPE ScriptType CPPDEFAULT(= SQLOLEScript_Default), SQLOLE_LPCSTR ScriptFilePath CPPDEFAULT(= NULL), SQLOLE_LPBSTR ScriptText CPPDEFAULT(= NULL)) PURE;
    STDMETHOD(SetPassword)(THIS_ SQLOLE_LPCSTR OldValue, SQLOLE_LPCSTR NewValue) PURE;

	// Post-6.0 additions
    STDMETHOD(EnumDatabaseMappings)(THIS_ LPSQLOLEQUERYRESULTS *ppResults) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLELanguage
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

	//*** properties
    STDMETHOD(GetName)(THIS_ SQLOLE_LPBSTR pbstrName) PURE;
    STDMETHOD(SetName)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetID)(THIS_ LPLONG plID) PURE;
    STDMETHOD(GetUpgrade)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetAlias)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetAlias)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetMonths)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetMonths)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetShortMonths)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetShortMonths)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetDays)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetDays)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetDateFormat)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetDateFormat)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetFirstDayOfWeek)(THIS_ LPINT pRetVal) PURE;
    STDMETHOD(SetFirstDayOfWeek)(THIS_ int NewValue) PURE;
    STDMETHOD(GetMonth)(THIS_ int iMonth, SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(GetShortMonth)(THIS_ int iMonth, SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(GetDay)(THIS_ int iDay, SQLOLE_LPBSTR pRetVal) PURE;

   //*** methods
    STDMETHOD(Remove)(THIS) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLEConfiguration
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

	//*** properties
    STDMETHOD(GetShowAdvancedOptions)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetShowAdvancedOptions)(THIS_ BOOL NewValue) PURE;
	
	//*** collection properties
    STDMETHOD(GetConfigValues)(THIS_ LPSQLOLECONFIGVALUES * ppRemoteLogins) PURE;
    STDMETHOD(GetConfigValueByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLECONFIGVALUE *ppRemoteLogin) PURE;
    STDMETHOD(GetConfigValueByOrd)(THIS_ long lOrdinal, LPSQLOLECONFIGVALUE *ppRemoteLogin) PURE;
    STDMETHOD(GetConfigValueCount)(THIS_ LPLONG plCount) PURE;

    STDMETHOD(GetParameters)(THIS_ LPSQLOLENAMES *ppParameters) PURE;

	//*** methods
    STDMETHOD(ReconfigureCurrentValues)(THIS) PURE;
    STDMETHOD(ReconfigureWithOverride)(THIS) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLEConfigValues
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

    //*** SQLOLE standard enumeration properties
	STDMETHOD(GetItemByOrd)(THIS_ long lOrdinal, LPSQLOLECONFIGVALUE *ppObj) PURE;
	STDMETHOD(GetItemByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLECONFIGVALUE *ppObj) PURE;
    STDMETHOD(GetItemByID)(THIS_ long lID, LPSQLOLECONFIGVALUE *ppObj) PURE;
	STDMETHOD(GetCount)(THIS_ LPLONG plCount) PURE;
    STDMETHOD(Refresh)(THIS) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLEConfigValue
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

	//*** properties
    STDMETHOD(GetName)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(GetMinimumValue)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetMaximumValue)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetDynamicReconfigure)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(GetCurrentValue)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetCurrentValue)(THIS_ long NewValue) PURE;
    STDMETHOD(GetRunningValue)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetDescription)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(GetID)(THIS_ SQLOLE_CONFIGVALUE_TYPE *pRetVal) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLEIntegratedSecurity
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

	//*** properties
    STDMETHOD(GetMapUnderscore)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetMapUnderscore)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetMapDollarSign)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetMapDollarSign)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetMapPoundSign)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetMapPoundSign)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetSecurityMode)(THIS_ SQLOLE_SECURITY_TYPE * pRetVal) PURE;
    STDMETHOD(SetSecurityMode)(THIS_ SQLOLE_SECURITY_TYPE NewValue) PURE;
    STDMETHOD(GetDefaultLogin)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetDefaultLogin)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetDefaultDomain)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetDefaultDomain)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetAuditLevel)(THIS_ SQLOLE_AUDIT_TYPE * pRetVal) PURE;
    STDMETHOD(SetAuditLevel)(THIS_ SQLOLE_AUDIT_TYPE NewValue) PURE;
    STDMETHOD(GetSetHostName)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetSetHostName)(THIS_ BOOL NewValue) PURE;
    STDMETHOD(GetImpersonateClient)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetImpersonateClient)(THIS_ BOOL NewValue) PURE;

   //*** methods
    STDMETHOD(Refresh)(THIS) PURE;
    STDMETHOD(GrantNTLogin)(THIS_ SQLOLE_LPCSTR Account, SQLOLE_INTSECLOGIN_TYPE LoginType CPPDEFAULT(= SQLOLEIntSecLogin_User)) PURE;
    STDMETHOD(RevokeNTLogin)(THIS_ SQLOLE_LPCSTR Account) PURE;
    STDMETHOD(EnumAccountInfo)(THIS_ LPSQLOLEQUERYRESULTS *ppResults, SQLOLE_LPCSTR Account CPPDEFAULT(= NULL), BOOL ListAll CPPDEFAULT(= FALSE)) PURE;
    STDMETHOD(EnumNTDomainGroups)(THIS_ LPSQLOLEQUERYRESULTS *ppResults, SQLOLE_LPCSTR Domain CPPDEFAULT(= NULL)) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLERemoteServer
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

	//*** properties
    STDMETHOD(GetName)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetName)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetID)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetNetName)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetNetName)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetOptions)(THIS_ SQLOLE_SRVOPTION_TYPE *pRetVal) PURE;
    STDMETHOD(GetTopologyX)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetTopologyY)(THIS_ LPLONG pRetVal) PURE;

	//*** object properties
    STDMETHOD(GetSubscriberInfo)(THIS_ LPSQLOLESUBSCRIBERINFO * ppSubscriberInfo) PURE;

	//*** collection properties
    STDMETHOD(GetRemoteLogins)(THIS_ LPSQLOLEREMOTELOGINS * ppRemoteLogins) PURE;
    STDMETHOD(GetRemoteLoginByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLEREMOTELOGIN *ppRemoteLogin) PURE;
    STDMETHOD(GetRemoteLoginByOrd)(THIS_ long lOrdinal, LPSQLOLEREMOTELOGIN *ppRemoteLogin) PURE;
    STDMETHOD(RemoveRemoteLoginByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
    STDMETHOD(RemoveRemoteLoginByOrd)(THIS_ long lOrdinal) PURE;
    STDMETHOD(AddRemoteLogin)(THIS_ LPSQLOLEREMOTELOGIN pRemoteLogin) PURE;
    STDMETHOD(GetRemoteLoginCount)(THIS_ LPLONG plCount) PURE;

	//*** methods
    STDMETHOD(Remove)(THIS) PURE;
    STDMETHOD(EnumPublicationDatabases)(THIS_ LPSQLOLEQUERYRESULTS *ppResults) PURE;
    STDMETHOD(EnumSubscriptionDatabases)(THIS_ LPSQLOLEQUERYRESULTS *ppResults) PURE;
    STDMETHOD(EnumPublications)(THIS_ SQLOLE_LPCSTR DatabaseName, LPSQLOLEQUERYRESULTS *ppResults) PURE;
    STDMETHOD(EnumArticles)(THIS_ SQLOLE_LPCSTR DatabaseName, SQLOLE_LPCSTR PublicationName, LPSQLOLEQUERYRESULTS *ppResults) PURE;
    STDMETHOD(EnumSubscriptions)(THIS_ SQLOLE_LPCSTR DatabaseName, SQLOLE_LPCSTR PublicationName, SQLOLE_LPCSTR ArticleName, LPSQLOLEQUERYRESULTS *ppResults) PURE;
    STDMETHOD(ExecuteImmediate)(THIS_ SQLOLE_LPCSTR Command) PURE;
    STDMETHOD(ExecuteWithResults)(THIS_ SQLOLE_LPCSTR Command, LPSQLOLEQUERYRESULTS *ppResults) PURE;
    STDMETHOD(Subscribe)(THIS_ SQLOLE_LPCSTR DatabaseName, SQLOLE_LPCSTR PublicationName, SQLOLE_LPCSTR ArticleName CPPDEFAULT(= NULL), 
    		SQLOLE_LPCSTR SubscribingDB CPPDEFAULT(= NULL), SQLOLE_SUBSYNC_TYPE SyncType CPPDEFAULT(= SQLOLESubSync_Auto)) PURE;
    STDMETHOD(UnSubscribe)(THIS_ SQLOLE_LPCSTR DatabaseName, SQLOLE_LPCSTR PublicationName CPPDEFAULT(= NULL), SQLOLE_LPCSTR ArticleName CPPDEFAULT(= NULL)) PURE;
    STDMETHOD(SetOptions)(THIS_ SQLOLE_SRVOPTION_TYPE Options, BOOL NewValue) PURE;
    STDMETHOD(EnumTasks)(THIS_ LPSQLOLEQUERYRESULTS *ppResults, SQLOLE_LPCSTR TaskName CPPDEFAULT(= NULL), long TaskID CPPDEFAULT(= 0)) PURE;
    STDMETHOD(SetTopologyXY)(THIS_ long X, long Y) PURE;
    STDMETHOD(EnumPublicationSyncTask)(THIS_ SQLOLE_LPCSTR DatabaseName, SQLOLE_LPCSTR PublicationName, LPSQLOLEQUERYRESULTS *ppResults) PURE;

	// Post-6.0 additions
    STDMETHOD(ExecuteWithResultsAndMessages)(THIS_ SQLOLE_LPCSTR Command, LPSQLOLEQUERYRESULTS *ppResults, SQLOLE_LPBSTR ppszMessages CPPDEFAULT(= 0)) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLERemoteLogin
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

	//*** properties
    STDMETHOD(GetLocalName)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetLocalName)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetRemoteName)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetRemoteName)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetTrusted)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetTrusted)(THIS_ BOOL NewValue) PURE;

	//*** methods
    STDMETHOD(Remove)(THIS) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLEQueryResults
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

	//*** properties
    STDMETHOD(GetResultSets)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetCurrentResultSet)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetCurrentResultSet)(THIS_ long NewValue) PURE;
    STDMETHOD(GetRows)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetColumns)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetColumnName)(THIS_ long lColumn, SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(GetColumnType)(THIS_ long lColumn, SQLOLE_QUERY_DATATYPE *pRetVal) PURE;
    STDMETHOD(GetColumnMaxLength)(THIS_ long lColumn, LPLONG pRetVal) PURE;

	//*** methods
    STDMETHOD(GetColumnLong)(THIS_ long lRow, long lColumn, LPLONG pRetVal) PURE;
    STDMETHOD(GetColumnBool)(THIS_ long lRow, long lColumn, LPBOOL pRetVal) PURE;
    STDMETHOD(GetColumnFloat)(THIS_ long lRow, long lColumn, LPFLOAT pRetVal) PURE;
    STDMETHOD(GetColumnDouble)(THIS_ long lRow, long lColumn, LPDOUBLE pRetVal) PURE;
    STDMETHOD(GetColumnString)(THIS_ long lRow, long lColumn, SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(GetRangeString)(THIS_ SQLOLE_LPBSTR pRetVal, long Top CPPDEFAULT(= 0), long Left CPPDEFAULT(= 1),
    								long Bottom CPPDEFAULT(= -1), long Right CPPDEFAULT(= -1),
    								SQLOLE_LPCSTR RowDelim CPPDEFAULT(= NULL), SQLOLE_LPCSTR ColDelim CPPDEFAULT(= NULL),
    								SQLOLE_LPCSTR ColWidths CPPDEFAULT(= NULL)) PURE;
    STDMETHOD(Refresh)(THIS) PURE;

	// Post-6.0 additions
    STDMETHOD(GetColumnDate)(THIS_ long lRow, long lColumn, LPSYSTEMTIME pSystemTime) PURE;
    STDMETHOD(GetColumnBinary)(THIS_ long lRow, long lColumn, LPVOID *pvData) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLETransactionLog
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

	//*** properties
    STDMETHOD(GetCreateDate)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(GetLastDump)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(GetSize)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetSpaceAvailable)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetSpaceAvailableInMB)(THIS_ LPFLOAT pRetVal) PURE;
    STDMETHOD(GetSpaceAllocatedOnDevice)(THIS_ SQLOLE_LPCSTR DeviceName, LPLONG pRetVal) PURE;
    STDMETHOD(IsLogOnSeparateDevice)(THIS_ LPBOOL pRetVal) PURE;

	//*** methods
    STDMETHOD(DedicateLogDevices)(THIS_ SQLOLE_LPCSTR DeviceNames) PURE;
    STDMETHOD(UndedicateLogDevices)(THIS_ SQLOLE_LPCSTR DeviceNames) PURE;
    STDMETHOD(Dump)(THIS_ LPSQLOLEBACKUP DumpSpec) PURE;
    STDMETHOD(Load)(THIS_ LPSQLOLEBACKUP LoadSpec) PURE;
    STDMETHOD(GenerateBackupSQL)(THIS_ LPSQLOLEBACKUP DumpSpec, SQLOLE_LPBSTR pSQLStatement) PURE;
    STDMETHOD(Truncate)(THIS) PURE;

	// List methods.
    STDMETHOD(ListDevices)(THIS_ LPSQLOLEDEVICELIST * ppList) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLETable
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

	//*** properties
    STDMETHOD(GetName)(THIS_ SQLOLE_LPBSTR pbstrName) PURE;
    STDMETHOD(SetName)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetID)(THIS_ LPLONG plID) PURE;
    STDMETHOD(GetOwner)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(GetCreateDate)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(GetSystemObject)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(GetRows)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetDataSpaceUsed)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetIndexSpaceUsed)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetAttributes)(THIS_ SQLOLE_TABLEATT_TYPE *pRetVal) PURE;
    STDMETHOD(GetPrimaryKey)(THIS_ LPSQLOLEKEY *ppPrimaryKey) PURE;
    STDMETHOD(GetClusteredIndex)(THIS_ LPSQLOLEINDEX *ppPrimaryKey) PURE;

	// Collection properties
    STDMETHOD(GetColumns)(THIS_ LPSQLOLECOLUMNS *ppColumns) PURE;
    STDMETHOD(GetColumnByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLECOLUMN *ppColumn) PURE;
    STDMETHOD(GetColumnByOrd)(THIS_ long lOrdinal, LPSQLOLECOLUMN *ppColumn) PURE;
    STDMETHOD(RemoveColumnByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
    STDMETHOD(RemoveColumnByOrd)(THIS_ long lOrdinal) PURE;
    STDMETHOD(AddColumn)(THIS_ LPSQLOLECOLUMN pColumn) PURE;
    STDMETHOD(GetColumnCount)(THIS_ LPLONG plCount) PURE;

    STDMETHOD(GetKeys)(THIS_ LPSQLOLEKEYS *ppKeys) PURE;
    STDMETHOD(GetKeyByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLEKEY *ppKey) PURE;
    STDMETHOD(GetKeyByOrd)(THIS_ long lOrdinal, LPSQLOLEKEY *ppKey) PURE;
    STDMETHOD(RemoveKeyByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
    STDMETHOD(RemoveKeyByOrd)(THIS_ long lOrdinal) PURE;
    STDMETHOD(AddKey)(THIS_ LPSQLOLEKEY pKey) PURE;
    STDMETHOD(GetKeyCount)(THIS_ LPLONG plCount) PURE;

    STDMETHOD(GetChecks)(THIS_ LPSQLOLECHECKS *ppChecks) PURE;
    STDMETHOD(GetCheckByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLECHECK *ppCheck) PURE;
    STDMETHOD(GetCheckByOrd)(THIS_ long lOrdinal, LPSQLOLECHECK *ppCheck) PURE;
    STDMETHOD(RemoveCheckByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
    STDMETHOD(RemoveCheckByOrd)(THIS_ long lOrdinal) PURE;
    STDMETHOD(AddCheck)(THIS_ LPSQLOLECHECK pCheck) PURE;
    STDMETHOD(GetCheckCount)(THIS_ LPLONG plCount) PURE;

    STDMETHOD(GetIndexes)(THIS_ LPSQLOLEINDEXES *ppIndexes) PURE;
    STDMETHOD(GetIndexByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLEINDEX *ppIndex) PURE;
    STDMETHOD(GetIndexByOrd)(THIS_ long lOrdinal, LPSQLOLEINDEX *ppIndex) PURE;
    STDMETHOD(RemoveIndexByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
    STDMETHOD(RemoveIndexByOrd)(THIS_ long lOrdinal) PURE;
    STDMETHOD(AddIndex)(THIS_ LPSQLOLEINDEX pIndex) PURE;
    STDMETHOD(GetIndexCount)(THIS_ LPLONG plCount) PURE;

    STDMETHOD(GetTriggers)(THIS_ LPSQLOLETRIGGERS *ppTriggers) PURE;
    STDMETHOD(GetTriggerByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLETRIGGER *ppTrigger) PURE;
    STDMETHOD(GetTriggerByOrd)(THIS_ long lOrdinal, LPSQLOLETRIGGER *ppTrigger) PURE;
    STDMETHOD(RemoveTriggerByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
    STDMETHOD(RemoveTriggerByOrd)(THIS_ long lOrdinal) PURE;
    STDMETHOD(AddTrigger)(THIS_ LPSQLOLETRIGGER pTrigger) PURE;
    STDMETHOD(GetTriggerCount)(THIS_ LPLONG plCount) PURE;

	//*** methods
    STDMETHOD(BeginAlter)(THIS) PURE;
    STDMETHOD(DoAlter)(THIS) PURE;
    STDMETHOD(DoAlterWithNoCheck)(THIS) PURE;
    STDMETHOD(CancelAlter)(THIS) PURE;
    STDMETHOD(Grant)(THIS_ SQLOLE_PRIVILEGE_TYPE iPrivileges, SQLOLE_LPCSTR GranteeNames, SQLOLE_LPCSTR ColumnNames CPPDEFAULT(= NULL)) PURE;
    STDMETHOD(Revoke)(THIS_ SQLOLE_PRIVILEGE_TYPE iPrivileges, SQLOLE_LPCSTR RevokeeNames, SQLOLE_LPCSTR ColumnNames CPPDEFAULT(= NULL)) PURE;
    STDMETHOD(CheckTable)(THIS_ SQLOLE_LPBSTR pResult) PURE;
    STDMETHOD(CheckTextAllocsFast)(THIS_ SQLOLE_LPBSTR pResult) PURE;
    STDMETHOD(CheckTextAllocsFull)(THIS_ SQLOLE_LPBSTR pResult) PURE;
    STDMETHOD(TruncateData)(THIS) PURE;
    STDMETHOD(UpdateStatistics)(THIS) PURE;
    STDMETHOD(ReCompileReferences)(THIS) PURE;
    STDMETHOD(Remove)(THIS) PURE;
    STDMETHOD(Refresh)(THIS) PURE;
    STDMETHOD(Script)(THIS_ SQLOLE_SCRIPT_TYPE ScriptType CPPDEFAULT(= SQLOLEScript_Default), SQLOLE_LPCSTR ScriptFilePath CPPDEFAULT(= NULL), SQLOLE_LPCSTR NewName CPPDEFAULT(= NULL), SQLOLE_LPBSTR ScriptText CPPDEFAULT(= NULL)) PURE;
    STDMETHOD(EnumReferencedKeys)(THIS_ LPSQLOLEQUERYRESULTS * ppResults, SQLOLE_LPCSTR ReferencedTableName CPPDEFAULT(= NULL), BOOL IncludeAllCandidates CPPDEFAULT(= NULL)) PURE;
    STDMETHOD(EnumReferencedTables)(THIS_ LPSQLOLEQUERYRESULTS * ppResults, BOOL IncludeAllCandidates CPPDEFAULT(= NULL)) PURE;
    STDMETHOD(EnumReferencingKeys)(THIS_ LPSQLOLEQUERYRESULTS * ppResults, SQLOLE_LPCSTR ReferencingTableName CPPDEFAULT(= NULL), BOOL IncludeAllCandidates CPPDEFAULT(= NULL)) PURE;
    STDMETHOD(EnumReferencingTables)(THIS_ LPSQLOLEQUERYRESULTS * ppResults, BOOL IncludeAllCandidates CPPDEFAULT(= NULL)) PURE;
    STDMETHOD(InsertColumn)(THIS_ LPSQLOLECOLUMN pNewColumn, SQLOLE_LPCSTR BeforeColumnName) PURE;
    STDMETHOD(RecalcSpaceUsage)(THIS) PURE;
    STDMETHOD(EnumDependencies)(THIS_ LPSQLOLEQUERYRESULTS *ppResults, SQLOLE_DEPENDENCY_TYPE DependencyType CPPDEFAULT(= SQLOLEDep_Parents)) PURE;
    STDMETHOD(EnumLastStatisticsUpdates)(THIS_ LPSQLOLEQUERYRESULTS * ppResults, SQLOLE_LPCSTR IndexName CPPDEFAULT(= NULL)) PURE;

	// List methods
    STDMETHOD(ListPermissions)(THIS_ LPSQLOLEPERMISSIONLIST * ppList, SQLOLE_PRIVILEGE_TYPE lPrivilegeTypes CPPDEFAULT(= SQLOLEPriv_AllObjectPrivs)) PURE;
    STDMETHOD(ListUserPermissions)(THIS_ SQLOLE_LPCSTR UserName, LPSQLOLEPERMISSIONLIST * ppList) PURE;
    STDMETHOD(ListArticles)(THIS_ LPSQLOLEARTICLELIST * ppList) PURE;

	// Post-6.0 additions.
	STDMETHOD(CheckIdentityValue)(THIS) PURE;
    STDMETHOD(RebuildIndexes)(THIS_ SQLOLE_INDEX_TYPE SortedDataType CPPDEFAULT(= SQLOLEIndex_Default), long lFillFactor CPPDEFAULT(= SQLOLE_USEEXISTINGFILLFACTOR)) PURE;
    STDMETHOD(ImportData)(THIS_ LPSQLOLEBULKCOPY Bcp, LPLONG plRowsImported CPPDEFAULT(= NULL)) PURE;
    STDMETHOD(ExportData)(THIS_ LPSQLOLEBULKCOPY Bcp, LPLONG plRowsExported CPPDEFAULT(= NULL)) PURE;
    STDMETHOD(CheckTableDataOnly)(THIS_ SQLOLE_LPBSTR pResult) PURE;
    STDMETHOD(InAlter)(THIS_ LPBOOL pRetVal) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLEView
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

	//*** properties
    STDMETHOD(GetName)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetName)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetID)(THIS_ LPLONG plID) PURE;
    STDMETHOD(GetOwner)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(GetCreateDate)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(GetText)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetText)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetSystemObject)(THIS_ LPBOOL pRetVal) PURE;

	//*** methods
    STDMETHOD(Grant)(THIS_ SQLOLE_PRIVILEGE_TYPE iPrivileges, SQLOLE_LPCSTR GranteeNames, SQLOLE_LPCSTR ColumnNames CPPDEFAULT(= NULL)) PURE;
    STDMETHOD(Revoke)(THIS_ SQLOLE_PRIVILEGE_TYPE iPrivileges, SQLOLE_LPCSTR RevokeeNames, SQLOLE_LPCSTR ColumnNames CPPDEFAULT(= NULL)) PURE;
    STDMETHOD(Remove)(THIS) PURE;
    STDMETHOD(Script)(THIS_ SQLOLE_SCRIPT_TYPE ScriptType CPPDEFAULT(= SQLOLEScript_Default), SQLOLE_LPCSTR ScriptFilePath CPPDEFAULT(= NULL), SQLOLE_LPBSTR ScriptText CPPDEFAULT(= NULL)) PURE;
    STDMETHOD(EnumDependencies)(THIS_ LPSQLOLEQUERYRESULTS *ppResults, SQLOLE_DEPENDENCY_TYPE DependencyType CPPDEFAULT(= SQLOLEDep_Parents)) PURE;
    
    // List methods
    STDMETHOD(ListPermissions)(THIS_ LPSQLOLEPERMISSIONLIST * ppList, SQLOLE_PRIVILEGE_TYPE lPrivilegeTypes CPPDEFAULT(= SQLOLEPriv_AllObjectPrivs)) PURE;
    STDMETHOD(ListUserPermissions)(THIS_ SQLOLE_LPCSTR UserName, LPSQLOLEPERMISSIONLIST * ppList) PURE;
    STDMETHOD(ListColumns)(THIS_ LPSQLOLECOLUMNLIST * ppList) PURE;

	// Post-6.0 additions.
    STDMETHOD(ExportData)(THIS_ LPSQLOLEBULKCOPY Bcp, LPLONG plRowsExported CPPDEFAULT(= NULL)) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLEColumn
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

	//*** properties
    STDMETHOD(GetName)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetName)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetDatatype)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetDatatype)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetPhysicalDatatype)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(GetLength)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetLength)(THIS_ long NewValue) PURE;
    STDMETHOD(GetDefault)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetDefault)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetRule)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetRule)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetAllowNulls)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetAllowNulls)(THIS_ BOOL NewValue) PURE;
    STDMETHOD(GetID)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetIdentity)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetIdentity)(THIS_ BOOL NewValue) PURE;
    STDMETHOD(GetNumericPrecision)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetNumericPrecision)(THIS_ long NewValue) PURE;
    STDMETHOD(GetNumericScale)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetNumericScale)(THIS_ long NewValue) PURE;
    STDMETHOD(GetIdentitySeed)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetIdentitySeed)(THIS_ long NewValue) PURE;
    STDMETHOD(GetIdentityIncrement)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetIdentityIncrement)(THIS_ long NewValue) PURE;
    STDMETHOD(GetDRIDefault)(THIS_ LPSQLOLEDRIDEFAULT *ppDRIDefault) PURE;
    STDMETHOD(GetInPrimaryKey)(THIS_ LPBOOL pRetVal) PURE;

   //*** methods
    STDMETHOD(Remove)(THIS) PURE;
    STDMETHOD(ListKeys)(THIS_ LPSQLOLEKEYLIST * ppList) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLEPermission
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

	//*** properties
    STDMETHOD(GetPrivilegeTypeName)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(GetPrivilegeType)(THIS_ SQLOLE_PRIVILEGE_TYPE *pRetVal) PURE;
    STDMETHOD(GetObjectName)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(GetObjectOwner)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(GetObjectTypeName)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(GetObjectType)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetObjectID)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetGrantee)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(GetGranted)(THIS_ LPBOOL pRetVal) PURE;

	//*** methods
	// List methods
    STDMETHOD(ListPrivilegeColumns)(THIS_ LPSQLOLECOLUMNLIST * ppList) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLEDBOption
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

	//*** properties
    STDMETHOD(GetSelectIntoBulkCopy)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetSelectIntoBulkCopy)(THIS_ BOOL NewValue) PURE;
    STDMETHOD(GetDBOUseOnly)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetDBOUseOnly)(THIS_ BOOL NewValue) PURE;
    STDMETHOD(GetNoCheckpointOnRecovery)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetNoCheckpointOnRecovery)(THIS_ BOOL NewValue) PURE;
    STDMETHOD(GetReadOnly)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetReadOnly)(THIS_ BOOL NewValue) PURE;
    STDMETHOD(GetSingleUser)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetSingleUser)(THIS_ BOOL NewValue) PURE;
    STDMETHOD(GetTruncateLogOnCheckpoint)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetTruncateLogOnCheckpoint)(THIS_ BOOL NewValue) PURE;
    STDMETHOD(GetEnablePublishing)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetEnablePublishing)(THIS_ BOOL NewValue) PURE;
    STDMETHOD(GetEnableSubscribing)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetEnableSubscribing)(THIS_ BOOL NewValue) PURE;
    STDMETHOD(GetColumnsNullByDefault)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetColumnsNullByDefault)(THIS_ BOOL NewValue) PURE;
    STDMETHOD(GetOffline)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetOffline)(THIS_ BOOL NewValue) PURE;

	//*** methods
    STDMETHOD(Refresh)(THIS) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLEDBObject
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

	//*** properties
    STDMETHOD(GetName)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetName)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetOwner)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(GetTypeName)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(GetType)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetCreateDate)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(GetID)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetSystemObject)(THIS_ LPBOOL pRetVal) PURE;
    
    //*** methods
    STDMETHOD(Remove)(THIS) PURE;
    STDMETHOD(Script)(THIS_ SQLOLE_SCRIPT_TYPE ScriptType CPPDEFAULT(= SQLOLEScript_Default), SQLOLE_LPCSTR ScriptFilePath CPPDEFAULT(= NULL), SQLOLE_LPBSTR ScriptText CPPDEFAULT(= NULL)) PURE;
    STDMETHOD(EnumDependencies)(THIS_ LPSQLOLEQUERYRESULTS *ppResults, SQLOLE_DEPENDENCY_TYPE DependencyType CPPDEFAULT(= SQLOLEDep_Parents)) PURE;

	// List methods
    STDMETHOD(ListPermissions)(THIS_ LPSQLOLEPERMISSIONLIST * ppList, SQLOLE_PRIVILEGE_TYPE lPrivilegeTypes CPPDEFAULT(= SQLOLEPriv_AllObjectPrivs)) PURE;
    STDMETHOD(ListUserPermissions)(THIS_ SQLOLE_LPCSTR UserName, LPSQLOLEPERMISSIONLIST * ppList) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLEIndex
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

	//*** properties
    STDMETHOD(GetName)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetName)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetType)(THIS_ SQLOLE_INDEX_TYPE *pRetVal) PURE;
    STDMETHOD(SetType)(THIS_ SQLOLE_INDEX_TYPE NewValue) PURE;
    STDMETHOD(GetID)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetFillFactor)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetFillFactor)(THIS_ long lNewValue) PURE;
    STDMETHOD(GetSpaceUsed)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetIndexedColumns)(THIS_ SQLOLE_LPCSTR ColumnNames) PURE;
    
    //*** methods
    STDMETHOD(UpdateStatistics)(THIS) PURE;
    STDMETHOD(Remove)(THIS) PURE;
    STDMETHOD(Script)(THIS_ SQLOLE_SCRIPT_TYPE ScriptType CPPDEFAULT(= SQLOLEScript_Default), SQLOLE_LPCSTR ScriptFilePath CPPDEFAULT(= NULL), SQLOLE_LPBSTR ScriptText CPPDEFAULT(= NULL)) PURE;
    STDMETHOD(Rebuild)(THIS) PURE;
    STDMETHOD(RecalcSpaceUsage)(THIS) PURE;
    STDMETHOD(EnumStatistics)(THIS_ LPSQLOLEQUERYRESULTS *ppResults) PURE;
    STDMETHOD(GenerateCreationSQL)(THIS_ LPSQLOLETABLE TargetTable, SQLOLE_LPBSTR pSQLStatement) PURE;

	// List methods
    STDMETHOD(ListIndexedColumns)(THIS_ LPSQLOLECOLUMNLIST * ppList) PURE;

	// Post-6.0 additions.
    STDMETHOD(CheckIndex)(THIS_ SQLOLE_LPBSTR pResult) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLEKey
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

	//*** properties
    STDMETHOD(GetName)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetName)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetType)(THIS_ SQLOLE_KEY_TYPE *pRetVal) PURE;
    STDMETHOD(SetType)(THIS_ SQLOLE_KEY_TYPE NewValue) PURE;
    STDMETHOD(GetClustered)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetClustered)(THIS_ BOOL bNewValue) PURE;
    STDMETHOD(GetFillFactor)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetFillFactor)(THIS_ long lNewValue) PURE;
    STDMETHOD(GetReferencedTable)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetReferencedTable)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetReferencedKey)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    
	//*** Collection properties
    STDMETHOD(GetKeyColumns)(THIS_ LPSQLOLENAMES *ppColumnNames) PURE;
    STDMETHOD(GetReferencedColumns)(THIS_ LPSQLOLENAMES *ppColumnNames) PURE;

    //*** methods
    STDMETHOD(Remove)(THIS) PURE;
    STDMETHOD(Script)(THIS_ SQLOLE_SCRIPT_TYPE ScriptType CPPDEFAULT(= SQLOLEScript_Default), SQLOLE_LPCSTR ScriptFilePath CPPDEFAULT(= NULL), SQLOLE_LPBSTR ScriptText CPPDEFAULT(= NULL)) PURE;

	// Post-6.0 additions.
    STDMETHOD(RebuildIndex)(THIS) PURE;
    STDMETHOD(GetExcludeReplication)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetExcludeReplication)(THIS_ BOOL NewValue) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLECheck
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

	//*** properties
    STDMETHOD(GetName)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetName)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetText)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetText)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetExcludeReplication)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetExcludeReplication)(THIS_ BOOL NewValue) PURE;

	//*** methods
    STDMETHOD(Remove)(THIS) PURE;
    STDMETHOD(Script)(THIS_ SQLOLE_SCRIPT_TYPE ScriptType CPPDEFAULT(= SQLOLEScript_Default), SQLOLE_LPCSTR ScriptFilePath CPPDEFAULT(= NULL), SQLOLE_LPBSTR ScriptText CPPDEFAULT(= NULL)) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLEDRIDefault
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

	//*** properties
    STDMETHOD(GetName)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetName)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetText)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetText)(THIS_ SQLOLE_LPCSTR NewValue) PURE;

	//*** methods
    STDMETHOD(Remove)(THIS) PURE;
    STDMETHOD(Script)(THIS_ SQLOLE_SCRIPT_TYPE ScriptType CPPDEFAULT(= SQLOLEScript_Default), SQLOLE_LPCSTR ScriptFilePath CPPDEFAULT(= NULL), SQLOLE_LPBSTR ScriptText CPPDEFAULT(= NULL)) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLERule
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

	//*** properties
    STDMETHOD(GetName)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetName)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetOwner)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(GetCreateDate)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(GetID)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetText)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetText)(THIS_ SQLOLE_LPCSTR NewValue) PURE;

	//*** methods
    STDMETHOD(BindToColumn)(THIS_ SQLOLE_LPCSTR TableName, SQLOLE_LPCSTR ColumnName) PURE;
    STDMETHOD(BindToDatatype)(THIS_ SQLOLE_LPCSTR DatatypeName, BOOL bFutureOnly CPPDEFAULT(= FALSE)) PURE;
    STDMETHOD(UnbindFromColumn)(THIS_ SQLOLE_LPCSTR TableName, SQLOLE_LPCSTR ColumnName) PURE;
    STDMETHOD(UnbindFromDatatype)(THIS_ SQLOLE_LPCSTR DatatypeName, BOOL bFutureOnly CPPDEFAULT(= FALSE)) PURE;
    STDMETHOD(Remove)(THIS) PURE;
    STDMETHOD(Script)(THIS_ SQLOLE_SCRIPT_TYPE ScriptType CPPDEFAULT(= SQLOLEScript_Default), SQLOLE_LPCSTR ScriptFilePath CPPDEFAULT(= NULL), SQLOLE_LPBSTR ScriptText CPPDEFAULT(= NULL)) PURE;

	// List methods
    STDMETHOD(ListBoundColumns)(THIS_ LPSQLOLECOLUMNLIST * ppList) PURE;
    STDMETHOD(ListBoundDatatypes)(THIS_ LPSQLOLEUSERDEFINEDDATATYPELIST * ppList) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLEDefault
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

	//*** properties
    STDMETHOD(GetName)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetName)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetOwner)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(GetCreateDate)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(GetID)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetText)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetText)(THIS_ SQLOLE_LPCSTR NewValue) PURE;

	//*** methods
    STDMETHOD(BindToColumn)(THIS_ SQLOLE_LPCSTR TableName, SQLOLE_LPCSTR ColumnName) PURE;
    STDMETHOD(BindToDatatype)(THIS_ SQLOLE_LPCSTR DatatypeName, BOOL bFutureOnly CPPDEFAULT(= FALSE)) PURE;
    STDMETHOD(UnbindFromColumn)(THIS_ SQLOLE_LPCSTR TableName, SQLOLE_LPCSTR ColumnName) PURE;
    STDMETHOD(UnbindFromDatatype)(THIS_ SQLOLE_LPCSTR DatatypeName, BOOL bFutureOnly CPPDEFAULT(= FALSE)) PURE;
    STDMETHOD(Remove)(THIS) PURE;
    STDMETHOD(Script)(THIS_ SQLOLE_SCRIPT_TYPE ScriptType CPPDEFAULT(= SQLOLEScript_Default), SQLOLE_LPCSTR ScriptFilePath CPPDEFAULT(= NULL), SQLOLE_LPBSTR ScriptText CPPDEFAULT(= NULL)) PURE;

	// List methods
    STDMETHOD(ListBoundColumns)(THIS_ LPSQLOLECOLUMNLIST * ppList) PURE;
    STDMETHOD(ListBoundDatatypes)(THIS_ LPSQLOLEUSERDEFINEDDATATYPELIST * ppList) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLEStoredProcedure
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

	//*** properties
    STDMETHOD(GetName)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetName)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetOwner)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(GetCreateDate)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(GetID)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetText)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetText)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetType)(THIS_ SQLOLE_PROCEDURE_TYPE *pRetVal) PURE;
    STDMETHOD(SetType)(THIS_ SQLOLE_PROCEDURE_TYPE NewValue) PURE;
    STDMETHOD(GetStartup)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetStartup)(THIS_ BOOL NewValue) PURE;
    STDMETHOD(GetSystemObject)(THIS_ LPBOOL pRetVal) PURE;

	//*** methods
    STDMETHOD(Grant)(THIS_ SQLOLE_PRIVILEGE_TYPE iPrivileges, SQLOLE_LPCSTR GranteeNames) PURE;
    STDMETHOD(Revoke)(THIS_ SQLOLE_PRIVILEGE_TYPE iPrivileges, SQLOLE_LPCSTR RevokeeNames) PURE;
    STDMETHOD(Remove)(THIS) PURE;
    STDMETHOD(EnumParameters)(THIS_ LPSQLOLEQUERYRESULTS * ppResults) PURE;
    STDMETHOD(Script)(THIS_ SQLOLE_SCRIPT_TYPE ScriptType CPPDEFAULT(= SQLOLEScript_Default), SQLOLE_LPCSTR ScriptFilePath CPPDEFAULT(= NULL), SQLOLE_LPBSTR ScriptText CPPDEFAULT(= NULL)) PURE;
    STDMETHOD(EnumDependencies)(THIS_ LPSQLOLEQUERYRESULTS *ppResults, SQLOLE_DEPENDENCY_TYPE DependencyType CPPDEFAULT(= SQLOLEDep_Parents)) PURE;

	// List methods
    STDMETHOD(ListPermissions)(THIS_ LPSQLOLEPERMISSIONLIST * ppList, SQLOLE_PRIVILEGE_TYPE lPrivilegeTypes CPPDEFAULT(= SQLOLEPriv_Execute)) PURE;
    STDMETHOD(ListUserPermissions)(THIS_ SQLOLE_LPCSTR UserName, LPSQLOLEPERMISSIONLIST * ppList) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLEBackup
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

	//*** properties
    STDMETHOD(GetDumpDevices)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetDumpDevices)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetDiskDevices)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetDiskDevices)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetTapeDevices)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetTapeDevices)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetFloppyDevices)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetFloppyDevices)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetUnloadTapeAfter)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetUnloadTapeAfter)(THIS_ BOOL NewValue) PURE;
    STDMETHOD(GetDumpInitDeviceBefore)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetDumpInitDeviceBefore)(THIS_ BOOL NewValue) PURE;
    STDMETHOD(GetDumpExpirationDate)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetDumpExpirationDate)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetDumpRetainDays)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetDumpRetainDays)(THIS_ long NewValue) PURE;
    STDMETHOD(GetSkipTapeHeader)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetSkipTapeHeader)(THIS_ BOOL NewValue) PURE;
    STDMETHOD(GetLoadTableBatchPages)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetLoadTableBatchPages)(THIS_ long NewValue) PURE;
    STDMETHOD(GetLoadFileNumber)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetLoadFileNumber)(THIS_ long NewValue) PURE;

	// Post-6.0 additions
    STDMETHOD(GetTableName)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetTableName)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetLoadStopDate)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetLoadStopDate)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetPipeDevices)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetPipeDevices)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetLoadFromSourceTableName)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetLoadFromSourceTableName)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetLoadAppendToTableData)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetLoadAppendToTableData)(THIS_ BOOL NewValue) PURE;
    STDMETHOD(GetPercentCompleteNotification)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetPercentCompleteNotification)(THIS_ long NewValue) PURE;

	// methods
    STDMETHOD(Abort)(THIS) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLEBulkCopy
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

	//*** properties
    STDMETHOD(GetDataFilePath)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetDataFilePath)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetFormatFilePath)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetFormatFilePath)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetErrorFilePath)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetErrorFilePath)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetLogFilePath)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetLogFilePath)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetColumnDelimiter)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetColumnDelimiter)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetRowDelimiter)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetRowDelimiter)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetDataFileType)(THIS_ SQLOLE_DATAFILE_TYPE FAR* pRetVal) PURE;
    STDMETHOD(SetDataFileType)(THIS_ SQLOLE_DATAFILE_TYPE NewValue) PURE;
    STDMETHOD(GetFirstRow)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetFirstRow)(THIS_ long NewValue) PURE;
    STDMETHOD(GetLastRow)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetLastRow)(THIS_ long NewValue) PURE;
    STDMETHOD(GetMaximumErrorsBeforeAbort)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetMaximumErrorsBeforeAbort)(THIS_ long NewValue) PURE;
    STDMETHOD(GetIncludeIdentityValues)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetIncludeIdentityValues)(THIS_ BOOL NewValue) PURE;
    STDMETHOD(GetImportRowsPerBatch)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetImportRowsPerBatch)(THIS_ long NewValue) PURE;
    STDMETHOD(GetUseBulkCopyOption)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetUseBulkCopyOption)(THIS_ BOOL NewValue) PURE;
    STDMETHOD(GetSuspendIndexing)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetSuspendIndexing)(THIS_ BOOL NewValue) PURE;
    STDMETHOD(GetTruncateLog)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetTruncateLog)(THIS_ BOOL NewValue) PURE;

	// Methods
    STDMETHOD(Abort)(THIS) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLEUserDefinedDatatype
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

	//*** properties
    STDMETHOD(GetName)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetName)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetOwner)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(GetAllowNulls)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetAllowNulls)(THIS_ BOOL NewValue) PURE;
    STDMETHOD(GetBaseType)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetBaseType)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetLength)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetLength)(THIS_ long NewValue) PURE;
    STDMETHOD(GetDefault)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetDefault)(THIS_ SQLOLE_LPCSTR NewValue, BOOL bFutureOnly CPPDEFAULT(= FALSE)) PURE;
    STDMETHOD(GetRule)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetRule)(THIS_ SQLOLE_LPCSTR NewValue, BOOL bFutureOnly CPPDEFAULT(= FALSE)) PURE;
    STDMETHOD(GetID)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetNumericPrecision)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetNumericPrecision)(THIS_ long NewValue) PURE;
    STDMETHOD(GetNumericScale)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetNumericScale)(THIS_ long NewValue) PURE;
    STDMETHOD(GetAllowIdentity)(THIS_ LPBOOL pRetVal) PURE;

	//*** methods
    STDMETHOD(Remove)(THIS) PURE;
    STDMETHOD(Script)(THIS_ SQLOLE_SCRIPT_TYPE ScriptType CPPDEFAULT(= SQLOLEScript_Default), SQLOLE_LPCSTR ScriptFilePath CPPDEFAULT(= NULL), SQLOLE_LPBSTR ScriptText CPPDEFAULT(= NULL)) PURE;

	// List methods
    STDMETHOD(ListBoundColumns)(THIS_ LPSQLOLECOLUMNLIST * ppList) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLEUser
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

	//*** properties
    STDMETHOD(GetName)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetName)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetLogin)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetLogin)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetGroup)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetGroup)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetID)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetSystemObject)(THIS_ LPBOOL pRetVal) PURE;

	//*** methods
    STDMETHOD(AddAlias)(THIS_ SQLOLE_LPCSTR LoginNames) PURE;
    STDMETHOD(RemoveAlias)(THIS_ SQLOLE_LPCSTR LoginNames) PURE;
    STDMETHOD(Remove)(THIS) PURE;
    STDMETHOD(Script)(THIS_ SQLOLE_SCRIPT_TYPE ScriptType CPPDEFAULT(= SQLOLEScript_Default), SQLOLE_LPCSTR ScriptFilePath CPPDEFAULT(= NULL), SQLOLE_LPBSTR ScriptText CPPDEFAULT(= NULL)) PURE;

	// List methods
    STDMETHOD(ListAliases)(THIS_ LPSQLOLELOGINLIST * ppList) PURE;
    STDMETHOD(ListOwnedObjects)(THIS_ LPSQLOLEDBOBJECTLIST * ppList, SQLOLE_OBJECT_TYPE lObjectTypes CPPDEFAULT(= SQLOLEObj_AllDatabaseObjects), SQLOLE_OBJSORT_TYPE SortBy CPPDEFAULT(= SQLOLEObjSort_Name)) PURE;
    STDMETHOD(ListDatabasePermissions)(THIS_ LPSQLOLEPERMISSIONLIST * ppList, SQLOLE_PRIVILEGE_TYPE lPrivilegeTypes CPPDEFAULT(= SQLOLEPriv_AllDatabasePrivs)) PURE;
    STDMETHOD(ListObjectPermissions)(THIS_ LPSQLOLEPERMISSIONLIST * ppList, SQLOLE_PRIVILEGE_TYPE lPrivilegeTypes CPPDEFAULT(= SQLOLEPriv_AllObjectPrivs)) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLEGroup
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

	//*** properties
    STDMETHOD(GetName)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetName)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetID)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetSystemObject)(THIS_ LPBOOL pRetVal) PURE;

	//*** methods
    STDMETHOD(Remove)(THIS) PURE;

	// List methods
    STDMETHOD(ListUsers)(THIS_ LPSQLOLEUSERLIST * ppList) PURE;
    STDMETHOD(ListDatabasePermissions)(THIS_ LPSQLOLEPERMISSIONLIST * ppList, SQLOLE_PRIVILEGE_TYPE lPrivilegeTypes CPPDEFAULT(= SQLOLEPriv_AllDatabasePrivs)) PURE;
    STDMETHOD(ListObjectPermissions)(THIS_ LPSQLOLEPERMISSIONLIST * ppList, SQLOLE_PRIVILEGE_TYPE lPrivilegeTypes CPPDEFAULT(= SQLOLEPriv_AllObjectPrivs)) PURE;
    STDMETHOD(Script)(THIS_ SQLOLE_SCRIPT_TYPE ScriptType CPPDEFAULT(= SQLOLEScript_Default), SQLOLE_LPCSTR ScriptFilePath CPPDEFAULT(= NULL), SQLOLE_LPBSTR ScriptText CPPDEFAULT(= NULL)) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLETrigger
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

	//*** properties
    STDMETHOD(GetName)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetName)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetOwner)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(GetCreateDate)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(GetID)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetText)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetText)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetType)(THIS_ SQLOLE_TRIGGER_TYPE *pRetVal) PURE;
    STDMETHOD(GetSystemObject)(THIS_ LPBOOL pRetVal) PURE;

	//*** methods
    STDMETHOD(Remove)(THIS) PURE;
    STDMETHOD(Script)(THIS_ SQLOLE_SCRIPT_TYPE ScriptType CPPDEFAULT(= SQLOLEScript_Default), SQLOLE_LPCSTR ScriptFilePath CPPDEFAULT(= NULL), SQLOLE_LPBSTR ScriptText CPPDEFAULT(= NULL)) PURE;
    STDMETHOD(EnumDependencies)(THIS_ LPSQLOLEQUERYRESULTS *ppResults, SQLOLE_DEPENDENCY_TYPE DependencyType CPPDEFAULT(= SQLOLEDep_Parents)) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLESystemDatatype
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

	//*** properties
    STDMETHOD(GetName)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(GetMaximumLength)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetAllowNulls)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(GetIsNumeric)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(GetAllowIdentity)(THIS_ LPBOOL pRetVal) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLEExecutive
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

	//*** properties
    STDMETHOD(GetStatus)(THIS_ SQLOLE_SVCSTATUS_TYPE *pRetVal) PURE;
    STDMETHOD(GetAutoStart)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetAutoStart)(THIS_ BOOL NewValue) PURE;
    STDMETHOD(GetRestartSQLServer)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetRestartSQLServer)(THIS_ BOOL NewValue) PURE;
    STDMETHOD(GetRestartSQLServerInterval)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetRestartSQLServerInterval)(THIS_ long NewValue) PURE;
    STDMETHOD(GetLimitHistoryRows)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetLimitHistoryRows)(THIS_ BOOL NewValue) PURE;
    STDMETHOD(GetLimitHistoryRowsMax)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetLimitHistoryRowsMax)(THIS_ long NewValue) PURE;
    STDMETHOD(GetAlertSystem)(THIS_ LPSQLOLEALERTSYSTEM * ppAlertSystem) PURE;

	//*** Collection properties
    STDMETHOD(GetTasks)(THIS_ LPSQLOLETASKS * ppTasks) PURE;
    STDMETHOD(GetTaskByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLETASK *ppTask) PURE;
    STDMETHOD(GetTaskByOrd)(THIS_ long lOrdinal, LPSQLOLETASK *ppTask) PURE;
    STDMETHOD(RemoveTaskByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
    STDMETHOD(RemoveTaskByOrd)(THIS_ long lOrdinal) PURE;
    STDMETHOD(AddTask)(THIS_ LPSQLOLETASK pTask) PURE;
    STDMETHOD(GetTaskCount)(THIS_ LPLONG plCount) PURE;

	//*** methods
    STDMETHOD(Stop)(THIS) PURE;
    STDMETHOD(Start)(THIS) PURE;
    STDMETHOD(EnumSubSystems)(THIS_ LPSQLOLEQUERYRESULTS *ppResults) PURE;
    STDMETHOD(EnumQueuedTasks)(THIS_ LPSQLOLEQUERYRESULTS *ppResults) PURE;
    STDMETHOD(ReassignLoginTasks)(THIS_ SQLOLE_LPCSTR szOldLogin, SQLOLE_LPCSTR szNewLogin) PURE;
    STDMETHOD(RemoveLoginTasks)(THIS_ SQLOLE_LPCSTR szLogin) PURE;
	STDMETHOD(Refresh)(THIS) PURE;
    STDMETHOD(BeginAlter)(THIS) PURE;
    STDMETHOD(DoAlter)(THIS) PURE;
    STDMETHOD(CancelAlter)(THIS) PURE;

	// List methods
    STDMETHOD(ListSubSystemTasks)(THIS_ SQLOLE_LPCSTR szSubSystem, LPSQLOLETASKLIST * ppList) PURE;

	// Post-6.0 additions
    STDMETHOD(GetLimitHistoryRowsPerTaskMax)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetLimitHistoryRowsPerTaskMax)(THIS_ long NewValue) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLETask
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

	//*** properties
    STDMETHOD(GetName)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetName)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetID)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetSubSystem)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetSubSystem)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetOwner)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(GetEnabled)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetEnabled)(THIS_ BOOL NewValue) PURE;
    STDMETHOD(GetDatabase)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetDatabase)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetUser)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetUser)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetFrequencyType)(THIS_ SQLOLE_FREQUENCY_TYPE *pRetVal) PURE;
    STDMETHOD(SetFrequencyType)(THIS_ SQLOLE_FREQUENCY_TYPE NewValue) PURE;
    STDMETHOD(GetFrequencyInterval)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetFrequencyInterval)(THIS_ long NewValue) PURE;
    STDMETHOD(GetFrequencyRelativeInterval)(THIS_ SQLOLE_FREQRELATIVE_TYPE *pRetVal) PURE;
    STDMETHOD(SetFrequencyRelativeInterval)(THIS_ SQLOLE_FREQRELATIVE_TYPE NewValue) PURE;
    STDMETHOD(GetFrequencyRecurrenceFactor)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetFrequencyRecurrenceFactor)(THIS_ long NewValue) PURE;
    STDMETHOD(GetActiveStartDate)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetActiveStartDate)(THIS_ long NewValue) PURE;
    STDMETHOD(GetActiveEndDate)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetActiveEndDate)(THIS_ long NewValue) PURE;
    STDMETHOD(GetActiveStartTimeOfDay)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetActiveStartTimeOfDay)(THIS_ long NewValue) PURE;
    STDMETHOD(GetActiveEndTimeOfDay)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetActiveEndTimeOfDay)(THIS_ long NewValue) PURE;
    STDMETHOD(GetNextRunDate)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetNextRunTime)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetLastRunDate)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetLastRunTime)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetRunPriority)(THIS_ SQLOLE_RUNPRIORITY_TYPE *pRetVal) PURE;
    STDMETHOD(SetRunPriority)(THIS_ SQLOLE_RUNPRIORITY_TYPE NewValue) PURE;
    STDMETHOD(GetEmailOperator)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetEmailOperator)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetRetryAttempts)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetRetryAttempts)(THIS_ long NewValue) PURE;
    STDMETHOD(GetRetryDelay)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetRetryDelay)(THIS_ long NewValue) PURE;
    STDMETHOD(GetLastRunRetries)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetDateCreated)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(GetDateModified)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(GetCommand)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetCommand)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetLastRunCompletionLevel)(THIS_ SQLOLE_COMPLETION_TYPE *pRetVal) PURE;
    STDMETHOD(GetLastRunDuration)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetLogHistoryCompletionLevel)(THIS_ SQLOLE_COMPLETION_TYPE *pRetVal) PURE;
    STDMETHOD(SetLogHistoryCompletionLevel)(THIS_ SQLOLE_COMPLETION_TYPE NewValue) PURE;
    STDMETHOD(GetEmailCompletionLevel)(THIS_ SQLOLE_COMPLETION_TYPE *pRetVal) PURE;
    STDMETHOD(SetEmailCompletionLevel)(THIS_ SQLOLE_COMPLETION_TYPE NewValue) PURE;
    STDMETHOD(GetTargetSQLServer)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetTargetSQLServer)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetDescription)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetDescription)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetFrequencySubDay)(THIS_ SQLOLE_FREQSUB_TYPE *pRetVal) PURE;
    STDMETHOD(SetFrequencySubDay)(THIS_ SQLOLE_FREQSUB_TYPE NewValue) PURE;
    STDMETHOD(GetFrequencySubDayInterval)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetFrequencySubDayInterval)(THIS_ long NewValue) PURE;
    STDMETHOD(GetTagAdditionalInfo)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetTagAdditionalInfo)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetTagObjectID)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetTagObjectID)(THIS_ long NewValue) PURE;
    STDMETHOD(GetTagObjectType)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetTagObjectType)(THIS_ long NewValue) PURE;

	//*** methods
    STDMETHOD(EnumHistory)(THIS_ LPSQLOLEQUERYRESULTS *ppResults, LPSQLOLEHISTORYFILTER pFilter CPPDEFAULT(= NULL)) PURE;
    STDMETHOD(PurgeHistory)(THIS_ LPSQLOLEHISTORYFILTER pFilter CPPDEFAULT(= NULL)) PURE;
    STDMETHOD(Invoke)(THIS) PURE;
    STDMETHOD(Remove)(THIS) PURE;
    STDMETHOD(BeginAlter)(THIS) PURE;
    STDMETHOD(DoAlter)(THIS) PURE;
    STDMETHOD(CancelAlter)(THIS) PURE;
    STDMETHOD(Refresh)(THIS) PURE;
    STDMETHOD(Reassign)(THIS_ SQLOLE_LPCSTR szNewLogin) PURE;

	// Post-6.0 additions
    STDMETHOD(GetParameters)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetParameters)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetCmdExecSuccessCode)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetCmdExecSuccessCode)(THIS_ long NewValue) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLEHistoryFilter
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

	//*** properties
    STDMETHOD(GetTaskName)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetTaskName)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetStartDate)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetStartDate)(THIS_ long NewValue) PURE;
    STDMETHOD(GetStartTime)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetStartTime)(THIS_ long NewValue) PURE;
    STDMETHOD(GetCompletionTypes)(THIS_ SQLOLE_COMPLETION_TYPE *pRetVal) PURE;
    STDMETHOD(SetCompletionTypes)(THIS_ SQLOLE_COMPLETION_TYPE NewValue) PURE;
    STDMETHOD(GetEventTypes)(THIS_ SQLOLE_EVENT_TYPE *pRetVal) PURE;
    STDMETHOD(SetEventTypes)(THIS_ SQLOLE_EVENT_TYPE NewValue) PURE;
    STDMETHOD(GetTaskID)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetTaskID)(THIS_ long NewValue) PURE;
    STDMETHOD(GetEventID)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetEventID)(THIS_ long NewValue) PURE;
    STDMETHOD(GetMessageID)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetMessageID)(THIS_ long NewValue) PURE;
    STDMETHOD(GetSeverity)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetSeverity)(THIS_ long NewValue) PURE;
    STDMETHOD(GetSource)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetSource)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetCategoryName)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetCategoryName)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetMinimumRunDuration)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetMinimumRunDuration)(THIS_ long NewValue) PURE;
    STDMETHOD(GetMinimumRetries)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetMinimumRetries)(THIS_ long NewValue) PURE;
    STDMETHOD(GetOldestFirst)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetOldestFirst)(THIS_ BOOL NewValue) PURE;
    STDMETHOD(GetEndDate)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetEndDate)(THIS_ long NewValue) PURE;
    STDMETHOD(GetEndTime)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetEndTime)(THIS_ long NewValue) PURE;
    STDMETHOD(GetMinimumTimesSkipped)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetMinimumTimesSkipped)(THIS_ LONG NewValue) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLEAlert
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

	//*** properties
    STDMETHOD(GetName)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetName)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetID)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetEventSource)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(GetEventCategory)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(GetEventID)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(GetMessageID)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetMessageID)(THIS_ long NewValue) PURE;
    STDMETHOD(GetSeverity)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetSeverity)(THIS_ long NewValue) PURE;
    STDMETHOD(GetEnabled)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetEnabled)(THIS_ BOOL NewValue) PURE;
    STDMETHOD(GetDelayBetweenResponses)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetDelayBetweenResponses)(THIS_ long NewValue) PURE;
    STDMETHOD(GetLastOccurrenceDate)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetLastOccurrenceDate)(THIS_ long NewValue) PURE;
    STDMETHOD(GetLastOccurrenceTime)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetLastOccurrenceTime)(THIS_ long NewValue) PURE;
    STDMETHOD(GetLastResponseDate)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetLastResponseDate)(THIS_ long NewValue) PURE;
    STDMETHOD(GetLastResponseTime)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetLastResponseTime)(THIS_ long NewValue) PURE;
    STDMETHOD(GetNotificationMessage)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetNotificationMessage)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetIncludeEventDescription)(THIS_ SQLOLE_NOTIFY_TYPE *pRetVal) PURE;
    STDMETHOD(SetIncludeEventDescription)(THIS_ SQLOLE_NOTIFY_TYPE NewValue) PURE;
    STDMETHOD(GetDatabaseName)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetDatabaseName)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetEventDescriptionKeyword)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetEventDescriptionKeyword)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetOccurrenceCount)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetOccurrenceCount)(THIS_ long NewValue) PURE;
    STDMETHOD(GetCountResetDate)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetCountResetDate)(THIS_ long NewValue) PURE;
    STDMETHOD(GetCountResetTime)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetCountResetTime)(THIS_ long NewValue) PURE;
    STDMETHOD(GetTaskName)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetTaskName)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetHasEmailNotification)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetHasPagerNotification)(THIS_ LPLONG pRetVal) PURE;

	//*** methods
    STDMETHOD(AddNotification)(THIS_ SQLOLE_LPCSTR OperatorName, SQLOLE_NOTIFY_TYPE NotifyMethod) PURE;
    STDMETHOD(UpdateNotification)(THIS_ SQLOLE_LPCSTR OperatorName, SQLOLE_NOTIFY_TYPE NotifyMethod) PURE;
    STDMETHOD(RemoveNotification)(THIS_ SQLOLE_LPCSTR OperatorName) PURE;
    STDMETHOD(EnumNotifications)(THIS_ SQLOLE_NOTIFY_TYPE NotifyMethod, SQLOLE_ENUMNOTIFY_TYPE EnumNotifyType, LPSQLOLEQUERYRESULTS *ppResults, SQLOLE_LPCSTR OperatorName CPPDEFAULT(= NULL)) PURE;
    STDMETHOD(Remove)(THIS) PURE;
    STDMETHOD(BeginAlter)(THIS) PURE;
    STDMETHOD(DoAlter)(THIS) PURE;
    STDMETHOD(CancelAlter)(THIS) PURE;
	STDMETHOD(Refresh)(THIS) PURE;

   // Post-6.0 additions.
    STDMETHOD(GetRaiseSNMPTrap)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetRaiseSNMPTrap)(THIS_ BOOL NewValue) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLEOperator
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

	//*** properties
    STDMETHOD(GetName)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetName)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetID)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetEnabled)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetEnabled)(THIS_ BOOL NewValue) PURE;
    STDMETHOD(GetEmailAddress)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetEmailAddress)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetLastEmailDate)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetLastEmailTime)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetPagerAddress)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetPagerAddress)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetLastPageDate)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetLastPageTime)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetWeekdayPagerStartTime)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetWeekdayPagerStartTime)(THIS_ long NewValue) PURE;
    STDMETHOD(GetWeekdayPagerEndTime)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetWeekdayPagerEndTime)(THIS_ long NewValue) PURE;
    STDMETHOD(GetSaturdayPagerStartTime)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetSaturdayPagerStartTime)(THIS_ long NewValue) PURE;
    STDMETHOD(GetSaturdayPagerEndTime)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetSaturdayPagerEndTime)(THIS_ long NewValue) PURE;
    STDMETHOD(GetSundayPagerStartTime)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetSundayPagerStartTime)(THIS_ long NewValue) PURE;
    STDMETHOD(GetSundayPagerEndTime)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetSundayPagerEndTime)(THIS_ long NewValue) PURE;
    STDMETHOD(GetPagerDays)(THIS_ SQLOLE_WEEKDAY_TYPE *pRetVal) PURE;
    STDMETHOD(SetPagerDays)(THIS_ SQLOLE_WEEKDAY_TYPE NewValue) PURE;

	//*** methods
    STDMETHOD(AddNotification)(THIS_ SQLOLE_LPCSTR AlertName, SQLOLE_NOTIFY_TYPE NotifyMethod) PURE;
    STDMETHOD(UpdateNotification)(THIS_ SQLOLE_LPCSTR AlertName, SQLOLE_NOTIFY_TYPE NotifyMethod) PURE;
    STDMETHOD(RemoveNotification)(THIS_ SQLOLE_LPCSTR AlertName) PURE;
    STDMETHOD(EnumNotifications)(THIS_ SQLOLE_NOTIFY_TYPE NotifyMethod, SQLOLE_ENUMNOTIFY_TYPE EnumNotifyType, LPSQLOLEQUERYRESULTS *ppResults, SQLOLE_LPCSTR AlertName CPPDEFAULT(= NULL)) PURE;
    STDMETHOD(Remove)(THIS) PURE;
    STDMETHOD(BeginAlter)(THIS) PURE;
    STDMETHOD(DoAlter)(THIS) PURE;
    STDMETHOD(CancelAlter)(THIS) PURE;
	STDMETHOD(Refresh)(THIS) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLEPublication
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

	//*** properties
    STDMETHOD(GetName)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetName)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetID)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetDescription)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetDescription)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetEnabled)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetEnabled)(THIS_ BOOL NewValue) PURE;
    STDMETHOD(GetInitialSyncTask)(THIS_ LPSQLOLETASK *ppTask) PURE;
    STDMETHOD(GetInitialSyncMethod)(THIS_ SQLOLE_INITIALSYNC_TYPE *pRetVal) PURE;
    STDMETHOD(SetInitialSyncMethod)(THIS_ SQLOLE_INITIALSYNC_TYPE NewValue) PURE;
    STDMETHOD(GetReplicationFrequency)(THIS_ SQLOLE_REPFREQ_TYPE *pRetVal) PURE;
    STDMETHOD(SetReplicationFrequency)(THIS_ SQLOLE_REPFREQ_TYPE NewValue) PURE;
    STDMETHOD(GetRestricted)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetRestricted)(THIS_ BOOL NewValue) PURE;

	//*** Collection properties
    STDMETHOD(GetArticles)(THIS_ LPSQLOLEARTICLES * ppArticles) PURE;
    STDMETHOD(GetArticleByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLEARTICLE *ppArticle) PURE;
    STDMETHOD(GetArticleByOrd)(THIS_ long lOrdinal, LPSQLOLEARTICLE *ppArticle) PURE;
    STDMETHOD(RemoveArticleByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
    STDMETHOD(RemoveArticleByOrd)(THIS_ long lOrdinal) PURE;
    STDMETHOD(AddArticle)(THIS_ LPSQLOLEARTICLE pArticle) PURE;
    STDMETHOD(GetArticleCount)(THIS_ LPLONG plCount) PURE;

	//*** methods
    STDMETHOD(Remove)(THIS) PURE;
    STDMETHOD(EnumFullSubscribers)(THIS_ LPSQLOLEQUERYRESULTS *ppResults) PURE;
    STDMETHOD(BeginAlter)(THIS) PURE;
    STDMETHOD(DoAlter)(THIS) PURE;
    STDMETHOD(CancelAlter)(THIS) PURE;

	// Post-6.0 additions
    STDMETHOD(AddFullSubscriber)(THIS_ SQLOLE_LPCSTR ServerName, SQLOLE_LPCSTR DestinationDatabase CPPDEFAULT(= NULL), 
    	SQLOLE_SUBSYNC_TYPE InitialSyncType CPPDEFAULT(= SQLOLESubSync_Default), SQLOLE_SUBSTATUS_TYPE Status CPPDEFAULT(= SQLOLESubStat_Default)) PURE;
    STDMETHOD(RemoveFullSubscriber)(THIS_ SQLOLE_LPCSTR ServerName) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLEArticle
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

	//*** properties
    STDMETHOD(GetName)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetName)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetID)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetTableName)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetTableName)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetDescription)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetDescription)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetReplicateAllColumns)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(GetInitialSyncObjectName)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetInitialSyncObjectName)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetReplicationType)(THIS_ SQLOLE_REPLICATION_TYPE *pRetVal) PURE;
    STDMETHOD(SetReplicationType)(THIS_ SQLOLE_REPLICATION_TYPE NewValue) PURE;
    STDMETHOD(GetInsertCommand)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetInsertCommand)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetUpdateCommand)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetUpdateCommand)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetDeleteCommand)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetDeleteCommand)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetReplicationFilterProcName)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetReplicationFilterProcName)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetCreationScriptPath)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetCreationScriptPath)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetDestinationTableName)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetDestinationTableName)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetPreCreationMethod)(THIS_ SQLOLE_PREARTICLE_TYPE *pRetVal) PURE;
    STDMETHOD(SetPreCreationMethod)(THIS_ SQLOLE_PREARTICLE_TYPE NewValue) PURE;
    STDMETHOD(GetFilterClause)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetFilterClause)(THIS_ SQLOLE_LPCSTR NewValue) PURE;

	//*** Collection Properties
    STDMETHOD(GetSubscriptions)(THIS_ LPSQLOLESUBSCRIPTIONS * ppSubscriptions) PURE;
    STDMETHOD(GetSubscriptionByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLESUBSCRIPTION *ppSubscription) PURE;
    STDMETHOD(GetSubscriptionByOrd)(THIS_ long lOrdinal, LPSQLOLESUBSCRIPTION *ppSubscription) PURE;
    STDMETHOD(RemoveSubscriptionByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
    STDMETHOD(RemoveSubscriptionByOrd)(THIS_ long lOrdinal) PURE;
    STDMETHOD(AddSubscription)(THIS_ LPSQLOLESUBSCRIPTION pSubscription) PURE;
    STDMETHOD(GetSubscriptionCount)(THIS_ LPLONG plCount) PURE;

	//*** methods
    STDMETHOD(Remove)(THIS) PURE;
    STDMETHOD(ListReplicatedColumns)(THIS_ LPSQLOLECOLUMNLIST *ppList) PURE;
    STDMETHOD(AddReplicatedColumns)(THIS_ SQLOLE_LPCSTR Columns) PURE;
    STDMETHOD(RemoveReplicatedColumns)(THIS_ SQLOLE_LPCSTR Columns) PURE;
    STDMETHOD(BeginAlter)(THIS) PURE;
    STDMETHOD(DoAlter)(THIS) PURE;
    STDMETHOD(CancelAlter)(THIS) PURE;
    STDMETHOD(ScriptDestinationTable)(THIS_ SQLOLE_SCRIPT_TYPE ScriptType CPPDEFAULT(= SQLOLEScript_Default), SQLOLE_LPCSTR ScriptFilePath CPPDEFAULT(= NULL), SQLOLE_LPBSTR ScriptText CPPDEFAULT(= NULL)) PURE;

	// Post-6.0 additions
    STDMETHOD(GetOwnerQualifyTable)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetOwnerQualifyTable)(THIS_ BOOL NewValue) PURE;
    STDMETHOD(GetIncludeInsertColumnNames)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetIncludeInsertColumnNames)(THIS_ BOOL NewValue) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLESubscription
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

	//*** properties
    STDMETHOD(GetServerName)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetServerName)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetDestinationDatabase)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetDestinationDatabase)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetInitialSyncType)(THIS_ SQLOLE_SUBSYNC_TYPE *pRetVal) PURE;
    STDMETHOD(SetInitialSyncType)(THIS_ SQLOLE_SUBSYNC_TYPE NewValue) PURE;
    STDMETHOD(GetStatus)(THIS_ SQLOLE_SUBSTATUS_TYPE *pRetVal) PURE;
    STDMETHOD(SetStatus)(THIS_ SQLOLE_SUBSTATUS_TYPE NewValue) PURE;

	//*** methods
    STDMETHOD(Remove)(THIS) PURE;
    STDMETHOD(BeginAlter)(THIS) PURE;
    STDMETHOD(DoAlter)(THIS) PURE;
    STDMETHOD(CancelAlter)(THIS) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLESubscriberInfo
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

	//*** properties
    STDMETHOD(GetFrequencyType)(THIS_ SQLOLE_FREQUENCY_TYPE *pRetVal) PURE;
    STDMETHOD(SetFrequencyType)(THIS_ SQLOLE_FREQUENCY_TYPE NewValue) PURE;
    STDMETHOD(GetFrequencyInterval)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetFrequencyInterval)(THIS_ long NewValue) PURE;
    STDMETHOD(GetFrequencyRelativeInterval)(THIS_ SQLOLE_FREQRELATIVE_TYPE *pRetVal) PURE;
    STDMETHOD(SetFrequencyRelativeInterval)(THIS_ SQLOLE_FREQRELATIVE_TYPE NewValue) PURE;
    STDMETHOD(GetFrequencyRecurrenceFactor)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetFrequencyRecurrenceFactor)(THIS_ long NewValue) PURE;
    STDMETHOD(GetFrequencySubDay)(THIS_ SQLOLE_FREQSUB_TYPE *pRetVal) PURE;
    STDMETHOD(SetFrequencySubDay)(THIS_ SQLOLE_FREQSUB_TYPE NewValue) PURE;
    STDMETHOD(GetFrequencySubDayInterval)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetFrequencySubDayInterval)(THIS_ long NewValue) PURE;
    STDMETHOD(GetFlushFrequency)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetFlushFrequency)(THIS_ long NewValue) PURE;
    STDMETHOD(GetActiveStartDate)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetActiveStartDate)(THIS_ long NewValue) PURE;
    STDMETHOD(GetActiveEndDate)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetActiveEndDate)(THIS_ long NewValue) PURE;
    STDMETHOD(GetActiveStartTimeOfDay)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetActiveStartTimeOfDay)(THIS_ long NewValue) PURE;
    STDMETHOD(GetActiveEndTimeOfDay)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetActiveEndTimeOfDay)(THIS_ long NewValue) PURE;
    STDMETHOD(GetLogBatchSize)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetLogBatchSize)(THIS_ long NewValue) PURE;
    STDMETHOD(GetCommitTransactionCount)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetCommitTransactionCount)(THIS_ long NewValue) PURE;
    STDMETHOD(GetLogin)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetLogin)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetPassword)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetPassword)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetType)(THIS_ SQLOLE_SUBSCRIBERINFO_TYPE *pRetVal) PURE;
    STDMETHOD(SetType)(THIS_ SQLOLE_SUBSCRIBERINFO_TYPE NewValue) PURE;

	//*** methods
	STDMETHOD(Refresh)(THIS) PURE;
    STDMETHOD(BeginAlter)(THIS) PURE;
    STDMETHOD(DoAlter)(THIS) PURE;
    STDMETHOD(CancelAlter)(THIS) PURE;

	// Post-6.0
    STDMETHOD(GetDescription)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetDescription)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLEAlertSystem
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

	//*** properties
	STDMETHOD(GetFailSafeOperator)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
	STDMETHOD(SetFailSafeOperator)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetNotificationMethod)(THIS_ SQLOLE_NOTIFY_TYPE *pRetVal) PURE;
    STDMETHOD(SetNotificationMethod)(THIS_ SQLOLE_NOTIFY_TYPE NewValue) PURE;
	STDMETHOD(GetForwardingServer)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
	STDMETHOD(SetForwardingServer)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetForwardingSeverity)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetForwardingSeverity)(THIS_ long NewValue) PURE;
	STDMETHOD(GetPagerToTemplate)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
	STDMETHOD(SetPagerToTemplate)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
	STDMETHOD(GetPagerCCTemplate)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
	STDMETHOD(SetPagerCCTemplate)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
	STDMETHOD(GetPagerSubjectTemplate)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
	STDMETHOD(SetPagerSubjectTemplate)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetPagerSendSubjectOnly)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetPagerSendSubjectOnly)(THIS_ BOOL NewValue) PURE;

	//*** methods
	STDMETHOD(Refresh)(THIS) PURE;
    STDMETHOD(BeginAlter)(THIS) PURE;
    STDMETHOD(DoAlter)(THIS) PURE;
    STDMETHOD(CancelAlter)(THIS) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLEServerGroup
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

	//*** properties
    STDMETHOD(GetName)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetName)(THIS_ SQLOLE_LPCSTR NewValue) PURE;

	//*** Collection Properties
    STDMETHOD(GetRegisteredServers)(THIS_ LPSQLOLEREGISTEREDSERVERS *ppRegisteredServers) PURE;
    STDMETHOD(GetRegisteredServerByName)(THIS_ SQLOLE_LPCSTR szName, LPSQLOLEREGISTEREDSERVER *ppRegisteredServer) PURE;
    STDMETHOD(GetRegisteredServerByOrd)(THIS_ long lOrdinal, LPSQLOLEREGISTEREDSERVER *ppRegisteredServer) PURE;
    STDMETHOD(RemoveRegisteredServerByName)(THIS_ SQLOLE_LPCSTR szName) PURE;
    STDMETHOD(RemoveRegisteredServerByOrd)(THIS_ long lOrdinal) PURE;
    STDMETHOD(AddRegisteredServer)(THIS_ LPSQLOLEREGISTEREDSERVER pRegisteredServer) PURE;
    STDMETHOD(GetRegisteredServerCount)(THIS_ LPLONG plCount) PURE;

	//*** methods
    STDMETHOD(Remove)(THIS) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLERegisteredServer
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

	//*** properties
    STDMETHOD(GetName)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetName)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetLogin)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetLogin)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetPassword)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetPassword)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetUseTrustedConnection)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetUseTrustedConnection)(THIS_ BOOL NewValue) PURE;
    STDMETHOD(GetVersionMajor)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetVersionMinor)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(GetSaLogin)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(GetPersistFlags)(THIS_ LPLONG pRetVal) PURE;
    STDMETHOD(SetPersistFlags)(THIS_ LONG NewValue) PURE;

	//*** methods
    STDMETHOD(Remove)(THIS) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLETransfer
DECLARE_INTERFACE_(INTERFACE, ISQLOLEStdObject)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** SQLOLE standard object properties.
    STDMETHOD(GetApplication)(THIS_ LPSQLOLEAPPLICATION *ppApp) PURE;
    STDMETHOD(GetParent)(THIS_ LPSQLOLESTDOBJECT *ppParent) PURE;
    STDMETHOD(GetTypeOf)(THIS_ SQLOLE_OBJECT_TYPE *pRetVal) PURE;
    STDMETHOD(GetUserData)(THIS_ LPVOID *pRetVal) PURE;
    STDMETHOD(SetUserData)(THIS_ LPVOID lpvNewValue) PURE;

	//*** properties
    STDMETHOD(GetDestServer)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetDestServer)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetDestLogin)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetDestLogin)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetDestPassword)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetDestPassword)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetDestDatabase)(THIS_ SQLOLE_LPBSTR pRetVal) PURE;
    STDMETHOD(SetDestDatabase)(THIS_ SQLOLE_LPCSTR NewValue) PURE;
    STDMETHOD(GetDestUseTrustedConnection)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetDestUseTrustedConnection)(THIS_ BOOL NewValue) PURE;
    STDMETHOD(GetCopyData)(THIS_ SQLOLE_COPYDATA_TYPE *pRetVal) PURE;
    STDMETHOD(SetCopyData)(THIS_ SQLOLE_COPYDATA_TYPE NewValue) PURE;
    STDMETHOD(GetCopySchema)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetCopySchema)(THIS_ BOOL NewValue) PURE;
    STDMETHOD(GetCopyAllObjects)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetCopyAllObjects)(THIS_ BOOL NewValue) PURE;
    STDMETHOD(GetCopyAllTables)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetCopyAllTables)(THIS_ BOOL NewValue) PURE;
    STDMETHOD(GetCopyAllViews)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetCopyAllViews)(THIS_ BOOL NewValue) PURE;
    STDMETHOD(GetCopyAllStoredProcedures)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetCopyAllStoredProcedures)(THIS_ BOOL NewValue) PURE;
    STDMETHOD(GetCopyAllUserDefinedDatatypes)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetCopyAllUserDefinedDatatypes)(THIS_ BOOL NewValue) PURE;
    STDMETHOD(GetCopyAllRules)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetCopyAllRules)(THIS_ BOOL NewValue) PURE;
    STDMETHOD(GetCopyAllDefaults)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetCopyAllDefaults)(THIS_ BOOL NewValue) PURE;
    STDMETHOD(GetCopyAllTriggers)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetCopyAllTriggers)(THIS_ BOOL NewValue) PURE;
    STDMETHOD(GetIncludeDependencies)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetIncludeDependencies)(THIS_ BOOL NewValue) PURE;
    STDMETHOD(GetIncludeUsers)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetIncludeUsers)(THIS_ BOOL NewValue) PURE;
    STDMETHOD(GetIncludeGroups)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetIncludeGroups)(THIS_ BOOL NewValue) PURE;
    STDMETHOD(GetIncludeLogins)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetIncludeLogins)(THIS_ BOOL NewValue) PURE;
    STDMETHOD(GetDropDestObjectsFirst)(THIS_ LPBOOL pRetVal) PURE;
    STDMETHOD(SetDropDestObjectsFirst)(THIS_ BOOL NewValue) PURE;
    STDMETHOD(GetScriptType)(THIS_ SQLOLE_SCRIPT_TYPE * pRetVal) PURE;
    STDMETHOD(SetScriptType)(THIS_ SQLOLE_SCRIPT_TYPE NewValue) PURE;

    //*** methods
	STDMETHOD(AddObjectByName)(THIS_ SQLOLE_LPCSTR ObjectName, SQLOLE_OBJECT_TYPE ObjectType) PURE;
	STDMETHOD(AddObject)(THIS_ LPSQLOLEDBOBJECT DBObject) PURE;
    STDMETHOD(ListObjectNames)(THIS_ SQLOLE_OBJECT_TYPE ObjectType, LPSQLOLENAMELIST * ppList) PURE;
	STDMETHOD(Abort)(THIS) PURE;
};

/////////////////////////////////////////////////////////////////////////////
//		SQLOLE Connection Point Sink Interfaces
/////////////////////////////////////////////////////////////////////////////

#undef INTERFACE
#define INTERFACE ISQLOLETransferSink
DECLARE_INTERFACE_(INTERFACE, IUnknown)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** Sink properties and methods.
    STDMETHOD(StatusMessage)(THIS_ SQLOLE_LPCSTR szMessage) PURE;
    STDMETHOD(PercentCompleteAtStep)(THIS_ SQLOLE_LPCSTR szMessage, long Percent) PURE;
    STDMETHOD(ScriptTransferPercentComplete)(THIS_ SQLOLE_LPCSTR szMessage, long Percent) PURE;
    STDMETHOD(TransferPercentComplete)(THIS_ SQLOLE_LPCSTR szMessage, long Percent) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLEServerSink
DECLARE_INTERFACE_(INTERFACE, IUnknown)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** Sink properties and methods.
    STDMETHOD(QueryTimeout)(THIS_ SQLOLE_LPCSTR Message, LPBOOL Continue) PURE;
    STDMETHOD(ServerMessage)(THIS_ long Severity, long MessageNumber, long MessageState, SQLOLE_LPCSTR Message) PURE;
    STDMETHOD(ConnectionBroken)(THIS_ SQLOLE_LPCSTR Message, LPBOOL Retry) PURE;
    STDMETHOD(RemoteLoginFailed)(THIS_ long Severity, long MessageNumber, long MessageState, SQLOLE_LPCSTR Message) PURE;
	STDMETHOD(CommandSent)(THIS_ SQLOLE_LPCSTR szSQL) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLEBackupSink
DECLARE_INTERFACE_(INTERFACE, IUnknown)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** Sink properties and methods.
    STDMETHOD(PercentComplete)(THIS_ SQLOLE_LPCSTR Message, long Percent) PURE;
    STDMETHOD(NextVolume)(THIS_ SQLOLE_LPCSTR Message) PURE;
    STDMETHOD(DumpComplete)(THIS_ SQLOLE_LPCSTR Message) PURE;
};

#undef INTERFACE
#define INTERFACE ISQLOLEBulkCopySink
DECLARE_INTERFACE_(INTERFACE, IUnknown)
{
   //*** IUnknown methods
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	//*** Sink properties and methods.
    STDMETHOD(RowsCopied)(THIS_ SQLOLE_LPCSTR Message, long Rows) PURE;
    STDMETHOD(BatchImported)(THIS_ SQLOLE_LPCSTR Message) PURE;
};

#ifdef _SQLOLE_INTERNAL_
#endif

#endif	// !_SQLOLE_ODL_
#endif	// _SQLOLE_H_
