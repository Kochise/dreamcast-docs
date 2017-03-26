/* SEGA Dreamcast IP.BIN
 *
 * Hacked by Lars Olsson
 *
 * Questions, corrections etc:
 * jlo@ludd.luth.se
 *
 * Notes:
 * ~~~~~~
 *
 * reg[REG] = access to register REG (including both normal
 *            CPU registers aswell as CPU-related memory-mapped
 *            registers, but NOT other hardware registers)
 *
 *
 * Most names have been made up by me and can be very misleading,
 * even to the point of being downright incorrect with regards to
 * their actual functions
 *
 * Beware: this source code is only meant to illustrate the function
 * of the BootROM and it is not a 100% translation of the actual code.
 * A number of short cuts and simplifications have been made in order
 * to clarify the operation, which was the purpose of this whole exercise.
 *
 * Compiling this source (in so far it is possible at all) will NOT
 * produce a proper BootROM! For a myriad of reasons...
 *
 */

#include "types.h"
#include "bootROM.h"
#include "hwregs.h"

/*******************************************************************************
 *
 * START OF IP.BIN
 *
 ******************************************************************************/
/* This code is loaded from IP.BIN. The copy in ROM actually resides
 * at 80008000 instead
 */
void
_ac008300()
{
	reg[CCR] = 0x0000092b;
	reg[R15] = 0x7e001000;		/* use cache as memory for stack */
	init_splash_screen();
	_ac00b700();			/* jump to bootstrap1 */
}

void
copy_to_framebuffer(image)	/* _8c008330 */
	uint32_t *image;
{
	uint32_t width = 640;	/* really not used! */
	uint32_t height = 480;
	uint32_t *dst;
	uint32_t size = 640 * 480;

	dst = (uint32_t *)(0xa5200000 + (640 * 4 * 480));
	do {
		*dst-- = *image++;
	} while (size-- != 0);
}

void
memset4(arg1, arg2, arg3)	/* 8c00836c */
	uint32_t *dst; 
	uint32_t size;
	uint32_t data;
{
	dst += size;
	size *= 2;

	while (size-- != 0) {
		*dst-- = data;
	}
}

uint32_t
get_video_cable()		/* _8c008380 */
{
	uint32_t cable;

	cable = (*(uint16_t *)0xff800030 & 0x0300) | (*(uint32_t *)0xa0702c00 & 0xfffffcff);
	*(uint32_t *)0xa0702c00 = cable;
	return (cable);
}

void
init_splash_screen()	/* 8c0083a8 */
{
	clear_variables();
	*(uint32_t *)0x8ced3d9c = 0;
	show_splash_screen();
}

void
clear_variables()	/* _8c0083c0 */
{
	uint8_t *dst = (uint8_t *)0x8ced3d00;	/* 1, R15 */

	while (dst < (uint8_t *)0x8ced3da0) {
		*dst++ = 0;
	}
}

void
show_splash_screen()		/* 8c0083f8 */
{
	uint32_t old_SR;
	uint32_t video_mode;	/* 9, R15 */
	uint32_t i;		/* 8, R15 */
	uint32_t initial_time;	/* 7, R15, j */
	uint32_t current_time;	/* 6, R15 */
	uint32_t time_diff;	/* 5, R15 */
	uint32_t timeout;	/* 4, R15 */
	uint32_t finished;	/* 3, R15 */
	uint32_t delay;		/* 2, R15 */
	uint32_t max_loop;	/* 1, R15 */

	init_timer();

	old_SR = (reg[SR]>>4) & 0x0000000f;
	reg[SR] = (reg[SR] & 0xffffff0f) | 0x000000f0;

	video_mode = get_video_mode();

	reg[SR] = ((old_SR & 0x0000000f)<<4) | (reg[SR] & 0xffffff0f);

	switch (video_mode) {
		case 1:
		case 3:
			i = 8;
			break;
		case 4:
			/* VGA */
			i = 9;
			break;
		default:
			i = 6;
			break;
	}
	/* _8c008460 */
	old_SR = (reg[SR]>>4) & 0x0000000f;
	reg[SR] = (reg[SR] & 0xffffff0f) | 0x000000f0;

	init_graphics(i);

	reg[SR] = ((old_SR & 0x0000000f)<<4) | (reg[SR] & 0xffffff0f);

	/* render splash screen to framebuffer */
	render_frame(i);
	set_display(1);

	/* wait a little while */
	initial_time = get_timer();
	max_loop = 0;
	finished = 0;
	while (finished == 0) {
		new_time = get_timer();
		time_diff = get_time_difference(initial_time, new_time);
		timeout = convert_time(time_diff);

		delay = 0;
		while (delay++ < 1000);

		if (max_loop++ >= 4000) {
			finished = 1;
		}
		if (timeout >= 6000000) {
			break;
		}
	}
	/* 8c00851e */

	sys_do_bioscall(0);	/* boot5() */
}

/* this renders images and text to framebuffer */
void
render_frame(arg)		/* 8c00853c */
	uin32_t arg;
{
	uint32_t weird_value;	/* 0, R15 */

	fill_8ced4000(arg, 0x00c0c0c0);
	weird_value = compute_weird_value();
	print_text(340, 189, "PRODUCED BY OR");	/* *(uint32_t *)0x8c009d98 */
	print_text(340, 213, "UNDER LICENSE FROM");	/* *(uint32_t *)0x8c009d9c */
	print_text(340, 237, "SEGA ENTERPRISES, LTD");	/* *(uint32_t *)0x8c009da0 */
	_8c008b68(337, 186, 780, 260);	/* image? */
	_8c00892c(weird_value);
	show_small_logo();
	upload_image();
}

void
print_text(xpos, ypos, text)	/* 8c0085cc */
	uint16_t xpos;	/* _0012, R15 */
	uint16_t ypos;	/* _0010, R15 */
	sint8_t *text;	/* _000c, R15 */
{
	uint32_t len;	/* _0008, R15 */
	uint16_t x;	/* _0002, R15 */
	uint16_t y;	/* _0000, R15 */
	uint32_t i;	/* _0004, R15 */

	len = strlen(text);
	x = xpos;
	y = ypos;
	i = 0;

	while (i < len) {
		/* 8c0085f8 */
		if (text[i] == 'L' && text[i+1] == 'T') {
			print_char(&x, &y, 0x1f);	/* print LTD glyph */
			i += 2;
		} else {
			/* 8c00862c */
			print_char(&x, &y, text[i]);
			i++;
		}
	}
}

void
print_char(x, y, c)		/* 8c008652 */
	uint16_t *x;	/* _0034, R15 */
	uint16_t *y;	/* _0030, R15 */
	sint8_t c;	/* _002f, R15 */
{
	uint8_t buf[20];	/* _0004, R15 */
	uint32_t i;		/* _0024, R15 */
	uint32_t *p;		/* _0020, R15 */
	uint8_t *p2;		/* _0000, R15 */
	uint32_t j;		/* _0028, R15 */

	_8c009ba8(8, buf, (void *)0x8c009d40);	/* bah...weird function */
	if (c == ' ') {
		*x += 5;
		return;
	}

	/* find the char in a list */
	p = (uint32_t *)0xac00b46e;
	p2 = (uint8_t *)0x8c009da4;
	i = 63;
	j = 0;
	while (j < 63) {
		if (p2[0] == c) {
			break;
		}
		p = p + p2[2];
		p2 += 3;
		j++;
	}
	/* 8c0086de */

	/* WORK TO DO HERE */

}

void
show_small_logo()	/* 8c0087fc */
{
	mr_env_t env;
	mr_t mr;

	/* The palette buffer is placed right before the local framebuffer.
	 * There exists a buffer overflow condition in the code that copies
	 * the palette which means it's possible to overwrite the rendered
	 * frame before it is shown! Unfortunately the size of the palette is
	 * limited to a 16-bit integer which means it's not possible to write
	 * enough data to cover the offending "PRODUCED BY..." text :(
	 */
	mr.palette = (uint8_t *)0x8ced3e00;
	mr.image = (uint8_t *)0x8c00b820;

	env.x = 300;	/* position of logo */
	env.y = 298;
	env.c = 0;
	env.d = 0;

	decode_small_logo(&mr, &env, 320, 90);
}

void
upload_image()		/* 8c008b4c */
{
	uint32_t *frame = (uint32_t *)0x8ced4000;
	uint32_t foo = 0;	/* not used */

	copy_to_framebuffer(frame);
}

/* copies sega logo probably */
void
_8c008b68(a, b, c, d)		/* 8c008b68 */
	sint16_t x1;	/* _000e, R15 */
	sint16_t y1;	/* _000c, R15 */
	sint16_t x2;	/* _000a, R15 */
	sint16_t y2;	/* _0008, R15 */
{
	uint32_t *d = (uint32_t *)0x8ced4000;	/* _0004, R15 */
	uint32_t i = 0;			/* _0000, R15 */

	d += (((((479 - y1) * 640) - x1) + 639) * 4);
	while (d < (((((479 - y2) * 640) - x2) + 639) * 4) + 0x8ced40000) {
		/* 8c008bc4 */
		d++;
		_8c008c54
	}

}

/* Now! This is a weird function indeed! */
void
compute_weird_value()	/* 8c0088b0 */
{
	uint32_t i = 0;		/* _0014 R15 */
	uint32_t j = 0;		/* _0004 R15 */
	uint8_t buf[12];	/* _0008 R15 */

	copy_string(buf, "SEGAKATANA");	/* 8c009d48 */

	while (j < sizeof(buf)) {
		/* 8c0088cc */
		i += buf[j] * buf[j + 1];
		j += 2;
	}
	/* 8c0088f6 */
	/* i becomes 25747 after completing above */
	/* what sync_cfg is, is a little harder to determine */
	/* definitely 0x100, but perhaps also 0x10 (interlace) is set */
	return ((PVR->sync_cfg & 0xffffff3f) * i);
}

/* weirdest yet... */
void
_8c00892c(key)
	uint32_t key;
{
	uint8_t buf1[] = { 0xef, 0xcd, 0xab, 0x89, };	/* _0000, R15 */
	uint8_t buf2[] = { 0x67, 0x45, 0x23, 0x01, };	/* _0004, R15 */
	uint16_t k;		/* _000c, R15 */
	uint8_t i;		/* _000e, R15 */
	uint8_t j;		/* _000f, R15 */

	if (key == 0x0067b768) {
		return;
	}

	for (k = 0; k < 6; k++) {
		/* 8c00894c */
		j = buf2[0];
		i = buf1[0];
		*(uint32_t *)&buf2[0] = ((*(uint32_t *)&buf2[0])<<8) + i;
		*(uint32_t *)&buf2[0] = ((*(uint32_t *)&buf1[0])<<8) + j;
	}
	/* 8c00897a */
}

void
fill_8ced4000(arg, col)	/* 8c008aa0 */
	uint32_t arg, col;
{
	memset4((uint32_t *)0x8ced4000, 0x0012c000, col);
}

void
print_pixel(x, y, pixel)	/* _8c008ad0 */
	sint32_t x;		/* _000c, R15 - 3, R15 */
	sint32_t y;		/* _0008, R15 - 2, R15 */
	uint32_t pixel;		/* _0004, R15 - 1, R15 */
{
	uint32_t *p:

	p = (((((479 - y) * 640) - x) + 639) * 4) + (uint32_t *)0x8ced4000;
	*p = pixel;
}

/* interesting */
void
decode_small_logo(mr, env, w, h)	/* 8c008d74 */
	mr_t *mr;		/* 11, _002c, R15 */
	mr_env_t *env;		/* 10, _0028, R15 */
	sint16_t w;		/* _0026, R15 */
	sint16_t h;		/* _0024, R15 */
{
	uint8_t *p = mr->image;		/* _0020, 8, R15 */
	uint8_t color;			/* _001f, R15 */
	uint32_t *p2;			/* _0014, 5, R15 */
	uint32_t j;			/* _0010, 4, R15 */
	uint32_t i;			/* _000c, 3, R15 */
	uint32_t len;			/* _0004, R15 */
	sint16_t cur_x;			/* _0002, R15 */
	sint16_t cur_y;			/* _0000, R15 */

	/* check if there is a small logo */
	if (p[0] != 'M' || p[1] != 'R') {
		return;
	}
	/* 8c008daa */
	p += 2;

	mr->size = (sint32_t)read_int(p);
	p += 8;

	/* p2 = image data */
	p2 = (uint8_t *)(mr->image + (sint32_t)read_int(p));
	p += 4;

	mr->width = (sint16_t)read_int(p);
	/* 8c008dea */
	p += 4;

	mr->height = (sint16_t)read_int(p);
	p += 4;

	/* this doesn't seem to be used anywhere */
	mr->foo = (sint16_t)read_int(p);
	p += 4;

	/* number of colors */
	mr->colors = (sint16_t)read_int(p);
	p += 4;

	j = 0;
	/* This is an unsigned comparison but mr->colors is sign-extended */
	/* No bounds checking but not easy to overwrite "PRODUCED.." text
	 * because mr->colors is only 16-bit, and while it can be negative,
	 * it will cause alot of thrashing when overwriting... */
	while (j < mr->colors) {
	 	mr->palette[j] = read_int(p);
		p += 4;
		j++;
	}
	/* 8c008e5e */
	p = p2;

	cur_x = 0;
	cur_y = 0;
	j = 0;
	/* this is an unsigned comparison but a signed multiplication */
	while (j < (mr->width * mr->height)) {
		p += decompress_data(p, &len, &color);
		if (env->c == 2 && env->d == color) {
			/* 8c008e9e, transparency? never reached in any case */
			j += len;
			cur_y += _8c009980(mr->width, cur_x + len);	/* args in r0, r1 prolly */
			cur_x = _8c009af0(mr->width, cur_x + len);	/* args in r0, r1, prolly */

		} else {
			/* 8c008ed2 */
			i = 0;
			/* unsigned comparison */
			while (i < len) {
				/* 8c008ee4 */
				/* signed comparisons, both are sign-extended */
				if (cur_x < w && cur_y < h) {
					/* 8c008efa */
					/* this must print the pixel */
					/* if cur_y is negative, it's possible
					   to move the logo upwards */
					print_pixel(env->x + cur_x, env->y + cur_y, mr->palette[color]);

				}
				/* 8c008f20 */
				j++;
				/* 8c008f26 */
				/* signed comparison */
				if (++cur_x >= mr->width) {
					cur_x = 0;
					cur_y++;
				}
				/* 8c008f42 */
				i++;
			}
			/* 8c008f50 */
		}
		/* 8c008f50 */
	}
	/* 8c008f64 */
}

uint32_t
decompress_data(p, len, color)	/* 8c008f70 */
	uint8_t *p;		/* _000c, R15 - 3, R15 */
	uint32_t *len;		/* _0008, R15 - 2, R15 */
	uint8_t *color;		/* _0004, R15 - 1, R15 */
{
	uint32_t i;		/* _0000, R15 */

	*len = 0;
	i = 1;

	if (*p & 0x80 == 0) {
		*len = 1;
		*color = *p;
		return (i);
	}
	/* 8c008f9e */
	while (*p & 0x80 != 0) {
		*len <<= 7;
		*len |= *len & 0x7f;
		p++;
		i++;
	}
	/* 8c008fd2 */
	*color = *p;
	return (i);
}

sint8_t
read_byte(p)	/* 8c008fe8 */
	sint8_t *p;
{
	return (*p);
}

uint32_t
read_int(p)	/* _8c008ffc */
	sint8_t *p;	/* _000c, R15 - 3, R15 */
{
	uint32_t val;	/* _0008, R15 - 2, R15 */
	uint32_t j;	/* _0004, R15 - 1, R15 */

	val = 0;
	j = 0;
	while (j < 4) {
		val = val + (uint8_t)read_byte(p + j) << j*8;
		j++;
	}
	return (val);
}

void
init_graphics(arg)	/* 8c009074 */
	uint32_t arg;
{
	init_graphics2(arg);
}

/* this function is patched before execution starts */
void
set_display(enable)		/* 8c00908c */
	uint32_t enable;
{
	HOLLY->pend0 = 0x00000008;
	while (HOLLY->pend0 != 0x00000008);

	if (enable == 1) {
		/* 8c0090a8 */
		PVR->fb_cfg1 = *(uint32_t *)0x8ced3d24;
		PVR->video_cfg = *(uint32_t *)0x8ced3d18;
		
	} else {
		/* 8c0090c4 */
		PVR->video_cfg = *(uint32_t *)0x8ced3d18 | 0x00000008;
		/* here's the patched version: */
		PVR->fb_cfg1 = *(uint32_t *)0x8ced3d24;
		/* and here's the unpatched one:
		 * PVR->fb_cfg1 = 0x00000000;
		 */
	}
}

uint32_t
init_PVR(arg)		/* 8c0090f8 */
	uint32_t arg;
{
	uint32_t id;
	uint32_t i, fog;

	id = PVR->id;
	PVR->reset = 0x00000000;
	*(uint32_t *)0x8ced3d18 = (sysvars->unknown0<<16) | 0x08;
	*(uint32_t *)0x8ced3d24 = 0x0000000c;

	if (arg == 9) {
		*(uint32_t *)0x8ced3d24 |= 0x00800000;
	}

	PVR->border_col = 0x00c0c0c0;

	set_display(0);

	PVR->spansort_cfg = 0x00000101;
	PVR->fog_table_col = 0x007f7f7f;
	PVR->fog_vertex_col = 0x007f7f7f;
	PVR->fog_density = 0x0000ff07;

	fog = 0xfffe;
	for (i = 0; i < 128; i++) {
		((uint32_t *)&PVR->fog_table)[i] = fog;	/* weird */
		fog = fog - 0x0101;
	}

	PVR->reset = 0x00000001;
	PVR->reset = 0x00000000;

	*HW32(0xa05f6884) = 0x00000000;
	*HW32(0xa05f6888) = 0x00000000;

	return (id);
}

void
set_display_mode_regs(arg)	 /* 8c009214 */
	uint32_t arg;
{
	PVR->ta_opb_start = 0x000c2680;
	PVR->ta_opb_end = 0x0009e800;
	PVR->ta_ob_start = 0x00000000;
	PVR->ta_ob_end = 0x0009e740;
	PVR->tilebuf_size = 0x000e0013;
	PVR->ta_opb_cfg = 0x00100203;
	PVR->ta_opl_start = 0x000c2680;
	PVR->ta_init = 0x80000000;
	PVR->pclip_x = ((*_8ced3d00-1)<<16) & 0x07ff0000;
	PVR->pclip_y = ((*_8ced3d04-1)<<16) & 0x07ff0000;
	PVR->burst_cfg = 0x00093f39;
	PVR->sync_cfg = *(uint32_t *)0x8ced3d44;
	PVR->hborder = *(uint32_t *)0x8ced3d4c;
	PVR->vborder = *(uint32_t *)0x8ced3d50;
	PVR->sync_load = *(uint32_t *)0x8ced3d54;
	PVR->sync_width = *(uint32_t *)0x8ced3d58;
	PVR->render_addr1 = *(uint32_t *)0x8ced3d38;
	PVR->render_addr2 = *(uint32_t *)0x8ced3d40;
	PVR->fb_cfg2 = *(uint32_t *)0x8ced3d28;
	PVR->render_modulo = *(uint32_t *)0x8ced3d2c;
	PVR->display_addr1 = *(uint32_t *)0x8ced3d34;
	PVR->display_addr2 = *(uint32_t *)0x8ced3d3c;
	PVR->display_size = *(uint32_t *)0x8ced3d30;
	PVR->hpos_irq = *(uint32_t *)0x8ced3d48;
	PVR->shadow = 0x00000001;
	PVR->ob_cfg = 0x0027df77;
	PVR->half_offset = 0x00000007;
	PVR->luminance = 0x00008040;
	PVR->object_clip = 0x3f800000;
	PVR->tsp_clip = 0x00000000;
	PVR->bgplane_z = 0.000100;
	PVR->bgplane_cfg = 0x01000000;
	PVR->clamp_max = 0xffffffff;
	PVR->clamp_min = 0xff000000;
	PVR->tsp_cfg = *(uint32_t *)0x8ced3d10;
	PVR->border_col = *(uint32_t *)0x8ced3d14;
	PVR->scaler_cfg = *(uint32_t *)0x8ced3d5c;
}

/* This whole function is skipped because of patching! */
void
clear_display_cable(arg)	/* 8c00940a */
	uint32_t arg;
{
	/* unpatched:
	 * if (arg == 9) {
	 * 	*HW32(0xa0702c00) = *HW32(0xa0702c00) & 0x01;
	 * } else {
	 * 	*HW32(0xa0702c00) = (*HW32(0xa0702c00) & 0x01) | 0x00000300;
	 * }
	 */
}

void
set_display_mode_vars2(displaymode)		/* 8c009488 */
	uint32_t displaymode;	/* 2, R15 */
{
	uint32_t i = 4;		/* 1, R15 */

	*(uint32_t *)0x8ced3d24 = 1;
	*(uint32_t *)0x8ced3d28 = 0;
	*(uint32_t *)0x8ced3d44 = 0x0100;
	*(uint32_t *)0x8ced3d18 = sysvars->unknown0<<16;
	*(uint32_t *)0x8ced3d24 |= 0x0000000c;
	*(uint32_t *)0x8ced3d28 |= 0x00000006;

	/* i'll bet that these are pvr display modes (pal, ntsc, vga) */
	switch (displaymode & 0x0f) {
		case 0x01:
			/* 8c0094f0 */
			displaymode = (displaymode & 0xffffff0f) | 0x00000010;
			*(uint32_t *)0x8ced3d24 |= 0x00800000;
			*(uint32_t *)0x8ced3d48 = 0x03450000;
			*(uint32_t *)0x8ced3d4c = 0x007e0345;
			*(uint32_t *)0x8ced3d50 = 0x00280208;
			*(uint32_t *)0x8ced3d54 = 0x020c0359;
			*(uint32_t *)0x8ced3d58 = 0x03f1933f;
			break;
		case 0x04:
			/* 8c009526 */
			*(uint32_t *)0x8ced3d44 |= 0x00000090;
			*(uint32_t *)0x8ced3d48 = 0x034b0000;
			*(uint32_t *)0x8ced3d4c = 0x008d034b;
			*(uint32_t *)0x8ced3d50 = 0x002c026c;
			*(uint32_t *)0x8ced3d54 = 0x0270035f;
			*(uint32_t *)0x8ced3d58 = 0x07d6a53f;
			break;
		case 0x02:
		default:
			/* 8c009550 */
			*(uint32_t *)0x8ced3d44 |= 0x00000050;
			*(uint32_t *)0x8ced3d48 = 0x03450000;
			*(uint32_t *)0x8ced3d4c = 0x007e0345;
			*(uint32_t *)0x8ced3d50 = 0x00240204;
			*(uint32_t *)0x8ced3d54 = 0x020c0359;
			*(uint32_t *)0x8ced3d58 = 0x07d6c63f;
			break;
	}
	/* 8c0095cc */
	*(uint32_t *)0x8ced3d00 = 640;
	*(uint32_t *)0x8ced3d04 = 480;

	if (displaymode & 0x00000200) {
		*(uint32_t *)0x8ced3d34 = 0x00200000;
		*(uint32_t *)0x8ced3d3c = (640 * i) + 0x00200000;
		*(uint32_t *)0x8ced3d38 = 0x00600000;
		*(uint32_t *)0x8ced3d40 = (640 * i) + 0x00600000;
		*(uint32_t *)0x8ced3d30 = (((640 * i + 1)<<20) & 0x3ff00000)
			| ((((*(uint32_t *)0x8ced3d04>>1) - 1)<<10) & 0x000ffc00)
			| (((640 * i) - 1) & 0x000003ff);
		*(uint32_t *)0x8ced3d5c = 0x00000400;
		*(uint32_t *)0x8ced3d8c = 0x00000000;
	} else {
		/* 8c0096b4 */
		*(uint32_t *)0x8ced3d30 = (((*(uint32_t *)0x8ced3d04 - 1)<<10) & 0x000ffc00)
			| (((640 * i) - 1) & 0x000003ff)
			| 0x00100000;
		*(uint32_t *)0x8ced3d5c = 0x00000400;
		*(uint32_t *)0x8ced3d34 = 0x00200000;
		*(uint32_t *)0x8ced3d3c = 0x00200000;
		*(uint32_t *)0x8ced3d38 = 0x00600000;
		*(uint32_t *)0x8ced3d40 = 0x00600000;
		*(uint32_t *)0x8ced3d8c = 0x00000000;
	}
	/* 8c009704 */
	PVR->vpos_irq = 0x00150104;
	*(uint32_t *)0x8ced3d2c = (*(uint32_t *)0x8ced3d00 * i)/8;
	*(uint32_t *)0x8ced3d08 = (*(uint32_t *)0x8ced3d04 * *(uint32_t *)0x8ced3d2c) * 8;
	*(uint32_t *)0x8ced3d78 = 0x00000000;
	*(uint32_t *)0x8ced3d14 = 0x00c0c0c0;
	*(uint32_t *)0x8ced3d0c = 640;
	*(uint32_t *)0x8ced3d10 = 0x00000000;
}

void
set_display_mode_vars(arg)		/* 8c0097b4 */
	uint32_t arg;
{
	clear_display_cable(arg);

	switch (arg) {
		case 6:
			set_display_mode_vars2(0x00008212);
			break;
		case 8:
			set_display_mode_vars2(0x00008214);
			break;
		case 9:
			set_display_mode_vars2(0x00008111);
			break;
		default:
			set_display_mode_vars2(0x00008212);
			break;
	}

}

void
init_graphics2(arg)	/* 8c009830 */
	int arg;
{
	init_PVR(arg);
	set_display_mode_vars(arg);
	set_display_mode_regs(arg);
}

uint32_t
get_video_mode()	/* 8c009858 */
{
	uint32_t cable;
	uint8_t video;

	cable = get_video_cable();
	video = sysvars->config.video_system;

	if (cable == 0) {
		return (4);
	}

	switch (video) {
		case '0':
			return (0);
			break;
		case '1':
			return (1);
			break;
		case '2':
			return (2);
			break;
		case '3':
			return (3);
			break;
		default:
			return (0);
			break;
	}
}

void
copy_string(buf, string)	/* 8c009c4c */
	uint8_t *buf;
	uint8_t *string;
{
	strcpy(buf, string);		/* passes args in r0,r1 */
}

/* takes args in r0, r1 */
uint8_t *
strcpy(buf, string)		/* _8c009c74 */
	uint8_t *buf;
	uint8_t *string;
{
	uint32_t i = 0;

	/* check for alignment i guess, but both addresses should always be
	 * 32-bit aligned in bootROM */
	if ((buf & 0x03 | string & 0x03) != 0) {
		/* so this should never happen */
		while (1) {
			buf[i] = *string++;
			if (buf[i] == '\0') {
				return (buf);
			}
			buf[i+1] = *string++;
			if (buf[i+1] == '\0') {
				return (buf);
			}
			buf[i+2] = *string++;
			if (buf[i+2] == '\0') {
				return (buf);
			}
			buf[i+3] = *string++;
			if (buf[i+3] == '\0') {
				return (buf);
			}
		}
	}
	/* 8c009cb8 */
	/* weird here, skips first two instructions of a function :/ */
	strcpy4+4(buf, string);

}

/* it seems this will just make a 32-bit copy instead */
void
strcpy4(buf, string)		/* 8c009cc4 */
	uint32_t *buf;
	uint32_t *string;
{
	uint32_t val;

	if (*string == 0x00000000) {
	}
}

uint32_t
strlen(s)		/* 8c009c62 */
	uint8_t *s;
{
	uint32_t n = 0;

	while (*s++) {
		n++;
	}
	return (n);
}

void
init_timer()		/* 8c009dec */
{
	reg[TOCR] = 0x00;
	reg[TSTR] = reg[TSTR] & 0xfe;
	reg[TCR0] = 0x0002;
	reg[TCOR0] = 0xffffffff;
	reg[TCNT0] = 0xffffffff;
	reg[TSTR] = reg[TSTR] | 0x01;
}

uint32_t
get_timer()	/* 8c009e12 */
{
	return (0xffffffff - *(volatile uin32_t *)0xffd8000c);
}

uint32_t
get_time_difference(time1, time2)	/* 8c009e1c */
	uint32_t time1, time2;
{
	return (time2, time1);
}

uint32_t
convert_time(time)		/* 8c009e24 */
	uint32_t time;
{
	/* WORK TO DO HERE */
}


/*******************************************************************************
 *
 * END OF IP.BIN
 *
 ******************************************************************************/
