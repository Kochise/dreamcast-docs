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


/*** reading file routine ***/


Sint32 ReadFromFile(Sint8 *fname, GDFS_DIRREC dirrec, void *buf)
{
    GDFS gdfs;
    Sint32 ret;
    Sint32 size;

    sprintf(msgbuf, "Filename: %s", fname);
    PutMsg(msgbuf);

    /* open a file */
    gdfs = gdFsOpen(fname, dirrec);
    sprintf(msgbuf, "gdFsOpen: %08x", (int) gdfs);
    PutMsg(msgbuf);

    if (gdfs == NULL) return -1;

    /* get the file size */
    gdFsGetFileSize(gdfs, &size);
    sprintf(msgbuf, "FileSize: %d", (int) size);
    PutMsg(msgbuf);

    /* calc the sctor size */
    size = gdFsCalcSctSize(size);
    sprintf(msgbuf, "FileSctSize: %d", (int) size);
    PutMsg(msgbuf);

    /* read data(s) from the file */
    ret = gdFsRead(gdfs, size, buf);
    sprintf(msgbuf, "gdFsRead: %d", (int) ret);
    PutMsg(msgbuf);

    /* close the file */
    gdFsClose(gdfs);

    if (ret == GDD_ERR_OK) return 0;

    return -2;
}


/*** main routine ***/

Sint32 mode;

Uint32 ReadBuf1[8192/4];
Uint32 ReadBuf2[8192/4];
Uint32 ReadBuf3[8192/4];

Uint32 dirbuf[gdFsGetDirrecSize(64)/4];
GDFS_DIRREC sub2;

enum main_mode {
	MODE_INIT,
	MODE_READ1,
	MODE_READ2,
	MODE_READ3,
	MODE_COMPLETE,
	MODE_ERROR,
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
        /* load a directory to a buffer */
        sub2 = gdFsCreateDirhn((void *) dirbuf, 64);
        ret = gdFsLoadDir("SUBDIR2", sub2);

        mode = MODE_READ1;

    case MODE_READ1:
        /* read a file from a current directory */
        ret = ReadFromFile("ABC.DAT", NULL, (void *) ReadBuf1);

        if (ret != 0) mode = MODE_ERROR;
        else mode = MODE_READ2;
        break;

    case MODE_READ2:
        /* read a file with changing directory */
        gdFsChangeDir("SUBDIR1");

        ret = ReadFromFile("FFFF_FILLDATA.DAT", NULL, (void *) ReadBuf2);

        if (ret != 0) mode = MODE_ERROR;
        else mode = MODE_READ3;
        break;

    case MODE_READ3:
        /* read a file from a not-current directory */
        ret = ReadFromFile("8888_FILLDATA.DAT", sub2, (void *) ReadBuf3);

        if (ret != 0) mode = MODE_ERROR;
        else mode = MODE_COMPLETE;
        break;

    case MODE_COMPLETE:
        PutMsg("Complete:");
        mode = 99;
        break;

    default:
        break;
    }

    /* draw phase */
    njPrintC(NJM_LOCATION(2,2), "GDFS SAMPLE");
    for (i = MAX_WIN_LINE; i > 0; i--) {
        njPrintC(NJM_LOCATION(2,4+i-1), MessageWin[i-1]);
    }

    return NJD_USER_CONTINUE;
}


void njUserExit(void)
{
    njExitPrint();
    sbExitSystem();
}

/* eof */
