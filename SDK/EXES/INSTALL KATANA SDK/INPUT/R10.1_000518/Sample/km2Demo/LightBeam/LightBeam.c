/*****************************************************************************
  Athor:	 Carlos Sarria	
  Name :     LightBeam
  Date :     Aug 1998
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
extern Struct_Texture  Texture[];

#define NUM_MESHES     7
#define NUM_TEXTURES   4

/* MESHES */
#define M_GROUND  0
#define M_LAMPBODY  1
#define M_LAMPLIGHT  2
#define M_BAR  3
#define M_BACKGROUND  4
#define M_LIGHTCONE  5
#define M_LAMPCONE  6

/*************************************************/
/*	Globals                                      */
/*************************************************/

/* texture surface */
KMSURFACEDESC		Tex[256];				

/* Vertex context */
KMSTRIPHEAD		StripHead[256];		
KMSTRIPHEAD     MV_Modified, MV_LightCone[3];
KMSTRIPHEAD 	pSShStripHead[3];

/* Vertex pointers*/
KMVERTEX_03			*KmVert[256];		

extern KMVERTEXBUFFDESC VertexBufferDesc;	/* is defined in KMShell.c */

int ScreenWidth=640, ScreenHeight=480;

km_vector CameraFrom		= { 0.0f, 0.0f, -100.0f};
km_vector CameraTo			= { 0.0f, 0.0f, 100.0f};
km_vector LightDirection	= { 1.0f, 1.0f, 1.0f};

float   nFrame = 0;
float	fXPos, fYPos;
float   fXAngle = 0.0f, fYAngle = 0.0f;

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

void	CheapShadowContext		(void);

void	kmtri_trianglesSHV (KMVERTEXBUFFDESC BufferDesc, unsigned nNumFaces, unsigned short *pFaces,
								KMVERTEX_03	*pVertices);
								
void 	RenderLight 		(int Object);								
void 	ScreenShadow 		(void);
void 	MoveLightUVs 		(void);
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
					 0x00   /* Logo background translucency */
					 );
					 
	KMShellSetBuffers (	 0, /* % Opaque  (all opaque flushed) */
					    20,	/* % ModVol Opaque */
					    80,	/* % Translucent   */
					     0,	/* % ModVol Trans  */
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
	kmFreeTexture(&Tex[M_GROUND]);
	kmFreeTexture(&Tex[M_LAMPBODY]);
	kmFreeTexture(&Tex[M_LAMPCONE]);
	kmFreeTexture(&Tex[M_LAMPLIGHT]);
		
	
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

	KMShellBackground(&StripHead[M_BACKGROUND]);
	
  /* Cover the screen with a cheap-shadow 'layer' 
   * Everything with the cheap-shadow flag in the scene will be made darker.
   */
  kmSetCheapShadowMode(100);
  ScreenShadow ();
   
   /*
    * Roll alone
    */
   	if (bStart == FALSE)
	{
		fYAngle = PI * sin((float)nFrame/128.0f)*0.2f+0.5f;
		fXAngle = (float)nFrame/64.0f;
	}
	
	MoveLightUVs();
	
   /*
    * Render all the standard objets.
    * Only the ground is affected by cheap-shadows.
    */
   for (i=0; i<NUM_MESHES;i++)
   {
   		if(i==M_BACKGROUND) continue;
   		
  		KMMatrixReset(&Matrx);

		if(i!=M_BAR)
		{
			KMMatrixRotate(&Matrx, 0.0f, 0.0f, fYAngle);
			KMMatrixRotate(&Matrx, 0.0f, fXAngle, 0.0f);
		}
		
		KMMatrixTranslate (&Matrx, 0.0f, 50.0f, 100.0f);
		
		if (i!=M_GROUND)
		{
			KMTransTransformProjectPerspective (&Matrx, Mesh[i].nNumVertex, Mesh[i].pVertex, 
										KmVert[i], ScreenWidth, ScreenHeight,
										CameraFrom, CameraTo, 0.0f, 1.0f, 1000000.0f, 60.0f*(PI/180.0f));
		}
		
		/* Transform the ground only once*/
		else if (nFrame==0)
		{
			KMMatrixReset(&Matrx);
			
			KMMatrixRotate(&Matrx, -0.1f, 0.0f, 0.0f);
			KMMatrixTranslate (&Matrx, 0.0f, -50.0f, 120.0f);
		
			KMTransTransformProjectPerspective (&Matrx, Mesh[i].nNumVertex, Mesh[i].pVertex, 
										KmVert[i], ScreenWidth, ScreenHeight,
										CameraFrom, CameraTo, 0.0f, 1.0f, 1000000.0f, 60.0f*(PI/180.0f));
										
		}

		if(i!=M_LIGHTCONE) RenderObject (i, &StripHead[i]);

	 }
      
     /* 
      * Exclusion cheap-shadows.
      * The shadow is removed from inside the light cone.
      */
     RenderLight (M_LIGHTCONE);
     
	 
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
			if (dwCurrentWin==-1) dwCurrentWin = 2;
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
			if (dwCurrentWin==3) dwCurrentWin = 0;
		}
		Delay =0;
	}

	
	/* No controler until START is pressed */
	if (bStart == FALSE) return TRUE;
	
	/* UP */
	if (AnalogPadY()<-64)
	{
		if(fYAngle<PI/3.5f)fYAngle += 0.05f;
	}

	/* DOWN */
	if (AnalogPadY()>64)
	{
		if(fYAngle>-PI/3.5f)fYAngle  -= 0.05f;
	}

	/* LEFT */
	if (AnalogPadX()<-64)
	{
		fXAngle  += 0.05f;
	}

	/* RIGHT */
	if (AnalogPadX()>64)
	{
		fXAngle  -= 0.05f;
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

			(KmVert[i]+j)->uBaseRGB.dwPacked	= 0xFFFFFFFF;
			(KmVert[i]+j)->uOffsetRGB.dwPacked	= 0xFF000000;
			
			if(i==M_LAMPCONE)
			{ 
				if(*(Mesh[i].pVertex+j*3+1) < -20.0f)
			 		(KmVert[i]+j)->uBaseRGB.dwPacked	= 0x00FFFFFF;
			 	else (KmVert[i]+j)->uBaseRGB.dwPacked	= 0x40FFFFFF;
			}
	
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
	KMTextureConvertAndLoad(&Tex[M_GROUND], Texture[0].pBitmapData, NULL, 
						Texture[0].nWidth, Texture[0].nHeight, KM_TEXTURE_TWIDDLED_MM | KM_TEXTURE_RGB565);
						
	KMTextureConvertAndLoad(&Tex[M_LAMPBODY], Texture[1].pBitmapData, NULL, 
						Texture[1].nWidth, Texture[1].nHeight, KM_TEXTURE_TWIDDLED | KM_TEXTURE_RGB565);
		
	KMTextureConvertAndLoad(&Tex[M_BACKGROUND], Texture[2].pBitmapData, NULL, 
						Texture[2].nWidth, Texture[2].nHeight, KM_TEXTURE_TWIDDLED | KM_TEXTURE_RGB565);
	
	KMTextureConvertAndLoad(&Tex[M_LAMPCONE], Texture[3].pBitmapData, NULL, 
						Texture[3].nWidth, Texture[3].nHeight, KM_TEXTURE_TWIDDLED | KM_TEXTURE_RGB565);
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
	KMShellInitStripHead (&StripHead[M_LAMPBODY],	&Tex[M_LAMPBODY],	VC_OPAQUE);
	KMShellInitStripHead (&StripHead[M_LAMPCONE],	&Tex[M_LAMPCONE],	VC_TRANS);
	KMShellInitStripHead (&StripHead[M_LAMPLIGHT],	&Tex[M_LAMPBODY],	VC_OPAQUE);
	KMShellInitStripHead (&StripHead[M_BAR],		&Tex[M_LAMPBODY],	VC_OPAQUE);
	KMShellInitStripHead (&StripHead[M_BACKGROUND],	&Tex[M_BACKGROUND],	VC_OPAQUE);
	
	KMShellInitStripHead (&StripHead[M_GROUND],	&Tex[M_GROUND],	VC_OPAQUE);
	kmChangeStripShadowMode (&StripHead[M_GROUND], KM_CHEAPSHADOW_POLYGON);
 
	
	/* Setting a special context for our modifier volume */
	CheapShadowContext ();
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
 *  Function Name   :  RenderObjectSHV                                      
 *  Inputs          :  Object                                                  
 *  Outputs         :  None                                                 
 *  Returns         :  None                                                 
 *  Globals Used    :                                                   
 *  Description     :  This is the Torus.                                                 
 *----------------------------------------------------------------------*/
void RenderLight (int Object)
{
	kmtri_trianglesSHV (VertexBufferDesc,  Mesh[Object].nNumFaces, Mesh[Object].pFaces, KmVert[Object]);
}

/*----------------------------------------------------------------------*
 *  Function Name   :  CheapShadowContext                                      
 *  Inputs          :  None                                                  
 *  Outputs         :  None                                                 
 *  Returns         :  None                                                 
 *  Globals Used    :                                                   
 *  Description     :  Modified/Modifier Volume contexts.                                                
 *----------------------------------------------------------------------*/
void CheapShadowContext (void)
{
KMSTRIPCONTEXT  SC_LightCone;
KMSTRIPCONTEXT	StripContext17;
	
	/**************************
	 * EXCLUSION CHEAP-SHADOW *
	 **************************/
	/**************************
	 * ModifierVolume-First	  *
	 **************************/
	memset(&MV_LightCone[0], 	0, sizeof(KMSTRIPHEAD)*3);
	memset(&SC_LightCone,	0, sizeof(KMSTRIPCONTEXT));
	
	SC_LightCone.nSize = sizeof(KMSTRIPCONTEXT);
	SC_LightCone.StripControl.nListType							= KM_OPAQUE_MODIFIER;
	SC_LightCone.StripControl.nUserClipMode						= KM_USERCLIP_DISABLE;
	SC_LightCone.ObjectControl.nCullingMode						= KM_NOCULLING;
	SC_LightCone.ObjectControl.dwModifierInstruction			= KM_MODIFIER_EXCLUDE_FIRST_POLY;

	kmGenerateStripHead17(&MV_LightCone[0], &SC_LightCone);

	/**************************
	 * ModifierVolume-Normal  *
	 **************************/
	SC_LightCone.ObjectControl.dwModifierInstruction				= KM_MODIFIER_NORMAL_POLY;
	kmGenerateStripHead17(&MV_LightCone[1], &SC_LightCone);
	
	/**************************
	 * ModifierVolume-Last    *
	 **************************/
	SC_LightCone.ObjectControl.dwModifierInstruction			= KM_MODIFIER_EXCLUDE_LAST_POLY;
	kmGenerateStripHead17(&MV_LightCone[2], &SC_LightCone);
	
	
	/**************************
	 * INCLUSION CHEAP-SHADOW *
	 **************************/
	/**************************
	 * ModifierVolume-First	  *
	 **************************/
	memset( &StripContext17, 0, sizeof(KMSTRIPCONTEXT));
	memset( &pSShStripHead[0]	, 0, sizeof(PKMSTRIPHEAD)*3);
	
	StripContext17.nSize									= sizeof(KMSTRIPCONTEXT);
	StripContext17.StripControl.nListType					= KM_OPAQUE_MODIFIER;
	StripContext17.StripControl.nUserClipMode				= KM_USERCLIP_DISABLE;
	StripContext17.ObjectControl.nCullingMode				= KM_NOCULLING;
	StripContext17.ObjectControl.dwModifierInstruction		= KM_MODIFIER_INCLUDE_FIRST_POLY;

	kmGenerateStripHead17(&pSShStripHead[0], &StripContext17);

	/**************************
	 * ModifierVolume-Normal  *
	 **************************/
	StripContext17.ObjectControl.dwModifierInstruction		= KM_MODIFIER_NORMAL_POLY;
	kmGenerateStripHead17(&pSShStripHead[1], &StripContext17);

	/**************************
	 * ModifierVolume-Last    *
	 **************************/
	StripContext17.ObjectControl.dwModifierInstruction		= KM_MODIFIER_INCLUDE_LAST_POLY;
	kmGenerateStripHead17(&pSShStripHead[2], &StripContext17);
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
		if (i==0)			kmStartStrip(&BufferDesc, &MV_LightCone[0]); /* Start  */
		if (i==1)			kmStartStrip(&BufferDesc, &MV_LightCone[1]); /* Normal */
		if (i==nNumFaces-1)	kmStartStrip(&BufferDesc, &MV_LightCone[2]); /* End    */

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
	TWin[0] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 60, "LIGHTBEAM - Cheap Shadows ", NULL);


	/* Window 1 */
	TWin[1] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 60, "LIGHTBEAM - Cheap Shadows (1 of 2)",
"This demo ilustrates the use of PowerSGL Direct2 'Cheap Shadows'. \
Cheap shadows are an optimized version of generic modifier volumes that perform real 3D clipping allowing \
the attributes of any objects contained in the volumes to be changed.\n\n\
In this case only the intensity of the light is changed.\n\n (START) Rolling demo/Interactive\n (ANALOG PAD) Move beam.\n\n");

	/* Window 2 */
	TWin[2] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 60, "LIGHTBEAM - Cheap Shadows (2 of 2)",
"Cheap shadows are normally only used for darkening objects, however in this case the effect is inverted: \
The entire landscape is emerged in a large shadow and the light beam volume is used to remove the shadow.\n\n");

}
/*----------------------------------------------------------------------*/
/*  Function Name   :  KMShellBackground                                */
/*  Inputs          :  pStripHead      		                            */  
/*  Outputs         :  None                                             */
/*  Returns         :  None                                             */
/*  Globals Used    :  VertexBufferDesc                                 */
/*  Description     :  Draws a background polygon.                      */
/*----------------------------------------------------------------------*/
void ScreenShadow (void)
{
KMVERTEX_17     V17[2];

	/***********************************
	 * VertexType17
	 ***********************************/
	
	V17[0].ParamControlWord	= KM_VERTEXPARAM_ENDOFSTRIP;
	V17[0].fAX		= 0.0f;	V17[0].fBX		= 0.0f;	V17[0].fCX		= 640.0f;
	V17[0].fAY		= 480.0f;	V17[0].fBY		= 0.0f;	V17[0].fCY		= 480.0f;
	V17[0].uA.fAZ	=   100.0f;	V17[0].uB.fBZ	=  100.0f;	V17[0].uC.fCZ	=  100.0f;
	
	kmStartStrip(&VertexBufferDesc, &pSShStripHead[1]);
	kmSetVertex (&VertexBufferDesc, (KMVERTEX_17 *)(&V17[0]), KM_VERTEXTYPE_17, sizeof (KMVERTEX_17));
	kmEndStrip (&VertexBufferDesc);
	    
	
	V17[1].ParamControlWord	= KM_VERTEXPARAM_ENDOFSTRIP;
	V17[1].fAX		= 640.0f;	V17[1].fBX		= 0.0f;	V17[1].fCX		= 640.0f;
	V17[1].fAY		= 480.0f;	V17[1].fBY		= 0.0f;	V17[1].fCY		= 0.0f;
	V17[1].uA.fAZ	=   100.0f;	V17[1].uB.fBZ	=   100.0f;	V17[1].uC.fCZ	=   100.0f;
	
	kmStartStrip(&VertexBufferDesc, &pSShStripHead[2]);
	kmSetVertex (&VertexBufferDesc, (KMVERTEX_17 *)(&V17[1]), KM_VERTEXTYPE_17, sizeof (KMVERTEX_17));

}
/*----------------------------------------------------------------------*/
/*  Function Name   :  MoveLightUVs                                     */
/*  Inputs          :  None      		                                */  
/*  Outputs         :  None                                             */
/*  Returns         :  None                                             */
/*  Globals Used    :                                                   */
/*  Description     :                                                   */
/*----------------------------------------------------------------------*/
void MoveLightUVs (void)
{
register j;
static float RevertPosition;

		for (j=0; j<Mesh[M_LAMPCONE].nNumVertex; j++)
		{
            (KmVert[M_LAMPCONE]+j)->fU	-= 0.005f;
            (KmVert[M_LAMPCONE]+j)->fV	-= 0.005f;

		}
	
}  
/*----------------------------------------------------------------------*
 * END OF FILE
 *----------------------------------------------------------------------*/