#include <pthread.h>
#include <errno.h>

/* Dynamic Package Initialization */
int pthread_once(pthread_once_t *once_control, void (*init_routine)(void)) {
	return EINVAL;
}

/* Thread-Specific Data Key Create, P1003.1c/Draft 10, p. 163 */

int pthread_key_create(pthread_key_t *key, void (*destructor)( void * )) {
	return EINVAL;
}

/* Thread-Specific Data Management, P1003.1c/Draft 10, p. 165 */   

int pthread_setspecific(pthread_key_t key, const void *value) {
	return EINVAL;
}

void * pthread_getspecific(pthread_key_t key) {
	return NULL;
}

/* Thread-Specific Data Key Deletion, P1003.1c/Draft 10, p. 167 */

int pthread_key_delete(pthread_key_t key) {
	return EINVAL;
}
