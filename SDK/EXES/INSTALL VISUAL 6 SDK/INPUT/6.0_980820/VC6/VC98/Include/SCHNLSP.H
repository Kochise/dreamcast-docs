//+---------------------------------------------------------------------------
//
//  Microsoft Windows
//  Copyright 1992 - 1998 Microsoft Corporation.
//
//  File:       schnlsp.h
//
//  Contents:   Public Definitions for SCHANNEL Security Provider
//
//  Classes:
//
//  Functions:
//
//  History:    6-8-96   Created
//
//----------------------------------------------------------------------------

#ifndef __SCHNLSP_H__
#define __SCHNLSP_H__

#include <wincrypt.h>


#define UNISP_NAME_A    "Microsoft Unified Security Protocol Provider"
#define UNISP_NAME_W    L"Microsoft Unified Security Protocol Provider"

#define SSL2SP_NAME_A    "Microsoft SSL 2.0"
#define SSL2SP_NAME_W    L"Microsoft SSL 2.0"

#define SSL3SP_NAME_A    "Microsoft SSL 3.0"
#define SSL3SP_NAME_W    L"Microsoft SSL 3.0"

#define TLS1SP_NAME_A    "Microsoft TLS 1.0"
#define TLS1SP_NAME_W    L"Microsoft TLS 1.0"

#define PCT1SP_NAME_A    "Microsoft PCT 1.0"
#define PCT1SP_NAME_W    L"Microsoft PCT 1.0"


#ifdef UNICODE

#define UNISP_NAME  UNISP_NAME_W
#define PCT1SP_NAME  PCT1SP_NAME_W
#define SSL2SP_NAME  SSL2SP_NAME_W
#define SSL3SP_NAME  SSL3SP_NAME_W
#define TLS1SP_NAME  TLS1SP_NAME_W

#else

#define UNISP_NAME  UNISP_NAME_A
#define PCT1SP_NAME  PCT1SP_NAME_A
#define SSL2SP_NAME  SSL2SP_NAME_A
#define SSL3SP_NAME  SSL3SP_NAME_A
#define TLS1SP_NAME  TLS1SP_NAME_A

#endif

#define SSL2SP_RPC_ID    12
#define PCT1SP_RPC_ID    13
#define SSL3SP_RPC_ID    14
#define UNISP_RPC_ID     15
#define TLS1SP_RPC_ID    16



#define SCH_CRED_V1              0x00000001
#define SCH_CRED_V2              0x00000002  // for legacy code
#define SCH_CRED_VERSION         0x00000002  // for legacy code
#define SCHANNEL_CRED_VERSION    0x00000003




//
// QueryContextAttributes/QueryCredentialsAttribute extensions
//
#define SECPKG_ATTR_REMOTE_CERT_CONTEXT  0x53  // returns PCCERT_CONTEXT
#define SECPKG_ATTR_LOCAL_CERT_CONTEXT   0x54  // returns PCCERT_CONTEXT
#define SECPKG_ATTR_ROOT_STORE           0x55  // returns HCERTCONTEXT to the root store
#define SECPKG_ATTR_SUPPORTED_ALGS       0x56  // returns SecPkgCred_SupportedAlgs
#define SECPKG_ATTR_CIPHER_STRENGTHS     0x57  // returns SecPkgCred_CipherStrengths
#define SECPKG_ATTR_SUPPORTED_PROTOCOLS  0x58  // returns SecPkgCred_SupportedProtocols
#define SECPKG_ATTR_ISSUER_LIST_EX       0x59  // returns SecPkgContext_IssuerListInfoEx
#define SECPKG_ATTR_CONNECTION_INFO      0x5a  // returns SecPkgContext_ConnectionInfo



typedef struct _SecPkgCred_SupportedAlgs
{
    DWORD		cSupportedAlgs;
    ALG_ID		*palgSupportedAlgs;
} SecPkgCred_SupportedAlgs, *PSecPkgCred_SupportedAlgs;

typedef struct _SecPkgCred_CipherStrengths
{
    DWORD       dwMinimumCipherStrength;
    DWORD       dwMaximumCipherStrength;
} SecPkgCred_CipherStrengths, *PSecPkgCred_CipherStrengths;

typedef struct _SecPkgCred_SupportedProtocols
{
    DWORD      	grbitProtocol;
} SecPkgCred_SupportedProtocols, *PSecPkgCred_SupportedProtocols;

typedef struct _SecPkgContext_IssuerListInfoEx
{
    PCERT_NAME_BLOB   	aIssuers;
    DWORD           	cIssuers;
} SecPkgContext_IssuerListInfoEx, *PSecPkgContext_IssuerListInfoEx;

typedef struct _SecPkgContext_ConnectionInfo
{
    DWORD    dwProtocol;
    ALG_ID   aiCipher;
    DWORD    dwCipherStrength;
    ALG_ID   aiHash;
    DWORD    dwHashStrength;
    ALG_ID   aiExch;
    DWORD    dwExchStrength;
}SecPkgContext_ConnectionInfo, *PSecPkgContext_ConnectionInfo;


//
// SCHANNEL Credentials data structure
//
struct _HMAPPER;

typedef struct _SCHANNEL_CRED
{
    DWORD           dwVersion;
    DWORD           cCreds;
    PCCERT_CONTEXT  *paCred; 
    HCERTSTORE      hRootStore;

    DWORD            cMappers;                
    struct _HMAPPER  **aphMappers;     

    DWORD           cSupportedAlgs;
    ALG_ID          *palgSupportedAlgs;

    DWORD           grbitEnabledProtocols;
    DWORD           dwMinimumCipherStrength;
    DWORD           dwMaximumCipherStrength;
    DWORD           dwSessionLifespan;

} SCHANNEL_CRED, *PSCHANNEL_CRED;


// 
//
// ApplyControlToken PkgParams types
//
// These identifiers are the DWORD types
// to be passed into ApplyControlToken
// through a PkgParams buffer.

//
// SCHANNEL_RENEGOTIATE
//
// Cause SCHANNEL to renegotiate 
// a connection.
//
#define SCHANNEL_RENEGOTIATE 0

//
// SCHANNEL_SHUTDOWN
//
// Cause SCHANNEL to shutdown 
// a connection.
//

#define SCHANNEL_SHUTDOWN    1


//
//
// ADDITIONAL SCHANNEL ERROR CODES
//
//


//
// MessageId: SEC_I_INCOMPLETE_CREDENTIALS
//
// MessageText:
//
//  If this is returned from InitializeSecurityContext, it indicates
//  that the credentials supplied were incomplete, and client-auth was
//  attempted.  On receipt, the client should call QueryContextAttributes
//  with SECPKG_ATTR_LOCAL_CERT to get the cert that was negotiated,
//  and the supply the private key with this cert to AcquireCredential
//  to get a new credential.  The context should then be closed, 
//  and renegotiation should be completed.
//  
//
#define SEC_I_INCOMPLETE_CREDENTIALS      ((HRESULT)0x00090320L)

#define SEC_E_INCOMPLETE_CREDENTIALS      ((HRESULT)0x80090320L)


//
// MessageId: SEC_I_RENEGOTIATE
//
// MessageText:
//
// This is returned by UnsealMessage, and indicates that the app should
// restart the renegotiation loop.  It should use the existing context, and
// pass in no data in the input buffers for the first call to AcceptSecurityContext
// or InitializeSecurityContext. 
//
#define SEC_I_RENEGOTIATE            ((HRESULT)0x00090321L)



//
//
// ADDITIONAL SCHANNEL CERTIFICATE PROPERTIES
//
//


// This property specifies the DER private key data associated with this
// certificate.  It is for use with legacy IIS style private keys.
//
// PBYTE
//
#define CERT_SCHANNEL_IIS_PRIVATE_KEY_PROP_ID  (CERT_FIRST_USER_PROP_ID + 0)

// The password used to crack the private key associated with the certificate.
// It is for use with legacy IIS style private keys.
//
// PBYTE
#define CERT_SCHANNEL_IIS_PASSWORD_PROP_ID  (CERT_FIRST_USER_PROP_ID + 1)

// This is the unique ID of a Server Gated Cryptography certificate associated
// with this certificate.
//
// CRYPT_BIT_BLOB
#define CERT_SCHANNEL_SGC_CERTIFICATE_PROP_ID  (CERT_FIRST_USER_PROP_ID + 2)



//
// Flags for identifying the various different protocols.
//

/* flag/identifiers for protocols we support */
#define SP_PROT_PCT1_SERVER             0x00000001
#define SP_PROT_PCT1_CLIENT             0x00000002
#define SP_PROT_PCT1                    (SP_PROT_PCT1_SERVER | SP_PROT_PCT1_CLIENT)

#define SP_PROT_SSL2_SERVER             0x00000004
#define SP_PROT_SSL2_CLIENT             0x00000008
#define SP_PROT_SSL2                    (SP_PROT_SSL2_SERVER | SP_PROT_SSL2_CLIENT)

#define SP_PROT_SSL3_SERVER             0x00000010
#define SP_PROT_SSL3_CLIENT             0x00000020
#define SP_PROT_SSL3                    (SP_PROT_SSL3_SERVER | SP_PROT_SSL3_CLIENT)

#define SP_PROT_TLS1_SERVER             0x00000040
#define SP_PROT_TLS1_CLIENT             0x00000080
#define SP_PROT_TLS1                    (SP_PROT_TLS1_SERVER | SP_PROT_TLS1_CLIENT)

#define SP_PROT_SSL3TLS1_CLIENTS        (SP_PROT_TLS1_CLIENT | SP_PROT_SSL3_CLIENT)
#define SP_PROT_SSL3TLS1_SERVERS        (SP_PROT_TLS1_SERVER | SP_PROT_SSL3_SERVER)
#define SP_PROT_SSL3TLS1                (SP_PROT_SSL3 | SP_PROT_TLS1)

#define SP_PROT_UNI_SERVER              0x40000000
#define SP_PROT_UNI_CLIENT              0x80000000
#define SP_PROT_UNI                     (SP_PROT_UNI_SERVER | SP_PROT_UNI_CLIENT)

#define SP_PROT_ALL                     0xffffffff
#define SP_PROT_ALL_NOT_TLS             (SP_PROT_PCT1 | SP_PROT_SSL2 | SP_PROT_SSL3)
#define SP_PROT_NONE                    0
#define SP_PROT_CLIENTS                 (SP_PROT_PCT1_CLIENT | SP_PROT_SSL2_CLIENT | SP_PROT_SSL3_CLIENT | SP_PROT_UNI_CLIENT | SP_PROT_TLS1_CLIENT)
#define SP_PROT_SERVERS                 (SP_PROT_PCT1_SERVER | SP_PROT_SSL2_SERVER | SP_PROT_SSL3_SERVER | SP_PROT_UNI_SERVER | SP_PROT_TLS1_SERVER)


// A call for IIS to empty the cache.

BOOL
SslEmptyCache(VOID);

//
//
//  Support for legacy applications
//  NOTE: Do not use the following 
//  API's and structures for new code.
//


#define SSLOLD_NAME_A    "Microsoft SSL"
#define SSLOLD_NAME_W    L"Microsoft SSL"
#define PCTOLD_NAME_A    "Microsoft PCT"
#define PCTOLD_NAME_W    L"Microsoft PCT"

#ifdef UNICODE
#define SSLOLD_NAME SSLOLD_NAME_W
#define PCTOLD_NAME PCTOLD_NAME_W
#else
#define SSLOLD_NAME SSLOLD_NAME_A
#define PCTOLD_NAME PCTOLD_NAME_A
#endif

#define NETWORK_DREP    0x00000000



// Structures for compatability with the
// NT 4.0 SP2 / IE 3.0 schannel interface, do
// not use.

typedef struct _SSL_CREDENTIAL_CERTIFICATE {
    DWORD   cbPrivateKey;
    PBYTE   pPrivateKey;
    DWORD   cbCertificate;
    PBYTE   pCertificate;
    PSTR    pszPassword;
} SSL_CREDENTIAL_CERTIFICATE, * PSSL_CREDENTIAL_CERTIFICATE;




// Structures for use with the 
// NT 4.0 SP3 Schannel interface, 
// do not use.
#define SCHANNEL_SECRET_TYPE_CAPI       0x00000001
#define SCHANNEL_SECRET_PRIVKEY         0x00000002
#define SCH_CRED_X509_CERTCHAIN   0x00000001
#define SCH_CRED_X509_CAPI        0x00000002
#define SCH_CRED_CERT_CONTEXT     0x00000003

struct _HMAPPER;
typedef struct _SCH_CRED
{
    DWORD     dwVersion;                // always SCH_CRED_VERSION.
    DWORD     cCreds;                   // Number of credentials.
    PVOID     *paSecret;                // Array of SCH_CRED_SECRET_* pointers
    PVOID     *paPublic;                // Array of SCH_CRED_PUBLIC_* pointers
    DWORD     cMappers;                 // Number of credential mappers.
    struct _HMAPPER   **aphMappers;     // pointer to an array of pointers to credential mappers 
} SCH_CRED, * PSCH_CRED;

// Structures for use with the 
// NT 4.0 SP3 Schannel interface, 
// do not use.
typedef struct _SCH_CRED_SECRET_CAPI
{
    DWORD           dwType;      // SCHANNEL_SECRET_TYPE_CAPI
    HCRYPTPROV      hProv;       // credential secret information.

} SCH_CRED_SECRET_CAPI, * PSCH_CRED_SECRET_CAPI;


// Structures for use with the 
// NT 4.0 SP3 Schannel interface, 
// do not use.
typedef struct _SCH_CRED_SECRET_PRIVKEY
{
    DWORD           dwType;       // SCHANNEL_SECRET_PRIVKEY
    PBYTE           pPrivateKey;   // Der encoded private key
    DWORD           cbPrivateKey;
    PSTR            pszPassword;  // Password to crack the private key.

} SCH_CRED_SECRET_PRIVKEY, * PSCH_CRED_SECRET_PRIVKEY;


// Structures for use with the 
// NT 4.0 SP3 Schannel interface, 
// do not use.
typedef struct _SCH_CRED_PUBLIC_CERTCHAIN
{
    DWORD       dwType;
    DWORD       cbCertChain;
    PBYTE       pCertChain;
} SCH_CRED_PUBLIC_CERTCHAIN, *PSCH_CRED_PUBLIC_CERTCHAIN;

// Structures for use with the 
// NT 4.0 SP3 Schannel interface, 
// do not use.
typedef struct _SCH_CRED_PUBLIC_CAPI
{
    DWORD           dwType;      // SCH_CRED_X509_CAPI
    HCRYPTPROV      hProv;       // CryptoAPI handle (usually a token CSP)

} SCH_CRED_PUBLIC_CAPI, * PSCH_CRED_PUBLIC_CAPI;

// Attributes for getting NON CAPI2 
// certificate blobs.  Use the CAPI2
// attributes defined above instead.
#define SECPKG_ATTR_ISSUER_LIST          0x50  // SecPkgContext_IssuerListInfo
#define SECPKG_ATTR_REMOTE_CRED          0x51  // SecPkgContext_RemoteCredentialInfo
#define SECPKG_ATTR_LOCAL_CRED           0x52  // SecPkgContext_LocalCredentialInfo

// Attributes for getting NON CAPI2 
// certificate blobs.  Use the CAPI2
// attributes defined above instead.
typedef struct _SecPkgContext_IssuerListInfo
{
    DWORD   cbIssuerList;
    PBYTE   pIssuerList;
} SecPkgContext_IssuerListInfo, *PSecPkgContext_IssuerListInfo;

// Attributes for getting NON CAPI2 
// certificate blobs.  Use the CAPI2
// attributes defined above instead.
typedef struct _SecPkgContext_RemoteCredentialInfo
{
    DWORD   cbCertificateChain;     // count of bytes in cert chain buffer.
    PBYTE   pbCertificateChain;     // DER encoded chain of certificates, leaf cert first.
    DWORD   cCertificates;
    DWORD   fFlags;
    DWORD   dwBits;                 // Number of bits in the remote credentials
} SecPkgContext_RemoteCredentialInfo, *PSecPkgContext_RemoteCredentialInfo;

// Make the old spelling error compatable
typedef SecPkgContext_RemoteCredentialInfo SecPkgContext_RemoteCredenitalInfo, *PSecPkgContext_RemoteCredenitalInfo;

// Attributes for getting NON CAPI2 
// certificate blobs.  Use the CAPI2
// attributes defined above instead.
typedef struct _SecPkgContext_LocalCredentialInfo
{
    DWORD   cbCertificateChain;     // count of bytes in cert chain buffer.
    PBYTE   pbCertificateChain;     // DER encoded chain of certificates, leaf cert first.
    DWORD   cCertificates;
    DWORD   fFlags;
    DWORD   dwBits;                 // Number of bits in the remote credentials.
} SecPkgContext_LocalCredentialInfo, *PSecPkgContext_LocalCredentialInfo;

// Make the old spelling error compatable.
typedef SecPkgContext_LocalCredentialInfo SecPkgContext_LocalCredenitalInfo, *PSecPkgContext_LocalCredenitalInfo;
#define RCRED_STATUS_NOCRED          0x00000000
#define RCRED_CRED_EXISTS            0x00000001
#define RCRED_STATUS_UNKNOWN_ISSUER  0x00000002    // The last cert in this chain has 
                                                   // an issuer that is unknown to us.
#define LCRED_STATUS_NOCRED          0x00000000
#define LCRED_CRED_EXISTS            0x00000001
#define LCRED_STATUS_UNKNOWN_ISSUER  0x00000002    // The last cert in this chain has 


// Structures needed for Pre NT4.0 SP2 calls.
typedef struct _PctPublicKey
{
    DWORD Type;
    DWORD cbKey;
    UCHAR pKey[1];
} PctPublicKey;

typedef struct _X509Certificate {
    DWORD           Version;
    DWORD           SerialNumber[4];
    ALG_ID          SignatureAlgorithm;
    FILETIME        ValidFrom;
    FILETIME        ValidUntil;
    PSTR            pszIssuer;
    PSTR            pszSubject;
    PctPublicKey    *pPublicKey;
} X509Certificate, * PX509Certificate;



// Pre NT4.0 SP2 calls.  Call CAPI1 or CAPI2
// to get the same functionality instead.
BOOL
SslGenerateKeyPair(
    PSSL_CREDENTIAL_CERTIFICATE pCerts,
    PSTR pszDN,
    PSTR pszPassword,
    DWORD Bits );

// Pre NT4.0 SP2 calls.  Call CAPI1 or CAPI2
// to get the same functionality instead.
VOID
SslGenerateRandomBits(
    PUCHAR      pRandomData,
    LONG        cRandomData
    );

// Pre NT4.0 SP2 calls.  Call CAPI1 or CAPI2
// to get the same functionality instead.
BOOL
SslCrackCertificate(
    PUCHAR              pbCertificate,
    DWORD               cbCertificate,
    DWORD               dwFlags,
    PX509Certificate *  ppCertificate
    );

// Pre NT4.0 SP2 calls.  Call CAPI1 or CAPI2
// to get the same functionality instead.
VOID
SslFreeCertificate(
    PX509Certificate    pCertificate
    );

// Call QueryCredentialsAttribute instead.
BOOL
SslGetDefaultIssuers(
    PBYTE pbIssuers,
    DWORD *pcbIssuers);


#define SSL_CRACK_CERTIFICATE_NAME  TEXT("SslCrackCertificate")
#define SSL_FREE_CERTIFICATE_NAME   TEXT("SslFreeCertificate")

// Pre NT4.0 SP2 calls.  Call CAPI1 or CAPI2
// to get the same functionality instead.
typedef BOOL
(WINAPI * SSL_CRACK_CERTIFICATE_FN)
(
    PUCHAR              pbCertificate,
    DWORD               cbCertificate,
    BOOL                VerifySignature,
    PX509Certificate *  ppCertificate
);


// Pre NT4.0 SP2 calls.  Call CAPI1 or CAPI2
// to get the same functionality instead.
typedef VOID
(WINAPI * SSL_FREE_CERTIFICATE_FN)
(
    PX509Certificate    pCertificate
);


#endif //__SCHNLSP_H__
