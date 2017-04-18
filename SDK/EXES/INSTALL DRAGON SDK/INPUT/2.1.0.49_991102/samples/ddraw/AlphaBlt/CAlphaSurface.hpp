/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    CAlphaSurface.hpp

Abstract:

    Alpha Blting Surface class declaration

-------------------------------------------------------------------*/

class CAlphaSurface 
{
public:
	CAlphaSurface(LPDIRECT3DDEVICE2 p3ddevice);
	~CAlphaSurface();
	bool LoadBitmap(LPTSTR tszBitmap);
	void Blt(LPRECT prcDest, LPRECT prcSrc, float fFade);

private:
	LPDIRECT3DTEXTURE2 m_ptexture;
	D3DTEXTUREHANDLE m_hTexture;
    LPDIRECT3DDEVICE2 m_p3ddevice;
    float m_fInvWidth, m_fInvHeight;
    float m_fOrigWidth, m_fOrigHeight;
    float m_fInvOrigWidth, m_fInvOrigHeight;
    LPDIRECTDRAWSURFACE LoadBitmapToDDS(LPTSTR tszBitmap);
};
