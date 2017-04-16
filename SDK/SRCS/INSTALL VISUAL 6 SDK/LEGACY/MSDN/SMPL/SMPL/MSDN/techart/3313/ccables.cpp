#include "stdafx.h"
#include "ccables.h"

CCables::CCables() : FIRSTCONNECT(0x0001), SECONDCONNECT(0x0002)
{
  m_GestureOrient = BADQUAD;
}

CCables::~CCables()
{
}

////////////////////////////////////////////
//Operator=
//
CCables& CCables::operator=(const CCables & ccables)
{
  m_FirstConnector = ccables.m_FirstConnector;
  m_SecondConnector = ccables.m_SecondConnector;
  memcpy(&m_CtrlPts, &ccables.m_CtrlPts, NUMCONTROLPTS * sizeof(POINT));
  m_GestureLimit = ccables.m_GestureLimit;
  m_GestureOrient = ccables.m_GestureOrient;
  memcpy(&m_Hittest, &ccables.m_Hittest, HITTESTRECTS * sizeof(CRect));
  return *this;
}
  
////////////////////////////////////////////
//Copy Constructor
//
CCables::CCables(const CCables& ccables) : FIRSTCONNECT(0x0001), SECONDCONNECT(0x0002) 
{
  m_FirstConnector = ccables.m_FirstConnector;
  m_SecondConnector = ccables.m_SecondConnector;
  memcpy(&m_CtrlPts, &ccables.m_CtrlPts, NUMCONTROLPTS * sizeof(POINT));
  m_GestureLimit = ccables.m_GestureLimit;
  m_GestureOrient = ccables.m_GestureOrient;
  memcpy(&m_Hittest, &ccables.m_Hittest, HITTESTRECTS * sizeof(CRect));
}

////////////////////////////////////////////
//SetConnectorPoint
//
BOOL CCables::SetConnectorPoint(CPoint point, int nConnectorNum, CRect *prectHittest)
{
	if (nConnectorNum != (int)FIRSTCONNECT && nConnectorNum != (int)SECONDCONNECT)
	  return FALSE;

	int nLeft = point.x - CONNECTORRADIUS;
	int nTop = point.y - CONNECTORRADIUS;
	int nRight = point.x + CONNECTORRADIUS;
	int nBottom = point.y + CONNECTORRADIUS;

    //hittest bounding rect
	if (prectHittest)
      m_Hittest[nConnectorNum - 1] = *prectHittest;
	else
	{
	  m_Hittest[nConnectorNum - 1].left = nLeft;
	  m_Hittest[nConnectorNum - 1].top = nTop;
	  m_Hittest[nConnectorNum - 1].right = nRight;
	  m_Hittest[nConnectorNum - 1].bottom = nBottom;
	}

    if (nConnectorNum == (int)FIRSTCONNECT)
      m_FirstConnector = point; 
	else
	{
      m_SecondConnector = point; 
	}

    SetControlPoints();

	return TRUE;
};

////////////////////////////////////////////
//GetConnectorPoint
//
CPoint CCables::GetConnectorPoint(int nConnectorNum) 
{
  if (nConnectorNum == (int)FIRSTCONNECT) 
    return m_FirstConnector;
  else
    return m_SecondConnector;
};

////////////////////////////////////////////
//SetControlPoints
//
void CCables::SetControlPoints()
{ 
  m_CtrlPts[0].x = m_FirstConnector.x;
  m_CtrlPts[0].y = m_FirstConnector.y;

  m_CtrlPts[1].x = m_FirstConnector.x;
  m_CtrlPts[1].y = m_GestureLimit;

  m_CtrlPts[2].x = m_SecondConnector.x;
  m_CtrlPts[2].y = m_GestureLimit;

  m_CtrlPts[3].x = m_SecondConnector.x;
  m_CtrlPts[3].y = m_SecondConnector.y;
}

////////////////////////////////////////////
//SetGestureLimit
//
BOOL CCables::SetGestureLimit(CPoint point)
{
    if (m_GestureOrient == BADQUAD)
	  GetGestureOrientation(m_FirstConnector, point);

	switch (m_GestureOrient)
	{
	  case QUAD1:
	  case QUAD2:
        m_GestureLimit = (point.y <= m_GestureLimit) ? point.y : m_GestureLimit;
	    break;
      case QUAD3:
	  case QUAD4:
        m_GestureLimit = (point.y > m_GestureLimit) ? point.y : m_GestureLimit;
	    break;
	  default:
	    break;
	}
	return TRUE;
}

////////////////////////////////////////////
//GetGestureOrientation
//
void CCables::GetGestureOrientation(CPoint XY0, CPoint XY1)
{
  if ((XY1.x - XY0.x == BADQUAD) || (XY1.y - XY0.y == BADQUAD))
  {
    m_GestureLimit = XY0.y;
    return;
  }

  m_GestureOrient = (XY1.x >= XY0.x) 
                    ? ((XY1.y >= XY0.y) ? QUAD4 : QUAD1)
                    : ((XY1.y > XY0.y) ? QUAD3 : QUAD2);
  m_GestureLimit = XY0.y;
}

////////////////////////////////////////////
//HittestConnector
//
int CCables::HittestConnector(CPoint point)
{
  int nRet = 0;
  for (int i = 0; i < HITTESTRECTS; i++)
  {
    if (m_Hittest[i].PtInRect(point)) 
	{
	  nRet = i + 1;
	  break;
	}
  }
  return (nRet);
}

////////////////////////////////////////////
//OnDrawConnector
//
BOOL CCables::OnDrawConnector(CDC *pdc, int nConnectorNum)
{
  ASSERT (pdc);
  BOOL bRet = FALSE;

  if (pdc)
  {
	//draw connector based on hittest rect
	CRect rectDraw = (nConnectorNum & FIRSTCONNECT) ? m_Hittest[0]: m_Hittest[1];

	CBrush *pBrush = new(CBrush);
	pBrush->CreateStockObject(NULL_BRUSH);
	CBrush *OldBrush = pdc->SelectObject(pBrush);
	pdc->Ellipse((LPRECT)rectDraw);
	pdc->SelectObject(OldBrush);
	delete(pBrush);
	bRet = TRUE;
  }
  return bRet;
}

////////////////////////////////////////////
//OnDrawCable
//
BOOL CCables::OnDrawCable(CDC *pdc, int nViewLandmarks)
{
  ASSERT (pdc);
  BOOL bRet = FALSE;

  if (pdc)
  {
    if (pdc->PolyBezier((const POINT *)&m_CtrlPts, NUMCONTROLPTS))
      bRet = TRUE;

    if (nViewLandmarks)
    {
      POINT points[4];
	  points[0].x = m_CtrlPts[0].x;
	  points[0].y = m_CtrlPts[0].y;
	  points[1].x = m_CtrlPts[1].x;
	  points[1].y = m_CtrlPts[1].y;
	  points[2].x = m_CtrlPts[2].x;
	  points[2].y = m_CtrlPts[2].y;
	  points[3].x = m_CtrlPts[3].x;
	  points[3].y = m_CtrlPts[3].y;

	  CPen cpen(PS_SOLID, 1, RGB(0xFF, 0x00, 0x00));
      CPen *cpOldPen = pdc->SelectObject(&cpen);
	  //draw control polygon
	  pdc->Polyline((LPPOINT)&points, 4);
	  pdc->SelectObject(cpOldPen);
	  cpen.DeleteObject();
	  //draw 2nd and 3rd control points
	  pdc->Ellipse(m_CtrlPts[1].x-2, m_CtrlPts[1].y-2, 
	               m_CtrlPts[1].x + 2, m_CtrlPts[1].y + 2);
	  pdc->Ellipse(m_CtrlPts[2].x -2, m_CtrlPts[2].y -2, 
	               m_CtrlPts[2].x + 2, m_CtrlPts[2].y + 2);
    }
  }
  return bRet;
}
