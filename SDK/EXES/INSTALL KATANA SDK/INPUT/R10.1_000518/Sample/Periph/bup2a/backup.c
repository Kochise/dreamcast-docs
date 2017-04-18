/********************************************************************
 *  Shinobi Library Sample
 *  Copyright (c) 1998 SEGA
 *
 *  Library : Backup Library
 *  Module  : Library Sample
 *  File    : backup.c
 *  Date    : 1999-01-14
 *  Version : 1.00
 *
 ********************************************************************/

#include <shinobi.h>
#include "backup.h"

/*===============================================================*/
/* 対応するメモリーカードの最大容量                              */
/* Mamimum volume to use.                                        */
/*===============================================================*/

#define MAX_CAPS BUD_CAPACITY_1MB


/*===============================================================*/
/* 対応するメモリーカードのドライブ数                            */
/* Number of memory card to use.                                 */
/*===============================================================*/

#define MAX_DRIVES 8
#define USE_DRIVES BUD_USE_DRIVE_ALL


/*===============================================================*/
/* メモリーカードの状態を格納しておく構造体                      */
/* (backup.h を参照)                                             */
/* Structure to store the information of memory card.            */
/* (See backup.h)                                                */
/*===============================================================*/

BACKUPINFO gBupInfo[8];


/*===============================================================*/
/* バックアップライブラリが使用するワーク                        */
/* ４バイト境界で確保する                                        */
/* Work buffer that backup library uses.                         */
/* (Must be 4-bytes aligned.)                                    */
/*===============================================================*/

Uint32 gBupWork[BUM_WORK_SIZE(MAX_CAPS, MAX_DRIVES) / sizeof(Uint32)];


/*===============================================================*/
/*      スタティック関数のプロトタイプ宣言                       */
/*      Prototypes of static functions.                          */
/*===============================================================*/

static Sint32 BupComplete(Sint32 drive, Sint32 op, Sint32 stat, Uint32 param);
static Sint32 BupProgress(Sint32 drive, Sint32 op, Sint32 count, Sint32 max);
static void BupInitCallback(void);


/*===============================================================*/
/*      バックアップライブラリ初期化                             */
/*      Initialize backup library.                               */
/*===============================================================*/

void BupInit(void)
{
	memset(gBupInfo, 0, sizeof(gBupInfo));
	buInit(MAX_CAPS, USE_DRIVES, gBupWork, BupInitCallback);
}


/*===============================================================*/
/*      バックアップライブラリ終了                               */
/*      Finalize backup library.                                 */
/*===============================================================*/

void BupExit(void)
{
	do {} while (buExit() != BUD_ERR_OK);
}


/*===============================================================*/
/*      メモリーカードの状態を取得                               */
/*      Get information of memory card.                          */
/*===============================================================*/

const BACKUPINFO* BupGetInfo(Sint32 drive)
{
	return (const BACKUPINFO*)&gBupInfo[drive];
}


/*===============================================================*/
/*      ファイルのロード                                         */
/*      Load a file.                                             */
/*===============================================================*/

Sint32 BupLoad(Sint32 drive, const char* fname, void* buf)
{
	return buLoadFile(drive, fname, buf, 0);
}


/*===============================================================*/
/*      ファイルのセーブ                                         */
/*      Save a file.                                             */
/*===============================================================*/

enum {
	Sunday = 0,
	Monday,
	Tuesday,
	Wednesday,
	Thursday,
	Friday,
	Saturday
};

static const BUS_TIME gBupTime = {
	1998, 12, 31,	/* 年月日 */	/* year, month, day     */
	23, 59, 59,		/* 時分秒 */	/* hour, minute, second */
	Thursday,		/* 曜日   */	/* day of week          */
};

Sint32 BupSave(Sint32 drive, const char* fname, void* buf, Sint32 nblock)
{
	return buSaveFile(drive, fname, buf, nblock, &gBupTime,
							BUD_FLAG_VERIFY | BUD_FLAG_COPY(0));
}


/*===============================================================*/
/*      ファイルの削除                                           */
/*      Delete a file.                                           */
/*===============================================================*/

Sint32 BupDelete(Sint32 drive, const char* fname)
{
	return buDeleteFile(drive, fname);
}


/*===============================================================*/
/*      エラーコードを文字列に変換                               */
/*      Convert error code into character string.                */
/*===============================================================*/

const char* BupGetErrorString(Sint32 err)
{
	switch (err) {
		case BUD_ERR_OK:				return "OK\0";
		case BUD_ERR_BUSY:				return "BUSY\0";
		case BUD_ERR_INVALID_PARAM:		return "INVALID PARAMETER\0";
		case BUD_ERR_ILLEGAL_DISK:		return "ILLEGAL DISK\0";
		case BUD_ERR_UNKNOWN_DISK:		return "UNKNOWN DISK\0";
		case BUD_ERR_NO_DISK:			return "NO DISK\0";
		case BUD_ERR_UNFORMAT:			return "UNFORMAT\0";
		case BUD_ERR_DISK_FULL:			return "DISK FULL\0";
		case BUD_ERR_FILE_NOT_FOUND:	return "FILE NOT FOUND\0";
		case BUD_ERR_FILE_EXIST:		return "FILE EXIST\0";
		case BUD_ERR_CANNOT_OPEN:		return "CANNOT OPEN\0";
		case BUD_ERR_CANNOT_CREATE:		return "CANNOT CREATE\0";
		case BUD_ERR_EXECFILE_EXIST:	return "EXECUTABLE FILE EXIST\0";
		case BUD_ERR_ACCESS_DENIED:		return "ACCESS DENIED\0";
		case BUD_ERR_VERIFY:			return "VERIFY ERROR\0";
		default:						return "GENERIC ERROR\0";
	}
}


/*===============================================================*/
/*      オペレーションコードを文字列に変換                       */
/*      Convert operation code into character string.            */
/*===============================================================*/

const char* BupGetOperationString(Sint32 op)
{
	switch (op) {
		case BUD_OP_MOUNT:			return "CONNECTED\0";
		case BUD_OP_UNMOUNT:		return "DISCONNECTED\0";
		case BUD_OP_FORMATDISK:		return "FORMATDISK\0";
		case BUD_OP_DELETEFILE:		return "DELETEFILE\0";
		case BUD_OP_LOADFILE:		return "LOADFILE\0";
		case BUD_OP_SAVEFILE:		return "SAVEFILE\0";
		default:					return "UNKNOWN OPERATION\0";
	}
}


/*===============================================================*/
/*      コールバック関数                                         */
/*      Callback functions.                                      */
/*===============================================================*/

/*
** 初期化終了コールバック関数
** Callback function when initialization of library was finished.
*/

static void BupInitCallback(void)
{
	Sint32 i;

	/* 完了、経過コールバック関数を設定する */
	/* Register callback functions.         */
	buSetCompleteCallback(BupComplete);
	buSetProgressCallback(BupProgress);
}


/*
** 完了コールバック関数
** Callback function when operation was finished.
*/

static Sint32 BupComplete(Sint32 drive, Sint32 op, Sint32 stat, Uint32 param)
{
	BACKUPINFO* info;
	Sint32 ret;

	info = &gBupInfo[drive];

	switch (op) {
		/* メモリーカードが接続された */
		/* Memory card was connected.  */
		case BUD_OP_MOUNT:
			if (stat == BUD_ERR_OK) {
				info->Ready = TRUE;
				ret = buGetDiskInfo(drive, &info->DiskInfo);
				if (ret == BUD_ERR_OK) {
					info->IsFormat = TRUE;
				}
				/* エラー状態をクリア */
				/* Clear error status */
				info->LastError = BUD_ERR_OK;
			}
			break;
		/* メモリーカードが取り外された */
		/* Memory card was removed.     */
		case BUD_OP_UNMOUNT:
			info->Ready = FALSE;
			info->IsFormat = FALSE;
			info->ProgressCount = 0;
			info->ProgressMax = 0;
			info->Operation = 0;
			memset(&info->DiskInfo, 0, sizeof(BUS_DISKINFO));
			break;
		default:
			/* エラー状態を格納 */
			/* Store error code. */
			info->LastError = stat;

			/* 情報を更新する */
			/* Update information of memory card. */
			buGetDiskInfo(drive, &info->DiskInfo);
	}

	/* オペレーションコードをクリア */
	/* Clear operation code.        */
	info->Operation = 0;

	return BUD_CBRET_OK;
}


/*
** 経過コールバック関数
** Callback function through operation progress.
*/

static Sint32 BupProgress(Sint32 drive, Sint32 op, Sint32 count, Sint32 max)
{
	BACKUPINFO* info;

	info = &gBupInfo[drive];

	/* 経過状態、オペレーションコードを格納 */
	/* Store operation code.                */
	info->ProgressCount = count;
	info->ProgressMax = max;
	info->Operation = op;

	return BUD_CBRET_OK;
}



/******************************* end of file *******************************/
