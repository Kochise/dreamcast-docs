/* ----------------------------------------------------------------------------
Microsoft	D.T.C (Distributed Transaction Coordinator)

(c)	1995	Microsoft Corporation.	All Rights Reserved

@doc

@module UTSem.H  |

	SYNCHRO - C++ class to provide synchronization object encapsulation

	This implementation of the SYNCHRO class provides multi-read XOR single-write
	(a.k.a. shared vs. exclusive) lock capabilities, with protection against
	writer starvation. Code origianly borrowed from 
	(c) 1994 by Daniel S. Glasser and then modified for our needs.

@devnote None

@rev	3	| 1st-Aug-1996	|	GaganC		| Added the spin lock code and class
@rev	2	| 31-May-1996	|	GaganC		| Removed the special code for x86
@rev	1	| 18th Jan, 96	|	GaganC		| Special cased UTGuard for X86
@rev 	0 	| 4th Feb,95	|	GaganC 		| Created
---------------------------------------------------------------------------- */
#ifndef __UTSEM_H__
#define __UTSEM_H__


// -------------------------------------------------------------
//				INCLUDES
// -------------------------------------------------------------
#include "UTAssert.H"


// -------------------------------------------------------------
//				CONSTANTS AND TYPES
// -------------------------------------------------------------
typedef enum {SLC_WRITE, SLC_READWRITE, SLC_READWRITEPROMOTE}
			 SYNCH_LOCK_CAPS;

typedef enum {SLT_READ, SLT_READPROMOTE, SLT_WRITE}
			 SYNCH_LOCK_TYPE;

const int NUM_SYNCH_LOCK_TYPES = SLT_WRITE + 1;



// -------------------------------------------------------------
//				FORWARDS
// -------------------------------------------------------------
class CSemExclusive;
class CSemExclusiveSL;
class UTGuard;
class UTSemReadWrite;
class UTSemCheapReadWrite;


// -------------------------------------------------------------
//					GLOBAL HELPER FUNCTIONS
// -------------------------------------------------------------


/* ----------------------------------------------------------------------------
 @func Description:<nl>

   Guarantees isolated increments of *pl.<nl><nl>

 Usage:<nl>
   Use instead of InterlockedIncrement for Win16/Win32 portability.<nl><nl>

 @rev 0 | 3/21/95 | Rcraig | Created.
---------------------------------------------------------------------------- */
inline LONG SafeIncrement ( LPLONG pl )
{
	return (InterlockedIncrement (pl));
} // SafeIncrement



/* ----------------------------------------------------------------------------
 @func Description:<nl>
   Win16/Win32 abstraction wrapper: 
   Guarantees isolated decrements of *pl.<nl><nl>

 Usage:<nl>
   Use instead of InterlockedDecrement for Win16/Win32 portability.<nl><nl>

 @rev 0 | 3/21/95 | Rcraig | Created.
---------------------------------------------------------------------------- */
inline LONG SafeDecrement ( LPLONG pl )
{
	return (InterlockedDecrement (pl));
} // SafeDecrement



/* ----------------------------------------------------------------------------
@class	UTGuard
	This object represents a guard that can be acquired or released. The 
	advantage with useing this instead of a critical section is that this
	is non blocking. If AcquireGuard fails, it will return false and will not
	block.

@rev 	0 	| 4th Feb,95 | GaganC 		| Created
---------------------------------------------------------------------------- */
class UTGuard
{
private:
	long			m_lVal;

public:
	//@cmember Constructor
	UTGuard (void);
	//@cmember Destructor
	~UTGuard (void);

	//@cmember	Acquires the guard
	BOOL			AcquireGuard (void);
	//@cmember	Releases the guard
	void			ReleaseGuard (void);
	
	//@cmember	Initializes the Guard
	void			Init (void);
} ; //End class UTGuard



//-----------------------------------------------------------------------------
//
//		IMPLEMENTATION of class UTGuard
//
//-----------------------------------------------------------------------------


/* ----------------------------------------------------------------------------
@mfunc 

---------------------------------------------------------------------------- */
inline UTGuard::UTGuard ( void )
{
	m_lVal = 0;
}



/* ----------------------------------------------------------------------------
@mfunc 

---------------------------------------------------------------------------- */
inline UTGuard::~UTGuard ( void )
{
	//Do nothing
}



/* ----------------------------------------------------------------------------
@mfunc 

---------------------------------------------------------------------------- */
inline BOOL	UTGuard::AcquireGuard (void)
{
	long		lVal;

	lVal = InterlockedExchange (&m_lVal, 1);

	return (lVal == 0);
}



/* ----------------------------------------------------------------------------
@mfunc 

---------------------------------------------------------------------------- */
inline void	UTGuard::ReleaseGuard (void)
{
	m_lVal = 0;
}


/* ----------------------------------------------------------------------------
@mfunc 

---------------------------------------------------------------------------- */
void inline UTGuard::Init ( void )
{
	m_lVal = 0;
}



/* ----------------------------------------------------------------------------
@class UTSemReadWrite

@rev 	0 	| 4th Feb,95 | GaganC 		| Created
---------------------------------------------------------------------------- */
class UTSemReadWrite
{
private:
	CRITICAL_SECTION csExclusive;	// Critical section object to synchronize writers
	CRITICAL_SECTION csReader;		// Critical section object to synchronize readers
	HANDLE hevReadDone;				// Manual-reset event to notify writers of 
									//reader completion
	int cReaders;					// Count of current readers

	BOOL fInitSucceeded;			// TRUE if the constructor function succeeded

public:
	UTSemReadWrite(void);				// Constructor
	~UTSemReadWrite(void);				// Destructor

	// This implementation supports Read and Write locks
	SYNCH_LOCK_CAPS GetCaps(void) { return SLC_READWRITE; };

	// This object is valid if it was initialized
	BOOL IsValid(void) { return fInitSucceeded; }

	BOOL Lock(SYNCH_LOCK_TYPE);	// Lock the object
	BOOL UnLock(SYNCH_LOCK_TYPE);	// Unlock the object
};




//-----------------------------------------------------------------------------
//
//		IMPLEMENTATION of class UTSemReadWrite
//
//-----------------------------------------------------------------------------

/* ----------------------------------------------------------------------------
@mfunc 

	SYNCHRO class - Constructor

	Create the event, initialize the critical section objects and reader count,
	and return.
---------------------------------------------------------------------------- */
inline UTSemReadWrite::UTSemReadWrite(void)
{
	// Create the manual-reset event (the only init that can fail)
	hevReadDone = CreateEvent(NULL, TRUE, TRUE, NULL);

	fInitSucceeded = hevReadDone != NULL;

	// If we created the event, proceed with the risk-free initialization
	if (fInitSucceeded)
	{
		cReaders = 0;
		InitializeCriticalSection(&csExclusive);
		InitializeCriticalSection(&csReader);
	}

	return;
}


/* ----------------------------------------------------------------------------
@mfunc 

	SYNCHRO class - Destructor

	Free the event, delete the critical section objects, and return.
---------------------------------------------------------------------------- */
inline UTSemReadWrite::~UTSemReadWrite(void)
{
	if (IsValid())
	{
		CloseHandle(hevReadDone);
		DeleteCriticalSection(&csExclusive);
		DeleteCriticalSection(&csReader);
	}

	return;
}




/* ----------------------------------------------------------------------------
@mfunc 

	SYNCHRO class - Lock member function
---------------------------------------------------------------------------- */
inline BOOL UTSemReadWrite::Lock(SYNCH_LOCK_TYPE lt)
{
	// Verify that the object is valid
	if (! IsValid())
		return FALSE;

	// Verify that the specified lock type is supported by this implementation
	if (lt == SLT_READPROMOTE)
		return FALSE;

	// Claim the read lock or write lock as specified
	if (lt == SLT_READ)
	{
		// Claim the <csExclusive> critical section.  This call blocks if there's
		// an active writer or if there's a writer waiting for active readers to
		// complete.
		EnterCriticalSection(&csExclusive);

		// Claim access to the reader count.  If this blocks, it's only for the
		// briefest moment, while other threads go through to increment or
		// decrement the reader count.
		EnterCriticalSection(&csReader);

		// Increment the reader count.  If this is the first reader, we reset the
		// hevReadDone event so that the next writer blocks.
		if (cReaders++ == 0)
			ResetEvent(hevReadDone);

		// Release access to the reader count
		LeaveCriticalSection(&csReader);

		// Release access to the <csExclusive> critical section.  This enables
		// other readers to come through and the next writer to wait for active
		// readers to complete (which in turn prevents new readers from entering).
		LeaveCriticalSection(&csExclusive);
	}
	else
	{
		// Verify that since this isn't the read lock, that it's the write lock
		Assert(lt == SLT_WRITE);

		// Claim the <csExclusive> critical section.  This not only prevents other
		// threads from claiming the write lock, but also prevents any new threads
		// from claiming the read lock.
		EnterCriticalSection(&csExclusive);

		// Wait for the active readers to release their read locks.
		return WaitForSingleObject(hevReadDone, INFINITE) == WAIT_OBJECT_0;
	}

	return TRUE;
} //End Lock



/* ----------------------------------------------------------------------------
@mfunc 

	SYNCHRO class - Unlock member function
---------------------------------------------------------------------------- */
inline BOOL UTSemReadWrite::UnLock(SYNCH_LOCK_TYPE lt)
{
	// Verify that the object is valid
	if (! IsValid())
		return FALSE;

	// Verify that the specified lock type is supported by this implementation
	if (lt == SLT_READPROMOTE)
		return FALSE;

	// Release the read lock or write lock as specified
	if (lt == SLT_READ)
	{
		// Claim access to the reader count.  If this blocks, it's only for the
		// briefest moment, while other threads go through to increment or
		// decrement the reader count.
		EnterCriticalSection(&csReader);

		// Decrement the reader count.  If this is the last reader, set 
		// <hevReadDone>, which allows the first waiting writer to proceed.
		if (--cReaders == 0)
			SetEvent(hevReadDone);

		// Release access to the reader count
		LeaveCriticalSection(&csReader);
	}
	else
	{
		// Verify that since this isn't the read lock, that it's the write lock
		Assert(lt == SLT_WRITE);

		// Make <csExclusive> available to one other writer or to the first reader
		LeaveCriticalSection(&csExclusive);
	}

	return TRUE;
} //End Unlock


/* ----------------------------------------------------------------------------
@class UTSemCheapReadWrite

@rev 	0 	| 5/1/97     | Shaiwals		| Created using UTSemReadWrite, reader
			|			 |				| access to the lock is cheaper if 
			|			 |				| there is already a reader present
---------------------------------------------------------------------------- */
class UTSemCheapReadWrite
{
private:
	CRITICAL_SECTION csExclusive;	// Critical section object to provide core locking
	CRITICAL_SECTION csReader;		// Critical section object to synchronize readers
	CRITICAL_SECTION csWriter;		// Critical section object to synchronize writers
	HANDLE hevReadDone;				// Manual-reset event to notify writers of 
									// reader completion

	HANDLE hevReaderPresent;		// Readers are currently present
	HANDLE hevWriterPresent;		// Writers are currently present
	long cReaders;					// Count of current readers
	long cWriters;					// Count of writers waiting

	BOOL fInitSucceeded;			// TRUE if the constructor function succeeded
	BOOL m_fReader;					// Flag to signal that readers presence has
									// been notifed

public:
	UTSemCheapReadWrite(void);				// Constructor
	~UTSemCheapReadWrite(void);				// Destructor

	// This implementation supports Read and Write locks
	SYNCH_LOCK_CAPS GetCaps(void) { return SLC_READWRITE; };

	// This object is valid if it was initialized
	BOOL IsValid(void) { return fInitSucceeded; }

	BOOL Lock(SYNCH_LOCK_TYPE);	// Lock the object
	BOOL UnLock(SYNCH_LOCK_TYPE);	// Unlock the object
};




//-----------------------------------------------------------------------------
//
//		IMPLEMENTATION of class UTSemCheapReadWrite
//
//-----------------------------------------------------------------------------

/* ----------------------------------------------------------------------------
@mfunc 

	SYNCHRO class - Constructor

	Create the event, initialize the critical section objects and reader count,
	and return.
---------------------------------------------------------------------------- */
inline UTSemCheapReadWrite::UTSemCheapReadWrite(void)
{
	// Create the manual-reset event (the only init that can fail)
	hevReadDone = CreateEvent(NULL, TRUE, TRUE, NULL);
	hevReaderPresent = CreateEvent(NULL, TRUE, FALSE, NULL);
	hevWriterPresent = CreateEvent(NULL, TRUE, FALSE, NULL);

	fInitSucceeded = (hevReadDone != NULL) && 
						(hevReaderPresent != NULL) && 
						(hevWriterPresent != NULL);

	// If we created the event, proceed with the risk-free initialization
	if (fInitSucceeded)
	{
		cReaders = -1;
		cWriters = -1;
		m_fReader = FALSE;
		InitializeCriticalSection(&csExclusive);
		InitializeCriticalSection(&csReader);
		InitializeCriticalSection(&csWriter);
	}

	return;
}


/* ----------------------------------------------------------------------------
@mfunc 

	SYNCHRO class - Destructor

	Free the event, delete the critical section objects, and return.
---------------------------------------------------------------------------- */
inline UTSemCheapReadWrite::~UTSemCheapReadWrite(void)
{
	if (IsValid())
	{
		CloseHandle(hevReadDone);
		DeleteCriticalSection(&csExclusive);
		DeleteCriticalSection(&csReader);
	}

	return;
}




/* ----------------------------------------------------------------------------
@mfunc 

	SYNCHRO class - Lock member function
---------------------------------------------------------------------------- */
inline BOOL UTSemCheapReadWrite::Lock(SYNCH_LOCK_TYPE lt)
{
	// Verify that the object is valid
	if (! IsValid())
		return FALSE;

	// Verify that the specified lock type is supported by this implementation
	if (lt == SLT_READPROMOTE)
		return FALSE;

	// Claim the read lock or write lock as specified
	if (lt == SLT_READ)
	{
		// First try to get the reader lock cheaply by incrementing
		// the reader count.  Only if reader count is positive
		// do we try and test that a reader is present
		if (InterlockedIncrement (&cReaders) > 0)
		{
			// Test that there is actually a reader holding on the the lock.
			// It is possible to that the reader count is greater that -1
			// but still there are no readers who have actually acquired the
			// lock
			if (WaitForSingleObject (hevReaderPresent, 0) == WAIT_OBJECT_0)
			{
				// Only if there are no writers waiting to acquire the lock
				// do we try to acquire the lock. Without this we cannot
				// guarantee that the writer wont starve.
				if (WaitForSingleObject (hevWriterPresent, 0) == WAIT_TIMEOUT)
					return TRUE;
			}
		}

		// Decrement extra reader count
		InterlockedDecrement (&cReaders);

		// Claim the <csExclusive> critical section.  This call blocks if there's
		// an active writer or if there's a writer waiting for active readers to
		// complete.
		EnterCriticalSection(&csExclusive);

		// Claim access to the reader count.  If this blocks, it's only for the
		// briefest moment, while other threads go through to increment or
		// decrement the reader count.
		EnterCriticalSection(&csReader);

		// Increment the reader count.  If this is the first reader, we reset the
		// hevReadDone event so that the next writer blocks.
		if (InterlockedIncrement (&cReaders) >= 0)
		{
			if (!m_fReader)
			{
				SetEvent (hevReaderPresent);
				ResetEvent(hevReadDone);
				m_fReader = TRUE;
			}
		}

		// Release access to the reader count
		LeaveCriticalSection(&csReader);

		// Release access to the <csExclusive> critical section.  This enables
		// other readers to come through and the next writer to wait for active
		// readers to complete (which in turn prevents new readers from entering).
		LeaveCriticalSection(&csExclusive);
	}
	else
	{
		// Verify that since this isn't the read lock, that it's the write lock
		Assert(lt == SLT_WRITE);

		// Gain access to the writer count
		EnterCriticalSection(&csWriter);

		// Increment the writer count.  If this is the writer reader, we set the
		// hevWriterPresent event so that new readers give way to the writer.
		if (InterlockedIncrement (&cWriters) == 0)
		{
			SetEvent (hevWriterPresent);
		}

		// Release access to the writer count
		LeaveCriticalSection(&csWriter);

		// Claim the <csExclusive> critical section.  This not only prevents other
		// threads from claiming the write lock, but also prevents any new threads
		// from claiming the read lock.
		EnterCriticalSection(&csExclusive);

		// Wait for the active readers to release their read locks.
		return WaitForSingleObject(hevReadDone, INFINITE) == WAIT_OBJECT_0;
	}

	return TRUE;
} //End Lock



/* ----------------------------------------------------------------------------
@mfunc 

	SYNCHRO class - Unlock member function
---------------------------------------------------------------------------- */
inline BOOL UTSemCheapReadWrite::UnLock(SYNCH_LOCK_TYPE lt)
{
	// Verify that the object is valid
	if (! IsValid())
		return FALSE;

	// Verify that the specified lock type is supported by this implementation
	if (lt == SLT_READPROMOTE)
		return FALSE;

	// Release the read lock or write lock as specified
	if (lt == SLT_READ)
	{
		// Claim access to the reader count.  If this blocks, it's only for the
		// briefest moment, while other threads go through to increment or
		// decrement the reader count.
		EnterCriticalSection(&csReader);

		// Decrement the reader count.  If this is the last reader, set 
		// <hevReadDone>, which allows the first waiting writer to proceed.
		if (InterlockedDecrement (&cReaders) < 0)
		{
			ResetEvent (hevReaderPresent);
			SetEvent(hevReadDone);
			m_fReader = FALSE;
		}

		// Release access to the reader count
		LeaveCriticalSection(&csReader);
	}
	else
	{
		// Verify that since this isn't the read lock, that it's the write lock
		Assert(lt == SLT_WRITE);
		
		// Gain access to the writer count
		EnterCriticalSection(&csWriter);

		// Decrement the writer count.  If this is the last writer, we reset the
		// hevWriterPresent event.
		if (InterlockedDecrement (&cWriters) < 0)
		{
			ResetEvent (hevWriterPresent);
		}

		// Release access to the writer count
		LeaveCriticalSection(&csWriter);

		// Make <csExclusive> available to one other writer or to the first reader
		LeaveCriticalSection(&csExclusive);
	}

	return TRUE;
} //End Unlock



/* ----------------------------------------------------------------------------
@class CSemExclusive:

	@rev 	0 	| 4th Feb,95 | GaganC 		| Created
---------------------------------------------------------------------------- */
class CSemExclusive
{
public:
	CSemExclusive (void);
	~CSemExclusive (void);
	void Lock (void);
	void UnLock (void);
private:
	CRITICAL_SECTION m_csx;
};	//end class CSemExclusive




//-----------------------------------------------------------------------------
//
//		IMPLEMENTATION of class CSemExclusive
//
//-----------------------------------------------------------------------------
/* ----------------------------------------------------------------------------
@mfunc 
---------------------------------------------------------------------------- */
inline CSemExclusive::CSemExclusive 
	(
		void
	)
{
	InitializeCriticalSection (&m_csx);
}

/* ----------------------------------------------------------------------------
@mfunc 

---------------------------------------------------------------------------- */
inline CSemExclusive::~CSemExclusive 
	(
		void
	)
{
	DeleteCriticalSection (&m_csx);
}


/* ----------------------------------------------------------------------------
@mfunc 
---------------------------------------------------------------------------- */
inline void CSemExclusive::Lock
	(
		void
	)
{
	EnterCriticalSection (&m_csx);
}


/* ----------------------------------------------------------------------------
@mfunc 
---------------------------------------------------------------------------- */
inline void CSemExclusive::UnLock
	(
		void
	)
{
	LeaveCriticalSection (&m_csx);
}






/* ----------------------------------------------------------------------------
@class CSemExclusiveSL:

---------------------------------------------------------------------------- */
class CSemExclusiveSL
{
public:
	CSemExclusiveSL (void);
	~CSemExclusiveSL (void);

	void Lock (void);
	void UnLock (void);
private:
	DWORD volatile m_dwLock;
	DWORD volatile *m_pdwLock;
	DWORD volatile m_dwOwningThread;
	ULONG volatile m_ulRecursionCount;
};


/* ----------------------------------------------------------------------------
@mfunc 

---------------------------------------------------------------------------- */
inline CSemExclusiveSL::CSemExclusiveSL ( void )
{
	m_dwOwningThread = 0;
	m_ulRecursionCount = 0;
	m_dwLock = 0;
	m_pdwLock = &m_dwLock;
}


/* ----------------------------------------------------------------------------
@mfunc 

---------------------------------------------------------------------------- */
inline CSemExclusiveSL::~CSemExclusiveSL ( void )
{
	//Nothing to do
}


/* ----------------------------------------------------------------------------
@mfunc 

**  Lock -- Obtains an SMP safe lock on the address given.
**	WARNING: Does not release any semaphore or critsec when waiting.
**

@rev 0  Created 04/20/93 by LaleD 
@rev 1	modified 7/13/96 by shaiwals
---------------------------------------------------------------------------- */
inline void CSemExclusiveSL::Lock ( void )
{
    DWORD	i;
	DWORD	n	=	0;
    int		m	=	0;


startover:

	if (InterlockedExchange((long *)m_pdwLock, 1) == 0)
	{
		m_dwOwningThread = GetCurrentThreadId();
		return;
	}

	if (m_dwOwningThread == GetCurrentThreadId())
	{
		m_ulRecursionCount++;
		return;
	}

	// Give away my time slice to another thread as the probability
	// of my getting this lock right away are low - shaiwals
	//Sleep (1); 

	/* retry using safe test only after cheaper, unsafe test succeeds */
	for (i = 0 ; i < (DWORD)(10000) ; i++)
	{
		if (*m_pdwLock == 0)
		{
			goto startover;
		}
	}

	/*
	**  Yield after hitting the cspinctr limit
	**    Sleep(0) only yields to threads of same priority
	**    if hit limit 10000 times, sleep 5sec and test for kill
	**    this provides a chance to CTRL-C it if stuck in loop
	*/
	
	m++;

	if( ( m % 10000 ) == 0)
	{
		Sleep(5000);
	}
	else
	{
		Sleep(0);
	}

	goto startover;
	/* try again */
}

/* ----------------------------------------------------------------------------
@mfunc 

---------------------------------------------------------------------------- */
inline void CSemExclusiveSL::UnLock ( void )
{
	AssertSz (m_dwOwningThread == GetCurrentThreadId(), \
						"Lock released by someone who doesnt own the lock!!!");

	if (m_ulRecursionCount > 0)
	{
		m_ulRecursionCount--;
		return;
	}

	m_dwOwningThread = 0;
	*m_pdwLock = 0;
}



#endif __UTSEM_H__
