// This can be useful for checking whether some pthread program compiled
// correctly (e.g. libstdc++).
// #define MUTEX_DEBUG 1

#include <pthread.h>
#include <errno.h>
#include <assert.h>

#if MUTEX_DEBUG == 1
#include <stdio.h>
#endif

// XXX Recursive mutexes are not supported ... this could cause deadlocks
// in code expecting it. Where do you set that!?

/* Mutex Initialization Attributes, P1003.1c/Draft 10, p. 81 */   

int pthread_mutexattr_init(pthread_mutexattr_t *attr) {
	return 0;
}

int pthread_mutexattr_destroy(pthread_mutexattr_t *attr) {
	return 0;
}

int pthread_mutexattr_getpshared(const pthread_mutexattr_t *attr, int  *pshared) {
	return 0;
}

int pthread_mutexattr_setpshared(pthread_mutexattr_t *attr, int pshared) {
	return 0;
}

/* Initializing and Destroying a Mutex, P1003.1c/Draft 10, p. 87 */

int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr) {
	assert( mutex );

	*mutex = mutex_create();
	if (*mutex)
		return 0;
	else
		return EAGAIN;
}

int pthread_mutex_destroy(pthread_mutex_t *mutex) {
	assert( mutex );

	mutex_destroy(*mutex);

	return 0;
}

// XXX mutexes made this way should probably be nuked at shutdown
#define CHK_AND_CREATE \
	if (*mutex == PTHREAD_MUTEX_INITIALIZER) { \
		int rv = pthread_mutex_init(mutex, NULL); \
		if (rv != 0) \
			return rv; \
	}

/*  Locking and Unlocking a Mutex, P1003.1c/Draft 10, p. 93
    NOTE: P1003.4b/D8 adds pthread_mutex_timedlock(), p. 29 */

int pthread_mutex_lock(pthread_mutex_t *mutex) {
	assert( mutex );

	CHK_AND_CREATE;

	mutex_lock(*mutex);

#if MUTEX_DEBUG == 1
	printf("locked %08x\n", mutex);
#endif

	return 0;
}

int pthread_mutex_trylock(pthread_mutex_t *mutex) {
	assert( mutex );

	CHK_AND_CREATE;

	if (mutex_trylock(*mutex) < 0) {
		if (errno == EAGAIN)
			return EBUSY;
		else
			return EINVAL;
	}

	return 0;
}

int pthread_mutex_unlock(pthread_mutex_t *mutex) {
	assert( mutex );

	CHK_AND_CREATE;

	mutex_unlock(*mutex);

#if MUTEX_DEBUG == 1
	printf("locked %08x\n", mutex);
#endif

	return 0;
}

/* Mutex Initialization Scheduling Attributes, P1003.1c/Draft 10, p. 128 */

int pthread_mutexattr_setprotocol(pthread_mutexattr_t *attr, int protocol) {
	return 0;
}

int pthread_mutexattr_getprotocol(const pthread_mutexattr_t *attr, int *protocol) {
	return EINVAL;
}

int pthread_mutexattr_setprioceiling(pthread_mutexattr_t *attr, int prioceiling) {
	return 0;
}

int pthread_mutexattr_getprioceiling(const pthread_mutexattr_t *attr, int *prioceiling) {
	return EINVAL;
}

/* Change the Priority Ceiling of a Mutex, P1003.1c/Draft 10, p. 131 */

int pthread_mutex_setprioceiling(pthread_mutex_t *mutex, int prioceiling, int *old_ceiling) {
	return 0;
}

int pthread_mutex_getprioceiling(pthread_mutex_t *mutex, int *prioceiling) {
	return EINVAL;
}
