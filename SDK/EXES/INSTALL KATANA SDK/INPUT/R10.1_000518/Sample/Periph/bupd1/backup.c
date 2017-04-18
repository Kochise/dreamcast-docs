/********************************************************************
 *  Shinobi Library Sample
 *  Copyright (c) 1998 SEGA
 *
 *  Library : Backup Library
 *  Module  : Library Sample(Dynamic memory allocation version)
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
/*      スタティック関数のプロトタイプ宣言                       */
/*      Prototypes of static functions.                          */
/*===============================================================*/

static Sint32 BupComplete(Sint32 drive, Sint32 op, Sint32 stat, Uint32 param);
static Sint32 BupProgress(Sint32 drive, Sint32 op, Sint32 count, Sint32 max);
static void BupInitCallback(void);
static void ClearInfo(Sint32 drive);


/*===============================================================*/
/*      バックアップライブラリ初期化                             */
/*      動的メモリ確保をするため、ワークアドレスにはNULLを指定   */
/*      Initialize backup library.                               */
/*      Please set NULL to work address to allocate memory       */
/*      dynamically.                                             */
/*===============================================================*/

void BupInit(void)
{
	memset(gBupInfo, 0, sizeof(gBupInfo));
	buInit(MAX_CAPS, USE_DRIVES, NULL, BupInitCallback);
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
/*      ワークの確保とマウント                                   */
/*      この処理が終了し、マウントコールバックが返ってから       */
/*      今までどおりファイルアクセスが可能になります             */
/*      Allocate memory and mount drive.                         */
/*      File access becomes possible as before after this        */
/*      operation is finished and mount callback occured.         */
/*===============================================================*/

void BupMount(Sint32 drive)
{
	BACKUPINFO* info;

	info = &gBupInfo[drive];

	if (info->Work) return;		/* すでにマウント済み */

	info->Work = syMalloc(info->WorkSize);

	buMountDisk(drive, info->Work, info->WorkSize);
}

/*===============================================================*/
/*      アンマウント                                             */
/*        これ以降そのドライブにはアクセスできません             */
/*        再びアクセスしたい場合は、もう一度ワークの確保と       */
/*        マウントを行ってください                               */
/*      buUnmount()使用上の注意(※重要)                          */
/*       ・BUD_OP_UNMOUNTコールバックは発生しません              */
/*       ・buUnmount()が成功しない場合、そのドライブはアクセス中 */
/*         です。ワークを開放してはいけません。                  */
/*       ・buUnmount()が成功した場合、直後にワークを開放しても   */
/*         問題ありません                                        */
/*      Unmount                                                  */
/*        You cannot access the drive after this.                */
/*        Please allocate memory and mount when want to access   */
/*        again.                                                 */
/*      ATTENTION ON USE buUnmount():*** Important ***           */
/*        .When buUnmount() was not successful, the drive is in  */
/*         access, and must not open up work buffer              */
/*        .When buUnmount() was successful, you can open up work */
/*         buffer immmediately after.                            */
/*===============================================================*/

void BupUnmount(Sint32 drive)
{
	BACKUPINFO* info;
	Sint32 err;

	info = &gBupInfo[drive];

	if (info->Work == NULL) return;		/* マウントされていない  */
										/* Drive is not mounted. */

	/* アンマウント関数が成功しない場合、そのドライブは       */
	/* アクセス中である。その場合、ワークを開放してはならない */
	/* When buUnmount() was not successful, the drive is in   */
	/* access, and must not open up work buffer               */

	if (buUnmount(drive) == BUD_ERR_OK) {
		syFree(info->Work);
		ClearInfo(drive);
	}
}

static void ClearInfo(Sint32 drive)
{
	BACKUPINFO* info;

	info = &gBupInfo[drive];
	info->ProgressCount = 0;
	info->ProgressMax = 0;
	info->Operation = 0;
	info->Ready = FALSE;
	info->IsFormat = FALSE;
	info->Work = NULL;
	memset(&info->DiskInfo, 0, sizeof(BUS_DISKINFO));
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
		case BUD_OP_CONNECT:		return "CONNECTED\0";
		case BUD_OP_MOUNT:			return "MOUNTED\0";
		case BUD_OP_UNMOUNT:		return "UNMOUNTED\0";
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
		case BUD_OP_CONNECT:
			info->Connect = TRUE;
			info->WorkSize = BUM_WORK_SIZE(stat, 1);
			info->Capacity = stat;
			break;
		/* バックアップRAMがマウントされた */
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
			if (info->Work) syFree(info->Work);
			ClearInfo(drive);
			info->Connect = FALSE;
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
