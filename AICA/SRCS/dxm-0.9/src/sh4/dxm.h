/* dxm.h - include file for SH4 programs to control the module aswell as
            allowing access to internal variables used by the module-player
*/

#ifndef _DXM_H_
#define _DXM_H_

#include "types.h"

/* prototypes */
sint32 dxm_disable_arm(void);
sint32 dxm_enable_arm(void);
sint32 dxm_load_driver(void *, uint32);
void *dxm_sramcpy4(void *, void *, uint32);
sint32 dxm_halt_xm(void);
sint32 dxm_init_xm(uint32);
sint32 dxm_init_done(void);
sint32 dxm_play_xm(void);
sint32 dxm_set_stereo(bool);
sint32 dxm_open_os(uint32, uint32, uint32, uint32, uint32, uint32, uint32, uint32, uint32, uint32);
sint32 dxm_play_os(uint32);
sint32 dxm_stop_os(uint32);
sint32 dxm_set_volume_os(uint32, uint32);
sint32 dxm_set_pan_os(uint32, sint32);

sint32 G2Write(uint32 *, uint32);
sint32 G2Read(volatile uint32 *, uint32 *);

#define NO_LOOP	0
#define LOOP	1

#define MODE_16BIT	0
#define MODE_8BIT	1
#define MODE_ADPCM	2
#define MODE_ADPCM_LOOP	3

/* keeps info & controls about the module */
/* this structure is placed in soundRAM so as to be accessible from both
   cpus. elements are either readonly or writeonly from respective cpu so as
   to not cause any race-conditions
*/
typedef struct _XM_INFO {
	/* written by SH4 */
	bool stereo;	/* really...shouldnt be in this struct at all... */
	uint32 play;	/* when != 0 play else no playing */
	uint32 init;	/* when != 0 initialize module (number-1 == order) */
	uint32 done;	/* when != 0 initialization is done */
	sint32 mvol;	/* master volume control */
	/* bookkeeping stuff */
	/* written by ARM */
	uint32 inst;	/* number of instruments */
	uint32 order;	/* current order */
	uint32 pattern;	/* current pattern */
	uint32 row;	/* current row */
	uint32 row_ofs;	/* offset to row in pat */
	uint32 speed;	/* current speed */
	uint32 bpm;	/* current bpm */
	uint32 tick;	/* current tick */
	sint32 gvol;	/* global volume */
	/* channels */
	uint8 cnot[32];	/* current note */
	uint16 cper[32];	/* current period */
	uint8 cins[32];	/* current ch instrument */
	uint8 cvef[32];	/* current ch vol effect */
	uint8 ceff[32];	/* current effect */
	uint8 cefp[32];	/* current effect parameter */
	/* all the different parameters for the effects need to be remmeberde */
	uint8 ce01[32];	/* current portaup param */
	uint8 ce02[32];	/* current portadown param */
	uint8 ce030[32];	/* current toneporta param speed */
	uint16 ce031[32];	/* current toneporta period */
	uint8 ce04[32];	/* current vibrato param */
	uint8 ce07[32];	/* current tremolo param */
	uint8 ce0a[32];	/* current volumeslide param */
	uint8 cee1[32];	/* current fineportaup param */
	uint8 cee2[32];	/* current fineportadown param */
	uint8 cee3[32];	/* current glissando control */
	uint8 cee4[32];	/* current vibrato control */
	uint8 cee7[32];	/* current tremolo control */
	uint8 ceea[32];	/* current finevolumeslideup param */
	uint8 ceeb[32];	/* current finevolumeslidedown param */
	uint8 ceec[32];	/* current cut note param */
	uint8 ceed[32];	/* current delay note param */
	uint8 ce0h[32];	/* current global volume slide param */
	uint8 ce0p[32];	/* current panning slide param */
	uint8 ce0r[32];	/* current multiretrignote param */
	uint8 ce0t[32];	/* current tremor param */
	uint8 cex1[32];	/* current extrafineportaup param */
	uint8 cex2[32];	/* current extrafineportadown param */
	/* effect variables */
	uint8 vib_pos[32];	/* vibrato position */
	uint8 trm_pos[32];	/* tremolo position */
	uint32 pat_dly;		/* how long delay is */
	uint32 pat_loop_row;	/* row number */
	uint32 pat_loop_row_ofs;	/* row offset (no extra calcing) */
	uint32 pat_loop_tmp;	/* temporary storage of row offset */
	uint32 pat_loop_cnt;	/* times left to loop */
	uint8 pbrk;		/* lock to prevent multiple pattern breaks */
	/* envelopes */
	uint16 vol_cnt[32];	/* frame counter for volume */
	uint16 pan_cnt[32];	/* frame counter for panning */
	sint32 fadeout_vol[32];	/* fadeout volume */
	uint8 env_vol[32];	/* envelope volume */
	uint8 env_pan[32];	/* envelope panning */
	uint8 keyoff[32];	/* keyoff status */
	uint16 avib_cnt[32];	/* frame counter for auto-vibrato */
	uint8 avib_pos[32];	/* auto-vibrato position */
	sint16 cvib_per[32];	/* current vibrato delta */
	/* variables */
	uint8 carp[32];	/* current ch arpeggio counter */
	sint8 cvol[32];	/* current ch vol */
	uint8 cpan[32];	/* current ch pan */
	sint8 cfin[32];	/* current finetune value */
} XM_INFO;

/* keeps information about one-shot waveforms */
typedef struct _OS_HEADER {
	uint32 addr;
	uint32 flags;
	uint32 loop;
	uint32 pitch;
	uint32 pan_volume;
	uint32 volume2;
} OS_HEADER;

#define XM_INFO_ADDR	0xa080b000

#endif	/* _DXM_H_ */
