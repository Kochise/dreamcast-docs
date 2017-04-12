
//=============================================================================
//  Microsoft Bloodhound. Copyright (C) 1991-1998.
//
//  MODULE: naltypes.h
//
//  This source file contains defintions for the Network Abstraction Layer (NAL).
//
//  NOTE: Do not make changes to this file unless you mahe changes to the
//        NDIS 2.0 driver header files. There are masm equivalents to change.
//=============================================================================

#include "buffer.h"                             //... Include buffer definitions.
#include "bherr.h"                              //... Bloodhound error codes.
#include "neterr.h"                             //... Network Topology error codes
#include "queue.h"                              //... Queuing functions.

#if !defined(_NALTYPES_)

#define _NALTYPES_

#pragma pack(1)

//=============================================================================
//  NETWORK_MESSAGE_TRIGGER_COMPLETE:
//
//  param1  =  Trigger structure.
//  param2  =  Nothing.
//=============================================================================

#define NETWORK_MESSAGE_TRIGGER_COMPLETE        0

//=============================================================================
//  NETWORK_MESSAGE_TRANSMIT_COMPLETE:
//
//  param1  =  Transmit statistics.
//  param2  =  Packet queue.
//=============================================================================

#define NETWORK_MESSAGE_TRANSMIT_COMPLETE       1

//=============================================================================
//  NETWORK_MESSAGE_RESET_STATE:
//
//  param1  =  RESET_COMPLETE     reset, current net handle now invalid
//             RESET_OPEN         reset, current net handle still valid
//  param2  =  Packet queue.
//=============================================================================

#define NETWORK_MESSAGE_RESET_STATE             2

#define RESET_COMPLETE                          0
#define RESET_OPEN                              1

//=============================================================================
//  NETWORK_MESSAGE_BH_ERROR
//
//  param1  =  BHERR ERROR CODE 
//  param2  =  LPSTR Description (optional pointer to description of error)
//=============================================================================

#define NETWORK_MESSAGE_BH_ERROR                3

//=============================================================================
//  NETWORK_MESSAGE_NETWORK_ERROR
//
//  param1  =  MacType (EtherNet, TokenRing, FDDI, etc.)
//  param2  =  NETERR_ error code (specific to topology)
//=============================================================================

#define NETWORK_MESSAGE_NETWORK_ERROR           4

//=============================================================================
//  The network handle.
//=============================================================================

#ifndef MAKE_IDENTIFIER
#define MAKE_IDENTIFIER(a, b, c, d)     ((DWORD) MAKELONG(MAKEWORD(a, b), MAKEWORD(c, d)))
#endif

typedef struct _NETWORK         *HNETWORK;

#define HANDLE_TYPE_NETWORK     MAKE_IDENTIFIER('N', 'E', 'T', '$')

//=============================================================================
//  NETWORKSTATE data structure.
//=============================================================================

typedef struct _NETWORKSTATUS
{
    DWORD       State;                                      //... Current state.
    DWORD       Flags;                                      //... Current flags.
    DWORD       TriggerAction;                              //... Trigger action.
    DWORD       TriggerOpcode;                              //... Trigger opcode.
    DWORD       TriggerState;                               //... Trigger state.
    DWORD       BufferSize;                                 //... Capture buffer size.
} NETWORKSTATUS;

typedef NETWORKSTATUS *LPNETWORKSTATUS;

#define NETWORKSTATUS_SIZE   sizeof(NETWORKSTATUS)

#define NETWORKSTATUS_STATE_VOID                0           //... Nothing state.
#define NETWORKSTATUS_STATE_INIT                1           //... Initial state.
#define NETWORKSTATUS_STATE_READY               2           //... Ready state.
#define NETWORKSTATUS_STATE_CAPTURING           3           //... Capturing state.
#define NETWORKSTATUS_STATE_PAUSED              4           //... Paused state.

#define NETWORKSTATUS_FLAGS_TRIGGER_PENDING     0x0001      //... Trigger pending.

//=============================================================================
//  General constants.
//=============================================================================

#define MAC_TYPE_UNKNOWN                        0           //... not supported
#define MAC_TYPE_ETHERNET                       1           //... ethernet and 802.3
#define MAC_TYPE_TOKENRING                      2           //... tokenring (802.5)
#define MAC_TYPE_FDDI                           3           //... fddi.

#define MACHINE_NAME_LENGTH                     16
#define USER_NAME_LENGTH                        32
#define ADAPTER_COMMENT_LENGTH                  32

#define CLOSE_FLAGS_CLOSE                       0x0000
#define CLOSE_FLAGS_SUSPEND                     0x0001

//=============================================================================
//  NAL error codes.
//=============================================================================

#define NAL_SUCCESS                          BHERR_SUCCESS
#define NAL_INVALID_NETWORK_ID               BHERR_INVALID_NETWORK_ID
#define NAL_INVALID_HNETCONTEXT              BHERR_INVALID_HNETWORK
#define NAL_OUT_OF_MEMORY                    BHERR_OUT_OF_MEMORY
#define NAL_NETWORK_BUSY                     BHERR_NETWORK_BUSY
#define NAL_INVALID_HBUFFER                  BHERR_INVALID_HBUFFER
#define NAL_INVALID_PACKET_LENGTH            BHERR_INVALID_PACKET_LENGTH
#define NAL_TRANSMIT_ERROR                   BHERR_TRANSMIT_ERROR
#define NAL_CAPTURE_PAUSED                   BHERR_CAPTURE_PAUSED
#define NAL_CAPTURE_NOT_PAUSED               BHERR_CAPTURE_NOT_PAUSED
#define NAL_CAPTURE_STARTED                  BHERR_CAPTURING
#define NAL_CAPTURE_NOT_STARTED              BHERR_NOT_CAPTURING
#define NAL_MSDOS_DRIVER_NOT_LOADED          BHERR_MSDOS_DRIVER_NOT_LOADED
#define NAL_WINDOWS_DRIVER_NOT_LOADED        BHERR_WINDOWS_DRIVER_NOT_LOADED
#define NAL_MSDOS_DRIVER_INIT_FAILURE        BHERR_MSDOS_DRIVER_INIT_FAILURE
#define NAL_WINDOWS_DRIVER_INIT_FAILURE      BHERR_WINDOWS_DRIVER_INIT_FAILURE
#define NAL_PROMISCUOUS_MODE_NOT_SUPPORTED   BHERR_PROMISCUOUS_MODE_NOT_SUPPORTED
#define NAL_MAC_DRIVER_OPEN_FAILURE          BHERR_MAC_DRIVER_OPEN_FAILURE
#define NAL_PENDING                          BHERR_PENDING
#define NAL_INTERNAL_EXCEPTION               BHERR_INTERNAL_EXCEPTION

//=============================================================================
//  Trigger codes.
//=============================================================================

#define TRIGGER_OFF                                     0
#define TRIGGER_ON_PATTERN_MATCH                        1
#define TRIGGER_ON_BUFFER_CONTENT                       2
#define TRIGGER_ON_PATTERN_MATCH_THEN_BUFFER_CONTENT    3
#define TRIGGER_ON_BUFFER_CONTENT_THEN_PATTERN_MATCH    4

#define TRIGGER_STATE_NOTHING                           0
#define TRIGGER_STATE_STOP_CAPTURE                      1
#define TRIGGER_STATE_PAUSE_CAPTURE                     2

#define TRIGGER_ACTION_NOTIFY                           0
#define TRIGGER_ACTION_EXECUTE_COMMAND                  1

//=============================================================================
//  Handle defintions.
//=============================================================================

typedef LPVOID HNETCONTEXT;

//=============================================================================
//  Transmit statistics structure.
//=============================================================================

typedef struct _TRANSMITSTATS
{
    DWORD       TotalFramesSent;
    DWORD       TotalBytesSent;
    DWORD       TotalTransmitErrors;
} TRANSMITSTATS;

typedef TRANSMITSTATS *LPTRANSMITSTATS;

#define TRANSMITSTATS_SIZE   sizeof(TRANSMITSTATS)

//=============================================================================
//  Statistics structure.
//=============================================================================

typedef struct _STATISTICS
{
    //=========================================================================
    //  Statistics kept by BH driver.
    //=========================================================================

    DWORD           TimeElapsed;

    //...           Buffered statistics

    DWORD           TotalFramesCaptured;
    DWORD           TotalBytesCaptured;

    //...           Filtered statistics

    DWORD           TotalFramesFiltered;
    DWORD           TotalBytesFiltered;

    //...           Overall statistics.

    DWORD           TotalFramesSeen;
    DWORD           TotalBytesSeen;

    DWORD           TotalMulticastsReceived;
    DWORD           TotalBroadcastsReceived;

    DWORD           TotalFramesDropped;
    DWORD           TotalFramesDroppedFromBuffer;

    //=========================================================================
    //  Statistics kept by MAC driver.
    //=========================================================================


    DWORD           MacFramesReceived;
    DWORD           MacCRCErrors;

    union
    {
        DWORD           MacBytesReceived;
        LARGE_INTEGER   MacBytesReceivedEx;
    };

    DWORD           MacFramesDropped_NoBuffers;
    DWORD           MacMulticastsReceived;
    DWORD           MacBroadcastsReceived;
    DWORD           MacFramesDropped_HwError;
} STATISTICS;

typedef STATISTICS *LPSTATISTICS;

#define STATISTICS_SIZE   sizeof(STATISTICS)

//=============================================================================
//  Protocol statistics structure.
//=============================================================================

typedef struct _PROTOCOLSTAT
{
    DWORD       ProtocolID;
    DWORD       ProtocolFramesCaptured;
    DWORD       ProtocolBytesCaptured;
} PROTOCOLSTAT;

typedef PROTOCOLSTAT *LPPROTOCOLSTAT;

#define PROTOCOLSTAT_SIZE   sizeof(PROTOCOLSTAT)

typedef struct _PROTOCOL_STATISTICS_TABLE
{
    DWORD           nProtocols;
    LPPROTOCOLSTAT  ProtocolStatistic;
} PROTOCOL_STATISTICS_TABLE;

typedef PROTOCOL_STATISTICS_TABLE *LPPROTOCOL_STATISTICS_TABLE;

#define PROTOCOL_STATISTIC_TABLE_SIZE   sizeof(PROTOCOL_STATISTICS_TABLE)

//=============================================================================
//  Packet data structure.
//=============================================================================

typedef struct _PACKET *LPPACKET;

typedef struct _PACKET
{
    LPBYTE      Frame;                      //... Pointer to entire MAC frame.
    LPVOID      FrameMdl;                   //... Driver-level frame pointer.
    WORD	FrameSize;		    //... Length of frame.
    WORD	ReferenceCount; 	    //... Number of frame references (lock count).
    DWORD       TimeStamp;                  //... Timestamp of frame.
} PACKET;

#define PACKET_SIZE  sizeof(PACKET)

//=============================================================================
//  StatFrame type.
//=============================================================================

typedef struct _FRAMEHDR
{
    BYTE    SrcAddress[6];
    BYTE    DstAddress[6];
    WORD    Length;
    BYTE    DSAP;
    BYTE    SSAP;
    BYTE    Control;
    BYTE    ProtocolID[3];
    WORD    EtherType;
} FRAMEHDR;

typedef struct _TRFRAMEHDR
{
    BYTE    AC;
    BYTE    FC;
    BYTE    SrcAddress[6];
    BYTE    DstAddress[6];
    BYTE    DSAP;
    BYTE    SSAP;
    BYTE    Control;
    BYTE    ProtocolID[3];
    WORD    EtherType;
} TRFRAMEHDR;

#define DEFAULT_AC          0x00
#define DEFAULT_FC          0x40
#define DEFAULT_SAP         0xAA
#define DEFAULT_CONTROL     0x03
#define DEFAULT_ETHERTYPE   0x8419

typedef struct _FDDIFRAMEHDR
{
    BYTE    FC;
    BYTE    SrcAddress[6];
    BYTE    DstAddress[6];
    BYTE    DSAP;
    BYTE    SSAP;
    BYTE    Control;
    BYTE    ProtocolID[3];
    WORD    EtherType;
} FDDIFRAMEHDR;
#define DEFAULT_FDDIFC      0x10

typedef struct _FDDISTATFRAME
{
    DWORD       TimeStamp;          //... Relative time in milliseconds.
    WORD        FrameLength;        //... MAC frame length.
    WORD        nBytesAvail;        //... Actual frame length copied.
    FDDIFRAMEHDR  FrameHeader;
    BYTE        FrameID[4];         //... "$MST"
    DWORD       Flags;              //... Flags
    DWORD       FrameType;          //... Statistics is always 103 (0x67)
    WORD        StatsDataLen;       //... Length of Version DWORD + STATISTICS
    DWORD       StatsVersion;
    STATISTICS  Statistics;
} FDDISTATFRAME;

typedef FDDISTATFRAME *LPFDDISTATFRAME;
typedef FDDISTATFRAME UNALIGNED *ULPFDDISTATFRAME;

#define FDDISTATFRAME_SIZE  sizeof(FDDISTATFRAME)

typedef struct _TRSTATFRAME
{
    DWORD       TimeStamp;          //... Relative time in milliseconds.
    WORD        FrameLength;        //... MAC frame length.
    WORD        nBytesAvail;        //... Actual frame length copied.
    TRFRAMEHDR  FrameHeader;
    BYTE        FrameID[4];         //... "$MST"
    DWORD       Flags;              //... Flags
    DWORD       FrameType;          //... Statistics is always 103 (0x67)
    WORD        StatsDataLen;       //... Length of Version DWORD + STATISTICS
    DWORD       StatsVersion;
    STATISTICS  Statistics;
} TRSTATFRAME;

typedef TRSTATFRAME *LPTRSTATFRAME;
typedef TRSTATFRAME UNALIGNED *ULPTRSTATFRAME;

#define TRSTATFRAME_SIZE  sizeof(TRSTATFRAME)

typedef struct _STATFRAME
{
    DWORD       TimeStamp;          //... Relative time in milliseconds.
    WORD        FrameLength;        //... MAC frame length.
    WORD        nBytesAvail;        //... Actual frame length copied.
    FRAMEHDR    FrameHeader;
    BYTE        FrameID[4];         //... "$MST"
    DWORD       Flags;              //... Flags
    DWORD       FrameType;          //... Statistics is always 103 (0x67)
    WORD        StatsDataLen;       //... Length of Version DWORD + STATISTICS
    DWORD       StatsVersion;
    STATISTICS  Statistics;
} STATFRAME;


#define STATISTICS_VERSION  0x00000000

typedef STATFRAME *LPSTATFRAME;
typedef STATFRAME UNALIGNED *ULPSTATFRAME;

#define STATFRAME_SIZE  sizeof(STATFRAME)


//=============================================================================
//  The network procedure type.
//
//  Syntax:
//
//  DWORD CALLBACK NetworkProc(handle, message, status, UserContext, param1, param2).
//=============================================================================

typedef DWORD (WINAPI *NETWORKPROC)(HNETWORK, DWORD, DWORD, LPVOID, LPVOID, LPVOID);


//=============================================================================
//  Packet queue data structure.
//=============================================================================

typedef struct _PACKETQUEUE *LPPACKETQUEUE;

typedef struct _PACKETQUEUE
{
    //=========================================================================
    //  The following members are set by the NAL interface and
    //  must be NOT used by the Bloodhound kernel or applications.
    //=========================================================================

    LINK            QueueLinkage;               //... Queue linkage (used by Bloodhound drivers).
    DWORD           State;                      //... Transmit complete flag (used by Bloodhound drivers).
    DWORD           Status;                     //... Final Bloodhound error code (used by Bloodhound drivers).
    LPVOID          TimerHandle;                //... Handle to timer or pending transmits (used by Bloodhound drivers).
    HANDLE          hNetwork;                   //... Network handle (set by NAL).
    LPVOID          InstData;                   //... OpenNetwork instance data.

    //=========================================================================
    //  The following members are set by NAL applications, such as the Bloodhound
    //  kernel.
    //=========================================================================

    DWORD           Size;                       //... The overall size in bytes.
    DWORD           FrameTimeDelta;             //... Time between frames (-1 means use frame timestamp).
    DWORD           QueueTimeDelta;             //... Time between queues.
    DWORD           IterationCount;             //... Number of times to repeat send sequence.
    TRANSMITSTATS   TransmitStats;              //... Transmit statistics structure.
    NETWORKPROC     NetworkProc;                //... Network procedure, used by the kernel to hook transmit completions.

    //=========================================================================
    //  The actual list of packets to transmit.
    //=========================================================================

    DWORD           nPackets;                   //... Packet queue length (i.e. number of frames to send).
    PACKET          Packet[0];                  //... Packet queue.
} PACKETQUEUE;

#define PACKETQUEUE_SIZE  sizeof(PACKETQUEUE)

#define PACKETQUEUE_STATE_VOID          0
#define PACKETQUEUE_STATE_PENDING       1
#define PACKETQUEUE_STATE_COMPLETE      2
#define PACKETQUEUE_STATE_CANCEL        3

//=============================================================================
//  Address structures
//=============================================================================

#define MAX_NAME_SIZE                   32
#define IP_ADDRESS_SIZE                 4
#define MAC_ADDRESS_SIZE                6

//      What is the maximum address size that we could have to copy?
//      IPX == DWORD + 6 bytes == 10
#define MAX_ADDRESS_SIZE                                10

//  VINES IP ADDRESS

typedef struct _VINES_IP_ADDRESS
{
    DWORD   NetID;
    WORD    SubnetID;
} VINES_IP_ADDRESS;

typedef VINES_IP_ADDRESS *LPVINES_IP_ADDRESS;

#define VINES_IP_ADDRESS_SIZE sizeof(VINES_IP_ADDRESS)

// ... IPX address

typedef struct _IPX_ADDRESS
{
    BYTE    Subnet[4];
    BYTE    Address[6];
} IPX_ADDRESS;

typedef IPX_ADDRESS *LPIPX_ADDRESS;

#define IPX_ADDRESS_SIZE sizeof(IPX_ADDRESS)

//... XNS address

typedef IPX_ADDRESS XNS_ADDRESS;

typedef IPX_ADDRESS *LPXNS_ADDRESS;

// ... ETHERNET SOURCE ADDRESS

typedef struct _ETHERNET_SRC_ADDRESS
{
    BYTE    RoutingBit:     1;
    BYTE    LocalBit:       1;
    BYTE    Byte0:          6;
    BYTE    Reserved[5];
} ETHERNET_SRC_ADDRESS;

typedef ETHERNET_SRC_ADDRESS *LPETHERNET_SRC_ADDRESS;

// ... ETHERNET DESTINATION ADDRESS

typedef struct _ETHERNET_DST_ADDRESS
{
    BYTE    GroupBit:       1;
    BYTE    AdminBit:       1;
    BYTE    Byte0:          6;
    BYTE    Reserved[5];
} ETHERNET_DST_ADDRESS;

typedef ETHERNET_DST_ADDRESS *LPETHERNET_DST_ADDRESS;

// ... FDDI addresses
typedef ETHERNET_SRC_ADDRESS FDDI_SRC_ADDRESS;
typedef ETHERNET_DST_ADDRESS FDDI_DST_ADDRESS;

typedef FDDI_SRC_ADDRESS *LPFDDI_SRC_ADDRESS;
typedef FDDI_DST_ADDRESS *LPFDDI_DST_ADDRESS;

// .... TOKENRING Source Address

typedef struct _TOKENRING_SRC_ADDRESS
{
    BYTE    Byte0:          6;
    BYTE    LocalBit:       1;
    BYTE    RoutingBit:     1;
    BYTE    Byte1;
    BYTE    Byte2:          7;
    BYTE    Functional:     1;
    BYTE    Reserved[3];
} TOKENRING_SRC_ADDRESS;

typedef TOKENRING_SRC_ADDRESS *LPTOKENRING_SRC_ADDRESS;

// .... TOKENRING Destination Address

typedef struct _TOKENRING_DST_ADDRESS
{
    BYTE    Byte0:          6;
    BYTE    AdminBit:       1;
    BYTE    GroupBit:       1;
    BYTE    Reserved[5];
} TOKENRING_DST_ADDRESS;

typedef TOKENRING_DST_ADDRESS *LPTOKENRING_DST_ADDRESS;

//... Old type def's

#define MACADDRESS_SIZE     MAC_ADDRESS_SIZE
#define IPADDRESS_SIZE      IP_ADDRESS_SIZE
#define IPXADDRESS_SIZE     IPX_ADDRESS_SIZE
#define VINESIPADDRESS_SIZE VINES_IP_ADDRESS_SIZE

typedef struct _ADDRESS
{
    DWORD                       Type;

    union
    {
        BYTE                    MACAddress[MAC_ADDRESS_SIZE];

        BYTE                    IPAddress[IP_ADDRESS_SIZE];

        BYTE                    IPXRawAddress[IPX_ADDRESS_SIZE];
        IPX_ADDRESS             IPXAddress;
        
        BYTE                    VinesIPRawAddress[VINES_IP_ADDRESS_SIZE];
        VINES_IP_ADDRESS        VinesIPAddress;       

        ETHERNET_SRC_ADDRESS    EthernetSrcAddress;
        ETHERNET_DST_ADDRESS    EthernetDstAddress;

        TOKENRING_SRC_ADDRESS   TokenringSrcAddress;
        TOKENRING_DST_ADDRESS   TokenringDstAddress;

        FDDI_SRC_ADDRESS        FddiSrcAddress;
        FDDI_DST_ADDRESS        FddiDstAddress;
    };

    WORD                        Flags;
} ADDRESS;

typedef ADDRESS *LPADDRESS;

#define ADDRESS_SIZE    sizeof(ADDRESS)

#define ADDRESS_TYPE_ETHERNET   0
#define ADDRESS_TYPE_IP         1
#define ADDRESS_TYPE_IPX        2
#define ADDRESS_TYPE_TOKENRING  3
#define ADDRESS_TYPE_FDDI       4
#define ADDRESS_TYPE_XNS        5
#define ADDRESS_TYPE_ANY        6        // NOTE: Special ANY and ANY_GROUP are placeholders, meaning, ignore this type
#define ADDRESS_TYPE_ANY_GROUP  7     
#define ADDRESS_TYPE_FIND_HIGHEST  8
#define ADDRESS_TYPE_VINES_IP   9
#define ADDRESS_TYPE_LOCAL_ONLY 10

#define ADDRESSTYPE_FLAGS_NORMALIZE     0x0001
#define ADDRESSTYPE_FLAGS_BIT_REVERSE   0x0002

//=============================================================================
//  Address pair.
//=============================================================================

typedef struct _ADDRESSPAIR
{
    WORD        AddressFlags;
    WORD        NalReserved;
    ADDRESS     DstAddress;
    ADDRESS     SrcAddress;
} ADDRESSPAIR;

typedef ADDRESSPAIR *LPADDRESSPAIR;

#define ADDRESS_FLAGS_MATCH_DST     0x0001  //... Match dest. address.
#define ADDRESS_FLAGS_MATCH_SRC     0x0002  //... Match src. address.
#define ADDRESS_FLAGS_EXCLUDE       0x0004  //... Perform logical XOR vs logical OR.
#define ADDRESS_FLAGS_GROUP_ADDR    0x0008  //... Match group bit only.

#define ADDRESS_FLAGS_MATCH_BOTH    0x0003  //... 0x0001 | 0x0002.

#define ADDRESSPAIR_SIZE sizeof(ADDRESSPAIR)

//=============================================================================
//  Address table.
//=============================================================================

#define MAX_ADDRESS_PAIRS   8

typedef struct _ADDRESSTABLE
{
    DWORD           nAddressPairs;
    ADDRESSPAIR     AddressPair[MAX_ADDRESS_PAIRS];
} ADDRESSTABLE;

typedef ADDRESSTABLE *LPADDRESSTABLE;

#define ADDRESSTABLE_SIZE sizeof(ADDRESSTABLE)

//=============================================================================
//  Network information.
//=============================================================================

typedef struct _NETWORKINFO
{
    BYTE            PermanentAddr[6];       //... Permanent MAC address
    BYTE            CurrentAddr[6];         //... Current  MAC address
    ADDRESS         OtherAddress;           //... Other address supported (IP, IPX, etc...)
    DWORD           LinkSpeed;              //... Link speed in Mbits.
    DWORD           MacType;                //... Media type.
    DWORD           MaxFrameSize;           //... Max frame size allowed.
    DWORD           Flags;                  //... Informational flags.
    DWORD           TimestampScaleFactor;   //... 1 = 1/1 ms, 10 = 1/10 ms, 100 = 1/100 ms, etc.
    BYTE            NodeName[32];           //... Name of remote workstation.
    BYTE            Comment[ADAPTER_COMMENT_LENGTH]; // Adapter comment field.
} NETWORKINFO;

typedef NETWORKINFO *LPNETWORKINFO;

#define NETWORKINFO_SIZE    sizeof(NETWORKINFO)

#define NETWORKINFO_FLAGS_PMODE_NOT_SUPPORTED           0x00000001
#define NETWORKINFO_FLAGS_LOOPBACK_NOT_SUPPORTED        0x00000002
#define NETWORKINFO_FLAGS_REMOTE_NAL                    0x00000004
#define NETWORKINFO_FLAGS_REMOTE_NAL_CONNECTED          0x00000008
#define NETWORKINFO_FLAGS_REMOTE_CARD                   0x00000010

//=============================================================================
//  Pattern structure.
//=============================================================================

#define MAX_PATTERN_LENGTH  16

typedef struct _PATTERNMATCH
{
    DWORD   Flags;
    WORD    Offset;
    WORD    Length;
    BYTE    PatternToMatch[MAX_PATTERN_LENGTH];                 //... Pattern to match.
} PATTERNMATCH;

#define PATTERN_MATCH_FLAGS_NOT                 0x00000001      //... Negate the results.
#define PATTERN_MATCH_FLAGS_DATA_RELATIVE       0x00000002      //... pattern is relative to data, not frame.

typedef PATTERNMATCH *LPPATTERNMATCH;

#define PATTERNMATCH_SIZE    sizeof(PATTERNMATCH)

//=============================================================================
//  Expression structure.
//=============================================================================

#define MAX_PATTERNS    4

typedef struct _ANDEXP
{
    DWORD            nPatternMatches;
    PATTERNMATCH     PatternMatch[MAX_PATTERNS];
} ANDEXP;

typedef ANDEXP *LPANDEXP;

#define ANDEXP_SIZE     sizeof(ANDEXP)

typedef struct _EXPRESSION
{
    DWORD       nAndExps;
    ANDEXP      AndExp[MAX_PATTERNS];
} EXPRESSION;

typedef EXPRESSION *LPEXPRESSION;

#define EXPRESSION_SIZE    sizeof(EXPRESSION)

//=============================================================================
//  Trigger.
//=============================================================================

typedef struct _TRIGGER
{
    DWORD           TriggerFlags;           //... Trigger flags.
    PATTERNMATCH    TriggerPatternMatch;    //... Trigger pattern match.
    BYTE            TriggerOpcode;          //... Trigger opcode.
    BYTE            TriggerAction;          //... Action to take when trigger occurs.
    WORD            TriggerState;           //... State change request.
    WORD            TriggerBufferSize;      //... Percentage of buffer to trigger on.
    LPSTR           TriggerCommand;         //... Command string to pass to WinExec.
} TRIGGER;

typedef TRIGGER *LPTRIGGER;

#define TRIGGER_SIZE    sizeof(TRIGGER)

#define TRIGGER_FLAGS_DATA_RELATIVE         0x00000001

//=============================================================================
//  Capture filter.
//=============================================================================

typedef struct _CAPTUREFILTER
{
    DWORD           FilterFlags;            //... filter flags,
    LPBYTE          SapTable;               //... sap table.
    LPWORD          EtypeTable;             //... etype table.
    WORD            nSaps;                  //... sap table length.
    WORD            nEtypes;                //... Etype table length.
    LPADDRESSTABLE  AddressTable;           //... Address table.
    EXPRESSION      FilterExpression;       //... Filter expression.
    TRIGGER         Trigger;                //... Trigger structure.
    DWORD           nFrameBytesToCopy;      //... Number of byte of each frame to copy.
    DWORD           Reserved;
} CAPTUREFILTER;

typedef CAPTUREFILTER *LPCAPTUREFILTER;

#define CAPTUREFILTER_SIZE sizeof(CAPTUREFILTER)

//=============================================================================
//  Capture filter flags. By default all frames are rejected and
//  NalSetCaptureFilter enables them based on the CAPTUREFILTER flags
//  defined below.
//=============================================================================

#define CAPTUREFILTER_FLAGS_INCLUDE_ALL_SAPS    0x0001      //... include saps.
#define CAPTUREFILTER_FLAGS_INCLUDE_ALL_ETYPES  0x0002      //... include etypes.
#define CAPTUREFILTER_FLAGS_TRIGGER             0x0004      //... process trigger.
#define CAPTUREFILTER_FLAGS_LOCAL_ONLY          0x0008      //... non-promiscuous.
#define CAPTUREFILTER_FLAGS_DISCARD_COMMENTS    0x0010      //... throw away our internal comment frames

//.. The following causes both saps and etypes to be included.

#define CAPTUREFILTER_FLAGS_INCLUDE_ALL         0x0003      //... 0x0001 | 0x0002

#define BUFFER_FULL_25_PERCENT                  0
#define BUFFER_FULL_50_PERCENT                  1
#define BUFFER_FULL_75_PERCENT                  2
#define BUFFER_FULL_100_PERCENT                 3

//=============================================================================
//  Station statistics.
//=============================================================================

typedef struct _STATIONSTATS *LPSTATIONSTATS;
typedef struct _SESSION      *LPSESSION;

typedef struct _SESSION
{
    LPSESSION       NextSession;            //... opaque, used by nal.
    LPSTATIONSTATS  StationOwner;
    LPSTATIONSTATS  StationPartner;
    DWORD           Flags;
    DWORD           TotalPacketsSent;
} SESSION;

#define SESSION_SIZE    sizeof(SESSION)

#define SESSION_FLAGS_INITIALIZED  0x0001           //... Structure has been initialized.
#define SESSION_FLAGS_EVENTPOSTED  0x0002           //... Nal has posted an event for this entry.

typedef struct _STATIONSTATS    *LPSTATIONSTATS;

typedef struct _STATIONSTATS
{
    LPSTATIONSTATS NextStationStats;        //... opaque, used by nal.
    LPSESSION       SessionPartnerList;     //... opaque, used by nal.
    DWORD           Flags;                  //... opaque, used by nal.
    BYTE            StationAddress[6];
    WORD            Pad;                    //... DWORD alignment.
    DWORD           TotalPacketsReceived;
    DWORD           TotalDirectedPacketsSent;
    DWORD           TotalBroadcastPacketsSent;
    DWORD           TotalMulticastPacketsSent;
    DWORD           TotalBytesReceived;
    DWORD           TotalBytesSent;
} STATIONSTATS;

#define STATIONSTATS_SIZE       sizeof(STATIONSTATS)

#define STATIONSTATS_FLAGS_INITIALIZED  0x0001      //... Structure has been initialized.
#define STATIONSTATS_FLAGS_EVENTPOSTED  0x0002      //... Nal has posted an event for this entry.

//=============================================================================
//  Bone packet definition.
//=============================================================================

#define STATIONQUERY_FLAGS_LOADED       0x0001      //... Driver is loaded but the kernel is not.
#define STATIONQUERY_FLAGS_RUNNING      0x0002      //... Driver is loaded but not capturing.
#define STATIONQUERY_FLAGS_CAPTURING    0x0004      //... Driver is actively capturing.
#define STATIONQUERY_FLAGS_TRANSMITTING 0x0008      //... Driver is actively transmitting.

typedef struct _STATIONQUERY
{
    DWORD           Flags;                              //... Current state of bloodhound.
    BYTE            BCDVerMinor;                        //... Binary coded decimal (minor).
    BYTE            BCDVerMajor;                        //... Binary coded decimal (major).
    DWORD           LicenseNumber;                      //... Software license number.
    BYTE            MachineName[MACHINE_NAME_LENGTH];   //... Machine name, if any.
    BYTE            UserName[USER_NAME_LENGTH];         //... Username name, if any.
    BYTE            Reserved[32];                       //... Reserved.
    BYTE            AdapterAddress[6];                  //... NIC address.
} STATIONQUERY;

typedef STATIONQUERY *LPSTATIONQUERY;

#define STATIONQUERY_SIZE sizeof(STATIONQUERY)

//=============================================================================
//  QUERYTABLE structure.
//=============================================================================

typedef struct _QUERYTABLE
{
    DWORD           nStationQueries;
    STATIONQUERY    StationQuery[0];
} QUERYTABLE;

typedef QUERYTABLE *LPQUERYTABLE;

#define QUERYTABLE_SIZE sizeof(QUERYTABLE)

//=============================================================================
//  BONEPACKET structure.
//=============================================================================

typedef struct _BONEPACKET
{
    DWORD       Signature;                  //... 'RTSS'
    BYTE        Command;                    //... packet command field.
    BYTE        Flags;                      //... flags.
    DWORD       Reserved;                   //... reserved.
    WORD        Length;                     //... length of data, if any.
} BONEPACKET;

typedef BONEPACKET *LPBONEPACKET;

#define BONEPACKET_SIZE sizeof(BONEPACKET)

//=============================================================================
//  BONE alert packet.
//=============================================================================

typedef struct _ALERT
{
    DWORD           AlertCode;                          //... Alert code.
    BYTE            MachineName[MACHINE_NAME_LENGTH];   //... Machine name, if any.
    BYTE            UserName[USER_NAME_LENGTH];         //... Username name, if any.

    union
    {
        BYTE            Pad[32];                        //... Alert code-specific data.
        DWORD           nFramesToSend;                  //... Transmit alert data.
    };
} ALERT;

typedef ALERT *LPALERT;

#define ALERT_SIZE sizeof(ALERT)

//... Alert codes.

#define ALERT_CODE_BEGIN_TRANSMIT           0

//=============================================================================
//  BONEPACKET signature.
//=============================================================================

#define MAKE_WORD(l, h)         (((WORD) (l)) | (((WORD) (h)) << 8))
#define MAKE_LONG(l, h)         (((DWORD) (l)) | (((DWORD) (h)) << 16L))

#define MAKE_SIG(a, b, c, d)    MAKE_LONG(MAKE_WORD(a, b), MAKE_WORD(c, d))

#define BONE_PACKET_SIGNATURE   MAKE_SIG('R', 'T', 'S', 'S')

//=============================================================================
//  BONEPACKET commands.
//=============================================================================

#define BONE_COMMAND_STATION_QUERY_REQUEST      0
#define BONE_COMMAND_STATION_QUERY_RESPONSE     1
#define BONE_COMMAND_ALERT                      2

//=============================================================================
//  STATISTICS parameter structure return from OpenNetwork().
//=============================================================================

typedef struct _STATISTICSPARAM
{
    DWORD           StatisticsSize;             //... Number of bytes.
    LPSTATISTICS    Statistics;
    DWORD           StatisticsTableEntries;     //... Number of entries.
    LPSTATIONSTATS  StatisticsTable;
    DWORD           SessionTableEntries;        //... Number of entries.
    LPSESSION       SessionTable;
} STATISTICSPARAM;

typedef STATISTICSPARAM *LPSTATISTICSPARAM;

#define STATISTICSPARAM_SIZE    sizeof(STATISTICSPARAM)

//=============================================================================
//  RECONNECTINFO structure.
//=============================================================================

typedef struct _RECONNECTINFO_HEADER
{
    DWORD       Signature;                      //... Application-defined signature.
    WORD        PrivateDataLength;              //... Private data length (max = 64K - header size).
    BYTE        Reserved[26];                   //... Reserved for future use.
} RECONNECTINFO_HEADER;

typedef RECONNECTINFO_HEADER *LPRECONNECTINFO_HEADER;

#define RECONNECTINFO_HEADER_SIZE   sizeof(RECONNECTINFO_HEADER)    //... 32 byte fixed header.

typedef struct _RECONNECTINFO
{
    RECONNECTINFO_HEADER    ReconnectInfoHeader;
    BYTE                    PrivateData[0];
} RECONNECTINFO;

typedef RECONNECTINFO *LPRECONNECTINFO;

#define RECONNECTINFO_SIZE  sizeof(RECONNECTINFO)

//=============================================================================
//  TEMP SetupNetworkID() data struct
//=============================================================================

typedef struct _SETUPNETWORKPARMS
{
    char    Nodename[32];       //... remote node to connect to
    char    Comment[255];       //... comment regarding what we are using remote network for
    int     NetID;              //... which network id to use
    DWORD   Frequency;          //... frequency of Agent status updates
    DWORD   fSlowLink:1;        //... flag to signify slow link
} SETUPNETWORKPARMS;

typedef SETUPNETWORKPARMS *LPSETUPNETWORKPARMS;

#define SETUPNETWORKPARMS_SIZE    sizeof(SETUPNETWORKPARMS)

//=============================================================================
// Constants for SpecialFrame comment insertions
//=============================================================================

#define SPECIAL_FRAME_FLAG_USE_AS_STATS_ENDPOINT      0x00000001

#define SPECIAL_FRAME_TYPE_COMMENT  101
#define SPECIAL_FRAME_TYPE_BOOKMARK 102
#define SPECIAL_FRAME_TYPE_STATS    103
#define SPECIAL_FRAME_TYPE_ODBC     104
#define SPECIAL_FRAME_TYPE_MESSAGE  105

#pragma pack()
#endif
