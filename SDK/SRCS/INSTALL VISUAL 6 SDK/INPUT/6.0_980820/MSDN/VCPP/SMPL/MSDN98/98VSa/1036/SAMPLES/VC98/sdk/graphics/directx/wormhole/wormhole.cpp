/***************************************************************************
 *  Copyright (C) 1995-1997 Microsoft Corporation. All Rights Reserved.
 ***************************************************************************/
#include <windows.h>
#include <ddraw.h>

HWND            hWnd;
PALETTEENTRY    pe[256];
BOOL            bActive;                                            
BOOL            bIsInitialized=FALSE;

LPDIRECTDRAW            lpDD = NULL;           
LPDIRECTDRAWSURFACE     lpDDSPrimary = NULL;   
LPDIRECTDRAWSURFACE     lpDDSOne = NULL;       
LPDIRECTDRAWCLIPPER     lpClipper = NULL;      
LPDIRECTDRAWPALETTE     lpDDPal = NULL;        

BOOL restoreAll();
void updateFrame();
static void finiObjects();
long FAR PASCAL WindowProc(HWND,UINT,WPARAM,LPARAM);
BOOL initFail(HWND);
static BOOL doInit(HINSTANCE, int);
void CyclePalette();
BOOL readBMPIntoSurfaces();
int PASCAL WinMain(HINSTANCE,HINSTANCE,LPSTR,int);

BOOL restoreAll()
{
    BOOL bResult;

    bResult=lpDDSPrimary->Restore() == DD_OK &&
            lpDDSOne->Restore()     == DD_OK;

    readBMPIntoSurfaces();

    return(bResult);
} 

void updateFrame()
{
    RECT                rcRect;
    RECT                destRect;
    HRESULT             ddrval;
    POINT               pt;

    rcRect.left=0;
    rcRect.top=0;
    rcRect.right=640;
    rcRect.bottom=480;

    GetClientRect(hWnd,&destRect);

    pt.x=pt.y=0;
    ClientToScreen(hWnd,&pt);
    OffsetRect(&destRect,pt.x,pt.y);

    while(1)
    {
        ddrval=lpDDSPrimary->Blt(&destRect,lpDDSOne,&rcRect,0,NULL);

        if(ddrval==DD_OK)
        {
            break;
        }
        if(ddrval==DDERR_SURFACELOST)
        {
            if(!restoreAll())
            {
                return;
            }
            continue;
        }
        if(ddrval!=DDERR_WASSTILLDRAWING)
        {
            return;
        }
    }
} 

static void finiObjects()
{
    if(lpDD!=NULL)
    {
        if(lpDDSPrimary!=NULL)
        {
            lpDDSPrimary->Release();
            lpDDSPrimary=NULL;
        }
        if(lpDDSOne!=NULL)
        {
            lpDDSOne->Release();
            lpDDSOne=NULL;
        }
        if(lpDDPal!=NULL)
        {
            lpDDPal->Release();
            lpDDPal=NULL;
        }
        lpDD->Release();
        lpDD=NULL;
    }
} 

long FAR PASCAL WindowProc(HWND hWnd,UINT message, 
                           WPARAM wParam,LPARAM lParam )
{
    switch(message)
    {
        case WM_ACTIVATE:
            bActive = wParam;
            break;

        case WM_CREATE:

            break;

        case WM_SETCURSOR:

            SetCursor(NULL);
	    if( bIsInitialized )
	    {
                updateFrame();
                lpDDPal->GetEntries(0,0,256,pe);
	    }
            break;

        case WM_KEYDOWN:

            switch(wParam)
            {
                case VK_ESCAPE:
                
                case VK_F12:
                    
                    PostMessage(hWnd,WM_CLOSE,0,0);
                    break;
            }
            break;
  
        case WM_DESTROY:

            finiObjects();
            PostQuitMessage(0);
            break;
    }
    return DefWindowProc(hWnd,message,wParam,lParam);
} 

BOOL initFail(HWND hWnd)
{
    finiObjects();
    MessageBox(hWnd,"DirectDraw Init FAILED","WormHole",MB_OK);
    DestroyWindow(hWnd);
    return FALSE;
} 

static BOOL doInit(HINSTANCE hInstance,int nCmdShow)
{
    WNDCLASS            wc;
    DDSURFACEDESC       ddsd;
    HRESULT             ddrval;

    wc.style=          CS_HREDRAW|CS_VREDRAW;
    wc.lpfnWndProc=    WindowProc;
    wc.cbClsExtra=     0;
    wc.cbWndExtra=     0;
    wc.hInstance=      hInstance;
    wc.hIcon=          LoadIcon(hInstance,IDI_APPLICATION);
    wc.hCursor=        LoadCursor(NULL,IDC_ARROW);
    wc.hbrBackground=  NULL;
    wc.lpszMenuName=   NULL;
    wc.lpszClassName=  "WormHole";
    RegisterClass(&wc);
    
    hWnd=CreateWindowEx(
        0,
        "WormHole",
        "WormHole",
        WS_POPUP,
        0,
        0,
        GetSystemMetrics(SM_CXSCREEN),
        GetSystemMetrics(SM_CYSCREEN),
        NULL,
        NULL,
        hInstance,
        NULL );

    if(!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd,nCmdShow);
    UpdateWindow(hWnd);

    ddrval=DirectDrawCreate(NULL,&lpDD,NULL);

    if(ddrval!=DD_OK)
    {
        return initFail(hWnd);
    }

    ddrval=lpDD->SetCooperativeLevel(hWnd,DDSCL_EXCLUSIVE|DDSCL_FULLSCREEN);
    ddrval=lpDD->SetDisplayMode(640,480,8);

    if(ddrval!=DD_OK)
    {
        return initFail(hWnd);
    }

    ddsd.dwSize=sizeof(ddsd);
    ddsd.dwFlags=DDSD_CAPS;
    ddsd.ddsCaps.dwCaps=DDSCAPS_PRIMARYSURFACE;

    ddrval=lpDD->CreateSurface(&ddsd,&lpDDSPrimary,NULL);

    if(ddrval!=DD_OK)
    {
        return initFail(hWnd);
    }

    ddsd.dwSize=sizeof(ddsd);
    ddsd.dwFlags=DDSD_CAPS|DDSD_HEIGHT|DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps=DDSCAPS_OFFSCREENPLAIN;
    ddsd.dwWidth=640;
    ddsd.dwHeight=480;

    lpDD->CreateSurface(&ddsd,&lpDDSOne,NULL);    
    if(lpDDSOne==NULL)
    {
        return initFail(hWnd);
    }

    bIsInitialized = TRUE;
    return TRUE;
} 

void CyclePalette()
{
    int                 reg[15];
    int                 k;
       
    for(k=0;k<15;k++)
    {
        reg[k]=pe[k+30].peRed;
    }
    for(k=45;k<255;k++)
    {                                                            
        pe[k-15].peRed=pe[k].peRed;
    }
    for(k=0;k<15;k++)
    {
        pe[k+240].peRed=reg[k];
    }
    for(k=0;k<15;k++)
    {
        reg[k]=pe[k+30].peGreen;
    }
    for(k=45;k<255;k++)
    {
        pe[k-15].peGreen=pe[k].peGreen;
    }
    for(k=0;k<15;k++)
    {
        pe[k+240].peGreen=reg[k];
    }
    for(k=0;k<15;k++)
    {
        reg[k]=pe[k+30].peBlue;
    }
    for(k=45;k<255;k++)
    {
        pe[k-15].peBlue=pe[k].peBlue;
    }
    for(k=0;k<15;k++)
    {
        pe[k+240].peBlue=reg[k];
    }

    for(k=2;k<17;k++)
    {
        reg[k-2]=pe[15*k+14].peRed;
        pe[15*k+14].peRed=pe[15*k+13].peRed;
        pe[15*k+13].peRed=pe[15*k+12].peRed;
        pe[15*k+12].peRed=pe[15*k+11].peRed;
        pe[15*k+11].peRed=pe[15*k+10].peRed;
        pe[15*k+10].peRed=pe[15*k+9].peRed;
        pe[15*k+9].peRed=pe[15*k+8].peRed;
        pe[15*k+8].peRed=pe[15*k+7].peRed;
        pe[15*k+7].peRed=pe[15*k+6].peRed;
        pe[15*k+6].peRed=pe[15*k+5].peRed;
        pe[15*k+5].peRed=pe[15*k+4].peRed;
        pe[15*k+4].peRed=pe[15*k+3].peRed;
        pe[15*k+3].peRed=pe[15*k+2].peRed;
        pe[15*k+2].peRed=pe[15*k+1].peRed;
        pe[15*k+1].peRed=pe[15*k].peRed;
        pe[15*k].peRed=reg[k-2];
        reg[k-2]=pe[15*k+14].peGreen;
        pe[15*k+14].peGreen=pe[15*k+13].peGreen;
        pe[15*k+13].peGreen=pe[15*k+12].peGreen;
        pe[15*k+12].peGreen=pe[15*k+11].peGreen;
        pe[15*k+11].peGreen=pe[15*k+10].peGreen;
        pe[15*k+10].peGreen=pe[15*k+9].peGreen;
        pe[15*k+9].peGreen=pe[15*k+8].peGreen;
        pe[15*k+8].peGreen=pe[15*k+7].peGreen;
        pe[15*k+7].peGreen=pe[15*k+6].peGreen;
        pe[15*k+6].peGreen=pe[15*k+5].peGreen;
        pe[15*k+5].peGreen=pe[15*k+4].peGreen;
        pe[15*k+4].peGreen=pe[15*k+3].peGreen;
        pe[15*k+3].peGreen=pe[15*k+2].peGreen;
        pe[15*k+2].peGreen=pe[15*k+1].peGreen;
        pe[15*k+1].peGreen=pe[15*k].peGreen;
        pe[15*k].peGreen=reg[k-2];
        reg[k-2]=pe[15*k+14].peBlue;
        pe[15*k+14].peBlue=pe[15*k+13].peBlue;
        pe[15*k+13].peBlue=pe[15*k+12].peBlue;
        pe[15*k+12].peBlue=pe[15*k+11].peBlue;
        pe[15*k+11].peBlue=pe[15*k+10].peBlue;
        pe[15*k+10].peBlue=pe[15*k+9].peBlue;
        pe[15*k+9].peBlue=pe[15*k+8].peBlue;
        pe[15*k+8].peBlue=pe[15*k+7].peBlue;
        pe[15*k+7].peBlue=pe[15*k+6].peBlue;
        pe[15*k+6].peBlue=pe[15*k+5].peBlue;
        pe[15*k+5].peBlue=pe[15*k+4].peBlue;
        pe[15*k+4].peBlue=pe[15*k+3].peBlue;
        pe[15*k+3].peBlue=pe[15*k+2].peBlue;
        pe[15*k+2].peBlue=pe[15*k+1].peBlue;
        pe[15*k+1].peBlue=pe[15*k].peBlue;
        pe[15*k].peBlue=reg[k-2];
    }
            
    lpDD->WaitForVerticalBlank(DDWAITVB_BLOCKBEGIN,NULL);

    if(lpDDPal->SetEntries(0,0,256,pe)!=DD_OK)
    {
        return;
    }
}

BOOL readBMPIntoSurfaces()
{
    HRESULT             ddrval;
    HRSRC               hBMP;
    RGBQUAD             Palette[256];
    PALETTEENTRY        pe[256];
    DDSURFACEDESC       DDSDesc;
    LPSTR               lpBits;
    LPSTR               lpSrc;
    BYTE                *lpBMP;
    int                 i;

    hBMP=FindResource(NULL,"wormhole_bmp",RT_BITMAP);    
    if( hBMP == NULL )
    {
        return FALSE;
    }

    lpBMP=(BYTE *)LockResource(LoadResource(NULL, hBMP));
    
    memcpy(Palette,&lpBMP[sizeof(BITMAPINFOHEADER)],sizeof(Palette));

    FreeResource(hBMP);

    for(i=0;i<256;i++)
    {
        pe[i].peRed=Palette[i].rgbRed;
        pe[i].peGreen=Palette[i].rgbGreen;
        pe[i].peBlue=Palette[i].rgbBlue;
    }   

    if (NULL == lpDDPal) {

      ddrval=lpDD->CreatePalette(DDPCAPS_8BIT,pe,&lpDDPal,NULL);

      if(ddrval!=DD_OK)
      {
          return FALSE;
      }
    }

    lpDDSPrimary->SetPalette(lpDDPal);

    DDSDesc.dwSize=sizeof(DDSDesc);
    ddrval=lpDDSOne->Lock(NULL,&DDSDesc,0,NULL);
    if(ddrval!=DD_OK)
    {
        return FALSE;
    }

    lpBits=(LPSTR)DDSDesc.lpSurface;
    lpSrc=(LPSTR)
          (&lpBMP[sizeof(BITMAPINFOHEADER)+sizeof(Palette)+(640*480)]);
    for(i=0;i<480;i++)
    {
        memcpy(lpBits,lpSrc,640);
        lpBits+=DDSDesc.lPitch;
        lpSrc-=640;
    }
    lpDDSOne->Unlock(NULL);

    return TRUE;
}

int PASCAL WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,int nCmdShow)
{
    MSG         msg;

    if(!doInit(hInstance,nCmdShow))
    {
        return FALSE;
    }

    readBMPIntoSurfaces();    
    updateFrame();

    while(1)
    {
        if(PeekMessage(&msg,NULL,0,0,PM_NOREMOVE))
        {
            if(!GetMessage(&msg,NULL,0,0))
            {
                return msg.wParam;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else if(bActive)
        {
            CyclePalette();
        }
        else
        {
            WaitMessage();
        }
    }
} 
