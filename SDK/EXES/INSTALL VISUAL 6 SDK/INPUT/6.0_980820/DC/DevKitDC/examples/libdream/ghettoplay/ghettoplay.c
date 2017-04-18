/* GhettoPlay: an S3M browser and playback util
   (c)2000 Dan Potter
   
   Distributed as an example for libdream 0.7
   Ported up to libdream 0.95
   Ported up to KOS 1.1.x

   Historical note: this is _really_ 2.0. There was an internally
   created Ghetto Play that I made to browse and test various S3Ms
   with early versions of the player. It _really_ deserved the name
   GHETTO Play =). This one, like Ghetto Pong, is a 2.0 that is more
   like "Pimpin' Play" ;-). However, sticking with tradition...   
   
   And in reality, this program can't properly be written with libdream.
   This will really demonstrate to the non-believers how much of a
   limitation it is not to have threads. I already have a program that
   performs a similar function under KallistiOS and everything keeps
   going solid even when it's doing disk access, or _even_ if, e.g.,
   input processing locks up.

   [note: I'm not sure what version of GhettoPlay I had in mind ^_^;
    but I don't have it now, so some better examples have been written
    back in the DC examples root. --Dan]
*/

#include <stdio.h>
#include "gp.h"

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

void blit_font_texture() {
	poly_hdr_t poly;
	vertex_ot_t vert;
	
	ta_poly_hdr_txr(&poly, TA_TRANSLUCENT, TA_ARGB4444, 256, 256, util_texture,
		TA_NO_FILTER);
	ta_commit_poly_hdr(&poly);

	vert.flags = TA_VERTEX_NORMAL;
	vert.x = 50.0f;
	vert.y = 50.0f + 256.0f;
	vert.z = 256.0f;
	vert.u = 0.0f;
	vert.v = 1.0f;
	vert.dummy1 = vert.dummy2 = 0;
	vert.a = 1.0f; vert.r = 1.0f; vert.g = 1.0f; vert.b = 1.0f;
	vert.oa = vert.or = vert.og = vert.ob = 0.0f;
	ta_commit_vertex(&vert, sizeof(vert));

	vert.x = 50.0f;
	vert.y = 50.0f;
	vert.u = 0.0f;
	vert.v = 0.0f;
	ta_commit_vertex(&vert, sizeof(vert));

	vert.x = 50.0f + 256.0f;
	vert.y = 50.0f + 256.0f;
	vert.u = 1.0f;
	vert.v = 1.0f;
	ta_commit_vertex(&vert, sizeof(vert));

	vert.flags = TA_VERTEX_EOL;
	vert.x = 50.0f + 256.0f;
	vert.y = 50.0f;
	vert.u = 1.0f;
	vert.v = 0.0f;
	ta_commit_vertex(&vert, sizeof(vert));
}

/* Start a song playing */
#include "s3mplay.h"
extern char curdir[];
void play_s3m(char *fnin) {
	int	idx, r;
	file_t	fd;
	uint8	buffer[2048];
	char	fn[256];

	spu_disable();
	sprintf(fn, "%s/%s", curdir, fnin);

	//dc_serial_printf("Loading %s\n", fn);
	fd = fs_open(fn, O_RDONLY);
	if (fd == 0) {
		//dc_serial_printf("Can't open file %s\n", fn);
		return;
	}
	
	idx = 0x10000;
	/* Load 2048 bytes at a time */
	while ( (r = fs_read(fd, buffer, 2048)) > 0) {
		spu_memload(idx, buffer, r);
		idx += r;
	}
	fs_close(fd);

	spu_memload(0, s3mplay, sizeof(s3mplay));
	spu_enable();
}

/* Render the mouse if they have one attached */
static int mx = 320, my = 240;
static int lmx[5] = {320, 320, 320, 320, 320},
	lmy[5] = {240, 240, 240, 240, 240};
static uint8 mmouse = 0;
void mouse_render() {
	mouse_cond_t cond;
	if (!mmouse) return;
	
	draw_poly_mouse(mx, my);
	
	if (mouse_get_cond(mmouse, &cond)) return;
	
	if (cond.dx || cond.dy) {
		int i;
		
		for (i=4; i>0; i--) {
			lmx[i] = lmx[i-1];
			lmy[i] = lmy[i-1];
		}
		lmx[0] = mx;
		lmy[0] = my;
		
		mx += cond.dx;
		my += cond.dy;
		
		if (mx < 0) mx = 0;
		if (mx > 640) mx = 640;
		if (my < 0) my = 0;
		if (my > 480) my = 480;
	}

	{
		poly_hdr_t poly;
		int i;
		static char msg[] = "mouse";
		char *s = msg;
		
		ta_poly_hdr_txr(&poly, TA_TRANSLUCENT, TA_ARGB4444, 256, 256,
			util_texture, TA_NO_FILTER);
		ta_commit_poly_hdr(&poly);
		
		for (i=0; i<5; i++) {
			draw_poly_char(lmx[i], lmy[i], 510.0f, 0.3f, 1.0f, 1.0f, 1.0f, *s++);
		}
	}
}

/* Update the VMU LCD */
#include "vmu_ghetto.h"
#include "vmu_play.h"
#include "vmu_ghettoplay.h"
static uint8 mvmu = 0;
static int cycle = 0, phase = 1;
void vmu_icon_draw(const char *vmu_icon) {
	uint8 bitmap[48*32/8] = {0};
	int x, y, xi, xb;

	if (vmu_icon) {	
		for (y=0; y<32; y++)
			for (x=0; x<48; x++) {
				xi = x / 8;
				xb = 0x80 >> (x % 8);
				if (vmu_icon[(31-y)*48+(47-x)] == '.')
					bitmap[y*(48/8)+xi] |= xb;
			}
	}
	
	vmu_draw_lcd(mvmu, bitmap);
}
void vmu_lcd_update() {
	switch(cycle) {
		case 0: {	/* Getto/Play/GettoPlay */
			if (phase == 1) {
				vmu_icon_draw(vmu_ghetto_xpm);
			} else if (phase == 60) {
				vmu_icon_draw(vmu_play_xpm);
			} else if (phase == 120) {
				vmu_icon_draw(vmu_ghettoplay_xpm);
			} else if (phase == 180) {
				phase = 0;
				cycle = 1;
			}
		} break;
		case 1: {	/* Flashing */
			if ((phase % 20) == 0) {
				vmu_icon_draw(vmu_ghettoplay_xpm);
			} else if ((phase % 20) == 10) {
				vmu_icon_draw(NULL);
			}
			
			if (phase == 60) {
				cycle = 0;
				phase = 0;
			}
		} break;
	}
	phase++;
}

/* Program entry */
int main(int argc, char **argv) {
	/* Do basic setup */
	kos_init_all(IRQ_ENABLE | THD_ENABLE | TA_ENABLE, ROMDISK_NONE);

	/* Setup the mouse/font texture */
	setup_util_texture();

	/* Setup background display */
	bkg_setup();

	/* Find a mouse if there is one */
	mmouse = maple_first_mouse();
	
	/* Find an LCD if there is one */
	mvmu = maple_first_lcd();

	while (!check_start()) {
		ta_begin_render();

		/* Opaque list *************************************/
		bkg_render();

		/* End of opaque list */
		ta_commit_eol();

		/* Translucent list ********************************/

		/* Top Banner */
		draw_poly_box(0.0f, 10.0f, 640.0f, 20.0f+24.0f+10.0f, 90.0f, 
			0.3f, 0.2f, 0.5f, 0.0f, 0.5f, 0.1f, 0.8f, 0.2f);
		draw_poly_strf(5.0f, 20.0f, 100.0f, 1.0f, 1.0f, 1.0f, 1.0f,
			"GhettoPlay 1.0 (c)2000 Dan Potter/Cryptic Allusion");

		/* Song menu */
		song_menu_render();

		/* Render the mouse if they move it.. it doesn't do anything
		   but it's cool looking ^_^ */
		mouse_render();

		/* End of translucent list */
		ta_commit_eol();

		/* Finish the frame *******************************/
		ta_finish_frame();
		
		/* Update the VMU LCD */
		vmu_lcd_update();
	}
	
	/* Stop the sound */
	spu_disable();

	return 0;
}





