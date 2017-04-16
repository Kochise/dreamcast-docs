#ifndef __CSCENE_H__
#define __CSCENE_H__

class CScene : public CGL
{
public:	
	CScene() ;
	virtual ~CScene() ;
	// Attributes
	enum enum_OBJECTS {Box=1, Pyramid=2, Dodec=3} ;	

	// Rotation members
	void Rotate() ;
	void SetRotatingObject(enum_OBJECTS object) {m_RotatingObject = object;}
	enum_OBJECTS GetRotatingObject() {return m_RotatingObject; }

	CSize m_angle[4];
	enum_OBJECTS m_RotatingObject ;

	// Scissor support
	void SetOrigin(int x, int y) {m_ptOrg.x = x ; m_ptOrg.y = y; }
	CPoint m_ptOrg ;
		
protected:

	// Override
	virtual BOOL OnResize(int cx, int cy) ;
	virtual BOOL OnInit() ;
	virtual BOOL OnRender() ;	

} ;
#endif 
