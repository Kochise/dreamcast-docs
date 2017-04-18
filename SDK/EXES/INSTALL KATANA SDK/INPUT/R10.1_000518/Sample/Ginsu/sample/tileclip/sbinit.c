/*
** sbinit.c 
** Copyright (C) 2000 Sega of America Dreamcast
** All Rights Reserved
*/

#include <shinobi.h>      /* Shinobi header file. */
#include <sg_syhw.h>      /* Hardware initialization library. */

/* One of the following graphics APIs must be defined. */
#ifdef _KAMUI2_
#include <kamui2.h>
#endif

#ifdef _KMDARK_
#include <kamui2.h>
#include <kmyami.h>
#include "init.h"
#endif

#ifdef _NINJA_
#include <ninja.h>
#endif

extern Uint8* _BSG_END;   /* End of BSG/BSG32 section (start of free memory). */

/* SH-4 program area address. */
#define P1AREA   0x80000000

/* Define work RAM end address (16 MB). */
#define WORK_END (((Uint32) _BSG_END) & 0xe0000000 | 0x0d000000)


/* Modify the following values as necessary. */

/***** GD Filesystem *******************************/
#define USE_GDFS 1        /* 0...No Filesystem. */
                          /* 1...Use GD Filesystem (DEFAULT). */

/***** Heap Location at end of Section B ***********/
#define USE_B_END 1       /* 0...No heap at Section B, specify HEAP_SIZE manually. */
                          /* 1...Heap located at end of Section B (DEFAULT) */

/* GD: Maximum number of files opened simultaneously. */
#define FILES 8

/* GD: Number of buffers for the current directory. */
#define BUFFERS 1024

/* Total memory capacity available for syMalloc() is 4MB in this sample heap definition. */
/* Define HEAP_SIZE only if heap not located at end of Section B. */
#if !USE_B_END
#define HEAP_SIZE 0x00400000
#endif

/* Declaration of global work area for Maple (control pads). */
Uint8 gMapleRecvBuf[1024 * 24 * 2 + 32];
Uint8 gMapleSendBuf[1024 * 24 * 2 + 32];

/* GD Filesystem directory and file handle tables. */
#if USE_GDFS
Uint8 gdfswork[GDFS_WORK_SIZE(FILES) + 32];
Uint8 gdfscurdir[GDFS_DIRREC_SIZE(BUFFERS) + 32];
#endif

/* Heap area for use by syMalloc(). */
#if USE_B_END
#define HEAP_AREA ((void*) ((((Uint32) _BSG_END | P1AREA) & 0xffffffe0) + 0x20))
#define HEAP_SIZE (WORK_END - (Uint32) HEAP_AREA)
#else
#define HEAP_AREA ((void*) ((Uint32) WORK_END - (Uint32) HEAP_SIZE))
#endif

#if defined(__MWERKS__) || defined (__GNUC__)
/* Global constructor/destructor section addresses. */
extern void * _START_DSG_INIT_;
extern void * _END_DSG_INIT_;
extern void * _START_DSG_END_ ;
extern void * _END_DSG_END_ ;

#ifdef __cplusplus
extern "C" {
#endif
extern void __call_static_initializers (void);
extern void __destroy_global_chain (void);
extern void __do_global_ctors (void);
extern void __do_global_dtors (void);
#ifdef __cplusplus
}
#endif

/* C++ global constructor support for Metrowerks CodeWarrior and GCC. */
void syStartGlobalConstructorAlt ( void )
{
    void (*pf)();
    Uint32 *adr;

    for( adr = (Uint32 *) (&_START_DSG_INIT_);
         adr < (Uint32 *) (&_END_DSG_INIT_); adr++ ){
        if( !( ( *adr == 0x00000000) ||
               ( *adr == 0xFFFFFFFF) )){
			pf = (void(*)())( *adr );
			(*pf)();
		}
    }
#ifdef __MWERKS__
    __call_static_initializers();
#endif
#ifdef __GNUC__
    __do_global_ctors();
#endif
}

/* C++ global destructor support for Metrowerks CodeWarrior and GCC. */
void syStartGlobalDestructorAlt ( void )
{
   void (*pf)();
    Uint32 *adr;

    for( adr = (Uint32 *) (&_START_DSG_END_) ;
    	 adr < (Uint32 *) (&_END_DSG_END_) ;
    	 adr++ ){
        if( !( ( *adr == 0x00000000) ||
               ( *adr == 0xFFFFFFFF) )){
     		pf = (void(*)())( *adr );
     		(*pf)();
      	}
    }
#ifdef __MWERKS__
    __destroy_global_chain();
#endif
#ifdef __GNUC__
    __do_global_dtors();
#endif
}
#endif


/*
** Initialize Shinobi
*/

void sbInitSystem (Int mode, Int frame, Int count)
{
    /* Keep changes to the following function calls to a minimum. */

    /* Disable all interrupts (during initialization). */
    set_imask(15);

    /* Hardware initialization. */
    syHwInit();

    /* Initialize memory management system. */
    syMallocInit (HEAP_AREA, HEAP_SIZE);

    /* Initialize C++ global constructors (also required for C applications). */
#if defined(__MWERKS__) || defined (__GNUC__)
    syStartGlobalConstructorAlt();
#else
    syStartGlobalConstructor();
#endif

    /* Graphics initialization. */
#ifdef _KAMUI2_
    kmInitDevice (KM_DREAMCAST);
    kmSetDisplayMode (mode, frame, TRUE, FALSE);
    kmSetWaitVsyncCount (count);
#endif

#ifdef _KMDARK_
    Initialize (mode, frame);
#endif

#ifdef _NINJA_
    njInitSystem (mode, frame, count);
#endif

    /* Additional hardware initialization. */
    syHwInit2();

    /* Controller library initialization. */
    pdInitPeripheral (PDD_PLOGIC_ACTIVE, gMapleRecvBuf, gMapleSendBuf);

    /* Initialize timer library. */
    syRtcInit();

    /* Enable all interrupts. */
    set_imask(0);

#if USE_GDFS
    /* GD Filesystem initialization. */
    {
        Uint8* wk;
        Uint8* dir;
        Sint32 err;
        Sint32 i;

        wk  = (Uint8*) (((Uint32) gdfswork & 0xffffffe0) + 0x20);
        dir = (Uint8*) (((Uint32) gdfscurdir & 0xffffffe0) + 0x20);

        /* Check the drive a reasonable number of times before failure (do not loop). */
        for (i = 8; i > 0; i--)
        {
            err = gdFsInit (FILES, wk, BUFFERS, dir);

            if (err == GDD_ERR_TRAYOPEND || err == GDD_ERR_UNITATTENT)
            {
                sbExitSystem();
                syBtExit();
            }
            else if (err == GDD_ERR_OK)
            {
                break;
            }
        }

        if (i == 0)
        {
            sbExitSystem();
            syBtExit();
        }
    }
#endif

    /* Additional user initialization goes here. */
	;
}


/*
** Shutdown the system.
*/

void sbExitSystem(void)
{
#if USE_GDFS
    /* Shutdown GD filesystem. */
    gdFsFinish();
#endif

    /* Shutdown Timer lib. */
    syRtcFinish();

    /* Terminate controller library. */
    pdExitPeripheral();

    /* Graphics shutdown. */
#ifdef _KAMUI2_
    kmUnloadDevice();
#endif

#ifdef _KMDARK_
    Finalize();
#endif

#ifdef _NINJA_
    njExitSystem();
#endif

    /* Call C++ global destructors. */
#if defined(__MWERKS__) || defined (__GNUC__)
    syStartGlobalDestructorAlt();
#else
    syStartGlobalDestructor();
#endif

    /* Terminate memory management. */
    syMallocFinish();

    /* Reset hardware. */
    syHwFinish();

    /* Disable interrupts using the specified mask. */
    set_imask(15);
}

/******************************* end of file *******************************/