/* KallistiOS ##version##

   pvr_irq.c
   (C)2002 Dan Potter

 */

#include <assert.h>
#include <dc/pvr.h>
#include <dc/video.h>
#include <dc/asic.h>
#include "pvr_internal.h"

/*
   PVR interrupt handler; the way things are setup, we're gonna get
   one of these for each full vertical refresh and at the completion
   of TA data acceptance. The timing here is pretty critical. We need
   to flip pages during a vertical blank, and then signal to the program
   that it's ok to start playing with TA registers again, or we waste
   rendering time.
*/

CVSID("$Id: pvr_irq.c,v 1.10 2003/04/24 03:12:25 bardtx Exp $");

void pvr_int_handler(uint32 code) {
	/* What kind of event did we get? Is it a list completion? */
	switch(code) {
	case ASIC_EVT_PVR_OPAQUEDONE:
		pvr_state.opb_completed |= 1 << PVR_OPB_OP;
		break;
	case ASIC_EVT_PVR_TRANSDONE:
		pvr_state.opb_completed |= 1 << PVR_OPB_TP;
		break;
	case ASIC_EVT_PVR_OPAQUEMODDONE:
		pvr_state.opb_completed |= 1 << PVR_OPB_OM;
		break;
	case ASIC_EVT_PVR_TRANSMODDONE:
		pvr_state.opb_completed |= 1 << PVR_OPB_TM;
		break;
	case ASIC_EVT_PVR_PTDONE:
		pvr_state.opb_completed |= 1 << PVR_OPB_PT;
		break;
	case ASIC_EVT_PVR_RENDERDONE:
		pvr_state.render_completed = 1;
		pvr_sync_stats(PVR_SYNC_RNDDONE);
		break;
	case ASIC_EVT_PVR_VBLINT:
		pvr_sync_stats(PVR_SYNC_VBLANK);
		break;
	}

	/* Update our stats if we finished all registration */
	switch (code) {
	case ASIC_EVT_PVR_OPAQUEDONE:
	case ASIC_EVT_PVR_TRANSDONE:
	case ASIC_EVT_PVR_OPAQUEMODDONE:
	case ASIC_EVT_PVR_TRANSMODDONE:
	case ASIC_EVT_PVR_PTDONE:
		if (pvr_state.opb_completed == pvr_state.opb_completed_full) {
			pvr_sync_stats(PVR_SYNC_REGDONE);
		}
		return;
	}

	/* Vertical blank is happening, all lists are complete, and render is done */
	/* Note: render-done doesn't seem to be reliable */
	if (pvr_state.opb_completed == pvr_state.opb_completed_full
			&& pvr_state.render_completed
			/* && !to_texture */
			&& code == ASIC_EVT_PVR_VBLINT) {
		/* Handle PVR stats */
		pvr_sync_stats(PVR_SYNC_VBLRNDDONE);

		/* Switch view address to the "good" buffer */
		pvr_state.view_page ^= 1;
		pvr_sync_view_page();
		
		/* Finish up rendering the current frame (into the other buffer) */
		pvr_state.render_completed = 0;
		pvr_begin_queued_render();
		
		/* Mark render/flip completion */
		pvr_state.flip_completed = 1;
		sem_signal(pvr_state.ready_sem);
		thd_schedule(1, 0);
		
		/* Clear list completion */
		pvr_state.opb_completed = 0;

		/* Setup registration for the next frame */
		pvr_sync_reg_buffer();
	}
}


