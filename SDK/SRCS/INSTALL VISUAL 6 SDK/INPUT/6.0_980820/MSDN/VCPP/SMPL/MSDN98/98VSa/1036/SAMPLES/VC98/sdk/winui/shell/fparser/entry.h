	/*
	|	These are #define that would have been put in vwdefs.h,
	|	but they need to be defined before vwdefs.h is included in
	|	vsctop.h so the filter writers can use them, especially
	|	VWPRT, in their own include file, which is included
	|	before vwdefs.h
	*/


#define WINDOWS

#ifdef WIN32

#define VWPTR
#define VW_ENTRYSC	__declspec(dllexport)
#define VW_ENTRYMOD	__cdecl
#define VW_LOCALSC
#define VW_LOCALMOD	__cdecl
#define VW_SEPARATE_DATA

#endif /*WIN32*/

