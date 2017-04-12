/*++

Copyright (c) 1995 - 1997  Microsoft Corporation

Module Name:

    rtutils.h

Abstract:
     Public declarations for the Router process  utility functions.

--*/

#ifndef __ROUTING_RTUTILS_H__
#define __ROUTING_RTUTILS_H__

#ifdef __cplusplus
extern "C" {
#endif

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// TRACING FUNCTION PROTOTYPES                                              //
//                                                                          //
// See DOCUMENT for more information                                        //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////    
//                                                                          //
// Definitions for flags and constants                                      //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
    
#define TRACE_USE_FILE      0x00000001
#define TRACE_USE_CONSOLE   0x00000002
#define TRACE_NO_SYNCH      0x00000004

#define TRACE_NO_STDINFO    0x00000001
#define TRACE_USE_MASK      0x00000002
#define TRACE_USE_MSEC      0x00000004

#define INVALID_TRACEID     0xFFFFFFFF


//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// ANSI entry-points                                                        //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
    
DWORD
APIENTRY
TraceRegisterExA(
    IN  LPCSTR      lpszCallerName,
    IN  DWORD       dwFlags
    );

DWORD
APIENTRY
TraceDeregisterA(
    IN  DWORD       dwTraceID
    );

DWORD
APIENTRY
TraceDeregisterExA(
    IN  DWORD       dwTraceID,
    IN  DWORD       dwFlags
    );

DWORD
APIENTRY
TraceGetConsoleA(
    IN  DWORD       dwTraceID,
    OUT LPHANDLE    lphConsole
    );

DWORD
APIENTRY
TracePrintfA(
    IN  DWORD       dwTraceID,
    IN  LPCSTR      lpszFormat,
    IN  ...         OPTIONAL
    );

DWORD
APIENTRY
TracePrintfExA(
    IN  DWORD       dwTraceID,
    IN  DWORD       dwFlags,
    IN  LPCSTR      lpszFormat,
    IN  ...         OPTIONAL
    );

DWORD
APIENTRY
TraceVprintfExA(
    IN  DWORD       dwTraceID,
    IN  DWORD       dwFlags,
    IN  LPCSTR      lpszFormat,
    IN  va_list     arglist
    );

DWORD
APIENTRY
TracePutsExA(
    IN  DWORD       dwTraceID,
    IN  DWORD       dwFlags,
    IN  LPCSTR      lpszString
    );

DWORD
APIENTRY
TraceDumpExA(
    IN  DWORD       dwTraceID,
    IN  DWORD       dwFlags,
    IN  LPBYTE      lpbBytes,
    IN  DWORD       dwByteCount,
    IN  DWORD       dwGroupSize,
    IN  BOOL        bAddressPrefix,
    IN  LPCSTR      lpszPrefix
    );


//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// ANSI entry-points macros                                                 //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

#define TraceRegisterA(a)               TraceRegisterExA(a,0)
#define TraceVprintfA(a,b,c)            TraceVprintfExA(a,0,b,c)
#define TracePutsA(a,b)                 TracePutsExA(a,0,b)
#define TraceDumpA(a,b,c,d,e,f)         TraceDumpExA(a,0,b,c,d,e,f)



//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Unicode entry-points                                                     //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

DWORD
APIENTRY
TraceRegisterExW(
    IN  LPCWSTR     lpszCallerName,
    IN  DWORD       dwFlags
    );

DWORD
APIENTRY
TraceDeregisterW(
    IN  DWORD       dwTraceID
    );

DWORD
APIENTRY
TraceDeregisterExW(
    IN  DWORD       dwTraceID,
    IN  DWORD       dwFlags
    );

DWORD
APIENTRY
TraceGetConsoleW(
    IN  DWORD       dwTraceID,
    OUT LPHANDLE    lphConsole
    );

DWORD
APIENTRY
TracePrintfW(
    IN  DWORD       dwTraceID,
    IN  LPCWSTR     lpszFormat,
    IN  ...         OPTIONAL
    );

DWORD
APIENTRY
TracePrintfExW(
    IN  DWORD       dwTraceID,
    IN  DWORD       dwFlags,
    IN  LPCWSTR     lpszFormat,
    IN  ...         OPTIONAL
    );

DWORD
APIENTRY
TraceVprintfExW(
    IN  DWORD       dwTraceID,
    IN  DWORD       dwFlags,
    IN  LPCWSTR     lpszFormat,
    IN  va_list     arglist
    );

DWORD
APIENTRY
TracePutsExW(
    IN  DWORD       dwTraceID,
    IN  DWORD       dwFlags,
    IN  LPCWSTR     lpszString
    );

DWORD
APIENTRY
TraceDumpExW(
    IN  DWORD       dwTraceID,
    IN  DWORD       dwFlags,
    IN  LPBYTE      lpbBytes,
    IN  DWORD       dwByteCount,
    IN  DWORD       dwGroupSize,
    IN  BOOL        bAddressPrefix,
    IN  LPCWSTR     lpszPrefix
    );


//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Unicode entry-points macros                                              //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

#define TraceRegisterW(a)               TraceRegisterExW(a,0)
#define TraceVprintfW(a,b,c)            TraceVprintfExW(a,0,b,c)
#define TracePutsW(a,b)                 TracePutsExW(a,0,b)
#define TraceDumpW(a,b,c,d,e,f)         TraceDumpExW(a,0,b,c,d,e,f)



//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Code-page dependent entry-point macros                                   //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

#ifdef UNICODE
#define TraceRegister           TraceRegisterW
#define TraceDeregister         TraceDeregisterW
#define TraceDeregisterEx       TraceDeregisterExW
#define TraceGetConsole         TraceGetConsoleW
#define TracePrintf             TracePrintfW
#define TraceVprintf            TraceVprintfW
#define TracePuts               TracePutsW
#define TraceDump               TraceDumpW
#define TraceRegisterEx         TraceRegisterExW
#define TracePrintfEx           TracePrintfExW
#define TraceVprintfEx          TraceVprintfExW
#define TracePutsEx             TracePutsExW
#define TraceDumpEx             TraceDumpExW
#else
#define TraceRegister           TraceRegisterA
#define TraceDeregister         TraceDeregisterA
#define TraceDeregisterEx       TraceDeregisterExA
#define TraceGetConsole         TraceGetConsoleA
#define TracePrintf             TracePrintfA
#define TraceVprintf            TraceVprintfA
#define TracePuts               TracePutsA
#define TraceDump               TraceDumpA
#define TraceRegisterEx         TraceRegisterExA
#define TracePrintfEx           TracePrintfExA
#define TraceVprintfEx          TraceVprintfExA
#define TracePutsEx             TracePutsExA
#define TraceDumpEx             TraceDumpExA
#endif



//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// EVENT LOGGING FUNCTION PROTOTYPES                                        //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// ANSI prototypes                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


VOID
APIENTRY
LogErrorA(
    IN DWORD    dwMessageId,
    IN DWORD    cNumberOfSubStrings,
    IN LPSTR   *plpwsSubStrings,
    IN DWORD    dwErrorCode
);

VOID
APIENTRY
LogEventA(
    IN DWORD   wEventType,
    IN DWORD   dwMessageId,
    IN DWORD   cNumberOfSubStrings,
    IN LPSTR  *plpwsSubStrings
);


//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Unicode prototypes                                                       //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

VOID
LogErrorW(
    IN DWORD    dwMessageId,
    IN DWORD    cNumberOfSubStrings,
    IN LPWSTR  *plpwsSubStrings,
    IN DWORD    dwErrorCode
);

VOID
LogEventW(
    IN DWORD   wEventType,
    IN DWORD   dwMessageId,
    IN DWORD   cNumberOfSubStrings,
    IN LPWSTR *plpwsSubStrings
);


#ifdef UNICODE
#define LogError                LogErrorW
#define LogEvent                LogEventW
#else
#define LogError                LogErrorA
#define LogEvent                LogEventA
#endif


//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// The following functions allow the caller to specify the event source.    //
//                                                                          //
// Call RouterLogRegister with the strings which would be passed to         //
// RegisterEventSource; this returns a handle which can be passed           //
// to the functions RouterLogEvent and RouterLogEventData.                  //
//                                                                          //
// Call RouterLogDeregister to close the handle.                            //
//                                                                          //
// Macros are provided for the different kinds of event log entrys:         //
//  RouterLogError          logs an error (EVENTLOG_ERROR_TYPE)             //
//  RouterLogWarning        logs a warning (EVENTLOG_WARNING_TYPE)          //
//  RouterLogInformation    logs information (EVENTLOG_INFORMATION_TYPE)    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// ANSI prototypes                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

HANDLE
RouterLogRegisterA(
    LPCSTR lpszSource
    );

VOID
RouterLogDeregisterA(
    HANDLE hLogHandle
    );

VOID
RouterLogEventA(
    IN HANDLE hLogHandle,
    IN DWORD dwEventType,
    IN DWORD dwMessageId,
    IN DWORD dwSubStringCount,
    IN LPSTR *plpszSubStringArray,
    IN DWORD dwErrorCode
    );

VOID
RouterLogEventDataA(
    IN HANDLE hLogHandle,
    IN DWORD dwEventType,
    IN DWORD dwMessageId,
    IN DWORD dwSubStringCount,
    IN LPSTR *plpszSubStringArray,
    IN DWORD dwDataBytes,
    IN LPBYTE lpDataBytes
    );

VOID
RouterLogEventStringA(
    IN HANDLE hLogHandle,
    IN DWORD dwEventType,
    IN DWORD dwMessageId,
    IN DWORD dwSubStringCount,
    IN LPSTR *plpszSubStringArray,
    IN DWORD dwErrorCode,
    IN DWORD dwErrorIndex
    );

DWORD
RouterGetErrorStringA(
    IN  DWORD   dwErrorCode,
    OUT LPSTR * lplpszErrorString
    );

#define RouterLogErrorA(h,msg,count,array,err) \
        RouterLogEventA(h,EVENTLOG_ERROR_TYPE,msg,count,array,err)
#define RouterLogWarningA(h,msg,count,array,err) \
        RouterLogEventA(h,EVENTLOG_WARNING_TYPE,msg,count,array,err)
#define RouterLogInformationA(h,msg,count,array,err) \
        RouterLogEventA(h,EVENTLOG_INFORMATION_TYPE,msg,count,array,err)

#define RouterLogErrorDataA(h,msg,count,array,c,buf) \
        RouterLogEventDataA(h,EVENTLOG_ERROR_TYPE,msg,count,array,c,buf)
#define RouterLogWarningDataA(h,msg,count,array,c,buf) \
        RouterLogEventDataA(h,EVENTLOG_WARNING_TYPE,msg,count,array,c,buf)
#define RouterLogInformationDataA(h,msg,count,array,c,buf) \
        RouterLogEventDataA(h,EVENTLOG_INFORMATION_TYPE,msg,count,array,c,buf)

#define RouterLogErrorStringA(h,msg,count,array,err,index) \
        RouterLogEventStringA(h,EVENTLOG_ERROR_TYPE,msg,count,array, err,index)
#define RouterLogWarningStringA(h,msg,count,array,err,index) \
        RouterLogEventStringA(h,EVENTLOG_WARNING_TYPE,msg,count,array,err,index)
#define RouterLogInformationStringA(h,msg,count,array, err,index) \
        RouterLogEventStringA(h,EVENTLOG_INFORMATION_TYPE,msg,count,array,err,\
                              index)


//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Unicode prototypes                                                       //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

HANDLE
RouterLogRegisterW(
    LPCWSTR lpszSource
    );

VOID
RouterLogDeregisterW(
    HANDLE hLogHandle
    );

VOID
RouterLogEventW(
    IN HANDLE hLogHandle,
    IN DWORD dwEventType,
    IN DWORD dwMessageId,
    IN DWORD dwSubStringCount,
    IN LPWSTR *plpszSubStringArray,
    IN DWORD dwErrorCode
    );

VOID
RouterLogEventDataW(
    IN HANDLE hLogHandle,
    IN DWORD dwEventType,
    IN DWORD dwMessageId,
    IN DWORD dwSubStringCount,
    IN LPWSTR *plpszSubStringArray,
    IN DWORD dwDataBytes,
    IN LPBYTE lpDataBytes
    );

VOID
RouterLogEventStringW(
    IN HANDLE hLogHandle,
    IN DWORD dwEventType,
    IN DWORD dwMessageId,
    IN DWORD dwSubStringCount,
    IN LPWSTR *plpszSubStringArray,
    IN DWORD dwErrorCode,
    IN DWORD dwErrorIndex
    );

DWORD
RouterGetErrorStringW(
    IN  DWORD    dwErrorCode,
    OUT LPWSTR * lplpwszErrorString
    );


#define RouterLogErrorW(h,msg,count,array,err) \
        RouterLogEventW(h,EVENTLOG_ERROR_TYPE,msg,count,array,err)
#define RouterLogWarningW(h,msg,count,array,err) \
        RouterLogEventW(h,EVENTLOG_WARNING_TYPE,msg,count,array,err)
#define RouterLogInformationW(h,msg,count,array,err) \
        RouterLogEventW(h,EVENTLOG_INFORMATION_TYPE,msg,count,array,err)

#define RouterLogErrorDataW(h,msg,count,array,c,buf) \
        RouterLogEventDataW(h,EVENTLOG_ERROR_TYPE,msg,count,array,c,buf)
#define RouterLogWarningDataW(h,msg,count,array,c,buf) \
        RouterLogEventDataW(h,EVENTLOG_WARNING_TYPE,msg,count,array,c,buf)
#define RouterLogInformationDataW(h,msg,count,array,c,buf) \
        RouterLogEventDataW(h,EVENTLOG_INFORMATION_TYPE,msg,count,array,c,buf)

#define RouterLogErrorStringW(h,msg,count,array,err,index) \
        RouterLogEventStringW(h,EVENTLOG_ERROR_TYPE,msg,count,array,err,index)
#define RouterLogWarningStringW(h,msg,count,array,err,index) \
        RouterLogEventStringW(h,EVENTLOG_WARNING_TYPE,msg,count,array,err,index)
#define RouterLogInformationStringW(h,msg,count,array,err,index) \
        RouterLogEventStringW(h,EVENTLOG_INFORMATION_TYPE,msg,count,array,err,\
                              index)


#ifdef UNICODE
#define RouterLogRegister           RouterLogRegisterW
#define RouterLogDeregister         RouterLogDeregisterW
#define RouterLogEvent              RouterLogEventW
#define RouterLogError              RouterLogErrorW
#define RouterLogWarning            RouterLogWarningW
#define RouterLogInformation        RouterLogInformationW
#define RouterLogEventData          RouterLogEventDataW
#define RouterLogErrorData          RouterLogErrorDataW
#define RouterLogWarningData        RouterLogWarningDataW
#define RouterLogInformationData    RouterLogInformationDataW
#define RouterLogEventString        RouterLogEventStringW
#define RouterLogErrorString        RouterLogErrorStringW
#define RouterLogWarningString      RouterLogWarningStringW
#define RouterLogInformationString  RouterLogInformationStringW
#define RouterGetErrorString        RouterGetErrorStringW        
#
#else
#define RouterLogRegister           RouterLogRegisterA
#define RouterLogDeregister         RouterLogDeregisterA
#define RouterLogEvent              RouterLogEventA
#define RouterLogError              RouterLogErrorA
#define RouterLogWarning            RouterLogWarningA
#define RouterLogInformation        RouterLogInformationA
#define RouterLogEventData          RouterLogEventDataA
#define RouterLogErrorData          RouterLogErrorDataA
#define RouterLogWarningData        RouterLogWarningDataA
#define RouterLogInformationData    RouterLogInformationDataA
#define RouterLogEventString        RouterLogEventStringA
#define RouterLogErrorString        RouterLogErrorStringA
#define RouterLogWarningString      RouterLogWarningStringA
#define RouterLogInformationString  RouterLogInformationStringA
#define RouterGetErrorString        RouterGetErrorStringA        
#endif




//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// WORKER THREAD POOL FUNCTIONS                                             //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//                                                                          //            
// definition of worker function passed in QueueWorkItem API                //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
            
typedef VOID (APIENTRY * WORKERFUNCTION)(PVOID);


//////////////////////////////////////////////////////////////////////////////
//                                                                          //            
//  Function: Queues the supplied work item in the work queue.              //
//                                                                          //
//  functionptr: function to be called must be of WORKERFUNCTION type       //
//  context:     opaque ptr                                                 //
//  serviceinalertablethread: if TRUE gets scheduled in                     //
//               a alertably waiting thread that never dies                 //
//  Returns:  0 (success)                                                   //
//            Win32 error codes for cases like out of memory                //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////        

DWORD
APIENTRY
QueueWorkItem(
    IN WORKERFUNCTION functionptr,
    IN PVOID context,
    IN BOOL serviceinalertablethread
    );


//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Function:        Associates file handle with the completion port (all    //
//                  asynchronous i/o on this handle will be queued to       //
//			        the completion port)                                    //
//                                                                          //
// FileHandle:	    File handle to be associated with completion port       //
//                                                                          //
// CompletionProc:  Procedure to be called when io associated with the file //
//				    handle completes. This function will be executed in     //
//				    the context of non-alertable worker thread              //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

DWORD
APIENTRY
SetIoCompletionProc (
	IN HANDLE							FileHandle,
	IN LPOVERLAPPED_COMPLETION_ROUTINE	CompletionProc
	);



//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// The following defines are included here as a hint on how the worker      //
// thread pool is managed:                                                  //
//                                                                          // 
// There are NUM_ALERTABLE_THREADS permanent threads that never quit and    //
// wait alertably on a alertable worker queue.  These threads should solely //
// be used for work items that intiate asyncronous operation (file io,      //
// waitable timer) that ABSOLUTELY require APCs to complete (preferable     //
// method for IO is the usage of completio port API)                        //
//                                                                          //
// There is a pool of the threads that wait on completion port              //
// that used both for processing of IO and non-IO related work items        //
//                                                                          // 
// The minimum number of threads is Number of processors                    //
// The maximum number of threads is MAX_WORKER_THREADS                      //
//                                                                          //
// A new thread is created if worker queue has not been served for more     //
// that WORK_QUEUE_TIMEOUT                                                  //
// The existing thread will be shut down if it is not used for more than    //
// THREAD_IDLE_TIMEOUT                                                      //
//                                                                          //
// Note that worker threads age guaranteed to be alive for at least         //
// THREAD_IDLE_TIMEOUT after the last work item is executed.  This timeout  //
// is chosen such that bulk of IO request could be completed before it      //
// expires.  If it is not enough for your case, use alertable thread with   //
// APC, or create your own thread.                                          //
//                                                                          //
// Note: changing these flags will not change anything.                     //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Number of alertable threads                                              //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

#define NUM_ALERTABLE_THREADS		2

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Max number of threads at any time                                        //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

#define MAX_WORKER_THREADS          10

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Time that the worker queue is not served before starting new thread      //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

#define WORK_QUEUE_TIMEOUT			1 //sec

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Time that thread has to be idle before exiting                           //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

#define THREAD_IDLE_TIMEOUT			10 //sec


//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// ROUTER ASSERT DECLARATION                                                //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

VOID
RouterAssert(
    IN PSTR pszFailedAssertion,
    IN PSTR pszFileName,
    IN DWORD dwLineNumber,
    IN PSTR pszMessage OPTIONAL
    );


#if DBG
#define RTASSERT(exp) \
        if (!(exp)) \
            RouterAssert(#exp, __FILE__, __LINE__, NULL)
#define RTASSERTMSG(msg, exp) \
        if (!(exp)) \
            RouterAssert(#exp, __FILE__, __LINE__, msg)
#else
#define RTASSERT(exp)
#define RTASSERTMSG(msg, exp)
#endif

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// REGISTRY CONFIGURATION FUNCTIONS                                         //
//                                                                          //
// The following definitions are used to read configuration information     //
// about installed protocols.                                               //
//                                                                          //
// Call 'MprSetupProtocolEnum' to enumerate the routing-protocols           //
// for transport 'dwTransportId'. This fills an array with entries          //
// of type 'MPR_PROTOCOL_0'.                                                //
//                                                                          //
// The array loaded can be destroyed by calling 'MprSetupProtocolFree'.     //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

#define MAX_PROTOCOL_NAME_LEN                           40
#define MAX_PROTOCOL_DLL_LEN                            48

typedef struct _MPR_PROTOCOL_0 {

    DWORD       dwProtocolId;                           // e.g. IP_RIP
    WCHAR       wszProtocol[MAX_PROTOCOL_NAME_LEN+1];   // e.g. "IPRIP"
    WCHAR       wszDLLName[MAX_PROTOCOL_DLL_LEN+1];     // e.g. "iprip2.dll"

} MPR_PROTOCOL_0;


DWORD APIENTRY
MprSetupProtocolEnum(
    IN      DWORD                   dwTransportId,
    OUT     LPBYTE*                 lplpBuffer,         // MPR_PROTOCOL_0
    OUT     LPDWORD                 lpdwEntriesRead
    );


DWORD APIENTRY
MprSetupProtocolFree(
    IN      LPVOID                  lpBuffer
    );


#ifdef __cplusplus
}
#endif

#endif // ___ROUTING_RTUTILS_H__


