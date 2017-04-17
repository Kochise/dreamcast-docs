#ifndef __INCLUDE_SIP__
#define __INCLUDE_SIP__

#ifdef __cplusplus
extern "C" {
#endif

DWORD WINAPI SipStatus();

#define SIP_STATUS_UNAVAILABLE	0
#define SIP_STATUS_AVAILABLE	1

BOOL WINAPI	SipSetDefaultRect(RECT *);
BOOL WINAPI	SipRegisterNotification(HWND);

BOOL WINAPI SipShowIM(DWORD);

#define SIPF_OFF	0x00000000
#define SIPF_ON 	0x00000001
#define SIPF_DOCKED	0x00000002
#define SIPF_LOCKED	0x00000004

#define SPI_SETCOMPLETIONINFO	223
#define SPI_SETSIPINFO			224
#define SPI_GETSIPINFO			225
#define SPI_SETCURRENTIM        226
#define SPI_GETCURRENTIM        227

typedef struct	tagSIPINFO
{
    DWORD   cbSize;
    DWORD   fdwFlags;
    RECT    rcVisibleDesktop;
    RECT    rcSipRect;
    DWORD   dwImDataSize;
    void   *pvImData;
} SIPINFO;

BOOL WINAPI SipGetInfo(SIPINFO *);
BOOL WINAPI SipSetInfo(SIPINFO *);

typedef struct tagIMENUMINFO
{
    TCHAR   szName[MAX_PATH];
    CLSID   clsid;
} IMENUMINFO, *PIMENUMINFO;

typedef int (* IMENUMPROC)(IMENUMINFO *);

int WINAPI SipEnumIM(IMENUMPROC);
BOOL WINAPI SipGetCurrentIM(CLSID *);
BOOL WINAPI SipSetCurrentIM(CLSID *);

typedef struct	tagIMWINDOWPOS
{
    int     x;	    // Screen coordinate
    int     y;	    // Screen coordinate
    int     cx;     // Screen coordinate
    int     cy;     // Screen coordinate
} IMWINDOWPOS;

// The following defines are for the WPARAM value in WM_IM_INFO.

#define IM_POSITION	0
#define IM_WIDEIMAGE	1
#define IM_NARROWIMAGE	2

#ifdef __cplusplus
}
#endif

#endif//__INCLUDE_SIP__
