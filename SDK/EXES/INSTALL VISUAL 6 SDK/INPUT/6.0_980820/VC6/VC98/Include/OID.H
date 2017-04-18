
//==========================================================================================================================
//  MODULE: OID.h
//
//  Description:
//
//  Bloodhound Kernel, OID utilities (SNMP)
//
//  Modification History
//
//  Keith Lau        01/09/95        Created
//==========================================================================================================================

#ifndef OID_H
#define OID_H

#include <windows.h>
#include <string.h>
#include <bh.h>

// class field of BER tag
#define ASN_UNIVERSAL         0x00
#define ASN_APPLICATION       0x40
#define ASN_CONTEXTSPECIFIC   0x80
#define ASN_PRIVATE           0xC0

// primative/constructed field of BER tag
#define ASN_PRIMATIVE         0x00
#define ASN_CONSTRUCTOR       0x20

// Priviliged message
#define ASN_RFCxxxx_PRIVDATA (ASN_CONTEXTSPECIFIC | ASN_PRIMATIVE | 0x01)

#define ASN_RFCxxxx_SNMPMGMTCOM (ASN_CONTEXTSPECIFIC | ASN_CONSTRUCTOR | 0x01)
#define ASN_RFCxxxx_SNMPAUTHMSG (ASN_CONTEXTSPECIFIC | ASN_CONSTRUCTOR | 0x01)
#define ASN_RFCxxxx_SNMPPRIVMSG (ASN_CONTEXTSPECIFIC | ASN_CONSTRUCTOR | 0x01)

// ASN.1 simple types
#define ASN_INTEGER           (ASN_UNIVERSAL | ASN_PRIMATIVE | 0x02)
#define ASN_OCTETSTRING       (ASN_UNIVERSAL | ASN_PRIMATIVE | 0x04)
#define ASN_NULL              (ASN_UNIVERSAL | ASN_PRIMATIVE | 0x05)
#define ASN_OBJECTIDENTIFIER  (ASN_UNIVERSAL | ASN_PRIMATIVE | 0x06)

// ASN.1 constructor types
#define ASN_SEQUENCE          (ASN_UNIVERSAL | ASN_CONSTRUCTOR | 0x10)
#define ASN_SEQUENCEOF        ASN_SEQUENCE

// ASN.1 application specific primatives
#define ASN_RFC1155_IPADDRESS  (ASN_APPLICATION | ASN_PRIMATIVE | 0x00)
#define ASN_RFC1155_COUNTER    (ASN_APPLICATION | ASN_PRIMATIVE | 0x01)
#define ASN_RFC1155_GAUGE      (ASN_APPLICATION | ASN_PRIMATIVE | 0x02)
#define ASN_RFC1155_TIMETICKS  (ASN_APPLICATION | ASN_PRIMATIVE | 0x03)
#define ASN_RFC1155_OPAQUE     (ASN_APPLICATION | ASN_PRIMATIVE | 0x04)
#define ASN_RFC1213_DISPSTRING ASN_OCTETSTRING

   // BER limits
#define BER_OCTET_LEN         8      // 8 bits in an octet
#define BER_OCTET_SIZE        256    // 8 bits make an octet
#define BER_MAX_INT_OCTETS    4      // 4 octets - 32 bit integer
#define BER_MAX_LEN_OCTETS    2      // 2 octets - 16 bit integer length
#define BER_MAX_STREAM_LEN    0xffff // 16 bit unsigned integer
#define BER_MIN_HEADER_LEN    2      // 2 octets
#define BER_MAX_SIMPLE_LEN    127    // SNMP BER definition

   // Buffer offsets for info.
#define BER_TAG_OFFSET        0
#define BER_LENGTH_OFFSET     1

   // Meaningful bit definitions
#define BER_EXTENDED_TAG      0x1f   // 00011111
#define BER_OCTET_CONT_BIT    0x80   // 10000000

   // BER OBJECTIDENTIFIER limits
#define BER_MAX_FIRST_ELEM    2      // Obj Id's 1st element must be 0-2
#define BER_MAX_SECOND_ELEM   39     // Obj Id's 2nd element must be 0-40


// These are defined solely for Object Identifier (OID) filter contains actions
#define OID_BEGINS_WITH       1
#define OID_ENDS_WITH         2
#define OID_CONTAINS          (OID_BEGINS_WITH | OID_ENDS_WITH)

// Function prototypes
DWORD WINAPI DecodeSNMPObjectIdentifier( LPBYTE              lpData, 
                                         DWORD               DataLen,
                                         LPOBJECT_IDENTIFIER lpOID);

VOID WINAPI EncodeSNMPObjectIdentifier( LPBYTE              lpData, 
										LPDWORD             lpDataLen,
										LPOBJECT_IDENTIFIER lpOID);

BOOL WINAPI IsValidSNMPObjectIdentifier(LPOBJECT_IDENTIFIER lpOID);

BOOL WINAPI ObjectIdentifierContains (LPBYTE SubOID,
                                      WORD   SubOIDLen,
                                      LPBYTE OID,
                                      WORD   OIDLen,
                                      DWORD  ContainFlags);



#endif
