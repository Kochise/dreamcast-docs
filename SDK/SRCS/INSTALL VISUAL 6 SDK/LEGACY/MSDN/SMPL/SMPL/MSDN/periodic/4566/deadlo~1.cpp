#include <windows.h>
#include <stdio.h>
#include <process.h>
#pragma hdrstop
#include "deadlockdll.h"

CRITICAL_SECTION MyCritSect;

void SecondThreadFunction(void * p);    // prototype the second thread function

// Called in the context of the main thread
__declspec(dllexport) int __stdcall FunctionInADLL(void)
{
    // Inform user of our startup status
    printf( "In primary thread\n" );

    // Initialize and enter a run of the mill critical section
    InitializeCriticalSection( &MyCritSect );
    EnterCriticalSection( &MyCritSect );

    // Start up a second thread, which will cause DllMain to be invoked in
    // the context of the new thread.
    printf( "Starting second thread\n" );
    _beginthread( SecondThreadFunction, 0, 0 );

    // Make the main thread sleep, thereby giving the second thread enough
    // time to execute through DllMain and deadlock
    printf( "Sleeping(1) in primary thread\n" );
    Sleep( 2000 );                                  
    printf("Done sleeping(1) in primary thread\n");

    // At this point, thread 1 owns MyCritSect, while thread 2 is blocked
    // inside DllMain, waiting for MyCritSect.  Unfortunately, thread
    // 2 holds the process critical section, which GetProcAddress neeeds.
    #if 1
    printf( "Before calling GetProcAddress in primary thread\n" );
    GetProcAddress( GetModuleHandle("KERNEL32.DLL"), "XYZ" );
    printf( "After calling GetProcAddress in primary thread\n" );
    #endif

    // If the process critical section didn't deadlock us, we'd release the
    // app critical section, and the 2nd thread would execute OK.
    LeaveCriticalSection( &MyCritSect );

    // Make the main thread sleep again, thereby ensuring that the second
    // thread has time to complete before the first thread exits
    printf( "Sleeping(2) in primary thread\n" );
    Sleep( 2000 );                              
    printf("Done sleeping(2) in primary thread\n");

    DeleteCriticalSection( &MyCritSect );       // Cleanup code

    printf( "Returning from primary thread\n" );
    return 0;
}

void SecondThreadFunction(void * p)
{
    printf("  In SecondThreadFunction\n" );
}

int WINAPI DllMain( HANDLE hInst, ULONG reason, LPVOID lpReserved )
{
    if ( reason == DLL_THREAD_ATTACH )
    {
        printf("  In DllMain of 2nd thread - Before EnterCriticalSection\n" );
        EnterCriticalSection( &MyCritSect );
        printf("  In DllMain of 2nd thread - After EnterCriticalSection\n" );
        LeaveCriticalSection( &MyCritSect );
        printf("  In DllMain of 2nd thread - After LeaveCriticalSection\n" );
    }

    return 1;
}

Pietrek
Under the Hood
10/03/95
2:12 PM

1


