/*
    Ninja Sample

    COPYRIGHT (C) SEGA ENTERSRISES,LTD.

    Print Sample for SET5

    1998.10.8
*/

#include <shinobi.h>
#include <sg_pdvib.h>

Uint32 gFrameCount;

void VibTest(void);
void disp_usage(void);

void njUserInit(void)
{
	gFrameCount = 0;

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
	njSetBackColor(0x00000000, 0x00000000, 0x00000000);
}


Sint32 njUserMain(void)
{
	njPrintC(NJM_LOCATION(4,  2), "MAXI SAMPLE");
	njPrintH(NJM_LOCATION(20,  2), gFrameCount++, 8);

	VibTest();

	return NJD_USER_CONTINUE;
}

void njUserExit(void)
{
	sbExitSystem();
}



void VibTest(void)
{
	const PDS_PERIPHERAL* per;
	static const Uint32 vibno[] = {PDD_PORT_A1, PDD_PORT_A2};
	Sint32 i;
	Sint32 vibport;
	PDS_VIBPARAM param;

	per = pdGetPeripheral(PDD_PORT_A0);

	vibport = -1;

	/* A1とA2のどっちに振動パックがあるかチェック */
	for (i = 0; i < 2; i++) {
		if (pdVibMxIsReady(vibno[i])) {
			vibport = vibno[i];
			break;
		}
	}

	if (vibport == -1) {
		if (gFrameCount & 0x18) {
			njPrintC(NJM_LOCATION(3, 20), "PLEASE CONNECT MAXI TO A-1 OR A-2.");
		}
	} else {
		njPrintC(NJM_LOCATION(8, 20), "PRESS BUTTON TO VIBRATE.");
		disp_usage();
		if (per->press & PDD_DGT_TA) {
			/* Aボタンで単発振動 */
			param.unit = 1;
			param.flag = 0;
			param.power = 7;
			param.freq = 15;
			param.inc = 0;
			pdVibMxStart(vibport, &param);
		}
		if (per->press & PDD_DGT_TB) {
			/* Bボタンで単発収束振動 */
			param.unit = 1;
			param.flag = PDD_VIB_FLAG_CONVERGENCE;
			param.power = 7;
			param.freq = 15;
			param.inc = 1;
			pdVibMxStart(vibport, &param);
		}
		if (per->press & PDD_DGT_KL) {
			/* 十字キー左で正方向連続振動 */
			param.unit = 1;
			param.flag = PDD_VIB_FLAG_CONTINUOUS;
			param.power = 7;
			param.freq = 15;
			param.inc = 0;
			pdVibMxStart(vibport, &param);
		}
		if (per->press & PDD_DGT_KR) {
			/* 十字キー右で負方向連続振動 */
			param.unit = 1;
			param.flag = PDD_VIB_FLAG_CONTINUOUS;
			param.power = -7;
			param.freq = 15;
			param.inc = 0;
			pdVibMxStart(vibport, &param);
		}
		if (per->press & PDD_DGT_KU) {
			/* 十字キー上で正方向連続収束振動 */
			param.unit = 1;
			param.flag = PDD_VIB_FLAG_CONTINUOUS | PDD_VIB_FLAG_CONVERGENCE;
			param.power = 7;
			param.freq = 15;
			param.inc = 1;
			pdVibMxStart(vibport, &param);
		}
		if (per->press & PDD_DGT_KD) {
			/* 十字キー下で負方向連続収束振動 */
			param.unit = 1;
			param.flag = PDD_VIB_FLAG_CONTINUOUS | PDD_VIB_FLAG_CONVERGENCE;
			param.power = -7;
			param.freq = 15;
			param.inc = 1;
			pdVibMxStart(vibport, &param);
		}
		if (per->press & PDD_DGT_ST) {
			/* スタートボタンで振動停止 */
			pdVibMxStop(vibport);
		}
	}
}

void disp_usage(void)
{
	Sint32 x, y;

	x = 4;
	y = 4;

	njPrintC(NJM_LOCATION(x, y + 0), "UP....CONTINUOUS,CONVERGENCE");
	njPrintC(NJM_LOCATION(x, y + 1), "DOWN..CONTINUOUS,CONVERGENCE,INVERT");
	njPrintC(NJM_LOCATION(x, y + 2), "LEFT..CONTINUOUS");
	njPrintC(NJM_LOCATION(x, y + 3), "RIGHT.CONTINUOUS,INVERT");
	njPrintC(NJM_LOCATION(x, y + 4), "A.....ONE SHOT");
	njPrintC(NJM_LOCATION(x, y + 5), "B.....ONE SHOT,CONVERGENCE");
}
