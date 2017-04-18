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
  Module Name:		km2api_render.h

  Abstract:
	KAMUI = Kamui is abstruction model that is ultimate interface for PowerVR.
	'km2api_render.h' define the function of rendering and the function 
	which is related with renderring.

  Environment:
	ANSI C Compiler.

  Notes:
	kmRender and kmRenderTexture must be among kmEndScene from kmBeginScene();
	kmRender and kmRenderTexture return RenderID.
	Therefore,RenderID must be examined in kmGetRenderStatus if wanting to know
	result of kmRender and kmRenderTexture.

  Revision History:

--*/

#if !defined(__kamui2_render_api_h__)
#define __kamui2_render_api_h__

/*++
kmRender

proto type:
	KMINT32
	kmRender( 
			IN KMDWORD dwFlipMode 
		);

Description:
	タイルアクセラレータに対して、1シーン分の頂点データの登録が終了したことを神威に通知し,
	データ展開完了後、Back Buffer に対するレンダリングを開始します。

Arguments:
	dwFlipMode

Result:
	KMINT32		0 < (return)	DMA lounch success. you can query finish render,
				0 > (return)	miss.

--*/

KMINT32 KMAPI
kmRender( 
		IN KMDWORD dwFlipMode
	);

/*++
kmRenderRect

proto type:
	KMINT32
	kmRenderRect( 
			IN KMDWORD dwFlipMode 
		);

Description:
	タイルアクセラレータに対して、1シーン分の頂点データの登録が終了したことを神威に通知し,
	データ展開完了後、Back Buffer に対するレンダリングを開始します。レンダリング前に、
	リージョンアレイの再構築を行います。

Arguments:
	dwFlipMode

Result:
	KMINT32		0 < (return)	DMA lounch success. you can query finish render,
				0 > (return)	miss.

--*/

KMINT32 KMAPI
kmRenderRect( 
		IN KMDWORD dwFlipMode
	);

/*++
kmRenderTexture

proto type:
	KMINT32
	kmRenderTexture(	
			IN	PKMSURFACEDESC pTextureSurface,
			IN  KMDWORD        dwDitherMode
		);

Description:
	タイルアクセラレータに対して、1シーン分の頂点データの登録が終了したことを神威に通知します。
	頂点データ展開完了後、引数(pTextureSurface) で指定されれたテクスチャに対するレンダリングを開始します。(
	なお、描画先に指定するテクスチャは、Rectangle/Stride形式でなければなりません。

Arguments:
	OUT	pTextureSurface		レンダリング結果を格納するテクスチャです。

Result:
	KMINT32		0 < (return)	DMA lounch success. you can query finish render,
				0 > (return)	miss.

--*/

KMINT32 KMAPI
kmRenderTexture(
			IN	PKMSURFACEDESC pTextureSurface,
			IN  KMDWORD        dwDitherMode
		);

/*++
kmGetRenderStatus

proto type:
	KMSTATUS
	kmGetRenderStatus(	
			IN	KMINT32			nRenderID
		);

Description:
	実行したレンダリングが現在どのような状況かを調べます。

Arguments:
	IN nRenderID	kmRenderもしくはkmRenderTextureを行った場合の返り値を入力します。

		注）kmRenderTextureおよびkmRenderにてNO_FLIPを指定した場合、
		　　KMSTATUS_UNDER_DISPLAYは本関数の返り値とはなりません。

Result:
	KMSTATUS_UNDER_DMA				指定のIDを持つレンダリングは現在頂点データをDMA転送中
	KMSTATUS_FINISH_DMA				指定のIDを持つレンダリングは現在DMA転送を終了
	KMSTATUS_UNDER_RENDER			指定のIDを持つレンダリングは現在レンダリング中
	KMSTATUS_FINISH_RENDER			指定のIDを持つレンダリングは現在レンダリングを終了
	KMSTATUS_UNDER_DISPLAY			指定のIDを持つレンダリングは現在表示中
	KMSTATUS_FINISH_ALL_SEQUENCE	指定のIDを持つレンダリングは現在すべての処理を終了

--*/

KMSTATUS KMAPI
kmGetRenderStatus(	
		IN	KMINT32			nRenderID
	);

#endif
