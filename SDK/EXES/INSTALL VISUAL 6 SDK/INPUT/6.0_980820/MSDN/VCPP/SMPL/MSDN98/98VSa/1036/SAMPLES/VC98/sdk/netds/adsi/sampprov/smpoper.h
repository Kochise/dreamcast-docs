/*++

Copyright (c) 1996 Microsoft Corporation

Module Name:

    SmpOper.h

Abstract:

Author:

Environment:

    User mode

Revision History :

--*/
#ifndef _SMPOPER_H_
#define _SMPOPER_H_

HRESULT
SampleDSTypeFreeSampleDSSynId1(
    PSampleDSOBJECT lpSampleDSDestObject
    );

HRESULT
SampleDSTypeFreeSampleDSSynId2(
    PSampleDSOBJECT lpSampleDSDestObject
    );

HRESULT
SampleDSTypeClear(
    PSampleDSOBJECT lpSampleDSDestObject
    );

void
SampleDSTypeFreeSampleDSObjects(
    PSampleDSOBJECT pSampleDSObject,
    DWORD dwNumValues
    );

HRESULT
SampleDSTypeCopySampleDSSynId1(
    PSampleDSOBJECT lpSampleDSSrcObject,
    PSampleDSOBJECT lpSampleDSDestObject
    );

HRESULT
SampleDSTypeCopySampleDSSynId2(
    PSampleDSOBJECT lpSampleDSSrcObject,
    PSampleDSOBJECT lpSampleDSDestObject
    );

HRESULT
SampleDSTypeCopy(
    PSampleDSOBJECT lpSampleDSSrcObject,
    PSampleDSOBJECT lpSampleDSDestObject
    );

HRESULT
SampleDSTypeCopyConstruct(
    LPSampleDSOBJECT pSampleDSSrcObjects,
    DWORD dwNumObjects,
    LPSampleDSOBJECT * ppSampleDSDestObjects
    );

HRESULT
UnMarshallSampleDSToSampleDSSynId(
    DWORD dwSyntaxId,
    DWORD dwNumValues,
    LPBYTE lpValue,
    PSampleDSOBJECT * ppSampleDSObject
    );

LPBYTE
CopySampleDS1ToSampleDSSynId1(
    LPBYTE lpByte,
    PSampleDSOBJECT lpSampleDSObject
    );
       
LPBYTE
CopySampleDS2ToSampleDSSynId2(
    LPBYTE lpByte,
    PSampleDSOBJECT lpSampleDSObject
    );

LPBYTE
CopySampleDSToSampleDSSynId(
    DWORD dwSyntaxId,
    LPBYTE lpByte,
    PSampleDSOBJECT lpSampleDSObject
    );

HRESULT
MarshallSampleDSSynIdToSampleDS(
    DWORD dwSyntaxId,
    PSampleDSOBJECT pSampleDSObject,
    DWORD dwNumValues,
    LPBYTE lpValue
    );

LPBYTE
CopySampleDSSynId1ToSampleDS1(
    LPBYTE lpByte,
    PSampleDSOBJECT lpSampleDSObject
    );

LPBYTE
CopySampleDSSynId2ToSampleDS2(
    LPBYTE lpByte,
    PSampleDSOBJECT lpSampleDSObject
    );

LPBYTE
CopySampleDSSynIdToSampleDS(
    DWORD dwSyntaxId,
    LPBYTE lpByte,
    PSampleDSOBJECT lpSampleDSObject
    );


void
VarTypeFreeVarObjects(
    VARIANT *pVarObject,
    DWORD dwNumValues
    );

HRESULT
SampleDSTypeToVarTypeCopySampleDSSynId1(
    PSampleDSOBJECT lpSampleDSSrcObject,
    VARIANT *lpVarDestObject
    );

HRESULT
SampleDSTypeToVarTypeCopySampleDSSynId2(
    PSampleDSOBJECT lpSampleDSSrcObject,
    PVARIANT lpVarDestObject
    );


HRESULT
SampleDSTypeToVarTypeCopy(
    PSampleDSOBJECT lpSampleDSSrcObject,
    VARIANT* lpVarDestObject
    );

HRESULT
SampleDSTypeToVarTypeCopyConstruct(
    LPSampleDSOBJECT pSampleDSSrcObjects,
    DWORD dwNumObjects,
    VARIANT *pVarDestObjects
    );

HRESULT
VarTypeToSampleDSTypeCopySampleDSSynId1(
    PVARIANT lpVarSrcObject,
    PSampleDSOBJECT lpSampleDSDestObject
    );

HRESULT
VarTypeToSampleDSTypeCopySampleDSSynId2(
    PVARIANT lpVarSrcObject,
    PSampleDSOBJECT lpSampleDSDestObject
    );

HRESULT
VarTypeToSampleDSTypeCopy(
    DWORD dwSampleDSType,
    PVARIANT lpVarSrcObject,
    PSampleDSOBJECT lpSampleDSDestObject
    );

HRESULT
VarTypeToSampleDSTypeCopyConstruct(
    DWORD dwSampleDSType,
    LPVARIANT pVarSrcObjects,
    DWORD dwNumObjects,
    LPSampleDSOBJECT * ppSampleDSDestObjects
    );

#endif

