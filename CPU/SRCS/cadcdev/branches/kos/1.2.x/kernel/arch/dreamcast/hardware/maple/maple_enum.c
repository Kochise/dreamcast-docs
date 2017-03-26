/* KallistiOS ##version##

   maple_enum.c
   (c)2002 Dan Potter
 */

#include <dc/maple.h>
#include <kos/thread.h>

CVSID("$Id: maple_enum.c,v 1.2 2002/05/18 07:11:24 bardtx Exp $");

/* Return the number of connected devices */
int maple_enum_count() {
	int p, u, cnt;

	for (cnt=0, p=0; p<MAPLE_PORT_COUNT; p++)
		for (u=0; u<MAPLE_UNIT_COUNT; u++) {
			if (maple_state.ports[p].units[u].valid)
				cnt++;
		}

	return cnt;
}

/* Return a raw device info struct for the given device */
maple_device_t * maple_enum_dev(int p, int u) {
	if (maple_dev_valid(p, u))
		return &maple_state.ports[p].units[u];
	else
		return NULL;
}

/* Return the Nth device of the requested type (where N is zero-indexed) */
maple_device_t * maple_enum_type(int n, uint32 func) {
	int p, u;
	maple_device_t *dev;

	for (p=0; p<MAPLE_PORT_COUNT; p++) {
		for (u=0; u<MAPLE_UNIT_COUNT; u++) {
			dev = maple_enum_dev(p, u);
			if (dev != NULL && dev->info.functions & func) {
				if (!n) return dev;
				n--;
			}
		}
	}

	return NULL;
}

/* Get the status struct for the requested maple device; wait until it's
   valid before returning. Cast to the appropriate type you're expecting. */
void * maple_dev_status(maple_device_t *dev) {
	/* Is the device valid? */
	if (!dev->valid)
		return NULL;

	/* Waits until the first DMA happens: crude but effective (replace me later) */
	while (!dev->status_valid)
		thd_pass();

	/* Cast and return the status buffer */
	return (void *)(dev->status);
}

