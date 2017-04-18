/*************************************************************************
**                                                                      **
**                          CVTYPES.H                                   **
**                                                                      **
**************************************************************************
**                                                                      **
**  This file contains a common set of base type declarations           **
**  between multiple CodeView projects.  If you touch this in one       **
**  project be sure to copy it to all other projects as well.           **
**                                                                      **
*************************************************************************/

#ifndef CV_PROJECT_BASE_TYPES

#define CV_PROJECT_BASE_TYPES

#include "dbapiver.h"

#ifndef _CV_INFO_INCLUDED
#include "cvinfo.h"
#endif

#if !defined(OSDEBUG4)
/*
**  HDEP is a machine dependent size and passes as a general handle.
**  HIND is a machine independent sized handle and is used for things
**      which are passed between machines
**
*/

#ifdef QCWIN32
    typedef HANDLE      HDEP;
    typedef DWORD       HIND;
#else
    DECLARE_HANDLE(HDEP);
    DECLARE_HANDLE(HIND);
#endif // QCWIN32


typedef HDEP FAR *      LPHDEP;
typedef HIND FAR *      LPHIND;


/* HMEM should be avoided (HDEP should be used instead), but for now we'll
** define it for backwards compatibility.
*/

typedef HDEP            HMEM;
typedef HMEM FAR *      LPHMEM;
#endif // !OSDEBUG4

/* These values are used in the SegType field of the Expression Evaluator's
** TI structure, and as the third parameter to the Symbol Handler's
** SHGetNearestHsym function.
*/
#define EECODE          0x01
#define EEDATA          0x02
#define EEANYSEG        0xFFFF

#if !defined(OSDEBUG4)
/*
**  HPID
**  HTID
**
*/

DECLARE_HANDLE(HPID);
DECLARE_HANDLE(HTID);

typedef USHORT      SEGMENT;    // 32-bit compiler doesn't like "_segment"
typedef ULONG       UOFF32;
typedef USHORT      UOFF16;
typedef LONG        OFF32;
typedef SHORT       OFF16;

#if defined (ADDR_16)
    // we are operating as a 16:16 evaluator only
    // the address packet will be defined as an offset and a 16 bit filler
    typedef OFF16       OFFSET;
    typedef UOFF16      UOFFSET;
#else
    typedef OFF32       OFFSET;
    typedef UOFF32      UOFFSET;
#endif // ADDR_16

typedef UOFFSET FAR *LPUOFFSET;

//  address definitions
//  the address packet is always a 16:32 address.

typedef struct {
    UOFF32          off;
    SEGMENT         seg;
} address_t;

#define SegAddrT(a)   ((a).seg)
#define OffAddrT(a)   ((a).off)
#define AddrTInit(paddrT,segSet,offSet)     \
        {                                   \
            SegAddrT(*(paddrT)) = segSet;   \
            OffAddrT(*(paddrT)) = offSet;   \
        }

typedef struct {
    BYTE    fFlat   :1;         // true if address is flat
    BYTE    fOff32  :1;         // true if offset is 32 bits
    BYTE    fIsLI   :1;         // true if segment is linker index
    BYTE    fReal   :1;         // x86: is segment a real mode address
    BYTE    unused  :4;         // unused
} memmode_t;

#define MODE_IS_FLAT(m)     ((m).fFlat)
#define MODE_IS_OFF32(m)    ((m).fOff32)
#define MODE_IS_LI(m)       ((m).fIsLI)
#define MODE_IS_REAL(m)     ((m).fReal)

#define ModeInit(pmode,fFlat,fOff32,fLi,fRealSet)   \
        {                                           \
            MODE_IS_FLAT(*(pmode))    = fFlat;      \
            MODE_IS_OFF32(*(pmode))   = fOff32;     \
            MODE_IS_LI(*(pmode))      = fLi;        \
            MODE_IS_REAL(*(pmode))    = fRealSet;   \
        }

typedef HIND    HEMI;           // Executable Module Index

typedef struct ADDR {
    address_t       addr;
    HEMI            emi;
    memmode_t       mode;
} ADDR;             //* An address specifier
typedef ADDR FAR *  PADDR;      //* REVIEW: BUG: shouldn't be explicitly far
typedef ADDR FAR *  LPADDR;

#define addrAddr(a)     ((a).addr)
#define emiAddr(a)      ((a).emi)
#define modeAddr(a)     ((a).mode)

#define AddrInit(paddr,emiSet,segSet,offSet,fFlat,fOff32,fLi,fRealSet)  \
        {                                                               \
            AddrTInit( &(addrAddr(*(paddr))), segSet, offSet );         \
            emiAddr(*(paddr)) = emiSet;                                 \
            ModeInit( &(modeAddr(*(paddr))),fFlat,fOff32,fLi,fRealSet); \
        }

#define ADDR_IS_FLAT(a)     (MODE_IS_FLAT(modeAddr(a)))
#define ADDR_IS_OFF32(a)    (MODE_IS_OFF32(modeAddr(a)))
#define ADDR_IS_LI(a)       (MODE_IS_LI(modeAddr(a)))
#define ADDR_IS_REAL(a)     (MODE_IS_REAL(modeAddr(a)))

#define ADDRSEG16(a)   { ADDR_IS_FLAT(a) = FALSE; ADDR_IS_OFF32(a) = FALSE; }
#define ADDRSEG32(a)   { ADDR_IS_FLAT(a) = FALSE; ADDR_IS_OFF32(a) = TRUE;  }
#define ADDRLIN32(a)   { ADDR_IS_FLAT(a) = TRUE;  ADDR_IS_OFF32(a) = TRUE;  }

#define GetAddrSeg(a)   ((a).addr.seg)
#define GetAddrOff(a)   ((a).addr.off)
#define SetAddrSeg(a,s) ((a)->addr.seg=s)
#define SetAddrOff(a,o) ((a)->addr.off=o)

// Because an ADDR has some filler areas (in the mode and the address_t),
// it's bad to use memcmp two ADDRs to see if they're equal.  Use this
// macro instead.  (I deliberately left out the test for fAddr32(), because
// I think it's probably not necessary when comparing.)
#define FAddrsEq(a1, a2)                        \
    (                                           \
    GetAddrOff(a1) == GetAddrOff(a2) &&         \
    GetAddrSeg(a1) == GetAddrSeg(a2) &&         \
    ADDR_IS_LI(a1) == ADDR_IS_LI(a2) &&         \
    emiAddr(a1)    == emiAddr(a2)               \
    )

//      address definitions
//      the address packet is always a 16:32 address.
#endif // !OSDEBUG4

typedef struct FRAME {
    SEGMENT         SS;
    address_t       BP;
    SEGMENT         DS;
    memmode_t       mode;
    HPID            PID;
    HTID            TID;
    address_t       SLP;    // Static link pointer
} FRAME;
typedef FRAME FAR *PFRAME;      //* REVIEW: BUG: shouldn't be explicitly far

#define addrFrameSS(a)     ((a).SS)
#define addrFrameBP(a)     ((a).BP)
#define GetFrameBPOff(a)   ((a).BP.off)
#define GetFrameBPSeg(a)   ((a).BP.seg)
#define SetFrameBPOff(a,o) ((a).BP.off = o)
#define SetFrameBPSeg(a,s) ((a).BP.seg = s)
#define GetFrameSLPOff(a)   ((a).SLP.off)
#define GetFrameSLPSeg(a)   ((a).SLP.seg)
#define SetFrameSLPOff(a,o) ((a).SLP.off = o)
#define SetFrameSLPSeg(a,s) ((a).SLP.seg = s)
#define FRAMEMODE(a)       ((a).mode)
#define FRAMEPID(a)        ((a).PID)
#define FRAMETID(a)        ((a).TID)

#define FrameFlat(a)       MODE_IS_FLAT((a).mode)
#define FrameOff32(a)      MODE_IS_OFF32((a).mode)
#define FrameReal(a)       MODE_IS_REAL((a).mode)

#if !defined(OSDEBUG4)
/*
** A few public types related to the linked list manager
*/

typedef HDEP        HLLI;       //* A handle to a linked list
typedef HIND        HLLE;       //* A handle to a linked list entry

typedef void (FAR PASCAL * LPFNKILLNODE)( LPV );
typedef int  (FAR PASCAL * LPFNFCMPNODE)( LPV, LPV, LONG );

typedef USHORT      LLF;        //* Linked List Flags
#define llfNull             (LLF)0x0
#define llfAscending        (LLF)0x1
#define llfDescending       (LLF)0x2
#endif // !OSDEBUG4

/*
**  EXPCALL indicates that a function should use whatever calling
**      convention is preferable for exported functions.  Under most
**      operating systems, this is PASCAL, because the name will be
**      left undecorated if it's PASCAL; but under NT and Win32s,
**      PASCAL is #defined to __stdcall, but _cdecl will leave the
**      name (mostly) undecorated.  (It will add an underscore, but
**      that's desirable under Win32s and NT, because you can't
**      export a name that *doesn't* have an underscore.)
**
**      Furthermore, we use _cdecl instead of CDECL because the current
**      NT header files don't necessarily define CDECL to _cdecl.
**
**      EXPCALL does NOT do everything that may be necessary for an
**      exported function (e.g. LOADDS, EXPORT, and FAR), because
**      it's too hard at the moment to clean up all the uses of
**      EXPCALL to use the same modifiers.  Someday.
*/

#if HOST32
    #define EXPCALL     __stdcall
#else
    #define EXPCALL     PASCAL
#endif

typedef struct _MEMINFO {
    ADDR addr;
    ADDR addrAllocBase;
    UOFF32 uRegionSize;
    DWORD dwProtect;
    DWORD dwState;
    DWORD dwType;
} MEMINFO;
typedef MEMINFO FAR * LPMEMINFO;

/*
**      Return values for mtrcEndian -- big or little endian -- which
**      byte is [0] most or least significat byte
*/
enum _END {
    endBig,
    endLittle
};
typedef DWORD END;

enum _MPT {
    mptix86,
    mptm68k,
    mptdaxp,
    mptmips,
    mptmppc,
    mptUnknown
};
typedef DWORD MPT;

#if !defined(OSDEBUG4)
#include <dbgver.h>
#endif // !OSDEBUG4

#endif // CV_PROJECT_BASE_TYPES
