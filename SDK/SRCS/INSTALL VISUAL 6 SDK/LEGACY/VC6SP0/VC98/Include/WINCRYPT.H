//+---------------------------------------------------------------------------
//
//  Microsoft Windows
//  Copyright 1992 - 1998 Microsoft Corporation.
//
//  File:       wincrypt.h
//
//  Contents:   Cryptographic API Prototypes and Definitions
//
//----------------------------------------------------------------------------

#ifndef __WINCRYPT_H__
#define __WINCRYPT_H__


#if(_WIN32_WINNT >= 0x0400)

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _HRESULT_DEFINED
#define _HRESULT_DEFINED
typedef LONG HRESULT;

#endif // !_HRESULT_DEFINED

#if !defined(_CRYPT32_)
#define WINCRYPT32API DECLSPEC_IMPORT
#else
#define WINCRYPT32API
#endif

//
// Algorithm IDs and Flags
//

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
#define ALG_SID_SAFERSK128              8
#define ALG_SID_3DES_112                9
#define ALG_SID_CYLINK_MEK              12
#define ALG_SID_RC5                     13

// Fortezza sub-ids
#define ALG_SID_SKIPJACK                10
#define ALG_SID_TEK                     11

// KP_MODE
#define CRYPT_MODE_CBCI                 6       // ANSI CBC Interleaved
#define CRYPT_MODE_CFBP                 7       // ANSI CFB Pipelined
#define CRYPT_MODE_OFBP                 8       // ANSI OFB Pipelined
#define CRYPT_MODE_CBCOFM               9       // ANSI CBC + OF Masking
#define CRYPT_MODE_CBCOFMI              10      // ANSI CBC + OFM Interleaved

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
#define ALG_SID_HMAC                    9

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

#ifndef ALGIDDEF
#define ALGIDDEF
typedef unsigned int ALG_ID;
#endif

// algorithm identifier definitions
#define CALG_MD2				(ALG_CLASS_HASH | ALG_TYPE_ANY | ALG_SID_MD2)
#define CALG_MD4				(ALG_CLASS_HASH | ALG_TYPE_ANY | ALG_SID_MD4)
#define CALG_MD5				(ALG_CLASS_HASH | ALG_TYPE_ANY | ALG_SID_MD5)
#define CALG_SHA				(ALG_CLASS_HASH | ALG_TYPE_ANY | ALG_SID_SHA)
#define CALG_SHA1				(ALG_CLASS_HASH | ALG_TYPE_ANY | ALG_SID_SHA1)
#define CALG_MAC				(ALG_CLASS_HASH | ALG_TYPE_ANY | ALG_SID_MAC)
#define CALG_RSA_SIGN			(ALG_CLASS_SIGNATURE | ALG_TYPE_RSA | ALG_SID_RSA_ANY)
#define CALG_DSS_SIGN			(ALG_CLASS_SIGNATURE | ALG_TYPE_DSS | ALG_SID_DSS_ANY)
#define CALG_RSA_KEYX			(ALG_CLASS_KEY_EXCHANGE|ALG_TYPE_RSA|ALG_SID_RSA_ANY)
#define CALG_DES				(ALG_CLASS_DATA_ENCRYPT|ALG_TYPE_BLOCK|ALG_SID_DES)
#define CALG_3DES_112			(ALG_CLASS_DATA_ENCRYPT|ALG_TYPE_BLOCK|ALG_SID_3DES_112)
#define CALG_3DES				(ALG_CLASS_DATA_ENCRYPT|ALG_TYPE_BLOCK|ALG_SID_3DES)
#define CALG_RC2				(ALG_CLASS_DATA_ENCRYPT|ALG_TYPE_BLOCK|ALG_SID_RC2)
#define CALG_RC4				(ALG_CLASS_DATA_ENCRYPT|ALG_TYPE_STREAM|ALG_SID_RC4)
#define CALG_SEAL				(ALG_CLASS_DATA_ENCRYPT|ALG_TYPE_STREAM|ALG_SID_SEAL)
#define CALG_DH_SF              (ALG_CLASS_KEY_EXCHANGE|ALG_TYPE_DH|ALG_SID_DH_SANDF)
#define CALG_DH_EPHEM			(ALG_CLASS_KEY_EXCHANGE|ALG_TYPE_DH|ALG_SID_DH_EPHEM)
#define CALG_AGREEDKEY_ANY		(ALG_CLASS_KEY_EXCHANGE|ALG_TYPE_DH|ALG_SID_AGREED_KEY_ANY)
#define CALG_KEA_KEYX			(ALG_CLASS_KEY_EXCHANGE|ALG_TYPE_DH|ALG_SID_KEA)
#define CALG_HUGHES_MD5         (ALG_CLASS_KEY_EXCHANGE|ALG_TYPE_ANY|ALG_SID_MD5)
#define CALG_SKIPJACK			(ALG_CLASS_DATA_ENCRYPT|ALG_TYPE_BLOCK|ALG_SID_SKIPJACK)
#define CALG_TEK				(ALG_CLASS_DATA_ENCRYPT|ALG_TYPE_BLOCK|ALG_SID_TEK)
#define CALG_CYLINK_MEK         (ALG_CLASS_DATA_ENCRYPT|ALG_TYPE_BLOCK|ALG_SID_CYLINK_MEK)
#define CALG_SSL3_SHAMD5        (ALG_CLASS_HASH | ALG_TYPE_ANY | ALG_SID_SSL3SHAMD5)
#define CALG_SSL3_MASTER        (ALG_CLASS_MSG_ENCRYPT|ALG_TYPE_SECURECHANNEL|ALG_SID_SSL3_MASTER)
#define CALG_SCHANNEL_MASTER_HASH   (ALG_CLASS_MSG_ENCRYPT|ALG_TYPE_SECURECHANNEL|ALG_SID_SCHANNEL_MASTER_HASH)
#define CALG_SCHANNEL_MAC_KEY   (ALG_CLASS_MSG_ENCRYPT|ALG_TYPE_SECURECHANNEL|ALG_SID_SCHANNEL_MAC_KEY)
#define CALG_SCHANNEL_ENC_KEY   (ALG_CLASS_MSG_ENCRYPT|ALG_TYPE_SECURECHANNEL|ALG_SID_SCHANNEL_ENC_KEY)
#define CALG_PCT1_MASTER        (ALG_CLASS_MSG_ENCRYPT|ALG_TYPE_SECURECHANNEL|ALG_SID_PCT1_MASTER)
#define CALG_SSL2_MASTER        (ALG_CLASS_MSG_ENCRYPT|ALG_TYPE_SECURECHANNEL|ALG_SID_SSL2_MASTER)
#define CALG_TLS1_MASTER        (ALG_CLASS_MSG_ENCRYPT|ALG_TYPE_SECURECHANNEL|ALG_SID_TLS1_MASTER)
#define CALG_RC5                (ALG_CLASS_DATA_ENCRYPT|ALG_TYPE_BLOCK|ALG_SID_RC5)
#define CALG_HMAC				(ALG_CLASS_HASH | ALG_TYPE_ANY | ALG_SID_HMAC)

typedef struct _VTableProvStruc {
    DWORD   Version;
    FARPROC FuncVerifyImage;
    FARPROC FuncReturnhWnd;
	DWORD   dwProvType;
	BYTE	*pbContextInfo;
	DWORD	cbContextInfo;
} VTableProvStruc, *PVTableProvStruc;

typedef unsigned long HCRYPTPROV;
typedef unsigned long HCRYPTKEY;
typedef unsigned long HCRYPTHASH;

// dwFlags definitions for CryptAcquireContext
#define CRYPT_VERIFYCONTEXT     0xF0000000
#define CRYPT_NEWKEYSET         0x00000008
#define CRYPT_DELETEKEYSET      0x00000010
#define CRYPT_MACHINE_KEYSET    0x00000020

// dwFlag definitions for CryptGenKey
#define CRYPT_EXPORTABLE        0x00000001
#define CRYPT_USER_PROTECTED    0x00000002
#define CRYPT_CREATE_SALT       0x00000004
#define CRYPT_UPDATE_KEY        0x00000008
#define CRYPT_NO_SALT           0x00000010
#define CRYPT_PREGEN            0x00000040
#define CRYPT_RECIPIENT         0x00000010
#define CRYPT_INITIATOR         0x00000040
#define CRYPT_ONLINE            0x00000080
#define CRYPT_SF                0x00000100
#define CRYPT_CREATE_IV         0x00000200
#define CRYPT_KEK               0x00000400
#define CRYPT_DATA_KEY          0x00000800

// dwFlags definitions for CryptDeriveKey
#define	CRYPT_SERVER			0x00000400

#define KEY_LENGTH_MASK         0xFFFF0000

// dwFlag definitions for CryptExportKey
#define CRYPT_Y_ONLY            0x00000001
#define CRYPT_SSL2_SLUMMING     0x00000002

// dwFlags definitions for CryptHashSessionKey
#define	CRYPT_LITTLE_ENDIAN		0x00000001

// dwFlag definitions for CryptSetProviderEx and CryptGetDefaultProvider
#define CRYPT_MACHINE_DEFAULT   0x00000001
#define CRYPT_USER_DEFAULT      0x00000002
#define CRYPT_DELETE_DEFAULT    0x00000004

// exported key blob definitions
#define SIMPLEBLOB              0x1
#define PUBLICKEYBLOB           0x6
#define PRIVATEKEYBLOB          0x7
#define PLAINTEXTKEYBLOB        0x8

#define AT_KEYEXCHANGE          1
#define AT_SIGNATURE            2

#define CRYPT_USERDATA          1

// dwParam
#define KP_IV                   1       // Initialization vector
#define KP_SALT                 2       // Salt value
#define KP_PADDING              3       // Padding values
#define KP_MODE                 4       // Mode of the cipher
#define KP_MODE_BITS            5       // Number of bits to feedback
#define KP_PERMISSIONS          6       // Key permissions DWORD
#define KP_ALGID                7       // Key algorithm
#define KP_BLOCKLEN             8       // Block size of the cipher
#define KP_KEYLEN               9       // Length of key in bits
#define KP_SALT_EX              10      // Length of salt in bytes
#define KP_P                    11      // DSS/Diffie-Hellman P value
#define KP_G                    12      // DSS/Diffie-Hellman G value
#define KP_Q                    13      // DSS Q value
#define KP_X                    14      // Diffie-Hellman X value
#define KP_Y                    15      // Y value
#define KP_RA                   16      // Fortezza RA value
#define KP_RB                   17      // Fortezza RB value
#define KP_INFO                 18      // for putting information into an RSA envelope
#define KP_EFFECTIVE_KEYLEN     19      // setting and getting RC2 effective key length
#define KP_SCHANNEL_ALG	        20      // for setting the Secure Channel algorithms
#define KP_CLIENT_RANDOM		21      // for setting the Secure Channel client random data
#define KP_SERVER_RANDOM		22      // for setting the Secure Channel server random data
#define	KP_RP					23
#define	KP_PRECOMP_MD5			24
#define	KP_PRECOMP_SHA			25
#define KP_CERTIFICATE          26      // for setting Secure Channel certificate data (PCT1)
#define KP_CLEAR_KEY            27      // for setting Secure Channel clear key data (PCT1)
#define KP_PUB_EX_LEN           28
#define KP_PUB_EX_VAL           29

// KP_PADDING
#define PKCS5_PADDING           1       // PKCS 5 (sec 6.2) padding method
#define RANDOM_PADDING			2
#define	ZERO_PADDING			3

// KP_MODE
#define CRYPT_MODE_CBC          1       // Cipher block chaining
#define CRYPT_MODE_ECB          2       // Electronic code book
#define CRYPT_MODE_OFB          3       // Output feedback mode
#define CRYPT_MODE_CFB          4       // Cipher feedback mode
#define CRYPT_MODE_CTS          5       // Ciphertext stealing mode

// KP_PERMISSIONS
#define CRYPT_ENCRYPT           0x0001  // Allow encryption
#define CRYPT_DECRYPT           0x0002  // Allow decryption
#define CRYPT_EXPORT            0x0004  // Allow key to be exported
#define CRYPT_READ              0x0008  // Allow parameters to be read
#define CRYPT_WRITE             0x0010  // Allow parameters to be set
#define CRYPT_MAC               0x0020  // Allow MACs to be used with key
#define CRYPT_EXPORT_KEY        0x0040  // Allow key to be used for exporting keys
#define CRYPT_IMPORT_KEY        0x0080  // Allow key to be used for importing keys

#define HP_ALGID                0x0001  // Hash algorithm
#define HP_HASHVAL              0x0002  // Hash value
#define HP_HASHSIZE             0x0004  // Hash value size
#define HP_HMAC_INFO            0x0005  // information for creating an HMAC

#define CRYPT_FAILED            FALSE
#define CRYPT_SUCCEED           TRUE

#define RCRYPT_SUCCEEDED(rt)     ((rt) == CRYPT_SUCCEED)
#define RCRYPT_FAILED(rt)        ((rt) == CRYPT_FAILED)

//
// CryptGetProvParam
//
#define PP_ENUMALGS             1
#define PP_ENUMCONTAINERS       2
#define PP_IMPTYPE              3
#define PP_NAME                 4
#define PP_VERSION              5
#define PP_CONTAINER            6
#define PP_CHANGE_PASSWORD      7
#define PP_KEYSET_SEC_DESCR     8       // get/set security descriptor of keyset
#define PP_CERTCHAIN            9       // for retrieving certificates from tokens
#define PP_KEY_TYPE_SUBTYPE     10
#define PP_PROVTYPE             16
#define PP_KEYSTORAGE           17
#define PP_APPLI_CERT           18
#define PP_SYM_KEYSIZE          19
#define PP_SESSION_KEYSIZE      20
#define PP_UI_PROMPT            21
#define PP_ENUMALGS_EX          22

#define CRYPT_FIRST             1
#define CRYPT_NEXT              2

#define CRYPT_IMPL_HARDWARE     1
#define CRYPT_IMPL_SOFTWARE     2
#define CRYPT_IMPL_MIXED        3
#define CRYPT_IMPL_UNKNOWN      4

// key storage flags
#define CRYPT_SEC_DESCR         0x00000001
#define CRYPT_PSTORE            0x00000002
#define CRYPT_UI_PROMPT         0x00000004

// protocol flags
#define CRYPT_FLAG_PCT1         0x0001
#define CRYPT_FLAG_SSL2         0x0002
#define CRYPT_FLAG_SSL3         0x0004
#define CRYPT_FLAG_TLS1         0x0008

//
// CryptSetProvParam
//
#define PP_CLIENT_HWND          1
#define PP_CONTEXT_INFO			11
#define	PP_KEYEXCHANGE_KEYSIZE	12
#define	PP_SIGNATURE_KEYSIZE    13
#define PP_KEYEXCHANGE_ALG      14
#define PP_SIGNATURE_ALG        15
#define PP_DELETEKEY            24

#define PROV_RSA_FULL           1
#define PROV_RSA_SIG            2
#define PROV_DSS                3
#define PROV_FORTEZZA           4
#define PROV_MS_EXCHANGE        5
#define PROV_SSL                6
#define PROV_RSA_SCHANNEL       12
#define PROV_DSS_DH             13
#define PROV_EC_ECDSA_SIG       14
#define PROV_EC_ECNRA_SIG       15
#define PROV_EC_ECDSA_FULL      16
#define PROV_EC_ECNRA_FULL      17
#define PROV_SPYRUS_LYNKS       20

//
// STT defined Providers
//
#define PROV_STT_MER                    7
#define PROV_STT_ACQ                    8
#define PROV_STT_BRND                   9
#define PROV_STT_ROOT                   10
#define PROV_STT_ISS                    11

//
// Provider friendly names
//
#define MS_DEF_PROV_A       "Microsoft Base Cryptographic Provider v1.0"
#define MS_DEF_PROV_W       L"Microsoft Base Cryptographic Provider v1.0"
#ifdef UNICODE
#define MS_DEF_PROV         MS_DEF_PROV_W
#else
#define MS_DEF_PROV         MS_DEF_PROV_A
#endif

#define MS_ENHANCED_PROV_A       "Microsoft Enhanced Cryptographic Provider v1.0"
#define MS_ENHANCED_PROV_W       L"Microsoft Enhanced Cryptographic Provider v1.0"
#ifdef UNICODE
#define MS_ENHANCED_PROV         MS_ENHANCED_PROV_W
#else
#define MS_ENHANCED_PROV         MS_ENHANCED_PROV_A
#endif

#define MS_DEF_RSA_SIG_PROV_A    "Microsoft RSA Signature Cryptographic Provider"
#define MS_DEF_RSA_SIG_PROV_W    L"Microsoft RSA Signature Cryptographic Provider"
#ifdef UNICODE
#define MS_DEF_RSA_SIG_PROV      MS_DEF_RSA_SIG_PROV_W
#else
#define MS_DEF_RSA_SIG_PROV      MS_DEF_RSA_SIG_PROV_A
#endif

#define MS_DEF_RSA_SCHANNEL_PROV_A  "Microsoft Base RSA SChannel Cryptographic Provider"
#define MS_DEF_RSA_SCHANNEL_PROV_W  L"Microsoft Base RSA SChannel Cryptographic Provider"
#ifdef UNICODE
#define MS_DEF_RSA_SCHANNEL_PROV         MS_DEF_RSA_SCHANNEL_PROV_W
#else
#define MS_DEF_RSA_SCHANNEL_PROV         MS_DEF_RSA_SCHANNEL_PROV_A
#endif

#define MS_ENHANCED_RSA_SCHANNEL_PROV_A  "Microsoft Enhanced RSA SChannel Cryptographic Provider"
#define MS_ENHANCED_RSA_SCHANNEL_PROV_W  L"Microsoft Enhanced RSA SChannel Cryptographic Provider"
#ifdef UNICODE
#define MS_ENHANCED_RSA_SCHANNEL_PROV    MS_ENHANCED_RSA_SCHANNEL_PROV_W
#else
#define MS_ENHANCED_RSA_SCHANNEL_PROV    MS_ENHANCED_RSA_SCHANNEL_PROV_A
#endif

#define MS_DEF_DSS_PROV_A        "Microsoft Base DSS Cryptographic Provider"
#define MS_DEF_DSS_PROV_W        L"Microsoft Base DSS Cryptographic Provider"
#ifdef UNICODE
#define MS_DEF_DSS_PROV          MS_DEF_DSS_PROV_W
#else
#define MS_DEF_DSS_PROV          MS_DEF_DSS_PROV_A
#endif

#define MS_DEF_DSS_DH_PROV_A    "Microsoft Base DSS and Diffie-Hellman Cryptographic Provider"
#define MS_DEF_DSS_DH_PROV_W    L"Microsoft Base DSS and Diffie-Hellman Cryptographic Provider"
#ifdef UNICODE
#define MS_DEF_DSS_DH_PROV      MS_DEF_DSS_DH_PROV_W
#else
#define MS_DEF_DSS_DH_PROV      MS_DEF_DSS_DH_PROV_A
#endif


#define MAXUIDLEN               64

#define CUR_BLOB_VERSION        2

// structure for use with CryptSetHashParam with CALG_HMAC
typedef struct _HMAC_Info {
        ALG_ID  HashAlgid;
        BYTE    *pbInnerString;
        DWORD   cbInnerString;
        BYTE    *pbOuterString;
        DWORD   cbOuterString;
} HMAC_INFO, *PHMAC_INFO;

// structure for use with CryptSetKeyParam with KP_SCHANNEL_ALG
typedef struct _SCHANNEL_ALG {
        DWORD   dwUse;
        ALG_ID  Algid;
        DWORD   cBits;
} SCHANNEL_ALG, *PSCHANNEL_ALG;

// uses of algortihms for SCHANNEL_ALG structure
#define     SCHANNEL_MAC_KEY    0x00000000
#define     SCHANNEL_ENC_KEY    0x00000001

typedef struct _PROV_ENUMALGS {
    ALG_ID    aiAlgid;
    DWORD     dwBitLen;
    DWORD     dwNameLen;
    CHAR      szName[20];
} PROV_ENUMALGS;

typedef struct _PROV_ENUMALGS_EX {
    ALG_ID    aiAlgid;
    DWORD     dwDefaultLen;
    DWORD     dwMinLen;
    DWORD     dwMaxLen;
    DWORD     dwProtocols;
    DWORD     dwNameLen;
    CHAR      szName[20];
    DWORD     dwLongNameLen;
    CHAR      szLongName[40];
} PROV_ENUMALGS_EX;

typedef struct _PUBLICKEYSTRUC {
        BYTE    bType;
        BYTE    bVersion;
        WORD    reserved;
        ALG_ID  aiKeyAlg;
} BLOBHEADER, PUBLICKEYSTRUC;

typedef struct _RSAPUBKEY {
        DWORD   magic;                  // Has to be RSA1
        DWORD   bitlen;                 // # of bits in modulus
        DWORD   pubexp;                 // public exponent
                                        // Modulus data follows
} RSAPUBKEY;

typedef struct _PUBKEY {
        DWORD   magic;
        DWORD   bitlen;                 // # of bits in modulus
} DHPUBKEY, DSSPUBKEY, KEAPUBKEY, TEKPUBKEY;

typedef struct _DSSSEED {
        DWORD   counter;
        BYTE    seed[20];
} DSSSEED;

typedef struct _KEY_TYPE_SUBTYPE {
        DWORD   dwKeySpec;
        GUID    Type;
        GUID    Subtype;
} KEY_TYPE_SUBTYPE, *PKEY_TYPE_SUBTYPE;


WINADVAPI
BOOL
WINAPI
CryptAcquireContextA(
    HCRYPTPROV *phProv,
    LPCSTR pszContainer,
    LPCSTR pszProvider,
    DWORD dwProvType,
    DWORD dwFlags);
WINADVAPI
BOOL
WINAPI
CryptAcquireContextW(
    HCRYPTPROV *phProv,
    LPCWSTR pszContainer,
    LPCWSTR pszProvider,
    DWORD dwProvType,
    DWORD dwFlags);
#ifdef UNICODE
#define CryptAcquireContext  CryptAcquireContextW
#else
#define CryptAcquireContext  CryptAcquireContextA
#endif // !UNICODE


WINADVAPI
BOOL
WINAPI
CryptReleaseContext(
    HCRYPTPROV hProv,
    DWORD dwFlags);


WINADVAPI
BOOL
WINAPI
CryptGenKey(
    HCRYPTPROV hProv,
    ALG_ID Algid,
    DWORD dwFlags,
    HCRYPTKEY *phKey);

WINADVAPI
BOOL
WINAPI
CryptDeriveKey(
    HCRYPTPROV hProv,
    ALG_ID Algid,
    HCRYPTHASH hBaseData,
    DWORD dwFlags,
    HCRYPTKEY *phKey);


WINADVAPI
BOOL
WINAPI
CryptDestroyKey(
    HCRYPTKEY hKey);

WINADVAPI
BOOL
WINAPI
CryptSetKeyParam(
    HCRYPTKEY hKey,
    DWORD dwParam,
    BYTE *pbData,
    DWORD dwFlags);

WINADVAPI
BOOL
WINAPI
CryptGetKeyParam(
    HCRYPTKEY hKey,
    DWORD dwParam,
    BYTE *pbData,
    DWORD *pdwDataLen,
    DWORD dwFlags);

WINADVAPI
BOOL
WINAPI
CryptSetHashParam(
    HCRYPTHASH hHash,
    DWORD dwParam,
    BYTE *pbData,
    DWORD dwFlags);

WINADVAPI
BOOL
WINAPI
CryptGetHashParam(
    HCRYPTHASH hHash,
    DWORD dwParam,
    BYTE *pbData,
    DWORD *pdwDataLen,
    DWORD dwFlags);

WINADVAPI
BOOL
WINAPI
CryptSetProvParam(
    HCRYPTPROV hProv,
    DWORD dwParam,
    BYTE *pbData,
    DWORD dwFlags);

WINADVAPI
BOOL
WINAPI
CryptGetProvParam(
    HCRYPTPROV hProv,
    DWORD dwParam,
    BYTE *pbData,
    DWORD *pdwDataLen,
    DWORD dwFlags);

WINADVAPI
BOOL
WINAPI
CryptGenRandom(
    HCRYPTPROV hProv,
    DWORD dwLen,
    BYTE *pbBuffer);

WINADVAPI
BOOL
WINAPI
CryptGetUserKey(
    HCRYPTPROV hProv,
    DWORD dwKeySpec,
    HCRYPTKEY *phUserKey);

WINADVAPI
BOOL
WINAPI
CryptExportKey(
    HCRYPTKEY hKey,
    HCRYPTKEY hExpKey,
    DWORD dwBlobType,
    DWORD dwFlags,
    BYTE *pbData,
    DWORD *pdwDataLen);

WINADVAPI
BOOL
WINAPI
CryptImportKey(
    HCRYPTPROV hProv,
    CONST BYTE *pbData,
    DWORD dwDataLen,
    HCRYPTKEY hPubKey,
    DWORD dwFlags,
    HCRYPTKEY *phKey);

WINADVAPI
BOOL
WINAPI
CryptEncrypt(
    HCRYPTKEY hKey,
    HCRYPTHASH hHash,
    BOOL Final,
    DWORD dwFlags,
    BYTE *pbData,
    DWORD *pdwDataLen,
    DWORD dwBufLen);

WINADVAPI
BOOL
WINAPI
CryptDecrypt(
    HCRYPTKEY hKey,
    HCRYPTHASH hHash,
    BOOL Final,
    DWORD dwFlags,
    BYTE *pbData,
    DWORD *pdwDataLen);

WINADVAPI
BOOL
WINAPI
CryptCreateHash(
    HCRYPTPROV hProv,
    ALG_ID Algid,
    HCRYPTKEY hKey,
    DWORD dwFlags,
    HCRYPTHASH *phHash);

WINADVAPI
BOOL
WINAPI
CryptHashData(
    HCRYPTHASH hHash,
    CONST BYTE *pbData,
    DWORD dwDataLen,
    DWORD dwFlags);

WINADVAPI
BOOL
WINAPI
CryptHashSessionKey(
    HCRYPTHASH hHash,
    HCRYPTKEY hKey,
    DWORD dwFlags);

WINADVAPI
BOOL
WINAPI
CryptDestroyHash(
    HCRYPTHASH hHash);

WINADVAPI
BOOL
WINAPI
CryptSignHashA(
    HCRYPTHASH hHash,
    DWORD dwKeySpec,
    LPCSTR sDescription,
    DWORD dwFlags,
    BYTE *pbSignature,
    DWORD *pdwSigLen);
WINADVAPI
BOOL
WINAPI
CryptSignHashW(
    HCRYPTHASH hHash,
    DWORD dwKeySpec,
    LPCWSTR sDescription,
    DWORD dwFlags,
    BYTE *pbSignature,
    DWORD *pdwSigLen);
#ifdef UNICODE
#define CryptSignHash  CryptSignHashW
#else
#define CryptSignHash  CryptSignHashA
#endif // !UNICODE

WINADVAPI
BOOL
WINAPI
CryptVerifySignatureA(
    HCRYPTHASH hHash,
    CONST BYTE *pbSignature,
    DWORD dwSigLen,
    HCRYPTKEY hPubKey,
    LPCSTR sDescription,
    DWORD dwFlags);
WINADVAPI
BOOL
WINAPI
CryptVerifySignatureW(
    HCRYPTHASH hHash,
    CONST BYTE *pbSignature,
    DWORD dwSigLen,
    HCRYPTKEY hPubKey,
    LPCWSTR sDescription,
    DWORD dwFlags);
#ifdef UNICODE
#define CryptVerifySignature  CryptVerifySignatureW
#else
#define CryptVerifySignature  CryptVerifySignatureA
#endif // !UNICODE

WINADVAPI
BOOL
WINAPI
CryptSetProviderA(
    LPCSTR pszProvName,
    DWORD dwProvType);
WINADVAPI
BOOL
WINAPI
CryptSetProviderW(
    LPCWSTR pszProvName,
    DWORD dwProvType);
#ifdef UNICODE
#define CryptSetProvider  CryptSetProviderW
#else
#define CryptSetProvider  CryptSetProviderA
#endif // !UNICODE

WINADVAPI
BOOL
WINAPI
CryptSetProviderExA(
    LPCSTR pszProvName,
    DWORD dwProvType,
    DWORD *pdwReserved,
    DWORD dwFlags);
WINADVAPI
BOOL
WINAPI
CryptSetProviderExW(
    LPCWSTR pszProvName,
    DWORD dwProvType,
    DWORD *pdwReserved,
    DWORD dwFlags);
#ifdef UNICODE
#define CryptSetProviderEx  CryptSetProviderExW
#else
#define CryptSetProviderEx  CryptSetProviderExA
#endif // !UNICODE

WINADVAPI
BOOL
WINAPI
CryptGetDefaultProviderA(
    DWORD dwProvType,
    DWORD *pdwReserved,
    DWORD dwFlags,
    LPSTR pszProvName,
    DWORD *pcbProvName);
WINADVAPI
BOOL
WINAPI
CryptGetDefaultProviderW(
    DWORD dwProvType,
    DWORD *pdwReserved,
    DWORD dwFlags,
    LPWSTR pszProvName,
    DWORD *pcbProvName);
#ifdef UNICODE
#define CryptGetDefaultProvider  CryptGetDefaultProviderW
#else
#define CryptGetDefaultProvider  CryptGetDefaultProviderA
#endif // !UNICODE

WINADVAPI
BOOL
WINAPI CryptEnumProviderTypesA(
    DWORD dwIndex,
    DWORD *pdwReserved,
    DWORD dwFlags,
    DWORD *pdwProvType,
    LPSTR pszTypeName,
    DWORD *pcbTypeName);
WINADVAPI
BOOL
WINAPI CryptEnumProviderTypesW(
    DWORD dwIndex,
    DWORD *pdwReserved,
    DWORD dwFlags,
    DWORD *pdwProvType,
    LPWSTR pszTypeName,
    DWORD *pcbTypeName);
#ifdef UNICODE
#define CryptEnumProviderTypes  CryptEnumProviderTypesW
#else
#define CryptEnumProviderTypes  CryptEnumProviderTypesA
#endif // !UNICODE

WINADVAPI
BOOL
WINAPI CryptEnumProvidersA(
    DWORD dwIndex,
    DWORD *pdwReserved,
    DWORD dwFlags,
    DWORD *pdwProvType,
    LPSTR pszProvName,
    DWORD *pcbProvName);
WINADVAPI
BOOL
WINAPI CryptEnumProvidersW(
    DWORD dwIndex,
    DWORD *pdwReserved,
    DWORD dwFlags,
    DWORD *pdwProvType,
    LPWSTR pszProvName,
    DWORD *pcbProvName);
#ifdef UNICODE
#define CryptEnumProviders  CryptEnumProvidersW
#else
#define CryptEnumProviders  CryptEnumProvidersA
#endif // !UNICODE

WINADVAPI
BOOL
WINAPI CryptContextAddRef(
    HCRYPTPROV hProv,
    DWORD *pdwReserved,
    DWORD dwFlags);

WINADVAPI
BOOL
WINAPI CryptDuplicateKey(
    HCRYPTKEY hKey,
    DWORD *pdwReserved,
    DWORD dwFlags,
    HCRYPTKEY * phKey);

WINADVAPI
BOOL
WINAPI CryptDuplicateHash(
    HCRYPTHASH hHash,
    DWORD *pdwReserved,
    DWORD dwFlags,
    HCRYPTHASH * phHash);

//+-------------------------------------------------------------------------
//  CRYPTOAPI BLOB definitions
//--------------------------------------------------------------------------
typedef struct _CRYPTOAPI_BLOB {
    DWORD   cbData;
    BYTE    *pbData;
} CRYPT_INTEGER_BLOB, *PCRYPT_INTEGER_BLOB,
  CRYPT_UINT_BLOB, *PCRYPT_UINT_BLOB,
  CRYPT_OBJID_BLOB, *PCRYPT_OBJID_BLOB,
  CERT_NAME_BLOB, *PCERT_NAME_BLOB,
  CERT_RDN_VALUE_BLOB, *PCERT_RDN_VALUE_BLOB,
  CERT_BLOB, *PCERT_BLOB,
  CRL_BLOB, *PCRL_BLOB,
  DATA_BLOB, *PDATA_BLOB,                   // JEFFJEFF temporary (too generic)
  CRYPT_DATA_BLOB, *PCRYPT_DATA_BLOB,
  CRYPT_HASH_BLOB, *PCRYPT_HASH_BLOB,
  CRYPT_DIGEST_BLOB, *PCRYPT_DIGEST_BLOB,
  CRYPT_DER_BLOB, *PCRYPT_DER_BLOB,
  CRYPT_ATTR_BLOB, *PCRYPT_ATTR_BLOB;

//+-------------------------------------------------------------------------
//  In a CRYPT_BIT_BLOB the last byte may contain 0-7 unused bits. Therefore, the
//  overall bit length is cbData * 8 - cUnusedBits.
//--------------------------------------------------------------------------
typedef struct _CRYPT_BIT_BLOB {
    DWORD   cbData;
    BYTE    *pbData;
    DWORD   cUnusedBits;
} CRYPT_BIT_BLOB, *PCRYPT_BIT_BLOB;

//+-------------------------------------------------------------------------
//  Type used for any algorithm
//
//  Where the Parameters CRYPT_OBJID_BLOB is in its encoded representation. For most
//  algorithm types, the Parameters CRYPT_OBJID_BLOB is NULL (Parameters.cbData = 0).
//--------------------------------------------------------------------------
typedef struct _CRYPT_ALGORITHM_IDENTIFIER {
    LPSTR               pszObjId;
    CRYPT_OBJID_BLOB    Parameters;
} CRYPT_ALGORITHM_IDENTIFIER, *PCRYPT_ALGORITHM_IDENTIFIER;

// Following are the definitions of various algorithm object identifiers
// RSA
#define szOID_RSA               "1.2.840.113549"
#define szOID_PKCS              "1.2.840.113549.1"
#define szOID_RSA_HASH          "1.2.840.113549.2"
#define szOID_RSA_ENCRYPT       "1.2.840.113549.3"

#define szOID_PKCS_1            "1.2.840.113549.1.1"
#define szOID_PKCS_2            "1.2.840.113549.1.2"
#define szOID_PKCS_3            "1.2.840.113549.1.3"
#define szOID_PKCS_4            "1.2.840.113549.1.4"
#define szOID_PKCS_5            "1.2.840.113549.1.5"
#define szOID_PKCS_6            "1.2.840.113549.1.6"
#define szOID_PKCS_7            "1.2.840.113549.1.7"
#define szOID_PKCS_8            "1.2.840.113549.1.8"
#define szOID_PKCS_9            "1.2.840.113549.1.9"
#define szOID_PKCS_10           "1.2.840.113549.1.10"

#define szOID_RSA_RSA           "1.2.840.113549.1.1.1"
#define szOID_RSA_MD2RSA        "1.2.840.113549.1.1.2"
#define szOID_RSA_MD4RSA        "1.2.840.113549.1.1.3"
#define szOID_RSA_MD5RSA        "1.2.840.113549.1.1.4"
#define szOID_RSA_SHA1RSA       "1.2.840.113549.1.1.5"
#define szOID_RSA_SETOAEP_RSA   "1.2.840.113549.1.1.6"

#define szOID_RSA_data          "1.2.840.113549.1.7.1"
#define szOID_RSA_signedData    "1.2.840.113549.1.7.2"
#define szOID_RSA_envelopedData "1.2.840.113549.1.7.3"
#define szOID_RSA_signEnvData   "1.2.840.113549.1.7.4"
#define szOID_RSA_digestedData  "1.2.840.113549.1.7.5"
#define szOID_RSA_hashedData    "1.2.840.113549.1.7.5"
#define szOID_RSA_encryptedData "1.2.840.113549.1.7.6"

#define szOID_RSA_emailAddr     "1.2.840.113549.1.9.1"
#define szOID_RSA_unstructName  "1.2.840.113549.1.9.2"
#define szOID_RSA_contentType   "1.2.840.113549.1.9.3"
#define szOID_RSA_messageDigest "1.2.840.113549.1.9.4"
#define szOID_RSA_signingTime   "1.2.840.113549.1.9.5"
#define szOID_RSA_counterSign   "1.2.840.113549.1.9.6"
#define szOID_RSA_challengePwd  "1.2.840.113549.1.9.7"
#define szOID_RSA_unstructAddr  "1.2.840.113549.1.9.8"
#define szOID_RSA_extCertAttrs  "1.2.840.113549.1.9.9"
#define szOID_RSA_SMIMECapabilities "1.2.840.113549.1.9.15"
#define szOID_RSA_preferSignedData "1.2.840.113549.1.9.15.1"

#define szOID_RSA_MD2           "1.2.840.113549.2.2"
#define szOID_RSA_MD4           "1.2.840.113549.2.4"
#define szOID_RSA_MD5           "1.2.840.113549.2.5"

#define szOID_RSA_RC2CBC        "1.2.840.113549.3.2"
#define szOID_RSA_RC4           "1.2.840.113549.3.4"
#define szOID_RSA_DES_EDE3_CBC  "1.2.840.113549.3.7"
#define szOID_RSA_RC5_CBCPad    "1.2.840.113549.3.9"

// ITU-T UsefulDefinitions
#define szOID_DS                "2.5"
#define szOID_DSALG             "2.5.8"
#define szOID_DSALG_CRPT        "2.5.8.1"
#define szOID_DSALG_HASH        "2.5.8.2"
#define szOID_DSALG_SIGN        "2.5.8.3"
#define szOID_DSALG_RSA         "2.5.8.1.1"
// NIST OSE Implementors' Workshop (OIW)
// http://nemo.ncsl.nist.gov/oiw/agreements/stable/OSI/12s_9506.w51
// http://nemo.ncsl.nist.gov/oiw/agreements/working/OSI/12w_9503.w51
#define szOID_OIW               "1.3.14"
// NIST OSE Implementors' Workshop (OIW) Security SIG algorithm identifiers
#define szOID_OIWSEC            "1.3.14.3.2"
#define szOID_OIWSEC_md4RSA     "1.3.14.3.2.2"
#define szOID_OIWSEC_md5RSA     "1.3.14.3.2.3"
#define szOID_OIWSEC_md4RSA2    "1.3.14.3.2.4"
#define szOID_OIWSEC_desECB     "1.3.14.3.2.6"
#define szOID_OIWSEC_desCBC     "1.3.14.3.2.7"
#define szOID_OIWSEC_desOFB     "1.3.14.3.2.8"
#define szOID_OIWSEC_desCFB     "1.3.14.3.2.9"
#define szOID_OIWSEC_desMAC     "1.3.14.3.2.10"
#define szOID_OIWSEC_rsaSign    "1.3.14.3.2.11"
#define szOID_OIWSEC_dsa        "1.3.14.3.2.12"
#define szOID_OIWSEC_shaDSA     "1.3.14.3.2.13"
#define szOID_OIWSEC_mdc2RSA    "1.3.14.3.2.14"
#define szOID_OIWSEC_shaRSA     "1.3.14.3.2.15"
#define szOID_OIWSEC_dhCommMod  "1.3.14.3.2.16"
#define szOID_OIWSEC_desEDE     "1.3.14.3.2.17"
#define szOID_OIWSEC_sha        "1.3.14.3.2.18"
#define szOID_OIWSEC_mdc2       "1.3.14.3.2.19"
#define szOID_OIWSEC_dsaComm    "1.3.14.3.2.20"
#define szOID_OIWSEC_dsaCommSHA "1.3.14.3.2.21"
#define szOID_OIWSEC_rsaXchg    "1.3.14.3.2.22"
#define szOID_OIWSEC_keyHashSeal "1.3.14.3.2.23"
#define szOID_OIWSEC_md2RSASign "1.3.14.3.2.24"
#define szOID_OIWSEC_md5RSASign "1.3.14.3.2.25"
#define szOID_OIWSEC_sha1       "1.3.14.3.2.26"
#define szOID_OIWSEC_dsaSHA1    "1.3.14.3.2.27"
#define szOID_OIWSEC_dsaCommSHA1 "1.3.14.3.2.28"
#define szOID_OIWSEC_sha1RSASign "1.3.14.3.2.29"
// NIST OSE Implementors' Workshop (OIW) Directory SIG algorithm identifiers
#define szOID_OIWDIR            "1.3.14.7.2"
#define szOID_OIWDIR_CRPT       "1.3.14.7.2.1"
#define szOID_OIWDIR_HASH       "1.3.14.7.2.2"
#define szOID_OIWDIR_SIGN       "1.3.14.7.2.3"
#define szOID_OIWDIR_md2        "1.3.14.7.2.2.1"
#define szOID_OIWDIR_md2RSA     "1.3.14.7.2.3.1"


// INFOSEC Algorithms
// joint-iso-ccitt(2) country(16) us(840) organization(1) us-government(101) dod(2) id-infosec(1)
#define szOID_INFOSEC                       "2.16.840.1.101.2.1"
#define szOID_INFOSEC_sdnsSignature         "2.16.840.1.101.2.1.1.1"
#define szOID_INFOSEC_mosaicSignature       "2.16.840.1.101.2.1.1.2"
#define szOID_INFOSEC_sdnsConfidentiality   "2.16.840.1.101.2.1.1.3"
#define szOID_INFOSEC_mosaicConfidentiality "2.16.840.1.101.2.1.1.4"
#define szOID_INFOSEC_sdnsIntegrity         "2.16.840.1.101.2.1.1.5"
#define szOID_INFOSEC_mosaicIntegrity       "2.16.840.1.101.2.1.1.6"
#define szOID_INFOSEC_sdnsTokenProtection   "2.16.840.1.101.2.1.1.7"
#define szOID_INFOSEC_mosaicTokenProtection "2.16.840.1.101.2.1.1.8"
#define szOID_INFOSEC_sdnsKeyManagement     "2.16.840.1.101.2.1.1.9"
#define szOID_INFOSEC_mosaicKeyManagement   "2.16.840.1.101.2.1.1.10"
#define szOID_INFOSEC_sdnsKMandSig          "2.16.840.1.101.2.1.1.11"
#define szOID_INFOSEC_mosaicKMandSig        "2.16.840.1.101.2.1.1.12"
#define szOID_INFOSEC_SuiteASignature       "2.16.840.1.101.2.1.1.13"
#define szOID_INFOSEC_SuiteAConfidentiality "2.16.840.1.101.2.1.1.14"
#define szOID_INFOSEC_SuiteAIntegrity       "2.16.840.1.101.2.1.1.15"
#define szOID_INFOSEC_SuiteATokenProtection "2.16.840.1.101.2.1.1.16"
#define szOID_INFOSEC_SuiteAKeyManagement   "2.16.840.1.101.2.1.1.17"
#define szOID_INFOSEC_SuiteAKMandSig        "2.16.840.1.101.2.1.1.18"
#define szOID_INFOSEC_mosaicUpdatedSig      "2.16.840.1.101.2.1.1.19"
#define szOID_INFOSEC_mosaicKMandUpdSig     "2.16.840.1.101.2.1.1.20"
#define szOID_INFOSEC_mosaicUpdatedInteg    "2.16.840.1.101.2.1.1.21"

typedef struct _CRYPT_OBJID_TABLE {
    DWORD   dwAlgId;
    LPCSTR  pszObjId;
} CRYPT_OBJID_TABLE, *PCRYPT_OBJID_TABLE;


//+-------------------------------------------------------------------------
//  PKCS #1 HashInfo (DigestInfo)
//--------------------------------------------------------------------------
typedef struct _CRYPT_HASH_INFO {
    CRYPT_ALGORITHM_IDENTIFIER  HashAlgorithm;
    CRYPT_HASH_BLOB             Hash;
} CRYPT_HASH_INFO, *PCRYPT_HASH_INFO;

//+-------------------------------------------------------------------------
//  Type used for an extension to an encoded content
//
//  Where the Value's CRYPT_OBJID_BLOB is in its encoded representation.
//--------------------------------------------------------------------------
typedef struct _CERT_EXTENSION {
    LPSTR               pszObjId;
    BOOL                fCritical;
    CRYPT_OBJID_BLOB    Value;
} CERT_EXTENSION, *PCERT_EXTENSION;

//+-------------------------------------------------------------------------
//  AttributeTypeValue
//
//  Where the Value's CRYPT_OBJID_BLOB is in its encoded representation.
//--------------------------------------------------------------------------
typedef struct _CRYPT_ATTRIBUTE_TYPE_VALUE {
    LPSTR               pszObjId;
    CRYPT_OBJID_BLOB    Value;
} CRYPT_ATTRIBUTE_TYPE_VALUE, *PCRYPT_ATTRIBUTE_TYPE_VALUE;

//+-------------------------------------------------------------------------
//  Attributes
//
//  Where the Value's PATTR_BLOBs are in their encoded representation.
//--------------------------------------------------------------------------
typedef struct _CRYPT_ATTRIBUTE {
    LPSTR               pszObjId;
    DWORD               cValue;
    PCRYPT_ATTR_BLOB    rgValue;
} CRYPT_ATTRIBUTE, *PCRYPT_ATTRIBUTE;

typedef struct _CRYPT_ATTRIBUTES {
    IN DWORD                cAttr;
    IN PCRYPT_ATTRIBUTE     rgAttr;
} CRYPT_ATTRIBUTES, *PCRYPT_ATTRIBUTES;

//+-------------------------------------------------------------------------
//  Attributes making up a Relative Distinguished Name (CERT_RDN)
//
//  The interpretation of the Value depends on the dwValueType.
//  See below for a list of the types.
//--------------------------------------------------------------------------
typedef struct _CERT_RDN_ATTR {
    LPSTR                   pszObjId;
    DWORD                   dwValueType;
    CERT_RDN_VALUE_BLOB     Value;
} CERT_RDN_ATTR, *PCERT_RDN_ATTR;

//+-------------------------------------------------------------------------
//  CERT_RDN attribute Object Identifiers
//--------------------------------------------------------------------------
// Labeling attribute types:
#define szOID_COMMON_NAME                   "2.5.4.3"  // case-ignore string
#define szOID_SUR_NAME                      "2.5.4.4"  // case-ignore string
#define szOID_DEVICE_SERIAL_NUMBER          "2.5.4.5"  // printable string

// Geographic attribute types:
#define szOID_COUNTRY_NAME                  "2.5.4.6"  // printable 2char string
#define szOID_LOCALITY_NAME                 "2.5.4.7"  // case-ignore string
#define szOID_STATE_OR_PROVINCE_NAME        "2.5.4.8"  // case-ignore string
#define szOID_STREET_ADDRESS                "2.5.4.9"  // case-ignore string

// Organizational attribute types:
#define szOID_ORGANIZATION_NAME             "2.5.4.10" // case-ignore string
#define szOID_ORGANIZATIONAL_UNIT_NAME      "2.5.4.11" // case-ignore string
#define szOID_TITLE                         "2.5.4.12" // case-ignore string

// Explanatory attribute types:
#define szOID_DESCRIPTION                   "2.5.4.13" // case-ignore string
#define szOID_SEARCH_GUIDE                  "2.5.4.14"
#define szOID_BUSINESS_CATEGORY             "2.5.4.15" // case-ignore string

// Postal addressing attribute types:
#define szOID_POSTAL_ADDRESS                "2.5.4.16"
#define szOID_POSTAL_CODE                   "2.5.4.17" // case-ignore string
#define szOID_POST_OFFICE_BOX               "2.5.4.18" // case-ignore string
#define szOID_PHYSICAL_DELIVERY_OFFICE_NAME "2.5.4.19" // case-ignore string

// Telecommunications addressing attribute types:
#define szOID_TELEPHONE_NUMBER              "2.5.4.20" // telephone number
#define szOID_TELEX_NUMBER                  "2.5.4.21"
#define szOID_TELETEXT_TERMINAL_IDENTIFIER  "2.5.4.22"
#define szOID_FACSIMILE_TELEPHONE_NUMBER    "2.5.4.23"
#define szOID_X21_ADDRESS                   "2.5.4.24" // numeric string
#define szOID_INTERNATIONAL_ISDN_NUMBER     "2.5.4.25" // numeric string
#define szOID_REGISTERED_ADDRESS            "2.5.4.26"
#define szOID_DESTINATION_INDICATOR         "2.5.4.27" // printable string

// Preference attribute types:
#define szOID_PREFERRED_DELIVERY_METHOD     "2.5.4.28"

// OSI application attribute types:
#define szOID_PRESENTATION_ADDRESS          "2.5.4.29"
#define szOID_SUPPORTED_APPLICATION_CONTEXT "2.5.4.30"

// Relational application attribute types:
#define szOID_MEMBER                        "2.5.4.31"
#define szOID_OWNER                         "2.5.4.32"
#define szOID_ROLE_OCCUPANT                 "2.5.4.33"
#define szOID_SEE_ALSO                      "2.5.4.34"

// Security attribute types:
#define szOID_USER_PASSWORD                 "2.5.4.35"
#define szOID_USER_CERTIFICATE              "2.5.4.36"
#define szOID_CA_CERTIFICATE                "2.5.4.37"
#define szOID_AUTHORITY_REVOCATION_LIST     "2.5.4.38"
#define szOID_CERTIFICATE_REVOCATION_LIST   "2.5.4.39"
#define szOID_CROSS_CERTIFICATE_PAIR        "2.5.4.40"

// Undocumented attribute types???
//#define szOID_???                         "2.5.4.41"
#define szOID_GIVEN_NAME                    "2.5.4.42" // case-ignore string
#define szOID_INITIALS                      "2.5.4.43" // case-ignore string

// Pilot user attribute types:
#define szOID_DOMAIN_COMPONENT  "0.9.2342.19200300.100.1.25" // IA5 string

//+-------------------------------------------------------------------------
//  CERT_RDN Attribute Value Types
//
//  For RDN_ENCODED_BLOB, the Value's CERT_RDN_VALUE_BLOB is in its encoded
//  representation. Otherwise, its an array of bytes.
//
//  For all CERT_RDN types, Value.cbData is always the number of bytes, not
//  necessarily the number of elements in the string. For instance,
//  RDN_UNIVERSAL_STRING is an array of ints (cbData == intCnt * 4) and
//  RDN_BMP_STRING is an array of unsigned shorts (cbData == ushortCnt * 2).
//
//  For CertDecodeName, two 0 bytes are always appended to the end of the
//  string (ensures a CHAR or WCHAR string is null terminated).
//  These added 0 bytes are't included in the BLOB.cbData.
//--------------------------------------------------------------------------
#define CERT_RDN_ANY_TYPE                0
#define CERT_RDN_ENCODED_BLOB            1
#define CERT_RDN_OCTET_STRING            2
#define CERT_RDN_NUMERIC_STRING          3
#define CERT_RDN_PRINTABLE_STRING        4
#define CERT_RDN_TELETEX_STRING          5
#define CERT_RDN_T61_STRING              5
#define CERT_RDN_VIDEOTEX_STRING         6
#define CERT_RDN_IA5_STRING              7
#define CERT_RDN_GRAPHIC_STRING          8
#define CERT_RDN_VISIBLE_STRING          9
#define CERT_RDN_ISO646_STRING           9
#define CERT_RDN_GENERAL_STRING          10
#define CERT_RDN_UNIVERSAL_STRING        11
#define CERT_RDN_INT4_STRING             11
#define CERT_RDN_BMP_STRING              12
#define CERT_RDN_UNICODE_STRING          12


// Macro to check that the dwValueType is a character string and not an
// encoded blob or octet string
#define IS_CERT_RDN_CHAR_STRING(X) (X >= CERT_RDN_NUMERIC_STRING)

//+-------------------------------------------------------------------------
//  A CERT_RDN consists of an array of the above attributes
//--------------------------------------------------------------------------
typedef struct _CERT_RDN {
    DWORD           cRDNAttr;
    PCERT_RDN_ATTR  rgRDNAttr;
} CERT_RDN, *PCERT_RDN;

//+-------------------------------------------------------------------------
//  Information stored in a subject's or issuer's name. The information
//  is represented as an array of the above RDNs.
//--------------------------------------------------------------------------
typedef struct _CERT_NAME_INFO {
    DWORD       cRDN;
    PCERT_RDN   rgRDN;
} CERT_NAME_INFO, *PCERT_NAME_INFO;

//+-------------------------------------------------------------------------
//  Name attribute value without the Object Identifier
//
//  The interpretation of the Value depends on the dwValueType.
//  See above for a list of the types.
//--------------------------------------------------------------------------
typedef struct _CERT_NAME_VALUE {
    DWORD               dwValueType;
    CERT_RDN_VALUE_BLOB Value;
} CERT_NAME_VALUE, *PCERT_NAME_VALUE;

//+-------------------------------------------------------------------------
//  Public Key Info
//
//  The PublicKey is the encoded representation of the information as it is
//  stored in the bit string
//--------------------------------------------------------------------------
typedef struct _CERT_PUBLIC_KEY_INFO {
    CRYPT_ALGORITHM_IDENTIFIER    Algorithm;
    CRYPT_BIT_BLOB                PublicKey;
} CERT_PUBLIC_KEY_INFO, *PCERT_PUBLIC_KEY_INFO;

#define CERT_RSA_PUBLIC_KEY_OBJID            szOID_RSA_RSA
#define CERT_DEFAULT_OID_PUBLIC_KEY_SIGN     szOID_RSA_RSA
#define CERT_DEFAULT_OID_PUBLIC_KEY_XCHG     szOID_RSA_RSA

//+-------------------------------------------------------------------------
//  Information stored in a certificate
//
//  The Issuer, Subject, Algorithm, PublicKey and Extension BLOBs are the
//  encoded representation of the information.
//--------------------------------------------------------------------------
typedef struct _CERT_INFO {
    DWORD                       dwVersion;
    CRYPT_INTEGER_BLOB          SerialNumber;
    CRYPT_ALGORITHM_IDENTIFIER  SignatureAlgorithm;
    CERT_NAME_BLOB              Issuer;
    FILETIME                    NotBefore;
    FILETIME                    NotAfter;
    CERT_NAME_BLOB              Subject;
    CERT_PUBLIC_KEY_INFO        SubjectPublicKeyInfo;
    CRYPT_BIT_BLOB              IssuerUniqueId;
    CRYPT_BIT_BLOB              SubjectUniqueId;
    DWORD                       cExtension;
    PCERT_EXTENSION             rgExtension;
} CERT_INFO, *PCERT_INFO;

//+-------------------------------------------------------------------------
//  Certificate versions
//--------------------------------------------------------------------------
#define CERT_V1     0
#define CERT_V2     1
#define CERT_V3     2

//+-------------------------------------------------------------------------
//  Certificate Information Flags
//--------------------------------------------------------------------------
#define CERT_INFO_VERSION_FLAG                      1
#define CERT_INFO_SERIAL_NUMBER_FLAG                2
#define CERT_INFO_SIGNATURE_ALGORITHM_FLAG          3
#define CERT_INFO_ISSUER_FLAG                       4
#define CERT_INFO_NOT_BEFORE_FLAG                   5
#define CERT_INFO_NOT_AFTER_FLAG                    6
#define CERT_INFO_SUBJECT_FLAG                      7
#define CERT_INFO_SUBJECT_PUBLIC_KEY_INFO_FLAG      8
#define CERT_INFO_ISSUER_UNIQUE_ID_FLAG             9
#define CERT_INFO_SUBJECT_UNIQUE_ID_FLAG            10
#define CERT_INFO_EXTENSION_FLAG                    11

//+-------------------------------------------------------------------------
//  An entry in a CRL
//
//  The Extension BLOBs are the encoded representation of the information.
//--------------------------------------------------------------------------
typedef struct _CRL_ENTRY {
    CRYPT_INTEGER_BLOB  SerialNumber;
    FILETIME            RevocationDate;
    DWORD               cExtension;
    PCERT_EXTENSION     rgExtension;
} CRL_ENTRY, *PCRL_ENTRY;

//+-------------------------------------------------------------------------
//  Information stored in a CRL
//
//  The Issuer, Algorithm and Extension BLOBs are the encoded
//  representation of the information.
//--------------------------------------------------------------------------
typedef struct _CRL_INFO {
    DWORD                       dwVersion;
    CRYPT_ALGORITHM_IDENTIFIER  SignatureAlgorithm;
    CERT_NAME_BLOB              Issuer;
    FILETIME                    ThisUpdate;
    FILETIME                    NextUpdate;
    DWORD                       cCRLEntry;
    PCRL_ENTRY                  rgCRLEntry;
    DWORD                       cExtension;
    PCERT_EXTENSION             rgExtension;
} CRL_INFO, *PCRL_INFO;

//+-------------------------------------------------------------------------
//  CRL versions
//--------------------------------------------------------------------------
#define CRL_V1     0
#define CRL_V2     1


//+-------------------------------------------------------------------------
//  Information stored in a certificate request
//
//  The Subject, Algorithm, PublicKey and Attribute BLOBs are the encoded
//  representation of the information.
//--------------------------------------------------------------------------
typedef struct _CERT_REQUEST_INFO {
    DWORD                   dwVersion;
    CERT_NAME_BLOB          Subject;
    CERT_PUBLIC_KEY_INFO    SubjectPublicKeyInfo;
    DWORD                   cAttribute;
    PCRYPT_ATTRIBUTE        rgAttribute;
} CERT_REQUEST_INFO, *PCERT_REQUEST_INFO;

//+-------------------------------------------------------------------------
//  Certificate Request versions
//--------------------------------------------------------------------------
#define CERT_REQUEST_V1     0

//+-------------------------------------------------------------------------
//  Information stored in Netscape's Keygen request
//--------------------------------------------------------------------------
typedef struct _CERT_KEYGEN_REQUEST_INFO {
    DWORD                   dwVersion;
    CERT_PUBLIC_KEY_INFO    SubjectPublicKeyInfo;
    LPWSTR                  pwszChallengeString;        // encoded as IA5
} CERT_KEYGEN_REQUEST_INFO, *PCERT_KEYGEN_REQUEST_INFO;

#define CERT_KEYGEN_REQUEST_V1     0


//+-------------------------------------------------------------------------
//  Certificate, CRL, Certificate Request or Keygen Request Signed Content
//
//  The "to be signed" encoded content plus its signature. The ToBeSigned
//  is the encoded CERT_INFO, CRL_INFO, CERT_REQUEST_INFO or
//  CERT_KEYGEN_REQUEST_INFO.
//--------------------------------------------------------------------------
typedef struct _CERT_SIGNED_CONTENT_INFO {
    CRYPT_DER_BLOB              ToBeSigned;
    CRYPT_ALGORITHM_IDENTIFIER  SignatureAlgorithm;
    CRYPT_BIT_BLOB              Signature;
} CERT_SIGNED_CONTENT_INFO, *PCERT_SIGNED_CONTENT_INFO;


//+-------------------------------------------------------------------------
//  Certificate Trust List (CTL)
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CTL Usage. Also used for EnhancedKeyUsage extension.
//--------------------------------------------------------------------------
typedef struct _CTL_USAGE {
    DWORD               cUsageIdentifier;
    LPSTR               *rgpszUsageIdentifier;      // array of pszObjId
} CTL_USAGE, *PCTL_USAGE,
  CERT_ENHKEY_USAGE, *PCERT_ENHKEY_USAGE;


//+-------------------------------------------------------------------------
//  An entry in a CTL
//--------------------------------------------------------------------------
typedef struct _CTL_ENTRY {
    CRYPT_DATA_BLOB     SubjectIdentifier;          // For example, its hash
    DWORD               cAttribute;
    PCRYPT_ATTRIBUTE    rgAttribute;                // OPTIONAL
} CTL_ENTRY, *PCTL_ENTRY;

//+-------------------------------------------------------------------------
//  Information stored in a CTL
//--------------------------------------------------------------------------
typedef struct _CTL_INFO {
    DWORD                       dwVersion;
    CTL_USAGE                   SubjectUsage;
    CRYPT_DATA_BLOB             ListIdentifier;     // OPTIONAL
    CRYPT_INTEGER_BLOB          SequenceNumber;     // OPTIONAL
    FILETIME                    ThisUpdate;
    FILETIME                    NextUpdate;         // OPTIONAL
    CRYPT_ALGORITHM_IDENTIFIER  SubjectAlgorithm;
    DWORD                       cCTLEntry;
    PCTL_ENTRY                  rgCTLEntry;         // OPTIONAL
    DWORD                       cExtension;
    PCERT_EXTENSION             rgExtension;        // OPTIONAL
} CTL_INFO, *PCTL_INFO;

//+-------------------------------------------------------------------------
//  CTL versions
//--------------------------------------------------------------------------
#define CTL_V1     0


//+-------------------------------------------------------------------------
//  TimeStamp Request
//
//  The pszTimeStamp is the OID for the Time type requested
//  The pszContentType is the Content Type OID for the content, usually DATA
//  The Content is a un-decoded blob
//--------------------------------------------------------------------------
typedef struct _CRYPT_TIME_STAMP_REQUEST_INFO {
    LPSTR                   pszTimeStampAlgorithm;   // pszObjId
    LPSTR                   pszContentType;          // pszObjId
    CRYPT_OBJID_BLOB        Content;
    DWORD                   cAttribute;
    PCRYPT_ATTRIBUTE        rgAttribute;
} CRYPT_TIME_STAMP_REQUEST_INFO, *PCRYPT_TIME_STAMP_REQUEST_INFO;

//+-------------------------------------------------------------------------
//  Certificate and Message encoding types
//
//  The encoding type is a DWORD containing both the certificate and message
//  encoding types. The certificate encoding type is stored in the LOWORD.
//  The message encoding type is stored in the HIWORD. Some functions or
//  structure fields require only one of the encoding types. The following
//  naming convention is used to indicate which encoding type(s) are
//  required:
//      dwEncodingType              (both encoding types are required)
//      dwMsgAndCertEncodingType    (both encoding types are required)
//      dwMsgEncodingType           (only msg encoding type is required)
//      dwCertEncodingType          (only cert encoding type is required)
//
//  Its always acceptable to specify both.
//--------------------------------------------------------------------------
#define CERT_ENCODING_TYPE_MASK     0x0000FFFF
#define CMSG_ENCODING_TYPE_MASK     0xFFFF0000
#define GET_CERT_ENCODING_TYPE(X)   (X & CERT_ENCODING_TYPE_MASK)
#define GET_CMSG_ENCODING_TYPE(X)   (X & CMSG_ENCODING_TYPE_MASK)

#define CRYPT_ASN_ENCODING          0x00000001
#define CRYPT_NDR_ENCODING          0x00000002
#define X509_ASN_ENCODING           0x00000001
#define X509_NDR_ENCODING           0x00000002
#define PKCS_7_ASN_ENCODING         0x00010000
#define PKCS_7_NDR_ENCODING         0x00020000


//+-------------------------------------------------------------------------
//  format the specified data structure according to the certificate
//  encoding type.
//
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CryptFormatObject(
    IN DWORD dwCertEncodingType,
    IN DWORD dwFormatType,
	IN DWORD dwFormatStrType,
	IN void	 *pFormatStruct,
    IN LPCSTR lpszStructType,
    IN const BYTE *pbEncoded,
    IN DWORD cbEncoded,
	OUT void *pbFormat,
    IN OUT DWORD *pcbFormat
    );

//+-------------------------------------------------------------------------
//  Encode / decode the specified data structure according to the certificate
//  encoding type.
//
//  See below for a list of the predefined data structures.
//--------------------------------------------------------------------------


WINCRYPT32API
BOOL
WINAPI
CryptEncodeObject(
    IN DWORD        dwCertEncodingType,
    IN LPCSTR       lpszStructType,
    IN const void   *pvStructInfo,
    OUT BYTE        *pbEncoded,
    IN OUT DWORD    *pcbEncoded
    );

WINCRYPT32API
BOOL
WINAPI
CryptDecodeObject(
    IN DWORD        dwCertEncodingType,
    IN LPCSTR       lpszStructType,
    IN const BYTE   *pbEncoded,
    IN DWORD        cbEncoded,
    IN DWORD        dwFlags,
    OUT void        *pvStructInfo,
    IN OUT DWORD    *pcbStructInfo
    );

// When the following flag is set the nocopy optimization is enabled.
// This optimization where appropriate, updates the pvStructInfo fields
// to point to content residing within pbEncoded instead of making a copy
// of and appending to pvStructInfo.
//
// Note, when set, pbEncoded can't be freed until pvStructInfo is freed.
#define CRYPT_DECODE_NOCOPY_FLAG            0x1

//+-------------------------------------------------------------------------
//  Predefined X509 certificate data structures that can be encoded / decoded.
//--------------------------------------------------------------------------
#define CRYPT_ENCODE_DECODE_NONE            0
#define X509_CERT                           ((LPCSTR) 1)
#define X509_CERT_TO_BE_SIGNED              ((LPCSTR) 2)
#define X509_CERT_CRL_TO_BE_SIGNED          ((LPCSTR) 3)
#define X509_CERT_REQUEST_TO_BE_SIGNED      ((LPCSTR) 4)
#define X509_EXTENSIONS                     ((LPCSTR) 5)
#define X509_NAME_VALUE                     ((LPCSTR) 6)
#define X509_NAME                           ((LPCSTR) 7)
#define X509_PUBLIC_KEY_INFO                ((LPCSTR) 8)

//+-------------------------------------------------------------------------
//  Predefined X509 certificate extension data structures that can be
//  encoded / decoded.
//--------------------------------------------------------------------------
#define X509_AUTHORITY_KEY_ID               ((LPCSTR) 9)
#define X509_KEY_ATTRIBUTES                 ((LPCSTR) 10)
#define X509_KEY_USAGE_RESTRICTION          ((LPCSTR) 11)
#define X509_ALTERNATE_NAME                 ((LPCSTR) 12)
#define X509_BASIC_CONSTRAINTS              ((LPCSTR) 13)
#define X509_KEY_USAGE                      ((LPCSTR) 14)
#define X509_BASIC_CONSTRAINTS2             ((LPCSTR) 15)
#define X509_CERT_POLICIES                  ((LPCSTR) 16)

//+-------------------------------------------------------------------------
//  Additional predefined data structures that can be encoded / decoded.
//--------------------------------------------------------------------------
#define PKCS_UTC_TIME                       ((LPCSTR) 17)
#define PKCS_TIME_REQUEST                   ((LPCSTR) 18)
#define RSA_CSP_PUBLICKEYBLOB               ((LPCSTR) 19)
#define X509_UNICODE_NAME                   ((LPCSTR) 20)

#define X509_KEYGEN_REQUEST_TO_BE_SIGNED    ((LPCSTR) 21)
#define PKCS_ATTRIBUTE                      ((LPCSTR) 22)
#define PKCS_CONTENT_INFO_SEQUENCE_OF_ANY   ((LPCSTR) 23)

//+-------------------------------------------------------------------------
//  Predefined primitive data structures that can be encoded / decoded.
//--------------------------------------------------------------------------
#define X509_UNICODE_NAME_VALUE             ((LPCSTR) 24)
#define X509_ANY_STRING                     X509_NAME_VALUE
#define X509_UNICODE_ANY_STRING             X509_UNICODE_NAME_VALUE
#define X509_OCTET_STRING                   ((LPCSTR) 25)
#define X509_BITS                           ((LPCSTR) 26)
#define X509_INTEGER                        ((LPCSTR) 27)
#define X509_MULTI_BYTE_INTEGER             ((LPCSTR) 28)
#define X509_ENUMERATED                     ((LPCSTR) 29)
#define X509_CHOICE_OF_TIME                 ((LPCSTR) 30)

//+-------------------------------------------------------------------------
//  More predefined X509 certificate extension data structures that can be
//  encoded / decoded.
//--------------------------------------------------------------------------
#define X509_AUTHORITY_KEY_ID2              ((LPCSTR) 31)
//#define X509_AUTHORITY_INFO_ACCESS          ((LPCSTR) 32)
#define X509_CRL_REASON_CODE                X509_ENUMERATED
#define PKCS_CONTENT_INFO                   ((LPCSTR) 33)
#define X509_SEQUENCE_OF_ANY                ((LPCSTR) 34)
#define X509_CRL_DIST_POINTS                ((LPCSTR) 35)
#define X509_ENHANCED_KEY_USAGE             ((LPCSTR) 36)
#define PKCS_CTL                            ((LPCSTR) 37)

#define X509_MULTI_BYTE_UINT                ((LPCSTR) 38)
#define X509_DSS_PUBLICKEY                  X509_MULTI_BYTE_UINT
#define X509_DSS_PARAMETERS                 ((LPCSTR) 39)
#define X509_DSS_SIGNATURE                  ((LPCSTR) 40)
#define PKCS_RC2_CBC_PARAMETERS             ((LPCSTR) 41)
#define PKCS_SMIME_CAPABILITIES             ((LPCSTR) 42)


//+-------------------------------------------------------------------------
//  Predefined PKCS #7 data structures that can be encoded / decoded.
//--------------------------------------------------------------------------
#define PKCS7_SIGNER_INFO                   ((LPCSTR) 500)

//+-------------------------------------------------------------------------
//  Predefined Software Publishing Credential (SPC)  data structures that
//  can be encoded / decoded.
//
//  Predefined values: 2000 .. 2999
//
//  See spc.h for value and data structure definitions.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  Extension Object Identifiers
//--------------------------------------------------------------------------
#define szOID_AUTHORITY_KEY_IDENTIFIER  "2.5.29.1"
#define szOID_KEY_ATTRIBUTES            "2.5.29.2"
#define szOID_KEY_USAGE_RESTRICTION     "2.5.29.4"
#define szOID_SUBJECT_ALT_NAME          "2.5.29.7"
#define szOID_ISSUER_ALT_NAME           "2.5.29.8"
#define szOID_BASIC_CONSTRAINTS         "2.5.29.10"
#define szOID_KEY_USAGE                 "2.5.29.15"
#define szOID_BASIC_CONSTRAINTS2        "2.5.29.19"
#define szOID_CERT_POLICIES             "2.5.29.32"

#define szOID_AUTHORITY_KEY_IDENTIFIER2 "2.5.29.35"
#define szOID_SUBJECT_KEY_IDENTIFIER    "2.5.29.14"
#define szOID_SUBJECT_ALT_NAME2         "2.5.29.17"
#define szOID_ISSUER_ALT_NAME2          "2.5.29.18"
#define szOID_CRL_REASON_CODE           "2.5.29.21"
#define szOID_CRL_DIST_POINTS           "2.5.29.31"
#define szOID_ENHANCED_KEY_USAGE        "2.5.29.37"


// Internet Public Key Infrastructure
#define szOID_PKIX                      "1.3.6.1.5.5.7"
#define szOID_AUTHORITY_INFO_ACCESS     "1.3.6.1.5.5.7.2"

// Microsoft extensions or attributes
#define szOID_CERT_EXTENSIONS           "1.3.6.1.4.1.311.2.1.14"
#define szOID_NEXT_UPDATE_LOCATION      "1.3.6.1.4.1.311.10.2"

//  Microsoft PKCS #7 ContentType Object Identifiers
#define szOID_CTL                       "1.3.6.1.4.1.311.10.1"

//+-------------------------------------------------------------------------
//  Extension Object Identifiers (currently not implemented)
//--------------------------------------------------------------------------
#define szOID_POLICY_MAPPINGS           "2.5.29.5"
#define szOID_SUBJECT_DIR_ATTRS         "2.5.29.9"

//+-------------------------------------------------------------------------
//  Enhanced Key Usage (Purpose) Object Identifiers
//--------------------------------------------------------------------------
#define szOID_PKIX_KP                   "1.3.6.1.5.5.7.3"

// Consistent key usage bits: DIGITAL_SIGNATURE, KEY_ENCIPHERMENT
// or KEY_AGREEMENT
#define szOID_PKIX_KP_SERVER_AUTH       "1.3.6.1.5.5.7.3.1"

// Consistent key usage bits: DIGITAL_SIGNATURE
#define szOID_PKIX_KP_CLIENT_AUTH       "1.3.6.1.5.5.7.3.2"

// Consistent key usage bits: DIGITAL_SIGNATURE
#define szOID_PKIX_KP_CODE_SIGNING      "1.3.6.1.5.5.7.3.3"

// Consistent key usage bits: DIGITAL_SIGNATURE, NON_REPUDIATION and/or
// (KEY_ENCIPHERMENT or KEY_AGREEMENT)
#define szOID_PKIX_KP_EMAIL_PROTECTION  "1.3.6.1.5.5.7.3.4"

//+-------------------------------------------------------------------------
//  Microsoft Enhanced Key Usage (Purpose) Object Identifiers
//+-------------------------------------------------------------------------

//  Signer of CTLs
#define szOID_KP_CTL_USAGE_SIGNING      "1.3.6.1.4.1.311.10.3.1"

//  Signer of TimeStamps
#define szOID_KP_TIME_STAMP_SIGNING         "1.3.6.1.4.1.311.10.3.2"

//+-------------------------------------------------------------------------
//  Microsoft Attribute Object Identifiers
//+-------------------------------------------------------------------------
#define szOID_YESNO_TRUST_ATTR          "1.3.6.1.4.1.311.10.4.1"

//+-------------------------------------------------------------------------
//  X509_CERT
//
//  The "to be signed" encoded content plus its signature. The ToBeSigned
//  content is the CryptEncodeObject() output for one of the following:
//  X509_CERT_TO_BE_SIGNED, X509_CERT_CRL_TO_BE_SIGNED or
//  X509_CERT_REQUEST_TO_BE_SIGNED.
//
//  pvStructInfo points to CERT_SIGNED_CONTENT_INFO.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  X509_CERT_TO_BE_SIGNED
//
//  pvStructInfo points to CERT_INFO.
//
//  For CryptDecodeObject(), the pbEncoded is the "to be signed" plus its
//  signature (output of a X509_CERT CryptEncodeObject()).
//
//  For CryptEncodeObject(), the pbEncoded is just the "to be signed".
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  X509_CERT_CRL_TO_BE_SIGNED
//
//  pvStructInfo points to CRL_INFO.
//
//  For CryptDecodeObject(), the pbEncoded is the "to be signed" plus its
//  signature (output of a X509_CERT CryptEncodeObject()).
//
//  For CryptEncodeObject(), the pbEncoded is just the "to be signed".
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  X509_CERT_REQUEST_TO_BE_SIGNED
//
//  pvStructInfo points to CERT_REQUEST_INFO.
//
//  For CryptDecodeObject(), the pbEncoded is the "to be signed" plus its
//  signature (output of a X509_CERT CryptEncodeObject()).
//
//  For CryptEncodeObject(), the pbEncoded is just the "to be signed".
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  X509_EXTENSIONS
//  szOID_CERT_EXTENSIONS
//
//  pvStructInfo points to following CERT_EXTENSIONS.
//--------------------------------------------------------------------------
typedef struct _CERT_EXTENSIONS {
    DWORD           cExtension;
    PCERT_EXTENSION rgExtension;
} CERT_EXTENSIONS, *PCERT_EXTENSIONS;

//+-------------------------------------------------------------------------
//  X509_NAME_VALUE
//  X509_ANY_STRING
//
//  pvStructInfo points to CERT_NAME_VALUE.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  X509_UNICODE_NAME_VALUE
//  X509_UNICODE_ANY_STRING
//
//  pvStructInfo points to CERT_NAME_VALUE.
//
//  The name values are unicode strings.
//
//  For CryptEncodeObject:
//    Value.pbData points to the unicode string.
//    If Value.cbData = 0, then, the unicode string is NULL terminated.
//    Otherwise, Value.cbData is the unicode string byte count. The byte count
//    is twice the character count.
//
//    If the unicode string contains an invalid character for the specified
//    dwValueType, then, *pcbEncoded is updated with the unicode character
//    index of the first invalid character. LastError is set to:
//    CRYPT_E_INVALID_NUMERIC_STRING, CRYPT_E_INVALID_PRINTABLE_STRING or
//    CRYPT_E_INVALID_IA5_STRING.
//
//    The unicode string is converted before being encoded according to
//    the specified dwValueType. If dwValueType is set to 0, LastError
//    is set to E_INVALIDARG.
//
//    If the dwValueType isn't one of the character strings (its a
//    CERT_RDN_ENCODED_BLOB or CERT_RDN_OCTET_STRING), then, CryptEncodeObject
//    will return FALSE with LastError set to CRYPT_E_NOT_CHAR_STRING.
//
//  For CryptDecodeObject:
//    Value.pbData points to a NULL terminated unicode string. Value.cbData
//    contains the byte count of the unicode string excluding the NULL
//    terminator. dwValueType contains the type used in the encoded object.
//    Its not forced to CERT_RDN_UNICODE_STRING. The encoded value is
//    converted to the unicode string according to the dwValueType.
//
//    If the encoded object isn't one of the character string types, then,
//    CryptDecodeObject will return FALSE with LastError set to
//    CRYPT_E_NOT_CHAR_STRING. For a non character string, decode using
//    X509_NAME_VALUE or X509_ANY_STRING.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  X509_NAME
//
//  pvStructInfo points to CERT_NAME_INFO.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  X509_UNICODE_NAME
//
//  pvStructInfo points to CERT_NAME_INFO.
//
//  The RDN attribute values are unicode strings except for the dwValueTypes of
//  CERT_RDN_ENCODED_BLOB or CERT_RDN_OCTET_STRING. These dwValueTypes are
//  the same as for a X509_NAME. Their values aren't converted to/from unicode.
//
//  For CryptEncodeObject:
//    Value.pbData points to the unicode string.
//    If Value.cbData = 0, then, the unicode string is NULL terminated.
//    Otherwise, Value.cbData is the unicode string byte count. The byte count
//    is twice the character count.
//
//    If dwValueType = 0 (CERT_RDN_ANY_TYPE), the pszObjId is used to find
//    an acceptable dwValueType. If the unicode string contains an
//    invalid character for the found or specified dwValueType, then,
//    *pcbEncoded is updated with the error location of the invalid character.
//    See below for details. LastError is set to:
//    CRYPT_E_INVALID_NUMERIC_STRING, CRYPT_E_INVALID_PRINTABLE_STRING or
//    CRYPT_E_INVALID_IA5_STRING.
//
//    The unicode string is converted before being encoded according to
//    the specified or ObjId matching dwValueType.
//
//  For CryptDecodeObject:
//    Value.pbData points to a NULL terminated unicode string. Value.cbData
//    contains the byte count of the unicode string excluding the NULL
//    terminator. dwValueType contains the type used in the encoded object.
//    Its not forced to CERT_RDN_UNICODE_STRING. The encoded value is
//    converted to the unicode string according to the dwValueType.
//
//    If the dwValueType of the encoded value isn't a character string
//    type, then, it isn't converted to UNICODE. Use the
//    IS_CERT_RDN_CHAR_STRING() macro on the dwValueType to check
//    that Value.pbData points to a converted unicode string.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  Unicode Name Value Error Location Definitions
//
//  Error location is returned in *pcbEncoded by
//  CryptEncodeObject(X509_UNICODE_NAME)
//
//  Error location consists of:
//    RDN_INDEX     - 10 bits << 22
//    ATTR_INDEX    - 6 bits << 16
//    VALUE_INDEX   - 16 bits (unicode character index)
//--------------------------------------------------------------------------
#define CERT_UNICODE_RDN_ERR_INDEX_MASK     0x3FF
#define CERT_UNICODE_RDN_ERR_INDEX_SHIFT    22
#define CERT_UNICODE_ATTR_ERR_INDEX_MASK    0x003F
#define CERT_UNICODE_ATTR_ERR_INDEX_SHIFT   16
#define CERT_UNICODE_VALUE_ERR_INDEX_MASK   0x0000FFFF
#define CERT_UNICODE_VALUE_ERR_INDEX_SHIFT  0

#define GET_CERT_UNICODE_RDN_ERR_INDEX(X)   \
    ((X >> CERT_UNICODE_RDN_ERR_INDEX_SHIFT) & CERT_UNICODE_RDN_ERR_INDEX_MASK)
#define GET_CERT_UNICODE_ATTR_ERR_INDEX(X)  \
    ((X >> CERT_UNICODE_ATTR_ERR_INDEX_SHIFT) & CERT_UNICODE_ATTR_ERR_INDEX_MASK)
#define GET_CERT_UNICODE_VALUE_ERR_INDEX(X) \
    (X & CERT_UNICODE_VALUE_ERR_INDEX_MASK)

//+-------------------------------------------------------------------------
//  X509_PUBLIC_KEY_INFO
//
//  pvStructInfo points to CERT_PUBLIC_KEY_INFO.
//--------------------------------------------------------------------------


//+-------------------------------------------------------------------------
//  X509_AUTHORITY_KEY_ID
//  szOID_AUTHORITY_KEY_IDENTIFIER
//
//  pvStructInfo points to following CERT_AUTHORITY_KEY_ID_INFO.
//--------------------------------------------------------------------------
typedef struct _CERT_AUTHORITY_KEY_ID_INFO {
    CRYPT_DATA_BLOB     KeyId;
    CERT_NAME_BLOB      CertIssuer;
    CRYPT_INTEGER_BLOB  CertSerialNumber;
} CERT_AUTHORITY_KEY_ID_INFO, *PCERT_AUTHORITY_KEY_ID_INFO;

//+-------------------------------------------------------------------------
//  X509_KEY_ATTRIBUTES
//  szOID_KEY_ATTRIBUTES
//
//  pvStructInfo points to following CERT_KEY_ATTRIBUTES_INFO.
//--------------------------------------------------------------------------
typedef struct _CERT_PRIVATE_KEY_VALIDITY {
    FILETIME                NotBefore;
    FILETIME                NotAfter;
} CERT_PRIVATE_KEY_VALIDITY, *PCERT_PRIVATE_KEY_VALIDITY;

typedef struct _CERT_KEY_ATTRIBUTES_INFO {
    CRYPT_DATA_BLOB             KeyId;
    CRYPT_BIT_BLOB              IntendedKeyUsage;
    PCERT_PRIVATE_KEY_VALIDITY  pPrivateKeyUsagePeriod;     // OPTIONAL
} CERT_KEY_ATTRIBUTES_INFO, *PCERT_KEY_ATTRIBUTES_INFO;

#define CERT_DIGITAL_SIGNATURE_KEY_USAGE     0x80
#define CERT_NON_REPUDIATION_KEY_USAGE       0x40
#define CERT_KEY_ENCIPHERMENT_KEY_USAGE      0x20
#define CERT_DATA_ENCIPHERMENT_KEY_USAGE     0x10
#define CERT_KEY_AGREEMENT_KEY_USAGE         0x08
#define CERT_KEY_CERT_SIGN_KEY_USAGE         0x04
#define CERT_OFFLINE_CRL_SIGN_KEY_USAGE      0x02

#define CERT_CRL_SIGN_KEY_USAGE              0x02

//+-------------------------------------------------------------------------
//  X509_KEY_USAGE_RESTRICTION
//  szOID_KEY_USAGE_RESTRICTION
//
//  pvStructInfo points to following CERT_KEY_USAGE_RESTRICTION_INFO.
//--------------------------------------------------------------------------
typedef struct _CERT_POLICY_ID {
    DWORD                   cCertPolicyElementId;
    LPSTR                   *rgpszCertPolicyElementId;  // pszObjId
} CERT_POLICY_ID, *PCERT_POLICY_ID;

typedef struct _CERT_KEY_USAGE_RESTRICTION_INFO {
    DWORD                   cCertPolicyId;
    PCERT_POLICY_ID         rgCertPolicyId;
    CRYPT_BIT_BLOB          RestrictedKeyUsage;
} CERT_KEY_USAGE_RESTRICTION_INFO, *PCERT_KEY_USAGE_RESTRICTION_INFO;

// See CERT_KEY_ATTRIBUTES_INFO for definition of the RestrictedKeyUsage bits

//+-------------------------------------------------------------------------
//  X509_ALTERNATE_NAME
//  szOID_SUBJECT_ALT_NAME
//  szOID_ISSUER_ALT_NAME
//  szOID_SUBJECT_ALT_NAME2
//  szOID_ISSUER_ALT_NAME2
//
//  pvStructInfo points to following CERT_ALT_NAME_INFO.
//--------------------------------------------------------------------------

typedef struct _CERT_ALT_NAME_ENTRY {
    DWORD   dwAltNameChoice;
    union {
        // Not implemented          OtherName;          // 1
        LPWSTR                      pwszRfc822Name;     // 2  (encoded IA5)
        LPWSTR                      pwszDNSName;        // 3  (encoded IA5)
        // Not implemented          x400Address;        // 4
        CERT_NAME_BLOB              DirectoryName;      // 5
        // Not implemented          pEdiPartyName;      // 6
        LPWSTR                      pwszURL;            // 7  (encoded IA5)
        CRYPT_DATA_BLOB             IPAddress;          // 8  (Octet String)
        LPSTR                       pszRegisteredID;    // 9  (Object Identifer)
    };
} CERT_ALT_NAME_ENTRY, *PCERT_ALT_NAME_ENTRY;

#define CERT_ALT_NAME_OTHER_NAME         1
#define CERT_ALT_NAME_RFC822_NAME        2
#define CERT_ALT_NAME_DNS_NAME           3
#define CERT_ALT_NAME_X400_ADDRESS       4
#define CERT_ALT_NAME_DIRECTORY_NAME     5
#define CERT_ALT_NAME_EDI_PARTY_NAME     6
#define CERT_ALT_NAME_URL                7
#define CERT_ALT_NAME_IP_ADDRESS         8
#define CERT_ALT_NAME_REGISTERED_ID      9


typedef struct _CERT_ALT_NAME_INFO {
    DWORD                   cAltEntry;
    PCERT_ALT_NAME_ENTRY    rgAltEntry;
} CERT_ALT_NAME_INFO, *PCERT_ALT_NAME_INFO;

//+-------------------------------------------------------------------------
//  Alternate name IA5 Error Location Definitions for
//  CRYPT_E_INVALID_IA5_STRING.
//
//  Error location is returned in *pcbEncoded by
//  CryptEncodeObject(X509_ALTERNATE_NAME)
//
//  Error location consists of:
//    ENTRY_INDEX   - 8 bits << 16
//    VALUE_INDEX   - 16 bits (unicode character index)
//--------------------------------------------------------------------------
#define CERT_ALT_NAME_ENTRY_ERR_INDEX_MASK  0xFF
#define CERT_ALT_NAME_ENTRY_ERR_INDEX_SHIFT 16
#define CERT_ALT_NAME_VALUE_ERR_INDEX_MASK  0x0000FFFF
#define CERT_ALT_NAME_VALUE_ERR_INDEX_SHIFT 0

#define GET_CERT_ALT_NAME_ENTRY_ERR_INDEX(X)   \
    ((X >> CERT_ALT_NAME_ENTRY_ERR_INDEX_SHIFT) & \
    CERT_ALT_NAME_ENTRY_ERR_INDEX_MASK)
#define GET_CERT_ALT_NAME_VALUE_ERR_INDEX(X) \
    (X & CERT_ALT_NAME_VALUE_ERR_INDEX_MASK)


//+-------------------------------------------------------------------------
//  X509_BASIC_CONSTRAINTS
//  szOID_BASIC_CONSTRAINTS
//
//  pvStructInfo points to following CERT_BASIC_CONSTRAINTS_INFO.
//--------------------------------------------------------------------------
typedef struct _CERT_BASIC_CONSTRAINTS_INFO {
    CRYPT_BIT_BLOB          SubjectType;
    BOOL                    fPathLenConstraint;
    DWORD                   dwPathLenConstraint;
    DWORD                   cSubtreesConstraint;
    CERT_NAME_BLOB          *rgSubtreesConstraint;
} CERT_BASIC_CONSTRAINTS_INFO, *PCERT_BASIC_CONSTRAINTS_INFO;

#define CERT_CA_SUBJECT_FLAG         0x80
#define CERT_END_ENTITY_SUBJECT_FLAG 0x40

//+-------------------------------------------------------------------------
//  X509_BASIC_CONSTRAINTS2
//  szOID_BASIC_CONSTRAINTS2
//
//  pvStructInfo points to following CERT_BASIC_CONSTRAINTS2_INFO.
//--------------------------------------------------------------------------
typedef struct _CERT_BASIC_CONSTRAINTS2_INFO {
    BOOL                    fCA;
    BOOL                    fPathLenConstraint;
    DWORD                   dwPathLenConstraint;
} CERT_BASIC_CONSTRAINTS2_INFO, *PCERT_BASIC_CONSTRAINTS2_INFO;

//+-------------------------------------------------------------------------
//  X509_KEY_USAGE
//  szOID_KEY_USAGE
//
//  pvStructInfo points to a CRYPT_BIT_BLOB. Has same bit definitions as
//  CERT_KEY_ATTRIBUTES_INFO's IntendedKeyUsage.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  X509_CERT_POLICIES
//  szOID_CERT_POLICIES
//
//  pvStructInfo points to following CERT_POLICIES_INFO.
//--------------------------------------------------------------------------
typedef struct _CERT_POLICY_QUALIFIER_INFO {
    LPSTR                       pszPolicyQualifierId;   // pszObjId
    CRYPT_OBJID_BLOB            Qualifier;              // optional
} CERT_POLICY_QUALIFIER_INFO, *PCERT_POLICY_QUALIFIER_INFO;

typedef struct _CERT_POLICY_INFO {
    LPSTR                       pszPolicyIdentifier;    // pszObjId
    DWORD                       cPolicyQualifier;       // optional
    CERT_POLICY_QUALIFIER_INFO  *rgPolicyQualifier;
} CERT_POLICY_INFO, *PCERT_POLICY_INFO;

typedef struct _CERT_POLICIES_INFO {
    DWORD                       cPolicyInfo;
    CERT_POLICY_INFO            *rgPolicyInfo;
} CERT_POLICIES_INFO, *PCERT_POLICIES_INFO;

//+-------------------------------------------------------------------------
//  RSA_CSP_PUBLICKEYBLOB
//
//  pvStructInfo points to a PUBLICKEYSTRUC immediately followed by a
//  RSAPUBKEY and the modulus bytes.
//
//  CryptExportKey outputs the above StructInfo for a dwBlobType of
//  PUBLICKEYBLOB. CryptImportKey expects the above StructInfo when
//  importing a public key.
//
//  For dwCertEncodingType = X509_ASN_ENCODING, the RSA_CSP_PUBLICKEYBLOB is
//  encoded as a PKCS #1 RSAPublicKey consisting of a SEQUENCE of a
//  modulus INTEGER and a publicExponent INTEGER. The modulus is encoded
//  as being a unsigned integer. When decoded, if the modulus was encoded
//  as unsigned integer with a leading 0 byte, the 0 byte is removed before
//  converting to the CSP modulus bytes.
//
//  For decode, the aiKeyAlg field of PUBLICKEYSTRUC is always set to
//  CALG_RSA_KEYX.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  X509_KEYGEN_REQUEST_TO_BE_SIGNED
//
//  pvStructInfo points to CERT_KEYGEN_REQUEST_INFO.
//
//  For CryptDecodeObject(), the pbEncoded is the "to be signed" plus its
//  signature (output of a X509_CERT CryptEncodeObject()).
//
//  For CryptEncodeObject(), the pbEncoded is just the "to be signed".
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  PKCS_ATTRIBUTE data structure
//
//  pvStructInfo points to a CRYPT_ATTRIBUTE.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  PKCS_CONTENT_INFO_SEQUENCE_OF_ANY data structure
//
//  pvStructInfo points to following CRYPT_CONTENT_INFO_SEQUENCE_OF_ANY.
//
//  For X509_ASN_ENCODING: encoded as a PKCS#7 ContentInfo structure wrapping
//  a sequence of ANY. The value of the contentType field is pszObjId,
//  while the content field is the following structure:
//      SequenceOfAny ::= SEQUENCE OF ANY
//
//  The CRYPT_DER_BLOBs point to the already encoded ANY content.
//--------------------------------------------------------------------------
typedef struct _CRYPT_CONTENT_INFO_SEQUENCE_OF_ANY {
    LPSTR               pszObjId;
    DWORD               cValue;
    PCRYPT_DER_BLOB     rgValue;
} CRYPT_CONTENT_INFO_SEQUENCE_OF_ANY, *PCRYPT_CONTENT_INFO_SEQUENCE_OF_ANY;

//+-------------------------------------------------------------------------
//  PKCS_CONTENT_INFO data structure
//
//  pvStructInfo points to following CRYPT_CONTENT_INFO.
//
//  For X509_ASN_ENCODING: encoded as a PKCS#7 ContentInfo structure.
//  The CRYPT_DER_BLOB points to the already encoded ANY content.
//--------------------------------------------------------------------------
typedef struct _CRYPT_CONTENT_INFO {
    LPSTR               pszObjId;
    CRYPT_DER_BLOB      Content;
} CRYPT_CONTENT_INFO, *PCRYPT_CONTENT_INFO;


//+-------------------------------------------------------------------------
//  X509_OCTET_STRING data structure
//
//  pvStructInfo points to a CRYPT_DATA_BLOB.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  X509_BITS data structure
//
//  pvStructInfo points to a CRYPT_BIT_BLOB.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  X509_INTEGER data structure
//
//  pvStructInfo points to an int.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  X509_MULTI_BYTE_INTEGER data structure
//
//  pvStructInfo points to a CRYPT_INTEGER_BLOB.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  X509_ENUMERATED data structure
//
//  pvStructInfo points to an int containing the enumerated value
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  X509_CHOICE_OF_TIME data structure
//
//  pvStructInfo points to a FILETIME.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  X509_SEQUENCE_OF_ANY data structure
//
//  pvStructInfo points to following CRYPT_SEQUENCE_OF_ANY.
//
//  The CRYPT_DER_BLOBs point to the already encoded ANY content.
//--------------------------------------------------------------------------
typedef struct _CRYPT_SEQUENCE_OF_ANY {
    DWORD               cValue;
    PCRYPT_DER_BLOB     rgValue;
} CRYPT_SEQUENCE_OF_ANY, *PCRYPT_SEQUENCE_OF_ANY;


//+-------------------------------------------------------------------------
//  X509_AUTHORITY_KEY_ID2
//  szOID_AUTHORITY_KEY_IDENTIFIER2
//
//  pvStructInfo points to following CERT_AUTHORITY_KEY_ID2_INFO.
//
//  For CRYPT_E_INVALID_IA5_STRING, the error location is returned in
//  *pcbEncoded by CryptEncodeObject(X509_AUTHORITY_KEY_ID2)
//
//  See X509_ALTERNATE_NAME for error location defines.
//--------------------------------------------------------------------------
typedef struct _CERT_AUTHORITY_KEY_ID2_INFO {
    CRYPT_DATA_BLOB     KeyId;
    CERT_ALT_NAME_INFO  AuthorityCertIssuer;    // Optional, set cAltEntry
                                                // to 0 to omit.
    CRYPT_INTEGER_BLOB  AuthorityCertSerialNumber;
} CERT_AUTHORITY_KEY_ID2_INFO, *PCERT_AUTHORITY_KEY_ID2_INFO;

//+-------------------------------------------------------------------------
//  szOID_SUBJECT_KEY_IDENTIFIER
//
//  pvStructInfo points to a CRYPT_DATA_BLOB.
//--------------------------------------------------------------------------


//+-------------------------------------------------------------------------
//  X509_CRL_REASON_CODE
//  szOID_CRL_REASON_CODE
//
//  pvStructInfo points to an int which can be set to one of the following
//  enumerated values:
//--------------------------------------------------------------------------
#define CRL_REASON_UNSPECIFIED              0
#define CRL_REASON_KEY_COMPROMISE           1
#define CRL_REASON_CA_COMPROMISE            2
#define CRL_REASON_AFFILIATION_CHANGED      3
#define CRL_REASON_SUPERSEDED               4
#define CRL_REASON_CESSATION_OF_OPERATION   5
#define CRL_REASON_CERTIFICATE_HOLD         6
#define CRL_REASON_REMOVE_FROM_CRL          8


//+-------------------------------------------------------------------------
//  X509_CRL_DIST_POINTS
//  szOID_CRL_DIST_POINTS
//
//  pvStructInfo points to following CRL_DIST_POINTS_INFO.
//
//  For CRYPT_E_INVALID_IA5_STRING, the error location is returned in
//  *pcbEncoded by CryptEncodeObject(X509_CRL_DIST_POINTS)
//
//  Error location consists of:
//    CRL_ISSUER_BIT    - 1 bit  << 31 (0 for FullName, 1 for CRLIssuer)
//    POINT_INDEX       - 7 bits << 24
//    ENTRY_INDEX       - 8 bits << 16
//    VALUE_INDEX       - 16 bits (unicode character index)
//
//  See X509_ALTERNATE_NAME for ENTRY_INDEX and VALUE_INDEX error location
//  defines.
//--------------------------------------------------------------------------
typedef struct _CRL_DIST_POINT_NAME {
    DWORD   dwDistPointNameChoice;
    union {
        CERT_ALT_NAME_INFO      FullName;       // 1
        // Not implemented      IssuerRDN;      // 2
    };
} CRL_DIST_POINT_NAME, *PCRL_DIST_POINT_NAME;

#define CRL_DIST_POINT_NO_NAME          0
#define CRL_DIST_POINT_FULL_NAME        1
#define CRL_DIST_POINT_ISSUER_RDN_NAME  2

typedef struct _CRL_DIST_POINT {
    CRL_DIST_POINT_NAME     DistPointName;      // OPTIONAL
    CRYPT_BIT_BLOB          ReasonFlags;        // OPTIONAL
    CERT_ALT_NAME_INFO      CRLIssuer;          // OPTIONAL
} CRL_DIST_POINT, *PCRL_DIST_POINT;

#define CRL_REASON_UNUSED_FLAG                  0x80
#define CRL_REASON_KEY_COMPROMISE_FLAG          0x40
#define CRL_REASON_CA_COMPROMISE_FLAG           0x20
#define CRL_REASON_AFFILIATION_CHANGED_FLAG     0x10
#define CRL_REASON_SUPERSEDED_FLAG              0x08
#define CRL_REASON_CESSATION_OF_OPERATION_FLAG  0x04
#define CRL_REASON_CERTIFICATE_HOLD_FLAG        0x02

typedef struct _CRL_DIST_POINTS_INFO {
    DWORD                   cDistPoint;
    PCRL_DIST_POINT         rgDistPoint;
} CRL_DIST_POINTS_INFO, *PCRL_DIST_POINTS_INFO;

#define CRL_DIST_POINT_ERR_INDEX_MASK          0x7F
#define CRL_DIST_POINT_ERR_INDEX_SHIFT         24
#define GET_CRL_DIST_POINT_ERR_INDEX(X)   \
    ((X >> CRL_DIST_POINT_ERR_INDEX_SHIFT) & CRL_DIST_POINT_ERR_INDEX_MASK)

#define CRL_DIST_POINT_ERR_CRL_ISSUER_BIT      0x80000000L
#define IS_CRL_DIST_POINT_ERR_CRL_ISSUER(X)   \
    (0 != (X & CRL_DIST_POINT_ERR_CRL_ISSUER_BIT))


//+-------------------------------------------------------------------------
//  X509_ENHANCED_KEY_USAGE
//  szOID_ENHANCED_KEY_USAGE
//
//  pvStructInfo points to a CERT_ENHKEY_USAGE, CTL_USAGE.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  szOID_NEXT_UPDATE_LOCATION
//
//  pvStructInfo points to a CERT_ALT_NAME_INFO.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  PKCS_CTL
//  szOID_CTL
//
//  pvStructInfo points to a CTL_INFO.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  X509_MULTI_BYTE_UINT
//
//  pvStructInfo points to a CRYPT_UINT_BLOB. Before encoding, inserts a
//  leading 0x00. After decoding, removes a leading 0x00.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  X509_DSS_PUBLICKEY
//
//  pvStructInfo points to a CRYPT_UINT_BLOB.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  X509_DSS_PARAMETERS
//
//  pvStructInfo points to following CERT_DSS_PARAMETERS data structure.
//--------------------------------------------------------------------------
typedef struct _CERT_DSS_PARAMETERS {
    CRYPT_UINT_BLOB     p;
    CRYPT_UINT_BLOB     q;
    CRYPT_UINT_BLOB     g;
} CERT_DSS_PARAMETERS, *PCERT_DSS_PARAMETERS;

//+-------------------------------------------------------------------------
//  X509_DSS_SIGNATURE
//
//  pvStructInfo is a BYTE rgbSignature[CERT_DSS_SIGNATURE_LEN]. The
//  bytes are ordered as output by the DSS CSP's CryptSignHash().
//--------------------------------------------------------------------------
#define CERT_DSS_R_LEN          20      
#define CERT_DSS_S_LEN          20      
#define CERT_DSS_SIGNATURE_LEN  (CERT_DSS_R_LEN + CERT_DSS_S_LEN)

// Sequence of 2 unsigned integers (the extra +1 is for a potential leading
// 0x00 to make the integer unsigned)
#define CERT_MAX_ASN_ENCODED_DSS_SIGNATURE_LEN  (2 + 2*(2 + 20 +1))


//+-------------------------------------------------------------------------
//  PKCS_RC2_CBC_PARAMETERS
//  szOID_RSA_RC2CBC
//
//  pvStructInfo points to following CRYPT_RC2_CBC_PARAMETERS data structure.
//--------------------------------------------------------------------------
typedef struct _CRYPT_RC2_CBC_PARAMETERS {
    DWORD               dwVersion;
    BOOL                fIV;            // set if has following IV
    BYTE                rgbIV[8];
} CRYPT_RC2_CBC_PARAMETERS, *PCRYPT_RC2_CBC_PARAMETERS;

#define CRYPT_RC2_40BIT_VERSION     160
#define CRYPT_RC2_64BIT_VERSION     120
#define CRYPT_RC2_128BIT_VERSION    58


//+-------------------------------------------------------------------------
//  PKCS_SMIME_CAPABILITIES
//  szOID_RSA_SMIMECapabilities
//
//  pvStructInfo points to following CRYPT_SMIME_CAPABILITIES data structure.
//
//  Note, for CryptEncodeObject(X509_ASN_ENCODING), Parameters.cbData == 0
//  causes the encoded parameters to be omitted and not encoded as a NULL
//  (05 00) as is done when encoding a CRYPT_ALGORITHM_IDENTIFIER. This
//  is per the SMIME specification for encoding capabilities.
//--------------------------------------------------------------------------
typedef struct _CRYPT_SMIME_CAPABILITY {
    LPSTR               pszObjId;
    CRYPT_OBJID_BLOB    Parameters;
} CRYPT_SMIME_CAPABILITY, *PCRYPT_SMIME_CAPABILITY;

typedef struct _CRYPT_SMIME_CAPABILITIES {
    DWORD                   cCapability;
    PCRYPT_SMIME_CAPABILITY rgCapability;
} CRYPT_SMIME_CAPABILITIES, *PCRYPT_SMIME_CAPABILITIES;


//+-------------------------------------------------------------------------
//  PKCS7_SIGNER_INFO
//
//  pvStructInfo points to CMSG_SIGNER_INFO.
//--------------------------------------------------------------------------


//+-------------------------------------------------------------------------
//  Netscape Certificate Extension Object Identifiers
//--------------------------------------------------------------------------
#define szOID_NETSCAPE                  "2.16.840.1.113730"
#define szOID_NETSCAPE_CERT_EXTENSION   "2.16.840.1.113730.1"
#define szOID_NETSCAPE_CERT_TYPE        "2.16.840.1.113730.1.1"
#define szOID_NETSCAPE_BASE_URL         "2.16.840.1.113730.1.2"
#define szOID_NETSCAPE_REVOCATION_URL   "2.16.840.1.113730.1.3"
#define szOID_NETSCAPE_CA_REVOCATION_URL "2.16.840.1.113730.1.4"
#define szOID_NETSCAPE_CERT_RENEWAL_URL "2.16.840.1.113730.1.7"
#define szOID_NETSCAPE_CA_POLICY_URL    "2.16.840.1.113730.1.8"
#define szOID_NETSCAPE_SSL_SERVER_NAME  "2.16.840.1.113730.1.12"
#define szOID_NETSCAPE_COMMENT          "2.16.840.1.113730.1.13"

//+-------------------------------------------------------------------------
//  Netscape Certificate Data Type Object Identifiers
//--------------------------------------------------------------------------
#define szOID_NETSCAPE_DATA_TYPE        "2.16.840.1.113730.2"
#define szOID_NETSCAPE_CERT_SEQUENCE    "2.16.840.1.113730.2.5"


//+-------------------------------------------------------------------------
//  szOID_NETSCAPE_CERT_TYPE extension
//
//  Its value is a bit string. CryptDecodeObject/CryptEncodeObject using
//  X509_BITS.
//
//  The following bits are defined:
//--------------------------------------------------------------------------
#define NETSCAPE_SSL_CLIENT_AUTH_CERT_TYPE  0x80
#define NETSCAPE_SSL_SERVER_AUTH_CERT_TYPE  0x40
#define NETSCAPE_SSL_CA_CERT_TYPE           0x04

//+-------------------------------------------------------------------------
//  szOID_NETSCAPE_BASE_URL extension
//
//  Its value is an IA5_STRING. CryptDecodeObject/CryptEncodeObject using
//  X509_ANY_STRING or X509_UNICODE_ANY_STRING, where,
//  dwValueType = CERT_RDN_IA5_STRING.
//
//  When present this string is added to the beginning of all relative URLs
//  in the certificate.  This extension can be considered an optimization
//  to reduce the size of the URL extensions.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  szOID_NETSCAPE_REVOCATION_URL extension
//
//  Its value is an IA5_STRING. CryptDecodeObject/CryptEncodeObject using
//  X509_ANY_STRING or X509_UNICODE_ANY_STRING, where,
//  dwValueType = CERT_RDN_IA5_STRING.
//
//  It is a relative or absolute URL that can be used to check the
//  revocation status of a certificate. The revocation check will be
//  performed as an HTTP GET method using a url that is the concatenation of
//  revocation-url and certificate-serial-number.
//  Where the certificate-serial-number is encoded as a string of
//  ascii hexadecimal digits. For example, if the netscape-base-url is
//  https://www.certs-r-us.com/, the netscape-revocation-url is
//  cgi-bin/check-rev.cgi?, and the certificate serial number is 173420,
//  the resulting URL would be:
//  https://www.certs-r-us.com/cgi-bin/check-rev.cgi?02a56c
//
//  The server should return a document with a Content-Type of
//  application/x-netscape-revocation.  The document should contain
//  a single ascii digit, '1' if the certificate is not curently valid,
//  and '0' if it is curently valid.
//
//  Note: for all of the URLs that include the certificate serial number,
//  the serial number will be encoded as a string which consists of an even
//  number of hexadecimal digits.  If the number of significant digits is odd,
//  the string will have a single leading zero to ensure an even number of
//  digits is generated.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  szOID_NETSCAPE_CA_REVOCATION_URL extension
//
//  Its value is an IA5_STRING. CryptDecodeObject/CryptEncodeObject using
//  X509_ANY_STRING or X509_UNICODE_ANY_STRING, where,
//  dwValueType = CERT_RDN_IA5_STRING.
//
//  It is a relative or absolute URL that can be used to check the
//  revocation status of any certificates that are signed by the CA that
//  this certificate belongs to. This extension is only valid in CA
//  certificates.  The use of this extension is the same as the above
//  szOID_NETSCAPE_REVOCATION_URL extension.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  szOID_NETSCAPE_CERT_RENEWAL_URL extension
//
//  Its value is an IA5_STRING. CryptDecodeObject/CryptEncodeObject using
//  X509_ANY_STRING or X509_UNICODE_ANY_STRING, where,
//  dwValueType = CERT_RDN_IA5_STRING.
//
//  It is a relative or absolute URL that points to a certificate renewal
//  form. The renewal form will be accessed with an HTTP GET method using a
//  url that is the concatenation of renewal-url and
//  certificate-serial-number. Where the certificate-serial-number is
//  encoded as a string of ascii hexadecimal digits. For example, if the
//  netscape-base-url is https://www.certs-r-us.com/, the
//  netscape-cert-renewal-url is cgi-bin/check-renew.cgi?, and the
//  certificate serial number is 173420, the resulting URL would be:
//  https://www.certs-r-us.com/cgi-bin/check-renew.cgi?02a56c
//  The document returned should be an HTML form that will allow the user
//  to request a renewal of their certificate.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  szOID_NETSCAPE_CA_POLICY_URL extension
//
//  Its value is an IA5_STRING. CryptDecodeObject/CryptEncodeObject using
//  X509_ANY_STRING or X509_UNICODE_ANY_STRING, where,
//  dwValueType = CERT_RDN_IA5_STRING.
//
//  It is a relative or absolute URL that points to a web page that
//  describes the policies under which the certificate was issued.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  szOID_NETSCAPE_SSL_SERVER_NAME extension
//
//  Its value is an IA5_STRING. CryptDecodeObject/CryptEncodeObject using
//  X509_ANY_STRING or X509_UNICODE_ANY_STRING, where,
//  dwValueType = CERT_RDN_IA5_STRING.
//
//  It is a "shell expression" that can be used to match the hostname of the
//  SSL server that is using this certificate.  It is recommended that if
//  the server's hostname does not match this pattern the user be notified
//  and given the option to terminate the SSL connection.  If this extension
//  is not present then the CommonName in the certificate subject's
//  distinguished name is used for the same purpose.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  szOID_NETSCAPE_COMMENT extension
//
//  Its value is an IA5_STRING. CryptDecodeObject/CryptEncodeObject using
//  X509_ANY_STRING or X509_UNICODE_ANY_STRING, where,
//  dwValueType = CERT_RDN_IA5_STRING.
//
//  It is a comment that may be displayed to the user when the certificate
//  is viewed.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  szOID_NETSCAPE_CERT_SEQUENCE
//
//  Its value is a PKCS#7 ContentInfo structure wrapping a sequence of
//  certificates. The value of the contentType field is
//  szOID_NETSCAPE_CERT_SEQUENCE, while the content field is the following
//  structure:
//      CertificateSequence ::= SEQUENCE OF Certificate.
//
//  CryptDecodeObject/CryptEncodeObject using
//  PKCS_CONTENT_INFO_SEQUENCE_OF_ANY, where,
//  pszObjId = szOID_NETSCAPE_CERT_SEQUENCE and the CRYPT_DER_BLOBs point
//  to encoded X509 certificates.
//--------------------------------------------------------------------------


//+=========================================================================
//  Object IDentifier (OID) Installable Functions:  Data Structures and APIs
//==========================================================================

typedef void *HCRYPTOIDFUNCSET;
typedef void *HCRYPTOIDFUNCADDR;

// Predefined OID Function Names
#define CRYPT_OID_ENCODE_OBJECT_FUNC        "CryptDllEncodeObject"
#define CRYPT_OID_DECODE_OBJECT_FUNC        "CryptDllDecodeObject"
#define CRYPT_OID_CREATE_COM_OBJECT_FUNC    "CryptDllCreateCOMObject"
#define CRYPT_OID_VERIFY_REVOCATION_FUNC    "CertDllVerifyRevocation"
#define CRYPT_OID_VERIFY_CTL_USAGE_FUNC     "CertDllVerifyCTLUsage"
#define CRYPT_OID_FORMAT_OBJECT_FUNC		"CryptDllFormatObject"
#define CRYPT_OID_FIND_OID_INFO_FUNC        "CryptDllFindOIDInfo"

// CryptDllEncodeObject has same function signature as CryptEncodeObject.

// CryptDllDecodeObject has same function signature as CryptDecodeObject.

// CryptDllCreateCOMObject has the following signature:
//      BOOL WINAPI CryptDllCreateCOMObject(
//          IN DWORD dwEncodingType,
//          IN LPCSTR pszOID,
//          IN PCRYPT_DATA_BLOB pEncodedContent,
//          IN DWORD dwFlags,
//          IN REFIID riid,
//          OUT void **ppvObj);

// CertDllVerifyRevocation has the same signature as CertVerifyRevocation
//  (See CertVerifyRevocation for details on when called)

// CertDllVerifyCTLUsage has the same signature as CertVerifyCTLUsage

// CryptDllFindOIDInfo currently is only used to store values used by
// CryptFindOIDInfo. See CryptFindOIDInfo() for more details.

//  Example of a complete OID Function Registry Name:
//    HKEY_LOCAL_MACHINE\Software\Microsoft\Cryptography\OID
//      Encoding Type 1\CryptDllEncodeObject\1.2.3
//
//  The key's L"Dll" value contains the name of the Dll.
//  The key's L"FuncName" value overrides the default function name
#define CRYPT_OID_REGPATH "Software\\Microsoft\\Cryptography\\OID"
#define CRYPT_OID_REG_ENCODING_TYPE_PREFIX  "EncodingType "
#define CRYPT_OID_REG_DLL_VALUE_NAME        L"Dll"
#define CRYPT_OID_REG_FUNC_NAME_VALUE_NAME  L"FuncName"
#define CRYPT_OID_REG_FUNC_NAME_VALUE_NAME_A "FuncName"

// OID used for Default OID functions
#define CRYPT_DEFAULT_OID                   "DEFAULT"

typedef struct _CRYPT_OID_FUNC_ENTRY {
    LPCSTR  pszOID;
    void    *pvFuncAddr;
} CRYPT_OID_FUNC_ENTRY, *PCRYPT_OID_FUNC_ENTRY;


#define CRYPT_INSTALL_OID_FUNC_BEFORE_FLAG  1

//+-------------------------------------------------------------------------
//  Install a set of callable OID function addresses.
//
//  By default the functions are installed at end of the list.
//  Set CRYPT_INSTALL_OID_FUNC_BEFORE_FLAG to install at beginning of list.
//
//  hModule should be updated with the hModule passed to DllMain to prevent
//  the Dll containing the function addresses from being unloaded by
//  CryptGetOIDFuncAddress/CryptFreeOIDFunctionAddress. This would be the
//  case when the Dll has also regsvr32'ed OID functions via
//  CryptRegisterOIDFunction.
//
//  DEFAULT functions are installed by setting rgFuncEntry[].pszOID =
//  CRYPT_DEFAULT_OID.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CryptInstallOIDFunctionAddress(
    IN HMODULE hModule,         // hModule passed to DllMain
    IN DWORD dwEncodingType,
    IN LPCSTR pszFuncName,
    IN DWORD cFuncEntry,
    IN const CRYPT_OID_FUNC_ENTRY rgFuncEntry[],
    IN DWORD dwFlags
    );

//+-------------------------------------------------------------------------
//  Initialize and return handle to the OID function set identified by its
//  function name.
//
//  If the set already exists, a handle to the existing set is returned.
//--------------------------------------------------------------------------
WINCRYPT32API
HCRYPTOIDFUNCSET
WINAPI
CryptInitOIDFunctionSet(
    IN LPCSTR pszFuncName,
    IN DWORD dwFlags
    );

//+-------------------------------------------------------------------------
//  Search the list of installed functions for an encoding type and OID match.
//  If not found, search the registry.
//
//  For success, returns TRUE with *ppvFuncAddr updated with the function's
//  address and *phFuncAddr updated with the function address's handle.
//  The function's handle is AddRef'ed. CryptFreeOIDFunctionAddress needs to
//  be called to release it.
//
//  For a registry match, the Dll containing the function is loaded.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CryptGetOIDFunctionAddress(
    IN HCRYPTOIDFUNCSET hFuncSet,
    IN DWORD dwEncodingType,
    IN LPCSTR pszOID,
    IN DWORD dwFlags,
    OUT void **ppvFuncAddr,
    OUT HCRYPTOIDFUNCADDR *phFuncAddr
    );


//+-------------------------------------------------------------------------
//  Get the list of registered default Dll entries for the specified
//  function set and encoding type.
//
//  The returned list consists of none, one or more null terminated Dll file
//  names. The list is terminated with an empty (L"\0") Dll file name.
//  For example: L"first.dll" L"\0" L"second.dll" L"\0" L"\0"
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CryptGetDefaultOIDDllList(
    IN HCRYPTOIDFUNCSET hFuncSet,
    IN DWORD dwEncodingType,
    OUT LPWSTR pwszDllList,
    IN OUT DWORD *pcchDllList
    );

//+-------------------------------------------------------------------------
//  Either: get the first or next installed DEFAULT function OR
//  load the Dll containing the DEFAULT function.
//
//  If pwszDll is NULL, search the list of installed DEFAULT functions.
//  *phFuncAddr must be set to NULL to get the first installed function.
//  Successive installed functions are returned by setting *phFuncAddr
//  to the hFuncAddr returned by the previous call.
//
//  If pwszDll is NULL, the input *phFuncAddr
//  is always CryptFreeOIDFunctionAddress'ed by this function, even for
//  an error.
//
//  If pwszDll isn't NULL, then, attempts to load the Dll and the DEFAULT
//  function. *phFuncAddr is ignored upon entry and isn't
//  CryptFreeOIDFunctionAddress'ed.
//
//  For success, returns TRUE with *ppvFuncAddr updated with the function's
//  address and *phFuncAddr updated with the function address's handle.
//  The function's handle is AddRef'ed. CryptFreeOIDFunctionAddress needs to
//  be called to release it or CryptGetDefaultOIDFunctionAddress can also
//  be called for a NULL pwszDll.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CryptGetDefaultOIDFunctionAddress(
    IN HCRYPTOIDFUNCSET hFuncSet,
    IN DWORD dwEncodingType,
    IN OPTIONAL LPCWSTR pwszDll,
    IN DWORD dwFlags,
    OUT void **ppvFuncAddr,
    IN OUT HCRYPTOIDFUNCADDR *phFuncAddr
    );

//+-------------------------------------------------------------------------
//  Releases the handle AddRef'ed and returned by CryptGetOIDFunctionAddress
//  or CryptGetDefaultOIDFunctionAddress.
//
//  If a Dll was loaded for the function its unloaded. However, before doing
//  the unload, the DllCanUnloadNow function exported by the loaded Dll is
//  called. It should return S_FALSE to inhibit the unload or S_TRUE to enable
//  the unload. If the Dll doesn't export DllCanUnloadNow, the Dll is unloaded.
//
//  DllCanUnloadNow has the following signature:
//      STDAPI  DllCanUnloadNow(void);
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CryptFreeOIDFunctionAddress(
    IN HCRYPTOIDFUNCADDR hFuncAddr,
    IN DWORD dwFlags
    );

//+-------------------------------------------------------------------------
//  Register the Dll containing the function to be called for the specified
//  encoding type, function name and OID.
//
//  pwszDll may contain environment-variable strings
//  which are ExpandEnvironmentStrings()'ed before loading the Dll.
//
//  In addition to registering the DLL, you may override the
//  name of the function to be called. For example,
//      pszFuncName = "CryptDllEncodeObject",
//      pszOverrideFuncName = "MyEncodeXyz".
//  This allows a Dll to export multiple OID functions for the same
//  function name without needing to interpose its own OID dispatcher function.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CryptRegisterOIDFunction(
    IN DWORD dwEncodingType,
    IN LPCSTR pszFuncName,
    IN LPCSTR pszOID,
    IN OPTIONAL LPCWSTR pwszDll,
    IN OPTIONAL LPCSTR pszOverrideFuncName
    );

//+-------------------------------------------------------------------------
//  Unregister the Dll containing the function to be called for the specified
//  encoding type, function name and OID.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CryptUnregisterOIDFunction(
    IN DWORD dwEncodingType,
    IN LPCSTR pszFuncName,
    IN LPCSTR pszOID
    );


//+-------------------------------------------------------------------------
//  Register the Dll containing the default function to be called for the
//  specified encoding type and function name.
//
//  Unlike CryptRegisterOIDFunction, you can't override the function name
//  needing to be exported by the Dll.
//
//  The Dll is inserted before the entry specified by dwIndex.
//    dwIndex == 0, inserts at the beginning.
//    dwIndex == CRYPT_REGISTER_LAST_INDEX, appends at the end.
//
//  pwszDll may contain environment-variable strings
//  which are ExpandEnvironmentStrings()'ed before loading the Dll.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CryptRegisterDefaultOIDFunction(
    IN DWORD dwEncodingType,
    IN LPCSTR pszFuncName,
    IN DWORD dwIndex,
    IN LPCWSTR pwszDll
    );

#define CRYPT_REGISTER_FIRST_INDEX   0
#define CRYPT_REGISTER_LAST_INDEX    0xFFFFFFFF

//+-------------------------------------------------------------------------
//  Unregister the Dll containing the default function to be called for
//  the specified encoding type and function name.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CryptUnregisterDefaultOIDFunction(
    IN DWORD dwEncodingType,
    IN LPCSTR pszFuncName,
    IN LPCWSTR pwszDll
    );

//+-------------------------------------------------------------------------
//  Set the value for the specified encoding type, function name, OID and
//  value name.
//
//  See RegSetValueEx for the possible value types.
//
//  String types are UNICODE.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CryptSetOIDFunctionValue(
    IN DWORD dwEncodingType,
    IN LPCSTR pszFuncName,
    IN LPCSTR pszOID,
    IN LPCWSTR pwszValueName,
    IN DWORD dwValueType,
    IN const BYTE *pbValueData,
    IN DWORD cbValueData
    );

//+-------------------------------------------------------------------------
//  Get the value for the specified encoding type, function name, OID and
//  value name.
//
//  See RegEnumValue for the possible value types.
//
//  String types are UNICODE.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CryptGetOIDFunctionValue(
    IN DWORD dwEncodingType,
    IN LPCSTR pszFuncName,
    IN LPCSTR pszOID,
    IN LPCWSTR pwszValueName,
    OUT DWORD *pdwValueType,
    OUT BYTE *pbValueData,
    IN OUT DWORD *pcbValueData
    );

typedef BOOL (WINAPI *PFN_CRYPT_ENUM_OID_FUNC)(
        IN DWORD dwEncodingType,
        IN LPCSTR pszFuncName,
        IN LPCSTR pszOID,
        IN DWORD cValue,
        IN const DWORD rgdwValueType[],
        IN LPCWSTR const rgpwszValueName[],
        IN const BYTE * const rgpbValueData[],
        IN const DWORD rgcbValueData[],
        IN void *pvArg
        );

//+-------------------------------------------------------------------------
//  Enumerate the OID functions identified by their encoding type,
//  function name and OID.
//
//  pfnEnumOIDFunc is called for each registry key matching the input
//  parameters. Setting dwEncodingType to CRYPT_MATCH_ANY_ENCODING_TYPE matches
//  any. Setting pszFuncName or pszOID to NULL matches any.
//
//  Set pszOID == CRYPT_DEFAULT_OID to restrict the enumeration to only the
//  DEFAULT functions
//
//  String types are UNICODE.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CryptEnumOIDFunction(
    IN DWORD dwEncodingType,
    IN OPTIONAL LPCSTR pszFuncName,
    IN OPTIONAL LPCSTR pszOID,
    IN DWORD dwFlags,
    IN void *pvArg,
    IN PFN_CRYPT_ENUM_OID_FUNC pfnEnumOIDFunc
    );

#define CRYPT_MATCH_ANY_ENCODING_TYPE   0xFFFFFFFF


//+=========================================================================
//  Object IDentifier (OID) Information:  Data Structures and APIs
//==========================================================================

//+-------------------------------------------------------------------------
//  OID Information
//--------------------------------------------------------------------------
typedef struct _CRYPT_OID_INFO {
    DWORD               cbSize;
    LPCSTR              pszOID;
    LPCWSTR             pwszName;
    DWORD               dwGroupId;
    union {
        DWORD               dwValue;
        ALG_ID              Algid;
        DWORD               dwLength;
    };
    CRYPT_DATA_BLOB     ExtraInfo;
} CRYPT_OID_INFO, *PCRYPT_OID_INFO;
typedef const CRYPT_OID_INFO CCRYPT_OID_INFO, *PCCRYPT_OID_INFO;

//+-------------------------------------------------------------------------
//  OID Group IDs
//--------------------------------------------------------------------------
#define CRYPT_HASH_ALG_OID_GROUP_ID             1
#define CRYPT_ENCRYPT_ALG_OID_GROUP_ID          2
#define CRYPT_PUBKEY_ALG_OID_GROUP_ID           3
#define CRYPT_SIGN_ALG_OID_GROUP_ID             4
#define CRYPT_RDN_ATTR_OID_GROUP_ID             5
#define CRYPT_EXT_OR_ATTR_OID_GROUP_ID          6
#define CRYPT_ENHKEY_USAGE_OID_GROUP_ID         7
#define CRYPT_POLICY_OID_GROUP_ID               8
#define CRYPT_LAST_OID_GROUP_ID                 8

#define CRYPT_FIRST_ALG_OID_GROUP_ID            CRYPT_HASH_ALG_OID_GROUP_ID
#define CRYPT_LAST_ALG_OID_GROUP_ID             CRYPT_SIGN_ALG_OID_GROUP_ID


// The CRYPT_*_ALG_OID_GROUP_ID's have an Algid. The CRYPT_RDN_ATTR_OID_GROUP_ID
// has a dwLength. The CRYPT_EXT_OR_ATTR_OID_GROUP_ID,
// CRYPT_ENHKEY_USAGE_OID_GROUP_ID or CRYPT_POLICY_OID_GROUP_ID don't have a
// dwValue.
//

// CRYPT_PUBKEY_ALG_OID_GROUP_ID has the following optional ExtraInfo:
//  DWORD[0] - Flags. CRYPT_OID_INHIBIT_SIGNATURE_FORMAT_FLAG can be set to
//             inhibit the reformatting of the signature before
//             CryptVerifySignature is called or after CryptSignHash
//             is called. CRYPT_OID_USE_PUBKEY_PARA_FOR_PKCS7_FLAG can
//             be set to include the public key algorithm's parameters
//             in the PKCS7's digestEncryptionAlgorithm's parameters.

#define CRYPT_OID_INHIBIT_SIGNATURE_FORMAT_FLAG     0x1
#define CRYPT_OID_USE_PUBKEY_PARA_FOR_PKCS7_FLAG    0x2

// CRYPT_SIGN_ALG_OID_GROUP_ID has the following optional ExtraInfo:
//  DWORD[0] - Public Key Algid.
//  DWORD[1] - Flags. Same as above for CRYPT_PUBKEY_ALG_OID_GROUP_ID.

// CRYPT_RDN_ATTR_OID_GROUP_ID has the following optional ExtraInfo:
//  Array of DWORDs:
//   [0 ..] - Null terminated list of acceptable RDN attribute
//            value types. An empty list implies CERT_RDN_PRINTABLE_STRING,
//            CERT_RDN_T61_STRING, 0.

//+-------------------------------------------------------------------------
//  Find OID information. Returns NULL if unable to find any information
//  for the specified key and group. Note, returns a pointer to a constant
//  data structure. The returned pointer MUST NOT be freed.
//
//  dwKeyType's:
//    CRYPT_OID_INFO_OID_KEY, pvKey points to a szOID
//    CRYPT_OID_INFO_NAME_KEY, pvKey points to a wszName
//    CRYPT_OID_INFO_ALGID_KEY, pvKey points to an ALG_ID
//    CRYPT_OID_INFO_SIGN_KEY, pvKey points to an array of two ALG_ID's:
//      ALG_ID[0] - Hash Algid
//      ALG_ID[1] - PubKey Algid
//
//  Setting dwGroupId to 0, searches all groups according to the dwKeyType.
//  Otherwise, only the dwGroupId is searched.
//--------------------------------------------------------------------------
WINCRYPT32API
PCCRYPT_OID_INFO
WINAPI
CryptFindOIDInfo(
    IN DWORD dwKeyType,
    IN void *pvKey,
    IN DWORD dwGroupId
    );

#define CRYPT_OID_INFO_OID_KEY           1
#define CRYPT_OID_INFO_NAME_KEY          2
#define CRYPT_OID_INFO_ALGID_KEY         3
#define CRYPT_OID_INFO_SIGN_KEY          4

//+-------------------------------------------------------------------------
//  Register OID information. The OID information specified in the
//  CCRYPT_OID_INFO structure is persisted to the registry.
//
//  crypt32.dll contains information for the commonly known OIDs. This function
//  allows applications to augment crypt32.dll's OID information. During
//  CryptFindOIDInfo's first call, the registered OID information is installed.
//
//  By default the registered OID information is installed after crypt32.dll's
//  OID entries. Set CRYPT_INSTALL_OID_INFO_BEFORE_FLAG to install before.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CryptRegisterOIDInfo(
    IN PCCRYPT_OID_INFO pInfo,
    IN DWORD dwFlags
    );

#define CRYPT_INSTALL_OID_INFO_BEFORE_FLAG  1

//+-------------------------------------------------------------------------
//  Unregister OID information. Only the pszOID and dwGroupId fields are
//  used to identify the OID information to be unregistered.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CryptUnregisterOIDInfo(
    IN PCCRYPT_OID_INFO pInfo
    );


//+=========================================================================
//  Low Level Cryptographic Message Data Structures and APIs
//==========================================================================

typedef void *HCRYPTMSG;

#define szOID_PKCS_7_DATA               "1.2.840.113549.1.7.1"
#define szOID_PKCS_7_SIGNED             "1.2.840.113549.1.7.2"
#define szOID_PKCS_7_ENVELOPED          "1.2.840.113549.1.7.3"
#define szOID_PKCS_7_SIGNEDANDENVELOPED "1.2.840.113549.1.7.4"
#define szOID_PKCS_7_DIGESTED           "1.2.840.113549.1.7.5"
#define szOID_PKCS_7_ENCRYPTED          "1.2.840.113549.1.7.6"

#define szOID_PKCS_9_CONTENT_TYPE       "1.2.840.113549.1.9.3"
#define szOID_PKCS_9_MESSAGE_DIGEST     "1.2.840.113549.1.9.4"

//+-------------------------------------------------------------------------
//  Message types
//--------------------------------------------------------------------------
#define CMSG_DATA                    1
#define CMSG_SIGNED                  2
#define CMSG_ENVELOPED               3
#define CMSG_SIGNED_AND_ENVELOPED    4
#define CMSG_HASHED                  5
#define CMSG_ENCRYPTED               6

//+-------------------------------------------------------------------------
//  Message Type Bit Flags
//--------------------------------------------------------------------------
#define CMSG_ALL_FLAGS                   (~0UL)
#define CMSG_DATA_FLAG                   (1 << CMSG_DATA)
#define CMSG_SIGNED_FLAG                 (1 << CMSG_SIGNED)
#define CMSG_ENVELOPED_FLAG              (1 << CMSG_ENVELOPED)
#define CMSG_SIGNED_AND_ENVELOPED_FLAG   (1 << CMSG_SIGNED_AND_ENVELOPED)
#define CMSG_HASHED_FLAG                 (1 << CMSG_HASHED)
#define CMSG_ENCRYPTED_FLAG              (1 << CMSG_ENCRYPTED)

//+-------------------------------------------------------------------------
//  The message encode information (pvMsgEncodeInfo) is message type dependent
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_DATA: pvMsgEncodeInfo = NULL
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_SIGNED
//
//  The pCertInfo in the CMSG_SIGNER_ENCODE_INFO provides the Issuer, SerialNumber
//  and PublicKeyInfo.Algorithm. The PublicKeyInfo.Algorithm implicitly
//  specifies the HashEncryptionAlgorithm to be used.
//
//  The hCryptProv and dwKeySpec specify the private key to use. If dwKeySpec
//  == 0, then, defaults to AT_SIGNATURE.
//
//  pvHashAuxInfo currently isn't used and must be set to NULL.
//--------------------------------------------------------------------------
typedef struct _CMSG_SIGNER_ENCODE_INFO {
    DWORD                       cbSize;
    PCERT_INFO                  pCertInfo;
    HCRYPTPROV                  hCryptProv;
    DWORD                       dwKeySpec;
    CRYPT_ALGORITHM_IDENTIFIER  HashAlgorithm;
    void                        *pvHashAuxInfo;
    DWORD                       cAuthAttr;
    PCRYPT_ATTRIBUTE            rgAuthAttr;
    DWORD                       cUnauthAttr;
    PCRYPT_ATTRIBUTE            rgUnauthAttr;
} CMSG_SIGNER_ENCODE_INFO, *PCMSG_SIGNER_ENCODE_INFO;

typedef struct _CMSG_SIGNED_ENCODE_INFO {
    DWORD                       cbSize;
    DWORD                       cSigners;
    PCMSG_SIGNER_ENCODE_INFO    rgSigners;
    DWORD                       cCertEncoded;
    PCERT_BLOB                  rgCertEncoded;
    DWORD                       cCrlEncoded;
    PCRL_BLOB                   rgCrlEncoded;
} CMSG_SIGNED_ENCODE_INFO, *PCMSG_SIGNED_ENCODE_INFO;

//+-------------------------------------------------------------------------
//  CMSG_ENVELOPED
//
//  The PCERT_INFO for the rgRecipients provides the Issuer, SerialNumber
//  and PublicKeyInfo. The PublicKeyInfo.Algorithm implicitly
//  specifies the KeyEncryptionAlgorithm to be used.
//
//  The PublicKeyInfo.PublicKey in PCERT_INFO is used to encrypt the content
//  encryption key for the recipient.
//
//  hCryptProv is used to do the content encryption, recipient key encryption
//  and export. The hCryptProv's private keys aren't used.
//
//  Note: CAPI currently doesn't support more than one KeyEncryptionAlgorithm
//  per provider. This will need to be fixed.
//
//  pvEncryptionAuxInfo currently isn't used and must be set to NULL.
//--------------------------------------------------------------------------
typedef struct _CMSG_ENVELOPED_ENCODE_INFO {
    DWORD                       cbSize;
    HCRYPTPROV                  hCryptProv;
    CRYPT_ALGORITHM_IDENTIFIER  ContentEncryptionAlgorithm;
    void                        *pvEncryptionAuxInfo;
    DWORD                       cRecipients;
    PCERT_INFO                  *rgpRecipients;
} CMSG_ENVELOPED_ENCODE_INFO, *PCMSG_ENVELOPED_ENCODE_INFO;

//+-------------------------------------------------------------------------
//  CMSG_SIGNED_AND_ENVELOPED
//
//  For PKCS #7, a signed and enveloped message doesn't have the
//  signer's authenticated or unauthenticated attributes. Otherwise, a
//  combination of the CMSG_SIGNED_ENCODE_INFO and CMSG_ENVELOPED_ENCODE_INFO.
//--------------------------------------------------------------------------
typedef struct _CMSG_SIGNED_AND_ENVELOPED_ENCODE_INFO {
    DWORD                       cbSize;
    CMSG_SIGNED_ENCODE_INFO     SignedInfo;
    CMSG_ENVELOPED_ENCODE_INFO  EnvelopedInfo;
} CMSG_SIGNED_AND_ENVELOPED_ENCODE_INFO, *PCMSG_SIGNED_AND_ENVELOPED_ENCODE_INFO;

//+-------------------------------------------------------------------------
//  CMSG_HASHED
//
//  hCryptProv is used to do the hash. Doesn't need to use a private key.
//
//  If fDetachedHash is set, then, the encoded message doesn't contain
//  any content (its treated as NULL Data)
//
//  pvHashAuxInfo currently isn't used and must be set to NULL.
//--------------------------------------------------------------------------
typedef struct _CMSG_HASHED_ENCODE_INFO {
    DWORD                       cbSize;
    HCRYPTPROV                  hCryptProv;
    CRYPT_ALGORITHM_IDENTIFIER  HashAlgorithm;
    void                        *pvHashAuxInfo;
} CMSG_HASHED_ENCODE_INFO, *PCMSG_HASHED_ENCODE_INFO;

//+-------------------------------------------------------------------------
//  CMSG_ENCRYPTED
//
//  The key used to encrypt the message is identified outside of the message
//  content (for example, password).
//
//  The content input to CryptMsgUpdate has already been encrypted.
//
//  pvEncryptionAuxInfo currently isn't used and must be set to NULL.
//--------------------------------------------------------------------------
typedef struct _CMSG_ENCRYPTED_ENCODE_INFO {
    DWORD                       cbSize;
    CRYPT_ALGORITHM_IDENTIFIER  ContentEncryptionAlgorithm;
    void                        *pvEncryptionAuxInfo;
} CMSG_ENCRYPTED_ENCODE_INFO, *PCMSG_ENCRYPTED_ENCODE_INFO;

//+-------------------------------------------------------------------------
//  This parameter allows messages to be of variable length with streamed
//  output.
//
//  By default, messages are of a definite length and
//  CryptMsgGetParam(CMSG_CONTENT_PARAM) is
//  called to get the cryptographically processed content. Until closed,
//  the handle keeps a copy of the processed content.
//
//  With streamed output, the processed content can be freed as its streamed.
//
//  If the length of the content to be updated is known at the time of the
//  open, then, ContentLength should be set to that length. Otherwise, it
//  should be set to CMSG_INDEFINITE_LENGTH.
//--------------------------------------------------------------------------
typedef BOOL (WINAPI *PFN_CMSG_STREAM_OUTPUT)(
        IN const void *pvArg,
        IN BYTE *pbData,
        IN DWORD cbData,
        IN BOOL fFinal
        );

#define CMSG_INDEFINITE_LENGTH       (0xFFFFFFFF)

typedef struct _CMSG_STREAM_INFO {
    DWORD                   cbContent;
    PFN_CMSG_STREAM_OUTPUT  pfnStreamOutput;
    void                    *pvArg;
} CMSG_STREAM_INFO, *PCMSG_STREAM_INFO;

//+-------------------------------------------------------------------------
//  Open dwFlags
//--------------------------------------------------------------------------
#define CMSG_BARE_CONTENT_FLAG              0x00000001
#define CMSG_LENGTH_ONLY_FLAG               0x00000002
#define CMSG_DETACHED_FLAG                  0x00000004
#define CMSG_AUTHENTICATED_ATTRIBUTES_FLAG  0x00000008
#define CMSG_CONTENTS_OCTETS_FLAG           0x00000010
#define CMSG_MAX_LENGTH_FLAG                0x00000020

//+-------------------------------------------------------------------------
//  Open a cryptographic message for encoding
//
//  For PKCS #7:
//  If the content to be passed to CryptMsgUpdate has already
//  been message encoded (the input to CryptMsgUpdate is the streamed output
//  from another message encode), then, the CMSG_ENCODED_CONTENT_INFO_FLAG should
//  be set in dwFlags. If not set, then, the inner ContentType is Data and
//  the input to CryptMsgUpdate is treated as the inner Data type's Content,
//  a string of bytes.
//  If CMSG_BARE_CONTENT_FLAG is specified for a streamed message,
//  the streamed output will not have an outer ContentInfo wrapper. This
//  makes it suitable to be streamed into an enclosing message.
//
//  The pStreamInfo parameter needs to be set to stream the encoded message
//  output.
//--------------------------------------------------------------------------
WINCRYPT32API
HCRYPTMSG
WINAPI
CryptMsgOpenToEncode(
    IN DWORD dwMsgEncodingType,
    IN DWORD dwFlags,
    IN DWORD dwMsgType,
    IN void const *pvMsgEncodeInfo,
    IN OPTIONAL LPSTR pszInnerContentObjID,
    IN OPTIONAL PCMSG_STREAM_INFO pStreamInfo
    );

//+-------------------------------------------------------------------------
//  Calculate the length of an encoded cryptographic message.
//
//  Calculates the length of the encoded message given the
//  message type, encoding parameters and total length of
//  the data to be updated. Note, this might not be the exact length. However,
//  it will always be greater than or equal to the actual length.
//--------------------------------------------------------------------------
WINCRYPT32API
DWORD
WINAPI
CryptMsgCalculateEncodedLength(
    IN DWORD dwMsgEncodingType,
    IN DWORD dwFlags,
    IN DWORD dwMsgType,
    IN void const *pvMsgEncodeInfo,
    IN OPTIONAL LPSTR pszInnerContentObjID,
    IN DWORD cbData
    );

//+-------------------------------------------------------------------------
//  Open a cryptographic message for decoding
//
// These comments need to be changed
//  For PKCS #7: if the inner ContentType isn't Data, then, the inner
//  ContentInfo consisting of both ContentType and Content is output.
//  To also enable ContentInfo output for the Data ContentType, then,
//  the CMSG_ENCODED_CONTENT_INFO_FLAG should be set
//  in dwFlags. If not set, then, only the content portion of the inner
//  ContentInfo is output for the Data ContentType.
//
//  To only calculate the length of the decoded message, set the
//  CMSG_LENGTH_ONLY_FLAG in dwFlags. After the final CryptMsgUpdate get the
//  MSG_CONTENT_PARAM. Note, this might not be the exact length. However,
//  it will always be greater than or equal to the actual length.
//
//  hCryptProv specifies the crypto provider to use for hashing and/or
//  decrypting the message. For enveloped messages, hCryptProv also specifies
//  the private exchange key to use. For signed messages, hCryptProv is used
//  when CryptMsgVerifySigner is called.
//
//  For enveloped messages, the pRecipientInfo contains the Issuer and
//  SerialNumber identifying the RecipientInfo in the message.
//
//  Note, the pRecipientInfo should correspond to the provider's private
//  exchange key.
//
//  If pRecipientInfo is NULL, then, the message isn't decrypted. To decrypt
//  the message, CryptMsgControl(CMSG_CTRL_DECRYPT) is called after the final
//  CryptMsgUpdate.
//
//  The pStreamInfo parameter needs to be set to stream the decoded content
//  output. Note, if pRecipientInfo is NULL, then, the streamed output isn't
//  decrypted.
//--------------------------------------------------------------------------
WINCRYPT32API
HCRYPTMSG
WINAPI
CryptMsgOpenToDecode(
    IN DWORD dwMsgEncodingType,
    IN DWORD dwFlags,
    IN DWORD dwMsgType,
    IN HCRYPTPROV hCryptProv,
    IN OPTIONAL PCERT_INFO pRecipientInfo,
    IN OPTIONAL PCMSG_STREAM_INFO pStreamInfo
    );

//+-------------------------------------------------------------------------
//  Close a cryptographic message handle
//
//  LastError is preserved unless FALSE is returned.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CryptMsgClose(
    IN HCRYPTMSG hCryptMsg
    );

//+-------------------------------------------------------------------------
//  Update the content of a cryptographic message. Depending on how the
//  message was opened, the content is either encoded or decoded.
//
//  This function is repetitively called to append to the message content.
//  fFinal is set to identify the last update. On fFinal, the encode/decode
//  is completed. The encoded/decoded content and the decoded parameters
//  are valid until the open and all duplicated handles are closed.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CryptMsgUpdate(
    IN HCRYPTMSG hCryptMsg,
    IN const BYTE *pbData,
    IN DWORD cbData,
    IN BOOL fFinal
    );

//+-------------------------------------------------------------------------
//  Perform a special "control" function after the final CryptMsgUpdate of a
//  encoded/decoded cryptographic message.
//
//  The dwCtrlType parameter specifies the type of operation to be performed.
//
//  The pvCtrlPara definition depends on the dwCtrlType value.
//
//  See below for a list of the control operations and their pvCtrlPara
//  type definition.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CryptMsgControl(
    IN HCRYPTMSG hCryptMsg,
    IN DWORD dwFlags,
    IN DWORD dwCtrlType,
    IN void const *pvCtrlPara
    );

//+-------------------------------------------------------------------------
//  Message control types
//--------------------------------------------------------------------------
#define CMSG_CTRL_VERIFY_SIGNATURE       1
#define CMSG_CTRL_DECRYPT                2
#define CMSG_CTRL_VERIFY_HASH            5
#define CMSG_CTRL_ADD_SIGNER             6
#define CMSG_CTRL_DEL_SIGNER             7
#define CMSG_CTRL_ADD_SIGNER_UNAUTH_ATTR 8
#define CMSG_CTRL_DEL_SIGNER_UNAUTH_ATTR 9
#define CMSG_CTRL_ADD_CERT               10
#define CMSG_CTRL_DEL_CERT               11
#define CMSG_CTRL_ADD_CRL                12
#define CMSG_CTRL_DEL_CRL                13

//+-------------------------------------------------------------------------
//  CMSG_CTRL_VERIFY_SIGNATURE
//
//  Verify the signature of a SIGNED or SIGNED_AND_ENVELOPED
//  message after it has been decoded.
//
//  For a SIGNED_AND_ENVELOPED message, called after
//  CryptMsgControl(CMSG_CTRL_DECRYPT), if CryptMsgOpenToDecode was called
//  with a NULL pRecipientInfo.
//
//  pvCtrlPara points to a CERT_INFO struct.
//
//  The CERT_INFO contains the Issuer and SerialNumber identifying
//  the Signer of the message. The CERT_INFO also contains the
//  PublicKeyInfo
//  used to verify the signature. The cryptographic provider specified
//  in CryptMsgOpenToDecode is used.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_CTRL_DECRYPT
//
//  Decrypt an ENVELOPED or SIGNED_AND_ENVELOPED message after it has been
//  decoded.
//
//  hCryptProv and dwKeySpec specify the private key to use. For dwKeySpec ==
//  0, defaults to AT_KEYEXCHANGE.
//
//  dwRecipientIndex is the index of the recipient in the message associated
//  with the hCryptProv's private key.
//
//  This control function needs to be called, if you don't know the appropriate
//  recipient before calling CryptMsgOpenToDecode. After the final
//  CryptMsgUpdate, the list of recipients is obtained by iterating through
//  CMSG_RECIPIENT_INFO_PARAM. The recipient corresponding to a private
//  key owned by the caller is selected and passed to this function to decrypt
//  the message.
//
//  Note, the message can only be decrypted once.
//--------------------------------------------------------------------------
typedef struct _CMSG_CTRL_DECRYPT_PARA {
    DWORD       cbSize;
    HCRYPTPROV  hCryptProv;
    DWORD       dwKeySpec;
    DWORD       dwRecipientIndex;
} CMSG_CTRL_DECRYPT_PARA, *PCMSG_CTRL_DECRYPT_PARA;


//+-------------------------------------------------------------------------
//  CMSG_CTRL_VERIFY_HASH
//
//  Verify the hash of a HASHED message after it has been decoded.
//
//  Only the hCryptMsg parameter is used, to specify the message whose
//  hash is being verified.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_CTRL_ADD_SIGNER
//
//  Add a signer to a signed-data or signed-and-enveloped-data message.
//
//  pvCtrlPara points to a CMSG_SIGNER_ENCODE_INFO.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_CTRL_DEL_SIGNER
//
//  Remove a signer from a signed-data or signed-and-enveloped-data message.
//
//  pvCtrlPara points to a DWORD containing the 0-based index of the
//  signer to be removed.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_CTRL_ADD_SIGNER_UNAUTH_ATTR
//
//  Add an unauthenticated attribute to the SignerInfo of a signed-data or
//  signed-and-enveloped-data message.
//
//  The unauthenticated attribute is input in the form of an encoded blob.
//--------------------------------------------------------------------------

typedef struct _CMSG_CTRL_ADD_SIGNER_UNAUTH_ATTR_PARA {
    DWORD               cbSize;
    DWORD               dwSignerIndex;
    CRYPT_DATA_BLOB     blob;
} CMSG_CTRL_ADD_SIGNER_UNAUTH_ATTR_PARA, *PCMSG_CTRL_ADD_SIGNER_UNAUTH_ATTR_PARA;

//+-------------------------------------------------------------------------
//  CMSG_CTRL_DEL_SIGNER_UNAUTH_ATTR
//
//  Delete an unauthenticated attribute from the SignerInfo of a signed-data
//  or signed-and-enveloped-data message.
//
//  The unauthenticated attribute to be removed is specified by
//  a 0-based index.
//--------------------------------------------------------------------------

typedef struct _CMSG_CTRL_DEL_SIGNER_UNAUTH_ATTR_PARA {
    DWORD               cbSize;
    DWORD               dwSignerIndex;
    DWORD               dwUnauthAttrIndex;
} CMSG_CTRL_DEL_SIGNER_UNAUTH_ATTR_PARA, *PCMSG_CTRL_DEL_SIGNER_UNAUTH_ATTR_PARA;

//+-------------------------------------------------------------------------
//  CMSG_CTRL_ADD_CERT
//
//  Add a certificate to a signed-data or signed-and-enveloped-data message.
//
//  pvCtrlPara points to a CRYPT_DATA_BLOB containing the certificate's
//  encoded bytes.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_CTRL_DEL_CERT
//
//  Delete a certificate from a signed-data or signed-and-enveloped-data
//  message.
//
//  pvCtrlPara points to a DWORD containing the 0-based index of the
//  certificate to be removed.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_CTRL_ADD_CRL
//
//  Add a CRL to a signed-data or signed-and-enveloped-data message.
//
//  pvCtrlPara points to a CRYPT_DATA_BLOB containing the CRL's
//  encoded bytes.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_CTRL_DEL_CRL
//
//  Delete a CRL from a signed-data or signed-and-enveloped-data message.
//
//  pvCtrlPara points to a DWORD containing the 0-based index of the CRL
//  to be removed.
//--------------------------------------------------------------------------


//+-------------------------------------------------------------------------
//  Verify a countersignature, at the SignerInfo level.
//  ie. verify that pbSignerInfoCountersignature contains the encrypted
//  hash of the encryptedDigest field of pbSignerInfo.
//
//  hCryptProv is used to hash the encryptedDigest field of pbSignerInfo.
//  The only fields referenced from pciCountersigner are SerialNumber, Issuer,
//  and SubjectPublicKeyInfo.
//--------------------------------------------------------------------------
BOOL
WINAPI
CryptMsgVerifyCountersignatureEncoded(
    IN HCRYPTPROV   hCryptProv,
    IN DWORD        dwEncodingType,
    IN PBYTE        pbSignerInfo,
    IN DWORD        cbSignerInfo,
    IN PBYTE        pbSignerInfoCountersignature,
    IN DWORD        cbSignerInfoCountersignature,
    IN PCERT_INFO   pciCountersigner
    );

//+-------------------------------------------------------------------------
//  Countersign an already-existing signature in a message
//
//  dwIndex is a zero-based index of the SignerInfo to be countersigned.
//--------------------------------------------------------------------------
BOOL
WINAPI
CryptMsgCountersign(
    IN OUT HCRYPTMSG            hCryptMsg,
    IN DWORD                    dwIndex,
    IN DWORD                    cCountersigners,
    IN PCMSG_SIGNER_ENCODE_INFO rgCountersigners
    );

//+-------------------------------------------------------------------------
//  Countersign an already-existing signature (encoded SignerInfo).
//  Output an encoded SignerInfo blob, suitable for use as a countersignature
//  attribute in the unauthenticated attributes of a signed-data or
//  signed-and-enveloped-data message.
//--------------------------------------------------------------------------
BOOL
WINAPI
CryptMsgCountersignEncoded(
    IN DWORD                    dwEncodingType,
    IN PBYTE                    pbSignerInfo,
    IN DWORD                    cbSignerInfo,
    IN DWORD                    cCountersigners,
    IN PCMSG_SIGNER_ENCODE_INFO rgCountersigners,
    OUT PBYTE                   pbCountersignature,
    IN OUT PDWORD               pcbCountersignature
    );


//+-------------------------------------------------------------------------
//  Get a parameter after encoding/decoding a cryptographic message. Called
//  after the final CryptMsgUpdate. Only the CMSG_CONTENT_PARAM and
//  CMSG_COMPUTED_HASH_PARAM are valid for an encoded message.
//
//  For an encoded HASHED message, the CMSG_COMPUTED_HASH_PARAM can be got
//  before any CryptMsgUpdates to get its length.
//
//  The pvData type definition depends on the dwParamType value.
//
//  Elements pointed to by fields in the pvData structure follow the
//  structure. Therefore, *pcbData may exceed the size of the structure.
//
//  Upon input, if *pcbData == 0, then, *pcbData is updated with the length
//  of the data and the pvData parameter is ignored.
//
//  Upon return, *pcbData is updated with the length of the data.
//
//  The OBJID BLOBs returned in the pvData structures point to
//  their still encoded representation. The appropriate functions
//  must be called to decode the information.
//
//  See below for a list of the parameters to get.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CryptMsgGetParam(
    IN HCRYPTMSG hCryptMsg,
    IN DWORD dwParamType,
    IN DWORD dwIndex,
    OUT void *pvData,
    IN OUT DWORD *pcbData
    );

//+-------------------------------------------------------------------------
//  Get parameter types and their corresponding data structure definitions.
//--------------------------------------------------------------------------
#define CMSG_TYPE_PARAM                              1
#define CMSG_CONTENT_PARAM                           2
#define CMSG_BARE_CONTENT_PARAM                      3
#define CMSG_INNER_CONTENT_TYPE_PARAM                4
#define CMSG_SIGNER_COUNT_PARAM                      5
#define CMSG_SIGNER_INFO_PARAM                       6
#define CMSG_SIGNER_CERT_INFO_PARAM                  7
#define CMSG_SIGNER_HASH_ALGORITHM_PARAM             8
#define CMSG_SIGNER_AUTH_ATTR_PARAM                  9
#define CMSG_SIGNER_UNAUTH_ATTR_PARAM                10
#define CMSG_CERT_COUNT_PARAM                        11
#define CMSG_CERT_PARAM                              12
#define CMSG_CRL_COUNT_PARAM                         13
#define CMSG_CRL_PARAM                               14
#define CMSG_ENVELOPE_ALGORITHM_PARAM                15
#define CMSG_RECIPIENT_COUNT_PARAM                   17
#define CMSG_RECIPIENT_INDEX_PARAM                   18
#define CMSG_RECIPIENT_INFO_PARAM                    19
#define CMSG_HASH_ALGORITHM_PARAM                    20
#define CMSG_HASH_DATA_PARAM                         21
#define CMSG_COMPUTED_HASH_PARAM                     22
#define CMSG_ENCRYPT_PARAM                           26
#define CMSG_ENCRYPTED_DIGEST                        27
#define CMSG_ENCODED_SIGNER                          28
#define CMSG_ENCODED_MESSAGE                         29

//+-------------------------------------------------------------------------
//  CMSG_TYPE_PARAM
//
//  The type of the decoded message.
//
//  pvData points to a DWORD
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_CONTENT_PARAM
//
//  The encoded content of a cryptographic message. Depending on how the
//  message was opened, the content is either the whole PKCS#7
//  message (opened to encode) or the inner content (opened to decode).
//  In the decode case, the decrypted content is returned, if enveloped.
//  If not enveloped, and if the inner content is of type DATA, the returned
//  data is the contents octets of the inner content.
//
//  pvData points to the buffer receiving the content bytes
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_BARE_CONTENT_PARAM
//
//  The encoded content of an encoded cryptographic message, without the
//  outer layer of ContentInfo. That is, only the encoding of the
//  ContentInfo.content field is returned.
//
//  pvData points to the buffer receiving the content bytes
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_INNER_CONTENT_TYPE_PARAM
//
//  The type of the inner content of a decoded cryptographic message,
//  in the form of a NULL-terminated object identifier string
//  (eg. "1.2.840.113549.1.7.1").
//
//  pvData points to the buffer receiving the object identifier string
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_SIGNER_COUNT_PARAM
//
//  Count of signers in a SIGNED or SIGNED_AND_ENVELOPED message
//
//  pvData points to a DWORD
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_SIGNER_CERT_INFO_PARAM
//
//  To get all the signers, repetitively call CryptMsgGetParam, with
//  dwIndex set to 0 .. SignerCount - 1.
//
//  pvData points to a CERT_INFO struct.
//
//  Only the following fields have been updated in the CERT_INFO struct:
//  Issuer and SerialNumber.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_SIGNER_INFO_PARAM
//
//  To get all the signers, repetitively call CryptMsgGetParam, with
//  dwIndex set to 0 .. SignerCount - 1.
//
//  pvData points to a CMSG_SIGNER_INFO struct.
//--------------------------------------------------------------------------
typedef struct _CMSG_SIGNER_INFO {
    DWORD                       dwVersion;
    CERT_NAME_BLOB              Issuer;
    CRYPT_INTEGER_BLOB          SerialNumber;
    CRYPT_ALGORITHM_IDENTIFIER  HashAlgorithm;
    CRYPT_ALGORITHM_IDENTIFIER  HashEncryptionAlgorithm;
    CRYPT_DATA_BLOB             EncryptedHash;
    CRYPT_ATTRIBUTES            AuthAttrs;
    CRYPT_ATTRIBUTES            UnauthAttrs;
} CMSG_SIGNER_INFO, *PCMSG_SIGNER_INFO;

//+-------------------------------------------------------------------------
//  CMSG_SIGNER_HASH_ALGORITHM_PARAM
//
//  This parameter specifies the HashAlgorithm that was used for the signer.
//
//  Set dwIndex to iterate through all the signers.
//
//  pvData points to an CRYPT_ALGORITHM_IDENTIFIER struct.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_SIGNER_AUTH_ATTR_PARAM
//
//  The authenticated attributes for the signer.
//
//  Set dwIndex to iterate through all the signers.
//
//  pvData points to a CMSG_ATTR struct.
//--------------------------------------------------------------------------
typedef CRYPT_ATTRIBUTES CMSG_ATTR;
typedef CRYPT_ATTRIBUTES *PCMSG_ATTR;

//+-------------------------------------------------------------------------
//  CMSG_SIGNER_UNAUTH_ATTR_PARAM
//
//  The unauthenticated attributes for the signer.
//
//  Set dwIndex to iterate through all the signers.
//
//  pvData points to a CMSG_ATTR struct.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_CERT_COUNT_PARAM
//
//  Count of certificates in a SIGNED or SIGNED_AND_ENVELOPED message.
//
//  pvData points to a DWORD
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_CERT_PARAM
//
//  To get all the certificates, repetitively call CryptMsgGetParam, with
//  dwIndex set to 0 .. CertCount - 1.
//
//  pvData points to an array of the certificate's encoded bytes.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_CRL_COUNT_PARAM
//
//  Count of CRLs in a SIGNED or SIGNED_AND_ENVELOPED message.
//
//  pvData points to a DWORD
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_CRL_PARAM
//
//  To get all the CRLs, repetitively call CryptMsgGetParam, with
//  dwIndex set to 0 .. CrlCount - 1.
//
//  pvData points to an array of the CRL's encoded bytes.
//--------------------------------------------------------------------------


//+-------------------------------------------------------------------------
//  CMSG_ENVELOPE_ALGORITHM_PARAM
//
//  The ContentEncryptionAlgorithm that was used in
//  an ENVELOPED or SIGNED_AND_ENVELOPED message.
//
//  pvData points to an CRYPT_ALGORITHM_IDENTIFIER struct.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_RECIPIENT_COUNT_PARAM
//
//  Count of recipients in an ENVELOPED or SIGNED_AND_ENVELOPED message.
//
//  pvData points to a DWORD
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_RECIPIENT_INDEX_PARAM
//
//  Index of the recipient used to decrypt an ENVELOPED or SIGNED_AND_ENVELOPED
//  message.
//
//  pvData points to a DWORD
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_RECIPIENT_INFO_PARAM
//
//  To get all the recipients, repetitively call CryptMsgGetParam, with
//  dwIndex set to 0 .. RecipientCount - 1.
//
//  pvData points to a CERT_INFO struct.
//
//  Only the following fields have been updated in the CERT_INFO struct:
//  Issuer, SerialNumber and PublicKeyAlgorithm. The PublicKeyAlgorithm
//  specifies the KeyEncryptionAlgorithm that was used.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_HASH_ALGORITHM_PARAM
//
//  The HashAlgorithm in a HASHED message.
//
//  pvData points to an CRYPT_ALGORITHM_IDENTIFIER struct.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_HASH_DATA_PARAM
//
//  The hash in a HASHED message.
//
//  pvData points to an array of bytes.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_COMPUTED_HASH_PARAM
//
//  The computed hash for a HASHED message.
//
//  This may be called for either an encoded or decoded message.
//  It also may be called before any encoded CryptMsgUpdates to get its length.
//
//  pvData points to an array of bytes.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_ENCRYPT_PARAM
//
//  The ContentEncryptionAlgorithm that was used in an ENCRYPTED message.
//
//  pvData points to an CRYPT_ALGORITHM_IDENTIFIER struct.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_ENCODED_MESSAGE
//
//  The full encoded message. This is useful in the case of a decoded
//  message which has been modified (eg. a signed-data or
//  signed-and-enveloped-data message which has been countersigned).
//
//  pvData points to an array of the message's encoded bytes.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CryptMsg OID installable functions
//--------------------------------------------------------------------------

// If *phCryptProv is NULL upon entry, then, if supported, the installable
// function should acquire a default provider and return. Note, its up
// to the installable function to release at process detach.
#define CMSG_OID_GEN_ENCRYPT_KEY_FUNC   "CryptMsgDllGenEncryptKey"
typedef BOOL (WINAPI *PFN_CMSG_GEN_ENCRYPT_KEY) (
    IN OUT HCRYPTPROV               *phCryptProv,
    IN PCRYPT_ALGORITHM_IDENTIFIER  paiEncrypt,
    IN PVOID                        pvEncryptAuxInfo,
    IN PCERT_PUBLIC_KEY_INFO        pPublicKeyInfo,
    OUT HCRYPTKEY                   *phEncryptKey
    );

#define CMSG_OID_EXPORT_ENCRYPT_KEY_FUNC   "CryptMsgDllExportEncryptKey"
typedef BOOL (WINAPI *PFN_CMSG_EXPORT_ENCRYPT_KEY) (
    IN HCRYPTPROV                   hCryptProv,
    IN HCRYPTKEY                    hEncryptKey,
    IN PCERT_PUBLIC_KEY_INFO        pPublicKeyInfo,
    OUT PBYTE                       pbData,
    IN OUT PDWORD                   pcbData
    );

#define CMSG_OID_IMPORT_ENCRYPT_KEY_FUNC   "CryptMsgDllImportEncryptKey"
typedef BOOL (WINAPI *PFN_CMSG_IMPORT_ENCRYPT_KEY) (
    IN HCRYPTPROV                   hCryptProv,
    IN DWORD                        dwKeySpec,
    IN PCRYPT_ALGORITHM_IDENTIFIER  paiEncrypt,
    IN PCRYPT_ALGORITHM_IDENTIFIER  paiPubKey,
    IN PBYTE                        pbEncodedKey,
    IN DWORD                        cbEncodedKey,
    OUT HCRYPTKEY                   *phEncryptKey
    );


//+=========================================================================
//  Certificate Store Data Structures and APIs
//==========================================================================

//+-------------------------------------------------------------------------
//              In its most basic implementation, a cert store is simply a
//              collection of certificates and/or CRLs. This is the case when
//              a cert store is opened with all of its certificates and CRLs
//              coming from a PKCS #7 encoded cryptographic message.
//
//              Nonetheless, all cert stores have the following properties:
//               - A public key may have more than one certificate in the store.
//                 For example, a private/public key used for signing may have a
//                 certificate issued for VISA and another issued for
//                 Mastercard. Also, when a certificate is renewed there might
//                 be more than one certificate with the same subject and
//                 issuer.
//               - However, each certificate in the store is uniquely
//                 identified by its Issuer and SerialNumber.
//               - There's an issuer of subject certificate relationship. A
//                 certificate's issuer is found by doing a match of
//                 pSubjectCert->Issuer with pIssuerCert->Subject.
//                 The relationship is verified by using
//                 the issuer's public key to verify the subject certificate's
//                 signature. Note, there might be X.509 v3 extensions
//                 to assist in finding the issuer certificate.
//               - Since issuer certificates might be renewed, a subject
//                 certificate might have more than one issuer certificate.
//               - There's an issuer of CRL relationship. An
//                 issuer's CRL is found by doing a match of
//                 pIssuerCert->Subject with pCrl->Issuer.
//                 The relationship is verified by using
//                 the issuer's public key to verify the CRL's
//                 signature. Note, there might be X.509 v3 extensions
//                 to assist in finding the CRL.
//               - Since some issuers might support the X.509 v3 delta CRL
//                 extensions, an issuer might have more than one CRL.
//               - The store shouldn't have any redundant certificates or
//                 CRLs. There shouldn't be two certificates with the same
//                 Issuer and SerialNumber. There shouldn't be two CRLs with
//                 the same Issuer, ThisUpdate and NextUpdate.
//               - The store has NO policy or trust information. No
//                 certificates are tagged as being "root". Its up to
//                 the application to maintain a list of CertIds (Issuer +
//                 SerialNumber) for certificates it trusts.
//               - The store might contain bad certificates and/or CRLs.
//                 The issuer's signature of a subject certificate or CRL may
//                 not verify. Certificates or CRLs may not satisfy their
//                 time validity requirements. Certificates may be
//                 revoked.
//
//              In addition to the certificates and CRLs, properties can be
//              stored. There are two predefined property IDs for a user
//              certificate: CERT_KEY_PROV_HANDLE_PROP_ID and
//              CERT_KEY_PROV_INFO_PROP_ID. The CERT_KEY_PROV_HANDLE_PROP_ID
//              is a HCRYPTPROV handle to the private key assoicated
//              with the certificate. The CERT_KEY_PROV_INFO_PROP_ID contains
//              information to be used to call
//              CryptAcquireContext and CryptProvSetParam to get a handle
//              to the private key associated with the certificate.
//
//              There exists two more predefined property IDs for certificates
//              and CRLs, CERT_SHA1_HASH_PROP_ID and CERT_MD5_HASH_PROP_ID.
//              If these properties don't already exist, then, a hash of the
//              content is computed. (CERT_HASH_PROP_ID maps to the default
//              hash algorithm, currently, CERT_SHA1_HASH_PROP_ID).
//
//              There are additional APIs for creating certificate and CRL
//      contexts not in a store (CertCreateCertificateContext and
//      CertCreateCRLContext).
//
//--------------------------------------------------------------------------


typedef void *HCERTSTORE;

//+-------------------------------------------------------------------------
//  Certificate context.
//
//  A certificate context contains both the encoded and decoded representation
//  of a certificate. A certificate context returned by a cert store function
//  must be freed by calling the CertFreeCertificateContext function. The
//  CertDuplicateCertificateContext function can be called to make a duplicate
//  copy (which also must be freed by calling CertFreeCertificateContext).
//--------------------------------------------------------------------------
typedef struct _CERT_CONTEXT {
    DWORD                   dwCertEncodingType;
    BYTE                    *pbCertEncoded;
    DWORD                   cbCertEncoded;
    PCERT_INFO              pCertInfo;
    HCERTSTORE              hCertStore;
} CERT_CONTEXT, *PCERT_CONTEXT;
typedef const CERT_CONTEXT *PCCERT_CONTEXT;

//+-------------------------------------------------------------------------
//  CRL context.
//
//  A CRL context contains both the encoded and decoded representation
//  of a CRL. A CRL context returned by a cert store function
//  must be freed by calling the CertFreeCRLContext function. The
//  CertDuplicateCRLContext function can be called to make a duplicate
//  copy (which also must be freed by calling CertFreeCRLContext).
//--------------------------------------------------------------------------
typedef struct _CRL_CONTEXT {
    DWORD                   dwCertEncodingType;
    BYTE                    *pbCrlEncoded;
    DWORD                   cbCrlEncoded;
    PCRL_INFO               pCrlInfo;
    HCERTSTORE              hCertStore;
} CRL_CONTEXT, *PCRL_CONTEXT;
typedef const CRL_CONTEXT *PCCRL_CONTEXT;

//+-------------------------------------------------------------------------
//  Certificate Trust List (CTL) context.
//
//  A CTL context contains both the encoded and decoded representation
//  of a CTL. Also contains an opened HCRYPTMSG handle to the decoded
//  cryptographic signed message containing the CTL_INFO as its inner content.
//  pbCtlContent is the encoded inner content of the signed message.
//
//  The CryptMsg APIs can be used to extract additional signer information.
//--------------------------------------------------------------------------
typedef struct _CTL_CONTEXT {
    DWORD                   dwMsgAndCertEncodingType;
    BYTE                    *pbCtlEncoded;
    DWORD                   cbCtlEncoded;
    PCTL_INFO               pCtlInfo;
    HCERTSTORE              hCertStore;
    HCRYPTMSG               hCryptMsg;
    BYTE                    *pbCtlContent;
    DWORD                   cbCtlContent;
} CTL_CONTEXT, *PCTL_CONTEXT;
typedef const CTL_CONTEXT *PCCTL_CONTEXT;

//+-------------------------------------------------------------------------
//  Certificate, CRL and CTL property IDs
//
//  See CertSetCertificateContextProperty or CertGetCertificateContextProperty
//  for usage information.
//--------------------------------------------------------------------------
#define CERT_KEY_PROV_HANDLE_PROP_ID        1
#define CERT_KEY_PROV_INFO_PROP_ID          2
#define CERT_SHA1_HASH_PROP_ID              3
#define CERT_MD5_HASH_PROP_ID               4
#define CERT_HASH_PROP_ID                   CERT_SHA1_HASH_PROP_ID
#define CERT_KEY_CONTEXT_PROP_ID            5
#define CERT_KEY_SPEC_PROP_ID               6
#define CERT_IE30_RESERVED_PROP_ID          7
#define CERT_PUBKEY_HASH_RESERVED_PROP_ID   8
#define CERT_ENHKEY_USAGE_PROP_ID           9
#define CERT_CTL_USAGE_PROP_ID              CERT_ENHKEY_USAGE_PROP_ID
#define CERT_NEXT_UPDATE_LOCATION_PROP_ID   10
#define CERT_FRIENDLY_NAME_PROP_ID          11
#define CERT_PVK_FILE_PROP_ID				12
// Note, 32 - 34 are reserved for the CERT, CRL and CTL file element IDs.
#define CERT_FIRST_RESERVED_PROP_ID         13

#define CERT_LAST_RESERVED_PROP_ID          0x00007FFF
#define CERT_FIRST_USER_PROP_ID             0x00008000
#define CERT_LAST_USER_PROP_ID              0x0000FFFF


#define IS_CERT_HASH_PROP_ID(X)     (CERT_SHA1_HASH_PROP_ID == (X) || \
                                            CERT_MD5_HASH_PROP_ID == (X))


//+-------------------------------------------------------------------------
//  Cryptographic Key Provider Information
//
//  CRYPT_KEY_PROV_INFO defines the CERT_KEY_PROV_INFO_PROP_ID's pvData.
//
//  The CRYPT_KEY_PROV_INFO fields are passed to CryptAcquireContext
//  to get a HCRYPTPROV handle. The optional CRYPT_KEY_PROV_PARAM fields are
//  passed to CryptProvSetParam to further initialize the provider.
//
//  The dwKeySpec field identifies the private key to use from the container
//  For example, AT_KEYEXCHANGE or AT_SIGNATURE.
//--------------------------------------------------------------------------
typedef struct _CRYPT_KEY_PROV_PARAM {
    DWORD           dwParam;
    BYTE            *pbData;
    DWORD           cbData;
    DWORD           dwFlags;
} CRYPT_KEY_PROV_PARAM, *PCRYPT_KEY_PROV_PARAM;

typedef struct _CRYPT_KEY_PROV_INFO {
    LPWSTR                  pwszContainerName;
    LPWSTR                  pwszProvName;
    DWORD                   dwProvType;
    DWORD                   dwFlags;
    DWORD                   cProvParam;
    PCRYPT_KEY_PROV_PARAM   rgProvParam;
    DWORD                   dwKeySpec;
} CRYPT_KEY_PROV_INFO, *PCRYPT_KEY_PROV_INFO;

//+-------------------------------------------------------------------------
//  The following flag should be set in the above dwFlags to enable
//  a CertSetCertificateContextProperty(CERT_KEY_CONTEXT_PROP_ID) after a
//  CryptAcquireContext is done in the Sign or Decrypt Message functions.
//
//  The following define must not collide with any of the
//  CryptAcquireContext dwFlag defines.
//--------------------------------------------------------------------------
#define CERT_SET_KEY_PROV_HANDLE_PROP_ID    0x00000001
#define CERT_SET_KEY_CONTEXT_PROP_ID        0x00000001

//+-------------------------------------------------------------------------
//  Certificate Key Context
//
//  CERT_KEY_CONTEXT defines the CERT_KEY_CONTEXT_PROP_ID's pvData.
//--------------------------------------------------------------------------
typedef struct _CERT_KEY_CONTEXT {
    DWORD           cbSize;           // sizeof(CERT_KEY_CONTEXT)
    HCRYPTPROV      hCryptProv;
    DWORD           dwKeySpec;
} CERT_KEY_CONTEXT, *PCERT_KEY_CONTEXT;

//+-------------------------------------------------------------------------
//  Certificate Store Provider Types
//--------------------------------------------------------------------------
#define CERT_STORE_PROV_MSG                 ((LPCSTR) 1)
#define CERT_STORE_PROV_MEMORY              ((LPCSTR) 2)
#define CERT_STORE_PROV_FILE                ((LPCSTR) 3)
#define CERT_STORE_PROV_REG                 ((LPCSTR) 4)

#define CERT_STORE_PROV_PKCS7               ((LPCSTR) 5)
#define CERT_STORE_PROV_SERIALIZED          ((LPCSTR) 6)
#define CERT_STORE_PROV_FILENAME_A          ((LPCSTR) 7)
#define CERT_STORE_PROV_FILENAME_W          ((LPCSTR) 8)
#define CERT_STORE_PROV_FILENAME            CERT_STORE_PROV_FILENAME_W
#define CERT_STORE_PROV_SYSTEM_A            ((LPCSTR) 9)
#define CERT_STORE_PROV_SYSTEM_W            ((LPCSTR) 10)
#define CERT_STORE_PROV_SYSTEM              CERT_STORE_PROV_SYSTEM_W

#define sz_CERT_STORE_PROV_MEMORY           "Memory"
#define sz_CERT_STORE_PROV_FILENAME_W       "File"
#define sz_CERT_STORE_PROV_FILENAME         sz_CERT_STORE_PROV_FILENAME_W
#define sz_CERT_STORE_PROV_SYSTEM_W         "System"
#define sz_CERT_STORE_PROV_SYSTEM           sz_CERT_STORE_PROV_SYSTEM_W
#define sz_CERT_STORE_PROV_PKCS7            "PKCS7"
#define sz_CERT_STORE_PROV_SERIALIZED       "Serialized"

//+-------------------------------------------------------------------------
//  Certificate Store verify/results flags
//--------------------------------------------------------------------------
#define CERT_STORE_SIGNATURE_FLAG           0x00000001
#define CERT_STORE_TIME_VALIDITY_FLAG       0x00000002
#define CERT_STORE_REVOCATION_FLAG          0x00000004
#define CERT_STORE_NO_CRL_FLAG              0x00010000
#define CERT_STORE_NO_ISSUER_FLAG           0x00020000


//+-------------------------------------------------------------------------
//  Certificate Store open/property flags
//--------------------------------------------------------------------------
#define CERT_STORE_NO_CRYPT_RELEASE_FLAG        0x00000001
#define CERT_STORE_READONLY_FLAG                0x00008000

//+-------------------------------------------------------------------------
//  Certificate Store Provider flags are in the HiWord (0xFFFF0000)
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  Certificate System Store Flag Values
//--------------------------------------------------------------------------
// Location of the system store in the registry:
//  HKEY_CURRENT_USER or HKEY_LOCAL_MACHINE
#define CERT_SYSTEM_STORE_LOCATION_MASK         0x00030000
#define CERT_SYSTEM_STORE_CURRENT_USER          0x00010000
#define CERT_SYSTEM_STORE_LOCAL_MACHINE         0x00020000


//+-------------------------------------------------------------------------
//  Open the cert store using the specified store provider.
//
//  hCryptProv specifies the crypto provider to use to create the hash
//  properties or verify the signature of a subject certificate or CRL.
//  The store doesn't need to use a private
//  key. If the CERT_STORE_NO_CRYPT_RELEASE_FLAG isn't set, hCryptProv is
//  CryptReleaseContext'ed on the final CertCloseStore.
//
//  Note, if the open fails, hCryptProv is released if it would have been
//  released when the store was closed.
//
//  If hCryptProv is zero, then, the default provider and container for the
//  PROV_RSA_FULL provider type is CryptAcquireContext'ed with
//  CRYPT_VERIFYCONTEXT access. The CryptAcquireContext is deferred until
//  the first create hash or verify signature. In addition, once acquired,
//  the default provider isn't released until process exit when crypt32.dll
//  is unloaded. The acquired default provider is shared across all stores
//  and threads.
//
//  After initializing the store's data structures and optionally acquiring a
//  default crypt provider, CertOpenStore calls CryptGetOIDFunctionAddress to
//  get the address of the CRYPT_OID_OPEN_STORE_PROV_FUNC specified by
//  lpszStoreProvider. Since a store can contain certificates with different
//  encoding types, CryptGetOIDFunctionAddress is called with dwEncodingType
//  set to 0 and not the dwEncodingType passed to CertOpenStore.
//  PFN_CERT_DLL_OPEN_STORE_FUNC specifies the signature of the provider's
//  open function. This provider open function is called to load the
//  store's certificates and CRLs. Optionally, the provider may return an
//  array of functions called before a certificate or CRL is added or deleted
//  or has a property that is set.
//
//  Use of the dwEncodingType parameter is provider dependent. The type
//  definition for pvPara also depends on the provider.
//
//  Store providers are installed or registered via
//  CryptInstallOIDFunctionAddress or CryptRegisterOIDFunction, where,
//  dwEncodingType is 0 and pszFuncName is CRYPT_OID_OPEN_STORE_PROV_FUNC.
//
//  Here's a list of the predefined provider types (implemented in crypt32.dll):
//
//  CERT_STORE_PROV_MSG:
//      Gets the certificates and CRLs from the specified cryptographic message.
//      dwEncodingType contains the message and certificate encoding types.
//      The message's handle is passed in pvPara. Given,
//          HCRYPTMSG hCryptMsg; pvPara = (const void *) hCryptMsg;
//
//  CERT_STORE_PROV_MEMORY
//  sz_CERT_STORE_PROV_MEMORY:
//      Opens a store without any initial certificates or CRLs. pvPara
//      isn't used.
//
//  CERT_STORE_PROV_FILE:
//      Reads the certificates and CRLs from the specified file. The file's
//      handle is passed in pvPara. Given,
//          HANDLE hFile; pvPara = (const void *) hFile;
//
//      For a successful open, the file pointer is advanced past
//      the certificates and CRLs and their properties read from the file.
//      Note, only expects a serialized store and not a file containing
//      either a PKCS #7 signed message or a single encoded certificate.
//
//      The hFile isn't closed.
//
//  CERT_STORE_PROV_REG:
//      Reads the certificates and CRLs from the registry. The registry's
//      key handle is passed in pvPara. Given,
//          HKEY hKey; pvPara = (const void *) hKey;
//
//      The input hKey isn't closed by the provider. Before returning, the
//      provider opens/creates "Certificates" and "CRLs" subkeys. These
//      subkeys remain open until the store is closed.
//
//      If CERT_STORE_READONLY_FLAG is set, then, the registry subkeys are
//      RegOpenKey'ed with KEY_READ_ACCESS. Otherwise, the registry subkeys
//      are RegCreateKey'ed with KEY_ALL_ACCESS.
//
//      This provider returns the array of functions for reading, writing,
//      deleting and property setting certificates and CRLs.
//      Any changes to the opened store are immediately pushed through to
//      the registry. However, if CERT_STORE_READONLY_FLAG is set, then,
//      writing, deleting or property setting results in a
//      SetLastError(E_ACCESSDENIED).
//
//      Note, all the certificates and CRLs are read from the registry
//      when the store is opened. The opened store serves as a write through
//      cache. However, the opened store isn't notified of other changes
//      made to the registry. Note, RegNotifyChangeKeyValue is supported
//      on NT but not supported on Windows95.
//
//  CERT_STORE_PROV_PKCS7:
//  sz_CERT_STORE_PROV_PKCS7:
//      Gets the certificates and CRLs from the encoded PKCS #7 signed message.
//      dwEncodingType specifies the message and certificate encoding types.
//      The pointer to the encoded message's blob is passed in pvPara. Given,
//          CRYPT_DATA_BLOB EncodedMsg; pvPara = (const void *) &EncodedMsg;
//
//      Note, also supports the IE3.0 special version of a
//      PKCS #7 signed message referred to as a "SPC" formatted message.
//
//  CERT_STORE_PROV_SERIALIZED:
//  sz_CERT_STORE_PROV_SERIALIZED:
//      Gets the certificates and CRLs from memory containing a serialized
//      store.  The pointer to the serialized memory blob is passed in pvPara.
//      Given,
//          CRYPT_DATA_BLOB Serialized; pvPara = (const void *) &Serialized;
//
//  CERT_STORE_PROV_FILENAME_A:
//  CERT_STORE_PROV_FILENAME_W:
//  CERT_STORE_PROV_FILENAME:
//  sz_CERT_STORE_PROV_FILENAME_W:
//  sz_CERT_STORE_PROV_FILENAME:
//      Opens the file and first attempts to read as a serialized store. Then,
//      as a PKCS #7 signed message. Finally, as a single encoded certificate.
//      The filename is passed in pvPara. The filename is UNICODE for the
//      "_W" provider and ASCII for the "_A" provider. For "_W": given,
//          LPCWSTR pwszFilename; pvPara = (const void *) pwszFilename;
//      For "_A": given,
//          LPCSTR pszFilename; pvPara = (const void *) pszFilename;
//
//      Note, the default (without "_A" or "_W") is unicode.
//
//      Note, also supports the reading of the IE3.0 special version of a
//      PKCS #7 signed message file referred to as a "SPC" formatted file.
//
//  CERT_STORE_PROV_SYSTEM_A:
//  CERT_STORE_PROV_SYSTEM_W:
//  CERT_STORE_PROV_SYSTEM:
//  sz_CERT_STORE_PROV_SYSTEM_W:
//  sz_CERT_STORE_PROV_SYSTEM:
//      Opens the specified "system" store. Currently, all the system
//      stores are stored in the registry. The upper word of the dwFlags
//      parameter is used to specify the location of the system store. It
//      should be set to either CERT_SYSTEM_STORE_CURRENT_USER for
//      HKEY_CURRENT_USER or CERT_SYSTEM_STORE_LOCAL_MACHINE for
//      HKEY_LOCAL_MACHINE.
//
//      After opening the registry key associated with the system name,
//      the CERT_STORE_PROV_REG provider is called to complete the open.
//
//      The system store name is passed in pvPara. The name is UNICODE for the
//      "_W" provider and ASCII for the "_A" provider. For "_W": given,
//          LPCWSTR pwszSystemName; pvPara = (const void *) pwszSystemName;
//      For "_A": given,
//          LPCSTR pszSystemName; pvPara = (const void *) pszSystemName;
//
//      Note, the default (without "_A" or "_W") is UNICODE.
//
//      If CERT_STORE_READONLY_FLAG is set, then, the registry is
//      RegOpenKey'ed with KEY_READ_ACCESS. Otherwise, the registry is
//      RegCreateKey'ed with KEY_ALL_ACCESS.
//
//      The "root" store is treated differently from the other system
//      stores. Before a certificate is added to or deleted from the "root"
//      store, a pop up message box is displayed. The certificate's subject,
//      issuer, serial number, time validity, sha1 and md5 thumbprints are
//      displayed. The user is given the option to do the add or delete.
//      If they don't allow the operation, LastError is set to E_ACCESSDENIED.
//--------------------------------------------------------------------------
WINCRYPT32API
HCERTSTORE
WINAPI
CertOpenStore(
    IN LPCSTR lpszStoreProvider,
    IN DWORD dwEncodingType,
    IN HCRYPTPROV hCryptProv,
    IN DWORD dwFlags,
    IN const void *pvPara
    );


//+-------------------------------------------------------------------------
//  OID Installable Certificate Store Provider Data Structures
//--------------------------------------------------------------------------

// Handle returned by the store provider when opened.
typedef void *HCERTSTOREPROV;

// Store Provider OID function's pszFuncName.
#define CRYPT_OID_OPEN_STORE_PROV_FUNC   "CertDllOpenStoreProv"

// Note, the Store Provider OID function's dwEncodingType is always 0.

// The following information is returned by the provider when opened. Its
// zeroed with cbSize set before the provider is called. If the provider
// doesn't need to be called again after the open it doesn't need to
// make any updates to the CERT_STORE_PROV_INFO.
typedef struct _CERT_STORE_PROV_INFO {
    DWORD               cbSize;
    DWORD               cStoreProvFunc;
    void                **rgpvStoreProvFunc;
    HCERTSTOREPROV      hStoreProv;
    DWORD               dwStoreProvFlags;
} CERT_STORE_PROV_INFO, *PCERT_STORE_PROV_INFO;

// Definition of the store provider's open function.
//
// *pStoreProvInfo has been zeroed before the call.
//
// Note, pStoreProvInfo->cStoreProvFunc should be set last.  Once set,
// all subsequent store calls, such as CertAddSerializedElementToStore will
// call the appropriate provider callback function.
typedef BOOL (WINAPI *PFN_CERT_DLL_OPEN_STORE_PROV_FUNC)(
        IN LPCSTR lpszStoreProvider,
        IN DWORD dwEncodingType,
        IN HCRYPTPROV hCryptProv,
        IN DWORD dwFlags,
        IN const void *pvPara,
        IN HCERTSTORE hCertStore,
        IN OUT PCERT_STORE_PROV_INFO pStoreProvInfo
        );

// Indices into the store provider's array of callback functions.
//
// The provider can implement any subset of the following functions. It
// sets pStoreProvInfo->cStoreProvFunc to the last index + 1 and any
// preceding not implemented functions to NULL.
#define CERT_STORE_PROV_CLOSE_FUNC              0
#define CERT_STORE_PROV_READ_CERT_FUNC          1
#define CERT_STORE_PROV_WRITE_CERT_FUNC         2
#define CERT_STORE_PROV_DELETE_CERT_FUNC        3
#define CERT_STORE_PROV_SET_CERT_PROPERTY_FUNC  4
#define CERT_STORE_PROV_READ_CRL_FUNC           5
#define CERT_STORE_PROV_WRITE_CRL_FUNC          6
#define CERT_STORE_PROV_DELETE_CRL_FUNC         7
#define CERT_STORE_PROV_SET_CRL_PROPERTY_FUNC   8
#define CERT_STORE_PROV_READ_CTL_FUNC           9
#define CERT_STORE_PROV_WRITE_CTL_FUNC          10
#define CERT_STORE_PROV_DELETE_CTL_FUNC         11
#define CERT_STORE_PROV_SET_CTL_PROPERTY_FUNC   12

// Called by CertCloseStore when the store's reference count is
// decremented to 0.
typedef void (WINAPI *PFN_CERT_STORE_PROV_CLOSE)(
        IN HCERTSTOREPROV hStoreProv,
        IN DWORD dwFlags
        );

// Currently not called directly by the store APIs. However, may be exported
// to support other providers based on it.
//
// Reads the provider's copy of the certificate context. If it exists,
// creates a new certificate context.
typedef BOOL (WINAPI *PFN_CERT_STORE_PROV_READ_CERT)(
        IN HCERTSTOREPROV hStoreProv,
        IN PCCERT_CONTEXT pStoreCertContext,
        IN DWORD dwFlags,
        OUT PCCERT_CONTEXT *ppProvCertContext
        );

#define CERT_STORE_PROV_WRITE_ADD_FLAG      0x1

// Called by CertAddEncodedCertificateToStore,
// CertAddCertificateContextToStore or CertAddSerializedElementToStore before
// adding to the store. The CERT_STORE_PROV_WRITE_ADD_FLAG is set. In
// addition to the encoded certificate, the added pCertContext might also
// have properties.
//
// Returns TRUE if its OK to update the the store.
typedef BOOL (WINAPI *PFN_CERT_STORE_PROV_WRITE_CERT)(
        IN HCERTSTOREPROV hStoreProv,
        IN PCCERT_CONTEXT pCertContext,
        IN DWORD dwFlags
        );

// Called by CertDeleteCertificateFromStore before deleting from the
// store.
//
// Returns TRUE if its OK to delete from the store.
typedef BOOL (WINAPI *PFN_CERT_STORE_PROV_DELETE_CERT)(
        IN HCERTSTOREPROV hStoreProv,
        IN PCCERT_CONTEXT pCertContext,
        IN DWORD dwFlags
        );

// Called by CertSetCertificateContextProperty before setting the
// certificate's property. Also called by CertGetCertificateContextProperty,
// when getting a hash property that needs to be created and then persisted
// via the set.
//
// Upon input, the property hasn't been set for the pCertContext parameter.
//
// Returns TRUE if its OK to set the property.
typedef BOOL (WINAPI *PFN_CERT_STORE_PROV_SET_CERT_PROPERTY)(
        IN HCERTSTOREPROV hStoreProv,
        IN PCCERT_CONTEXT pCertContext,
        IN DWORD dwPropId,
        IN DWORD dwFlags,
        IN const void *pvData
        );

// Currently not called directly by the store APIs. However, may be exported
// to support other providers based on it.
//
// Reads the provider's copy of the CRL context. If it exists,
// creates a new CRL context.
typedef BOOL (WINAPI *PFN_CERT_STORE_PROV_READ_CRL)(
        IN HCERTSTOREPROV hStoreProv,
        IN PCCRL_CONTEXT pStoreCrlContext,
        IN DWORD dwFlags,
        OUT PCCRL_CONTEXT *ppProvCrlContext
        );

// Called by CertAddEncodedCRLToStore,
// CertAddCRLContextToStore or CertAddSerializedElementToStore before
// adding to the store. The CERT_STORE_PROV_WRITE_ADD_FLAG is set. In
// addition to the encoded CRL, the added pCertContext might also
// have properties.
//
// Returns TRUE if its OK to update the the store.
typedef BOOL (WINAPI *PFN_CERT_STORE_PROV_WRITE_CRL)(
        IN HCERTSTOREPROV hStoreProv,
        IN PCCRL_CONTEXT pCrlContext,
        IN DWORD dwFlags
        );

// Called by CertDeleteCRLFromStore before deleting from the store.
//
// Returns TRUE if its OK to delete from the store.
typedef BOOL (WINAPI *PFN_CERT_STORE_PROV_DELETE_CRL)(
        IN HCERTSTOREPROV hStoreProv,
        IN PCCRL_CONTEXT pCrlContext,
        IN DWORD dwFlags
        );

// Called by CertSetCRLContextProperty before setting the
// CRL's property. Also called by CertGetCRLContextProperty,
// when getting a hash property that needs to be created and then persisted
// via the set.
//
// Upon input, the property hasn't been set for the pCrlContext parameter.
//
// Returns TRUE if its OK to set the property.
typedef BOOL (WINAPI *PFN_CERT_STORE_PROV_SET_CRL_PROPERTY)(
        IN HCERTSTOREPROV hStoreProv,
        IN PCCRL_CONTEXT pCrlContext,
        IN DWORD dwPropId,
        IN DWORD dwFlags,
        IN const void *pvData
        );

// Currently not called directly by the store APIs. However, may be exported
// to support other providers based on it.
//
// Reads the provider's copy of the CTL context. If it exists,
// creates a new CTL context.
typedef BOOL (WINAPI *PFN_CERT_STORE_PROV_READ_CTL)(
        IN HCERTSTOREPROV hStoreProv,
        IN PCCTL_CONTEXT pStoreCtlContext,
        IN DWORD dwFlags,
        OUT PCCTL_CONTEXT *ppProvCtlContext
        );

// Called by CertAddEncodedCTLToStore,
// CertAddCTLContextToStore or CertAddSerializedElementToStore before
// adding to the store. The CERT_STORE_PROV_WRITE_ADD_FLAG is set. In
// addition to the encoded CTL, the added pCertContext might also
// have properties.
//
// Returns TRUE if its OK to update the the store.
typedef BOOL (WINAPI *PFN_CERT_STORE_PROV_WRITE_CTL)(
        IN HCERTSTOREPROV hStoreProv,
        IN PCCTL_CONTEXT pCtlContext,
        IN DWORD dwFlags
        );

// Called by CertDeleteCTLFromStore before deleting from the store.
//
// Returns TRUE if its OK to delete from the store.
typedef BOOL (WINAPI *PFN_CERT_STORE_PROV_DELETE_CTL)(
        IN HCERTSTOREPROV hStoreProv,
        IN PCCTL_CONTEXT pCtlContext,
        IN DWORD dwFlags
        );

// Called by CertSetCTLContextProperty before setting the
// CTL's property. Also called by CertGetCTLContextProperty,
// when getting a hash property that needs to be created and then persisted
// via the set.
//
// Upon input, the property hasn't been set for the pCtlContext parameter.
//
// Returns TRUE if its OK to set the property.
typedef BOOL (WINAPI *PFN_CERT_STORE_PROV_SET_CTL_PROPERTY)(
        IN HCERTSTOREPROV hStoreProv,
        IN PCCTL_CONTEXT pCtlContext,
        IN DWORD dwPropId,
        IN DWORD dwFlags,
        IN const void *pvData
        );

//+-------------------------------------------------------------------------
//  Duplicate a cert store handle
//--------------------------------------------------------------------------
WINCRYPT32API
HCERTSTORE
WINAPI
CertDuplicateStore(
    IN HCERTSTORE hCertStore
    );

#define CERT_STORE_SAVE_AS_STORE        1
#define CERT_STORE_SAVE_AS_PKCS7        2

#define CERT_STORE_SAVE_TO_FILE         1
#define CERT_STORE_SAVE_TO_MEMORY       2
#define CERT_STORE_SAVE_TO_FILENAME_A   3
#define CERT_STORE_SAVE_TO_FILENAME_W   4
#define CERT_STORE_SAVE_TO_FILENAME     CERT_STORE_SAVE_TO_FILENAME_W

//+-------------------------------------------------------------------------
//  Save the cert store. Extended version with lots of options.
//
//  According to the dwSaveAs parameter, the store can be saved as a
//  serialized store (CERT_STORE_SAVE_AS_STORE) containing properties in
//  addition to encoded certificates, CRLs and CTLs or the store can be saved
//  as a PKCS #7 signed message (CERT_STORE_SAVE_AS_PKCS7) which doesn't
//  include the properties or CTLs.
//
//  Note, the CERT_KEY_CONTEXT_PROP_ID property (and its
//  CERT_KEY_PROV_HANDLE_PROP_ID or CERT_KEY_SPEC_PROP_ID) isn't saved into
//  a serialized store.
//
//  For CERT_STORE_SAVE_AS_PKCS7, the dwEncodingType specifies the message
//  encoding type. The dwEncodingType parameter isn't used for
//  CERT_STORE_SAVE_AS_STORE.
//
//  The dwFlags parameter currently isn't used and should be set to 0.
//
//  The dwSaveTo and pvSaveToPara parameters specify where to save the
//  store as follows:
//    CERT_STORE_SAVE_TO_FILE:
//      Saves to the specified file. The file's handle is passed in
//      pvSaveToPara. Given,
//          HANDLE hFile; pvSaveToPara = (void *) hFile;
//
//      For a successful save, the file pointer is positioned after the
//      last write.
//
//    CERT_STORE_SAVE_TO_MEMORY:
//      Saves to the specified memory blob. The pointer to
//      the memory blob is passed in pvSaveToPara. Given,
//          CRYPT_DATA_BLOB SaveBlob; pvSaveToPara = (void *) &SaveBlob;
//      Upon entry, the SaveBlob's pbData and cbData need to be initialized.
//      Upon return, cbData is updated with the actual length.
//      For a length only calculation, pbData should be set to NULL. If
//      pbData is non-NULL and cbData isn't large enough, FALSE is returned
//      with a last error of ERRROR_MORE_DATA.
//
//    CERT_STORE_SAVE_TO_FILENAME_A:
//    CERT_STORE_SAVE_TO_FILENAME_W:
//    CERT_STORE_SAVE_TO_FILENAME:
//      Opens the file and saves to it. The filename is passed in pvSaveToPara.
//      The filename is UNICODE for the "_W" option and ASCII for the "_A"
//      option. For "_W": given,
//          LPCWSTR pwszFilename; pvSaveToPara = (void *) pwszFilename;
//      For "_A": given,
//          LPCSTR pszFilename; pvSaveToPara = (void *) pszFilename;
//
//      Note, the default (without "_A" or "_W") is UNICODE.
//
//--------------------------------------------------------------------------
BOOL
WINAPI
CertSaveStore(
    IN HCERTSTORE hCertStore,
    IN DWORD dwEncodingType,
    IN DWORD dwSaveAs,
    IN DWORD dwSaveTo,
    IN OUT void *pvSaveToPara,
    IN DWORD dwFlags
    );

//+-------------------------------------------------------------------------
//  Certificate Store close flags
//--------------------------------------------------------------------------
#define CERT_CLOSE_STORE_FORCE_FLAG         0x00000001
#define CERT_CLOSE_STORE_CHECK_FLAG         0x00000002

//+-------------------------------------------------------------------------
//  Close a cert store handle.
//
//  There needs to be a corresponding close for each open and duplicate.
//
//  Even on the final close, the cert store isn't freed until all of its
//  certificate and CRL contexts have also been freed.
//
//  On the final close, the hCryptProv passed to CertStoreOpen is
//  CryptReleaseContext'ed.
//
//  To force the closure of the store with all of its memory freed, set the
//  CERT_STORE_CLOSE_FORCE_FLAG. This flag should be set when the caller does
//  its own reference counting and wants everything to vanish.
//
//  To check if all the store's certificates and CRLs have been freed and that
//  this is the last CertCloseStore, set the CERT_CLOSE_STORE_CHECK_FLAG. If
//  set and certs, CRLs or stores still need to be freed/closed, FALSE is
//  returned with LastError set to CRYPT_E_PENDING_CLOSE. Note, for FALSE,
//  the store is still closed. This is a diagnostic flag.
//
//  LastError is preserved unless CERT_CLOSE_STORE_CHECK_FLAG is set and FALSE
//  is returned.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CertCloseStore(
    IN HCERTSTORE hCertStore,
    DWORD dwFlags
    );

//+-------------------------------------------------------------------------
//  Get the subject certificate context uniquely identified by its Issuer and
//  SerialNumber from the store.
//
//  If the certificate isn't found, NULL is returned. Otherwise, a pointer to
//  a read only CERT_CONTEXT is returned. CERT_CONTEXT must be freed by calling
//  CertFreeCertificateContext. CertDuplicateCertificateContext can be called to make a
//  duplicate.
//
//  The returned certificate might not be valid. Normally, it would be
//  verified when getting its issuer certificate (CertGetIssuerCertificateFromStore).
//--------------------------------------------------------------------------
WINCRYPT32API
PCCERT_CONTEXT
WINAPI
CertGetSubjectCertificateFromStore(
    IN HCERTSTORE hCertStore,
    IN DWORD dwCertEncodingType,
    IN PCERT_INFO pCertId           // Only the Issuer and SerialNumber
                                    // fields are used
    );

//+-------------------------------------------------------------------------
//  Enumerate the certificate contexts in the store.
//
//  If a certificate isn't found, NULL is returned.
//  Otherwise, a pointer to a read only CERT_CONTEXT is returned. CERT_CONTEXT
//  must be freed by calling CertFreeCertificateContext or is freed when passed as the
//  pPrevCertContext on a subsequent call. CertDuplicateCertificateContext
//  can be called to make a duplicate.
//
//  pPrevCertContext MUST BE NULL to enumerate the first
//  certificate in the store. Successive certificates are enumerated by setting
//  pPrevCertContext to the CERT_CONTEXT returned by a previous call.
//
//  NOTE: a NON-NULL pPrevCertContext is always CertFreeCertificateContext'ed by
//  this function, even for an error.
//--------------------------------------------------------------------------
WINCRYPT32API
PCCERT_CONTEXT
WINAPI
CertEnumCertificatesInStore(
    IN HCERTSTORE hCertStore,
    IN PCCERT_CONTEXT pPrevCertContext
    );

//+-------------------------------------------------------------------------
//  Find the first or next certificate context in the store.
//
//  The certificate is found according to the dwFindType and its pvFindPara.
//  See below for a list of the find types and its parameters.
//
//  Currently dwFindFlags is only used for CERT_FIND_SUBJECT_ATTR,
//  CERT_FIND_ISSUER_ATTR or CERT_FIND_CTL_USAGE. Otherwise, must be set to 0.
//
//  Usage of dwCertEncodingType depends on the dwFindType.
//
//  If the first or next certificate isn't found, NULL is returned.
//  Otherwise, a pointer to a read only CERT_CONTEXT is returned. CERT_CONTEXT
//  must be freed by calling CertFreeCertificateContext or is freed when passed as the
//  pPrevCertContext on a subsequent call. CertDuplicateCertificateContext
//  can be called to make a duplicate.
//
//  pPrevCertContext MUST BE NULL on the first
//  call to find the certificate. To find the next certificate, the
//  pPrevCertContext is set to the CERT_CONTEXT returned by a previous call.
//
//  NOTE: a NON-NULL pPrevCertContext is always CertFreeCertificateContext'ed by
//  this function, even for an error.
//--------------------------------------------------------------------------
WINCRYPT32API
PCCERT_CONTEXT
WINAPI
CertFindCertificateInStore(
    IN HCERTSTORE hCertStore,
    IN DWORD dwCertEncodingType,
    IN DWORD dwFindFlags,
    IN DWORD dwFindType,
    IN const void *pvFindPara,
    IN PCCERT_CONTEXT pPrevCertContext
    );


//+-------------------------------------------------------------------------
// Certificate comparison functions
//--------------------------------------------------------------------------
#define CERT_COMPARE_MASK           0xFFFF
#define CERT_COMPARE_SHIFT          16
#define CERT_COMPARE_ANY            0
#define CERT_COMPARE_SHA1_HASH      1
#define CERT_COMPARE_NAME           2
#define CERT_COMPARE_ATTR           3
#define CERT_COMPARE_MD5_HASH       4
#define CERT_COMPARE_PROPERTY       5
#define CERT_COMPARE_PUBLIC_KEY     6
#define CERT_COMPARE_HASH           CERT_COMPARE_SHA1_HASH
#define CERT_COMPARE_NAME_STR_A     7
#define CERT_COMPARE_NAME_STR_W     8
#define CERT_COMPARE_KEY_SPEC       9
#define CERT_COMPARE_ENHKEY_USAGE   10
#define CERT_COMPARE_CTL_USAGE      CERT_COMPARE_ENHKEY_USAGE

//+-------------------------------------------------------------------------
//  dwFindType
//
//  The dwFindType definition consists of two components:
//   - comparison function
//   - certificate information flag
//--------------------------------------------------------------------------
#define CERT_FIND_ANY           (CERT_COMPARE_ANY << CERT_COMPARE_SHIFT)
#define CERT_FIND_SHA1_HASH     (CERT_COMPARE_SHA1_HASH << CERT_COMPARE_SHIFT)
#define CERT_FIND_MD5_HASH      (CERT_COMPARE_MD5_HASH << CERT_COMPARE_SHIFT)
#define CERT_FIND_HASH          CERT_FIND_SHA1_HASH
#define CERT_FIND_PROPERTY      (CERT_COMPARE_PROPERTY << CERT_COMPARE_SHIFT)
#define CERT_FIND_PUBLIC_KEY    (CERT_COMPARE_PUBLIC_KEY << CERT_COMPARE_SHIFT)
#define CERT_FIND_SUBJECT_NAME  (CERT_COMPARE_NAME << CERT_COMPARE_SHIFT | \
                                 CERT_INFO_SUBJECT_FLAG)
#define CERT_FIND_SUBJECT_ATTR  (CERT_COMPARE_ATTR << CERT_COMPARE_SHIFT | \
                                 CERT_INFO_SUBJECT_FLAG)
#define CERT_FIND_ISSUER_NAME   (CERT_COMPARE_NAME << CERT_COMPARE_SHIFT | \
                                 CERT_INFO_ISSUER_FLAG)
#define CERT_FIND_ISSUER_ATTR   (CERT_COMPARE_ATTR << CERT_COMPARE_SHIFT | \
                                 CERT_INFO_ISSUER_FLAG)
#define CERT_FIND_SUBJECT_STR_A (CERT_COMPARE_NAME_STR_A << CERT_COMPARE_SHIFT | \
                                 CERT_INFO_SUBJECT_FLAG)
#define CERT_FIND_SUBJECT_STR_W (CERT_COMPARE_NAME_STR_W << CERT_COMPARE_SHIFT | \
                                 CERT_INFO_SUBJECT_FLAG)
#define CERT_FIND_SUBJECT_STR   CERT_FIND_SUBJECT_STR_W
#define CERT_FIND_ISSUER_STR_A  (CERT_COMPARE_NAME_STR_A << CERT_COMPARE_SHIFT | \
                                 CERT_INFO_ISSUER_FLAG)
#define CERT_FIND_ISSUER_STR_W  (CERT_COMPARE_NAME_STR_W << CERT_COMPARE_SHIFT | \
                                 CERT_INFO_ISSUER_FLAG)
#define CERT_FIND_ISSUER_STR    CERT_FIND_ISSUER_STR_W
#define CERT_FIND_KEY_SPEC      (CERT_COMPARE_KEY_SPEC << CERT_COMPARE_SHIFT)
#define CERT_FIND_ENHKEY_USAGE  (CERT_COMPARE_ENHKEY_USAGE << CERT_COMPARE_SHIFT)
#define CERT_FIND_CTL_USAGE     CERT_FIND_ENHKEY_USAGE



//+-------------------------------------------------------------------------
//  CERT_FIND_ANY
//
//  Find any certificate.
//
//  pvFindPara isn't used.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CERT_FIND_HASH
//
//  Find a certificate with the specified hash.
//
//  pvFindPara points to a CRYPT_HASH_BLOB.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CERT_FIND_PROPERTY
//
//  Find a certificate having the specified property.
//
//  pvFindPara points to a DWORD containing the PROP_ID
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CERT_FIND_PUBLIC_KEY
//
//  Find a certificate matching the specified public key.
//
//  pvFindPara points to a CERT_PUBLIC_KEY_INFO containing the public key
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CERT_FIND_SUBJECT_NAME
//  CERT_FIND_ISSUER_NAME
//
//  Find a certificate with the specified subject/issuer name. Does an exact
//  match of the entire name.
//
//  Restricts search to certificates matching the dwCertEncodingType.
//
//  pvFindPara points to a CERT_NAME_BLOB.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CERT_FIND_SUBJECT_ATTR
//  CERT_FIND_ISSUER_ATTR
//
//  Find a certificate with the specified subject/issuer attributes.
//
//  Compares the attributes in the subject/issuer name with the
//  Relative Distinguished Name's (CERT_RDN) array of attributes specified in
//  pvFindPara. The comparison iterates through the CERT_RDN attributes and looks
//  for an attribute match in any of the subject/issuer's RDNs.
//
//  The CERT_RDN_ATTR fields can have the following special values:
//    pszObjId == NULL              - ignore the attribute object identifier
//    dwValueType == RDN_ANY_TYPE   - ignore the value type
//    Value.pbData == NULL          - match any value
//
//  Currently only an exact, case sensitive match is supported.
//
//  CERT_UNICODE_IS_RDN_ATTRS_FLAG should be set in dwFindFlags if the RDN was
//  initialized with unicode strings as for
//  CryptEncodeObject(X509_UNICODE_NAME).
//
//  Restricts search to certificates matching the dwCertEncodingType.
//
//  pvFindPara points to a CERT_RDN (defined in wincert.h).
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CERT_FIND_SUBJECT_STR_A
//  CERT_FIND_SUBJECT_STR_W | CERT_FIND_SUBJECT_STR
//  CERT_FIND_ISSUER_STR_A
//  CERT_FIND_ISSUER_STR_W  | CERT_FIND_ISSUER_STR
//
//  Find a certificate containing the specified subject/issuer name string.
//
//  First, the certificate's subject/issuer is converted to a name string
//  via CertNameToStrA/CertNameToStrW(CERT_SIMPLE_NAME_STR). Then, a
//  case insensitive substring within string match is performed.
//
//  Restricts search to certificates matching the dwCertEncodingType.
//
//  For *_STR_A, pvFindPara points to a null terminated character string.
//  For *_STR_W, pvFindPara points to a null terminated wide character string.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CERT_FIND_KEY_SPEC
//
//  Find a certificate having a CERT_KEY_SPEC_PROP_ID property matching
//  the specified KeySpec.
//
//  pvFindPara points to a DWORD containing the KeySpec.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CERT_FIND_ENHKEY_USAGE
//
//  Find a certificate having the szOID_ENHANCED_KEY_USAGE extension or
//  the CERT_ENHKEY_USAGE_PROP_ID and matching the specified pszUsageIdentifers.
//
//  pvFindPara points to a CERT_ENHKEY_USAGE data structure. If pvFindPara
//  is NULL or CERT_ENHKEY_USAGE's cUsageIdentifier is 0, then, matches any
//  certificate having enhanced key usage.
//
//  The CERT_FIND_OPTIONAL_ENHKEY_USAGE_FLAG can be set in dwFindFlags to
//  also match a certificate without either the extension or property.
//
//  If CERT_FIND_NO_ENHKEY_USAGE_FLAG is set in dwFindFlags, finds
//  certificates without the key usage extension or property. Setting this
//  flag takes precedence over pvFindPara being NULL.
//
//  If the CERT_FIND_EXT_ONLY_ENHKEY_USAGE_FLAG is set, then, only does a match
//  using the extension. If pvFindPara is NULL or cUsageIdentifier is set to
//  0, finds certificates having the extension. If
//  CERT_FIND_OPTIONAL_ENHKEY_USAGE_FLAG is set, also matches a certificate
//  without the extension. If CERT_FIND_NO_ENHKEY_USAGE_FLAG is set, finds
//  certificates without the extension.
//
//  If the CERT_FIND_EXT_PROP_ENHKEY_USAGE_FLAG is set, then, only does a match
//  using the property. If pvFindPara is NULL or cUsageIdentifier is set to
//  0, finds certificates having the property. If
//  CERT_FIND_OPTIONAL_ENHKEY_USAGE_FLAG is set, also matches a certificate
//  without the property. If CERT_FIND_NO_ENHKEY_USAGE_FLAG is set, finds
//  certificates without the property.
//--------------------------------------------------------------------------

#define CERT_FIND_OPTIONAL_ENHKEY_USAGE_FLAG  0x1
#define CERT_FIND_EXT_ONLY_ENHKEY_USAGE_FLAG  0x2
#define CERT_FIND_PROP_ONLY_ENHKEY_USAGE_FLAG 0x4
#define CERT_FIND_NO_ENHKEY_USAGE_FLAG        0x8

#define CERT_FIND_OPTIONAL_CTL_USAGE_FLAG   CERT_FIND_OPTIONAL_ENHKEY_USAGE_FLAG

#define CERT_FIND_EXT_ONLY_CTL_USAGE_FLAG \
        CERT_FIND_EXT_ONLY_ENHKEY_USAGE_FLAG

#define CERT_FIND_PROP_ONLY_CTL_USAGE_FLAG \
        CERT_FIND_PROP_ONLY_ENHKEY_USAGE_FLAG

#define CERT_FIND_NO_CTL_USAGE_FLAG         CERT_FIND_NO_ENHKEY_USAGE_FLAG

//+-------------------------------------------------------------------------
//  Get the certificate context from the store for the first or next issuer
//  of the specified subject certificate. Perform the enabled
//  verification checks on the subject. (Note, the checks are on the subject
//  using the returned issuer certificate.)
//
//  If the first or next issuer certificate isn't found, NULL is returned.
//  Otherwise, a pointer to a read only CERT_CONTEXT is returned. CERT_CONTEXT
//  must be freed by calling CertFreeCertificateContext or is freed when passed as the
//  pPrevIssuerContext on a subsequent call. CertDuplicateCertificateContext
//  can be called to make a duplicate.
//
//  For a self signed subject certificate, NULL is returned with LastError set
//  to CERT_STORE_SELF_SIGNED. The enabled verification checks are still done.
//
//  The pSubjectContext may have been obtained from this store, another store
//  or created by the caller application. When created by the caller, the
//  CertCreateCertificateContext function must have been called.
//
//  An issuer may have multiple certificates. This may occur when the validity
//  period is about to change. pPrevIssuerContext MUST BE NULL on the first
//  call to get the issuer. To get the next certificate for the issuer, the
//  pPrevIssuerContext is set to the CERT_CONTEXT returned by a previous call.
//
//  NOTE: a NON-NULL pPrevIssuerContext is always CertFreeCertificateContext'ed by
//  this function, even for an error.
//
//  The following flags can be set in *pdwFlags to enable verification checks
//  on the subject certificate context:
//      CERT_STORE_SIGNATURE_FLAG     - use the public key in the returned
//                                      issuer certificate to verify the
//                                      signature on the subject certificate.
//                                      Note, if pSubjectContext->hCertStore ==
//                                      hCertStore, the store provider might
//                                      be able to eliminate a redo of
//                                      the signature verify.
//      CERT_STORE_TIME_VALIDITY_FLAG - get the current time and verify that
//                                      its within the subject certificate's
//                                      validity period
//      CERT_STORE_REVOCATION_FLAG    - check if the subject certificate is on
//                                      the issuer's revocation list
//
//  If an enabled verification check fails, then, its flag is set upon return.
//  If CERT_STORE_REVOCATION_FLAG was enabled and the issuer doesn't have a
//  CRL in the store, then, CERT_STORE_NO_CRL_FLAG is set in addition to
//  the CERT_STORE_REVOCATION_FLAG.
//
//  If CERT_STORE_SIGNATURE_FLAG or CERT_STORE_REVOCATION_FLAG is set, then,
//  CERT_STORE_NO_ISSUER_FLAG is set if it doesn't have an issuer certificate
//  in the store.
//
//  For a verification check failure, a pointer to the issuer's CERT_CONTEXT
//  is still returned and SetLastError isn't updated.
//--------------------------------------------------------------------------
WINCRYPT32API
PCCERT_CONTEXT
WINAPI
CertGetIssuerCertificateFromStore(
    IN HCERTSTORE hCertStore,
    IN PCCERT_CONTEXT pSubjectContext,
    IN OPTIONAL PCCERT_CONTEXT pPrevIssuerContext,
    IN OUT DWORD *pdwFlags
    );

//+-------------------------------------------------------------------------
//  Perform the enabled verification checks on the subject certificate
//  using the issuer. Same checks and flags definitions as for the above
//  CertGetIssuerCertificateFromStore.
//
//  If you are only checking CERT_STORE_TIME_VALIDITY_FLAG, then, the
//  issuer can be NULL.
//
//  For a verification check failure, SUCCESS is still returned.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CertVerifySubjectCertificateContext(
    IN PCCERT_CONTEXT pSubject,
    IN OPTIONAL PCCERT_CONTEXT pIssuer,
    IN OUT DWORD *pdwFlags
    );

//+-------------------------------------------------------------------------
//  Duplicate a certificate context
//--------------------------------------------------------------------------
WINCRYPT32API
PCCERT_CONTEXT
WINAPI
CertDuplicateCertificateContext(
    IN PCCERT_CONTEXT pCertContext
    );

//+-------------------------------------------------------------------------
//  Create a certificate context from the encoded certificate. The created
//  context isn't put in a store.
//
//  Makes a copy of the encoded certificate in the created context.
//
//  If unable to decode and create the certificate context, NULL is returned.
//  Otherwise, a pointer to a read only CERT_CONTEXT is returned.
//  CERT_CONTEXT must be freed by calling CertFreeCertificateContext.
//  CertDuplicateCertificateContext can be called to make a duplicate.
//
//  CertSetCertificateContextProperty and CertGetCertificateContextProperty can be called
//  to store properties for the certificate.
//--------------------------------------------------------------------------
WINCRYPT32API
PCCERT_CONTEXT
WINAPI
CertCreateCertificateContext(
    IN DWORD dwCertEncodingType,
    IN const BYTE *pbCertEncoded,
    IN DWORD cbCertEncoded
    );

//+-------------------------------------------------------------------------
//  Free a certificate context
//
//  There needs to be a corresponding free for each context obtained by a
//  get, find, duplicate or create.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CertFreeCertificateContext(
    IN PCCERT_CONTEXT pCertContext
    );

//+-------------------------------------------------------------------------
//  Set the property for the specified certificate context.
//
//  The type definition for pvData depends on the dwPropId value. There are
//  five predefined types:
//      CERT_KEY_PROV_HANDLE_PROP_ID - a HCRYPTPROV for the certificate's
//      private key is passed in pvData. Updates the hCryptProv field
//      of the CERT_KEY_CONTEXT_PROP_ID. If the CERT_KEY_CONTEXT_PROP_ID
//      doesn't exist, its created with all the other fields zeroed out. If
//      CERT_STORE_NO_CRYPT_RELEASE_FLAG isn't set, HCRYPTPROV is implicitly
//      released when either the property is set to NULL or on the final
//      free of the CertContext.
//
//      CERT_KEY_PROV_INFO_PROP_ID - a PCRYPT_KEY_PROV_INFO for the certificate's
//      private key is passed in pvData.
//
//      CERT_SHA1_HASH_PROP_ID -
//      CERT_MD5_HASH_PROP_ID  - normally, either property is implicitly
//      set by doing a CertGetCertificateContextProperty. pvData points to a
//      CRYPT_HASH_BLOB.
//
//      CERT_KEY_CONTEXT_PROP_ID - a PCERT_KEY_CONTEXT for the certificate's
//      private key is passed in pvData. The CERT_KEY_CONTEXT contains both the
//      hCryptProv and dwKeySpec for the private key.
//      See the CERT_KEY_PROV_HANDLE_PROP_ID for more information about
//      the hCryptProv field and dwFlags settings. Note, more fields may
//      be added for this property. The cbSize field value will be adjusted
//      accordingly.
//
//      CERT_KEY_SPEC_PROP_ID - the dwKeySpec for the private key. pvData
//      points to a DWORD containing the KeySpec
//
//      CERT_ENHKEY_USAGE_PROP_ID - enhanced key usage definition for the
//      certificate. pvData points to a CRYPT_DATA_BLOB containing an
//      ASN.1 encoded CERT_ENHKEY_USAGE (encoded via
//      CryptEncodeObject(X509_ENHANCED_KEY_USAGE).
//
//      CERT_NEXT_UPDATE_LOCATION_PROP_ID - location of the next update.
//      Currently only applicable to CTLs. pvData points to a CRYPT_DATA_BLOB
//      containing an ASN.1 encoded CERT_ALT_NAME_INFO (encoded via
//      CryptEncodeObject(X509_ALTERNATE_NAME)).
//
//      CERT_FRIENDLY_NAME_PROP_ID - friendly name for the cert, CRL or CTL.
//      pvData points to a CRYPT_DATA_BLOB. pbData is a pointer to a NULL
//      terminated unicode, wide character string.
//      cbData = (wcslen((LPWSTR) pbData) + 1) * sizeof(WCHAR).
//
//  For all the other PROP_IDs: an encoded PCRYPT_DATA_BLOB is passed in pvData.
//
//  If the property already exists, then, the old value is deleted and silently
//  replaced. Setting, pvData to NULL, deletes the property.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CertSetCertificateContextProperty(
    IN PCCERT_CONTEXT pCertContext,
    IN DWORD dwPropId,
    IN DWORD dwFlags,
    IN const void *pvData
    );

//+-------------------------------------------------------------------------
//  Get the property for the specified certificate context.
//
//  For CERT_KEY_PROV_HANDLE_PROP_ID, pvData points to a HCRYPTPROV.
//
//  For CERT_KEY_PROV_INFO_PROP_ID, pvData points to a CRYPT_KEY_PROV_INFO structure.
//  Elements pointed to by fields in the pvData structure follow the
//  structure. Therefore, *pcbData may exceed the size of the structure.
//
//  For CERT_KEY_CONTEXT_PROP_ID, pvData points to a CERT_KEY_CONTEXT structure.
//
//  For CERT_KEY_SPEC_PROP_ID, pvData points to a DWORD containing the KeySpec.
//  If the CERT_KEY_CONTEXT_PROP_ID exists, the KeySpec is obtained from there.
//  Otherwise, if the CERT_KEY_PROV_INFO_PROP_ID exists, its the source
//  of the KeySpec.
//
//  For CERT_SHA1_HASH_PROP_ID or CERT_MD5_HASH_PROP_ID, if the hash
//  doesn't already exist, then, its computed via CryptHashCertificate()
//  and then set. pvData points to the computed hash. Normally, the length
//  is 20 bytes for SHA and 16 for MD5.
//
//  For all other PROP_IDs, pvData points to an encoded array of bytes.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CertGetCertificateContextProperty(
    IN PCCERT_CONTEXT pCertContext,
    IN DWORD dwPropId,
    OUT void *pvData,
    IN OUT DWORD *pcbData
    );

//+-------------------------------------------------------------------------
//  Enumerate the properties for the specified certificate context.
//
//  To get the first property, set dwPropId to 0. The ID of the first
//  property is returned. To get the next property, set dwPropId to the
//  ID returned by the last call. To enumerate all the properties continue
//  until 0 is returned.
//
//  CertGetCertificateContextProperty is called to get the property's data.
//
//  Note, since, the CERT_KEY_PROV_HANDLE_PROP_ID and CERT_KEY_SPEC_PROP_ID
//  properties are stored as fields in the CERT_KEY_CONTEXT_PROP_ID
//  property, they aren't enumerated individually.
//--------------------------------------------------------------------------
WINCRYPT32API
DWORD
WINAPI
CertEnumCertificateContextProperties(
    IN PCCERT_CONTEXT pCertContext,
    IN DWORD dwPropId
    );

//+-------------------------------------------------------------------------
//  Get the first or next CRL context from the store for the specified
//  issuer certificate. Perform the enabled verification checks on the CRL.
//
//  If the first or next CRL isn't found, NULL is returned.
//  Otherwise, a pointer to a read only CRL_CONTEXT is returned. CRL_CONTEXT
//  must be freed by calling CertFreeCRLContext. However, the free must be
//  pPrevCrlContext on a subsequent call. CertDuplicateCRLContext
//  can be called to make a duplicate.
//
//  The pIssuerContext may have been obtained from this store, another store
//  or created by the caller application. When created by the caller, the
//  CertCreateCertificateContext function must have been called.
//
//  If pIssuerContext == NULL, finds all the CRLs in the store.
//
//  An issuer may have multiple CRLs. For example, it generates delta CRLs
//  using a X.509 v3 extension. pPrevCrlContext MUST BE NULL on the first
//  call to get the CRL. To get the next CRL for the issuer, the
//  pPrevCrlContext is set to the CRL_CONTEXT returned by a previous call.
//
//  NOTE: a NON-NULL pPrevCrlContext is always CertFreeCRLContext'ed by
//  this function, even for an error.
//
//  The following flags can be set in *pdwFlags to enable verification checks
//  on the returned CRL:
//      CERT_STORE_SIGNATURE_FLAG     - use the public key in the
//                                      issuer's certificate to verify the
//                                      signature on the returned CRL.
//                                      Note, if pIssuerContext->hCertStore ==
//                                      hCertStore, the store provider might
//                                      be able to eliminate a redo of
//                                      the signature verify.
//      CERT_STORE_TIME_VALIDITY_FLAG - get the current time and verify that
//                                      its within the CRL's ThisUpdate and
//                                      NextUpdate validity period.
//
//  If an enabled verification check fails, then, its flag is set upon return.
//
//  If pIssuerContext == NULL, then, an enabled CERT_STORE_SIGNATURE_FLAG
//  always fails and the CERT_STORE_NO_ISSUER_FLAG is also set.
//
//  For a verification check failure, a pointer to the first or next
//  CRL_CONTEXT is still returned and SetLastError isn't updated.
//--------------------------------------------------------------------------
WINCRYPT32API
PCCRL_CONTEXT
WINAPI
CertGetCRLFromStore(
    IN HCERTSTORE hCertStore,
    IN OPTIONAL PCCERT_CONTEXT pIssuerContext,
    IN PCCRL_CONTEXT pPrevCrlContext,
    IN OUT DWORD *pdwFlags
    );


//+-------------------------------------------------------------------------
//  Duplicate a CRL context
//--------------------------------------------------------------------------
WINCRYPT32API
PCCRL_CONTEXT
WINAPI
CertDuplicateCRLContext(
    IN PCCRL_CONTEXT pCrlContext
    );

//+-------------------------------------------------------------------------
//  Create a CRL context from the encoded CRL. The created
//  context isn't put in a store.
//
//  Makes a copy of the encoded CRL in the created context.
//
//  If unable to decode and create the CRL context, NULL is returned.
//  Otherwise, a pointer to a read only CRL_CONTEXT is returned.
//  CRL_CONTEXT must be freed by calling CertFreeCRLContext.
//  CertDuplicateCRLContext can be called to make a duplicate.
//
//  CertSetCRLContextProperty and CertGetCRLContextProperty can be called
//  to store properties for the CRL.
//--------------------------------------------------------------------------
WINCRYPT32API
PCCRL_CONTEXT
WINAPI
CertCreateCRLContext(
    IN DWORD dwCertEncodingType,
    IN const BYTE *pbCrlEncoded,
    IN DWORD cbCrlEncoded
    );

//+-------------------------------------------------------------------------
//  Free a CRL context
//
//  There needs to be a corresponding free for each context obtained by a
//  get, duplicate or create.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CertFreeCRLContext(
    IN PCCRL_CONTEXT pCrlContext
    );

//+-------------------------------------------------------------------------
//  Set the property for the specified CRL context.
//
//  Same Property Ids and semantics as CertSetCertificateContextProperty.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CertSetCRLContextProperty(
    IN PCCRL_CONTEXT pCrlContext,
    IN DWORD dwPropId,
    IN DWORD dwFlags,
    IN const void *pvData
    );

//+-------------------------------------------------------------------------
//  Get the property for the specified CRL context.
//
//  Same Property Ids and semantics as CertGetCertificateContextProperty.
//
//  CERT_SHA1_HASH_PROP_ID or CERT_MD5_HASH_PROP_ID is the predefined
//  property of most interest.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CertGetCRLContextProperty(
    IN PCCRL_CONTEXT pCrlContext,
    IN DWORD dwPropId,
    OUT void *pvData,
    IN OUT DWORD *pcbData
    );

//+-------------------------------------------------------------------------
//  Enumerate the properties for the specified CRL context.
//
//  To get the first property, set dwPropId to 0. The ID of the first
//  property is returned. To get the next property, set dwPropId to the
//  ID returned by the last call. To enumerate all the properties continue
//  until 0 is returned.
//
//  CertGetCRLContextProperty is called to get the property's data.
//--------------------------------------------------------------------------
WINCRYPT32API
DWORD
WINAPI
CertEnumCRLContextProperties(
    IN PCCRL_CONTEXT pCrlContext,
    IN DWORD dwPropId
    );

//+-------------------------------------------------------------------------
// Add certificate/CRL, encoded, context or element disposition values.
//--------------------------------------------------------------------------
#define CERT_STORE_ADD_NEW                  1
#define CERT_STORE_ADD_USE_EXISTING         2
#define CERT_STORE_ADD_REPLACE_EXISTING     3
#define CERT_STORE_ADD_ALWAYS               4

//+-------------------------------------------------------------------------
//  Add the encoded certificate to the store according to the specified
//  disposition action.
//
//  Makes a copy of the encoded certificate before adding to the store.
//
//  dwAddDispostion specifies the action to take if the certificate
//  already exists in the store. This parameter must be one of the following
//  values:
//    CERT_STORE_ADD_NEW
//      Fails if the certificate already exists in the store. LastError
//      is set to CRYPT_E_EXISTS.
//    CERT_STORE_ADD_USE_EXISTING
//      If the certifcate already exists, then, its used and if ppCertContext
//      is non-NULL, the existing context is duplicated.
//    CERT_STORE_ADD_REPLACE_EXISTING
//      If the certificate already exists, then, the existing certificate
//      context is deleted before creating and adding the new context.
//    CERT_STORE_ADD_ALWAYS
//      No check is made to see if the certificate already exists. A
//      new certificate context is always created. This may lead to
//      duplicates in the store.
//
//  CertGetSubjectCertificateFromStore is called to determine if the
//  certificate already exists in the store.
//
//  ppCertContext can be NULL, indicating the caller isn't interested
//  in getting the CERT_CONTEXT of the added or existing certificate.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CertAddEncodedCertificateToStore(
    IN HCERTSTORE hCertStore,
    IN DWORD dwCertEncodingType,
    IN const BYTE *pbCertEncoded,
    IN DWORD cbCertEncoded,
    IN DWORD dwAddDisposition,
    OUT OPTIONAL PCCERT_CONTEXT *ppCertContext
    );

//+-------------------------------------------------------------------------
//  Add the certificate context to the store according to the specified
//  disposition action.
//
//  In addition to the encoded certificate, the context's properties are
//  also copied.  Note, the CERT_KEY_CONTEXT_PROP_ID property (and its
//  CERT_KEY_PROV_HANDLE_PROP_ID or CERT_KEY_SPEC_PROP_ID) isn't copied.
//
//  Makes a copy of the certificate context before adding to the store.
//
//  dwAddDispostion specifies the action to take if the certificate
//  already exists in the store. This parameter must be one of the following
//  values:
//    CERT_STORE_ADD_NEW
//      Fails if the certificate already exists in the store. LastError
//      is set to CRYPT_E_EXISTS.
//    CERT_STORE_ADD_USE_EXISTING
//      If the certifcate already exists, then, its used and if ppStoreContext
//      is non-NULL, the existing context is duplicated. Iterates
//      through pCertContext's properties and only copies the properties
//      that don't already exist. The SHA1 and MD5 hash properties aren't
//      copied.
//    CERT_STORE_ADD_REPLACE_EXISTING
//      If the certificate already exists, then, the existing certificate
//      context is deleted before creating and adding a new context.
//      Properties are copied before doing the add.
//    CERT_STORE_ADD_ALWAYS
//      No check is made to see if the certificate already exists. A
//      new certificate context is always created and added. This may lead to
//      duplicates in the store. Properties are
//      copied before doing the add.
//
//  CertGetSubjectCertificateFromStore is called to determine if the
//  certificate already exists in the store.
//
//  ppStoreContext can be NULL, indicating the caller isn't interested
//  in getting the CERT_CONTEXT of the added or existing certificate.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CertAddCertificateContextToStore(
    IN HCERTSTORE hCertStore,
    IN PCCERT_CONTEXT pCertContext,
    IN DWORD dwAddDisposition,
    OUT OPTIONAL PCCERT_CONTEXT *ppStoreContext
    );


//+-------------------------------------------------------------------------
//  Certificate Store Context Types
//--------------------------------------------------------------------------
#define CERT_STORE_CERTIFICATE_CONTEXT  1
#define CERT_STORE_CRL_CONTEXT          2
#define CERT_STORE_CTL_CONTEXT          3

//+-------------------------------------------------------------------------
//  Certificate Store Context Bit Flags
//--------------------------------------------------------------------------
#define CERT_STORE_ALL_CONTEXT_FLAG             (~0UL)
#define CERT_STORE_CERTIFICATE_CONTEXT_FLAG     \
                (1 << CERT_STORE_CERTIFICATE_CONTEXT)
#define CERT_STORE_CRL_CONTEXT_FLAG             \
                (1 << CERT_STORE_CRL_CONTEXT)
#define CERT_STORE_CTL_CONTEXT_FLAG             \
                (1 << CERT_STORE_CTL_CONTEXT)

//+-------------------------------------------------------------------------
//  Add the serialized certificate or CRL element to the store.
//
//  The serialized element contains the encoded certificate, CRL or CTL and
//  its properties, such as, CERT_KEY_PROV_INFO_PROP_ID.
//
//  If hCertStore is NULL, creates a certificate, CRL or CTL context not
//  residing in any store.
//
//  dwAddDispostion specifies the action to take if the certificate or CRL
//  already exists in the store. See CertAddCertificateContextToStore for a
//  list of and actions taken.
//
//  dwFlags currently isn't used and should be set to 0.
//
//  dwContextTypeFlags specifies the set of allowable contexts. For example, to
//  add either a certificate or CRL, set dwContextTypeFlags to:
//      CERT_STORE_CERTIFICATE_CONTEXT_FLAG | CERT_STORE_CRL_CONTEXT_FLAG
//
//  *pdwContextType is updated with the type of the context returned in
//  *ppvContxt. pdwContextType or ppvContext can be NULL, indicating the
//  caller isn't interested in getting the output. If *ppvContext is
//  returned it must be freed by calling CertFreeCertificateContext or
//  CertFreeCRLContext.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CertAddSerializedElementToStore(
    IN HCERTSTORE hCertStore,
    IN const BYTE *pbElement,
    IN DWORD cbElement,
    IN DWORD dwAddDisposition,
    IN DWORD dwFlags,
    IN DWORD dwContextTypeFlags,
    OUT OPTIONAL DWORD *pdwContextType,
    OUT OPTIONAL const void **ppvContext
    );

//+-------------------------------------------------------------------------
//  Delete the specified certificate from the store.
//
//  All subsequent gets or finds for the certificate will fail. However,
//  memory allocated for the certificate isn't freed until all of its contexts
//  have also been freed.
//
//  The pCertContext is obtained from a get, enum, find or duplicate.
//
//  Some store provider implementations might also delete the issuer's CRLs
//  if this is the last certificate for the issuer in the store.
//
//  NOTE: the pCertContext is always CertFreeCertificateContext'ed by
//  this function, even for an error.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CertDeleteCertificateFromStore(
    IN PCCERT_CONTEXT pCertContext
    );

//+-------------------------------------------------------------------------
//  Add the encoded CRL to the store according to the specified
//  disposition option.
//
//  Makes a copy of the encoded CRL before adding to the store.
//
//  dwAddDispostion specifies the action to take if the CRL
//  already exists in the store. See CertAddEncodedCertificateToStore for a
//  list of and actions taken.
//
//  Compares the CRL's Issuer to determine if the CRL already exists in the
//  store.
//
//  ppCrlContext can be NULL, indicating the caller isn't interested
//  in getting the CRL_CONTEXT of the added or existing CRL.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CertAddEncodedCRLToStore(
    IN HCERTSTORE hCertStore,
    IN DWORD dwCertEncodingType,
    IN const BYTE *pbCrlEncoded,
    IN DWORD cbCrlEncoded,
    IN DWORD dwAddDisposition,
    OUT OPTIONAL PCCRL_CONTEXT *ppCrlContext
    );

//+-------------------------------------------------------------------------
//  Add the CRL context to the store according to the specified
//  disposition option.
//
//  In addition to the encoded CRL, the context's properties are
//  also copied.  Note, the CERT_KEY_CONTEXT_PROP_ID property (and its
//  CERT_KEY_PROV_HANDLE_PROP_ID or CERT_KEY_SPEC_PROP_ID) isn't copied.
//
//  Makes a copy of the encoded CRL before adding to the store.
//
//  dwAddDispostion specifies the action to take if the CRL
//  already exists in the store. See CertAddCertificateContextToStore for a
//  list of and actions taken.
//
//  Compares the CRL's Issuer, ThisUpdate and NextUpdate to determine
//  if the CRL already exists in the store.
//
//  ppStoreContext can be NULL, indicating the caller isn't interested
//  in getting the CRL_CONTEXT of the added or existing CRL.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CertAddCRLContextToStore(
    IN HCERTSTORE hCertStore,
    IN PCCRL_CONTEXT pCrlContext,
    IN DWORD dwAddDisposition,
    OUT OPTIONAL PCCRL_CONTEXT *ppStoreContext
    );

//+-------------------------------------------------------------------------
//  Delete the specified CRL from the store.
//
//  All subsequent gets for the CRL will fail. However,
//  memory allocated for the CRL isn't freed until all of its contexts
//  have also been freed.
//
//  The pCrlContext is obtained from a get or duplicate.
//
//  NOTE: the pCrlContext is always CertFreeCRLContext'ed by
//  this function, even for an error.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CertDeleteCRLFromStore(
    IN PCCRL_CONTEXT pCrlContext
    );

//+-------------------------------------------------------------------------
//  Serialize the certificate context's encoded certificate and its
//  properties.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CertSerializeCertificateStoreElement(
    IN PCCERT_CONTEXT pCertContext,
    IN DWORD dwFlags,
    OUT BYTE *pbElement,
    IN OUT DWORD *pcbElement
    );


//+-------------------------------------------------------------------------
//  Serialize the CRL context's encoded CRL and its properties.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CertSerializeCRLStoreElement(
    IN PCCRL_CONTEXT pCrlContext,
    IN DWORD dwFlags,
    OUT BYTE *pbElement,
    IN OUT DWORD *pcbElement
    );


//+=========================================================================
//  Certificate Trust List (CTL) Store Data Structures and APIs
//==========================================================================

//+-------------------------------------------------------------------------
//  Duplicate a CTL context
//--------------------------------------------------------------------------
WINCRYPT32API
PCCTL_CONTEXT
WINAPI
CertDuplicateCTLContext(
    IN PCCTL_CONTEXT pCtlContext
    );

//+-------------------------------------------------------------------------
//  Create a CTL context from the encoded CTL. The created
//  context isn't put in a store.
//
//  Makes a copy of the encoded CTL in the created context.
//
//  If unable to decode and create the CTL context, NULL is returned.
//  Otherwise, a pointer to a read only CTL_CONTEXT is returned.
//  CTL_CONTEXT must be freed by calling CertFreeCTLContext.
//  CertDuplicateCTLContext can be called to make a duplicate.
//
//  CertSetCTLContextProperty and CertGetCTLContextProperty can be called
//  to store properties for the CTL.
//--------------------------------------------------------------------------
WINCRYPT32API
PCCTL_CONTEXT
WINAPI
CertCreateCTLContext(
    IN DWORD dwMsgAndCertEncodingType,
    IN const BYTE *pbCtlEncoded,
    IN DWORD cbCtlEncoded
    );

//+-------------------------------------------------------------------------
//  Free a CTL context
//
//  There needs to be a corresponding free for each context obtained by a
//  get, duplicate or create.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CertFreeCTLContext(
    IN PCCTL_CONTEXT pCtlContext
    );

//+-------------------------------------------------------------------------
//  Set the property for the specified CTL context.
//
//  Same Property Ids and semantics as CertSetCertificateContextProperty.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CertSetCTLContextProperty(
    IN PCCTL_CONTEXT pCtlContext,
    IN DWORD dwPropId,
    IN DWORD dwFlags,
    IN const void *pvData
    );

//+-------------------------------------------------------------------------
//  Get the property for the specified CTL context.
//
//  Same Property Ids and semantics as CertGetCertificateContextProperty.
//
//  CERT_SHA1_HASH_PROP_ID or CERT_NEXT_UPDATE_LOCATION_PROP_ID are the
//  predefined properties of most interest.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CertGetCTLContextProperty(
    IN PCCTL_CONTEXT pCtlContext,
    IN DWORD dwPropId,
    OUT void *pvData,
    IN OUT DWORD *pcbData
    );

//+-------------------------------------------------------------------------
//  Enumerate the properties for the specified CTL context.
//--------------------------------------------------------------------------
WINCRYPT32API
DWORD
WINAPI
CertEnumCTLContextProperties(
    IN PCCTL_CONTEXT pCtlContext,
    IN DWORD dwPropId
    );

//+-------------------------------------------------------------------------
//  Enumerate the CTL contexts in the store.
//
//  If a CTL isn't found, NULL is returned.
//  Otherwise, a pointer to a read only CTL_CONTEXT is returned. CTL_CONTEXT
//  must be freed by calling CertFreeCTLContext or is freed when passed as the
//  pPrevCtlContext on a subsequent call. CertDuplicateCTLContext
//  can be called to make a duplicate.
//
//  pPrevCtlContext MUST BE NULL to enumerate the first
//  CTL in the store. Successive CTLs are enumerated by setting
//  pPrevCtlContext to the CTL_CONTEXT returned by a previous call.
//
//  NOTE: a NON-NULL pPrevCtlContext is always CertFreeCTLContext'ed by
//  this function, even for an error.
//--------------------------------------------------------------------------
WINCRYPT32API
PCCTL_CONTEXT
WINAPI
CertEnumCTLsInStore(
    IN HCERTSTORE hCertStore,
    IN PCCTL_CONTEXT pPrevCtlContext
    );

//+-------------------------------------------------------------------------
//  Attempt to find the specified subject in the CTL.
//
//  For CTL_CERT_SUBJECT_TYPE, pvSubject points to a CERT_CONTEXT. The CTL's
//  SubjectAlgorithm is examined to determine the representation of the
//  subject's identity. Initially, only SHA1 or MD5 hash will be supported.
//  The appropriate hash property is obtained from the CERT_CONTEXT.
//
//  For CTL_ANY_SUBJECT_TYPE, pvSubject points to the CTL_ANY_SUBJECT_INFO
//  structure which contains the SubjectAlgorithm to be matched in the CTL
//  and the SubjectIdentifer to be matched in one of the CTL entries.
//
//  The certificate's hash or the CTL_ANY_SUBJECT_INFO's SubjectIdentifier
//  is used as the key in searching the subject entries. A binary
//  memory comparison is done between the key and the entry's SubjectIdentifer.
//
//  dwEncodingType isn't used for either of the above SubjectTypes.
//--------------------------------------------------------------------------
WINCRYPT32API
PCTL_ENTRY
WINAPI
CertFindSubjectInCTL(
    IN DWORD dwEncodingType,
    IN DWORD dwSubjectType,
    IN void *pvSubject,
    IN PCCTL_CONTEXT pCtlContext,
    IN DWORD dwFlags
    );

// Subject Types:
//  CTL_ANY_SUBJECT_TYPE, pvSubject points to following CTL_ANY_SUBJECT_INFO.
//  CTL_CERT_SUBJECT_TYPE, pvSubject points to CERT_CONTEXT.
#define CTL_ANY_SUBJECT_TYPE            1
#define CTL_CERT_SUBJECT_TYPE           2

typedef struct _CTL_ANY_SUBJECT_INFO {
    CRYPT_ALGORITHM_IDENTIFIER  SubjectAlgorithm;
    CRYPT_DATA_BLOB             SubjectIdentifier;
} CTL_ANY_SUBJECT_INFO, *PCTL_ANY_SUBJECT_INFO;

//+-------------------------------------------------------------------------
//  Find the first or next CTL context in the store.
//
//  The CTL is found according to the dwFindType and its pvFindPara.
//  See below for a list of the find types and its parameters.
//
//  Currently dwFindFlags isn't used and must be set to 0.
//
//  Usage of dwMsgAndCertEncodingType depends on the dwFindType.
//
//  If the first or next CTL isn't found, NULL is returned.
//  Otherwise, a pointer to a read only CTL_CONTEXT is returned. CTL_CONTEXT
//  must be freed by calling CertFreeCTLContext or is freed when passed as the
//  pPrevCtlContext on a subsequent call. CertDuplicateCTLContext
//  can be called to make a duplicate.
//
//  pPrevCtlContext MUST BE NULL on the first
//  call to find the CTL. To find the next CTL, the
//  pPrevCtlContext is set to the CTL_CONTEXT returned by a previous call.
//
//  NOTE: a NON-NULL pPrevCtlContext is always CertFreeCTLContext'ed by
//  this function, even for an error.
//--------------------------------------------------------------------------
WINCRYPT32API
PCCTL_CONTEXT
WINAPI
CertFindCTLInStore(
    IN HCERTSTORE hCertStore,
    IN DWORD dwMsgAndCertEncodingType,
    IN DWORD dwFindFlags,
    IN DWORD dwFindType,
    IN const void *pvFindPara,
    IN PCCTL_CONTEXT pPrevCtlContext
    );

#define CTL_FIND_ANY                0
#define CTL_FIND_SHA1_HASH          1
#define CTL_FIND_MD5_HASH           2
#define CTL_FIND_USAGE              3
#define CTL_FIND_SUBJECT            4

typedef struct _CTL_FIND_USAGE_PARA {
    DWORD               cbSize;
    CTL_USAGE           SubjectUsage;   // optional
    CRYPT_DATA_BLOB     ListIdentifier; // optional
    PCERT_INFO          pSigner;        // optional
} CTL_FIND_USAGE_PARA, *PCTL_FIND_USAGE_PARA;

#define CTL_FIND_NO_LIST_ID_CBDATA  0xFFFFFFFF
#define CTL_FIND_NO_SIGNER_PTR      ((PCERT_INFO) 0xFFFFFFFF)

#define CTL_FIND_SAME_USAGE_FLAG    0x1


typedef struct _CTL_FIND_SUBJECT_PARA {
    DWORD                   cbSize;
    PCTL_FIND_USAGE_PARA    pUsagePara; // optional
    DWORD                   dwSubjectType;
    void                    *pvSubject;
} CTL_FIND_SUBJECT_PARA, *PCTL_FIND_SUBJECT_PARA;


//+-------------------------------------------------------------------------
//  CTL_FIND_ANY
//
//  Find any CTL.
//
//  pvFindPara isn't used.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CTL_FIND_SHA1_HASH
//  CTL_FIND_MD5_HASH
//
//  Find a CTL with the specified hash.
//
//  pvFindPara points to a CRYPT_HASH_BLOB.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CTL_FIND_USAGE
//
//  Find a CTL having the specified usage identifiers, list identifier or
//  signer. The CertEncodingType of the signer is obtained from the
//  dwMsgAndCertEncodingType parameter.
//
//  pvFindPara points to a CTL_FIND_USAGE_PARA data structure. The
//  SubjectUsage.cUsageIdentifer can be 0 to match any usage. The
//  ListIdentifier.cbData can be 0 to match any list identifier. To only match
//  CTLs without a ListIdentifier, cbData must be set to
//  CTL_FIND_NO_LIST_ID_CBDATA. pSigner can be NULL to match any signer. Only
//  the Issuer and SerialNumber fields of the pSigner's PCERT_INFO are used.
//  To only match CTLs without a signer, pSigner must be set to
//  CTL_FIND_NO_SIGNER_PTR.
//
//  The CTL_FIND_SAME_USAGE_FLAG can be set in dwFindFlags to
//  only match CTLs with the same usage identifiers. CTLs having additional
//  usage identifiers aren't matched. For example, if only "1.2.3" is specified
//  in CTL_FIND_USAGE_PARA, then, for a match, the CTL must only contain
//  "1.2.3" and not any additional usage identifers.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CTL_FIND_SUBJECT
//
//  Find a CTL having the specified subject. CertFindSubjectInCTL can be
//  called to get a pointer to the subject's entry in the CTL.  pUsagePara can
//  optionally be set to enable the above CTL_FIND_USAGE matching.
//
//  pvFindPara points to a CTL_FIND_SUBJECT_PARA data structure.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  Add the encoded CTL to the store according to the specified
//  disposition option.
//
//  Makes a copy of the encoded CTL before adding to the store.
//
//  dwAddDispostion specifies the action to take if the CTL
//  already exists in the store. See CertAddEncodedCertificateToStore for a
//  list of and actions taken.
//
//  Compares the CTL's SubjectUsage, ListIdentifier and any of its signers
//  to determine if the CTL already exists in the store.
//
//  ppCtlContext can be NULL, indicating the caller isn't interested
//  in getting the CTL_CONTEXT of the added or existing CTL.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CertAddEncodedCTLToStore(
    IN HCERTSTORE hCertStore,
    IN DWORD dwMsgAndCertEncodingType,
    IN const BYTE *pbCtlEncoded,
    IN DWORD cbCtlEncoded,
    IN DWORD dwAddDisposition,
    OUT OPTIONAL PCCTL_CONTEXT *ppCtlContext
    );

//+-------------------------------------------------------------------------
//  Add the CTL context to the store according to the specified
//  disposition option.
//
//  In addition to the encoded CTL, the context's properties are
//  also copied.  Note, the CERT_KEY_CONTEXT_PROP_ID property (and its
//  CERT_KEY_PROV_HANDLE_PROP_ID or CERT_KEY_SPEC_PROP_ID) isn't copied.
//
//  Makes a copy of the encoded CTL before adding to the store.
//
//  dwAddDispostion specifies the action to take if the CTL
//  already exists in the store. See CertAddCertificateContextToStore for a
//  list of and actions taken.
//
//  Compares the CTL's SubjectUsage, ListIdentifier and any of its signers
//  to determine if the CTL already exists in the store.
//
//  ppStoreContext can be NULL, indicating the caller isn't interested
//  in getting the CTL_CONTEXT of the added or existing CTL.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CertAddCTLContextToStore(
    IN HCERTSTORE hCertStore,
    IN PCCTL_CONTEXT pCtlContext,
    IN DWORD dwAddDisposition,
    OUT OPTIONAL PCCTL_CONTEXT *ppStoreContext
    );

//+-------------------------------------------------------------------------
//  Serialize the CTL context's encoded CTL and its properties.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CertSerializeCTLStoreElement(
    IN PCCTL_CONTEXT pCtlContext,
    IN DWORD dwFlags,
    OUT BYTE *pbElement,
    IN OUT DWORD *pcbElement
    );

//+-------------------------------------------------------------------------
//  Delete the specified CTL from the store.
//
//  All subsequent gets for the CTL will fail. However,
//  memory allocated for the CTL isn't freed until all of its contexts
//  have also been freed.
//
//  The pCtlContext is obtained from a get or duplicate.
//
//  NOTE: the pCtlContext is always CertFreeCTLContext'ed by
//  this function, even for an error.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CertDeleteCTLFromStore(
    IN PCCTL_CONTEXT pCtlContext
    );


//+=========================================================================
//  Enhanced Key Usage Helper Functions
//==========================================================================

//+-------------------------------------------------------------------------
//  Get the enhanced key usage extension or property from the certificate
//  and decode.
//
//  If the CERT_FIND_EXT_ONLY_ENHKEY_USAGE_FLAG is set, then, only get the
//  extension.
//
//  If the CERT_FIND_PROP_ONLY_ENHKEY_USAGE_FLAG is set, then, only get the
//  property.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CertGetEnhancedKeyUsage(
    IN PCCERT_CONTEXT pCertContext,
    IN DWORD dwFlags,
    OUT PCERT_ENHKEY_USAGE pUsage,
    IN OUT DWORD *pcbUsage
    );

//+-------------------------------------------------------------------------
//  Set the enhanced key usage property for the certificate.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CertSetEnhancedKeyUsage(
    IN PCCERT_CONTEXT pCertContext,
    IN PCERT_ENHKEY_USAGE pUsage
    );

//+-------------------------------------------------------------------------
//  Add the usage identifier to the certificate's enhanced key usage property.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CertAddEnhancedKeyUsageIdentifier(
    IN PCCERT_CONTEXT pCertContext,
    IN LPCSTR pszUsageIdentifier
    );


//+-------------------------------------------------------------------------
//  Remove the usage identifier from the certificate's enhanced key usage
//  property.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CertRemoveEnhancedKeyUsageIdentifier(
    IN PCCERT_CONTEXT pCertContext,
    IN LPCSTR pszUsageIdentifier
    );


//+=========================================================================
//  Cryptographic Message helper functions for verifying and signing a
//  CTL.
//==========================================================================

//+-------------------------------------------------------------------------
//  Get and verify the signer of a cryptographic message.
//
//  To verify a CTL, the hCryptMsg is obtained from the CTL_CONTEXT's
//  hCryptMsg field.
//
//  If CMSG_TRUSTED_SIGNER_FLAG is set, then, treat the Signer stores as being
//  trusted and only search them to find the certificate corresponding to the
//  signer's issuer and serial number.  Otherwise, the SignerStores are
//  optionally provided to supplement the message's store of certificates.
//  If a signer certificate is found, its public key is used to verify
//  the message signature. The CMSG_SIGNER_ONLY_FLAG can be set to
//  return the signer without doing the signature verify.
//
//  If CMSG_USE_SIGNER_INDEX_FLAG is set, then, only get the signer specified
//  by *pdwSignerIndex. Otherwise, iterate through all the signers
//  until a signer verifies or no more signers.
//
//  For a verified signature, *ppSigner is updated with certificate context
//  of the signer and *pdwSignerIndex is updated with the index of the signer.
//  ppSigner and/or pdwSignerIndex can be NULL, indicating the caller isn't
//  interested in getting the CertContext and/or index of the signer.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CryptMsgGetAndVerifySigner(
    IN HCRYPTMSG hCryptMsg,
    IN DWORD cSignerStore,
    IN OPTIONAL HCERTSTORE *rghSignerStore,
    IN DWORD dwFlags,
    OUT OPTIONAL PCCERT_CONTEXT *ppSigner,
    IN OUT OPTIONAL DWORD *pdwSignerIndex
    );

#define CMSG_TRUSTED_SIGNER_FLAG            0x1
#define CMSG_SIGNER_ONLY_FLAG               0x2
#define CMSG_USE_SIGNER_INDEX_FLAG          0x4

//+-------------------------------------------------------------------------
//  Sign an encoded CTL.
//
//  The pbCtlContent can be obtained via a CTL_CONTEXT's pbCtlContent
//  field or via a CryptEncodeObject(PKCS_CTL).
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CryptMsgSignCTL(
    IN DWORD dwMsgEncodingType,
    IN BYTE *pbCtlContent,
    IN DWORD cbCtlContent,
    IN PCMSG_SIGNED_ENCODE_INFO pSignInfo,
    IN DWORD dwFlags,
    OUT BYTE *pbEncoded,
    IN OUT DWORD *pcbEncoded
    );

//+-------------------------------------------------------------------------
//  Encode the CTL and create a signed message containing the encoded CTL.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CryptMsgEncodeAndSignCTL(
    IN DWORD dwMsgEncodingType,
    IN PCTL_INFO pCtlInfo,
    IN PCMSG_SIGNED_ENCODE_INFO pSignInfo,
    IN DWORD dwFlags,
    OUT BYTE *pbEncoded,
    IN OUT DWORD *pcbEncoded
    );


//+=========================================================================
//  Certificate Verify CTL Usage Data Structures and APIs
//==========================================================================

typedef struct _CTL_VERIFY_USAGE_PARA {
    DWORD                   cbSize;
    CRYPT_DATA_BLOB         ListIdentifier;     // OPTIONAL
    DWORD                   cCtlStore;
    HCERTSTORE              *rghCtlStore;       // OPTIONAL
    DWORD                   cSignerStore;
    HCERTSTORE              *rghSignerStore;    // OPTIONAL
} CTL_VERIFY_USAGE_PARA, *PCTL_VERIFY_USAGE_PARA;

typedef struct _CTL_VERIFY_USAGE_STATUS {
    DWORD                   cbSize;
    DWORD                   dwError;
    DWORD                   dwFlags;
    PCCTL_CONTEXT           *ppCtl;             // IN OUT OPTIONAL
    DWORD                   dwCtlEntryIndex;
    PCCERT_CONTEXT          *ppSigner;          // IN OUT OPTIONAL
    DWORD                   dwSignerIndex;
} CTL_VERIFY_USAGE_STATUS, *PCTL_VERIFY_USAGE_STATUS;

#define CERT_VERIFY_INHIBIT_CTL_UPDATE_FLAG     0x1
#define CERT_VERIFY_TRUSTED_SIGNERS_FLAG        0x2
#define CERT_VERIFY_NO_TIME_CHECK_FLAG          0x4
#define CERT_VERIFY_ALLOW_MORE_USAGE_FLAG       0x8

#define CERT_VERIFY_UPDATED_CTL_FLAG            0x1

//+-------------------------------------------------------------------------
//  Verify that a subject is trusted for the specified usage by finding a
//  signed and time valid CTL with the usage identifiers and containing the
//  the subject. A subject can be identified by either its certificate context
//  or any identifier such as its SHA1 hash.
//
//  See CertFindSubjectInCTL for definition of dwSubjectType and pvSubject
//  parameters.
//
//  Via pVerifyUsagePara, the caller can specify the stores to be searched
//  to find the CTL. The caller can also specify the stores containing
//  acceptable CTL signers. By setting the ListIdentifier, the caller
//  can also restrict to a particular signer CTL list.
//
//  Via pVerifyUsageStatus, the CTL containing the subject, the subject's
//  index into the CTL's array of entries, and the signer of the CTL
//  are returned. If the caller is not interested, ppCtl and ppSigner can be set
//  to NULL. Returned contexts must be freed via the store's free context APIs.
//
//  If the CERT_VERIFY_INHIBIT_CTL_UPDATE_FLAG isn't set, then, a time
//  invalid CTL in one of the CtlStores may be replaced. When replaced, the
//  CERT_VERIFY_UPDATED_CTL_FLAG is set in pVerifyUsageStatus->dwFlags.
//
//  If the CERT_VERIFY_TRUSTED_SIGNERS_FLAG is set, then, only the
//  SignerStores specified in pVerifyUsageStatus are searched to find
//  the signer. Otherwise, the SignerStores provide additional sources
//  to find the signer's certificate.
//
//  If CERT_VERIFY_NO_TIME_CHECK_FLAG is set, then, the CTLs aren't checked
//  for time validity.
//
//  If CERT_VERIFY_ALLOW_MORE_USAGE_FLAG is set, then, the CTL may contain
//  additional usage identifiers than specified by pSubjectUsage. Otherwise,
//  the found CTL will contain the same usage identifers and no more.
//
//  CertVerifyCTLUsage will be implemented as a dispatcher to OID installable
//  functions. First, it will try to find an OID function matching the first
//  usage object identifier in the pUsage sequence. Next, it will dispatch
//  to the default CertDllVerifyCTLUsage functions.
//
//  If the subject is trusted for the specified usage, then, TRUE is
//  returned. Otherwise, FALSE is returned with dwError set to one of the
//  following:
//      CRYPT_E_NO_VERIFY_USAGE_DLL
//      CRYPT_E_NO_VERIFY_USAGE_CHECK
//      CRYPT_E_VERIFY_USAGE_OFFLINE
//      CRYPT_E_NOT_IN_CTL
//      CRYPT_E_NO_TRUSTED_SIGNER
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CertVerifyCTLUsage(
    IN DWORD dwEncodingType,
    IN DWORD dwSubjectType,
    IN void *pvSubject,
    IN PCTL_USAGE pSubjectUsage,
    IN DWORD dwFlags,
    IN OPTIONAL PCTL_VERIFY_USAGE_PARA pVerifyUsagePara,
    IN OUT PCTL_VERIFY_USAGE_STATUS pVerifyUsageStatus
    );


//+=========================================================================
//  Certificate Revocation Data Structures and APIs
//==========================================================================

//+-------------------------------------------------------------------------
//  The following data structure may be passed to CertVerifyRevocation to
//  assist in finding the issuer of the context to be verified.
//
//  When pIssuerCert is specified, pIssuerCert is the issuer of
//  rgpvContext[cContext - 1].
//
//  When cCertStore and rgCertStore are specified, these stores may contain
//  an issuer certificate.
//--------------------------------------------------------------------------
typedef struct _CERT_REVOCATION_PARA {
    DWORD                   cbSize;
    PCCERT_CONTEXT          pIssuerCert;
    DWORD                   cCertStore;
    HCERTSTORE              *rgCertStore;
} CERT_REVOCATION_PARA, *PCERT_REVOCATION_PARA;


//+-------------------------------------------------------------------------
//  The following data structure is returned by CertVerifyRevocation to
//  specify the status of the revoked or unchecked context. Review the
//  following CertVerifyRevocation comments for details.
//
//  Upon input to CertVerifyRevocation, cbSize must be set to a size
//  >= sizeof(CERT_REVOCATION_STATUS). Otherwise, CertVerifyRevocation
//  returns FALSE and sets LastError to E_INVALIDARG.
//
//  Upon input to the installed or registered CRYPT_OID_VERIFY_REVOCATION_FUNC
//  functions, the dwIndex, dwError and dwReason have been zero'ed.
//--------------------------------------------------------------------------
typedef struct _CERT_REVOCATION_STATUS {
    DWORD                   cbSize;
    DWORD                   dwIndex;
    DWORD                   dwError;
    DWORD                   dwReason;
} CERT_REVOCATION_STATUS, *PCERT_REVOCATION_STATUS;


//+-------------------------------------------------------------------------
//  Verifies the array of contexts for revocation. The dwRevType parameter
//  indicates the type of the context data structure passed in rgpvContext.
//  Currently only the revocation of certificates is defined.
//
//  If the CERT_VERIFY_REV_CHAIN_FLAG flag is set, then, CertVerifyRevocation
//  is verifying a chain of certs where, rgpvContext[i + 1] is the issuer
//  of rgpvContext[i]. Otherwise, CertVerifyRevocation makes no assumptions
//  about the order of the contexts.
//
//  To assist in finding the issuer, the pRevPara may optionally be set. See
//  the CERT_REVOCATION_PARA data structure for details.
//
//  The contexts must contain enough information to allow the
//  installable or registered revocation DLLs to find the revocation server. For
//  certificates, this information would normally be conveyed in an
//  extension such as the IETF's AuthorityInfoAccess extension.
//
//  CertVerifyRevocation returns TRUE if all of the contexts were successfully
//  checked and none were revoked. Otherwise, returns FALSE and updates the
//  returned pRevStatus data structure as follows:
//    dwIndex
//      Index of the first context that was revoked or unable to
//      be checked for revocation
//    dwError
//      Error status. LastError is also set to this error status.
//      dwError can be set to one of the following error codes defined
//      in winerror.h:
//        ERROR_SUCCESS - good context
//        CRYPT_E_REVOKED - context was revoked. dwReason contains the
//           reason for revocation
//        CRYPT_E_REVOCATION_OFFLINE - unable to connect to the
//           revocation server
//        CRYPT_E_NOT_IN_REVOCATION_DATABASE - the context to be checked
//           was not found in the revocation server's database.
//        CRYPT_E_NO_REVOCATION_CHECK - the called revocation function
//           wasn't able to do a revocation check on the context
//        CRYPT_E_NO_REVOCATION_DLL - no installed or registered Dll was
//           found to verify revocation
//    dwReason
//      The dwReason is currently only set for CRYPT_E_REVOKED and contains
//      the reason why the context was revoked. May be one of the following
//      CRL reasons defined by the CRL Reason Code extension ("2.5.29.21")
//          CRL_REASON_UNSPECIFIED              0
//          CRL_REASON_KEY_COMPROMISE           1
//          CRL_REASON_CA_COMPROMISE            2
//          CRL_REASON_AFFILIATION_CHANGED      3
//          CRL_REASON_SUPERSEDED               4
//          CRL_REASON_CESSATION_OF_OPERATION   5
//          CRL_REASON_CERTIFICATE_HOLD         6
//
//  For each entry in rgpvContext, CertVerifyRevocation iterates
//  through the CRYPT_OID_VERIFY_REVOCATION_FUNC
//  function set's list of installed DEFAULT functions.
//  CryptGetDefaultOIDFunctionAddress is called with pwszDll = NULL. If no
//  installed functions are found capable of doing the revocation verification,
//  CryptVerifyRevocation iterates through CRYPT_OID_VERIFY_REVOCATION_FUNC's
//  list of registered DEFAULT Dlls. CryptGetDefaultOIDDllList is called to
//  get the list. CryptGetDefaultOIDFunctionAddress is called to load the Dll.
//
//  The called functions have the same signature as CertVerifyRevocation. A
//  called function returns TRUE if it was able to successfully check all of
//  the contexts and none were revoked. Otherwise, the called function returns
//  FALSE and updates pRevStatus. dwIndex is set to the index of
//  the first context that was found to be revoked or unable to be checked.
//  dwError and LastError are updated. For CRYPT_E_REVOKED, dwReason
//  is updated. Upon input to the called function, dwIndex, dwError and
//  dwReason have been zero'ed. cbSize has been checked to be >=
//  sizeof(CERT_REVOCATION_STATUS).
//
//  If the called function returns FALSE, and dwError isn't set to
//  CRYPT_E_REVOKED, then, CertVerifyRevocation either continues on to the
//  next DLL in the list for a returned dwIndex of 0 or for a returned
//  dwIndex > 0, restarts the process of finding a verify function by
//  advancing the start of the context array to the returned dwIndex and
//  decrementing the count of remaining contexts.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CertVerifyRevocation(
    IN DWORD dwEncodingType,
    IN DWORD dwRevType,
    IN DWORD cContext,
    IN PVOID rgpvContext[],
    IN DWORD dwFlags,
    IN OPTIONAL PCERT_REVOCATION_PARA pRevPara,
    IN OUT PCERT_REVOCATION_STATUS pRevStatus
    );

//+-------------------------------------------------------------------------
//  Revocation types
//--------------------------------------------------------------------------
#define CERT_CONTEXT_REVOCATION_TYPE        1

//+-------------------------------------------------------------------------
//  When the following flag is set, rgpvContext[] consists of a chain
//  of certificates, where rgpvContext[i + 1] is the issuer of rgpvContext[i].
//--------------------------------------------------------------------------
#define CERT_VERIFY_REV_CHAIN_FLAG          0x1

//+-------------------------------------------------------------------------
//  CERT_CONTEXT_REVOCATION_TYPE
//
//  pvContext points to a const CERT_CONTEXT.
//--------------------------------------------------------------------------

//+=========================================================================
//  Certificate Helper APIs
//==========================================================================


//+-------------------------------------------------------------------------
//  Compare two multiple byte integer blobs to see if they are identical.
//
//  Before doing the comparison, leading zero bytes are removed from a
//  positive number and leading 0xFF bytes are removed from a negative
//  number.
//
//  The multiple byte integers are treated as Little Endian. pbData[0] is the
//  least significant byte and pbData[cbData - 1] is the most significant
//  byte.
//
//  Returns TRUE if the integer blobs are identical after removing leading
//  0 or 0xFF bytes.
//--------------------------------------------------------------------------
BOOL
WINAPI
CertCompareIntegerBlob(
    IN PCRYPT_INTEGER_BLOB pInt1,
    IN PCRYPT_INTEGER_BLOB pInt2
    );

//+-------------------------------------------------------------------------
//  Compare two certificates to see if they are identical.
//
//  Since a certificate is uniquely identified by its Issuer and SerialNumber,
//  these are the only fields needing to be compared.
//
//  Returns TRUE if the certificates are identical.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CertCompareCertificate(
    IN DWORD dwCertEncodingType,
    IN PCERT_INFO pCertId1,
    IN PCERT_INFO pCertId2
    );

//+-------------------------------------------------------------------------
//  Compare two certificate names to see if they are identical.
//
//  Returns TRUE if the names are identical.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CertCompareCertificateName(
    IN DWORD dwCertEncodingType,
    IN PCERT_NAME_BLOB pCertName1,
    IN PCERT_NAME_BLOB pCertName2
    );

//+-------------------------------------------------------------------------
//  Compare the attributes in the certificate name with the specified
//  Relative Distinguished Name's (CERT_RDN) array of attributes.
//  The comparison iterates through the CERT_RDN attributes and looks for an
//  attribute match in any of the certificate name's RDNs.
//  Returns TRUE if all the attributes are found and match.
//
//  The CERT_RDN_ATTR fields can have the following special values:
//    pszObjId == NULL              - ignore the attribute object identifier
//    dwValueType == RDN_ANY_TYPE   - ignore the value type
//
//  Currently only an exact, case sensitive match is supported.
//
//  CERT_UNICODE_IS_RDN_ATTRS_FLAG should be set if the pRDN was initialized
//  with unicode strings as for CryptEncodeObject(X509_UNICODE_NAME).
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CertIsRDNAttrsInCertificateName(
    IN DWORD dwCertEncodingType,
    IN DWORD dwFlags,
    IN PCERT_NAME_BLOB pCertName,
    IN PCERT_RDN pRDN
    );

#define CERT_UNICODE_IS_RDN_ATTRS_FLAG  0x1

//+-------------------------------------------------------------------------
//  Compare two public keys to see if they are identical.
//
//  Returns TRUE if the keys are identical.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CertComparePublicKeyInfo(
    IN DWORD dwCertEncodingType,
    IN PCERT_PUBLIC_KEY_INFO pPublicKey1,
    IN PCERT_PUBLIC_KEY_INFO pPublicKey2
    );

//+-------------------------------------------------------------------------
//  Get the public/private key's bit length.
//
//  Returns 0 if unable to determine the key's length.
//--------------------------------------------------------------------------
WINCRYPT32API
DWORD
WINAPI
CertGetPublicKeyLength(
    IN DWORD dwCertEncodingType,
    IN PCERT_PUBLIC_KEY_INFO pPublicKey
    );

//+-------------------------------------------------------------------------
//  Verify the signature of a subject certificate or a CRL using the
//  public key info
//
//  Returns TRUE for a valid signature.
//
//  hCryptProv specifies the crypto provider to use to verify the signature.
//  It doesn't need to use a private key.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CryptVerifyCertificateSignature(
    IN HCRYPTPROV               hCryptProv,
    IN DWORD                    dwCertEncodingType,
    IN const BYTE *             pbEncoded,
    IN DWORD                    cbEncoded,
    IN PCERT_PUBLIC_KEY_INFO    pPublicKey
    );

//+-------------------------------------------------------------------------
//  Compute the hash of the "to be signed" information in the encoded
//  signed content (CERT_SIGNED_CONTENT_INFO).
//
//  hCryptProv specifies the crypto provider to use to compute the hash.
//  It doesn't need to use a private key.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CryptHashToBeSigned(
    IN HCRYPTPROV hCryptProv,
    IN DWORD dwCertEncodingType,
    IN const BYTE *pbEncoded,
    IN DWORD cbEncoded,
    OUT BYTE *pbComputedHash,
    IN OUT DWORD *pcbComputedHash
    );

//+-------------------------------------------------------------------------
//  Hash the encoded content.
//
//  hCryptProv specifies the crypto provider to use to compute the hash.
//  It doesn't need to use a private key.
//
//  Algid specifies the CAPI hash algorithm to use. If Algid is 0, then, the
//  default hash algorithm (currently SHA1) is used.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CryptHashCertificate(
    IN HCRYPTPROV hCryptProv,
    IN ALG_ID Algid,
    IN DWORD dwFlags,
    IN const BYTE *pbEncoded,
    IN DWORD cbEncoded,
    OUT BYTE *pbComputedHash,
    IN OUT DWORD *pcbComputedHash
    );

//+-------------------------------------------------------------------------
//  Sign the "to be signed" information in the encoded signed content.
//
//  hCryptProv specifies the crypto provider to use to do the signature.
//  It uses the specified private key.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CryptSignCertificate(
    IN HCRYPTPROV hCryptProv,
    IN DWORD dwKeySpec,
    IN DWORD dwCertEncodingType,
    IN const BYTE *pbEncodedToBeSigned,
    IN DWORD cbEncodedToBeSigned,
    IN PCRYPT_ALGORITHM_IDENTIFIER pSignatureAlgorithm,
    IN OPTIONAL const void *pvHashAuxInfo,
    OUT BYTE *pbSignature,
    IN OUT DWORD *pcbSignature
    );

//+-------------------------------------------------------------------------
//  Encode the "to be signed" information. Sign the encoded "to be signed".
//  Encode the "to be signed" and the signature.
//
//  hCryptProv specifies the crypto provider to use to do the signature.
//  It uses the specified private key.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CryptSignAndEncodeCertificate(
    IN HCRYPTPROV hCryptProv,
    IN DWORD dwKeySpec,
    IN DWORD dwCertEncodingType,
    IN LPCSTR lpszStructType,       // "to be signed"
    IN const void *pvStructInfo,
    IN PCRYPT_ALGORITHM_IDENTIFIER pSignatureAlgorithm,
    IN OPTIONAL const void *pvHashAuxInfo,
    OUT PBYTE pbEncoded,
    IN OUT DWORD *pcbEncoded
    );


//+-------------------------------------------------------------------------
//  Verify the time validity of a certificate.
//
//  Returns -1 if before NotBefore, +1 if after NotAfter and otherwise 0 for
//  a valid certificate
//
//  If pTimeToVerify is NULL, uses the current time.
//--------------------------------------------------------------------------
WINCRYPT32API
LONG
WINAPI
CertVerifyTimeValidity(
    IN LPFILETIME pTimeToVerify,
    IN PCERT_INFO pCertInfo
    );


//+-------------------------------------------------------------------------
//  Verify the time validity of a CRL.
//
//  Returns -1 if before ThisUpdate, +1 if after NextUpdate and otherwise 0 for
//  a valid CRL
//
//  If pTimeToVerify is NULL, uses the current time.
//--------------------------------------------------------------------------
WINCRYPT32API
LONG
WINAPI
CertVerifyCRLTimeValidity(
    IN LPFILETIME pTimeToVerify,
    IN PCRL_INFO pCrlInfo
    );

//+-------------------------------------------------------------------------
//  Verify that the subject's time validity nests within the issuer's time
//  validity.
//
//  Returns TRUE if it nests. Otherwise, returns FALSE.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CertVerifyValidityNesting(
    IN PCERT_INFO pSubjectInfo,
    IN PCERT_INFO pIssuerInfo
    );

//+-------------------------------------------------------------------------
//  Verify that the subject certificate isn't on its issuer CRL.
//
//  Returns true if the certificate isn't on the CRL.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CertVerifyCRLRevocation(
    IN DWORD dwCertEncodingType,
    IN PCERT_INFO pCertId,          // Only the Issuer and SerialNumber
                                    // fields are used
    IN DWORD cCrlInfo,
    IN PCRL_INFO rgpCrlInfo[]
    );

//+-------------------------------------------------------------------------
//  Convert the CAPI AlgId to the ASN.1 Object Identifier string
//
//  Returns NULL if there isn't an ObjId corresponding to the AlgId.
//--------------------------------------------------------------------------
WINCRYPT32API
LPCSTR
WINAPI
CertAlgIdToOID(
    IN DWORD dwAlgId
    );

//+-------------------------------------------------------------------------
//  Convert the ASN.1 Object Identifier string to the CAPI AlgId.
//
//  Returns 0 if there isn't an AlgId corresponding to the ObjId.
//--------------------------------------------------------------------------
WINCRYPT32API
DWORD
WINAPI
CertOIDToAlgId(
    IN LPCSTR pszObjId
    );

//+-------------------------------------------------------------------------
//  Find an extension identified by its Object Identifier.
//
//  If found, returns pointer to the extension. Otherwise, returns NULL.
//--------------------------------------------------------------------------
WINCRYPT32API
PCERT_EXTENSION
WINAPI
CertFindExtension(
    IN LPCSTR pszObjId,
    IN DWORD cExtensions,
    IN CERT_EXTENSION rgExtensions[]
    );

//+-------------------------------------------------------------------------
//  Find the first attribute identified by its Object Identifier.
//
//  If found, returns pointer to the attribute. Otherwise, returns NULL.
//--------------------------------------------------------------------------
WINCRYPT32API
PCRYPT_ATTRIBUTE
WINAPI
CertFindAttribute(
    IN LPCSTR pszObjId,
    IN DWORD cAttr,
    IN CRYPT_ATTRIBUTE rgAttr[]
    );

//+-------------------------------------------------------------------------
//  Find the first CERT_RDN attribute identified by its Object Identifier in
//  the name's list of Relative Distinguished Names.
//
//  If found, returns pointer to the attribute. Otherwise, returns NULL.
//--------------------------------------------------------------------------
WINCRYPT32API
PCERT_RDN_ATTR
WINAPI
CertFindRDNAttr(
    IN LPCSTR pszObjId,
    IN PCERT_NAME_INFO pName
    );

//+-------------------------------------------------------------------------
//  Get the intended key usage bytes from the certificate.
//
//  If the certificate doesn't have any intended key usage bytes, returns FALSE
//  and *pbKeyUsage is zeroed. Otherwise, returns TRUE and up through
//  cbKeyUsage bytes are copied into *pbKeyUsage. Any remaining uncopied
//  bytes are zeroed.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CertGetIntendedKeyUsage(
    IN DWORD dwCertEncodingType,
    IN PCERT_INFO pCertInfo,
    OUT BYTE *pbKeyUsage,
    IN DWORD cbKeyUsage
    );


//+-------------------------------------------------------------------------
//  Export the public key info associated with the provider's corresponding
//  private key.
//
//  Calls CryptExportPublicKeyInfo with pszPublicKeyObjId = szOID_RSA_RSA,
//  dwFlags = 0 and pvAuxInfo = NULL.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CryptExportPublicKeyInfo(
    IN HCRYPTPROV hCryptProv,
    IN DWORD dwKeySpec,
    IN DWORD dwCertEncodingType,
    OUT PCERT_PUBLIC_KEY_INFO pInfo,
    IN OUT DWORD *pcbInfo
    );


//+-------------------------------------------------------------------------
//  Export the public key info associated with the provider's corresponding
//  private key.
//
//  Uses the dwCertEncodingType and pszPublicKeyObjId to call the
//  installable CRYPT_OID_EXPORT_PUBLIC_KEY_INFO_FUNC. The called function
//  has the same signature as CryptExportPublicKeyInfoEx.
//
//  If unable to find an installable OID function for the pszPublicKeyObjId,
//  attempts to export as a RSA Public Key (szOID_RSA_RSA).
//
//  The dwFlags and pvAuxInfo aren't used for szOID_RSA_RSA.
//--------------------------------------------------------------------------
#define CRYPT_OID_EXPORT_PUBLIC_KEY_INFO_FUNC   "CryptDllExportPublicKeyInfoEx"

WINCRYPT32API
BOOL
WINAPI
CryptExportPublicKeyInfoEx(
    IN HCRYPTPROV hCryptProv,
    IN DWORD dwKeySpec,
    IN DWORD dwCertEncodingType,
    IN LPSTR pszPublicKeyObjId,
    IN DWORD dwFlags,
    IN OPTIONAL void *pvAuxInfo,
    OUT PCERT_PUBLIC_KEY_INFO pInfo,
    IN OUT DWORD *pcbInfo
    );


//+-------------------------------------------------------------------------
//  Convert and import the public key info into the provider and return a
//  handle to the public key.
//
//  Calls CryptImportPublicKeyInfoEx with aiKeyAlg = 0, dwFlags = 0 and
//  pvAuxInfo = NULL.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CryptImportPublicKeyInfo(
    IN HCRYPTPROV hCryptProv,
    IN DWORD dwCertEncodingType,
    IN PCERT_PUBLIC_KEY_INFO pInfo,
    OUT HCRYPTKEY *phKey
    );

//+-------------------------------------------------------------------------
//  Convert and import the public key info into the provider and return a
//  handle to the public key.
//
//  Uses the dwCertEncodingType and pInfo->Algorithm.pszObjId to call the
//  installable CRYPT_OID_IMPORT_PUBLIC_KEY_INFO_FUNC. The called function
//  has the same signature as CryptImportPublicKeyInfoEx.
//
//  If unable to find an installable OID function for the pszObjId,
//  attempts to import as a RSA Public Key (szOID_RSA_RSA).
//
//  For szOID_RSA_RSA: aiKeyAlg may be set to CALG_RSA_SIGN or CALG_RSA_KEYX.
//  Defaults to CALG_RSA_KEYX. The dwFlags and pvAuxInfo aren't used.
//--------------------------------------------------------------------------
#define CRYPT_OID_IMPORT_PUBLIC_KEY_INFO_FUNC   "CryptDllImportPublicKeyInfoEx"

WINCRYPT32API
BOOL
WINAPI
CryptImportPublicKeyInfoEx(
    IN HCRYPTPROV hCryptProv,
    IN DWORD dwCertEncodingType,
    IN PCERT_PUBLIC_KEY_INFO pInfo,
    IN ALG_ID aiKeyAlg,
    IN DWORD dwFlags,
    IN OPTIONAL void *pvAuxInfo,
    OUT HCRYPTKEY *phKey
    );

//+-------------------------------------------------------------------------
//  Compute the hash of the encoded public key info.
//
//  The public key info is encoded and then hashed.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CryptHashPublicKeyInfo(
    IN HCRYPTPROV hCryptProv,
    IN ALG_ID Algid,
    IN DWORD dwFlags,
    IN DWORD dwCertEncodingType,
    IN PCERT_PUBLIC_KEY_INFO pInfo,
    OUT BYTE *pbComputedHash,
    IN OUT DWORD *pcbComputedHash
    );

//+-------------------------------------------------------------------------
//  Convert a Name Value to a null terminated char string
//
//  Returns the number of characters converted including the terminating null
//  character. If psz is NULL or csz is 0, returns the required size of the
//  destination string (including the terminating null char).
//
//  If psz != NULL && csz != 0, returned psz is always NULL terminated.
//
//  Note: csz includes the NULL char.
//--------------------------------------------------------------------------
WINCRYPT32API
DWORD
WINAPI
CertRDNValueToStrA(
    IN DWORD dwValueType,
    IN PCERT_RDN_VALUE_BLOB pValue,
    OUT OPTIONAL LPSTR psz,
    IN DWORD csz
    );
//+-------------------------------------------------------------------------
//  Convert a Name Value to a null terminated char string
//
//  Returns the number of characters converted including the terminating null
//  character. If psz is NULL or csz is 0, returns the required size of the
//  destination string (including the terminating null char).
//
//  If psz != NULL && csz != 0, returned psz is always NULL terminated.
//
//  Note: csz includes the NULL char.
//--------------------------------------------------------------------------
WINCRYPT32API
DWORD
WINAPI
CertRDNValueToStrW(
    IN DWORD dwValueType,
    IN PCERT_RDN_VALUE_BLOB pValue,
    OUT OPTIONAL LPWSTR psz,
    IN DWORD csz
    );
#ifdef UNICODE
#define CertRDNValueToStr  CertRDNValueToStrW
#else
#define CertRDNValueToStr  CertRDNValueToStrA
#endif // !UNICODE

//+-------------------------------------------------------------------------
//  Convert the certificate name blob to a null terminated char string.
//
//  Follows the string representation of distinguished names specified in
//  RFC 1779. (Note, added double quoting "" for embedded quotes, quote
//  empty strings and don't quote strings containing consecutive spaces).
//  RDN values of type CERT_RDN_ENCODED_BLOB or CERT_RDN_OCTET_STRING are
//  formatted in hexadecimal (e.g. #0A56CF).
//
//  The name string is formatted according to the dwStrType:
//    CERT_SIMPLE_NAME_STR
//      The object identifiers are discarded. CERT_RDN entries are separated
//      by ", ". Multiple attributes per CERT_RDN are separated by " + ".
//      For example:
//          Microsoft, Joe Cool + Programmer
//    CERT_OID_NAME_STR
//      The object identifiers are included with a "=" separator from their
//      attribute value. CERT_RDN entries are separated by ", ".
//      Multiple attributes per CERT_RDN are separated by " + ". For example:
//          2.5.4.11=Microsoft, 2.5.4.3=Joe Cool + 2.5.4.12=Programmer
//    CERT_X500_NAME_STR
//      The object identifiers are converted to their X500 key name. Otherwise,
//      same as CERT_OID_NAME_STR. If the object identifier doesn't have
//      a corresponding X500 key name, then, the object identifier is used with
//      a "OID." prefix. For example:
//          OU=Microsoft, CN=Joe Cool + T=Programmer, OID.1.2.3.4.5.6=Unknown
//
//  We quote the RDN value if it contains leading or trailing whitespace
//  or one of the following characters: ",", "+", "=", """, "\n",  "<", ">",
//  "#" or ";". The quoting character is ". If the the RDN Value contains
//  a " it is double quoted (""). For example:
//      OU="  Microsoft", CN="Joe ""Cool""" + T="Programmer, Manager"
//
//  CERT_NAME_STR_SEMICOLON_FLAG can be or'ed into dwStrType to replace
//  the ", " separator with a "; " separator.
//
//  CERT_NAME_STR_CRLF_FLAG can be or'ed into dwStrType to replace
//  the ", " separator with a "\r\n" separator.
//
//  CERT_NAME_STR_NO_PLUS_FLAG can be or'ed into dwStrType to replace the
//  " + " separator with a single space, " ".
//
//  CERT_NAME_STR_NO_QUOTING_FLAG can be or'ed into dwStrType to inhibit
//  the above quoting.
//
//  Returns the number of characters converted including the terminating null
//  character. If psz is NULL or csz is 0, returns the required size of the
//  destination string (including the terminating null char).
//
//  If psz != NULL && csz != 0, returned psz is always NULL terminated.
//
//  Note: csz includes the NULL char.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//--------------------------------------------------------------------------
WINCRYPT32API
DWORD
WINAPI
CertNameToStrA(
    IN DWORD dwCertEncodingType,
    IN PCERT_NAME_BLOB pName,
    IN DWORD dwStrType,
    OUT OPTIONAL LPSTR psz,
    IN DWORD csz
    );
//+-------------------------------------------------------------------------
//--------------------------------------------------------------------------
WINCRYPT32API
DWORD
WINAPI
CertNameToStrW(
    IN DWORD dwCertEncodingType,
    IN PCERT_NAME_BLOB pName,
    IN DWORD dwStrType,
    OUT OPTIONAL LPWSTR psz,
    IN DWORD csz
    );
#ifdef UNICODE
#define CertNameToStr  CertNameToStrW
#else
#define CertNameToStr  CertNameToStrA
#endif // !UNICODE

//+-------------------------------------------------------------------------
//  Certificate name string types
//--------------------------------------------------------------------------
#define CERT_SIMPLE_NAME_STR        1
#define CERT_OID_NAME_STR           2
#define CERT_X500_NAME_STR          3

//+-------------------------------------------------------------------------
//  Certificate name string type flags OR'ed with the above types
//--------------------------------------------------------------------------
#define CERT_NAME_STR_SEMICOLON_FLAG    0x40000000
#define CERT_NAME_STR_NO_PLUS_FLAG      0x20000000
#define CERT_NAME_STR_NO_QUOTING_FLAG   0x10000000
#define CERT_NAME_STR_CRLF_FLAG         0x08000000
#define CERT_NAME_STR_COMMA_FLAG        0x04000000


//+-------------------------------------------------------------------------
//  Convert the null terminated X500 string to an encoded certificate name.
//
//  The input string is expected to be formatted the same as the output
//  from the above CertNameToStr API.
//
//  The CERT_SIMPLE_NAME_STR type isn't supported. Otherwise, when dwStrType
//  is set to 0, CERT_OID_NAME_STR or CERT_X500_NAME_STR, allow either a
//  case insensitive X500 key (CN=), case insensitive "OID." prefixed
//  object identifier (OID.1.2.3.4.5.6=) or an object identifier (1.2.3.4=).
//
//  If no flags are OR'ed into dwStrType, then, allow "," or ";" as RDN
//  separators and "+" as the multiple RDN value separator. Quoting is
//  supported. A quote may be included in a quoted value by double quoting,
//  for example (CN="Joe ""Cool"""). A value starting with a "#" is treated
//  as ascii hex and converted to a CERT_RDN_OCTET_STRING. Embedded whitespace
//  is skipped (1.2.3 = # AB CD 01  is the same as 1.2.3=#ABCD01).
//
//  Whitespace surrounding the keys, object identifers and values is removed.
//
//  CERT_NAME_STR_COMMA_FLAG can be or'ed into dwStrType to only allow the
//  "," as the RDN separator.
//
//  CERT_NAME_STR_SEMICOLON_FLAG can be or'ed into dwStrType to only allow the
//  ";" as the RDN separator.
//
//  CERT_NAME_STR_CRLF_FLAG can be or'ed into dwStrType to only allow
//  "\r" or "\n" as the RDN separator.
//
//  CERT_NAME_STR_NO_PLUS_FLAG can be or'ed into dwStrType to ignore "+"
//  as a separator and not allow multiple values per RDN.
//
//  CERT_NAME_STR_NO_QUOTING_FLAG can be or'ed into dwStrType to inhibit
//  quoting.
//
//  Support the following X500 Keys:
//
//  Key         Object Identifier               RDN Value Type(s)
//  ---         -----------------               -----------------
//  CN          szOID_COMMON_NAME               Printable, T61
//  L           szOID_LOCALITY_NAME             Printable, T61
//  O           szOID_ORGANIZATION_NAME         Printable, T61
//  OU          szOID_ORGANIZATIONAL_UNIT_NAME  Printable, T61
//  Email       szOID_RSA_emailAddr             Only IA5
//  C           szOID_COUNTRY_NAME              Only Printable
//  S           szOID_STATE_OR_PROVINCE_NAME    Printable, T61
//  ST          szOID_STATE_OR_PROVINCE_NAME    Printable, T61
//  STREET      szOID_STREET_ADDRESS            Printable, T61
//  T           szOID_TITLE                     Printable, T61
//  Title       szOID_TITLE                     Printable, T61
//  G           szOID_GIVEN_NAME                Printable, T61
//  GivenName   szOID_GIVEN_NAME                Printable, T61
//  I           szOID_INITIALS                  Printable, T61
//  Initials    szOID_INITIALS                  Printable, T61
//  SN          szOID_SUR_NAME                  Printable, T61
//  DC          szOID_DOMAIN_COMPONENT          Only IA5
//
//  The T61 types are UTF-8 encoded.
//
//  Returns TRUE if successfully parsed the input string and encoded
//  the name.
//
//  If the input string is detected to be invalid, *ppszError is updated
//  to point to the beginning of the invalid character sequence. Otherwise,
//  *ppszError is set to NULL. *ppszError is updated with a non-NULL pointer
//  for the following errors:
//      CRYPT_E_INVALID_X500_STRING
//      CRYPT_E_INVALID_NUMERIC_STRING
//      CRYPT_E_INVALID_PRINTABLE_STRING
//      CRYPT_E_INVALID_IA5_STRING
//
//  ppszError can be set to NULL if not interested in getting a pointer
//  to the invalid character sequence.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CertStrToNameA(
    IN DWORD dwCertEncodingType,
    IN LPCSTR pszX500,
    IN DWORD dwStrType,
    IN OPTIONAL void *pvReserved,
    OUT BYTE *pbEncoded,
    IN OUT DWORD *pcbEncoded,
    OUT OPTIONAL LPCSTR *ppszError
    );
//+-------------------------------------------------------------------------
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CertStrToNameW(
    IN DWORD dwCertEncodingType,
    IN LPCWSTR pszX500,
    IN DWORD dwStrType,
    IN OPTIONAL void *pvReserved,
    OUT BYTE *pbEncoded,
    IN OUT DWORD *pcbEncoded,
    OUT OPTIONAL LPCWSTR *ppszError
    );
#ifdef UNICODE
#define CertStrToName  CertStrToNameW
#else
#define CertStrToName  CertStrToNameA
#endif // !UNICODE


//+=========================================================================
//  Simplified Cryptographic Message Data Structures and APIs
//==========================================================================


//+-------------------------------------------------------------------------
//              Conventions for the *pb and *pcb output parameters:
//
//              Upon entry to the function:
//                  if pcb is OPTIONAL && pcb == NULL, then,
//                      No output is returned
//                  else if pb == NULL && pcb != NULL, then,
//                      Length only determination. No length error is
//                      returned.
//                  otherwise where (pb != NULL && pcb != NULL && *pcb != 0)
//                      Output is returned. If *pcb isn't big enough a
//                      length error is returned. In all cases *pcb is updated
//                      with the actual length needed/returned.
//--------------------------------------------------------------------------


//+-------------------------------------------------------------------------
//  Type definitions of the parameters used for doing the cryptographic
//  operations.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  Callback to get and verify the signer's certificate.
//
//  Passed the CertId of the signer (its Issuer and SerialNumber) and a
//  handle to its cryptographic signed message's cert store.
//
//  For CRYPT_E_NO_SIGNER, called with pSignerId == NULL.
//
//  For a valid signer certificate, returns a pointer to a read only
//  CERT_CONTEXT. The returned CERT_CONTEXT is either obtained from a
//  cert store or was created via CertCreateCertificateContext. For either case,
//  its freed via CertFreeCertificateContext.
//
//  If a valid certificate isn't found, this callback returns NULL with
//  LastError set via SetLastError().
//
//  The NULL implementation tries to get the Signer certificate from the
//  message cert store. It doesn't verify the certificate.
//--------------------------------------------------------------------------
typedef PCCERT_CONTEXT (WINAPI *PFN_CRYPT_GET_SIGNER_CERTIFICATE)(
            IN void *pvGetArg,
            IN DWORD dwCertEncodingType,
            IN PCERT_INFO pSignerId,    // Only the Issuer and SerialNumber
                                        // fields have been updated
            IN HCERTSTORE hMsgCertStore
            );

//+-------------------------------------------------------------------------
//  The CRYPT_SIGN_MESSAGE_PARA are used for signing messages using the
//  specified signing certificate contexts. (Note, allows multiple signers.)
//
//  Either the CERT_KEY_PROV_HANDLE_PROP_ID or CERT_KEY_PROV_INFO_PROP_ID must
//  be set for each rgpSigningCert[]. Either one specifies the private
//  signature key to use.
//
//  If any certificates and/or CRLs are to be included in the signed message,
//  then, the MsgCert and MsgCrl parameters need to be updated. If the
//  rgpSigningCerts are to be included, then, they must also be in the
//  rgpMsgCert array.
//
//  cbSize must be set to the sizeof(CRYPT_SIGN_MESSAGE_PARA) or else
//  LastError will be updated with E_INVALIDARG.
//
//  pvHashAuxInfo currently isn't used and must be set to NULL.
//
//  dwFlags normally is set to 0. However, if the encoded output
//  is to be a CMSG_SIGNED inner content of an outer cryptographic message,
//  such as a CMSG_ENVELOPED, then, the CRYPT_MESSAGE_BARE_CONTENT_OUT_FLAG
//  should be set. If not set, then it would be encoded as an inner content
//  type of CMSG_DATA.
//
//  dwInnerContentType is normally set to 0. It needs to be set if the
//  ToBeSigned input is the encoded output of another cryptographic
//  message, such as, an CMSG_ENVELOPED. When set, it's one of the cryptographic
//  message types, for example, CMSG_ENVELOPED.
//
//  If the inner content of a nested cryptographic message is data (CMSG_DATA
//  the default), then, neither dwFlags or dwInnerContentType need to be set.
//--------------------------------------------------------------------------
typedef struct _CRYPT_SIGN_MESSAGE_PARA {
    DWORD                       cbSize;
    DWORD                       dwMsgEncodingType;
    PCCERT_CONTEXT              pSigningCert;
    CRYPT_ALGORITHM_IDENTIFIER  HashAlgorithm;
    void                        *pvHashAuxInfo;
    DWORD                       cMsgCert;
    PCCERT_CONTEXT              *rgpMsgCert;
    DWORD                       cMsgCrl;
    PCCRL_CONTEXT               *rgpMsgCrl;
    DWORD                       cAuthAttr;
    PCRYPT_ATTRIBUTE            rgAuthAttr;
    DWORD                       cUnauthAttr;
    PCRYPT_ATTRIBUTE            rgUnauthAttr;
    DWORD                       dwFlags;
    DWORD                       dwInnerContentType;
} CRYPT_SIGN_MESSAGE_PARA, *PCRYPT_SIGN_MESSAGE_PARA;

#define CRYPT_MESSAGE_BARE_CONTENT_OUT_FLAG     0x1

//+-------------------------------------------------------------------------
//  The CRYPT_VERIFY_MESSAGE_PARA are used to verify signed messages.
//
//  hCryptProv is used to do hashing and signature verification.
//
//  The dwCertEncodingType specifies the encoding type of the certificates
//  and/or CRLs in the message.
//
//  pfnGetSignerCertificate is called to get and verify the message signer's
//  certificate.
//
//  cbSize must be set to the sizeof(CRYPT_VERIFY_MESSAGE_PARA) or else
//  LastError will be updated with E_INVALIDARG.
//--------------------------------------------------------------------------
typedef struct _CRYPT_VERIFY_MESSAGE_PARA {
    DWORD                               cbSize;
    DWORD                               dwMsgAndCertEncodingType;
    HCRYPTPROV                          hCryptProv;
    PFN_CRYPT_GET_SIGNER_CERTIFICATE    pfnGetSignerCertificate;
    void                                *pvGetArg;
} CRYPT_VERIFY_MESSAGE_PARA, *PCRYPT_VERIFY_MESSAGE_PARA;

//+-------------------------------------------------------------------------
//  The CRYPT_ENCRYPT_MESSAGE_PARA are used for encrypting messages.
//
//  hCryptProv is used to do content encryption, recipient key
//  encryption, and recipient key export. Its private key
//  isn't used.
//
//  pvEncryptionAuxInfo currently isn't used and must be set to NULL.
//
//  cbSize must be set to the sizeof(CRYPT_ENCRYPT_MESSAGE_PARA) or else
//  LastError will be updated with E_INVALIDARG.
//
//  dwFlags normally is set to 0. However, if the encoded output
//  is to be a CMSG_ENVELOPED inner content of an outer cryptographic message,
//  such as a CMSG_SIGNED, then, the CRYPT_MESSAGE_BARE_CONTENT_OUT_FLAG
//  should be set. If not set, then it would be encoded as an inner content
//  type of CMSG_DATA.
//
//  dwInnerContentType is normally set to 0. It needs to be set if the
//  ToBeEncrypted input is the encoded output of another cryptographic
//  message, such as, an CMSG_SIGNED. When set, it's one of the cryptographic
//  message types, for example, CMSG_SIGNED.
//
//  If the inner content of a nested cryptographic message is data (CMSG_DATA
//  the default), then, neither dwFlags or dwInnerContentType need to be set.
//--------------------------------------------------------------------------
typedef struct _CRYPT_ENCRYPT_MESSAGE_PARA {
    DWORD                       cbSize;
    DWORD                       dwMsgEncodingType;
    HCRYPTPROV                  hCryptProv;
    CRYPT_ALGORITHM_IDENTIFIER  ContentEncryptionAlgorithm;
    void                        *pvEncryptionAuxInfo;
    DWORD                       dwFlags;
    DWORD                       dwInnerContentType;
} CRYPT_ENCRYPT_MESSAGE_PARA, *PCRYPT_ENCRYPT_MESSAGE_PARA;

//+-------------------------------------------------------------------------
//  The CRYPT_DECRYPT_MESSAGE_PARA are used for decrypting messages.
//
//  The CertContext to use for decrypting a message is obtained from one
//  of the specified cert stores. An encrypted message can have one or
//  more recipients. The recipients are identified by their CertId (Issuer
//  and SerialNumber). The cert stores are searched to find the CertContext
//  corresponding to the CertId.
//
//  Only CertContexts in the store with either
//  the CERT_KEY_PROV_HANDLE_PROP_ID or CERT_KEY_PROV_INFO_PROP_ID set
//  can be used. Either property specifies the private exchange key to use.
//
//  cbSize must be set to the sizeof(CRYPT_DECRYPT_MESSAGE_PARA) or else
//  LastError will be updated with E_INVALIDARG.
//--------------------------------------------------------------------------
typedef struct _CRYPT_DECRYPT_MESSAGE_PARA {
    DWORD                   cbSize;
    DWORD                   dwMsgAndCertEncodingType;
    DWORD                   cCertStore;
    HCERTSTORE              *rghCertStore;
} CRYPT_DECRYPT_MESSAGE_PARA, *PCRYPT_DECRYPT_MESSAGE_PARA;

//+-------------------------------------------------------------------------
//  The CRYPT_HASH_MESSAGE_PARA are used for hashing or unhashing
//  messages.
//
//  hCryptProv is used to compute the hash.
//
//  pvHashAuxInfo currently isn't used and must be set to NULL.
//
//  cbSize must be set to the sizeof(CRYPT_HASH_MESSAGE_PARA) or else
//  LastError will be updated with E_INVALIDARG.
//--------------------------------------------------------------------------
typedef struct _CRYPT_HASH_MESSAGE_PARA {
    DWORD                       cbSize;
    DWORD                       dwMsgEncodingType;
    HCRYPTPROV                  hCryptProv;
    CRYPT_ALGORITHM_IDENTIFIER  HashAlgorithm;
    void                        *pvHashAuxInfo;
} CRYPT_HASH_MESSAGE_PARA, *PCRYPT_HASH_MESSAGE_PARA;



//+-------------------------------------------------------------------------
//  The CRYPT_KEY_SIGN_MESSAGE_PARA are used for signing messages until a
//  certificate has been created for the signature key.
//
//  pvHashAuxInfo currently isn't used and must be set to NULL.
//
//  If PubKeyAlgorithm isn't set, defaults to szOID_RSA_RSA.
//
//  cbSize must be set to the sizeof(CRYPT_KEY_SIGN_MESSAGE_PARA) or else
//  LastError will be updated with E_INVALIDARG.
//--------------------------------------------------------------------------
typedef struct _CRYPT_KEY_SIGN_MESSAGE_PARA {
    DWORD                       cbSize;
    DWORD                       dwMsgAndCertEncodingType;
    HCRYPTPROV                  hCryptProv;
    DWORD                       dwKeySpec;
    CRYPT_ALGORITHM_IDENTIFIER  HashAlgorithm;
    void                        *pvHashAuxInfo;
    CRYPT_ALGORITHM_IDENTIFIER  PubKeyAlgorithm;
} CRYPT_KEY_SIGN_MESSAGE_PARA, *PCRYPT_KEY_SIGN_MESSAGE_PARA;

//+-------------------------------------------------------------------------
//  The CRYPT_KEY_VERIFY_MESSAGE_PARA are used to verify signed messages without
//  a certificate for the signer.
//
//  Normally used until a certificate has been created for the key.
//
//  hCryptProv is used to do hashing and signature verification.
//
//  cbSize must be set to the sizeof(CRYPT_KEY_VERIFY_MESSAGE_PARA) or else
//  LastError will be updated with E_INVALIDARG.
//--------------------------------------------------------------------------
typedef struct _CRYPT_KEY_VERIFY_MESSAGE_PARA {
    DWORD                   cbSize;
    DWORD                   dwMsgEncodingType;
    HCRYPTPROV              hCryptProv;
} CRYPT_KEY_VERIFY_MESSAGE_PARA, *PCRYPT_KEY_VERIFY_MESSAGE_PARA;


//+-------------------------------------------------------------------------
//  Sign the message.
//
//  If fDetachedSignature is TRUE, the "to be signed" content isn't included
//  in the encoded signed blob.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CryptSignMessage(
    IN PCRYPT_SIGN_MESSAGE_PARA pSignPara,
    IN BOOL fDetachedSignature,
    IN DWORD cToBeSigned,
    IN const BYTE *rgpbToBeSigned[],
    IN DWORD rgcbToBeSigned[],
    OUT BYTE *pbSignedBlob,
    IN OUT DWORD *pcbSignedBlob
    );

//+-------------------------------------------------------------------------
//  Verify a signed message.
//
//  If pbDecoded == NULL, then, *pcbDecoded is implicitly set to 0 on input.
//  For *pcbDecoded == 0 && ppSignerCert == NULL on input, the signer isn't
//  verified.
//
//  A message might have more than one signer. Set dwSignerIndex to iterate
//  through all the signers. dwSignerIndex == 0 selects the first signer.
//
//  pVerifyPara's pfnGetSignerCertificate is called to get the signer's
//  certificate.
//
//  For a verified signer and message, *ppSignerCert is updated
//  with the CertContext of the signer. It must be freed by calling
//  CertFreeCertificateContext. Otherwise, *ppSignerCert is set to NULL.
//
//  ppSignerCert can be NULL, indicating the caller isn't interested
//  in getting the CertContext of the signer.
//
//  pcbDecoded can be NULL, indicating the caller isn't interested in getting
//  the decoded content. Furthermore, if the message doesn't contain any
//  content or signers, then, pcbDecoded must be set to NULL, to allow the
//  pVerifyPara->pfnGetCertificate to be called. Normally, this would be
//  the case when the signed message contains only certficates and CRLs.
//  If pcbDecoded is NULL and the message doesn't have the indicated signer,
//  pfnGetCertificate is called with pSignerId set to NULL.
//
//  If the message doesn't contain any signers || dwSignerIndex > message's
//  SignerCount, then, an error is returned with LastError set to
//  CRYPT_E_NO_SIGNER. Also, for CRYPT_E_NO_SIGNER, pfnGetSignerCertificate
//  is still called with pSignerId set to NULL.
//
//  Note, an alternative way to get the certificates and CRLs from a
//  signed message is to call CryptGetMessageCertificates.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CryptVerifyMessageSignature(
    IN PCRYPT_VERIFY_MESSAGE_PARA pVerifyPara,
    IN DWORD dwSignerIndex,
    IN const BYTE *pbSignedBlob,
    IN DWORD cbSignedBlob,
    OUT BYTE OPTIONAL *pbDecoded,
    IN OUT OPTIONAL DWORD *pcbDecoded,
    OUT OPTIONAL PCCERT_CONTEXT *ppSignerCert
    );

//+-------------------------------------------------------------------------
//  Returns the count of signers in the signed message. For no signers, returns
//  0. For an error returns -1 with LastError updated accordingly.
//--------------------------------------------------------------------------
WINCRYPT32API
LONG
WINAPI
CryptGetMessageSignerCount(
    IN DWORD dwMsgEncodingType,
    IN const BYTE *pbSignedBlob,
    IN DWORD cbSignedBlob
    );

//+-------------------------------------------------------------------------
//  Returns the cert store containing the message's certs and CRLs.
//  For an error, returns NULL with LastError updated.
//--------------------------------------------------------------------------
WINCRYPT32API
HCERTSTORE
WINAPI
CryptGetMessageCertificates(
    IN DWORD dwMsgAndCertEncodingType,
    IN HCRYPTPROV hCryptProv,           // passed to CertOpenStore
    IN DWORD dwFlags,                   // passed to CertOpenStore
    IN const BYTE *pbSignedBlob,
    IN DWORD cbSignedBlob
    );

//+-------------------------------------------------------------------------
//  Verify a signed message containing detached signature(s).
//  The "to be signed" content is passed in separately. No
//  decoded output. Otherwise, identical to CryptVerifyMessageSignature.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CryptVerifyDetachedMessageSignature(
    IN PCRYPT_VERIFY_MESSAGE_PARA pVerifyPara,
    IN DWORD dwSignerIndex,
    IN const BYTE *pbDetachedSignBlob,
    IN DWORD cbDetachedSignBlob,
    IN DWORD cToBeSigned,
    IN const BYTE *rgpbToBeSigned[],
    IN DWORD rgcbToBeSigned[],
    OUT OPTIONAL PCCERT_CONTEXT *ppSignerCert
    );

//+-------------------------------------------------------------------------
//  Encrypts the message for the recipient(s).
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CryptEncryptMessage(
    IN PCRYPT_ENCRYPT_MESSAGE_PARA pEncryptPara,
    IN DWORD cRecipientCert,
    IN PCCERT_CONTEXT rgpRecipientCert[],
    IN const BYTE *pbToBeEncrypted,
    IN DWORD cbToBeEncrypted,
    OUT BYTE *pbEncryptedBlob,
    IN OUT DWORD *pcbEncryptedBlob
    );

//+-------------------------------------------------------------------------
//  Decrypts the message.
//
//  If pbDecrypted == NULL, then, *pcbDecrypted is implicitly set to 0 on input.
//  For *pcbDecrypted == 0 && ppXchgCert == NULL on input, the message isn't
//  decrypted.
//
//  For a successfully decrypted message, *ppXchgCert is updated
//  with the CertContext used to decrypt. It must be freed by calling
//  CertStoreFreeCert. Otherwise, *ppXchgCert is set to NULL.
//
//  ppXchgCert can be NULL, indicating the caller isn't interested
//  in getting the CertContext used to decrypt.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CryptDecryptMessage(
    IN PCRYPT_DECRYPT_MESSAGE_PARA pDecryptPara,
    IN const BYTE *pbEncryptedBlob,
    IN DWORD cbEncryptedBlob,
    OUT OPTIONAL BYTE *pbDecrypted,
    IN OUT OPTIONAL DWORD *pcbDecrypted,
    OUT OPTIONAL PCCERT_CONTEXT *ppXchgCert
    );

//+-------------------------------------------------------------------------
//  Sign the message and encrypt for the recipient(s). Does a CryptSignMessage
//  followed with a CryptEncryptMessage.
//
//  Note: this isn't the CMSG_SIGNED_AND_ENVELOPED. Its a CMSG_SIGNED
//  inside of an CMSG_ENVELOPED.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CryptSignAndEncryptMessage(
    IN PCRYPT_SIGN_MESSAGE_PARA pSignPara,
    IN PCRYPT_ENCRYPT_MESSAGE_PARA pEncryptPara,
    IN DWORD cRecipientCert,
    IN PCCERT_CONTEXT rgpRecipientCert[],
    IN const BYTE *pbToBeSignedAndEncrypted,
    IN DWORD cbToBeSignedAndEncrypted,
    OUT BYTE *pbSignedAndEncryptedBlob,
    IN OUT DWORD *pcbSignedAndEncryptedBlob
    );

//+-------------------------------------------------------------------------
//  Decrypts the message and verifies the signer. Does a CryptDecryptMessage
//  followed with a CryptVerifyMessageSignature.
//
//  If pbDecrypted == NULL, then, *pcbDecrypted is implicitly set to 0 on input.
//  For *pcbDecrypted == 0 && ppSignerCert == NULL on input, the signer isn't
//  verified.
//
//  A message might have more than one signer. Set dwSignerIndex to iterate
//  through all the signers. dwSignerIndex == 0 selects the first signer.
//
//  The pVerifyPara's VerifySignerPolicy is called to verify the signer's
//  certificate.
//
//  For a successfully decrypted and verified message, *ppXchgCert and
//  *ppSignerCert are updated. They must be freed by calling
//  CertStoreFreeCert. Otherwise, they are set to NULL.
//
//  ppXchgCert and/or ppSignerCert can be NULL, indicating the
//  caller isn't interested in getting the CertContext.
//
//  Note: this isn't the CMSG_SIGNED_AND_ENVELOPED. Its a CMSG_SIGNED
//  inside of an CMSG_ENVELOPED.
//
//  The message always needs to be decrypted to allow access to the
//  signed message. Therefore, if ppXchgCert != NULL, its always updated.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CryptDecryptAndVerifyMessageSignature(
    IN PCRYPT_DECRYPT_MESSAGE_PARA pDecryptPara,
    IN PCRYPT_VERIFY_MESSAGE_PARA pVerifyPara,
    IN DWORD dwSignerIndex,
    IN const BYTE *pbEncryptedBlob,
    IN DWORD cbEncryptedBlob,
    OUT OPTIONAL BYTE *pbDecrypted,
    IN OUT OPTIONAL DWORD *pcbDecrypted,
    OUT OPTIONAL PCCERT_CONTEXT *ppXchgCert,
    OUT OPTIONAL PCCERT_CONTEXT *ppSignerCert
    );

//+-------------------------------------------------------------------------
//  Decodes a cryptographic message which may be one of the following types:
//    CMSG_DATA
//    CMSG_SIGNED
//    CMSG_ENVELOPED
//    CMSG_SIGNED_AND_ENVELOPED
//    CMSG_HASHED
//
//  dwMsgTypeFlags specifies the set of allowable messages. For example, to
//  decode either SIGNED or ENVELOPED messages, set dwMsgTypeFlags to:
//      CMSG_SIGNED_FLAG | CMSG_ENVELOPED_FLAG.
//
//  dwProvInnerContentType is only applicable when processing nested
//  crytographic messages. When processing an outer crytographic message
//  it must be set to 0. When decoding a nested cryptographic message
//  its the dwInnerContentType returned by a previous CryptDecodeMessage
//  of the outer message. The InnerContentType can be any of the CMSG types,
//  for example, CMSG_DATA, CMSG_SIGNED, ...
//
//  The optional *pdwMsgType is updated with the type of message.
//
//  The optional *pdwInnerContentType is updated with the type of the inner
//  message. Unless there is cryptographic message nesting, CMSG_DATA
//  is returned.
//
//  For CMSG_DATA: returns decoded content.
//  For CMSG_SIGNED: same as CryptVerifyMessageSignature.
//  For CMSG_ENVELOPED: same as CryptDecryptMessage.
//  For CMSG_SIGNED_AND_ENVELOPED: same as CryptDecryptMessage plus
//      CryptVerifyMessageSignature.
//  For CMSG_HASHED: verifies the hash and returns decoded content.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CryptDecodeMessage(
    IN DWORD dwMsgTypeFlags,
    IN PCRYPT_DECRYPT_MESSAGE_PARA pDecryptPara,
    IN PCRYPT_VERIFY_MESSAGE_PARA pVerifyPara,
    IN DWORD dwSignerIndex,
    IN const BYTE *pbEncodedBlob,
    IN DWORD cbEncodedBlob,
    IN DWORD dwPrevInnerContentType,
    OUT OPTIONAL DWORD *pdwMsgType,
    OUT OPTIONAL DWORD *pdwInnerContentType,
    OUT OPTIONAL BYTE *pbDecoded,
    IN OUT OPTIONAL DWORD *pcbDecoded,
    OUT OPTIONAL PCCERT_CONTEXT *ppXchgCert,
    OUT OPTIONAL PCCERT_CONTEXT *ppSignerCert
    );

//+-------------------------------------------------------------------------
//  Hash the message.
//
//  If fDetachedHash is TRUE, only the ComputedHash is encoded in the
//  pbHashedBlob. Otherwise, both the ToBeHashed and ComputedHash
//  are encoded.
//
//  pcbHashedBlob or pcbComputedHash can be NULL, indicating the caller
//  isn't interested in getting the output.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CryptHashMessage(
    IN PCRYPT_HASH_MESSAGE_PARA pHashPara,
    IN BOOL fDetachedHash,
    IN DWORD cToBeHashed,
    IN const BYTE *rgpbToBeHashed[],
    IN DWORD rgcbToBeHashed[],
    OUT OPTIONAL BYTE *pbHashedBlob,
    IN OUT OPTIONAL DWORD *pcbHashedBlob,
    OUT OPTIONAL BYTE *pbComputedHash,
    IN OUT OPTIONAL DWORD *pcbComputedHash
    );

//+-------------------------------------------------------------------------
//  Verify a hashed message.
//
//  pcbToBeHashed or pcbComputedHash can be NULL,
//  indicating the caller isn't interested in getting the output.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CryptVerifyMessageHash(
    IN PCRYPT_HASH_MESSAGE_PARA pHashPara,
    IN BYTE *pbHashedBlob,
    IN DWORD cbHashedBlob,
    OUT OPTIONAL BYTE *pbToBeHashed,
    IN OUT OPTIONAL DWORD *pcbToBeHashed,
    OUT OPTIONAL BYTE *pbComputedHash,
    IN OUT OPTIONAL DWORD *pcbComputedHash
    );

//+-------------------------------------------------------------------------
//  Verify a hashed message containing a detached hash.
//  The "to be hashed" content is passed in separately. No
//  decoded output. Otherwise, identical to CryptVerifyMessageHash.
//
//  pcbComputedHash can be NULL, indicating the caller isn't interested
//  in getting the output.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CryptVerifyDetachedMessageHash(
    IN PCRYPT_HASH_MESSAGE_PARA pHashPara,
    IN BYTE *pbDetachedHashBlob,
    IN DWORD cbDetachedHashBlob,
    IN DWORD cToBeHashed,
    IN const BYTE *rgpbToBeHashed[],
    IN DWORD rgcbToBeHashed[],
    OUT OPTIONAL BYTE *pbComputedHash,
    IN OUT OPTIONAL DWORD *pcbComputedHash
    );

//+-------------------------------------------------------------------------
//  Sign the message using the provider's private key specified in the
//  parameters. A dummy SignerId is created and stored in the message.
//
//  Normally used until a certificate has been created for the key.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CryptSignMessageWithKey(
    IN PCRYPT_KEY_SIGN_MESSAGE_PARA pSignPara,
    IN const BYTE *pbToBeSigned,
    IN DWORD cbToBeSigned,
    OUT BYTE *pbSignedBlob,
    IN OUT DWORD *pcbSignedBlob
    );

//+-------------------------------------------------------------------------
//  Verify a signed message using the specified public key info.
//
//  Normally called by a CA until it has created a certificate for the
//  key.
//
//  pPublicKeyInfo contains the public key to use to verify the signed
//  message. If NULL, the signature isn't verified (for instance, the decoded
//  content may contain the PublicKeyInfo).
//
//  pcbDecoded can be NULL, indicating the caller isn't interested
//  in getting the decoded content.
//--------------------------------------------------------------------------
WINCRYPT32API
BOOL
WINAPI
CryptVerifyMessageSignatureWithKey(
    IN PCRYPT_KEY_VERIFY_MESSAGE_PARA pVerifyPara,
    IN OPTIONAL PCERT_PUBLIC_KEY_INFO pPublicKeyInfo,
    IN const BYTE *pbSignedBlob,
    IN DWORD cbSignedBlob,
    OUT OPTIONAL BYTE *pbDecoded,
    IN OUT OPTIONAL DWORD *pcbDecoded
    );


//+=========================================================================
//  System Certificate Store Data Structures and APIs
//==========================================================================


//+-------------------------------------------------------------------------
//  Get a system certificate store based on a subsystem protocol.
//
//  Current examples of subsystems protocols are:
//      "MY"    Cert Store hold certs with associated Private Keys
//      "CA"    Certifying Authority certs
//      "ROOT"  Root Certs
//      "SPC"   Software publisher certs
//
//
//  If hProv is NULL the default provider "1" is opened for you.
//  When the store is closed the provider is release. Otherwise
//  if hProv is not NULL, no provider is created or released.
//
//  The returned Cert Store can be searched for an appropriate Cert
//  using the Cert Store API's (see certstor.h)
//
//  When done, the cert store should be closed using CertStoreClose
//--------------------------------------------------------------------------


WINCRYPT32API HCERTSTORE WINAPI CertOpenSystemStoreA(
    HCRYPTPROV      hProv,
    LPCSTR            szSubsystemProtocol
    );
WINCRYPT32API HCERTSTORE WINAPI CertOpenSystemStoreW(
    HCRYPTPROV      hProv,
    LPCWSTR            szSubsystemProtocol
    );
#ifdef UNICODE
#define CertOpenSystemStore  CertOpenSystemStoreW
#else
#define CertOpenSystemStore  CertOpenSystemStoreA
#endif // !UNICODE

WINCRYPT32API BOOL WINAPI CertAddEncodedCertificateToSystemStoreA(
    LPCSTR            szCertStoreName,
    const BYTE *    pbCertEncoded,
    DWORD           cbCertEncoded
    );
WINCRYPT32API BOOL WINAPI CertAddEncodedCertificateToSystemStoreW(
    LPCWSTR            szCertStoreName,
    const BYTE *    pbCertEncoded,
    DWORD           cbCertEncoded
    );
#ifdef UNICODE
#define CertAddEncodedCertificateToSystemStore  CertAddEncodedCertificateToSystemStoreW
#else
#define CertAddEncodedCertificateToSystemStore  CertAddEncodedCertificateToSystemStoreA
#endif // !UNICODE


//+-------------------------------------------------------------------------
//  Find all certificate chains tying the given issuer name to any certificate
//  that the current user has a private key for.
//
//  If no certificate chain is found, FALSE is returned with LastError set
//  to CRYPT_E_NOT_FOUND and the counts zeroed.
//
//  IE 3.0 ASSUMPTION:
//   The client certificates are in the "My" system store. The issuer
//   cerificates may be in the "Root", "CA" or "My" system stores.
//--------------------------------------------------------------------------
typedef struct _CERT_CHAIN {
    DWORD                   cCerts;     // number of certs in chain
    PCERT_BLOB              certs;      // pointer to array of cert chain blobs
                                        // representing the certs
    CRYPT_KEY_PROV_INFO     keyLocatorInfo; // key locator for cert
} CERT_CHAIN, *PCERT_CHAIN;


// WINCRYPT32API    This is not exported by crypt32, it is exported by softpub
HRESULT
WINAPI
FindCertsByIssuer(
    OUT PCERT_CHAIN pCertChains,
    IN OUT DWORD *pcbCertChains,
    OUT DWORD *pcCertChains,        // count of certificates chains returned
    IN BYTE* pbEncodedIssuerName,   // DER encoded issuer name
    IN DWORD cbEncodedIssuerName,   // count in bytes of encoded issuer name
    IN LPCWSTR pwszPurpose,         // "ClientAuth" or "CodeSigning"
    IN DWORD dwKeySpec              // only return signers supporting this
                                    // keyspec
    );

#ifdef __cplusplus
}       // Balance extern "C" above
#endif

#endif /* _WIN32_WINNT >= 0x0400 */


#endif // __WINCRYPT_H__
