/* KallistiOS ##version##

   sfxmgr.c
   (c)2000 Dan Potter

   Sound effects management system; this thing loads and plays sound effects
   during game operation.
*/

#include <kos.h>

CVSID("$Id: sfxmgr.c,v 1.2 2002/01/06 00:40:33 bardtx Exp $");

typedef struct {
	uint32	loc, len;
	uint32	rate;
	uint32	used;
} snd_effect;

#define SFX_CNT 16
static snd_effect sfx[SFX_CNT] = { {0,0,0,0} };

static int sfx_lastchan = 2;

static int sfx_find_open() {
	int i;
	for (i=0; i<SFX_CNT; i++)
		if (sfx[i].used == 0)
			return i;
			
	return -1;
}

void sfx_unload_all() {
	int i;

	for (i=0; i<SFX_CNT; i++) {
		sfx[i].loc = sfx[i].len = sfx[i].rate = sfx[i].used = 0;
	}
}

/* WAV header:
	0x08	-- "WAVE"
	0x16	-- short num channels (1/2)
	0x18	-- long  HZ
	0x22	-- short 8 or 16 (bits)
	0x28	-- long  data length
	0x2c	-- data start

 */
int sfx_load(const char *fn) {
	uint32	fd, len, hz;
	uint16	*tmp, chn, fmt;
	int	idx;

	idx = sfx_find_open();
	if (idx < 0) {
		printf("sndserver: no more sfx slots\r\n");
		return -1;
	}
	
	printf("sndserver: loading effect %s as slot %d\r\n", fn, idx);

	fd = fs_open(fn, O_RDONLY);
	if (fd == 0) {
		printf("sndserver: can't open sfx %s\r\n", fn);
		return -1;
	}

	/* Check file magic */
	hz = 0;
	fs_seek(fd, 8, SEEK_SET);
	fs_read(fd, &hz, 4);
	if (strncmp((char*)&hz, "WAVE", 4)) {
		printf("sndserver: file is not RIFF WAVE\r\n");
		fs_close(fd);
		return -1;
	}
	
	
	/* Read WAV header info */
	fs_seek(fd, 0x16, SEEK_SET);
	fs_read(fd, &chn, 2);
	fs_read(fd, &hz, 4);
	fs_seek(fd, 0x22, SEEK_SET);
	fs_read(fd, &fmt, 2);
	
	// printf("WAVE file is %s, %dHZ, %d bits\r\n", chn==1 ? "mono" : "stereo", hz, fmt);
	
	/* Read WAV data */
	fs_seek(fd, 0x28, SEEK_SET);
	fs_read(fd, &len, 4);
	// printf("Reading %d bytes of wave data\r\n", len);
	tmp = malloc(len);
	fs_read(fd, tmp, len);
	fs_close(fd);
	sfx[idx].loc = sfx_load_sample(tmp, len);
	free(tmp);
	
	sfx[idx].len = len;
	sfx[idx].rate = hz;
	sfx[idx].used = 1;

	return idx;
}

void sfx_play(int idx, int vol, int pan) {
	int size;

	size = sfx[idx].len/2;
	if (size > 65536) size = 65535;
	/* printf("sndstream: playing effect %d on chan %d, loc %x, rate %d, size %d, vol %d, pan %d\r\n",
		idx, sfx_lastchan, sfx[idx].loc, sfx[idx].rate, size, vol, pan); */
	sfx_play_effect(sfx_lastchan, sfx[idx].loc, sfx[idx].rate, size, vol, pan);
	
	sfx_lastchan++;
	if (sfx_lastchan >= 64)
		sfx_lastchan = 2;
}

