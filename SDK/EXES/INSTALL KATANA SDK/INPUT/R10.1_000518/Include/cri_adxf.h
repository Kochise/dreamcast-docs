#ifndef	_CRI_ADXF_H_INCLUDED
#define	_CRI_ADXF_H_INCLUDED
/****************************************************************************/
/*																			*/
/*			$title$ ＡＤＸファイルシステム ライブラリ						*/
/*				ADXF (ADX File System) Library								*/
/*																			*/
/*			Copyright (c) 1998 CSK Research Institute						*/
/*				1998.7.3		written by S.Hosaka							*/
/*																			*/
/****************************************************************************/

/****************************************************************************/
/*      インクルードファイル												*/
/*      Include file														*/
/****************************************************************************/

/****************************************************************************/
/*		定数マクロ															*/
/*		MACRO CONSTANT														*/
/****************************************************************************/

/*	Version number of ADX File System	*/
#define	ADXF_VER				"5.55"


/*	最大パーティション数				*/
/*	Maximum number of partition			*/
#define	ADXF_PART_MAX			(256)

/*	最大ファイル数						*/
/*	Maximum number of file				*/
#define	ADXF_FILE_MAX			(65536)

/*	ADXFハンドルオブジェクトの個数		*/
/*	Maximum number of ADXF handle		*/
#define	ADXF_OBJ_MAX			(16)

/*	ハンドルの状態						*/
/*	Status of handle					*/
#define	ADXF_STAT_STOP			(1)			/*	停止中						*/
											/*	During standstill			*/
#define ADXF_STAT_READING		(2)			/*	データ読み込み中			*/
											/*	During data read-in			*/
#define ADXF_STAT_READEND		(3)			/*	データ読み込み終了			*/
											/*	Data read-in end			*/
#define ADXF_STAT_ERROR			(4)			/*	読み込みエラー発生			*/
											/*	Read-in error outbreak state*/

/*	シークタイプ						*/
/*	Type of seek						*/
#define	ADXF_SEEK_SET			(0)			/*	ファイルの先頭				*/
											/*	The beginning of file		*/
#define ADXF_SEEK_CUR			(1)			/*	現在の位置					*/
											/*	The current position		*/
#define ADXF_SEEK_END			(2)			/*	ファイルの終端				*/
											/*	The end of file				*/

/*	エラーコード						*/
/*	Error code							*/
#define	ADXF_ERR_OK				(0)			/*	正常終了					*/
											/*	Successful					*/
#define	ADXF_ERR_FATAL			(-1)		/*	外部のエラー				*/
											/*	Fatal error					*/
#define	ADXF_ERR_INTERNAL		(-2)		/*	内部のエラー				*/
											/*	Internal error				*/
#define	ADXF_ERR_PRM			(-3)		/*	不正なパラメータ			*/
											/*	Illegal parameter			*/
#define	ADXF_ERR_AFS_FILE		(-4)		/*	不正なAFSファイル			*/
											/*	Illegal AFS file			*/

/*	既定値								*/
/*	Default value						*/
#define	ADXF_DEF_SCT_SIZE		(2048)		/*	CD-ROMのセクタサイズ		*/
											/*	Sector size in CD-ROM		*/
#define	ADXF_DEF_DMA_ALIGN		(32)		/*	DMAのアライメント			*/
											/*	Alignment of DMA transfer	*/

#define	ADXF_CMD_HSTRY_MAX		(256)		/*	コマンド履歴の個数			*/
											/*	Number of command history	*/

#define	ADXF_CMD_OPEN			(1)			/*	ADXF_Open					*/
#define	ADXF_CMD_OPEN_AFS		(2)			/*	ADXF_OpenAfs				*/
#define	ADXF_CMD_CLOSE			(3)			/*	ADXF_Close					*/
#define	ADXF_CMD_READ_NW32		(4)			/*	ADXF_ReadNw32				*/
#define	ADXF_CMD_STOP			(5)			/*	ADXF_Stop					*/
#define	ADXF_CMD_SEEK			(6)			/*	ADXF_Seek					*/

#define	ADXF_CMD_NUM_MAX		(16)

/****************************************************************************/
/*		列挙定数															*/
/*		Enumarate Constants													*/
/****************************************************************************/

/****************************************************************************/
/*		処理マクロ															*/
/*		Process MACRO														*/
/****************************************************************************/

/*	パーティション情報に必要な領域の計算						*/
/*	Calculation of necessary area for partition information		*/

#define	ADXF_PTIF_CMN_SZ			(5*sizeof(long))

#define	ADXF_CALC_PTINFO_REAL_SIZE(n)	\
								(ADXF_PTIF_CMN_SZ+(((n)+1)*sizeof(short)))

#define	ADXF_CALC_PTINFO_SIZE(n)	\
					((ADXF_CALC_PTINFO_REAL_SIZE(n)+sizeof(short))/4*4)

#define	ADXF_CALC_ADD_PTINFO_SIZE(n)	\
					(ADXF_PTIF_CMN_SZ+((n)*(2*sizeof(short)+sizeof(long))))

/****************************************************************************/
/*		データ型															*/
/*      Data type declaration												*/
/****************************************************************************/

#ifndef ADXSTM_DEFINED
#define ADXSTM_DEFINED
typedef void *ADXSTM;
#endif

#ifndef SJ_DEFINED
#define SJ_DEFINED
typedef void *SJ;
#endif

/*	ADXFハンドル		*/
/*	ADXF handle			*/
#ifndef ADXF_DEFINED
#define	ADXF_DEFINED
typedef	struct _adx_fs {
	char	used;					/*	使用中か否か						*/
	char	stat;					/*	ハンドルの状態						*/
	char	sjflag;					/*	外部から設定されたSJか否か			*/
	char	rev;					/*	予約領域							*/
	ADXSTM	stm;					/*	ADXSTMハンドル						*/
	SJ		sj;						/*	ストリームジョイント				*/
	long	fad;					/*	ファイルアドレス					*/
	long	fnsct;					/*	ファイルサイズ(セクタ)				*/
	long	fsize;					/*	ファイルサイズ(バイト)				*/
	long	skpos;					/*	アクセスポインタの位置				*/
	long	rdstpos;				/*	読み込み開始位置					*/
	long	rqsct;					/*	読み込み要求データ量(セクタ)		*/
	long	rdsct;					/*	読み込んだデータ量(セクタ)			*/
	char	*buf;					/*	バッファのアドレス(バイト)			*/
	long	bsize;					/*	バッファのサイズ(バイト)			*/
} ADX_FS;
typedef	ADX_FS	*ADXF;
#endif

/*	パーティション情報		*/
/*	Partition information	*/
#ifndef ADXF_PTINFO_DEFINED
#define ADXF_PTINFO_DEFINED
typedef struct _adxf_ptinfo {
	struct _adxf_ptinfo	*next;		/*	次のパーティション(NULL:オリジナル)	*/
	long				size;		/*	パーティション情報領域サイズ		*/
	long				fad;		/*	パーティションの先頭FAD				*/
	long				nfile;		/*	パーティション内のファイル数		*/
	unsigned short		nentry;		/*	パーティション内の登録ファイル数	*/
	char				type;		/*	オリジナルか追記かのフラグ			*/
	char				rev;		/*	予約領域							*/
	long				top;		/*	ファイル情報の先頭					*/
} ADXF_PTINFO;
#endif

/*	追記ファイルの情報				*/
/*	Information of postscript file	*/
#ifndef ADXF_ADD_DEFINED
#define ADXF_ADD_DEFINED
typedef struct _adxf_add_info {
	unsigned short	flid;			/*	ファイルID							*/
	unsigned short	fnsct;			/*	ファイルサイズ						*/
	long			ofst;			/*	オフセット							*/
} ADXF_ADD_INFO;
#endif

#ifndef ADXF_CMD_HSTRY_DEFINED
#define ADXF_CMD_HSTRY_DEFINED
typedef struct _adxf_cmd_hstry {
	unsigned char	cmdid;			/*	コマンド(関数)ID					*/
	unsigned char	fg;				/*	関数の入り口か出口かを示すフラグ	*/
	unsigned short	ncall;			/*	コマンドの呼び出し回数				*/
	long	prm[3];					/*	コマンドパラメータ					*/
} ADXF_CMD_HSTRY;
#endif

/****************************************************************************/
/*		変数宣言															*/
/*		Variable Declaration												*/
/****************************************************************************/

/****************************************************************************/
/*		関数の宣言															*/
/*      Function Declaration												*/
/****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*==========================================================================
		ライブラリの初期化と終了処理
 		Initialize and Finalize of Library
  ==========================================================================*/

/*  ライブラリの初期化
 * [書　式] void ADXF_Init( void );
 * [入　力] なし
 * [出　力] なし
 * [関数値] なし
 * [機　能] ライブラリを初期化する。
 *  Initialization of library
 * [Inputs  ] None
 * [Outputs ] None
 * [Return  ] None
 * [Function] Initializes library.
 */
void ADXF_Init(void);

/* ライブラリの終了処理
 * [書　式] void ADXF_Finish(void);
 * [入　力] なし
 * [出　力] なし
 * [関数値] なし
 * [機　能] ライブラリの終了処理をする。
 *  Termination of library
 * [Inputs  ] None
 * [Outputs ] None
 * [Return  ] None
 * [Function] Finalizes library.
 */
void ADXF_Finish(void);

/*  パーティションのロード
 * [書　式] long ADXF_LoadPartition(long ptid, char *fname, 
 *													void *ptinfo, long nfile);
 * [入　力] ptid	:パーティションID
 *			fname	:AFSファイルの名前
 *			ptinfo	:パーティション情報読み込み領域
 *			nfile	:ファイル数
 * [出　力] なし
 * [関数値] エラーコード
 * [機　能] AFSファイル名を読み込んで、パーティションIDに設定する。
 *  Load of the partition
 * [Inputs  ] ptid   :Partition ID
 *			  fname  :Name of AFS file
 *            ptinfo :Area of partition information
 *            nfile  :The number of files
 * [Outputs ] None
 * [Return  ] Error code
 * [Function] Loads AFS file and sets partition ID.
 */
long ADXF_LoadPartition(long ptid, char *fname, void *ptinfo, long nfile);

/*  パーティションの追加
 * [書　式] long ADXF_AddPartition(long ptid, char *fname, 
 *													void *ptinfo, long nfile);
 * [入　力] ptid	:パーティションID
 *			fname	:AFSファイルの名前
 *			ptinfo	:パーティション情報読み込み領域
 *			nfile	:ファイル数
 * [出　力] なし
 * [関数値] エラーコード
 * [機　能] 指定されたパーティションIDにAFSファイルを追加する。
 *  Additon of the partition
 * [Inputs  ] ptid   :Partition ID
 *			  fname  :Name of AFS file
 *            ptinfo :Area of partition information
 *            nfile  :The number of files
 * [Outputs ] None
 * [Return  ] Error code
 * [Function] Adds AFS file to the partition ID.
 */
long ADXF_AddPartition(long ptid, char *fname, void *ptinfo, long nfile);

/*  パーティション情報サイズの取得
 * [書　式] long ADXF_GetPtinfoSize(long ptid);
 * [入　力] ptid	:パーティションID
 * [出　力] なし
 * [関数値] パーティション情報サイズ(単位：バイト)
 * [機　能] パーティション情報領域のサイズを取得する。
 *  Get size of partition information
 * [Inputs  ] ptid   :Partition ID
 * [Outputs ] None
 * [Return  ] Size of the partition information(byte)
 * [Function] Gets size of the partition information.
 */
long ADXF_GetPtinfoSize(long ptid);

/*==========================================================================
		ファイルの読み込み
		Read file
  ==========================================================================*/

/*	ファイルのオープン(ISO9660のファイル)
 * [書　式] ADXF ADXF_Open(char *fname, void *atr);
 * [入　力] fname	: ファイル名
 *			atr		: ファイルの属性
 * [出　力] なし
 * [関数値] ADXFハンドル、エラーの場合NULL
 * [機　能] 指定のファイルをオープンし、ADXFハンドルを返す。
 *  Open file(ISO9660 format)
 * [Inputs  ] fname  : File name
 *			  atr    : File attribute
 * [Outputs ] None
 * [Return  ] ADXF handle
 *			  (If the operation was unsuccessful, this function returns NULL.)
 * [Function] Opens a file of ISO9660 format.
 */
ADXF ADXF_Open(char *fname, void *atr);

/*	ファイルのオープン(AFSフォーマット)
 * [書　式] ADXF ADXF_OpenAfs(long ptid, long flid);
 * [入　力] ptid	: パーティションID
 *			flid	: ファイルID
 * [出　力] なし
 * [関数値] ADXFハンドル、エラーの場合NULL
 * [機　能] パーティションIDとファイルIDで指定されたAFSファイルをオープンし、
 *			ADXFハンドルを返す。
 *  Open file(AFS format)
 * [Inputs  ] ptid   : Partition ID
 *			  flid   : File ID
 * [Outputs ] None
 * [Return  ] ADXF handle
 *			  (If the operation was unsuccessful, this function returns NULL.)
 * [Function] Opens a file of AFS format.
 */
ADXF ADXF_OpenAfs(long ptid, long flid);

/* ファイルのクローズ
 * [書　式] void ADXF_Close(ADXF adxf);
 * [入　力] adxf	: ADXFハンドル
 * [出　力] なし
 * [関数値] なし
 * [機　能] 指定されたADXFハンドルのファイルをクローズする。
 *  Close file
 * [Inputs  ] adxf   : ADXF handle
 * [Outputs ] None
 * [Return  ] None
 * [Function] Closes a file of specific ADXF handle.
 */
void ADXF_Close(ADXF adxf);

/* 全てのファイルクローズ
 * [書　式] void ADXF_CloseAll(void);
 * [入　力] adxf	: ADXFハンドル
 * [出　力] なし
 * [関数値] なし
 * [機　能] ADXFハンドルのファイルを全てクローズする。
 *  Close file
 * [Inputs  ] adxf   : ADXF handle
 * [Outputs ] None
 * [Return  ] None
 * [Function] Closes all file of ADXF handle.
 */
void ADXF_CloseAll(void);

/*  SJへのデータ読み込み開始
 * [書　式] void ADXF_ReadSj32(ADXF adxf, long nsct, SJ sj);
 * [入　力] adxf	: ADXFハンドル
 *			nsct	: 読み込みデータの量(単位：セクタ)
 *			SJ		: ストリームジョイント
 * [出　力] なし
 * [関数値] 読み込みデータ量(単位：セクタ)
 * [機　能] ストリームジョイントにデータ読み込みのリクエストを発行する。
 *			ストリームジョイントのバッファサイズは、セクタの整数倍でなければ
 *			ならない。
 *			ストリームジョイントからユーザがデータを読み出すと、自動的にストリー *			ムジョイントにデータが読み込まれる。
 *			リクエストしたアクセス動作が完了すると、アクセスポインタは
 *			nsctセクタ進む。
 *  Read-in start to Stream Joint
 * [Inputs  ] adxf   : ADXF handle
 *			  nsct   : Number of read-in sectors to request
 *			  SJ     : Stream Joint
 * [Outputs ] None
 * [Return  ] Number of sectors to read
 * [Function] Requests data read-in to Stream Joint.
 *			  Buffer size of Stream Joint must be multiples of integer.
 *			  If you read data from Stream Joint, data are read into Stream 
 *			  Joint automatically.
 *			  The access pointer moves 'nsct' sector minute when the request 
 *			  was completed.
 */
long ADXF_ReadSj32(ADXF adxf, long nsct, SJ sj);

/* データの読み込み開始
 * [書　式] void ADXF_ReadNw32(ADXF adxf, long nsct, void *buf);
 * [入　力] adxf	: ADXFハンドル
 *			nsct	: 読み込みデータの量(単位：セクタ)
 *			buf		: 読み込み領域
 * [出　力] なし
 * [関数値] 読み込みデータ量(単位：セクタ)
 * [機　能] データ読み込みのリクエストを発行する。
 *			リクエストしたアクセス動作が完了すると、アクセスポインタは
 *			nsctセクタ進む。
 *  Read-in start
 * [Inputs  ] adxf   : ADXF handle
 *			  nsct   : Number of read-in sectors to request
 *			  buf    : Pointer to buffer into which the data is read
 * [Outputs ] None
 * [Return  ] Number of sectors to read
 * [Function] Requests data read-in to Stream Joint.
 *			  The access pointer moves 'nsct' sector minute when the request 
 *			  was completed.
 */
long ADXF_ReadNw32(ADXF adxf, long nsct, void *buf);

/* データの読み込み中止
 * [書　式] long ADXF_Stop(ADXF adxf);
 * [入　力] adxf	: ADXFハンドル
 * [出　力] なし
 * [関数値] 中止した時点でのアクセスポインタの位置
 * [機　能] データの読み込みを中止する。
 *  Read-in stop
 * [Inputs  ] adxf   : ADXF handle
 * [Outputs ] None
 * [Return  ] The location of access pointer when you stop to read
 * [Function] Stops to read data.
 */
long ADXF_Stop(ADXF adxf);

/* サーバ関数
 * [書　式] void ADXF_ExecServer(void);
 * [入　力] なし
 * [出　力] なし
 * [関数値] なし
 * [機　能] 内部状態を更新する。
 *  Server function
 * [Inputs  ] None
 * [Outputs ] None
 * [Return  ] None
 * [Function] Update the inside status of library.
 */
void ADXF_ExecServer(void);

/*==========================================================================
		アクセスポインタの制御
		Control access pointer
  ==========================================================================*/

/*  アクセスポインタの移動
 * [書　式] long ADXF_Seek(ADXF adxf, long pos, long type);
 * [入　力] adxf	: ADXFハンドル
 *			pos		: アクセスポインタの移動量(単位：セクタ)
 *			type	: 移動基準(シークタイプ：ADXF_SEEK_～)
 * [出　力] なし
 * [関数値] アクセスポインタの位置、負の値はエラーコード
 * [機　能] アクセスポインタをtypeからposセクタ離れた位置に移動させる。
 *  Move access pointer
 * [Inputs  ] adxf   : ADXF handle
 *			  pos    : Offset relative to 'type'
 *			  type   : Specified the origin for the offset
 * [Outputs ] None
 * [Return  ] Location containing new seek pointer
 * [Function] Changes the seek pointer to a new location relative to the 
 *			  beginning of the file, to the end of the file, or to the current 
 *			  seek pointer.
 */
long ADXF_Seek(ADXF adxf, long pos, long type);

/*  アクセスポインタの取得
 * [書　式] long ADXF_Tell(ADXF adxf);
 * [入　力] adxf	: ADXFハンドル
 * [出　力] なし
 * [関数値] アクセスポインタの位置
 * [機　能] アクセスポインタの位置を取得する。
 *  Get the access pointer
 * [Inputs  ] adxf   : ADXF handle
 * [Outputs ] None
 * [Return  ] Access pointer
 * [Function] Gets the access pointer.
 */
long ADXF_Tell(ADXF adxf);

/*==========================================================================
		情報の取得
		Get information
  ==========================================================================*/

/*  ファイルサイズの取得
 * [書　式] long ADXF_GetFsizeSct(ADXF adxf);
 * [入　力] adxf	: ADXFハンドル
 * [出　力] なし
 * [関数値] ファイルサイズ(単位：セクタ)
 * [機　能] 指定されたファイルのサイズをセクタ単位で取得する。
 *  Get file size
 * [Inputs  ] adxf   : ADXF handle
 * [Outputs ] None
 * [Return  ] File size(sector)
 * [Function] Obtains the size of the specified file.
 */
long ADXF_GetFsizeSct(ADXF adxf);

/*  ファイルサイズの取得
 * [書　式] long ADXF_GetFsizeByte(ADXF adxf);
 * [入　力] adxf	: ADXFハンドル
 * [出　力] なし
 * [関数値] ファイルサイズ(単位：バイト)
 * [機　能] 指定されたファイルのサイズをバイト単位で取得する。
 *  Get file size
 * [Inputs  ] adxf   : ADXF handle
 * [Outputs ] None
 * [Return  ] File size(byte)
 * [Function] Obtains the size of the specified file.
 */
long ADXF_GetFsizeByte(ADXF adxf);

/*  読み込み要求情報の取得
 * [書　式] long ADXF_GetNumReqSct(ADXF adxf, long *seekpos);
 * [入　力] adxf	: ADXFハンドル
 * [出　力] seekpos	: 読み込み位置
 * [関数値] 要求した読み込みデータ量(単位：セクタ)
 * [機　能] 要求した読み込み位置とデータ量を取得する。
 *  Get request information
 * [Inputs  ] adxf   : ADXF handle
 * [Outputs ] seekpos: location of start to read
 * [Return  ] Request data size(sector)
 * [Function] Obtains read-in start position and the read-in size that 
 *			  demanded.
 */
long ADXF_GetNumReqSct(ADXF adxf, long *seekpos);

/*  実際に読み込んだセクタ数の取得
 * [書　式] long ADXF_GetNumReadSct(ADXF adxf);
 * [入　力] adxf	: ADXFハンドル
 * [出　力] なし
 * [関数値] 読み込んだデータ量(単位：セクタ)
 * [機　能] 実際に読み込んだデータ量を取得する。
 *  Get the number of sectors read
 * [Inputs  ] adxf   : ADXF handle
 * [Outputs ] None
 * [Return  ] Size of read data(sector)
 * [Function] Obtains the size of data that read actually.
 */
long ADXF_GetNumReadSct(ADXF adxf);

/*  ハンドルの状態の取得
 * [書　式] long ADXF_GetStat(ADXF adxf);
 * [入　力] adxf	: ADXFハンドル
 * [出　力] なし
 * [関数値] ADXFハンドルの内部状態(状態：ADXF_STAT_～)
 * [機　能] ADXFハンドルの内部状態を取得する。
 *  Get status of handle
 * [Inputs  ] adxf   : ADXF handle
 * [Outputs ] None
 * [Return  ] Status of handle
 * [Function] Gets status of handle.
 */
long ADXF_GetStat(ADXF adxf);

/*  FADとファイルサイズの取得
 * [書　式] long ADXF_GetAfsRange(long ptid, long flid, 
 *													long *fad, long *fnsct);
 * [入　力] ptid	: パーティションID
 *			flid	: ファイルID
 * [出　力] fad		: ファイルアドレス
 *			nsct	: ファイルサイズ(単位:セクタ)
 * [関数値] エラーコード
 * [機　能] パーティション内のファイルのファイルアドレスとサイズを取得する。
 *  Get FAD and file size
 * [Inputs  ] ptid   : Partition ID
 *			  flid   : File ID
 * [Outputs ] fad    : File address
 *			  nsct   : File size(sector)
 * [Return  ] Error code
 * [Function] Obtains address and size of file in the partition.
 */
long ADXF_GetFileRange(long ptid, long flid, long *fad, long *fnsct);


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif	/* _CRI_ADXF_H_INCLUDED */
