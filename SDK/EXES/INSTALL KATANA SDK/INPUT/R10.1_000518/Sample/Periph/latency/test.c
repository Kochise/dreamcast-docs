/********************************************************************
 *  Shinobi Library Sample
 *  Copyright (c) 1998 SEGA
 *
 *  Library : Controller Library
 *  Module  :
 *  File    : test.c
 *  Date    : 1999-05-26
 *  Version : 1.00
 ********************************************************************/

#include <shinobi.h>

Uint32 gFrameCount;

/*===============================================================*/
/* 割り込みでパッドデータを取得するためのバッファ                */
/* Data buffer to get the peripheral data by interrupt.          */
/*===============================================================*/
PDS_PERIPHERAL PadBuf[4];

void PadIntFunc(void);
void PrintPeripheralInfo(Sint32 x, Sint32 y, const PDS_PERIPHERAL* per);

/*===============================================================*/
/* アプリケーションの初期化                                      */
/* Initialize application.                                       */
/*===============================================================*/

void njUserInit(void)
{
	gFrameCount = 0;
	njSetBorderColor(0);

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
    njInitVertexBuffer( 1000, 0, -1, 0, 0);
    njInitPrint(NULL, 0, 0);
    njPrintSize(14);
	njSetBackColor(0x00000000, 0x00000000, 0x000000FF);

	memset(PadBuf, 0, sizeof(PadBuf));

	/* 割り込み関数の登録            */
	/* Register an interrupt handler */
	pdSetIntFunction(PadIntFunc);
}


/*===============================================================*/
/* アプリケーションのメインループ                                */
/* Main loop of application.                                     */
/*===============================================================*/

Sint32 njUserMain(void)
{
	njPrintC(NJM_LOCATION(4,  2), "PERIPHERAL INTERRUPT SAMPLE");
	njPrintH(NJM_LOCATION(34,  2), gFrameCount, 4);

	PrintPeripheralInfo( 2,  4, &PadBuf[0]);
	PrintPeripheralInfo(22,  4, &PadBuf[1]);
	PrintPeripheralInfo( 2, 17, &PadBuf[2]);
	PrintPeripheralInfo(22, 17, &PadBuf[3]);

	gFrameCount++;

	return NJD_USER_CONTINUE;
}


/*===============================================================*/
/* アプリケーションの終了                                        */
/* Finalize application                                          */
/*===============================================================*/

void njUserExit(void)
{
	sbExitSystem();
	syBtExit();
}



/*===============================================================*/
/* コントローラデータを取得(割り込みハンドラ)                    */
/* Get the controller data (Interrupt handler)                   */
/*   ・ここでpdGetPeripheralDirect()を使用することにより、最小の */
/*     レイテンシでコントローラデータを取得することができます。  */
/*   ※従来のpdGetPeripheral()を使用しても、得られるデータは     */
/*     前のフレームのものとなりますので注意してください。        */
/*===============================================================*/

void PadIntFunc(void)
{
	pdGetPeripheralDirect(PDD_PORT_A0, &PadBuf[0], NULL, NULL);
	pdGetPeripheralDirect(PDD_PORT_B0, &PadBuf[1], NULL, NULL);
	pdGetPeripheralDirect(PDD_PORT_C0, &PadBuf[2], NULL, NULL);
	pdGetPeripheralDirect(PDD_PORT_D0, &PadBuf[3], NULL, NULL);

/*
	MODEM_SEND_DATA(&PadBuf[0], sizeof(PadBuf[0]));
	MODEM_SEND_DATA(&PadBuf[1], sizeof(PadBuf[1]));
	MODEM_SEND_DATA(&PadBuf[2], sizeof(PadBuf[2]));
	MODEM_SEND_DATA(&PadBuf[3], sizeof(PadBuf[3]));
*/

}


/*===============================================================*/
/* ペリフェラル情報の取得                                        */
/* Display the peripheral information.                           */
/*===============================================================*/

void PrintPeripheralInfo(Sint32 x, Sint32 y, const PDS_PERIPHERAL* per)
{
	njPrintC(NJM_LOCATION(x, y +  0), "SUPPORT:");
	njPrintC(NJM_LOCATION(x, y +  1), "ON     :");
	njPrintC(NJM_LOCATION(x, y +  2), "OFF    :");
	njPrintC(NJM_LOCATION(x, y +  3), "PRESS  :");
	njPrintC(NJM_LOCATION(x, y +  4), "RELEASE:");
	njPrintC(NJM_LOCATION(x, y +  5), "R      :");
	njPrintC(NJM_LOCATION(x, y +  6), "L      :");
	njPrintC(NJM_LOCATION(x, y +  7), "X1     :");
	njPrintC(NJM_LOCATION(x, y +  8), "Y1     :");
	njPrintC(NJM_LOCATION(x, y +  9), "X2     :");
	njPrintC(NJM_LOCATION(x, y + 10), "Y2     :");

	x += 8;
	njPrintH(NJM_LOCATION(x, y), per->support, 8);
	njPrintH(NJM_LOCATION(x, y + 1), per->on, 8);
	njPrintH(NJM_LOCATION(x, y + 2), per->off, 8);
	njPrintH(NJM_LOCATION(x, y + 3), per->press, 8);
	njPrintH(NJM_LOCATION(x, y + 4), per->release, 8);
	njPrintD(NJM_LOCATION(x + (per->r  >= 0), y + 5), per->r, 5);
	njPrintD(NJM_LOCATION(x + (per->l  >= 0), y + 6), per->l, 5);
	njPrintD(NJM_LOCATION(x + (per->x1 >= 0), y + 7), per->x1, 5);
	njPrintD(NJM_LOCATION(x + (per->y1 >= 0), y + 8), per->y1, 5);
	njPrintD(NJM_LOCATION(x + (per->x2 >= 0), y + 9), per->x2, 5);
	njPrintD(NJM_LOCATION(x + (per->y2 >= 0), y + 10), per->y2, 5);
}

