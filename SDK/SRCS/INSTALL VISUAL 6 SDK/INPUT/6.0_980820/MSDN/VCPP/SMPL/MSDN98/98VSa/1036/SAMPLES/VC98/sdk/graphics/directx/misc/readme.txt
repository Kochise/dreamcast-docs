DirectX Samples MISC Directory Readme
Copyright (C) 1995-1997 Microsoft Corporation. All Rights Reserved.

1. D3DUtils

        d3dutils.h, d3dutils.inl and d3dutils.cpp implement a set
of helper functions for C++ programmers for the following tasks:


1a. Matrix construction

D3DMATRIX ZeroMatrix();
        Returns the zero matrix.

D3DMATRIX IdentityMatrix();
        Returns the identity matrix.

D3DMATRIX ProjectionMatrix(const float Zn, const float Zf,
        const float fov);
        Returns the projection matrix:

        [c      0       0       0
         0      c       0       0
         0      0       Q       s
         0      0       -QZn    0]

                s = sin(fov/2)
                c = cos(fov/2)
                Q = s / (1 - Zn/Zf)
        Zn and Zf specify the near and far clipping planes.
        fov specifies the field of view angle in radians.

D3DMATRIX RotateXMatrix(const float rads);
D3DMATRIX RotateYMatrix(const float rads);
D3DMATRIX RotateZMatrix(const float rads);
        Constructs a matrix that rotates about the given axis
by rads radians.

D3DMATRIX TranslateMatrix(const float dx, const float dy,
        const float dz);
D3DMATRIX TranslateMatrix(const D3DVECTOR& v);
        Constructs a matrix to translate by the given vector.

D3DMATRIX ViewMatrix(const D3DVECTOR& from, const D3DVECTOR& at,
        const D3DVECTOR& up, const float roll);

        from is the location of the eye
        at is the location of the eye's point of interest
        up is the global "up" vector
        roll is a roll angle about the axis of the viewer

        Constructs a view matrix to translate and rotate such that
the viewer is looking down the +Z axis from the origin.

D3DMATRIX ScaleMatrix(const float size);
D3DMATRIX ScaleMatrix(const float a, const float b, const float c);
D3DMATRIX ScaleMatrix(const D3DVECTOR& v);
        Uniform and nonuniform scale matrices.

D3DMATRIX MatrixMult (const D3DMATRIX& a, const D3DMATRIX& b);
        Returns a*b

D3DMATRIX MatrixInverse (const D3DMATRIX& a);
        Returns the inverse of a.

D3DMATRIX MatrixTranspose(const D3DMATRIX& a);
        Returns the transpose of a.

D3DVECTOR TransformVector(const D3DVECTOR& v, const D3DMATRIX& m);
        Returns v*m. Divides the result through by the
perspective component of v*m.

D3DVECTOR TransformNormal(const D3DVECTOR& v, const D3DMATRIX& m);
        Returns v*MatrixTranspose(MatrixInverse(m)). This is the
correct way to transform a normal vector.
        Note, this routine should not be used to transform batches
of vectors because it would repeatedly perform the transpose and
inverse operations on the input matrix.


1b. Light management

Data Members

        D3DLIGHT2       light;
                Structure describing the light.

        LPDIRECT3DLIGHT lpD3DLight;
                Interface pointer for the light.

        int             changed;
                Dirty bit for the light.

Member Functions

HRESULT AddToViewport(LPDIRECT3DVIEWPORT2 lpView);
        Adds the light to the viewport.

HRESULT RemoveFromViewport(LPDIRECT3DVIEWPORT2 lpView);
        Removes the light from the viewport.

HRESULT Set();
        Forces the light to be updated through SetLight.

The Set*/Get* functions enable the application to update the light's
properties with single function calls. The Set* functions set
the dirty bit so the light will be updated when necessary.

SetColor/GetColor
SetPosition/GetPosition
SetDirection/GetDirection
SetAttenuation/GetAttenuation
SetRange/GetRange
SetFalloff/GetFalloff
SetUmbra/GetUmbra
SetPenumbra/GetPenumbra
SetFlags/GetFlags

Several classes are derived from Light. This is basically to
simplify construction, since some elements of D3DLIGHT2 are
not relevant to certain light types.

DirectionalLight(LPDIRECT3D2 lpD3D,
                 const D3DVECTOR& color,
                 const D3DVECTOR& direction);
ParallelPointLight(LPDIRECT3D2 lpD3D,
                   const D3DVECTOR& color,
                   const D3DVECTOR& position);
PointLight(LPDIRECT3D2 lpD3D,
           const D3DVECTOR& color,
           const D3DVECTOR& position);
SpotLight(LPDIRECT3D2 lpD3D,
          const D3DVECTOR& color,
          const D3DVECTOR& position,
          const D3DVECTOR& direction,
          const float umbra_angle,
          const float penumbra_angle);

1c. Material management

        The Material class simplifies dealing with Direct3D
materials.

Data Members

        D3DMATERIAL     Mat;
                Structure describing the material.

        D3DMATERIALHANDLE hMat;
                The material's handle.

	LPDIRECT3DMATERIAL2 lpMat;
                Pointer to the material's interface.

        int             changed;
                Dirty bit for the material.

Member Functions

HRESULT SetAsCurrent(LPDIRECT3DDEVICE2 lpDev);
        Sets the material as current to the device.

HRESULT SetAsBackground(LPDIRECT3DDEVICE2 lpDev);
        Sets the material as the current background on the device.

HRESULT Set(void);
        Forces the material to be updated using SetMaterial.

The Set*/Get* functions enable the application to update the various
material properties with single function calls. The Set* functions
set the dirty bit so the material will be updated when necessary.
        SetDiffuse/GetDiffuse
        SetAlpha/GetAlpha
        SetAmbient/GetAmbient
        SetEmissive/GetEmissive
        SetSpecular/GetSpecular
        SetPower/GetPower
        SetRampSize/GetRampSize
        SetTextureHandle/GetTextureHandle

See boids and pplane for examples of how to use the Material class.

2. D3DTexture

        d3dtex.h and d3dtex.cpp implement the D3DTexture class, which
simplifies texture managment.  D3DTexture's features are as follows:
        - Keeps a system memory copy of the texture to restore the surface.
        - Enables loading textures from bitmaps
        - Uses DirectDraw's GetDC function to access GDI's support
          for color-converting blts to load the textures.
          Note, D3DTexture does not currently support textures with
          alpha because GDI does not support bitmaps with alpha.

        See boids and flip3d for examples of how to use D3DTexture.


3.  GetDXVersion

    getdxver.cpp implements sample code showing how to detect which
version of DirectX is currently running (1.0, 2.0, ..., 5.0).

        See boids and flip3d for examples of how to use GetDXVersion.
       

4.1 RMMain

Uses D3DRM to setup a window for rendering, ask the sample to build
it's scene and then renders the scene.

rmmain.cpp

Main source file which includes WinMain and message handler.  Creates
D3DRM, uses it to setup the window for rendering and then asks the
sample to build it's scene.

rmmain.h

Header for rmmain.cpp.

rmmain.rc

Resource file for rmmain.cpp.

rmerror.cpp

D3DRM error code to string and error message box.

rmerror.h

Header for rmerror.cpp.

rmdemo.h

Because the samples do not create and manage all DirectDraw and
Direct3D objects themselves, the source is much simpler than the
immediate mode samples, but they can only run in a window.
Optionally, the D3DRM samples can be linked to D3DApp via another
harness.  This will allow them to enter fullscreen modes.  Fly is
linked to these files.

rmfull.cpp

Main source file which includes WinMain and message handler.  Uses
D3DApp to setup rendering.

rmfull.h

Header for rmfull.cpp.

rmfull.rc

Defines menus and keyboard accelerator.

rmfullrc.h

Header for rmfull.rc.

rmstats.cpp

Calculates and displays frame rate and other information.
