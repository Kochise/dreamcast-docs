/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    perstore.h

Abstract:

    This file defines the Persistent Storage interfaces
    (IFlashDevice and IFlashFile) and their associated typedefs,
    defines, etc.

-------------------------------------------------------------------*/

#ifndef __PERSTORE_H_INCLUDED__
#define __PERSTORE_H_INCLUDED__


#ifdef __cplusplus
extern "C"{
#endif 

/* Header file for IUnknown interface */
#include "unknwn.h"

/* Forward Declarations */ 
typedef interface IFlashDevice IFlashDevice;
typedef interface IFlashFile IFlashFile;


//
// FSDATETIME is used to represent the creation date/time 
// of flash devices and flash files
//
typedef struct _FSDATETIME
{
    // Shown are values for 5:30 PM, Friday, June 26, 1998
    BYTE    bYearTop;       // 19
    BYTE    bYearBottom;    // 98
    BYTE    bMonth;         // 6
    BYTE    bDay;           // 26
    BYTE    bHour;          // 17
    BYTE    bMinute;        // 30
    BYTE    bDayOfWeek;     // 5    (DoW = 0..6, with 0=Sunday)
    BYTE    bReserved;      // 0
} FSDATETIME, *LPFSDATETIME;

typedef const FSDATETIME *LPCFSDATETIME;


//-------------------------------------------------------------------
//-------------------------------------------------------------------
//
//                      Support for Flash Devices
//
//-------------------------------------------------------------------
//-------------------------------------------------------------------

//
// FSARGB4 is the Flash Store's way of representing 
// alpha+RGB (4 bits each).  The MAKE_ARGB4 macro is used
// to construct FSARGB4 values.  Note that the parameters
// a, r, g, and b must all fall in the range 0..15.
//
typedef WORD FSARGB4;

#define MAKE_FSARGB4(a, r, g, b)   \
    ((FSARGB4)(((a) << 12) | ((r) << 8) | ((g) << 4) | (b)))

//
// FSARGB8 is the same as FSARGB4, except ARGB are 8 bits each.
// The parameters a, r, g, and b must all fall in the range 0..255.
//
typedef DWORD FSARGB8;

#define MAKE_FSARGB8(a, r, g, b)   \
    ((FSARGB8)(((a) << 24) | ((r) << 16) | ((g) << 8) | (b)))

//
// FSVOLUMEICON describes the icon to be associated with the
// volume.  The volume icon can only be set when the device
// is formatted.
//
// The volume icon can either just be a byte value that selects
// one of 256 predefined icons, or can actually define a 
// custom monochrome image (and, optionally, a custom
// color image as well).
//
// To select a predefined icon, just set fUsePredefinedIcon to
// TRUE and bPredefinedIcon to a value in the range 0..255.
//
// To define a custom icon (or icons), set fUsePredefinedIcon
// to FALSE.  When this is done, a monochrome icon is required.  
// The image is stored left to right, top to bottom, with 8 
// pixels stored per byte.  The least significant bit is the 
// rightmost pixel in the group of 8, and the most significant 
// bit is the leftmost pixel.
//
// After you've defined the custom monochrome icon, you can
// optionally add a palettized ARGB4444 icon by setting fHasColor 
// to TRUE.  Here, each byte of pixelsColor stores 2 pixels, with 
// the 4 low order bits being the right pixel of the pair, and the 
// 4 high order bits being the left pixel.  The palette is 16 entries 
// long, each entry being one ARGB4444 color.  See the 
// MAKE_FSARGB4 macro for details on building FSARGB4 values.
//
typedef struct _FSVOLUMEICON
{
    // If TRUE, use bPredefinedIcon, else imagedata
    BOOL    fUsePredefinedIcon;

    union
    {
        // Selects predefined icon 0..255
        BYTE    bPredefinedIcon;

        struct
        {
            // Monochrome image data is 32x32, 1bpp.  Note that
            // pixelsMonochrome[y][x] actually contains 8 pixels,
            // (x*8, y) through (x*8+7, y).
            BYTE    pixelsMonochrome[32][32/8];
            
            // If FALSE, following fields ignored
            BOOL    fHasColor;

            // 16-color palette (ARGB4444)
            FSARGB4 palette[16];

            // Color image data is 32x32, 4bpp palettized.  Note 
            // that pixelsColor[y][x] actually contains 2 pixels,
            // (x*2, y) and (x*2+1, y).
            BYTE    pixelsColor[32][32/2];
        } imagedata;
    };
} FSVOLUMEICON;

//
// FSDEVICEDESC is used when creating and querying flash devices
//
typedef struct _FSDEVICEDESC
{
    DWORD        dwSize;
    DWORD        dwFlags;
    DWORD        dwPortNumber;
    DWORD        dwDeviceNumber;
    DWORD        dwTotalBlocks;
    DWORD        dwFreeBlocks;
    DWORD        dwBlockSize;
    FSARGB8      colorVMS;          // VMS display color
    FSVOLUMEICON fsvolumeicon;
    FSDATETIME   fsdatetimeCreated;
} FSDEVICEDESC, *LPFSDEVICEDESC;

typedef const FSDEVICEDESC *LPCFSDEVICEDESC;

//
// Flags for FSDEVICEDESC.dwFlags
//
#define FSDD_PORT_NUMBER         0x00000001
#define FSDD_DEVICE_NUMBER       0x00000002
#define FSDD_TOTAL_BLOCKS        0x00000004
#define FSDD_FREE_BLOCKS         0x00000008
#define FSDD_BLOCK_SIZE          0x00000010
#define FSDD_COLOR_VMS           0x00000020
#define FSDD_VOLUME_ICON         0x00000040
#define FSDD_DATE_TIME_CREATED   0x00000080

#define FSDD_ALL                   \
             (FSDD_PORT_NUMBER   | \
              FSDD_DEVICE_NUMBER | \
              FSDD_TOTAL_BLOCKS  | \
              FSDD_FREE_BLOCKS   | \
              FSDD_BLOCK_SIZE    | \
              FSDD_COLOR_VMS     | \
              FSDD_VOLUME_ICON   | \
              FSDD_DATE_TIME_CREATED)


//-------------------------------------------------------------------
//-------------------------------------------------------------------
//
//                      Support for Flash Files
//
//-------------------------------------------------------------------
//-------------------------------------------------------------------

//
// MAX_FLASH_FILE_NAME is the maximum length of a flash
// file name (12 single-byte characters stored on
// the device plus a trailing NUL when in memory).
//
#define MAX_FLASH_FILE_NAME (12 + 1)

//
// MAX_VMS_COMMENT is the maximum length of a flash file's
// "VMS Comment" (16 single-byte characters stored on
// the device plus a trailing NUL when in memory).
//
#define MAX_VMS_COMMENT (16 + 1)

//
// MAX_BOOT_ROM_COMMENT is the maximum length of a flash file's
// "Boot ROM" (16 double-byte characters stored on
// the device plus a trailing NUL when in memory).
//
#define MAX_BOOT_ROM_COMMENT (32 + 1)

//
// MAX_GAME_NAME is the maximum length of a flash file's
// "Game Name" (16 single-byte characters stored on
// the device plus a trailing NUL when in memory).
//
#define MAX_GAME_NAME (16 + 1)

//
// FSFILEICON describes the (required) file icon associated with
// the file.  The icon is palettized ARGB4444, 32x32, and can
// have between 1 and 3 frames of animation.
//
typedef struct _FSFILEICON
{
    BYTE    bAnimationFrames;       // Number of frames of icon animation (1-3)
    BYTE    bAnimationDelay;        // Specified in 1/30th of a second
    FSARGB4 palette[16];            // 16-entry ARGB4444 palette
    BYTE    pixelsFrame1[32][32/2]; // 32x32, 4bpp palettized icon pixel data.
                                    // Note that pixelsFrame1[y][x] actually 
                                    // contains 2 pixels, (x*2, y) and (x*2+1, y)
    BYTE    pixelsFrame2[32][32/2]; // Ditto, second frame (optional)
    BYTE    pixelsFrame3[32][32/2]; // Ditto, third frame (optional)
} FSFILEICON, *LPFSFILEICON;

typedef const FSFILEICON *LPCFSFILEICON;


//
// FSVISDATA describes the (optional) visual data associated with
// the file.  This graphical type has three different representations:
//
//      Type A: 72x56, 16bpp direct color (no palette)
//
//      Type B: 72x56, 8bpp palettized, 256-entry palette of ARGB4444
//
//      Type C: 72x56, 4bpp palettized, 16-entry palette of ARGB4444
//

#define FSVISDATA_NONE      ((BYTE)0)
#define FSVISDATA_TYPE_A    ((BYTE)1)
#define FSVISDATA_TYPE_B    ((BYTE)2)
#define FSVISDATA_TYPE_C    ((BYTE)3)

typedef struct _FSVISDATA
{
    //
    // bVisualType can be FSVISDATA_TYPE_x (where x = A, B, or C)
    // and determines which member of the union is valid.
    //
    BYTE    bVisualType;

    union
    {
        struct
        {
            FSARGB4 pixels[56][72];     // Each FSARGB4 directly encodes one pixel:
                                        // pixels[y][x] is pixel (x, y)
        } typeA;

        struct
        {
            FSARGB4 palette[256];       // 256-entry ARGB4444 palette
            BYTE    pixels[56][72];     // Each BYTE is one palettized pixel:
                                        // pixels[y][x] is pixel (x, y)
        } typeB;

        struct
        {
            FSARGB4 palette[16];        // 16-entry ARGB4444 palette
            BYTE    pixels[56][72/2];   // Each BYTE encodes two 4bpp palettized
                                        // pixels: pixels[y][x] contains  
                                        // pixels (x*2, y) and (x*2+1, y)
        } typeC;
    };    
    
} FSVISDATA, *LPFSVISDATA;

typedef const FSVISDATA *LPCFSVISDATA;

//
// FSFILEDESC is used when creating and querying files
//
typedef struct _FSFILEDESC
{
    DWORD       dwSize;
    DWORD       dwFlags;
    DWORD       dwBlocksUsed;       // Total blocks consumed on device
    DWORD       dwTotalBytes;       // Bytes available to application
    DWORD       dwBytesRequired;    // IN param only (cannot be queried for)
    char        szFileName[MAX_FLASH_FILE_NAME];
    char        szVMSComment[MAX_VMS_COMMENT];
    char        szBootROMComment[MAX_BOOT_ROM_COMMENT];
    char        szGameName[MAX_GAME_NAME];
    BYTE        bStatus;            // FS_STATUS_DATA_FILE or FS_STATUS_EXE_FILE
    BYTE        bCopy;              // FS_COPY_ENABLED or FS_COPY_DISABLED
    FSFILEICON  fsfileicon;         // File icon (required)
    FSVISDATA   fsvisdata;          // Visual data (optional)
    FSDATETIME  fsdatetimeCreated;
} FSFILEDESC, *LPFSFILEDESC;

typedef const FSFILEDESC *LPCFSFILEDESC;

//
// Flags for FSFILEDESC.dwFlags
//
#define FSFD_BLOCKS_USED        0x00000001
#define FSFD_TOTAL_BYTES        0x00000002
#define FSFD_BYTES_REQUIRED     0x00000004
#define FSFD_FILE_NAME          0x00000008
#define FSFD_VMS_COMMENT        0x00000010
#define FSFD_BOOT_ROM_COMMENT   0x00000020
#define FSFD_GAME_NAME          0x00000040
#define FSFD_STATUS             0x00000080
#define FSFD_COPY               0x00000100
#define FSFD_FILEICON           0x00000200
#define FSFD_VISDATA            0x00000400
#define FSFD_DATE_TIME_CREATED  0x00000800
#define FSFD_CRC                0x00001000

//
// Use FSFD_CREATE_FILE (and set all associated fields) when
// creating a file.
//
// You may optionally OR in:
//   o FSFD_VISDATA if your FSFILEDESC also contains a valid FSVISDATA
//   o FSFD_CRC if you want this file to be CRC-checked.
//
#define FSFD_CREATE_FILE              \
             (FSFD_BYTES_REQUIRED   | \
              FSFD_FILE_NAME        | \
              FSFD_VMS_COMMENT      | \
              FSFD_BOOT_ROM_COMMENT | \
              FSFD_GAME_NAME        | \
              FSFD_STATUS           | \
              FSFD_COPY             | \
              FSFD_FILEICON)

//
// Use FSFD_FULL_QUERY to have IFlashDevice::GetDeviceDesc return
// all retrievable device characteristics.
//
#define FSFD_FULL_QUERY               \
             (FSFD_BLOCKS_USED      | \
              FSFD_TOTAL_BYTES      | \
              FSFD_FILE_NAME        | \
              FSFD_VMS_COMMENT      | \
              FSFD_BOOT_ROM_COMMENT | \
              FSFD_GAME_NAME        | \
              FSFD_STATUS           | \
              FSFD_COPY             | \
              FSFD_FILEICON         | \
              FSFD_VISDATA          | \
              FSFD_DATE_TIME_CREATED)

//
// Values for FSFILEDESC.bStatus
//
#define FS_STATUS_DATA_FILE  ((BYTE)0x33)
#define FS_STATUS_EXE_FILE   ((BYTE)0xcc)

//
// Values for FSFILEDESC.bCopy
//
#define FS_COPY_ENABLED      ((BYTE)0x00)   // File can be copied
#define FS_COPY_DISABLED     ((BYTE)0xff)   // File cannot be copied

//
// FSFILEID is an opaque type representing a flash file.
// It is passed to the use via the LPFSENUMFILESCALLBACK callback,
// and can be passed to IFlashDevice::OpenFlashFile to create an
// IFlashFile on that file.
//
typedef DWORD FSFILEID;

//
// LPFSENUMFILESCALLBACK is the callback used by IFlashDevice::EnumFiles
//
typedef BOOL (*LPFSENUMFILESCALLBACK)(
                     IFlashDevice  *pIFlashDevice,
                     FSFILEID       fsfileid,
                     LPCFSFILEDESC  lpcfsfiledesc,
                     void          *pvContext);


// -------------------------------------------------------------------
// -------------------------------------------------------------------
//
//                       Interface Definitions
//
// -------------------------------------------------------------------
// -------------------------------------------------------------------


// -------------------------------------------------------------------
//
// IFlashDevice: Interface that allows access to a particular attached
// flash device
//
// -------------------------------------------------------------------

#ifndef __IFlashDevice_INTERFACE_DEFINED__
#define __IFlashDevice_INTERFACE_DEFINED__

EXTERN_C const IID IID_IFlashDevice;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("59C842A1-C2B2-11d1-BB4D-00C04FC324BC")
    IFlashDevice : public IUnknown
    {
    public:
        //
        // Returns S_OK if the device is already formatted, an error if not.
        //
        virtual HRESULT STDMETHODCALLTYPE 
        CheckFormat(void) = 0;
        
        //
        // Format the device according to the given FSDEVICEDESC structure
        //
        virtual HRESULT STDMETHODCALLTYPE 
        DoFormat( 
            /* [in] */ LPCFSDEVICEDESC lpcfsdevicedesc
            ) = 0;
        
        //
        // Fills in a FSDEVICEDESC that describes the current device.
        // On entry, FSDEVICEDESC.dwSize and .dwFlags must be set.
        // On exit, fields (as requested by .dwFlags) will be set.
        //
        virtual HRESULT STDMETHODCALLTYPE 
        GetDeviceDesc( 
            /* [out][in] */ LPFSDEVICEDESC lpfsdevicedesc
            ) = 0;
        
        //
        // Calls the user-defined callback pfnEnumFiles for each 
        // existing flash file on this device (or until the callback 
        // returns FALSE).
        //
        virtual HRESULT STDMETHODCALLTYPE 
        EnumFlashFiles( 
            /* [in] */ LPFSENUMFILESCALLBACK pfnEnumFiles,
            /* [in] */ void *pvContext
            ) = 0;
        
        //
        // Calls the user-defined callback pfnEnumFiles for each 
        // existing flash file on this device (or until the callback 
        // returns FALSE).
        //
        virtual HRESULT STDMETHODCALLTYPE 
        FastEnumFlashFiles( 
            /* [in] */ LPFSENUMFILESCALLBACK pfnEnumFiles,
            /* [in] */ void *pvContext
            ) = 0;
        
        //
        // Returns an IFlashFile associated with a newly-created 
        // file that is described by the FSFILEDESC.  All appropriate
        // fields of the FSFILEDESC must be set.
        //
        virtual HRESULT STDMETHODCALLTYPE 
        CreateFlashFile( 
            /* [out] */ IFlashFile **ppIFlashFile,
            /* [out][in] */ LPFSFILEDESC lpfsfiledesc
            ) = 0;
        
        //
        // Returns an IFlashFile for the file identified by FSFILEID,
        // or an error if no such file exists on this device.
        //
        virtual HRESULT STDMETHODCALLTYPE 
        OpenFlashFile( 
            /* [out] */ IFlashFile **ppIFlashFile,
            /* [in] */ FSFILEID fsfileid
            ) = 0;
        //
        // Returns an IFlashFile for the file named pFileName,
        // or an error if no such file exists on this device.
        //
        virtual HRESULT STDMETHODCALLTYPE 
        OpenFlashFileByName( 
            /* [out] */ IFlashFile **ppIFlashFile,
            /* [in] */ LPSTR pFileName
            ) = 0;

        //
        // Write all cached data to the device
        //
        virtual HRESULT STDMETHODCALLTYPE 
        Flush( ) = 0;

        //
        // Set the volume icon
        //
        virtual HRESULT STDMETHODCALLTYPE 
        SetVolumeIcon( 
            /* [in] */ FSVOLUMEICON *pfsvolumeicon
            ) = 0;

    };
    
#else   /* C style interface */

    typedef struct IFlashDeviceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT (STDMETHODCALLTYPE *QueryInterface)( 
            IFlashDevice * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject
            );
        
        ULONG (STDMETHODCALLTYPE *AddRef)( 
            IFlashDevice * This
            );
        
        ULONG (STDMETHODCALLTYPE *Release)( 
            IFlashDevice * This
            );
        
        HRESULT (STDMETHODCALLTYPE *CheckFormat)( 
            IFlashDevice * This
            );
        
        HRESULT (STDMETHODCALLTYPE *DoFormat)( 
            IFlashDevice * This,
            /* [in] */ LPCFSDEVICEDESC lpcfsdevicedesc
            );
        
        HRESULT (STDMETHODCALLTYPE *GetDeviceDesc)( 
            IFlashDevice * This,
            /* [out][in] */ LPFSDEVICEDESC lpfsdevicedesc
            );
        
        HRESULT (STDMETHODCALLTYPE *EnumFlashFiles)( 
            IFlashDevice * This,
            /* [in] */ LPFSENUMFILESCALLBACK pfnEnumFiles,
            /* [in] */ void *pvContext
            );
        
        HRESULT (STDMETHODCALLTYPE *FastEnumFlashFiles)( 
            IFlashDevice * This,
            /* [in] */ LPFSENUMFILESCALLBACK pfnEnumFiles,
            /* [in] */ void *pvContext
            );
        
        HRESULT (STDMETHODCALLTYPE *CreateFlashFile)( 
            IFlashDevice * This,
            /* [out] */ IFlashFile **ppIFlashFile,
            /* [out][in] */ LPFSFILEDESC lpfsfiledesc
            );
        
        HRESULT (STDMETHODCALLTYPE *OpenFlashFile)( 
            IFlashDevice * This,
            /* [out] */ IFlashFile **ppIFlashFile,
            /* [in] */ FSFILEID fsfileid
            );
        
        HRESULT (STDMETHODCALLTYPE *OpenFlashFileByName)( 
            IFlashDevice * This,
            /* [out] */ IFlashFile **ppIFlashFile,
            /* [in] */ LPSTR pName
            );

        HRESULT (STDMETHODCALLTYPE *Flush)( 
            IFlashDevice * This
            );

        HRESULT (STDMETHODCALLTYPE *SetVolumeIcon)( 
            IFlashDevice * This,
            /* [in] */ FSVOLUMEICON *pfsvolumeicon
            );
        END_INTERFACE
    } IFlashDeviceVtbl;

    interface IFlashDevice
    {
        CONST_VTBL struct IFlashDeviceVtbl *lpVtbl;
    };

    
#ifdef COBJMACROS

#define IFlashDevice_QueryInterface(This,riid,ppvObject)    \
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IFlashDevice_AddRef(This)   \
    (This)->lpVtbl -> AddRef(This)

#define IFlashDevice_Release(This)  \
    (This)->lpVtbl -> Release(This)

#define IFlashDevice_CheckFormat(This)  \
    (This)->lpVtbl -> CheckFormat(This)

#define IFlashDevice_DoFormat(This,lpcfsdevicedesc) \
    (This)->lpVtbl -> DoFormat(This,lpcfsdevicedesc)

#define IFlashDevice_GetDeviceDesc(This,lpfsdevicedesc) \
    (This)->lpVtbl -> GetDeviceDesc(This,lpfsdevicedesc)

#define IFlashDevice_EnumFlashFiles(This,pfnEnumFiles,pvContext)    \
    (This)->lpVtbl -> EnumFlashFiles(This,pfnEnumFiles,pvContext)

#define IFlashDevice_FastEnumFlashFiles(This,pfnEnumFiles,pvContext)    \
    (This)->lpVtbl -> FastEnumFlashFiles(This,pfnEnumFiles,pvContext)

#define IFlashDevice_CreateFlashFile(This,ppIFlashFile,lpfsfiledesc)    \
    (This)->lpVtbl -> CreateFlashFile(This,ppIFlashFile,lpfsfiledesc)

#define IFlashDevice_OpenFlashFile(This,ppIFlashFile,fsfileid)  \
    (This)->lpVtbl -> OpenFlashFile(This,ppIFlashFile,fsfileid)

#define IFlashDevice_OpenFlashFileByName(This,ppIFlashFile,pFileName)  \
    (This)->lpVtbl -> OpenFlashFileByName(This,ppIFlashFile,pFileName)

#define IFlashDevice_Flush(This)  \
    (This)->lpVtbl -> Flush(This)

#define IFlashDevice_SetVolumeIcon(This,pfsvolumeicon)  \
    (This)->lpVtbl -> SetVolumeIcon(This,pfsvolumeicon)

#endif /* COBJMACROS */

#endif /* C style interface */

#endif /* __IFlashDevice_INTERFACE_DEFINED__ */

typedef IFlashDevice *LPFLASHDEVICE;



// -------------------------------------------------------------------
//
// IFlashFile: Interface that allows access to a particular file on
// an attached flash device
//
// -------------------------------------------------------------------


#ifndef __IFlashFile_INTERFACE_DEFINED__
#define __IFlashFile_INTERFACE_DEFINED__

EXTERN_C const IID IID_IFlashFile;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("59C842A2-C2B2-11d1-BB4D-00C04FC324BC")
    IFlashFile : public IUnknown
    {
    public:
        //
        // Fills in a FSFILEDESC that describes the current file.
        // On entry, FSFILEDESC.dwSize and .dwFlags must be set.
        // On exit, fields (as requested by .dwFlags) will be set.
        //
        virtual HRESULT STDMETHODCALLTYPE 
        GetFileDesc( 
            /* [out][in] */ LPFSFILEDESC lpfsfiledesc
            ) = 0;
        
        //
        // Reads data from the file and writes it to pbData.
        // If the read would have gone past EOF, the call fails 
        // and no bytes are read.
        //
        virtual HRESULT STDMETHODCALLTYPE 
        Read( 
            /* [in] */ DWORD dwStart,
            /* [in] */ DWORD dwNumBytes,
            /* [out] */ BYTE *pbData
            ) = 0;
        
        //
        // Writes the given data to the file.
        // If the write would have gone past EOF, the call fails 
        // and no bytes are written.
        //
        virtual HRESULT STDMETHODCALLTYPE 
        Write( 
            /* [in] */ DWORD dwStart,
            /* [in] */ DWORD dwNumBytes,
            /* [in] */ BYTE *pbData
            ) = 0;
        
        //
        // Deletes the file.  All other operations on this file will
        // fail (except AddRef/Release/QI methods of IUnknown)
        //
        virtual HRESULT STDMETHODCALLTYPE 
        Delete(void) = 0;

		//
        // Writes all cached data associated with this file to the device
        //
        virtual HRESULT STDMETHODCALLTYPE 
        Flush(void) = 0;
    };
    
#else   /* C style interface */

    typedef struct IFlashFileVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT (STDMETHODCALLTYPE *QueryInterface)( 
            IFlashFile * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject
            );
        
        ULONG (STDMETHODCALLTYPE *AddRef)( 
            IFlashFile * This
            );
        
        ULONG (STDMETHODCALLTYPE *Release)( 
            IFlashFile * This
            );
        
        HRESULT (STDMETHODCALLTYPE *GetFileDesc)( 
            IFlashFile * This,
            /* [out][in] */ LPFSFILEDESC lpfsfiledesc
            );
        
        HRESULT (STDMETHODCALLTYPE *Read)( 
            IFlashFile * This,
            /* [in] */ DWORD dwStart,
            /* [in] */ DWORD dwNumBytes,
            /* [out] */ BYTE *pbData
            );
        
        HRESULT (STDMETHODCALLTYPE *Write)( 
            IFlashFile * This,
            /* [in] */ DWORD dwStart,
            /* [in] */ DWORD dwNumBytes,
            /* [in] */ BYTE *pbData
            );
        
        HRESULT (STDMETHODCALLTYPE *Delete)( 
            IFlashFile * This
            );
        
        HRESULT (STDMETHODCALLTYPE *Flush)( 
            IFlashFile * This
            );

        END_INTERFACE
    } IFlashFileVtbl;

    interface IFlashFile
    {
        CONST_VTBL struct IFlashFileVtbl *lpVtbl;
    };
    

#ifdef COBJMACROS

#define IFlashFile_QueryInterface(This,riid,ppvObject)  \
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IFlashFile_AddRef(This) \
    (This)->lpVtbl -> AddRef(This)

#define IFlashFile_Release(This)    \
    (This)->lpVtbl -> Release(This)

#define IFlashFile_GetFileDesc(This,lpfsfiledesc)   \
    (This)->lpVtbl -> GetFileDesc(This,lpfsfiledesc)

#define IFlashFile_Read(This,dwStart,dwNumBytes,pbData) \
    (This)->lpVtbl -> Read(This,dwStart,dwNumBytes,pbData)

#define IFlashFile_Write(This,dwStart,dwNumBytes,pbData)    \
    (This)->lpVtbl -> Write(This,dwStart,dwNumBytes,pbData)

#define IFlashFile_Delete(This) \
    (This)->lpVtbl -> Delete(This)

#define IFlashFile_Flush(This) \
    (This)->lpVtbl -> Flush(This)

#endif /* COBJMACROS */

#endif  /* C style interface */

#endif  /* __IFlashFile_INTERFACE_DEFINED__ */

typedef IFlashFile *LPFLASHFILE;


        

// HRESULT return codes for the Persistent Storage Flash API
#define FACILITY_VMSFLASH                   0x685
#define MAKE_VMSHRESULT(code)               MAKE_HRESULT(1, FACILITY_VMSFLASH, code)

// Success.
#define VMS_OK                                          S_OK    

// Error.  The block cannot be read or written anymore.
#define VMSERR_BADBLOCK                                 MAKE_VMSHRESULT(0x0010)

// Error.  The CRC (cyclic redundancy check) for the data
// in the file does not match the CRC value stored in the
// file header.
#define VMSERR_BADCRC                                   MAKE_VMSHRESULT(0x0018)

// Error.  The device has somehow become corrupted, and 
// is now unusable.
#define VMSERR_BADDEVICE                                MAKE_VMSHRESULT(0x0020)

// Error.  The file being read is corrupt.  Header 
// information is not consistent with the spec.
#define VMSERR_BADFILE                                  MAKE_VMSHRESULT(0x0030)

// Error.  User tried to open/create a file called 
// "ICONDATA_VMS", or some other illegal filename.
#define VMSERR_BADFILENAME                              MAKE_VMSHRESULT(0x0040)

// Error.  Unknown bus error.
#define VMSERR_DEVICEERROR                              MAKE_VMSHRESULT(0x0050)

// Error.  User tried to perform a file operation on a 
// device which is not formatted.
#define VMSERR_DEVICENOTFORMATTED                       MAKE_VMSHRESULT(0x0060)

// Error.  User tried to create a device on a port which 
// does not exist.  Perhaps the VMS Flash device is not 
// plugged in.
#define VMSERR_DEVICENOTFOUND                           MAKE_VMSHRESULT(0x0070)

// Error.  User either tried to create a file with the 
// same name as a file already on the device, or user 
// tried to create an executable file on a device which 
// already has an executable on it.
#define VMSERR_FILEALREADYEXISTS                        MAKE_VMSHRESULT(0x0080)

// Error.  User attempted to open a file which doesn't 
// exist on the device.
#define VMSERR_FILENOTFOUND                             MAKE_VMSHRESULT(0x0090)

// Error.  One of the parameters passed in to the 
// function is invalid.
#define VMSERR_INVALIDPARAM                             E_INVALIDARG // 0x80070057

// Error.  There is not enough free space on the flash 
// device to create the new file which the user is 
// requesting.
#define VMSERR_NOTENOUGHSPACE                           MAKE_VMSHRESULT(0x00A0)

// Error.  The system has run out of memory.
#define VMSERR_OUTOFMEMORY                              E_OUTOFMEMORY // 0x8007000E

// Unknown OS error.
#define VMSERR_UNKNOWN                                  MAKE_VMSHRESULT(0x00B0)

// Error.  User is trying to use the Flash API to access 
// a device which is not supported.  The driver only 
// supports external flash devices with exactly one 
// partition.
#define VMSERR_UNKNOWNDEVICETYPE                        MAKE_VMSHRESULT(0x00C0)

// Error.  The file being created is not a data file or 
// an executable file.
#define VMSERR_UNKNOWNFILETYPE                          MAKE_VMSHRESULT(0x00D0)

// Error.  The read or write operation requested would have
// gone past the end of the file.
#define VMSERR_EOF                                      MAKE_VMSHRESULT(0x00E0)


#ifdef __cplusplus
}
#endif

#endif  // !__PERSTORE_H_INCLUDED__
