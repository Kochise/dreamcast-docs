#include <pthread.h>
#include <errno.h>
#include <assert.h>

/* Thread Creation, P1003.1c/Draft 10, p. 144 */

int pthread_create(pthread_t *thread, const pthread_attr_t  *attr,
	void *(*start_routine)( void * ), void *arg)
{
	kthread_t * nt;

	assert( thread );
	assert( start_routine );

	nt = thd_create( (void (*)(void *))start_routine, arg );
	if (nt) {
		*thread = nt;
		return 0;
	} else {
		return EAGAIN;
	}
}

/* Wait for Thread Termination, P1003.1c/Draft 10, p. 147 */

int pthread_join(pthread_t thread, void **value_ptr) {
	assert( thread );

	// XXX Need to get return value if value_ptr != NULL.
	if (thd_wait(thread) < 0)
		return ESRCH;
	else
		return 0;
}

/* Detaching a Thread, P1003.1c/Draft 10, p. 149 */

int pthread_detach(pthread_t thread) {
	// Currently meaningless.
	return 0;
}

/* Thread Termination, p1003.1c/Draft 10, p. 150 */

void pthread_exit(void *value_ptr) {
	// XXX Need to get return value.
	thd_exit();
}

/* Get Calling Thread's ID, p1003.1c/Draft 10, p. XXX */

pthread_t pthread_self(void) {
	return thd_current;
}

/* Compare Thread IDs, p1003.1c/Draft 10, p. 153 */

int pthread_equal(pthread_t t1, pthread_t t2) {
	return t1 == t2;
}
