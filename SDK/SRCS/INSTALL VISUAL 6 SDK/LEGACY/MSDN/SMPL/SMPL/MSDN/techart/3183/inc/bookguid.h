/*
 * BOOKGUID.H
 *
 * CLSIDs and IIDs defined for the Windows Object book.  This file
 * centralizes them all so we can keep track of which ones are used.
 * The file also includes a number of useful macros that all samples
 * might be interested in as well as including BOOK1632.H and DEBUG.H.
 *
 * Copyright (c)1993-1994 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Software Design Engineer
 * Microsoft Systems Developer Relations
 *
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _BOOKGUID_H_
#define _BOOKGUID_H_


#include <book1632.h>
#include <dbgout.h>

#ifdef INITGUIDS
#include <initguid.h>
#endif //INITGUIDS


//Types that OLE2.H et. al. leave out
#ifndef LPLPVOID
typedef LPVOID FAR * LPLPVOID;
#endif  //LPLPVOID

#ifndef PPVOID  //Large model version
typedef LPVOID * PPVOID;
#endif  //PPVOID


#ifdef _OLE2_H_   //May not include ole2.h at all times.
#ifndef LPPOINTL
typedef POINTL FAR * LPPOINTL;
#endif  //LPPOINTL

#ifndef PPOINTL //Large model version
typedef POINTL * PPOINTL;
#endif  //PPOINTL


//Useful macros.
#define SETFormatEtc(fe, cf, asp, td, med, li)   \
    {\
    (fe).cfFormat=cf;\
    (fe).dwAspect=asp;\
    (fe).ptd=td;\
    (fe).tymed=med;\
    (fe).lindex=li;\
    };

#define SETDefFormatEtc(fe, cf, med)   \
    {\
    (fe).cfFormat=cf;\
    (fe).dwAspect=DVASPECT_CONTENT;\
    (fe).ptd=NULL;\
    (fe).tymed=med;\
    (fe).lindex=-1;\
    };


#define SETRECTL(rcl, l, t, r, b) \
    {\
    (rcl).left=l;\
    (rcl).top=t;\
    (rcl).right=r;\
    (rcl).bottom=b;\
    }

#define SETSIZEL(szl, h, v) \
    {\
    (szl).cx=h;\
    (szl).cy=v;\
    }


#define RECTLFROMRECT(rcl, rc)\
    {\
    (rcl).left=(long)(rc).left;\
    (rcl).top=(long)(rc).top;\
    (rcl).right=(long)(rc).right;\
    (rcl).bottom=(long)(rc).bottom;\
    }


#define RECTFROMRECTL(rc, rcl)\
    {\
    (rc).left=(int)(rcl).left;\
    (rc).top=(int)(rcl).top;\
    (rc).right=(int)(rcl).right;\
    (rc).bottom=(int)(rcl).bottom;\
    }


#define POINTLFROMPOINT(ptl, pt) \
    { \
    (ptl).x=(long)(pt).x; \
    (ptl).y=(long)(pt).y; \
    }


#define POINTFROMPOINTL(pt, ptl) \
    { \
    (pt).x=(int)(ptl).x; \
    (pt).y=(int)(ptl).y; \
    }

//Here's one that should be in windows.h
#define SETPOINT(pt, h, v) \
    {\
    (pt).x=h;\
    (pt).y=v;\
    }

#define SETPOINTL(ptl, h, v) \
    {\
    (ptl).x=h;\
    (ptl).y=v;\
    }

#endif  //_OLE2_H_


/*
 * State flags for IPersistStorage implementations.  These
 * are kept here to avoid repeating the code in all samples.
 */

//State Flags
typedef enum
    {
    PSSTATE_UNINIT,     //Uninitialized
    PSSTATE_SCRIBBLE,   //Scribble
    PSSTATE_ZOMBIE,     //No scribble
    PSSTATE_HANDSOFF    //Hand-off
    } PSSTATE;




/*
 * GUIDs
 *
 * For this book the author has been allocated the GUIDs in the range:
 *     00021100-0000-0000-C000-000000000046
 *     000211FF-0000-0000-C000-000000000046
 *
 * Gaps in the sequences are GUIDS used by the author for purposes other
 * than this book, e.g. magazine articles.
 */


//GUIDs for Chapter 4

//Koala
DEFINE_GUID(CLSID_Koala, 0x00021102, 0, 0, 0xC0,0,0,0,0,0,0,0x46);


//Polyine
DEFINE_GUID(CLSID_Polyline4,          0x00021103, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(IID_IPolyline4,           0x00021104, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(IID_IPolylineAdviseSink4, 0x00021105, 0, 0, 0xC0,0,0,0,0,0,0,0x46);


//GUIDs for Chapter 5

//Patron Files for Chapter 5 and beyond:  becomes Patron's App ID
DEFINE_GUID(CLSID_PatronPages, 0x00021106, 0, 0, 0xC0,0,0,0,0,0,0,0x46);

//Cosmo Files for Chapter 5 and beyond:  becomes Cosmo's App ID
DEFINE_GUID(CLSID_Cosmo2Figure, 0x00021107, 0, 0, 0xC0,0,0,0,0,0,0,0x46);

//Polyine
DEFINE_GUID(CLSID_Polyline5,          0x00021108, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(IID_IPolyline5,           0x00021109, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(IID_IPolylineAdviseSink5, 0x0002110A, 0, 0, 0xC0,0,0,0,0,0,0,0x46);


//GUIDs for Chapter 6

//DataObject variations for the data set.  Same server supplies them all.
DEFINE_GUID(CLSID_DataObjectSmall,  0x0002110B, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(CLSID_DataObjectMedium, 0x0002110C, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(CLSID_DataObjectLarge,  0x0002110D, 0, 0, 0xC0,0,0,0,0,0,0,0x46);

//Polyine
DEFINE_GUID(CLSID_Polyline6,          0x0002110E, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(IID_IPolyline6,           0x0002110F, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(IID_IPolylineAdviseSink6, 0x00021110, 0, 0, 0xC0,0,0,0,0,0,0,0x46);


//GUIDS for Chapter 7

//Data Transfer Component Object
DEFINE_GUID(CLSID_DataTransferObject, 0x00021111, 0, 0, 0xC0,0,0,0,0,0,0,0x46);

#ifndef WIN32
//OLE32 has these defined, OLE16 doesn't
#undef CLSID_Picture_Metafile
#undef CLSID_Picture_Dib
DEFINE_OLEGUID(CLSID_Picture_Metafile,        0x00000315, 0, 0);
DEFINE_OLEGUID(CLSID_Picture_Dib,             0x00000316, 0, 0);
#endif

//Cosmo in chapter 10 uses CLSID_Cosmo2Figure above.


//GUIDs for Chapter 11

//HCosmo is registered under CLSID_Cosmo2Figure

//Polyine
DEFINE_GUID(CLSID_Polyline11, 0x00021112, 0, 0, 0xC0,0,0,0,0,0,0,0x46);


//GUIDs for Chapter 12

//LinksAssistant
DEFINE_GUID(CLSID_LinksAssistant, 0x00021113, 0, 0, 0xC0,0,0,0,0,0,0,0x46);

//OLE 2.0 SDK forgot this one.
DEFINE_GUID(IID_IOleUILinkContainer, 0x00021114, 0, 0, 0xC0,0,0,0,0,0,0,0x46);


//GUIDs for Chapter 16

/*
 * Cosmo in chapter 16 uses CLSID_Cosmo2Figure above.
 * Polyine in Chapter 16 uses CLSID_Polyline11.
 *
 * This is so we don't make repeat entries in the
 * registration database.
 */


#endif //_BOOKGUID_H_
