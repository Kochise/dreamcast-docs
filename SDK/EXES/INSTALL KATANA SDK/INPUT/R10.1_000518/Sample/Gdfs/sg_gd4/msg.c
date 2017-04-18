/* msg.c */

#include <shinobi.h>
#include "msg.h"


/*** Message Scroll Subroutine ***/


static char *MessageWin[MAX_WIN_LINE];
static char MessageWinWork[MAX_WIN_LINE*MAX_MSG_LEN];
static Sint32 MsgLine;


static void scpy(char *src, char *dst)
{
	while (*src != (char) NULL) {
		*dst++ = *src++;
	}
	*dst = (char) NULL;
}


void initMsg(void)
{
	Sint32 i;
	Sint8 **mesp;
	Sint8 *mp;

	MsgLine = 0;
    for (mesp = (Sint8 **) MessageWin, mp = MessageWinWork; mesp < (Sint8 **) MessageWin + MAX_WIN_LINE; mesp++) {
		*mesp = mp;
		*mp = 0;
		mp += MAX_MSG_LEN;
	}
}


void putMsg(const char *msg)
{
	Sint32 i;

	if (MsgLine < MAX_WIN_LINE) {
        scpy((char *) msg, MessageWin[MsgLine]);

		MsgLine++;

	} else {
		Sint8 *tmp;

		tmp = MessageWin[0];
		for (i = 1; i < MAX_WIN_LINE; i++) {
			MessageWin[i - 1] = MessageWin[i];
		}
		MessageWin[MAX_WIN_LINE - 1] = tmp;

        scpy((char *) msg, MessageWin[MAX_WIN_LINE - 1]);
	}
}


void drawMsg(Sint32 x, Sint32 y)
{
	Sint32 i;

	for (i = MAX_WIN_LINE - 1; i >= 0; i--) {
		njPrintC(NJM_LOCATION(x, y + i), MessageWin[i]);
	}
}


/* eof */