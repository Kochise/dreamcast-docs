#ifdef WIN32
# ifndef __based
#  define __based(a)
# endif
#endif

#define DECLARE_REGUID(name, b) \
	EXTERN_C const GUID CDECL FAR name

// Comment out declaration of IID_IRichEditOleCallback
//  because it is already defined in richole.h
//
// DECLARE_REGUID(IID_IRichEditOleCallback,		0x03);
//
