/*  Metrowerks Standard Library  */

/*  $Date: 1999/04/01 00:31:09 $ 
 *  $Revision: 1.9 $ 
 *  $NoKeywords: $ 
 *
 *		Portions Copyright © 1995-1999 Metrowerks, Inc.
 *		All rights reserved.
 */

/**
 **  mutex.h
 **/

#ifndef _MUTEX_H
#define _MUTEX_H

#include <mslconfig>

#ifdef _MWMT

	#ifdef _USE_PTHREADS

		#include <pthread.h>

		class mutex
		{
		public:
			mutex() {pthread_mutex_init(&m_, 0);}
			~mutex() {pthread_mutex_destroy(&m_);}
			void lock() {pthread_mutex_lock(&m_);}
			void unlock() {pthread_mutex_unlock(&m_);}
		private:
			pthread_mutex_t m_;

			mutex(const mutex&);             // Not defined
			mutex& operator=(const mutex&);  // Not defined
		};
	
	#elif __dest_os == __win32_os

		#pragma ANSI_strict off

		#include <WINDEF.H>
		#include <WINBASE.H>

		#pragma ANSI_strict reset

		class mutex
		{
		public:
			mutex() {InitializeCriticalSection(&m_);}
			~mutex() {DeleteCriticalSection(&m_);}
			void lock() {EnterCriticalSection(&m_);}
			void unlock() {LeaveCriticalSection(&m_);}
		private:
			CRITICAL_SECTION m_;

			mutex(const mutex&);             // Not defined
			mutex& operator=(const mutex&);  // Not defined
		};

	#elif __dest_os == __be_os

		#include <OS.h>
		#include <be_rw_lock.h>

		class mutex
		{
		public:
			mutex() : m_(0) {}
			~mutex() {m_ = 0;}
			void lock() {acquire_spinlock(&m_);}
			void unlock() {release_spinlock(&m_);}
		private:
			long m_;

			mutex(const mutex&);             // Not defined
			mutex& operator=(const mutex&);  // Not defined
		};
	
	#else

		#error OS not supported in mutex.h

	#endif

	class mutex_lock
	{
	public:
		mutex_lock(mutex& m) : m_(m) {m_.lock();}
		~mutex_lock() {m_.unlock();}
	private:
		mutex& m_;

		mutex_lock(const mutex_lock&);             // Not defined
		mutex_lock& operator=(const mutex_lock&);  // Not defined
	};

	#define _MSL_DECLARE_MUTEX(mut) mutex mut;
	#define _MSL_LOCK_MUTEX(lock, mut) mutex_lock lock(mut);

#else  // !_MWMT

	#define _MSL_DECLARE_MUTEX(mut)
	#define _MSL_LOCK_MUTEX(lock, mut)

#endif // _MWMT

#endif // _MUTEX_H

// hh 971220 fixed MOD_INCLUDE
// hh 971222 added alignment wrapper
// bs 990121 added BeOS changes
// hh 990318 Rewrote
