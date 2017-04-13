
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1993-1997  Microsoft Corporation.  All Rights Reserved.
//
//  MODULE:   commdef.h
//
//  PURPOSE:  Define types and values for communication.
//

typedef struct _CLIENT_IO_RETURN_DATA
{
   DWORD ByteCount;
}
CLIENT_IO_RETURN_DATA, *PCLIENT_IO_RETURN_DATA;

typedef struct _CLIENT_IO_I_AM_DONE
{
   DWORD TotalTicks;
   DWORD TotalIterations;
   DWORD TotalBytesTransferred;
}
CLIENT_IO_I_AM_DONE, *PCLIENT_IO_I_AM_DONE;

//
// Message types
//
#define CLIENT_IO_MT_RETURN_DATA    1
#define CLIENT_IO_MT_I_AM_DONE      2

typedef struct _CLIENT_IO_BUFFER
{
   DWORD MessageType;
   union
   {
      CLIENT_IO_RETURN_DATA ReturnData;
      CLIENT_IO_I_AM_DONE IAmDone;
   }
   u;
}
CLIENT_IO_BUFFER, *PCLIENT_IO_BUFFER;


#define CLIENT_OUTBOUND_BUFFER_MAX  1024

//
// Choose an arbitrary port number.  May need to be changed if
// it conflicts with an existing application.
//
#define SERVPORT 12396
