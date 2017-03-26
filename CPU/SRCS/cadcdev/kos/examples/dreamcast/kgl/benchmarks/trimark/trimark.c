/* KallistiGL ##version##

   pvrmark.c
   (c)2002 Dan Potter, Paul Boese
*/

#include <kos.h>
#include <GL/gl.h>
#include <time.h>

CVSID("$Id: trimark.c,v 1.3 2003/03/09 01:20:06 bardtx Exp $");

pvr_init_params_t pvr_params = {
	{ PVR_BINSIZE_16, PVR_BINSIZE_0, PVR_BINSIZE_0, PVR_BINSIZE_0, PVR_BINSIZE_0 },
	512 * 1024
};

enum { PHASE_HALVE, PHASE_INCR, PHASE_DECR, PHASE_FINAL };

int polycnt;
int phase = PHASE_HALVE;
float avgfps = -1;

void running_stats() {
	pvr_stats_t stats;
	pvr_get_stats(&stats);
	if (avgfps == -1)
		avgfps = stats.frame_rate;
	else
		avgfps = (avgfps + stats.frame_rate) / 2.0f;
}

void stats() {
	pvr_stats_t stats;

	pvr_get_stats(&stats);
	dbglog(DBG_DEBUG, "3D Stats: %d VBLs, frame rate ~%f fps\n",
		stats.vbl_count, stats.frame_rate);
}


int check_start() {
	uint8 addr;
	cont_cond_t cond;

	addr = maple_first_controller();
	if (cont_get_cond(addr, &cond) < 0)
		return 0;

	return !(cond.buttons & CONT_START);
}

pvr_poly_hdr_t hdr;

void setup() {
	pvr_init(&pvr_params);
	glKosInit();
	pvr_set_bg_color(0,0,0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(0,640,0,480,-100,100);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

void do_frame() {
	int x, y, z;
	int size;
	int i;
	float col;

	glKosBeginFrame();
	vid_border_color(0,255,0);
	glBegin(GL_TRIANGLES);
	for (i=0; i<polycnt; i++) {
		x = rand() % 640;
		y = rand() % 480;
		z = rand() % 100 + 1;
		size = rand() % 50;
		col = (rand () % 255) * 0.00391f;
	
		glColor3f(col, col, col);
		glVertex3f(x-size, y+size, z);
		glVertex3f(x-size, y-size, z);
		glVertex3f(x+size, y+size, z);
	}
	glEnd();

	vid_border_color(255,0,0);
	glKosFinishFrame();
	vid_border_color(0,0,0);
}

time_t start;
void switch_tests(int ppf) {
	printf("Beginning new test: %d polys per frame (%d per second at 60fps)\n",
		ppf, ppf * 60);
	avgfps = -1;
	polycnt = ppf;
}

void check_switch() {
	time_t now;

	now = time(NULL);
	if (now >= (start + 5)) {
		start = time(NULL);
		printf("  Average Frame Rate: ~%f fps (%d pps)\n", avgfps, (int)(polycnt * avgfps));
		switch(phase) {
		case PHASE_HALVE:
			if (avgfps < 55) {
				switch_tests(polycnt / 1.2f);
			} else {
				printf("  Entering PHASE_INCR\n");
				phase = PHASE_INCR;
			}
			break;
		case PHASE_INCR:
			if (avgfps >= 55) {
				switch_tests(polycnt + 15);
			} else {
				printf("  Entering PHASE_DECR\n");
				phase = PHASE_DECR;
			}
			break;
		case PHASE_DECR:
			if (avgfps < 55) {
				switch_tests(polycnt - 20);
			} else { 
				printf("  Entering PHASE_FINAL\n");
				phase = PHASE_FINAL;
			}
			break;
		case PHASE_FINAL:
			break;
		}
	}
}

int main(int argc, char **argv) {
	setup();

	/* Start off with something obscene */
	switch_tests(220000 / 60);
	start = time(NULL);

	for(;;) {
		if (check_start())
			break;

		printf(" \r");
		do_frame();
		running_stats();
		check_switch();
	}

	stats();

	return 0;
}


