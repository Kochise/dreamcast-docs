//=============================================================================
//  Microsoft (R) Bloodhound (tm). Copyright (C) 1991-1992.
//
//  MODULE: bhTypes.h
//
//  This is the top-level include file for all Bloodhound struct definitions.
//=============================================================================

#if !defined(_BHTYPE_)

#define _BHTYPE_

#pragma pack(1)

//=============================================================================
//  Unaligned base type definitions.
//=============================================================================

typedef VOID        UNALIGNED   *ULPVOID;
typedef BYTE        UNALIGNED   *ULPBYTE;
typedef WORD        UNALIGNED   *ULPWORD;
typedef DWORD       UNALIGNED   *ULPDWORD;
typedef CHAR        UNALIGNED   *ULPSTR;
typedef SYSTEMTIME  UNALIGNED   *ULPSYSTEMTIME;

//=============================================================================
//  Handle definitions.
//=============================================================================

typedef struct _PARSER     *HPARSER;

typedef struct _FRAMEDESC  *HFRAME;
typedef struct _CAPTURE    *HCAPTURE;
typedef struct _FILTER     *HFILTER;
typedef struct _ADDRESSDB  *HADDRESSDB;
typedef struct _PROTOCOL   *HPROTOCOL;
typedef DWORD               HPROPERTY;

typedef HPROTOCOL          *LPHPROTOCOL;

//=============================================================================
//  GetTableSize() -- The following macro is used to calculate the actual
//                    length of Bloodhound variable-length table structures.
//
//  EXAMPLE:
//
//  GetTableSize(PROTOCOLTABLESIZE, ProtocolTable->nProtocols, sizeof(HPROTOCOL))
//=============================================================================

#define GetTableSize(TableBaseSize, nElements, ElementSize) ((TableBaseSize) + ((nElements) * (ElementSize)))

//=============================================================================
//  Object type identifiers.
//=============================================================================

typedef DWORD OBJECTTYPE;

#ifndef MAKE_IDENTIFIER
#define MAKE_IDENTIFIER(a, b, c, d)     ((DWORD) MAKELONG(MAKEWORD(a, b), MAKEWORD(c, d)))
#endif

#define HANDLE_TYPE_INVALID             MAKE_IDENTIFIER(-1, -1, -1, -1)
#define HANDLE_TYPE_CAPTURE             MAKE_IDENTIFIER('C', 'A', 'P', '$')
#define HANDLE_TYPE_PARSER              MAKE_IDENTIFIER('P', 'S', 'R', '$')
#define HANDLE_TYPE_ADDRESSDB           MAKE_IDENTIFIER('A', 'D', 'R', '$')
#define HANDLE_TYPE_PROTOCOL            MAKE_IDENTIFIER('P', 'R', 'T', '$')
#define HANDLE_TYPE_BUFFER              MAKE_IDENTIFIER('B', 'U', 'F', '$')

//=============================================================================
//  Bloodhound constant definitions.
//=============================================================================

#define INLINE  __inline
#define BHAPI   WINAPI

#define MAX_NAME_LENGTH                 16
#define MAX_ADDR_LENGTH                 6

//=============================================================================
//  Ethernet type (ETYPE) constant definitions.
//=============================================================================

#define ETYPE_LOOP                      0x9000
#define ETYPE_3COM_NETMAP1              0x9001
#define ETYPE_3COM_NETMAP2              0x9002
#define ETYPE_IBM_RT                    0x80D5
#define ETYPE_NETWARE                   0x8137
#define ETYPE_XNS1                      0x0600
#define ETYPE_XNS2                      0x0807
#define ETYPE_3COM_NBP0                 0x3C00
#define ETYPE_3COM_NBP1                 0x3C01
#define ETYPE_3COM_NBP2                 0x3C02
#define ETYPE_3COM_NBP3                 0x3C03
#define ETYPE_3COM_NBP4                 0x3C04
#define ETYPE_3COM_NBP5                 0x3C05
#define ETYPE_3COM_NBP6                 0x3C06
#define ETYPE_3COM_NBP7                 0x3C07
#define ETYPE_3COM_NBP8                 0x3C08
#define ETYPE_3COM_NBP9                 0x3C09
#define ETYPE_3COM_NBP10                0x3C0A
#define ETYPE_IP                        0x0800
#define ETYPE_ARP1                      0x0806
#define ETYPE_ARP2                      0x0807
#define ETYPE_RARP                      0x8035
#define ETYPE_TRLR0                     0x1000
#define ETYPE_TRLR1                     0x1001
#define ETYPE_TRLR2                     0x1002
#define ETYPE_TRLR3                     0x1003
#define ETYPE_TRLR4                     0x1004
#define ETYPE_TRLR5                     0x1005
#define ETYPE_PUP                       0x0200
#define ETYPE_PUP_ARP                   0x0201
#define ETYPE_APPLETALK_ARP             0x80F3
#define ETYPE_APPLETALK_LAP             0x809B
#define ETYPE_SNMP                      0x814C

//=============================================================================
//  LLC (802.2) SAP constant definitions.
//=============================================================================

#define SAP_SNAP                        0xAA
#define SAP_BPDU                        0x42
#define SAP_IBM_NM                      0xF4
#define SAP_IBM_NETBIOS                 0xF0
#define SAP_SNA1                        0x04
#define SAP_SNA2                        0x05
#define SAP_SNA3                        0x08
#define SAP_SNA4                        0x0C
#define SAP_NETWARE1                    0x10
#define SAP_NETWARE2                    0xE0
#define SAP_NETWARE3                    0xFE
#define SAP_IP                          0x06
#define SAP_X25                         0x7E
#define SAP_RPL1                        0xF8
#define SAP_RPL2                        0xFC
#define SAP_UB                          0xFA
#define SAP_XNS                         0x80

//=============================================================================
//  Property constants
//=============================================================================

// data types

#define PROP_TYPE_VOID              0x00
#define PROP_TYPE_SUMMARY           0x01
#define PROP_TYPE_BYTE              0x02
#define PROP_TYPE_WORD              0x03
#define PROP_TYPE_DWORD             0x04
#define PROP_TYPE_LARGEINT          0x05
#define PROP_TYPE_ADDR              0x06
#define PROP_TYPE_TIME              0x07
#define PROP_TYPE_STRING            0x08
#define PROP_TYPE_IP_ADDRESS        0x09
#define PROP_TYPE_IPX_ADDRESS       0x0A
#define PROP_TYPE_BYTESWAPPED_WORD  0x0B
#define PROP_TYPE_BYTESWAPPED_DWORD 0x0C
#define PROP_TYPE_TYPED_STRING      0x0D
#define PROP_TYPE_RAW_DATA          0x0E
#define PROP_TYPE_COMMENT           0x0F
#define PROP_TYPE_SRCFRIENDLYNAME   0x10
#define PROP_TYPE_DSTFRIENDLYNAME   0x11
#define PROP_TYPE_TOKENRING_ADDRESS 0x12
#define PROP_TYPE_FDDI_ADDRESS      0x13
#define PROP_TYPE_ETHERNET_ADDRESS  0x14
#define PROP_TYPE_OBJECT_IDENTIFIER	0x15
#define PROP_TYPE_VINES_IP_ADDRESS  0x16
#define PROP_TYPE_VAR_LEN_SMALL_INT 0x17

// data qualifiers

#define PROP_QUAL_NONE              0x00
#define PROP_QUAL_RANGE             0x01
#define PROP_QUAL_SET               0x02
#define PROP_QUAL_BITFIELD          0x03
#define PROP_QUAL_LABELED_SET       0x04
#define PROP_QUAL_LABELED_BITFIELD  0x08
#define PROP_QUAL_CONST             0x09
#define PROP_QUAL_FLAGS             0x0A
#define PROP_QUAL_ARRAY             0x0B

//=============================================================================
//  LARGEINT structure defined in winnt.h
//=============================================================================

//typedef struct _LARGEINT
//{
//    ULONG LowLong;
//    LONG  HighLong;
//} LARGEINT;
//

typedef LARGE_INTEGER *LPLARGEINT;
typedef LARGE_INTEGER UNALIGNED *ULPLARGEINT;

//=============================================================================
//  Range structure.
//=============================================================================

typedef struct _RANGE
{
    DWORD   MinValue;
    DWORD   MaxValue;
} RANGE;

typedef RANGE *LPRANGE;

//=============================================================================
//  LABELED_BYTE structure
//=============================================================================

typedef struct _LABELED_BYTE
{
    BYTE    Value;
    LPSTR   Label;
} LABELED_BYTE;

typedef LABELED_BYTE *LPLABELED_BYTE;

//=============================================================================
//  LABELED_WORD structure
//=============================================================================

typedef struct _LABELED_WORD
{
    WORD    Value;
    LPSTR   Label;
} LABELED_WORD;

typedef LABELED_WORD *LPLABELED_WORD;

//=============================================================================
//  LABELED_DWORD structure
//=============================================================================

typedef struct _LABELED_DWORD
{
    DWORD   Value;
    LPSTR   Label;
} LABELED_DWORD;

typedef LABELED_DWORD *LPLABELED_DWORD;

//=============================================================================
//  LABELED_LARGEINT structure
//=============================================================================

typedef struct _LABELED_LARGEINT
{
    LARGE_INTEGER   Value;
    LPSTR           Label;
} LABELED_LARGEINT;

typedef LABELED_LARGEINT *LPLABELED_LARGEINT;

//=============================================================================
//  LABELED_SYSTEMTIME structure
//=============================================================================

typedef struct _LABELED_SYSTEMTIME
{
    SYSTEMTIME      Value;
    LPSTR           Label;
} LABELED_SYSTEMTIME;

typedef LABELED_SYSTEMTIME *LPLABELED_SYSTEMTIME;

//=============================================================================
//  LABELED_BIT structure
//=============================================================================

typedef struct _LABELED_BIT
{
    BYTE    BitNumber;          //... Bit number (starts at 0, upto 256 bits).
    LPSTR   LabelOff;           //... Label for bit = 0
    LPSTR   LabelOn;            //... Label for bit = 1
} LABELED_BIT;

typedef LABELED_BIT *LPLABELED_BIT;

//=============================================================================
//  TYPED_STRING structure
//=============================================================================

#define TYPED_STRING_NORMAL     1
#define TYPED_STRING_UNICODE    2

#define TYPED_STRING_EXFLAG     1

typedef struct _TYPED_STRING
{
    BYTE    StringType:7;   // defined above
    BYTE    fStringEx:1;    // we are always Ex... so this is how we ExEx
    LPSTR   lpString;       // the actual string
    BYTE    Byte[0];        // if instEx, then the data would go here.
} TYPED_STRING;

typedef TYPED_STRING *LPTYPED_STRING;

//=============================================================================
//  OBJECT_IDENTIFIER structure
//=============================================================================

typedef struct _OBJECT_IDENTIFIER
{
    DWORD   Length;			// Number of identifiers in the OID
    LPDWORD	lpIdentifier;	// Array of Identifiers
} OBJECT_IDENTIFIER;

typedef OBJECT_IDENTIFIER *LPOBJECT_IDENTIFIER;


//=============================================================================
//  Set structure.
//=============================================================================

typedef struct _SET
{
    DWORD   nEntries;

    union
    {
        //... set of values

        LPVOID                  lpVoidTable;                    // set of anything.
        LPBYTE                  lpByteTable;                    // set of bytes
        LPWORD                  lpWordTable;                    // set of words
        LPDWORD                 lpDwordTable;                   // set of dwords
        LPLARGEINT              lpLargeIntTable;                // set of LARGEINT structures
        LPSYSTEMTIME            lpSystemTimeTable;              // set of SYSTEMTIME structures

        //... set of labeled values

        LPLABELED_BYTE          lpLabeledByteTable;             // set of labeled_byte structs
        LPLABELED_WORD          lpLabeledWordTable;             // set of labeled_word structs
        LPLABELED_DWORD         lpLabeledDwordTable;            // set of labeled_dword structs
        LPLABELED_LARGEINT      lpLabeledLargeIntTable;         // set of Labeled_LARGEINT structs
        LPLABELED_SYSTEMTIME    lpLabeledSystemTimeTable;       // set of labeled_systemtime structs
        LPLABELED_BIT           lpLabeledBit;                   // set of labeled_bit structs.
    };
} SET;

typedef SET *LPSET;

//=============================================================================
//  String table.
//=============================================================================

typedef struct _STRINGTABLE
{
    DWORD           nStrings;               // number LPSTR in table
    LPSTR           String[0];
} STRINGTABLE;

typedef STRINGTABLE *LPSTRINGTABLE;

#define STRINGTABLE_SIZE    sizeof(STRINGTABLE)

//=============================================================================
//  RECOGNIZEDATA structure.
//
//  This structure to keep track of the start of each recognized protocol.
//=============================================================================

typedef struct _RECOGNIZEDATA
{
    WORD        ProtocolID;         //... Protocol which was recognized
    WORD        nProtocolOffset;    //... Offset from the start of the frame of the start of this protocol.
    LPVOID      InstData;           //... Opaque, for protocol only.
} RECOGNIZEDATA;

typedef RECOGNIZEDATA * LPRECOGNIZEDATA;

//=============================================================================
//  RECOGNIZEDATATABLE structure.
//
//  This structure to keep track of the start of each RECOGNIZEDATA structure
//=============================================================================

typedef struct _RECOGNIZEDATATABLE
{
    WORD            nRecognizeDatas;    //... number of RECOGNIZEDATA structures
    RECOGNIZEDATA   RecognizeData[0];   //... array of RECOGNIZEDATA structures follows
} RECOGNIZEDATATABLE;

typedef RECOGNIZEDATATABLE * LPRECOGNIZEDATATABLE;

//=============================================================================
//  Property information structure.
//=============================================================================

typedef struct _PROPERTYINFO
{
    HPROPERTY       hProperty;      //... Handle to the property.
    DWORD           Version;        //... Version of property.
    LPSTR           Label;          //... name of property
    LPSTR           Comment;        //... description of property
    BYTE            DataType;       //... data type of property
    BYTE            DataQualifier;  //... data qualifier of property

    union
    {
        LPVOID          lpExtendedInfo; //... generic pointer.
        LPRANGE         lpRange;        //... pointer to range
        LPSET           lpSet;          //... pointer to set
        DWORD           Bitmask;        //... bitmask to apply
        DWORD           Value;          //... constant value.
    };

    WORD            FormatStringSize;   //... max size to reserve for text description
    LPVOID          InstanceData;       //... property-specific instance data.
} PROPERTYINFO;

typedef PROPERTYINFO *LPPROPERTYINFO;

#define PROPERTYINFO_SIZE   sizeof(PROPERTYINFO)


//=============================================================================
//  Property instance Extended structure.
//=============================================================================

typedef struct _PROPERTYINSTEX
{
    WORD        Length;         //... length of raw data in frame
    WORD        LengthEx;       //... number of bytes following
    ULPVOID     lpData;         //... pointer to raw data in frame

    union
    {
        BYTE            Byte[];     //... table of bytes follows
        WORD            Word[];     //... table of words follows
        DWORD           Dword[];    //... table of Dwords follows
        LARGE_INTEGER   LargeInt[]; //... table of LARGEINT structures to follow
        SYSTEMTIME      SysTime[];  //... table of SYSTEMTIME structures follows
        TYPED_STRING    TypedString;//... a typed_string that may have extended data
    };
} PROPERTYINSTEX;

typedef PROPERTYINSTEX *LPPROPERTYINSTEX;

#define PROPERTYINSTEX_SIZE     sizeof(PROPERTYINSTEX)

typedef PROPERTYINSTEX UNALIGNED *ULPPROPERTYINSTEX;

//=============================================================================
//  Property instance structure.
//=============================================================================

typedef struct _PROPERTYINST
{
    LPPROPERTYINFO          lpPropertyInfo;     // pointer to property info
    LPSTR                   szPropertyText;     // pointer to string description

    union
    {
        LPVOID              lpData;             // pointer to data
        LPBYTE              lpByte;             // bytes
        ULPWORD             lpWord;             // words
        ULPDWORD            lpDword;            // dwords

        ULPLARGEINT         lpLargeInt;         // LargeInt
        ULPSYSTEMTIME       lpSysTime;          // pointer to SYSTEMTIME structures
        LPPROPERTYINSTEX    lpPropertyInstEx;   // pointer to propertyinstex (if DataLength = -1)
    };

    WORD                    DataLength;         // length of data, or flag for propertyinstex struct
    WORD                    Level   : 4  ;      // level information        ............1111
    WORD                    HelpID  : 12 ;      // context ID for helpfile  111111111111....
                     //    ---------------
                     // total of 16 bits == 1 WORD == DWORD ALIGNED structure
                            // Interpretation Flags:  Flags that define attach time information to the
                            // interpretation of the property.  For example, in RPC, the client can be
                            // Intel format and the server can be non-Intel format... thus the property
                            // database cannot describe the property at database creation time.
    DWORD                   IFlags;
} PROPERTYINST;

typedef PROPERTYINST *LPPROPERTYINST;

#define PROPERTYINST_SIZE   sizeof(PROPERTYINST)



// Flags passed at AttachPropertyInstance and AttachPropertyInstanceEx time in the IFlags field:
// flag for error condition ...............1
#define IFLAG_ERROR     0x00000001
// is the WORD or DWORD byte non-Intel format at attach time?
#define IFLAG_SWAPPED   0x00000002
// is the STRING UNICODE at attach time?
#define IFLAG_UNICODE   0x00000004


//=============================================================================
//  Property instance table structure.
//=============================================================================

typedef struct _PROPERTYINSTTABLE
{
    WORD                nPropertyInsts;     //... number of items
    WORD                nPropertyInstIndex; //... index to first item
} PROPERTYINSTTABLE;

typedef PROPERTYINSTTABLE *LPPROPERTYINSTTABLE;

#define PROPERTYINSTTABLE_SIZE  sizeof(PROPERTYINSTTABLE)

//=============================================================================
//  Property table structure.
//=============================================================================

typedef struct _PROPERTYTABLE
{
    LPVOID                  lpFormatBuffer;             //... Opaque.                       (PRIVATE)
    DWORD                   FormatBufferLength;         //... Opaque.                       (PRIVATE)
    DWORD                   nTotalPropertyInsts;        //... total number of propertyinstances in array
    LPPROPERTYINST          lpFirstPropertyInst;        //... array of property instances
    BYTE                    nPropertyInstTables;        //... total PropertyIndexTables following
    PROPERTYINSTTABLE       PropertyInstTable[0];       //... array of propertyinstance index table structures
} PROPERTYTABLE;

typedef PROPERTYTABLE *LPPROPERTYTABLE;

#define PROPERTYTABLE_SIZE  sizeof(PROPERTYTABLE)

//=============================================================================
//  Protocol entry points.
//=============================================================================

typedef VOID    (WINAPI *REGISTER)(HPROTOCOL);

typedef VOID    (WINAPI *DEREGISTER)(HPROTOCOL);

typedef LPBYTE  (WINAPI *RECOGNIZEFRAME)(HFRAME, LPBYTE, LPBYTE, DWORD, DWORD, HPROTOCOL, DWORD, LPDWORD, LPHPROTOCOL, LPDWORD);

typedef LPBYTE  (WINAPI *ATTACHPROPERTIES)(HFRAME, LPBYTE, LPBYTE, DWORD, DWORD, HPROTOCOL, DWORD, DWORD);

typedef DWORD   (WINAPI *FORMATPROPERTIES)(HFRAME, LPBYTE, LPBYTE, DWORD, LPPROPERTYINST);

//=============================================================================
//  Protocol entry point structure.
//=============================================================================

typedef struct _ENTRYPOINTS
{
    REGISTER            Register;               //... Protocol Register() entry point.
    DEREGISTER          Deregister;             //... Protocol Deregister() entry point.
    RECOGNIZEFRAME      RecognizeFrame;         //... Protocol RecognizeFrame() entry point.
    ATTACHPROPERTIES    AttachProperties;       //... Protocol AttachProperties() entry point.
    FORMATPROPERTIES    FormatProperties;       //... Protocol FormatProperties() entry point.
} ENTRYPOINTS;

typedef ENTRYPOINTS *LPENTRYPOINTS;

#define ENTRYPOINTS_SIZE    sizeof(ENTRYPOINTS)

//=============================================================================
//  Property database structure.
//=============================================================================

typedef struct _PROPERTYDATABASE
{
    DWORD           nProperties;                 //... Number of properties in database.
    LPPROPERTYINFO  PropertyInfo[0];             //... Array of property info pointers.
} PROPERTYDATABASE;


#define PROPERTYDATABASE_SIZE   sizeof(PROPERTYDATABASE)

typedef PROPERTYDATABASE *LPPROPERTYDATABASE;

//=============================================================================
//  Protocol info structure (PUBLIC portion of HPROTOCOL).
//=============================================================================

typedef struct _PROTOCOLINFO
{
    DWORD               ProtocolID;             //... Prootocol ID of owning protocol.
    LPPROPERTYDATABASE  PropertyDatabase;       //... Property database.
    BYTE                ProtocolName[16];       //... Protocol name.
    BYTE                HelpFile[16];           //... Optional helpfile name.
    BYTE                Comment[128];           //... Comment describing protocol.
} PROTOCOLINFO;

typedef PROTOCOLINFO *LPPROTOCOLINFO;

#define PROTOCOLINFO_SIZE   sizeof(PROTOCOLINFO)

//=============================================================================
//  Protocol Table.
//=============================================================================

typedef struct _PROTOCOLTABLE
{
    DWORD       nProtocols;
    HPROTOCOL   hProtocol[1];                       //... This must be the last member.
} PROTOCOLTABLE;

typedef PROTOCOLTABLE *LPPROTOCOLTABLE;

#define PROTOCOLTABLE_SIZE  (sizeof(PROTOCOLTABLE) - sizeof(HPROTOCOL))

#define PROTOCOLTABLE_ACTUAL_SIZE(p) GetTableSize(PROTOCOLTABLE_SIZE, (p)->nProtocols, sizeof(HPROTOCOL))

//=============================================================================
//  AddressInfo structure
//=============================================================================
#define SORT_BYADDRESS  0
#define SORT_BYNAME     1

#define PERMANENT_NAME  0x00000100

typedef struct _ADDRESSINFO *LPADDRESSINFO;
typedef struct _ADDRESSINFO
{
    ADDRESS        Address;
    BYTE           Name[MAX_NAME_SIZE];
	DWORD          Flags;
    LPVOID         lpAddressInstData;
} ADDRESSINFO;

#define ADDRESSINFO_SIZE    sizeof(ADDRESSINFO)

//=============================================================================
//  AddressInfoTable
//=============================================================================

typedef struct _ADDRESSINFOTABLE
{
    DWORD         nAddressInfos;
    LPADDRESSINFO lpAddressInfo[0];
} ADDRESSINFOTABLE;

typedef ADDRESSINFOTABLE *LPADDRESSINFOTABLE;

#define ADDRESSINFOTABLE_SIZE   sizeof(ADDRESSINFOTABLE)

//=============================================================================
//  callback procedures.
//=============================================================================

typedef DWORD (WINAPI *FILTERPROC)(HCAPTURE, HFRAME, LPVOID);

#pragma pack()
#endif
