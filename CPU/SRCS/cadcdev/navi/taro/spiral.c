/* Taro ##version##
   
   spiral.c
   
   (c)2002 Dan Potter
*/

#include "taro.h"

static pvr_ptr_t txr_dot, txr_logo_l, txr_logo_r;
static float phase;
static int frame;

static void load_txr(const char *fn, pvr_ptr_t *txr) {
	kos_img_t img;
	if (png_to_img(fn, PNG_FULL_ALPHA, &img) < 0)
		assert(false);
	printf("Loaded %s: %dx%d, format %d\n",
		fn, img.w, img.h, img.fmt);

	assert((img.fmt & KOS_IMG_FMT_MASK) == KOS_IMG_FMT_ARGB4444);
	*txr = pvr_mem_malloc(img.w * img.h * 2);
	pvr_txr_load_kimg(&img, *txr, 0);
	kos_img_free(&img, 0);
}

static void draw_one_dot(float x, float y, float z) {
	pvr_vertex_t	v;

	v.flags = PVR_CMD_VERTEX;
	v.x = x-32.0/2;
	v.y = y+32.0/2;
	v.z = z;
	v.u = 0.0f; v.v = 1.0f;
	v.argb = 0xff3370d4;
	// v.argb = 0xffffffff;
	v.oargb = 0;
	pvr_prim(&v, sizeof(v));

	v.y = y-32.0/2;
	v.v = 0.0f;
	pvr_prim(&v, sizeof(v));

	v.x = x+32.0/2;
	v.y = y+32.0/2;
	v.u = 1.0f;
	v.v = 1.0f;
	pvr_prim(&v, sizeof(v));

	v.flags = PVR_CMD_VERTEX_EOL;
	v.y = y-32.0/2;
	v.v = 0.0f;
	pvr_prim(&v, sizeof(v));
}

static void draw_spiral(float phase) {
	pvr_poly_hdr_t	hdr;
	pvr_poly_cxt_t	cxt;
	float		x, y, t, r, z, scale;

	pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY,
		PVR_TXRFMT_ARGB4444, 32, 32, txr_dot, PVR_FILTER_BILINEAR);
	pvr_poly_compile(&hdr, &cxt);
	pvr_prim(&hdr, sizeof(hdr));

	for (z=1.0f, r=15.0, t=M_PI/2 - M_PI/4 + phase; t<(6*M_PI+phase); ) {
		x = r*fcos(t); y = r*fsin(t);
		draw_one_dot(320 + x, 189 + y, z);

		scale = 12.0f - 11.0f * ((t-phase) / (6*M_PI));
		t+=scale*2*M_PI/360.0;
		r+=scale*0.6f/(2*M_PI);
		z+=0.1f;
	}
}

static void draw_logo() {
	pvr_poly_hdr_t	hdr;
	pvr_poly_cxt_t	cxt;
	pvr_vertex_t	v;
	float		x, y;
	static int 	frame = 0;

	pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY,
		PVR_TXRFMT_ARGB4444, 256, 256, txr_logo_l, PVR_FILTER_BILINEAR);
	pvr_poly_compile(&hdr, &cxt);
	pvr_prim(&hdr, sizeof(hdr));

	x = 310.0f;
	y = 330.0f;
	v.flags = PVR_CMD_VERTEX;
	v.x = x - 256.0f;
	v.y = y + 256.0f;
	v.z = 0.5f;
	v.u = 0.0f; v.v = 1.0f;
	v.argb = 0xffffffff;
	v.oargb = 0;
	pvr_prim(&v, sizeof(v));

	v.y = y;
	v.v = 0.0f;
	pvr_prim(&v, sizeof(v));

	v.x = x;
	v.y = y + 256.0f;
	v.u = 1.0f;
	v.v = 1.0f;
	pvr_prim(&v, sizeof(v));

	v.flags = PVR_CMD_VERTEX_EOL;
	v.y = y;
	v.v = 0.0f;
	pvr_prim(&v, sizeof(v));

	pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY,
		PVR_TXRFMT_ARGB4444, 256, 256, txr_logo_r, PVR_FILTER_BILINEAR);
	pvr_poly_compile(&hdr, &cxt);
	pvr_prim(&hdr, sizeof(hdr));

	v.flags = PVR_CMD_VERTEX;
	v.x = x;
	v.y = y + 256.0f;
	v.z = 0.5f;
	v.u = 0.0f; v.v = 1.0f;
	v.argb = 0xffffffff;
	v.oargb = 0;
	pvr_prim(&v, sizeof(v));

	v.y = y;
	v.v = 0.0f;
	pvr_prim(&v, sizeof(v));

	v.x = x + 256.0f;
	v.y = y + 256.0f;
	v.u = 1.0f;
	v.v = 1.0f;
	pvr_prim(&v, sizeof(v));

	v.flags = PVR_CMD_VERTEX_EOL;
	v.y = y;
	v.v = 0.0f;
	pvr_prim(&v, sizeof(v));
}

int spiral_init() {
	load_txr("/rd/dot.png", &txr_dot);
	load_txr("/rd/logo-left.png", &txr_logo_l);
	load_txr("/rd/logo-right.png", &txr_logo_r);

	phase = 0.0f;
	frame = 0;
	
	return 0;
}

/* Call during trans poly */
void spiral_frame() {
	draw_spiral(phase);
	draw_logo();

	frame++;
	phase = 2*M_PI * fsin(frame * 2*M_PI / 360.0f);
}

