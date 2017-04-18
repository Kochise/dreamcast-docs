#include "exeview.h"
#include "pefile.h"

#define BYTE_WIN_WIDTH	    77
#define CLINESSHOW   8
#define ABS(x) ((x) < 0? -(x) : (x))

/* externally defined system constants */
extern int		    xChar,
			    yChar,
			    xScreen,
			    yScreen,
			    yFrame,
			    xFrame,
			    yCaption,
			    xVScrollBar;
extern HFONT hFont;
extern HWND  hMemWnd;

void	WINAPI VScrollBytes (HWND, int, int, LPMEMVIEW);
void	WINAPI KeyToScrollMsg (HWND, WPARAM);
void	WINAPI DisplayBytes (HDC, LPRECT, LPMEMVIEW);
void	WINAPI GetBytesLine (LPBYTE, UINT, DWORD, int, char *);


/* function creates a window for viewing memory */
void  WINAPI ViewExe (
    HWND      hWndParent,
    char      *lpszExeName)
{
    LPMEMVIEW	 pmv;
    char	 szClass[MAX_PATH];
    char	 szError[MAX_PATH];
    char	 szTitle[MAX_PATH];
    char	 szFilename[MAX_PATH];
    OFSTRUCT	 of;
    HWND	 hWnd;
    IMAGE_SECTION_HEADER	   sh;
    IMAGE_OPTIONAL_HEADER	   oh;
    IMAGE_FILE_HEADER		   fh;
    IMAGE_SEPARATE_DEBUG_HEADER    dh;
    char			   *szTest;


    /* allocate local memory for memory view structure */
    pmv = (LPMEMVIEW)LocalAlloc (LPTR, sizeof (MEMVIEW));

    /* open exe file */
    if (!(pmv->hFile = (HANDLE)OpenFile (lpszExeName, &of, OF_READ)))
	{
	LoadString (GetModuleHandle (NULL), IDS_CANTOPENFILE, szError, MAX_PATH);
	GetFileFromPath (lpszExeName, szFilename);
	strcat (szError, szFilename);
	LoadString (GetModuleHandle (NULL), IDS_ERROR, szTitle, MAX_PATH);
	MessageBox (NULL, szError, szTitle, MB_OK);
	return;
	}

    /* map view of exe file */
    if ((pmv->hMMFile = CreateFileMapping (pmv->hFile,
					  NULL,
					  PAGE_READONLY,
					  0,
					  0,
					  NULL)) != NULL)
	{
	pmv->lpMem = MapViewOfFile (pmv->hMMFile, FILE_MAP_READ, 0, 0, 0);
	if (pmv->lpMem == NULL)
	    {
	    LoadString (GetModuleHandle (NULL), IDS_CANTMAPVIEW, szError, MAX_PATH);
	    GetFileFromPath (lpszExeName, szFilename);
	    strcat (szError, szFilename);
	    LoadString (GetModuleHandle (NULL), IDS_ERROR, szTitle, MAX_PATH);
	    MessageBox (NULL, szError, szTitle, MB_OK);
	    return;
	    }
	}
    else
	{
	LoadString (GetModuleHandle (NULL), IDS_CANTCREATEMAPPING, szError, MAX_PATH);
	GetFileFromPath (lpszExeName, szFilename);
	strcat (szError, szFilename);
	LoadString (GetModuleHandle (NULL), IDS_ERROR, szTitle, MAX_PATH);
	MessageBox (NULL, szError, szTitle, MB_OK);
	return;
	}

    pmv->nSize = GetFileSize (pmv->hFile, NULL);
    pmv->nBase = 0;


    /* create caption that identifies file type */
    switch (ImageFileType (pmv->lpMem))
	{
	case IMAGE_NT_SIGNATURE:
	    LoadString (GetModuleHandle (NULL), IDS_NTFILESIGNATURE, szTitle, MAX_PATH);
	    break;

	case IMAGE_OS2_SIGNATURE:
	    LoadString (GetModuleHandle (NULL), IDS_OS2FILESIGNATURE, szTitle, MAX_PATH);
	    break;

	case IMAGE_OS2_SIGNATURE_LE:
	    LoadString (GetModuleHandle (NULL), IDS_OS2FILESIGNATURELE, szTitle, MAX_PATH);
	    break;

	case IMAGE_DOS_SIGNATURE:
	    LoadString (GetModuleHandle (NULL), IDS_DOSFILESIGNATURE, szTitle, MAX_PATH);
	    break;

	default:
	    LoadString (GetModuleHandle (NULL), IDS_UNKNOWNFILESIGNATURE, szTitle, MAX_PATH);
	    break;
	}
    GetFileFromPath (lpszExeName, szFilename);
    strcat (szTitle, szFilename);



/* test code */

if (IsDebugFile (pmv->lpMem))
    GetSeparateDebugHeader (pmv->lpMem, &dh);
else
    {
    GetPEFileHeader (pmv->lpMem, &fh);
    GetPEOptionalHeader (pmv->lpMem, &oh);
    GetSectionHdrByName (pmv->lpMem, &sh, ".edata");
    GetSectionHdrByName (pmv->lpMem, &sh, ".idata");
    GetExportFunctionNames (pmv->lpMem, GetProcessHeap (), &szTest);
    GetNumberOfExportedFunctions (pmv->lpMem);
    GetExportFunctionEntryPoints (pmv->lpMem);
    GetExportFunctionOrdinals (pmv->lpMem);
    GetImportModuleNames (pmv->lpMem, GetProcessHeap (), &szTest);
    GetImportFunctionNamesByModule (pmv->lpMem, GetProcessHeap (), "GDI32.dll", &szTest);
    GetSectionNames (pmv->lpMem, GetProcessHeap (), &szTest);
    GetNumberOfResources(pmv->lpMem);
    GetListOfResourceTypes (pmv->lpMem, GetProcessHeap (), &szTest);
    ImageDirectoryOffset (pmv->lpMem, IMAGE_DIRECTORY_ENTRY_DEBUG);
    }
IsDebugInfoStripped (pmv->lpMem);
RetrieveModuleName (pmv->lpMem, GetProcessHeap (), &szTest);


    /* load resource strings for window class  */
    LoadString (GetModuleHandle (NULL), IDS_MEMVIEWCLASS, szClass, MAX_PATH);

    /* create memory view window */
    hWnd = CreateWindow (szClass,
			 szTitle,
			 WS_POPUPWINDOW | WS_VISIBLE | WS_CAPTION |
			 WS_VSCROLL | WS_THICKFRAME | WS_MAXIMIZEBOX,
			 0,
			 0,
			 BYTE_WIN_WIDTH * xChar + xVScrollBar + 2*xFrame,
			 yScreen/2,
			 hWndParent,
			 NULL,
			 GetModuleHandle (NULL),
			 (LPVOID)pmv);

    UpdateWindow (hWnd);
    ShowWindow (hWnd, SW_SHOWNORMAL);
}



LONG WINAPI MemWndProc (
    HWND      hWnd,
    UINT      uMsg,
    WPARAM    wParam,
    LPARAM    lParam)
{
    LONG       lRet = 1;
    MEMVIEW    *pmv = (LPMEMVIEW)GetWindowLong (hWnd, WXB_LPMEMVIEW);

    
    switch (uMsg)
	{
	case WM_CREATE:
	    pmv = (LPMEMVIEW)((LPCREATESTRUCT)lParam)->lpCreateParams;
	    SetWindowLong (hWnd, WXB_LPMEMVIEW, (LONG)pmv);

	    pmv->nLines = (pmv->nSize+15)/16;
	    pmv->nExtraBytes = (pmv->nSize & 0x0000000F);
	    pmv->PosV = 0;

	    /* reposition window with proper x,y positions */
	    MoveWindow (hWnd,
			15,
			15,
			((LPCREATESTRUCT)lParam)->cx,
			((LPCREATESTRUCT)lParam)->cy,
			TRUE);
            break;

	case WM_SIZE:
	    pmv->xWin = LOWORD (lParam);
	    pmv->yWin = HIWORD (lParam);

	    pmv->RangeV = pmv->nLines-pmv->yWin/yChar;

	    if (pmv->RangeV < 0)
		pmv->RangeV = 0;

	    if (pmv->PosV > pmv->RangeV)
		pmv->PosV = pmv->RangeV;

	    SetScrollRange (hWnd, SB_VERT, 0, pmv->RangeV, FALSE);
	    SetScrollPos (hWnd, SB_VERT, pmv->PosV, TRUE);
            break;

	case WM_PAINT:
	    {
	    PAINTSTRUCT    ps;

	    BeginPaint (hWnd, &ps);
	    DisplayBytes (ps.hdc,
			  &(ps.rcPaint),
			  pmv);
	    EndPaint (hWnd, &ps);
	    }
            break;

        case WM_KEYDOWN:
	    KeyToScrollMsg (hWnd, wParam);
            break;

        case WM_VSCROLL:
	    VScrollBytes (hWnd, LOWORD (wParam), GetScrollPos (hWnd, SB_VERT), pmv);
            break;

	case WM_DESTROY:
	    {
	    LPMEMVIEW	 lpmv;

	    /* free virtual memory block  and local memory buffer */
	    VirtualFree (pmv->lpMem, 0, MEM_RELEASE);
	    LocalFree ((HANDLE)pmv);

	    /* remove any old view memory */
	    if ((lpmv = (LPMEMVIEW)GetWindowLong (hWnd, WXB_LPMEMVIEW)) != NULL)
		{
		VirtualFree (lpmv->lpMem, 0, MEM_RELEASE);
		LocalFree ((HANDLE)lpmv);
		}
	    }
            break;

        default:
	    return (DefWindowProc(hWnd, uMsg, wParam, lParam));
            break;
	}
    return 0L;
}




void  WINAPI VScrollBytes (
    HWND	 hWnd,
    int 	 cmd,
    int 	 pos,
    LPMEMVIEW	 lpmv)
{
    int    nScrollInc;

    switch (cmd)
	{
        case SB_TOP:
	    nScrollInc = -lpmv->PosV;
            break ;

        case SB_BOTTOM:
	    nScrollInc = lpmv->RangeV - lpmv->PosV;
            break ;

        case SB_LINEUP:
            nScrollInc = -1;
            break;

        case SB_LINEDOWN:
            nScrollInc = 1;
            break;

        case SB_PAGEDOWN:
	    nScrollInc = max (1, lpmv->yWin/yChar);
            break;

        case SB_PAGEUP:
	    nScrollInc = min (-1, -(lpmv->yWin/yChar));
            break;
    
        case SB_THUMBPOSITION:
	    nScrollInc = pos - lpmv->PosV;
            break;

	case SB_THUMBTRACK:
	    nScrollInc = pos - lpmv->PosV;
            break;

        default:
            nScrollInc = 0;
	}

    if (nScrollInc > lpmv->RangeV-lpmv->PosV)
	nScrollInc = lpmv->RangeV-lpmv->PosV;

    if (nScrollInc < -lpmv->PosV)
	nScrollInc = -lpmv->PosV;

    if (nScrollInc)
	{
	lpmv->PosV += nScrollInc;

	if (ABS (nScrollInc) < lpmv->yWin/yChar)
	    ScrollWindow (hWnd, 0, -(yChar*nScrollInc), NULL, NULL);
	else
	    InvalidateRect (hWnd, NULL, TRUE);

	SetScrollPos (hWnd, SB_VERT, lpmv->PosV, TRUE);
	UpdateWindow(hWnd);
	}
}



void  WINAPI KeyToScrollMsg (
    HWND      hWnd,
    WPARAM    wParam)
{
    int       i, nKeys;
    static    struct
	{
        WORD wVirtKey;
        int  iMessage;
        WORD wRequest;
	}key2scroll [] = {
			 VK_HOME,  WM_VSCROLL, SB_TOP,	  VK_END,   WM_VSCROLL,
			 SB_BOTTOM, VK_PRIOR, WM_VSCROLL, SB_PAGEUP, VK_NEXT,
			 WM_VSCROLL, SB_PAGEDOWN, VK_UP,    WM_VSCROLL, SB_LINEUP,
			 VK_DOWN,  WM_VSCROLL, SB_LINEDOWN, VK_LEFT,  WM_HSCROLL,
			 SB_LINEUP, VK_RIGHT, WM_HSCROLL, SB_LINEDOWN,
			 };

    nKeys = sizeof key2scroll / sizeof key2scroll[0];

    for (i=0; i<nKeys; i++)
	{
        if (wParam == key2scroll[i].wVirtKey)   
	    {
            SendMessage (hWnd, key2scroll[i].iMessage, key2scroll[i].wRequest, 0L);
            return;
	    }
	}
}



void  WINAPI DisplayBytes (
    HDC 	 hDC,
    RECT	 *pRect,
    LPMEMVIEW	 lpmv)
{
    UINT      i, iFirst, iLast, y;
    char      szBuf[MAX_PATH];
    LPBYTE    pMem = (LPBYTE)lpmv->lpMem;

    SelectObject (hDC, hFont);
    SetTextColor (hDC, GetSysColor (COLOR_WINDOWTEXT));
    SetBkColor (hDC, GetSysColor (COLOR_WINDOW));

    y = lpmv->PosV;

    iFirst = y + pRect->top/yChar-1;

    if (iFirst == 0xFFFFFFFFL)
	iFirst = 0;

    iLast = min (y + pRect->bottom/yChar+1, (UINT)lpmv->nLines-1);
    pMem += iFirst << 4;

    if (lpmv->nExtraBytes)
        iLast--;

    /* paint complete lines (lines with 16 bytes) */
    y = (iFirst - y) * yChar;
    for (i = iFirst; i<iLast; i++)
	{
	GetBytesLine (pMem, i, lpmv->nBase, 16, szBuf);
	SetTextColor (hDC, GetSysColor(COLOR_WINDOWTEXT));
	TextOut (hDC, xChar, LOWORD (y), szBuf, lstrlen (szBuf));
	pMem += 16;
	y += yChar;
	}

    /* paint last partial line if any (line with less than 16 bytes) */
    if (lpmv->nExtraBytes)
	{
	GetBytesLine (pMem, i, lpmv->nBase, lpmv->nExtraBytes, szBuf);
	SetTextColor (hDC, GetSysColor(COLOR_WINDOWTEXT));
	TextOut(hDC, xChar, y, szBuf, lstrlen (szBuf));
	}

    SelectObject(hDC, GetStockObject(SYSTEM_FONT));
}





void  WINAPI GetBytesLine (
    LPBYTE   pBytes,
    UINT     LineNum,
    DWORD    dwBase,
    int      nBytes,
    char     *szLine)
{
    int 	     j;
    unsigned char    ch;
    char	     szAscii[17];

    wsprintf (szLine, "%#08lx  ", dwBase + (LineNum*16));
        
    for (j = 0; j < nBytes; j++)
	{
	ch = *pBytes++;
	wsprintf (szLine, "%s%02X ", (LPSTR)szLine, (WORD)ch);
        szAscii[j] = ((ch & 0x7F) >= ' ') ? ch : '.';
	}

    szAscii[nBytes] = 0;
    wsprintf(szLine, "%-59s%s", (LPSTR)szLine, (LPSTR)szAscii);
}
