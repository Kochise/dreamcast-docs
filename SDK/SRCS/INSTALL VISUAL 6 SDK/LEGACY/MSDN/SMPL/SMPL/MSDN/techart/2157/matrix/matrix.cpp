
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples.
*       Copyright (C) 1993 Microsoft Corporation.
*       All rights reserved.
*       This source code is only intended as a supplement to
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the
*       Microsoft samples programs.
\******************************************************************************/

//Revision history:
// Apr. 15, 1994 -- fixed HEAP_ZEROINIT bug and added backcheck bug fix -
// also added optimization code to avoid calling AddScalarToColumn 
// if pivot == 0 -- RAc


#include <stdio.h>
#include <windows.h>
#include <math.h>
#define CLASSES
#include "matrix.hpp"


BOOL WINAPI DllMain (HANDLE hDLL, DWORD dwReason, LPVOID lpReserved)
{
  switch (dwReason)
  {
    case DLL_PROCESS_ATTACH:
  hMemPool = HeapCreate(0,4096,0);

      break;

    case DLL_THREAD_ATTACH:

      break;

    case DLL_THREAD_DETACH:

      break;

    case DLL_PROCESS_DETACH:
  HeapDestroy(hMemPool);

      break;
  }

return TRUE;
}


matrix::matrix(int iR, int iC)
{
  iRows = iR;
  iColumns = iC;
  iSquareVal=max(iR,iC);
  lpMemory = HeapAlloc(hMemPool,HEAP_ZERO_MEMORY,sizeof(SHORT)*iSquareVal*iSquareVal);
  if (lpMemory) iStatus = TRUE;
  else  iStatus = FALSE;
}

matrix::~matrix()
{
};



void matrix::SetElement(int iR, int iC, SHORT iElement)
{
  *(SHORT *)(((SHORT *)lpMemory)+(iColumns*iR)+iC) = iElement;

};

SHORT matrix::GetElement(int iR, int iC)
{
   return *(SHORT *)(((SHORT *)lpMemory)+(iColumns*iR)+iC);

};

matrix matrix::MultiplyRowByInt(int iR, SHORT iMult)
{ int iCount;
  matrix mtNew(1,iColumns);
  for (iCount=0; iCount<iColumns; iCount++)
   mtNew.SetElement(0,iCount,GetElement(iR,iCount)*iMult);
  return(mtNew);    /* Copy constructor takes care of us here */
};

matrix matrix::MultiplyColByInt(int iC, SHORT iMult)
{ int iCount;
  matrix mtNew(iRows,1);
  for (iCount=0; iCount<iRows; iCount++)
   mtNew.SetElement(iCount,0,GetElement(iCount,iC)*iMult);
   return(mtNew);
};

void matrix::ReplaceRowByScalar(int iR, matrix mScalar)
{ int iCount;
  for (iCount=0;iCount<iColumns; iCount++)
    SetElement(iR,iCount,mScalar.GetElement(0,iCount));
};

void matrix::ReplaceColByScalar(int iC, matrix mScalar)
{ int iCount;
//  _asm int 3;
  for (iCount=0;iCount<iRows; iCount++)
    SetElement(iCount,iC,mScalar.GetElement(iCount,0));
};

void matrix::AddScalarToRow(int iR, matrix mtScalar, SHORT iFactor)
{ SHORT iBias=0;
  BOOL bUhoh=FALSE;
  int iCount,iBackCheck;
  for (iCount=0;iCount<iColumns;iCount++)
   { SHORT sElement = GetElement(iR,iCount)+mtScalar.GetElement(0,iCount)*iFactor;
     if (!bUhoh && abs(sElement)>1)
	   {iBias=sElement;
        for (iBackCheck=0;iBackCheck<iCount;iBackCheck++)
		 if ((GetElement(iR,iBackCheck)%iBias)!=0) iBias =1;

	    bUhoh = TRUE;
       };
	 if (bUhoh && (sElement%iBias != 0)) iBias =1;
    SetElement(iR,iCount,sElement);
   };
  if (bUhoh && iBias!=1)
  for (iCount=0;iCount<iColumns;iCount++)
    SetElement(iR,iCount,GetElement(iR,iCount)/iBias);
};

void matrix::AddScalarToColumn(int iC, matrix mtScalar, SHORT iFactor)
{ int iCount,iBackCheck;
// if we end up with any matrix element with an absolute greater than 1,
// we try to see if we can divide the rest of the matrix evenly by that
// element as well, in which case we are back to a "clean" matrix.
  SHORT iBias=0;
  BOOL bUhoh=FALSE;
  for (iCount=0;iCount<iRows;iCount++)
   { SHORT sElement= GetElement(iCount,iC)+mtScalar.GetElement(iCount,0)*iFactor;
	 if (!bUhoh && abs(sElement)>1)
	   {iBias=sElement;
// it might have been the case that the problem index was found late in
// the column, so we must check the beginning of that column up to the 
// offensive index...
        for (iBackCheck=0;iBackCheck<iCount;iBackCheck++)
		 if ((GetElement(iBackCheck,iC)%iBias)!=0) iBias =1;
	    bUhoh = TRUE;
       };
	 if (bUhoh && (sElement%iBias != 0)) iBias =1;
    SetElement(iCount,iC,sElement);
   };
// in the second pass over the column, adjust all elements by the bias factor.
  if (bUhoh && iBias!=1)
  for (iCount=0;iCount<iRows;iCount++)
    SetElement(iCount,iC,GetElement(iCount,iC)/iBias);
};


matrix* matrix::FindNullSpace()
{ matrix *ptSolutions, *ptScalar;
  int iMatrixWidth=iColumns;
  int iMatrixHeight=iRows;
  int iSolMatHeight=max(iMatrixHeight,iMatrixWidth);
  int j,k,r;
/* the solution matrix has n+1 rows, where n is the dimension of the
   matrix to traverse. The n+1th row is Knuths c vector, and the n+2th row
   the mapping vector */
  ptSolutions= new matrix(iSolMatHeight,iMatrixWidth+2);
/* Step 1: Initialize the c vector to -1 */
  for (k=0; k<iSolMatHeight; k++)
   {ptSolutions->SetElement(k,iMatrixWidth,-1);
    ptSolutions->SetElement(k,iMatrixWidth+1,-1);
   };
  r = 0;
/* Step 2: Loop on k - do step 3 for k to matrix height, and then terminate */
  for (k=0; k<iMatrixHeight; k++)
/* Step 3: Scan row for dependence */
   {
     int iCount;
     int iMultiplicator;
     j=-1;
	 iMultiplicator=0;
/* Step 3a: Find a j such that a[k,j] !=0 and c[j]<0. Note that we are
   only dealing with 1-conservative nets; any other type of matrix needs
   more work here. */
     for (iCount=0;iCount<iMatrixWidth;iCount++)
       {
/* only consider elements whose columns have not been tagged yet. */
         if (ptSolutions->GetElement(iCount,iMatrixWidth)>=0)
           continue;
/* Now grab the next element...*/
         int iNext=GetElement(k,iCount);
/* -1 is perfect. Grab it, no questions asked. */
         if (iNext == -1)
            {j=iCount;  // best solution
             iMultiplicator=1;
             break;
            };
/* 1 is good as well, consider it, but keep looking for possible -1s. */
         if (iNext == 1)
            {j=iCount;
             iMultiplicator=-1;
            }
		 else
/* There is something in the matrix that is neither 1 nor -1. We're in
   trouble here... keep looking for something acceptable...*/
         if (iNext != 0)
		    iMultiplicator=iNext;
       };
/* End of j-selection code. */
    if (j==-1)
       {
/* we have a non-integer solution. Ideally we would have to backtrack now,
   but in this case we merely bail out... */

	   if (iMultiplicator!=0)
	      { delete (ptSolutions);
		    return (matrix *)0;
		  };
/* No appropriate j could be found. Add a solution to the matrix. */
      int iCount;
       for (iCount=0;iCount<iMatrixHeight;iCount++)
        { if (iCount==k)
           {ptSolutions->SetElement(iCount,r,1);
            continue;
           };
/* we must be associative here (find the column in which the row is marked) */
          int iTemp = ptSolutions->GetElement(iCount,iMatrixWidth+1);
          if (iTemp >=0)
            ptSolutions->SetElement(iCount,r,GetElement(k,iTemp));
        };
         r++;

      }
/* j was found, so transform the matrix... */
    else
      {

       int iCount;
       ptScalar=&(MultiplyColByInt(j,iMultiplicator));
       ReplaceColByScalar(j,*ptScalar);
       for (iCount=0;iCount<iMatrixWidth;iCount++)
         if (iCount!=j && GetElement(k,iCount)!=0)
           AddScalarToColumn(iCount,*ptScalar,GetElement(k,iCount));
       ptSolutions->SetElement(j,iMatrixWidth,0);
       ptSolutions->SetElement(k,iMatrixWidth+1,j);
      };
    };
   matrix *ptReturn=new matrix(iMatrixHeight,r);
   for (k=0;k<iMatrixHeight;k++)
    for (j=0;j<r;j++)
     ptReturn->SetElement(k,j,ptSolutions->GetElement(k,j));
   delete ptSolutions;
   return (ptReturn);
};

matrix *matrix::Copy()
{ matrix *mtNew;
  mtNew = new matrix(iRows,iColumns);
  int iR,iC;
  for (iR=0;iR<iRows;iR++)
   for (iC=0;iC<iColumns;iC++)
     mtNew->SetElement(iR,iC,GetElement(iR,iC));
  return mtNew;
};

