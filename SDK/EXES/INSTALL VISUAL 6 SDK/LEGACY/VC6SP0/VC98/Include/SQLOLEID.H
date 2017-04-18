#ifndef SQLOLEID_H_
#define SQLOLEID_H_
/////////////////////////////////////////////////////////////////////////////////////////
// Header file for SQLOLE Component Object classes and interfaces.
// Copyright 1994 Microsoft Corporation.
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
//	SQLOLE Library UUID
/////////////////////////////////////////////////////////////////////////////////
DEFINE_OLEGUID(LIBID_SQLOLELibrary, 0x00026b00, 0, 0);

/////////////////////////////////////////////////////////////////////////////////
// VB/VBA Interfaces (IID_IV*).  These support IDispatch and vtable binding.
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// Internal base interfaces.
/////////////////////////////////////////////////////////////////////////////////
DEFINE_OLEGUID(IID_IVSQLOLEStdObject, 0x00026b01, 0, 0);
DEFINE_OLEGUID(IID_IVSQLOLEStdCollection, 0x00026b02, 0, 0);
DEFINE_OLEGUID(IID_ISQLOLEAnsiUniInternal, 0x00026b03, 0, 0);
DEFINE_OLEGUID(IID_ISQLOLEPrivate, 0x00026b04, 0, 0);

/////////////////////////////////////////////////////////////////////////////////
// Automation generic-property interfaces
/////////////////////////////////////////////////////////////////////////////////
DEFINE_OLEGUID(IID_IVSQLOLEProperties, 0x00026b05, 0, 0);
DEFINE_OLEGUID(IID_IVSQLOLEProperty, 0x00026b06, 0, 0);

/////////////////////////////////////////////////////////////////////////////////
// Create our own GUID template (OLEPM doesn't maintain the list anymore)
// The hardcoded numbers are from uuidgen, a unique time and netcard combination.
// As versions of SQLOLE increase, most DEFINE_OLDGUID macros below will be
// replaced by DEFINE_SQLOLEGUID, as the IID's are revved when new members are
// added to the interface (the old GUIDs will still be recognized for binary
// compatibility, but newly-compiled apps will use the new ones).
/////////////////////////////////////////////////////////////////////////////////
#define DEFINE_SQLOLEGUID(name, l) \
      DEFINE_GUID(name, l, 0x0bcc, 0x11ce, 0xa4, 0xb3, 0x00, 0xaa, 0x00, 0x4a, 0x34, 0xd5)

/////////////////////////////////////////////////////////////////////////////////
//	SQLOLE NonCreatable-Object Interface UUIDs.  These consist of all objects
// which do not have a class factory, such as collections and other objects
// the user acquires as the result of a property call.  VBA binds to these
// for simple pointer declarations.
/////////////////////////////////////////////////////////////////////////////////

// Collections of Creatable objects.  All Creatable objects (those which have a
// Class Factory), except the Application Object, exist in collections.
DEFINE_OLEGUID(IID_IVSQLOLEServers, 0x00026b11, 0, 0);
DEFINE_OLEGUID(IID_IVSQLOLEDatabases, 0x00026b12, 0, 0);
DEFINE_OLEGUID(IID_IVSQLOLETables, 0x00026b13, 0, 0);
DEFINE_OLEGUID(IID_IVSQLOLEColumns, 0x00026b14, 0, 0);
DEFINE_OLEGUID(IID_IVSQLOLEViews, 0x00026b15, 0, 0);
DEFINE_OLEGUID(IID_IVSQLOLEUserDefinedDatatypes, 0x00026b16, 0, 0);
DEFINE_OLEGUID(IID_IVSQLOLEDefaults, 0x00026b17, 0, 0);
DEFINE_OLEGUID(IID_IVSQLOLERules, 0x00026b18, 0, 0);
DEFINE_OLEGUID(IID_IVSQLOLEUsers, 0x00026b19, 0, 0);
DEFINE_OLEGUID(IID_IVSQLOLEGroups, 0x00026b1a, 0, 0);
DEFINE_OLEGUID(IID_IVSQLOLEStoredProcedures, 0x00026b1b, 0, 0);
DEFINE_OLEGUID(IID_IVSQLOLEIndexes, 0x00026b1c, 0, 0);
DEFINE_OLEGUID(IID_IVSQLOLEKeys, 0x00026b1d, 0, 0);
DEFINE_OLEGUID(IID_IVSQLOLETriggers, 0x00026b1e, 0, 0);
DEFINE_OLEGUID(IID_IVSQLOLEDevices, 0x00026b1f, 0, 0);
DEFINE_OLEGUID(IID_IVSQLOLEAlerts, 0x00026b20, 0, 0);
DEFINE_OLEGUID(IID_IVSQLOLELogins, 0x00026b21, 0, 0);
DEFINE_OLEGUID(IID_IVSQLOLELanguages, 0x00026b22, 0, 0);
DEFINE_OLEGUID(IID_IVSQLOLERemoteServers, 0x00026b23, 0, 0);
DEFINE_OLEGUID(IID_IVSQLOLERemoteLogins, 0x00026b24, 0, 0);
DEFINE_OLEGUID(IID_IVSQLOLETasks, 0x00026b25, 0, 0);
// Not used; slot preserved for numerical sequencing.  DEFINE_OLEGUID(IID_IVSQLOLETransfers, 0x00026b26, 0, 0);
// Not used; slot preserved for numerical sequencing.  DEFINE_OLEGUID(IID_IVSQLOLEBackups, 0x00026b27, 0, 0);
// Not used; slot preserved for numerical sequencing.  DEFINE_OLEGUID(IID_IVSQLOLEHistoryFilters, 0x00026b28, 0, 0);
DEFINE_OLEGUID(IID_IVSQLOLEOperators, 0x00026b29, 0, 0);
DEFINE_OLEGUID(IID_IVSQLOLEPublications, 0x00026b2a, 0, 0);
DEFINE_OLEGUID(IID_IVSQLOLEArticles, 0x00026b2b, 0, 0);
DEFINE_OLEGUID(IID_IVSQLOLESubscriptions, 0x00026b2c, 0, 0);
DEFINE_OLEGUID(IID_IVSQLOLEChecks, 0x00026b2d, 0, 0);
DEFINE_OLEGUID(IID_IVSQLOLEServerGroups, 0x00026b2e, 0, 0);
DEFINE_OLEGUID(IID_IVSQLOLERegisteredServers, 0x00026b2f, 0, 0);
// Not used; slot preserved for numerical sequencing.  DEFINE_OLEGUID(IID_IVSQLOLEBulkCopys, 0x00027b30, 0, 0);

// Non-Creatable objects, and collections thereof.
DEFINE_OLEGUID(IID_IVSQLOLENames, 0x00026b40, 0, 0);
DEFINE_OLEGUID(IID_IVSQLOLEDBObject, 0x00026b41, 0, 0);
DEFINE_OLEGUID(IID_IVSQLOLEDBOption, 0x00026b42, 0, 0);
DEFINE_OLEGUID(IID_IVSQLOLEConfiguration, 0x00026b43, 0, 0);
DEFINE_OLEGUID(IID_IVSQLOLEConfigValue, 0x00026b44, 0, 0);
DEFINE_SQLOLEGUID(IID_IVSQLOLESubscriberInfo, 0x00027b45);
DEFINE_OLEGUID(IID_IVSQLOLENameList, 0x00026b46, 0, 0);
DEFINE_SQLOLEGUID(IID_IVSQLOLEExecutive, 0x00027b47);
DEFINE_SQLOLEGUID(IID_IVSQLOLEQueryResults, 0x00027b48);
DEFINE_OLEGUID(IID_IVSQLOLETransactionLog, 0x00026b49, 0, 0);
DEFINE_OLEGUID(IID_IVSQLOLERegistry, 0x00026b4a, 0, 0);
DEFINE_OLEGUID(IID_IVSQLOLESystemDatatypes, 0x00026b4b, 0, 0);
DEFINE_OLEGUID(IID_IVSQLOLESystemDatatype, 0x00026b4c, 0, 0);
DEFINE_OLEGUID(IID_IVSQLOLEObjectList, 0x00026b4d, 0, 0);
DEFINE_OLEGUID(IID_IVSQLOLEPermission, 0x00026b4e, 0, 0);
DEFINE_OLEGUID(IID_IVSQLOLEIntegratedSecurity, 0x00026b4f, 0, 0);
DEFINE_OLEGUID(IID_IVSQLOLEDRIDefault, 0x00026b50, 0, 0);
DEFINE_OLEGUID(IID_IVSQLOLEConfigValues, 0x00026b51, 0, 0);
DEFINE_OLEGUID(IID_IVSQLOLEAlertSystem, 0x00026b52, 0, 0);

/////////////////////////////////////////////////////////////////////////////////
// SQLOLE Creatable-Object Interface UUIDs.  Class names in .odl/.hdl file are
// underscore-prefixed.  CoCreateInstance for these objects must use the corresponding
// CoClass uuid (CLSID_SQLOLE*) defined below.  These iids are solely to keep mktyplib happy.
// VBA binds to these interfaces indirectly, via the CoClass.
/////////////////////////////////////////////////////////////////////////////////
DEFINE_SQLOLEGUID(IID_IVSQLOLEApplication, 0x00027b70);

DEFINE_SQLOLEGUID(IID_IVSQLOLEServer, 0x00027b71);
DEFINE_SQLOLEGUID(IID_IVSQLOLEDatabase, 0x00027b72);
DEFINE_SQLOLEGUID(IID_IVSQLOLETable, 0x00027b73);
DEFINE_OLEGUID(IID_IVSQLOLEColumn, 0x00026b74, 0, 0);
DEFINE_SQLOLEGUID(IID_IVSQLOLEView, 0x00027b75);
DEFINE_OLEGUID(IID_IVSQLOLEUserDefinedDatatype, 0x00026b76, 0, 0);
DEFINE_OLEGUID(IID_IVSQLOLEDefault, 0x00026b77, 0, 0);
DEFINE_OLEGUID(IID_IVSQLOLERule, 0x00026b78, 0, 0);
DEFINE_OLEGUID(IID_IVSQLOLEUser, 0x00026b79, 0, 0);
DEFINE_OLEGUID(IID_IVSQLOLEGroup, 0x00026b7a, 0, 0);
DEFINE_SQLOLEGUID(IID_IVSQLOLEStoredProcedure, 0x00027b7b);
DEFINE_SQLOLEGUID(IID_IVSQLOLEIndex, 0x00027b7c);
DEFINE_SQLOLEGUID(IID_IVSQLOLEKey, 0x00027b7d);
DEFINE_OLEGUID(IID_IVSQLOLETrigger, 0x00026b7e, 0, 0);
DEFINE_SQLOLEGUID(IID_IVSQLOLEDevice, 0x00027b7f);
DEFINE_SQLOLEGUID(IID_IVSQLOLEAlert, 0x00027b80);
DEFINE_SQLOLEGUID(IID_IVSQLOLELogin, 0x00027b81);
DEFINE_OLEGUID(IID_IVSQLOLELanguage, 0x00026b82, 0, 0);
DEFINE_SQLOLEGUID(IID_IVSQLOLERemoteServer, 0x00027b83);
DEFINE_OLEGUID(IID_IVSQLOLERemoteLogin, 0x00026b84, 0, 0);
DEFINE_SQLOLEGUID(IID_IVSQLOLETask, 0x00027b85);
DEFINE_OLEGUID(IID_IVSQLOLETransfer, 0x00026b86, 0, 0);
DEFINE_SQLOLEGUID(IID_IVSQLOLEBackup, 0x00027b87);
DEFINE_OLEGUID(IID_IVSQLOLEHistoryFilter, 0x00026b88, 0, 0);
DEFINE_OLEGUID(IID_IVSQLOLEOperator, 0x00026b89, 0, 0);
DEFINE_SQLOLEGUID(IID_IVSQLOLEPublication, 0x00027b8a);
DEFINE_SQLOLEGUID(IID_IVSQLOLEArticle, 0x00027b8b);
DEFINE_OLEGUID(IID_IVSQLOLESubscription, 0x00026b8c, 0, 0);
DEFINE_OLEGUID(IID_IVSQLOLECheck, 0x00026b8d, 0, 0);
DEFINE_OLEGUID(IID_IVSQLOLEServerGroup, 0x00026b8e, 0, 0);
DEFINE_OLEGUID(IID_IVSQLOLERegisteredServer, 0x00026b8f, 0, 0);
DEFINE_SQLOLEGUID(IID_IVSQLOLEBulkCopy, 0x00027b90);

/////////////////////////////////////////////////////////////////////////////////
//	SQLOLE Creatable-Object ClassFactory Interface UUIDs (must be in Registry).
/////////////////////////////////////////////////////////////////////////////////
DEFINE_OLEGUID(CLSID_SQLOLEApplication, 0x00026ba0, 0, 0);
DEFINE_OLEGUID(CLSID_SQLOLEServer, 0x00026ba1, 0, 0);
DEFINE_OLEGUID(CLSID_SQLOLEDatabase, 0x00026ba2, 0, 0);
DEFINE_OLEGUID(CLSID_SQLOLETable, 0x00026ba3, 0, 0);
DEFINE_OLEGUID(CLSID_SQLOLEColumn, 0x00026ba4, 0, 0);
DEFINE_OLEGUID(CLSID_SQLOLEView, 0x00026ba5, 0, 0);
DEFINE_OLEGUID(CLSID_SQLOLEUserDefinedDatatype, 0x00026ba6, 0, 0);
DEFINE_OLEGUID(CLSID_SQLOLEDefault, 0x00026ba7, 0, 0);
DEFINE_OLEGUID(CLSID_SQLOLERule, 0x00026ba8, 0, 0);
DEFINE_OLEGUID(CLSID_SQLOLEUser, 0x00026ba9, 0, 0);
DEFINE_OLEGUID(CLSID_SQLOLEGroup, 0x00026baa, 0, 0);
DEFINE_OLEGUID(CLSID_SQLOLEStoredProcedure, 0x00026bab, 0, 0);
DEFINE_OLEGUID(CLSID_SQLOLEIndex, 0x00026bac, 0, 0);
DEFINE_OLEGUID(CLSID_SQLOLEKey, 0x00026bad, 0, 0);
DEFINE_OLEGUID(CLSID_SQLOLETrigger, 0x00026bae, 0, 0);
DEFINE_OLEGUID(CLSID_SQLOLEDevice, 0x00026baf, 0, 0);
DEFINE_OLEGUID(CLSID_SQLOLEAlert, 0x00026bb0, 0, 0);
DEFINE_OLEGUID(CLSID_SQLOLELogin, 0x00026bb1, 0, 0);
DEFINE_OLEGUID(CLSID_SQLOLELanguage, 0x00026bb2, 0, 0);
DEFINE_OLEGUID(CLSID_SQLOLERemoteServer, 0x00026bb3, 0, 0);
DEFINE_OLEGUID(CLSID_SQLOLERemoteLogin, 0x00026bb4, 0, 0);
DEFINE_OLEGUID(CLSID_SQLOLETask, 0x00026bb5, 0, 0);
DEFINE_OLEGUID(CLSID_SQLOLETransfer, 0x00026bb6, 0, 0);
DEFINE_OLEGUID(CLSID_SQLOLEBackup, 0x00026bb7, 0, 0);
DEFINE_OLEGUID(CLSID_SQLOLEHistoryFilter, 0x00026bb8, 0, 0);
DEFINE_OLEGUID(CLSID_SQLOLEOperator, 0x00026bb9, 0, 0);
DEFINE_OLEGUID(CLSID_SQLOLEPublication, 0x00026bba, 0, 0);
DEFINE_OLEGUID(CLSID_SQLOLEArticle, 0x00026bbb, 0, 0);
DEFINE_OLEGUID(CLSID_SQLOLESubscription, 0x00026bbc, 0, 0);
DEFINE_OLEGUID(CLSID_SQLOLECheck, 0x00026bbd, 0, 0);
DEFINE_OLEGUID(CLSID_SQLOLEServerGroup, 0x00026bbe, 0, 0);
DEFINE_OLEGUID(CLSID_SQLOLERegisteredServer, 0x00026bbf, 0, 0);
DEFINE_OLEGUID(CLSID_SQLOLEBulkCopy, 0x00026bc0, 0, 0);

/////////////////////////////////////////////////////////////////////////////////
// Ansi C/C++ Interfaces (IID_IA*)
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// Internal base interfaces.
/////////////////////////////////////////////////////////////////////////////////
DEFINE_OLEGUID(IID_ISQLOLEInternal, 0x00026c00, 0, 0);
DEFINE_OLEGUID(IID_IASQLOLEStdObject, 0x00026c01, 0, 0);
DEFINE_OLEGUID(IID_IASQLOLEStdCollection, 0x00026c02, 0, 0);

/////////////////////////////////////////////////////////////////////////////////
//	These IIDs are used by Ansi C/C++ clients.  Their sequence is identical to that
// defined above for all IID_ interfaces (not CoClass CLSIDs).  C/C++ clients
// bind to these rather than the VBA forms above.
/////////////////////////////////////////////////////////////////////////////////
// Collections of Creatable objects.  All Creatable objects (those which have a
// Class Factory), except the Application Object, exist in collections.
DEFINE_OLEGUID(IID_IASQLOLEServers, 0x00026c11, 0, 0);
DEFINE_OLEGUID(IID_IASQLOLEDatabases, 0x00026c12, 0, 0);
DEFINE_OLEGUID(IID_IASQLOLETables, 0x00026c13, 0, 0);
DEFINE_OLEGUID(IID_IASQLOLEColumns, 0x00026c14, 0, 0);
DEFINE_OLEGUID(IID_IASQLOLEViews, 0x00026c15, 0, 0);
DEFINE_OLEGUID(IID_IASQLOLEUserDefinedDatatypes, 0x00026c16, 0, 0);
DEFINE_OLEGUID(IID_IASQLOLEDefaults, 0x00026c17, 0, 0);
DEFINE_OLEGUID(IID_IASQLOLERules, 0x00026c18, 0, 0);
DEFINE_OLEGUID(IID_IASQLOLEUsers, 0x00026c19, 0, 0);
DEFINE_OLEGUID(IID_IASQLOLEGroups, 0x00026c1a, 0, 0);
DEFINE_OLEGUID(IID_IASQLOLEStoredProcedures, 0x00026c1b, 0, 0);
DEFINE_OLEGUID(IID_IASQLOLEIndexes, 0x00026c1c, 0, 0);
DEFINE_OLEGUID(IID_IASQLOLEKeys, 0x00026c1d, 0, 0);
DEFINE_OLEGUID(IID_IASQLOLETriggers, 0x00026c1e, 0, 0);
DEFINE_OLEGUID(IID_IASQLOLEDevices, 0x00026c1f, 0, 0);
DEFINE_OLEGUID(IID_IASQLOLEAlerts, 0x00026c20, 0, 0);
DEFINE_OLEGUID(IID_IASQLOLELogins, 0x00026c21, 0, 0);
DEFINE_OLEGUID(IID_IASQLOLELanguages, 0x00026c22, 0, 0);
DEFINE_OLEGUID(IID_IASQLOLERemoteServers, 0x00026c23, 0, 0);
DEFINE_OLEGUID(IID_IASQLOLERemoteLogins, 0x00026c24, 0, 0);
DEFINE_OLEGUID(IID_IASQLOLETasks, 0x00026c25, 0, 0);
// Not used; slot preserved for numerical sequencing.  DEFINE_OLEGUID(IID_IASQLOLETransfers, 0x00026c26, 0, 0);
// Not used; slot preserved for numerical sequencing.  DEFINE_OLEGUID(IID_IASQLOLEBackups, 0x00026c27, 0, 0);
// Not used; slot preserved for numerical sequencing.  DEFINE_OLEGUID(IID_IASQLOLEHistoryFilters, 0x00026c28, 0, 0);
DEFINE_OLEGUID(IID_IASQLOLEOperators, 0x00026c29, 0, 0);
DEFINE_OLEGUID(IID_IASQLOLEPublications, 0x00026c2a, 0, 0);
DEFINE_OLEGUID(IID_IASQLOLEArticles, 0x00026c2b, 0, 0);
DEFINE_OLEGUID(IID_IASQLOLESubscriptions, 0x00026c2c, 0, 0);
DEFINE_OLEGUID(IID_IASQLOLEChecks, 0x00026c2d, 0, 0);
DEFINE_OLEGUID(IID_IASQLOLEServerGroups, 0x00026c2e, 0, 0);
DEFINE_OLEGUID(IID_IASQLOLERegisteredServers, 0x00026c2f, 0, 0);
// Not used; slot preserved for numerical sequencing.  DEFINE_OLEGUID(IID_IASQLOLEBulkCopys, 0x00026c30, 0, 0);

// Non-Creatable objects, and collections thereof.
DEFINE_OLEGUID(IID_IASQLOLENames, 0x00026c40, 0, 0);
DEFINE_OLEGUID(IID_IASQLOLEDBObject, 0x00026c41, 0, 0);
DEFINE_OLEGUID(IID_IASQLOLEDBOption, 0x00026c42, 0, 0);
DEFINE_OLEGUID(IID_IASQLOLEConfiguration, 0x00026c43, 0, 0);
DEFINE_OLEGUID(IID_IASQLOLEConfigValue, 0x00026c44, 0, 0);
DEFINE_SQLOLEGUID(IID_IASQLOLESubscriberInfo, 0x00027c45);
DEFINE_OLEGUID(IID_IASQLOLENameList, 0x00026c46, 0, 0);
DEFINE_SQLOLEGUID(IID_IASQLOLEExecutive, 0x00027c47);
DEFINE_SQLOLEGUID(IID_IASQLOLEQueryResults, 0x00027c48);
DEFINE_OLEGUID(IID_IASQLOLETransactionLog, 0x00026c49, 0, 0);
DEFINE_OLEGUID(IID_IASQLOLERegistry, 0x00026c4a, 0, 0);
DEFINE_OLEGUID(IID_IASQLOLESystemDatatypes, 0x00026c4b, 0, 0);
DEFINE_OLEGUID(IID_IASQLOLESystemDatatype, 0x00026c4c, 0, 0);
DEFINE_OLEGUID(IID_IASQLOLEObjectList, 0x00026c4d, 0, 0);
DEFINE_OLEGUID(IID_IASQLOLEPermission, 0x00026c4e, 0, 0);
DEFINE_OLEGUID(IID_IASQLOLEIntegratedSecurity, 0x00026c4f, 0, 0);
DEFINE_OLEGUID(IID_IASQLOLEDRIDefault, 0x00026c50, 0, 0);
DEFINE_OLEGUID(IID_IASQLOLEConfigValues, 0x00026c51, 0, 0);
DEFINE_OLEGUID(IID_IASQLOLEAlertSystem, 0x00026c52, 0, 0);

//	Creatable objects.
DEFINE_SQLOLEGUID(IID_IASQLOLEApplication, 0x00027c70);

DEFINE_SQLOLEGUID(IID_IASQLOLEServer, 0x00027c71);
DEFINE_SQLOLEGUID(IID_IASQLOLEDatabase, 0x00027c72);
DEFINE_SQLOLEGUID(IID_IASQLOLETable, 0x00027c73);
DEFINE_OLEGUID(IID_IASQLOLEColumn, 0x00026c74, 0, 0);
DEFINE_SQLOLEGUID(IID_IASQLOLEView, 0x00027c75);
DEFINE_OLEGUID(IID_IASQLOLEUserDefinedDatatype, 0x00026c76, 0, 0);
DEFINE_OLEGUID(IID_IASQLOLEDefault, 0x00026c77, 0, 0);
DEFINE_OLEGUID(IID_IASQLOLERule, 0x00026c78, 0, 0);
DEFINE_OLEGUID(IID_IASQLOLEUser, 0x00026c79, 0, 0);
DEFINE_OLEGUID(IID_IASQLOLEGroup, 0x00026c7a, 0, 0);
DEFINE_SQLOLEGUID(IID_IASQLOLEStoredProcedure, 0x00027c7b);
DEFINE_SQLOLEGUID(IID_IASQLOLEIndex, 0x00027c7c);
DEFINE_SQLOLEGUID(IID_IASQLOLEKey, 0x00027c7d);
DEFINE_OLEGUID(IID_IASQLOLETrigger, 0x00026c7e, 0, 0);
DEFINE_SQLOLEGUID(IID_IASQLOLEDevice, 0x00027c7f);
DEFINE_SQLOLEGUID(IID_IASQLOLEAlert, 0x00027c80);
DEFINE_SQLOLEGUID(IID_IASQLOLELogin, 0x00027c81);
DEFINE_OLEGUID(IID_IASQLOLELanguage, 0x00026c82, 0, 0);
DEFINE_SQLOLEGUID(IID_IASQLOLERemoteServer, 0x00027c83);
DEFINE_OLEGUID(IID_IASQLOLERemoteLogin, 0x00026c84, 0, 0);
DEFINE_SQLOLEGUID(IID_IASQLOLETask, 0x00027c85);
DEFINE_OLEGUID(IID_IASQLOLETransfer, 0x00026c86, 0, 0);
DEFINE_SQLOLEGUID(IID_IASQLOLEBackup, 0x00027c87);
DEFINE_OLEGUID(IID_IASQLOLEHistoryFilter, 0x00026c88, 0, 0);
DEFINE_OLEGUID(IID_IASQLOLEOperator, 0x00026c89, 0, 0);
DEFINE_SQLOLEGUID(IID_IASQLOLEPublication, 0x00027c8a);
DEFINE_SQLOLEGUID(IID_IASQLOLEArticle, 0x00027c8b);
DEFINE_OLEGUID(IID_IASQLOLESubscription, 0x00026c8c, 0, 0);
DEFINE_OLEGUID(IID_IASQLOLECheck, 0x00026c8d, 0, 0);
DEFINE_OLEGUID(IID_IASQLOLEServerGroup, 0x00026c8e, 0, 0);
DEFINE_OLEGUID(IID_IASQLOLERegisteredServer, 0x00026c8f, 0, 0);
DEFINE_SQLOLEGUID(IID_IASQLOLEBulkCopy, 0x00027c90);


/////////////////////////////////////////////////////////////////////////////////
// Wide (Unicode) C/C++ Interfaces (IID_IW*)
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// Internal base interfaces.
/////////////////////////////////////////////////////////////////////////////////
DEFINE_OLEGUID(IID_IWSQLOLEStdObject, 0x00026d00, 0, 0);

/////////////////////////////////////////////////////////////////////////////////
// Collections of Creatable objects.  All Creatable objects (those which have a
// Class Factory), except the Application Object, exist in collections.
/////////////////////////////////////////////////////////////////////////////////

DEFINE_SQLOLEGUID(IID_IWSQLOLEServers, 0x00026d11);
DEFINE_SQLOLEGUID(IID_IWSQLOLEDatabases, 0x00026d12);
DEFINE_SQLOLEGUID(IID_IWSQLOLETables, 0x00026d13);
DEFINE_SQLOLEGUID(IID_IWSQLOLEColumns, 0x00026d14);
DEFINE_SQLOLEGUID(IID_IWSQLOLEViews, 0x00026d15);
DEFINE_SQLOLEGUID(IID_IWSQLOLEUserDefinedDatatypes, 0x00026d16);
DEFINE_SQLOLEGUID(IID_IWSQLOLEDefaults, 0x00026d17);
DEFINE_SQLOLEGUID(IID_IWSQLOLERules, 0x00026d18);
DEFINE_SQLOLEGUID(IID_IWSQLOLEUsers, 0x00026d19);
DEFINE_SQLOLEGUID(IID_IWSQLOLEGroups, 0x00026d1a);
DEFINE_SQLOLEGUID(IID_IWSQLOLEStoredProcedures, 0x00026d1b);
DEFINE_SQLOLEGUID(IID_IWSQLOLEIndexes, 0x00026d1c);
DEFINE_SQLOLEGUID(IID_IWSQLOLEKeys, 0x00026d1d);
DEFINE_SQLOLEGUID(IID_IWSQLOLETriggers, 0x00026d1e);
DEFINE_SQLOLEGUID(IID_IWSQLOLEDevices, 0x00026d1f);
DEFINE_SQLOLEGUID(IID_IWSQLOLEAlerts, 0x00026d20);
DEFINE_SQLOLEGUID(IID_IWSQLOLELogins, 0x00026d21);
DEFINE_SQLOLEGUID(IID_IWSQLOLELanguages, 0x00026d22);
DEFINE_SQLOLEGUID(IID_IWSQLOLERemoteServers, 0x00026d23);
DEFINE_SQLOLEGUID(IID_IWSQLOLERemoteLogins, 0x00026d24);
DEFINE_SQLOLEGUID(IID_IWSQLOLETasks, 0x00026d25);
// Not used; slot preserved for numerical sequencing.  DEFINE_SQLOLEGUID(IID_IWSQLOLETransfers, 0x00026d26);
// Not used; slot preserved for numerical sequencing.  DEFINE_SQLOLEGUID(IID_IWSQLOLEBackups, 0x00026d27);
// Not used; slot preserved for numerical sequencing.  DEFINE_SQLOLEGUID(IID_IWSQLOLEHistoryFilters, 0x00026d28);
DEFINE_SQLOLEGUID(IID_IWSQLOLEOperators, 0x00026d29);
DEFINE_SQLOLEGUID(IID_IWSQLOLEPublications, 0x00026d2a);
DEFINE_SQLOLEGUID(IID_IWSQLOLEArticles, 0x00026d2b);
DEFINE_SQLOLEGUID(IID_IWSQLOLESubscriptions, 0x00026d2c);
DEFINE_SQLOLEGUID(IID_IWSQLOLEChecks, 0x00026d2d);
DEFINE_SQLOLEGUID(IID_IWSQLOLEServerGroups, 0x00026d2e);
DEFINE_SQLOLEGUID(IID_IWSQLOLERegisteredServers, 0x00026d2f);
// Not used; slot preserved for numerical sequencing.  DEFINE_SQLOLEGUID(IID_IWSQLOLEBulkCopys, 0x00026d30);

// Non-Creatable objects, and collections thereof.
DEFINE_SQLOLEGUID(IID_IWSQLOLENames, 0x00026d40);
DEFINE_SQLOLEGUID(IID_IWSQLOLEDBObject, 0x00026d41);
DEFINE_SQLOLEGUID(IID_IWSQLOLEDBOption, 0x00026d42);
DEFINE_SQLOLEGUID(IID_IWSQLOLEConfiguration, 0x00026d43);
DEFINE_SQLOLEGUID(IID_IWSQLOLEConfigValue, 0x00026d44);
DEFINE_SQLOLEGUID(IID_IWSQLOLESubscriberInfo, 0x00027d45);
DEFINE_SQLOLEGUID(IID_IWSQLOLENameList, 0x00026d46);
DEFINE_SQLOLEGUID(IID_IWSQLOLEExecutive, 0x00027d47);
DEFINE_SQLOLEGUID(IID_IWSQLOLEQueryResults, 0x00027d48);
DEFINE_SQLOLEGUID(IID_IWSQLOLETransactionLog, 0x00026d49);
DEFINE_SQLOLEGUID(IID_IWSQLOLERegistry, 0x00026d4a);
DEFINE_SQLOLEGUID(IID_IWSQLOLESystemDatatypes, 0x00026d4b);
DEFINE_SQLOLEGUID(IID_IWSQLOLESystemDatatype, 0x00026d4c);
DEFINE_SQLOLEGUID(IID_IWSQLOLEObjectList, 0x00026d4d);
DEFINE_SQLOLEGUID(IID_IWSQLOLEPermission, 0x00026d4e);
DEFINE_SQLOLEGUID(IID_IWSQLOLEIntegratedSecurity, 0x00026d4f);
DEFINE_SQLOLEGUID(IID_IWSQLOLEDRIDefault, 0x00026d50);
DEFINE_SQLOLEGUID(IID_IWSQLOLEConfigValues, 0x00026d51);
DEFINE_SQLOLEGUID(IID_IWSQLOLEAlertSystem, 0x00026d52);

//	Creatable objects.
DEFINE_SQLOLEGUID(IID_IWSQLOLEApplication, 0x00027d70);

DEFINE_SQLOLEGUID(IID_IWSQLOLEServer, 0x00027d71);
DEFINE_SQLOLEGUID(IID_IWSQLOLEDatabase, 0x00027d72);
DEFINE_SQLOLEGUID(IID_IWSQLOLETable, 0x00027d73);
DEFINE_SQLOLEGUID(IID_IWSQLOLEColumn, 0x00026d74);
DEFINE_SQLOLEGUID(IID_IWSQLOLEView, 0x00027d75);
DEFINE_SQLOLEGUID(IID_IWSQLOLEUserDefinedDatatype, 0x00026d76);
DEFINE_SQLOLEGUID(IID_IWSQLOLEDefault, 0x00026d77);
DEFINE_SQLOLEGUID(IID_IWSQLOLERule, 0x00026d78);
DEFINE_SQLOLEGUID(IID_IWSQLOLEUser, 0x00026d79);
DEFINE_SQLOLEGUID(IID_IWSQLOLEGroup, 0x00026d7a);
DEFINE_SQLOLEGUID(IID_IWSQLOLEStoredProcedure, 0x00027d7b);
DEFINE_SQLOLEGUID(IID_IWSQLOLEIndex, 0x00027d7c);
DEFINE_SQLOLEGUID(IID_IWSQLOLEKey, 0x00027d7d);
DEFINE_SQLOLEGUID(IID_IWSQLOLETrigger, 0x00026d7e);
DEFINE_SQLOLEGUID(IID_IWSQLOLEDevice, 0x00027d7f);
DEFINE_SQLOLEGUID(IID_IWSQLOLEAlert, 0x00027d80);
DEFINE_SQLOLEGUID(IID_IWSQLOLELogin, 0x00027d81);
DEFINE_SQLOLEGUID(IID_IWSQLOLELanguage, 0x00026d82);
DEFINE_SQLOLEGUID(IID_IWSQLOLERemoteServer, 0x00027d83);
DEFINE_SQLOLEGUID(IID_IWSQLOLERemoteLogin, 0x00026d84);
DEFINE_SQLOLEGUID(IID_IWSQLOLETask, 0x00027d85);
DEFINE_SQLOLEGUID(IID_IWSQLOLETransfer, 0x00026d86);
DEFINE_SQLOLEGUID(IID_IWSQLOLEBackup, 0x00027d87);
DEFINE_SQLOLEGUID(IID_IWSQLOLEHistoryFilter, 0x00026d88);
DEFINE_SQLOLEGUID(IID_IWSQLOLEOperator, 0x00026d89);
DEFINE_SQLOLEGUID(IID_IWSQLOLEPublication, 0x00027d8a);
DEFINE_SQLOLEGUID(IID_IWSQLOLEArticle, 0x00027d8b);
DEFINE_SQLOLEGUID(IID_IWSQLOLESubscription, 0x00026d8c);
DEFINE_SQLOLEGUID(IID_IWSQLOLECheck, 0x00026d8d);
DEFINE_SQLOLEGUID(IID_IWSQLOLEServerGroup, 0x00026d8e);
DEFINE_SQLOLEGUID(IID_IWSQLOLERegisteredServer, 0x00026d8f);
DEFINE_SQLOLEGUID(IID_IWSQLOLEBulkCopy, 0x00027d90);

/////////////////////////////////////////////////////////////////////
// SQLOLE Connection Point IID's.
/////////////////////////////////////////////////////////////////////
DEFINE_SQLOLEGUID(IID_IASQLOLETransferSink, 0x00030000);
DEFINE_SQLOLEGUID(IID_IWSQLOLETransferSink, 0x00030001);
DEFINE_SQLOLEGUID(IID_IVSQLOLETransferSink, 0x00030002);
DEFINE_SQLOLEGUID(IID_IASQLOLEServerSink, 0x00030003);
DEFINE_SQLOLEGUID(IID_IWSQLOLEServerSink, 0x00030004);
DEFINE_SQLOLEGUID(IID_IVSQLOLEServerSink, 0x00030005);
DEFINE_SQLOLEGUID(IID_IASQLOLEBackupSink, 0x00030006);
DEFINE_SQLOLEGUID(IID_IWSQLOLEBackupSink, 0x00030007);
DEFINE_SQLOLEGUID(IID_IVSQLOLEBackupSink, 0x00030008);
DEFINE_SQLOLEGUID(IID_IASQLOLEBulkCopySink, 0x00030009);
DEFINE_SQLOLEGUID(IID_IWSQLOLEBulkCopySink, 0x0003000a);
DEFINE_SQLOLEGUID(IID_IVSQLOLEBulkCopySink, 0x0003000b);

#endif


