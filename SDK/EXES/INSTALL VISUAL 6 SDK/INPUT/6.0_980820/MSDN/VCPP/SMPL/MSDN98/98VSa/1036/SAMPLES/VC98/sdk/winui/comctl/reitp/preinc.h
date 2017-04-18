/*
 *	PREINC.H
 *
 *	DGreen
 */

#ifdef DEBUG
// define MEMCHECK to enable memory checking code
#define MEMCHECK
#endif

#ifdef MEMCHECK
// define INSTRUMENT_MEMMAN here to enable memory manager statistics
//#define INSTRUMENT_MEMMAN
#endif

#define BEGIN_CODESPACE_DATA data_seg(".text")
#define END_CODESPACE_DATA data_seg()

#ifdef DEBUG
#define MINTEST
#endif

#define LOCAL

#ifdef DLL
#define _DLL
#endif

#ifdef UNICODE
#define _UNICODE
#endif

#define DOSWIN32

#define STRICT

#define _INC_OLE

#define NOSHELLDEBUG //disables asserts in shell.h

#define MAPI_DIM


#ifdef DBCS
#define DBCS_EDIT RICHEDIT_CLASS
#else
#define DBCS_EDIT "Edit"
#endif
