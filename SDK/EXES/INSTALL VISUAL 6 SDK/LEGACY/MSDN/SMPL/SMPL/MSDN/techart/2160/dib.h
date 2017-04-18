// dib.h : header file
//
// CDIB class
//

#ifndef __DIB__
#define __DIB__

class CDIB : public CObject
{
    DECLARE_SERIAL(CDIB)
public:
    CDIB();
    ~CDIB();
    CDIB(const CDIB &dib);                      // copy costructor
    CDIB &CDIB::operator=(const CDIB &dib);     // assignment

    BYTE GetPixelValue(int x, int y);           // value (clr index) of a pixel
    LPRGBQUAD GetClrTabAddress();               // ptr to color table
    LPBITMAPINFO GetBitmapInfoAddress() {
        return (LPBITMAPINFO) m_pDIB;}          // ptr to bitmap info
    int GetNumClrEntries();                     // number of color table entries
    LPBYTE GetBitsAddress();                    // ptr to the bits

    virtual int GetWidth() {return DibWidth();}   // image width
    virtual int GetHeight() {return DibHeight();} // image height
    virtual COLORREF GetPixelColor(int x, int y); // color (RGB value) of a pixel
    virtual void GetRect(LPRECT pRect);         // get bounding rect
    virtual BOOL Create(int width, int height); // create a new DIB
    virtual BOOL Load(LPSTR pszFileName = NULL);// load DIB from disk file
    virtual BOOL Load(CFile *fp);               // load from file
    virtual int MapColorsToPalette(CPalette *pPal);
    virtual void Serialize(CArchive& ar);
    virtual void Draw(CDC *pDC, int x, int y);
    virtual void CopyBits(CDIB *pDIB, 
                          int xd, int yd,
                          int w, int h,
                          int xs, int ys,
                          COLORREF clrTrans = 0xFFFFFFFF);


protected:
    LPBYTE m_pDIB;                  // pointer to the packed DIB structure

private:
    int GetStorageWidth();                  // line storage width
    LPBYTE GetPixelAddress(int x, int y);   // get a ptr to a pixel
    int DibHeight() 
        {return ((LPBITMAPINFO)m_pDIB)->bmiHeader.biHeight;}
    int DibWidth()
        {return ((LPBITMAPINFO)m_pDIB)->bmiHeader.biWidth;}
};

// private module scope functions
static BOOL IsWinDIB(LPBITMAPINFOHEADER pBIH);
static int NumDIBColorEntries(LPBITMAPINFO pBmpInfo); 

#endif // __DIB__
