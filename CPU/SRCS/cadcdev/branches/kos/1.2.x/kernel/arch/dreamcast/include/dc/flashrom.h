/* KallistiOS ##version##

   kernel/arch/dreamcast/include/dc/flashrom.h
   Copyright (C)2003 Dan Potter

   $Id: flashrom.h,v 1.4 2003/03/10 01:45:32 bardtx Exp $
*/


#ifndef __DC_FLASHROM_H
#define __DC_FLASHROM_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>

/**
  \file Implements wrappers for the BIOS flashrom syscalls, and some
  utilities to make it easier to use the flashrom info. Note that
  because the flash writing can be such a dangerous thing potentially
  (I haven't deleted my flash to see what happens, but given the
  info stored here it sounds like a Bad Idea(tm)) the syscalls for
  the WRITE and DELETE operations are not enabled by default. If you
  are 100% sure you really want to be writing to the flash and you
  know what you're doing, then you can edit flashrom.c and re-enable
  them there. */

/**
  An enumeration of partitions available in the flashrom. */
#define FLASHROM_PT_SYSTEM	0	//< Factory settings (read-only, 8K)
#define FLASHROM_PT_RESERVED	1	//< reserved (all 0s, 8K)
#define FLASHROM_PT_BLOCK_1	2	//< Block allocated (16K)
#define FLASHROM_PT_SETTINGS	3	//< Game settings (block allocated, 32K)
#define FLASHROM_PT_BLOCK_2	4	//< Block allocated (64K)

/**
  Implements the FLASHROM_INFO syscall; given a partition ID,
  return two ints specifying the beginning and the size of
  the partition (respectively) inside the flashrom. Returns zero
  if successful, -1 otherwise. */
int flashrom_info(int part, int * start_out, int * size_out);

/**
  Implements the FLASHROM_READ syscall; given a flashrom offset,
  an output buffer, and a count, this reads data from the
  flashrom. Returns the number of bytes read if successful,
  or -1 otherwise. */
int flashrom_read(int offset, void * buffer_out, int bytes);

/**
  Implements the FLASHROM_WRITE syscall; given a flashrom offset,
  an input buffer, and a count, this writes data to the flashrom.
  Returns the number of bytes written if successful, -1 otherwise.

  NOTE: It is not possible to write ones to the flashrom over zeros.
  If you want to do this, you must save the old data in the flashrom,
  delete it out, and save the new data back. */
int flashrom_write(int offset, void * buffer, int bytes);

/**
  Implements the FLASHROM_DELETE syscall; given a partition offset,
  that entire partition of the flashrom will be deleted and all data
  will be reset to FFs. Returns zero if successful, -1 on failure. */
int flashrom_delete(int offset);



/* Higher level functions */

/**
  Language settings possible in the BIOS menu. These will be returned
  from flashrom_get_language(). */
#define FLASHROM_LANG_JAPANESE	0
#define FLASHROM_LANG_ENGLISH	1
#define FLASHROM_LANG_GERMAN	2
#define FLASHROM_LANG_FRENCH	3
#define FLASHROM_LANG_SPANISH	4
#define FLASHROM_LANG_ITALIAN	5

/**
  This struct will be filled by calling the flashrom_get_syscfg call
  below. */
typedef struct flashrom_syscfg {
	int	language;	//< Language setting (see defines above)
	int	audio;		//< 0 == mono, 1 == stereo
	int	autostart;	//< 0 == off, 1 == on
} flashrom_syscfg_t;

/**
  Retrieves the current syscfg settings and fills them into the struct
  passed in to us. */
int flashrom_get_syscfg(flashrom_syscfg_t * out);


/**
  Region settings possible in the system flash (partition 0). */
#define FLASHROM_REGION_UNKNOWN	0
#define FLASHROM_REGION_JAPAN	1
#define FLASHROM_REGION_US	2
#define FLASHROM_REGION_EUROPE	3

/**
  Retrieves the console's region code. This is still somewhat 
  experimental, it may not function 100% on all DCs. Returns
  one of the codes above or -1 on error. */
int flashrom_get_region();


/* More to come later */

__END_DECLS

#endif	/* __DC_FLASHROM_H */

