/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    mmatrix.cpp

Abstract:

    mmatrix Application

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "mmatrix.hpp"

//-----------------------------------------------------------------------------
// Defines, constants, and global variables
//-----------------------------------------------------------------------------
#define ELLIPSE_NUMRINGS    20
#define ELLIPSE_NUMSECTIONS 20
#define ELLIPSE_X_LENGTH    10.5f
#define ELLIPSE_Y_LENGTH    10.5f
#define ELLIPSE_Z_LENGTH    40.5f
#define fSCREEN_WIDTH       640.0f
#define fSCREEN_HEIGHT      -480.0f
#define fXOFFSET			0.0f
#define fYOFFSET			480.0f
#define	NUM_BANANAS			36
#define NUM_COLS			6
#define NUM_ROWS			(1+(NUM_BANANAS/NUM_COLS))

//#define USE_LVERTS

// ++++ Global Variables ++++++++++++++++++++++++++++++++++++++++++++
HWND      g_hwndApp;                                // HWND of the application
HINSTANCE g_hinst;                                  // HINSTANCE of the application

// ++++ Local Variables +++++++++++++++++++++++++++++++++++++++++++++
TCHAR     g_tszAppName[] = TEXT("MMatrix");			// The App's Name


LPDIRECT3DTEXTURE2 g_pTexture[2];                 	// Ripe and green bananas

D3DVERTEX			*g_pBananaVerts		= NULL;		// Vertices for banana
D3DLVERTEX			*g_pBananaLVerts	= NULL;		// Pre-lit Vertices for banana
WORD				*g_pBananaIndices	= NULL;		// Indices for banana
WORD				*g_pEndIndices		= NULL;		// End of indices for banana
D3DMATRIX			*g_pmP				= NULL;		// Projection
D3DMATRIX			*g_pmC				= NULL;		// Projection * Clip
D3DMATRIX			*g_pmPC				= NULL;		// Projection * Clip
D3DMATRIX			*g_pmV				= NULL;		// View matrix
D3DMATRIX			*g_pmVPC			= NULL;		// View * Projection * Clip
D3DMATRIX			*g_pmMat1			= NULL;		// 1st matrix for skin
D3DMATRIX			*g_pmMat2			= NULL;		// 2nd matrix for skin
D3DMATRIX			*g_pMTM				= NULL;		// Transform matrices
D3DMATRIX			*g_mView			= NULL;		// View Matrix
D3DMATRIX			*g_mProj			= NULL;		// Projection Matrix
D3DMATRIX			*g_mWeight1			= NULL;		// Weighted Matrix
D3DMATRIX			*g_mWeight2			= NULL;		// Weighted Matrix
float				*aMatrices[8];					// Pointers for up to 8 matrices
D3DCOLOR			*g_pLightTable		= NULL;
LightDirn			*g_pLightDirn		= NULL;
float				*g_pWeights			= NULL;
D3DCOLOR			g_D3DColor;
D3DCOLOR			g_D3DSpecular;
D3DVECTOR			g_DirLight;

int					g_NumMatrices		= ELLIPSE_NUMRINGS + 2;
float				g_Frequency;

DWORD				g_dwNumRings = ELLIPSE_NUMRINGS;
DWORD				g_dwNumSections = ELLIPSE_NUMSECTIONS;

DWORD				g_dwNumTriangles = (g_dwNumRings+1) * g_dwNumSections * 2;
DWORD				g_dwNumVertices  = (g_dwNumRings+1) * g_dwNumSections + 2;

					//				     Indices for end caps      +               Indices for rings              
DWORD				g_dwNumIndices   = ( g_dwNumSections * 2 * 4 ) + ( g_dwNumRings * ( (g_dwNumSections * 2) + 3 ) );

extern D3DVECTOR g_vectUp;
extern D3DVECTOR g_vectFrom;
extern D3DVECTOR g_vectAt;
extern float     g_rNear;
extern float     g_rFar;
extern float     g_rAspect;
extern float	 g_rFov;


// ++++ Local Functions +++++++++++++++++++++++++++++++++++++++++++++
static BOOL RenderSceneToBackBuffer();
static BOOL AppInit(HINSTANCE hPrev,int nCmdShow);
static void *malloc32( size_t size );
static void free32( void *base32 );
static void CreateSkinningData();
static void ReleaseSkinningData();
static void InitializeMatrices();
static void BuildLights();
static void BuildMatrices();
static void BendBanana( float fTime );
static void MoveCamera( float fTime );
static void	SetRingWeight( int ringID, float z );
static void ModMatrices();

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CleanUp

Description:

    Cleans up after the application is done.  Frees allocated memory

Arguments:

    None
  
Return Value:

    None

-------------------------------------------------------------------*/
void
CleanUp()
{
    // Release global light
    for (int i = 0; i < g_cLights; i++)
        g_rglight[i]->Release();
    
	if(g_pTexture[0])
    	g_pTexture[0]->Release();
	if(g_pTexture[1])
    	g_pTexture[1]->Release();

    // Release global materials
    if (g_pmatWhite)  
        g_pmatWhite->Release();
    if (g_pmatBkGnd)  
        g_pmatBkGnd->Release();

    // Release the Viewport
    if (g_pviewport)       
        g_pviewport->Release();

    // Release the 3D Device
    if (g_p3ddevice)         
        g_p3ddevice->Release();
    
    // Release back buffer
    if (g_pddsBack)           
        g_pddsBack->Release();

    // Release the primary surface.
    if (g_pddsPrimary)        
        g_pddsPrimary->Release();

    // Release the D3D object
    if (g_pd3d)               
        g_pd3d->Release();

    // Release the DD object
    if (g_pdd)                
        g_pdd->Release();  
    
	if( g_pmP != NULL )
		free32( g_pmP );

	if( g_pmC != NULL )
		free32( g_pmC );

	if( g_pmPC != NULL )
		free32( g_pmPC );

	if( g_pmV != NULL )
		free32( g_pmV );

	if( g_pmVPC != NULL )
		free32( g_pmVPC );

	if( g_mProj != NULL )
		free32( g_mProj );

	if( g_mView != NULL )
		free32( g_mView );

	if( g_pmMat1 != NULL )
		free32( g_pmMat1 );

	if( g_pmMat2 != NULL )
		free32( g_pmMat2 );

	if( g_mWeight1 != NULL )
		free32( g_mWeight1 );

	if( g_mWeight2 != NULL )
		free32( g_mWeight2 );

	if( g_pMTM != NULL )
		free32( g_pMTM );

	if( g_pBananaVerts != NULL )
		free32( g_pBananaVerts );
	
	if( g_pBananaLVerts != NULL )
		free32( g_pBananaLVerts );
	
	if( g_pBananaIndices != NULL )
		free32( g_pBananaIndices );

	if( g_pLightTable != NULL )
		free32( g_pLightTable );

	if( g_pLightDirn != NULL )
		free32( g_pLightDirn );

	if( g_pWeights != NULL )
		free32( g_pWeights );
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    WndProc

Description:

    Window message processing routine for the main application window.
    The main purpose of this function is to exit the app when the user
    presses <Escape> or <F12>.

Arguments:

    HWND hWnd           - Window handle

    UINT uMessage       - Message identifier
  
    WPARAM wParam       - First message parameter
    
    LPARAM lParam       - Second message parameter
  
Return Value:

    Zero if the message was processed.  The return value from 
    DefWindowProc otherwise.

-------------------------------------------------------------------*/
LRESULT CALLBACK
WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
    switch (uMessage)
    {
    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE:
        case VK_F12:
            DestroyWindow(hWnd);
            return 0;

        } // switch (wParam)
        break;

    case WM_DESTROY:
        // Cleanup DirectX structures
        CleanUp();

        PostQuitMessage(0);
        return 0L;

    } // switch (message)

    return DefWindowProc (hWnd, uMessage, wParam, lParam);
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    RenderSceneToBackBuffer

Description:

    Renders the scene to the back buffer

Arguments:
    
    None

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL 
RenderSceneToBackBuffer()
{
    // Begin the scene
    g_errLast = g_p3ddevice->BeginScene();
    if (CheckError(TEXT("Begin Scene")))
        return FALSE;
	for( int i = 0; i < NUM_BANANAS; i++ )
	{
        D3DMULTIMATRIX d3dmmVars;
        
		d3dmmVars.lpd3dMatrices = &g_pMTM[i * g_NumMatrices];

		// Set texture handle to skin
		g_p3ddevice->SetTexture(0, g_pTexture[i%2]);
						
#ifdef USE_LVERTS
		d3dmmVars.lpvLightDirs = NULL;
		d3dmmVars.lpLightTable = NULL;
		d3dmmVars.lpvVertices = g_pBananaLVerts;

		g_errLast = g_p3ddevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, D3DFVF_LVERTEX,
        												 (LPVOID)&d3dmmVars, g_dwNumVertices,
                                                         g_pBananaIndices, g_dwNumIndices,
                                                         D3DDP_MULTIMATRIX );
	    if (CheckError(TEXT("DrawIndexedPrimitive")))
        {
		    g_p3ddevice->EndScene();
	        return FALSE;
        }
#else
		d3dmmVars.lpvLightDirs = &g_pLightDirn[i * g_NumMatrices];
		d3dmmVars.lpLightTable = g_pLightTable;
		d3dmmVars.lpvVertices = g_pBananaVerts;

		g_errLast = g_p3ddevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, D3DFVF_VERTEX,
        												 (LPVOID)&d3dmmVars, g_dwNumVertices,
                                                         g_pBananaIndices, g_dwNumIndices,
                                                         D3DDP_MULTIMATRIX );
	    if (CheckError(TEXT("DrawIndexedPrimitive")))
        {
		    g_p3ddevice->EndScene();
	        return FALSE;
        }
#endif

	}
	// End the scene
    g_errLast = g_p3ddevice->EndScene();
    if (CheckError(TEXT("EndScene")))
        return FALSE;

	return TRUE;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    malloc32

Description:

    Allocate 32-byte aligned data

Return Value:

    pointer to new buffer.

-------------------------------------------------------------------*/

static void *malloc32( size_t size )
{
	void *base = malloc(size+32);
	if( base )
	{
		unsigned long base32 = ( 32 + (unsigned long)base ) & ~31L;
		*(void **)(base32-4) = base;
		base = (void *)base32;
	}
	return base;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    free32

Description:

    Frees 32-byte aligned data

Return Value:

    none.

-------------------------------------------------------------------*/

static void free32( void *base32 )
{
	if( !base32 )
		free( (void *)(*(unsigned long *)((unsigned long)base32 - 4)) );
}


//******************************************************************************
//
// Function:
//
//     SetDisplayValue
//
// Description:
//
//     Set the given registry key using the given value.
//
// Arguments:
//
//     LPCWSTR szName           - Name of the registry key to set
//
//     DWORD dwValue            - Value to set the key with
//
//     LPDWORD pdwOldValue      - Contains the old value of the registry key
//                                on return
//
// Return Value:
//
//     true on success, false on failure.
//
//******************************************************************************
bool SetDisplayValue(LPCWSTR szName, DWORD dwValue, LPDWORD pdwOldValue) {

    HKEY  hKey;
    DWORD dwType;
    DWORD dwSize;
    bool  bRet = false;

    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"DisplaySettings", 0, 0, &hKey)
                                                        == ERROR_SUCCESS)
    {
        if (pdwOldValue) {
            DWORD dwOldValue;
            dwSize = sizeof(DWORD);
            if (RegQueryValueEx(hKey, szName, NULL, &dwType,
                                (LPBYTE)&dwOldValue, &dwSize) == ERROR_SUCCESS)
            {
                *pdwOldValue = dwOldValue;
            }
        }

        if (RegSetValueEx(hKey, szName, 0, REG_DWORD, (LPBYTE)&dwValue,
                            sizeof(DWORD)) == ERROR_SUCCESS)
        {
            bRet = true;
        }

        RegCloseKey(hKey);
    }

    return bRet;
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    UpdateFrame

Description:

    This function is called whenever the CPU is idle.  The application
    should update it's state and rerender to the screen if appropriate.

Return Value:

    None.

-------------------------------------------------------------------*/
void 
UpdateFrame ()
{
    static D3DRECT s_d3drect = {0, 0, 640, 480};
	
	LARGE_INTEGER lPerformanceCount;
	
	QueryPerformanceCounter( &lPerformanceCount );

	float	fTime = ((float)lPerformanceCount.QuadPart) * g_Frequency;
	
    // Clear the back buffer here so performance monitor is correct.
    g_errLast = g_pviewport->Clear(1, &s_d3drect, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER);
    if (CheckError(TEXT("Clear Back Buffer")))
        return;

	MoveCamera( fTime );
	BendBanana( fTime );
    
	// Render the banana
    if (!RenderSceneToBackBuffer())
        return;
    
    // Flip the buffers
    FlipBuffers();

}


//-----------------------------------------------------------------------------
// Name: InitVertex()
// Desc: Initializes the input vertex
//-----------------------------------------------------------------------------
VOID InitVertex
(
D3DVERTEX& vtx,
D3DVECTOR& v,
D3DVECTOR& n,
float tu,
float tv,
int matID
)
{
    vtx.x     = v.x; 
    vtx.y     = v.y; 
    vtx.z     = v.z; 
    vtx.nx    = n.x;
    vtx.ny    = n.y;
    vtx.nz    = n.z;
    vtx.tu    = tu; 
    vtx.tv    = tv;

	// Point to first matrix
	SET_MM_INDEX(vtx,matID);
}


//-----------------------------------------------------------------------------
// Name: InitLVertex()
// Desc: Initializes the pre-lit vertex
//-----------------------------------------------------------------------------
VOID InitLVertex
(
D3DLVERTEX& vtx,
D3DVECTOR& v,
D3DCOLOR clr,
D3DCOLOR spclr,
float tu,
float tv,
int matID
)
{
    vtx.x		= v.x; 
    vtx.y		= v.y; 
    vtx.z		= v.z;
	vtx.dwReserved = 0;
    vtx.color   = clr;
    vtx.specular= spclr;
    vtx.tu		= tu; 
    vtx.tv		= tv;

	// Point to first matrix
	SET_MM_INDEX(vtx,matID);
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    GenerateBanana

Description:

    Makes vertex and index data for a banana
Arguments:

    None.

Return Value:

    None.

-------------------------------------------------------------------*/
BOOL GenerateBanana( FLOAT sx, FLOAT sy, FLOAT sz )
{
    DWORD i, j, n, m; // Counters

    // Generate vertices at the end points.
    D3DVECTOR vPoint  = D3DVECTOR( 0.0f, 0.0f, sz );
    D3DVECTOR vNormal = D3DVECTOR( 0.0f, 0.0f, 1.0f );

    InitVertex( g_pBananaVerts[0], vPoint, vNormal, 0.0f, 0.0f, 0 );
    InitVertex( g_pBananaVerts[g_dwNumVertices-1], -vPoint, -vNormal, 0.0f, 0.0f, g_NumMatrices-1 );
    InitLVertex( g_pBananaLVerts[0], vPoint, g_D3DColor, g_D3DSpecular, 0.0f, 0.0f, 0 );
    InitLVertex( g_pBananaLVerts[g_dwNumVertices-1], -vPoint, g_D3DColor, g_D3DSpecular, 0.0f, 0.0f, g_NumMatrices-1 );
	
    SetRingWeight( 0, sz );
	SetRingWeight( g_NumMatrices-1, -sz );

    // Generate vertex points for rings
    FLOAT dtheta = (float)(PI / (g_dwNumRings + 2));     //Angle between each ring
    FLOAT dphi   = (float)(2*PI / g_dwNumSections); //Angle between each section
    FLOAT theta  = dtheta;
    n = 1; //vertex being generated, begins at 1 to skip top point

    for( i = 0; i < (g_dwNumRings+1); i++ )
    {
        FLOAT z   = (float)cos(theta); // z is the same for each ring
        FLOAT tv  = theta / PI;        // v is the same for each ring
        FLOAT phi = 0.0f;
        FLOAT rsintheta = (float)sin(theta);
		
		SetRingWeight( i+1, sz *z );
		
		for( j = 0; j < g_dwNumSections; j++ )
        {
            FLOAT x  =  rsintheta * (float)sin(phi);
            FLOAT y  = -rsintheta * (float)cos(phi);
            FLOAT tu = (float)(1.0f - phi / (2*PI) );
            
            vPoint  = D3DVECTOR( sx*x, sy*y, sz*z );
            vNormal = D3DVECTOR( x, y, z );
            InitVertex( g_pBananaVerts[n], vPoint, vNormal, tu, tv, i+1 );
            InitLVertex( g_pBananaLVerts[n], vPoint, g_D3DColor, g_D3DSpecular, tu, tv, i+1 );

            phi += dphi;
            ++n;
        }
        theta += dtheta;
    }

    // Generate triangles for top and bottom caps.
    for( i = 0; i < g_dwNumSections; i++ )
    {
        DWORD t1 = 4*i;
        DWORD t2 = g_dwNumIndices - ( 4 * ( g_dwNumSections - i ) );

        g_pBananaIndices[t1+0] = (WORD)(0);
        g_pBananaIndices[t1+1] = (WORD)(i + 1);
        g_pBananaIndices[t1+2] = (WORD)(1 + ((i + 1) % g_dwNumSections));
 
		// Don't forget end of strip terminator!!
		g_pBananaIndices[t1+3] =  -1;

        g_pBananaIndices[t2+0] = (WORD)( g_dwNumVertices - 1 );
        g_pBananaIndices[t2+1] = (WORD)( g_dwNumVertices - 2 - i );
        g_pBananaIndices[t2+2] = (WORD)( g_dwNumVertices - 2 - ((1 + i) % g_dwNumSections) );

        // Don't forget end of strip terminator!!
		g_pBananaIndices[t2+3] =  -1;
    }

    // Generate triangles for the rings
    m = 1;						// 1st vertex begins at 1 to skip top point
    n = g_dwNumSections * 4;	// triangle being generated, skip the top cap 
    
    for( i = 0; i < g_dwNumRings; i++ )
    {
		for( j = 0; j < g_dwNumSections+1; j++ )
        {
            g_pBananaIndices[n++] = (WORD)(m + ( j % g_dwNumSections ) );
            g_pBananaIndices[n++] = (WORD)(m + g_dwNumSections + ((j + 1) % g_dwNumSections));
		}

        // Don't forget end of strip terminator!!
		g_pBananaIndices[n++] = -1;

        m += g_dwNumSections;
    }
    return TRUE;
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    BendBanana

Description:

Arguments:

    None.

Return Value:

    None.

-------------------------------------------------------------------*/

void
BendBanana( float fTime )
{
    FLOAT fBendAngle = ( (float)sin(fTime) + 1.0f ) * 0.6f;
    *g_pmMat1  = g_matIdent;
	SetRotateXMatrix( *g_pmMat2, -fBendAngle );
	BuildMatrices();
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    MoveCamera

Description:

Arguments:

    None.

Return Value:

    None.

-------------------------------------------------------------------*/

void
MoveCamera( float fTime )
{
    // Rotate the camera about the y-axis
	g_vectFrom = D3DVECTOR( 0.0f, 0.0f, 0.0f );
	g_vectFrom.x =  (float)sin(fTime) * 600.0f;
	g_vectFrom.z = (float)-cos(fTime) * 600.0f;
    
	D3DMATRIXSetView(g_pmV, &g_vectFrom, &g_vectAt, &g_vectUp);
	
	// The light follows the camera
	D3DVECTOR light = D3DVECTOR( g_vectFrom.x, 0.0f, g_vectFrom.z );
	D3DVECTORNormalize( &light );
	g_DirLight = light;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    BuildLights

Description:

    Builds light table and initializes the light normal
Arguments:

    None.

Return Value:

    None.

-------------------------------------------------------------------*/

void
BuildLights()
{
	int i;
	DWORD red = 64;
	DWORD green = 64; 
	DWORD blue = 64;
	DWORD ambient = ( red << 16 ) | ( green << 8 ) | blue;

	for( i = 64; i < 128; i++ )
		g_pLightTable[i] = ambient;

	for( i = 0; i < 64; i++ )
	{
		g_pLightTable[i] = ( red << 16 ) | ( green << 8 ) | blue;
		red+=3;
		green+=3;
		blue+=3;
	}
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    ModMatrices

Description:

    Adds scaling and offset to perspective matrix
Arguments:

    None.

Return Value:

    None.

-------------------------------------------------------------------*/

void
ModMatrices()
{	
		D3DMATRIX *mIn = g_pmPC;
		D3DMATRIX  mOut;


		
		mOut._11 = 0.f;
		mOut._12 = mIn->_11 * fSCREEN_WIDTH + mIn->_14 * fXOFFSET;
		mOut._13 = mIn->_12 * fSCREEN_HEIGHT + mIn->_14 * fYOFFSET;
		mOut._14 = mIn->_14;
		mOut._21 = 0.f;
		mOut._22 = mIn->_21 * fSCREEN_WIDTH + mIn->_24 * fXOFFSET;
		mOut._23 = mIn->_22 * fSCREEN_HEIGHT + mIn->_24 * fYOFFSET;
		mOut._24 = mIn->_24;
		mOut._31 = 0.f;
		mOut._32 = mIn->_31 * fSCREEN_WIDTH + mIn->_34 * fXOFFSET;
		mOut._33 = mIn->_32 * fSCREEN_HEIGHT + mIn->_34 * fYOFFSET;
		mOut._34 = mIn->_34;
		mOut._42 = mIn->_41 * fSCREEN_WIDTH + mIn->_44 * fXOFFSET;
		mOut._43 = mIn->_42 * fSCREEN_HEIGHT + mIn->_44 * fYOFFSET;
		mOut._44 = mIn->_44;

		*g_pmPC = mOut;
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    BuildMatrices

Description:

    Builds 'weighted' matices
Arguments:

    None.

Return Value:

    None.

-------------------------------------------------------------------*/

void
BuildMatrices()
{
	aMatrices[0] = (float*)g_pmPC;
	aMatrices[1] = (float*)g_pmV;
	aMatrices[2] = (float*)g_mWeight1;
	aMatrices[3] = NULL;

	float y = -( NUM_ROWS / 2 ) * 50.0f;
	unsigned long EVal = 0xe0001000;

	for( int j = 0; j < NUM_ROWS; j++ )
	{
		float x = -( NUM_COLS / 2 ) * 50.0f;
		
		for( int k = 0; k < NUM_COLS; k ++ )
		{
			if( ((j*NUM_COLS)+(k+1)) > NUM_BANANAS ) break;

			for( int i = 0; i < g_NumMatrices; i++ )
			{
				D3DVECTOR light;
				D3DMATRIX transpose;

				float weight1, weight2;

				weight1 = g_pWeights[i];
				weight2 = 1.0f - weight1;
				
				ScaleMatrix( (float*)g_mWeight1, (float*)g_pmMat1, (float*)&weight1 );
				ScaleMatrix( (float*)g_mWeight2, (float*)g_pmMat2, (float*)&weight2 );
				
				// ScaleMatrix won't change these, so do it here...
				g_mWeight1->_44 *= weight1;	
				g_mWeight2->_44 *= weight2;

				AddMatrices( (float*)g_mWeight1, (float*)g_mWeight1, (float*)g_mWeight2 );
				
				TransposeMatrix( (float*)&transpose, (float*)g_mWeight1 );
				VectorMatrixMultiply( (float*)&light, (float*)&transpose, (float*)&g_DirLight );

				int index = ( NUM_COLS * j * g_NumMatrices) + ( k * g_NumMatrices ) + i;

				g_pLightDirn[index].w = 0.0f;
				g_pLightDirn[index].x = light.x * 251.0f;
				g_pLightDirn[index].y = light.y * 251.0f;
				g_pLightDirn[index].z = light.z * 251.0f;
				
				// Add x/y translation
				g_mWeight1->_41 = x;
				g_mWeight1->_42 = y;
				
				ConcatenateMatrices( (float*) &g_pMTM[index], aMatrices );
								
				g_pMTM[index]._41 = *(float *)&EVal;

			}
			x += 50.0f;
		}
		y += 50.0f;
	}

}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    GenerateWeights

Description:

    Generates weighting values for bending banana
Arguments:

    None.

Return Value:

    None.

-------------------------------------------------------------------*/

void
SetRingWeight( int ringID, float z )
{
    if( ringID < 0 || ringID >= g_NumMatrices ) return;
	
	float fMinZ = -ELLIPSE_Z_LENGTH;
    float fMaxZ = +ELLIPSE_Z_LENGTH;
	float a = ( z - fMinZ ) / ( fMaxZ - fMinZ );

	if( a >= 0.75f )
		g_pWeights[ringID] = 0.0f;
	else if( a >= 0.5f )
		g_pWeights[ringID] = 8.0f*((0.75f-a)*(0.75f-a));
	else if( a >= 0.25f )
		g_pWeights[ringID] = 1.0f-8.0f*((a-0.25f)*(a-0.25f));
	else
		g_pWeights[ringID] = 1.0f;

}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    InitializeMatrices

Description:

    Builds initial matices
Arguments:

    None.

Return Value:

    None.

-------------------------------------------------------------------*/

void
InitializeMatrices()
{
	for( int i = 0; i < g_NumMatrices * NUM_BANANAS; i++ )
		g_pMTM[i]	= g_matIdent;
	
    D3DMATRIXSetView(g_pmV, &g_vectFrom, &g_vectAt, &g_vectUp);
    D3DMATRIXSetProjection(g_pmP, g_rNear, g_rFar, g_rFov, g_rAspect);

	*g_pmC = g_matIdent; 
	
	g_pmC->_11 = 0.5f; 
	g_pmC->_22 = 0.5f; 
	g_pmC->_41 = 0.5f; 
	g_pmC->_42 = 0.5f; 

	aMatrices[0] = (float*)g_pmC;
	aMatrices[1] = (float*)g_pmP;
	aMatrices[2] = NULL;
	
	ConcatenateMatrices( (float*)g_pmPC, aMatrices );
	
	ModMatrices();

}



/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CreateSkinningData

Description:

    Initialize all of the data structures for skinning

Return Value:

    None.

-------------------------------------------------------------------*/
void 
CreateSkinningData ()
{
	g_pmP = (D3DMATRIX*)malloc32( sizeof(D3DMATRIX) );
		if( g_pmP == NULL ) return;

	g_pmC = (D3DMATRIX*)malloc32( sizeof(D3DMATRIX) );
		if( g_pmC == NULL ) return;

	g_pmPC = (D3DMATRIX*)malloc32( sizeof(D3DMATRIX) );
		if( g_pmPC == NULL ) return;

	g_pmV = (D3DMATRIX*)malloc32( sizeof(D3DMATRIX) );
		if( g_pmV == NULL ) return;

	g_pmVPC = (D3DMATRIX*)malloc32( sizeof(D3DMATRIX) );
		if( g_pmVPC == NULL ) return;

	g_mView = (D3DMATRIX*)malloc32( sizeof(D3DMATRIX) );
		if( g_mView == NULL ) return;

	g_mProj = (D3DMATRIX*)malloc32( sizeof(D3DMATRIX) );
		if( g_mProj == NULL ) return;

	g_mWeight1 = (D3DMATRIX*)malloc32( sizeof(D3DMATRIX) );
		if( g_mWeight1 == NULL ) return;

	g_mWeight2 = (D3DMATRIX*)malloc32( sizeof(D3DMATRIX) );
		if( g_mWeight2 == NULL ) return;

	g_pmMat1 = (D3DMATRIX*)malloc32( sizeof(D3DMATRIX) );
		if( g_pmMat1 == NULL ) return;

	g_pmMat2 = (D3DMATRIX*)malloc32( sizeof(D3DMATRIX) );
		if( g_pmMat2 == NULL ) return;

	g_pMTM = (D3DMATRIX*)malloc32( sizeof(D3DMATRIX) * g_NumMatrices * NUM_BANANAS  );
		if( g_pmMat2 == NULL ) return;

	g_pBananaVerts = (D3DVERTEX*)malloc32( sizeof(D3DVERTEX) * g_dwNumVertices );
		if( g_pBananaVerts == NULL ) return;
	
	g_pBananaLVerts = (D3DLVERTEX*)malloc32( sizeof(D3DVERTEX) * g_dwNumVertices );
		if( g_pBananaLVerts == NULL ) return;
	
	g_pBananaIndices = (WORD*)malloc32( sizeof(WORD) *g_dwNumIndices );
		if( g_pBananaIndices == NULL ) return;

	g_pEndIndices = &g_pBananaIndices[g_dwNumIndices-1];

	g_pLightTable = (D3DCOLOR*)malloc32( sizeof(D3DCOLOR) * 128 );
		if( g_pLightTable == NULL ) return;

	g_pLightDirn = (LightDirn*)malloc32( sizeof(LightDirn) * g_NumMatrices * NUM_BANANAS );
		if( g_pLightDirn == NULL ) return;

	g_pWeights = (float*)malloc32( sizeof(float) * g_NumMatrices );
		if( g_pWeights == NULL ) return;

	g_D3DColor = D3DRGB( 0.7,0.7,0.7 );
	g_D3DSpecular = D3DRGB( 0.5, 0.5, 0.5 );

	g_DirLight.x = 0.0f;
    g_DirLight.y = 0.707f;
    g_DirLight.z = 0.707f;
    
	// Generate the banana data
    GenerateBanana( ELLIPSE_X_LENGTH, ELLIPSE_Y_LENGTH, ELLIPSE_Z_LENGTH );

	InitializeMatrices();
 
	BuildLights();
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    AppInit

Description:

    This function registers a window class, and creates a window for
    the application.

Arguments:

    hPrev               - Hinstance of another process running the program

    nCmdShow            - Whether the app should be shown (ignored)

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL 
AppInit(HINSTANCE hPrev, int nCmdShow)
{
    WNDCLASS  cls;          
	LARGE_INTEGER lFrequency;

    if (!hPrev)
    {
        //  Register a class for the main application window
        cls.hCursor        = NULL;
        cls.hIcon          = NULL;
        cls.lpszMenuName   = NULL;
        cls.hbrBackground  = NULL;
        cls.hInstance      = g_hinst;
        cls.lpszClassName  = g_tszAppName;
        cls.lpfnWndProc    = (WNDPROC)WndProc;
        cls.style          = 0;
        cls.cbWndExtra     = 0;
        cls.cbClsExtra     = 0;

        if (!RegisterClass(&cls))
            return FALSE;
    }

    g_hwndApp = CreateWindowEx (0, g_tszAppName, g_tszAppName, WS_VISIBLE, 
                                0, 0, 640, 480, NULL, NULL, g_hinst, NULL);

    CreateSkinningData ();
	
#define VERTEX_BUFFER_SIZE 0x001E0000
#define POLYGON_BUFFER_SIZE 0x0030000
    DWORD dwVertexBufferSize;
    DWORD dwPolygonBufferSize;
	
    SetDisplayValue(L"CommandVertexBufferSize", VERTEX_BUFFER_SIZE,
    					&dwVertexBufferSize);
	SetDisplayValue(L"CommandPolygonBufferSize", POLYGON_BUFFER_SIZE,
                        &dwPolygonBufferSize);

	// Initialize DirectDraw
    if (!InitDirectDraw())
        return FALSE;

    // Initializes the Direct3D object, viewport, and sets the rendering state.
    if (!InitDirect3D())
        return FALSE;

    // Load the textures for the bananas.
	g_pTexture[0] = LoadTexture(TEXT("SKIN1"));
	g_pTexture[1] = LoadTexture(TEXT("SKIN2"));
	    	
	QueryPerformanceFrequency( &lFrequency );
	
	g_Frequency = 0.5f / (float)lFrequency.QuadPart; 

	return TRUE;
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    WinMain

Description:

    This is the entrypoint for this sample app.  It creates an app
    window and then enters a message loop.

Arguments:

    hInstance           - HInstance of the process

    hPrev               - HInstance of another process running the program

    LPTSTR lpCmdLine    - Pointer to command line string

    nCmdShow            - Whether the app should be shown (ignored)

Return Value:

    We normally return the wParam value from the WM_QUIT message.  If
    there's a failure upon initialization, we just return 0.

-------------------------------------------------------------------*/
extern "C" int APIENTRY 
WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    MSG msg;

    // Store Instance handle for use later...
    g_hinst = hInstance;

    // Call initialization procedure
    if (!AppInit(hPrevInstance,nCmdShow))
        return 0L;

    // Main Message loop
    while (TRUE)
    {
        if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
        {
            // There's a message waiting in the queue for us.  Retrieve
            // it and dispatch it, unless it's a WM_QUIT.
            if (msg.message == WM_QUIT)
                break;

            TranslateMessage(&msg); 
            DispatchMessage(&msg);
        }
        else
        {
            // If no messages pending, then update the frame.

            // Do game-related calculations (physics, AI, etc).

            // ...

            // Render the frame
            UpdateFrame();
        }
    }

    RetailOutput(TEXT("\r\nApp exited...\r\n"));
    return msg.wParam;
}
