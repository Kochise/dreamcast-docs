//
//  CS Sample Header File
//

#ifdef _UNICODE
#ifndef UNICODE
#define UNICODE
#endif
#endif

#if 0

#ifndef _vstprintf 

#ifdef UNICODE
#define _vstprintf vsprintf
#else
#define _vstprintf vswprintf
#endif	// UNICODE

#endif	// _vstprintf 

#endif

#define MAX_MESSAGE 100
#define BUFFER_SIZE 256
#define XSTART      5
#define YSTART      40
