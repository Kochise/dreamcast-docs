/*  Metrowerks Standard Library  */

/*  $Date: 1999/01/23 00:26:07 $ 
 *  $Revision: 1.6 $ 
 *  $NoKeywords: $ 
 *
 *		Portions Copyright © 1995-1999 Metrowerks, Inc.
 *		All rights reserved.
 */

/**
 **  Lib++  : The Modena C++ Standard Library,
 **           Version 2.4, October 1997
 **
 **  Copyright (c) 1995-1997 Modena Software Inc.
 **/

#include <mcompile.h>

#include <istream>      // hh 981122 #include these instead of <iostream>
#include <ostream>
#include <mutex.h>
//#include <iostream>    // hh 971220 fixed MOD_INCLUDE
#include <fstream>     // hh 971220 fixed MOD_INCLUDE

MSIPL_STD_BEGIN

// Static data member initialization

#ifdef MSIPL_MULTITHREAD
mutex_arith<int, mutex>*  ios_base::Init::init_cnt = 0;
#else
int *ios_base::Init::init_cnt = 0;
#endif

  base_allocator::obj  *base_allocator::free_list[MSIPL_NFREELISTS];
  char  * base_allocator::start_free = 0;
  char  * base_allocator::end_free = 0;
  size_t  base_allocator::heap_size = 0;
#ifdef MSIPL_MULTITHREAD
  mutex * base_allocator::_mutex = 0;

#endif

int ios_base::index;

// hh 980513 moved into ios_base::Init::Init()
//static  filebuf   __msipl_fin (stdin);
//static  filebuf   __msipl_fout (stdout);
//static  filebuf   __msipl_ferr (stderr);

// hh 981124 added pragma
#pragma suppress_init_code on

istream cin;   //  (&__msipl_fin);  // hh 980513 default constructors should not
ostream cout;  // (&__msipl_fout);  //           allocate or otherwise touch any
ostream clog;  // (&__msipl_ferr);  //           memory.
ostream cerr;  // (&__msipl_ferr);

// hh 990109 Added support for wide standard streams
#ifdef MSIPL_WCHART

	wistream wcin;
	wostream wcout;
	wostream wclog;
	wostream wcerr;

#endif

#pragma suppress_init_code off

//static ios_base::Init  __msipl_ios_init;

ios_base::Init::Init ()
{
	// hh 980513 moved from file scope.  Trying to get std streams working
	//           before main, without leaking memory
	static  filebuf   __msipl_fin (stdin);
	static  filebuf   __msipl_fout (stdout);
	static  filebuf   __msipl_ferr (stderr);

	// hh 990109 Added support for wide standard streams
	#ifdef MSIPL_WCHART
		static  wfilebuf   wfin (stdin);
		static  wfilebuf   wfout (stdout);
		static  wfilebuf   wferr (stderr);
	#endif

	if (init_cnt != 0) 
		(*init_cnt)++;
	else
	{
		#ifdef MSIPL_MULTITHREAD
			init_cnt = new mutex_arith<int, mutex>;
		#else
			init_cnt = new int;
		#endif

		new (&cin)  istream (&__msipl_fin);
		new (&cout) ostream (&__msipl_fout);
		new (&cerr) ostream (&__msipl_ferr);
		new (&clog) ostream (&__msipl_ferr);
		cin.tie (&cout);
		cerr.tie (&cout);
		cerr.setf (ios_base::unitbuf);
		clog.tie (&cout);

		// hh 990109 Added support for wide standard streams
		#ifdef MSIPL_WCHART
			new (&wcin)  wistream (&wfin);
			new (&wcout) wostream (&wfout);
			new (&wcerr) wostream (&wferr);
			new (&wclog) wostream (&wferr);
			wcin.tie (&wcout);
			wcerr.tie (&wcout);
			wcerr.setf (ios_base::unitbuf);
			wclog.tie (&wcout);
		#endif

		*init_cnt = 1;
	}
}
 
ios_base::Init::~Init ()
{
	if (--(*init_cnt) == 0)
	{
		delete init_cnt;  // hh 980112 Clean up to prevent memory leak

		cout.flush ();
		cerr.flush ();
		clog.flush ();
		destroy(&cin);   // hh 981124 added destructors
		destroy(&cout);
		destroy(&cerr);
		destroy(&clog);

		// hh 990109 Added support for wide standard streams
		#ifdef MSIPL_WCHART
			wcout.flush ();
			wcerr.flush ();
			wclog.flush ();
			destroy(&wcin);
			destroy(&wcout);
			destroy(&wcerr);
			destroy(&wclog);
		#endif
	}
}

MSIPL_STD_END

// hh 971220 fixed MOD_INCLUDE
// hh 980112 Modifications to prevent memory leaks
// hh 981122 Replace #include <iostream> with <istream> and <ostream>
// hh 981124 Added code to insure that the standard streams are constructed and destructed
//           only within ios_base::Init
// hh 990109 Added support for wide standard streams
