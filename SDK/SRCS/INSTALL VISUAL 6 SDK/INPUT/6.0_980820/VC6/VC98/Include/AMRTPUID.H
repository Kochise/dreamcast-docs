///*M*
// INTEL CORPORATION PROPRIETARY INFORMATION
// This software is supplied under the terms of a licence agreement or
// nondisclosure agreement with Intel Corporation and may not be copied
// or disclosed except in accordance with the terms of that agreement.
// Copyright (c) 1997 Intel Corporation. All Rights Reserved.
//
// Filename : AMRTPUID.h
// Purpose  : Define the UIDs used in the ActiveMovie RTP architecture.
// Contents : 
//      MEDIATYPE_RTP_Single_Stream     Defines an RTP stream which
//          only contains media samples from a single source.
//      MEDIATYPE_RTP_Multiple_Stream   Defines an RTP stream which
//          may contain media samples from many sources (eg, a multicast
//          conference.)
//      MEDIASUBTYPE_RTP_Payload_Mixed  A subtype of MEDIATYPE_RTP_Multiple_Stream,
//          indicates that the stream may consist or RTP packets with
//          many different PT values.
//      MEDIASUBTYPE_RTP_Payload_G711U  A subtype of MEDIATYPE_RTP_Single_Stream
//          or MEDIATYPE_RTP_Multiple_Stream. Indicates that the stream(s)
//          are all of the same payload type (e.g., G.711 Mulaw Audio)
//      MEDIASUBTYPE_RTP_Payload_G711A  A subtype of MEDIATYPE_RTP_Single_Stream
//          or MEDIATYPE_RTP_Multiple_Stream. Indicates that the stream(s)
//          are all of the same payload type (e.g., G.711 Alaw Audio)
//      MEDIASUBTYPE_RTP_Payload_G723   A subtype of MEDIATYPE_RTP_Single_Stream
//          or MEDIATYPE_RTP_Multiple_Stream. Indicates that the stream(s)
//          are all of the same payload type (e.g., G.723 Audio)
//      MEDIASUBTYPE_RTP_Payload_H261   A subtype of MEDIATYPE_RTP_Single_Stream
//          or MEDIATYPE_RTP_Multiple_Stream. Indicates that the stream(s)
//          are all of the same payload type (e.g., H.261 Video)
//      MEDIASUBTYPE_RTP_Payload_H263 A subtype of MEDIATYPE_RTP_Single_Stream
//          or MEDIATYPE_RTP_Multiple_Stream. Indicates that the stream(s)
//          are all of the same payload type (e.g., H.263 Video)
//      MEDIASUBTYPE_RTP_Payload_ANY  A subtype of MEDIATYPE_RTP_Single_Stream
//          or MEDIATYPE_RTP_Multiple_Stream. Indicates that the stream(s)
//          are all of the same payload type, but the actual type is not set. 
//      MEDIASUBTYPE_H263EX   A subtype of MEDIATYPE_Video.  Indicates that the stream(s) 
//          are all of the same media type (e.g., H.263 Extended Bitstream Video)
//      MEDIASUBTYPE_H261EX   A subtype of MEDIATYPE_Video.  Indicates that the stream(s) 
//          are all of the same media type (e.g., H.261 Extended Bitstream Video)
//*M*/

#ifndef OUR_GUID_ENTRY
    #define OUR_GUID_ENTRY(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
        DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8);
#endif

// {14099BC0-787B-11d0-9CD3-00A0C9081C19}
OUR_GUID_ENTRY(MEDIATYPE_RTP_Single_Stream, 
0x14099bc0, 0x787b, 0x11d0, 0x9c, 0xd3, 0x0, 0xa0, 0xc9, 0x8, 0x1c, 0x19);

// {14099BC1-787B-11d0-9CD3-00A0C9081C19}
OUR_GUID_ENTRY(MEDIATYPE_RTP_Multiple_Stream, 
0x14099bc1, 0x787b, 0x11d0, 0x9c, 0xd3, 0x0, 0xa0, 0xc9, 0x8, 0x1c, 0x19);

// {14099BC2-787B-11d0-9CD3-00A0C9081C19}
OUR_GUID_ENTRY(MEDIASUBTYPE_RTP_Payload_Mixed, 
0x14099bc2, 0x787b, 0x11d0, 0x9c, 0xd3, 0x0, 0xa0, 0xc9, 0x8, 0x1c, 0x19);

// {14099BC3-787B-11d0-9CD3-00A0C9081C19}
OUR_GUID_ENTRY(MEDIASUBTYPE_RTP_Payload_G711U, 
0x14099bc3, 0x787b, 0x11d0, 0x9c, 0xd3, 0x0, 0xa0, 0xc9, 0x8, 0x1c, 0x19);

// {14099BC4-787B-11d0-9CD3-00A0C9081C19}
OUR_GUID_ENTRY(MEDIASUBTYPE_RTP_Payload_G711A, 
0x14099bc4, 0x787b, 0x11d0, 0x9c, 0xd3, 0x0, 0xa0, 0xc9, 0x8, 0x1c, 0x19);

// {14099BC5-787B-11d0-9CD3-00A0C9081C19}
OUR_GUID_ENTRY(MEDIASUBTYPE_RTP_Payload_G723, 
0x14099bc5, 0x787b, 0x11d0, 0x9c, 0xd3, 0x0, 0xa0, 0xc9, 0x8, 0x1c, 0x19);

// {14099BC6-787B-11d0-9CD3-00A0C9081C19}
OUR_GUID_ENTRY(MEDIASUBTYPE_RTP_Payload_H261, 
0x14099bc6, 0x787b, 0x11d0, 0x9c, 0xd3, 0x0, 0xa0, 0xc9, 0x8, 0x1c, 0x19);

// {14099BC7-787B-11d0-9CD3-00A0C9081C19}
OUR_GUID_ENTRY(MEDIASUBTYPE_RTP_Payload_H263, 
0x14099bc7, 0x787b, 0x11d0, 0x9c, 0xd3, 0x0, 0xa0, 0xc9, 0x8, 0x1c, 0x19);

// {14099BCA-787B-11d0-9CD3-00A0C9081C19}
OUR_GUID_ENTRY(MEDIASUBTYPE_RTP_Payload_ANY, 
0x14099bc8, 0x787b, 0x11d0, 0x9c, 0xd3, 0x0, 0xa0, 0xc9, 0x8, 0x1c, 0x19);

// {33363248-0000-0010-8000-00AA00389B71}
OUR_GUID_ENTRY(MEDIASUBTYPE_H263, 
0x33363248, 0x0000, 0x0010, 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71);

// {14099BC8-787B-11d0-9CD3-00A0C9081C19}
OUR_GUID_ENTRY(MEDIASUBTYPE_H263EX, 
0x14099bc8, 0x787b, 0x11d0, 0x9c, 0xd3, 0x0, 0xa0, 0xc9, 0x8, 0x1c, 0x19);

// {31363248-0000-0010-8000-00AA00389B71}
OUR_GUID_ENTRY(MEDIASUBTYPE_H261, 
0x31363248, 0x0000, 0x0010, 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71);

// {14099BC9-787B-11d0-9CD3-00A0C9081C19}
OUR_GUID_ENTRY(MEDIASUBTYPE_H261EX, 
0x14099bc9, 0x787b, 0x11d0, 0x9c, 0xd3, 0x0, 0xa0, 0xc9, 0x8, 0x1c, 0x19);

#undef OUR_GUID_ENTRY

