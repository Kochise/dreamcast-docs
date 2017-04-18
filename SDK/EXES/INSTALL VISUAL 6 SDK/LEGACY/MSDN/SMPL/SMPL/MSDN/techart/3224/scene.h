#ifndef __CSCENE_H__
#define __CSCENE_H__

class CScene : public CGL
{
protected:
	// Attributes
	enum enum_OBJECTS {Box=1, Pyramid=2, Dodec=3} ;		

	// Override
	virtual BOOL OnResize(int cx, int cy) ;
	virtual BOOL OnInit() ;
	virtual BOOL OnRender() ;
	
	virtual BOOL OnCreatePaletteCI(LOGPALETTE* pPal) ;	// Setup color-index palette
} ;
#endif 
