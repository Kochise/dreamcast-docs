/* KallistiOS ##version##

   snd_stream.c
   Copyright (c)2000,2001,2002,2003 Dan Potter
   Copyright (c)2002 Florian Schulze

   SH-4 support routines for SPU streaming sound driver
*/

#include <string.h>
#include <stdlib.h>

#include <arch/timer.h>
#include <dc/g2bus.h>
#include <dc/spu.h>
#include <dc/sound/sound.h>
#include <dc/sound/stream.h>

#include "arm/aica_cmd_iface.h"

CVSID("$Id: snd_stream.c,v 1.13 2003/03/09 01:26:37 bardtx Exp $");

/*

This module uses a nice circularly queued data stream in SPU RAM, which is
looped by a program running in the SPU itself.

Basically the poll routine checks to see if a certain minimum amount of
data is available to the SPU to be played, and if not, we ask the user
routine for more sound data and load it up. That's about it.

*/


/* The last write position in the playing buffer */
static int last_write_pos = 0;
static int curbuffer = 0;

/* the address of the sound ram from the SH4 side */
#define SPU_RAM_BASE            0xa0800000

/* buffer size in bytes */
#define BUFFER_SIZE		0x10000

/* Stream data location in AICA RAM */
static uint32			spu_ram_sch1, spu_ram_sch2;

/* Seperation buffers (for stereo) */
static int16 *sep_buffer[2] = { NULL, NULL };

/* "Get data" callback; we'll call this any time we want to get another
   buffer of output data. */
static void* (*str_get_data)(int requested_cnt, int * received_cnt) = NULL;

/* Our list of filter callback functions */
typedef struct filter {
	TAILQ_ENTRY(filter)	lent;
	snd_stream_filter_t	func;
	void			* data;
} filter_t;
TAILQ_HEAD(filterlist, filter) filters;

/* Stereo/mono flag for stream */
static int stereo;

/* Playback frequency */
static int frequency;

/* Stream queueing is where we get everything ready to go but don't
   actually start it playing until the signal (for music sync, etc) */
static int snd_stream_queueing;

/* Have we been initialized yet? (and reserved a buffer, etc) */
static int initted = 0;

/* Set "get data" callback */
void snd_stream_set_callback(void *(*func)(int, int*)) {
	str_get_data = func;
}

void snd_stream_filter_add(snd_stream_filter_t filtfunc, void * obj) {
	filter_t * f;

	f = malloc(sizeof(filter_t));
	f->func = filtfunc;
	f->data = obj;
	TAILQ_INSERT_TAIL(&filters, f, lent);
}

void snd_stream_filter_remove(snd_stream_filter_t filtfunc, void * obj) {
	filter_t * f;

	TAILQ_FOREACH(f, &filters, lent) {
		if (f->func == filtfunc && f->data == obj) {
			TAILQ_REMOVE(&filters, f, lent);
			free(f);
			return;
		}
	}
}

static void process_filters(void **buffer, int *samplecnt) {
	filter_t * f;

	TAILQ_FOREACH(f, &filters, lent) {
		f->func(f->data, frequency, stereo ? 2 : 1, buffer, samplecnt);
	}
}


/* Performs stereo seperation for the two channels; this routine
   has been optimized for the SH-4. */
static void sep_data(void *buffer, int len) {
	register int16	*bufsrc, *bufdst;
	register int	x, y, cnt;

	if (stereo) {
		bufsrc = (int16*)buffer;
		bufdst = sep_buffer[0];
		x = 0; y = 0; cnt = len / 2;
		do {
			*bufdst = *bufsrc;
			bufdst++; bufsrc+=2; cnt--;
		} while (cnt > 0);

		bufsrc = (int16*)buffer; bufsrc++;
		bufdst = sep_buffer[1];
		x = 1; y = 0; cnt = len / 2;
		do {
			*bufdst = *bufsrc;
			bufdst++; bufsrc+=2; cnt--;
			x+=2; y++;
		} while (cnt > 0);
	} else {
		memcpy(sep_buffer[0], buffer, len);
		memcpy(sep_buffer[1], buffer, len);
	}
}

/* Prefill buffers -- do this before calling start() */
void snd_stream_prefill() {
	void *buf;
	int got;

	if (!str_get_data) return;

	/* Load first buffer */
	/* XXX Note: This will not work if the full data size is less than
	   BUFFER_SIZE or BUFFER_SIZE/2. */
	if (stereo)
		buf = str_get_data(BUFFER_SIZE, &got);
	else
		buf = str_get_data((BUFFER_SIZE/2), &got);
	process_filters(&buf, &got);
	sep_data(buf, (BUFFER_SIZE/2));
	spu_memload(spu_ram_sch1 + (BUFFER_SIZE/2)*0, (uint8*)sep_buffer[0], (BUFFER_SIZE/2));
	spu_memload(spu_ram_sch2 + (BUFFER_SIZE/2)*0, (uint8*)sep_buffer[1], (BUFFER_SIZE/2));

	/* Load second buffer */
	if (stereo)
		buf = str_get_data(BUFFER_SIZE, &got);
	else
		buf = str_get_data((BUFFER_SIZE/2), &got);
	process_filters(&buf, &got);
	sep_data(buf, (BUFFER_SIZE/2));
	spu_memload(spu_ram_sch1 + (BUFFER_SIZE/2)*1, (uint8*)sep_buffer[0], (BUFFER_SIZE/2));
	spu_memload(spu_ram_sch2 + (BUFFER_SIZE/2)*1, (uint8*)sep_buffer[1], (BUFFER_SIZE/2));

	/* Start with playing on buffer 0 */
	last_write_pos = 0;
	curbuffer = 0;
}

/* Initialize stream system */
int snd_stream_init(void* (*callback)(int, int *)) {
	/* Start off with queueing disabled */
	snd_stream_queueing = 0;
	
	/* Setup the callback */
	snd_stream_set_callback(callback);

	if (initted)
		return 0;

	/* Initialize our filter chain list */
	TAILQ_INIT(&filters);

	/* Create stereo seperation buffers */
	if (!sep_buffer[0]) {
		sep_buffer[0] = memalign(32, (BUFFER_SIZE/2));
		sep_buffer[1] = memalign(32, (BUFFER_SIZE/2));
	}

	/* Finish loading the stream driver */
	if (snd_init() < 0) {
		dbglog(DBG_ERROR, "snd_stream_init(): snd_init() failed, giving up\n");
		return -1;
	}

	spu_ram_sch1 = snd_mem_malloc(BUFFER_SIZE*2);
	spu_ram_sch2 = spu_ram_sch1 + BUFFER_SIZE;

	initted = 1;

	return 0;
}

/* Shut everything down and free mem */
void snd_stream_shutdown() {
	filter_t * c, * n;

	if (!initted)
		return;

	c = TAILQ_FIRST(&filters);
	while (c) {
		n = TAILQ_NEXT(c, lent);
		free(c);
		c = n;
	}
	TAILQ_INIT(&filters);

	snd_stream_stop();
	if (sep_buffer[0]) {
		free(sep_buffer[0]);	sep_buffer[0] = NULL;
		free(sep_buffer[1]);	sep_buffer[1] = NULL;
	}
	snd_mem_free(spu_ram_sch1);
	initted = 0;
}

/* Enable / disable stream queueing */
void snd_stream_queue_enable() {
	snd_stream_queueing = 1;
}

void snd_stream_queue_disable() {
	snd_stream_queueing = 0;
}

/* Start streaming (or if queueing is enabled, just get ready) */
void snd_stream_start(uint32 freq, int st) {
	AICA_CMDSTR_CHANNEL(tmp, cmd, chan);
	
	if (!str_get_data) return;

	stereo = st;
	frequency = freq;

	/* Make sure these are sync'd (and/or delayed) */
	snd_sh4_to_aica_stop();
	
	/* Prefill buffers */
	snd_stream_prefill();

	/* Channel 0 */
	cmd->cmd = AICA_CMD_CHAN;
	cmd->timestamp = 0;
	cmd->size = AICA_CMDSTR_CHANNEL_SIZE;
	cmd->cmd_id = 0;
	chan->cmd = AICA_CH_CMD_START;
	chan->base = spu_ram_sch1;
	chan->type = AICA_SM_16BIT;
	chan->length = (BUFFER_SIZE/2);
	chan->loop = 1;
	chan->loopstart = 0;
	chan->loopend = (BUFFER_SIZE/2);
	chan->freq = freq;
	chan->vol = 240;
	chan->pan = 0;
	snd_sh4_to_aica(tmp, cmd->size);

	/* Channel 1 */
	cmd->cmd_id = 1;
	chan->base = spu_ram_sch2;
	chan->pan = 255;
	snd_sh4_to_aica(tmp, cmd->size);

	/* Process the changes */
	if (!snd_stream_queueing)
		snd_sh4_to_aica_start();
}

/* Actually make it go (in queued mode) */
void snd_stream_queue_go() {
	snd_sh4_to_aica_start();
}

/* Stop streaming */
void snd_stream_stop() {
	AICA_CMDSTR_CHANNEL(tmp, cmd, chan);
	
	if (!str_get_data) return;

	/* Stop stream */
	/* Channel 0 */
	cmd->cmd = AICA_CMD_CHAN;
	cmd->timestamp = 0;
	cmd->size = AICA_CMDSTR_CHANNEL_SIZE;
	cmd->cmd_id = 0;
	chan->cmd = AICA_CH_CMD_STOP;
	snd_sh4_to_aica(tmp, cmd->size);

	/* Channel 1 */
	cmd->cmd_id = 1;
	snd_sh4_to_aica(tmp, AICA_CMDSTR_CHANNEL_SIZE);
}

/* Poll streamer to load more data if neccessary */
int snd_stream_poll() {
	uint32		ch0pos, ch1pos;
	int		realbuffer;
	int		current_play_pos;
	int		needed_samples;
	int		got_samples;
	void		*data;

	if (!str_get_data) return -1;

	/* Get "real" buffer */
	ch0pos = g2_read_32(SPU_RAM_BASE + AICA_CHANNEL(0) + offsetof(aica_channel_t, pos));
	ch1pos = g2_read_32(SPU_RAM_BASE + AICA_CHANNEL(1) + offsetof(aica_channel_t, pos));

	if (ch0pos >= (BUFFER_SIZE/2)) {
		dbglog(DBG_ERROR, "snd_stream_poll: chan0.pos = %ld (%08lx)\n", ch0pos, ch0pos);
		return -1;
	}
	
	realbuffer = !((ch0pos < (BUFFER_SIZE/4)) && (ch1pos < (BUFFER_SIZE/4)));

	current_play_pos = (ch0pos < ch1pos)?(ch0pos):(ch1pos);

	/* count just till the end of the buffer, so we don't have to
	   handle buffer wraps */
	if (last_write_pos <= current_play_pos)
		needed_samples = current_play_pos - last_write_pos;
	else
		needed_samples = (BUFFER_SIZE/2) - last_write_pos;
	/* round it a little bit */
	needed_samples &= ~0x7ff;
	/* printf("last_write_pos %6i, current_play_pos %6i, needed_samples %6i\n",last_write_pos,current_play_pos,needed_samples); */

	if (needed_samples > 0) {
		if (stereo) {
			data = str_get_data(needed_samples * 4, &got_samples);
			process_filters(&data, &got_samples);
			if (got_samples < needed_samples * 4) {
				needed_samples = got_samples / 4;
				if (needed_samples & 3)
					needed_samples = (needed_samples + 4) & ~3;
			}
		} else {
			data = str_get_data(needed_samples * 2, &got_samples);
			process_filters(&data, &got_samples);
			if (got_samples < needed_samples * 2) {
				needed_samples = got_samples / 2;
				if (needed_samples & 1)
					needed_samples = (needed_samples + 2) & ~1;
			}
		}
		if (data == NULL) {
			/* Fill the "other" buffer with zeros */
			spu_memset(spu_ram_sch1 + (last_write_pos * 2), 0, needed_samples * 2);
			spu_memset(spu_ram_sch2 + (last_write_pos * 2), 0, needed_samples * 2);
			return -3;
		}

		sep_data(data, needed_samples * 2);
		spu_memload(spu_ram_sch1 + (last_write_pos * 2), (uint8*)sep_buffer[0], needed_samples * 2);
		spu_memload(spu_ram_sch2 + (last_write_pos * 2), (uint8*)sep_buffer[1], needed_samples * 2);

		last_write_pos += needed_samples;
		if (last_write_pos >= (BUFFER_SIZE/2))
			last_write_pos -= (BUFFER_SIZE/2);
	}
	return 0;
}

/* Set the volume on the streaming channels */
void snd_stream_volume(int vol) {
	AICA_CMDSTR_CHANNEL(tmp, cmd, chan);

	cmd->cmd = AICA_CMD_CHAN;
	cmd->timestamp = 0;
	cmd->size = AICA_CMDSTR_CHANNEL_SIZE;
	cmd->cmd_id = 0;
	chan->cmd = AICA_CH_CMD_UPDATE | AICA_CH_UPDATE_SET_VOL;
	chan->vol = vol;
	snd_sh4_to_aica(tmp, cmd->size);

	cmd->cmd_id = 1;
	snd_sh4_to_aica(tmp, cmd->size);
}


