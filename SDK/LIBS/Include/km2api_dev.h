/*++

  COPYRIGHT        (C) NEC        Corporation 1997 - 1999

  All rights reserved by NEC Corporation. This program must be
  used solely for the purpose for which it was furnished by NEC
  Corporation. No part of this program may be reproduced or
  disclosed to others, in any form, without the prior written
  permission of NEC Corporation.
  Use of copyright notice does not evidence publication of this
  program.

  Author     :		T.Hirata(NEC Software,Ltd.)
  Module Name:		km2api_dev.h

  Abstract:
	KAMUI = Kamui is abstruction model that is ultimate interface for PowerVR.
	'km2api_dev.h' define Device and Display Control API.

  Environment:
	ANSI C Compiler.

  Notes:
	define Kamui's Device and Display control api proto-types.

  Revision History:

--*/

#if !defined(__kamui2_device_api_h__)
#define __kamui2_device_api_h__

/*++
kmInitDevice

proto type:

	KMSTATUS
	kmInitDevice (
				KMDEVICE nDevice
			);

Description:
	ハードウェアの初期化を行います。

Arguments:
	IN	nDevice
		使用するハードウェアを指定します。

			KM_DREAMCAST	... Dreamcast(tm) を使う。
			KM_NAOMI    	... NA@MI(tm) をつかう。


Result:

	KMSTATUS_SUCCESS				デバイス初期化成功
	KMSTATUS_INVALID_VIDEOMODE		不正なビデオモードを指定した。
	KMSTATUS_HARDWARE_NOT_PRESENTED	ハードウェアが使用できない。

--*/
KMSTATUS KMAPI
kmInitDevice (
		IN	KMDEVICE nDevice
	);


/*++
kmUnloadDevice

proto type:

	KMSTATUS
	kmUnloadDevice (
				KMVOID
			);

Description:
	ハードウェアのアンロードを行います。

Arguments:

Result:
	KMSTATUS_SUCCESS				成功

--*/
KMSTATUS KMAPI
kmUnloadDevice(
		KMVOID
	);

/*++
kmSetDisplayMode

proto type:

	KMSTATUS
	kmSetDisplayMode(
			IN	KMDISPLAYMODE	nDisplayMode,
			IN	KMBPPMODE		nBpp,
			IN	KMBOOLEAN		fDither,
			IN	KMBOOLEAN		fAntiAlias
		);

Description:
	Frame Bufferの表示モードを設定します。

Arguments:
	IN	nDisplayMode
	ディスプレイモードを指定します。
		KM_DSPMODE_VGA				VGA(640x480) 60Hz
		KM_DSPMODE_NTSCNI320x240	320x240 ノンインタレース60Hz
		KM_DSPMODE_NTSCI320x240		320x240 インタレース 30Hz
		KM_DSPMODE_NTSCNI320x480	320x240 疑似ノンインターレース 60Hz
		KM_DSPMODE_NTSCNI320x480FF	320x240 疑似ノンインターレース 60Hz フリッカーフリー
		KM_DSPMODE_NTSCI320x480		320x240 インタレース 30Hz
		KM_DSPMODE_NTSCNI640x240	640x240 ノンインタレース60Hz
		KM_DSPMODE_NTSCI640x240		640x240 インタレース30Hz
		KM_DSPMODE_NTSCNI640x480	640x480 疑似ノンインターレース 60Hz
		KM_DSPMODE_NTSCNI640x480FF	640x480 疑似ノンインターレース 60Hz フリッカーフリー
		KM_DSPMODE_NTSCI640x480		640x480 インタレース 30Hz

		KM_DSPMODE_PALNI320x240		320x240 ノンインタレース50Hz
		KM_DSPMODE_PALI320x240		320x240 インタレース25Hz
		KM_DSPMODE_PALNI320x480		320x480 疑似ノンインターレース 50Hz
		KM_DSPMODE_PALNI320x480FF	320x480 疑似ノンインターレース 50Hz フリッカーフリー
		KM_DSPMODE_PALI320x480		320x480 インタレース25Hz
		KM_DSPMODE_PALNI640x240		640x240 ノンインタレース50Hz
		KM_DSPMODE_PALI640x240	 	640x240 インタレース25Hz
		KM_DSPMODE_PALNI640x480		640x480 疑似ノンインターレース 50Hz
		KM_DSPMODE_PALNI640x480FF	640x480 疑似ノンインターレース 50Hz フリッカーフリー
		KM_DSPMODE_PALI640x480		640x480 インタレース25Hz

	IN	nBpp
	FrameBufferのカラーモードを指定します。
	以下の定義済み定数を使用することができます。
		KM_DSPBPP_RGB565		RGB565 
		KM_DSPBPP_RGB555		RGB555
		KM_DSPBPP_ARGB1555		ARGB1555
		KM_DSPBPP_RGB888		RGB888
		KM_DSPBPP_ARGB8888		ARGB8888

	IN	bDither
		PowerVR が レンダリング結果を 16bitの Frame Buffer に書き込む際の
		Dither の有無を決定します。レンダリング先の Frame Buffer が 
		RGB888、ARGB8888 である場合、このフラグは無視されます。

			TRUE	Dither を使用する。
			FALSE	Dither を使用しない。

	IN	bAntiAlias
		アンチエリアシングフィルタの使用可否を決定します。
		アンチエイリアシングフィルタを有効にした場合動作速度が
		低下する場合があります。

			TRUE 	Anti Aliasing Filter を使用する。
			FALSE	Anti Aliasing Filter を使用しない。


Result:
	KMSTATUS_SUCCESS				成功
	KMSTATUS_INVALID_DISPLAY_MODE	不正なディスプレイモードが指定された。
									初期化時に指定されたディスプレイモードと
									矛盾するディスプレイモードが指定された。


--*/

KMSTATUS KMAPI
kmSetDisplayMode(
		IN	KMDISPLAYMODE	nDisplayMode,
		IN	KMBPPMODE		nBpp,
		IN	KMBOOLEAN		fDither,
		IN	KMBOOLEAN		fAntiAlias
	);

/*++
kmChangeDisplayFilterMode

proto type:

	KMSTATUS 
	kmChangeDisplayFilterMode(	
			KMBOOLEAN fDither,
			KMBOOLEAN fAntiAlias
		);

Description:
	kmSetDisplayMode で設定したディザやアンチエリアシングフィルタの Enable / Disable を
	後で変更する為に使用します。

Arguments:
	IN	bDither
		PowerVR が レンダリング結果を 16bitの Frame Buffer に書き込む際の
		Dither の有無を決定します。レンダリング先の Frame Buffer が 
		RGB888、ARGB8888 である場合、このフラグは無視されます。

			TRUE	Dither を使用する。
			FALSE	Dither を使用しない。

	IN	bAntiAlias
		アンチエリアシングフィルタの使用可否を決定します。
		アンチエイリアシングフィルタを有効にした場合動作速度が
		低下する場合があります。

			TRUE 	Anti Aliasing Filter を使用する。
			FALSE	Anti Aliasing Filter を使用しない。

Result:
	KMSTATUS_SUCCESS				成功
	KMSTATUS_INVALID_DISPLAY_MODE	不正なディスプレイモードが指定された。
									初期化時に指定されたディスプレイモードと
									矛盾するディスプレイモードが指定された。

--*/

KMSTATUS  KMAPI
kmChangeDisplayFilterMode(	
		IN	KMBOOLEAN fDither,
		IN	KMBOOLEAN fAntiAlias
	);

/*++
kmChangeDisplayDitherMode

proto type:

	KMSTATUS 
	kmChangeDisplayDitherMode( 
		IN	KMBOOLEAN bEnable 
		);

Description:
	kmSetDisplayMode で設定したディザモードを変更する為に使用します。

Arguments:
	IN	bEnable
		PowerVR が レンダリング結果を 16bitの Frame Buffer に書き込む際の
		Dither の有無を決定します。レンダリング先の Frame Buffer が 
		RGB888、ARGB8888 である場合、このフラグは無視されます。

			TRUE	Dither を使用する。
			FALSE	Dither を使用しない。


Result:
	KMSTATUS_SUCCESS				成功

--*/
KMSTATUS KMAPI
kmChangeDisplayDitherMode( 
		IN	KMBOOLEAN bEnable 
	);


/*++
kmChangeDisplayAntiAliasMode

proto type:

	KMSTATUS 
	kmChangeDisplayAntiAliasMode(
			IN	KMBOOLEAN bEnable
		);

Description:
	kmSetDisplayMode で設定したアンチエリアシングフィルタの Enable / Disable を
	変更する為に使用します。

Arguments:
	IN	bEnable
		アンチエリアシングフィルタの使用可否を決定します。
		アンチエイリアシングフィルタを有効にした場合動作速度が
		低下する場合があります。

			TRUE 	Anti Aliasing Filter を使用する。
			FALSE	Anti Aliasing Filter を使用しない。

Result:
	KMSTATUS_SUCCESS				成功

--*/
KMSTATUS KMAPI
kmChangeDisplayAntiAliasMode( 
		IN	KMBOOLEAN bEnable 
	);

/*++
kmGetDisplayFilterMode

proto type:

	KMSTATUS 
	kmGetDisplayFilterMode( 
			OUT	PKMBOOLEAN pbEnabledDither, 
			OUT	PKMBOOLEAN pbEnableAntiAlias
		);

Description:
	kmSetDisplayMode で設定したディザモードを変更する為に使用します。

Arguments:
	OUT	pbEnabledDither
		PowerVR が レンダリング結果を 16bitの Frame Buffer に書き込む際の
		Dither の有無を取得します。レンダリング先の Frame Buffer が 
		RGB888、ARGB8888 である場合、このフラグは無視されています。
			TRUE	Dither を使用する。
			FALSE	Dither を使用しない。

	OUT	pbEnableAntiAlias
		アンチエリアシングフィルタの使用可否を取得します。
			TRUE 	Anti Aliasing Filter を使用する。
			FALSE	Anti Aliasing Filter を使用しない。

Result:
	KMSTATUS_SUCCESS				成功

--*/

KMSTATUS KMAPI
kmGetDisplayFilterMode( 
		OUT	PKMBOOLEAN pbEnabledDither, 
		OUT	PKMBOOLEAN pbEnableAntiAlias
	);


/*++
kmGetDisplayDitherMode

proto type:

	KMSTATUS 
	kmGetDisplayDitherMode( 
		OUT	PKMBOOLEAN pbEnable
		);

Description:
	kmSetDisplayMode で設定したディザモードを変更する為に使用します。

Arguments:
	OUT	pbEnable 
		PowerVR が レンダリング結果を 16bitの Frame Buffer に書き込む際の
		Dither の有無を取得します。レンダリング先の Frame Buffer が 
		RGB888、ARGB8888 である場合、このフラグは無視されています。

			TRUE	Dither を使用する。
			FALSE	Dither を使用しない。

Result:
	KMSTATUS_SUCCESS				成功

--*/
KMSTATUS KMAPI
kmGetDisplayDitherMode( 
		OUT	PKMBOOLEAN pbEnable 
	);


/*++
kmChangeDisplayAntiAliasMode

proto type:

	KMSTATUS 
	kmGetDisplayAntiAliasMode(
			OUT	PKMBOOLEAN pbEnable 
		);

Description:
	kmSetDisplayMode 等で設定したアンチエリアシングフィルタの Enable / Disable を
	取得する為に使用します。

Arguments:
	OUT	pbEnabled
		アンチエリアシングフィルタの使用可否を取得します。

			TRUE 	Anti Aliasing Filter を使用する。
			FALSE	Anti Aliasing Filter を使用しない。

Result:
	KMSTATUS_SUCCESS				成功

--*/
KMSTATUS KMAPI
kmGetDisplayAntiAliasMode( 
		OUT	PKMBOOLEAN pbEnable
	);

/*++
kmBlankScreen

proto type:

	KMSTATUS
	kmBlankScreen(	KMBOOLEAN bBlanking	);

Description:
	フレームバッファの画面表示を中止し、ブランキングにする。
	＜< 1回の V-Sync Callback 中で 1回の呼び出しのみ対応する。>＞

Arguments:
	IN	bBlanking	画面をブランキングするかどうかの指定。
			TRUE 	ブランキング開始
            FALSE	ブランキング解除

Result:
	KMSTATUS_SUCCESS		成功

--*/
KMSTATUS KMAPI
kmBlankScreen(
			IN	KMBOOLEAN bBlanking
		);

/*++
kmAdjustDisplayCenter

proto type:

	KMSTATUS
	kmAdjustDisplayCenter( 	KMINT32 nXAdjust, 
							KMINT32 nYAdjust 
						);

Description:
	画面上におけるFrame buffer の表示位置の調整を行います。

Arguments:
	IN	nXAdjust	横方向の画面描画位置を調整する値
	IN	nYAdjust	縦方向の画面描画位置を調整する値

Result:
	KMSTATUS_SUCCESS		成功
	KMSTATUS_OUT_OF_RANGE	有効範囲外の値を指定した。

--*/
KMSTATUS KMAPI
kmAdjustDisplayCenter( 
			IN	KMINT32 nXAdjust, 
			IN	KMINT32 nYAdjust 
		);


/*++
kmSetHSyncLine

proto type:
	KMSTATUS
	kmSetHSyncLine(
			KMINT32 nInterruptLine
		);

Description:
	表示何ライン目で割り込みを起こすかを指定します。 

Arguments:
	IN	nInterruptLine	何ライン目で割り込みを起こすか指定します。0～240/480の値を設定してください。 

Result:
	KMSTATUS_SUCCESS			設定成功
	KMSTATUS_ILLEGAL_PARAMETER	値が不正

--*/

KMSTATUS KMAPI
kmSetHSyncLine(
		KMINT32 nInterruptLine
	);

/*++
kmGetCurrentScanline

proto type:
	KMSTATUS
	kmGetCurrentScanline(
			PKMINT32 pScanline
		);

Description:
	現在のH-Syncラインを読み出します。 

Arguments:
	OUT	pScanline	現在のH-Syncラインを格納するKMINT32へのポインタです。 

Result:
	KMSTATUS_SUCCESS			設定成功

--*/
KMSTATUS KMAPI
kmGetCurrentScanline(
		PKMINT32 pScanline
	);

/*++
kmWaitVBlank

proto type:
	KMSTATUS
	kmWaitVBlank(
			KMVOID
		);

Description:
	V-Sync を待ち合わせます。

Arguments:

Result:
	KMSTATUS_SUCCESS			成功

--*/
KMSTATUS KMAPI
kmWaitVBlank( KMVOID );


/*++
kmGetDisplayColorMode

proto type:
	KMSTATUS
	kmGetDisplayColorMode(
			PKMINT32 pBpp
		);

Description:
	現在の表示カラーモードラインを読み出します。

Arguments:
	OUT	pBpp		現在のカラーモードを格納するKMINT32へのポインタです。

Result:
	KMSTATUS_SUCCESS			取得成功

--*/

KMSTATUS KMAPI
kmGetDisplayColorMode(
		OUT KMINT32		pBpp
	);

/*++
kmSetVirticalFilterMode

proto type:
	KMSTATUS
	kmSetVirticalFilterMode(
			PKMINT32 pBpp
		);

Description:
	レンダリングに使用する縦方向フィルタの種類を設定します。

Arguments:
	IN	nMode		設定する 縦方向フィルタの種類です。

			KM_VIRTICAL_FILTER_NORMAL		デフォルトのモードです。
			KM_VIRTICAL_FILTER_NO_FILTER	ムービー再生時などに、縦フィルタをカット
											する場合に指定します。
			KM_VIRTICAL_FILTER_SQUARE_PIXEL 上下が切れにくい様に縦方向に縮小します。

Result:
	KMSTATUS_SUCCESS			取得成功

--*/
KMSTATUS KMAPI
kmSetVirticalFilterMode(
		IN	KM_VIRTICAL_FILETERMODE nMode
	);

/*++
kmGetVirticalFilterMode

proto type:
	KMSTATUS
	kmGetVirticalFilterMode(
			OUT	PKMINT32 pMode
		);

Description:
	現在の縦方向フィルタの種類を読み出します。

Arguments:
	OUT	pMode		縦方向フィルタの種類を格納するKMINT32へのポインタです。

			KM_VIRTICAL_FILTER_NORMAL		デフォルトのモードです。
			KM_VIRTICAL_FILTER_NO_FILTER	ムービー再生時などに、縦フィルタをカット
											する場合に指定します。
			KM_VIRTICAL_FILTER_SQUARE_PIXEL 上下が切れにくい様に縦方向に縮小します。


Result:
	KMSTATUS_SUCCESS			取得成功

--*/

KMSTATUS KMAPI
kmGetVirticalFilterMode(
		OUT	PKMINT32 pMode
	);

/*++
kmGetDisplaySize

proto type:
	KMSTATUS KMAPI
	kmGetDisplaySize( 
			OUT	PKMINT32	pWidth,
			OUT	PKMINT32	pHeight
		);

Description:
	画面のサイズを取得する。

Arguments:
	OUT	pWidth		幅を得る。
	OUT	pHeight		高さを得る。


Result:
	KMSTATUS_SUCCESS			取得成功

--*/
KMSTATUS KMAPI
kmGetDisplaySize( 
		OUT	PKMINT32	pWidth,
		OUT	PKMINT32	pHeight
	);


/*++
kmGetDisplayInfo

proto type:
	KMSTATUS KMAPI
	kmGetDisplayInfo(
			IN	KMDISPLAYINFO	nIndex,
			OUT	PKMDWORD 		pInfo
		);

Description:
	画面のサイズを取得する。

Arguments:
	IN	nIndex		
	OUT	pInfo		


Result:
	KMSTATUS_SUCCESS			取得成功

--*/
KMSTATUS KMAPI
kmGetDisplayInfo(
		IN	KMDISPLAYINFO	nIndex,
		OUT	PKMDWORD 		pInfo
	);


/*++
kmGetCurrentDisplaySurface

proto type:
	KMSTATUS KMAPI
	kmGetCurrentDisplaySurface(
			OUT	PKMSURFACEDESC pDesc
		);

Description:
	画面のサイズを取得する。

Arguments:
	OUT	pDesc		


Result:
	KMSTATUS_SUCCESS			取得成功

--*/
KMSTATUS KMAPI
kmGetCurrentDisplaySurface(
		OUT	PKMSURFACEDESC pDesc
	);

#endif
