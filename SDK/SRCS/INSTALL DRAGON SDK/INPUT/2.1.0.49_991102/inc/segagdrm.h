//+----------------------------------------------------------------------------
//
// File:        segacdrm.h
//
// Copyight:    (c) 1998, Microsoft Corporation
//			All Rights Reserved
//                      Infomation Contained Herein Is Proprietary
//                      and Confidential
//
// Contents:    Sega CD-ROM IOCTLS, data structure & value defines
//
//-----------------------------------------------------------------------------

#ifndef _SEGACDRM_H_
#define _SEGACDRM_H_

#include <winioctl.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, segagdrm)
#pragma pack(1)

#define IOCTL_SEGACD_TEST_UNIT      	CTL_CODE(IOCTL_CDROM_BASE, 0x0400, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_SEGACD_REQ_MODE       	CTL_CODE(IOCTL_CDROM_BASE, 0x0402, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_SEGACD_SET_MODE       	CTL_CODE(IOCTL_CDROM_BASE, 0x0403, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_SEGACD_CD_OPEN        	CTL_CODE(IOCTL_CDROM_BASE, 0x0407, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_SEGACD_CD_PLAYTRACK   	CTL_CODE(IOCTL_CDROM_BASE, 0x0408, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_SEGACD_GET_SCD        	CTL_CODE(IOCTL_CDROM_BASE, 0x040d, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_SEGACD_GET_STATUS     	CTL_CODE(IOCTL_CDROM_BASE, 0x040e, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_SEGACD_GET_IP         	CTL_CODE(IOCTL_CDROM_BASE, 0x040f, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_SEGACD_SET_DOOR_BEHAVIOR	CTL_CODE(IOCTL_CDROM_BASE, 0x0410, METHOD_BUFFERED, FILE_READ_ACCESS)

#define SEGACD_STAT_BUSY    0x0
#define SEGACD_STAT_PAUSE   0x1
#define SEGACD_STAT_STANDBY 0x2
#define SEGACD_STAT_PLAY    0x3
#define SEGACD_STAT_SEEK    0x4
#define SEGACD_STAT_SCAN    0x5
#define SEGACD_STAT_OPEN    0x6
#define SEGACD_STAT_NODISC  0x7
#define SEGACD_STAT_RETRY   0x8
#define SEGACD_STAT_ERROR   0x9

#define SEGACD_FORMAT_CDDA      0x0
#define SEGACD_FORMAT_CDROM     0x1
#define SEGACD_FORMAT_CDROMXA   0x2
#define SEGACD_FORMAT_CDI       0x3
#define SEGACD_FORMAT_GDROM     0x9

//
// Received from IOCTL_SEGACD_GET_STATUS
//
typedef struct SEGACD_STATUS
{
    DWORD dwStatus;
    DWORD dwDiscFormat;
} SEGACD_STATUS;

//
//  Sent to IOCTL_SEGACD_GET_SCD
//
typedef struct SEGACD_SCD
{
    DWORD dwDataFormat;
    DWORD dwLength;
    WORD* pwBuffer;                     // points to one of the buffer types below
} SEGACD_SCD;

#define SEGACD_SCD_FORMAT_ALL   0x00    // All subcode information is transferred as raw data
#define SEGACD_SCD_FORMAT_SUBQ  0x01    // Subcode Q data only
#define SEGACD_SCD_FORMAT_UPC   0x02    // Media catalog number (UPC/bar code)
#define SEGACD_SCD_FORMAT_ISRC  0x03    // International standard recording code

// audio status definitions
#define SEGACD_AUDIO_INVALID    0x00    // Audio status byte not supported or invalid
#define SEGACD_AUDIO_PLAYING    0x11    // playback in progress
#define SEGACD_AUDIO_PAUSED     0x12    // playback paused
#define SEGACD_AUDIO_ENDED      0x13    // playback ended normally
#define SEGACD_AUDIO_ERROR      0x14    // playback ended abnormally (error)
#define SEGACD_AUDIO_NOINFO     0x15    // No audio status information

typedef struct SEGACD_SCD_HEADER
{
    BYTE Reserved;
    BYTE AudioStatus;
    BYTE DataLength[2];
} SEGACD_SCD_HEADER;

typedef struct SEGACD_SCD_SUB_Q
{
    SEGACD_SCD_HEADER Header;
    BYTE Control : 4;
    BYTE ADR : 4;
    BYTE TrackNumber;
    BYTE IndexNumber;
    BYTE ElapsedFADWithinTrack[3];
    BYTE Reserved2[4];
} SEGACD_SCD_SUB_Q;

typedef struct SEGACD_SCD_MEDIA_CATALOG
{
    SEGACD_SCD_HEADER Header;
    BYTE FormatCode;                    // == 0x02
    BYTE Reserved[3];
    BYTE Reserved1 : 7;
    BYTE Mcval : 1;
    BYTE MediaCatalog[15];
} SEGACD_SCD_MEDIA_CATALOG;

typedef struct SEGACD_SCD_TRACK_ISRC
{
    SEGACD_SCD_HEADER Header;
    BYTE FormatCode;                    // == 0x03
    BYTE Reserved[3];
    BYTE Reserved1 : 7;
    BYTE Tcval : 1;
    BYTE TrackIsrc[15];
} SEGACD_SCD_TRACK_ISRC;

//
// Received from IOCTL_SEGACD_GET_IP
//
typedef struct SEGACD_IP
{
    BYTE IP[256];
} SEGACD_IP;

//
// Sent to IOCTL_SEGACD_SET_MODE
// Received from IOCTL_SEGACD_REQ_MODE
//
typedef struct SEGACD_MODE
{
    DWORD	dwCD_Speed;
    DWORD   dwStandby_Time;
    DWORD   dwRead_Retry;
    DWORD   dwRead_Retry_Times;
} SEGACD_MODE;

//
// Sent to IOCTL_SEGACD_CD_PLAYTRACK
//
typedef struct SEGACD_PLAYTRACK
{
    DWORD	dwStartTrack;
    DWORD   dwEndTrack;
    DWORD   dwRepeat;
} SEGACD_PLAYTRACK;

//
// Received from IOCTL_SEGACD_SET_DOOR_BEHAVIOR
//
typedef struct SEGACD_DOOR_BEHAVIOR
{
	DWORD	dwBehavior;
} SEGACD_DOOR_BEHAVIOR;

#define SEGACD_DOOR_REBOOT		0x00
#define SEGACD_DOOR_NOTIFY_APP	0x01

#pragma pack(pop, segagdrm)

#ifdef __cplusplus
}
#endif

#endif // _SEGACDRM_H_
