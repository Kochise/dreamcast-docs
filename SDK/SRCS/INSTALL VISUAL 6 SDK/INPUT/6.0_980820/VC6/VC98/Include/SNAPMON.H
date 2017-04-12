
/*****************************************************************************/
/* snapmon.h - include for the SNA Perfmon Interface                         */
/* Copyright (c) Microsoft Corporation 1995 - 1996                           */
/*****************************************************************************/


#ifdef __cplusplus
extern "C"
{
#endif


typedef struct adaptercounter {
    ULONG          count;
    ULONG          type;
    LONG           scale;
} ADAPTERCOUNTER;

typedef struct adapterperfdata {
    ULONG          inuse;
    ULONG          ServiceNameIndex;
    ULONG          FirstCounterIndex;

    ADAPTERCOUNTER TotalBytesReceived;
    ADAPTERCOUNTER TotalBytesTransmitted;
    ADAPTERCOUNTER TotalFramesReceived;
    ADAPTERCOUNTER TotalFramesTransmitted;
    ADAPTERCOUNTER SuccessfulConnects;
    ADAPTERCOUNTER ConnectionFailures;
    ADAPTERCOUNTER TotalBytesThroughput;
    ADAPTERCOUNTER TotalFramesThroughput;
    ADAPTERCOUNTER AdapterFailures;
    ADAPTERCOUNTER reserved[11];

    ULONG          pad;
} ADAPTERPERFDATA;

extern void              WINAPI SNAInitLinkPerfmon(HANDLE *, void **);
extern ADAPTERPERFDATA * WINAPI SNAGetLinkPerfArea(HANDLE, ADAPTERPERFDATA *);
extern USHORT            WINAPI SNAGetPerfValues(int *, int *);
extern USHORT            WINAPI SNAGetPNodePerfVals(int *, int *);


#ifdef __cplusplus
}
#endif
