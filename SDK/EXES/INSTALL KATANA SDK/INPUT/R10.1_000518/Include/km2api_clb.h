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
  Module Name:		km2api_clb.h

  Abstract:
	KAMUI = Kamui is abstruction model that is ultimate interface for PowerVR.
	'km2api_clb.h' define the function which is related with callback.

  Environment:
	ANSI C Compiler.

  Notes:
	This heder file defines the function which registers callback function.
	The factor of callback is shown bellow.
		- end of render
		- end of vertex
		- end of yuv
		- V-Sync
		- H-Sync

		- Texture Over flow
		- Waiting V-Sync()

		- Strip Buffer Overrun
		- Fatal Error

  Revision History:

--*/

#if !defined(__kamui2_callback_api_h__)
#define __kamui2_callback_api_h__

/*++
kmSetEORCallback

proto type:

	KMSTATUS 
	kmSetEORCallback(
			PKMCALLBACKFUNC pEORCallback,
			PVOID pCallbackArguments
		);

Description:
	レンダリング終了時に呼ばれるコールバック関数を登録します。
	コールバック関数は、以下の形式でコーディングしてください。

		VOID EORCallbackFunc(PVOID pCallbackArguments);

	pCallbackArguments(入力)：登録時に指定されたパラメータへのポインタです。

Arguments:
	IN	pEORCallback	レンダリング終了時に呼ばれる関数のポインタを指定します。
	IN	pCallbackArguments
						callback 時に呼出される関数へ渡す、引数へのポインタを指定します。


Result:
	KMSTATUS_SUCCESS		登録成功

--*/

KMSTATUS  KMAPI
kmSetEORCallback(
		PKMCALLBACKFUNC pEORCallback,
		PVOID 			pCallbackArguments
	);

/*++
kmSetVSyncCallback

proto type:
	KMSTATUS
	kmSetVSyncCallback(
			PKMCALLBACKFUNC pVSyncCallback,
			PVOID pCallbackArguments
		);

Description:
	垂直帰線区間(Vsync)突入時に呼び出されるコールバック関数を登録します。
	コールバック関数は、以下の形式でコーディングしてください。

		VOID VSyncCallbackFunc(PVOID pCallbackArguments);

	pCallbackArguments(入力)：登録時に指定されたパラメータへのポインタです。

Arguments:
	IN	pVSyncCallback	Vsync突入時に呼ばれる関数のポインタを指定します。
	IN	pCallbackArguments
						callback 時に呼出される関数へ渡す、引数へのポインタを指定します。

Result:
	KMSTATUS_SUCCESS		登録成功

--*/

KMSTATUS KMAPI
kmSetVSyncCallback(
		PKMCALLBACKFUNC pVSyncCallback,
		PVOID 			pCallbackArguments
	);

/*++
kmSetHSyncCallback

proto type:
	KMSTATUS
	kmSetHSyncCallback(
			PKMCALLBACKFUNC pHSyncCallback,
			PVOID pCallbackArguments
		);

Description:
	水平帰線区間(Hsync)突入時に呼び出されるコールバック関数を登録します。
	コールバック関数は、以下の形式でコーディングしてください。

	VOID HSyncCallbackFunc(PVOID pCallbackArguments);

	pCallbackArguments(入力)：登録時に指定されたパラメータへのポインタです。

Arguments:
	IN	pHSyncCallback		Hsync突入時に呼ばれる関数のポインタを指定します。

	pCallbackArguments		callback 時に呼出される関数へ渡す、引数へのポインタを指定します。
							KmSetHSyncLine で指定したライン番号は渡されないので、
							kmSetHSyncLine で設定した値をこのポインタが示す領域に保持するか、
							または、kmGetCurrentScanline()を使用して、現在の Scanline 数を取得してください。

Result:
	KMSTATUS_SUCCESS		登録成功

--*/

KMSTATUS KMAPI
kmSetHSyncCallback(
		PKMCALLBACKFUNC pHSyncCallback,
		PVOID pCallbackArguments
	);

/*++
kmSetTexOverflowCallback

proto type:
	KMSTATUS
	kmSetTexOverflowCallback(
			PKMCALLBACKFUNC pTexOverflowCallback,
			PVOID pCallbackArguments
		);

Description:
	テクスチャメモリが残っていない状態で、テクスチャを登録しようとした場合に呼ばれるコールバック関数を
	登録します。コールバック関数は、以下の形式でコーディングしてください。

		VOID TexOverflowCallbackFunc(PVOID pCallbackArguments);

	pCallbackArguments(入力)：登録時に指定されたパラメータへのポインタです。

Arguments:
	IN	pTexOverflowCallback	テクスチャオーバーフロー時のコールバック関数へのポインタを指定します。
	IN	pCallbackArguments		callback 時に呼出される関数へ渡す、引数へのポインタを指定します。
	
Result:
	KMSTATUS_SUCCESS		登録成功

--*/

KMSTATUS KMAPI
kmSetTexOverflowCallback(
		PKMCALLBACKFUNC pTexOverflowCallback,
		PVOID pCallbackArguments
	);

/*++
kmSetStripOverRunCallback

proto type:
	KMSTATUS
	kmSetStripOverRunCallback (
			PKMCALLBACKFUNC	pStripOverRunCallback,
			PVOID			pCallbackArguments
		);

Description:
	StripBufferの縦サイズの表示期間中に次のStripのレンダリングが終了しなかった場合に呼ばれる
	コールバック関数を登録します。コールバック関数は、以下の形式でコーディングしてください。

			VOID StripOverRunCallbackFunc(PVOID pCallbackArguments);

	pCallbackArguments(入力)：登録時に指定されたパラメータへのポインタです。

Arguments:
	IN	pStripOverRunCallback	コールバック関数へのポインタを指定します。
	IN	pCallbackArguments		callback 時に呼出される関数へ渡す、引数へのポインタを指定します。

Result:
	KMSTATUS_SUCCESS		登録成功

--*/

KMSTATUS KMAPI
kmSetStripOverRunCallback (
		PKMCALLBACKFUNC	pStripOverRunCallback,
		PVOID			pCallbackArguments
	);

/*++
kmSetEndOfVertexCallback

proto type:
	KMSTATUS
	kmSetEndOfVertexCallback (
			PKMCALLBACKFUNC pEndOfVertexCallback,
			PKMVOID			pCallbackArguments
		);

Description:
	神威からレンダリングハードウェアへの、1シーンのデータ転送が終了した場合に呼ばれるコールバック関数を
	登録します。コールバック関数は、以下の形式でコーディングしてください。

			VOID EndOfVertexCallbackFunc(PVOID pCallbackArguments);

	pCallbackArguments(入力)：登録時に指定されたパラメータへのポインタです。

Arguments:
	IN	pEndOfVertexCallback	コールバック関数へのポインタを指定します。
	IN	pCallbackArguments		callback 時に呼出される関数へ渡す、引数へのポインタを指定します。

Result:
	KMSTATUS_SUCCESS		登録成功

--*/

KMSTATUS KMAPI
kmSetEndOfVertexCallback (
		PKMCALLBACKFUNC pEndOfVertexCallback,
		PKMVOID 		pCallbackArguments
	);

/*++
kmSetEndOfYUVCallback

proto type:
	KMSTATUS
	kmSetEndOfYUVCallback(
			PKMCALLBACKFUNC pEndOfYUVCallback,
			PVOID pCallbackArguments
		);

Description:
	YUVコンバータがコンバートを終了した際に発行する、YUV終了割り込みに対する
	コールバック関数を登録します。

		VOID EndOfYUVFunc(PVOID pCallbackArguments);

	pCallbackArguments(入力)：登録時に指定されたパラメータへのポインタです。

Arguments:
	IN	pEndOfYUVCallback		YUVコンバート終了時のコールバック関数へのポインタを指定します。
	IN	pCallbackArguments		callback 時に呼出される関数へ渡す、引数へのポインタを指定します。
	
Result:
	KMSTATUS_SUCCESS		登録成功

--*/

KMSTATUS KMAPI
kmSetEndOfYUVCallback(
		PKMCALLBACKFUNC pEndOfYUVCallback,
		PVOID pCallbackArguments
	);

/*++
kmSetWaitVsyncCallback

proto type:
	KMSTATUS
	kmSetWaitVsyncCallback(
			PKMCALLBACKFUNC pWaitVsyncCallback,
			PVOID pCallbackArguments
		);

Description:
	VsyncのWAIT中に呼ばれるコールバック関数を登録します。CD-ROMからの読み出しをバックグラウンド
	等で行う場合や、その他V非同期処理を行うためのコールバック等として使用します。
	ただし、あまり大きな関数、コールバック内での無限ループ等は行わないでください。
	
		VOID WaitVsyncCallbackFunc(PVOID pCallbackArguments);

	pCallbackArguments(入力)：登録時に指定されたパラメータへのポインタです。

Arguments:
	IN	pWaitVsyncCallback		Vsyncウェイト中のコールバック関数へのポインタを指定します。
	IN	pCallbackArguments		callback 時に呼出される関数へ渡す、引数へのポインタを指定します。
	
Result:
	KMSTATUS_SUCCESS		登録成功

--*/

KMSTATUS KMAPI
kmSetWaitVsyncCallback(
		PKMCALLBACKFUNC pWaitVsyncCallback,
		PVOID pCallbackArguments
	);

/*++
kmSetFatalErrorCallback

proto type:
	KMSTATUS
	kmSetFatalErrorCallback(
			PKMCALLBACKFUNC pFaltalErrorCallback,
			PVOID 			pCallbackArguments
		);

Description:
	神威２では回復不能なエラーが発生した場合に呼び出される
	コールバック関数を登録します。以下の形式で呼び出されます。

		VOID FaltalErrorCallback(PVOID pCallbackArguments);

	pCallbackArguments(入力)：登録時に指定されたパラメータへのポインタです。

Arguments:
	IN	pFaltalErrorCallback	回復不能なエラーが発生した場合に呼び出されるコールバック関数です。
	IN	pCallbackArguments		callback 時に呼出される関数へ渡す、引数へのポインタを指定します。

Result:
	KMSTATUS_SUCCESS		登録成功

--*/

KMSTATUS KMAPI
kmSetFatalErrorCallback(
		IN	PKMCALLBACKFUNC pFaltalErrorCallback,
		IN	PVOID			pCallbackArguments
	);


/*++
kmSetPALEXTCallback

proto type:
	KMSTATUS
	kmSetPALEXTCallback(
			PKMCALLBACKFUNC pPalExtCallback,
			PVOID 			Reserved
		);

Description:
	kmSetDisplayMode を呼び出した際に、	PAL ??? EXT を指定した場合、
	縦の表示比率を決定するための定数を返すためのコールバック関数です。

		VOID pPalExtCallback(PVOID pData);

	pData には、システム内部の KMPALEXTINFO 構造体へのポインタが渡されます。
	nPALExtMode メンバに対して適切な値を代入してください。
	KMPALEXTINFO 構造体の nDisplayModeには、kmSetDisplayMode の
	引数が代入されています。

Arguments:
	IN	pFaltalErrorCallback	回復不能なエラーが発生した場合に呼び出されるコールバック関数です。
	IN	reserved				NULL を入れてください。

Result:
	KMSTATUS_SUCCESS		登録成功

--*/

KMSTATUS KMAPI
kmSetPALEXTCallback( 
		IN	PKMCALLBACKFUNC pPalExtCallback,
		IN	PVOID			pCallbackArguments
	);
#endif
