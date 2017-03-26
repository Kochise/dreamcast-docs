/*
   Tiki

   thread.cpp

   Copyright (C)2005 Cryptic Allusion, LLC
*/

#include "pch.h"
#include "Tiki/thread.h"

using namespace Tiki::Thread;

// Heh...
Tiki::Thread::Thread::Thread() {
}

Tiki::Thread::Thread::Thread(void* (* func)(void *), void * param) {
	create(func, param);
}

Tiki::Thread::Thread::~Thread() {
	if (valid())
		join(NULL);
}

bool Tiki::Thread::Thread::operator==(const Thread & other) const {
	return equal(m_hnd, other.m_hnd);
}

bool Tiki::Thread::Thread::valid() const {
	return (m_hnd != NULL);
}

bool Tiki::Thread::Thread::create(void* (* func)(void *), void * param) {
	return Tiki::Thread::create(&m_hnd, func, param);
}

bool Tiki::Thread::Thread::join(void ** out) {
	return Tiki::Thread::join(m_hnd, out);
}

////////////////////////////////////////////////////////////////////////////////////////////////

Lockable::Lockable() {
}

Lockable::~Lockable() {
}

bool Lockable::lock() {
	assert( false );
	return false;
}

bool Lockable::unlock() {
	assert( false );
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////

AutoLock::AutoLock(Lockable * mtx, bool acquireNow) {
	m_locked = mtx;
	m_isLocked = false;
	if (acquireNow)
		lock();
}

AutoLock::~AutoLock() {
	unlock();
}

bool AutoLock::lock() {
	if (!m_isLocked) {
		m_isLocked = m_locked->lock();
		return m_isLocked;
	} else
		return true;
}

bool AutoLock::unlock() {
	if (m_isLocked) {
		m_isLocked = !m_locked->unlock();
		return !m_isLocked;
	} else
		return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////

Mutex::Mutex() {
	bool rv = Tiki::Thread::mutex_create(&m_mtx);
	assert( rv );
}

Mutex::~Mutex() {
	Tiki::Thread::mutex_destroy(&m_mtx);
}

bool Mutex::trylock() {
	return Tiki::Thread::mutex_trylock(&m_mtx);
}

bool Mutex::lock() {
	return Tiki::Thread::mutex_lock(&m_mtx);
}

bool Mutex::unlock() {
	return Tiki::Thread::mutex_unlock(&m_mtx);
}

////////////////////////////////////////////////////////////////////////////////////////////////

Cond::Cond(Mutex * m) {
	bool rv = Tiki::Thread::cond_create(&m_cond);
	assert( rv );
	m_mtx = m;
}

Cond::~Cond() {
	Tiki::Thread::cond_destroy(&m_cond);
}

bool Cond::broadcast() {
	return Tiki::Thread::cond_broadcast(&m_cond);
}

bool Cond::signal() {
	return Tiki::Thread::cond_signal(&m_cond);
}

bool Cond::wait(uint64 maxWaitMicros) {
	return Tiki::Thread::cond_wait(&m_cond, &m_mtx->m_mtx, maxWaitMicros);
}

bool Cond::wait() {
	return Tiki::Thread::cond_wait(&m_cond, &m_mtx->m_mtx);
}









