/*----------------------------------------------------------------------*/
/*   Name   : Tools.c   (Some tools for Arc1a)                          */
/*   Author : Carlos Sarria (Matrix code is Jim's)                      */
/*   Date   : October 1997                                              */
/*                                                                      */
/*   Copyright : 1997 by VideoLogic Limited. All rights reserved.       */
/*			February 17. 1999 by Takeshi Muto for Shinobi				*/
/*----------------------------------------------------------------------*/

#include	<math.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<float.h>
#include	<Shinobi.h>
#include	<sg_sytmr.h>	/* System timer */

#pragma warning (disable : 4244) /* Disables float to double conversion warning */
#pragma warning (disable : 4056)
#define _STRICT_UNION_
#define _CLX2_
#define _CLX_

#include "kmtrtool.h"

float			LightDir[3] = { -1.0f, 0.0f, 0.0f };
unsigned		TotalPolys = 0;
unsigned char	VFog = 0;

PVRVERTEX		*PVRVert[256];
CASTMESHES		CMesh[256];
TRANSFORM		T[256];

/***********************************************************************/
/* Kamui Val.s *********************************************************/
/***********************************************************************/
#if defined(_DISP_PERFORMANCE_)
extern	int					frame;					/* 画面フレーム							*/
extern	int					frame_2;				/* 画面フレーム上位						*/
extern	Uint32		StartTime;
extern	Uint32		EndTime;
extern	double				nFPS;					/* 現在の性能(Frame/Second)				*/
extern	double				aFPS;					/* 性能の平均値							*/
extern	double				MxFPS;					/* 最高性能								*/
extern	double				MnFPS;					/* 最低性能								*/
extern	double				nowTime;				/* 現在の描画時間(msec)					*/
extern	double				maxTime;				/* 最高描画時間(msec)					*/
extern	double				minTime;				/* 最低描画時間(msec)					*/
extern	double				totalTime;				/* 累積render時間(msec)					*/
extern	double				aveTime;				/* 平均描画時間(msec)					*/
#endif

extern	KMSTATUS			status;					/* return status of KAMUI API */
extern	KMVERTEXBUFFDESC	VertexBufferDesc;		/* Vertex-buffer */
extern	KMSYSTEMCONFIGSTRUCT	SystemConfig;		/* System Configuration flag */

/*--------------------------------------------------------------------*/
/*  Function Name   : ResetMatrix                                     */
/*  Inputs          : Object                                          */
/*  Outputs         :                                                 */
/*  Returns         :                                                 */
/*  Globals Used    :                                                 */
/*  Description     : Builds an identity matrix and stores it in T    */
/*--------------------------------------------------------------------*/
void ResetMatrix (int Object)
{
	static TRANSFORM Id =
	{
		{
			{1.0f, 0.0f, 0.0f, 0.0f},
		  	{0.0f, 1.0f, 0.0f, 0.0f},
		  	{0.0f, 0.0f, 1.0f, 0.0f}
		},
		{
			{1.0f, 0.0f, 0.0f, 0.0f},
		  	{0.0f, 1.0f, 0.0f, 0.0f},
		  	{0.0f, 0.0f, 1.0f, 0.0f}
		}
	};

	memcpy (&T[Object], &Id, sizeof (TRANSFORM));
}
/*----------------------------------------------------------------------*/
/*  Function Name   :  Rotate                                           */
/*  Inputs          :  Object, Axis, Theta                              */
/*  Outputs         :                                                   */
/*  Returns         :                                                   */
/*  Globals Used    :                                                   */
/*  Description     :  Rotate T an angle Theta around Axis              */
/*----------------------------------------------------------------------*/
void Rotate (int Object, pvr_vector Axis, float Theta)
{
	float	halfTheta;
 	float	sinHalfTheta;
 	float	cosHalfTheta;
	float	MRot[3][4], MTemp[3][4];
	float	W,X,Y,Z;
	float	Tm1,Tm2,Tm3,Tm4,Tm5,TmNorm;
	int		Row, Col;

	/* convert to quaternian */

	halfTheta = Theta * 0.5f;

	/*	Using double sin and cos  */

	cosHalfTheta = (float) cos(halfTheta);
	sinHalfTheta = (float) sin(halfTheta);

	W = cosHalfTheta;
	X = sinHalfTheta * Axis[0];
	Y = sinHalfTheta * Axis[1];
	Z = sinHalfTheta * Axis[2];

	/* convert quaternian into Matrix form */

	Tm1 = X * X;
	Tm2 = Y * Y;
	Tm3 = Z * Z;
	Tm4 = Tm2 + Tm3;

	TmNorm= W*W + Tm1 + Tm4;  /* Normalising term */

	if (TmNorm!=0.0f)
	{
		Tm5 = 2.0f / TmNorm;
	}
	else
	{
		Tm5 = 0.0f;
	}

	MRot[0][0] = 1.0f - Tm5*Tm4;
	MRot[1][1] = 1.0f - Tm5*(Tm1+Tm3);
	MRot[2][2] = 1.0f - Tm5*(Tm1+Tm2);

	Tm1 = Tm5*X;
	Tm2 = Tm5*Y;
	Tm4 = Tm5*Z*W;
	Tm5 = Tm1*Y;

	MRot[0][1] = Tm5 - Tm4;
	MRot[1][0] = Tm5 + Tm4;

	Tm4 = Tm2*W;
	Tm5 = Tm1*Z;

	MRot[0][2] = Tm5 + Tm4;
	MRot[2][0] = Tm5 - Tm4;


	Tm4 = Tm1*W;
	Tm5 = Tm2*Z;

	MRot[1][2] = Tm5 - Tm4;
	MRot[2][1] = Tm5 + Tm4;

	memcpy (MTemp, &T[Object].Matrix, sizeof (T[Object].Matrix));

	for(Row = 0; Row < 3; Row ++)
	{
		for(Col = 0; Col < 3; Col ++)
		{
			/*
				unroll the innermost loop to do sr bit
			*/

			T[Object].Matrix[Row][Col] = MTemp[Row][0] * MRot[0][Col] +
								  MTemp[Row][1] * MRot[1][Col] +
								  MTemp[Row][2] * MRot[2][Col];
		}
	}

	memcpy (MTemp, &T[Object].Inverse, sizeof (T[Object].Matrix));

	for(Row = 0; Row < 3; Row ++)
	{
		for(Col = 0; Col < 3; Col ++)
		{
			/*
				unroll the innermost loop to do sr bit
				inverse of a rotation is its transpose!
			*/

			T[Object].Inverse[Row][Col] = MRot[0][Row] * MTemp[0][Col] +
								   MRot[1][Row] * MTemp[1][Col] +
								   MRot[2][Row] * MTemp[2][Col];
		}
	}
}
/*----------------------------------------------------------------------*/
/*  Function Name   :  Scale                                            */
/*  Inputs          :  Object, S                                        */
/*  Outputs         :                                                   */
/*  Returns         :                                                   */
/*  Globals Used    :                                                   */
/*  Description     :  Escale T using S values (x, y, z)                */
/*----------------------------------------------------------------------*/
void Scale (int Object, float SX, float SY, float SZ)
{
	int i;

	float invX = 1.0f / SX;
	float invY = 1.0f / SY;
	float invZ = 1.0f / SZ;

	for(i = 0; i < 3; i ++)
	{
	 	T[Object].Matrix[i][0] *= SX;
	 	T[Object].Matrix[i][1] *= SY;
	 	T[Object].Matrix[i][2] *= SZ;

	 	T[Object].Inverse[0][i] *= invX;
	 	T[Object].Inverse[1][i] *= invY;
	 	T[Object].Inverse[2][i] *= invZ;
	}

 	T[Object].Inverse[0][3] *= invX;
 	T[Object].Inverse[1][3] *= invY;
 	T[Object].Inverse[2][3] *= invZ;
}
/*----------------------------------------------------------------------*/
/*  Function Name   : Translate                                         */
/*  Inputs          : Object, Tr                                        */
/*  Outputs         :                                                   */
/*  Returns         :                                                   */
/*  Globals Used    :                                                   */
/*  Description     : Translate T using Tr(x,y,z) displacement.         */
/*----------------------------------------------------------------------*/
void Translate (int Object, float TrX, float TrY, float TrZ)
{
	T[Object].Matrix[0][3] += T[Object].Matrix[0][0] * TrX + T[Object].Matrix[0][1] * TrY + T[Object].Matrix[0][2] * TrZ;	
	T[Object].Matrix[1][3] += T[Object].Matrix[1][0] * TrX + T[Object].Matrix[1][1] * TrY + T[Object].Matrix[1][2] * TrZ;	
	T[Object].Matrix[2][3] += T[Object].Matrix[2][0] * TrX + T[Object].Matrix[2][1] * TrY + T[Object].Matrix[2][2] * TrZ;	

	T[Object].Inverse[0][3] -= TrX;	
	T[Object].Inverse[1][3] -= TrY;	
	T[Object].Inverse[2][3] -= TrZ;	
}
/*----------------------------------------------------------------------*/
/*  Function Name   : InitScene                                         */
/*  Inputs          :                                                   */
/*  Outputs         :                                                   */
/*  Returns         :                                                   */
/*  Globals Used    :                                                   */
/*  Description     : Draw a object in PVR                              */
/*----------------------------------------------------------------------*/
void InitScene (void)
{
	/* シ－ンの開始	*/
	kmBeginScene(&SystemConfig);

	/* パスの開始 */
	kmBeginPass(&VertexBufferDesc);
}

/*----------------------------------------------------------------------*/
/*  Function Name   : EndScene                                          */
/*  Inputs          :                                                   */
/*  Outputs         :                                                   */
/*  Returns         :                                                   */
/*  Globals Used    :                                                   */
/*  Description     : Draw a object in PVR                              */
/*----------------------------------------------------------------------*/
void EndScene (void)
{
	txt_SetCursor(0,1);
#if defined(_DISP_PERFORMANCE_)
	/* Write FPS on screen -----------------------------------------------------*/
	PRINTOUT(("FRAME:%06d%06d Now:%07.3fFPS, Ave:%07.3fFPS\n",frame_2, frame,nFPS,aFPS));
#else
	PRINTOUT(("FRAME:%06d%06d\n",frame_2, frame));
#endif	/* defined(_DISP_PERFORMANCE_) */

	/*-----------------------------------------------------------------------------------*/
	/* Rendering start */
#if defined(_DISPLAY_STRING_)
	txt_DispScreen(&VertexBufferDesc);		/* Display screen */
#endif

	/* パスの終了 */
	kmEndPass(&VertexBufferDesc);
	status = kmRender(KM_RENDER_FLIP);

	/* レンダリング */
/*	status = kmRender(KM_RENDER_FLIP);
	Check_Status(status, "kmRender");*/

	/* シ－ンの終了 */
	kmEndScene(&SystemConfig);

/*	status = kmRender();
	Check_Status(status, "kmRender");*/

	/*----------------------------------------------------------------------------------- */
	/* Flip screen */
/*	status = kmFlipFrameBuffer();
	Check_Status(status, "kmFlipFrameBuffer");*/

#if defined(_DISP_PERFORMANCE_)
/* 性能計算 ------------------------------------------------------------------*/
	EndTime	= syTmrGetCount();
	/* ただいまのフレームを作成するのにかかった時間 */
	nowTime = syTmrCountToMicro( syTmrDiffCount( StartTime, EndTime ) ) / 1000.0f;
	StartTime = EndTime;

	if((nowTime > 1000.0f)||(nowTime < 1.0f)){nowTime = 20.0f;}
												/* 得られた値が異常であった場合は無視 */
	if(nowTime > maxTime) maxTime = nowTime;	/* もっとも時間がかかった？ */
	if(nowTime < minTime) minTime = nowTime;	/* もっとも早かった？ */

	totalTime += nowTime;								/* 累積時間 */
	aveTime = totalTime / ((double)frame + 1.0f);		/* 今までの平均時間 */

	nFPS  = 1000.0f / (double)nowTime;
	aFPS  = 1000.0f / (double)aveTime;
	MxFPS = 1000.0f / (double)minTime;
	MnFPS = 1000.0f / (double)maxTime;
#endif	/* defined(_DISP_PERFORMANCE_) */

	frame++;
	if(frame > 1000000) {	/* フレームのリセット */
		frame = 0;
#if defined(_DISP_PERFORMANCE_)
		totalTime = 0;
#endif	/* defined(_DISP_PERFORMANCE_) */
		frame_2++;
	}
}

/*----------------------------------------------------------------------*/
/*  Function Name   : InitMeshes                                        */
/*  Inputs          :                                                   */
/*  Outputs         :                                                   */
/*  Returns         :                                                   */
/*  Globals Used    :                                                   */
/*  Description     : Draw a object in PVR                              */
/*----------------------------------------------------------------------*/
void InitMeshes (int nMeshes, CASTMESHES *pMeshes)
{
register i;
/* SET4 / SET5 */
int mptr = 0x0c400000;

	/*(CASTMESHES *) CMesh = pMeshes; */

	/* Memory allocation for PVRVert, UV values and SmoothShading*/
    for (i=0; i<nMeshes; i++) 
	{
		memcpy ( &CMesh[i], &pMeshes[i], sizeof (CASTMESHES) );
#if 0
		PVRVert[i] = (PVRVERTEX *)mptr; mptr += CMesh[i].NumVertex*sizeof(PVRVERTEX);
#else
		PVRVert[i] = (PVRVERTEX *)(((KMDWORD)syMalloc(CMesh[i].NumVertex*sizeof(PVRVERTEX)) & 0x0FFFFFFFUL) | 0xA0000000);
#endif
		ResetMatrix (i); 
		SetUV (i);
		SetSmoothShading (i, (i==0)?C_NONE:C_PLAIN);
		TotalPolys += CMesh[i].NumFaces;
	}
}
/*----------------------------------------------------------------------*/
/*  Function Name   : FreeMeshes                                        */
/*  Inputs          :                                                   */
/*  Outputs         :                                                   */
/*  Returns         :                                                   */
/*  Globals Used    :                                                   */
/*  Description     : Draw a object in PVR                              */
/*----------------------------------------------------------------------*/
void FreeMeshes (int nMeshes)
{
register i;

	for (i=0; i<nMeshes; i++) free(PVRVert[i]);

}

/*----------------------------------------------------------------------*/
/*  Function Name   : SetVertices                                       */
/*  Inputs          : nFaces, Faces, nVertex, pVertex                   */
/*  Outputs         :                                                   */
/*  Returns         :                                                   */
/*  Globals Used    :                                                   */
/*  Description     : Draw a object in PVR                              */
/*----------------------------------------------------------------------*/
/*void SetVertices (int Object, int Texture, int Effect) */
void SetVertices (int Object, KMSTRIPHEAD StripHead[], INFO CInfo, int Effect)
{
register		i, nVertex = 0;
float			fX, fY, fZ, pV[3], f1OverZ;
float			CamFocus = 600.0f;
/*float			mod; */
extern float	CosA, SinA, TrX, TrY, TrZ, MovX, MovZ;
extern int		Type;
int				NumVert, NumFac;

	NumVert = CMesh[Object].NumVertex;
	NumFac  = CMesh[Object].NumFaces;

	/*if (Object==0 && Type==1) {NumVert-=50*3;NumFac=CMesh[Object].NumFaces-150*3;} */
	/*if (Object==0 && Type==2) {NumVert-=50*9;NumFac=CMesh[Object].NumFaces-150*9;} */

	for (i = 0; i < NumVert; i++) {

		pV[0] = *(CMesh[Object].Vertex+nVertex++) + TrX;
		fY    = *(CMesh[Object].Vertex+nVertex++) + TrY;
		pV[2] = *(CMesh[Object].Vertex+nVertex++) + TrZ;

		fX =  CosA * pV[0] + SinA * pV[2] + MovX;
		fZ = -SinA * pV[0] + CosA * pV[2] + MovZ;
		fZ += 500;

		if (fZ < 1.0f) {
			if( Object == 1 ) return;
			else {
				fZ = 0.00001f;
				fY =-100.0f;
			}
		}

		f1OverZ = 1.0f / fZ;

		(PVRVert[Object]+i)->fX		=  f1OverZ * fX * 600 + 320;
		(PVRVert[Object]+i)->fY		= -f1OverZ * fY * 600 + 240;
		(PVRVert[Object]+i)->fInvW	=  f1OverZ;

		if (Effect == FX_OPTIC) {
			(PVRVert[Object]+i)->fUOverW = 0.5f + (fX + pV[2])/200.0f;
			(PVRVert[Object]+i)->fVOverW = 0.5f + (fY + pV[2])/200.0f;
		}

		if (Effect == FX_PLANAR) {
			(PVRVert[Object]+i)->fUOverW = 0.5f + fX/640.0f;
			(PVRVert[Object]+i)->fVOverW = 0.5f + fY/480.0f;
		}

	}

	VFog = (unsigned char) ((fZ*150.0f)/2000.0f) - 30;

	if(CInfo.Textured == TRUE) {
		kmtri_triangles (	VertexBufferDesc,				/* KMVERTEXBUFFDESC	BufferDesc, */
							&StripHead[1],					/* PKMSTRIPHEAD		pStripHead, */
							NumFac,							/* int  nNumFaces, */
							(int(*)[3])CMesh[Object].Faces,	/* int  pFaces[][3], */
							PVRVert[Object],				/* PPVRVERTEX  pVertices */
							TRUE							/* int	bTexture */
							);
	}
	else {
		kmtri_triangles (	VertexBufferDesc,				/* KMVERTEXBUFFDESC	BufferDesc, */
							&StripHead[0],					/* PKMSTRIPHEAD		pStripHead, */
							NumFac,							/* int  nNumFaces, */
							(int(*)[3])CMesh[Object].Faces,	/* int  pFaces[][3], */
							PVRVert[Object],				/* PPVRVERTEX  pVertices */
							FALSE							/* int	bTexture */
							);
	}

}

/*----------------------------------------------------------------------*/
/*  Function Name   : SetUV                                             */
/*  Inputs          : nFaces, Faces, pUV                                */
/*  Outputs         :                                                   */
/*  Returns         :                                                   */
/*  Globals Used    :                                                   */
/*  Description     :                                                   */
/*----------------------------------------------------------------------*/
void SetUV (int Object)
{
register i;

    for (i=0; i<CMesh[Object].NumVertex; i++)
	{
		(PVRVert[Object]+i)->fUOverW = *(CMesh[Object].UV++);
		(PVRVert[Object]+i)->fVOverW = *(CMesh[Object].UV++);
	}

}
/*----------------------------------------------------------------------*/
/*  Function Name   : SetSmoothShading                                  */
/*  Inputs          : nFaces, Faces, nVertex, pNormals                  */
/*  Outputs         :                                                   */
/*  Returns         :                                                   */
/*  Globals Used    :                                                   */
/*  Description     :                                                   */
/*----------------------------------------------------------------------*/
void SetSmoothShading (int Object, int Color)
{
register				i, nNormal = 0;
unsigned char			Col;
/*unsigned char			Spec; */
static unsigned char	SpecVal[256] = { 0 };
float					LightLocal[3], f1OverLength, fN[3];

    	LightLocal[0] = LightDir[0]*T[Object].Inverse[0][0] + LightDir[1]*T[Object].Inverse[0][1] + LightDir[2]*T[Object].Inverse[0][2];
		LightLocal[1] = LightDir[0]*T[Object].Inverse[1][0] + LightDir[1]*T[Object].Inverse[1][1] + LightDir[2]*T[Object].Inverse[1][2];
		LightLocal[2] = LightDir[0]*T[Object].Inverse[2][0] + LightDir[1]*T[Object].Inverse[2][1] + LightDir[2]*T[Object].Inverse[2][2];

		f1OverLength =  1.0f / (float) sqrt (LightLocal[0]*LightLocal[0] + 
											 LightLocal[1]*LightLocal[1] + 
											 LightLocal[2]*LightLocal[2]);

		LightLocal[0] *= f1OverLength;
		LightLocal[1] *= f1OverLength;
		LightLocal[2] *= f1OverLength;

		for (i=0; i<CMesh[Object].NumVertex; i++)
		{
		fN[0] = *(CMesh[Object].Normals+nNormal++);
		fN[1] = *(CMesh[Object].Normals+nNormal++);
		fN[2] = *(CMesh[Object].Normals+nNormal++);

		Col = (unsigned char) (127.0f * (fN[0]*LightLocal[0] + fN[1]*LightLocal[1] + fN[2]*LightLocal[2]+ 1.0f) );
     
		switch (Color)
		{
		case C_WHITE :  (PVRVert[Object]+i)->u32Colour = RGBAColour(Col,Col,Col, 150); break;
        case C_BLACK :  (PVRVert[Object]+i)->u32Colour = RGBAColour(Col>>3,Col>>3,Col>>3, 128); break;
	    case C_GREY  :  (PVRVert[Object]+i)->u32Colour = RGBAColour(Col>>1,Col>>1,Col>>1, 128); break;
		case C_RED   :  (PVRVert[Object]+i)->u32Colour = RGBAColour(Col, 0, 0, 128); break;
		case C_GREEN :  (PVRVert[Object]+i)->u32Colour = RGBAColour(0, Col, 0, 128); break;
		case C_BLUE  :  (PVRVert[Object]+i)->u32Colour = RGBAColour(0, 0, Col, 128); break;
		case C_YELLOW:  (PVRVert[Object]+i)->u32Colour = RGBAColour(Col, Col, 0, 128); break;
		case C_BROWN :  (PVRVert[Object]+i)->u32Colour = RGBAColour(Col,Col>>1,Col>>2, 128); break;
		case C_PLAIN :  (PVRVert[Object]+i)->u32Specular  = RGBAColour(0,0,0, 0);
		                (PVRVert[Object]+i)->u32Colour = RGBAColour(255,255,255, 150);
						break;
      }
		}
		

}
/*----------------------------------------------------------------------*/
/*  Function Name   : SetBackground                                     */
/*  Inputs          :                                                   */
/*  Outputs         :                                                   */
/*  Returns         :                                                   */
/*  Globals Used    :                                                   */
/*  Description     :                                                   */
/*----------------------------------------------------------------------*/
void SetBackground (int TextureID)
{
 PVRVERTEX Plane[3];
 int Tri[3] = { 2, 1, 0 };
 

     Plane[0].fX		= 0.0f;
	 Plane[0].fY		= 0.0f;
	 Plane[0].fInvW		= 0.000001f;
	 Plane[0].u32Colour = RGBAColour (255, 255, 255, 255);
	 Plane[0].fUOverW   = 0.0f + BILINEAR_CORRECTION;
     Plane[0].fVOverW   = 1.0f - BILINEAR_CORRECTION; 
            

	 Plane[1].fX		= 640.0f;
	 Plane[1].fY		= 0.0f;
	 Plane[1].fInvW		= 0.000001f;
	 Plane[1].u32Colour = RGBAColour (255, 255, 255, 255);
	 Plane[1].fUOverW   = 1.0f - BILINEAR_CORRECTION;
     Plane[1].fVOverW   = 1.0f - BILINEAR_CORRECTION; 

	 Plane[2].fX		= 640.0f;
	 Plane[2].fY		= 480.0f;
	 Plane[2].fInvW		= 0.000001f;
	 Plane[2].u32Colour = RGBAColour (255, 255, 255, 255);
	 Plane[2].fUOverW   = 1.0f - BILINEAR_CORRECTION;
     Plane[2].fVOverW   = 0.0f + BILINEAR_CORRECTION; 

	InitBackGround();

}
/*----------------------------------------------------------------------*/
/*  Function Name   : Timer                                             */
/*  Inputs          :                                                   */
/*  Outputs         :                                                   */
/*  Returns         :                                                   */
/*  Globals Used    :                                                   */
/*  Description     :                                                   */
/*----------------------------------------------------------------------*/
void Timer (int Action)
{
#if 0
char Text[500];
static double TotalTime= 0.0f, CurrentTime = 0.0f, AverageTime = 0.0f;
static unsigned TimeFrame = 0;
static LARGE_INTEGER LapTime1, LapTime2, Freq;
extern int nTrees, Type;
int NT[] = { 3, 6, 12};
	
    if (Action == RESET_TIME || TimeFrame == 0)
	{
		TotalTime = 0.0f;
		TimeFrame = 1;
        QueryPerformanceCounter(&LapTime1);
		return;
	}

	QueryPerformanceFrequency(&Freq);
	QueryPerformanceCounter(&LapTime2);
  
	if (LapTime2.LowPart < LapTime1.LowPart){
       QueryPerformanceCounter(&LapTime1);
	   return;
	   }		
	 
	CurrentTime = (double)LapTime2.LowPart - (double)LapTime1.LowPart;

	QueryPerformanceCounter(&LapTime1);

	CurrentTime  = (CurrentTime)/((double)Freq.LowPart);

	TotalTime += CurrentTime;

	AverageTime = (TotalTime*1000.0f)/TimeFrame;

	if (Action == DISPLAY_TIME)
	{
	sprintf (Text,"Transformed Polys per sec : %d",TotalPolys+nTrees*NT[Type]); 
	Print3D  (2, 5, 0.6f, Text);
    
	sprintf (Text,"Software FPS : %d",(int)(1.0f/CurrentTime)); 
	Print3D  (2, 25, 0.6f	,Text);
	Print3D  (2, 45, 0.6f	,"Hardware FPS on consol screen (F9)");
	}

	else if (Action==HARD_TIME)
	{
	printf ("\r Hardware  FPS: %.2f     ",(1.0f/CurrentTime)); 
	}

   TimeFrame++;
#endif
}
/*----------------------------------------------------------------------*/
/*  Function Name   : EnviroMap                                         */
/*  Inputs          : nFaces, Faces, pUV                                */
/*  Outputs         :                                                   */
/*  Returns         :                                                   */
/*  Globals Used    :                                                   */
/*  Description     :                                                   */
/*----------------------------------------------------------------------*/
void EnviroMap (int nVertex, float *pVertex, PVRVERTEX *PvrVertex)
{
register i;

    for (i=0; i<nVertex; i++)
	{
		(PvrVertex+i)->fUOverW = (PvrVertex+i)->fUOverW;/*(((float) atan2 (Vertices[k][2] - Centre[2], fX) + PI) * ONEOVERTWOPI) * fU; */
		(PvrVertex+i)->fVOverW = (PvrVertex+i)->fUOverW;/*(((float) atan2 (Vertices[k][1] - Centre[1], fX) + PI) * ONEOVERTWOPI) * fV; */
	}

}

/***************************************
 *	VertexType01用KMSTRIPHEADの構築
 ***************************************/
void	InitStripContext01(
								PKMSTRIPCONTEXT pStripContext,
								PKMSTRIPHEAD	pStripHead
)
{
	pStripContext->nSize = sizeof(KMSTRIPCONTEXT);
	pStripContext->StripControl.nListType		 					= KM_OPAQUE_POLYGON;
	pStripContext->StripControl.nUserClipMode	 					= KM_USERCLIP_DISABLE;
	pStripContext->StripControl.nShadowMode		 					= KM_NORMAL_POLYGON;
	pStripContext->StripControl.bGouraud		 					= KM_TRUE;
	pStripContext->ObjectControl.nDepthCompare			 			= KM_GREATER;
	pStripContext->ObjectControl.nCullingMode			 			= KM_NOCULLING;
	pStripContext->ObjectControl.bZWriteDisable			 			= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nSRCBlendingMode	= KM_ONE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nDSTBlendingMode	= KM_ZERO;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bSRCSelect			= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bDSTSelect			= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nFogMode			= KM_NOFOG;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bColorClamp		= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bUseAlpha			= KM_FALSE;

	kmGenerateStripHead01( pStripHead,pStripContext );
}

/***************************************
 *	VertexType03用KMSTRIPHEADの構築
 ***************************************/
void	InitStripContext03(
							PKMSTRIPCONTEXT pStripContext,	/* Strip context */
							PKMSTRIPHEAD    pStripHead,		/* Strip header */
							PKMSURFACEDESC	pTexture		/* Texture surface */
		)
{
	pStripContext->nSize = sizeof(KMSTRIPCONTEXT);
	pStripContext->StripControl.nListType							= KM_OPAQUE_POLYGON;
	pStripContext->StripControl.nUserClipMode						= KM_USERCLIP_DISABLE;
	pStripContext->StripControl.nShadowMode							= KM_NORMAL_POLYGON;
	pStripContext->StripControl.bOffset								= KM_FALSE;
	pStripContext->StripControl.bGouraud							= KM_TRUE;
	pStripContext->ObjectControl.nDepthCompare						= KM_GREATER;
	pStripContext->ObjectControl.nCullingMode						= KM_NOCULLING;
	pStripContext->ObjectControl.bZWriteDisable						= KM_FALSE;
	pStripContext->ObjectControl.bDCalcControl						= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nSRCBlendingMode	= KM_ONE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nDSTBlendingMode	= KM_ZERO;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bSRCSelect			= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bDSTSelect			= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nFogMode			= KM_NOFOG;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bColorClamp		= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bUseAlpha			= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bIgnoreTextureAlpha= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nFlipUV			= KM_NOFLIP;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nClampUV			= KM_NOCLAMP;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nFilterMode		= KM_BILINEAR;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bSuperSampleMode	= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].dwMipmapAdjust		= KM_MIPMAP_D_ADJUST_1_00;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nTextureShadingMode= KM_MODULATE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].pTextureSurfaceDesc= pTexture;

	kmGenerateStripHead03( pStripHead,pStripContext);
}

/*----------------------------------------------------------------------*/
/*  Function Name   : InitContext                                       */
/*  Inputs          : CInfo                                             */
/*  Outputs         :                                                   */
/*  Returns         :                                                   */
/*  Globals Used    :                                                   */
/*  Description     :                                                   */
/*----------------------------------------------------------------------*/

void InitContext (
					KMSTRIPCONTEXT	StripContext[],
					KMSTRIPHEAD		StripHead[],
					INFO CInfo,
					int Trans,
					PKMSURFACEDESC pTexture)
{
KMLISTTYPE	ListType;										/* List type */

	/*-------------------------------------------------------------------------------- */
	/* Initialize Vertex Context */
	/*-------------------------------------------------------------------------------- */
	/* Clear Strip context */
	memset( &StripContext[0], 0, sizeof(KMSTRIPCONTEXT));	/* for TYPE01 */
	memset( &StripContext[1], 0, sizeof(KMSTRIPCONTEXT));	/* for TYPE03 */
	/*Clear Strip head */
	memset( &StripHead[0], 0, sizeof(KMSTRIPHEAD));			/* for TYPE01 */
	memset( &StripHead[1], 0, sizeof(KMSTRIPHEAD));			/* for TYPE03 */

	/* VertexType01用KMSTRIPHEADの構築 */
	InitStripContext01( &StripContext[0],					/* Strip context */
						&StripHead[0]);						/* Strip head */

	/* VertexType03用KMSTRIPHEADの構築 */
	InitStripContext03( &StripContext[1],					/* Strip context */
						&StripHead[1],						/* Strip head */
						pTexture);							/* Texture surface */

	if (CInfo.Bilinear)
	{
		kmChangeStripFilterMode(&StripHead[1],KM_IMAGE_PARAM1,KM_BILINEAR);
	}
	else
	{
		kmChangeStripFilterMode(&StripHead[1],KM_IMAGE_PARAM1,KM_POINT_SAMPLE);
	}

	if(CInfo.Gouraud)
	{
		/* Set shading mode */
		kmChangeStripGouraud(&StripHead[0],KM_TRUE);
		kmChangeStripGouraud(&StripHead[1],KM_TRUE);
	}
	else
	{
		/* Set shading mode */
		kmChangeStripGouraud(&StripHead[0],KM_FALSE);
		kmChangeStripGouraud(&StripHead[1],KM_FALSE);
	}

	if(Trans > 0)
	/* 半透明・パンチスル－ポリゴン設定 */
	{
		/* Blending mode */
		kmChangeStripBlendingMode(	&StripHead[0],
									KM_IMAGE_PARAM1,
									KM_SRCALPHA,
									KM_INVSRCALPHA);
		kmChangeStripBlendingMode(	&StripHead[1],
									KM_IMAGE_PARAM1,
									KM_SRCALPHA,
									KM_INVSRCALPHA);

		/* List type */
		if(Trans == 1)	{ListType = KM_TRANS_POLYGON;}
		else			{ListType = KM_PUNCHTHROUGH_POLYGON;}
		kmChangeStripListType(&StripHead[0],ListType);
		kmChangeStripListType(&StripHead[1],ListType);

		/* Use Alpha */
		kmChangeStripUseAlpha(&StripHead[0],KM_IMAGE_PARAM1,KM_TRUE);
		kmChangeStripUseAlpha(&StripHead[1],KM_IMAGE_PARAM1,KM_TRUE);
	}
}

/*----------------------------------------------------------------------*/
/*  Function Name   : SetContext                                        */
/*  Inputs          : CInfo                                             */
/*  Outputs         :                                                   */
/*  Returns         :                                                   */
/*  Globals Used    :                                                   */
/*  Description     :                                                   */
/*----------------------------------------------------------------------*/

void SetContext (KMSTRIPHEAD StripHead[], INFO CInfo, int Trans, PKMSURFACEDESC pTexture)
{
KMLISTTYPE	ListType;									/* List type */

	if (CInfo.Bilinear)
	{
		kmChangeStripFilterMode(&StripHead[1],KM_IMAGE_PARAM1,KM_BILINEAR);
	}
	else
	{
		kmChangeStripFilterMode(&StripHead[1],KM_IMAGE_PARAM1,KM_POINT_SAMPLE);
	}

	if(CInfo.Gouraud)
	{
		/* Set shading mode */
		kmChangeStripGouraud(&StripHead[0],KM_TRUE);
		kmChangeStripGouraud(&StripHead[1],KM_TRUE);
	}
	else
	{
		/* Set shading mode */
		kmChangeStripGouraud(&StripHead[0],KM_FALSE);
		kmChangeStripGouraud(&StripHead[1],KM_FALSE);
	}

	if(Trans > 0)
	/* 半透明・パンチスル－ポリゴン設定 */
	{
		/* Blending mode */
		kmChangeStripBlendingMode(	&StripHead[0],
									KM_IMAGE_PARAM1,
									KM_SRCALPHA,
									KM_INVSRCALPHA);
		kmChangeStripBlendingMode(	&StripHead[1],
									KM_IMAGE_PARAM1,
									KM_SRCALPHA,
									KM_INVSRCALPHA);

		/* List type */
		if(Trans == 1)	{ListType = KM_TRANS_POLYGON;}
		else			{ListType = KM_PUNCHTHROUGH_POLYGON;}
		kmChangeStripListType(&StripHead[0],ListType);
		kmChangeStripListType(&StripHead[1],ListType);

		/* Use Alpha */
		kmChangeStripUseAlpha(&StripHead[0],KM_IMAGE_PARAM1,KM_TRUE);
		kmChangeStripUseAlpha(&StripHead[1],KM_IMAGE_PARAM1,KM_TRUE);
	}
	else
	/* 不透明ポリゴン設定 */
	{
		/* Blending mode */
		/* Blending mode */
		kmChangeStripBlendingMode(	&StripHead[0],
									KM_IMAGE_PARAM1,
									KM_ONE,
									KM_ZERO);
		kmChangeStripBlendingMode(	&StripHead[1],
									KM_IMAGE_PARAM1,
									KM_ONE,
									KM_ZERO);

		/* List type */
		kmChangeStripListType(&StripHead[0],KM_OPAQUE_POLYGON);
		kmChangeStripListType(&StripHead[1],KM_OPAQUE_POLYGON);

		/* Use Alpha */
		kmChangeStripUseAlpha(&StripHead[0],KM_IMAGE_PARAM1,KM_FALSE);
		kmChangeStripUseAlpha(&StripHead[1],KM_IMAGE_PARAM1,KM_FALSE);
	}
}

/*----------------------------------------------------------------------*/
/*  Function Name   : 3DPrint                                           */
/*  Inputs          : nFaces, Faces, pUV                                */
/*  Outputs         :                                                   */
/*  Returns         :                                                   */
/*  Globals Used    :                                                   */
/*  Description     :                                                   */
/*----------------------------------------------------------------------*/
void Print3D (float PosX, float PosY, float Size, char *Text)
{
#if 0
unsigned				i = 0;
pvr_intermediate_map	TempMap;
PVRVERTEX				LettVert[4];
int						Val, Tri[] = {0,1,2,3}; 
float					CurPos = 0, VPos, HPos, UVHPos, UVVPos, TSize = 160.0f;
static					TexID = 666, Depht = 1;
    
    if (Size<=0) return;

    if (TexID == 666) {
		TempMap.id[0]='I'; TempMap.id[1]='M'; TempMap.id[2]='A'; TempMap.id[3]='P';
		TempMap.x_dim = 256;
		TempMap.y_dim = 256;
		TempMap.pixels = (pvr_map_pixel *) malloc (4*256*256);

		for (i=0; i<256*256; i++)
		{
			(TempMap.pixels+i)->red   = 255;
			(TempMap.pixels+i)->green = 0;
			(TempMap.pixels+i)->blue  = 0;
			(TempMap.pixels+i)->alpha = ABCTexture[i];
		}

		TexID = pvr_create_texture (pvr_map_trans16, pvr_map_256x256, FALSE, FALSE, &TempMap, NULL);
	}

      i=0;
	  PosY -= 0.01f; PosX += 0.01f; /* To avoid integer rounding */
	  TSize *= Size;

      while (TRUE)
	  {
       Val = (int)*(Text+i++);
	   if (Val==0 || i>100) return;

	   if (Val==' ')  {CurPos += TextSize['1']*TSize; continue;}
  
	   VPos   = TSize*(30.0f/255.0f);
	   HPos   = TSize*TextSize[Val];
	   UVHPos = TextSize[Val];
	   UVVPos = (28.0f/255.0f);

	   LettVert[0].fX = (PosX+CurPos);
	   LettVert[0].fY =  PosY;
	   LettVert[0].fInvW = 10000.0f;
	   LettVert[0].u32Colour = RGBAColour (255,255,255,255);
	   LettVert[0].fUOverW = TextU[Val];
	   LettVert[0].fVOverW = 1.0f-TextV[Val];

	   LettVert[1].fX = (PosX+CurPos+HPos) ;
	   LettVert[1].fY = PosY;
	   LettVert[1].fInvW = 10000.0f;
	   LettVert[1].u32Colour = RGBAColour (255,255,255,255);
	   LettVert[1].fUOverW = TextU[Val]+UVHPos;
	   LettVert[1].fVOverW = 1.0f-TextV[Val];

	   LettVert[2].fX = (PosX+CurPos+HPos);
	   LettVert[2].fY = (PosY+VPos);
	   LettVert[2].fInvW = 10000.0f;
	   LettVert[2].u32Colour = RGBAColour (255,255,255,255);
	   LettVert[2].fUOverW = TextU[Val]+UVHPos;
	   LettVert[2].fVOverW = 1.0f-TextV[Val]-UVVPos;

	   LettVert[3].fX = (PosX+CurPos);
	   LettVert[3].fY = (PosY+VPos) ;
	   LettVert[3].fInvW = 10000.0f;
	   LettVert[3].u32Colour = RGBAColour (255,255,255,255);
	   LettVert[3].fUOverW = TextU[Val];
	   LettVert[3].fVOverW = 1.0f-TextV[Val]-UVVPos;

       CurPos += TextSize[Val]*TSize;

	   PVRContext.nTextureName =  TexID;
	   PVRContext.u32Flags     =  PVRTT_TEXTURE | PVRTT_BILINEAR ;

	  pvrtri_quads (&PVRContext, 1, (int (*)[4])Tri, LettVert);
	  }
#endif
}
/*---------------------- End Of File -----------------------------------*/
