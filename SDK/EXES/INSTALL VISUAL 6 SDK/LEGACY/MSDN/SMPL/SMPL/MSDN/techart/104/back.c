///////////////////////////////////////////////////////////////////////////
// Back to the Future -
// ---- -- --- ------
//	Sample Application which compiles and runs under both DOS and Windows.
//
// 
//
//

//////////////////////////////////////////
// Setup for Windows version
//
#ifdef _WINDOWS
#include <windows.h>
#include <windowsx.h>

#include "trace.h"	// Header file for DLL

#define BUFSIZE 1024

extern const HINSTANCE _hInstance ;

void useInstance() ;

#else

//////////////////////////////////////////
// Setup for MS-DOS version
//
#define trace printf
#endif

///////////////////////////////////////////
// Header files common to MS-DOS and Windows
//
#include <stdlib.h>
#include <stdio.h>

//////////////////////////////////////////////
// This sample uses main() instead of WinMain.
//
void main( int argc, char *argv[], char **envp )
{
	int count;
	
	// Display each command-line argument.
		trace( "\r\nCommand-line arguments:\r\n");
		for ( count = 0; count < argc; count++)
			trace(" argv[%d] %s\n", count, argv[count] ) ;
	
	// Display each environment variable.
		trace( "\r\nEnvironment variables:\r\n") ;
		while(*envp != NULL)
			trace( " %s\r\n", *(envp++) ) ;

#ifdef _WINDOWS
	// Demonstrate how to get to _hInstance.
	useInstance() ;
#endif

		return ;
}


#ifdef _WINDOWS

////////////////////////////////////////////
// This function is called only in the Windows
// version. It shows how to access hInstance when 
// using main() instead of WinMain() as an entry.
//
void useInstance()
{
		char * buf ;
		
		// Demonstrate use of malloc
			buf = (char *)malloc( BUFSIZE ) ;

		// Print out that we are compiled for Windows.
			trace("\r\nWindows Version:\r\n") ;
		
		// Demonstrate using _hInstance.
			GetModuleFileName(_hInstance, buf, BUFSIZE ) ;
			trace("nModule Filename: %s\r\n",(LPSTR)buf) ;	
			
		// Be nice and free memory.
			free(buf) ;
}

#endif //_WINDOWS



