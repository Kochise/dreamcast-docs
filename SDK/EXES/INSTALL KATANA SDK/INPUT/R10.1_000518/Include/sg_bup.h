/*
 *  Shinobi Library
 *  Copyright (c) 1998 SEGA
 *
 *       Backup
 *
 *  Module  : Library Header File
 *  File    : sg_bup.h
 *  Create  : 1998-07-03
 *  Modify  : 1999-03-01
 *  Version : 1.44
 *  Note    :
 */

#ifndef _SG_BUP_H_
#define _SG_BUP_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*
 * C VIRTUAL TYPES DEFINITIONS
 */

#include <sg_xpt.h>


/*
 *  TYPEDEFS
 */

/******** タイムスタンプ構造体 *********************************************/
/******** Time stamp structure *********************************************/
typedef struct {
	Uint16 year;                /* 年(1998～)                              */
	                            /* year(1998-)                             */
	Uint8 month;                /* 月(1～12)                               */
	                            /* month(1-12)                             */
	Uint8 day;                  /* 日(1～31)                               */
	                            /* day(1-31)                               */
	Uint8 hour;                 /* 時(0～23)                               */
	                            /* hour(0-23)                              */
	Uint8 minute;               /* 分(0～59)                               */
	                            /* minute(0-59)                            */
	Uint8 second;               /* 秒(0～59)                               */
	                            /* second(0-59)                            */
	Uint8 dayofweek;            /* 曜日(日 = 0,月 = 1, ... 土 = 6)         */
	                            /* day of week(sun=0, mon=1, ... sat=6)    */
} BUS_TIME;


/******** ディスク情報構造体 ***********************************************/
/******** Disk information structure ***************************************/
typedef struct {
	Uint8 volume[32];           /* ボリュームデータ                        */
	                            /* Volume data                             */
	Uint16 total_blocks;        /* 全ブロック数                            */
	                            /* Number of all blocks                    */
	Uint16 total_user_blocks;   /* 全ユーザーブロック数(最大ファイル数)    */
	                            /* Number of all user blocks(Max files)    */
	Uint16 free_blocks;         /* 空きブロック数                          */
	                            /* Number of free blocks                   */
	Uint16 free_user_blocks;    /* 空きユーザーブロック数                  */
	                            /* Number of free user blocks              */
	Uint16 total_exe_blocks;    /* 全実行ファイル用ブロック数              */
	                            /* Number of blocks for executable file    */
	Uint16 free_exe_blocks;     /* 空き実行ファイル用ブロック数            */
	                            /* Number of free blocks for executable    */
	Uint16 block_size;          /* ブロックサイズ(512固定)                 */
	                            /* Size of block (Always 512 bytes)        */
	Uint16 icon_no;             /* アイコン番号(0～255)                    */
	                            /* Icon number(0-255)                      */
	BUS_TIME time;              /* フォーマットされた時刻                  */
	                            /* Time when disk was formatted            */
} BUS_DISKINFO;

/******** ファイル情報構造体 ***********************************************/
/******** File information structure ***************************************/
typedef struct {
	Uint32 filesize;            /* ファイルサイズ(バイト数)                */
	                            /* File size (in bytes)                    */
	Uint16 blocks;              /* 使用ブロック数                          */
	                            /* File size (in blocks)                   */
	Uint8 type;                 /* ファイルタイプ(通常/実行可能)           */
	                            /* File type (normal / executable)         */
	Uint8 copyflag;             /* コピーフラグ(ff=コピー不可)             */
	                            /* Copy flag(ff=cannot copy)               */
	Uint16 headerofs;           /* ヘッダオフセット                        */
	                            /* Header offset                           */
	BUS_TIME time;              /* タイムスタンプ                          */
	                            /* Time stamp                              */
} BUS_FILEINFO;

/******** バックアップファイルヘッダ ***************************************/
/******** Backup file header structure *************************************/
typedef struct {
	char vms_comment[18];       /* VMS用コメント                           */
	                            /* Comment string for VMS                  */
	char btr_comment[34];       /* BOOT ROM用コメント                      */
	                            /* Comment string for BOOT ROM             */
	Uint8 game_name[16];        /* ゲーム名                                */
	                            /* Game name (Sort key)                    */
	void* icon_palette;         /* アイコンパレットアドレス                */
	                            /* Icon palette address                    */
	void* icon_data;            /* アイコンデータアドレス                  */
	                            /* Icon pixel address                      */
	Uint16 icon_num;            /* アイコン数                              */
	                            /* Number of icons                         */
	Uint16 icon_speed;          /* アイコンアニメーションスピード          */
	                            /* Icon animation speed                    */
	void* visual_data;          /* ビジュアルデータアドレス                */
	                            /* Visual data address                     */
	Uint16 visual_type;         /* ビジュアルタイプ                        */
	                            /* Visual type                             */
	Uint16 reserved;            /* 予約                                    */
	                            /* Reserved                                */
	void* save_data;            /* アプリケーションセーブデータアドレス    */
	                            /* Application save data address           */
	Uint32 save_size;           /* アプリケーションセーブデータサイズ      */
	                            /* Application save data size (in bytes)   */
} BUS_BACKUPFILEHEADER;

/******** ボリュームアイコンファイル ***************************************/
/******** Volume icon file structure ***************************************/
typedef struct {
	char vms_comment[16];              /* VMS用コメント                    */
	                                   /* Comment string for VMS           */
	Uint8 mono_icon[128];              /* モノクロアイコンデータ           */
	                                   /* Monochrome icon data             */
	Uint16 color_icon_palette[16];     /* カラーアイコンパレット           */
	                                   /* Color icon palette               */
	Uint8 color_icon[512];             /* カラーアイコンデータ             */
	                                   /* Color icon pixel data            */
	Uint8 reserved[1024-16-128-544-4]; /* 予約                             */
	                                   /* reserved                         */
	Uint32 aligndata;                  /* 4バイトアラインのためのデータ    */
	                                   /* Data for 4-bytes align           */
} BUS_VOLUMEICONFILE;


/******** コールバック関数型 ***********************************************/
/******** Callback function types ******************************************/
typedef void (*BU_INITCALLBACK)(void);
typedef Sint32 (*BU_COMPLETECALLBACK)(Sint32 drive, Sint32 op,
												Sint32 status, Uint32 param);
typedef Sint32 (*BU_PROGRESSCALLBACK)(Sint32 drive, Sint32 op,
												Sint32 count, Sint32 max);


/*
 *  PROTOTYPES
 */


/*-------- 通常アプリで使用する関数 ---------------------------------------*/
/*-------- Functions for normal applications ------------------------------*/
Sint32 buInit(Sint32 capacity, Sint32 drives, void* work,
													BU_INITCALLBACK func);
Sint32 buExit(void);
Sint32 buSaveFile(Sint32 drive, const char* fname, const void* buf,
									Uint32 nblock, BUS_TIME* time, Uint32 flag);
Sint32 buSaveExecFile(Sint32 drive, const char* fname, const void* buf,
									Uint32 nblock, BUS_TIME* time, Uint32 flag);
Sint32 buLoadFile(Sint32 drive, const char* fname, void* buf, Uint32 nblock);

Sint32 buDeleteFile(Sint32 drive, const char* fname);
Sint32 buDeleteFileEx(Sint32 drive, const char** fname, Sint32 nfiles);

void buSetCompleteCallback(BU_COMPLETECALLBACK func);
void buSetProgressCallback(BU_PROGRESSCALLBACK func);
Sint32 buIsReady(Sint32 drive);
Sint32 buIsFormat(Sint32 drive);
Sint32 buGetDiskFree(Sint32 drive, Sint32 type);
Sint32 buGetFileInfo(Sint32 drive, const char* fname, BUS_FILEINFO* finfo);
Sint32 buGetFileSize(Sint32 drive, const char* fname);
Sint32 buIsExistFile(Sint32 drive, const char* fname);
Sint32 buStat(Sint32 drive);
Sint32 buGetLastError(Sint32 drive);
Sint32 buMountDisk(Sint32 drive, void* addr, Sint32 size);
Sint32 buUnmountDisk(Sint32 drive);
Sint32 buRewriteExecFile(Sint32 drive, const char* fname, const void* buf,
												Uint32 start, Uint32 nblock);
Sint32 buMakeBackupFileImage(void* buf, const BUS_BACKUPFILEHEADER* hdr);
Sint32 buCalcBackupFileSize(Uint32 inum, Uint32 vtype, Uint32 size);
Sint32 buAnalyzeBackupFileImage(BUS_BACKUPFILEHEADER* hdr, const void* buf);

/*-------- 主にファイルユーティリティ等で使用する関数 ---------------------*/
/*-------- Functions for file utility -------------------------------------*/
void buSetCallbackParam(Uint32 param);
Sint32 buMount(Sint32 drive);
Sint32 buRemount(Sint32 drive);
Sint32 buUnmount(Sint32 drive);
Sint32 buGetDiskInfo(Sint32 drive, BUS_DISKINFO* info);
Sint32 buFindFirstFile(Sint32 drive, char* fname);
Sint32 buFindNextFile(Sint32 drive, char* fname);
Sint32 buFindFirstFileEx(Sint32 drive, char* fname, BUS_FILEINFO* finfo);
Sint32 buFindNextFileEx(Sint32 drive, char* fname, BUS_FILEINFO* finfo);
Sint32 buFindExecFile(Sint32 drive, char* fname);
Sint32 buSetFileAttr(Sint32 drive, const char* fname, Uint16 hdrofs,
															Uint8 copyflag);
Sint32 buFormatDisk(Sint32 drive, const Uint8* volume, Sint32 icon,
											const BUS_TIME* time, Uint32 flag);
Sint32 buRenameFile(Sint32 drive, const char* from, const char* to);
Sint32 buDefragDisk(Sint32 drive, void* work);
Sint32 buLoadFileEx(Sint32 drive, const char* fname, void* buf,
												Uint32 start, Uint32 nblock);

/*-------- その他の関数 ---------------------------------------------------*/
/*-------- Other functions ------------------------------------------------*/
void buExecServer(void);
Uint32 buGetVersion(void);
void buSetPrintFunc(void (*func)(const char* str));
void buSetRetryCount(Sint32 count);
Sint32 buGetRetryCount(void);
Uint16 buCalcCRC(const void* buf, Uint32 size);



/******** ワーク容量 *******************************************************/
/******** Work *************************************************************/
#define BUD_WORK_GAP 32

#define BUM_WORK_SIZE(_cap_, _max_) \
	(((_cap_ * _max_) * 512) + (BUD_WORK_GAP * _max_))

/******** セーブ時のフラグ指定 *********************************************/
/******** Save flags *******************************************************/
#define BUD_FLAG_VERIFY       0x80000000    /* ベリファイ指定              */
                                            /* Verify on                   */
#define BUD_FLAG_COPY(n)      (n & 0xff)    /* コピーフラグ                */
                                            /* Copy flag                   */
#define BUD_FLAG_COPYDISABLE  0x000000ff    /* コピー禁止フラグを付ける    */
                                            /* Set copy prohibition flag   */

/******** 対応最大容量 *****************************************************/
/******** Capacity *********************************************************/
#define BUD_CAPACITY_128KB   (1 + 1 +  13)  /* 容量128KBのみ               */
                                            /* 128KB only                  */
#define BUD_CAPACITY_256KB   (1 + 2 +  30)  /* 容量256KBまで               */
                                            /* 128KB,256KB                 */
#define BUD_CAPACITY_512KB   (1 + 4 +  60)  /* 容量512KBまで               */
                                            /* 128KB,256KB,512KB           */
#define BUD_CAPACITY_1MB     (1 + 8 + 113)  /* 容量1MBまで                 */
                                            /* 128KB,256KB,512KB,1MB       */

/******** 対応ドライブ *****************************************************/
/******** Drives ***********************************************************/
#define BUD_USE_DRIVE_A1    (1 << 0)        /* ポートAの拡張スロット1      */
                                            /* Expansion slot 1 of port A  */
#define BUD_USE_DRIVE_A2    (1 << 1)        /* ポートAの拡張スロット2      */
                                            /* Expansion slot 2 of port A  */
#define BUD_USE_DRIVE_B1    (1 << 2)        /* ポートBの拡張スロット1      */
                                            /* Expansion slot 1 of port B  */
#define BUD_USE_DRIVE_B2    (1 << 3)        /* ポートBの拡張スロット2      */
                                            /* Expansion slot 2 of port B  */
#define BUD_USE_DRIVE_C1    (1 << 4)        /* ポートCの拡張スロット1      */
                                            /* Expansion slot 1 of port C  */
#define BUD_USE_DRIVE_C2    (1 << 5)        /* ポートCの拡張スロット2      */
                                            /* Expansion slot 2 of port C  */
#define BUD_USE_DRIVE_D1    (1 << 6)        /* ポートDの拡張スロット1      */
                                            /* Expansion slot 1 of port D  */
#define BUD_USE_DRIVE_D2    (1 << 7)        /* ポートDの拡張スロット2      */
                                            /* Expansion slot 2 of port D  */
#define BUD_USE_DRIVE_ALL   0xff            /* 全部                        */
                                            /* All slots of all ports      */

/******** ドライブ番号 *****************************************************/
/******** Drive number *****************************************************/
#define BUD_DRIVE_A1   0                    /* ポートAの拡張スロット1      */
                                            /* Expansion slot 1 of port A  */
#define BUD_DRIVE_A2   1                    /* ポートAの拡張スロット2      */
                                            /* Expansion slot 2 of port A  */
#define BUD_DRIVE_B1   2                    /* ポートBの拡張スロット1      */
                                            /* Expansion slot 1 of port B  */
#define BUD_DRIVE_B2   3                    /* ポートBの拡張スロット2      */
                                            /* Expansion slot 2 of port B  */
#define BUD_DRIVE_C1   4                    /* ポートCの拡張スロット1      */
                                            /* Expansion slot 1 of port C  */
#define BUD_DRIVE_C2   5                    /* ポートCの拡張スロット2      */
                                            /* Expansion slot 2 of port C  */
#define BUD_DRIVE_D1   6                    /* ポートDの拡張スロット1      */
                                            /* Expansion slot 1 of port D  */
#define BUD_DRIVE_D2   7                    /* ポートDの拡張スロット2      */
                                            /* Expansion slot 2 of port D  */

/******** ファイルタイプ ***************************************************/
/******* File types ********************************************************/
#define BUD_FILETYPE_NORMAL       0         /* 通常ファイル                */
                                            /* Normal file                 */
#define BUD_FILETYPE_EXECUTABLE   1         /* 実行ファイル                */
                                            /* Executable file             */

/******** ステータス *******************************************************/
/******** Status ***********************************************************/
#define BUD_STAT_READY       0x00000000     /* コマンド発行可能            */
                                            /* Can execute command         */
#define BUD_STAT_BUSY        0xffffffff     /* コマンド実行中              */
                                            /* Busy                        */

/******** コールバックオペレーションパラメータ *****************************/
/******** Callback operation parameters ************************************/
#define BUD_OP_NOP             0x00000000   /* nop                         */
#define BUD_OP_MOUNT           0x00000001   /* buRemount()/connect         */
#define BUD_OP_UNMOUNT         0x00000002   /* remove                      */
#define BUD_OP_FORMATDISK      0x00000003   /* buFormatDisk()              */
#define BUD_OP_CLOSEFILE       0x00000004   /* buCloseFile()               */
#define BUD_OP_READFILE        0x00000005   /* buReadFile()                */
#define BUD_OP_WRITEFILE       0x00000006   /* buWriteFile()               */
#define BUD_OP_DELETEFILE      0x00000007   /* buDeleteFile()              */
#define BUD_OP_RENAMEFILE      0x00000008   /* buRenameFile()              */
#define BUD_OP_DEFRAGDISK      0x00000009   /* buDefragDisk()              */
#define BUD_OP_SETFILEATTR     0x0000000a   /* buSetFileAttr()             */
#define BUD_OP_LOADFILE        0x0000000b   /* buLoadFile()                */
#define BUD_OP_SAVEFILE        0x0000000c   /* buSaveFile()                */
#define BUD_OP_SAVEEXECFILE    0x0000000d   /* buSaveExecFile()            */
#define BUD_OP_LOADFILEEX      0x0000000e   /* buLoadFileEx()              */
#define BUD_OP_READIMAGE       0x0000000f   /* buReadDiskImage()           */
#define BUD_OP_WRITEIMAGE      0x00000010   /* buWriteDiskImage()          */
#define BUD_OP_DELETEFILEEX    0x00000011   /* buDeleteFileEx()            */
#define BUD_OP_CONNECT         0x00000012   /* connect(before mount)       */
#define BUD_OP_REMOVE          0x00000013   /* remove                      */
#define BUD_OP_REWRITEEXECFILE 0x00000014   /* buRewriteExecFile()         */

/******** コールバック関数の戻り値 *****************************************/
/******** Return value of callback function ********************************/
#define BUD_CBRET_OK   0x00000000           /* 処理継続                    */
                                            /* Continue operation          */

/******** エラーコード *****************************************************/
/******** Error code *******************************************************/
#define BUD_ERR_OK              0x00000000  /* エラーなし                  */
                                            /* No error                    */
#define BUD_ERR_BUSY            0xffffffff  /* コマンド実行中              */
                                            /* Busy                        */
#define BUD_ERR_INVALID_PARAM   0xffffff00  /* 関数パラメータが異常        */
                                            /* Invalid function parameter  */
#define BUD_ERR_ILLEGAL_DISK    0xffffff81  /* 最終ブロック不良            */
                                            /* Illegal disk                */
#define BUD_ERR_UNKNOWN_DISK    0xffffff83  /* 対応していないディスク      */
                                            /* Not supported disk          */
#define BUD_ERR_NO_DISK         0xffffff01  /* ディスクが入っていない      */
                                            /* Disk is not connected       */
#define BUD_ERR_UNFORMAT        0xffffff03  /* 未フォーマット              */
                                            /* Disk is not formatted       */
#define BUD_ERR_DISK_FULL       0xffffff04  /* ディスクフル                */
                                            /* Disk full                   */
#define BUD_ERR_FILE_NOT_FOUND  0xffffff05  /* ファイルが見つからない      */
                                            /* File not found              */
#define BUD_ERR_FILE_EXIST      0xffffff06  /* 同じ名前のファイルがある    */
                                            /* File already exists         */
#define BUD_ERR_CANNOT_OPEN     0xffffff07  /* ファイルが開けない          */
                                            /* Cannot open file            */
#define BUD_ERR_CANNOT_CREATE   0xffffff08  /* 実行ファイルを作成できない  */
                                            /* Cannot create executable    */
#define BUD_ERR_EXECFILE_EXIST  0xffffff09  /* 実行ファイルが存在する      */
                                            /* Executable file exists      */
#define BUD_ERR_CANNOT_DELETE   0xffffff0a  /* ファイルを消せなかった      */
                                            /* Cannot delete file          */
#define BUD_ERR_ACCESS_DENIED   0xffffff0b  /* ファイルアクセス拒否        */
                                            /* Access is refused           */
#define BUD_ERR_VERIFY          0xffffff10  /* ベリファイエラー            */
                                            /* Verify error                */
#define BUD_ERR_WRITE_ERROR     0xffffff40  /* ライトエラー                */
                                            /* Write error                 */
#define BUD_ERR_FILE_BROKEN     0xffffff41  /* ファイルが壊れている        */
                                            /* File is broken              */
#define BUD_ERR_BUPFILE_CRC     0xffffff20  /* バックアップ形式CRCエラー   */
                                            /* CRC Error                   */
#define BUD_ERR_BUPFILE_ILLEGAL 0xffffff21  /* バックアップ形式ではない    */
                                            /* File is not backup file     */
#define BUD_ERR_GENERIC         0xffff0000  /* 未定義エラー                */
                                            /* Unknown error               */

/******** バックアップファイルのビジュアルデータタイプ *********************/
/******** Visual type of backup file ***************************************/
#define BUD_VISUALTYPE_NONE   0             /* ビジュアルデータなし        */
                                            /* No visual data              */
#define BUD_VISUALTYPE_A      1             /* タイプA                     */
                                            /* Type A                      */
#define BUD_VISUALTYPE_B      2             /* タイプB                     */
                                            /* Type B                      */
#define BUD_VISUALTYPE_C      3             /* タイプC                     */
                                            /* Type C                      */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _SG_BUP_H_ */

