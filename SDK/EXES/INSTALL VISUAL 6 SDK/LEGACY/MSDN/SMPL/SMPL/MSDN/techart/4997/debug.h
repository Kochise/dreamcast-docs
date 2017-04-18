//
// debug.h
//
// Provides basic debug services for C and C++ source modules.
//

#ifndef _INC_DEBUG
#define _INC_DEBUG

#ifdef __cplusplus
extern "C"
{
#endif
    extern char szDebug [];
#ifdef __cplusplus
}
#endif


//#define IDDEBUG   1

// Debug macros
#ifdef _DEBUG
#ifdef IDDEBUG
#define IDENTIFY() wsprintf (szDebug, "%s, %d: ", __FILE__, __LINE__); OutputDebugString (szDebug)
#else
#define IDENTIFY()
#endif
#define DOUT(fmt) IDENTIFY(); OutputDebugString (fmt)
#define DOUT1(fmt, p1) IDENTIFY(); wsprintf (szDebug, fmt, p1); OutputDebugString (szDebug)
#define DOUT2(fmt, p1, p2) IDENTIFY(); wsprintf (szDebug, fmt, p1, p2); OutputDebugString (szDebug)
#define DOUT3(fmt, p1, p2, p3) IDENTIFY(); wsprintf (szDebug, fmt, p1, p2, p3); OutputDebugString (szDebug)
#define DOUT4(fmt, p1, p2, p3, p4) IDENTIFY(); wsprintf (szDebug, fmt, p1, p2, p3, p4); OutputDebugString (szDebug)
#else
#define DOUT(fmt)
#define DOUT1(fmt, p1)
#define DOUT2(fmt, p1, p2)
#define DOUT3(fmt, p1, p2, p3)
#define DOUT4(fmt, p1, p2, p3, p4)
#endif

#endif // _INC_DEBUG