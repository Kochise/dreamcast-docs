/***********************************************************************
**      M S T V . H                                                    *
**                                                                     *
************************************************************************
** Copyright (C) 1996 by Microsoft Corporation                         *
**                 All Rights Reserved                                 *
************************************************************************/
/*

    MSTV.H

    Class definitions for CommMSTV SDK.

This is a part of the Microsoft TV SDK library.
See the TODO.hlp file for detailed information regarding the
Microsoft TV SDK product.

*/

#ifndef _MSTV_H_
#define _MSTV_H_


// Disable export declaration for third party compilation
#ifdef DLLEXPORT
#undef DLLEXPORT   // as nothing
#endif
#ifdef BUILDCOMMMSTV
#define COMMMSTVEXPORT __declspec ( dllexport )
#else
#define COMMMSTVEXPORT __declspec ( dllimport )
#endif

// Defines for Database in-memory structs
#define MAX_CALLLETTERS	10
#define MAX_TITLE		256
#define MAX_DESCRIPTION	1024
#define	MAX_LOGOMONIKER	1024

typedef struct tagCHANNEL_INFO
{
	LONG	lChannelID;
	LONG	lTuningSpace;
	LONG	lChannelNumber;
	LONG	lNetworkID;
	LONG	lRatingID;
	LONG	lDisplayMask;
	LONG	lPaymentAddress;
	LONG	lPaymentToken;
	LONG	lLength;
	DATE	StartTime;
	DATE	EndTime;
	DATE	LastUpdate;
	TCHAR	szCallLetters[MAX_CALLLETTERS];
	TCHAR	szDescription[MAX_DESCRIPTION];
	TCHAR	szNetworkName[MAX_CALLLETTERS];
	TCHAR	szNetworkLogoMoniker[MAX_LOGOMONIKER];
	BOOL	fTunable;
} CHANNEL_INFO;

#define CONTINUOUS_EPISODE	0

// lRepetition below is set to one of these values if Episode is a representation
// of a reminder
#define REMIND_NONE 0
#define REMIND_ONCE 1
#define REMIND_DAILY 2
#define REMIND_WEEKLY 3
#define REMIND_WEEKDAYS 4
#define REMIND_MAX 4

#define TUNING_DEFAULT	0


#define VIRTUAL_TUNINGSPACE(a) (a < 0 ? TRUE : FALSE )

typedef struct tagTUNING_INFO
{
	LONG	lTuningSpace;
	LONG	lChannelNumber;
	LONG	lVideoStream;
	LONG	lAudioStream;
	BSTR    bsIPStream;	// xxx.xxx.xxx.xxx
	TCHAR	szCallLetters[MAX_CALLLETTERS];
} TUNING_INFO;



// General error domains

#define	ERRDOM_DB			0x010000
#define ERRDOM_FILE			0x020000
#define ERRDOM_MEMORY		0x040000
#define ERRDOM_TIMING		0x080000	// issue may go away if we just retry a few seconds later
#define ERRDOM_STATE		0x0F0000  
#define ERRDOM_INSTALL		0x100000	// something missing from the install
	
#define ERRDOM_OTHER        0xFF0000	// miscellaneous


// General error codes

#define ERR_SUCCEEDED				0x00000000

// database errors
#define ERR_NULL_CHANNEL_LIST		(ERRDOM_DB | 0x0001)		// chanlist null
#define ERR_EPISODE_RS_FAILED		(ERRDOM_DB | 0x0002)		// openRecordSet for Episode failed

// file errors


// memory errors


// timing errors


// state errors
#define ERR_NULL_TVXDOC				(ERRDOM_STATE | 0x0001)	// CTvxDoc not initialized yet
#define ERR_IN_MODAL_STATE			(ERRDOM_STATE | 0x0002)	// Modal dlg is up


// installation errors
#define ERR_FILE_MSVIDEO_MISSING	(ERRDOM_INSTALL | 0x0001)	// msvideo.htm is missing
#define ERR_FILE_NODEVICE_MISSING	(ERRDOM_INSTALL | 0x0002)	// nodevice.htm is missing
#define ERR_FILE_MSGUIDE_MISSING    (ERRDOM_INSTALL | 0x0003) // msguide.htm is missing


// misc
#define ERR_CANT_NAVIGATE			(ERRDOM_OTHER | 0x0001)	// IWebBrowser::Navigate() failed
#define ERR_CHANNEL_DNE				(ERRDOM_OTHER | 0x0002)	// specified channel does not exists

#endif // _MSTV_H_


