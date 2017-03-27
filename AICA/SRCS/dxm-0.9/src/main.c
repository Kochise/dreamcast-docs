/* main.c - main routines */

#include "types.h"
#include "dxm.h"

/* extern prototypes */
extern void hw_init(void);

/* prototypes */
void init_xm(uint32);
void play_xm(void);

static const char id[] __attribute__ ((section (".text"))) =
	"dxm $Id: main.c,v 1.1.1.1 2001/09/08 10:48:15 ejstans Exp $";


/* this should of course be in soundRAM */
static XM_INFO *xm_info = (XM_INFO *)XM_INFO_ADDR;

extern sint32 FIQ_div;		/* divisor for irq counter to get proper
				   tick rate */
extern uint32 counter;		/* interrupt counter */

/* keep gcc from complaining */
void
atexit()
{
}

/* main */
int
main()
{

	/* initialize voice channels */
	hw_init();

	/* initialize variables */
	init_xm(0);

	/* inform SH4 that initialization is done */
	xm_info->done = 1;

	/* main-loop */
	while (1) {
		if ((counter % FIQ_div) == 0) {
			play_xm();
		}
	}

}
