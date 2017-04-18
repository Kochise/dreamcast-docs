// COpenGL.h : header file
//
// COpenGL class
//

#ifndef __WGL__
#define __WGL__

class COpenGL : public CObject
{

public://functions
	HGLRC                  m_hglrc;
	HDC                    m_hdc;
    int                    m_maxpfd;
    PIXELFORMATDESCRIPTOR  m_PixFmtDesc;
    //
	//constructor
	//
	COpenGL(HDC hdc = NULL, PIXELFORMATDESCRIPTOR *pfd = NULL);
	//
	//destructor
	//
    ~COpenGL();
	//
	//utility functions
	//
	void  Init(PIXELFORMATDESCRIPTOR *pfd);
    BOOL  GetGLRC(HDC hdc);
	BOOL  ReleaseGLRC(HWND hwnd);
    BOOL  SetupPixelFormat(HDC hdc, PIXELFORMATDESCRIPTOR *pPFD);
	int   GetCurPFDIndex();
    int   GetMaxPFIndex(HDC hdc);
	BOOL  IsNativeIndex(HDC hdc, int nIdx);
	BOOL  IsDeviceIndex(HDC hdc, int idx);
	BOOL  IsSurfaceInitialized() {return m_fIsInitialized;}
	void  SetSurfaceInitialized() {m_fIsInitialized = TRUE;}
	//
	//class wrappers for win32 pix format and buffering api
	//and WGL functions
	//
    int   ChoosePixelFormat(HDC hdc, PIXELFORMATDESCRIPTOR *ppfd);
    int   DescribePixelFormat(HDC hdc, int iPixelFormat, 
                              UINT nBytes, 
                              PIXELFORMATDESCRIPTOR *ppfd);
    int   GetPixelFormat(HDC hdc);
    BOOL  SetPixelFormat(HDC hdc, int iPixelFormat, PIXELFORMATDESCRIPTOR *ppfd);
    BOOL  SwapBuffers(HDC hdc);
    HGLRC wglCreateContext(HDC hdc);
    BOOL  wglDeleteContext(HGLRC hglrc);
    HGLRC wglGetCurrentContext(void);
    HDC   wglGetCurrentDC(void);
    BOOL  wglMakeCurrent(HDC hdc, HGLRC hglrc);
    BOOL  wglUseFontBitmaps(HDC hdc, DWORD first, DWORD count, DWORD listbase);


private://data
	BOOL m_fIsInitialized;
    static unsigned char   m_oneto8[2];
    static unsigned char   m_twoto8[4];
    static unsigned char   m_threeto8[8];
    static int             m_defaultOverride[13];
    static PALETTEENTRY    m_defaultPalEntry[20];

    void  CreateRGBPalette(HDC hDC);
    UCHAR ComponentFromIndex(int i, UINT nbits, UINT shift);

};					   

#endif // __WGL__
