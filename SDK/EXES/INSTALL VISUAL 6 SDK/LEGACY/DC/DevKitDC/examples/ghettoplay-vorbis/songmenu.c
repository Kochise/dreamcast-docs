/* GhettoPlay: an S3M browser and playback util
   (c)2000 Dan Potter
*/

#include <oggvorbis/sndoggvorbis.h>
#include <string.h>
#include "gp.h"

/* Takes care of the song menu */


/* Song menu choices */
typedef struct {
	char	fn[16];
	int	size;
} entry;
typedef struct {
	char	fn[64];
	int	size;
} lst_entry;
char curdir[64] = "/";
char playdir[64] = "/";
char loadme[256] = "";
char workstring[256] ="";

static entry entries[200];
static int num_entries = 0, load_queued = 0;
static int selected = 0, top = 0, iplaying = 0;

static int framecnt = 0;
static float throb = 0.2f, dthrob = 0.01f;

/* Here we hold the playlist */
static int lst_size = 0;
static lst_entry lst_entries[200];
static int lst_playing = -1;

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
	float y = 92.0f;
	int i, esel;

//	printf("DEBUG: List size %d\r\n",lst_size);

	/* Draw all the song titles */	
//	for (i=0; i<14 && (top+i)<num_entries; i++) {
	for (i=0; i<10 && (top+i)<num_entries; i++) {
		int li;
		draw_poly_strf(32.0f, y, 100.0f, 1.0f, 1.0f, 1.0f, 1.0f,
			entries[top+i].fn);
		if (entries[top+i].size >= 0) {
			draw_poly_strf(32.0f+180.0f, y, 100.0f, 1.0f, 1.0f, 1.0f, 1.0f,
				"%d bytes", entries[top+i].size);
		} else {
			draw_poly_strf(32.0f+180.0f, y, 100.0f, 1.0f, 1.0f, 1.0f, 1.0f, "<DIR>");
		}

		/* Check for playlist entries */
		for(li = 0; li<lst_size;li++)
		{
			strcat(workstring,curdir);
			strcat(workstring,"/");
			strcat(workstring,entries[top+i].fn);
	
//			printf("%s =? %s \r\n",workstring,lst_entries[li].fn);

			if(!(strcmp(workstring,lst_entries[li].fn)))
			{
				char number[2];
				sprintf(number,"%2d",li+1);
				draw_poly_strf(36.0f+32.0f+180.0f+300.0f, y, 100.0f, 1.0f, 1.0f, 1.0f, 1.0f, number);
			}				
			if(!(strcmp(workstring,lst_entries[lst_playing].fn)))
			{
				draw_poly_box  (31.0f, y - 1.0f,
						609.0f, y + 25.0f, 90.0f,
						throb, 0.0f, 0.2f, 0.2f, 
						throb, 0.0f, throb, 0.2f);

			}
			
			workstring[0]=0;
		}		
		
		
		y += 24.0f;
	}
	
	/* Put a highlight bar under one of them */
	esel = (selected - top);
	draw_poly_box(31.0f, 92.0f+esel*24.0f - 1.0f,
		609.0f, 92.0f+esel*24.0f + 25.0f, 95.0f,
		throb, throb, 0.2f, 0.2f, throb, throb, 0.2f, 0.2f);

	/* Put a hightlight bar under the playing file */
	/* Only works correctly if you're in the same dir as the played file */
	if( (sndoggvorbis_isplaying() && !(strcmp(playdir,curdir)) && (lst_size==0)) )
	{
		esel = (iplaying - top);
		draw_poly_box(31.0f, 92.0f+esel*24.0f - 1.0f,
			609.0f, 92.0f+esel*24.0f + 25.0f, 90.0f,
			throb, 0.0f, 0.2f, 0.2f, 
			throb, 0.0f, throb, 0.2f);
	}


}

/* Handle controller input */
void check_controller() {
	static uint8 mcont = 0;
	static int up_moved = 0, down_moved = 0, a_pressed = 0, y_pressed = 0;
	cont_cond_t cond;

	if ((!(sndoggvorbis_isplaying())) && (lst_playing != -1))
	{
		lst_playing++;
		if (lst_playing == lst_size)
		{
			printf("DEBUG: Reached end of playlist...\r\n");
			lst_playing = -1;
			lst_size = 0;
		}
		else
		{
			printf("DEBUG: Next song in playlist...\r\n");
			sndoggvorbis_start(lst_entries[lst_playing].fn,0);
			// sndoggvorbis_wait_play();
		}
	}
				
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
//				if (selected >= (top+14)) {
				if (selected >= (top+10)) {
					top++;
				}
			}
			down_moved = framecnt;
		}
	}
	if (cond.ltrig > 0) {
		if ((framecnt - up_moved) > 10) {
//			selected -= 14;
			selected -= 10;

			if (selected < 0) selected = 0;
			if (selected < top) top = selected;
			up_moved = framecnt;
		}
	}
	if (cond.rtrig > 0) {
		if ((framecnt - down_moved) > 10) {
//			selected += 14;
			selected -= 10;
			if (selected > (num_entries - 1))
				selected = num_entries - 1;
//			if (selected >= (top+14))
			if (selected >= (top+10))
				top = selected;
			down_moved = framecnt;
		}
	}
	if (!(cond.buttons & CONT_B)) {
		sndoggvorbis_stop();
	}

	if (!(cond.buttons & CONT_Y)) {
		if ((framecnt - y_pressed) > 10)
		{
		strcat(workstring,curdir);
		strcat(workstring,"/");
		strcat(workstring,entries[selected].fn);		
		strcpy(lst_entries[lst_size].fn,workstring);
		
		printf("DEBUG: Entry %d : %s\r\n",lst_size,lst_entries[lst_size].fn);

		workstring[0]=0;
		
		lst_size++;

		}
		y_pressed=framecnt;
	}

	if (!(cond.buttons & CONT_A)) {
		if ((framecnt - a_pressed) > 10)
		{
			if (!strcmp(entries[selected].fn, "Error!"))
			{
				num_entries = 0;
				load_song_list();
			}
			else if (lst_size > 0)
			{
				printf("DEBUG: Playing playlist...\r\n");
				lst_playing=0;
				sndoggvorbis_stop();
				sndoggvorbis_start(lst_entries[lst_playing].fn,0);
				// sndoggvorbis_wait_play();
			}
			else if (entries[selected].size >= 0)
			{
				sndoggvorbis_stop();
				strcpy(playdir,curdir);
				strcat(loadme,curdir);
				strcat(loadme,"/");
				strcat(loadme,entries[selected].fn);
				sndoggvorbis_start(loadme,0);
				loadme[0]=0;
				iplaying=selected;
			}
			else
			{
				if (!strcmp(entries[selected].fn, "<..>"))
				{
					int i;
					for (i=strlen(curdir); i>0; i--)
					{
						if (curdir[i] == '/')
						{
							curdir[i] = 0;
							break;
						}
						else
						{
							curdir[i] = 0;
						}
					}
				} 
				else
				{
					if (strcmp(curdir, "/"))
					strcat(curdir, "/");
					strcat(curdir, entries[selected].fn);
				}
				selected = top = num_entries = 0;
				printf("current directory is now '%s'\n", curdir);
				load_song_list();
			}
		}
		a_pressed = framecnt;
	}
}

/* Check maple bus inputs */
void check_inputs() {
	check_controller();
}

/* Main rendering of the song menu */
void song_menu_render() {
	/* Draw a background box */
	draw_poly_box(30.0f, 80.0f, 610.0f, 440.0f-96.0f, 90.0f, 
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




