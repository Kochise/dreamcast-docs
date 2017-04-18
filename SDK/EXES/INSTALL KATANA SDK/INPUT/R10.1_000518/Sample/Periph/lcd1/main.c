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

    SetLCD();

    njPrintC(NJM_LOCATION(10,2), "LCD SAMPLE #1");
    njPrintH(NJM_LOCATION(30,2), lcdFrameCount, 4);

    return NJD_USER_CONTINUE;
}
/*========================================================*/
void njUserExit(void)
{
    njExitTexture();
    njExitPrint();
    sbExitSystem();
}
/*========================================================*/
#include    "testdata.dat"
static int testpos=2,testdir=1,testpat=0;
static int testcnt=0;
/*static int xpos[8]={32, 32, 32, 32, 32, 32, 32, 32};*/
static int xpos[8]={-21,-21,-21,-21,-21,-21,-21,-21};
static int xspd[8]={80, 70, 60, 50, 40, 30, 20, 10};

void SetLCD(void)
{
    int cnt;

    lcdFillData(0x00);

    for(cnt = 0; cnt < 8; cnt++) {
        if((testcnt % xspd[cnt]) == 0) {
            if(--xpos[cnt] < -22) {
                xpos[cnt] = 49;
            }
        }

        if((xpos[cnt] % 2) == 0) {
            lcdSetData(sampleOBJ1, xpos[cnt], cnt*3, cnt);
        } else {
            lcdSetData(sampleOBJ0, xpos[cnt], cnt*3, cnt);
        }
    }

    testcnt++;
    lcdSync();
}
