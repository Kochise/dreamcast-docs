/*=====================[ DIAL API Interface Code ]=======================*
 |
 | DIAL Library - Copyright Cross Products Ltd. 1999
 |
 *------------------------------[ VERSION ]------------------------------*
 |
 | $Workfile: DialConsole.h $
 | $Author: Jmullins $
 | $Revision: 4 $
 | $Modtime: 18/08/99 10:29 $
 | $Date: 18/08/99 10:31 $
 | $Archive: /library/DIAL/DialConsole.h $
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

#ifndef DIALCONSOLE_H_
#define DIALCONSOLE_H_

#include "dial.h"
#include "genconsole.h"


typedef CSalsaConsoleStatus		CDialConsoleStatus;
typedef SSALSARegsSH4EVA		SDialRegsSH4EVA;
typedef SSALSARegsSH4EVA_FPU	SDialRegsSH4EVA_FPU;
typedef SSALSARegsSH4EVA_MMU	SDialRegsSH4EVA_MMU;
typedef SSALSAUBCRegsSH4EVA		SDialUBCRegsSH4EVA;
typedef SSALSAHBCRegsSH4EVA		SDialHBCRegsSH4EVA;

class CDialConsole : public CGenConsole
{
public:
	virtual DIAL_EC Inquiry( DIAL_ID, INQUIRY& ) = 0;
	virtual DIAL_EC ProcessInquiryError( const INQUIRY&, BOOL = TRUE, BOOL = FALSE ) = 0;
	virtual DIAL_EC Execute( DIAL_ID, DWORD ) = 0;
	virtual DIAL_EC Suspend( DIAL_ID ) = 0;
	virtual DIAL_EC Resume( DIAL_ID ) = 0;
	virtual DIAL_EC ReadMemory( DIAL_ID, DWORD, ELEMENTSIZE, DWORD, void* ) = 0;
	virtual DIAL_EC WriteMemory( DIAL_ID, DWORD, ELEMENTSIZE, DWORD, const void* ) = 0;
	virtual DIAL_EC ReadContext( DIAL_ID, CONTEXTMODE, WORD, void* ) = 0;
	virtual DIAL_EC WriteContext( DIAL_ID, CONTEXTMODE, WORD, const void* ) = 0;
	virtual DIAL_EC ReadConfig( DIAL_ID, READCONFIG& ) = 0;
	virtual DIAL_EC ResetNoDebug( DIAL_ID ) = 0;
	virtual DIAL_EC ResetAndDebug( DIAL_ID ) = 0;
	virtual DIAL_EC MakeSafe( DIAL_ID ) = 0;
	virtual DIAL_EC GetValidConsoleStatus( DIAL_ID, CDialConsoleStatus *& ) = 0;
};

#ifndef CPL_INTERNAL
class CDialConsoleEx : public CDialConsole {};
#endif

#endif
