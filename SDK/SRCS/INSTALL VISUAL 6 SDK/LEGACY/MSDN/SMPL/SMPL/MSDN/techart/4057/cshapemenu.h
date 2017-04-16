#ifndef __CSHAPEMENU_H__
#define __CSHAPEMENU_H__

#include "gllib.h"
#include "CSceneBox.h"
#include "CSceneDodec.h"
#include "CScenePyramid.h"
#include "CSimpleDib.h"

//
// CShape Menu -
//
// Implements a self-drawing menu that displays OpenGL rendered DIBs.
//
class CShapeMenu : public CMenu
{
public:
	enum enum_SHAPES {BOX, PYRAMID, DODEC} ; 
// Operations
	// Modify menu to make it owner-drawn.
	void ChangeMenuItem(UINT nID, enum_SHAPES shape);
	
	// Initialize CShapeMenu.
	void Init() ;

// Virtual Overrides.
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMIS);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);

// Construction 
	CShapeMenu();
	virtual ~CShapeMenu();

private:
	CGL* m_pScenes[3] ;		// OpenGL scenes of the three shapes.
	CSimpleDIB m_DIB[3] ;	// DIB sections scenes are rendered on.

};
#endif
