//==========================================================================;
//
//  Copyright (c) 1997	Microsoft Corporation.	All Rights Reserved.
//
//--------------------------------------------------------------------------;

#ifndef __IVPNotify__
#define __IVPNotify__

#ifdef __cplusplus
extern "C" {
#endif

/*
typedef struct _DDCOLORCONTROL
{
    DWORD 		dwSize;
    DWORD		dwFlags;
    LONG		lBrightness;
    LONG		lContrast;
    LONG		lHue;
    LONG 		lSaturation;
    LONG		lSharpness;
    LONG		lGamma;
    LONG		lEnable;
} DDCOLORCONTROL;
*/

// interface IVPBaseNotify
DECLARE_INTERFACE_(IVPBaseNotify, IUnknown)
{
public:
	// this function initializes the reconnection to the decoder. 
	STDMETHOD (RenegotiateVPParameters)(THIS_
					   ) PURE;

};

// interface IVPNotify
DECLARE_INTERFACE_(IVPNotify, IVPBaseNotify)
{
public:
    // function to set the mode (bob, weave etc)
    STDMETHOD (SetDeinterlaceMode)(THIS_ 
				   IN AMVP_MODE mode
				  ) PURE;

    // function to get the mode (bob, weave etc)
    STDMETHOD (GetDeinterlaceMode)(THIS_ 
				   OUT AMVP_MODE *pMode
				  ) PURE;


    /*
    // this function sets the overlay surface that the mixer is supposed to use.
    STDMETHOD (SetOverlaySurface)(THIS_ 
				  IN LPDIRECTDRAWSURFACE pOverlaySurface
				 ) PURE;

    // this function gets the overlay surface that the mixer is using
    STDMETHOD (GetOverlaySurface)(THIS_ 
				  OUT LPDIRECTDRAWSURFACE *ppOverlaySurface
				 ) PURE;

  // this functions sets the color-controls, if the chip supports it.
    STDMETHOD (SetColorControls)(THIS_ 
				 IN LPDDCOLORCONTROL pColorControl
				) PURE;

    // this functions also returns the capability of the hardware in the dwFlags
    // value of the struct.
    STDMETHOD (GetColorControls)(THIS_ 
				 OUT LPDDCOLORCONTROL *ppColorControl
				) PURE;
    */

};

// interface IVPVBINotify
DECLARE_INTERFACE_(IVPVBINotify, IVPBaseNotify)
{
public:
};

#ifdef __cplusplus
}
#endif


#endif // __IVPNotify__
