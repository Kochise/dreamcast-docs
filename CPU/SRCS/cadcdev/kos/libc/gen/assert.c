/* KallistiOS ##version##

   assert.c
   (c)2002 Dan Potter

   $Id: assert.c,v 1.5 2002/09/23 23:16:24 bardtx Exp $
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef FRAME_POINTERS
#include <arch/stack.h>
#endif

CVSID("$Id: assert.c,v 1.5 2002/09/23 23:16:24 bardtx Exp $");

/* The default assert handler */
static void assert_handler_default(const char *file, int line, const char *expr,
	const char *msg, const char *func)
{
	dbglog(DBG_CRITICAL, "\n*** ASSERTION FAILURE ***\n");
	if (msg == NULL)
		dbglog(DBG_CRITICAL, "Assertion \"%s\" failed at %s:%d in `%s'\n\n",
			expr, file, line, func);
	else
		dbglog(DBG_CRITICAL, "Assertion \"%s\" failed at %s:%d in `%s': %s\n\n",
			expr, file, line, func, msg);
#ifdef FRAME_POINTERS
	arch_stk_trace(2);
#endif
	abort();
	/* NOT REACHED */
}

/* The active assert handler */
static assert_handler_t a_hnd = assert_handler_default;

/* Set a new handler */
assert_handler_t assert_set_handler(assert_handler_t hnd) {
	assert_handler_t rv = a_hnd;
	a_hnd = hnd;
	return rv;
}

void __assert(const char *file, int line, const char *expr, const char *msg, const char *func) {
	if (a_hnd != NULL)
		a_hnd(file, line, expr, msg, func);
}

