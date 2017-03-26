#include "pch.h"

#include "Tiki/thread.h"
#include "Tiki/glhdrs.h"

struct StubInfo {
	void * (*func)(void *);
	void * data;
};

static DWORD WINAPI thdStub(void * data) {
	assert( data );
	StubInfo * inf = (StubInfo *)data;

	// Set up our GL context so that texture loading and such works here as well.
	HDC threadDc = GetDC(Tiki::GetWin32Window());
	HGLRC threadRc = wglCreateContext(threadDc);
	wglShareLists(Tiki::GetWin32MainHGLRC(), threadRc);
	wglMakeCurrent(threadDc, threadRc);

	void * result = inf->func(inf->data);
	delete inf;

	wglDeleteContext(threadRc);
	ReleaseDC(Tiki::GetWin32Window(), threadDc);

	return (DWORD)(DWORD_PTR)result;
}

bool Thread::create(HANDLE * out, void * (*func)(void *), void * param) {
	StubInfo * inf = new StubInfo;
	inf->func = func;
	inf->data = param;
	DWORD threadId;
	assert( out );
	*out = CreateThread(NULL, 0, thdStub, inf, 0, &threadId);
	return *out != INVALID_HANDLE_VALUE;
}

bool Thread::join(HANDLE thd, void ** out) {
	DWORD code;

	DWORD result = WaitForSingleObject( thd, INFINITE );
	if (result != WAIT_OBJECT_0) {
		Debug::printf("Thread::join WaitForSingleObject error: %d\n", GetLastError());
		return false;
	}
	if (!GetExitCodeThread( thd, &code )) {
		Debug::printf("Thread::join GetExitCodeThread error: %d\n", GetLastError());
		return false;
	}
	CloseHandle( thd );
	if (out)
		*out = (void *)(DWORD_PTR)code;

	return true;
}

bool Thread::equal(thread_t t1, thread_t t2) {
	/* DWORD id1 = GetThreadId(t1);
	DWORD id2 = GetThreadId(t2);
	return id1 == id2; */
	return t1 == t2;
}

Thread::thread_t Thread::self() {
	return GetCurrentThread();
}

void Thread::exit(void * ptr) {
	ExitThread((DWORD)(DWORD_PTR)ptr);
}


bool Thread::mutex_create(mutex_t * out) {
	assert( out );

	*out = CreateMutex(NULL, FALSE, NULL);
	return *out != INVALID_HANDLE_VALUE;
}

bool Thread::mutex_destroy(mutex_t * m) {
	assert( m );

	CloseHandle(*m);
	return true;
}

bool Thread::mutex_trylock(mutex_t * m) {
	assert( m );
	DWORD result = WaitForSingleObject(*m, 0);
	return result == WAIT_OBJECT_0;
}

bool Thread::mutex_lock(mutex_t * m) {
	assert( m );
	DWORD result = WaitForSingleObject(*m, INFINITE);
	return result == WAIT_OBJECT_0;
}

bool Thread::mutex_unlock(mutex_t * m) {
	assert( m );
	return !!ReleaseMutex(*m);
}


// XXX These aren't implemented yet. The mapping to Win32 is a little tricky.
bool Thread::cond_broadcast(cond_t *cond) {
	assert( false );
	return false;
}

bool Thread::cond_destroy(cond_t *cond) {
	assert( false );
	return false;
}

bool Thread::cond_create(cond_t *cond) {
	assert( false );
	return false;
}

bool Thread::cond_signal(cond_t *cond) {
	assert( false );
	return false;
}

bool Thread::cond_wait(cond_t *cond, mutex_t *mutex, uint64 maxWaitMicros) {
	assert( false );
	return false;
}

bool Thread::cond_wait(cond_t *cond, mutex_t *mutex) {
	assert( false );
	return false;
}






















