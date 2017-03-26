// acassert.h
//
// This has the assert macro used by the audio subsystem.
//
//

#ifndef _AC_ASSERT_H
#define _AC_ASSERT_H

//	acAssert() under reconstruction
//
//#ifdef DEBUG
//	#undef assert
//
//	void _acAssert(char *moduleName,unsigned long lineNumber,char *message);
//	
//	#define assert(e,message)       ((e) ? ((void)0) : _acAssert(__FILE__, __LINE__,message))
//#else
	#undef assert
	
	#define assert(e,message)     ((void)0)
//#endif

#endif // end of #ifndef _AC_ASSERT_H

// -------------------------------------------------------------------------------------------
// end of file: acassert.h
// -------------------------------------------------------------------------------------------
