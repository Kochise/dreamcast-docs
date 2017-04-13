/*
 * XFORM.CPP
 *
 * Utility functions for coordinate conversion taken from the
 * original OLE UI Library.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "inoledll.h"


#define HIMETRIC_PER_INCH   2540    //Number HIMETRIC units per inch
#define PTS_PER_INCH        72      //Number points (font size) per inch

#define MAP_PIX_TO_LOGHIM(x,ppli)   MulDiv(HIMETRIC_PER_INCH, (x), (ppli))
#define MAP_LOGHIM_TO_PIX(x,ppli)   MulDiv((ppli), (x), HIMETRIC_PER_INCH)



/*
 * XformWidthInPixelsToHimetric
 * XformWidthInHimetricToPixels
 * XformHeightInPixelsToHimetric
 * XformHeightInHimetricToPixels
 *
 * Functions to convert an int between a device coordinate system and
 * logical HiMetric units.
 *
 * Parameters:
 *  hDC             HDC providing reference to the pixel mapping.  If
 *                  NULL, a screen DC is used.
 *  (others)        Values to convert
 *
 * NOTE:
 *  When displaying on the screen, Window apps display everything enlarged
 *  from its actual size so that it is easier to read. For example, if an
 *  app wants to display a 1in. horizontal line, that when printed is
 *  actually a 1in. line on the printed page, then it will display the line
 *  on the screen physically larger than 1in. This is described as a line
 *  that is "logically" 1in. along the display width. Windows maintains as
 *  part of the device-specific information about a given display device:
 *      LOGPIXELSX -- no. of pixels per logical in along the display width
 *      LOGPIXELSY -- no. of pixels per logical in along the display height
 *
 *  The following formula converts a distance in pixels into its equivalent
 *  logical HIMETRIC units:
 *
 *      DistInHiMetric = (HIMETRIC_PER_INCH * DistInPix)
 *                       -------------------------------
 *                           PIXELS_PER_LOGICAL_IN
 *
 */

STDAPI_(int) XformWidthInPixelsToHimetric(HDC hDC, int iWidthInPix)
	{
	int     iXppli;     //Pixels per logical inch along width
	int     iWidthInHiMetric;
	BOOL    fSystemDC=FALSE;

	if (NULL==hDC)
		{
		hDC=GetDC(NULL);
		fSystemDC=TRUE;
		}

	iXppli=GetDeviceCaps (hDC, LOGPIXELSX);

	//We got pixel units, convert them to logical HIMETRIC along the display
	iWidthInHiMetric=MAP_PIX_TO_LOGHIM(iWidthInPix, iXppli);

	if (fSystemDC)
		ReleaseDC(NULL, hDC);

	return iWidthInHiMetric;
	}


STDAPI_(int) XformWidthInHimetricToPixels(HDC hDC, int iWidthInHiMetric)
	{
	int     iXppli;     //Pixels per logical inch along width
	int     iWidthInPix;
	BOOL    fSystemDC=FALSE;

	if (NULL==hDC)
		{
		hDC=GetDC(NULL);
		fSystemDC=TRUE;
		}

	iXppli=GetDeviceCaps (hDC, LOGPIXELSX);

	//We got logical HIMETRIC along the display, convert them to pixel units
	iWidthInPix=MAP_LOGHIM_TO_PIX(iWidthInHiMetric, iXppli);

	if (fSystemDC)
		ReleaseDC(NULL, hDC);

	return iWidthInPix;
	}


STDAPI_(int) XformHeightInPixelsToHimetric(HDC hDC, int iHeightInPix)
	{
	int     iYppli;     //Pixels per logical inch along height
	int     iHeightInHiMetric;
	BOOL    fSystemDC=FALSE;

	if (NULL==hDC)
		{
		hDC=GetDC(NULL);
		fSystemDC=TRUE;
		}

	iYppli=GetDeviceCaps (hDC, LOGPIXELSY);

	//We got pixel units, convert them to logical HIMETRIC along the display
	iHeightInHiMetric=MAP_PIX_TO_LOGHIM(iHeightInPix, iYppli);

	if (fSystemDC)
		ReleaseDC(NULL, hDC);

	return iHeightInHiMetric;
	}


STDAPI_(int) XformHeightInHimetricToPixels(HDC hDC, int iHeightInHiMetric)
	{
	int     iYppli;     //Pixels per logical inch along height
	int     iHeightInPix;
	BOOL    fSystemDC=FALSE;

	if (NULL==hDC)
		{
		hDC=GetDC(NULL);
		fSystemDC=TRUE;
		}

	iYppli=GetDeviceCaps (hDC, LOGPIXELSY);

	//We got logical HIMETRIC along the display, convert them to pixel units
	iHeightInPix=MAP_LOGHIM_TO_PIX(iHeightInHiMetric, iYppli);

	if (fSystemDC)
		ReleaseDC(NULL, hDC);

	return iHeightInPix;
	}



/*
 * XformRectInPixelsToHimetric
 * XformRectInHimetricToPixels
 *
 * Purpose:
 *  Convert a rectangle between pixels of a given hDC and HIMETRIC units
 *  as manipulated in OLE.  If the hDC is NULL, then a screen DC is used
 *  and assumes the MM_TEXT mapping mode.
 *
 * Parameters:
 *  hDC             HDC providing reference to the pixel mapping.  If
 *                  NULL, a screen DC is used.
 *  prcPix          LPRECT containng the rectangles to convert.
 *  prcHiMetric
 *
 * Return Value:
 *  None
 *
 * NOTE:
 *  When displaying on the screen, Window apps display everything enlarged
 *  from its actual size so that it is easier to read. For example, if an
 *  app wants to display a 1in. horizontal line, that when printed is
 *  actually a 1in. line on the printed page, then it will display the line
 *  on the screen physically larger than 1in. This is described as a line
 *  that is "logically" 1in. along the display width. Windows maintains as
 *  part of the device-specific information about a given display device:
 *      LOGPIXELSX -- no. of pixels per logical in along the display width
 *      LOGPIXELSY -- no. of pixels per logical in along the display height
 *
 *  The following formula converts a distance in pixels into its equivalent
 *  logical HIMETRIC units:
 *
 *      DistInHiMetric=(HIMETRIC_PER_INCH * DistInPix)
 *                      -------------------------------
 *                            PIXELS_PER_LOGICAL_IN
 *
 * Rect in Pixels (MM_TEXT):
 *
 *              0---------- X
 *              |
 *              |       1) ------------------ ( 2   P1=(rc.left, rc.top)
 *              |       |                     |     P2=(rc.right, rc.top)
 *              |       |                     |     P3=(rc.left, rc.bottom)
 *              |       |                     |     P4=(rc.right, rc.bottom)
 *                      |                     |
 *              Y       |                     |
 *                      3) ------------------ ( 4
 *
 *              NOTE:   Origin  =(P1x, P1y)
 *                      X extent=P4x - P1x
 *                      Y extent=P4y - P1y
 *
 *
 * Rect in Himetric (MM_HIMETRIC):
 *
 *
 *                      1) ------------------ ( 2   P1=(rc.left, rc.top)
 *              Y       |                     |     P2=(rc.right, rc.top)
 *                      |                     |     P3=(rc.left, rc.bottom)
 *              |       |                     |     P4=(rc.right, rc.bottom)
 *              |       |                     |
 *              |       |                     |
 *              |       3) ------------------ ( 4
 *              |
 *              0---------- X
 *
 *              NOTE:   Origin  =(P3x, P3y)
 *                      X extent=P2x - P3x
 *                      Y extent=P2y - P3y
 *
 *
 */

STDAPI_(void) XformRectInPixelsToHimetric(HDC hDC, LPRECT prcPix
	, LPRECT prcHiMetric)
	{
	int     iXppli;     //Pixels per logical inch along width
	int     iYppli;     //Pixels per logical inch along height
	int     iXextInPix=(prcPix->right-prcPix->left);
	int     iYextInPix=(prcPix->bottom-prcPix->top);
	BOOL    fSystemDC=FALSE;

	if (NULL==hDC || GetDeviceCaps(hDC, LOGPIXELSX) == 0)
		{
		hDC=GetDC(NULL);
		fSystemDC=TRUE;
		}

	iXppli=GetDeviceCaps (hDC, LOGPIXELSX);
	iYppli=GetDeviceCaps (hDC, LOGPIXELSY);

	//We got pixel units, convert them to logical HIMETRIC along the display
	prcHiMetric->right=MAP_PIX_TO_LOGHIM(iXextInPix, iXppli);
	prcHiMetric->top  =MAP_PIX_TO_LOGHIM(iYextInPix, iYppli);

	prcHiMetric->left   =0;
	prcHiMetric->bottom =0;

	if (fSystemDC)
		ReleaseDC(NULL, hDC);

	return;
	}



STDAPI_(void) XformRectInHimetricToPixels(HDC hDC, LPRECT prcHiMetric
	, LPRECT prcPix)
	{
	int     iXppli;     //Pixels per logical inch along width
	int     iYppli;     //Pixels per logical inch along height
	int     iXextInHiMetric=(prcHiMetric->right-prcHiMetric->left);
	int     iYextInHiMetric=(prcHiMetric->bottom-prcHiMetric->top);
	BOOL    fSystemDC=FALSE;

	if (NULL==hDC || GetDeviceCaps(hDC, LOGPIXELSX) == 0)
		{
		hDC=GetDC(NULL);
		fSystemDC=TRUE;
		}

	iXppli=GetDeviceCaps (hDC, LOGPIXELSX);
	iYppli=GetDeviceCaps (hDC, LOGPIXELSY);

	//We got pixel units, convert them to logical HIMETRIC along the display
	prcPix->right=MAP_LOGHIM_TO_PIX(iXextInHiMetric, iXppli);
	prcPix->top  =MAP_LOGHIM_TO_PIX(iYextInHiMetric, iYppli);

	prcPix->left =0;
	prcPix->bottom= 0;

	if (fSystemDC)
		ReleaseDC(NULL, hDC);

	return;
	}




/*
 * XformSizeInPixelsToHimetric
 * XformSizeInHimetricToPixels
 *
 * Functions to convert a SIZEL structure (Size functions) or
 * an int (Width functions) between a device coordinate system and
 * logical HiMetric units.
 *
 * Parameters:
 *  hDC             HDC providing reference to the pixel mapping.  If
 *                  NULL, a screen DC is used.
 *  pSizeInPix      LPSIZEL containing the size to convert.
 *  pSizeInHiMetric
 *
 * NOTE:
 *  When displaying on the screen, Window apps display everything enlarged
 *  from its actual size so that it is easier to read. For example, if an
 *  app wants to display a 1in. horizontal line, that when printed is
 *  actually a 1in. line on the printed page, then it will display the line
 *  on the screen physically larger than 1in. This is described as a line
 *  that is "logically" 1in. along the display width. Windows maintains as
 *  part of the device-specific information about a given display device:
 *      LOGPIXELSX -- no. of pixels per logical in along the display width
 *      LOGPIXELSY -- no. of pixels per logical in along the display height
 *
 *  The following formula converts a distance in pixels into its equivalent
 *  logical HIMETRIC units:
 *
 *      DistInHiMetric=(HIMETRIC_PER_INCH * DistInPix)
 *                       -------------------------------
 *                           PIXELS_PER_LOGICAL_IN
 *
 */

STDAPI_(void) XformSizeInPixelsToHimetric(HDC hDC, LPSIZEL pSizeInPix
	, LPSIZEL pSizeInHiMetric)
	{
	int     iXppli;     //Pixels per logical inch along width
	int     iYppli;     //Pixels per logical inch along height
	BOOL    fSystemDC=FALSE;

	if (NULL==hDC || GetDeviceCaps(hDC, LOGPIXELSX) == 0)
		{
		hDC=GetDC(NULL);
		fSystemDC=TRUE;
		}

	iXppli=GetDeviceCaps (hDC, LOGPIXELSX);
	iYppli=GetDeviceCaps (hDC, LOGPIXELSY);

	//We got pixel units, convert them to logical HIMETRIC along the display
	pSizeInHiMetric->cx=(long)MAP_PIX_TO_LOGHIM((int)pSizeInPix->cx, iXppli);
	pSizeInHiMetric->cy=(long)MAP_PIX_TO_LOGHIM((int)pSizeInPix->cy, iYppli);

	if (fSystemDC)
		ReleaseDC(NULL, hDC);

	return;
	}


STDAPI_(void) XformSizeInHimetricToPixels(HDC hDC, LPSIZEL pSizeInHiMetric
	, LPSIZEL pSizeInPix)
	{
	int     iXppli;     //Pixels per logical inch along width
	int     iYppli;     //Pixels per logical inch along height
	BOOL    fSystemDC=FALSE;

	if (NULL==hDC || GetDeviceCaps(hDC, LOGPIXELSX) == 0)
		{
		hDC=GetDC(NULL);
		fSystemDC=TRUE;
		}

	iXppli=GetDeviceCaps (hDC, LOGPIXELSX);
	iYppli=GetDeviceCaps (hDC, LOGPIXELSY);

	//We got logical HIMETRIC along the display, convert them to pixel units
	pSizeInPix->cx=(long)MAP_LOGHIM_TO_PIX((int)pSizeInHiMetric->cx, iXppli);
	pSizeInPix->cy=(long)MAP_LOGHIM_TO_PIX((int)pSizeInHiMetric->cy, iYppli);

	if (fSystemDC)
		ReleaseDC(NULL, hDC);

	return;
	}
