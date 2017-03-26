#include <curses.h>
#include <stdio.h>
#include <string.h>
#include "sh4sim.h"

/* Ported from my Python debugger */

/******************************************************** Code Window ***/
typedef struct {
	int	x1, y1, width, height;	/* Window coordinates */
	WINDOW*	cwnd;			/* Curses window */
	char**	wndlines;		/* An array of the lines of the display */
	uint32	wndpa;			/* Top-of-window program address */
	uint32	pc;			/* Current program counter */
	uint32	spa;			/* Selected program address */
} codewnd_t;
static codewnd_t code;

void codewnd_init(WINDOW *cwnd, int x, int y, int w, int h) {
	int i;
	
	code.cwnd = cwnd;
	code.x1 = x; code.y1 = y; code.width = w; code.height = h;
	wborder(code.cwnd, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE,
		ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
	mvwaddstr(code.cwnd, 0, 2, "[Code]");
	
	if ((regs.pc & ~0xe0000000) > 8)
		code.wndpa = regs.pc - 8;
	else
		code.wndpa = regs.pc;
	code.pc = regs.pc;
	code.spa = regs.pc;
	code.wndlines = malloc((code.height-2) * sizeof(char*));
	for (i=0; i<(code.height-2); i++)
		code.wndlines[i] = malloc(200);
}

char* codewnd_compose_line(uint32 addr) {
	char buffer[200];
	static char buffer2[200];
	char *da = disasm_insn(addr);
	char chars[2];
	int  charsorig[2];
	int i, lt, o;
	
	sim_read(addr, 2, (uint8*)chars);
	charsorig[0] = chars[0]; charsorig[1] = chars[1];
	if (chars[0] < 32 || chars[0] > 126)
		chars[0] = '.';
	if (chars[1] < 32 || chars[1] > 126)
		chars[1] = '.';
	
	lt = 0; o=0;
	for (i=0; i<strlen(da); i++) {
		if (da[i] == '\t') {
			int j;
			for (j=0; j<15 - (i - lt); j++)
				buffer[o++] = ' ';
			lt = i;
		} else {
			buffer[o++] = da[i];
		}
	}
	buffer[o] = '\0';

	sprintf(buffer2, "%08x  %c%c  %02x%02x  %s",
		addr,
		chars[0], chars[1],
		charsorig[1]&0xff, charsorig[0]&0xff,
		buffer);
	
	return buffer2;
}

void codewnd_repaint() {
	int i, q, lt;
	char buffer[200];
	for (i=0; i<(code.height-2); i++) {
		strcpy(buffer, code.wndlines[i]);
		for (q=strlen(buffer); q<code.width-2; q++)
			buffer[q] = ' ';
		buffer[q] = '\0';
		if (code.wndpa+i*2 == code.pc)
			for (q=0; q<strlen(buffer); q++) {
				if (buffer[q] == ' ')
					buffer[q] = '*';
			}
		if (code.wndpa+i*2 == code.spa)
			wstandout(code.cwnd);
		mvwaddstr(code.cwnd, i+1, 1, buffer);
		if (code.wndpa+i*2 == code.spa)
			wstandend(code.cwnd);
	}
	wrefresh(code.cwnd);
}

void codewnd_refresh() {
	int i;
	for (i=0; i<(code.height-2); i++) {
		strcpy(code.wndlines[i], codewnd_compose_line(code.wndpa+i*2));
	}
	codewnd_repaint();
}

void codewnd_draw() { codewnd_refresh(); }

void codewnd_set_params(uint32 wndpa, uint32 pc, uint32 spa) {
	code.wndpa = wndpa;
	code.pc = pc;
	code.spa = spa;
}

void codewnd_update_pc(uint32 pc) {
	code.pc = pc;
	code.spa = pc;
	if (pc < code.wndpa || pc >= (code.wndpa + (code.height-2)*2)) {
		code.wndpa = pc - 8;
		codewnd_refresh();
	} else
		codewnd_repaint();
}

void codewnd_move_cursor(uint32 spa) {
	code.spa = spa;
	if (spa < code.wndpa || spa >= (code.wndpa + (code.height-2)*2)) {
		code.wndpa = spa - 8;
		codewnd_refresh();
	} else
		codewnd_repaint();
}

void codewnd_cursor_up() {
	code.spa -= 2;
	if (code.spa < code.wndpa) {
		code.wndpa -= 16;
		codewnd_refresh();
	} else
		codewnd_repaint();
}

void codewnd_cursor_down() {
	code.spa += 2;
	if (code.spa >= (code.wndpa + (code.height-2)*2)) {
		code.wndpa += 16;
		codewnd_refresh();
	} else
		codewnd_repaint();
}

/******************************************************** Regs Window ***/
typedef struct {
	WINDOW*	cwnd;
	int	x1, y1, width, height;
} regswnd_t;
static regswnd_t rwnd;

void regswnd_init(WINDOW *cwnd, int x, int y, int w, int h) {
	rwnd.cwnd = cwnd;
	rwnd.x1 = x; rwnd.y1 = y; rwnd.width = w; rwnd.height = h;
	wborder(rwnd.cwnd, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE,
		ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
	mvwaddstr(rwnd.cwnd, 0, 2, "[Regs]");
}

void regswnd_draw() {
	char buffer[200];
	int i;
	
	for (i=0; i<16; i++) {
		if (i < 10)
			sprintf(buffer, "R%d   %08x", i, regs.r[i]);
		else
			sprintf(buffer, "R%d  %08x", i, regs.r[i]);
		mvwaddstr(rwnd.cwnd, 1+i, 1, buffer);
	}

	sprintf(buffer, "PC   %08x", regs.pc); mvwaddstr(rwnd.cwnd, 18, 1, buffer);
	sprintf(buffer, "PR   %08x", regs.pr); mvwaddstr(rwnd.cwnd, 19, 1, buffer);
	sprintf(buffer, "SR   %08x", regs.sr); mvwaddstr(rwnd.cwnd, 20, 1, buffer);
	sprintf(buffer, "  t      %d", (regs.sr & SR_T_MASK)?1:0); mvwaddstr(rwnd.cwnd, 21, 1, buffer);
	sprintf(buffer, "  imask  %d", (regs.sr & SR_I_MASK)>>4); mvwaddstr(rwnd.cwnd, 22, 1, buffer);
	sprintf(buffer, "  md     %d", (regs.sr & SR_MD_MASK)?1:0); mvwaddstr(rwnd.cwnd, 23, 1, buffer);
	sprintf(buffer, "  rb     %d", (regs.sr & SR_RB_MASK)?1:0); mvwaddstr(rwnd.cwnd, 24, 1, buffer);
	sprintf(buffer, "  bl     %d", (regs.sr & SR_BL_MASK)?1:0); mvwaddstr(rwnd.cwnd, 25, 1, buffer);
	sprintf(buffer, "GBR   %08x", regs.gbr); mvwaddstr(rwnd.cwnd, 27, 1, buffer);
	sprintf(buffer, "VBR   %08x", regs.vbr); mvwaddstr(rwnd.cwnd, 28, 1, buffer);
	sprintf(buffer, "DBR   %08x", regs.dbr); mvwaddstr(rwnd.cwnd, 29, 1, buffer);
	sprintf(buffer, "MACH  %08x", regs.mach); mvwaddstr(rwnd.cwnd, 30, 1, buffer);
	sprintf(buffer, "MACL  %08x", regs.macl); mvwaddstr(rwnd.cwnd, 31, 1, buffer);
	sprintf(buffer, "FPSCR %08x", regs.fpscr); mvwaddstr(rwnd.cwnd, 32, 1, buffer);
	wrefresh(rwnd.cwnd);
}

/******************************************************** Msgs Window ***/
#include <stdarg.h>

typedef struct {
	WINDOW* cwnd;
	int	x1, y1, width, height;
	
	char**	lines;			/* Lines of display text */
	int	linecnt, colcnt;	/* Number of lines, cols of text */
} msgswnd_t;
static msgswnd_t msgs;

void msgswnd_init(WINDOW *cwnd, int x, int y, int w, int h) {
	int i;
	
	msgs.cwnd = cwnd;
	msgs.x1 = x; msgs.y1 = y; msgs.width = w; msgs.height = h;
	wborder(msgs.cwnd, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE,
		ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
	mvwaddstr(msgs.cwnd, 0, 2, "[Messages]");
	
	msgs.linecnt = msgs.height - 2;
	msgs.colcnt = msgs.width - 2;
	msgs.lines = malloc(msgs.linecnt * sizeof(char*));
	for (i=0; i<msgs.linecnt; i++)
		msgs.lines[i] = malloc(msgs.colcnt+1);
}

void msgswnd_draw() {
	int i;
	for (i=0; i<msgs.linecnt; i++) {
		mvwhline(msgs.cwnd, i+1, 1, 32, msgs.colcnt);
		mvwaddstr(msgs.cwnd, i+1, 1, msgs.lines[i]);
	}
	wrefresh(msgs.cwnd);
}

void msgswnd_write_one_line(char* line) {
	int i;
	for (i=0; i<(msgs.linecnt-1); i++) {
		memcpy(msgs.lines[i], msgs.lines[i+1], msgs.colcnt+1);
	}
	if (strlen(line) >= msgs.colcnt)
		line[msgs.colcnt] = '\0';
	strcpy(msgs.lines[msgs.linecnt-1], line);
	msgswnd_draw();
}

/* Need to break up lines */
void msgswnd_write_message(char* line) {
	msgswnd_write_one_line(line);
}

extern FILE* debug_log;
void msgswnd_printf(char* fmt, ...) {
	va_list		args;
	int		rv;
	char		buffer[1024];
	
	va_start(args, fmt);
	rv = vsprintf(buffer, fmt, args);
	va_end(args);
	msgswnd_write_message(buffer);
	if (debug_log)
		fprintf(debug_log, "%s", buffer);
}


/******************************************************** Global Screen ***/
typedef struct {
	WINDOW*	cwnd;			/* Curses object of the whole screen */
	int	scrn_w, scrn_h;		/* Width and height of screen */
} scrn_t;
static scrn_t scrn;

void draw_menubar() {
	char txtbuffer[400] = "j-Jump J-JumpHere F5-Go F6-AutoStep F7-Step F8-Step2Here F9-Run2Here";
	int i;
	
	for (i=strlen(txtbuffer); i<scrn.scrn_w; i++)
		txtbuffer[i] = ' ';
	txtbuffer[i] = '\0';
	wstandout(scrn.cwnd);
	mvwaddstr(scrn.cwnd, 0, 0, txtbuffer);
	wstandend(scrn.cwnd);
}

void setup_codewnd() {
	int w = scrn.scrn_w - 20;
	int h = scrn.scrn_h - 8;
	int x = 0;
	int y = 1;
	WINDOW* cwnd = subwin(scrn.cwnd, h, w, y, x);
	codewnd_init(cwnd, x, y, w, h);
	codewnd_draw();
}

void setup_regswnd() {
	int w = 21;
	int h = scrn.scrn_h - 8;
	int x = scrn.scrn_w - 21;
	int y = 1;
	WINDOW* cwnd = subwin(scrn.cwnd, h, w, y, x);
	regswnd_init(cwnd, x, y, w, h);
	regswnd_draw();
}

void setup_msgswnd() {
	int w = scrn.scrn_w;
	int h = 8;
	int x = 0;
	int y = scrn.scrn_h - 8;
	WINDOW* cwnd = subwin(scrn.cwnd, h, w, y, x);
	msgswnd_init(cwnd, x, y, w, h);
	msgswnd_draw();
}

void screen_init() {
	WINDOW* tmp;
	
	scrn.cwnd = initscr();
	noecho();
	keypad(scrn.cwnd, 1);
	getmaxyx(scrn.cwnd, scrn.scrn_h, scrn.scrn_w);
	
	draw_menubar();
	setup_codewnd();
	setup_regswnd();
	setup_msgswnd();
	
}


void screen_run() {
	int k, quit = 0;
	while (!quit) {
		k = getch();
		switch(k) {
			case KEY_UP:
				codewnd_cursor_up();
				break;
			case KEY_DOWN:
				codewnd_cursor_down();
				break;
			case KEY_PPAGE:
				codewnd_move_cursor(code.wndpa - (code.height-2)*2);
				break;
			case KEY_NPAGE:
				codewnd_move_cursor(code.wndpa + (code.height-2)*2);
				break;
			case KEY_F(9): {
				uint32 here = code.spa;
				DEBUG("Running until PC==%08x\n", here);
				while (regs.pc != here) {
					sim_exec_single();
				}
				regswnd_draw();
				codewnd_update_pc(regs.pc);
				DEBUG("Done\n", 0);
				break;
			}
			case KEY_F(8): {
				uint32 here = code.spa;
				DEBUG("Stepping until PC==%08x\n", here);
				while (regs.pc != here) {
					sim_exec_single();
					codewnd_update_pc(regs.pc);
					regswnd_draw();
				}
				DEBUG("Done\n", 0);
				break;
			}
			case KEY_F(7):
				sim_exec_single();
				codewnd_update_pc(regs.pc);
				regswnd_draw();
				break;
			case 'J':
				regs.pc = regs.npc = code.spa;
				codewnd_update_pc(regs.pc);
				regswnd_draw();
				break;
			case 'q':
				quit = 1;
				break;
			default:
				DEBUG("Received unknown keypress %d\n", k);
		}
	}
}


void screen_shutdown() {
	endwin();
}

