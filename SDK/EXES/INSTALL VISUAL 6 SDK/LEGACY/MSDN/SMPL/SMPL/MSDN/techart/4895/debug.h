//
// debug.h
//

// Debug macros
#ifdef _DEBUG
char szDebug [256];
#define DOUT(fmt) OutputDebugString (fmt)
#define DOUT1(fmt, p1) wsprintf (szDebug, fmt, p1); OutputDebugString (szDebug)
#define DOUT2(fmt, p1, p2) wsprintf (szDebug, fmt, p1, p2); OutputDebugString (szDebug)
#define DOUT3(fmt, p1, p2, p3) wsprintf (szDebug, fmt, p1, p2, p3); OutputDebugString (szDebug)
#define DOUT4(fmt, p1, p2, p3, p4) wsprintf (szDebug, fmt, p1, p2, p3, p4); OutputDebugString (szDebug)
#else
#define DOUT(fmt)
#define DOUT1(fmt, p1)
#define DOUT2(fmt, p1, p2)
#define DOUT3(fmt, p1, p2, p3)
#define DOUT4(fmt, p1, p2, p3, p4)
#endif
