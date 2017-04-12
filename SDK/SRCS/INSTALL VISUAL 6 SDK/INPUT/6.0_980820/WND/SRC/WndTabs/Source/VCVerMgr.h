/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/


#ifndef __VCVERMGR_H
#define __VCVERMGR_H

#ifdef WT_INITGUID
#define WT_DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
    EXTERN_C GUID name \
                = { l, w1, w2, { b1, b2,  b3,  b4,  b5,  b6,  b7,  b8 } }
#else
#define WT_DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
    EXTERN_C GUID FAR name
#endif // INITGUID


WT_DEFINE_GUID(IID_IDocuments_Resolved, 
               0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

WT_DEFINE_GUID(IID_IGenericDocument_Resolved, 
               0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

WT_DEFINE_GUID(IID_ITextDocument_Resolved, 
               0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

enum VC_Versions { 
    Unknown = 99,
    VC   = 0,          // Visual C++ 5.0/6.0
    eVC3 = 1,          // eMbedded Visual C++ 3
    CEPB = 2,          // WinCE Platform Builder
    eVC4 = 3,          // eMbedded Visual C++ 4
    VF   = 4           // Visual Fortran
};

extern VC_Versions g_VCVer;
extern const char *g_pszVCExeName;


#endif // __VCVERMGR_H
