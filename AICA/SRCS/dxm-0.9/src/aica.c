/* aica.c - sound hardware routines */

#include "types.h"
#include "dxm.h"
#include "aica.h"

/* only define if debugging */
//#define DEBUG	1

/* hw-regs */
static aica_vox_t *AICA_VOX = (aica_vox_t *)0x00800000;

/* prototypes */
void hw_init(void);
void hw_play_waveform(XM_SM_HEADER *, uint32, uint32, uint32);
void hw_set_vol_pan_freq(uint8, uint8, uint8, uint8, uint32);
uint32 random(void);

/* private prototypes */
static uint16 convert_freq(uint32);
static uint16 convert_pan_vol(sint8, uint32);
static uint16 convert_volume2(uint32);

static const char id[] __attribute__ ((section (".text"))) =
	"dxm $Id: aica.c,v 1.1.1.1 2001/09/08 10:48:15 ejstans Exp $";

/* taken from Dan Potters s3mplay but I'm not sure it is correct */
/* neither of these are correct, so im just using the linear volume
   directly (this is not correct either but will save a few bytes of
   memory and actually sounds somewhat better */
/*
static uint8 VolTab[] = {
	0xff, 0x4a, 0x48, 0x47, 0x46, 0x44, 0x43, 0x42, 0x40, 0x3f,
	0x3e, 0x3c, 0x3b, 0x3a, 0x38, 0x37, 0x36, 0x35, 0x33, 0x32,
	0x31, 0x30, 0x2e, 0x2d, 0x2c, 0x2b, 0x2a, 0x28, 0x27, 0x26,
	0x25, 0x24, 0x23, 0x22, 0x20, 0x1f, 0x1e, 0x1d, 0x1c, 0x1b,
	0x1a, 0x19, 0x17, 0x16, 0x15, 0x14, 0x13, 0x12, 0x11, 0x10,
	0x0f, 0x0e, 0x0d, 0x0c, 0x0b, 0x0a, 0x09, 0x08, 0x07, 0x06,
	0x05, 0x04, 0x03, 0x01, 0x00,
*/
/*
	0xff, 0x7f, 0x69, 0x5d, 0x54, 0x4d, 0x47, 0x43, 0x3f, 0x3b,
	0x38, 0x35, 0x32, 0x30, 0x2d, 0x2b, 0x29, 0x27, 0x26, 0x24,
	0x22, 0x21, 0x1f, 0x1e, 0x1d, 0x1b, 0x1a, 0x19, 0x18, 0x17,
	0x16, 0x15, 0x14, 0x13, 0x12, 0x11, 0x10, 0x0f, 0x0f, 0x0e,
	0x0d, 0x0c, 0x0b, 0x0b, 0x0a, 0x09, 0x09, 0x08, 0x07, 0x07,
	0x06, 0x05, 0x05, 0x04, 0x04, 0x03, 0x03, 0x02, 0x02, 0x01,
	0x00, 0x00, 0x00, 0x00, 0x00,

};

*/

/* initialize hw-registers */
void
hw_init()
{
	sint32 i, j;
	uint32 *p;

	*(uint32 *)0x00802800 = 0;

	/* reset the 64 voice channels */
	for (i = 0; i < 64; i++) {
		AICA_VOX[i].cfg_addr_hi = 0x8000;
		AICA_VOX[i].addr_lo = 0;
		AICA_VOX[i].loop_start = 0;
		AICA_VOX[i].loop_end = 0;
		AICA_VOX[i].adsr1 = 0x0000;
		AICA_VOX[i].adsr2 = 0x0000;
		AICA_VOX[i].pitch = 0;
		AICA_VOX[i].lfo1 = 0x0000;
		AICA_VOX[i].lfo2 = 0;
		AICA_VOX[i].pan_volume = 0;
		AICA_VOX[i].volume2 = 0x0020;
		AICA_VOX[i].unknown[0] = 0x1fff;
		AICA_VOX[i].unknown[1] = 0x1fff;
		AICA_VOX[i].unknown[2] = 0x1fff;
		AICA_VOX[i].unknown[3] = 0x1fff;
		AICA_VOX[i].unknown[4] = 0x1fff;
		for (j = 5; j < 21; j++) {
			AICA_VOX[i].unknown[j] = 0;
		}
	}
	p = (uint32 *)0x00803400;
	for (i = 0; i < 0x0800/4; i++) {
		p[i] = 0;
	}
	p = (uint32 *)0x00803000;
	for (i = 0; i < 0x0200/4; i++) {
		p[i] = 0;
	}
	p = (uint32 *)0x00803200;
	for (i = 0; i < 0x0100/4; i++) {
		p[i] = 0;
	}
	p = (uint32 *)0x00804000;
	for (i = 0; i < 0x0400/4; i++) {
		p[i] = 0;
	}

	for (i = 0; i < 8; i++) {
		*(uint32 *)0x00802d04 = 0x0008;
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
	}
	*(uint32 *)0x00802800 = 15;

}

void
hw_play_waveform(my_sm_hdr, ch, sample_offset, freq)
	XM_SM_HEADER *my_sm_hdr;
	uint32 ch;
	uint32 sample_offset;
	uint32 freq;
{

	uint32 loop = 0;
	uint32 format = 0;
	uint32 addr = (uint32)(my_sm_hdr->data) + sample_offset;

	/* the following can be used to mask out channels */

#ifdef DEBUG
	switch (ch) {
		case 9:
		case 10:
		case 11:
		case 17:
		case 18:
		case 19:
		case 20:
		case 21:
		case 22:
		case 23:
			break;
		default:
			return;
			break;
	}
#endif	/* DEBUG */


	/* must change sample type later if ADPCM is to be supported */
	if ((my_sm_hdr->type & 0x10) == 0x10) {
		format = 0;
	} else {
		format = 1;
	}

	/* stop any previous sound */
	AICA_VOX[ch].cfg_addr_hi = KEYOFF;
	/* set lo-order bits of waveform address */
	AICA_VOX[ch].addr_lo = addr & 0xffff;
	switch (my_sm_hdr->type>>5) {
		case 0:
			/* short waveform */
			AICA_VOX[ch].loop_start = my_sm_hdr->loop_start - sample_offset;
			AICA_VOX[ch].loop_end = my_sm_hdr->loop_end - sample_offset;
			if ((my_sm_hdr->type & 0x03) != 0) {
				loop = 1;
			}
//			/* remove */ loop = 1;
			break;
		case 1:
		case 2:
		case 3:
			/* the rest dont use hw-loops (at least not here) */
			AICA_VOX[ch].loop_start = 0;
			AICA_VOX[ch].loop_end = 0xffff;
			loop = 0;
			break;
	}
//	AICA_VOX[ch].adsr1 = 0x07df;
	AICA_VOX[ch].adsr1 = 0x07fa;
	AICA_VOX[ch].adsr2 = 0x0000;
	AICA_VOX[ch].pitch = convert_freq(freq);
	AICA_VOX[ch].lfo1 = 0x4210;
	AICA_VOX[ch].lfo2 = 0x0000;
	/* dont set any volume here; will set vol+pan after env proc. */
	AICA_VOX[ch].pan_volume = 0x0000;
//	AICA_VOX[ch].pan_volume = 0x0f00;
//	AICA_VOX[ch].volume2 = 0x0020;
	/* start playing the waveform */
	AICA_VOX[ch].cfg_addr_hi = KEYON | (loop<<9) | (format<<7)
		| ((addr>>16) & 0x1f);
}

/* convert frequency to AICA format [algorithm by Marcus Comstedt] */
static uint16
convert_freq(freq)
	uint32 freq;
{

	uint32 freq_lo, freq_base = 5644800;
	sint32 freq_hi = 7;

        while (freq < freq_base && freq_hi > -8) {
                freq_base >>= 1;
                freq_hi--;
        }
        freq_lo = (freq<<10) / freq_base;
        return ((freq_hi << 11) | (freq_lo & 1023));

}

/* convert paning and global volume to AICA format */
static uint16
convert_pan_vol(pan, vol)
	sint8 pan;
	uint32 vol;
{
	if (pan < 0) {
		pan = ((~pan)>>3) & 0x0f;
	} else {
		pan = ((pan>>3) & 0x0f) | 0x10;
	}
	return ((((vol>>2) & 0x0f)<<8) | pan);
}

/* convert volume to AICA format */
static uint16
convert_volume2(vol)
	uint32 vol;
{
	return ((vol == 0) ? 0xff20 : (((~(vol-1)) & 0x3f)<<8) | 0x20);
	/* return ((VolTab[vol]<<8) | 0x20); */
}

/* set final volume, panning and frequency */
void
hw_set_vol_pan_freq(ch, mvol, vol, pan, freq)
	uint8 ch;
	uint8 mvol;
	uint8 vol;
	uint8 pan;
	uint32 freq;
{
	AICA_VOX[ch].pan_volume = convert_pan_vol(pan, mvol);
	AICA_VOX[ch].volume2 = convert_volume2(vol);

	/* clamp frequency here (not really necessary) */

	/* set sound frequency */
	AICA_VOX[ch].pitch = convert_freq(freq);
}

/* returns a (hehe) "random" number */
uint32
random()
{
	return (*(uint32 *)0x00810004);
}
