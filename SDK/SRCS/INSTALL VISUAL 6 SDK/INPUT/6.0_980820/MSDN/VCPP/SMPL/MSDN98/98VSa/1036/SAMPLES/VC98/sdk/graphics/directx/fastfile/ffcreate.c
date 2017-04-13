/*==========================================================================
 *
 *  Copyright (C) 1995-1997 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       ffcreate.c
 *  Content:	Fast file I/O for large numbers of files.
 *		Turns all files in a directory into a single file.
 *		This single file contains a directory + all the files.
 *
 * THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
 * EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
 * WARRANTIES OF MERCHANTBILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
 *
 ***************************************************************************/
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys\types.h>
#include <sys\stat.h>
#include <fcntl.h>
#include <io.h>
#include <malloc.h>

#ifdef __WATCOMC__
#define _open open
#define _close close
#define _lseek lseek
#define _read read
#define _write write
#define _stricmp stricmp
#define _S_IREAD S_IREAD
#define _S_IWRITE S_IWRITE
#endif

#include "ffent.h"

#define BLOCK_SIZE	16*1024

/*
 * Compare
 *
 * quicksort comparison routine
 */
int Compare( const LPFILEENTRY p1, const LPFILEENTRY p2 )
{
    return( _stricmp( (p1)->name,(p2)->name ) );
}

/*
 * main
 */
main( int argc, char *argv[] )
{
    HANDLE		dir;
    WIN32_FIND_DATA	fd;
    int			out;
    int			in;
    unsigned long	cnt;
    unsigned long	tmp;
    LPFILEENTRY		pfe;
    int			i;
    int			bytes;
    int			outbytes;
    char		*buff;
    char		*fname;
    char		*dename;
    long		pos;

    /*
     * get i/o buffer
     */
    buff = malloc( BLOCK_SIZE );
    if( buff == NULL ) {
	printf( "Out of memory!\n" );
	exit( 1 );
    }

    /*
     * get fastfile name, open file
     */
    if( argc < 2 ) {
	fname = "\\result.ff";
    } else {
	fname = argv[1];
    }
    printf( "Creating FastFile \"%s\"\n", fname );
    out = _open( fname, O_CREAT | O_TRUNC | O_WRONLY | O_BINARY,
    		_S_IREAD | _S_IWRITE );
    if( out < 0 ) {
	printf( "Could not open file \"%s\"", fname );
	exit( 1 );
    }

    /*
     * build a header
     */
    cnt = 0;
    printf( "Pass 1: building header\n" );
    dir = FindFirstFile( "*.*", &fd );
    if( dir == NULL ) {
	printf( "Could not open current directory\n" );
	_close( out );
	exit( 1 );
    }
    pfe = NULL;
    while( 1 ) {
	if( !(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ) {
	    cnt++;
	    pfe = realloc( pfe, (cnt+1) * sizeof( FILEENTRY ) );
	    memset( &pfe[cnt-1], 0, sizeof( FILEENTRY )*2 );
	    if( pfe == NULL ) {
		printf( "Out of memory!\n" );
		_close( out );
		exit( 1 );
	    }
	    dename = fd.cAlternateFileName;
	    if( dename[0] == 0 ) {
		dename = fd.cFileName;
	    }
	    printf( "File %d: %s                 \r", cnt, dename );
	    pfe[cnt-1].offset = 0;
	    strcpy( pfe[cnt-1].name, dename );
	}
	if( !FindNextFile( dir, &fd ) ) {
	    break;
	}
    }
    FindClose( dir );

    if( cnt == 0 ) {
	printf( "No files found!\n" );
	exit( 0 );
    }

    /*
     * sort the directory
     */
    qsort( pfe, cnt, sizeof( FILEENTRY ), (LPVOID) Compare );

    /*
     * write the number of directory entries + the directory
     */
    tmp = cnt+1;
    bytes = _write( out, &tmp, sizeof( tmp ) );
    if( bytes != sizeof( tmp ) ) {
	printf( "Error writing output file\n" );
	_close( out );
	exit( 1 );
    }
    bytes = _write( out, pfe, tmp * sizeof( FILEENTRY ) );
    if( bytes != (int) (tmp * sizeof( FILEENTRY )) ) {
	printf( "Error writing output file\n" );
	_close( out );
	exit( 1 );
    }

    /*
     * now read all of the files one by one and add them to the fastfile
     */
    printf( "Pass 2: adding data files                  \n" );
    for( i=0;i<(int)cnt;i++ ) {
	/*
	 * save current file position
	 */
	pfe[i].offset = _lseek( out, 0, SEEK_CUR );
	if( pfe[i].offset < 0 ) {
	    printf( "\nSeek error on output file\n" );
	    _close( out );
	    exit( 1 );
	}

	/*
	 * open next file to add
	 */
	in = _open( pfe[i].name, O_RDONLY | O_BINARY, 0 );
	printf( "File %d: \"%s\", offset=%ld                          \r",
				i+1, pfe[i].name, pfe[i].offset );
	if( in < 0 ) {
	    printf( "\nError opening file %s\n", pfe[i].name );
	    _close( out );
	    exit( 1 );
	}

	/*
	 * copy the data in the file
	 */
	while( 1 ) {
	    bytes = _read( in, buff, BLOCK_SIZE );
	    if( bytes == 0 ) {
		break;
	    }
	    if( bytes < 0 ) {
		printf( "\nError reading file %s\n", pfe[i].name );
		_close( in );
		_close( out );
		exit( 1 );
	    }
	    outbytes = _write( out, buff, bytes );
	    if( bytes != outbytes ) {
		printf( "\nError writing output file\n" );
		_close( in );
		_close( out );
		exit( 1 );
	    }
	    if( bytes < BLOCK_SIZE ) {
		break;
	    }
	}
	_close( in );
    }

    /*
     * get position of file end
     */
    pfe[i].offset = _lseek( out, 0, SEEK_CUR );

    /*
     * seek to the start of the directory (right after the # of entries)
     */
    pos = _lseek( out, sizeof( tmp ), SEEK_SET );
    if( pos != sizeof( tmp ) ) {
	printf( "Seek error on output file\n" );
	_close( out );
	exit( 1 );
    }

    /*
     * re-write the directory with the offsets setup
     */
    bytes = _write( out, pfe, tmp * sizeof( FILEENTRY ) );
    if( bytes != (int) (tmp * sizeof( FILEENTRY )) ) {
	printf( "Error writing output file\n" );
	_close( out );
	exit( 1 );
    }

    /*
     * all done
     */
    printf( "FastFile \"%s\" created:                   \n", fname );
    printf( "    %ld files\n", tmp );
    printf( "    %ld total file size\n", pfe[i].offset );

    _close( out );
    return 0;

} /* main */
