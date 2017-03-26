/*
   Tiki

   platthread.cpp

   Copyright (C)2005 Cryptic Allusion, LLC
*/

#include "pch.h"
#include "Tiki/thread.h"

#include <sys/time.h>
#include <time.h>

using Tiki::Thread::mutex_t;
using Tiki::Thread::cond_t;

bool Thread::create(pthread_t * out, void * (*func)(void *), void * param) {
	return pthread_create(out, NULL, func, param) >= 0;
}

bool Thread::join(pthread_t thd, void ** out) {
	return pthread_join(thd, out) >= 0;
}

void Thread::exit(void * ptr) {
	pthread_exit(ptr);
}

bool Thread::equal(pthread_t t1, pthread_t t2) {
	return !!pthread_equal(t1, t2);
}

pthread_t Thread::self() {
	return pthread_self();
}


bool Thread::mutex_create(mutex_t * out) {
	pthread_mutexattr_t attrs;
	if (pthread_mutexattr_init(&attrs) < 0) {
		assert( false );
		return false;
	}
	if (pthread_mutexattr_settype(&attrs, PTHREAD_MUTEX_RECURSIVE) < 0) {
		assert( false );
		return false;
	}
	int rv = pthread_mutex_init(out, &attrs) >= 0;
	pthread_mutexattr_destroy(&attrs);
	return rv;
}

bool Thread::mutex_destroy(mutex_t * m) {
	return pthread_mutex_destroy(m) >= 0;
}

bool Thread::mutex_trylock(mutex_t * m) {
	return pthread_mutex_trylock(m) >= 0;
}

bool Thread::mutex_lock(mutex_t * m) {
	return pthread_mutex_lock(m) >= 0;
}

bool Thread::mutex_unlock(mutex_t * m) {
	return pthread_mutex_unlock(m) >= 0;
}


bool Thread::cond_broadcast(cond_t *cond) {
	return pthread_cond_broadcast(cond) >= 0;
}

bool Thread::cond_destroy(cond_t *cond) {
	return pthread_cond_destroy(cond) >= 0;
}

bool Thread::cond_create(cond_t *cond) {
	return pthread_cond_init(cond, NULL) >= 0;
}

bool Thread::cond_signal(cond_t *cond) {
	return pthread_cond_signal(cond) >= 0;
}

bool Thread::cond_wait(cond_t *cond, mutex_t *mutex, uint64 maxWaitMicros) {
	struct timeval tn;
	gettimeofday(&tn, NULL);
	
	tn.tv_sec += maxWaitMicros / 1000000;
	tn.tv_usec += maxWaitMicros % 1000000;
	
	struct timespec ts;
	ts.tv_sec = tn.tv_sec;
	ts.tv_nsec = tn.tv_usec * 1000;
		
	return pthread_cond_timedwait(cond, mutex, &ts) >= 0;
}

bool Thread::cond_wait(cond_t * cond, mutex_t *mutex) {
	return pthread_cond_wait(cond, mutex) >= 0;
}










