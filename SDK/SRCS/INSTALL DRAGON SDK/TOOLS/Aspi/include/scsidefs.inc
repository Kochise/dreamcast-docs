;****************************************************************************
;
; Name: 	SCSIDEFS.INC
;
; Description:	SCSI definitions (Assembly Language)
;
;****************************************************************************

;****************************************************************************
;		     %%% TARGET STATUS VALUES %%%
;****************************************************************************
STATUS_GOOD	equ	00h	;Status Good
STATUS_CHKCOND	equ	02h	;Check Condition
STATUS_CONDMET	equ	04h	;Condition Met
STATUS_BUSY	equ	08h	;Busy
STATUS_INTERM	equ	10h	;Intermediate
STATUS_INTCDMET equ	14h	;Intermediate-condition met
STATUS_RESCONF	equ	18h	;Reservation conflict
STATUS_COMTERM	equ	22h	;Command Terminated
STATUS_QFULL	equ	28h	;Queue full

;****************************************************************************
;		  %%% SCSI MISCELLANEOUS EQUATES %%%
;****************************************************************************
MAXLUN		equ	7	;Maximum Logical Unit Id
MAXTARG 	equ	7	;Maximum Target Id
MAX_SCSI_LUNS	equ	64	;Maximum Number of SCSI LUNs
MAX_NUM_HA	equ	8	;Maximum Number of SCSI HA's

;/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\
;
;		     %%% SCSI COMMAND OPCODES %%%
;
;\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/

;****************************************************************************
;		%%% Commands for all Device Types %%%
;****************************************************************************
SCSI_CHANGE_DEF equ	040h	;Change Definition (Optional)
SCSI_COMPARE	equ	039h	;Compare (O)
SCSI_COPY	equ	018h	;Copy (O)
SCSI_COP_VERIFY equ	03Ah	;Copy and Verify (O)
SCSI_INQUIRY	equ	012h	;Inquiry (MANDATORY)
SCSI_LOG_SELECT equ	04Ch	;Log Select (O)
SCSI_LOG_SENSE	equ	04Dh	;Log Sense (O)
SCSI_MODE_SEL6	equ	015h	;Mode Select 6-byte (Device Specific)
SCSI_MODE_SEL10	equ	055h	;Mode Select 10-byte (Device Specific)
SCSI_MODE_SEN6	equ	01Ah	;Mode Sense 6-byte (Device Specific)
SCSI_MODE_SEN10	equ	05Ah	;Mode Sense 10-byte (Device Specific)
SCSI_READ_BUFF	equ	03Ch	;Read Buffer (O)
SCSI_REQ_SENSE	equ	003h	;Request Sense (MANDATORY)
SCSI_SEND_DIAG	equ	01Dh	;Send Diagnostic (O)
SCSI_TST_U_RDY	equ	000h	;Test Unit Ready (MANDATORY)
SCSI_WRITE_BUFF equ	03Bh	;Write Buffer (O)

;****************************************************************************
;	   %%% Commands Unique to Direct Access Devices %%%
;****************************************************************************
SCSI_COMPARE	equ	039h	;Compare (O)
SCSI_FORMAT	equ	004h	;Format Unit (MANDATORY)
SCSI_LCK_UN_CAC equ	036h	;Lock Unlock Cache (O)
SCSI_PREFETCH	equ	034h	;Prefetch (O)
SCSI_MED_REMOVL equ	01Eh	;Prevent/Allow medium Removal (O)
SCSI_READ6	equ	008h	;Read 6-byte (MANDATORY)
SCSI_READ10	equ	028h	;Read 10-byte (MANDATORY)
SCSI_RD_CAPAC	equ	025h	;Read Capacity (MANDATORY)
SCSI_RD_DEFECT	equ	037h	;Read Defect Data (O)
SCSI_READ_LONG	equ	03Eh	;Read Long (O)
SCSI_REASS_BLK	equ	007h	:Reassign Blocks (O)
SCSI_RCV_DIAG	equ	01Ch	;Receive Diagnostic Results (O)
SCSI_RELEASE	equ	017h	;Release Unit (MANDATORY)
SCSI_REZERO	equ	001h	;Rezero Unit (O)
SCSI_SRCH_DAT_E equ	031h	;Search Data Equal (O)
SCSI_SRCH_DAT_H equ	030h	;Search Data High (O)
SCSI_SRCH_DAT_L equ	032h	;Search Data Low (O)
SCSI_SEEK6	equ	00Bh	;Seek 6-Byte (O)
SCSI_SEEK10	equ	02Bh	;Seek 10-Byte (O)
SCSI_SEND_DIAG	equ	01Dh	;Send Diagnostics (MANDATORY)
SCSI_SET_LIMIT	equ	033h	;Set Limits (O)
SCSI_START_STP	equ	01Bh	;Start/Stop Unit (O)
SCSI_SYNC_CACHE equ	035h	;Synchronize Cache (O)
SCSI_VERIFY	equ	02Fh	;Verify (O)
SCSI_WRITE6	equ	00Ah	;Write 6-Byte (MANDATORY)
SCSI_WRITE10	equ	02Ah	;Write 10-Byte (MANDATORY)
SCSI_WRT_VERIFY equ	02Eh	;Write and Verify (O)
SCSI_WRITE_LONG equ	03Fh	;Write Long (O)
SCSI_WRITE_SAME equ	041h	;Write Same (O)

;****************************************************************************
;	 %%% Commands Unique to Sequential Access Devices %%%
;****************************************************************************
SCSI_ERASE	equ	019h	;Erase (MANDATORY)
SCSI_LOAD_UN	equ	01Bh	;Load/Unload (O)
SCSI_LOCATE	equ	02Bh	;Locate (O)
SCSI_RD_BLK_LIM equ	005h	;Read Block Limits (MANDATORY)
SCSI_READ_POS	equ	034h	;Read Position (O)
SCSI_READ_REV	equ	00Fh	;Read Reverse (O)
SCSI_REC_BF_DAT equ	014h	;Recover Buffer Data (O)
SCSI_RESERVE	equ	016h	;Reserve Unit (MANDATORY)
SCSI_REWIND	equ	001h	;Rewind (MANDATORY)
SCSI_SPACE	equ	011h	;Space (MANDATORY)
SCSI_VERIFY_T	equ	013h	;Verify (Tape) (O)
SCSI_WRT_FILE	equ	010h	;Write Filemarks (MANDATORY)

;****************************************************************************
;	      %%% Commands Unique to Printer Devices %%%
;****************************************************************************
SCSI_PRINT	equ	00Ah	;Print (MANDATORY)
SCSI_SLEW_PNT	equ	00Bh	;Slew and Print (O)
SCSI_STOP_PNT	equ	01Bh	;Stop Print (O)
SCSI_SYNC_BUFF	equ	010h	;Synchronize Buffer (O)

;****************************************************************************
;	     %%% Commands Unique to Processor Devices %%%
;****************************************************************************
SCSI_RECEIVE	equ	008h	;Receive (O)
SCSI_SEND	equ	00Ah	;Send (O)

;****************************************************************************
;	    %%% Commands Unique to Write-Once Devices %%%
;****************************************************************************
SCSI_MEDIUM_SCN equ	038h	;Medium Scan (O)
SCSI_SRCHDATE10 equ	031h	;Search Data Equal 10-Byte (O)
SCSI_SRCHDATE12 equ	0B1h	;Search Data Equal 12-Byte (O)
SCSI_SRCHDATH10 equ	030h	;Search Data High 10-Byte (O)
SCSI_SRCHDATH12 equ	0B0h	;Search Data High 12-Byte (O)
SCSI_SRCHDATL10 equ	032h	;Search Data Low 10-Byte (O)
SCSI_SRCHDATL12 equ	0B2h	;Search Data Low 12-Byte (O)
SCSI_SET_LIM_10 equ	033h	;Set Limits 10-Byte (O)
SCSI_SET_LIM_12	equ	0B3h	;Set Limits 10-Byte (O)
SCSI_VERIFY10	equ	02Fh	;Verify 10-Byte (O)
SCSI_VERIFY12	equ	0AFh	;Verify 12-Byte (O)
SCSI_WRITE12	equ	0AAh	;Write 12-Byte (O)
SCSI_WRT_VER10	equ	02Eh	;Write and Verify 10-Byte (O)
SCSI_WRT_VER12	equ	0AEh	;Write and Verify 12-Byte (O)

;****************************************************************************
;	      %%% Commands Unique to CD-ROM Devices %%%
;****************************************************************************
SCSI_PLAYAUD_10 equ	045h	;Play Audio 10-Byte (O)
SCSI_PLAYAUD_12 equ	0A5h	;Play Audio 12-Byte 12-Byte (O)
SCSI_PLAYAUDMSF equ	047h	;Play Audio MSF (O)
SCSI_PLAYA_TKIN equ	048h	;Play Audio Track/Index (O)
SCSI_PLYTKREL10 equ	049h	;Play Track Relative 10-Byte (O)
SCSI_PLYTKREL12 equ	0A9h	;Play Track Relative 12-Byte (O)
SCSI_READCDCAP	equ	025h	;Read CD-ROM Capacity (MANDATORY)
SCSI_READHEADER equ	044h	;Read Header (O)
SCSI_SUBCHANNEL equ	042h	;Read Subchannel (O)
SCSI_READ_TOC	equ	043h	;Read TOC (O)

;****************************************************************************
;	      %%% Commands Unique to Scanner Devices %%%
;****************************************************************************
SCSI_GETDBSTAT	equ	034h	;Get Data Buffer Status (O)
SCSI_GETWINDOW	equ	025h	;Get Window (O)
SCSI_OBJECTPOS	equ	031h	;Object Postion (O)
SCSI_SCAN	equ	01Bh	;Scan (O)
SCSI_SETWINDOW	equ	024h	;Set Window (MANDATORY)

;****************************************************************************
;	  %%% Commands Unique to Optical Memory Devices %%%
;****************************************************************************
SCSI_UpdateBlk	equ	3Dh	;Update Block (O)

;****************************************************************************
;	  %%% Commands Unique to Medium Changer Devices %%%
;****************************************************************************
SCSI_EXCHMEDIUM equ	0A6h	;Exchange Medium (O)
SCSI_INITELSTAT equ	007h	;Initialize Element Status (O)
SCSI_POSTOELEM	equ	02Bh	;Position to Element (O)
SCSI_REQ_VE_ADD equ	0B5h	;Request Volume Element Address (O)
SCSI_SENDVOLTAG equ	0B6h	;Send Volume Tag (O)

;****************************************************************************
;	   %%% Commands Unique to Communication Devices %%%
;****************************************************************************
SCSI_GET_MSG_6	equ	008h	;Get Message 6-Byte (MANDATORY)
SCSI_GET_MSG_10 equ	028h	;Get Message 10-Byte (O)
SCSI_GET_MSG_12 equ	0A8h	;Get Message 12-Byte (O)
SCSI_SND_MSG_6	equ	00Ah	;Send Message 6-Byte (MANDATORY)
SCSI_SND_MSG_10 equ	02Ah	;Send Message 10-Byte (O)
SCSI_SND_MSG_12 equ	0AAh	;Send Message 12-Byte (O)

;/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\
;
;		 %%% END OF SCSI COMMAND OPCODES %%%
;
;/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\

;****************************************************************************
;		  %%% Request Sense Data Format %%%
;****************************************************************************
SENSE_DATA_FMT		struc
	ErrorCode	db	?	;Error Code (70H or 71H)
	SegmentNum	db	?	;Number of current segment descriptor
	SenseKey	db	?	;Sense Key(See bit definitions too)
	InfoByte0 	db	?	;Information MSB
	InfoByte1 	db	?	;Information MID
	InfoByte2 	db	?	;Information MID
	InfoByte3 	db	?	;Information LSB
	AddSenLen	db	?	;Additional Sense Length
	ComSpecInf0	db	?	;Command Specific Information MSB
	ComSpecInf1	db	?	;Command Specific Information MID
	ComSpecInf2	db	?	;Command Specific Information MID
	ComSpecInf3	db	?	;Command Specific Information LSB
	AddSenseCode	db	?	;Additional Sense Code
	AddSenQual	db	?	;Additional Sense Code Qualifier
	FieldRepUCode	db	?	;Field Replaceable Unit Code
	SenKeySpec15	db	?	;Sense Key Specific 15th byte
	SenKeySpec16	db	?	;Sense Key Specific 16th byte
	SenKeySpec17	db	?	;Sense Key Specific 17th byte
	AddSenseBytes	db	?	;Additional Sense Bytes
SENSE_DATA_FMT		ends

;****************************************************************************
;		   %%% REQUEST SENSE ERROR CODE %%%
;****************************************************************************
SERROR_CURRENT	equ	070H	;Current Errors
SERROR_DEFERED	equ	071H	;Deferred Errors

;****************************************************************************
;		%%% REQUEST SENSE BIT DEFINITIONS %%%
;****************************************************************************
SENSE_VALID	equ	080H	;Byte 0 Bit 7
SENSE_FILEMRK	equ	080H	;Byte 2 Bit 7
SENSE_EOM	equ	040H	;Byte 2 Bit 6
SENSE_ILI	equ	020H	;Byte 2 Bit 5

;****************************************************************************
;	     %%% REQUEST SENSE SENSE KEY DEFINITIONS %%%
;****************************************************************************
KEY_NOSENSE	equ	00H	;No Sense
KEY_RECERROR	equ	01H	;Recovered Error
KEY_NOTREADY	equ	02H	;Not Ready
KEY_MEDIUMERR	equ	03H	;Medium Error
KEY_HARDERROR	equ	04H	;Hardware Error
KEY_ILLGLREQ	equ	05H	;Illegal Request
KEY_UNITATT	equ	06H	;Unit Attention
KEY_DATAPROT	equ	07H	;Data Protect
KEY_BLANKCHK	equ	08H	;Blank Check
KEY_VENDSPEC	equ	09H	;Vendor Specific
KEY_COPYABORT	equ	0AH	;Copy Abort
KEY_EQUAL	equ	0CH	;Equal (Search)
KEY_VOLOVRFLW	equ	0DH	;Volume Overflow
KEY_MISCOMP	equ	0EH	;Miscompare (Search)
KEY_RESERVED	equ	0FH	;Reserved

;****************************************************************************
;		     %%% Inquiry Data Format %%%
;****************************************************************************
INQRY_DATA_FMT		struc
	PerQualTyp	db	?	;Peripheral Qualifier and Device Type
			db	?	;Reserved except for bit 7 (RMB)
	Versions	db	?	;ISO, ECMA and ANSI versions
			db	?	;
	AddLengh	db	?	;Additional Length
	Reserved1	db	?	;Reserved
	Reserved2	db	?	;Reserved
	Flags		db	?	;RelAdr, WBus32, WBus16, Sync, ....
	VendorId	db	8 dup (?) ;Command Specific Information LSB
	ProdId		db     16 dup (?) ;Additional Sense Code
	ProdRev 	db	4 dup (?) ;Additional Sense Code Qualifier
INQRY_DATA_FMT		ends

;****************************************************************************
;	      %%% PERIPHERAL DEVICE TYPE DEFINITIONS %%%
;****************************************************************************
DTYPE_DASD	equ	00H	;Disk Device
DTYPE_SEQD	equ	01H	;Tape Device
DTYPE_PRNT	equ	02H	;Printer
DTYPE_PROC	equ	03H	;Processor
DTYPE_WORM	equ	04H	;Write-once read-multiple
DTYPE_CROM	equ	05H	;CD-ROM device
DTYPE_CDROM	equ	05H	;CD-ROM device
DTYPE_SCAN	equ	06H	;Scanner device
DTYPE_OPTI	equ	07H	;Optical memory device
DTYPE_JUKE	equ	08H	;Medium Changer device
DTYPE_COMM	equ	09H	;Communications device
DTYPE_RESL	equ	0AH	;Reserved (low)
DTYPE_RESH	equ	1EH	;Reserved (high)
DTYPE_UNKNOWN	equ	1FH	;Unknown or no device type

;****************************************************************************
;	      %%% ANSI APPROVED VERSION DEFINITIONS %%%
;****************************************************************************
ANSI_MAYBE	equ	00H	;Device may or may not be ANSI approved stand
ANSI_SCSI1	equ	01H	;Device complies to ANSI X3.131-1986 (SCSI-1)
ANSI_SCSI2	equ	02H	;Device complies to SCSI-2
ANSI_RESLO	equ	03H	;Reserved (low)
ANSI_RESHI	equ	07H	;Reserved (high)

;****************************************************************************
;	     %%% 6-Byte Data Transfer Command Format %%%
;****************************************************************************
DATA_XFER_6		struc
	_OpCode 	db	?	;Opcode of SCSI Command
	_LUNumber	db	?	;Logical Unit Number & LBA MSB
	_LBAMiddl	db	?	;Logical Block Address Middle Byte
	_LBALeast	db	?	;Logical Block Address Least Byte
	_Length 	db	?	;Transfer Length
	_Control	db	?	;Control Byte
DATA_XFER_6		ends

;****************************************************************************
;	     %%% 10-Byte Data Transfer Command Format %%%
;****************************************************************************
_LBA_3rd	equ	_OpCode+3     ;Logical Block Address 3rd Byte
_LBA_2nd	equ	_OpCode+4     ;Logical Block Address 2nd Byte
_LBA_1st	equ	_OpCode+5     ;Logical Block Address 1st Byte
_LBA_0th	equ	_OpCode+6     ;Logical Block Address 0th Byte
_Length_Hi	equ	_OpCode+7     ;Transfer Length High
_Length_Lo	equ	_OpCode+8     ;Transfer Length Low
_Control10	equ	_OpCode+9     ;Control Byte


