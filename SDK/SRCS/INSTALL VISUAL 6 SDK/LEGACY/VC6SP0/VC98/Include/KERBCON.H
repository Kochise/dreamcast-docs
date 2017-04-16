//+-----------------------------------------------------------------------
//
// File:        KERBCON.H
//
// Contents:    Microsoft Kerberos constants
//
//
// History:     25 Feb 92   RichardW    Compiled from other files
//
//------------------------------------------------------------------------

#ifndef __KERBCON_H__
#define __KERBCON_H__


// Revision of the Kerberos Protocol.  MS uses Version 5, Revision 6

#define KERBEROS_VERSION    5
#define KERBEROS_REVISION   6



// Encryption Types:
// These encryption types are supported by the default MS KERBSUPP DLL
// as crypto systems.  Values over 127 are local values, and may be changed
// without notice.

#define KERB_ETYPE_NULL             0
#define KERB_ETYPE_DES_CBC_CRC      1
#define KERB_ETYPE_DES_CBC_MD4      2
#define KERB_ETYPE_DES_CBC_MD5      3

#define KERB_ETYPE_OLD_RC4_MD4          128
#define KERB_ETYPE_OLD_RC4_PLAIN        129
#define KERB_ETYPE_OLD_RC4_LM           130
#define KERB_ETYPE_OLD_RC4_SHA          131
#define KERB_ETYPE_OLD_DES_PLAIN        132

#define KERB_ETYPE_RC4_MD4          -128
#define KERB_ETYPE_RC4_PLAIN        -129
#define KERB_ETYPE_RC4_LM           -130
#define KERB_ETYPE_RC4_SHA          -131
#define KERB_ETYPE_DES_PLAIN        -132


// Checksum algorithms.
// These algorithms are keyed internally for our use.

#define KERB_CHECKSUM_NONE  0
#define KERB_CHECKSUM_CRC32         1
#define KERB_CHECKSUM_MD4           2
#define KERB_CHECKSUM_KRB_DES_MAC   4
#define KERB_CHECKSUM_MD5           7
#define KERB_CHECKSUM_MD5_DES       8


#define KERB_CHECKSUM_OLD_LM            130
#define KERB_CHECKSUM_OLD_SHA1          131
#define KERB_CHECKSUM_OLD_REAL_CRC32    132
#define KERB_CHECKSUM_OLD_DES_MAC       133
#define KERB_CHECKSUM_OLD_DES_MAC_MD5   134
#define KERB_CHECKSUM_OLD_MD25          135
#define KERB_CHECKSUM_OLD_RC4_MD5       136


#define KERB_CHECKSUM_LM            -130
#define KERB_CHECKSUM_SHA1          -131
#define KERB_CHECKSUM_REAL_CRC32    -132
#define KERB_CHECKSUM_DES_MAC       -133
#define KERB_CHECKSUM_DES_MAC_MD5   -134
#define KERB_CHECKSUM_MD25          -135
#define KERB_CHECKSUM_RC4_MD5       -136


#define AUTH_REQ_ALLOW_FORWARDABLE      0x00000001
#define AUTH_REQ_ALLOW_PROXIABLE        0x00000002
#define AUTH_REQ_ALLOW_POSTDATE         0x00000004
#define AUTH_REQ_ALLOW_RENEWABLE        0x00000008
#define AUTH_REQ_ALLOW_NOADDRESS        0x00000010
#define AUTH_REQ_ALLOW_ENC_TKT_IN_SKEY  0x00000020
#define AUTH_REQ_ALLOW_VALIDATE         0x00000040
#define AUTH_REQ_VALIDATE_CLIENT        0x00000080
#define AUTH_REQ_OK_AS_DELEGATE         0x00000100


//
// KDC auditing flags. these do not belong here for long
//

#define KDC_AUDIT_AS_SUCCESS            0x1
#define KDC_AUDIT_AS_FAILURE            0x2
#define KDC_AUDIT_TGS_SUCCESS           0x4
#define KDC_AUDIT_TGS_FAILURE           0x8

//
// macro for converting auth flags & audit flags to state which may
// be set through the debug function KdcSetState
//

#define KDC_MAKE_STATE(AuthFlag, AuditFlag) (((AuditFlag) << 16) | ((AuthFlag) & 0xffff))
#define KDC_AUTH_STATE(StateFlags) ((StateFlags) & 0xffff)
#define KDC_AUDIT_STATE(StateFlags) ((StateFlags) >> 16)

#endif // __KERBCON_H__
