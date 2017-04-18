#ifndef __CSCENE_H__
#define __CSCENE_H__
struct CSize3D
{
	int cx, cy, cz;
} ;

class CScene : public CGL
{
public:	
	CScene() ;
	virtual ~CScene() ;
	// Attributes
	enum enum_OBJECTS {Box=1, Pyramid=2, Dodec=3} ;	

	// Rotation members
	void Rotate() ;
	void Bounce() ;

	CSize3D m_angle;
	CSize3D m_change ;

   // Texture Mapping Support
   CGLImage m_imageTexMap[6] ;

   double setTexRep(CGLImage& rImage) ;
 		
protected:

	// Override
	virtual BOOL OnCreate(CWnd* pWnd, PIXELFORMATDESCRIPTOR* pfd) ;
	virtual BOOL OnResize(int cx, int cy) ;
	virtual BOOL OnInit() ;
	virtual BOOL OnRender() ;	

   // Shapes
   void BoxList(int id, GLdouble size);
   void PyramidList(int id, GLdouble size) ;
   void DodecList(int id, GLdouble dsize) ;
} ;
#endif 
