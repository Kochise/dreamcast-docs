

//=============================================================================
//  Microsoft (R) Bloodhound (tm). Copyright (C) 1991-1992.
//
//  MODULE: bhsupp.h
//=============================================================================

#if !defined(_BHSUPP_)

#define _BHSUPP_

#pragma pack(1)

//=============================================================================
//  Windows version constants.
//=============================================================================

#define WINDOWS_VERSION_UNKNOWN     0
#define WINDOWS_VERSION_WIN32S      1
#define WINDOWS_VERSION_WIN32C      2
#define WINDOWS_VERSION_WIN32       3

//=============================================================================
//  Frame masks.
//=============================================================================

#define FRAME_MASK_ETHERNET         ((BYTE) ~0x01)
#define FRAME_MASK_TOKENRING        ((BYTE) ~0x80)
#define FRAME_MASK_FDDI             ((BYTE) ~0x01)

//=============================================================================
//  ACCESSRIGHTS
//=============================================================================

typedef enum _ACCESSRIGHTS
{
    AccessRightsNoAccess,               //... Access denied, invalid password.
    AccessRightsMonitoring,             //... Monitoring mode only.
    AccessRightsUserAccess,             //... User-level access rights.
    AccessRightsAllAccess               //... All access.
} ACCESSRIGHTS;

typedef ACCESSRIGHTS *PACCESSRIGHTS;

typedef LPVOID HPASSWORD;

#define HANDLE_TYPE_PASSWORD            MAKE_IDENTIFIER('P', 'W', 'D', '$')

//=============================================================================
//  Object heap type.
//=============================================================================

typedef LPVOID HOBJECTHEAP;                 //... Opaque.

//=============================================================================
//  Object cleanup procedure.
//=============================================================================

typedef VOID (WINAPI *OBJECTPROC)(HOBJECTHEAP, LPVOID);

#pragma pack()

//=============================================================================
//  Bloodhound timers.
//=============================================================================

typedef struct _TIMER *HTIMER;

typedef VOID (WINAPI *BHTIMERPROC)(LPVOID);

extern  HTIMER WINAPI BhSetTimer(BHTIMERPROC TimerProc, LPVOID InstData, DWORD TimeOut);

extern  VOID   WINAPI BhKillTimer(HTIMER hTimer);

//=============================================================================
//  Bloodhound driver support.
//=============================================================================

extern LPVOID WINAPI BhAllocSystemMemory(DWORD nBytes);

extern LPVOID WINAPI BhFreeSystemMemory(LPVOID ptr);

extern LPVOID WINAPI BhGetNetworkRequestAddress(DWORD NalRequestType);

//=============================================================================
//  Bloodhound global error API.
//=============================================================================

extern DWORD  WINAPI BhGetLastError(VOID);

extern DWORD  WINAPI BhSetLastError(DWORD Error);

//=============================================================================
//  Object manager function prototypes.
//=============================================================================

extern HOBJECTHEAP WINAPI CreateObjectHeap(DWORD ObjectSize, OBJECTPROC ObjectProc);

extern HOBJECTHEAP WINAPI DestroyObjectHeap(HOBJECTHEAP hObjectHeap);

extern LPVOID      WINAPI AllocObject(HOBJECTHEAP hObjectHeap);

extern LPVOID      WINAPI FreeObject(HOBJECTHEAP hObjectHeap, LPVOID ObjectMemory);

extern DWORD       WINAPI GrowObjectHeap(HOBJECTHEAP hObjectHeap, DWORD nObjects);

extern DWORD       WINAPI GetObjectHeapSize(HOBJECTHEAP hObjectHeap);

extern VOID        WINAPI PurgeObjectHeap(HOBJECTHEAP hObjectHeap);

//=============================================================================
//  Memory functions.
//=============================================================================

extern LPVOID     WINAPI AllocMemory(DWORD size);

extern LPVOID     WINAPI ReallocMemory(LPVOID ptr, DWORD NewSize);

extern VOID       WINAPI FreeMemory(LPVOID ptr);

extern VOID       WINAPI TestMemory(LPVOID ptr);

extern DWORD      WINAPI MemorySize(LPVOID ptr);

extern HANDLE     WINAPI MemoryHandle(LPBYTE ptr);

//=============================================================================
//  MS BTE format buffer API's.
//=============================================================================

extern HBUFFER    WINAPI BhAllocNetworkBuffer(DWORD NetworkID, DWORD BufferSize, LPDWORD nBytesAllocated);

extern HBUFFER    WINAPI BhFreeNetworkBuffer(HBUFFER hBuffer);

extern VOID       WINAPI BhCompactNetworkBuffer(HBUFFER hBuffer);

extern LPFRAME    WINAPI BhGetNetworkFrame(HBUFFER hBuffer, DWORD FrameNumber);

//=============================================================================
//  Password API's.
//=============================================================================

extern HPASSWORD    WINAPI CreatePassword(LPSTR password);

extern VOID         WINAPI DestroyPassword(HPASSWORD hPassword);

extern ACCESSRIGHTS WINAPI ValidatePassword(HPASSWORD hPassword);

//=============================================================================
//  EXPRESSION API's
//=============================================================================

extern LPEXPRESSION         WINAPI InitializeExpression(LPEXPRESSION Expression);

extern LPPATTERNMATCH       WINAPI InitializePattern(LPPATTERNMATCH Pattern, LPVOID ptr, DWORD offset, DWORD length);

extern LPEXPRESSION         WINAPI AndExpression(LPEXPRESSION Expression, LPPATTERNMATCH Pattern);

extern LPEXPRESSION         WINAPI OrExpression(LPEXPRESSION Expression, LPPATTERNMATCH Pattern);

extern LPPATTERNMATCH       WINAPI NegatePattern(LPPATTERNMATCH Pattern);

extern LPADDRESSTABLE       WINAPI AdjustOperatorPrecedence(LPADDRESSTABLE AddressTable);

extern LPADDRESS            WINAPI NormalizeAddress(LPADDRESS Address);

extern LPADDRESSTABLE       WINAPI NormalizeAddressTable(LPADDRESSTABLE AddressTable);

//=============================================================================
//  SERVICE API's
//=============================================================================

extern HANDLE               WINAPI BhOpenService(LPSTR ServiceName);

extern VOID                 WINAPI BhCloseService(HANDLE ServiceHandle);

extern DWORD                WINAPI BhStartService(HANDLE ServiceHandle);

extern DWORD                WINAPI BhStopService(HANDLE ServiceHandle);

//=============================================================================
//  MISC. API's
//=============================================================================

extern DWORD                WINAPI BhGetWindowsVersion(VOID);

extern BOOL                 WINAPI IsDaytona(VOID);

extern VOID                 dprintf(LPSTR format, ...);

#endif
