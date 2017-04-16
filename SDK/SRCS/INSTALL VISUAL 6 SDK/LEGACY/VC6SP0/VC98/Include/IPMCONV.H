// --ipmconv.h----------------------------------------------------------------
//
// API entry points for the inbound and outbound sample gateway
// message conversion DLLs.
//
// The ipm_out DLL converts MAPI messages to an 822-style header.
// This is the "Outbound IPM Converter". 
//
// The ipm_in DLL converts an 822-style header to a MAPI message.
// This is the "Inbound IPM Converter".
//
// Copyright (C) Microsoft Corp., 1986-1996.  All rights reserved.
//
// ---------------------------------------------------------------------------

#ifndef _IPMCONV_H
#define _IPMCONV_H

#ifdef __cplusplus
extern "C" {
#endif

// Supported conversion message class prefixes.
#define IPMENVELOPECLASS    L"ENVELOPE.IPM"
#define IPMREPORTCLASS      L"REPORT.IPM"

// $--CONV_OPTIONS-------------------------------------------------------------
//
// Conversion options for the IPM Inbound and Outbound conversion
// DLLs.  This structure is passed to the conversion DLL via the 
// pGatewayDefined field of the EDKCNVENV conversion environment
// structure (defined in convstrc.h).
//
// ----------------------------------------------------------------------------
typedef struct _CONV_OPTIONS
{
    BOOL    fTnefEncode;            // TRUE if want Tnef encoding/decoding
    LPCSTR  lpszAddressType;        // Address type string

} CONV_OPTIONS;

// $--HrGetExportVector--------------------------------------------------------
//
// DESCRIPTION: Gets pointer to exported functions/vectors structures
//              for either the inbound or outbound converter.
//
// INPUT:       dwVersion   --  version requested
//
// OUTPUT:      ppExportVectors --  pointer to export vector structure pointer
//
// RETURNS:     HRESULT     --  NOERROR if successful,
//                              E_INVALIDARG if invalid parameter,
//
// ---------------------------------------------------------------------------

HRESULT HrGetExportVector(
        IN DWORD dwVersion,         // version requested
        OUT PCONVDLLVECT * ppExportVectors);  // pointer to exported functions structure

#ifdef __cplusplus
}
#endif

#endif
