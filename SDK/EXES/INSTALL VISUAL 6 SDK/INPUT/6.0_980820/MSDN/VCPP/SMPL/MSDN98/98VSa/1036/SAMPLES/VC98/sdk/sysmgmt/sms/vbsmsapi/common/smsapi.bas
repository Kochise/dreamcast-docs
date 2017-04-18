Option Explicit
'// **************************************************************************
'//
'//  File: SMSAPI.H
'//
'//  Copyright (c) 1994, 1995 Microsoft Corp.
'//
'//  This is the header file for the SMS API.
'//
'//  This file contains all data definitions, manifests, return codes and
'//  API declarations that constitute the API set.
'//
'//
'// **************************************************************************
'
'
'
'// **************************************************************************
'//
'//  The SMS API set provides a set of interfaces to enable querying and,
'//  in some cases creation and deletion, of data from an SMS database.
'//
'//  SMS contains numerous objects to which an ISV needs access. These objects
'//  are (not in any particular order): packages, jobs, workstation command
'//  lines, program items, sites, domains, machines, machine groups.
'//
'//  The SMS API is built using a technology known as the objectity technique.
'//  This technique expresses all objects in terms of containers, folders,
'//  and scalars. All SMS objects are thus expressed in these terms.
'//  The advantage of this is that we have a standard interface to all
'//  objects. That is, the API does not distinguish between, say, a job and
'//  a machine.
'//
'//  The starting point is the container. There are certain types of container
'//  defined (container types below). A container is opened and then
'//  populated. The act of populating a container causes it to be filled with
'//  folders of defned types. A folder can contain sub-folders and scalars.
'//  Scalars are akin to leaf nodes in a hierarchy graph. The contain a
'//  name, type, and value.
'//
'//  Much of the power to the objectity technique is provided by filters.
'//  These are objects which specify selection criteria. Filters are applied
'//  by the user at the container level, at which point the implementation of
'//  the API will assume ownership of the filter. It is guaranteed that only
'//  folders matching the filters will be included in the container hierarchy.
'//
'//  Every folder can contain a set of scalars. Not all folders do, for
'//  example a machine folder does not. In some cases a folder contains a
'//  defined set of scalars, in other cases the scalar set can only be
'//  determined at run time. In cases where the scalar set is predetermined
'//  it will be documented in supporting documentation.
'//
'//  The APIs behave in an uniform manner.
'//  1. They all return a status code (SMS_STATUS).
'//  2. Where a value needs to be returned, it is done via a reference
'//     parameter.
'//
'//  An API is provided to determine the API version. Any problems involving
'//  the SMS API should include the information provided by this API.
'//
'//  The first step in using the APIs to to establish a connection to a
'//  datasource. Currently the only datasource supported in SQL, but the
'//  API is designed in such a way that additional datasources can be
'//  added. Two APIs are provided for dealing with datasources:
'//  DataSourceConnect and DataSourceDisonnect. The connect API returns a
'//  connection handle, this is used in subsequent calls to open containers.
'//
'//  Apart from these APIs, the rest of the API set is divided into four
'//  groups:
'//  1. Container APIs.
'//  2. Folder APIs.
'//  3. Scalar APIs.
'//  4. Filter APIs.
'//
'//  1. Container APIs.
'//  These allow a container to be opened, a filter to be applied to a
'//  container, a container to be populated with folders, a folder to be
'//  retrieved, and the container to be closed. An API also exists to
'//  return the number of folders currently contained in a container.
'//
'//  2. Folder APIs.
'//  These allow a for retrieval of various types of information about a
'//  folder (its ID or name, its type, the number of sub-folders, the number
'//  of scalars). Retrieval of sub-folders within a folder in both a
'//  sequential fashion and by name. Retrieval of scalars (sequential and by
'//  name. And closure of the folder.
'//  An API exists to allow folder creation. However, this is implementation
'//  dependant. That is, most folders do not permit creation, some (eg
'//  ceratin types of jobs) do.
'//
'//  3. Scalar APIs.
'//  There is a bit of overlap between this and the previous group. Although
'//  scalar retrieval is included in the Folder API group, it can also be
'//  considered a scalar API.
'//  An API is provided to set/update the value of a scalar. This can
'//  currently only be done in a folder that is being newly created.
'//
'//  4. Filter APIs.
'//  APIs for opening and closing a filter, and adding tokens into a filter.
'//  Filters are composed of one or more tokens of the same type. Some filters
'//  permit grouping of tokens within the filter (ie machine filter). This
'//  allows for complex boolean expressions.
'//  Tokens differ between different filters, but have a common interface.
'//  Tokens are contructed via the SmsAddToken API.
'//
'//  5. Filter container APIs
'//  Certain filters can be persistent, that is they are saved in the database
'//  and can be reloaded by separate processes. These filters can be created
'//  either the APIs, or via the SMS Admin.
'//   These APIs enable the retrieval of these filters from the datasource
'//  and the commital of new filters into the datasource.
'//  Currently machine filters are the only filters capable of exhibiting
'//  persistence.
'//
'// **************************************************************************
'
'// ====================================================================
'//
'//  Includes
'//
'// ====================================================================
'
'/* VB: These includes must be explicitly listed in the VB makefile   */
'
'include qrycodes.bas         // The query codes for Machine queries.
'
'include smsinfo.bas          // Manifests related to scalar settings.
'
'include objectty.bas         // Objectity engine.
'
'
'// ====================================================================
'//
'//  Datasource definition information.
'//
'// ====================================================================
'
'//
'// Supported datasources.
'// (NOTE: only sql supported currently).
'//
 Type DATASOURCE_TYPE
     enum As Long
 End Type
 
 ' These are initialized in Init_DATASOURCE_TYPE_enums()
 Global DB_SQL As DATASOURCE_TYPE
 Global DB_SQL_CONNECTED As DATASOURCE_TYPE
 Global DB_OTHER As DATASOURCE_TYPE
'
'
'//
'// Prototype for a decryption function. This is the last parameter
'// to the SQL_CONNECT_PARAMS structure.
'// When a user calls the DataSourceConnect API he can pass in the
'// user name and password in encrypted form. If the decryption function
'// pointer is non-null the the API will attempt to call this function
'// both for the user name and password.
'// The decryption function is user-supplied, it is expected to return
'// the decrypted data in the first parameter.
'//
'
'typedef void (*PDECRYPTFUNC)(char *pszBuffer, char *pszDecryptMe, char *pszKey);
'/* VB: This can not be done this way in VB  */
'
'
'//
'//  The information block needed for the DataSourceConnect API.
'//  1. SQL datasource.
'//
'
 Type SQL_CONNECT_PARAMS
     ds As DATASOURCE_TYPE
     pszServer As String                 '// SQL Server name.
     pszUserName As String               '// User name (possibly encrypted).
     pszPasswd As String                 '// Password (possibly encrypted).
     pszDbName As String                 '// Database name.
     pszKey As String                    '// Decryption key.
     pFunc As Long                       '// Pointer to a decryption function.
 End Type
'
'
'//
'//  2. RESERVED DO NOT USE
'//
'
'typedef struct _SQL_CONNECT_CONNECTED_PARAMS {
'    DATASOURCE_TYPE ds;
'    HANDLE hDataSource;
'    const char *pszAccessType;
'} SQL_CONNECT_CONNECTED_PARAMS;
'
'
'
'//
'// This only has the type field. It is used for extracting the type
'// in such a fashion that user code doesn't have to imply any
'// particular data source. It has no use other than that.
'//
'
 Type GENERIC
     ds As DATASOURCE_TYPE
 End Type
'
'
'
'// We can now define the DATASOURCE. It is a union of the structs above.
'typedef union {
'    GENERIC             type;
'    SQL_CONNECT_PARAMS  sqlParams;
'    SQL_CONNECT_CONNECTED_PARAMS sqlConnectedParams;
'} DATASOURCE;
'
'/* VB: Unions can not be done in VB  */
'
'
'
'// ====================================================================
'//
'//  Return codes. See also objectty.h.
'//
'// ====================================================================
'typedef DWORD SMS_STATUS;           // All APIs return an SMS_STATUS.
'/* VB: All API's return Long  */
'
 Global Const SMS_OK = OTT_OK
 Global Const SMS_MORE_DATA = OTT_MORE_DATA
 Global Const SMS_NO_MORE_DATA = OTT_NO_MORE_DATA
 Global Const SMS_FOLDER_NO_UPDATE = OTT_FOLDER_NO_UPDATE
'
'// Error codes when registering (and accessing) containers and filters
 Global Const SMS_DUPLICATE_CONTAINER_ID = OTT_DUPLICATE_CONTAINER_ID
 Global Const SMS_DUPLICATE_FOLDER_ID = OTT_DUPLICATE_FOLDER_ID
 Global Const SMS_DUPLICATE_FILTER_ID = OTT_DUPLICATE_FILTER_ID
'
 Global Const SMS_DUPLICATE_FILTER = OTT_DUPLICATE_FILTER
'
 Global Const SMS_SCALAR_NO_UPDATE = OTT_SCALAR_NO_UPDATE
 Global Const SMS_SCALAR_WRONG_TYPE = OTT_SCALAR_WRONG_TYPE
 Global Const SMS_INVALID_CONTAINER_ID = OTT_INVALID_CONTAINER_ID
 Global Const SMS_INVALID_FOLDER_ID = OTT_INVALID_FOLDER_ID
 Global Const SMS_INVALID_FILTER_ID = OTT_INVALID_FILTER_ID
'
 Global Const SMS_CONTAINER_NO_UPDATE = OTT_CONTAINER_NO_UPDATE
'
 Global Const SMS_PARAMETER_ERROR = OTT_PARAMETER_ERROR
 Global Const SMS_UNSUPPORTED = OTT_UNSUPPORTED
'
'// This is returned when a specific object (folder or scalar) is
'// requested and not found. APIs returning this are GetFolderByID
'// and GetScalarByName.
 Global Const SMS_NOT_FOUND = OTT_NOT_FOUND
'
 Global Const SMS_PARENT_NOT_FOUND = OTT_PARENT_NOT_FOUND
'
 Global Const SMS_CANT_DELETE = OTT_CANT_DELETE
'
 Global Const SMS_NEW_FOLDER = OTT_NEW_FOLDER
'
'// Error when attempting to multiply link a folder.
 Global Const SMS_FOLDER_LINKED = OTT_FOLDER_LINKED
'
'// Filter operations.
 Global Const SMS_RANGE_ERROR = OTT_RANGE_ERROR
'
'// These are returned when a container operation is tried
'// when it shouldn't be.
 Global Const SMS_CONTAINER_NOT_POPULATED = OTT_CONTAINER_NOT_POPULATED
 Global Const SMS_CONTAINER_POPULATED = OTT_CONTAINER_POPULATED
'
'
'// Attempt to perform persistent operation on a non-persistent filter.
 Global Const SMS_FILTER_NOT_PERSISTENT = OTT_FILTER_NOT_PERSISTENT
'
'// Error return if the connection handle of a filter doesn't match
'// that of a container to which the filter is being applied.
 Global Const SMS_INVALID_CONNECTION_HANDLE = OTT_INVALID_CONNECTION_HANDLE
 Global Const SMS_INVALID_FILTER_TYPE = OTT_INVALID_FILTER_TYPE

'// Folder's can't be unlinked if there are multiple handles
'// to the same object.
 Global Const SMS_IN_USE_BY_OTHER = OTT_IN_USE_BY_OTHER
'
'
'// User (ie non-engine) codes begin here.
 Global Const SMS_ERROR = OTT_END + 1
 Global Const SMS_SQL_ERROR = OTT_END + 2
 Global Const SMS_INVALID_DATASOURCE = OTT_END + 3
 Global Const SMS_INVALID_HANDLE = OTT_END + 4
 Global Const SMS_INVALID_FOLDER_TYPE = OTT_END + 6
'
 Global Const SMS_CONNECT_FAILED = OTT_END + 7
 Global Const SMS_NO_CREATE = OTT_END + 8
 Global Const SMS_FOLDER_NOT_MODIFIED = OTT_END + 9
 Global Const SMS_INCORRECT_FOLDER_TYPE = OTT_END + 10 'Unused.
 Global Const SMS_INVALID_PARAMETER = OTT_END + 11
 Global Const SMS_EMPTY = OTT_END + 12
'
'// Error when attempting to commit a child folder when the
'// parent folder must be committed.
 Global Const SMS_PARENT_NEEDS_COMMIT = OTT_END + 13
 Global Const SMS_PARENT_ALREADY_COMMITTED = OTT_END + 14
'
'// Used in asynchronous folder retrieval. Indicates that there
'// might be more data but it isn't available yet.
 Global Const SMS_NOT_READY = OTT_END + 15
'
 Global Const SMS_FILTER_NO_MODIFY = OTT_END + 16
 Global Const SMS_FOLDER_ALREADY_DELETED = OTT_END + 17
'
'// Only allow one active connection. This is an SMS restriction.
 Global Const SMS_ALREADY_CONNECTED = OTT_END + 18

'// Some failure in committing a folder
 Global Const SMS_COMMIT_FAILED = OTT_END + 19


'// Specific failure in linking a folder
 Global Const SMS_DUPLICATE_FOLDER = OTT_END + 20

 Global Const SMS_ERROR_LAST = OTT_END + 20


'Error strings
'This array is initialized in Init_SMSError_array()
Global SMSError$(0 To SMS_ERROR_LAST)

'
'// ====================================================================
'//
'//  Various manifests.
'//
'// ====================================================================
'
'// The location of the SMS registry root.
 Global Const SMS_REG_ROOT = "SOFTWARE\Microsoft\SMS\"
'
'// The max size of character (string) data that we return.
 Global Const SMS_DATA_BUFF_SIZE = 255
'
'
'// 'SMSBUFF' and 'OBJDESCRIPTOR' used in object type enumeration APIs.
'// ===================================================================

'// A character buffer.
'// -------------------
'typedef char SMSBUFF[SMS_DATA_BUFF_SIZE+1];

'// Describes an object returned from SmsEnumObjects.
'// -------------------------------------------------
 Type OBJDESCRIPTOR
     objType As Long                   '// Type of this object.
     szName As String                  '// Object name (eg 'Personal Computer')
     szFriendlyName As String          '// Friendly name. Only used in groups
                                       '// where szName would be, eg,
                                       '// 'MICROSOFT|IDENTIFICATION|1.0', the
                                       '// friendly name would be 'Identification'.
     bGotFriendlyName As Long          '// TRUE if we have a friendly name.

     dwRelopMin As Long                '// For attributes, indicates range of
     dwRelopMax As Long                '// relational operators that can be used
                                       '// for this attribute.
     bGotRelops As Long                '// TRUE if we have the relops fields set.

 End Type


'// Object types.
'// =============
'// This is the value that is inserted by the object
'// enumeration APIs into the OBJDESCRIPTOR structure.
'// --------------------------------------------------
 Global Const OT_ARCHLIST = 1
 Global Const OT_ARCH = 2
 Global Const OT_GROUP = 3
 Global Const OT_ATTRIBUTE = 4

 Global Const OT_PLATFORMS = 5
 Global Const OT_PLATFORM_PDF = 6
 Global Const OT_PLATFORM_WINST = 7
 Global Const OT_PLATFORM_NAD = 8

 Global Const OT_UNKNOWN = 100



'// --------------------------------------------------------------------
'// Flags for Populate options.
'// --------------------------------------------------------------------
 Global Const POP_SYNC = &H0&
 Global Const POP_ASYNC = &H1&
 Global Const POP_EVENT = &H10&
 Global Const POP_WINDOW = &H20&
'
'
'// --------------------------------------------------------------------
'// Folder types supported by smsapi (MUST NOT BEGIN AT ZERO).
'// --------------------------------------------------------------------
 Global Const F_SITE = 1                 'Site folder
 Global Const F_MACHINE = 2              'Machine folder
 Global Const F_GROUP = 3                'Subfolder of machine
 Global Const F_DOMAIN = 4               'Domain folder, subfolder of a site

'// Jobs
 Global Const F_SYSTEMJOB = 5            'System (NAD/Site) job folder
'Global Const F_MINIJOB = 6              'Mini-job folder
 Global Const F_INSTALLJOB = 7           'Job folder (wksta install)
 Global Const F_SRVINSTALLJOB = 8        'Job folder (server install)
 Global Const F_REMPKGJOB = 9            'Remove package Job folder
'
 Global Const F_PACKAGE = 10             'Packages
 Global Const F_WCL = 11                 'Workstation command lines
 Global Const F_PROGITEM = 12            'Program items
 Global Const F_INVENTORY = 13           'Inventory rules.
'
 Global Const F_MACHINEGROUP = 14        'Machine group
 Global Const F_SITEGROUP = 15           'Site group folder
'
'// --------------------------------------------------------------------
'// Container types supported by smsapi (MUST NOT BEGIN AT ZERO).
'// --------------------------------------------------------------------
 Global Const C_SITE = 1                 'Site container
 Global Const C_JOB = 2                  'Job container
 Global Const C_MACHINE = 3              'Machine container
 Global Const C_PACKAGE = 4              'Package container
 Global Const C_MACHINEGROUP = 5         'Machine group
 Global Const C_SITEGROUP = 6            'Site group
'
'
'// ====================================================================
'//
'//      Filter information.
'//
'// ====================================================================
'
'
'// --------------------------------------------------------------------
'//  Filter types
'// --------------------------------------------------------------------
 Global Const SITE_FILTER = 1
 Global Const MACHINE_FILTER = 2
 Global Const GROUP_FILTER = 3
 Global Const JOB_FILTER = 4
 Global Const ARCHITECTURE_FILTER = 5
 Global Const PACKAGE_FILTER = 6
 Global Const ATTRIBUTE_FILTER = 7
 Global Const SITELIMIT_FILTER = 8
'
'
'// --------------------------------------------------------------------
'// Token types.
'// --------------------------------------------------------------------
 Global Const TOKEN_USER = &H8      '1000 bit 3 always set for user-token
 Global Const TOKEN_OR = &H2        '0010 bit 1 always set for AND/OR
 Global Const TOKEN_AND = &H3       '0011 bit 1 always set for AND/OR
 Global Const TOKEN_OPENPAREN = &H4 '0100 bit 2 always set for PAREN
 Global Const TOKEN_CLOSEPAREN = &H5'0101 bit 2 always set for PAREN
 Global Const TOKEN_NOTIN = &H20    '10100 bit 2 set for a PAREN plus bit 4 for an extra indicator.
 Global Const TOKEN_OPERATOR = &H2  'Detects both AND or OR
 Global Const TOKEN_PAREN = &H4     'Detects either open or close paren
'
'
'// --------------------------------------------------------------------
'// Manifests used in filter token APIs.
'// --------------------------------------------------------------------
 Global Const AT_START = OTT_AT_START 'Token will be inserted at start of expression
 Global Const AT_END = OTT_AT_END     'Token will be appended to end of expression
'
'//
'// Flags fields in SmsManipulateTokens.
'//
 Global Const TOK_GROUP = 1          'Flags field in SmsManipulateTokens
 Global Const TOK_UNGROUP = 2
 Global Const TOK_DELETE = 3
 Global Const TOK_GROUP_NOT = 4
'
'
 Sub Init_DATASOURCE_TYPE_enums ()
     DB_SQL.enum = 0
     DB_SQL_CONNECTED.enum = 1
     DB_OTHER.enum = 2
 End Sub

 Function Init_SMSAPI% ()
     'Default return value True (DLL loaded)
     Init_SMSAPI% = True
 
     'Initialize "included" modules
     Init_OBJECTTY
     Init_QRYCODES
 
     'Initialize this module
     Init_DATASOURCE_TYPE_enums
 
     'Initialize error string array
     Init_SMSError_array
 End Function

 Sub Init_SMSError_array ()
     SMSError$(SMS_OK) = "SMS_OK"
     SMSError$(SMS_MORE_DATA) = "SMS_MORE_DATA"
     SMSError$(SMS_NO_MORE_DATA) = "SMS_NO_MORE_DATA"
     SMSError$(SMS_FOLDER_NO_UPDATE) = "SMS_FOLDER_NO_UPDATE"
 
'// Error codes when registering (and accessing) containers and filters
     SMSError$(SMS_DUPLICATE_CONTAINER_ID) = "SMS_DUPLICATE_CONTAINER_ID"
     SMSError$(SMS_DUPLICATE_FOLDER_ID) = "SMS_DUPLICATE_FOLDER_ID"
     SMSError$(SMS_DUPLICATE_FILTER_ID) = "SMS_DUPLICATE_FILTER_ID"
     SMSError$(SMS_DUPLICATE_FILTER) = "SMS_DUPLICATE_FILTER"
     
     SMSError$(SMS_SCALAR_NO_UPDATE) = "SMS_SCALAR_NO_UPDATE"
     SMSError$(SMS_SCALAR_WRONG_TYPE) = "SMS_SCALAR_WRONG_TYPE"
     SMSError$(SMS_INVALID_CONTAINER_ID) = "SMS_INVALID_CONTAINER_ID"
     SMSError$(SMS_INVALID_FOLDER_ID) = "SMS_INVALID_FOLDER_ID"
     SMSError$(SMS_INVALID_FILTER_ID) = "SMS_INVALID_FILTER_ID"
 
     SMSError$(SMS_CONTAINER_NO_UPDATE) = "SMS_CONTAINER_NO_UPDATE"
 
     SMSError$(SMS_PARAMETER_ERROR) = "SMS_PARAMETER_ERROR"
     SMSError$(SMS_UNSUPPORTED) = "SMS_UNSUPPORTED"
 
'// This is returned when a specific object (folder or scalar) is
'// requested and not found. APIs returning this are GetFolderByID
'// and GetScalarByName.
     SMSError$(SMS_NOT_FOUND) = "SMS_NOT_FOUND"
 
     SMSError$(SMS_PARENT_NOT_FOUND) = "SMS_PARENT_NOT_FOUND"
     
     SMSError$(SMS_CANT_DELETE) = "SMS_CANT_DELETE"
     
     SMSError$(SMS_NEW_FOLDER) = "SMS_NEW_FOLDER"
 
'// Error when attempting to multiply link a folder.
     SMSError$(SMS_FOLDER_LINKED) = "SMS_FOLDER_LINKED"
     
'// Filter operations.
     SMSError$(SMS_RANGE_ERROR) = "SMS_RANGE_ERROR"
     
'// These are returned when a container operation is tried
'// when it shouldn't be.
     SMSError$(SMS_CONTAINER_NOT_POPULATED) = "SMS_CONTAINER_NOT_POPULATED"
     SMSError$(SMS_CONTAINER_POPULATED) = "SMS_CONTAINER_POPULATED"
 
'// Attempt to perform persistent operation on a non-persistent filter.
     SMSError$(SMS_FILTER_NOT_PERSISTENT) = "SMS_FILTER_NOT_PERSISTENT"
 
'// Error return if the connection handle of a filter doesn't match
'// that of a container to which the filter is being applied.
     SMSError$(SMS_INVALID_CONNECTION_HANDLE) = "SMS_INVALID_CONNECTION_HANDLE"
 
'// User (ie non-engine) codes begin here.
     SMSError$(SMS_ERROR) = "SMS_ERROR"
     SMSError$(SMS_SQL_ERROR) = "SMS_SQL_ERROR"
     SMSError$(SMS_INVALID_DATASOURCE) = "SMS_INVALID_DATASOURCE"
     SMSError$(SMS_INVALID_HANDLE) = "SMS_INVALID_HANDLE"
     SMSError$(SMS_INVALID_FILTER_TYPE) = "SMS_INVALID_FILTER_TYPE"
     SMSError$(SMS_INVALID_FOLDER_TYPE) = "SMS_INVALID_FOLDER_TYPE"
 
     SMSError$(SMS_CONNECT_FAILED) = "SMS_CONNECT_FAILED"
     SMSError$(SMS_NO_CREATE) = "SMS_NO_CREATE"
     SMSError$(SMS_FOLDER_NOT_MODIFIED) = "SMS_FOLDER_NOT_MODIFIED"
     SMSError$(SMS_INCORRECT_FOLDER_TYPE) = "SMS_INCORRECT_FOLDER_TYPE"
     SMSError$(SMS_INVALID_PARAMETER) = "SMS_INVALID_PARAMETER"
     SMSError$(SMS_EMPTY) = "SMS_EMPTY"
 
'// Error when attempting to commit a child folder when the
'// parent folder must be committed.
     SMSError$(SMS_PARENT_NEEDS_COMMIT) = "SMS_PARENT_NEEDS_COMMIT"
     SMSError$(SMS_PARENT_ALREADY_COMMITTED) = "SMS_PARENT_ALREADY_COMMITTED"
 
'// Used in asynchronous folder retrieval. Indicates that there
'// might be more data but it isn't available yet.
     SMSError$(SMS_NOT_READY) = "SMS_NOT_READY"
     
     SMSError$(SMS_FILTER_NO_MODIFY) = "SMS_FILTER_NO_MODIFY"
     SMSError$(SMS_FOLDER_ALREADY_DELETED) = "SMS_FOLDER_ALREADY_DELETED"
 
'// Only allow one active connection (SMS restriction).
     SMSError$(SMS_ALREADY_CONNECTED) = "SMS_ALREADY_CONNECTED"
 End Sub

