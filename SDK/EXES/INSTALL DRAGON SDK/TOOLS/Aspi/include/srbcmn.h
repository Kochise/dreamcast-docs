/**!!SDK_COMMON!!**/
/**++SDK_PRIVATE++**/
/**++SDK_COMMON++**/
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
** THIS FILE IS FOR INTERNAL ADAPTEC USE ONLY!  THIS FILE IS NOT FOR INCLUSION
** IN THE ASPI SOFTWARE DEVELOPMENT KIT AND IT SHOULD NOT BE MAILED OR POSTED!
******************************************************************************/

/**++SDK_EXCLUDE++**/
/******************************************************************************
**
**  Module Name:    srbcmn.h
**
**  Description:    SRB definitions common to both ASPI for Win16 and ASPI for
**                  Win32.  Look in srb16.h and srb32.h for ASPI for Win 16/32
**                  specific structures and definitions.
**
**                  This file should be combined with srb16.h and cleaned
**                  up to produce the winaspi.h for the SDK.  Similarly, this
**                  file should be combined with srb32.h and cleaned up to
**                  produce wnaspi32.h for the SDK.
**
**  Programmers:    Daniel Polfer (dap)
**
**  History:        11/09/95 (dap)  Initial creation.
**                  12/18/95 (dap)  Added max timeout value.
**                  02/20/96 (dap)  Added SRB_NO_ERROR_POSTING.
**                  09/03/96 (dap)  Renamed and modified to be shared between
**                                  ring-0 and ring-3 code bases.
**                  09/13/96 (dap)  Added queue management structures, etc.
**                  06/24/98 (dap)  Modified to use allow auto-SDK generation.
**                  11-27-01 (jck)  Correct spelling of TOO_BIG.
**
**  Notes:          This file created using 4 spaces per tab.
**
**                  This file is NOT a customer deliverable to be included
**                  with the ASPI SDK.  It is specific to our ASPI
**                  implementation and contains definitions of private
**                  Adpatec structures.
**
******************************************************************************/

#ifndef __SRBCMN_H__
#define __SRBMCN_H__

/**++SDK_PUBLIC++**/
/**++SDK_32ONLY++**/
/******************************************************************************
**
**  Module Name:    wnaspi32.h
**
**  Description:    Header file for ASPI for Win32.  This header includes
**                  macro and type declarations, and can be included without
**                  modification when using Borland C++ or Microsoft Visual
**                  C++ with 32-bit compilation.  If you are using a different
**                  compiler then you MUST ensure that structures are packed
**                  onto byte alignments, and that C++ name mangling is turned
**                  off.
**
**  Notes:          This file created using 4 spaces per tab.
**
******************************************************************************/
/**++SDK_32ONLY:++**/
/**++SDK_32ONLY:#ifndef __WNASPI32_H__++**/
/**++SDK_32ONLY:#define __WNASPI32_H__++**/
/**++SDK_16ONLY++**/
/******************************************************************************
**
**  Module Name:    winaspi.h
**
**  Description:    Header file for ASPI for Win16.  This header includes
**                  macro and type declarations, and can be included without
**                  modification when Microsoft Visual C++ with 16-bit
**                  compilation.  If you are using a different compiler then
**                  you MUST ensure that structures are packed onto byte
**                  alignments, and that C++ name mangling is turned off.
**
**  Notes:          This file created using 4 spaces per tab.
**
******************************************************************************/
/**++SDK_16ONLY:++**/
/**++SDK_16ONLY:#ifndef __WINASPI_H__++**/
/**++SDK_16ONLY:#define __WINASPI_H__++**/
/**++SDK_COMMON++**/

/*
** Make sure structures are packed and undecorated.
*/

/**++SDK_32ONLY++**/
#ifdef __BORLANDC__
#pragma option -a1
#endif //__BORLANDC__

/**++SDK_COMMON++**/
#ifdef _MSC_VER
#pragma pack(1)
#endif //__MSC_VER

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

//*****************************************************************************
//      %%% SCSI MISCELLANEOUS EQUATES %%%
//*****************************************************************************

#define SENSE_LEN                   14          // Default sense buffer length
#define SRB_DIR_SCSI                0x00        // Direction determined by SCSI
#define SRB_POSTING                 0x01        // Enable ASPI posting
#define SRB_ENABLE_RESIDUAL_COUNT   0x04        // Enable residual byte count reporting
#define SRB_DIR_IN                  0x08        // Transfer from SCSI target to host
#define SRB_DIR_OUT                 0x10        // Transfer from host to SCSI target
/**++SDK_32ONLY++**/
#define SRB_EVENT_NOTIFY            0x40        // Enable ASPI event notification

#define RESIDUAL_COUNT_SUPPORTED    0x02        // Extended buffer flag
#define MAX_SRB_TIMEOUT             108000lu    // 30 hour maximum timeout in s
#define DEFAULT_SRB_TIMEOUT         108000lu    // Max timeout by default

/**++SDK_EXCLUDE++**/
#define SRB_NO_ERROR_POSTING        0x02        // Do not post completion on error
#define SRB_HEAD_OF_QUEUE           0x20        // Insert SRB at queue head
#define SRB_BYPASS_QUEUE            0x80        // Bypass queue management

/**++SDK_PRIVATE++**/
/**++SDK_32ONLY++**/
#define SRBQ_ENABLE_QUEUEING        0x01        // Enable queueing for a target
#define SRBQ_FREEZE_QUEUE           0x02        // Freeze a target queue
#define SRBQ_UNFREEZE_QUEUE         0x03        // Unfreeze a target queue
#define SRBQ_CLEAR_QUEUE            0x04        // Clear a frozen target queue
#define SRBQ_QUERY_QUEUE            0x05        // Return queue status
#define SRBQ_SET_CDB_DELAY          0x06        // Set delay on a select CDB
#define SRBQ_DISABLE_QUEUEING       0x00        // Disable queueing for a target

/**++SDK_PUBLIC++**/
/**++SDK_COMMON++**/

//*****************************************************************************
//      %%% ASPI Command Definitions %%%
//*****************************************************************************

#define SC_HA_INQUIRY               0x00        // Host adapter inquiry
#define SC_GET_DEV_TYPE             0x01        // Get device type
#define SC_EXEC_SCSI_CMD            0x02        // Execute SCSI command
#define SC_ABORT_SRB                0x03        // Abort an SRB
#define SC_RESET_DEV                0x04        // SCSI bus device reset
#define SC_SET_HA_PARMS             0x05        // Set HA parameters
#define SC_GET_DISK_INFO            0x06        // Get Disk information
#define SC_SEEPROM					0xe1		// Get SEEPROM Contents
#define SC_EEPROM					0xe2		// Get EEPROM Contents
#define SC_PCIINFO					0xe3		// Get SEEPROM Contents
#define SC_NEGO_XFER_RATE			0xe4		// Get SEEPROM Contents
#define OC_SEEPROM_READ				0xa1		// Read SEEPROM Contents
#define OC_SEEPROM_WRITE			0xa2		// Write SEEPROM Contents
#define OC_SEEPROM_DETECT			0xa3		// Detect SEEPROM
#define OC_SEEPROM_ERASE			0xa4		// Erase SEEPROM
#define OC_EEPROM_READ				0xb1		// Read SEEPROM Contents
#define OC_EEPROM_WRITE				0xb2		// Write SEEPROM Contents
#define OC_PCIINFO_READ				0xc1
#define OC_PCIINFO_WRITE			0xc2
#define OC_NEGO_XFER_RATE_READ		0xd1

#define	MAX_SCSI_DEVS			16

	/**++SDK_32ONLY++**/
#define SC_RESCAN_SCSI_BUS          0x07        // ReBuild SCSI device map
#define SC_GETSET_TIMEOUTS          0x08        // Get/Set target timeouts
/**++SDK_PRIVATE++**/
#define SC_MANAGE_QUEUE             0xC8        // Manage per-target SRB queues
/**++SDK_PUBLIC++**/
/**++SDK_COMMON++**/

//*****************************************************************************
//      %%% SRB Status %%%
//*****************************************************************************

#define SS_PENDING                  0x00        // SRB being processed
#define SS_COMP                     0x01        // SRB completed without error
#define SS_ABORTED                  0x02        // SRB aborted
#define SS_ABORT_FAIL               0x03        // Unable to abort SRB
#define SS_ERR                      0x04        // SRB completed with error

/**++SDK_PRIVATE++**/
#define SS_ABORTED_QUEUE_FROZEN     0x42        // SRB aborted, target queue frozen
#define SS_ERR_QUEUE_FROZEN         0x44        // SRB completed with error, target queue frozen
#define SS_BUFFTOBIG_QUEUE_FROZEN   0x4F        // SRB buffer too big, target queue frozen

/**++SDK_PUBLIC++**/
#define SS_INVALID_CMD              0x80        // Invalid ASPI command
#define SS_INVALID_HA               0x81        // Invalid host adapter number
#define SS_NO_DEVICE                0x82        // SCSI device not installed

#define SS_INVALID_SRB              0xE0        // Invalid parameter set in SRB
#define SS_OLD_MANAGER              0xE1        // ASPI manager doesn't support Windows
#define SS_BUFFER_ALIGN             0xE1        // Buffer not aligned (replaces OLD_MANAGER in Win32)
#define SS_ILLEGAL_MODE             0xE2        // Unsupported Windows mode
#define SS_NO_ASPI                  0xE3        // No ASPI managers resident
#define SS_FAILED_INIT              0xE4        // ASPI for windows failed init
#define SS_ASPI_IS_BUSY             0xE5        // No resources available to execute cmd
#define SS_BUFFER_TO_BIG            0xE6        // Buffer size to big to handle!
#define SS_BUFFER_TOO_BIG           0xE6        // Buffer size toobig to handle!
#define SS_MISMATCHED_COMPONENTS    0xE7        // The DLLs/EXEs of ASPI don't version check
#define SS_NO_ADAPTERS              0xE8        // No host adapters to manage
#define SS_INSUFFICIENT_RESOURCES   0xE9        // Couldn't allocate resources needed to init
#define SS_ASPI_IS_SHUTDOWN         0xEA        // Call came to ASPI after PROCESS_DETACH
#define SS_BAD_INSTALL              0xEB        // The DLL or other components are installed wrong

//*****************************************************************************
//      %%% Host Adapter Status %%%
//*****************************************************************************

#define HASTAT_OK                   0x00        // Host adapter did not detect an                                                                                                                       // error
#define HASTAT_SEL_TO               0x11        // Selection Timeout
#define HASTAT_DO_DU                0x12        // Data overrun data underrun
#define HASTAT_BUS_FREE             0x13        // Unexpected bus free
#define HASTAT_PHASE_ERR            0x14        // Target bus phase sequence                                                                                                                            // failure
#define HASTAT_TIMEOUT              0x09        // Timed out while SRB was                                                                                                                                      waiting to beprocessed.
#define HASTAT_COMMAND_TIMEOUT      0x0B        // Adapter timed out processing SRB.
#define HASTAT_MESSAGE_REJECT       0x0D        // While processing SRB, the                                                                                                                            // adapter received a MESSAGE
#define HASTAT_BUS_RESET            0x0E        // A bus reset was detected.
#define HASTAT_PARITY_ERROR         0x0F        // A parity error was detected.
#define HASTAT_REQUEST_SENSE_FAILED 0x10        // The adapter failed in issuing

/**++SDK_EXCLUDE++**/
//*****************************************************************************
//          %%% SRB - HEADER %%%
//*****************************************************************************

typedef struct                                  // Offset
{                                               // HX/DEC
    BYTE        SRB_Cmd;                        // 00/000
    BYTE        SRB_Status;                     // 01/001
    BYTE        SRB_HaId;                       // 02/002
    BYTE        SRB_Flags;                      // 03/003
    DWORD       SRB_Hdr_Rsvd;                   // 04/004
}
SRB_Header, *PSRB_Header, FAR *LPSRB_Header;

/*
** SCSI address of a target.  Just a convenient way to group the HA/ID/LUN
** together and be able to use them individually or as a DWORD path variable.
*/

typedef union
{
    struct
    {
        BYTE    Lun;
        BYTE    TargetId;
        BYTE    HaId;
        BYTE    Flag;
    } by;
    struct
    {
        DWORD   Path;
    } dw;
}
SCSIADDR, *PSCSIADDR;

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

#endif //__SRBCMN_H__
