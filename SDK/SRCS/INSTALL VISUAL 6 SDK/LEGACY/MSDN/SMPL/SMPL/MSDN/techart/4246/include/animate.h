// animate.h : header file
//
// @doc
// All classes for animation
//

#ifndef __ANIMATE__
#define __ANIMATE__

#include <mmsystem.h>

/////////////////////////////////////////////////////////////////////////////
// @class CDIB | This class encapsulates a Windows DIB.
// @base public | CObject
// @member GetBitmapInfoAddress | Get a pointer to the BITMAPINFO.
// @member GetBitsAddress | Get a pointer to the bitmap bits.
// @member GetClrTabAddress | Get a pointer to the color table.
// @member GetNumClrEntries | Get the number of entries in the color table.
// @member Create | Create a new CDIB object.
// @member GetPixelAddress | Get the address of a given pixel.
// @member Load | Load the DIB from a file or resource.
// @member Save | Save the DIB to a file.
// @member Draw | Draw the DIB to a CDC object.
// @member GetWidth | Get the width of the image.
// @member GetStorageWidth | Get the memory width of the image (DWORD aligned).
// @member GetHeight | Get the height of the image.
// @member MapColorsToPalette | Map the DIB colors to a given palette.
// @member GetRect | Get the bounding rectangle.
// @member CopyBits | Copy a rectangle to another DIB.
// @member StretchBits | Stretch a rectangle to another DIB.
// @member GetBitsPerPixel | Get the number of bits per pixel.
// @member SetColorTable | Set the color table entries.
/*
@mfunc BITMAPINFO* | CDIB | GetBitmapInfoAddress | Get a pointer to the BITMAPINFO.
@syntax BITMAPINFO* GetBitmapInfoAddress(); 
@rdesc The return value is a pointer to the DIB's BITMAPINFO structure.
@xref <c CDIB>

@mfunc void* | CDIB | GetBitsAddress | Get a pointer to the DIB bits.
@syntax void* GetBitsAddress(); 
@rdesc The return value is a pointer to the DIB's bits.
@xref <c CDIB>

@mfunc RGBQUAD* | CDIB | GetClrTabAddress | Get a pointer to the DIB's
color table.
@syntax RGBQUAD* GetClrTabAddress(); 
@rdesc The return value is a pointer to the DIB's color table.
@xref <c CDIB>

@mfunc int | CDIB | GetWidth | Get the width of the image.
@syntax int GetWidth(); 
@rdesc The return value is width of the DIB in pixels.
@xref <c CDIB>

@mfunc int | CDIB | GetStorageWidth | Get the width of the image in memory.
@syntax int GetStorageWidth(); 
@rdesc The return value is width of a sigle scanline of the DIB in pixels.
@comm DIB scanlines are DWORD aligned so the width in memory is >= the image width. 
@xref <c CDIB>

@mfunc int | CDIB | GetHeight | Get the height of the image.
@syntax int GetHeight(); 
@rdesc The return value is height of the DIB in pixels.
@xref <c CDIB>

@mfunc int | CDIB | GetBitsPerPixel | Get the number of bits used to store
each pixel of the image.
@syntax int GetBitsPerPixel(); 
@rdesc The return value is the number of bits used per pixel.
@xref <c CDIB>

*/

class CDIB : public CObject
{
    DECLARE_SERIAL(CDIB)
public:
    CDIB();
    ~CDIB();

    BITMAPINFO *GetBitmapInfoAddress()
        {return m_pBMI;}                        // ptr to bitmap info
    void *GetBitsAddress()
        {return m_pBits;}                       // ptr to the bits
    RGBQUAD *GetClrTabAddress()
        {return (LPRGBQUAD)(((BYTE *)(m_pBMI)) 
            + sizeof(BITMAPINFOHEADER));}       // ptr to color table
    int GetNumClrEntries();                     // number of color table entries
    BOOL Create(int width, int height, CPalette* pPal = NULL);         // create a new DIB
    BOOL Create(int width, int height, HPALETTE hPal);         // create a new DIB
    BOOL Create(BITMAPINFO* pBMI, BYTE* pBits, BOOL bOwnBits = FALSE); // create from existing mem,
    BOOL Create(BITMAPINFO* pPackedDIB); // create from packed DIB
    void *GetPixelAddress(int x, int y);
    int GetBitsPerPixel()
        {return m_pBMI->bmiHeader.biBitCount;}
    virtual BOOL Load(const char* pszFileName = NULL);// load DIB from disk file
    virtual BOOL Load(CFile* fp);               // load from file
    virtual BOOL Load(WORD wResid);             // load DIB from resource
    virtual BOOL Save(const char* pszFileName = NULL);// save DIB to disk file
    virtual BOOL Save(CFile *fp);               // save to file
    virtual void Serialize(CArchive& ar);
    virtual void Draw(CDC *pDC, int x, int y);
    virtual void Draw(HDC hDC, int x, int y);
    virtual int GetWidth() {return DibWidth();}   // image width
    virtual int GetStorageWidth() {return StorageWidth();}   // memory width
    virtual int GetHeight() {return DibHeight();} // image height
    virtual BOOL MapColorsToPalette(CPalette *pPal);
    virtual BOOL MapColorsToPalette(HPALETTE hPal);
    virtual void GetRect(RECT* pRect);
    virtual void CopyBits(CDIB* pDIB, 
                          int xd, int yd,
                          int w, int h,
                          int xs, int ys,
                          COLORREF clrTrans = 0xFFFFFFFF);
    virtual void StretchBits(CDIB* pDIB, 
                             int xd, int yd,
                             int wd, int hd,
                             int xs, int ys,
                             int ws, int hs,
                             COLORREF clrTrans = 0xFFFFFFFF);
    virtual void DoubleBits(CDIB* pDIB, 
                            int xd, int yd,
                            int xs, int ys,
                            int ws, int hs,
                            COLORREF clrTrans = 0xFFFFFFFF);
    BOOL SetColorTable(CPalette* pPal);

    static BOOL IsWinDIB(BITMAPINFOHEADER* pBIH);
    static int NumDIBColorEntries(BITMAPINFO* pBmpInfo);

protected:
    BITMAPINFO *m_pBMI;         // pointer to BITMAPINFO struct
    BYTE *m_pBits;              // pointer to the bits
    BOOL m_bMyBits;             // TRUE if DIB owns Bits memory

private:
    int DibHeight() 
        {return m_pBMI->bmiHeader.biHeight;}
    int DibWidth()
        {return m_pBMI->bmiHeader.biWidth;}
    int StorageWidth()
        {return (((m_pBMI->bmiHeader.biWidth * m_pBMI->bmiHeader.biBitCount)
                     + 31) & ~31) >> 3;}
};

/////////////////////////////////////////////////////////////////////////////
// @class CDIBPal | This class enhances the CPalette class.
// @base public | CPalette
// @member Create | Create a new palette;
// @member Draw | Draw the palette to a CDC object.
// @member GetNumColors | Get the number of colors in the palette.
// @member SetSysPalColors | Create an identity palette.
// @member Load | Load a palette from a file.
// @member Save | Save the palette to a file.
// @member CreateWash | Create a color cube wash palette.
// @member CreateSystemColorPalette | Create a palette from
//         the 20 system reserved colors.

class CDIBPal : public CPalette
{
public:
    CDIBPal();
    ~CDIBPal();
    BOOL Create(CDIB *pDIB);            // create from a DIB
    BOOL Create(BITMAPINFO* pBMI);      // create from color table
    BOOL Create(RGBQUAD* pRGB, int iClrs); // create from clr table
    void Draw(CDC *pDC, CRect *pRect, BOOL bBkgnd = FALSE); 
    void Draw(HDC hDC, RECT* pRect, BOOL bBkgnd = FALSE); 
    int GetNumColors();                 // get the no. of colors in the pal.
    BOOL SetSysPalColors();
    BOOL Load(const char* pszFileName = NULL);
    BOOL Load(CFile* fp);  
    BOOL Load(UINT hFile);
    BOOL Load(HMMIO hmmio);
    BOOL Save(const char* pszFileName = NULL);
    BOOL Save(CFile* fp);  
    BOOL Save(UINT hFile);
    BOOL Save(HMMIO hmmio);
    BOOL CreateWash();
    BOOL CreateSystemColorPalette();
};

/////////////////////////////////////////////////////////////////////////////
// @class CDIBSurface | This class provides a drawing surface based on
//  a CDIB object which can be drawn to using GDI operations and can also 
//  be manipulated directly. Note that this object requires the target system
// to be Windows NT, Windows 95 or Win 3.1 with Win32s and WinG installed.
// @base public | CDIB
// @member Create | Create a new surface.
// @member GetDC | Get a CDC for the surface.
// @member BitBlt | Blt a section of the surface to a CDC.
// @member StretchBlt | Stretch a section of the surface to a CDC.
// @member Draw | Draw the entire surface to a DC.
// @member SetPalette | Set a new palette.

/*
@mfunc CDC* | CDIBSurface | GetDC | Get a CDC for the surface.
@syntax CDC* GetDC();
@rdesc The return value is a pointer to a CDC object which can be
used for drawing to the surface.
@xref <c CDIBSurface>
*/

// define the WinG functions
#define WINGAPI WINAPI
typedef HDC (WINGAPI WinGCreateDCProc)(void);
typedef HBITMAP (WINGAPI WinGCreateBitmapProc)(HDC WinGDC,
                                                 const BITMAPINFO* pHeader,
                                                 void** ppBits);
typedef UINT (WINGAPI WinGSetDIBColorTableProc)(HDC WinGDC,
                                                 UINT StartIndex,
                                                 UINT NumberOfEntries,
                                                 const RGBQUAD* pColors );
typedef BOOL (WINGAPI WinGBitBltProc)(HDC hdcDest,
                                       int nXOriginDest,
                                       int nYOriginDest,
                                       int nWidthDest,
                                       int nHeightDest,
                                       HDC hdcSrc,
                                       int nXOriginSrc,
                                       int nYOriginSrc );

typedef BOOL (WINGAPI WinGStretchBltProc)(HDC hdcDest,
                                       int nXOriginDest,
                                       int nYOriginDest,
                                       int nWidthDest,
                                       int nHeightDest,
                                       HDC hdcSrc,
                                       int nXOriginSrc,
                                       int nYOriginSrc,
                                       int nWidthSrc,
                                       int nHeightSrc );


class CDIBSurface : public CDIB
{
    DECLARE_SERIAL(CDIBSurface)
public:
    CDIBSurface();
    ~CDIBSurface();

// Attributes
public:
    CDC* GetDC() {return &m_dcBuffer;}
    HDC GetHDC() {return (HDC) m_dcBuffer.GetSafeHdc();}

// Operations
public:
    BOOL Create(int cx, int cy, CPalette* pPal = NULL);
    BOOL Create(int width, int height, HPALETTE hPal); 
    void BitBlt(CDC* pDC, int xd, int yd, int w, int h,
                int xs, int ys);  
    void BitBlt(HDC hDC, int xd, int yd, int w, int h,
                int xs, int ys);  
    void StretchBlt(CDC* pDC, int xd, int yd, int wd, int hd,
                    int xs, int ys, int ws, int hs);  
    void Draw(CDC* pDC);
    void Draw(HDC hDC, int x, int y);
    void SetPalette(CPalette* pPal);
    void SetPalette(HPALETTE hPal);
    BOOL Load(const char* pszFileName = NULL); // load DIB from disk file
    BOOL MapColorsToPalette(CPalette *pPal);
    BOOL MapColorsToPalette(HPALETTE hPal);

// Implementation
protected:
#if 0
    CPalette* m_pPal;       // Palette for drawing
#else
    HPALETTE m_hPal;
#endif
    CDC m_dcBuffer;         // DC for GDI ops

private:
    static BOOL m_bUseCreateDIBSection;        // flag
    static BOOL m_bUseWinG;                    // flag
    static WinGCreateDCProc* m_pWinGCDCProc;   // ptr to WinGCreateDC()
    static WinGCreateBitmapProc* m_pWinGCBProc;// ptr to WinGCreateBitmap()
    static WinGSetDIBColorTableProc* m_pWinGSDCTProc;  // ptr to WinGSetDIBColorTable()
    static WinGBitBltProc* m_pWinGBBProc;      // ptr to WinGBitBlt()
    static WinGStretchBltProc* m_pWinGSBProc;  // ptr to WinGStretchBlt()
    HBITMAP m_hbmBuffer;        // buffer DDB
    HBITMAP m_hbmOld;           // used for storing old bitmap

    static BOOL CDIBSurface::TestPlatform();
};

/////////////////////////////////////////////////////////////////////////////
// @class COSBView | This class provides a buffered off-screen
//  view based on a CDIBSurface object.
// @base public | CScrollView
// @member Create | Creates a new buffer.
// @member GetDIB | Returns a pointer to the CDIBSurface object.
// @member GetPalette | Returns a pointer to the palette in use.
// @member GetBufferDC | Returns a GDI DC for the buffer.
// @member Draw | Draws the off-screen buffer to the window DC.
// @member AddDirtyRegion | Adds a region to the dirty region list.
// @member RenderAndDrawDirtyList | Renders and draws the entire dirty list.

/*
@mfunc CDIB* | COSBView | GetDIB | Get a pointer to the DIB buffer.
@syntax CDIB* GetDIB();
@rdesc The return value is a pointer to the buffer on NULL if an error
occurs.
@xref <c COSBView>

@mfunc CDIBPal* | COSBView | GetPalette | Get a pointer to the palette.
@syntax CDIBPal* GetPalette();
@rdesc The return value is a pointer to the palette on NULL if no palette 
exists.
@xref <c COSBView>
*/

class COSBView : public CScrollView
{
protected: // create from serialization only
    COSBView();
    DECLARE_DYNCREATE(COSBView)

// Attributes
public:
    CDocument* GetDocument();
    CDIB* GetDIB() {return m_pDIBSurf;}
    CDIBPal* GetPalette() {return m_pPal;}
    CDC* GetBufferDC();

// Operations
public:
    BOOL Create(CDIB* pDIB);        // create a new buffer
    BOOL Create(int w, int h, CPalette* pPal); // create a new buffer
    void Draw(CRect* pClipRect = NULL);  // draw os buffer to screen
    virtual void Render(CRect* pClipRect = NULL) {return;}
    void AddDirtyRegion(CRect* pRect);
    void RenderAndDrawDirtyList();

// Implementation
public:
    virtual ~COSBView();
    virtual void OnDraw(CDC* pDC);  // overridden to draw this view
    virtual void OnInitialUpdate(); // first time after construct
    virtual void OnUpdate(CView* pSender,
                          LPARAM lHint,
                          CObject* pHint);


#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    CDIBSurface* m_pDIBSurf;// the DIB buffer
    CDIBPal* m_pPal;        // Palette for drawing

private:
    CObList m_DirtyList;        // dirty regions

    void EmptyDirtyList();

// Generated message map functions
protected:
    //{{AFX_MSG(COSBView)
    afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
    afx_msg BOOL OnQueryNewPalette();
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in osbview.cpp
inline CDocument* COSBView::GetDocument()
   { return (CDocument*) m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
// @class CSpriteNotifyObj | This class provides a notifaction object 
//  template for use with CSprite objects.
// @base public | CObject
// @member Change | Called to notify a change in the status of the
//  CSprite object.

class CSprite;

class CSpriteNotifyObj : public CObject
{
public:
    enum CHANGETYPE {
        ZORDER      = 0x0001,
        POSITION    = 0x0002,
        IMAGE       = 0x0004
    };

public:
    virtual void Change(CSprite *pSprite,
                        CHANGETYPE change,
                        CRect* pRect1 = NULL,
                        CRect* pRect2 = NULL) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// @class CSprite | This class provides a sprite type object.
// @base public | CDIB
// @member GetX | Get the X coordinate of the sprite.
// @member GetY | Get the Y coordinate of the sprite.
// @member GetZ | Get the Z order of the sprite.
// @member Render | Render the image to a CDIB object.
// @member HitTest | Test if a given point is visible in the sprite.
// @member SetPosition | Set the X and Y coordinates.
// @member SetZ | Set the z order of the sprite.
// @member SetNotificationObject | Associates a notification object 
//  with the sprite.

/*
@mfunc int | CSprite | GetX | Get the X coordinate of the sprite.
@syntax virtual int GetX();
@rdesc The return value is the X coordinate of the sprite.
@xref <c CSprite> <c CDIB>

@mfunc int | CSprite | GetY | Get the Y coordinate of the sprite.
@syntax virtual int GetY();
@rdesc The return value is the Y coordinate of the sprite.
@xref <c CSprite> <c CDIB>

@mfunc int | CSprite | GetZ | Get the Z order of the sprite.
@syntax virtual int GetZ();
@rdesc The return value is the Z order of the sprite.
@xref <c CSprite> <c CDIB>

@mfunc void | CSprite | SetNotificationObject | Associates a notification
object with the sprite.
@syntax virtual void SetNotificationObject(CSpriteNotifyObj* pNO);
@parm CSpriteNotifyObj* | pNO | A pointer to a CSpriteNotifyObj object.
@rdesc There is no return value.
@xref <c CSprite> <c CDIB>
*/

class CSprite : public CDIB
{
    DECLARE_SERIAL(CSprite)
public:
    CSprite();
    ~CSprite();

    virtual int GetX() { return m_x;}   // get x
    virtual int GetY() { return m_y;}   // get y
    virtual int GetZ() { return m_z;}   // get z order

    virtual void Render(CDIB* pDIB, CRect* pClipRect = NULL);
    virtual BOOL HitTest(CPoint point);
    virtual void SetPosition(int x,
                             int y);
    virtual void SetZ(int z);
    virtual void SetNotificationObject(CSpriteNotifyObj* pNO)
        {m_pNotifyObj = pNO;}

    // from base class
    virtual void Serialize(CArchive& ar);
    virtual BOOL Load(CFile *fp);               // load from file
    virtual BOOL Load(char *pszFileName = NULL);// load DIB from disk file
    virtual BOOL Load(WORD wResid);             // load DIB from resource
    virtual BOOL MapColorsToPalette(CPalette *pPal);
    virtual void GetRect(RECT* pRect); 

protected:
    int m_x;                    // X Coordinate of top-left corner
    int m_y;                    // Y Coordinate of top-left corner
    int m_z;                    // Z order for sprite
    BYTE m_bTransIndex;         // transparency index value
    CSpriteNotifyObj *m_pNotifyObj; // ptr to a notification object

    virtual void Initialize();  // set initial state
};

/////////////////////////////////////////////////////////////////////////////
// @class CPhasedSprite | This class provides a sprite object
//  which can have multiple shapes.
// @base public | CSprite
// @member GetNumCellRows | Get the number of image cell rows.
// @member GetNumCellColumns | Get the number of image cell columns.
// @member GetCellRow | Get the current cell row.
// @member GetCellColumn | Get the current cell column.
// @member SetNumCellRows | Set the mubmer of cell rows in the image grid.
// @member SetNumCellColumns | Set the mubmer of cell columns in the image grid.
// @member SetCellRow | Set the current cell row.
// @member SetCellColumn | Set the current cell column.

/*
@mfunc int | CPhasedSprite | GetNumCellRows | Get the number of image
cell rows.
@syntax virtual int GetNumCellRows();
@rdesc The return value is the number of image cell rows.
@xref <c CPhasedSprite> <c CSprite>

@mfunc int | CPhasedSprite | GetNumCellColumns | Get the number of image
cell columns.
@syntax virtual int GetNumCellColumns();
@rdesc The return value is the number of image cell columns.
@xref <c CPhasedSprite> <c CSprite>

@mfunc int | CPhasedSprite | GetCellRow | Get the current cell row.
@syntax virtual int GetCellRow();
@rdesc The return value is the current cell row.
@xref <c CPhasedSprite> <c CSprite>

@mfunc int | CPhasedSprite | GetCellColumn | Get the current cell column.
@syntax virtual int GetCellColumn();
@rdesc The return value is the current cell column.
@xref <c CPhasedSprite> <c CSprite>

*/
class CPhasedSprite : public CSprite
{
    DECLARE_SERIAL(CPhasedSprite)
public:
    CPhasedSprite();
    ~CPhasedSprite();

    // New in this class
    virtual int GetNumCellRows() {return m_iNumCellRows;}
    virtual int GetNumCellColumns() {return m_iNumCellColumns;}
    virtual int GetCellRow() {return m_iCellRow;}
    virtual int GetCellColumn() {return m_iCellColumn;}

    virtual BOOL SetNumCellRows(int iNumRows);
    virtual BOOL SetNumCellColumns(int iNumColumns);
    virtual BOOL SetCellRow(int iRow);
    virtual BOOL SetCellColumn(int iColumn);

    // from base classes
    virtual int GetHeight() {return m_iCellHeight;}
    virtual int GetWidth() {return m_iCellWidth;}
    virtual void GetRect(RECT* pRect); 
    virtual BOOL HitTest(CPoint point);
    virtual void Render(CDIB* pDIB, CRect* pClipRect = NULL);
    virtual void Serialize(CArchive& ar);
    virtual void Initialize();

protected:
    int m_iNumCellRows;     // number of rows in the image grid
    int m_iNumCellColumns;  // number of columns in the image grid
    int m_iCellRow;         // current cell row
    int m_iCellColumn;      // current cell column
    int m_iCellHeight;      // height of a row
    int m_iCellWidth;       // width of a column
};

/////////////////////////////////////////////////////////////////////////////
// @class CSpriteListNotifyObj | This class provides a notification object
//  for use with the CSpriteList class.
// @base public | CSpriteNotifyObj
// @member SetList | Set the list to which the notification object belongs.
// @member SetView | Set the view to which the notification object belongs.
// @member Change | The notification function.

/*
@mfunc void | CSpriteListNotifyObj | SetList | Set the list to which
the notification object belongs.
@syntax void SetList(CSpriteList* pSpriteList);
@parm CSpriteList* | pSpriteList | A pointer to the parent CSpriteList object.
@rdesc There is no return value.
@xref <c CSpriteListNotifyObj> <c CSpriteNotifyObj>

@mfunc void | CSpriteListNotifyObj | SetView | Set the view to
which the notification object belongs.
@syntax void SetView(COSBView* pBufferView);
@parm COSBView* | pBufferView | A pointer to the view object.
@rdesc There is no return value.
@xref <c CSpriteListNotifyObj> <c CSpriteNotifyObj>
*/

class CSpriteList;
class COSBView;

class CSpriteListNotifyObj : public CSpriteNotifyObj
{
public:
    CSpriteListNotifyObj();
    ~CSpriteListNotifyObj();
    void SetList(CSpriteList* pSpriteList)
        {m_pSpriteList = pSpriteList;}
    void SetView(COSBView* pBufferView)
        {m_pBufferView = pBufferView;}
    void Change(CSprite *pSprite,
                CHANGETYPE change,
                CRect* pRect1 = NULL,
                CRect* pRect2 = NULL);

protected:
    CSpriteList* m_pSpriteList;
    COSBView* m_pBufferView;
};

/////////////////////////////////////////////////////////////////////////////
// @class CSpriteList | This class provides a list of CSprite objects.
// @base public | CObList
// @member RemoveAll | Remove all sprites from the list and delete them.
// @member Insert | Insert a sprite in the list.
// @member Reorder | Replace a sprite in the list according to its z-order.
// @member HitTest | Test to see if a point lies in any sprite.

class CSpriteList : private CObList
{
    DECLARE_SERIAL(CSpriteList)
public:
    CSpriteList();
    ~CSpriteList();
    void RemoveAll();
    BOOL Insert(CSprite *pSprite);
    void Reorder(CSprite *pSprite);
    CSprite *Remove(CSprite *pSprite);
    CSprite *GetNext(POSITION &pos)
        {return (CSprite *) CObList::GetNext(pos);}
    CSprite *GetPrev(POSITION &pos)
        {return (CSprite *) CObList::GetPrev(pos);}
    POSITION GetTailPosition() const
        {return CObList::GetTailPosition();}
    POSITION GetHeadPosition() const
        {return CObList::GetHeadPosition();}
    CSprite *HitTest(CPoint point);
    virtual void Serialize(CArchive& ar);
    BOOL IsEmpty()
        {return CObList::IsEmpty();}

public:
    CSpriteListNotifyObj m_NotifyObj;
};

/////////////////////////////////////////////////////////////////////////////
// @class CMCIObject | This class provides an object which encapsulates some of
//  the functionality of the Media Control Interface (MCI).
// @base public | CObject
// @member OpenFile | Open a file.
// @member OpenDevice | Open a device (such as a CD-ROM drive).
// @member Close | Close the file or device.
// @member Play | Start playback.
// @member Stop | Stop all operations.
// @member GetPosition | Get the current position.

class CMCIObject : public CObject
{
    DECLARE_SERIAL(CMCIObject)
public:
    CMCIObject();     
    ~CMCIObject();
    BOOL OpenFile(const char* pszFileName);
    BOOL OpenDevice(const char* pszDevName);
    void Close();
    void Play();
    void Stop();
    DWORD GetPosition();

// Implementation
protected:
    virtual void Serialize(CArchive& ar);   // overridden for document i/o

private:
    void MCIError(DWORD dwErr);

    MCI_OPEN_PARMS m_OpenParams; 
};

// @class CSound | This class encapsulates a simple
//  sound object.
// @base public | CObject
// @member Load | Load the sound from a resource ID.
// @member Play | Play the sound asynchronously.
// @member PlaySync | Play the sound synchronously.

class CSound : public CObject
{
    DECLARE_SERIAL(CSound)
public:
    CSound();     
    ~CSound();
    BOOL Load(WORD wResid);
    void Play();
    void PlaySync();

// Implementation
protected:
    virtual void Serialize(CArchive& ar);   // overridden for document i/o

private:
    BYTE* m_pSoundImage;
};

/////////////////////////////////////////////////////////////////////////////
// @class CWaveInDevice | This class encapsulates a waveform input device driver.
// @base public | CWnd
// @member IsOpen | Test if the device is open.
// @member CanDoFormat | Test if the device supports a given format.
// @member Open | Open the device.
// @member Close | Close the device.
// @member Reset | Stop all actions and free buffers.
// @member Record | Start recording.

class CWave;
class CWaveNotifyObj;

class CWaveInDevice : public CWnd
{

// Attributes
public:
    BOOL IsOpen(); 
    BOOL CanDoFormat(WAVEFORMAT* pFormat);

// Operations
public:
    CWaveInDevice();
    BOOL Open(int iID, WAVEFORMAT* pFormat);
    BOOL Open(int iID, PCMWAVEFORMAT* pFormat)
        {return Open(iID, (WAVEFORMAT*)pFormat);}
    BOOL Close();
    void WaveInData(CWave* pWave, WAVEHDR* pHdr);
    void Reset();
    BOOL Record(CWave* pWave,
                int iBlockSize = 4096);


// Implementation
public:
    virtual ~CWaveInDevice();

private:
    BOOL Create();

    HWAVEIN m_hInDev;               // input device handle
    int m_iBlockSize;
    int m_iBlockCount;              // number of blocks in the queue

    // Generated message map functions
protected:
    //{{AFX_MSG(CWaveInDev)
    afx_msg LRESULT OnWimData(WPARAM w, LPARAM l);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// @class CWaveOutDevice | This class encapsulates a waveform
//  output device driver.
// @base public | CWnd
// @member IsOpen | Test if the device is open.
// @member CanDoFormat | Test if the device supports a given format.
// @member Open | Open the device.
// @member Close | Close the device.
// @member Play | Start playing.
// @member Reset | Stop all actions and free buffers.

class CWaveOutDevice : public CWnd
{

// Attributes
public:
    BOOL IsOpen(); 
    BOOL CanDoFormat(WAVEFORMAT* pFormat);

// Operations
public:
    CWaveOutDevice();
    BOOL Open(WAVEFORMAT* pFormat);
    BOOL Open(PCMWAVEFORMAT* pFormat)
        {return Open((WAVEFORMAT*)pFormat);}
    BOOL Close();
    BOOL Play(CWave* pWave);
    void WaveOutDone(CWave* pWave, WAVEHDR* pHdr);
    void Reset();

// Implementation
public:
    virtual ~CWaveOutDevice();

private:
    BOOL Create();

    HWAVEOUT m_hOutDev;             // output device handle
    int m_iBlockCount;              // number of blocks in the queue

    // Generated message map functions
protected:
    //{{AFX_MSG(CWaveOutDev)
    afx_msg LRESULT OnWomDone(WPARAM w, LPARAM l);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

// some global items
extern CWaveOutDevice theDefaultWaveOutDevice;

/////////////////////////////////////////////////////////////////////////////
// @class CWaveBlock | This class encapsulates a block of
//  wave data.
// @base public | CObject
// @member CWaveBlock | Constructor.
// @member GetSamples | Get a pointer to the samples in the block.
// @member GetSize | Get the block size in bytes.
// @member GetNumSamples | Get the number of samples in the block.
// @member SetNumSamples | Set the number of samples in the block.

/*
@mfunc void* | CWaveBlock | GetSamples | Get a pointer to the sample data.
@syntax void* GetSamples();
@rdesc The return value is a pointer to the samples or NULL if no data
exists in the block.
@xref <c CWaveBlock>

@mfunc int | CWaveBlock | GetSize | Get the block size.
@syntax int GetSize();
@rdesc The return value is the size of the data block in bytes.
@xref <c CWaveBlock>

@mfunc int | CWaveBlock | GetNumSamples | Get the number of samples
in the block.
@syntax int GetNumSamples();
@rdesc The return value is the number of samples in the data block.
@xref <c CWaveBlock>

@mfunc void | CWaveBlock | SetNumSamples | Set the number of samples
in the block.
@syntax void SetNumSamples(int iCount);
@parm int | iCount | The new sample count.
@rdesc There is no return value.
@xref <c CWaveBlock>
*/

class CWaveBlock : public CObject
{
    DECLARE_SERIAL(CWaveBlock)
public:
    CWaveBlock();
    CWaveBlock(int iSize);
    CWaveBlock(void* pData, int iSize, int iSamples);     
    ~CWaveBlock();
    virtual void Serialize(CArchive& ar);
    void* GetSamples()
        {return m_pSamples;}
    int GetSample(int iSample, int iSampleSize);
    int GetSize()
        {return m_iSize;}
    int GetNumSamples()
        {return m_iNumSamples;}
    void SetNumSamples(int iCount)
        {m_iNumSamples = iCount;}   

public:
    void* m_pSamples;           // ptr to samples
    int m_iSize;                // size of block in bytes
    int m_iNumSamples;          // no of samples used in block
};

/////////////////////////////////////////////////////////////////////////////
// @class CWaveBlockList | This class provides a list of CWaveBlock objects.
// @base private | CObList
// @member FreeAll | Delete all blocks in the list.
// @member AppendBlock | Append a CWaveBlock to the list.
// @member IsEmpty | Test if the list is empty.
// @member GetCount | Get the number of blocks in the list.
// @member GetSample | Get a single sample from the block.
// @member RemoveHead | Remove the first block from the list.
// @member RemoveTail | Remove the last block from the list.

/*
@mfunc void | CWaveBlockList | AppendBlock | Add a new block to the end of
the list.
@syntax void AppendBlock(CWaveBlock* pBlock);
@parm CWaveBlock* | pBlock | A pointer to the new block to add to the list.
@rdesc There is no return value.
@xref <c CWaveBlocklist> <c CWaveBlock>
*/

class CWaveBlockList : private CObList
{
    DECLARE_SERIAL(CWaveBlockList)
public:
    CWaveBlockList();     
    ~CWaveBlockList();
    virtual void Serialize(CArchive& ar);
    void FreeAll();
    BOOL IsEmpty() 
        {return CObList::IsEmpty();}
    int GetCount()
        {return CObList::GetCount();}
    CWaveBlock* RemoveHead()
        {return (CWaveBlock*) CObList::RemoveHead();}
    CWaveBlock* RemoveTail()
        {return (CWaveBlock*) CObList::RemoveTail();}
    void AppendBlock(CWaveBlock* pBlock)
        {CObList::AddTail(pBlock);}
    POSITION GetHeadPosition() 
        {return CObList::GetHeadPosition();}
    CWaveBlock* GetNext(POSITION& rPos)
        {return (CWaveBlock*) CObList::GetNext(rPos);}                   
};


/////////////////////////////////////////////////////////////////////////////
// @class CWaveNotifyObj | This class provides a notification object
//  used by CWave objects.
// @base public | CObject
// @member NewData | Called when new data is added to a CWave object.
// @member EndPlayback | Called when playback of a CWave object stops.

/*
@mfunc int | CWaveNotifyObj | NewData | Called when new data arrives
in the owning CWave object.
@syntax virtual void NewData(CWave *pWave, CWaveBlock* pBlock) = 0;
@parm CWave | pWave | A pointer the the CWave object receiving the
new data.
@parm CWaveBlock | pBlock | A pointer to the CWaveBlock object receiving the
new data.
@rdesc There is no return value.
@comm This is a pure virtual function. You must derive your own class
from <c CWaveNotifyObj> and implement the <mf CWaveNotifyObj::NewData>
function in your derived class.
@xref <c CWaveNotifyObj> <c CWave> <c CWaveBlock>

@mfunc int | CWaveNotifyObj | EndPlayback | Called when playback of a
CWave object stops.
@syntax virtual void EndPlayback(CWave *pWave) = 0;
@parm CWave | pWave | A pointer the the CWave object which was
being played.
@rdesc There is no return value.
@comm This is a pure virtual function. You must derive your own class
from <c CWaveNotifyObj> and implement the <mf CWaveNotifyObj::Endplayback>
function in your derived class.
@xref <c CWaveNotifyObj> <c CWave> <c CWaveBlock>
*/

class CWaveNotifyObj : public CObject
{
public:
    virtual void NewData(CWave *pWave,
                         CWaveBlock* pBlock) = 0;
    virtual void EndPlayback(CWave *pWave) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// @class CWave | This class encapsulates a waveform.
// @base public | CObject
// @member CWave | Constructor.
// @member AddRef | Increments the object's reference count.
// @member Release | Decrements the object's reference count and deletes
//  the object if the reference count falls to zero.
// @member Create | Create a new CWave object.
// @member Play | Start playing.
// @member Stop | Playing or recording.
// @member Load | Load a sound from a file.
// @member LoadResource | Load a sound from a resource.
// @member Record | Start recording.
// @member DeleteAll | Delete all samples.
// @member GetNumSamples | Get the number of samples in the waveform.
// @member GetFormat | Get the format of the waveform.
// @member GetOutDevice | Get the current output device.
// @member GetInDevice | Get the current input device.
// @member GetBlockList | Get the block list.
// @member GetSample | Get a single sample from the waveform.
// @member GetSampleRate | Get the sample rate.
// @member GetSampleSize | Get the size of each sample in bits.

/*
@mfunc WAVEFORMAT* | CWave | GetFormat | Get the format of the 
waveform.
@syntax WAVEFORMAT* GetFormat();
@rdesc The return value is a pointer to a WAVEFORMAT structure
which describes the format of the waveform.
@xref <c CWave>

@mfunc CWaveOutDevice* | CWave | GetOutDevice | Get the 
current output device.
@syntax CWaveOutDevice* GetOutDevice();
@rdesc The return value is a pointer to the current output
device or NULL if none is selected.
@xref <c CWave>

@mfunc CWaveInDevice* | CWave | GetInDevice | Get the 
current input device.
@syntax CWaveInDevice* GetInDevice();
@rdesc The return value is a pointer to the current input
device or NULL if none is selected.
@xref <c CWave>

@mfunc CWaveBlockList* | CWave | GetBlockList | Get a pointer
to the block list.
@syntax CWaveBlockList* GetBlockList();
@rdesc The return value is a pointer to a <c CWaveBlockList> object.
@xref <c CWave> <c CWaveBlockList>

@mfunc int | CWave | GetSampleRate | Get the sample rate.
@syntax int GetSampleRate();
@rdesc The return value is the sample rate in samples per second.
@comm Note that the sample rate is only applicable to certain types
of waveform.
@xref <c CWave>

@mfunc int | CWave | GetSampleSize | Get the sample size.
@syntax int GetSampleSize();
@rdesc The return value is the size of a sample in bits.
@xref <c CWave>

*/
class CWave : public CObject
{
public:
    enum WAVEFLAG {
        flagDefault         = 0x0000,
        flagAutoDestruct    = 0x0001
    };

    DECLARE_SERIAL(CWave)
public:
    CWave(WAVEFLAG flag = CWave::flagDefault);     
    virtual ~CWave();
    int AddRef();
    int Release();
    BOOL Create(int samprate = 11025,
                int sampsize = 8,
                int nSamples = 0);
    BOOL Create(PCMWAVEFORMAT* pFmt,
                int nSamples = 0);
    BOOL Play(CWaveOutDevice *pWaveOutDevice = NULL,
              CWaveNotifyObj* pNotify = NULL);
    void Stop();
    BOOL Load(const char *pszFileName = NULL);
    BOOL Load(CFile *fp);  
    BOOL Load(UINT hFile);
    BOOL Load(HMMIO hmmio);
    BOOL LoadResource(WORD wID);
    BOOL Record(CWaveInDevice* pDev,
                int iBlockSize = 4096,
                CWaveNotifyObj* pNotify = NULL);
    void DeleteAll();
    int GetNumSamples();
    int GetSample(int iSample);
    int GetSampleRate()
        {return m_pcmfmt.wf.nSamplesPerSec;}
    int GetSampleSize()
        {return m_pcmfmt.wBitsPerSample;}

// Attributes
public:
    WAVEFORMAT *GetFormat() 
        {return (WAVEFORMAT*)&m_pcmfmt;}
    CWaveOutDevice* GetOutDevice() 
        {return m_pOutDev;}
    CWaveInDevice* GetInDevice() 
        {return m_pInDev;}
    CWaveBlockList* GetBlockList()
        {return &m_BlockList;}
    void NewData(CWaveBlock* pBlock);


// Implementation
public:
    BOOL m_bAutoDestruct;       // die when not busy
    BOOL IsPlaying() 
        {return m_iPlayCount > 0 ? TRUE : FALSE;}
    void IncPlayCount() 
        {m_iPlayCount++;}
    void DecPlayCount(); 

protected:
    virtual void Serialize(CArchive& ar);   // overridden for document i/o

private:
    PCMWAVEFORMAT m_pcmfmt;     // pcm wave format header
    CWaveBlockList m_BlockList; // list of wave blocks
    CWaveOutDevice *m_pOutDev;  // output device
    CWaveInDevice *m_pInDev;    // input device
    int m_iRefCount;            // reference count
    int m_iPlayCount;           // no of blocks currently being played
    CWaveNotifyObj* m_pNotifyObj;
};

/////////////////////////////////////////////////////////////////////////////
// @class CMeter | This class provides a moving coil meter display with up to 
//  4 needles.  Each needle can have a separate scale.
//  view based on a CDIBSurface object.
// @base public | CWnd
// @member Create | Creates a new meter.
// @member SetScale | Sets a scale range
// @member SetNeedleColor | Sets the color of a needle
// @member SetValue | Sets the current value of a needle
// @member SetScaleSplit | Sets the point on the scale at which the color changes.
// @member SetScaleColor | Sets the color of the two scale segments.
// @member SetTextColor | Sets the color of the text.

typedef struct _METERSCALE {
    int iMin;               // min value
    int iMax;               // max value ( > min)
    int iValue;             // current value
    COLORREF clr;           // needle color
    CPoint ptEnd;           // where the end of the needle is
} METERSCALE;

#define MAXSCALES 4         // max number of meter needles

class CMeter : public CWnd
{
// Construction
public:
    CMeter(CPalette* pPal = NULL);
    BOOL Create(const char* pszCaption,
                DWORD dwStyle,
                const RECT& rect,
                CWnd* pwndParent,
                UINT id,
                CPalette* pPal = NULL);

// Attributes
public:

// Operations
public:
    void SetScale(int iMin, int iMax, int iScale = 0);
    void SetNeedleColor(COLORREF clr, int iScale = 0);
    void SetValue(int iValue, int iScale = 0);
    void SetScaleSplit(int iValue);
    void SetScaleColor(COLORREF clrLower, COLORREF clrUpper = 0xFFFFFFFF);
    void SetTextColor(COLORREF clrText);

// Implementation
public:
    virtual ~CMeter();

protected:
    int m_iWidth;
    int m_iHeight;
    CPalette* m_pPal;
    COLORREF m_clrBkgnd;            // background color
    COLORREF m_clrText;            // scale color
    METERSCALE m_Scale[MAXSCALES];  // scale info
    CPoint m_ptCenter;              // center of pointer rotation
    CDIBSurface m_dsBuffer;         // os-buffer
    CDIBSurface m_dsImage;          // image of the meter
    CString m_strCaption;           // caption
    int m_iScaleSplit;              // scale split point (scale 0 only)
    COLORREF m_clrLowerScale;       // lower scale color
    COLORREF m_clrUpperScale;       // upper scale color

    void CreateImages();
    void Render(const CRect* pClipRect = NULL);
    void Draw(const CRect* pClipRect = NULL);
    void GetNeedleRect(CRect* pRect, METERSCALE* ps);
    void ComputeNeedleEnd(CPoint* pPt, int iValue, METERSCALE* ps);
    int InRange(int iValue, int iScale);

    // Generated message map functions
protected:
    //{{AFX_MSG(CMeter)
    afx_msg void OnPaint();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// @class CVUMeter | This class provides a VU meter.
// @base public | CMeter
// @member SetValue | Set the mean and peak values.

class CVUMeter : public CMeter
{
// Construction
public:
    CVUMeter(CPalette* pPal = NULL);
    BOOL Create(const char* pszCaption,
                DWORD dwStyle,
                const RECT& rect,
                CWnd* pwndParent,
                UINT id,
                CPalette* pPal = NULL);

// Attributes
public:

// Operations
public:
    void SetValue(int iMean, int iPeak);

// Implementation
public:
    virtual ~CVUMeter();

private:
    UINT m_uiTimer;
    int m_iMean;
    int m_iPeak;
    int m_iNewMean;
    int m_iNewPeak;

    // Generated message map functions
protected:
    //{{AFX_MSG(CVUMeter)
    afx_msg void OnTimer(UINT nIDEvent);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnDestroy();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// @class CTransBmp | This class adds simple and transparent drawing
//  to the CBitmap class.
// @base public | CBitmap
// @member GetWidth | Returns the width of the bitmap.
// @member GetHeight | Returns the height of the bitmap.
// @member Draw | Draws the bitmap with no transparency.
// @member DrawTrans | Draws the bitmap with transparency.
  
class CTransBmp : public CBitmap
{
public:
    CTransBmp();
    ~CTransBmp();
    void Draw(HDC hDC, int x, int y);
    void Draw(CDC* pDC, int x, int y);
    void DrawTrans(HDC hDC, int x, int y);
    void DrawTrans(CDC* pDC, int x, int y);
    int GetWidth();
    int GetHeight();

private:
    int m_iWidth;
    int m_iHeight;
    HBITMAP m_hbmMask;    // handle to mask bitmap

    void GetMetrics();
    void CreateMask(HDC hDC);
};


#endif // __ANIMATE__
