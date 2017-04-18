/*++

Copyright (c) 1997-1998 Microsoft Corporation

Module Name:

    sslsock.h

Abstract:

    WinSock SSL external function prototypes and data declarations.

--*/

#ifndef __SSLSOCK_H__
#define __SSLSOCK_H__

#ifdef __cplusplus
extern "C" {
#endif

//
// SSL PROVIDER_INFO security protocol tag
//

#define SECURITY_PROTOCOL_SSL           0x0001

//
// SSL WSAIoctl control code tags
//

#define SO_SSL_FAMILY                   0x00730000
#define SO_SSL_FAMILY_MASK              0x07ff0000

#define _SO_SSL                         ((2L << 27) | SO_SSL_FAMILY)

// Base SSL WSAIoctl tags
#define _SO_SSL_CAPABILITIES            0x01
#define _SO_SSL_FLAGS                   0x02
#define _SO_SSL_PROTOCOLS               0x03
#define _SO_SSL_CIPHERS                 0x04
#define _SO_SSL_CLIENT_OPTS             0x05
#define _SO_SSL_SERVER_OPTS             0x06
#define _SO_SSL_CLIENT_AUTH_OPTS        0x07
#define _SO_SSL_VALIDATE_CERT_HOOK      0x08
#define _SO_SSL_AUTH_REQUEST_HOOK       0x09
#define _SO_SSL_KEY_EXCH_HOOK           0x0a
#define _SO_SSL_SIGNATURE_HOOK          0x0b
#define _SO_SSL_PERFORM_HANDSHAKE       0x0d
#define _SO_SSL_CONNECTION_INFO         0x0e

// Actual SSL WSAIoctl commands
#define SO_SSL_GET_CAPABILITIES         (IOC_OUT | _SO_SSL | _SO_SSL_CAPABILITIES)
#define SO_SSL_SET_FLAGS                (IOC_IN  | _SO_SSL | _SO_SSL_FLAGS)
#define SO_SSL_GET_FLAGS                (IOC_OUT | _SO_SSL | _SO_SSL_FLAGS)
#define SO_SSL_SET_PROTOCOLS            (IOC_IN  | _SO_SSL | _SO_SSL_PROTOCOLS)
#define SO_SSL_GET_PROTOCOLS            (IOC_OUT | _SO_SSL | _SO_SSL_PROTOCOLS)
#define SO_SSL_SET_CIPHERS              (IOC_IN  | _SO_SSL | _SO_SSL_CIPHERS)
#define SO_SSL_GET_CIPHERS              (IOC_OUT | IOC_IN | _SO_SSL | _SO_SSL_CIPHERS)
#define SO_SSL_SET_CLIENT_OPTS          (IOC_IN  | _SO_SSL | _SO_SSL_CLIENT_OPTS)
#define SO_SSL_GET_CLIENT_OPTS          (IOC_OUT | _SO_SSL | _SO_SSL_CLIENT_OPTS)
#define SO_SSL_SET_SERVER_OPTS          (IOC_IN  | _SO_SSL | _SO_SSL_SERVER_OPTS)
#define SO_SSL_GET_SERVER_OPTS          (IOC_OUT | _SO_SSL | _SO_SSL_SERVER_OPTS)
#define SO_SSL_SET_CLIENT_AUTH_OPTS     (IOC_IN  | _SO_SSL | _SO_SSL_CLIENT_AUTH_OPTS)
#define SO_SSL_GET_CLIENT_AUTH_OPTS     (IOC_OUT | _SO_SSL | _SO_SSL_CLIENT_AUTH_OPTS)
#define SO_SSL_SET_VALIDATE_CERT_HOOK   (IOC_IN  | _SO_SSL | _SO_SSL_VALIDATE_CERT_HOOK)
#define SO_SSL_GET_VALIDATE_CERT_HOOK   (IOC_OUT | _SO_SSL | _SO_SSL_VALIDATE_CERT_HOOK)
#define SO_SSL_SET_AUTH_REQUEST_HOOK    (IOC_IN  | _SO_SSL | _SO_SSL_AUTH_REQUEST_HOOK)
#define SO_SSL_GET_AUTH_REQUEST_HOOK    (IOC_OUT | _SO_SSL | _SO_SSL_AUTH_REQUEST_HOOK)
#define SO_SSL_SET_KEY_EXCH_HOOK        (IOC_IN  | _SO_SSL | _SO_SSL_KEY_EXCH_HOOK)
#define SO_SSL_GET_KEY_EXCH_HOOK        (IOC_OUT | _SO_SSL | _SO_SSL_KEY_EXCH_HOOK)
#define SO_SSL_SET_SIGNATURE_HOOK       (IOC_IN  | _SO_SSL | _SO_SSL_SIGNATURE_HOOK)
#define SO_SSL_GET_SIGNATURE_HOOK       (IOC_OUT | _SO_SSL | _SO_SSL_SIGNATURE_HOOK)
#define SO_SSL_PERFORM_HANDSHAKE        (          _SO_SSL | _SO_SSL_PERFORM_HANDSHAKE)
#define SO_SSL_GET_CONNECTION_INFO      (IOC_OUT | _SO_SSL | _SO_SSL_CONNECTION_INFO)

//
// Error codes to be returned by the hook functions.
//

#define SSL_ERR_OKAY            0
#define SSL_ERR_FAILED          2
#define SSL_ERR_BAD_LEN         3
#define SSL_ERR_BAD_TYPE        4
#define SSL_ERR_BAD_DATA        5
#define SSL_ERR_NO_CERT         6
#define SSL_ERR_BAD_SIG         7
#define SSL_ERR_CERT_EXPIRED    8
#define SSL_ERR_CERT_REVOKED    9
#define SSL_ERR_CERT_UNKNOWN    10
#define SSL_ERR_SIGNATURE       11

//
// Definition copied from <winsock2.h>.
//

#ifndef _tagBLOB_DEFINED
#define _tagBLOB_DEFINED
#define _BLOB_DEFINED
#define _LPBLOB_DEFINED
typedef struct _BLOB {
    ULONG cbSize ;
#ifdef MIDL_PASS
    [size_is(cbSize)] BYTE *pBlobData;
#else  /* MIDL_PASS */
    BYTE *pBlobData ;
#endif /* MIDL_PASS */
} BLOB, *LPBLOB ;
#endif

//
// Declarations for _SO_SSL_CAPABILITIES
//

#define SSL_CAP_CLIENT          0x0001
#define SSL_CAP_SERVER          0x0002
#define SSL_CAP_CLIENT_AUTH     0x0004
#define SSL_CAP_CRYPTOAPI       0x0008

//
// Declarations for _SO_SSL_FLAGS
//

// Provider option flags.
#define SSL_FLAG_SERVER          0x0002
#define SSL_FLAG_AUTH_CLIENT     0x0004
#define SSL_FLAG_DEFER_HANDSHAKE 0x0008

//
// Declarations for _SO_SSL_PROTOCOLS
//

#define SSL_PROTOCOL_PCT1       1
#define SSL_PROTOCOL_SSL2       2
#define SSL_PROTOCOL_SSL3       3

typedef struct _SSLPROTOCOL {
    DWORD dwProtocol;
    DWORD dwVersion;
    DWORD dwFlags;
} SSLPROTOCOL, FAR *LPSSLPROTOCOL;

typedef struct _SSLPROTOCOLS {
    DWORD dwCount;
    SSLPROTOCOL ProtocolList[1];   // array of 'count' structures
} SSLPROTOCOLS, FAR *LPSSLPROTOCOLS;

//
// Declarations for _SO_SSL_CIPHERS
//

typedef struct _SSLCIPHERS {
    DWORD dwProtocol;
    DWORD dwCount;
    DWORD CipherList[1];             // array of 'count' integers
} SSLCIPHERS, FAR *LPSSLCIPHERS;

//
// Declarations for _SO_SSL_CLIENT_OPTS
//

typedef struct _SSLCLIENTOPTS {
    time_t CacheTimeout;
    DWORD  dwCacheEntries;
    DWORD  dwFlags;
} SSLCLIENTOPTS, FAR *LPSSLCLIENTOPTS;

//
// Declarations for _SO_SSL_SERVER_OPTS
//

typedef struct _SSLSERVEROPTS {
    time_t CacheTimeout;
    DWORD  dwCacheEntries;
    DWORD  dwFlags;
} SSLSERVEROPTS, FAR *LPSSLSERVEROPTS;

//
// Declarations for _SO_SSL_CLIENT_AUTH_OPTS
//

typedef struct _SSLCLIENTAUTHOPTS {
    DWORD  dwRequestClientAuth;
    DWORD  dwRedoHandshake;
    DWORD  dwType;
    DWORD  dwIssuerCount;
    LPBLOB pIssuerList;
    DWORD  dwFlags;
} SSLCLIENTAUTHOPTS, FAR *LPSSLCLIENTAUTHOPTS;

//
// Declarations for _SO_SSL_VALIDATE_CERT_HOOK
//

#define SSL_CERT_X509       0x0001
#define SSL_CERT_FLAG_ISSUER_UNKNOWN 0x0001

typedef int (CALLBACK FAR *SSLVALIDATECERTFUNC)(
    DWORD  dwType,          // in
    LPVOID pvArg,           // in
    DWORD  dwChainLen,      // in
    LPBLOB pCertChain,      // in
    DWORD dwFlags);         // in

typedef struct _SSLVALIDATECERTHOOK {
    SSLVALIDATECERTFUNC HookFunc;
    LPVOID pvArg;
} SSLVALIDATECERTHOOK, FAR *LPSSLVALIDATECERTHOOK;

//
// Declarations for _SO_SSL_AUTH_REQUEST_HOOK
//

typedef int (CALLBACK FAR *SSLAUTHREQUESTFUNC)(
    DWORD         dwType,           // in
    LPVOID        pvArg,            // in
    DWORD         dwIssuerCount,    // in
    LPBLOB        pIssuerList,      // in
    DWORD         dwFlags,          // in
    LPDWORD       pdwChainLen,      // out
    LPBLOB        *ppCertChain);    // out

typedef struct _SSLAUTHREQUESTHOOK {
    SSLAUTHREQUESTFUNC HookFunc;
    LPVOID pvArg;
} SSLAUTHREQUESTHOOK, FAR *LPSSLAUTHREQUESTHOOK;

//
// Declarations for _SO_SSL_KEY_EXCH_HOOK
//

#define SSL_EXCH_RSAENCRYPT   1
#define SSL_EXCH_RSADECRYPT   2

typedef int (CALLBACK FAR *SSLKEYEXCHANGEFUNC)(
    DWORD   dwType,           // in
    LPVOID  pvArg,            // in
    LPBYTE  pSource,          // in
    DWORD   dwSourceLen,      // in
    DWORD   dwFlags,          // in
    LPBYTE  pDest,            // out
    LPDWORD pdwDestLen);      // in, out

typedef struct _SSLKEYEXCHANGEHOOK {
    SSLKEYEXCHANGEFUNC HookFunc;
    LPVOID pvArg;
} SSLKEYEXCHANGEHOOK, FAR *LPSSLKEYEXCHANGEHOOK;

//
// Declarations for _SO_SSL_SIGNATURE_HOOK
//

// Values for 'dwType'.
#define SSL_SIGN_RSA_MD2    1
#define SSL_SIGN_RSA_MD5    2
#define SSL_SIGN_RSA_SHA    3
#define SSL_SIGN_RSA_SHAMD5 4

// Values for 'dwFlags'.
#define SSL_SIGN_VERIFY_SIGNATURE   0x00000001
#define SSL_SIGN_PERFORM_HASH       0x00000002

typedef int (CALLBACK FAR *SSLSIGNATUREFUNC)(
    DWORD   dwType,           // in
    LPVOID  pvArg,            // in
    LPBYTE  pSource,          // in
    DWORD   dwSourceLen,      // in
    DWORD   dwFlags,          // in
    LPBYTE  pDest,            // out
    LPDWORD pdwDestLen);      // in, out

typedef struct _SSLSIGNATUREHOOK {
    SSLSIGNATUREFUNC HookFunc;
    LPVOID pvArg;
} SSLSIGNATUREHOOK, FAR *LPSSLSIGNATUREHOOK;

//
// ALG_ID definitions.
//

#ifndef ALGIDDEF

#define ALGIDDEF
typedef unsigned int ALG_ID;

// ALG_ID crackers
#define GET_ALG_CLASS(x)                (x & (7 << 13))
#define GET_ALG_TYPE(x)                 (x & (15 << 9))
#define GET_ALG_SID(x)                  (x & (511))

// Algorithm classes
#define ALG_CLASS_ANY                   (0)
#define ALG_CLASS_SIGNATURE             (1 << 13)
#define ALG_CLASS_MSG_ENCRYPT           (2 << 13)
#define ALG_CLASS_DATA_ENCRYPT          (3 << 13)
#define ALG_CLASS_HASH                  (4 << 13)
#define ALG_CLASS_KEY_EXCHANGE          (5 << 13)

// Algorithm types
#define ALG_TYPE_ANY                    (0)
#define ALG_TYPE_DSS                    (1 << 9)
#define ALG_TYPE_RSA                    (2 << 9)
#define ALG_TYPE_BLOCK                  (3 << 9)
#define ALG_TYPE_STREAM                 (4 << 9)
#define ALG_TYPE_DH                     (5 << 9)
#define ALG_TYPE_SECURECHANNEL          (6 << 9)

// Generic sub-ids
#define ALG_SID_ANY                     (0)

// Some RSA sub-ids
#define ALG_SID_RSA_ANY                 0
#define ALG_SID_RSA_PKCS                1
#define ALG_SID_RSA_MSATWORK            2
#define ALG_SID_RSA_ENTRUST             3
#define ALG_SID_RSA_PGP                 4

// Some DSS sub-ids
//
#define ALG_SID_DSS_ANY                 0
#define ALG_SID_DSS_PKCS                1
#define ALG_SID_DSS_DMS                 2

// Block cipher sub ids
// DES sub_ids
#define ALG_SID_DES                     1
#define ALG_SID_3DES                    3
#define ALG_SID_DESX                    4
#define ALG_SID_IDEA                    5
#define ALG_SID_CAST                    6
#define ALG_SID_SAFERSK64               7
#define ALD_SID_SAFERSK128              8
#define ALG_SID_3DES_112                9
#define ALG_SID_CYLINK_MEK              12

// Fortezza sub-ids
#define ALG_SID_SKIPJACK                10
#define ALG_SID_TEK                     11

// RC2 sub-ids
#define ALG_SID_RC2                     2

// Stream cipher sub-ids
#define ALG_SID_RC4                     1
#define ALG_SID_SEAL                    2

// Diffie-Hellman sub-ids
#define ALG_SID_DH_SANDF                1
#define ALG_SID_DH_EPHEM                2
#define ALG_SID_AGREED_KEY_ANY          3
#define ALG_SID_KEA                     4

// Hash sub ids
#define ALG_SID_MD2                     1
#define ALG_SID_MD4                     2
#define ALG_SID_MD5                     3
#define ALG_SID_SHA                     4
#define ALG_SID_SHA1                    4
#define ALG_SID_MAC                     5
#define ALG_SID_RIPEMD                  6
#define ALG_SID_RIPEMD160               7
#define ALG_SID_SSL3SHAMD5              8

// secure channel sub ids
#define ALG_SID_SSL3_MASTER             1
#define ALG_SID_SCHANNEL_MASTER_HASH    2
#define ALG_SID_SCHANNEL_MAC_KEY        3
#define ALG_SID_PCT1_MASTER             4
#define ALG_SID_SSL2_MASTER             5
#define ALG_SID_TLS1_MASTER             6
#define ALG_SID_SCHANNEL_ENC_KEY        7

// Our silly example sub-id
#define ALG_SID_EXAMPLE                 80

// algorithm identifier definitions
#define CALG_MD2                (ALG_CLASS_HASH | ALG_TYPE_ANY | ALG_SID_MD2)
#define CALG_MD4                (ALG_CLASS_HASH | ALG_TYPE_ANY | ALG_SID_MD4)
#define CALG_MD5                (ALG_CLASS_HASH | ALG_TYPE_ANY | ALG_SID_MD5)
#define CALG_SHA                (ALG_CLASS_HASH | ALG_TYPE_ANY | ALG_SID_SHA)
#define CALG_SHA1               (ALG_CLASS_HASH | ALG_TYPE_ANY | ALG_SID_SHA1)
#define CALG_MAC                (ALG_CLASS_HASH | ALG_TYPE_ANY | ALG_SID_MAC)
#define CALG_RSA_SIGN           (ALG_CLASS_SIGNATURE | ALG_TYPE_RSA | ALG_SID_RSA_ANY)
#define CALG_DSS_SIGN           (ALG_CLASS_SIGNATURE | ALG_TYPE_DSS | ALG_SID_DSS_ANY)
#define CALG_RSA_KEYX           (ALG_CLASS_KEY_EXCHANGE|ALG_TYPE_RSA|ALG_SID_RSA_ANY)
#define CALG_DES                (ALG_CLASS_DATA_ENCRYPT|ALG_TYPE_BLOCK|ALG_SID_DES)
#define CALG_3DES_112           (ALG_CLASS_DATA_ENCRYPT|ALG_TYPE_BLOCK|ALG_SID_3DES_112)
#define CALG_3DES               (ALG_CLASS_DATA_ENCRYPT|ALG_TYPE_BLOCK|ALG_SID_3DES)
#define CALG_RC2                (ALG_CLASS_DATA_ENCRYPT|ALG_TYPE_BLOCK|ALG_SID_RC2)
#define CALG_RC4                (ALG_CLASS_DATA_ENCRYPT|ALG_TYPE_STREAM|ALG_SID_RC4)
#define CALG_SEAL               (ALG_CLASS_DATA_ENCRYPT|ALG_TYPE_STREAM|ALG_SID_SEAL)
#define CALG_DH_SF              (ALG_CLASS_KEY_EXCHANGE|ALG_TYPE_DH|ALG_SID_DH_SANDF)
#define CALG_DH_EPHEM           (ALG_CLASS_KEY_EXCHANGE|ALG_TYPE_DH|ALG_SID_DH_EPHEM)
#define CALG_AGREEDKEY_ANY      (ALG_CLASS_KEY_EXCHANGE|ALG_TYPE_DH|ALG_SID_AGREED_KEY_ANY)
#define CALG_KEA_KEYX           (ALG_CLASS_KEY_EXCHANGE|ALG_TYPE_DH|ALG_SID_KEA)
#define CALG_HUGHES_MD5         (ALG_CLASS_KEY_EXCHANGE|ALG_TYPE_ANY|ALG_SID_MD5)
#define CALG_SKIPJACK           (ALG_CLASS_DATA_ENCRYPT|ALG_TYPE_BLOCK|ALG_SID_SKIPJACK)
#define CALG_TEK                (ALG_CLASS_DATA_ENCRYPT|ALG_TYPE_BLOCK|ALG_SID_TEK)
#define CALG_CYLINK_MEK         (ALG_CLASS_DATA_ENCRYPT|ALG_TYPE_BLOCK|ALG_SID_CYLINK_MEK)
#define CALG_SSL3_SHAMD5        (ALG_CLASS_HASH | ALG_TYPE_ANY | ALG_SID_SSL3SHAMD5)
#define CALG_SSL3_MASTER        (ALG_CLASS_MSG_ENCRYPT|ALG_TYPE_SECURECHANNEL|ALG_SID_SSL3_MASTER)
#define CALG_SCHANNEL_MASTER_HASH   (ALG_CLASS_MSG_ENCRYPT|ALG_TYPE_SECURECHANNEL|ALG_SID_SCHANNEL_MASTER_HASH)
#define CALG_SCHANNEL_MAC_KEY   (ALG_CLASS_MSG_ENCRYPT|ALG_TYPE_SECURECHANNEL|ALG_SID_SCHANNEL_MAC_KEY)
#define CALG_SCHANNEL_ENC_KEY   (ALG_CLASS_MSG_ENCRYPT|ALG_TYPE_SECURECHANNEL|ALG_SID_SCHANNEL_ENC_KEY)
#define CALG_PCT1_MASTER        (ALG_CLASS_MSG_ENCRYPT|ALG_TYPE_SECURECHANNEL|ALG_SID_PCT1_MASTER)
#define CALG_SSL2_MASTER        (ALG_CLASS_MSG_ENCRYPT|ALG_TYPE_SECURECHANNEL|ALG_SID_SSL2_MASTER)
#define CALG_TLS1_MASTER        (ALG_CLASS_MSG_ENCRYPT|ALG_TYPE_SECURECHANNEL|ALG_SID_TLS1_MASTER)

#endif // !ALGIDDEF

//
// Declarations for _SO_SSL_GET_CONNECTION_INFO
//

typedef struct _SSLCONNECTIONINFO
{
    DWORD   dwProtocol;
    ALG_ID  aiCipher;
    DWORD   dwCipherStrength;
    ALG_ID  aiHash;
    DWORD   dwHashStrength;
    ALG_ID  aiExch;
    DWORD   dwExchStrength;
} SSLCONNECTIONINFO, FAR *PSSLCONNECTIONINFO;

//
// dwProtocol bit array values.
//

#define SSL_PROT_PCT1_SERVER        0x00000001
#define SSL_PROT_PCT1_CLIENT        0x00000002
#define SSL_PROT_SSL2_SERVER        0x00000004
#define SSL_PROT_SSL2_CLIENT        0x00000008
#define SSL_PROT_SSL3_SERVER        0x00000010
#define SSL_PROT_SSL3_CLIENT        0x00000020

#ifdef __cplusplus
}
#endif

#endif //__SSLSOCK_H__
