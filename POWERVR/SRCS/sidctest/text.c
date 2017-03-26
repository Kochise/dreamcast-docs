/* Adapted from Dan Potter's Tryptonite code

   text.c
   (c)2000 Dan Potter

   Text functions 
*/

static char id[] = "xxx";


#include <string.h>
#include <kos.h>
#include "text.h"

static uint32 menu_fnt;

static int ch_throb;


/********************************************************************************/

#define FONT_NAME tryptofont_base_pcx
#define FONT_WIDTH 16
#define FONT_HEIGHT 20
#define FONT_PIC_WIDTH 256
#define FONT_PIC_HEIGHT 256
#define FONT_DOUBLE 1.0f
char font_map[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.:!?[]'\"-+=^/\\# ";
#undef FONT_HAS_LC


#define FONT_PERROW (FONT_PIC_WIDTH / FONT_WIDTH)
#define FONT_ROWS (480 / FONT_HEIGHT)

static char charmap[256];

/* Draws a font letter using two triangle strips */
void font_draw_char(float x1, float y1, float z, float a, float r, float g, float b, int ch) {
	int index = charmap[ch];
	int ix = (index % FONT_PERROW) * FONT_WIDTH;
	int iy = (index / FONT_PERROW) * FONT_HEIGHT;
	float u1 = ix * 1.0f / FONT_PIC_WIDTH;
	float v1 = iy * 1.0f / FONT_PIC_HEIGHT;
	float u2 = (ix+FONT_WIDTH) * 1.0f / FONT_PIC_WIDTH;
	float v2 = (iy+FONT_HEIGHT) * 1.0f / FONT_PIC_HEIGHT;
	vertex_ot_t vert;

	if (index == -1)
		return;

	vert.flags = TA_VERTEX_NORMAL;
	vert.x = x1; vert.y = y1 + FONT_HEIGHT*FONT_DOUBLE;
	vert.z = 512.0f + z;
	vert.u = u1; vert.v = v2;
	vert.a = a; vert.r = r; vert.g = g; vert.b = b;
	vert.oa = vert.or = vert.og = vert.ob = 0.0f;
	ta_commit_vertex(&vert, sizeof(vert));
	
	vert.x = x1; vert.y = y1;
	vert.u = u1; vert.v = v1;
	ta_commit_vertex(&vert, sizeof(vert));
	
	vert.x = x1 + FONT_WIDTH*FONT_DOUBLE; vert.y = y1 + FONT_HEIGHT*FONT_DOUBLE;
	vert.u = u2; vert.v = v2;
	ta_commit_vertex(&vert, sizeof(vert));

	vert.flags = TA_VERTEX_EOL;
	vert.x = x1 + FONT_WIDTH*FONT_DOUBLE; vert.y = y1;
	vert.u = u2; vert.v = v1;
	ta_commit_vertex(&vert, sizeof(vert));
}

void font_draw_string(float x1, float y1, float z, float a, float r, float g, float b, char *str) {
	/* Start a textured polygon set (with the font texture) */
	poly_hdr_t poly;
	ta_poly_hdr_txr(&poly, TA_TRANSLUCENT, TA_ARGB4444_TWID, 256, 256, menu_fnt, TA_BILINEAR_FILTER);
	ta_commit_poly_hdr(&poly);

	while (*str) {
		font_draw_char(x1, y1, z, a, r, g, b, *str++);
		x1 += (int)(FONT_WIDTH*FONT_DOUBLE+1);
	}
}

void font_draw_string_bouncy(float x1, float y1, float z, float a, float r, float g, float b, char *str) {
	int i;
	float yo;
	
	/* Start a textured polygon set (with the font texture) */
	poly_hdr_t poly;
	ta_poly_hdr_txr(&poly, TA_TRANSLUCENT, TA_ARGB4444_TWID, 256, 256, menu_fnt, TA_BILINEAR_FILTER);
	ta_commit_poly_hdr(&poly);

	i = 0;
	while (*str) {
		if (i % 2)
			yo = icos(ch_throb)*3.0f;
		else
			yo = isin(ch_throb)*3.0f;
		i++;
		
		font_draw_char(x1, y1+yo, z, a, r, g, b, *str++);
		x1 += (int)(FONT_WIDTH*FONT_DOUBLE+1);
	}
}

void font_throb() {
	ch_throb = (ch_throb + 24) % 1024;
}


#if 0
/* Debug code to draw the font texture */
void blit_font_texture() {
	vertex_ot_t vert;
	
	vert.flags = TA_VERTEX_NORMAL;
	vert.x = 50.0f;
	vert.y = 50.0f + 512.0f;
	vert.z = 512.0f;
	vert.u = 0.0f;
	vert.v = 1.0f;
	vert.a = 0.6f; vert.r = 1.0f; vert.g = 1.0f; vert.b = 1.0f;
	vert.oa = vert.or = vert.og = vert.ob = 0.0f;
	ta_commit_vertex(&vert, sizeof(vert));

	vert.x = 50.0f;
	vert.y = 50.0f;
	vert.u = 0.0f;
	vert.v = 0.0f;
	ta_commit_vertex(&vert, sizeof(vert));

	vert.x = 50.0f + 512.0f;
	vert.y = 50.0f + 512.0f;
	vert.u = 1.0f;
	vert.v = 1.0f;
	ta_commit_vertex(&vert, sizeof(vert));

	vert.flags = TA_VERTEX_EOL;
	vert.x = 50.0f + 512.0f;
	vert.y = 50.0f;
	vert.u = 1.0f;
	vert.v = 0.0f;
	ta_commit_vertex(&vert, sizeof(vert));
	
	return;
}
#endif

#undef tolower(c)
#define tolower(c) ((c) >= 'A' && (c) <='Z' ? (c)+('a' - 'A') : (c))

static void font_init() {
	int c;

	for (c=0; c<255; c++)
		charmap[c] = -1;
	for (c=0; c<strlen(font_map); c++) {
		charmap[(int)font_map[c]] = c;
#ifndef FONT_HAS_LC
		charmap[tolower(font_map[c])] = c;
#endif
	}
	charmap[' '] = -1;
}

/* Convert the font bitmap from RGB565 to ARGB4444 (use RGB565 as an alpha mask) */
void font_conv_bitmap(Image *i) {
	int x, y, val;
	
	for (y=0; y<i->height; y++)
		for (x=0; x<i->width; x++) {
			/* Grab RGB565 value and convert it to grayscale (use green) */
			val = i->pixel_data[y*i->width+x];
			val = ((val >> 5) & 63);
			
			/* Convert to ARGB4444 (all white, above == alpha) */
			val = ((val >> 2) << 12) | 0x0fff;
			i->pixel_data[y*i->width+x] = val;
		}
}

/********************************************************************************/

/* Load up the texture data */
static int menu_load_txrs() {
	Image	*img;
	

	/* Load font image */
	img = pcx_load("/rd/tryptofont_base.pcx");
	if (img == NULL) {
		printf("Can't load menu font\r\n");
		return -1;
	}
	
	/* Twiddle it into PVR mem as 256x256 */
	font_conv_bitmap(img);
	txr_twiddle_copy(img->pixel_data, img->width, img->height,
		menu_fnt, 256, 256, 0);
	/* Free the image */
	pcx_free(img);
	
	/* Finish initializing font support */
	font_init();
	
	return 0;
}

int text_init() {

	/* Load the texture data */
	if (menu_load_txrs() < 0)
		return -1;

	return 0;
}

/* vi:tabstop=4
*/
