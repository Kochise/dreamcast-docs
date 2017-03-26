/* KallistiOS ##version##

   pvr_scene.c
   (C)2002 Dan Potter

 */

#include <assert.h>
#include <stdio.h>
#include <kos/thread.h>
#include <dc/pvr.h>
#include <dc/sq.h>
#include "pvr_internal.h"

/*

   Scene rendering

   Please see ../../include/dc/pvr.h for more info on this API!
 
*/

CVSID("$Id: pvr_scene.c,v 1.9 2003/03/09 01:19:31 bardtx Exp $");


/* Setup a vertex buffer for one of the list types. If the specified list type
   already has a vertex buffer, it will be replaced by the new one; if NULL
   is specified as a buffer location, the list type will be switched to direct
   mode. The old buffer location will be returned (if any). */
void * pvr_set_vertex_buffer(pvr_list_t list, void * buffer, int len) {
	assert_msg(0, "not implemented yet");
	return NULL;
}

/* Begin collecting data for a frame of 3D output to the off-screen
   frame buffer */
void pvr_scene_begin() {
	/* Get everything setup */
	pvr_state.opb_open_list = -1;
	pvr_state.opb_closed = 0;
	pvr_state.opb_completed = 0;
	pvr_state.flip_completed = 0;

	/* We assume registration is starting immediately */
	pvr_sync_stats(PVR_SYNC_REGSTART);
}

/* Begin collecting data for a frame of 3D output to the specified texture;
   pass in the size of the buffer in rx and ry, and the return values in
   rx and ry will be the size actually used (if changed). Note that
   currently this only supports screen-sized output! */
void pvr_scene_begin_txr(pvr_ptr_t txr, uint32 *rx, uint32 *ry) {
	assert_msg(0, "not implemented yet");
}

/* Begin collecting data for the given list type. Lists do not have to be
   submitted in any particular order, but all types of a list must be 
   submitted at once. If the given list has already been closed, then an
   error (-1) is returned. */
int pvr_list_begin(pvr_list_t list) {
	/* Check to make sure we can do this */
#ifndef NDEBUG
	if (pvr_state.opb_closed & (1 << list)) {
		dbglog(DBG_WARNING, "pvr_list_begin: attempt to open already closed list\n");
		return -1;
	}
#endif	/* !NDEBUG */

	/* If we already had a list open, close it first */
	if (pvr_state.opb_open_list != -1) {
		pvr_list_finish();
	}

	/* Ok, set the flag */
	pvr_state.opb_open_list = list;

	/* Start out having not submitted any primitives */
	pvr_state.opb_open_list_cnt = 0;

	return 0;
}

/* End collecting data for the current list type. Lists can never be opened
   again within a single frame once they have been closed. Thus submitting
   a primitive that belongs in a closed list is considered an error. Closing
   a list that is already closed is also an error (-1). Note that if you open
   a list but do not submit any primitives, a blank one will be submitted to
   satisfy the hardware. */
int pvr_list_finish() {
	/* Check to make sure we can do this */
#ifndef NDEBUG
	if (pvr_state.opb_open_list == -1) {
		dbglog(DBG_WARNING, "pvr_list_finish: attempt to close unopened list\n");
		return -1;
	}
#endif	/* !NDEBUG */

	/* If we haven't sent anything in this list, send a dummy */
	if (pvr_state.opb_open_list_cnt == 0) {
		pvr_blank_polyhdr(pvr_state.opb_open_list);
	}
	
	/* Set the flags */
	pvr_state.opb_closed |= (1 << pvr_state.opb_open_list);
	pvr_state.opb_open_list = -1;

	/* Send an EOL marker */
	sq_set32((void *)PVR_TA_INPUT, 0, 32);

	return 0;
}

/* Submit a primitive of the _current_ list type; note that any values
   submitted in this fashion will go directly to the hardware without any
   sort of buffering, and submitting a primitive of the wrong type will
   quite likely ruin your scene. Note that this also will not work if you
   haven't begun any list types (i.e., all data is queued). Returns -1 for
   failure. */
int pvr_prim(void * data, int size) {
	/* Check to make sure we can do this */
#ifndef NDEBUG
	if (pvr_state.opb_open_list == -1) {
		dbglog(DBG_WARNING, "pvr_prim: attempt to submit to unopened list\n");
		return -1;
	}
#endif	/* !NDEBUG */

	/* Add one to the submitted count */
	pvr_state.opb_open_list_cnt++;

	/* Send the data */
	sq_cpy((void *)PVR_TA_INPUT, data, size);
	
	return 0;
}

/* Submit a primitive of the given list type; if the requested list is not
   the current list, then the data will be queued in a vertex buffer if
   available, otherwise it will be submitted directly. If a vertex buffer
   doesn't exist when one is needed, an error (-1) is returned. */
int pvr_list_prim(pvr_list_t list, void * data, int size) {
	assert_msg(0, "not implemented yet");
	return -1;
}

/* Called to flush buffered data of the given list type to the hardware
   processor. If there is no vertex buffer for the given type, then an error
   (-1) is returned. The list must have been started with pvr_begin_list(). */
int pvr_list_flush(pvr_list_t list) {
	assert_msg(0, "not implemented yet");
	return -1;
}

/* Call this after you have finished submitting all data for a frame; once
   this has been called, you can not submit any more data until one of the
   pvr_scene_begin() functions is called again. An error (-1) is returned if
   you have not started a scene already. */
int pvr_scene_finish() {
	int i;
	
	/* If a list was open, close it */
	if (pvr_state.opb_open_list != -1)
		pvr_list_finish();

	/* If any lists weren't submitted, then submit blank ones now */
	for (i=0; i<PVR_OPB_COUNT; i++) {
		if ( (pvr_state.opb_completed_full & (1 << i))
				&& (!( pvr_state.opb_closed & (1 << i) )) ) {
			pvr_list_begin(i);
			pvr_blank_polyhdr(i);
			pvr_list_finish();
		}
	}

	/* Ok, now it's just a matter of waiting for the interrupt... */
	return 0;
}

/* Block the caller until the PVR system is ready for another frame to be
   started. The PVR system allocates enough space for two frames: one in
   data collection mode, and another in rendering mode. If a frame is 
   currently rendering, and another frame has already been closed, then the
   caller cannot do anything else until the rendering frame completes. Note
   also that the new frame cannot be activated except during a vertical
   blanking period, so this essentially waits until a rendered frame is
   complete _AND_ a vertical blank happens. Returns -1 if the wait times
   out. Note that once this returns, the PVR system is ready for another
   frame's data to be collected. */
int pvr_wait_ready() {
	int t;

	if (thd_mode == THD_MODE_COOP) {
		t = jiffies + 10;
		while (pvr_state.flip_completed == 0 && (jiffies < t)) {
			thd_pass();
		}
		if (jiffies >= t) {
			dbglog(DBG_WARNING, "pvr_wait_ready: timed out\n");
			return -1;
		} else {
			pvr_state.flip_completed = 0;
		}
	} else {
		t = sem_wait_timed(pvr_state.ready_sem, 100);
		if (t < 0) {
			dbglog(DBG_WARNING, "pvr_wait_ready: timed out\n");
			return -1;
		}

		pvr_state.flip_completed = 0;
	}

	return 0;
}

/* Same thing as above, but in non-blocking form; returns -1 if the PVR isn't
   ready; returns 0 when the PVR has accepted your frame and is ready for
   more. */
int pvr_check_ready() {
	if (pvr_state.flip_completed != 0) {
		pvr_state.flip_completed = 0;
		if (thd_mode != THD_MODE_COOP) {
			assert( sem_count(pvr_state.ready_sem) > 0 );
			sem_wait(pvr_state.ready_sem);
		}
		return 0;
	} else {
		return -1;
	}
}




