/* KallistiOS ##version##

   dc/maple/purupuru.h
   Copyright (C) 2003 Dan Potter
   Copyright (C) 2005 Lawrence Sebald

   $Id: purupuru.h,v 1.1 2003/03/15 00:47:24 bardtx Exp $

*/

#ifndef __DC_MAPLE_PURUPURU_H
#define __DC_MAPLE_PURUPURU_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>

/* These defines are based off of information that Kamjin provided on the 
   DCEmulation forums. They may or may not act the same on all purus.
   For instance, on my official Sega Purupuru, the decay setting seems
   to make many if not all effects do nothing. Don't be surprised if
   your initial effect does nothing for you, its to be expected. Using
   the purupuru seems to be very much a guess-and-test situation. */

/* Effect Generation structure, use with the defines below. */
typedef struct purupuru_effect  {
	uint8 duration;
	uint8 effect2;
	uint8 effect1;
	uint8 special;
} purupuru_effect_t;

/* Set one of each of the following in the effect2 field of the
   purupuru_effect_t. Valid values for each are 0-7. The LINTENSITY
   value works with the INTENSITY of effect1 to increase the intensity
   of the rumble, where UINTENSITY apparently lowers the rumble's
   intensity somewhat. */
#define PURUPURU_EFFECT2_UINTENSITY(x) (x << 4)
#define PURUPURU_EFFECT2_LINTENSITY(x) (x)

/* OR these in with your effect2 value if you feel so inclined.
   if you or the PULSE effect in here, you probably should also
   do so with the effect1 one below. */
#define PURUPURU_EFFECT2_DECAY         (8 << 4)
#define PURUPURU_EFFECT2_PULSE         (8)

/* Set one value for this in the effect1 field of the effect structure. */
#define PURUPURU_EFFECT1_INTENSITY(x)  (x << 4)

/* OR these in with your effect1 value, if you need them. PULSE
   should probably be used with the PULSE in effect2, as well.
   POWERSAVE will probably make your purupuru ignore that command. */
#define PURUPURU_EFFECT1_PULSE         (8 << 4)
#define PURUPURU_EFFECT1_POWERSAVE     (15)

/* Special Effects and motor select. The normal purupuru packs will
   only have one motor. Selecting MOTOR2 for these is probably not
   a good idea. The PULSE setting here supposably creates a sharp
   pulse effect, when ORed with the special field. */
#define PURUPURU_SPECIAL_MOTOR1        (1 << 4)
#define PURUPURU_SPECIAL_MOTOR2        (1 << 7)
#define PURUPURU_SPECIAL_PULSE         (1)

/* Send a specified effect to a specified purupuru */
int purupuru_rumble(maple_device_t *dev, purupuru_effect_t *effect);

/* Send a raw effect to a specified purupuru */
int purupuru_rumble_raw(maple_device_t *dev, uint32 effect);

/* Init / Shutdown */
int purupuru_init();
void purupuru_shutdown();

__END_DECLS

#endif	/* __DC_MAPLE_PURUPURU_H */

