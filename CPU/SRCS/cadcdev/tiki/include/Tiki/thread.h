/*
   Tiki

   thread.h

   Copyright (C)2005 Cryptic Allusion, LLC
*/

#ifndef __TIKI_THREAD_H
#define __TIKI_THREAD_H

#include "Tiki/tikitypes.h"
#include "Tiki/platthread.h"
#include "Tiki/refcnt.h"

namespace Tiki {
namespace Thread {

// This expects that a type 'thread_t' has been defined in this namespace
// which is a pointer that is NULL for an invalid value, or otherwise
// points to a running thread. These functions are basically analogs of
// the pthread functions.

// Plat should have also defined mutex_t and cond_t.

bool create(thread_t * hndout, void * (*func)(void *), void * param);
bool join(thread_t hnd, void ** out);
bool equal(thread_t t1, thread_t t2);
thread_t self();
void exit(void * ptr);

bool mutex_create(mutex_t * out);
bool mutex_destroy(mutex_t * m);
bool mutex_trylock(mutex_t * m);
bool mutex_lock(mutex_t * m);
bool mutex_unlock(mutex_t * m);

bool cond_broadcast(cond_t *cond);
bool cond_destroy(cond_t *cond);
bool cond_create(cond_t *cond);
bool cond_signal(cond_t *cond);
bool cond_wait(cond_t *cond, mutex_t *mutex, uint64 maxWaitMicros);
bool cond_wait(cond_t *cond, mutex_t *mutex);

// Convenience object to wrap up thread funcs.
class Thread : public RefCnt {
public:
	Thread();
	Thread(void* (*)(void *), void * param);
	virtual ~Thread();
	
	bool operator==(const Thread & other) const;
	bool valid() const;
	
	bool create(void* (*func)(void *), void * param);
	bool join(void ** out = NULL);

protected:
	thread_t	m_hnd;
};

// Base class for any lockable object.
class Lockable : public RefCnt {
public:
	Lockable();
	virtual ~Lockable();
	
	virtual bool lock();
	virtual bool unlock();
};

// Stack-based auto-locker which can automatically lock and unlock a lockable.
class AutoLock {
public:
	AutoLock(Lockable * mtx, bool acquireNow = true);
	virtual ~AutoLock();

	bool lock();
	bool unlock();

	RefPtr<Lockable>	m_locked;
	bool			m_isLocked;
};

// Wrapper for mutex funcs.
class Cond;
class Mutex : public Lockable {
public:
	Mutex();
	virtual ~Mutex();
	
	bool	trylock();
	bool	lock();
	bool	unlock();

protected:
	mutex_t		m_mtx;
	friend class Cond;
};

// Wrapper for condvar funcs.
class Cond : public RefCnt {
public:
	Cond(Mutex * m);
	virtual ~Cond();
	
	bool	broadcast();
	bool	signal();
	bool	wait(uint64 maxWaitMicros);
	bool	wait();

protected:
	RefPtr<Mutex>	m_mtx;
	cond_t		m_cond;
};

}
}

#endif	// __TIKI_THREAD_H

