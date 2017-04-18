/***************************************************************************/
/*                 File: classes.cpp (contains C++ class declarations)     */
/***************************************************************************/


/***************************************************************************/
/*                 INCLUDES                                                */
/***************************************************************************/

#define CLASSES


#include "classes.h"
#include <math.h>
#include "pntdoc.h"
#include "netview.h"

/***************************************************************************/
/*                 The chained structure object                            */
/***************************************************************************/

ChainedStructure::ChainedStructure()
{
csNext=(ChainedStructure *)0;
};
ChainedStructure::~ChainedStructure()
{};
BOOL ChainedStructure::AppendAtEnd(ChainedStructure *csNew)
{
if (csNext==(ChainedStructure *)0)
   {csNext=csNew;
    return TRUE;
   }
   else
   if (csNext==csNew) return FALSE;
   else return csNext->AppendAtEnd(csNew);  
};
ChainedStructure * ChainedStructure::AppendUpFront(ChainedStructure *csNew)
{
ChainedStructure *csResult = csNext;
csNext = csNew;
return csResult;
};


/***************************************************************************/
/*                 The TP object                                           */
/***************************************************************************/

TP::TP(int ix,int iy)
{
  bAlerted=FALSE;
  szName="\0";
  Reposition(ix,iy);
};

void TP::Name(CString lpName)
{ szName=lpName;
};

TP::~TP()
{
};

BOOL TP::Reposition(int ix, int iy)
{  
    if ((abs(iX-ix)<DONTMOVESPACE) && (abs(iY-iy)<DONTMOVESPACE))
	 return (FALSE);
	 iX=ix;
	 iY=iy;
	 return (TRUE);
};

void TP::SnapToGrid(int iSnapSize)
{ int iLower, iUpper;
iLower=iSnapSize*(iX/iSnapSize);
if (iLower!=iX)
 {
   iUpper=iLower+iSnapSize;
   if (iX>(iLower+(iSnapSize/2)) || (iLower<PLACEXEXTENSION/2))
     iX=iUpper;
   else iX=iLower;
 };
iLower=iSnapSize*(iY/iSnapSize);
if (iLower!=iY)
 {
   iUpper=iLower+iSnapSize;
   if (iY>(iLower+(iSnapSize/2)) || (iLower<PLACEYEXTENSION/2))
     iY=iUpper;
   else iY=iLower;
 };
if (Succ()!= (TP *)0)
  Succ()->SnapToGrid(iSnapSize);
}

void TP::Alert(BOOL bAction)
{ bAlerted = bAction;
};

TP *TP::Hittest(int iCurrentX,int iCurrentY)
{
   {if ((abs(iX-iCurrentX)<((iType&TRANSITION_TYPE)?TRANSXEXTENSION:
    													PLACEXEXTENSION)) &&
        (abs(iY-iCurrentY)<((iType&PLACE_TYPE)?PLACEYEXTENSION:
        										   TRANSYEXTENSION)))
	return this;
	else {if (Succ() != (TP *)0)
	       return (Succ()->Hittest(iCurrentX,iCurrentY));
		 };
	return (TP *)0;
   };
}

/***************************************************************************/
/*                 The TPLIST object                                       */
/***************************************************************************/


TPLIST::TPLIST(place *tpEl)
{ tpElement = tpEl;
};

TPLIST::~TPLIST()
{};

BOOL TPLIST::AppendAtEnd(TPLIST *tpNew)
{
 if (csNext == (TPLIST *)0) 
  {csNext = tpNew;
   return TRUE;
  }
 else
// we will not allow multiple connections to the same element, sorry... 
  {if (tpElement==tpNew->tpElement) return FALSE; 
   return (csNext->AppendAtEnd(tpNew));
  };
};


/***************************************************************************/
/*          Objects derived from the TP class                              */
/***************************************************************************/

place::place(int ix,int iy) : TP(ix, iy)
{
iType = PLACE_TYPE;
bMarkState=FALSE;
};

transition::transition(int ix,int iy) : TP(ix, iy)
{
backwardlink = (TPLIST *)0;
forwardlink = (TPLIST *)0;
iType = TRANSITION_TYPE;
};

place::~place(void)
{ 
};

transition::~transition(void)
{
};

void place::Mark(BOOL bMark)
{ 
  bMarkState = bMark;
};

BOOL place::GetMark(void)
{ return bMarkState;
};

#define DELTA 5.0
#define COS120 -.5
#define SIN120 .866025
#define COS240 COS120
#define SIN240 SIN120*-1.0


CRect place::GetRect(CPoint cpOffset)
{   return CRect(iX-PLACEXEXTENSION/2-cpOffset.x,iY-PLACEYEXTENSION/2-cpOffset.y,
			   iX+PLACEXEXTENSION/2-cpOffset.x,iY+PLACEYEXTENSION/2-cpOffset.y);
};

void place::DrawYourself(CDC *hDC)
{ int iCenterX,iCenterY;
  CBrush *hOldBrush;
  CBrush hStockBrush;

  if (bAlerted) 
    {hStockBrush.CreateStockObject(GRAY_BRUSH);
     hOldBrush=hDC->SelectObject(&hStockBrush);
	}

     iCenterX=iX-(PLACEXEXTENSION/2);
	 iCenterY=iY-(PLACEYEXTENSION/2);
     hDC->Ellipse(iCenterX,iCenterY,iCenterX+PLACEXEXTENSION,iCenterY+PLACEYEXTENSION);
  if (bAlerted) hDC->SelectObject(hOldBrush);

	 if (bMarkState)
	 {
	  hStockBrush.CreateStockObject(BLACK_BRUSH);
	  hOldBrush=hDC->SelectObject(&hStockBrush);
      hDC->Ellipse(iCenterX+(int)(PLACEXEXTENSION/4),
                   iCenterY+(int)(PLACEXEXTENSION/4),
                   iCenterX+(int)(PLACEXEXTENSION*.75),
                   iCenterY+(int)(PLACEYEXTENSION*.75));
	 hDC->SelectObject(hOldBrush);
	 };

     hDC->TextOut(iCenterX+PLACEXEXTENSION,iCenterY,szName);

  if (Succ() != (TP *)0)
    Succ()->DrawYourself(hDC);

};

CRect transition::GetRect(CPoint cpOffset)
{  return CRect(iX-TRANSXEXTENSION/2-cpOffset.x,iY-TRANSYEXTENSION/2-cpOffset.y,
			   iX+TRANSXEXTENSION/2-cpOffset.x,iY+TRANSYEXTENSION/2-cpOffset.y);
};


void transition::DrawYourself(CDC *hDC)
{ int iCenterX,iCenterY;
  TPLIST *tpChain;
  CBrush *hOldBrush;
  CBrush hStockBrush;
  hStockBrush.CreateStockObject(BLACK_BRUSH);
  hOldBrush=hDC->SelectObject(&hStockBrush);
  tpChain = forwardlink;
// this while loop runs through all forward connections and displays them as
// arrows...
  while (tpChain != (TPLIST *)0)
    {
     int iTargetX, iTargetY;
     POINT ptArrow[3];
     float iNewX,iNewY;
     iTargetX=tpChain->tpElement->iX;
     iTargetY=tpChain->tpElement->iY;
     float iSlope;
     if (iX==iTargetX) iSlope=0; else iSlope=(float)(iTargetY-iY)/(float)(iTargetX-iX);
// We have to stop short of the circle because otherwise parts of it gets
// overwritten -- here we compute where to stop... 
     iNewX=((float)1.0/(float)sqrt((float)1.0+((float)iSlope*(float)iSlope)));
     iNewY=((iSlope<0?iSlope*(float)-1.0:iSlope)/(float)sqrt((float)1.0+((float)iSlope*(float)iSlope)));
     if (iX==iTargetX) {iNewX=0; iNewY=1;}
     if (iX<iTargetX) iNewX*=(float)-1.;
     if (iY<iTargetY) iNewY*=(float)-1.;
     iTargetX+=(int)(iNewX*((float)PLACEXEXTENSION/2));
     iTargetY+=(int)(iNewY*((float)PLACEYEXTENSION/2));
     hDC->MoveTo(iX,iY);
     hDC->LineTo(iTargetX,iTargetY);
// now compute the middle of the line so we can draw the arrow head around it
     iCenterX=((abs(iTargetX-iX))/2+min(iX,iTargetX));
     iCenterY=((abs(iTargetY-iY))/2+min(iY,iTargetY));
     iNewX=(float)(1/sqrt(1+(iSlope*iSlope)));
     iNewY=(float)(iSlope/sqrt(1+(iSlope*iSlope)));
     if (iCenterX==iTargetX) 
        {
         iNewX=0; 
         iNewY=(iTargetY>iCenterY) ? (float)1 : (float)-1;
        }
       else
     if (iCenterX>iTargetX) {iNewY*=(float)-1; iNewX*=(float)-1;};
// assign the arrow head coordinates.
     ptArrow[0].x= (int)(DELTA*iNewX)+iCenterX; 
     ptArrow[0].y= (int)(DELTA*iNewY)+iCenterY; 
     ptArrow[1].x= (int)(iNewX*COS120*DELTA-iNewY*SIN120*DELTA)+iCenterX;
     ptArrow[1].y= (int)(iNewX*SIN120*DELTA+iNewY*COS120*DELTA)+iCenterY;     
     ptArrow[2].x= (int)(iNewX*COS240*DELTA-iNewY*SIN240*DELTA)+iCenterX;
     ptArrow[2].y= (int)(iNewX*SIN240*DELTA+iNewY*COS240*DELTA)+iCenterY;
// draw the arrow head
     hDC->Polygon(ptArrow,3);
     tpChain=tpChain->Succ();
    }; // end of loop through forward connections.
// Now do the same thing for the backwards connections.
// The only difference here is that we need to flip the arrow head.
  tpChain = backwardlink;
  while (tpChain != (TPLIST *)0)
     {
      int iTargetX, iTargetY;
      POINT ptArrow[3];
      float iNewX,iNewY;
      iTargetX=tpChain->tpElement->iX;
      iTargetY=tpChain->tpElement->iY;
      float iSlope;
      if (iX==iTargetX) iSlope=0; else iSlope=(float)(iTargetY-iY)/(float)(iTargetX-iX);
// We have to stop short of the circle because otherwise parts of it gets
// overwritten -- here we compute where to stop... 
      iNewX=((float)1.0/(float)sqrt((float)1.0+((float)iSlope*(float)iSlope)));
      iNewY=((iSlope<0?iSlope*(float)-1.0:iSlope)/(float)sqrt((float)1.0+((float)iSlope*(float)iSlope)));
      if (iX==iTargetX) {iNewX=0; iNewY=1;}
      if (iX<iTargetX) iNewX*=(float)-1.;
      if (iY<iTargetY) iNewY*=(float)-1.;
      iTargetX+=(int)(iNewX*((float)PLACEXEXTENSION/2));
      iTargetY+=(int)(iNewY*((float)PLACEYEXTENSION/2));
      hDC->MoveTo(iX,iY);
      hDC->LineTo(iTargetX,iTargetY);
// now compute the middle of the line so we can draw the arrow head around it
      iCenterX=((abs(iTargetX-iX))/2+min(iX,iTargetX));
      iCenterY=((abs(iTargetY-iY))/2+min(iY,iTargetY));
      iNewX=(float)(1/sqrt(1+(iSlope*iSlope)));
      iNewY=(float)(iSlope/sqrt(1+(iSlope*iSlope)));
      if (iCenterX==iTargetX) 
        {iNewX=0; 
         iNewY= (iTargetY<iCenterY) ? (float)1 : (float)-1;
        }
        else
      if (iCenterX<iTargetX) {iNewY*=(float)-1; iNewX*=(float)-1;};

// assign the arrow head coordinates.
      ptArrow[0].x= (int)(DELTA*iNewX)+iCenterX; 
      ptArrow[0].y= (int)(DELTA*iNewY)+iCenterY; 
      ptArrow[1].x= (int)(iNewX*COS120*DELTA-iNewY*SIN120*DELTA)+iCenterX;
      ptArrow[1].y= (int)(iNewX*SIN120*DELTA+iNewY*COS120*DELTA)+iCenterY;     
      ptArrow[2].x= (int)(iNewX*COS240*DELTA-iNewY*SIN240*DELTA)+iCenterX;
      ptArrow[2].y= (int)(iNewX*SIN240*DELTA+iNewY*COS240*DELTA)+iCenterY;
// draw the arrow head.
      hDC->Polygon(ptArrow,3);
      tpChain=tpChain->Succ();
	}; // end of loop through backward connections.

  hDC->SelectObject(hOldBrush);
  if (bAlerted) 
    {hStockBrush.CreateStockObject(GRAY_BRUSH);
     hOldBrush=hDC->SelectObject(&hStockBrush);
    }
// this section displays the transition...
  iCenterX=iX-(TRANSXEXTENSION/2); 
  iCenterY=iY-(TRANSYEXTENSION/2);
  hDC->Rectangle(iCenterX,iCenterY,iCenterX+TRANSXEXTENSION,iCenterY+TRANSYEXTENSION);
  hDC->TextOut(iCenterX+TRANSXEXTENSION,iCenterY,szName);
  if (bAlerted) hDC->SelectObject(hOldBrush);
  if (Succ() != (TP *)0)
    Succ()->DrawYourself(hDC);
};

BOOL place::Connect(TP *whereto)
{ return ((transition *)whereto)->BackConnect(new TPLIST(this));
};

BOOL transition::Connect(TP *whereto)
{ TPLIST *tplNew = new TPLIST((place *)whereto);
  if (forwardlink == (TPLIST *)0)
   {forwardlink = tplNew;
    return (TRUE);
   }
  else return forwardlink->AppendAtEnd(tplNew);
};

BOOL transition::BackConnect(TPLIST *whereto)
{ if (backwardlink == (TPLIST *)0)
   {backwardlink = whereto;
    return (TRUE);
   }
  else return backwardlink->AppendAtEnd(whereto);
};

void transition::DisConnect(place *wherefrom)
{
TPLIST *traverselist, *tpVictim;
 traverselist=backwardlink;
// we first remove any occurrences of the taget place in the head of the 
// chain. Note that we do not allow more than one Insert of the same element. 
 if ((traverselist!= (TPLIST *)0) && (traverselist->tpElement==wherefrom))
   {tpVictim=backwardlink;
    backwardlink=backwardlink->Succ();
    delete (tpVictim);
   }
 else
 while (traverselist!=(TPLIST *)0 && traverselist->Succ()!=(TPLIST *)0)
 { if (traverselist->Succ()->tpElement==wherefrom)
     {tpVictim=traverselist->Succ();
      traverselist->AppendUpFront(tpVictim->Succ());
      delete (tpVictim);
      break;
     };
   traverselist=traverselist->Succ();
 };
// now do the same thing with the forward links...
traverselist=forwardlink;
// we first remove any occurrences of the target place in the head of the 
// chain. Note that we do not allow more than one Insert of the same element,
// so after the first occurrence is found, we can stop... 
 if ((traverselist!= (TPLIST *)0) && (traverselist->tpElement==wherefrom))
   {tpVictim=forwardlink;
    forwardlink=forwardlink->Succ();
    delete (tpVictim);
   }
 else
 while (traverselist!=(TPLIST *)0 && traverselist->Succ()!=(TPLIST *)0)
 { if (traverselist->Succ()->tpElement==wherefrom)
     {tpVictim=traverselist->Succ();
      traverselist->AppendUpFront(tpVictim->Succ());
      delete (tpVictim);
      break;
     };
   traverselist=traverselist->Succ();
 };
 	  
}; 


TPLIST *transition::GetConnections(BOOL bWhich)
{ if (bWhich) return forwardlink; else return backwardlink;
};


