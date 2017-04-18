/**!!SDK_16ONLY!!**/
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
**  Module Name:    srb16.h
**
**  Description:    ASPI for Win16 structure definitions.  No ASPI constants
**                  are defined here.  Look in srbcmn.h for ASPI definitions
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
**                  09/03/96 (dap)  Renamed and modified to act as a shared
**                                  file between KMD/VxD and the ring-3 DLLs.
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

#ifndef __SRB16_H__
#define __SRB16_H__

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
/**++SDK_16ONLY++**/
//*****************************************************************************
//          %%% SRB - HOST ADAPTER INQUIRY - SC_HA_INQUIRY (0) %%%
//*****************************************************************************

typedef struct                                  // Offset
{                                               // HX/DEC
    BYTE        SRB_Cmd;                        // 00/000 ASPI command code = SC_HA_INQUIRY
    BYTE        SRB_Status;                     // 01/001 ASPI command status byte
    BYTE        SRB_HaId;                       // 02/002 ASPI host adapter number
    BYTE        SRB_Flags;                      // 03/003 ASPI request flags
    WORD        SRB_55AASignature;              // 04/004 Signature to signal extended inquiry
    WORD        SRB_ExtBufferSize;              // 06/006 Size of extended buffer, if any
    BYTE        HA_Count;                       // 08/008 Number of host adapters present
    BYTE        HA_SCSI_ID;                     // 09/009 SCSI ID of host adapter
    BYTE        HA_ManagerId[16];               // 0A/010 String describing the manager
    BYTE        HA_Identifier[16];              // 1A/026 String describing the host adapter
    BYTE        HA_Unique[16];                  // 2A/042 Host Adapter Unique parameters
    BYTE        HA_ExtBuffer[8];                // 3A/058 Extended inquiry data
}
SRB16_HAInquiry, *PSRB16_HAInquiry, FAR *LPSRB16_HAInquiry;

//*****************************************************************************
//          %%% SRB - GET DEVICE TYPE - SC_GET_DEV_TYPE (1) %%%
//*****************************************************************************

typedef struct                                  // Offset
{                                               // HX/DEC
    BYTE        SRB_Cmd;                        // 00/000 ASPI command code = SC_GET_DEV_TYPE
    BYTE        SRB_Status;                     // 01/001 ASPI command status byte
    BYTE        SRB_HaId;                       // 02/002 ASPI host adapter number
    BYTE        SRB_Flags;                      // 03/003 ASPI request flags
    DWORD       SRB_Hdr_Rsvd;                   // 04/004 Reserved, MUST = 0
    BYTE        SRB_Target;                     // 08/008 Target's SCSI ID
    BYTE        SRB_Lun;                        // 09/009 Target's LUN number
    BYTE        SRB_DeviceType;                 // 0A/010 Target's peripheral device type
}
SRB16_GDEVBlock, *PSRB16_GDEVBlock, FAR *LPSRB16_GDEVBlock;

//*****************************************************************************
//          %%% SRB - EXECUTE SCSI COMMAND - SC_EXEC_SCSI_CMD (2) %%%
//*****************************************************************************

/**++SDK_EXCLUDE++**/
typedef struct                                  // Offset
{                                               // HX/DEC
    BYTE        SRB_Cmd;                        // 00/000
    BYTE        SRB_Status;                     // 01/001
    BYTE        SRB_HaId;                       // 02/002
    BYTE        SRB_Flags;                      // 03/003
    DWORD       SRB_Hdr_Rsvd;                   // 04/004
    BYTE        SRB_Target;                     // 08/008
    BYTE        SRB_Lun;                        // 09/009
    DWORD       SRB_BufLen;                     // 0A/010
    BYTE        SRB_SenseLen;                   // 0E/014
    BYTE        FAR *SRB_BufPointer;            // 0F/015
    BYTE        FAR *SRB_LinBufPointer;         // 13/019 SRB_Rsvd1 - 32 bit linear buf addr for WOW
    BYTE        SRB_CDBLen;                     // 17/023
    BYTE        SRB_HaStat;                     // 18/024
    BYTE        SRB_TargStat;                   // 19/025
    VOID        FAR *SRB_PostProc;              // 1A/026
    BYTE        SRB_Rsvd2[29];                  // 1E/030
    BYTE        SRB_PortStat;                   // 3B/059 SRB_Rsvd2 - Copy of port status byte
    VOID        FAR *SRB_SRB16SOPointer;        // 3C/060 SRB_Rsvd2 - SEG/OFF pointer used by WOW
    BYTE        CDBByte[];                      // 40/064
}
SRB16_ExecSCSICmd, *PSRB16_ExecSCSICmd, FAR *LPSRB16_ExecSCSICmd;

/**++SDK_16ONLY++**/
typedef struct                                  // Offset Structure for 6-byte CDBs
{                                               // HX/DEC
    BYTE        SRB_Cmd;                        // 00/000 ASPI command code = SC_EXEC_SCSI_CMD
    BYTE        SRB_Status;                     // 01/001 ASPI command status byte
    BYTE        SRB_HaId;                       // 02/002 ASPI host adapter number
    BYTE        SRB_Flags;                      // 03/003 ASPI request flags
    DWORD       SRB_Hdr_Rsvd;                   // 04/004 Reserved, MUST = 0
    BYTE        SRB_Target;                     // 08/008 Target's SCSI ID
    BYTE        SRB_Lun;                        // 09/009 Target's LUN number
    DWORD       SRB_BufLen;                     // 0A/010 Data Allocation Length
    BYTE        SRB_SenseLen;                   // 0E/014 Sense Allocation Length
    BYTE        FAR *SRB_BufPointer;            // 0F/015 Data Buffer Pointer
    DWORD       SRB_Rsvd1;                      // 13/019 Reserved, MUST = 0
    BYTE        SRB_CDBLen;                     // 17/023 CDB Length = 6
    BYTE        SRB_HaStat;                     // 18/024 Host Adapter Status
    BYTE        SRB_TargStat;                   // 19/025 Target Status
    VOID        FAR *SRB_PostProc;              // 1A/026 Post routine
    BYTE        SRB_Rsvd2[34];                  // 1E/030 Reserved, MUST = 0
    BYTE        CDBByte[6];                     // 40/064 SCSI CDB
    BYTE        SenseArea6[SENSE_LEN];          // 46/070 Request Sense buffer
}
SRB_ExecSCSICmd6, *PSRB_ExecSCSICmd6, FAR *LPSRB_ExecSCSICmd6;

typedef struct                                  // Offset Structure for 10-byte CDBs
{                                               // HX/DEC
    BYTE        SRB_Cmd;                        // 00/000 ASPI command code = SC_EXEC_SCSI_CMD
    BYTE        SRB_Status;                     // 01/001 ASPI command status byte
    BYTE        SRB_HaId;                       // 02/002 ASPI host adapter number
    BYTE        SRB_Flags;                      // 03/003 ASPI request flags
    DWORD       SRB_Hdr_Rsvd;                   // 04/004 Reserved, MUST = 0
    BYTE        SRB_Target;                     // 08/008 Target's SCSI ID
    BYTE        SRB_Lun;                        // 09/009 Target's LUN number
    DWORD       SRB_BufLen;                     // 0A/010 Data Allocation Length
    BYTE        SRB_SenseLen;                   // 0E/014 Sense Allocation Length
    BYTE        FAR *SRB_BufPointer;            // 0F/015 Data Buffer Pointer
    DWORD       SRB_Rsvd1;                      // 13/019 Reserved, MUST = 0
    BYTE        SRB_CDBLen;                     // 17/023 CDB Length = 10
    BYTE        SRB_HaStat;                     // 18/024 Host Adapter Status
    BYTE        SRB_TargStat;                   // 19/025 Target Status
    VOID        FAR *SRB_PostProc;              // 1A/026 Post routine
    BYTE        SRB_Rsvd2[34];                  // 1E/030 Reserved, MUST = 0
    BYTE        CDBByte[6];                     // 40/064 SCSI CDB
    BYTE        SenseArea10[SENSE_LEN];         // 50/070 Request Sense buffer
}
SRB_ExecSCSICmd10, *PSRB_ExecSCSICmd10, FAR *LPSRB_ExecSCSICmd10;

typedef struct                                  // Offset Structure for 12-byte CDBs
{                                               // HX/DEC
    BYTE        SRB_Cmd;                        // 00/000 ASPI command code = SC_EXEC_SCSI_CMD
    BYTE        SRB_Status;                     // 01/001 ASPI command status byte
    BYTE        SRB_HaId;                       // 02/002 ASPI host adapter number
    BYTE        SRB_Flags;                      // 03/003 ASPI request flags
    DWORD       SRB_Hdr_Rsvd;                   // 04/004 Reserved, MUST = 0
    BYTE        SRB_Target;                     // 08/008 Target's SCSI ID
    BYTE        SRB_Lun;                        // 09/009 Target's LUN number
    DWORD       SRB_BufLen;                     // 0A/010 Data Allocation Length
    BYTE        SRB_SenseLen;                   // 0E/014 Sense Allocation Length
    BYTE        FAR *SRB_BufPointer;            // 0F/015 Data Buffer Pointer
    DWORD       SRB_Rsvd1;                      // 13/019 Reserved, MUST = 0
    BYTE        SRB_CDBLen;                     // 17/023 CDB Length = 12
    BYTE        SRB_HaStat;                     // 18/024 Host Adapter Status
    BYTE        SRB_TargStat;                   // 19/025 Target Status
    VOID        FAR *SRB_PostProc;              // 1A/026 Post routine
    BYTE        SRB_Rsvd2[34];                  // 1E/030 Reserved, MUST = 0
    BYTE        CDBByte[12];                    // 40/064 SCSI CDB
    BYTE        SenseArea12[SENSE_LEN];         // 4C/076 Request Sense buffer
}
SRB_ExecSCSICmd12, *PSRB_ExecSCSICmd12, FAR *LPSRB_ExecSCSICmd12;

//*****************************************************************************
//          %%% SRB - ABORT AN SRB - SC_ABORT_SRB (3) %%%
//*****************************************************************************

typedef struct                                  // Offset
{                                               // HX/DEC
    BYTE        SRB_Cmd;                        // 00/000 ASPI command code = SC_ABORT_SRB
    BYTE        SRB_Status;                     // 01/001 ASPI command status byte
    BYTE        SRB_HaId;                       // 02/002 ASPI host adapter number
    BYTE        SRB_Flags;                      // 03/003 ASPI request flags
    DWORD       SRB_Hdr_Rsvd;                   // 04/004 Reserved, MUST = 0
    VOID        FAR *SRB_ToAbort;               // 08/008 Pointer to SRB to abort
}
SRB16_Abort, *PSRB16_Abort, FAR *LPSRB16_Abort;

//*****************************************************************************
//          %%% SRB - BUS DEVICE RESET - SC_RESET_DEV (4) %%%
//*****************************************************************************

typedef struct                                  // Offset
{                                               // HX/DEC
    BYTE        SRB_Cmd;                        // 00/000 ASPI command code = SC_RESET_DEV
    BYTE        SRB_Status;                     // 01/001 ASPI command status byte
    BYTE        SRB_HaId;                       // 02/002 ASPI host adapter number
    BYTE        SRB_Flags;                      // 03/003 ASPI request flags
    DWORD       SRB_Hdr_Rsvd;                   // 04/004 Reserved, MUST = 0
    BYTE        SRB_Target;                     // 08/008 Target's SCSI ID
    BYTE        SRB_Lun;                        // 09/009 Target's LUN number
    BYTE        SRB_ResetRsvd1[14];             // 0A/010 Reserved, MUST = 0
    BYTE        SRB_HaStat;                     // 18/024 Host Adapter Status
    BYTE        SRB_TargStat;                   // 19/025 Target Status
    VOID        FAR *SRB_PostProc;              // 1A/026 Post routine
    BYTE        SRB_ResetRsvd2[34];             // 1E/030 Reserved, MUST = 0
}
SRB16_BusDeviceReset, *PSRB16_BusDeviceReset, FAR *LPSRB16_BusDeviceReset;

/**++SDK_16ONLY://*****************************************************************************++**/
/**++SDK_16ONLY://          %%% PROTOTYPES - User Callable ASPI for Win16 Functions %%%++**/
/**++SDK_16ONLY://*****************************************************************************++**/
/**++SDK_16ONLY:++**/
/**++SDK_16ONLY:typedef BYTE far *LPSRB;++**/
/**++SDK_16ONLY:++**/
/**++SDK_16ONLY:WORD FAR PASCAL SendASPICommand( LPSRB );++**/
/**++SDK_16ONLY:WORD FAR PASCAL GetASPISupportInfo( VOID );++**/

/*
** Restore compiler default packing and close off the C declarations.
*/

#ifdef _MSC_VER
#pragma pack()
#endif //_MSC_VER

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //__WINASPI_H__
