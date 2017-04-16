/*++

Copyright 1996 - 1998 Microsoft Corporation

Module Name:

    rtp.h

Abstract:

    Header for RTP/RTCP Protocol.

--*/
 
#ifndef _INC_RTP
#define _INC_RTP

#define RTP_TYPE     2
#define RTP_MAX_SDES 256
#define RTP_MAX_EKEY 32

typedef struct _RTP_SDES_ITEM {
    BYTE Type;
    BYTE TextLength;
    BYTE Text[RTP_MAX_SDES];
} RTCP_SDES_ITEM, *PRTCP_SDES_ITEM;

typedef struct _RTCP_SENDER_REPORT {
    DWORD NtpTimestampSec;
    DWORD NtpTimestampFrac;
    DWORD RtpTimestamp;
    DWORD TotalPackets;
    DWORD TotalOctets;
} RTCP_SENDER_REPORT, *PRTCP_SENDER_REPORT;
    
typedef struct _RTCP_RECEIVER_REPORT {
    DWORD FractionLost:8;
    DWORD TotalLostPackets:24;
    DWORD HighestSequenceNum;
    DWORD InterarrivalJitter;
    DWORD LastSRTimestamp;
    DWORD DelaySinceLastSR;
} RTCP_RECEIVER_REPORT, *PRTCP_RECEIVER_REPORT;

typedef struct _RTCP_PARTICIPANT_REPORT {
    DWORD                SSRC;
    RTCP_SENDER_REPORT   LastSR;
    RTCP_RECEIVER_REPORT LastIncomingRR;
    RTCP_RECEIVER_REPORT LastOutgoingRR;
} RTCP_PARTICIPANT_REPORT, *PRTCP_PARTICIPANT_REPORT;
    
typedef struct _RTP_HEADER {
//--- NETWORK BYTE ORDER BEGIN ---//
    WORD  NumCSRC:4;                                      
    WORD  fExtHeader:1;                                   
    WORD  fPadding:1;                                     
    WORD  Version:2;                                      
    WORD  PayloadType:7;
    WORD  fMarker:1;
//---- NETWORK BYTE ORDER END ----//
    WORD  SequenceNum;
    DWORD Timestamp;
    DWORD SSRC;
} RTP_HEADER, *PRTP_HEADER;

typedef struct _RTP_HEADER_X {
    WORD  Identifier;
    WORD  DataLength;
    DWORD Data[1];
} RTP_HEADER_X, *PRTP_HEADER_X;

typedef struct _RTP_ENCRYPTION_INFO {
    DWORD Scheme;
    DWORD Key[RTP_MAX_EKEY];
} RTP_ENCRYPTION_INFO, *PRTP_ENCRYPTION_INFO;

#endif // _INC_RTP
