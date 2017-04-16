/////////////////////////////////////////////////////////////////////////////
// Logger.h : logging definitions
//
// This is a part of the Webster HTTP Server application
// for Microsoft Systems Journal
//

#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <fstream.h>	// ofstream

// Common Log Format record definition
typedef struct
{
	CString		client ;
	CString		inetd ;
	CString		username ;
	CTime		datetime ;
	CString		request ;
	long		status ;
	long		bytes ;
} COMLOGREC, *PCOMLOGREC ;

#endif // __LOGGER_H__
