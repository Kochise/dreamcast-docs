/*
	Ninja Sample

	COPYRIGHT (C) SEGA ENTERSRISES,LTD.

	Backup Sample (Dynamic Work Allocation) #1

	1999.5.31
*/

#include <shinobi.h>
#include "backup.h"

Sint32 gFrameCount;
const PDS_PERIPHERAL* gPad[4];

void DispBackupRAMInfo(Sint32 x, Sint32 y, Sint32 drive);
void MountCheck(void);

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
    njInitVertexBuffer( 10000, 0, -1, 0, 0);
    njInitPrint(NULL, 0, 0);
    njPrintSize(14);
	njSetBackColor(0x00000000, 0x00000000, 0x0000C060);

	BupInit();
}

Sint32 njUserMain(void)
{
	Sint32 drive;
	Sint32 x, y;
	Sint32 i;

	gPad[0] = pdGetPeripheral(PDD_PORT_A0);
	gPad[1] = pdGetPeripheral(PDD_PORT_B0);
	gPad[2] = pdGetPeripheral(PDD_PORT_C0);
	gPad[3] = pdGetPeripheral(PDD_PORT_D0);

	njPrintColor(0xffc0c0c0);
	njPrintC(NJM_LOCATION(2, 2), "BACKUP SAMPLE #D-1");
	njPrintH(NJM_LOCATION(30, 2), gFrameCount++, 8);

	MountCheck();

	x = 2;
	y = 2;
	for (drive = 0; drive < 8; drive++) {
		y = drive * 2 + 6;
		DispBackupRAMInfo(x, y, drive);
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



/*===============================================================*/
/* バックアップRAMのマウントを行う                               */
/* そのバックアップRAMの接続されたコントローラーの、             */
/*   Aボタン ... スロット1のメモリーカードのマウント             */
/*   Bボタン ... スロット1のメモリーカードのアンマウント         */
/*   Xボタン ... スロット2のメモリーカードのマウント             */
/*   Yボタン ... スロット2のメモリーカードのアンマウント         */
/* で、ワークの確保とマウント、アンマウントを行います            */
/*===============================================================*/

void MountCheck(void)
{
	const BACKUPINFO* binfo;
	BUS_DISKINFO* diskinfo;
	Sint32 drive;
	Sint32 i;

	drive = 0;
	for (i = 0; i < 4; i++, drive += 2) {
		if (gPad[i]->press & PDD_DGT_TA) {
			binfo = BupGetInfo(drive);
			if (binfo->Connect) {
				BupMount(drive);
			}
		} else if (gPad[i]->press & PDD_DGT_TB) {
			BupUnmount(drive);
		}

		if (gPad[i]->press & PDD_DGT_TX) {
			binfo = BupGetInfo(drive + 1);
			if (binfo->Connect) {
				BupMount(drive + 1);
			}
		} else if (gPad[i]->press & PDD_DGT_TY) {
			BupUnmount(drive + 1);
		}
	}
}

