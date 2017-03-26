/*
 *  Middleware Library
 *  Copyright (c) 1998,1999 SEGA
 *  
 *		MPEG Sofdec
 *
 *  Module  : Library Header File
 *  File    : SFD_MW.H
 *  Create  : 1998-07-25
 *  Modify  : 1999-03-12
 *  Note    :
 */

#ifndef	_SFD_MW_H_
#define	_SFD_MW_H_

/*	Version No.	*/
#define	MWD_SFD_VER	"1.30"

/***************************************************************************
 *      MACRO CONSTANT
 ***************************************************************************/

/*	Sofdec Error						*/
#define	MWD_PLY_ERR_SFD_INIT	(-301)
#define	MWD_PLY_ERR_SFD_NOTYPE	(-302)
#define	MWD_PLY_ERR_SFD_ERRFN	(-303)
#define	MWD_PLY_ERR_SFD_FINISH	(-304)
#define	MWD_PLY_ERR_SFD_CREATE	(-305)
#define	MWD_PLY_ERR_SFD_DSTRY	(-306)
#define	MWD_PLY_ERR_SFD_START	(-307)
#define	MWD_PLY_ERR_SFD_STOP	(-308)
#define	MWD_PLY_ERR_SFD_GETTIME	(-309)
#define	MWD_PLY_ERR_SFD_PAUSE	(-310)
#define	MWD_PLY_ERR_SFD_STANDBY	(-311)

/*	ファイルタイプ						*/
/*	File type							*/
#define	MWD_PLY_FTYPE_NON		(0)
#define	MWD_PLY_FTYPE_SFD		(1)
#define	MWD_PLY_FTYPE_MPV		(2)

/*	デコーダタイプ						*/
/*	Decode type							*/
#define	MWD_DECTYP_NON			(0)
#define	MWD_DECTYP_SOFDEC		(1)

/*	表示レイテンシ						*/
/*	Display latency						*/
#define	MWD_LATENCY_2V			(2)
#define	MWD_LATENCY_3V			(3)

/*	GSCハンドル最大数					*/
/*	Maximum number of GSC handle		*/
#define	MWD_GSCHN_MAX			(1)

/*	動画の表示タイプ					*/
/*	Display type of animation			*/
#define MWD_PLY_DTYPE_AUTO	(0)
#define MWD_PLY_DTYPE_FULL	(1)

/*	輝度のデフォルト値					*/
/*	Default value of brightness			*/
#if 0
#define MWD_DFL_BRIGHT		(0xea)		/* mwSfd Ver1.11 */
#define MWD_DFL_BRIGHT		(0xff)
#endif
#define MWD_DFL_BRIGHT		(0xe0)		/*	Ver.1.20	*/

/*	輝度オフセットのデフォルト値		*/
/*	Default value of brightness offset	*/
/*
#define MWD_DFL_BRIGHT_OFST	(0)
*/
#define MWD_DFL_BRIGHT_OFST	(6)			/*	Ver.1.20	*/

/*	表示スクリーンの奥行きのデフォルト値		*/
/*	Default value of z coordinay	*/
#define MWD_DFL_DLZ			(65536.0f)

/***************************************************************************
 *      Process MACRO
 ***************************************************************************/

/*	オーディオ出力バッファのサイズ			*/
/*	Calculation of audio output buffer size	*/
#define	MWD_SFD_CALC_WORK_AUDIO_OUT(nch)	(0x2020*sizeof(short)*(nch)+32)

/*	オーディオ出力バッファサイズ(デフォルト値)	*/
/*	Default size of audio output buffer			*/
#define	MWD_SFD_CALC_WORK_AUDIO_OUT0	MWD_SFD_CALC_WORK_AUDIO_OUT(2)

/*	オーディオ入力バッファサイズ			*/
/*	Default size of audio input buffer size	*/
#define	MWD_SFD_CALC_WORK_AUDIO_IN			(36*2048+32)

/*	オーディオ用バッファサイズ				*/
/*	Buffer size for the audio system		*/
#define	MWD_SFD_SIZE_WORK_AUDIO(nch)	( \
				MWD_SFD_CALC_WORK_AUDIO_OUT0 + \
				MWD_SFD_CALC_WORK_AUDIO_IN \
			)

/*	参照用フレームバッファサイズ					*/
/*	Calculation of frame buffer size for reference	*/
#define	MWD_SFD_CALC_WORK_RFB(wc, hc, wy, hy)	\
								SFD_RFB_BUF_SIZ((wc), (hc), (wy), (hy))

/*	参照用フレームバッファサイズ(デフォルト値)		*/
/*	Default value of frame buffer size for reference*/
#define	MWD_SFD_CALC_WORK_RFB0 \
				MWD_SFD_CALC_WORK_RFB(	SFD_RFB_WIDTH_C, \
										SFD_RFB_HEIGHT_C, \
										SFD_RFB_WIDTH_Y, \
										SFD_RFB_HEIGHT_Y )

/*	出力用フレームバッファサイズ					*/
/*	Calculation of frame buffer size for output		*/
#define	MWD_SFD_CALC_WORK_TAB(wy, hy, nfrm)	\
								SFD_TA_BUF_SIZ((wy), (hy), (nfrm))

/*	出力用フレームバッファサイズ(デフォルト値)		*/
/*	Default value of frame buffer size for output	*/
#define MWD_SFD_CALC_WORK_TAB0	\
				MWD_SFD_CALC_WORK_TAB(SFD_RFB_WIDTH_Y, SFD_RFB_HEIGHT_Y, 4)

#define	MWD_SFD_CALC_WORK(sx, sy, nch)	\
		MWD_SFD_CALC_WORK_AUDIO(2) +	\
		
/*	作業領域のサイズ									*/
/*	Size of working area								*/
#define	MWD_SFD_SIZE_WORK		(0x00300000)

/*
 *  表示レイテンシ
 *  頂点登録用バッファサイズから判断できる。
 *  1つをマイナスにすると2Vレーテンシモード。
 *	Display latency
 *	It is possible to judge from vertex buffer size.
 *	It become 2V latency mode when you turn one argument into 
 *	negative number.
 */
#define	MWD_PLY_LATENCY(op, om, tp, tm, pt) ( \
			((op) < 0) ? MWD_LATENCY_2V : \
			((om) < 0) ? MWD_LATENCY_2V : \
			((tp) < 0) ? MWD_LATENCY_2V : \
			((tm) < 0) ? MWD_LATENCY_2V : \
			((pt) < 0) ? MWD_LATENCY_2V : MWD_LATENCY_3V)


/***************************************************************************
 *      Data type declaration
 ***************************************************************************/

/*	Sofdecの初期化パラメータ構造体							*/
/*	Parameter structure of Sofdec initialization function	*/
typedef struct {
#if 0
	Sint32		ftype;			/*	再生するストリームの種別				*/
								/*	File type								*/
	Sint32		hnmax;			/*	最大ハンドル数							*/
								/*	Maximum number of handle				*/
	Sint32		vsync_mhz;		/*	VSYNC周波数（Hzの1,000倍)				*/
								/*	V-sync frequency(1/1000Hz)				*/
	Sint32		disp_latency;	/*	表示レイテンシ (2/3)					*/
								/*	Display latency(2 or 3)					*/
#endif
	/*	Ninjaで実際に設定した表示モードと同じ値を設定して下さい 			*/
	/*	Please set the value same as mode that you set in Ninja				*/
	Sint32		mode;			/*	画面モード								*/
								/*	Picture mode							*/
	Sint32		frame;			/*	フレームバッファのカラーモード 			*/
								/*	Color mode of the frame buffer			*/
	Sint32		count;			/*	フレームカウント数						*/
								/*	Number of frame count					*/
	Sint32		latency;		/*	表示レイテンシ (2or3)					*/
								/*	Display latency(2 or 3)					*/
	Sint32		rsv[4];			/*	予約 (全て0を設定して下さい) 			*/
								/*	Reserved(Please set 0 in all of area)	*/
} MWS_PLY_INIT_SFD;

/*	ハンドル生成パラメータ構造体			*/
/*	Parameter structure of handle creation	*/
typedef struct {
	Sint32	ftype;				/*	再生するストリームの種別 				*/
								/*	File type								*/
	Sint32	max_bps;			/*	最大のビットストリーム量　(bit/sec)		*/
								/*	Maximum number of bit per second		*/
	Sint32	max_width;			/*	再生画像サイズの最大幅					*/
								/*	Maximum width of video stream			*/
	Sint32	max_height;			/*	再生画像サイズの最大高さ				*/
								/*	Maximum height of video stream			*/
	Sint32	nfrm_pool_wk;		/*	システム領域のフレームプール数（通常3)	*/
								/*	フレーム落ちが発生した場合は、この値を	*/
								/*	増やしてください。						*/
								/*	Number of frame pools in system memory.	*/
								/*	Normaly this number is 3. If frame is 	*/
								/*	droped,you have to increase this number.*/
	Sint8	*work;				/*	ワーク領域								*/
								/*	Address of working area					*/
	Sint32	wksize;				/*	ワーク領域サイズ						*/
								/*	Size of working area					*/
	Sint32  dtype;				/*	表示タイプ								*/
								/*	Display type							*/
} MWS_PLY_CPRM_SFD;


/***************************************************************************
 *      Function Declaration
 ***************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*	システムの初期化(sbInitSystemの前に呼ぶ関数)					*/
/*	Initialization of system										*/
/*	(Call this function before 'sbInitSystem' function)				*/
void mwPlyPreInitSofdec(void);

/*	Initialization of Sofdec library	*/
void mwPlyInitSofdec(MWS_PLY_INIT_SFD *iprm);

/*	Termination of Sofdec library		*/
void mwPlyFinishSofdec(void);

/*	Create MWPLY handle for Sofdec		*/
MWPLY mwPlyCreateSofdec(MWS_PLY_CPRM_SFD *cprm);

/*	作業領域サイズの計算				*/
/*	Calculation of working area size	*/
Sint32 mwPlyCalcWorkSofdec(
	Sint32 ftype, Sint32 max_bps, Sint32 max_sx, Sint32 max_sy, Sint32 nfb);

/*	作業領域サイズの計算	*/
/*	Calculation of working area size from create parameter	*/
Sint32 mwPlyCalcWorkCprmSfd(MWS_PLY_CPRM_SFD *cprm);

/*	表示モードの設定
 *	[入力]
 *		mode		:画面モード
 *		frame		:フレームバッファのカラーモード
 *		count		:フレームカウント数
 *		latency		:表示レイテンシ (2Vレイテンシを推奨)
 *	[注意]
 *	 Ninjaで実際に設定した表示モードと同じ値を設定して下さい。
 *	 初期化時に MWS_PLY_INIT_SFD で設定した場合、この関数は必要ありません。
 *	 表示モードを変更した場合は、この関数で再設定する必要があります。
 *	[備考]
 *	 フレームカウント数について
 *	・インタレースの場合、表示更新VSYNC数 = 2*count となります。
 *	  例えば、インタレースでフレームカウント数2なら、4V表示となります。
 *	・1V表示は、24fpsなど、任意のフレームレートの動画をスムーズに表示します。
 *	・2V表示は、より多くのCPU時間をSofdecに与え、コマ落ちの危険を軽減しますが、
 *	  スムーズに再生できるフレームレートが限定されます。
 *	  (NTSC,VGA:29.97fps 30fps,  PAL:25fps)
 *	・3V以上の表示は、動画再生には推奨しません。
 *	Set display mode
 *	[Inputs]
 *		mode		:Picture mode
 *		frame		:Color mode of frame buffer
 *		count		:Number of frame count
 *		latency		:Display latency(We recommend 2V latency.)
 *	[Notes]
 *	 Please set the value same as mode that you set in Ninja.
 *	 This function is not necessary when you set MWS_PLY_INIT_SFD in 
 *	 initialize function.
 *	 You need to set if by this function again when changed display mode.
 *	[Remarks]
 *	 About number of frame count
 *	 1)V-sync number of update display is twice 'count' in case of interlace.
 *	   For example, display is 4V when the number of frame count is 2 in case
 *	   of interlace.
 *	 2)1V-display displays animation of arbitrary frame rate smoothly.
 *	   For example 24fps.
 *	 3)2V-display gives CPU time to Sofdec and reduce danger of frame drops, 
 *	   but the frame rate that can be played smoothly is limited.
 *	   (NTSC,VGA:29.97fps 30fps, PAL:25fps)
 *	 4)We do not recommend display of more than 3V in animation play.
 */
void mwPlySetDispMode(Sint32 mode, Sint32 frame, Sint32 count, Sint32 latency);

/*	高速ハールペル処理の設定	*/
/*	Set high-speed Half Pel		*/
void mwPlySetFastHalfpel(MWPLY mwply, Sint32 sw);

/*	輝度補正(-16)スイッチの設定	*/
/*	Set adjust luminosity switch (if sw==1 then y = y-16)	*/
void mwPlySetAdjustY16(MWPLY mwply, Sint32 sw);

/*	音声出力スイッチの設定			*/
/*	Set audio output switch			*/
void mwPlySetAudioSw(MWPLY mwply, Sint32 sw);

/*	表示位置の設定				*/
/*	Set location of the display	*/
void mwPlySetDispPos(MWPLY mwply, float lx, float ly);

/*	表示サイズの設定			*/
/*	Set size of the display		*/
void mwPlySetDispSize(MWPLY mwply, float sx, float sy);

/*	輝度の設定(val= 0～255)		*/
/*	Set brightness(value=0-255)	*/
void mwPlySetBright(MWPLY mwply, Sint32 val);

/*	輝度のオフセット設定(val= 0～255)	*/
/*	Set brightness offset(value=0-255)	*/
void mwPlySetBrightOfst(MWPLY mwply, Sint32 val);

/*	輝度の取得					*/
/*	Get brightness				*/
Sint32 mwPlyGetBright(MWPLY mwply);

/*	輝度オフセットの取得		*/
/*	Get brightness offset		*/
Sint32 mwPlyGetBrightOfst(MWPLY mwply);

/*	表示スクリーンの奥行き値の取得	(z:1.0->65536.0)	*/
/*	Get Z coordinary of screen	(z:1.0->65536.0)		*/
float mwPlyGetDispZ(MWPLY mwply);

/*	表示スクリーンの奥行き値の設定	(z:1.0->65536.0)	*/
/*	Get Z coordinary of screen	(z:1.0->65536.0)		*/
void mwPlySetDispZ(MWPLY mwply, float z);

/*	映像表示スイッチの設定									*/
/*	Set video output switch (if sw == 1 then output video)	*/
void mwPlySetVideoSw(MWPLY ply, Sint32 sw);

/*	映像表示スイッチの取得									*/
/*	Get video output switch									*/
Sint32 mwPlyGetVideoSw(MWPLY ply);

/*	コマ落ちしたフレーム数の取得											*/
/*	ビデオモードがインタレースモードで29.97, 30fpsのムービーの時のみ有効	*/
/*	Get number of droped frame												*/
/*	If video mode is interlace and movie is 29.97 or 30 fps,				*/
/*	you can use this function.												*/
Sint32 mwPlyGetNumDropFrm(MWPLY ply);

#ifdef __cplusplus
}
#endif

#endif	/*	_SFD_MW_H_	*/
