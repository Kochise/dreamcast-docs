///////////////////////////////////////////////////////////////////////////////
//
//  File Name 
//      TRACES.H
//
//  Description
//      Function declaration for the API's in TRACES.CPP
//
//  Author
//      Irving De la Cruz
//
//  Revision: 1.3
//
// Written for Microsoft Windows Developer Support
// Copyright (c) 1994-1996 Microsoft Corporation. All rights reserved.
//

#ifndef _TRACES_H
#define _TRACES_H

///////////////////////////////////////////////////////////////////////////////
//  Function prototype for the debug functions used to trace and log output 
//  messages
//
#include <OBJBASE.H>

#define TRACES_CONSOLE              0x00000001
#define TRACES_LOG_FILE             0x00000002
#define TRACES_NO_COM_OUTPUT        0x00000004
#define TRACES_NO_ASSERTS           0x00000008
#define TRACES_NO_ASSERT_DIALOG     0x00000010

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#ifdef ENABLE_DEBUG_OUTPUT

void WINAPI InitTraces (DWORD dwFlags);
void WINAPI UnInitTraces ();

void WINAPI  TraceFn1 (LPSTR);
void WINAPI  TraceFn2 (LPSTR, ULONG);
void WINAPI  TraceFn3 (LPSTR);
void __cdecl TraceFn4 (BOOL, LPSTR, ...);
void WINAPI  TraceIO  (ULONG);
void WINAPI  TraceIO2 (LPSTR, ULONG);

#ifndef TRACES_NO_MAPI
void WINAPI TraceProp (ULONG);
#else
#define TraceProp(a)
#endif // TRACES_NO_MAPI

#define TraceString1(a,b)           TraceFn4 (FALSE, a, b)
#define TraceString2(a,b,c)         TraceFn4 (FALSE, a, b, c)
#define TraceString3(a,b,c,d)       TraceFn4 (FALSE, a, b, c, d)
#define TraceString4(a,b,c,d,e)     TraceFn4 (FALSE, a, b, c, d, e)

#define TraceMessage(a)             TraceFn1 (a)
#define TraceMessageIf(a, b)        {if (b) TraceFn1 (a); }
#define TraceRaw(a)                 TraceFn3 (a)

// These functions will trace only if the error is non-zero
#define TraceRPCError(a,b)          {if (b) TraceFn4 (FALSE, "%s, RPC error: %d",a, b);}
#define TraceSysError(a,b)          {if (b) TraceFn4 (FALSE, "%s, Systen Error: %d",a, b);}
#define TraceResult(a, b)           {if (b) TraceFn2 (a, b);}
#define TraceDebugger(a,b)          TraceFn4 (TRUE, a, b)

void WINAPI AssertStatement (LPSTR, ULONG);
void WINAPI AssertStatementWithMsg (LPSTR, LPSTR, ULONG);

#ifndef ASSERT
#define ASSERT(a)           {if (!(a)) AssertStatement (__FILE__, __LINE__);}
#endif // ASSERT
#define ASSERTMSG(a, b)     {if (!(a)) AssertStatementWithMsg (b, __FILE__, __LINE__);}

#ifndef VERIFY
#define VERIFY(a)       ASSERT(a)
#endif // VERIFY

#ifdef  DISABLE_INFO_TRACES
#define TraceInfoMessage(a)
#else  // DISABLE_INFO_TRACES
#define TraceInfoMessage(a)     TraceFn1 (a)
#endif // DISABLE_INFO_TRACES

#else // ENABLE_DEBUG_OUTPUT

#define TraceMessage(a)
#define TraceMessageIf(a, b)
#define TraceInfoMessage(a)
#define TraceResult(a, b)
#define TraceIO(a)              a
#define TraceIO2(a, b)
#define TraceProp(a)
#define TraceRPCError(a,b)
#define TraceSysError(a,b)
#define TraceString1(a,b)
#define TraceString2(a,b,c)
#define TraceString3(a,b,c,d)
#define TraceString4(a,b,c,d,e)
#define TraceRaw(a)
#define TraceDebugger(a,b)

#ifndef ASSERT
#define ASSERT(a)
#endif // ASSERT
#define ASSERTMSG(a, b)

#ifndef VERIFY
#define VERIFY(a)               a
#endif // VERIFY

#define InitTraces(a)
#define UnInitTraces()

#endif // ENABLE_DEBUG_OUTPUT

#define AssertSz(a, b)      ASSERTMSG(a, b)

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _TRACES_H

// End of file for TRACES.H
