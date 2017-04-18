/*
    Gdfs Sample

    COPYRIGHT (C) SEGA ENTERSRISES,LTD.

    FileRead Sample with request queuing

    1999.01.19
*/

#include <shinobi.h>

#include "req.h"


/*** Message Scroll routine ***/

#define MAX_WIN_LINE  20
#define MAX_MSG_LEN  80


Sint8 *MessageWin[MAX_WIN_LINE];
Sint8 MessageWinWork[MAX_WIN_LINE*MAX_MSG_LEN];
Sint8 msgbuf[MAX_MSG_LEN];
Sint32 MsgLine;


void scpy(Sint8 *src, Sint8 *dst)
{
    while (*src != (Sint8) NULL) {
        *dst++ = *src++;
    }
    *dst = (Sint8) NULL;
}


void initMsg(void)
{
    Sint32 i;
    Sint8 **mesp;
    Sint8 *mp;

    MsgLine = 0;
    for (mesp = MessageWin, mp = MessageWinWork; mesp < MessageWin + MAX_WIN_LINE; mesp++) {
        *mesp = mp;
        *mp = 0;
        mp += MAX_MSG_LEN;
    }
}


void PutMsg(Sint8 *msg)
{
    Sint32 i;

    if (MsgLine < MAX_WIN_LINE) {
        scpy(msg, MessageWin[MsgLine]);

        MsgLine++;

    } else {
        Sint8 *tmp;

        tmp = MessageWin[0];
        for (i = 1; i < MAX_WIN_LINE; i++) {
            MessageWin[i - 1] = MessageWin[i];
        }
        MessageWin[MAX_WIN_LINE - 1] = tmp;

        scpy(msg, MessageWin[MAX_WIN_LINE - 1]);
    }
}


/*** main routine ***/

Sint32 mode;
Sint32 wait;
GDFS filehn[8];
Uint32 *ReadBuf[8];

enum main_mode {
	MODE_INIT,
	MODE_ALLOC,
	MODE_OPEN,
	MODE_READ,
	MODE_WAIT,
	MODE_CLOSE,
	MODE_COMPLETE,
	MODE_HALT,
	MODE_MAX
};


void njUserInit(void)
{
    /* Check the cable for NTSC/PAL or VGA.. works properly for SCART. */
    switch (syCblCheck())
	{
        /* Initialize the display device and set the frame buffer based on the video mode. */
        case SYE_CBL_NTSC:  /* U.S./North America NTSC (60Hz) and Brazil PAL-M (60Hz). */
            sbInitSystem (NJD_RESOLUTION_640x480_NTSCNI, NJD_FRAMEBUFFER_MODE_RGB565, 1);
            break;
        case SYE_CBL_PAL:   /* Europe PAL (50Hz) and Argentina PAL-N (50Hz). */
            sbInitSystem (NJD_RESOLUTION_640x544_PALNI, NJD_FRAMEBUFFER_MODE_RGB565, 1);
            break;
        case SYE_CBL_VGA:   /* Standard VGA. */
            sbInitSystem (NJD_RESOLUTION_VGA, NJD_FRAMEBUFFER_MODE_RGB565, 1);
            break;
        default:
            syBtExit();     /* Unknown video type, return to Dreamcast BootROM. */
	}
    njSetBorderColor( 0x00000000 ) ;
    njInitVertexBuffer( 100000, 0, 100000, 0, 0);
    njInitPrint(NULL, 0, 0);
    njPrintSize(14);
    njSetBackColor(0x00000000,0x00000000,0x000000FF);

    initMsg();

    ReqInit();

    mode = MODE_INIT;
    wait = 30;
}


Sint32 njUserMain(void)
{
    Sint32 i;
    Sint32 ret;

    switch (mode){
    case MODE_INIT:
        if (--wait <= 0) mode = MODE_ALLOC;
        break;
    
    case MODE_ALLOC:
        mode = MODE_OPEN;
        
        PutMsg("Alloc Buffer:");
        
        /* alloc buffers */
        for (i = 0; i < 8; i++) {
            if ((ReadBuf[i] = syMalloc(32768)) == NULL) mode = MODE_HALT;
        }
        break;
    
    case MODE_OPEN:
        mode = MODE_READ;
        
        PutMsg("File Open:");
        
        /* open files */
        for (i = 0; i < 8; i++) {
            sprintf(msgbuf, "F%04X.", (int) i);
            if ((filehn[i] = gdFsOpen(msgbuf, NULL)) == NULL) mode = MODE_HALT;
        }
        break;
    
    case MODE_READ:
        mode = MODE_WAIT;
        
        PutMsg("Request:");
        
        /* request to read */
        for (i = 0; i < 8; i++) {
            ReqRead(filehn[i], 16, ReadBuf[i]);
        }
        break;
    
    case MODE_WAIT:
        ret = ReqExec();
        sprintf(msgbuf, "Rest: %d", (int) ret);
        PutMsg(msgbuf);
        
        if (ret == 0) mode = MODE_CLOSE;
        break;
    
    case MODE_CLOSE:
        PutMsg("Close:");
        
        /* close files */
        for (i = 0; i < 8; i++) {
            gdFsClose(filehn[i]);
        }
        
        mode = MODE_COMPLETE;
        break;
    
    case MODE_COMPLETE:
        PutMsg("Complete:");
        mode = MODE_HALT;
        break;

    default:
        break;
    }


    /* display phase */
    njPrintC(NJM_LOCATION(2,2), "GDFS REQ-QUEUE SAMPLE");
    for (i = MAX_WIN_LINE; i > 0; i--) {
        njPrintC(NJM_LOCATION(2,5+i-1), MessageWin[i-1]);
    }

    return NJD_USER_CONTINUE;
}


void njUserExit(void)
{
    njExitPrint();
    sbExitSystem();
}

/* eof */
