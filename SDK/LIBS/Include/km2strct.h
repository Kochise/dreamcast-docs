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
  Module Name:		km2strct.h

  Abstract:
	Kamui is Low-Level PowerVR Driver.
	'km2strct.h' is kamui2 structure defines header.

  Environment:
	ANSI

  Notes:
	Kamui2 structure.

  Revision History:
	97.08.19	Separeted from kmdefs.h
	98.10.01	Modified for KAMUI2

--*/
#if !defined(__kamui_struct_h)
#define __kamui_struct_h

#ifdef __cplusplus
extern "C" {
#endif 

/*++
 KMVERSIONINFO
 -------------
	KAMUI Library Version Information.

--*/
/*
 * Kamui Version Information structure
 */
typedef struct KMVERSIONINFO
{
	KMDWORD kmMajorVersion;
	KMDWORD kmLocalVersion;
	KMDWORD kmFrameBufferSize; 		/* Total Size of TextureÅïFrameBuffer */
} KMVERSIONINFO, *PKMVERSIONINFO;


/*++
Color and Palette Structure.
----------------------------


--*/
#if defined(_X86_)
#pragma pack(1)
#endif

/*
 * 32 bit packed color
 */
typedef union _tagKMPACKEDARGB
{
	KMDWORD	dwPacked;
	struct {
		KMBYTE	bBlue;
		KMBYTE	bGreen;
		KMBYTE	bRed;
		KMBYTE	bAlpha;
	}byte;
}KMPACKEDARGB,*PKMPACKEDARGB;

/*
 * Floating Color structure.
 */
typedef struct _tagKMFLOATCOLOR
{
	KMFLOAT	fAlpha;
	KMFLOAT	fRed;
	KMFLOAT	fGreen;
	KMFLOAT	fBlue;
}KMFLOATCOLOR,*PKMFLOATCOLOR;

/*
 * PowerVR II OnChip Palette
 */
typedef union _tagKMPALETTEDATA
{
	KMDWORD	wPaletteData [KM_PALETTE_ENTRY];
	KMDWORD	dwPaletteData[KM_PALETTE_ENTRY];
}KMPALETTEDATA,*PKMPALETTEDATA;

#if defined(_X86_)
#pragma pack()
#endif

/*
 * FrameBuffer/TextureSurface
 */

typedef struct tagKMSURFACEDESC
{
	KMDWORD	SurfaceType;				/* 1:FrameBuffer 2:Texture 3:SmallVQ-Texture */
	KMDWORD	BitDepth;					/* 1:16bpp       2:24bpp   3:32bpp           */
	KMDWORD	PixelFormat;				/* FrameBuffer : */
										/* KM_DSPBPP_RGB565		= 0 */
										/* KM_DSPBPP_RGB555		= 1 */
										/* KM_DSPBPP_ARGB1555	= 3 */
										/* KM_DSPBPP_RGB888		= 4 */
										/* KM_DSPBPP_ARGB8888	= 5 */
										/* Texture : */
										/* KM_PIXELFORMAT_ARGB1555			(0x00000000) */
										/* KM_PIXELFORMAT_RGB565			(0x08000000) */
										/* KM_PIXELFORMAT_ARGB4444			(0x10000000) */
										/* KM_PIXELFORMAT_YUV422			(0x18000000) */
										/* KM_PIXELFORMAT_BUMP				(0x20000000) */
										/* KM_PIXELFORMAT_PALETTIZED_4BPP	(0x28000000) */
										/* KM_PIXELFORMAT_PALETTIZED_8BPP	(0x30000000) */
	union{
		KMDWORD	USize;					/* Texture USize 8-1024			*/
		KMDWORD	Width;					/* Frame Buffer Width			*/
	}
#if defined(_STRICT_UNION_)
	u0
#endif
	;

	union{
		KMDWORD	VSize;					/* Texture VSize 8-1024			*/
		KMDWORD	Height;					/* Frame Buffer Height			*/
	}
#if defined(_STRICT_UNION_)
	u1
#endif
	;

	union{
		KMDWORD	dwTextureSize;			/* TextureSize (byte)			*/
		KMDWORD	dwFrameBufferSize;		/* FrameBufferSize (byte)		*/
	}
#if defined(_STRICT_UNION_)
	uSize
#endif
	;

	KMDWORD		fSurfaceFlags;			/* Surface Flags							*/
	PKMDWORD	pSurface;				/* Texture instance(Pointer on PVRII Core)	*/

}KMSURFACEDESC;
typedef KMSURFACEDESC* PKMSURFACEDESC;
typedef PKMSURFACEDESC* PPKMSURFACEDESC;

/*
 * Frame Buffer Control Structure.
 */
typedef struct tagKMFBSTATUS
{
	/* Size Of KMFBSTATUS */
	KMDWORD		dwSize;					/*  =  sizeof(KMFBSTATUS); */

	KMDWORD		dwNumberOfFreeBlocks;	/* Number of "FREE Texture Control Structure" to be using at present */
	KMDWORD		dwNumberOfUsedBlocks;	/* Number of "USED Texture Control Structure" to be using at present */
	KMDWORD		dwNumberOfMaxBlocks;	/* Number of whole structure which it is possible to use. */
	KMDWORD		dwNumberOfVQBlocks;		/* Number of "VQ Texture Control Structure" to be using at present */
	KMDWORD		dwNumberOfMaxVQBlocks;	/* Number of effective "VQ Texture Control Structure"*/
	KMDWORD		dwSizeOfFixedArea;		/* Size of Allocated Fixed Area(byte) */
	KMDWORD		dwSizeOfFrameBuffer;	/* Size of Frame buffer/Texture Memory(byte) */
} KMFBSTATUS, *PKMFBSTATUS;

/*
 * Each PASS Information.
 */
typedef struct	_tagKMPASSINFO{
	KMDWORD			dwRegionArrayFlag;					/* Region Array Flag		*/
	PKMDWORD		pVertexBuffer;						/* VertexBuffer Pointer		*/
	KMUINT32		nVertexBufferSize;					/* VertexBuffer Size		*/
	KMUINT32		nDirectTransferList;				/* DirectTransfer List Type */
	KMFLOAT			fBufferSize[KM_MAX_DISPLAY_LIST];	/* Buffer size in percent	*/
	KMDWORD			dwOPBSize[KM_MAX_DISPLAY_LIST];		/* Object Ponter Block Size */
}KMPASSINFO,*PKMPASSINFO;

/*
 * Base address of each VertexList.
 */
typedef struct _tagKMVERTEXBUFFERPOINTER
{
	PKMDWORD pListBase[5];				/* Pointer to Top of Vertex buffers					*/
}KMVERTEXBUFFERPOINTER,*PKMVERTEXBUFFERPOINTER;

typedef PKMVERTEXBUFFERPOINTER *PPKMVERTEXBUFFERPOINTER;

/*
 * Current Vertex Buffer List Statistics
 */
typedef struct _tagKMCURRENTLISTSTATE
{
	KMDWORD		ListType;				/* List type : 0-3 								*/
	KMDWORD		GlobalParamSize;		/* Size of Global parameter : 0x20 or 0x40		*/
	KMDWORD		VertexType;				/* Next vertex type	for Error check				*/
	KMDWORD		VertexBank;				/* Bank# of Vertex buffer : 0 or 1				*/
	KMDWORD		nCurrentPass;			/* CurrentPass									*/
	KMDWORD		nMaxPass;				/* Maximum Pass Depth							*/
	KMDWORD		flags;					/* Vertex List Status Flag.					*/

}KMCURRENTLISTSTATE,*PKMCURRENTLISTSTATE;

/*
 * VertexBuffer DESC
 */
typedef struct _tagKMVERTEXBUFFDESC
{
	PKMDWORD					*pCurrentPtr;		/* Pointer to top of Current pass vertex buffer pointers */
	PKMDWORD					pGlobalParam;		/* Pointer to Global parameter work area			*/
	PKMCURRENTLISTSTATE			pCurrentListState;	/* Pointer to KMCURRENTLISTSTATE structure			*/
	PPKMVERTEXBUFFERPOINTER		ppBuffer;			/* Pointer to Vertex buffer pointer structure		*/
	PKMDWORD					*pFirstPassPtr;		/* Pointer to top of First Pass buffer 				*/
	KMDWORD						nMaxBank;			/* Maximum Vertex Buffer Bank						*/
	PKMPASSINFO					pPassInfo;			/* 32byte Align										*/
	KMDWORD						Reserved3;			/* 32byte Align										*/
}KMVERTEXBUFFDESC,*PKMVERTEXBUFFDESC;

/*
 * SystemConfigration Struct
 */
typedef struct	_tagKMSYSTEMCONFIGSTRUCT {
	KMDWORD				dwSize;						/* Size Of KMSYSTEMCONFIGSTRUCT	*/
	KMDWORD				flags;						/* System Configuration Flags	*/

	/* for Frame Buffer */
	PPKMSURFACEDESC		ppSurfaceDescArray;			/* Array of SurfaceDesc	Pointer	*/
	struct{
		KMUINT32		nNumOfFrameBuffer;			/* Number Of Frame Buffer		*/
		KMUINT32		nStripBufferHeight;			/* Height of Strip Buffer		*/
	}fb;

	/* 
	 * for Texture Memory
	 */
	KMUINT32			nTextureMemorySize;			/* Texture Memory size			*/
	KMUINT32			nNumOfTextureStruct;		/* number of Texture Control Structure			*/
	KMUINT32			nNumOfSmallVQStruct;		/* number of SmallVQ Texture Control Structure	*/
	PKMDWORD			pTextureWork;				/* Pointer to kamui work area							*/

	/*
	 *  for Vertex Buffer
	 */
	PKMVERTEXBUFFDESC	pBufferDesc;				/* pointer to KMVERTEXBUFFDESC 		*/
	KMUINT32			nNumOfVertexBank;			/* Number of VertexBank 			*/
	PKMDWORD			pVertexBuffer;				/* VertexBuffer Pointer				*/
	KMUINT32			nVertexBufferSize;			/* VertexBuffer Size				*/
	KMUINT32			nPassDepth;					/* Path Depth						*/

	KMPASSINFO			Pass[KM_MAX_DISPLAY_LIST_PASS];			/* Pass Information			*/

} KMSYSTEMCONFIGSTRUCT, *PKMSYSTEMCONFIGSTRUCT;

/*
 * Callback functions
 */
typedef VOID (* PKMCALLBACKFUNC)( PKMVOID pArgs );

/*
 * Rectangle struct
 */
typedef struct _tagKMRECT
{
	KMINT32	nXmin;
	KMINT32	nYmin;
	KMINT32	nXmax;
	KMINT32	nYmax;
}KMRECT,*PKMRECT;

/*
 * SystemMetrics struct
 */

typedef struct _tagKMSYSTEMMETRICS
{
	KMDWORD	flags;

	/* RENDER Performance */
	KMDWORD	nLastRenderTime[KM_MAX_RENDER_TIME];
	KMDWORD	nLastDMATime[KM_MAX_DISPLAY_LIST_PASS];

	/* TimeOut Setting Data */
	KMDWORD	nCurrentTimeOutCount;
	KMDWORD	nDMATimeOutCount;
	KMDWORD nRenderTimeOutCount;
	KMDWORD nOBJOverflowCount;
	KMDWORD nParamOverflowCount;

	KMDWORD nParamCurrent;
	KMDWORD nOBJCurrent;
	KMDWORD nOBJLimit;
	KMDWORD nParamLimit;

	/* VertexBuffer Information */
	KMDWORD	VertexBufferSize[KM_MAX_DISPLAY_LIST_PASS][KM_MAX_DISPLAY_LIST];
	KMDWORD	MaxVertexSize[KM_MAX_DISPLAY_LIST_PASS][KM_MAX_DISPLAY_LIST];

	KMDWORD Reserved[16];

}KMSYSTEMMETRICS, *PKMSYSTEMMETRICS;

/*
 * for Fatal Error Callback arg.
 */
typedef struct _tagKMFATALERRORDATA
{
	KMDWORD	dwReason;
}KMFATALERRORDATA,*PKMFATALERRORDATA;

/*
 * for PAL Extension Mode
 */
typedef struct _tagKMPALEXTINFO
{
	IN	KMDISPLAYMODE	nDisplayMode;
	OUT	KMINT32			nPALExtMode;
} KMPALEXTINFO,*PKMPALEXTINFO;


/*++

	 ------ DEBUG Version only ---------

--*/
/*
 * structure for Kamui2 Internal ASSERT(); callback.
 */
typedef struct _tagKMASSERTIONFAIL
{
	PKMCHAR8	pszErrMsg;
	PKMCHAR8	pszFormula;
	PKMCHAR8	pszFile;
	KMINT32		nLine;
}KMASSERTIONFAIL,*PKMASSERTIONFAIL;

#ifdef __cplusplus
}
#endif 

#endif /*  __kamui_struct_h	*/

