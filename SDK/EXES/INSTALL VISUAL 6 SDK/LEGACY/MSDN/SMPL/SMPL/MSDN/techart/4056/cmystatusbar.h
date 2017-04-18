
#ifndef __MYSTATUSBAR_H__
#define __MYSTATUSBAR_H__

#include "gllib.h"
#include "CSceneBox.h"
#include "CSceneDodec.h"
#include "CScenePyramid.h"
#include "CSimpleDib.h"

class CMyStatusBar : public CStatusBar
{
	public:
		// Construction
		CMyStatusBar() ;
		~CMyStatusBar() ;

		// Initialize our status bar.
		void Init() ;

		// Set the bitmap to display in the statusbar.
		void SetBitmap(int i) ;

		// Override the painting of the statusbar.
		void DoPaint(CDC* pDC) ;


  protected:
      CFont m_Font ; 			// Font for statusbar.
      int m_iCurrentDIB ;		// Index of DIB currently displayed in dialog.
      CGL* m_pScenes[3] ;		// OpenGL rendered scenes.
      CSimpleDIB m_DIB[3] ;	// DIBs to hold the OpenGL scenes.
} ;
#endif
