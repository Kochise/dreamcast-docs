/* dxm.h - definitions, structs etc for dxm */

#ifndef _DXM_H_
#define _DXM_H_

#include "types.h"

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

/* since driver is only 1/4th of this, maybe reduce this and fit more data */
#define XM_INFO_ADDR	0x0000b000
#define XM_HEADER_ADDR	0x00010000

typedef struct _XM_SM_HEADER {
	uint32 sample_length;
	uint32 loop_start;
	uint32 loop_end;
	uint8 volume;
	sint8 finetune;
	uint8 type;
	uint8 pan;
	sint8 relative_note;
	uint8 pad[3];
	void *data;		/* ptr to sample */
} XM_SM_HEADER;

typedef struct _XM_XI_HEADER2 {		/* this is aligned (without padding) */
	uint8 note_sample_nr[96];
	struct {
		uint16 frame;
		uint16 value;
	} vol_envelope[12];
	struct {
		uint16 frame;
		uint16 value;
	} pan_envelope[12];
	uint8 vol_points;
	uint8 pan_points;
	uint8 vol_sustain_point;
	uint8 vol_loop_start;
	uint8 vol_loop_end;
	uint8 pan_sustain_point;
	uint8 pan_loop_start;
	uint8 pan_loop_end;
	uint8 vol_type;
	uint8 pan_type;
	uint8 vibrato_type;
	uint8 vibrato_sweep;
	uint8 vibrato_depth;
	uint8 vibrato_rate;
	uint16 fadeout_vol;
	uint16 reserved;
	XM_SM_HEADER *sample;
} XM_XI_HEADER2;

typedef struct _XM_PT_HEADER{		/* this is aligned (without padding) */
	uint16 rows;
	uint16 size;
	uint8 *data;
} XM_PT_HEADER;

typedef struct _XM_XI_HEADER {		/* this is aligned (with padding) */
	uint16 samples;
	uint16 pad;
	XM_XI_HEADER2 *instrument;	/* if no sample this is NULL */
} XM_XI_HEADER;

typedef struct _XM_HEADER {		/* all of this is aligned without padding */
	uint16 song_length;
	uint16 restart_pos;
	uint16 channels;
	uint16 patterns;
	uint16 instruments;
	uint16 flags;
	uint16 tempo;
	uint16 bpm;
	uint8 pattern_order_table[256];
	XM_PT_HEADER *hdr_pat;
	XM_XI_HEADER *hdr_inst;
} XM_HEADER;

#endif	/* _DXM_H_ */
