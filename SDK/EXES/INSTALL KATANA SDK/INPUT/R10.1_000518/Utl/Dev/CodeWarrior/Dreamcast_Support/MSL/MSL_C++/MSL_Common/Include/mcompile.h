/*  Metrowerks Standard Library  */

/*  $Date: 1999/01/25 16:33:59 $ 
 *  $Revision: 1.9 $ 
 *  $NoKeywords: $ 
 *
 *		Portions Copyright © 1995-1999 Metrowerks, Inc.
 *		All rights reserved.
 */

/**
 **  mcompile.h
 **
 **  Lib++  : The Modena C++ Standard Library,
 **           Version 2.4, October 1997
 **
 **  Copyright (c) 1995-1997 Modena Software Inc.
 **/

#ifndef MSIPL_COMPILE_H
#define MSIPL_COMPILE_H

// hh 990120 <mcompile.h> is now obsolete.  <mslconfig> is the place to configure
//           your library.  <mcompile.h> is used now just for backward compatibility
//           with older code.  It will translate the new #defines into the old ones
//           so that older code can continue to use the old Modena #defines.  The
//           old #defines will eventually go away so you should migrate any use of
//           them to the new #defines in <mslconfig>.
#include <mslconfig>

#define  RD_LOCK     1
#define  WR_LOCK     2
#define  SRD_LOCK    3
#define  SWR_LOCK    4

//#include <stddef.h>   // hh 971222 commented out
//#include <stdio.h>

/*************************************************************************
** Here is a list of all the compiler switches which can be used in
** accordance with your requirements.
** 
** COMPILER SWITCH               DEFINED                            
** ================================================================
**
** MSIPL_SOL1                    library is to be built on solaris 1.
** MSIPL_SOL2                    library is to be built on solaris 2.
** MSIPL_LINUX                   library is to be built on LINUX.
** MSIPL_WIN32                   library is to be built on Windows-95/NT.
** 
** MSIPL_APG40                   Apogee C++ (4.0) compiler is used.
** MSIPL_EDG232                  EDG C++ (2.32) compiler is used.
** MSIPL_EDG234                  EDG C++ (2.34) compiler is used.
** MSIPL_EDG235                  EDG C++ (2.35) compiler is used.
** MSIPL_EDG236                  EDG C++ (2.36) compiler is used.
** MSIPL_BC50                    Borland C++ (5.0) compiler is used. 
** MSIPL_MSVC50                  Microsoft C++ (5.0) compiler is used. 
**
** MSIPL_USING_NAMESPACE         library is defined in namespace std.
** 
** MSIPL_HEADER_EXTN_H           all header file names have ".h".
** MSIPL_ANSI_HEADER             all C header files are named a cxxx.
** 
** MSIPL_USE_EXTERNAL_MATHLIB    extended math library is provided.
** 
** MSIPL_EXCEPT                  exception handling enabled.
** __EDG_EXCEPT_CLASSES          edg's exception classes available.
** MSIPL_THROW_SPECS             throw specifications allowed.
** 
** MSIPL_DEFAULT_TEMPLATE_ARG    default template arguments allowed.
** MSIPL_EXPLICIT_INSTANTIATION  explicit instantiation allowed.
** MSIPL_PARTIAL_SPECIALIZATION  class template partial specialization.
** MSIPL_EXPLICIT_SPL_SPEC       template<> is mandatory for specialization.
** MSIPL_MEMBER_TEMPLATE         member templates allowed.
** MSIPL_CONST_TEMPLATE_ARG      contant template arguments supported.
** 
** MSIPL_STL_ALLOCATOR           use efficient allocators with less
**                               fragmentation of memory. 
**
** MSIPL_MULTITHREAD             library is to be multi-thread safe.
** MSIPL_OBJECT_LOCK             object level locking enabled.
** MSIPL_MULTIPLE_RW_LOCK        allows multiple simultaneous reads.
** 
** MSIPL_EXPLICIT                keyword "explicit" is defined.           
** 
** MSIPL_STATIC_CONST_INIT       static const data members initialisation 
**                               allowed.
** 
** MSIPL_BOOL_BUILTIN            data type bool builtin in compiler.
** 
** MSIPL_TYPENAME                keyword "typename" is defined.
** 
** MSIPL_NON_TYPE_TEMPARG        template arguments other than type allowed.
** 
** MSIPL_INSTANTIATE_ALL         aggresive instantiations done. 
**
** MSIPL_DEBUG_MODE              build the library in debug mode. 
******************************************************************************/

/* For Metrowerks */
// hh 990120 <mcompile.h> is now obsolete.  <mslconfig> is the place to configure
//           your library.  <mcompile.h> is used now just for backward compatibility
//           with older code.  It will translate the new #defines into the old ones
//           so that older code can continue to use the old Modena #defines.  The
//           old #defines will eventually go away so you should migrate any use of
//           them to the new #defines in <mslconfig>.
#ifdef __MWERKS__
	#ifndef _MSL_NO_CPP_NAMESPACE
		#define MSIPL_USING_NAMESPACE
	#endif
	#ifndef _MSL_NO_EXCEPTIONS
		#define MSIPL_EXCEPT
	#endif
	#ifndef _MSL_NO_THROW_SPECS
		#define MSIPL_THROW_SPECS
	#endif
	#define MSIPL_DEFAULT_TEMPLATE_ARG
	#define MSIPL_CONST_TEMPLATE_ARG
	#define MSIPL_EXPLICIT
	#define MSIPL_STATIC_CONST_INIT
	#ifndef _MSL_NO_BOOL
		#define MSIPL_BOOL_BUILTIN
	#endif
	#ifndef _MSL_NO_WCHART
		#define MSIPL_WCHART
	#endif
	#define MSIPL_NON_TYPE_TEMPARG
	#define MSIPL_ANSI_HEADER
	#define MSIPL_USE_EXTERNAL_MATHLIB
	#define MSIPL_TYPENAME
	#ifndef _MSL_NO_EXPLICIT_FUNC_TEMPLATE_ARG
		#define MSIPL_EXPLICIT_FUNC_TEMPLATE_ARG
	#endif
	#define MSIPL_EXPLICIT_SPL_SPEC
	#define MSIPL_HEADER_EXTN_H // hh 980105 just to pass Modena tests
	#ifndef _MSL_NO_PARTIAL_SPECIALIZATION
		#define MSIPL_PARTIAL_SPECIALIZATION
	#endif
	#ifndef _MSL_NO_MEMBER_TEMPLATE
		#define MSIPL_MEMBER_TEMPLATE
	#endif
	#ifdef _MSL_MULTITHREAD
		#define MSIPL_MULTITHREAD
	#endif
#endif
/*
#ifdef __MWERKS__
	#ifdef _MSL_USING_NAMESPACE
		#define MSIPL_USING_NAMESPACE
	#endif
	#if __option(exceptions)
		#define MSIPL_EXCEPT
	#endif
	#if __PPC_EABI__
		#pragma exceptions on
	#endif
	#define MSIPL_THROW_SPECS
	#define MSIPL_DEFAULT_TEMPLATE_ARG
	#define MSIPL_CONST_TEMPLATE_ARG
	#define MSIPL_EXPLICIT
	#define MSIPL_STATIC_CONST_INIT
	#if __option(bool)
		#define MSIPL_BOOL_BUILTIN
		#ifndef TYPE_BOOL
			#define TYPE_BOOL 1
		#endif
	#endif
	#if __option(wchar_type)
		#define MSIPL_WCHART
	#endif
	#define __MSL_LONGLONG_SUPPORT__
	#define MSIPL_NON_TYPE_TEMPARG
	#define MSIPL_ANSI_HEADER
	#define MSIPL_USE_EXTERNAL_MATHLIB
	#define MSIPL_TYPENAME
	#define MSIPL_EXPLICIT_FUNC_TEMPLATE_ARG
	#define MSIPL_EXPLICIT_SPL_SPEC
	#define MSIPL_HEADER_EXTN_H // hh 980105 just to pass Modena tests

	// _Inhibit_Container_Optimization, if uncommented will disable pointer
	// specializations in the containers.  This may make debugging easier.
//	#define _Inhibit_Container_Optimization

	// _Inhibit_Optimize_RB_bit is a space optimization that compacts the red/black
	// flag with the parent pointer in each node.  By uncommenting this
	// define, the optimization is turned off, and the red/black flag will
	// be stored as an enum in each node.
//	#define _Inhibit_Optimize_RB_bit


	#define MSIPL_PARTIAL_SPECIALIZATION
	#if !__option(ARM_conform)
		#define MSIPL_MEMBER_TEMPLATE
	#endif
	#ifdef __QNXC__
		#ifdef _MSL_USING_NAMESPACE
			#define MSIPL_USING_NAMESPACE
			#define _STD ::std::
		#else
			#define _STD
		#endif
		#define _MSL_CX_LIMITED_RANGE
	#endif
//	#define _No_Floating_Point
#endif
*/
#ifdef __GNUC__

	#define __QNXC__
	#define MSIPL_EXCEPT
	#define MSIPL_THROW_SPECS
	#define MSIPL_DEFAULT_TEMPLATE_ARG
	#define MSIPL_CONST_TEMPLATE_ARG
	#define MSIPL_EXPLICIT
	#define MSIPL_STATIC_CONST_INIT
	#define MSIPL_BOOL_BUILTIN
	#define MSIPL_NON_TYPE_TEMPARG
	#define MSIPL_ANSI_HEADER
	#define MSIPL_USE_EXTERNAL_MATHLIB
	#define MSIPL_TYPENAME
//	#define MSIPL_EXPLICIT_FUNC_TEMPLATE_ARG
	#define MSIPL_EXPLICIT_SPL_SPEC

	// Uncomment none or one of the following to specifiy which facets have
	// virtual methods (and are thus user overideable).  The standard says
	// all are overrideable (none uncommented).  Uncommenting _NO_VIRTUAL_FACETS
	// will make your executable smaller.
//	#define _NO_VIRTUAL_FACETS
	#define _ONLY_VIRTUAL_PUNCTS
//	#define _CUSTOM_VIRTUAL_FACETS

	#define MSIPL_PARTIAL_SPECIALIZATION
	#define _MSL_CX_LIMITED_RANGE
//	#define _No_Floating_Point
	#ifdef _MSL_USING_NAMESPACE
		#define MSIPL_USING_NAMESPACE
		#define _STD ::std::
	#else
		#define _STD
	#endif

#endif

/* For Apogee */
#ifdef MSIPL_APG40
#  define MSIPL_HEADER_EXTN_H
#  define MSIPL_THROW_SPECS
#  define MSIPL_DEFAULT_TEMPLATE_ARG
#  define MSIPL_NON_TYPE_TEMPARG
#  define MSIPL_STATIC_CONST_INIT
#  define MSIPL_CONST_TEMPLATE_ARG

#  define MSIPL_USING_NAMESPACE
#  define MSIPL_EXCEPT
#  define __EDG_EXCEPT_CLASSES

#  define MSIPL_BOOL_BUILTIN
#  define MSIPL_TYPENAME
#  define MSIPL_EXPLICIT_INSTANTIATION
//#  define MSIPL_EXPLICIT_FUNC_TEMPLATE_ARG

//#  define MSIPL_STL_ALLOCATOR

#  define MSIPL_EXPLICIT
#  define MSIPL_EXPLICIT_SPL_SPEC
#  define MSIPL_MEMBER_TEMPLATE

//# define MSIPL_DEBUG_MODE
#endif

/* For EDG */
#if defined(MSIPL_EDG234) || defined(MSIPL_EDG235) || defined (MSIPL_EDG236)
#  define MSIPL_EDG232
#  define MSIPL_PARTIAL_SPECIALIZATION
#endif

#ifdef MSIPL_EDG232
#  define MSIPL_HEADER_EXTN_H
#  define MSIPL_THROW_SPECS
#  define MSIPL_DEFAULT_TEMPLATE_ARG
#  define MSIPL_STATIC_CONST_INIT
#  define MSIPL_CONST_TEMPLATE_ARG

#  define MSIPL_USING_NAMESPACE
#  define MSIPL_EXCEPT
#  define __EDG_EXCEPT_CLASSES

#  define MSIPL_BOOL_BUILTIN
#  define MSIPL_TYPENAME
#  define MSIPL_EXPLICIT_INSTANTIATION
#  define MSIPL_INSTANTIATE_ALL
 
#  define MSIPL_EXPLICIT        
#  define MSIPL_EXPLICIT_SPL_SPEC   
#  define MSIPL_MEMBER_TEMPLATE
//#  define MSIPL_EXPLICIT_FUNC_TEMPLATE_ARG

//#  define MSIPL_STL_ALLOCATOR

//#  define MSIPL_MULTITHREAD
//#  define MSIPL_OBJECT_LOCK
//#  define MSIPL_MULTIPLE_RW_LOCK

//# define MSIPL_DEBUG_MODE
#endif

#ifdef MSIPL_EDG235
#  ifdef MSIPL_INSTANTIATE_ALL
#    undef MSIPL_INSTANTIATE_ALL
#  endif
#endif

/* For Borland C++ (5.0) compiler */
#ifdef MSIPL_BC50
#  define MSIPL_EXCEPT
#  define MSIPL_THROW_SPECS
#  define MSIPL_NONDEF
#  define MSIPL_TYPENAME
#  define MSIPL_BOOL_BUILTIN
#  pragma warn -inl
#endif

/* For Microsoft C++ (5.0) compiler */
#ifdef MSIPL_MSVC50
#  define MSIPL_HEADER_EXTN_H
#  define MSIPL_USING_NAMESPACE
#  define MSIPL_EXCEPT
#  define __EDG_EXCEPT_CLASSES
#endif

#ifdef MSIPL_SOL2
#  define MSIPL_SUN_OS
#endif

#ifndef MSIPL_SUN_OS
#  ifdef MSIPL_MULTIPLE_RW_LOCK
#    undef MSIPL_MULTIPLE_RW_LOCK
#  endif
#  if !defined(MSIPL_LINUX) && !defined(MSIPL_WIN32)
#    ifdef MSIPL_MULTITHREAD
#      undef MSIPL_MULTITHREAD
#    endif
#    ifdef MSIPL_OBJECT_LOCK
#      undef MSIPL_OBJECT_LOCK
#    endif
#  endif
#endif

#ifdef MSIPL_WIN32
	#define _WIN32
#endif

#ifdef MSIPL_MULTITHREAD
#  define DEC_MUTEX(obj)                mutex  obj;
#  define DEC_STATIC_MUTEX_P(obj)static mutex* obj;
#  define DEC_MUTEX_ARITH(size_t, mutex, obj) mutex_arith<size_t, mutex> obj;
#  define LOCK(mut_block, mut) \
       mutex_block<mutex> mut_block(mut)
#  define LOCK_P(mut_block, pmut) \
       if(pmut == 0) pmut = new mutex; \
       mutex_block<mutex> mut_block(*pmut)

#  define REMOVE(mutex)    mutex.remove()

#  ifdef MSIPL_OBJECT_LOCK

#    ifdef MSIPL_MULTIPLE_RW_LOCK
#      define DEC_OBJ_LOCK(obj)   rw_mutex  obj;
#      define READ_LOCK(mut)  \
         mutex_block<rw_mutex> rloc_mut(mut,RD_LOCK)
#      define WRITE_LOCK(mut)    \
         mutex_block<rw_mutex> wloc_mut(mut,WR_LOCK)
#      ifdef MSIPL_SUN_OS
#      define SREAD_LOCK(mut)  \
         while(mut.try_rdlock()) thr_yield(); \
         mutex_block<rw_mutex> rloc_mut(mut,SRD_LOCK); \
         mut.release() 
#      define SWRITE_LOCK(mut)    \
         while(mut.try_wrlock()) thr_yield(); \
         mutex_block<rw_mutex> wloc_mut(mut,SWR_LOCK); \
         mut.release() 
#      else
#      define SREAD_LOCK(mut)  \
         mutex_block<rw_mutex> rloc_mut(mut,RD_LOCK)
#      define SWRITE_LOCK(mut)    \
         mutex_block<rw_mutex> wloc_mut(mut,WR_LOCK)
#      endif

#    else                 /* !MSIPL_MULTIPLE_RW_LOCK */

#      define DEC_OBJ_LOCK(obj) mutex obj;
#      define READ_LOCK(mut)  \
          mutex_block<mutex> rloc_mut(mut,RD_LOCK)
#      define WRITE_LOCK(mut)     \
          mutex_block<mutex> wloc_mut(mut,WR_LOCK)
#      ifdef MSIPL_SUN_OS
#      define SREAD_LOCK(mut)  \
          while(mut.try_lock()) thr_yield(); \
          mutex_block<mutex> rloc_mut(mut,SRD_LOCK); \
          mut.release() 
#      define SWRITE_LOCK(mut)     \
          while(mut.try_lock()) thr_yield(); \
          mutex_block<mutex> wloc_mut(mut,SWR_LOCK); \
          mut.release() 
#      else
#      define SREAD_LOCK(mut)  \
          mutex_block<mutex> rloc_mut(mut,RD_LOCK)
#      define SWRITE_LOCK(mut)     \
          mutex_block<mutex> wloc_mut(mut,WR_LOCK)
#      endif

#    endif               /* MSIPL_MULTIPLE_RW_LOCK */ 

#  else

#    define DEC_OBJ_LOCK(obj)
#    define READ_LOCK(mut)       
#    define WRITE_LOCK(mut)
#    define SREAD_LOCK(mut)       
#    define SWRITE_LOCK(mut)

#  endif                 /* MSIPL_OBJECT_LOCK */

#else                    /* !MSIPL_MULTITHREAD */

#  define DEC_OBJ_LOCK(obj)
#  define DEC_MUTEX(obj)
#  define DEC_STATIC_MUTEX_P(obj)
#  define READ_LOCK(mut)              
#  define WRITE_LOCK(mut)            
#  define SREAD_LOCK(mut)       
#  define SWRITE_LOCK(mut)
#  define REMOVE(mut)               
#  define REMOVE_P(mut)               
#  define LOCK(bl_mut, mut)           
#  define LOCK_P(bl_mut, mut)           
#  define DEC_MUTEX_ARITH(size_t, mutex, obj) size_t obj;

#endif                   /* MSIPL_MULTITHREAD */

/*  // hh 990120 now done in mslconfig
#ifndef MSIPL_BOOL_BUILTIN
#  define bool int
#  define true 1
#  define false 0
#endif
*/

/* does your compiler support 'explicit' keyword ?? */
#ifndef MSIPL_EXPLICIT
#  define explicit
#endif

/* does your compiler support 'typename' ?? */
#ifndef MSIPL_TYPENAME
#  define typename
#endif

/* does your compiler support 'template<>' ?? */
#ifdef MSIPL_EXPLICIT_SPL_SPEC
#  define null_template template<>
#else
#  define null_template
#endif

/* does your compiler instantiate const ARG as a
   template parameter properly */
#ifdef MSIPL_CONST_TEMPLATE_ARG
#  define M_CONST const
#else
#  define M_CONST
#endif

#ifdef MSIPL_EXCEPT 
#  define MSIPL_THROW_ME(type, str) throw type##(##str##); 
#  define THROW_BAD_ALLOC throw bad_alloc ();
#  ifdef __EDG_EXCEPT_CLASSES
#     define MSIPL_THROW_BAD_CAST(str) throw bad_cast();
#  else
#     define MSIPL_THROW_BAD_CAST(str) throw bad_cast();  // hh 971227 removed str argument
#  endif
#  ifdef MSIPL_THROW_SPECS
#     define MSIPL_THROW throw()
#  else
#     define MSIPL_THROW 
#  endif
#  define MSIPL_TRY try
#  define MSIPL_CATCH catch(...)
#else
#  define MSIPL_THROW_ME(type, str) {fprintf(stderr,##str##); exit(1);}
#  define MSIPL_THROW_BAD_CAST(str) {fprintf(stderr,##str##); exit(1);}
#  define THROW_BAD_ALLOC {fprintf(stderr,"Could not allocate memory\n");exit(1);}
#  define MSIPL_THROW 
#  define MSIPL_TRY
#  define MSIPL_CATCH if (0)
#endif

#ifdef MSIPL_HEADER_EXTN_H
#  define MOD_INCLUDE(str) <str##.h>
#else
#  define MOD_INCLUDE(str) <str>
#endif

#ifdef MSIPL_ANSI_HEADER
#  define MOD_C_INCLUDE(str) MOD_INCLUDE(c##str)
#else
#  define MOD_C_INCLUDE(str) MOD_INCLUDE(str)
#endif

// To avoid possible clashes with g++(gnu C++).
#ifdef MSIPL_LINUX 
#  define NDEBUG   
#  define __signed__ signed
#  define __NO_MATH_INLINES
#endif 

#ifdef MSIPL_MEMBER_TEMPLATE
#  define ALLOC_BIND(type) typename Allocator::rebind<type>::other
#else
#  define ALLOC_BIND(type) DefAllocator<type>
#endif

#ifdef MSIPL_USING_NAMESPACE
#  define MSIPL_STD_BEGIN     namespace std {
#  define MSIPL_STD_END       }
#  define MSIPL_USING_STD using namespace std;
#  define MSIPLSTD ::std
#else
#  define MSIPL_STD_BEGIN
#  define MSIPL_STD_END
#  define MSIPL_USING_STD 
#  define MSIPLSTD
#endif

#ifdef MSIPL_DEFAULT_TEMPLATE_ARG
#  define DEFTEMPARG(i,j) i = j
#else
#  define DEFTEMPARG(i,j) i
#endif

#ifdef MSIPL_DEBUG_MODE
#  ifdef MSIPL_EXCEPT
#    define MSIPL_ASSERT(x) \
        if (!(x)) throw out_of_range ("Out of range exception occurred\n");
#  else
#    define MSIPL_ASSERT(x) \
        if (!(x)){fprintf(stderr,"Out of range exception occurred\n");exit(1);}
#  endif /* MSIPL_EXCEPT */
#else
#  define MSIPL_ASSERT(x)
#endif /* MSIPL_DEBUG_MODE */

#endif /* MSIPL_COMPILE_H */

// hh 971222 commented out #includes.  This file must be dependent on nothing
// hh 971226 added __MWERKS__ section
// hh 980120 added <mslGlobals.h>
