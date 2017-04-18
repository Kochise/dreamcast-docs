/*
	Ninja Sample

	COPYRIGHT (C) SEGA ENTERSRISES,LTD.

	Backup Sample #D-2

	1999.5.31
*/

#include <shinobi.h>
#include "backup.h"

#define DRIVE 0

#define S_NOT_READY 0
#define S_READY     1
#define S_SAVE      2
#define S_LOAD      3
#define S_DELETE    4
#define S_COMPLETE  5

#define FNAME "SAVEDATA_002"
#define SAVEBUFFER SaveBuffer
#define SAVEBLOCKS 4

Sint32 save_file(void);
Sint32 load_file(void);
Sint32 delete_file(void);

Sint32 gFrameCount;
Uint32 gState;

extern Uint8 SaveData[];

Uint32 SaveBuffer[512 * SAVEBLOCKS / sizeof(Uint32)];

void DispBackupRAMInfo(Sint32 x, Sint32 y, Sint32 drive);

void njUserInit(void)
{
	gFrameCount = 0;
	gState = 0;

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
    njInitVertexBuffer( 10000, 0, -1, 0, 0);
    njInitPrint(NULL, 0, 0);
    njPrintSize(14);
	njSetBackColor(0x00000000, 0x00000000, 0x0000C060);

	BupInit();
}


Sint32 njUserMain(void)
{
	const PDS_PERIPHERAL* per;
	const BACKUPINFO *binfo;

	njPrintColor(0xffc0c0c0);
	njPrintC(NJM_LOCATION(2, 2), "BACKUP SAMPLE #D-2");
	njPrintH(NJM_LOCATION(30, 2), gFrameCount++, 8);

	per = pdGetPeripheral(PDD_PORT_A0);

	binfo = BupGetInfo(DRIVE);

	DispBackupRAMInfo(2, 22, 0);

	njPrintColor(0xffc0c0c0);
	switch (gState) {
		case S_NOT_READY:
			njPrintC(NJM_LOCATION(4, 4), "CONNECT MEMORY CARD TO PORT A-1");
			if (binfo->Connect) gState = S_READY;
			break;
		case S_READY:
			njPrintC(NJM_LOCATION(4, 4), "PRESS A BUTTON TO SAVE FILE");
			njPrintC(NJM_LOCATION(4, 5), "PRESS B BUTTON TO LOAD FILE");
			njPrintC(NJM_LOCATION(4, 6), "PRESS X BUTTON TO DELETE FILE");
			njPrintC(NJM_LOCATION(4, 7), "PRESS Y BUTTON TO MOUNT/UNMOUNT");
			if (per->press & NJD_DGT_TA) {
				memcpy(SAVEBUFFER, SaveData, SAVEBLOCKS * 512);
				BupSave(DRIVE, FNAME, SAVEBUFFER, SAVEBLOCKS);
				gState = S_SAVE;
			}
			if (per->press & NJD_DGT_TB) {
				BupLoad(DRIVE, FNAME, SAVEBUFFER);
				gState = S_LOAD;
			}
			if (per->press & NJD_DGT_TX) {
				BupDelete(DRIVE, FNAME);
				gState = S_DELETE;
			}
			if (per->press & PDD_DGT_TY) {
				binfo = BupGetInfo(DRIVE);
				if (binfo->Work == NULL) {
					BupMount(DRIVE);
				} else {
					BupUnmount(DRIVE);
				}
			}
			if (!binfo->Connect) gState = S_NOT_READY;
			break;
		case S_SAVE:
			njPrint(NJM_LOCATION(4, 8), "NOW SAVING...(%03d%%)",
			binfo->ProgressCount * 100 / binfo->ProgressMax);
			if (buStat(DRIVE) == BUD_STAT_READY) {
				gState = S_COMPLETE;
			}
			break;
		case S_LOAD:
			njPrint(NJM_LOCATION(4, 8), "NOW LOADING...(%03d%%)",
			binfo->ProgressCount * 100 / binfo->ProgressMax);
			if (buStat(DRIVE) == BUD_STAT_READY) {
				gState = S_COMPLETE;
			}
			break;
		case S_DELETE:
			njPrint(NJM_LOCATION(4, 8), "NOW DELETING...(%03d%%)",
			binfo->ProgressCount * 100 / binfo->ProgressMax);
			if (buStat(DRIVE) == BUD_STAT_READY) {
				gState = S_COMPLETE;
			}
			break;
		case S_COMPLETE:
			njPrint(NJM_LOCATION(4, 9), "COMPLETE[%s]",
			BupGetErrorString(binfo->LastError));
			njPrintC(NJM_LOCATION(4, 10), "PRESS BUTTON");
			if (per->press) {
				gState = S_NOT_READY;
			}
			break;
		default:
			break;
	}


	return NJD_USER_CONTINUE;
}



void njUserExit(void)
{
	BupExit();
	sbExitSystem();
	syBtExit();
}


/*===============================================================*/
/* バックアップRAMの状態を表示する                               */
/* 接続(マウント)されていなければ「---」を、                     */
/* フォーマットされていなければ  「UNFORMAT」を、                */
/* フォーマットされている場合は空き容量と最大容量を表示します。  */
/* また、そのドライブで使用しているワークアドレスと、サイズも    */
/* あわせて表示します。                                          */
/*===============================================================*/

void DispBackupRAMInfo(Sint32 x, Sint32 y, Sint32 drive)
{
	const BACKUPINFO* binfo;
	BUS_DISKINFO* diskinfo;

	binfo = BupGetInfo(drive);
	diskinfo = &binfo->DiskInfo;

	njPrintColor(0xffc0c080);
	njPrint(NJM_LOCATION(x, y), "MEMORY CARD #%d",drive);

	njPrintColor(0xffc0c0c0);
	if (binfo->Ready) {
		if (binfo->IsFormat) {
			njPrint(NJM_LOCATION(x + 15, y), "%04d/%04d BLOCKS",
				diskinfo->free_user_blocks,
				diskinfo->total_user_blocks);
		} else {
			njPrint(NJM_LOCATION(x + 15, y), "UNFORMAT        ");
		}
	} else {
		if (binfo->Operation == BUD_OP_MOUNT) {
			njPrint(NJM_LOCATION(x + 15, y), "CHECKING...     ");
		} else {
			njPrint(NJM_LOCATION(x + 15, y), "----------------");
		}
	}

	njPrintColor(0xff808080);
	njPrint(NJM_LOCATION(x + 15, y + 1),
		"%08X-%08X[%04X]", (Uint32)binfo->Work,
							(Uint32)binfo->Work + binfo->WorkSize - 1,
							binfo->WorkSize);
}


