//+-------------------------------------------------------------------------
//
//  Microsoft Windows
//
//  Copyright 1996 - 1998 Microsoft Corporation.
//
//  File:       wintrust.h
//
//  Contents:   Microsoft Internet Security Trust Provider Model
//
//  History:    31-May-1997 created
//
//--------------------------------------------------------------------------

#ifndef WINTRUST_H
#define WINTRUST_H

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
//      Client definitions, typedefs, and prototypes
//
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#pragma pack(8)

//////////////////////////////////////////////////////////////////////////////
//
// WINTRUST_DATA Structure
//----------------------------------------------------------------------------
//  Used when calling WinVerifyTrust to pass necessary information into
//  the Providers.
//
typedef struct _WINTRUST_DATA
{
    DWORD           cbStruct;                   // = sizeof(WINTRUST_DATA)

    LPVOID          pPolicyCallbackData;        // optional: used to pass data between the app and policy

    DWORD           dwUIChoice;                 // required: UI choice.  One of the following.
#                       define      WTD_UI_ALL              1
#                       define      WTD_UI_NONE             2
#                       define      WTD_UI_NOBAD            3
#                       define      WTD_UI_NOGOOD           4

    DWORD           fdwRevocationChecks;        // required: certificate revocation check options
#                       define      WTD_REVOKE_NONE         0x00000000
#                       define      WTD_REVOKE_WHOLECHAIN   0x00000001

    DWORD           dwUnionChoice;              // required: which structure is being passed in?
#                       define      WTD_CHOICE_FILE         1
#                       define      WTD_CHOICE_CATALOG      2
#                       define      WTD_CHOICE_BLOB         3
#                       define      WTD_CHOICE_SIGNER       4
#                       define      WTD_CHOICE_CERT         5
    union
    {
        struct WINTRUST_FILE_INFO_      *pFile;         // individual file
        struct WINTRUST_CATALOG_INFO_   *pCatalog;      // member of a Catalog File
        struct WINTRUST_BLOB_INFO_      *pBlob;         // memory blob
        struct WINTRUST_SGNR_INFO_      *pSgnr;         // signer structure only
        struct WINTRUST_CERT_INFO_      *pCert;
    };

    DWORD           dwStateAction;                      // future. DO NOT USE!!! (optional)
#                       define      WTD_STATEACTION_OPEN    1
#                       define      WTD_STATEACTION_VERIFY  2
#                       define      WTD_STATEACTION_CLOSE   3

    HANDLE          hWVTStateData;                      // future. DO NOT USE!!! (optional)

} WINTRUST_DATA, *PWINTRUST_DATA;

//////////////////////////////////////////////////////////////////////////////
//
// WINTRUST_FILE_INFO Structure
//----------------------------------------------------------------------------
//  Used when calling WinVerifyTrust against an individual file.
//
typedef struct WINTRUST_FILE_INFO_
{
    DWORD           cbStruct;                   // = sizeof(WINTRUST_FILE_INFO)

    LPCWSTR         pcwszFilePath;              // required, file name to be verified
    HANDLE          hFile;                      // optional, open handle to pcwszFilePath
      
} WINTRUST_FILE_INFO, *PWINTRUST_FILE_INFO;

//////////////////////////////////////////////////////////////////////////////
//
// WINTRUST_CATALOG_INFO Structure
//----------------------------------------------------------------------------
//  Used when calling WinVerifyTrust against a member of a Microsoft Catalog
//  file.
//
typedef struct WINTRUST_CATALOG_INFO_
{
    DWORD               cbStruct;               // = sizeof(WINTRUST_CATALOG_INFO)

    DWORD               dwCatalogVersion;       // optional: Catalog version number
    LPCWSTR             pcwszCatalogFilePath;   // required: path/name to Catalog file

    LPCWSTR             pcwszMemberTag;         // required: tag to member in Catalog
    LPCWSTR             pcwszMemberFilePath;    // required: path/name to member file
    HANDLE              hMemberFile;            // optional: open handle to pcwszMemberFilePath

} WINTRUST_CATALOG_INFO, *PWINTRUST_CATALOG_INFO;

//////////////////////////////////////////////////////////////////////////////
//
// WINTRUST_BLOB_INFO Structure
//----------------------------------------------------------------------------
//  Used when calling WinVerifyTrust against a memory blob.
//
typedef struct WINTRUST_BLOB_INFO_
{
    DWORD               cbStruct;               // = sizeof(WINTRUST_BLOB_INFO)

    LPCWSTR             pcwszDisplayName;       // name of the "thing" the pbMem is pointing to.

    DWORD               cbMem;
    BYTE                *pbMem;

} WINTRUST_BLOB_INFO, *PWINTRUST_BLOB_INFO;

//////////////////////////////////////////////////////////////////////////////
//
// WINTRUST_SGNR_INFO Structure
//----------------------------------------------------------------------------
//  Used when calling WinVerifyTrust against a CMSG_SIGNER_INFO Structure
//
typedef struct WINTRUST_SGNR_INFO_
{
    DWORD               cbStruct;               // = sizeof(WINTRUST_SGNR_INFO)

    LPCWSTR             pcwszDisplayName;       // name of the "thing" the pbMem is pointing to.

    CMSG_SIGNER_INFO    *psSignerInfo;

    DWORD               chStores;               // number of stores in pahStores
    HCERTSTORE          *pahStores;             // array of stores to add to internal list

} WINTRUST_SGNR_INFO, *PWINTRUST_SGNR_INFO;

//////////////////////////////////////////////////////////////////////////////
//
// WINTRUST_CERT_INFO Structure
//----------------------------------------------------------------------------
//  Used when calling WinVerifyTrust against a CERT_CONTEXT Structure
//
typedef struct WINTRUST_CERT_INFO_
{
    DWORD               cbStruct;               // = sizeof(WINTRUST_CERT_INFO)

    LPCWSTR             pcwszDisplayName;       // name of the "thing" the pbMem is pointing to.

    CERT_CONTEXT        *psCertContext;

    DWORD               chStores;               // number of stores in pahStores
    HCERTSTORE          *pahStores;             // array of stores to add to internal list

} WINTRUST_CERT_INFO, *PWINTRUST_CERT_INFO;

#pragma pack()


//////////////////////////////////////////////////////////////////////////////
//
// WinVerifyTrust
//----------------------------------------------------------------------------
//  Exported from WINTRUST.DLL.
//  Call this function to verify the trust based on a digital signer.
//
//  Returns:
//          ERROR_SUCCESS               If the trust is authenticated or
//                                      if the user accepted the risk.
//
//          TRUST_E_PROVIDER_UNKNOWN    there was an error loading one of the 
//                                      required Providers.
//
//          all error codes passed back are based on the Policy Provider used.
//

LONG WINAPI WinVerifyTrust(IN OPTIONAL HWND hwnd,
                              IN          GUID *pgActionID,
                              IN          LPVOID pWintrustData);


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
//      Trust, Policy, and UI Provider definitions, typedefs, and prototypes
//
//  Model:
//      A client wishing to validate trust through WinVerifyTrust will
//      select an appropriate Action ID guid for the call.
//      This guid is defined by each Policy Provider and represents the 
//      functions called based on the policy for the given object.
//
//      In this model, the Policy Provider determines which style of UI
//      will be shown to the user (this only applies to style, the 
//      determination of whether UI is displayed is set by the calling client
//      in the UI flags member of WINTRUST_DATA).
//
//      Since the function entry points are common (same return value and
//      parameters), it allows Policy Provider developers to take advantage 
//      of existing, generic, code to fill the CRYPT_PROVIDER_DATA structure.
//    
//      This also allows the developer to simply add the specific policy they
//      need, then, call the generic Policy Provider - if appropriate.
//
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//
// Supported ASN structures contained in WINTRUST.DLL
//----------------------------------------------------------------------------
//  
#pragma pack (8)

#define SPC_INDIRECT_DATA_CONTENT_STRUCT    ((LPCSTR)2003)
#define SPC_INDIRECT_DATA_OBJID             "1.3.6.1.4.1.311.2.1.4"
#define SPC_GLUE_RDN_OBJID                  "1.3.6.1.4.1.311.2.1.25"

typedef struct _SPC_INDIRECT_DATA_CONTENT 
{
    CRYPT_ATTRIBUTE_TYPE_VALUE    Data;
    CRYPT_ALGORITHM_IDENTIFIER    DigestAlgorithm;
    CRYPT_HASH_BLOB               Digest;

} SPC_INDIRECT_DATA_CONTENT, *PSPC_INDIRECT_DATA_CONTENT;

#pragma pack()


//////////////////////////////////////////////////////////////////////////////
//
// Wintrust Policy Flags
//----------------------------------------------------------------------------
//  These are set during install and can be modified by the user
//  through various means.  The SETREG.EXE utility (found in the Authenticode
//  Tools Pack) will select/deselect each of them.
//
#define WTPF_TRUSTTEST              0x00000020  // trust any "TEST" generated certificate
#define WTPF_TESTCANBEVALID         0x00000080 
#define WTPF_IGNOREEXPIRATION       0x00000100  // Use expiration date
#define WTPF_IGNOREREVOKATION       0x00000200  // Do revocation check
#define WTPF_OFFLINEOK_IND          0x00000400  // off-line is ok for individual certs
#define WTPF_OFFLINEOK_COM          0x00000800  // off-line is ok for commercial certs
#define WTPF_OFFLINEOKNBU_IND       0x00001000  // off-line is ok for individual certs, no bad ui
#define WTPF_OFFLINEOKNBU_COM       0x00002000  // off-line is ok for commercial certs, no bad ui
#define WTPF_TIMESTAMP_IND          0x00004000  // Use timestamp for individual certs
#define WTPF_TIMESTAMP_COM          0x00008000  // Use timestamp for commerical certs
#define WTPF_VERIFY_V1_OFF          0x00010000  // turn verify of v1 certs off
#define WTPF_IGNOREREVOCATIONONTS   0x00020000  // ignore TimeStamp revocation checks

//////////////////////////////////////////////////////////////////////////////
//
// WintrustGetRegPolicyFlags
//----------------------------------------------------------------------------
//  This API call is exported from WINTRUST.DLL and is the recommended method
//  of retrieving the DWORD representing the Policy Flags.
//
extern void WINAPI      WintrustGetRegPolicyFlags(DWORD *pdwPolicyFlags);


//////////////////////////////////////////////////////////////////////////////
//
// Trust Provider "Step" Error defines
//----------------------------------------------------------------------------
//  Each "step" of the Trust process has an error "slot" associated with it.
//  If an error occurs, the "step" will assign its result to this "slot".  These
//  errors can be any valid WINERROR.H HRESULT code.
//
#define TRUSTERROR_STEP_WVTPARAMS                   0
#define TRUSTERROR_STEP_FILEIO                      2
#define TRUSTERROR_STEP_SIP                         3
#define TRUSTERROR_STEP_SIPSUBJINFO                 5
#define TRUSTERROR_STEP_CATALOGFILE                 6
#define TRUSTERROR_STEP_CERTSTORE                   7
#define TRUSTERROR_STEP_MESSAGE                     8
#define TRUSTERROR_STEP_MSG_SIGNERCOUNT             9
#define TRUSTERROR_STEP_MSG_INNERCNTTYPE            10
#define TRUSTERROR_STEP_MSG_INNERCNT                11
#define TRUSTERROR_STEP_MSG_STORE                   12
#define TRUSTERROR_STEP_MSG_SIGNERINFO              13
#define TRUSTERROR_STEP_MSG_SIGNERCERT              14
#define TRUSTERROR_STEP_MSG_CERTCHAIN               15
#define TRUSTERROR_STEP_MSG_COUNTERSIGINFO          16
#define TRUSTERROR_STEP_MSG_COUNTERSIGCERT          17
#define TRUSTERROR_STEP_VERIFY_MSGHASH              18
#define TRUSTERROR_STEP_VERIFY_MSGINDIRECTDATA      19

#define TRUSTERROR_STEP_FINAL_WVTINIT               30
#define TRUSTERROR_STEP_FINAL_INITPROV              31
#define TRUSTERROR_STEP_FINAL_OBJPROV               32
#define TRUSTERROR_STEP_FINAL_SIGPROV               33
#define TRUSTERROR_STEP_FINAL_CERTPROV              34
#define TRUSTERROR_STEP_FINAL_CERTCHKPROV           35
#define TRUSTERROR_STEP_FINAL_POLICYPROV            36
#define TRUSTERROR_STEP_FINAL_UIPROV                37

#define TRUSTERROR_MAX_STEPS                        38

//////////////////////////////////////////////////////////////////////////////
//
//  allocation and free function prototypes
//----------------------------------------------------------------------------
//
typedef void        *(*PFN_CPD_MEM_ALLOC)(IN DWORD cbSize);
typedef void        (*PFN_CPD_MEM_FREE)(IN void *pvMem2Free);

typedef BOOL        (*PFN_CPD_ADD_STORE)(IN struct _CRYPT_PROVIDER_DATA *pProvData, 
                                         IN HCERTSTORE hStore2Add);

typedef BOOL        (*PFN_CPD_ADD_SGNR)(IN          struct _CRYPT_PROVIDER_DATA *pProvData, 
                                        IN          BOOL fCounterSigner,
                                        IN OPTIONAL DWORD idxSigner,
                                        IN          struct _CRYPT_PROVIDER_SGNR *pSgnr2Add);

typedef BOOL        (*PFN_CPD_ADD_CERT)(IN          struct _CRYPT_PROVIDER_DATA *pProvData, 
                                        IN          DWORD idxSigner,
                                        IN          BOOL fCounterSigner,
                                        IN OPTIONAL DWORD idxCounterSigner,
                                        IN          PCCERT_CONTEXT pCert2Add);

typedef BOOL        (*PFN_CPD_ADD_PRIVDATA)(IN struct _CRYPT_PROVIDER_DATA *pProvData,
                                            IN struct _CRYPT_PROVIDER_PRIVDATA *pPrivData2Add);

//////////////////////////////////////////////////////////////////////////////
//
//  Provider function prototypes
//----------------------------------------------------------------------------
//

//
//  entry point for the object provider
//
typedef HRESULT     (*PFN_PROVIDER_INIT_CALL)(IN OUT struct _CRYPT_PROVIDER_DATA *pProvData);

//
//  entry point for the object provider
//
typedef HRESULT     (*PFN_PROVIDER_OBJTRUST_CALL)(IN OUT struct _CRYPT_PROVIDER_DATA *pProvData);

//
//  entry point for the Signature Provider
//
typedef HRESULT     (*PFN_PROVIDER_SIGTRUST_CALL)(IN OUT struct _CRYPT_PROVIDER_DATA *pProvData);

//
//  entry point for the Certificate Provider
//
typedef HRESULT     (*PFN_PROVIDER_CERTTRUST_CALL)(IN OUT struct _CRYPT_PROVIDER_DATA *pProvData);

//
//  entry point for the Policy Provider's final call (from the trust provider)
//
typedef HRESULT     (*PFN_PROVIDER_FINALPOLICY_CALL)(IN OUT struct _CRYPT_PROVIDER_DATA *pProvData);

//
//  entry point for the Policy Provider's "dump structure" call 
//
typedef HRESULT     (*PFN_PROVIDER_TESTFINALPOLICY_CALL)(IN OUT struct _CRYPT_PROVIDER_DATA *pProvData);

//
//  entry point for the Policy Provider's Cert Check call.  This will return
//  true if the Trust Provider is to continue building the certificate chain.
//  If the PP returns FALSE, it is assumed that we have reached a "TRUSTED",
//  self-signed, root.
//
typedef BOOL        (*PFN_PROVIDER_CERTCHKPOLICY_CALL)( IN          struct _CRYPT_PROVIDER_DATA *pProvData, 
                                                        IN          DWORD idxSigner,
                                                        IN          BOOL fCounterSignerChain,
                                                        IN OPTIONAL DWORD idxCounterSigner);

#pragma pack(8)

//////////////////////////////////////////////////////////////////////////////
//
// CRYPT_PROVIDER_FUNCTIONS structure
//----------------------------------------------------------------------------
//
//
typedef struct _CRYPT_PROVIDER_FUNCTIONS
{
    DWORD                               cbStruct;

    PFN_CPD_MEM_ALLOC                   pfnAlloc;               // set in WVT
    PFN_CPD_MEM_FREE                    pfnFree;                // set in WVT

    PFN_CPD_ADD_STORE                   pfnAddStore2Chain;      // call to add a store to the chain.
    PFN_CPD_ADD_SGNR                    pfnAddSgnr2Chain;       // call to add a sgnr struct to a msg struct sgnr chain
    PFN_CPD_ADD_CERT                    pfnAddCert2Chain;       // call to add a cert struct to a sgnr struct cert chain
    PFN_CPD_ADD_PRIVDATA                pfnAddPrivData2Chain;   // call to add provider private data to struct.

    PFN_PROVIDER_INIT_CALL              pfnInitialize;          // initialize Policy data.
    PFN_PROVIDER_OBJTRUST_CALL          pfnObjectTrust;         // build info up to the signer info(s).
    PFN_PROVIDER_SIGTRUST_CALL          pfnSignatureTrust;      // build info to the signing cert
    PFN_PROVIDER_CERTTRUST_CALL         pfnCertificateTrust;    // build the chain
    PFN_PROVIDER_FINALPOLICY_CALL       pfnFinalPolicy;         // final call to policy
    PFN_PROVIDER_CERTCHKPOLICY_CALL     pfnCertCheckPolicy;     // check each cert will building chain
    PFN_PROVIDER_TESTFINALPOLICY_CALL   pfnTestFinalPolicy;     // dump structures to a file (or whatever the policy chooses)

} CRYPT_PROVIDER_FUNCTIONS, *PCRYPT_PROVIDER_FUNCTIONS;

//////////////////////////////////////////////////////////////////////////////
//
// CRYPT_PROVIDER_CERT structure
//----------------------------------------------------------------------------
//  After the Signature and Certificate Providers are finished there will 
//  be zero to many of these filled out in the CRYPT_PROVIDER_SGNR 
//  structure.  One for each certificate in the chain.
//  
//
typedef struct _CRYPT_PROVIDER_CERT
{
    DWORD                       cbStruct;

    PCCERT_CONTEXT              pCert;              // must have its own ref-count!

    BOOL                        fCommercial;
    BOOL                        fTrustedRoot;       // certchk policy should set this.
    BOOL                        fSelfSigned;        // set in cert provider

    BOOL                        fTestCert;          // certchk policy will set

    DWORD                       dwRevokedReason;

    DWORD                       dwConfidence;       // set in the Certificate Provider
#                                   define  CERT_CONFIDENCE_SIG          0x10000000
#                                   define  CERT_CONFIDENCE_TIME         0x01000000
#                                   define  CERT_CONFIDENCE_TIMENEST     0x00100000
#                                   define  CERT_CONFIDENCE_AUTHIDEXT    0x00010000
#                                   define  CERT_CONFIDENCE_HIGHEST      0x11110000

    DWORD                       dwError;

} CRYPT_PROVIDER_CERT, *PCRYPT_PROVIDER_CERT;

//////////////////////////////////////////////////////////////////////////////
//
// CRYPT_PROVIDER_SGNR structure
//----------------------------------------------------------------------------
//  After the Signature Provider is finished there will be zero to many of these
//  filled out.  One for each signer of the message.  Also, there will be zero 
//  to many of these filled out inside this structure.  One for each counter 
//  signer of the signer.
//  
//  IMPORTANT:  1.  All dynamically allocated members MUST use allocation
//                  and Add2 functions provided.
//
typedef struct _CRYPT_PROVIDER_SGNR
{
    DWORD                       cbStruct;

    FILETIME                    sftVerifyAsOf;      // either today's filetime or the timestamps

    DWORD                       csCertChain;        // do NOT set manually.
    CRYPT_PROVIDER_CERT         *pasCertChain;      // use the Add2 allocator

    DWORD                       dwSignerType;       // set if known by policy
#                                   define  SGNR_TYPE_TIMESTAMP     0x00000010

    CMSG_SIGNER_INFO            *psSigner;          // must use the pfnAlloc allocator!

    DWORD                       dwError;            // error encounted while building/verifying the signer.

    DWORD                       csCounterSigners;   // do NOT set manually.
    struct _CRYPT_PROVIDER_SGNR *pasCounterSigners; // use the Add2 allocator.

} CRYPT_PROVIDER_SGNR, *PCRYPT_PROVIDER_SGNR;

//////////////////////////////////////////////////////////////////////////////
//
// CRYPT_PROVIDER_PRIVDATA structure
//----------------------------------------------------------------------------
//  This structure is to allow Policy Provider functions to share
//  POLICY SPECIFIC data between Policy Functions.
//  The Policy must use the pfnAddPrivateData2Chain function and 
//  must free any data within the member before the Final Policy returns
//  to WVT.  
//  To allow multiple providers to use this feature, each provider that
//  uses this member must set the provider ID to it's Action ID so that 
//  the provider can find its data and ignore any other.
//
typedef struct _CRYPT_PROVIDER_PRIVDATA
{
    DWORD                           cbStruct;

    GUID                            gProviderID;

    DWORD                           cbProvData;
    void                            *pvProvData;

} CRYPT_PROVIDER_PRIVDATA, *PCRYPT_PROVIDER_PRIVDATA;

//////////////////////////////////////////////////////////////////////////////
//
// CRYPT_PROVIDER_DATA Structure
//----------------------------------------------------------------------------
//  Used to pass information between WinVerifyTrust and all of the Provider
//  calls.
//
//  IMPORTANT:  1.  All dynamically allocated members MUST use the allocation
//                  and Add2 functions provided.
//
typedef struct _CRYPT_PROVIDER_DATA
{
    DWORD                       cbStruct;               // = sizeof(TRUST_PROVIDER_DATA) (set in WVT)

    WINTRUST_DATA               *pWintrustData;         // NOT verified (set in WVT)
    BOOL                        fOpenedFile;            // the provider opened the file handle (if applicable)
    HWND                        hWndParent;             // if passed in, else, Desktop hWnd (set in WVT).
    GUID                        *pgActionID;            // represents the Provider combination (set in WVT).

    HCRYPTPROV                  hProv;                  // set in WVT

    DWORD                       dwError;                // error to be returned

    DWORD                       dwRegSecuritySettings;  // ie security settings (set in WVT)
    DWORD                       dwRegPolicySettings;    // setreg settings (set in WVT)

    CRYPT_PROVIDER_FUNCTIONS    sPfns;                  // set in WVT.

    DWORD                       cdwTrustStepErrors;     // set in WVT.
    DWORD                       *padwTrustStepErrors;   // allocated in WVT.  filled in WVT & Trust Provider

    DWORD                       chStores;               // number of stores in pahStores (root set in WVT)
    HCERTSTORE                  *pahStores;             // array of known stores (root set in WVT) root is ALWAYS #0!!!

    DWORD                       dwEncoding;             // message encoding type (set in WVT and Signature Prov)
    HCRYPTMSG                   hMsg;                   // set in Signature Prov.

    GUID                        gSubject;               // subject guid of file/member file. (set in Sig Prov)
    struct SIP_DISPATCH_INFO_   *pSip;                  // set in Sig Prov - defined in sipbase.h
    struct SIP_DISPATCH_INFO_   *pCATSip;               // set in Sig Prov - defined in sipbase.h
    struct SIP_SUBJECTINFO_     *psSipSubjectInfo;      // set in Sig Prov - defined in sipbase.h
    struct SIP_SUBJECTINFO_     *psSipCATSubjectInfo;   // set in Sig Prov - defined in sipbase.h
    struct SIP_INDIRECT_DATA_   *psIndirectData;        // set in Sig Prov - defined in sipbase.h

    DWORD                       csSigners;              // use Add2 function!
    CRYPT_PROVIDER_SGNR         *pasSigners;            // use Add2 function!

    DWORD                       csProvPrivData;         // use Add2 function!
    CRYPT_PROVIDER_PRIVDATA     *pasProvPrivData;       // use Add2 function!

} CRYPT_PROVIDER_DATA, *PCRYPT_PROVIDER_DATA;


//////////////////////////////////////////////////////////////////////////////
//
// structures used to register action IDs
//----------------------------------------------------------------------------
//
typedef struct _CRYPT_TRUST_REG_ENTRY
{
    DWORD                   cbStruct;

    WCHAR                   *pwszDLLName;
    WCHAR                   *pwszFunctionName;

} CRYPT_TRUST_REG_ENTRY, *PCRYPT_TRUST_REG_ENTRY;

typedef struct _CRYPT_REGISTER_ACTIONID
{
    DWORD                   cbStruct;

    CRYPT_TRUST_REG_ENTRY   sInitProvider;
    CRYPT_TRUST_REG_ENTRY   sObjectProvider;
    CRYPT_TRUST_REG_ENTRY   sSignatureProvider;
    CRYPT_TRUST_REG_ENTRY   sCertificateProvider;
    CRYPT_TRUST_REG_ENTRY   sCertificatePolicyProvider;
    CRYPT_TRUST_REG_ENTRY   sFinalPolicyProvider;
    CRYPT_TRUST_REG_ENTRY   sTestPolicyProvider;

} CRYPT_REGISTER_ACTIONID, *PCRYPT_REGISTER_ACTIONID;

#pragma pack()

//////////////////////////////////////////////////////////////////////////////
//
// WINTRUST.DLL Provider defines
//----------------------------------------------------------------------------
//  The following are definitions of the Microsoft Generic Cert Provider
//  
#define WT_CURRENT_VERSION                  0x00000200
#define WT_MAX_FUNC_NAME                    128

#define WT_PROVIDER_DLL_NAME                L"WINTRUST.DLL"
#define WT_PROVIDER_CERTTRUST_FUNCTION      L"WintrustCertificateTrust"

//////////////////////////////////////////////////////////////////////////////
//
// WintrustAddActionID
//----------------------------------------------------------------------------
//  Adds a new Provider combination to the users' 
//  system.  Creates all necessary registry entries, etc.  This should be done
//  during the Policy Provider's DllRegisterServer.
//
//  *** THE ONLY ONE WHO SHOULD CALL THIS IS THE POLICY PROVIDER ***
// 
// Returns: 
//      TRUE:                           No fatal errors
//      FALSE:                          Errors occured.  See GetLastError()
//
extern BOOL WINAPI  WintrustAddActionID(IN GUID *pgActionID, 
                                        IN DWORD fdwReserved,    // future use.
                                        IN CRYPT_REGISTER_ACTIONID *psProvInfo);


//////////////////////////////////////////////////////////////////////////////
//
// WintrustRemoveActionID
//----------------------------------------------------------------------------
//  Removes the Provider action combination from the users'
//  system.
// 
// Returns: 
//      TRUE:                           No fatal errors
//      FALSE:                          Errors occured.  See GetLastError()
//
extern BOOL WINAPI  WintrustRemoveActionID(IN GUID *pgActionID);

//////////////////////////////////////////////////////////////////////////////
//
// WintrustLoadFunctionPointers
//----------------------------------------------------------------------------
//  Retrieves the function entry points based on the Action ID given.
// 
// Returns: 
//      TRUE                            success.
//      FALSE                           fail.
//
extern BOOL WINAPI WintrustLoadFunctionPointers(GUID *pgActionID, CRYPT_PROVIDER_FUNCTIONS *pPfns);

//
//  helper functions exported from wintrust.dll
//
extern HANDLE WINAPI            WTHelperGetFileHandle(WINTRUST_DATA *pWintrustData);
extern WCHAR * WINAPI           WTHelperGetFileName(WINTRUST_DATA *pWintrustData);
extern PCCERT_CONTEXT WINAPI    WTHelperCertFindIssuerCertificate(CRYPT_PROVIDER_DATA *pProvData, 
                                                                  CRYPT_PROVIDER_SGNR *pSgnr,
                                                                  PCCERT_CONTEXT pChildContext,
                                                                  DWORD *pdwConfidence,
                                                                  DWORD *pdwError);
extern BOOL WINAPI              WTHelperCertIsSelfSigned(DWORD dwEncoding, CERT_INFO *pCert);
extern BOOL WINAPI              WTHelperOpenKnownStores(CRYPT_PROVIDER_DATA *pProvData);


#endif // WINTRUST_H
