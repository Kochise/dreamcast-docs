/*=======================[ SALSA API Error Codes ]=======================*
 |
 | SALSA Library - Copyright Cross Products Ltd. 1998
 |
 *------------------------------[ VERSION ]------------------------------*
 |
 | $Workfile: error.h $
 | $Author: Jmullins $
 | $Revision: 33 $
 | $Modtime: 19/07/99 15:30 $
 | $Date: 19/07/99 15:33 $
 | $Archive: /library/NAIL/USERSALSA/error.h $
 |
 *-------------------------------[ NOTES ]-------------------------------*
 |
 |  Description: contains API error code definitions for the
 |               Sega Advanced Library for SCSI Access (SALSA).
 |
 |  LIB: salsa.lib
 |
 *----------------------------[ DEFINITIONS ]----------------------------*
 |
 *----------------------------[ DECLARATIONS ]---------------------------*
 |
 *=======================================================================*/

#ifndef error_h
#define error_h

typedef DWORD SALSA_EC;	// Error Codes are made MSW category and LSW error

#define SALSA_MakeEC(wCategory, wError)   (SALSA_EC)((wCategory << 16) | (wError & 0xFFFF))
#define  SALSA_EC_NOERROR ((SALSA_EC)(0))


/* SALSA_EC the error code type is made up of 2 parts
 * the SALSA_EC is a 32 bit value
 * the higher 16 bits is a group code indicating module
 * The lower 16 bits is the actual error code.
 */

/*
 * Categories
 */
enum ERRCAT
{
	ERRCAT_NOERROR,		// The 'no error' category
	ERRCAT_SALSA,		// General SALSA errors
	ERRCAT_SALSADACON,	// Additional SALSA errors relating to DA and Console operations
	ERRCAT_ASPI,		// Errors originating in the ASPI layer
	ERRCAT_DA,			// Errors from DA specific commands
	ERRCAT_CON,			// Errors from Console specific commands
	ERRCAT_CDM,			// CD-emulator errors
	ERRCAT_WINSOCK,		// Windows sockets errors
	ERRCAT_TFTP,		// Errors from TFTP
	ERRCAT_UNKNOWN		// Errors of unknown origin
};

/*
 * The ERRUNKNOWN category error codes
 */
enum ERRUNKNOWN
{
	ERRUNKNOWN_UNKNOWNERR = 1
};

/*
 * The SALSA category error codes
 */
enum ERRSALSA
{
	ERRSALSA_NOERROR,			// No error
	ERRSALSA_NOTINITED,			// Call made to uninitialised SALSA layer - SALSA_Inited was FALSE
	ERRSALSA_DEVICENOTMATCH,	// Failed to validate the device type
	ERRSALSA_DEVICENOTFOUND,	// Didn't find requested device
	ERRSALSA_CHANLNOTALLOCD,	// Logical channel (LUN) not allocated.
	ERRSALSA_NOCHNLAVAIL,		// No more channels (LUNs) available.
	ERRSALSA_MEMALLOCFAIL,		// Memory allocation failed...
	ERRSALSA_BADADAPTER,		// Failed to validate the Adapter
	ERRSALSA_BADDEVICEID,		// Failed to validate the Device SCSI ID

	ERRSALSA_TIMEOUT,			// Timed out on SALSA command

	ERRSALSA_FAILCREATESYNCOBJ,	// Failed to create the target device's synchronisation object (e.g. CSEMAPHORE)
	ERRSALSA_FAILCREATELOCKOBJ,	// Failed to create the target device's synchronisation control object (e.g. CSINGLELOCK)
	ERRSALSA_FAILLOCK,			// Timed out or bad attempt to lock a synchronisation object
	ERRSALSA_FAILUNLOCK,		// Failed attempting to unlock a synchronisation object
	ERRSALSA_BADVERSION,		// The user salsa version does not match the library version
	ERRSALSA_NOTIMPLEMENTED,
	ERRSALSA_DEVICEINUSE
};

enum ERRSALSADACON
{
	// This is an extension to the protocol defined codes for SALSA defined additions relating to DA and Console operations

	ERRSALSADACON_CMDPENDING		= 0x0100,	// Command is still pending completion
	ERRSALSADACON_CMDNOMATCH		= 0x0200,	// Returned command header did not match in command field
	ERRSALSADACON_SEQNOMATCH		= 0x0300,	// Returned command header did not match in sequence field
	ERRSALSADACON_FLSHOPENFAIL		= 0x0400,	// Failed to open flash image file
	ERRSALSADACON_FLSHSTATFAIL		= 0x0500,	// Failed to fstat flash image file
	ERRSALSADACON_FLSHSHORTREAD		= 0x0600,	// Short read from flash image file
	ERRSALSADACON_BADELEMENTSIZE	= 0x0700,	// Bad ELEMENTSIZE specified in Read/WriteMemory()
	ERRSALSADACON_NOCONPOWER		= 0x0800,	// tsf0	The Console is currently powered off
	ERRSALSADACON_RESETINGCON		= 0x0900,	// tsf1	The Console is currently being reset (Reset pin low).
	ERRSALSADACON_FAILLOADSTUB		= 0x0a00,	// SIGNAL_FAIL (default) stub failed to loaded.
	ERRSALSADACON_FAIL1KSTUB		= 0x0b00,	// tsf4	The 1K stub failed to loaded.
	ERRSALSADACON_FAILFULLSTUB		= 0x0c00,	// tsf5	The Full stub failed to loaded.
	ERRSALSADACON_FAILSTUBCORRUPT	= 0x0d00,	// tsf6 The full stub has been corrupted
	ERRSALSADACON_FAILNODEBUG		= 0x0e00	// (SIGNAL_NODEBUG) no debug support available
};

/*
 * The ASPI category error codes
 */
enum ERRASPI
{
	ERRASPI_NOERROR,			// No error
	ERRASPI_UNKNOWNERR,			// Unknown error
	ERRASPI_ABORTED,			// SS_ABORTED
	ERRASPI_ABORTFAIL,			// SS_ABORT_FAIL
	ERRASPI_PENDING,			// SS_PENDING
	ERRASPI_COMPLETEDERR,		// SS_ERR and RequestSense/ProcessCheckCondition() == SALSA_EC_NOERROR
	ERRASPI_INVALIDSCSICMD,		// SS_INVALID_CMD
	ERRASPI_INVALIDADAPTER,		// SS_INVALID_HA
	ERRASPI_NODEVICE,			// SS_NO_DEVICE
	ERRASPI_INVALIDSRB,			// SS_INVALID_SRB
	ERRASPI_FAILEDINIT,			// SS_FAILED_INIT
	ERRASPI_ISBUSY,				// SS_ASPI_IS_BUSY
	ERRASPI_BUFFTOBIG,			// SS_BUFFER_TO_BIG

	ERRASPI_NOASPIDRIVER,		// Call made to uninitialised ASPI layer - ASPI_Inited was FALSE
	ERRASPI_NOADAPTERS,			// ASPI_byNumAdapters == 0
	ERRASPI_CREATEVENTFAIL,		// Unable to create the ASPI completion event object
	ERRASPI_THREADTERMINATED,   // WAIT_ABANDONED on SendASPI32Command
	ERRASPI_TIMEOUT,			// WAIT_TIMEOUT on SendASPI32Command
	ERRASPI_MISSINGASPIFUNCTION,	// Failed to load an ASPI function from the DLL
	ERRASPI_SETTIMEOUTFAILED,	// Failed to set ASPI timeout value
	ERRASPI_HANDLETIMEOUT,		// A handle timeed out before ASPI - this is a BAD THING - dangling resources!
	//OLDMANAGER is overridden in Win32 by BUFFER_ALIGN
	//ERRASPI_OLDMANAGER,			// ASPI manager does not support windows
	ERRASPI_BUFFER_ALIGN,		// Buffer not aligned
	ERRASPI_ILLEGAL_MODE,		// Unsupported windows mode
	ERRASPI_NO_ASPI,			// No aspi managers resident
	ERRASPI_MISMATCHED_COMPONENTS,	//ASPI versions do not match
	ERRASPI_NO_ADAPTERS,		//No host adapters present
	ERRASPI_INSUFFICIENT_RESOURCES	//Cannot allocate enough resource to initialise
};



enum DAERRCAT
{
	DAERRCAT_OK,
	DAERRCAT_DA,
	DAERRCAT_CON
};

enum DAERROK
{
	DAERROK_AOKAOK,				// Command completed without an error.
	DAERROK_AOKRUN,				// Command in progress (Asynchronous commands).
	DAERROK_AOKERR				// Command error (Asynchronous commands).
};

enum DAERRDA
{
	DAERRDA_DAAOK,				// Command completed without an error.
	DAERRDA_DATMO,				// DA Command Time-out during action.
	DAERRDA_DAERA,				// DA Command Error during flash erase.
	DAERRDA_DAPRG,				// DA Command Error during flash program.
	DAERRDA_DAFIC,				// DA Command Flash image corrupt.
	DAERRDA_DAERR				// DA Command general error
};

enum DAERRCON
{
	DAERRCON_CONAOK,			// Console command completed without an error.
	DAERRCON_CONERR,			// Console command fatal error.
	DAERRCON_CONBAD,			// Console command unknown
	DAERRCON_CONPRM,			// Console command parameter error.
	DAERRCON_CONADR,			// Console command bad address.
	DAERRCON_CONCNT,			// Console command bad count.
	DAERRCON_CONCBF,			// Console command channel buffer full.
	DAERRCON_CONCBE,			// Console command channel buffer empty.

	DAERRCON_CONBSY,			// Console command not processed as BUSY
	DAERRCON_CONCNA				// Console command not available (no debug stub)
};


enum ERRCDM
{
	ERRCDM_NOCDMCIRCUITRY,				// dasf0	The CD-M unit circuitry is not fitted.
	ERRCDM_NOCDMMECHANISM,				// dasf1	The CD-M unit mechanism is not fitted.
	ERRCDM_FLASH,						// failed to upgrade flash file
	ERRCDM_BAD_FLASH_FILE,				// the flash file may not be a valid flash file
	ERRCDM_CACHE_FLUSH					// failed to flush NT's file cache

};

enum ERRWINSOCK
{
	ERRWINSOCK_NOERROR,
	ERRWINSOCK_INVALIDVERSION,			//	Could not find a valid version of WinSock
	ERRWINSOCK_CANTCONNECT				//	Could not connect to the specified device

};

enum ERRTFTP
{
	ERRTFTP_NOERROR,
	ERRTFTP_FILENOTFOUND				//	Could not find the file
};

#endif /* error_h */
