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
    RGBQUAD *GetClrTabAddress();                // ptr to color table
    BITMAPINFO *GetBitmapInfoAddress()
        {return m_pBMI;}                        // ptr to bitmap info
    int GetNumClrEntries();                     // number of color table entries
    BYTE *GetBitsAddress()
        {return m_pBits;}                       // ptr to the bits
    BOOL Create(BITMAPINFO *pBMI, BYTE *pBits); // create from existing mem,
    BYTE *GetPixelAddress(int x, int y);        // get a ptr to a pixel
    
    virtual int GetWidth() {return DibWidth();}   // image width
    virtual int GetHeight() {return DibHeight();} // image height
    virtual COLORREF GetPixelColor(int x, int y); // color (RGB value) of a pixel
    virtual void GetRect(RECT *pRect);          // get bounding rect
    virtual BOOL Create(int width, int height); // create a new DIB
    virtual BOOL Load(char *pszFileName = NULL);// load DIB from disk file
    virtual BOOL Load(CFile *fp);               // load from file
    virtual BOOL Save(char *pszFileName = NULL);// save DIB to disk file
    virtual BOOL Save(CFile *fp);               // save to file
    virtual int MapColorsToPalette(CPalette *pPal);
    virtual void Serialize(CArchive& ar);
    virtual void Draw(CDC *pDC, int x, int y);
    virtual void CopyBits(CDIB *pDIB, 
                          int xd, int yd,
                          int w, int h,
                          int xs, int ys,
                          COLORREF clrTrans = 0xFFFFFFFF);


protected:
    BITMAPINFO *m_pBMI;         // pointer to BITMAPINFO struct
    BYTE *m_pBits;              // pointer to the bits
    BOOL m_bMyBits;             // TRUE if DIB owns Bits memory

private:
    int DibHeight() 
        {return m_pBMI->bmiHeader.biHeight;}
    int DibWidth()
        {return m_pBMI->bmiHeader.biWidth;}
    int GetStorageWidth()
        {return (m_pBMI->bmiHeader.biWidth + 3) & ~3;}
};

// private module scope functions
static BOOL IsWinDIB(BITMAPINFOHEADER *pBIH);
static int NumDIBColorEntries(BITMAPINFO *pBmpInfo); 

#endif // __DIB__
