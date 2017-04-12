#ifndef __GP_H
#define __GP_H

#include <kos.h>

/* Floating-point Sin/Cos; 256 angles, -1.0 to 1.0 */
extern float sintab[];
#define msin(angle) sintab[angle]
#define mcos(angle) sintab[((angle)+64) % 256]

/* ghettoplay.c */
void play_s3m(char *fn);

/* bkg.c */
void bkg_setup();
void bkg_render();

/* texture.c */
extern uint32 util_texture;
uint32 texture_alloc(uint32 size);
void setup_util_texture();

/* 3dutils.c */
void rotate(int zang, int xang, int yang, float *x, float *y, float *z);
void draw_poly_mouse(int ptrx, int ptry);
void draw_poly_char(float x1, float y1, float z1, float a, float r, float g, float b, int c);
void draw_poly_strf(float x1, float y1, float z1, float a, float r, float g, float b, char *fmt, ...);
void draw_poly_box(float x1, float y1, float x2, float y2, float z,
		float a1, float r1, float g1, float b1,
		float a2, float r2, float g2, float b2);

/* songmenu.c */
void song_menu_render();

#endif	/* __GP_H */
