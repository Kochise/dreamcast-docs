//////////////////////////////////////////////////////////////////////////////
//
//  File Name 
//      TRACES.CPP
//
//  Description
//      This file implements tracing functions for sending debug/trace strings
//      to an attached debug monitor, the serial port, or a log file.
//
//  Author
//      Irving De la Cruz
//
//  Revision: 1.3
//
// Written for Microsoft Windows Developer Support
// Copyright (c) 1994-1996 Microsoft Corporation. All rights reserved.
//

// These functions DO NOT support UNICODE of Multi-Byte character sets
// but can be easily extended to do so
#ifdef UNICODE
#undef UNICODE
#endif
#ifdef _UNICODE
#undef _UNICODE
#endif
#ifdef _MBCS
#undef _MBCS
#endif

#include <WINDOWS.H>
#ifndef TRACES_NO_MAPI
#include <MAPIDEFS.H>
#include <MAPITAGS.H> 
#include <MAPICODE.H>
#endif // TRACES_NO_MAPI

#ifndef ENABLE_DEBUG_OUTPUT
#define ENABLE_DEBUG_OUTPUT
#endif // ENABLE_DEBUG_OUTPUT
#include "TRACES.H"

///////////////////////////////////////////////////////////////////////////////
//
// USER SETTINGS FOR TRACING FUNCTIONS
// 
//  THIS IS THE ONLY PART THAT NEEDS TO BE ALTERED FOR A DIFFERENT DESTINATION 
//  OUTPUT PORT OR LOG FILE NAME
//

// Change the port as necessary, depending on the COM port to which the 
// debugger terminal is attached to.
#define COM_PORT_STRING         "COM1"
// Change the setting below to what ever is necessary. Check the Win32 
// documentation on the DCB (Data communication block) structure for other 
// valid values. Default: 9600, 8, N, 1
#define COM_BAUD_RATE           9600
#define COM_DATA_BYTE_SIZE      8
#define COM_PARITY              NOPARITY
#define COM_STOP_BIT            ONESTOPBIT

#define LOG_FILE_NAME           "C:\\MAPILOG.TXT"

static BOOL fFileInit   = FALSE;
static BOOL fComInit = FALSE;

static HANDLE hCom      = NULL;
static HANDLE hConsole  = NULL;
static HANDLE hLogFile  = NULL;

DWORD gTracesFlags = 0;

// Prototypes
inline void WINAPI OpenOutputHandles (void);
inline void WINAPI CloseOutputHandles (void);
inline void WINAPI WriteOutputString (LPSTR, DWORD);

void WINAPI InitTraces (DWORD dwFlags)
{
    if (dwFlags & (TRACES_CONSOLE |
                   TRACES_LOG_FILE |
                   TRACES_NO_COM_OUTPUT |
                   TRACES_NO_ASSERT_DIALOG))
    {
        gTracesFlags = dwFlags;
        if (gTracesFlags & TRACES_CONSOLE)
        {
            AllocConsole();
            hConsole = GetStdHandle (STD_OUTPUT_HANDLE);
            COORD coord;
            coord.X = 80;
            coord.Y = 300;
            SetConsoleScreenBufferSize( hConsole, coord );
        }
    }
}

void WINAPI UnInitTraces ()
{
    if (gTracesFlags & TRACES_CONSOLE)
    {
        FreeConsole();
    }
    if (!hLogFile)
    {
        CloseHandle (hLogFile);
    }
}

inline void WINAPI OpenOutputHandles ()
{
    if (!hCom && !(gTracesFlags & TRACES_NO_COM_OUTPUT))
    {   
        hCom = CreateFile (COM_PORT_STRING,
                           GENERIC_WRITE | GENERIC_READ,
                           0,
                           NULL,
                           OPEN_EXISTING,
                           0,
                           NULL); 
        if (INVALID_HANDLE_VALUE == hCom)
        {
            hCom = NULL;
        }
        else
        {
            DCB dcb;
            GetCommState (hCom, &dcb);
            dcb.BaudRate    = COM_BAUD_RATE;
            dcb.ByteSize    = COM_DATA_BYTE_SIZE;
            dcb.Parity      = COM_PARITY;
            dcb.StopBits    = COM_STOP_BIT;
            SetCommState (hCom, &dcb);
            if (!fComInit)
            {
                DWORD dwBytes;
                for (int i=0; i<55; i++)
                {
                    WriteFile (hCom, "\r\n", 2, &dwBytes, NULL);
                }
                fComInit = TRUE;
            }
        }
    }

    if (!hLogFile && (gTracesFlags & TRACES_LOG_FILE))
    {    
        hLogFile = CreateFile (LOG_FILE_NAME,
                               GENERIC_WRITE,
                               FILE_SHARE_READ | FILE_SHARE_WRITE,
                               NULL,
                               OPEN_ALWAYS,
                               0,
                               NULL);
        if (INVALID_HANDLE_VALUE == hLogFile)
        {
            hLogFile = NULL;
        }
        if (!fFileInit)
        {
            DWORD dwFileSize = GetFileSize (hLogFile, NULL);
            SetFilePointer (hLogFile, dwFileSize, NULL, FILE_BEGIN);

            char szTmpStr[64];
            DWORD dwBytes, nChars = wsprintf (szTmpStr, 
            "======================================================\r\n");
            WriteFile (hLogFile, szTmpStr, nChars, &dwBytes, NULL);
            SYSTEMTIME st;
            GetSystemTime (&st);
            nChars = wsprintf (szTmpStr, "Log Date: %d/%d/%d - %d:%d\r\n",
            st.wMonth, st.wDay, st.wYear, st.wHour, st.wMinute);
            WriteFile (hLogFile, szTmpStr, nChars, &dwBytes, NULL);
            nChars = wsprintf (szTmpStr, 
            "======================================================\r\n");
            WriteFile (hLogFile, szTmpStr, nChars, &dwBytes, NULL);
            fFileInit = TRUE;
        }
    }
}

inline void WINAPI CloseOutputHandles ()
{
    if (gTracesFlags & TRACES_NO_COM_OUTPUT)
    {
        return;
    }
    CloseHandle (hCom);
    hCom = NULL;
}

inline void WINAPI WriteOutputString (LPSTR pStr, DWORD dwSize)
{
    DWORD dwBytes;
    OpenOutputHandles ();
    if (hCom && !(gTracesFlags & TRACES_NO_COM_OUTPUT))
    {
        WriteFile (hCom, pStr, dwSize, &dwBytes, NULL);
    }

    if (hLogFile && (gTracesFlags & TRACES_LOG_FILE))
    {
        WriteFile (hLogFile, pStr, dwSize, &dwBytes, NULL);
    }

    if (hConsole && (gTracesFlags & TRACES_CONSOLE))
    {
        WriteFile (hConsole, pStr, dwSize, &dwBytes, NULL);
    }

    OutputDebugString (pStr);

    CloseOutputHandles();
}

void WINAPI TraceFn1 (LPSTR pString)
{
    char string[512];
    DWORD dwSize = wsprintf (string, "%s\r\n", pString);
    WriteOutputString (string, dwSize);
}


void WINAPI TraceFn2 (LPSTR pString, ULONG ulError)
{
    TCHAR   string[512];
    LPTSTR  szErr;

    switch(ulError)
    {        
        case E_FAIL                             : szErr = "E_FAIL";                         break;
        case E_INVALIDARG                       : szErr = "E_INVALIDARG";                   break;
        case E_NOINTERFACE                      : szErr = "E_NOINTERFACE";                  break;
        case E_OUTOFMEMORY                      : szErr = "E_OUTOFMEMORY";                  break;
        case E_ACCESSDENIED                     : szErr = "E_ACCESSDENIED";                 break;

#ifndef TRACES_NO_MAPI
        case MAPI_E_NO_SUPPORT                  : szErr = "MAPI_E_NO_SUPPORT";              break;
        case MAPI_E_BAD_CHARWIDTH               : szErr = "MAPI_E_BAD_CHARWIDTH";           break;
        case MAPI_E_STRING_TOO_LONG             : szErr = "MAPI_E_STRING_TOO_LONG";         break;
        case MAPI_E_UNKNOWN_FLAGS               : szErr = "MAPI_E_UNKNOWN_FLAGS";           break;
        case MAPI_E_INVALID_ENTRYID             : szErr = "MAPI_E_INVALID_ENTRYID";         break;
        case MAPI_E_INVALID_OBJECT              : szErr = "MAPI_E_INVALID_OBJECT";          break;
        case MAPI_E_OBJECT_CHANGED              : szErr = "MAPI_E_OBJECT_CHANGED";          break;
        case MAPI_E_OBJECT_DELETED              : szErr = "MAPI_E_OBJECT_DELETED";          break;
        case MAPI_E_BUSY                        : szErr = "MAPI_E_BUSY";                    break;
        case MAPI_E_NOT_ENOUGH_DISK             : szErr = "MAPI_E_NOT_ENOUGH_DISK";         break;
        case MAPI_E_NOT_ENOUGH_RESOURCES        : szErr = "MAPI_E_NOT_ENOUGH_RESOURCES";    break;
        case MAPI_E_NOT_FOUND                   : szErr = "MAPI_E_NOT_FOUND";               break;
        case MAPI_E_VERSION                     : szErr = "MAPI_E_VERSION";                 break;
        case MAPI_E_LOGON_FAILED                : szErr = "MAPI_E_LOGON_FAILED";            break;
        case MAPI_E_SESSION_LIMIT               : szErr = "MAPI_E_SESSION_LIMIT";           break;
        case MAPI_E_USER_CANCEL                 : szErr = "MAPI_E_USER_CANCEL";             break;
        case MAPI_E_UNABLE_TO_ABORT             : szErr = "MAPI_E_UNABLE_TO_ABORT";         break;
        case MAPI_E_NETWORK_ERROR               : szErr = "MAPI_E_NETWORK_ERROR";           break;
        case MAPI_E_DISK_ERROR                  : szErr = "MAPI_E_DISK_ERROR";              break;
        case MAPI_E_TOO_COMPLEX                 : szErr = "MAPI_E_TOO_COMPLEX";             break;
        case MAPI_E_BAD_COLUMN                  : szErr = "MAPI_E_BAD_COLUMN";              break;
        case MAPI_E_EXTENDED_ERROR              : szErr = "MAPI_E_EXTENDED_ERROR";          break;
        case MAPI_E_COMPUTED                    : szErr = "MAPI_E_COMPUTED";                break;
        case MAPI_E_CORRUPT_DATA                : szErr = "MAPI_E_CORRUPT_DATA";            break;
        case MAPI_E_UNCONFIGURED                : szErr = "MAPI_E_UNCONFIGURED";            break;
        case MAPI_E_FAILONEPROVIDER             : szErr = "MAPI_E_FAILONEPROVIDER";         break;
        case MAPI_E_END_OF_SESSION              : szErr = "MAPI_E_END_OF_SESSION";          break;
        case MAPI_E_UNKNOWN_ENTRYID             : szErr = "MAPI_E_UNKNOWN_ENTRYID";         break;
        case MAPI_E_MISSING_REQUIRED_COLUMN     : szErr = "MAPI_E_MISSING_REQUIRED_COLUMN"; break;
        case MAPI_W_NO_SERVICE                  : szErr = "MAPI_W_NO_SERVICE";              break;
        case MAPI_E_BAD_VALUE                   : szErr = "MAPI_E_BAD_VALUE";               break;
        case MAPI_E_INVALID_TYPE                : szErr = "MAPI_E_INVALID_TYPE";            break;
        case MAPI_E_TYPE_NO_SUPPORT             : szErr = "MAPI_E_TYPE_NO_SUPPORT";         break;
        case MAPI_E_UNEXPECTED_TYPE             : szErr = "MAPI_E_UNEXPECTED_TYPE";         break;
        case MAPI_E_TOO_BIG                     : szErr = "MAPI_E_TOO_BIG";                 break;
        case MAPI_E_DECLINE_COPY                : szErr = "MAPI_E_DECLINE_COPY";            break;
        case MAPI_E_UNEXPECTED_ID               : szErr = "MAPI_E_UNEXPECTED_ID";           break;
        case MAPI_W_ERRORS_RETURNED             : szErr = "MAPI_W_ERRORS_RETURNED";         break;
        case MAPI_E_UNABLE_TO_COMPLETE          : szErr = "MAPI_E_UNABLE_TO_COMPLETE";      break;
        case MAPI_E_TIMEOUT                     : szErr = "MAPI_E_TIMEOUT";                 break;
        case MAPI_E_TABLE_EMPTY                 : szErr = "MAPI_E_TABLE_EMPTY";             break;
        case MAPI_E_TABLE_TOO_BIG               : szErr = "MAPI_E_TABLE_TOO_BIG";           break;
        case MAPI_E_INVALID_BOOKMARK            : szErr = "MAPI_E_INVALID_BOOKMARK";        break;
        case MAPI_W_POSITION_CHANGED            : szErr = "MAPI_W_POSITION_CHANGED";        break;
        case MAPI_W_APPROX_COUNT                : szErr = "MAPI_W_APPROX_COUNT";            break;
        case MAPI_E_WAIT                        : szErr = "MAPI_E_WAIT";                    break;
        case MAPI_E_CANCEL                      : szErr = "MAPI_E_CANCEL";                  break;
        case MAPI_E_NOT_ME                      : szErr = "MAPI_E_NOT_ME";                  break;
        case MAPI_W_CANCEL_MESSAGE              : szErr = "MAPI_W_CANCEL_MESSAGE";          break;
        case MAPI_E_CORRUPT_STORE               : szErr = "MAPI_E_CORRUPT_STORE";           break;
        case MAPI_E_NOT_IN_QUEUE                : szErr = "MAPI_E_NOT_IN_QUEUE";            break;
        case MAPI_E_NO_SUPPRESS                 : szErr = "MAPI_E_NO_SUPPRESS";             break;
        case MAPI_E_COLLISION                   : szErr = "MAPI_E_COLLISION";               break;
        case MAPI_E_NOT_INITIALIZED             : szErr = "MAPI_E_NOT_INITIALIZED";         break;
        case MAPI_E_NON_STANDARD                : szErr = "MAPI_E_NON_STANDARD";            break;
        case MAPI_E_NO_RECIPIENTS               : szErr = "MAPI_E_NO_RECIPIENTS";           break;
        case MAPI_E_SUBMITTED                   : szErr = "MAPI_E_SUBMITTED";               break;
        case MAPI_E_HAS_FOLDERS                 : szErr = "MAPI_E_HAS_FOLDERS";             break;
        case MAPI_E_HAS_MESSAGES                : szErr = "MAPI_E_HAS_MESSAGES";            break;
        case MAPI_E_FOLDER_CYCLE                : szErr = "MAPI_E_FOLDER_CYCLE";            break;
        case MAPI_W_PARTIAL_COMPLETION          : szErr = "MAPI_W_PARTIAL_COMPLETION";      break;
        case MAPI_E_AMBIGUOUS_RECIP             : szErr = "MAPI_E_AMBIGUOUS_RECIP";         break;
        
        #ifndef MAPI_E_UNKNOWN_CPID
        #define MAPI_E_UNKNOWN_CPID             MAKE_MAPI_E( 0x11E )
        #define MAPI_E_UNKNOWN_LCID             MAKE_MAPI_E( 0x11F )
        #endif
        case MAPI_E_UNKNOWN_CPID                : szErr = "MAPI_E_UNKNOWN_CPID";            break;
        case MAPI_E_UNKNOWN_LCID                : szErr = "MAPI_E_UNKNOWN_LCID";            break;
#endif // TRACES_NO_MAPI

        case STG_E_INVALIDFUNCTION              : szErr = "STG_E_INVALIDFUNCTION";          break;
        case STG_E_FILENOTFOUND                 : szErr = "STG_E_FILENOTFOUND";             break;
        case STG_E_PATHNOTFOUND                 : szErr = "STG_E_PATHNOTFOUND";             break;
        case STG_E_TOOMANYOPENFILES             : szErr = "STG_E_TOOMANYOPENFILES";         break;
        case STG_E_ACCESSDENIED                 : szErr = "STG_E_ACCESSDENIED";             break;
        case STG_E_INVALIDHANDLE                : szErr = "STG_E_INVALIDHANDLE";            break;
        case STG_E_INSUFFICIENTMEMORY           : szErr = "STG_E_INSUFFICIENTMEMORY";       break;
        case STG_E_INVALIDPOINTER               : szErr = "STG_E_INVALIDPOINTER";           break;
        case STG_E_NOMOREFILES                  : szErr = "STG_E_NOMOREFILES";              break;
        case STG_E_DISKISWRITEPROTECTED         : szErr = "STG_E_DISKISWRITEPROTECTED";     break;
        case STG_E_SEEKERROR                    : szErr = "STG_E_SEEKERROR";                break;
        case STG_E_WRITEFAULT                   : szErr = "STG_E_WRITEFAULT";               break;
        case STG_E_READFAULT                    : szErr = "STG_E_READFAULT";                break;
        case STG_E_SHAREVIOLATION               : szErr = "STG_E_SHAREVIOLATION";           break;
        case STG_E_LOCKVIOLATION                : szErr = "STG_E_LOCKVIOLATION";            break;
        case STG_E_FILEALREADYEXISTS            : szErr = "STG_E_FILEALREADYEXISTS";        break;
        case STG_E_INVALIDPARAMETER             : szErr = "STG_E_INVALIDPARAMETER";         break;
        case STG_E_MEDIUMFULL                   : szErr = "STG_E_MEDIUMFULL";               break;
        case STG_E_ABNORMALAPIEXIT              : szErr = "STG_E_ABNORMALAPIEXIT";          break;
        case STG_E_INVALIDHEADER                : szErr = "STG_E_INVALIDHEADER";            break;
        case STG_E_INVALIDNAME                  : szErr = "STG_E_INVALIDNAME";              break;
        case STG_E_UNKNOWN                      : szErr = "STG_E_UNKNOWN";                  break;
        case STG_E_UNIMPLEMENTEDFUNCTION        : szErr = "STG_E_UNIMPLEMENTEDFUNCTION";    break;
        case STG_E_INVALIDFLAG                  : szErr = "STG_E_INVALIDFLAG";              break;
        case STG_E_INUSE                        : szErr = "STG_E_INUSE";                    break;
        case STG_E_NOTCURRENT                   : szErr = "STG_E_NOTCURRENT";               break;
        case STG_E_REVERTED                     : szErr = "STG_E_REVERTED";                 break;
        case STG_E_CANTSAVE                     : szErr = "STG_E_CANTSAVE";                 break;
        case STG_E_OLDFORMAT                    : szErr = "STG_E_OLDFORMAT";                break;
        case STG_E_OLDDLL                       : szErr = "STG_E_OLDDLL";                   break;
        case STG_E_SHAREREQUIRED                : szErr = "STG_E_SHAREREQUIRED";            break;
        case STG_E_NOTFILEBASEDSTORAGE          : szErr = "STG_E_NOTFILEBASEDSTORAGE";      break;
        case STG_S_CONVERTED                    : szErr = "STG_S_CONVERTED";                break;


        case HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND) :         szErr = "WIN32 - ERROR_FILE_NOT_FOUND";         break;
        case HRESULT_FROM_WIN32(ERROR_INVALID_DRIVE) :          szErr = "WIN32 - ERROR_INVALID_DRIVE";          break;
        case HRESULT_FROM_WIN32(ERROR_INVALID_HANDLE) :         szErr = "WIN32 - ERROR_INVALID_HANDLE";         break;
        case HRESULT_FROM_WIN32(ERROR_SEEK) :                   szErr = "WIN32 - ERROR_SEEK";                   break;
        case HRESULT_FROM_WIN32(ERROR_SECTOR_NOT_FOUND) :       szErr = "WIN32 - ERROR_SECTOR_NOT_FOUND";       break;
        case HRESULT_FROM_WIN32(ERROR_WRITE_FAULT) :            szErr = "WIN32 - ERROR_WRITE_FAULT";            break;
        case HRESULT_FROM_WIN32(ERROR_READ_FAULT) :             szErr = "WIN32 - ERROR_READ_FAULT";             break;
        case HRESULT_FROM_WIN32(ERROR_SHARING_VIOLATION) :      szErr = "WIN32 - ERROR_SHARING_VIOLATION";      break;
        case HRESULT_FROM_WIN32(ERROR_LOCK_VIOLATION) :         szErr = "WIN32 - ERROR_LOCK_VIOLATION";         break;
        case HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED) :          szErr = "WIN32 - ERROR_NOT_SUPPORTED";          break;
        case HRESULT_FROM_WIN32(ERROR_NO_SUCH_USER) :           szErr = "WIN32 - ERROR_NO_SUCH_USER";           break;
        case HRESULT_FROM_WIN32(ERROR_NO_SUCH_GROUP) :          szErr = "WIN32 - ERROR_NO_SUCH_GROUP";          break;
        case HRESULT_FROM_WIN32(ERROR_WRONG_PASSWORD) :         szErr = "WIN32 - ERROR_WRONG_PASSWORD";         break;
        case HRESULT_FROM_WIN32(ERROR_INVALID_PASSWORD) :       szErr = "WIN32 - ERROR_INVALID_PASSWORD";       break;
        case HRESULT_FROM_WIN32(ERROR_INVALID_FLAGS) :          szErr = "WIN32 - ERROR_INVALID_FLAGS";          break;
        case HRESULT_FROM_WIN32(ERROR_BAD_USERNAME) :           szErr = "WIN32 - ERROR_BAD_USERNAME";           break;
        case HRESULT_FROM_WIN32(ERROR_BROKEN_PIPE) :            szErr = "WIN32 - ERROR_BROKEN_PIPE";            break;
        case HRESULT_FROM_WIN32(ERROR_PIPE_BUSY) :              szErr = "WIN32 - ERROR_PIPE_BUSY";              break;
        case HRESULT_FROM_WIN32(ERROR_PIPE_NOT_CONNECTED):      szErr = "WIN32 - ERROR_PIPE_NOT_CONNECTED";     break;
        case HRESULT_FROM_WIN32(ERROR_PIPE_CONNECTED):          szErr = "WIN32 - ERROR_PIPE_CONNECTED";         break;
        case HRESULT_FROM_WIN32(ERROR_STATIC_INIT) :            szErr = "WIN32 - ERROR_STATIC_INIT";            break;
        case HRESULT_FROM_WIN32(ERROR_INVALID_FUNCTION) :       szErr = "WIN32 - ERROR_INVALID_FUNCTION";       break;
        case HRESULT_FROM_WIN32(ERROR_EXCEPTION_IN_SERVICE):    szErr = "WIN32 - ERROR_EXCEPTION_IN_SERVICE";   break;
        case HRESULT_FROM_WIN32(ERROR_CANCELLED):               szErr = "WIN32 - ERROR_CANCELLED";              break;
        case HRESULT_FROM_WIN32(ERROR_PARTIAL_COPY):            szErr = "WIN32 - ERROR_PARTIAL_COPY";           break;
        case HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER):     szErr = "WIN32 - ERROR_INSUFFICIENT_BUFFER";    break;
        case HRESULT_FROM_WIN32(ERROR_NO_UNICODE_TRANSLATION):  szErr = "WIN32 - ERROR_NO_UNICODE_TRANSLATION"; break;
        case HRESULT_FROM_WIN32(ERROR_INVALID_ACCOUNT_NAME):    szErr = "WIN32 - ERROR_INVALID_ACCOUNT_NAME";   break;
        case HRESULT_FROM_WIN32(ERROR_PRIVILEGE_NOT_HELD):      szErr = "WIN32 - ERROR_INVALID_ACCOUNT_NAME";   break;
        case HRESULT_FROM_WIN32(ERROR_BAD_NET_NAME):            szErr = "WIN32 - ERROR_BAD_NET_NAME";           break;
        case HRESULT_FROM_WIN32(ERROR_SERVICE_NO_THREAD):       szErr = "WIN32 - ERROR_SERVICE_NO_THREAD";      break;
        case HRESULT_FROM_WIN32(ERROR_SHUTDOWN_IN_PROGRESS):    szErr = "WIN32 - ERROR_SHUTDOWN_IN_PROGRESS";   break;
        case HRESULT_FROM_WIN32(ERROR_CONNECTION_INVALID):      szErr = "WIN32 - ERROR_CONNECTION_INVALID";     break;
        case HRESULT_FROM_WIN32(ERROR_HANDLE_EOF):              szErr = "WIN32 - ERROR_HANDLE_EOF";             break;
        case HRESULT_FROM_WIN32(ERROR_ALREADY_EXISTS):          szErr = "WIN32 - ERROR_ALREADY_EXISTS";         break;
        case HRESULT_FROM_WIN32(ERROR_HOST_UNREACHABLE):        szErr = "WIN32 - ERROR_HOST_UNREACHABLE";       break;
        case HRESULT_FROM_WIN32(ERROR_FILE_EXISTS):             szErr = "WIN32 - ERROR_FILE_EXISTS";            break;
        case HRESULT_FROM_WIN32(ERROR_IO_PENDING):              szErr = "WIN32 - ERROR_IO_PENDING";             break;
        case HRESULT_FROM_WIN32(ERROR_ILL_FORMED_PASSWORD):     szErr = "WIN32 - ERROR_ILL_FORMED_PASSWORD";    break;
        case HRESULT_FROM_WIN32(ERROR_PASSWORD_RESTRICTION):    szErr = "WIN32 - ERROR_PASSWORD_RESTRICTION";   break;
        case HRESULT_FROM_WIN32(ERROR_LOGON_FAILURE):           szErr = "WIN32 - ERROR_LOGON_FAILURE";          break;
        case HRESULT_FROM_WIN32(ERROR_ACCOUNT_RESTRICTION):     szErr = "WIN32 - ERROR_ACCOUNT_RESTRICTION";    break;
        case HRESULT_FROM_WIN32(ERROR_INVALID_LOGON_HOURS):     szErr = "WIN32 - ERROR_INVALID_LOGON_HOURS";    break;
        case HRESULT_FROM_WIN32(ERROR_INVALID_WORKSTATION):     szErr = "WIN32 - ERROR_INVALID_WORKSTATION";    break;
        case HRESULT_FROM_WIN32(ERROR_PASSWORD_EXPIRED):        szErr = "WIN32 - ERROR_PASSWORD_EXPIRED";       break;
        case HRESULT_FROM_WIN32(ERROR_ACCOUNT_DISABLED):        szErr = "WIN32 - ERROR_ACCOUNT_DISABLED";       break;
        case HRESULT_FROM_WIN32(ERROR_NONE_MAPPED):             szErr = "WIN32 - ERROR_NONE_MAPPED";            break;
        case HRESULT_FROM_WIN32(ERROR_FAILED_SERVICE_CONTROLLER_CONNECT) : szErr = "WIN32 - ERROR_FAILED_SERVICE_CONTROLLER_CONNECT"; break;

        case MAKE_HRESULT(1, FACILITY_RPC, RPC_S_CALL_FAILED):              szErr = "RPC Error - RPC_S_CALL_FAILED";            break;
        case MAKE_HRESULT(1, FACILITY_RPC, RPC_S_CALL_FAILED_DNE):          szErr = "RPC Error - RPC_S_CALL_FAILED_DNE";        break;
        case MAKE_HRESULT(1, FACILITY_RPC, RPC_S_PROTOCOL_ERROR):           szErr = "RPC Error - RPC_S_PROTOCOL_ERROR";         break;
        case MAKE_HRESULT(1, FACILITY_RPC, RPC_S_UNSUPPORTED_TRANS_SYN):    szErr = "RPC Error - RPC_S_UNSUPPORTED_TRANS_SYN";  break;
        case MAKE_HRESULT(1, FACILITY_RPC, RPC_S_UNSUPPORTED_TYPE):         szErr = "RPC Error - RPC_S_UNSUPPORTED_TYPE";       break;
        case MAKE_HRESULT(1, FACILITY_RPC, RPC_S_INVALID_TAG):              szErr = "RPC Error - RPC_S_INVALID_TAG";            break;
        case MAKE_HRESULT(1, FACILITY_RPC, RPC_S_INVALID_BOUND):            szErr = "RPC Error - RPC_S_INVALID_BOUND";          break;
        case MAKE_HRESULT(1, FACILITY_RPC, RPC_S_NO_ENTRY_NAME):            szErr = "RPC Error - RPC_S_NO_ENTRY_NAME";          break;
        case MAKE_HRESULT(1, FACILITY_RPC, RPC_S_INVALID_NAME_SYNTAX):      szErr = "RPC Error - RPC_S_INVALID_NAME_SYNTAX";    break;
        case MAKE_HRESULT(1, FACILITY_RPC, RPC_S_UNSUPPORTED_NAME_SYNTAX):  szErr = "RPC Error - RPC_S_UNSUPPORTED_NAME_SYNTAX";break;
        case MAKE_HRESULT(1, FACILITY_RPC, RPC_S_DUPLICATE_ENDPOINT):       szErr = "RPC Error - RPC_S_DUPLICATE_ENDPOINT";     break;
        case MAKE_HRESULT(1, FACILITY_RPC, RPC_S_INVALID_STRING_BINDING):   szErr = "RPC Error - RPC_S_INVALID_STRING_BINDING"; break;
        case MAKE_HRESULT(1, FACILITY_RPC, RPC_S_WRONG_KIND_OF_BINDING):    szErr = "RPC Error - RPC_S_WRONG_KIND_OF_BINDING";  break;
        case MAKE_HRESULT(1, FACILITY_RPC, RPC_S_INVALID_BINDING):          szErr = "RPC Error - RPC_S_INVALID_BINDING";        break;
        case MAKE_HRESULT(1, FACILITY_RPC, RPC_S_PROTSEQ_NOT_SUPPORTED):    szErr = "RPC Error - RPC_S_PROTSEQ_NOT_SUPPORTED";  break;
        case MAKE_HRESULT(1, FACILITY_RPC, RPC_S_INVALID_RPC_PROTSEQ):      szErr = "RPC Error - RPC_S_INVALID_RPC_PROTSEQ";    break;
        case MAKE_HRESULT(1, FACILITY_RPC, RPC_S_INVALID_STRING_UUID):      szErr = "RPC Error - RPC_S_INVALID_STRING_UUID";    break;
        case MAKE_HRESULT(1, FACILITY_RPC, RPC_S_INVALID_ENDPOINT_FORMAT):  szErr = "RPC Error - RPC_S_INVALID_ENDPOINT_FORMAT";break;
        case MAKE_HRESULT(1, FACILITY_RPC, RPC_S_INVALID_NET_ADDR):         szErr = "RPC Error - RPC_S_NO_ENDPOINT_FOUND";      break;
        case MAKE_HRESULT(1, FACILITY_RPC, RPC_S_NO_ENDPOINT_FOUND):        szErr = "RPC Error - RPC_S_DUPLICATE_ENDPOINT";     break;
        case MAKE_HRESULT(1, FACILITY_RPC, RPC_S_INVALID_TIMEOUT):          szErr = "RPC Error - RPC_S_INVALID_TIMEOUT";        break;
        case MAKE_HRESULT(1, FACILITY_RPC, RPC_S_OBJECT_NOT_FOUND):         szErr = "RPC Error - RPC_S_OBJECT_NOT_FOUND";       break;
        case MAKE_HRESULT(1, FACILITY_RPC, RPC_S_ALREADY_REGISTERED):       szErr = "RPC Error - RPC_S_ALREADY_REGISTERED";     break;
        case MAKE_HRESULT(1, FACILITY_RPC, RPC_S_TYPE_ALREADY_REGISTERED):  szErr = "RPC Error - RPC_S_TYPE_ALREADY_REGISTERED";break;
        case MAKE_HRESULT(1, FACILITY_RPC, RPC_S_ALREADY_LISTENING):        szErr = "RPC Error - RPC_S_ALREADY_LISTENING";      break;
        case MAKE_HRESULT(1, FACILITY_RPC, RPC_S_NO_PROTSEQS_REGISTERED):   szErr = "RPC Error - RPC_S_NO_PROTSEQS_REGISTERED"; break;
        case MAKE_HRESULT(1, FACILITY_RPC, RPC_S_NOT_LISTENING):            szErr = "RPC Error - RPC_S_NOT_LISTENING";          break;
        case MAKE_HRESULT(1, FACILITY_RPC, RPC_S_UNKNOWN_MGR_TYPE):         szErr = "RPC Error - RPC_S_UNKNOWN_MGR_TYPE";       break;
        case MAKE_HRESULT(1, FACILITY_RPC, RPC_S_UNKNOWN_IF):               szErr = "RPC Error - RPC_S_UNKNOWN_IF";             break;
        case MAKE_HRESULT(1, FACILITY_RPC, RPC_S_NO_BINDINGS):              szErr = "RPC Error - RPC_S_NO_BINDINGS";            break;
        case MAKE_HRESULT(1, FACILITY_RPC, RPC_S_NO_PROTSEQS):              szErr = "RPC Error - RPC_S_NO_PROTSEQS";            break;
        case MAKE_HRESULT(1, FACILITY_RPC, RPC_S_CANT_CREATE_ENDPOINT):     szErr = "RPC Error - RPC_S_CANT_CREATE_ENDPOINT";   break;
        case MAKE_HRESULT(1, FACILITY_RPC, RPC_S_OUT_OF_RESOURCES):         szErr = "RPC Error - RPC_S_OUT_OF_RESOURCES";       break;
        case MAKE_HRESULT(1, FACILITY_RPC, RPC_S_SERVER_UNAVAILABLE):       szErr = "RPC Error - RPC_S_SERVER_UNAVAILABLE";     break;
        case MAKE_HRESULT(1, FACILITY_RPC, RPC_S_SERVER_TOO_BUSY):          szErr = "RPC Error - RPC_S_SERVER_TOO_BUSY";        break;

        default : szErr = "UNKNOWN"; break;
    }   

    DWORD dwSize = wsprintf (string, "Error in %s, %s (%#08x)\r\n", pString, szErr, ulError);
    WriteOutputString(string, dwSize);
}

void WINAPI TraceFn3 (LPSTR pString)
{
    WriteOutputString (pString, lstrlen(pString));
}

void __cdecl TraceFn4 (BOOL fDebuggerOnly, LPSTR pszFormat, ...)
{
    char string[512];
    va_list vl;
    va_start(vl, pszFormat);
    DWORD dwSize = wvsprintf (string, pszFormat, vl);
    va_end(vl);
    strcat(string, "\r\n");
    if (fDebuggerOnly)
    {
        OutputDebugString (string);
    }
    else
    {
        dwSize += 2;
        WriteOutputString (string, dwSize);
    }
}

void WINAPI TraceIO (ULONG hResult)
{
    if (!(hResult<0))
    {
        return;
    }
    char string[34];
    DWORD dwSize = wsprintf (string,"I/O Function Failed: %#08x\r\n", hResult);
    WriteOutputString (string, dwSize);
}

void WINAPI TraceIO2 (LPSTR pszMsg, ULONG hResult)
{
    if (!(hResult<0))
    {
        return;
    }
    WriteOutputString (pszMsg, lstrlen(pszMsg));
    char string[48];
    DWORD dwSize = wsprintf (string,": I/O Function Failed: %#08x\r\n", hResult);
    WriteOutputString (string, dwSize);
}

void WINAPI AssertNow (LPSTR pszAssertMsg)
{
    HWND hWnd = GetActiveWindow();
    int nResponse = MessageBox (hWnd, 
                                pszAssertMsg,
                                "WARNING",
                                MB_YESNO | MB_ICONSTOP | 
                                MB_TASKMODAL | MB_SETFOREGROUND);
    if (IDYES == nResponse)
    {
        DebugBreak();
    }
}

void WINAPI AssertStatement (LPSTR pszFile, ULONG ulLine)
{
    if (gTracesFlags & TRACES_NO_ASSERTS)
    {
        return;
    }
    char szStr[1024];
    wsprintf (szStr, "Assertion failed in File: %s, Line: %d", pszFile, ulLine);
    TraceMessage (szStr);
    if (gTracesFlags & TRACES_NO_ASSERT_DIALOG)
    {
        return;
    }
    wsprintf (szStr, "%s - Break into the debugger?", szStr);
    AssertNow (szStr);
}

void WINAPI AssertStatementWithMsg (LPSTR pszMsg, LPSTR pszFile, ULONG ulLine)
{
    if (gTracesFlags & TRACES_NO_ASSERTS)
    {
        return;
    }
    char szStr[2048];
    wsprintf (szStr, "%s\r\nAssertion in File: %s, Line: %d", pszMsg, pszFile, ulLine);
    TraceMessage (szStr);
    if (gTracesFlags & TRACES_NO_ASSERT_DIALOG)
    {
        return;
    }
    wsprintf (szStr, "%s\r\nAssertion in File: %s, Line: %d\r\nBreak into the debugger?", pszMsg, pszFile, ulLine);
    AssertNow (szStr);
}


#ifndef TRACES_NO_MAPI

void WINAPI TraceProp (ULONG ulPropTag)
{
    char * pszTag;
    char message [128];
    char szUnkType[32];
    char szUnkTag[32];
    DWORD dwSize;
    switch (PROP_ID(ulPropTag))
    {
        // Message envelope properties
        case PROP_ID(PR_ACKNOWLEDGEMENT_MODE) :                     pszTag = "PR_ACKNOWLEDGEMENT_MODE";                         break;
        case PROP_ID(PR_ALTERNATE_RECIPIENT_ALLOWED) :              pszTag = "PR_ALTERNATE_RECIPIENT_ALLOWED";                  break;
        case PROP_ID(PR_AUTHORIZING_USERS) :                        pszTag = "PR_AUTHORIZING_USERS";                            break;
        case PROP_ID(PR_AUTO_FORWARD_COMMENT) :                     pszTag = "PR_AUTO_FORWARD_COMMENT";                         break;
        case PROP_ID(PR_AUTO_FORWARDED) :                           pszTag = "PR_AUTO_FORWARDED";                               break;
        case PROP_ID(PR_CONTENT_CONFIDENTIALITY_ALGORITHM_ID) :     pszTag = "PR_CONTENT_CONFIDENTIALITY_ALGORITHM_ID";         break;
        case PROP_ID(PR_CONTENT_CORRELATOR) :                       pszTag = "PR_CONTENT_CORRELATOR";                           break;
        case PROP_ID(PR_CONTENT_IDENTIFIER) :                       pszTag = "PR_CONTENT_IDENTIFIER";                           break;
        case PROP_ID(PR_CONTENT_LENGTH) :                           pszTag = "PR_CONTENT_LENGTH";                               break;
        case PROP_ID(PR_CONTENT_RETURN_REQUESTED) :                 pszTag = "PR_CONTENT_RETURN_REQUESTED";                     break;
        case PROP_ID(PR_CONVERSATION_KEY) :                         pszTag = "PR_CONVERSATION_KEY";                             break;
        case PROP_ID(PR_CONVERSION_EITS) :                          pszTag = "PR_CONVERSION_EITS";                              break;
        case PROP_ID(PR_CONVERSION_WITH_LOSS_PROHIBITED) :          pszTag = "PR_CONVERSION_WITH_LOSS_PROHIBITED";              break;
        case PROP_ID(PR_CONVERTED_EITS) :                           pszTag = "PR_CONVERTED_EITS";                               break;
        case PROP_ID(PR_DEFERRED_DELIVERY_TIME) :                   pszTag = "PR_DEFERRED_DELIVERY_TIME";                       break;
        case PROP_ID(PR_DELIVER_TIME) :                             pszTag = "PR_DELIVER_TIME";                                 break;
        case PROP_ID(PR_DISCARD_REASON) :                           pszTag = "PR_DISCARD_REASON";                               break;
        case PROP_ID(PR_DISCLOSURE_OF_RECIPIENTS) :                 pszTag = "PR_DISCLOSURE_OF_RECIPIENTS";                     break;
        case PROP_ID(PR_DL_EXPANSION_HISTORY) :                     pszTag = "PR_DL_EXPANSION_HISTORY";                         break;
        case PROP_ID(PR_DL_EXPANSION_PROHIBITED) :                  pszTag = "PR_DL_EXPANSION_PROHIBITED";                      break;
        case PROP_ID(PR_EXPIRY_TIME) :                              pszTag = "PR_EXPIRY_TIME";                                  break;
        case PROP_ID(PR_IMPLICIT_CONVERSION_PROHIBITED) :           pszTag = "PR_IMPLICIT_CONVERSION_PROHIBITED";               break;
        case PROP_ID(PR_IMPORTANCE) :                               pszTag = "PR_IMPORTANCE";                                   break;
        case PROP_ID(PR_IPM_ID) :                                   pszTag = "PR_IPM_ID";                                       break;
        case PROP_ID(PR_LATEST_DELIVERY_TIME) :                     pszTag = "PR_LATEST_DELIVERY_TIME";                         break;
        case PROP_ID(PR_MESSAGE_CLASS) :                            pszTag = "PR_MESSAGE_CLASS";                                break;
        case PROP_ID(PR_MESSAGE_DELIVERY_ID) :                      pszTag = "PR_MESSAGE_DELIVERY_ID";                          break;   
        case PROP_ID(PR_MESSAGE_SECURITY_LABEL) :                   pszTag = "PR_MESSAGE_SECURITY_LABEL";                       break;   
        case PROP_ID(PR_OBSOLETED_IPMS) :                           pszTag = "PR_OBSOLETED_IPMS";                               break;   
        case PROP_ID(PR_ORIGINALLY_INTENDED_RECIPIENT_NAME) :       pszTag = "PR_ORIGINALLY_INTENDED_RECIPIENT_NAME";           break;   
        case PROP_ID(PR_ORIGINAL_EITS) :                            pszTag = "PR_ORIGINAL_EITS";                                break;   
        case PROP_ID(PR_ORIGINATOR_CERTIFICATE) :                   pszTag = "PR_ORIGINATOR_CERTIFICATE";                       break;   
        case PROP_ID(PR_ORIGINATOR_DELIVERY_REPORT_REQUESTED) :     pszTag = "PR_ORIGINATOR_DELIVERY_REPORT_REQUESTED";         break;   
        case PROP_ID(PR_ORIGINATOR_RETURN_ADDRESS) :                pszTag = "PR_ORIGINATOR_RETURN_ADDRESS";                    break;   
        case PROP_ID(PR_PARENT_KEY) :                               pszTag = "PR_PARENT_KEY";                                   break;   
        case PROP_ID(PR_PRIORITY) :                                 pszTag = "PR_PRIORITY";                                     break;   
        case PROP_ID(PR_ORIGIN_CHECK) :                             pszTag = "PR_ORIGIN_CHECK";                                 break;   
        case PROP_ID(PR_PROOF_OF_SUBMISSION_REQUESTED) :            pszTag = "PR_PROOF_OF_SUBMISSION_REQUESTED";                break;   
        case PROP_ID(PR_READ_RECEIPT_REQUESTED) :                   pszTag = "PR_READ_RECEIPT_REQUESTED";                       break;   
        case PROP_ID(PR_RECEIPT_TIME) :                             pszTag = "PR_RECEIPT_TIME";                                 break;   
        case PROP_ID(PR_RECIPIENT_REASSIGNMENT_PROHIBITED) :        pszTag = "PR_RECIPIENT_REASSIGNMENT_PROHIBITED";            break;   
        case PROP_ID(PR_REDIRECTION_HISTORY) :                      pszTag = "PR_REDIRECTION_HISTORY";                          break;   
        case PROP_ID(PR_RELATED_IPMS) :                             pszTag = "PR_RELATED_IPMS";                                 break;   

        #ifndef PR_ORIGINAL_SENSITIVITY
        #define PR_ORIGINAL_SENSITIVITY                             PROP_TAG( PT_LONG,      0x002E)
        #endif
        case PROP_ID(PR_ORIGINAL_SENSITIVITY) :                     pszTag = "PR_ORIGINAL_SENSITIVITY";                         break;

        case PROP_ID(PR_LANGUAGES) :                                pszTag = "PR_LANGUAGES";                                    break;   
        case PROP_ID(PR_REPLY_TIME) :                               pszTag = "PR_REPLY_TIME";                                   break;   
        case PROP_ID(PR_REPORT_TAG) :                               pszTag = "PR_REPORT_TAG";                                   break;   
        case PROP_ID(PR_REPORT_TIME) :                              pszTag = "PR_REPORT_TIME";                                  break;   
        case PROP_ID(PR_RETURNED_IPM) :                             pszTag = "PR_RETURNED_IPM";                                 break;   
        case PROP_ID(PR_SECURITY) :                                 pszTag = "PR_SECURITY";                                     break;   
        case PROP_ID(PR_INCOMPLETE_COPY) :                          pszTag = "PR_INCOMPLETE_COPY";                              break;       
        case PROP_ID(PR_SENSITIVITY) :                              pszTag = "PR_SENSITIVITY";                                  break;   
        case PROP_ID(PR_SUBJECT) :                                  pszTag = "PR_SUBJECT";                                      break;   
        case PROP_ID(PR_SUBJECT_IPM) :                              pszTag = "PR_SUBJECT_IPM";                                  break;   
        case PROP_ID(PR_CLIENT_SUBMIT_TIME) :                       pszTag = "PR_CLIENT_SUBMIT_TIME";                           break;   
        case PROP_ID(PR_REPORT_NAME) :                              pszTag = "PR_REPORT_NAME";                                  break;   
        case PROP_ID(PR_SENT_REPRESENTING_SEARCH_KEY) :             pszTag = "PR_SENT_REPRESENTING_SEARCH_KEY";                 break;   
        case PROP_ID(PR_X400_CONTENT_TYPE) :                        pszTag = "PR_X400_CONTENT_TYPE";                            break;   
        case PROP_ID(PR_NON_RECEIPT_REASON) :                       pszTag = "PR_NON_RECEIPT_REASON";                           break;   
        case PROP_ID(PR_RECEIVED_BY_ENTRYID) :                      pszTag = "PR_RECEIVED_BY_ENTRYID";                          break;   
        case PROP_ID(PR_RECEIVED_BY_NAME) :                         pszTag = "PR_RECEIVED_BY_NAME";                             break;   
        case PROP_ID(PR_SENT_REPRESENTING_ENTRYID) :                pszTag = "PR_SENT_REPRESENTING_ENTRYID";                    break;   
        case PROP_ID(PR_SENT_REPRESENTING_NAME) :                   pszTag = "PR_SENT_REPRESENTING_NAME";                       break;   
        case PROP_ID(PR_RCVD_REPRESENTING_ENTRYID) :                pszTag = "PR_RCVD_REPRESENTING_ENTRYID";                    break;   
        case PROP_ID(PR_RCVD_REPRESENTING_NAME) :                   pszTag = "PR_RCVD_REPRESENTING_NAME";                       break;   
        case PROP_ID(PR_REPORT_ENTRYID) :                           pszTag = "PR_REPORT_ENTRYID";                               break;   
        case PROP_ID(PR_READ_RECEIPT_ENTRYID) :                     pszTag = "PR_READ_RECEIPT_ENTRYID";                         break;   
        case PROP_ID(PR_MESSAGE_SUBMISSION_ID) :                    pszTag = "PR_MESSAGE_SUBMISSION_ID";                        break;   
        case PROP_ID(PR_PROVIDER_SUBMIT_TIME) :                     pszTag = "PR_PROVIDER_SUBMIT_TIME";                         break;   
        case PROP_ID(PR_ORIGINAL_SUBJECT) :                         pszTag = "PR_ORIGINAL_SUBJECT";                             break;   
        case PROP_ID(PR_DISC_VAL) :                                 pszTag = "PR_DISC_VAL";                                     break;   
        case PROP_ID(PR_ORIG_MESSAGE_CLASS) :                       pszTag = "PR_ORIG_MESSAGE_CLASS";                           break;   
        case PROP_ID(PR_ORIGINAL_AUTHOR_ENTRYID) :                  pszTag = "PR_ORIGINAL_AUTHOR_ENTRYID";                      break;   
        case PROP_ID(PR_ORIGINAL_AUTHOR_NAME) :                     pszTag = "PR_ORIGINAL_AUTHOR_NAME";                         break;   
        case PROP_ID(PR_ORIGINAL_SUBMIT_TIME) :                     pszTag = "PR_ORIGINAL_SUBMIT_TIME";                         break;   
        case PROP_ID(PR_REPLY_RECIPIENT_ENTRIES) :                  pszTag = "PR_REPLY_RECIPIENT_ENTRIES";                      break;   
        case PROP_ID(PR_REPLY_RECIPIENT_NAMES) :                    pszTag = "PR_REPLY_RECIPIENT_NAMES";                        break;   
        case PROP_ID(PR_RECEIVED_BY_SEARCH_KEY) :                   pszTag = "PR_RECEIVED_BY_SEARCH_KEY";                       break;   
        case PROP_ID(PR_RCVD_REPRESENTING_SEARCH_KEY) :             pszTag = "PR_RCVD_REPRESENTING_SEARCH_KEY";                 break;   
        case PROP_ID(PR_READ_RECEIPT_SEARCH_KEY) :                  pszTag = "PR_READ_RECEIPT_SEARCH_KEY";                      break;   
        case PROP_ID(PR_REPORT_SEARCH_KEY) :                        pszTag = "PR_REPORT_SEARCH_KEY";                            break;   
        case PROP_ID(PR_ORIGINAL_DELIVERY_TIME) :                   pszTag = "PR_ORIGINAL_DELIVERY_TIME";                       break;   
        case PROP_ID(PR_ORIGINAL_AUTHOR_SEARCH_KEY) :               pszTag = "PR_ORIGINAL_AUTHOR_SEARCH_KEY";                   break;   
        case PROP_ID(PR_MESSAGE_TO_ME) :                            pszTag = "PR_MESSAGE_TO_ME";                                break;   
        case PROP_ID(PR_MESSAGE_CC_ME) :                            pszTag = "PR_MESSAGE_CC_ME";                                break;   
        case PROP_ID(PR_MESSAGE_RECIP_ME) :                         pszTag = "PR_MESSAGE_RECIP_ME";                             break;   
        case PROP_ID(PR_ORIGINAL_SENDER_NAME) :                     pszTag = "PR_ORIGINAL_SENDER_NAME";                         break;   
        case PROP_ID(PR_ORIGINAL_SENDER_ENTRYID) :                  pszTag = "PR_ORIGINAL_SENDER_ENTRYID";                      break;   
        case PROP_ID(PR_ORIGINAL_SENDER_SEARCH_KEY) :               pszTag = "PR_ORIGINAL_SENDER_SEARCH_KEY";                   break;   
        case PROP_ID(PR_ORIGINAL_SENT_REPRESENTING_NAME) :          pszTag = "PR_ORIGINAL_SENT_REPRESENTING_NAME";              break;   
        case PROP_ID(PR_ORIGINAL_SENT_REPRESENTING_ENTRYID) :       pszTag = "PR_ORIGINAL_SENT_REPRESENTING_ENTRYID";           break;   
        case PROP_ID(PR_ORIGINAL_SENT_REPRESENTING_SEARCH_KEY) :    pszTag = "PR_ORIGINAL_SENT_REPRESENTING_SEARCH_KEY";        break;   
        case PROP_ID(PR_START_DATE) :                               pszTag = "PR_START_DATE";                                   break;   
        case PROP_ID(PR_END_DATE) :                                 pszTag = "PR_END_DATE";                                     break;   
        case PROP_ID(PR_OWNER_APPT_ID) :                            pszTag = "PR_OWNER_APPT_ID";                                break;   
        case PROP_ID(PR_RESPONSE_REQUESTED) :                       pszTag = "PR_RESPONSE_REQUESTED";                           break;   
        case PROP_ID(PR_SENT_REPRESENTING_ADDRTYPE) :               pszTag = "PR_SENT_REPRESENTING_ADDRTYPE";                   break;   
        case PROP_ID(PR_SENT_REPRESENTING_EMAIL_ADDRESS) :          pszTag = "PR_SENT_REPRESENTING_EMAIL_ADDRESS";              break;   
        case PROP_ID(PR_ORIGINAL_SENDER_ADDRTYPE) :                 pszTag = "PR_ORIGINAL_SENDER_ADDRTYPE";                     break;   
        case PROP_ID(PR_ORIGINAL_SENDER_EMAIL_ADDRESS) :            pszTag = "PR_ORIGINAL_SENDER_EMAIL_ADDRESS";                break;   
        case PROP_ID(PR_ORIGINAL_SENT_REPRESENTING_ADDRTYPE) :      pszTag = "PR_ORIGINAL_SENT_REPRESENTING_ADDRTYPE";          break;   
        case PROP_ID(PR_ORIGINAL_SENT_REPRESENTING_EMAIL_ADDRESS) : pszTag = "PR_ORIGINAL_SENT_REPRESENTING_EMAIL_ADDRESS";     break; 
        case PROP_ID(PR_CONVERSATION_TOPIC) :                       pszTag = "PR_CONVERSATION_TOPIC";                           break;   
        case PROP_ID(PR_CONVERSATION_INDEX) :                       pszTag = "PR_CONVERSATION_INDEX";                           break;   
        case PROP_ID(PR_ORIGINAL_DISPLAY_BCC) :                     pszTag = "PR_ORIGINAL_DISPLAY_BCC";                         break;   
        case PROP_ID(PR_ORIGINAL_DISPLAY_CC) :                      pszTag = "PR_ORIGINAL_DISPLAY_CC";                          break;   
        case PROP_ID(PR_ORIGINAL_DISPLAY_TO) :                      pszTag = "PR_ORIGINAL_DISPLAY_TO";                          break;   
        case PROP_ID(PR_RECEIVED_BY_ADDRTYPE) :                     pszTag = "PR_RECEIVED_BY_ADDRTYPE";                         break; 
        case PROP_ID(PR_RECEIVED_BY_EMAIL_ADDRESS) :                pszTag = "PR_RECEIVED_BY_EMAIL_ADDRESS";                    break; 
        case PROP_ID(PR_RCVD_REPRESENTING_ADDRTYPE) :               pszTag = "PR_RCVD_REPRESENTING_ADDRTYPE";                   break; 
        case PROP_ID(PR_RCVD_REPRESENTING_EMAIL_ADDRESS) :          pszTag = "PR_RCVD_REPRESENTING_EMAIL_ADDRESS";              break; 
        case PROP_ID(PR_ORIGINAL_AUTHOR_ADDRTYPE) :                 pszTag = "PR_ORIGINAL_AUTHOR_ADDRTYPE";                     break; 
        case PROP_ID(PR_ORIGINAL_AUTHOR_EMAIL_ADDRESS) :            pszTag = "PR_ORIGINAL_AUTHOR_EMAIL_ADDRESS";                break; 
        case PROP_ID(PR_ORIGINALLY_INTENDED_RECIP_ADDRTYPE) :       pszTag = "PR_ORIGINALLY_INTENDED_RECIP_ADDRTYPE";           break; 
        case PROP_ID(PR_ORIGINALLY_INTENDED_RECIP_EMAIL_ADDRESS) :  pszTag = "PR_ORIGINALLY_INTENDED_RECIP_EMAIL_ADDRESS";      break; 
        case PROP_ID(PR_TRANSPORT_MESSAGE_HEADERS) :                pszTag = "PR_TRANSPORT_MESSAGE_HEADERS";                    break; 

        #ifndef PR_DELEGATION
        #define PR_DELEGATION                                       PROP_TAG(PT_BINARY,     0x007E)
        #endif
        case PROP_ID(PR_DELEGATION) :                               pszTag = "PR_DELEGATION";                                   break;   

        // Message content properties
        case PROP_ID(PR_BODY) :                                     pszTag = "PR_BODY";                                         break;   
        case PROP_ID(PR_REPORT_TEXT) :                              pszTag = "PR_REPORT_TEXT";                                  break;   
        case PROP_ID(PR_ORIGINATOR_AND_DL_EXPANSION_HISTORY) :      pszTag = "PR_ORIGINATOR_AND_DL_EXPANSION_HISTORY";          break;   
        case PROP_ID(PR_REPORTING_DL_NAME) :                        pszTag = "PR_REPORTING_DL_NAME";                            break;   
        case PROP_ID(PR_REPORTING_MTA_CERTIFICATE) :                pszTag = "PR_REPORTING_MTA_CERTIFICATE";                    break;   
        case PROP_ID(PR_RTF_SYNC_BODY_CRC) :                        pszTag = "PR_RTF_SYNC_BODY_CRC";                            break;   
        case PROP_ID(PR_RTF_SYNC_BODY_COUNT) :                      pszTag = "PR_RTF_SYNC_BODY_COUNT";                          break;   
        case PROP_ID(PR_RTF_SYNC_BODY_TAG) :                        pszTag = "PR_RTF_SYNC_BODY_TAG";                            break;   
        case PROP_ID(PR_RTF_COMPRESSED) :                           pszTag = "PR_RTF_COMPRESSED";                               break;   
        case PROP_ID(PR_RTF_SYNC_PREFIX_COUNT) :                    pszTag = "PR_RTF_SYNC_PREFIX_COUNT";                        break;   
        case PROP_ID(PR_RTF_SYNC_TRAILING_COUNT) :                  pszTag = "PR_RTF_SYNC_TRAILING_COUNT";                      break;   
        case PROP_ID(PR_ORIGINALLY_INTENDED_RECIP_ENTRYID) :        pszTag = "PR_ORIGINALLY_INTENDED_RECIP_ENTRYID";            break;   

        // Message recipient properties
        case PROP_ID(PR_CONTENT_INTEGRITY_CHECK) :                  pszTag = "PR_CONTENT_INTEGRITY_CHECK";                      break;   
        case PROP_ID(PR_EXPLICIT_CONVERSION) :                      pszTag = "PR_EXPLICIT_CONVERSION";                          break;   
        case PROP_ID(PR_IPM_RETURN_REQUESTED) :                     pszTag = "PR_IPM_RETURN_REQUESTED";                         break;   
        case PROP_ID(PR_MESSAGE_TOKEN) :                            pszTag = "PR_MESSAGE_TOKEN";                                break;   
        case PROP_ID(PR_NDR_REASON_CODE) :                          pszTag = "PR_NDR_REASON_CODE";                              break;   
        case PROP_ID(PR_NDR_DIAG_CODE) :                            pszTag = "PR_NDR_DIAG_CODE";                                break;   
        case PROP_ID(PR_NON_RECEIPT_NOTIFICATION_REQUESTED) :       pszTag = "PR_NON_RECEIPT_NOTIFICATION_REQUESTED";           break;   

        #ifndef PR_DELIVERY_POINT
        #define PR_DELIVERY_POINT                                   PROP_TAG( PT_LONG,      0x0C07)
        #endif
        case PROP_ID(PR_DELIVERY_POINT) :                           pszTag = "PR_DELIVERY_POINT";                               break;   

        case PROP_ID(PR_ORIGINATOR_NON_DELIVERY_REPORT_REQUESTED) : pszTag = "PR_ORIGINATOR_NON_DELIVERY_REPORT_REQUESTED";     break;   
        case PROP_ID(PR_ORIGINATOR_REQUESTED_ALTERNATE_RECIPIENT) : pszTag = "PR_ORIGINATOR_REQUESTED_ALTERNATE_RECIPIENT";     break;   
        case PROP_ID(PR_PHYSICAL_DELIVERY_BUREAU_FAX_DELIVERY) :    pszTag = "PR_PHYSICAL_DELIVERY_BUREAU_FAX_DELIVERY";        break;   
        case PROP_ID(PR_PHYSICAL_DELIVERY_MODE) :                   pszTag = "PR_PHYSICAL_DELIVERY_MODE";                       break;   
        case PROP_ID(PR_PHYSICAL_DELIVERY_REPORT_REQUEST) :         pszTag = "PR_PHYSICAL_DELIVERY_REPORT_REQUEST";             break;   
        case PROP_ID(PR_PHYSICAL_FORWARDING_ADDRESS) :              pszTag = "PR_PHYSICAL_FORWARDING_ADDRESS";                  break;   
        case PROP_ID(PR_PHYSICAL_FORWARDING_ADDRESS_REQUESTED) :    pszTag = "PR_PHYSICAL_FORWARDING_ADDRESS_REQUESTED";        break;   
        case PROP_ID(PR_PHYSICAL_FORWARDING_PROHIBITED) :           pszTag = "PR_PHYSICAL_FORWARDING_PROHIBITED";               break;   
        case PROP_ID(PR_PHYSICAL_RENDITION_ATTRIBUTES) :            pszTag = "PR_PHYSICAL_RENDITION_ATTRIBUTES";                break;   
        case PROP_ID(PR_PROOF_OF_DELIVERY) :                        pszTag = "PR_PROOF_OF_DELIVERY";                            break;   
        case PROP_ID(PR_PROOF_OF_DELIVERY_REQUESTED) :              pszTag = "PR_PROOF_OF_DELIVERY_REQUESTED";                  break;   
        case PROP_ID(PR_RECIPIENT_CERTIFICATE) :                    pszTag = "PR_RECIPIENT_CERTIFICATE";                        break;   
        case PROP_ID(PR_RECIPIENT_NUMBER_FOR_ADVICE) :              pszTag = "PR_RECIPIENT_NUMBER_FOR_ADVICE";                  break;   
        case PROP_ID(PR_RECIPIENT_TYPE) :                           pszTag = "PR_RECIPIENT_TYPE";                               break;   
        case PROP_ID(PR_REGISTERED_MAIL_TYPE) :                     pszTag = "PR_REGISTERED_MAIL_TYPE";                         break;   
        case PROP_ID(PR_REPLY_REQUESTED) :                          pszTag = "PR_REPLY_REQUESTED";                              break;   
        case PROP_ID(PR_REQUESTED_DELIVERY_METHOD) :                pszTag = "PR_REQUESTED_DELIVERY_METHOD";                    break;   
        case PROP_ID(PR_SENDER_ENTRYID) :                           pszTag = "PR_SENDER_ENTRYID";                               break;   
        case PROP_ID(PR_SENDER_NAME) :                              pszTag = "PR_SENDER_NAME";                                  break;   
        case PROP_ID(PR_SUPPLEMENTARY_INFO) :                       pszTag = "PR_SUPPLEMENTARY_INFO";                           break;   
        case PROP_ID(PR_TYPE_OF_MTS_USER) :                         pszTag = "PR_TYPE_OF_MTS_USER";                             break;   
        case PROP_ID(PR_SENDER_SEARCH_KEY) :                        pszTag = "PR_SENDER_SEARCH_KEY";                            break;   
        case PROP_ID(PR_SENDER_ADDRTYPE) :                          pszTag = "PR_SENDER_ADDRTYPE";                              break;   
        case PROP_ID(PR_SENDER_EMAIL_ADDRESS) :                     pszTag = "PR_SENDER_EMAIL_ADDRESS";                         break;   
        
        // Message non-transmittable properties
        case PROP_ID(PR_CURRENT_VERSION) :                          pszTag = "PR_CURRENT_VERSION";                              break;   
        case PROP_ID(PR_DELETE_AFTER_SUBMIT) :                      pszTag = "PR_DELETE_AFTER_SUBMIT";                          break;   
        case PROP_ID(PR_DISPLAY_BCC) :                              pszTag = "PR_DISPLAY_BCC";                                  break;   
        case PROP_ID(PR_DISPLAY_CC) :                               pszTag = "PR_DISPLAY_CC";                                   break;   
        case PROP_ID(PR_DISPLAY_TO) :                               pszTag = "PR_DISPLAY_TO";                                   break;   
        case PROP_ID(PR_PARENT_DISPLAY) :                           pszTag = "PR_PARENT_DISPLAY";                               break;   
        case PROP_ID(PR_MESSAGE_DELIVERY_TIME) :                    pszTag = "PR_MESSAGE_DELIVERY_TIME";                        break;   
        case PROP_ID(PR_MESSAGE_FLAGS) :                            pszTag = "PR_MESSAGE_FLAGS";                                break;   
        case PROP_ID(PR_MESSAGE_SIZE) :                             pszTag = "PR_MESSAGE_SIZE";                                 break;   
        case PROP_ID(PR_PARENT_ENTRYID) :                           pszTag = "PR_PARENT_ENTRYID";                               break;   
        case PROP_ID(PR_SENTMAIL_ENTRYID) :                         pszTag = "PR_SENTMAIL_ENTRYID";                             break;   
        case PROP_ID(PR_CORRELATE) :                                pszTag = "PR_CORRELATE";                                    break;   
        case PROP_ID(PR_CORRELATE_MTSID) :                          pszTag = "PR_CORRELATE_MTSID";                              break;   
        case PROP_ID(PR_DISCRETE_VALUES) :                          pszTag = "PR_DISCRETE_VALUES";                              break;   
        case PROP_ID(PR_RESPONSIBILITY) :                           pszTag = "PR_RESPONSIBILITY";                               break;   
        case PROP_ID(PR_SPOOLER_STATUS) :                           pszTag = "PR_SPOOLER_STATUS";                               break;   
        case PROP_ID(PR_TRANSPORT_STATUS) :                         pszTag = "PR_TRANSPORT_STATUS";                             break;   
        case PROP_ID(PR_MESSAGE_RECIPIENTS) :                       pszTag = "PR_MESSAGE_RECIPIENTS";                           break;   
        case PROP_ID(PR_MESSAGE_ATTACHMENTS) :                      pszTag = "PR_MESSAGE_ATTACHMENTS";                          break;   
        case PROP_ID(PR_SUBMIT_FLAGS) :                             pszTag = "PR_SUBMIT_FLAGS";                                 break;   
        case PROP_ID(PR_RECIPIENT_STATUS) :                         pszTag = "PR_RECIPIENT_STATUS";                             break;   
        case PROP_ID(PR_TRANSPORT_KEY) :                            pszTag = "PR_TRANSPORT_KEY";                                break;   
        case PROP_ID(PR_MSG_STATUS) :                               pszTag = "PR_MSG_STATUS";                                   break;   
        case PROP_ID(PR_MESSAGE_DOWNLOAD_TIME) :                    pszTag = "PR_MESSAGE_DOWNLOAD_TIME";                        break;   
        case PROP_ID(PR_CREATION_VERSION) :                         pszTag = "PR_CREATION_VERSION";                             break;   
        case PROP_ID(PR_MODIFY_VERSION) :                           pszTag = "PR_MODIFY_VERSION";                               break;   
        case PROP_ID(PR_HASATTACH) :                                pszTag = "PR_HASATTACH";                                    break;   
        case PROP_ID(PR_BODY_CRC) :                                 pszTag = "PR_BODY_CRC";                                     break;   
        case PROP_ID(PR_NORMALIZED_SUBJECT) :                       pszTag = "PR_NORMALIZED_SUBJECT";                           break;   
        case PROP_ID(PR_RTF_IN_SYNC) :                              pszTag = "PR_RTF_IN_SYNC";                                  break;   
        case PROP_ID(PR_ATTACH_SIZE) :                              pszTag = "PR_ATTACH_SIZE";                                  break;   
        case PROP_ID(PR_ATTACH_NUM) :                               pszTag = "PR_ATTACH_NUM";                                   break;   
        case PROP_ID(PR_PREPROCESS) :                               pszTag = "PR_PREPROCESS";                                   break;   
        
        case PROP_ID(PR_ORIGINATING_MTA_CERTIFICATE) :              pszTag = "PR_ORIGINATING_MTA_CERTIFICATE";                  break;   
        case PROP_ID(PR_PROOF_OF_SUBMISSION) :                      pszTag = "PR_PROOF_OF_SUBMISSION";                          break;   
        
        // Properties common to multiple objects (including message objects)
        case PROP_ID(PR_ENTRYID) :                                  pszTag = "PR_ENTRYID";                                      break;   
        case PROP_ID(PR_OBJECT_TYPE) :                              pszTag = "PR_OBJECT_TYPE";                                  break;   
        case PROP_ID(PR_ICON) :                                     pszTag = "PR_ICON";                                         break;   
        case PROP_ID(PR_MINI_ICON) :                                pszTag = "PR_MINI_ICON";                                    break;   
        case PROP_ID(PR_STORE_ENTRYID) :                            pszTag = "PR_STORE_ENTRYID";                                break;   
        case PROP_ID(PR_STORE_RECORD_KEY) :                         pszTag = "PR_STORE_RECORD_KEY";                             break;   
        case PROP_ID(PR_RECORD_KEY) :                               pszTag = "PR_RECORD_KEY";                                   break;   
        case PROP_ID(PR_MAPPING_SIGNATURE) :                        pszTag = "PR_MAPPING_SIGNATURE";                            break;   
        case PROP_ID(PR_ACCESS_LEVEL) :                             pszTag = "PR_ACCESS_LEVEL";                                 break;   
        case PROP_ID(PR_INSTANCE_KEY) :                             pszTag = "PR_INSTANCE_KEY";                                 break;   
        case PROP_ID(PR_ROW_TYPE) :                                 pszTag = "PR_ROW_TYPE";                                     break;   
        case PROP_ID(PR_ACCESS) :                                   pszTag = "PR_ACCESS";                                       break;   
        
        // Properties common to multiple objects (NOT including message objects)
        case PROP_ID(PR_ROWID) :                                    pszTag = "PR_ROWID";                                        break;   
        case PROP_ID(PR_DISPLAY_NAME) :                             pszTag = "PR_DISPLAY_NAME";                                 break;   
        case PROP_ID(PR_ADDRTYPE) :                                 pszTag = "PR_ADDRTYPE";                                     break;   
        case PROP_ID(PR_EMAIL_ADDRESS) :                            pszTag = "PR_EMAIL_ADDRESS";                                break;   
        case PROP_ID(PR_COMMENT) :                                  pszTag = "PR_COMMENT";                                      break;   
        case PROP_ID(PR_DEPTH) :                                    pszTag = "PR_DEPTH";                                        break;   
        case PROP_ID(PR_PROVIDER_DISPLAY) :                         pszTag = "PR_PROVIDER_DISPLAY";                             break;   
        case PROP_ID(PR_CREATION_TIME) :                            pszTag = "PR_CREATION_TIME";                                break;   
        case PROP_ID(PR_LAST_MODIFICATION_TIME) :                   pszTag = "PR_LAST_MODIFICATION_TIME";                       break;   
        case PROP_ID(PR_RESOURCE_FLAGS) :                           pszTag = "PR_RESOURCE_FLAGS";                               break;   
        case PROP_ID(PR_PROVIDER_DLL_NAME) :                        pszTag = "PR_PROVIDER_DLL_NAME";                            break;   
        case PROP_ID(PR_SEARCH_KEY) :                               pszTag = "PR_SEARCH_KEY";                                   break;   
        case PROP_ID(PR_PROVIDER_UID) :                             pszTag = "PR_PROVIDER_UID";                                 break;   
        case PROP_ID(PR_PROVIDER_ORDINAL) :                         pszTag = "PR_PROVIDER_ORDINAL";                             break;   

        // MAPI Form properties
        case PROP_ID(PR_FORM_VERSION) :                             pszTag = "PR_FORM_VERSION";                                 break;   
        case PROP_ID(PR_FORM_CLSID) :                               pszTag = "PR_FORM_CLSID";                                   break;   
        case PROP_ID(PR_FORM_CONTACT_NAME) :                        pszTag = "PR_FORM_CONTACT_NAME";                            break;   
        case PROP_ID(PR_FORM_CATEGORY) :                            pszTag = "PR_FORM_CATEGORY";                                break;   
        case PROP_ID(PR_FORM_CATEGORY_SUB) :                        pszTag = "PR_FORM_CATEGORY_SUB";                            break;   
        case PROP_ID(PR_FORM_HOST_MAP) :                            pszTag = "PR_FORM_HOST_MAP";                                break;   
        case PROP_ID(PR_FORM_HIDDEN) :                              pszTag = "PR_FORM_HIDDEN";                                  break;   
        case PROP_ID(PR_FORM_DESIGNER_NAME) :                       pszTag = "PR_FORM_DESIGNER_NAME";                           break;   
        case PROP_ID(PR_FORM_DESIGNER_GUID) :                       pszTag = "PR_FORM_DESIGNER_GUID";                           break;   
        case PROP_ID(PR_FORM_MESSAGE_BEHAVIOR) :                    pszTag = "PR_FORM_MESSAGE_BEHAVIOR";                        break;   
        
        //Message store properties
        case PROP_ID(PR_DEFAULT_STORE) :                            pszTag = "PR_DEFAULT_STORE";                                break;   
        case PROP_ID(PR_STORE_SUPPORT_MASK) :                       pszTag = "PR_STORE_SUPPORT_MASK";                           break;
        case PROP_ID(PR_STORE_STATE) :                              pszTag = "PR_STORE_STATE";                                  break;
        case PROP_ID(PR_IPM_SUBTREE_SEARCH_KEY) :                   pszTag = "PR_IPM_SUBTREE_SEARCH_KEY";                       break;   
        case PROP_ID(PR_IPM_OUTBOX_SEARCH_KEY) :                    pszTag = "PR_IPM_OUTBOX_SEARCH_KEY";                        break;   
        case PROP_ID(PR_IPM_WASTEBASKET_SEARCH_KEY) :               pszTag = "PR_IPM_WASTEBASKET_SEARCH_KEY";                   break;   
        case PROP_ID(PR_IPM_SENTMAIL_SEARCH_KEY) :                  pszTag = "PR_IPM_SENTMAIL_SEARCH_KEY";                      break;   
        case PROP_ID(PR_MDB_PROVIDER) :                             pszTag = "PR_MDB_PROVIDER";                                 break;   
        case PROP_ID(PR_RECEIVE_FOLDER_SETTINGS) :                  pszTag = "PR_RECEIVE_FOLDER_SETTINGS";                      break;   
        case PROP_ID(PR_VALID_FOLDER_MASK) :                        pszTag = "PR_VALID_FOLDER_MASK";                            break;   
        case PROP_ID(PR_IPM_SUBTREE_ENTRYID) :                      pszTag = "PR_IPM_SUBTREE_ENTRYID";                          break;   
        case PROP_ID(PR_IPM_OUTBOX_ENTRYID) :                       pszTag = "PR_IPM_OUTBOX_ENTRYID";                           break;   
        case PROP_ID(PR_IPM_WASTEBASKET_ENTRYID) :                  pszTag = "PR_IPM_WASTEBASKET_ENTRYID";                      break;   
        case PROP_ID(PR_IPM_SENTMAIL_ENTRYID) :                     pszTag = "PR_IPM_SENTMAIL_ENTRYID";                         break;   
        case PROP_ID(PR_VIEWS_ENTRYID) :                            pszTag = "PR_VIEWS_ENTRYID";                                break;   
        case PROP_ID(PR_COMMON_VIEWS_ENTRYID) :                     pszTag = "PR_COMMON_VIEWS_ENTRYID";                         break;   
        case PROP_ID(PR_FINDER_ENTRYID) :                           pszTag = "PR_FINDER_ENTRYID";                               break;   
        
        // Folder and AB Container properties
        case PROP_ID(PR_CONTAINER_FLAGS) :                          pszTag = "PR_CONTAINER_FLAGS";                              break;   
        case PROP_ID(PR_FOLDER_TYPE) :                              pszTag = "PR_FOLDER_TYPE";                                  break;   
        case PROP_ID(PR_CONTENT_COUNT) :                            pszTag = "PR_CONTENT_COUNT";                                break;   
        case PROP_ID(PR_CONTENT_UNREAD) :                           pszTag = "PR_CONTENT_UNREAD";                               break;   
        case PROP_ID(PR_CREATE_TEMPLATES) :                         pszTag = "PR_CREATE_TEMPLATES";                             break;   
        case PROP_ID(PR_DETAILS_TABLE) :                            pszTag = "PR_DETAILS_TABLE";                                break;   
        case PROP_ID(PR_SEARCH) :                                   pszTag = "PR_SEARCH";                                       break;   
        case PROP_ID(PR_SELECTABLE) :                               pszTag = "PR_SELECTABLE";                                   break;   
        case PROP_ID(PR_SUBFOLDERS) :                               pszTag = "PR_SUBFOLDERS";                                   break;   
        case PROP_ID(PR_STATUS) :                                   pszTag = "PR_STATUS";                                       break;   
        case PROP_ID(PR_ANR) :                                      pszTag = "PR_ANR";                                          break;   
        case PROP_ID(PR_CONTENTS_SORT_ORDER) :                      pszTag = "PR_CONTENTS_SORT_ORDER";                          break;   
        case PROP_ID(PR_CONTAINER_HIERARCHY) :                      pszTag = "PR_CONTAINER_HIERARCHY";                          break;   
        case PROP_ID(PR_CONTAINER_CONTENTS) :                       pszTag = "PR_CONTAINER_CONTENTS";                           break;   
        case PROP_ID(PR_FOLDER_ASSOCIATED_CONTENTS) :               pszTag = "PR_FOLDER_ASSOCIATED_CONTENTS";                   break;   
        case PROP_ID(PR_DEF_CREATE_DL) :                            pszTag = "PR_DEF_CREATE_DL";                                break;   
        case PROP_ID(PR_DEF_CREATE_MAILUSER) :                      pszTag = "PR_DEF_CREATE_MAILUSER";                          break;   
        case PROP_ID(PR_CONTAINER_CLASS) :                          pszTag = "PR_CONTAINER_CLASS";                              break;   
        case PROP_ID(PR_CONTAINER_MODIFY_VERSION) :                 pszTag = "PR_CONTAINER_MODIFY_VERSION";                     break;   
        case PROP_ID(PR_AB_PROVIDER_ID) :                           pszTag = "PR_AB_PROVIDER_ID";                               break;
        case PROP_ID(PR_DEFAULT_VIEW_ENTRYID) :                     pszTag = "PR_DEFAULT_VIEW_ENTRYID";                         break;
        case PROP_ID(PR_ASSOC_CONTENT_COUNT) :                      pszTag = "PR_ASSOC_CONTENT_COUNT";                          break;
        
        // Defined in Build 556 and above
        #ifndef PR_VIEW_BINARY
        #define PR_VIEW_BINARY          PROP_TAG( PT_BINARY,    0x3618)
        #define PR_VIEW_STRINGS         PROP_TAG( PT_TSTRING,   0x3619)
        #define PR_VIEW_FLAGS           PROP_TAG( PT_LONG,      0x361A)
        #define PR_VIEW_LINK_TO         PROP_TAG( PT_BINARY,    0x361B)
        #define PR_VIEW_VIEW_FOLDER     PROP_TAG( PT_BINARY,    0x361C)
        #define PR_VIEW_NAME            PROP_TAG( PT_TSTRING,   0x361D)
        #define PR_VIEW_VERSION         PROP_TAG( PT_LONG,      0x361E)
        #define PR_VIEW_COLLAPSE_STATE  PROP_TAG( PT_BINARY,    0x361F)
        #endif // PR_VIEW_BINARY

        case PROP_ID(PR_VIEW_BINARY) :                              pszTag = "PR_VIEW_BINARY";                                  break;
        case PROP_ID(PR_VIEW_STRINGS) :                             pszTag = "PR_VIEW_STRINGS";                                 break;
        case PROP_ID(PR_VIEW_FLAGS) :                               pszTag = "PR_VIEW_FLAGS";                                   break;
        case PROP_ID(PR_VIEW_LINK_TO) :                             pszTag = "PR_VIEW_LINK_TO";                                 break;
        case PROP_ID(PR_VIEW_VIEW_FOLDER) :                         pszTag = "PR_VIEW_VIEW_FOLDER";                             break;
        case PROP_ID(PR_VIEW_NAME) :                                pszTag = "PR_VIEW_NAME";                                    break;
        case PROP_ID(PR_VIEW_VERSION) :                             pszTag = "PR_VIEW_VERSION";                                 break;
        case PROP_ID(PR_VIEW_COLLAPSE_STATE) :                      pszTag = "PR_VIEW_COLLAPSE_STATE";                          break;
        
        // Attachment properties
        case PROP_ID(PR_ATTACHMENT_X400_PARAMETERS) :               pszTag = "PR_ATTACHMENT_X400_PARAMETERS";                   break;   
        case PROP_ID(PR_ATTACH_DATA_OBJ) :                          pszTag = "PR_ATTACH_DATA_BIN or PR_ATTACH_DATA_OBJ";        break;   
        case PROP_ID(PR_ATTACH_ENCODING) :                          pszTag = "PR_ATTACH_ENCODING";                              break;   
        case PROP_ID(PR_ATTACH_EXTENSION) :                         pszTag = "PR_ATTACH_EXTENSION";                             break;   
        case PROP_ID(PR_ATTACH_FILENAME) :                          pszTag = "PR_ATTACH_FILENAME";                              break;   
        case PROP_ID(PR_ATTACH_METHOD) :                            pszTag = "PR_ATTACH_METHOD";                                break;   
        case PROP_ID(PR_ATTACH_LONG_FILENAME) :                     pszTag = "PR_ATTACH_LONG_FILENAME";                         break;   
        case PROP_ID(PR_ATTACH_PATHNAME) :                          pszTag = "PR_ATTACH_PATHNAME";                              break;   
        case PROP_ID(PR_ATTACH_RENDERING) :                         pszTag = "PR_ATTACH_RENDERING";                             break;   
        case PROP_ID(PR_ATTACH_TAG) :                               pszTag = "PR_ATTACH_TAG";                                   break;   
        case PROP_ID(PR_RENDERING_POSITION) :                       pszTag = "PR_RENDERING_POSITION";                           break;   
        case PROP_ID(PR_ATTACH_TRANSPORT_NAME) :                    pszTag = "PR_ATTACH_TRANSPORT_NAME";                        break;

        // Defined in Build 541 and above
        #ifndef PR_ATTACH_LONG_PATHNAME
        #define PR_ATTACH_LONG_PATHNAME                             PROP_TAG( PT_TSTRING,   0x370D)
        #define PR_ATTACH_MIME_TAG                                  PROP_TAG( PT_TSTRING,   0x370E)
        #endif
        case PROP_ID(PR_ATTACH_LONG_PATHNAME) :                     pszTag = "PR_ATTACH_LONG_PATHNAME";                         break;   
        case PROP_ID(PR_ATTACH_MIME_TAG) :                          pszTag = "PR_ATTACH_MIME_TAG";                              break;
        
        // AB Object properties
        case PROP_ID(PR_DISPLAY_TYPE) :                             pszTag = "PR_DISPLAY_TYPE";                                 break;   
        case PROP_ID(PR_TEMPLATEID) :                               pszTag = "PR_TEMPLATEID";                                   break;   
        case PROP_ID(PR_PRIMARY_CAPABILITY) :                       pszTag = "PR_PRIMARY_CAPABILITY";                           break;   

        // Mail user properties
        #ifndef PR_7BIT_DISPLAY_NAME
        #define PR_7BIT_DISPLAY_NAME                                PROP_TAG( PT_STRING8,   0x39FF)
        #endif
        case PROP_ID(PR_7BIT_DISPLAY_NAME) :                        pszTag = "PR_7BIT_DISPLAY_NAME";                                      break;
        case PROP_ID(PR_ACCOUNT) :                                  pszTag = "PR_ACCOUNT";                                      break;
        case PROP_ID(PR_ALTERNATE_RECIPIENT) :                      pszTag = "PR_ALTERNATE_RECIPIENT";                          break;   
        case PROP_ID(PR_CALLBACK_TELEPHONE_NUMBER) :                pszTag = "PR_CALLBACK_TELEPHONE_NUMBER";                    break;   
        case PROP_ID(PR_CONVERSION_PROHIBITED) :                    pszTag = "PR_CONVERSION_PROHIBITED";                        break;   
        case PROP_ID(PR_DISCLOSE_RECIPIENTS) :                      pszTag = "PR_DISCLOSE_RECIPIENTS";                          break;   
        case PROP_ID(PR_GENERATION) :                               pszTag = "PR_GENERATION";                                   break;   
        case PROP_ID(PR_GIVEN_NAME) :                               pszTag = "PR_GIVEN_NAME";                                   break;   
        case PROP_ID(PR_GOVERNMENT_ID_NUMBER) :                     pszTag = "PR_GOVERNMENT_ID_NUMBER";                         break;   
        case PROP_ID(PR_OFFICE_TELEPHONE_NUMBER) :                  pszTag = "PR_OFFICE_TELEPHONE_NUMBER";                      break;   
        case PROP_ID(PR_HOME_TELEPHONE_NUMBER) :                    pszTag = "PR_HOME_TELEPHONE_NUMBER";                        break;   
        case PROP_ID(PR_INITIALS) :                                 pszTag = "PR_INITIALS";                                     break;   
        case PROP_ID(PR_KEYWORD) :                                  pszTag = "PR_KEYWORD";                                      break;   
        case PROP_ID(PR_LANGUAGE) :                                 pszTag = "PR_LANGUAGE";                                     break;   
        case PROP_ID(PR_LOCATION) :                                 pszTag = "PR_LOCATION";                                     break;   
        case PROP_ID(PR_MAIL_PERMISSION) :                          pszTag = "PR_MAIL_PERMISSION";                              break;   
        case PROP_ID(PR_MHS_COMMON_NAME) :                          pszTag = "PR_MHS_COMMON_NAME";                              break;   
        case PROP_ID(PR_ORGANIZATIONAL_ID_NUMBER) :                 pszTag = "PR_ORGANIZATIONAL_ID_NUMBER";                     break;   
        case PROP_ID(PR_SURNAME) :                                  pszTag = "PR_SURNAME";                                      break;   
        case PROP_ID(PR_ORIGINAL_ENTRYID) :                         pszTag = "PR_ORIGINAL_ENTRYID";                             break;   
        case PROP_ID(PR_ORIGINAL_DISPLAY_NAME) :                    pszTag = "PR_ORIGINAL_DISPLAY_NAME";                        break;   
        case PROP_ID(PR_ORIGINAL_SEARCH_KEY) :                      pszTag = "PR_ORIGINAL_SEARCH_KEY";                          break;   
        case PROP_ID(PR_POSTAL_ADDRESS) :                           pszTag = "PR_POSTAL_ADDRESS";                               break;   
        case PROP_ID(PR_COMPANY_NAME) :                             pszTag = "PR_COMPANY_NAME";                                 break;   
        case PROP_ID(PR_TITLE) :                                    pszTag = "PR_TITLE";                                        break;   
        case PROP_ID(PR_DEPARTMENT_NAME) :                          pszTag = "PR_DEPARTMENT_NAME";                              break;   
        case PROP_ID(PR_OFFICE_LOCATION) :                          pszTag = "PR_OFFICE_LOCATION";                              break;   
        case PROP_ID(PR_PRIMARY_TELEPHONE_NUMBER) :                 pszTag = "PR_PRIMARY_TELEPHONE_NUMBER";                     break;   
        case PROP_ID(PR_OFFICE2_TELEPHONE_NUMBER) :                 pszTag = "PR_OFFICE2_TELEPHONE_NUMBER";                     break;   
        case PROP_ID(PR_CELLULAR_TELEPHONE_NUMBER) :                pszTag = "PR_CELLULAR_TELEPHONE_NUMBER";                    break;   
        case PROP_ID(PR_RADIO_TELEPHONE_NUMBER) :                   pszTag = "PR_RADIO_TELEPHONE_NUMBER";                       break;   
        case PROP_ID(PR_CAR_TELEPHONE_NUMBER) :                     pszTag = "PR_CAR_TELEPHONE_NUMBER";                         break;   
        case PROP_ID(PR_OTHER_TELEPHONE_NUMBER) :                   pszTag = "PR_OTHER_TELEPHONE_NUMBER";                       break;   
        case PROP_ID(PR_TRANSMITABLE_DISPLAY_NAME) :                pszTag = "PR_TRANSMITABLE_DISPLAY_NAME";                    break;   
        case PROP_ID(PR_BEEPER_TELEPHONE_NUMBER) :                  pszTag = "PR_BEEPER_TELEPHONE_NUMBER";                      break;   
        case PROP_ID(PR_USER_CERTIFICATE) :                         pszTag = "PR_USER_CERTIFICATE";                             break;
        case PROP_ID(PR_PRIMARY_FAX_NUMBER) :                       pszTag = "PR_PRIMARY_FAX_NUMBER";                           break;
        case PROP_ID(PR_BUSINESS_FAX_NUMBER) :                      pszTag = "PR_BUSINESS_FAX_NUMBER";                          break;
        case PROP_ID(PR_HOME_FAX_NUMBER) :                          pszTag = "PR_HOME_FAX_NUMBER";                              break;
        case PROP_ID(PR_COUNTRY) :                                  pszTag = "PR_COUNTRY";                                      break;
        case PROP_ID(PR_LOCALITY) :                                 pszTag = "PR_LOCALITY";                                     break;
        case PROP_ID(PR_STATE_OR_PROVINCE) :                        pszTag = "PR_STATE_OR_PROVINCE";                            break;
        case PROP_ID(PR_STREET_ADDRESS) :                           pszTag = "PR_STREET_ADDRESS";                               break;
        case PROP_ID(PR_POSTAL_CODE) :                              pszTag = "PR_POSTAL_CODE";                                  break;
        case PROP_ID(PR_POST_OFFICE_BOX) :                          pszTag = "PR_POST_OFFICE_BOX";                              break;
        case PROP_ID(PR_TELEX_NUMBER) :                             pszTag = "PR_TELEX_NUMBER";                                 break;
        case PROP_ID(PR_ISDN_NUMBER) :                              pszTag = "PR_ISDN_NUMBER";                                  break;
        case PROP_ID(PR_ASSISTANT_TELEPHONE_NUMBER) :               pszTag = "PR_ASSISTANT_TELEPHONE_NUMBER";                   break;
        case PROP_ID(PR_HOME2_TELEPHONE_NUMBER) :                   pszTag = "PR_HOME2_TELEPHONE_NUMBER";                       break;
        case PROP_ID(PR_ASSISTANT) :                                pszTag = "PR_ASSISTANT";                                    break;
        case PROP_ID(PR_SEND_RICH_INFO) :                           pszTag = "PR_SEND_RICH_INFO";                               break;

        // Profile section properties
        case PROP_ID(PR_STORE_PROVIDERS) :                          pszTag = "PR_STORE_PROVIDERS";                              break;   
        case PROP_ID(PR_AB_PROVIDERS) :                             pszTag = "PR_AB_PROVIDERS";                                 break;   
        case PROP_ID(PR_TRANSPORT_PROVIDERS) :                      pszTag = "PR_TRANSPORT_PROVIDERS";                          break;   
        case PROP_ID(PR_DEFAULT_PROFILE) :                          pszTag = "PR_DEFAULT_PROFILE";                              break;   
        case PROP_ID(PR_AB_SEARCH_PATH) :                           pszTag = "PR_AB_SEARCH_PATH";                               break;   
        case PROP_ID(PR_AB_DEFAULT_DIR) :                           pszTag = "PR_AB_DEFAULT_DIR";                               break;   
        case PROP_ID(PR_AB_DEFAULT_PAB) :                           pszTag = "PR_AB_DEFAULT_PAB";                               break;   
        case PROP_ID(PR_FILTERING_HOOKS) :                          pszTag = "PR_FILTERING_HOOKS";                              break;   
        case PROP_ID(PR_SERVICE_NAME) :                             pszTag = "PR_SERVICE_NAME";                                 break;   
        case PROP_ID(PR_SERVICE_DLL_NAME) :                         pszTag = "PR_SERVICE_DLL_NAME";                             break;   
        case PROP_ID(PR_SERVICE_ENTRY_NAME) :                       pszTag = "PR_SERVICE_ENTRY_NAME";                           break;   
        case PROP_ID(PR_SERVICE_UID) :                              pszTag = "PR_SERVICE_UID";                                  break;   
        case PROP_ID(PR_SERVICE_EXTRA_UIDS) :                       pszTag = "PR_SERVICE_EXTRA_UIDS";                           break;   
        case PROP_ID(PR_SERVICES) :                                 pszTag = "PR_SERVICES";                                     break;   
        case PROP_ID(PR_SERVICE_SUPPORT_FILES) :                    pszTag = "PR_SERVICE_SUPPORT_FILES";                        break;   
        case PROP_ID(PR_SERVICE_DELETE_FILES) :                     pszTag = "PR_SERVICE_DELETE_FILES";                         break;   
        case PROP_ID(PR_AB_SEARCH_PATH_UPDATE) :                    pszTag = "PR_AB_SEARCH_PATH_UPDATE";                        break;   

        // Status object properties
        case PROP_ID(PR_IDENTITY_DISPLAY) :                         pszTag = "PR_IDENTITY_DISPLAY";                             break;   
        case PROP_ID(PR_IDENTITY_ENTRYID) :                         pszTag = "PR_IDENTITY_ENTRYID";                             break;   
        case PROP_ID(PR_RESOURCE_METHODS) :                         pszTag = "PR_RESOURCE_METHODS";                             break;   
        case PROP_ID(PR_RESOURCE_TYPE) :                            pszTag = "PR_RESOURCE_TYPE";                                break;   
        case PROP_ID(PR_STATUS_CODE) :                              pszTag = "PR_STATUS_CODE";                                  break;   
        case PROP_ID(PR_IDENTITY_SEARCH_KEY) :                      pszTag = "PR_IDENTITY_SEARCH_KEY";                          break;   
        case PROP_ID(PR_OWN_STORE_ENTRYID) :                        pszTag = "PR_OWN_STORE_ENTRYID";                            break;   
        case PROP_ID(PR_RESOURCE_PATH) :                            pszTag = "PR_RESOURCE_PATH";                                break;   
        case PROP_ID(PR_STATUS_STRING) :                            pszTag = "PR_STATUS_STRING";                                break;   
        case PROP_ID(PR_X400_DEFERRED_DELIVERY_CANCEL) :            pszTag = "PR_X400_DEFERRED_DELIVERY_CANCEL";                break;   
        case PROP_ID(PR_HEADER_FOLDER_ENTRYID) :                    pszTag = "PR_HEADER_FOLDER_ENTRYID";                        break;   
        case PROP_ID(PR_REMOTE_PROGRESS) :                          pszTag = "PR_REMOTE_PROGRESS";                              break;   
        case PROP_ID(PR_REMOTE_PROGRESS_TEXT) :                     pszTag = "PR_REMOTE_PROGRESS_TEXT";                         break;   
        case PROP_ID(PR_REMOTE_VALIDATE_OK) :                       pszTag = "PR_REMOTE_VALIDATE_OK";                           break;   

        //Display table properties
        case PROP_ID(PR_CONTROL_FLAGS) :                            pszTag = "PR_CONTROL_FLAGS";                                break;   
        case PROP_ID(PR_CONTROL_STRUCTURE) :                        pszTag = "PR_CONTROL_STRUCTURE";                            break;
        case PROP_ID(PR_CONTROL_TYPE) :                             pszTag = "PR_CONTROL_TYPE";                                 break;
        case PROP_ID(PR_DELTAX) :                                   pszTag = "PR_DELTAX";                                       break;
        case PROP_ID(PR_DELTAY) :                                   pszTag = "PR_DELTAY";                                       break;
        case PROP_ID(PR_XPOS) :                                     pszTag = "PR_XPOS";                                         break;
        case PROP_ID(PR_YPOS) :                                     pszTag = "PR_YPOS";                                         break;
        case PROP_ID(PR_CONTROL_ID) :                               pszTag = "PR_CONTROL_ID";                                   break;
        case PROP_ID(PR_INITIAL_DETAILS_PANE) :                     pszTag = "PR_INITIAL_DETAILS_PANE";                         break;

        default :
            if (0x8000 >= PROP_ID(ulPropTag))
            {
                wsprintf (szUnkTag, "Named Property (%x)", PROP_ID(ulPropTag));
            }
            else
            {
                wsprintf (szUnkTag, "UNKNOWN (%x)", PROP_ID(ulPropTag));
            }
            pszTag = szUnkTag;
            break;
    }
    char * pszType;
    switch (PROP_TYPE(ulPropTag))
    {
        case PT_UNSPECIFIED :   pszType = "PT_UNSPECIFIED"; break;
        case PT_NULL :          pszType = "PT_NULL";        break;
        case PT_SHORT :         pszType = "PT_SHORT";       break;
        case PT_LONG :          pszType = "PT_LONG";        break;
        case PT_FLOAT :         pszType = "PT_FLOAT";       break;
        case PT_DOUBLE :        pszType = "PT_DOUBLE";      break;
        case PT_CURRENCY :      pszType = "PT_CURRENCY";    break;
        case PT_APPTIME :       pszType = "PT_APPTIME";     break;
        case PT_ERROR :         pszType = "PT_ERROR";       break;
        case PT_BOOLEAN :       pszType = "PT_BOOLEAN";     break;
        case PT_OBJECT :        pszType = "PT_OBJECT";      break;
        case PT_I8 :            pszType = "PT_I8";          break;
        case PT_STRING8 :       pszType = "PT_STRING8";     break;
        case PT_UNICODE :       pszType = "PT_UNICODE";     break;
        case PT_SYSTIME :       pszType = "PT_SYSTIME";     break;
        case PT_CLSID :         pszType = "PT_CLSID";       break;
        case PT_BINARY :        pszType = "PT_BINARY";      break;
        default :
            wsprintf (szUnkType, "UNKNOWN (%x)", PROP_TYPE(ulPropTag));
            pszType = szUnkType;
            break;
    }
    dwSize = wsprintf (message, "Tag: %s  Type: %s\r\n", pszTag, pszType);
    WriteOutputString (message, dwSize);
}
#endif // TRACES_NO_MAPI

// End of file for TRACES.CPP
