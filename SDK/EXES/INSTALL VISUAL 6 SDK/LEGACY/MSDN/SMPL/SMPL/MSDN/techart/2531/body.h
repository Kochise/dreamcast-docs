#ifndef	__BODY_H__
#define __BODY_H__

#include "phsprite.h"
#include "uni.h"

class CAnimDoc;


class CVector {
	public:
		double x ;
		double y ;
};

class CBody : public CPhasedSprite {
   DECLARE_SERIAL(CBody)

//Interface
	public:            
		CBody() ;     
		~CBody() ;
 
	
		void SetMass (double mass) ;		
		void SetVelocity (double Vx, double Vy) ; 
		void SetUPosition (double X, double Y ) ;  //Interference with CSprite...       
		void SetSPosition() ;
		static void SetUniverseScale(CRect* pRectScreen) ;
		void ApplyForce(CBody* pbody) ;
		void Update() ;
		void Reset() ;		

// AnimSprite compatability stuff ....
	BOOL DoDialog();
	virtual void Serialize(CArchive& ar);

//Implementation	
	protected:
		static CVector s_scale ;     
		CVector m_position ;
		CVector  m_velocity ;
		double m_mass ;
		double m_gmass ;
		
		// Initial postion
		CVector m_positionI ;
		CVector m_velocityI ;
		double m_massI ;
}; 

#endif //__BODY_H__
