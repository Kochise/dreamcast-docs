/*  Metrowerks Standard Library  */

/*  $Date: 1999/03/24 17:58:02 $ 
 *  $Revision: 1.7 $ 
 *  $NoKeywords: $ 
 *
 *		Copyright © 1995-1999 Metrowerks, Inc.
 *		All rights reserved.
 */

/************************************************************************/
/*	Project...:	Standard C++ Library									*/
/*	Name......:	MSLstring.cpp											*/
/*	Purpose...:	exception string handling								*/
/************************************************************************/

#include <MSLstring.h>
#include <string>
#include <cstring>

_STD::_MSLstring::_MSLstring(const char* value)
{
	char* data = new char [strlen(value)+1];
	strcpy(data, value);
	data_ = data;
}

_STD::_MSLstring::_MSLstring(const string& value)
{
	char* data = new char [value.size()+1];
	strcpy(data, value.c_str());
	data_ = data;
}

// hh 990120 changed name of MSIPL flags
// hh 990314 Added const char* constructor to support nonstandard const char* constructors
//           on all of the standard exceptions.
