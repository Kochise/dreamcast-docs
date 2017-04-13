//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                  Copyright Microsoft Corp. 1992-1996
//                      Remote Machine WinTyp sample
//
// FILE     :   client.h
//
// PURPOSE  :   Definitions and function prototypes used on client side
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//------------------------------------------------------------------------
//      Global variables used on the client side
//------------------------------------------------------------------------
HWND        g_hWnd;                 // Handle to the window
HINSTANCE   g_hInstance;            // Handle to the instance
LPTSTR      g_szClassName =         // The class name on client side
        TEXT("ClientClassName");	
LPTSTR      g_szWindowCaption =     // The caption shown in the window
        TEXT("WinTyp RPC sample program -- Client side");	
BITMAP      g_Bitmap;               // A bitmap structure
HBITMAP     g_hBitmap;              // Handle to the bitmap stucture
HPALETTE    g_hPalette;             // A handle to the palette used
BOOL        BITMAP_READ = FALSE;    // Indicates if bitmap is read
BOOL        EDGE_FOUND = FALSE;     // Indicates if edges is found
BOOL        g_bBound = FALSE;       // Indicates is binding has been done
TCHAR       g_szFileName[100];      // Name of file with bitmap
UINT        g_BitsPerPixel;         // Number of bits per pixel


//------------------------------------------------------------------------
//      Function prototyping 
//------------------------------------------------------------------------
int WINAPI          WinMain (HINSTANCE, HINSTANCE, LPSTR, int);
LRESULT CALLBACK    ClientProc(HWND, UINT, WPARAM, LPARAM);
BOOL                Init(void);
BOOL CALLBACK       AboutDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK       BindingDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL                GetBitmapFileName(void);
void                RedrawClientArea(HDC);
BOOL                ReadBitmapFromFile(void);
void                CleanUp();
HPALETTE            LoadPaletteFromFile(LPTSTR lpszFileName);
RPC_STATUS          Bind(HWND hWnd);



//------------------------------------------------------------------------
//      Variables used for finding the binding with the server
//      Since the variables uses definitions from the COMMON.H file
//      remember to include "common.h" before this file
//------------------------------------------------------------------------
RPC_STATUS      status;
_TUCHAR         *pszUuid                    = NULL;
_TUCHAR         pszProtocolSequence[100];    
_TUCHAR         pszNetworkAddress[100];      
_TUCHAR         pszEndpoint[100];            
_TUCHAR         *pszOptions                 = NULL;
_TUCHAR         *pszStringBinding           = NULL;
