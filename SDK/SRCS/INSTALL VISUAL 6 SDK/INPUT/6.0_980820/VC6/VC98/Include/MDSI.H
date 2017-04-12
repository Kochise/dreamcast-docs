/*---------------------------------------------------------------------------

	Copyright (c) Microsoft Corporation. 1996. All Rights Reserved.


	mdsi.h

		Multiple Domain Synchronization Interface


	Authors:

		sandipn


	Version Ident:



	History:

		03/26/96	sandipn     Initial Creation
		08/08/96	sandipn     Updates for MDSI V1.1
		10/10/96	sandipn     Updates for MDSI V1.2

---------------------------------------------------------------------------*/


#ifndef __MDSI_H__
#define __MDSI_H__


#ifndef _WINDOWS_
#include <windows.h>
#endif // _WINDOWS_


#ifdef __cplusplus
extern "C" {
#endif

//
// In parameters
// 

#undef IN
#define IN

//
// Out parameters
// 

#undef OUT
#define OUT

//
// Following define is used to enable forwarding user's old password
// in a change password request
//

#undef 	ENABLE_OLD_PASSWORD_PROPAGATION
#define ENABLE_OLD_PASSWORD_PROPAGATION		1

//
// Version of the Host Process exported MDSI interface
// Version is in two parts: Major revision and minor revision.
// Major revision is the upper 16-bits, minor is the lower
// 16-bits.
//

#define HOSTSEC_MDSI_VERSION_1_1             (0X00010001)
#define HOSTSEC_MDSI_VERSION_1_2             (0X00010002)
#define HOSTSEC_MDSI_CURRENT_VERSION         (HOSTSEC_MDSI_VERSION_1_2)


//
//	Host Process implemented functions which ISV Security DLL invokes
//

//
//	NtSecValidateLogin
//

typedef
DWORD 
(WINAPI * PNTSEC_VALIDATE_LOGIN)(
		IN  HANDLE,										// hHostDomain
		IN  HANDLE,										// hTransaction
		IN  LPWSTR,										// pwszUserName
		IN  LPWSTR										// pwszPassword
		);

//
//	NtSecChangePassword
//

#ifdef ENABLE_OLD_PASSWORD_PROPAGATION

typedef
DWORD
(WINAPI * PNTSEC_CHANGE_PASSWORD)(
		IN  HANDLE,										// hHostDomain
		IN  HANDLE,										// hTransaction
		IN  LPWSTR,										// pwszUserName
		IN  LPWSTR,										// pwszNewPassword
		IN  LPWSTR										// pwszOldPassword
		);

#else

typedef
DWORD
(WINAPI * PNTSEC_CHANGE_PASSWORD)(
		IN  HANDLE,										// hHostDomain
		IN  HANDLE,										// hTransaction
		IN  LPWSTR,										// pwszUserName
		IN  LPWSTR										// pwszPassword
		);

#endif // ENABLE_OLD_PASSWORD_PROPAGATION

//
//	NtSecTransactionComplete
//

typedef
BOOL
(WINAPI * PNTSEC_TRANSACTION_COMPLETE)(
		IN  HANDLE,										// hHostDomain
		IN  HANDLE,										// hTransaction
		IN  DWORD										// dwStatus
		);

//
//	NtSecShutdownComplete
//

typedef
DWORD
(WINAPI * PNTSEC_SHUTDOWN_COMPLETE)(
		IN  HANDLE										// hHostDomain
		);

//
//	NtSecGetHostUser
//

typedef
DWORD 
(WINAPI * PNTSEC_GET_HOST_USER)(
		IN HANDLE,										// hHostDomain
		IN HANDLE,										// hTransaction
		IN LPWSTR,										// pwszNtUserDomain,
		IN LPWSTR										// pwszNtUser
		);

//
//	NtSecGetNtUser
//

typedef
DWORD 
(WINAPI * PNTSEC_GET_NT_USER)(
		IN HANDLE,										// hHostDomain
		IN HANDLE,										// hTransaction
		IN LPWSTR										// pwszHostUser
		);


//
// Function Dispatch Table: contains pointers to each of the entrypoints the Host Process 
// provides to the Security Integration DLL.  
//

typedef struct tagNTSEC_DISPATCH_VERSION_1_1
{

	PNTSEC_VALIDATE_LOGIN        NtSecValidateLogin;
	PNTSEC_CHANGE_PASSWORD       NtSecChangePassword;
	PNTSEC_TRANSACTION_COMPLETE  NtSecTransactionComplete;
	PNTSEC_SHUTDOWN_COMPLETE     NtSecShutdownComplete;

} NTSEC_DISPATCH_VERSION_1_1, *PNTSEC_DISPATCH_VERSION_1_1;

typedef struct tagNTSEC_DISPATCH_VERSION_1_2
{

	PNTSEC_VALIDATE_LOGIN        NtSecValidateLogin;
	PNTSEC_CHANGE_PASSWORD       NtSecChangePassword;
	PNTSEC_TRANSACTION_COMPLETE  NtSecTransactionComplete;
	PNTSEC_SHUTDOWN_COMPLETE     NtSecShutdownComplete;
	PNTSEC_GET_HOST_USER         NtSecGetHostUser;
	PNTSEC_GET_NT_USER           NtSecGetNtUser;

} NTSEC_DISPATCH_VERSION_1_2, *PNTSEC_DISPATCH_VERSION_1_2;

typedef NTSEC_DISPATCH_VERSION_1_2		NTSEC_DISPATCH_CURRENT_VERSION;
typedef NTSEC_DISPATCH_CURRENT_VERSION	*PNTSEC_DISPATCH_CURRENT_VERSION;


//
//	ISV Security DLL implemented functions which Host Process invokes
//

//
//	HostSecNegotiate
//

BOOL
WINAPI 
HostSecNegotiate(
		IN  DWORD,										// dwHostProcessVersion
		OUT PDWORD										// pdwDllVersion
		);

typedef
BOOL
(WINAPI * PHOSTSEC_NEGOTIATE)(
		IN  DWORD,										// dwHostProcessVersion
		OUT PDWORD										// pdwDllVersion
		);

//
//	HostSecInitialize
//

BOOL
WINAPI 
HostSecInitialize(
		IN  LPWSTR,										// pwszDomainName
		IN  HANDLE,										// hHostDomain
		IN  PVOID,										// pHostSecFunctions
		OUT PVOID *,									// ppDllSecFunctions
		OUT PVOID *										// phDllDomainContext
		);

typedef
BOOL
(WINAPI * PHOSTSEC_INITIALIZE)(
		IN  LPWSTR,										// pwszDomainName
		IN  HANDLE,										// hHostDomain
		IN  PVOID,										// pHostSecFunctions
		OUT PVOID *,									// ppDllSecFunctions
		OUT PVOID *										// phDllDomainContext
		);

//
//	HostSecValidateLogin
//

DWORD
WINAPI 
HostSecValidateLogin(
		IN  PVOID,										// hDllDomainContext
		IN  HANDLE,										// hTransaction
		IN  LPWSTR,										// pwszUserName
		IN  LPWSTR										// pwszPassword
		);

typedef
DWORD
(WINAPI * PHOSTSEC_VALIDATE_LOGIN)(
		IN  PVOID,										// hDllDomainContext
		IN  HANDLE,										// hTransaction
		IN  LPWSTR,										// pwszUserName
		IN  LPWSTR										// pwszPassword
		);

//
//	HostSecChangePassword
//

#ifdef ENABLE_OLD_PASSWORD_PROPAGATION

DWORD
WINAPI 
HostSecChangePassword(
		IN  PVOID,										// hDllDomainContext
		IN  HANDLE,										// hTransaction
		IN  LPWSTR,										// pwszUserName
		IN  LPWSTR,										// pwszNewPassword
		IN	LPWSTR										// pwszOldPassword	
		);

typedef
DWORD
(WINAPI * PHOSTSEC_CHANGE_PASSWORD)(
		IN  PVOID,										// hDllDomainContext
		IN  HANDLE,										// hTransaction
		IN  LPWSTR,										// pwszUserName
		IN  LPWSTR,										// pwszNewPassword
		IN	LPWSTR										// pwszOldPassword	
		);

#else

DWORD
WINAPI 
HostSecChangePassword(
		IN  PVOID,										// hDllDomainContext
		IN  HANDLE,										// hTransaction
		IN  LPWSTR,										// pwszUserName
		IN  LPWSTR										// pwszPassword
		);

typedef
DWORD
(WINAPI * PHOSTSEC_CHANGE_PASSWORD)(
		IN  PVOID,										// hDllDomainContext
		IN  HANDLE,										// hTransaction
		IN  LPWSTR,										// pwszUserName
		IN  LPWSTR										// pwszPassword
		);

#endif // ENABLE_OLD_PASSWORD_PROPAGATION

//
//	HostSecTransactionComplete
//

BOOL
WINAPI 
HostSecTransactionComplete(
 		IN  PVOID,										// hDllDomainContext
 		IN  HANDLE,										// hTransaction
		IN  DWORD										// dwStatus
		);

typedef
BOOL
(WINAPI * PHOSTSEC_TRANSACTION_COMPLETE)(
 		IN  PVOID,										// hDllDomainContext
 		IN  HANDLE,										// hTransaction
 		IN  DWORD										// dwStatus
 		);

//
//	HostSecShutdown
//

DWORD
WINAPI 
HostSecShutdown(
		IN  PVOID,										// hDllDomainContext
		IN  DWORD										// dwShutdownFlag
		);

typedef
DWORD
(WINAPI * PHOSTSEC_SHUTDOWN)(
		IN  PVOID,										// hDllDomainContext
		IN  DWORD										// dwShutdownFlag
		);

//
//	HostSecHostPing
//

DWORD
WINAPI 
HostSecHostPing(
		IN  PVOID,										// hDllDomainContext
		OUT PDWORD										// pdwStatus
		);

typedef
DWORD
(WINAPI * PHOSTSEC_HOST_PING)(
		IN  PVOID,										// hDllDomainContext
		OUT PDWORD										// pdwStatus
		);

//
//	HostSecTransactionCompleteEx
//

BOOL 
WINAPI
HostSecTransactionCompleteEx(
		IN PVOID,										// hDllDomainContext
		IN HANDLE,										// hTransaction
		IN DWORD,										// dwStatus
		IN LPWSTR,										// pwszUser
		IN LPWSTR										// pwszDomain
		);

typedef
BOOL 
(WINAPI * PHOSTSEC_TRANSACTION_COMPLETE_EX)(
		IN PVOID,										// hDllDomainContext
		IN HANDLE,										// hTransaction
		IN DWORD,										// dwStatus
		IN LPWSTR,										// pwszUser
		IN LPWSTR										// pwszDomain
		);



//
// Function Dispatch Table: contains pointers to each of the entrypoints the ISV Security 
// DLL provides to the Host Process.
//  

typedef struct tagHOSTSEC_DISPATCH_VERSION_1_1
{

	PHOSTSEC_VALIDATE_LOGIN        HostSecValidateLogin;
	PHOSTSEC_CHANGE_PASSWORD       HostSecChangePassword;
	PHOSTSEC_TRANSACTION_COMPLETE  HostSecTransactionComplete;
	PHOSTSEC_SHUTDOWN              HostSecShutdown;
	PHOSTSEC_HOST_PING             HostSecHostPing;

} HOSTSEC_DISPATCH_VERSION_1_1, *PHOSTSEC_DISPATCH_VERSION_1_1;

typedef struct tagHOSTSEC_DISPATCH_VERSION_1_2
{

	PHOSTSEC_VALIDATE_LOGIN           HostSecValidateLogin;
	PHOSTSEC_CHANGE_PASSWORD          HostSecChangePassword;
	PHOSTSEC_TRANSACTION_COMPLETE     HostSecTransactionComplete;
	PHOSTSEC_SHUTDOWN                 HostSecShutdown;
	PHOSTSEC_HOST_PING                HostSecHostPing;
	PHOSTSEC_TRANSACTION_COMPLETE_EX  HostSecTransactionCompleteEx;

} HOSTSEC_DISPATCH_VERSION_1_2, *PHOSTSEC_DISPATCH_VERSION_1_2;

typedef HOSTSEC_DISPATCH_VERSION_1_2		HOSTSEC_DISPATCH_CURRENT_VERSION;
typedef HOSTSEC_DISPATCH_CURRENT_VERSION	*PHOSTSEC_DISPATCH_CURRENT_VERSION; 


//
// HostSecShutdown uses following values (dwShutdownFlag) to indicate Security DLL which 
// way cleanup should be done.
//
//	NORMAL		-	Host Process will not initiate any more transactions. DLL should reject
//					any new transactions from the host. Host Process will continue to call
//					HostSecTransactionComplete() with any outstanding host initiated completions.
//
//	DONE		-	Host Process has completed all host initiated transactions. DLL can terminate
//					host communications and free up any system resources it has acquired.
//
//	ABORT		-	Security DLL should abort all host communications and attempt to release
//					all system resources it has acquired.
//

#define HOSTSEC_SHUTDOWN_NORMAL                            (1)
#define HOSTSEC_SHUTDOWN_DONE                              (2)
#define HOSTSEC_SHUTDOWN_ABORT                             (3)


//
// HostSecHostPing returns following values as status (pdwStatus) of host connection.
//
//	LOCAL_CONFIG_ERROR				-	Local configuration error occurred.
//
//	REMOTE_TP_UNAVAILABLE_RETRY		-	Remote TP is not available, retry could be done.
//
//	REMOTE_TP_UNAVAILABLE_NORETRY	-	Remote TP is not available, retry should not be done.
//
//	REMOTE_UNREACHABLE				-	Host is un-reachable.
//

#define HOSTSEC_PING_LOCAL_CONFIG_ERROR                    (1)
#define HOSTSEC_PING_REMOTE_TP_UNAVAILABLE_RETRY           (2)
#define HOSTSEC_PING_REMOTE_TP_UNAVAILABLE_NORETRY         (3)
#define HOSTSEC_PING_REMOTE_UNREACHABLE                    (4)


#ifdef __cplusplus
}
#endif

#endif // __MDSI_H__
