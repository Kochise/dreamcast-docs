/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    DCGraphics.h

Abstract:

    Class for drawing graphics.

-------------------------------------------------------------------*/


#define  D3D_OVERLOADS
#include <ddraw.h>
#include <d3d.h>

#define GR_MAX_TEXTUREX 1024
#define GR_MAX_TEXTUREY 1024

#define	TFLAG_MIPMAPPED	0x01
#define	TFLAG_ALPHA		0x02

typedef BOOL (*TEXTURE_LOAD_FUNCTION)(HANDLE TextureID, int *X, int *Y, DWORD *Flags, DWORD **Data);

enum BlendFuncType
{
	BLEND_ZERO=0,
	BLEND_ONE,
	BLEND_OTHERCOLOR,
	BLEND_INVOTHERCOLOR,
	BLEND_SRCALPHA,
	BLEND_INVSRCALPHA,
	BLEND_DESTALPHA,
	BLEND_INVDESTALPHA
};

enum DepthFuncType
{
	DFUNC_NEVER=D3DCMP_NEVER,
	DFUNC_LESS=D3DCMP_LESS,
	DFUNC_EQUAL=D3DCMP_EQUAL,
	DFUNC_LESSEQUAL=D3DCMP_LESSEQUAL,
	DFUNC_GREATER=D3DCMP_GREATER,
	DFUNC_NOTEQUAL=D3DCMP_NOTEQUAL,
	DFUNC_GREATEREQUAL=D3DCMP_GREATEREQUAL,
	DFUNC_ALWAYS=D3DCMP_ALWAYS
};

// All our basic graphics functionality is encapsulated in this class.
class GraphicsClass
{
	BOOL Initialized;

	// Window/Viewport related stuff.
	int		ResX,ResY;
	BOOL	Windowed,TripleBuffer;

	// Stuff created/destroyed by platform specific code.
	HWND	Window;
	LPDIRECTDRAW4		 DDInterface;
	LPDIRECT3D3			 D3DInterface;
	LPDIRECTDRAWSURFACE4 FrontBuffer,BackBuffer,ZBuffer;
	LPDIRECT3DDEVICE3	 D3DDevice;
	LPDIRECT3DVIEWPORT3  Viewport;
	// For windowed mode only.
	RECT WindowScreenRect;
	BOOL TV;

	// Texture management.
#define GR_MAX_TEXTURES 150
	int FirstFreeTextureIndex;
	BOOL UseTextureCaching;
	struct TextureClass
	{
		LPDIRECTDRAWSURFACE4	SurfInterface;
		LPDIRECT3DTEXTURE2		TexInterface;
		TEXTURE_LOAD_FUNCTION	LoadFunc;
		HANDLE					LoadFuncTextureID;
		BOOL					IDIsText;
		BOOL					UseMaxColor;
		DWORD					MaxColor;
		DWORD					TextureType;
	public:
		LPDIRECT3DTEXTURE2 GetInterface(void) { return TexInterface; };
	} Textures[GR_MAX_TEXTURES];
	int MaxTextureWidth,MaxTextureHeight;

	// Pixel formats for textures.
	DDPIXELFORMAT RGBPixelFormat;
	DDPIXELFORMAT ARGBPixelFormat;

	// Matrix related.
	BOOL MatrixIsIdentity;
	DCMatrix16 Matrix;

	// Primitive handling.
	DWORD VertexType;
	DWORD VertexType2L;
	DWORD VertexFlags;
    D3DVIEWPORT2 ViewportData;

	// Debugging related.
	BOOL ShowTriangles;

	// Platform specific functions.
	BOOL CreateAppWindow(void);
	void DestroyAppWindow(void);
	BOOL CreateD3D(GUID *pDriverGUID, int BitDepth);
	void DestroyD3D(void);
	
	// Other private functions.
	void SetTextureData(LPDIRECTDRAWSURFACE4 SurfInterface,DWORD *TextureData,
						int X, int Y, DWORD Flags);

public:
	// Scale/translate values for 2D items.
	float ScaleX2D,ScaleY2D,TransX2D,TransY2D;
	float ScaleX2DNoShrink,ScaleY2DNoShrink,TransX2DNoShrink,TransY2DNoShrink;
	float ScaleX3D,ScaleY3D,TransX3D,TransY3D;

	// Constructor function.
	GraphicsClass(void) { Initialized=FALSE; }

	// Initialization/shutdown.
	BOOL Initialize(GUID* pDriverGUID,
					int ResXIn,
					int ResYin,
					int BitDepthIn,
					BOOL WindowedIn,
					BOOL TripleBufferIn);
	void Shutdown(void);
	
	// Textures loading.
	HANDLE AddTexture(TEXTURE_LOAD_FUNCTION LoadFunc, HANDLE LoadFuncTextureID, BOOL IDIsText, BOOL UseMaxColor);
	BOOL LoadTextures(void);
	void ReleaseTextures(void);
	void RestoreTextures(void);
	void ReloadTexture(HANDLE Texture);

	// Scene related stuff.
	BOOL BeginScene(void);
	BOOL EndScene(void);

	// Frame buffer related.
	void Flip(void);
	void AppWindowMoving(void);
	void RestoreSurfaces(void);
	void BlitBackBufferToFrontBuffer(void);
	BOOL LockFrameBuffer(void **Address, int *Stride, BOOL Front=FALSE, BOOL Read=FALSE);
	void UnlockFrameBuffer(BOOL Front=FALSE);
	BOOL LockDepthBuffer(void **Address, int *Stride);
	void UnlockDepthBuffer(void);
	void Clear(DCRect *Rect,
			   BOOL FrameBuffer, DWORD Color, 
			   BOOL ZBuffer=FALSE, float ZValue=0.0f,
			   BOOL StencilBuffer=FALSE, DWORD StencilValue=0);
	BOOL GetScreenShot(DCRect *Region, DWORD **Data);
	void DumpScreenShot(void);
	void DumpDepthBufferShot(void);

	// Matrix code.
	void SetPerspectiveProjection(float FOV, float ZNear, float ZFar);
	void SetProjectionMatrix(DCMatrix16 *m=NULL); // NULL means use "current" matrix.
	void SetViewMatrix(DCMatrix16 *m=NULL); // NULL means use "current" matrix.
	void SetWorldMatrix(DCMatrix16 *m=NULL); // NULL means use "current" matrix.
	void MatrixIdentity(void);
	void MatrixSet(DCMatrix16 *m);
	void MatrixGet(DCMatrix16 *m);
	void MatrixMultiply(DCMatrix16 *m);
	void MatrixRotateX(float Angle);
	void MatrixRotateY(float Angle);
	void MatrixRotateZ(float Angle);
	void MatrixTranslate(float X, float Y, float Z);
	void MatrixScale(float X, float Y, float Z);
	void GetProjectionMatrix(DCMatrix16 *m);
	void GetWorldMatrix(DCMatrix16 *m);
	void GetViewMatrix(DCMatrix16 *m);

	// 2D Scale/Translate.
	void Setup2DScaleTranslate(float Left, float Right, float Top, float Bottom);

	// Querying code.
	int GetFrameBufferResX(void) { return ResX; }
	int GetFrameBufferResY(void) { return ResY; }
	int GetFrameBufferBitDepth(void);
	int GetDepthBufferBitDepth(void);
	void GetViewMaxAngles(float FOVIn,float *HorzOut,float *VertOut);
	BOOL GetShowTriangles(void) { return ShowTriangles; }
	HWND GetAppWindow(void);
	BOOL IsWindowed(void) { return Windowed; };
	void GetAppWindowCentre(int *X, int *Y);
	DWORD GetTextureMaxColor(HANDLE Texture) { return (Texture) ? ((TextureClass *)Texture)->MaxColor : 0xFFFFFFFF; }

	// State changing code. Most is inline for performance reasons.
	void SetTexture(HANDLE Texture,int Stage=0) 
	{ 
		LPDIRECT3DTEXTURE2 TexInterface = (Texture) ? ((TextureClass *)Texture)->GetInterface() : NULL;
		D3DDevice->SetTexture(Stage,TexInterface);
	}
	void ShadeModeFlat(void) { D3DDevice->SetRenderState(D3DRENDERSTATE_SHADEMODE,D3DSHADE_FLAT); }  
	void ShadeModeGouraud(void) { D3DDevice->SetRenderState(D3DRENDERSTATE_SHADEMODE,D3DSHADE_GOURAUD); }  
	void DepthBias(int Bias) { D3DDevice->SetRenderState(D3DRENDERSTATE_ZBIAS,Bias); } // Bias is 0-16 as with D3D.
	void DepthFunc(DepthFuncType Func) { D3DDevice->SetRenderState(D3DRENDERSTATE_ZFUNC,Func); }
	void BlendMode(BlendFuncType Src, BlendFuncType Dst);
	void CullDisable(void) { D3DDevice->SetRenderState(D3DRENDERSTATE_CULLMODE,D3DCULL_NONE); }
	void CullCW(void) { D3DDevice->SetRenderState(D3DRENDERSTATE_CULLMODE,D3DCULL_CW); }
	void CullCCW(void) { D3DDevice->SetRenderState(D3DRENDERSTATE_CULLMODE,D3DCULL_CCW); }
	void TexAddressModeRepeat(int Stage=0) { D3DDevice->SetTextureStageState(Stage,D3DTSS_ADDRESS,D3DTADDRESS_WRAP); }
	void TexAddressModeClamp(int Stage=0)  { D3DDevice->SetTextureStageState(Stage,D3DTSS_ADDRESS,D3DTADDRESS_CLAMP); }
	void TexAddressModeMirror(int Stage=0) { D3DDevice->SetTextureStageState(Stage,D3DTSS_ADDRESS,D3DTADDRESS_MIRROR); }
	void TexBlendDecal()			{ D3DDevice->SetRenderState(D3DRENDERSTATE_TEXTUREMAPBLEND,D3DTBLEND_DECAL); }
	void TexBlendModulate()			{ D3DDevice->SetRenderState(D3DRENDERSTATE_TEXTUREMAPBLEND,D3DTBLEND_MODULATE); }
	void TexBlendModulateAlpha()	{ D3DDevice->SetRenderState(D3DRENDERSTATE_TEXTUREMAPBLEND,D3DTBLEND_MODULATEALPHA); }

	void EnableBlend(void) { D3DDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE,TRUE); }
	void DisableBlend(void) { D3DDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE,FALSE); }
	void EnableDepthTest(void) { D3DDevice->SetRenderState(D3DRENDERSTATE_ZENABLE,D3DZB_TRUE); } 
	void DisableDepthTest(void) { D3DDevice->SetRenderState(D3DRENDERSTATE_ZENABLE,D3DZB_FALSE); } 
	void EnableDepthWrite(void) { D3DDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE,TRUE); } 
	void DisableDepthWrite(void) { D3DDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE,FALSE); } 
	void EnableSpecular(void) { D3DDevice->SetRenderState(D3DRENDERSTATE_SPECULARENABLE,TRUE); }
	void DisableSpecular(void) { D3DDevice->SetRenderState(D3DRENDERSTATE_SPECULARENABLE,FALSE); }
	
	void EnableTransforms(void);
	void DisableTransforms(void);
	void EnableClipping(void) { VertexFlags&=~D3DDP_DONOTCLIP; }
	void DisableClipping(void) { VertexFlags|=D3DDP_DONOTCLIP; }
	void EnableShowTriangles(void) { ShowTriangles=TRUE; }
	void DisableShowTriangles(void) { ShowTriangles=FALSE; }

	// Primtive handling code. Again, most is inline for performance reasons.
	void DrawTriangles(DCVertex Verts[],int Count);
	void DrawTrianglesIndexed(DCVertex Verts[],int VertexCount,WORD *Indices,int IndexCount);
	void DrawStripTriangles(DCVertex Verts[],int Count);
	void DrawStripTrianglesIndexed(DCVertex Verts[],int VertexCount,WORD *Indices,int IndexCount);
	void Triangles(DCVertex *Verts, int Count)
	{
		D3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST,VertexType,Verts,Count,VertexFlags);
		if (ShowTriangles)
			DrawTriangles(Verts,Count);
	}
	void TrianglesIndexed(DCVertex *Verts,int VertexCount, WORD *Indices, int IndexCount)
	{
		D3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,VertexType,Verts,VertexCount,Indices,IndexCount,VertexFlags);
		if (ShowTriangles)
			DrawTrianglesIndexed(Verts,VertexCount,Indices,IndexCount);
	}
	void Strip(DCVertex *Verts,int Count) 
	{ 
		D3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,VertexType,Verts,Count,VertexFlags);
		if (ShowTriangles)
			DrawStripTriangles(Verts,Count);
	}
	void StripIndexed(DCVertex *Verts,int VertexCount, WORD *Indices, int IndexCount)
	{
		D3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,VertexType,Verts,VertexCount,Indices,IndexCount,VertexFlags);
		if (ShowTriangles)
			DrawStripTrianglesIndexed(Verts,VertexCount,Indices,IndexCount);
	}
	void Strip2L(DCVertex2L *Verts,int Count) 
	{ 
		D3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,VertexType2L,Verts,Count,VertexFlags);
	}
};

extern GraphicsClass gGraphics;
