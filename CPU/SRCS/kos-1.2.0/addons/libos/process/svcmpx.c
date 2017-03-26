/* KallistiOS 1.2.0

   svcmpx.c
   (c)2000-2001 Dan Potter
*/

#include <malloc.h>
#include <string.h>
#include <kos/thread.h>
#include <arch/spinlock.h>
#include <os/process.h>
#include <os/svcmpx.h>

CVSID("$Id: svcmpx.c,v 1.2 2002/01/06 00:40:33 bardtx Exp $");

/*

This module manages service multiplexing. This is the method by which loaded
programs can find kernel entry points for various services. It is also the
means by which one replaces kernel functionality (as seen from "user land")
with some patch.

Each service is associated with a name token that is expected to resolve to
a pointer to a structure whose first members never change in subsequent
compatible versions. If the members do change, then a major version increase
needs to happen to alert a program of potential problems.

*/

static spinlock_t mutex;

typedef struct svc_handler_str {
	char		name[MAX_SVC_LEN];
	void		*svc_struct;
	struct svc_handler_str *next;
} svc_handler_t;

static svc_handler_t *svc_handlers;
static int mpx_enabled = 0;

/* The handler itself; all this does is search the linked list for the named
   service and return the matching service structure. */
void* svcmpx_get_handler(const char *svcname) {
	svc_handler_t	*cur;
	void		*rv;

	rv = NULL;
	
	spinlock_lock(&mutex);
	cur = svc_handlers;
	while (cur != NULL) {
		if (!strcmp(cur->name, svcname)) {
			rv = cur->svc_struct;
			break;
		}
		cur = cur->next;
	}
	spinlock_unlock(&mutex);
	
	return rv;
}

/* Adds a new service handler (replacing any previous handler) */
int svcmpx_add_handler(const char *name, void *svc_struct) {
	svc_handler_t	*cur;

	if (!mpx_enabled) return -1;

	spinlock_lock(&mutex);

	cur = svc_handlers;
	while (cur != NULL) {
		if (!strcmp(cur->name, name)) break;
		cur = cur->next;
	}
	
	if (cur == NULL) {
		cur = malloc(sizeof(svc_handler_t));
		cur->next = svc_handlers;
		strcpy(cur->name, name);
		svc_handlers = cur;
	}
	cur->svc_struct = svc_struct;

	spinlock_unlock(&mutex);
	
	return 0;
}

/* Removes the handler of the given name (if any) */
int svcmpx_remove_handler(const char *name) {
	svc_handler_t *cur, *last;
	int rv;

	if (!mpx_enabled) return -1;

	last = NULL;
	rv = 0;

	spinlock_lock(&mutex);
	cur = svc_handlers;
	while (cur != NULL) {
		if (!strcmp(cur->name, name)) break;
		cur = cur->next;
	}
	
	if (cur == NULL)
		rv = -1;
	else {
		if (last == NULL) {
			last = svc_handlers->next;
			free(svc_handlers);
			svc_handlers = last;
		} else {
			last->next = cur->next;
			free(cur);
		}
	}
	
	spinlock_unlock(&mutex);
	
	return rv;
}

/* Returns 1 if the svcmpx module is active */
int svcmpx_enabled() {
	return mpx_enabled;
}

/* add a service for this modules:  this allows userland progs to
   add services and so forth */
#include <os/abi/svcmpx.h>
static abi_svcmpx_t sabi;
static void svcmpx_svc_init() {
	memset(&sabi, 0, sizeof(sabi));

	sabi.hdr.version = ABI_MAKE_VER(1, 0, 0);

	sabi.get_handler = svcmpx_get_handler;
	sabi.add_handler = svcmpx_add_handler;
	sabi.remove_handler = svcmpx_remove_handler;

	svcmpx_add_handler("svcmpx", &sabi);
}

int services_init();
int svcmpx_init() {
	/* Start with no handlers */
	svc_handlers = NULL;
	
	/* Init thread mutex */
	spinlock_init(&mutex);

	/* Install our handler */
	ps_set_multiplexer(svcmpx_get_handler);

	/* Set enable flag */
	mpx_enabled = 1;

	/* register the functions in this module as a service */
	svcmpx_svc_init();

	/* Initialize other KOS services */
	services_init();
	
	return 0;
}

void svcmpx_shutdown() {
	svc_handler_t *cur, *tmp;

	/* get rid of this handler for this module */
	svcmpx_remove_handler("svcmpx");

	/* Unset enable flag */
	mpx_enabled = 0;

	/* Put back the default handler */
	ps_set_multiplexer(svcmpx_get_handler);
	
	/* Free any handler blocks */
	cur = svc_handlers;
	while (cur != NULL) {
		tmp = cur;
		cur = cur->next;
		free(tmp);
	}
}





