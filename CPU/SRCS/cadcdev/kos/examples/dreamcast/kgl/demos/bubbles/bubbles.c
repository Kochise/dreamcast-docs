/*
   KallistiOS ##version##
   bubbles.c

   (c)2002 Dan Potter
*/

#include <kos.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>

/*

This example shows off something truly evil ;-)

KGL is a really nice API for doing some quick graphics work without having
to worry about the little issues like vertex structures, 3D rotations, etc.
But sometimes KGL just isn't fast enough for what you want to do. This came
up recently during an effect I was working on for a game project. So for this
case, the Direct Rendering macros were created.

The basic problem is that the DC's SH-4 makes very inefficient use of the
RAM, and has no L2 cache. So if you use RAM in your PVR-feeding loop, you're
likely to blow 3-4 times as many cycles as you really need to. What we really
want to do is eliminate all function calls, all RAM access, and streamline
everything as much as possible. So here's the basic idea:

- Inline all access to hardware rather than calling functions; so store queue
  functions, TA submission, etc, are all handled inline by the macros
- Do not involve RAM at all, except maybe a small stack page if neccessary
  for each variables; a memory stucture is not even used for storing vertex
  data while it is being prepared -- it is written directly into the store
  queues as it's generated.
- Bypass KGL entirely for transformations and data submission

Obviously as KGL becomes more complex, this means you have more and more of
a burden to shoulder to do it this way, but sometimes you just need more
direct access, and this is a good way.

This sample uses 4800 triangles per frame, for 288000 per second at 60fps
for the translucent version, and 9600 per frame, for 576000 per
second at 60fps.

Pre-DR, I was able to barely maintain 30fps with 6 spheres, and with this
new optimized version, I can now easily do 12 spheres at 60fps even with
translucent polys, so the difference is quite marked.

*/


/* Draws a sphere out of GL_QUADS according to the syntax of glutSolidSphere

   This now uses triangle strips and KGL/PVR Direct Rendering for the best
   possible performance.

   Based very loosely on a routine from James Susinno.
*/
static float phase = 0.0f;
static pvr_poly_cxt_t cxt;
static pvr_poly_hdr_t hdr;
static void sphere( float radius, int slices, int stacks ) {
	int	i, j;
	float	pitch, pitch2;
	float	x, y, z, g, b;
	float	yaw, yaw2;
	pvr_vertex_t	*vert;
	pvr_dr_state_t	dr_state;

	/* Setup our Direct Render state: pick a store queue and setup QACR0/1 */
	pvr_dr_init(dr_state);

	/* Initialize xmtrx with the values from KGL */
	glKosMatrixIdent();
	glKosMatrixApply(GL_KOS_SCREENVIEW);
	glKosMatrixApply(GL_PROJECTION);
	glKosMatrixApply(GL_MODELVIEW);

	/* Put our own polygon header */
	pvr_prim(&hdr, sizeof(hdr));

	/* Iterate over stacks */
	for ( i=0; i<stacks; i++ ) {
		pitch = 2*M_PI * ( (float)i/(float)stacks );
		pitch2 = 2*M_PI * ( (float)(i+1)/(float)stacks );

		/* Iterate over slices: each entire stack will be one
		   long triangle strip. */
		for ( j=0; j<=slices/2; j++ ) {
			yaw = 2*M_PI * ( (float)j/(float)slices );
			yaw2 = 2*M_PI * ( (float)(j+1)/(float)slices );

			/* x, y+1 */
			x = radius * fcos( yaw ) * fcos( pitch2 );
			y = radius * fsin( pitch2 );
			z = radius * fsin( yaw ) * fcos( pitch2 );
			mat_trans_single(x, y, z);			/* Use ftrv to transform */
			g = fcos( yaw*2 ) / 2.0f + 0.5f;
			b = fsin( phase + pitch2 ) / 2.0f + 0.5f;
			vert = pvr_dr_target(dr_state);			/* Get a store queue address */
			vert->flags = PVR_CMD_VERTEX;
			vert->x = x;
			vert->y = y;
			vert->z = z;
			vert->u = 0.0f;
			vert->v = 0.0f;
			vert->argb = PVR_PACK_COLOR(0.5f, 0.0f, g, b);
			vert->oargb = 0xff000000;
			pvr_dr_commit(vert);				/* Prefetch the SQ */
                
			/* x, y */
			x = radius * fcos( yaw ) * fcos( pitch );
			y = radius * fsin( pitch );
			z = radius * fsin( yaw ) * fcos( pitch );
			mat_trans_single(x, y, z);
			g = fcos( yaw*2 ) / 2.0f + 0.5f;
			b = fsin( phase + pitch ) / 2.0f + 0.5f;
			vert = pvr_dr_target(dr_state);
			if (j == (slices/2))
				vert->flags = PVR_CMD_VERTEX_EOL;
			else
				vert->flags = PVR_CMD_VERTEX;
			vert->x = x;
			vert->y = y;
			vert->z = z;
			vert->u = 0.0f;
			vert->v = 0.0f;
			vert->argb = PVR_PACK_COLOR(0.5f, 0.0f, g, b);
			vert->oargb = 0xff000000;
			pvr_dr_commit(vert);
		}
	}
}

#define SPHERE_CNT 12
static int r = 0;

static void sphere_frame_opaque() {
	int i;

	vid_border_color(255, 0, 0);
	glKosBeginFrame();

	vid_border_color(0, 255, 0);

	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -12.0f);
	glRotatef(r * 2, 0.75f, 1.0f, 0.5f);
	glDisable(GL_CULL_FACE);

	for (i=0; i<SPHERE_CNT; i++) {
		glPushMatrix();
		glTranslatef(6.0f * fcos(i * 2*M_PI / SPHERE_CNT), 0.0f, 6.0f * fsin(i * 2*M_PI / SPHERE_CNT));
		glRotatef(r, 1.0f, 1.0f, 1.0f);
		sphere(1.2f, 20, 20);
		glPopMatrix();
	}

	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -12.0f);
	glRotatef(-r * 2, 0.75f, 1.0f, 0.5f);
	glDisable(GL_CULL_FACE);

	for (i=0; i<SPHERE_CNT; i++) {
		glPushMatrix();
		glTranslatef(3.0f * fcos(i * 2*M_PI / SPHERE_CNT), 0.0f, 3.0f * fsin(i * 2*M_PI / SPHERE_CNT));
		glRotatef(r, 1.0f, 1.0f, 1.0f);
		sphere(0.8f, 20, 20);
		glPopMatrix();
	}

	glKosFinishList();

	vid_border_color(0, 0, 255);
	glKosFinishFrame();
	r++;
	phase += 2*M_PI / 240.0f;
}

static void sphere_frame_trans() {
	int i;

	glKosBeginFrame();

	glKosFinishList();

	vid_border_color(0, 255, 0);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -10.0f);
	glRotatef(15, 1.0f, 0.0f, 0.0f);
	glRotatef(r * 2, 0.75f, 1.0f, 0.5f);
	glDisable(GL_CULL_FACE);

	for (i=0; i<SPHERE_CNT; i++) {
		glPushMatrix();
		glTranslatef(4.0f * fcos(i * 2*M_PI / SPHERE_CNT), 0.0f, 4.0f * fsin(i * 2*M_PI / SPHERE_CNT));
		glRotatef(r, 1.0f, 1.0f, 1.0f);
		sphere(1.0f, 20, 20);
		glPopMatrix();
	}

	vid_border_color(0, 0, 255);
	glKosFinishFrame();
	vid_border_color(255, 0, 0);
	r++;
	phase += 2*M_PI / 240.0f;
}

void do_sphere_test() {
	uint8		addr;
	cont_cond_t	cond;
	int		mode = 0;
	int		a_was_down = 0;

	glClearColor(0.2f, 0.0f, 0.4f, 1.0f);
	glDisable(GL_TEXTURE_2D);

	pvr_poly_cxt_col(&cxt, PVR_LIST_OP_POLY);
	cxt.gen.culling = PVR_CULLING_NONE;
	pvr_poly_compile(&hdr, &cxt);

	for (;;) {
		if (!mode)
			sphere_frame_opaque();
		else
			sphere_frame_trans();
	
		addr = maple_first_controller();
		if (addr == 0)
			continue;
		if (cont_get_cond(addr, &cond) < 0)
			continue;
		if (!(cond.buttons & CONT_START)) {
			return;
		}
		if (!(cond.buttons & CONT_A)) {
			if (a_was_down) continue;
			a_was_down = 1;
			mode ^= 1;
			switch(mode) {
			case 0:	/* Opaque */
				pvr_poly_cxt_col(&cxt, PVR_LIST_OP_POLY);
				cxt.gen.culling = PVR_CULLING_NONE;
				pvr_poly_compile(&hdr, &cxt);
				break;
			case 1:	/* Translucent */
				pvr_poly_cxt_col(&cxt, PVR_LIST_TR_POLY);
				cxt.gen.culling = PVR_CULLING_NONE;
				pvr_poly_compile(&hdr, &cxt);
				break;
			}
		} else {
			a_was_down = 0;
		}
	}
}

pvr_init_params_t params = {
	/* Enable opaque and translucent polygons with size 16 */
	{ PVR_BINSIZE_16, PVR_BINSIZE_0, PVR_BINSIZE_16, PVR_BINSIZE_0, PVR_BINSIZE_0 },
	
	/* Vertex buffer size 512K */
	512*1024
};
	
int main(int argc, char **argv) {
	/* Init PVR API */
	if (pvr_init(&params) < 0)
		return -1;

	/* Init KGL */
	glKosInit();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, 640.0f / 480.0f, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_TEXTURE_2D);

	/* Expect CW verts */
	glFrontFace(GL_CW);

	/* Enable Transparancy */
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_DEPTH_TEST);

	/* Do the test */
	printf("Bubbles KGL sample: press START to exit, A to toggle sphere type\n");
	do_sphere_test();

	return 0;
}

