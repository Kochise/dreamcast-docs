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
  Module Name:		km2api_misc.h

  Abstract:
	KAMUI = Kamui is abstruction model that is ultimate interface for PowerVR.
	'km2api_misc.h' define miscelaneous API which can not be classified.

  Environment:
	ANSI C Compiler.

  Notes:
	define Kamui's miscelaneous API proto-types which can not be classified. 
	fog , palette , pixel clipping etc..

  Revision History:

--*/

#if !defined(__kamui2_miscelaneous_api_h__)
#define __kamui2_miscelaneous_api_h__

/*++
kmSetWaitVsyncCount

proto type:

	KMSTATUS
	kmSetWaitVsyncCount( KMINT32 nCount );

Description:
		フレームレートを定率にするために、前回の Flip後、
		次にFlip 可能になるまでのV-Sync数を指定します。

Arguments:
		IN	nCount		V-Sync を待つ回数を指定します。前回の Flip後、
						次にFlip 可能になるまでのV-Sync数を指定します。

Result:
		KMSTATUS_SUCCESS			成功
--*/
KMSTATUS KMAPI
kmSetWaitVsyncCount(
		IN	KMINT32 nCount 
		);


/*++
kmSetCullingRegister

proto type:

	KMSTATUS
	kmSetCullingRegister(
			KMFLOAT fCullVal
		);

Description:
		小さい Polygon に対するカリングのスレッショルド値を設定します。

Arguments:
		IN	fCullVal	平面パラメータのデタミナント値を設定します。

Result:
		KMSTATUS_SUCCESS			Flipコマンド発行成功
		KMSTATUS_CANT_FLIP_SURFACE 	Flipコマンド発行失敗

--*/

KMSTATUS KMAPI
kmSetCullingRegister(
		IN	KMFLOAT fCullVal
	);


/*++
kmSetColorClampValue

proto type:

	KMSTATUS
	kmSetColorClampValue(
			KMPACKEDARGB MaxVal,
			KMPACKEDARGB MinVal 
		);

Description:
	カラーのクランプ値を指定します。カラークランプはフォグの前段で掛けられます。

Arguments:
	IN	MaxVal			Packedの ARGB 32bitカラーで、クランプの最大値を指定します。
	IN	MinVal			Packedの ARGB 32bitカラーで、クランプの最小値を指定します。

Result:
	KMSTATUS_SUCCESS		設定成功

--*/
KMSTATUS KMAPI
kmSetColorClampValue(
		IN	KMPACKEDARGB MaxVal,
		IN	KMPACKEDARGB MinVal 
	);

/*++
kmSetColorClampMax

proto type:
	KMSTATUS KMAPI
	kmSetColorClampMax(
			IN	KMPACKEDARGB Val
		);

Description:
	カラーのクランプ値を指定します。カラークランプはフォグの前段で掛けられます。

Arguments:
	IN	Val				Packedの ARGB 32bitカラーで、クランプの最大値を指定します。

Result:
	KMSTATUS_SUCCESS		設定成功

--*/
KMSTATUS KMAPI
kmSetColorClampMax(
		IN	KMPACKEDARGB Val
	);

/*++
kmSetColorClampMin

proto type:
	KMSTATUS KMAPI
	kmSetColorClampMin(
			IN	KMPACKEDARGB Val
		);

Description:
	カラーのクランプ値を指定します。カラークランプはフォグの前段で掛けられます。

Arguments:
	IN	Val				Packedの ARGB 32bitカラーで、クランプの最小値を指定します。

Result:
	KMSTATUS_SUCCESS		設定成功

--*/
KMSTATUS KMAPI
kmSetColorClampMin(
		IN	KMPACKEDARGB Val
	);


/*++
kmSetFogTableColor

proto type:

	KMSTATUS
	kmSetFogTableColor(
			IN	KMPACKEDARGB FogTableColor
		);

Description:
	Table を使用する フォグカラーを指定します。

Arguments:
	IN	FogTableColor		FogTable に使用するPackedの32bitカラーです。

Result:
	KMSTATUS_SUCCESS		設定成功

--*/

KMSTATUS KMAPI
kmSetFogTableColor(
		IN	KMPACKEDARGB FogTableColor
	);

/*++
kmSetFogVertexColor

proto type:

	KMSTATUS 
	kmSetFogVertexColor(
			KMPACKEDARGB FogVertexColor
		);

Description:
	FogVertex のフォグカラーを指定します。

Arguments:
	IN	FogVertexColor		FogVertexに使用するPackedの32bitカラーです。

Result:
	KMSTATUS_SUCCESS		設定成功

--*/

KMSTATUS  KMAPI
kmSetFogVertexColor(
		IN	KMPACKEDARGB FogVertexColor
	);

/*++
kmGenerateFogTable

proto type:

	KMSTATUS
	kmGenerateFogTable(
		OUT	PKMFLOAT	pFogTable,
		IN	KMFLOAT		fFrontBorder,
		IN	KMFLOAT		fBackBorder,
		IN	KMFLOAT		fFogDensity,
		OUT	KMFLOAT		*fHWFogDensity,
		IN	KMDWORD		dwFogType
		);

Description:
	フォグテーブルを自動生成します。
	フォグが有効となる区間の前縁および後縁の奥行き値を与えると、
	その区間になだらかなフォグがかかるようなフォグテーブルとフォグ係数を生成します。 

Arguments:
	OUT	PKMFLOAT	pFogTable
		生成したフォグテーブルを格納するための、
		128 エントリの KMFLOAT形式の一次元配列へのポインタです。
	IN	KMFLOAT		fFrontBorder
		フォグが有効となる区間の前縁奥行き値を指定します。
	IN	KMFLOAT		fBackBorder
		フォグが有効となる区間の後縁奥行き値を指定します。
	IN	KMFLOAT		fFogDensity
		フォグの濃度を指定します。 
	OUT	KMFLOAT		*fHWFogDensity
		kmSetFogDensity でPowerVRハードウェアに設定する、
		フォグ係数を浮動小数で返します。
	IN	KMDWORD		dwFogType
		フォグテーブルのタイプを指定します。

Result:
	KMSTATUS_SUCCESS		設定成功
	KMSTATUS_OUT_OF_RANGE	fBackBorderが0.0f以下である、
							または fBackBorder > fFrontBorderである、
							または fFogDensityが0.0fより小さい。 

--*/

KMSTATUS KMAPI
kmGenerateFogTable(
	OUT	PKMFLOAT	pFogTable,
	IN	KMFLOAT		fFrontBorder,
	IN	KMFLOAT		fBackBorder,
	IN	KMFLOAT		fFogDensity,
	OUT	KMFLOAT		*fHWFogDensity,
	IN	KMDWORD		dwFogType
	);

/*++
kmConvertFogDensity

proto type:

	KMSTATUS
	kmConvertFogDensity(
		IN	KMFLOAT		fFogDensity,
		OUT	KMDWORD		*dwFogDensity
		);

Description:
	浮動小数点数から、PowerVRハードウェアレジスタに設定するための
	2 バイトのフォグ係数を求めます。

Arguments:
	IN	KMFLOAT		fFogDensity
		kmGenerateFogTable で生成された浮動小数点数のフォグ係数を指定します。 
	OUT	KMDWORD		*dwFogDensity
		kmSetFogDensity でハードウェアに設定するときの２バイト値を返します。 

Result:
	KMSTATUS_SUCCESS		設定成功

--*/

KMSTATUS KMAPI
kmConvertFogDensity(
	IN	KMFLOAT		fFogDensity,
	OUT	KMDWORD		*dwFogDensity
	);

/*++
kmSetFogTable

proto type:

	KMSTATUS
	kmSetFogTable(
			PKMFLOAT pfFogTable
		);

Description:
	FogTableを登録します。128 個のfloat値の格納された配列へのポインタを引数として渡します。

Arguments:
	IN	pfFogTable	フォグテーブル値配列へのポインタ。128個のパラメータを指定します。

Result:
	KMSTATUS_SUCCESS		設定成功

--*/

KMSTATUS KMAPI
kmSetFogTable(
		IN	PKMFLOAT pfFogTable
	);

/*++
kmSetFogDensity

proto type:

	KMSTATUS
	kmSetFogDensity(KMDWORD fogDensity)

Description:
	Fog の係数を与える。

Arguments:
	IN	fogDensity			2 バイトの Fog の係数 

Result:
	KMSTATUS_SUCCESS		設定成功

--*/
KMSTATUS	KMAPI
kmSetFogDensity(
		IN	KMDWORD fogDensity
	);

/*++
kmSetPaletteMode

proto type:

	KMSTATUS 
	kmSetPaletteMode(	
			KMPALETTEMODE Palettemode
		);

Description:
	パレットのモード指定をします。
	パレットデータを描き込む前にパレットモードを設定する必要があります。

Arguments:
	IN	PaletteMode		パレットの BPP モード
						KM_PALETTE_16BPP_ARGB1555	16BPPモード 
						KM_PALETTE_16BPP_RGB565		16BPPモード 
						KM_PALETTE_16BPP_ARGB4444	16BPPモード 
						KM_PALETTE_32BPP_ARGB8888	32BPPモード 

Result:
	KMSTATUS_SUCCESS		設定成功

--*/
KMSTATUS  KMAPI
kmSetPaletteMode(	
		IN	KMPALETTEMODE Palettemode
	);

/*++
kmSetPaletteData

proto type:
	KMSTATUS
	kmSetPaletteData(
			PKMPALETTEDATA pPaletteTable
		);

Description:
	パレットの設定を行います。

Arguments:
	IN	pPaletteTable	Palette設定用配列のポインタを指定します。
						Palette設定用配列の内容は以下のようになります。

Result:
	KMSTATUS_SUCCESS		設定成功

--*/

KMSTATUS KMAPI
kmSetPaletteData(
		IN	PKMPALETTEDATA pPaletteTable
	);


/*++
kmSetPaletteBankData

proto type:
	KMSTATUS 
	kmSetPaletteBankData(
			IN KMINT32		PaletteEntry,
			IN KMINT32		DataSize,
			IN PKMPALETTEDATA	pPaletteTable
		);

Description:
	Palettizeテクスチャで使用される Palette の一部分を、
	指定したパレットデータで書き換えます。
	パレットの構造についてはkmSetPaletteDataを参照願います。

	パレットモードが4bpp/8bppに関わらず PaletteEntryに指定可能な値は、
	0から1023のいずれかです。バンクの境界に関係なく、任意のエントリから
	データを書き込むことができます。パレットのPaletteEntry番目のエントリから、
			PaletteEntry　＋　DataSize番目のエントリ
	までに、pPaletteTableで指される領域の先頭のデータから順にセットしていきます。
	パレット番号 1023 より大きいパレット番号に対応するデータは無視されます。
	すなわち設定が以下に示すような場合は、パレット番号1023までで停止します。
			 PaletteEntry　＋　DataSize　＞　1024　

Arguments:
	IN PaletteEntry
		データを書き込むパレットの先頭エントリ番号を指定します。
		 0 から 1023 の中のいずれかを指定します。
		指定されたエントリ番号からのパレットの内容を書き換えます。

	IN DataSize
		書き込むデータのサイズ(エントリ数)を指定します。
		1 から最大1024 が指定できます。

	IN pPaletteTable
		Palette設定用配列のポインタを指定します。
		Palette設定用配列の内容は以下のようになります。

		KMPALETTEDATA		PaletteTable;

		このパレットデータの要素数はDataSize個以上なければなりません。
		これがDataSize個以上なかった場合の動作は保証しません。

Result:
	KMSTATUS_SUCCESS		設定成功

--*/
KMSTATUS  KMAPI
kmSetPaletteBankData(
		IN KMINT32			PaletteEntry,
		IN KMINT32			DataSize,
		IN PKMPALETTEDATA	pPaletteTable
	);

/*++
kmSetPaletteBank

proto type:
	KMSTATUS 
	kmSetPaletteBank(
		IN KMINT32				Bank,
		IN KMPALETTE_ENTRY_SIZE	DataSize,
		IN PKMDWORD				pPaletteData
		);

Description:
	Palettizeテクスチャで使用されるオンチップパレットの、
	指定された 1 バンクを新たなデータで書き換えます。 

	書き換えるエントリの数は、BPPの指定により決定します。 
	DataSizeに KM_PALETTE_ENTRY_16が指定されたときは、１６エントリを書き換えます。
	この場合は、pPaletteDataには１６エントリ分のデータが必要です。 
	DataSizeにKM_PALETTE_ENTRY_256が指定されたときは、２５６エントリを書き換えます。
	この場合は、pPaletteDataには２５６エントリ分のデータが必要です。 

	パレットの構造については kmSetPaletteData を参照願います。 

Arguments:
	IN KMINT32				Bank
		書き換えるバンクの番号を指定します。
		0 から 63 までのいずれかが指定可能です。 
		8BPPパレットとして扱う場合には、0、16、32、48のいずれかが有効です。
		これ以外の値が指定された場合は、下 4 bitを mask して、
		0,16,32,48のいずれかに変換して使用します。 

	IN KMPALETTE_ENTRY_SIZE	DataSize
		書き換えるパレットデータのサイズを指定します。
		以下のいずれかが指定可能です。

		KM_PALETTE_ENTRY_16 	16エントリ分のデータを書き換えます。 
								4 BPPパレットとして扱います。
		KM_PALETTE_ENTRY_256	256エントリ分のデータを書き換えます。 
								8 BPPパレットとして扱います。


	IN PKMDWORD				pPaletteData
		Palette設定用配列のポインタを指定します。
		このパレットデータの要素数 はDataSize 個以上なければなりません。
		これが DataSize 個以上なかった場合の動作は保証しません。 

Result:
	KMSTATUS_SUCCESS		設定成功

--*/
KMSTATUS  KMAPI
kmSetPaletteBank(
		IN KMINT32				Bank,
		IN KMPALETTE_ENTRY_SIZE	DataSize,
		IN PKMDWORD				pPaletteData
	);

/*++
kmSetBorderColor

proto type:
	KMSTATUS
	kmSetBorderColor(
			KMPACKEDARGB BorderColor
		);

Description:
	ボーダー(表示画面外の部分)カラーの設定を行います。

Arguments:
	IN	BorderColor		PackedのARGBカラーです。

Result:
	KMSTATUS_SUCCESS		設定成功

--*/

KMSTATUS KMAPI
kmSetBorderColor(
		IN	KMPACKEDARGB BorderColor
	);

/*++
kmSetBackGroundRenderState

proto type:
	KMSTATUS
	kmSetBackGroundRenderState(
			PKMVERTEXCONTEXT	pVertexContext
		);

Description:
	kmProcessVertexRenderState で設定した KMVERTEXCONTEXT構造体の以下のメンバを
	Background Plane のレンダリングパラメータとしてシステムに登録する。
	本関数呼び出し以降の kmSetBackGroundPlane() で指定する ＢＧ面の設定は、
	引数、pVertexContext で設定した KMVERTEXCONTEXT の値が有効になる。

	参照するメンバ：
				pVertexContext->GLOBALPARAMBUFFER
				pVertexContext->ISPPARAMBUFFER
				pVertexContext->TSPPARAMBUFFER
				pVertexContext->TexturePARAMBUFFER


Arguments:
	IN	pVertexContext
						Vertex Context へのポインタを与える。

Result:
	KMSTATUS_SUCCESS	設定成功

--*/

KMSTATUS KMAPI
kmSetBackGroundRenderState(
		IN	PKMVERTEXCONTEXT	pVertexContext
	);

/*++
kmSetBackGroundPlane

proto type:
	KMSTATUS
	kmSetBackGroundPlane(
				PVOID			pVertex[3],
				KMVERTEXTYPE	VertexType,
				KMINT32			StructSize
			);

Description:
	バックグラウンド平面の設定を行います。
	この前に、kmSetBackGroundRenderState を呼び出す必要があります。

Arguments:
	IN	pVertex[3]		バックグラウンドプレーン上の座標を示す頂点データ構造体へのポインタ
						詳細は、 kmSetVertex 参照

	IN	VertexType		頂点データのデータタイプを示す。
						詳細は kmSetVertex 参照
	IN	StructSize		頂点データのデータタイプを示す。
						詳細は kmSetVertex 参照

Result:
	KMSTATUS_SUCCESS			設定成功

--*/

KMSTATUS KMAPI
kmSetBackGroundPlane(
			IN	PVOID			pVertex[3],
			IN	KMVERTEXTYPE	VertexType,
			IN	KMINT32			StructSize
		);

/*++
kmSetBackGround

proto type:
	KMSTATUS
	kmSetBackGroundPlane(
				IN	PKMSTRIPHEAD	pStripHead,
				IN	KMVERTEXTYPE	VertexType,
				IN	PVOID			pVertex1,
				IN	PVOID			pVertex2,
				IN	PVOID			pVertex3
			);

Description:
	バックグラウンド平面の設定を行います。

Arguments:
	IN	pStripHead		有効な KMSTRIPHEAD 構造体へのポインタを渡します。
	IN	VertexType		background 面で使用する頂点データのデータタイプを示す。
	IN	pVertex1 / 		バックグラウンドプレーン上の座標を示す頂点データ構造体へのポインタ
		pVertex2 /		(0-16)
		pVertex3

Result:
	KMSTATUS_SUCCESS			設定成功

--*/
KMSTATUS KMAPI
kmSetBackGround(
		IN	PKMSTRIPHEAD	pStripHead,
		IN	KMVERTEXTYPE	VertexType,
		IN	PVOID			pVertex1,
		IN	PVOID			pVertex2,
		IN	PVOID			pVertex3
	);

/*++
kmSetAutoSortMode

proto type:
	KMSTATUS
	kmSetAutoSortMode(
			KMBOOLEAN fEnable
		);

Description:
	半透明面のオートソートモードのON/OFFを制御します。

	-> マルチパス対応のために、この関数は無効にしました。
	   kmSetSystemConfiguration を使用して、
	   各パス毎に AutoSort の有無を指定してください。

Arguments:
	IN	bEnable		Auto Sort mode の有効化フラグ
				TRUE	半透明面のソートにオートソートモードを設定します。
				FALSE	従来型と同じソフトウェアによるソーティングをエミュレーションします。

Result:
	KMSTATUS_SUCCESS		設定成功

--*/
KMSTATUS KMAPI
kmSetAutoSortMode(
		IN	KMBOOLEAN fEnable
	);

/*++
kmSetPixelClipping

proto type:
	KMSTATUS
	kmSetPixelClipping(
				KMINT32	Xmin,
				KMINT32	Ymin,
				KMINT32	Xmax,
				KMINT32	Ymax
			);

Description:
	 Frame Buffer へのレンダリングの出力に対する、ピクセル単位のクリッピングを設定します。

Arguments:
	IN	Xmin, Ymin, Xmax, Ymax
				ピクセル単位のクリッピング領域の左上、右下座標を指定します。
				(Xmin,Ymin)-(Xmax,Ymax)は、画面サイズより小さくなければいけません。
				また、画面モードが24bppの時は、クリッピング領域の座標は偶数でなければいけません
				(すなわち 2ピクセル単位でしかクリッピング領域を設定できません)。
				偶数でなかった場合には、(Xmin,Ymin)に対しては指定より 1 大きい値、
										(Xmax,Ymax)に対しては指定より 1 小さい値が設定されます。

Result:
	KMSTATUS_SUCCESS		設定成功
	KMSTATUS_INVALID_PARAMETER	パラメータが不正

--*/

KMSTATUS KMAPI
kmSetPixelClipping(
		IN	KMINT32	Xmin,
		IN	KMINT32	Ymin,
		IN	KMINT32	Xmax,
		IN	KMINT32	Ymax
	);

/*++
kmSetRegionClipping

proto type:
	KMSTATUS
	kmSetRegionClipping(
				KMINT32	Xmin,
				KMINT32	Ymin,
				KMINT32	Xmax,
				KMINT32	Ymax
			);

Description:
	 Frame Buffer へのレンダリングの出力に対する、リージョン単位のクリッピングを設定します。

Arguments:
	IN	Xmin, Ymin, Xmax, Ymax
				リージョン単位のクリッピング領域の左上、右下座標を指定します。
				(Xmin,Ymin)-(Xmax,Ymax)は、画面サイズより小さくなければいけません。

Result:
	KMSTATUS_SUCCESS		設定成功
	KMSTATUS_INVALID_PARAMETER	パラメータが不正

--*/

KMSTATUS KMAPI
kmSetRegionClipping(
		IN	KMINT32	Xmin,
		IN	KMINT32	Ymin,
		IN	KMINT32	Xmax,
		IN	KMINT32	Ymax
	);

/*++
kmSetGlobalClipping

proto type:
	KMSTATUS
	kmSetGlobalClipping(
				KMINT32 nWidth, 
				KMINT32 nHeight
			);
Description:
	グローバルクリッピング領域を指定します。0,0オリジンでWidth、Heightで指定された
	領域以外のところにはレンダリングされません。

Arguments:
	IN	nWidth, nHeight				タイルサイズは、32x32です。
									たとえば128x64の領域を指定したい場合には 
									Width = 4,Height= 2とします。

Result:
	KMSTATUS_SUCCESS					設定成功
	KMSTATUS_INVALID_PARAMETER			設定失敗

--*/

KMSTATUS KMAPI
kmSetGlobalClipping(
		IN	KMINT32 nWidth, 
		IN	KMINT32 nHeight
	);

/*++
kmSetStrideWidth

proto type:
	KMSTATUS
	kmSetStrideWidth(
			KMINT32 nWidth
		);

Description:
	ストライドテクスチャのストライドサイズを指定します。ストライドサイズは、
	32 の倍数でなければならない。

Arguments:
	IN	nWidth		ストライドサイズを入力する。
					ストライドサイズは 32の倍数でなければならない。

Result:
	KMSTATUS_SUCCESS			設定成功
	KMSTATUS_INVALID_PARAMETER	パラメータが不正

--*/

KMSTATUS KMAPI
kmSetStrideWidth(
		KMINT32 nWidth
	);

/*++
kmResetRenderer

proto type:

	KMSTATUS
	kmResetRenderer( VOID );

Description:
	レンダリングパイプラインのソフトウェアリセットを行う。

	使用する場合：
		・StripBuffer使用時にストリップ内のデータを描ききれなかった
		  場合の強制リセットする。

Arguments:
	NONE

Result:

	KMSTATUS_SUCCESS				成功

--*/

KMSTATUS KMAPI
kmResetRenderer( VOID );

/*++
kmSetUserClipLevelAdjust

proto type:

	KMSTATUS
	kmSetUserClipLevelAdjust( KMADJUSTTYPE	Adjust,
				  PKMINT32	pLine
				 );

Description:
	水平方向の画面表示モードを設定します。
	これを使用することにより、水平方向のユーザークリッピング領域の境界を、
	画面のほぼ中央に来るようにすることができます。対戦ゲームなどで画面を
	上下 2 分割して使用する場合に設定します。

	神威で画面を上下 2 つに分割したい場合は、この関数でKM_LEVEL_ADJUST_HALFを指定した上で、
	ユーザークリップ領域のＹ座標を下記のように設定してください。すると、このクリップ領域の
	水平方向の境界が極力画面の中央となるよう、表示領域を調整します。

		画面の縦方向の解像度	ユーザークリップ領域のＹ座標
			240						0 ～ 119　と　120 ～ 239
			480						0 ～ 255　と　256 ～ 479

	なお、この場合、画面の上部何ラインかは表示しなくなります。表示され
	なくなるライン数は、pLineから得ることができます。

Arguments:
	IN	Adjust	水平方向の画面表示モードを指定します。
			以下のいずれかが指定できます。
			KMADJUSTTYPE
			KM_LEVEL_ADJUST_NORMAL		通常表示用の表示モード指定します。
			KM_LEVEL_ADJUST_HALF		2分割表示用の表示モードを指定します。


	OUT	pLine
			AdjustにKM_LEVEL_ADJUST_HALFを指定した場合、神威はここに画面の上下方向の
			シフト量をピクセル数で返します。画面の最上部から、ここで指定されたライン数は
			表示されなくなります。頂点登録時には各頂点のＹ座標値に、この値を加算してください。
			pLine に NULL を指定してもかまいませんが、その場合、ユーザは頂点のＹ座標に加算すべき
			ライン数を取得することができません。

			AdjustにKM_LEVEL_ADJUST_NORMALを指定した場合は、pLineが指す領域の内容は変更しません。


Result:

	KMSTATUS_SUCCESS				成功

--*/
KMSTATUS KMAPI
kmSetUserClipLevelAdjust(
		IN	KMADJUSTTYPE	Adjust,
		OUT	PKMINT32	pLine
	);

/*++
kmGetGunTriggerPos

proto type:
	KMSTATUS KMAPI
	kmGetGunTriggerPos(
			PKMDWORD pHPos,
			PKMDWORD pVPos
		);

Description:
	Gun Peripheral のトリガが押された位置を返します。

Arguments:
	OUT	pHPos	H-Blank Out からの水平位置
    OUT	pVPos	V-Blank Out からの垂直位置

Result:
	KMSTATUS_SUCCESS		成功

--*/

KMSTATUS KMAPI
kmGetGunTriggerPos(
		OUT	PKMDWORD pHPos,
		OUT	PKMDWORD pVPos
	);

/*++
kmUseAnotherModifier

proto type:
	KMSTATUS
	kmUseAnotherModifier(
			KMLISTTYPE kmModifierListType
			);

Description:
	kmModifierListType で指定した Modifier を他方の 
	Modifier としても使用する。

	-> マルチパス対応のために、この関数は無効にしました。
	   kmSetSystemConfiguration を使用して、各パス毎に 
		他方のリストを使用機能の有無を指定してください。

Arguments:
	IN	kmModifierListType		KM_OPAQUE_MODIFIER	Opaque Modifier を Trans Modifier  として使用する。
								KM_TRANS_MODIFIER	Trans Modifier  を Opaque Modifier として使用する。

Result:
	KMSTATUS_SUCCESS				設定成功
	KMSTATUS_INVALID_LIST_TYPE		設定失敗

--*/

KMSTATUS KMAPI
kmUseAnotherModifier(
		IN	KMLISTTYPE kmModifier
			);

/*++
kmSetCheapShadowMode

proto type:
	KMSTATUS
	kmSetCheapShadowMode(
			KMINT32 nIntensity
			);

Description:
	チープ(簡易)シャドウモードを選択します。CheapShadowModeとは、あるPolygonが Modifier Volume にさしかかった場合、
   その部分の輝度を下げることにより影を表現する機能です。この関数で値が設定された後は、すべてのModifierVolumeの設定は
   チープシャドウモードに設定されます。シーン内で 2 パラメータPolygonとの共存はできません。
   CheapShadowModeを終了させるには引数に負の数を入れてこの関数を呼び出してください。

Arguments:
	IN	nIntensity		モディファイアボリューム内に入ったPolygonの輝度を設定します。0から255の値が使用できます。
						実際にはこれを256で割った値がPolygonのベースカラーとオフセットカラーに乗算されます。従って、
						128を指定すると128/256 = 0.5が乗算されることになります。また、負の値を入力した場合、
						そのシーンから CheapShadowMode の設定を終了し、通常の 2 パラメータPolygonが有功となります。

Result:
	KMSTATUS_SUCCESS					設定成功
	KMSTATUS_INVALID_PARAMETER			パラメータが不正

--*/

KMSTATUS KMAPI
kmSetCheapShadowMode(
		IN	KMINT32 nIntensity
			);


/*++
kmQueryFinishLastTextureDMA

proto type:
	KMSTATUS
	kmQueryFinishLastTextureDMA(KMVOID);

Description:
	前回のLoadTextureによるDMAが終了したかどうかをチェックします。
	kmSetSystemConfigurationでflagにKM_CONFIGFLAG_NOWAIT_FINISH_TEXTUREDMAが
	場合にのみ有効です。それ以外の場合には、常にKMSTATUS_SUCCESSを返します。

Arguments:
	なし

Result:
	KMSTATUS_SUCCESS				前回のDMAは終了している
	KMSTATUS_NOT_FINISH_DMA			前回のDMAは終了していない

--*/
KMSTATUS KMAPI
kmQueryFinishLastTextureDMA(KMVOID);


/*++
kmGetSystemMetrics

proto type:
	KMSTATUS
	kmGetSystemMetrics(
		PKMSYSTEMMETRICS pSysMetrics
		);

Description:

Arguments:
	IN	OUT	pSysMetrics				

Result:
	KMSTATUS_SUCCESS				

--*/
KMSTATUS KMAPI
kmGetSystemMetrics(
		IN OUT PKMSYSTEMMETRICS pSysMetrics
		);

/*++
kmSetPunchThroughThreshold

proto type:
	KMSTATUS KMAPI
	kmSetPunchThroughThreshold(
			IN	KMDWORD dwThreshold
		);

Description:
		Punch Through List の α の閾値を設定します。

			0 < α < dwThreshold 	= 0
			dwThreshold  < α < 255	= 0xff

Arguments:
	IN	dwThreshold		Punch Through List の α 閾値
						範囲 ： 0 - 255

Result:
	KMSTATUS_SUCCESS				設定成功

--*/
KMSTATUS KMAPI
kmSetPunchThroughThreshold(
		IN	KMDWORD dwThreshold
	);

#endif
