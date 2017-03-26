/* Taro ##version##
   
   menu.c
   
   (c)2002 Dan Potter
*/

#include "taro.h"

static pvr_ptr_t txr_font;
static float alpha;
static int frame;

typedef struct menu_item {
	char			name[256];
	char			cmd[256];
	struct menu_item	* next;
} menu_item_t;

static menu_item_t * items;
static int items_cnt;

static int selected;

static void init_txr() {
	uint16	*vram;
	int	x, y;

	txr_font = pvr_mem_malloc(256*256*2);
	vram = (uint16*)txr_font;

	for (y=0; y<8; y++) {
		for (x=0; x<16; x++) {
			bfont_draw(vram, 256, 0, y*16+x);
			vram+=16;
		}
		vram += 23*256;
	}
}

/* The following funcs blatently ripped from libconio =) */

/* Draw one font character (6x12) */
static void draw_char(float x1, float y1, float z1, float a, float r,
		float g, float b, int c) {
	pvr_vertex_t	vert;
	int ix, iy;
	float u1, v1, u2, v2;

	if (c == ' ')
		return;

	assert( c > ' ' && c < 127 );
	
	ix = (c % 16) * 16;
	iy = (c / 16) * 24;
	u1 = ix * 1.0f / 256.0f;
	v1 = iy * 1.0f / 256.0f;
	u2 = (ix+12) * 1.0f / 256.0f;
	v2 = (iy+24) * 1.0f / 256.0f;

	vert.flags = PVR_CMD_VERTEX;
	vert.x = x1;
	vert.y = y1 + 24;
	vert.z = z1;
	vert.u = u1;
	vert.v = v2;
	vert.argb = PVR_PACK_COLOR(a, r, g, b);
	vert.oargb = 0;
	pvr_prim(&vert, sizeof(vert));
	
	vert.x = x1;
	vert.y = y1;
	vert.u = u1;
	vert.v = v1;
	pvr_prim(&vert, sizeof(vert));
	
	vert.x = x1 + 12;
	vert.y = y1 + 24;
	vert.u = u2;
	vert.v = v2;
	pvr_prim(&vert, sizeof(vert));

	vert.flags = PVR_CMD_VERTEX_EOL;
	vert.x = x1 + 12;
	vert.y = y1;
	vert.u = u2;
	vert.v = v1;
	pvr_prim(&vert, sizeof(vert));
}

/* draw len chars at string */
static void draw_string(float x, float y, float z, float a, float r, float g,
		float b, char *str, int len) {
	int i;
	pvr_poly_cxt_t	cxt;
	pvr_poly_hdr_t	poly;

	pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB1555 | PVR_TXRFMT_NONTWIDDLED,
		256, 256, txr_font, PVR_FILTER_NONE);
	pvr_poly_compile(&poly, &cxt);
	pvr_prim(&poly, sizeof(poly));

	for (i = 0; i < len; i++) {
		draw_char(x, y, z, a, r, g, b, str[i]);
		x += 12;
	}
}

/* draw a box (used by cursor and border, etc) (at 1.0f z coord) */
static void draw_box(float x, float y, float w, float h, float z, float a, float r, float g, float b) {
	pvr_poly_cxt_t	cxt;
	pvr_poly_hdr_t	poly;
	pvr_vertex_t	vert;

	pvr_poly_cxt_col(&cxt, PVR_LIST_TR_POLY);
	pvr_poly_compile(&poly, &cxt);
	pvr_prim(&poly, sizeof(poly));

	vert.flags = PVR_CMD_VERTEX;
	vert.x = x;
	vert.y = y + h;
	vert.z = z;
	vert.u = vert.v = 0.0f;
	vert.argb = PVR_PACK_COLOR(a, r, g, b);
	vert.oargb = 0;
	pvr_prim(&vert, sizeof(vert));

	vert.y -= h;
	pvr_prim(&vert, sizeof(vert));

	vert.y += h;
	vert.x += w;
	pvr_prim(&vert, sizeof(vert));

	vert.flags = PVR_CMD_VERTEX_EOL;
	vert.y -= h;
	pvr_prim(&vert, sizeof(vert));
}

/* draw the cursor */
static void draw_cursor(float x1, float y1, float w, float h, float z, float a) {
}

int load_progs() {
	FILE	*f;
	char	buffer[256];
	menu_item_t	*item;

	f = fopen("/rd/programs.txt", "r");
	assert(f);

	items = NULL;
	items_cnt = 0;
	for( ; ; ) {
		if (!fgets(buffer, 255, f)) {
			printf("error reading programs.txt\n");
			return -1;
		}

		if (!strcmp(buffer, "-eof-\n"))
			break;


		item = malloc(sizeof(menu_item_t));
		item->next = items;
		items = item;
		strcpy(item->name, buffer);
		item->name[strlen(item->name)-1] = '\0';
		
		if (!fgets(item->cmd, 255, f)) {
			printf("error reading programs.txt\n");
			return -1;
		}
		item->cmd[strlen(item->cmd)-1] = '\0';
		items_cnt++;
	}
	
	return 0;
}

static uint32 last_btns = 0;
static void check_input() {
	uint8		cont;
	cont_cond_t	cond;

	cont = maple_first_controller();
	if (!cont)
		return;

	if (cont_get_cond(cont, &cond) < 0)
		return;

	if (last_btns != cond.buttons) {
		if (!(cond.buttons & CONT_DPAD_UP)) {
			selected--;
			if (selected < 0)
				selected += items_cnt;
		}
		if (!(cond.buttons & CONT_DPAD_DOWN)) {
			selected++;
			if (selected >= items_cnt)
				selected -= items_cnt;
		}
		if (!(cond.buttons & CONT_A)) {
			menu_item_t	*item;
			int		i;
			file_t		f;
			void		*where;

			for (item=items, i=0; i<selected; i++, item=item->next)
				;
			printf("Executing '%s'\n", item->cmd);

			f = fs_open(item->cmd, O_RDONLY);
			assert(f);
			where = fs_mmap(f);
			assert(where);
			arch_exec(where, fs_total(f));
		}
		last_btns = cond.buttons;
	}
}

int menu_init() {
	menu_item_t	*item;
	
	alpha = 0.0f;
	init_txr();
	load_progs();

	printf("Loaded items:\n");
	for (item=items; item; item=item->next) {
		printf("  '%s'  '%s'\n", item->name, item->cmd);
	}
	printf("End\n");

	frame = 0;
	selected = 0;
	
	return 0;
}

void menu_frame() {
	menu_item_t	*item;
	float		y;
	const char	* title = "Select a program";

	/* Delay */
	frame++;
	if (frame < 120)
		return;

	/* Adjust alpha */
	if (alpha < 1.0f)
		alpha += 1/30.0f;
	else
		alpha = 1.0f;

	/* Draw title */
	draw_box(90, 90, 640-180, 26, 100.0f, alpha * 0.3f, 0.7f, 0.0f, 0.0f);
	draw_string(320.0f - (12*strlen(title))/2, 91.0f, 101.0f, alpha, 1, 1, 1, title, strlen(title));
	
	/* Draw background plane */
	draw_box(90, 90+26, 640-180, 480-(180+26), 100.0f, alpha * 0.3f, 0.0f, 0.7f, 0.0f);

	/* Draw menu items */
	for (y=90+36, item=items; item; item=item->next, y+=25.0f) {
		draw_string(100.0f, y, 101.0f, alpha, 1, 1, 1, item->name, strlen(item->name));
	}

	/* Cursor */
	draw_box(90, 90 + 36 + selected * 25 - 1,
		640-180, 26, 100.5f, 
		alpha * 0.5f, 0.5f, 0, 0);

	/* Check for key input */
	check_input();
}
