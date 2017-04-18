#ifndef __CSCENE_H__
#define __CSCENE_H__

class CScene : public CGL
{
public:
	// An OpenGL Image, see GLlib.
	CGLImage m_anImage ;

	// Hold the size of Scene in pixels.
	CSize m_sizeScene ;

	// Construction/ Destruction
	CScene();
	virtual ~CScene() ;

protected:
	// Override
	virtual BOOL OnCreate(CWnd* pWnd, PIXELFORMATDESCRIPTOR* pfd);
	virtual BOOL OnResize(int cx, int cy) ;
	virtual BOOL OnInit() ;
	virtual BOOL OnRender() ;	
} ;
#endif 
