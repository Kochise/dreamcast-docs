/* KallistiOS ##version##

   arch/ps2/include/sbios.h
   (c)2002 Dan Potter
   
   $Id: sbios.h,v 1.1 2002/10/27 23:39:23 bardtx Exp $
*/

#ifndef __PS2_SBIOS_H
#define __PS2_SBIOS_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>

#ifdef _arch_sub_rte	/* Only applies to the RTE */

/* Everything you ever wanted to know about the SBIOS interface and more! */

/* Misc notes divined by studying various code and mem dumps....

   Basic memory layout when booted from the RTE (either directly or via
   RedBoot:

   0x80000000 - 0x80000280: MIPS exception vectors (can be user-programmed)
   0x80000280 - 0x80010000: RTE kernel (called via SBIOS interface func)
   0x80001000:              RTE kernel SBIOS interface

  under RedBoot:
   0x80010000 - 0x80f00000: Available for usage
   0x80f00000 - 0x81000000: Reserved for eCos/RedBoot usage
   0x81000000 - 0x81fff000: Available for usage
  under raw RTE:
   0x80010000 - 0x81fff000: Available for usage

   0x81fff000 - 0x82000000: RTE bootstrap info (cmdline args, etc)

   When booted directly from the RTE, the standard MIPS prom boot
   convention is generally used, which is to pass in an argc, argv,
   and envp using the standard calling conventions. The PS2 cheats
   a little by overloading 'envp' to point to a full-sized ps2_bootinfo_t
   struct (below). You can verify that this is what you have for envp
   by checking the magic value against the constants below.

   When booting from RedBoot with 'go', you probably won't get those
   args (though I haven't checked for 100% sure). Instead, you can
   get a slightly truncated version of the ps2_bootinfo_t struct
   by peeking directly at the SBIOS interface at 0x80001000. This
   contains a 32-bit function pointer to the "sbios" function, which
   is what you talk to in order to do just about anything with the
   RTE. This is followed by a 32-bit magic value (constant below)
   which you can check to make sure nothing weird is going on.

 */

/****************************************** SBIOS Structs/Constants *****/

/* Real-time clock struct; used below in the boot time member. Everything
   in here is pretty obvious, except "year", which is 2000+year. Doesn't
   anyone EVER learn from their mistakes?! */
typedef struct ps2_rtc {
	uint8	junk1;
	uint8	sec;
	uint8	min;
	uint8	hour;
	uint8	junk2;
	uint8	day;
	uint8	mon;
	uint8	year;	/* <-- Y2K/Y2.1K non-compliant!! */
} ps2_rtc_t;

/* System configuration values; used below in the sysconf member. 
   I suppose that somewhere something describes what exactly these
   members mean... about the only thing I can guess at is "spdif",
   which is probably non-zero if using SPDIF audio output. Other
   than that... who knows. */
typedef struct ps2_sysconf {
	int16	time_zone;
	uint8	aspect;
	uint8	datenotation;
	uint8	language;
	uint8	spdif;
	uint8	summertime;
	uint8	timenotation;
	uint8	video;
} ps2_sysconf_t;

/* Boot info struct */
typedef struct ps2_bootinfo {
	/* Basic info */
	uint32		pccard_type;		/* ? */
	char		* args;			/* Command line args */
	uint32		res[2];			/* Reserved */
	ps2_rtc_t	boot_time;		/* Time when the system booted */
	uint32		mach_type;		/* Machine type (T10K, PS2) */
	uint32		pcic_type;		/* ? */
	ps2_sysconf_t	sysconf;		/* System config settings */

	/* "old" bootinfo struct stops here */
	
	uint32		magic;			/* Should be "P2LB" */
	int32		size;			/* Size of the bootinfo struct */
	uint32		sbios_base;		/* Base of the SBIOS structs */
	uint32		memsize;		/* Size of available memory (?) */
	
	/* Version strings */
	uint32		ver_stringsize;		/* Size of the total version string buffer */
	char 		* ver_string;		/* Pointer to the total version string buffer */
	char *		ver_strings[10];	/* Version strings for individual pieces */
} ps2_bootinfo_t;

/* Magic value for "new" bootinfo struct (when directly booting on RTE
   as opposed to under RedBoot, etc). "P2LB" == "PS2 Linux Boot"? */
#define PS2_BOOTINFO_MAGIC		0x50324c42	/* "P2LB" */

/* Machine types */
enum {
	PS2_MACH_TYPE_PS2 = 0,
	PS2_MACH_TYPE_T10K
};

/* Version string indeces */
enum {
	PS2_VER_VM = 0,
	PS2_VER_RB,
	PS2_VER_MODEL,
	PS2_VER_PS1DRV_ROM,
	PS2_VER_PS1DRV_HDD,
	PS2_VER_PS1DRV_PATH,
	PS2_VER_DVD_ID,
	PS2_VER_DVD_ROM,
	PS2_VER_DVD_HDD,
	PS2_VER_DVD_PATH
};

/* SBIOS-related constants */
#define PS2_SBIOS_BASE		0x80001000	/* Base of the SBIOS "old bootinfo" */
#define PS2_SBIOS_ENTRY_OFFS	0		/* SBIOS entry function */
#define PS2_SBIOS_MAGIC_OFFS	4		/* SBIOS magic offset */

/* We'll set these up in sbios_init(). */
int 		(* sbios_call)(int, void *);	/* SBIOS entry function */
ps2_bootinfo_t 	sbios_bootinfo;			/* Our bootinfo struct */
int		sbios_bootinfo_old;		/* Old-style bootinfo? */

/************************************************* SBIOS Calls/Args *****/

enum {
	PS2_SB_GETVER = 0,
	PS2_SB_HALT,
	PS2_SB_SETDVE,
	PS2_SB_PUTCHAR,
	PS2_SB_GETCHAR,
	PS2_SB_SETGSCRT,
	
	PS2_SB_SIFINIT = 0x10,
	PS2_SB_SIFEXIT,
	PS2_SB_SIFSETDMA,
	PS2_SB_SIFDMASTART,
	PS2_SB_SIFSETDCHAIN,
	
	PS2_SB_SIFINITCMD = 0x20,
	PS2_SB_SIFEXITCMD,
	PS2_SB_SIFSENDCMD,
	PS2_SB_SIFCMDINTRHDLR,
	PS2_SB_SIFADDCMDHANDLER,
	PS2_SB_SIFREMOVECMDHANDLER,
	PS2_SB_SIFSETCMDBUFFER,

	PS2_SB_SIFINITRPC = 0x30,
	PS2_SB_SIFEXITRPC,
	PS2_SB_SIFGETOTHERDATA,
	PS2_SB_SIFBINDRPC,
	PS2_SB_SIFCALLRPC,
	PS2_SB_SIFCHECKSTATRPC,
	PS2_SB_SIFSETRPCQUEUE,
	PS2_SB_SIFREGISTERRPC,
	PS2_SB_SIFREMOVERPC,
	PS2_SB_SIFREMOVERPCQUEUE,
	PS2_SB_SIFGETNEXTREQUEST,
	PS2_SB_SIFEXECREQUEST,

	PS2_SB_IOPH_INIT = 0x40,
	PS2_SB_IOPH_ALLOC,
	PS2_SB_IOPH_FREE,

	PS2_SB_PAD_INIT = 0x50,
	PS2_SB_PAD_END,
	PS2_SB_PAD_PORTOPEN,
	PS2_SB_PAD_PORTCLOSE,
	PS2_SB_PAD_SETMAINMODE,
	PS2_SB_PAD_SETACTDIRECT,
	PS2_SB_PAD_SETACTALIGN,
	PS2_SB_PAD_INFOPRESSMODE,
	PS2_SB_PAD_ENTERPRESSMODE,
	PS2_SB_PAD_EXITPRESSMODE,
	PS2_SB_PAD_READ,
	PS2_SB_PAD_GETSTATE,
	PS2_SB_PAD_GETREQSTATE,
	PS2_SB_PAD_INFOACT,
	PS2_SB_PAD_INFOCOMB,
	PS2_SB_PAD_INFOMODE

	// XXX More to add.. hands tired ;)
};


/********************************************* SBIOS Util Functions *****/

/* Initialize the SBIOS interface. If an SBIOS is properly detected and
   initialized, then we'll return 0; otherwise -1. */
int		sbios_init();

/* Shut down the SBIOS interface. */
void		sbios_shutdown();

#endif	/* _arch_sub_rte */

__END_DECLS

#endif	/* __PS2_SBIOS_H */

