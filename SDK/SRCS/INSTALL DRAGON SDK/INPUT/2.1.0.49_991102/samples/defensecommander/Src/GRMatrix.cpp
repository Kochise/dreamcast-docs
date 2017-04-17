/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    GRMatrix.cpp

Abstract:

    Matrix related code.

-------------------------------------------------------------------*/

#include "DC.h"
#include "DCGraphics.h"

// Sets the projection matrix up for a perspective projection.
void GraphicsClass::SetPerspectiveProjection(float FOV, float ZNear, float ZFar)
{
	DCMatrix16 m;

	// Calculate matrix.
	FLOAT h = (float)( cos(FOV/2)/sin(FOV/2) );
	FLOAT w = h * (3.0f/4.0f);
    FLOAT Q = ZFar / ( ZFar - ZNear );

    DCZeroMemory( &m, sizeof(DCMatrix16) );
    m.m11 = w;
    m.m22 = h;
    m.m33 = Q;
    m.m34 = 1.0f;
    m.m43 = -Q*ZNear;

    // Set matrix.
	D3DDevice->SetTransform( D3DTRANSFORMSTATE_PROJECTION, (D3DMATRIX *)&m );
}

// Sets the projection matrix to the matrix specified. 
// If the matrix is not specified (NULL) then the current matrix is used.
void GraphicsClass::SetProjectionMatrix(DCMatrix16 *m)
{
	// If matrix not specified, use current matrix.
	if (!m)
		m=&Matrix;

	// Set it.
	D3DDevice->SetTransform( D3DTRANSFORMSTATE_PROJECTION, (D3DMATRIX *)m );
}

// Sets the view matrix to the matrix specified. 
// If the matrix is not specified (NULL) then the current matrix is used.
void GraphicsClass::SetViewMatrix(DCMatrix16 *m)
{
	// If matrix not specified, use current matrix.
	if (!m)
		m=&Matrix;

	// Set it.
	D3DDevice->SetTransform( D3DTRANSFORMSTATE_VIEW, (D3DMATRIX *)m );
}

// Sets the world matrix to the matrix specified. 
// If the matrix is not specified (NULL) then the current matrix is used.
void GraphicsClass::SetWorldMatrix(DCMatrix16 *m)
{
	// If matrix not specified, use current matrix.
	if (!m)
		m=&Matrix;

	// Set it.
	D3DDevice->SetTransform( D3DTRANSFORMSTATE_WORLD, (D3DMATRIX *)m );
}

// Sets the current matrix to the identity matrix.
void GraphicsClass::MatrixIdentity(void)
{
	static DCMatrix16 Identity=
	{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	DCCopyMemory(&Matrix,&Identity,sizeof(DCMatrix16));
	MatrixIsIdentity=TRUE;
}

// Set the current matrix to the matrix specified.
void GraphicsClass::MatrixSet(DCMatrix16 *m)
{
	DCCopyMemory(&Matrix,m,sizeof(DCMatrix16));
	MatrixIsIdentity=FALSE;
}

// Return the current matrix in "m".
void GraphicsClass::MatrixGet(DCMatrix16 *m)
{
	DCCopyMemory(m,&Matrix,sizeof(DCMatrix16));
}

// Multiply the current matrix by the one specified.
void GraphicsClass::MatrixMultiply(DCMatrix16 *m)
{
	if (MatrixIsIdentity)
	{
		DCCopyMemory(&Matrix,m,sizeof(DCMatrix16));
		MatrixIsIdentity=FALSE;
	}
	else
	{
		float m1,m2,m3,m4;

		// Calculate one row at a time. 
		// Operation is done partially in-place by copying out the destination row.
		m1=Matrix.m11; m2=Matrix.m12; m3=Matrix.m13; m4=Matrix.m14;
		Matrix.m11=m1*m->m11 + m2*m->m21 + m3*m->m31 + m4*m->m41;
		Matrix.m12=m1*m->m12 + m2*m->m22 + m3*m->m32 + m4*m->m42;
		Matrix.m13=m1*m->m13 + m2*m->m23 + m3*m->m33 + m4*m->m43;
		Matrix.m14=m1*m->m14 + m2*m->m24 + m3*m->m34 + m4*m->m44;

		m1=Matrix.m21; m2=Matrix.m22; m3=Matrix.m23; m4=Matrix.m24;
		Matrix.m21=m1*m->m11 + m2*m->m21 + m3*m->m31 + m4*m->m41;
		Matrix.m22=m1*m->m12 + m2*m->m22 + m3*m->m32 + m4*m->m42;
		Matrix.m23=m1*m->m13 + m2*m->m23 + m3*m->m33 + m4*m->m43;
		Matrix.m24=m1*m->m14 + m2*m->m24 + m3*m->m34 + m4*m->m44;

		m1=Matrix.m31; m2=Matrix.m32; m3=Matrix.m33; m4=Matrix.m34;
		Matrix.m31=m1*m->m11 + m2*m->m21 + m3*m->m31 + m4*m->m41;
		Matrix.m32=m1*m->m12 + m2*m->m22 + m3*m->m32 + m4*m->m42;
		Matrix.m33=m1*m->m13 + m2*m->m23 + m3*m->m33 + m4*m->m43;
		Matrix.m34=m1*m->m14 + m2*m->m24 + m3*m->m34 + m4*m->m44;

		m1=Matrix.m41; m2=Matrix.m42; m3=Matrix.m43; m4=Matrix.m44;
		Matrix.m41=m1*m->m11 + m2*m->m21 + m3*m->m31 + m4*m->m41;
		Matrix.m42=m1*m->m12 + m2*m->m22 + m3*m->m32 + m4*m->m42;
		Matrix.m43=m1*m->m13 + m2*m->m23 + m3*m->m33 + m4*m->m43;
		Matrix.m44=m1*m->m14 + m2*m->m24 + m3*m->m34 + m4*m->m44;
	}
}

// Rotate around the X axis.
void GraphicsClass::MatrixRotateX(float Angle)
{
	float SinAngle,CosAngle;

	// Calculate sin and cos of angle.
	SinAngle=(float)sin(Angle);
	CosAngle=(float)cos(Angle);

	if (MatrixIsIdentity)
	{
		Matrix.m22=CosAngle;
		Matrix.m23=-SinAngle;
		Matrix.m32=SinAngle;
		Matrix.m33=CosAngle;

		MatrixIsIdentity=FALSE;
	}
	else
	{
		float m2,m3;

		// This code optimizes out redundant parts 
		// of the matrix multiply with the current matrix.
		m2=Matrix.m12; m3=Matrix.m13;
		Matrix.m12 = m2*CosAngle + m3*SinAngle;
		Matrix.m13 = m3*CosAngle - m2*SinAngle;

		m2=Matrix.m22; m3=Matrix.m23;
		Matrix.m22 = m2*CosAngle + m3*SinAngle;
		Matrix.m23 = m3*CosAngle - m2*SinAngle;

		m2=Matrix.m32; m3=Matrix.m33;
		Matrix.m32 = m2*CosAngle + m3*SinAngle;
		Matrix.m33 = m3*CosAngle - m2*SinAngle;

		m2=Matrix.m42; m3=Matrix.m43;
		Matrix.m42 = m2*CosAngle + m3*SinAngle;
		Matrix.m43 = m3*CosAngle - m2*SinAngle;
	}
}

// Rotate around the Y axis.
void GraphicsClass::MatrixRotateY(float Angle)
{
	float SinAngle,CosAngle;

	// Calculate sin and cos of angle.
	SinAngle=(float)sin(Angle);
	CosAngle=(float)cos(Angle);

	if (MatrixIsIdentity)
	{
		Matrix.m11=CosAngle;
		Matrix.m13=SinAngle;
		Matrix.m31=-SinAngle;
		Matrix.m33=CosAngle;

		MatrixIsIdentity=FALSE;
	}
	else
	{
		float m1,m3;

		// This code optimizes out redundant parts 
		// of the matrix multiply with the current matrix.
		m1=Matrix.m11; m3=Matrix.m13;
		Matrix.m11 = m1*CosAngle - m3*SinAngle;
		Matrix.m13 = m1*SinAngle + m3*CosAngle;

		m1=Matrix.m21; m3=Matrix.m23;
		Matrix.m21 = m1*CosAngle - m3*SinAngle;
		Matrix.m23 = m1*SinAngle + m3*CosAngle;

		m1=Matrix.m31; m3=Matrix.m33;
		Matrix.m31 = m1*CosAngle - m3*SinAngle;
		Matrix.m33 = m1*SinAngle + m3*CosAngle;

		m1=Matrix.m41; m3=Matrix.m43;
		Matrix.m41 = m1*CosAngle - m3*SinAngle;
		Matrix.m43 = m1*SinAngle + m3*CosAngle;
	}
}

// Rotate around the Z axis.
void GraphicsClass::MatrixRotateZ(float Angle)
{
	float SinAngle,CosAngle;

	// Calculate sin and cos of angle.
	SinAngle=(float)sin(Angle);
	CosAngle=(float)cos(Angle);

	if (MatrixIsIdentity)
	{
		Matrix.m11=CosAngle;
		Matrix.m12=-SinAngle;
		Matrix.m21=SinAngle;
		Matrix.m22=CosAngle;

		MatrixIsIdentity=FALSE;
	}
	else
	{
		float m1,m2;

		// This code optimizes out redundant parts 
		// of the matrix multiply with the current matrix.
		m1=Matrix.m11; m2=Matrix.m12;
		Matrix.m11 = m1*CosAngle + m2*SinAngle;
		Matrix.m12 = m2*CosAngle - m1*SinAngle;

		m1=Matrix.m21; m2=Matrix.m22;
		Matrix.m21 = m1*CosAngle + m2*SinAngle;
		Matrix.m22 = m2*CosAngle - m1*SinAngle;

		m1=Matrix.m31; m2=Matrix.m32;
		Matrix.m31 = m1*CosAngle + m2*SinAngle;
		Matrix.m32 = m2*CosAngle - m1*SinAngle;

		m1=Matrix.m41; m2=Matrix.m42;
		Matrix.m41 = m1*CosAngle + m2*SinAngle;
		Matrix.m42 = m2*CosAngle - m1*SinAngle;
	}
}

// Translate.
void GraphicsClass::MatrixTranslate(float X, float Y, float Z)
{
	if (MatrixIsIdentity)
	{
		Matrix.m41=X;
		Matrix.m42=Y;
		Matrix.m43=Z;

		MatrixIsIdentity=FALSE;
	}
	else
	{
		// This code optimizes out redundant parts 
		// of the matrix multiply with the current matrix.
		Matrix.m11 += Matrix.m14*X;
		Matrix.m12 += Matrix.m14*Y;
		Matrix.m13 += Matrix.m14*Z;

		Matrix.m21 += Matrix.m24*X;
		Matrix.m22 += Matrix.m24*Y;
		Matrix.m23 += Matrix.m24*Z;
		
		Matrix.m31 += Matrix.m34*X;
		Matrix.m32 += Matrix.m34*Y;
		Matrix.m33 += Matrix.m34*Z;
		
		Matrix.m41 += Matrix.m44*X;
		Matrix.m42 += Matrix.m44*Y;
		Matrix.m43 += Matrix.m44*Z;
	}
}

// Scale.
void GraphicsClass::MatrixScale(float X, float Y, float Z)
{
	if (MatrixIsIdentity)
	{
		Matrix.m11=X;
		Matrix.m22=Y;
		Matrix.m33=Z;

		MatrixIsIdentity=FALSE;
	}
	else
	{
		// This code optimizes out redundant parts 
		// of the matrix multiply with the current matrix.
		Matrix.m11*=X; Matrix.m12*=Y; Matrix.m13*=Z;
		Matrix.m21*=X; Matrix.m22*=Y; Matrix.m23*=Z;
		Matrix.m31*=X; Matrix.m32*=Y; Matrix.m33*=Z;
		Matrix.m31*=X; Matrix.m42*=Y; Matrix.m43*=Z;
	}
}

// Routines to retrieve matricies.
void GraphicsClass::GetProjectionMatrix(DCMatrix16 *m)
{
	D3DDevice->GetTransform( D3DTRANSFORMSTATE_PROJECTION, (D3DMATRIX *)m );
}

void GraphicsClass::GetWorldMatrix(DCMatrix16 *m)
{
	D3DDevice->GetTransform( D3DTRANSFORMSTATE_WORLD, (D3DMATRIX *)m );
}

void GraphicsClass::GetViewMatrix(DCMatrix16 *m)
{
	D3DDevice->GetTransform( D3DTRANSFORMSTATE_VIEW, (D3DMATRIX *)m );
}

