/************************************************************************ 
**	D B D A O I N T. H													*
**																		*
************************************************************************* 
** Copyright (C) 1995 by Microsoft Corporation		 					*
**		   All Rights Reserved					 						*
************************************************************************/ 
/*
 DBDAOINT.H
 OLE DAO Interface.  
This is a part of the Microsoft Data Access Objects SDK library.
See the dao*.hlp files for detailed information regarding the
Microsoft Data Access Objects SDK product.
 
*/
#ifndef _DBDAOINT_H_
#define _DBDAOINT_H_

#ifndef _INC_TCHAR
#include <tchar.h>
#endif

// Constants

typedef enum RecordsetTypeEnum {
    dbOpenTable = 1,
    dbOpenDynaset = 2,
    dbOpenSnapshot = 4,
    dbOpenForwardOnly = 8,
    dbOpenDynamic = 16
} RecordsetTypeEnum;

typedef enum EditModeEnum {
    dbEditNone = 0,
    dbEditInProgress = 1,
    dbEditAdd = 2,
    dbEditChanged = 4,
    dbEditDeleted = 8,
    dbEditNew = 16
} EditModeEnum;

typedef enum RecordsetOptionEnum {
    dbDenyWrite = 1,
    dbDenyRead = 2,
    dbReadOnly = 4,
    dbAppendOnly = 8,
    dbInconsistent = 16,
    dbConsistent = 32,
    dbSQLPassThrough = 64,
    dbFailOnError = 128,
    dbForwardOnly = 256,
    dbSeeChanges = 512,
    dbRunAsync = 1024,
    dbExecDirect = 2048
} RecordsetOptionEnum;

typedef enum LockTypeEnum {
    dbPessimistic = 2,
    dbOptimistic = 3,
    dbOptimisticValue = 1,
    dbOptimisticBatch = 5
} LockTypeEnum;

typedef enum UpdateCriteriaEnum {
    dbCriteriaKey = 1,
    dbCriteriaModValues = 2,
    dbCriteriaAllCols = 4,
    dbCriteriaTimestamp = 8,
    dbCriteriaDeleteInsert = 16,
    dbCriteriaUpdate = 32
} UpdateCriteriaEnum;

typedef enum FieldAttributeEnum {
    dbFixedField = 1,
    dbVariableField = 2,
    dbAutoIncrField = 16,
    dbUpdatableField = 32,
    dbSystemField = 8192,
    dbHyperlinkField = 32768,
    dbDescending = 1
} FieldAttributeEnum;

typedef enum DataTypeEnum {
    dbBoolean = 1,
    dbByte = 2,
    dbInteger = 3,
    dbLong = 4,
    dbCurrency = 5,
    dbSingle = 6,
    dbDouble = 7,
    dbDate = 8,
    dbBinary = 9,
    dbText = 10,
    dbLongBinary = 11,
    dbMemo = 12,
    dbGUID = 15,
    dbBigInt = 16,
    dbVarBinary = 17,
    dbChar = 18,
    dbNumeric = 19,
    dbDecimal = 20,
    dbFloat = 21,
    dbTime = 22,
    dbTimeStamp = 23
} DataTypeEnum;

typedef enum RelationAttributeEnum {
    dbRelationUnique = 1,
    dbRelationDontEnforce = 2,
    dbRelationInherited = 4,
    dbRelationUpdateCascade = 256,
    dbRelationDeleteCascade = 4096,
    dbRelationLeft = 16777216,
    dbRelationRight = 33554432
} RelationAttributeEnum;

typedef enum TableDefAttributeEnum {
    dbAttachExclusive = 65536,
    dbAttachSavePWD = 131072,
    dbSystemObject = -2147483646,
    dbAttachedTable = 1073741824,
    dbAttachedODBC = 536870912,
    dbHiddenObject = 1
} TableDefAttributeEnum;

typedef enum QueryDefTypeEnum {
    dbQSelect = 0,
    dbQProcedure = 224,
    dbQAction = 240,
    dbQCrosstab = 16,
    dbQDelete = 32,
    dbQUpdate = 48,
    dbQAppend = 64,
    dbQMakeTable = 80,
    dbQDDL = 96,
    dbQSQLPassThrough = 112,
    dbQSetOperation = 128,
    dbQSPTBulk = 144,
    dbQCompound = 160
} QueryDefTypeEnum;

typedef enum QueryDefStateEnum {
    dbQPrepare = 1,
    dbQUnprepare = 2
} QueryDefStateEnum;

typedef enum DatabaseTypeEnum {
    dbVersion10 = 1,
    dbEncrypt = 2,
    dbDecrypt = 4,
    dbVersion11 = 8,
    dbVersion20 = 16,
    dbVersion30 = 32
} DatabaseTypeEnum;

typedef enum CollatingOrderEnum {
    dbSortNeutral = 1024,
    dbSortArabic = 1025,
    dbSortCyrillic = 1049,
    dbSortCzech = 1029,
    dbSortDutch = 1043,
    dbSortGeneral = 1033,
    dbSortGreek = 1032,
    dbSortHebrew = 1037,
    dbSortHungarian = 1038,
    dbSortIcelandic = 1039,
    dbSortNorwdan = 1030,
    dbSortPDXIntl = 1033,
    dbSortPDXNor = 1030,
    dbSortPDXSwe = 1053,
    dbSortPolish = 1045,
    dbSortSpanish = 1034,
    dbSortSwedFin = 1053,
    dbSortTurkish = 1055,
    dbSortJapanese = 1041,
    dbSortChineseSimplified = 2052,
    dbSortChineseTraditional = 1028,
    dbSortKorean = 1042,
    dbSortThai = 1054,
    dbSortSlovenian = 1060,
    dbSortUndefined = -1
} CollatingOrderEnum;

typedef enum IdleEnum {
    dbFreeLocks = 1,
    dbRefreshCache = 8
} IdleEnum;

typedef enum PermissionEnum {
    dbSecNoAccess = 0,
    dbSecFullAccess = 1048575,
    dbSecDelete = 65536,
    dbSecReadSec = 131072,
    dbSecWriteSec = 262144,
    dbSecWriteOwner = 524288,
    dbSecDBCreate = 1,
    dbSecDBOpen = 2,
    dbSecDBExclusive = 4,
    dbSecDBAdmin = 8,
    dbSecCreate = 1,
    dbSecReadDef = 4,
    dbSecWriteDef = 65548,
    dbSecRetrieveData = 20,
    dbSecInsertData = 32,
    dbSecReplaceData = 64,
    dbSecDeleteData = 128
} PermissionEnum;

typedef enum SynchronizeTypeEnum {
    dbRepExportChanges = 1,
    dbRepImportChanges = 2,
    dbRepImpExpChanges = 4,
    dbRepSyncInternet = 16
} SynchronizeTypeEnum;

typedef enum ReplicaTypeEnum {
    dbRepMakeReadOnly = 2,
    dbRepMakePartial = 1
} ReplicaTypeEnum;

typedef enum WorkspaceTypeEnum {
    dbUseODBC = 1,
    dbUseJet = 2
} WorkspaceTypeEnum;

typedef enum CursorDriverEnum {
    dbUseDefaultCursor = -1,
    dbUseODBCCursor = 1,
    dbUseServerCursor = 2,
    dbUseClientBatchCursor = 3,
    dbUseNoCursor = 4
} CursorDriverEnum;

typedef enum DriverPromptEnum {
    dbDriverPrompt = 2,
    dbDriverNoPrompt = 1,
    dbDriverComplete = 0,
    dbDriverCompleteRequired = 3
} DriverPromptEnum;

typedef enum SetOptionEnum {
    dbPageTimeout = 6,
    dbLockRetry = 57,
    dbMaxBufferSize = 8,
    dbUserCommitSync = 58,
    dbImplicitCommitSync = 59,
    dbExclusiveAsyncDelay = 60,
    dbSharedAsyncDelay = 61,
    dbMaxLocksPerFile = 62,
    dbLockDelay = 63,
    dbRecycleLVs = 65,
    dbFlushTransactionTimeout = 66
} SetOptionEnum;

typedef enum ParameterDirectionEnum {
    dbParamInput = 1,
    dbParamOutput = 2,
    dbParamInputOutput = 3,
    dbParamReturnValue = 4
} ParameterDirectionEnum;

typedef enum UpdateTypeEnum {
    dbUpdateBatch = 4,
    dbUpdateRegular = 1,
    dbUpdateCurrentRecord = 2
} UpdateTypeEnum;

typedef enum RecordStatusEnum {
    dbRecordUnmodified = 0,
    dbRecordModified = 1,
    dbRecordNew = 2,
    dbRecordDeleted = 3,
    dbRecordDBDeleted = 4
} RecordStatusEnum;

typedef enum CommitTransOptionsEnum {
    dbForceOSFlush = 1
} CommitTransOptionsEnum;

typedef enum _DAOSuppHelp {
    LogMessages = 0,
    KeepLocal = 0,
    Replicable = 0,
    ReplicableBool = 0,
    V1xNullBehavior = 0
} _DAOSuppHelp;




	const TCHAR dbLangArabic[] = _T(";LANGID=0x0401;CP=1256;COUNTRY=0";);
	const TCHAR dbLangCzech[] = _T(";LANGID=0x0405;CP=1250;COUNTRY=0";);
	const TCHAR dbLangDutch[] = _T(";LANGID=0x0413;CP=1252;COUNTRY=0";);
	const TCHAR dbLangGeneral[] = _T(";LANGID=0x0409;CP=1252;COUNTRY=0";);
	const TCHAR dbLangGreek[] = _T(";LANGID=0x0408;CP=1253;COUNTRY=0";);
	const TCHAR dbLangHebrew[] = _T(";LANGID=0x040D;CP=1255;COUNTRY=0";);
	const TCHAR dbLangHungarian[] = _T(";LANGID=0x040E;CP=1250;COUNTRY=0";);
	const TCHAR dbLangIcelandic[] = _T(";LANGID=0x040F;CP=1252;COUNTRY=0";);
	const TCHAR dbLangNordic[] = _T(";LANGID=0x041D;CP=1252;COUNTRY=0";);
	const TCHAR dbLangNorwDan[] = _T(";LANGID=0x0414;CP=1252;COUNTRY=0";);
	const TCHAR dbLangPolish[] = _T(";LANGID=0x0415;CP=1250;COUNTRY=0";);
	const TCHAR dbLangCyrillic[] = _T(";LANGID=0x0419;CP=1251;COUNTRY=0";);
	const TCHAR dbLangSpanish[] = _T(";LANGID=0x040A;CP=1252;COUNTRY=0";);
	const TCHAR dbLangSwedFin[] = _T(";LANGID=0x040B;CP=1252;COUNTRY=0";);
	const TCHAR dbLangTurkish[] = _T(";LANGID=0x041F;CP=1254;COUNTRY=0";);
	const TCHAR dbLangJapanese[] = _T(";LANGID=0x0411;CP=932;COUNTRY=0";);
	const TCHAR dbLangChineseSimplified[] = _T(";LANGID=0x0804;CP=936;COUNTRY=0";);
	const TCHAR dbLangChineseTraditional[] = _T(";LANGID=0x0404;CP=950;COUNTRY=0";);
	const TCHAR dbLangKorean[] = _T(";LANGID=0x0412;CP=949;COUNTRY=0";);
	const TCHAR dbLangThai[] = _T(";LANGID=0x041E;CP=874;COUNTRY=0";);
	const TCHAR dbLangSlovenian[] = _T(";LANGID=0x0424;CP=1250;COUNTRY=0";);
// Forwards
#define DAODBEngine _DAODBEngine
interface _DAODBEngine;
interface DAOError;
interface DAOErrors;
interface DAOProperty;
interface DAOProperties;
interface DAOWorkspace;
interface DAOWorkspaces;
interface DAOConnection;
interface DAOConnections;
interface DAODatabase;
interface DAODatabases;
#define DAOTableDef _DAOTableDef
interface _DAOTableDef;
interface DAOTableDefs;
#define DAOQueryDef _DAOQueryDef
interface _DAOQueryDef;
interface DAOQueryDefs;
interface DAORecordset;
interface DAORecordsets;
#define DAOField _DAOField
interface _DAOField;
interface DAOFields;
#define DAOIndex _DAOIndex
interface _DAOIndex;
interface DAOIndexes;
interface DAOParameter;
interface DAOParameters;
#define DAOUser _DAOUser
interface _DAOUser;
interface DAOUsers;
#define DAOGroup _DAOGroup
interface _DAOGroup;
interface DAOGroups;
#define DAORelation _DAORelation
interface _DAORelation;
interface DAORelations;
interface DAOContainer;
interface DAOContainers;
interface DAODocument;
interface DAODocuments;


// Interface: _DAOCollection
#undef INTERFACE
#define INTERFACE _DAOCollection
DECLARE_INTERFACE_(_DAOCollection, IDispatch)
	{
	STDMETHOD(get_Count)						 (THIS_ short FAR* c) PURE;
	STDMETHOD(_NewEnum)							 (THIS_ IUnknown * FAR* ppunk) PURE;
	STDMETHOD(Refresh)							 (THIS) PURE;
	};

// Interface: _DAODynaCollection
#undef INTERFACE
#define INTERFACE _DAODynaCollection
DECLARE_INTERFACE_(_DAODynaCollection, _DAOCollection)
	{
	STDMETHOD(Append)							 (THIS_ IDispatch * Object) PURE;
	STDMETHOD(Delete)							 (THIS_ BSTR Name) PURE;
	};

// Interface: _DAO
#undef INTERFACE
#define INTERFACE _DAO
DECLARE_INTERFACE_(_DAO, IDispatch)
	{
	STDMETHOD(get_Properties)					 (THIS_ DAOProperties FAR* FAR* ppprops) PURE;
	};

// Interface: _DAODBEngine
#undef INTERFACE
#define INTERFACE _DAODBEngine
DECLARE_INTERFACE_(_DAODBEngine, _DAO)
	{
	STDMETHOD(get_Version)						 (THIS_ BSTR FAR* pbstr) PURE;
	STDMETHOD(get_IniPath)						 (THIS_ BSTR FAR* pbstr) PURE;
	STDMETHOD(put_IniPath)						 (THIS_ BSTR path) PURE;
	STDMETHOD(put_DefaultUser)					 (THIS_ BSTR user) PURE;
	STDMETHOD(put_DefaultPassword)				 (THIS_ BSTR pw) PURE;
	STDMETHOD(get_LoginTimeout)					 (THIS_ short FAR* ps) PURE;
	STDMETHOD(put_LoginTimeout)					 (THIS_ short Timeout) PURE;
	STDMETHOD(get_Workspaces)					 (THIS_ DAOWorkspaces FAR* FAR* ppworks) PURE;
	STDMETHOD(get_Errors)						 (THIS_ DAOErrors FAR* FAR* pperrs) PURE;
	STDMETHOD(Idle)								 (THIS_ VARIANT Action) PURE;
	STDMETHOD(CompactDatabase)					 (THIS_ BSTR SrcName, BSTR DstName, VARIANT DstLocale, VARIANT Options, VARIANT SrcLocale) PURE;
	STDMETHOD(RepairDatabase)					 (THIS_ BSTR Name) PURE;
	STDMETHOD(RegisterDatabase)					 (THIS_ BSTR Dsn, BSTR Driver, VARIANT_BOOL Silent, BSTR Attributes) PURE;
	STDMETHOD(_30_CreateWorkspace)				 (THIS_ BSTR Name, BSTR UserName, BSTR Password, DAOWorkspace FAR* FAR* ppwrk) PURE;
	STDMETHOD(OpenDatabase)						 (THIS_ BSTR Name, VARIANT Options, VARIANT ReadOnly, VARIANT Connect, DAODatabase FAR* FAR* ppdb) PURE;
	STDMETHOD(CreateDatabase)					 (THIS_ BSTR Name, BSTR Locale, VARIANT Option, DAODatabase FAR* FAR* ppdb) PURE;
	STDMETHOD(FreeLocks)						 (THIS) PURE;
	STDMETHOD(BeginTrans)						 (THIS) PURE;
	STDMETHOD(CommitTrans)						 (THIS_ long Option) PURE;
	STDMETHOD(Rollback)							 (THIS) PURE;
	STDMETHOD(SetDefaultWorkspace)				 (THIS_ BSTR Name, BSTR Password) PURE;
	STDMETHOD(SetDataAccessOption)				 (THIS_ short Option, VARIANT Value) PURE;
	STDMETHOD(ISAMStats)						 (THIS_ long StatNum, VARIANT Reset, long FAR* pl) PURE;
	STDMETHOD(get_SystemDB)						 (THIS_ BSTR FAR* pbstr) PURE;
	STDMETHOD(put_SystemDB)						 (THIS_ BSTR SystemDBPath) PURE;
	STDMETHOD(CreateWorkspace)					 (THIS_ BSTR Name, BSTR UserName, BSTR Password, VARIANT UseType, DAOWorkspace FAR* FAR* ppwrk) PURE;
	STDMETHOD(OpenConnection)					 (THIS_ BSTR Name, VARIANT Options, VARIANT ReadOnly, VARIANT Connect, DAOConnection FAR* FAR* ppconn) PURE;
	STDMETHOD(get_DefaultType)					 (THIS_ long FAR* Option) PURE;
	STDMETHOD(put_DefaultType)					 (THIS_ long Option) PURE;
	STDMETHOD(SetOption)						 (THIS_ long Option, VARIANT Value) PURE;
	};

// Interface: DAOError
#undef INTERFACE
#define INTERFACE DAOError
DECLARE_INTERFACE_(DAOError, IDispatch)
	{
	STDMETHOD(get_Number)						 (THIS_ long FAR* pl) PURE;
	STDMETHOD(get_Source)						 (THIS_ BSTR FAR* pbstr) PURE;
	STDMETHOD(get_Description)					 (THIS_ BSTR FAR* pbstr) PURE;
	STDMETHOD(get_HelpFile)						 (THIS_ BSTR FAR* pbstr) PURE;
	STDMETHOD(get_HelpContext)					 (THIS_ long FAR* pl) PURE;
	};

// Interface: DAOErrors
#undef INTERFACE
#define INTERFACE DAOErrors
DECLARE_INTERFACE_(DAOErrors, _DAOCollection)
	{
	STDMETHOD(get_Item)							 (THIS_ VARIANT index, DAOError FAR* FAR* pperr) PURE;
	};

// Interface: DAOWorkspace
#undef INTERFACE
#define INTERFACE DAOWorkspace
DECLARE_INTERFACE_(DAOWorkspace, _DAO)
	{
	STDMETHOD(get_Name)							 (THIS_ BSTR FAR* pbstr) PURE;
	STDMETHOD(put_Name)							 (THIS_ BSTR Name) PURE;
	STDMETHOD(get_UserName)						 (THIS_ BSTR FAR* pbstr) PURE;
	STDMETHOD(put__30_UserName)					 (THIS_ BSTR UserName) PURE;
	STDMETHOD(put__30_Password)					 (THIS_ BSTR Password) PURE;
	STDMETHOD(get_IsolateODBCTrans)				 (THIS_ short FAR* ps) PURE;
	STDMETHOD(put_IsolateODBCTrans)				 (THIS_ short s) PURE;
	STDMETHOD(get_Databases)					 (THIS_ DAODatabases FAR* FAR* ppdbs) PURE;
	STDMETHOD(get_Users)						 (THIS_ DAOUsers FAR* FAR* ppusrs) PURE;
	STDMETHOD(get_Groups)						 (THIS_ DAOGroups FAR* FAR* ppgrps) PURE;
	STDMETHOD(BeginTrans)						 (THIS) PURE;
	STDMETHOD(CommitTrans)						 (THIS_ long Options) PURE;
	STDMETHOD(Close)							 (THIS) PURE;
	STDMETHOD(Rollback)							 (THIS) PURE;
	STDMETHOD(OpenDatabase)						 (THIS_ BSTR Name, VARIANT Options, VARIANT ReadOnly, VARIANT Connect, DAODatabase FAR* FAR* ppdb) PURE;
	STDMETHOD(CreateDatabase)					 (THIS_ BSTR Name, BSTR Connect, VARIANT Option, DAODatabase FAR* FAR* ppdb) PURE;
	STDMETHOD(CreateUser)						 (THIS_ VARIANT Name, VARIANT PID, VARIANT Password, DAOUser FAR* FAR* ppusr) PURE;
	STDMETHOD(CreateGroup)						 (THIS_ VARIANT Name, VARIANT PID, DAOGroup FAR* FAR* ppgrp) PURE;
	STDMETHOD(OpenConnection)					 (THIS_ BSTR Name, VARIANT Options, VARIANT ReadOnly, VARIANT Connect, DAOConnection FAR* FAR* ppconn) PURE;
	STDMETHOD(get_LoginTimeout)					 (THIS_ long FAR* pTimeout) PURE;
	STDMETHOD(put_LoginTimeout)					 (THIS_ long Timeout) PURE;
	STDMETHOD(get_DefaultCursorDriver)			 (THIS_ long FAR* pCursorType) PURE;
	STDMETHOD(put_DefaultCursorDriver)			 (THIS_ long CursorType) PURE;
	STDMETHOD(get_hEnv)							 (THIS_ long FAR* phEnv) PURE;
	STDMETHOD(get_Type)							 (THIS_ long FAR* ptype) PURE;
	STDMETHOD(get_Connections)					 (THIS_ DAOConnections FAR* FAR* ppcns) PURE;
	};

// Interface: DAOWorkspaces
#undef INTERFACE
#define INTERFACE DAOWorkspaces
DECLARE_INTERFACE_(DAOWorkspaces, _DAODynaCollection)
	{
	STDMETHOD(get_Item)							 (THIS_ VARIANT index, DAOWorkspace FAR* FAR* ppwrk) PURE;
	};

// Interface: _DAOTableDef
#undef INTERFACE
#define INTERFACE _DAOTableDef
DECLARE_INTERFACE_(_DAOTableDef, _DAO)
	{
	STDMETHOD(get_Attributes)					 (THIS_ long FAR* pl) PURE;
	STDMETHOD(put_Attributes)					 (THIS_ long Attributes) PURE;
	STDMETHOD(get_Connect)						 (THIS_ BSTR FAR* pbstr) PURE;
	STDMETHOD(put_Connect)						 (THIS_ BSTR Connection) PURE;
	STDMETHOD(get_DateCreated)					 (THIS_ VARIANT FAR* pvar) PURE;
	STDMETHOD(get_LastUpdated)					 (THIS_ VARIANT FAR* pvar) PURE;
	STDMETHOD(get_Name)							 (THIS_ BSTR FAR* pbstr) PURE;
	STDMETHOD(put_Name)							 (THIS_ BSTR Name) PURE;
	STDMETHOD(get_SourceTableName)				 (THIS_ BSTR FAR* pbstr) PURE;
	STDMETHOD(put_SourceTableName)				 (THIS_ BSTR bstr) PURE;
	STDMETHOD(get_Updatable)					 (THIS_ VARIANT_BOOL FAR* pb) PURE;
	STDMETHOD(get_ValidationText)				 (THIS_ BSTR FAR* pbstr) PURE;
	STDMETHOD(put_ValidationText)				 (THIS_ BSTR bstr) PURE;
	STDMETHOD(get_ValidationRule)				 (THIS_ BSTR FAR* pbstr) PURE;
	STDMETHOD(put_ValidationRule)				 (THIS_ BSTR bstr) PURE;
	STDMETHOD(get_RecordCount)					 (THIS_ long FAR* pl) PURE;
	STDMETHOD(get_Fields)						 (THIS_ DAOFields FAR* FAR* ppflds) PURE;
	STDMETHOD(get_Indexes)						 (THIS_ DAOIndexes FAR* FAR* ppidxs) PURE;
	STDMETHOD(OpenRecordset)					 (THIS_ VARIANT Type, VARIANT Options, DAORecordset FAR* FAR* pprst) PURE;
	STDMETHOD(RefreshLink)						 (THIS) PURE;
	STDMETHOD(CreateField)						 (THIS_ VARIANT Name, VARIANT Type, VARIANT Size, DAOField FAR* FAR* ppfld) PURE;
	STDMETHOD(CreateIndex)						 (THIS_ VARIANT Name, DAOIndex FAR* FAR* ppidx) PURE;
	STDMETHOD(CreateProperty)					 (THIS_ VARIANT Name, VARIANT Type, VARIANT Value, VARIANT DDL, DAOProperty FAR* FAR* pprp) PURE;
	STDMETHOD(get_ConflictTable)				 (THIS_ BSTR FAR* pbstr) PURE;
	STDMETHOD(get_ReplicaFilter)				 (THIS_ VARIANT FAR* pFilter) PURE;
	STDMETHOD(put_ReplicaFilter)				 (THIS_ VARIANT Filter) PURE;
	};

// Interface: DAOTableDefs
#undef INTERFACE
#define INTERFACE DAOTableDefs
DECLARE_INTERFACE_(DAOTableDefs, _DAODynaCollection)
	{
	STDMETHOD(get_Item)							 (THIS_ VARIANT index, DAOTableDef FAR* FAR* pptdf) PURE;
	};

// Interface: DAODatabase
#undef INTERFACE
#define INTERFACE DAODatabase
DECLARE_INTERFACE_(DAODatabase, _DAO)
	{
	STDMETHOD(get_CollatingOrder)				 (THIS_ long FAR* pl) PURE;
	STDMETHOD(get_Connect)						 (THIS_ BSTR FAR* pbstr) PURE;
	STDMETHOD(get_Name)							 (THIS_ BSTR FAR* pbstr) PURE;
	STDMETHOD(get_QueryTimeout)					 (THIS_ short FAR* ps) PURE;
	STDMETHOD(put_QueryTimeout)					 (THIS_ short Timeout) PURE;
	STDMETHOD(get_Transactions)					 (THIS_ VARIANT_BOOL FAR* pb) PURE;
	STDMETHOD(get_Updatable)					 (THIS_ VARIANT_BOOL FAR* pb) PURE;
	STDMETHOD(get_Version)						 (THIS_ BSTR FAR* pbstr) PURE;
	STDMETHOD(get_RecordsAffected)				 (THIS_ long FAR* pl) PURE;
	STDMETHOD(get_TableDefs)					 (THIS_ DAOTableDefs FAR* FAR* pptdfs) PURE;
	STDMETHOD(get_QueryDefs)					 (THIS_ DAOQueryDefs FAR* FAR* ppqdfs) PURE;
	STDMETHOD(get_Relations)					 (THIS_ DAORelations FAR* FAR* pprls) PURE;
	STDMETHOD(get_Containers)					 (THIS_ DAOContainers FAR* FAR* ppctns) PURE;
	STDMETHOD(get_Recordsets)					 (THIS_ DAORecordsets FAR* FAR* pprsts) PURE;
	STDMETHOD(Close)							 (THIS) PURE;
	STDMETHOD(Execute)							 (THIS_ BSTR Query, VARIANT Options) PURE;
	STDMETHOD(_30_OpenRecordset)				 (THIS_ BSTR Name, VARIANT Type, VARIANT Options, DAORecordset FAR* FAR* pprst) PURE;
	STDMETHOD(CreateProperty)					 (THIS_ VARIANT Name, VARIANT Type, VARIANT Value, VARIANT DDL, DAOProperty FAR* FAR* pprp) PURE;
	STDMETHOD(CreateRelation)					 (THIS_ VARIANT Name, VARIANT Table, VARIANT ForeignTable, VARIANT Attributes, DAORelation FAR* FAR* pprel) PURE;
	STDMETHOD(CreateTableDef)					 (THIS_ VARIANT Name, VARIANT Attributes, VARIANT SourceTablename, VARIANT Connect, DAOTableDef FAR* FAR* pptdf) PURE;
	STDMETHOD(BeginTrans)						 (THIS) PURE;
	STDMETHOD(CommitTrans)						 (THIS_ long Options) PURE;
	STDMETHOD(Rollback)							 (THIS) PURE;
	STDMETHOD(CreateDynaset)					 (THIS_ BSTR Name, VARIANT Options, VARIANT Inconsistent, DAORecordset FAR* FAR* pprst) PURE;
	STDMETHOD(CreateQueryDef)					 (THIS_ VARIANT Name, VARIANT SQLText, DAOQueryDef FAR* FAR* ppqdf) PURE;
	STDMETHOD(CreateSnapshot)					 (THIS_ BSTR Source, VARIANT Options, DAORecordset FAR* FAR* pprst) PURE;
	STDMETHOD(DeleteQueryDef)					 (THIS_ BSTR Name) PURE;
	STDMETHOD(ExecuteSQL)						 (THIS_ BSTR SQL, long FAR* pl) PURE;
	STDMETHOD(ListFields)						 (THIS_ BSTR Name, DAORecordset FAR* FAR* pprst) PURE;
	STDMETHOD(ListTables)						 (THIS_ DAORecordset FAR* FAR* pprst) PURE;
	STDMETHOD(OpenQueryDef)						 (THIS_ BSTR Name, DAOQueryDef FAR* FAR* ppqdf) PURE;
	STDMETHOD(OpenTable)						 (THIS_ BSTR Name, VARIANT Options, DAORecordset FAR* FAR* pprst) PURE;
	STDMETHOD(get_ReplicaID)					 (THIS_ BSTR FAR* pbstr) PURE;
	STDMETHOD(get_DesignMasterID)				 (THIS_ BSTR FAR* pbstr) PURE;
	STDMETHOD(put_DesignMasterID)				 (THIS_ BSTR MasterID) PURE;
	STDMETHOD(Synchronize)						 (THIS_ BSTR DbPathName, VARIANT ExchangeType) PURE;
	STDMETHOD(MakeReplica)						 (THIS_ BSTR PathName, BSTR Description, VARIANT Options) PURE;
	STDMETHOD(put_Connect)						 (THIS_ BSTR ODBCConnnect) PURE;
	STDMETHOD(NewPassword)						 (THIS_ BSTR bstrOld, BSTR bstrNew) PURE;
	STDMETHOD(OpenRecordset)					 (THIS_ BSTR Name, VARIANT Type, VARIANT Options, VARIANT LockEdit, DAORecordset FAR* FAR* pprst) PURE;
	STDMETHOD(get_Connection)					 (THIS_ DAOConnection FAR* FAR* ppCn) PURE;
	STDMETHOD(PopulatePartial)					 (THIS_ BSTR DbPathName) PURE;
	};

// Interface: DAODatabases
#undef INTERFACE
#define INTERFACE DAODatabases
DECLARE_INTERFACE_(DAODatabases, _DAOCollection)
	{
	STDMETHOD(get_Item)							 (THIS_ VARIANT index, DAODatabase FAR* FAR* ppdb) PURE;
	};

// Interface: _DAOQueryDef
#undef INTERFACE
#define INTERFACE _DAOQueryDef
DECLARE_INTERFACE_(_DAOQueryDef, _DAO)
	{
	STDMETHOD(get_DateCreated)					 (THIS_ VARIANT FAR* pvar) PURE;
	STDMETHOD(get_LastUpdated)					 (THIS_ VARIANT FAR* pvar) PURE;
	STDMETHOD(get_Name)							 (THIS_ BSTR FAR* pbstr) PURE;
	STDMETHOD(put_Name)							 (THIS_ BSTR bstr) PURE;
	STDMETHOD(get_ODBCTimeout)					 (THIS_ short FAR* ps) PURE;
	STDMETHOD(put_ODBCTimeout)					 (THIS_ short timeout) PURE;
	STDMETHOD(get_Type)							 (THIS_ short FAR* pi) PURE;
	STDMETHOD(get_SQL)							 (THIS_ BSTR FAR* pbstr) PURE;
	STDMETHOD(put_SQL)							 (THIS_ BSTR bstr) PURE;
	STDMETHOD(get_Updatable)					 (THIS_ VARIANT_BOOL FAR* pb) PURE;
	STDMETHOD(get_Connect)						 (THIS_ BSTR FAR* pbstr) PURE;
	STDMETHOD(put_Connect)						 (THIS_ BSTR bstr) PURE;
	STDMETHOD(get_ReturnsRecords)				 (THIS_ VARIANT_BOOL FAR* pb) PURE;
	STDMETHOD(put_ReturnsRecords)				 (THIS_ VARIANT_BOOL f) PURE;
	STDMETHOD(get_RecordsAffected)				 (THIS_ long FAR* pl) PURE;
	STDMETHOD(get_Fields)						 (THIS_ DAOFields FAR* FAR* ppflds) PURE;
	STDMETHOD(get_Parameters)					 (THIS_ DAOParameters FAR* FAR* ppprms) PURE;
	STDMETHOD(Close)							 (THIS) PURE;
	STDMETHOD(_30_OpenRecordset)				 (THIS_ VARIANT Type, VARIANT Options, DAORecordset FAR* FAR* pprst) PURE;
	STDMETHOD(_30__OpenRecordset)				 (THIS_ VARIANT Type, VARIANT Options, DAORecordset FAR* FAR* pprst) PURE;
	STDMETHOD(_Copy)							 (THIS_ DAOQueryDef FAR* FAR* ppqdf) PURE;
	STDMETHOD(Execute)							 (THIS_ VARIANT Options) PURE;
	STDMETHOD(Compare)							 (THIS_ DAOQueryDef FAR* pQdef, short FAR* lps) PURE;
	STDMETHOD(CreateDynaset)					 (THIS_ VARIANT Options, VARIANT Inconsistent, DAORecordset FAR* FAR* pprst) PURE;
	STDMETHOD(CreateSnapshot)					 (THIS_ VARIANT Options, DAORecordset FAR* FAR* pprst) PURE;
	STDMETHOD(ListParameters)					 (THIS_ DAORecordset FAR* FAR* pprst) PURE;
	STDMETHOD(CreateProperty)					 (THIS_ VARIANT Name, VARIANT Type, VARIANT Value, VARIANT DDL, DAOProperty FAR* FAR* pprp) PURE;
	STDMETHOD(OpenRecordset)					 (THIS_ VARIANT Type, VARIANT Options, VARIANT LockEdit, DAORecordset FAR* FAR* pprst) PURE;
	STDMETHOD(_OpenRecordset)					 (THIS_ VARIANT Type, VARIANT Options, VARIANT LockEdit, DAORecordset FAR* FAR* pprst) PURE;
	STDMETHOD(Cancel)							 (THIS) PURE;
	STDMETHOD(get_hStmt)						 (THIS_ long FAR* phStmt) PURE;
	STDMETHOD(get_MaxRecords)					 (THIS_ long FAR* pMxRecs) PURE;
	STDMETHOD(put_MaxRecords)					 (THIS_ long MxRecs) PURE;
	STDMETHOD(get_StillExecuting)				 (THIS_ VARIANT_BOOL FAR* pStillExec) PURE;
	STDMETHOD(get_CacheSize)					 (THIS_ long FAR* lCacheSize) PURE;
	STDMETHOD(put_CacheSize)					 (THIS_ long lCacheSize) PURE;
	STDMETHOD(get_Prepare)						 (THIS_ VARIANT FAR* pb) PURE;
	STDMETHOD(put_Prepare)						 (THIS_ VARIANT f) PURE;
	};

// Interface: DAOQueryDefs
#undef INTERFACE
#define INTERFACE DAOQueryDefs
DECLARE_INTERFACE_(DAOQueryDefs, _DAODynaCollection)
	{
	STDMETHOD(get_Item)							 (THIS_ VARIANT index, DAOQueryDef FAR* FAR* ppqdef) PURE;
	};

// Interface: DAORecordset
#undef INTERFACE
#define INTERFACE DAORecordset
DECLARE_INTERFACE_(DAORecordset, _DAO)
	{
	STDMETHOD(get_BOF)							 (THIS_ VARIANT_BOOL FAR* pb) PURE;
	STDMETHOD(get_Bookmark)						 (THIS_ SAFEARRAY FAR* FAR* ppsach) PURE;
	STDMETHOD(put_Bookmark)						 (THIS_ SAFEARRAY FAR* FAR* psach) PURE;
	STDMETHOD(get_Bookmarkable)					 (THIS_ VARIANT_BOOL FAR* pb) PURE;
	STDMETHOD(get_DateCreated)					 (THIS_ VARIANT FAR* pvar) PURE;
	STDMETHOD(get_EOF)							 (THIS_ VARIANT_BOOL FAR* pb) PURE;
	STDMETHOD(get_Filter)						 (THIS_ BSTR FAR* pbstr) PURE;
	STDMETHOD(put_Filter)						 (THIS_ BSTR Filter) PURE;
	STDMETHOD(get_Index)						 (THIS_ BSTR FAR* pbstr) PURE;
	STDMETHOD(put_Index)						 (THIS_ BSTR bstr) PURE;
	STDMETHOD(get_LastModified)					 (THIS_ SAFEARRAY FAR* FAR* ppsa) PURE;
	STDMETHOD(get_LastUpdated)					 (THIS_ VARIANT FAR* pvar) PURE;
	STDMETHOD(get_LockEdits)					 (THIS_ VARIANT_BOOL FAR* pb) PURE;
	STDMETHOD(put_LockEdits)					 (THIS_ VARIANT_BOOL Lock) PURE;
	STDMETHOD(get_Name)							 (THIS_ BSTR FAR* pbstr) PURE;
	STDMETHOD(get_NoMatch)						 (THIS_ VARIANT_BOOL FAR* pb) PURE;
	STDMETHOD(get_Sort)							 (THIS_ BSTR FAR* pbstr) PURE;
	STDMETHOD(put_Sort)							 (THIS_ BSTR Sort) PURE;
	STDMETHOD(get_Transactions)					 (THIS_ VARIANT_BOOL FAR* pb) PURE;
	STDMETHOD(get_Type)							 (THIS_ short FAR* ps) PURE;
	STDMETHOD(get_RecordCount)					 (THIS_ long FAR* pl) PURE;
	STDMETHOD(get_Updatable)					 (THIS_ VARIANT_BOOL FAR* pb) PURE;
	STDMETHOD(get_Restartable)					 (THIS_ VARIANT_BOOL FAR* pb) PURE;
	STDMETHOD(get_ValidationText)				 (THIS_ BSTR FAR* pbstr) PURE;
	STDMETHOD(get_ValidationRule)				 (THIS_ BSTR FAR* pbstr) PURE;
	STDMETHOD(get_CacheStart)					 (THIS_ SAFEARRAY FAR* FAR* ppsa) PURE;
	STDMETHOD(put_CacheStart)					 (THIS_ SAFEARRAY FAR* FAR* psa) PURE;
	STDMETHOD(get_CacheSize)					 (THIS_ long FAR* pl) PURE;
	STDMETHOD(put_CacheSize)					 (THIS_ long CacheSize) PURE;
	STDMETHOD(get_PercentPosition)				 (THIS_ float FAR* pd) PURE;
	STDMETHOD(put_PercentPosition)				 (THIS_ float Position) PURE;
	STDMETHOD(get_AbsolutePosition)				 (THIS_ long FAR* pl) PURE;
	STDMETHOD(put_AbsolutePosition)				 (THIS_ long Position) PURE;
	STDMETHOD(get_EditMode)						 (THIS_ short FAR* pi) PURE;
	STDMETHOD(get_ODBCFetchCount)				 (THIS_ long FAR* pl) PURE;
	STDMETHOD(get_ODBCFetchDelay)				 (THIS_ long FAR* pl) PURE;
	STDMETHOD(get_Parent)						 (THIS_ DAODatabase FAR* FAR* pdb) PURE;
	STDMETHOD(get_Fields)						 (THIS_ DAOFields FAR* FAR* ppflds) PURE;
	STDMETHOD(get_Indexes)						 (THIS_ DAOIndexes FAR* FAR* ppidxs) PURE;
	STDMETHOD(_30_CancelUpdate)					 (THIS) PURE;
	STDMETHOD(AddNew)							 (THIS) PURE;
	STDMETHOD(Close)							 (THIS) PURE;
	STDMETHOD(OpenRecordset)					 (THIS_ VARIANT Type, VARIANT Options, DAORecordset FAR* FAR* pprst) PURE;
	STDMETHOD(Delete)							 (THIS) PURE;
	STDMETHOD(Edit)								 (THIS) PURE;
	STDMETHOD(FindFirst)						 (THIS_ BSTR Criteria) PURE;
	STDMETHOD(FindLast)							 (THIS_ BSTR Criteria) PURE;
	STDMETHOD(FindNext)							 (THIS_ BSTR Criteria) PURE;
	STDMETHOD(FindPrevious)						 (THIS_ BSTR Criteria) PURE;
	STDMETHOD(MoveFirst)						 (THIS) PURE;
	STDMETHOD(_30_MoveLast)						 (THIS) PURE;
	STDMETHOD(MoveNext)							 (THIS) PURE;
	STDMETHOD(MovePrevious)						 (THIS) PURE;
	STDMETHOD(Seek)								 (THIS_ BSTR Comparison, VARIANT Key1, VARIANT Key2, VARIANT Key3, VARIANT Key4, VARIANT Key5, VARIANT Key6, VARIANT Key7, VARIANT Key8, VARIANT Key9, VARIANT Key10, VARIANT Key11, VARIANT Key12, VARIANT Key13) PURE;
	STDMETHOD(_30_Update)						 (THIS) PURE;
	STDMETHOD(Clone)							 (THIS_ DAORecordset FAR* FAR* pprst) PURE;
	STDMETHOD(Requery)							 (THIS_ VARIANT NewQueryDef) PURE;
	STDMETHOD(Move)								 (THIS_ long Rows, VARIANT StartBookmark) PURE;
	STDMETHOD(FillCache)						 (THIS_ VARIANT Rows, VARIANT StartBookmark) PURE;
	STDMETHOD(CreateDynaset)					 (THIS_ VARIANT Options, VARIANT Inconsistent, DAORecordset FAR* FAR* pprst) PURE;
	STDMETHOD(CreateSnapshot)					 (THIS_ VARIANT Options, DAORecordset FAR* FAR* pprst) PURE;
	STDMETHOD(CopyQueryDef)						 (THIS_ DAOQueryDef FAR* FAR* ppqdf) PURE;
	STDMETHOD(ListFields)						 (THIS_ DAORecordset FAR* FAR* pprst) PURE;
	STDMETHOD(ListIndexes)						 (THIS_ DAORecordset FAR* FAR* pprst) PURE;
	STDMETHOD(GetRows)							 (THIS_ VARIANT NumRows, VARIANT FAR* pvar) PURE;
	STDMETHOD(get_Collect)						 (THIS_ VARIANT index, VARIANT FAR* pvar) PURE;
	STDMETHOD(put_Collect)						 (THIS_ VARIANT index, VARIANT value) PURE;
	STDMETHOD(Cancel)							 (THIS) PURE;
	STDMETHOD(NextRecordset)					 (THIS_ VARIANT_BOOL FAR* pb) PURE;
	STDMETHOD(get_hStmt)						 (THIS_ long FAR* phStmt) PURE;
	STDMETHOD(get_StillExecuting)				 (THIS_ VARIANT_BOOL FAR* pStillExec) PURE;
	STDMETHOD(get_BatchSize)					 (THIS_ long FAR* pl) PURE;
	STDMETHOD(put_BatchSize)					 (THIS_ long BatchSize) PURE;
	STDMETHOD(get_BatchCollisionCount)			 (THIS_ long FAR* pl) PURE;
	STDMETHOD(get_BatchCollisions)				 (THIS_ VARIANT FAR* pvar) PURE;
	STDMETHOD(get_Connection)					 (THIS_ DAOConnection FAR* FAR* ppCn) PURE;
	STDMETHOD(putref_Connection)				 (THIS_ DAOConnection FAR* pNewCn) PURE;
	STDMETHOD(get_RecordStatus)					 (THIS_ short FAR* pi) PURE;
	STDMETHOD(get_UpdateOptions)				 (THIS_ long FAR* pl) PURE;
	STDMETHOD(put_UpdateOptions)				 (THIS_ long l) PURE;
	STDMETHOD(CancelUpdate)						 (THIS_ long UpdateType) PURE;
	STDMETHOD(Update)							 (THIS_ long UpdateType, VARIANT_BOOL Force) PURE;
	STDMETHOD(MoveLast)							 (THIS_ long Options) PURE;
	};

// Interface: DAORecordsets
#undef INTERFACE
#define INTERFACE DAORecordsets
DECLARE_INTERFACE_(DAORecordsets, _DAOCollection)
	{
	STDMETHOD(get_Item)							 (THIS_ VARIANT index, DAORecordset FAR* FAR* pprst) PURE;
	};

// Interface: _DAOField
#undef INTERFACE
#define INTERFACE _DAOField
DECLARE_INTERFACE_(_DAOField, _DAO)
	{
	STDMETHOD(get_CollatingOrder)				 (THIS_ long FAR* pl) PURE;
	STDMETHOD(get_Type)							 (THIS_ short FAR* ps) PURE;
	STDMETHOD(put_Type)							 (THIS_ short Type) PURE;
	STDMETHOD(get_Name)							 (THIS_ BSTR FAR* pbstr) PURE;
	STDMETHOD(put_Name)							 (THIS_ BSTR Name) PURE;
	STDMETHOD(get_Size)							 (THIS_ long FAR* pl) PURE;
	STDMETHOD(put_Size)							 (THIS_ long Size) PURE;
	STDMETHOD(get_SourceField)					 (THIS_ BSTR FAR* pbstr) PURE;
	STDMETHOD(get_SourceTable)					 (THIS_ BSTR FAR* pbstr) PURE;
	STDMETHOD(get_Value)						 (THIS_ VARIANT FAR* pvar) PURE;
	STDMETHOD(put_Value)						 (THIS_ VARIANT Val) PURE;
	STDMETHOD(get_Attributes)					 (THIS_ long FAR* pl) PURE;
	STDMETHOD(put_Attributes)					 (THIS_ long Attr) PURE;
	STDMETHOD(get_OrdinalPosition)				 (THIS_ short FAR* ps) PURE;
	STDMETHOD(put_OrdinalPosition)				 (THIS_ short Pos) PURE;
	STDMETHOD(get_ValidationText)				 (THIS_ BSTR FAR* pbstr) PURE;
	STDMETHOD(put_ValidationText)				 (THIS_ BSTR bstr) PURE;
	STDMETHOD(get_ValidateOnSet)				 (THIS_ VARIANT_BOOL FAR* pb) PURE;
	STDMETHOD(put_ValidateOnSet)				 (THIS_ VARIANT_BOOL Validate) PURE;
	STDMETHOD(get_ValidationRule)				 (THIS_ BSTR FAR* pbstr) PURE;
	STDMETHOD(put_ValidationRule)				 (THIS_ BSTR bstr) PURE;
	STDMETHOD(get_DefaultValue)					 (THIS_ VARIANT FAR* pvar) PURE;
	STDMETHOD(put_DefaultValue)					 (THIS_ VARIANT var) PURE;
	STDMETHOD(get_Required)						 (THIS_ VARIANT_BOOL FAR* pb) PURE;
	STDMETHOD(put_Required)						 (THIS_ VARIANT_BOOL fReq) PURE;
	STDMETHOD(get_AllowZeroLength)				 (THIS_ VARIANT_BOOL FAR* pb) PURE;
	STDMETHOD(put_AllowZeroLength)				 (THIS_ VARIANT_BOOL fAllow) PURE;
	STDMETHOD(get_DataUpdatable)				 (THIS_ VARIANT_BOOL FAR* pb) PURE;
	STDMETHOD(get_ForeignName)					 (THIS_ BSTR FAR* pbstr) PURE;
	STDMETHOD(put_ForeignName)					 (THIS_ BSTR bstr) PURE;
	STDMETHOD(AppendChunk)						 (THIS_ VARIANT Val) PURE;
	STDMETHOD(GetChunk)							 (THIS_ long Offset, long Bytes, VARIANT FAR* pvar) PURE;
	STDMETHOD(_30_FieldSize)					 (THIS_ long FAR* pl) PURE;
	STDMETHOD(CreateProperty)					 (THIS_ VARIANT Name, VARIANT Type, VARIANT Value, VARIANT DDL, DAOProperty FAR* FAR* pprp) PURE;
	STDMETHOD(get_CollectionIndex)				 (THIS_ short FAR* i) PURE;
	STDMETHOD(get_OriginalValue)				 (THIS_ VARIANT FAR* pvar) PURE;
	STDMETHOD(get_VisibleValue)					 (THIS_ VARIANT FAR* pvar) PURE;
	STDMETHOD(get_FieldSize)					 (THIS_ long FAR* pl) PURE;
	};

// Interface: DAOFields
#undef INTERFACE
#define INTERFACE DAOFields
DECLARE_INTERFACE_(DAOFields, _DAODynaCollection)
	{
	STDMETHOD(get_Item)							 (THIS_ VARIANT index, DAOField FAR* FAR* ppfld) PURE;
	};

// Interface: _DAOIndex
#undef INTERFACE
#define INTERFACE _DAOIndex
DECLARE_INTERFACE_(_DAOIndex, _DAO)
	{
	STDMETHOD(get_Name)							 (THIS_ BSTR FAR* pbstr) PURE;
	STDMETHOD(put_Name)							 (THIS_ BSTR bstr) PURE;
	STDMETHOD(get_Foreign)						 (THIS_ VARIANT_BOOL FAR* pb) PURE;
	STDMETHOD(get_Unique)						 (THIS_ VARIANT_BOOL FAR* pb) PURE;
	STDMETHOD(put_Unique)						 (THIS_ VARIANT_BOOL fUnique) PURE;
	STDMETHOD(get_Clustered)					 (THIS_ VARIANT_BOOL FAR* pb) PURE;
	STDMETHOD(put_Clustered)					 (THIS_ VARIANT_BOOL fClustered) PURE;
	STDMETHOD(get_Required)						 (THIS_ VARIANT_BOOL FAR* pb) PURE;
	STDMETHOD(put_Required)						 (THIS_ VARIANT_BOOL fRequired) PURE;
	STDMETHOD(get_IgnoreNulls)					 (THIS_ VARIANT_BOOL FAR* pb) PURE;
	STDMETHOD(put_IgnoreNulls)					 (THIS_ VARIANT_BOOL fIgnoreNulls) PURE;
	STDMETHOD(get_Primary)						 (THIS_ VARIANT_BOOL FAR* pb) PURE;
	STDMETHOD(put_Primary)						 (THIS_ VARIANT_BOOL fPrimary) PURE;
	STDMETHOD(get_DistinctCount)				 (THIS_ long FAR* pl) PURE;
	STDMETHOD(get_Fields)						 (THIS_ VARIANT FAR* pv) PURE;
	STDMETHOD(put_Fields)						 (THIS_ VARIANT v) PURE;
	STDMETHOD(CreateField)						 (THIS_ VARIANT Name, VARIANT Type, VARIANT Size, DAOField FAR* FAR* ppfld) PURE;
	STDMETHOD(CreateProperty)					 (THIS_ VARIANT Name, VARIANT Type, VARIANT Value, VARIANT DDL, DAOProperty FAR* FAR* pprp) PURE;
	};

// Interface: DAOIndexes
#undef INTERFACE
#define INTERFACE DAOIndexes
DECLARE_INTERFACE_(DAOIndexes, _DAODynaCollection)
	{
	STDMETHOD(get_Item)							 (THIS_ VARIANT index, DAOIndex FAR* FAR* ppidx) PURE;
	};

// Interface: DAOIndexFields
#undef INTERFACE
#define INTERFACE DAOIndexFields
DECLARE_INTERFACE_(DAOIndexFields, _DAODynaCollection)
	{
	STDMETHOD(get_Item)							 (THIS_ VARIANT index, VARIANT FAR* pvar) PURE;
	};

// Interface: DAOParameter
#undef INTERFACE
#define INTERFACE DAOParameter
DECLARE_INTERFACE_(DAOParameter, _DAO)
	{
	STDMETHOD(get_Name)							 (THIS_ BSTR FAR* pbstr) PURE;
	STDMETHOD(get_Value)						 (THIS_ VARIANT FAR* pvar) PURE;
	STDMETHOD(put_Value)						 (THIS_ VARIANT val) PURE;
	STDMETHOD(get_Type)							 (THIS_ short FAR* ps) PURE;
	STDMETHOD(put_Type)							 (THIS_ short s) PURE;
	STDMETHOD(get_Direction)					 (THIS_ short FAR* pOption) PURE;
	STDMETHOD(put_Direction)					 (THIS_ short Option) PURE;
	};

// Interface: DAOParameters
#undef INTERFACE
#define INTERFACE DAOParameters
DECLARE_INTERFACE_(DAOParameters, _DAOCollection)
	{
	STDMETHOD(get_Item)							 (THIS_ VARIANT index, DAOParameter FAR* FAR* ppprm) PURE;
	};

// Interface: _DAOUser
#undef INTERFACE
#define INTERFACE _DAOUser
DECLARE_INTERFACE_(_DAOUser, _DAO)
	{
	STDMETHOD(get_Name)							 (THIS_ BSTR FAR* pbstr) PURE;
	STDMETHOD(put_Name)							 (THIS_ BSTR bstr) PURE;
	STDMETHOD(put_PID)							 (THIS_ BSTR bstr) PURE;
	STDMETHOD(put_Password)						 (THIS_ BSTR bstr) PURE;
	STDMETHOD(get_Groups)						 (THIS_ DAOGroups FAR* FAR* ppgrps) PURE;
	STDMETHOD(NewPassword)						 (THIS_ BSTR bstrOld, BSTR bstrNew) PURE;
	STDMETHOD(CreateGroup)						 (THIS_ VARIANT Name, VARIANT PID, DAOGroup FAR* FAR* ppgrp) PURE;
	};

// Interface: DAOUsers
#undef INTERFACE
#define INTERFACE DAOUsers
DECLARE_INTERFACE_(DAOUsers, _DAODynaCollection)
	{
	STDMETHOD(get_Item)							 (THIS_ VARIANT index, DAOUser FAR* FAR* ppusr) PURE;
	};

// Interface: _DAOGroup
#undef INTERFACE
#define INTERFACE _DAOGroup
DECLARE_INTERFACE_(_DAOGroup, _DAO)
	{
	STDMETHOD(get_Name)							 (THIS_ BSTR FAR* pbstr) PURE;
	STDMETHOD(put_Name)							 (THIS_ BSTR bstr) PURE;
	STDMETHOD(put_PID)							 (THIS_ BSTR bstr) PURE;
	STDMETHOD(get_Users)						 (THIS_ DAOUsers FAR* FAR* ppusrs) PURE;
	STDMETHOD(CreateUser)						 (THIS_ VARIANT Name, VARIANT PID, VARIANT Password, DAOUser FAR* FAR* ppusr) PURE;
	};

// Interface: DAOGroups
#undef INTERFACE
#define INTERFACE DAOGroups
DECLARE_INTERFACE_(DAOGroups, _DAODynaCollection)
	{
	STDMETHOD(get_Item)							 (THIS_ VARIANT index, DAOGroup FAR* FAR* ppgrp) PURE;
	};

// Interface: _DAORelation
#undef INTERFACE
#define INTERFACE _DAORelation
DECLARE_INTERFACE_(_DAORelation, _DAO)
	{
	STDMETHOD(get_Name)							 (THIS_ BSTR FAR* pbstr) PURE;
	STDMETHOD(put_Name)							 (THIS_ BSTR bstr) PURE;
	STDMETHOD(get_Table)						 (THIS_ BSTR FAR* pbstr) PURE;
	STDMETHOD(put_Table)						 (THIS_ BSTR bstr) PURE;
	STDMETHOD(get_ForeignTable)					 (THIS_ BSTR FAR* pbstr) PURE;
	STDMETHOD(put_ForeignTable)					 (THIS_ BSTR bstr) PURE;
	STDMETHOD(get_Attributes)					 (THIS_ long FAR* pl) PURE;
	STDMETHOD(put_Attributes)					 (THIS_ long attr) PURE;
	STDMETHOD(get_Fields)						 (THIS_ DAOFields FAR* FAR* ppflds) PURE;
	STDMETHOD(CreateField)						 (THIS_ VARIANT Name, VARIANT Type, VARIANT Size, DAOField FAR* FAR* ppfld) PURE;
	STDMETHOD(get_PartialReplica)				 (THIS_ VARIANT_BOOL FAR* pfPartialReplica) PURE;
	STDMETHOD(put_PartialReplica)				 (THIS_ VARIANT_BOOL fPartialReplica) PURE;
	};

// Interface: DAORelations
#undef INTERFACE
#define INTERFACE DAORelations
DECLARE_INTERFACE_(DAORelations, _DAODynaCollection)
	{
	STDMETHOD(get_Item)							 (THIS_ VARIANT index, DAORelation FAR* FAR* pprel) PURE;
	};

// Interface: DAOProperty
#undef INTERFACE
#define INTERFACE DAOProperty
DECLARE_INTERFACE_(DAOProperty, _DAO)
	{
	STDMETHOD(get_Value)						 (THIS_ VARIANT FAR* pval) PURE;
	STDMETHOD(put_Value)						 (THIS_ VARIANT val) PURE;
	STDMETHOD(get_Name)							 (THIS_ BSTR FAR* pbstr) PURE;
	STDMETHOD(put_Name)							 (THIS_ BSTR bstr) PURE;
	STDMETHOD(get_Type)							 (THIS_ short FAR* ptype) PURE;
	STDMETHOD(put_Type)							 (THIS_ short type) PURE;
	STDMETHOD(get_Inherited)					 (THIS_ VARIANT_BOOL FAR* pb) PURE;
	};

// Interface: DAOProperties
#undef INTERFACE
#define INTERFACE DAOProperties
DECLARE_INTERFACE_(DAOProperties, _DAODynaCollection)
	{
	STDMETHOD(get_Item)							 (THIS_ VARIANT index, DAOProperty FAR* FAR* ppprop) PURE;
	};

// Interface: DAOContainer
#undef INTERFACE
#define INTERFACE DAOContainer
DECLARE_INTERFACE_(DAOContainer, _DAO)
	{
	STDMETHOD(get_Name)							 (THIS_ BSTR FAR* pbstr) PURE;
	STDMETHOD(get_Owner)						 (THIS_ BSTR FAR* pbstr) PURE;
	STDMETHOD(put_Owner)						 (THIS_ BSTR bstr) PURE;
	STDMETHOD(get_UserName)						 (THIS_ BSTR FAR* pbstr) PURE;
	STDMETHOD(put_UserName)						 (THIS_ BSTR bstr) PURE;
	STDMETHOD(get_Permissions)					 (THIS_ long FAR* pl) PURE;
	STDMETHOD(put_Permissions)					 (THIS_ long permissions) PURE;
	STDMETHOD(get_Inherit)						 (THIS_ VARIANT_BOOL FAR* pb) PURE;
	STDMETHOD(put_Inherit)						 (THIS_ VARIANT_BOOL fInherit) PURE;
	STDMETHOD(get_Documents)					 (THIS_ DAODocuments FAR* FAR* ppdocs) PURE;
	STDMETHOD(get_AllPermissions)				 (THIS_ long FAR* pl) PURE;
	};

// Interface: DAOContainers
#undef INTERFACE
#define INTERFACE DAOContainers
DECLARE_INTERFACE_(DAOContainers, _DAOCollection)
	{
	STDMETHOD(get_Item)							 (THIS_ VARIANT index, DAOContainer FAR* FAR* ppctn) PURE;
	};

// Interface: DAODocument
#undef INTERFACE
#define INTERFACE DAODocument
DECLARE_INTERFACE_(DAODocument, _DAO)
	{
	STDMETHOD(get_Name)							 (THIS_ BSTR FAR* pbstr) PURE;
	STDMETHOD(get_Owner)						 (THIS_ BSTR FAR* pbstr) PURE;
	STDMETHOD(put_Owner)						 (THIS_ BSTR bstr) PURE;
	STDMETHOD(get_Container)					 (THIS_ BSTR FAR* pbstr) PURE;
	STDMETHOD(get_UserName)						 (THIS_ BSTR FAR* pbstr) PURE;
	STDMETHOD(put_UserName)						 (THIS_ BSTR bstr) PURE;
	STDMETHOD(get_Permissions)					 (THIS_ long FAR* pl) PURE;
	STDMETHOD(put_Permissions)					 (THIS_ long permissions) PURE;
	STDMETHOD(get_DateCreated)					 (THIS_ VARIANT FAR* pvar) PURE;
	STDMETHOD(get_LastUpdated)					 (THIS_ VARIANT FAR* pvar) PURE;
	STDMETHOD(get_AllPermissions)				 (THIS_ long FAR* pl) PURE;
	STDMETHOD(CreateProperty)					 (THIS_ VARIANT Name, VARIANT Type, VARIANT Value, VARIANT DDL, DAOProperty FAR* FAR* pprp) PURE;
	};

// Interface: DAODocuments
#undef INTERFACE
#define INTERFACE DAODocuments
DECLARE_INTERFACE_(DAODocuments, _DAOCollection)
	{
	STDMETHOD(get_Item)							 (THIS_ VARIANT index, DAODocument FAR* FAR* ppdoc) PURE;
	};

// Interface: DAOConnection
#undef INTERFACE
#define INTERFACE DAOConnection
DECLARE_INTERFACE_(DAOConnection, IDispatch)
	{
	STDMETHOD(get_Name)							 (THIS_ BSTR FAR* pbstr) PURE;
	STDMETHOD(get_Connect)						 (THIS_ BSTR FAR* pbstr) PURE;
	STDMETHOD(get_Database)						 (THIS_ DAODatabase FAR* FAR* ppDb) PURE;
	STDMETHOD(get_hDbc)							 (THIS_ long FAR* phDbc) PURE;
	STDMETHOD(get_QueryTimeout)					 (THIS_ short FAR* pSeconds) PURE;
	STDMETHOD(put_QueryTimeout)					 (THIS_ short Seconds) PURE;
	STDMETHOD(get_Transactions)					 (THIS_ VARIANT_BOOL FAR* pb) PURE;
	STDMETHOD(get_RecordsAffected)				 (THIS_ long FAR* pRecords) PURE;
	STDMETHOD(get_StillExecuting)				 (THIS_ VARIANT_BOOL FAR* pStillExec) PURE;
	STDMETHOD(get_Updatable)					 (THIS_ VARIANT_BOOL FAR* pStillExec) PURE;
	STDMETHOD(get_QueryDefs)					 (THIS_ DAOQueryDefs FAR* FAR* ppqdfs) PURE;
	STDMETHOD(get_Recordsets)					 (THIS_ DAORecordsets FAR* FAR* pprsts) PURE;
	STDMETHOD(Cancel)							 (THIS) PURE;
	STDMETHOD(Close)							 (THIS) PURE;
	STDMETHOD(CreateQueryDef)					 (THIS_ VARIANT Name, VARIANT SQLText, DAOQueryDef FAR* FAR* ppqdf) PURE;
	STDMETHOD(Execute)							 (THIS_ BSTR Query, VARIANT Options) PURE;
	STDMETHOD(OpenRecordset)					 (THIS_ BSTR Name, VARIANT Type, VARIANT Options, VARIANT LockEdit, DAORecordset FAR* FAR* pprst) PURE;
	};

// Interface: DAOConnections
#undef INTERFACE
#define INTERFACE DAOConnections
DECLARE_INTERFACE_(DAOConnections, _DAOCollection)
	{
	STDMETHOD(get_Item)							 (THIS_ VARIANT index, DAOConnection FAR* FAR* ppconn) PURE;
	};

#endif // _DBDAOINT_H_
