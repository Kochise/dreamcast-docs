/*****************************************************************************
  Name : KMShell.c
  Date : August 1998 (Kamui2 update August 1999)
  Platform : ANSI compatible
 
  Description : 
  This file contains the Kamui start-up code and the main() function.
  It is the same for all the demos. To interact with the user's application,
  KMShell calls some functions that have to be defined by the user.

  These functions are:

  void InitAplication (void);
	
  This function will be called by the KM Shell before anything happens, at the very
  beginning of the KMShell main() function. That's the only time this function
  will be called. This function enables the user to perform any initialisation before 
  the program is actually run.


  void QuitAplication(void);

  This function will be called by the KMShell just before finishing the program.
  It enables the user to release any memory allocated before.

  
  BOOL RenderScene	(void);

  That's the main user function in which you have to do your own rendering.
  Be sure to make this function return TRUE if the rendering has gone OK.

  int PadControl(void);

  This function is the user Procedure function. 
  It enables the user to control the Dreamcast PAD.
  If you don't want to use this function, put nothing in it :
    
  int PadControl(void){}
 
 
  Copyright : 1998 by VideoLogic Limited. All rights reserved.
******************************************************************************/
#include "KMShell.h"

/* Shinobi for VideoInit and Controller*/
#include <shinobi.h>
#include <stdio.h>
#include <sg_syCfg.h>

#include "DCLogo.dat" /* Dreamcast Logo *
/************************************************************************
 *     DEFINES
 ************************************************************************/
#define VERTEXBUFFERSIZE    0x90000   /* Size of vertex buffer, in bytes. */
#define TEXTUREMEMORYSIZE   0x400000  /* VRAM set aside for textures, in bytes (4 MB). */
#define MAXTEXTURES         4096      /* Maximum number of textures to be tracked. */
#define MAXSMALLVQ          0         /* Maximum number of small VQ textures. */


/* Align a pointer to the nearest 32-byte aligned memory address. */
#define syMallocAlign32Byte(size)  (void *)((((long)malloc(size+0x1F)) + 0x1F) & 0xFFFFFFE0)

/* Reference physical memory through a non-cached memory address (SH4 P2 memory region). */
#define SH4_P2NonCachedMem(ADR) ((((long) ADR) & 0x0FFFFFFF) | 0xA0000000)



/************************************************************************
 *     GLOBALS
 ************************************************************************/
KMVERTEXBUFFDESC 	VertexBufferDesc;

/* Variables for Maple controler */
NJS_PERIPHERAL 		*PadPointer;
unsigned 			Pad;
int     			AnlgPadX, AnlgPadY;

/* Globals for System configuration */
PKMDWORD 				pVertexBuffer;
PKMSURFACEDESC			pFB[2];
KMSYSTEMCONFIGSTRUCT	SystemConfig;
KMSURFACEDESC			PrimarySurfaceDesc;	
KMSURFACEDESC			BackSurfaceDesc;
 
int						bTransAutosort = TRUE;

KMSURFACEDESC 			TexDCLogo;
KMSTRIPHEAD 			DCLogoStripHead, DCLogoBackStripHead; 
int						DCLogoColor = 0xFFFF3C28, DCLogoBackTrans;

#if 1
/* Kamui2 texture work area, must be aligned to 32-byte boundary. */
#ifdef  __MWERKS__
#pragma align (32);
KMDWORD
#else
#ifdef __GNUC__
KMDWORD __attribute__ ((aligned (32)))
#else
#pragma aligndata32(TextureWorkArea)
KMDWORD
#endif /* __GNUC__ */
#endif /* _MWERKS__ */
TextureWorkArea[MAXTEXTURES * 24/4 + MAXSMALLVQ * 76/4]; /* 4096 standard textures and 0 small vq textures */

#ifdef  __MWERKS__
#pragma align (4);	/* Return Metrowerks alignment to 4-bytes. */
#endif
#endif

/************************************************************************
 *      LOCAL FUNCTIONS
 ************************************************************************/
 
PKMDWORD KMShellGetMaple (void);

void LoadDCLogo (void);

void KMDisplayDCLogo (void);

VOID STATIC	PALExtCallbackFunc(PVOID pCallbackArguments);

/************************************************************************
 *      MAIN
 ************************************************************************/
int main (void)
{
BOOL hRes;

#ifdef __GNUC__
	shinobi_workaround();
#endif
  	
 	
  	/* User initialization */
    InitApplication (); 
    
   	LoadDCLogo();

 	/*   MAIN LOOP */
	while (1)
	{
		kmBeginScene(&SystemConfig);
		
		kmBeginPass(&VertexBufferDesc);
		
        /*
		 * Controler data 
		 */
		KMShellGetMaple ();
		
		/* User input */
		if(!PadControl()) break;
		
	
		
     	/*
		 * Draw our scene while TRUE is returned
		 */
		hRes = RenderScene ();
		
		/* The Dreamcast Logo */
		KMDisplayDCLogo ();
				 
		if (hRes == NULL) break;

		/*
		 * Finish the pass (only one). 
		 */
		kmEndPass(&VertexBufferDesc);
		        
		/*
		 * Rendering 
		 */
		kmRender(KM_RENDER_FLIP);
		
			
		/*
		 * Finish the scene. 
		 */
        kmEndScene (&SystemConfig);
        
        pdExecPeripheralServer();
		
	} /* End of while */


	/* User finish */
	QuitApplication();

	KMShellQuitKamui();
	
	return 0;
}
/*----------------------------------------------------------------------*/
/*  Function Name   : KMShellSetVideo                                   */
/*  Inputs          : VGAOn fOpaq fOpaqMV fTrans fTransMV fPnchTh       */  
/*  Outputs         : None                                              */
/*  Returns         : Actual video mode.                                */
/*  Globals Used    : VertexBufferDesc                                  */
/*  Description     : Init Kamui Video.                                 */ 
/*----------------------------------------------------------------------*/
KMDWORD KMShellSetVideo (BOOL bIsPreSort, DWORD dwDCLogoTrans) 
{
KMPACKEDARGB   cBorder;
SYE_CBL_CABLE  cblCable;
        
    /* Logo Color for Europe */
    if(syCblCheckBroadcast()==SYE_CBL_BROADCAST_PAL) DCLogoColor = 0xFF5070C0;
         
    cblCable = syCblCheck();    
    
	switch(cblCable) 
	{
		default:
		case SYE_CBL_VGA : /* 640x480 VGA */
			sbInitSystem (KM_DSPMODE_VGA, KM_DSPBPP_RGB565, 1); 
			break;    
			
		case SYE_CBL_NTSC : /* U.S./North America NTSC (60Hz). */
			sbInitSystem (KM_DSPMODE_NTSCNI640x480, KM_DSPBPP_RGB565, 1);
			break;
			
		case SYE_CBL_PAL :	/* Europe PAL (50Hz). */
			sbInitSystem (KM_DSPMODE_PALNI640x480EXT, KM_DSPBPP_RGB565,1);
			
			/*	Change the PAL height ratio */
			kmSetPALEXTCallback(PALExtCallbackFunc,NULL);
			kmSetDisplayMode (KM_DSPMODE_PALNI640x480EXT, KM_DSPBPP_RGB565, TRUE, FALSE);
			
			break;
	}
	
	
	/* PRE-SORTING (to be set in KMShellSetBuffers())*/
	bTransAutosort = (bIsPreSort)?FALSE:TRUE;
	
	/* Logo background translucency */
	DCLogoBackTrans = dwDCLogoTrans;
	
	/* Black Border */
	cBorder.dwPacked	=	0x00000000;
	kmSetBorderColor(cBorder);
  
   return (KMDWORD) cblCable;
}
/*----------------------------------------------------------------------*/
/*  Function Name   : PALExtCallbackFunc                                */
/*  Inputs          : pCallbackArguments                                */  
/*  Outputs         : None                                              */
/*  Returns         : None                                              */
/*  Globals Used    :                                                   */
/*  Description     : PAL mode callback (used to set the height ratio)  */ 
/*----------------------------------------------------------------------*/
VOID STATIC	PALExtCallbackFunc(PVOID pCallbackArguments)
{
PKMPALEXTINFO	pInfo;

	pInfo = (PKMPALEXTINFO)pCallbackArguments;
	pInfo->nPALExtMode = KM_PALEXT_HEIGHT_RATIO_1_133;
	return;
}
/*----------------------------------------------------------------------*/
/*  Function Name   : KMShellSetBuffers                                 */
/*  Inputs          : VGAOn fOpaq fOpaqMV fTrans fTransMV fPnchTh       */  
/*  Outputs         : None                                              */
/*  Returns         : ErrorCode                                         */
/*  Globals Used    : VertexBufferDesc                                  */
/*  Description     : Init Kamui buffers.                               */ 
/*                    The size of each vertex buffer is given in %      */
/*----------------------------------------------------------------------*/
KMDWORD KMShellSetBuffers (float fOpaq, float fOpaqMV, float fTrans, float fTransMV,  float fPnchTh) 
{
KMDWORD	ErrorCode;

	pFB[0] = &PrimarySurfaceDesc;
	pFB[1] = &BackSurfaceDesc;
	
	SystemConfig.dwSize	=	sizeof(KMSYSTEMCONFIGSTRUCT);
	
	SystemConfig.flags	=	KM_CONFIGFLAG_ENABLE_CLEAR_FRAMEBUFFER |   /* Clear FB at initialization. */
   					    	KM_CONFIGFLAG_NOWAITVSYNC              |   /* Don't wait for the VBlank. */
                			KM_CONFIGFLAG_ENABLE_2V_LATENCY        |   /* Use 2V latency render model. */
							0;                		
                		

	/* for Frame buffer */
	SystemConfig.ppSurfaceDescArray		=	pFB;
	SystemConfig.fb.nNumOfFrameBuffer	=	2;
	SystemConfig.fb.nStripBufferHeight	=	32; 

	/* for Texture Memory */
	SystemConfig.nTextureMemorySize	 = TEXTUREMEMORYSIZE;	/* Texture */
	SystemConfig.nNumOfTextureStruct = MAXTEXTURES;         /* Maximum number of textures tracked. */
    SystemConfig.nNumOfSmallVQStruct = MAXSMALLVQ;         	/* Max. number of small VQ textures. */
    SystemConfig.pTextureWork 		 = TextureWorkArea;     /* Texture work area in system memory. */
    
	/* for Vertex buffer */
	/* Kamui2 requires the vertex buffer region to be 32-byte aligned and non-cacheable. */
    pVertexBuffer = (PKMDWORD) syMallocAlign32Byte (VERTEXBUFFERSIZE * 2);

    SystemConfig.nNumOfVertexBank	= 2;
    SystemConfig.pVertexBuffer 		= (PKMDWORD) SH4_P2NonCachedMem (pVertexBuffer);
    SystemConfig.nVertexBufferSize	= VERTEXBUFFERSIZE;	
	SystemConfig.pBufferDesc 		= &VertexBufferDesc; /* Struct used to maintain vertex buffer info. */
	
	/* Passes */
	SystemConfig.nPassDepth	= 1;
	
	SystemConfig.Pass[0].nDirectTransferList = KM_OPAQUE_POLYGON;   /* Type sent direct in 2V mode. */
	if(bTransAutosort)  SystemConfig.Pass[0].dwRegionArrayFlag = KM_PASSINFO_ENABLE_Z_CLEAR | KM_PASSINFO_AUTOSORT;
	else  				SystemConfig.Pass[0].dwRegionArrayFlag = KM_PASSINFO_ENABLE_Z_CLEAR | KM_PASSINFO_PRESORT;
	
   /* These amounts in % */
	SystemConfig.Pass[0].fBufferSize[0]		=	0;	/* Opaque is flushed */
	SystemConfig.Pass[0].fBufferSize[1]		=	fOpaqMV;	
	SystemConfig.Pass[0].fBufferSize[2]		=   fTrans;	
	SystemConfig.Pass[0].fBufferSize[3]		=	fTransMV;	
	SystemConfig.Pass[0].fBufferSize[4]		=	fPnchTh;	
	
	ErrorCode = kmSetSystemConfiguration( &SystemConfig );
	
	if (ErrorCode != KMSTATUS_SUCCESS) return ErrorCode;

	/* Everything's OK */
	return KMSTATUS_SUCCESS;
}

/*----------------------------------------------------------------------*/
/*  Function Name   : KMShellGetMaple                                   */
/*  Inputs          : None                                              */  
/*  Outputs         : None                                              */
/*  Returns         : None                                              */
/*  Globals Used    : VertexBufferDesc                                  */
/*  Description     :                                                   */
/*----------------------------------------------------------------------*/
PKMDWORD KMShellGetMaple (void)
{
	pdExecPeripheralServer();    

	PadPointer = (NJS_PERIPHERAL *)pdGetPeripheral(PDD_PORT_A0);

	if (PadPointer)
	{
		Pad = (unsigned)PadPointer->on;
	
		AnlgPadX = (int)PadPointer->x1;
		AnlgPadY = (int)PadPointer->y1;
	}
	else	Pad = (unsigned) 0;
}
/*----------------------------------------------------------------------*/

BOOL IsAKey(void) { return ((Pad & PDD_DGT_TA) ? TRUE : FALSE); }
BOOL IsBKey(void) { return ((Pad & PDD_DGT_TB) ? TRUE : FALSE); }
BOOL IsXKey(void) { return ((Pad & PDD_DGT_TX) ? TRUE : FALSE); }
BOOL IsYKey(void) { return ((Pad & PDD_DGT_TY) ? TRUE : FALSE); }

BOOL IsLFKey(void) { return ((Pad & PDD_DGT_TL) ? TRUE : FALSE); }
BOOL IsRFKey(void) { return ((Pad & PDD_DGT_TR) ? TRUE : FALSE); }

BOOL IsSTARTKey(void) { return ((Pad & PDD_DGT_ST) ? TRUE : FALSE); }

BOOL IsUPKey(void)	  { return ((Pad & PDD_DGT_KU) ? TRUE : FALSE); }
BOOL IsDOWNKey(void)  { return ((Pad & PDD_DGT_KD) ? TRUE : FALSE); }
BOOL IsLEFTKey(void)  { return ((Pad & PDD_DGT_KL) ? TRUE : FALSE); }
BOOL IsRIGHTKey(void) { return ((Pad & PDD_DGT_KR) ? TRUE : FALSE); }

int AnalogPadX(void) { return (AnlgPadX); }
int AnalogPadY(void) { return (AnlgPadY); }


/*----------------------------------------------------------------------*/
/*  Function Name   : KMShellQuitKamui                                  */
/*  Inputs          : None                                              */  
/*  Outputs         : None                                              */
/*  Returns         : None                                              */
/*  Globals Used    : VertexBufferDesc                                  */
/*  Description     : Free all buffers.                                 */
/*----------------------------------------------------------------------*/
void	KMShellQuitKamui(void)
{
	/* free logo texture */
	kmFreeTexture(&TexDCLogo);
	
	/* Free vertex buffer */
	kmDiscardVertexBuffer(&VertexBufferDesc);

	/* End display */
	kmStopDisplayFrameBuffer();

	/* Dreamcast end */
	sbExitSystem();

}
/*----------------------------------------------------------------------*/
/*  Function Name   :  KMShellInitStripHead		                        */
/*  Inputs          :  pStripHead, *pTexSurfDesc nMode                  */  
/*  Outputs         :  None                                             */
/*  Returns         :  None                                             */
/*  Globals Used    :  None                                             */
/*  Description     :  Sets standard render parameters.                 */
/*----------------------------------------------------------------------*/
void KMShellInitStripHead (PKMSTRIPHEAD	pStripHead,	KMSURFACEDESC  *pTexSurfDesc, int nMode)
{
KMSTRIPCONTEXT pStripContext;
int nPoly;

	memset (&pStripContext, 0, sizeof(KMSTRIPCONTEXT));

	pStripContext.nSize = sizeof(KMSTRIPCONTEXT);
	
	/* Defaults */
	pStripContext.StripControl.nListType		 						= KM_OPAQUE_POLYGON;
	pStripContext.StripControl.nUserClipMode	 						= KM_USERCLIP_DISABLE;
	pStripContext.StripControl.nShadowMode		 						= KM_NORMAL_POLYGON;
	pStripContext.StripControl.bOffset									= KM_FALSE;
	pStripContext.StripControl.bGouraud		 							= KM_TRUE;
	pStripContext.ObjectControl.nDepthCompare			 				= KM_GREATEREQUAL;
	pStripContext.ObjectControl.nCullingMode			 				= KM_NOCULLING;
	pStripContext.ObjectControl.bZWriteDisable							= KM_FALSE;
	pStripContext.ObjectControl.bDCalcControl			 				= KM_FALSE;
	pStripContext.ImageControl[KM_IMAGE_PARAM1].nSRCBlendingMode		= KM_ONE;
	pStripContext.ImageControl[KM_IMAGE_PARAM1].nDSTBlendingMode		= KM_ZERO;
	pStripContext.ImageControl[KM_IMAGE_PARAM1].bSRCSelect				= KM_FALSE;
	pStripContext.ImageControl[KM_IMAGE_PARAM1].bDSTSelect				= KM_FALSE;
	pStripContext.ImageControl[KM_IMAGE_PARAM1].nFogMode				= KM_NOFOG;
	pStripContext.ImageControl[KM_IMAGE_PARAM1].bColorClamp				= KM_FALSE;
	pStripContext.ImageControl[KM_IMAGE_PARAM1].bUseAlpha				= KM_FALSE;
	pStripContext.ImageControl[KM_IMAGE_PARAM1].bIgnoreTextureAlpha		= KM_FALSE;
	pStripContext.ImageControl[KM_IMAGE_PARAM1].nFlipUV					= KM_NOFLIP;
	pStripContext.ImageControl[KM_IMAGE_PARAM1].nClampUV				= KM_NOCLAMP;
	pStripContext.ImageControl[KM_IMAGE_PARAM1].nFilterMode				= KM_BILINEAR;
	pStripContext.ImageControl[KM_IMAGE_PARAM1].bSuperSampleMode		= KM_FALSE;
	pStripContext.ImageControl[KM_IMAGE_PARAM1].dwMipmapAdjust			= KM_MIPMAP_D_ADJUST_1_00;
	pStripContext.ImageControl[KM_IMAGE_PARAM1].nTextureShadingMode		= KM_MODULATE_ALPHA;
	pStripContext.ImageControl[KM_IMAGE_PARAM1].pTextureSurfaceDesc		= pTexSurfDesc;

	
	/* Polygon  type */
	nPoly = nMode & 3;
	  
	if (nPoly==VC_TRANS || nPoly==VC_ADDITIVE) 	pStripContext.StripControl.nListType = KM_TRANS_POLYGON;
	else if (nPoly==VC_PUNCHTHROUGH)  			pStripContext.StripControl.nListType = KM_PUNCHTHROUGH_POLYGON;
		
	/* Specular (Offset colour) */
	if (nMode & VC_SPECULAR)	pStripContext.StripControl.bOffset	= KM_TRUE;
	
	/* Culling backfaces */
	if(nMode & VC_CULLING)	pStripContext.ObjectControl.nCullingMode = KM_CULLCCW;
		
	/* Translucency */
	if (nPoly==VC_TRANS | nPoly==VC_PUNCHTHROUGH | nPoly==VC_ADDITIVE)
				pStripContext.ImageControl[KM_IMAGE_PARAM1].bUseAlpha	= KM_TRUE;
		
	/* Decal alpha */
	if (nMode & VC_DECALALPHA) 	pStripContext.ImageControl[KM_IMAGE_PARAM1].nTextureShadingMode	= KM_DECAL_ALPHA;
		
	/* Flip UVs */
	if (nMode & VC_UVFLIP) 	pStripContext.ImageControl[KM_IMAGE_PARAM1].nFlipUV	= KM_FLIP_UV;
	
	/* Blend modes */
	if (nPoly==VC_TRANS | nPoly==VC_PUNCHTHROUGH)
	{
		pStripContext.ImageControl[KM_IMAGE_PARAM1].nSRCBlendingMode  = KM_SRCALPHA;
		pStripContext.ImageControl[KM_IMAGE_PARAM1].nDSTBlendingMode  = KM_INVSRCALPHA;
	}
	else if (nPoly==VC_ADDITIVE)
	{
		pStripContext.ImageControl[KM_IMAGE_PARAM1].nSRCBlendingMode	= KM_ONE;
		pStripContext.ImageControl[KM_IMAGE_PARAM1].nDSTBlendingMode	= KM_ONE;
	}
	
	/* Fog */
	if (nMode & VC_FOGVERTEX)		pStripContext.ImageControl[KM_IMAGE_PARAM1].nFogMode = KM_FOGVERTEX;	
	else if (nMode & VC_FOGTABLE)	pStripContext.ImageControl[KM_IMAGE_PARAM1].nFogMode = KM_FOGTABLE;
	
	
	/* Create the strip head */
	kmGenerateStripHead03(pStripHead, &pStripContext);
}
/*----------------------------------------------------------------------*/
/*  Function Name   : KMShellStrips                                     */
/*  Inputs          : nNumStrips *pLen *pStrips *pVertices              */  
/*  Outputs         : None                                              */
/*  Returns         : None                                              */
/*  Globals Used    : VertexBufferDesc                                  */
/*  Description     : This is a Kamui version of sgltri_index_strips.   */
/*----------------------------------------------------------------------*/
void KMShellStrips (PKMSTRIPHEAD pStripHead, unsigned nNumStrips, unsigned short *pLen, 
						unsigned short *pStrips, KMVERTEX_03 *pVertices)
{
int i, j;
int nVertices;
int nFace, nFacesCont=0;

	/* Strips start */
	kmStartStrip(&VertexBufferDesc, pStripHead);
	
	for (j=0; j<nNumStrips; j++)
	{
	
		nVertices = *(pLen+j) + 1;
		
		/* Setting vertices */
		for(i = nVertices; i >= 0; i--)
		{
			nFace = *(pStrips+nFacesCont++);
			(pVertices+nFace)->ParamControlWord	= (i!=0)?KM_VERTEXPARAM_NORMAL:KM_VERTEXPARAM_ENDOFSTRIP;

			kmSetVertex (&VertexBufferDesc, (KMVERTEX_03 *)(pVertices+nFace), KM_VERTEXTYPE_03, sizeof (KMVERTEX_03));
		}
	}	
}
/*------------------------------------------------------------------------*/
/*  Function Name   : KMShellTriangles                                    */
/*  Inputs          : nNumfaces *pFaces *pVertices                        */  
/*  Outputs         : None                                                */
/*  Returns         : None                                                */
/*  Globals Used    : VertexBufferDesc                                    */
/*  Description     : This is a Kamui version of sgltri_index_triangles.  */
/*                                                                        */
/*  Warning			: To use triangles(one-poly strip) is not recomended  */
/*					  because it generates more pointers in the parameter */
/*					  buffer than longer strips.     					  */								
/*------------------------------------------------------------------------*/
void KMShellTriangles (PKMSTRIPHEAD pStripHead, unsigned nNumFaces,
						unsigned short *pFaces, KMVERTEX_03	*pVertices)
{
int nFace, nFacesCont=0, i;

	/* Strips start */
	kmStartStrip(&VertexBufferDesc, pStripHead);

	for(i = 0; i < nNumFaces; i++)
	{
			
		/* Vertex 1 */
		nFace = *(pFaces+nFacesCont++);
		(pVertices+nFace)->ParamControlWord	= KM_VERTEXPARAM_NORMAL;
		kmSetVertex (&VertexBufferDesc, (KMVERTEX_03 *)(pVertices+nFace), KM_VERTEXTYPE_03, sizeof (KMVERTEX_03));
		
		/* Vertex 2 */
		nFace = *(pFaces+nFacesCont++);
		(pVertices+nFace)->ParamControlWord	= KM_VERTEXPARAM_NORMAL;
		kmSetVertex (&VertexBufferDesc, (KMVERTEX_03 *)(pVertices+nFace), KM_VERTEXTYPE_03, sizeof (KMVERTEX_03));
			
		/* Vertex 3 */
		nFace = *(pFaces+nFacesCont++);
		(pVertices+nFace)->ParamControlWord	= KM_VERTEXPARAM_ENDOFSTRIP;
		kmSetVertex (&VertexBufferDesc, (KMVERTEX_03 *)(pVertices+nFace), KM_VERTEXTYPE_03, sizeof (KMVERTEX_03));
	}		
}

/*----------------------------------------------------------------------*/
/*  Function Name   :  KMShellBackground                                */
/*  Inputs          :  pStripHead      		                            */  
/*  Outputs         :  None                                             */
/*  Returns         :  None                                             */
/*  Globals Used    :  VertexBufferDesc                                 */
/*  Description     :  Draws a background polygon.                      */
/*----------------------------------------------------------------------*/
void KMShellBackground (PKMSTRIPHEAD pStripHead)
{
KMVERTEX_03     V[4];
int	i, k;

	V[0].ParamControlWord	= KM_VERTEXPARAM_NORMAL;
	V[1].ParamControlWord	= KM_VERTEXPARAM_NORMAL;
	V[2].ParamControlWord	= KM_VERTEXPARAM_NORMAL;
	V[3].ParamControlWord	= KM_VERTEXPARAM_ENDOFSTRIP;

	/* Colors */
	for (k=0;k<4;k++)
	{
	V[k].uBaseRGB.dwPacked	 = 0xFFFFFFFF;
	V[k].uOffsetRGB.dwPacked = 0x00000000;
	}

    /* Position */
    V[0].fX	= 0.0f;
	V[0].fY	= 480.0f;

	V[1].fX	= 0.0f;
	V[1].fY	= 0.0f;

	V[2].fX	= 640.0f;
	V[2].fY	= 480.0f;

	V[3].fX	= 640.0f;
	V[3].fY	= 0.0f;

	V[0].u.fZ =  0.00001;
	V[1].u.fZ =  0.00001;
	V[2].u.fZ =  0.00001;
	V[3].u.fZ =  0.00001;

	/* UVs */
	V[0].fU	=  0.0f;
	V[0].fV	=  0.0f;

	V[1].fU	=  0.0f;
	V[1].fV	=  1.0f;

	V[2].fU	=  1.0f;
	V[2].fV	=  0.0f;

    V[3].fU	=  1.0f;
	V[3].fV	=  1.0f;

	/* Strip start */
	kmStartStrip(&VertexBufferDesc, pStripHead);

	/* Setting vertices */
	for(i = 0; i<4; i++)
	{
		kmSetVertex (&VertexBufferDesc, (KMVERTEX_03 *)(&V[i]), KM_VERTEXTYPE_03, sizeof (KMVERTEX_03));
	}
   
}
/*----------------------------------------------------------------------*/
/*  Function Name   :  KMShellGetVertexBuffer                           */
/*  Inputs          :  *VertexContext                                   */  
/*  Outputs         :  None                                             */
/*  Returns         :  None                                             */
/*  Globals Used    :  VertexBufferDesc                                 */
/*  Description     :  Retrieve the vertex buffer pointer               */
/*----------------------------------------------------------------------*/
KMVERTEXBUFFDESC *KMShellGetVertexBuffer (void)
{
	return (&VertexBufferDesc);
}
/*----------------------------------------------------------------------*/
/*  Function Name   :  LoadDCLogo                                       */
/*  Inputs          :  None                                             */  
/*  Outputs         :  None                                             */
/*  Returns         :  None                                             */
/*  Globals Used    :                                                   */
/*  Description     :                                                   */
/*----------------------------------------------------------------------*/
void LoadDCLogo (void)
{
	/* Create texture surface */
	kmCreateTextureSurface(&TexDCLogo, 128,	128, KM_TEXTURE_VQ | KM_TEXTURE_ARGB4444);

	/* Load and set texture */
	kmLoadTexture(&TexDCLogo, (unsigned long *)DCLogo + (16 / sizeof(KMDWORD)));

	KMShellInitStripHead (&DCLogoStripHead,  &TexDCLogo, VC_TRANS);
	
	KMShellInitStripHead (&DCLogoBackStripHead,  &TexDCLogo, VC_TRANS);
	kmChangeStripIgnoreTextureAlpha(&DCLogoBackStripHead, KM_IMAGE_PARAM1, TRUE);

}
/*----------------------------------------------------------------------*/
/*  Function Name   :  KMDisplayDCLogo                                  */
/*  Inputs          :  None      		                                */  
/*  Outputs         :  None                                             */
/*  Returns         :  None                                             */
/*  Globals Used    :                                                   */
/*  Description     :                                                   */
/*----------------------------------------------------------------------*/
void KMDisplayDCLogo (void)
{
KMVERTEX_03     V[4];
int	i, k;

	V[0].ParamControlWord	= KM_VERTEXPARAM_NORMAL;
	V[1].ParamControlWord	= KM_VERTEXPARAM_NORMAL;
	V[2].ParamControlWord	= KM_VERTEXPARAM_NORMAL;
	V[3].ParamControlWord	= KM_VERTEXPARAM_ENDOFSTRIP;
	
	/* Position */
    V[0].fX	= 530.0f;
	V[0].fY	= 110.0f;

	V[1].fX	= 530.0f;
	V[1].fY	= 10.0f;

	V[2].fX	= 630.0f;
	V[2].fY	= 110.0f;

	V[3].fX	= 630.0f;
	V[3].fY	= 10.0f;
	
	/* White Background */
	for (k=0;k<4;k++)
	{
		V[k].uBaseRGB.dwPacked	 = 0x00FFFFFF | (DCLogoBackTrans & 0xFF) << 24;
		V[k].uOffsetRGB.dwPacked = 0x00000000;
		V[k].u.fZ =  200.0f;
	}
	
	/* UVs */
	V[0].fU	=  0.0f;
	V[0].fV	=  0.5f;

	V[1].fU	=  0.0f;
	V[1].fV	=  1.0f;

	V[2].fU	=  100.0f/128.0f;
	V[2].fV	=  0.5f;

    V[3].fU	=  100.0f/128.0f;
	V[3].fV	=  1.0f;
	
	/* Strip start */
	kmStartStrip(&VertexBufferDesc, &DCLogoBackStripHead);	
	
	/* Setting vertices */
	for(i = 0; i<4; i++)
	{
		if(DCLogoBackTrans>0) /* Don't Draw if full translucent */
		{
			kmSetVertex (&VertexBufferDesc, (KMVERTEX_03 *)(&V[i]), KM_VERTEXTYPE_03, sizeof (KMVERTEX_03));
		}
	}

	/*  DC Swirl */
  	for (k=0;k<4;k++)
	{
		V[k].uBaseRGB.dwPacked	 = DCLogoColor;
		V[k].uOffsetRGB.dwPacked = 0x00000000;
		V[k].u.fZ =  201.0f;
	}

    /* UVs */
	V[0].fU	=  0.0f;
	V[0].fV	=  1.0f-100.0f/128.0f;

	V[1].fU	=  0.0f;
	V[1].fV	=  1.0f;

	V[2].fU	=  100.0f/128.0f;
	V[2].fV	=  1.0f-100.0f/128.0f;

    V[3].fU	=  100.0f/128.0f;
	V[3].fV	=  1.0f;
	
	

	/* Strip start */
	kmStartStrip(&VertexBufferDesc, &DCLogoStripHead);

	/* Setting vertices */
	for(i = 0; i<4; i++)
	{
		kmSetVertex (&VertexBufferDesc, (KMVERTEX_03 *)(&V[i]), KM_VERTEXTYPE_03, sizeof (KMVERTEX_03));
	}

}