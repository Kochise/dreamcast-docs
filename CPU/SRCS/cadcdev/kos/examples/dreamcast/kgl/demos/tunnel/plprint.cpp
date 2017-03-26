/* KallistiOS ##version##
 
   plprint.cpp
   (c)2002 Paul Boese

   Uses Steve Baker's PLIB that was ported by Peter Hatch.
*/

#include <kos.h>
#include <time.h>
#include <dcplib/fnt.h>
#include "plprint.h"

CVSID("$Id: plprint.cpp,v 1.2 2002/04/12 01:05:12 axlen Exp $");

extern uint8 romdisk[];

static fntRenderer *text;
static fntTexFont *font;

static int filter_mode = 1;

void plinit() {
	text = new fntRenderer ();
	font = new fntTexFont("/rd/courier-bold.txf");
	printf("Loading font\n");
}

void plprint(int x, int y, float r, float g, float b, const char *s, int fp) {
	text->setFilterMode(filter_mode);
	font->setFixedPitch(fp);
	if ((fp) == 1) {
		font->setGap(0.1);
		font->setWidth(0.5);
	}
	else {
		font->setGap(0.1);
		font->setWidth(1.0);
	}
	text->setFont(font);
	text->setPointSize(20);
	text->begin();
	text->setColor(r, g, b, 0.8f);
	text->start2f(x*16, y*16);
	text->puts(s);
	text->end();
}

