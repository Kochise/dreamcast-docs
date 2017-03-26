/*
   Tiki

   platthread.cpp

   Copyright (C)2005 Cryptic Allusion, LLC
*/

#include "pch.h"
#include "Tiki/thread.h"

#include <sys/time.h>
#include <time.h>

using Tiki::Thread::thread_t;
using Tiki::Thread::mutex_t;
using Tiki::Thread::cond_t;

bool Thread::create(thread_t * out, void * (*func)(void *), void * param) {
	return false;
}

bool Thread::join(thread_t thd, void ** out) {
	return false;
}

void Thread::exit(void * ptr) {
}

bool Thread::equal(thread_t t1, thread_t t2) {
	return false;
}

thread_t Thread::self() {
	return NULL;
}


bool Thread::mutex_create(mutex_t * out) {
	return false;
}

bool Thread::mutex_destroy(mutex_t * m) {
	return false;
}

bool Thread::mutex_trylock(mutex_t * m) {
	return false;
}

bool Thread::mutex_lock(mutex_t * m) {
	return false;
}

bool Thread::mutex_unlock(mutex_t * m) {
	return false;
}


bool Thread::cond_broadcast(cond_t *cond) {
	return false;
}

bool Thread::cond_destroy(cond_t *cond) {
	return false;
}

bool Thread::cond_create(cond_t *cond) {
	return false;
}

bool Thread::cond_signal(cond_t *cond) {
	return false;
}

bool Thread::cond_wait(cond_t *cond, mutex_t *mutex, uint64 maxWaitMicros) {
	return false;
}

bool Thread::cond_wait(cond_t * cond, mutex_t *mutex) {
	return false;
}










