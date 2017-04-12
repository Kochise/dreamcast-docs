/****************************************************************************
 *                                                                          *
 *      ntverp.H        -- Version information for internal builds          *
 *                                                                          *
 *      This file is only modified by the official builder to update the    *
 *      VERSION, VER_PRODUCTVERSION, VER_PRODUCTVERSION_STR and             *
 *      VER_PRODUCTBETA_STR values.                                         *
 *                                                                          *
 ****************************************************************************/

/*--------------------------------------------------------------*/
/* the following values should be modified by the official      */
/* builder for each build                                       */
/*                                                              */
/* the VER_PRODUCTBUILD lines must contain the product          */
/* comments (Win9x or NT) and end with the build#<CR><LF>       */
/*                                                              */
/* the VER_PRODUCTBETA_STR lines must  contain the product      */
/* comments (Win9x or NT) and end with "some string"<CR><LF>    */
/*--------------------------------------------------------------*/


#if defined(NASHVILLE)
#include <ieverp.h>
#else
#define VER_PRODUCTBUILD_QFE        1
#define VER_PRODUCTBUILD            /* NT */     1636
#define VER_PRODUCTBETA_STR         /* NT */     ""
#define VER_PRODUCTVERSION_STRING   "5.00"
#define VER_PRODUCTVERSION          5,00,VER_PRODUCTBUILD,VER_PRODUCTBUILD_QFE
#define VER_PRODUCTVERSION_W        (0x0500)
#define VER_PRODUCTVERSION_DW       (0x05000000 | VER_PRODUCTBUILD)


/*--------------------------------------------------------------*/
/* this value is used by third party drivers build with the DDK */
/* and internally, to avoid version number conflicts.           */
/*--------------------------------------------------------------*/
#define VER_DDK_PRODUCTVERSION       5,01
#define VER_DDK_PRODUCTVERSION_STR  "5.01"

#endif

#if 	(VER_PRODUCTBUILD < 10)
#define VER_BPAD "000"
#elif	(VER_PRODUCTBUILD < 100)
#define VER_BPAD "00"
#elif	(VER_PRODUCTBUILD < 1000)
#define VER_BPAD "0"
#else
#define VER_BPAD
#endif

#define VER_PRODUCTVERSION_STR2(x,y) VER_PRODUCTVERSION_STRING "." VER_BPAD #x "." #y
#define VER_PRODUCTVERSION_STR1(x,y) VER_PRODUCTVERSION_STR2(x, y)
#define VER_PRODUCTVERSION_STR       VER_PRODUCTVERSION_STR1(VER_PRODUCTBUILD, VER_PRODUCTBUILD_QFE)

/*--------------------------------------------------------------*/
/* the following section defines values used in the version     */
/* data structure for all files, and which do not change.       */
/*--------------------------------------------------------------*/

/* default is nodebug */
#if DBG
#define VER_DEBUG                   VS_FF_DEBUG
#else
#define VER_DEBUG                   0
#endif

/* default is prerelease */
#if BETA
#define VER_PRERELEASE              VS_FF_PRERELEASE
#else
#define VER_PRERELEASE              0
#endif

#define VER_FILEFLAGSMASK           VS_FFI_FILEFLAGSMASK
#define VER_FILEOS                  VOS_NT_WINDOWS32
#define VER_FILEFLAGS               (VER_PRERELEASE|VER_DEBUG)

#define VER_COMPANYNAME_STR         "Microsoft Corporation"
#define VER_PRODUCTNAME_STR         "Microsoft(R) Windows NT(R) Operating System"
#define VER_LEGALTRADEMARKS_STR     \
"Microsoft(R) is a registered trademark of Microsoft Corporation. Windows NT(R) is a registered trademark of Microsoft Corporation."
