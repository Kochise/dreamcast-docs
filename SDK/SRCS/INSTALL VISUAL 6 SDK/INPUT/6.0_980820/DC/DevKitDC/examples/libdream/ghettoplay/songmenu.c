/* GhettoPlay: an S3M browser and playback util
   (c)2000 Dan Potter
*/

#include <string.h>
#include "gp.h"

/* Takes care of the song menu */


/* Song menu choices */
typedef struct {
	char	fn[16];
	int	size;
} entry;
char curdir[64] = "/";

static entry entries[200];
static int num_entries = 0, load_queued = 0;
static int selected = 0, top = 0;

static int framecnt = 0;
static float throb = 0.2f, dthrob = 0.01f;

static void load_song_list() {
	file_t d;

	d = fs_open(curdir, O_RDONLY | O_DIR);
	if (!d) {
		strcpy(curdir, "/");
		d = fs_open(curdir, O_RDONLY | O_DIR);
		if (!d) {
			num_entries = 1;
			strcpy(entries[0].fn,"Error!");
			entries[0].size = 0;
			return;
		}
	}
	{
		dirent_t *de;
		num_entries = 0;
		if (strcmp(curdir, "/")) {
			strcpy(entries[0].fn, "<..>"); entries[0].size = -1;
			num_entries++;
		}
		while ( (de = fs_readdir(d)) && num_entries < 200) {
			printf("read entry '%s'\n", de->name);
			strcpy(entries[num_entries].fn, de->name);
			entries[num_entries].size = de->size;
			num_entries++;
		}
	}
	fs_close(d);
}

/* Draws the song listing */
static void draw_listing() {
	float y = 82.0f;
	int i, esel;

	/* Draw all the song titles */	
	for (i=0; i<14 && (top+i)<num_entries; i++) {
		draw_poly_strf(32.0f, y, 100.0f, 1.0f, 1.0f, 1.0f, 1.0f,
			entries[top+i].fn);
		if (entries[top+i].size >= 0) {
			draw_poly_strf(32.0f+180.0f, y, 100.0f, 1.0f, 1.0f, 1.0f, 1.0f,
				"%d bytes", entries[top+i].size);
		} else {
			draw_poly_strf(32.0f+180.0f, y, 100.0f, 1.0f, 1.0f, 1.0f, 1.0f, "<DIR>");
		}
		y += 24.0f;
	}
	
	/* Put a highlight bar under one of them */
	esel = (selected - top);
	draw_poly_box(31.0f, 82.0f+esel*24.0f - 1.0f,
		609.0f, 82.0f+esel*24.0f + 25.0f, 95.0f,
		throb, throb, 0.2f, 0.2f, throb, throb, 0.2f, 0.2f);
}

/* Handle controller input */
void check_controller() {
	static uint8 mcont = 0;
	static int up_moved = 0, down_moved = 0;
	cont_cond_t cond;

	if (!mcont) {
		mcont = maple_first_controller();
		if (!mcont) { return; }
	}
	if (cont_get_cond(mcont, &cond)) { return; }

	if (!(cond.buttons & CONT_DPAD_UP)) {
		if ((framecnt - up_moved) > 10) {
			if (selected > 0) {
				selected--;
				if (selected < top) {
					top = selected;
				}
			}
			up_moved = framecnt;
		}
	}
	if (!(cond.buttons & CONT_DPAD_DOWN)) {
		if ((framecnt - down_moved) > 10) {
			if (selected < (num_entries - 1)) {
				selected++;
				if (selected >= (top+14)) {
					top++;
				}
			}
			down_moved = framecnt;
		}
	}
	if (cond.ltrig > 0) {
		if ((framecnt - up_moved) > 10) {
			selected -= 14;
			if (selected < 0) selected = 0;
			if (selected < top) top = selected;
			up_moved = framecnt;
		}
	}
	if (cond.rtrig > 0) {
		if ((framecnt - down_moved) > 10) {
			selected += 14;
			if (selected > (num_entries - 1))
				selected = num_entries - 1;
			if (selected >= (top+14))
				top = selected;
			down_moved = framecnt;
		}
	}
	if (!(cond.buttons & CONT_A)) {
		if (!strcmp(entries[selected].fn, "Error!")) {
			num_entries = 0;
			load_song_list();
		} else if (entries[selected].size >= 0) {
			play_s3m(entries[selected].fn);
		} else {
			if (!strcmp(entries[selected].fn, "<..>")) {
				int i;
				for (i=strlen(curdir); i>0; i--) {
					if (curdir[i] == '/') {
						curdir[i] = 0;
						break;
					} else
						curdir[i] = 0;
				}
			} else {
				if (strcmp(curdir, "/"))
					strcat(curdir, "/");
				strcat(curdir, entries[selected].fn);
			}
			selected = top = num_entries = 0;
			printf("current directory is now '%s'\n", curdir);
			load_song_list();
		}
	}
}

/* Check maple bus inputs */
void check_inputs() {
	check_controller();
}

/* Main rendering of the song menu */
void song_menu_render() {
	/* Draw a background box */
	draw_poly_box(30.0f, 70.0f, 610.0f, 430.0f, 90.0f, 
		0.2f, 0.8f, 0.5f, 0.0f, 0.2f, 0.8f, 0.8f, 0.2f);
		
	/* If we don't have a file listing, get it now */
	if (num_entries == 0) {
		if (load_queued < 4) {
			draw_poly_strf(32.0f, 82.0f, 100.0f, 1.0f, 1.0f, 1.0f, 1.0f,
				"Scanning Directory...");
			load_queued++;
			return;
		} else {
			load_song_list();
			load_queued = 0;
		}
	}
	
	/* Draw the song listing */
	draw_listing();
	
	/* Adjust the throbber */
	throb += dthrob;
	if (throb < 0.2f || throb > 0.8f) {
		dthrob = -dthrob;
		throb += dthrob;
	}
	
	/* Check maple inputs */
	check_inputs();
	
	framecnt++;
}




