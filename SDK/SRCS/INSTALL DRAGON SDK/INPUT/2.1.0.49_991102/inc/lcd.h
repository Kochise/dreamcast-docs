#ifndef _LCD_H_
#define _LCD_H_

#ifdef __cplusplus
extern "C" {
#endif

#define CONTRAST_DARKEN     0x01
#define CONTRAST_LIGHTEN    0x80
#define CONTRAST_RESET      0x00
#define CONTRAST_GET_VALUE  0xFF

/*
 * Data is not yet available.
 */
#ifndef E_PENDING
#define E_PENDING                       0x80070007L
#endif


typedef struct _LCD_INFO
{
    // Calculated value
    USHORT  actualBlockSize;  // calculated ((BB+1)*32)

    // Raw values
    BYTE    PT; // Number of LCDs (numLCDs = PT+1)
    BYTE    BB; // Bytes Per Block (numBytes = (BB+1) * 32)
    BYTE    WA; // Num access to write a full block
    BYTE    HV; // Horizontal/Vertical setting
    BYTE    BW; // BW = 0 means if data = 0 LCD is white.  
    BYTE    FD; // reserved.   
    BYTE    dX; // x axis dots (numXDots = dX+1)
    BYTE    dY; // y axis dots (numYDots = dY+1)
    BYTE    TE; // Gadiation (bits per dot)
    BYTE    CT; // Contrast range (0-15, 0 means no contrast adjustment)
    BYTE    RE; // Reserved;

} LCD_INFO, *PLCD_INFO;


// {7383A1E8-0ACA-11d2-B0F7-00C04FC324F3}
DEFINE_GUID(IID_ILcd, 
0x7383a1e8, 0xaca, 0x11d2, 0xb0, 0xf7, 0x0, 0xc0, 0x4f, 0xc3, 0x24, 0xf3);


#undef INTERFACE
#define INTERFACE ILcd


DECLARE_INTERFACE_(ILcd, IUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID * ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /*** ILcd methods ***/
    STDMETHOD_(BOOL, IsStandardLcd)(THIS) PURE;
    STDMETHOD(GetLcdInfo)(THIS_ UINT pt, PLCD_INFO pLcdInfo) PURE;
    STDMETHOD(GetLcdBuffer)(THIS_ BYTE **ppLcdBuffer, DWORD *pdwBufId, DWORD dwNumLcdBytes) PURE;
    STDMETHOD(FreeLcdBuffer)(THIS_ DWORD dwBufId) PURE;
    STDMETHOD(SendLcdBuffer)(THIS_ DWORD dwBufId, BYTE pt, BYTE phase, USHORT block, HANDLE hEvent) PURE;
    STDMETHOD_(BYTE, SetLcdContrast)(THIS_ BYTE pt, BYTE contrastValue) PURE;
};

typedef struct ILcd *PLCD;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define ILcd_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define ILcd_AddRef(p) (p)->lpVtbl->AddRef(p)
#define ILcd_Release(p) (p)->lpVtbl->Release(p)
#define ILcd_IsStandardLcd(p) (p)->lpVtbl->IsStandardLcd(p)
#define ILcd_GetLcdInfo(p,a,b) (p)->lpVtbl->GetLcdInfo(p,a,b)
#define ILcd_GetLcdBuffer(p,a,b,c) (p)->lpVtbl->GetLcdBuffer(p,a,b,c)
#define ILcd_FreeLcdBuffer(p,a) (p)->lpVtbl->FreeLcdBuffer(p,a)
#define ILcd_SendLcdBuffer(p,a,b,c,d,e) (p)->lpVtbl->SendLcdBuffer(p,a,b,c,d,e)
#define ILcd_SetLcdContrast(p,a,b) (p)->lpVtbl->SetLcdContrast(p,a,b)
#else
#define ILcd_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define ILcd_AddRef(p) (p)->AddRef()
#define ILcd_Release(p) (p)->Release()
#define ILcd_IsStandardLcd(p) (p)->IsStandardLcd()
#define ILcd_GetLcdInfo(p,a,b) (p)->GetLcdInfo(a,b)
#define ILcd_GetLcdBuffer(p,a,b,c) (p)->GetLcdBuffer(a,b,c)
#define ILcd_FreeLcdBuffer(p,a) (p)->FreeLcdBuffer(a)
#define ILcd_SendLcdBuffer(p,a,b,c,d,e) (p)->SendLcdBuffer(a,b,c,d,e)
#define ILcd_SetLcdContrast(p,a,b) (p)->SetLcdContrast(a,b)
#endif




#ifdef __cplusplus
};
#endif

#endif //_LCD_H_
