/////////////////////////////////////////////////////////////////////////////
// IDrawSurfObj wrapper class

class IDrawSurfObj : public COleDispatchDriver
{
// Attributes
public:
	long GetWidth();
	void SetWidth(long);
	long GetHeight();
	void SetHeight(long);
	long GetHDC();
	void SetHDC(long);

// Operations
public:
	BOOL LoadFile(LPCTSTR pszFile);
	void Draw(long hDC, long x, long y);
	BOOL MapToPalette(long hPal);
	long GetBitmapInfo();
	BOOL CreateNew(long width, long height, long hPal);
	void CopyWithTransparency(LPDISPATCH ds, long x, long y);
	long GetDIBSurface();
};
