/*++ BUILD Version: 0001    // Increment this if a change has global effects

Copyright (c) 1990-1998  Microsoft Corporation

Module Name:

    ceddcdrm.h

Abstract:

    This module contains structures and definitions
    associated with CDROM IOCTls.

Author:

    Mike Glass

Revision History:

--*/

//
// NtDeviceIoControlFile IoControlCode values for this device.
//
// Warning:  Remember that the low two bits of the code specify how the
//           buffers are passed to the driver!
//

#define IOCTL_CDROM_BASE                 FILE_DEVICE_CD_ROM

#define IOCTL_CDROM_UNLOAD_DRIVER        CTL_CODE(IOCTL_CDROM_BASE, 0x0402, METHOD_BUFFERED, FILE_READ_ACCESS)

//
// CDROM Audio Device Control Functions
//

#define IOCTL_CDROM_READ_TOC         CTL_CODE(IOCTL_CDROM_BASE, 0x0000, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_CDROM_GET_CONTROL      CTL_CODE(IOCTL_CDROM_BASE, 0x000D, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_CDROM_PLAY_AUDIO_MSF   CTL_CODE(IOCTL_CDROM_BASE, 0x0006, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_CDROM_SEEK_AUDIO_MSF   CTL_CODE(IOCTL_CDROM_BASE, 0x0001, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_CDROM_STOP_AUDIO       CTL_CODE(IOCTL_CDROM_BASE, 0x0002, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_CDROM_PAUSE_AUDIO      CTL_CODE(IOCTL_CDROM_BASE, 0x0003, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_CDROM_RESUME_AUDIO     CTL_CODE(IOCTL_CDROM_BASE, 0x0004, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_CDROM_GET_VOLUME       CTL_CODE(IOCTL_CDROM_BASE, 0x0005, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_CDROM_SET_VOLUME       CTL_CODE(IOCTL_CDROM_BASE, 0x000A, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_CDROM_READ_Q_CHANNEL   CTL_CODE(IOCTL_CDROM_BASE, 0x000B, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_CDROM_GET_LAST_SESSION CTL_CODE(IOCTL_CDROM_BASE, 0x000E, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_CDROM_RAW_READ         CTL_CODE(IOCTL_CDROM_BASE, 0x000F, METHOD_OUT_DIRECT,  FILE_READ_ACCESS)
#define IOCTL_CDROM_DISK_TYPE        CTL_CODE(IOCTL_CDROM_BASE, 0x0010, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_CDROM_SCAN_AUDIO       CTL_CODE(IOCTL_CDROM_BASE, 0x0020, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_CDROM_GET_DRIVE_GEOMETRY CTL_CODE(IOCTL_CDROM_BASE, 0x0013, METHOD_BUFFERED, FILE_READ_ACCESS)

//
// The following device control codes are common for all class drivers.  The
// functions codes defined here must match all of the other class drivers.
//
// Warning: these codes will be replaced in the future with the IOCTL_STORAGE
// codes included below
//

#define IOCTL_CDROM_CHECK_VERIFY    CTL_CODE(IOCTL_CDROM_BASE, 0x0200, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_CDROM_MEDIA_REMOVAL   CTL_CODE(IOCTL_CDROM_BASE, 0x0201, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_CDROM_EJECT_MEDIA     CTL_CODE(IOCTL_CDROM_BASE, 0x0202, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_CDROM_LOAD_MEDIA      CTL_CODE(IOCTL_CDROM_BASE, 0x0203, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_CDROM_RESERVE         CTL_CODE(IOCTL_CDROM_BASE, 0x0204, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_CDROM_RELEASE         CTL_CODE(IOCTL_CDROM_BASE, 0x0205, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_CDROM_FIND_NEW_DEVICES CTL_CODE(IOCTL_CDROM_BASE, 0x0206, METHOD_BUFFERED, FILE_READ_ACCESS)

#define IOCTL_CDROM_READ_SG         CTL_CODE(IOCTL_CDROM_BASE, 0x0301, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_CDROM_TEST_UNIT_READY CTL_CODE(IOCTL_CDROM_BASE, 0x0302, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_CDROM_DISC_INFO       CTL_CODE(IOCTL_CDROM_BASE, 0x0303, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_CDROM_TRACK_INFO      CTL_CODE(IOCTL_CDROM_BASE, 0x0304, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_CDROM_SET_SPEED       CTL_CODE(IOCTL_CDROM_BASE, 0x0305, METHOD_BUFFERED, FILE_READ_ACCESS)


//
// The following file contains the IOCTL_STORAGE class ioctl definitions
//

#include "ceddstor.h"

//
// Maximum CD Rom size
//

#define MAXIMUM_NUMBER_TRACKS 100
#define MAXIMUM_CDROM_SIZE 804

//
// CD ROM Table OF Contents (TOC)
//
// Format 0 - Get table of contents
//

typedef struct _TRACK_DATA {
    UCHAR Reserved;
    UCHAR Control : 4;
    UCHAR Adr : 4;
    UCHAR TrackNumber;
    UCHAR Reserved1;
    UCHAR Address[4];
} TRACK_DATA, *PTRACK_DATA;

typedef struct _CDROM_TOC {

    //
    // Header
    //

    UCHAR Length[2];
    UCHAR FirstTrack;
    UCHAR LastTrack;

    //
    // Track data
    //

    TRACK_DATA TrackData[MAXIMUM_NUMBER_TRACKS];
} CDROM_TOC, *PCDROM_TOC;

#define CDROM_TOC_SIZE sizeof(CDROM_TOC)

//
// Play audio starting at MSF and ending at MSF
//

typedef struct _CDROM_PLAY_AUDIO_MSF {
    UCHAR StartingM;
    UCHAR StartingS;
    UCHAR StartingF;
    UCHAR EndingM;
    UCHAR EndingS;
    UCHAR EndingF;
} CDROM_PLAY_AUDIO_MSF, *PCDROM_PLAY_AUDIO_MSF;

//
// Seek to MSF
//

typedef struct _CDROM_SEEK_AUDIO_MSF {
    UCHAR M;
    UCHAR S;
    UCHAR F;
} CDROM_SEEK_AUDIO_MSF, *PCDROM_SEEK_AUDIO_MSF;


//
//  Flags for the disk type
//

typedef struct _CDROM_DISK_DATA {

    ULONG DiskData;

} CDROM_DISK_DATA, *PCDROM_DISK_DATA;

#define CDROM_DISK_AUDIO_TRACK      (0x00000001)
#define CDROM_DISK_DATA_TRACK       (0x00000002)

//
// CD ROM Data Mode Codes, used with IOCTL_CDROM_READ_Q_CHANNEL
//

#define IOCTL_CDROM_SUB_Q_CHANNEL    0x00
#define IOCTL_CDROM_CURRENT_POSITION 0x01
#define IOCTL_CDROM_MEDIA_CATALOG    0x02
#define IOCTL_CDROM_TRACK_ISRC       0x03

typedef struct _CDROM_SUB_Q_DATA_FORMAT {
    UCHAR Format;
    UCHAR Track;
} CDROM_SUB_Q_DATA_FORMAT, *PCDROM_SUB_Q_DATA_FORMAT;


//
// CD ROM Sub-Q Channel Data Format
//

typedef struct _SUB_Q_HEADER {
    UCHAR Reserved;
    UCHAR AudioStatus;
    UCHAR DataLength[2];
} SUB_Q_HEADER, *PSUB_Q_HEADER;

typedef struct _SUB_Q_CURRENT_POSITION {
    SUB_Q_HEADER Header;
    UCHAR FormatCode;
    UCHAR Control : 4;
    UCHAR ADR : 4;
    UCHAR TrackNumber;
    UCHAR IndexNumber;
    UCHAR AbsoluteAddress[4];
    UCHAR TrackRelativeAddress[4];
} SUB_Q_CURRENT_POSITION, *PSUB_Q_CURRENT_POSITION;

typedef struct _SUB_Q_MEDIA_CATALOG_NUMBER {
    SUB_Q_HEADER Header;
    UCHAR FormatCode;
    UCHAR Reserved[3];
    UCHAR Reserved1 : 7;
    UCHAR Mcval : 1;
    UCHAR MediaCatalog[15];
} SUB_Q_MEDIA_CATALOG_NUMBER, *PSUB_Q_MEDIA_CATALOG_NUMBER;

typedef struct _SUB_Q_TRACK_ISRC {
    SUB_Q_HEADER Header;
    UCHAR FormatCode;
    UCHAR Reserved0;
    UCHAR Track;
    UCHAR Reserved1;
    UCHAR Reserved2 : 7;
    UCHAR Tcval : 1;
    UCHAR TrackIsrc[15];
} SUB_Q_TRACK_ISRC, *PSUB_Q_TRACK_ISRC;

typedef union _SUB_Q_CHANNEL_DATA {
    SUB_Q_CURRENT_POSITION CurrentPosition;
    SUB_Q_MEDIA_CATALOG_NUMBER MediaCatalog;
    SUB_Q_TRACK_ISRC TrackIsrc;
} SUB_Q_CHANNEL_DATA, *PSUB_Q_CHANNEL_DATA;

//
// Audio Status Codes
//

#define AUDIO_STATUS_NOT_SUPPORTED  0x00
#define AUDIO_STATUS_IN_PROGRESS    0x11    // PLAY
#define AUDIO_STATUS_PAUSED         0x12    // PAUSE
#define AUDIO_STATUS_PLAY_COMPLETE  0x13
#define AUDIO_STATUS_PLAY_ERROR     0x14
#define AUDIO_STATUS_NO_STATUS      0x15    // STOP

//
// ADR Sub-channel Q Field
//

#define ADR_NO_MODE_INFORMATION     0x0
#define ADR_ENCODES_CURRENT_POSITION 0x1
#define ADR_ENCODES_MEDIA_CATALOG   0x2
#define ADR_ENCODES_ISRC            0x3

//
// Sub-channel Q Control Bits
//

#define AUDIO_WITH_PREEMPHASIS      0x0
#define DIGITAL_COPY_PERMITTED      0x2
#define AUDIO_DATA_TRACK            0x4
#define TWO_FOUR_CHANNEL_AUDIO      0x8

//
// Get Audio control parameters
//

typedef struct _CDROM_AUDIO_CONTROL {
    UCHAR LbaFormat;
    USHORT LogicalBlocksPerSecond;
} CDROM_AUDIO_CONTROL, *PCDROM_AUDIO_CONTROL;

//
// Volume control - Volume takes a value between 1 and 0xFF.
// SCSI-II CDROM audio suppports up to 4 audio ports with
// Independent volume control.
//

typedef struct _VOLUME_CONTROL {
    UCHAR PortVolume[4];
} VOLUME_CONTROL, *PVOLUME_CONTROL;

typedef enum _TRACK_MODE_TYPE {
    YellowMode2,
    XAForm2,
    CDDA
} TRACK_MODE_TYPE, *PTRACK_MODE_TYPE;

//
// Passed to cdrom to describe the raw read, ie. Mode 2, Form 2, CDDA...
//

typedef struct __RAW_READ_INFO {
    LARGE_INTEGER DiskOffset;
    ULONG    SectorCount;
    TRACK_MODE_TYPE TrackMode;
} RAW_READ_INFO, *PRAW_READ_INFO;

//
// Scan audio starting at Address
//

typedef struct _CDROM_SCAN_AUDIO {
    UCHAR Reserved  : 4;
    UCHAR Direction : 1;    // 0 = Fast Forward, 1 = Fast Reverse
    UCHAR Reserved1 : 3;
    UCHAR Address[4];
    UCHAR Reserved2[3];
    UCHAR Reserved3 : 6;
    UCHAR AddressType : 2;  // 0 = LBA, 1 = MSF, 2 = Track Number
} CDROM_SCAN_AUDIO, *PCDROM_SCAN_AUDIO;


/***	Definitions for CD-ROM Disk Addresses
 *
 *	Two standards are available for addressing the disk, known as
 *	the Redbook (MSF) or the High Sierra Group (HSG) addresses.
 *	Redbook addresses are given as Minute, Second, and Frame numbers.
 *	HSG addresses are just logical block addresses, as an unsigned long.
 *	The term "LBA", for "logical block address", is preferred over HSG.
 *	The standard conversion formula between these two formats is
 *	Sector = (((Minute*60) + Second)*75) + Frame;
 */


/***	The MSF_ADDR structure describes a disk address in Redbook format.
 *	The Minute, Second, and Frame are given as binary numbers.
 *	BEWARE: In some cases, the MSF is given as 3 pairs of BCD digits
 *	on disk.   This format only specifies the binary number version.
 */

typedef struct	MSF_ADDR { /* */
    UCHAR   msf_Frame;
    UCHAR   msf_Second;
    UCHAR   msf_Minute;
    UCHAR   msf_Filler;
} MSF_ADDR, *PMSF_ADDR;


/***	The LBA_ADDR typedef describes a disk address in HSG format.
 */

typedef ULONG	LBA_ADDR;


/***	The MSF_LBA union combines both Redbook and HSG formats
 */

typedef union	MSF_LBA { /* */
    MSF_ADDR	msf;
    LBA_ADDR	lba;
} MSF_LBA;


#define CDROM_ADDR_LBA	0
#define CDROM_ADDR_MSF	1


/***	The CDROM_ADDR structure is used to store addresses of either format.
 */

typedef struct	CDROM_ADDR { /* */
    ULONG   Mode;
    MSF_LBA Address;
} CDROM_ADDR, *PCDROM_ADDR;

/***	These macros convert either format of CDROM address to the other.
 *	They are written as expressions rather than functions to simplify
 *	callers.  Converting LBA to MSF format is more difficult, and
 *	requires a temporary variable of type MSF_ADDR.
 */

#define CDROM_MSF_TO_LBA(pcdra) 		\
    (((pcdra)-> Mode = CDROM_ADDR_LBA), 	\
     (((pcdra)-> Address.lba) = (LBA_ADDR) (	   \
       (((pcdra)-> Address.msf.msf_Minute) * 60 +  \
	((pcdra)-> Address.msf.msf_Second)) * 75 + \
       ((pcdra)-> Address.msf.msf_Frame)) - 150))

#define CDROM_MSFCOMP_TO_LBA(min, sec, frame) 	\
    ((LBA_ADDR)((((min) * 60 + (sec)) * 75 + ((frame)) - 150)))
       
#define CDROM_LBA_TO_MSF(pcdra,msfTemp) 			\
    (								\
	((pcdra)-> Mode = CDROM_ADDR_MSF),			\
	(((pcdra)-> Address.lba) += 150),			\
	(msfTemp.msf_Frame  = (UCHAR)(((pcdra)-> Address.lba) % 75)),	\
	(((pcdra)-> Address.lba) /= 75),			\
	(msfTemp.msf_Second = (UCHAR)(((pcdra)-> Address.lba) % 60)),	\
	(((pcdra)-> Address.lba) /= 60),			\
	(msfTemp.msf_Minute = (UCHAR)(((pcdra)-> Address.lba))), 	\
	(msfTemp.msf_Filler = 0),				\
	((pcdra)-> Address.msf.msf_Filler = msfTemp.msf_Filler),\
	((pcdra)-> Address.msf.msf_Minute = msfTemp.msf_Minute),\
	((pcdra)-> Address.msf.msf_Second = msfTemp.msf_Second),\
	((pcdra)-> Address.msf.msf_Frame  = msfTemp.msf_Frame)	\
    )

typedef struct _SGX_BUF {
	PUCHAR sb_buf;        // pointer to buffer
	DWORD  sb_len;        // length of buffer
} SGX_BUF, *PSGX_BUF; 

typedef struct	CDROM_READ { /* */
    CDROM_ADDR	    StartAddr;		    // Sector number to read from
    DWORD           TransferLength;     // Number of blocks to read
    BOOL            bRawMode;           // Raw mode?
    TRACK_MODE_TYPE TrackMode;          // Only used if bRawMode == TRUE
    DWORD           sgcount;            // Count of scatter gather buffers
    SGX_BUF         sglist[1];          // first scatter/gather buffer
} CDROM_READ, *PCDROM_READ;

/***	CDROM_IOCTL_TEST_UNIT_READY 
 *
 *	CDROM_IOCTL_TEST_UNIT_READ - Check for unit ready
 *
 *	ENTRY
 *
 *	EXIT
 *	    Success
 *		Returns NO_ERROR
 *		CDROM_UNITREADY - filled
 *
 *	    Failure
 *		Returns an extended error code.
 *		ERROR_UNKNOWN_COMMAND - The command is not supported
 *		ERROR_INVALID_PARAMETER - The desired speed is not supported
 *		Other Extended Errors may also be returned
 *
 */

typedef struct	CDROM_TESTUNITREADY { /* */
    ULONG	Reserved;		// Reserved - must be zero
    BOOL    bUnitReady;		// Is unit ready
} CDROM_TESTUNITREADY, *PCDROM_TESTUNITREADY;

/***	CDROM_IOCTL_DISC_INFO - Get Disk Information
 *
 *	This function returns the TOC (table of contents) information
 *	from the Q-channel in the lead-in track of the disc, which
 *	indicates the starting and ending tracks and the start of
 *	the lead-out track.
 *
 *	The first and last track number are binary values, not BCD.
 *
 *	It is recommended that the information from the TOC be read
 *	in and cached on drive initialization so that when this function
 *	is called, there is not need to interrupt drive play to get this
 *	information.  Note that the first and last track numbers do not
 *	include the lead-in and lead-out tracks of the session.
 *
 *	The SessionIndex is used to get TOC information from disks
 *	with more than one recorded session.  Sessions are the same
 *	as OrangeBook Volumes.	The first session has a SessionIndex
 *	of zero, and the second session has a SessionIndex of one.
 * A SessionIndex of DISC_INFO_LAST_SESSION (-1) requests the disc
 * info for the last session recorded on the disc.
 *
 *	The LogicStartAddr is the logical sector address of the first
 *	data sector of the first track in this session.
 *
 *	For standard Redbook and Yellowbook CD-ROMs, zero (0) is the
 *	only valid SessionIndex value.	In this case, LogicStartAddr
 *	should be returned as zero (0).
 *
 *	Note: The LogicStartAddr is normally used to locate the first
 *	sector of the Volume Recognition Sequence for the indicated
 *	session. The Volume Recognition Sequence for the session is
 *	expected to start at Sector (LogicStartAddr + 16).
 *
 *	ENTRY
 *	    IOCTL Packet format specified by CDROM_DISCINFO structure.
 *	    Reserved - Reserved Zero
 *	    SessionIndex - Set to desired session number to query.
 *		SessionIndex = 0 indicates a query for the first session
 *		SessionIndex = 0xFFFFFFFF indicates a query for the last
 *		    session on the disk
 *
 *	EXIT
 *	    Success
 *		Returns NO_ERROR
 *		CDROM_DISCINFO structure filled in for indicated session
 *
 *		If SessionIndex was passed in as 0xFFFFFFFF, it may be
 *		modified to contain the index of the last session on the
 *		disk.  Because not all device drivers must scan through
 *		all the sessions on the disk, this update may or may not
 *		actually take place.
 *
 *	    Failure
 *		Returns an extended error code.
 *		ERROR_UNKNOWN_COMMAND - The command is not supported
 *		ERROR_INVALID_PARAMETER - The session number is invalid
 *		Other Extended Errors may also be returned
 */

typedef struct	CDROM_DISCINFO { /* */
    ULONG	Reserved;		// Reserved - must be zero
    ULONG	FirstTrack;		// First Track of Session
    ULONG	LastTrack;		// Last Track of Session
    MSF_ADDR	LeadOutTrackAddr;	// Address of Lead-out Track of Session
    UCHAR	FirstSession;
    UCHAR	LastSession;
    UCHAR	ReqSession;
    UCHAR	RetSession;
    ULONG	LogicStartAddr; 	// Session Logical Start Acdress
} CDROM_DISCINFO, *PCDROM_DISCINFO;

#define DISC_INFO_LAST_SESSION 0xFF

/***	CDROM_IOCTL_TRACK_INFO - Get Track Parameters
 *
 *	This function takes a binary track number in the range
 *	specified by the first and last track number for the disk
 *	and returns the Redbook address for the starting point of
 *	the track and control information for the track.  The control
 *	information is contained in the 4 most significant bits of the
 *	control information byte.  The definitions of the bit fields
 *	are given below.
 *
 *	It is recommended that the information from the TOC be read
 *	in and cached on drive initialization so that when this function
 *	is called, there is not need to interrupt drive play to get this
 *	information.
 *
 *	ENTRY
 *	    IOCTL Packet format specified by CDROM_TRACKINFO structure.
 *	    Reserved - Reserved Zero
 *	    TrackNumber - Set to desired track number to query.
 *
 *	EXIT
 *	    Success
 *		Returns NO_ERROR
 *		CDROM_TRACKINFO structure filled in for indicated track
 *
 *	    Failure
 *		Returns an extended error code.
 *		ERROR_UNKNOWN_COMMAND - The command is not supported
 *		ERROR_INVALID_PARAMETER - The track number is invalid
 *		Other Extended Errors may also be returned
 *
 *	TrackControl Bit Definitions
 *
 *	Bit	Definition
 *	0-3	ADR information
 *	4	0 - No preemphasis on audio channels
 *		1 - Preemphasis on audio channels
 *	5	0 - Digital copy prohibited
 *		1 - Digital copy allowed
 *	6	0 - Audio Track
 *		1 - Data Track
 *	7	0 - 2 Audio channels
 *		1 - 4 Audio channels
 */

typedef struct	CDROM_TRACKINFO    { /* */
    ULONG	Reserved;		// Reserved - must be zero
    ULONG	TrackNumber;		// Desired Track Number
    MSF_ADDR	TrackAddr;		// Track Starting Address
    ULONG	TrackControl;		// Track Control Flags (CDTRACK_)
} CDROM_TRACKINFO, *PCDROM_TRACKINFO;

#define CDTRACK_ADRMASK     0x0F	// ADR Information
#define CDTRACK_PREEMPHASIS 0x10	// Audio Preemphasis Indicator
#define CDTRACK_COPYOK	    0x20	// Digital Copy Allowed
#define CDTRACK_DATA	    0x40	// Data Track
#define CDTRACK_4CHANNEL    0x80	// 4 Audio Channels


/***	CDROM_IOCTL_GET_AUDIO_STATE - Get Audio Pause State
 *
 *	CDROM_IOCTL_GET_AUDIO_STATE returns inforation about the current
 *	audio state.
 *
 *	This function returns information about whether audio is playing
 *	or paused on the drive.
 *
 *	If the audio is paused, the Redbook starting and ending addresses
 *	for the resume audio operation are returned.
 *
 *	ENTRY
 *	    IOCTL Packet format specified by CDROM_AUDSTATE structure.
 *	    Reserved - Reserved Zero
 *	    CDROM_AUDSTATE contents = don't care
 *
 *	EXIT
 *	    Success
 *		Returns NO_ERROR
 *		CDROM_AUDSTATE structure filled in
 *		Bits of AudioFlags set according to CDAUDSTAT definitions
 *
 *	    Failure
 *		Returns an extended error code.
 *		ERROR_UNKNOWN_COMMAND - The command is not supported
 *		Other Extended Errors may also be returned
 *
 *	AudioFlags Bit Definitions
 *
 *	Bit	Definition
 *	0	0 - Audio is not paused
 *		1 - Audio is paused
 *	1	0 - Audio play request is in progress
 *		1 - There are no play requests in progress
 *	1-15	Reserved (must be zero)
 *
 */

typedef struct	CDROM_AUDSTATE { /* */
    ULONG	Reserved;		// Reserved - must be zero
    ULONG	AudioFlags;		// Audio Pause Flags
    MSF_ADDR	StartAddress;		// Starting Address for Audio Resume
    MSF_ADDR	EndAddress;		// Ending Address for Audio Resume
} CDROM_AUDSTATE, *PCDROM_AUDSTATE;

#define CDAUDSTAT_PAUSED    0x0001
#define CDAUDSTAT_PLAYING   0x0002

// Set spindle speed for reading data off the CD

typedef struct _CDROM_SPEED {
    USHORT ReadSpeed;           // Drive read speed in KB/s, 0xFFFF for max
    USHORT Reserved;
} CDROM_SPEED, *PCDROM_SPEED;
