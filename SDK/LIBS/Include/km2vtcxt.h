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
  Module Name:		km2vtcxt.h

  Abstract:
	Kamui is Low-Level PowerVR Driver.
	'km2vtcxt.h' define kamui1 compatible vertex context.

  Environment:
	ANSI C Compiler.

  Notes:
	define kamui1 compatible vertex context.

  Revision History:

--*/
#if !defined(__kamui_vertex_context_h)
#define __kamui_vertex_context_h

#ifdef __cplusplus
extern "C" {
#endif 

/*
 * Kamui VertexContext
 */
typedef struct tagKMVERTEXCONTEXT
{
	KMDWORD					RenderState;			/* Render Context		*/

	/* 
	 *for Global Parameter
	 */
	KMPARAMTYPE				ParamType;				/* Parameter Type			*/
	KMLISTTYPE				ListType;				/* List Type				*/
	KMCOLORTYPE				ColorType;				/* Color Type				*/
	KMUVFORMAT				UVFormat;				/* UV Format				*/

	/*
	 * for ISP/TSP Instruction Word 
	 */
	KMDEPTHMODE				DepthMode;				/* DepthMode					*/
	KMCULLINGMODE			CullingMode;			/* Culling Mode					*/
	KMDWORD					reserved00;				/* ScreenCoordination was deleted.*/
	KMSHADINGMODE			ShadingMode;			/* Shading Mode					*/
	KMMODIFIER				SelectModifier;			/* Modifier Volume Valiant		*/
	KMBOOLEAN				bZWriteDisable;			/* Z Write Disable				*/

	/*
	 * for TSP Control Word 
	 */
	KMBLENDINGMODE			SRCBlendingMode;		/* Source Blending Mode			*/
	KMBLENDINGMODE			DSTBlendingMode;		/* Desitination Blending Mode	*/
	KMBOOLEAN				bSRCSel;				/* Source Select				*/
	KMBOOLEAN				bDSTSel;				/* Distination Select			*/
	KMFOGMODE				FogMode;				/* Fogging						*/
	KMBOOLEAN				bUseSpecular;			/* Specular Highlight			*/
	KMBOOLEAN				bUseAlpha;				/* Alpha						*/
	KMBOOLEAN				bIgnoreTextureAlpha;	/* Ignore Texture Alpha			*/
	KMCLAMPMODE				ClampUV;				/* Clamp						*/
	KMFLIPMODE				FlipUV;					/* Flip							*/
	KMFILTERMODE			FilterMode;				/* Texture Filter				*/
	KMBOOLEAN				bSuperSample;			/* Anisotoropic Filter			*/
	KMDWORD					MipMapAdjust;			/* Mipmap D Adjust				*/
	KMTEXTURESHADINGMODE	TextureShadingMode;		/* Texture Shading Mode			*/
	KMBOOLEAN				bColorClamp;			/* ColorClamp Mode				*/
	KMDWORD					PaletteBank;			/* Bank of Palette				*/

	/*
	 * for Texture Control Bit/Address 
	 */
	PKMSURFACEDESC			pTextureSurfaceDesc;	/* Texture Handle */

	/*
	 *  for Intensity FaceColor
	 */
	KMFLOAT					fFaceColorAlpha;		/* Face Color Alpha				*/
	KMFLOAT					fFaceColorRed;			/* Face Color Red				*/
	KMFLOAT					fFaceColorGreen;		/* Face Color Green				*/
	KMFLOAT					fFaceColorBlue;			/* Face Color Blue				*/

	/*
	 * for Intensity Specular Highlight
	 */
	KMFLOAT					fOffsetColorAlpha;		/* Specular Color Alpha		*/
	KMFLOAT					fOffsetColorRed;		/* Specular Color Red		*/
	KMFLOAT					fOffsetColorGreen;		/* Specular Color Green		*/
	KMFLOAT					fOffsetColorBlue;		/* Specular Color Blue		*/

	/*
	 * Internal use values.
	 */
	KMDWORD					GLOBALPARAMBUFFER;		/*  Grobal Parameter Buffer	*/
	KMDWORD					ISPPARAMBUFFER;			/*  ISP Parameter Buffer	*/
	KMDWORD					TSPPARAMBUFFER;			/*	TSP Parameter Buffer	*/
	KMDWORD					TexturePARAMBUFFER;		/*	Texture Parameter Buffer*/

	/*
	 * for ModifierInstruction 
	 */
	KMDWORD					ModifierInstruction;	/* ModifierInstruction 		*/
	KMFLOAT					reserved01;				/* Bounding Box	was deleted.*/
	KMFLOAT					reserved02;				/* Bounding Box	was deleted.*/
	KMFLOAT					reserved03;				/* Bounding Box	was deleted.*/
	KMFLOAT					reserved04;				/* Bounding Box	was deleted.*/

	KMBOOLEAN				bDCalcExact;			/* D Calc Exact				*/
	KMDWORD					reserved05;				/* ScreenCoordination was deleted.*/
	KMUSERCLIPMODE			UserClipMode;			/* UserClip Mode			*/

} KMVERTEXCONTEXT, *PKMVERTEXCONTEXT, **PPKMVERTEXCONTEXT;

#ifdef __cplusplus
}
#endif 

#endif /*  __kamui_vertex_h */
