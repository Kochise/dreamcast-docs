/********************************************************************
 *  Shinobi Library Sample
 *  Copyright (c) 1998 SEGA
 *
 *  Library : Ninja
 *  Module  : Debug print
 *  File    : dbgcons.c
 *  Date    : 1999-05-27
 *  Version : 1.00
 *  Note    : This file provides a simple console interface with
 *            njDebugPrint().
 ********************************************************************/

#include <shinobi.h>
#include "dbgcons.h"
#include <stdarg.h>

/*-------------------------------------------------------------------------*/
typedef struct {
	char* buf;              /* テキストバッファアドレス                    */
	                        /* Text Buffer Address                         */
	Sint32 cx, cy;          /* カーソル位置                                */
	                        /* Cursor Position                             */
	Sint32 x, y, w, h;      /* コンソールの座標(x,y)とサイズ(w,h)          */
	                        /* Console position(x,y) and size(w,h)         */
	Uint32 count;           /* サーバーが呼ばれるたびにカウントアップ      */
	                        /* Count up when server function is called     */
} CONSOLECTX;

static CONSOLECTX ConsoleCtx;
static CONSOLECTX* cn;

static void ResetCursorBlink(void);

/*-------------------------------------------------------------------------*/
/*===============================================================*/
/* コンソールの初期化                                            */
/* Initialize console                                            */
/*===============================================================*/

void ConInit(Sint32 x, Sint32 y, Sint32 w, Sint32 h, void* buf)
{
	cn = &ConsoleCtx;
	cn->buf = (char*)buf;
	cn->cx = 0;
	cn->cy = 0;
	cn->x = x;
	cn->y = y;
	cn->w = w;
	cn->h = h;
	cn->count = 0;

	memset(buf, ' ', w * h);
}

/*-------------------------------------------------------------------------*/
/*===============================================================*/
/* コンソールの終了                                              */
/* Finalize console                                              */
/*===============================================================*/
void ConExit(void)
{
	memset(cn, 0, sizeof(*cn));
}

/*-------------------------------------------------------------------------*/
/*===============================================================*/
/* カーソル位置へ１文字表示                                      */
/* Put an character into cursor position                         */
/*===============================================================*/
void ConPutc(char ch)
{
	cn->buf[cn->cx + cn->cy * cn->w] = ch;
}

/*-------------------------------------------------------------------------*/
/*===============================================================*/
/* １行スクロール                                                */
/* Scrolle one line                                              */
/*===============================================================*/
void ConRoll(void)
{
	Sint32 i, j;
	char* d;
	char* s;

	d = cn->buf;
	s = d + cn->w;
	for (i = 0; i < cn->h - 1; i++) {
		for (j = 0; j < cn->w; j++) {
			*d++ = *s++;
		}
	}

	d =cn->buf + cn->w * (cn->h - 1);
	for (j = 0; j < cn->w; j++) {
		*d++ = ' ';
	}
}

/*-------------------------------------------------------------------------*/
/*===============================================================*/
/* カーソル位置へ文字列表示(カーソル位置更新)                    */
/* Put an string into cusor position(w/Cursor position update)   */
/*===============================================================*/

void ConPrint(const char* str)
{
	char ch;

	while (ch = *str++) {
		if (ch == '\n') {
			cn->cy++;
			cn->cx = 0;
		}
		if (ch == 0x08) {	/* BS */
			if (cn->cx > 0) cn->cx--;
			ConPutc(' ');
		}
		if (ch == '\t') {	/* TAB */
			cn->cx += 4;
			cn->cx &= ~3;
			ConPutc(' ');
		}

		if (cn->cx >= cn->w) {
			cn->cx = 0;
			cn->cy++;
		}
		if (cn->cy >= cn->h) {
			cn->cy--;
			cn->cx = 0;
			ConRoll();
		}

		if (ch == '\n') continue;
		if (ch == '\t') continue;
		if (ch == 0x08) continue;
		if (ch == 0x7f) continue;

		ConPutc(ch);
		cn->cx++;
	}

	cn->count = 1 << 4;
}

/*-------------------------------------------------------------------------*/
/*===============================================================*/
/* カーソル位置へprintf()書式文字列表示(カーソル位置更新)        */
/* Put an printf() format string into cusor position             */
/* (w/Cursor position update)                                    */
/*===============================================================*/

void ConPrintf(const char* fmt, ...)
{
	static char buffer[512];
	va_list va;

	va_start(va, fmt);
	vsprintf(buffer, fmt, va);
	va_end(va);

	ConPrint(buffer);
}

/*-------------------------------------------------------------------------*/
/*===============================================================*/
/* カーソル位置設定                                              */
/* Set cursor position                                           */
/*===============================================================*/

void ConLocate(Sint32 x, Sint32 y)
{
	if (x < 0) x = 0;
	if (y < 0) y = 0;
	if (x >= cn->w) x = cn->w;
	if (y >= cn->h) y = cn->h;

	cn->cx = x;
	cn->cy = y;

	ResetCursorBlink();
}

/*-------------------------------------------------------------------------*/
/*===============================================================*/
/* カーソル位置取得                                              */
/* Get cursor position                                           */
/*===============================================================*/

void ConGetPos(Sint32* x, Sint32* y)
{
	*x = cn->cx;
	*y = cn->cy;
}

/*-------------------------------------------------------------------------*/
/*===============================================================*/
/* サーバー関数 テキストバッファの内容を描画                     */
/* Server function:Render the text buffer                        */
/*===============================================================*/

void ConMain(void)
{
	Sint32 i, j, x, y;
	char* p;
	char buf[2];

	buf[1] = '\0';

	p = cn->buf;
	for (i = 0; i < cn->h; i++) {
		for (j = 0; j < cn->w; j++, p++) {
			x = cn->x + j;
			y = cn->y + i;
			buf[0] = *p;
			njPrintC(NJM_LOCATION(x, y), buf);
		}
	}

	cn->count++;
}


/*-------------------------------------------------------------------------*/
/*===============================================================*/
/* テキストバッファのクリアとホーム位置への移動                  */
/* Clear the text buffer and set cursor position to (0,0)        */
/*===============================================================*/

void ConCls(void)
{
	memset(cn->buf, ' ', cn->w * cn->h);
	cn->cx = 0;
	cn->cy = 0;
}

/*-------------------------------------------------------------------------*/
/*===============================================================*/
/* カーソルの表示                                                */
/* Put cursor                                                    */
/*===============================================================*/

void ConDispCursor(void)
{
	if ((cn->count >> 4) & 1) {
		njPrintC(NJM_LOCATION(cn->x + cn->cx, cn->y + cn->cy), "_");
	}
}

/*-------------------------------------------------------------------------*/
/*===============================================================*/
/* カーソルの点滅を初期化                                        */
/* Initialize the blink count of the cursor                      */
/*===============================================================*/

static void ResetCursorBlink(void)
{
	cn->count = 1 << 4;
}


