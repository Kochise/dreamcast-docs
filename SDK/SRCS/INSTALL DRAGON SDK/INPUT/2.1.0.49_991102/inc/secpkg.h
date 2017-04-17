/*++

Copyright (c) 1992-1998 Microsoft Corporation

Module Name: secpkg.h

Purpose: Global definitions for security packages. Everything specific to 
         writing a security package.

--*/

#ifndef __SECPKG_H__
#define __SECPKG_H__

// #include <ntlsa.h> // SECURITY_LOGON_TYPE

#ifdef SECURITY_KERNEL
//
// Can't use the windows.h def'ns in kernel mode.
//
typedef PVOID                   SEC_THREAD_START;
typedef PVOID                   SEC_ATTRS;
#else
typedef LPTHREAD_START_ROUTINE  SEC_THREAD_START;
typedef LPSECURITY_ATTRIBUTES   SEC_ATTRS;
#endif




//
// The following structures are used by the helper functions
//

typedef struct _SECPKG_CLIENT_INFO {
    LUID            LogonId;            // Effective Logon Id
    ULONG           ProcessID;          // Process Id of caller
    ULONG           ThreadID;           // Thread Id of caller
    BOOLEAN         HasTcbPrivilege;    // Client has TCB
    BOOLEAN         Impersonating;      // Client is impersonating
} SECPKG_CLIENT_INFO, * PSECPKG_CLIENT_INFO;

typedef struct _SECPKG_CALL_INFO {
    ULONG           ProcessId ;
    ULONG           ThreadId ;
    ULONG           Attributes ;
    ULONG           Reserved ;
} SECPKG_CALL_INFO, * PSECPKG_CALL_INFO ;

#define SECPKG_CALL_KERNEL_MODE 0x00000001  // Call originated in kernel mode
#define SECPKG_CALL_ANSI        0x00000002  // Call came from ANSI stub
#define SECPKG_CALL_URGENT      0x00000004  // Call designated urgent


//
// This flag is used for to indicate which buffers in the SPMgr are located
// in the client's address space
//

#define SECBUFFER_UNMAPPED 0x40000000


//////////////////////////////////////////////////////////////////////////
//
// The following prototypes are to functions that are provided by the SPMgr
// to security packages.
//
//////////////////////////////////////////////////////////////////////////

typedef NTSTATUS
(NTAPI LSA_IMPERSONATE_CLIENT) (
    VOID
    );


typedef NTSTATUS
(NTAPI LSA_UNLOAD_PACKAGE)(
    VOID
    );

typedef NTSTATUS
(NTAPI LSA_DUPLICATE_HANDLE)(
    IN HANDLE SourceHandle,
    OUT PHANDLE DestionationHandle);


typedef NTSTATUS
(NTAPI LSA_SAVE_SUPPLEMENTAL_CREDENTIALS)(
    IN PLUID LogonId,
    IN ULONG SupplementalCredSize,
    IN PVOID SupplementalCreds,
    IN BOOLEAN Synchronous
    );

#ifdef _WINDEF_

typedef NTSTATUS
(NTAPI LSA_GET_WINDOW)(
    OUT HWND * Window
    );

#else

typedef NTSTATUS
(NTAPI LSA_GET_WINDOW)(
    OUT HANDLE * Window
    );

#endif

typedef VOID
(NTAPI LSA_RELEASE_WINDOW)(
    VOID
    );



typedef HANDLE
(NTAPI LSA_CREATE_THREAD)(
    IN SEC_ATTRS SecurityAttributes,
    IN ULONG StackSize,
    IN SEC_THREAD_START StartFunction,
    IN PVOID ThreadParameter,
    IN ULONG CreationFlags,
    OUT PULONG ThreadId
    );


typedef NTSTATUS
(NTAPI LSA_GET_CLIENT_INFO)(
    OUT PSECPKG_CLIENT_INFO ClientInfo
    );



typedef HANDLE
(NTAPI LSA_REGISTER_NOTIFICATION)(
    IN SEC_THREAD_START StartFunction,
    IN PVOID Parameter,
    IN ULONG NotificationType,
    IN ULONG NotificationClass,
    IN ULONG NotificationFlags,
    IN ULONG IntervalMinutes,
    IN OPTIONAL HANDLE WaitEvent
    );


typedef NTSTATUS
(NTAPI LSA_CANCEL_NOTIFICATION)(
    IN HANDLE NotifyHandle
    );

typedef NTSTATUS
(NTAPI LSA_MAP_BUFFER)(
    IN PSecBuffer InputBuffer,
    OUT PSecBuffer OutputBuffer
    );

typedef NTSTATUS
(NTAPI LSA_CREATE_TOKEN) (
    IN PLUID LogonId,
    IN PTOKEN_SOURCE TokenSource,
    IN SECURITY_LOGON_TYPE LogonType,
    IN LSA_TOKEN_INFORMATION_TYPE TokenInformationType,
    IN PVOID TokenInformation,
    IN PTOKEN_GROUPS TokenGroups,
    IN PUNICODE_STRING AccountName,
    IN PUNICODE_STRING AuthorityName,
    IN PUNICODE_STRING Workstation,
    OUT PHANDLE Token,
    OUT PNTSTATUS SubStatus
    );

typedef VOID
(NTAPI LSA_AUDIT_LOGON) (
    IN NTSTATUS Status,
    IN NTSTATUS SubStatus,
    IN PUNICODE_STRING AccountName,
    IN PUNICODE_STRING AuthenticatingAuthority,
    IN PUNICODE_STRING WorkstationName,
    IN OPTIONAL PSID UserSid,
    IN SECURITY_LOGON_TYPE LogonType,
    IN PTOKEN_SOURCE TokenSource,
    IN PLUID LogonId
    );

typedef NTSTATUS
(NTAPI LSA_CALL_PACKAGE) (
    IN PUNICODE_STRING AuthenticationPackage,
    IN PVOID ProtocolSubmitBuffer,
    IN ULONG SubmitBufferLength,
    OUT PVOID *ProtocolReturnBuffer,
    OUT PULONG ReturnBufferLength,
    OUT PNTSTATUS ProtocolStatus
    );

typedef VOID
(NTAPI LSA_FREE_LSA_HEAP) (
    IN PVOID Base
    );

typedef BOOLEAN
(NTAPI LSA_GET_CALL_INFO) (
    OUT PSECPKG_CALL_INFO   Info
    );


#define NOTIFIER_FLAG_NEW_THREAD    0x00000001
#define NOTIFIER_FLAG_ONE_SHOT      0x00000002
#define NOTIFIER_FLAG_HANDLE_FREE   0x00000004
#define NOTIFIER_FLAG_SECONDS       0x80000000

#define NOTIFIER_TYPE_INTERVAL      1
#define NOTIFIER_TYPE_HANDLE_WAIT   2
#define NOTIFIER_TYPE_STATE_CHANGE  3
#define NOTIFIER_TYPE_NOTIFY_EVENT  4
#define NOTIFIER_TYPE_IMMEDIATE 16

#define NOTIFY_CLASS_PACKAGE_CHANGE 1

typedef struct _SECPKG_EVENT_PACKAGE_CHANGE {
    ULONG   ChangeType;
    ULONG   PackageId;
    SECURITY_STRING PackageName;
} SECPKG_EVENT_PACKAGE_CHANGE, * PSECPKG_EVENT_PACKAGE_CHANGE ;

#define SECPKG_PACKAGE_CHANGE_LOAD      0
#define SECPKG_PACKAGE_CHANGE_UNLOAD    1
#define SECPKG_PACKAGE_CHANGE_SELECT    2

typedef struct _SECPKG_EVENT_NOTIFY {
    ULONG EventClass;
    ULONG Reserved;
    ULONG EventDataSize;
    PVOID EventData;
    PVOID PackageParameter;
} SECPKG_EVENT_NOTIFY, *PSECPKG_EVENT_NOTIFY ;

typedef LSA_IMPERSONATE_CLIENT * PLSA_IMPERSONATE_CLIENT;
typedef LSA_UNLOAD_PACKAGE * PLSA_UNLOAD_PACKAGE;
typedef LSA_DUPLICATE_HANDLE * PLSA_DUPLICATE_HANDLE ;
typedef LSA_SAVE_SUPPLEMENTAL_CREDENTIALS * PLSA_SAVE_SUPPLEMENTAL_CREDENTIALS;
typedef LSA_GET_WINDOW * PLSA_GET_WINDOW;
typedef LSA_RELEASE_WINDOW * PLSA_RELEASE_WINDOW;
typedef LSA_CREATE_THREAD * PLSA_CREATE_THREAD;
typedef LSA_GET_CLIENT_INFO * PLSA_GET_CLIENT_INFO;
typedef LSA_REGISTER_NOTIFICATION * PLSA_REGISTER_NOTIFICATION;
typedef LSA_CANCEL_NOTIFICATION * PLSA_CANCEL_NOTIFICATION;
typedef LSA_MAP_BUFFER * PLSA_MAP_BUFFER;
typedef LSA_CREATE_TOKEN * PLSA_CREATE_TOKEN;
typedef LSA_AUDIT_LOGON * PLSA_AUDIT_LOGON;
typedef LSA_CALL_PACKAGE * PLSA_CALL_PACKAGE;
typedef LSA_GET_CALL_INFO * PLSA_GET_CALL_INFO ;


// Functions provided by the SPM to the packages:
typedef struct _LSA_SECPKG_FUNCTION_TABLE {
    PLSA_CREATE_LOGON_SESSION CreateLogonSession;
    PLSA_DELETE_LOGON_SESSION DeleteLogonSession;
    PLSA_ADD_CREDENTIAL AddCredential;
    PLSA_GET_CREDENTIALS GetCredentials;
    PLSA_DELETE_CREDENTIAL DeleteCredential;
    PLSA_ALLOCATE_LSA_HEAP AllocateLsaHeap;
    PLSA_FREE_LSA_HEAP FreeLsaHeap;
    PLSA_ALLOCATE_CLIENT_BUFFER AllocateClientBuffer;
    PLSA_FREE_CLIENT_BUFFER FreeClientBuffer;
    PLSA_COPY_TO_CLIENT_BUFFER CopyToClientBuffer;
    PLSA_COPY_FROM_CLIENT_BUFFER CopyFromClientBuffer;
    PLSA_IMPERSONATE_CLIENT ImpersonateClient;
    PLSA_UNLOAD_PACKAGE UnloadPackage;
    PLSA_DUPLICATE_HANDLE DuplicateHandle;
    PLSA_SAVE_SUPPLEMENTAL_CREDENTIALS SaveSupplementalCredentials;
    PLSA_GET_WINDOW GetWindow;
    PLSA_RELEASE_WINDOW ReleaseWindow;
    PLSA_CREATE_THREAD CreateThread;
    PLSA_GET_CLIENT_INFO GetClientInfo;
    PLSA_REGISTER_NOTIFICATION RegisterNotification;
    PLSA_CANCEL_NOTIFICATION CancelNotification;
    PLSA_MAP_BUFFER MapBuffer;
    PLSA_CREATE_TOKEN CreateToken;
    PLSA_AUDIT_LOGON AuditLogon;
    PLSA_CALL_PACKAGE CallPackage;
    PLSA_FREE_LSA_HEAP FreeReturnBuffer;
    PLSA_GET_CALL_INFO GetCallInfo;
} LSA_SECPKG_FUNCTION_TABLE, *PLSA_SECPKG_FUNCTION_TABLE;

typedef struct _SECPKG_DLL_FUNCTIONS {
    PLSA_ALLOCATE_LSA_HEAP AllocateHeap;
    PLSA_FREE_LSA_HEAP FreeHeap;
} SECPKG_DLL_FUNCTIONS, * PSECPKG_DLL_FUNCTIONS;



#define PRIMARY_CRED_CLEAR_PASSWORD 0x1
#define PRIMARY_CRED_OWF_PASSWORD 0x2

typedef struct _SECPKG_PRIMARY_CRED {
    LUID LogonId;
    UNICODE_STRING DownlevelName;
    UNICODE_STRING DomainName;
    UNICODE_STRING Password;
    PSID UserSid;
    ULONG Flags;
} SECPKG_PRIMARY_CRED, *PSECPKG_PRIMARY_CRED;

//
// Maximum size of stored credentials.
//

#define MAX_CRED_SIZE 1024

typedef struct _SECPKG_PARAMETERS {
    ULONG           Version;
    ULONG           MachineState;
    ULONG           SetupMode;
    UNICODE_STRING  DomainName;
    PSID            DomainSid;
} SECPKG_PARAMETERS, *PSECPKG_PARAMETERS;

typedef struct _SECPKG_SUPPLEMENTAL_CRED {
    UNICODE_STRING PackageName;
    ULONG CredentialSize;
    PUCHAR Credentials;
} SECPKG_SUPPLEMENTAL_CRED, *PSECPKG_SUPPLEMENTAL_CRED;


//
// Extended Package information structures
//

#define SECPKG_INFO_GSS_INFO    1

typedef struct _SECPKG_GSS_INFO {
    PUCHAR  EncodedId;
} SECPKG_GSS_INFO, * PSECPKG_GSS_INFO ;




//
// The following prototypes are to functions that will be called only while
// in the Security Package Manager context.
//

typedef NTSTATUS
(LSA_AP_INITIALIZE_PACKAGE) (
    IN ULONG AuthenticationPackageId,
    IN PLSA_DISPATCH_TABLE LsaDispatchTable,
    IN PLSA_STRING Database OPTIONAL,
    IN PLSA_STRING Confidentiality OPTIONAL,
    OUT PLSA_STRING *AuthenticationPackageName
    );

typedef NTSTATUS
(LSA_AP_LOGON_USER) (
    IN PLSA_CLIENT_REQUEST ClientRequest,
    IN SECURITY_LOGON_TYPE LogonType,
    IN PVOID AuthenticationInformation,
    IN PVOID ClientAuthenticationBase,
    IN ULONG AuthenticationInformationLength,
    OUT PVOID *ProfileBuffer,
    OUT PULONG ProfileBufferLength,
    OUT PLUID LogonId,
    OUT PNTSTATUS SubStatus,
    OUT PLSA_TOKEN_INFORMATION_TYPE TokenInformationType,
    OUT PVOID *TokenInformation,
    OUT PLSA_UNICODE_STRING *AccountName,
    OUT PLSA_UNICODE_STRING *AuthenticatingAuthority
    );

typedef NTSTATUS
(LSA_AP_LOGON_USER_EX) (
    IN PLSA_CLIENT_REQUEST ClientRequest,
    IN SECURITY_LOGON_TYPE LogonType,
    IN PVOID AuthenticationInformation,
    IN PVOID ClientAuthenticationBase,
    IN ULONG AuthenticationInformationLength,
    OUT PVOID *ProfileBuffer,
    OUT PULONG ProfileBufferLength,
    OUT PLUID LogonId,
    OUT PNTSTATUS SubStatus,
    OUT PLSA_TOKEN_INFORMATION_TYPE TokenInformationType,
    OUT PVOID *TokenInformation,
    OUT PUNICODE_STRING *AccountName,
    OUT PUNICODE_STRING *AuthenticatingAuthority,
    OUT PUNICODE_STRING *MachineName
    );

typedef NTSTATUS
(LSA_AP_CALL_PACKAGE) (
    IN PLSA_CLIENT_REQUEST ClientRequest,
    IN PVOID ProtocolSubmitBuffer,
    IN PVOID ClientBufferBase,
    IN ULONG SubmitBufferLength,
    OUT PVOID *ProtocolReturnBuffer,
    OUT PULONG ReturnBufferLength,
    OUT PNTSTATUS ProtocolStatus
    );

typedef VOID
(LSA_AP_LOGON_TERMINATED) (
    IN PLUID LogonId
    );

typedef LSA_AP_CALL_PACKAGE LSA_AP_CALL_PACKAGE_UNTRUSTED;


typedef NTSTATUS
(NTAPI SpInitializeFn)(
    IN ULONG PackageId,
    IN PSECPKG_PARAMETERS Parameters,
    IN PLSA_SECPKG_FUNCTION_TABLE FunctionTable
    );

typedef NTSTATUS
(NTAPI SpShutdownFn)(
    VOID
    );

typedef NTSTATUS
(NTAPI SpGetInfoFn)(
    OUT PSecPkgInfo PackageInfo
    );

typedef NTSTATUS
(LSA_AP_LOGON_USER_EX2) (
    IN PLSA_CLIENT_REQUEST ClientRequest,
    IN SECURITY_LOGON_TYPE LogonType,
    IN PVOID AuthenticationInformation,
    IN PVOID ClientAuthenticationBase,
    IN ULONG AuthenticationInformationLength,
    OUT PVOID *ProfileBuffer,
    OUT PULONG ProfileBufferLength,
    OUT PLUID LogonId,
    OUT PNTSTATUS SubStatus,
    OUT PLSA_TOKEN_INFORMATION_TYPE TokenInformationType,
    OUT PVOID *TokenInformation,
    OUT PUNICODE_STRING *AccountName,
    OUT PUNICODE_STRING *AuthenticatingAuthority,
    OUT PUNICODE_STRING *MachineName,
    OUT PSECPKG_PRIMARY_CRED PrimaryCredentials,
    OUT PULONG CachedCredentialCount,
    OUT PSECPKG_SUPPLEMENTAL_CRED * CachedCredentials
    );

typedef LSA_AP_LOGON_USER_EX2 *PLSA_AP_LOGON_USER_EX2;
#define LSA_AP_NAME_LOGON_USER_EX2 "LsaApLogonUserEx2\0"

typedef NTSTATUS
(NTAPI SpAcceptCredentialsFn)(
    IN SECURITY_LOGON_TYPE LogonType,
    IN PUNICODE_STRING AccountName,
    IN PSECPKG_PRIMARY_CRED PrimaryCredentials,
    IN PSECPKG_SUPPLEMENTAL_CRED SupplementalCredentials
    );
#define SP_ACCEPT_CREDENTIALS_NAME "SpAcceptCredentials\0"

typedef NTSTATUS
(NTAPI SpAcquireCredentialsHandleFn)(
    IN OPTIONAL PUNICODE_STRING PrincipalName,
    IN ULONG CredentialUseFlags,
    IN OPTIONAL PLUID LogonId,
    IN PVOID AuthorizationData,
    IN PVOID GetKeyFunciton,
    IN PVOID GetKeyArgument,
    OUT PULONG CredentialHandle,
    OUT PTimeStamp ExpirationTime
    );

typedef NTSTATUS
(NTAPI SpFreeCredentialsHandleFn)(
    IN ULONG CredentialHandle
    );

typedef NTSTATUS
(NTAPI SpQueryCredentialsAttributesFn)(
    IN ULONG CredentialHandle,
    IN ULONG CredentialAttribute,
    IN OUT PVOID Buffer
    );

typedef NTSTATUS
(NTAPI SpSaveCredentialsFn)(
    IN ULONG CredentialHandle,
    IN PSecBuffer Credentials);

typedef NTSTATUS
(NTAPI SpGetCredentialsFn)(
    IN ULONG CredentialHandle,
    IN OUT PSecBuffer Credentials
    );

typedef NTSTATUS
(NTAPI SpDeleteCredentialsFn)(
    IN ULONG CredentialHandle,
    IN PSecBuffer Key
    );

typedef NTSTATUS
(NTAPI SpInitLsaModeContextFn)(
    IN OPTIONAL ULONG CredentialHandle,
    IN OPTIONAL ULONG ContextHandle,
    IN OPTIONAL PUNICODE_STRING TargetName,
    IN ULONG ContextRequirements,
    IN ULONG TargetDataRep,
    IN PSecBufferDesc InputBuffers,
    OUT PULONG NewContextHandle,
    IN OUT PSecBufferDesc OutputBuffers,
    OUT PULONG ContextAttributes,
    OUT PTimeStamp ExpirationTime,
    OUT PBOOLEAN MappedContext,
    OUT PSecBuffer ContextData
    );




typedef NTSTATUS
(NTAPI SpDeleteContextFn)(
    IN ULONG ContextHandle
    );

typedef NTSTATUS
(NTAPI SpApplyControlTokenFn)(
    IN ULONG ContextHandle,
    IN PSecBufferDesc ControlToken);


typedef NTSTATUS
(NTAPI SpAcceptLsaModeContextFn)(
    IN OPTIONAL ULONG CredentialHandle,
    IN OPTIONAL ULONG ContextHandle,
    IN PSecBufferDesc InputBuffer,
    IN ULONG ContextRequirements,
    IN ULONG TargetDataRep,
    OUT PULONG NewContextHandle,
    OUT PSecBufferDesc OutputBuffer,
    OUT PULONG ContextAttributes,
    OUT PTimeStamp ExpirationTime,
    OUT PBOOLEAN MappedContext,
    OUT PSecBuffer ContextData
    );




typedef NTSTATUS
(NTAPI SpGetUserInfoFn)(
    IN PLUID LogonId,
    IN ULONG Flags,
    OUT PSecurityUserData * UserData
    );



typedef
NTSTATUS
(NTAPI SpGetExtendedInformationFn)(
    IN ULONG PackageInformationType,
    OUT PVOID * PackageInformation
    );


typedef struct _SECPKG_FUNCTION_TABLE {
    PLSA_AP_INITIALIZE_PACKAGE InitializePackage;
    PLSA_AP_LOGON_USER LogonUser;
    PLSA_AP_CALL_PACKAGE CallPackage;
    PLSA_AP_LOGON_TERMINATED LogonTerminated;
    PLSA_AP_CALL_PACKAGE_UNTRUSTED CallPackageUntrusted;
    PLSA_AP_LOGON_USER_EX LogonUserEx;
    PLSA_AP_LOGON_USER_EX2 LogonUserEx2;
    SpInitializeFn * Initialize;
    SpShutdownFn * Shutdown;
    SpGetInfoFn * GetInfo;
    SpAcceptCredentialsFn * AcceptCredentials;
    SpAcquireCredentialsHandleFn * AcquireCredentialsHandle;
    SpQueryCredentialsAttributesFn * QueryCredentialsAttributes;
    SpFreeCredentialsHandleFn * FreeCredentialsHandle;
    SpSaveCredentialsFn * SaveCredentials;
    SpGetCredentialsFn * GetCredentials;
    SpDeleteCredentialsFn * DeleteCredentials;
    SpInitLsaModeContextFn * InitLsaModeContext;
    SpAcceptLsaModeContextFn * AcceptLsaModeContext;
    SpDeleteContextFn * DeleteContext;
    SpApplyControlTokenFn * ApplyControlToken;
    SpGetUserInfoFn * GetUserInfo;
} SECPKG_FUNCTION_TABLE, *PSECPKG_FUNCTION_TABLE;

//
// The following prototypes are to functions that will be called while in the
// context of a user process that is using the functions through the security
// DLL.
//

typedef NTSTATUS
(NTAPI SpInstanceInitFn)(
    IN ULONG Version,
    IN PSECPKG_DLL_FUNCTIONS FunctionTable,
    OUT PVOID * UserFunctions
    );


typedef NTSTATUS
(NTAPI SpInitUserModeContextFn)(
    IN ULONG ContextHandle,
    IN PSecBuffer PackedContext
    );

typedef NTSTATUS
(NTAPI SpMakeSignatureFn)(
    IN ULONG ContextHandle,
    IN ULONG QualityOfProtection,
    IN PSecBufferDesc MessageBuffers,
    IN ULONG MessageSequenceNumber
    );

typedef NTSTATUS
(NTAPI SpVerifySignatureFn)(
    IN ULONG ContextHandle,
    IN PSecBufferDesc MessageBuffers,
    IN ULONG MessageSequenceNumber,
    OUT PULONG QualityOfProtection
    );

typedef NTSTATUS
(NTAPI SpSealMessageFn)(
    IN ULONG ContextHandle,
    IN ULONG QualityOfProtection,
    IN PSecBufferDesc MessageBuffers,
    IN ULONG MessageSequenceNumber
    );

typedef NTSTATUS
(NTAPI SpUnsealMessageFn)(
    IN ULONG ContextHandle,
    IN PSecBufferDesc MessageBuffers,
    IN ULONG MessageSequenceNumber,
    OUT PULONG QualityOfProtection
    );


typedef NTSTATUS
(NTAPI SpGetContextTokenFn)(
    IN ULONG ContextHandle,
    OUT PHANDLE ImpersonationToken
    );

typedef NTSTATUS
(NTAPI SpQueryContextAttributesFn)(
    IN ULONG ContextHandle,
    IN ULONG ContextAttribute,
    IN OUT PVOID Buffer);


typedef NTSTATUS
(NTAPI SpCompleteAuthTokenFn)(
    IN ULONG ContextHandle,
    IN PSecBufferDesc InputBuffer
    );


typedef NTSTATUS
(NTAPI SpFormatCredentialsFn)(
    IN PSecBuffer Credentials,
    OUT PSecBuffer FormattedCredentials
    );

typedef NTSTATUS
(NTAPI SpMarshallSupplementalCredsFn)(
    IN ULONG CredentialSize,
    IN PUCHAR Credentials,
    OUT PULONG MarshalledCredSize,
    OUT PVOID * MarshalledCreds);


typedef struct _SECPKG_USER_FUNCTION_TABLE {
    SpInstanceInitFn *                      InstanceInit;
    SpInitUserModeContextFn *               InitUserModeContext;
    SpMakeSignatureFn *                     MakeSignature;
    SpVerifySignatureFn *                   VerifySignature;
    SpSealMessageFn *                       SealMessage;
    SpUnsealMessageFn *                     UnsealMessage;
    SpGetContextTokenFn *                   GetContextToken;
    SpQueryContextAttributesFn *            QueryContextAttributes;
    SpCompleteAuthTokenFn *                 CompleteAuthToken;
    SpDeleteContextFn *                     DeleteUserModeContext;
    SpFormatCredentialsFn *                 FormatCredentials;
    SpMarshallSupplementalCredsFn *         MarshallSupplementalCreds;
} SECPKG_USER_FUNCTION_TABLE, *PSECPKG_USER_FUNCTION_TABLE;

typedef NTSTATUS
(SEC_ENTRY * SpLsaModeInitializeFn)(
    IN ULONG LsaVersion,
    OUT PULONG PackageVersion,
    OUT PSECPKG_FUNCTION_TABLE * ppTables,
    OUT PULONG pcTables);

typedef NTSTATUS
(SEC_ENTRY * SpUserModeInitializeFn)(
    IN ULONG LsaVersion,
    OUT PULONG PackageVersion,
    OUT PSECPKG_USER_FUNCTION_TABLE *ppTables,
    OUT PULONG pcTables
    );


#define SP_ORDINAL_LSA_INIT                     0
#define SP_ORDINAL_LOGONUSER                    1
#define SP_ORDINAL_CALLPACKAGE                  2
#define SP_ORDINAL_LOGONTERMINATED              3
#define SP_ORDINAL_CALLPACKAGEUNTRUSTED         4
#define SP_ORDINAL_LOGONUSEREX                  5
#define SP_ORDINAL_LOGONUSEREX2                 6
#define SP_ORDINAL_INITIALIZE                   7
#define SP_ORDINAL_SHUTDOWN                     8
#define SP_ORDINAL_GETINFO                      9
#define SP_ORDINAL_ACCEPTCREDS                  10
#define SP_ORDINAL_ACQUIRECREDHANDLE            11
#define SP_ORDINAL_QUERYCREDATTR                12
#define SP_ORDINAL_FREECREDHANDLE               13
#define SP_ORDINAL_SAVECRED                     14
#define SP_ORDINAL_GETCRED                      15
#define SP_ORDINAL_DELETECRED                   16
#define SP_ORDINAL_INITLSAMODECTXT              17
#define SP_ORDINAL_ACCEPTLSAMODECTXT            18
#define SP_ORDINAL_DELETECTXT                   19
#define SP_ORDINAL_APPLYCONTROLTOKEN            20
#define SP_ORDINAL_GETUSERINFO                  21
#define SP_ORDINAL_GRANTPROXY                   22
#define SP_ORDINAL_REVOKEPROXY                  23
#define SP_ORDINAL_INVOKEPROXY                  24
#define SP_ORDINAL_RENEWPROXY                   25


#define SP_MAX_TABLE_ORDINAL            (SP_ORDINAL_RENEWPROXY + 1)
#define SP_MAX_AUTHPKG_ORDINAL          (SP_ORDINAL_LOGONUSEREX)

#define SP_ORDINAL_INSTANCEINIT         32


#define SECPKG_LSAMODEINIT_NAME     "SpLsaModeInitialize"
#define SECPKG_USERMODEINIT_NAME    "SpUserModeInitialize"

#define SECPKG_INTERFACE_VERSION    0x00010000



typedef struct _SECPKG_KERNEL_FUNCTIONS {
    PLSA_ALLOCATE_LSA_HEAP AllocateHeap;
    PLSA_FREE_LSA_HEAP FreeHeap;
} SECPKG_KERNEL_FUNCTIONS, *PSECPKG_KERNEL_FUNCTIONS;

typedef NTSTATUS
(NTAPI KspInitPackageFn)(
    PSECPKG_KERNEL_FUNCTIONS    FunctionTable
    );

typedef NTSTATUS
(NTAPI KspDeleteContextFn)(
    IN ULONG ContextId,
    OUT PULONG LsaContextId
    );

typedef NTSTATUS
(NTAPI KspInitContextFn)(
    IN ULONG ContextId,
    IN PSecBuffer ContextData,
    OUT PULONG NewContextId
    );

typedef NTSTATUS
(NTAPI KspMakeSignatureFn)(
    IN ULONG ContextId,
    IN ULONG fQOP,
    IN OUT PSecBufferDesc Message,
    IN ULONG MessageSeqNo
    );

typedef NTSTATUS
(NTAPI KspVerifySignatureFn)(
    IN ULONG ContextId,
    IN OUT PSecBufferDesc Message,
    IN ULONG MessageSeqNo,
    OUT PULONG pfQOP
    );


typedef NTSTATUS
(NTAPI KspSealMessageFn)(
    IN ULONG ContextId,
    IN ULONG fQOP,
    IN OUT PSecBufferDesc Message,
    IN ULONG MessageSeqNo
    );

typedef NTSTATUS
(NTAPI KspUnsealMessageFn)(
    IN ULONG ContextId,
    IN OUT PSecBufferDesc Message,
    IN ULONG MessageSeqNo,
    OUT PULONG pfQOP
    );

typedef NTSTATUS
(NTAPI KspGetTokenFn)(
    IN ULONG ContextId,
    OUT PHANDLE ImpersonationToken,
    OUT OPTIONAL PACCESS_TOKEN * RawToken
    );

typedef NTSTATUS
(NTAPI KspQueryAttributesFn)(
    IN ULONG ContextId,
    IN ULONG Attribute,
    IN OUT PVOID Buffer
    );

typedef NTSTATUS
(NTAPI KspCompleteTokenFn)(
    IN ULONG ContextId,
    IN PSecBufferDesc Token
    );


typedef NTSTATUS
(NTAPI KspMapHandleFn)(
    IN ULONG ContextId,
    OUT PULONG LsaContextId
    );

typedef struct _SECPKG_KERNEL_FUNCTION_TABLE {
    KspInitPackageFn *      Initialize;
    KspDeleteContextFn *    DeleteContext;
    KspInitContextFn *      InitContext;
    KspMapHandleFn *        MapHandle;
    KspMakeSignatureFn *    Sign;
    KspVerifySignatureFn *  Verify;
    KspSealMessageFn *      Seal;
    KspUnsealMessageFn *    Unseal;
    KspGetTokenFn *         GetToken;
    KspQueryAttributesFn *  QueryAttributes;
    KspCompleteTokenFn *    CompleteToken;
} SECPKG_KERNEL_FUNCTION_TABLE, *PSECPKG_KERNEL_FUNCTION_TABLE;

SECURITY_STATUS
SEC_ENTRY
KsecRegisterSecurityProvider(
    PSECURITY_STRING    ProviderName,
    PSECPKG_KERNEL_FUNCTION_TABLE Table
    );


extern SECPKG_KERNEL_FUNCTIONS KspKernelFunctions;


//
// Common types used by negotiable security packages
//

#define SEC_WINNT_AUTH_IDENTITY_MARSHALLED 0x4

#endif // __SECPKG_H__
