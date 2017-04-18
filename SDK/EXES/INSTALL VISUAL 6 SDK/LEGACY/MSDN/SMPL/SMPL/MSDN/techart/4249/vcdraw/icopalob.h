/////////////////////////////////////////////////////////////////////////////
// IColorPalObj wrapper class

class IColorPalObj : public COleDispatchDriver
{
// Attributes
public:
	long GetHPal();
	void SetHPal(long);

// Operations
public:
	BOOL CreateColorCube();
	void Draw(long hDC, long x1, long y1, long x2, long y2);
	void MakeIdentity();
	BOOL CreateFromImage(LPDISPATCH pImage);
	void Apply(long hDC);
	void Remove(long hDC);
};
