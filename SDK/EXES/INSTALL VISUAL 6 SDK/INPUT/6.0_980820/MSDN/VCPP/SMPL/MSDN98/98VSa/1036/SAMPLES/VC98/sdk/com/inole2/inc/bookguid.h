/*
 * BOOKGUID.H
 *
 * CLSIDs and IIDs defined for Inside OLE.  This file centralizes
 * them all so we can keep track of which ones are used.  The IDs
 * in this file are for exclusive use of the author and should not
 * be used under any circumstances in any other projects.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _BOOKGUID_H_
#define _BOOKGUID_H_

#ifdef INITGUIDS
#include <initguid.h>
#endif //INITGUIDS



/*
 * GUIDs
 *
 * For this book the author has been allocated the GUIDs in the range:
 *     00021100-0000-0000-C000-000000000046
 *     000211FF-0000-0000-C000-000000000046
 *
 * Gaps in the sequences are GUIDS used by the author for purposes other
 * than this book, e.g. magazine articles.
 *
 * GUIDs between 00021100 and 0002113F were used for the first edition
 * of Inside OLE 2 and interim samples.  Those starting with 00021140
 * are for the second edition of Inside OLE.
 *
 * GUIDs are only included if a "CHAPTERx" synmbol is defined.  This
 * keeps unused GUIDs out of the compilation.
 */


//Chapter 2
#ifdef CHAPTER2
DEFINE_GUID(IID_IEnumRECT,  0x00021140, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(IID_ISampleOne, 0x00021141, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(IID_ISampleTwo, 0x00021142, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(IID_IAnimal,    0x00021143, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(IID_IKoala,     0x00021144, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
#endif


//Chapter 4
#ifdef CHAPTER4
DEFINE_GUID(IID_IDuckEvents, 0x00021145, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
#endif


//Chapter 5
#ifdef CHAPTER5

//Koala Objects
DEFINE_GUID(CLSID_Koala, 0x00021146, 0, 0, 0xC0,0,0,0,0,0,0,0x46);

//Polyline
DEFINE_GUID(CLSID_Polyline5,          0x00021147, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(IID_IPolyline5,           0x00021148, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(IID_IPolylineAdviseSink5, 0x00021149, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
#endif


//Chapter 6
#ifdef CHAPTER6

//Koala Object:  Repeat of the Chapter 5 definition
DEFINE_GUID(CLSID_Koala,      0x00021146, 0, 0, 0xC0,0,0,0,0,0,0,0x46);

//Custom interfaces and proxy/stub CLSID
DEFINE_GUID(IID_IAnimal,      0x0002114A, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(CLSID_PSIAnimal,  0x0002114A, 0, 0, 0xC0,0,0,0,0,0,0,0x46);

DEFINE_GUID(IID_IKoala,       0x0002114B, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(CLSID_PSIKoala,   0x0002114B, 0, 0, 0xC0,0,0,0,0,0,0,0x46);

//Custom marshaling proxy
DEFINE_GUID(CLSID_KoalaProxy, 0x0002114C, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
#endif


//Chapter 7
#ifdef CHAPTER7
//Patron's App ID
DEFINE_GUID(CLSID_PatronPages, 0x0002114D, 0, 0, 0xC0,0,0,0,0,0,0,0x46);

#ifndef GUIDS_FROM_TYPELIB
//Cosmo Figures/Files
DEFINE_GUID(CLSID_CosmoFigure, 0x0002114E, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
#endif  //GUIDS_FROM_TYPELIB

#endif


//Chapter 8
#ifdef CHAPTER8

//Polyline
DEFINE_GUID(CLSID_Polyline8,          0x0002114F, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(IID_IPolyline8,           0x00021150, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(IID_IPolylineAdviseSink8, 0x00021151, 0, 0, 0xC0,0,0,0,0,0,0,0x46);

#endif



//Chapter 9
#ifdef CHAPTER9
DEFINE_GUID(IID_IDescription,  0x00021152, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(CLSID_LinkedFile,  0x00021153, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
#endif


//Chapter 10
#ifdef CHAPTER10

//DataObject variations for the data set.  Same server supplies them all.
DEFINE_GUID(CLSID_DataObjectSmall,  0x00021154, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(CLSID_DataObjectMedium, 0x00021155, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(CLSID_DataObjectLarge,  0x00021156, 0, 0, 0xC0,0,0,0,0,0,0,0x46);

//Polyine
DEFINE_GUID(CLSID_Polyline10,          0x00021157, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(IID_IPolyline10,           0x00021158, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(IID_IPolylineAdviseSink10, 0x00021159, 0, 0, 0xC0,0,0,0,0,0,0,0x46);

#endif


//Chapter 11
#ifdef CHAPTER11
#endif

//Needed for many subsequent chapters
#ifndef WIN32
//OLE32 has these defined, OLE16 doesn't
#undef CLSID_Picture_Metafile
#undef CLSID_Picture_Dib
DEFINE_OLEGUID(CLSID_Picture_Metafile,        0x00000315, 0, 0);
DEFINE_OLEGUID(CLSID_Picture_Dib,             0x00000316, 0, 0);
#endif


//Chapter 12
#ifdef CHAPTER12

DEFINE_GUID(CLSID_PatronPages, 0x0002114D, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(CLSID_CosmoFigure, 0x0002114E, 0, 0, 0xC0,0,0,0,0,0,0,0x46);

DEFINE_GUID(CLSID_Polyline10,          0x00021157, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(IID_IPolyline10,           0x00021158, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(IID_IPolylineAdviseSink10, 0x00021159, 0, 0, 0xC0,0,0,0,0,0,0,0x46);

//Data Transfer Component
DEFINE_GUID(CLSID_DataTransferObject, 0x0002115A, 0, 0, 0xC0,0,0,0,0,0,0,0x46);

#endif


//Chapter 13
#ifdef CHAPTER13

DEFINE_GUID(CLSID_PatronPages, 0x0002114D, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(CLSID_CosmoFigure, 0x0002114E, 0, 0, 0xC0,0,0,0,0,0,0,0x46);

DEFINE_GUID(CLSID_Polyline10,          0x00021157, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(IID_IPolyline10,           0x00021158, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(IID_IPolylineAdviseSink10, 0x00021159, 0, 0, 0xC0,0,0,0,0,0,0,0x46);

DEFINE_GUID(CLSID_DataTransferObject, 0x0002115A, 0, 0, 0xC0,0,0,0,0,0,0,0x46);

#endif


//Chapter 14
#ifdef CHAPTER14

//For Cosmo
DEFINE_GUID(CLSID_CosmoFigure,        0x0002114E, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(CLSID_DataTransferObject, 0x0002115A, 0, 0, 0xC0,0,0,0,0,0,0,0x46);

//Beeper samples
#ifndef GUIDS_FROM_TYPELIB
DEFINE_GUID(CLSID_Beeper,            0x0002115B, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(IID_IBeeper,             0x0002115C, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(DIID_DIBeeper,           0x0002115D, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(LIBID_BeeperTypeLibrary, 0x0002115E, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
#endif


//Cosmo Chapter 14:  Automation Interfaces
#ifndef GUIDS_FROM_TYPELIB
DEFINE_GUID(IID_ICosmoApplication,    0x0002115F, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(IID_ICosmoFigures,        0x00021160, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(IID_ICosmoFigure,         0x00021161, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(DIID_DICosmoApplication,  0x00021162, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(DIID_DICosmoFigures,      0x00021163, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(DIID_DICosmoFigure,       0x00021164, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(LIBID_Cosmo2TypeLibrary,  0x00021165, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(CLSID_Cosmo2Application,  0x00021166, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
#endif

#endif



//Chapter 15
#ifdef CHAPTER15

//SphereSquare Automation Object
#ifndef GUIDS_FROM_TYPELIB
DEFINE_GUID(CLSID_SphereSquare,   0x00021167, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(IID_ISphereSquare,    0x00021168, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(TLBID_SphereSquare,   0x00021169, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(DIID_DISphereSquare,  0x0002116A, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
#endif

#endif


//Chapter 16
#ifdef CHAPTER16

//Repeats from Chapter 14
#ifndef GUIDS_FROM_TYPELIB
DEFINE_GUID(CLSID_Beeper,            0x0002115B, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(IID_IBeeper,             0x0002115C, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(DIID_DIBeeper,           0x0002115D, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(LIBID_BeeperTypeLibrary, 0x0002115E, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
#endif

//Beeper Property Page
DEFINE_GUID(CLSID_BeeperPropertyPage, 0x0002116B, 0, 0, 0xC0,0,0,0,0,0,0,0x46);

#endif

//Chapter 17
#ifdef CHAPTER17
DEFINE_GUID(CLSID_PatronPages,        0x0002114D, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(CLSID_DataTransferObject, 0x0002115A, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
#endif


//Chapter 18
#ifdef CHAPTER18
DEFINE_GUID(CLSID_CosmoFigure,        0x0002114E, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(CLSID_DataTransferObject, 0x0002115A, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
#endif


//Chapter 19
#ifdef CHAPTER19
DEFINE_GUID(IID_IPolyline10,           0x00021158, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(IID_IPolylineAdviseSink10, 0x00021159, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(CLSID_Polyline19,          0x0002116D, 0, 0, 0xC0,0,0,0,0,0,0,0x46);

DEFINE_GUID(CLSID_CosmoFigure,         0x0002114E, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
#endif

//Chapter 20
#ifdef CHAPTER20
DEFINE_GUID(CLSID_PatronPages,        0x0002114D, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(CLSID_DataTransferObject, 0x0002115A, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(CLSID_LinksAssistant,     0x0002116E, 0, 0, 0xC0,0,0,0,0,0,0,0x46);

//For OLEUI, not defined in OLE headers
DEFINE_GUID(IID_IOleUILinkContainer,  0x0002116F, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
#endif

//Chapter 21
#ifdef CHAPTER21
DEFINE_GUID(CLSID_PatronPages,        0x0002114D, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(CLSID_CosmoFigure,        0x0002114E, 0, 0, 0xC0,0,0,0,0,0,0,0x46);

DEFINE_GUID(IID_IPolyline10,           0x00021158, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(IID_IPolylineAdviseSink10, 0x00021159, 0, 0, 0xC0,0,0,0,0,0,0,0x46);

//This is used for Polyline21 as well
DEFINE_GUID(CLSID_Polyline19,          0x0002116D, 0, 0, 0xC0,0,0,0,0,0,0,0x46);

DEFINE_GUID(CLSID_DataTransferObject, 0x0002115A, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(CLSID_LinksAssistant,     0x0002116E, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(IID_IOleUILinkContainer,  0x0002116F, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
#endif

//Chapter 22
#ifdef CHAPTER22
DEFINE_GUID(CLSID_PatronPages,        0x0002114D, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(CLSID_DataTransferObject, 0x0002115A, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(CLSID_LinksAssistant,     0x0002116E, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(IID_IOleUILinkContainer,  0x0002116F, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
#endif

//Chapter 23
#ifdef CHAPTER23
DEFINE_GUID(CLSID_CosmoFigure,        0x0002114E, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(CLSID_DataTransferObject, 0x0002115A, 0, 0, 0xC0,0,0,0,0,0,0,0x46);

DEFINE_GUID(IID_IPolyline10,           0x00021158, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(IID_IPolylineAdviseSink10, 0x00021159, 0, 0, 0xC0,0,0,0,0,0,0,0x46);

//This is used for Polyline23 as well
DEFINE_GUID(CLSID_Polyline19,          0x0002116D, 0, 0, 0xC0,0,0,0,0,0,0,0x46);

#endif

//Chapter 24
#ifdef CHAPTER24

DEFINE_GUID(IID_IPolyline10,           0x00021158, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(CLSID_PatronPages,        0x0002114D, 0, 0, 0xC0,0,0,0,0,0,0,0x46);

DEFINE_GUID(CLSID_DataTransferObject, 0x0002115A, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(CLSID_LinksAssistant,     0x0002116E, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(IID_IOleUILinkContainer,  0x0002116F, 0, 0, 0xC0,0,0,0,0,0,0,0x46);


#ifndef GUIDS_FROM_TYPELIB
DEFINE_GUID(IID_IPolylineAdviseSink10,   0x00021159, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(DIID_DIPolylineAdviseSink10, 0x00021170, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(IID_IPolylineControl,        0x00021171, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(DIID_DIPolylineControl,      0x00021172, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
DEFINE_GUID(LIBID_Polyline,              0x00021173, 0, 0, 0xC0,0,0,0,0,0,0,0x46);

//This is used for Polyline25 as well
DEFINE_GUID(CLSID_Polyline19,          0x0002116D, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
#endif //GUIDSFROMTYPELIB

DEFINE_GUID(CLSID_PolylinePropPage,    0x00021174, 0, 0, 0xC0,0,0,0,0,0,0,0x46);
#endif


//Chapter 25
#ifdef CHAPTER25
#endif

#endif //_BOOKGUID_H_
