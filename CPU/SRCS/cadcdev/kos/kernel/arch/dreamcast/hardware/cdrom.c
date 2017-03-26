/* KallistiOS ##version##

   cdrom.c

   (c)2000 Dan Potter

 */

#include <dc/cdrom.h>
#include <kos/thread.h>
#include <kos/mutex.h>

CVSID("$Id: cdrom.c,v 1.8 2003/04/24 03:25:27 bardtx Exp $");

/*

This module contains low-level primitives for accessing the CD-Rom (I
refer to it as a CD-Rom and not a GD-Rom, because this code will not
access the GD area, by design). Whenever a file is accessed and a new
disc is inserted, it reads the TOC for the disc in the drive and
gets everything situated. After that it will read raw sectors from 
the data track on a standard DC bootable CDR (one audio track plus
one data track in xa1 format).

Most of the information/algorithms in this file are thanks to
Marcus Comstedt. Thanks to Maiwe for the verbose command names and
also for the CDDA playback routines.

Note that these functions may be affected by changing compiler options...
they require their parameters to be in certain registers, which is 
normally the case with the default options. If in doubt, decompile the
output and look to make sure.

*/


/* GD-Rom BIOS calls... named mostly after Marcus' code. None have more
   than two parameters; R7 (fourth parameter) needs to describe
   which syscall we want. */

#define MAKE_SYSCALL(rs, p1, p2, idx) \
	uint32 *syscall_bc = (uint32*)0x8c0000bc; \
	int (*syscall)() = (int (*)())(*syscall_bc); \
	rs syscall((p1), (p2), 0, (idx));

/* Reset system functions */
static void gdc_init_system() {	MAKE_SYSCALL(/**/, 0, 0, 3); }

/* Submit a command to the system */
static int gdc_req_cmd(int cmd, void *param) { MAKE_SYSCALL(return, cmd, param, 0); }

/* Check status on an executed command */
static int gdc_get_cmd_stat(int f, void *status) { MAKE_SYSCALL(return, f, status, 1); }

/* Execute submitted commands */
static void gdc_exec_server() { MAKE_SYSCALL(/**/, 0, 0, 2); }

/* Check drive status and get disc type */
static int gdc_get_drv_stat(void *param) { MAKE_SYSCALL(return, param, 0, 4); }

/* Set disc access mode */
static int gdc_change_data_type(void *param) { MAKE_SYSCALL(return, param, 0, 10); }


/* The CD access mutex */
static mutex_t * mutex = NULL;

/* Command execution sequence */
int cdrom_exec_cmd(int cmd, void *param) {
	int status[4] = {0};
	int f, n;

	/* Submit the command and wait for it to finish */
	f = gdc_req_cmd(cmd, param);
	do {
		gdc_exec_server();
		n = gdc_get_cmd_stat(f, status);
		if (n == 1)
			thd_pass();
	} while (n == 1);

	if (n == 2)
		return ERR_OK;
	else {
		switch(status[0]) {
			case 2: return ERR_NO_DISC;
			case 6: return ERR_DISC_CHG;
			default:
				return ERR_SYS;
		}
	}
}

/* Return the status of the drive as two integers (see constants) */
int cdrom_get_status(int *status, int *disc_type) {
	int 	rv = ERR_OK;
	uint32	params[2];

	/* We might be called in an interrupt to check for ISO cache
	   flushing, so make sure we're not interrupting something
	   already in progress. */
	if (irq_inside_int()) {
		if (mutex_is_locked(mutex))
			return -1;
	} else {
		mutex_lock(mutex);
	}

	rv = gdc_get_drv_stat(params);
	if (rv >= 0) {
		if (status != NULL)
			*status = params[0];
		if (disc_type != NULL)
			*disc_type = params[1];
	} else {
		if (status != NULL)
			*status = -1;
		if (disc_type != NULL)
			*disc_type = -1;
	}

	if (!irq_inside_int())
		mutex_unlock(mutex);

	return rv;
}

/* Re-init the drive, e.g., after a disc change, etc */
int cdrom_reinit() {
	int	rv = ERR_OK;
	int	r = -1, cdxa;
	uint32	params[4];
	int	timeout;

	mutex_lock(mutex);

	/* Try a few times; it might be busy. If it's still busy
	   after this loop then it's probably really dead. */
	timeout = 10*1000/20;	/* 10 second timeout */
	while (timeout > 0) {
		r = cdrom_exec_cmd(CMD_INIT, NULL);
		if (r == 0) break;
		if (r == ERR_NO_DISC) {
			rv = r;
			goto exit;
		} else if (r == ERR_SYS) {
			rv = r;
			goto exit;
		}

		/* Still trying.. sleep a bit and check again */
		thd_sleep(20);
		timeout--;
	}
	if (timeout <= 0) {
		rv = r;
		goto exit;
	}

	/* Check disc type and set parameters */
	gdc_get_drv_stat(params);
	cdxa = params[1] == 32;
	params[0] = 0;				/* 0 = set, 1 = get */
	params[1] = 8192;			/* ? */
	params[2] = cdxa ? 2048 : 1024;		/* CD-XA mode 1/2 */
	params[3] = 2048;			/* sector size */
	if (gdc_change_data_type(params) < 0) { rv = ERR_SYS; goto exit; }

exit:
	mutex_unlock(mutex);
	return rv;
}

/* Read the table of contents */
int cdrom_read_toc(CDROM_TOC *toc_buffer, int session) {
	struct {
		int	session;
		void	*buffer;
	} params;
	int rv;
	
	mutex_lock(mutex);
	
	params.session = session;
	params.buffer = toc_buffer;
	rv = cdrom_exec_cmd(CMD_GETTOC2, &params);
	
	mutex_unlock(mutex);
	return rv;
}

/* Read one or more sectors */
int cdrom_read_sectors(void *buffer, int sector, int cnt) {
	struct {
		int	sec, num;
		void	*buffer;
		int	dunno;
	} params;
	int rv;

	mutex_lock(mutex);
	
	params.sec = sector;	/* Starting sector */
	params.num = cnt;	/* Number of sectors */
	params.buffer = buffer;	/* Output buffer */
	params.dunno = 0;	/* ? */
	rv = cdrom_exec_cmd(CMD_PIOREAD, &params);
	
	mutex_unlock(mutex);
	return rv;
}

/* Locate the LBA sector of the data track; use after reading TOC */
uint32 cdrom_locate_data_track(CDROM_TOC *toc) {
	int i, first, last;
	
	first = TOC_TRACK(toc->first);
	last = TOC_TRACK(toc->last);
	
	if (first < 1 || last > 99 || first > last)
		return 0;
	
	/* Find the last track which as a CTRL of 4 */
	for (i=last; i>=first; i--) {
		if (TOC_CTRL(toc->entry[i - 1]) == 4)
			return TOC_LBA(toc->entry[i - 1]);
	}
	
	return 0;
}

/* Play CDDA tracks
   start  -- track to play from
   end    -- track to play to
   repeat -- number of times to repeat (0-15, 15=infinite)
   mode   -- CDDA_TRACKS or CDDA_SECTORS
 */
int cdrom_cdda_play(uint32 start, uint32 end, uint32 repeat, int mode) {
	struct {
		int start;
		int end;
		int repeat;
	} params;
	int rv;

	/* Limit to 0-15 */
	if (repeat > 15)
		repeat = 15;

	params.start = start;
	params.end = end;
	params.repeat = repeat;

	mutex_lock(mutex);
	if (mode == CDDA_TRACKS)
		rv = cdrom_exec_cmd(CMD_PLAY, &params);
	else
		rv = cdrom_exec_cmd(CMD_PLAY2, &params);
	mutex_unlock(mutex);

	return rv;
}

/* Pause CDDA audio playback */
int cdrom_cdda_pause() {
	int rv;

	mutex_lock(mutex);
	rv = cdrom_exec_cmd(CMD_PAUSE, NULL);
	mutex_unlock(mutex);

	return rv;
}

/* Resume CDDA audio playback */
int cdrom_cdda_resume() {
	int rv;

	mutex_lock(mutex);
	rv = cdrom_exec_cmd(CMD_RELEASE, NULL);
	mutex_unlock(mutex);

	return rv;
}

/* Spin down the CD */
int cdrom_spin_down() {
	int rv;

	mutex_lock(mutex);
	rv = cdrom_exec_cmd(CMD_STOP, NULL);
	mutex_unlock(mutex);

	return rv;
}

/* Initialize: assume no threading issues */
int cdrom_init() {
	uint32 p, x;
	volatile uint32 *react = (uint32*)0xa05f74e4,
		*bios = (uint32*)0xa0000000;

	if (mutex != NULL)
		return -1;

	/* Reactivate drive: send the BIOS size and then read each
	   word across the bus so the controller can verify it. */
	*react = 0x1fffff;
	for (p=0; p<0x200000/4; p++) { x = bios[p]; }

	/* Reset system functions */
	gdc_init_system();

	/* Initialize mutex */
	mutex = mutex_create();

	/* Do an initial initialization */
	cdrom_reinit();
	
	return 0;
}

void cdrom_shutdown() {
	if (mutex == NULL)
		return;
	mutex_destroy(mutex);
	mutex = NULL;
}

