/*****************************************************************************
  Name :     Fortune
  Author:	 Carlos Sarria
  Date :     September 1998 (updated June 1999)
  Platform : Dreamcast Set5 (CLX2.2 + SH4)
 
  Description : 1 Gigapixel fill-rate demo.

  Copyright : 1999 by VideoLogic Limited. All rights reserved.
******************************************************************************/
#include <math.h>

#include "KMTools.h"
#include "KMShell.h"

#define TOTAL_CARDS 52
#define NUM_CARDS   42

#define CARD_REAL_AREA   154000 

/*************************************************/
/*	Model                                        */
/*************************************************/
#include "DataTypedef.h"

extern Struct_Material Material[];
extern Struct_Texture  Texture[];

/* MESHES */
#define NUM_MATERIALS  4
#define	NUM_TEXTURES   29

/*************************************************/
/*	Defines                                      */
/*************************************************/
#ifndef PI
	#define PI 3.14159f
#endif

typedef struct Card_Tag{
	float fVertex[4*3];
	float fNormal[4*3];
	float fU[4];
	float fV[4];
	float fTU[4];
	float fTV[4];
	float fShU[4];
	float fShV[4];
	int   Texture;
	float Displ;
	KMVERTEX_03 KmVert[4];
} CARD_TYPE;


/*************************************************/
/*	Globals                                      */
/*************************************************/
int bStart = FALSE;

int CurrentCard = 0;
float PosZ = 50.0f;

CARD_TYPE   Card[TOTAL_CARDS];

int nCardsList[] = {33,50, 6, 26, 8,34, 3, 9,12,11,
					10,27,25,7,15,30,1,18,37,2,
					13,21,31,32, 16,17, 24,19,
					39,14,0,22,46,5,4,38, 47,49,45,
					20,44,48,36,23,28,43,29,41,35,40,
					51,42,52};
				

int					nFrame = 0;
int 				bIsPacked = FALSE;
static int			nPackCont = 0;

KMSURFACEDESC		Tex[256];	
KMSTRIPHEAD			VC_Table, VC_Reflect, VC_Shadow, VC_DarkShadow;			
KMSTRIPHEAD			VC_Card[256];		

int ScreenWidth=640, ScreenHeight=480;

km_vector CameraTo   = { 0.0f, 0.0f, 5000.0f};
km_vector CameraFrom = { 0.0f, -700.0f, -800.0f};
km_vector LightDir   = { 1.0f, -1.0f, 1.0f};

/* Info windows control */
DWORD dwCurrentWin= 0, dwDisplayWins = TRUE, InfoWin, TWin[10];

/**************************************************/
/* Prototypes                                     */
/**************************************************/

void	InitMeshes			(void);
void	InitMaterials		(void);
void	CalculateFlyingCard	(int nCard);
void	DrawCard			(int nCard, float Dist);
void 	ShowLayers 			(void);
void 	CreateWindows 		(void);

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
 *  Description     :   InitApplication() is called by KMShell to enable the
 *						user to initialise the application                                           
 *----------------------------------------------------------------------*/
void InitApplication (void)
{


	KMShellSetVideo	(TRUE,  /* FALSE = Hardware Trans Sorting  TRUE = User Trans PreSort  */
					 0x00   /* Logo background translucency */
					 );


	KMShellSetBuffers( 0, 		/* % Opaque  (flushed)  */
					   0,		/* % ModVol Opaque */
					  100,		/* % Translucent   */
					   0,		/* % ModVol Trans  */
					   0		/* % Punchthrough  */
					   );		

	KMPrint3DSetTextures();

	InitMaterials ();

	InitMeshes();
	
	CreateWindows ();
}
/*----------------------------------------------------------------------*
 *  Function Name   :  QuitApplication                                 
 *  Inputs          :  None                                               
 *  Outputs         :  None                                                 
 *  Returns         :                                            
 *  Globals Used    :                                                 
 *  Description     :  QuitApplication() is called by KMShell to enable the
 *						user to finish the application                                                    
 *----------------------------------------------------------------------*/
void QuitApplication (void)
{
register i;

	KMPrint3DReleaseTextures ();

	/* FREE TEXTURES */
	for (i=0; i<NUM_TEXTURES; i++)
	{
		kmFreeTexture(&Tex[i]);
	}
}
/*----------------------------------------------------------------------*
 *  Function Name   :  RenderScene                                      
 *  Inputs          :  None                                               
 *  Outputs         :  None                                                 
 *  Returns         :  FALSE to finish                                               
 *  Globals Used    :  nFrame, CameraTo, CameraFrom, nPT                                                
 *  Description     :  Draws everything in the scene.                                                 
 *----------------------------------------------------------------------*/
int RenderScene (void)
{
float Area;
int i;
MATRIX Matrix;
float fFPS;
 
	KMShellBackground (&VC_Table);
	
	if(dwCurrentWin==2)
	{
		ShowLayers();
	}
	else
	{
		for (i=0; i<TOTAL_CARDS;i++)
		{
			if (nCardsList[i]<CurrentCard)  DrawCard(nCardsList[i], 0.0f); 
			if (nCardsList[i]==CurrentCard) DrawCard(nCardsList[i], PosZ);
		}
   
	    CalculateFlyingCard(CurrentCard);
	    
	    KMPrint3DDisplayWindow(InfoWin);
    }
	
    fFPS = KMTimerGetFPS();
    
   	/* 
	 * Text windows.
	 */
	 if(dwDisplayWins)
	 {
		KMPrint3DDisplayWindow(TWin[dwCurrentWin]);
	 }
   	

	Area = 3.0f*CARD_REAL_AREA*CurrentCard + (640.0f*480.0f*2.0f);
		
	KMPrint3DWindowOutput (InfoWin, " %s Fill Rate = %.2f Mpps\n", (dwCurrentWin==0)?"Approximate":"Exact",
								fFPS * (Area+640*480)/1000000);

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
 *  Description     : PadControl() is called by KMShell every frame to enable the
 *						user to read the joystick status.                         
 *-------------------------------------------------------------------------------------*/
int PadControl (void)
{	
register i;
static unsigned nDelay = 0, nTempCurrent;

    nDelay++;

	/* START */
	if (IsSTARTKey())
	{
		bStart = TRUE;
	}
	
	/* UP/DOWN X-PAD */
	if (IsUPKey() || IsDOWNKey())
	{
		if(nDelay>2)
		{
			dwDisplayWins = !dwDisplayWins;
		}
		nDelay = 0;
	}

	

	/* LEFT X-PAD */
	if (IsLEFTKey())
	{
		if(nDelay>2)
		{
			dwDisplayWins = TRUE;
			dwCurrentWin--;
			if (dwCurrentWin==-1) dwCurrentWin = 2;
			
			if (dwCurrentWin==1)
			{
				nTempCurrent = CurrentCard;
				bIsPacked = TRUE;
				for (i=0; i<=CurrentCard;i++)	CalculateFlyingCard (i);
				CurrentCard = nTempCurrent;
			}
			else
			{
				bIsPacked = FALSE;
			}
		}
		nDelay =0;
								
	}

	/* RIGHT X-PAD */
	if (IsRIGHTKey())
	{
		if(nDelay>2)
		{
			dwDisplayWins = TRUE;
			dwCurrentWin++;
			if (dwCurrentWin==3) dwCurrentWin = 0;
			
			if (dwCurrentWin==1)
			{
				nTempCurrent = CurrentCard;
				bIsPacked = TRUE;
				for (i=0; i<=CurrentCard;i++)	CalculateFlyingCard (i);
				CurrentCard = nTempCurrent;
			}
			else
			{
				bIsPacked = FALSE;
			}
		}
		nDelay =0;
	}


	/* A button */
	if (IsAKey())
	{
		if (nDelay>10)
		{
			nTempCurrent = CurrentCard;
			bIsPacked = !bIsPacked;
			if(bIsPacked)	for (i=0; i<=CurrentCard;i++)	CalculateFlyingCard (i);
			CurrentCard = nTempCurrent;
		}
		nDelay = 0;
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
/**************************************************************************************/
/*                                                                                    */
/*                            Aplication functions                                    */
/*                                                                                    */
/**************************************************************************************/
/*-------------------------------------------------------------------------------------* 
 *  Function Name   : InitMeshes                                                         
 *  Inputs          : None                                                               
 *  Outputs         : None                                                               
 *  Returns         : None                                                               
 *  Globals Used    :                          
 *  Description     : Sets initials values for meshes managing                            
 *-------------------------------------------------------------------------------------*/
void InitMeshes (void)
{
float fCardVert[]   = {-165.0f,-250.0f, 0.0f, 165.0f,-250.0f, 0.0f, 
                       -165.0f, 250.0f, 0.0f, 165.0f, 250.0f, 0.0f};

float fCardUVOdd[]  = {0.0f,0.0f,   0.5f,0.0f,  0.0f,1.0f,   0.5f,1.0f};

float fCardUVEven[] = {0.5f,0.0f,   1.0f,0.0f,  0.5f,1.0f,   1.0f,1.0f};

register i,j;
int nIndex[TOTAL_CARDS], nCard;

	 for (i=0; i<TOTAL_CARDS; i++) 
	{
       
		for (j=0; j<4; j++)
		{
            nCard = nCardsList[i];

			Card[i].fVertex[j*3+0] = fCardVert[j*3+0];
			Card[i].fVertex[j*3+1] = fCardVert[j*3+1];
			Card[i].fVertex[j*3+2] = fCardVert[j*3+2];
						
			Card[i].fU[j] = (nCard&1) ? fCardUVEven[j*2+0]: fCardUVOdd[j*2+0];
			Card[i].fV[j] = (nCard&1) ? fCardUVEven[j*2+1]: fCardUVOdd[j*2+1];
			
			Card[i].KmVert[j].uBaseRGB.dwPacked = 0xFFFFFFFF;
			Card[i].KmVert[j].uOffsetRGB.dwPacked = 0xFF000000;

			Card[i].KmVert[j].fU = Card[i].fU[j];
			Card[i].KmVert[j].fV = Card[i].fV[j];

			Card[i].Texture = nCard/2;
			Card[i].Displ = (float)(KMMiscRand()%500-250)/10.0f;
	
		}
		
	}
	
}
/*-------------------------------------------------------------------------------------* 
 *  Function Name   : InitMaterials                                                         
 *  Inputs          : None                                                               
 *  Outputs         : None                                                               
 *  Returns         : None                                                               
 *  Globals Used    :                                   
 *  Description     : Loads textures and sets vertex contexts  
 *  Note			: Textures are converted from a 24bits bitmap format to a 16bits 
 *                    hardware format on the fly.
 *-------------------------------------------------------------------------------------*/
#define LOAD_CARD(x) KMTextureConvertAndLoad(&Tex[x], Texture[x].pBitmapData, NULL,Texture[x].nWidth, \
										Texture[x].nHeight, KM_TEXTURE_TWIDDLED | KM_TEXTURE_RGB565);\
					 KMShellInitStripHead (&VC_Card[x], &Tex[x], VC_OPAQUE)

void InitMaterials (void)
{
	/* TABLE Texture n28 */
	KMTextureConvertAndLoad(&Tex[28], Texture[28].pBitmapData, NULL, 
						Texture[28].nWidth, Texture[28].nHeight, KM_TEXTURE_TWIDDLED | KM_TEXTURE_RGB565);
	KMShellInitStripHead (&VC_Table, &Tex[28], VC_OPAQUE);

	/* REFLECTION Texture n27 */
	KMTextureConvertAndLoad(&Tex[27], Texture[27].pBitmapData, NULL, 
						Texture[27].nWidth, Texture[27].nHeight, KM_TEXTURE_TWIDDLED | KM_TEXTURE_RGB565);
	KMShellInitStripHead (&VC_Reflect, &Tex[27], VC_TRANS);

	/* LIGHTMAP Texture n26 */
	/* The blend mode is special for ligth maps: KM_DESTCOLOR - KM_ZERO */
	KMTextureConvertAndLoad(&Tex[26], Texture[26].pBitmapData, NULL,Texture[26].nWidth, Texture[26].nHeight, KM_TEXTURE_TWIDDLED | KM_TEXTURE_RGB565);
	KMShellInitStripHead (&VC_Shadow, &Tex[26], VC_TRANS);
	kmChangeStripBlendingMode	( &VC_Shadow, KM_IMAGE_PARAM1, KM_DESTCOLOR, KM_ZERO );


	/* SHADOW ON THE TABLE no texture */
	KMShellInitStripHead (&VC_DarkShadow,  NULL, VC_OPAQUE | VC_NONTEXTURED);

	/* CARDS Textures n0-25 */
	LOAD_CARD(0);
	LOAD_CARD(1);	LOAD_CARD(2);	LOAD_CARD(3);	LOAD_CARD(4);	LOAD_CARD(5);
	LOAD_CARD(6);	LOAD_CARD(7);	LOAD_CARD(8);	LOAD_CARD(9);	LOAD_CARD(10);
	LOAD_CARD(11);	LOAD_CARD(12);	LOAD_CARD(13);	LOAD_CARD(14);	LOAD_CARD(15);
	LOAD_CARD(16);	LOAD_CARD(17);	LOAD_CARD(18);	LOAD_CARD(19);	LOAD_CARD(20);
	LOAD_CARD(21);	LOAD_CARD(22);	LOAD_CARD(23);	LOAD_CARD(24);	LOAD_CARD(25);
	

}
/*-------------------------------------------------------------------------------------* 
 *  Function Name   :   CalculateFlyingCard                                              
 *  Inputs          :   nCard                                                     
 *  Outputs         :   None                                                           
 *  Returns         :   None                                                            
 *  Globals Used    :                             
 *  Description     :   New position and UVs.                         
 *-------------------------------------------------------------------------------------*/
void CalculateFlyingCard (int nCard)
{
register i;
MATRIX Matrix;
CARD_TYPE BufferCard;
static float	PosX = 0.0f, PosY = -1600.0f, AngZ;
static float	AngIncr = -0.3f, PosXIncr = -5.0f, PosYIncr = 20.0f;

	AngZ += AngIncr;
	PosX += PosXIncr;
	PosY += PosYIncr;
	PosZ--;

	/* New position */
	if (bIsPacked)
	{
		KMMatrixReset(&Matrix);
		KMMatrixTranslate (&Matrix, ((nCard+nPackCont)&1)*340-170, -600.0, 0.0f);
	}
	else
	{
		KMMatrixReset(&Matrix);
		KMMatrixRotate (&Matrix, 0.0f, 0.0f, AngZ);
		KMMatrixTranslate (&Matrix, PosX, PosY, 0.0f);
	}


	KMTransTransformProjectPerspective(&Matrix, 4, Card[nCard].fVertex, Card[nCard].KmVert,
											640, 480,CameraFrom, CameraTo, 0.0f,
											1.0f, 10000.0f, PI/4);
	
	/* Caculating new UVs for environment-map and shadow-map */
	for (i=0; i<4; i++)
	{
	Card[nCard].fTU[i] = (Card[nCard].KmVert[i].fX+Card[nCard].Displ)/(640.0f-nCard);
	Card[nCard].fTV[i] = 1.0f-(Card[nCard].KmVert[i].fY+Card[nCard].Displ)/(480.0f-nCard);

	Card[nCard].fShU[i] = (Card[nCard].KmVert[i].fX)/640.0f;
	Card[nCard].fShV[i] = 1.0f-(Card[nCard].KmVert[i].fY)/480.0f;
	}

	/* If the fly of the card has finished start a new one... */
	if (PosZ==0.0f)
	{
		PosX = 0.0f;
		PosY = -1600.0f;
		PosZ = 50.0f;
		AngIncr = -0.22;
		PosXIncr = (float)(KMMiscRand()%140-70)/10.0f;
		PosYIncr = 20.0f - (float)(KMMiscRand()%100-50)/10.0f;
	
		if (nCard<NUM_CARDS)
		{
			CurrentCard++;
		}
		else 
		{
			nPackCont++;

			memcpy(&BufferCard,		&Card[0],		sizeof(CARD_TYPE));
			memcpy(&Card[0],		&Card[1],		sizeof(CARD_TYPE)*(nCard));
			memcpy(&Card[nCard],	&BufferCard,	sizeof(CARD_TYPE));

			KMMatrixReset		(&Matrix);
			KMMatrixRotate		(&Matrix, 0.0f, 0.0f, AngZ);
			KMMatrixTranslate	(&Matrix, PosX, PosY, 0.0f);

			KMTransTransformProjectPerspective(&Matrix, 4, Card[nCard].fVertex, Card[nCard].KmVert,
											640, 480,CameraFrom, CameraTo, 0.0f,
											1.0f, 10000.0f, PI/4);
		}
	}

}
/*-------------------------------------------------------------------------------------* 
 *  Function Name   :   DrawCard                                              
 *  Inputs          :   nCard Dist                                                       
 *  Outputs         :   None                                                          
 *  Returns         :   None                                                            
 *  Globals Used    :                             
 *  Description     :   Draw three layers (one opaque and two trans) for every card.                       
 *-------------------------------------------------------------------------------------*/
void DrawCard (int nCard, float Dist)
{
register i;
MATRIX Matrix;
unsigned short pLength[] = {2};
unsigned short pFaces[] = {0,1,2,3};

	for(i=0;i<4;i++) 
	{
		Card[nCard].KmVert[i].u.fZ = 1.0f/(float)(60-nCard);

		Card[nCard].KmVert[i].fU = Card[nCard].fU[i];
		Card[nCard].KmVert[i].fV = Card[nCard].fV[i];
		Card[nCard].KmVert[i].uBaseRGB.dwPacked = 0xFFFFFFFF;
	}
	KMShellStrips (&VC_Card[Card[nCard].Texture], 1, pLength, pFaces, Card[nCard].KmVert);
	

	for(i=0;i<4;i++)
	{
		Card[nCard].KmVert[i].u.fZ += 0.0001;

		Card[nCard].KmVert[i].fU = Card[nCard].fShU[i];
		Card[nCard].KmVert[i].fV = Card[nCard].fShV[i];
		Card[nCard].KmVert[i].uBaseRGB.dwPacked = 0xFFFFFFFF;
	}
 
	KMShellStrips (&VC_Shadow, 1, pLength, pFaces, Card[nCard].KmVert);

	for(i=0;i<4;i++)
	{
            Card[nCard].KmVert[i].u.fZ += 0.0001;

			Card[nCard].KmVert[i].fU = Card[nCard].fTU[i];
			Card[nCard].KmVert[i].fV = Card[nCard].fTV[i];
			Card[nCard].KmVert[i].uBaseRGB.dwPacked = 0x40FFFFFF;
	}

	KMShellStrips (&VC_Reflect, 1, pLength, pFaces, Card[nCard].KmVert);
	
	if (Dist > 0.0f && !bIsPacked)
	{
		for(i=0;i<4;i++) 
		{
			Card[nCard].KmVert[i].u.fZ = 1.0f/(float)(60-nCard) - 0.0001;
			Card[nCard].KmVert[i].fX -= Dist*3.0f; 
			Card[nCard].KmVert[i].fY += Dist*3.0f; 
			Card[nCard].KmVert[i].fU  = Card[nCard].fU[i];
			Card[nCard].KmVert[i].fV  = Card[nCard].fV[i];
			Card[nCard].KmVert[i].uBaseRGB.dwPacked = 0xFF000000;
		}

		KMShellStrips (&VC_DarkShadow, 1, pLength, pFaces, Card[nCard].KmVert);

		for(i=0;i<4;i++) 
		{
			Card[nCard].KmVert[i].fX += Dist*3.0f; 
			Card[nCard].KmVert[i].fY -= Dist*3.0f; 
		}
	}
 
}
/*-------------------------------------------------------------------------------------* 
 *  Function Name   :   ShowLayers                                              
 *  Inputs          :   None                                                     
 *  Outputs         :   None                                                           
 *  Returns         :   None                                                            
 *  Globals Used    :                             
 *  Description     :   Shows the three layers of a card apart.                          
 *-------------------------------------------------------------------------------------*/
 void ShowLayers (void)
{
register i;
MATRIX Matrix;
unsigned short pLength[] = {2};
unsigned short pFaces[] = {0,1,2,3};
float fPos;


	fPos = (float)fabs(50 * (float) sin((float)nFrame/50.0f));

	KMMatrixReset	(&Matrix);
	KMMatrixRotate	(&Matrix, 0.0f, 0.0f, (float)nFrame/400.0f);
	KMMatrixTranslate	(&Matrix, 0, -600, 0.0f);


	KMTransTransformProjectPerspective(&Matrix, 4, Card[50].fVertex, Card[50].KmVert,
											640, 480,CameraFrom, CameraTo, 0.0f,
											1.0f, 10000.0f, PI/4);
	
	for(i=0;i<4;i++) 
	{
		Card[50].KmVert[i].u.fZ = 1.0f/(float)(60-50);

		Card[50].KmVert[i].fU = Card[50].fU[i];
		Card[50].KmVert[i].fV = Card[50].fV[i];
		Card[50].KmVert[i].uBaseRGB.dwPacked = 0xFFFFFFF;

	}
	KMShellStrips (&VC_Card[Card[50].Texture], 1, pLength, pFaces, Card[50].KmVert);
	
	
	for (i=0; i<4; i++)
	{
		Card[50].fTU[i] = (Card[50].KmVert[i].fX+Card[50].Displ)/(640.0f-50);
		Card[50].fTV[i] = 1.0f-(Card[50].KmVert[i].fY+Card[50].Displ)/(480.0f-50);

		Card[50].fShU[i] = (Card[50].KmVert[i].fX)/640.0f;
		Card[50].fShV[i] = 1.0f-(Card[50].KmVert[i].fY)/480.0f;
	}
	
	for(i=0;i<4;i++)
	{
		Card[50].KmVert[i].fX += fPos;
		Card[50].KmVert[i].u.fZ += 0.0001;
	
		Card[50].KmVert[i].fU = Card[50].fShU[i];
		Card[50].KmVert[i].fV = Card[50].fShV[i];
		Card[50].KmVert[i].uBaseRGB.dwPacked = 0xFFFFFFFF;
	}
 
	KMShellStrips (&VC_Shadow, 1, pLength, pFaces, Card[50].KmVert);

	for(i=0;i<4;i++)
	{
			Card[50].KmVert[i].fX -= fPos*2;
            Card[50].KmVert[i].u.fZ += 0.0001;

			Card[50].KmVert[i].fU = Card[50].fTU[i];
			Card[50].KmVert[i].fV = Card[50].fTV[i];
			Card[50].KmVert[i].uBaseRGB.dwPacked = 0x40FFFFFF;
	}

	KMShellStrips (&VC_Reflect, 1, pLength, pFaces, Card[50].KmVert);
	
 
}
/*-------------------------------------------------------------------------------------* 
 *  Function Name   :   CreateWindows                                              
 *  Inputs          :   None                                                       
 *  Outputs         :   None                                                          
 *  Returns         :   None                                                            
 *  Globals Used    :                             
 *  Description     :   Info windows.                        
 *-------------------------------------------------------------------------------------*/
void CreateWindows (void)
{
	/* Info Window */
	InfoWin = KMPrint3DCreateWindow (50, 1);
	
	KMPrint3DSetWindow		(InfoWin, 0xFFA00000, 0xFFFFFFFF, 0.5f, 1.0f, 90.0f, 50.0f, 10.0f);
	KMPrint3DSetWindowFlags	(InfoWin, PRINT3D_ADJUST_SIZE_ALWAYS | PRINT3D_DEACTIVATE_TITLE );

	/* Text Windows */
	/* Window 0 */
	TWin[0] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 45, "FORTUNE   Fill Rate Test ", NULL);
	KMPrint3DSetWindowFlags (TWin[0], PRINT3D_ADJUST_SIZE_ALWAYS| PRINT3D_DEACTIVATE_WIN);
	
	
	/* Window 1 */
	TWin[1] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 45, "FORTUNE   Fill Rate Test (1 of 2)","\
The overall fillrate is calculated by summing up the surface area of all polygons in the scene, multiplied by the framerate.\n\n\
In this case the cards are not clipped so the fill rate is not an approximation.\n\n");
	KMPrint3DSetWindowFlags (TWin[1], PRINT3D_ADJUST_SIZE_ALWAYS );

	/* Window 2 */
	TWin[2] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 45, "FORTUNE   Fill Rate Test (2 of 2)", "\
Every card covers an area of about half the screen (150K pixels), consists of three layers: one opaque and two translucent.\n\n");
	KMPrint3DSetWindowFlags (TWin[2], PRINT3D_ADJUST_SIZE_ALWAYS);

}