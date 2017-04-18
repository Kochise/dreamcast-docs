/*
 * draw.c - conio drawing funcs:  mainly font routines borrowed from JAM.
 */

/* #include <os/abi/ta.h> */
#include "kosh.h"
#include "conio.h"
#include "draw.h"

/* the color theme */
int draw_theme = THEME_PLAIN;

/* the font texture */
uint32 font_texture = 0;

/* initialize draw stuff: get our texture of the font, etc */
void draw_init() {
	uint16 *vram;
	int x, y;

	font_texture = 0;
	vram = (uint16 *) ta_txr_map(font_texture);

	for (y = 0; y < 8; y++) {
		for (x = 0; x < 16; x++) {
			bfont_draw(vram, 256, 0, y*16 + x);
			vram += 16;
		}
		vram += 23*256;
	}
	
}

/* Draw one font character (6x12) */
static void draw_char(float x1, float y1, float z1, float a, float r,
		float g, float b, int c) {
	vertex_ot_t	vert;
	int ix, iy;
	float u1, v1, u2, v2;

	if (c == ' ')
		return;
	
	ix = (c % 16) * 16;
	iy = (c / 16) * 24;
	u1 = ix * 1.0f / 256.0f;
	v1 = iy * 1.0f / 256.0f;
	u2 = (ix+12) * 1.0f / 256.0f;
	v2 = (iy+24) * 1.0f / 256.0f;

	vert.flags = TA_VERTEX_NORMAL;
	vert.x = x1;
	//vert.y = y1 + 16.0f;
	vert.y = y1 + FONT_HEIGHT;
	vert.z = z1;
	vert.u = u1;
	vert.v = v2;
	vert.dummy1 = vert.dummy2 = 0;
	vert.a = a;
	vert.r = r;
	vert.g = g;
	vert.b = b;
	vert.oa = vert.or = vert.og = vert.ob = 0.0f;
	ta_commit_vertex(&vert, sizeof(vert));
	
	vert.x = x1;
	vert.y = y1;
	vert.u = u1;
	vert.v = v1;
	ta_commit_vertex(&vert, sizeof(vert));
	
	vert.x = x1 + FONT_WIDTH;
	//vert.y = y1 + 16.0f;
	vert.y = y1 + FONT_HEIGHT;
	vert.u = u2;
	vert.v = v2;
	ta_commit_vertex(&vert, sizeof(vert));

	vert.flags = TA_VERTEX_EOL;
	vert.x = x1 + FONT_WIDTH;
	vert.y = y1;
	vert.u = u2;
	vert.v = v1;
	ta_commit_vertex(&vert, sizeof(vert));
}

/* draw len chars at string */
static void draw_string(float x, float y, float z, float a, float r, float g,
		float b, char *str, int len) {
	int i;
	poly_hdr_t poly;
	
	ta_poly_hdr_txr(&poly, TA_TRANSLUCENT, TA_ARGB4444, 256, 256, font_texture, 0 /* TA_BILINEAR_FILTER */);
	ta_commit_poly_hdr(&poly);

	for (i = 0; i < len; i++) {
		draw_char(x, y, z, a, r, g, b, str[i]);
		x += FONT_WIDTH;
	}
}

/* draw a box (used by cursor and border, etc) (at 1.0f z coord) */
static void draw_box(float x, float y, float w, float h, float a, float r, float g, float b) {
	poly_hdr_t poly;
	vertex_oc_t vert;

	ta_poly_hdr_col(&poly, TA_TRANSLUCENT);
	ta_commit_poly_hdr(&poly);

	vert.flags = TA_VERTEX_NORMAL;
	vert.x = x;
	vert.y = y;
	vert.z = 1.0f;
	vert.a = a;
	vert.r = r; vert.g = g; vert.b = b;
	ta_commit_vertex(&vert, sizeof(vert));

	vert.x += w;
	ta_commit_vertex(&vert, sizeof(vert));

	vert.y += h;
	ta_commit_vertex(&vert, sizeof(vert));
	ta_commit_vertex(&vert, sizeof(vert));
	vert.y -= h;
	vert.x -= w;
	ta_commit_vertex(&vert, sizeof(vert));

	vert.flags = TA_VERTEX_EOL;
	vert.y += h;
	ta_commit_vertex(&vert, sizeof(vert));

}

/* draw the border around the screen etc */
static void draw_border(float r, float g, float b) {
	draw_box(0, 0, SCREEN_FIRSTCOL - 1, SCREEN_HEIGHT, 1.0f, r, g, b);
	draw_box(SCREEN_LASTCOL, 0, SCREEN_WIDTH - SCREEN_LASTCOL, SCREEN_HEIGHT, 1.0f, r, g, b);
	draw_box(0, 0, SCREEN_WIDTH, FONT_HEIGHT, 1.0f, r, g, b);
	draw_box(0, SCREEN_HEIGHT - FONT_HEIGHT, SCREEN_WIDTH, FONT_HEIGHT, 1.0f, r, g, b);
}

static void draw_middle(float r, float g, float b) {
	draw_box(SCREEN_FIRSTCOL, FONT_HEIGHT, FONT_WIDTH * NUM_COLS, FONT_HEIGHT * NUM_ROWS, 1.0f, r, g, b);
}

/* draw the virtual screen */
static void draw_virtscr(float a, float r, float g, float b) {
	int i;

	for (i = 0; i < NUM_ROWS; i++) {
		draw_string(SCREEN_FIRSTCOL, (i + 1) * FONT_HEIGHT, 1.0f, a, r, g, b,
			virtscr[i], NUM_COLS);
	}
}

/* draw the cursor */
static float c_alpha = 1.0f, c_dalpha = -0.1f;
static void draw_cursor(float r, float g, float b) {
	poly_hdr_t poly;
	vertex_oc_t vert;

	/* modify our alpha to give a little fading effect */
	c_alpha += c_dalpha;
	if (c_alpha >= 1.0f || c_alpha <= 0.0f)
		c_dalpha = -c_dalpha;

	draw_box(cursor.col * FONT_WIDTH + SCREEN_FIRSTCOL, (cursor.row + 1) * FONT_HEIGHT, FONT_WIDTH, FONT_HEIGHT,
		c_alpha, r, g, b);
}

/* our exported drawing function: does a full redraw of everything */
void draw_frame() {
	ta_begin_render();

	/* dummy polygon */
	{
		poly_hdr_t poly;
		ta_poly_hdr_col(&poly, TA_OPAQUE);
		ta_commit_poly_hdr(&poly);
	}
	

	ta_commit_eol();

	switch (draw_theme) {
		case THEME_C64:
			draw_border(0.4f, 0.6f, 0.98f);
			draw_middle(0.0f, 0.0f, 1.0f);
			draw_virtscr(1.0f, 1.0f, 1.0f, 1.0f);
			draw_cursor(0.4f, 0.6f, 0.98f);
			break;
		case THEME_MATRIX:
			draw_virtscr(1.0f, 0.0f, 1.0f, 0.0f);
			draw_cursor(0.0f, 0.7f, 0.0f);
			break;
		case THEME_PLAIN:
		default:
			draw_virtscr(1.0f, 1.0f, 1.0f, 1.0f);
			draw_cursor(1.0f, 1.0f, 1.0f);
			break;
	}
	
	ta_commit_eol();
	ta_finish_frame();
}


