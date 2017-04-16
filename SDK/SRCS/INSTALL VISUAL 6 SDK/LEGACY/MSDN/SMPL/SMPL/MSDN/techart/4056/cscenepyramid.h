#ifndef __CSCENEPYRAMID_H__
#define __CSCENEPYRAMID_H__

//
// CScenePyramid -
//
// Builds a CGL scene around the Pyramid display list defined in shapes.cpp.
//
//

class CScenePyramid : public CGL
{
protected:
	// Override
	virtual BOOL OnResize(int cx, int cy) ;
	virtual BOOL OnInit() ;
	virtual BOOL OnRender() ;	
} ;
#endif 
