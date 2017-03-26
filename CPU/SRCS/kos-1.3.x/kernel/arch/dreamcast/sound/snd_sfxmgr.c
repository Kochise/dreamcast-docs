/* KallistiOS ##version##

   snd_sfxmgr.c
   (c)2000-2002 Dan Potter

   Sound effects management system; this thing loads and plays sound effects
   during game operation.
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <sys/queue.h>
#include <kos/fs.h>
#include <dc/spu.h>
#include <dc/sound/sound.h>
#include <dc/sound/sfxmgr.h>

#include "arm/aica_cmd_iface.h"

CVSID("$Id: snd_sfxmgr.c,v 1.11 2003/04/24 03:17:08 bardtx Exp $");

struct snd_effect;
LIST_HEAD(selist, snd_effect);

typedef struct snd_effect {
	uint32	locl, locr;
	uint32	len;
	uint32	rate;
	uint32	used;
	int	stereo;
	uint32	fmt;

	LIST_ENTRY(snd_effect)	list;
} snd_effect_t;

struct selist snd_effects;

static int sfx_lastchan = 2;

/* Unload all loaded samples and free their SPU RAM */
void snd_sfx_unload_all() {
	snd_effect_t * t, * n;

	t = LIST_FIRST(&snd_effects);
	while (t) {
		n = LIST_NEXT(t, list);

		snd_mem_free(t->locl);
		if (t->stereo)
			snd_mem_free(t->locr);
		free(t);

		t = n;
	}

	LIST_INIT(&snd_effects);
}

/* Unload a single sample */
void snd_sfx_unload(sfxhnd_t idx) {
	snd_effect_t * t = (snd_effect_t *)idx;

	snd_mem_free(t->locl);
	if (t->stereo)
		snd_mem_free(t->locr);

	LIST_REMOVE(t, list);
	free(t);
}

/* WAV header:
	0x08	-- "WAVE"
	0x14	-- 1 for PCM, 20 for ADPCM
	0x16	-- short num channels (1/2)
	0x18	-- long  HZ
	0x22	-- short 8 or 16 (bits)
	0x28	-- long  data length
	0x2c	-- data start

 */

/* Load a sound effect from a WAV file and return a handle to it */
sfxhnd_t snd_sfx_load(const char *fn) {
	uint32	fd, len, hz;
	uint16	*tmp, chn, bitsize, fmt;
	snd_effect_t *t;
	int	ownmem;

	dbglog(DBG_DEBUG, "snd_sfx: loading effect %s\n", fn);

	fd = fs_open(fn, O_RDONLY);
	if (fd == 0) {
		dbglog(DBG_WARNING, "snd_sfx: can't open sfx %s\n", fn);
		return 0;
	}

	/* Check file magic */
	hz = 0;
	fs_seek(fd, 8, SEEK_SET);
	fs_read(fd, &hz, 4);
	if (strncmp((char*)&hz, "WAVE", 4)) {
		dbglog(DBG_WARNING, "snd_sfx: file is not RIFF WAVE\n");
		fs_close(fd);
		return 0;
	}
	
	
	/* Read WAV header info */
	fs_seek(fd, 0x14, SEEK_SET);
	fs_read(fd, &fmt, 2);
	fs_read(fd, &chn, 2);
	fs_read(fd, &hz, 4);
	fs_seek(fd, 0x22, SEEK_SET);
	fs_read(fd, &bitsize, 2);
	
	/* Read WAV data */
	fs_seek(fd, 0x28, SEEK_SET);
	fs_read(fd, &len, 4);

	printf("WAVE file is %s, %dHZ, %d bits/sample, %d bytes total, format %d\n",
		chn==1 ? "mono" : "stereo", hz, bitsize, len, fmt);

	/* Try to mmap it and if that works, no need to copy it again */
	ownmem = 0;
	tmp = (uint16 *)fs_mmap(fd);
	if (!tmp) {
		tmp = malloc(len);
		fs_read(fd, tmp, len);
		ownmem = 1;
	} else {
		tmp = (uint16 *)( ((uint8 *)tmp) + fs_tell(fd) );
	}
	fs_close(fd);

	t = malloc(sizeof(snd_effect_t));
	memset(t, 0, sizeof(snd_effect_t));

	if (chn == 1) {
		/* Mono PCM/ADPCM */
		t->len = len/2;	/* 16-bit samples */
		t->rate = hz;
		t->used = 1;
		t->locl = snd_mem_malloc(len);
		if (t->locl)
			spu_memload(t->locl, tmp, len);
		t->locr = 0;
		t->stereo = 0;

		if (fmt == 20) {
			t->fmt = AICA_SM_ADPCM;
			t->len *= 4;	/* 4-bit packed samples */
		} else
			t->fmt = AICA_SM_16BIT;
	} else if (chn == 2 && fmt == 1) {
		/* Stereo PCM */
		int i;
		uint16 * sepbuf;

		sepbuf = malloc(len/2);
		for (i=0; i<len/2; i+=2) {
			sepbuf[i/2] = tmp[i+1];
		}
		for (i=0; i<len/2; i+=2) {
			tmp[i/2] = tmp[i];
		}
		
		t->len = len/4;	/* Two stereo, 16-bit samples */
		t->rate = hz;
		t->used = 1;
		t->locl = snd_mem_malloc(len/2);
		t->locr = snd_mem_malloc(len/2);
		if (t->locl)
			spu_memload(t->locl, tmp, len/2);
		if (t->locr)
			spu_memload(t->locr, sepbuf, len/2);
		t->stereo = 1;
		t->fmt = AICA_SM_16BIT;

		free(sepbuf);
	} else if (chn == 2 && fmt == 20) {
		/* Stereo ADPCM */

		/* We have to be careful here, because the second sample might not
		   start on a nice even dword boundary. We take the easy way out
		   and just malloc a second buffer. */
		uint8 * buf2 = malloc(len/2);
		memcpy(buf2, ((uint8*)tmp) + len/2, len/2);

		t->len = len;	/* Two stereo, 4-bit samples */
		t->rate = hz;
		t->used = 1;
		t->locl = snd_mem_malloc(len/2);
		t->locr = snd_mem_malloc(len/2);
		if (t->locl)
			spu_memload(t->locl, tmp, len/2);
		if (t->locr)
			spu_memload(t->locr, buf2, len/2);
		t->stereo = 1;
		t->fmt = AICA_SM_ADPCM;

		free(buf2);
	} else {
		free(t);
		t = NULL;
	}

	if (ownmem)
		free(tmp);

	if (t) {
		LIST_INSERT_HEAD(&snd_effects, t, list);
	}
	
	return (sfxhnd_t)t;
}

/* Play a sound effect with the given volume and panning */
void snd_sfx_play(sfxhnd_t idx, int vol, int pan) {
	int size;
	snd_effect_t * t = (snd_effect_t *)idx;
	AICA_CMDSTR_CHANNEL(tmp, cmd, chan);

	size = t->len;
	if (size >= 65535) size = 65534;

	/* printf("sndstream: playing effect %p on chan %d, loc %x/%x, rate %d, size %d, vol %d, pan %d\r\n",
		idx, sfx_lastchan, t->locl, t->locr, t->rate, size, vol, pan); */
	if (!t->stereo) {
		cmd->cmd = AICA_CMD_CHAN;
		cmd->timestamp = 0;
		cmd->size = AICA_CMDSTR_CHANNEL_SIZE;
		cmd->cmd_id = sfx_lastchan;
		chan->cmd = AICA_CH_CMD_START;
		chan->base = t->locl;
		chan->type = t->fmt;
		chan->length = size;
		chan->loop = 0;
		chan->loopstart = 0;
		chan->loopend = size;
		chan->freq = t->rate;
		chan->vol = vol;
		chan->pan = pan;
		snd_sh4_to_aica(tmp, cmd->size);
	
		sfx_lastchan++;
		if (sfx_lastchan >= 64)
			sfx_lastchan = 2;
	} else {
		cmd->cmd = AICA_CMD_CHAN;
		cmd->timestamp = 0;
		cmd->size = AICA_CMDSTR_CHANNEL_SIZE;
		cmd->cmd_id = sfx_lastchan;
		chan->cmd = AICA_CH_CMD_START;
		chan->base = t->locl;
		chan->type = t->fmt;
		chan->length = size;
		chan->loop = 0;
		chan->loopstart = 0;
		chan->loopend = size;
		chan->freq = t->rate;
		chan->vol = vol;
		chan->pan = 0;

		snd_sh4_to_aica_stop();
		snd_sh4_to_aica(tmp, cmd->size);

		sfx_lastchan++;
		if (sfx_lastchan >= 64)
			sfx_lastchan = 2;

		cmd->cmd_id = sfx_lastchan;
		chan->base = t->locr;
		chan->pan = 255;
		snd_sh4_to_aica(tmp, cmd->size);
		snd_sh4_to_aica_start();
		
		sfx_lastchan++;
		if (sfx_lastchan >= 64)
			sfx_lastchan = 2;
	}
}

void snd_sfx_stop_all() {
	int i;
	
	AICA_CMDSTR_CHANNEL(tmp, cmd, chan);

	for (i=2; i<64; i++) {
		cmd->cmd = AICA_CMD_CHAN;
		cmd->timestamp = 0;
		cmd->size = AICA_CMDSTR_CHANNEL_SIZE;
		cmd->cmd_id = i;
		chan->cmd = AICA_CH_CMD_STOP;
		chan->base = 0;
		chan->type = 0;
		chan->length = 0;
		chan->loop = 0;
		chan->loopstart = 0;
		chan->loopend = 0;
		chan->freq = 44100;
		chan->vol = 0;
		chan->pan = 0;
		snd_sh4_to_aica(tmp, cmd->size);
	}
}
