#ifndef __CSCENECI_H__
#define __CSCENECI_H__

class CSceneCI : public CGL
{
protected:
	// Attributes
	enum enum_OBJECTS {Box=1, Pyramid=2, Dodec=3} ;		

	// Override
	virtual BOOL OnCreate(CWnd* pWnd, PIXELFORMATDESCRIPTOR* pfd); 
	virtual BOOL OnResize(int cx, int cy) ;
	virtual BOOL OnInit() ;
	virtual BOOL OnRender() ;
	
	virtual BOOL OnCreatePaletteCI(LOGPALETTE* pPal) ;	// Setup color-index palette
} ;
#endif 
