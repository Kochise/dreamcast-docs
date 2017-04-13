/**************************************************************************
  dumb3d.cpp - A simple linear algebra library for 3D.

 **************************************************************************/
/**************************************************************************

    (C) Copyright 1995-1996 Microsoft Corp.  All rights reserved.

    You have a royalty-free right to use, modify, reproduce and 
    distribute the Sample Files (and/or any modified version) in 
    any way you find useful, provided that you agree that 
    Microsoft has no warranty obligations or liability for any 
    Sample Application Files which are modified. 

 **************************************************************************/

#include<memory.h>
#include<math.h>
#include"dumb3d.h"

/*--------------------------------------------------------------------------

matrix multiplication.

*/

matrix_4x4 operator*( matrix_4x4 const &Multiplicand,
    matrix_4x4 const &Multiplier )
{
  matrix_4x4 ReturnMatrix;

  for(int i = 0;i < 4;i++)
  {
    for(int j = 0;j < 4;j++)
    {
      real Value = 0;
      
      for(int k = 0;k < 4;k++)
      {
        Value += Multiplicand.GetElement(i,k) *
            Multiplier.GetElement(k,j);
      }

      ReturnMatrix.SetElement(i,j,Value);
    }
  }

  return ReturnMatrix;
}

vector_4 operator*( matrix_4x4 const &Multiplicand,
    vector_4 const &Multiplier )
{
  vector_4 ReturnPoint;

  for(int i = 0;i < 4;i++)
  {
    real Value = 0;
    
    for(int k = 0;k < 4;k++)
    {
      Value += Multiplicand.GetElement(i,k) *
          Multiplier.GetElement(k);
    }

    ReturnPoint.SetElement(i,Value);
  }

  return ReturnPoint;
}

point_4 operator*( matrix_4x4 const &Multiplicand,
    point_4 const &Multiplier )
{
  point_4 ReturnPoint;

  for(int i = 0;i < 4;i++)
  {
    real Value = 0;
    
    for(int k = 0;k < 4;k++)
    {
      Value += Multiplicand.GetElement(i,k) *
          Multiplier.GetElement(k);
    }

    ReturnPoint.SetElement(i,Value);
  }

  return ReturnPoint;
}


/*--------------------------------------------------------------------------

constructor.

*/

matrix_4x4::matrix_4x4( void )
{
  for(int Counter = 0;Counter < 16;Counter++)
  {
    aElements[0][Counter] = 0;
  }

  aElements[0][0] = aElements[1][1] = aElements[2][2] = aElements[3][3] = 1;
}


/*--------------------------------------------------------------------------

Rotations.

*/

matrix_4x4 &matrix_4x4::ConcatenateXRotation( real Degrees )
{
  real Temp01, Temp11, Temp21, Temp31;
  real Temp02, Temp12, Temp22, Temp32;

  real Radians = (Degrees/360) * M_PI * 2;

  real Sin = sin(Radians), Cos = cos(Radians);

  Temp01 = aElements[0][1] * Cos + aElements[0][2] * Sin;
  Temp11 = aElements[1][1] * Cos + aElements[1][2] * Sin;
  Temp21 = aElements[2][1] * Cos + aElements[2][2] * Sin;
  Temp31 = aElements[3][1] * Cos + aElements[3][2] * Sin;

  Temp02 = aElements[0][1] * -Sin + aElements[0][2] * Cos;
  Temp12 = aElements[1][1] * -Sin + aElements[1][2] * Cos;
  Temp22 = aElements[2][1] * -Sin + aElements[2][2] * Cos;
  Temp32 = aElements[3][1] * -Sin + aElements[3][2] * Cos;

  aElements[0][1] = Temp01;
  aElements[1][1] = Temp11;
  aElements[2][1] = Temp21;
  aElements[3][1] = Temp31;
  aElements[0][2] = Temp02;
  aElements[1][2] = Temp12;
  aElements[2][2] = Temp22;
  aElements[3][2] = Temp32;

  return *this;
}

matrix_4x4 &matrix_4x4::ConcatenateYRotation( real Degrees )
{
  real Temp00, Temp10, Temp20, Temp30;
  real Temp02, Temp12, Temp22, Temp32;

  real Radians = (Degrees/360) * M_PI * 2;

  real Sin = sin(Radians), Cos = cos(Radians);

  Temp00 = aElements[0][0] * Cos + aElements[0][2] * -Sin;
  Temp10 = aElements[1][0] * Cos + aElements[1][2] * -Sin;
  Temp20 = aElements[2][0] * Cos + aElements[2][2] * -Sin;
  Temp30 = aElements[3][0] * Cos + aElements[3][2] * -Sin;

  Temp02 = aElements[0][0] * Sin + aElements[0][2] * Cos;
  Temp12 = aElements[1][0] * Sin + aElements[1][2] * Cos;
  Temp22 = aElements[2][0] * Sin + aElements[2][2] * Cos;
  Temp32 = aElements[3][0] * Sin + aElements[3][2] * Cos;

  aElements[0][0] = Temp00;
  aElements[1][0] = Temp10;
  aElements[2][0] = Temp20;
  aElements[3][0] = Temp30;
  aElements[0][2] = Temp02;
  aElements[1][2] = Temp12;
  aElements[2][2] = Temp22;
  aElements[3][2] = Temp32;

  return *this;
}

matrix_4x4 &matrix_4x4::ConcatenateZRotation( real Degrees )
{
  real Temp00, Temp10, Temp20, Temp30;
  real Temp01, Temp11, Temp21, Temp31;

  real Radians = (Degrees/360) * M_PI * 2;

  real Sin = sin(Radians), Cos = cos(Radians);

  Temp00 = aElements[0][0] * Cos + aElements[0][1] * Sin;
  Temp10 = aElements[1][0] * Cos + aElements[1][1] * Sin;
  Temp20 = aElements[2][0] * Cos + aElements[2][1] * Sin;
  Temp30 = aElements[3][0] * Cos + aElements[3][1] * Sin;

  Temp01 = aElements[0][0] * -Sin + aElements[0][1] * Cos;
  Temp11 = aElements[1][0] * -Sin + aElements[1][1] * Cos;
  Temp21 = aElements[2][0] * -Sin + aElements[2][1] * Cos;
  Temp31 = aElements[3][0] * -Sin + aElements[3][1] * Cos;

  aElements[0][0] = Temp00;
  aElements[1][0] = Temp10;
  aElements[2][0] = Temp20;
  aElements[3][0] = Temp30;
  aElements[0][1] = Temp01;
  aElements[1][1] = Temp11;
  aElements[2][1] = Temp21;
  aElements[3][1] = Temp31;

  return *this;
}

/*--------------------------------------------------------------------------

Translations.

*/

matrix_4x4 &matrix_4x4::ConcatenateXTranslation( real Distance )
{
  aElements[0][3] = aElements[0][0] * Distance + aElements[0][3];
  aElements[1][3] = aElements[1][0] * Distance + aElements[1][3];
  aElements[2][3] = aElements[2][0] * Distance + aElements[2][3];
  aElements[3][3] = aElements[3][0] * Distance + aElements[3][3];

  return *this;
}

matrix_4x4 &matrix_4x4::ConcatenateYTranslation( real Distance )
{
  aElements[0][3] = aElements[0][1] * Distance + aElements[0][3];
  aElements[1][3] = aElements[1][1] * Distance + aElements[1][3];
  aElements[2][3] = aElements[2][1] * Distance + aElements[2][3];
  aElements[3][3] = aElements[3][1] * Distance + aElements[3][3];

  return *this;
}

matrix_4x4 &matrix_4x4::ConcatenateZTranslation( real Distance )
{
  aElements[0][3] = aElements[0][2] * Distance + aElements[0][3];
  aElements[1][3] = aElements[1][2] * Distance + aElements[1][3];
  aElements[2][3] = aElements[2][2] * Distance + aElements[2][3];
  aElements[3][3] = aElements[3][2] * Distance + aElements[3][3];

  return *this;
}

/*--------------------------------------------------------------------------

vector normalize.

*/

vector_4 &vector_4::Normalize( void )
{
  real Length = sqrt(GetX()*GetX() + GetY()*GetY() + GetZ()*GetZ());

  SetX(GetX() / Length);
  SetY(GetY() / Length);
  SetZ(GetZ() / Length);

  return *this;
}
  
/*--------------------------------------------------------------------------

view transform ctor.

*/

view_transform::view_transform( point_4 const &Viewpoint,
  vector_4 const &ViewDirection, vector_4 const &Up )
{
  // translate the viewpoint to the origin

  this->ConcatenateXTranslation(-Viewpoint.GetX());
  this->ConcatenateYTranslation(-Viewpoint.GetY());
  this->ConcatenateZTranslation(-Viewpoint.GetZ());

  // get view vectors set up

  vector_4 Right = -CrossProduct(ViewDirection,Up);
  vector_4 ReallyUp = CrossProduct(Right,ViewDirection);
    
  matrix_4x4 LookDownZ;

  for(int Counter = 0;Counter < 3;Counter++)
  {
    LookDownZ.SetElement(0,Counter,Right.GetElement(Counter));
  }

  for(Counter = 0;Counter < 3;Counter++)
  {
    LookDownZ.SetElement(1,Counter,ReallyUp.GetElement(Counter));
  }

  for(Counter = 0;Counter < 3;Counter++)
  {
    LookDownZ.SetElement(2,Counter,ViewDirection.GetElement(Counter));
  }

  this->matrix_4x4::operator=(LookDownZ * *this);
}
