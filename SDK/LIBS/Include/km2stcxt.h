/*++

  COPYRIGHT        (C) NEC        Corporation 1998 - 1999

  All rights reserved by NEC Corporation. This program must be
  used solely for the purpose for which it was furnished by NEC
  Corporation. No part of this program may be reproduced or
  disclosed to others, in any form, without the prior written
  permission of NEC Corporation.
  Use of copyright notice does not evidence publication of this
  program.

  Author     :		T.Hirata(NEC Software,Ltd.)
  Module Name:		km2stcxt.h

  Abstract:
	Kamui is Low-Level PowerVR Driver.
	'km2stcxt.h' define kamui2 new feature strip context and strip head.

  Environment:
	ANSI

  Notes:
	kamui2 new feature strip context and strip head.

  Revision History:

--*/
#if !defined(__kamui_strip_context_h)
#define __kamui_strip_context_h

/*
 * StripHead Structure
 */
#define	KM_MAX_STRIP_HEAD_SIZE	(16)
typedef struct _tagKMSTRIPHEAD
{
	KMDWORD		dwStripHead[KM_MAX_STRIP_HEAD_SIZE];
}KMSTRIPHEAD,*PKMSTRIPHEAD;

/*
 * StripContext Structure
 */
typedef struct _tagKMSTRIPCONTROL
{
	KMLISTTYPE			nListType;
	KMUSERCLIPMODE		nUserClipMode;
	KMSHADOWMODE		nShadowMode;
	KMCOLORTYPE			nIntensityMode;
	KMBOOLEAN			bOffset;
	KMBOOLEAN			bGouraud;
}KMSTRIPCONTROL,*PKMSTRIPCONTROL;

typedef struct _tagKMOBJECTCONTROL
{
	KMDEPTHMODE				nDepthCompare;
	KMCULLINGMODE			nCullingMode;
	KMBOOLEAN				bZWriteDisable;
	KMBOOLEAN				bDCalcControl;
	KMDWORD					dwModifierInstruction;
}KMOBJECTCONTROL,*PKMOBJECTCONTROL;

typedef struct _tagKMIMAGECONTROL
{
	KMBLENDINGMODE			nSRCBlendingMode;
	KMBLENDINGMODE			nDSTBlendingMode;
	KMBOOLEAN				bSRCSelect;
	KMBOOLEAN				bDSTSelect;
	KMFOGMODE				nFogMode;
	KMBOOLEAN				bColorClamp;
	KMBOOLEAN				bUseAlpha;
	KMBOOLEAN				bIgnoreTextureAlpha;
	KMFLIPMODE				nFlipUV;
	KMCLAMPMODE				nClampUV;
	KMFILTERMODE			nFilterMode;
	KMBOOLEAN				bSuperSampleMode;
	KMDWORD					dwMipmapAdjust;
	KMTEXTURESHADINGMODE	nTextureShadingMode;
    KMDWORD					dwPaletteBank;
    PKMSURFACEDESC 			pTextureSurfaceDesc;
}KMIMAGECONTROL,*PKMIMAGECONTROL;

#define KM_IMAGE_PARAM1			(0)
#define KM_IMAGE_PARAM2			(1)
#define KM_INTENSITY_BASE		(0)
#define KM_INTENSITY_BASE_2ND	(1)
#define KM_INTENSITY_OFFSET		(1)

typedef struct _tagKMSTRIPCONTEXT
{
	KMINT32			nSize;
	KMSTRIPCONTROL	StripControl;			/* StripControl */
	KMOBJECTCONTROL	ObjectControl;			/* ObjectControl*/
	union
	{
		struct {
			KMFLOATCOLOR	Face[2];
		}intensity;
		struct {
		    KMPACKEDARGB	Base;
		    KMPACKEDARGB	Offset;
		}splite;
	}type;

	KMIMAGECONTROL	ImageControl[1];		/* ImageControl	*/

}KMSTRIPCONTEXT,*PKMSTRIPCONTEXT;

typedef struct _tagKMTWOVOLUMESTRIPCONTEXT
{
	KMINT32			nSize;
	KMSTRIPCONTROL	StripControl;			/* StripControl */
	KMOBJECTCONTROL	ObjectControl;			/* ObjectControl*/

	union
	{
		struct {
			KMFLOATCOLOR	Face[2];
		}intensity;
		struct {
		    KMPACKEDARGB	Base;
		    KMPACKEDARGB	Offset;
		}splite;
	}type;

	KMIMAGECONTROL	ImageControl[2];		/* ImageControl	*/

}KMTWOVOLUMESTRIPCONTEXT,*PKMTWOVOLUMESTRIPCONTEXT;


#endif /*  __kamui_vertex_h */
