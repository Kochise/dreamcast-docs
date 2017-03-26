/* KallistiOS ##version##

   sfxmgr.c
   (c)2000 Dan Potter

*/

#include <kos.h>

CVSID("$Id: s3m.c,v 1.2 2002/01/06 00:40:33 bardtx Exp $");

static uint32 ram_top;



uint32 sfx_load_sample(const uint16 *src, uint32 len) {
	uint32 where;

	where = ram_top;
	spu_memload(where, (uint8*)src, len);
	ram_top = (ram_top + len + 3) & (~3);

	return where;
}

sfx_play_effect(int chn, uint32 src, uint32 freq, uint32 len, uint32 vol, uint32 pan) {
	chans[chn].cmd = AICA_CMD_START;
	chans[chn].pos = src;
	chans[chn].length = len;
	chans[chn].freq = freq;
	chans[chn].vol = vol;
	chans[chn].pan = pan;
	chn_kick(chn);
}


