//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This source code is a part of BCGControlBar library.
// You may use, compile or redistribute it as part of your application 
// for free. You cannot redistribute it as a part of a software development 
// library without the agreement of the author. If the sources are 
// distributed along with the application, you should leave the original 
// copyright notes in the source code without any changes.
// This code can be used WITHOUT ANY WARRANTIES on your own risk.
// 
// For the latest updates to this library, check my site:
// http://welcome.to/bcgsoft
// 
// Stas Levin <bcgsoft@yahoo.com>
//*******************************************************************************

// MenuImages.h: interface for the CMenuImages class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MENUIMAGES_H__DE028D41_36EB_11D3_95C5_00A0C9289F1B__INCLUDED_)
#define AFX_MENUIMAGES_H__DE028D41_36EB_11D3_95C5_00A0C9289F1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bcgcontrolbar.h"
#include "BCGToolBarImages.h"

class BCGCONTROLBARDLLEXPORT CMenuImages  
{
public:
	enum IMAGES_IDS
	{
		IdArowDown,
		IdArowDownDsbl,
		IdArowLeft,
		IdArowLeftDsbl,
		IdArowLeftWhite,
		IdArowLeftWhiteDsbl,
		IdCheck,
		IdCheckDsbl,
		IdMinimize,
		IdMinimizeDsbl,
		IdRestore,
		IdRestoreDsbl,
		IdClose,
		IdCloseDsbl,
		IdMaximize,
		IdMaximizeDsbl,
		IdArowUp,
		IdArowUpDisabled,
		IdArowShowAll,
		IdArowRight,
		IdCloseSmall,
		IdMoreButtons,
		IdRadio,
		IdRadioDsbl,
		IdArowDownLarge,
		IdArowDownLargeDsbl,
		IdArowLeftLarge,
		IdArowLeftLargeDsbl,
	};

	static void Draw (CDC* pDC, CMenuImages::IMAGES_IDS id, const CPoint& ptImage,
					  const CSize& sizeImage = CSize (0, 0));
	static CSize Size()
	{
		Initialize ();
		return m_Images.GetImageSize ();
	}

	static void CleanUp ();

protected:
	static BOOL Initialize ();
	static CBCGToolBarImages	m_Images;
};

#endif // !defined(AFX_MENUIMAGES_H__DE028D41_36EB_11D3_95C5_00A0C9289F1B__INCLUDED_)
