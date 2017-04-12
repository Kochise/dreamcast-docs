/*++ BUILD Version: 0001    // Increment this if a change has global effects

Copyright 1991-1998 Microsoft Corporation

Module Name:

    lmdfs.h

Abstract:

    This file contains structures, function prototypes, and definitions
    for the NetDfs API

Environment:

    User Mode - Win32

Notes:

    You must include <windef.h> and <lmcons.h> before this file.

--*/

#ifndef _LMDFS_
#define _LMDFS_

#ifdef __cplusplus
extern "C" {
#endif

//
// DFS Volume state
//

#define DFS_VOLUME_STATE_OK            1
#define DFS_VOLUME_STATE_INCONSISTENT  2
#define DFS_VOLUME_STATE_OFFLINE       3
#define DFS_VOLUME_STATE_ONLINE        4

//
// DFS Storage State
//

#define DFS_STORAGE_STATE_OFFLINE      1
#define DFS_STORAGE_STATE_ONLINE       2

//
// Level 1:
//
typedef struct _DFS_INFO_1 {
    LPWSTR  EntryPath;              // Dfs name for the top of this piece of storage
} DFS_INFO_1, *PDFS_INFO_1, *LPDFS_INFO_1;

//
// Level 2:
//
typedef struct _DFS_INFO_2 {
    LPWSTR  EntryPath;              // Dfs name for the top of this volume
    LPWSTR  Comment;                // Comment for this volume
    DWORD   State;                  // State of this volume, one of DFS_VOLUME_STATE_*
    DWORD   NumberOfStorages;       // Number of storages for this volume
} DFS_INFO_2, *PDFS_INFO_2, *LPDFS_INFO_2;

typedef struct _DFS_STORAGE_INFO {
    ULONG   State;                  // State of this storage, one of DFS_STORAGE_STATE_*
    LPWSTR  ServerName;             // Name of server hosting this storage
    LPWSTR  ShareName;              // Name of share hosting this storage
} DFS_STORAGE_INFO, *PDFS_STORAGE_INFO, *LPDFS_STORAGE_INFO;

//
// Level 3:
//
typedef struct _DFS_INFO_3 {
    LPWSTR  EntryPath;              // Dfs name for the top of this volume
    LPWSTR  Comment;                // Comment for this volume
    DWORD   State;                  // State of this volume, one of DFS_VOLUME_STATE_*
    DWORD   NumberOfStorages;       // Number of storage servers for this volume
#ifdef MIDL_PASS
    [size_is(NumberOfStorages)] LPDFS_STORAGE_INFO Storage;
#else
    LPDFS_STORAGE_INFO   Storage;   // An array (of NumberOfStorages elements) of storage-specific information.
#endif // MIDL_PASS
} DFS_INFO_3, *PDFS_INFO_3, *LPDFS_INFO_3;

//
// Level 100:
//
typedef struct _DFS_INFO_100 {
    LPWSTR  Comment;                // Comment for this volume or storage
} DFS_INFO_100, *PDFS_INFO_100, *LPDFS_INFO_100;

//
// Level 101:
//
typedef struct _DFS_INFO_101 {
    DWORD   State;                  // State of this storage, one of DFS_STORAGE_STATE_*
} DFS_INFO_101, *PDFS_INFO_101, *LPDFS_INFO_101;

//
// Add a new volume or additional storage for an existing volume at
// DfsEntryPath.
//
NET_API_STATUS NET_API_FUNCTION
NetDfsAdd(
    IN  LPWSTR DfsEntryPath,        // DFS entry path for this added volume or storage
    IN  LPWSTR ServerName,          // Name of server hosting the storage
    IN  LPWSTR ShareName,           // Existing share name for the storage
    IN  LPWSTR Comment OPTIONAL,    // Optional comment for this volume or storage
    IN  DWORD  Flags                // See below. Zero for no flags.
);

//
// Flags:
//
#define DFS_ADD_VOLUME          1   // Add a new volume to the DFS if not already there
#define DFS_RESTORE_VOLUME      2   // Volume/Replica is being restored - do not verify share etc.

//
// Remove a volume or additional storage for volume from the Dfs at
// DfsEntryPath. When applied to the last storage in a volume, removes
// the volume from the DFS.
//
NET_API_STATUS NET_API_FUNCTION
NetDfsRemove(
    IN  LPWSTR  DfsEntryPath,       // DFS entry path for this added volume or storage
    IN  LPWSTR  ServerName,         // Name of server hosting the storage
    IN  LPWSTR  ShareName           // Name of share hosting the storage
);

//
// Get information about all of the volumes in the Dfs. DfsName is
// the "server" part of the UNC name used to refer to this particular Dfs.
//
// Valid levels are 1-3.
//
NET_API_STATUS NET_API_FUNCTION
NetDfsEnum(
    IN      LPWSTR  DfsName,        // Name of the Dfs for enumeration
    IN      DWORD   Level,          // Level of information requested
    IN      DWORD   PrefMaxLen,     // Advisory, but -1 means "get it all"
    OUT     LPBYTE* Buffer,         // API allocates and returns buffer with requested info
    OUT     LPDWORD EntriesRead,    // Number of entries returned
    IN OUT  LPDWORD ResumeHandle    // Must be 0 on first call, reused on subsequent calls
);

//
// Get information about the volume or storage.
// If ServerName and ShareName are specified, the information returned
// is specific to that server and share, else the information is specific
// to the volume as a whole.
//
// Valid levels are 1-3, 100-101.
//
NET_API_STATUS NET_API_FUNCTION
NetDfsGetInfo(
    IN  LPWSTR  DfsEntryPath,       // DFS entry path for the volume
    IN  LPWSTR  ServerName OPTIONAL,// Name of server hosting a storage
    IN  LPWSTR  ShareName OPTIONAL, // Name of share on server serving the volume
    IN  DWORD   Level,              // Level of information requested
    OUT LPBYTE* Buffer              // API allocates and returns buffer with requested info
);

//
// Set info about the volume or storage.
// If ServerName and ShareName are specified, the information set is
// specific to that server and share, else the information is specific
// to the volume as a whole.
//
// Valid levels are 100 and 101.
//
NET_API_STATUS NET_API_FUNCTION
NetDfsSetInfo(
    IN  LPWSTR  DfsEntryPath,           // DFS entry path for the volume
    IN  LPWSTR  ServerName OPTIONAL,    // Name of server hosting a storage
    IN  LPWSTR  ShareName OPTIONAL,     // Name of share hosting a storage
    IN  DWORD   Level,                  // Level of information to be set
    IN  LPBYTE  Buffer                  // Buffer holding information
);

//
// Move a DFS volume and all subordinate volumes from one place in the
// DFS to another place in the DFS.
//
NET_API_STATUS NET_API_FUNCTION
NetDfsMove(
    IN  LPWSTR  DfsEntryPath,           // Current DFS entry path for this volume
    IN  LPWSTR  DfsNewEntryPath         // New DFS entry path for this volume
);

NET_API_STATUS NET_API_FUNCTION
NetDfsRename(
    IN  LPWSTR  Path,                   // Current Win32 path in a Dfs
    IN  LPWSTR  NewPath                 // New Win32 path in the same Dfs
);

#ifdef __cplusplus
}
#endif

#endif // _LMDFS_
