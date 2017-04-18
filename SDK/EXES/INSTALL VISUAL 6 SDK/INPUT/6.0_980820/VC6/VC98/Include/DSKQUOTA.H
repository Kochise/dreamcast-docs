/************************************************************************
*                                                                       *
*   dskquota.h --  public header for Windows NT disk quota interfaces.  *
*                                                                       *
*   Copyright 1991-1998, Microsoft Corp. All rights reserved.       *
*                                                                       *
************************************************************************/
#ifndef __DSKQUOTA_H
#define __DSKQUOTA_H

//
// This is the public header for the Windows NT disk quota control 
// COM library.  The interfaces are implemented in DSKQUOTA.DLL.
//
// Define the INITGUIDS macros in one source module (and only one source
// module) before including this header.  This will generate a single 
// definition for the GUIDs used by the library.
//
// DSKQUOTA.DLL is self-registering using REGSVR32.
//
//
// Interfaces -----------------------------------------------------------------
//
//      IDiskQuotaControl
//
//          Represents an NTFS volume for purposes of managing disk quota.
//          Instantiate this interface for each volume to be controlled.
//          Through it you can:
//              * Enable/Disable disk quotas.
//              * Obtain status of quota system on the volume.
//              * Deny disk space to users exceding their quota limit.
//              * Assign default warning threshold and quota limit values
//                to be used for new volume users.
//              * Locate a single user quota entry.
//              * Mark a user quota entry for deletion.
//              * Create an enumeration object for enumerating user quota
//                entries.
//              * Create a batch object for updating multiple user quota
//                entries efficiently.
//
//      IDiskQuotaUser
//
//          Represents a user quota entry on the volume.
//          Instantiated through IEnumDiskQuotaUsers, 
//              IDiskQuotaControl::FindUserSid or 
//              IDiskQuotaControl::FindUserName or
//              IDiskQuotaControl::AddUser
//
//          Through it you can:
//              * Set/Retrieve the user's quota warning threshold and quota
//                limit.
//              * Retrieve the user's quota amount "used" value.
//              * Retrieve the user's domain, account and friendly name.
//              * Retrieve the user's security ID (SID).
//
//      IEnumDiskQuotaUsers
//
//          Enumerates user quota entries on the volume.  Implements the
//          standard OLE IEnumXXXX interface.
//          Instantiated through IDiskQuotaControl::CreateEnumUsers.
//
//      IDiskQuotaUserBatch
//
//          Coordinates the update of multiple user quota entries into
//          a single call to NTFS.  Improves update efficiency when 
//          multiple entries must be updated.
//          Instantiated through IDiskQuotaControl::CreateUserBatch.
//
//      IDiskQuotaEvents
//
//          The DiskQuotaControl object services this interface as
//          an OLE connection point.  The connection point is used to
//          notify client code when a significant event has occured in
//          the quota system.  Currently, the only event supported is
//          the asynchronous update of a quota user object's name 
//          information.
//
// Interfaces [end] -----------------------------------------------------------
//          
//
#ifndef _WINDOWS_
#include <windows.h>
#endif

#ifndef _OLE2_H_
#include <ole2.h>
#endif

#ifndef _OLECTL_H_
#include <olectl.h>
#endif

#ifdef INITGUIDS
#include <initguid.h>
#endif


//
// Class IDs
//
// {7988B571-EC89-11cf-9C00-00AA00A14F56}
DEFINE_GUID(CLSID_DiskQuotaControl, 
0x7988b571, 0xec89, 0x11cf, 0x9c, 0x0, 0x0, 0xaa, 0x0, 0xa1, 0x4f, 0x56);

//
// Interface IDs
//
// {7988B572-EC89-11cf-9C00-00AA00A14F56}
DEFINE_GUID(IID_IDiskQuotaControl, 
0x7988b572, 0xec89, 0x11cf, 0x9c, 0x0, 0x0, 0xaa, 0x0, 0xa1, 0x4f, 0x56);

// {7988B574-EC89-11cf-9C00-00AA00A14F56}
DEFINE_GUID(IID_IDiskQuotaUser, 
0x7988b574, 0xec89, 0x11cf, 0x9c, 0x0, 0x0, 0xaa, 0x0, 0xa1, 0x4f, 0x56);

// {7988B576-EC89-11cf-9C00-00AA00A14F56}
DEFINE_GUID(IID_IDiskQuotaUserBatch, 
0x7988b576, 0xec89, 0x11cf, 0x9c, 0x0, 0x0, 0xaa, 0x0, 0xa1, 0x4f, 0x56);

// {7988B577-EC89-11cf-9C00-00AA00A14F56}
DEFINE_GUID(IID_IEnumDiskQuotaUsers, 
0x7988b577, 0xec89, 0x11cf, 0x9c, 0x0, 0x0, 0xaa, 0x0, 0xa1, 0x4f, 0x56);

// {7988B579-EC89-11cf-9C00-00AA00A14F56}
DEFINE_GUID(IID_IDiskQuotaEvents, 
0x7988b579, 0xec89, 0x11cf, 0x9c, 0x0, 0x0, 0xaa, 0x0, 0xa1, 0x4f, 0x56);


//
// Definitions for value and bits in DWORD returned by GetQuotaState().
//
#define DISKQUOTA_STATE_DISABLED            0x00000000
#define DISKQUOTA_STATE_TRACK               0x00000001
#define DISKQUOTA_STATE_ENFORCE             0x00000002
#define DISKQUOTA_STATE_MASK                0x00000003
#define DISKQUOTA_FILESTATE_INCOMPLETE      0x00000100
#define DISKQUOTA_FILESTATE_REBUILDING      0x00000200
#define DISKQUOTA_FILESTATE_MASK            0x00000300

//
// Helper macros for setting and testing state value.
//
#define DISKQUOTA_SET_DISABLED(s) \
            ((s) &= ~DISKQUOTA_STATE_MASK)

#define DISKQUOTA_SET_TRACKED(s) \
            ((s) |= (DISKQUOTA_STATE_MASK & DISKQUOTA_STATE_TRACK))

#define DISKQUOTA_SET_ENFORCED(s) \
            ((s) |= (DISKQUOTA_STATE_ENFORCE & DISKQUOTA_STATE_ENFORCE))

#define DISKQUOTA_IS_DISABLED(s) \
            (DISKQUOTA_STATE_DISABLED == ((s) & DISKQUOTA_STATE_MASK))

#define DISKQUOTA_IS_TRACKED(s) \
            (DISKQUOTA_STATE_TRACK == ((s) & DISKQUOTA_STATE_MASK))

#define DISKQUOTA_IS_ENFORCED(s) \
            (DISKQUOTA_STATE_ENFORCE == ((s) & DISKQUOTA_STATE_MASK))
//
// These file state flags are read-only.
//
#define DISKQUOTA_FILE_INCOMPLETE(s) \
            (0 != ((s) & DISKQUOTA_FILESTATE_INCOMPLETE))

#define DISKQUOTA_FILE_REBUILDING(s) \
            (0 != ((s) & DISKQUOTA_FILESTATE_REBUILDING))


//
// Definitions for bits in DWORD returned by GetQuotaLogFlags().
//
#define DISKQUOTA_LOGFLAG_USER_THRESHOLD    0x00000001
#define DISKQUOTA_LOGFLAG_USER_LIMIT        0x00000002

//
// Helper macros to interrogate a log flags DWORD.
//
#define DISKQUOTA_IS_LOGGED_USER_THRESHOLD(f) \
            (0 != ((f) & DISKQUOTA_LOGFLAG_USER_THRESHOLD))

#define DISKQUOTA_IS_LOGGED_USER_LIMIT(f) \
            (0 != ((f) & DISKQUOTA_LOGFLAG_USER_LIMIT))

//
// Helper macros to set/clear bits in a log flags DWORD.
//
#define DISKQUOTA_SET_LOG_USER_THRESHOLD(f,yn) \
              ((f &= ~DISKQUOTA_LOGFLAG_USER_THRESHOLD) |= ((yn) ? DISKQUOTA_LOGFLAG_USER_THRESHOLD : 0))

#define DISKQUOTA_SET_LOG_USER_LIMIT(f,yn) \
              ((f &= ~DISKQUOTA_LOGFLAG_USER_LIMIT) |= ((yn) ? DISKQUOTA_LOGFLAG_USER_LIMIT : 0))

//
// Per-user quota information.
//
typedef struct DiskQuotaUserInformation {    
    LONGLONG QuotaUsed;
    LONGLONG QuotaThreshold;
    LONGLONG QuotaLimit;
} DISKQUOTA_USER_INFORMATION, *PDISKQUOTA_USER_INFORMATION;


//
// Values for fNameResolution argument to:
//
//      IDiskQuotaControl::AddUser
//      IDiskQuotaControl::FindUserSid
//      IDiskQuotaControl::CreateEnumUsers
//
#define DISKQUOTA_USERNAME_RESOLVE_NONE     0
#define DISKQUOTA_USERNAME_RESOLVE_SYNC     1
#define DISKQUOTA_USERNAME_RESOLVE_ASYNC    2

//
// Values for status returned by IDiskQuotaUser::GetAccountStatus.
//
#define DISKQUOTA_USER_ACCOUNT_RESOLVED     0
#define DISKQUOTA_USER_ACCOUNT_UNAVAILABLE  1
#define DISKQUOTA_USER_ACCOUNT_DELETED      2
#define DISKQUOTA_USER_ACCOUNT_INVALID      3
#define DISKQUOTA_USER_ACCOUNT_UNKNOWN      4
#define DISKQUOTA_USER_ACCOUNT_UNRESOLVED   5


///////////////////////////////////////////////////////////////////////////////
// IDiskQuotaUser interface
//
// This interface represents a single user entry in the volume's quota
// information file.  Through this interface, you can query and modify
// user-specific quota information on an NTFS volume.  An IDiskQuotaUser 
// interface is instantiated through IEnumDiskQuotaUsers, 
// IDiskQuotaControl::FindUserSid, IDiskQuotaControl::FindUserName or
// IDiskQuotaControl::AddUser.
//
// IDiskQuotaUser::GetName ----------------------------------------------------
//
//      Retrieves the various name strings associated with a disk quota user.
//
//      Arguments:
//
//          pszDomain - Address of buffer to receive the name of the user's 
//              network domain.  May be NULL.
//
//          cchDomain - Size of domain name buffer in characters.  Ignored if
//              pszDomain is NULL.
//
//          pszName - Address of buffer to receive the name of the user's
//              account in the network domain.  May be NULL.
//
//          cchName - Size of the name buffer in characters.  Ignored if pszName
//              is NULL.
//
//          pszFullName - Address of buffer to receive the "full" name for
//              the quota user.  The "full" name is the friendly name 
//              associated with the user's account.  For example, user 
//              John Doe might have an account name of "jdoe" while his
//              "full" name is the string "John Doe".  May be NULL.
//
//          cchFullName - Size of the "full name" buffer in characters.  Ignored
//              if pszFullName is NULL.
//
//      Returns:
//          NOERROR           - Success.
//          DQC_E_LOCK_FAILED - Could not gain exclusive lock on user object.
//
//
// IDiskQuotaUser::GetSidLength -----------------------------------------------
//
//      Retrieves the length of the user's security ID (SID) in bytes.  The
//      return value is used to size the destination buffer passed to
//      IDiskQuotaUser::GetSid.
//
//      Arguments:
//
//          pdwLength - Address of DWORD variable to receive SID length.
//
//      Returns:
//
//          NOERROR           - Success.
//          E_POINTER         - pdwLength argument is NULL.
//          DQC_E_INVALID_SID - User's SID is invalid.
//          DQC_E_LOCK_FAILED - Could not gain exclusive lock on user object.
//          
//
// IDiskQuotaUser::GetSid -----------------------------------------------------
//
//      Retrieves the user's security ID (SID).
//
//      Arguments:
//
//          pbSidBuffer - Address of destination buffer to receive SID.
//
//          cbSidBuffer - Size of destination buffer in bytes.
//
//      Returns:
//
//          NOERROR                   - Success.
//          E_POINTER                 - pbSidBuffer is NULL.
//          DQC_E_INVALID_SID         - Quota entry SID is invalid.
//          DQC_E_INSUFFICIENT_BUFFER - Insufficient destination buffer size.
//          DQC_E_LOCK_FAILED         - Couldn't lock user object.
//          
//
// IDiskQuotaUser::GetQuotaThreshold ------------------------------------------
//
//      Retrieves the user's quota "threshold" value on the volume.  The
//      threshold is an arbitrary value set by the volume's quota 
//      administrator.  It may be used to identify users who are approaching
//      their quota limit.
//
//      Arguments:
//
//          pllThreshold - Address of LONGLONG variable to receive the 
//              threshold value.
//
//      Returns:
//
//          NOERROR             - Success.
//          DQC_E_ACCESS_DENIED - No READ access to quota information.
//          DQC_E_LOCK_FAILED   - Couldn't lock user object.
//          E_POINTER           - pllThreshold is NULL.
//          E_OUTOFMEMORY       - Insufficient memory.
//          E_FAIL              - Failed reading quota information.
//          
//
// IDiskQuotaUser::GetQuotaThresholdText --------------------------------------
//
//      Retrieves the user's quota "threshold" value expressed as a text
//      string (i.e. "10.5 MB").  If the user's threshold is unlimited,
//      the string "No Limit" is returned (localized).
//
//      Arguments:
//
//          pszText - Address of character buffer to receive text.
//
//          cchText - Size of destination buffer in bytes.
//
//      Returns:
//
//          NOERROR             - Success.
//          DQC_E_ACCESS_DENIED - No READ access to quota information.
//          DQC_E_LOCK_FAILED   - Couldn't lock user object.
//          E_OUTOFMEMORY       - Insufficient memory.
//          E_FAIL              - Failed reading quota information.
//
//
// IDiskQuotaUser::GetQuotaLimit ----------------------------------------------
//
//      Retrieves the user's quota "limit" value on the volume.  The
//      limit is set as the maximum amount of disk space available to the
//      volume user.  There are two special-case values associated with the
//      quota limit.
//
//          -1 = User has unlimited quota on the volume.
//          -2 = User's quota entry is marked for deletion.  If the entry's
//               value for quota "used" is 0, the record will be deleted by
//               NTFS at some future time.
//
//      Arguments:
//
//          pllLimit - Address of LONGLONG variable to receive the limit value.
//
//      Returns:
//
//          NOERROR             - Success.
//          DQC_E_ACCESS_DENIED - No READ access to quota information.
//          DQC_E_LOCK_FAILED   - Couldn't lock user object.
//          E_POINTER           - pllLimit is NULL.
//          E_OUTOFMEMORY       - Insufficient memory.
//          E_FAIL              - Failed reading quota information.
//          
//
// IDiskQuotaUser::GetQuotaLimitText ------------------------------------------
//
//      Retrieves the user's quota "limit" value expressed as a text
//      string (i.e. "10.5 MB").  If the user's limit is unlimited,
//      the string "No Limit" is returned (localized).
//
//      Arguments:
//
//          pszText - Address of character buffer to receive text.
//
//          cchText - Size of destination buffer in bytes.
//
//      Returns:
//
//          NOERROR             - Success.
//          DQC_E_ACCESS_DENIED - No READ access to quota information.
//          DQC_E_LOCK_FAILED   - Couldn't lock user object.
//          E_OUTOFMEMORY       - Insufficient memory.
//          E_FAIL              - Failed reading quota information.
//
//
// IDiskQuotaUser::GetQuotaUsed -----------------------------------------------
//
//      Retrieves the user's quota "used" value on the volume.  This is the
//      amount of information stored on the volume by the user.  Note that
//      this is the amount of uncompressed information.  Therefore, the 
//      use of NTFS compression does not affect this value.
//
//      Arguments:
//
//          pllUsed - Address of LONGLONG variable to receive the 
//              quota used value.
//
//      Returns:
//
//          NOERROR             - Success.
//          DQC_E_ACCESS_DENIED - No READ access to quota information.
//          DQC_E_LOCK_FAILED   - Couldn't lock user object.
//          E_POINTER           - pllUsed is NULL.
//          E_OUTOFMEMORY       - Insufficient memory.
//          E_FAIL              - Failed reading quota information.
//          
//
// IDiskQuotaUser::GetQuotaUsedText -------------------------------------------
//
//      Retrieves the user's quota "used" value expressed as a text
//      string (i.e. "10.5 MB").
//
//      Arguments:
//
//          pszText - Address of character buffer to receive text.
//
//          cchText - Size of destination buffer in bytes.
//
//      Returns:
//
//          NOERROR             - Success.
//          DQC_E_ACCESS_DENIED - No READ access to quota information.
//          DQC_E_LOCK_FAILED   - Couldn't lock user object.
//          E_OUTOFMEMORY       - Insufficient memory.
//          E_FAIL              - Failed reading quota information.
//
//
// IDiskQuotaUser::GetQuotaInformation ----------------------------------------
//
//      Retrieves the user's quota "threshold", "used" and "limit" values in 
//      a single function call.
//
//      Arguments:
//
//          pQuotaInfo - Address of DISKQUOTA_USER_INFORMATION structure to 
//              receive the quota information.
//
//          cbQuotaInfo - Size of the desination buffer in bytes.
//
//      Returns:
//
//          NOERROR             - Success.
//          DQC_E_ACCESS_DENIED - No READ access to quota information.
//          DQC_E_LOCK_FAILED   - Couldn't lock user object.
//          E_POINTER           - pQuotaInfo is NULL.
//          E_OUTOFMEMORY       - Insufficient memory.
//          E_FAIL              - Failed reading quota information.
//          
//
// IDiskQuotaUser::SetQuotaThreshold ------------------------------------------
//
//      Sets the user's quota "threshold" value on the volume.  The
//      threshold is an arbitrary value set by the volume's quota 
//      administrator.  It may be used to identify users who are approaching
//      their quota limit.
//
//      Arguments:
//
//          llThreshold - Threshold value.
//
//          fWriteThrough - Set this to TRUE if you want to immediately write
//              the value to the volume's quota file.  Otherwise, the value
//              is only written to the quota user object's local memory.
//              This value should normally be set to TRUE.  Set it to FALSE 
//              when using the IDiskQuotaUserBatch interface to modify 
//              multiple user quota entries at once.
//
//      Returns:
//
//          NOERROR             - Success.
//          DQC_E_ACCESS_DENIED - No WRITE access to quota information.
//          DQC_E_LOCK_FAILED   - Couldn't lock user object.
//          E_FAIL              - Failed writing quota information.
//          
//
// IDiskQuotaUser::SetQuotaLimit ----------------------------------------------
//
//      Sets the user's quota "limit" value on the volume.  The
//      limit is set as the maximum amount of disk space available to the
//      volume user.  
//
//      Arguments:
//
//          llLimit - Limit value (bytes).  -1 = Unlimitd quota.
//
//          fWriteThrough - Set this to TRUE if you want to immediately write
//              the value to the volume's quota file.  Otherwise, the value
//              is only written to the quota user object's local memory.
//              This value should normally be set to TRUE.  Set it to FALSE 
//              when using the IDiskQuotaUserBatch interface to modify 
//              multiple user quota entries at once.
//
//      Returns:
//
//          NOERROR             - Success.
//          DQC_E_ACCESS_DENIED - No WRITE access to quota information.
//          DQC_E_LOCK_FAILED   - Couldn't lock user object.
//          E_FAIL              - Failed writing quota information.
//          
//
// IDiskQuotaUser::Invalidate -------------------------------------------------
//
//      Invalidates the quota information stored in the quota user object.
//      The next time information is requested, it is refreshed from disk.
//
//      Arguments: None.
//
//      Returns:   NOERROR.
//          
//
// IDiskQuotaUser::GetAccountStatus -------------------------------------------
//
//      Retrieves the status of the user object's account.  User information
//      is identified in the quota system by user security ID (SID).  This
//      SID must be resolved to a user account for the user's domain,
//      account name or full name to be retrieved.  This status information
//      may be used to determine why a user's name string(s) are not available.
//
//      Arguments:
//
//          pdwStatus - Address of DWORD variable to receive user's account
//              status.  The status value may be one of the following:
//
//              DISKQUOTA_USER_ACCOUNT_RESOLVED - SID has been resolved to
//                  a user account.  Names are available through GetName().
//
//              DISKQUOTA_USER_ACCOUNT_UNAVAILABLE - User's account is 
//                  unavailable at this time.  Network domain controller
//                  may not be available.  Name information will not be
//                  available.
//
//              DISKQUOTA_USER_ACCOUNT_DELETED - User's account has been
//                  deleted from the domain.  Name information will not be
//                  available.
//
//              DISKQUOTA_USER_ACCOUNT_INVALID - User's account is invalid.
//                  Name information will not be available.
//
//              DISKQUOTA_USER_ACCOUNT_UNKNOWN - User's account is unknown.
//                  Name information will not be available.
//
//              DISKQUOTA_USER_ACCOUNT_UNRESOLVED - SID has yet to be resolved
//                  to a user account.  
//
//
//      Returns:   NOERROR   - Success.
//                 E_POINTER - pdwStatus argument is NULL.
//
///////////////////////////////////////////////////////////////////////////////
#undef  INTERFACE
#define INTERFACE IDiskQuotaUser

DECLARE_INTERFACE_(IDiskQuotaUser, IUnknown)
{
    STDMETHOD(GetName)(THIS_ 
        LPWSTR pszDomain, 
        DWORD cchDomain, 
        LPWSTR pszName, 
        DWORD cchName, 
        LPWSTR pszFullName, 
        DWORD cchFullName) PURE;

    STDMETHOD(GetSidLength)(THIS_ 
        LPDWORD pdwLength) PURE;

    STDMETHOD(GetSid)(THIS_ 
        LPBYTE pbSidBuffer, 
        DWORD cbSidBuffer) PURE;

    STDMETHOD(GetQuotaThreshold)(THIS_ 
        PLONGLONG pllThreshold) PURE;

    STDMETHOD(GetQuotaThresholdText)(THIS_
        LPWSTR pszText,
        DWORD cchText) PURE;

    STDMETHOD(GetQuotaLimit)(THIS_ 
        PLONGLONG pllLimit) PURE;

    STDMETHOD(GetQuotaLimitText)(THIS_
        LPWSTR pszText,
        DWORD cchText) PURE;

    STDMETHOD(GetQuotaUsed)(THIS_ 
        PLONGLONG pllUsed) PURE;

    STDMETHOD(GetQuotaUsedText)(THIS_
        LPWSTR pszText,
        DWORD cchText) PURE;

    STDMETHOD(GetQuotaInformation)(THIS_ 
        LPVOID pbQuotaInfo, 
        DWORD cbQuotaInfo) PURE;

    STDMETHOD(SetQuotaThreshold)(THIS_ 
        LONGLONG llThreshold,
        BOOL fWriteThrough) PURE;

    STDMETHOD(SetQuotaLimit)(THIS_ 
        LONGLONG llLimit,
        BOOL fWriteThrough) PURE;

    STDMETHOD(Invalidate)(THIS) PURE;

    STDMETHOD(GetAccountStatus)(THIS_ 
        LPDWORD pdwStatus) PURE;
};

typedef IDiskQuotaUser DISKQUOTA_USER, *PDISKQUOTA_USER;


///////////////////////////////////////////////////////////////////////////////
// IEnumDiskQuotaUsers interface
//
// Implementation of a standard OLE IEnumXXXX interface for enumerating 
// IDiskQuotaUser objects.  IEnumDiskQuotaUsers is instantiated 
// with IDiskQuotaControl::CreateEnumUsers.
//
// For a description of argument and return values, see the OLE documentation 
// for IEnumXXXX.
//
///////////////////////////////////////////////////////////////////////////////
#undef  INTERFACE
#define INTERFACE IEnumDiskQuotaUsers

DECLARE_INTERFACE_(IEnumDiskQuotaUsers, IUnknown)
{
    STDMETHOD(Next)(THIS_ 
        DWORD cUsers, 
        PDISKQUOTA_USER *rgUsers, 
        LPDWORD pcUsersFetched) PURE;

    STDMETHOD(Skip)(THIS_ 
        DWORD cUsers) PURE;

    STDMETHOD(Reset)(THIS) PURE;

    STDMETHOD(Clone)(THIS_ 
        IEnumDiskQuotaUsers **ppEnum) PURE;
};

typedef IEnumDiskQuotaUsers ENUM_DISKQUOTA_USERS, *PENUM_DISKQUOTA_USERS;



///////////////////////////////////////////////////////////////////////////////
// IDiskQuotaUserBatch interface
//
// This interface provides a mechanism for optimizing updates of quota
// information on multiple users.  Through this interface, you can add quota
// user objects to a container that is then submitted for update in a single
// call.  This reduces the number of calls to the underlying file system
// providing optimal performance when large numbers of user objects must
// be updated.
//
// IDiskQuotaUserBatch::Add ---------------------------------------------------
//
//      Adds an IDiskQuotaUser pointer to the batch list.  When setting values
//      on a quota user object in preparation for batch processing, specify
//      FALSE for the fWriteThrough flag in the SetQuotaLimit and
//      SetQuotaThreshold functions.  This will store the values in memory
//      without writing through to disk.  Calling FlushToDisk will write the
//      changes to disk.
//      This function calls AddRef() on the pUser interface pointer.
//      Release() is automatically called on each contained IDiskQuotaUser 
//      interface pointer when the batch object is destroyed.
//
//      Arguments:
//
//          pUser - Address of quota user object's IDiskQuotaUser interface.
//
//      Returns:
//
//          NOERROR        - Success.
//          E_POINTER      - pUser arg is NULL. 
//          E_OUTOFMEMORY  - Insufficient memory.
//          E_UNEXPECTED   - Unexpected exception occured.
//          
//
// IDiskQuotaUserBatch::Remove ------------------------------------------------
//
//      Removes an IDiskQuotaUser pointer from the batch list.
//
//      Arguments:
//
//          pUser - Address of quota user object's IDiskQuotaUser interface.
//
//      Returns:
//
//          NOERROR       - Success.
//          S_FALSE       - Quota user object not found in batch.
//          E_POINTER     - pUser arg is NULL. 
//          E_UNEXPECTED  - An unexpected exception occured.
//
//
// IDiskQuotaUserBatch::RemoveAll ---------------------------------------------
//
//      Removes all IDiskQuotaUser pointers from the batch list.
//
//      Arguments: None.
//
//      Returns:
//
//          NOERROR      - Success.
//          E_UNEXPECTED - An unexpected exception occured.
//
//
// IDiskQuotaUserBatch::FlushToDisk -------------------------------------------
//
//      Writes user object changes to disk in a single call to NTFS.
//
//      Note that there are limitations as to how much information can be
//      written to disk in a single call to the file system.  The flush 
//      operation may require multiple calls to NTFS.  Nonetheless, it will
//      be much more efficient than a single call for each user object.
//
//      Arguments: None.
//
//      Returns:
//
//          NOERROR             - Success.
//          E_FAIL              - Error writing quota information.
//          E_OUTOFMEMORY       - Insufficient memory.
//          E_UNEXPECTED        - An unexpected exception occured.
//          DQC_E_ACCESS_DENIED - No WRITE access to quota information.
//
///////////////////////////////////////////////////////////////////////////////
#undef  INTERFACE
#define INTERFACE IDiskQuotaUserBatch

DECLARE_INTERFACE_(IDiskQuotaUserBatch, IUnknown)
{
    STDMETHOD(Add)(THIS_ 
        PDISKQUOTA_USER pUser) PURE;

    STDMETHOD(Remove)(THIS_ 
        PDISKQUOTA_USER pUser) PURE;

    STDMETHOD(RemoveAll)(THIS) PURE;

    STDMETHOD(FlushToDisk)(THIS) PURE;
};


typedef IDiskQuotaUserBatch DISKQUOTA_USER_BATCH, *PDISKQUOTA_USER_BATCH;


///////////////////////////////////////////////////////////////////////////////
// IDiskQuotaControl interface
//
// This interface is the principle point of control for the disk quota control
// library.  A client instantiates this interface through CoCreateInstance
// using the the class ID CLSID_DiskQuotaControl.  The resulting quota control 
// object provides a layer of abstraction around the disk quota facilities of 
// a single NTFS volume.  Through the IDiskQuotaControl interface, the client
// may query and set volume-specific quota attributes as well as enumerate
// all quota user entries on the volume.
//
// The DiskQuotaControl object also implements IConnectionPointContainer
// to service the IDiskQuotaEvents connection point interface.
//
//
// IDiskQuotaControl::Initialize ----------------------------------------------
//
//      Initializes a new QuotaControl object by opening the NTFS volume
//      with the requested access rights.  The return value indicates
//      if the volume does not support NTFS disk quotas or if the caller
//      does not have sufficient access rights.  
//
//                        >>>>>>  NOTE  <<<<<<<
//
//          Accessing quota information on remote volumes is not 
//          supported for NT5 Beta 1.  Remote volume support will be
//          added after Beta 1.
//
//      Arguments:
//
//          pszPath - Name of NTFS path to open.
//                    To obtain WRITE access, this string must be
//                    "\\.\X" where 'X' is the drive letter for the 
//                    volume.  If only READ access is desired, the
//                    path may be simply "X:\"
//
//          bReadWrite - TRUE  = Open for read/write.
//                       FALSE = Open for read only
//
//      Returns:
//
//        NOERROR               - Success.
//        E_FAIL                - Error getting volume information.
//        DQC_E_INITIALIZED     - Controller object already initialized.
//        DQC_E_ACCESS_DENIED   - Caller has insufficient access rights.
//        DQC_E_INVALID_NAME    - Invalid path string at pszPath.
//        DQC_E_FILE_NOT_FOUND  - Specified path doesn't exist.
//        DQC_E_PATH_NOT_FOUND  - Specified path doesn't exist.
//        DQC_E_BAD_PATHNAME    - Specified path name is invalid.
//        DQC_E_NO_QUOTAS_FS    - File system isn't NTFS.
//        DQC_E_NO_QUOTAS_FSVER - File system isn't NTFS v5.0 or greater.
//          
//              
// IDiskQuotaControl::SetQuotaState -------------------------------------------
//
//      Sets the state of the quota system.  Note that not all state attributes
//      can be modified.  The enable/disable and track/enforce attributes can
//      be modified.
//
//      Arguments:
//
//          dwState - DWORD containing the state to be applied to the volume.
//              Use the following macros to set the proper bits in the dwState
//              argument:
//
//                                       Enable?   Track?  Enforce?
//                                       --------- ------- --------
//              DISKQUOTA_SET_DISABLED -   No        No       No
//              DISKQUOTA_SET_TRACKED  -   Yes       Yes      No
//              DISKQUOTA_SET_ENFORCED -   Yes       Yes      Yes
//
//      Returns:
//
//          NOERROR             - Success.
//          E_INVALIDARG        - dwState value is incorrect.
//          DQC_E_ACCESS_DENIED - No WRITE access to quota information.
//          E_FAIL              - Failed writing quota information.
//          
//
// IDiskQuotaControl::GetQuotaState -------------------------------------------
//
//      Retrieves a set of flags describing the state of the quota system.
//
//      Arguments:
//
//          pdwState - Address of DWORD to receive the state flags.  The flag
//              bits are defined as follows:
//
//              DISKQUOTA_STATE_DISABLED - Quotas are not enabled on the volume.
//
//              DISKQUOTA_STATE_TRACK - Quotas are enabled but the limit value
//                  is not being enforced.  Users may exceed their quota limit.
//
//              DISKQUOTA_STATE_ENFORCE - Quotas are enabled and the limit 
//                  value is enforced.  Users cannot exceed their quota limit.
//
//              DISKQUOTA_FILESTATE_INCOMPLETE - The volume's quota information
//                  is out of date.  Quotas are probably disabled.
//
//              DISKQUOTA_FILESTATE_REBUILDING - The volume is rebuilding it's
//                  quota information.
//
//      Returns:
//
//          NOERROR             - Success.
//          E_POINTER           - pdwState argument is NULL.
//          DQC_E_ACCESS_DENIED - No READ access to quota information.
//          E_FAIL              - Error reading quota information.
//          
//
// IDiskQuotaControl::SetQuotaLogFlags ----------------------------------------
//
//      Controls the logging of user-related quota events on the volume. 
//      Logging consists of an entry in the volume server system's event log.
//
//      Arguments:
//
//          dwFlags - DWORD containing the flags to be applied to the volume.
//              Use the following macros to set the proper bits in the dwFlags
//              argument:
//
//              DISKQUOTA_SET_LOG_USER_THRESHOLD - Turn on/off logging of 
//                  user quota threshold violations.  If set, an event log
//                  entry will be created when the user exceeds their assigned
//                  quota warning threshold.
//
//              DISKQUOTA_SET_LOG_USER_LIMIT - Turn on/off logging of user
//                  quota limit violations.  If set, an event log entry will
//                  be created when the user exceeds their assigned quota 
//                  limit.
//
//      Returns:
//
//          NOERROR             - Success.
//          DQC_E_ACCESS_DENIED - No WRITE access to quota information.
//          E_FAIL              - Failed writing quota information.
//          
//
// IDiskQuotaControl::GetQuotaLogFlags ----------------------------------------
//
//      Retrieves the flags that control the logging of user-related quota 
//      events on the volume. Logging consists of an entry in the volume 
//      server's event log.
//
//      Arguments:
//
//          pdwFlags - Address of DWORD variable to receive the volume's
//              quota logging flags.  Use the following macros to 
//              interrogate the contents of the flag value:
//
//              DISKQUOTA_IS_LOGGED_USER_THRESHOLD
//              DISKQUOTA_IS_LOGGED_USER_LIMIT
//
//      Returns:
//
//          NOERROR             - Success.
//          E_POINTER           - pdwFlags argument is NULL.
//          DQC_E_ACCESS_DENIED - No READ access to quota information.
//          E_FAIL              - Failed reading volume quota information.
//          
//          
// IDiskQuotaControl::SetDefaultQuotaLimit ------------------------------------
//
//      Modifies the default quota limit applied automatically to new users
//      of the volume.
//
//      Arguments:
//
//          llLimit - Default quota limit value.
//
//      Returns:
//
//          NOERROR             - Success.
//          DQC_E_ACCESS_DENIED - No WRITE access to quota information.
//          E_FAIL              - Failed writing quota information.
//          
//
// IDiskQuotaControl::GetDefaultQuotaLimit ------------------------------------
//
//      Retrieves the default quota limit applied automatically to new users
//      of the volume.
//
//      Arguments:
//
//          pllLimit - Address of LONGLONG variable to receive the limit value.
//
//      Returns:
//
//          NOERROR             - Success.
//          E_POINTER           - pllLimit argument is NULL.
//          DQC_E_ACCESS_DENIED - No READ access to quota information.
//          E_FAIL              - Failed reading quota information.
//          
//
// IDiskQuotaControl::GetDefaultQuotaLimitText --------------------------------
//
//      Retrieves the volume's default quota "limit" expressed as a text
//      string (i.e. "10.5 MB"). If the volume's limit is unlimited,
//      the string "No Limit" is returned (localized).
//
//      Arguments:
//
//          pszText - Address of character buffer to receive text.
//
//          cchText - Size of destination buffer in bytes.
//
//      Returns:
//          NOERROR             - Success.
//          DQC_E_ACCESS_DENIED - No READ access to quota information.
//          E_FAIL              - Failed reading quota information.
//
//
// IDiskQuotaControl::SetDefaultQuotaThreshold --------------------------------
//
//      Modifies the default quota warning threshold applied automatically to 
//      new users of the volume.
//
//      Arguments:
//
//          llThreshold - Default quota threshold value.
//
//      Returns:
//
//          NOERROR             - Success.
//          DQC_E_ACCESS_DENIED - No WRITE access to quota information.
//          E_FAIL              - Failed writing quota information.
//          
//
// IDiskQuotaControl::GetDefaultQuotaThreshold --------------------------------
//
//      Retrieves the default quota warning threshold applied automatically to 
//      new users of the volume.
//
//      Arguments:
//
//          pllThreshold - Address of LONGLONG variable to receive the 
//              warning threshold value.
//
//      Returns:
//
//          NOERROR             - Success.
//          E_POINTER           - pllThreshold argument is NULL.
//          DQC_E_ACCESS_DENIED - No READ access to quota information.
//          E_FAIL              - Failed reading quota information.
//          
//
// IDiskQuotaControl::GetDefaultQuotaThresholdText ----------------------------
//
//      Retrieves the volume's default quota "threshold" expressed as a text
//      string (i.e. "10.5 MB"). If the volume's threshold is unlimited,
//      the string "No Limit" is returned (localized).
//
//      Arguments:
//
//          pszText - Address of character buffer to receive text.
//
//          cchText - Size of destination buffer in bytes.
//
//      Returns:
//          NOERROR             - Success.
//          DQC_E_ACCESS_DENIED - No READ access to quota information.
//          E_FAIL              - Failed reading quota information.
//
//
// IDiskQuotaControl::AddUserSid ----------------------------------------------
// IDiskQuotaControl::AddUserName ---------------------------------------------
//
//      Adds a new quota entry on the volume for a given user.  Note that 
//      NTFS automatically creates a user quota entry when a user first writes
//      to the volume.  Automatically created user entries are assigned the
//      volume's default threshold and limit values.  This function allows
//      you to create a user quota entry before a user has written information
//      to the volume.  One reason for doing this might be to pre-assign
//      a threshold or limit value different than the volume defaults.
//
//      Arguments:
//
//          pUserSid - Address of buffer containing user's security ID (SID).
//
//          pszDomain - Address of user's domain name string.
//
//          pszName - Address of user's account name string.
//              If pszDomain points to a blank string, it is assumed that
//              pszName points to a fully-qualified "Domain\Account" string.
//
//          fNameResolution - Flag indicating how the user's account information
//              is to be obtained.  The volume's quota information contains
//              only security IDs for identifying users.  The user's account 
//              information such as domain name, account name and full user 
//              name must be obtained from the network domain controller, or 
//              the local machine if the machine is not networked.  This 
//              information may be obtained synchronously, asynchronously or 
//              not at all.
//              Specify one of the following values in this argument:
//
//              DISKQUOTA_USERNAME_RESOLVE_NONE - Do not resolve user account
//                  information.
//
//              DISKQUOTA_USERNAME_RESOLVE_SYNC - Resolve user account 
//                  information synchronously.  AddUser will not return until 
//                  the information has been resolved.  If the information
//                  is present in the disk quota SID cache, the return of
//                  information will be immediate.  If not cached, the
//                  function can take a considerable amount of time to 
//                  locate the user's information.  This period is dependent
//                  upon many network-related factors.  It can be on the
//                  order of several seconds.
//
//              DISKQUOTA_USERNAME_RESOLVE_ASYNC - Resolve user account 
//                  information asynchronously.  AddUser will return 
//                  immediately.  The caller must implement 
//                  IDiskQuotaUserEvents to receive notification when the 
//                  account information is available.  This option causes
//                  the user object to be placed on a queue.  This queue
//                  is serviced by a thread dedicated to obtaining account
//                  information for disk quota users on the volume. If the 
//                  information has been cached from a previous request,
//                  the notification occurs as soon as the object is serviced.
//                  If the information is not cached, the thread obtains
//                  the information from the network domain controller and
//                  then notifies IDiskQuotaUserEvents that the operation
//                  is complete.
//
//          ppUser - Address of IDiskQuotaUser pointer variable to receive
//              the interface pointer of the newly created quota user object.
//
//
//      Returns:
//
//          SUCCESS            - Success.
//          E_OUTOFMEMORY      - Insufficient memory.
//          S_FALSE            - User already exists.  Not added.
//          E_POINTER          - Pointer argument was NULL.
//          DQC_E_USER_UNKNOWN - User name provided is unknown.
//
//
// IDiskQuotaControl::FindUserSid ---------------------------------------------
//
//      Locates a specific user entry in the volume's quota information.
//      The user's security ID (SID) is used as the search key.
//
//      Arguments:
//
//          pUserSid - Address of buffer containing user's security ID (SID).
//
//          fNameResolution - Flag indicating how the user's account information
//              is to be resolved.  See description in AddUser for details.
//
//          ppUser - Address of IDiskQuotaUser pointer variable to receive
//              the interface pointer of the quota user object for the user.
//
//      Returns:
//          NOERROR             - Success.
//          E_FAIL              - User not found in volume's quota information.
//          E_POINTER           - Either pUserSid or ppUser was NULL.
//          E_OUTOFMEMORY       - Insufficient memory.
//          DQC_E_INVALID_SID   - SID pointed to by pUserSid is invalid.
//          DQC_E_ACCESS_DENIED - No READ access to quota information.
//
//                   >>>>>>>>> IMPORTANT NOTE <<<<<<<<<
//
//        This method will return a user object even if there is no quota
//        record for the user in the quota file.  While that may sound
//        strange, it is consistent with the idea of automatic user addition
//        and default quota settings.  If there is currently no quota entry
//        for the requested user, and the user would be added to the quota
//        file if they were to request disk space, the returned user object
//        will have a quota threshold and limit equal to the volume defaults.
//
//
// IDiskQuotaControl::FindUserName --------------------------------------------
//
//      Locates a specific entry in the volume's quota information.
//      The user's domain and account name are used as the search key.  
//      This method can take some time as it may need to resolve the name to 
//      a security ID.  See note for FindUserSid (above) concerning behavior
//      when an entry for the user does not exist.
//
//      Arguments:
//
//          pszDomain - Address of buffer containing user's domain name string.
//
//          pszName - Address of buffer containing user's account name string.
//
//          ppUser - Address of IDiskQuotaUser pointer variable to receive
//              the interface pointer of the quota user object for the user.
//
//          fNameResolution - Flag indicating how the user's account information
//              is to be resolved.  See description in AddUser for details.
//
//      Returns:
//          NOERROR             - Success.
//          E_FAIL              - User not found in volume's quota information.
//          E_POINTER           - Either pUserSid or ppUser was NULL.
//          E_OUTOFMEMORY       - Insufficient memory.
//          DQC_E_INVALID_SID   - SID pointed to by pUserSid is invalid.
//          DQC_E_ACCESS_DENIED - No READ access to quota information.
//          DQC_E_NO_SID_MAPPING- Could not map account name to a security ID.
//
//
// IDiskQuotaControl::DeleteUser ----------------------------------------------
//
//      Removes a user entry from the volume's quota information file if the 
//      user's charged quota amount is 0 bytes.  This function doesn't actually
//      remove the quota entry from the volume.  It marks the entry for 
//      deletion.  NTFS performs the actual deletion at a later point in time.
//      Following a call to DeleteUser, the IDiskQuotaUser interface is still
//      active.  This function does not delete the user object from memory.
//      You must still call IUnknown::Release() on the user object to
//      release it.
//
//      Arguments:
//
//          pUser - Pointer to IDiskQuotaUser interface of quota user who's
//              quota record is marked for deletion.
//
//      Returns:
//      
//          NOERROR              - Success.
//          E_POINTER            - pUser argument was NULL.
//          E_FAIL               - Error marking entry for deletion.
//          DQC_E_USER_HAS_FILES - Couldn't delete.  User still has file(s) on
//                                 the volume.
//          DQC_E_ACCESS_DENIED  - Insufficient access.
//
//
// IDiskQuotaControl::CreateEnumUsers -----------------------------------------
//
//      Creates an enumerator object for enumerating quota users on the volume.
//      The object created implements the IEnumDiskQuotaUsers interface.  
//      The object created supports the standard OLE IEnumXXXX functions.
//
//      Arguments:
//
//          rgpUserSids - Array of security ID (SID) pointers representing the
//              user objects to be included in the enumeration.  If this 
//              value is NULL, all user entries are enumerated.
//
//          cpSids - Number of items in the rgpUserSids array.  Ignored if 
//              rgpUserSids is NULL.
//
//
//          ppEnum - Address of IEnumDiskQuotaUsers pointer variable to receive
//              the address of the new enumerator.
//
//          fNameResolution - Flag indicating how the account information for
//              enumerated users is to be resolved.  See description in
//              AddUser for details.
//
//      Returns:
//          NOERROR             - Success.
//          E_POINTER           - ppEnum argument is NULL.
//          E_OUTOFMEMORY       - Insufficient memory.
//          DQC_E_ACCESS_DENIED - Insufficient access rights.
//
//
// IDiskQuotaControl::CreateUserBatch -----------------------------------------
//
//      Creates a batching object for optimizing updates to the quota settings
//      of multiple users simultaneously. See IDiskQuotaUserBatch for details.
//
//      Arguments:
//
//          ppBatch - Address of IDiskQuotaUserBatch pointer variable to 
//              receive the IDiskQuotaUserBatch interface pointer.
//
//      Returns:
//
//        NOERROR             - Success.
//        E_POINTER           - ppBatch argument is NULL.
//        E_OUTOFMEMORY       - Insufficient memory to create batch object.
//        DQC_E_ACCESS_DENIED - Insufficient access rights.
//
//
// IDiskQuotaControl::InvalidateSidNameCache ----------------------------------
//
//      Invalidates the contents of the system's SID-Name cache so that 
//      subsequent requests for new user objects (IEnumDiskQuotaUsers::Next,
//      IDiskQuotaControl::FindUserSid and IDiskQuotaControl::FindUserName) 
//      must obtain user names from the network domain controller.  As names 
//      are obtained, they are again cached.
//
//      In general there is no reason to call this method.  It is included to 
//      provide a method for programmatically refreshing the entire SID-name
//      cache.
//
//      Arguments: None.
//
//      Returns:
//
//          NOERROR - Success.
//          E_FAIL  - SID/Name cache not available or couldn't obtain 
//              exclusive lock on cache.
//
//
// IDiskQuotaControl::GiveUserNameResolutionPriority --------------------------
//
//      By default, quota user objects are serviced in the resolution queue in 
//      the order they were placed into the queue.  This function will promote
//      a specified user object to the head of the queue so that it is next in 
//      line for resolution.
//
//      Arguments:
//
//          pUser - Address of user object's IDiskQuotaUser interface.
//
//      Returns:
//
//        NOERROR       - Success.
//        S_FALSE       - Quota user object not in resolver queue.
//        E_UNEXPECTED  - Unexpected error.  Caught an exception or the 
//                        Sid-Name resolver hasn't been created.
//
//
// IDiskQuotaControl::ShutdownNameResolution ----------------------------------
//
//      The SID-Name resolver runs on a background thread to translate
//      user security IDs to user names.  When a quota control object is 
//      destroyed, this thread automatically terminates.  If you have a
//      situation where you're finished with the quota control object and
//      it is not be ready to be destroyed (other open ref counts),
//      this method may be called to shut down the background thread before
//      the object is destroyed.  Note that asynchronous name resolution will 
//      also cease once the thread terminates.  A subsequent call to 
//      CreateEnumUsers, AddUserSid, AddUserName, FindUserSid or FindUserName 
//      may re-create the resolver thread.
//      
//      Arguments: None.
//
//      Returns : Only returns NOERROR.
//
///////////////////////////////////////////////////////////////////////////////
#undef INTERFACE
#define INTERFACE IDiskQuotaControl

DECLARE_INTERFACE_(IDiskQuotaControl, IConnectionPointContainer)
{
    STDMETHOD(Initialize)(THIS_ 
        LPCWSTR pszPath, 
        BOOL bReadWrite) PURE;

    STDMETHOD(SetQuotaState)(THIS_ 
        DWORD dwState) PURE;

    STDMETHOD(GetQuotaState)(THIS_ 
        LPDWORD pdwState) PURE;

    STDMETHOD(SetQuotaLogFlags)(THIS_ 
        DWORD dwFlags) PURE;

    STDMETHOD(GetQuotaLogFlags)(THIS_ 
        LPDWORD pdwFlags) PURE;

    STDMETHOD(SetDefaultQuotaThreshold)(THIS_ 
        LONGLONG llThreshold) PURE;

    STDMETHOD(GetDefaultQuotaThreshold)(THIS_ 
        PLONGLONG pllThreshold) PURE;

    STDMETHOD(GetDefaultQuotaThresholdText)(THIS_
        LPWSTR pszText,
        DWORD cchText) PURE;

    STDMETHOD(SetDefaultQuotaLimit)(THIS_ 
        LONGLONG llLimit) PURE;

    STDMETHOD(GetDefaultQuotaLimit)(THIS_ 
        PLONGLONG pllLimit) PURE;

    STDMETHOD(GetDefaultQuotaLimitText)(THIS_
        LPWSTR pszText,
        DWORD cchText) PURE;

    STDMETHOD(AddUserSid)(THIS_ 
        PSID pUserSid, 
        DWORD fNameResolution,
        PDISKQUOTA_USER *ppUser) PURE; 

    STDMETHOD(AddUserName)(THIS_ 
        LPWSTR pszDomain,
        LPWSTR pszName,
        DWORD fNameResolution,
        PDISKQUOTA_USER *ppUser) PURE; 

    STDMETHOD(DeleteUser)(THIS_ 
        PDISKQUOTA_USER pUser) PURE;

    STDMETHOD(FindUserSid)(THIS_ 
        PSID pUserSid, 
        DWORD fNameResolution,
        PDISKQUOTA_USER *ppUser) PURE;

    STDMETHOD(FindUserName)(THIS_ 
        LPCWSTR pszDomain, 
        LPCWSTR pszName, 
        PDISKQUOTA_USER *ppUser) PURE;

    STDMETHOD(CreateEnumUsers)(THIS_ 
        PSID *rgpUserSids, 
        DWORD cpSids, 
        DWORD fNameResolution,
        PENUM_DISKQUOTA_USERS *ppEnum) PURE;

    STDMETHOD(CreateUserBatch)(THIS_ 
        PDISKQUOTA_USER_BATCH *ppBatch) PURE;

    STDMETHOD(InvalidateSidNameCache)(THIS) PURE;

    STDMETHOD(GiveUserNameResolutionPriority)(THIS_ 
        PDISKQUOTA_USER pUser) PURE;

    STDMETHOD(ShutdownNameResolution)(THIS_
        VOID) PURE;
};

typedef IDiskQuotaControl DISKQUOTA_CONTROL, *PDISKQUOTA_CONTROL;



///////////////////////////////////////////////////////////////////////////////
// IDiskQuotaEvents interface
//
// A client must implement this interface as an OLE event sink in order to
// receive quota-related event notifications such as asynchronous account
// name resolution.
//
// IDiskQuotaEvents::OnUserNameChanged ----------------------------------------
//
//      Notifies client's connection sink whenever a user's SID has been 
//      asynchronously resolved so that the user's domain, account and full
//      name strings are available in the quota user object.
//
//      Arguments:
//
//          pUser - Address of IDiskQuotaUser interface for quota user object.
//                  It is not necessary to call Release() on this pointer.
//                  The DiskQuotaControl object controls the lifetime of the
//                  user object.
//
//      Returns:  Return value is ignored.
//  
///////////////////////////////////////////////////////////////////////////////
#undef  INTERFACE
#define INTERFACE IDiskQuotaEvents

DECLARE_INTERFACE_(IDiskQuotaEvents, IUnknown)
{
    STDMETHOD(OnUserNameChanged)(THIS_ 
        PDISKQUOTA_USER pUser) PURE;
};

typedef IDiskQuotaEvents DISKQUOTA_EVENTS, *PDISKQUOTA_EVENTS;


///////////////////////////////////////////////////////////////////////////////
// DiskQuotaEventSink
//
// Declaration for a class that implements IDiskQuotaEvents.  A client may
// implement this class as it is declared or create their own class.  The only
// requirement is that it implement IDiskQuotaEvents as an OLE connection
// point.  See the SDK documentation for details on OLE connection points and
// OLE connection point containers.
//
///////////////////////////////////////////////////////////////////////////////
class DiskQuotaEventSink : public IDiskQuotaEvents
{
    private:
        LONG  m_cRef;       // Interface reference count.

    public:
        DWORD m_dwCookie;   // Connection point cookie.

        DiskQuotaEventSink(VOID);
        ~DiskQuotaEventSink(VOID);

        //
        // IUnknown methods.
        //
        STDMETHODIMP QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(VOID);
        STDMETHODIMP_(ULONG) Release(VOID);

        //
        // IDiskQuotaEvents
        //
        STDMETHODIMP OnUserNameChanged(PDISKQUOTA_USER pUser);
};


///////////////////////////////////////////////////////////////////////////////
// Error codes specific to the public disk quota interfaces.
// "DQC" = Disk Quota Control
///////////////////////////////////////////////////////////////////////////////
//
// Security ID for user is invalid.
//
#define DQC_E_INVALID_SID          MAKE_HRESULT(SEVERITY_ERROR, \
                                                FACILITY_ITF, \
                                                ERROR_INVALID_SID)
//
// Insufficient memory to complete operation.
//
#define DQC_E_INSUFFICIENT_BUFFER  MAKE_HRESULT(SEVERITY_ERROR, \
                                                FACILITY_ITF, \
                                                ERROR_INSUFFICIENT_BUFFER)
//
// An operation/capability is not supported.
//
#define DQC_E_NOT_SUPPORTED        MAKE_HRESULT(SEVERITY_ERROR, \
                                                FACILITY_ITF, \
                                                ERROR_NOT_SUPPORTED)
//
// No access to perform the requested operation.
//
#define DQC_E_ACCESS_DENIED        MAKE_HRESULT(SEVERITY_ERROR, \
                                                FACILITY_ITF, \
                                                ERROR_ACCESS_DENIED)
//
// Requested file or object not found.
//
#define DQC_E_FILE_NOT_FOUND       MAKE_HRESULT(SEVERITY_ERROR, \
                                                FACILITY_ITF, \
                                                ERROR_FILE_NOT_FOUND)
//
// Requested file path not found.
//
#define DQC_E_PATH_NOT_FOUND       MAKE_HRESULT(SEVERITY_ERROR, \
                                                FACILITY_ITF, \
                                                ERROR_PATH_NOT_FOUND)
//
// Requested file path is invalid.
//
#define DQC_E_INVALID_NAME         MAKE_HRESULT(SEVERITY_ERROR, \
                                                FACILITY_ITF, \
                                                ERROR_INVALID_NAME)
//
// Requested file path is invalid.
//
#define DQC_E_BAD_PATHNAME         MAKE_HRESULT(SEVERITY_ERROR, \
                                                FACILITY_ITF, \
                                                ERROR_BAD_PATHNAME)
//
// Failed to obtain exclusive lock on a shared resource.
//
#define DQC_E_LOCK_FAILED          MAKE_HRESULT(SEVERITY_ERROR, \
                                                FACILITY_ITF, \
                                                ERROR_LOCK_FAILED)
//
// No mapping available for security ID to user name.
//
#define DQC_E_NO_SID_MAPPING       MAKE_HRESULT(SEVERITY_ERROR, \
                                                FACILITY_ITF, \
                                                ERROR_NONE_MAPPED)
//
// No more items in enumeration.
//
#define DQC_S_NO_MORE_ITEMS        MAKE_HRESULT(SEVERITY_SUCCESS, \
                                                FACILITY_ITF, \
                                                ERROR_NO_MORE_ITEMS)
//
// User owns files on volume.
// 
#define DQC_E_USER_HAS_FILES       MAKE_HRESULT(SEVERITY_ERROR, \
                                                FACILITY_ITF, \
                                                0x8002)
//
// File system doesn't support quotas.
// Currently, must be NTFS.
//
#define DQC_E_NO_QUOTAS_FS         MAKE_HRESULT(SEVERITY_ERROR, \
                                                FACILITY_ITF, \
                                                0x8003)
//
// File system version doesn't support quotas.
// Currently, must be NTFS 5.0 or greater.
//
#define DQC_E_NO_QUOTAS_FSVER      MAKE_HRESULT(SEVERITY_ERROR, \
                                                FACILITY_ITF, \
                                                0x8004)
//
// Object has already been initialized.
// Multiple initialization is not allowed.
//
#define DQC_E_INITIALIZED          MAKE_HRESULT(SEVERITY_ERROR, \
                                                FACILITY_ITF, \
                                                0x8005)

//
// Object has not been initialized.
// Initialization must be completed before operation can be performed.
//
#define DQC_E_NOT_INITIALIZED      MAKE_HRESULT(SEVERITY_ERROR, \
                                                FACILITY_ITF, \
                                                0x8006)
//
// Specified user is unknown.
//
#define DQC_E_USER_UNKNOWN         MAKE_HRESULT(SEVERITY_ERROR, \
                                                FACILITY_ITF, \
                                                0x8007)

//=============================================================================
//=============================================================================
// ActiveX Control Description
//=============================================================================
//=============================================================================
//
// DSKQUOTA.DLL also provides an ActiveX control that performs much of the
// functionality found in the vtable interfaces IDiskQuotaControl, 
// IDiskQuotaUser and IDiskQuotaEvents.
//
// The following section describes the properties and methods for each
// OLE automation interface supported.
//
// ActiveX object ProgID = "Microsoft.DiskQuota.1"
// ActiveX object CLSID  = {7988B571-EC89-11cf-9C00-00AA00A14F56}
// Type library CLSID    = {7988B57C-EC89-11cf-9C00-00AA00A14F56}
// 
// The object supports 3 automation-compatible interfaces:
//
//      IID_DIDiskQuotaControl          [default]
//      IID_DIDiskQuotaUser
//      IID_DIDiskQuotaControlEvents    [default, source]
// 
//
// ----------------------------------------------------------------------------
// IID_DIDiskQuotaControl - Disk Quota Controller
//
// This interface is the default controlling interface for the DiskQuota
// ActiveX component.  It implements much the same functionality as 
// the vtable interface IDiskQuotaControl.
//
// Properties:
//
//      QuotaState
//
//          Desc:   The "state" of NTFS disk quotas on the volume.
//                  The state can be either "disabled", "tracking quota usage"
//                  or "enforcing quota limits".  Enforcement implies
//                  tracking.
//
//          Type:   QuotaStateConstants (enumeration)
//
//          Domain: dqStateDisable   (0)
//                  qsStateTrack     (1)
//                  qsStateEnforce   (2)
//
//      QuotaFileIncomplete (read only)
//
//          Desc:   Determines if the quota file on the volume is marked
//                  as "incomplete".  An incomplete volume is usually the
//                  result of a disabled quota system.
//
//          Type:   VARIANT_BOOL
//
//          Domain: True/False
//
//      QuotaFileRebuilding (read only)
//
//          Desc:   Determines if the quota file on the volume is being
//                  rebuilt.  Rebuilding automatically occurs whenever
//                  quotas are enabled on the system or when one or more
//                  user entries are marked for deletion.
//
//          Type:   VARIANT_BOOL
//
//          Domain: True/False
//
//      LogQuotaThreshold
//
//          Desc:   Indicates if a system event log entry should be created
//                  whenever a user exceeds their assigned quota warning
//                  threshold.
//
//          Type:   VARIANT_BOOL
//
//          Domain: True/False
//
//      LogQuotaLimit
//
//          Desc:   Indicates if a system event log entry should be created
//                  whenever a user exceeds their assigned quota limit.
//
//          Type:   VARIANT_BOOL
//
//          Domain: True/False
//
//      DefaultQuotaThreshold
//
//          Desc:   The default warning threshold value assigned to new users
//                  of the volume.
//
//          Type:   double
//
//          Domain: Value is expressed in bytes.
//
//      DefaultQuotaThresholdText (read only)
//
//          Desc:   The default threshold value expressed as a text
//                  string suitable for display.  The recipient of
//                  the string is responsible for deleting the string
//                  using SysFreeString().
//
//          Type:   BSTR
//
//          Domain: Threshold value formatted as a decimal number
//                  and appended with a units suffix.
//
//                  i.e.:  "10.5 MB"
//                         "No Limit" if unlimited.
//
//      DefaultQuotaLimit
//
//          Desc:   The default quota limit value assigned to new users
//                  of the volume.
//
//          Type:   double
//
//          Domain: Value is expressed in bytes.
//                  -1 is special case meaning "no limit".
//
//      DefaultQuotaLimitText (read only)
//
//          Desc:   The default quota limit value expressed as a text
//                  string suitable for display.  The recipient of
//                  the string is responsible for deleting the string
//                  using SysFreeString().
//
//          Type:   BSTR
//
//          Domain: Limit value formatted as a decimal number
//                  and appended with a units suffix.
//
//                  i.e.:  "10.5 MB"
//                         "No Limit" if unlimited.
//
//      UserNameResolution
//
//          Desc:   Controls the behavior of the security ID-to-Name
//                  resolution processing.  The process may be bypassed,
//                  performed synchronously or performed asynchronously.
//                  If Asynchronous name resolution is chosen, the caller
//                  must implement the DIDiskQuotaControlEvents dispatch 
//                  interface to receive notification when the name has
//                  been resolved.
//
//          Type:   UserNameResolutionConstants (enumeration)
//
//          Domain: dqResolveNone      (0) - No name information
//                  dqResolveSync      (1) - Resolve synchronously
//                  dqResolveAsync     (2) - Resolve asynchronously
//
// Methods:
//
//      Initialize
//
//          Desc:   Initializes a DiskQuota object for a given NTFS volume.
//                  This method must be called before any other methods.
//                  If unsuccessful, any other method calls will return
//                  DQC_E_NOT_INITIALIZED.
//
//                        >>>>>>  NOTE  <<<<<<<
//
//          Accessing quota information on remote volumes is not 
//          supported for NT5 Beta 1.  Remote volume support will be
//          added after Beta 1.
//
//
//          Arguments:
//              pPath [in] - Contains path of volume to initialize.
//
//                  Type:   BSTR
//
//                  Domain: To obtain WRITE access, this string must be
//                          "\\.\X" where 'X' is the drive letter for the 
//                          volume.  If only READ access is desired, the
//                          path may be simply "X:\"
//
//              bReadWrite [in] - Indicates if "write" access is desired.  
//
//                  Type:   VARIANT_BOOL
//
//                  Domain: False = Read-only
//                          True  = Read-Write
//
//          Returns: Nothing.
//
//          Errors:  See IDiskQuotaControl::Initialize.
//
//
//      AddUser
//
//          Desc:   Add a new user entry to the volume's quota file.
//                  If the user already exists, the object for the existing
//                  user is returned.
//
//          Arguments:
//              pDomain [in] - User's account domain name.
//
//                  Type:   BSTR
//
//                  Domain: Windows NT domain names.
//
//              pName [in] - User's account name.  If pDomain is a blank string,
//                  pName is assumed to contain a fully-qualified
//                  "Domain\Account" combination.
//
//                  Type:   BSTR
//
//                  Domain: Windows NT user account names.
//
//          Returns:
//              Reference to newly added user object (DIDiskQuotaUser).
//
//          Errors:  See IDiskQuotaControl::AddUserName
//
//
//      DeleteUser
//
//          Arguments:
//              pUser [in] - Reference to user object to be marked for deletion.
//
//                  Type:   DIDiskQuotaUser
//
//                  Domain: Pointer to DIDiskQuotaUser interface.
//
//          Returns: Nothing
//
//          Errors:  See IDiskQuotaControl::DeleteUser
//
//
//      FindUser
//
//          Desc:   Locate user entry in the volume's quota file.
//
//          Arguments:
//              pDomain [in] - User's account domain name.
//
//                  Type:   BSTR
//
//                  Domain: Windows NT domain names.
//
//              pName [in] - User's account name.
//
//                  Type:   BSTR
//
//                  Domain: Windows NT user account names.
//
//          Returns:
//              Reference to located user object (DIDiskQuotaUser).
//
//          Errors:  See IDiskQuotaControl::FindUserName
//
//
//      InvalidateSidNameCache
//
//          Desc:   Invalidates the contents of the Security ID-User name
//                  cache.  Following cache invalidation, subsequent 
//                  creations of user objects will need resolve and
//                  re-cache account information.
//      
//          Arguments: None
//
//          Returns:  Nothing
//
//          Errors:  See IDiskQuotaControl::InvalidateSidNameCache
//
//
//      GiveUserNameResolutionPriority
//
//          Desc:   When UserNameResolution is dqResolveAsync, 
//                  user entry objects with unresolved security IDs are
//                  automatically placed on a queue, waiting to be
//                  resolved.  The resolution process occurs on a background
//                  thread.  Normally objects are processed on a FIFO
//                  basis (queue).  This method moves the specified user
//                  object to the front of the line so to speak.  This
//                  can be helpful when a user interface is being
//                  updated dynamically through IDiskQuotaControlEvent
//                  notifications.
//
//          Arguments:
//              pUser - Reference to user object to be promoted.
//
//          Returns: Nothing.
//
//          Errors:  See IDiskQuotaControl::GiveUserNameResolutionPriority
//
//
//      ShutdownNameResolution
//
//          Desc:   The SID-Name resolver runs on a background thread to 
//                  translate user security IDs to user names.  When a quota 
//                  control object is destroyed, this thread automatically 
//                  terminates.  In situations where you're finished 
//                  with the quota control object and it is not be ready to be 
//                  destroyed (i.e. other open ref counts), this method may be 
//                  called to shut down the background thread before the object
//                  is destroyed.  Note that asynchronous name resolution will 
//                  also cease once the thread terminates.  A subsequent call
//                  to CreateEnumUsers, AddUserSid, AddUserName, FindUserSid or
//                  FindUserName may re-create the resolver thread.
//      
//          Arguments: None.
//
//          Returns : Nothing.
//
//          Errors: None.
//
//
// ----------------------------------------------------------------------------
// IID_DIDiskQuotaUser - Disk Quota user entry object.
//
// This interface represents a user entry in a volume's quota information.
// It implements much the same functionality as the vtable interface 
// IDiskQuotaUser.  Disk Quota user objects can only be created through
// a Disk Quota controller object (enumeration, AddUser, FindUser etc).
//
// Properties:
//
//      DomainName (read only)
//
//          Desc:   The domain name for the user's account.
//
//          Type:   BSTR
//
//          Domain: Windows NT network domain names.
//
//      AccountName (read only)
//
//          Desc:   The account name for the user's account.
//
//          Type:   BSTR
//
//          Domain: Windows NT network account names.
//
//      Name (read only)
//
//          Desc:   The "friendly" name for the user's account.
//
//          Type:   BSTR
//
//          Domain: Whatever string is assigned to the account.
//
//      QuotaThreshold
//
//          Desc:   The user's quota warning threshold.
//
//          Type:   double
//
//          Domain: Value expressed in bytes.
//
//      QuotaThresholdText (read only)
//
//          Desc:   User's threshold value formatted as a decimal number
//                  and appended with a units suffix.
//
//          Type:   BSTR
//
//          Domain: i.e. "10.5 MB"
//                       "No Limit" if unlimited.
//
//      QuotaLimit
//
//          Desc:   The user's quota limit.
//
//          Type:   double
//
//          Domain: Value expressed in bytes.
//
//      QuotaLimitText (read only)
//
//          Desc:   User's limit value formatted as a decimal number
//                  and appended with a units suffix.
//
//          Type:   BSTR
//
//          Domain: i.e. "10.5 MB"
//                       "No Limit" if unlimited.
//
//      AccountStatus (read only)
//
//          Desc:   Status of the user's account information.
//
//          Type:   AccountStatusConstants (enumeration)
//
//          Domain: dqAcctResolved    (0) - Name information available
//                  dqAcctUnavailable (1) - Can't get name information
//                  dqAcctDeleted     (2) - Account has been deleted
//                  dqAcctInvalid     (3) - Account is invalid
//                  dqAcctUnknown     (4) - Account is not known
//                  dqAcctUnresolved  (5) - Name information not yet resolved
//
// Methods:
//
//      Invalidate
//
//          Desc:   Invalidates the information cached in the user object.
//                  Following a call to Invalidate, the next call for 
//                  a quota-related property refreshes the information from
//                  the NTFS volume.
//
//          Arguments: None.
//
//          Returns: Nothing.
//
//          Errors: None. Always returns S_OK.
//
//
// ----------------------------------------------------------------------------
// IID_DIDiskQuotaControlEvents - Disk Quota Controller Events source.
//
// This interface is the default source interface for the DiskQuota
// ActiveX component.  It is not implemented in the DiskQuota object.  It
// merely describes the interface that must be implemented by clients if they
// are to receive user-name-update notifications for asynchronous resolution
// of user object name information.
//
// Properties:  None.
//
// Methods:
//
//      OnUserNameChanged
//
//          Desc:   Called by the DiskQuota object whenever an asynchronous
//                  name resolution operation has completed for a single user
//                  object.  This notification indicates that the user's
//                  DomainName, AccountName and Name properties contain
//                  valid information.
//                  It is not necessary to call Release() on this pointer.
//                  The DiskQuotaControl object controls the lifetime of the
//                  user object.
//
//          Arguments:
//              pUser - Reference to the user object associated with the event.
//
//          Returns: Ignored by DiskQuota object.
//
//          Errorrs: Ignored by DiskQuota object.
//
//

#endif // __DSKQUOTA_H
