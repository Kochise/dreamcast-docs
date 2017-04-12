/*++

Copyright (c) 1996 Microsoft Corporation

Module Name:

    amrtpnet.h

Abstract:

    Definitions for ActiveMovie RTP Network Filters.

--*/
 

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// RTP Filter UUIDS                                                          //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

DEFINE_GUID(CLSID_RTPRenderFilter,
0x00d20921, 0x7e20, 0x11d0, 0xb2, 0x91, 0x00, 0xc0, 0x4f, 0xc3, 0x1d, 0x18);

DEFINE_GUID(CLSID_RTPRenderFilterProperties,
0x00d20923, 0x7e20, 0x11d0, 0xb2, 0x91, 0x00, 0xc0, 0x4f, 0xc3, 0x1d, 0x18);

DEFINE_GUID(CLSID_RTPSourceFilter,
0x00d20920, 0x7e20, 0x11d0, 0xb2, 0x91, 0x00, 0xc0, 0x4f, 0xc3, 0x1d, 0x18);

DEFINE_GUID(CLSID_RTPSourceFilterProperties,
0x00d20922, 0x7e20, 0x11d0, 0xb2, 0x91, 0x00, 0xc0, 0x4f, 0xc3, 0x1d, 0x18);

DEFINE_GUID(IID_IRTPStream, 
0x00d20915, 0x7e20, 0x11d0, 0xb2, 0x91, 0x00, 0xc0, 0x4f, 0xc3, 0x1d, 0x18);

#ifndef _INC_AMRTPNET
#define _INC_AMRTPNET

#include <rtp.h>


///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// IRTPStream Interface                                                      //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

DECLARE_INTERFACE_(IRTPStream, IUnknown) {

    STDMETHOD(GetAddress)(THIS_
        LPBYTE  pRtpAddr,
        LPDWORD pdwRtpAddrLen
        ) PURE;

    STDMETHOD(SetAddress)(THIS_
        LPBYTE pRtpAddr,
        DWORD  dwRtpAddrLen
        ) PURE;

    STDMETHOD(GetMulticastScope)(THIS_
        LPDWORD pdwMulticastScope
        ) PURE;

    STDMETHOD(SetMulticastScope)(THIS_
        DWORD   dwMulticastScope
        ) PURE;

    STDMETHOD(SetQualityOfService)(THIS_
        QOS *   pQOS
        ) PURE;

    STDMETHOD(GetQOSstate)(THIS_
        DWORD *pdwQOSstate
        ) PURE;

    STDMETHOD(SetQOSstate)(THIS_
        DWORD dwQOSstate
        ) PURE;

    STDMETHOD(GetMulticastLoopBack)(THIS_
        DWORD *pdwMulticastLoopBack
        ) PURE;

    STDMETHOD(SetMulticastLoopBack)(THIS_
		DWORD dwMulticastLoopBack
        ) PURE;
};

#endif // _INC_AMRTPNET
