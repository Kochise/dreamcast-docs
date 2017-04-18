// -----------------------------------------------------------------------------
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//  Copyright (c) 1995-1998  Microsoft Corporation
//  
// -----------------------------------------------------------------------------
//
//  msacm.h     Audio Compression Manager Public Header File
//
// -----------------------------------------------------------------------------

#ifndef _INC_ACM
#define _INC_ACM        /* #defined if msacm.h has been included */

#if !defined(_INC_MMREG) || (_INC_MMREG < 142)
#ifndef RC_INVOKED
#error MMREG.H version 142 or greater to be included first
#endif
#endif

#ifndef RC_INVOKED
#pragma pack(1)         /* Assume byte packing throughout */
#endif  /* RC_INVOKED */

#ifdef __cplusplus
extern "C" {            /* Assume C declarations for C++ */
#endif  /* __cplusplus */


//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;
//
//
//
//
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;

#ifndef DRV_MAPPER_PREFERRED_INPUT_GET
#define DRV_MAPPER_PREFERRED_INPUT_GET  (DRV_USER + 0)
#endif

#ifndef DRV_MAPPER_PREFERRED_OUTPUT_GET
#define DRV_MAPPER_PREFERRED_OUTPUT_GET (DRV_USER + 2)
#endif


#ifndef DRVM_MAPPER_STATUS
#define DRVM_MAPPER_STATUS              (0x2000)
#endif

#ifndef WIDM_MAPPER_STATUS
#define WIDM_MAPPER_STATUS              (DRVM_MAPPER_STATUS + 0)
#define WAVEIN_MAPPER_STATUS_DEVICE     0
#define WAVEIN_MAPPER_STATUS_MAPPED     1
#define WAVEIN_MAPPER_STATUS_FORMAT     2
#endif

#ifndef WODM_MAPPER_STATUS
#define WODM_MAPPER_STATUS              (DRVM_MAPPER_STATUS + 0)
#define WAVEOUT_MAPPER_STATUS_DEVICE    0
#define WAVEOUT_MAPPER_STATUS_MAPPED    1
#define WAVEOUT_MAPPER_STATUS_FORMAT    2
#endif


//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;
//
//
//
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;
#define ACMAPI              WINAPI

typedef DWORD FOURCC;


//
//  there are four types of 'handles' used by the ACM. the first three
//  are unique types that define specific objects:
//
//  HACMDRIVERID: used to _identify_ an ACM driver. this identifier can be
//  used to _open_ the driver for querying details, etc about the driver.
//
//  HACMDRIVER: used to manage a driver (codec, filter, etc). this handle
//  is much like a handle to other media drivers--you use it to send
//  messages to the converter, query for capabilities, etc.
//
//  HACMSTREAM: used to manage a 'stream' (conversion channel) with the
//  ACM. you use a stream handle to convert data from one format/type
//  to another--much like dealing with a file handle.
//
//
//  the fourth handle type is a generic type used on ACM functions that
//  can accept two or more of the above handle types (for example the
//  acmMetrics and acmDriverID functions).
//
//  HACMOBJ: used to identify ACM objects. this handle is used on functions
//  that can accept two or more ACM handle types.
//
DECLARE_HANDLE(HACMDRIVERID);
typedef HACMDRIVERID       *PHACMDRIVERID;
typedef HACMDRIVERID   FAR *LPHACMDRIVERID;

DECLARE_HANDLE(HACMDRIVER);
typedef HACMDRIVER         *PHACMDRIVER;
typedef HACMDRIVER     FAR *LPHACMDRIVER;

DECLARE_HANDLE(HACMSTREAM);
typedef HACMSTREAM         *PHACMSTREAM;
typedef HACMSTREAM     FAR *LPHACMSTREAM;

DECLARE_HANDLE(HACMOBJ);
typedef HACMOBJ            *PHACMOBJ;
typedef HACMOBJ        FAR *LPHACMOBJ;



//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;
//
//  ACM Error Codes
//
//  Note that these error codes are specific errors that apply to the ACM
//  directly--general errors are defined as MMSYSERR_*.
//
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;

#ifndef _MMRESULT_
#define _MMRESULT_
typedef UINT                MMRESULT;
#endif

#define ACMERR_BASE         (512)
#define ACMERR_NOTPOSSIBLE  (ACMERR_BASE + 0)
#define ACMERR_BUSY         (ACMERR_BASE + 1)
#define ACMERR_UNPREPARED   (ACMERR_BASE + 2)
#define ACMERR_CANCELED     (ACMERR_BASE + 3)


//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;
//
//  ACM Window Messages
//
//  These window messages are sent by the ACM or ACM drivers to notify
//  applications of events.
//
//  Note that these window message numbers will also be defined in
//  mmsystem.
//
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;

#define MM_ACM_OPEN         (MM_STREAM_OPEN)  // conversion callback messages
#define MM_ACM_CLOSE        (MM_STREAM_CLOSE)
#define MM_ACM_DONE         (MM_STREAM_DONE)


//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;
//
//  acmGetVersion()
//
//  the ACM version is a 32 bit number that is broken into three parts as 
//  follows:
//
//      bits 24 - 31:   8 bit _major_ version number
//      bits 16 - 23:   8 bit _minor_ version number
//      bits  0 - 15:   16 bit build number
//
//  this is then displayed as follows:
//
//      bMajor = (BYTE)(dwVersion >> 24)
//      bMinor = (BYTE)(dwVersion >> 16) & 
//      wBuild = LOWORD(dwVersion)
//
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;

DWORD ACMAPI acmGetVersion
(
    void
);


//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;
//
//  acmMetrics()
//
//
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;

MMRESULT ACMAPI acmMetrics
(
    HACMOBJ                 hao,
    UINT                    uMetric,
    LPVOID                  pMetric
);

#define ACM_METRIC_COUNT_DRIVERS            1
#define ACM_METRIC_COUNT_CODECS             2
#define ACM_METRIC_COUNT_CONVERTERS         3
#define ACM_METRIC_COUNT_FILTERS            4
#define ACM_METRIC_COUNT_DISABLED           5
#define ACM_METRIC_COUNT_HARDWARE           6
#define ACM_METRIC_COUNT_LOCAL_DRIVERS      20
#define ACM_METRIC_COUNT_LOCAL_CODECS       21
#define ACM_METRIC_COUNT_LOCAL_CONVERTERS   22
#define ACM_METRIC_COUNT_LOCAL_FILTERS      23
#define ACM_METRIC_COUNT_LOCAL_DISABLED     24
#define ACM_METRIC_HARDWARE_WAVE_INPUT      30
#define ACM_METRIC_HARDWARE_WAVE_OUTPUT     31
#define ACM_METRIC_MAX_SIZE_FORMAT          50
#define ACM_METRIC_MAX_SIZE_FILTER          51
#define ACM_METRIC_DRIVER_SUPPORT           100
#define ACM_METRIC_DRIVER_PRIORITY          101


//--------------------------------------------------------------------------;
//
//  ACM Drivers
//
//
//
//
//--------------------------------------------------------------------------;

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;
//
//  acmDriverEnum()
//
//
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;

typedef BOOL (CALLBACK *ACMDRIVERENUMCB)
(
    HACMDRIVERID            hadid,
    DWORD                   dwInstance,
    DWORD                   fdwSupport
);

MMRESULT ACMAPI acmDriverEnum
(
    ACMDRIVERENUMCB         fnCallback,
    DWORD                   dwInstance,
    DWORD                   fdwEnum
);

#define ACM_DRIVERENUMF_NOLOCAL     0x40000000L
#define ACM_DRIVERENUMF_DISABLED    0x80000000L




//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;
//
//  acmDriverID()
//
//
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;

MMRESULT ACMAPI acmDriverID
(
    HACMOBJ                 hao,
    LPHACMDRIVERID          phadid,
    DWORD                   fdwDriverID
);



//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;
//
//  acmDriverAdd()
//
//
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;

MMRESULT ACMAPI acmDriverAdd
(
    LPHACMDRIVERID          phadid,
    HINSTANCE               hinstModule,
    LPARAM                  lParam, 
    DWORD                   dwPriority,
    DWORD                   fdwAdd
);


#define ACM_DRIVERADDF_NOTIFYHWND   0x00000004L  // lParam is notify hwnd



//
//  prototype for ACM driver procedures that are installed as _functions_
//  or _notifations_ instead of as a standalone installable driver.
//
typedef LRESULT (CALLBACK *ACMDRIVERPROC)(DWORD, HACMDRIVERID, UINT, LPARAM, LPARAM);
typedef ACMDRIVERPROC FAR *LPACMDRIVERPROC;

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;
//
//  acmDriverRemove()
//
//
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;

MMRESULT ACMAPI acmDriverRemove
(
    HACMDRIVERID            hadid,
    DWORD                   fdwRemove
);


//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;
//
//  acmDriverOpen()
//
//
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;

MMRESULT ACMAPI acmDriverOpen
(
    LPHACMDRIVER            phad, 
    HACMDRIVERID            hadid,
    DWORD                   fdwOpen
);


//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;
//
//  acmDriverClose()
//
//
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;

MMRESULT ACMAPI acmDriverClose
(
    HACMDRIVER              had,
    DWORD                   fdwClose
);


//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;
//
//  acmDriverMessage()
//
//
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;

LRESULT ACMAPI acmDriverMessage
(
    HACMDRIVER              had,
    UINT                    uMsg, 
    LPARAM                  lParam1,
    LPARAM                  lParam2
);


//
//
//
//
#define DRV_USER 0x4000
#define ACMDM_USER                  (DRV_USER + 0x0000)
#define ACMDM_RESERVED_LOW          (DRV_USER + 0x2000)
#define ACMDM_RESERVED_HIGH         (DRV_USER + 0x2FFF)

#define ACMDM_BASE                  ACMDM_RESERVED_LOW

#define ACMDM_DRIVER_ABOUT          (ACMDM_BASE + 11)


//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;
//
//  acmDriverPriority
//
//
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;

MMRESULT ACMAPI acmDriverPriority
(
    HACMDRIVERID            hadid,
    DWORD                   dwPriority,
    DWORD                   fdwPriority
);


#define ACM_DRIVERPRIORITYF_ENABLE      0x00000001L
#define ACM_DRIVERPRIORITYF_DISABLE     0x00000002L
#define ACM_DRIVERPRIORITYF_ABLEMASK    0x00000003L
#define ACM_DRIVERPRIORITYF_BEGIN       0x00010000L
#define ACM_DRIVERPRIORITYF_END         0x00020000L
#define ACM_DRIVERPRIORITYF_DEFERMASK   0x00030000L



//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;
//
//  acmDriverDetails()
//
//
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;

//
//  ACMDRIVERDETAILS
//
//  the ACMDRIVERDETAILS structure is used to get various capabilities from
//  an ACM driver (codec, converter, filter).
//
#define ACMDRIVERDETAILS_SHORTNAME_CHARS    32
#define ACMDRIVERDETAILS_LONGNAME_CHARS     128
#define ACMDRIVERDETAILS_COPYRIGHT_CHARS    80
#define ACMDRIVERDETAILS_LICENSING_CHARS    128
#define ACMDRIVERDETAILS_FEATURES_CHARS     512

typedef struct tACMDRIVERDETAILS
{
    DWORD           cbStruct;           // number of valid bytes in structure

    FOURCC          fccType;            // compressor type 'audc'
    FOURCC          fccComp;            // sub-type (not used; reserved)

    WORD            wMid;               // manufacturer id
    WORD            wPid;               // product id

    DWORD           vdwACM;             // version of the ACM *compiled* for
    DWORD           vdwDriver;          // version of the driver

    DWORD           fdwSupport;         // misc. support flags
    DWORD           cFormatTags;        // total unique format tags supported
    DWORD           cFilterTags;        // total unique filter tags supported

    HICON           hicon;              // handle to custom icon

    WCHAR           szShortName[ACMDRIVERDETAILS_SHORTNAME_CHARS];
    WCHAR           szLongName[ACMDRIVERDETAILS_LONGNAME_CHARS];
    WCHAR           szCopyright[ACMDRIVERDETAILS_COPYRIGHT_CHARS];
    WCHAR           szLicensing[ACMDRIVERDETAILS_LICENSING_CHARS];
    WCHAR           szFeatures[ACMDRIVERDETAILS_FEATURES_CHARS];

} ACMDRIVERDETAILS, *PACMDRIVERDETAILS, FAR *LPACMDRIVERDETAILS;


//
//  ACMDRIVERDETAILS.fccType
//
//  ACMDRIVERDETAILS_FCCTYPE_AUDIOCODEC: the FOURCC used in the fccType
//  field of the ACMDRIVERDETAILS structure to specify that this is an ACM
//  codec designed for audio.
//
//
//  ACMDRIVERDETAILS.fccComp
//
//  ACMDRIVERDETAILS_FCCCOMP_UNDEFINED: the FOURCC used in the fccComp
//  field of the ACMDRIVERDETAILS structure. this is currently an unused
//  field.
//
#define ACMDRIVERDETAILS_FCCTYPE_AUDIOCODEC mmioFOURCC('a', 'u', 'd', 'c')
#define ACMDRIVERDETAILS_FCCCOMP_UNDEFINED  mmioFOURCC('\0', '\0', '\0', '\0')


//
//  the following flags are used to specify the type of conversion(s) that
//  the converter/codec/filter supports. these are placed in the fdwSupport
//  field of the ACMDRIVERDETAILS structure. note that a converter can
//  support one or more of these flags in any combination.
//
//  ACMDRIVERDETAILS_SUPPORTF_CODEC: this flag is set if the driver supports
//  conversions from one format tag to another format tag. for example, if a
//  converter compresses WAVE_FORMAT_PCM to WAVE_FORMAT_ADPCM, then this bit
//  should be set.
//
//  ACMDRIVERDETAILS_SUPPORTF_CONVERTER: this flags is set if the driver
//  supports conversions on the same format tag. as an example, the PCM
//  converter that is built into the ACM sets this bit (and only this bit)
//  because it converts only PCM formats (bits, sample rate).
//
//  ACMDRIVERDETAILS_SUPPORTF_FILTER: this flag is set if the driver supports
//  transformations on a single format. for example, a converter that changed
//  the 'volume' of PCM data would set this bit. 'echo' and 'reverb' are
//  also filter types.
//
//  ACMDRIVERDETAILS_SUPPORTF_HARDWARE: this flag is set if the driver supports
//  hardware input and/or output through a waveform device.
//
//  ACMDRIVERDETAILS_SUPPORTF_ASYNC: this flag is set if the driver supports
//  async conversions.
//
//
//  ACMDRIVERDETAILS_SUPPORTF_LOCAL: this flag is set _by the ACM_ if a
//  driver has been installed local to the current task. this flag is also
//  set in the fdwSupport argument to the enumeration callback function
//  for drivers.
//
//  ACMDRIVERDETAILS_SUPPORTF_DISABLED: this flag is set _by the ACM_ if a
//  driver has been disabled. this flag is also passed set in the fdwSupport
//  argument to the enumeration callback function for drivers.
//
#define ACMDRIVERDETAILS_SUPPORTF_CODEC     0x00000001L
#define ACMDRIVERDETAILS_SUPPORTF_CONVERTER 0x00000002L
#define ACMDRIVERDETAILS_SUPPORTF_FILTER    0x00000004L
#define ACMDRIVERDETAILS_SUPPORTF_HARDWARE  0x00000008L
#define ACMDRIVERDETAILS_SUPPORTF_ASYNC     0x00000010L
#define ACMDRIVERDETAILS_SUPPORTF_LOCAL     0x40000000L
#define ACMDRIVERDETAILS_SUPPORTF_DISABLED  0x80000000L


MMRESULT ACMAPI acmDriverDetails
(
    HACMDRIVERID            hadid,
    LPACMDRIVERDETAILS      padd,
    DWORD                   fdwDetails
);



 
//--------------------------------------------------------------------------;
//
//  ACM Format Tags
//
//
//
//
//--------------------------------------------------------------------------;

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;
//
//  acmFormatTagDetails()
//
//
//
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;

#define ACMFORMATTAGDETAILS_FORMATTAG_CHARS 48

typedef struct tACMFORMATTAGDETAILSW
{
    DWORD           cbStruct;
    DWORD           dwFormatTagIndex;
    DWORD           dwFormatTag;
    DWORD           cbFormatSize;
    DWORD           fdwSupport;
    DWORD           cStandardFormats;
    WCHAR           szFormatTag[ACMFORMATTAGDETAILS_FORMATTAG_CHARS];

} ACMFORMATTAGDETAILS, *PACMFORMATTAGDETAILS, FAR *LPACMFORMATTAGDETAILS;

MMRESULT ACMAPI acmFormatTagDetails
(
    HACMDRIVER              had,
    LPACMFORMATTAGDETAILS   paftd,
    DWORD                   fdwDetails
);

#define ACM_FORMATTAGDETAILSF_INDEX         0x00000000L
#define ACM_FORMATTAGDETAILSF_FORMATTAG     0x00000001L
#define ACM_FORMATTAGDETAILSF_LARGESTSIZE   0x00000002L
#define ACM_FORMATTAGDETAILSF_QUERYMASK     0x0000000FL



//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;
//
//  acmFormatTagEnum()
//
//
//
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;

typedef BOOL (CALLBACK *ACMFORMATTAGENUMCB)
(
    HACMDRIVERID            hadid,
    LPACMFORMATTAGDETAILS   paftd,
    DWORD                   dwInstance,
    DWORD                   fdwSupport
);

MMRESULT ACMAPI acmFormatTagEnum
(
    HACMDRIVER              had,
    LPACMFORMATTAGDETAILS   paftd,
    ACMFORMATTAGENUMCB      fnCallback,
    DWORD                   dwInstance, 
    DWORD                   fdwEnum
);



//--------------------------------------------------------------------------;
//
//  ACM Formats
//
//
//
//
//--------------------------------------------------------------------------;

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;
//
//  acmFormatDetails()
//
//
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;

#define ACMFORMATDETAILS_FORMAT_CHARS   128

typedef struct tACMFORMATDETAILS
{
    DWORD           cbStruct;
    DWORD           dwFormatIndex;
    DWORD           dwFormatTag;
    DWORD           fdwSupport;
    LPWAVEFORMATEX  pwfx;
    DWORD           cbwfx;
    WCHAR           szFormat[ACMFORMATDETAILS_FORMAT_CHARS];

} ACMFORMATDETAILS, *PACMFORMATDETAILS, FAR *LPACMFORMATDETAILS;


MMRESULT ACMAPI acmFormatDetails
(
    HACMDRIVER              had,
    LPACMFORMATDETAILS      pafd,
    DWORD                   fdwDetails
);

#define ACM_FORMATDETAILSF_INDEX        0x00000000L
#define ACM_FORMATDETAILSF_FORMAT       0x00000001L
#define ACM_FORMATDETAILSF_QUERYMASK    0x0000000FL



//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;
//
//  acmFormatEnum()
//
//
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;

typedef BOOL (CALLBACK *ACMFORMATENUMCB)
(
    HACMDRIVERID            hadid,
    LPACMFORMATDETAILS      pafd,
    DWORD                   dwInstance,
    DWORD                   fdwSupport
);

MMRESULT ACMAPI acmFormatEnum
(
    HACMDRIVER              had,
    LPACMFORMATDETAILS      pafd,
    ACMFORMATENUMCB         fnCallback,
    DWORD                   dwInstance, 
    DWORD                   fdwEnum
);

#define ACM_FORMATENUMF_WFORMATTAG       0x00010000L
#define ACM_FORMATENUMF_NCHANNELS        0x00020000L
#define ACM_FORMATENUMF_NSAMPLESPERSEC   0x00040000L
#define ACM_FORMATENUMF_WBITSPERSAMPLE   0x00080000L
#define ACM_FORMATENUMF_CONVERT          0x00100000L
#define ACM_FORMATENUMF_SUGGEST          0x00200000L
#define ACM_FORMATENUMF_HARDWARE         0x00400000L
#define ACM_FORMATENUMF_INPUT            0x00800000L
#define ACM_FORMATENUMF_OUTPUT           0x01000000L

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;
//
//  acmFormatSuggest()
//
//
//
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;

MMRESULT ACMAPI acmFormatSuggest
(
    HACMDRIVER          had,
    LPWAVEFORMATEX      pwfxSrc,
    LPWAVEFORMATEX      pwfxDst,
    DWORD               cbwfxDst,
    DWORD               fdwSuggest
);

#define ACM_FORMATSUGGESTF_WFORMATTAG       0x00010000L
#define ACM_FORMATSUGGESTF_NCHANNELS        0x00020000L
#define ACM_FORMATSUGGESTF_NSAMPLESPERSEC   0x00040000L
#define ACM_FORMATSUGGESTF_WBITSPERSAMPLE   0x00080000L

#define ACM_FORMATSUGGESTF_TYPEMASK         0x00FF0000L


//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;
//
//  acmFormatChoose()
//
//
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;

#define ACMHELPMSGSTRING        TEXT("acmchoose_help")
#define ACMHELPMSGCONTEXTMENU   TEXT("acmchoose_contextmenu")
#define ACMHELPMSGCONTEXTHELP   TEXT("acmchoose_contexthelp")

//
//  MM_ACM_FORMATCHOOSE is sent to hook callbacks by the Format Chooser
//  Dialog...
//
#define MM_ACM_FORMATCHOOSE             (0x8000)

#define FORMATCHOOSE_MESSAGE            0
#define FORMATCHOOSE_FORMATTAG_VERIFY   (FORMATCHOOSE_MESSAGE+0)
#define FORMATCHOOSE_FORMAT_VERIFY      (FORMATCHOOSE_MESSAGE+1)
#define FORMATCHOOSE_CUSTOM_VERIFY      (FORMATCHOOSE_MESSAGE+2)


typedef UINT (CALLBACK *ACMFORMATCHOOSEHOOKPROC)
(
    HWND                    hwnd,
    UINT                    uMsg,
    WPARAM                  wParam,
    LPARAM                  lParam
);

//
//
//
//
typedef struct tACMFORMATCHOOSE
{
    DWORD           cbStruct;           // sizeof(ACMFORMATCHOOSE)
    DWORD           fdwStyle;           // chooser style flags
    
    HWND            hwndOwner;          // caller's window handle

    LPWAVEFORMATEX  pwfx;               // ptr to wfx buf to receive choice
    DWORD           cbwfx;              // size of mem buf for pwfx
    LPCWSTR         pszTitle;           // dialog box title bar
    
    WCHAR           szFormatTag[ACMFORMATTAGDETAILS_FORMATTAG_CHARS];
    WCHAR           szFormat[ACMFORMATDETAILS_FORMAT_CHARS];    

    LPWSTR          pszName;            // custom name selection
    DWORD           cchName;            // size in chars of mem buf for pszName

    DWORD           fdwEnum;            // format enumeration restrictions
    LPWAVEFORMATEX  pwfxEnum;           // format describing restrictions
    
    HINSTANCE       hInstance;          // app instance containing dlg template
    LPCWSTR         pszTemplateName;    // custom template name
    LPARAM          lCustData;          // data passed to hook fn.
    ACMFORMATCHOOSEHOOKPROC pfnHook;    // ptr to hook function

} ACMFORMATCHOOSE, *PACMFORMATCHOOSE, FAR *LPACMFORMATCHOOSE;

//
//  ACMFORMATCHOOSE.fdwStyle
//
//
//
#define ACMFORMATCHOOSE_STYLEF_SHOWHELP              0x00000004L
#define ACMFORMATCHOOSE_STYLEF_ENABLEHOOK            0x00000008L
#define ACMFORMATCHOOSE_STYLEF_ENABLETEMPLATE        0x00000010L
#define ACMFORMATCHOOSE_STYLEF_ENABLETEMPLATEHANDLE  0x00000020L
#define ACMFORMATCHOOSE_STYLEF_INITTOWFXSTRUCT       0x00000040L
#define ACMFORMATCHOOSE_STYLEF_CONTEXTHELP           0x00000080L

MMRESULT ACMAPI acmFormatChoose
(
    LPACMFORMATCHOOSE       pafmtc
);


//--------------------------------------------------------------------------;
//
//  ACM Filter Tags
//
//
//
//
//--------------------------------------------------------------------------;

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;
//
//  acmFilterTagDetails()
//
//
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;

#define ACMFILTERTAGDETAILS_FILTERTAG_CHARS 48

typedef struct tACMFILTERTAGDETAILS
{
    DWORD           cbStruct;
    DWORD           dwFilterTagIndex;
    DWORD           dwFilterTag;
    DWORD           cbFilterSize;
    DWORD           fdwSupport;
    DWORD           cStandardFilters;
    WCHAR           szFilterTag[ACMFILTERTAGDETAILS_FILTERTAG_CHARS];

} ACMFILTERTAGDETAILS, *PACMFILTERTAGDETAILS, FAR *LPACMFILTERTAGDETAILS;

MMRESULT ACMAPI acmFilterTagDetails
(
    HACMDRIVER              had,
    LPACMFILTERTAGDETAILS   paftd,
    DWORD                   fdwDetails
);

#define ACM_FILTERTAGDETAILSF_INDEX         0x00000000L
#define ACM_FILTERTAGDETAILSF_FILTERTAG     0x00000001L
#define ACM_FILTERTAGDETAILSF_LARGESTSIZE   0x00000002L
#define ACM_FILTERTAGDETAILSF_QUERYMASK     0x0000000FL



//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;
//
//  acmFilterTagEnum()
//
//
//
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;

typedef BOOL (CALLBACK *ACMFILTERTAGENUMCB)
(
    HACMDRIVERID            hadid,
    LPACMFILTERTAGDETAILS   paftd,
    DWORD                   dwInstance,
    DWORD                   fdwSupport
);

MMRESULT ACMAPI acmFilterTagEnum
(
    HACMDRIVER              had,
    LPACMFILTERTAGDETAILS   paftd,
    ACMFILTERTAGENUMCB      fnCallback,
    DWORD                   dwInstance, 
    DWORD                   fdwEnum
);



//--------------------------------------------------------------------------;
//
//  ACM Filters
//
//
//
//
//--------------------------------------------------------------------------;

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;
//
//  acmFilterDetails()
//
//
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;

#define ACMFILTERDETAILS_FILTER_CHARS   128

typedef struct tACMFILTERDETAILS
{
    DWORD           cbStruct;
    DWORD           dwFilterIndex;
    DWORD           dwFilterTag;
    DWORD           fdwSupport;
    LPWAVEFILTER    pwfltr;
    DWORD           cbwfltr;
    WCHAR           szFilter[ACMFILTERDETAILS_FILTER_CHARS];

} ACMFILTERDETAILS, *PACMFILTERDETAILS, FAR *LPACMFILTERDETAILS;

MMRESULT ACMAPI acmFilterDetails
(
    HACMDRIVER              had,
    LPACMFILTERDETAILS      pafd,
    DWORD                   fdwDetails
);

#define ACM_FILTERDETAILSF_INDEX        0x00000000L
#define ACM_FILTERDETAILSF_FILTER       0x00000001L
#define ACM_FILTERDETAILSF_QUERYMASK    0x0000000FL



//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;
//
//  acmFilterEnum()
//
//
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;

typedef BOOL (CALLBACK *ACMFILTERENUMCB)
(
    HACMDRIVERID            hadid,
    LPACMFILTERDETAILS      pafd,
    DWORD                   dwInstance,
    DWORD                   fdwSupport
);

MMRESULT ACMAPI acmFilterEnum
(
    HACMDRIVER              had,
    LPACMFILTERDETAILS      pafd,
    ACMFILTERENUMCB         fnCallback,
    DWORD                   dwInstance, 
    DWORD                   fdwEnum
);

#define ACM_FILTERENUMF_DWFILTERTAG         0x00010000L




//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;
//
//  acmFilterChoose()
//
//
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;

//
//  MM_ACM_FILTERCHOOSE is sent to hook callbacks by the Filter Chooser
//  Dialog...
//
#define MM_ACM_FILTERCHOOSE             (0x8000)

#define FILTERCHOOSE_MESSAGE            0
#define FILTERCHOOSE_FILTERTAG_VERIFY   (FILTERCHOOSE_MESSAGE+0)
#define FILTERCHOOSE_FILTER_VERIFY      (FILTERCHOOSE_MESSAGE+1)
#define FILTERCHOOSE_CUSTOM_VERIFY      (FILTERCHOOSE_MESSAGE+2)


typedef UINT (CALLBACK *ACMFILTERCHOOSEHOOKPROC)
(
    HWND                    hwnd,
    UINT                    uMsg,
    WPARAM                  wParam,
    LPARAM                  lParam
);

//
//  ACMFILTERCHOOSE
//
//
typedef struct tACMFILTERCHOOSE
{
    DWORD           cbStruct;           // sizeof(ACMFILTERCHOOSE)
    DWORD           fdwStyle;           // chooser style flags

    HWND            hwndOwner;          // caller's window handle

    LPWAVEFILTER    pwfltr;             // ptr to wfltr buf to receive choice
    DWORD           cbwfltr;            // size of mem buf for pwfltr

    LPCWSTR         pszTitle;

    WCHAR           szFilterTag[ACMFILTERTAGDETAILS_FILTERTAG_CHARS];
    WCHAR           szFilter[ACMFILTERDETAILS_FILTER_CHARS];
    LPWSTR          pszName;            // custom name selection
    DWORD           cchName;            // size in chars of mem buf for pszName

    DWORD           fdwEnum;            // filter enumeration restrictions
    LPWAVEFILTER    pwfltrEnum;         // filter describing restrictions
    
    HINSTANCE       hInstance;          // app instance containing dlg template
    LPCWSTR         pszTemplateName;    // custom template name
    LPARAM          lCustData;          // data passed to hook fn.
    ACMFILTERCHOOSEHOOKPROC pfnHook;    // ptr to hook function

} ACMFILTERCHOOSE, *PACMFILTERCHOOSE, FAR *LPACMFILTERCHOOSE;

//
//  ACMFILTERCHOOSE.fdwStyle
//
//
#define ACMFILTERCHOOSE_STYLEF_SHOWHELP              0x00000004L
#define ACMFILTERCHOOSE_STYLEF_ENABLEHOOK            0x00000008L
#define ACMFILTERCHOOSE_STYLEF_ENABLETEMPLATE        0x00000010L
#define ACMFILTERCHOOSE_STYLEF_ENABLETEMPLATEHANDLE  0x00000020L
#define ACMFILTERCHOOSE_STYLEF_INITTOFILTERSTRUCT    0x00000040L
#define ACMFILTERCHOOSE_STYLEF_CONTEXTHELP           0x00000080L

MMRESULT ACMAPI acmFilterChoose
(
    LPACMFILTERCHOOSE       pafltrc
);


//--------------------------------------------------------------------------;
//
//  ACM Stream API's
//
//
//
//--------------------------------------------------------------------------;

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;
//
//  acmStreamOpen()
//
//
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;

typedef struct tACMSTREAMHEADER
{
    DWORD           cbStruct;               // sizeof(ACMSTREAMHEADER)
    DWORD           fdwStatus;              // ACMSTREAMHEADER_STATUSF_*
    DWORD           dwUser;                 // user instance data for hdr
    LPBYTE          pbSrc;
    DWORD           cbSrcLength;
    DWORD           cbSrcLengthUsed;
    DWORD           dwSrcUser;              // user instance data for src
    LPBYTE          pbDst;
    DWORD           cbDstLength;
    DWORD           cbDstLengthUsed;
    DWORD           dwDstUser;              // user instance data for dst
    DWORD           dwReservedDriver[10];   // driver reserved work space

} ACMSTREAMHEADER, *PACMSTREAMHEADER, FAR *LPACMSTREAMHEADER;

//
//  ACMSTREAMHEADER.fdwStatus
//
//  ACMSTREAMHEADER_STATUSF_DONE: done bit for async conversions.
//
#define ACMSTREAMHEADER_STATUSF_DONE        0x00010000L
#define ACMSTREAMHEADER_STATUSF_PREPARED    0x00020000L
#define ACMSTREAMHEADER_STATUSF_INQUEUE     0x00100000L



MMRESULT ACMAPI acmStreamOpen
(
    LPHACMSTREAM            phas,       // pointer to stream handle
    HACMDRIVER              had,        // optional driver handle
    LPWAVEFORMATEX          pwfxSrc,    // source format to convert
    LPWAVEFORMATEX          pwfxDst,    // required destination format
    LPWAVEFILTER            pwfltr,     // optional filter
    DWORD                   dwCallback, // callback
    DWORD                   dwInstance, // callback instance data
    DWORD                   fdwOpen     // ACM_STREAMOPENF_* and CALLBACK_*
);

#define ACM_STREAMOPENF_QUERY           0x00000001
#define ACM_STREAMOPENF_ASYNC           0x00000002
#define ACM_STREAMOPENF_NONREALTIME     0x00000004


//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;
//
//  acmStreamClose()
//
//
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;

MMRESULT ACMAPI acmStreamClose
(
    HACMSTREAM              has,
    DWORD                   fdwClose
);



//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;
//
//  acmStreamSize()
//
//
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;

MMRESULT ACMAPI acmStreamSize
(
    HACMSTREAM              has,
    DWORD                   cbInput,
    LPDWORD                 pdwOutputBytes,
    DWORD                   fdwSize
);

#define ACM_STREAMSIZEF_SOURCE          0x00000000L
#define ACM_STREAMSIZEF_DESTINATION     0x00000001L
#define ACM_STREAMSIZEF_QUERYMASK       0x0000000FL



//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;
//
//  acmStreamReset()
//
//
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;

MMRESULT ACMAPI acmStreamReset
(
    HACMSTREAM              has,
    DWORD                   fdwReset
);





//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;
//
//  acmStreamMessage()
//
//
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;

MMRESULT ACMAPI acmStreamMessage
(
    HACMSTREAM              has,
    UINT                    uMsg, 
    LPARAM                  lParam1,
    LPARAM                  lParam2
);



//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;
//
//  acmStreamConvert()
//
//
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;

MMRESULT ACMAPI acmStreamConvert
(
    HACMSTREAM              has, 
    LPACMSTREAMHEADER       pash,
    DWORD                   fdwConvert
);

#define ACM_STREAMCONVERTF_BLOCKALIGN   0x00000004
#define ACM_STREAMCONVERTF_START        0x00000010
#define ACM_STREAMCONVERTF_END          0x00000020


//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;
//
//  acmStreamPrepareHeader()
//
//
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;

MMRESULT ACMAPI acmStreamPrepareHeader
(
    HACMSTREAM          has,
    LPACMSTREAMHEADER   pash,
    DWORD               fdwPrepare
);




//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;
//
//  acmStreamUnprepareHeader()
//
//
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;

MMRESULT ACMAPI acmStreamUnprepareHeader
(
    HACMSTREAM          has,
    LPACMSTREAMHEADER   pash,
    DWORD               fdwUnprepare
);
                                       


#ifndef RC_INVOKED
#pragma pack()          /* Revert to default packing */
#endif  /* RC_INVOKED */

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif  /* __cplusplus */

#endif  /* _INC_ACM */


