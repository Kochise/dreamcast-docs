#include "stdafx.h"
#include "CShapeMenu.h"

//
// Self-drawing Menu Item Size
//
#define MENU_WIDTH     100
#define MENU_HEIGHT    100
	
//
// Constructor
//
CShapeMenu::CShapeMenu()
{
	m_pScenes[BOX] = NULL;
	m_pScenes[PYRAMID] = NULL;
	m_pScenes[DODEC] = NULL;
}

//
// Destructor
//
CShapeMenu::~CShapeMenu()
{
	if (m_pScenes[BOX]) 	   delete m_pScenes[BOX] ;
	if (m_pScenes[PYRAMID]) delete m_pScenes[PYRAMID] ;
	if (m_pScenes[DODEC]) 	delete m_pScenes[DODEC] ;

	Detach();
	ASSERT(m_hMenu == NULL);    // default CMenu::~CMenu will destroy
}

//
// ChangeMenuItem - Change menu item into a self-drawing (owner-drawn) menu.
//
void CShapeMenu::ChangeMenuItem(UINT nID, enum_SHAPES shape)
{
	VERIFY(ModifyMenu(	nID, 
						MF_BYCOMMAND | MF_ENABLED | MF_OWNERDRAW,
						nID,
						(LPCTSTR)shape));
}

//
// Init - Initialize CShapeMenu by creating the scenes and DIBs.
//
void CShapeMenu::Init()
{
	// Allocate the OpenGL scenes.
	m_pScenes[BOX] = 		new CSceneBox ;
	m_pScenes[PYRAMID] = 	new CScenePyramid ;
	m_pScenes[DODEC] = 		new CSceneDodec ;

	CClientDC dc(NULL) ;
	int iBitsPixel = dc.GetDeviceCaps(BITSPIXEL) ;	
	if (iBitsPixel == 16) iBitsPixel = 8 ; // Use 8 bpp dibs because they are faster...
	
	for(int i = 0 ; i < 3 ; i++)
	{
		// Create the DIBs to render the scenes on.
		m_DIB[i].Create(MENU_WIDTH, MENU_HEIGHT, iBitsPixel) ;
		CDC* pdcTemp = m_DIB[i].GetDC() ;

		// Create the OpenGL scenes.
		m_pScenes[i]->Create(pdcTemp) ;

		// Set DIB palette to the palette from the scene.
		CPalette* pPalTemp = m_pScenes[i]->GetPalette() ;
		if (pPalTemp) m_DIB[i].SetPalette(pPalTemp) ;

		// Render the scene onto the DIB.
		m_pScenes[i]->Resize(MENU_WIDTH, MENU_HEIGHT) ; //Doesn't resize?!!!!
		m_pScenes[i]->Init() ;
		m_pScenes[i]->Render() ;
	}			
}
/////////////////////////////////////////////////////////////////////////////
//
// Virtual function overrides.
//


//
// MeasureItem - returns the size of the menu item.
//
void CShapeMenu::MeasureItem(LPMEASUREITEMSTRUCT lpMIS)
{
	int iWidthCheck = LOWORD(GetMenuCheckMarkDimensions()) ;

	// all items are of fixed size
	lpMIS->itemHeight = MENU_HEIGHT;
	// Remove space automatically added for the check mark
	lpMIS->itemWidth = MENU_WIDTH - iWidthCheck;

}

//
// DrawItem - Draw the menu.
//
void CShapeMenu::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
	CDC* pDC = CDC::FromHandle(lpDIS->hDC);
	enum_SHAPES nShape = (enum_SHAPES)lpDIS->itemData;

	// Use GetSysColor if it makes sense.
	const COLORREF crSelect = RGB(255,0,0) ;	// Selection color
	const COLORREF crCheck 	= RGB(0,0,255) ;	// Checked color
	const COLORREF crNormal = RGB(0,255,0) ;	// Normal Color
	COLORREF cr = crNormal;

	if (lpDIS->itemAction & ODA_DRAWENTIRE)
	{
		CPalette* pOldPal = NULL;

		// Set palette.
		CPalette* pPalTemp = m_pScenes[nShape]->GetPalette() ;
		if (pPalTemp != NULL)
		{
			pOldPal = pDC->SelectPalette(pPalTemp, FALSE) ;
			pDC->RealizePalette() ;		
		}

		// Draw the bitmap.
		m_DIB[nShape].Draw(pDC,lpDIS->rcItem.left, lpDIS->rcItem.top) ;

 		if (pOldPal != NULL) pDC->SelectPalette(pOldPal, FALSE ) ;
	}

	if (lpDIS->itemState & ODS_CHECKED)
	{
		// Menu item is checked.
		cr = crCheck ;
	}

	if (lpDIS->itemAction & ODA_SELECT)
	{
		if (lpDIS->itemState & ODS_SELECTED)
		{
			// Menu item is selected.
			cr = crSelect ;
		}
	}
	
	// Draw the border around the menu item. Color based on menu state.
	CBrush br(cr);
	CRgn rgn;
	rgn.CreateRectRgnIndirect(&lpDIS->rcItem) ;
	pDC->FrameRgn(&rgn,&br,4,4) ;
}
