#ifndef __KMGENC_H
#define __KMGENC_H

// Some useful global headers
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <errno.h>

// For outputting KMG files
#define NEED_KOS_TYPES
#include "../../addons/include/kmg/kmg.h"

// A single color value
typedef struct fcolor {
	float a;
	float r;
	float g;
	float b;
} fcolor_t;

// A few useful macros for color manipulation
#define PACK4444(a, r, g, b) ( \
	( (((int)((a)*15))) << 12) | \
	( (((int)((r)*15))) << 8) | \
	( (((int)((g)*15))) << 4) | \
	( (((int)((b)*15))) << 0) )

#define PACK1555(a, r, g, b) ( \
	( ((a) ? 0x8000 : 0x0000) | \
	( (((int)((r)*31))) << 10) | \
	( (((int)((g)*31))) << 5) | \
	( (((int)((b)*31))) << 0) )

#define PACK565(r, g, b) ( \
	( (((int)((r)*31))) << 11) | \
	( (((int)((g)*63))) << 5) | \
	( (((int)((b)*31))) << 0) )

#define LIMIT(x, low, high) (x) < low ? low : (x) > high ? high : (x)

#define LIMITFC(x) do { \
		(x).a = LIMIT((x).a, 0.0f, 1.0f); \
		(x).r = LIMIT((x).r, 0.0f, 1.0f); \
		(x).g = LIMIT((x).g, 0.0f, 1.0f); \
		(x).b = LIMIT((x).b, 0.0f, 1.0f); \
	} while (0)

static inline void get_fcolor_24(fcolor_t *c, uint8 *pixels) {
	c->a = 1.0f;
	c->r = pixels[0] / 255.0f;
	c->g = pixels[1] / 255.0f;
	c->b = pixels[2] / 255.0f;
}
static inline void get_fcolor_32(fcolor_t *c, uint8 *pixels) {
	c->a = pixels[0] / 255.0f;
	c->r = pixels[1] / 255.0f;
	c->g = pixels[2] / 255.0f;
	c->b = pixels[3] / 255.0f;
}

// Endian fixing
static int is_le = -1;

static inline int le_detect() {
	if (is_le == -1) {
		unsigned long test = 0x12345678;
		unsigned char * tp = (unsigned char *)&test;
		if (*tp == 0x78)
			/* Little endian */
			is_le = 1;
		else
			/* Big endian */
			is_le = 0;
	}
	return is_le;
}

static inline int le16(int x) {
	if (le_detect())
		return x;
	else
		return ((x << 8) & 0xff00) | ((x >> 8) & 0x00ff);
}

static inline int le32(int x) {
	uint32 val = *((uint32 *)&x);
	if (le_detect())
		return x;
	else
		return ((val << 24) & 0xff000000) |
			((val << 8) & 0x00ff0000) |
			((val >> 8) & 0x0000ff00) |
			((val >> 24) & 0x000000ff);
}

// Internal includes
#include "get_image.h"


#endif // __KMGENC_H
