// **************************************************************************
//
//  File: SMSAPI.H
//
//  Copyright (c) 1994, 1995 Microsoft Corp.
//
//  This is the header file for the SMS API.
//
//  This file contains all data definitions, manifests, return codes and
//  API declarations that constitute the API set.
//
//
// **************************************************************************



// **************************************************************************
//
//  The SMS API set provides a set of interfaces to enable querying and,
//  in some cases creation and deletion, of data from an SMS database.
//
//  SMS contains numerous objects to which an ISV needs access. These objects
//  are (not in any particular order): packages, jobs, workstation command
//  lines, program items, sites, domains, machines, machine groups.
//
//  The SMS API is built using a technology known as the objectity technique.
//  This technique expresses all objects in terms of containers, folders,
//  and scalars. All SMS objects are thus expressed in these terms.
//  The advantage of this is that we have a standard interface to all
//  objects. That is, the API does not distinguish between, say, a job and
//  a machine.
//
//  The starting point is the container. There are certain types of container
//  defined (container types below). A container is opened and then
//  populated. The act of populating a container causes it to be filled with
//  folders of defned types. A folder can contain sub-folders and scalars.
//  Scalars are akin to leaf nodes in a hierarchy graph. The contain a
//  name, type, and value.
//
//  Much of the power to the objectity technique is provided by filters.
//  These are objects which specify selection criteria. Filters are applied
//  by the user at the container level, at which point the implementation of
//  the API will assume ownership of the filter. It is guaranteed that only
//  folders matching the filters will be included in the container hierarchy.
//
//  Every folder can contain a set of scalars. Not all folders do, for
//  example a machine folder does not. In some cases a folder contains a
//  defined set of scalars, in other cases the scalar set can only be
//  determined at run time. In cases where the scalar set is predetermined
//  it will be documented in supporting documentation.
//
//  The APIs behave in a uniform manner.
//  1. They all return a status code (SMS_STATUS).
//  2. Where a value needs to be returned, it is done via a reference
//     parameter.
//
//  An API is provided to determine the API version. Any problems involving
//  the SMS API should include the information provided by this API.
//
//  The first step in using the APIs to to establish a connection to a
//  datasource. Currently the only datasource supported in SQL, but the
//  API is designed in such a way that additional datasources can be
//  added. Two APIs are provided for dealing with datasources:
//  DataSourceConnect and DataSourceDisonnect. The connect API returns a
//  connection handle, this is used in subsequent calls to open containers.
//
//  Apart from these APIs, the rest of the API set is divided into four
//  groups:
//  1. Container APIs.
//  2. Folder APIs.
//  3. Scalar APIs.
//  4. Filter APIs.
//
//  1. Container APIs.
//  These allow a container to be opened, a filter to be applied to a
//  container, a container to be populated with folders, a folder to be
//  retrieved, and the container to be closed. An API also exists to
//  return the number of folders currently contained in a container.
//
//  2. Folder APIs.
//  These allow a for retrieval of various types of information about a
//  folder (its ID or name, its type, the number of sub-folders, the number
//  of scalars). Retrieval of sub-folders within a folder in both a
//  sequential fashion and by name. Retrieval of scalars (sequential and by
//  name. And closure of the folder.
//  An API exists to allow folder creation. However, this is implementation
//  dependant. That is, most folders do not permit creation, some (eg
//  ceratin types of jobs) do.
//
//  3. Scalar APIs.
//  There is a bit of overlap between this and the previous group. Although
//  scalar retrieval is included in the Folder API group, it can also be
//  considered a scalar API.
//  An API is provided to set/update the value of a scalar. This can
//  currently only be done in a folder that is being newly created.
//
//  4. Filter APIs.
//  APIs for opening and closing a filter, and adding tokens into a filter.
//  Filters are composed of one or more tokens of the same type. Some filters
//  permit grouping of tokens within the filter (ie machine filter). This
//  allows for complex boolean expressions.
//  Tokens differ between different filters, but have a common interface.
//  Tokens are contructed via the SmsAddToken API.
//
//  5. Filter container APIs
//  Certain filters can be persistent, that is they are saved in the database
//  and can be reloaded by separate processes. These filters can be created
//  either the APIs, or via the SMS Admin.
//   These APIs enable the retrieval of these filters from the datasource
//  and the commital of new filters into the datasource.
//  Currently machine filters are the only filters capable of exhibiting
//  persistence.
//
// **************************************************************************


#ifndef _SMSAPI_H_
#define _SMSAPI_H_



// ====================================================================
//
//  Includes
//
// ====================================================================

#include <qrycodes.h>           // The query codes for Machine queries.

#include <smsinfo.h>            // Manifests related to scalar settings.

#include <objectty.h>           // Objectity engine.


#ifdef __cplusplus
extern "C" {
#endif



// ====================================================================
//
//  Datasource definition information.
//
// ====================================================================

//
// Supported datasources.
// (NOTE: only sql supported currently).
//
typedef enum { DB_SQL, DB_SQL_CONNECTED, DB_OTHER } DATASOURCE_TYPE;


//
// Prototype for a decryption function. This is the last parameter
// to the SQL_CONNECT_PARAMS structure.
// When a user calls the DataSourceConnect API he can pass in the
// user name and password in encrypted form. If the decryption function
// pointer is non-null the the API will attempt to call this function
// both for the user name and password.
// The decryption function is user-supplied, it is expected to return
// the decrypted data in the first parameter.
//

typedef void (*PDECRYPTFUNC)(char *pszBuffer, char *pszDecryptMe, char *pszKey);


//
//  The information block needed for the DataSourceConnect API.
//  1. SQL datasource.
//

typedef struct _SQL_CONNECT_PARAMS {
    DATASOURCE_TYPE ds;
    char *pszServer;                    // SQL Server name.
    char *pszUserName;                  // User name (possibly encrypted).
    char *pszPasswd;                    // Password (possibly encrypted).
    char *pszDbName;                    // Database name.
    char *pszKey;                       // Decryption key.
    PDECRYPTFUNC pFunc;                 // Pointer to a decryption function.
} SQL_CONNECT_PARAMS;


//
//  2. RESERVED DO NOT USE
//

typedef struct _SQL_CONNECT_CONNECTED_PARAMS {
    DATASOURCE_TYPE ds;
    HANDLE hDataSource;
    const char *pszAccessType;
} SQL_CONNECT_CONNECTED_PARAMS;



//
// This only has the type field. It is used for extracting the type
// in such a fashion that user code doesn't have to imply any
// particular data source. It has no use other than that.
//

typedef struct _GENERIC {
    DATASOURCE_TYPE ds;
} GENERIC;



// We can now define the DATASOURCE. It is a union of the structs above.
typedef union {
    GENERIC             type;
    SQL_CONNECT_PARAMS  sqlParams;
    SQL_CONNECT_CONNECTED_PARAMS sqlConnectedParams;
} DATASOURCE;





// ====================================================================
//
//  Return codes. See also objectty.h.
//
// ====================================================================
typedef DWORD SMS_STATUS;           // All APIs return an SMS_STATUS.

#define SMS_OK                          OTT_OK
#define SMS_MORE_DATA                   OTT_MORE_DATA
#define SMS_NO_MORE_DATA                OTT_NO_MORE_DATA
#define SMS_FOLDER_NO_UPDATE            OTT_FOLDER_NO_UPDATE

// Error codes when registering (and accessing) containers and filters
#define SMS_DUPLICATE_CONTAINER_ID      OTT_DUPLICATE_CONTAINER_ID
#define SMS_DUPLICATE_FOLDER_ID         OTT_DUPLICATE_FOLDER_ID
#define SMS_DUPLICATE_FILTER_ID         OTT_DUPLICATE_FILTER_ID

#define SMS_DUPLICATE_FILTER            OTT_DUPLICATE_FILTER

#define SMS_SCALAR_NO_UPDATE            OTT_SCALAR_NO_UPDATE
#define SMS_SCALAR_WRONG_TYPE           OTT_SCALAR_WRONG_TYPE
#define SMS_INVALID_CONTAINER_ID        OTT_INVALID_CONTAINER_ID
#define SMS_INVALID_FOLDER_ID           OTT_INVALID_FOLDER_ID
#define SMS_INVALID_FILTER_ID           OTT_INVALID_FILTER_ID

#define SMS_CONTAINER_NO_UPDATE         OTT_CONTAINER_NO_UPDATE

#define SMS_PARAMETER_ERROR             OTT_PARAMETER_ERROR
#define SMS_UNSUPPORTED                 OTT_UNSUPPORTED

// This is returned when a specific object
// (folder or scalar) is requested and not
// found. APIs returning this are GetFolderByID
// and GetScalarByName.
#define SMS_NOT_FOUND                   OTT_NOT_FOUND

#define SMS_PARENT_NOT_FOUND            OTT_PARENT_NOT_FOUND

#define SMS_CANT_DELETE                 OTT_CANT_DELETE

#define SMS_NEW_FOLDER                  OTT_NEW_FOLDER

// Error when attempting to multiply
// link a folder.
#define SMS_FOLDER_LINKED               OTT_FOLDER_LINKED

// Filter operations.
#define SMS_RANGE_ERROR                 OTT_RANGE_ERROR

// These are returned when a container
// operation is tried when it shouldn't be.
#define SMS_CONTAINER_NOT_POPULATED     OTT_CONTAINER_NOT_POPULATED
#define SMS_CONTAINER_POPULATED         OTT_CONTAINER_POPULATED


// Attempt to perform persistent operation
// on a non-persistent filter.
#define SMS_FILTER_NOT_PERSISTENT       OTT_FILTER_NOT_PERSISTENT

// Error return if the connection handle
// of a filter doesn't match that of a
// container to which the filter is being
// applied.
#define SMS_INVALID_CONNECTION_HANDLE   OTT_INVALID_CONNECTION_HANDLE
#define SMS_INVALID_FILTER_TYPE         OTT_INVALID_FILTER_TYPE

// Folder's can't be unlinked if there are multiple handles
// to the same object.
#define SMS_IN_USE_BY_OTHER             OTT_IN_USE_BY_OTHER

// User (ie non-engine) codes begin here.
#define SMS_ERROR                       (OTT_END + 1)
#define SMS_SQL_ERROR                   (OTT_END + 2)
#define SMS_INVALID_DATASOURCE          (OTT_END + 3)
#define SMS_INVALID_HANDLE              (OTT_END + 4)
#define SMS_INVALID_FOLDER_TYPE         (OTT_END + 6)

#define SMS_CONNECT_FAILED              (OTT_END + 7)
#define SMS_NO_CREATE                   (OTT_END + 8)
#define SMS_FOLDER_NOT_MODIFIED         (OTT_END + 9)
#define SMS_INCORRECT_FOLDER_TYPE       (OTT_END + 10)  // Unused.
#define SMS_INVALID_PARAMETER           (OTT_END + 11)
#define SMS_EMPTY                       (OTT_END + 12)

// Return when commiting a child folder
// and the parent folder must be committed.
#define SMS_PARENT_NEEDS_COMMIT         (OTT_END + 13)
#define SMS_PARENT_ALREADY_COMMITTED    (OTT_END+ 14)

// Used in asynchronous folder retrieval.
// Indicates that there might be more
// data but it isn't available yet.
#define SMS_NOT_READY                   (OTT_END + 15)

#define SMS_FILTER_NO_MODIFY            (OTT_END + 16)
#define SMS_FOLDER_ALREADY_DELETED      (OTT_END + 17)

// Only allow one active connection.
// This is an SMS restriction.
#define SMS_ALREADY_CONNECTED           (OTT_END + 18)

// Some failure in committing a folder
#define SMS_COMMIT_FAILED               (OTT_END + 19)


// Specific failure in linking a folder
#define SMS_DUPLICATE_FOLDER            (OTT_END + 20)


// ====================================================================
//
//  Various manifests.
//
// ====================================================================

// The location of the SMS registry root.
#define SMS_REG_ROOT "SOFTWARE\\Microsoft\\SMS\\"

// The max size of character (string) data that we return.
#define SMS_DATA_BUFF_SIZE  255


// 'SMSBUFF' and 'OBJDESCRIPTOR' used in object type enumeration APIs.
// ===================================================================

// A character buffer.
// -------------------
typedef char SMSBUFF[SMS_DATA_BUFF_SIZE+1];

// Describes an object returned from SmsEnumObjects.
// -------------------------------------------------
typedef struct _OBJDESCRIPTOR {
    DWORD objType;                  // Type of this object.
    SMSBUFF szName;                 // Object name (eg 'Personal Computer')
    SMSBUFF szFriendlyName;         // Friendly name. Only used in groups
                                    // where szName would be, eg,
                                    // 'MICROSOFT|IDENTIFICATION|1.0', the
                                    // friendly name would be 'Identification'.
    BOOL bGotFriendlyName;          // TRUE if we have a friendly name.

    DWORD dwRelopMin;               // For attributes, indicates range of
    DWORD dwRelopMax;               // relational operators that can be used
                                    // for this attribute.
    BOOL bGotRelops;                // TRUE if we have the relops fields set.

} OBJDESCRIPTOR;


// Object types.
// =============
// This is the value that is inserted by the object
// enumeration APIs into the OBJDESCRIPTOR structure.
// --------------------------------------------------
#define OT_ARCHLIST         1
#define OT_ARCH             2
#define OT_GROUP            3
#define OT_ATTRIBUTE        4

#define OT_PLATFORMS        5
#define OT_PLATFORM_PDF     6
#define OT_PLATFORM_WINST   7
#define OT_PLATFORM_NAD     8

#define OT_UNKNOWN          100




// --------------------------------------------------------------------
// Flags for Populate options.
// --------------------------------------------------------------------
#define POP_SYNC            0x00000000
#define POP_ASYNC           0x00000001
#define POP_EVENT           0x00000010
#define POP_WINDOW          0x00000020


// --------------------------------------------------------------------
// Folder types supported by smsapi (MUST NOT BEGIN AT ZERO).
// --------------------------------------------------------------------
#define F_SITE              1               // Site folder.
#define F_MACHINE           2               // Machine folder.
#define F_GROUP             3               // Subfolder of machine
#define F_DOMAIN            4               // Domain folder, subfolder
                                            // of a site.
// Jobs
#define F_SYSTEMJOB         5               // System (NAD/Site) job folder.
//#define F_MINIJOB           6               // Mini-job folder.
#define F_INSTALLJOB        7               // Job folder (wksta install).
#define F_SRVINSTALLJOB     8               // Job folder (server install).
#define F_REMPKGJOB         9               // Remove package Job folder.

#define F_PACKAGE           10              // Packages.
#define F_WCL               11              // Workstation command lines.
#define F_PROGITEM          12              // Program items.
#define F_INVENTORY         13              // Inventory rules.

#define F_MACHINEGROUP      14              // Machine group
#define F_SITEGROUP         15              // Site group folder

// --------------------------------------------------------------------
// Container types supported by smsapi (MUST NOT BEGIN AT ZERO).
// --------------------------------------------------------------------
#define C_SITE              1               // Site container.
#define C_JOB               2               // Job container.
#define C_MACHINE           3               // Machine container.
#define C_PACKAGE           4               // Package container.
#define C_MACHINEGROUP      5               // Machine group
#define C_SITEGROUP         6               // Site group


// ====================================================================
//
//      Filter information.
//
// ====================================================================


// --------------------------------------------------------------------
//  Filter types
// --------------------------------------------------------------------
#define SITE_FILTER         1
#define MACHINE_FILTER      2
#define GROUP_FILTER        3
#define JOB_FILTER          4
#define ARCHITECTURE_FILTER 5
#define PACKAGE_FILTER      6
#define ATTRIBUTE_FILTER    7
#define SITELIMIT_FILTER    8


// --------------------------------------------------------------------
// Token types.
// --------------------------------------------------------------------
#define TOKEN_USER          0x8    // 1000 bit 3 always set for user-token
#define TOKEN_OR            0x2    // 0010 bit 1 always set for AND/OR
#define TOKEN_AND           0x3    // 0011 bit 1 always set for AND/OR
#define TOKEN_OPENPAREN     0x4    // 0100 bit 2 always set for PAREN
#define TOKEN_CLOSEPAREN    0x5    // 0101 bit 2 always set for PAREN
#define TOKEN_NOTIN         0x20   //10100 bit 2 set for a PAREN plus bit 4 for an extra indicator.
#define TOKEN_OPERATOR      0x2    // Detects both AND or OR
#define TOKEN_PAREN         0x4    // Detects either open or close paren


// --------------------------------------------------------------------
// Manifests used in filter token APIs.
// --------------------------------------------------------------------
#define AT_START        OTT_AT_START    // Token will be inserted at start of
                                        // expression.
#define AT_END          OTT_AT_END      // Token will be appended to end of
                                        // expression.

//
// Flags field in SmsManipulateTokens.
//
#define TOK_GROUP           1
#define TOK_UNGROUP         2
#define TOK_DELETE          3
#define TOK_GROUP_NOT       4


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
///////////     The APIs     ////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////


// **************************************************************************
//
//  This DLL provides a "C" interface for accessing SMS objects.
//
//===========================================================================
//
//  SmsAPIVer
//
//  This API returns a version string to identify the SMS API version.
//
//  Parameters:
//      char **ppVersion                The version string is returned
//                                      in this pointer.
//                                      The user must not free this memory,
//                                      it is a static buffer inside the API
//                                      dll.
//
//  Returns:
//      SMS_STATUS                      Always SMS_OK.
//
//===========================================================================
//
//===========================================================================
//  1.  Connection APIs.
//===========================================================================
//
//  SmsDataSourceConnect
//
//  This API connects to the datasource as specified in the DATASOURCE
//  parameter. The API returns a connection handle in the second
//  parameter.
//  This handle is passed to OpenContainer.
//
//  Parameters:
//      DATASOURCE *pd                  Pointer to DATASOURCE structure.
//                                      The user must have already set up
//                                      the appropriate parameters in this
//                                      structure. For SQL this contains
//                                      the server name, user name, password,
//                                      database, public encryption key, and
//                                      a pointer to a decryption function.
//                                      See the description above.
//      HANDLE *phConn                  Handle to a connection. This is
//                                      filled in by the API.
//
//  Returns:
//      SMS_STATUS                      Status. Either SMS_OK or one of the
//                                      error codes listed above.
//
//===========================================================================
//
//  SmsDataSourceDisconnect
//
//  This API releases a datasource connection that was established by
//  DataSourceConnect.
//
//  Parameters:
//      HANDLE hConn                    Handle to the connection to be closed.
//
//  Returns:
//      SMS_STATUS                      Status. Either SMS_OK or one of the
//                                      error codes listed above.
//
//===========================================================================
//
//  2.  Engine APIs.
//
//  These are straight "pass-through" APIs that just call the engine APIs
//  (in objectty.dll) directly. Here for name conformance and so to ensure
//  that smsapi.dll will get loaded before the engine.
//
//===========================================================================

//
//  SmsEnumContainers
//
//  This returns an array of pointers to FOLDER_INFO structures.
//  If the pData parameter is NULL the API sets pCount to the number of
//  containers registered. Thus, a user can call this API with a NULL
//  buffer to get the count, which enables the application to allocate
//  sufficient memory. If pData is non-NULL the API will copy up to
//  pCount FOLDER_INFO pointers into the data buffer. If that number
//  is less than the number of containers the count will be set as
//  previously described.
//  The data buffer is an array of pointers to FOLDER_INFO structures.
//  These point to memory in the engine's address space, it should
//  not be deallocated or modified.
//LATER: make this pointer to const.
//
//
//  Parameters:
//      FOLDER_INFO **pData         Pointer to array of FOLDER_INFO structures.
//      DWORD *pCount               Pointer to count of containers.
//
//  Returns:
//      SMS_STATUS                  OTT_OK: success.
//                                  OTT_MORE_DATA: passed buffer not
//                                      big enough. *pCount says how
//                                      many containers registered.
//
// ====================================================================
//
//  SmsEnumFilters
//
//  This API returns a list of all filters currently registered
//  in the filter registry. This list is actually an array of
//  FILTER_INFO structs.
//
//  The memory for this array must be allocated by the caller.
//  To determine the size of the array call this API with NULL as
//  the first parameter. This will result in the number of filters
//  being returned in pCount.
//
//
//  Parameters:
//      FILTER_INFO *paFI           Pointer to an array of FILTER_INFO
//                                  structures.
//                                  The user is responsible for allocating
//                                  (and deallocating) this memory.
//      DWORD *pCount               Pointer to count of filters.
//
//  Returns:
//      SMS_STATUS                  OTT_OK: success.
//                                  OTT_MORE_DATA: passed buffer not
//                                      big enough. *pCount says how
//                                      many containers registered.
//
// ==========================================================================
//
//  SmsEnumFolders
//
//  This API returns a list of all folders currently registered
//  in the folder registry. This list is actually an array of
//  FOLDER_INFO structs.
//
//  The memory for this array must be allocated by the caller.
//  To determine the size of the array call this API with NULL as
//  the first parameter. This will result in the number of filters
//  being returned in pCount.
//
//
//  Parameters:
//      FOLDER_INFO **pData         Pointer to an array of FOLDER_INFO structures.
//      DWORD *pCount               Pointer to count of folders.
//
//  Returns:
//      SMS_STATUS                  OTT_OK: success.
//                                  OTT_MORE_DATA: passed buffer not
//                                      big enough. *pCount says how
//                                      many containers registered.
//
// ==========================================================================
//
//  SmsDescribeFolder
//
//  This API retrieves information about a container/folder and returns
//  it in the FOLDER_INFO parameter (see description of FOLDER_INFO).
//  Because containers and folders share the same id space for their
//  tags, it is necessary for the caller to specify which one they are
//  interested in.
//  Note that the Enum... APIs return a set of objects, this API returns
//  only a single one.
//
//
//
//  Parameters:
//      BASETYPE tObjectity         T_CONTAINER or T_FOLDER
//                                  (do we want a container or folder).
//      DWORD dwTag                 Container/folder type.
//      FOLDER_INFO **ppFInfo       Store the retrieved FOLDER_INFO here.
//
//  Returns:
//      SMS_STATUS                  OTT_OK: success.
//                                  OTT_INVALID_CONTAINER_ID:
//                                  OTT_INVALID_FOLDER_ID:
//                                      The container/folder cannot be
//                                      located in the registry.
//
//===========================================================================
//  3.  Container APIs.
//===========================================================================
//
//  SmsOpenContainer
//
//  Opens a container of the specified type (cType). The container is opened
//  but is currently empty. The only operations that can be performed on it
//  in this state is SetFilter, Populate, and CloseContainer.
//  It is permissible to have multiple containers of the same type opened
//  simultaneously.
//  Only when a container has been populated does it have information that
//  can resonably be examined.
//  The container type is one of the C_xxx manifests in the list above.
//
//  Parameters:
//      DWORD cType                     Type of the container to open.
//                                      This should be one of thr C_xxx
//                                      manifests above.
//      HANDLE hConnect                 Handle to a connection that has been
//                                      established via SmsDataSourceConnect.
//      HANDLE *phContainer             Handle to the container, filled in by
//                                      the API.
//
//  Returns:
//      SMS_STATUS                      Status. Either SMS_OK or one of the
//                                      error codes listed above.
//
//===========================================================================
//
//  SmsSetFilter
//
//  This API submitts a filter to the container. The filter consists
//  of tokens (possibly grouped) which express conditions for folder
//  inclusion within a container.
//  Note: when applying multiple filters an implicit AND is performed between
//  filters.
//
//  Parameters:
//      HANDLE hContainer               Identifies the container.
//      HANDLE hFilter                  Handle to the filter to assign to
//                                      the container.
//
//  Returns:
//      SMS_STATUS                      Status. Either SMS_OK or one of the
//                                      error codes listed above.
//
//===========================================================================
//
//  SmsPopulate
//
//  This causes the container to be populated with folders according to the
//  filters applied to the container.
//  It should be noted that not all filters that are applied to a container
//  will be activated at this stage. For instance, applying an attribute
//  filter to a site container has no effect at this stage. However, the
//  filter is held internally within the system and will be applied to the
//  appropriate folder. For an attribute filter, its activation in a site
//  container would come at the level of a child domain folder. This
//  technique is known as percolating filters.
//  Containers are the only level at which filters can be applied at the
//  API level.
//  The dwOpts parameter allows the caller to specify whether the population
//  (and the folder retrieval) should be asynchronous or synchronous.
//  Synchronous is the default. These options are described earlier (see
//  "Populate options").
//  This parameter also specifies how the event handle should be set. The
//  event handle can be set by the API whenever a folder has been retrieved,
//  when all folders have been retrieved, or it can not be used at all (the
//  default).
//
//  A third parameter is an event handle. According
//
//  Parameters:
//      HANDLE hContainer               Identifies the container.
//      DWORD dwOptions                 Synchronous/asynch, event handle usage.
//      NOTIFY *pNotify                 Contains information about asynchronous
//                                      notification. NULL if synchronous.
//                                      parameter.
//  Returns:
//      SMS_STATUS                      Status. Either SMS_OK or one of the
//                                      error codes listed above.
//
//===========================================================================
//
//  SmsGetNextFolder
//
//  This API retrieves the next folder in a parent container or folder.
//
//  Parameters:
//      HANDLE hParent                  Identifies the parent (container or
//                                      folder).
//      DWORD fType                     Which type of sub-folder we want to
//                                      retrieve.
//      HANDLE *phFolder                Receives a handle to the next
//                                      folder in the parent.
//
//  Returns:
//      SMS_STATUS                      Status. Either SMS_OK or one of the
//                                      error codes listed above.
//
//===========================================================================
//
//  SmsCloseContainer
//
//  Closes a currently open container, and frees resources held be the
//  container.
//  It is possible to open a container's child folders and then close the
//  container. This has no adverse effects on either the folders or on any
//  filters that have been applied to the container.
//
//  Parameters:
//      HANDLE hContainer               Identifies the container.
//
//  Returns:
//      SMS_STATUS                      Status. Either SMS_OK or one of the
//                                      error codes listed above.
//
//===========================================================================
//  4.  Folder APIs.
//===========================================================================
//
//  SmsCreateFolder
//
//  This API attempts to create a folder (initally empty) of the specified
//  type. Folder creation is done in the context of a parent (folder or
//  container). Not all containers/folder support folder creation.
//  Once created, a folder must have its scalars set by the application.
//  Failure to do so will result in the system not accepting the newly
//  created folder. See DescribeFolder for information on retrieving details
//  about a folder's scalars.
//
//  Parameters:
//      HANDLE hParent                  Identifies the parent (can be either
//                                      container or folder).
//      DWORD fType                     The type of folder to create. See
//                                      the list of folders above).
//      char *pszFolderID               A name to give the folder. Not all
//                                      creatable folders can be named by the
//                                      user. In many cases SMS itself will
//                                      assign the name.
//      HANDLE *phFolder                Receives a handle to the newly-created
//                                      folder (if successful).
//
//  Returns:
//      SMS_STATUS                      Status. Either SMS_OK or one of the
//                                      error codes listed above.
//
//===========================================================================
//
//  SmsGetFolderID
//
//  This API retrives the ID/name of the folder referenced by the folder handle.
//
//  Parameters:
//      HANDLE hFolder                  Which folder object we're talking about.
//      char *pszFolderID               Pointer to buffer to receive the
//                                      folder's ID. It is the caller's
//                                      responsibility to ensure that this
//                                      buffer is large enough. If in doubt
//                                      use of buffer of size SMS_DATA_BUFF_SIZE.
//                                      This is guaranteed to be sufficient.
//
//  Returns:
//      SMS_STATUS                      Status. Either SMS_OK or one of the
//                                      error codes listed above.
//
//===========================================================================
//
//  SmsGetFolderType
//
//  This API retrieves the folder's type as both an integer value and as
//  a character string. For instance invoking this API on a domain folder
//  will result in a type string of "Domain folder" and an integer type of
//  F_DOMAIN being returned. The caller is responsible for ensuring that
//  the character buffer is of sufficient size.
//
//  Parameters:
//      HANDLE hFolder                  The folder to query.
//      DWORD *pfType                   Receive's the folder's type (integer).
//      char *pszfType                  Receives folder's type (as a string).
//
//  Returns:
//      SMS_STATUS                      Status. Either SMS_OK or one of the
//                                      error codes listed above.
//
//===========================================================================
//
//  SmsEnumFolderTypes
//
//  This API returns an array of DWORDs which indicate what folder types
//  CAN be contained within this folder. It is the caller's responsibility
//  to ensure that the DWORD array (*pfTypes) is of sufficient size.
//  Calling this API with pfTypes of NULL or with *pctFolderTypes of 0,
//  will result in the correct count being returned to the caller in
//  pctFolderTypes.
//  If the *pctFolderTypes is less than the number of folders, then up to
//  *pctFolderTypes are returned in the DWORD array, and a status of
//  SMS_MORE_DATA is returned.
//  If *pctFolderTypes is greater than the number of folders then the maximum
//  number of folder types will be stored in the array, and a value of
//  PARAMETER_ERROR returned. *pctFolderTypes will be updated to indicate
//  the number of folder types.
//
//  Note the difference between this API and GetFolderCount. This returns
//  a list of sub-folder types that can be contained in the folder,
//  GetFolderCount returns a count of how many sub-folders of a specified
//  type actually are contained in the folder.
//
//  Parameters:
//      HANDLE hFolder                  The folder to query.
//      DWORD *pfTypes                  Points to an array of DWORD.
//                                      Filled in with the types of sub-
//                                      folders that this folder can contain.
//      DWORD *pctFolderTypes           How many types of sub-folders this
//                                      folder can contain.
//
//  Returns:
//      SMS_STATUS                      Status. Either SMS_OK or one of the
//                                      error codes listed above.
//
//===========================================================================
//
//  SmsGetFolderCount
//
//  This API returns (in the DWORD parameter) how many sub-folders of the
//  specified folder-type are contained in this folder.
//  Note that a DWORD of F_ANY means return the total count of sub-folders.
//
//  Parameters:
//      HANDLE hFolder                  The folder (or container) to query.
//      DWORD fType                     Which type of sub-folder we're
//                                      interested in. F_ANY means all types.
//      DWORD *pctFolders               Receives the count.
//
//  Returns:
//      SMS_STATUS                      Status. Either SMS_OK or one of the
//                                      error codes listed above.
//
//===========================================================================
//
//  SmsGetFolderByID
//
//  This API the retrieves from the folder a sub-folder of the specified
//  type and with a specified ID.
//  This method of folder retrieval is non-sequential. Once a sub-folder has
//  been retrieved it can be re-retrieved. It is always legal to open a
//  folder multiple times. Doing this will create multiple instances of a
//  folder. Thus, it is possible to retrieve a folder twice, close once
//  instance, and still have an instance of the folder available.
//  Note that a folder type of F_ANY is not accepted here, it will result
//  in a return code of SMS_INVALID_FOLDER_TYPE.
//  Note that a type of F_ANY is not allowed.
//
//
//  Parameters:
//      HANDLE hFolder                  The folder to query.
//      DWORD fType                     Which type of sub-folder we want to
//                                      retrieve (see GetFolderCount).
//      char *pszFolderID               The sub-folder's ID (name).
//      HANDLE *phSubFolder             Receives a handle to the sub-folder.
//
//  Returns:
//      SMS_STATUS                      Status. Either SMS_OK or one of the
//                                      error codes listed above.
//
//===========================================================================
//
//  SmsRewind
//
//  This API resets the internal counts of either a container, a folder, or
//  a filter so that contained sub-folders and/or scalars can be re-
//  enumerated.
//  Because GetNextFolder and GetNextScalar are sequential, once thay have
//  been retrieved once they cannot be re-retrieved with these APIs.
//  The Rewind API enbles the retrieval to be restarted.
//  The options parameter allows the user to specify that either the folder
//  list or the scalar list or both be rewound.
//
//
//  Parameters:
//      HANDLE hObject                  The container, folder, or filter
//                                      to be rewound.
//      DWORD  dwOptions                Rewind options:-
//                                      RW_FOLDER: rewind folder lists.
//                                      RW_SCALAR: rewind scalar lists.
//                                      RW_ALL:    both.
//
//                                      If the object is a container or
//                                      folder, a particular type of sub-
//                                      folder list may be rewound by passing
//                                      the child folder type in the
//                                      dwOptions parameter.
//
//                                      If the object is a filter container,
//                                      then a particular type of filter list
//                                      may be rewound by passing the filter
//                                      type in the dwOptions parameter.
//
//                                      If the object is a filter then only
//                                      RW_SCALAR is valid.
//
//  Returns:
//      SMS_STATUS                      Status. Either SMS_OK or one of the
//                                      error codes listed above.
//

//===========================================================================
//
//  SmsCloseFolder
//
//  This API closes the specified folder.
//  Closing a folder causes sub-folders to be closed and deallocated UNLESS
//  they have already been retrieved by a GetSubFolder/GetFolderByID call
//  in which case they remain open.
//  A folder's scalars are always closed and their memory deallocated.
//
//  Parameters:
//      HANDLE hFolder                  The folder to close.
//
//  Returns:
//      SMS_STATUS                      Status. Either SMS_OK or one of the
//                                      error codes listed above.
//
//===========================================================================
//
//  SmsLinkFolder
//
//  This API inserts the specified folder into the in-memory list of folders
//  and causes it to be linked to its parent (must still be open).
//  The folder is not written back to the datasource until CommitFolder is
//  called.
//
//  Parameters:
//      HANDLE hFolder                  The folder to insert.
//
//  Returns:
//      SMS_STATUS                      Status. Either SMS_OK or one of the
//                                      error codes listed above.
//
//===========================================================================
//
//  SmsUnlinkFolder
//
//  This API deletes the specified folder from the in-memory list of folders.
//  All memory associated with the folder is deallocated. However, the
//  folder is not deleted from the datasource until CommitFolder is called.
//
//  Parameters:
//      HANDLE hFolder                  The folder to delete.
//
//  Returns:
//      SMS_STATUS                      Status. Either SMS_OK or one of the
//                                      error codes listed above.
//
//===========================================================================
//
//  SmsCommitFolder
//
//  This API causes any changes in the specified folder to be written back to
//  the datasource.
//  This should be called after LinkFolder and UnlinkFolder in order to make
//  the changes permanent.
//  Note that a Commit following an Unlink will render the specified folder
//  unavailable to all operations (other that SmsCloseFolder).
//
//  Parameters:
//      HANDLE hFolder                  The folder to update (insert or delete).
//
//  Returns:
//      SMS_STATUS                      Status. Either SMS_OK or one of the
//                                      error codes listed above.
//
//===========================================================================
//
//  SmsDupFolder
//
//  This API causes the folder (hFolder) to be copied (into hNewFolder)
//  in the context of the specified parent (hParent - container or folder).
//
//  Parameters:
//      HANDLE hParent                  The parent folder in whose context
//                                      the new folder will be inserted.
//      HANDLE hFolder                  The folder to be duplicated
//      HANDLE *phNewFolder             The handle to the new folder
//                                      is returned here.
//
//  Returns:
//      SMS_STATUS                      Status. Either SMS_OK or one of the
//                                      error codes listed above.
//
//===========================================================================
//  5.  Scalar APIs.
//===========================================================================
//
//  SmsGetScalarCount
//
//  This API returns the count of scalars in this folder.
//
//  Parameters:
//      HANDLE hFolder                  The folder to query.
//      DWORD *pctScalars               Receives the count of scalars.
//
//  Returns:
//      SMS_STATUS                      Status. Either SMS_OK or one of the
//                                      error codes listed above.
//
//===========================================================================
//
//  SmsGetNextScalar
//
//  This API retrieves the next scalar from the folder.
//  Scalars can either be retrieved in a sequential fashion (this API)
//  or by name (GetScalarByName). The RewindFolder API enables the sequential
//  enumeration of scalars to be restarted.
//
//  Parameters:
//      HANDLE hFolder                  The folder to query.
//      SCALAR *pScalar                 Pointer to a SCALAR that has been
//                                      allocated by the caller.
//                                      See notes on SCALAR for a full
//                                      description of this structure and
//                                      its use.
//  Returns:
//      SMS_STATUS                      Status. Either SMS_OK or one of the
//                                      error codes listed above.
//
//===========================================================================
//
//  SmsGetScalarByName
//
//  This API retrieves the scalar specified by its name.
//
//  Parameters:
//      HANDLE hFolder                  The folder to query.
//      const char *pszName             Name of the scalar.
//      SCALAR *pScalar                 Pointer to a SCALAR that has been
//                                      allocated by the caller.
//                                      See notes on SCALAR for a full
//                                      description of this structure and
//                                      its use.
//  Returns:
//      SMS_STATUS                      Status. Either SMS_OK or one of the
//                                      error codes listed above.
//
//===========================================================================
//
//  SmsSetScalar
//
//  This API is used to set the value of a scalar. It is used when creating a
//  folder. In the future it will also be used to modify the value of a
//  scalar in an existing folder.
//  The set of scalars supported by a folder is always known at the time a
//  folder is opened, this is true even when a folder is being created.
//  Scalars have a name, a type, and a value. This API allows the value to
//  be set. Only values of the correct type are allowed. Attempting to set,
//  for instance, an integer value in a string scalar will result in a
//  SMS_SCALAR_WRONG_TYPE error return.
//  The API set supports the notion of access rights on folders and scalars,
//  in order for this API to succeed the caller must have the correct
//  access to both. Failure results in an error return of SMS_SCALAR_NO_UPDATE
//  or SMS_FOLDER_NO_UPDATE.
//
//  Parameters:
//      HANDLE hFolder                  The folder containing the scalar.
//      SCALAR *pScalar                 Pointer to a SCALAR that has been
//                                      allocated and filled in by the caller.
//                                      See notes on SCALAR for a full
//                                      description of this structure and
//                                      its use.
//  Returns:
//      SMS_STATUS                      Status. Either SMS_OK or one of the
//                                      error codes listed above.
//
//===========================================================================
//  6.  Filter container APIs.
//===========================================================================
//
//  SmsOpenFilterContainer
//
//  The filter container is a storage mechanism for persistent filters,
//  currently only Machine Filters (SMS Queries) fall into this category.
//
//  Calling this API causes the filter container to be automatically populated
//  with all persistent filters in the system.
//
//  Parameters:
//      HANDLE hConnection              Which connection to use.
//      HANDLE *phFContainer            Receives the handle to the opened
//                                      filter container.
//
//  Returns:
//      SMS_STATUS                      Status. Either SMS_OK or an error code.
//                                      LIST POSSIBLE ERROR CODES HERE.
//
//===========================================================================
//
//  SmsCloseFilterContainer
//
//  Closes the filter container. All filters container herein that have
//  not been explicitly opened are closed and the memory associated with
//  them is freed.
//
//  Parameters:
//      HANDLE hFContainer              The handle to the filter container.
//
//  Returns:
//      SMS_STATUS                      Status. Either SMS_OK or an error code.
//                                      LIST POSSIBLE ERROR CODES HERE.
//
//===========================================================================
//
//  SmsGetNextFilter
//
//  This returns (in *phFilter) a handle to the next sequential filter of
//  the specified type from the filter container (specified by hFContainer).
//  A filter type of F_ANY is not acceptable.
//
//  Parameters:
//      HANDLE hFContainer              Handle to the filter container.
//      DWORD frType                    Filter type.
//      HANDLE *phFilter                Handle to the filter returned here.
//
//  Returns:
//      SMS_STATUS                      Status. Either SMS_OK or an error code.
//                                      LIST POSSIBLE ERROR CODES HERE.
//
//===========================================================================
//
//  SmsGetFilterByID
//
//  The API will return (in *phFilter) a handle to the filter of the specified
//  type which has the specified ID.
//  As above, the handle to the filter container is also passed into the API.
//  A filter type of F_ANY is not acceptable.
//
//  Parameters:
//      HANDLE hFContainer              Handle to the filter container.
//      DWORD frType                    Filter type.
//      const char *pszID               ID of the filter to retrieve.
//      HANDLE *phFilter                Handle to the filter returned here.
//
//  Returns:
//      SMS_STATUS                      Status. Either SMS_OK or an error code.
//                                      LIST POSSIBLE ERROR CODES HERE.
//
//===========================================================================
//
//  SmsGetFilterID
//
//  This returns, in pszID, the ID of the filter specified by the handle.
//
//  Parameters:
//      HANDLE hFilter
//      char *pszID
//
//  Returns:
//      SMS_STATUS                      Status. Either SMS_OK or an error code.
//                                      LIST POSSIBLE ERROR CODES HERE.
//
//===========================================================================
//
//  SmsCommitFilter
//
//  This API will attempt to make the specified filter persistent. The filter
//  must be of a type that supports persistence, and all manadatory scalars
//  for the filter must have been set.
//
//  Parameters:
//      HANDLE hFilter
//      HANDLE hFContainer
//
//  Returns:
//      SMS_STATUS                      Status. Either SMS_OK or an error code.
//                                      LIST POSSIBLE ERROR CODES HERE.
//
//===========================================================================
//
//===========================================================================
//  7.  Filter APIs.
//===========================================================================
//
//  SmsCreateFilter
//
//  This API creates a filter of the specified type, initially empty. The
//  caller must then set tokens in this filter.
//  Filter types are listed above.
//
//  Parameters:
//      DWORD fType                     Type of filter to create.
//      HANDLE hConnection              Filters are associated with a
//                                      connection.
//      HANDLE *phFilter                Receives a handle to the filter.
//  Returns:
//      SMS_STATUS                      Status. Either SMS_OK or one of the
//                                      error codes listed above.
//
//============================================================================
//
//  SmsCloseFilter
//
//  Close the specified filter and deallocate any memory asociated with it.
//  Once a filter has been applied to a container (SetFilter), the user is
//  free to close it. The API system has made it own copy which will be freed
//  when no longer necessary.
//
//  Parameters:
//      HANDLE hFilter                  The filter to close.
//
//  Returns:
//      SMS_STATUS                      Status. Either SMS_OK or one of the
//                                      error codes listed above.
//
//============================================================================
//
//  SmsGetFilterType
//
//  This API gets the type for a particular filter. Using this type it is
//  possible to get the filter template.
//  Parameters:
//      HANDLE hFilter                  The filter to retrieve the type for.
//      DWORD *pfilterType              The filter type is returned here.
//      char *pszTag                    The filter tag is returned here.
//
//  Returns:
//      SMS_STATUS                      Status. Either SMS_OK or one of the
//                                      error codes listed above.
//
//===========================================================================
//
//  SmsGetToken
//
//  This API retrieves a token from the specified filter or folder. The token
//  to retrieve is given by the index parameter. See also SmsGetTokenCount.
//  The TOKEN structure is detailed in the file objectty.h.
//
//  Parameters:
//      HANDLE hObject                  Handle to filter or folder.
//      INT iIndex
//      TOKEN *pTokenInfo
//
//  Returns:
//      SMS_STATUS                      Status. Either SMS_OK or one of the
//                                      error codes listed above.
//
//===========================================================================
//
//  SmsAddToken
//
//  This API allows the caller to add a token into a filter (or folder). The
//  ANDOR parameter specifies if the token is to be ANDed or ORed with the
//  preceeding token. The index specifies whereabout in the filter expression
//  the token is to be inserted. The rules are as follows:
//  1. index is AT_START (-1), the token will be inserted at the start of the
//     expression and the ANDOR operator will be postfixed.
//  2. index is AT_END (-2), the token will be appended to the end of the
//     expression, the ANDOR operator will prefix the token.
//  3. if index is anything else, if the expression is currently empty then
//     the token will be inserted at the start of the expression, and the
//     ANDOR operator is ignored. If the expression is not empty then the
//     token will be inserted at the given index and the operator prefixed.
//     The exception here is if the index is out of range, in this case the
//     token will be appended with the ANDOR being prefixed.
//     In all cases, if inserting the token would cause the resulting
//     expression to be illegal a status of SMS_RANGE_ERROR will be returned.
//
//  Parameters:
//      HANDLE hObject                  Handle to filter or folder.
//      ANDOR opAndOr
//      TOKEN *pTokenInfo
//      INT iIndex
//
//  Returns:
//      SMS_STATUS                      Status. Either SMS_OK or one of the
//                                      error codes listed above.
//
//===========================================================================
//
//  SmsGetTokenCount
//
//  This API will return (in *pctTokens) the number of tokens currently in
//  the filter or folder expression.
//
//  Parameters:
//      HANDLE hObject                  Handle to either filter or folder.
//      DWORD *pctTokens
//
//  Returns:
//      SMS_STATUS                      SMS_OK, or SMS_INVALID_HANDLE.
//
//===========================================================================
//
//  SmsManipulateTokens
//
//  This APIs allows for the manipulation of tokens within a filter or folder
//  expression in various ways, according to the flags parameter.
//  TOK_GROUP       The tokens between the specified indicies are grouped
//                  together to form a sub-expression, ie they are backeted by
//                  parentheses.
//  TOK_UNGROUP     The tokens between the specified indicies have their
//                  parenthesis removed. This undoes the action of TOK_GROUP.
//  TOK_DELETE      The tokens within the specified indecies are deleted.
//                  In this case the tokens must not form a legal sub-
//                  expression.
//  TOK_GROUP_NOT   This is applicable only to persistent filters. At the
//                  moment that means only machine filters.
//                  This flag is applied to a range of one or more tokens that
//                  form a legal sub-expression. That is, a range of tokens
//                  that can ge grouped. The action performed by this is to
//                  group these tokens and preceed them with a 'NOT IN'
//                  token. This has the effect of specifying exclusion.
//
//  The user may use the manifests AT_START and AT_END to indicate
//  the full range of tokens within the filter or folder object.
//  The iStart and iEnd may be one of the following:
//  1. AT_START (-1), the index will be at the start of the expression.
//  2. AT_END (-2), the index will be at the end of the expression.
//  3. For any other valid indexes, the tokens will be manipulated within the given indexes
//
//  Parameters:
//      HANDLE hObject                  Handle to either filter or folder.
//      DWORD dwFlags
//      INT iStart
//      INT iEnd
//
//  Returns:
//      SMS_STATUS                      Status. Either SMS_OK or one of the
//                                      error codes listed above.
//
//===========================================================================
//
//  SmsGetAllFilters
//
//  This API retrieves from the specified container a list of filter handles
//  that have been applied to that container.
//  It is important to note that once this has been called, the API
//  SmsCloseFilter must be called for each of the filters in the array.
//
//  Calling this with NULL for the array of filters will cause the *pctFilters
//  parameter to be set with the number of filters, in this case the API
//  will return a status of SMS_MORE_DATA.
//  The user should then allocate sufficient memory and call the API again.
//
//  Note that the container specified here is a normal (ie folder) container
//  and not a filter container.
//
//  Parameters:
//      HANDLE hContainer
//      HANDLE *pahFilters
//      DWORD *pctFilters
//
//  Returns:
//      SMS_STATUS                      Status. Either SMS_OK or one of the
//                                      error codes listed above.
//
//===========================================================================
//
//===========================================================================
//  8.  Object enumeration APIs.
//===========================================================================
//
//  SmsEnumObjectTypes
//
//  This API returns a list of first-class objects that are known to the
//  API.
//  These objects do not have a direct existence in the container hierarchy,
//  but play an important part in the API. The objects of major concern are
//  architectures and their descendents, but Platforms are also supported.
//
//  A first-class object is one that is known directly to the APIs and which
//  does not require any additional informaion. Thus the system knows
//  directly about architectures and platforms, while it cannot know about,
//  for instance, attributes, without first knowing about an architecture
//  and a groupclass.
//
//  The 'pObjects' parameter is an array of SMSBUFF objects. On successful
//  completion of the API this array will be filled with the names of
//  each first-class object known to the system.
//
//  On entry the 'pCtObjects' parameter tells the API the size of the
//  pObjects array. On exit it contains the actual number of objects
//  known to the system.
//  If this parameter is less than the number of objects known to the system
//  then it is still set to the total, but no information will have been
//  copied to the pObjects array, and a status of SMS_MORE_DATA will be
//  returned.
//
//  Parameters:
//      HANDLE hConnection              Handle to a connection that has been
//                                      established via SmsDataSourceConnect.
//      SMSBUFF *pObjects
//      DWORD *pCtObjects
//
//  Returns:
//      SMS_STATUS                      Status. Either SMS_OK or one of the
//                                      error codes listed above.
//
//===========================================================================
//
//  SmsEnumObjects
//
//  This object actually does the work of enumerating objects. For first-
//  class objects (see above) the 'pPredecessor' parameter is not used,
//  in this case it may be set to NULL. For non first-class objects this
//  list states the predecessor objects that must be given to the system
//  in order for it to locate the requested object.
//
//  The 'ctPredecessors' parameter tells the API the number of entries in the
//  predecessor list.
//
//  'pszObjectType' tells the API what object type the user is interested in.
//
//  'pObjects' is an array of OBJDESCRIPTORS, this array will be filled in
//  with details of the requested object type.
//
//  'pCtObjects' is a pointer to a DWORD. On entry it tells the API the number
//  of entries in 'pObjects'. On exit it is always set to then count of
//  objects of the specified type. If the entry value is less than the actual
//  number of objects then no data is copied and a status of SMS_NMO_MORE_DATA
//  is returned.
//
//  Consider an example.
//  If we want to enumerate the attributes in the 'MICROSOFT|IDENTIFICATION|1.0'
//  groupclass for 'Personal Computer' objects then we would set the parameters
//  as follows:
//      pszObjectType    = "MICROSOFT|IDENTIFICATION|1.0"
//      pPredecessors[0] = "Architectures"
//      pPredecessors[1] = "Personal Computer"
//      ctPredecessors   = 2
//      pObjects - you can declare it as 'OBJDESCRIPTOR pObjects[SOME_SIZE]'
//      *pCtObjects      = SOME_SIZE
//
//  On exit the pObjects array would have 9 entries (as currently defined,
//  this can change). The first entry would look like this:
//      pObjects[0].objType          = OT_ATTRIBUTE
//      pObjects[0].szName           = 'Name"
//      pObjects[0].szFriendlyName - unused
//      pObjects[0].bGotFriendlyName = FALSE
//      pObjects[0].dwRelopMin       = QOP_STR_EQ
//      pObjects[0].dwRelopMax       = QOP_UPCASE_NOTLIKE
//      pObjects[0].bGotRelops       = TRUE

//  Parameters:
//      HANDLE hConn
//      char *pszObjectType
//      SMSBUFF *pPredecessors
//      DWORD ctPredecessors
//      OBJDESCRIPTOR *pObjects
//      DWORD *pCtObjects
//
//  Returns:
//      SMS_STATUS                      Status. Either SMS_OK or one of the
//                                      error codes listed above.
//
//===========================================================================



// ====================================================================
//      Version number API.
// ====================================================================
__declspec (dllexport) SMS_STATUS SmsAPIVer( char **ppVersion );


// ====================================================================
//      Engine APIs.
// ====================================================================

__declspec (dllexport) SMS_STATUS SmsEnumContainers(
                FOLDER_INFO **pData,
                DWORD *pCount );

__declspec (dllexport) SMS_STATUS SmsEnumFilters(
                FILTER_INFO *paFI,
                DWORD *pCount );

__declspec (dllexport) SMS_STATUS SmsEnumFolders(
                FOLDER_INFO **pData,
                DWORD *pCount );

__declspec (dllexport) SMS_STATUS SmsDescribeFolder(
                BASETYPE tObjectity,        // T_CONTAINER or T_FOLDER.
                DWORD dwTag,                // folder type (or F_ANY)
                FOLDER_INFO **ppFInfo );    // We store the FOLDER_INFO here.


// ====================================================================
//      Connection APIs.
// ====================================================================
__declspec (dllexport) SMS_STATUS SmsDataSourceConnect(
                                DATASOURCE *pd,
                                HANDLE *phConn );

__declspec (dllexport) SMS_STATUS SmsDataSourceDisconnect(
                                HANDLE hConn );


// ====================================================================
//      Container APIS.
// ====================================================================
__declspec (dllexport) SMS_STATUS SmsOpenContainer(
                                DWORD cType,
                                HANDLE hConnection,
                                HANDLE *phContainer );

__declspec (dllexport) SMS_STATUS SmsSetFilter(
                                HANDLE hContainer,
                                HANDLE hFilter );

__declspec (dllexport) SMS_STATUS SmsPopulate(
                                HANDLE hContainer,
                                DWORD dwOptions,
                                NOTIFY *pNotify );

__declspec (dllexport) SMS_STATUS SmsGetNextFolder(
                                HANDLE hParent,
                                DWORD fType,
                                HANDLE *phFolder );

__declspec (dllexport) SMS_STATUS SmsCloseContainer(
                                HANDLE hContainer );

// ====================================================================
//  Folder (collection) APIs.
//  A collection contains other things, that is it can have embedded
//  collections and it can also have properties (scalars).
// ====================================================================

__declspec (dllexport) SMS_STATUS SmsCreateFolder(
                                HANDLE hParent,
                                DWORD fType,
                                const char *pszFolderID,
                                HANDLE *phFolder );

__declspec (dllexport) SMS_STATUS SmsGetFolderID(
                                HANDLE hFolder,
                                char *pszFolderID );

__declspec (dllexport) SMS_STATUS SmsGetFolderType(
                                HANDLE hFolder,
                                DWORD *pfType,
                                char *pszfType );

__declspec (dllexport) SMS_STATUS SmsEnumFolderTypes(
                                HANDLE hFolder,
                                DWORD *pfTypes,
                                DWORD *pctFolderTypes );

__declspec (dllexport) SMS_STATUS SmsGetFolderCount(
                                HANDLE hFolder,
                                DWORD fType,
                                DWORD *pctFolders );

__declspec (dllexport) SMS_STATUS SmsGetFolderByID(
                                HANDLE hFolder,
                                DWORD fType,
                                char *pszFolderID,
                                HANDLE *phSubFolder );

__declspec (dllexport) SMS_STATUS SmsRewind(
                                HANDLE hObject,
                                DWORD dwOptions );

__declspec (dllexport) SMS_STATUS SmsCloseFolder(
                                HANDLE hFolder );

__declspec (dllexport) SMS_STATUS SmsLinkFolder(
                                HANDLE hFolder );

__declspec (dllexport) SMS_STATUS SmsUnlinkFolder(
                                HANDLE hFolder );

__declspec (dllexport) SMS_STATUS SmsCommitFolder(
                                HANDLE hFolder );

__declspec (dllexport) SMS_STATUS SmsDupFolder(
                                HANDLE hParent,
                                HANDLE hFolder,
                                HANDLE *phNewFolder );

// ====================================================================
//  Scalar APIs.
// ====================================================================

__declspec (dllexport) SMS_STATUS SmsGetScalarCount(
                                HANDLE hFolder,
                                DWORD *pctScalars );

__declspec (dllexport) SMS_STATUS SmsGetNextScalar(
                                HANDLE hFolder,
                                SCALAR *pScalarStruct );

__declspec (dllexport) SMS_STATUS SmsGetScalarByName(
                                HANDLE hFolder,
                                const char *pszName,
                                SCALAR *pScalarStruct );

__declspec (dllexport) SMS_STATUS SmsSetScalar(
                                HANDLE hFolder,
                                SCALAR *pScalarStruct );



// ====================================================================
//
//  FilterContainer APIs
//
// ====================================================================

__declspec (dllexport) SMS_STATUS SmsOpenFilterContainer(
                                HANDLE hConnection,
                                HANDLE *phFContainer );

__declspec (dllexport) SMS_STATUS SmsCloseFilterContainer(
                                HANDLE hFContainer );

__declspec (dllexport) SMS_STATUS SmsGetNextFilter(
                                HANDLE hFContainer,
                                DWORD frType,
                                HANDLE *phFilter );

__declspec (dllexport) SMS_STATUS SmsGetFilterByID(
                                HANDLE hFContainer,
                                DWORD frType,
                                const char *pszID,
                                HANDLE *phFilter );

__declspec (dllexport) SMS_STATUS SmsGetFilterID(
                                HANDLE hFilter,
                                char *pszID );

__declspec (dllexport) SMS_STATUS SmsCommitFilter(
                                HANDLE hFilter,
                                HANDLE hFContainer );



// ====================================================================
//
//  Filter APIs
//
// ====================================================================

__declspec (dllexport) SMS_STATUS SmsCreateFilter(
                                DWORD frType,
                                HANDLE hConnection,
                                HANDLE *phFilter );

__declspec (dllexport) SMS_STATUS SmsCloseFilter(
                                HANDLE hFilter );

__declspec (dllexport) SMS_STATUS SmsGetFilterType(
                                HANDLE hFilter,
                                DWORD *pfilterType,
                                char *pszTag );

__declspec (dllexport) SMS_STATUS SmsGetToken(
                                HANDLE hObject,
                                INT iIndex,
                                TOKEN *pTokenInfo);

__declspec (dllexport) SMS_STATUS SmsAddToken(
                                HANDLE hObject,
                                ANDOR opAndOr,
                                TOKEN *pTokenInfo,
                                INT iIndex );

__declspec (dllexport) SMS_STATUS SmsGetTokenCount(
                                HANDLE hObject,
                                DWORD *pctTokens );

__declspec (dllexport) SMS_STATUS SmsManipulateTokens(
                                HANDLE hObject,
                                DWORD dwFlags,
                                INT iStart,
                                INT iEnd );

__declspec (dllexport) SMS_STATUS SmsGetAllFilters(
                                HANDLE hContainer,
                                HANDLE *pahFilters,
                                DWORD *pctFilters );


__declspec (dllexport) SMS_STATUS SmsEnumObjectTypes(
                                HANDLE hConnection,
                                SMSBUFF *pObjects,
                                DWORD *pCtObjects );

__declspec (dllexport) SMS_STATUS SmsEnumObjects(
                                HANDLE hConn,
                                char *pszObjectType,
                                SMSBUFF *pPredecessors,
                                DWORD ctPredecessors,
                                OBJDESCRIPTOR *pObjects,
                                DWORD *pCtObjects );


#ifdef __cplusplus
}
#endif

#endif  // _SMSAPI_H_

/* EOF: smsapi.h */

