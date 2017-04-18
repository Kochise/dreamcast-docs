/*
    Gdfs Sample

    COPYRIGHT (C) SEGA ENTERSRISES,LTD.

    FileRead Sample

    1999.01.18
*/

#include <shinobi.h>


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
Uint32 *ReadBuf1;
char fname[] = "M0000.";
GDFS gdfs;
Sint32 rsize = 0;
Sint32 rnum = 0;

enum main_mode {
	MODE_INIT,
	MODE_OPEN,
	MODE_ALLOC,
	MODE_CALC,
	MODE_READ,
	MODE_WAIT,
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

    mode = MODE_INIT;
}


Sint32 njUserMain(void)
{
    Sint32 i;
    Sint32 ret;

    switch (mode){
    case MODE_INIT:
        sprintf(msgbuf, "Filename: %s", fname);
        PutMsg(msgbuf);

        mode = MODE_OPEN;
        break;

    case MODE_OPEN:
        /* open file */
        gdfs = gdFsOpen(fname, NULL);
        sprintf(msgbuf, "gdFsOpen: %08x", (int) gdfs);
        PutMsg(msgbuf);

        if (gdfs == NULL) {
            mode = MODE_HALT;
            break;
        }

        mode = MODE_ALLOC;
        break;

    case MODE_ALLOC:
        /* allocate a buffer */
        ReadBuf1 = syMalloc(0x180000);
        if (ReadBuf1 == NULL) {
            sprintf(msgbuf, "not enough memory.");
            PutMsg(msgbuf);

            mode = MODE_HALT;
            break;
        }

        mode = MODE_CALC;
        break;

    case MODE_CALC:
        /* get file size */
        gdFsGetFileSize(gdfs, &rsize);
        sprintf(msgbuf, "FileSize: %d", (int) rsize);
        PutMsg(msgbuf);

        /* calc sctor size */
        rsize = gdFsCalcSctSize(rsize);
        sprintf(msgbuf, "FileSctSize: %d", (int) rsize);
        PutMsg(msgbuf);

        mode = MODE_READ;
        break;

    case MODE_READ:
        /* request to read */
        ret = gdFsReqRd32(gdfs, rsize, ReadBuf1);
        sprintf(msgbuf, "gdFsReqRd32: %d", (int) ret);
        PutMsg(msgbuf);

        if (ret < 0) {
            sprintf(msgbuf, "can't read.");
            PutMsg(msgbuf);

            mode = MODE_HALT;
            break;
        }

        mode = MODE_WAIT;
        break;

    case MODE_WAIT:
        {
            Sint32 stat;
            rnum = gdFsGetNumRd(gdfs);

            /* wait during reading */
            if ((stat = gdFsGetStat(gdfs)) != GDD_STAT_READ) {
                if (stat == GDD_STAT_ERR) {
                    PutMsg("Read error:");
                    mode = MODE_HALT;
                    break;
                }
                
                mode = MODE_COMPLETE;
                break;
            }
        }
        break;

    case MODE_COMPLETE:
        /* close file */
        gdFsClose(gdfs);

        PutMsg("Complete:");
        mode = MODE_HALT;
        break;

    default:
        break;
    }

    /* display phase */
    njPrintC(NJM_LOCATION(2,2), "GDFS SAMPLE");

    if (rsize > 0) {
        sprintf(msgbuf, "%d (%d/%d)", rnum, rnum*100/rsize/2048, 100);
        njPrintC(NJM_LOCATION(2,4), msgbuf);
    }

    for (i = MAX_WIN_LINE; i > 0; i--) {
        njPrintC(NJM_LOCATION(2,6+i-1), MessageWin[i-1]);
    }

    return NJD_USER_CONTINUE;
}


void njUserExit(void)
{
    njExitPrint();
    sbExitSystem();
}

/* eof */
