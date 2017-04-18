// body.cpp : implementation file
//

 
#include "stdafx.h"
#include "gravity.h"
#include "animdoc.h"
//DER --- #include "animsp.h" 
#include "body.h"
#include "spritedl.h"

#include <math.h>
#include <limits.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBody

IMPLEMENT_SERIAL(CBody, CPhasedSprite, 0 /* schema number*/ )

//
// Statics
//
CVector CBody::s_scale ;

//
// CBody
//
CBody::CBody()
	: m_mass(0), m_gmass(0),m_massI(0)
{     
	m_position.x = 0.0 ;
	m_position.y = 0.0 ;
	m_velocity.x = 0.0 ;
	m_velocity.y = 0.0 ;	

	m_positionI.x = 0.0 ;
	m_positionI.y = 0.0 ;
	m_velocityI.x = 0.0 ;
	m_velocityI.y = 0.0 ;	
}  

CBody::~CBody()
{     
}
  

void CBody::SetMass( double mass)
{
	m_mass = m_massI = mass ;        
	m_gmass = CUniverse::G * mass ;

}

void CBody::SetVelocity(double Vx, double Vy)  
{
	m_velocity.x = m_velocityI.x = Vx ;
	m_velocity.y = m_velocityI.y = Vy ;
}


void CBody::SetUPosition (double X, double Y ) 
{
	m_position.x = m_positionI.x = X ;
	m_position.y = m_positionI.y = Y ;

	SetSPosition() ;
}

void CBody::SetSPosition()
{
	int x = (int)(m_position.x * s_scale.x) ;
	int y = (int)(m_position.y * s_scale.y) ;
	CPhasedSprite::SetPosition(x,y) ; // Notifies the list that the position has changed...
}

void CBody::ApplyForce(CBody* pbody)
{
	CVector d ;
	double rs;
	double r;
	double v ;   
	double vr ;
	
	d.x = m_position.x - pbody->m_position.x ;
	d.y = m_position.y - pbody->m_position.y ;
	
	rs = (d.x * d.x) + (d.y * d.y) ;
	if (rs != 0.0) // ICK! comparing floats...
	{
		r = sqrt(rs) ;
		v = (pbody->m_gmass / rs) * CUniverse::SECS_PER_TICK ; 
		vr = v / r ;
		m_velocity.x += vr * d.x ;
		m_velocity.y += vr * d.y ;
	}
}


void CBody::Update()
{
	m_position.x += m_velocity.x * CUniverse::SECS_PER_TICK ; 
	m_position.y += m_velocity.y * CUniverse::SECS_PER_TICK ;

	// Cycle through the phases
   if (GetNumPhases() > 1)
       SetPhase((GetPhase()+1)%GetNumPhases());
	// Set the sprite Screen position...
	SetSPosition() ;	
}


/////////////////////////////////////////////////////////////////////////////
// CBody serialization

void CBody::Serialize(CArchive& ar)
{
    CPhasedSprite::Serialize(ar);
    
    if (ar.IsStoring()) {
        ar <<  m_velocity.x;
        ar <<  m_velocity.y;
		  ar <<  m_position.x ;
		  ar <<  m_position.y ;
		  ar << 	m_mass ;
        ar <<  m_velocityI.x;
        ar <<  m_velocityI.y;
		  ar <<  m_positionI.x ;
		  ar <<  m_positionI.y ;
		  ar << 	m_massI ;
        //ar << (DWORD) m_bSelectable;
    } else  {
        ar >> m_velocity.x ;
        ar >> m_velocity.y ;
		  ar >>  m_position.x ;
		  ar >>  m_position.y ;
		  double mass ;
		  ar >> mass ;
		  SetMass(mass) ;
        ar >> m_velocityI.x ;
        ar >> m_velocityI.y ;
		  ar >>  m_positionI.x ;
		  ar >>  m_positionI.y ;
		  ar >> m_massI ;	
    }

}

/////////////////////////////////////////////////////////////////////////////
// CBody commands copied from CAnimSprite

// Show the sprite parameter dialog
BOOL CBody::DoDialog()
{
	//Now uses doubles instead of ints...
    CSpriteDlg dlg;
    dlg.m_x = m_position.x;
    dlg.m_y = m_position.y;
    dlg.m_vx = m_velocity.x;
    dlg.m_vy = m_velocity.y;
	 dlg.m_mass = m_mass ;
	 dlg.m_phases = GetNumPhases() ;
    dlg.pSprite = this;
    if (dlg.DoModal() == IDOK) {
        // Update sprite params and send notifications
        SetVelocity(dlg.m_vx, dlg.m_vy);
        SetUPosition(dlg.m_x, dlg.m_y);
		  SetMass(dlg.m_mass) ;
		  SetNumPhases(dlg.m_phases) ;
        return TRUE;
    }
    return FALSE;
}

void CBody::SetUniverseScale(CRect* pRectScreen)
{
	s_scale.x = (double)pRectScreen->right / CUniverse::HEIGHT ;
	s_scale.y = (double)pRectScreen->bottom / CUniverse::WIDTH ;
}

void CBody::Reset()
{
	m_velocity = m_velocityI ;
	m_position = m_positionI ;
	SetMass(m_massI) ;

	m_iPhase = 0 ; // Set Current phase back to zero

	SetSPosition() ;
}
