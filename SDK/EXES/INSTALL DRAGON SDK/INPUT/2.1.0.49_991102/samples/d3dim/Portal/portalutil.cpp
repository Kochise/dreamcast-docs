/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    PortalUtil.cpp

Abstract:

    Contains portal functionality.

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "Portal.hpp"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    ReplaceRenderTarget

Description:

    Replaces the current rendering target surface with the given 
    surface and updates the aspect ratio of the viewport.

Arguments:

    LPDIRECTDRAWSURFACE4 pdds      - New rendering target surface

    LPDIRECTDRAWSURFACE4* ppddsOld - A pointer to a surface interface
                                     pointer that, on return, will be 
                                     set to the rendering target 
                                     that was replaced

    LPD3DRECT pd3drect             - A D3DRECT pointer that will be
                                     set to the dimensions of the 
                                     new rendering target on return

Return Value:

   TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL 
ReplaceRenderTarget(LPDIRECTDRAWSURFACE4 pdds, 
                    LPDIRECTDRAWSURFACE4* ppddsOld, 
                    LPD3DRECT pd3drect) 
{
    DDSURFACEDESC2  ddsd;
    D3DVIEWPORT2    viewData;

    if (ppddsOld) 
    {
        // Retrieve a pointer to the current rendering target
        g_errLast = g_p3ddevice->GetRenderTarget(ppddsOld);
        if (CheckError(TEXT("GetRenderTarget")))
            return FALSE;

        // GetRenderTarget incremented the ref count on the surface.
        // Release the reference.
        (*ppddsOld)->Release();
    }

    // Replace the current rendering target with the given surface
    g_errLast = g_p3ddevice->SetRenderTarget(pdds, 0);
    if (CheckError(TEXT("SetRenderTarget")))
        return FALSE;

    // Obtain the dimensions of the new rendering target
    g_errLast = GetSurfaceDesc(&ddsd, pdds);
    if (CheckError(TEXT("GetSurfaceDesc")))
        return FALSE;

    if (pd3drect) {
        pd3drect->x1 = 0;
        pd3drect->y1 = 0;
        pd3drect->x2 = ddsd.dwWidth;
        pd3drect->y2 = ddsd.dwHeight;
    }

    // Update the viewport with the dimensions of the new rendering target
    memset(&viewData, 0, sizeof(D3DVIEWPORT2));
    viewData.dwSize = sizeof(D3DVIEWPORT2);

    g_errLast = g_pviewport->GetViewport2(&viewData);
    if (CheckError(TEXT("Get Viewport")))
        return TRUE;

    viewData.dwWidth  = ddsd.dwWidth;
    viewData.dwHeight = ddsd.dwHeight;

    g_errLast = g_pviewport->SetViewport2(&viewData);
    if (CheckError(TEXT("Set Viewport")))
        return TRUE;

    return TRUE;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    SetPortalView

Description:

    Sets the view and projection matrices in such a way as to 
    render the scene from a reflective surface's point of view.

Arguments:

    PCAMERA pcam                   - The camera in the scene

    PMLVERTEX pvert                - Pointer to the first of at
                                     least three vertices representing
                                     the plane of the reflective
                                     surface

    LPD3DMATRIX pmatWorld          - The world matrix that will
                                     be used to render the reflective
                                     surface

Return Value:

   TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL 
SetPortalView(PCAMERA pcam, PMLVERTEX pvert, LPD3DMATRIX pmatWorld) 
{
    D3DVECTOR   vectFaceNormal,
                vectIncidenceDir, vectReflectDir,
                vectOffset,
                vect1, vect2,
                vectPlane[3];
    CAMERA      camReflect;
    int         i;

    // Transform the first three vertices of the reflective plane from model space to world space
    for (i = 0; i < 3; i++) {
        MultiplyVectorMatrix(&vectPlane[i], &pvert[i].vectPosition, pmatWorld);
    }

    // Calculate the face normal of the reflective plane
    vect1 = vectPlane[1] - vectPlane[0];
    vect2 = vectPlane[2] - vectPlane[0];
    vectFaceNormal = Normalize(CrossProduct(vect1, vect2));

    // Calculate the position of the camera for the reflected point of view
    memcpy(&camReflect, pcam, sizeof(CAMERA));
    vectIncidenceDir = Normalize(pcam->vectInterest - pcam->vectPosition);
    vectOffset = (2 * DotProduct(vectFaceNormal, (*(LPD3DVECTOR)&(vectPlane[0].x) - pcam->vectPosition)) * vectFaceNormal);
    camReflect.vectPosition = pcam->vectPosition + vectOffset;

    // Calculate the direction of the camera for the reflected point of view
    vectOffset = (2 * DotProduct(vectFaceNormal, vectIncidenceDir) * vectFaceNormal);
    vectReflectDir = vectIncidenceDir - vectOffset;
    camReflect.vectInterest = camReflect.vectPosition + vectReflectDir;

    camReflect.rFieldOfView = PI/3.0f;

    // Update the view matrix to reposition the camera to the mirrored point of view
    if (!SetView(&camReflect)) {
        return FALSE;
    }

    return TRUE;
}

