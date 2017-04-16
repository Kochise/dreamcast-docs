/****************************************************************************

    NAME       : EZPRINT.DLL

    PURPOSE    : This DLL provides printing functionality such as placement of text,
    		     lines and rectangles with various attributes.  For those desiring
    		     more sophisticated functionality, EZPRINT provides a framework upon
    		     which to build those extended capabilities.
    		  
    COMMENTS   : this dll was designed with VB in mind.  This means that
	             long pointers cannot be passed in structures.

*******************************************************************************/

#include <windows.h>
#include <windowsx.h>
#include <memory.h>
#include <commdlg.h>
#include "ezprint.h"

/****************************************************************************

    FUNCTION   : PrintObject

    PURPOSE    : Entry point for printing objects.  Calls PrintObjectIndirect.
               	
    RETURNS    : int

    MESSAGES   : none
    
    COMMENTS   : Copies the parameters into global memory for later use.

****************************************************************************/

int FAR PASCAL _export PrintObject(LPPRINTSTRUCT lpPS)
{
  int	iRet;
    //save the parameters in global memory for use later when painting
    //alloc and check the validity of this memory first because the structure
    //must always be passed in.	
  lpPStruct = (LPPRINTSTRUCT)GlobalAllocPtr(GHND, sizeof(PRINTSTRUCT));

  if (lpPStruct != NULL)
    _fmemcpy(lpPStruct, lpPS, sizeof(PRINTSTRUCT));
  else
    return(FALSE);
    
  iRet = PrintObjectIndirect(lpPStruct);
    //clean up
  GlobalFreePtr(lpPStruct);     
  
  return(iRet);
}

/****************************************************************************

    FUNCTION   : PrintObjectIndirect

    PARAMETERS : LPPRINTSTRUCT lpPStruct

    PURPOSE    : Handle printing of various objects (ie: text, lines, rects). 

    RETURNS    : void

    MESSAGES   : none

    COMMENTS   :

****************************************************************************/

int PrintObjectIndirect(LPPRINTSTRUCT lpPStruct)
{

  static int saveContext;

  switch (lpPStruct->nPrintObject)  {

    case PO_TEXT:
	{
	    LOGFONT	      lf;
	    HFONT	      hOldFont, hFont;
	    int		      saveContext;
	    RECT	      rc;
	    HBRUSH	      hOldBrush, hBrush;
	    UINT	      fuFormat = DT_NOPREFIX;
	    POINT	      ptPO;

	      //initialize the rect structure
	    rc.left   = lpPStruct->nXOrg;
	    rc.top    = lpPStruct->nYOrg;
	    rc.right  = lpPStruct->nXExt;
	    rc.bottom = lpPStruct->nYExt;

	      //convert logical coordinates to device coordinates
	    LPtoDP(pd.hDC, (LPPOINT)&rc, 2);

	      //save the dc and change map mode to MM_TEXT.  Much
	      //easier to work with fonts in this mode.
	    saveContext = SaveDC(pd.hDC);

	    SetMapMode(pd.hDC, MM_TEXT);

	      //create the font based on lpPStruct
	    lf.lfHeight = -MulDiv(lpPStruct->nPointSize,
				  GetDeviceCaps(pd.hDC, LOGPIXELSY), 72);
	    lf.lfWidth = 0;
	    lf.lfEscapement = 0;
	    lf.lfOrientation = 0;
	    lf.lfWeight = (lpPStruct->uiTextFlags & TEXT_BOLD) ? FW_BOLD : FW_NORMAL;
	    lf.lfItalic = (lpPStruct->uiTextFlags & TEXT_ITALIC) ? 1 : 0;
	    lf.lfUnderline = (lpPStruct->uiTextFlags & TEXT_UNDERLINED) ? 1 : 0;
	    lf.lfStrikeOut = (lpPStruct->uiTextFlags & TEXT_STRIKEOUT) ? 1 : 0;
	    lf.lfCharSet = ANSI_CHARSET;
	    lf.lfOutPrecision = OUT_STROKE_PRECIS;
	    lf.lfClipPrecision = CLIP_STROKE_PRECIS;
	    lf.lfQuality = DRAFT_QUALITY;
	    lf.lfPitchAndFamily = VARIABLE_PITCH | FF_SWISS;
	    lstrcpy((LPSTR)lf.lfFaceName, (LPSTR)"Arial");

	    hFont = CreateFontIndirect(&lf);

	    hOldFont = SelectObject(pd.hDC, hFont);


	      //set the alignment flags in the format bitfield
	    fuFormat |= (lpPStruct->uiTextFlags & TEXT_CENTER) ? DT_CENTER :
			(lpPStruct->uiTextFlags & TEXT_RIGHT)  ? DT_RIGHT  :
			 DT_LEFT;

	      //expand tabs if indicated
	    if (lpPStruct->uiTextFlags & TEXT_EXPANDTABS)
		fuFormat |=  DT_EXPANDTABS;

	      //set text clipping
	    if (lpPStruct->uiTextFlags & TEXT_NOCLIP)
		fuFormat |=  DT_NOCLIP;

	      //if this is a single line then set alignment to bottom
	    if (lpPStruct->uiTextFlags & TEXT_SINGLELINE)
		fuFormat |=  DT_SINGLELINE;
	    else
		fuFormat |=  DT_WORDBREAK;

	      //if the extents of rect haven't been specified then
	      //calculate them
	    if (lpPStruct->nXExt == 0 && lpPStruct->nYExt == 0)
		DrawText(pd.hDC, (LPSTR)lpPStruct->szText, -1,
			 &rc, fuFormat | DT_CALCRECT);

	      //adjust for the printing offset.	when the DPtoLP transform
	      //occurs the printing offset is erroneously calculated into
	      //the transform
	    Escape(pd.hDC, GETPRINTINGOFFSET, NULL, NULL, (LPSTR)(LPPOINT)&ptPO);

	    rc.left   -= ptPO.x;
	    rc.top    -= ptPO.y;
	    rc.right  -= ptPO.x;
	    rc.bottom -= ptPO.y;

	      //now draw the text
	    DrawText(pd.hDC, (LPSTR)lpPStruct->szText, -1,
		     &rc, fuFormat);

	    if (lpPStruct->uiTextFlags & TEXT_RECT)  {

	      hBrush = GetStockObject((lpPStruct->uiFillFlags & FILL_GRAY)   ? GRAY_BRUSH   :
				      (lpPStruct->uiFillFlags & FILL_LTGRAY) ? LTGRAY_BRUSH :
				      (lpPStruct->uiFillFlags & FILL_DKGRAY) ? DKGRAY_BRUSH :
				      (lpPStruct->uiFillFlags & FILL_BLACK)  ? BLACK_BRUSH  : HOLLOW_BRUSH);

	      hOldBrush = SelectObject(pd.hDC, hBrush);

	      Rectangle(pd.hDC, rc.left, rc.top, rc.right, rc.bottom);
	    }

	      //this line spacing is based on the logical size of the page.
	      //it seems a bit bogus...you know, not getting the text metrics
	      //but it is right on.  The next line is 2 * the height.  remember
	      //that we are setting the alignment to the bottom of the bounding
	      //rectangle.
	    uiLineSpacing = 2 * lpPStruct->nPointSize;

	    if (lpPStruct->uiTextFlags & TEXT_RECT)
	      DeleteObject(SelectObject(pd.hDC, hOldBrush));

	    DeleteObject(SelectObject(pd.hDC, hOldFont));

	    if (saveContext)
		RestoreDC(pd.hDC, -1);

	}
	return (uiLineSpacing);
	break;

    case PO_RECT:
	{
	    HPEN   hOldPen, hPen;
	    HBRUSH hOldBrush, hBrush;
	    POINT  lpPT[4];

	    hBrush = GetStockObject((lpPStruct->uiFillFlags & FILL_GRAY)   ? GRAY_BRUSH   :
				    (lpPStruct->uiFillFlags & FILL_LTGRAY) ? LTGRAY_BRUSH :
				    (lpPStruct->uiFillFlags & FILL_DKGRAY) ? DKGRAY_BRUSH :
				    (lpPStruct->uiFillFlags & FILL_BLACK)  ? BLACK_BRUSH  : HOLLOW_BRUSH);

	    hOldBrush = SelectObject(pd.hDC, hBrush);

	    hPen = CreatePen((lpPStruct->uiPenFlags & PEN_DASH) ? PS_DASH  :
			     (lpPStruct->uiPenFlags & PEN_DOT)	? PS_DOT   : PS_SOLID,
			     0, BLACK);

	    hOldPen = SelectObject(pd.hDC, hPen);

	    lpPT[0].x = lpPStruct->nXOrg;
	    lpPT[0].y = lpPStruct->nYOrg;
	    lpPT[1].x = lpPStruct->nXExt;
	    lpPT[1].y = lpPStruct->nYOrg;
	    lpPT[2].x = lpPStruct->nXExt;
	    lpPT[2].y = lpPStruct->nYExt;
	    lpPT[3].x = lpPStruct->nXOrg;
	    lpPT[3].y = lpPStruct->nYExt;

	    Polygon(pd.hDC, lpPT, sizeof(lpPT) / sizeof(POINT));

	    DeleteObject(SelectObject(pd.hDC, hOldPen));
	    DeleteObject(SelectObject(pd.hDC, hOldBrush));
	}
	return(1);
	break;

    case PO_GRID:
	  //this is intended for design purposes only.	It is inefficient
	  //in its use of moveto/lineto combinations.  In fact, it may fail should
	  //your printer not have enough memory!
	{

	    HPEN hOldPen, hPen;
	    int  i;

	    hPen = CreatePen(PS_SOLID, 0, BLACK);

	    hOldPen = SelectObject(pd.hDC, hPen);

	    for (i = 0; i < XEXT; i++)	{
	      if (!(i % 10))  {
		MoveTo(pd.hDC, i, 0);
		LineTo(pd.hDC, i, YEXT);
	      }
	    }

	    for (i = 0; i < YEXT; i++)	{
	      if (!(i % 10))  {
		MoveTo(pd.hDC, 0, i);
		LineTo(pd.hDC, XEXT, i);
	      }
	    }

	    DeleteObject(SelectObject(pd.hDC, hOldPen));

	      //draw the wide line along the X and Y midpoints
	    hPen = CreatePen(PS_SOLID, 2, BLACK);

	    hOldPen = SelectObject(pd.hDC, hPen);

	    MoveTo(pd.hDC, 500, 0);
	    LineTo(pd.hDC, 500, YEXT);

	    MoveTo(pd.hDC, 0, 500);
	    LineTo(pd.hDC, XEXT, 500);

	    DeleteObject(SelectObject(pd.hDC, hOldPen));

	}
	return(1);
	break;

    case PO_LINE:
	{
	    HPEN  hOldPen, hPen;
	    POINT pt[2];
	    int   nPenStyle;
	    int   nLineWidth;

	    nPenStyle = (lpPStruct->uiPenFlags & PEN_DASH)	 ? PS_DASH	 :
			(lpPStruct->uiPenFlags & PEN_DOT)	 ? PS_DOT	 :
			(lpPStruct->uiPenFlags & PEN_DASHDOT)	 ? PS_DASHDOT	 :
			(lpPStruct->uiPenFlags & PEN_DASHDOTDOT) ? PS_DASHDOTDOT :
			 PS_SOLID;


	    nLineWidth = (lpPStruct->uiPenFlags & PEN_THICK) ? 2 : 0;

	    hPen = CreatePen(nPenStyle, nLineWidth, BLACK);
	    
        pt[0].x = lpPStruct->nXOrg;
        pt[0].y = lpPStruct->nYOrg;
        pt[1].x = lpPStruct->nXExt;
        pt[1].y = lpPStruct->nYExt;
        
	    hOldPen = SelectObject(pd.hDC, hPen);                   
	    
        Polyline(pd.hDC, pt, sizeof(pt) / sizeof(POINT));
        
	    DeleteObject(SelectObject(pd.hDC, hOldPen));
	}
	return(1);
	break;

    case PO_NEWPAGE:
	Escape(pd.hDC, NEWFRAME, 0, NULL, NULL);
	return(1);

    default:
	return(1);
  }

}


/****************************************************************************

    FUNCTION   : StartDocument

    PARAMETERS : void

    PURPOSE    : init the printer, obtain a DC and STARTDOC

    CALLS      :

    RETURNS    : BOOL - FALSE if called more than once before calling EndDocument
			            FALSE if unable to get DC
			            TRUE if DC obtained and bPDInit == FALSE

    MESSAGES   : none

    COMMENTS   : this is called prior to starting a document.  It must not
		         be called after the document has started.  It must be
		         matched with an EndDocument().  This uses COMMDLG.DLL

****************************************************************************/

BOOL FAR PASCAL _export StartDocument(HWND hWnd, BOOL bEnablePrintDialog)
{

  POINT ptPO;
  DOCINFO di;  
   
  int cbBuffer = PRTJOBNAME;
  char szDocName[PRTJOBNAME];

  if (bPDInit == TRUE)
    return (FALSE);

    //Set all structure members to zero.
  memset(&pd, 0, sizeof(PRINTDLG));

    //Initialize the necessary PRINTDLG structure members.                
  pd.lStructSize = sizeof(PRINTDLG);

  if (!bEnablePrintDialog)
      //send it to the printer without bringing up print dialog
    pd.Flags = PD_RETURNDC | PD_RETURNDEFAULT;
  else
      //set the flags to enable the print dialog box
    pd.Flags = PD_RETURNDC | PD_HIDEPRINTTOFILE | PD_NOPAGENUMS | PD_NOSELECTION;

  if (PrintDlg(&pd) != 0)  {

    bAbort = FALSE;

    hDlgAbort = CreateDialog(hInst, "PRINTDLG", hWnd, PrintAbortDlg);
    ShowWindow(hDlgAbort, SW_NORMAL);
    EnableWindow(hWnd, FALSE);                                                                             
    
      //if you want this to work in Windows 3.0 you should use the SETABORTPROC escape 
      //versus the 3.1 SetAbortProc function
    if (SetAbortProc(pd.hDC, PrintAbortProc) < 0)
    {
      char szSAPFailure[PRTJOBNAME];
    
      LoadString(hInst, IDS_SAP_FAILED, szSAPFailure, cbBuffer);
 	  MessageBox(NULL, (LPSTR)szSAPFailure, NULL, MB_ICONSTOP | MB_OK);

	  DeleteDC(pd.hDC);

	  if (pd.hDevMode != NULL)
	    GlobalFree(pd.hDevMode);

	  if (pd.hDevNames != NULL)
	    GlobalFree(pd.hDevNames);

	  bPDInit = FALSE;

	  return FALSE;
    }


    ptPO.x = 0;
    ptPO.y = 0;

    Escape(pd.hDC, GETPRINTINGOFFSET, NULL, NULL, (LPSTR)(LPPOINT)&ptPO);

    bPDInit = TRUE;
    Page.LogPage.x = GetDeviceCaps (pd.hDC, HORZRES);
    Page.LogPage.y = GetDeviceCaps (pd.hDC, VERTRES);

    Page.VOx = 0 + ptPO.x;
    Page.VOy = 0 + ptPO.y;
    Page.VEx = Page.LogPage.x - (2 * ptPO.x);
    Page.VEy = Page.LogPage.y - (2 * ptPO.y);


    SetMapMode	   (pd.hDC, MM_ANISOTROPIC );
    SetWindowOrg   (pd.hDC, 0, 0 );
    SetWindowExt   (pd.hDC, XEXT, YEXT );
    SetViewportOrg (pd.hDC, Page.VOx, Page.VOy );
    SetViewportExt (pd.hDC, Page.VEx, Page.VEy );
    
     if (!LoadString(hInst, IDS_PRTMGR_DOCNAME, szDocName, cbBuffer))
        lstrcpy((LPSTR)szDocName, (LPSTR)"Sample Report");
     di.lpszDocName = (LPSTR)szDocName;
     di.lpszOutput  = NULL;
     di.cbSize = sizeof(DOCINFO);
                    

     if (StartDoc(pd.hDC, &di) == SP_ERROR)
     {                                                                                         
      char szSDFailure[PRTJOBNAME];
      
      LoadString(hInst, IDS_SD_FAILED, szSDFailure, cbBuffer);
	  MessageBox(NULL,(LPSTR)szSDFailure, NULL,
                    MB_APPLMODAL|MB_ICONSTOP|MB_OK);

	  DeleteDC(pd.hDC);

	  if (pd.hDevMode != NULL)
	    GlobalFree(pd.hDevMode);

	  if (pd.hDevNames != NULL)
	    GlobalFree(pd.hDevNames);

	  bPDInit = FALSE;
	  return FALSE;
    }

    return (TRUE);
  }
  else	{
    bPDInit = FALSE;
    return (FALSE);
  }
}

/****************************************************************************

    FUNCTION   : EndDocument

    PARAMETERS : void

    PURPOSE    : end the document, nuke the DC and clean up the memory

    RETURNS    : BOOL - FALSE if invalid DC
			            FALSE if ENDDOC fails
			            FALSE if DeleteDC fails
			            TRUE if success

    MESSAGES   : none
    
    COMMENTS   : this is called after calling StartDocument.  

****************************************************************************/

BOOL FAR PASCAL _export EndDocument(HWND hWnd)
{

    //did we ever call StartDocument?  If not then fail.
  if (bPDInit == FALSE)
    return (FALSE);

    //eject the page
  if (!Escape(pd.hDC, NEWFRAME, 0, NULL, NULL))
    return (FALSE);

    //end the document
  if (EndDoc(pd.hDC) < 0)
    return (FALSE);

  EnableWindow(hWnd, TRUE);

    //get rid of abort dialog
  DestroyWindow(hDlgAbort);

    //clean up
  if (!DeleteDC(pd.hDC))
    return (FALSE);

  if (pd.hDevMode != NULL)
     GlobalFree(pd.hDevMode);

  if (pd.hDevNames != NULL)
     GlobalFree(pd.hDevNames);

  bPDInit = FALSE;

  return (TRUE);

}

/****************************************************************************

    FUNCTION   : PrintAbortProc

    PARAMETERS : HDC hDC
	             short code

    PURPOSE    : Function is used to give application some "multi-tasking"
	             through the use of a PeekMessage().  Also, it gives the
	             application some error control during printing.

    RETURNS    : BOOL - TRUE if user aborts printing procedure

    MESSAGES   : none

    COMMENTS   :

****************************************************************************/

BOOL FAR PASCAL _export PrintAbortProc (HDC hDC, short code)
{
   MSG msg;

   while (!bAbort && PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
      if (!IsDialogMessage(hDlgAbort, &msg))  {
         TranslateMessage(&msg);
         DispatchMessage(&msg);
      }
   return (!bAbort);
}

/****************************************************************************

    FUNCTION   : PrintAbortDlg

    PARAMETERS : HWND hWnd
                 unsigned msg
                 WORD wParam
                 LONG lParam

    PURPOSE    : Dialog procedure for print abort dialog.

    RETURNS    : int

    MESSAGES   : none

    COMMENTS   :

****************************************************************************/

int FAR PASCAL _export PrintAbortDlg (HWND hDlg, unsigned msg, WORD wParam, LONG lParam)
{
   RECT rc;

   switch (msg)
      {
      case WM_INITDIALOG:
	   //center the dialog on the screen
	 GetWindowRect(hDlg, &rc);
	 SetWindowPos(hDlg, NULL,
	      (GetSystemMetrics(SM_CXSCREEN) - (rc.right - rc.left)) /2,
	      (GetSystemMetrics(SM_CYSCREEN) - (rc.bottom - rc.top)) /3,
	      0, 0, SWP_NOSIZE | SWP_NOACTIVATE);
	   //set the button focus to the cancel button
	 SetFocus(GetDlgItem(hDlg, IDCANCEL));
         return TRUE;

      case WM_COMMAND:
	   //set the global "we've aborted the print job" flag
	 bAbort = TRUE;
         return TRUE;
      }

   return FALSE;
}
