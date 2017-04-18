/*++

  COPYRIGHT        (C) NEC        Corporation 1997 - 1999

  All rights reserved by NEC Corporation. This program must be
  used solely for the purpose for which it was furnished by NEC
  Corporation. No part of this program may be reproduced or
  disclosed to others, in any form, without the prior written
  permission of NEC Corporation.
  Use of copyright notice does not evidence publication of this
  program.

  Author     :		T.Kamei(NEC Software,Ltd.)
  Module Name:		km2vtxapi.h

  Abstract:
	KAMUI = Kamui is abstruction model that is ultimate interface for PowerVR.
	'km2vtxapi.h' define the function which manage vertex strip ,generate strip head ,
	process vertex context and is related with vertex strip.

  Environment:
	ANSI C Compiler.

  Notes:

  Revision History:

--*/

#if !defined(__kamui2_vertex_api_h__)
#define __kamui2_vertex_api_h__
/*++
kmGenerateStripHead

proto type:
	KMSTATUS KMAPI
	kmGenerateStripHead(
	        OUT PKMSTRIPHEAD        pStripHead,
	        IN  PKMSTRIPCONTEXT     pStripContext,
			IN  KMVERTEXTYPE		nVertexType
		);

Description:
	pStripContext の内容を元に、nVertexType で指定された頂点タイプにあう、
	KMSTRIPHEAD を作成し pStripHead が示す領域に書き込みます。

	実体は、 kmGenerateStripHeadxx() へのディスパッチャです。
	使用する頂点タイプが決まっている場合にはkmGenerateStripHeadxx()を
	使用したほうが若干高速です(xx : 00 - 17 の任意の数値)。

Arguments:
	OUT pStripHead		生成後の KMSTRIPHEADを書き込む領域を示す
						ポインタです。

	IN  pStripContext	StripHead を生成するための元になる情報を格納した
						KMSTRIPCONTEXT 構造体へのポインタを指定します。

	IN  nVertexType		使用する頂点の種類によって、pStripHead に書き込む内容が異なるため、
						KMSTRIPCONTEXT を使用して生成する KMSTRIPHEADの後に続く
						頂点のタイプを指定します。

Result:
	KMSTATUS_SUCCESS		成功

--*/
KMSTATUS KMAPI
kmGenerateStripHead(
        OUT PKMSTRIPHEAD        pStripHead,
        IN  PKMSTRIPCONTEXT     pStripContext,
		IN  KMVERTEXTYPE		nVertexType
	);

/*++
kmGenerateStripHeadxx

proto type:
	KMSTATUS KMAPI
	kmGenerateStripHeadxx(
	        OUT PKMSTRIPHEAD        pStripHead,
	        IN  PKMSTRIPCONTEXT     pStripContext
		);

Description:
	xx は 00 - 17 の任意の数値で頂点タイプを示します。
	生成する頂点タイプに特化した KMSTRIPHEAD 生成関数群です。

	各関数が pStripContext の内容を元に xx が示す 頂点タイプにあった
	KMSTRIPHEAD を作成し pStripHead が示す領域に書き込みます。

Arguments:
	OUT pStripHead		生成後の KMSTRIPHEADを書き込む領域を示す
						ポインタです。

	IN  pStripContext	StripHead を生成するための元になる情報を格納した
						KMSTRIPCONTEXT 構造体へのポインタを指定します。

Result:
	KMSTATUS_SUCCESS		成功

--*/

KMSTATUS KMAPI
kmGenerateStripHead00(
        OUT PKMSTRIPHEAD        pStripHead,
        IN  PKMSTRIPCONTEXT     pStripContext
	);

KMSTATUS KMAPI
kmGenerateStripHead01(
        OUT PKMSTRIPHEAD        pStripHead,
        IN  PKMSTRIPCONTEXT     pStripContext
	);

KMSTATUS KMAPI
kmGenerateStripHead02(
        OUT PKMSTRIPHEAD        pStripHead,
        IN  PKMSTRIPCONTEXT     pStripContext
	);

KMSTATUS KMAPI
kmGenerateStripHead03(
        OUT PKMSTRIPHEAD        pStripHead,
        IN  PKMSTRIPCONTEXT     pStripContext
	);

KMSTATUS KMAPI
kmGenerateStripHead04(
        OUT PKMSTRIPHEAD        pStripHead,
        IN  PKMSTRIPCONTEXT     pStripContext
	);

KMSTATUS KMAPI
kmGenerateStripHead05(
        OUT PKMSTRIPHEAD        pStripHead,
        IN  PKMSTRIPCONTEXT     pStripContext
	);

KMSTATUS KMAPI
kmGenerateStripHead06(
        OUT PKMSTRIPHEAD        pStripHead,
        IN  PKMSTRIPCONTEXT     pStripContext
	);

KMSTATUS KMAPI
kmGenerateStripHead07(
        OUT PKMSTRIPHEAD        pStripHead,
        IN  PKMSTRIPCONTEXT     pStripContext
	);

KMSTATUS KMAPI
kmGenerateStripHead08(
        OUT PKMSTRIPHEAD        pStripHead,
        IN  PKMSTRIPCONTEXT     pStripContext
	);

KMSTATUS KMAPI
kmGenerateStripHead09(
        OUT PKMSTRIPHEAD        pStripHead,
        IN  PKMSTRIPCONTEXT     pStripContext
	);

KMSTATUS KMAPI
kmGenerateStripHead10(
        OUT PKMSTRIPHEAD        pStripHead,
        IN  PKMSTRIPCONTEXT     pStripContext
	);

KMSTATUS KMAPI
kmGenerateStripHead11(
        OUT PKMSTRIPHEAD        pStripHead,
        IN  PKMSTRIPCONTEXT     pStripContext
	);

KMSTATUS KMAPI
kmGenerateStripHead12(
        OUT PKMSTRIPHEAD        pStripHead,
        IN  PKMSTRIPCONTEXT     pStripContext
	);

KMSTATUS KMAPI
kmGenerateStripHead13(
        OUT PKMSTRIPHEAD        pStripHead,
        IN  PKMSTRIPCONTEXT     pStripContext
	);

KMSTATUS KMAPI
kmGenerateStripHead14(
        OUT PKMSTRIPHEAD        pStripHead,
        IN  PKMSTRIPCONTEXT     pStripContext
	);

KMSTATUS KMAPI
kmGenerateStripHead15(
        OUT PKMSTRIPHEAD        pStripHead,
        IN  PKMSTRIPCONTEXT     pStripContext
	);

KMSTATUS KMAPI
kmGenerateStripHead16(
        OUT PKMSTRIPHEAD        pStripHead,
        IN  PKMSTRIPCONTEXT     pStripContext
	);

KMSTATUS KMAPI
kmGenerateStripHead17(
        OUT PKMSTRIPHEAD        pStripHead,
        IN  PKMSTRIPCONTEXT     pStripContext
	);

/*++
kmInitStripContext

proto type:
	KMSTATUS KMAPI
	kmInitStripContext(
			IN  KMDWORD		dwIndex,
			OUT PKMVOID		pStripContext
		);

Description:
	典型的な KMSTRIPCONTEXT を生成し、pStripContextが示す領域へ
	書き込みます。

Arguments:
	IN  dwIndex			Index です。
	OUT pStripContext	受け取る領域へのポインタです。

Result:
	KMSTATUS_SUCCESS		成功

--*/
KMSTATUS KMAPI
kmInitStripContext(
		IN  KMDWORD		dwIndex,
		OUT PKMVOID		pStripContext
	);

/*++
kmRegisterStripContext

proto type:
	KMSTATUS KMAPI
	kmRegisterStripContext(
			IN  KMDWORD				dwIndex,
			IN  PKMSTRIPCONTEXT     pStripContext
		);

Description:
	よく使用するお気に入りの STRIPCONTEXT 構造体を
	後で使用するためにシステムに一旦登録しておく関数です。

Arguments:
	IN  dwIndex				書き換える領域の index
	IN  pStripContext		

Result:
	KMSTATUS_SUCCESS		成功

--*/
KMSTATUS KMAPI
kmRegisterStripContext(
		IN  KMDWORD				dwIndex,
		IN  PKMSTRIPCONTEXT     pStripContext
	);

/*++
kmStartStrip

proto type:
	KMSTATUS KMAPI
	kmStartStrip(
			IN  PKMVERTEXBUFFDESC   pVertexBuffDesc,
			IN  PKMSTRIPHEAD        pStripHead
		);

Description:

Arguments:
	IN  pVertexBuffDesc		データを登録する頂点データリストの情報を示す、
							PKMVERTEXBUFFDESC型の、Vertex Buffer Descriptorへの
							ポインタです。

	IN  pStripHead			頂点リストの先頭になる KMSTRIPHEAD 構造体への
							ポインタです。

Result:
	KMSTATUS_SUCCESS		成功

--*/
#if !defined(_KM_USE_VERTEX_MACRO_)
KMSTATUS KMAPI
kmStartStrip(
		IN  PKMVERTEXBUFFDESC   pVertexBuffDesc,
		IN  PKMSTRIPHEAD        pStripHead
	);
#endif


/*++
kmEndStrip

proto type:

Description:

Arguments:
	IN  pVertexBuffDesc		データを登録する頂点データリストの情報を示す、
							PKMVERTEXBUFFDESC型の、Vertex Buffer Descriptorへの
							ポインタです。

Result:
	KMSTATUS_SUCCESS		成功

--*/
KMSTATUS KMAPI
kmEndStrip(
		IN  PKMVERTEXBUFFDESC   pVertexBuffDesc
	);

/*++
kmSetVertex

proto type:
	KMSTATUS
	kmSetVertex(
			PKMVERTEXBUFFDESC pBufferDesc,
			PVOID pVertex,
			KMVERTEXTYPE VertexType,
			KMINT32 StructSize
		);

Description:
	pVertexが指す頂点データを、システムに登録済みのレンダリンパラメータの ListType で指定した頂点データリストへ書き込みます。
	ストリップの最後となる頂点データのParameter Control Word がKM_VERTEXPARAM_ENDOFSTRIP でなかったときの動作は保証しません。

	注意：	ここで書き込む頂点パラメータの形式と、この前のkmSetVertexRenderStateで設定したグローバルパラメータの形式の
			組み合わせが正しくない場合の動作は保証しません。

	<本関数は高速性を要求されるためInline展開されるマクロとして定義されます。>

	マクロを使用する場合には、以下のように設定してください。

		#define _KM_USE_VERTEX_MACRO_
		#include <kamui.h>
		#include <kamuix.h> 

Arguments:
	IN	pBufferDesc		PKMVERTEXBUFFDESC型の、Vertex Buffer Descriptorへのポインタです。
	IN	pVertex			頂点データ構造体へのポインタです。
	IN	VertexType		頂点データのデータタイプを示します。下記のいずれかを指定します。
						KM_VERTEXTYPE_00			// 頂点データ Type 0
						KM_VERTEXTYPE_01			// 頂点データ Type 1
						KM_VERTEXTYPE_02			// 頂点データ Type 2
						KM_VERTEXTYPE_03			// 頂点データ Type 3
						KM_VERTEXTYPE_04			// 頂点データ Type 4
						KM_VERTEXTYPE_05			// 頂点データ Type 5
						KM_VERTEXTYPE_06			// 頂点データ Type 6
						KM_VERTEXTYPE_07			// 頂点データ Type 7
						KM_VERTEXTYPE_08			// 頂点データ Type 8
						KM_VERTEXTYPE_09			// 頂点データ Type 9
						KM_VERTEXTYPE_10			// 頂点データ Type 10
						KM_VERTEXTYPE_11			// 頂点データ Type 11
						KM_VERTEXTYPE_12			// 頂点データ Type 12
						KM_VERTEXTYPE_13			// 頂点データ Type 13
						KM_VERTEXTYPE_14			// 頂点データ Type 14
						KM_VERTEXTYPE_15			// 頂点データ Type 15
						KM_VERTEXTYPE_16			// 頂点データ Type 16
						KM_VERTEXTYPE_17			// 頂点データ Type 17

	IN	StructSize		頂点データのデータタイプサイズを示します。頂点データに使用するタイプに合わせて、
						sizeof(KMVERTEX_01)の様に指定してください。

Result:
	KMSTATUS_SUCCESS			頂点データ書き込み成功
	KMSTATUS_NOT_ENOUGH_MEMORY	頂点データリストの容量が足りない

--*/
#if !defined(_KM_USE_VERTEX_MACRO_)
KMSTATUS KMAPI
kmSetVertex(
		IN	PKMVERTEXBUFFDESC pBufferDesc,
		IN	PVOID pVertex,
		IN	KMVERTEXTYPE VertexType,
		IN	KMINT32 StructSize
	);
#endif

/*++
kmSetUserClipping

proto type:
	KMSTATUS KMAPI
	kmSetUserClipping(
			IN  PKMVERTEXBUFFDESC   pVertexBuffDesc,
			IN  KMUSERCLIPMODE      nPrevUserClipMode,
			IN  KMLISTTYPE          nListType,
			IN  PKMRECT             pRect
		);

Description:
	IN  pVertexBuffDesc		データを登録する頂点データリストの情報を示す、
							PKMVERTEXBUFFDESC型の、Vertex Buffer Descriptorへの
							ポインタです。
	IN  nPrevUserClipMode	
	IN  nListType			
	IN  pRect				

Arguments:

Result:
	KMSTATUS_SUCCESS		成功
--*/
KMSTATUS KMAPI
kmSetUserClipping(
		IN  PKMVERTEXBUFFDESC   pVertexBuffDesc,
		IN  KMUSERCLIPMODE      nPrevUserClipMode,
		IN  KMLISTTYPE          nListType,
		IN  PKMRECT             pRect
	);

/*++
kmSetStripHead

proto type:
	KMSTATUS KMAPI
	kmSetStripHead(
			IN  PKMVERTEXBUFFDESC   pVertexBuffDesc,
			IN  PKMSTRIPHEAD        pStripHead
		);

Description:

Arguments:
	IN  pVertexBuffDesc		データを登録する頂点データリストの情報を示す、
							PKMVERTEXBUFFDESC型の、Vertex Buffer Descriptorへの
							ポインタです。
	IN  pStripHead

Result:
	KMSTATUS_SUCCESS		成功

--*/
KMSTATUS KMAPI
kmSetStripHead(
		IN  PKMVERTEXBUFFDESC   pVertexBuffDesc,
		IN  PKMSTRIPHEAD        pStripHead
	);

/*++
kmChangeStripXxxx

proto type:
	KMSTATUS KMAPI
	kmChangeStripXxxx(
			IN OUT	PKMSTRIPHEAD	pStripHead,
			IN		KMXXXXXX		xXxx
		);

	KMSTATUS KMAPI
	kmChangeStripXxxx(
			IN OUT	PKMSTRIPHEAD	pStripHead,
			IN		KMINT32			nParam,
			IN		KMBLENDINGMODE	xXxxx
		);

Description:
	kmGenerateStripHead 等を使用して生成した、KMSTRIPHEAD 構造体の内容を
	一部書き換える関数群です。

Arguments:
	IN OUT	pStripHead	書き換える対象となる KMSTRIPHEAD 構造体へのポインタ
	IN		nParam		2 volume に関係するパラメータを書き換える場合には、
						どちらのパラメータを書き換えるのかを明示する必要がある。
	IN		xXxxx		変更するパラメータ

Result:
	KMSTATUS_SUCCESS		成功

--*/
KMSTATUS KMAPI
kmChangeStripListType(
		IN OUT	PKMSTRIPHEAD	pStripHead,
		IN		KMLISTTYPE		nListType
	);
KMSTATUS KMAPI
kmChangeStripUserClipMode(
		IN OUT	PKMSTRIPHEAD	pStripHead,
		IN		KMUSERCLIPMODE	nUserClipMode
	);
KMSTATUS KMAPI
kmChangeStripShadowMode(
		IN OUT	PKMSTRIPHEAD	pStripHead,
		IN		KMSHADOWMODE	nShadowMode
	);
KMSTATUS KMAPI
kmChangeStripIntensityMode(
		IN OUT	PKMSTRIPHEAD	pStripHead,
		IN		KMCOLORTYPE		nIntensityMode
	);
KMSTATUS KMAPI
kmChangeStripOffset(
		IN OUT	PKMSTRIPHEAD	pStripHead,
		IN		KMBOOLEAN		bOffset
	);
KMSTATUS KMAPI
kmChangeStripGouraud(
		IN OUT	PKMSTRIPHEAD	pStripHead,
		IN		KMBOOLEAN		bGouraud
	);
KMSTATUS KMAPI
kmChangeStripDepthCompareMode(
		IN OUT	PKMSTRIPHEAD	pStripHead,
		IN		KMDEPTHMODE		nDepthCompareMode
	);
KMSTATUS KMAPI
kmChangeStripModifierInstruction(
		IN OUT	PKMSTRIPHEAD	pStripHead,
		IN		KMDWORD			dwModifierInstruction
	);
KMSTATUS KMAPI
kmChangeStripCullingMode(
		IN OUT	PKMSTRIPHEAD	pStripHead,
		IN		KMCULLINGMODE	nCullingMode
	);
KMSTATUS KMAPI
kmChangeStripZWriteDisable(
		IN OUT	PKMSTRIPHEAD	pStripHead,
		IN		KMBOOLEAN		bZWriteDisable
	);
KMSTATUS KMAPI
kmChangeStripDCalcControl(
		IN OUT	PKMSTRIPHEAD	pStripHead,
		IN		KMBOOLEAN		bDCalcControl
	);
KMSTATUS KMAPI
kmChangeStripBlendingMode(
		IN OUT	PKMSTRIPHEAD	pStripHead,
		IN		KMINT32			nParam,
		IN		KMBLENDINGMODE	nSRCBlendingMode,
		IN		KMBLENDINGMODE	nDSTBlendingMode
	);
KMSTATUS KMAPI
kmChangeStripSRCSelect(
		IN OUT	PKMSTRIPHEAD	pStripHead,
		IN		KMINT32			nParam,
		IN		KMBOOLEAN		bSRCSelect
	);
KMSTATUS KMAPI
kmChangeStripDSTSelect(
		IN OUT	PKMSTRIPHEAD	pStripHead,
		IN		KMINT32			nParam,
		IN		KMBOOLEAN		bDSTSelect
	);
KMSTATUS KMAPI
kmChangeStripFogMode(
		IN OUT	PKMSTRIPHEAD	pStripHead,
		IN		KMINT32			nParam,
		IN		KMFOGMODE		nFogMode
	);
KMSTATUS KMAPI
kmChangeStripColorClamp(
		IN OUT	PKMSTRIPHEAD	pStripHead,
		IN		KMINT32			nParam,
		IN		KMBOOLEAN		bColorClamp
	);
KMSTATUS KMAPI
kmChangeStripUseAlpha(
		IN OUT	PKMSTRIPHEAD	pStripHead,
		IN		KMINT32			nParam,
		IN		KMBOOLEAN		bUseAlpha
	);
KMSTATUS KMAPI
kmChangeStripIgnoreTextureAlpha(
		IN OUT	PKMSTRIPHEAD	pStripHead,
		IN		KMINT32			nParam,
		IN		KMBOOLEAN		bIgnoreTextureAlpha
	);
KMSTATUS KMAPI
kmChangeStripFlipUV(
		IN OUT	PKMSTRIPHEAD	pStripHead,
		IN		KMINT32			nParam,
		IN		KMFLIPMODE		nFlipUV
	);
KMSTATUS KMAPI
kmChangeStripClampUV(
		IN OUT	PKMSTRIPHEAD	pStripHead,
		IN		KMINT32			nParam,
		IN		KMCLAMPMODE		nClampUV
	);
KMSTATUS KMAPI
kmChangeStripFilterMode(
		IN OUT	PKMSTRIPHEAD	pStripHead,
		IN		KMINT32			nParam,
		IN		KMFILTERMODE	nFilterMode
	);
KMSTATUS KMAPI
kmChangeStripSuperSampleMode(
		IN OUT	PKMSTRIPHEAD	pStripHead,
		IN		KMINT32			nParam,
		IN		KMBOOLEAN		bSuperSampleMode
	);
KMSTATUS KMAPI
kmChangeStripMipmapAdjust(
		IN OUT	PKMSTRIPHEAD	pStripHead,
		IN		KMINT32			nParam,
		IN		KMDWORD			dwMipmapAdjust
	);
KMSTATUS KMAPI
kmChangeStripTextureShadingMode(
		IN OUT	PKMSTRIPHEAD			pStripHead,
		IN		KMINT32					nParam,
		IN		KMTEXTURESHADINGMODE	nTextureShadingMode
	);
KMSTATUS KMAPI
kmChangeStripPaletteBank(
		IN OUT	PKMSTRIPHEAD	pStripHead,
		IN		KMINT32			nParam,
		IN		KMDWORD			dwPaletteBank
	);
KMSTATUS KMAPI
kmChangeStripTextureSurface(
		IN OUT	PKMSTRIPHEAD	pStripHead,
        IN      KMINT32         nParam,
		IN		PKMSURFACEDESC	pTextureSurfaceDesc
	);
KMSTATUS KMAPI
kmChangeStripTextureAddress(
		IN OUT	PKMSTRIPHEAD	pStripHead,
		IN		KMINT32			nParam,
		IN		PKMSURFACEDESC	pTextureSurfaceDesc
	);
KMSTATUS KMAPI
kmChangeStripFaceColor(
		IN OUT	PKMSTRIPHEAD	pStripHead,
		IN		KMINT32			nParam,
		IN		PKMFLOATCOLOR	pFaceColor
	);
KMSTATUS KMAPI
kmChangeStripFaceOffsetColor(
		IN OUT	PKMSTRIPHEAD	pStripHead,
		IN		PKMFLOATCOLOR	pFaceOffsetColor
	);
KMSTATUS KMAPI
kmChangeStripSpriteBaseColor(
		IN OUT	PKMSTRIPHEAD	pStripHead,
		IN		KMPACKEDARGB	dwBaseColor
	);
KMSTATUS KMAPI
kmChangeStripSpriteOffsetColor(
		IN OUT	PKMSTRIPHEAD	pStripHead,
		IN		KMPACKEDARGB	dwOffsetColor
	);

/*++
kmChangeContextXxxxx

proto type:

	KMSTATUS KMAPI
	kmChangeContextXxxx(
			IN OUT	PKMVERTEXBUFFDESC	pVertexBuffDesc,
			IN		KMXXXX				xXxxxx
		);

	KMSTATUS KMAPI
	kmChangeContextXxxxx(
			IN OUT	PKMVERTEXBUFFDESC	pVertexBuffDesc,
			IN		KMINT32				nParam,
			IN		KMXXXX				xXxxxx
		);

Description:
	kmSetStripHead を使用して、一時システムに登録した、
	KMSTRIPHEAD 構造体を書き換える関数群です。

Arguments:
	IN OUT	pVertexBuffDesc		データを変更する頂点データリストの情報を示す、
								PKMVERTEXBUFFDESC型の、Vertex Buffer Descriptorへの
								ポインタです。

	IN		nParam				2ボリュームに関係する関数では必要です。
								0 / 1 を入れてください。

	IN		xXxxxx				変更するパラメータ

Result:
	KMSTATUS_SUCCESS		成功

--*/
KMSTATUS KMAPI
kmChangeContextListType(
		IN OUT	PKMVERTEXBUFFDESC	pVertexBuffDesc,
		IN		KMLISTTYPE			nListType
	);

KMSTATUS KMAPI
kmChangeContextUserClipMode(
		IN OUT	PKMVERTEXBUFFDESC	pVertexBuffDesc,
		IN		KMUSERCLIPMODE		nUserClipMode
	);

KMSTATUS KMAPI
kmChangeContextShadowMode(
		IN OUT	PKMVERTEXBUFFDESC	pVertexBuffDesc,
		IN		KMSHADOWMODE		nShadowMode
	);

KMSTATUS KMAPI
kmChangeContextIntensityMode(
		IN OUT	PKMVERTEXBUFFDESC	pVertexBuffDesc,
		IN		KMCOLORTYPE			nIntensityMode
	);

KMSTATUS KMAPI
kmChangeContextOffset(
		IN OUT	PKMVERTEXBUFFDESC	pVertexBuffDesc,
		IN		KMBOOLEAN			bOffset
	);

KMSTATUS KMAPI
kmChangeContextGouraud(
		IN OUT	PKMVERTEXBUFFDESC	pVertexBuffDesc,
		IN		KMBOOLEAN			bGouraud
	);

KMSTATUS KMAPI
kmChangeContextDepthCompareMode(
		IN OUT	PKMVERTEXBUFFDESC	pVertexBuffDesc,
		IN		KMDEPTHMODE			nDepthCompareMode
	);

KMSTATUS KMAPI
kmChangeContextModifierInstruction(
		IN OUT	PKMVERTEXBUFFDESC	pVertexBuffDesc,
		IN		KMDWORD				dwModifierInstruction
	);

KMSTATUS KMAPI
kmChangeContextCullingMode(
		IN OUT	PKMVERTEXBUFFDESC	pVertexBuffDesc,
		IN		KMCULLINGMODE		nCullingMode
	);

KMSTATUS KMAPI
kmChangeContextZWriteDisable(
		IN OUT	PKMVERTEXBUFFDESC	pVertexBuffDesc,
		IN		KMBOOLEAN			bZWriteDisable
	);

KMSTATUS KMAPI
kmChangeContextDCalcControl(
		IN OUT	PKMVERTEXBUFFDESC	pVertexBuffDesc,
		IN		KMBOOLEAN			bDCalcControl
	);

KMSTATUS KMAPI
kmChangeContextBlendingMode(
		IN OUT	PKMVERTEXBUFFDESC	pVertexBuffDesc,
		IN		KMINT32				nParam,
		IN		KMBLENDINGMODE		nSRCBlendingMode,
		IN		KMBLENDINGMODE		nDSTBlendingMode
	);

KMSTATUS KMAPI
kmChangeContextSRCSelect(
		IN OUT	PKMVERTEXBUFFDESC	pVertexBuffDesc,
		IN		KMINT32				nParam,
		IN		KMBOOLEAN			bSRCSelect
	);

KMSTATUS KMAPI
kmChangeContextDSTSelect(
		IN OUT	PKMVERTEXBUFFDESC	pVertexBuffDesc,
		IN		KMINT32				nParam,
		IN		KMBOOLEAN			bDSTSelect
	);

KMSTATUS KMAPI
kmChangeContextFogMode(
		IN OUT	PKMVERTEXBUFFDESC	pVertexBuffDesc,
		IN		KMINT32				nParam,
		IN		KMFOGMODE			nFogMode
	);

KMSTATUS KMAPI
kmChangeContextColorClamp(
		IN OUT	PKMVERTEXBUFFDESC	pVertexBuffDesc,
		IN		KMINT32				nParam,
		IN		KMBOOLEAN			bColorClamp
	);

KMSTATUS KMAPI
kmChangeContextUseAlpha(
		IN OUT	PKMVERTEXBUFFDESC	pVertexBuffDesc,
		IN		KMINT32				nParam,
		IN		KMBOOLEAN			bUseAlpha
	);

KMSTATUS KMAPI
kmChangeContextIgnoreTextureAlpha(
		IN OUT	PKMVERTEXBUFFDESC	pVertexBuffDesc,
		IN		KMINT32				nParam,
		IN		KMBOOLEAN			bIgnoreTextureAlpha
	);

KMSTATUS KMAPI
kmChangeContextFlipUV(
		IN OUT	PKMVERTEXBUFFDESC	pVertexBuffDesc,
		IN		KMINT32				nParam,
		IN		KMFLIPMODE			nFlipUV
	);

KMSTATUS KMAPI
kmChangeContextClampUV(
		IN OUT	PKMVERTEXBUFFDESC	pVertexBuffDesc,
		IN		KMINT32				nParam,
		IN		KMCLAMPMODE			nClampUV
	);

KMSTATUS KMAPI
kmChangeContextFilterMode(
		IN OUT	PKMVERTEXBUFFDESC	pVertexBuffDesc,
		IN		KMINT32				nParam,
		IN		KMFILTERMODE		nFilterMode
	);

KMSTATUS KMAPI
kmChangeContextSuperSampleMode(
		IN OUT	PKMVERTEXBUFFDESC	pVertexBuffDesc,
		IN		KMINT32				nParam,
		IN		KMBOOLEAN			bSuperSampleMode
	);

KMSTATUS KMAPI
kmChangeContextMipmapAdjust(
		IN OUT	PKMVERTEXBUFFDESC	pVertexBuffDesc,
		IN		KMINT32				nParam,
		IN		KMDWORD				dwMipmapAdjust
	);

KMSTATUS KMAPI
kmChangeContextTextureShadingMode(
		IN OUT	PKMVERTEXBUFFDESC		pVertexBuffDesc,
		IN		KMINT32					nParam,
		IN		KMTEXTURESHADINGMODE	nTextureShadingMode
	);

KMSTATUS KMAPI
kmChangeContextPaletteBank(
		IN OUT	PKMVERTEXBUFFDESC	pVertexBuffDesc,
		IN		KMINT32				nParam,
		IN		KMDWORD				dwPaletteBank
	);

KMSTATUS KMAPI
kmChangeContextTextureSurface(
		IN OUT	PKMVERTEXBUFFDESC	pVertexBuffDesc,
        IN      KMINT32				nParam,
		IN		PKMSURFACEDESC		pTextureSurfaceDesc
	);

KMSTATUS KMAPI
kmChangeContextTextureAddress(
		IN OUT	PKMVERTEXBUFFDESC	pVertexBuffDesc,
		IN		KMINT32				nParam,
		IN		PKMSURFACEDESC		pTextureSurfaceDesc
	);

KMSTATUS KMAPI
kmChangeContextFaceColor(
		IN OUT	PKMVERTEXBUFFDESC	pVertexBuffDesc,
		IN		KMINT32				nParam,
		IN		PKMFLOATCOLOR		pFaceColor
	);

KMSTATUS KMAPI
kmChangeContextFaceOffsetColor(
		IN OUT	PKMVERTEXBUFFDESC	pVertexBuffDesc,
		IN		PKMFLOATCOLOR		pFaceOffsetColor
	);

KMSTATUS KMAPI
kmChangeContextSpriteBaseColor(
		IN OUT	PKMVERTEXBUFFDESC	pVertexBuffDesc,
		IN		KMPACKEDARGB		dwBaseColor
	);

KMSTATUS KMAPI
kmChangeContextSpriteOffsetColor(
		IN OUT	PKMVERTEXBUFFDESC	pVertexBuffDesc,
		IN		KMPACKEDARGB		dwOffsetColor
	);

/*----------------------------------------*/
/* KAMUI1 Legacy API                      */
/* -----------------                      */
/* sorry following functions too slow!!   */
/* and KMVERTEXCONTEXT was huge....       */
/* we only left backward compatibility    */
/*----------------------------------------*/
/*++
kmProcessVertexRenderState

proto type:
	KMSTATUS
	kmProcessVertexRenderState(
				PKMVERTEXCONTEXT pVertexContext
			);

Description:
	頂点(ストリップ)ごとに有効となるレンダリング・パラメータを設定します
	(pVertexContextの設定値をシステムに登録するための前処理を行います)。

	本関数はpVertexContextに設定された値をもとに以下の値を生成します。
			Global Parameter
			Combined ISP/TSP
			Instruction Word
			TSP Control Word
			Texture Control Bits

	本関数が生成した上記データは、KMVERTEXCONTEXT内の以下に示すメンバに保存します。
			pVertexContext->GLOBALPARAMBUFFER
			pVertexContext->ISPPARAMBUFFER
			pVertexContext->TSPPARAMBUFFER
			pVertexContext->TexturePARAMBUFFER

	本関数により、前処理を行った pVertexContext の上記メンバをレンダリングに使用する
	パラメータとして、システムに登録するためには、kmSetVertexRenderStateを呼び出すこと必要があります。

	VERTEXCONTEXTを最初に使用する時には、VERTEXCONTEXTのすべてのメンバの値を指定(初期化)する
	必要があります。

	注：
		pVertexContext->RenderState にすべてのフラグを設定し、すべてのパラメータを定義してください。
		未定義のビットがあった場合の動作は保証しません。

Arguments:
	IN	pVertexContext		コンテキストへのポインタを設定します。

Result:
	KMSTATUS_SUCCESS		設定成功
	KMSTATUS_INVALIDSETTING	許可されていないモード設定

--*/
KMSTATUS KMAPI
kmProcessVertexRenderState(
		IN	PKMVERTEXCONTEXT pVertexContext
	);

/*++
kmSetVertexRenderState

proto type:

	KMSTATUS
	kmSetVertexRenderState (
        	PKMVERTEXBUFFDESC   pVertexBuffDesc,
			PKMVERTEXCONTEXT 	pVertexContext
		);

Description:
	kmProcessVertexRenderStateで処理した pVertexContext 内の以下のメンバ及び関連する値を
	レンダリングに使用するパラメータとしてシステムに登録します。

			pVertexContext->GLOBALPARAMBUFFER
			pVertexContext->ISPPARAMBUFFER
			pVertexContext->TSPPARAMBUFFER
			pVertexContext->TexturePARAMBUFFER

	本関数の呼び出しで設定したパラメータは 本関数の後で呼び出される kmStartVertexStrip 
	以降の頂点(Strip)登録で有効となります。


Arguments:
	OUT	pVertexBuffDesc		KMVERTEXBUFFDESC 構造体へのポインタを設定します。
	IN	pVertexContext		KMVERTEXCONTEXT 構造体へのポインタを設定します。

Result:
	KMSTATUS_SUCCESS		レンダリングパラメータ登録成功

--*/
KMSTATUS KMAPI
kmSetVertexRenderState (
        OUT	PKMVERTEXBUFFDESC   pVertexBuffDesc,
		IN	PKMVERTEXCONTEXT 	pVertexContext
	);

/*++
kmSetModifierRenderState

proto type:
	KMSTATUS
	kmSetModifierRenderState(
        	PKMVERTEXBUFFDESC   pVertexBuffDesc,
			PKMVERTEXCONTEXT 	pVertexContext
		);

Description:
	kmProcessVertexRenderStateで設定したKMVERTEXCONTEXT内の以下のメンバを、
	 Modifier Volume の影響を受ける Polygonの、2 番目のレンダリングパラメータ
	としてシステムに登録します。

				pVertexContext->TSPPARAMBUFFER
				pVertexContext->TexturePARAMBUFFER

	以降の Modifier Volume の影響を受ける Polygon の登録では、本関数で指定した
	KMVERTEXCONTEXTが 2 番目のレンダリングパラメータとして使用します。

	KMVERTEXCONTEXT構造体のうち以下のメンバは参照しません(無視します)。
	(kmSetVertexRenderStateで設定した値が有効となります)
	// for Global Parameter
	KMPARAMTYPE			ParamType			// Parameter Type
	KMLISTTYPE			ListType			// List Type
	KMSTRIPLENGTH		StripLength			// Strip Length
	KMUSERCLIPMODE		UserClipMode		// UserClip Mode
	KMCOLORTYPE			ColorType			// Color Type
	KMUVFORMAT			UVFormat			// UV format

	// for ISP/TSP Instruction Word
	KMDEPTHMODE			DepthMode;			// DepthMode指定
	KMCULLINGMODE		CullingMode;		// Culling Mode
	KMSCREENCORDINATION	ScreenCoordination;	// Screen Coordination
	KMSHADINGMODE		ShadingMode;		// Shading Mode
	KMMODIFIER			SelectModifier;		// Modifier Volume Valiant
	KMBOOLEAN			bZWriteDisable;		// Z Write Disable

	// for ModifierInstruction
	KMDWORD				ModifierInstruction;// ModifierInstruction
	KMFLOAT				fBoundingBoxXmin;	// BoundingBoxXmin(ShadowVolume)
	KMFLOAT				fBoundingBoxYmin;	// BoundingBoxYmin(ShadowVolume)
	KMFLOAT				fBoundingBoxXmax;	// BoundingBoxXmax(ShadowVolume)
	KMFLOAT				fBoundingBoxYmax;	// BoundingBoxYmax(ShadowVolume)

Arguments:
	IN	OUT	pVertexBuffDesc		pVertexContext が持つパラメータを登録登録する
								KMVERTEXBUFFDESC 構造体へのポインタ.
								あらかじめ kmSetSystemConfiguration にて
								初期化されている必要があります。

	IN		pVertexContext		KMVERTEXCONTEXT 構造体へのポインタを設定します。

Result:
	KMSTATUS_SUCCESS			モディファイアの影響を受けるレンダリングパラメータ
								登録成功

--*/

KMSTATUS KMAPI
kmSetModifierRenderState(
        IN	OUT	PKMVERTEXBUFFDESC   pVertexBuffDesc,
		IN		PKMVERTEXCONTEXT 	pVertexContext
	);


/*++
kmStartVertexStrip

proto type:
	KMSTATUS
	kmStartVertexStrip( 
			PKMVERTEXBUFFDESC pBufferDesc
		);

Description:
	神威に、頂点データストリップの登録を開始することを通知します。
	以下の関数の呼び出しでシステムに登録した

		kmSetVertexRenderState
		kmSetModifierRenderState

	レンダリングパラメータを、5種の頂点データリストのいずれかへ書き込みます。
	書き込む頂点データリストは、 KMVERTEXCONTEXTの
	ListTypeメンバから決定されます。

注意：ここで書き込んだレンダリングパラメータの情報と、これに続くkmSetVertexで送る
	  頂点パラメータの形式の組み合わせが正しくない場合の動作は保証されません。

	<本関数は高速性を要求されるためInline展開されるマクロとして定義されます。>

	マクロを使用する場合には、以下のように設定してください。

		#define _KM_USE_VERTEX_MACRO_
		#include <kamui.h>
		#include <kamuix.h> 

Arguments:
	IN	pBufferDesc				PKMVERTEXBUFFDESC型の、Vertex Buffer Descriptorへのポインタです。
								データを登録する頂点データリストの情報を示す。

Result:
	KMSTATUS_SUCCESS			レンダリングパラメータ 書き込み成功
	KMSTATUS_NOT_ENOUGH_MEMORY	頂点データリストの容量が足りない

--*/
#if !defined(_KM_USE_VERTEX_MACRO_)
KMSTATUS KMAPI
kmStartVertexStrip( 
		IN	PKMVERTEXBUFFDESC pBufferDesc
	);
#endif


/*++
kmEndVertexStrip

proto type:
	KMSTATUS KMAPI
	kmEndVertexStrip(
			IN  PKMVERTEXBUFFDESC   pVertexBuffDesc
		);
	
Description:
	
Arguments:
	IN	pVertexBuffDesc		

Result:
	KMSTATUS_SUCCESS		成功

--*/
KMSTATUS KMAPI
kmEndVertexStrip(
		IN  PKMVERTEXBUFFDESC   pVertexBuffDesc
	);
#endif
