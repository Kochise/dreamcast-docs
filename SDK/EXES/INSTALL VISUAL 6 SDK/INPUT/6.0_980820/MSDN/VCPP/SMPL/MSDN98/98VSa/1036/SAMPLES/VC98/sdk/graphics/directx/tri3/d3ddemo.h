/*==========================================================================
 *
 *  Copyright (C) 1995, 1996 Microsoft Corporation. All Rights Reserved.
 *
 *  File: d3ddemo.h
 *
 ***************************************************************************/
#ifndef __D3DDEMO_H__
#define __D3DDEMO_H__

#include <ddraw.h>
#include <d3d.h>
#include "d3dapp.h"
#include "d3dmath.h"
#include "d3dsphr.h"
#include "d3dmacs.h"

#ifdef __cplusplus
extern "C" {
#endif
    /*
     * SetMouseCallback
     * Called in an example to set a callback function for all WM messages
     * dealing with the mouse.  The handler should return whether or not
     * it handled the message.
     */
    BOOL SetMouseCallback(BOOL(*)(UINT, WPARAM, LPARAM));
    /*
     * SetKeyDownCallback
     * Called in an example to set a callback function for keyboard
     * messages. The handler should return whether or not it handled the
     * message.
     */
    BOOL SetKeyboardCallback(BOOL(*)(UINT, WPARAM, LPARAM));

/*
 * These functions are found in the source for each example.
 */
    /*
     * RenderScene
     * Clears the viewport and viewport Z-buffer and render the scene.
     * The extent of rendering is returned in the rectangle.
     */
    BOOL RenderScene(LPDIRECT3DDEVICE2 lpDev, LPDIRECT3DVIEWPORT2 lpView,
		     LPD3DRECT lpExtent);
    /*
     * InitScene
     * Builds the model which will be rendered.
     */
    BOOL InitScene(void);

    /*
     * InitView
     * Builds execute buffer and all components needed to be added to viewport.
     */
    BOOL InitView(LPDIRECTDRAW lpDD,
		  LPDIRECT3D2 lpD3D,
		  LPDIRECT3DDEVICE2 lpDev,
		  LPDIRECT3DVIEWPORT2 lpView,
		  int NumTextures,
		  LPD3DTEXTUREHANDLE TextureHandle);
    /*
     * Release all objects and free all memory allocated in InitScene
     */
    void ReleaseScene(void);

    /*
     * Release all objects and free all memory allocated in InitView
     */
    void ReleaseView(LPDIRECT3DVIEWPORT2 lpView);

    typedef struct Defaultstag {
	D3DAppRenderState rs;
	BOOL bTexturesDisabled;
	BOOL bResizingDisabled;
	BOOL bClearsOn;
	char Name[30];
    } Defaults;

    /*
     * Allows each example to begin with different defaults
     */
    void OverrideDefaults(Defaults* defaults);

#ifdef __cplusplus
};
#endif

#endif // __D3DDEMO_H__
