/*
    Ninja Sample

    COPYRIGHT (C) SEGA ENTERSRISES,LTD.

    VMS LCD Sample for SET5

    1998.7.28
*/

#include <shinobi.h>
#include "lcdlib.h"

NJS_PERIPHERAL *per,*per1;

void SetLCD(void);

/*========================================================*/
void main(void)
{
#ifdef __GNUC__
	shinobi_workaround();
#endif
    njUserInit();
    for(;;) {
        if(njUserMain() < 0) break;
        njWaitVSync();
    }
    njUserExit();
}
/*========================================================*/
static Sint8 texbuf[0x40000];

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
    njInitTextureBuffer(texbuf, sizeof(texbuf));
    njInitVertexBuffer(10000, 0, 10000, 0, 0);
    njInitPrint(NULL, 0, 0);
    njSetAspect(1.0f, 1.0f);
    njSetBackColor(0xff0000ff, 0xff0000ff, 0x00000000);
    lcdInit();
}
/*========================================================*/
extern Uint32 lcdFrameCount;

Sint32 njUserMain(void)
{
    int cnt;
    per=njGetPeripheral(NJD_PORT_A0);

    SetLCD();

    njPrintC(NJM_LOCATION(10,2), "LCD SAMPLE #2");
    njPrintH(NJM_LOCATION(30,2), lcdFrameCount, 4);
    njPrintH(NJM_LOCATION(10,23), per->x1, 8);
    njPrintH(NJM_LOCATION(10,24), per->y1, 8);

    return NJD_USER_CONTINUE;
}
/*========================================================*/
void njUserExit(void)
{
    njExitPrint();
    njExitTexture();
    sbExitSystem();
}
/*========================================================*/
/*
#include    "vmstst0.dat"
#include    "vmstst1.dat"
*/
#include "testfont.dat"

static int testxpos=48,testypos=0;
static int testdir=1,testcnt=0;
unsigned char *fonttable[]={
    eisu1x1,
hira1x1,
kata1x1,
kigo1x1,
alpa1x2,
kigo1x2,
suji1x2,
hira2x2,
kata2x2,
kigo2x2,
/*
kanji_00,
kanji_01,
kanji_02,
kanji_03,
kanji_04,
kanji_05,
kanji_06,
kanji_07,
kanji_08,
kanji_09,
kanji_10,
kanji_11,
kanji_12,
*/
kanji_13,
/*
kanji_14,
kanji_15,
kanji_16,
*/
};

extern int revtest,pictnum=0;

void SetLCD(void)
{
    int cnt;

    lcdFillData(0x00);

    lcdSetData(fonttable[pictnum], testxpos, testypos, 0);

    if(++testcnt > 2) {
        testxpos += (per->x1 / 16);
        testypos += (per->y1 / 16);
        njPrintH(NJM_LOCATION(20,23), testxpos, 8);
        njPrintH(NJM_LOCATION(20,24), testypos, 8);
        testcnt = 0;
    }

    if(per->press & PDD_DGT_KR)
        testxpos-=8;
    if(per->press & PDD_DGT_KL)
        testxpos+=8;
    if(per->press & PDD_DGT_KD)
        testypos-=8;
    if(per->press & PDD_DGT_KU)
        testypos+=8;
    if(per->press & PDD_DGT_TA)
        revtest ^= 1;
    if(per->press & PDD_DGT_ST)
        testxpos = testypos = 0;
    if(per->press & PDD_DGT_TX)
        if(pictnum < 10) pictnum++;
    if(per->press & PDD_DGT_TY)
        if(pictnum > 0) pictnum--;

    lcdSync();
}
