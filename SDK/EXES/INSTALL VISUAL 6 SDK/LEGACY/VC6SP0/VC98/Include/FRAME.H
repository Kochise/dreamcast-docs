
//=============================================================================
//  Microsoft (R) Bloodhound (tm). Copyright (C) 1991-1992.
//
//  MODULE: frame.h
//=============================================================================

#if !defined(_FRAME_)

#define _FRAME_

#pragma pack(1)

#define MAX_ADDR_LENGTH     6

//=============================================================================
//  802.3 and ETHERNET MAC structure.
//=============================================================================

typedef struct _ETHERNET
{
    BYTE    DstAddr[MAX_ADDR_LENGTH];   //... destination address.
    BYTE    SrcAddr[MAX_ADDR_LENGTH];   //... source address.
    union
    {
        WORD    Length;                 //... 802.3 length field.
        WORD    Type;                   //... Ethernet type field.
    };
    BYTE    Info[0];                    //... information field.
} ETHERNET;

typedef ETHERNET *LPETHERNET;

typedef ETHERNET UNALIGNED *ULPETHERNET;

#define ETHERNET_SIZE   sizeof(ETHERNET)

#define ETHERNET_HEADER_LENGTH  14

#define ETHERNET_DATA_LENGTH    0x05DC  //... 1500. Max ethernet data length.
#define ETHERNET_FRAME_LENGTH   0x05EA  //... 1514. Max ethernet frame length.
#define ETHERNET_FRAME_TYPE     0x0600  //... 1536. First ethernet type assigned.

//=============================================================================
//  802.5 (TOKENRING) MAC structure.
//=============================================================================

typedef struct _TOKENRING
{
    BYTE    AccessCtrl;                 //... access control field.
    BYTE    FrameCtrl;                  //... frame control field.
    BYTE    DstAddr[MAX_ADDR_LENGTH];   //... destination address.
    BYTE    SrcAddr[MAX_ADDR_LENGTH];   //... source address.
    union
    {
        BYTE    Info[0];                //... information field.
        WORD    RoutingInfo[0];         //... routing information field.
    };
} TOKENRING;

typedef TOKENRING *LPTOKENRING;
typedef TOKENRING UNALIGNED *ULPTOKENRING;

#define TOKENRING_SIZE  sizeof(TOKENRING)

#define TOKENRING_HEADER_LENGTH     14

#define TOKENRING_SA_ROUTING_INFO   0x0080
#define TOKENRING_SA_LOCAL          0x0040

#define TOKENRING_DA_LOCAL          0x0040
#define TOKENRING_DA_GROUP          0x0080

#define TOKENRING_RC_LENGTHMASK     0x001F
#define TOKENRING_BC_MASK           0x00E0

#define TOKENRING_TYPE_MAC          0x0000  //... MAC frame.
#define TOKENRING_TYPE_LLC          0x0040  //... LLC frame.

//=============================================================================
//  FDDI MAC structure.
//=============================================================================

typedef struct _FDDI
{
    BYTE    FrameCtrl;                  //... frame control field.
    BYTE    DstAddr[MAX_ADDR_LENGTH];   //... destination address.
    BYTE    SrcAddr[MAX_ADDR_LENGTH];   //... source address.
    BYTE    Info[0];                    //... information field.
} FDDI;

#define FDDI_SIZE       sizeof(FDDI)

typedef FDDI *LPFDDI;
typedef FDDI UNALIGNED *ULPFDDI;

#define FDDI_HEADER_LENGTH  13

#define FDDI_TYPE_MAC               0x00  //... MAC frame.
#define FDDI_TYPE_LLC               0x10  //... LLC frame.
#define FDDI_TYPE_LONG_ADDRESS      0x40  //... 48-bit address

//=============================================================================
//  LLC (802.2)
//=============================================================================

typedef struct _LLC
{
    BYTE    dsap;
    BYTE    ssap;

    struct
    {
        union
        {
            BYTE Command;
            BYTE NextSend;
        };

        union
        {
            BYTE NextRecv;
            BYTE Data[1];
        };
    } ControlField;
} LLC;

typedef LLC *LPLLC;
typedef LLC UNALIGNED *ULPLLC;

#define LLC_SIZE    sizeof(LLC);

//=============================================================================
//  Helper macros.
//=============================================================================

#define IsRoutingInfoPresent(f) ((((ULPTOKENRING) (f))->SrcAddr[0] & TOKENRING_SA_ROUTING_INFO) ? TRUE : FALSE)

#define GetRoutingInfoLength(f) (IsRoutingInfoPresent(f) \
                                 ? (((ULPTOKENRING) (f))->RoutingInfo[0] & TOKENRING_RC_LENGTHMASK) : 0)

#pragma pack()
#endif
