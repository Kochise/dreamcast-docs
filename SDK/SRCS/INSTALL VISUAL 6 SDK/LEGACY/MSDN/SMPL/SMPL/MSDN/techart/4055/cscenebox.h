#ifndef __CSCENEBOX_H__
#define __CSCENEBOX_H__

//
// CSceneBox -
//
// Builds a CGL scene around the Box display list defined in shapes.cpp.
//
//
class CSceneBox : public CGL
{
protected:
	// Override
	virtual BOOL OnResize(int cx, int cy) ;
	virtual BOOL OnInit() ;
	virtual BOOL OnRender() ;	
} ;
#endif 
