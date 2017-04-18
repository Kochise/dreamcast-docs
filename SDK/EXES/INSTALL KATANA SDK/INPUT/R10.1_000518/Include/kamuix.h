/*++

  COPYRIGHT		   (C) NEC		  Corporation 1998 - 1999

  All rights reserved by NEC Corporation. This program must be
  used solely for the purpose for which it was furnished by NEC
  Corporation. No part of this program may be reproduced or
  disclosed to others, in any form, without the prior written
  permission of NEC Corporation.
  Use of copyright notice does not evidence publication of this
  program.

  Author     :		T.Hirata(NEC Software,Ltd.)
  Module Name:		kamuix.h

  Abstract:
	KAMUI = Kamui is abstruction model that is ultimate interface for PowerVR.
	'kamuix.h' macro.

  Environment:
	Microsoft Compiler. & SHC compiler

  Notes:
	define Kamui's SetVertex macro

  Revision History:

--*/

#if !defined(__kmvertex_macro_header__)
#define __kmvertex_macro_header__
#ifdef __cplusplus
extern "C" {
#endif

#if defined(_KAMUIX_USE_MMU_)
	extern PKMVOID sySqStart(PKMVOID);
	#define KMI_GET_MAPPING_ADDRESS(addr)	\
		(PKMVOID)(addr)
#else
	#define KMI_GET_MAPPING_ADDRESS(addr)	\
		((PKMDWORD)(((KMDWORD)(addr) & 0x03FFFFFF) | 0xE0000000)); \
		*((volatile PKMDWORD)(0xFF000038)) = *((volatile PKMDWORD)(0xFF00003C)) = (KMDWORD)(addr) >> 24;
#endif

#if !defined(WIN32)
#include <machine.h>		/* SHC Built-in Library Header */
#endif

#if defined(_KM_USE_VERTEX_MACRO_)

#if defined(WIN32)
/*
 * Macro for kmStartVertexStrip();
 *
 *	KMSTATUS KMAPI
 *	kmStartVertexStrip(
 *			IN	PKMVERTEXBUFFDESC pBufferDesc
 *		);
 *
 */

#define kmStartVertexStrip(pBufferDesc) KMSTATUS_SUCCESS;	{										\
	KMDWORD StructSize;																				\
	KMDWORD ListType;																				\
	ListType   = ((PKMCURRENTLISTSTATE)(pBufferDesc)->pCurrentListState)->ListType;					\
	StructSize = ((PKMCURRENTLISTSTATE)(pBufferDesc)->pCurrentListState)->GlobalParamSize;			\
	memcpy( (PKMDWORD)(*((pBufferDesc)->pCurrentPtr + ListType)),									\
			(PKMDWORD)((pBufferDesc)->pGlobalParam),												\
			StructSize);																			\
	(*((pBufferDesc)->pCurrentPtr + ListType)) += (StructSize >> 2);								\
	}

/*
 * Macro for kmSetVertex();
 *
 *	KMSTATUS
 *	kmSetVertex(
 *		IN	PKMVERTEXBUFFDESC pBufferDesc,
 *		IN	PVOID pVertex,
 *		IN	KMVERTEXTYPE VertexType,
 *		IN	KMINT32 StructSize
 *		);
 */
#define	kmSetVertex(pBufferDesc,pVertex,VertexType,StructSize)	KMSTATUS_SUCCESS;{					\
	KMDWORD ListType;																				\
	ListType	= (((PKMCURRENTLISTSTATE)(pBufferDesc)->pCurrentListState)->ListType);				\
	memcpy((PKMDWORD)(*((pBufferDesc)->pCurrentPtr + ListType)),(PKMDWORD)(pVertex),(StructSize));	\
	(*((pBufferDesc)->pCurrentPtr + ListType)) += ((StructSize) >> 2);								\
}
#else /* WIN32 */

/* Prototypes for SH4 Macro */
PKMDWORD
kmyMemCopy (
		IN	KMVOID *dst,
		IN	KMVOID *src,
		IN	KMDWORD size
	);

/*
 * Macro for kmStartVertexStrip();
 *	for SH4 FLAT
 *	KMSTATUS KMAPI
 *	kmStartVertexStrip(
 *			IN	PKMVERTEXBUFFDESC pBufferDesc
 *		);
 *
 */
#define kmStartVertexStrip(pBufferDesc) KMSTATUS_SUCCESS;	{										\
	KMDWORD StructSize;																				\
	KMDWORD ListType;																				\
	PKMDWORD pDST;																					\
	ListType   = ((PKMCURRENTLISTSTATE)(pBufferDesc)->pCurrentListState)->ListType;					\
	pDST = (PKMDWORD)(*((pBufferDesc)->pCurrentPtr + ListType));									\
	StructSize = ((PKMCURRENTLISTSTATE)(pBufferDesc)->pCurrentListState)->GlobalParamSize;			\
	*((volatile PKMDWORD)0xFF000038) = *((volatile PKMDWORD)0xFF00003C) = (KMDWORD)pDST >> 24;		\
	pDST = (PKMDWORD)(((KMDWORD)pDST & 0x03FFFFFF) | 0xE0000000);									\
	kmyMemCopy( pDST,	(PKMDWORD)((pBufferDesc)->pGlobalParam), StructSize);						\
	prefetch((void *)pDST);																			\
	if(StructSize == 0x40) prefetch((void *)(pDST + 8));											\
	(*((pBufferDesc)->pCurrentPtr + ListType)) += (StructSize >> 2);								\
}

/*
 * Macro for kmStartStrip();
 *	for SH4 FLAT
 *	KMSTATUS KMAPI
 *	kmStartVertexStrip(
 *			IN	PKMVERTEXBUFFDESC pBufferDesc,
 *			IN	PKMSTRIPHEAD	  pStripHead
 *		);
 *
 */
#define kmStartStrip( _pDesc_,_pHead_ )		KMSTATUS_SUCCESS;	{									\
	KMDWORD ListType;																				\
	PKMDWORD pDST;																					\
	ListType   = ((((PKMSTRIPHEAD)(_pHead_))->dwStripHead[0]) >> 24) & 7;							\
	((PKMCURRENTLISTSTATE)(_pDesc_)->pCurrentListState)->ListType = ListType;						\
	pDST = (PKMDWORD)(*((_pDesc_)->pCurrentPtr + ListType));										\
	*((volatile PKMDWORD)0xFF000038) = *((volatile PKMDWORD)0xFF00003C) = (KMDWORD)pDST >> 24;		\
	pDST = (PKMDWORD)(((KMDWORD)pDST & 0x03FFFFFF) | 0xE0000000);									\
	if(((PKMSTRIPHEAD)_pHead_)->dwStripHead[0] & 0x00001400)										\
	{	kmyMemCopy( pDST,	(PKMDWORD)(((PKMSTRIPHEAD)(_pHead_))->dwStripHead), 0x40);				\
		prefetch((void *)pDST);																		\
		prefetch((void *)(pDST + 8));																\
		(*((_pDesc_)->pCurrentPtr + ListType)) += (16);												\
	}else{																							\
		kmyMemCopy( pDST,	(PKMDWORD)(((PKMSTRIPHEAD)(_pHead_))->dwStripHead), 0x20);				\
		prefetch((void *)pDST);																		\
		(*((_pDesc_)->pCurrentPtr + ListType)) += (8);												\
	}																								\
	}

/*
 * Macro for kmSetVertex();
 *	for SH4 FLAT
 *	KMSTATUS
 *	kmSetVertex(
 *		IN	PKMVERTEXBUFFDESC pBufferDesc,
 *		IN	PVOID pVertex,
 *		IN	KMVERTEXTYPE VertexType,
 *		IN	KMINT32 StructSize
 *		);
 */
#define	kmSetVertex(pBufferDesc,pVertex,VertexType,StructSize)	KMSTATUS_SUCCESS;{					\
	KMDWORD ListType;																				\
	PKMDWORD pDST;																					\
	ListType	= (((PKMCURRENTLISTSTATE)(pBufferDesc)->pCurrentListState)->ListType);				\
	pDST = (PKMDWORD)(*((pBufferDesc)->pCurrentPtr + ListType));									\
	*((volatile PKMDWORD)0xFF000038) = *((volatile PKMDWORD)0xFF00003C) = (KMDWORD)pDST >> 24;		\
	pDST = (PKMDWORD)(((KMDWORD)pDST & 0x03FFFFFF) | 0xE0000000);								\
	kmyMemCopy(pDST,(PKMDWORD)(pVertex),(StructSize));											\
	prefetch((void *)pDST);																		\
	if(StructSize == 0x40) prefetch((void *)(pDST + 8));										\
	(*((pBufferDesc)->pCurrentPtr + ListType)) += ((StructSize) >> 2);							\
}
#endif /* WIN32 */

#endif	/* _KM_USE_VERTEX_MACRO_ */

/*
 *	KMSTATUS
 *	kmxSetVertex(
 *		IN	PKMVERTEXBUFFDESC pBufferDesc,
 *		IN	PVOID pVertex,
 *		IN	KMVERTEXTYPE VertexType,
 *		IN	KMINT32 StructSize
 *		);
 */
#define	kmxSetVertex(desc,ptr,type,size)		kmxSetVertex_##type(desc,ptr)

#define kmxSetVertex_KM_VERTEXTYPE_00( desc,ptr)	kmxSetVertex_0( desc,ptr)
#define kmxSetVertex_KM_VERTEXTYPE_01( desc,ptr)	kmxSetVertex_1( desc,ptr)
#define kmxSetVertex_KM_VERTEXTYPE_02( desc,ptr)	kmxSetVertex_2( desc,ptr)
#define kmxSetVertex_KM_VERTEXTYPE_03( desc,ptr)	kmxSetVertex_3( desc,ptr)
#define kmxSetVertex_KM_VERTEXTYPE_04( desc,ptr)	kmxSetVertex_4( desc,ptr)
#define kmxSetVertex_KM_VERTEXTYPE_05( desc,ptr)	kmxSetVertex_5( desc,ptr)
#define kmxSetVertex_KM_VERTEXTYPE_06( desc,ptr)	kmxSetVertex_6( desc,ptr)
#define kmxSetVertex_KM_VERTEXTYPE_07( desc,ptr)	kmxSetVertex_7( desc,ptr)
#define kmxSetVertex_KM_VERTEXTYPE_08( desc,ptr)	kmxSetVertex_8( desc,ptr)
#define kmxSetVertex_KM_VERTEXTYPE_09( desc,ptr)	kmxSetVertex_9( desc,ptr)
#define kmxSetVertex_KM_VERTEXTYPE_10( desc,ptr)	kmxSetVertex_10(desc,ptr)
#define kmxSetVertex_KM_VERTEXTYPE_11( desc,ptr)	kmxSetVertex_11(desc,ptr)
#define kmxSetVertex_KM_VERTEXTYPE_12( desc,ptr)	kmxSetVertex_12(desc,ptr)
#define kmxSetVertex_KM_VERTEXTYPE_13( desc,ptr)	kmxSetVertex_13(desc,ptr)
#define kmxSetVertex_KM_VERTEXTYPE_14( desc,ptr)	kmxSetVertex_14(desc,ptr)
#define kmxSetVertex_KM_VERTEXTYPE_15( desc,ptr)	kmxSetVertex_15(desc,ptr)
#define kmxSetVertex_KM_VERTEXTYPE_16( desc,ptr)	kmxSetVertex_16(desc,ptr)
#define kmxSetVertex_KM_VERTEXTYPE_17( desc,ptr)	kmxSetVertex_17(desc,ptr)


/*
 * Vertex Struct Clacker macro
 */
#if !defined(_KM_USE_VERTEX_MACRO_L2_)
#define kmxSetVertex_0( desc,ptr)	kmSetVertex(desc,ptr,KM_VERTEXTYPE_00,sizeof(KMVERTEX0))
#define kmxSetVertex_1( desc,ptr)	kmSetVertex(desc,ptr,KM_VERTEXTYPE_01,sizeof(KMVERTEX1))
#define kmxSetVertex_2( desc,ptr)	kmSetVertex(desc,ptr,KM_VERTEXTYPE_02,sizeof(KMVERTEX2))
#define kmxSetVertex_3( desc,ptr)	kmSetVertex(desc,ptr,KM_VERTEXTYPE_03,sizeof(KMVERTEX3))
#define kmxSetVertex_4( desc,ptr)	kmSetVertex(desc,ptr,KM_VERTEXTYPE_04,sizeof(KMVERTEX4))
#define kmxSetVertex_5( desc,ptr)	kmSetVertex(desc,ptr,KM_VERTEXTYPE_05,sizeof(KMVERTEX5))
#define kmxSetVertex_6( desc,ptr)	kmSetVertex(desc,ptr,KM_VERTEXTYPE_06,sizeof(KMVERTEX6))
#define kmxSetVertex_7( desc,ptr)	kmSetVertex(desc,ptr,KM_VERTEXTYPE_07,sizeof(KMVERTEX7))
#define kmxSetVertex_8( desc,ptr)	kmSetVertex(desc,ptr,KM_VERTEXTYPE_08,sizeof(KMVERTEX8))
#define kmxSetVertex_9( desc,ptr)	kmSetVertex(desc,ptr,KM_VERTEXTYPE_09,sizeof(KMVERTEX9))
#define kmxSetVertex_10(desc,ptr)	kmSetVertex(desc,ptr,KM_VERTEXTYPE_10,sizeof(KMVERTEX10))
#define kmxSetVertex_11(desc,ptr)	kmSetVertex(desc,ptr,KM_VERTEXTYPE_11,sizeof(KMVERTEX11))
#define kmxSetVertex_12(desc,ptr)	kmSetVertex(desc,ptr,KM_VERTEXTYPE_12,sizeof(KMVERTEX12))
#define kmxSetVertex_13(desc,ptr)	kmSetVertex(desc,ptr,KM_VERTEXTYPE_13,sizeof(KMVERTEX13))
#define kmxSetVertex_14(desc,ptr)	kmSetVertex(desc,ptr,KM_VERTEXTYPE_14,sizeof(KMVERTEX14))
#define kmxSetVertex_15(desc,ptr)	kmSetVertex(desc,ptr,KM_VERTEXTYPE_15,sizeof(KMVERTEX15))
#define kmxSetVertex_16(desc,ptr)	kmSetVertex(desc,ptr,KM_VERTEXTYPE_16,sizeof(KMVERTEX16))
#define kmxSetVertex_17(desc,ptr)	kmSetVertex(desc,ptr,KM_VERTEXTYPE_17,sizeof(KMVERTEX17))
#else

#define	kmxGetDstAddress(desc)	(PKMDWORD)(*(((desc)->pCurrentPtr)								\
								+ (((PKMCURRENTLISTSTATE)((desc)->pCurrentListState))->ListType)))
#define kmxSetVertex_0( desc,ptr)													\
	KMSTATUS_SUCCESS;{																\
		PKMVERTEX0			pkmxVertex;												\
		pkmxVertex = ((PKMVERTEX0)(kmxGetDstAddress(desc)));						\
		pkmxVertex->ParamControlWord	= ((PKMVERTEX0)(ptr))->ParamControlWord;	\
		pkmxVertex->fX					= ((PKMVERTEX0)(ptr))->fX;					\
		pkmxVertex->fY					= ((PKMVERTEX0)(ptr))->fY;					\
		pkmxVertex->u.fZ				= ((PKMVERTEX0)(ptr))->u.fZ;				\
		pkmxVertex->uBaseRGB			= ((PKMVERTEX0)(ptr))->uBaseRGB;			\
		((PKMVERTEX0)(kmxGetDstAddress(desc)))++;									\
	}

#define kmxSetVertex_1( desc,ptr)													\
	KMSTATUS_SUCCESS;{																\
		PKMVERTEX1			pkmxVertex;												\
		pkmxVertex = ((PKMVERTEX1)(kmxGetDstAddress(desc)));						\
		pkmxVertex->ParamControlWord	= ((PKMVERTEX1)(ptr))->ParamControlWord;	\
		pkmxVertex->fX					= ((PKMVERTEX1)(ptr))->fX;					\
		pkmxVertex->fY					= ((PKMVERTEX1)(ptr))->fY;					\
		pkmxVertex->u.fZ				= ((PKMVERTEX1)(ptr))->u.fZ;				\
		pkmxVertex->fBaseAlpha			= ((PKMVERTEX1)(ptr))->fBaseAlpha;			\
		pkmxVertex->fBaseRed			= ((PKMVERTEX1)(ptr))->fBaseRed;			\
		pkmxVertex->fBaseGreen			= ((PKMVERTEX1)(ptr))->fBaseGreen;			\
		pkmxVertex->fBaseBlue			= ((PKMVERTEX1)(ptr))->fBaseBlue;			\
		((PKMVERTEX1)(kmxGetDstAddress(desc)))++;									\
	}

#define kmxSetVertex_2( desc,ptr)													\
	KMSTATUS_SUCCESS;{																\
		PKMVERTEX2			pkmxVertex;												\
		pkmxVertex = ((PKMVERTEX2)(kmxGetDstAddress(desc)));						\
		pkmxVertex->ParamControlWord	= ((PKMVERTEX2)(ptr))->ParamControlWord;	\
		pkmxVertex->fX					= ((PKMVERTEX2)(ptr))->fX;					\
		pkmxVertex->fY					= ((PKMVERTEX2)(ptr))->fY;					\
		pkmxVertex->u.fZ				= ((PKMVERTEX2)(ptr))->u.fZ;				\
		pkmxVertex->fBaseIntensity		= ((PKMVERTEX2)(ptr))->fBaseIntensity;		\
		((PKMVERTEX2)(kmxGetDstAddress(desc)))++;									\
	}

#define kmxSetVertex_3( desc,ptr)													\
	KMSTATUS_SUCCESS;{																\
		PKMVERTEX3			pkmxVertex;												\
		pkmxVertex = ((PKMVERTEX3)(kmxGetDstAddress(desc)));						\
		pkmxVertex->ParamControlWord	= ((PKMVERTEX3)(ptr))->ParamControlWord;	\
		pkmxVertex->fX					= ((PKMVERTEX3)(ptr))->fX;					\
		pkmxVertex->fY					= ((PKMVERTEX3)(ptr))->fY;					\
		pkmxVertex->u.fZ				= ((PKMVERTEX3)(ptr))->u.fZ;				\
		pkmxVertex->fU					= ((PKMVERTEX3)(ptr))->fU;					\
		pkmxVertex->fV					= ((PKMVERTEX3)(ptr))->fV;					\
		pkmxVertex->uBaseRGB			= ((PKMVERTEX3)(ptr))->uBaseRGB;			\
		pkmxVertex->uOffsetRGB			= ((PKMVERTEX3)(ptr))->uOffsetRGB;			\
		((PKMVERTEX3)(kmxGetDstAddress(desc)))++;									\
	}

#define kmxSetVertex_4( desc,ptr)													\
	KMSTATUS_SUCCESS;{																\
		PKMVERTEX4			pkmxVertex;												\
		pkmxVertex = ((PKMVERTEX4)(kmxGetDstAddress(desc)));						\
		pkmxVertex->ParamControlWord	= ((PKMVERTEX4)(ptr))->ParamControlWord;	\
		pkmxVertex->fX					= ((PKMVERTEX4)(ptr))->fX;					\
		pkmxVertex->fY					= ((PKMVERTEX4)(ptr))->fY;					\
		pkmxVertex->u.fZ				= ((PKMVERTEX4)(ptr))->u.fZ;				\
		pkmxVertex->dwUV				= ((PKMVERTEX4)(ptr))->dwUV;				\
		pkmxVertex->uBaseRGB			= ((PKMVERTEX4)(ptr))->uBaseRGB;			\
		pkmxVertex->uOffsetRGB			= ((PKMVERTEX4)(ptr))->uOffsetRGB;			\
		((PKMVERTEX4)(kmxGetDstAddress(desc)))++;									\
	}

#define kmxSetVertex_5( desc,ptr)													\
	KMSTATUS_SUCCESS;{																\
		PKMVERTEX5			pkmxVertex;												\
		pkmxVertex = ((PKMVERTEX5)(kmxGetDstAddress(desc)));						\
		pkmxVertex->ParamControlWord	= ((PKMVERTEX5)(ptr))->ParamControlWord;	\
		pkmxVertex->fX					= ((PKMVERTEX5)(ptr))->fX;					\
		pkmxVertex->fY					= ((PKMVERTEX5)(ptr))->fY;					\
		pkmxVertex->u.fZ				= ((PKMVERTEX5)(ptr))->u.fZ;				\
		pkmxVertex->fU					= ((PKMVERTEX5)(ptr))->fU;					\
		pkmxVertex->fV					= ((PKMVERTEX5)(ptr))->fV;					\
		pkmxVertex->fBaseAlpha			= ((PKMVERTEX5)(ptr))->fBaseAlpha;			\
		pkmxVertex->fBaseRed			= ((PKMVERTEX5)(ptr))->fBaseRed;			\
		pkmxVertex->fBaseGreen			= ((PKMVERTEX5)(ptr))->fBaseGreen;			\
		pkmxVertex->fBaseBlue			= ((PKMVERTEX5)(ptr))->fBaseBlue;			\
		pkmxVertex->fOffsetAlpha		= ((PKMVERTEX5)(ptr))->fOffsetAlpha;		\
		pkmxVertex->fOffsetRed			= ((PKMVERTEX5)(ptr))->fOffsetRed;			\
		pkmxVertex->fOffsetGreen		= ((PKMVERTEX5)(ptr))->fOffsetGreen;		\
		pkmxVertex->fOffsetBlue			= ((PKMVERTEX5)(ptr))->fOffsetBlue;			\
		((PKMVERTEX5)(kmxGetDstAddress(desc)))++;									\
	}

#define kmxSetVertex_6( desc,ptr)													\
	KMSTATUS_SUCCESS;{																\
		PKMVERTEX6			pkmxVertex;												\
		pkmxVertex = ((PKMVERTEX6)(kmxGetDstAddress(desc)));						\
		pkmxVertex->ParamControlWord	= ((PKMVERTEX6)(ptr))->ParamControlWord;	\
		pkmxVertex->fX					= ((PKMVERTEX6)(ptr))->fX;					\
		pkmxVertex->fY					= ((PKMVERTEX6)(ptr))->fY;					\
		pkmxVertex->u.fZ				= ((PKMVERTEX6)(ptr))->u.fZ;				\
		pkmxVertex->dwUV				= ((PKMVERTEX6)(ptr))->dwUV;				\
		pkmxVertex->fBaseAlpha			= ((PKMVERTEX6)(ptr))->fBaseAlpha;			\
		pkmxVertex->fBaseRed			= ((PKMVERTEX6)(ptr))->fBaseRed;			\
		pkmxVertex->fBaseGreen			= ((PKMVERTEX6)(ptr))->fBaseGreen;			\
		pkmxVertex->fBaseBlue			= ((PKMVERTEX6)(ptr))->fBaseBlue;			\
		pkmxVertex->fOffsetAlpha		= ((PKMVERTEX6)(ptr))->fOffsetAlpha;		\
		pkmxVertex->fOffsetRed			= ((PKMVERTEX6)(ptr))->fOffsetRed;			\
		pkmxVertex->fOffsetGreen		= ((PKMVERTEX6)(ptr))->fOffsetGreen;		\
		pkmxVertex->fOffsetBlue			= ((PKMVERTEX6)(ptr))->fOffsetBlue;			\
		((PKMVERTEX6)(kmxGetDstAddress(desc)))++;									\
	}

#define kmxSetVertex_7( desc,ptr)													\
	KMSTATUS_SUCCESS;{																\
		PKMVERTEX7			pkmxVertex;												\
		pkmxVertex = ((PKMVERTEX7)(kmxGetDstAddress(desc)));						\
		pkmxVertex->ParamControlWord	= ((PKMVERTEX7)(ptr))->ParamControlWord;	\
		pkmxVertex->fX					= ((PKMVERTEX7)(ptr))->fX;					\
		pkmxVertex->fY					= ((PKMVERTEX7)(ptr))->fY;					\
		pkmxVertex->u.fZ				= ((PKMVERTEX7)(ptr))->u.fZ;				\
		pkmxVertex->fU					= ((PKMVERTEX7)(ptr))->fU;					\
		pkmxVertex->fV					= ((PKMVERTEX7)(ptr))->fV;					\
		pkmxVertex->fBaseIntensity		= ((PKMVERTEX7)(ptr))->fBaseIntensity;		\
		pkmxVertex->fOffsetIntensity	= ((PKMVERTEX7)(ptr))->fOffsetIntensity;	\
		((PKMVERTEX7)(kmxGetDstAddress(desc)))++;									\
	}

#define kmxSetVertex_8( desc,ptr)													\
	KMSTATUS_SUCCESS;{																\
		PKMVERTEX8			pkmxVertex;												\
		pkmxVertex = ((PKMVERTEX8)(kmxGetDstAddress(desc)));						\
		pkmxVertex->ParamControlWord	= ((PKMVERTEX8)(ptr))->ParamControlWord;	\
		pkmxVertex->fX					= ((PKMVERTEX8)(ptr))->fX;					\
		pkmxVertex->fY					= ((PKMVERTEX8)(ptr))->fY;					\
		pkmxVertex->u.fZ				= ((PKMVERTEX8)(ptr))->u.fZ;				\
		pkmxVertex->dwUV				= ((PKMVERTEX8)(ptr))->dwUV;				\
		pkmxVertex->fBaseIntensity		= ((PKMVERTEX8)(ptr))->fBaseIntensity;		\
		pkmxVertex->fOffsetIntensity	= ((PKMVERTEX8)(ptr))->fOffsetIntensity;	\
		((PKMVERTEX8)(kmxGetDstAddress(desc)))++;									\
	}

#define kmxSetVertex_9( desc,ptr)													\
	KMSTATUS_SUCCESS;{																\
		PKMVERTEX9			pkmxVertex;												\
		pkmxVertex = ((PKMVERTEX9)(kmxGetDstAddress(desc)));						\
		pkmxVertex->ParamControlWord	= ((PKMVERTEX9)(ptr))->ParamControlWord;	\
		pkmxVertex->fX					= ((PKMVERTEX9)(ptr))->fX;					\
		pkmxVertex->fY					= ((PKMVERTEX9)(ptr))->fY;					\
		pkmxVertex->u.fZ				= ((PKMVERTEX9)(ptr))->u.fZ;				\
		pkmxVertex->uBaseRGB0m			= ((PKMVERTEX9)(ptr))->uBaseRGB0m;			\
		pkmxVertex->uBaseRGB1m			= ((PKMVERTEX9)(ptr))->uBaseRGB1m;			\
		((PKMVERTEX9)(kmxGetDstAddress(desc)))++;									\
	}

#define kmxSetVertex_10(desc,ptr)													\
	KMSTATUS_SUCCESS;{																\
		PKMVERTEX10			pkmxVertex;												\
		pkmxVertex = ((PKMVERTEX10)(kmxGetDstAddress(desc)));						\
		pkmxVertex->ParamControlWord	= ((PKMVERTEX10)(ptr))->ParamControlWord;	\
		pkmxVertex->fX					= ((PKMVERTEX10)(ptr))->fX;					\
		pkmxVertex->fY					= ((PKMVERTEX10)(ptr))->fY;					\
		pkmxVertex->u.fZ				= ((PKMVERTEX10)(ptr))->u.fZ;				\
		pkmxVertex->fBaseIntensity0m	= ((PKMVERTEX10)(ptr))->fBaseIntensity0m;	\
		pkmxVertex->fBaseIntensity1m	= ((PKMVERTEX10)(ptr))->fBaseIntensity1m;	\
		((PKMVERTEX10)(kmxGetDstAddress(desc)))++;									\
	}

#define kmxSetVertex_11(desc,ptr)													\
	KMSTATUS_SUCCESS;{																\
		PKMVERTEX11			pkmxVertex;												\
		pkmxVertex = ((PKMVERTEX11)(kmxGetDstAddress(desc)));						\
		pkmxVertex->ParamControlWord	= ((PKMVERTEX11)(ptr))->ParamControlWord;	\
		pkmxVertex->fX					= ((PKMVERTEX11)(ptr))->fX;					\
		pkmxVertex->fY					= ((PKMVERTEX11)(ptr))->fY;					\
		pkmxVertex->u.fZ				= ((PKMVERTEX11)(ptr))->u.fZ;				\
		pkmxVertex->fU0m				= ((PKMVERTEX11)(ptr))->fU0m;				\
		pkmxVertex->fV0m				= ((PKMVERTEX11)(ptr))->fV0m;				\
		pkmxVertex->uBaseRGB0m			= ((PKMVERTEX11)(ptr))->uBaseRGB0m;			\
		pkmxVertex->uOffsetRGB0m		= ((PKMVERTEX11)(ptr))->uOffsetRGB0m;		\
		pkmxVertex->fU1m				= ((PKMVERTEX11)(ptr))->fU1m;				\
		pkmxVertex->fV1m				= ((PKMVERTEX11)(ptr))->fV1m;				\
		pkmxVertex->uBaseRGB1m			= ((PKMVERTEX11)(ptr))->uBaseRGB1m;			\
		pkmxVertex->uOffsetRGB1m		= ((PKMVERTEX11)(ptr))->uOffsetRGB1m;		\
		((PKMVERTEX11)(kmxGetDstAddress(desc)))++;									\
	}

#define kmxSetVertex_12(desc,ptr)													\
	KMSTATUS_SUCCESS;{																\
		PKMVERTEX12			pkmxVertex;												\
		pkmxVertex = ((PKMVERTEX12)(kmxGetDstAddress(desc)));						\
		pkmxVertex->ParamControlWord	= ((PKMVERTEX12)(ptr))->ParamControlWord;	\
		pkmxVertex->fX					= ((PKMVERTEX12)(ptr))->fX;					\
		pkmxVertex->fY					= ((PKMVERTEX12)(ptr))->fY;					\
		pkmxVertex->u.fZ				= ((PKMVERTEX12)(ptr))->u.fZ;				\
		pkmxVertex->dwUV0m				= ((PKMVERTEX12)(ptr))->dwUV0m;				\
		pkmxVertex->uBaseRGB0m			= ((PKMVERTEX12)(ptr))->uBaseRGB0m;			\
		pkmxVertex->uOffsetRGB0m		= ((PKMVERTEX12)(ptr))->uOffsetRGB0m;		\
		pkmxVertex->dwUV1m				= ((PKMVERTEX12)(ptr))->dwUV1m;				\
		pkmxVertex->uBaseRGB1m			= ((PKMVERTEX12)(ptr))->uBaseRGB1m;			\
		pkmxVertex->uOffsetRGB1m		= ((PKMVERTEX12)(ptr))->uOffsetRGB1m;		\
		((PKMVERTEX12)(kmxGetDstAddress(desc)))++;									\
	}

#define kmxSetVertex_13(desc,ptr)													\
	KMSTATUS_SUCCESS;{																\
		PKMVERTEX13			pkmxVertex;												\
		pkmxVertex = ((PKMVERTEX13)(kmxGetDstAddress(desc)));						\
		pkmxVertex->ParamControlWord	= ((PKMVERTEX13)(ptr))->ParamControlWord;	\
		pkmxVertex->fX					= ((PKMVERTEX13)(ptr))->fX;					\
		pkmxVertex->fY					= ((PKMVERTEX13)(ptr))->fY;					\
		pkmxVertex->u.fZ				= ((PKMVERTEX13)(ptr))->u.fZ;				\
		pkmxVertex->fU0m				= ((PKMVERTEX13)(ptr))->fU0m;				\
		pkmxVertex->fV0m				= ((PKMVERTEX13)(ptr))->fV0m;				\
		pkmxVertex->fBaseIntensity0m	= ((PKMVERTEX13)(ptr))->fBaseIntensity0m;	\
		pkmxVertex->fOffsetIntensity0m	= ((PKMVERTEX13)(ptr))->fOffsetIntensity0m;	\
		pkmxVertex->fU1m				= ((PKMVERTEX13)(ptr))->fU1m;				\
		pkmxVertex->fV1m				= ((PKMVERTEX13)(ptr))->fV1m;				\
		pkmxVertex->fBaseIntensity1m	= ((PKMVERTEX13)(ptr))->fBaseIntensity1m;	\
		pkmxVertex->fOffsetIntensity0m	= ((PKMVERTEX13)(ptr))->fOffsetIntensity0m;	\
		((PKMVERTEX13)(kmxGetDstAddress(desc)))++;									\
	}

#define kmxSetVertex_14(desc,ptr)													\
	KMSTATUS_SUCCESS;{																\
		PKMVERTEX14			pkmxVertex;												\
		pkmxVertex = ((PKMVERTEX14)(kmxGetDstAddress(desc)));						\
		pkmxVertex->ParamControlWord	= ((PKMVERTEX14)(ptr))->ParamControlWord;	\
		pkmxVertex->fX					= ((PKMVERTEX14)(ptr))->fX;					\
		pkmxVertex->fY					= ((PKMVERTEX14)(ptr))->fY;					\
		pkmxVertex->u.fZ				= ((PKMVERTEX14)(ptr))->u.fZ;				\
		pkmxVertex->dwUV0m				= ((PKMVERTEX14)(ptr))->dwUV0m;				\
		pkmxVertex->fBaseIntensity0m	= ((PKMVERTEX14)(ptr))->fBaseIntensity0m;	\
		pkmxVertex->fOffsetIntensity0m	= ((PKMVERTEX14)(ptr))->fOffsetIntensity0m;	\
		pkmxVertex->dwUV1m				= ((PKMVERTEX14)(ptr))->dwUV1m;				\
		pkmxVertex->fBaseIntensity1m	= ((PKMVERTEX14)(ptr))->fBaseIntensity1m;	\
		pkmxVertex->fOffsetIntensity0m	= ((PKMVERTEX14)(ptr))->fOffsetIntensity0m;	\
		((PKMVERTEX14)(kmxGetDstAddress(desc)))++;									\
	}

#define kmxSetVertex_15(desc,ptr)													\
	KMSTATUS_SUCCESS;{																\
		PKMVERTEX15			pkmxVertex;												\
		pkmxVertex = ((PKMVERTEX15)(kmxGetDstAddress(desc)));						\
		pkmxVertex->ParamControlWord	= ((PKMVERTEX15)(ptr))->ParamControlWord;	\
		pkmxVertex->fAX					= ((PKMVERTEX15)(ptr))->fAX;				\
		pkmxVertex->fAY					= ((PKMVERTEX15)(ptr))->fAY;				\
		pkmxVertex->uA.fAZ				= ((PKMVERTEX15)(ptr))->uA.fAZ;				\
		pkmxVertex->fBX					= ((PKMVERTEX15)(ptr))->fBX;				\
		pkmxVertex->fBY					= ((PKMVERTEX15)(ptr))->fBY;				\
		pkmxVertex->uB.fBZ				= ((PKMVERTEX15)(ptr))->uB.fBZ;				\
		pkmxVertex->fCX					= ((PKMVERTEX15)(ptr))->fCX;				\
		pkmxVertex->fCY					= ((PKMVERTEX15)(ptr))->fCY;				\
		pkmxVertex->uC.fCZ				= ((PKMVERTEX15)(ptr))->uC.fCZ;				\
		pkmxVertex->fDX					= ((PKMVERTEX15)(ptr))->fDX;				\
		pkmxVertex->fDY					= ((PKMVERTEX15)(ptr))->fDY;				\
		((PKMVERTEX15)(kmxGetDstAddress(desc)))++;									\
	}

#define kmxSetVertex_16(desc,ptr)													\
	KMSTATUS_SUCCESS;{																\
		PKMVERTEX16			pkmxVertex;												\
		pkmxVertex = ((PKMVERTEX16)(kmxGetDstAddress(desc)));						\
		pkmxVertex->ParamControlWord	= ((PKMVERTEX16)(ptr))->ParamControlWord;	\
		pkmxVertex->ParamControlWord	= ((PKMVERTEX16)(ptr))->ParamControlWord;	\
		pkmxVertex->fAX					= ((PKMVERTEX16)(ptr))->fAX;				\
		pkmxVertex->fAY					= ((PKMVERTEX16)(ptr))->fAY;				\
		pkmxVertex->uA.fAZ				= ((PKMVERTEX16)(ptr))->uA.fAZ;				\
		pkmxVertex->fBX					= ((PKMVERTEX16)(ptr))->fBX;				\
		pkmxVertex->fBY					= ((PKMVERTEX16)(ptr))->fBY;				\
		pkmxVertex->uB.fBZ				= ((PKMVERTEX16)(ptr))->uB.fBZ;				\
		pkmxVertex->fCX					= ((PKMVERTEX16)(ptr))->fCX;				\
		pkmxVertex->fCY					= ((PKMVERTEX16)(ptr))->fCY;				\
		pkmxVertex->uC.fCZ				= ((PKMVERTEX16)(ptr))->uC.fCZ;				\
		pkmxVertex->fDX					= ((PKMVERTEX16)(ptr))->fDX;				\
		pkmxVertex->fDY					= ((PKMVERTEX16)(ptr))->fDY;				\
		pkmxVertex->dwUVA				= ((PKMVERTEX16)(ptr))->dwUVA;				\
		pkmxVertex->dwUVB				= ((PKMVERTEX16)(ptr))->dwUVB;				\
		pkmxVertex->dwUVC				= ((PKMVERTEX16)(ptr))->dwUVC;				\
		((PKMVERTEX16)(kmxGetDstAddress(desc)))++;									\
	}

#define kmxSetVertex_17(desc,ptr)													\
	KMSTATUS_SUCCESS;{																\
		PKMVERTEX17			pkmxVertex;												\
		pkmxVertex = ((PKMVERTEX17)(kmxGetDstAddress(desc)));						\
		pkmxVertex->ParamControlWord	= ((PKMVERTEX17)(ptr))->ParamControlWord;	\
		pkmxVertex->fAX					= ((PKMVERTEX17)(ptr))->fAX;				\
		pkmxVertex->fAY					= ((PKMVERTEX17)(ptr))->fAY;				\
		pkmxVertex->uA.fAZ				= ((PKMVERTEX17)(ptr))->uA.fAZ;				\
		pkmxVertex->fBX					= ((PKMVERTEX17)(ptr))->fBX;				\
		pkmxVertex->fBY					= ((PKMVERTEX17)(ptr))->fBY;				\
		pkmxVertex->uB.fBZ				= ((PKMVERTEX17)(ptr))->uB.fBZ;				\
		pkmxVertex->fCX					= ((PKMVERTEX17)(ptr))->fCX;				\
		pkmxVertex->fCY					= ((PKMVERTEX17)(ptr))->fCY;				\
		pkmxVertex->uC.fCZ				= ((PKMVERTEX17)(ptr))->uC.fCZ;				\
		((PKMVERTEX17)(kmxGetDstAddress(desc)))++;									\
	}


#endif

#if defined(_KM_USE_VERTEX_MACRO_L3_)
#if defined(WIN32)
#define kmxxGetCurrentPtr(desc)																\
{																							\
	PKMDWORD pkmCurrentPtr;																	\
	pkmCurrentPtr =(PKMDWORD)(*((desc)->pCurrentPtr + ((PKMCURRENTLISTSTATE)(desc)->pCurrentListState)->ListType));

#define kmxxStartVertexStrip(desc) KMSTATUS_SUCCESS;										\
	memcpy( pkmCurrentPtr,																	\
			(PKMDWORD)((desc)->pGlobalParam),												\
			((PKMCURRENTLISTSTATE)(desc)->pCurrentListState)->GlobalParamSize);				\
	pkmCurrentPtr += ((PKMCURRENTLISTSTATE)(desc)->pCurrentListState)->GlobalParamSize >> 2;

#define kmxxReleaseCurrentPtr(desc)	\
	*((desc)->pCurrentPtr + ((PKMCURRENTLISTSTATE)(desc)->pCurrentListState)->ListType) = pkmCurrentPtr; \
}
#define kmxxSetVertex_0(pcw, x, y, invw, pkdcol)								\
		((PKMVERTEX0)(pkmCurrentPtr))->ParamControlWord = pcw;					\
		((PKMVERTEX0)(pkmCurrentPtr))->fX				= x;					\
		((PKMVERTEX0)(pkmCurrentPtr))->fY				= y;					\
		((PKMVERTEX0)(pkmCurrentPtr))->u.fZ				= invw;					\
		((PKMVERTEX0)(pkmCurrentPtr))->uBaseRGB.dwPacked			= pkdcol;				\
		((PKMVERTEX0)pkmCurrentPtr)++;

#define kmxxSetVertex_1(pcw, x, y, invw, Alpha, Red, Green, Blue)				\
		((PKMVERTEX1)(pkmCurrentPtr))->ParamControlWord	= pcw;					\
		((PKMVERTEX1)(pkmCurrentPtr))->fX				= x;					\
		((PKMVERTEX1)(pkmCurrentPtr))->fY				= y;					\
		((PKMVERTEX1)(pkmCurrentPtr))->u.fZ				= invw;					\
		((PKMVERTEX1)(pkmCurrentPtr))->fBaseAlpha		= Alpha;				\
		((PKMVERTEX1)(pkmCurrentPtr))->fBaseRed			= Red;					\
		((PKMVERTEX1)(pkmCurrentPtr))->fBaseGreen		= Green;				\
		((PKMVERTEX1)(pkmCurrentPtr))->fBaseBlue		= Blue;					\
		((PKMVERTEX1)pkmCurrentPtr)++;

#define kmxxSetVertex_2(pcw, x, y, invw, bi )									\
		((PKMVERTEX2)(pkmCurrentPtr))->ParamControlWord	= pcw;					\
		((PKMVERTEX2)(pkmCurrentPtr))->fX				= x;					\
		((PKMVERTEX2)(pkmCurrentPtr))->fY				= y;					\
		((PKMVERTEX2)(pkmCurrentPtr))->u.fZ				= invw;					\
		((PKMVERTEX2)(pkmCurrentPtr))->fBaseIntensity	= bi;					\
		((PKMVERTEX2)pkmCurrentPtr)++;

#define kmxxSetVertex_3(pcw, x, y, invw, fu, fv, bcol, ocol)					\
		((PKMVERTEX3)(pkmCurrentPtr))->ParamControlWord	= pcw;					\
		((PKMVERTEX3)(pkmCurrentPtr))->fX				= x;					\
		((PKMVERTEX3)(pkmCurrentPtr))->fY				= y;					\
		((PKMVERTEX3)(pkmCurrentPtr))->u.fZ				= invw;					\
		((PKMVERTEX3)(pkmCurrentPtr))->fU				= fu;					\
		((PKMVERTEX3)(pkmCurrentPtr))->fV				= fv;					\
		((PKMVERTEX3)(pkmCurrentPtr))->uBaseRGB.dwPacked			= bcol;					\
		((PKMVERTEX3)(pkmCurrentPtr))->uOffsetRGB.dwPacked		= ocol;					\
		((PKMVERTEX3)pkmCurrentPtr)++;

#define kmxxSetVertex_4(pcw, x, y, invw, uv, bcol, ocol)						\
		((PKMVERTEX4)(pkmCurrentPtr))->ParamControlWord	= pcw;					\
		((PKMVERTEX4)(pkmCurrentPtr))->fX				= x;					\
		((PKMVERTEX4)(pkmCurrentPtr))->fY				= y;					\
		((PKMVERTEX4)(pkmCurrentPtr))->u.fZ				= invw;					\
		((PKMVERTEX4)(pkmCurrentPtr))->dwUV				= uv;					\
		((PKMVERTEX4)(pkmCurrentPtr))->uBaseRGB.dwPacked			= bcol;					\
		((PKMVERTEX4)(pkmCurrentPtr))->uOffsetRGB.dwPacked		= ocol;					\
		((PKMVERTEX4)pkmCurrentPtr)++;

#define kmxxSetVertex_5(pcw, x, y,invw, fu, fv, ba, br, bg, bb, oa, or, og, ob)	\
		((PKMVERTEX5)(pkmCurrentPtr))->ParamControlWord	= pcw;					\
		((PKMVERTEX5)(pkmCurrentPtr))->fX				= x;					\
		((PKMVERTEX5)(pkmCurrentPtr))->fY				= y;					\
		((PKMVERTEX5)(pkmCurrentPtr))->u.fZ				= invw;					\
		((PKMVERTEX5)(pkmCurrentPtr))->fU				= fu;					\
		((PKMVERTEX5)(pkmCurrentPtr))->fV				= fv;					\
		((PKMVERTEX5)(pkmCurrentPtr))->fBaseAlpha		= ba;					\
		((PKMVERTEX5)(pkmCurrentPtr))->fBaseRed			= br;					\
		((PKMVERTEX5)(pkmCurrentPtr))->fBaseGreen		= bg;					\
		((PKMVERTEX5)(pkmCurrentPtr))->fBaseBlue		= bb;					\
		((PKMVERTEX5)(pkmCurrentPtr))->fOffsetAlpha		= oa;					\
		((PKMVERTEX5)(pkmCurrentPtr))->fOffsetRed		= or;					\
		((PKMVERTEX5)(pkmCurrentPtr))->fOffsetGreen		= og;					\
		((PKMVERTEX5)(pkmCurrentPtr))->fOffsetBlue		= ob;					\
		((PKMVERTEX5)pkmCurrentPtr)++;

#define kmxxSetVertex_6(pcw, x, y, invw, uv, ba, br, bg, bb, oa, or, og, ob)	\
		((PKMVERTEX6)(pkmCurrentPtr))->ParamControlWord	= pcw;					\
		((PKMVERTEX6)(pkmCurrentPtr))->fX				= x;					\
		((PKMVERTEX6)(pkmCurrentPtr))->fY				= y;					\
		((PKMVERTEX6)(pkmCurrentPtr))->u.fZ				= invw;					\
		((PKMVERTEX6)(pkmCurrentPtr))->dwUV				= uv;					\
		((PKMVERTEX6)(pkmCurrentPtr))->fBaseAlpha		= ba;					\
		((PKMVERTEX6)(pkmCurrentPtr))->fBaseRed			= br;					\
		((PKMVERTEX6)(pkmCurrentPtr))->fBaseGreen		= bg;					\
		((PKMVERTEX6)(pkmCurrentPtr))->fBaseBlue		= bb;					\
		((PKMVERTEX6)(pkmCurrentPtr))->fOffsetAlpha		= oa;					\
		((PKMVERTEX6)(pkmCurrentPtr))->fOffsetRed		= or;					\
		((PKMVERTEX6)(pkmCurrentPtr))->fOffsetGreen		= og;					\
		((PKMVERTEX6)(pkmCurrentPtr))->fOffsetBlue		= ob;					\
		((PKMVERTEX6)pkmCurrentPtr)++;

#define kmxxSetVertex_7(pcw, x, y, invw, fu, fv, bi, oi)						\
		((PKMVERTEX7)(pkmCurrentPtr))->ParamControlWord	= pcw;					\
		((PKMVERTEX7)(pkmCurrentPtr))->fX				= x;					\
		((PKMVERTEX7)(pkmCurrentPtr))->fY				= y;					\
		((PKMVERTEX7)(pkmCurrentPtr))->u.fZ				= invw;					\
		((PKMVERTEX7)(pkmCurrentPtr))->fU				= fu;					\
		((PKMVERTEX7)(pkmCurrentPtr))->fV				= fv;					\
		((PKMVERTEX7)(pkmCurrentPtr))->fBaseIntensity	= bi;					\
		((PKMVERTEX7)(pkmCurrentPtr))->fOffsetIntensity	= oi;					\
		((PKMVERTEX7)pkmCurrentPtr)++;

#define kmxxSetVertex_8(pcw, x, y, invw, uv, bi, oi)							\
		((PKMVERTEX8)(pkmCurrentPtr))->ParamControlWord	= pcw;					\
		((PKMVERTEX8)(pkmCurrentPtr))->fX				= x;					\
		((PKMVERTEX8)(pkmCurrentPtr))->fY				= y;					\
		((PKMVERTEX8)(pkmCurrentPtr))->u.fZ				= invw;					\
		((PKMVERTEX8)(pkmCurrentPtr))->dwUV				= uv;					\
		((PKMVERTEX8)(pkmCurrentPtr))->fBaseIntensity	= bi;					\
		((PKMVERTEX8)(pkmCurrentPtr))->fOffsetIntensity	= oi;					\
		((PKMVERTEX8)pkmCurrentPtr)++;

#define kmxxSetVertex_9(pcw, x, y, invw, m0col, m1col)							\
		((PKMVERTEX9)(pkmCurrentPtr))->ParamControlWord	= pcw;					\
		((PKMVERTEX9)(pkmCurrentPtr))->fX				= x;					\
		((PKMVERTEX9)(pkmCurrentPtr))->fY				= y;					\
		((PKMVERTEX9)(pkmCurrentPtr))->u.fZ				= invw;					\
		((PKMVERTEX9)(pkmCurrentPtr))->uBaseRGB0m.dwPacked		= m0col;				\
		((PKMVERTEX9)(pkmCurrentPtr))->uBaseRGB1m.dwPacked		= m1col;				\
		((PKMVERTEX9)pkmCurrentPtr)++;

#define kmxxSetVertex_10(pcw, x, y, invw, m0bi, m1bi)							\
		((PKMVERTEX10)(pkmCurrentPtr))->ParamControlWord= pcw;					\
		((PKMVERTEX10)(pkmCurrentPtr))->fX				= x;					\
		((PKMVERTEX10)(pkmCurrentPtr))->fY				= y;					\
		((PKMVERTEX10)(pkmCurrentPtr))->u.fZ			= invw;					\
		((PKMVERTEX10)(pkmCurrentPtr))->fBaseIntensity0m= m0bi;					\
		((PKMVERTEX10)(pkmCurrentPtr))->fBaseIntensity1m= m1bi;					\
		((PKMVERTEX10)pkmCurrentPtr)++;

#define kmxxSetVertex_11(pcw, x, y, invw, um0, vm0, bcolm0, ocolm0, um1, vm1, bcolm1, ocolm1)		\
		((PKMVERTEX11)(pkmCurrentPtr))->ParamControlWord	= pcw;				\
		((PKMVERTEX11)(pkmCurrentPtr))->fX					= x;				\
		((PKMVERTEX11)(pkmCurrentPtr))->fY					= y;				\
		((PKMVERTEX11)(pkmCurrentPtr))->u.fZ				= invw;				\
		((PKMVERTEX11)(pkmCurrentPtr))->fU0m				= um0;				\
		((PKMVERTEX11)(pkmCurrentPtr))->fV0m				= vm0;				\
		((PKMVERTEX11)(pkmCurrentPtr))->uBaseRGB0m.dwPacked			= bcolm0;			\
		((PKMVERTEX11)(pkmCurrentPtr))->uOffsetRGB0m.dwPacked		= ocolm0;			\
		((PKMVERTEX11)(pkmCurrentPtr))->fU1m				= um1;				\
		((PKMVERTEX11)(pkmCurrentPtr))->fV1m				= vm1;				\
		((PKMVERTEX11)(pkmCurrentPtr))->uBaseRGB1m.dwPacked			= bcolm1;			\
		((PKMVERTEX11)(pkmCurrentPtr))->uOffsetRGB1m.dwPacked		= ocolm1;			\
		((PKMVERTEX11)pkmCurrentPtr)++;

#define kmxxSetVertex_12(pcw, x, y, invw, uvm0, bcolm0, ocolm0, uvm1, bcolm1, ocolm1)				\
		((PKMVERTEX12)(pkmCurrentPtr))->ParamControlWord	= pcw;				\
		((PKMVERTEX12)(pkmCurrentPtr))->fX					= x;				\
		((PKMVERTEX12)(pkmCurrentPtr))->fY					= y;				\
		((PKMVERTEX12)(pkmCurrentPtr))->u.fZ				= invw;				\
		((PKMVERTEX12)(pkmCurrentPtr))->dwUV0m				= uvm0;				\
		((PKMVERTEX12)(pkmCurrentPtr))->uBaseRGB0m.dwPacked			= bcolm0;			\
		((PKMVERTEX12)(pkmCurrentPtr))->uOffsetRGB0m.dwPacked		= ocolm0;			\
		((PKMVERTEX12)(pkmCurrentPtr))->dwUV1m				= uvm1;				\
		((PKMVERTEX12)(pkmCurrentPtr))->uBaseRGB1m.dwPacked			= bcolm1;			\
		((PKMVERTEX12)(pkmCurrentPtr))->uOffsetRGB1m.dwPacked		= ocolm1;			\
		((PKMVERTEX12)pkmCurrentPtr)++;

#define kmxxSetVertex_13(pcw, x, y, invw, um0, vm0, bim0, oim0, um1, vm1, bim1, oim1)					\
		((PKMVERTEX13)(pkmCurrentPtr))->ParamControlWord	= pcw;				\
		((PKMVERTEX13)(pkmCurrentPtr))->fX					= x;				\
		((PKMVERTEX13)(pkmCurrentPtr))->fY					= y;				\
		((PKMVERTEX13)(pkmCurrentPtr))->u.fZ				= invw;				\
		((PKMVERTEX13)(pkmCurrentPtr))->fU0m				= um0;				\
		((PKMVERTEX13)(pkmCurrentPtr))->fV0m				= vm0;				\
		((PKMVERTEX13)(pkmCurrentPtr))->fBaseIntensity0m	= bim0;				\
		((PKMVERTEX13)(pkmCurrentPtr))->fOffsetIntensity0m	= oim0;				\
		((PKMVERTEX13)(pkmCurrentPtr))->fU1m				= um1;				\
		((PKMVERTEX13)(pkmCurrentPtr))->fV1m				= vm1;				\
		((PKMVERTEX13)(pkmCurrentPtr))->fBaseIntensity1m	= bim1;				\
		((PKMVERTEX13)(pkmCurrentPtr))->fOffsetIntensity0m	= oim1;				\
		((PKMVERTEX13)pkmCurrentPtr)++;

#define kmxxSetVertex_14(pcw, x, y, invw, uvm0, bim0, oim0, uvm1, bim1, oim1)	\
		((PKMVERTEX14)(pkmCurrentPtr))->ParamControlWord	= pcw;				\
		((PKMVERTEX14)(pkmCurrentPtr))->fX					= x;				\
		((PKMVERTEX14)(pkmCurrentPtr))->fY					= y;				\
		((PKMVERTEX14)(pkmCurrentPtr))->u.fZ				= invw;				\
		((PKMVERTEX14)(pkmCurrentPtr))->dwUV0m				= uvm0;				\
		((PKMVERTEX14)(pkmCurrentPtr))->fBaseIntensity0m	= bim0;				\
		((PKMVERTEX14)(pkmCurrentPtr))->fOffsetIntensity0m	= oim0;				\
		((PKMVERTEX14)(pkmCurrentPtr))->dwUV1m				= uvm1;				\
		((PKMVERTEX14)(pkmCurrentPtr))->fBaseIntensity1m	= bim1;				\
		((PKMVERTEX14)(pkmCurrentPtr))->fOffsetIntensity0m	= oim1;				\
		((PKMVERTEX14)pkmCurrentPtr)++;

#define kmxxSetVertex_15(pcw, xa, ya, invwa, xb, yb, invwb, xc, yc, invwc, xd, yd)	\
		((PKMVERTEX15)(pkmCurrentPtr))->ParamControlWord	= pcw;				\
		((PKMVERTEX15)(pkmCurrentPtr))->fAX					= xa;				\
		((PKMVERTEX15)(pkmCurrentPtr))->fAY					= ya;				\
		((PKMVERTEX15)(pkmCurrentPtr))->uA.fAZ				= invwa;			\
		((PKMVERTEX15)(pkmCurrentPtr))->fBX					= xb;				\
		((PKMVERTEX15)(pkmCurrentPtr))->fBY					= yb;				\
		((PKMVERTEX15)(pkmCurrentPtr))->uB.fBZ				= invwb;			\
		((PKMVERTEX15)(pkmCurrentPtr))->fCX					= xc;				\
		((PKMVERTEX15)(pkmCurrentPtr))->fCY					= yc;				\
		((PKMVERTEX15)(pkmCurrentPtr))->uC.fCZ				= invwc;			\
		((PKMVERTEX15)(pkmCurrentPtr))->fDX					= xd;				\
		((PKMVERTEX15)(pkmCurrentPtr))->fDY					= yd;				\
		((PKMVERTEX15)pkmCurrentPtr)++;

#define kmxxSetVertex_16(pcw, xa, ya, invwa, xb, yb, invwb, xc, yc, invwc, xd, yd, uva, uvb, uvc )	\
		((PKMVERTEX16)(pkmCurrentPtr))->ParamControlWord	= pcw;				\
		((PKMVERTEX16)(pkmCurrentPtr))->fAX					= xa;				\
		((PKMVERTEX16)(pkmCurrentPtr))->fAY					= ya;				\
		((PKMVERTEX16)(pkmCurrentPtr))->uA.fAZ				= invwa;			\
		((PKMVERTEX16)(pkmCurrentPtr))->fBX					= xb;				\
		((PKMVERTEX16)(pkmCurrentPtr))->fBY					= yb;				\
		((PKMVERTEX16)(pkmCurrentPtr))->uB.fBZ				= invwb;			\
		((PKMVERTEX16)(pkmCurrentPtr))->fCX					= xc;				\
		((PKMVERTEX16)(pkmCurrentPtr))->fCY					= yc;				\
		((PKMVERTEX16)(pkmCurrentPtr))->uC.fCZ				= invwc;			\
		((PKMVERTEX16)(pkmCurrentPtr))->fDX					= xd;				\
		((PKMVERTEX16)(pkmCurrentPtr))->fDY					= yd;				\
		((PKMVERTEX16)(pkmCurrentPtr))->dwUVA				= uva;				\
		((PKMVERTEX16)(pkmCurrentPtr))->dwUVB				= uvb;				\
		((PKMVERTEX16)(pkmCurrentPtr))->dwUVC				= uvc;				\
		((PKMVERTEX16)pkmCurrentPtr)++;

#define kmxxSetVertex_17(pcw, xa, ya, invwa, xb, yb, invwb, xc, yc, invwc)		\
		((PKMVERTEX17)(pkmCurrentPtr))->ParamControlWord	= pcw;				\
		((PKMVERTEX17)(pkmCurrentPtr))->fAX					= xa;				\
		((PKMVERTEX17)(pkmCurrentPtr))->fAY					= ya;				\
		((PKMVERTEX17)(pkmCurrentPtr))->uA.fAZ				= invwa;			\
		((PKMVERTEX17)(pkmCurrentPtr))->fBX					= xb;				\
		((PKMVERTEX17)(pkmCurrentPtr))->fBY					= yb;				\
		((PKMVERTEX17)(pkmCurrentPtr))->uB.fBZ				= invwb;			\
		((PKMVERTEX17)(pkmCurrentPtr))->fCX					= xc;				\
		((PKMVERTEX17)(pkmCurrentPtr))->fCY					= yc;				\
		((PKMVERTEX17)(pkmCurrentPtr))->uC.fCZ				= invwc;			\
		((PKMVERTEX17)pkmCurrentPtr)++;

#else	/* WIN32 */

#define kmxxGetCurrentPtr(desc)																\
{																							\
	register PKMDWORD pkmCurrentPtr;														\
	PKMDWORD pkmCurrentListPtr;																\
	PKMDWORD pkmStartPtr;																		\
	pkmCurrentListPtr = (PKMDWORD)((desc)->pCurrentPtr + ((PKMCURRENTLISTSTATE)(desc)->pCurrentListState)->ListType); \
	pkmStartPtr = pkmCurrentPtr = KMI_GET_MAPPING_ADDRESS(*pkmCurrentListPtr);

#define kmxxStartVertexStrip(desc) KMSTATUS_SUCCESS;{										\
	register KMDWORD StructSize = ((PKMCURRENTLISTSTATE)(desc)->pCurrentListState)->GlobalParamSize; \
	kmyMemCopy(pkmCurrentPtr,	(PKMDWORD)((desc)->pGlobalParam), StructSize);		\
	prefetch((void *)pkmCurrentPtr);														\
	if(StructSize == 0x40) prefetch((void *)(pkmCurrentPtr + 8));							\
	pkmCurrentPtr += (StructSize >> 2);														\
}

#define kmxxStartStrip( _pDesc_,_pHead_ )		KMSTATUS_SUCCESS;	{						\
	KMDWORD ListType;																		\
	PKMDWORD pDST;																			\
	*pkmCurrentListPtr += ((KMDWORD)pkmCurrentPtr - (KMDWORD)pkmStartPtr); 					\
	ListType   = ((((PKMSTRIPHEAD)(_pHead_))->dwStripHead[0]) >> 24) & 7;					\
	((PKMCURRENTLISTSTATE)(_pDesc_)->pCurrentListState)->ListType = ListType;				\
	pkmCurrentListPtr = (PKMDWORD)((_pDesc_)->pCurrentPtr + ListType) ; 					\
	pkmStartPtr = pkmCurrentPtr = KMI_GET_MAPPING_ADDRESS(*pkmCurrentListPtr);				\
	if(((PKMSTRIPHEAD)_pHead_)->dwStripHead[0] & 0x00001400)								\
	{	kmyMemCopy( pkmCurrentPtr,	(PKMDWORD)(((PKMSTRIPHEAD)(_pHead_))->dwStripHead), 0x40);\
		prefetch((void *)pkmCurrentPtr);													\
		prefetch((void *)(pkmCurrentPtr + 8));												\
		pkmCurrentPtr  += (16);																\
	}else{																					\
		kmyMemCopy( pkmCurrentPtr,	(PKMDWORD)(((PKMSTRIPHEAD)(_pHead_))->dwStripHead), 0x20);\
		prefetch((void *)pkmCurrentPtr);													\
		pkmCurrentPtr  += (8);																\
	}																						\
	}

#define kmxxReleaseCurrentPtr(desc)															\
	*pkmCurrentListPtr += ((KMDWORD)pkmCurrentPtr - (KMDWORD)pkmStartPtr);									\
}

#define kmxxSetVertex_0(pcw, x, y, invw, pkdcol)								\
		((PKMVERTEX0)(pkmCurrentPtr))->ParamControlWord = pcw;					\
		((PKMVERTEX0)(pkmCurrentPtr))->fX				= x;					\
		((PKMVERTEX0)(pkmCurrentPtr))->fY				= y;					\
		((PKMVERTEX0)(pkmCurrentPtr))->u.fZ				= invw;					\
		((PKMVERTEX0)(pkmCurrentPtr))->uBaseRGB.dwPacked			= pkdcol;				\
		prefetch((void *)pkmCurrentPtr);										\
		pkmCurrentPtr += (sizeof(KMVERTEX0) / sizeof(KMDWORD));

#define kmxxSetVertex_1(pcw, x, y, invw, Alpha, Red, Green, Blue)				\
		((PKMVERTEX1)(pkmCurrentPtr))->ParamControlWord	= pcw;					\
		((PKMVERTEX1)(pkmCurrentPtr))->fX				= x;					\
		((PKMVERTEX1)(pkmCurrentPtr))->fY				= y;					\
		((PKMVERTEX1)(pkmCurrentPtr))->u.fZ				= invw;					\
		((PKMVERTEX1)(pkmCurrentPtr))->fBaseAlpha		= Alpha;				\
		((PKMVERTEX1)(pkmCurrentPtr))->fBaseRed			= Red;					\
		((PKMVERTEX1)(pkmCurrentPtr))->fBaseGreen		= Green;				\
		((PKMVERTEX1)(pkmCurrentPtr))->fBaseBlue		= Blue;					\
		prefetch((void *)pkmCurrentPtr);										\
		pkmCurrentPtr += (sizeof(KMVERTEX1) / sizeof(KMDWORD));

#define kmxxSetVertex_2(pcw, x, y, invw, bi )									\
		((PKMVERTEX2)(pkmCurrentPtr))->ParamControlWord	= pcw;					\
		((PKMVERTEX2)(pkmCurrentPtr))->fX				= x;					\
		((PKMVERTEX2)(pkmCurrentPtr))->fY				= y;					\
		((PKMVERTEX2)(pkmCurrentPtr))->u.fZ				= invw;					\
		((PKMVERTEX2)(pkmCurrentPtr))->fBaseIntensity	= bi;					\
		prefetch((void *)pkmCurrentPtr);										\
		pkmCurrentPtr += (sizeof(KMVERTEX2) / sizeof(KMDWORD));

#define kmxxSetVertex_3(pcw, x, y, invw, fu, fv, bcol, ocol)					\
		((PKMVERTEX3)(pkmCurrentPtr))->ParamControlWord	= pcw;					\
		((PKMVERTEX3)(pkmCurrentPtr))->fX				= x;					\
		((PKMVERTEX3)(pkmCurrentPtr))->fY				= y;					\
		((PKMVERTEX3)(pkmCurrentPtr))->u.fZ				= invw;					\
		((PKMVERTEX3)(pkmCurrentPtr))->fU				= fu;					\
		((PKMVERTEX3)(pkmCurrentPtr))->fV				= fv;					\
		((PKMVERTEX3)(pkmCurrentPtr))->uBaseRGB.dwPacked			= bcol;					\
		((PKMVERTEX3)(pkmCurrentPtr))->uOffsetRGB.dwPacked		= ocol;					\
		prefetch((void *)pkmCurrentPtr);										\
		pkmCurrentPtr += (sizeof(KMVERTEX3) / sizeof(KMDWORD));

#define kmxxSetVertex_4(pcw, x, y, invw, uv, bcol, ocol)						\
		((PKMVERTEX4)(pkmCurrentPtr))->ParamControlWord	= pcw;					\
		((PKMVERTEX4)(pkmCurrentPtr))->fX				= x;					\
		((PKMVERTEX4)(pkmCurrentPtr))->fY				= y;					\
		((PKMVERTEX4)(pkmCurrentPtr))->u.fZ				= invw;					\
		((PKMVERTEX4)(pkmCurrentPtr))->dwUV				= uv;					\
		((PKMVERTEX4)(pkmCurrentPtr))->uBaseRGB.dwPacked			= bcol;					\
		((PKMVERTEX4)(pkmCurrentPtr))->uOffsetRGB.dwPacked		= ocol;					\
		prefetch((void *)pkmCurrentPtr);										\
		pkmCurrentPtr += (sizeof(KMVERTEX4) / sizeof(KMDWORD));

#define kmxxSetVertex_5(pcw, x, y,invw, fu, fv, ba, br, bg, bb, oa, or, og, ob)	\
		((PKMVERTEX5)(pkmCurrentPtr))->ParamControlWord	= pcw;					\
		((PKMVERTEX5)(pkmCurrentPtr))->fX				= x;					\
		((PKMVERTEX5)(pkmCurrentPtr))->fY				= y;					\
		((PKMVERTEX5)(pkmCurrentPtr))->u.fZ				= invw;					\
		((PKMVERTEX5)(pkmCurrentPtr))->fU				= fu;					\
		((PKMVERTEX5)(pkmCurrentPtr))->fV				= fv;					\
		((PKMVERTEX5)(pkmCurrentPtr))->fBaseAlpha		= ba;					\
		((PKMVERTEX5)(pkmCurrentPtr))->fBaseRed			= br;					\
		prefetch((void *)pkmCurrentPtr);										\
		((PKMVERTEX5)(pkmCurrentPtr))->fBaseGreen		= bg;					\
		((PKMVERTEX5)(pkmCurrentPtr))->fBaseBlue		= bb;					\
		((PKMVERTEX5)(pkmCurrentPtr))->fOffsetAlpha		= oa;					\
		((PKMVERTEX5)(pkmCurrentPtr))->fOffsetRed		= or;					\
		((PKMVERTEX5)(pkmCurrentPtr))->fOffsetGreen		= og;					\
		((PKMVERTEX5)(pkmCurrentPtr))->fOffsetBlue		= ob;					\
		prefetch((void *)(pkmCurrentPtr+8));									\
		pkmCurrentPtr += (sizeof(KMVERTEX5) / sizeof(KMDWORD));

#define kmxxSetVertex_6(pcw, x, y, invw, uv, ba, br, bg, bb, oa, or, og, ob)	\
		((PKMVERTEX6)(pkmCurrentPtr))->ParamControlWord	= pcw;					\
		((PKMVERTEX6)(pkmCurrentPtr))->fX				= x;					\
		((PKMVERTEX6)(pkmCurrentPtr))->fY				= y;					\
		((PKMVERTEX6)(pkmCurrentPtr))->u.fZ				= invw;					\
		((PKMVERTEX6)(pkmCurrentPtr))->dwUV				= uv;					\
		((PKMVERTEX6)(pkmCurrentPtr))->fBaseAlpha		= ba;					\
		((PKMVERTEX6)(pkmCurrentPtr))->fBaseRed			= br;					\
		((PKMVERTEX6)(pkmCurrentPtr))->fBaseGreen		= bg;					\
		prefetch((void *)pkmCurrentPtr);										\
		((PKMVERTEX6)(pkmCurrentPtr))->fBaseBlue		= bb;					\
		((PKMVERTEX6)(pkmCurrentPtr))->fOffsetAlpha		= oa;					\
		((PKMVERTEX6)(pkmCurrentPtr))->fOffsetRed		= or;					\
		((PKMVERTEX6)(pkmCurrentPtr))->fOffsetGreen		= og;					\
		((PKMVERTEX6)(pkmCurrentPtr))->fOffsetBlue		= ob;					\
		prefetch((void *)(pkmCurrentPtr+8));									\
		pkmCurrentPtr += (sizeof(KMVERTEX6) / sizeof(KMDWORD));

#define kmxxSetVertex_7(pcw, x, y, invw, fu, fv, bi, oi)						\
		((PKMVERTEX7)(pkmCurrentPtr))->ParamControlWord	= pcw;					\
		((PKMVERTEX7)(pkmCurrentPtr))->fX				= x;					\
		((PKMVERTEX7)(pkmCurrentPtr))->fY				= y;					\
		((PKMVERTEX7)(pkmCurrentPtr))->u.fZ				= invw;					\
		((PKMVERTEX7)(pkmCurrentPtr))->fU				= fu;					\
		((PKMVERTEX7)(pkmCurrentPtr))->fV				= fv;					\
		((PKMVERTEX7)(pkmCurrentPtr))->fBaseIntensity	= bi;					\
		((PKMVERTEX7)(pkmCurrentPtr))->fOffsetIntensity	= oi;					\
		prefetch((void *)pkmCurrentPtr);										\
		pkmCurrentPtr += (sizeof(KMVERTEX7) / sizeof(KMDWORD));

#define kmxxSetVertex_8(pcw, x, y, invw, uv, bi, oi)							\
		((PKMVERTEX8)(pkmCurrentPtr))->ParamControlWord	= pcw;					\
		((PKMVERTEX8)(pkmCurrentPtr))->fX				= x;					\
		((PKMVERTEX8)(pkmCurrentPtr))->fY				= y;					\
		((PKMVERTEX8)(pkmCurrentPtr))->u.fZ				= invw;					\
		((PKMVERTEX8)(pkmCurrentPtr))->dwUV				= uv;					\
		((PKMVERTEX8)(pkmCurrentPtr))->fBaseIntensity	= bi;					\
		((PKMVERTEX8)(pkmCurrentPtr))->fOffsetIntensity	= oi;					\
		prefetch((void *)pkmCurrentPtr);										\
		pkmCurrentPtr += (sizeof(KMVERTEX8) / sizeof(KMDWORD));

#define kmxxSetVertex_9(pcw, x, y, invw, m0col, m1col)							\
		((PKMVERTEX9)(pkmCurrentPtr))->ParamControlWord	= pcw;					\
		((PKMVERTEX9)(pkmCurrentPtr))->fX				= x;					\
		((PKMVERTEX9)(pkmCurrentPtr))->fY				= y;					\
		((PKMVERTEX9)(pkmCurrentPtr))->u.fZ				= invw;					\
		((PKMVERTEX9)(pkmCurrentPtr))->uBaseRGB0m.dwPacked		= m0col;				\
		((PKMVERTEX9)(pkmCurrentPtr))->uBaseRGB1m.dwPacked		= m1col;				\
		prefetch((void *)pkmCurrentPtr);										\
		pkmCurrentPtr += (sizeof(KMVERTEX9) / sizeof(KMDWORD));

#define kmxxSetVertex_10(pcw, x, y, invw, m0bi, m1bi)							\
		((PKMVERTEX10)(pkmCurrentPtr))->ParamControlWord= pcw;					\
		((PKMVERTEX10)(pkmCurrentPtr))->fX				= x;					\
		((PKMVERTEX10)(pkmCurrentPtr))->fY				= y;					\
		((PKMVERTEX10)(pkmCurrentPtr))->u.fZ			= invw;					\
		((PKMVERTEX10)(pkmCurrentPtr))->fBaseIntensity0m= m0bi;					\
		((PKMVERTEX10)(pkmCurrentPtr))->fBaseIntensity1m= m1bi;					\
		prefetch((void *)pkmCurrentPtr);										\
		pkmCurrentPtr += (sizeof(KMVERTEX10) / sizeof(KMDWORD));

#define kmxxSetVertex_11(pcw, x, y, invw, um0, vm0, bcolm0, ocolm0, um1, vm1, bcolm1, ocolm1)		\
		((PKMVERTEX11)(pkmCurrentPtr))->ParamControlWord	= pcw;				\
		((PKMVERTEX11)(pkmCurrentPtr))->fX					= x;				\
		((PKMVERTEX11)(pkmCurrentPtr))->fY					= y;				\
		((PKMVERTEX11)(pkmCurrentPtr))->u.fZ				= invw;				\
		((PKMVERTEX11)(pkmCurrentPtr))->fU0m				= um0;				\
		((PKMVERTEX11)(pkmCurrentPtr))->fV0m				= vm0;				\
		((PKMVERTEX11)(pkmCurrentPtr))->uBaseRGB0m.dwPacked			= bcolm0;			\
		((PKMVERTEX11)(pkmCurrentPtr))->uOffsetRGB0m.dwPacked		= ocolm0;			\
		prefetch((void *)pkmCurrentPtr);										\
		((PKMVERTEX11)(pkmCurrentPtr))->fU1m				= um1;				\
		((PKMVERTEX11)(pkmCurrentPtr))->fV1m				= vm1;				\
		((PKMVERTEX11)(pkmCurrentPtr))->uBaseRGB1m.dwPacked			= bcolm1;			\
		((PKMVERTEX11)(pkmCurrentPtr))->uOffsetRGB1m.dwPacked		= ocolm1;			\
		prefetch((void *)(pkmCurrentPtr+8));									\
		pkmCurrentPtr += (sizeof(KMVERTEX11) / sizeof(KMDWORD));

#define kmxxSetVertex_12(pcw, x, y, invw, uvm0, bcolm0, ocolm0, uvm1, bcolm1, ocolm1)				\
		((PKMVERTEX12)(pkmCurrentPtr))->ParamControlWord	= pcw;				\
		((PKMVERTEX12)(pkmCurrentPtr))->fX					= x;				\
		((PKMVERTEX12)(pkmCurrentPtr))->fY					= y;				\
		((PKMVERTEX12)(pkmCurrentPtr))->u.fZ				= invw;				\
		((PKMVERTEX12)(pkmCurrentPtr))->dwUV0m				= uvm0;				\
		((PKMVERTEX12)(pkmCurrentPtr))->uBaseRGB0m.dwPacked			= bcolm0;			\
		((PKMVERTEX12)(pkmCurrentPtr))->uOffsetRGB0m.dwPacked		= ocolm0;			\
		((PKMVERTEX12)(pkmCurrentPtr))->dwUV1m				= uvm1;				\
		prefetch((void *)pkmCurrentPtr);										\
		((PKMVERTEX12)(pkmCurrentPtr))->uBaseRGB1m.dwPacked			= bcolm1;			\
		((PKMVERTEX12)(pkmCurrentPtr))->uOffsetRGB1m.dwPacked		= ocolm1;			\
		prefetch((void *)(pkmCurrentPtr+8));										\
		pkmCurrentPtr += (sizeof(KMVERTEX12) / sizeof(KMDWORD));

#define kmxxSetVertex_13(pcw, x, y, invw, um0, vm0, bim0, oim0, um1, vm1, bim1, oim1)					\
		((PKMVERTEX13)(pkmCurrentPtr))->ParamControlWord	= pcw;				\
		((PKMVERTEX13)(pkmCurrentPtr))->fX					= x;				\
		((PKMVERTEX13)(pkmCurrentPtr))->fY					= y;				\
		((PKMVERTEX13)(pkmCurrentPtr))->u.fZ				= invw;				\
		((PKMVERTEX13)(pkmCurrentPtr))->fU0m				= um0;				\
		((PKMVERTEX13)(pkmCurrentPtr))->fV0m				= vm0;				\
		((PKMVERTEX13)(pkmCurrentPtr))->fBaseIntensity0m	= bim0;				\
		((PKMVERTEX13)(pkmCurrentPtr))->fOffsetIntensity0m	= oim0;				\
		prefetch((void *)pkmCurrentPtr);										\
		((PKMVERTEX13)(pkmCurrentPtr))->fU1m				= um1;				\
		((PKMVERTEX13)(pkmCurrentPtr))->fV1m				= vm1;				\
		((PKMVERTEX13)(pkmCurrentPtr))->fBaseIntensity1m	= bim1;				\
		((PKMVERTEX13)(pkmCurrentPtr))->fOffsetIntensity0m	= oim1;				\
		prefetch((void *)(pkmCurrentPtr+8));										\
		pkmCurrentPtr += (sizeof(KMVERTEX13) / sizeof(KMDWORD));

#define kmxxSetVertex_14(pcw, x, y, invw, uvm0, bim0, oim0, uvm1, bim1, oim1)	\
		((PKMVERTEX14)(pkmCurrentPtr))->ParamControlWord	= pcw;				\
		((PKMVERTEX14)(pkmCurrentPtr))->fX					= x;				\
		((PKMVERTEX14)(pkmCurrentPtr))->fY					= y;				\
		((PKMVERTEX14)(pkmCurrentPtr))->u.fZ				= invw;				\
		((PKMVERTEX14)(pkmCurrentPtr))->dwUV0m				= uvm0;				\
		((PKMVERTEX14)(pkmCurrentPtr))->fBaseIntensity0m	= bim0;				\
		((PKMVERTEX14)(pkmCurrentPtr))->fOffsetIntensity0m	= oim0;				\
		((PKMVERTEX14)(pkmCurrentPtr))->dwUV1m				= uvm1;				\
		prefetch((void *)pkmCurrentPtr);										\
		((PKMVERTEX14)(pkmCurrentPtr))->fBaseIntensity1m	= bim1;				\
		((PKMVERTEX14)(pkmCurrentPtr))->fOffsetIntensity0m	= oim1;				\
		prefetch((void *)(pkmCurrentPtr+8));									\
		pkmCurrentPtr += (sizeof(KMVERTEX14) / sizeof(KMDWORD));

#define kmxxSetVertex_15(pcw, xa, ya, invwa, xb, yb, invwb, xc, yc, invwc, xd, yd)	\
		((PKMVERTEX15)(pkmCurrentPtr))->ParamControlWord	= pcw;				\
		((PKMVERTEX15)(pkmCurrentPtr))->fAX					= xa;				\
		((PKMVERTEX15)(pkmCurrentPtr))->fAY					= ya;				\
		((PKMVERTEX15)(pkmCurrentPtr))->uA.fAZ				= invwa;			\
		((PKMVERTEX15)(pkmCurrentPtr))->fBX					= xb;				\
		((PKMVERTEX15)(pkmCurrentPtr))->fBY					= yb;				\
		((PKMVERTEX15)(pkmCurrentPtr))->uB.fBZ				= invwb;			\
		((PKMVERTEX15)(pkmCurrentPtr))->fCX					= xc;				\
		prefetch((void *)pkmCurrentPtr);										\
		((PKMVERTEX15)(pkmCurrentPtr))->fCY					= yc;				\
		((PKMVERTEX15)(pkmCurrentPtr))->uC.fCZ				= invwc;			\
		((PKMVERTEX15)(pkmCurrentPtr))->fDX					= xd;				\
		((PKMVERTEX15)(pkmCurrentPtr))->fDY					= yd;				\
		prefetch((void *)(pkmCurrentPtr+8));									\
		pkmCurrentPtr += (sizeof(KMVERTEX15) / sizeof(KMDWORD));

#define kmxxSetVertex_16(pcw, xa, ya, invwa, xb, yb, invwb, xc, yc, invwc, xd, yd, uva, uvb, uvc )	\
		((PKMVERTEX16)(pkmCurrentPtr))->ParamControlWord	= pcw;				\
		((PKMVERTEX16)(pkmCurrentPtr))->fAX					= xa;				\
		((PKMVERTEX16)(pkmCurrentPtr))->fAY					= ya;				\
		((PKMVERTEX16)(pkmCurrentPtr))->uA.fAZ				= invwa;			\
		((PKMVERTEX16)(pkmCurrentPtr))->fBX					= xb;				\
		((PKMVERTEX16)(pkmCurrentPtr))->fBY					= yb;				\
		((PKMVERTEX16)(pkmCurrentPtr))->uB.fBZ				= invwb;			\
		((PKMVERTEX16)(pkmCurrentPtr))->fCX					= xc;				\
		prefetch((void *)pkmCurrentPtr);										\
		((PKMVERTEX16)(pkmCurrentPtr))->fCY					= yc;				\
		((PKMVERTEX16)(pkmCurrentPtr))->uC.fCZ				= invwc;			\
		((PKMVERTEX16)(pkmCurrentPtr))->fDX					= xd;				\
		((PKMVERTEX16)(pkmCurrentPtr))->fDY					= yd;				\
		((PKMVERTEX16)(pkmCurrentPtr))->dwUVA				= uva;				\
		((PKMVERTEX16)(pkmCurrentPtr))->dwUVB				= uvb;				\
		((PKMVERTEX16)(pkmCurrentPtr))->dwUVC				= uvc;				\
		prefetch((void *)(pkmCurrentPtr+8));									\
		pkmCurrentPtr += (sizeof(KMVERTEX16) / sizeof(KMDWORD));

#define kmxxSetVertex_17(pcw, xa, ya, invwa, xb, yb, invwb, xc, yc, invwc)		\
		((PKMVERTEX17)(pkmCurrentPtr))->ParamControlWord	= pcw;				\
		((PKMVERTEX17)(pkmCurrentPtr))->fAX					= xa;				\
		((PKMVERTEX17)(pkmCurrentPtr))->fAY					= ya;				\
		((PKMVERTEX17)(pkmCurrentPtr))->uA.fAZ				= invwa;			\
		((PKMVERTEX17)(pkmCurrentPtr))->fBX					= xb;				\
		((PKMVERTEX17)(pkmCurrentPtr))->fBY					= yb;				\
		((PKMVERTEX17)(pkmCurrentPtr))->uB.fBZ				= invwb;			\
		((PKMVERTEX17)(pkmCurrentPtr))->fCX					= xc;				\
		prefetch((void *)pkmCurrentPtr);										\
		((PKMVERTEX17)(pkmCurrentPtr))->fCY					= yc;				\
		((PKMVERTEX17)(pkmCurrentPtr))->uC.fCZ				= invwc;			\
		prefetch((void *)(pkmCurrentPtr+8));									\
		pkmCurrentPtr += (sizeof(KMVERTEX17) / sizeof(KMDWORD));

#endif /* WIN32 */

#endif	/* _L3_ */


#if !defined(_KM_USE_VERTEX_MACRO_L3_) && defined(_KM_USE_VERTEX_MACRO_L4_)
#define kmxxGetCurrentPtr(desc)																\
{																							\
	register PKMDWORD pkmCurrentPtr;														\
	PKMDWORD pkmCurrentListPtr;																\
	PKMDWORD pkmStartPtr;																		\
	pkmCurrentListPtr = (PKMDWORD)((desc)->pCurrentPtr + ((PKMCURRENTLISTSTATE)(desc)->pCurrentListState)->ListType); \
	pkmStartPtr = pkmCurrentPtr = KMI_GET_MAPPING_ADDRESS(*pkmCurrentListPtr);

#define kmxxStartVertexStrip(desc) KMSTATUS_SUCCESS;{										\
	register KMDWORD StructSize = ((PKMCURRENTLISTSTATE)(desc)->pCurrentListState)->GlobalParamSize; \
	kmyMemCopy(pkmCurrentPtr,	(PKMDWORD)((desc)->pGlobalParam), StructSize);		\
	prefetch((void *)pkmCurrentPtr);														\
	if(StructSize == 0x40) prefetch((void *)(pkmCurrentPtr + 8));							\
	pkmCurrentPtr += (StructSize >> 2);														\
}

#define kmxxStartStrip( _pDesc_,_pHead_ )		KMSTATUS_SUCCESS;	{						\
	KMDWORD ListType;																		\
	PKMDWORD pDST;																			\
	*pkmCurrentListPtr += ((KMDWORD)pkmCurrentPtr - (KMDWORD)pkmStartPtr); 					\
	ListType   = ((((PKMSTRIPHEAD)(_pHead_))->dwStripHead[0]) >> 24) & 7;					\
	((PKMCURRENTLISTSTATE)(_pDesc_)->pCurrentListState)->ListType = ListType;				\
	pkmCurrentListPtr = (PKMDWORD)((_pDesc_)->pCurrentPtr + ListType) ; 					\
	pkmStartPtr = pkmCurrentPtr = KMI_GET_MAPPING_ADDRESS(*pkmCurrentListPtr);				\
	if(((PKMSTRIPHEAD)_pHead_)->dwStripHead[0] & 0x00001400)								\
	{	kmyMemCopy( pkmCurrentPtr,	(PKMDWORD)(((PKMSTRIPHEAD)(_pHead_))->dwStripHead), 0x40);\
		prefetch((void *)pkmCurrentPtr);													\
		prefetch((void *)(pkmCurrentPtr + 8));												\
		pkmCurrentPtr  += (16);																\
	}else{																					\
		kmyMemCopy( pkmCurrentPtr,	(PKMDWORD)(((PKMSTRIPHEAD)(_pHead_))->dwStripHead), 0x20);\
		prefetch((void *)pkmCurrentPtr);													\
		pkmCurrentPtr  += (8);																\
	}																						\
	}

#define kmxxReleaseCurrentPtr(desc)															\
	*pkmCurrentListPtr += ((KMDWORD)pkmCurrentPtr - (KMDWORD)pkmStartPtr);									\
}

#define kmxxSetVertex_0(pcw, x, y, invw, pkdcol)								\
		*pkmCurrentPtr++ = pcw;													\
		*(PKMFLOAT)pkmCurrentPtr++ = x;													\
		*(PKMFLOAT)pkmCurrentPtr++ = y;													\
		*(PKMFLOAT)pkmCurrentPtr++ = invw;												\
		*pkmCurrentPtr   = pkdcol;												\
		pkmCurrentPtr  += 2;													\
		*pkmCurrentPtr   = pkdcol;												\
		prefetch((void *)pkmCurrentPtr);										\
		pkmCurrentPtr  += 2;

#define kmxxSetVertex_1(pcw, x, y, invw, Alpha, Red, Green, Blue)				\
		*pkmCurrentPtr++ = pcw;													\
		*(PKMFLOAT)pkmCurrentPtr++ = x;													\
		*(PKMFLOAT)pkmCurrentPtr++ = y;													\
		*(PKMFLOAT)pkmCurrentPtr++ = invw;												\
		*(PKMFLOAT)pkmCurrentPtr++ = Alpha;												\
		*(PKMFLOAT)pkmCurrentPtr++ = Red;													\
		*(PKMFLOAT)pkmCurrentPtr++ = Green;												\
		*(PKMFLOAT)pkmCurrentPtr   = Blue;												\
		prefetch((void *)pkmCurrentPtr);										\
		pkmCurrentPtr++;

#define kmxxSetVertex_2(pcw, x, y, invw, bi )									\
		*pkmCurrentPtr++ = pcw;													\
		*(PKMFLOAT)pkmCurrentPtr++ = x;													\
		*(PKMFLOAT)pkmCurrentPtr++ = y;													\
		*(PKMFLOAT)pkmCurrentPtr++ = invw;												\
		*(PKMFLOAT)pkmCurrentPtr	 = bi;													\
		pkmCurrentPtr 	+= 2;													\
		*(PKMFLOAT)pkmCurrentPtr	 = bi;													\
		prefetch((void *)pkmCurrentPtr);										\
		pkmCurrentPtr += 2;

#define kmxxSetVertex_3(pcw, x, y, invw, fu, fv, bcol, ocol)					\
		*pkmCurrentPtr++ = pcw;													\
		*(PKMFLOAT)pkmCurrentPtr++ = x;													\
		*(PKMFLOAT)pkmCurrentPtr++ = y;													\
		*(PKMFLOAT)pkmCurrentPtr++ = invw;												\
		*(PKMFLOAT)pkmCurrentPtr++ = fu;													\
		*(PKMFLOAT)pkmCurrentPtr++ = fv;													\
		*pkmCurrentPtr++ = bcol;												\
		*pkmCurrentPtr   = ocol;												\
		prefetch((void *)pkmCurrentPtr);										\
		pkmCurrentPtr++;

#define kmxxSetVertex_4(pcw, x, y, invw, uv, bcol, ocol)						\
		*pkmCurrentPtr++ = pcw;													\
		*(PKMFLOAT)pkmCurrentPtr++ = x;													\
		*(PKMFLOAT)pkmCurrentPtr++ = y;													\
		*(PKMFLOAT)pkmCurrentPtr++ = invw;												\
		*pkmCurrentPtr	 = uv;													\
		pkmCurrentPtr  += 2;													\
		*pkmCurrentPtr++ = bcol;												\
		*pkmCurrentPtr	 = ocol;												\
		prefetch((void *)pkmCurrentPtr);										\
		pkmCurrentPtr++;

#define kmxxSetVertex_5(pcw, x, y,invw, fu, fv, ba, br, bg, bb, oa, or, og, ob)	\
		*pkmCurrentPtr++ = pcw;					\
		*(PKMFLOAT)pkmCurrentPtr++ = x;					\
		*(PKMFLOAT)pkmCurrentPtr++ = y;					\
		*(PKMFLOAT)pkmCurrentPtr++ = invw;				\
		*(PKMFLOAT)pkmCurrentPtr++ = fu;					\
		*(PKMFLOAT)pkmCurrentPtr   = fv;					\
		prefetch((void *)pkmCurrentPtr);		\
		pkmCurrentPtr   += 3;					\
		*(PKMFLOAT)pkmCurrentPtr++ = ba;					\
		*(PKMFLOAT)pkmCurrentPtr++ = br;					\
		*(PKMFLOAT)pkmCurrentPtr++ = bg;					\
		*(PKMFLOAT)pkmCurrentPtr++ = bb;					\
		*(PKMFLOAT)pkmCurrentPtr++ = oa;					\
		*(PKMFLOAT)pkmCurrentPtr++ = or;					\
		*(PKMFLOAT)pkmCurrentPtr++ = og;					\
		*(PKMFLOAT)pkmCurrentPtr = ob;					\
		prefetch((void *)pkmCurrentPtr);		\
		pkmCurrentPtr++;

#define kmxxSetVertex_6(pcw, x, y, invw, uv, ba, br, bg, bb, oa, or, og, ob)	\
		*pkmCurrentPtr++ = pcw;					\
		*(PKMFLOAT)pkmCurrentPtr++ = x;					\
		*(PKMFLOAT)pkmCurrentPtr++ = y;					\
		*(PKMFLOAT)pkmCurrentPtr++ = invw;				\
		*pkmCurrentPtr   = uv;					\
		prefetch((void *)pkmCurrentPtr);		\
		pkmCurrentPtr   += 4;					\
		*(PKMFLOAT)pkmCurrentPtr++ = ba;					\
		*(PKMFLOAT)pkmCurrentPtr++ = br;					\
		*(PKMFLOAT)pkmCurrentPtr++ = bg;					\
		*(PKMFLOAT)pkmCurrentPtr++ = bb;					\
		*(PKMFLOAT)pkmCurrentPtr++ = oa;					\
		*(PKMFLOAT)pkmCurrentPtr++ = or;					\
		*(PKMFLOAT)pkmCurrentPtr++ = og;					\
		*(PKMFLOAT)pkmCurrentPtr   = ob;					\
		prefetch((void *)pkmCurrentPtr);		\
		pkmCurrentPtr++;

#define kmxxSetVertex_7(pcw, x, y, invw, fu, fv, bi, oi)						\
		*pkmCurrentPtr++ = pcw;													\
		*(PKMFLOAT)pkmCurrentPtr++ = x;													\
		*(PKMFLOAT)pkmCurrentPtr++ = y;													\
		*(PKMFLOAT)pkmCurrentPtr++ = invw;												\
		*(PKMFLOAT)pkmCurrentPtr++ = fu;													\
		*(PKMFLOAT)pkmCurrentPtr++ = fv;													\
		*(PKMFLOAT)pkmCurrentPtr++ = bi;												\
		*(PKMFLOAT)pkmCurrentPtr   = oi;												\
		prefetch((void *)pkmCurrentPtr);										\
		pkmCurrentPtr++;

#define kmxxSetVertex_8(pcw, x, y, invw, uv, bi, oi)							\
		*pkmCurrentPtr++ = pcw;													\
		*(PKMFLOAT)pkmCurrentPtr++ = x;													\
		*(PKMFLOAT)pkmCurrentPtr++ = y;													\
		*(PKMFLOAT)pkmCurrentPtr++ = invw;												\
		*pkmCurrentPtr 	 = uv;													\
		pkmCurrentPtr 	+= 2;													\
		*(PKMFLOAT)pkmCurrentPtr++ = bi;													\
		*(PKMFLOAT)pkmCurrentPtr   = oi;													\
		prefetch((void *)pkmCurrentPtr);										\
		pkmCurrentPtr++;

#define kmxxSetVertex_9(pcw, x, y, invw, m0col, m1col)							\
		*pkmCurrentPtr++ = pcw;													\
		*(PKMFLOAT)pkmCurrentPtr++ = x;													\
		*(PKMFLOAT)pkmCurrentPtr++ = y;													\
		*(PKMFLOAT)pkmCurrentPtr++ = invw;												\
		*pkmCurrentPtr++ = m0col;												\
		*pkmCurrentPtr++ = m1col;												\
		prefetch((void *)pkmCurrentPtr);										\
		pkmCurrentPtr += 2;

#define kmxxSetVertex_10(pcw, x, y, invw, m0bi, m1bi)							\
		*pkmCurrentPtr++ = pcw;													\
		*(PKMFLOAT)pkmCurrentPtr++ = x;													\
		*(PKMFLOAT)pkmCurrentPtr++ = y;													\
		*(PKMFLOAT)pkmCurrentPtr++ = invw;												\
		*(PKMFLOAT)pkmCurrentPtr++ = m0bi;												\
		*(PKMFLOAT)pkmCurrentPtr++ = m1bi;												\
		prefetch((void *)pkmCurrentPtr);										\
		pkmCurrentPtr += 2;

#define kmxxSetVertex_11(pcw, x, y, invw, um0, vm0, bcolm0, ocolm0, um1, vm1, bcolm1, ocolm1)		\
		*pkmCurrentPtr++ = pcw;													\
		*(PKMFLOAT)pkmCurrentPtr++ = x;													\
		*(PKMFLOAT)pkmCurrentPtr++ = y;													\
		*(PKMFLOAT)pkmCurrentPtr++ = invw;												\
		*(PKMFLOAT)pkmCurrentPtr++ = um0;													\
		*(PKMFLOAT)pkmCurrentPtr++ = vm0;													\
		*pkmCurrentPtr++ = bcolm0;												\
		*pkmCurrentPtr   = ocolm0;												\
		prefetch((void *)pkmCurrentPtr);										\
		pkmCurrentPtr++;														\
		*(PKMFLOAT)pkmCurrentPtr++ = um1;													\
		*(PKMFLOAT)pkmCurrentPtr++ = vm1;													\
		*pkmCurrentPtr++ = bcolm1;												\
		*pkmCurrentPtr++ = ocolm1;												\
		prefetch((void *)pkmCurrentPtr);										\
		pkmCurrentPtr += 4;

#define kmxxSetVertex_12(pcw, x, y, invw, uvm0, bcolm0, ocolm0, uvm1, bcolm1, ocolm1)				\
		*pkmCurrentPtr++ = pcw;													\
		*(PKMFLOAT)pkmCurrentPtr++ = x;													\
		*(PKMFLOAT)pkmCurrentPtr++ = y;													\
		*(PKMFLOAT)pkmCurrentPtr++ = invw;												\
		*pkmCurrentPtr++ = uvm0;												\
		pkmCurrentPtr++;														\
		*pkmCurrentPtr++ = bcolm0;												\
		*pkmCurrentPtr   = ocolm0;												\
		prefetch((void *)pkmCurrentPtr);										\
		pkmCurrentPtr++;														\
		*pkmCurrentPtr++ = uvm1;												\
		pkmCurrentPtr++;														\
		*pkmCurrentPtr++ = bcolm1;												\
		*pkmCurrentPtr++ = ocolm1;												\
		prefetch((void *)pkmCurrentPtr);										\
		pkmCurrentPtr += 4;

#define kmxxSetVertex_13(pcw, x, y, invw, um0, vm0, bim0, oim0, um1, vm1, bim1, oim1)					\
		*pkmCurrentPtr++ = pcw;													\
		*(PKMFLOAT)pkmCurrentPtr++ = x;													\
		*(PKMFLOAT)pkmCurrentPtr++ = y;													\
		*(PKMFLOAT)pkmCurrentPtr++ = invw;												\
		*(PKMFLOAT)pkmCurrentPtr++ = um0;													\
		*(PKMFLOAT)pkmCurrentPtr++ = vm0;													\
		*(PKMFLOAT)pkmCurrentPtr++ = bim0;												\
		*(PKMFLOAT)pkmCurrentPtr   = oim0;												\
		prefetch((void *)pkmCurrentPtr);										\
		pkmCurrentPtr++;														\
		*(PKMFLOAT)pkmCurrentPtr++ = um1;													\
		*(PKMFLOAT)pkmCurrentPtr++ = vm1;													\
		*(PKMFLOAT)pkmCurrentPtr++ = bim1;												\
		*(PKMFLOAT)pkmCurrentPtr++ = oim1;												\
		prefetch((void *)pkmCurrentPtr);									\
		pkmCurrentPtr += 4;

#define kmxxSetVertex_14(pcw, x, y, invw, uvm0, bim0, oim0, uvm1, bim1, oim1)	\
		*pkmCurrentPtr++ = pcw;													\
		*(PKMFLOAT)pkmCurrentPtr++ = x;													\
		*(PKMFLOAT)pkmCurrentPtr++ = y;													\
		*(PKMFLOAT)pkmCurrentPtr++ = invw;												\
		*pkmCurrentPtr++ = uvm0;												\
		pkmCurrentPtr++;														\
		*(PKMFLOAT)pkmCurrentPtr++ = bim0;												\
		*(PKMFLOAT)pkmCurrentPtr   = oim0;												\
		prefetch((void *)pkmCurrentPtr);										\
		pkmCurrentPtr++;														\
		*pkmCurrentPtr++ = uvm1;												\
		pkmCurrentPtr++;													\
		*(PKMFLOAT)pkmCurrentPtr++ = bim1;												\
		*(PKMFLOAT)pkmCurrentPtr++ = oim1;												\
		prefetch((void *)pkmCurrentPtr);									\
		pkmCurrentPtr += 4;

#define kmxxSetVertex_15(pcw, xa, ya, invwa, xb, yb, invwb, xc, yc, invwc, xd, yd)	\
		*pkmCurrentPtr++ = pcw;													\
		*(PKMFLOAT)pkmCurrentPtr++ = xa;				\
		*(PKMFLOAT)pkmCurrentPtr++ = ya;				\
		*(PKMFLOAT)pkmCurrentPtr++ = invwa;			\
		*(PKMFLOAT)pkmCurrentPtr++ = xb;				\
		*(PKMFLOAT)pkmCurrentPtr++ = yb;				\
		*(PKMFLOAT)pkmCurrentPtr++ = invwb;			\
		*(PKMFLOAT)pkmCurrentPtr  = xc;				\
		prefetch((void *)pkmCurrentPtr);										\
		pkmCurrentPtr++;					\
		*(PKMFLOAT)pkmCurrentPtr++  = yc;				\
		*(PKMFLOAT)pkmCurrentPtr++  = invwc;			\
		*(PKMFLOAT)pkmCurrentPtr++  = xd;				\
		*(PKMFLOAT)pkmCurrentPtr++  = yd;				\
		prefetch((void *)pkmCurrentPtr);									\
		pkmCurrentPtr += 4;

#define kmxxSetVertex_16(pcw, xa, ya, invwa, xb, yb, invwb, xc, yc, invwc, xd, yd, uva, uvb, uvc )	\
		*pkmCurrentPtr++  = pcw;			\
		*(PKMFLOAT)pkmCurrentPtr++  = xa;				\
		*(PKMFLOAT)pkmCurrentPtr++  = ya;				\
		*(PKMFLOAT)pkmCurrentPtr++  = invwa;			\
		*(PKMFLOAT)pkmCurrentPtr++  = xb;				\
		*(PKMFLOAT)pkmCurrentPtr++  = yb;				\
		*(PKMFLOAT)pkmCurrentPtr++  = invwb;			\
		*(PKMFLOAT)pkmCurrentPtr    = xc;				\
		prefetch((void *)pkmCurrentPtr);	\
		pkmCurrentPtr++;					\
		*(PKMFLOAT)pkmCurrentPtr++  = yc;				\
		*(PKMFLOAT)pkmCurrentPtr++  = invwc;			\
		*(PKMFLOAT)pkmCurrentPtr++  = xd;				\
		*(PKMFLOAT)pkmCurrentPtr++  = yd;				\
		pkmCurrentPtr++;					\
		*pkmCurrentPtr++  = uva;				\
		*pkmCurrentPtr++  = uvb;				\
		*pkmCurrentPtr    = uvc;				\
		prefetch((void *)pkmCurrentPtr);		\
		pkmCurrentPtr++;

#define kmxxSetVertex_17(pcw, xa, ya, invwa, xb, yb, invwb, xc, yc, invwc)		\
		*pkmCurrentPtr++  = pcw;			\
		*(PKMFLOAT)pkmCurrentPtr++  = xa;				\
		*(PKMFLOAT)pkmCurrentPtr++  = ya;				\
		*(PKMFLOAT)pkmCurrentPtr++  = invwa;			\
		*(PKMFLOAT)pkmCurrentPtr++  = xb;				\
		*(PKMFLOAT)pkmCurrentPtr++  = yb;				\
		*(PKMFLOAT)pkmCurrentPtr++  = invwb;			\
		*(PKMFLOAT)pkmCurrentPtr    = xc;				\
		prefetch((void *)pkmCurrentPtr);	\
		pkmCurrentPtr++;					\
		*(PKMFLOAT)pkmCurrentPtr++  = yc;				\
		*(PKMFLOAT)pkmCurrentPtr++  = invwc;			\
		prefetch((void *)pkmCurrentPtr);	\
		pkmCurrentPtr += 6;
#endif /* _L4_ */


#if !defined(_KM_USE_VERTEX_MACRO_L4_) && defined(_KM_USE_VERTEX_MACRO_L5_)
#define kmxxGetCurrentPtr(desc)																\
{																							\
	register PKMDWORD pkmCurrentPtr;														\
	PKMDWORD pkmCurrentListPtr;																\
	PKMDWORD pkmStartPtr;																	\
	pkmCurrentListPtr = (PKMDWORD)((desc)->pCurrentPtr + ((PKMCURRENTLISTSTATE)(desc)->pCurrentListState)->ListType); \
	pkmStartPtr = pkmCurrentPtr = KMI_GET_MAPPING_ADDRESS(*pkmCurrentListPtr);

#define kmxxStartVertexStrip(desc) KMSTATUS_SUCCESS;{										\
	register KMDWORD StructSize = ((PKMCURRENTLISTSTATE)(desc)->pCurrentListState)->GlobalParamSize; \
	kmyMemCopy(pkmCurrentPtr,	(PKMDWORD)((desc)->pGlobalParam), StructSize);				\
	prefetch((void *)pkmCurrentPtr);														\
	pkmCurrentPtr  += 8;																	\
	if(StructSize == 0x40)																	\
	{																						\
		prefetch((void *)pkmCurrentPtr);													\
		pkmCurrentPtr  += 8;																\
	}																						\
}

#define kmxxInternalStartStrip( _pDesc_,_pHead_ )											\
	{																						\
		KMDWORD ListType;																	\
		ListType   = ((((PKMSTRIPHEAD)(_pHead_))->dwStripHead[0]) >> 24) & 7;				\
		((PKMCURRENTLISTSTATE)(_pDesc_)->pCurrentListState)->ListType = ListType;			\
		pkmCurrentListPtr = (PKMDWORD)((_pDesc_)->pCurrentPtr + ListType) ; 				\
	}																						\
	pkmStartPtr = pkmCurrentPtr = KMI_GET_MAPPING_ADDRESS(*pkmCurrentListPtr);				\
	if(((PKMSTRIPHEAD)_pHead_)->dwStripHead[0] & 0x00001400)								\
	{																						\
		kmyMemCopy( pkmCurrentPtr,	(PKMDWORD)(((PKMSTRIPHEAD)(_pHead_))->dwStripHead), 0x40);\
		prefetch((void *)pkmCurrentPtr);													\
		pkmCurrentPtr  += 8;																\
	}																						\
	else																					\
	{																						\
		kmyMemCopy( pkmCurrentPtr,	(PKMDWORD)(((PKMSTRIPHEAD)(_pHead_))->dwStripHead), 0x20);\
	}																						\
	prefetch((void *)pkmCurrentPtr);														\
	pkmCurrentPtr  += 8;

#define kmxxStartStripGetCurrentPtr( _pDesc_,_pHead_ )		KMSTATUS_SUCCESS;				\
{																							\
	register PKMDWORD pkmCurrentPtr;														\
	PKMDWORD pkmCurrentListPtr;																\
	PKMDWORD pkmStartPtr;																	\
	kmxxInternalStartStrip( _pDesc_,_pHead_ );

#define kmxxStartStrip( _pDesc_,_pHead_ )		KMSTATUS_SUCCESS;							\
	*pkmCurrentListPtr += ((KMDWORD)pkmCurrentPtr - (KMDWORD)pkmStartPtr); 					\
	kmxxInternalStartStrip( _pDesc_,_pHead_ );

#define kmxxReleaseCurrentPtr(desc)															\
	*pkmCurrentListPtr += ((KMDWORD)pkmCurrentPtr - (KMDWORD)pkmStartPtr);					\
}

#define kmxxSetVertex_(pcw, x, y, invw, size)									\
		*(PKMFLOAT)--pkmCurrentPtr	= invw;										\
		*(PKMFLOAT)--pkmCurrentPtr	= y;										\
		*(PKMFLOAT)--pkmCurrentPtr	= x;										\
		*--pkmCurrentPtr			= pcw;										\
		prefetch((void *)pkmCurrentPtr);										\
		pkmCurrentPtr += size;													\

#define kmxxSetVertex_0(pcw, x, y, invw, pkdcol)								\
		pkmCurrentPtr += 7;														\
		*--pkmCurrentPtr				= pkdcol;								\
		pkmCurrentPtr -= 2;														\
		kmxxSetVertex_(pcw, x, y, invw, 8);										\

#define kmxxSetVertex_1(pcw, x, y, invw, Alpha, Red, Green, Blue)				\
		pkmCurrentPtr += 8;														\
		*(PKMFLOAT)--pkmCurrentPtr	= Blue;										\
		*(PKMFLOAT)--pkmCurrentPtr	= Green;									\
		*(PKMFLOAT)--pkmCurrentPtr	= Red;										\
		*(PKMFLOAT)--pkmCurrentPtr	= Alpha;									\
		kmxxSetVertex_(pcw, x, y, invw, 8);										\

#define kmxxSetVertex_2(pcw, x, y, invw, bi )									\
		pkmCurrentPtr += 7;														\
		*(PKMFLOAT)--pkmCurrentPtr		= bi;									\
		pkmCurrentPtr -= 2;														\
		kmxxSetVertex_(pcw, x, y, invw, 8);										\

#define kmxxSetVertex_3(pcw, x, y, invw, fu, fv, bcol, ocol)					\
		pkmCurrentPtr += 8;														\
		*--pkmCurrentPtr			= ocol;										\
		*--pkmCurrentPtr			= bcol;										\
		*(PKMFLOAT)--pkmCurrentPtr	= fv;										\
		*(PKMFLOAT)--pkmCurrentPtr	= fu;										\
		kmxxSetVertex_(pcw, x, y, invw, 8);										\

#define kmxxSetVertex_4(pcw, x, y, invw, uv, bcol, ocol)						\
		pkmCurrentPtr += 8;														\
		*--pkmCurrentPtr			= ocol;										\
		*--pkmCurrentPtr			= bcol;										\
		*--pkmCurrentPtr			= bcol;	/* dummy */							\
		*--pkmCurrentPtr			= uv;										\
		kmxxSetVertex_(pcw, x, y, invw, 8);										\

#define kmxxSetVertex_5(pcw, x, y,invw, fu, fv, ba, br, bg, bb, oa, or, og, ob)	\
		pkmCurrentPtr += 16;													\
		*(PKMFLOAT)--pkmCurrentPtr	= ob;										\
		*(PKMFLOAT)--pkmCurrentPtr	= og;										\
		*(PKMFLOAT)--pkmCurrentPtr	= or;										\
		*(PKMFLOAT)--pkmCurrentPtr	= oa;										\
		*(PKMFLOAT)--pkmCurrentPtr	= bb;										\
		*(PKMFLOAT)--pkmCurrentPtr	= bg;										\
		*(PKMFLOAT)--pkmCurrentPtr	= br;										\
		*(PKMFLOAT)--pkmCurrentPtr	= ba;										\
		prefetch((void *)pkmCurrentPtr);										\
		pkmCurrentPtr -= 2;														\
		*(PKMFLOAT)--pkmCurrentPtr	= fv;										\
		*(PKMFLOAT)--pkmCurrentPtr	= fu;										\
		kmxxSetVertex_(pcw, x, y, invw, 16);									\

#define kmxxSetVertex_6(pcw, x, y, invw, uv, ba, br, bg, bb, oa, or, og, ob)	\
		pkmCurrentPtr += 16;													\
		*(PKMFLOAT)--pkmCurrentPtr	= ob;										\
		*(PKMFLOAT)--pkmCurrentPtr	= og;										\
		*(PKMFLOAT)--pkmCurrentPtr	= or;										\
		*(PKMFLOAT)--pkmCurrentPtr	= oa;										\
		*(PKMFLOAT)--pkmCurrentPtr	= bb;										\
		*(PKMFLOAT)--pkmCurrentPtr	= bg;										\
		*(PKMFLOAT)--pkmCurrentPtr	= br;										\
		*(PKMFLOAT)--pkmCurrentPtr	= ba;										\
		prefetch((void *)pkmCurrentPtr);										\
		pkmCurrentPtr -= 3;														\
		*--pkmCurrentPtr			= uv;										\
		kmxxSetVertex_(pcw, x, y, invw, 16);									\

#define kmxxSetVertex_7(pcw, x, y, invw, fu, fv, bi, oi)						\
		pkmCurrentPtr += 8;														\
		*(PKMFLOAT)--pkmCurrentPtr	= oi;										\
		*(PKMFLOAT)--pkmCurrentPtr	= bi;										\
		*(PKMFLOAT)--pkmCurrentPtr	= fv;										\
		*(PKMFLOAT)--pkmCurrentPtr	= fu;										\
		kmxxSetVertex_(pcw, x, y, invw, 8);										\

#define kmxxSetVertex_8(pcw, x, y, invw, uv, bi, oi)							\
		pkmCurrentPtr += 8;														\
		*(PKMFLOAT)--pkmCurrentPtr	= oi;										\
		*(PKMFLOAT)--pkmCurrentPtr	= bi;										\
		*(PKMFLOAT)--pkmCurrentPtr	= bi; /* Dummy */							\
		*--pkmCurrentPtr			= uv;										\
		kmxxSetVertex_(pcw, x, y, invw, 8);										\

#define kmxxSetVertex_9(pcw, x, y, invw, m0col, m1col)							\
		pkmCurrentPtr += 6;														\
		*--pkmCurrentPtr			= m1col;									\
		*--pkmCurrentPtr			= m0col;									\
		kmxxSetVertex_(pcw, x, y, invw, 8);										\

#define kmxxSetVertex_10(pcw, x, y, invw, m0bi, m1bi)							\
		pkmCurrentPtr += 6;														\
		*(PKMFLOAT)--pkmCurrentPtr	= m1bi;									\
		*(PKMFLOAT)--pkmCurrentPtr	= m0bi;									\
		kmxxSetVertex_(pcw, x, y, invw, 8);										\

#define kmxxSetVertex_11(pcw, x, y, invw, um0, vm0, bcolm0, ocolm0, um1, vm1, bcolm1, ocolm1)		\
		pkmCurrentPtr += 12;													\
		*--pkmCurrentPtr			= ocolm1;									\
		*--pkmCurrentPtr			= bcolm1;									\
		*(PKMFLOAT)--pkmCurrentPtr	= vm1;										\
		*(PKMFLOAT)--pkmCurrentPtr	= um1;										\
		prefetch((void *)pkmCurrentPtr);										\
		*--pkmCurrentPtr			= ocolm0;									\
		*--pkmCurrentPtr			= bcolm0;									\
		*(PKMFLOAT)--pkmCurrentPtr	= vm0;										\
		*(PKMFLOAT)--pkmCurrentPtr	= um0;										\
		kmxxSetVertex_(pcw, x, y, invw, 16);									\

#define kmxxSetVertex_12(pcw, x, y, invw, uvm0, bcolm0, ocolm0, uvm1, bcolm1, ocolm1)				\
		pkmCurrentPtr += 12;													\
		*--pkmCurrentPtr			= ocolm1;									\
		*--pkmCurrentPtr			= bcolm1;									\
		*--pkmCurrentPtr			= bcolm1;	/* Dummy */						\
		*--pkmCurrentPtr			= uvm1;										\
		prefetch((void *)pkmCurrentPtr);										\
		*--pkmCurrentPtr			= ocolm0;									\
		*--pkmCurrentPtr			= bcolm0;									\
		*--pkmCurrentPtr			= bcolm0;	/* Dummy */						\
		*--pkmCurrentPtr			= uvm0;										\
		kmxxSetVertex_(pcw, x, y, invw, 16);									\

#define kmxxSetVertex_13(pcw, x, y, invw, um0, vm0, bim0, oim0, um1, vm1, bim1, oim1)					\
		pkmCurrentPtr += 12;													\
		*(PKMFLOAT)--pkmCurrentPtr	= oim1;										\
		*(PKMFLOAT)--pkmCurrentPtr	= bim1;										\
		*(PKMFLOAT)--pkmCurrentPtr	= vm1;										\
		*(PKMFLOAT)--pkmCurrentPtr	= um1;										\
		prefetch((void *)pkmCurrentPtr);										\
		*(PKMFLOAT)--pkmCurrentPtr	= oim0;										\
		*(PKMFLOAT)--pkmCurrentPtr	= bim0;										\
		*(PKMFLOAT)--pkmCurrentPtr	= vm0;										\
		*(PKMFLOAT)--pkmCurrentPtr	= um0;										\
		kmxxSetVertex_(pcw, x, y, invw, 16);									\

#define kmxxSetVertex_14(pcw, x, y, invw, uvm0, bim0, oim0, uvm1, bim1, oim1)	\
		pkmCurrentPtr += 12;													\
		*(PKMFLOAT)--pkmCurrentPtr	= oim1;										\
		*(PKMFLOAT)--pkmCurrentPtr	= bim1;										\
		*(PKMFLOAT)--pkmCurrentPtr	= bim1;		/* Dummy */						\
		*--pkmCurrentPtr			= uvm1;										\
		prefetch((void *)pkmCurrentPtr);										\
		*(PKMFLOAT)--pkmCurrentPtr	= oim0;										\
		*(PKMFLOAT)--pkmCurrentPtr	= bim0;										\
		*(PKMFLOAT)--pkmCurrentPtr	= bim0;		/* Dummy */						\
		*--pkmCurrentPtr			= uvm0;										\
		kmxxSetVertex_(pcw, x, y, invw, 16);									\

#define kmxxSetVertex_Tri(pcw, xa, ya, invwa, xb, yb, invwb, xc, yc, invwc)		\
		*(PKMFLOAT)--pkmCurrentPtr	= invwc;									\
		*(PKMFLOAT)--pkmCurrentPtr	= yc;										\
		prefetch((void *)pkmCurrentPtr);										\
		*(PKMFLOAT)--pkmCurrentPtr	= xc;										\
		*(PKMFLOAT)--pkmCurrentPtr	= invwb;									\
		*(PKMFLOAT)--pkmCurrentPtr	= yb;										\
		*(PKMFLOAT)--pkmCurrentPtr	= xb;										\
		*(PKMFLOAT)--pkmCurrentPtr	= invwa;									\
		*(PKMFLOAT)--pkmCurrentPtr	= ya;										\
		*(PKMFLOAT)--pkmCurrentPtr	= xa;										\
		*--pkmCurrentPtr			= pcw;										\
		prefetch((void *)pkmCurrentPtr);										\
		pkmCurrentPtr += 16;													\

#define kmxxSetVertex_15(pcw, xa, ya, invwa, xb, yb, invwb, xc, yc, invwc, xd, yd)	\
		pkmCurrentPtr += 12;													\
		*(PKMFLOAT)--pkmCurrentPtr	= yd;										\
		*(PKMFLOAT)--pkmCurrentPtr	= xd;										\
		kmxxSetVertex_Tri(pcw, xa, ya, invwa, xb, yb, invwb, xc, yc, invwc);	\

#define kmxxSetVertex_16(pcw, xa, ya, invwa, xb, yb, invwb, xc, yc, invwc, xd, yd, uva, uvb, uvc )	\
		pkmCurrentPtr += 16;													\
		*--pkmCurrentPtr			= uvc;										\
		*--pkmCurrentPtr			= uvb;										\
		*--pkmCurrentPtr			= uva;										\
		*--pkmCurrentPtr			= uva;		/* Dummy */						\
		*(PKMFLOAT)--pkmCurrentPtr	= yd;										\
		*(PKMFLOAT)--pkmCurrentPtr	= xd;										\
		kmxxSetVertex_Tri(pcw, xa, ya, invwa, xb, yb, invwb, xc, yc, invwc);	\

#define kmxxSetVertex_17(pcw, xa, ya, invwa, xb, yb, invwb, xc, yc, invwc)		\
		pkmCurrentPtr += 10;													\
		kmxxSetVertex_Tri(pcw, xa, ya, invwa, xb, yb, invwb, xc, yc, invwc);	\

#endif /* _L5_ */


#if defined(_KM_USE_CHANGESTRIP_MACRO_)
/*
 *  Change Strip Macros
 */

#if !defined (__kmiParamDefs_H)
#define KMY_TEXADRS_MASK			(0xffe00000)
#define KMY_USIZE_MASK              (0xffffffc7)
#define KMY_VSIZE_MASK				(0xfffffff8)
#define KMY_LIST_MASK				(0xf8ffffff)
#define KMY_ALPHA_ENABLE_MASK		(0xffefffff)
#endif

#define kmChangeStripTextureSurface(_pHead_, _nParam_, _pSurface_) KMSTATUS_SUCCESS; {                                  \
	(_pHead_)->dwStripHead[2 + 2*_nParam_] = ((_pHead_)->dwStripHead[2+2*_nParam_] & ( KMY_USIZE_MASK & KMY_VSIZE_MASK )) | (((_pSurface_)->fSurfaceFlags) & ~(KMY_USIZE_MASK & KMY_VSIZE_MASK)); \
	(_pHead_)->dwStripHead[3 + 2*_nParam_] = (((_pSurface_)->fSurfaceFlags | (_pSurface_)->PixelFormat) & KMY_TEXADRS_MASK) |	(((KMDWORD)((_pSurface_)->pSurface)>>3) & ~KMY_TEXADRS_MASK); 	\
}

#define kmChangeStripListType(_pHead_, _Type_) KMSTATUS_SUCCESS; {										\
	(_pHead_)->dwStripHead[0] = ((_pHead_)->dwStripHead[0] & KMY_LIST_MASK) | ((_Type_ & 0x07)<<24);	\
}

#define kmChangeStripUseAlpha(_pHead_, _nParam_,_bUseAlpha_) KMSTATUS_SUCCESS; {					\
	(_pHead_)->dwStripHead[2 + 2 * _nParam_] = (((_pHead_)->dwStripHead[2 + 2 * _nParam_] & KMY_ALPHA_ENABLE_MASK) | ((_bUseAlpha_ & 0x01)<<20) ); \
}

#define kmChangeStripTextureAddress(_pHead_, _nParam_, _pSurface_) KMSTATUS_SUCCESS; {	\
	(_pHead_)->dwStripHead[3 + 2*_nParam_] = ((_pHead_)->dwStripHead[3 + 2*_nParam_] & KMY_TEXADRS_MASK) |	(((KMDWORD)((_pSurface_)->pSurface)>>3) & ~KMY_TEXADRS_MASK); 	\
}

#endif

#ifdef __cplusplus
}
#endif
#endif	/* __kmvertex_macro_header__ */