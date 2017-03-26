#include <stdio.h>
#include <stdlib.h>

#define FILENAME_IP_BIN    "IP.BIN"
#define FILESIZE_IP_BIN    32768

void main( int argc, char* argv[1] )
{
	FILE*	fpIPBIN;
	FILE*	fpSource;
	FILE*	fpDest;

   if( argc != 3 )
   {
      printf( "IP.BIN Binary Inserter - by Fulg\n" );
      printf( "Usage: %s <source> <dest>\n\n", argv[0] );
      printf( "Will overwrite the first %d bytes of <source> with the contents\n"
              "of %s, assumed to be in the current directory. "
              "Result stored in <dest>.\n", FILESIZE_IP_BIN, FILENAME_IP_BIN );
      exit( -1 );
   }

   fpIPBIN = fopen( FILENAME_IP_BIN, "rb" );
   if( !fpIPBIN )
   {
      printf( "%s: Cannot open IP.BIN\n", argv[0] );
      exit( -2 );
   }

	fpSource = fopen( argv[1], "rb" );
   if( !fpSource )
   {
      printf( "%s: Cannot open %s\n", argv[0], argv[1] );
      exit( -3 );
   }

   fpDest = fopen( argv[2], "wb" );
   if( !fpDest )
   {
      printf( "%s: Cannot open %s\n", argv[0], argv[2] );
      exit( -4 );
   }

   fseek( fpSource, 0, SEEK_END );
   int iSourceSize = ftell( fpSource );
   fseek( fpSource, 0, SEEK_SET );

   unsigned char* pWorkBuf = (unsigned char*)malloc( iSourceSize );
   if( !pWorkBuf )
   {
      printf( "%s: Cannot allocate work buffers\n", argv[0] );
      exit( -5 );
   }

   // read original file in memory...
   fread( pWorkBuf, iSourceSize, 1, fpSource );

   // overlay IP.BIN
   fread( pWorkBuf, FILESIZE_IP_BIN, 1, fpIPBIN );

   // write merged file
   fwrite( pWorkBuf, iSourceSize, 1, fpDest );

   fclose( fpSource );
   fclose( fpDest );
   fclose( fpIPBIN );

   free( pWorkBuf );

   printf( "%s: done, %s inserted\n", argv[0], FILENAME_IP_BIN );

   exit(0);
}

