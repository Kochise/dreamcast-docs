/*
**-----------------------------------------------------------------------------
** Name:    dxprint.c
** Purpose: print's DX Tree View info to selected printer
** Notes:
**-----------------------------------------------------------------------------
*/

/*
**-----------------------------------------------------------------------------
** Includes
**-----------------------------------------------------------------------------
*/
#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>
#include <commctrl.h>
#include <commdlg.h>        // Common Print Dialog
#include <tchar.h>          // Unicode string functions and types

#include <ddraw.h>
#include <dsound.h>
#include <dplay.h>
#include <d3d.h>
#include "dxview.h"


/*
**-----------------------------------------------------------------------------
** Local Variables
**-----------------------------------------------------------------------------
*/

BOOL g_fAbortPrint      = FALSE;       // Did User Abort Print operation ?!?
HWND g_hAbortPrintDlg   = NULL;        // Print Abort Dialog handle
BOOL g_PrintToFile      = FALSE;       // Don't print to printer print to dxview.log
HANDLE g_FileHandle     = NULL;        // Handle to log file
                                        
/*
**-----------------------------------------------------------------------------
** Local Prototypes
**-----------------------------------------------------------------------------
*/

BOOL CALLBACK PrintTreeStats(
    HINSTANCE   hInstance,
    HWND        hWindow,
    HWND        hTreeWnd,
    HTREEITEM   hRoot);

void DoMessage (DWORD dwTitle, DWORD dwMsg);


/*
**-----------------------------------------------------------------------------
** Functions
**-----------------------------------------------------------------------------
*/

/*
**-----------------------------------------------------------------------------
** Name:    DXView_OnPrint
** Purpose: Print user defined stuff
**-----------------------------------------------------------------------------
*/

BOOL DXView_OnPrint (
    HWND hWindow, 
    HWND hTreeWnd,
    BOOL fPrintAll)
{
    HINSTANCE hInstance;
    HTREEITEM hRoot;

    // Check Parameters
    if ((! hWindow) || (! hTreeWnd))
    {
        // Invalid parameters
        return FALSE;
    }

    // Get hInstance
    hInstance = (HINSTANCE)GetWindowLong (hWindow, GWL_HINSTANCE);
    if (! hInstance)
        return FALSE;

    if (fPrintAll)
    {
        hRoot = NULL;
    }
    else
    {
        hRoot = TreeView_GetSelection (hTreeWnd);
        if (! hRoot)
        {
            DoMessage (IDS_PRINT_WARNING, IDS_PRINT_NEEDSELECT);
        }
    }
    g_PrintToFile = FALSE;
    // Do actual printing
    return PrintTreeStats (hInstance, hWindow, hTreeWnd, hRoot);

} // End DXView_OnPrint

BOOL DXView_OnFile (
    HWND hWindow, 
    HWND hTreeWnd,
    BOOL fPrintAll)
{
    HINSTANCE hInstance;
    HTREEITEM hRoot;

    // Check Parameters
    if ((! hWindow) || (! hTreeWnd))
    {
        // Invalid parameters
        return FALSE;
    }

    // Get hInstance
    hInstance = (HINSTANCE)GetWindowLong (hWindow, GWL_HINSTANCE);
    if (! hInstance)
        return FALSE;

    if (fPrintAll)
    {
        hRoot = NULL;
    }
    else
    {
        hRoot = TreeView_GetSelection (hTreeWnd);
        if (! hRoot)
        {
            DoMessage (IDS_PRINT_WARNING, IDS_PRINT_NEEDSELECT);
        }
    }
    g_PrintToFile = TRUE;
    // Do actual printing
    return PrintTreeStats (hInstance, hWindow, hTreeWnd, hRoot);

} // End DXView_OnPrint



/*
**-----------------------------------------------------------------------------
** Name:    PrintDialogProc
** Purpose: Dialog procedure for printing
**-----------------------------------------------------------------------------
*/

BOOL CALLBACK PrintDialogProc (
    HWND    hDialog,
    UINT    uiMsg,
    WPARAM  wParam,
    LPARAM  lParam)
{
    switch (uiMsg)
    {
    case WM_INITDIALOG:
        {
        // Disable system menu on dialog
        HMENU hSysMenu = GetSystemMenu (hDialog, FALSE);
        EnableMenuItem (hSysMenu, SC_CLOSE, MF_GRAYED);
        }
        return TRUE;

    case WM_COMMAND:
        {
        // User is aborting print operation
        g_fAbortPrint = TRUE;
        EnableWindow (GetParent (hDialog), TRUE);
        DestroyWindow (hDialog);
        g_hAbortPrintDlg = NULL;
        }
        return TRUE;
    } // End switch

    return FALSE;
} // End PrintDialogProc



/*
**-----------------------------------------------------------------------------
** Name:    AbortProc
** Purpose: Abort procedure for printing
**-----------------------------------------------------------------------------
*/

BOOL CALLBACK AbortProc (HDC hPrinterDC, int iCode)
{
    MSG msg;

    while (! g_fAbortPrint && PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
    {
        if ((! g_hAbortPrintDlg) || ! IsDialogMessage (g_hAbortPrintDlg, &msg))
        {
            TranslateMessage (&msg);
            DispatchMessage (&msg);
        }
    }

    return !g_fAbortPrint;
} // End AbortProc


/*
**-----------------------------------------------------------------------------
** Name:    PrintStats
** Purpose: Print user defined stuff
**-----------------------------------------------------------------------------
*/

BOOL CALLBACK PrintTreeStats(
    HINSTANCE   hInstance,
    HWND        hWindow,
    HWND        hTreeWnd,
    HTREEITEM   hRoot)
{
    static DOCINFO  di;
    static PRINTDLG pd;

    BOOL        fDone           = FALSE;
    BOOL        fFindNext       = FALSE;
    BOOL        fResult         = FALSE;
    BOOL        fStartDoc       = FALSE;
    BOOL        fDisableWindow  = FALSE;
    LPTSTR      pstrTitle       = NULL;
    LPTSTR      pstrBuff        = NULL;
    TEXTMETRIC  tm;
    DWORD       dwCurrCopy;
    HANDLE      hHeap;
    DWORD       cbSize;
    DWORD       cchLen;
    TV_ITEM     tvi;
    HTREEITEM   hStartTree, hTempTree;
    PRINTCBINFO pci;

    // Check Parameters
    if ((! hInstance) || (! hWindow) || (! hTreeWnd))
    {
        // Error, invalid parameters
        return FALSE;
    }

    // Get Starting point for tree
    if (hRoot)
        hStartTree = hRoot;
    else
        hStartTree = TreeView_GetRoot (hTreeWnd);
    if (! hStartTree)
    {
        // Error, invalid tree
        return FALSE;
    }
    
    // Initialize Print Dialog structure
    pd.lStructSize          = sizeof (PRINTDLG);
    pd.hwndOwner            = hWindow;
    pd.hDevMode             = NULL;
    pd.hDevNames            = NULL;
    pd.hDC                  = NULL;
    pd.Flags                = PD_ALLPAGES | PD_RETURNDC;
    pd.nFromPage            = 0;
    pd.nToPage              = 0;
    pd.nMinPage             = 0;
    pd.nMaxPage             = 0;
    pd.nCopies              = 1;
    pd.hInstance            = NULL;
    pd.lCustData            = 0L;
    pd.lpfnPrintHook        = NULL;
    pd.lpfnSetupHook        = NULL;
    pd.lpPrintTemplateName  = NULL;
    pd.lpSetupTemplateName  = NULL;
    pd.hPrintTemplate       = NULL;
    pd.hSetupTemplate       = NULL;

    if(g_PrintToFile)
    {
        pci.hdcPrint = NULL;
    }else
    {
        // Call Common Print Dialog to get printer DC
        if ((! PrintDlg (&pd)) || (! pd.hDC))
        {
            // Error, Print Dialog failed or user canceled
            return TRUE;
        }
        pci.hdcPrint = pd.hDC;
        // Get Text metrics for printing
        if (! GetTextMetrics (pci.hdcPrint, &tm))
        {
            // Error, TextMetrics failed
            goto lblCLEANUP;
        }
    }
    if(g_PrintToFile)
    {
        pci.dwLineHeight   = 1;
        pci.dwCharWidth    = 1;
        pci.dwCharsPerLine = 80;
        pci.dwLinesPerPage = 66;
    }else
    {
        pci.dwLineHeight   = tm.tmHeight + tm.tmExternalLeading;
        pci.dwCharWidth    = tm.tmAveCharWidth;
        pci.dwCharsPerLine = GetDeviceCaps (pci.hdcPrint, HORZRES) / pci.dwCharWidth;
        pci.dwLinesPerPage = GetDeviceCaps (pci.hdcPrint, VERTRES) / pci.dwLineHeight;
    }
 
    // Get Heap
    hHeap = GetProcessHeap ();
    if (! hHeap)
    {
        // Error, no heap associated with this process
        goto lblCLEANUP;
    }

    // Create line buffer
    cbSize = (pci.dwCharsPerLine + 1) * sizeof(TCHAR);
    pstrBuff = (LPTSTR) HeapAlloc (hHeap, HEAP_NO_SERIALIZE, cbSize);
    if (! pstrBuff)
    {
        // Error, not enough memory 
        goto lblCLEANUP;
    }

    // Disable Parent window
    EnableWindow (hWindow, FALSE);
    fDisableWindow = TRUE;

    // Start Printer Abort Dialog
    g_fAbortPrint = FALSE;
    g_hAbortPrintDlg = CreateDialog (hInstance, MAKEINTRESOURCE (IDD_ABORTPRINTDLG),
                                     hWindow, (DLGPROC)PrintDialogProc);
    if (! g_hAbortPrintDlg)
    {
        // Error, unable to create abort dialog
        goto lblCLEANUP;
    }

    //
    // Set Document title to Root string
    //
    tvi.mask            = TVIF_CHILDREN | TVIF_TEXT;
    tvi.hItem           = hStartTree;
    tvi.pszText         = pstrBuff;
    tvi.cchTextMax      = pci.dwCharsPerLine;
    if (TreeView_GetItem (hTreeWnd, &tvi))
    {
        SetWindowText (g_hAbortPrintDlg, pstrBuff);
        SetAbortProc (pd.hDC, AbortProc);
        cchLen = _tcsclen (pstrBuff);
        cbSize = (cchLen + 1) * sizeof(TCHAR);
        pstrTitle = (LPTSTR) HeapAlloc (hHeap, HEAP_NO_SERIALIZE, cbSize);
        if (! pstrTitle)
        {
            // Error, not enough memory 
            goto lblCLEANUP;
        }

        _tcsncpy (pstrTitle, pstrBuff, cchLen);
        pstrTitle[cchLen] = 0;
    }
    else
    {
        SetWindowText (g_hAbortPrintDlg, TEXT("Unknown"));
        SetAbortProc (pd.hDC, AbortProc);
        cchLen = _tcsclen (TEXT("Unknown"));
        cbSize = (cchLen + 1) * sizeof(TCHAR);
        pstrTitle = (LPTSTR) HeapAlloc (hHeap, HEAP_NO_SERIALIZE, cbSize);
        if (! pstrTitle)
        {
            // Error, not enough memory 
            goto lblCLEANUP;
        }

        _tcsncpy (pstrTitle, TEXT("Unknown"), cchLen);
        pstrTitle[cchLen] = 0;
    }

    // Initialize Document Structure
    di.cbSize       = sizeof(DOCINFO);
    di.lpszDocName  = pstrTitle; 
    di.lpszOutput   = NULL; 
    di.lpszDatatype = NULL;
    di.fwType       = 0;

    // Start document
    if(g_PrintToFile)
    {
        g_FileHandle = CreateFile("dxview.log",GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
    } else
    if (StartDoc (pd.hDC, &di) < 0)
    {
        // Error, StartDoc failed
        goto lblCLEANUP;
    }
    fStartDoc = TRUE;

    // Print requested number of copies
    fResult = FALSE;
    for (dwCurrCopy = 0; dwCurrCopy < (DWORD)pd.nCopies; dwCurrCopy++)
    {

        pci.hCurrTree       = hStartTree;
        pci.fStartPage      = TRUE;
        pci.dwCurrIndent    = 0;


        // Note:  We are basically doing an pre-order traversal
        //        of the Tree.  Printing the current node
        //        before moving on to it's children or siblings

        fDone               = FALSE;
        while (! fDone)
        {
            // Check if we need to start a new page
            if (! PrintStartPage (&pci))
            {
                goto lblCLEANUP;
            }

            //
            // Get Current Item in Tree 
            // and print it's text info and associated Node caps
            //

            tvi.mask            = TVIF_CHILDREN | TVIF_TEXT | TVIF_PARAM;
            tvi.hItem           = pci.hCurrTree;
            tvi.pszText         = pstrBuff;
            tvi.lParam          = 0;
            tvi.cchTextMax      = pci.dwCharsPerLine;
            if (TreeView_GetItem (hTreeWnd, &tvi))
            {
                cchLen = _tcslen (pstrBuff);
                if (cchLen > 0)
                {
                    int xOffset = (int)(pci.dwCurrIndent * DEF_TAB_SIZE * pci.dwCharWidth);
                    int yOffset = (int)(pci.dwLineHeight * pci.dwCurrLine);

                    // Print this line
                    if (! PrintLine (xOffset, yOffset, pstrBuff, cchLen, &pci))
                    {
                        goto lblCLEANUP;
                    }
    
                    // Advance to next line in page
                    if (! PrintNextLine (&pci))
                    {
                        goto lblCLEANUP;
                    }

                    // Check if there is any additional node info 
                    // that needs to be printed
                    if (tvi.lParam != 0)
                    {
                        NODEINFO * pni = (NODEINFO*)tvi.lParam;
                    
                        if (pni && pni->printCallback)
                        {                            
                            // Force indent to offset node info from tree info
                            pci.dwCurrIndent += 2;

                            if (! pni->printCallback(pni->lParam1, pni->lParam2, &pci))
                            {
                                // Error, callback failed
                                goto lblCLEANUP;
                            }

                            // Recover indent
                            pci.dwCurrIndent -= 2;
                        }
                    }
                }
            } // End if TreeView_GetItem()

            
            
            // 
            // Get Next Item in tree
            //

            // Get first child, if any
            if (tvi.cChildren)
            {
                // Get First child
                hTempTree = TreeView_GetChild (hTreeWnd, pci.hCurrTree);
                if (hTempTree)
                {
                    // Increase Indentation
                    pci.dwCurrIndent++;

                    pci.hCurrTree = hTempTree;
                    continue;
                }
            }
            
            // Exit, if we are the root
            if (pci.hCurrTree == hRoot)
            {
                // We have reached the root, so stop
                PrintEndPage (&pci);
                fDone = TRUE;
                continue;
            }

            // Get next sibling in the chain
            hTempTree = TreeView_GetNextSibling (hTreeWnd, pci.hCurrTree);
            if (hTempTree)
            {
                pci.hCurrTree = hTempTree;
                continue;
            }

            // Get next Ancestor yet to be processed
            // (uncle, granduncle, etc)
            fFindNext = FALSE;
            while (! fFindNext)
            {
                hTempTree = TreeView_GetParent (hTreeWnd, pci.hCurrTree);
                if ((! hTempTree) || (hTempTree == hRoot))
                {
                    // We have reached the root, so stop
                    PrintEndPage (&pci);
                    fDone       = TRUE;
                    fFindNext   = TRUE;
                }
                else
                {
                    // Move up to the parent
                    pci.hCurrTree = hTempTree;

                    // Decrease Indentation
                    pci.dwCurrIndent--;

                    // Since we have already processed the parent 
                    // we want to get the uncle/aunt node
                    hTempTree = TreeView_GetNextSibling (hTreeWnd, pci.hCurrTree);
                    if (hTempTree)
                    {
                        // Found a non-processed node
                        pci.hCurrTree = hTempTree;
                        fFindNext = TRUE;
                    }
                }
            }
        } // End While (! fDone)
    } // End for num copies

    // Success
    fResult = TRUE;

lblCLEANUP:    
    // End Document
    if (fStartDoc)
    {
        if(g_PrintToFile)
        {
            CloseHandle(g_FileHandle);
        } else
        EndDoc (pd.hDC);
        fStartDoc = FALSE;
    }

    // Re-enable main window
    // Note:  Do this before destroying abort dialog
    //        otherwise the main window loses focus
    if (fDisableWindow)
    {
        EnableWindow (hWindow, TRUE);
        fDisableWindow = FALSE;
    }

    // Destroy Abort Dialog
    if (g_hAbortPrintDlg)
    {
        DestroyWindow (g_hAbortPrintDlg);
        g_hAbortPrintDlg = NULL;
    }

    // Free title memory
    if (pstrTitle)
    {
        HeapFree (hHeap, 0, (LPVOID)pstrTitle);
        pstrTitle       = NULL;
        di.lpszDocName  = NULL; 
    }

    // Free buffer memory
    if (pstrBuff)
    {
        HeapFree (hHeap, 0, (LPVOID)pstrBuff);
        pstrBuff = NULL;
    }

    // Cleanup printer DC
    if (pd.hDC)
    {
        DeleteDC (pd.hDC);
        pd.hDC = NULL;
    }

    // Return success/failure
    return fResult;
} // End PrintTreeStats



/*
**-----------------------------------------------------------------------------
** Name:    PrintStartPage
** Purpose: check if we need to start a new page
**-----------------------------------------------------------------------------
*/

BOOL PrintStartPage (PRINTCBINFO * pci)
{
    if(g_PrintToFile)
        return TRUE;
    if (! pci)
        return FALSE;

    // Check if we need to start a new page
    if (pci->fStartPage)
    {
        // Check for user abort
        if (g_fAbortPrint)
        {
            // Error, user canceled printing job
            return FALSE;
        } 

        // Start new page
        if (StartPage (pci->hdcPrint) < 0)
        {
            // Error, StartPage failed
            return FALSE;
        }

        // Reset line count
        pci->fStartPage = FALSE;
        pci->dwCurrLine = 0;
    }

    // Success
    return TRUE;
} // End PrintStartPage


  
/*
**-----------------------------------------------------------------------------
** Name:    PrintEndPage
** Purpose: check if we need to start a new page
**-----------------------------------------------------------------------------
*/

BOOL PrintEndPage (PRINTCBINFO * pci)
{
    if(g_PrintToFile)
        return TRUE;
    if (! pci)
        return FALSE;

    // Check if we need to end this page
    if (! pci->fStartPage)
    {
        // End page
        if (EndPage (pci->hdcPrint) < 0)
        {
            // Error, end page failed
            return FALSE;
        }
        pci->fStartPage = TRUE;

        // Check for user abort
        if (g_fAbortPrint)
        {
            // Error, user canceled printing job
            return FALSE;
        } 
    }

    // Success
    return TRUE;
} // End PrintEndPage


  
/*
**-----------------------------------------------------------------------------
** Name:    PrintLine
** Purpose: Prints text to page at specified location
**-----------------------------------------------------------------------------
*/
static DWORD iLastXPos;

BOOL PrintLine (
    int xOffset,
    int yOffset,
    LPCTSTR pszBuff,
    DWORD  cchBuff,
    PRINTCBINFO * pci)
{
    if (! pci)
    {
        // Programming error
        return FALSE;
    }

    // Check if we need to start a new page
    if (! PrintStartPage (pci))
        return FALSE;

    if ((! pszBuff) || (! cchBuff))
    {
        // Nothing to print
        // assume it's OK and just keep printing
        return TRUE;
    }

    // Print text out to buffer current line
    if(g_PrintToFile)
    {
        DWORD Foobar;
        TCHAR Temp[80];

        if(((xOffset-iLastXPos)/pci->dwCharWidth)>80)
            return TRUE;
        memset(Temp,' ',sizeof(TCHAR)*79);
        Temp[(xOffset-iLastXPos)/pci->dwCharWidth]=0;
        WriteFile(g_FileHandle,Temp,(xOffset-iLastXPos)/pci->dwCharWidth,&Foobar,NULL);
        iLastXPos = (xOffset-iLastXPos)+(pci->dwCharWidth * cchBuff);
            
        WriteFile(g_FileHandle,pszBuff,cchBuff,&Foobar,NULL);
    }else
    {
        TextOut (pci->hdcPrint, xOffset, yOffset, pszBuff, cchBuff);
    };

    return TRUE;
} // End PrintLine
    


/*
**-----------------------------------------------------------------------------
** Name:    PrintNextLine
** Purpose: advance to next line on page
**-----------------------------------------------------------------------------
*/

BOOL PrintNextLine (PRINTCBINFO * pci)
{

    if(g_PrintToFile)
    {
        DWORD Foobar;

        WriteFile(g_FileHandle,"\r\n",2,&Foobar,NULL);
        iLastXPos = 0;
        return TRUE;
    };
    if (! pci)
        return FALSE;

    pci->dwCurrLine++;

    // Check if we need to end the page
    if (pci->dwCurrLine >= pci->dwLinesPerPage)
    {
        return PrintEndPage (pci);
    }

    // Success
    return TRUE;
} // End PrintNextLine



/*
**-----------------------------------------------------------------------------
** Name:    DoMessage
** Purpose: display warning message to user
**-----------------------------------------------------------------------------
*/

#define MAX_TITLE   64
#define MAX_MESSAGE 256

void DoMessage (DWORD dwTitle, DWORD dwMsg)
{
    TCHAR szTitle[MAX_TITLE];
    TCHAR szMsg[MAX_MESSAGE];
    HMODULE hModule;

    hModule = GetModuleHandle (NULL);

    LoadString (hModule, dwTitle, szTitle, MAX_TITLE);
    LoadString (hModule, dwMsg, szMsg, MAX_MESSAGE);
    MessageBox (NULL, szMsg, szTitle, MB_OK);
} // End DoMessage
  

/*
**-----------------------------------------------------------------------------
** End of File
**-----------------------------------------------------------------------------
*/
