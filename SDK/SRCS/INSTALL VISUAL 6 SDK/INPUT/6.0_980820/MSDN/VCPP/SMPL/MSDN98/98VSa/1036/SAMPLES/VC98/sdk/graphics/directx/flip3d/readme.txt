Flip3D

Direct3D Immediate Mode (DrawPrimitive) Sample
Copyright (C) 1997 by Microsoft Corporation. All Rights Reserved.

This is a small, self-contained DrawPrimitive sample with
the following features.
    It does its own transform and lighting, so uses D3DTLVERTEX
        data only in its DrawPrimitive calls.
    It is full-screen only, which simplifies the code.
    It illustrates how to use GDI to do color conversion
        into texture surfaces.  See the D3DTexture class in
        texture.h and texture.cpp.
