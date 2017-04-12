#if _MSC_VER > 1000
#pragma once
#endif

#ifndef BPCREG_H
#define BPCREG_H

#include <tchar.h>

//-----------------------------------------------------------------------------
//
// Registry usage:
//
// HKLM = HKEY_LOCAL_MACHINE
// HKCU = HKEY_CURRENT_USER
//
// HKLM\Software\Microsoft\TV System Services
//
//     REG_SZ (Default)  - Not used.
//     REG_SZ ProductDir - Root directory for BPC software
//     REG_SZ DBFile     - Full path to tss.mdb
//     REG_SZ DBReplacementFile     - Full path to the empty replacement tss.mdb
//     REG_SZ EPGDBFile  - Full path to epg.mdb
//     REG_SZ SystemDB   - Full path to tss.mdw
//     REG_SZ AMFilter   - Full path to dss.grf
//
// HKLM\Software\Microsoft\TV System Services\Tuning Spaces
//
//     REG_SZ (Default)  - Not used.
//
// HKLM\Software\Microsoft\TV System Services\Tuning Spaces\<iTuningSpace>
//
//     REG_SZ (Default)   - Not used.
//     REG_SZ Name        - UNDONE
//     REG_SZ Description - UNDONE
//     REG_SZ Loader      - UNDONE
//     REG_SZ MinChannel  - UNDONE
//     REG_SZ MaxChannel  - UNDONE
//     REG_SZ Devices     - UNDONE
//     REG_SZ MediaType   - UNDONE
//
// HKLM\Software\Microsoft\TV System Services\Tuning Spaces\1
//
//     REG_SZ Messages - UNDONE
//     REG_SZ History  - UNDONE
//
// HKLM\Software\Microsoft\TV System Services\EPG Loaders
//
//     REG_SZ (Default)               - Not used.
//     REG_SZ LastAttempt             - UNDONE
//     REG_BINARY LastAttemptTime     - UNDONE
//     REG_SZ LastCompletion          - UNDONE
//     REG_BINARY LastCompletionTime  - UNDONE
//     REG_DWORD LastCompletionResult - UNDONE
//     REG_BINARY EngineeringByte         - UNDONE
//
// HKLM\Software\Microsoft\TV System Services\EPG Loaders\<guid>
//
//     REG_SZ (Default)               - Not used.
//     REG_SZ Name                    - UNDONE
//     REG_SZ TuningID                - UNDONE
//     REG_BINARY LastAttemptTime     - UNDONE
//     REG_BINARY LastCompletionTime  - UNDONE
//     REG_DWORD LastCompletionResult - UNDONE
//
// HKCU\Software\Microsoft\TV System Services
//
//     REG_SZ (Default)  - Not used.
//
// HKCU\Software\Microsoft\Microsoft TVExplorer
//
//     REG_SZ (Default)  - Not used.
//
// HKCU\Software\Microsoft\Microsoft TVExplorer\RemoteKeys
//
//     REG_SZ (Default)  - Not used.
//
// HKCU\Software\Microsoft\Microsoft TVExplorer\RemoteKeys\CommandLines
//
//     REG_SZ (Default)  - Not used.
//     REG_SZ Guide      - UNDONE
//     REG_SZ TV         - UNDONE
//
// HKCU\Software\Microsoft\Microsoft TVExplorer\RemoteKeys\WakeupKeys
//
//     REG_SZ (Default)  - Not used.
//     REG_SZ Guide      - UNDONE
//     REG_SZ TV         - UNDONE
//
// HKCU\AppEvents\Schemes\Apps\TVExplorer
//
//     REG_SZ (Default)  - "TV Explorer"
//
//-----------------------------------------------------------------------------

extern const LPCTSTR g_strBaseRegKey;
extern const LPCTSTR g_strProductDir;
extern const LPCTSTR g_strDBFile;
extern const LPCTSTR g_strDBReplacementFile;
extern const LPCTSTR g_strEPGDBFile;
extern const LPCTSTR g_strDefVBITS;
extern const LPCTSTR g_strDefVBIChan;
extern const LPCTSTR g_strSysFile;
extern const LPCTSTR g_strAMFilter;
extern const LPCTSTR g_strAMFClass;
extern const LPCTSTR g_strTSInputType;
extern const LPCTSTR g_strCountryCode;
extern const LPCTSTR g_strVolume;
extern const LPCTSTR g_strBalance;
extern const LPCTSTR g_strAudioPin;
extern const LPCTSTR g_strTVXRegKey;
extern const LPCTSTR g_strNTSC;
extern const LPCTSTR g_strDistanceViewing;

extern const LPCTSTR g_strConfigRegKey;
extern const LPCTSTR g_strConfigLastPage;

extern const LPCTSTR g_strTuningSpaceRegKey;
extern const LPCTSTR g_strTuningSpaceName;
extern const LPCTSTR g_strCurTVTuningSpace;
extern const LPCTSTR g_strDSSTuningSpaceRegKey;
extern const LPCTSTR g_strLCIDToSTYPE;

extern const LPCTSTR g_strCAProviderRegKey;
extern const LPCTSTR g_strCAProviderName;
extern const LPCTSTR g_strCAProviderDesc;
extern const LPCTSTR g_strVenPrefix;
extern const LPCTSTR g_strDevPrefix;

extern const LPCTSTR g_strEPGRegKey;
extern const LPCTSTR g_strEPGLoadersRegKey;
extern const LPCTSTR g_strEPGLoaderAttempt;
extern const LPCTSTR g_strEPGLoaderAttemptTime;
extern const LPCTSTR g_strEPGLoaderCompletion;
extern const LPCTSTR g_strEPGLoaderCompletionTime;
extern const LPCTSTR g_strEPGLoaderCompletionResult;
extern const LPCTSTR g_strEPGLoaderName;
extern const LPCTSTR g_strEPGLoaderTuningID;
extern const LPCTSTR g_strLoaderPostalCode;

extern const LPCTSTR g_strLoaderReadPrefix;
extern const LPCTSTR g_strLoaderWritePrefix;
extern const LPCTSTR g_strLoaderReadFile;
extern const LPCTSTR g_strDTVLoaderCSSByte;
extern const LPCTSTR g_strSSLoaderRegionID;
extern const LPCTSTR g_strSSLoaderChannel;
extern const LPCTSTR g_strSSLoaderLine;
extern const LPCTSTR g_strSSLoaderScanReturnCode;
extern const LPCTSTR g_strSSLoaderListenReturnCode;
extern const LPCTSTR g_strSSLoaderListenReturnCodeCount;

#ifdef _DEBUG
extern const LPCTSTR g_strDEBUG;
extern const LPCTSTR g_strTrace;
#endif


//-----------------------------------------------------------------------------
// OpenRegKey
//
// Opens a registry HKEY.  There are several overloads of this function
// that basically just provide defaults for the arguments to this function.
//
// Please use the overload that defaults as much as possible.
//
// The registry key is a combination of the following four parts.
//
//   HKEY hkeyRoot       = Optional root hkey.
//                         Default: HKEY_LOCAL_MACHINE
//
//   LPCTSTR szKey       = Optional key to be set.
//                         Default: g_strBaseRegKey
//
//   LPCTSTR szSubKey1
//   LPCTSTR szSubKey2   = Optional sub keys that are concatenated after
//                         szKey to form the full key.
//                         Backward slashes are added as necessary.
//
//                         Default: NULL
//
//   Note: if only one or two strings are specified they are assumed to be
//         szSubKey1 and szSubKey2.
//         i.e. szKey defaults to g_strBaseRegKey before szSubKey1 and
//         szSubKey2 default to NULL.
//
//         If szKey, szSubKey1, and szSubKey2 are NULL then this will open
//         a duplicate of hkeyRoot.
//
// The only required argument is the destination for the returned HKEY.
//
//   HKEY *pkey  = The returned HKEY.
//                 Remember to use RegCloseKey(*pkey) when you are finished
//                 with this registry key.
//
// The last two arguments are optional.
//
//   REGSAM sam  = Desired access mask.
//                 Default: KEY_ALL_ACCESS
//
//   BOOL fCreate = TRUE if the key should be created.
//                  Default: FALSE
//
// Returns:
//     ERROR_SUCCESS or an error code.
//-----------------------------------------------------------------------------
long OpenRegKey(HKEY hkeyRoot, LPCTSTR szKey, LPCTSTR szSubKey1,
        LPCTSTR szSubKey2, HKEY *pkey,
        REGSAM sam = KEY_ALL_ACCESS, BOOL fCreate = FALSE);

inline long OpenRegKey(LPCTSTR szKey, LPCTSTR szSubKey1, LPCTSTR szSubKey2,
        HKEY *pkey, REGSAM sam = KEY_ALL_ACCESS, BOOL fCreate = FALSE)
{
     return OpenRegKey(HKEY_LOCAL_MACHINE, szKey, szSubKey1, szSubKey2, pkey,
             sam, fCreate);
}

inline long OpenRegKey(LPCTSTR szSubKey1, LPCTSTR szSubKey2,
        HKEY *pkey, REGSAM sam = KEY_ALL_ACCESS, BOOL fCreate = FALSE)
{
     return OpenRegKey(HKEY_LOCAL_MACHINE, g_strBaseRegKey, szSubKey1,
             szSubKey2, pkey, sam, fCreate);
}

inline long OpenRegKey(LPCTSTR szSubKey, HKEY *pkey,
        REGSAM sam = KEY_ALL_ACCESS, BOOL fCreate = FALSE)
{
     return OpenRegKey(HKEY_LOCAL_MACHINE, g_strBaseRegKey, szSubKey, NULL,
             pkey, sam, fCreate);
}

inline long OpenRegKey(HKEY *pkey, REGSAM sam = KEY_ALL_ACCESS,
        BOOL fCreate = FALSE)
{
     return OpenRegKey(HKEY_LOCAL_MACHINE, g_strBaseRegKey, NULL, NULL,
             pkey, sam, fCreate);
}

//-----------------------------------------------------------------------------
// OpenUserRegKey
//
// Same as OpenRegKey except hkeyRoot defaults to HKEY_CURRENT_USER.
//-----------------------------------------------------------------------------
inline long OpenUserRegKey(LPCTSTR szKey, LPCTSTR szSubKey1, LPCTSTR szSubKey2,
        HKEY *pkey, REGSAM sam = KEY_ALL_ACCESS, BOOL fCreate = FALSE)
{
     return OpenRegKey(HKEY_CURRENT_USER, szKey, szSubKey1, szSubKey2, pkey,
             sam, fCreate);
}

inline long OpenUserRegKey(LPCTSTR szSubKey1, LPCTSTR szSubKey2,
        HKEY *pkey, REGSAM sam = KEY_ALL_ACCESS, BOOL fCreate = FALSE)
{
     return OpenRegKey(HKEY_CURRENT_USER, g_strBaseRegKey, szSubKey1,
             szSubKey2, pkey, sam, fCreate);
}

inline long OpenUserRegKey(LPCTSTR szSubKey, HKEY *pkey,
        REGSAM sam = KEY_ALL_ACCESS, BOOL fCreate = FALSE)
{
     return OpenRegKey(HKEY_CURRENT_USER, g_strBaseRegKey, szSubKey, NULL,
             pkey, sam, fCreate);
}

inline long OpenUserRegKey(HKEY *pkey, REGSAM sam = KEY_ALL_ACCESS,
        BOOL fCreate = FALSE)
{
     return OpenRegKey(HKEY_CURRENT_USER, g_strBaseRegKey, NULL, NULL,
             pkey, sam, fCreate);
}

//-----------------------------------------------------------------------------
// GetRegValue
//
// Gets data from the registry.  There are numerous overloads of this function
// that basically just provide defaults for the arguments to this function.
//
// Please use the overload that defaults as much as possible.
//
// The registry key/value is a combination of the following five parts.
// The first four are the same as in OpenRegKey().
//
//   HKEY hkeyRoot
//   LPCTSTR szKey
//   LPCTSTR szSubKey1
//   LPCTSTR szSubKey2
//
//   LPCTSTR szValueName = The name of the value to be set.
//                         If it is NULL then the default value for the key
//                         will be set.
//
//                         Default: none
//
// There are four ways to specify where the data to be returned
// depending on the type of data in the registry.
//
// REG_BINARY
//
//   BYTE *pb      = Out: The data is copied to this location.
//   DWORD *pcb    = In:  Maximum size of the returned data (in bytes).
//                   Out: Actual size of the data (in bytes).
//
// REG_SZ
//
//   TCHAR *psz    = Out: The string is copied to this location.
//   DWORD *pcb    = In:  Maximum size of the returned data (in bytes).
//                   Out: Actual size of the data (in bytes).
//                   Includes the null terminator.
//
// REG_DWORD
//
//   DWORD *pdw    = Out: The data is copied to this location.
//                   The length is assumed to be sizeof(DWORD).
//
// All other types
//
//   DWORD dwType  = The data type.
//   BYTE *pb      = Pointer to the data.
//   DWORD *pcb    = In:  Maximum size of the returned data (in bytes).
//                   Out: Actual size of the data (in bytes).
//                   Includes the null terminator if the data is a string type.
//
// Returns:
//     ERROR_SUCCESS or an error code.
//-----------------------------------------------------------------------------
long GetRegValue(HKEY hkeyRoot, LPCTSTR szKey, LPCTSTR szSubKey1,
        LPCTSTR szSubKey2, LPCTSTR szValueName,
        DWORD dwType, BYTE *pb, DWORD *pcb);

//-----------------------------------------------------------------------------
// REG_BINARY variants
//-----------------------------------------------------------------------------
inline long GetRegValue(LPCTSTR szKey, LPCTSTR szSubKey1, LPCTSTR szSubKey2,
        LPCTSTR szValueName, BYTE *pb, DWORD *pcb)
{
    return GetRegValue(HKEY_LOCAL_MACHINE, szKey, szSubKey1, szSubKey2,
            szValueName,
            REG_BINARY, pb, pcb);
}

inline long GetRegValue(LPCTSTR szSubKey1, LPCTSTR szSubKey2,
        LPCTSTR szValueName, BYTE *pb, DWORD *pcb)
{
    return GetRegValue(HKEY_LOCAL_MACHINE, g_strBaseRegKey, szSubKey1,
            szSubKey2, szValueName, REG_BINARY, pb, pcb);
}

inline long GetRegValue(LPCTSTR szSubKey, LPCTSTR szValueName,
        BYTE *pb, DWORD *pcb)
{
    return GetRegValue(HKEY_LOCAL_MACHINE, g_strBaseRegKey, szSubKey, NULL,
            szValueName, REG_BINARY, pb, pcb);
}

inline long GetRegValue(LPCTSTR szValueName, BYTE *pb, DWORD *pcb)
{
    return GetRegValue(HKEY_LOCAL_MACHINE, g_strBaseRegKey, NULL, NULL,
            szValueName, REG_BINARY, pb, pcb);
}

//-----------------------------------------------------------------------------
// REG_SZ variants
//-----------------------------------------------------------------------------
inline long GetRegValue(LPCTSTR szKey, LPCTSTR szSubKey1, LPCTSTR szSubKey2,
        LPCTSTR szValueName, TCHAR *psz, DWORD *pcb)
{
    return GetRegValue(HKEY_LOCAL_MACHINE, szKey, szSubKey1, szSubKey2,
            szValueName, REG_SZ, (BYTE *) psz, pcb);
}
inline long GetRegValue(LPCTSTR szSubKey1, LPCTSTR szSubKey2,
        LPCTSTR szValueName, TCHAR *psz, DWORD *pcb)
{
    return GetRegValue(HKEY_LOCAL_MACHINE, g_strBaseRegKey, szSubKey1,
            szSubKey2, szValueName, REG_SZ, (BYTE *) psz, pcb);
}

inline long GetRegValue(LPCTSTR szSubKey, LPCTSTR szValueName,
        TCHAR *psz, DWORD *pcb)
{
    return GetRegValue(HKEY_LOCAL_MACHINE, g_strBaseRegKey, szSubKey, NULL,
            szValueName, REG_SZ, (BYTE *)psz, pcb);
}

#if 0
inline long GetRegValue(HKEY hk, LPCTSTR szValueName,
        TCHAR *psz, DWORD *pcb)
{
    return GetRegValue(hk, NULL, NULLy, NULL,
            szValueName, REG_SZ, (BYTE *)psz, pcb);
}
#endif

inline long GetRegValue(LPCTSTR szValueName, TCHAR *psz, DWORD *pcb)
{
    return GetRegValue(HKEY_LOCAL_MACHINE, g_strBaseRegKey, NULL, NULL,
            szValueName, REG_SZ, (BYTE *) psz, pcb);
}

//-----------------------------------------------------------------------------
// REG_DWORD variants
//-----------------------------------------------------------------------------
inline long GetRegValue(LPCTSTR szKey, LPCTSTR szSubKey1, LPCTSTR szSubKey2,
        LPCTSTR szValueName, DWORD *pdw)
{
    DWORD cb = sizeof(DWORD);

    return GetRegValue(HKEY_LOCAL_MACHINE, szKey, szSubKey1, szSubKey2,
            szValueName, REG_DWORD, (BYTE *) pdw, &cb);
}

inline long GetRegValue(LPCTSTR szSubKey1, LPCTSTR szSubKey2,
        LPCTSTR szValueName, DWORD *pdw)
{
    DWORD cb = sizeof(DWORD);

    return GetRegValue(HKEY_LOCAL_MACHINE, g_strBaseRegKey, szSubKey1,
            szSubKey2, szValueName, REG_DWORD, (BYTE *) pdw, &cb);
}


inline long GetRegValue(LPCTSTR szSubKey, LPCTSTR szValueName, DWORD *pdw)
{
    DWORD cb = sizeof(DWORD);

    return GetRegValue(HKEY_LOCAL_MACHINE, g_strBaseRegKey, szSubKey, NULL,
            szValueName, REG_DWORD, (BYTE *) pdw, &cb);
}

inline long GetRegValue(LPCTSTR szValueName, DWORD *pdw)
{
    DWORD cb = sizeof(DWORD);

    return GetRegValue(HKEY_LOCAL_MACHINE, g_strBaseRegKey, NULL, NULL,
            szValueName, REG_DWORD, (BYTE *) pdw, &cb);
}

//-----------------------------------------------------------------------------
// The following variants are for getting values from an already open key.
//-----------------------------------------------------------------------------
inline long GetRegValue(HKEY hkey, LPCTSTR szKey, LPCTSTR szSubKey,
        LPCTSTR szValueName, TCHAR *psz, DWORD *pcb)
{
    return GetRegValue(hkey, szKey, szSubKey, NULL, szValueName,
            REG_SZ, (BYTE *) psz, pcb);
}

inline long GetRegValue(HKEY hkey, LPCTSTR szValueName, BYTE *pb, DWORD *pcb)
{
    return GetRegValue(hkey, NULL, NULL, NULL, szValueName,
            REG_BINARY, pb, pcb);
}

inline long GetRegValue(HKEY hkey, LPCTSTR szValueName, TCHAR *psz, DWORD *pcb)
{
    return GetRegValue(hkey, NULL, NULL, NULL, szValueName,
            REG_SZ, (BYTE *) psz, pcb);
}

inline long GetRegValue(HKEY hkey, LPCTSTR szValueName, DWORD *pdw)
{
    DWORD cb = sizeof(DWORD);

    return GetRegValue(hkey, NULL, NULL, NULL, szValueName,
            REG_DWORD, (BYTE *) pdw, &cb);
}

//-----------------------------------------------------------------------------
// GetUserRegValue
//
// Same as GetRegValue except hkeyRoot defaults to HKEY_CURRENT_USER.
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// REG_BINARY variants
//-----------------------------------------------------------------------------
inline long GetUserRegValue(LPCTSTR szKey, LPCTSTR szSubKey1, LPCTSTR szSubKey2,
        LPCTSTR szValueName, BYTE *pb, DWORD *pcb)
{
    return GetRegValue(HKEY_CURRENT_USER, szKey, szSubKey1, szSubKey2,
            szValueName,
            REG_BINARY, pb, pcb);
}

inline long GetUserRegValue(LPCTSTR szSubKey1, LPCTSTR szSubKey2,
        LPCTSTR szValueName, BYTE *pb, DWORD *pcb)
{
    return GetRegValue(HKEY_CURRENT_USER, g_strBaseRegKey, szSubKey1,
            szSubKey2, szValueName, REG_BINARY, pb, pcb);
}

inline long GetUserRegValue(LPCTSTR szSubKey, LPCTSTR szValueName,
        BYTE *pb, DWORD *pcb)
{
    return GetRegValue(HKEY_CURRENT_USER, g_strBaseRegKey, szSubKey, NULL,
            szValueName, REG_BINARY, pb, pcb);
}

inline long GetUserRegValue(LPCTSTR szValueName, BYTE *pb, DWORD *pcb)
{
    return GetRegValue(HKEY_CURRENT_USER, g_strBaseRegKey, NULL, NULL,
            szValueName, REG_BINARY, pb, pcb);
}

//-----------------------------------------------------------------------------
// REG_SZ variants
//-----------------------------------------------------------------------------
inline long GetUserRegValue(LPCTSTR szKey, LPCTSTR szSubKey1, LPCTSTR szSubKey2,
        LPCTSTR szValueName, TCHAR *psz, DWORD *pcb)
{
    return GetRegValue(HKEY_CURRENT_USER, szKey, szSubKey1, szSubKey2,
            szValueName, REG_SZ, (BYTE *) psz, pcb);
}
inline long GetUserRegValue(LPCTSTR szSubKey1, LPCTSTR szSubKey2,
        LPCTSTR szValueName, TCHAR *psz, DWORD *pcb)
{
    return GetRegValue(HKEY_CURRENT_USER, g_strBaseRegKey, szSubKey1,
            szSubKey2, szValueName, REG_SZ, (BYTE *) psz, pcb);
}

inline long GetUserRegValue(LPCTSTR szSubKey, LPCTSTR szValueName,
        TCHAR *psz, DWORD *pcb)
{
    return GetRegValue(HKEY_CURRENT_USER, g_strBaseRegKey, szSubKey, NULL,
            szValueName, REG_SZ, (BYTE *)psz, pcb);
}

inline long GetUserRegValue(LPCTSTR szValueName, TCHAR *psz, DWORD *pcb)
{
    return GetRegValue(HKEY_CURRENT_USER, g_strBaseRegKey, NULL, NULL,
            szValueName, REG_SZ, (BYTE *) psz, pcb);
}

//-----------------------------------------------------------------------------
// REG_DWORD variants
//-----------------------------------------------------------------------------
inline long GetUserRegValue(LPCTSTR szKey, LPCTSTR szSubKey1, LPCTSTR szSubKey2,
        LPCTSTR szValueName, DWORD *pdw)
{
    DWORD cb = sizeof(DWORD);

    return GetRegValue(HKEY_CURRENT_USER, szKey, szSubKey1, szSubKey2,
            szValueName, REG_DWORD, (BYTE *) pdw, &cb);
}

inline long GetUserRegValue(LPCTSTR szSubKey1, LPCTSTR szSubKey2,
        LPCTSTR szValueName, DWORD *pdw)
{
    DWORD cb = sizeof(DWORD);

    return GetRegValue(HKEY_CURRENT_USER, g_strBaseRegKey, szSubKey1,
            szSubKey2, szValueName, REG_DWORD, (BYTE *) pdw, &cb);
}


inline long GetUserRegValue(LPCTSTR szSubKey, LPCTSTR szValueName, DWORD *pdw)
{
    DWORD cb = sizeof(DWORD);

    return GetRegValue(HKEY_CURRENT_USER, g_strBaseRegKey, szSubKey, NULL,
            szValueName, REG_DWORD, (BYTE *) pdw, &cb);
}

inline long GetUserRegValue(LPCTSTR szValueName, DWORD *pdw)
{
    DWORD cb = sizeof(DWORD);

    return GetRegValue(HKEY_CURRENT_USER, g_strBaseRegKey, NULL, NULL,
            szValueName, REG_DWORD, (BYTE *) pdw, &cb);
}

inline long GetUserRegValue(LPCTSTR szSubKey, LPCTSTR szValueName, DWORD &dw)
{
    DWORD cb = sizeof(DWORD);

    return GetRegValue(HKEY_CURRENT_USER, g_strBaseRegKey, szSubKey, NULL,
            szValueName, REG_DWORD, (BYTE *) &dw, &cb);
}

inline long GetUserRegValue(LPCTSTR szValueName, DWORD &dw)
{
    DWORD cb = sizeof(DWORD);

    return GetRegValue(HKEY_CURRENT_USER, g_strBaseRegKey, NULL, NULL,
            szValueName, REG_DWORD, (BYTE *) &dw, &cb);
}

//-----------------------------------------------------------------------------
// SetRegValue
//
// Sets data into the registry.  There are numerous overloads of this function
// that basically just provide defaults for the arguments to this function.
//
// Please use the overload that defaults as much as possible.
//
// The registry key/value is a combination of the following five parts.
// The first four are the same as in OpenRegKey().
//
//   HKEY hkeyRoot
//   LPCTSTR szKey
//   LPCTSTR szSubKey1
//   LPCTSTR szSubKey2
//
//   LPCTSTR szValueName = The name of the value to be set.
//                         If it is NULL then the default value for the key
//                         will be set.
//
//                         Default: none
//
// There are four ways to specify the data to be set into the registry
// depending on the type of data being stored.
//
// REG_BINARY
//
//   BYTE *pb      = Pointer to the data.
//   DWORD cb      = Actual size of the data (in bytes).
//
// REG_SZ
//
//   TCHAR *psz    = The data is written as type REG_SZ.
//                   The length is calculated as _tcsclen(psz) + sizeof(TCHAR).
//
// REG_DWORD
//
//   DWORD dw      = The data is written as type DWORD.
//                   The length is calculated as sizeof(DWORD).
//
// All other types
//
//   DWORD dwType  = The data type.
//   BYTE *pb      = Pointer to the data.
//   DWORD cb      = Actual size of the data in bytes.
//
// Returns:
//     ERROR_SUCCESS or an error code.
//-----------------------------------------------------------------------------
long SetRegValue(HKEY hkeyRoot, LPCTSTR szKey, LPCTSTR szSubKey1,
        LPCTSTR szSubKey2, LPCTSTR szValueName,
        DWORD dwType, const BYTE *pb, DWORD cb);

//-----------------------------------------------------------------------------
// REG_BINARY variants
//-----------------------------------------------------------------------------
inline long SetRegValue(LPCTSTR szKey, LPCTSTR szSubKey1, LPCTSTR szSubKey2,
        LPCTSTR szValueName, const BYTE *pb, DWORD cb)
{
    return SetRegValue(HKEY_LOCAL_MACHINE, szKey, szSubKey1, szSubKey2,
            szValueName, REG_BINARY, pb, cb);
}

inline long SetRegValue(LPCTSTR szSubKey1, LPCTSTR szSubKey2,
        LPCTSTR szValueName, const BYTE *pb, DWORD cb)
{
    return SetRegValue(HKEY_LOCAL_MACHINE, g_strBaseRegKey, szSubKey1,
            szSubKey2, szValueName, REG_BINARY, pb, cb);
}

inline long SetRegValue(LPCTSTR szSubKey, LPCTSTR szValueName,
        const BYTE *pb, DWORD cb)
{
    return SetRegValue(HKEY_LOCAL_MACHINE, g_strBaseRegKey, szSubKey, NULL,
            szValueName, REG_BINARY, pb, cb);
}

inline long SetRegValue(LPCTSTR szValueName, const BYTE *pb, DWORD cb)
{
    return SetRegValue(HKEY_LOCAL_MACHINE, g_strBaseRegKey, NULL, NULL,
            szValueName, REG_BINARY, pb, cb);
}

//-----------------------------------------------------------------------------
// REG_SZ variants
//-----------------------------------------------------------------------------
inline long SetRegValue(LPCTSTR szKey, LPCTSTR szSubKey1, LPCTSTR szSubKey2,
        LPCTSTR szValueName, const TCHAR *psz)
{
    return SetRegValue(HKEY_LOCAL_MACHINE,
            szKey, szSubKey1, szSubKey2, szValueName,
            REG_SZ, (const BYTE *) psz, _tcsclen(psz) + sizeof(TCHAR));
}
inline long SetRegValue(LPCTSTR szSubKey1, LPCTSTR szSubKey2,
        LPCTSTR szValueName, const TCHAR *psz)
{
    return SetRegValue(HKEY_LOCAL_MACHINE, g_strBaseRegKey,
            szSubKey1, szSubKey2, szValueName,
            REG_SZ, (const BYTE *) psz, _tcsclen(psz) + sizeof(TCHAR));
}

inline long SetRegValue(LPCTSTR szSubKey, LPCTSTR szValueName, const TCHAR *psz)
{
    return SetRegValue(HKEY_LOCAL_MACHINE,
            g_strBaseRegKey, szSubKey, NULL, szValueName,
            REG_SZ, (const BYTE *)psz, _tcsclen(psz) + sizeof(TCHAR));
}

inline long SetRegValue(LPCTSTR szValueName, const TCHAR *psz)
{
    return SetRegValue(HKEY_LOCAL_MACHINE,
            g_strBaseRegKey, NULL, NULL, szValueName,
            REG_SZ, (const BYTE *) psz, _tcsclen(psz) + sizeof(TCHAR));
}

//-----------------------------------------------------------------------------
// REG_DWORD variants
//-----------------------------------------------------------------------------
inline long SetRegValue(LPCTSTR szKey, LPCTSTR szSubKey1, LPCTSTR szSubKey2,
        LPCTSTR szValueName, DWORD dw)
{
    return SetRegValue(HKEY_LOCAL_MACHINE,
            szKey, szSubKey1, szSubKey2, szValueName,
            REG_DWORD, (BYTE *) &dw, sizeof(DWORD));
}

inline long SetRegValue(LPCTSTR szSubKey1, LPCTSTR szSubKey2,
        LPCTSTR szValueName, DWORD dw)
{
    return SetRegValue(HKEY_LOCAL_MACHINE,
            g_strBaseRegKey, szSubKey1, szSubKey2, szValueName,
            REG_DWORD, (BYTE *) &dw, sizeof(DWORD));
}

inline long SetRegValue(LPCTSTR szSubKey, LPCTSTR szValueName, DWORD dw)
{
    return SetRegValue(HKEY_LOCAL_MACHINE,
            g_strBaseRegKey, szSubKey, NULL, szValueName,
            REG_DWORD, (const BYTE *) &dw, sizeof(DWORD));
}

inline long SetRegValue(LPCTSTR szValueName, DWORD dw)
{
    return SetRegValue(HKEY_LOCAL_MACHINE,
            g_strBaseRegKey, NULL, NULL, szValueName,
            REG_DWORD, (const BYTE *) &dw, sizeof(DWORD));
}

//-----------------------------------------------------------------------------
// The following variants are for setting values in an already open key.
//-----------------------------------------------------------------------------
inline long SetRegValue(HKEY hkey, LPCTSTR szValueName, const BYTE *pb, DWORD cb)
{
    return SetRegValue(hkey, NULL, NULL, NULL, szValueName,
            REG_BINARY, pb, cb);
}

inline long SetRegValue(HKEY hkey, LPCTSTR szValueName, const TCHAR *psz)
{
    return SetRegValue(hkey, NULL, NULL, NULL, szValueName,
            REG_SZ, (const BYTE *) psz, _tcsclen(psz) + sizeof(TCHAR));
}

inline long SetRegValue(HKEY hkey, LPCTSTR szValueName, DWORD dw)
{
    return SetRegValue(hkey, NULL, NULL, NULL, szValueName,
            REG_DWORD, (const BYTE *) &dw, sizeof(DWORD));
}

//-----------------------------------------------------------------------------
// SetUserRegValue
//
// Same as SetRegValue except hkeyRoot defaults to HKEY_CURRENT_USER.
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// REG_BINARY variants
//-----------------------------------------------------------------------------
inline long SetUserRegValue(LPCTSTR szKey, LPCTSTR szSubKey1, LPCTSTR szSubKey2,
        LPCTSTR szValueName, const BYTE *pb, DWORD cb)
{
    return SetRegValue(HKEY_CURRENT_USER, szKey, szSubKey1, szSubKey2,
            szValueName, REG_BINARY, pb, cb);
}

inline long SetUserRegValue(LPCTSTR szSubKey1, LPCTSTR szSubKey2,
        LPCTSTR szValueName, const BYTE *pb, DWORD cb)
{
    return SetRegValue(HKEY_CURRENT_USER, g_strBaseRegKey, szSubKey1,
            szSubKey2, szValueName, REG_BINARY, pb, cb);
}

inline long SetUserRegValue(LPCTSTR szSubKey, LPCTSTR szValueName,
        const BYTE *pb, DWORD cb)
{
    return SetRegValue(HKEY_CURRENT_USER, g_strBaseRegKey, szSubKey, NULL,
            szValueName, REG_BINARY, pb, cb);
}

inline long SetUserRegValue(LPCTSTR szValueName, const BYTE *pb, DWORD cb)
{
    return SetRegValue(HKEY_CURRENT_USER, g_strBaseRegKey, NULL, NULL,
            szValueName, REG_BINARY, pb, cb);
}

//-----------------------------------------------------------------------------
// REG_SZ variants
//-----------------------------------------------------------------------------
inline long SetUserRegValue(LPCTSTR szKey, LPCTSTR szSubKey1, LPCTSTR szSubKey2,
        LPCTSTR szValueName, const TCHAR *psz)
{
    return SetRegValue(HKEY_CURRENT_USER,
            szKey, szSubKey1, szSubKey2, szValueName,
            REG_SZ, (const BYTE *) psz, _tcsclen(psz) + sizeof(TCHAR));
}
inline long SetUserRegValue(LPCTSTR szSubKey1, LPCTSTR szSubKey2,
        LPCTSTR szValueName, const TCHAR *psz)
{
    return SetRegValue(HKEY_CURRENT_USER, g_strBaseRegKey,
            szSubKey1, szSubKey2, szValueName,
            REG_SZ, (const BYTE *) psz, _tcsclen(psz) + sizeof(TCHAR));
}

inline long SetUserRegValue(LPCTSTR szSubKey, LPCTSTR szValueName, const TCHAR *psz)
{
    return SetRegValue(HKEY_CURRENT_USER,
            g_strBaseRegKey, szSubKey, NULL, szValueName,
            REG_SZ, (const BYTE *)psz, _tcsclen(psz) + sizeof(TCHAR));
}

inline long SetUserRegValue(LPCTSTR szValueName, const TCHAR *psz)
{
    return SetRegValue(HKEY_CURRENT_USER,
            g_strBaseRegKey, NULL, NULL, szValueName,
            REG_SZ, (const BYTE *) psz, _tcsclen(psz) + sizeof(TCHAR));
}

//-----------------------------------------------------------------------------
// REG_DWORD variants
//-----------------------------------------------------------------------------
inline long SetUserRegValue(LPCTSTR szKey, LPCTSTR szSubKey1, LPCTSTR szSubKey2,
        LPCTSTR szValueName, DWORD dw)
{
    return SetRegValue(HKEY_CURRENT_USER,
            szKey, szSubKey1, szSubKey2, szValueName,
            REG_DWORD, (BYTE *) &dw, sizeof(DWORD));
}

inline long SetUserRegValue(LPCTSTR szSubKey1, LPCTSTR szSubKey2,
        LPCTSTR szValueName, DWORD dw)
{
    return SetRegValue(HKEY_CURRENT_USER,
            g_strBaseRegKey, szSubKey1, szSubKey2, szValueName,
            REG_DWORD, (BYTE *) &dw, sizeof(DWORD));
}

inline long SetUserRegValue(LPCTSTR szSubKey, LPCTSTR szValueName, DWORD dw)
{
    return SetRegValue(HKEY_CURRENT_USER,
            g_strBaseRegKey, szSubKey, NULL, szValueName,
            REG_DWORD, (const BYTE *) &dw, sizeof(DWORD));
}

inline long SetUserRegValue(LPCTSTR szValueName, DWORD dw)
{
    return SetRegValue(HKEY_CURRENT_USER,
            g_strBaseRegKey, NULL, NULL, szValueName,
            REG_DWORD, (const BYTE *) &dw, sizeof(DWORD));
}

#endif // BPCREG_H
