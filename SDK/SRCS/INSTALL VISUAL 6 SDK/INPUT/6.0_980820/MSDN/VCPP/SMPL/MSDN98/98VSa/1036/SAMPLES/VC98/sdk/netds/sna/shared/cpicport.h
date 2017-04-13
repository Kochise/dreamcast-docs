/*****************************************************************************
 *
 *  MODULE NAME: CPICPORT.H
 *
 *  COPYRIGHTS:
 *             This module contains code made available by IBM
 *             Corporation on an AS IS basis.  Any one receiving the
 *             module is considered to be licensed under IBM copyrights
 *             to use the IBM-provided source code in any way he or she
 *             deems fit, including copying it, compiling it, modifying
 *             it, and redistributing it, with or without
 *             modifications.  No license under any IBM patents or
 *             patent applications is to be implied from this copyright
 *             license.
 *
 *             A user of the module should understand that IBM cannot
 *             provide technical support for the module and will not be
 *             responsible for any consequences of use of the program.
 *
 *             Any notices, including this one, are not to be removed
 *             from the module without the prior written consent of
 *             IBM.
 *
 *  AUTHOR:    Peter J. Schwaller
 *             VNET:     PJS at RALVM6           Tie Line: 444-4376
 *             Internet: pjs@ralvm6.vnet.ibm.com     (919) 254-4376
 *
 *  AVAILABILITY:
 *             These sample programs and source are also available on
 *             CompuServe through the APPC Information Exchange.  To get
 *             to the APPC forum just type 'GO APPC' from any CompuServe
 *             prompt.  The samples are available in the Sample Programs
 *             library section.  Just search on the keyword CPICPGMS to
 *             find all the samples in this series.
 *
 *             Updates for the sample programs and support for many more
 *             CPI-C platforms will also be made available on CompuServe.
 *
 *  RELATED FILES:
 *             Used by CPICPORT.C
 *
 *  CHANGE HISTORY:
 *  Date       Description
 *  08/05/92   Version 2.31 of APING, ATELL and AREXEC released to CompuServe.
 *             This version was also distributed at the APPC/APPN Platform
 *             Developer's Conference held in Raleigh, NC.
 *  08/13/92   Added the write_*() calls.
 *             Changed all printf and fprintf calls to use a write_*() call.
 *
 *****************************************************************************/

#ifndef INCL_CPICPORT
#define INCL_CPICPORT

/*
 * This file contains all of the non-portable code for the CPI-C toolkit.
 * Conditional compilation directives determine what code will be compiled
 * for which platform.  The following constants have been established
 * to identify the supported platforms:
 *    DOS   - Networking Services/DOS
 *    OS2   - Extended Services for OS/2
 *    FAPI  - Compiling for both DOS and OS2
 *    AIX   - SNA Services
 *    OS400 - OS/400 (for the AS/400)
 *    MVS   - MVS ESA 4.2 or greater
 *    VM    - VM/CMS ESA 1.0 or greater
 *    WIN32 - Windows NT v3.1
 *    WINDOWS - Windows v3.1
 * These constants should be defined outside of the source code on
 * your compiler command line (e.g., cc -DOS2 foo.c).
 *
 * If you are porting to another platform, you should only use new constant
 * if you don't fit into any of the above categories.  To avoid name
 * conflicts please contact the supplier of this file, indicated above.
 */


/*
 * Set up the various constant definitions for:
 *    EBCDIC_HOST
 *    BIG_ENDIAN
 *    SHORT_IDENTIFIERS
 *    DOES_NOT_NEED_STRUPR
 *    SUPPORTS_SETTING_SECURITY
 *    PLN_COULD_REQUIRE_LOWERCASE
 *    ECS_NOT_SUPPORTED
 */
#include "cpicdefs.h"

/*
 * Include CPICERRS.H file for the definition of the CPICERR structure.
 */
#include "cpicerrs.h"



#define TIMELENGTH                 26
#define MAX_MESSAGE_LENGTH        (300+1)


#ifdef SHORT_IDENTIFIERS
/* The C/370 compiler requires that identifier be unique in the 1st 8 chars. */
    #define  ascii_to_ebcdic_field        a2efield
    #define  ascii_to_ebcdic_table        a2etab
    #define  ebcdic_to_ascii_field        e2afield
    #define  ebcdic_to_ascii_table        e2atab
#endif


#ifdef EBCDIC_HOST

#define convert_to_ascii(buffer, len)  ebcdic_to_ascii_field(buffer,len)
#define convert_from_ascii(buffer, len) ascii_to_ebcdic_field(buffer,len)

#else

#define convert_to_ascii(buffer, len)
#define convert_from_ascii(buffer, len)

#endif



/*
 * If we are on a big endian machine, we will convert the integer format
 * to little endian before sending the integers.  This is done through
 * a set of macros to swap the byte order.
 *
 * Programs should use the following macros before sending:
 *   convert_long_to_network     -- 32 bit integers
 *   convert_short_to_network    -- 16 bit integers
 *
 * Programs should use the following macros after receiving:
 *   convert_long_from_network   -- 32 bit integers
 *   convert_short_from_network  -- 16 bit integers
 *
 * Application code should use these macros before sending or receiving
 * any integers.  On a big endian platform, the macros will return a
 * a byte swapping of the integer.  On a little endian platform,
 * the original integer will be returned unmodified (no-op).
 */
#ifdef BIG_ENDIAN

#define  convert_long_to_network(x)        SWAP4(x)
#define  convert_short_to_network(x)       SWAP2(x)
#define  convert_long_from_network(x)      SWAP4(x)
#define  convert_short_from_network(x)     SWAP2(x)

#    ifndef SWAP2
/* Macro SWAP2 swaps the bytes in a two-byte integer         */
#    define SWAP2(s)       (unsigned short)(((s)<<8)|(((s)&0xFF00)>>8))
#    endif

#    ifndef SWAP4
/* Macro SWAP4 swaps the bytes in a four-byte integer        */
#    define SWAP4(l)       (unsigned long)(((l)<<24)|(((l)&0xFF000000)>>24)\
                           |(((l)&0xFF00)<<8)|(((l)&0xFF0000)>>8))
#    endif


#else
/*
 * If the platform is little endian, we don't have to do any byte
 * order changing of the integers.
 */
#define  convert_long_to_network(x)        x
#define  convert_short_to_network(x)       x
#define  convert_long_from_network(x)      x
#define  convert_short_from_network(x)     x
#    ifndef SWAP2
/* Macro SWAP2 swaps the bytes in a two-byte integer         */
#    define SWAP2(s)       (unsigned short)(((s)<<8)|(((s)&0xFF00)>>8))
#    endif

#    ifndef SWAP4
/* Macro SWAP4 swaps the bytes in a four-byte integer        */
#    define SWAP4(l)       (unsigned long)(((l)<<24)|(((l)&0xFF000000)>>24)\
                           |(((l)&0xFF00)<<8)|(((l)&0xFF0000)>>8))
#    endif

#endif





/*
 * Function prototypes
 */

void           write_error(            char *fmt, ...);
void           write_output(           char *fmt, ...);
void           write_log(              FILE * file,
                                       char *fmt, ...);

char CM_PTR    alloc_cpic_buffer(      unsigned int size);

void           show_info(              char * * text);

void           set_echo(               int mode);

int            get_password(           char * password,
                                       int max_length);

unsigned long  get_time(               void);

void           display_message(        char * destination,
                                       char * userid,
                                       char * message);


void           datetime(               char *);

void           do_exit(                int rc);

void           ascii_to_ebcdic_field(  unsigned char * ascii_field,
                                       unsigned int field_size);
void           ebcdic_to_ascii_field(  unsigned char * ebcdic_field,
                                       unsigned int field_size);

void           execute_and_send_output(char * command,
                                       unsigned char * cm_conv_id,
                                       struct error_handler_cpicerr * cpicerr);
void		   free_cpic_buffer(	   void *memblock ); 
#endif
