/* KallistiOS ##version##

   dc/maple/keyboard.h
   (C)2000-2002 Jordan DeLong and Dan Potter

   $Id: keyboard.h,v 1.3 2002/05/18 07:11:44 bardtx Exp $
*/

#ifndef __DC_MAPLE_KEYBOARD_H
#define __DC_MAPLE_KEYBOARD_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>

/* modifier keys */
#define KBD_MOD_LCTRL 		(1<<0)
#define KBD_MOD_LSHIFT		(1<<1)
#define KBD_MOD_LALT		(1<<2)
#define KBD_MOD_S1		(1<<3)
#define KBD_MOD_RCTRL		(1<<4)
#define KBD_MOD_RSHIFT		(1<<5)
#define KBD_MOD_RALT		(1<<6)
#define KBD_MOD_S2		(1<<7)

/* bits for leds : this is not comprensive (need for japanese kbds also) */
#define KBD_LED_NUMLOCK		(1<<0)
#define KBD_LED_CAPSLOCK	(1<<1)
#define KBD_LED_SCRLOCK		(1<<2)

/* defines for the keys (argh...) */
#define KBD_KEY_NONE		0x00
#define KBD_KEY_ERROR		0x01
#define KBD_KEY_A		0x04
#define KBD_KEY_B		0x05
#define KBD_KEY_C		0x06
#define KBD_KEY_D		0x07
#define KBD_KEY_E		0x08
#define KBD_KEY_F		0x09
#define KBD_KEY_G		0x0a
#define KBD_KEY_H		0x0b
#define KBD_KEY_I		0x0c
#define KBD_KEY_J		0x0d
#define KBD_KEY_K		0x0e
#define KBD_KEY_L		0x0f
#define KBD_KEY_M		0x10
#define KBD_KEY_N		0x11
#define KBD_KEY_O		0x12
#define KBD_KEY_P		0x13
#define KBD_KEY_Q		0x14
#define KBD_KEY_R		0x15
#define KBD_KEY_S		0x16
#define KBD_KEY_T		0x17
#define KBD_KEY_U		0x18
#define KBD_KEY_V		0x19
#define KBD_KEY_W		0x1a
#define KBD_KEY_X		0x1b
#define KBD_KEY_Y		0x1c
#define KBD_KEY_Z		0x1d
#define KBD_KEY_1		0x1e
#define KBD_KEY_2		0x1f
#define KBD_KEY_3		0x20
#define KBD_KEY_4		0x21
#define KBD_KEY_5		0x22
#define KBD_KEY_6		0x23
#define KBD_KEY_7		0x24
#define KBD_KEY_8		0x25
#define KBD_KEY_9		0x26
#define KBD_KEY_0		0x27
#define KBD_KEY_ENTER		0x28
#define KBD_KEY_ESCAPE		0x29
#define KBD_KEY_BACKSPACE	0x2a
#define KBD_KEY_TAB		0x2b
#define KBD_KEY_SPACE		0x2c
#define KBD_KEY_MINUS		0x2d
#define KBD_KEY_PLUS		0x2e
#define KBD_KEY_LBRACKET	0x2f
#define KBD_KEY_RBRACKET	0x30
#define KBD_KEY_BACKSLASH	0x31
#define KBD_KEY_SEMICOLON	0x33
#define KBD_KEY_QUOTE		0x34
#define KBD_KEY_TILDE		0x35
#define KBD_KEY_COMMA		0x36
#define KBD_KEY_PERIOD		0x37
#define KBD_KEY_SLASH		0x38
#define KBD_KEY_CAPSLOCK	0x39
#define KBD_KEY_F1		0x3a
#define KBD_KEY_F2		0x3b
#define KBD_KEY_F3		0x3c
#define KBD_KEY_F4		0x3d
#define KBD_KEY_F5		0x3e
#define KBD_KEY_F6		0x3f
#define KBD_KEY_F7		0x40
#define KBD_KEY_F8		0x41
#define KBD_KEY_F9		0x42
#define KBD_KEY_F10		0x43
#define KBD_KEY_F11		0x44
#define KBD_KEY_F12		0x45
#define KBD_KEY_PRINT		0x46
#define KBD_KEY_SCRLOCK		0x47
#define KBD_KEY_PAUSE		0x48
#define KBD_KEY_INSERT		0x49
#define KBD_KEY_HOME		0x4a
#define KBD_KEY_PGUP		0x4b
#define KBD_KEY_DEL		0x4c
#define KBD_KEY_END		0x4d
#define KBD_KEY_PGDOWN		0x4e
#define KBD_KEY_RIGHT		0x4f
#define KBD_KEY_LEFT		0x50
#define KBD_KEY_DOWN		0x51
#define KBD_KEY_UP		0x52
#define KBD_KEY_PAD_NUMLOCK	0x53
#define KBD_KEY_PAD_DIVIDE	0x54
#define KBD_KEY_PAD_MULTIPLY	0x55
#define KBD_KEY_PAD_MINUS	0x56
#define KBD_KEY_PAD_PLUS	0x57
#define KBD_KEY_PAD_ENTER	0x58
#define KBD_KEY_PAD_1		0x59
#define KBD_KEY_PAD_2		0x5a
#define KBD_KEY_PAD_3		0x5b
#define KBD_KEY_PAD_4		0x5c
#define KBD_KEY_PAD_5		0x5d
#define KBD_KEY_PAD_6		0x5e
#define KBD_KEY_PAD_7		0x5f
#define KBD_KEY_PAD_8		0x60
#define KBD_KEY_PAD_9		0x61
#define KBD_KEY_PAD_0		0x62
#define KBD_KEY_PAD_PERIOD	0x63
#define KBD_KEY_S3		0x65

/* Raw condition structure */
typedef struct {
	uint8 modifiers;	/* bitmask of shift keys/etc */
	uint8 leds;		/* bitmask of leds that are lit */
	uint8 keys[6];		/* codes for up to 6 currently pressed keys */
} kbd_cond_t;

/* This is the structure of the 'state' space. This is what you will
   get back if you call maple_dev_state(). */
typedef struct kbd_state {
	/* The latest raw keyboard condition */
	kbd_cond_t cond;
	
	/* The key matrix array -- this is an array that lists the status of all
	   keys on the keyboard. This is mainly used for key repeat and debouncing. */
	uint8	matrix[256];

	/* Shift key status */
	int	shift_keys;
} kbd_state_t;

/* Turn keyboard queueing on or off. This is mainly useful if you want
   to use the keys for a game where individual keypresses don't mean
   as much as having the keys up or down. Setting this state to
   a new value will clear the queue. */
void kbd_set_queue(int active);

/* Take a key scancode, encode it appropriate, and place it on the
   keyboard queue. At the moment we assume no key overflows. */
/* int kbd_enqueue(uint8 keycode); */

/* Take a key off the key queue, or return -1 if there is none waiting */
int kbd_get_key();

/* Init / Shutdown */
int	kbd_init();
void	kbd_shutdown();

__END_DECLS

#endif	/* __DC_MAPLE_KEYBOARD_H */


