/* control.c - SH4 control over module playing */

#include "sh4/dxm.h"
#include "types.h"
#include "aica.h"

/* hardware registers */
static aica_vox_t *AICA_VOX  = (aica_vox_t *)0xa0700000;

/* private prototypes */
sint32 G2Write(uint32 *, uint32);
sint32 G2Read(volatile uint32 *, uint32 *);

static void *spu_memset(void *, uint32, uint32);
static void *spu_memcpy(void *, void *, uint32);
static uint32 convert_volume(uint32);
static uint32 convert_pan(sint32);
static uint32 convert_freq(uint32);

/* get a more appropriate timeout later */
#define TIMEOUT	1000000

XM_INFO *xm_info = (XM_INFO *)XM_INFO_ADDR;
OS_HEADER os_header[32];

sint32
dxm_disable_arm()
{
	sint32 val;
	sint32 i;
	sint32 *ptr;

	/* disable ARM cpu */
	if (G2Read((uint32 *)0xa0702c00, &val) < 0) {
		return (-1);
	}
	G2Write((void *)0xa0702c00, val | 1);

	/* turn off all voices */
	for (i = 0, ptr = (sint32 *)0xa0700000; i < 64; i++) {
		G2Write(ptr, 0x80000000);
		G2Write(ptr, 0);
		G2Write(ptr, 0);
		G2Write(ptr, 0);
		G2Write(ptr, 0);
		G2Write(ptr, 0);
		G2Write(ptr, 0);
		G2Write(ptr, 0);
		G2Write(ptr, 0);
		G2Write(ptr, 0);
		G2Write(ptr, 0);
		G2Write(ptr, 0);
		G2Write(ptr, 0);
		G2Write(ptr, 0);
		G2Write(ptr, 0);
		G2Write(ptr, 0);
		G2Write(ptr, 0);
		G2Write(ptr, 0);
		G2Write(ptr, 0);
		G2Write(ptr, 0);
		G2Write(ptr, 0);
		G2Write(ptr, 0);
		G2Write(ptr, 0);
		G2Write(ptr, 0);
		G2Write(ptr, 0);
		G2Write(ptr, 0);
		G2Write(ptr, 0);
		G2Write(ptr, 0);
		G2Write(ptr, 0);
		G2Write(ptr, 0);
		G2Write(ptr, 0);
	}
	return (0);

}

sint32
dxm_enable_arm()
{

	uint32 val;

	/* enable ARM cpu */
	if (G2Read((uint32 *)0xa0702c00, &val) < 0) {
		return (-1);
	}
	G2Write((void *)0xa0702c00, val & (~1));

	return (0);

}

sint32
dxm_load_driver(driver, size)
	void *driver;
	uint32 size;
{

	/* make sure ARM is disabled */
	dxm_disable_arm();

	/* clear all of driver sound RAM (first 64kbytes) */
	spu_memset((void *)0x00000000, 0, 64*1024);

	/* copy driver to sound RAM */
	spu_memcpy((void *)0x00000000, driver, size);

	return (0);

}

void *
dxm_sramcpy4(dst, src, size)
	void *dst;
	void *src;
	uint32 size;
{
	return (spu_memcpy(dst, src, size));
}

sint32
dxm_halt_xm()
{
	G2Write(&(xm_info->play), 0);
	return (0);
}

sint32
dxm_init_xm(order)
	uint32 order;
{

	uint32 timeout = TIMEOUT;
	uint32 val;

	G2Write(&(xm_info->init), order);

	do {
		if ((G2Read(&(xm_info->init), &val) < 0) || !timeout--) {
			return (-1);
		}
	} while (val != 0);
	return (0);

}

sint32
dxm_init_done()
{

	uint32 timeout = TIMEOUT;
	uint32 val;

	do {
		if ((G2Read(&(xm_info->done), &val) < 0) || !timeout--) {
			return (-1);
		}
	} while (val == 0);
	return (0);

}

sint32
dxm_play_xm()
{
	G2Write(&(xm_info->play), 1);
	return (0);
}

sint32
dxm_set_stereo(mode)
	bool mode;
{
	G2Write(&(xm_info->play), mode);
	return (0);
}

sint32
dxm_open_os(ch, addr, format, loop, start, end, size, freq, pan, volume)
	uint32 ch;
	uint32 addr;
	uint32 format;
	uint32 loop;
	uint32 start;
	uint32 end;
	uint32 size;
	uint32 freq;
	uint32 pan;
	uint32 volume;
{

	/* fill out the structure for specified channel */
	os_header[ch].addr = addr;
	os_header[ch].flags = ((format & 0x02)<<7) | ((loop & 0x01)<<9);
	if (loop) {
		os_header[ch].loop = (start & 0xffff) | (end<<16);
	} else {
		os_header[ch].loop = (size<<16);
	}
	os_header[ch].pitch = convert_freq(freq);
	os_header[ch].pan_volume = convert_pan(pan)
			| (convert_volume(volume)<<8);
	return (0);

}

sint32
dxm_play_os(ch)
	uint32 ch;
{

	sint32 flags;
	sint32 i = ch + 32;

	/* if looping ADPCM, make sure the waveform format is MODE_ADPCM_LOOP */
	flags = os_header[ch].flags;
	if (flags & 0x0300) {
		flags |= 0x0080;
	}

	G2Write((uint32 *)AICA_VOX[i].cfg_addr_hi, KEYOFF);
	G2Write((uint32 *)AICA_VOX[i].addr_lo, os_header[ch].addr & 0xffff);
	G2Write((uint32 *)AICA_VOX[i].loop_start, os_header[ch].loop & 0xffff);
	G2Write((uint32 *)AICA_VOX[i].loop_end, (os_header[ch].loop>>16) & 0xffff);
	G2Write((uint32 *)AICA_VOX[i].adsr1, 0x07df);
	G2Write((uint32 *)AICA_VOX[i].adsr2, 0x0000);
	G2Write((uint32 *)AICA_VOX[i].pitch, os_header[ch].pitch & 0xffff);
	G2Write((uint32 *)AICA_VOX[i].lfo1, 0x0000);
	G2Write((uint32 *)AICA_VOX[i].lfo2, 0x0000);
	G2Write((uint32 *)AICA_VOX[i].pan_volume, os_header[ch].pan_volume & 0xffff);
	G2Write((uint32 *)AICA_VOX[i].volume2, os_header[ch].volume2 & 0xffff);
	G2Write((uint32 *)AICA_VOX[i].unknown[0], 0x0000);
	G2Write((uint32 *)AICA_VOX[i].unknown[1], 0x0000);
	G2Write((uint32 *)AICA_VOX[i].unknown[2], 0x0000);
	G2Write((uint32 *)AICA_VOX[i].unknown[3], 0x0000);
	G2Write((uint32 *)AICA_VOX[i].cfg_addr_hi, KEYON
			| (os_header[ch].flags & 0x0380)
			| ((os_header[ch].addr>>16) & 0x001f));
	return (0);

}

sint32
dxm_stop_os(ch)
	uint32 ch;
{

	uint32 val;
	sint32 i = ch + 32;

	/* move ARM stuff here instead */

	if (G2Read((uint32 *)AICA_VOX[i].cfg_addr_hi, &val) < 0) {
		return (-1);
	}
	G2Write((uint32 *)AICA_VOX[i].cfg_addr_hi, (val & ~0x4200) | 0x8000);
	return (0);

}

sint32
dxm_set_volume_os(ch, volume)
	uint32 ch;
	uint32 volume;
{
	sint32 i = ch + 32;

	os_header[ch].pan_volume = (os_header[ch].pan_volume & 0xf0ff)
				| (convert_volume(volume)<<8);

	G2Write((uint32 *)AICA_VOX[i].pan_volume, os_header[ch].pan_volume);

	return (0);

}

sint32
dxm_set_pan_os(ch, pan)
	uint32 ch;
	sint32 pan;
{

	sint32 i = ch + 32;

	os_header[ch].pan_volume = (os_header[ch].pan_volume & 0xffe0)
				| convert_pan(pan);

	G2Write((uint32 *)AICA_VOX[i].pan_volume, os_header[ch].pan_volume);

	return (0);

}

/* 0: no sound, 128: max sound */
static uint32
convert_volume(volume)
	uint32 volume;
{
	return ((volume>>3) & 0x0f);
}

/* -128 = panned to the left, 0 = center, 128 = panned to the right */
static uint32
convert_pan(pan)
	sint32 pan;
{
	pan += 128;
	pan = pan>>3;
	if (pan < 16) {
		pan = ~(pan - 16);
	}
	return (pan & 0x1f);
}

/* converts to floating-point form (algo by Marcus Comstedt) */
static uint32
convert_freq(freq)
	uint32 freq;
{

	uint32 freq_lo, freq_base = 5644800;
	sint32 freq_hi = 7;

	while (freq < freq_base && freq_hi > -8) {
		freq_base >>= 1;
		--freq_hi;
	}
	freq_lo = (freq<<10) / freq_base;
	return ((freq_hi << 11) | (freq_lo & 1023));

}

sint32
G2Write(addr, val)
	uint32 *addr;
	uint32 val;
{

	/* should disable IRQs + DMA here */

	while (*(volatile uint32 *)0xa05f688c & 0x11);

	*addr = val;

	while (*(volatile uint32 *)0xa05f688c & 0x11);

	/* should enable IRQs + DMA here */

	return (0);

}

sint32
G2Read(addr, val)
	volatile uint32 *addr;
	uint32 *val;
{

	uint32 val1, val2;
	uint32 timeout = 0;

	while (*(volatile uint32 *)0xa05f688c & 0x11);

	do {
		val1 = *addr;
		val2 = *addr;

		while (*(volatile uint32 *)0xa05f688c & 0x11);
		
		if (timeout++ > 10000) {
			return (-1);
		}
	} while (val1 != val2);

	*val = val1;

	return (0);

}

/* only 32-bit writes */
static void *
spu_memset(s, c, n)
	void *s;
	uint32 c;
	uint32 n;
{

	uint32 i;
	uint32 *ptr = (uint32 *)s + 0xa0800000/4;

	for (i = 0, n >>= 2; i < n; i++) {
		G2Write(ptr++, c);
	}

	return (s);

}

/* only 32-bit writes */
static void *
spu_memcpy(dst, src, n)
	void *dst;
	void *src;
	uint32 n;
{

	uint32 i;
	uint32 *s = (uint32 *)src, *d = (uint32 *)dst + 0xa0800000/4;

	for (i = 0, n >>= 2; i < n; i++) {
		G2Write(d++, *(s++));
	}

	return (dst);

}
