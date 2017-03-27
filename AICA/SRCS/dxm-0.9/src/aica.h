/* aica.h - definitions and structures for AICA hardware */

#ifndef _AICA_H_
#define _AICA_H_

#include "types.h"

#define KEYON	0xc000
#define KEYOFF	0x8000

/* put voice registers in a struct */
typedef struct {
	volatile uint32 cfg_addr_hi;	/* _0000 */
	volatile uint32 addr_lo;	/* _0004 */
	volatile uint32 loop_start;	/* _0008 */
	volatile uint32 loop_end;	/* _000c */
	volatile uint32 adsr1;		/* _0010 */
	volatile uint32 adsr2;		/* _0014 */
	volatile uint32 pitch;		/* _0018 */
	volatile uint32 lfo1;		/* _001c */
	volatile uint32 lfo2;		/* _0020 */
	volatile uint32 pan_volume;	/* _0024 */
	volatile uint32 volume2;	/* _0028 */
	volatile uint32 unknown[21];	/* _002c - _007c */
} aica_vox_t;

#endif	/* _AICA_H_ */
