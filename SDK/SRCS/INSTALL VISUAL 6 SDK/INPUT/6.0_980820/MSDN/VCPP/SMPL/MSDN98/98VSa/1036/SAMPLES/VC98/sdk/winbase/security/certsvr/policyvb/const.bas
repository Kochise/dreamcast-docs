Attribute VB_Name = "Const"
Option Explicit
'+---------------------------------------------------------------------------
'
' Microsoft Windows
'
' File: wincrypt.h
'
' Contents: Cryptographic API Prototypes and Definitions
'
'----------------------------------------------------------------------------
'
' Algorithm IDs and Flags
'
' ALG_ID crackers
' Algorithm classes
Public Const ALG_CLASS_ANY As Long = 0
' Algorithm types
Public Const ALG_TYPE_ANY As Long = 0
' Generic sub-ids
Public Const ALG_SID_ANY As Long = 0
' Some RSA sub-ids
Public Const ALG_SID_RSA_ANY As Long = 0
Public Const ALG_SID_RSA_PKCS As Long = 1
Public Const ALG_SID_RSA_MSATWORK As Long = 2
Public Const ALG_SID_RSA_ENTRUST As Long = 3
Public Const ALG_SID_RSA_PGP As Long = 4
' Some DSS sub-ids
'
Public Const ALG_SID_DSS_ANY As Long = 0
Public Const ALG_SID_DSS_PKCS As Long = 1
Public Const ALG_SID_DSS_DMS As Long = 2
' Block cipher sub ids
' DES sub_ids
Public Const ALG_SID_DES As Long = 1
Public Const ALG_SID_3DES As Long = 3
Public Const ALG_SID_DESX As Long = 4
Public Const ALG_SID_IDEA As Long = 5
Public Const ALG_SID_CAST As Long = 6
Public Const ALG_SID_SAFERSK64 As Long = 7
Public Const ALD_SID_SAFERSK128 As Long = 8
Public Const ALG_SID_3DES_112 As Long = 9
Public Const ALG_SID_CYLINK_MEK As Long = 12
Public Const ALG_SID_RC5 As Long = 13
' Fortezza sub-ids
Public Const ALG_SID_SKIPJACK As Long = 10
Public Const ALG_SID_TEK As Long = 11
' KP_MODE
Public Const CRYPT_MODE_CBCI As Long = 6
Public Const CRYPT_MODE_CFBP As Long = 7
Public Const CRYPT_MODE_OFBP As Long = 8
Public Const CRYPT_MODE_CBCOFM As Long = 9
Public Const CRYPT_MODE_CBCOFMI As Long = 10
' RC2 sub-ids
Public Const ALG_SID_RC2 As Long = 2
' Stream cipher sub-ids
Public Const ALG_SID_RC4 As Long = 1
Public Const ALG_SID_SEAL As Long = 2
' Diffie-Hellman sub-ids
Public Const ALG_SID_DH_SANDF As Long = 1
Public Const ALG_SID_DH_EPHEM As Long = 2
Public Const ALG_SID_AGREED_KEY_ANY As Long = 3
Public Const ALG_SID_KEA As Long = 4
' Hash sub ids
Public Const ALG_SID_MD2 As Long = 1
Public Const ALG_SID_MD4 As Long = 2
Public Const ALG_SID_MD5 As Long = 3
Public Const ALG_SID_SHA As Long = 4
Public Const ALG_SID_SHA1 As Long = 4
Public Const ALG_SID_MAC As Long = 5
Public Const ALG_SID_RIPEMD As Long = 6
Public Const ALG_SID_RIPEMD160 As Long = 7
Public Const ALG_SID_SSL3SHAMD5 As Long = 8
Public Const ALG_SID_HMAC As Long = 9
' secure channel sub ids
Public Const ALG_SID_SSL3_MASTER As Long = 1
Public Const ALG_SID_SCHANNEL_MASTER_HASH As Long = 2
Public Const ALG_SID_SCHANNEL_MAC_KEY As Long = 3
Public Const ALG_SID_PCT1_MASTER As Long = 4
Public Const ALG_SID_SSL2_MASTER As Long = 5
Public Const ALG_SID_TLS1_MASTER As Long = 6
Public Const ALG_SID_SCHANNEL_ENC_KEY As Long = 7
' Our silly example sub-id
Public Const ALG_SID_EXAMPLE As Long = 80
' algorithm identifier definitions
' dwFlags definitions for CryptAcquireContext
Public Const CRYPT_VERIFYCONTEXT As Long = &HF0000000
Public Const CRYPT_NEWKEYSET As Long = &H00000008
Public Const CRYPT_DELETEKEYSET As Long = &H00000010
Public Const CRYPT_MACHINE_KEYSET As Long = &H00000020
' dwFlag definitions for CryptGenKey
Public Const CRYPT_EXPORTABLE As Long = &H00000001
Public Const CRYPT_USER_PROTECTED As Long = &H00000002
Public Const CRYPT_CREATE_SALT As Long = &H00000004
Public Const CRYPT_UPDATE_KEY As Long = &H00000008
Public Const CRYPT_NO_SALT As Long = &H00000010
Public Const CRYPT_PREGEN As Long = &H00000040
Public Const CRYPT_RECIPIENT As Long = &H00000010
Public Const CRYPT_INITIATOR As Long = &H00000040
Public Const CRYPT_ONLINE As Long = &H00000080
Public Const CRYPT_SF As Long = &H00000100
Public Const CRYPT_CREATE_IV As Long = &H00000200
Public Const CRYPT_KEK As Long = &H00000400
Public Const CRYPT_DATA_KEY As Long = &H00000800
' dwFlags definitions for CryptDeriveKey
Public Const CRYPT_SERVER As Long = &H00000400
Public Const KEY_LENGTH_MASK As Long = &HFFFF0000
' dwFlag definitions for CryptExportKey
Public Const CRYPT_Y_ONLY As Long = &H00000001
Public Const CRYPT_SSL2_SLUMMING As Long = &H00000002
' dwFlags definitions for CryptHashSessionKey
Public Const CRYPT_LITTLE_ENDIAN As Long = &H00000001
' dwFlag definitions for CryptSetProviderEx and CryptGetDefaultProvider
Public Const CRYPT_MACHINE_DEFAULT As Long = &H00000001
Public Const CRYPT_USER_DEFAULT As Long = &H00000002
Public Const CRYPT_DELETE_DEFAULT As Long = &H00000004
' exported key blob definitions
Public Const SIMPLEBLOB As Long = &H1
Public Const PUBLICKEYBLOB As Long = &H6
Public Const PRIVATEKEYBLOB As Long = &H7
Public Const PLAINTEXTKEYBLOB As Long = &H8
Public Const AT_KEYEXCHANGE As Long = 1
Public Const AT_SIGNATURE As Long = 2
Public Const CRYPT_USERDATA As Long = 1
' dwParam
Public Const KP_IV As Long = 1
Public Const KP_SALT As Long = 2
Public Const KP_PADDING As Long = 3
Public Const KP_MODE As Long = 4
Public Const KP_MODE_BITS As Long = 5
Public Const KP_PERMISSIONS As Long = 6
Public Const KP_ALGID As Long = 7
Public Const KP_BLOCKLEN As Long = 8
Public Const KP_KEYLEN As Long = 9
Public Const KP_SALT_EX As Long = 10
Public Const KP_P As Long = 11
Public Const KP_G As Long = 12
Public Const KP_Q As Long = 13
Public Const KP_X As Long = 14
Public Const KP_Y As Long = 15
Public Const KP_RA As Long = 16
Public Const KP_RB As Long = 17
Public Const KP_INFO As Long = 18
Public Const KP_EFFECTIVE_KEYLEN As Long = 19
Public Const KP_SCHANNEL_ALG As Long = 20
Public Const KP_CLIENT_RANDOM As Long = 21
Public Const KP_SERVER_RANDOM As Long = 22
Public Const KP_RP As Long = 23
Public Const KP_PRECOMP_MD5 As Long = 24
Public Const KP_PRECOMP_SHA As Long = 25
Public Const KP_CERTIFICATE As Long = 26
Public Const KP_CLEAR_KEY As Long = 27
Public Const KP_PUB_EX_LEN As Long = 28
Public Const KP_PUB_EX_VAL As Long = 29
' KP_PADDING
Public Const PKCS5_PADDING As Long = 1
Public Const RANDOM_PADDING As Long = 2
Public Const ZERO_PADDING As Long = 3
' KP_MODE
Public Const CRYPT_MODE_CBC As Long = 1
Public Const CRYPT_MODE_ECB As Long = 2
Public Const CRYPT_MODE_OFB As Long = 3
Public Const CRYPT_MODE_CFB As Long = 4
Public Const CRYPT_MODE_CTS As Long = 5
' KP_PERMISSIONS
Public Const CRYPT_ENCRYPT As Long = &H0001
Public Const CRYPT_DECRYPT As Long = &H0002
Public Const CRYPT_EXPORT As Long = &H0004
Public Const CRYPT_READ As Long = &H0008
Public Const CRYPT_WRITE As Long = &H0010
Public Const CRYPT_MAC As Long = &H0020
Public Const CRYPT_EXPORT_KEY As Long = &H0040
Public Const CRYPT_IMPORT_KEY As Long = &H0080
Public Const HP_ALGID As Long = &H0001
Public Const HP_HASHVAL As Long = &H0002
Public Const HP_HASHSIZE As Long = &H0004
Public Const HP_HMAC_INFO As Long = &H0005
'
' CryptGetProvParam
'
Public Const PP_ENUMALGS As Long = 1
Public Const PP_ENUMCONTAINERS As Long = 2
Public Const PP_IMPTYPE As Long = 3
Public Const PP_NAME As Long = 4
Public Const PP_VERSION As Long = 5
Public Const PP_CONTAINER As Long = 6
Public Const PP_CHANGE_PASSWORD As Long = 7
Public Const PP_KEYSET_SEC_DESCR As Long = 8
Public Const PP_CERTCHAIN As Long = 9
Public Const PP_KEY_TYPE_SUBTYPE As Long = 10
Public Const PP_PROVTYPE As Long = 16
Public Const PP_KEYSTORAGE As Long = 17
Public Const PP_APPLI_CERT As Long = 18
Public Const PP_SYM_KEYSIZE As Long = 19
Public Const PP_SESSION_KEYSIZE As Long = 20
Public Const PP_UI_PROMPT As Long = 21
Public Const PP_ENUMALGS_EX As Long = 22
Public Const CRYPT_FIRST As Long = 1
Public Const CRYPT_NEXT As Long = 2
Public Const CRYPT_IMPL_HARDWARE As Long = 1
Public Const CRYPT_IMPL_SOFTWARE As Long = 2
Public Const CRYPT_IMPL_MIXED As Long = 3
Public Const CRYPT_IMPL_UNKNOWN As Long = 4
' key storage flags
Public Const CRYPT_SEC_DESCR As Long = &H00000001
Public Const CRYPT_PSTORE As Long = &H00000002
Public Const CRYPT_UI_PROMPT As Long = &H00000004
' protocol flags
Public Const CRYPT_FLAG_PCT1 As Long = &H0001
Public Const CRYPT_FLAG_SSL2 As Long = &H0002
Public Const CRYPT_FLAG_SSL3 As Long = &H0004
Public Const CRYPT_FLAG_TLS1 As Long = &H0008
'
' CryptSetProvParam
'
Public Const PP_CLIENT_HWND As Long = 1
Public Const PP_CONTEXT_INFO As Long = 11
Public Const PP_KEYEXCHANGE_KEYSIZE As Long = 12
Public Const PP_SIGNATURE_KEYSIZE As Long = 13
Public Const PP_KEYEXCHANGE_ALG As Long = 14
Public Const PP_SIGNATURE_ALG As Long = 15
Public Const PROV_RSA_FULL As Long = 1
Public Const PROV_RSA_SIG As Long = 2
Public Const PROV_DSS As Long = 3
Public Const PROV_FORTEZZA As Long = 4
Public Const PROV_MS_EXCHANGE As Long = 5
Public Const PROV_SSL As Long = 6
Public Const PROV_RSA_SCHANNEL As Long = 12
Public Const PROV_DSS_DH As Long = 13
Public Const PROV_EC_ECDSA As Long = 14
Public Const PROV_EC_ECNR As Long = 15
Public Const PROV_EC_ECDSA_FULL As Long = 16
Public Const PROV_EC_ECNR_FULL As Long = 17
Public Const PROV_SPYRUS_LYNKS As Long = 20
'
' STT defined Providers
'
Public Const PROV_STT_MER As Long = 7
Public Const PROV_STT_ACQ As Long = 8
Public Const PROV_STT_BRND As Long = 9
Public Const PROV_STT_ROOT As Long = 10
Public Const PROV_STT_ISS As Long = 11
'
' Provider friendly names
'
Public Const MS_DEF_PROV_A As String = "Microsoft Base Cryptographic Provider v1.0"
Public Const MS_DEF_PROV_W As String = "Microsoft Base Cryptographic Provider v1.0"
Public Const MS_ENHANCED_PROV_A As String = "Microsoft Enhanced Cryptographic Provider v1.0"
Public Const MS_ENHANCED_PROV_W As String = "Microsoft Enhanced Cryptographic Provider v1.0"
Public Const MS_DEF_DSS_PROV_A As String = "Microsoft Base DSS Cryptographic Provider"
Public Const MS_DEF_DSS_PROV_W As String = "Microsoft Base DSS Cryptographic Provider"
Public Const MAXUIDLEN As Long = 64
Public Const CUR_BLOB_VERSION As Long = 2
' structure for use with CryptSetHashParam with CALG_HMAC
' structure for use with CryptSetKeyParam with KP_SCHANNEL_ALG
' uses of algortihms for SCHANNEL_ALG structure
Public Const SCHANNEL_MAC_KEY As Long = &H00000000
Public Const SCHANNEL_ENC_KEY As Long = &H00000001
'+-------------------------------------------------------------------------
' CRYPTOAPI BLOB definitions
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' In a CRYPT_BIT_BLOB the last byte may contain 0-7 unused bits. Therefore, the
' overall bit length is cbData * 8 - cUnusedBits.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Type used for any algorithm
'
' Where the Parameters CRYPT_OBJID_BLOB is in its encoded representation. For most
'--------------------------------------------------------------------------
' Following are the definitions of various algorithm object identifiers
' RSA
Public Const szOID_RSA As String = "1.2.840.113549"
Public Const szOID_PKCS As String = "1.2.840.113549.1"
Public Const szOID_RSA_HASH As String = "1.2.840.113549.2"
Public Const szOID_RSA_ENCRYPT As String = "1.2.840.113549.3"
Public Const szOID_PKCS_1 As String = "1.2.840.113549.1.1"
Public Const szOID_PKCS_2 As String = "1.2.840.113549.1.2"
Public Const szOID_PKCS_3 As String = "1.2.840.113549.1.3"
Public Const szOID_PKCS_4 As String = "1.2.840.113549.1.4"
Public Const szOID_PKCS_5 As String = "1.2.840.113549.1.5"
Public Const szOID_PKCS_6 As String = "1.2.840.113549.1.6"
Public Const szOID_PKCS_7 As String = "1.2.840.113549.1.7"
Public Const szOID_PKCS_8 As String = "1.2.840.113549.1.8"
Public Const szOID_PKCS_9 As String = "1.2.840.113549.1.9"
Public Const szOID_PKCS_10 As String = "1.2.840.113549.1.10"
Public Const szOID_RSA_RSA As String = "1.2.840.113549.1.1.1"
Public Const szOID_RSA_MD2RSA As String = "1.2.840.113549.1.1.2"
Public Const szOID_RSA_MD4RSA As String = "1.2.840.113549.1.1.3"
Public Const szOID_RSA_MD5RSA As String = "1.2.840.113549.1.1.4"
Public Const szOID_RSA_SHA1RSA As String = "1.2.840.113549.1.1.5"
Public Const szOID_RSA_SETOAEP_RSA As String = "1.2.840.113549.1.1.6"
Public Const szOID_RSA_data As String = "1.2.840.113549.1.7.1"
Public Const szOID_RSA_signedData As String = "1.2.840.113549.1.7.2"
Public Const szOID_RSA_envelopedData As String = "1.2.840.113549.1.7.3"
Public Const szOID_RSA_signEnvData As String = "1.2.840.113549.1.7.4"
Public Const szOID_RSA_digestedData As String = "1.2.840.113549.1.7.5"
Public Const szOID_RSA_hashedData As String = "1.2.840.113549.1.7.5"
Public Const szOID_RSA_encryptedData As String = "1.2.840.113549.1.7.6"
Public Const szOID_RSA_emailAddr As String = "1.2.840.113549.1.9.1"
Public Const szOID_RSA_unstructName As String = "1.2.840.113549.1.9.2"
Public Const szOID_RSA_contentType As String = "1.2.840.113549.1.9.3"
Public Const szOID_RSA_messageDigest As String = "1.2.840.113549.1.9.4"
Public Const szOID_RSA_signingTime As String = "1.2.840.113549.1.9.5"
Public Const szOID_RSA_counterSign As String = "1.2.840.113549.1.9.6"
Public Const szOID_RSA_challengePwd As String = "1.2.840.113549.1.9.7"
Public Const szOID_RSA_unstructAddr As String = "1.2.840.113549.1.9.8"
Public Const szOID_RSA_extCertAttrs As String = "1.2.840.113549.1.9.9"
Public Const szOID_RSA_MD2 As String = "1.2.840.113549.2.2"
Public Const szOID_RSA_MD4 As String = "1.2.840.113549.2.4"
Public Const szOID_RSA_MD5 As String = "1.2.840.113549.2.5"
Public Const szOID_RSA_RC2CBC As String = "1.2.840.113549.3.2"
Public Const szOID_RSA_RC4 As String = "1.2.840.113549.3.4"
' ITU-T UsefulDefinitions
Public Const szOID_DS As String = "2.5"
Public Const szOID_DSALG As String = "2.5.8"
Public Const szOID_DSALG_CRPT As String = "2.5.8.1"
Public Const szOID_DSALG_HASH As String = "2.5.8.2"
Public Const szOID_DSALG_SIGN As String = "2.5.8.3"
Public Const szOID_DSALG_RSA As String = "2.5.8.1.1"
' http:
' http:
Public Const szOID_OIW As String = "1.3.14"
Public Const szOID_OIWSEC As String = "1.3.14.3.2"
Public Const szOID_OIWSEC_md4RSA As String = "1.3.14.3.2.2"
Public Const szOID_OIWSEC_md5RSA As String = "1.3.14.3.2.3"
Public Const szOID_OIWSEC_md4RSA2 As String = "1.3.14.3.2.4"
Public Const szOID_OIWSEC_desECB As String = "1.3.14.3.2.6"
Public Const szOID_OIWSEC_desCBC As String = "1.3.14.3.2.7"
Public Const szOID_OIWSEC_desOFB As String = "1.3.14.3.2.8"
Public Const szOID_OIWSEC_desCFB As String = "1.3.14.3.2.9"
Public Const szOID_OIWSEC_desMAC As String = "1.3.14.3.2.10"
Public Const szOID_OIWSEC_rsaSign As String = "1.3.14.3.2.11"
Public Const szOID_OIWSEC_dsa As String = "1.3.14.3.2.12"
Public Const szOID_OIWSEC_shaDSA As String = "1.3.14.3.2.13"
Public Const szOID_OIWSEC_mdc2RSA As String = "1.3.14.3.2.14"
Public Const szOID_OIWSEC_shaRSA As String = "1.3.14.3.2.15"
Public Const szOID_OIWSEC_dhCommMod As String = "1.3.14.3.2.16"
Public Const szOID_OIWSEC_desEDE As String = "1.3.14.3.2.17"
Public Const szOID_OIWSEC_sha As String = "1.3.14.3.2.18"
Public Const szOID_OIWSEC_mdc2 As String = "1.3.14.3.2.19"
Public Const szOID_OIWSEC_dsaComm As String = "1.3.14.3.2.20"
Public Const szOID_OIWSEC_dsaCommSHA As String = "1.3.14.3.2.21"
Public Const szOID_OIWSEC_rsaXchg As String = "1.3.14.3.2.22"
Public Const szOID_OIWSEC_keyHashSeal As String = "1.3.14.3.2.23"
Public Const szOID_OIWSEC_md2RSASign As String = "1.3.14.3.2.24"
Public Const szOID_OIWSEC_md5RSASign As String = "1.3.14.3.2.25"
Public Const szOID_OIWSEC_sha1 As String = "1.3.14.3.2.26"
Public Const szOID_OIWSEC_dsaSHA1 As String = "1.3.14.3.2.27"
Public Const szOID_OIWSEC_dsaCommSHA1 As String = "1.3.14.3.2.28"
Public Const szOID_OIWSEC_sha1RSASign As String = "1.3.14.3.2.29"
Public Const szOID_OIWDIR As String = "1.3.14.7.2"
Public Const szOID_OIWDIR_CRPT As String = "1.3.14.7.2.1"
Public Const szOID_OIWDIR_HASH As String = "1.3.14.7.2.2"
Public Const szOID_OIWDIR_SIGN As String = "1.3.14.7.2.3"
Public Const szOID_OIWDIR_md2 As String = "1.3.14.7.2.2.1"
Public Const szOID_OIWDIR_md2RSA As String = "1.3.14.7.2.3.1"
' INFOSEC Algorithms
Public Const szOID_INFOSEC As String = "2.16.840.1.101.2.1"
Public Const szOID_INFOSEC_sdnsSignature As String = "2.16.840.1.101.2.1.1.1"
Public Const szOID_INFOSEC_mosaicSignature As String = "2.16.840.1.101.2.1.1.2"
Public Const szOID_INFOSEC_sdnsConfidentiality As String = "2.16.840.1.101.2.1.1.3"
Public Const szOID_INFOSEC_mosaicConfidentiality As String = "2.16.840.1.101.2.1.1.4"
Public Const szOID_INFOSEC_sdnsIntegrity As String = "2.16.840.1.101.2.1.1.5"
Public Const szOID_INFOSEC_mosaicIntegrity As String = "2.16.840.1.101.2.1.1.6"
Public Const szOID_INFOSEC_sdnsTokenProtection As String = "2.16.840.1.101.2.1.1.7"
Public Const szOID_INFOSEC_mosaicTokenProtection As String = "2.16.840.1.101.2.1.1.8"
Public Const szOID_INFOSEC_sdnsKeyManagement As String = "2.16.840.1.101.2.1.1.9"
Public Const szOID_INFOSEC_mosaicKeyManagement As String = "2.16.840.1.101.2.1.1.10"
Public Const szOID_INFOSEC_sdnsKMandSig As String = "2.16.840.1.101.2.1.1.11"
Public Const szOID_INFOSEC_mosaicKMandSig As String = "2.16.840.1.101.2.1.1.12"
Public Const szOID_INFOSEC_SuiteASignature As String = "2.16.840.1.101.2.1.1.13"
Public Const szOID_INFOSEC_SuiteAConfidentiality As String = "2.16.840.1.101.2.1.1.14"
Public Const szOID_INFOSEC_SuiteAIntegrity As String = "2.16.840.1.101.2.1.1.15"
Public Const szOID_INFOSEC_SuiteATokenProtection As String = "2.16.840.1.101.2.1.1.16"
Public Const szOID_INFOSEC_SuiteAKeyManagement As String = "2.16.840.1.101.2.1.1.17"
Public Const szOID_INFOSEC_SuiteAKMandSig As String = "2.16.840.1.101.2.1.1.18"
Public Const szOID_INFOSEC_mosaicUpdatedSig As String = "2.16.840.1.101.2.1.1.19"
Public Const szOID_INFOSEC_mosaicKMandUpdSig As String = "2.16.840.1.101.2.1.1.20"
Public Const szOID_INFOSEC_mosaicUpdatedInteg As String = "2.16.840.1.101.2.1.1.21"
'+-------------------------------------------------------------------------
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Type used for an extension to an encoded content
'
' Where the Value's CRYPT_OBJID_BLOB is in its encoded representation.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' AttributeTypeValue
'
' Where the Value's CRYPT_OBJID_BLOB is in its encoded representation.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Attributes
'
' Where the Value's PATTR_BLOBs are in their encoded representation.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
'
' The interpretation of the Value depends on the dwValueType.
' See below for a list of the types.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' CERT_RDN attribute Object Identifiers
'--------------------------------------------------------------------------
' Labeling attribute types:
Public Const szOID_COMMON_NAME As String = "2.5.4.3"
Public Const szOID_SUR_NAME As String = "2.5.4.4"
Public Const szOID_DEVICE_SERIAL_NUMBER As String = "2.5.4.5"
' Geographic attribute types:
Public Const szOID_COUNTRY_NAME As String = "2.5.4.6"
Public Const szOID_LOCALITY_NAME As String = "2.5.4.7"
Public Const szOID_STATE_OR_PROVINCE_NAME As String = "2.5.4.8"
Public Const szOID_STREET_ADDRESS As String = "2.5.4.9"
' Organizational attribute types:
Public Const szOID_ORGANIZATION_NAME As String = "2.5.4.10"
Public Const szOID_ORGANIZATIONAL_UNIT_NAME As String = "2.5.4.11"
Public Const szOID_TITLE As String = "2.5.4.12"
' Explanatory attribute types:
Public Const szOID_DESCRIPTION As String = "2.5.4.13"
Public Const szOID_SEARCH_GUIDE As String = "2.5.4.14"
Public Const szOID_BUSINESS_CATEGORY As String = "2.5.4.15"
' Postal addressing attribute types:
Public Const szOID_POSTAL_ADDRESS As String = "2.5.4.16"
Public Const szOID_POSTAL_CODE As String = "2.5.4.17"
Public Const szOID_POST_OFFICE_BOX As String = "2.5.4.18"
Public Const szOID_PHYSICAL_DELIVERY_OFFICE_NAME As String = "2.5.4.19"
' Telecommunications addressing attribute types:
Public Const szOID_TELEPHONE_NUMBER As String = "2.5.4.20"
Public Const szOID_TELEX_NUMBER As String = "2.5.4.21"
Public Const szOID_TELETEXT_TERMINAL_IDENTIFIER As String = "2.5.4.22"
Public Const szOID_FACSIMILE_TELEPHONE_NUMBER As String = "2.5.4.23"
Public Const szOID_X21_ADDRESS As String = "2.5.4.24"
Public Const szOID_INTERNATIONAL_ISDN_NUMBER As String = "2.5.4.25"
Public Const szOID_REGISTERED_ADDRESS As String = "2.5.4.26"
Public Const szOID_DESTINATION_INDICATOR As String = "2.5.4.27"
' Preference attribute types:
Public Const szOID_PREFERRED_DELIVERY_METHOD As String = "2.5.4.28"
' OSI application attribute types:
Public Const szOID_PRESENTATION_ADDRESS As String = "2.5.4.29"
Public Const szOID_SUPPORTED_APPLICATION_CONTEXT As String = "2.5.4.30"
' Relational application attribute types:
Public Const szOID_MEMBER As String = "2.5.4.31"
Public Const szOID_OWNER As String = "2.5.4.32"
Public Const szOID_ROLE_OCCUPANT As String = "2.5.4.33"
Public Const szOID_SEE_ALSO As String = "2.5.4.34"
' Security attribute types:
Public Const szOID_USER_PASSWORD As String = "2.5.4.35"
Public Const szOID_USER_CERTIFICATE As String = "2.5.4.36"
Public Const szOID_CA_CERTIFICATE As String = "2.5.4.37"
Public Const szOID_AUTHORITY_REVOCATION_LIST As String = "2.5.4.38"
Public Const szOID_CERTIFICATE_REVOCATION_LIST As String = "2.5.4.39"
Public Const szOID_CROSS_CERTIFICATE_PAIR As String = "2.5.4.40"
' Undocumented attribute types???
'#define szOID_??? "2.5.4.41"
Public Const szOID_GIVEN_NAME As String = "2.5.4.42"
Public Const szOID_INITIALS As String = "2.5.4.43"
' Pilot user attribute types:
Public Const szOID_DOMAIN_COMPONENT As String = "0.9.2342.19200300.100.1.25"
'+-------------------------------------------------------------------------
' CERT_RDN Attribute Value Types
'
' For RDN_ENCODED_BLOB, the Value's CERT_RDN_VALUE_BLOB is in its encoded
' representation. Otherwise, its an array of bytes.
'
' For all CERT_RDN types, Value.cbData is always the number of bytes, not
' necessarily the number of elements in the string. For instance,
'
' For CertDecodeName, two 0 bytes are always appended to the end of the
' These added 0 bytes are't included in the BLOB.cbData.
'--------------------------------------------------------------------------
Public Const CERT_RDN_ANY_TYPE As Long = 0
Public Const CERT_RDN_ENCODED_BLOB As Long = 1
Public Const CERT_RDN_OCTET_STRING As Long = 2
Public Const CERT_RDN_NUMERIC_STRING As Long = 3
Public Const CERT_RDN_PRINTABLE_STRING As Long = 4
Public Const CERT_RDN_TELETEX_STRING As Long = 5
Public Const CERT_RDN_T61_STRING As Long = 5
Public Const CERT_RDN_VIDEOTEX_STRING As Long = 6
Public Const CERT_RDN_IA5_STRING As Long = 7
Public Const CERT_RDN_GRAPHIC_STRING As Long = 8
Public Const CERT_RDN_VISIBLE_STRING As Long = 9
Public Const CERT_RDN_ISO646_STRING As Long = 9
Public Const CERT_RDN_GENERAL_STRING As Long = 10
Public Const CERT_RDN_UNIVERSAL_STRING As Long = 11
Public Const CERT_RDN_INT4_STRING As Long = 11
Public Const CERT_RDN_BMP_STRING As Long = 12
Public Const CERT_RDN_UNICODE_STRING As Long = 12
' Macro to check that the dwValueType is a character string and not an
' encoded blob or octet string
'+-------------------------------------------------------------------------
' A CERT_RDN consists of an array of the above attributes
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Information stored in a subject's or issuer's name. The information
' is represented as an array of the above RDNs.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Name attribute value without the Object Identifier
'
' The interpretation of the Value depends on the dwValueType.
' See above for a list of the types.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Public Key Info
'
' The PublicKey is the encoded representation of the information as it is
' stored in the bit string
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Information stored in a certificate
'
' The Issuer, Subject, Algorithm, PublicKey and Extension BLOBs are the
' encoded representation of the information.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Certificate versions
'--------------------------------------------------------------------------
Public Const CERT_V1 As Long = 0
Public Const CERT_V2 As Long = 1
Public Const CERT_V3 As Long = 2
'+-------------------------------------------------------------------------
' Certificate Information Flags
'--------------------------------------------------------------------------
Public Const CERT_INFO_VERSION_FLAG As Long = 1
Public Const CERT_INFO_SERIAL_NUMBER_FLAG As Long = 2
Public Const CERT_INFO_SIGNATURE_ALGORITHM_FLAG As Long = 3
Public Const CERT_INFO_ISSUER_FLAG As Long = 4
Public Const CERT_INFO_NOT_BEFORE_FLAG As Long = 5
Public Const CERT_INFO_NOT_AFTER_FLAG As Long = 6
Public Const CERT_INFO_SUBJECT_FLAG As Long = 7
Public Const CERT_INFO_SUBJECT_PUBLIC_KEY_INFO_FLAG As Long = 8
Public Const CERT_INFO_ISSUER_UNIQUE_ID_FLAG As Long = 9
Public Const CERT_INFO_SUBJECT_UNIQUE_ID_FLAG As Long = 10
Public Const CERT_INFO_EXTENSION_FLAG As Long = 11
'+-------------------------------------------------------------------------
' An entry in a CRL
'
' The Extension BLOBs are the encoded representation of the information.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Information stored in a CRL
'
' The Issuer, Algorithm and Extension BLOBs are the encoded
' representation of the information.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' CRL versions
'--------------------------------------------------------------------------
Public Const CRL_V1 As Long = 0
Public Const CRL_V2 As Long = 1
'+-------------------------------------------------------------------------
' Information stored in a certificate request
'
' The Subject, Algorithm, PublicKey and Attribute BLOBs are the encoded
' representation of the information.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Certificate Request versions
'--------------------------------------------------------------------------
Public Const CERT_REQUEST_V1 As Long = 0
'+-------------------------------------------------------------------------
' Information stored in Netscape's Keygen request
'--------------------------------------------------------------------------
Public Const CERT_KEYGEN_REQUEST_V1 As Long = 0
'+-------------------------------------------------------------------------
' Certificate, CRL, Certificate Request or Keygen Request Signed Content
'
' The "to be signed" encoded content plus its signature. The ToBeSigned
' is the encoded CERT_INFO, CRL_INFO, CERT_REQUEST_INFO or
' CERT_KEYGEN_REQUEST_INFO.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' CTL Usage. Also used for EnhancedKeyUsage extension.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' An entry in a CTL
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Information stored in a CTL
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' CTL versions
'--------------------------------------------------------------------------
Public Const CTL_V1 As Long = 0
'+-------------------------------------------------------------------------
' TimeStamp Request
'
' The pszTimeStamp is the OID for the Time type requested
' The pszContentType is the Content Type OID for the content, usually DATA
' The Content is a un-decoded blob
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Certificate and Message encoding types
'
' The encoding type is a DWORD containing both the certificate and message
' encoding types. The certificate encoding type is stored in the LOWORD.
' The message encoding type is stored in the HIWORD. Some functions or
' structure fields require only one of the encoding types. The following
' required:
'
' Its always acceptable to specify both.
'--------------------------------------------------------------------------
Public Const CERT_ENCODING_TYPE_MASK As Long = &H0000FFFF
Public Const CMSG_ENCODING_TYPE_MASK As Long = &HFFFF0000
Public Const CRYPT_ASN_ENCODING As Long = &H00000001
Public Const CRYPT_NDR_ENCODING As Long = &H00000002
Public Const X509_ASN_ENCODING As Long = &H00000001
Public Const X509_NDR_ENCODING As Long = &H00000002
Public Const PKCS_7_ASN_ENCODING As Long = &H00010000
Public Const PKCS_7_NDR_ENCODING As Long = &H00020000
'+-------------------------------------------------------------------------
' format the specified data structure according to the certificate
' encoding type.
'
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Encode / decode the specified data structure according to the certificate
' encoding type.
'
' See below for a list of the predefined data structures.
'--------------------------------------------------------------------------
' When the following flag is set the nocopy optimization is enabled.
' This optimization where appropriate, updates the pvStructInfo fields
' to point to content residing within pbEncoded instead of making a copy
' of and appending to pvStructInfo.
'
' Note, when set, pbEncoded can't be freed until pvStructInfo is freed.
Public Const CRYPT_DECODE_NOCOPY_FLAG As Long = &H1
'+-------------------------------------------------------------------------
' Predefined X509 certificate data structures that can be encoded / decoded.
'--------------------------------------------------------------------------
Public Const CRYPT_ENCODE_DECODE_NONE As Long = 0
'+-------------------------------------------------------------------------
' Predefined X509 certificate extension data structures that can be
' encoded / decoded.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Additional predefined data structures that can be encoded / decoded.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Predefined primitive data structures that can be encoded / decoded.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' More predefined X509 certificate extension data structures that can be
' encoded / decoded.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Predefined PKCS #7 data structures that can be encoded / decoded.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' can be encoded / decoded.
'
' Predefined values: 2000 .. 2999
'
' See spc.h for value and data structure definitions.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Extension Object Identifiers
'--------------------------------------------------------------------------
Public Const szOID_AUTHORITY_KEY_IDENTIFIER As String = "2.5.29.1"
Public Const szOID_KEY_ATTRIBUTES As String = "2.5.29.2"
Public Const szOID_KEY_USAGE_RESTRICTION As String = "2.5.29.4"
Public Const szOID_SUBJECT_ALT_NAME As String = "2.5.29.7"
Public Const szOID_ISSUER_ALT_NAME As String = "2.5.29.8"
Public Const szOID_BASIC_CONSTRAINTS As String = "2.5.29.10"
Public Const szOID_KEY_USAGE As String = "2.5.29.15"
Public Const szOID_BASIC_CONSTRAINTS2 As String = "2.5.29.19"
Public Const szOID_CERT_POLICIES As String = "2.5.29.32"
Public Const szOID_AUTHORITY_KEY_IDENTIFIER2 As String = "2.5.29.35"
Public Const szOID_SUBJECT_KEY_IDENTIFIER As String = "2.5.29.14"
Public Const szOID_SUBJECT_ALT_NAME2 As String = "2.5.29.17"
Public Const szOID_ISSUER_ALT_NAME2 As String = "2.5.29.18"
Public Const szOID_CRL_REASON_CODE As String = "2.5.29.21"
Public Const szOID_CRL_DIST_POINTS As String = "2.5.29.31"
Public Const szOID_ENHANCED_KEY_USAGE As String = "2.5.29.37"
' Internet Public Key Infrastructure
Public Const szOID_PKIX As String = "1.3.6.1.5.5.7"
Public Const szOID_AUTHORITY_INFO_ACCESS As String = "1.3.6.1.5.5.7.2"
' Microsoft extensions or attributes
Public Const szOID_CERT_EXTENSIONS As String = "1.3.6.1.4.1.311.2.1.14"
Public Const szOID_NEXT_UPDATE_LOCATION As String = "1.3.6.1.4.1.311.10.2"
' Microsoft PKCS #7 ContentType Object Identifiers
Public Const szOID_CTL As String = "1.3.6.1.4.1.311.10.1"
'+-------------------------------------------------------------------------
'--------------------------------------------------------------------------
Public Const szOID_POLICY_MAPPINGS As String = "2.5.29.5"
Public Const szOID_SUBJECT_DIR_ATTRS As String = "2.5.29.9"
'+-------------------------------------------------------------------------
'--------------------------------------------------------------------------
Public Const szOID_PKIX_KP As String = "1.3.6.1.5.5.7.3"
' Consistent key usage bits: DIGITAL_SIGNATURE, KEY_ENCIPHERMENT
' or KEY_AGREEMENT
Public Const szOID_PKIX_KP_SERVER_AUTH As String = "1.3.6.1.5.5.7.3.1"
' Consistent key usage bits: DIGITAL_SIGNATURE
Public Const szOID_PKIX_KP_CLIENT_AUTH As String = "1.3.6.1.5.5.7.3.2"
' Consistent key usage bits: DIGITAL_SIGNATURE
Public Const szOID_PKIX_KP_CODE_SIGNING As String = "1.3.6.1.5.5.7.3.3"
' Consistent key usage bits: DIGITAL_SIGNATURE, NON_REPUDIATION and/or
Public Const szOID_PKIX_KP_EMAIL_PROTECTION As String = "1.3.6.1.5.5.7.3.4"
'+-------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Signer of CTLs
Public Const szOID_KP_CTL_USAGE_SIGNING As String = "1.3.6.1.4.1.311.10.3.1"
'+-------------------------------------------------------------------------
' Microsoft Attribute Object Identifiers
'+-------------------------------------------------------------------------
Public Const szOID_YESNO_TRUST_ATTR As String = "1.3.6.1.4.1.311.10.4.1"
'+-------------------------------------------------------------------------
' X509_CERT
'
' The "to be signed" encoded content plus its signature. The ToBeSigned
' X509_CERT_TO_BE_SIGNED, X509_CERT_CRL_TO_BE_SIGNED or
' X509_CERT_REQUEST_TO_BE_SIGNED.
'
' pvStructInfo points to CERT_SIGNED_CONTENT_INFO.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' X509_CERT_TO_BE_SIGNED
'
' pvStructInfo points to CERT_INFO.
'
'
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' X509_CERT_CRL_TO_BE_SIGNED
'
' pvStructInfo points to CRL_INFO.
'
'
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' X509_CERT_REQUEST_TO_BE_SIGNED
'
' pvStructInfo points to CERT_REQUEST_INFO.
'
'
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' X509_EXTENSIONS
' szOID_CERT_EXTENSIONS
'
' pvStructInfo points to following CERT_EXTENSIONS.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' X509_NAME_VALUE
' X509_ANY_STRING
'
' pvStructInfo points to CERT_NAME_VALUE.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' X509_UNICODE_NAME_VALUE
' X509_UNICODE_ANY_STRING
'
' pvStructInfo points to CERT_NAME_VALUE.
'
' The name values are unicode strings.
'
' For CryptEncodeObject:
' Value.pbData points to the unicode string.
' If Value.cbData = 0, then, the unicode string is NULL terminated.
' Otherwise, Value.cbData is the unicode string byte count. The byte count
' is twice the character count.
'
' If the unicode string contains an invalid character for the specified
' dwValueType, then, *pcbEncoded is updated with the unicode character
' index of the first invalid character. LastError is set to:
' CRYPT_E_INVALID_NUMERIC_STRING, CRYPT_E_INVALID_PRINTABLE_STRING or
' CRYPT_E_INVALID_IA5_STRING.
'
' The unicode string is converted before being encoded according to
' the specified dwValueType. If dwValueType is set to 0, LastError
' is set to E_INVALIDARG.
'
' CERT_RDN_ENCODED_BLOB or CERT_RDN_OCTET_STRING), then, CryptEncodeObject
' will return FALSE with LastError set to CRYPT_E_NOT_CHAR_STRING.
'
' For CryptDecodeObject:
' Value.pbData points to a NULL terminated unicode string. Value.cbData
' contains the byte count of the unicode string excluding the NULL
' terminator. dwValueType contains the type used in the encoded object.
' Its not forced to CERT_RDN_UNICODE_STRING. The encoded value is
' converted to the unicode string according to the dwValueType.
'
' If the encoded object isn't one of the character string types, then,
' CryptDecodeObject will return FALSE with LastError set to
' CRYPT_E_NOT_CHAR_STRING. For a non character string, decode using
' X509_NAME_VALUE or X509_ANY_STRING.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' X509_NAME
'
' pvStructInfo points to CERT_NAME_INFO.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' X509_UNICODE_NAME
'
' pvStructInfo points to CERT_NAME_INFO.
'
' The RDN attribute values are unicode strings except for the dwValueTypes of
' CERT_RDN_ENCODED_BLOB or CERT_RDN_OCTET_STRING. These dwValueTypes are
' the same as for a X509_NAME. Their values aren't converted to/from unicode.
'
' For CryptEncodeObject:
' Value.pbData points to the unicode string.
' If Value.cbData = 0, then, the unicode string is NULL terminated.
' Otherwise, Value.cbData is the unicode string byte count. The byte count
' is twice the character count.
'
' an acceptable dwValueType. If the unicode string contains an
' invalid character for the found or specified dwValueType, then,
' *pcbEncoded is updated with the error location of the invalid character.
' See below for details. LastError is set to:
' CRYPT_E_INVALID_NUMERIC_STRING, CRYPT_E_INVALID_PRINTABLE_STRING or
' CRYPT_E_INVALID_IA5_STRING.
'
' The unicode string is converted before being encoded according to
' the specified or ObjId matching dwValueType.
'
' For CryptDecodeObject:
' Value.pbData points to a NULL terminated unicode string. Value.cbData
' contains the byte count of the unicode string excluding the NULL
' terminator. dwValueType contains the type used in the encoded object.
' Its not forced to CERT_RDN_UNICODE_STRING. The encoded value is
' converted to the unicode string according to the dwValueType.
'
' If the dwValueType of the encoded value isn't a character string
' type, then, it isn't converted to UNICODE. Use the
' that Value.pbData points to a converted unicode string.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Unicode Name Value Error Location Definitions
'
' Error location is returned in *pcbEncoded by
'
' Error location consists of:
' RDN_INDEX - 10 bits << 22
' ATTR_INDEX - 6 bits << 16
'--------------------------------------------------------------------------
Public Const CERT_UNICODE_RDN_ERR_INDEX_MASK As Long = &H3FF
Public Const CERT_UNICODE_RDN_ERR_INDEX_SHIFT As Long = 22
Public Const CERT_UNICODE_ATTR_ERR_INDEX_MASK As Long = &H003F
Public Const CERT_UNICODE_ATTR_ERR_INDEX_SHIFT As Long = 16
Public Const CERT_UNICODE_VALUE_ERR_INDEX_MASK As Long = &H0000FFFF
Public Const CERT_UNICODE_VALUE_ERR_INDEX_SHIFT As Long = 0
'+-------------------------------------------------------------------------
' X509_PUBLIC_KEY_INFO
'
' pvStructInfo points to CERT_PUBLIC_KEY_INFO.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' X509_AUTHORITY_KEY_ID
' szOID_AUTHORITY_KEY_IDENTIFIER
'
' pvStructInfo points to following CERT_AUTHORITY_KEY_ID_INFO.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' X509_KEY_ATTRIBUTES
' szOID_KEY_ATTRIBUTES
'
' pvStructInfo points to following CERT_KEY_ATTRIBUTES_INFO.
'--------------------------------------------------------------------------
Public Const CERT_DIGITAL_SIGNATURE_KEY_USAGE As Long = &H80
Public Const CERT_NON_REPUDIATION_KEY_USAGE As Long = &H40
Public Const CERT_KEY_ENCIPHERMENT_KEY_USAGE As Long = &H20
Public Const CERT_DATA_ENCIPHERMENT_KEY_USAGE As Long = &H10
Public Const CERT_KEY_AGREEMENT_KEY_USAGE As Long = &H08
Public Const CERT_KEY_CERT_SIGN_KEY_USAGE As Long = &H04
Public Const CERT_OFFLINE_CRL_SIGN_KEY_USAGE As Long = &H02
Public Const CERT_CRL_SIGN_KEY_USAGE As Long = &H02
'+-------------------------------------------------------------------------
' X509_KEY_USAGE_RESTRICTION
' szOID_KEY_USAGE_RESTRICTION
'
' pvStructInfo points to following CERT_KEY_USAGE_RESTRICTION_INFO.
'--------------------------------------------------------------------------
' See CERT_KEY_ATTRIBUTES_INFO for definition of the RestrictedKeyUsage bits
'+-------------------------------------------------------------------------
' X509_ALTERNATE_NAME
' szOID_SUBJECT_ALT_NAME
' szOID_ISSUER_ALT_NAME
' szOID_SUBJECT_ALT_NAME2
' szOID_ISSUER_ALT_NAME2
'
' pvStructInfo points to following CERT_ALT_NAME_INFO.
'--------------------------------------------------------------------------
Public Const CERT_ALT_NAME_OTHER_NAME As Long = 1
Public Const CERT_ALT_NAME_RFC822_NAME As Long = 2
Public Const CERT_ALT_NAME_DNS_NAME As Long = 3
Public Const CERT_ALT_NAME_X400_ADDRESS As Long = 4
Public Const CERT_ALT_NAME_DIRECTORY_NAME As Long = 5
Public Const CERT_ALT_NAME_EDI_PARTY_NAME As Long = 6
Public Const CERT_ALT_NAME_URL As Long = 7
Public Const CERT_ALT_NAME_IP_ADDRESS As Long = 8
Public Const CERT_ALT_NAME_REGISTERED_ID As Long = 9
'+-------------------------------------------------------------------------
' Alternate name IA5 Error Location Definitions for
' CRYPT_E_INVALID_IA5_STRING.
'
' Error location is returned in *pcbEncoded by
'
' Error location consists of:
' ENTRY_INDEX - 8 bits << 16
'--------------------------------------------------------------------------
Public Const CERT_ALT_NAME_ENTRY_ERR_INDEX_MASK As Long = &HFF
Public Const CERT_ALT_NAME_ENTRY_ERR_INDEX_SHIFT As Long = 16
Public Const CERT_ALT_NAME_VALUE_ERR_INDEX_MASK As Long = &H0000FFFF
Public Const CERT_ALT_NAME_VALUE_ERR_INDEX_SHIFT As Long = 0
'+-------------------------------------------------------------------------
' X509_BASIC_CONSTRAINTS
' szOID_BASIC_CONSTRAINTS
'
' pvStructInfo points to following CERT_BASIC_CONSTRAINTS_INFO.
'--------------------------------------------------------------------------
Public Const CERT_CA_SUBJECT_FLAG As Long = &H80
Public Const CERT_END_ENTITY_SUBJECT_FLAG As Long = &H40
'+-------------------------------------------------------------------------
' X509_BASIC_CONSTRAINTS2
' szOID_BASIC_CONSTRAINTS2
'
' pvStructInfo points to following CERT_BASIC_CONSTRAINTS2_INFO.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' X509_KEY_USAGE
' szOID_KEY_USAGE
'
' pvStructInfo points to a CRYPT_BIT_BLOB. Has same bit definitions as
' CERT_KEY_ATTRIBUTES_INFO's IntendedKeyUsage.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' X509_CERT_POLICIES
' szOID_CERT_POLICIES
'
' pvStructInfo points to following CERT_POLICIES_INFO.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' RSA_CSP_PUBLICKEYBLOB
'
' pvStructInfo points to a PUBLICKEYSTRUC immediately followed by a
' RSAPUBKEY and the modulus bytes.
'
' CryptExportKey outputs the above StructInfo for a dwBlobType of
' PUBLICKEYBLOB. CryptImportKey expects the above StructInfo when
' importing a public key.
'
' For dwCertEncodingType = X509_ASN_ENCODING, the RSA_CSP_PUBLICKEYBLOB is
' encoded as a PKCS #1 RSAPublicKey consisting of a SEQUENCE of a
' modulus INTEGER and a publicExponent INTEGER. The modulus is encoded
' as being a unsigned integer. When decoded, if the modulus was encoded
' as unsigned integer with a leading 0 byte, the 0 byte is removed before
' converting to the CSP modulus bytes.
'
' For decode, the aiKeyAlg field of PUBLICKEYSTRUC is always set to
' CALG_RSA_KEYX.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' X509_KEYGEN_REQUEST_TO_BE_SIGNED
'
' pvStructInfo points to CERT_KEYGEN_REQUEST_INFO.
'
'
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' PKCS_ATTRIBUTE data structure
'
' pvStructInfo points to a CRYPT_ATTRIBUTE.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' PKCS_CONTENT_INFO_SEQUENCE_OF_ANY data structure
'
' pvStructInfo points to following CRYPT_CONTENT_INFO_SEQUENCE_OF_ANY.
'
' For X509_ASN_ENCODING: encoded as a PKCS#7 ContentInfo structure wrapping
' a sequence of ANY. The value of the contentType field is pszObjId,
' while the content field is the following structure:
' SequenceOfAny ::= SEQUENCE OF ANY
'
' The CRYPT_DER_BLOBs point to the already encoded ANY content.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' PKCS_CONTENT_INFO data structure
'
' pvStructInfo points to following CRYPT_CONTENT_INFO.
'
' For X509_ASN_ENCODING: encoded as a PKCS#7 ContentInfo structure.
' The CRYPT_DER_BLOB points to the already encoded ANY content.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' X509_OCTET_STRING data structure
'
' pvStructInfo points to a CRYPT_DATA_BLOB.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' X509_BITS data structure
'
' pvStructInfo points to a CRYPT_BIT_BLOB.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' X509_INTEGER data structure
'
' pvStructInfo points to an int.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' X509_MULTI_BYTE_INTEGER data structure
'
' pvStructInfo points to a CRYPT_INTEGER_BLOB.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' X509_ENUMERATED data structure
'
' pvStructInfo points to an int containing the enumerated value
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' X509_CHOICE_OF_TIME data structure
'
' pvStructInfo points to a FILETIME.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' X509_SEQUENCE_OF_ANY data structure
'
' pvStructInfo points to following CRYPT_SEQUENCE_OF_ANY.
'
' The CRYPT_DER_BLOBs point to the already encoded ANY content.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' X509_AUTHORITY_KEY_ID2
' szOID_AUTHORITY_KEY_IDENTIFIER2
'
' pvStructInfo points to following CERT_AUTHORITY_KEY_ID2_INFO.
'
' For CRYPT_E_INVALID_IA5_STRING, the error location is returned in
'
' See X509_ALTERNATE_NAME for error location defines.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' szOID_SUBJECT_KEY_IDENTIFIER
'
' pvStructInfo points to a CRYPT_DATA_BLOB.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' X509_CRL_REASON_CODE
' szOID_CRL_REASON_CODE
'
' pvStructInfo points to an int which can be set to one of the following
' enumerated values:
'--------------------------------------------------------------------------
Public Const CRL_REASON_UNSPECIFIED As Long = 0
Public Const CRL_REASON_KEY_COMPROMISE As Long = 1
Public Const CRL_REASON_CA_COMPROMISE As Long = 2
Public Const CRL_REASON_AFFILIATION_CHANGED As Long = 3
Public Const CRL_REASON_SUPERSEDED As Long = 4
Public Const CRL_REASON_CESSATION_OF_OPERATION As Long = 5
Public Const CRL_REASON_CERTIFICATE_HOLD As Long = 6
Public Const CRL_REASON_REMOVE_FROM_CRL As Long = 8
'+-------------------------------------------------------------------------
' X509_CRL_DIST_POINTS
' szOID_CRL_DIST_POINTS
'
' pvStructInfo points to following CRL_DIST_POINTS_INFO.
'
' For CRYPT_E_INVALID_IA5_STRING, the error location is returned in
'
' Error location consists of:
' POINT_INDEX - 7 bits << 24
' ENTRY_INDEX - 8 bits << 16
'
' See X509_ALTERNATE_NAME for ENTRY_INDEX and VALUE_INDEX error location
' defines.
'--------------------------------------------------------------------------
Public Const CRL_DIST_POINT_NO_NAME As Long = 0
Public Const CRL_DIST_POINT_FULL_NAME As Long = 1
Public Const CRL_DIST_POINT_ISSUER_RDN_NAME As Long = 2
Public Const CRL_REASON_UNUSED_FLAG As Long = &H80
Public Const CRL_REASON_KEY_COMPROMISE_FLAG As Long = &H40
Public Const CRL_REASON_CA_COMPROMISE_FLAG As Long = &H20
Public Const CRL_REASON_AFFILIATION_CHANGED_FLAG As Long = &H10
Public Const CRL_REASON_SUPERSEDED_FLAG As Long = &H08
Public Const CRL_REASON_CESSATION_OF_OPERATION_FLAG As Long = &H04
Public Const CRL_REASON_CERTIFICATE_HOLD_FLAG As Long = &H02
Public Const CRL_DIST_POINT_ERR_INDEX_MASK As Long = &H7F
Public Const CRL_DIST_POINT_ERR_INDEX_SHIFT As Long = 24
'+-------------------------------------------------------------------------
' X509_ENHANCED_KEY_USAGE
' szOID_ENHANCED_KEY_USAGE
'
' pvStructInfo points to a CERT_ENHKEY_USAGE, CTL_USAGE.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' szOID_NEXT_UPDATE_LOCATION
'
' pvStructInfo points to a CERT_ALT_NAME_INFO.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' PKCS_CTL
' szOID_CTL
'
' pvStructInfo points to a CTL_INFO.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' PKCS7_SIGNER_INFO
'
' pvStructInfo points to CMSG_SIGNER_INFO.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Netscape Certificate Extension Object Identifiers
'--------------------------------------------------------------------------
Public Const szOID_NETSCAPE As String = "2.16.840.1.113730"
Public Const szOID_NETSCAPE_CERT_EXTENSION As String = "2.16.840.1.113730.1"
Public Const szOID_NETSCAPE_CERT_TYPE As String = "2.16.840.1.113730.1.1"
Public Const szOID_NETSCAPE_BASE_URL As String = "2.16.840.1.113730.1.2"
Public Const szOID_NETSCAPE_REVOCATION_URL As String = "2.16.840.1.113730.1.3"
Public Const szOID_NETSCAPE_CA_REVOCATION_URL As String = "2.16.840.1.113730.1.4"
Public Const szOID_NETSCAPE_CERT_RENEWAL_URL As String = "2.16.840.1.113730.1.7"
Public Const szOID_NETSCAPE_CA_POLICY_URL As String = "2.16.840.1.113730.1.8"
Public Const szOID_NETSCAPE_SSL_SERVER_NAME As String = "2.16.840.1.113730.1.12"
Public Const szOID_NETSCAPE_COMMENT As String = "2.16.840.1.113730.1.13"
'+-------------------------------------------------------------------------
' Netscape Certificate Data Type Object Identifiers
'--------------------------------------------------------------------------
Public Const szOID_NETSCAPE_DATA_TYPE As String = "2.16.840.1.113730.2"
Public Const szOID_NETSCAPE_CERT_SEQUENCE As String = "2.16.840.1.113730.2.5"
'+-------------------------------------------------------------------------
' szOID_NETSCAPE_CERT_TYPE extension
'
' Its value is a bit string. CryptDecodeObject/CryptEncodeObject using
' X509_BITS.
'
' The following bits are defined:
'--------------------------------------------------------------------------
Public Const NETSCAPE_SSL_CLIENT_AUTH_CERT_TYPE As Long = &H80
Public Const NETSCAPE_SSL_SERVER_AUTH_CERT_TYPE As Long = &H40
Public Const NETSCAPE_SSL_CA_CERT_TYPE As Long = &H04
'+-------------------------------------------------------------------------
' szOID_NETSCAPE_BASE_URL extension
'
' Its value is an IA5_STRING. CryptDecodeObject/CryptEncodeObject using
' X509_ANY_STRING or X509_UNICODE_ANY_STRING, where,
' dwValueType = CERT_RDN_IA5_STRING.
'
' When present this string is added to the beginning of all relative URLs
' in the certificate. This extension can be considered an optimization
' to reduce the size of the URL extensions.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' szOID_NETSCAPE_REVOCATION_URL extension
'
' Its value is an IA5_STRING. CryptDecodeObject/CryptEncodeObject using
' X509_ANY_STRING or X509_UNICODE_ANY_STRING, where,
' dwValueType = CERT_RDN_IA5_STRING.
'
' It is a relative or absolute URL that can be used to check the
' revocation status of a certificate. The revocation check will be
' performed as an HTTP GET method using a url that is the concatenation of
' revocation-url and certificate-serial-number.
' Where the certificate-serial-number is encoded as a string of
' ascii hexadecimal digits. For example, if the netscape-base-url is
' https:
' cgi-bin/check-rev.cgi?, and the certificate serial number is 173420,
' the resulting URL would be:
' https:
'
' The server should return a document with a Content-Type of
' application/x-netscape-revocation. The document should contain
' a single ascii digit, '1' if the certificate is not curently valid,
' and '0' if it is curently valid.
'
' Note: for all of the URLs that include the certificate serial number,
' the serial number will be encoded as a string which consists of an even
' number of hexadecimal digits. If the number of significant digits is odd,
' the string will have a single leading zero to ensure an even number of
' digits is generated.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' szOID_NETSCAPE_CA_REVOCATION_URL extension
'
' Its value is an IA5_STRING. CryptDecodeObject/CryptEncodeObject using
' X509_ANY_STRING or X509_UNICODE_ANY_STRING, where,
' dwValueType = CERT_RDN_IA5_STRING.
'
' It is a relative or absolute URL that can be used to check the
' revocation status of any certificates that are signed by the CA that
' this certificate belongs to. This extension is only valid in CA
' certificates. The use of this extension is the same as the above
' szOID_NETSCAPE_REVOCATION_URL extension.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' szOID_NETSCAPE_CERT_RENEWAL_URL extension
'
' Its value is an IA5_STRING. CryptDecodeObject/CryptEncodeObject using
' X509_ANY_STRING or X509_UNICODE_ANY_STRING, where,
' dwValueType = CERT_RDN_IA5_STRING.
'
' It is a relative or absolute URL that points to a certificate renewal
' form. The renewal form will be accessed with an HTTP GET method using a
' url that is the concatenation of renewal-url and
' certificate-serial-number. Where the certificate-serial-number is
' encoded as a string of ascii hexadecimal digits. For example, if the
' netscape-base-url is https:
' netscape-cert-renewal-url is cgi-bin/check-renew.cgi?, and the
' certificate serial number is 173420, the resulting URL would be:
' https:
' The document returned should be an HTML form that will allow the user
' to request a renewal of their certificate.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' szOID_NETSCAPE_CA_POLICY_URL extension
'
' Its value is an IA5_STRING. CryptDecodeObject/CryptEncodeObject using
' X509_ANY_STRING or X509_UNICODE_ANY_STRING, where,
' dwValueType = CERT_RDN_IA5_STRING.
'
' It is a relative or absolute URL that points to a web page that
' describes the policies under which the certificate was issued.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' szOID_NETSCAPE_SSL_SERVER_NAME extension
'
' Its value is an IA5_STRING. CryptDecodeObject/CryptEncodeObject using
' X509_ANY_STRING or X509_UNICODE_ANY_STRING, where,
' dwValueType = CERT_RDN_IA5_STRING.
'
' It is a "shell expression" that can be used to match the hostname of the
' SSL server that is using this certificate. It is recommended that if
' the server's hostname does not match this pattern the user be notified
' and given the option to terminate the SSL connection. If this extension
' is not present then the CommonName in the certificate subject's
' distinguished name is used for the same purpose.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' szOID_NETSCAPE_COMMENT extension
'
' Its value is an IA5_STRING. CryptDecodeObject/CryptEncodeObject using
' X509_ANY_STRING or X509_UNICODE_ANY_STRING, where,
' dwValueType = CERT_RDN_IA5_STRING.
'
' It is a comment that may be displayed to the user when the certificate
' is viewed.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' szOID_NETSCAPE_CERT_SEQUENCE
'
' Its value is a PKCS#7 ContentInfo structure wrapping a sequence of
' certificates. The value of the contentType field is
' szOID_NETSCAPE_CERT_SEQUENCE, while the content field is the following
' structure:
' CertificateSequence ::= SEQUENCE OF Certificate.
'
' CryptDecodeObject/CryptEncodeObject using
' PKCS_CONTENT_INFO_SEQUENCE_OF_ANY, where,
' pszObjId = szOID_NETSCAPE_CERT_SEQUENCE and the CRYPT_DER_BLOBs point
' to encoded X509 certificates.
'--------------------------------------------------------------------------
'+=========================================================================
'==========================================================================
' Predefined OID Function Names
Public Const CRYPT_OID_ENCODE_OBJECT_FUNC As String = "CryptDllEncodeObject"
Public Const CRYPT_OID_DECODE_OBJECT_FUNC As String = "CryptDllDecodeObject"
Public Const CRYPT_OID_CREATE_COM_OBJECT_FUNC As String = "CryptDllCreateCOMObject"
Public Const CRYPT_OID_VERIFY_REVOCATION_FUNC As String = "CertDllVerifyRevocation"
Public Const CRYPT_OID_VERIFY_CTL_USAGE_FUNC As String = "CertDllVerifyCTLUsage"
Public Const CRYPT_OID_FORMAT_OBJECT_FUNC As String = "CryptDllFormatObject"
' CryptDllEncodeObject has same function signature as CryptEncodeObject.
' CryptDllDecodeObject has same function signature as CryptDecodeObject.
' CryptDllCreateCOMObject has the following signature:
' IN DWORD dwEncodingType,
' IN LPCSTR pszOID,
' IN PCRYPT_DATA_BLOB pEncodedContent,
' IN DWORD dwFlags,
' IN REFIID riid,
' OUT void **ppvObj);
' CertDllVerifyRevocation has the same signature as CertVerifyRevocation
' CertDllVerifyCTLUsage has the same signature as CertVerifyCTLUsage
' Example of a complete OID Function Registry Name:
' HKEY_LOCAL_MACHINE\Software\Microsoft\Cryptography\OID
' Encoding Type 1\CryptDllEncodeObject\1.2.3
'
' The key's "Dll" value contains the name of the Dll.
' The key's "FuncName" value overrides the default function name
Public Const CRYPT_OID_REGPATH As String = "Software\\Microsoft\\Cryptography\\OID"
Public Const CRYPT_OID_REG_ENCODING_TYPE_PREFIX As String = "EncodingType "
Public Const CRYPT_OID_REG_DLL_VALUE_NAME As String = "Dll"
Public Const CRYPT_OID_REG_FUNC_NAME_VALUE_NAME As String = "FuncName"
Public Const CRYPT_OID_REG_FUNC_NAME_VALUE_NAME_A As String = "FuncName"
' OID used for Default OID functions
Public Const CRYPT_DEFAULT_OID As String = "DEFAULT"
Public Const CRYPT_INSTALL_OID_FUNC_BEFORE_FLAG As Long = 1
'+-------------------------------------------------------------------------
' Install a set of callable OID function addresses.
'
' By default the functions are installed at end of the list.
' Set CRYPT_INSTALL_OID_FUNC_BEFORE_FLAG to install at beginning of list.
'
' hModule should be updated with the hModule passed to DllMain to prevent
' the Dll containing the function addresses from being unloaded by
' CryptGetOIDFuncAddress/CryptFreeOIDFunctionAddress. This would be the
' case when the Dll has also regsvr32'ed OID functions via
' CryptRegisterOIDFunction.
'
' DEFAULT functions are installed by setting rgFuncEntry[].pszOID =
' CRYPT_DEFAULT_OID.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Initialize and return handle to the OID function set identified by its
' function name.
'
' If the set already exists, a handle to the existing set is returned.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Search the list of installed functions for an encoding type and OID match.
' If not found, search the registry.
'
' For success, returns TRUE with *ppvFuncAddr updated with the function's
' address and *phFuncAddr updated with the function address's handle.
' The function's handle is AddRef'ed. CryptFreeOIDFunctionAddress needs to
' be called to release it.
'
' For a registry match, the Dll containing the function is loaded.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Get the list of registered default Dll entries for the specified
' function set and encoding type.
'
' The returned list consists of none, one or more null terminated Dll file
' For example: "first.dll" L"\0" L"second.dll" L"\0" L"\0"
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Either: get the first or next installed DEFAULT function OR
' load the Dll containing the DEFAULT function.
'
' If pwszDll is NULL, search the list of installed DEFAULT functions.
' *phFuncAddr must be set to NULL to get the first installed function.
' Successive installed functions are returned by setting *phFuncAddr
' to the hFuncAddr returned by the previous call.
'
' If pwszDll is NULL, the input *phFuncAddr
' is always CryptFreeOIDFunctionAddress'ed by this function, even for
' an error.
'
' If pwszDll isn't NULL, then, attempts to load the Dll and the DEFAULT
' function. *phFuncAddr is ignored upon entry and isn't
' CryptFreeOIDFunctionAddress'ed.
'
' For success, returns TRUE with *ppvFuncAddr updated with the function's
' address and *phFuncAddr updated with the function address's handle.
' The function's handle is AddRef'ed. CryptFreeOIDFunctionAddress needs to
' be called to release it or CryptGetDefaultOIDFunctionAddress can also
' be called for a NULL pwszDll.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Releases the handle AddRef'ed and returned by CryptGetOIDFunctionAddress
' or CryptGetDefaultOIDFunctionAddress.
'
' If a Dll was loaded for the function its unloaded. However, before doing
' the unload, the DllCanUnloadNow function exported by the loaded Dll is
' called. It should return S_FALSE to inhibit the unload or S_TRUE to enable
' the unload. If the Dll doesn't export DllCanUnloadNow, the Dll is unloaded.
'
' DllCanUnloadNow has the following signature:
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Register the Dll containing the function to be called for the specified
' encoding type, function name and OID.
'
' pwszDll may contain environment-variable strings
'
' In addition to registering the DLL, you may override the
' name of the function to be called. For example,
' pszFuncName = "CryptDllEncodeObject",
' pszOverrideFuncName = "MyEncodeXyz".
' This allows a Dll to export multiple OID functions for the same
' function name without needing to interpose its own OID dispatcher function.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Unregister the Dll containing the function to be called for the specified
' encoding type, function name and OID.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Register the Dll containing the default function to be called for the
' specified encoding type and function name.
'
' Unlike CryptRegisterOIDFunction, you can't override the function name
' needing to be exported by the Dll.
'
' The Dll is inserted before the entry specified by dwIndex.
' dwIndex == 0, inserts at the beginning.
' dwIndex == CRYPT_REGISTER_LAST_INDEX, appends at the end.
'
' pwszDll may contain environment-variable strings
'--------------------------------------------------------------------------
Public Const CRYPT_REGISTER_FIRST_INDEX As Long = 0
Public Const CRYPT_REGISTER_LAST_INDEX As Long = &HFFFFFFFF
'+-------------------------------------------------------------------------
' Unregister the Dll containing the default function to be called for
' the specified encoding type and function name.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Set the value for the specified encoding type, function name, OID and
' value name.
'
' See RegSetValueEx for the possible value types.
'
' String types are UNICODE.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Get the value for the specified encoding type, function name, OID and
' value name.
'
' See RegEnumValue for the possible value types.
'
' String types are UNICODE.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Enumerate the OID functions identified by their encoding type,
' function name and OID.
'
' pfnEnumOIDFunc is called for each registry key matching the input
' parameters. Setting dwEncodingType to CRYPT_MATCH_ANY_ENCODING_TYPE matches
' any. Setting pszFuncName or pszOID to NULL matches any.
'
' Set pszOID == CRYPT_DEFAULT_OID to restrict the enumeration to only the
' DEFAULT functions
'
' String types are UNICODE.
'--------------------------------------------------------------------------
Public Const CRYPT_MATCH_ANY_ENCODING_TYPE As Long = &HFFFFFFFF
'+=========================================================================
' Low Level Cryptographic Message Data Structures and APIs
'==========================================================================
Public Const szOID_PKCS_7_DATA As String = "1.2.840.113549.1.7.1"
Public Const szOID_PKCS_7_SIGNED As String = "1.2.840.113549.1.7.2"
Public Const szOID_PKCS_7_ENVELOPED As String = "1.2.840.113549.1.7.3"
Public Const szOID_PKCS_7_SIGNEDANDENVELOPED As String = "1.2.840.113549.1.7.4"
Public Const szOID_PKCS_7_DIGESTED As String = "1.2.840.113549.1.7.5"
Public Const szOID_PKCS_7_ENCRYPTED As String = "1.2.840.113549.1.7.6"
Public Const szOID_PKCS_9_CONTENT_TYPE As String = "1.2.840.113549.1.9.3"
Public Const szOID_PKCS_9_MESSAGE_DIGEST As String = "1.2.840.113549.1.9.4"
'+-------------------------------------------------------------------------
' Message types
'--------------------------------------------------------------------------
Public Const CMSG_DATA As Long = 1
Public Const CMSG_SIGNED As Long = 2
Public Const CMSG_ENVELOPED As Long = 3
Public Const CMSG_SIGNED_AND_ENVELOPED As Long = 4
Public Const CMSG_HASHED As Long = 5
Public Const CMSG_ENCRYPTED As Long = 6
'+-------------------------------------------------------------------------
' Message Type Bit Flags
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' CMSG_DATA: pvMsgEncodeInfo = NULL
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' CMSG_SIGNED
'
' The pCertInfo in the CMSG_SIGNER_ENCODE_INFO provides the Issuer, SerialNumber
' and PublicKeyInfo.Algorithm. The PublicKeyInfo.Algorithm implicitly
' specifies the HashEncryptionAlgorithm to be used.
'
' The hCryptProv and dwKeySpec specify the private key to use. If dwKeySpec
' == 0, then, defaults to AT_SIGNATURE.
'
' pvHashAuxInfo currently isn't used and must be set to NULL.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' CMSG_ENVELOPED
'
' The PCERT_INFO for the rgRecipients provides the Issuer, SerialNumber
' and PublicKeyInfo. The PublicKeyInfo.Algorithm implicitly
' specifies the KeyEncryptionAlgorithm to be used.
'
' The PublicKeyInfo.PublicKey in PCERT_INFO is used to encrypt the content
' encryption key for the recipient.
'
' hCryptProv is used to do the content encryption, recipient key encryption
' and export. The hCryptProv's private keys aren't used.
'
' Note: CAPI currently doesn't support more than one KeyEncryptionAlgorithm
' per provider. This will need to be fixed.
'
' pvEncryptionAuxInfo currently isn't used and must be set to NULL.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' CMSG_SIGNED_AND_ENVELOPED
'
' For PKCS #7, a signed and enveloped message doesn't have the
' signer's authenticated or unauthenticated attributes. Otherwise, a
' combination of the CMSG_SIGNED_ENCODE_INFO and CMSG_ENVELOPED_ENCODE_INFO.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' CMSG_HASHED
'
' hCryptProv is used to do the hash. Doesn't need to use a private key.
'
' If fDetachedHash is set, then, the encoded message doesn't contain
'
' pvHashAuxInfo currently isn't used and must be set to NULL.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' CMSG_ENCRYPTED
'
' The key used to encrypt the message is identified outside of the message
'
' The content input to CryptMsgUpdate has already been encrypted.
'
' pvEncryptionAuxInfo currently isn't used and must be set to NULL.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' This parameter allows messages to be of variable length with streamed
' output.
'
' By default, messages are of a definite length and
' called to get the cryptographically processed content. Until closed,
' the handle keeps a copy of the processed content.
'
' With streamed output, the processed content can be freed as its streamed.
'
' If the length of the content to be updated is known at the time of the
' open, then, ContentLength should be set to that length. Otherwise, it
' should be set to CMSG_INDEFINITE_LENGTH.
'--------------------------------------------------------------------------
Public Const CMSG_INDEFINITE_LENGTH As Long = &HFFFFFFFF
'+-------------------------------------------------------------------------
' Open dwFlags
'--------------------------------------------------------------------------
Public Const CMSG_BARE_CONTENT_FLAG As Long = &H00000001
Public Const CMSG_LENGTH_ONLY_FLAG As Long = &H00000002
Public Const CMSG_DETACHED_FLAG As Long = &H00000004
Public Const CMSG_AUTHENTICATED_ATTRIBUTES_FLAG As Long = &H00000008
Public Const CMSG_CONTENTS_OCTETS_FLAG As Long = &H00000010
'+-------------------------------------------------------------------------
' Open a cryptographic message for encoding
'
' For PKCS #7:
' If the content to be passed to CryptMsgUpdate has already
' from another message encode), then, the CMSG_ENCODED_CONTENT_INFO_FLAG should
' be set in dwFlags. If not set, then, the inner ContentType is Data and
' the input to CryptMsgUpdate is treated as the inner Data type's Content,
' a string of bytes.
' If CMSG_BARE_CONTENT_FLAG is specified for a streamed message,
' the streamed output will not have an outer ContentInfo wrapper. This
' makes it suitable to be streamed into an enclosing message.
'
' The pStreamInfo parameter needs to be set to stream the encoded message
' output.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Calculate the length of an encoded cryptographic message.
'
' Calculates the length of the encoded message given the
' message type, encoding parameters and total length of
' the data to be updated. Note, this might not be the exact length. However,
' it will always be greater than or equal to the actual length.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Open a cryptographic message for decoding
'
' BUGBUG! These comments need to be changed
' For PKCS #7: if the inner ContentType isn't Data, then, the inner
' ContentInfo consisting of both ContentType and Content is output.
' To also enable ContentInfo output for the Data ContentType, then,
' the CMSG_ENCODED_CONTENT_INFO_FLAG should be set
' in dwFlags. If not set, then, only the content portion of the inner
' ContentInfo is output for the Data ContentType.
'
' To only calculate the length of the decoded message, set the
' CMSG_LENGTH_ONLY_FLAG in dwFlags. After the final CryptMsgUpdate get the
' MSG_CONTENT_PARAM. Note, this might not be the exact length. However,
' it will always be greater than or equal to the actual length.
'
' hCryptProv specifies the crypto provider to use for hashing and/or
' decrypting the message. For enveloped messages, hCryptProv also specifies
' the private exchange key to use. For signed messages, hCryptProv is used
' when CryptMsgVerifySigner is called.
'
' For enveloped messages, the pRecipientInfo contains the Issuer and
' SerialNumber identifying the RecipientInfo in the message.
'
' Note, the pRecipientInfo should correspond to the provider's private
' exchange key.
'
' If pRecipientInfo is NULL, then, the message isn't decrypted. To decrypt
' CryptMsgUpdate.
'
' The pStreamInfo parameter needs to be set to stream the decoded content
' output. Note, if pRecipientInfo is NULL, then, the streamed output isn't
' decrypted.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Close a cryptographic message handle
'
' LastError is preserved unless FALSE is returned.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Update the content of a cryptographic message. Depending on how the
' message was opened, the content is either encoded or decoded.
'
' This function is repetitively called to append to the message content.
' fFinal is set to identify the last update. On fFinal, the encode/decode
' is completed. The encoded/decoded content and the decoded parameters
' are valid until the open and all duplicated handles are closed.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Perform a special "control" function after the final CryptMsgUpdate of a
' encoded/decoded cryptographic message.
'
' The dwCtrlType parameter specifies the type of operation to be performed.
'
' The pvCtrlPara definition depends on the dwCtrlType value.
'
' See below for a list of the control operations and their pvCtrlPara
' type definition.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Message control types
'--------------------------------------------------------------------------
Public Const CMSG_CTRL_VERIFY_SIGNATURE As Long = 1
Public Const CMSG_CTRL_DECRYPT As Long = 2
Public Const CMSG_CTRL_VERIFY_HASH As Long = 5
Public Const CMSG_CTRL_ADD_SIGNER As Long = 6
Public Const CMSG_CTRL_DEL_SIGNER As Long = 7
Public Const CMSG_CTRL_ADD_SIGNER_UNAUTH_ATTR As Long = 8
Public Const CMSG_CTRL_DEL_SIGNER_UNAUTH_ATTR As Long = 9
Public Const CMSG_CTRL_ADD_CERT As Long = 10
Public Const CMSG_CTRL_DEL_CERT As Long = 11
Public Const CMSG_CTRL_ADD_CRL As Long = 12
Public Const CMSG_CTRL_DEL_CRL As Long = 13
'+-------------------------------------------------------------------------
' CMSG_CTRL_VERIFY_SIGNATURE
'
' Verify the signature of a SIGNED or SIGNED_AND_ENVELOPED
' message after it has been decoded.
'
' For a SIGNED_AND_ENVELOPED message, called after
' with a NULL pRecipientInfo.
'
' pvCtrlPara points to a CERT_INFO struct.
'
' The CERT_INFO contains the Issuer and SerialNumber identifying
' the Signer of the message. The CERT_INFO also contains the
' PublicKeyInfo
' used to verify the signature. The cryptographic provider specified
' in CryptMsgOpenToDecode is used.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' CMSG_CTRL_DECRYPT
'
' Decrypt an ENVELOPED or SIGNED_AND_ENVELOPED message after it has been
' decoded.
'
' hCryptProv and dwKeySpec specify the private key to use. For dwKeySpec ==
' 0, defaults to AT_KEYEXCHANGE.
'
' dwRecipientIndex is the index of the recipient in the message associated
' with the hCryptProv's private key.
'
' This control function needs to be called, if you don't know the appropriate
' recipient before calling CryptMsgOpenToDecode. After the final
' CryptMsgUpdate, the list of recipients is obtained by iterating through
' CMSG_RECIPIENT_INFO_PARAM. The recipient corresponding to a private
' key owned by the caller is selected and passed to this function to decrypt
' the message.
'
' Note, the message can only be decrypted once.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' CMSG_CTRL_VERIFY_HASH
'
' Verify the hash of a HASHED message after it has been decoded.
'
' Only the hCryptMsg parameter is used, to specify the message whose
' hash is being verified.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' CMSG_CTRL_ADD_SIGNER
'
' Add a signer to a signed-data or signed-and-enveloped-data message.
'
' pvCtrlPara points to a CMSG_SIGNER_ENCODE_INFO.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' CMSG_CTRL_DEL_SIGNER
'
' Remove a signer from a signed-data or signed-and-enveloped-data message.
'
' pvCtrlPara points to a DWORD containing the 0-based index of the
' signer to be removed.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' CMSG_CTRL_ADD_SIGNER_UNAUTH_ATTR
'
' Add an unauthenticated attribute to the SignerInfo of a signed-data or
' signed-and-enveloped-data message.
'
' The unauthenticated attribute is input in the form of an encoded blob.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' CMSG_CTRL_DEL_SIGNER_UNAUTH_ATTR
'
' Delete an unauthenticated attribute from the SignerInfo of a signed-data
' or signed-and-enveloped-data message.
'
' The unauthenticated attribute to be removed is specified by
' a 0-based index.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' CMSG_CTRL_ADD_CERT
'
' Add a certificate to a signed-data or signed-and-enveloped-data message.
'
' pvCtrlPara points to a CRYPT_DATA_BLOB containing the certificate's
' encoded bytes.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' CMSG_CTRL_DEL_CERT
'
' Delete a certificate from a signed-data or signed-and-enveloped-data
' message.
'
' pvCtrlPara points to a DWORD containing the 0-based index of the
' certificate to be removed.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' CMSG_CTRL_ADD_CRL
'
' Add a CRL to a signed-data or signed-and-enveloped-data message.
'
' pvCtrlPara points to a CRYPT_DATA_BLOB containing the CRL's
' encoded bytes.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' CMSG_CTRL_DEL_CRL
'
' Delete a CRL from a signed-data or signed-and-enveloped-data message.
'
' pvCtrlPara points to a DWORD containing the 0-based index of the CRL
' to be removed.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Verify a countersignature, at the SignerInfo level.
' ie. verify that pbSignerInfoCountersignature contains the encrypted
' hash of the encryptedDigest field of pbSignerInfo.
'
' hCryptProv is used to hash the encryptedDigest field of pbSignerInfo.
' The only fields referenced from pciCountersigner are SerialNumber, Issuer,
' and SubjectPublicKeyInfo.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Countersign an already-existing signature in a message
'
' dwIndex is a zero-based index of the SignerInfo to be countersigned.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Output an encoded SignerInfo blob, suitable for use as a countersignature
' attribute in the unauthenticated attributes of a signed-data or
' signed-and-enveloped-data message.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Get a parameter after encoding/decoding a cryptographic message. Called
' after the final CryptMsgUpdate. Only the CMSG_CONTENT_PARAM and
' CMSG_COMPUTED_HASH_PARAM are valid for an encoded message.
'
' For an encoded HASHED message, the CMSG_COMPUTED_HASH_PARAM can be got
' before any CryptMsgUpdates to get its length.
'
' The pvData type definition depends on the dwParamType value.
'
' Elements pointed to by fields in the pvData structure follow the
' structure. Therefore, *pcbData may exceed the size of the structure.
'
' Upon input, if *pcbData == 0, then, *pcbData is updated with the length
' of the data and the pvData parameter is ignored.
'
' Upon return, *pcbData is updated with the length of the data.
'
' The OBJID BLOBs returned in the pvData structures point to
' their still encoded representation. The appropriate functions
' must be called to decode the information.
'
' See below for a list of the parameters to get.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Get parameter types and their corresponding data structure definitions.
'--------------------------------------------------------------------------
Public Const CMSG_TYPE_PARAM As Long = 1
Public Const CMSG_CONTENT_PARAM As Long = 2
Public Const CMSG_BARE_CONTENT_PARAM As Long = 3
Public Const CMSG_INNER_CONTENT_TYPE_PARAM As Long = 4
Public Const CMSG_SIGNER_COUNT_PARAM As Long = 5
Public Const CMSG_SIGNER_INFO_PARAM As Long = 6
Public Const CMSG_SIGNER_CERT_INFO_PARAM As Long = 7
Public Const CMSG_SIGNER_HASH_ALGORITHM_PARAM As Long = 8
Public Const CMSG_SIGNER_AUTH_ATTR_PARAM As Long = 9
Public Const CMSG_SIGNER_UNAUTH_ATTR_PARAM As Long = 10
Public Const CMSG_CERT_COUNT_PARAM As Long = 11
Public Const CMSG_CERT_PARAM As Long = 12
Public Const CMSG_CRL_COUNT_PARAM As Long = 13
Public Const CMSG_CRL_PARAM As Long = 14
Public Const CMSG_ENVELOPE_ALGORITHM_PARAM As Long = 15
Public Const CMSG_RECIPIENT_COUNT_PARAM As Long = 17
Public Const CMSG_RECIPIENT_INDEX_PARAM As Long = 18
Public Const CMSG_RECIPIENT_INFO_PARAM As Long = 19
Public Const CMSG_HASH_ALGORITHM_PARAM As Long = 20
Public Const CMSG_HASH_DATA_PARAM As Long = 21
Public Const CMSG_COMPUTED_HASH_PARAM As Long = 22
Public Const CMSG_ENCRYPT_PARAM As Long = 26
Public Const CMSG_ENCRYPTED_DIGEST As Long = 27
Public Const CMSG_ENCODED_SIGNER As Long = 28
Public Const CMSG_ENCODED_MESSAGE As Long = 29
'+-------------------------------------------------------------------------
' CMSG_TYPE_PARAM
'
' The type of the decoded message.
'
' pvData points to a DWORD
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' CMSG_CONTENT_PARAM
'
' The encoded content of a cryptographic message. Depending on how the
' message was opened, the content is either the whole PKCS#7
' In the decode case, the decrypted content is returned, if enveloped.
' If not enveloped, and if the inner content is of type DATA, the returned
' data is the contents octets of the inner content.
'
' pvData points to the buffer receiving the content bytes
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' CMSG_BARE_CONTENT_PARAM
'
' The encoded content of an encoded cryptographic message, without the
' outer layer of ContentInfo. That is, only the encoding of the
' ContentInfo.content field is returned.
'
' pvData points to the buffer receiving the content bytes
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' CMSG_INNER_CONTENT_TYPE_PARAM
'
' The type of the inner content of a decoded cryptographic message,
' in the form of a NULL-terminated object identifier string
'
' pvData points to the buffer receiving the object identifier string
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' CMSG_SIGNER_COUNT_PARAM
'
' Count of signers in a SIGNED or SIGNED_AND_ENVELOPED message
'
' pvData points to a DWORD
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' CMSG_SIGNER_CERT_INFO_PARAM
'
' To get all the signers, repetitively call CryptMsgGetParam, with
' dwIndex set to 0 .. SignerCount - 1.
'
' pvData points to a CERT_INFO struct.
'
' Only the following fields have been updated in the CERT_INFO struct:
' Issuer and SerialNumber.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' CMSG_SIGNER_INFO_PARAM
'
' To get all the signers, repetitively call CryptMsgGetParam, with
' dwIndex set to 0 .. SignerCount - 1.
'
' pvData points to a CMSG_SIGNER_INFO struct.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' CMSG_SIGNER_HASH_ALGORITHM_PARAM
'
' This parameter specifies the HashAlgorithm that was used for the signer.
'
' Set dwIndex to iterate through all the signers.
'
' pvData points to an CRYPT_ALGORITHM_IDENTIFIER struct.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' CMSG_SIGNER_AUTH_ATTR_PARAM
'
' The authenticated attributes for the signer.
'
' Set dwIndex to iterate through all the signers.
'
' pvData points to a CMSG_ATTR struct.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' CMSG_SIGNER_UNAUTH_ATTR_PARAM
'
' The unauthenticated attributes for the signer.
'
' Set dwIndex to iterate through all the signers.
'
' pvData points to a CMSG_ATTR struct.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' CMSG_CERT_COUNT_PARAM
'
' Count of certificates in a SIGNED or SIGNED_AND_ENVELOPED message.
'
' pvData points to a DWORD
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' CMSG_CERT_PARAM
'
' To get all the certificates, repetitively call CryptMsgGetParam, with
' dwIndex set to 0 .. CertCount - 1.
'
' pvData points to an array of the certificate's encoded bytes.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' CMSG_CRL_COUNT_PARAM
'
' Count of CRLs in a SIGNED or SIGNED_AND_ENVELOPED message.
'
' pvData points to a DWORD
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' CMSG_CRL_PARAM
'
' To get all the CRLs, repetitively call CryptMsgGetParam, with
' dwIndex set to 0 .. CrlCount - 1.
'
' pvData points to an array of the CRL's encoded bytes.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' CMSG_ENVELOPE_ALGORITHM_PARAM
'
' The ContentEncryptionAlgorithm that was used in
' an ENVELOPED or SIGNED_AND_ENVELOPED message.
'
' pvData points to an CRYPT_ALGORITHM_IDENTIFIER struct.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' CMSG_RECIPIENT_COUNT_PARAM
'
' Count of recipients in an ENVELOPED or SIGNED_AND_ENVELOPED message.
'
' pvData points to a DWORD
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' CMSG_RECIPIENT_INDEX_PARAM
'
' Index of the recipient used to decrypt an ENVELOPED or SIGNED_AND_ENVELOPED
' message.
'
' pvData points to a DWORD
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' CMSG_RECIPIENT_INFO_PARAM
'
' To get all the recipients, repetitively call CryptMsgGetParam, with
' dwIndex set to 0 .. RecipientCount - 1.
'
' pvData points to a CERT_INFO struct.
'
' Only the following fields have been updated in the CERT_INFO struct:
' Issuer, SerialNumber and PublicKeyAlgorithm. The PublicKeyAlgorithm
' specifies the KeyEncryptionAlgorithm that was used.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' CMSG_HASH_ALGORITHM_PARAM
'
' The HashAlgorithm in a HASHED message.
'
' pvData points to an CRYPT_ALGORITHM_IDENTIFIER struct.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' CMSG_HASH_DATA_PARAM
'
' The hash in a HASHED message.
'
' pvData points to an array of bytes.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' CMSG_COMPUTED_HASH_PARAM
'
' The computed hash for a HASHED message.
'
' This may be called for either an encoded or decoded message.
' It also may be called before any encoded CryptMsgUpdates to get its length.
'
' pvData points to an array of bytes.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' CMSG_ENCRYPT_PARAM
'
' The ContentEncryptionAlgorithm that was used in an ENCRYPTED message.
'
' pvData points to an CRYPT_ALGORITHM_IDENTIFIER struct.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' CMSG_ENCODED_MESSAGE
'
' The full encoded message. This is useful in the case of a decoded
' signed-and-enveloped-data message which has been countersigned).
'
' pvData points to an array of the message's encoded bytes.
'--------------------------------------------------------------------------
'+=========================================================================
' Certificate Store Data Structures and APIs
'==========================================================================
'+-------------------------------------------------------------------------
' In its most basic implementation, a cert store is simply a
' collection of certificates and/or CRLs. This is the case when
' a cert store is opened with all of its certificates and CRLs
' coming from a PKCS #7 encoded cryptographic message.
'
' Nonetheless, all cert stores have the following properties:
' - A public key may have more than one certificate in the store.
' For example, a private/public key used for signing may have a
' certificate issued for VISA and another issued for
' Mastercard. Also, when a certificate is renewed there might
' be more than one certificate with the same subject and
' issuer.
' - However, each certificate in the store is uniquely
' identified by its Issuer and SerialNumber.
' - There's an issuer of subject certificate relationship. A
' certificate's issuer is found by doing a match of
' pSubjectCert->Issuer with pIssuerCert->Subject.
' The relationship is verified by using
' the issuer's public key to verify the subject certificate's
' signature. Note, there might be X.509 v3 extensions
' to assist in finding the issuer certificate.
' - Since issuer certificates might be renewed, a subject
' certificate might have more than one issuer certificate.
' - There's an issuer of CRL relationship. An
' issuer's CRL is found by doing a match of
' pIssuerCert->Subject with pCrl->Issuer.
' The relationship is verified by using
' the issuer's public key to verify the CRL's
' signature. Note, there might be X.509 v3 extensions
' to assist in finding the CRL.
' - Since some issuers might support the X.509 v3 delta CRL
' extensions, an issuer might have more than one CRL.
' - The store shouldn't have any redundant certificates or
' CRLs. There shouldn't be two certificates with the same
' Issuer and SerialNumber. There shouldn't be two CRLs with
' the same Issuer, ThisUpdate and NextUpdate.
' - The store has NO policy or trust information. No
' certificates are tagged as being "root". Its up to
' SerialNumber) for certificates it trusts.
' - The store might contain bad certificates and/or CRLs.
' The issuer's signature of a subject certificate or CRL may
' not verify. Certificates or CRLs may not satisfy their
' time validity requirements. Certificates may be
' revoked.
'
' In addition to the certificates and CRLs, properties can be
' stored. There are two predefined property IDs for a user
' certificate: CERT_KEY_PROV_HANDLE_PROP_ID and
' CERT_KEY_PROV_INFO_PROP_ID. The CERT_KEY_PROV_HANDLE_PROP_ID
' is a HCRYPTPROV handle to the private key assoicated
' with the certificate. The CERT_KEY_PROV_INFO_PROP_ID contains
' information to be used to call
' CryptAcquireContext and CryptProvSetParam to get a handle
' to the private key associated with the certificate.
'
' There exists two more predefined property IDs for certificates
' and CRLs, CERT_SHA1_HASH_PROP_ID and CERT_MD5_HASH_PROP_ID.
' If these properties don't already exist, then, a hash of the
' hash algorithm, currently, CERT_SHA1_HASH_PROP_ID).
'
' There are additional APIs for creating certificate and CRL
' CertCreateCRLContext).
'
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Certificate context.
'
' A certificate context contains both the encoded and decoded representation
' of a certificate. A certificate context returned by a cert store function
' must be freed by calling the CertFreeCertificateContext function. The
' CertDuplicateCertificateContext function can be called to make a duplicate
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' CRL context.
'
' A CRL context contains both the encoded and decoded representation
' of a CRL. A CRL context returned by a cert store function
' must be freed by calling the CertFreeCRLContext function. The
' CertDuplicateCRLContext function can be called to make a duplicate
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
'
' A CTL context contains both the encoded and decoded representation
' of a CTL. Also contains an opened HCRYPTMSG handle to the decoded
' cryptographic signed message containing the CTL_INFO as its inner content.
' pbCtlContent is the encoded inner content of the signed message.
'
' The CryptMsg APIs can be used to extract additional signer information.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Certificate, CRL and CTL property IDs
'
' See CertSetCertificateContextProperty or CertGetCertificateContextProperty
' for usage information.
'--------------------------------------------------------------------------
Public Const CERT_KEY_PROV_HANDLE_PROP_ID As Long = 1
Public Const CERT_KEY_PROV_INFO_PROP_ID As Long = 2
Public Const CERT_SHA1_HASH_PROP_ID As Long = 3
Public Const CERT_MD5_HASH_PROP_ID As Long = 4
Public Const CERT_KEY_CONTEXT_PROP_ID As Long = 5
Public Const CERT_KEY_SPEC_PROP_ID As Long = 6
Public Const CERT_IE30_RESERVED_PROP_ID As Long = 7
Public Const CERT_PUBKEY_HASH_RESERVED_PROP_ID As Long = 8
Public Const CERT_ENHKEY_USAGE_PROP_ID As Long = 9
Public Const CERT_NEXT_UPDATE_LOCATION_PROP_ID As Long = 10
Public Const CERT_FRIENDLY_NAME_PROP_ID As Long = 11
' Note, 32 - 34 are reserved for the CERT, CRL and CTL file element IDs.
Public Const CERT_FIRST_RESERVED_PROP_ID As Long = 12
Public Const CERT_LAST_RESERVED_PROP_ID As Long = &H00007FFF
Public Const CERT_FIRST_USER_PROP_ID As Long = &H00008000
Public Const CERT_LAST_USER_PROP_ID As Long = &H0000FFFF
'+-------------------------------------------------------------------------
' Cryptographic Key Provider Information
'
' CRYPT_KEY_PROV_INFO defines the CERT_KEY_PROV_INFO_PROP_ID's pvData.
'
' The CRYPT_KEY_PROV_INFO fields are passed to CryptAcquireContext
' to get a HCRYPTPROV handle. The optional CRYPT_KEY_PROV_PARAM fields are
' passed to CryptProvSetParam to further initialize the provider.
'
' The dwKeySpec field identifies the private key to use from the container
' For example, AT_KEYEXCHANGE or AT_SIGNATURE.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' The following flag should be set in the above dwFlags to enable
' CryptAcquireContext is done in the Sign or Decrypt Message functions.
'
' The following define must not collide with any of the
' CryptAcquireContext dwFlag defines.
'--------------------------------------------------------------------------
Public Const CERT_SET_KEY_PROV_HANDLE_PROP_ID As Long = &H00000001
Public Const CERT_SET_KEY_CONTEXT_PROP_ID As Long = &H00000001
'+-------------------------------------------------------------------------
' Certificate Key Context
'
' CERT_KEY_CONTEXT defines the CERT_KEY_CONTEXT_PROP_ID's pvData.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Certificate Store Provider Types
'--------------------------------------------------------------------------
Public Const sz_CERT_STORE_PROV_MEMORY As String = "Memory"
Public Const sz_CERT_STORE_PROV_FILENAME_W As String = "File"
Public Const sz_CERT_STORE_PROV_SYSTEM_W As String = "System"
Public Const sz_CERT_STORE_PROV_PKCS7 As String = "PKCS7"
Public Const sz_CERT_STORE_PROV_SERIALIZED As String = "Serialized"
'+-------------------------------------------------------------------------
' Certificate Store verify/results flags
'--------------------------------------------------------------------------
Public Const CERT_STORE_SIGNATURE_FLAG As Long = &H00000001
Public Const CERT_STORE_TIME_VALIDITY_FLAG As Long = &H00000002
Public Const CERT_STORE_REVOCATION_FLAG As Long = &H00000004
Public Const CERT_STORE_NO_CRL_FLAG As Long = &H00010000
Public Const CERT_STORE_NO_ISSUER_FLAG As Long = &H00020000
'+-------------------------------------------------------------------------
' Certificate Store open/property flags
'--------------------------------------------------------------------------
Public Const CERT_STORE_NO_CRYPT_RELEASE_FLAG As Long = &H00000001
Public Const CERT_STORE_READONLY_FLAG As Long = &H00008000
'+-------------------------------------------------------------------------
' Certificate Store Provider flags are in the HiWord 0xFFFF0000
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Certificate System Store Flag Values
'--------------------------------------------------------------------------
' Location of the system store in the registry:
' HKEY_CURRENT_USER or HKEY_LOCAL_MACHINE
Public Const CERT_SYSTEM_STORE_LOCATION_MASK As Long = &H00030000
Public Const CERT_SYSTEM_STORE_CURRENT_USER As Long = &H00010000
Public Const CERT_SYSTEM_STORE_LOCAL_MACHINE As Long = &H00020000
'+-------------------------------------------------------------------------
' Open the cert store using the specified store provider.
'
' hCryptProv specifies the crypto provider to use to create the hash
' properties or verify the signature of a subject certificate or CRL.
' The store doesn't need to use a private
' key. If the CERT_STORE_NO_CRYPT_RELEASE_FLAG isn't set, hCryptProv is
' CryptReleaseContext'ed on the final CertCloseStore.
'
' Note, if the open fails, hCryptProv is released if it would have been
' released when the store was closed.
'
' If hCryptProv is zero, then, the default provider and container for the
' PROV_RSA_FULL provider type is CryptAcquireContext'ed with
' CRYPT_VERIFYCONTEXT access. The CryptAcquireContext is deferred until
' the first create hash or verify signature. In addition, once acquired,
' the default provider isn't released until process exit when crypt32.dll
' is unloaded. The acquired default provider is shared across all stores
' and threads.
'
' After initializing the store's data structures and optionally acquiring a
' default crypt provider, CertOpenStore calls CryptGetOIDFunctionAddress to
' get the address of the CRYPT_OID_OPEN_STORE_PROV_FUNC specified by
' lpszStoreProvider. Since a store can contain certificates with different
' encoding types, CryptGetOIDFunctionAddress is called with dwEncodingType
' set to 0 and not the dwEncodingType passed to CertOpenStore.
' PFN_CERT_DLL_OPEN_STORE_FUNC specifies the signature of the provider's
' open function. This provider open function is called to load the
' store's certificates and CRLs. Optionally, the provider may return an
' array of functions called before a certificate or CRL is added or deleted
' or has a property that is set.
'
' Use of the dwEncodingType parameter is provider dependent. The type
' definition for pvPara also depends on the provider.
'
' Store providers are installed or registered via
' CryptInstallOIDFunctionAddress or CryptRegisterOIDFunction, where,
' dwEncodingType is 0 and pszFuncName is CRYPT_OID_OPEN_STORE_PROV_FUNC.
'
'
' CERT_STORE_PROV_MSG:
' Gets the certificates and CRLs from the specified cryptographic message.
' dwEncodingType contains the message and certificate encoding types.
' The message's handle is passed in pvPara. Given,
'
' CERT_STORE_PROV_MEMORY
' sz_CERT_STORE_PROV_MEMORY:
' Opens a store without any initial certificates or CRLs. pvPara
' isn't used.
'
' CERT_STORE_PROV_FILE:
' Reads the certificates and CRLs from the specified file. The file's
' handle is passed in pvPara. Given,
'
' For a successful open, the file pointer is advanced past
' the certificates and CRLs and their properties read from the file.
' Note, only expects a serialized store and not a file containing
' either a PKCS #7 signed message or a single encoded certificate.
'
' The hFile isn't closed.
'
' CERT_STORE_PROV_REG:
' Reads the certificates and CRLs from the registry. The registry's
' key handle is passed in pvPara. Given,
'
' The input hKey isn't closed by the provider. Before returning, the
' provider opens/creates "Certificates" and "CRLs" subkeys. These
' subkeys remain open until the store is closed.
'
' If CERT_STORE_READONLY_FLAG is set, then, the registry subkeys are
' RegOpenKey'ed with KEY_READ_ACCESS. Otherwise, the registry subkeys
' are RegCreateKey'ed with KEY_ALL_ACCESS.
'
' This provider returns the array of functions for reading, writing,
' deleting and property setting certificates and CRLs.
' Any changes to the opened store are immediately pushed through to
' the registry. However, if CERT_STORE_READONLY_FLAG is set, then,
' writing, deleting or property setting results in a
'
' Note, all the certificates and CRLs are read from the registry
' when the store is opened. The opened store serves as a write through
' cache. However, the opened store isn't notified of other changes
' made to the registry. Note, RegNotifyChangeKeyValue is supported
' on NT but not supported on Windows95.
'
' CERT_STORE_PROV_PKCS7:
' sz_CERT_STORE_PROV_PKCS7:
' Gets the certificates and CRLs from the encoded PKCS #7 signed message.
' dwEncodingType specifies the message and certificate encoding types.
' The pointer to the encoded message's blob is passed in pvPara. Given,
'
' Note, also supports the IE3.0 special version of a
' PKCS #7 signed message referred to as a "SPC" formatted message.
'
' CERT_STORE_PROV_SERIALIZED:
' sz_CERT_STORE_PROV_SERIALIZED:
' Gets the certificates and CRLs from memory containing a serialized
' store. The pointer to the serialized memory blob is passed in pvPara.
' Given,
'
' CERT_STORE_PROV_FILENAME_A:
' CERT_STORE_PROV_FILENAME_W:
' CERT_STORE_PROV_FILENAME:
' sz_CERT_STORE_PROV_FILENAME_W:
' sz_CERT_STORE_PROV_FILENAME:
' Opens the file and first attempts to read as a serialized store. Then,
' as a PKCS #7 signed message. Finally, as a single encoded certificate.
' The filename is passed in pvPara. The filename is UNICODE for the
' "_W" provider and ASCII for the "_A" provider. For "_W": given,
' For "_A": given,
'
'
' Note, also supports the reading of the IE3.0 special version of a
' PKCS #7 signed message file referred to as a "SPC" formatted file.
'
' CERT_STORE_PROV_SYSTEM_A:
' CERT_STORE_PROV_SYSTEM_W:
' CERT_STORE_PROV_SYSTEM:
' sz_CERT_STORE_PROV_SYSTEM_W:
' sz_CERT_STORE_PROV_SYSTEM:
' Opens the specified "system" store. Currently, all the system
' stores are stored in the registry. The upper word of the dwFlags
' parameter is used to specify the location of the system store. It
' should be set to either CERT_SYSTEM_STORE_CURRENT_USER for
' HKEY_CURRENT_USER or CERT_SYSTEM_STORE_LOCAL_MACHINE for
' HKEY_LOCAL_MACHINE.
'
' After opening the registry key associated with the system name,
' the CERT_STORE_PROV_REG provider is called to complete the open.
'
' The system store name is passed in pvPara. The name is UNICODE for the
' "_W" provider and ASCII for the "_A" provider. For "_W": given,
' For "_A": given,
'
'
' If CERT_STORE_READONLY_FLAG is set, then, the registry is
' RegOpenKey'ed with KEY_READ_ACCESS. Otherwise, the registry is
' RegCreateKey'ed with KEY_ALL_ACCESS.
'
' The "root" store is treated differently from the other system
' stores. Before a certificate is added to or deleted from the "root"
' store, a pop up message box is displayed. The certificate's subject,
' issuer, serial number, time validity, sha1 and md5 thumbprints are
' displayed. The user is given the option to do the add or delete.
' If they don't allow the operation, LastError is set to E_ACCESSDENIED.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' OID Installable Certificate Store Provider Data Structures
'--------------------------------------------------------------------------
' Handle returned by the store provider when opened.
' Store Provider OID function's pszFuncName.
Public Const CRYPT_OID_OPEN_STORE_PROV_FUNC As String = "CertDllOpenStoreProv"
' Note, the Store Provider OID function's dwEncodingType is always 0.
' The following information is returned by the provider when opened. Its
' zeroed with cbSize set before the provider is called. If the provider
' doesn't need to be called again after the open it doesn't need to
' make any updates to the CERT_STORE_PROV_INFO.
' Definition of the store provider's open function.
'
' *pStoreProvInfo has been zeroed before the call.
'
' Note, pStoreProvInfo->cStoreProvFunc should be set last. Once set,
' all subsequent store calls, such as CertAddSerializedElementToStore will
' call the appropriate provider callback function.
' Indices into the store provider's array of callback functions.
'
' The provider can implement any subset of the following functions. It
' sets pStoreProvInfo->cStoreProvFunc to the last index + 1 and any
' preceding not implemented functions to NULL.
Public Const CERT_STORE_PROV_CLOSE_FUNC As Long = 0
Public Const CERT_STORE_PROV_READ_CERT_FUNC As Long = 1
Public Const CERT_STORE_PROV_WRITE_CERT_FUNC As Long = 2
Public Const CERT_STORE_PROV_DELETE_CERT_FUNC As Long = 3
Public Const CERT_STORE_PROV_SET_CERT_PROPERTY_FUNC As Long = 4
Public Const CERT_STORE_PROV_READ_CRL_FUNC As Long = 5
Public Const CERT_STORE_PROV_WRITE_CRL_FUNC As Long = 6
Public Const CERT_STORE_PROV_DELETE_CRL_FUNC As Long = 7
Public Const CERT_STORE_PROV_SET_CRL_PROPERTY_FUNC As Long = 8
Public Const CERT_STORE_PROV_READ_CTL_FUNC As Long = 9
Public Const CERT_STORE_PROV_WRITE_CTL_FUNC As Long = 10
Public Const CERT_STORE_PROV_DELETE_CTL_FUNC As Long = 11
Public Const CERT_STORE_PROV_SET_CTL_PROPERTY_FUNC As Long = 12
' Called by CertCloseStore when the store's reference count is
' decremented to 0.
' Currently not called directly by the store APIs. However, may be exported
' to support other providers based on it.
'
' Reads the provider's copy of the certificate context. If it exists,
' creates a new certificate context.
Public Const CERT_STORE_PROV_WRITE_ADD_FLAG As Long = &H1
' Called by CertAddEncodedCertificateToStore,
' CertAddCertificateContextToStore or CertAddSerializedElementToStore before
' adding to the store. The CERT_STORE_PROV_WRITE_ADD_FLAG is set. In
' addition to the encoded certificate, the added pCertContext might also
' have properties.
'
' Returns TRUE if its OK to update the the store.
' Called by CertDeleteCertificateFromStore before deleting from the
' store.
'
' Returns TRUE if its OK to delete from the store.
' Called by CertSetCertificateContextProperty before setting the
' certificate's property. Also called by CertGetCertificateContextProperty,
' when getting a hash property that needs to be created and then persisted
' via the set.
'
' Upon input, the property hasn't been set for the pCertContext parameter.
'
' Returns TRUE if its OK to set the property.
' Currently not called directly by the store APIs. However, may be exported
' to support other providers based on it.
'
' Reads the provider's copy of the CRL context. If it exists,
' creates a new CRL context.
' Called by CertAddEncodedCRLToStore,
' CertAddCRLContextToStore or CertAddSerializedElementToStore before
' adding to the store. The CERT_STORE_PROV_WRITE_ADD_FLAG is set. In
' addition to the encoded CRL, the added pCertContext might also
' have properties.
'
' Returns TRUE if its OK to update the the store.
' Called by CertDeleteCRLFromStore before deleting from the store.
'
' Returns TRUE if its OK to delete from the store.
' Called by CertSetCRLContextProperty before setting the
' CRL's property. Also called by CertGetCRLContextProperty,
' when getting a hash property that needs to be created and then persisted
' via the set.
'
' Upon input, the property hasn't been set for the pCrlContext parameter.
'
' Returns TRUE if its OK to set the property.
' Currently not called directly by the store APIs. However, may be exported
' to support other providers based on it.
'
' Reads the provider's copy of the CTL context. If it exists,
' creates a new CTL context.
' Called by CertAddEncodedCTLToStore,
' CertAddCTLContextToStore or CertAddSerializedElementToStore before
' adding to the store. The CERT_STORE_PROV_WRITE_ADD_FLAG is set. In
' addition to the encoded CTL, the added pCertContext might also
' have properties.
'
' Returns TRUE if its OK to update the the store.
' Called by CertDeleteCTLFromStore before deleting from the store.
'
' Returns TRUE if its OK to delete from the store.
' Called by CertSetCTLContextProperty before setting the
' CTL's property. Also called by CertGetCTLContextProperty,
' when getting a hash property that needs to be created and then persisted
' via the set.
'
' Upon input, the property hasn't been set for the pCtlContext parameter.
'
' Returns TRUE if its OK to set the property.
'+-------------------------------------------------------------------------
' Duplicate a cert store handle
'--------------------------------------------------------------------------
Public Const CERT_STORE_SAVE_AS_STORE As Long = 1
Public Const CERT_STORE_SAVE_AS_PKCS7 As Long = 2
Public Const CERT_STORE_SAVE_TO_FILE As Long = 1
Public Const CERT_STORE_SAVE_TO_MEMORY As Long = 2
Public Const CERT_STORE_SAVE_TO_FILENAME_A As Long = 3
Public Const CERT_STORE_SAVE_TO_FILENAME_W As Long = 4
'+-------------------------------------------------------------------------
' Save the cert store. Extended version with lots of options.
'
' According to the dwSaveAs parameter, the store can be saved as a
' addition to encoded certificates, CRLs and CTLs or the store can be saved
' include the properties or CTLs.
'
' CERT_KEY_PROV_HANDLE_PROP_ID or CERT_KEY_SPEC_PROP_ID) isn't saved into
' a serialized store.
'
' For CERT_STORE_SAVE_AS_PKCS7, the dwEncodingType specifies the message
' encoding type. The dwEncodingType parameter isn't used for
' CERT_STORE_SAVE_AS_STORE.
'
' The dwFlags parameter currently isn't used and should be set to 0.
'
' The dwSaveTo and pvSaveToPara parameters specify where to save the
' store as follows:
' CERT_STORE_SAVE_TO_FILE:
' Saves to the specified file. The file's handle is passed in
' pvSaveToPara. Given,
'
' For a successful save, the file pointer is positioned after the
' last write.
'
' CERT_STORE_SAVE_TO_MEMORY:
' Saves to the specified memory blob. The pointer to
' the memory blob is passed in pvSaveToPara. Given,
' Upon entry, the SaveBlob's pbData and cbData need to be initialized.
' Upon return, cbData is updated with the actual length.
' For a length only calculation, pbData should be set to NULL. If
' pbData is non-NULL and cbData isn't large enough, FALSE is returned
' with a last error of ERRROR_MORE_DATA.
'
' CERT_STORE_SAVE_TO_FILENAME_A:
' CERT_STORE_SAVE_TO_FILENAME_W:
' CERT_STORE_SAVE_TO_FILENAME:
' Opens the file and saves to it. The filename is passed in pvSaveToPara.
' The filename is UNICODE for the "_W" option and ASCII for the "_A"
' option. For "_W": given,
' For "_A": given,
'
'
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Certificate Store close flags
'--------------------------------------------------------------------------
Public Const CERT_CLOSE_STORE_FORCE_FLAG As Long = &H00000001
Public Const CERT_CLOSE_STORE_CHECK_FLAG As Long = &H00000002
'+-------------------------------------------------------------------------
' Close a cert store handle.
'
' There needs to be a corresponding close for each open and duplicate.
'
' Even on the final close, the cert store isn't freed until all of its
' certificate and CRL contexts have also been freed.
'
' On the final close, the hCryptProv passed to CertStoreOpen is
' CryptReleaseContext'ed.
'
' To force the closure of the store with all of its memory freed, set the
' CERT_STORE_CLOSE_FORCE_FLAG. This flag should be set when the caller does
' its own reference counting and wants everything to vanish.
'
' To check if all the store's certificates and CRLs have been freed and that
' this is the last CertCloseStore, set the CERT_CLOSE_STORE_CHECK_FLAG. If
' set and certs, CRLs or stores still need to be freed/closed, FALSE is
' returned with LastError set to CRYPT_E_PENDING_CLOSE. Note, for FALSE,
' the store is still closed. This is a diagnostic flag.
'
' LastError is preserved unless CERT_CLOSE_STORE_CHECK_FLAG is set and FALSE
' is returned.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Get the subject certificate context uniquely identified by its Issuer and
' SerialNumber from the store.
'
' If the certificate isn't found, NULL is returned. Otherwise, a pointer to
' a read only CERT_CONTEXT is returned. CERT_CONTEXT must be freed by calling
' CertFreeCertificateContext. CertDuplicateCertificateContext can be called to make a
' duplicate.
'
' The returned certificate might not be valid. Normally, it would be
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Enumerate the certificate contexts in the store.
'
' If a certificate isn't found, NULL is returned.
' Otherwise, a pointer to a read only CERT_CONTEXT is returned. CERT_CONTEXT
' must be freed by calling CertFreeCertificateContext or is freed when passed as the
' pPrevCertContext on a subsequent call. CertDuplicateCertificateContext
' can be called to make a duplicate.
'
' pPrevCertContext MUST BE NULL to enumerate the first
' certificate in the store. Successive certificates are enumerated by setting
' pPrevCertContext to the CERT_CONTEXT returned by a previous call.
'
' NOTE: a NON-NULL pPrevCertContext is always CertFreeCertificateContext'ed by
' this function, even for an error.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Find the first or next certificate context in the store.
'
' The certificate is found according to the dwFindType and its pvFindPara.
' See below for a list of the find types and its parameters.
'
' Currently dwFindFlags is only used for CERT_FIND_SUBJECT_ATTR,
' CERT_FIND_ISSUER_ATTR or CERT_FIND_CTL_USAGE. Otherwise, must be set to 0.
'
' Usage of dwCertEncodingType depends on the dwFindType.
'
' If the first or next certificate isn't found, NULL is returned.
' Otherwise, a pointer to a read only CERT_CONTEXT is returned. CERT_CONTEXT
' must be freed by calling CertFreeCertificateContext or is freed when passed as the
' pPrevCertContext on a subsequent call. CertDuplicateCertificateContext
' can be called to make a duplicate.
'
' pPrevCertContext MUST BE NULL on the first
' call to find the certificate. To find the next certificate, the
' pPrevCertContext is set to the CERT_CONTEXT returned by a previous call.
'
' NOTE: a NON-NULL pPrevCertContext is always CertFreeCertificateContext'ed by
' this function, even for an error.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Certificate comparison functions
'--------------------------------------------------------------------------
Public Const CERT_COMPARE_MASK As Long = &HFFFF
Public Const CERT_COMPARE_SHIFT As Long = 16
Public Const CERT_COMPARE_ANY As Long = 0
Public Const CERT_COMPARE_SHA1_HASH As Long = 1
Public Const CERT_COMPARE_NAME As Long = 2
Public Const CERT_COMPARE_ATTR As Long = 3
Public Const CERT_COMPARE_MD5_HASH As Long = 4
Public Const CERT_COMPARE_PROPERTY As Long = 5
Public Const CERT_COMPARE_PUBLIC_KEY As Long = 6
Public Const CERT_COMPARE_NAME_STR_A As Long = 7
Public Const CERT_COMPARE_NAME_STR_W As Long = 8
Public Const CERT_COMPARE_KEY_SPEC As Long = 9
Public Const CERT_COMPARE_ENHKEY_USAGE As Long = 10
'+-------------------------------------------------------------------------
' dwFindType
'
' The dwFindType definition consists of two components:
' - comparison function
' - certificate information flag
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' CERT_FIND_ANY
'
' Find any certificate.
'
' pvFindPara isn't used.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' CERT_FIND_HASH
'
' Find a certificate with the specified hash.
'
' pvFindPara points to a CRYPT_HASH_BLOB.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' CERT_FIND_PROPERTY
'
' Find a certificate having the specified property.
'
' pvFindPara points to a DWORD containing the PROP_ID
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' CERT_FIND_PUBLIC_KEY
'
' Find a certificate matching the specified public key.
'
' pvFindPara points to a CERT_PUBLIC_KEY_INFO containing the public key
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' CERT_FIND_SUBJECT_NAME
' CERT_FIND_ISSUER_NAME
'
' Find a certificate with the specified subject/issuer name. Does an exact
' match of the entire name.
'
' Restricts search to certificates matching the dwCertEncodingType.
'
' pvFindPara points to a CERT_NAME_BLOB.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' CERT_FIND_SUBJECT_ATTR
' CERT_FIND_ISSUER_ATTR
'
' Find a certificate with the specified subject/issuer attributes.
'
' Compares the attributes in the subject/issuer name with the
' pvFindPara. The comparison iterates through the CERT_RDN attributes and looks
' for an attribute match in any of the subject/issuer's RDNs.
'
' The CERT_RDN_ATTR fields can have the following special values:
' pszObjId == NULL - ignore the attribute object identifier
' dwValueType == RDN_ANY_TYPE - ignore the value type
' Value.pbData == NULL - match any value
'
' Currently only an exact, case sensitive match is supported.
'
' CERT_UNICODE_IS_RDN_ATTRS_FLAG should be set in dwFindFlags if the RDN was
' initialized with unicode strings as for
'
' Restricts search to certificates matching the dwCertEncodingType.
'
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' CERT_FIND_SUBJECT_STR_A
' CERT_FIND_SUBJECT_STR_W | CERT_FIND_SUBJECT_STR
' CERT_FIND_ISSUER_STR_A
' CERT_FIND_ISSUER_STR_W | CERT_FIND_ISSUER_STR
'
' Find a certificate containing the specified subject/issuer name string.
'
' First, the certificate's subject/issuer is converted to a name string
' case insensitive substring within string match is performed.
'
' Restricts search to certificates matching the dwCertEncodingType.
'
' For *_STR_A, pvFindPara points to a null terminated character string.
' For *_STR_W, pvFindPara points to a null terminated wide character string.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' CERT_FIND_KEY_SPEC
'
' Find a certificate having a CERT_KEY_SPEC_PROP_ID property matching
' the specified KeySpec.
'
' pvFindPara points to a DWORD containing the KeySpec.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' CERT_FIND_ENHKEY_USAGE
'
' Find a certificate having the szOID_ENHANCED_KEY_USAGE extension or
' the CERT_ENHKEY_USAGE_PROP_ID and matching the specified pszUsageIdentifers.
'
' pvFindPara points to a CERT_ENHKEY_USAGE data structure. If pvFindPara
' is NULL or CERT_ENHKEY_USAGE's cUsageIdentifier is 0, then, matches any
' certificate having enhanced key usage.
'
' The CERT_FIND_OPTIONAL_ENHKEY_USAGE_FLAG can be set in dwFindFlags to
' also match a certificate without either the extension or property.
'
' If CERT_FIND_NO_ENHKEY_USAGE_FLAG is set in dwFindFlags, finds
' certificates without the key usage extension or property. Setting this
' flag takes precedence over pvFindPara being NULL.
'
' If the CERT_FIND_EXT_ONLY_ENHKEY_USAGE_FLAG is set, then, only does a match
' using the extension. If pvFindPara is NULL or cUsageIdentifier is set to
' 0, finds certificates having the extension. If
' CERT_FIND_OPTIONAL_ENHKEY_USAGE_FLAG is set, also matches a certificate
' without the extension. If CERT_FIND_NO_ENHKEY_USAGE_FLAG is set, finds
' certificates without the extension.
'
' If the CERT_FIND_EXT_PROP_ENHKEY_USAGE_FLAG is set, then, only does a match
' using the property. If pvFindPara is NULL or cUsageIdentifier is set to
' 0, finds certificates having the property. If
' CERT_FIND_OPTIONAL_ENHKEY_USAGE_FLAG is set, also matches a certificate
' without the property. If CERT_FIND_NO_ENHKEY_USAGE_FLAG is set, finds
' certificates without the property.
'--------------------------------------------------------------------------
Public Const CERT_FIND_OPTIONAL_ENHKEY_USAGE_FLAG As Long = &H1
Public Const CERT_FIND_EXT_ONLY_ENHKEY_USAGE_FLAG As Long = &H2
Public Const CERT_FIND_PROP_ONLY_ENHKEY_USAGE_FLAG As Long = &H4
Public Const CERT_FIND_NO_ENHKEY_USAGE_FLAG As Long = &H8
'+-------------------------------------------------------------------------
' Get the certificate context from the store for the first or next issuer
' of the specified subject certificate. Perform the enabled
' using the returned issuer certificate.)
'
' If the first or next issuer certificate isn't found, NULL is returned.
' Otherwise, a pointer to a read only CERT_CONTEXT is returned. CERT_CONTEXT
' must be freed by calling CertFreeCertificateContext or is freed when passed as the
' pPrevIssuerContext on a subsequent call. CertDuplicateCertificateContext
' can be called to make a duplicate.
'
' For a self signed subject certificate, NULL is returned with LastError set
' to CERT_STORE_SELF_SIGNED. The enabled verification checks are still done.
'
' The pSubjectContext may have been obtained from this store, another store
' or created by the caller application. When created by the caller, the
' CertCreateCertificateContext function must have been called.
'
' An issuer may have multiple certificates. This may occur when the validity
' period is about to change. pPrevIssuerContext MUST BE NULL on the first
' call to get the issuer. To get the next certificate for the issuer, the
' pPrevIssuerContext is set to the CERT_CONTEXT returned by a previous call.
'
' NOTE: a NON-NULL pPrevIssuerContext is always CertFreeCertificateContext'ed by
' this function, even for an error.
'
' The following flags can be set in *pdwFlags to enable verification checks
' on the subject certificate context:
' CERT_STORE_SIGNATURE_FLAG - use the public key in the returned
' issuer certificate to verify the
' signature on the subject certificate.
' Note, if pSubjectContext->hCertStore ==
' hCertStore, the store provider might
' be able to eliminate a redo of
' the signature verify.
' CERT_STORE_TIME_VALIDITY_FLAG - get the current time and verify that
' its within the subject certificate's
' validity period
' CERT_STORE_REVOCATION_FLAG - check if the subject certificate is on
' the issuer's revocation list
'
' If an enabled verification check fails, then, its flag is set upon return.
' If CERT_STORE_REVOCATION_FLAG was enabled and the issuer doesn't have a
' CRL in the store, then, CERT_STORE_NO_CRL_FLAG is set in addition to
' the CERT_STORE_REVOCATION_FLAG.
'
' If CERT_STORE_SIGNATURE_FLAG or CERT_STORE_REVOCATION_FLAG is set, then,
' CERT_STORE_NO_ISSUER_FLAG is set if it doesn't have an issuer certificate
' in the store.
'
' For a verification check failure, a pointer to the issuer's CERT_CONTEXT
' is still returned and SetLastError isn't updated.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Perform the enabled verification checks on the subject certificate
' using the issuer. Same checks and flags definitions as for the above
' CertGetIssuerCertificateFromStore.
'
' If you are only checking CERT_STORE_TIME_VALIDITY_FLAG, then, the
' issuer can be NULL.
'
' For a verification check failure, SUCCESS is still returned.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Duplicate a certificate context
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Create a certificate context from the encoded certificate. The created
' context isn't put in a store.
'
' Makes a copy of the encoded certificate in the created context.
'
' If unable to decode and create the certificate context, NULL is returned.
' Otherwise, a pointer to a read only CERT_CONTEXT is returned.
' CERT_CONTEXT must be freed by calling CertFreeCertificateContext.
' CertDuplicateCertificateContext can be called to make a duplicate.
'
' CertSetCertificateContextProperty and CertGetCertificateContextProperty can be called
' to store properties for the certificate.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Free a certificate context
'
' There needs to be a corresponding free for each context obtained by a
' get, find, duplicate or create.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Set the property for the specified certificate context.
'
' The type definition for pvData depends on the dwPropId value. There are
' five predefined types:
' CERT_KEY_PROV_HANDLE_PROP_ID - a HCRYPTPROV for the certificate's
' private key is passed in pvData. Updates the hCryptProv field
' of the CERT_KEY_CONTEXT_PROP_ID. If the CERT_KEY_CONTEXT_PROP_ID
' doesn't exist, its created with all the other fields zeroed out. If
' CERT_STORE_NO_CRYPT_RELEASE_FLAG isn't set, HCRYPTPROV is implicitly
' released when either the property is set to NULL or on the final
' free of the CertContext.
'
' CERT_KEY_PROV_INFO_PROP_ID - a PCRYPT_KEY_PROV_INFO for the certificate's
' private key is passed in pvData.
'
' CERT_SHA1_HASH_PROP_ID -
' CERT_MD5_HASH_PROP_ID - normally, either property is implicitly
' set by doing a CertGetCertificateContextProperty. pvData points to a
' CRYPT_HASH_BLOB.
'
' CERT_KEY_CONTEXT_PROP_ID - a PCERT_KEY_CONTEXT for the certificate's
' private key is passed in pvData. The CERT_KEY_CONTEXT contains both the
' hCryptProv and dwKeySpec for the private key.
' See the CERT_KEY_PROV_HANDLE_PROP_ID for more information about
' the hCryptProv field and dwFlags settings. Note, more fields may
' be added for this property. The cbSize field value will be adjusted
' accordingly.
'
' CERT_KEY_SPEC_PROP_ID - the dwKeySpec for the private key. pvData
' points to a DWORD containing the KeySpec
'
' CERT_ENHKEY_USAGE_PROP_ID - enhanced key usage definition for the
' certificate. pvData points to a CRYPT_DATA_BLOB containing an
'
' CERT_NEXT_UPDATE_LOCATION_PROP_ID - location of the next update.
' Currently only applicable to CTLs. pvData points to a CRYPT_DATA_BLOB
'
' CERT_FRIENDLY_NAME_PROP_ID - friendly name for the cert, CRL or CTL.
' pvData points to a CRYPT_DATA_BLOB. pbData is a pointer to a NULL
' terminated unicode, wide character string.
'
' For all the other PROP_IDs: an encoded PCRYPT_DATA_BLOB is passed in pvData.
'
' If the property already exists, then, the old value is deleted and silently
' replaced. Setting, pvData to NULL, deletes the property.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Get the property for the specified certificate context.
'
' For CERT_KEY_PROV_HANDLE_PROP_ID, pvData points to a HCRYPTPROV.
'
' For CERT_KEY_PROV_INFO_PROP_ID, pvData points to a CRYPT_KEY_PROV_INFO structure.
' Elements pointed to by fields in the pvData structure follow the
' structure. Therefore, *pcbData may exceed the size of the structure.
'
' For CERT_KEY_CONTEXT_PROP_ID, pvData points to a CERT_KEY_CONTEXT structure.
'
' For CERT_KEY_SPEC_PROP_ID, pvData points to a DWORD containing the KeySpec.
' If the CERT_KEY_CONTEXT_PROP_ID exists, the KeySpec is obtained from there.
' Otherwise, if the CERT_KEY_PROV_INFO_PROP_ID exists, its the source
' of the KeySpec.
'
' For CERT_SHA1_HASH_PROP_ID or CERT_MD5_HASH_PROP_ID, if the hash
' and then set. pvData points to the computed hash. Normally, the length
' is 20 bytes for SHA and 16 for MD5.
'
' For all other PROP_IDs, pvData points to an encoded array of bytes.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Enumerate the properties for the specified certificate context.
'
' To get the first property, set dwPropId to 0. The ID of the first
' property is returned. To get the next property, set dwPropId to the
' ID returned by the last call. To enumerate all the properties continue
' until 0 is returned.
'
' CertGetCertificateContextProperty is called to get the property's data.
'
' Note, since, the CERT_KEY_PROV_HANDLE_PROP_ID and CERT_KEY_SPEC_PROP_ID
' properties are stored as fields in the CERT_KEY_CONTEXT_PROP_ID
' property, they aren't enumerated individually.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Get the first or next CRL context from the store for the specified
' issuer certificate. Perform the enabled verification checks on the CRL.
'
' If the first or next CRL isn't found, NULL is returned.
' Otherwise, a pointer to a read only CRL_CONTEXT is returned. CRL_CONTEXT
' must be freed by calling CertFreeCRLContext. However, the free must be
' pPrevCrlContext on a subsequent call. CertDuplicateCRLContext
' can be called to make a duplicate.
'
' The pIssuerContext may have been obtained from this store, another store
' or created by the caller application. When created by the caller, the
' CertCreateCertificateContext function must have been called.
'
' If pIssuerContext == NULL, finds all the CRLs in the store.
'
' An issuer may have multiple CRLs. For example, it generates delta CRLs
' using a X.509 v3 extension. pPrevCrlContext MUST BE NULL on the first
' call to get the CRL. To get the next CRL for the issuer, the
' pPrevCrlContext is set to the CRL_CONTEXT returned by a previous call.
'
' NOTE: a NON-NULL pPrevCrlContext is always CertFreeCRLContext'ed by
' this function, even for an error.
'
' The following flags can be set in *pdwFlags to enable verification checks
' on the returned CRL:
' CERT_STORE_SIGNATURE_FLAG - use the public key in the
' issuer's certificate to verify the
' signature on the returned CRL.
' Note, if pIssuerContext->hCertStore ==
' hCertStore, the store provider might
' be able to eliminate a redo of
' the signature verify.
' CERT_STORE_TIME_VALIDITY_FLAG - get the current time and verify that
' its within the CRL's ThisUpdate and
' NextUpdate validity period.
'
' If an enabled verification check fails, then, its flag is set upon return.
'
' If pIssuerContext == NULL, then, an enabled CERT_STORE_SIGNATURE_FLAG
' always fails and the CERT_STORE_NO_ISSUER_FLAG is also set.
'
' For a verification check failure, a pointer to the first or next
' CRL_CONTEXT is still returned and SetLastError isn't updated.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Duplicate a CRL context
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Create a CRL context from the encoded CRL. The created
' context isn't put in a store.
'
' Makes a copy of the encoded CRL in the created context.
'
' If unable to decode and create the CRL context, NULL is returned.
' Otherwise, a pointer to a read only CRL_CONTEXT is returned.
' CRL_CONTEXT must be freed by calling CertFreeCRLContext.
' CertDuplicateCRLContext can be called to make a duplicate.
'
' CertSetCRLContextProperty and CertGetCRLContextProperty can be called
' to store properties for the CRL.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Free a CRL context
'
' There needs to be a corresponding free for each context obtained by a
' get, duplicate or create.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Set the property for the specified CRL context.
'
' Same Property Ids and semantics as CertSetCertificateContextProperty.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Get the property for the specified CRL context.
'
' Same Property Ids and semantics as CertGetCertificateContextProperty.
'
' CERT_SHA1_HASH_PROP_ID or CERT_MD5_HASH_PROP_ID is the predefined
' property of most interest.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Enumerate the properties for the specified CRL context.
'
' To get the first property, set dwPropId to 0. The ID of the first
' property is returned. To get the next property, set dwPropId to the
' ID returned by the last call. To enumerate all the properties continue
' until 0 is returned.
'
' CertGetCRLContextProperty is called to get the property's data.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Add certificate/CRL, encoded, context or element disposition values.
'--------------------------------------------------------------------------
Public Const CERT_STORE_ADD_NEW As Long = 1
Public Const CERT_STORE_ADD_USE_EXISTING As Long = 2
Public Const CERT_STORE_ADD_REPLACE_EXISTING As Long = 3
Public Const CERT_STORE_ADD_ALWAYS As Long = 4
'+-------------------------------------------------------------------------
' Add the encoded certificate to the store according to the specified
' disposition action.
'
' Makes a copy of the encoded certificate before adding to the store.
'
' dwAddDispostion specifies the action to take if the certificate
' already exists in the store. This parameter must be one of the following
' values:
' CERT_STORE_ADD_NEW
' Fails if the certificate already exists in the store. LastError
' is set to CRYPT_E_EXISTS.
' CERT_STORE_ADD_USE_EXISTING
' If the certifcate already exists, then, its used and if ppCertContext
' is non-NULL, the existing context is duplicated.
' CERT_STORE_ADD_REPLACE_EXISTING
' If the certificate already exists, then, the existing certificate
' context is deleted before creating and adding the new context.
' CERT_STORE_ADD_ALWAYS
' No check is made to see if the certificate already exists. A
' new certificate context is always created. This may lead to
' duplicates in the store.
'
' CertGetSubjectCertificateFromStore is called to determine if the
' certificate already exists in the store.
'
' ppCertContext can be NULL, indicating the caller isn't interested
' in getting the CERT_CONTEXT of the added or existing certificate.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Add the certificate context to the store according to the specified
' disposition action.
'
' In addition to the encoded certificate, the context's properties are
' CERT_KEY_PROV_HANDLE_PROP_ID or CERT_KEY_SPEC_PROP_ID) isn't copied.
'
' Makes a copy of the certificate context before adding to the store.
'
' dwAddDispostion specifies the action to take if the certificate
' already exists in the store. This parameter must be one of the following
' values:
' CERT_STORE_ADD_NEW
' Fails if the certificate already exists in the store. LastError
' is set to CRYPT_E_EXISTS.
' CERT_STORE_ADD_USE_EXISTING
' If the certifcate already exists, then, its used and if ppStoreContext
' is non-NULL, the existing context is duplicated. Iterates
' through pCertContext's properties and only copies the properties
' that don't already exist. The SHA1 and MD5 hash properties aren't
' copied.
' CERT_STORE_ADD_REPLACE_EXISTING
' If the certificate already exists, then, the existing certificate
' context is deleted before creating and adding a new context.
' Properties are copied before doing the add.
' CERT_STORE_ADD_ALWAYS
' No check is made to see if the certificate already exists. A
' new certificate context is always created and added. This may lead to
' duplicates in the store. Properties are
' copied before doing the add.
'
' CertGetSubjectCertificateFromStore is called to determine if the
' certificate already exists in the store.
'
' ppStoreContext can be NULL, indicating the caller isn't interested
' in getting the CERT_CONTEXT of the added or existing certificate.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Certificate Store Context Types
'--------------------------------------------------------------------------
Public Const CERT_STORE_CERTIFICATE_CONTEXT As Long = 1
Public Const CERT_STORE_CRL_CONTEXT As Long = 2
Public Const CERT_STORE_CTL_CONTEXT As Long = 3
'+-------------------------------------------------------------------------
' Certificate Store Context Bit Flags
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Add the serialized certificate or CRL element to the store.
'
' The serialized element contains the encoded certificate, CRL or CTL and
' its properties, such as, CERT_KEY_PROV_INFO_PROP_ID.
'
' If hCertStore is NULL, creates a certificate, CRL or CTL context not
' residing in any store.
'
' dwAddDispostion specifies the action to take if the certificate or CRL
' already exists in the store. See CertAddCertificateContextToStore for a
' list of and actions taken.
'
' dwFlags currently isn't used and should be set to 0.
'
' dwContextTypeFlags specifies the set of allowable contexts. For example, to
' add either a certificate or CRL, set dwContextTypeFlags to:
' CERT_STORE_CERTIFICATE_CONTEXT_FLAG | CERT_STORE_CRL_CONTEXT_FLAG
'
' *pdwContextType is updated with the type of the context returned in
' *ppvContxt. pdwContextType or ppvContext can be NULL, indicating the
' caller isn't interested in getting the output. If *ppvContext is
' returned it must be freed by calling CertFreeCertificateContext or
' CertFreeCRLContext.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Delete the specified certificate from the store.
'
' All subsequent gets or finds for the certificate will fail. However,
' memory allocated for the certificate isn't freed until all of its contexts
' have also been freed.
'
' The pCertContext is obtained from a get, enum, find or duplicate.
'
' Some store provider implementations might also delete the issuer's CRLs
' if this is the last certificate for the issuer in the store.
'
' NOTE: the pCertContext is always CertFreeCertificateContext'ed by
' this function, even for an error.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Add the encoded CRL to the store according to the specified
' disposition option.
'
' Makes a copy of the encoded CRL before adding to the store.
'
' dwAddDispostion specifies the action to take if the CRL
' already exists in the store. See CertAddEncodedCertificateToStore for a
' list of and actions taken.
'
' Compares the CRL's Issuer to determine if the CRL already exists in the
' store.
'
' ppCrlContext can be NULL, indicating the caller isn't interested
' in getting the CRL_CONTEXT of the added or existing CRL.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Add the CRL context to the store according to the specified
' disposition option.
'
' In addition to the encoded CRL, the context's properties are
' CERT_KEY_PROV_HANDLE_PROP_ID or CERT_KEY_SPEC_PROP_ID) isn't copied.
'
' Makes a copy of the encoded CRL before adding to the store.
'
' dwAddDispostion specifies the action to take if the CRL
' already exists in the store. See CertAddCertificateContextToStore for a
' list of and actions taken.
'
' Compares the CRL's Issuer, ThisUpdate and NextUpdate to determine
' if the CRL already exists in the store.
'
' ppStoreContext can be NULL, indicating the caller isn't interested
' in getting the CRL_CONTEXT of the added or existing CRL.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Delete the specified CRL from the store.
'
' All subsequent gets for the CRL will fail. However,
' memory allocated for the CRL isn't freed until all of its contexts
' have also been freed.
'
' The pCrlContext is obtained from a get or duplicate.
'
' NOTE: the pCrlContext is always CertFreeCRLContext'ed by
' this function, even for an error.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Serialize the certificate context's encoded certificate and its
' properties.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Serialize the CRL context's encoded CRL and its properties.
'--------------------------------------------------------------------------
'+=========================================================================
'==========================================================================
'+-------------------------------------------------------------------------
' Duplicate a CTL context
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Create a CTL context from the encoded CTL. The created
' context isn't put in a store.
'
' Makes a copy of the encoded CTL in the created context.
'
' If unable to decode and create the CTL context, NULL is returned.
' Otherwise, a pointer to a read only CTL_CONTEXT is returned.
' CTL_CONTEXT must be freed by calling CertFreeCTLContext.
' CertDuplicateCTLContext can be called to make a duplicate.
'
' CertSetCTLContextProperty and CertGetCTLContextProperty can be called
' to store properties for the CTL.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Free a CTL context
'
' There needs to be a corresponding free for each context obtained by a
' get, duplicate or create.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Set the property for the specified CTL context.
'
' Same Property Ids and semantics as CertSetCertificateContextProperty.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Get the property for the specified CTL context.
'
' Same Property Ids and semantics as CertGetCertificateContextProperty.
'
' CERT_SHA1_HASH_PROP_ID or CERT_NEXT_UPDATE_LOCATION_PROP_ID are the
' predefined properties of most interest.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Enumerate the properties for the specified CTL context.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Enumerate the CTL contexts in the store.
'
' If a CTL isn't found, NULL is returned.
' Otherwise, a pointer to a read only CTL_CONTEXT is returned. CTL_CONTEXT
' must be freed by calling CertFreeCTLContext or is freed when passed as the
' pPrevCtlContext on a subsequent call. CertDuplicateCTLContext
' can be called to make a duplicate.
'
' pPrevCtlContext MUST BE NULL to enumerate the first
' CTL in the store. Successive CTLs are enumerated by setting
' pPrevCtlContext to the CTL_CONTEXT returned by a previous call.
'
' NOTE: a NON-NULL pPrevCtlContext is always CertFreeCTLContext'ed by
' this function, even for an error.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Attempt to find the specified subject in the CTL.
'
' For CTL_CERT_SUBJECT_TYPE, pvSubject points to a CERT_CONTEXT. The CTL's
' SubjectAlgorithm is examined to determine the representation of the
' subject's identity. Initially, only SHA1 or MD5 hash will be supported.
' The appropriate hash property is obtained from the CERT_CONTEXT.
'
' For CTL_ANY_SUBJECT_TYPE, pvSubject points to the CTL_ANY_SUBJECT_INFO
' structure which contains the SubjectAlgorithm to be matched in the CTL
' and the SubjectIdentifer to be matched in one of the CTL entries.
'
' The certificate's hash or the CTL_ANY_SUBJECT_INFO's SubjectIdentifier
' is used as the key in searching the subject entries. A binary
' memory comparison is done between the key and the entry's SubjectIdentifer.
'
' dwEncodingType isn't used for either of the above SubjectTypes.
'--------------------------------------------------------------------------
' Subject Types:
' CTL_ANY_SUBJECT_TYPE, pvSubject points to following CTL_ANY_SUBJECT_INFO.
' CTL_CERT_SUBJECT_TYPE, pvSubject points to CERT_CONTEXT.
Public Const CTL_ANY_SUBJECT_TYPE As Long = 1
Public Const CTL_CERT_SUBJECT_TYPE As Long = 2
'+-------------------------------------------------------------------------
' Find the first or next CTL context in the store.
'
' The CTL is found according to the dwFindType and its pvFindPara.
' See below for a list of the find types and its parameters.
'
' Currently dwFindFlags isn't used and must be set to 0.
'
' Usage of dwMsgAndCertEncodingType depends on the dwFindType.
'
' If the first or next CTL isn't found, NULL is returned.
' Otherwise, a pointer to a read only CTL_CONTEXT is returned. CTL_CONTEXT
' must be freed by calling CertFreeCTLContext or is freed when passed as the
' pPrevCtlContext on a subsequent call. CertDuplicateCTLContext
' can be called to make a duplicate.
'
' pPrevCtlContext MUST BE NULL on the first
' call to find the CTL. To find the next CTL, the
' pPrevCtlContext is set to the CTL_CONTEXT returned by a previous call.
'
' NOTE: a NON-NULL pPrevCtlContext is always CertFreeCTLContext'ed by
' this function, even for an error.
'--------------------------------------------------------------------------
Public Const CTL_FIND_ANY As Long = 0
Public Const CTL_FIND_SHA1_HASH As Long = 1
Public Const CTL_FIND_MD5_HASH As Long = 2
Public Const CTL_FIND_USAGE As Long = 3
Public Const CTL_FIND_SUBJECT As Long = 4
Public Const CTL_FIND_NO_LIST_ID_CBDATA As Long = &HFFFFFFFF
Public Const CTL_FIND_SAME_USAGE_FLAG As Long = &H1
'+-------------------------------------------------------------------------
' CTL_FIND_ANY
'
' Find any CTL.
'
' pvFindPara isn't used.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' CTL_FIND_SHA1_HASH
' CTL_FIND_MD5_HASH
'
' Find a CTL with the specified hash.
'
' pvFindPara points to a CRYPT_HASH_BLOB.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' CTL_FIND_USAGE
'
' Find a CTL having the specified usage identifiers, list identifier or
' signer. The CertEncodingType of the signer is obtained from the
' dwMsgAndCertEncodingType parameter.
'
' pvFindPara points to a CTL_FIND_USAGE_PARA data structure. The
' SubjectUsage.cUsageIdentifer can be 0 to match any usage. The
' ListIdentifier.cbData can be 0 to match any list identifier. To only match
' CTLs without a ListIdentifier, cbData must be set to
' CTL_FIND_NO_LIST_ID_CBDATA. pSigner can be NULL to match any signer. Only
' the Issuer and SerialNumber fields of the pSigner's PCERT_INFO are used.
' To only match CTLs without a signer, pSigner must be set to
' CTL_FIND_NO_SIGNER_PTR.
'
' The CTL_FIND_SAME_USAGE_FLAG can be set in dwFindFlags to
' only match CTLs with the same usage identifiers. CTLs having additional
' usage identifiers aren't matched. For example, if only "1.2.3" is specified
' in CTL_FIND_USAGE_PARA, then, for a match, the CTL must only contain
' "1.2.3" and not any additional usage identifers.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' CTL_FIND_SUBJECT
'
' Find a CTL having the specified subject. CertFindSubjectInCTL can be
' called to get a pointer to the subject's entry in the CTL. pUsagePara can
' optionally be set to enable the above CTL_FIND_USAGE matching.
'
' pvFindPara points to a CTL_FIND_SUBJECT_PARA data structure.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Add the encoded CTL to the store according to the specified
' disposition option.
'
' Makes a copy of the encoded CTL before adding to the store.
'
' dwAddDispostion specifies the action to take if the CTL
' already exists in the store. See CertAddEncodedCertificateToStore for a
' list of and actions taken.
'
' Compares the CTL's SubjectUsage, ListIdentifier and any of its signers
' to determine if the CTL already exists in the store.
'
' ppCtlContext can be NULL, indicating the caller isn't interested
' in getting the CTL_CONTEXT of the added or existing CTL.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Add the CTL context to the store according to the specified
' disposition option.
'
' In addition to the encoded CTL, the context's properties are
' CERT_KEY_PROV_HANDLE_PROP_ID or CERT_KEY_SPEC_PROP_ID) isn't copied.
'
' Makes a copy of the encoded CTL before adding to the store.
'
' dwAddDispostion specifies the action to take if the CTL
' already exists in the store. See CertAddCertificateContextToStore for a
' list of and actions taken.
'
' Compares the CTL's SubjectUsage, ListIdentifier and any of its signers
' to determine if the CTL already exists in the store.
'
' ppStoreContext can be NULL, indicating the caller isn't interested
' in getting the CTL_CONTEXT of the added or existing CTL.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Serialize the CTL context's encoded CTL and its properties.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Delete the specified CTL from the store.
'
' All subsequent gets for the CTL will fail. However,
' memory allocated for the CTL isn't freed until all of its contexts
' have also been freed.
'
' The pCtlContext is obtained from a get or duplicate.
'
' NOTE: the pCtlContext is always CertFreeCTLContext'ed by
' this function, even for an error.
'--------------------------------------------------------------------------
'+=========================================================================
' Enhanced Key Usage Helper Functions
'==========================================================================
'+-------------------------------------------------------------------------
' Get the enhanced key usage extension or property from the certificate
' and decode.
'
' If the CERT_FIND_EXT_ONLY_ENHKEY_USAGE_FLAG is set, then, only get the
' extension.
'
' If the CERT_FIND_PROP_ONLY_ENHKEY_USAGE_FLAG is set, then, only get the
' property.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Set the enhanced key usage property for the certificate.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Add the usage identifier to the certificate's enhanced key usage property.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Remove the usage identifier from the certificate's enhanced key usage
' property.
'--------------------------------------------------------------------------
'+=========================================================================
' Cryptographic Message helper functions for verifying and signing a
' CTL.
'==========================================================================
'+-------------------------------------------------------------------------
' Get and verify the signer of a cryptographic message.
'
' To verify a CTL, the hCryptMsg is obtained from the CTL_CONTEXT's
' hCryptMsg field.
'
' If CMSG_TRUSTED_SIGNER_FLAG is set, then, treat the Signer stores as being
' trusted and only search them to find the certificate corresponding to the
' signer's issuer and serial number. Otherwise, the SignerStores are
' optionally provided to supplement the message's store of certificates.
' If a signer certificate is found, its public key is used to verify
' the message signature. The CMSG_SIGNER_ONLY_FLAG can be set to
' return the signer without doing the signature verify.
'
' If CMSG_USE_SIGNER_INDEX_FLAG is set, then, only get the signer specified
' by *pdwSignerIndex. Otherwise, iterate through all the signers
' until a signer verifies or no more signers.
'
' For a verified signature, *ppSigner is updated with certificate context
' of the signer and *pdwSignerIndex is updated with the index of the signer.
' ppSigner and/or pdwSignerIndex can be NULL, indicating the caller isn't
' interested in getting the CertContext and/or index of the signer.
'--------------------------------------------------------------------------
Public Const CMSG_TRUSTED_SIGNER_FLAG As Long = &H1
Public Const CMSG_SIGNER_ONLY_FLAG As Long = &H2
Public Const CMSG_USE_SIGNER_INDEX_FLAG As Long = &H4
'+-------------------------------------------------------------------------
' Sign an encoded CTL.
'
' The pbCtlContent can be obtained via a CTL_CONTEXT's pbCtlContent
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Encode the CTL and create a signed message containing the encoded CTL.
'--------------------------------------------------------------------------
'+=========================================================================
' Certificate Verify CTL Usage Data Structures and APIs
'==========================================================================
Public Const CERT_VERIFY_INHIBIT_CTL_UPDATE_FLAG As Long = &H1
Public Const CERT_VERIFY_TRUSTED_SIGNERS_FLAG As Long = &H2
Public Const CERT_VERIFY_NO_TIME_CHECK_FLAG As Long = &H4
Public Const CERT_VERIFY_ALLOW_MORE_USAGE_FLAG As Long = &H8
Public Const CERT_VERIFY_UPDATED_CTL_FLAG As Long = &H1
'+-------------------------------------------------------------------------
' Verify that a subject is trusted for the specified usage by finding a
' signed and time valid CTL with the usage identifiers and containing the
' the subject. A subject can be identified by either its certificate context
' or any identifier such as its SHA1 hash.
'
' See CertFindSubjectInCTL for definition of dwSubjectType and pvSubject
' parameters.
'
' Via pVerifyUsagePara, the caller can specify the stores to be searched
' to find the CTL. The caller can also specify the stores containing
' acceptable CTL signers. By setting the ListIdentifier, the caller
' can also restrict to a particular signer CTL list.
'
' Via pVerifyUsageStatus, the CTL containing the subject, the subject's
' index into the CTL's array of entries, and the signer of the CTL
' are returned. If the caller is not interested, ppCtl and ppSigner can be set
' to NULL. Returned contexts must be freed via the store's free context APIs.
'
' If the CERT_VERIFY_INHIBIT_CTL_UPDATE_FLAG isn't set, then, a time
' invalid CTL in one of the CtlStores may be replaced. When replaced, the
' CERT_VERIFY_UPDATED_CTL_FLAG is set in pVerifyUsageStatus->dwFlags.
'
' If the CERT_VERIFY_TRUSTED_SIGNERS_FLAG is set, then, only the
' SignerStores specified in pVerifyUsageStatus are searched to find
' the signer. Otherwise, the SignerStores provide additional sources
' to find the signer's certificate.
'
' If CERT_VERIFY_NO_TIME_CHECK_FLAG is set, then, the CTLs aren't checked
' for time validity.
'
' If CERT_VERIFY_ALLOW_MORE_USAGE_FLAG is set, then, the CTL may contain
' additional usage identifiers than specified by pSubjectUsage. Otherwise,
' the found CTL will contain the same usage identifers and no more.
'
' CertVerifyCTLUsage will be implemented as a dispatcher to OID installable
' functions. First, it will try to find an OID function matching the first
' usage object identifier in the pUsage sequence. Next, it will dispatch
' to the default CertDllVerifyCTLUsage functions.
'
' If the subject is trusted for the specified usage, then, TRUE is
' returned. Otherwise, FALSE is returned with dwError set to one of the
' following:
' CRYPT_E_NO_VERIFY_USAGE_DLL
' CRYPT_E_NO_VERIFY_USAGE_CHECK
' CRYPT_E_VERIFY_USAGE_OFFLINE
' CRYPT_E_NOT_IN_CTL
' CRYPT_E_NO_TRUSTED_SIGNER
'--------------------------------------------------------------------------
'+=========================================================================
' Certificate Revocation Data Structures and APIs
'==========================================================================
'+-------------------------------------------------------------------------
' The following data structure may be passed to CertVerifyRevocation to
' assist in finding the issuer of the context to be verified.
'
' When pIssuerCert is specified, pIssuerCert is the issuer of
' rgpvContext[cContext - 1].
'
' When cCertStore and rgCertStore are specified, these stores may contain
' an issuer certificate.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' The following data structure is returned by CertVerifyRevocation to
' specify the status of the revoked or unchecked context. Review the
' following CertVerifyRevocation comments for details.
'
' Upon input to CertVerifyRevocation, cbSize must be set to a size
' returns FALSE and sets LastError to E_INVALIDARG.
'
' Upon input to the installed or registered CRYPT_OID_VERIFY_REVOCATION_FUNC
' functions, the dwIndex, dwError and dwReason have been zero'ed.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Verifies the array of contexts for revocation. The dwRevType parameter
' indicates the type of the context data structure passed in rgpvContext.
' Currently only the revocation of certificates is defined.
'
' If the CERT_VERIFY_REV_CHAIN_FLAG flag is set, then, CertVerifyRevocation
' is verifying a chain of certs where, rgpvContext[i + 1] is the issuer
' of rgpvContext[i]. Otherwise, CertVerifyRevocation makes no assumptions
' about the order of the contexts.
'
' To assist in finding the issuer, the pRevPara may optionally be set. See
' the CERT_REVOCATION_PARA data structure for details.
'
' The contexts must contain enough information to allow the
' installable or registered revocation DLLs to find the revocation server. For
' certificates, this information would normally be conveyed in an
' extension such as the IETF's AuthorityInfoAccess extension.
'
' CertVerifyRevocation returns TRUE if all of the contexts were successfully
' checked and none were revoked. Otherwise, returns FALSE and updates the
' returned pRevStatus data structure as follows:
' dwIndex
' Index of the first context that was revoked or unable to
' be checked for revocation
' dwError
' Error status. LastError is also set to this error status.
' dwError can be set to one of the following error codes defined
' in winerror.h:
' ERROR_SUCCESS - good context
' CRYPT_E_REVOKED - context was revoked. dwReason contains the
' reason for revocation
' CRYPT_E_REVOCATION_OFFLINE - unable to connect to the
' revocation server
' CRYPT_E_NOT_IN_REVOCATION_DATABASE - the context to be checked
' was not found in the revocation server's database.
' CRYPT_E_NO_REVOCATION_CHECK - the called revocation function
' wasn't able to do a revocation check on the context
' CRYPT_E_NO_REVOCATION_DLL - no installed or registered Dll was
' found to verify revocation
' dwReason
' The dwReason is currently only set for CRYPT_E_REVOKED and contains
' the reason why the context was revoked. May be one of the following
' CRL_REASON_UNSPECIFIED 0
' CRL_REASON_KEY_COMPROMISE 1
' CRL_REASON_CA_COMPROMISE 2
' CRL_REASON_AFFILIATION_CHANGED 3
' CRL_REASON_SUPERSEDED 4
' CRL_REASON_CESSATION_OF_OPERATION 5
' CRL_REASON_CERTIFICATE_HOLD 6
'
' For each entry in rgpvContext, CertVerifyRevocation iterates
' through the CRYPT_OID_VERIFY_REVOCATION_FUNC
' function set's list of installed DEFAULT functions.
' CryptGetDefaultOIDFunctionAddress is called with pwszDll = NULL. If no
' installed functions are found capable of doing the revocation verification,
' CryptVerifyRevocation iterates through CRYPT_OID_VERIFY_REVOCATION_FUNC's
' list of registered DEFAULT Dlls. CryptGetDefaultOIDDllList is called to
' get the list. CryptGetDefaultOIDFunctionAddress is called to load the Dll.
'
' The called functions have the same signature as CertVerifyRevocation. A
' called function returns TRUE if it was able to successfully check all of
' the contexts and none were revoked. Otherwise, the called function returns
' FALSE and updates pRevStatus. dwIndex is set to the index of
' the first context that was found to be revoked or unable to be checked.
' dwError and LastError are updated. For CRYPT_E_REVOKED, dwReason
' is updated. Upon input to the called function, dwIndex, dwError and
' dwReason have been zero'ed. cbSize has been checked to be >=
'
' If the called function returns FALSE, and dwError isn't set to
' CRYPT_E_REVOKED, then, CertVerifyRevocation either continues on to the
' next DLL in the list for a returned dwIndex of 0 or for a returned
' dwIndex > 0, restarts the process of finding a verify function by
' advancing the start of the context array to the returned dwIndex and
' decrementing the count of remaining contexts.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Revocation types
'--------------------------------------------------------------------------
Public Const CERT_CONTEXT_REVOCATION_TYPE As Long = 1
'+-------------------------------------------------------------------------
' When the following flag is set, rgpvContext[] consists of a chain
' of certificates, where rgpvContext[i + 1] is the issuer of rgpvContext[i].
'--------------------------------------------------------------------------
Public Const CERT_VERIFY_REV_CHAIN_FLAG As Long = &H1
'+-------------------------------------------------------------------------
' CERT_CONTEXT_REVOCATION_TYPE
'
' pvContext points to a const CERT_CONTEXT.
'--------------------------------------------------------------------------
'+=========================================================================
' Certificate Helper APIs
'==========================================================================
'+-------------------------------------------------------------------------
' Compare two multiple byte integer blobs to see if they are identical.
'
' Before doing the comparison, leading zero bytes are removed from a
' positive number and leading 0xFF bytes are removed from a negative
' number.
'
' The multiple byte integers are treated as Little Endian. pbData[0] is the
' least significant byte and pbData[cbData - 1] is the most significant
' byte.
'
' Returns TRUE if the integer blobs are identical after removing leading
' 0 or 0xFF bytes.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Compare two certificates to see if they are identical.
'
' Since a certificate is uniquely identified by its Issuer and SerialNumber,
' these are the only fields needing to be compared.
'
' Returns TRUE if the certificates are identical.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Compare two certificate names to see if they are identical.
'
' Returns TRUE if the names are identical.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Compare the attributes in the certificate name with the specified
' The comparison iterates through the CERT_RDN attributes and looks for an
' attribute match in any of the certificate name's RDNs.
' Returns TRUE if all the attributes are found and match.
'
' The CERT_RDN_ATTR fields can have the following special values:
' pszObjId == NULL - ignore the attribute object identifier
' dwValueType == RDN_ANY_TYPE - ignore the value type
'
' Currently only an exact, case sensitive match is supported.
'
' CERT_UNICODE_IS_RDN_ATTRS_FLAG should be set if the pRDN was initialized
'--------------------------------------------------------------------------
Public Const CERT_UNICODE_IS_RDN_ATTRS_FLAG As Long = &H1
'+-------------------------------------------------------------------------
' Compare two public keys to see if they are identical.
'
' Returns TRUE if the keys are identical.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Verify the signature of a subject certificate or a CRL using the
' public key info
'
' Returns TRUE for a valid signature.
'
' hCryptProv specifies the crypto provider to use to verify the signature.
' It doesn't need to use a private key.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Compute the hash of the "to be signed" information in the encoded
'
' hCryptProv specifies the crypto provider to use to compute the hash.
' It doesn't need to use a private key.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Hash the encoded content.
'
' hCryptProv specifies the crypto provider to use to compute the hash.
' It doesn't need to use a private key.
'
' Algid specifies the CAPI hash algorithm to use. If Algid is 0, then, the
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Sign the "to be signed" information in the encoded signed content.
'
' hCryptProv specifies the crypto provider to use to do the signature.
' It uses the specified private key.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Encode the "to be signed" information. Sign the encoded "to be signed".
' Encode the "to be signed" and the signature.
'
' hCryptProv specifies the crypto provider to use to do the signature.
' It uses the specified private key.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Verify the time validity of a certificate.
'
' Returns -1 if before NotBefore, +1 if after NotAfter and otherwise 0 for
' a valid certificate
'
' If pTimeToVerify is NULL, uses the current time.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Verify the time validity of a CRL.
'
' Returns -1 if before ThisUpdate, +1 if after NextUpdate and otherwise 0 for
' a valid CRL
'
' If pTimeToVerify is NULL, uses the current time.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Verify that the subject's time validity nests within the issuer's time
' validity.
'
' Returns TRUE if it nests. Otherwise, returns FALSE.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Verify that the subject certificate isn't on its issuer CRL.
'
' Returns true if the certificate isn't on the CRL.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Convert the CAPI AlgId to the ASN.1 Object Identifier string
'
' Returns NULL if there isn't an ObjId corresponding to the AlgId.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Convert the ASN.1 Object Identifier string to the CAPI AlgId.
'
' Returns 0 if there isn't an AlgId corresponding to the ObjId.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Find an extension identified by its Object Identifier.
'
' If found, returns pointer to the extension. Otherwise, returns NULL.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Find the first attribute identified by its Object Identifier.
'
' If found, returns pointer to the attribute. Otherwise, returns NULL.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Find the first CERT_RDN attribute identified by its Object Identifier in
' the name's list of Relative Distinguished Names.
'
' If found, returns pointer to the attribute. Otherwise, returns NULL.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Get the intended key usage bytes from the certificate.
'
' If the certificate doesn't have any intended key usage bytes, returns FALSE
' and *pbKeyUsage is zeroed. Otherwise, returns TRUE and up through
' cbKeyUsage bytes are copied into *pbKeyUsage. Any remaining uncopied
' bytes are zeroed.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Export the public key info associated with the provider's corresponding
' private key.
'
' Calls CryptExportPublicKeyInfo with pszPublicKeyObjId = szOID_RSA_RSA,
' dwFlags = 0 and pvAuxInfo = NULL.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Export the public key info associated with the provider's corresponding
' private key.
'
' Uses the dwCertEncodingType and pszPublicKeyObjId to call the
' installable CRYPT_OID_EXPORT_PUBLIC_KEY_INFO_FUNC. The called function
' has the same signature as CryptExportPublicKeyInfoEx.
'
' If unable to find an installable OID function for the pszPublicKeyObjId,
'
' The dwFlags and pvAuxInfo aren't used for szOID_RSA_RSA.
'--------------------------------------------------------------------------
Public Const CRYPT_OID_EXPORT_PUBLIC_KEY_INFO_FUNC As String = "CryptDllExportPublicKeyInfoEx"
'+-------------------------------------------------------------------------
' Convert and import the public key info into the provider and return a
' handle to the public key.
'
' Calls CryptImportPublicKeyInfoEx with aiKeyAlg = 0, dwFlags = 0 and
' pvAuxInfo = NULL.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Convert and import the public key info into the provider and return a
' handle to the public key.
'
' Uses the dwCertEncodingType and pInfo->Algorithm.pszObjId to call the
' installable CRYPT_OID_IMPORT_PUBLIC_KEY_INFO_FUNC. The called function
' has the same signature as CryptImportPublicKeyInfoEx.
'
' If unable to find an installable OID function for the pszObjId,
'
' For szOID_RSA_RSA: aiKeyAlg may be set to CALG_RSA_SIGN or CALG_RSA_KEYX.
' Defaults to CALG_RSA_KEYX. The dwFlags and pvAuxInfo aren't used.
'--------------------------------------------------------------------------
Public Const CRYPT_OID_IMPORT_PUBLIC_KEY_INFO_FUNC As String = "CryptDllImportPublicKeyInfoEx"
'+-------------------------------------------------------------------------
' Compute the hash of the encoded public key info.
'
' The public key info is encoded and then hashed.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Convert a Name Value to a null terminated char string
'
' Returns the number of characters converted including the terminating null
' character. If psz is NULL or csz is 0, returns the required size of the
'
' If psz != NULL && csz != 0, returned psz is always NULL terminated.
'
' Note: csz includes the NULL char.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Convert a Name Value to a null terminated char string
'
' Returns the number of characters converted including the terminating null
' character. If psz is NULL or csz is 0, returns the required size of the
'
' If psz != NULL && csz != 0, returned psz is always NULL terminated.
'
' Note: csz includes the NULL char.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Convert the certificate name blob to a null terminated char string.
'
' Follows the string representation of distinguished names specified in
' empty strings and don't quote strings containing consecutive spaces).
' RDN values of type CERT_RDN_ENCODED_BLOB or CERT_RDN_OCTET_STRING are
'
' The name string is formatted according to the dwStrType:
' CERT_SIMPLE_NAME_STR
' The object identifiers are discarded. CERT_RDN entries are separated
' by ", ". Multiple attributes per CERT_RDN are separated by " + ".
' For example:
' Microsoft, Joe Cool + Programmer
' CERT_OID_NAME_STR
' The object identifiers are included with a "=" separator from their
' attribute value. CERT_RDN entries are separated by ", ".
' Multiple attributes per CERT_RDN are separated by " + ". For example:
' 2.5.4.11=Microsoft, 2.5.4.3=Joe Cool + 2.5.4.12=Programmer
' CERT_X500_NAME_STR
' The object identifiers are converted to their X500 key name. Otherwise,
' same as CERT_OID_NAME_STR. If the object identifier doesn't have
' a corresponding X500 key name, then, the object identifier is used with
' a "OID." prefix. For example:
' OU=Microsoft, CN=Joe Cool + T=Programmer, OID.1.2.3.4.5.6=Unknown
'
' We quote the RDN value if it contains leading or trailing whitespace
' or one of the following characters: ",", "+", "=", """, "\n", "<", ">",
' "#" or ";". The quoting character is ". If the the RDN Value contains
' OU=" Microsoft", CN="Joe ""Cool""" + T="Programmer, Manager"
'
' CERT_NAME_STR_SEMICOLON_FLAG can be or'ed into dwStrType to replace
' the ", " separator with a "; " separator.
'
' CERT_NAME_STR_CRLF_FLAG can be or'ed into dwStrType to replace
' the ", " separator with a "\r\n" separator.
'
' CERT_NAME_STR_NO_PLUS_FLAG can be or'ed into dwStrType to replace the
' " + " separator with a single space, " ".
'
' CERT_NAME_STR_NO_QUOTING_FLAG can be or'ed into dwStrType to inhibit
' the above quoting.
'
' Returns the number of characters converted including the terminating null
' character. If psz is NULL or csz is 0, returns the required size of the
'
' If psz != NULL && csz != 0, returned psz is always NULL terminated.
'
' Note: csz includes the NULL char.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Certificate name string types
'--------------------------------------------------------------------------
Public Const CERT_SIMPLE_NAME_STR As Long = 1
Public Const CERT_OID_NAME_STR As Long = 2
Public Const CERT_X500_NAME_STR As Long = 3
'+-------------------------------------------------------------------------
' Certificate name string type flags OR'ed with the above types
'--------------------------------------------------------------------------
Public Const CERT_NAME_STR_SEMICOLON_FLAG As Long = &H40000000
Public Const CERT_NAME_STR_NO_PLUS_FLAG As Long = &H20000000
Public Const CERT_NAME_STR_NO_QUOTING_FLAG As Long = &H10000000
Public Const CERT_NAME_STR_CRLF_FLAG As Long = &H08000000
Public Const CERT_NAME_STR_COMMA_FLAG As Long = &H04000000
'+-------------------------------------------------------------------------
' Convert the null terminated X500 string to an encoded certificate name.
'
' The input string is expected to be formatted the same as the output
' from the above CertNameToStr API.
'
' The CERT_SIMPLE_NAME_STR type isn't supported. Otherwise, when dwStrType
' is set to 0, CERT_OID_NAME_STR or CERT_X500_NAME_STR, allow either a
'
' If no flags are OR'ed into dwStrType, then, allow "," or ";" as RDN
' separators and "+" as the multiple RDN value separator. Quoting is
' supported. A quote may be included in a quoted value by double quoting,
' as ascii hex and converted to a CERT_RDN_OCTET_STRING. Embedded whitespace
'
' Whitespace surrounding the keys, object identifers and values is removed.
'
' CERT_NAME_STR_COMMA_FLAG can be or'ed into dwStrType to only allow the
' "," as the RDN separator.
'
' CERT_NAME_STR_SEMICOLON_FLAG can be or'ed into dwStrType to only allow the
' ";" as the RDN separator.
'
' CERT_NAME_STR_CRLF_FLAG can be or'ed into dwStrType to only allow
' "\r" or "\n" as the RDN separator.
'
' CERT_NAME_STR_NO_PLUS_FLAG can be or'ed into dwStrType to ignore "+"
' as a separator and not allow multiple values per RDN.
'
' CERT_NAME_STR_NO_QUOTING_FLAG can be or'ed into dwStrType to inhibit
' quoting.
'
' Support the following X500 Keys:
'
' --- ----------------- -----------------
' CN szOID_COMMON_NAME Printable, T61
' L szOID_LOCALITY_NAME Printable, T61
' O szOID_ORGANIZATION_NAME Printable, T61
' OU szOID_ORGANIZATIONAL_UNIT_NAME Printable, T61
' Email szOID_RSA_emailAddr Only IA5
' C szOID_COUNTRY_NAME Only Printable
' S szOID_STATE_OR_PROVINCE_NAME Printable, T61
' ST szOID_STATE_OR_PROVINCE_NAME Printable, T61
' STREET szOID_STREET_ADDRESS Printable, T61
' T szOID_TITLE Printable, T61
' Title szOID_TITLE Printable, T61
' G szOID_GIVEN_NAME Printable, T61
' GivenName szOID_GIVEN_NAME Printable, T61
' I szOID_INITIALS Printable, T61
' Initials szOID_INITIALS Printable, T61
' SN szOID_SUR_NAME Printable, T61
' DC szOID_DOMAIN_COMPONENT Only IA5
'
' The T61 types are UTF-8 encoded.
'
' Returns TRUE if successfully parsed the input string and encoded
' the name.
'
' If the input string is detected to be invalid, *ppszError is updated
' to point to the beginning of the invalid character sequence. Otherwise,
' *ppszError is set to NULL. *ppszError is updated with a non-NULL pointer
' for the following errors:
' CRYPT_E_INVALID_X500_STRING
' CRYPT_E_INVALID_NUMERIC_STRING
' CRYPT_E_INVALID_PRINTABLE_STRING
' CRYPT_E_INVALID_IA5_STRING
'
' ppszError can be set to NULL if not interested in getting a pointer
' to the invalid character sequence.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
'--------------------------------------------------------------------------
'+=========================================================================
' Simplified Cryptographic Message Data Structures and APIs
'==========================================================================
'+-------------------------------------------------------------------------
' Conventions for the *pb and *pcb output parameters:
'
' Upon entry to the function:
' if pcb is OPTIONAL && pcb == NULL, then,
' No output is returned
' else if pb == NULL && pcb != NULL, then,
' Length only determination. No length error is
' returned.
' Output is returned. If *pcb isn't big enough a
' length error is returned. In all cases *pcb is updated
' with the actual length needed/returned.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Type definitions of the parameters used for doing the cryptographic
' operations.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Callback to get and verify the signer's certificate.
'
' handle to its cryptographic signed message's cert store.
'
' For CRYPT_E_NO_SIGNER, called with pSignerId == NULL.
'
' For a valid signer certificate, returns a pointer to a read only
' CERT_CONTEXT. The returned CERT_CONTEXT is either obtained from a
' cert store or was created via CertCreateCertificateContext. For either case,
' its freed via CertFreeCertificateContext.
'
' If a valid certificate isn't found, this callback returns NULL with
'
' The NULL implementation tries to get the Signer certificate from the
' message cert store. It doesn't verify the certificate.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' The CRYPT_SIGN_MESSAGE_PARA are used for signing messages using the
'
' Either the CERT_KEY_PROV_HANDLE_PROP_ID or CERT_KEY_PROV_INFO_PROP_ID must
' be set for each rgpSigningCert[]. Either one specifies the private
' signature key to use.
'
' If any certificates and/or CRLs are to be included in the signed message,
' then, the MsgCert and MsgCrl parameters need to be updated. If the
' rgpSigningCerts are to be included, then, they must also be in the
' rgpMsgCert array.
'
' LastError will be updated with E_INVALIDARG.
'
' pvHashAuxInfo currently isn't used and must be set to NULL.
'
' dwFlags normally is set to 0. However, if the encoded output
' is to be a CMSG_SIGNED inner content of an outer cryptographic message,
' such as a CMSG_ENVELOPED, then, the CRYPT_MESSAGE_BARE_CONTENT_OUT_FLAG
' should be set. If not set, then it would be encoded as an inner content
' type of CMSG_DATA.
'
' dwInnerContentType is normally set to 0. It needs to be set if the
' ToBeSigned input is the encoded output of another cryptographic
' message, such as, an CMSG_ENVELOPED. When set, it's one of the cryptographic
' message types, for example, CMSG_ENVELOPED.
'
' the default), then, neither dwFlags or dwInnerContentType need to be set.
'--------------------------------------------------------------------------
Public Const CRYPT_MESSAGE_BARE_CONTENT_OUT_FLAG As Long = &H1
'+-------------------------------------------------------------------------
' The CRYPT_VERIFY_MESSAGE_PARA are used to verify signed messages.
'
' hCryptProv is used to do hashing and signature verification.
'
' The dwCertEncodingType specifies the encoding type of the certificates
' and/or CRLs in the message.
'
' pfnGetSignerCertificate is called to get and verify the message signer's
' certificate.
'
' LastError will be updated with E_INVALIDARG.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' The CRYPT_ENCRYPT_MESSAGE_PARA are used for encrypting messages.
'
' hCryptProv is used to do content encryption, recipient key
' encryption, and recipient key export. Its private key
' isn't used.
'
' pvEncryptionAuxInfo currently isn't used and must be set to NULL.
'
' LastError will be updated with E_INVALIDARG.
'
' dwFlags normally is set to 0. However, if the encoded output
' is to be a CMSG_ENVELOPED inner content of an outer cryptographic message,
' such as a CMSG_SIGNED, then, the CRYPT_MESSAGE_BARE_CONTENT_OUT_FLAG
' should be set. If not set, then it would be encoded as an inner content
' type of CMSG_DATA.
'
' dwInnerContentType is normally set to 0. It needs to be set if the
' ToBeEncrypted input is the encoded output of another cryptographic
' message, such as, an CMSG_SIGNED. When set, it's one of the cryptographic
' message types, for example, CMSG_SIGNED.
'
' the default), then, neither dwFlags or dwInnerContentType need to be set.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' The CRYPT_DECRYPT_MESSAGE_PARA are used for decrypting messages.
'
' The CertContext to use for decrypting a message is obtained from one
' of the specified cert stores. An encrypted message can have one or
' and SerialNumber). The cert stores are searched to find the CertContext
' corresponding to the CertId.
'
' Only CertContexts in the store with either
' the CERT_KEY_PROV_HANDLE_PROP_ID or CERT_KEY_PROV_INFO_PROP_ID set
' can be used. Either property specifies the private exchange key to use.
'
' LastError will be updated with E_INVALIDARG.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' The CRYPT_HASH_MESSAGE_PARA are used for hashing or unhashing
' messages.
'
' hCryptProv is used to compute the hash.
'
' pvHashAuxInfo currently isn't used and must be set to NULL.
'
' LastError will be updated with E_INVALIDARG.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' The CRYPT_KEY_SIGN_MESSAGE_PARA are used for signing messages until a
' certificate has been created for the signature key.
'
' pvHashAuxInfo currently isn't used and must be set to NULL.
'
' LastError will be updated with E_INVALIDARG.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' The CRYPT_KEY_VERIFY_MESSAGE_PARA are used to verify signed messages without
' a certificate for the signer.
'
' Normally used until a certificate has been created for the key.
'
' hCryptProv is used to do hashing and signature verification.
'
' LastError will be updated with E_INVALIDARG.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Sign the message.
'
' If fDetachedSignature is TRUE, the "to be signed" content isn't included
' in the encoded signed blob.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Verify a signed message.
'
' If pbDecoded == NULL, then, *pcbDecoded is implicitly set to 0 on input.
' For *pcbDecoded == 0 && ppSignerCert == NULL on input, the signer isn't
' verified.
'
' A message might have more than one signer. Set dwSignerIndex to iterate
' through all the signers. dwSignerIndex == 0 selects the first signer.
'
' pVerifyPara's pfnGetSignerCertificate is called to get the signer's
' certificate.
'
' For a verified signer and message, *ppSignerCert is updated
' with the CertContext of the signer. It must be freed by calling
' CertFreeCertificateContext. Otherwise, *ppSignerCert is set to NULL.
'
' ppSignerCert can be NULL, indicating the caller isn't interested
' in getting the CertContext of the signer.
'
' pcbDecoded can be NULL, indicating the caller isn't interested in getting
' the decoded content. Furthermore, if the message doesn't contain any
' content or signers, then, pcbDecoded must be set to NULL, to allow the
' pVerifyPara->pfnGetCertificate to be called. Normally, this would be
' the case when the signed message contains only certficates and CRLs.
' If pcbDecoded is NULL and the message doesn't have the indicated signer,
' pfnGetCertificate is called with pSignerId set to NULL.
'
' If the message doesn't contain any signers || dwSignerIndex > message's
' SignerCount, then, an error is returned with LastError set to
' CRYPT_E_NO_SIGNER. Also, for CRYPT_E_NO_SIGNER, pfnGetSignerCertificate
' is still called with pSignerId set to NULL.
'
' Note, an alternative way to get the certificates and CRLs from a
' signed message is to call CryptGetMessageCertificates.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Returns the count of signers in the signed message. For no signers, returns
' 0. For an error returns -1 with LastError updated accordingly.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Returns the cert store containing the message's certs and CRLs.
' For an error, returns NULL with LastError updated.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' The "to be signed" content is passed in separately. No
' decoded output. Otherwise, identical to CryptVerifyMessageSignature.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Decrypts the message.
'
' If pbDecrypted == NULL, then, *pcbDecrypted is implicitly set to 0 on input.
' For *pcbDecrypted == 0 && ppXchgCert == NULL on input, the message isn't
' decrypted.
'
' For a successfully decrypted message, *ppXchgCert is updated
' with the CertContext used to decrypt. It must be freed by calling
' CertStoreFreeCert. Otherwise, *ppXchgCert is set to NULL.
'
' ppXchgCert can be NULL, indicating the caller isn't interested
' in getting the CertContext used to decrypt.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' followed with a CryptEncryptMessage.
'
' Note: this isn't the CMSG_SIGNED_AND_ENVELOPED. Its a CMSG_SIGNED
' inside of an CMSG_ENVELOPED.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Decrypts the message and verifies the signer. Does a CryptDecryptMessage
' followed with a CryptVerifyMessageSignature.
'
' If pbDecrypted == NULL, then, *pcbDecrypted is implicitly set to 0 on input.
' For *pcbDecrypted == 0 && ppSignerCert == NULL on input, the signer isn't
' verified.
'
' A message might have more than one signer. Set dwSignerIndex to iterate
' through all the signers. dwSignerIndex == 0 selects the first signer.
'
' The pVerifyPara's VerifySignerPolicy is called to verify the signer's
' certificate.
'
' For a successfully decrypted and verified message, *ppXchgCert and
' *ppSignerCert are updated. They must be freed by calling
' CertStoreFreeCert. Otherwise, they are set to NULL.
'
' ppXchgCert and/or ppSignerCert can be NULL, indicating the
' caller isn't interested in getting the CertContext.
'
' Note: this isn't the CMSG_SIGNED_AND_ENVELOPED. Its a CMSG_SIGNED
' inside of an CMSG_ENVELOPED.
'
' The message always needs to be decrypted to allow access to the
' signed message. Therefore, if ppXchgCert != NULL, its always updated.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Decodes a cryptographic message which may be one of the following types:
' CMSG_DATA
' CMSG_SIGNED
' CMSG_ENVELOPED
' CMSG_SIGNED_AND_ENVELOPED
' CMSG_HASHED
'
' dwMsgTypeFlags specifies the set of allowable messages. For example, to
' decode either SIGNED or ENVELOPED messages, set dwMsgTypeFlags to:
' CMSG_SIGNED_FLAG | CMSG_ENVELOPED_FLAG.
'
' dwProvInnerContentType is only applicable when processing nested
' crytographic messages. When processing an outer crytographic message
' it must be set to 0. When decoding a nested cryptographic message
' its the dwInnerContentType returned by a previous CryptDecodeMessage
' of the outer message. The InnerContentType can be any of the CMSG types,
' for example, CMSG_DATA, CMSG_SIGNED, ...
'
' The optional *pdwMsgType is updated with the type of message.
'
' The optional *pdwInnerContentType is updated with the type of the inner
' message. Unless there is cryptographic message nesting, CMSG_DATA
' is returned.
'
' For CMSG_DATA: returns decoded content.
' For CMSG_SIGNED: same as CryptVerifyMessageSignature.
' For CMSG_ENVELOPED: same as CryptDecryptMessage.
' For CMSG_SIGNED_AND_ENVELOPED: same as CryptDecryptMessage plus
' CryptVerifyMessageSignature.
' For CMSG_HASHED: verifies the hash and returns decoded content.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Hash the message.
'
' If fDetachedHash is TRUE, only the ComputedHash is encoded in the
' pbHashedBlob. Otherwise, both the ToBeHashed and ComputedHash
' are encoded.
'
' pcbHashedBlob or pcbComputedHash can be NULL, indicating the caller
' isn't interested in getting the output.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Verify a hashed message.
'
' pcbToBeHashed or pcbComputedHash can be NULL,
' indicating the caller isn't interested in getting the output.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Verify a hashed message containing a detached hash.
' The "to be hashed" content is passed in separately. No
' decoded output. Otherwise, identical to CryptVerifyMessageHash.
'
' pcbComputedHash can be NULL, indicating the caller isn't interested
' in getting the output.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Sign the message using the provider's private key specified in the
' parameters. A dummy SignerId is created and stored in the message.
'
' Normally used until a certificate has been created for the key.
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Verify a signed message using the specified public key info.
'
' Normally called by a CA until it has created a certificate for the
' key.
'
' pPublicKeyInfo contains the public key to use to verify the signed
' content may contain the PublicKeyInfo).
'
' pcbDecoded can be NULL, indicating the caller isn't interested
' in getting the decoded content.
'--------------------------------------------------------------------------
'+=========================================================================
' System Certificate Store Data Structures and APIs
'==========================================================================
'+-------------------------------------------------------------------------
' Get a system certificate store based on a subsystem protocol.
'
' Current examples of subsystems protocols are:
' "MY" Cert Store hold certs with associated Private Keys
' "CA" Certifying Authority certs
' "ROOT" Root Certs
' "SPC" Software publisher certs
'
'
' If hProv is NULL the default provider "1" is opened for you.
' When the store is closed the provider is release. Otherwise
' if hProv is not NULL, no provider is created or released.
'
' The returned Cert Store can be searched for an appropriate Cert
'
' When done, the cert store should be closed using CertStoreClose
'--------------------------------------------------------------------------
'+-------------------------------------------------------------------------
' Find all certificate chains tying the given issuer name to any certificate
' that the current user has a private key for.
'
' If no certificate chain is found, FALSE is returned with LastError set
' to CRYPT_E_NOT_FOUND and the counts zeroed.
'
' IE 3.0 ASSUMPTION:
' The client certificates are in the "My" system store. The issuer
' cerificates may be in the "Root", "CA" or "My" system stores.
'--------------------------------------------------------------------------
' WINCRYPT32API This is not exported by crypt32, it is exported by softpub
'+--------------------------------------------------------------------------
'
' Microsoft Windows
'
' File: cs.h
'
' Contents: Cert Server common definitions
'
' History: 25-Jul-96 vich created
'
'---------------------------------------------------------------------------
Public Const VR_PENDING As Long = 0
Public Const VR_INSTANT_OK As Long = 1
Public Const VR_INSTANT_BAD As Long = 2
' Certificate types:
Public Const CERT_TYPE_NONE As Long = 0
Public Const CERT_TYPE_X509 As Long = 1
Public Const CERT_TYPE_SDSI As Long = 2
Public Const CERT_TYPE_PGP As Long = 3
' Request types:
Public Const REQ_TYPE_NONE As Long = 0
Public Const REQ_TYPE_PKCS10 As Long = 1
Public Const REQ_TYPE_KEYGEN As Long = 2
' RegisterNewRequest is called to deliver a new request to the certificate
' server. dwType indicates the type of request that has been received.
' The following values are valid:
Public Const RNR_T_UNK As Long = 0
Public Const RNR_T_PKCS10 As Long = 1
Public Const RNR_T_KEYGEN As Long = 2
Public Const RNR_T_CUSTOM As Long = 3
' Transport Info:
' The transport info structure is used several places in the certificate
' server to describe how request arrived, or how a certificate or CRL is to be
' sent. The structure can define an address in steps of precision. It can be
' just a type of transport, a specific transport mechanism, a transport
' address, or a specific authenticated user at an address.
' Address Types:
Public Const ADR_TYPE As Long = &H00000001
Public Const ADR_STYPE As Long = &H00000002
Public Const ADR_ADDR As Long = &H00000004
Public Const ADR_USER As Long = &H00000008
Public Const ADR_AUTH As Long = &H00000010
Public Const ADR_TIME As Long = &H00000020
' Transport Types:
Public Const TTYPE_FREE As Long = 0
Public Const TTYPE_EMAIL As Long = 1
Public Const TTYPE_DNS As Long = 2
' EMAIL subtypes:
Public Const TSUB_MAIL_GENERIC As Long = 1
Public Const TSUB_MAIL_PEM As Long = 2
Public Const TSUB_MAIL_EXCHSEC As Long = 3
Public Const TSUB_MAIL_PGP As Long = 4
' DNS subtypes:
Public Const TSUB_DNS_FTP As Long = 1
Public Const TSUB_DNS_HTTP As Long = 2
Public Const TSUB_DNS_HTTPS As Long = 3
' Authentication Types:
Public Const AAT_CERT As Long = 1
Public Const AAT_NTLM As Long = 2
Public Const AAT_SICILY As Long = 3
'
' VOID
' PLIST_ENTRY ListHead
' );
'
'
' VOID
' PLIST_ENTRY ListHead,
' PLIST_ENTRY Entry
' );
'
'
' VOID
' PLIST_ENTRY Entry
' );
'
'+--------------------------------------------------------------------------
'
' Microsoft Windows
'
' File: csprop.h
'
' Contents: Cert Server Property interfaces
'
' History: 31-Jul-96 vich created
'
'---------------------------------------------------------------------------
'+--------------------------------------------------------------------------
' Name properties:
Public Const wszPROPDISTINGUISHEDNAME As String = "DistinguishedName"
Public Const wszPROPRAWNAME As String = "RawName"
Public Const wszPROPNAMETYPE As String = "NameType"
Public Const wszPROPCOUNTRY As String = "Country"
Public Const wszPROPORGANIZATION As String = "Organization"
Public Const wszPROPORGUNIT As String = "OrgUnit"
Public Const wszPROPCOMMONNAME As String = "CommonName"
Public Const wszPROPLOCALITY As String = "Locality"
Public Const wszPROPSTATE As String = "State"
Public Const wszPROPTITLE As String = "Title"
Public Const wszPROPGIVENNAME As String = "GivenName"
Public Const wszPROPINITIALS As String = "Initials"
Public Const wszPROPSURNAME As String = "SurName"
Public Const wszPROPDOMAINCOMPONENT As String = "DomainComponent"
Public Const wszPROPEMAIL As String = "EMail"
'+--------------------------------------------------------------------------
' Subject Name properties:
Public Const wszPROPSUBJECTDOT As String = "Subject."
'+--------------------------------------------------------------------------
' Issuer Name properties:
Public Const wszPROPISSUERDOT As String = "Issuer."
'+--------------------------------------------------------------------------
' For mapping request attribute names to internal property names:
' Map to wszPROPSUBJECTCOMMONNAME:
Public Const wszATTRCOMMONNAME1 As String = "CN"
Public Const wszATTRCOMMONNAME2 As String = "CommonName"
' Map to wszPROPSUBJECTLOCALITY:
Public Const wszATTRLOCALITY1 As String = ""
Public Const wszATTRLOCALITY2 As String = "Locality"
' Map to wszPROPSUBJECTSTATE:
Public Const wszATTRSTATE1 As String = "S"
Public Const wszATTRSTATE2 As String = "State"
' Map to wszPROPSUBJECTCOUNTRY:
Public Const wszATTRCOUNTRY1 As String = "C"
Public Const wszATTRCOUNTRY2 As String = "Country"
' Map to wszPROPSUBJECTORGANIZATION:
Public Const wszATTRORG1 As String = "O"
Public Const wszATTRORG2 As String = "Org"
Public Const wszATTRORG3 As String = "Organization"
' Map to wszPROPSUBJECTORGUNIT:
Public Const wszATTRORGUNIT1 As String = "OU"
Public Const wszATTRORGUNIT2 As String = "OrgUnit"
Public Const wszATTRORGUNIT3 As String = "OrganizationUnit"
Public Const wszATTRORGUNIT4 As String = "OrganizationalUnit"
' Map to wszPROPSUBJECTDOMAINCOMPONENT:
Public Const wszATTRDOMAINCOMPONENT1 As String = "DC"
Public Const wszATTRDOMAINCOMPONENT2 As String = "DomainComponent"
' Map to wszPROPSUBJECTEMAIL:
Public Const wszATTREMAIL1 As String = "EMail"
'+--------------------------------------------------------------------------
' Request properties:
Public Const wszPROPREQUESTREQUESTID As String = "RequestID"
Public Const wszPROPREQUESTRAWREQUEST As String = "RawRequest"
Public Const wszPROPREQUESTATTRIBUTES As String = "RequestAttributes"
Public Const wszPROPREQUESTTYPE As String = "RequestType"
Public Const wszPROPREQUESTFLAGS As String = "RequestFlags"
Public Const wszPROPREQUESTSTATUS As String = "Status"
Public Const wszPROPREQUESTSTATUSCODE As String = "StatusCode"
Public Const wszPROPREQUESTDISPOSITION As String = "Disposition"
Public Const wszPROPREQUESTDISPOSITIONMESSAGE As String = "DispositionMessage"
Public Const wszPROPREQUESTSUBMITTEDWHEN As String = "SubmittedWhen"
Public Const wszPROPREQUESTRESOLVEDWHEN As String = "ResolvedWhen"
Public Const wszPROPREQUESTREVOKEDWHEN As String = "RevokedWhen"
Public Const wszPROPREQUESTREVOKEDEFFECTIVEWHEN As String = "RevokedEffectiveWhen"
Public Const wszPROPREQUESTREVOKEDREASON As String = "RevokedReason"
Public Const wszPROPREQUESTSUBJECTNAMEID As String = "SubjectNameID"
Public Const wszPROPREQUESTERNAME As String = "RequesterName"
Public Const wszPROPREQUESTERADDRESS As String = "RequesterAddress"
'+--------------------------------------------------------------------------
' Request attribute properties:
Public Const wszPROPCHALLENGE As String = "Challenge"
Public Const wszPROPEXPECTEDCHALLENGE As String = "ExpectedChallenge"
'+--------------------------------------------------------------------------
' Certificate properties:
Public Const wszPROPCERTIFICATEREQUESTID As String = "RequestID"
Public Const wszPROPRAWCERTIFICATE As String = "RawCertificate"
Public Const wszPROPCERTIFICATETYPE As String = "CertificateType"
Public Const wszPROPCERTIFICATESERIALNUMBER As String = "SerialNumber"
Public Const wszPROPCERTIFICATEISSUERNAMEID As String = "IssuerNameID"
Public Const wszPROPCERTIFICATESUBJECTNAMEID As String = "SubjectNameID"
Public Const wszPROPCERTIFICATENOTBEFOREDATE As String = "NotBefore"
Public Const wszPROPCERTIFICATENOTAFTERDATE As String = "NotAfter"
Public Const wszPROPCERTIFICATERAWPUBLICKEY As String = "RawPublicKey"
Public Const wszPROPCERTIFICATEPUBLICKEYALGORITHM As String = "PublicKeyAlgorithm"
'+--------------------------------------------------------------------------
' Certificate extension properties:
Public Const wszPROPCERTIFICATEEXTENSIONFLAGS As String = "Flags"
Public Const wszPROPCERTIFICATEEXTENSIONVALUE As String = "Value"
Public Const EXTENSION_CRITICAL_FLAG As Long = &H00000001
Public Const EXTENSION_DISABLE_FLAG As Long = &H00000002
Public Const EXTENSION_POLICY_MASK As Long = &H0000ffff
Public Const EXTENSION_ORIGIN_REQUEST As Long = &H00010000
Public Const EXTENSION_ORIGIN_POLICY As Long = &H00020000
Public Const EXTENSION_ORIGIN_ADMIN As Long = &H00030000
Public Const EXTENSION_ORIGIN_SERVER As Long = &H00040000
Public Const EXTENSION_ORIGIN_MASK As Long = &H000f0000
'+--------------------------------------------------------------------------
' GetProperty/SetProperty Flags:
'
' Choose one Type
Public Const PROPTYPE_LONG As Long = &H00000001
Public Const PROPTYPE_DATE As Long = &H00000002
Public Const PROPTYPE_BINARY As Long = &H00000003
Public Const PROPTYPE_STRING As Long = &H00000004
Public Const PROPTYPE_ANSI As Long = &H00000005
Public Const PROPTYPE_MASK As Long = &H000000ff
' Choose one Caller:
Public Const PROPCALLER_SERVER As Long = &H00000100
Public Const PROPCALLER_POLICY As Long = &H00000200
Public Const PROPCALLER_EXIT As Long = &H00000300
Public Const PROPCALLER_ADMIN As Long = &H00000400
Public Const PROPCALLER_MASK As Long = &H00000f00
' Choose one Table:
Public Const PROPTABLE_REQUEST As Long = &H00001000
Public Const PROPTABLE_CERTIFICATE As Long = &H00002000
Public Const PROPTABLE_EXTENSIONS As Long = &H00003000
Public Const PROPTABLE_ATTRIBUTES As Long = &H00004000
Public Const PROPTABLE_MASK As Long = &H0000f000
' Internal use only
Public Const PROPTABLE_EXTENSIONFLAGS As Long = &H00010000
Public Const PROPTABLE_EXTENSIONVALUE As Long = &H00020000
Public Const cchSERIALNUMBERMAX As Long = 64
Public Const cchOBJECTIDMAX As Long = 31
Public Const cchDISTINGUISHEDNAMEMAX As Long = 254
Public Const cchCOUNTRYNAMEMAX As Long = 2
' Request Status property values:
Public Const REQSTATUS_ACTIVE As Long = 1
Public Const REQSTATUS_ACCEPTED As Long = 2
Public Const REQSTATUS_DENIED As Long = 3
Public Const REQSTATUS_PENDING As Long = 4
Public Const REQSTATUS_ERROR As Long = 5
' CertIF property callback support:
' CertIF property enumeration callback support:
Public Const CIE_OBJECTID As Long = &H00000001
Public Const CIE_TABLE_EXTENSIONS As Long = &H00000010
Public Const CIE_TABLE_ATTRIBUTES As Long = &H00000020
Public Const CIE_TABLE_MASK As Long = &H000000f0
'+--------------------------------------------------------------------------
'
' Microsoft Windows
'
' File: certreq.h
'
' Contents: ICertRequest definitions
'
' History: 03-Jan-97 vich created
'
'---------------------------------------------------------------------------
'+--------------------------------------------------------------------------
' Known request Attribute names and Value strings
' RequestType attribute name:
Public Const wszCERT_TYPE As String = "RequestType"
' RequestType attribute values:
' Not specified:
Public Const wszCERT_TYPE_CLIENT As String = "Client"
Public Const wszCERT_TYPE_SERVER As String = "Server"
Public Const wszCERT_TYPE_CODESIGN As String = "CodeSign"
Public Const wszCERT_TYPE_CUSTOMER As String = "SetCustomer"
Public Const wszCERT_TYPE_MERCHANT As String = "SetMerchant"
Public Const wszCERT_TYPE_PAYMENT As String = "SetPayment"
' Version attribute name:
Public Const wszCERT_VERSION As String = "Version"
' Version attribute values:
' Not specified:
Public Const wszCERT_VERSION_1 As String = "1"
Public Const wszCERT_VERSION_2 As String = "2"
Public Const wszCERT_VERSION_3 As String = "3"
