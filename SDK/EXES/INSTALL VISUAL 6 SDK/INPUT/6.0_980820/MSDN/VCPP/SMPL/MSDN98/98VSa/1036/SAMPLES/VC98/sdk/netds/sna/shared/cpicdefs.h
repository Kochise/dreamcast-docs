/*****************************************************************************
 *
 *  MODULE NAME: CPICDEFS.H
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
 *  08/01/92   This file was created.
 *  08/05/92   Version 2.31 of APING, ATELL and AREXEC released to CompuServe.
 *             This version was also distributed at the APPC/APPN Platform
 *             Developer's Conference held in Raleigh, NC.
 *  08/17/92   Added FAPI to list of SUPPORTS_SETTING_SECURITY.
 *  01/06/93   Added OS2_20 to list of SUPPORTS_SETTING_SECURITY.
 *
 *
 *****************************************************************************/

#ifndef INCL_CPICDEFS
#define INCL_CPICDEFS


/*
 * Define the operating system string.
 */

#define OPSYS_STRING    "Windows NT 3.1"

#define DOES_NOT_NEED_STRUPR

/*
 * There are a few CPI-C extensions that are not supported across all
 * platforms and a few local names that are handled differently.  Many
 * of these are treated the same on a group of platforms.  To avoid
 * testing for each platform throughout the code, I have established
 * a number of constants that indicate whether a feature is supported
 * or not.
 *
 * If you are porting this application to another platform, you can
 * add your platform to the list with an or (||) clause.
 */

/*
 * Setting security type and userid/password information is not part of
 * the SAA CPI-C base.
 *
 * This constant is referenced in the CPICINIT.C file.
 */
#if defined(OS2) || defined(DOS) || defined(VM) || defined(AIX) || \
    defined(FAPI) || defined(OS2_20)
#define SUPPORTS_SETTING_SECURITY
#endif

/*
 * On most platforms partner LU names will always be in uppercase.
 * Some platforms allow you to specify a partner LU name that can
 * contain lowercase characters (e.g., OS/2 partner LU aliases).
 * If this constant is defined, the partner LU name will only be
 * converted to uppercase if it is a fully qualified LU name.
 *
 * This constant is referenced in the CPICINIT.C file.
 */
#if defined(OS2) || defined(FAPI) || defined(OS2_20) \
    || defined (AIX)
#define PLN_COULD_REQUIRE_LOWERCASE
#endif

/*
 * Some platforms do not support the base function, Extract Conversation
 * State.
 *
 * This constant is referenced in the CPICERR.C file.
 */
#if defined(OS400) || defined(MVS)
#define  ECS_NOT_SUPPORTED
#endif



/* min and max macros */
#ifndef max
#define max(a,b)        (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)        (((a) < (b)) ? (a) : (b))
#endif


#ifndef TRUE
#define  TRUE  (1)
#endif

#ifndef FALSE
#define  FALSE (0)
#endif


#endif
