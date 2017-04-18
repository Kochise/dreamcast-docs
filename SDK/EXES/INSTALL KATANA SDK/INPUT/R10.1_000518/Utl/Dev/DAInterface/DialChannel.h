/*=====================[ DIAL API Interface Code ]=======================*
 |
 | DIAL Library - Copyright Cross Products Ltd. 1999
 |
 *------------------------------[ VERSION ]------------------------------*
 |
 | $Workfile: DialChannel.h $
 | $Author: Jmullins $
 | $Revision: 6 $
 | $Modtime: 22/07/99 13:50 $
 | $Date: 27/07/99 10:31 $
 | $Archive: /library/DIAL/DialChannel.h $
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

#ifndef DIALCHANNEL_H_
#define DIALCHANNEL_H_

#include "dial.h"
#include "genchannel.h"

class CDialChannelEx : public CGenChannel
{
public:
		virtual DIAL_EC Reserve( DIAL_ID, CHANTYPE, DWORD = DIAL_DEFAULT_TIMEOUT ) = 0;
		virtual DIAL_EC Release( DIAL_ID, CHANTYPE ) = 0;
		virtual DIAL_EC Validate( DIAL_ID, CHANTYPE ) = 0;
		virtual DIAL_EC DataReady( DIAL_ID, CHANTYPE, BOOL&, DWORD& ) = 0;
		virtual DIAL_EC Read( DIAL_ID, CHANTYPE, DWORD, DWORD&, void*, BOOL = FALSE, DWORD = DIAL_DEFAULT_TIMEOUT ) = 0;
		virtual DIAL_EC Write( DIAL_ID, CHANTYPE, DWORD, DWORD&, const void*, BOOL = FALSE, DWORD = DIAL_DEFAULT_TIMEOUT ) = 0;
};

//	This represents a read-only channel of a specific type
class CTypedChannelROEx : public CGenChannel
{
public:
		virtual DIAL_EC Reserve( DIAL_ID, DWORD = DIAL_DEFAULT_TIMEOUT ) = 0;
		virtual DIAL_EC Release( DIAL_ID ) = 0;
		virtual DIAL_EC Validate( DIAL_ID ) = 0;
		virtual DIAL_EC DataReady( DIAL_ID, BOOL&, DWORD& ) = 0;
		virtual DIAL_EC Read( DIAL_ID, DWORD, DWORD&, void*, BOOL = FALSE, DWORD = DIAL_DEFAULT_TIMEOUT ) = 0;
};

//	This represents a read-write channel of a specific type

class CTypedChannelEx : public CTypedChannelROEx
{
public:
		virtual DIAL_EC Write( DIAL_ID, DWORD, DWORD&, const void*, BOOL = FALSE, DWORD = DIAL_DEFAULT_TIMEOUT ) = 0;
};


#endif
