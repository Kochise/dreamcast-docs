/* KallistiOS 1.1.6

   2ndmix.c
   (c)2000 Dan Potter

*/

static char id[] = "KOS $Id: 2ndmix.c,v 1.1.1.1 2001/09/26 07:05:15 bardtx Exp $";

/* 

The good ol' 2ndmix example that just won't die ^_^

*/

#include <kos.h>

/* Floating-point Sin/Cos; 256 angles, -1.0 to 1.0 */
#include "sintab.h"
#define msin(angle) sintab[angle]
#define mcos(angle) sintab[((angle)+64) % 256]

/* optimal random number function. */
unsigned long seed=123;
#define RNDC 1013904223
#define RNDM 1164525

int rand() {
	seed = seed * RNDM + RNDC;
	return seed;
}

int randnum(int limit) { return (rand() & 0x7fffffff) % limit; }

/* Texture offsets */
uint32 txr_font = 0;

/**********************************************************/
/* Load and start an S3M file from disk or memory */
#include "s3mplay.h"

volatile unsigned long *snd_dbg = (unsigned long*)0xa080ffc0;

void play_s3m(char *fn) {
	int idx, i, r;
	uint32 fd;
	unsigned char buffer[2048];

	spu_disable();

	printf("Loading %s\r\n", fn);
	fd = fs_open(fn, O_RDONLY);
	if (fd == 0) {
		printf("Can't open file %s\r\n", fn);
		return;
	}
	
	idx = 0x10000;
	/* Load 2048 bytes at a time */
	while ( (r=fs_read(fd, buffer, 2048)) > 0) {
		spu_memload(idx, buffer, r);
		idx += r;
	}
	fs_close(fd);
	
	/* Switch channels to mono if holding down A */
	/*if (check_for_btn(BTN_A)) {
		snd_dbg[1] = 1;
	} else {
		snd_dbg[1] = 0;
	}*/
	
	//dc_serial_printf("Load OK, starting ARM\r\n");
	printf("Loading ARM program\r\n");
	spu_memload(0, s3mplay, sizeof(s3mplay));
	
	printf("Start\r\n");
	spu_enable();

	while (*snd_dbg != 3)
		;

	while (*snd_dbg == 3)
		;
		
	printf("Done\r\n");
}

/**********************************************************/
/* 3D star code, written a long time ago =) */
#define NS 1024
int	*star_x = NULL, *star_y, *star_z;

/* init stars so that they will be anywhere on the screen, but will start out
   as a single dot in the middle because of the Z coord.

   This routine has been mathmatically optimized to produce the best possible
   spread of stars on the given starfield parameters by solving the
   perspective equation for X and Y. */

#define zk 64
#define MAXX ((640*(zk+640))/zk)
#define MAXY ((480*(zk+480))/zk)

void stars_init() {
	int i;

	if (star_x == NULL) {
		star_x = malloc(NS*sizeof(int));
		star_y = malloc(NS*sizeof(int));
		star_z = malloc(NS*sizeof(int));
	}

	for (i=0; i<NS; i++) {
		star_x[i]=randnum(MAXX)-(MAXX/2);
		star_y[i]=randnum(MAXY)-(MAXY/2);
		star_z[i]=randnum(640);
	}
}

/* Draws a point using a triangle strip */
void poly_pnt(int x, int y, float z, float size, int color) {
	vertex_oc_t vert;
	
	vert.flags = TA_VERTEX_NORMAL;
	vert.x = x;
	vert.y = y + size;
	vert.z = z;
	vert.a = 1.0f;
	vert.r = color / 256.0f;
	vert.g = color / 256.0f;
	vert.b = color / 256.0f;
	ta_commit_vertex(&vert, sizeof(vert));
	
	vert.y = y;
	ta_commit_vertex(&vert, sizeof(vert));
	
	vert.flags = TA_VERTEX_EOL;
	vert.x = x + size;
	vert.y = y + size;
	ta_commit_vertex(&vert, sizeof(vert));
}

void stars_one_frame() {
	int i, x1, y1, xn, yn, zn, c;
	poly_hdr_t poly;

	/* Send polygon header to the TA using store queues */
	ta_poly_hdr_col(&poly, TA_OPAQUE);
	ta_commit_poly_hdr(&poly);

	/* Calculate each star's position and plot it on screen */
	for (i=0; i<NS; i++) {
		/* Calculate star perspective */
		xn = star_x[i]; yn = star_y[i]; zn = star_z[i];
		x1 = xn*zk / (zn + zk);
		y1 = yn*zk / (zn + zk);

		if (x1>-320 && y1>-240 && x1<320 && y1<240) {
			c = (zn * 256/640) & 0xff;
			poly_pnt(x1+320, y1+240, 1.0f, 4.0f, 255 - c);
		} else {
			star_z[i] = 640;
		}

		/* Move star's Z coord to show motion inward */
		star_z[i]-=8;
	}
}

/********************************************************************/
/* Draws some nifty 3D cubes on the screen */

/* Cube data is now an ordered list of triangle strips */
#define NUM_FACES 6
int cube_points[] = {
	-1, -1,  1,	/* Front plane */
	-1,  1,  1,
	 1, -1,  1,
	 1,  1,  1,

	 1, -1, -1,	/* Back plane */
	 1,  1, -1,
	-1, -1, -1,
	-1,  1, -1,

	-1, -1, -1,	/* Left plane */
	-1,  1, -1,
	-1, -1,  1,
	-1,  1,  1,

	 1, -1,  1,	/* Right plane */
	 1,  1,  1,
	 1, -1, -1,
	 1,  1, -1,

	-1, -1, -1,	/* Top plane */
	-1, -1,  1,
	 1, -1, -1,
	 1, -1,  1,
	
	-1,  1,  1,	/* Bottom plane */
	-1,  1, -1,
	 1,  1,  1,
	 1,  1, -1
};

void blagh(int x) { x++; }

int rotang = 0;
#define zkonst 128
#define mult 64
float cubesizes[6] = { 0.0f };
int tmpframe = 0;
void draw_cube(int which) {
	int cp;
	int ra, rao, ra2;
	float x, y, z, tx, ty, tz;
	float xt, yt;
	float xtrans, ytrans, ztrans;
	vertex_oc_t vert;

	cp = 0;

	if (cubesizes[which] < 0.1f)
		return;

	ra = (rotang*2) % 256;
	ra = (ra + 42*which) % 256;	/* heh */
	ra2 = (rotang/2);
	
	/* If the current parameters don't make you motion sick,
	   then try setting *32 on ytrans to something higher =) */
	xtrans = mcos(ra) * 220;
	ytrans = msin((ra*3) % 256) * 32;
	ztrans = msin(ra) * 256 + 256.0;

	/* Try commenting this out and setting -O1 in GCC 3.0 for a
	   fun light show.. gods bless GCC's amazing SH-4
	   optimizations! Hallelujah! */
	/* blagh((int)(xtrans * 100));
	blagh((int)(ytrans * 100));
	blagh((int)(ztrans * 100)); */

	/* if (!(tmpframe++ % 30)) {
		printf("Cube %d at %d,%d,%d\n", which,
			(int)(xtrans*100),
			(int)(ytrans*100),
			(int)(ztrans*100));
	} */

	for (cp=0; cp<(NUM_FACES*4*3); cp+=3) {
		x = cube_points[cp+0] * mult * cubesizes[which];
		y = cube_points[cp+1] * mult * cubesizes[which];
		z = cube_points[cp+2] * mult * cubesizes[which];

		tx = (mcos(ra)*x - msin(ra)*y);
		ty = (mcos(ra)*y + msin(ra)*x);
		x = tx; y = ty;
		
		tz = (mcos(ra2)*z - msin(ra2)*y);
		ty = (mcos(ra2)*y + msin(ra2)*z);
		y = ty; z = tz;

		tx = (mcos(ra)*x - msin(ra)*z);
		tz = (mcos(ra)*z + msin(ra)*x);
		x = tx; z = tz;
		
		z += ztrans;

		xt = (x*zkonst) / (zkonst+z+mult);
		yt = (y*zkonst) / (zkonst+z+mult);

		xt += xtrans;
		yt += ytrans;

		if ((cp % 12) == 9)
			vert.flags = TA_VERTEX_EOL;
		else
			vert.flags = TA_VERTEX_NORMAL;
		vert.x = xt+320.0f; vert.y = yt+240.0f; vert.z = 128.0 - (z/64.0);
		vert.a = 0.8f;
		if (ztrans == 0) ztrans++;
		switch((cp % 4)) {
			case 0:
				vert.r = 192.0f/ztrans; vert.g = 0.0f; vert.b = 0.0f;
				break;
			case 1:
				vert.r = 0.0f; vert.g = 192.0f/ztrans; vert.b = 0.0f;
				break;
			case 2:
				vert.r = 0.0f; vert.g = 0.0f; vert.b = 192.0f/ztrans;
				break;
			case 3:
				vert.r = 192.0f/ztrans; vert.g = 192.0f/ztrans; vert.b = 0.0f;
				break;
		}

		ta_commit_vertex(&vert, sizeof(vert));
	}
}

/* Draw six cubes arranged in a circle */
int zooming = 1;
void cube_one_frame() {
	int i, j;

	rotang = (rotang+1) % 512;

	if (zooming) {
		for (j=0; j<6; j++) {
			if (cubesizes[j] < 1.0f) {
				cubesizes[j] += 1/85.0f;
				break;
			} else {
				cubesizes[j] = 1.0f;
			}
		}
		if (j >= 6)
			zooming = 0;
	}
	for (i=0; i<6; i++) {
		draw_cube(i);
	}
}

void cubes_one_frame() {
	poly_hdr_t poly;
	
	/* Send polygon header to the TA using store queues */
	ta_poly_hdr_col(&poly, TA_TRANSLUCENT);
	ta_commit_poly_hdr(&poly);

	/* Draw cubes */
	cube_one_frame();
}

/**********************************************************/
/* Port of an OLD OLD PCX loading function =) */

struct pcx_hdr {
	char   Mfg;               // manufacturer, always 0xa0
	char   Ver;               // encoder version number (5)
	char   Enc;               // encoding code, always 1
	char   Bpp;               // bits per pixel, 8 in mode 0x13
	uint16 Xmin,Ymin;         // image origin, usually 0,0
	uint16 Xmax,Ymax;         // image dimensions
	uint16 Hres;              // horizontal resolution value
	uint16 Vres;              // vertical resolution value
	char   Pal[48];           // palette (not in mode 0x13)
	char   Reserved;          // who knows?
	char   ClrPlanes;         // number of planes, 1 in mode 0x13
	uint16 Bpl;               // bytes per line, 80 in mode 0x13
	uint16 plType;            // Grey or Color palette flag
	char   Filler[58];        // Zsoft wanted a 128 byte header
};

short	imageWidth,imageHeight;
uint8	*image;			/* Allocate this first */
uint8	*pcxpal;
char	*charmap;

int load_pcx(char *pcxdata) {
	int	bytes;         // counts unpacked bytes
	char	c;	       // byte being processed
	int	runlen,q;      // length of packet
	int	num_bytes;
	struct  pcx_hdr pcxh;
	char	*imgret;

	bytes = 0;

	memcpy(&pcxh, pcxdata, sizeof(pcxh)); pcxdata += sizeof(pcxh);
	if (pcxh.Bpp!=8) {
		printf("PCX data is not 8bpp\r\n");
		return 0;
	}

	imageWidth=pcxh.Xmax+1;
	imageHeight=pcxh.Ymax+1;
	num_bytes = imageWidth * imageHeight;
	printf("Image is %dx%d (%d bytes)\r\n", imageWidth, imageHeight, num_bytes);

	do {
		c=*(pcxdata++);

		if ((c & 0xc0) == 0xc0) {   // high 2 bits set is packet
			runlen = (c & 0x3f);	  // AND off the high bits
			c=*(pcxdata++);
			while(runlen--) (image[bytes++]=c);
		}
		else
			image[bytes++]=c;
	} while (bytes<num_bytes);

	pcxdata++;			      // this is a marker before the palette
	memcpy(pcxpal, pcxdata, 768); pcxdata+=768;

	return 1;
}

/**********************************************************/
/* Scrolly routines */

#include "gfx/font14_256.h"
#define FONT_NAME font14_256_pcx
#define FONT_WIDTH 8
#define FONT_HEIGHT 9
#define FONT_PIC_WIDTH 256
#define FONT_PIC_HEIGHT 256
#define FONT_DOUBLE 2.2
char font_map[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789?:;/!\"#$%&'[]*+,-."
	"abcdefghijklmnopqrstuvwxyz^_@ ";
#define FONT_HAS_LC

/*
#include "gfx/font5_256.h"
#define FONT_NAME font5_256_pcx
#define FONT_WIDTH 16
#define FONT_HEIGHT 20
#define FONT_PIC_WIDTH 256
#define FONT_PIC_HEIGHT 256
#define FONT_DOUBLE 1
char font_map[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789+#!*:.,\\?-+=@$%() ";
#undef FONT_HAS_LC
*/

#define FONT_PERROW (FONT_PIC_WIDTH / FONT_WIDTH)
#define FONT_ROWS (480 / FONT_HEIGHT)

typedef struct {
	float	x, y, fade;
	char	*chars;
} fontrow_t;
fontrow_t font_rows[FONT_ROWS];

char *scrollypos = NULL;
char scrolly[] =
"\x02Stars:2ndMix\0"
"By Dan Potter\0"
"\r\0"

"\x0c"
"Hi there.. welcome to the second\0"
"released demo for the Dreamcast\0"
"video game system. It's not quite\0"
"so simple anymore. :]\0"
"\0"
"In the background you can see a\0"
"simple star effect, playing over\0"
"an S3M by Krystall. Krystall was\0"
"a good friend in the days of\0"
"Digital Infinity so I hope he'll\0"
"forgive me for using his\0"
"track..:]\0"
"\r\0"

"\x0d"
"You can also see a little cube\0"
"flying around back there. At long\0"
"last we can make use of the 3D\0"
"acceleration hardware in the DC.\0"
"This demo has come a long way since\0"
"its humble beginnings.\0"
"\0"
"The music is running entirely\0"
"in the dedicated sound CPU, using\0"
"an S3M player I wrote way back\0"
"when. It takes no main processor\0"
"cycles. Pretty cool, huh?\0"
"\r\0"

"\x0c"
"The source code to this demo\0"
"and things to help you make\0"
"your own cool demos and games\0"
"can be found here:\0"
"\0"
"http://dcdev.allusion.net/\0"
"\0"
"There is NO Katana code in this\0"
"program or any others on my site.\0"
"Rather, it uses the new Cryptic\0"
"Allusion DC operating system,\0"
"KallistiOS.\0"
"\r\0"

"\x09"
"Quick hellos to the people out\0"
"in the dcdev 'scene' and the\0"
"folks at Sega [we love your\0"
"machine, sorry it didn't work\0"
"out for you].\0"
"\0"
"Well.. the other effects never\0"
"got ported so here is where it\0"
"wraps. Hit START to exit!\0"
"\a\0";
int active_lines = 0, pause_count = 0, mode = 0;

/* Draws a font letter using two triangle strips */
void font_draw_char(int x1, int y1, float color, int ch) {
	int	index, ix, iy;
	float	u1, v1, u2, v2;
	vertex_ot_t vert;

	index = charmap[ch];
	ix = (index % FONT_PERROW) * FONT_WIDTH;
	iy = (index / FONT_PERROW) * FONT_HEIGHT;
	u1 = ix * 1.0f / FONT_PIC_WIDTH;
	v1 = iy * 1.0f / FONT_PIC_HEIGHT;
	u2 = (ix+FONT_WIDTH) * 1.0f / FONT_PIC_WIDTH;
	v2 = (iy+FONT_HEIGHT) * 1.0f / FONT_PIC_HEIGHT;

	if (index == -1)
		return;

	vert.flags = TA_VERTEX_NORMAL;
	vert.x = x1;
	vert.y = y1 + FONT_HEIGHT*FONT_DOUBLE;
	vert.z = 512.0f;
	vert.u = u1;
	vert.v = v2;
	vert.a = color;
	vert.r = 0.0f;
	vert.g = 0.75f;
	vert.b = 1.0f;
	vert.oa = vert.or = vert.og = vert.ob = 0.0f;
	ta_commit_vertex(&vert, sizeof(vert));
	
	vert.x = x1;
	vert.y = y1;
	vert.u = u1;
	vert.v = v1;
	ta_commit_vertex(&vert, sizeof(vert));
	
	vert.x = x1 + FONT_WIDTH*FONT_DOUBLE;
	vert.y = y1 + FONT_HEIGHT*FONT_DOUBLE;
	vert.u = u2;
	vert.v = v2;
	ta_commit_vertex(&vert, sizeof(vert));

	vert.flags = TA_VERTEX_EOL;
	vert.x = x1 + FONT_WIDTH*FONT_DOUBLE;
	vert.y = y1;
	vert.u = u2;
	vert.v = v1;
	ta_commit_vertex(&vert, sizeof(vert));
}

void font_draw_string(int x1, int y1, float color, char *str) {
	while (*str) {
		font_draw_char(x1, y1, color, *str++);
		x1 += (int)(FONT_WIDTH*FONT_DOUBLE+1);
	}
}

void font_next_screen() {
	int width, height;
	int y, y1, x;
	
	if (!scrollypos)
		scrollypos = scrolly;

	memset(font_rows, 0, sizeof(font_rows));

	active_lines = *scrollypos++;
	y1 = (480 - active_lines*(FONT_HEIGHT*FONT_DOUBLE+4))/2;
	y=0;
	while(*scrollypos!='\r' && *scrollypos!='\a') {
		x = strlen(scrollypos);
		width = x * (int)(FONT_WIDTH*FONT_DOUBLE+1);

		font_rows[y].x = (640-width)/2;
		font_rows[y].y = y1;
		font_rows[y].chars = scrollypos;
		font_rows[y].fade = 0.0f;
		scrollypos += x+1;
		y1 += (int)(FONT_HEIGHT*FONT_DOUBLE+4);
		y++;
	}
	
	if (*scrollypos == '\a') {
		scrollypos = scrolly;
	}
	else {
		scrollypos += 2;
	}
}

#if 0
/* Debug code to draw the font texture */
void blit_font_texture() {
	vertex_ot_t vert;
	
	vert.flags = TA_VERTEX_NORMAL;
	vert.x = 50.0f;
	vert.y = 50.0f + 512.0f;
	vert.z = 512.0f;
	vert.u = 0.0f;
	vert.v = 1.0f;
	vert.a = 0.6f; vert.r = 1.0f; vert.g = 1.0f; vert.b = 1.0f;
	vert.oa = vert.or = vert.og = vert.ob = 0.0f;
	ta_commit_vertex(&vert, sizeof(vert));

	vert.x = 50.0f;
	vert.y = 50.0f;
	vert.u = 0.0f;
	vert.v = 0.0f;
	ta_commit_vertex(&vert, sizeof(vert));

	vert.x = 50.0f + 512.0f;
	vert.y = 50.0f + 512.0f;
	vert.u = 1.0f;
	vert.v = 1.0f;
	ta_commit_vertex(&vert, sizeof(vert));

	vert.flags = TA_VERTEX_EOL;
	vert.x = 50.0f + 512.0f;
	vert.y = 50.0f;
	vert.u = 1.0f;
	vert.v = 0.0f;
	ta_commit_vertex(&vert, sizeof(vert));
	
	return;
}
#endif

void font_one_frame() {
	int		done, y, actrows;
	poly_hdr_t	poly;

	actrows = 0;
	
	/* Start a textured polygon set (with the font texture) */
	ta_poly_hdr_txr(&poly, TA_TRANSLUCENT, TA_ARGB4444,
		256, 256, txr_font, TA_NO_FILTER);
	ta_commit_poly_hdr(&poly);

	//blit_font_texture();
	//return;

	/* Draw all font rows */
	for (y=0; y<FONT_ROWS; y++) {
		if (font_rows[y].fade >= 0.05f && font_rows[y].chars != NULL) {
			font_draw_string(font_rows[y].x, font_rows[y].y,
				font_rows[y].fade, font_rows[y].chars);
			actrows++;
		}
	}

	/* Do any pausing */
	if (pause_count > 0) {
		pause_count--;
		return;
	}

	if (!mode) {
		done = 1;
		for (y=0; y<FONT_ROWS; y++) {
			if (font_rows[y].fade < 1.0f) {
				font_rows[y].fade += 0.05f;
				done = 0;
			}
		}
		if (done) {
			mode = 1;
			pause_count = actrows * 60;
		}
	} else {
		done = 1;
		for (y=0; y<FONT_ROWS; y++) {
			if (font_rows[y].chars != NULL && font_rows[y].fade >= 0.1f) {
				font_rows[y].fade -= 0.1f;
				done = 0;
			}
		}

		if (done) {
			mode = 0;
			pause_count = 60;
			font_next_screen();
		}
	}
}

#define tolower(c) ((c) >= 'A' && (c) <='Z' ? (c)+('a' - 'A') : (c))

void font_init() {
	int x, y, c;
	uint8 pcxpall[768];
	volatile uint16 *vtex;
	uint16 val;

	vtex = (uint16*)ta_txr_map(txr_font);

	charmap = malloc(256);
	image = malloc(FONT_PIC_WIDTH * FONT_PIC_HEIGHT);
	pcxpal = pcxpall;
	
	if (!load_pcx(FONT_NAME)) {
		printf("Couldn't load PCX of font image\r\n");
		return;
	}

	printf("Drawing into 0x%08lx\r\n", vtex);
	for (y=0; y<FONT_PIC_HEIGHT; y++) {
		for (x=0; x<FONT_PIC_WIDTH; x++) {
			val = pcxpal[image[y*256+x]*3];
			if (val != 0)
				val = ((val >> 4) << 8)
					| ((val >> 4) << 4)
					| ((val >> 4) << 0)
					| 0xf000;
			*vtex++ = val;
		}
	}
	
	for (c=0; c<255; c++)
		charmap[c] = -1;
	for (c=0; c<strlen(font_map); c++) {
		charmap[font_map[c]] = c;
#ifndef FONT_HAS_LC
		charmap[tolower(font_map[c])] = c;
#endif
	}
	charmap[' '] = -1;
		
	memset(font_rows, 0, sizeof(font_rows));

	font_next_screen();
	
	free(image);
}

/********************************************************************/

int framecnt = 0;
void draw_one_frame() {
	/* Begin opaque polygons */
	ta_begin_render();

	/* Draw stars */
	stars_one_frame();

	/* Begin translucent polygons */
	ta_commit_eol();

	/* Draw cubes */
	cubes_one_frame();

	/* Draw scrolly */
	font_one_frame();
	
	/* Finish up */
	ta_commit_eol();
	ta_finish_frame();
	
	framecnt++;
}

extern uint8 romdisk_boot[];

/* Main program: init and loop drawing polygons */
// #include "song.h"
int main() {
	int i;
	cont_cond_t cond;

	/* Initialize all other hardware */
	kos_init_all(IRQ_ENABLE | TA_ENABLE, romdisk_boot);

	printf("2ndMix/KallistiOS starting\n");

	printf("Initializing stars\n");
	stars_init();
	printf("Init font\n");
	font_init();

	printf("Loading music\n");
	play_s3m("/rd/e-79014.s3m");

	printf("Starting display\n");
	while(1) {
		if (cont_get_cond(maple_first_controller(), &cond) < 0)
			break;
		if (!(cond.buttons & CONT_START))
			break;
		draw_one_frame();
	}

	printf("Shutting down\n");
	kos_shutdown_all();

	printf("Done, returning\n");
	return 0;
}


