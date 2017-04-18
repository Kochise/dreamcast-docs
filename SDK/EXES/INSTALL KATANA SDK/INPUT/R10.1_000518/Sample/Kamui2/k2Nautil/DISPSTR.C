/********************************************************************/
/* Kamui function test program subroutine							*/
/* string display routine for KAMUI									*/
/********************************************************************/
/*   COPYRIGHT (C) NEC Corporation 1997 - 1999                      */
/*   All rights reserved by NEC Corporation. This program must be   */
/*   used solely for the purpose for which it was furnished by NEC  */
/*   Corporation. No part of this program may be reproduced or      */
/*   disclosed to others, in any form, without the prior written    */
/*   permission of NEC Corporation.                                 */
/*   Use of copyright notice does not evidence publication of this  */
/*   program.                                                       */
/*                                                                  */
/*   Author   : Takeshi Muto / NEC Software, Ltd.                   */
/*   Created  : October 19 1997 by NEC Software, Ltd.               */
/*   Modified : April   09 1998 for SET5 by T.Muto                  */
/*              Janualy 08 1999 for Kamui2 by T.Muto                */
/*              Janualy 27 1999 for use of Strip context by T.Kamei */
/********************************************************************/

#define		TEX_TYPE			KM_TEXTURE_ARGB4444		/* Font Texture type */
#define		TEXCHAR_U			(256)					/* Font Texture width */
#define		TEXCHAR_V			(256)					/* Font Texture height */
#define		CHAR_SIZE_X			(16.0f)					/* Font display size (width) */
#define		CHAR_SIZE_Y			(32.0f)					/* Font display size (height) */
#define		CHAR_PITCH			(-6.0f)					/* Character pitch 0=standard */
#define		LINE_PITCH			(-10.0f)				/* Line pitch 0=standard */
#define		MAXLINE		21		/* = 480 / ( CHAR_SIZE_Y + LINE_PITCH ) */
#define		MAXCOLMN	64		/* = 640 / ( CHAR_SIZE_X + CHAR_PITCH ) */

#include	<stdio.h>
#include	<stdarg.h>
#define _KM_USE_VERTEX_MACRO_
/*#define _KM_USE_VERTEX_MACRO_L2_	/***/
#define _KM_USE_VERTEX_MACRO_L4_	/***/
#include	"kamui2.h"				/* for Kamui Call */
#include    "kamuix.h"           /* for Kamui macor Call */

/* Texture */
extern const unsigned char character[];

typedef struct tagTXTATTRIB
{
	union {
		struct {
			unsigned  char	red;			/* color red */
			unsigned  char	green;			/* color green */
			unsigned  char	blue;			/* color blue */
			unsigned  char	pad;			/* Padding byte */
		} bytecolor;

		struct {
			KMDWORD	  dwColor;
		} dwcolor;
	}Color;

	int		reverse;		/* reverse flag */
	int		blink;			/* blink flag */
} TXTATTRIB, *PTXTATTRIB;

/***************************************************************************/
/**	グローバル変数 *********************************************************/
/***************************************************************************/
static	KMUINT32	colmn = 0;			/* cursor x number */
static	KMUINT32	line = 0;			/* cursor y number */
static	KMUINT32	initialized = 0;	/* initialized ? or not ? */
static	unsigned char	scrn[MAXLINE][MAXCOLMN];		/* screen image */
static	TXTATTRIB	attrib[MAXLINE][MAXCOLMN];		/* attribute */
static	unsigned char	colorRed	= 255;	/* current color red */
static	unsigned char	colorGreen	= 255;	/* current color green */
static	unsigned char	colorBlue	= 255;	/* current color blue */
static	int			reverse		= 0;	/* current reverse flag */
static	int			blink		= 0;	/* current blink flag */
static	int			blinkcount	= 0;	/* current blink flag */
static	int			blinkspeed	= 30;	/* blink speed */
static	float		scaleX		= 1.0f;	/* character size scale X */
static	float		scaleY		= 1.0f;	/* character size scale Y */

/****************************************************************************/
/**	Valuables for KAMUI *****************************************************/
/****************************************************************************/
static	KMSURFACEDESC		kmiDispStrTexSurfaceDesc;	/* texture surface */
static	KMSTRIPCONTEXT		kmiDispStrStripContext16;	/* Strip Context(VertexType05)	*/
static	KMSTRIPHEAD			kmiStripHead16;				/* Strip Head(VertexType05)		*/

/***************************************************************************/
/**	サブルーチン ***********************************************************/
/***************************************************************************/

/****************************************************************************/
/** Set Cursor **************************************************************/
/****************************************************************************/
void
txt_SetCursor(KMUINT32 x, KMUINT32 y)
{
	colmn = x; line = y;
}

/****************************************************************************/
/** Set Scale ***************************************************************/
/****************************************************************************/
void
txt_SetScale( float x, float y )
{
	scaleX = x;
	if( x <=  0.0f ) scaleX =  1.0f;
	if( x >  20.0f ) scaleX = 20.0f;
	scaleY = y;
	if( y <=  0.0f ) scaleY =  1.0f;
	if( y >  20.0f ) scaleY = 20.0f;
}

/****************************************************************************/
/** Set Color ***************************************************************/
/****************************************************************************/
void
txt_SetColor( float R, float G, float B )
{
	if( R < 0.0f ) R = 0.0f;
	if( R > 1.0f ) R = 1.0f;
	colorRed = (unsigned char)(R * 255.0f);

	if( G < 0.0f ) G = 0.0f;
	if( G > 1.0f ) G = 1.0f;
	colorGreen = (unsigned char)(G * 255.0f);

	if( B < 0.0f ) B = 0.0f;
	if( B > 1.0f ) B = 1.0f;
	colorBlue = (unsigned char)(B * 255.0f);
}

/****************************************************************************/
/** Set Reverce *************************************************************/
/****************************************************************************/
void
txt_SetReverce( int flag )
{
	if( flag == TRUE ) {
		reverse = 1;
	}
	else {
		reverse = 0;
	}
}

/****************************************************************************/
/** Set Blink ***************************************************************/
/****************************************************************************/
void
txt_SetBlink( int flag )
{
	if( flag == TRUE ) {
		blink = 1;
	}
	else {
		blink = 0;
	}
}

/****************************************************************************/
/** Set Blink speed *********************************************************/
/****************************************************************************/
void
txt_SetBlinkSpeed( int speed )
{
	blinkspeed = 30 - speed;
	if(blinkspeed <= 0) blinkspeed = 1;
	if(blinkspeed > 500) blinkspeed = 500;
}

/****************************************************************************/
/** Clear screen ************************************************************/
/****************************************************************************/
void
txt_ClearScreen(void)
{
	KMUINT32	x, y;

	for(y = 0; y < MAXLINE; y++) {
		for(x = 0; x < MAXCOLMN; x++) {
			scrn[y][x] = 0;
			attrib[y][x].Color.bytecolor.red		= 255;		/* color red */
			attrib[y][x].Color.bytecolor.green		= 255;		/* color green */
			attrib[y][x].Color.bytecolor.blue		= 255;		/* color blue */
			attrib[y][x].reverse	= 0;		/* reverse flag */
			attrib[y][x].blink		= 0;		/* blink flag */
		}
	}
	colmn = 0; line = 0;
}

/****************************************************************************/
/** Init Display String *****************************************************/
/****************************************************************************/
void
txt_InitDisplayString(void)
{
	KMSTATUS			status;						/* return status of KAMUI API */
	PKMDWORD			pTexture01;					/* Pointer to texture */
	KMTEXTURETYPE		nTextureType;				/* texture type definition */
	KMPACKEDARGB		BaseColor;

	BaseColor.dwPacked = 0xFFFFFFFF;

	/*-----------------------------------------------------------------------------------*/
	/* Create texture surface */
	nTextureType = KM_TEXTURE_TWIDDLED | TEX_TYPE;	/* Set texture type */
	status = kmCreateTextureSurface(
		&kmiDispStrTexSurfaceDesc,		/* OUT	PKMSURFACEDESC	pSurfaceDesc */
		TEXCHAR_U,						/*	IN	KMINT32			nWidth */
		TEXCHAR_V,						/*	IN	KMINT32			nHeight */
		nTextureType					/*	IN	KMTEXTURETYPE	nTextureType */
	);
	if(status != KMSTATUS_SUCCESS) return;

	/*-----------------------------------------------------------------------------------*/
	/* Load and set texture */
	pTexture01 = (unsigned long *)&character;
	status = kmLoadTexture(&kmiDispStrTexSurfaceDesc,	/* PKMSURFACEDESC pSurfaceDesc */
							pTexture01 + (16 / sizeof(KMDWORD))	/* PKMDWORD pTexture */
							);
	if(status != KMSTATUS_SUCCESS) return;

	/*-----------------------------------------------------------------------------------*/
	/* Initialize StripContext 16 */
	memset(&kmiDispStrStripContext16,0,sizeof(KMSTRIPCONTEXT));

	kmiDispStrStripContext16.nSize = sizeof(kmiDispStrStripContext16);
	kmiDispStrStripContext16.StripControl.nListType								= KM_TRANS_POLYGON;
	kmiDispStrStripContext16.StripControl.nUserClipMode	 						= KM_USERCLIP_DISABLE;
	kmiDispStrStripContext16.StripControl.nShadowMode		 					= KM_NORMAL_POLYGON;
	kmiDispStrStripContext16.StripControl.bOffset								= KM_FALSE;
 	kmiDispStrStripContext16.StripControl.bGouraud		 						= KM_TRUE;
	kmiDispStrStripContext16.ObjectControl.nDepthCompare			 			= KM_ALWAYS;
	kmiDispStrStripContext16.ObjectControl.nCullingMode			 				= KM_NOCULLING;
	kmiDispStrStripContext16.ObjectControl.bZWriteDisable						= KM_FALSE;
	kmiDispStrStripContext16.ObjectControl.bDCalcControl			 			= KM_FALSE;
	kmiDispStrStripContext16.type.splite.Base									= BaseColor;
	kmiDispStrStripContext16.ImageControl[KM_IMAGE_PARAM1].nSRCBlendingMode		= KM_SRCALPHA;
	kmiDispStrStripContext16.ImageControl[KM_IMAGE_PARAM1].nDSTBlendingMode		= KM_INVSRCALPHA;
	kmiDispStrStripContext16.ImageControl[KM_IMAGE_PARAM1].bSRCSelect			= KM_FALSE;
	kmiDispStrStripContext16.ImageControl[KM_IMAGE_PARAM1].bDSTSelect			= KM_FALSE;
	kmiDispStrStripContext16.ImageControl[KM_IMAGE_PARAM1].nFogMode				= KM_NOFOG;
	kmiDispStrStripContext16.ImageControl[KM_IMAGE_PARAM1].bColorClamp			= KM_FALSE;
	kmiDispStrStripContext16.ImageControl[KM_IMAGE_PARAM1].bUseAlpha			= KM_TRUE;
	kmiDispStrStripContext16.ImageControl[KM_IMAGE_PARAM1].bIgnoreTextureAlpha	= KM_FALSE;
	kmiDispStrStripContext16.ImageControl[KM_IMAGE_PARAM1].nFlipUV				= KM_NOFLIP;
	kmiDispStrStripContext16.ImageControl[KM_IMAGE_PARAM1].nClampUV				= KM_CLAMP_UV;
	kmiDispStrStripContext16.ImageControl[KM_IMAGE_PARAM1].nFilterMode			= KM_BILINEAR;
	kmiDispStrStripContext16.ImageControl[KM_IMAGE_PARAM1].bSuperSampleMode		= KM_FALSE;
	kmiDispStrStripContext16.ImageControl[KM_IMAGE_PARAM1].dwMipmapAdjust		= KM_MIPMAP_D_ADJUST_1_00;
	kmiDispStrStripContext16.ImageControl[KM_IMAGE_PARAM1].nTextureShadingMode	= KM_MODULATE;
	kmiDispStrStripContext16.ImageControl[KM_IMAGE_PARAM1].pTextureSurfaceDesc	= &kmiDispStrTexSurfaceDesc;

	kmGenerateStripHead16( &kmiStripHead16,&kmiDispStrStripContext16 );

	initialized = 1;	/* set initialize flag */
}

/****************************************************************************/
/** Display String **********************************************************/
/****************************************************************************/
void
txt_DispString(char *instring,...)
{
	KMINT32		i = 0;
	KMINT32		x,j;


	char		string[4096];
	va_list		vaArgs;

/*--
	if(initialized == 0) return;
--*/

	va_start (vaArgs, instring);
	vsprintf (string, instring, vaArgs);

	do{
		if(string[i] == '\n') {
			for(j = colmn; j < MAXCOLMN; j++) {
				scrn[line][j] = 0;
			}
			colmn = 0; line++;
			if(line >= MAXLINE) {
				kmyMemCopy(	(KMVOID *)&scrn[0][0],
							(KMVOID *)&scrn[1][0],
							(KMDWORD)((MAXLINE - 1) * MAXCOLMN * sizeof(unsigned char))
						  );
				kmyMemCopy(	(KMVOID *)&attrib[0][0],
							(KMVOID *)&attrib[1][0],
							(KMDWORD)((MAXLINE - 1) * MAXCOLMN * sizeof(TXTATTRIB))
						  );
				line = MAXLINE - 1;
				for(x = 0; x < MAXCOLMN; x++) {
					scrn[line][x] 				= 0;
					attrib[line][x].Color.bytecolor.red			= 255;		/* color red */
					attrib[line][x].Color.bytecolor.green		= 255;		/* color green */
					attrib[line][x].Color.bytecolor.blue		= 255;		/* color blue */
					attrib[line][x].reverse		= 0;		/* reverse flag */
					attrib[line][x].blink		= 0;		/* blink flag */
				}
			}
		}
		else if(string[i] == 0x08){			/* Back Space */
			if(colmn > 1){
				scrn[line][colmn]			= ' ';
				colmn--;
			}
		}
		else if(string[i] >= ' ') {
			scrn[line][colmn]			= (unsigned char)string[i];	/* set character */
			attrib[line][colmn].Color.bytecolor.red		= colorRed;		/* set current color red */
			attrib[line][colmn].Color.bytecolor.green	= colorGreen;	/* set current color green */
			attrib[line][colmn].Color.bytecolor.blue	= colorBlue;	/* set current color blue */
			attrib[line][colmn].reverse	= reverse;		/* set current reverse flag */
			attrib[line][colmn].blink	= blink;		/* set current blink flag */
			colmn++;
			if(colmn >= MAXCOLMN) {
				colmn = 0; line++;
				if(line >= MAXLINE) {
					line = 0;
				}
			}
		}
		else {
			scrn[line][colmn] = 0;
			colmn++;
			if(colmn >= MAXCOLMN) {
				colmn = 0; line++;
				if(line >= MAXLINE) {
					line = 0;
				}
			}
		}
	} while(string[++i] != 0);
}

/****************************************************************************/
/** Display String **********************************************************/
/****************************************************************************/
void
txt_DispScreen( PKMVERTEXBUFFDESC pBufferDesc )
{
	KMINT32			x, y;
	KMINT32			nChar;
	KMINT32			StateChange = 0;
	KMINT32			bReverse = 0;
	KMSTATUS		status;					/* return status of KAMUI API */
	TXTATTRIB		*pAttrib;

	KMDWORD			uv1, uv2, uv3;
	KMPACKEDARGB	PrevColor;

	float		x_scale, y_scale, x_size, y_size;
	float		XPos,YPos;
	float		fUC,fVC;

	union {
		KMFLOAT f[2];
		KMWORD  f16[4];
	} f;

	if(initialized == 0) return;

	PrevColor.dwPacked = 0xFFFFFFFF;

	x_scale	= (CHAR_SIZE_X + CHAR_PITCH) * scaleX;
	y_scale	= (CHAR_SIZE_Y + LINE_PITCH) * scaleY;
	x_size	= CHAR_SIZE_X * scaleX;
	y_size	= CHAR_SIZE_Y * scaleY;

	kmxxGetCurrentPtr(pBufferDesc);
	kmxxStartStrip(pBufferDesc,&kmiStripHead16);

	for(y = 0; y < MAXLINE; y++) {
		for(x = 0; x < MAXCOLMN; x++) {
			nChar = scrn[y][x];
			if(nChar >= ' ') {
				if(attrib[y][x].reverse != bReverse)
				{
					bReverse = attrib[y][x].reverse;
					if(bReverse == 0) {	/* Normal */
						kmChangeStripBlendingMode	( &kmiStripHead16,KM_IMAGE_PARAM1,KM_SRCALPHA,KM_INVSRCALPHA );
						StateChange = 1;
					}
					else {	/* Reverce */
						kmChangeStripBlendingMode	( &kmiStripHead16,KM_IMAGE_PARAM1,KM_INVSRCALPHA,KM_SRCALPHA );
						StateChange = 1;
					}
				}

				if(attrib[y][x].Color.dwcolor.dwColor != PrevColor.dwPacked)
				{
					PrevColor.dwPacked = attrib[y][x].Color.dwcolor.dwColor;
					kmChangeStripSpriteBaseColor(&kmiStripHead16, PrevColor);
					StateChange = 1;
				}

				if((attrib[y][x].blink == 0)||(blinkcount > 0))
				{
					nChar -= 32;

					fUC = 0.0625f *(float)((int)(nChar - (nChar / 16)*16));
					fVC = 0.125f * ( 7 - (nChar / 16));
					XPos = x * x_scale;
					YPos = y * y_scale;
					pAttrib = &(attrib[y][x]);

					if(StateChange)
					{
						kmxxStartStrip( pBufferDesc , &kmiStripHead16 );
					}

					f.f[1] = fUC;
					f.f[0] = fVC + 0.125f;
					uv1 = ((KMDWORD)f.f16[3] << 16) | (KMDWORD)f.f16[1];

					f.f[1] = fUC + 0.0625f;
					f.f[0] = fVC + 0.125f;
					uv2 = ((KMDWORD)f.f16[3] << 16) | (KMDWORD)f.f16[1];

					f.f[1] = fUC + 0.0625f;
					f.f[0] = fVC;
					uv3 = ((KMDWORD)f.f16[3] << 16) | (KMDWORD)f.f16[1];

					kmxxSetVertex_16(	KM_VERTEXPARAM_ENDOFSTRIP,
										XPos, 			YPos, 			256.0f,
										XPos + x_size,	YPos,			256.0f,
										XPos + x_size,	YPos + y_size,	256.0f,
										XPos,			YPos + y_size,
										uv1, uv2, uv3
									);

					kmEndStrip( pBufferDesc );
				}	/* End of if((attrib[y][x].blink == 0)||(blinkcount > 0)) */
			}	/* End of if(scrn[y][x] >= ' ') */
		}	/* End of for(x = 0; x < MAXCOLMN; x++) */
	}	/* End of for(y = 0; y < MAXLINE; y++) */

	kmxxReleaseCurrentPtr(pBufferDesc);

	if(--blinkcount < -blinkspeed) blinkcount = blinkspeed;
}

/*--------------------------- End of File --------------------------------*/