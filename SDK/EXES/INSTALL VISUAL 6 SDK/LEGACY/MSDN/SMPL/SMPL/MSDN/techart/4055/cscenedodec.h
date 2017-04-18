#ifndef __CSCENEDODEC_H__
#define __CSCENEDODEC_H__

//
// CSceneDodec -
//
// Builds a CGL scene around the Dodec display list defined in shapes.cpp.
//
//

class CSceneDodec : public CGL
{
protected:
	// Override
	virtual BOOL OnResize(int cx, int cy) ;
	virtual BOOL OnInit() ;
	virtual BOOL OnRender() ;	
} ;
#endif 
