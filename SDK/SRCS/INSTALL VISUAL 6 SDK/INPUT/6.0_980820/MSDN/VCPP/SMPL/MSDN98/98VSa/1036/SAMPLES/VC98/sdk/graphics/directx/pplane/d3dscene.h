#ifndef D3DSCENE_H
#define D3DSCENE_H
/*
**-----------------------------------------------------------------------------
**  File:       D3DScene.h
**  Purpose:    Sample D3D Scene Management code
**  Notes:
**
**  Copyright (c) 1995 - 1997 by Microsoft, all rights reserved
**-----------------------------------------------------------------------------
*/

/*
**-----------------------------------------------------------------------------
**  Include files
**-----------------------------------------------------------------------------
*/

#include "Common.h"
#include "D3DWin.h"


/*
**-----------------------------------------------------------------------------
**  Classes
**-----------------------------------------------------------------------------
*/

/*
**-----------------------------------------------------------------------------
**  Name:	D3DScene
**  Purpose:
**-----------------------------------------------------------------------------
*/

class D3DScene {
private:
protected:
	// Data
	LPD3DWindow lpd3dWindow;		// Associated D3D Window

public:

	D3DScene ();
	~D3DScene ();

	HRESULT Init (LPD3DWindow lpd3dWin);
	HRESULT Fini (void);

	HRESULT InitViewport (void);
	HRESULT FiniViewport (void);

	HRESULT Render (void);
	HRESULT Restore (void);

}; // End class D3DScene


/*
**-----------------------------------------------------------------------------
**  End of File
**-----------------------------------------------------------------------------
*/
#endif // End D3DSCENE_H


