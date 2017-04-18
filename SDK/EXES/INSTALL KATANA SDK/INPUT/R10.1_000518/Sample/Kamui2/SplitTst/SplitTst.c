/********************************************************************************************/
/* CONFIDENTIAL AND PROPRIETARY:                                                            */
/*      Copyright 1999, Sega of America.  All rights reserved.                              */
/*      This sample source code is provided for demonstration purposes only.                */
/*      Use and distribution of Sega proprietary material is governed by                    */
/*      developer licensing agreement.                                                      */
/********************************************************************************************/

/********************************************************************************************/
/* Name:     QuikTst2.c                                                                     */
/* Title:    QuickTest Kamui2 Example                                                       */
/* Author:   Gary Lake                                                                      */
/* Created:  June 4, 1999                                                                   */
/*                                                                                          */
/* Version:  1.0                                                                            */
/* Platform: Dreamcast | Set5.24 | Shinobi | Kamui2                                         */
/*                                                                                          */
/* Description:                                                                             */
/*      The purpose of this example is to provide a simple test program to demonstrate      */
/*      hardware clipping for four-player split screen applications.                        */
/*                                                                                          */
/* History:                                                                                 */
/*      08/30/99 - Minor fixes: changed vbuffer malloc, removed kmEndStrip (Gary Lake).     */
/*      06/04/99 - Ported QuikTest to Kamui2 (Gary Lake).                                   */
/*      02/24/99 - Modified memory allocation routines for 32-byte alignment.               */
/*      11/06/98 - Added extra goodies to demonstrate Set5.24 functionality (Gary Lake).    */
/*      11/04/98 - Fixes added for Set5.23 (Kerry Thompson).                                */
/*      10/11/98 - Ported to Set5.16 (Gary Lake).                                           */
/*      07/03/98 - Ported to Set4 (Gary Lake).                                              */
/*      04/08/98 - Program created (Gary Lake).                                             */
/********************************************************************************************/


/********************************************************************************************/
/* Includes                                                                                 */
/********************************************************************************************/

#include <shinobi.h>    /* Shinobi system routines. */
#include <kamui2.h>     /* Kamui2 low-level graphics HAL. */
#include <sn_fcntl.h>   /* LibCross file types. */
#include <usrsnasm.h>   /* LibCross I/O routines. */
#include <sg_syCbl.h>   /* NTSC/RGB/VGA Cable check interface. */


/********************************************************************************************/
/* Definitions                                                                              */
/********************************************************************************************/

#define DIRECT  0       /* Direct mode has been removed from Kamui2.. use 2V, it's faster.  */

#define VERTEXBUFFERSIZE    0x40000     /* Size of vertex buffer, in bytes (to be doubled). */
#define TEXTUREMEMORYSIZE   0x400000    /* VRAM set aside for textures, in bytes (4 MB). */
#define MAXTEXTURES         4096        /* Maximum number of textures to be tracked. */
#define MAXSMALLVQ          0           /* Maximum number of small VQ textures. */

/* Override Shinobi's syMalloc() / syFree() macros. */
#ifdef syMalloc
#undef syMalloc
#define syMalloc    malloc
#endif /* syMalloc */

#ifdef syFree
#undef syFree
#define syFree      free
#endif /* syFree */


/********************************************************************************************/
/* Global Variables                                                                         */
/********************************************************************************************/

void *(*MallocPtr)(unsigned long) = syMalloc;   /* Default allocation is syMalloc(). */
void (*FreePtr)(void *) = syFree;               /* Default de-allocation is syFree(). */
void PALExtCallbackFunc(PVOID pCallbackArguments); 

extern long *kmiDeviceExtension;    /* External reference to Kamui2 device driver. */

KMSTRIPCONTEXT DefaultContext =     /* Standard opaque polygon. */
{
    0x90, {KM_OPAQUE_POLYGON, KM_USERCLIP_INSIDE, KM_NORMAL_POLYGON,
    KM_FLOATINGCOLOR, KM_FALSE, KM_TRUE}, {KM_GREATER, KM_CULLCCW, KM_FALSE,
    KM_FALSE, 0}, {0, 0}, {KM_ONE, KM_ZERO, KM_FALSE, KM_FALSE, KM_NOFOG,
    KM_FALSE, KM_FALSE, KM_FALSE, KM_NOFLIP, KM_NOCLAMP, KM_BILINEAR,
    KM_FALSE, KM_MIPMAP_D_ADJUST_1_00, KM_MODULATE, 0, 0}
};

KMPACKEDARGB    Border;         /* Border color packed ARGB value. */

/* Kamui2 texture work area, must be aligned to 32-byte boundary. */
#ifdef  __MWERKS__
#pragma align (32);
KMDWORD
#else
#ifdef __GNUC__
KMDWORD __attribute__ ((aligned (32)))
#else
#pragma aligndata32(TextureWorkArea)
KMDWORD
#endif /* __GNUC__ */
#endif /* _MWERKS__ */
TextureWorkArea[MAXTEXTURES * 24 / 4 + MAXSMALLVQ * 76 / 4];

#ifdef  __MWERKS__
#pragma align (4);	/* Return Metrowerks alignment to 4-bytes. */
#endif


/********************************************************************************************/
/* Macros                                                                                   */
/********************************************************************************************/

/* Set up 32-byte aligned malloc() / free() memory management. */
#define Align32Malloc   (*MallocPtr)
#define Align32Free     (*FreePtr)

/* Align a pointer to the nearest 32-byte aligned memory address. */
#define Align32Byte(ADR)        ((((long) ADR) + 0x1F) & 0xFFFFFFE0)

/* Reference physical memory through a cached memory address (SH4 P1 memory region). */
#define SH4_P1CachedMem(ADR)    ((((long) ADR) & 0x0FFFFFFF) | 0x80000000)

/* Reference physical memory through a non-cached memory address (SH4 P2 memory region). */
#define SH4_P2NonCachedMem(ADR) ((((long) ADR) & 0x0FFFFFFF) | 0xA0000000)

/* Pack red, green, blue, and alpha values into a 32-bit RGBA color word. */
#define PackRGBA(R, G, B, A)  ((unsigned long) (((A) << 24) | ((R) << 16) | ((G) << 8) | (B)))


/********************************************************************************************/
/* MACRO _TWIDDLEADR():                                                                     */
/*      Internal macro used by TwiddledOffset() to convert a rectangular coordinate into    */
/*      a twiddled address.                                                                 */
/********************************************************************************************/

#define _TWIDDLEADR(COORD)      ((COORD & 1)             | ((COORD >> 1) & 1) << 2   |  \
                                ((COORD >> 2) & 1) << 4  | ((COORD >> 3) & 1) << 6   |  \
                                ((COORD >> 4) & 1) << 8  | ((COORD >> 5) & 1) << 10  |  \
                                ((COORD >> 6) & 1) << 12 | ((COORD >> 7) & 1) << 14  |  \
                                ((COORD >> 8) & 1) << 16 | ((COORD >> 9) & 1) << 18)


/********************************************************************************************/
/* MACRO TwiddledOffset():                                                                  */
/*      Convert a rectangular coordinate pair (x, y) into a twiddled offset.                */
/*                                                                                          */
/* Inputs:                                                                                  */
/*      X   = Horizontal pixel coordinate.                                                  */
/*      Y   = Vertical pixel coordinate.                                                    */
/*                                                                                          */
/* Outputs:                                                                                 */
/*      Return = Pixel offset into twiddled texture.                                        */
/********************************************************************************************/

#define TwiddledOffset(X, Y)    ((_TWIDDLEADR(X) << 1) | _TWIDDLEADR(Y))


/********************************************************************************************/
/* Functions & Procedures                                                                   */
/********************************************************************************************/

/********************************************************************************************/
/* _Align32Malloc():                                                                        */
/*      Allocate a memory region with a size padded to the nearest multiple of 32 bytes     */
/*      and an alignment shifted to the nearest 32-byte boundary.                           */
/*                                                                                          */
/* Inputs:                                                                                  */
/*      Size    = Size of memory region to allocate.                                        */
/*                                                                                          */
/* Outputs:                                                                                 */
/*      Return  = Pointer to 32-byte aligned memory region.                                 */
/********************************************************************************************/

void *_Align32Malloc (unsigned long Size)
{
    void *Ptr, *AlignedPtr;

    /* Adjust the requested size to a multiple of 32 bytes. */
    Size = (Size + 0x1F) & 0xFFFFFFE0;

    /* Allocate requested size plus 32 bytes padding. */
    Ptr = syMalloc (Size + 32);

    /* Align to 32-bytes (add 32 bytes if already aligned - the padding is used below). */
    AlignedPtr = (void *) ((((long) Ptr) + 0x20) & 0xFFFFFFE0);

    /* Place cookie one byte earlier for _Align32Free(). */
    *((char *) AlignedPtr - 1) = (char) ((long) AlignedPtr - (long) Ptr);

    return (AlignedPtr);
}


/********************************************************************************************/
/* _Align32Free():                                                                          */
/*      Free memory allocated using _Align32Malloc().                                       */
/*                                                                                          */
/* Inputs:                                                                                  */
/*      Ptr     = Pointer to memory region to free.                                         */
/********************************************************************************************/

void _Align32Free (void *Ptr)
{
    char Diff;

    /* Read cookie and adjust pointer back to original unaligned address before freeing. */
    Diff = *((char *) Ptr - 1);
    Ptr = (void *) ((long) Ptr - Diff);

    syFree (Ptr);
}


/********************************************************************************************/
/* Init32Malloc():                                                                          */
/*      Check the built-in malloc() / free() routines for 32-byte alignment.                */
/*      If allocations are not aligned, install alternate Align32Malloc() and               */
/*      Align32Free() functions.                                                            */
/*                                                                                          */
/* Outputs:                                                                                 */
/*      Align32Malloc   = Global macro, adjusted to point to 32-byte aligned malloc().      */
/*      Align32Free     = Global macro, adjusted to point to valid 32-byte aligned free().  */
/********************************************************************************************/

void Init32Malloc (void)
{
    char *Ptr1, *Ptr2;

    /* Use syMalloc() / syFree() by default. */
    MallocPtr = syMalloc;
    FreePtr = syFree;

    Ptr1 = syMalloc (1);
    Ptr2 = syMalloc (1);

    /* Test if either allocation was not 32-byte aligned. */
    if (((long) Ptr1 & 0x1F) || ((long) Ptr2 & 0x1F))
    {
        MallocPtr = _Align32Malloc;
        FreePtr = _Align32Free;
    }

    syFree (Ptr1);
    syFree (Ptr2);
}


/********************************************************************************************/
/* Rectangle2Twiddled():                                                                    */
/*      Convert a rectangle texture (linear order) into a PVR twiddled format texture.      */
/*      This routine was coded for sample purposes and not optimized for run-time use.      */
/*                                                                                          */
/* Inputs:                                                                                  */
/*      Rectangle    = Pointer to rectangle texture.                                        */
/*      Dimension    = Texture dimension (assumed to be square, i.e. width = height).       */
/*      BitsPerPixel = Bit depth of texture.                                                */
/*                                                                                          */
/* Outputs:                                                                                 */
/*      Twiddled = Buffer for twiddled texture output (same size as rectangle).             */
/********************************************************************************************/

void Rectangle2Twiddled (char *Rectangle, char *Twiddled, int Dimension, int BitsPerPixel)
{
    int x, y;
    char *In = Rectangle, *Out;

    /* Convert BitsPerPixel into a shift value.. 8-bit = shift by 0, 16-bit = shift by 1. */
    BitsPerPixel = BitsPerPixel >> 4;

    for (y = 0; y < Dimension; y++)
    {
        for (x = 0; x < Dimension; x++)
        {
            /* TwiddledOffset macro converts coordinate into twiddled texture offset. */
            Out = Twiddled + ((TwiddledOffset (x, y)) << BitsPerPixel);

            /* Transfer pixel from Rectangle texture to Twiddled. */
            *Out = *In;
            if (BitsPerPixel > 0)           /* Account for 16-bit data. */
                *(Out + 1) = *(In + 1);
            In += BitsPerPixel + 1;
        }
    }
}


/********************************************************************************************/
/* LoadTextureFile():                                                                       */
/*      Allocate system memory for a PVR texture and load the specified texture file from   */
/*      the GD filesystem.  Returns a pointer to the allocated memory block.                */
/*                                                                                          */
/*      Note: The PVR texture data will be offset to the nearest 32-byte aligned address    */
/*      within the returned memory region.                                                  */
/*                                                                                          */
/* Inputs:                                                                                  */
/*      Filename    = Filename character string, must be valid for the current directory.   */
/*                                                                                          */
/* Outputs:                                                                                 */
/*      Twiddled    = Buffer containing PVR texture data.                                   */
/********************************************************************************************/

PKMDWORD LoadTextureFile (char *Filename)
{
    PKMDWORD    TexturePtr;
    GDFS        gdfs;
    long        FileBlocks;

    /* Open input file. */
    if (!(gdfs = gdFsOpen (Filename, NULL)))
        return NULL;

    /* Get file size (in blocks/sectors). */
    gdFsGetFileSctSize (gdfs, &FileBlocks);

    /* Allocate memory to nearest block size (2048 bytes). */
    TexturePtr = Align32Malloc (FileBlocks * 2048);

    /* Read file to memory region (Destination address must be 32-byte aligned). */
    gdFsReqRd32 (gdfs, FileBlocks, TexturePtr);

    /* Wait for file access to finish. */
    while (gdFsGetStat (gdfs) != GDD_STAT_COMPLETE)
        ;

    /* Close file. */
    gdFsClose (gdfs);

    return TexturePtr;
}

/*------------------------------------------------------------*/
/*  Function Name   : PALExtCallbackFunc                      */
/*  Inputs          : pCallbackArguments                      */  
/*  Outputs         : None                                    */
/*  Returns         : None                                    */
/*  Globals Used    :                                         */
/*  Description     : PAL mode callback (set the height ratio)*/ 
/*------------------------------------------------------------*/

VOID STATIC	PALExtCallbackFunc(PVOID pCallbackArguments)
{
PKMPALEXTINFO	pInfo;

	pInfo = (PKMPALEXTINFO)pCallbackArguments;
	pInfo->nPALExtMode = KM_PALEXT_HEIGHT_RATIO_1_133;	   //for PAL extended mode
	return;
}




/********************************************************************************************/
/* main():                                                                                  */
/*      Entry point for C code (Where it all happens).                                      */
/********************************************************************************************/

int main (void)
{
    KMSYSTEMCONFIGSTRUCT kmsc;      /* Kamui2 system configuration structure. */

    KMVERSIONINFO       VersionInfo;            /* Kamui2 version information. */
    KMSURFACEDESC       PrimarySurfaceDesc;     /* Primary framebuffer. */
    KMSURFACEDESC       BackSurfaceDesc;        /* Back framebuffer surface. */
    KMSURFACEDESC       TexSurfaceDesc;         /* Texture surface. */
    KMVERTEXBUFFDESC    VertexBufferDesc;       /* Vertex buffer. */
    PKMSURFACEDESC      FBSurfaces[2];          /* Array of pointers to FB surfaces. */
    KMSTRIPHEAD         StripHead_01;           /* Render params for oqaque color polys. */
    KMSTRIPHEAD         StripHead_05_Opaque;    /* Render params for opaque textured polys. */
    KMSTRIPHEAD         StripHead_05_Trans;     /* Params for translucent textured polys. */
    KMVERTEX_01         CurrentStrip_01[16];    /* Strip of opaque color triangles. */
    KMVERTEX_05         CurrentStrip_05[16];    /* Strip of textured triangles. */
    PKMDWORD            VertexBufferPtr;        /* Pointer to user-allocated vertex buffer. */
    PKMDWORD            TexturePtr;             /* Pointer to texture. */
    PKMDWORD            TwiddledPtr;            /* Pointer to twiddled texture. */
    PDS_PERIPHERAL      *per;                   /* Structure used to read control pad. */
    char                Count = 0;
    float               Angle;

    int                 i;
    float               Red = 0.0f, Green = 0.0f, Blue = 0.0f;      /* Gradient colors. */
    float               ColorDelta = 0.01f;
    char                TmpString[80];

#ifdef __GNUC__
	shinobi_workaround();
#endif

    /* Tell the user about this app. */
    debug_write (SNASM_STDOUT, "SplitTest: Demonstrates 4 player split screen.", 46);

    /* Check the cable for NTSC/PAL or VGA.. works properly for SCART. */
    switch (syCblCheck())
	{
        /* Initialize the display device and set the frame buffer based on the video mode. */
        case SYE_CBL_NTSC:  /* U.S./North America NTSC (60Hz) and Brazil PAL-M (60Hz). */
            sbInitSystem (KM_DSPMODE_NTSCNI640x480, KM_DSPBPP_RGB565, 1);
            break;
        case SYE_CBL_PAL:   /* Europe PAL (50Hz) and Argentina PAL-N (50Hz). */
            sbInitSystem (KM_DSPMODE_PALNI640x480EXT, KM_DSPBPP_RGB565, 1);

			/*	Change the PAL height ratio */
			kmSetPALEXTCallback(PALExtCallbackFunc,NULL);
			kmSetDisplayMode (KM_DSPMODE_PALNI640x480EXT, KM_DSPBPP_RGB565, TRUE, FALSE);

            break;
        case SYE_CBL_VGA:   /* Standard VGA. */
            sbInitSystem (KM_DSPMODE_VGA, KM_DSPBPP_RGB565, 1);
            break;
        default:
            syBtExit();     /* Unknown video type, return to Dreamcast BootROM. */
	}

    /* Check malloc alignment. */
    Init32Malloc();

    /* Check Kamui2 version and memory information. */
    debug_write (SNASM_STDOUT, "Kamui2 Version =", 16);

    /* Use kmGetVersionInfo() or peek around in memory like a real hacker. */
    #if 1
        kmGetVersionInfo (&VersionInfo);
    #else
        VersionInfo.kmMajorVersion = *kmiDeviceExtension;
        VersionInfo.kmLocalVersion = ((*(kmiDeviceExtension + 1) & 0xFF) << 24);
        VersionInfo.kmLocalVersion |= ((*(kmiDeviceExtension + 2) & 0xFF) << 16);
        VersionInfo.kmLocalVersion |= (*(kmiDeviceExtension + 3) & 0xFFFF);
        VersionInfo.kmFrameBufferSize = *((long *) ((long) &kmiDeviceExtension + 24));
    #endif

    /* Print version information to the Codescape log window. */
    sprintf (TmpString, "  Major Version: %d", VersionInfo.kmMajorVersion);
    debug_write (SNASM_STDOUT, TmpString, strlen (TmpString));
    sprintf (TmpString, "  Minor Version: %d", ((VersionInfo.kmLocalVersion >> 24) & 0xFF));
    debug_write (SNASM_STDOUT, TmpString, strlen (TmpString));
    sprintf (TmpString, "  Major Build:   %d", ((VersionInfo.kmLocalVersion >> 16) & 0xFF));
    debug_write (SNASM_STDOUT, TmpString, strlen (TmpString));
    sprintf (TmpString, "  Minor Build:   %d", (VersionInfo.kmLocalVersion & 0xFFFF));
    debug_write (SNASM_STDOUT, TmpString, strlen (TmpString));
    sprintf (TmpString, "VRAM size %d bytes.", (VersionInfo.kmFrameBufferSize >> 4));
    debug_write (SNASM_STDOUT, TmpString, strlen (TmpString));

    /* Set size of system configuration struct, required. */
    kmsc.dwSize = sizeof(KMSYSTEMCONFIGSTRUCT);

    /* Render control flags. */
    kmsc.flags  = KM_CONFIGFLAG_ENABLE_CLEAR_FRAMEBUFFER    /* Clear FB at initialization. */
                | KM_CONFIGFLAG_NOWAITVSYNC                 /* Don't wait for the VBlank. */
                | KM_CONFIGFLAG_ENABLE_2V_LATENCY;          /* Use 2V latency render model. */

    /* Frame buffer surfaces information. */
    FBSurfaces[0] = &PrimarySurfaceDesc;
    FBSurfaces[1] = &BackSurfaceDesc;
    kmsc.ppSurfaceDescArray = FBSurfaces;   /* Set frame buffer surface description array. */
    kmsc.fb.nNumOfFrameBuffer = 2;          /* Number of frame buffers (double buffered). */
    kmsc.fb.nStripBufferHeight = 32;        /* Strip buffer height = 32xN pixels, if used. */

    /* Texture handler setup. */
    kmsc.nTextureMemorySize = TEXTUREMEMORYSIZE;    /* Texture VRAM, divisible by 32 bytes. */
    kmsc.nNumOfTextureStruct = MAXTEXTURES;         /* Maximum number of textures tracked. */
    kmsc.nNumOfSmallVQStruct = MAXSMALLVQ;          /* Max. number of small VQ textures. */
    kmsc.pTextureWork = TextureWorkArea;            /* Texture work area in system memory. */

    /* Generate 32-byte aligned vertex buffer (double-buffered). */
    VertexBufferPtr = (PKMDWORD) Align32Malloc (2 * VERTEXBUFFERSIZE);

    /* Kamui2 requires the vertex buffer region to be 32-byte aligned and non-cacheable. */
    kmsc.pVertexBuffer = (PKMDWORD) SH4_P2NonCachedMem (VertexBufferPtr);

    /* Define vertex buffer. */
    kmsc.nVertexBufferSize = VERTEXBUFFERSIZE * 2;  /* Size of vertex buffer X2, in bytes. */
    kmsc.pBufferDesc = &VertexBufferDesc;   /* Struct used to maintain vertex buffer info. */
    kmsc.nNumOfVertexBank = 2;              /* Number of vertex buffers (double buffered). */

    /* Set multi-pass rendering information. */
    kmsc.nPassDepth = 1;                                    /* Number of passes. */
    kmsc.Pass[0].dwRegionArrayFlag = KM_PASSINFO_AUTOSORT   /* Autosort translucent polys. */
        | KM_PASSINFO_ENABLE_Z_CLEAR;                       /* Clear Z buffer. */
    kmsc.Pass[0].nDirectTransferList = KM_OPAQUE_POLYGON;   /* Type sent direct in 2V mode. */

    /* Percent of vertex buffer used for each vertex type in a pass (must total 100%). */
    kmsc.Pass[0].fBufferSize[0] =  0.0f;        /* Opaque polygons (0% if sent direct). */
    kmsc.Pass[0].fBufferSize[1] =  0.0f;        /* Opaque modifier. */
    kmsc.Pass[0].fBufferSize[2] = 50.0f;        /* Translucent. */
    kmsc.Pass[0].fBufferSize[3] =  0.0f;        /* Translucent modifier. */
    kmsc.Pass[0].fBufferSize[4] = 50.0f;        /* Punchthrough. */

    /* Set system configuration. */
    kmSetSystemConfiguration (&kmsc);

    /* Set screen border color. */
    Border.dwPacked = 0x0;
    kmSetBorderColor (Border);

    /* Create a texture surface. */
    kmCreateTextureSurface (&TexSurfaceDesc, 256, 256,
        (KM_TEXTURE_TWIDDLED | KM_TEXTURE_RGB565));

    /* Load a texture file from disk. */
    TexturePtr = LoadTextureFile ("FBI.pvr");

    /* The next few calls demonstrate how to algorithmically generate a texture.  In this   */
    /* case, a rectangle format texture is loaded from disk and twiddled at run-time.       */

    /* Allocate memory for twiddled texture (256x256 16-bit). */
    TwiddledPtr = (PKMDWORD) Align32Malloc (256 * 256 * 2);

    /* Run-time twiddle source rectangle texture + 16 bytes to skip PVRT chunk header. */
    Rectangle2Twiddled ((char *) ((long) TexturePtr + 16), (char *) TwiddledPtr, 256, 16);

    /* Transfer twiddled texture from system mem to video mem using a DMA transfer. */
    kmLoadTexture (&TexSurfaceDesc, TwiddledPtr);

    /* Generate a strip head array for opaque color (no texture) polygons. */
    memset (&StripHead_01, 0, sizeof(StripHead_01));
    kmGenerateStripHead01 (&StripHead_01, &DefaultContext);

    /* Set the texture surface of the opaque polygon context to the newly loaded texture. */
    DefaultContext.ImageControl[KM_IMAGE_PARAM1].pTextureSurfaceDesc = &TexSurfaceDesc;

    /* Generate a strip head array for opaque textured polygons. */
    memset (&StripHead_05_Opaque, 0, sizeof(StripHead_05_Opaque));
    kmGenerateStripHead05 (&StripHead_05_Opaque, &DefaultContext);

    /* Modify the standard polygon context to support translucency. */
    DefaultContext.StripControl.nListType = KM_TRANS_POLYGON;
    DefaultContext.ImageControl[KM_IMAGE_PARAM1].bUseAlpha = KM_TRUE;
    DefaultContext.ImageControl[KM_IMAGE_PARAM1].nTextureShadingMode = KM_MODULATE_ALPHA;

    /* Generate a strip head array for translucent textured polygons. */
    memset (&StripHead_05_Trans, 0, sizeof(StripHead_05_Trans));
    kmGenerateStripHead05 (&StripHead_05_Trans, &DefaultContext);

    /* Just to demonstrate how a strip head can be modified once generated.. */
    kmChangeStripBlendingMode (&StripHead_05_Trans, KM_IMAGE_PARAM1,
        KM_SRCALPHA, KM_INVSRCALPHA);

    /* The main render loop. */
    while (TRUE)
	{
        Count++;
        Angle = ((float) Count) * 2.0f * 3.141592654f / 255.0f;

        /* Get control pad info filled out by the 'PeripheralServer'. */
        per = (PDS_PERIPHERAL *) pdGetPeripheral (PDD_PORT_A0);

        /* Set the vertices of the background plane for a nice color gradient. */
        /* NOTE: Yes, you can change the background plane on-the-fly. */
        CurrentStrip_01[0].ParamControlWord     = KM_VERTEXPARAM_NORMAL;
        CurrentStrip_01[0].fX                   =   0.0f;
        CurrentStrip_01[0].fY                   = 479.0f;
        CurrentStrip_01[0].u.fZ                 =   0.2f;
        CurrentStrip_01[0].fBaseAlpha           =   1.0f;
        CurrentStrip_01[0].fBaseRed             =   0.0f;
        CurrentStrip_01[0].fBaseGreen           =   0.0f;
        CurrentStrip_01[0].fBaseBlue            =   0.0f;

        CurrentStrip_01[1].ParamControlWord     = KM_VERTEXPARAM_NORMAL;
        CurrentStrip_01[1].fX                   =   0.0f;
        CurrentStrip_01[1].fY                   =   0.0f;
        CurrentStrip_01[1].u.fZ                 =   0.2f;
        CurrentStrip_01[1].fBaseAlpha           =   1.0f;
        CurrentStrip_01[1].fBaseRed             =   Red;
        CurrentStrip_01[1].fBaseGreen           =   Green;
        CurrentStrip_01[1].fBaseBlue            =   Blue;

        CurrentStrip_01[2].ParamControlWord     = KM_VERTEXPARAM_ENDOFSTRIP;
        CurrentStrip_01[2].fX                   = 639.0f;
        CurrentStrip_01[2].fY                   = 479.0f;
        CurrentStrip_01[2].u.fZ                 =   0.2f;
        CurrentStrip_01[2].fBaseAlpha           =   1.0f;
        CurrentStrip_01[2].fBaseRed             =   0.0f;
        CurrentStrip_01[2].fBaseGreen           =   0.0f;
        CurrentStrip_01[2].fBaseBlue            =   0.0f;

        /* Set the background plane to the vertices filled in above. */
        kmSetBackGround (&StripHead_01, KM_VERTEXTYPE_01,
            &CurrentStrip_01[0], &CurrentStrip_01[1], &CurrentStrip_01[2]);

        /* Update colors - just to show we're doing something. */
        if (Blue < 0.99)
        {
            Blue += ColorDelta;
            if (ColorDelta < 0)
            {
                Red += ColorDelta;
                Green += ColorDelta;
            }
        }
        else
        {
            if (Red > 0.99)
            {
                ColorDelta = -ColorDelta;
                Blue += ColorDelta;
            }
            Red += ColorDelta;
            Green += ColorDelta;
        }

        if (Blue < 0.0)
        {
            Blue = 0.0;
            Red = 0.0;
            Green = 0.0;
            ColorDelta = 0.01f;
        }

        /* Reduce the region array for kmRenderRect() to the size specified. */
        kmSetRegionClipping (0, 0, ((640/32/2) - 1), (480/32/2));

        /* Clip pixels to the bounding box provided (occurs at final stage of render). */
        kmSetPixelClipping (0, 0, 320, 240);

        /* Tell Kamui2 to start accepting polygon data for a new scene. */
        kmBeginScene (&kmsc);

        /* Start the first pass (for multipass rendering). */
        kmBeginPass (&VertexBufferDesc);

/* -------------------> Draw Quadrant 1 -------------------> */
        /* Set a user clipping region (to the nearest 32x32 tile). */
        /* May be specified multiple times per frame. */
        {
            KMRECT  ClipArea = {0, 0, ((640/32/2) - 1), (480/32/2)};

            kmSetUserClipping (&VertexBufferDesc, KM_USERCLIP_DISABLE,
                KM_OPAQUE_POLYGON, &ClipArea);

            kmSetUserClipping (&VertexBufferDesc, KM_USERCLIP_DISABLE,
                KM_TRANS_POLYGON, &ClipArea);
        }

        /* Start rendering opaque textured strips. */
        kmStartStrip (&VertexBufferDesc, &StripHead_05_Opaque);

        /* Set the vertices in the current strip to draw a textured square. */
        CurrentStrip_05[0].ParamControlWord     = KM_VERTEXPARAM_NORMAL;
        CurrentStrip_05[0].fX                   = cos(Angle) * 50.0f + 250.0f;
        CurrentStrip_05[0].fY                   = sin(Angle) * 50.0f + 240.0f;
        CurrentStrip_05[0].u.fZ                 =  11.0f;
        CurrentStrip_05[0].fU                   =   0.0f;
        CurrentStrip_05[0].fV                   =   1.0f;
        CurrentStrip_05[0].fBaseAlpha           =   1.0f;
        CurrentStrip_05[0].fBaseRed             =   0.0f;
        CurrentStrip_05[0].fBaseGreen           =   0.15f;
        CurrentStrip_05[0].fBaseBlue            =   0.73f;

        CurrentStrip_05[1].ParamControlWord     = KM_VERTEXPARAM_NORMAL;
        CurrentStrip_05[1].fX                   = cos(Angle) * 50.0f + 250.0f;
        CurrentStrip_05[1].fY                   = sin(Angle) * 50.0f + 110.0f;
        CurrentStrip_05[1].u.fZ                 =  11.0f;
        CurrentStrip_05[1].fU                   =   0.0f;
        CurrentStrip_05[1].fV                   =   0.0f;
        CurrentStrip_05[1].fBaseAlpha           =   1.0f;
        CurrentStrip_05[1].fBaseRed             =   0.55f;
        CurrentStrip_05[1].fBaseGreen           =   0.87f;
        CurrentStrip_05[1].fBaseBlue            =   0.96f;

        CurrentStrip_05[2].ParamControlWord     = KM_VERTEXPARAM_NORMAL;
        CurrentStrip_05[2].fX                   = cos(Angle) * 50.0f + 390.0f;
        CurrentStrip_05[2].fY                   = sin(Angle) * 50.0f + 240.0f;
        CurrentStrip_05[2].u.fZ                 =  11.0f;
        CurrentStrip_05[2].fU                   =   1.0f;
        CurrentStrip_05[2].fV                   =   1.0f;
        CurrentStrip_05[2].fBaseAlpha           =   1.0f;
        CurrentStrip_05[2].fBaseRed             =   0.55f;
        CurrentStrip_05[2].fBaseGreen           =   0.87f;
        CurrentStrip_05[2].fBaseBlue            =   0.96f;

        CurrentStrip_05[3].ParamControlWord     = KM_VERTEXPARAM_ENDOFSTRIP;
        CurrentStrip_05[3].fX                   = cos(Angle) * 50.0f + 390.0f;
        CurrentStrip_05[3].fY                   = sin(Angle) * 50.0f + 110.0f;
        CurrentStrip_05[3].u.fZ                 =  11.0f;
        CurrentStrip_05[3].fU                   =   1.0f;
        CurrentStrip_05[3].fV                   =   0.0f;
        CurrentStrip_05[3].fBaseAlpha           =   1.0f;
        CurrentStrip_05[3].fBaseRed             =   0.0f;
        CurrentStrip_05[3].fBaseGreen           =   0.15f;
        CurrentStrip_05[3].fBaseBlue            =   0.73f;

        for (i = 0; i <= 3; i++)
            kmSetVertex (&VertexBufferDesc, &CurrentStrip_05[i],
                KM_VERTEXTYPE_05, sizeof (KMVERTEX_05));

        /* kmEndStrip() skipped. */

        /* End the first (and only) pass. */
        kmEndPass (&VertexBufferDesc);

        /* Transfer remaining vertices to the TA and begin render to the clip region. */
        kmRenderRect (KM_RENDER_NOFLIP);

        /* Finish the scene. */
        kmEndScene (&kmsc);

        /* Clip pixels to the bounding box provided (occurs at final stage of render). */
        kmSetPixelClipping (320, 0, 640, 240);

        /* Tell Kamui2 to start accepting polygon data for a new scene. */
        kmBeginScene (&kmsc);

        /* Start the first pass (for multipass rendering). */
        kmBeginPass (&VertexBufferDesc);

/* -------------------> Draw Quadrant 2 -------------------> */
        /* Set a user clipping region (to the nearest 32x32 tile). */
        /* May be specified multiple times per frame. */
        {
            KMRECT  ClipArea = {(640/32/2), 0, (640/32), (480/32/2)};

            kmSetUserClipping (&VertexBufferDesc, KM_USERCLIP_DISABLE,
                KM_OPAQUE_POLYGON, &ClipArea);

            kmSetUserClipping (&VertexBufferDesc, KM_USERCLIP_DISABLE,
                KM_TRANS_POLYGON, &ClipArea);
        }

        /* Start translucent textured strips. */
        kmStartStrip (&VertexBufferDesc, &StripHead_05_Trans);

        /* Set the vertices in the current strip to draw a translucent textured square. */
        CurrentStrip_05[0].ParamControlWord     = KM_VERTEXPARAM_NORMAL;
        CurrentStrip_05[0].fX                   = cos(Angle) * 50.0f + 250.0f;
        CurrentStrip_05[0].fY                   = sin(Angle) * 50.0f + 370.0f;
        CurrentStrip_05[0].u.fZ                 =  21.0f;
        CurrentStrip_05[0].fU                   =   0.0f;
        CurrentStrip_05[0].fV                   =   1.0f;
        CurrentStrip_05[0].fBaseAlpha           =   0.25f;
        CurrentStrip_05[0].fBaseRed             =   0.0f;
        CurrentStrip_05[0].fBaseGreen           =   0.15f;
        CurrentStrip_05[0].fBaseBlue            =   0.73f;

        CurrentStrip_05[1].ParamControlWord     = KM_VERTEXPARAM_NORMAL;
        CurrentStrip_05[1].fX                   = cos(Angle) * 50.0f + 250.0f;
        CurrentStrip_05[1].fY                   = sin(Angle) * 50.0f + 240.0f;
        CurrentStrip_05[1].u.fZ                 =  21.0f;
        CurrentStrip_05[1].fU                   =   0.0f;
        CurrentStrip_05[1].fV                   =   0.0f;
        CurrentStrip_05[1].fBaseAlpha           =   0.25f;
        CurrentStrip_05[1].fBaseRed             =   0.55f;
        CurrentStrip_05[1].fBaseGreen           =   0.87f;
        CurrentStrip_05[1].fBaseBlue            =   0.96f;

        CurrentStrip_05[2].ParamControlWord     = KM_VERTEXPARAM_NORMAL;
        CurrentStrip_05[2].fX                   = cos(Angle) * 50.0f + 390.0f;
        CurrentStrip_05[2].fY                   = sin(Angle) * 50.0f + 370.0f;
        CurrentStrip_05[2].u.fZ                 =  21.0f;
        CurrentStrip_05[2].fU                   =   1.0f;
        CurrentStrip_05[2].fV                   =   1.0f;
        CurrentStrip_05[2].fBaseAlpha           =   0.25f;
        CurrentStrip_05[2].fBaseRed             =   0.55f;
        CurrentStrip_05[2].fBaseGreen           =   0.87f;
        CurrentStrip_05[2].fBaseBlue            =   0.96f;

        CurrentStrip_05[3].ParamControlWord     = KM_VERTEXPARAM_ENDOFSTRIP;
        CurrentStrip_05[3].fX                   = cos(Angle) * 50.0f + 390.0f;
        CurrentStrip_05[3].fY                   = sin(Angle) * 50.0f + 240.0f;
        CurrentStrip_05[3].u.fZ                 =  21.0f;
        CurrentStrip_05[3].fU                   =   1.0f;
        CurrentStrip_05[3].fV                   =   0.0f;
        CurrentStrip_05[3].fBaseAlpha           =   0.25f;
        CurrentStrip_05[3].fBaseRed             =   0.0f;
        CurrentStrip_05[3].fBaseGreen           =   0.15f;
        CurrentStrip_05[3].fBaseBlue            =   0.73f;

        /* NOTE: We can keep adding vertices, even past an ENDOFSTRIP flag - see below. */
        CurrentStrip_05[4].ParamControlWord     = KM_VERTEXPARAM_NORMAL;
        CurrentStrip_05[4].fX                   = cos(Angle) * 50.0f + 330.0f;
        CurrentStrip_05[4].fY                   = sin(Angle) * 50.0f + 305.0f;
        CurrentStrip_05[4].u.fZ                 =  20.0f;
        CurrentStrip_05[4].fU                   =   0.0f;
        CurrentStrip_05[4].fV                   =   1.0f;
        CurrentStrip_05[4].fBaseAlpha           =   0.75f;
        CurrentStrip_05[4].fBaseRed             =   0.0f;
        CurrentStrip_05[4].fBaseGreen           =   0.15f;
        CurrentStrip_05[4].fBaseBlue            =   0.73f;

        CurrentStrip_05[5].ParamControlWord     = KM_VERTEXPARAM_NORMAL;
        CurrentStrip_05[5].fX                   = cos(Angle) * 50.0f + 330.0f;
        CurrentStrip_05[5].fY                   = sin(Angle) * 50.0f + 175.0f;
        CurrentStrip_05[5].u.fZ                 =  20.0f;
        CurrentStrip_05[5].fU                   =   0.0f;
        CurrentStrip_05[5].fV                   =   0.0f;
        CurrentStrip_05[5].fBaseAlpha           =   0.75f;
        CurrentStrip_05[5].fBaseRed             =   0.55f;
        CurrentStrip_05[5].fBaseGreen           =   0.87f;
        CurrentStrip_05[5].fBaseBlue            =   0.96f;

        CurrentStrip_05[6].ParamControlWord     = KM_VERTEXPARAM_NORMAL;
        CurrentStrip_05[6].fX                   = cos(Angle) * 50.0f + 470.0f;
        CurrentStrip_05[6].fY                   = sin(Angle) * 50.0f + 305.0f;
        CurrentStrip_05[6].u.fZ                 =  20.0f;
        CurrentStrip_05[6].fU                   =   1.0f;
        CurrentStrip_05[6].fV                   =   1.0f;
        CurrentStrip_05[6].fBaseAlpha           =   0.75f;
        CurrentStrip_05[6].fBaseRed             =   0.55f;
        CurrentStrip_05[6].fBaseGreen           =   0.87f;
        CurrentStrip_05[6].fBaseBlue            =   0.96f;

        CurrentStrip_05[7].ParamControlWord     = KM_VERTEXPARAM_ENDOFSTRIP;
        CurrentStrip_05[7].fX                   = cos(Angle) * 50.0f + 470.0f;
        CurrentStrip_05[7].fY                   = sin(Angle) * 50.0f + 175.0f;
        CurrentStrip_05[7].u.fZ                 =  20.0f;
        CurrentStrip_05[7].fU                   =   1.0f;
        CurrentStrip_05[7].fV                   =   0.0f;
        CurrentStrip_05[7].fBaseAlpha           =   0.75f;
        CurrentStrip_05[7].fBaseRed             =   0.0f;
        CurrentStrip_05[7].fBaseGreen           =   0.15f;
        CurrentStrip_05[7].fBaseBlue            =   0.73f;

        /* NOTE: A lot of context switching and setup can be avoided by providing           */
        /*       several strips of the same type in kmSetVertex() calls without starting    */
        /*       a new strip.  Don't call kmStartVertexStrip() redundantly.                 */
        for (i = 0; i <= 7; i++)
            kmSetVertex (&VertexBufferDesc, &CurrentStrip_05[i],
            	KM_VERTEXTYPE_05, sizeof (KMVERTEX_05));

        /* kmEndStrip() skipped. */

        /* End the first (and only) pass. */
        kmEndPass (&VertexBufferDesc);

        /* Tell Kamui2 to transfer remaining vertices to the TA and begin rendering. */
        kmRender (KM_RENDER_NOFLIP);

        /* Finish the scene. */
        kmEndScene (&kmsc);

        /* Reduce the region array for kmRenderRect() to the size specified. */
        kmSetRegionClipping (0, 0, ((640/32/2) - 1), ((480/32) - 1));

        /* Clip pixels to the bounding box provided (occurs at final stage of render). */
        kmSetPixelClipping (0, 240, 320, 480);

        /* Tell Kamui2 to start accepting polygon data for a new scene. */
        kmBeginScene (&kmsc);

        /* Start the first pass (for multipass rendering). */
        kmBeginPass (&VertexBufferDesc);

/* -------------------> Draw Quadrant 3 -------------------> */
        /* Set a user clipping region (to the nearest 32x32 tile). */
        /* May be specified multiple times per frame. */
        {
            KMRECT  ClipArea = {0, (480/32/2), ((640/32/2) - 1), (480/32)};

            kmSetUserClipping (&VertexBufferDesc, KM_USERCLIP_DISABLE,
                KM_OPAQUE_POLYGON, &ClipArea);

            kmSetUserClipping (&VertexBufferDesc, KM_USERCLIP_DISABLE,
                KM_TRANS_POLYGON, &ClipArea);
        }

        /* Start rendering opaque color strips. */
        kmStartStrip (&VertexBufferDesc, &StripHead_01);

        /* Set the vertices in the current strip to draw a colorful square. */
        CurrentStrip_01[0].ParamControlWord     = KM_VERTEXPARAM_NORMAL;
        CurrentStrip_01[0].fX                   = cos(Angle) * 50.0f + ((float) Count) * 2.0f;
        CurrentStrip_01[0].fY                   = sin(Angle) * 50.0f + 305.0f;
        CurrentStrip_01[0].u.fZ                 =  10.0f;
        CurrentStrip_01[0].fBaseAlpha           =   1.0f;
        CurrentStrip_01[0].fBaseRed             =   1.0f;
        CurrentStrip_01[0].fBaseGreen           =   0.0f;
        CurrentStrip_01[0].fBaseBlue            =   0.0f;

        CurrentStrip_01[1].ParamControlWord     = KM_VERTEXPARAM_NORMAL;
        CurrentStrip_01[1].fX                   = cos(Angle) * 50.0f + ((float) Count) * 2.0f;
        CurrentStrip_01[1].fY                   = sin(Angle) * 50.0f + 175.0f;
        CurrentStrip_01[1].u.fZ                 =  10.0f;
        CurrentStrip_01[1].fBaseAlpha           =   1.0f;
        CurrentStrip_01[1].fBaseRed             =   0.0f;
        CurrentStrip_01[1].fBaseGreen           =   1.0f;
        CurrentStrip_01[1].fBaseBlue            =   0.0f;

        CurrentStrip_01[2].ParamControlWord     = KM_VERTEXPARAM_NORMAL;
        CurrentStrip_01[2].fX                   = cos(Angle) * 50.0f + ((float) Count) * 2.0f + 300.0f;
        CurrentStrip_01[2].fY                   = sin(Angle) * 50.0f + 305.0f;
        CurrentStrip_01[2].u.fZ                 =  10.0f;
        CurrentStrip_01[2].fBaseAlpha           =   1.0f;
        CurrentStrip_01[2].fBaseRed             =   0.0f;
        CurrentStrip_01[2].fBaseGreen           =   0.0f;
        CurrentStrip_01[2].fBaseBlue            =   1.0f;

        CurrentStrip_01[3].ParamControlWord     = KM_VERTEXPARAM_ENDOFSTRIP;
        CurrentStrip_01[3].fX                   = cos(Angle) * 50.0f + ((float) Count) * 2.0f + 300.0f;
        CurrentStrip_01[3].fY                   = sin(Angle) * 50.0f + 175.0f;
        CurrentStrip_01[3].u.fZ                 =  10.0f;
        CurrentStrip_01[3].fBaseAlpha           =   1.0f;
        CurrentStrip_01[3].fBaseRed             =   0.0f;
        CurrentStrip_01[3].fBaseGreen           =   0.0f;
        CurrentStrip_01[3].fBaseBlue            =   0.0f;

        for (i=0; i<=3; i++)
            kmSetVertex (&VertexBufferDesc, &CurrentStrip_01[i],
                KM_VERTEXTYPE_01, sizeof (KMVERTEX_01));

        /* kmEndStrip() is a dummy function - Don't bother calling it. */

        /* End the first (and only) pass. */
        kmEndPass (&VertexBufferDesc);

        /* Transfer remaining vertices to the TA and begin render to the clip region. */
        kmRenderRect (KM_RENDER_NOFLIP);

        /* Finish the scene. */
        kmEndScene (&kmsc);

        /* Clip pixels to the bounding box provided (occurs at final stage of render). */
        kmSetPixelClipping (320, 240, 640, 480);

        /* Tell Kamui2 to start accepting polygon data for a new scene. */
        kmBeginScene (&kmsc);

        /* Start the first pass (for multipass rendering). */
        kmBeginPass (&VertexBufferDesc);

/* -------------------> Draw Quadrant 4 -------------------> */
        /* Set a user clipping region (to the nearest 32x32 tile). */
        /* May be specified multiple times per frame. */
        {
            KMRECT  ClipArea = {(640/32/2), (480/32/2), (640/32), (480/32)};

            kmSetUserClipping (&VertexBufferDesc, KM_USERCLIP_DISABLE,
                KM_OPAQUE_POLYGON, &ClipArea);

            kmSetUserClipping (&VertexBufferDesc, KM_USERCLIP_DISABLE,
                KM_TRANS_POLYGON, &ClipArea);
        }

        /* Start rendering opaque color strips. */
        kmStartStrip (&VertexBufferDesc, &StripHead_01);

        /* Set the vertices in the current strip to draw a colorful square. */
        CurrentStrip_01[0].ParamControlWord     = KM_VERTEXPARAM_NORMAL;
        CurrentStrip_01[0].fX                   = cos(Angle) * 50.0f + 250.0f;
        CurrentStrip_01[0].fY                   = sin(Angle) * 50.0f + 305.0f;
        CurrentStrip_01[0].u.fZ                 =   9.0f;
        CurrentStrip_01[0].fBaseAlpha           =   1.0f;
        CurrentStrip_01[0].fBaseRed             =   0.0f;
        CurrentStrip_01[0].fBaseGreen           =   0.0f;
        CurrentStrip_01[0].fBaseBlue            =   0.0f;

        CurrentStrip_01[1].ParamControlWord     = KM_VERTEXPARAM_NORMAL;
        CurrentStrip_01[1].fX                   = cos(Angle) * 50.0f + 250.0f;
        CurrentStrip_01[1].fY                   = sin(Angle) * 50.0f + 175.0f;
        CurrentStrip_01[1].u.fZ                 =   9.0f;
        CurrentStrip_01[1].fBaseAlpha           =   1.0f;
        CurrentStrip_01[1].fBaseRed             =   1.0f;
        CurrentStrip_01[1].fBaseGreen           =   0.0f;
        CurrentStrip_01[1].fBaseBlue            =   0.0f;

        CurrentStrip_01[2].ParamControlWord     = KM_VERTEXPARAM_NORMAL;
        CurrentStrip_01[2].fX                   = cos(Angle) * 50.0f + 390.0f;
        CurrentStrip_01[2].fY                   = sin(Angle) * 50.0f + 305.0f;
        CurrentStrip_01[2].u.fZ                 =   9.0f;
        CurrentStrip_01[2].fBaseAlpha           =   1.0f;
        CurrentStrip_01[2].fBaseRed             =   1.0f;
        CurrentStrip_01[2].fBaseGreen           =   0.0f;
        CurrentStrip_01[2].fBaseBlue            =   0.0f;

        CurrentStrip_01[3].ParamControlWord     = KM_VERTEXPARAM_ENDOFSTRIP;
        CurrentStrip_01[3].fX                   = cos(Angle) * 50.0f + 390.0f;
        CurrentStrip_01[3].fY                   = sin(Angle) * 50.0f + 175.0f;
        CurrentStrip_01[3].u.fZ                 =   9.0f;
        CurrentStrip_01[3].fBaseAlpha           =   1.0f;
        CurrentStrip_01[3].fBaseRed             =   0.0f;
        CurrentStrip_01[3].fBaseGreen           =   0.0f;
        CurrentStrip_01[3].fBaseBlue            =   0.0f;

        for (i=0; i<=3; i++)
            kmSetVertex (&VertexBufferDesc, &CurrentStrip_01[i],
                KM_VERTEXTYPE_01, sizeof (KMVERTEX_01));

        /* kmEndStrip() is a dummy function - Don't bother calling it. */

        /* End the first (and only) pass. */
        kmEndPass (&VertexBufferDesc);

        /* Transfer remaining vertices to the TA, render, and enqueue a page flip. */
        kmRender (KM_RENDER_FLIP);

        /* Finish the scene. */
        kmEndScene (&kmsc);

        /* Ping the peripheral server. */
        pdExecPeripheralServer();
	}

    sbExitSystem();
}