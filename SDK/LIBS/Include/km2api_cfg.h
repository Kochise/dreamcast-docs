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
  Module Name:		km2api.h

  Abstract:
	KAMUI = Kamui is abstruction model that is ultimate interface for PowerVR.
	'km2api_cfg.h' defines kmSetSystemConfiguration();

  Environment:
	ANSI C Compiler.

  Notes:
	kmSetSystemConfiguration();

  Revision History:

--*/

#if !defined(__kamui2_configuration_api_h)
#define __kamui2_configuration_api_h

/*++
kmSetSystemConfiguration

proto type:
	KMSTATUS kmSetSystemConfiguration(
			PKMSYSTEMCONFIGSTRUCT pSystemConfigStruct
	)

Description:
		KMSYSTEMCONFIGSTRUCT型構造体に指定したパラメータに従い、神威のシステム構成を設定します。

		 Texture/Frame Buffer 全体の容量  -  (指定された最大テクスチャ使用サイズ + 表示用Frame Buffer)
				=	 Native Buffer

Arguments:
	IN	OUT	pSystemConfigStruct
							KMSYSTEMCONFIGSTRUCT型構造体へのポインタを指定します。
							本構造体のメンバは以下の様に設定します。

				dwSize		KMSYSTEMCONFIGSTRUCT 構造体のサイズ を代入します。
							pSystemConfigStruct->dwSize = sizeof(KMSYSTEMCONFIGSTRUCT);

				flags		システムの動作を指定します。
								KM_CONFIGFLAG_ENABLE_CLEAR_FRAMEBUFFER	Frame Buffer 確保時にバッファの内容をクリアします。
								KM_CONFIGFLAG_ENABLE_STRIPBUFFER		Strip Buffer を有効にします。
								KM_CONFIGFLAG_ENABLE_2V_LATENCY			2V Laytency Mode にします。
								KM_CONFIGFLAG_NOWAITVSYNC				V-SYNC を待たないモードです。

								KM_CONFIGFLAG_NOWAIT_FINISH_TEXTUREDMA	TextureをDMA転送した場合に、DMAの終了を待たないようにします。
								                                        DMAの終了検出はkmQueryFinishLastTextureDMAを使用して行ってください。
								                                        また、DMA中のDMA転送元メモリへのアクセスは必ず避けるようにしてください。

				ppSurfaceDescArray/	nNumOfFrameBuffer;
							KMSURFACEDESC 構造体のポインタ配列へのポインタとポインタ配列の要素数を与えます。
							以下のように設定します。

									KMSURFACEDESC Surface1;
									KMSURFACEDESC Surface2;
									PKMSURFACEDESC ppSurfaceArray[nNumOfFrameBuffer];
									ppSurfaceArray[0] = &Surface1;
									ppSurfaceArray[1] = &Surface2;

									pSystemConfigStruct->nNumOfFrameBuffer  = nNumOfFrameBuffer;
									pSystemConfigStruct->ppSurfaceDescArray = ppSurfaceArray;

				nTextureMemorySize
							使用するテクスチャメモリのサイズを指定します。

				pBufferDesc
						KMVERTEXBUFFDESC 構造体へのポインタです。

				pVertexBuffer
				nVertexBufferSize;
						頂点バッファへのベースアドレス/サイズを指定します。

Result:
	KMSTATUS_SUCCESS			成功
	KMSTATUS_NOT_ENOUGH_MEMORY	Native Buffer/Frame Buffer のためのメモリ容量が足りません

--*/

KMSTATUS KMAPI
kmSetSystemConfiguration(
		IN	OUT	PKMSYSTEMCONFIGSTRUCT pSystemConfigStruct
	);
#endif
