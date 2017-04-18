/* GhettoPlay: an S3M browser and playback util
   (c)2000 Dan Potter
*/

#include "gp.h"


/* This module will manage the spiffy background effects */

static int ang = 0;
static uint32 chktexture = 0;
static float horizon = 340.0f;

/* Make a nice (now familiar =) XOR pattern texture */
void bkg_setup() {
	int x, y;
	uint16 *texture;
	
	chktexture = ta_txr_allocate(64*64*2);
	texture = (uint16*)ta_txr_map(chktexture);
	for (y=0; y<64; y++)
		for (x=0; x<64; x++) {
			int v = ((x*4)^(y*4)) & 255;
			*texture++ = ((v >> 3) << 11)
				| ((v >> 2) << 5)
				| ((v >> 3) << 0); 
		}
}

/* Draws the floor polygon */
static void draw_floor_poly() {
	vertex_ot_t vert;
	float u2 = 0.374f, j = 0.0f;

	vert.flags = TA_VERTEX_NORMAL;
	vert.x = 0.0f; vert.y = 480.0f; vert.z = 64.0f;
	vert.u = u2 - 0.5f; vert.v = 1.0f - 0.5f;
	rotate(ang, 0, 0, &vert.u, &vert.v, &j);
	vert.u += 0.5f; vert.v += 0.5f;
	vert.dummy1 = vert.dummy2 = 0;
	vert.a = 1.0f; vert.r = 0.2f; vert.g = 1.0f; vert.b = 1.0f;
	vert.oa = vert.or = vert.og = vert.ob = 0.0f;
	ta_commit_vertex(&vert, sizeof(vert));

	vert.x = 0.0f; vert.y = horizon; vert.z = 16.0f;
	vert.u = 0.0f - 0.5f; vert.v = 0.0f - 0.5f;
	rotate(ang, 0, 0, &vert.u, &vert.v, &j);
	vert.u += 0.5f; vert.v += 0.5f;
	vert.a = 1.0f; vert.r = 0.5f; vert.g = 0.3f; vert.b = 1.0f;
	ta_commit_vertex(&vert, sizeof(vert));

	vert.x = 640.0f; vert.y = 480.0f; vert.z = 64.0f;
	vert.u = (1.0f - u2) - 0.5f; vert.v = 1.0f - 0.5f;
	rotate(ang, 0, 0, &vert.u, &vert.v, &j);
	vert.u += 0.5f; vert.v += 0.5f;
	vert.a = 1.0f; vert.r = 0.2f; vert.g = 1.0f; vert.b = 1.0f;
	ta_commit_vertex(&vert, sizeof(vert));

	vert.flags = TA_VERTEX_EOL;
	vert.x = 640.0f; vert.y = horizon; vert.z = 16.0f;
	vert.u = 1.0f - 0.5f; vert.v = 0.0f - 0.5f;
	rotate(ang, 0, 0, &vert.u, &vert.v, &j);
	vert.u += 0.5f; vert.v += 0.5f;
	vert.a = 1.0f; vert.r = 0.5f; vert.g = 0.3f; vert.b = 1.0f;
	ta_commit_vertex(&vert, sizeof(vert));
}

/* Draws the "wall" polygon */
static void draw_wall_poly() {
	vertex_oc_t vertc;

	vertc.flags = TA_VERTEX_NORMAL;
	vertc.x = 0.0f; vertc.y = horizon; vertc.z = 64.0f;
	vertc.a = 1.0f; vertc.r = 0.5f; vertc.g = 0.3f; vertc.b = 1.0f;
	ta_commit_vertex(&vertc, sizeof(vertc));
	
	vertc.x = 0.0f; vertc.y = 0.0f; vertc.z = 64.0f;
	vertc.a = 1.0f; vertc.r = 0.0f; vertc.g = 0.0f; vertc.b = 0.0f;
	ta_commit_vertex(&vertc, sizeof(vertc));

	vertc.x = 640.0f; vertc.y = horizon; vertc.z = 64.0f;
	vertc.a = 1.0f; vertc.r = 0.5f; vertc.g = 0.3f; vertc.b = 1.0f;
	ta_commit_vertex(&vertc, sizeof(vertc));
	
	vertc.flags = TA_VERTEX_EOL;
	vertc.x = 640.0f; vertc.y = 0.0f; vertc.z = 64.0f;
	vertc.a = 1.0f; vertc.r = 0.0f; vertc.g = 0.0f; vertc.b = 0.0f;
	ta_commit_vertex(&vertc, sizeof(vertc));
}

void bkg_render() {
	poly_hdr_t poly;
	
	/* "floor" polygon */
	ta_poly_hdr_txr(&poly, TA_OPAQUE, TA_RGB565, 64, 64, chktexture,
		TA_BILINEAR_FILTER);
	ta_commit_poly_hdr(&poly);

	draw_floor_poly();
	
	/* "wall" polygon */
	ta_poly_hdr_col(&poly, TA_OPAQUE);
	ta_commit_poly_hdr(&poly);
	
	draw_wall_poly();

	
	ang = (ang-1) & 255;
}

