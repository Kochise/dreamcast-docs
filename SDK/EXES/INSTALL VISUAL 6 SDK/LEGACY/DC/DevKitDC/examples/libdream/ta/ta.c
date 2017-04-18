/* This is a port of my original 3dtest example to KOS. The big difference
   here is that the background plane is no longer used. This also 
   demonstrates one of the libdcutils functions, pvr_dummy_poly(). */

#include <kos.h>

/* This is really more complicated than it needs to be in this particular
   case, but it's nice and verbose. */
int check_start() {
	static uint8 mcont = 0;
	cont_cond_t cond;

	if (!mcont) {
		mcont = maple_first_controller();
		if (!mcont) {
			printf("No controllers attached\n");
			return 1;
		}
	}

	/* Check for start on the controller */
	if (cont_get_cond(mcont, &cond)) {
		printf("Error getting controller status\n");
		return 1;
	}
		
	if (!(cond.buttons & CONT_START)) {
		printf("Pressed start\n");
		return 1;
	}

	return 0;
}



/* A little test program -- creates twelve rainbow polygons and
   moves them around over a color-shifting background. */
typedef struct {
	float	x, y, z;
	float	dx, dy;
} polyplace_t;

polyplace_t polys[12] = {
	{ 16.0f, 0.0f, 10.0f, 3.0f, 5.0f },	/* Top */
	{ 300.0f, 0.0f, 11.0f, 0.0f, 6.0f },
	{ 624.0f, 0.0f, 12.0f, -3.0f, 7.0f },
	
	{ 24.0f, 300.0f, 13.0f, 3.0f, -7.0f },	/* Bottom */
	{ 340.0f, 300.0f, 14.0f, 0.0f, -6.0f },
	{ 616.0f, 300.0f, 15.0f, -3.0f, -5.0f },
	
	{ 0.0f, 16.0f, 16.0f, 5.0f, 3.0f },	/* Left */
	{ 0.0f, 220.0f, 17.0f, 6.0f, 0.0f },
	{ 0.0f, 364.0f, 18.0f, 7.0f, -3.0f },
	
	{ 480.0f, 24.0f, 19.0f, -7.0f, 3.0f },	/* Right */
	{ 480.0f, 260.0f, 20.0f, -6.0f, 0.0f },
	{ 480.0f, 356.0f, 21.0f, -5.0f, -3.0f },
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
	vertex_oc_t vert;
	
	vert.flags = TA_VERTEX_NORMAL;
	vert.x = p->x + 0.0f;
	vert.y = p->y + 200.0f;
	vert.z = p->z;
	vert.a = 1.0f; vert.r = 0.0f; vert.g = 0.0f; vert.b = 1.0f;
	ta_commit_vertex(&vert, sizeof(vert));

	vert.flags = TA_VERTEX_NORMAL;
	vert.y = p->y + 0.0f;
	vert.a = 1.0f; vert.r = 0.0f; vert.g = 1.0f; vert.b = 0.0f;
	ta_commit_vertex(&vert, sizeof(vert));

	vert.flags = TA_VERTEX_NORMAL;
	vert.x = p->x + 200.0f;
	vert.y = p->y + 200.0f;
	vert.a = 1.0f; vert.r = 0.0f; vert.g = 0.0f; vert.b = 0.0f;
	ta_commit_vertex(&vert, sizeof(vert));

	vert.flags = TA_VERTEX_EOL;
	vert.y = p->y + 0.0f;
	vert.a = 1.0f; vert.r = 1.0f; vert.g = 0.0f; vert.b = 0.0f;
	ta_commit_vertex(&vert, sizeof(vert));
}

uint32 color = 0; int dcolor = 5;
void draw_frame() {
	poly_hdr_t	poly;
	int i;

	color += dcolor;
	if (color <= 0) {
		color = 0; dcolor = -dcolor;
	}
	if (color >= 255) {
		color = 255; dcolor = -dcolor;
	}

	/* Send polygon header to the TA using store queues */
	ta_poly_hdr_col(&poly, TA_OPAQUE);
	ta_commit_poly_hdr(&poly);

	/* Draw all polygons */
	for (i=0; i<12; i++)
		draw_one_poly(polys+i);

	/* End of opaque list */
	ta_commit_eol();

	/* TA freaks out at having a completely empty list */	
	pvr_dummy_poly(TA_TRANSLUCENT);

	/* End of translucent list */
	ta_commit_eol();
	
	/* Finish the frame */
	ta_finish_frame();
	
	/* Move all polygons */
	move_polys();
}

/* Main program: init and loop drawing polygons */
int main(int argc, char **argv) {
	/* NOTE: You MUST enable IRQs for the TA to work! If you don't
	   do it here then you must call irq_enable() before you start
	   doing things with the TA. */
	kos_init_all(IRQ_ENABLE | TA_ENABLE, ROMDISK_NONE);

	while (!check_start())
		draw_frame();
		
	return 0;
}

