/* GhettoPlay: an S3M browser and playback util
   (c)2000 Dan Potter
*/

#include <stdarg.h>
#include <stdio.h>
#include "gp.h"

#include "sintab.h"

/* Some misc 3D utils */

/* Rotate a 3-pair of coordinates by the given angle 0..255 */
void rotate(int zang, int xang, int yang, float *x, float *y, float *z) {
	float tx, ty, tz;
	
	tx = (mcos(zang)* *x - msin(zang)* *y);
	ty = (mcos(zang)* *y + msin(zang)* *x);
	*x = tx; *y = ty;
		
	tz = (mcos(xang)* *z - msin(xang)* *y);
	ty = (mcos(xang)* *y + msin(xang)* *z);
	*y = ty; *z = tz;

	tx = (mcos(yang)* *x - msin(yang)* *z);
	tz = (mcos(yang)* *z + msin(yang)* *x);
	*x = tx; *z = tz;
}

/* Draw the mouse cursor at the given location */
void draw_poly_mouse(int ptrx, int ptry) {
	poly_hdr_t	poly;
	vertex_ot_t	vert;
	
	/* Start a textured polygon set (with the font texture) */
	ta_poly_hdr_txr(&poly, TA_TRANSLUCENT, TA_ARGB4444, 256, 256,
		util_texture, TA_NO_FILTER);
	ta_commit_poly_hdr(&poly);

	vert.flags = TA_VERTEX_NORMAL;
	vert.x = ptrx;
	vert.y = ptry + 16.0f;
	vert.z = 512.0f;
	vert.u = 0.0f;
	vert.v = 16.0f / 256.0f;
	vert.dummy1 = vert.dummy2 = 0;
	vert.a = 0.80f;
	vert.r = 1.0f;
	vert.g = 1.0f;
	vert.b = 1.0f;
	vert.oa = vert.or = vert.og = vert.ob = 0.0f;
	ta_commit_vertex(&vert, sizeof(vert));
	
	vert.x = ptrx;
	vert.y = ptry;
	vert.u = 0.0f;
	vert.v = 0.0f;
	ta_commit_vertex(&vert, sizeof(vert));
	
	vert.x = ptrx + 10.0f;
	vert.y = ptry + 16.0f;
	vert.u = 10.0f / 256.0f;
	vert.v = 16.0f / 256.0f;
	ta_commit_vertex(&vert, sizeof(vert));

	vert.flags = TA_VERTEX_EOL;
	vert.x = ptrx + 10.0f;
	vert.y = ptry;
	vert.u = 10.0f / 256.0f;
	vert.v = 0.0f;
	ta_commit_vertex(&vert, sizeof(vert));
}

/* Draw one font character (12x24); assumes polygon header already sent */
void draw_poly_char(float x1, float y1, float z1, float a, float r, float g, float b, int c) {
	vertex_ot_t	vert;
	int ix = (c % 16) * 16;
	int iy = (c / 16) * 24;
	float u1 = ix * 1.0f / 256.0f;
	float v1 = iy * 1.0f / 256.0f;
	float u2 = (ix+12) * 1.0f / 256.0f;
	float v2 = (iy+24) * 1.0f / 256.0f;

	vert.flags = TA_VERTEX_NORMAL;
	vert.x = x1;
	vert.y = y1 + 24.0f;
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
	
	vert.x = x1 + 12.0f;
	vert.y = y1 + 24.0f;
	vert.u = u2;
	vert.v = v2;
	ta_commit_vertex(&vert, sizeof(vert));

	vert.flags = TA_VERTEX_EOL;
	vert.x = x1 + 12.0f;
	vert.y = y1;
	vert.u = u2;
	vert.v = v1;
	ta_commit_vertex(&vert, sizeof(vert));
}

/* Draw a set of textured polygons at the given depth and color that
   represent a string of text. */
static char strbuf[1024];
void draw_poly_strf(float x1, float y1, float z1, float a, float r,
		float g, float b, char *fmt, ...) {
	va_list args;
	char *s;
	poly_hdr_t poly;
	
	va_start(args, fmt);
	vsprintf(strbuf, fmt, args);
	va_end(args);

	ta_poly_hdr_txr(&poly, TA_TRANSLUCENT, TA_ARGB4444, 256, 256, util_texture, TA_NO_FILTER);
	ta_commit_poly_hdr(&poly);
	s = strbuf;
	while (*s) {
		if (*s == ' ') {
			x1 += 12.0f; s++;
		} else {
			draw_poly_char(x1+=12.0f, y1, z1, a, r, g, b, *s++);
		}
	}
}


/* Draw a polygon for a shaded box; wow, a nasty looking func =) */
void draw_poly_box(float x1, float y1, float x2, float y2, float z,
		float a1, float r1, float g1, float b1,
		float a2, float r2, float g2, float b2) {
	poly_hdr_t poly;
	vertex_oc_t vert;
	
	ta_poly_hdr_col(&poly, TA_TRANSLUCENT);
	ta_commit_poly_hdr(&poly);
	
	vert.flags = TA_VERTEX_NORMAL;
	vert.x = x1; vert.y = y2; vert.z = z;
	vert.a = (a1+a2)/2; vert.r = (r1+r2/2); vert.g = (g1+g2)/2; vert.b = (b1+b2)/2;
	ta_commit_vertex(&vert, sizeof(vert));
	
	vert.y = y1;
	vert.a = a1; vert.r = r1; vert.g = g1; vert.b = b1;
	ta_commit_vertex(&vert, sizeof(vert));
	
	vert.x = x2; vert.y = y2;
	vert.a = a2; vert.r = r2; vert.g = g2; vert.b = b2;
	ta_commit_vertex(&vert, sizeof(vert));
	
	vert.flags = TA_VERTEX_EOL;
	vert.y = y1;
	vert.a = (a1+a2)/2; vert.r = (r1+r2/2); vert.g = (g1+g2)/2; vert.b = (b1+b2)/2;
	ta_commit_vertex(&vert, sizeof(vert));
}









