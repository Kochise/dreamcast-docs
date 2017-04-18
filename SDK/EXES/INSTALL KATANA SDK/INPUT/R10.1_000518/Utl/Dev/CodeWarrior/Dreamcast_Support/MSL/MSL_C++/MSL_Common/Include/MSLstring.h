/*  Metrowerks Standard Library  Version 4.0  1998 August 10  */

/*  $Date: 1999/03/24 17:54:49 $ 
 *  $Revision: 1.8 $ 
 *  $NoKeywords: $ 
 *
 *		Copyright © 1995-1999 Metrowerks, Inc.
 *		All rights reserved.
 */

#ifndef _MSLstring_h
#define _MSLstring_h

// _MSLstring is a special simple string class used by <stdexept>.  This
// class breaks a potentially cyclic relationship between <stdexcept> and
// <string>.  Without this class, <string> throws classes from <stdexcept>
// and <stdexcept> processes <string>.  By making <stdexcept> depend on
// _MSLstring instead of <string>, the cycle is broken.
// hh 971226

#include <mslconfig>
#include <RefCountedPtrArray.h>

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#ifndef _MSL_NO_CPP_NAMESPACE
	namespace std {
#endif

	template <class T> class allocator;
	template<class charT> struct char_traits;
	template <class charT, class traits, class Allocator> class basic_string;
	typedef basic_string<char, char_traits<char>, allocator<char> > string;

	class _MSLstring {
	public:
		_MSLstring(const char* value);
		_MSLstring(const string& value);
		const char* c_str() const {return data_;}
	protected:
	private:
		_RefCountedPtr<char, _Array<char> > data_;
	};

#ifndef _MSL_NO_CPP_NAMESPACE
	} // namespace std 
#endif

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif

// hh 990120 changed name of MSIPL flags
// hh 990314 Added const char* constructor to support nonstandard const char* constructors
//           on all of the standard exceptions.
