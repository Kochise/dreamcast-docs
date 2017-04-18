/*
** sbinit.c Ver.0.60  1998/8/28
** Copyright (C) 1998 SEGA Enterprises Co.,Ltd
** All Rights Reserved
*/

#include <shinobi.h>      /* Shinobi header file. */
#include <sg_syhw.h>      /* Hardware initialization library. */

extern Uint8* _BSG_END;   /* End of BSG/BSG32 section. */

/* Program area address. */
#define P1AREA   0x80000000

/* Define work RAM end address. */
#define WORK_END (((Uint32)_BSG_END) & 0xe0000000 | 0x0d000000)


/* Modify the following values as necessary. */

/***** Ninja or Kamui *******************************/
#define	USE_NINJA 1       /* 0...Use Kamui graphics library. */
                          /* 1...Use Ninja graphics library (DEFAULT). */

/***** Controller Box *******************************/
#define USE_DCPAD 1       /* 0...Use Saturn Maple controller box. */
                          /* 1...Use Dreamcast controller box (DEFAULT). */

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

/* Total memory capacity available for syMalloc() is approximately 4MB. */
/* Define HEAP_SIZE only if heap not located at end of Section B. */
#if !USE_B_END
#define HEAP_SIZE 0x00400000
#endif


/* Declaration of global work area. */

Uint8 gMapleRecvBuf[1024 * 24 * 2 + 32];
Uint8 gMapleSendBuf[1024 * 24 * 2 + 32];

#if USE_GDFS
Uint8 gdfswork[GDFS_WORK_SIZE(FILES) + 32];
Uint8 gdfscurdir[GDFS_DIRREC_SIZE(BUFFERS) + 32];
#endif

/* Heap area for use by syMalloc(). */
#if USE_B_END
#define HEAP_AREA ((void*)((((Uint32)_BSG_END | P1AREA) & 0xffffffe0) + 0x20))
#define HEAP_SIZE (WORK_END - (Uint32)HEAP_AREA)
#else
#define HEAP_AREA ((void*)((Uint32)WORK_END - (Uint32)HEAP_SIZE))
#endif

/*
** Set2 njInitSystem() and Set5 sbInitSystem() arguments are interchangeable.
*/
void sbInitSystem(Int mode, Int frame, Int count)
{
    /* Keep changes to the following function calls to a minimum. */

    /* Disable interrupts using the specified mask (during initialization). */
    set_imask(15);

    /* Hardware initialization. */
    syHwInit();

    /* Initialize memory management system. */
    syMallocInit(HEAP_AREA, HEAP_SIZE);

#if USE_NINJA
    /* Ninja/Kamui initialization. */
    njInitSystem( mode, frame, count );
#else
    kmInitDevice( (mode&(KM_PAL|KM_NTSC|KM_VGA)) );
    kmSetDisplayMode( mode, frame, TRUE, FALSE);
    kmSetWaitVsyncCount( count );
#endif

    /* Additional hardware initialization. */
    syHwInit2();

    /* Controller library initialization. */
    pdInitPeripheral(PDD_PLOGIC_ACTIVE, gMapleRecvBuf, gMapleSendBuf);

    /* Initialize Timer lib. */
    syRtcInit();

    /* Enable all interrupts. */
    set_imask(0);

#if USE_GDFS
    {
        Uint8* wk;
        Uint8* dir;
        Sint32 err;
        Sint32 i;

        wk  = (Uint8*) (((Uint32) gdfswork & 0xffffffe0) + 0x20);
        dir = (Uint8*) (((Uint32) gdfscurdir & 0xffffffe0) + 0x20);

        /* Check the drive a reasonable number of times before failure. */
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

#if !USE_DCPAD
    pdSetMode (PDD_MODE_TYPE_A);
#endif
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

#if USE_NINJA
    /* Ninja/Kamui shutdown. */
    njExitSystem();
#endif

    /* Terminate memory management. */
    syMallocFinish();

    /* Reset hardware. */
    syHwFinish();

    /* Disable interrupts using the specified mask. */
    set_imask(15);
}


/******************************* end of file *******************************/