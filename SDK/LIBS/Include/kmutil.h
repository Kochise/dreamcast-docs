/*++

  COPYRIGHT        (C) NEC        Corporation 1997 - 1999

  All rights reserved by NEC Corporation. This program must be
  used solely for the purpose for which it was furnished by NEC
  Corporation. No part of this program may be reproduced or
  disclosed to others, in any form, without the prior written
  permission of NEC Corporation.
  Use of copyright notice does not evidence publication of this
  program.

  Author	:  		T.Muto(NEC Software Ltd.,)
  Module Name:		kmutil.h

  Abstract:
	KAMUI = Kamui is abstruction model that is ultimate interface for PowerVR.
	'kmutil.h' utilities functions for KAMUI.

  Environment:
	Microsoft Compiler.

  Notes:

  Revision History:

--*/

#if !defined(__kamui_utility_h)
#define __kamui_utility_h

#ifdef __cplusplus
extern "C" {
#endif 

#include "kamui2.h"

/*
 * KMUPASSSTATUS is kmuXxxPassTable Status.
 */
typedef KMUINT32	KMUPASSSTATUS;

/*
 *	for kmutil target
 */
#define	KMU_TARGET_ARC1			(0x00000001)
#define	KMU_TARGET_CLX1			(0x00000002)
#define	KMU_TARGET_CLX2			(0x00000003)

/*
 *	for kmuXxxPassTable
 */
#define KMU_PASS_OK							 0L
#define KMU_PASS_ERROR_VERTEXCONTEXT		 1L
#define KMU_PASS_ERROR_VERTEXCONTEXT_PASS	 2L
#define KMU_PASS_ERROR_PARAMTYPE			 3L
#define KMU_PASS_ERROR_LISTTYPE				 4L
#define KMU_PASS_ERROR_MIPMAP_D_ADJUST		 5L
#define KMU_PASS_ERROR_FOGMODE				 6L
#define KMU_PASS_ERROR_FILTERMODE			 7L
#define KMU_PASS_ERROR_TEXTURESHADINGMODE	 8L
#define KMU_PASS_ERROR_COLORTYPE			 9L
#define KMU_PASS_ERROR_SHADINGMODE			10L
#define KMU_PASS_ERROR_USERCLIPMODE			11L
#define KMU_PASS_ERROR_TRILINEAR_SETTING	12L
#define KMU_PASS_ERROR_SPRITE_SETTING		13L
#define KMU_PASS_ERROR_BLENDINGMODE_SETTING	14L
#define KMU_PASS_ERROR_MODIFIER_SETTING		15L

#define KMU_PASS_ERROR_NOT_IMPLEMENTED	   120L

/*
 * for kmuCalculateKamuiWorkareaSize
 */
typedef struct tagKMWORKAREASIZE
{
	/* Inputs by user */
	KMDWORD		dwNumberOfFameBuffes;		/* Number of Frame buffers */
	KMDWORD		dwNumberOfNativeBuffers;	/* Number of Native buffer */
	KMDWORD		dwNumberOfTextures;			/* Number of Textures (No small VQ) */
	KMDWORD		dwNumberOf8x8SmallVQ;		/* Number of 8x8 small VQ texture */
	KMDWORD		dwNumberOf8x8SmallVQmm;		/* Number of 8x8 small VQ mipmap texture */
	KMDWORD		dwNumberOf16x16SmallVQ;		/* Number of 16x16 small VQ texture */
	KMDWORD		dwNumberOf16x16SmallVQmm;	/* Number of 16x16 small VQ mipmap texture */
	KMDWORD		dwNumberOf32x32SmallVQ;		/* Number of 32x32 small VQ texture */
	KMDWORD		dwNumberOf32x32SmallVQmm;	/* Number of 32x32 small VQ mipmap texture */
	KMDWORD		dwNumberOf64x64SmallVQ;		/* Number of 64x64 small VQ texture */
	KMDWORD		dwNumberOf64x64SmallVQmm;	/* Number of 64x64 small VQ mipmap texture */

	/* Outputs for SystemConfigStruct */
	KMDWORD		dwTextureStructNum;			/* Number of texture structure */
	KMDWORD		dwSmallVQStructNum;			/* Number of small VQ texture structure */
	KMDWORD		dwKamuiWorkareaSize;		/* Size of Kamui work area */
} KMWORKAREASIZE, *PKMWORKAREASIZE;


/*++
kmuCreateTwiddledTexture

proto type:

	KMSTATUS
	kmuCreateTwiddledTexture(
			PKMDWORD		pOutputTexture,
			PKMDWORD		pInputTexture,
			KMBOOLEAN		bAutoMipMap,
			KMBOOLEAN		bDither,
			KMINT32			USize,
			KMTEXTURETYPE	nTextureType
		);

Description:
	メインメモリ上のKM_TEXTURE_BMP形式(ABGR8888)のテクスチャを、
	Twiddled / Twiddled Mipmap 形式のテクスチャに変換します。
	bAutoMipMapにTRUEを指定した場合は、ミップマップの自動生成を行います。
	bDitherにTRUEを指定した場合は、ディザを行います。
	注意：ミップマップ、ディザの指定を行ったときは
			入力テクスチャデータの内容は破壊されます。

Arguments:
	OUT	pOutputTexture	変換後のテクスチャデータを書き込むメインメモリ上のアドレスです。
	IN	pInputTexture	KM_TEXTURE_BMP形式の入力テクスチャを示すポインタです。
	IN	bAutoMipMap		自動的にMIPMAPを生成するかどうかを指定します。
						TRUEが指定された場合には自動的にMIPMAPを生成します。
						(出力はKM_TEXTURE_TWIDDLED_MM形式になります)
						FALSEが指定された場合にはMIPMAP生成は行いません。
						(出力はKM_TEXTURE_TWIDDLED形式になります)
	IN	bDither			ディザをかけるかどうかを指定します。
						TRUEが指定された場合はディザをかけます。
	IN	USize			テクスチャの一辺のテクセル数を指定します。
						下記の中のいずれかを指定します。
						KM_MAPSIZE_8
						KM_MAPSIZE_16
						KM_MAPSIZE_32
						KM_MAPSIZE_64
						KM_MAPSIZE_128
						KM_MAPSIZE_256
						KM_MAPSIZE_512
						KM_MAPSIZE_1024
	IN	nTextureType	変換後のテクスチャのピクセルフォーマットを指定します。
						下記の中のいずれかを指定します。
						KM_PIXELFORMAT_ARGB1555
						KM_PIXELFORMAT_RGB565
						KM_PIXELFORMAT_ARGB4444

Result:
	KMSTATUS_SUCCESS					読み込み成功
	KMSTATUS_INVALID_TEXTURE_TYPE		無効なテクスチャタイプ、サイズを指定した

--*/

KMSTATUS KMAPI
kmuCreateTwiddledTexture(
	OUT	PKMDWORD		pOutputTexture,
	IN	PKMDWORD		pInputTexture,
	IN	KMBOOLEAN		bAutoMipMap,
	IN	KMBOOLEAN		bDither,
	IN	KMINT32			USize,
	IN	KMTEXTURETYPE	nTextureType
	);


/*++
kmuCreateTwiddledTextureEx

proto type:

	KMSTATUS
	kmuCreateTwiddledTextureEx(
		OUT	PKMDWORD		pOutputTexture,
		IN	PKMDWORD		pInputTexture,
		IN	KMBOOLEAN		bAutoMipMap,
		IN	KMBOOLEAN		bDither,
		IN	KMINT32			USize,
		IN	KMINT32			VSize,
		IN	KMTEXTURETYPE	nTextureType,
		IN	PKMDWORD		pWorkarea
		);

Description:
	メインメモリ上のKM_TEXTURE_BMP形式(ABGR8888)のテクスチャを、
	Twiddled / Twiddled Mipmap 形式のテクスチャに変換します。
	bAutoMipMapにTRUEを指定した場合は、ミップマップの自動生成を行います。
	bDitherにTRUEを指定した場合は、ディザを行います。
	USizeとVSizeに異なる値を指定した場合には、TwiddledRectangle形式
	のテクスチャを生成します。
	注意：ミップマップ、ディザの指定を行ったときは
			入力テクスチャデータの内容は破壊されます。

Arguments:
	OUT	pOutputTexture	変換後のテクスチャデータを書き込むメインメモリ上のアドレスです。
	IN	pInputTexture	KM_TEXTURE_BMP形式の入力テクスチャを示すポインタです。
	IN	bAutoMipMap		自動的にMIPMAPを生成するかどうかを指定します。
						TRUEが指定された場合には自動的にMIPMAPを生成します。
						(出力はKM_TEXTURE_TWIDDLED_MM形式になります)
						FALSEが指定された場合にはMIPMAP生成は行いません。
						(出力はKM_TEXTURE_TWIDDLED形式になります)
	IN	bDither			ディザをかけるかどうかを指定します。
						TRUEが指定された場合はディザをかけます。
	IN	USize, VSize	テクスチャの一辺のテクセル数を指定します。
						下記の中のいずれかを指定します。
						KM_MAPSIZE_8
						KM_MAPSIZE_16
						KM_MAPSIZE_32
						KM_MAPSIZE_64
						KM_MAPSIZE_128
						KM_MAPSIZE_256
						KM_MAPSIZE_512
						KM_MAPSIZE_1024
	IN	nTextureType	変換後のテクスチャのピクセルフォーマットを指定します。
						下記の中のいずれかを指定します。
						KM_PIXELFORMAT_ARGB1555
						KM_PIXELFORMAT_RGB565
						KM_PIXELFORMAT_ARGB4444
	IN	pWorkarea		入力データと同じサイズのワークエリアを準備し、
						その先頭アドレスを指定します。
						横長のテクスチャをTwiddled-Rectangle形式に変換する場合に必要です。 
						その他の場合にはワークエリアは必要ありません。
						その場合にはNULLを指定してください。 

Result:
	KMSTATUS_SUCCESS					読み込み成功
	KMSTATUS_INVALID_TEXTURE_TYPE		無効なテクスチャタイプ、サイズを指定した

--*/

KMSTATUS KMAPI
kmuCreateTwiddledTextureEx(
	OUT	PKMDWORD		pOutputTexture,
	IN	PKMDWORD		pInputTexture,
	IN	KMBOOLEAN		bAutoMipMap,
	IN	KMBOOLEAN		bDither,
	IN	KMINT32			USize,
	IN	KMINT32			VSize,
	IN	KMTEXTURETYPE	nTextureType,
	IN	PKMDWORD		pWorkarea
	);


/*++
kmuConvertFBtoBMP

proto type:

	KMSTATUS
	kmuConvertFBtoBMP(
			PKMDWORD		pOutputData,
			PKMDWORD		pInputData,
			KMINT32			nWidth,
			KMINT32			nHeight,
			KMBPPMODE		nBpp
		);

Description:
	kmGetTextureでメインメモリ上に読み出したフレームバッファの内容を、
	Windows フルカラーBMP形式のピクセルデータとして、メモリ上に書き出します。
	なお、この出力にはWindows BMPのヘッダ54バイトは生成されません。

Arguments:
	OUT	pOutputData		変換後のピクセルデータを書き込むメインメモリ上のアドレスです。
	IN	pInputData		フレームバッファの内容を示すポインタです。
						kmGetTextureで、フレームバッファサーフェスへのディスクリプタを
						指定して読み出したフレームバッファのピクセルデータを指していなければ
						いけません。KAMUIテクスチャデータは指定不可能です。
	IN	nWidth,nHeight	読み出したフレームバッファのサイズを指定します。
	IN	nBpp			読み出したフレームバッファのピクセルフォーマットを指定します。
						下記の中のいずれかを指定します。
							KM_DSPBPP_RGB565
							KM_DSPBPP_RGB555
							KM_DSPBPP_ARGB4444
							KM_DSPBPP_ARGB1555

Result:
	KMSTATUS_SUCCESS					読み込み成功

--*/

KMSTATUS KMAPI
kmuConvertFBtoBMP(
		PKMDWORD		pOutputData,
		PKMDWORD		pInputData,
		KMINT32			nWidth,
		KMINT32			nHeight,
		KMBPPMODE		nBpp
		);


/*++
kmuCalculateKamuiWorkareaSize

proto type:

	KMSTATUS
	kmuCalculateKamuiWorkareaSize(
			IN OUT PKMWORKAREASIZE	pWorkareaSize
		);

Description:
	KMWORKAREASIZE構造体に指定された各種パラメータより、
	SystemConfigStruct の dwTextureStructNum, dwSmallVQStructNum メンバ
	の内容、及び pAddress メンバに指定するワークエリア領域のサイズ
	を求めます。

Arguments:
	IN OUT PKMWORKAREASIZE	pWorkareaSize
	入力パラメータ及び結果が保存される構造体です。

	dwNumberOfFameBuffes
	フレームバッファの数を指定します。例えば、ダブルバッファの場合は２を指定します。
	dwNumberOfNativeBuffers
	ネイティブコマンドバッファの数を指定します。例えば、ダブルバッファの場合は２を指定します。
	KMDWORD		dwNumberOfTextures
	一度に使用する、small VQ形式以外のテクスチャの総数を指定します。
	KMDWORD		dwNumberOf8x8SmallVQ
	一度に使用する、8x8 small VQ形式のテクスチャの総数を指定します。
	KMDWORD		dwNumberOf8x8SmallVQmm
	一度に使用する、8x8 small VQ mipmap 形式のテクスチャの総数を指定します。
	KMDWORD		dwNumberOf16x16SmallVQ
	一度に使用する、16x16 small VQ形式のテクスチャの総数を指定します。
	KMDWORD		dwNumberOf16x16SmallVQmm
	一度に使用する、16x16 small VQ mipmap 形式のテクスチャの総数を指定します。
	KMDWORD		dwNumberOf32x32SmallVQ
	一度に使用する、32x32 small VQ形式のテクスチャの総数を指定します。
	KMDWORD		dwNumberOf32x32SmallVQmm
	一度に使用する、32x32 small VQ mipmap 形式のテクスチャの総数を指定します。
	KMDWORD		dwNumberOf64x64SmallVQ
	一度に使用する、64x64 small VQ形式のテクスチャの総数を指定します。
	KMDWORD		dwNumberOf64x64SmallVQmm
	一度に使用する、64x64 small VQ mipmap 形式のテクスチャの総数を指定します。

	8x8 small VQ, 8x8 small VQ mipmap, 64x64 small VQ mipmapは現在のKamui
	では非対応です。これらのメンバには、常にゼロを指定してください。

Result:
	KMSTATUS_SUCCESS					成功

--*/

KMSTATUS KMAPI
kmuCalculateKamuiWorkareaSize(
		IN OUT PKMWORKAREASIZE	pWorkareaSize
		);

/*++
kmuCreateTextureSurfaceFromFixed

proto type:

	KMSTATUS
	kmuCreateTextureSurfaceFromFixed(
		IN OUT	PKMDWORD		*pFixedArea,
		OUT		PKMSURFACEDESC	pSurfaceDesc,
		IN		KMINT32			nWidth,
		IN		KMINT32			nHeight,
		IN		KMTEXTURETYPE	nTextureType
		);

Description:
	kmCreateFixedTextureAreaで確保した固定テクスチャ領域を複数に
	分割して使用する場合のサーフェスディスクリプタを生成します。

	*pFixedAreaに指定されたアドレスから、ここで指定された形式の
	テクスチャサーフェスを確保することを想定して、サーフェス
	ディスクリプタ構造体の内容をセットします。
	また、*pFixedAreaには、ここで指定されたテクスチャの領域サイズ
	が加算されます。

	この関数はあくまでサーフェスディスクリプタ構造体の内容をセット
	するだけです。固定領域の分割管理を行うわけではありません。
	固定領域の分割管理、残容量管理、アドレスのアライメント管理
	はユーザー側で行ってください。

	この関数は、"small VQ圧縮形式"、"small VQ圧縮形式Mipmapあり"
	には対応していません。これらのテクスチャを固定領域で使用した
	い場合には、サーフェスディスクリプタの生成もユーザー側で行っ
	てください。

Arguments:
	IN OUT	*pFixedArea
		kmCreateFixedTextureAreaで確保した固定テクスチャ領域の先頭
		アドレスを指定します。ここには、指定されたテクスチャを保存
		するのに必要な容量が加算されます。
	OUT	pSurfaceDesc(出力)
		KMSURFACEDESC型の構造体へのポインタです。この構造体には、
		神威によってSurface情報が返されます。 
	IN	nWidth, nHeight(入力)
		テクスチャの横サイズ、縦サイズを指定します。 
		MIPMAPを使用する場合にはトップレベルのテクスチャサイズを指定します。
		nWidth, nHeightに指定する値は,8, 16, 32, 64, 128, 256, 512, 1024の
		いずれかでなければなりません。 
	IN	nTextureType(入力)
		テクスチャの形式を指定します。
		"small VQ圧縮形式"、"small VQ圧縮形式Mipmapあり" を除く
		いずれかの形式のテクスチャサーフェスを指定することができます。
		kmCreateTextureSurfaceの説明をご覧ください。

Result:
	KMSTATUS_SUCCESS					成功
	KMSTATUS_INVALID_TEXTURE_TYPE		無効なテクスチャタイプ、サイズを指定した
	KMSTATUS_INVALID_ADDRESS			pFixedArea, pSurfaceDesc がNULLである。

--*/

KMSTATUS KMAPI
kmuCreateTextureSurfaceFromFixed(
	IN OUT	PKMDWORD		*pFixedArea,
	OUT		PKMSURFACEDESC	pSurfaceDesc,
	IN		KMINT32			nWidth,
	IN		KMINT32			nHeight,
	IN		KMTEXTURETYPE	nTextureType
	);

/*++
kmuGeneratePassTable

proto type:

	KMUPASSSTATUS
	kmuGeneratePassTable(
			IN	PKMVERTEXCONTEXT	pVertexContext,
			IN	KMUINT32			nNumContext,
			OUT	PPKMVERTEXCONTEXT	ppVertexContextTable,
			OUT	PKMUINT32			pPass
		);

Description:
	設定されたレンダリング指定(pVertexContext)をもとに、マルチパス(Trilinear)の各Passで
	必要なコンテキストを生成します。
	  pVertexContextにTrilinearの1Pass目のKMVERTEXCONTEXTを入力すると、その設定値より
	各Passで必要なKMVERTEXCONTEXTを生成します(Opaque:2Pass,Trans:3Pass)
	  TransPolygonのTrilinearの場合に3Pass目のBlendingModeの設定は任意に設定可能ですが、
	本関数を使用した場合には、下記の設定になります。
	(TransPolygonを使用した場合の3Pass目)
		SRCBlendingMode	:: KM_SRCALPHA
		DSTBlendingMode	:: KM_INVSRCALPHA
	ppVertexContextTableにNULLが指定された場合はpPassへ必要なパス数のみが返却します。

Arguments:
	IN		pVertexContext			レンダリング条件を指定するKMVERTEXCONTEXTへのポインタ
									を設定します。
	IN		nNumContext				準備したppVertexContextTableのエントリ数(パス数)を設定します。
									これが実際に必要なパス数より小さい場合は、
									KMU_PASS_ERROR_VERTEXCONTEXT_PASSが返され、
									pPassへ必要なパス数のみが返されて終了します。
	OUT		ppVertexContextTable	生成されたマルチパス用KMVERTEXCONTEXTを受け取るための、
									KMVERTEXCONTEXTへのポインタの配列へのポインタを設定します。
									ここにNULLが指定された場合はpPassへ必要なパス数のみを返します。
	OUT		pPass					設定されたレンダリング指定で必要となるマルチパス数を返します。

Result:
	KMU_PASS_OK							設定成功
	KMU_PASS_ERROR_NOT_IMPLEMENTED		現在のシステムでは、本関数は対応してません
	KMU_PASS_ERROR_VERTEXCONTEXT		pVertexContextが不正(NULL)です
	KMU_PASS_ERROR_VERTEXCONTEXT_PASS	指定したパス数(nNumContext)では不足しています
--*/

KMUPASSSTATUS KMAPI
kmuGeneratePassTable(
		IN	PKMVERTEXCONTEXT	pVertexContext,
		IN	KMUINT32			nNumContext,
		OUT	PPKMVERTEXCONTEXT	ppVertexContextTable,
		OUT	PKMUINT32			pPass
	);


/*++
kmuCheckPassTable

proto type:

	KMUPASSSTATUS
	kmuCheckPassTable(
			IN	PPKMVERTEXCONTEXT	ppVertexContextTable,
			IN	KMUINT32			nNumContext,
			OUT	PKMUINT32			pPass
		);

Description:
	指定されたKMVERTEXCONTEXTテーブルの各コンテキストの内容が正しいか否かをチェックします。

Arguments:
	IN		ppVertexContextTable	準備したKMVERTEXCONTEXTへのポインタの配列へのポインタを設定します。
	IN		nNumContext				準備したppVertexContextTableのエントリ数を設定します。
	OUT		pPass					エラーが見つかった場合には、間違っているKMVERTEXCONTENTの
									エントリ番号をセットします。

Result:
	KMU_PASS_OK								設定成功
	KMU_PASS_ERROR_VERTEXCONTEXT			KMVERTEXCONTEXTが不正(NULL)です
	KMU_PASS_ERROR_VERTEXCONTEXT_PASS		nNumContextが不正(1未満)です
	KMU_PASS_ERROR_PARAMTYPE				KMVERTEXCONTEXTの ParamTypeが不正です
	KMU_PASS_ERROR_LISTTYPE					KMVERTEXCONTEXTの ListTypeが不正です
	KMU_PASS_ERROR_MIPMAP_D_ADJUST			KMVERTEXCONTEXTの MipMapAdjustが不正です
	KMU_PASS_ERROR_FOGMODE					KMVERTEXCONTEXTの FogModeが不正です
	KMU_PASS_ERROR_FILTERMODE				KMVERTEXCONTEXTの FilterModeが不正です
	KMU_PASS_ERROR_TEXTURESHADINGMODE		KMVERTEXCONTEXTの TextureShadingModeが不正です
	KMU_PASS_ERROR_COLORTYPE				KMVERTEXCONTEXTの ColorTypeが不正です
	KMU_PASS_ERROR_SHADINGMODE				KMVERTEXCONTEXTの ShadingModeが不正です
	KMU_PASS_ERROR_USERCLIPMODE				KMVERTEXCONTEXTの UserClipModeが不正です
	KMU_PASS_ERROR_TRILINEAR_SETTING		Trilinear設定の組み合わせが不正です
											 KMVERTEXCONTEXTの ListType/ShadingMode/FilterMode
											SRCBlendingMode/DSTBlendingMode/bSRCSel/bSRCSel
											のいずれかが、Trilinearで使用できない設定です。
	KMU_PASS_ERROR_SPRITE_SETTING			Sprite設定の組み合わせが不正です
											 KMVERTEXCONTEXTの ShadingMode/ColorType/UVFormat
											のいずれかが、Spriteで使用できない設定です。
	KMU_PASS_ERROR_BLENDINGMODE_SETTING		BlendingMode設定の組み合わせが不正です
											 OpaquePolygon使用時(ListType:KM_OPAQUE_POLYGON)に
											KMVERTEXCONTEXTの SRCBlendingMode/DSTBlendingModeで
											設定不可の組み合わせが指定された場合です
											(SRCBlendingMode:KM_ONE , DSTBlendingMode:KM_ZERO以外)
	KMU_PASS_ERROR_MODIFIER_SETTING			Modifier設定の組み合わせが不正です
											 Modifier使用時(ParamType:KM_MODIFIERVOLUME)に
											KMVERTEXCONTEXTの ModifierInstructionが不正な場合です。

--*/

KMUPASSSTATUS KMAPI
kmuCheckPassTable(
		IN	PPKMVERTEXCONTEXT	ppVertexContextTable,
		IN	KMUINT32			nNumContext,
		OUT	PKMUINT32			pPass
	);


/*++
kmuConvertStripContext

proto type:

	KMSTATUS
	kmuConvertStripContext(
		OUT	PKMVOID				pStripContext,
		IN	PKMVERTEXCONTEXT	pVertexContext1,
		IN	PKMVERTEXCONTEXT	pVertexContext2
	)

Description:
	従来互換のKMVERTEXCONTEXT構造体から、KAMUI2のKMSTRIPCONTEXT(KMTWOVOLUMESTRIPCONTEXT)
	への内部設定値のコンバートをおこないます。

Arguments:
	OUT		pStripContext			KMSTRIPCONTEXTまたは、KMTWOVOLUMESTRIPCONTEXT構造体へのポインタ
									を指定します。Param2を使用する場合は、KMTWOVOLUMESTRIPCONTEXTへ
									のポインタを使用してください。
	IN		pVertexContext1			Param1で使用するKMVERTEXCONTEXT構造体へのポインタを指定します。
	IN		pVertexContext2			Param2で使用するKMVERTEXCONTEXT構造体へのポインタを指定します。
									Param2を使用しない場合は、NULLを指定してください。

Result:
	KMSTATUS_SUCCESS				設定成功
	KMSTATUS_INVALID_ADDRESS		引数が不正(NULL)です。
	KMSTATUS_INVALID_SETTING		pStripContextのサイズ設定が不正です。
--*/

KMSTATUS KMAPI
kmuConvertStripContext(
		OUT	PKMVOID				pStripContext,
		IN	PKMVERTEXCONTEXT	pVertexContext1,
		IN	PKMVERTEXCONTEXT	pVertexContext2
	);

#ifdef __cplusplus
}
#endif 

#endif
