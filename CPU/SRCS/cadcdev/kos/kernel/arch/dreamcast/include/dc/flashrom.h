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
  An enumeration of logical blocks available in the flashrom. */
#define FLASHROM_B1_SYSCFG	0x05	//< System config (BLOCK_1)
#define FLASHROM_B1_IP_SETTINGS	0xE0	//< IP settings for BBA (BLOCK_1)
#define FLASHROM_B1_EMAIL	0xE2	//< Email address (BLOCK_1)
#define FLASHROM_B1_SMTP	0xE4	//< SMTP server setting (BLOCK_1)
#define FLASHROM_B1_POP3	0xE5	//< POP3 server setting (BLOCK_1)
#define FLASHROM_B1_POP3LOGIN	0xE6	//< POP3 login setting (BLOCK_1)
#define FLASHROM_B1_POP3PASSWD	0xE7	//< POP3 password setting + proxy (BLOCK_1)
#define FLASHROM_B1_PPPLOGIN	0xE8	//< PPP username + proxy (BLOCK_1)
#define FLASHROM_B1_PPPPASSWD	0xE9	//< PPP passwd (BLOCK_1)

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


/* Medium-level functions */
/**
  Returns a numbered logical block from the requested partition. The newest
  data is returned. 'buffer_out' must have enough room for 60 bytes of
  data. */
int flashrom_get_block(int partid, int blockid, uint8 * buffer_out);


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

/**
  Method constants for the ispcfg struct */
#define FLASHROM_ISP_DHCP	0
#define FLASHROM_ISP_STATIC	1
#define FLASHROM_ISP_DIALUP	2
#define FLASHROM_ISP_PPPOE	4

/**
  This struct will be filled by calling flashrom_get_isp_settings below.
  Thanks to Sam Steele for this info. */
typedef struct flashrom_ispcfg {
	int	ip_valid;	//< >0 if the IP settings are valid
	int	method;		//< DHCP, Static, dialup(?), PPPoE
	uint8	ip[4];		//< Host IP address
	uint8	nm[4];		//< Netmask
	uint8	bc[4];		//< Broadcast address
	uint8	gw[4];		//< Gateway address
	uint8	dns[2][4];	//< DNS servers (2)
	char	hostname[24];	//< DHCP/Host name

	int	email_valid;	//< >0 if the email setting is valid
	char	email[48];	//< Email address

	int	smtp_valid;	//< >0 if the smtp setting is valid
	char	smtp[28];	//< SMTP server

	int	pop3_valid;	//< >0 if the pop3 setting is valid
	char	pop3[24];	//< POP3 server

	int	pop3_login_valid;	//< >0 if the login setting is valid
	char	pop3_login[20];		//< POP3 login

	int	pop3_passwd_valid;	//< >0 if the passwd/proxy setting is valid
	char	pop3_passwd[32];	//< POP3 passwd
	char	proxy_host[16];		//< Proxy server hostname

	int	ppp_login_valid;	//< >0 if the PPP login/proxy setting is valid
	int	proxy_port;		//< Proxy server port
	char	ppp_login[8];		//< PPP login

	int	ppp_passwd_valid;	//< >0 if the PPP passwd setting is valid
	char	ppp_passwd[20];		//< PPP password
} flashrom_ispcfg_t;

/**
  Retrieves the console's ISP settings, if they exist. These are set by
  programs like Dream Passport 3. Returns -1 on error (none of the settings
  can be found, or some other error), or >=0 on success. You should check
  the _valid member of the matching part of the struct before relying on
  the data. */
int flashrom_get_ispcfg(flashrom_ispcfg_t * out);

/* More to come later */

__END_DECLS

#endif	/* __DC_FLASHROM_H */

