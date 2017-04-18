/**!!SDK_32ONLY!!**/
/**++SDK_EXCLUDE++**/
/******************************************************************************
**
** Copyright 1992-98 Adaptec, Inc.,  All Rights Reserved.
**
** This software contains the valuable trade secrets of Adaptec.  The
** software is protected under copyright laws as an unpublished work of
** Adaptec.  Notice is for informational purposes only and does not imply
** publication.  The user of this software may make copies of the software
** for use with parts manufactured by Adaptec or under license from Adaptec
** and for no other use.
**
******************************************************************************/

/******************************************************************************
**
**  Module Name:    srb32.h
**
**  Description:    ASPI for Win32 SRB definitions.  No ASPI constants
**                  are defined here.  Look in srbcmn.h for SRB definitions
**                  common to ASPI for Win16 and ASPI for Win32.
**
**                  This may be bad coding practice, but to keep down on the
**                  chaff I have only documented those fields in the below
**                  structures which aren't defined in the ASPI specification.
**                  It makes the code a little easier to read, and I assume
**                  only people maintaining this code will be messing with it.
**                  I've also added offsets to help out when you're looking at
**                  hex dumps.
**
**  Programmers:    Daniel Polfer (dap)
**
**  History:        11/09/95 (dap)  Initial creation using other headers.
**                  11/30/95 (dap)  Added the TARGETINFO structure.
**                  03/02/95 (dap)  Added ASPI32BUFF structure.
**                  06/01/96 (dap)  Common IOCTLs and PnP structures.
**                  09/03/96 (dap)  Renamed and modified to act as a shared
**                                  file between KMD/VxD and the ring-3 DLLs.
**                  09/13/96 (dap)  Added queue management structures, etc.
**                  06/24/98 (dap)  Modified to use allow auto-SDK generation.
**
**  Notes:          This file created using 4 spaces per tab.
**
**                  This file is NOT a customer deliverable to be included
**                  with the ASPI SDK.  It is specific to our ASPI
**                  implementation and DOES contain definitions of private
**                  Adaptec structures.
**
******************************************************************************/

#ifndef __SRB32_H__
#define __SRB32_H__

/*
** Make sure structures are packed and undecorated.
*/

#ifdef __BORLANDC__
#pragma option -a1
#endif //__BORLANDC__

#ifdef _MSC_VER
#pragma pack(1)
#endif //__MSC_VER

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

/**++SDK_PUBLIC++**/
/**++SDK_32ONLY++**/
//*****************************************************************************
//          %%% SRB - HOST ADAPTER INQUIRY - SC_HA_INQUIRY (0) %%%
//*****************************************************************************

typedef struct                                  // Offset
{                                               // HX/DEC
    BYTE        SRB_Cmd;                        // 00/000 ASPI command code = SC_HA_INQUIRY
    BYTE        SRB_Status;                     // 01/001 ASPI command status byte
    BYTE        SRB_HaId;                       // 02/002 ASPI host adapter number
    BYTE        SRB_Flags;                      // 03/003 ASPI request flags
    DWORD       SRB_Hdr_Rsvd;                   // 04/004 Reserved, MUST = 0
    BYTE        HA_Count;                       // 08/008 Number of host adapters present
    BYTE        HA_SCSI_ID;                     // 09/009 SCSI ID of host adapter
    BYTE        HA_ManagerId[16];               // 0A/010 String describing the manager
    BYTE        HA_Identifier[16];              // 1A/026 String describing the host adapter
/**++SDK_EXCLUDE++**/
    WORD        HA_BufAlignMask;                // 2A/042 HA_Unique[1-0]
    BYTE        HA_Flags;                       // 2C/044 HA_Unique[2]
    BYTE        HA_MaxTargets;                  // 2D/045 HA_Unique[3]
    DWORD       HA_MaxTransferLength;           // 2E/046 HA_Unique[7-4]
    DWORD       HA_MaxSGElements;               // 32/050 HA_Unique[11-8]
    BYTE        HA_Rsvd2[4];                    // 36/054 HA_Unique[15-12]
/**++SDK_32ONLY:    BYTE        HA_Unique[16];                  // 2A/042 Host Adapter Unique parameters++**/
    WORD        HA_Rsvd1;                       // 3A/058 Reserved, MUST = 0
}
SRB32_HAInquiry, *PSRB32_HAInquiry, FAR *LPSRB32_HAInquiry;

/*
 * New
 *
 */
#define	MAX_SCSI_DEVS				16

typedef struct {
	BYTE	NegoDat[4];
} NegoXferData;

typedef struct tag_NEGO_XFER_RATE_STRUCT {
	NegoXferData	NegoXferRate[MAX_SCSI_DEVS];
} NEGO_XFER_RATE_STRUCT, *PNEGO_XFER_RATE_STRUCT;

typedef struct tag_SEE_512_STRUCT {
	union {
		UCHAR	b[512];
		USHORT	w[256];
	} array;
} SEE_512_STRUCT, *PSEE_512_STRUCT;

typedef struct                                  // Offset
{                                               // HX/DEC
    BYTE        SRB_Cmd;                        // 00/000 ASPI command code = SC_EXEC_SCSI_CMD
    WORD        SRB_Status;                     // 01/001 ASPI command status byte
    BYTE        SRB_HaId;                       // 02/002 ASPI host adapter number
    BYTE		SRB_Flags;                      // 03/003 Reserved, MUST = 0
    DWORD		SRB_Hdr_Rsvd;                   // 04/004 Reserved, MUST = 0
	DWORD		SRB_OpCode;
    WORD       	SRB_BufLen;                     // 0C/012 Data Allocation Length
    BYTE        FAR *SRB_BufPointer;            // 10/016 Data Buffer Pointer
}
SRB32_SEEPROM, *PSRB32_SEEPROM, FAR *LPSRB32_SEEPROM;

typedef struct                                  // Offset
{                                               // HX/DEC
    BYTE        SRB_Cmd;                        // 00/000 ASPI command code = SC_HA_INQUIRY
    WORD		SRB_Status;                     // 01/001 ASPI command status byte
    BYTE        SRB_HaId;                       // 02/002 ASPI host adapter number
    BYTE		SRB_Flags;                      // 03/003 Reserved, MUST = 0
    DWORD		SRB_Hdr_Rsvd;                   // 04/004 Reserved, MUST = 0
	DWORD		SRB_OpCode;
    DWORD		SRB_BufLen;                     // 0C/012 Data Allocation Length
    BYTE        FAR *SRB_BufPointer;            // 10/016 Data Buffer Pointer
}
SRB32_EEPROM, *PSRB32_EEPROM, FAR *LPSRB32_EEPROM;

typedef struct                                  // Offset
{                                               // HX/DEC
    BYTE        SRB_Cmd;                        // 00/000 ASPI command code = SC_EXEC_SCSI_CMD
    WORD        SRB_Status;                     // 01/001 ASPI command status byte
    BYTE        SRB_HaId;                       // 02/002 ASPI host adapter number
    BYTE		SRB_Flags;                      // 03/003 Reserved, MUST = 0
    DWORD		SRB_Hdr_Rsvd;                   // 04/004 Reserved, MUST = 0
	DWORD		SRB_OpCode;
    WORD		SRB_BufLen;                     // 0C/012 Data Allocation Length
    BYTE        FAR *SRB_BufPointer;            // 10/016 Data Buffer Pointer
}
SRB32_PCIINFO, *PSRB32_PCIINFO, FAR *LPSRB32_PCIINFO;

typedef struct                                  // Offset
{                                               // HX/DEC
    BYTE        SRB_Cmd;                        // 00/000 ASPI command code = SC_EXEC_SCSI_CMD
    WORD        SRB_Status;                     // 01/001 ASPI command status byte
    BYTE        SRB_HaId;                       // 02/002 ASPI host adapter number
    BYTE		SRB_Flags;                      // 03/003 Reserved, MUST = 0
    DWORD		SRB_Hdr_Rsvd;                   // 04/004 Reserved, MUST = 0
	DWORD		SRB_OpCode;
    WORD		SRB_BufLen;                     // 0C/012 Data Allocation Length
    BYTE        FAR *SRB_BufPointer;            // 10/016 Data Buffer Pointer
}
SRB32_NEGO_XFER_RATE, *PSRB32_NEGO_XFER_RATE, FAR *LPSRB32_NEGO_XFER_RATE;

//*****************************************************************************
//          %%% SRB - GET DEVICE TYPE - SC_GET_DEV_TYPE (1) %%%
//*****************************************************************************

typedef struct                                  // Offset
{                                               // HX/DEC
    BYTE        SRB_Cmd;                        // 00/000 ASPI command code = SC_GET_DEV_TYPE
    BYTE        SRB_Status;                     // 01/001 ASPI command status byte
    BYTE        SRB_HaId;                       // 02/002 ASPI host adapter number
    BYTE        SRB_Flags;                      // 03/003 Reserved, MUST = 0
    DWORD       SRB_Hdr_Rsvd;                   // 04/004 Reserved, MUST = 0
    BYTE        SRB_Target;                     // 08/008 Target's SCSI ID
    BYTE        SRB_Lun;                        // 09/009 Target's LUN number
    BYTE        SRB_DeviceType;                 // 0A/010 Target's peripheral device type
    BYTE        SRB_Rsvd1;                      // 0B/011 Reserved, MUST = 0
}
SRB32_GDEVBlock, *PSRB32_GDEVBlock, FAR *LPSRB32_GDEVBlock;

//*****************************************************************************
//          %%% SRB - EXECUTE SCSI COMMAND - SC_EXEC_SCSI_CMD (2) %%%
//*****************************************************************************

typedef struct                                  // Offset
{                                               // HX/DEC
    BYTE        SRB_Cmd;                        // 00/000 ASPI command code = SC_EXEC_SCSI_CMD
    BYTE        SRB_Status;                     // 01/001 ASPI command status byte
    BYTE        SRB_HaId;                       // 02/002 ASPI host adapter number
    BYTE        SRB_Flags;                      // 03/003 ASPI request flags
    DWORD       SRB_Hdr_Rsvd;                   // 04/004 Reserved
    BYTE        SRB_Target;                     // 08/008 Target's SCSI ID
    BYTE        SRB_Lun;                        // 09/009 Target's LUN number
    WORD        SRB_Rsvd1;                      // 0A/010 Reserved for Alignment
    DWORD       SRB_BufLen;                     // 0C/012 Data Allocation Length
    BYTE        FAR *SRB_BufPointer;            // 10/016 Data Buffer Pointer
    BYTE        SRB_SenseLen;                   // 14/020 Sense Allocation Length
    BYTE        SRB_CDBLen;                     // 15/021 CDB Length
    BYTE        SRB_HaStat;                     // 16/022 Host Adapter Status
    BYTE        SRB_TargStat;                   // 17/023 Target Status
    VOID        FAR *SRB_PostProc;              // 18/024 Post routine
/**++SDK_EXCLUDE++**/
    VOID        FAR *SRB_SRB16Pointer;          // 1C/028 SRB_Rsvd2
    BYTE        SRB_PortStat;                   // 20/032 SRB_Rsvd3 Byte 1
    BYTE        SRB_Rsvd3[15];                  // 21/033 Reserved, MUST = 0
/**++SDK_32ONLY:    BYTE        SRB_Rsvd2[20];                  // 1C/028 Reserved, MUST = 0++**/
    BYTE        CDBByte[16];                    // 30/048 SCSI CDB
/**++SDK_EXCLUDE++**/
    BYTE        SenseArea[];                    // 40/064 Request Sense buffer
/**++SDK_32ONLY:    BYTE        SenseArea[SENSE_LEN+2];         // 50/064 Request Sense buffer++**/
}
SRB32_ExecSCSICmd, *PSRB32_ExecSCSICmd, FAR *LPSRB32_ExecSCSICmd;

//*****************************************************************************
//          %%% SRB - ABORT AN SRB - SC_ABORT_SRB (3) %%%
//*****************************************************************************

typedef struct                                  // Offset
{                                               // HX/DEC
    BYTE        SRB_Cmd;                        // 00/000 ASPI command code = SC_ABORT_SRB
    BYTE        SRB_Status;                     // 01/001 ASPI command status byte
    BYTE        SRB_HaId;                       // 02/002 ASPI host adapter number
    BYTE        SRB_Flags;                      // 03/003 Reserved
    DWORD       SRB_Hdr_Rsvd;                   // 04/004 Reserved
    VOID        FAR *SRB_ToAbort;               // 08/008 Pointer to SRB to abort
}
SRB32_Abort, *PSRB32_Abort, FAR *LPSRB32_Abort;

//*****************************************************************************
//          %%% SRB - BUS DEVICE RESET - SC_RESET_DEV (4) %%%
//*****************************************************************************

typedef struct                                  // Offset
{                                               // HX/DEC
    BYTE        SRB_Cmd;                        // 00/000 ASPI command code = SC_RESET_DEV
    BYTE        SRB_Status;                     // 01/001 ASPI command status byte
    BYTE        SRB_HaId;                       // 02/002 ASPI host adapter number
    BYTE        SRB_Flags;                      // 03/003 ASPI request flags
    DWORD       SRB_Hdr_Rsvd;                   // 04/004 Reserved
    BYTE        SRB_Target;                     // 08/008 Target's SCSI ID
    BYTE        SRB_Lun;                        // 09/009 Target's LUN number
    BYTE        SRB_Rsvd1[12];                  // 0A/010 Reserved for Alignment
    BYTE        SRB_HaStat;                     // 16/022 Host Adapter Status
    BYTE        SRB_TargStat;                   // 17/023 Target Status
    VOID        FAR *SRB_PostProc;              // 18/024 Post routine
/**++SDK_EXCLUDE++**/
    VOID        FAR *SRB_Rsvd2;                 // 1C/028 Reserved, MUST = 0
    BYTE        SRB_Rsvd3[32];                  // 20/032 Reserved, MUST = 0
/**++SDK_32ONLY:    BYTE        SRB_Rsvd2[36];                  // 1C/028 Reserved, MUST = 0++**/
}
SRB32_BusDeviceReset, *PSRB32_BusDeviceReset, FAR *LPSRB32_BusDeviceReset;

//*****************************************************************************
//          %%% SRB - GET DISK INFORMATION - SC_GET_DISK_INFO %%%
//*****************************************************************************

typedef struct                                  // Offset
{                                               // HX/DEC
    BYTE        SRB_Cmd;                        // 00/000 ASPI command code = SC_GET_DISK_INFO
    BYTE        SRB_Status;                     // 01/001 ASPI command status byte
    BYTE        SRB_HaId;                       // 02/002 ASPI host adapter number
    BYTE        SRB_Flags;                      // 03/003 Reserved, MUST = 0
    DWORD       SRB_Hdr_Rsvd;                   // 04/004 Reserved, MUST = 0
    BYTE        SRB_Target;                     // 08/008 Target's SCSI ID
    BYTE        SRB_Lun;                        // 09/009 Target's LUN number
    BYTE        SRB_DriveFlags;                 // 0A/010 Driver flags
    BYTE        SRB_Int13HDriveInfo;            // 0B/011 Host Adapter Status
    BYTE        SRB_Heads;                      // 0C/012 Preferred number of heads translation
    BYTE        SRB_Sectors;                    // 0D/013 Preferred number of sectors translation
    BYTE        SRB_Rsvd1[10];                  // 0E/014 Reserved, MUST = 0
}
SRB32_GetDiskInfo, *PSRB32_GetDiskInfo, FAR *LPSRB32_GetDiskInfo;

//*****************************************************************************
//          %%%  SRB - RESCAN SCSI BUS(ES) ON SCSIPORT %%%
//*****************************************************************************

typedef struct                                  // Offset
{                                               // HX/DEC
    BYTE        SRB_Cmd;                        // 00/000 ASPI command code = SC_RESCAN_SCSI_BUS
    BYTE        SRB_Status;                     // 01/001 ASPI command status byte
    BYTE        SRB_HaId;                       // 02/002 ASPI host adapter number
    BYTE        SRB_Flags;                      // 03/003 Reserved, MUST = 0
    DWORD       SRB_Hdr_Rsvd;                   // 04/004 Reserved, MUST = 0
}
SRB32_RescanPort, *PSRB32_RescanPort, FAR *LPSRB32_RescanPort;

//*****************************************************************************
//          %%% SRB - GET/SET TARGET TIMEOUTS %%%
//*****************************************************************************

typedef struct                                  // Offset
{                                               // HX/DEC
    BYTE        SRB_Cmd;                        // 00/000 ASPI command code = SC_GETSET_TIMEOUTS
    BYTE        SRB_Status;                     // 01/001 ASPI command status byte
    BYTE        SRB_HaId;                       // 02/002 ASPI host adapter number
    BYTE        SRB_Flags;                      // 03/003 ASPI request flags
    DWORD       SRB_Hdr_Rsvd;                   // 04/004 Reserved, MUST = 0
    BYTE        SRB_Target;                     // 08/008 Target's SCSI ID
    BYTE        SRB_Lun;                        // 09/009 Target's LUN number
    DWORD       SRB_Timeout;                    // 0A/010 Timeout in half seconds
}
SRB32_GetSetTimeouts, *PSRB32_GetSetTimeouts, FAR *LPSRB32_GetSetTimeouts;

/**++SDK_PRIVATE++**/
//*****************************************************************************
//          %%% SRB - PER-TARGET QUEUE MANAGEMENT %%%
//*****************************************************************************

typedef struct                                  // Offset
{                                               // HX/DEC
    BYTE        SRB_Cmd;                        // 00/000
    BYTE        SRB_Status;                     // 01/001
    BYTE        SRB_HaId;                       // 02/002
    BYTE        SRB_Flags;                      // 03/003
    DWORD       SRB_Hdr_Rsvd;                   // 04/004
    BYTE        SRB_Target;                     // 08/008
    BYTE        SRB_Lun;                        // 09/009
    BYTE        SRB_QueueCmd;                   // 0A/010
    BYTE        SRB_Enabled;                    // 0B/011
    BYTE        SRB_FreezeDepth;                // 0C/012
    BYTE        SRB_Rsvd1;                      // 0D/013
}
SRB32_ManageQueue, *PSRB32_ManageQueue, FAR *LPSRB32_ManageQueue;

typedef struct                                  // Offset
{                                               // HX/DEC
    BYTE        SRB_Cmd;                        // 00/000
    BYTE        SRB_Status;                     // 01/001
    BYTE        SRB_HaId;                       // 02/002
    BYTE        SRB_Flags;                      // 03/003
    DWORD       SRB_Hdr_Rsvd;                   // 04/004
    BYTE        SRB_Target;                     // 08/008
    BYTE        SRB_Lun;                        // 09/009
    BYTE        SRB_QueueCmd;                   // 0A/010 - Must be SRBQ_SET_CDB_DELAY
    BYTE        SRB_WriteCDB;                   // 0C/012 - Must go on top of SRB_Enabled
    BYTE        SRB_WriteSpeed;                 // 0D/013 - Must go on top of SRB_FreezeDepth
    BYTE        SRB_DelayMode;                  // 0B/011 - 0 None, 1 Delay, 2 bufcap, 3 HP bufcap
    WORD        SRB_BlockSize;                  // 0E/014
    DWORD       SRB_Reserved;                   // 10/016
}
SRB32_SetCDBDelay, *PSRB32_SetCDBDelay, FAR *LPSRB32_SetCDBDelay;

/**++SDK_PUBLIC++**/
//*****************************************************************************
//          %%% ASPIBUFF - Structure For Controllng I/O Buffers %%%
//*****************************************************************************

typedef struct tag_ASPI32BUFF                   // Offset
{                                               // HX/DEC
    PBYTE                   AB_BufPointer;      // 00/000 Pointer to the ASPI allocated buffer
    DWORD                   AB_BufLen;          // 04/004 Length in bytes of the buffer
    DWORD                   AB_ZeroFill;        // 08/008 Flag set to 1 if buffer should be zeroed
/**++SDK_EXCLUDE++**/
    struct tag_ASPI32BUFF  *AB_Next;            // 0C/012 Pointer to next buffer in chain
/**++SDK_32ONLY:    DWORD                   AB_Reserved;        // 0C/012 Reserved++**/
}
ASPI32BUFF, *PASPI32BUFF, FAR *LPASPI32BUFF;

/**++SDK_32ONLY://*****************************************************************************++**/
/**++SDK_32ONLY://          %%% PROTOTYPES - User Callable ASPI for Win32 Functions %%%++**/
/**++SDK_32ONLY://*****************************************************************************++**/
/**++SDK_32ONLY:++**/
/**++SDK_32ONLY:typedef void *LPSRB;++**/
/**++SDK_32ONLY:++**/
/**++SDK_32ONLY:#if defined(__BORLANDC__)++**/
/**++SDK_32ONLY:++**/
/**++SDK_32ONLY:DWORD _import GetASPI32SupportInfo( void );++**/
/**++SDK_32ONLY:DWORD _import SendASPI32Command( LPSRB );++**/
/**++SDK_32ONLY:BOOL _import GetASPI32Buffer( PASPI32BUFF );++**/
/**++SDK_32ONLY:BOOL _import FreeASPI32Buffer( PASPI32BUFF );++**/
/**++SDK_32ONLY:BOOL _import TranslateASPI32Address( PDWORD, PDWORD );++**/
/**++SDK_32ONLY:++**/
/**++SDK_32ONLY:#elif defined(_MSC_VER)++**/
/**++SDK_32ONLY:++**/
/**++SDK_32ONLY:__declspec(dllimport) DWORD GetASPI32SupportInfo( void );++**/
/**++SDK_32ONLY:__declspec(dllimport) DWORD SendASPI32Command( LPSRB );++**/
/**++SDK_32ONLY:__declspec(dllimport) BOOL GetASPI32Buffer( PASPI32BUFF );++**/
/**++SDK_32ONLY:__declspec(dllimport) BOOL FreeASPI32Buffer( PASPI32BUFF );++**/
/**++SDK_32ONLY:__declspec(dllimport) BOOL TranslateASPI32Address( PDWORD, PDWORD );++**/
/**++SDK_32ONLY:++**/
/**++SDK_32ONLY:#else++**/
/**++SDK_32ONLY:++**/
/**++SDK_32ONLY:extern DWORD GetASPI32SupportInfo( void );++**/
/**++SDK_32ONLY:extern DWORD SendASPI32Command( LPSRB );++**/
/**++SDK_32ONLY:extern BOOL GetASPI32Buffer( PASPI32BUFF );++**/
/**++SDK_32ONLY:extern BOOL FreeASPI32Buffer( PASPI32BUFF );++**/
/**++SDK_32ONLY:extern BOOL TranslateASPI32Address( PDWORD, PDWORD );++**/
/**++SDK_32ONLY:++**/
/**++SDK_32ONLY:#endif++**/

/*
** Restore compiler default packing and close off the C declarations.
*/

#ifdef __BORLANDC__
#pragma option -a.
#endif //__BORLANDC__

#ifdef _MSC_VER
#pragma pack()
#endif //_MSC_VER

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //__WNASPI32_H__
