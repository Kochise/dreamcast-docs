/* This program is a slight modification of the libdream/ta example program.
   The big difference in this program is that we add in a small bit of user
   input code, and support render-to-texture mode. */

/* This is a port of my original 3dtest example to KOS. The big difference
   here is that the background plane is no longer used. */

#include <kos.h>

/* A little test program -- creates twelve rainbow polygons and
   moves them around over a color-shifting background. */
typedef struct {
	float	x, y, z;
	float	dx, dy;
} polyplace_t;

polyplace_t polys[6] = {
	{ 16.0f, 0.0f, 10.0f, 3.0f, 5.0f },
	{ 624.0f, 0.0f, 12.0f, -3.0f, 7.0f },
	{ 24.0f, 300.0f, 13.0f, 3.0f, -7.0f },
	{ 0.0f, 16.0f, 16.0f, 5.0f, 3.0f },
	{ 0.0f, 364.0f, 18.0f, 7.0f, -3.0f },
	{ 480.0f, 24.0f, 19.0f, -7.0f, 3.0f },
};

/* Does one frame of polygon movement */
void move_polys() {
	int i;
	polyplace_t *p;
	
	for (i=0; i<12; i++) {
		p = polys+i;
		
		p->x += p->dx;
		if (p->x < 0 || p->x > 580.0f) {
			p->dx = -p->dx;
			p->x += p->dx;
		}

		p->y += p->dy;
		if (p->y < 0 || p->y > 420.0f) {
			p->dy = -p->dy;
			p->y += p->dy;
		}
	}
}

/* Sends one polygon's worth of data to the TA */
void draw_one_poly(polyplace_t *p) {
	/* Opaque Colored vertex */
	pvr_vertex_t vert;
	
	vert.flags = PVR_CMD_VERTEX;
	vert.x = p->x + 0.0f;
	vert.y = p->y + 240.0f;
	vert.z = p->z;
	vert.u = vert.v = 0.0f;
	vert.argb = 0xff0000ff;
	vert.oargb = 0;
	pvr_prim(&vert, sizeof(vert));

	vert.y = p->y + 0.0f;
	vert.argb = 0xff00ff00;
	pvr_prim(&vert, sizeof(vert));

	vert.x = p->x + 320.0f;
	vert.y = p->y + 240.0f;
	vert.argb = 0xff000000;
	pvr_prim(&vert, sizeof(vert));

	vert.flags = PVR_CMD_VERTEX_EOL;
	vert.y = p->y + 0.0f;
	vert.argb = 0xffff0000;
	pvr_prim(&vert, sizeof(vert));
}

/* Sends one polygon's worth of data to the TA */
void draw_one_textured_poly(polyplace_t *p) {
	/* Opaque Textured vertex */
	pvr_vertex_t vert;
	
	vert.flags = PVR_CMD_VERTEX;
	vert.x = p->x + 0.0f;
	vert.y = p->y + 240.0f;
	vert.z = p->z;
	vert.u = 0.0f;
	vert.v = 480.0f / 512.0f;
	vert.argb = 0xffffffff;
	vert.oargb = 0;
	pvr_prim(&vert, sizeof(vert));
	
	vert.y = p->y + 0.0f;
	vert.v = 0.0f;
	pvr_prim(&vert, sizeof(vert));
	
	vert.x = p->x + 320.0f;
	vert.y = p->y + 240.0f;
	vert.u = 640.0f / 1024.0f;
	vert.v = 480.0f / 512.0f;
	pvr_prim(&vert, sizeof(vert));
	
	vert.flags = PVR_CMD_VERTEX_EOL;
	vert.y = p->y + 0.0f;
	vert.v = 0.0f;
	pvr_prim(&vert, sizeof(vert));
}

int to_texture = 0;
pvr_ptr_t d_texture;
uint32 tx_x = 1024, tx_y = 512;

void draw_frame() {
	pvr_poly_cxt_t	cxt;
	pvr_poly_hdr_t	poly;
	int i;

	pvr_poly_cxt_col(&cxt, PVR_LIST_OP_POLY);
	pvr_poly_compile(&poly, &cxt);

	/* Start opaque poly list */
	pvr_wait_ready();
	if(!to_texture)
		pvr_scene_begin();
	else	{
		pvr_scene_begin_txr(d_texture, &tx_x, &tx_y);
		to_texture = 2;
	}

	pvr_list_begin(PVR_LIST_OP_POLY);

	/* Send polygon header to the TA using store queues */
	pvr_prim(&poly, sizeof(poly));

	/* Draw all polygons */
	for (i=0; i<6; i++)
		draw_one_poly(polys+i);

	/* End of opaque list */
	pvr_list_finish();

	/* Finish the frame */
	pvr_scene_finish();

	/* Move all polygons */
	move_polys();
}

void draw_textured() {
	pvr_poly_cxt_t cxt;
	pvr_poly_hdr_t hdr;
	pvr_ptr_t tmp;
	int i;

	pvr_poly_cxt_txr(&cxt, PVR_LIST_OP_POLY, PVR_TXRFMT_RGB565 | PVR_TXRFMT_NONTWIDDLED, 1024, 512, d_texture, PVR_FILTER_NONE);
	pvr_poly_compile(&hdr, &cxt);

	/* Start opaque poly list */
	pvr_wait_ready();

	if(to_texture == 3)	{
		pvr_scene_begin_txr(d_texture, &tx_x, &tx_y);
		to_texture = 2;
	}
	else
		pvr_scene_begin();

	pvr_list_begin(PVR_LIST_OP_POLY);

	/* Send polygon header to the TA using store queues */
	pvr_prim(&hdr, sizeof(hdr));

	/* Draw all polygons */
	for (i = 0; i < 6; i++)
		draw_one_textured_poly(polys+i);

	/* End of opaque list */
	pvr_list_finish();

	/* Finish the frame */
	pvr_scene_finish();

	/* Move all polygons */
	move_polys();
}

/* Main program: init and loop drawing polygons */
pvr_init_params_t pvr_params = {
	{ PVR_BINSIZE_16, PVR_BINSIZE_0, PVR_BINSIZE_0, PVR_BINSIZE_0, PVR_BINSIZE_0 },
	64 * 1024
};

int main(int argc, char **argv) {
	maple_device_t *cont;
	cont_state_t *state;
	int finished = 0;
	uint64 timer = timer_ms_gettime64();

	pvr_init(&pvr_params);

	/* Allocate our texture to be rendered to */
	d_texture = pvr_mem_malloc(1024 * 512 * 2);

	pvr_set_bg_color(1.0f, 1.0f, 1.0f);

	while(!finished)	{
		cont = maple_enum_type(0, MAPLE_FUNC_CONTROLLER);

		if(cont != NULL)	{
			state = (cont_state_t *) maple_dev_status(cont);

			if(state != NULL && timer < timer_ms_gettime64())	{
				if(state->buttons & CONT_START)
					finished = 1;
				else if(state->buttons & CONT_A && (to_texture % 2) != 1)	{
					++to_texture;
					timer = timer_ms_gettime64() + 200;
				}
				else if(state->buttons & CONT_B && to_texture)	{
					to_texture = 0;
					timer = timer_ms_gettime64() + 200;
				}
			}
		}

		if(to_texture < 2)	{
			draw_frame();
		}
		else	{
			draw_textured();
		}
	}

	pvr_mem_free(d_texture);

	/* Shutdown isn't technically neccessary, but is possible */
	pvr_shutdown();
		
	return 0;
}

