// cemf.h : interface of the CEMF class
//
/////////////////////////////////////////////////////////////////////////////

class CEMF : public CObject
{
// Operations
public:
	CEMF();
	~CEMF();
	BOOL Load(const char *szFileName);
	BOOL Draw(CDC* pDC, RECT* pRect);
    LPENHMETAHEADER GetEMFHeader(){return ((m_pEMFHdr) ? m_pEMFHdr : NULL);};
    LPTSTR GetEMFDescString(){return ((m_pDescStr) ? m_pDescStr : NULL);};
    HENHMETAFILE GetEMFHandle(){return ((m_hemf) ? m_hemf : NULL);};
	

protected:
    BOOL GetEMFCoolStuff();
    BOOL LoadPalette();

// Attributes
protected:
   CString m_szPathName;
   HENHMETAFILE m_hemf;
   LPENHMETAHEADER m_pEMFHdr;
   LPTSTR m_pDescStr;
   LPPALETTEENTRY m_pPal;
   UINT m_palNumEntries;
   LPLOGPALETTE m_pLogPal;
   LOGPALETTE m_LogPal;
   HPALETTE m_hPal;
};

