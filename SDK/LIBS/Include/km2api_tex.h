/*++

  COPYRIGHT        (C) NEC        Corporation 1997 - 1999

  All rights reserved by NEC Corporation. This program must be
  used solely for the purpose for which it was furnished by NEC
  Corporation. No part of this program may be reproduced or
  disclosed to others, in any form, without the prior written
  permission of NEC Corporation.
  Use of copyright notice does not evidence publication of this
  program.

  Author     :		T.Muto(NEC Software,Ltd.)
  Module Name:		km2api_tex.h

  Abstract:
	KAMUI = Kamui is abstruction model that is ultimate interface for PowerVR.
	'km2api_tex.h' define the function of texture memory manager.

  Environment:
	ANSI C Compiler.

  Notes:
	

  Revision History:

--*/

#if !defined(__kamui2_texture_api_h__)
#define __kamui2_texture_api_h__

/*++
kmCreateTextureSurface

proto type:
	KMSTATUS 
	kmCreateTextureSurface(
			PKMSURFACEDESC	pSurfaceDesc,
			KMINT32			nWidth, 
			KMINT32			nHeight, 
			KMTEXTURETYPE	nTextureType
		);

Description:
	テクスチャ用のSurfaceを確保します。

Arguments:
	OUT	pSurfaceDesc		KMSURFACEDESC 構造体の領域を示すポインタです。
							確保した Texture Surface の情報が返されます。
							KMSTATUS にKMSTATUS_NOT_ENOUGH_MEMORYが返された場合には不定となります。

	IN	nWidth, nHeight		テクスチャの横サイズ、縦サイズを指定します。
								MIPMAPを使用する場合にはトップレベルのテクスチャサイズを指定します。
								Twiddled, VQ, Palettizedなどの正方形テクスチャを使用する場合には 
									nWidthに指定した値のみが使用されます。
								長方形テクスチャを使用する場合には、nWidth, nHeight共に有効です。
								HOLLYは正方形テクスチャサイズとして 8x8～1024x1024までのテクスチャを使用できますが、
								nWidth, nHeightに指定する値は,8, 16, 32, 64, 128, 256, 512, 1024の
								いずれかでなければなりません。

	IN	nTextureType		テクスチャの形式を指定します。
							以下のカテゴリコード、ピクセルフォーマットコードから
							一つずつ選び出し、論理和(or)して与えます

								-カテゴリコード
									KM_TEXTURE_TWIDDLED			// Twiddledフォーマット
									KM_TEXTURE_TWIDDLED_MM		// TwiddledフォーマットMipmapあり
									KM_TEXTURE_VQ				// VQ圧縮形式
									KM_TEXTURE_VQ_MM			// VQ圧縮形式Mipmapあり
									KM_TEXTURE_PALETTIZE4		// 4bppパレット形式
									KM_TEXTURE_PALETTIZE4_MM	// 4bppパレット形式Mipmapあり
									KM_TEXTURE_PALETTIZE8		// 8bppパレット形式
									KM_TEXTURE_PALETTIZE8_MM	// 8bppパレット形式Mipmapあり
									KM_TEXTURE_RECTANGLE		// 矩形

								- ピクセルフォーマットコード
									KM_TEXTURE_1555
									KM_TEXTURE_565
									KM_TEXTURE_4444
									KM_TEXTURE_YUV422
									KM_TEXTURE_BUMP
									KM_TEXTURE_8888

							注)  KM_TEXTURE_8888はKM_TEXTURE_PALETTIZE4or8との組み合わせのみ有効です。

Result:
		KMSTATUS_SUCCESS					テクスチャメモリ確保成功
		KMSTATUS_INVALID_TEXTURE_TYPE		無効なテクスチャタイプを指定した
		KMSTATUS_NOT_ENOUGH_MEMORY			メモリ容量が足りない
		KMSTATUS_INVALID_MIPMAPED_TEXTURE	MIPMAPできないテクスチャにMIPMAPを指定した。

--*/

KMSTATUS KMAPI
kmCreateTextureSurface(
		OUT	PKMSURFACEDESC	pSurfaceDesc,
		IN	KMINT32			nWidth, 
		IN	KMINT32			nHeight, 
		IN	KMTEXTURETYPE	nTextureType
	);

/*++
kmCreateCombinedTextureSurface

proto type:
	KMSTATUS 
	kmCreateCombinedTextureSurface(
			PKMSURFACEDESC	pSurfaceDesc1,
			PKMSURFACEDESC	pSurfaceDesc2,
			KMINT32			nWidth, 
			KMINT32			nHeight, 
			KMTEXTURETYPE	nTextureType
		);

Description:
	VQテクスチャ用のSurfaceを 2つ確保します。nTextureTypeにに設定するテクスチャカテゴリは
	KM_TEXTURE_VQ,KM_TEXTURE_VQ_MMのどちらかでなければなりません。

Arguments:
	OUT	pSurfaceDesc1		KMSURFACEDESC 構造体の領域を示す 1 つめのポインタです。
							確保した Texture Surface の情報が返されます。
							KMSTATUS にKMSTATUS_NOT_ENOUGH_MEMORYが返された場合には不定となります。

	OUT	pSurfaceDesc2		KMSURFACEDESC 構造体の領域を示す 2 つめのポインタです。
							確保した Texture Surface の情報が返されます。
							KMSTATUS にKMSTATUS_NOT_ENOUGH_MEMORYが返された場合には不定となります。

	IN	nWidth, nHeight		テクスチャの横サイズ、縦サイズを指定します。
							MIPMAPを使用する場合にはトップレベルのテクスチャサイズを指定します。
							HOLLYは正方形テクスチャサイズとして 8x8～1024x1024までのテクスチャを使用できますが、
							nWidth, nHeightに指定する値は,8, 16, 32, 64, 128, 256, 512, 1024の
							いずれかでなければなりません。

	IN	nTextureType		テクスチャの形式を指定します。
							以下のカテゴリコード、ピクセルフォーマットコードから
							一つずつ選び出し、論理和(or)して与えます

								-カテゴリコード
									KM_TEXTURE_VQ				// VQ圧縮形式
									KM_TEXTURE_VQ_MM			// VQ圧縮形式Mipmapあり

								- ピクセルフォーマットコード
									KM_TEXTURE_ARGB1555
									KM_TEXTURE_ARGB4444

Result:
		KMSTATUS_SUCCESS					テクスチャメモリ確保成功
		KMSTATUS_INVALID_TEXTURE_TYPE		無効なテクスチャタイプを指定した
		KMSTATUS_NOT_ENOUGH_MEMORY			メモリ容量が足りない

--*/

KMSTATUS KMAPI
kmCreateCombinedTextureSurface(
		OUT	PKMSURFACEDESC	pSurfaceDesc1,
		OUT	PKMSURFACEDESC	pSurfaceDesc2,
		IN	KMINT32			nWidth, 
		IN	KMINT32			nHeight, 
		IN	KMTEXTURETYPE	nTextureType
	);


/*++
kmLoadTexture

proto type:

	KMSTATUS
	kmLoadTexture(
			PKMSURFACEDESC pSurfaceDesc,
			PKMDWORD pTexture
		);

Description:
	kmCreateTextureSurfaceで確保したテクスチャメモリ上の領域に、 
	pTextureで指定されたメインメモリ上のテクスチャを読み込みます。

Arguments:
	IN	pSurfaceDesc	kmCreateTextureSurfaceで確保したテクスチャサーフェスです。
	IN	pTexture		メインメモリ上のテクスチャを示すポインタです。

Result:
	KMSTATUS_SUCCESS					読み込み成功
	KMSTATUS_INVALID_TEXTURE_TYPE		無効なテクスチャタイプを指定した

--*/
KMSTATUS KMAPI
kmLoadTexture(
	IN	PKMSURFACEDESC pSurfaceDesc,
	IN	PKMDWORD pTexture
	);

/*++
kmLoadTextureBlock

proto type:

	KMSTATUS KMAPI
	kmLoadTextureBlock(
		PKMSURFACEDESC	pSurfaceDesc,
		PKMDWORD		pTexture,
		KMUINT32		nBlockNum,
		KMUINT32		nBlockSize
	)

Description:
	kmCreateTextureSurfaceでアロケートしたテクスチャメモリ上の領域に、 
	pTextureで指定されたメインメモリ上のテクスチャブロックを読み込みます。

	テクスチャデータをいくつかのブロックに分割して読み込みます。
	これにより、メインメモリ上に大きなワークエリアを確保することなく、
	サイズの大きなテクスチャを読み込むことができます。

	テクスチャ全体のサイズがブロックサイズで割り切れなくても、正しく読み込まれます。

	読み込むテクスチャのフォーマット形式、サイズなどは、pSurfaceDesc
	が指すサーフェスディスクリプタより判断します。
	実際のテクスチャのフォーマット形式などが、pSurfaceDescが指すサーフェスディスクリプタ
	の内容と異なっている場合は、表示が不正となります。

	なお、この関数はSmall VQ形式のテクスチャには対応していません。
	Small VQ形式のpSurfaceDescを指定した場合には、KMSTATUS_INVALID_TEXTURE_TYPEを返します。

Arguments:
	IN	pSurfaceDesc	kmCreateTextureSurface/kmCreateCombinedTextureSurfaceで
						アロケートしたテクスチャサーフェスです。
	IN	pTexture		メインメモリ上のテクスチャブロックの先頭を示すポインタです。
	IN	nBlockNum		テクスチャのブロック番号を 0 から n ( nはフォーマット/サイズによる)で指定します。
	IN	nBlockSize		ブロックのサイズを 32バイト単位で指定します。
						ブロックサイズ(バイト)を 32 で割った値を指定してください。
						なお、テクスチャ全体のサイズがブロックサイズで割り切れる必要はありません。

Result:
	KMSTATUS_SUCCESS					読み込み成功
	KMSTATUS_INVALID_BLOCKNUMBER		ブロック番号が不正
	KMSTATUS_INVALID_ADDRESS			指定されたアドレスを先頭に持つメモリブロックは
										アロケートされていない
	KMSTATUS_INVALID_TEXTURE_TYPE		無効なテクスチャタイプを指定した

--*/

KMSTATUS KMAPI
kmLoadTextureBlock(
	IN	PKMSURFACEDESC	pSurfaceDesc,
	IN	PKMDWORD		pTexture,
	IN	KMUINT32		nBlockNum,
	IN	KMUINT32		nBlockSize
	);

/*++
kmLoadTexturePart

proto type:

	KMSTATUS KMAPI
	kmLoadTexturePart(
			PKMSURFACEDESC	pSurfaceDesc,
			PKMDWORD		pTexture,
			KMUINT32		nOffset,
			KMUINT32		nSize
		)

Description:
	kmCreateTextureSurfaceでアロケートしたテクスチャメモリ上の領域に、 
	pTextureで指定されたメインメモリ上のテクスチャ(部分)を読み込みます。

	テクスチャデータをいくつかの部分に分割して読み込みます。
	これにより、メインメモリ上に大きなワークエリアを確保することなく、
	サイズの大きなテクスチャを読み込むことができます。

	kmLoadTextureBlockと異なり、一つのテクスチャを、「サイズの異なる」
	複数の部分に分けて読み込むことができます。ただし、今までに読み込んだ
	テクスチャのサイズ(先頭からのオフセット量)は、ユーザ側で管理する
	必要があります。

	読み込むテクスチャのフォーマット形式、サイズなどは、pSurfaceDesc
	で指定されるサーフェスディスクリプタより判断されます。
	実際のテクスチャのフォーマット形式などが、pSurfaceDescで指定される
	サーフェスディスクリプタの内容と異なっている場合は、表示が不正となります。

	なお、この関数はSmall VQ形式のテクスチャには対応していません。
	Small VQ形式のpSurfaceDescを指定した場合には、KMSTATUS_INVALID_TEXTURE_TYPEを返します。

Arguments:
	IN	pSurfaceDesc	kmCreateTextureSurface/kmCreateCombinedTextureSurfaceで
						アロケートしたテクスチャサーフェスです。
	IN	pTexture		メインメモリ上のテクスチャブロックの先頭を示すポインタです。
	IN	nOffset			すでに読み込んだテクスチャのサイズ(先頭からのオフセット量)を
						バイト単位で指定します。これは、今回読み込むテクスチャデータが
						転送される、テクスチャ領域の先頭アドレスとなります。
	IN	nSize			今回読み込む部分のサイズをバイト単位で指定します。
						なお、nSizeが、テクスチャの残りサイズ ( = テクスチャサイズ - nOffset)
						より大きい場合は、残りサイズのみを正しく読み込んで正常終了します。

Usage:
	nOffset = 0;
	nSize   = ***;
	pTextureにテクスチャデータの最初のnSizeバイトをロード;
	while(KMSTATUS_SUCCESS == kmLoadTexturePart(...);
		nOffset = nOffset + nSize;
		nSize   = ????;
		pTextureに次のnSizeバイトをロード;
	}

Result:
	KMSTATUS_SUCCESS					読み込み成功
	KMSTATUS_INVALID_ADDRESS			nOffsetがテクスチャサイズを越えている
	KMSTATUS_INVALID_TEXTURE_TYPE		無効なテクスチャタイプを指定した

--*/

KMSTATUS KMAPI
kmLoadTexturePart(
	IN	PKMSURFACEDESC	pSurfaceDesc,
	IN	PKMDWORD		pTexture,
	IN	KMUINT32		nOffset,
	IN	KMUINT32		nSize
	);


/*++
kmLoadRectangleTexturePart

proto type:

	KMSTATUS KMAPI
	kmLoadRectangleTexturePart(
			PKMSURFACEDESC	pSurfaceDesc,
			PKMDWORD		pTexture,
			KMUINT32		width,
			KMUINT32		height,
			KMUINT32		dst_X,
			KMUINT32		dst_Y,
			KMUINT32		src_X,
			KMUINT32		src_Y,
			KMUINT32		src_U
			)

Description:
	kmCreateTextureSurfaceでアロケートしたRectangle/Stride形式
	テクスチャメモリ上の矩形領域に、pTextureで指定されたメイン
	メモリ上のテクスチャの矩形領域(部分)を書き込みます。

	Rectangle/Stride形式テクスチャの一部を書き換えることができます。

	転送先の矩形領域は、( dst_X, dst_Y )-( dst_X + width, dst_Y + height )です。
	転送元の矩形領域は、( src_X, src_Y )-( src_X + width, src_Y + height )です。
	src_Uがゼロであった場合は、転送元テクスチャのサイズは矩形領域の幅と
	高さ(width,height)と等しいものとみなします。

	なお、この関数はRectangle/Stride形式テクスチャにのみ対応しています。
	これら以外のpSurfaceDescを指定した場合には、
	KMSTATUS_INVALID_TEXTURE_TYPEを返します。

	矩形領域は、転送先・転送元テクスチャの領域内に完全に含まれていなけ
	ればなりません。
	そうでない場合には、転送先テクスチャを含め、他のテクスチャのデータ
	が破壊される場合があります。
	神威では、このチェックは行いません。

Arguments:
	IN	pSurfaceDesc	kmCreateTextureSurface/kmCreateCombinedTextureSurfaceで
						アロケートしたRectangle/Stride形式のテクスチャサーフェスです。
						(転送先テクスチャ)
	IN	pTexture		メインメモリ上のテクスチャデータの先頭を示すポインタです。
						(転送元テクスチャ)
	IN	width,height	転送する矩形領域の幅と高さをテクセル数で指定します。
	IN	dst_X,dst_Y		転送先テクスチャに於ける矩形領域のX,Y座標です。
						転送先テクスチャの左下(先頭)テクセルからの
						相対テクセル数で指定します。
	IN	src_X,src_Y		転送元テクスチャに於ける矩形領域のX,Y座標です。
						転送元テクスチャの左下(先頭)テクセルからの
						相対テクセル数で指定します。
	IN	src_U			転送元テクスチャの幅をテクセル数で指定します。
						これがゼロであった場合は、転送元テクスチャのサイズは
						矩形領域の幅と高さ(width,height)と等しいものとみなします。
						このときは、src_X,src_Yの値は無視されます。(0とみなされます)

Result:
	KMSTATUS_SUCCESS					読み込み成功
	KMSTATUS_INVALID_TEXTURE_TYPE		無効なテクスチャタイプを指定した

--*/

KMSTATUS KMAPI
kmLoadRectangleTexturePart(
	IN	PKMSURFACEDESC	pSurfaceDesc,
	IN	PKMDWORD		pTexture,
	IN	KMUINT32		width,
	IN	KMUINT32		height,
	IN	KMUINT32		dst_X,
	IN	KMUINT32		dst_Y,
	IN	KMUINT32		src_X,
	IN	KMUINT32		src_Y,
	IN	KMUINT32		src_U
	);


/*++
kmFreeTexture

proto type:
	KMSTATUS
	kmFreeTexture(
			PKMSURFACEDESC pSurfaceDesc
		);

Description:
	指定したテクスチャサーフェスを解放します。

Arguments:
	IN	pSurfaceDesc	kmCreateTextureSurfaceで確保したテクスチャサーフェスです。

Result:
	KMSTATUS_SUCCESS				解放成功
	KMSTATUS_INVALID_PARAMETER		解放失敗、テクスチャの指定が不正

--*/

KMSTATUS KMAPI
kmFreeTexture(
	IN	PKMSURFACEDESC pSurfaceDesc
	);


/*++
kmGetFreeTextureMem

proto type:
	KMSTATUS
	kmGetFreeTextureMem(
		PKMUINT32 pSizeOfTexture,
		PKMUINT32 pMaxBlockSizeOfTexture
		);

Description:
	テクスチャメモリの残容量を返します。

Arguments:
	OUT	pSizeOfTexture
			テクスチャメモリの残容量を返すKMDWORD領域へのポインタです。
	OUT	pMaxBlockSizeOfTexture
			テクスチャメモリの空きブロックの最大容量を返すKMDWORD領域へのポインタです。
Result:
	KMSTATUS_SUCCESS		成功

--*/

KMSTATUS KMAPI
kmGetFreeTextureMem(
	OUT	PKMUINT32 pSizeOfTexture,
	OUT	PKMUINT32 pMaxBlockSizeOfTexture
	);

/*++
kmReLoadMipmap

proto type:
	KMSTATUS
	kmReLoadMipmap(
			PKMSURFACEDESC 	pSurfaceDesc,
			PKMVOID	 		pTexture,
			KMINT32	 		nMipmapCount
		);

Description:
	kmCreateTextureSurfaceで確保したテクスチャメモリ上の領域に、 
	pTextureで指定されたメインメモリ上のミップマップテクスチャを上書き読み込みします。

Arguments:
	IN	pSurfaceDesc	kmCreateTextureSurfaceで確保したテクスチャサーフェスです。
						＜Reload先です＞

	IN	pTexture		メインメモリ上のミップマップテクスチャを示すポインタです。
						＜Reload元です＞

	IN	nMipmapCount	読み込むミップマップテクスチャのレベルを指定します。
						下記のいずれかを指定することができます。

						nMipmapCount			Texture Size
						KM_MAPSIZE_1x1				   1x1
						KM_MAPSIZE_2x2				   2x2
						KM_MAPSIZE_4x4				   4x4
						KM_MAPSIZE_8x8				   8x8
						KM_MAPSIZE_16x16			  16x16
						KM_MAPSIZE_32x32			  32x32
						KM_MAPSIZE_64x64			  64x64
						KM_MAPSIZE_128x128			 128x128
						KM_MAPSIZE_256x256			 256x256
						KM_MAPSIZE_512x512			 512x512
						KM_MAPSIZE_1024x1024		1024x1024
	

Result:
	KMSTATUS_SUCCESS			成功
	KMSTATUS_INVALID_PARAMETER	パラメータが不正
	KMSTATUS_INVALID_TEXTURE	無効なテクスチャを指定した

--*/
KMSTATUS KMAPI
kmReLoadMipmap(
	IN	PKMSURFACEDESC 	pSurfaceDesc,
	IN	PKMVOID		 	pTexture,
	IN	KMINT32	 		nMipmapCount
	);

/*++
kmGetTexture

proto type:

	KMSTATUS
	kmGetTexture(
		PKMDWORD		pTexture,
		PKMSURFACEDESC	pSurfaceDesc
		);

Description:
	pSurfaceDescで指定したテクスチャメモリ上のテクスチャを、 
	pTextureで指定されたメインメモリ上に読み出します。
	出力には、KAMUIテクスチャフォーマットに従った16バイトのヘッダが付加されます。

Arguments:
	OUT	pTexture		メインメモリ上のテクスチャを保存する領域を示すポインタです。
	IN	pSurfaceDesc	テクスチャが保存されているテクスチャサーフェスです。

Result:
	KMSTATUS_SUCCESS					読み出し成功
	KMSTATUS_INVALID_ADDRESS			指定されたテクスチャサーフェスは
										確保されていない

--*/

KMSTATUS KMAPI
kmGetTexture(
	OUT	PKMDWORD		pTexture,
	IN	PKMSURFACEDESC	pSurfaceDesc
	);


/*++
kmGarbageCollectTexture

proto type:
	KMSTATUS
	kmGarbageCollectTexture( KMVOID );

Description:
	 Frame Buffer メモリのガベージコレクションを行います。

Arguments:

Result:
	KMSTATUS_SUCCESS					ガベージコレクション成功
	KMSTATUS_NOT_ENOUGH_MEMORY			メモリ容量が足りない

--*/

KMSTATUS KMAPI
kmGarbageCollectTexture( KMVOID );



/*++
kmSetFramebufferTexture

proto type:
	KMSTATUS 
	kmSetFramebufferTexture(
		IN	OUT	PKMSURFACEDESC	pSurfaceDesc
	);

Description:
	 Frame Buffer の情報を、テクスチャ用のSurfaceDescに読み出します。
	直前の Frame Buffer の内容が、Stride-Rectanglar-TextureとしてSurfaceDescに設定されます。
	このSurfaceDescを使用してテクスチャマップすることにより、直前の Frame Buffer 
	の内容をテクスチャとして使用することができます。
	テクスチャとして使用しようとする Frame Buffer は、下記の設定である必要があります。

	・kmSetDisplayModeで、BitDepth が下記のいづれかが指定されていること。
		KM_DSPBPP_ARGB1555
		KM_DSPBPP_RGB565

Arguments:
	IN	OUT	pSurfaceDesc	KMSURFACEDESC 構造体の領域を示すポインタです。
							 Frame Buffer の情報が返されます。

Result:
		KMSTATUS_SUCCESS				 Frame Buffer の情報読み出し成功
		KMSTATUS_INVALID_TEXTURE_TYPE	現在の Frame Buffer の設定はテクスチャとして使用できない

Sample:
	kmSetStrideWidth(nScreenWidth);					// Set screen width
	....(Setup vertex)....
	kmRender();										// Generate previous Frame-Buffer
	kmSetFramebufferTexture(pSurfaceDesc);			// Get Framebuffer information
	VertexContext.pTextureSurfaceDesc	= &pSurfaceDesc;
	kmProcessVertexRenderState(&VertexContext);		// Use Framebuffer as texture
	kmSetVertexRenderState(&VertexContext);			// Set new vertex-context
	....(Setup vertex)....
	kmRender();										// Render!!

--*/
#if 0
KMSTATUS KMAPI
kmSetFramebufferTexture(
		PKMSURFACEDESC	pSurfaceDesc
	);
#endif

/*++
kmLoadVQCodebook

proto type:

	KMSTATUS
	kmLoadVQCodebook(
			PKMSURFACEDESC pSurfaceDesc,
			PKMDWORD pTexture
		);

Description:
	pSurfaceDescで指定されたVQテクスチャサーフェスに、pTextureで指定された
	メインメモリ上のVQテクスチャのコードブック部分のみを読み込みます。
	ロード済みのVQテクスチャの、コードブック(800hバイト)のみを書き換えて
	カラーパレット効果を出したいときに使用します。

Arguments:
	IN	pSurfaceDesc	kmCreateTextureSurfaceで確保したテクスチャサーフェスです。
						このサーフェスのカテゴリは、KM_TEXTURE_VQまたはKM_TEXTURE_VQ_MM
						のどちらかでなければなりません。
	IN	pTexture		メインメモリ上のテクスチャ(コードブック)を示すポインタです。
						これは完全なVQテクスチャである必要はありませんが、
						少なくとも先頭に800hバイトのコードブックを含んでいる必要があります。

Result:
	KMSTATUS_SUCCESS					読み込み成功
	KMSTATUS_INVALID_TEXTURE_TYPE		無効なテクスチャタイプを指定した

--*/

KMSTATUS KMAPI
kmLoadVQCodebook(
	IN	PKMSURFACEDESC	pSurfaceDesc,
	IN	PKMDWORD		pTexture
	);


/*++
kmCreateContiguousTextureSurface

proto type:
	KMSTATUS 
	kmCreateContiguousTextureSurface(
			PKMSURFACEDESC	pSurfaceDesc,
			KMINT32			nTexture,
			KMINT32			nWidth, 
			KMINT32			nHeight, 
			KMTEXTURETYPE	nTextureType
		);

Description:
	 Frame Buffer の連続したアドレス領域に、同時に複数のテクスチャ用Surfaceを確保します。
	これは、Tile AcceleratorのYUVコンバータを使用して、連続して複数のYUV422形式のテクスチャ
	を読み込むときに使用します。(kmLoadYUVTextureをご参照ください)
	YUV422以外のテクスチャ用Surfaceの確保にも使用することができます。

Arguments:
	OUT	pSurfaceDesc			KMSURFACEDESC 構造体の配列へのポインタです。
								確保した Texture Surface の情報が返されます。
								KMSTATUS にKMSTATUS_NOT_ENOUGH_MEMORYが返された場合には不定となります。

	IN	nTexture				連続して確保する Texture Surface の数を指定します。

	IN	nWidth, nHeight			テクスチャの横サイズ、縦サイズを指定します。
								nWidth, nHeightに指定する値は,8, 16, 32, 64, 128, 256, 512, 1024の
								いずれかでなければなりません。

	IN	nTextureType			テクスチャの形式を指定します。
								以下のカテゴリコード、ピクセルフォーマットコードから
								一つずつ選び出し、論理和(or)して与えます

								-カテゴリコード
									KM_TEXTURE_TWIDDLED				// Twiddledフォーマット
									KM_TEXTURE_TWIDDLED_MM			// TwiddledフォーマットMipmapあり
									KM_TEXTURE_TWIDDLED_RECTANGLE	// Twiddled-Rectangle
									KM_TEXTURE_VQ					// VQ圧縮フォーマット
									KM_TEXTURE_VQ_MM				// VQ圧縮フォーマットMipmapあり
									KM_TEXTURE_PALETTIZE4			// 4bppパレット形式
									KM_TEXTURE_PALETTIZE4_MM		// 4bppパレット形式Mipmapあり
									KM_TEXTURE_PALETTIZE8			// 8bppパレット形式
									KM_TEXTURE_PALETTIZE8_MM		// 8bppパレット形式Mipmapあり
									KM_TEXTURE_RECTANGLE			// 矩形
									KM_TEXTURE_STRIDE				// 矩形(ストライド指定有り)

								- ピクセルフォーマットコード
									KM_TEXTURE_ARGB1555
									KM_TEXTURE_RGB565
									KM_TEXTURE_ARGB4444
									KM_TEXTURE_YUV422
									KM_TEXTURE_BUMP

Result:
		KMSTATUS_SUCCESS					テクスチャメモリ確保成功
		KMSTATUS_INVALID_TEXTURE_TYPE		無効なテクスチャタイプを指定した
		KMSTATUS_NOT_ENOUGH_MEMORY			メモリ容量が足りない

--*/

KMSTATUS KMAPI
kmCreateContiguousTextureSurface(
	OUT		PKMSURFACEDESC	pSurfaceDesc,
	IN		KMINT32			nTexture,
	IN		KMINT32			nWidth,
	IN		KMINT32			nHeight,
	IN		KMTEXTURETYPE	nTextureType
	);


/*++
kmLoadYUVTexture

proto type:

	KMSTATUS
	kmLoadYUVTexture(
		PPKMSURFACEDESC	ppSurfaceDesc,
		PKMDWORD		pTexture,
		KMINT32			nWidth,
		KMINT32			nHeight,
		KMDWORD			nFormat,
		KMBOOLEAN		bWaitEndOfDMA
		);

Description:
	kmCreateTextureSurface/kmCreateCombinedTextureSurface/kmCreateContiguousTextureSurface
	で確保したテクスチャメモリ上の領域に、pTextureで指定されたメインメモリ上の
	YUV420-data/YUV422-dataを、Non-Twiddled YUV422テクスチャに変換して読み込みます。
	Tile Accelerator に内蔵されている YUV-data converter を使用して、変換しながら
	読み込みます。

	YUV-data converter の出力は Non-Twiddled であるため、このAPIで指定する読み込み先の
	Texture Surface の形式は、以下のいずれかでなければなりません。
		KM_TEXTURE_RECTANGLE | KM_TEXTURE_YUV422	// 矩形
		KM_TEXTURE_STRIDE    | KM_TEXTURE_YUV422	// 矩形(ストライド指定有り)

	複数のYUV-dataを、一度に連続して読み込む場合(nTexture > 1 の時)は、個々のテクスチャの
	サイズは16x16テクセルでなければなりません。このAPIで指定する読み込み先のTexture Surface
	のサイズ指定にご注意ください。
	また、この場合は、読み込み先のTexture Surfaceは Frame Buffer 上で連続したアドレスに
	確保されていることが必要です。"kmCreateContiguousTextureSurface" APIを使用して
	確保したTexture Surfaceを指定してください。

Arguments:
	IN	ppSurfaceDesc	アロケート済みのテクスチャサーフェスを示すKMSURFACEDESC 構造体への
						ポインタ配列のポインタです。
	IN	pTexture		メインメモリ上のYUV420-data/YUV422-dataを示すポインタです。
	IN	nWidth,
	IN	nHeight,
						連続して読み込む Texture マクロブロックの数を縦と横の数で指定します。
						指定できる値は、それぞれ 1 から 64 のいずれかです。
	IN	nFormat			読み込むデータの形式を指定します。以下のいずれかを指定します。
						KM_TEXTURE_YUV420		入力データがYUV420-dataであることを示します。
						KM_TEXTURE_YUV422		入力データがYUV422-dataであることを示します。
	IN	bWaitEndOfDMA	TRUEの場合、YUVコンバータへのデータ転送のDMAが完了するのを待ちます。
									DMAが終了するまで、本APIは終了しません。
						FALSEの場合、DMAの終了を待ちません。DMAの終了を検知したい場合は
									コールバック"kmSetEndOfYUVCallback"を使用してください。

Result:
	KMSTATUS_SUCCESS					読み込み成功
	KMSTATUS_INVALID_TEXTURE_TYPE		無効なテクスチャタイプを指定した

--*/

KMSTATUS KMAPI
kmLoadYUVTexture(
	IN	PKMSURFACEDESC	pSurfaceDesc,
	IN	PKMDWORD		pTexture,
	IN	KMINT32			nWidth,
	IN	KMINT32			nHeight,
	IN	KMDWORD			nFormat,
	IN	KMBOOLEAN		bWaitEndOfDMA
	);


/*++
kmCreateFixedTextureArea

proto type:

	KMSTATUS KMAPI
	kmCreateFixedTextureArea(
		OUT  PKMSURFACEDESC pSurfaceDesc,
		IN  KMINT32  nWidth,
		IN  KMINT32  nHeight,
		IN  KMTEXTURETYPE  nTextureType
		);

Description:
	kmSetSystemConfiguration を発行しても失われない、固定テクスチャ領域を確
	保します。固定テクスチャ領域はゲーム全体で使用するフォントテクスチャな
	どを置く領域として使用できます。これで確保した領域は 
	kmFreeFixedTextureArea関数でしか解放出来ません。
	また、固定テクスチャ領域はシステムで一つしか確保できません。

	実際の固定テクスチャ領域の確保は、次に kmSetSystemConfiguration を発行し
	たときに行われます。この関数発行後は、必ず kmSetSystemConfiguration を発
	行する必要があります。また、固定テクスチャ領域へのデータ読み込みは、
	 kmSetSystemConfiguration の後に行わなければなりません。
	すなわち、関数の呼び出し順序は、
	(1)kmCreateFixedTextureAreaで固定テクスチャ領域を確保。
	(2)kmSetSystemConfiguration発行。実際の固定領域確保はここで行われる。
	(3)kmLoadTextureなどで、固定テクスチャ領域へテクスチャデータを読み込む。
	となります。 

	kmSetSystemConfiguration を発行する前に、kmFreeFixedTextureArea が発行さ
	れた場合は、それまでに発行されたkmCreateFixedTextureAreaは無効となります
	。この場合は、固定テクスチャ領域は確保されません。 

	なお、ここで確保した領域はガベージコレクションの対象とはなりません。また
	、固定テクスチャ領域の容量は４ＭＢを越えることはできません。 

Arguments:
	OUT	pSurfaceDesc	KMSURFACEDESC型の構造体へのポインタです。
						この構造体には、神威によってSurface情報が返されます。
						KMSTATUS にKMSTATUS_NOT_ENOUGH_MEMORYが返された場合に
						は不定となります。 
	IN	nWidth,nHeight	テクスチャの横サイズ、縦サイズを指定します。 MIPMAPを
						使用する場合にはトップレベルのテクスチャサイズを指定
						します。正方形テクスチャサイズは8x8～1024x1024までの
						テクスチャを使用できますが、 nWidth, nHeightに指定す
						る値は,8, 16, 32, 64, 128, 256, 512, 1024のいずれかで
						なければなりません。 
	IN	nTextureType	テクスチャの形式を指定します。 KmCreateTextureSurface
						の説明をご参照ください。 

Result:
	KMSTATUS_SUCCESS					読み込み成功
	KMSTATUS_INVALID_TEXTURE_TYPE		無効なテクスチャタイプを指定した
	KMSTATUS_NOT_ENOUGH_MEMORY			固定テクスチャ領域の容量が４ＭＢを越えた 

--*/

KMSTATUS KMAPI
kmCreateFixedTextureArea(
	OUT	PKMSURFACEDESC	pSurfaceDesc,
	IN	KMINT32			nWidth,
	IN	KMINT32			nHeight,
	IN	KMTEXTURETYPE	nTextureType
	);


/*++
kmFreeFixedTextureArea

proto type:

	KMSTATUS KMAPI
	kmFreeFixedTextureArea( KMVOID ); 

Description:
	kmCreateFixedTextureArea で確保したすべての固定テクスチャ領域を解放しま
	す。
	実際の固定テクスチャ領域の解放は、次に kmSetSystemConfiguration を発行し
	たときに行われます。この関数発行後は、必ず kmSetSystemConfiguration を発
	行する必要があります。 
	この関数では、 kmCreateTextureSurface / kmCreateCombinedTextureSurface /
	kmCreateContiguousTextureSurface で確保した領域は開放できません。 

Arguments:
	None

Result:
	KMSTATUS_SUCCESS					読み込み成功

--*/

KMSTATUS KMAPI
kmFreeFixedTextureArea( KMVOID ); 


/*++
kmGetCurrentTextureStatus

proto type:

	KMSTATUS KMAPI
	kmGetCurrentTextureStatus(
		OUT PKMFBSTATUS pFBStatus
		);

Description:
	フレームバッファメモリの管理に関する情報を読み出します。ユーザーが下記構
	造体を準備し、そこへのポインタを渡すと、この関数が各メンバの内容を設定し
	ます。 

Arguments:
	OUT	pFBStatus		FB管理情報構造体へのポインタ 

Result:
	KMSTATUS_SUCCESS					成功

--*/

KMSTATUS KMAPI
kmGetCurrentTextureStatus(
	OUT PKMFBSTATUS pFBStatus
	);

#endif
