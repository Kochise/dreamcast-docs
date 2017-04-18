/*====================[ SALSA Channel API Prototypes ]===================*
 |
 | SALSA Library - Copyright Cross Products Ltd. 1998
 |
 *------------------------------[ VERSION ]------------------------------*
 |
 | $Workfile: GenChannel.h $
 | $Author: Jmullins $
 | $Revision: 2 $
 | $Modtime: 16/07/99 10:11 $
 | $Date: 16/07/99 10:24 $
 | $Archive: /library/SALSA/GenChannel.h $
 |
 *-------------------------------[ NOTES ]-------------------------------*
 |
 |  Description: contains Generic Channel API abstract base class 
 |	prototypes for Sega Advanced Library for SCSI Access (SALSA).
 |
 |  LIB: salsa.lib
 |
 |************************************************************************
 |These enum and structure definitions *MUST* match the firmware *exactly*
 |************************************************************************
 |
 *----------------------------[ DEFINITIONS ]----------------------------*
 |
 *----------------------------[ DECLARATIONS ]---------------------------*
 |
 *=======================================================================*/

#ifndef genchannel_h
#define genchannel_h

#define SALSA_MAX_CHANNELS		6			// SALSA max. Virtual Channels on DA device


// *********************************************************************
// Define the command protocol structures, ensuring correct byte packing
// *********************************************************************
#if defined(__MWERKS__)
#pragma pack(push, 1)
#else
#pragma pack(push, genchannel, 1)
#endif


struct BUFFPARAMS
{
	BYTE	byChannel;
	BYTE	byZPad;
	DWORD	dwLength;

	BUFFPARAMS(VOID)
	{
		Initialise();
	}

	VOID Initialise(VOID)
	{
		memset((VOID*)this, 0, sizeof(BUFFPARAMS));
	}

	int Size() { return(6); }

};


#if defined(__MWERKS__)
#pragma pack(pop)
#else
#pragma pack(pop, genchannel)
#endif
// ********************************************************************************
// Finished defining the command protocol structures, ensuring correct byte packing
// ********************************************************************************


class CGenChannel
{
	public:
		enum CHANTYPE
		{
			 CHANTYPE_DEBUGOS,
			 CHANTYPE_FILESERVER,
			 CHANTYPE_SOUNDTOOL,
			 CHANTYPE_VSERIAL,
			 CHANTYPE_TRACEPROFILE,
			 CHANTYPE_UNUSED
		};

		enum CHANSTATUS
		{
			CHANSTATUS_HALFFULL = 0x01
		};

};


#endif /* #ifndef genchannel_h */
