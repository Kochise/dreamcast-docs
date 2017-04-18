/******************************************************************************* */
/* Name     : transform.c */
/* Title    : ジオメトリ演算 */
/* Author   : Video Logic */
/* Created  : 30/01/1997 by VideoLogic */
/* Modified :  */
/* */
/* Description :  */
/* */
/******************************************************************************* */

#include <math.h>
#include <stdio.h>
#include <float.h>
#include "transfor.h"

typedef float	km_2d_vec[2];

/***************************************************************************/
/**	変換行列式の初期化 *****************************************************/
/***************************************************************************/
void MatrixIdentity (TRANSFORM *T)
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
	memcpy (T, &Id, sizeof (TRANSFORM));
}

/***************************************************************************/
/**	変換行列式による回転 ***************************************************/
/***************************************************************************/
void MatrixRotate (TRANSFORM *T, km_vector Axis, float Theta)
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

	memcpy (MTemp, &T->Matrix, sizeof (T->Matrix));

	for(Row = 0; Row < 3; Row ++)
	{
		for(Col = 0; Col < 3; Col ++)
		{
			/*
				unroll the innermost loop to do sr bit
			*/

			T->Matrix[Row][Col] = MTemp[Row][0] * MRot[0][Col] +
								  MTemp[Row][1] * MRot[1][Col] +
								  MTemp[Row][2] * MRot[2][Col];
		}
	}

	memcpy (MTemp, &T->Inverse, sizeof (T->Matrix));

	for(Row = 0; Row < 3; Row ++)
	{
		for(Col = 0; Col < 3; Col ++)
		{
			/*
				unroll the innermost loop to do sr bit
				inverse of a rotation is its transpose!
			*/

			T->Inverse[Row][Col] = MRot[0][Row] * MTemp[0][Col] +
								   MRot[1][Row] * MTemp[1][Col] +
								   MRot[2][Row] * MTemp[2][Col];
		}
	}
}

/***************************************************************************/
/**	変換行列式による拡大・縮小 *********************************************/
/***************************************************************************/
void MatrixScale (TRANSFORM *T, km_vector S)
{
	int i;

	float invX = 1.0f / S[0];
	float invY = 1.0f / S[1];
	float invZ = 1.0f / S[2];

	for(i = 0; i < 3; i ++)
	{
	 	T->Matrix[i][0] *= S[0];
	 	T->Matrix[i][1] *= S[1];
	 	T->Matrix[i][2] *= S[2];

	 	T->Inverse[0][i] *= invX;
	 	T->Inverse[1][i] *= invY;
	 	T->Inverse[2][i] *= invZ;
	}

 	T->Inverse[0][3] *= invX;
 	T->Inverse[1][3] *= invY;
 	T->Inverse[2][3] *= invZ;
}

/***************************************************************************/
/**	変換行列式による移動 ***************************************************/
/***************************************************************************/
void MatrixTranslate (TRANSFORM *T, km_vector Tr)
{
	T->Matrix[0][3] += T->Matrix[0][0] * Tr[0] + T->Matrix[0][1] * Tr[1] + T->Matrix[0][2] * Tr[2];	
	T->Matrix[1][3] += T->Matrix[1][0] * Tr[0] + T->Matrix[1][1] * Tr[1] + T->Matrix[1][2] * Tr[2];	
	T->Matrix[2][3] += T->Matrix[2][0] * Tr[0] + T->Matrix[2][1] * Tr[1] + T->Matrix[2][2] * Tr[2];	

	T->Inverse[0][3] -= Tr[0];	
	T->Inverse[1][3] -= Tr[1];	
	T->Inverse[2][3] -= Tr[2];	
}
