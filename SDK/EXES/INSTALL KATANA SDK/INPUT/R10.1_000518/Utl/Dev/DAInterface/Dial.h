/*=====================[ DIAL API Interface Code ]=======================*
 |
 | DIAL Library - Copyright Cross Products Ltd. 1999
 |
 *------------------------------[ VERSION ]------------------------------*
 |
 | $Workfile: dial.h $
 | $Author: Jmullins $
 | $Revision: 18 $
 | $Modtime: 17/04/00 12:54 $
 | $Date: 17/04/00 12:55 $
 | $Archive: /library/DIAL/dial.h $
 |
 *-------------------------------[ NOTES ]-------------------------------*
 |
 |  Description: contains API interface code prototypes for the
 |               Debug Interface Access Layer (DIAL).
 |
 |
 *----------------------------[ DEFINITIONS ]----------------------------*
 |
 *----------------------------[ DECLARATIONS ]---------------------------*
 |
 *=======================================================================*/

#ifndef DIAL_H_
#define DIAL_H_

#include "error.h"

typedef DWORD DIAL_EC;
typedef DWORD DIAL_ID;

const DIAL_EC_NOERROR = 0;
const DIAL_ID_UNDEF = 0xffffffff;

const DWORD DIAL_DEFAULT_TIMEOUT	=	5000;

const DWORD DIAL_BUILD_VERSION		=	0x10004;		// Verison number when library built


class CDialDAEx;
class CDialConsoleEx;
class CTypedChannelEx;
class CTypedChannelROEx;
class CDialChannelEx;
class CDialMirageEx;

struct DIALDEVICE
{
	enum DEVTYPE
	{
		DEVTYPE_UNKNOWN,
		DEVTYPE_CARTDEV_DA,
		DEVTYPE_KATANA_DA,
		DEVTYPE_MIRAGE_DSK,
		DEVTYPE_GDM,

		// this *must* be last
		DEVTYPE_UNDEF = 0xFF
	};

	DIAL_ID		deviceID;					//	Device identifier
	DEVTYPE		deviceType;					//	Device type ( see above )
	char		deviceDesc[ 80 ];

	DIALDEVICE() : deviceID( DIAL_ID_UNDEF ), deviceType( DEVTYPE_UNDEF ) {}
};


class CDial
{
public:
		enum DEBUGMODE
		{
			DEBUGMODE_OS,
			DEBUGMODE_CPU
		};
		CDialDAEx&			DA;
		CDialConsoleEx&		Console;

		// Use these channel wrapper classes in preference to using CChannel directly
		CTypedChannelEx&	VSerial;
		CTypedChannelEx&	DebugOS;
		CTypedChannelEx&	FServer;
		CTypedChannelEx&	Sound;
		CTypedChannelROEx&	TraceProfile;
		// Direct access to the CChannel class. 
		// Needs specification of channel identifier CHANTYPE enumerated parameter defined in channel.h
		// N.B. CHANTYPE_TRACEPROFILE is *Read Only*, as specified in  CTraceProfile API.
		CDialChannelEx&		Channel;

		CDial( CDialDAEx& da, 
				CDialConsoleEx& console, 
				CTypedChannelEx& vserial,
				CTypedChannelEx& debugOS,
				CTypedChannelEx& fileServer,
				CTypedChannelEx& sound,
				CTypedChannelROEx& traceProfile,
				CDialChannelEx& channel
				) : DA( da ), Console( console ), VSerial( vserial ), DebugOS( debugOS ), FServer( fileServer ),
					Sound( sound ), TraceProfile( traceProfile ), Channel( channel )
		{
		}


		virtual BOOL		GetVersion( DWORD&, DWORD& ) const = 0;

		virtual void		SetTimeOut( DWORD ) = 0;
		virtual DWORD		GetTimeOut() const = 0;

		virtual DIAL_EC		FindNextDevice( DIAL_ID&, DIALDEVICE::DEVTYPE ) = 0;

		virtual DIAL_EC		GetDeviceDetails( DIAL_ID, DIALDEVICE& ) = 0;

		virtual DIAL_EC		ValidateDevice( DIAL_ID, DIALDEVICE::DEVTYPE = DIALDEVICE::DEVTYPE_UNDEF ) = 0;

		virtual	const char*	GetErrorText( DIAL_EC ) = 0;

		virtual	DIAL_EC		Connect( DIAL_ID ) = 0;

		virtual void		Disconnect( DIAL_ID ) = 0;
};

#ifdef DIAL_DEF_
extern "C" __declspec( dllexport ) CDial * InitializeDial();
extern "C" __declspec( dllexport ) DIAL_EC GetDialDebugMode( CDial *, DIAL_ID, CDial::DEBUGMODE& );
extern "C" __declspec( dllexport ) DIAL_EC SetDialDebugMode( CDial *, DIAL_ID, CDial::DEBUGMODE );
#else
extern "C" __declspec( dllimport ) CDial * InitializeDial();
extern "C" __declspec( dllimport ) DIAL_EC GetDialDebugMode( CDial *, DIAL_ID, CDial::DEBUGMODE& );
extern "C" __declspec( dllimport ) DIAL_EC SetDialDebugMode( CDial *, DIAL_ID, CDial::DEBUGMODE );
typedef CDialDAEx		CDA;
typedef CDialConsoleEx	CConsole;
typedef CDialChannelEx	CChannel;
typedef CDialMirageEx	CMirage;
#endif



#endif
