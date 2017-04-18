/***
*cmsgs.h - runtime errors
*
*       Copyright (c) 1990-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       The file defines, in one place, all error message strings used within
*       the C run-time library.
*
*       [Internal]
*
****/

#if _MSC_VER > 1000
#pragma once
#endif  /* _MSC_VER > 1000 */

#ifndef _INC_CMSGS
#define _INC_CMSGS

#ifndef _CRTBLD
/*
 * This is an internal C runtime header file. It is used when building
 * the C runtimes only. It is not to be used as a public header file.
 */
#error ERROR: Use of C runtime library internal header file.
#endif  /* _CRTBLD */

/*
 * runtime error and termination messages
 */

#ifdef _MAC
#define EOL "\n"
#else  /* _MAC */
#define EOL "\r\n"
#endif  /* _MAC */

#define _RT_STACK_TXT      "R6000" EOL "- stack overflow" EOL

#define _RT_FLOAT_TXT      "R6002" EOL "- floating point not loaded" EOL

#define _RT_INTDIV_TXT     "R6003" EOL "- integer divide by 0" EOL

#define _RT_SPACEARG_TXT   "R6008" EOL "- not enough space for arguments" EOL

#define _RT_SPACEENV_TXT   "R6009" EOL "- not enough space for environment" EOL

#define _RT_ABORT_TXT      "" EOL "abnormal program termination" EOL

#define _RT_THREAD_TXT     "R6016" EOL "- not enough space for thread data" EOL

#define _RT_LOCK_TXT       "R6017" EOL "- unexpected multithread lock error" EOL

#define _RT_HEAP_TXT       "R6018" EOL "- unexpected heap error" EOL

#define _RT_OPENCON_TXT    "R6019" EOL "- unable to open console device" EOL

#define _RT_NONCONT_TXT    "R6022" EOL "- non-continuable exception" EOL

#define _RT_INVALDISP_TXT  "R6023" EOL "- invalid exception disposition" EOL

/*
 * _RT_ONEXIT_TXT is specific to Win32 and Dosx32 platforms
 */
#define _RT_ONEXIT_TXT     "R6024" EOL "- not enough space for _onexit/atexit table" EOL

#define _RT_PUREVIRT_TXT   "R6025" EOL "- pure virtual function call" EOL

#define _RT_STDIOINIT_TXT  "R6026" EOL "- not enough space for stdio initialization" EOL

#define _RT_LOWIOINIT_TXT  "R6027" EOL "- not enough space for lowio initialization" EOL

#define _RT_HEAPINIT_TXT   "R6028" EOL "- unable to initialize heap" EOL

/*
 * _RT_DOMAIN_TXT, _RT_SING_TXT and _RT_TLOSS_TXT are used by the floating
 * point library.
 */
#define _RT_DOMAIN_TXT     "DOMAIN error" EOL

#define _RT_SING_TXT       "SING error" EOL

#define _RT_TLOSS_TXT      "TLOSS error" EOL


#define _RT_CRNL_TXT       EOL

#define _RT_BANNER_TXT     "runtime error "


#endif  /* _INC_CMSGS */
