/*****************************************************************************
  Athor:	 Carlos Sarria	
  Name :     Scanner
  Date :     July 1998 (Updated June 1999)
  Platform : Dreamcast Set5 (CLX2 + SH4) 
 
  Description : Generic modifier volume demo.

  Copyright : 1999 by VideoLogic Limited. All rights reserved.
******************************************************************************/
#include <math.h>

#include "KMTools.h"
#include "KMShell.h"

/*************************************************/
/*	Model                                        */
/*************************************************/
#include "DataTypedef.h"

extern Struct_Mesh     Mesh[];
extern Struct_Material Material[];
extern Struct_Texture  Texture[];

#define NUM_MESHES     8
#define NUM_TEXTURES   6
#define NUM_MATERIALS  6

/* MESHES */
#define M_DINOSKIN  0
#define M_BONES  1
#define M_SURFACE  2
#define M_SURFACE01  3
#define M_COLLAR  4
#define M_SCANNER  5
#define M_LOGO  6
#define M_BACKGROUND  7



/*************************************************/
/*	Globals                                      */
/*************************************************/

/* texture surface */
KMSURFACEDESC		Tex[256];				

/* Vertex context */
KMSTRIPHEAD		StripHead[256];		
KMSTRIPHEAD     MV_Dino, MV_Scanner[3];	

/* Vertex pointers*/
KMVERTEX_03			*KmVert[256];		

extern KMVERTEXBUFFDESC VertexBufferDesc;	/* is defined in KMShell.c */

int ScreenWidth=640, ScreenHeight=480;

km_vector CameraFrom		= { 0.0f, 0.0f, -100.0f};
km_vector CameraTo			= { 0.0f, 0.0f, 100.0f};
km_vector LightDirection	= { 1.0f, 1.0f, 1.0f};

float   nFrame = 0;
float	fXPos, fYPos;
float   MachineAngle = 0.0f, ScannerAngle = 0.0f;

BOOL    bStart = FALSE;

/* Info windows control */
DWORD dwCurrentWin= 0, dwDisplayWins = TRUE, InfoWin, TWin[10];

/**************************************************/
/* Prototypes                                     */
/**************************************************/

void	InitMeshes			(void); 
void 	LoadTextures 		(void);
void 	CreateContexts 		(void);
void	RenderObject		(int Object, KMSTRIPHEAD *StripHead);
void 	CreateWindows 		(void);

void	ModVolContext		(void);
void	RenderObjectMV		(int);
void	RenderObjectSHV		(int Object);

void	kmtri_stripsMV		(KMVERTEXBUFFDESC BufferDesc, unsigned nNumStrips, unsigned short *pLen, 
								unsigned short *pStrips, KMVERTEX_03 *pVertices);

void	kmtri_trianglesSHV (KMVERTEXBUFFDESC BufferDesc, unsigned nNumFaces, unsigned short *pFaces,
								KMVERTEX_03	*pVertices);

/************************************************************************/
/* KMShell functions:                                                   */
/*    KMInitApplication                                                 */
/*    KMQuitApplication                                                 */
/*    KMRenderScene                                                     */
/*    KMPadControl                                                      * 
/*                                                                      */
/* WARNING : These functions must be created always because are called  */
/*           by KMShell.											    */
/************************************************************************/
/*----------------------------------------------------------------------*
 *  Function Name   :  InitApplication                              
 *  Inputs          :  None                                               
 *  Outputs         :  None                                                 
 *  Returns         :                                              
 *  Globals Used    :                                                
 *  Description     :   InitApplication() is called by KMShell to enable
 *						the user to initialise the application                                           
 *----------------------------------------------------------------------*/
void InitApplication (void)
{

	KMShellSetVideo	(FALSE,  /* FALSE = Hardware Trans Sorting  TRUE = User Trans PreSort  */
					 0x80   /* Logo background translucency */
					 );
					 
	KMShellSetBuffers (	 0, 	/* % Opaque  (all opaque flushed) */
					     0,		/* % ModVol Opaque */
					    80,		/* % Translucent   */
					    20,		/* % ModVol Trans  */
					     0);	

	KMPrint3DSetTextures();

	LoadTextures ();
	CreateContexts ();
	
	CreateWindows ();

	InitMeshes();
}
/*----------------------------------------------------------------------*
 *  Function Name   :  QuitApplication                                 
 *  Inputs          :  None                                               
 *  Outputs         :  None                                                 
 *  Returns         :                                            
 *  Globals Used    :                                                 
 *  Description     :  QuitApplication() is called by KMShell to enable
 *						the user to finish the application                                                 
 *----------------------------------------------------------------------*/
void QuitApplication (void)
{
register i;

	KMPrint3DReleaseTextures ();

	/* FREE TEXTURES */
	kmFreeTexture(&Tex[M_BONES]);
	kmFreeTexture(&Tex[M_SURFACE]);
	kmFreeTexture(&Tex[M_SCANNER]);
	kmFreeTexture(&Tex[M_SURFACE01]);
	kmFreeTexture(&Tex[M_BACKGROUND]);
	kmFreeTexture(&Tex[M_DINOSKIN]);
	kmFreeTexture(&Tex[M_SCANNER]);
	kmFreeTexture(&Tex[M_LOGO]);
	kmFreeTexture(&Tex[M_COLLAR]);		
	
	for (i=0; i<NUM_MESHES; i++) 
	{
		syFree(KmVert[i]);
	}

}

/*----------------------------------------------------------------------*
 *  Function Name   :  RenderScene                                      
 *  Inputs          :  None                                               
 *  Outputs         :  None                                                 
 *  Returns         :  FALSE to finish                                               
 *  Globals Used    :                                           
 *  Description     :  Draws everything in the scene.                                                 
 *----------------------------------------------------------------------*/
int RenderScene (void)
{
int i;
MATRIX Matrx;

   KMShellBackground (&StripHead[M_BACKGROUND]);
   
   if (bStart == FALSE)
   {
		MachineAngle += PI/500.0f;
		ScannerAngle += PI/75.0f;
   }
   
   for (i=0; i<NUM_MESHES;i++)
   {
		if(i==M_BACKGROUND) continue; /* The background is drawn appart. */
		
		KMMatrixReset(&Matrx);

		if (i==M_SCANNER)
		{
			KMMatrixRotate(&Matrx, -ScannerAngle, 0.0f, 0.0f);
			KMMatrixTranslate (&Matrx, 0.0f, 0.0f, 100.0f * sin(ScannerAngle));
		}

		KMMatrixRotate(&Matrx, 0.0f, 0.0f, -PI*0.02f);
		KMMatrixRotate(&Matrx, 0.0f, MachineAngle, 0.0f);
		KMMatrixTranslate (&Matrx, 0.0f, 0.0f, 110.0f); 
		
		/* Transform */
		KMTransTransformProjectPerspective (&Matrx, Mesh[i].nNumVertex, Mesh[i].pVertex, 
										KmVert[i], ScreenWidth, ScreenHeight,
										CameraFrom, CameraTo, 0.0f, 1.0f, 1000000.0f, 60.0f*(PI/180.0f));
		/* lighting */
		if(i!=M_BONES && i!=M_SCANNER && i!=M_LOGO && i!=M_SURFACE01)
		{
			KMLightSmoothShade (&Matrx, Mesh[i].nNumVertex, Mesh[i].pNormals, (KMVERTEX_03 *)KmVert[i],
						LightDirection, 0xFFFFFFFF, FALSE);	

		}

		if (i==M_DINOSKIN) /* Modified volume (Dino's skin)*/
		{
			RenderObjectMV (i);
		}
		else  /* Standard object */
		{
			RenderObject (i, &StripHead[i]);
		}

	}
   
	RenderObjectSHV (M_SCANNER); /* Modifier volume (Torus)*/

 
  	/* 
	 * Text windows.
	 */
	 if(dwDisplayWins)
	 {
		KMPrint3DDisplayWindow(TWin[dwCurrentWin]);
		 }

   nFrame++;     

	/* RenderScene OK */
	return TRUE;

}
/*-------------------------------------------------------------------------------------* 
 *  Function Name   : PadControl()                                                         
 *  Inputs          : None                                                               
 *  Outputs         : None                                                               
 *  Returns         : TRUE to continue, FALSE to finish the app.                                                               
 *  Globals Used    :                                   
 *  Description     : PadControl() is called by KMShell every frameto enable
 *						the user to control the joystick                                 
 *-------------------------------------------------------------------------------------*/
int PadControl (void)
{	
	static	int	Delay = 0;

	Delay++;

	/* START */
	if (IsSTARTKey())
	{
		if (Delay>10) bStart = !bStart;
		Delay = 0;
	}
	
	/* UP/DOWN X-PAD */
	if (IsUPKey() || IsDOWNKey())
	{
		if(Delay>2)
		{
			dwDisplayWins = !dwDisplayWins;
		}
		Delay = 0;
	}

	

	/* LEFT X-PAD */
	if (IsLEFTKey())
	{
		if(Delay>2)
		{
			dwDisplayWins = TRUE;
			dwCurrentWin--;
			if (dwCurrentWin==-1) dwCurrentWin = 1;
		}
		Delay =0;
								
	}

	/* RIGHT X-PAD */
	if (IsRIGHTKey())
	{
		if(Delay>2)
		{
			dwDisplayWins = TRUE;
			dwCurrentWin++;
			if (dwCurrentWin==2) dwCurrentWin = 0;
		}
		Delay =0;
	}

	
	/* No controler until START is pressed */
	if (bStart == FALSE) return TRUE;
	
	/* UP */
	if (AnalogPadY()<-64)
	{
		ScannerAngle += 0.05f;
	}

	/* DOWN */
	if (AnalogPadY()>64)
	{
		ScannerAngle  -= 0.05f;
	}

	/* LEFT */
	if (AnalogPadX()<-64)
	{
		MachineAngle  += 0.05f;
	}

	/* RIGHT */
	if (AnalogPadX()>64)
	{
		MachineAngle  -= 0.05f;
	}


	/* A button */
	if (IsAKey())
	{
	}
	
	/* B button */
	if (IsBKey())
	{
	}
		
	/* X button */
	if (IsXKey())
	{
	}

	/* Y button */
	if (IsYKey())
	{
	}

	/* LEFT finger button */
	if (IsLFKey())
	{
	}

	/* RIGHT finger button */
	if (IsRFKey())
	{
	}
	
	return TRUE;
}
/*-------------------------------------------------------------------------------------*
 *  Function Name   : InitMeshes                                                      
 *  Inputs          : None                                                             
 *  Outputs         : None                                                           
 *  Returns         : None                                                             
 *  Globals Used    :                              
 *  Description     : Sets initials values for meshes managment.                         
 *-------------------------------------------------------------------------------------*/
void InitMeshes (void)
{
register unsigned i,j, k=0;

	/* Memory allocation for KmVert */
	for (i=0; i<NUM_MESHES; i++) 
	{
		KmVert[i] = (KMVERTEX_03 *)syMalloc(Mesh[i].nNumVertex*sizeof(KMVERTEX_03));
	}

	/* Setting UV values and colors for all the meshes */
    for (i=0; i<NUM_MESHES;i++)
	{
		for (j=0; j<Mesh[i].nNumVertex; j++)
		{
            (KmVert[i]+j)->fU				= *(Mesh[i].pUV+j*2+0);
            (KmVert[i]+j)->fV				= *(Mesh[i].pUV+j*2+1);

			(KmVert[i]+j)->uBaseRGB.dwPacked	= 0xA0FFFFFF;
			(KmVert[i]+j)->uOffsetRGB.dwPacked	= 0xFF000000;
		
		}     
	}
 
  
}
/*-------------------------------------------------------------------------------------* 
 *  Function Name   : LoadTextures                                                         
 *  Inputs          : None                                                               
 *  Outputs         : None                                                               
 *  Returns         : None                                                               
 *  Globals Used    :                                   
 *  Description     : Convert textures from a 24bits Bitmap format to a 16bits hardware 
 *                    format and loads them in video memory.                    
 *-------------------------------------------------------------------------------------*/
void LoadTextures (void)
{
int i, j;
int nMaterial, nTexture;


	for (i=0; i<NUM_MESHES; i++)
	{
	
		nMaterial = Mesh[i].nMaterial;
		
		if (nMaterial == -1) continue; /* No material defined for this object */
		
		nTexture = -1;
		
		/* Looking for the texture that fits the difusse file names of the current material */
		for (j=0; j<NUM_TEXTURES; j++)
		{
			if (strcmp(Material[nMaterial].sDifusseFile, Texture[j].sTextureFileName) == 0) 
			{
				nTexture = j;
			}
			
		}
		
		if(nTexture==-1) continue; /* Humm... */
		
		/* Convert from 24bits to 16bits formated and load in video memmory (24bits texture data comes from Scanner.htx) */	
		if (i==M_LOGO) /* No mipmap for the logo and background */
		{
			KMTextureConvertAndLoad(&Tex[i], Texture[nTexture].pBitmapData, NULL, 
						Texture[nTexture].nWidth, Texture[nTexture].nHeight, KM_TEXTURE_TWIDDLED | KM_TEXTURE_RGB565);
		}
		else
		{
				KMTextureConvertAndLoad(&Tex[i], Texture[nTexture].pBitmapData, NULL, 
						Texture[nTexture].nWidth, Texture[nTexture].nHeight, KM_TEXTURE_TWIDDLED_MM | KM_TEXTURE_RGB565);
		}
	}
}
/*-------------------------------------------------------------------------------------* 
 *  Function Name   : CreateContexts                                                         
 *  Inputs          : None                                                               
 *  Outputs         : None                                                               
 *  Returns         : None                                                               
 *  Globals Used    :                                   
 *  Description     : All the contexts needed by the application.          
 *-------------------------------------------------------------------------------------*/
void CreateContexts (void)
{
	/* VERTEX CONTEXT */
	KMShellInitStripHead (&StripHead[M_BONES],		&Tex[M_BONES],		VC_OPAQUE);
	KMShellInitStripHead (&StripHead[M_SURFACE],	&Tex[M_SURFACE],	VC_OPAQUE);
	KMShellInitStripHead (&StripHead[M_SURFACE01],	&Tex[M_SURFACE01],	VC_OPAQUE);
	KMShellInitStripHead (&StripHead[M_COLLAR],		&Tex[M_COLLAR],	    VC_OPAQUE);
	KMShellInitStripHead (&StripHead[M_BACKGROUND],	&Tex[M_BACKGROUND],	VC_OPAQUE);
	KMShellInitStripHead (&StripHead[M_DINOSKIN],	&Tex[M_DINOSKIN],	VC_TRANS );
	KMShellInitStripHead (&StripHead[M_SCANNER],	&Tex[M_SCANNER],	VC_TRANS | VC_CULLING);
	KMShellInitStripHead (&StripHead[M_LOGO],		&Tex[M_LOGO],		VC_OPAQUE);

	/* Setting a special context for our modifier volume */
	ModVolContext (); 
}
/*-------------------------------------------------------------------------------------*
 *  Function Name   : RenderObject                                              
 *  Inputs          : Object pStripHead                                                       
 *  Outputs         : None                                                         
 *  Returns         : None                                                           
 *  Globals Used    :                                                               
 *  Description     : Sending a set of strips to render.                         
 *-------------------------------------------------------------------------------------*/
void RenderObject (int Object, KMSTRIPHEAD *pStripHead)
{
	KMShellStrips (pStripHead, Mesh[Object].nNumStrips, Mesh[Object].pStripLength,
		          Mesh[Object].pStrips, KmVert[Object]);

}
/*----------------------------------------------------------------------*
 *  Function Name   :  RenderObjectMV                                      
 *  Inputs          :  Object                                                  
 *  Outputs         :  None                                                 
 *  Returns         :  None                                                 
 *  Globals Used    :                                                   
 *  Description     :  This is the Dino's Skin                                                
 *----------------------------------------------------------------------*/
void RenderObjectMV (int Object)
{
	kmtri_stripsMV (VertexBufferDesc,	Mesh[Object].nNumStrips, Mesh[Object].pStripLength,
		            Mesh[Object].pStrips, KmVert[Object]);

}
/*----------------------------------------------------------------------*
 *  Function Name   :  RenderObjectSHV                                      
 *  Inputs          :  Object                                                  
 *  Outputs         :  None                                                 
 *  Returns         :  None                                                 
 *  Globals Used    :                                                   
 *  Description     :  This is the Torus.                                                 
 *----------------------------------------------------------------------*/
void RenderObjectSHV (int Object)
{
	kmtri_trianglesSHV (VertexBufferDesc,  Mesh[Object].nNumFaces, Mesh[Object].pFaces, KmVert[Object]);
}

/*----------------------------------------------------------------------*
 *  Function Name   :  ModVolContext                                      
 *  Inputs          :  None                                                  
 *  Outputs         :  None                                                 
 *  Returns         :  None                                                 
 *  Globals Used    :                                                   
 *  Description     :  Modified/Modifier Volume contexts.                                                
 *----------------------------------------------------------------------*/
void ModVolContext (void)
{
KMSTRIPCONTEXT  SC_MV_Scanner;
KMTWOVOLUMESTRIPCONTEXT SC_MV_Dino;

	memset(&SC_MV_Dino, 0, sizeof(KMTWOVOLUMESTRIPCONTEXT));
	memset(&MV_Dino, 	0, sizeof(KMSTRIPHEAD));
	
	SC_MV_Dino.nSize 												= sizeof(KMTWOVOLUMESTRIPCONTEXT);
	SC_MV_Dino.StripControl.nListType		 						= KM_TRANS_POLYGON;
	SC_MV_Dino.StripControl.nUserClipMode	 						= KM_USERCLIP_DISABLE;
	SC_MV_Dino.StripControl.bOffset									= KM_FALSE;
	SC_MV_Dino.StripControl.bGouraud		 						= KM_TRUE;
	SC_MV_Dino.ObjectControl.nDepthCompare			 				= KM_GREATEREQUAL;
	SC_MV_Dino.ObjectControl.nCullingMode			 				= KM_NOCULLING;
	SC_MV_Dino.ObjectControl.bZWriteDisable							= KM_FALSE;
	SC_MV_Dino.ObjectControl.bDCalcControl			 				= KM_FALSE;
	SC_MV_Dino.ImageControl[KM_IMAGE_PARAM1].nSRCBlendingMode		= KM_ONE;
	SC_MV_Dino.ImageControl[KM_IMAGE_PARAM1].nDSTBlendingMode		= KM_ZERO;
	SC_MV_Dino.ImageControl[KM_IMAGE_PARAM1].bSRCSelect				= KM_FALSE;
	SC_MV_Dino.ImageControl[KM_IMAGE_PARAM1].bDSTSelect				= KM_FALSE;
	SC_MV_Dino.ImageControl[KM_IMAGE_PARAM1].nFogMode				= KM_NOFOG;
	SC_MV_Dino.ImageControl[KM_IMAGE_PARAM1].bColorClamp			= KM_FALSE;
	SC_MV_Dino.ImageControl[KM_IMAGE_PARAM1].bUseAlpha				= KM_TRUE;
	SC_MV_Dino.ImageControl[KM_IMAGE_PARAM1].bIgnoreTextureAlpha	= KM_FALSE;
	SC_MV_Dino.ImageControl[KM_IMAGE_PARAM1].nFlipUV				= KM_NOFLIP;
	SC_MV_Dino.ImageControl[KM_IMAGE_PARAM1].nClampUV				= KM_NOCLAMP;
	SC_MV_Dino.ImageControl[KM_IMAGE_PARAM1].nFilterMode			= KM_BILINEAR;
	SC_MV_Dino.ImageControl[KM_IMAGE_PARAM1].bSuperSampleMode		= KM_FALSE;
	SC_MV_Dino.ImageControl[KM_IMAGE_PARAM1].dwMipmapAdjust			= KM_MIPMAP_D_ADJUST_1_00;
	SC_MV_Dino.ImageControl[KM_IMAGE_PARAM1].nTextureShadingMode	= KM_MODULATE_ALPHA;
	SC_MV_Dino.ImageControl[KM_IMAGE_PARAM1].pTextureSurfaceDesc	= &Tex[M_DINOSKIN];

	SC_MV_Dino.ImageControl[KM_IMAGE_PARAM2].nSRCBlendingMode		= KM_SRCALPHA;
	SC_MV_Dino.ImageControl[KM_IMAGE_PARAM2].nDSTBlendingMode		= KM_INVSRCALPHA;
	SC_MV_Dino.ImageControl[KM_IMAGE_PARAM2].bSRCSelect				= KM_FALSE;
	SC_MV_Dino.ImageControl[KM_IMAGE_PARAM2].bDSTSelect				= KM_FALSE;
	SC_MV_Dino.ImageControl[KM_IMAGE_PARAM2].nFogMode				= KM_NOFOG;
	SC_MV_Dino.ImageControl[KM_IMAGE_PARAM2].bColorClamp			= KM_FALSE;
	SC_MV_Dino.ImageControl[KM_IMAGE_PARAM2].bUseAlpha				= KM_TRUE;
	SC_MV_Dino.ImageControl[KM_IMAGE_PARAM2].bIgnoreTextureAlpha	= KM_FALSE;
	SC_MV_Dino.ImageControl[KM_IMAGE_PARAM2].nFlipUV				= KM_NOFLIP;
	SC_MV_Dino.ImageControl[KM_IMAGE_PARAM2].nClampUV				= KM_NOCLAMP;
	SC_MV_Dino.ImageControl[KM_IMAGE_PARAM2].nFilterMode			= KM_BILINEAR;
	SC_MV_Dino.ImageControl[KM_IMAGE_PARAM2].bSuperSampleMode		= KM_FALSE;
	SC_MV_Dino.ImageControl[KM_IMAGE_PARAM2].dwMipmapAdjust			= KM_MIPMAP_D_ADJUST_1_00;
	SC_MV_Dino.ImageControl[KM_IMAGE_PARAM2].nTextureShadingMode	= KM_MODULATE_ALPHA;
	SC_MV_Dino.ImageControl[KM_IMAGE_PARAM2].pTextureSurfaceDesc	= &Tex[M_BONES];

    kmGenerateStripHead11 (&MV_Dino, (KMSTRIPCONTEXT *)&SC_MV_Dino);
	
		
	/**************************
	 * ModifierVolume-First	  *
	 **************************/
	memset(&MV_Scanner[0], 	0, sizeof(KMSTRIPHEAD));
	memset(&SC_MV_Scanner,	0, sizeof(KMSTRIPCONTEXT));
	
	SC_MV_Scanner.nSize = sizeof(KMSTRIPCONTEXT);
	SC_MV_Scanner.StripControl.nListType							= KM_TRANS_MODIFIER;
	SC_MV_Scanner.StripControl.nUserClipMode						= KM_USERCLIP_DISABLE;
	SC_MV_Scanner.ObjectControl.nCullingMode						= KM_NOCULLING;
	SC_MV_Scanner.ObjectControl.dwModifierInstruction				= KM_MODIFIER_INCLUDE_FIRST_POLY;

	kmGenerateStripHead17(&MV_Scanner[0], &SC_MV_Scanner);

	/**************************
	 * ModifierVolume-Normal  *
	 **************************/
	memset(&MV_Scanner[1], 	0, sizeof(KMSTRIPHEAD));
	memset(&SC_MV_Scanner,	0, sizeof(KMSTRIPCONTEXT));
	
	SC_MV_Scanner.nSize = sizeof(KMSTRIPCONTEXT);
	SC_MV_Scanner.StripControl.nListType							= KM_TRANS_MODIFIER;
	SC_MV_Scanner.StripControl.nUserClipMode						= KM_USERCLIP_DISABLE;
	SC_MV_Scanner.ObjectControl.nCullingMode						= KM_NOCULLING;
	SC_MV_Scanner.ObjectControl.dwModifierInstruction				= KM_MODIFIER_NORMAL_POLY;

	kmGenerateStripHead17(&MV_Scanner[1], &SC_MV_Scanner);
	
	/**************************
	 * ModifierVolume-Last	  *
	 **************************/
	memset(&MV_Scanner[2], 	0, sizeof(KMSTRIPHEAD));
	memset(&SC_MV_Scanner,	0, sizeof(KMSTRIPCONTEXT));
	
	SC_MV_Scanner.nSize = sizeof(KMSTRIPCONTEXT);
	SC_MV_Scanner.StripControl.nListType							= KM_TRANS_MODIFIER;
	SC_MV_Scanner.StripControl.nUserClipMode						= KM_USERCLIP_DISABLE;
	SC_MV_Scanner.ObjectControl.nCullingMode						= KM_NOCULLING;
	SC_MV_Scanner.ObjectControl.dwModifierInstruction				= KM_MODIFIER_INCLUDE_LAST_POLY;

	kmGenerateStripHead17(&MV_Scanner[2], &SC_MV_Scanner);
}

/*----------------------------------------------------------------------*
 *  Function Name   :   kmtri_stripsMV             
 *  Inputs          :   BufferDesc  nNumStrips  pLen  pStrips pVertices                            
 *  Outputs         :   None                                              
 *  Returns         :   None                                                
 *  Globals Used    :                                                
 *  Description     :   Special version of kmtri_strips for Modified Vol.                                                
 *                      Translation from KMVERTEX03 to KMVERTEX11.
 *----------------------------------------------------------------------*/
void kmtri_stripsMV (KMVERTEXBUFFDESC	BufferDesc,	unsigned nNumStrips, unsigned short *pLen, 
							unsigned short *pStrips, KMVERTEX_03 *pVertices)
{
int i, j;
int nVertices;
int nFace, nFacesCont=0;
unsigned nPointer=0;
KMVERTEX_11 Buffer;

	kmStartStrip(&BufferDesc, &MV_Dino);
	
    for (j=0; j<nNumStrips; j++)
	{
		nVertices = *(pLen+j) + 1;

        nFacesCont = nPointer;
    
    	for(i = nVertices; i >= 0; i--)
		{
			nFace = *(pStrips+nFacesCont++);
			(pVertices+nFace)->ParamControlWord	= (i!=0)?KM_VERTEXPARAM_NORMAL:KM_VERTEXPARAM_ENDOFSTRIP;
			
			Buffer.ParamControlWord			= (i!=0)?KM_VERTEXPARAM_NORMAL:KM_VERTEXPARAM_ENDOFSTRIP;
			Buffer.fX 						= (pVertices+nFace)->fX;
			Buffer.fY 						= (pVertices+nFace)->fY; 
			Buffer.u.fZ 					= (pVertices+nFace)->u.fZ; 
			Buffer.fU0m 					= (pVertices+nFace)->fU;
			Buffer.fV0m 					= (pVertices+nFace)->fV;
 			Buffer.uBaseRGB0m.dwPacked 		= (pVertices+nFace)->uBaseRGB.dwPacked; 
 			Buffer.uOffsetRGB0m.dwPacked 	= 0x00000000;
			Buffer.fU1m					 	= (pVertices+nFace)->fU; 
			Buffer.fV1m 					= (pVertices+nFace)->fV;
			Buffer.uBaseRGB1m.dwPacked 		= 0x80FFFFFF; 
			Buffer.uOffsetRGB1m.dwPacked 	= 0x00000000;
		
			kmSetVertex (&BufferDesc, (KMVERTEX_11 *)&Buffer, KM_VERTEXTYPE_11, sizeof (KMVERTEX_11));
		}
		
		nPointer+=nVertices+1;
	}					
		
	/* Strips end */
    kmEndStrip (&BufferDesc);
		    
}

/*----------------------------------------------------------------------*
 *  Function Name   :   kmtri_trianglesSHV             
 *  Inputs          :   BufferDesc  nNumFaces  pFaces pVertices                            
 *  Outputs         :   None                                              
 *  Returns         :   None                                                 
 *  Globals Used    :                                                
 *  Description     :   Special version of kmtri_triangles for Modified Vol.                                                
 *                      Translation from KMVERTEX03 to KMVERTEX17.
 *----------------------------------------------------------------------*/
void kmtri_trianglesSHV ( KMVERTEXBUFFDESC	BufferDesc,	unsigned nNumFaces, unsigned short *pFaces, 
							KMVERTEX_03	*pVertices)
{
int nFace, nFacesCont=0, i;
KMVERTEX_17 Buffer;

	
	for(i = 0; i < nNumFaces; i++)
	{
		if (i==0)			kmStartStrip(&BufferDesc, &MV_Scanner[0]); /* Start  */
		if (i==1)			kmStartStrip(&BufferDesc, &MV_Scanner[1]); /* Normal */
		if (i==nNumFaces-1)	kmStartStrip(&BufferDesc, &MV_Scanner[2]); /* End    */

		/* Vertices */
		Buffer.ParamControlWord	= KM_VERTEXPARAM_ENDOFSTRIP;
		
		nFace = *(pFaces+nFacesCont++);
		Buffer.fAX = (pVertices+nFace)->fX;
		Buffer.fAY = (pVertices+nFace)->fY;
		Buffer.uA.fAZ = (pVertices+nFace)->u.fZ;
			
		nFace = *(pFaces+nFacesCont++);
		Buffer.fBX = (pVertices+nFace)->fX;
		Buffer.fBY = (pVertices+nFace)->fY;
		Buffer.uB.fBZ = (pVertices+nFace)->u.fZ;

		nFace = *(pFaces+nFacesCont++);
		Buffer.fCX = (pVertices+nFace)->fX;
		Buffer.fCY = (pVertices+nFace)->fY;
		Buffer.uC.fCZ = (pVertices+nFace)->u.fZ;

		kmSetVertex (&BufferDesc, (KMVERTEX_17 *)&Buffer, KM_VERTEXTYPE_17, sizeof (KMVERTEX_17));
		
		if(i==0 || i==nNumFaces-2 || i==nNumFaces-1)
		{
			/* Strips end */
		    kmEndStrip (&BufferDesc);
		}
		
	}					
	
}
/*----------------------------------------------------------------------*
 *  Function Name   :  CreateWindows         
 *  Inputs          :  None                                   
 *  Outputs         :  None                                                
 *  Returns         :  None                                                 
 *  Globals Used    :                                                
 *  Description     :  Info windows. 
 *----------------------------------------------------------------------*/
void CreateWindows (void)
{
	/* Info Window */
	InfoWin = KMPrint3DCreateDefaultWindow (80.0f, 93.0f, 150, NULL, " ");

	/* Text Windows */
	/* Window 0 */
	TWin[0] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 60, "SCANNER - Modifier Volume     ", NULL);


	/* Window 1 */
	TWin[1] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 60, "SCANNER - Modifier Volume (1 of 1)",
"This demo demonstrates the use of PowerSGL Direct2 modifier volumes. \
Modifier volumes perform real 3D clipping allowing the attributes of any objects contained in the volumes to be changed.\n\n\
In this case the torus object also defines a modifier volume which is used to draw the dinosaur skin using \
two different textures.\n\n (START) Rolling demo/Interactive\n (ANALOG PAD) Move scanner.\n\n");

}
/*----------------------------------------------------------------------*
 * END OF FILE
 *----------------------------------------------------------------------*/