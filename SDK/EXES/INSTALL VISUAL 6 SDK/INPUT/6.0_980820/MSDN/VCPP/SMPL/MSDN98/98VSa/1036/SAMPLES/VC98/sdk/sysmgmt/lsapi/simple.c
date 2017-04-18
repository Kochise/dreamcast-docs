/*
 *  This is a part of the Microsoft Source Code Samples.
 *  Copyright 1996-1997 Microsoft Corporation.
 *  All rights reserved.
 *
 *  The following example uses the minimum amount of code required to
 *  utilize any licensing system.  This example is provided on the SDK
 *  and can be used to familiarize oneself with a licensing system or
 *  as a template for an application.  Note that the code exits if a
 *  grant cannot be obtained.  Recall that this is strictly an
 *  application's decision and is not dictated by any licensing system
 *  which adheres to the LSAPI standard.
 */

#include <stdio.h>
#include <stdlib.h>
#include "windows.h"

/*
 * Include the LSAPI header file.
 */
#include "lsapi.h"

/*
 * Define the product name, product version, and publisher name for
 * use with the licensing calls.
 */
#define MYAPP_PRODUCT_NAME    "sample_product"
#define MYAPP_PRODUCT_VERSION "1.0"
#define MYAPP_PUBLISHER_NAME  "sample_publishers"

/*
 * Define the strings used to log a comment with the license system.
 */
#define MYAPP_REQUEST_LOG_COMMENT "Comment for the LSRequest call"
#define MYAPP_RELEASE_LOG_COMMENT "Comment for the LSRelease call"

/*
 * Forward declarations
 */
void PrintErrors( LS_HANDLE handle, LS_STATUS_CODE errorCode );


__cdecl main()
{
   /*
    * LSAPI Variables
    */
   LS_ULONG        unitsGranted;
   LS_HANDLE       licenseHandle;
   LS_STATUS_CODE  status;

   /************ the following code is for the LSAPI beta only! ************/
   char            szProviderPath[ MAX_PATH ];
   UINT            nChars;

   /* install if necessary */
   nChars = GetSystemDirectory( szProviderPath, sizeof( szProviderPath ) );
   if ( 0 == nChars )
   {
      printf( "Can't get system directory, error %d.\n", GetLastError() );
   }

   lstrcat( szProviderPath, "\\mslsp32.dll" );
   status = LSInstall( szProviderPath );
   if ( LS_SUCCESS != status )
   {
      printf( "Cannot install LSAPI, error 0x%08lx.\n", status );
   }

   /* add licenses for our product */
   status = LSLicenseUnitsSet( LS_ANY,
                               MYAPP_PUBLISHER_NAME,
                               MYAPP_PRODUCT_NAME,
                               MYAPP_PRODUCT_VERSION,
                               LS_LICENSE_TYPE_NODE,
                               LS_NULL,
                               1,
                               0,
                               NULL );
   if ( LS_SUCCESS != status )
   {
      printf( "Cannot install licenses, error 0x%lx.\n", status );
   }
   /************ the above code is for the LSAPI beta only! ************/

   /*
    * Make the call to request a grant
    */
   status = LSRequest(
         LS_ANY,                               /* Use any licensing system */
         (LS_STR FAR *)MYAPP_PUBLISHER_NAME,   /* Publisher name           */
         (LS_STR FAR *)MYAPP_PRODUCT_NAME,     /* Product name             */
         (LS_STR FAR *)MYAPP_PRODUCT_VERSION,  /* Version number           */
         LS_DEFAULT_UNITS,                     /* Let license figure units */
         (LS_STR FAR *)MYAPP_REQUEST_LOG_COMMENT, /* Log comment         */
         0,                                    /* No Challenge             */
         &unitsGranted,                        /* # units granted          */
         &licenseHandle );                     /* license context          */

   /*
    * Check whether we got a successful grant.  If not, then call a routine
    * which prints out the error message, free the license handle, and do
    * not continue running the application.
    */
   if ( LS_SUCCESS != status )
      {
      PrintErrors( licenseHandle, LS_USE_LAST );
      LSFreeHandle( licenseHandle );
      return(1);
      }

   /*
    * Continue with the application.
    */
   printf("Hello World\n");


   /*
    * We are now done with the application, so we must make a call
    * to release the grant.
    */
   status = LSRelease(
         licenseHandle,                        /* License context          */
         LS_DEFAULT_UNITS,                     /* Let license figure units */
         (LS_STR FAR *)MYAPP_RELEASE_LOG_COMMENT);/* Log comment         */
   if ( LS_SUCCESS != status )
      {
      PrintErrors( licenseHandle, status );
      LSFreeHandle( licenseHandle );
      return( 1 );
      }

   /*
    * Free the license handle.
    */
   LSFreeHandle( licenseHandle );


   exit( 0 );
}


void PrintErrors( LS_HANDLE handle, LS_STATUS_CODE errorCode )
{
   LS_STATUS_CODE   status;
   char             errorText[200];


   errorText[0] = 0;

   status = LSGetMessage( handle, errorCode, (LS_STR FAR *)errorText, 200);
   if ( LS_TEXT_UNAVAILABLE == status )
      printf("Error: No message catalog available.\n");
   else
      if ( LS_UNKNOWN_STATUS == status )
         printf("Error: Unknown error code was used.\n");
      else
         printf("Error: %s\n", errorText);
}
