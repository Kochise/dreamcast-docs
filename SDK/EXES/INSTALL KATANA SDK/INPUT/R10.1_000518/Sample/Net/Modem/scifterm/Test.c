
/*
	Ninja Sample

	COPYRIGHT (C) SEGA ENTERSRISES,LTD.

	Print Sample for SET4

	1998.4.24
*/

#include <shinobi.h>
#include <machine.h>
#include "mdmAPI.h"
#include "sh4scif.h"

const char *printBuild = "scifterm Build:" __DATE__ "(" __TIME__")";

#define TEXT_OFFSET 2

extern long frxi_count;
extern long ftxi_count;
extern long feri_count;
extern long fbri_count;
extern long overrun_count;
extern long framing_count;
extern long parity_count;
extern long break_count;

MDM mdmHandle;
#define SCIF_RCV_BUF_SIZE 0x100
#define SCIF_SND_BUF_SIZE 0x100
char sciRcvBuf[SCIF_RCV_BUF_SIZE];
char sciSndBuf[SCIF_SND_BUF_SIZE];

#define MDM_RX_BUFSIZE 0x10000
#define MDM_TX_BUFSIZE 0x10000
char mdmRxBuf[MDM_RX_BUFSIZE];
char mdmTxBuf[MDM_TX_BUFSIZE];

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
	njSetBorderColor(0x00000000);
	njInitVertexBuffer(100000, 0, 800000, 0, 0);
    njSetBackColor(0x00000000, 0x00000000, 0x000000FF);
    njInitPrint(NULL, 0, 0);
    njPrintSize(14);

    /* Initialize the scif part of this sample */
	scif_init(sciRcvBuf, SCIF_RCV_BUF_SIZE, sciSndBuf, SCIF_SND_BUF_SIZE); /* for SCIF */
    scif_open(BPS_57600);
    /* Initialize the modem library */
	mdmInit(mdmRxBuf, mdmTxBuf, MDM_RX_BUFSIZE, MDM_TX_BUFSIZE);
	mdmHandle = mdmOpen(1);
	overrun_count =  parity_count = framing_count = break_count = frxi_count = feri_count = fbri_count = 0;
#if 1
	{
      const char sciMessage0[] =
        "\r\n\t***SCIF interface start.(57600 bps)***\r\n"
        "1: Change SPEED to  19200 bps\r\n"
        "2: Change SPEED to  38400 bps\r\n"
        "3: Change SPEED to  57600 bps\r\n"
        "4: Change SPEED to 115200 bps\r\n"
	    "\r\nInput Number(1-4) >";
	  const char sciMessage1[] =
	    "\r\n\tPlease Change TERMINAL setting...\r\n";
	  char *ptr;
	  static char buf[256];
	  MDS_DCB mdmDcb;
	  volatile int i;

      njPrintC(NJM_LOCATION(6,7),"Connect Set5 serial output to PC");
      njPrintC(NJM_LOCATION(6,8),"to control DC modem remotely.");

      njPrintC(NJM_LOCATION(6,10),"Please select serial");
      njPrintC(NJM_LOCATION(6,11),"speed from TERMINAL...");
      njPrintC(NJM_LOCATION(6,13),"Initial setting: 57600 bps");
      njPrintC(NJM_LOCATION(6,14),"  (8-N-1 HW Flow)");
      njPrintC(NJM_LOCATION(6,16),"From TERMINAL, type ATDT <number>");
      njWaitVSync();
      njWaitVSync();
      njWaitVSync();

	RETRY_INPUT_SPEED:
	  for(ptr = sciMessage0; *ptr != '\0'; ptr++){
	    scif_putq(*ptr);
	  }
	  while(1){
	    buf[0]=scif_get();
	    if((buf[0] >= '0') && (buf[0] <= '9')){
	      for(ptr = sciMessage1; *ptr != '\0'; ptr++){
		scif_putq(*ptr);
	      }
	      for(i = 0; i < 0x800000; i++){ /* WAIT ‚¢‚¢‰ÁŒ¸‚È‚È‚ª‚³ */
	      }
	      mdmGetCommState(&mdmDcb);
	      scif_close();
	      switch(buf[0]){
	      case '1':
		scif_open(BPS_19200);
		mdmDcb.LineSpeed = MDD_LINESPEED_19200;
		break;
	      case '2':
		scif_open(BPS_38400);
		mdmDcb.LineSpeed = MDD_LINESPEED_38400;
		break;
	      case '3':
		scif_open(BPS_57600);
		mdmDcb.LineSpeed = MDD_LINESPEED_57600;
		break;
	      case '4':
		scif_open(BPS_115200);
		mdmDcb.LineSpeed = MDD_LINESPEED_115200;
		break;
#if 0
	      default:
        scif_open(BPS_57600);
        mdmDcb.LineSpeed = MDD_LINESPEED_57600;
		goto RETRY_INPUT_SPEED;
		break;
#endif
	      }
	      mdmSetCommState(mdmDcb);
	      break;
	    }else{
	      /*	      scif_putq(buf[i]); *//* echo back */
	    }
	  }
	}
#endif
}


Sint32 frameCount = 0;
int wret, rret;

#define READ_BUF_LEN 256
char readBuf[READ_BUF_LEN];

#define WRITE_BUF_LEN 256
char writeBuf[WRITE_BUF_LEN];

Uint32 mdmStartTime, mdmEndTime, mdmElapTime;
Uint32 scifStartTime, scifEndTime, scifElapTime;

Sint32 njUserMain(void)
{
	Int y = 0, x = 0;
	int i,j;
	static char pbuf[2]={0,0};
	const int dispon = 1;
	MDS_DCB mdmDcb;

    scifElapTime = 0;
	mdmElapTime = 0;

	frameCount++;
	mdmGetCommState(&mdmDcb);

	if(dispon){
      njPrintC(NJM_LOCATION(TEXT_OFFSET,3),"Modem Sample - FRAME COUNT:");
      njPrintH(NJM_LOCATION(TEXT_OFFSET+28,3),frameCount, 8);

      njPrintC(NJM_LOCATION(TEXT_OFFSET,12), "--DCB STATUS--");
      njPrint(NJM_LOCATION(TEXT_OFFSET,13), "DTR:      %d", mdmDcb.Dtr);
      njPrint(NJM_LOCATION(TEXT_OFFSET,14), "RTS:      %d", mdmDcb.Rts);
      njPrint(NJM_LOCATION(TEXT_OFFSET,15), "CHARLEN:  %d", mdmDcb.CharLen);
      njPrint(NJM_LOCATION(TEXT_OFFSET,16), "PARITY:   %d", mdmDcb.Parity);
      njPrint(NJM_LOCATION(TEXT_OFFSET,17), "STOPBIT:  %d", mdmDcb.StopBit);
      njPrint(NJM_LOCATION(TEXT_OFFSET,18), "SETBREAK: %d", mdmDcb.SetBreak);
      njPrint(NJM_LOCATION(TEXT_OFFSET,19), "LINESPEED:%d", mdmDcb.LineSpeed);
      njPrint(NJM_LOCATION(TEXT_OFFSET,20), "CTS:      %d", mdmDcb.Cts);
      njPrint(NJM_LOCATION(TEXT_OFFSET,21), "DSR:      %d", mdmDcb.Dsr);
      njPrint(NJM_LOCATION(TEXT_OFFSET,22), "RI:       %d", mdmDcb.Ri);
      njPrint(NJM_LOCATION(TEXT_OFFSET,23), "DCD:      %d", mdmDcb.Dcd);
      njPrint(NJM_LOCATION(TEXT_OFFSET,24), "BRK:      %d", mdmDcb.Brk);

      njPrintC(NJM_LOCATION(TEXT_OFFSET,26), "--mdmAPI BUFFER STATUS--");
      njPrint(NJM_LOCATION(TEXT_OFFSET,27), "TxFree: 0x%8.8X", mdmTxFreeSize(mdmHandle));
      njPrint(NJM_LOCATION(TEXT_OFFSET,28), "TxAvail:0x%8.8X", mdmTxAvailSize(mdmHandle));
      njPrint(NJM_LOCATION(TEXT_OFFSET,29), "RxFree: 0x%8.8X", mdmRxFreeSize(mdmHandle));
      njPrint(NJM_LOCATION(TEXT_OFFSET,30), "RxAvail:0x%8.8X", mdmRxAvailSize(mdmHandle));
	}
	/* SCIF READ */
    scifStartTime = syTmrGetCount();

#if 0
	for(i = 0;(i < WRITE_BUF_LEN) && scif_isget(); i++){
#else
	for(i = 0;(i < mdmTxFreeSize(mdmHandle)) && scif_isget(); i++){
#endif
	  int get;
	  get = (char)scif_get();
	  pbuf[0] = writeBuf[i] = (char)get;
	}

    scifEndTime = syTmrGetCount();
	scifElapTime += syTmrCountToMicro(scifEndTime-scifStartTime);

	/* MODEM WRITE */
	if(i > 0){
	  int size;
	  char *ptr;

      mdmStartTime = syTmrGetCount();
      for(size = i, ptr = writeBuf;
	      wret != size;
	      size -= wret, ptr+= wret){
	    wret = mdmWrite(mdmHandle, ptr, size);
	  }
      mdmEndTime = syTmrGetCount();
	}
    mdmElapTime += syTmrCountToMicro(mdmEndTime-mdmStartTime);
	if(dispon){
      njPrintC(NJM_LOCATION(TEXT_OFFSET,6),"mdmWrite: ret = ");
      njPrintH(NJM_LOCATION(TEXT_OFFSET+strlen("mdmWrite: ret = "),6),wret, 8);
	}

	/* MODEM READ */
    mdmStartTime = syTmrGetCount();
#if 0
	rret = mdmRead(mdmHandle, readBuf, READ_BUF_LEN);
#else
	rret = mdmRead(mdmHandle, readBuf, scif_TxFreeSize());
#endif
    mdmEndTime = syTmrGetCount();
	mdmElapTime += syTmrCountToMicro(mdmEndTime-mdmStartTime);
	if(dispon){
      njPrintC(NJM_LOCATION(TEXT_OFFSET,5),"mdmRead:  ret = ");
      njPrintH(NJM_LOCATION(TEXT_OFFSET+strlen("mdmRead:  ret = "),5),rret, 8);

      njPrintC(NJM_LOCATION(TEXT_OFFSET,7),"scifPerf: ");
      njPrintD(NJM_LOCATION(TEXT_OFFSET+strlen("scifPerf: "),7), scifElapTime, 4);

      njPrintC(NJM_LOCATION(TEXT_OFFSET,8),"mdmPerf:  ");
      njPrintD(NJM_LOCATION(TEXT_OFFSET+strlen("mdmPerf:  "),8), mdmElapTime, 4);
    }

    {
	  static Uint32 byteSumR=0, byteSumW=0;
	  static Uint32 count=1;
	  static Uint32 averageR=0, averageW=0;
	  static char strbuf[1024];

	  /* Transfer Rate */
	  if(count++ > 30){
	    averageR = byteSumR/30;
	    byteSumR = 0;
	    averageW = byteSumW/30;
	    byteSumW = 0;
	    count = 1;
	  }
	  byteSumR += rret;
	  byteSumW += i;
	  if(dispon){
	    sprintf(strbuf, "mdmRead:  %4.4d bytes/frame", averageR);
        njPrintC(NJM_LOCATION(TEXT_OFFSET,9),strbuf);
	    sprintf(strbuf, "mdmWrite: %4.4d bytes/frame", averageW);
        njPrintC(NJM_LOCATION(TEXT_OFFSET,10),strbuf);
	  }
	}

	if(rret > 0){
	  char *str;
	  /* SCIF OUT */
	  str = readBuf;

      scifStartTime = syTmrGetCount();
      for(i = 0; i < rret; i++){
	    scif_putq(*str++);
	  }
      scifEndTime = syTmrGetCount();
	  scifElapTime += syTmrCountToMicro(scifEndTime-scifStartTime);
	}

    /* enable DTR LINE by PRESS A button */
	if (pdGetPeripheral(PDD_PORT_A0)->press & PDD_DGT_TA) {
	  mdmEnableDtr(mdmHandle);
	}
	/* disable DTR LINE by PRESS B button */
	if (pdGetPeripheral(PDD_PORT_A0)->press & PDD_DGT_TB) {
	  mdmDropDtr(mdmHandle);
	}
	if (pdGetPeripheral(PDD_PORT_A0)->press & PDD_DGT_TX) {
	  mdmPurgeTxBuffer(mdmHandle);
	}

	if (pdGetPeripheral(PDD_PORT_A0)->press & PDD_DGT_TY) {
	  mdmPurgeRxBuffer(mdmHandle);
	}
	if (pdGetPeripheral(PDD_PORT_A0)->press & PDD_DGT_ST) {
#if 0
	  return NJD_USER_EXIT;
#else
	  mdmClose(mdmHandle);
	  mdmFinish();
	  mdmInit(mdmRxBuf, mdmTxBuf, MDM_RX_BUFSIZE, MDM_TX_BUFSIZE);
	  mdmHandle = mdmOpen(1);
#endif
	}
	return NJD_USER_CONTINUE;
}

void njUserExit(void)
{
	mdmClose(mdmHandle);
	sbExitSystem();
}