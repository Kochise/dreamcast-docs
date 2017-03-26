/* KallistiOS ##version##

   kernel/arch/dreamcast/hardware/vblank.c
   Copyright (C)2003 Dan Potter
*/

#include <malloc.h>
#include <errno.h>
#include <sys/queue.h>

#include <arch/irq.h>
#include <dc/vblank.h>
#include <kos/process.h>

CVSID("$Id: vblank.c,v 1.2 2003/07/31 00:42:00 bardtx Exp $");

/*
   Functions to multiplex the vblank IRQ out to N client routines.
   This module is necessary because a number of things need to hang
   off the vblank IRQ, and chaining is unreliable.
*/

/* Our list of handlers */
struct vblhnd {
	TAILQ_ENTRY(vblhnd)	listent;
	int			id;
	asic_evt_handler	handler;
	kprocess_t		* owner;
};
static TAILQ_HEAD(vhlist, vblhnd) vblhnds;
static int vblid_high;

/* Our internal IRQ handler */
static void vblank_handler(uint32 src) {
	struct vblhnd * t;

	TAILQ_FOREACH(t, &vblhnds, listent) {
		t->handler(src);
	}
}

int _vblank_handler_add(kprocess_t * proc, asic_evt_handler hnd) {
	struct vblhnd * vh;
	int old;

	vh = malloc(sizeof(struct vblhnd));
	if (!vh) {
		errno = ENOMEM;
		return -1;
	}

	/* Disable ints just in case */
	old = irq_disable();

	/* Find a new ID */
	vh->id = vblid_high; vblid_high++;

	/* Finish filling the struct */
	vh->handler = hnd;
	vh->owner = proc;

	/* Add it to the list */
	TAILQ_INSERT_TAIL(&vblhnds, vh, listent);

	/* Restore ints */
	irq_restore(old);

	return vh->id;
}

int vblank_handler_remove(int handle) {
	struct vblhnd * t;
	int old, rv;

	/* Disable ints just in case */
	old = irq_disable();

	/* Look for it */
	rv = -1;
	TAILQ_FOREACH(t, &vblhnds, listent) {
		if (t->id == handle) {
			TAILQ_REMOVE(&vblhnds, t, listent);
			free(t);
			rv = 0;
			break;
		}
	}

	/* Restore ints */
	irq_restore(old);

	return rv;
}

int vblank_remove_process(struct kprocess * proc) {
	struct vblhnd * t, * tn;
	int old;

	/* Disable ints just in case */
	old = irq_disable();

	t = TAILQ_FIRST(&vblhnds);
	while (t) {
		tn = TAILQ_NEXT(t, listent);
		if (tn->owner == proc) {
			TAILQ_REMOVE(&vblhnds, t, listent);
			free(t);
		}
		t = tn;
	}

	/* Restore ints */
	irq_restore(old);

	return 0;
}

int vblank_init() {
	/* Setup our data structures */
	TAILQ_INIT(&vblhnds);
	vblid_high = 1;

	/* Hook and enable the interrupt */
	asic_evt_set_handler(ASIC_EVT_PVR_VBLINT, vblank_handler);
	asic_evt_enable(ASIC_EVT_PVR_VBLINT, ASIC_IRQ_DEFAULT);

	return 0;
}

int vblank_shutdown() {
	struct vblhnd * c, * n;

	/* Disable and unhook the interrupt */
	asic_evt_disable(ASIC_EVT_PVR_VBLINT, ASIC_IRQ_DEFAULT);
	asic_evt_set_handler(ASIC_EVT_PVR_VBLINT, NULL);

	/* Free any allocated handlers */
	c = TAILQ_FIRST(&vblhnds);
	while (c != NULL) {
		n = TAILQ_NEXT(c, listent);
		free(c);
		c = n;
	}
	TAILQ_INIT(&vblhnds);

	return 0;
}


