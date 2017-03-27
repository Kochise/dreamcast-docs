/* loader.c - convert + load a module to sound RAM */

/* this is code is really due for a cleanup... */

//#define DEBUG 1

#if defined (DEBUG) || defined (HOST)
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "types.h"
#else
#ifdef VERBOSE
#include <stdio.h>
#endif	/* VERBOSE */
#endif	/* DEBUG || HOST */
#include "types.h"
#include "dxm.h"

#define PCM	0
#define ADPCM	1	/* not yet supported */

static sint32 spu_memcpy(void *, void *, uint32);
static uint16 short2little(uint8 *);
static uint32 word2little(uint8 *);
static sint32 load_xm(uint8 *);
static sint32 load_mod(uint8 *, uint32);
static sint32 load_s3m(uint8 *);

#if defined (DEBUG) || defined (HOST)
	char *outputname;
#else
	static void *memcpy(void *, void *, uint32);
	static sint8 strncmp(sint8 *, sint8 *, uint32);
#endif	/* DEBUG || HOST */

static const char id[] __attribute__ ((section (".text"))) =
	"dxm $Id: loader.c,v 1.1.1.1 2001/09/08 10:48:15 ejstans Exp $";

/* put a check in this one to make sure we're dont overrun available
   sound RAM
*/
static sint32
spu_memcpy(dst, src, size)
	void *dst;
	void *src;
	uint32 size;
{

#if defined (DEBUG) || defined (HOST)
	int fd;
#endif	/* DEBUG || HOST */

	if (dst + size >= (void *)0x00200000) {
#if defined (DEBUG) || defined(HOST) || defined(VERBOSE)
		printf("module is too large - doesnt fit in sound RAM!\n");
#endif	/* DEBUG || HOST || VERBOSE */
		return (-1);
	}

#if defined (DEBUG) || defined (HOST)
	/* do writing to file here */
	fd = open(outputname, O_WRONLY | O_CREAT,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd < 0) {
		printf("couldn't open output file for writing\n");
		return (-1);
	}
	if (lseek(fd, ((int)dst) - XM_HEADER_ADDR, SEEK_SET) != ((int)dst) - XM_HEADER_ADDR) {
		printf("lseek() failed\n");
		return (-1);
	}

	while (size > 0) {
		int n;
		n = write(fd, src, size);
		if (n < 0) {
			printf("write() failed\n");
			return (-1);
		}
		size -= n;
	}

	close (fd);

#else
	/* do writing to soudn RAM here */

#endif	/* DEBUG || HOST */

	return (0);

}

static uint16
short2little(buf)
	uint8 *buf;
{
	sint32 i;
	uint16 ret = 0;

	for (i = 1; i >= 0; i--) {
		ret = ret<<8;
		ret |= buf[i] & 0xff;
	}
	return (ret);

}

static uint32
word2little(buf)
	uint8 *buf;
{
	 sint32 i;
	 uint32 ret = 0;

	 for (i = 3; i >= 0; i--) {
		 ret = ret<<8;
		 ret |= buf[i] & 0xff;
	 }
	 return (ret);
}

/* initializes the module by loading samples to sound RAM aswell as doing
   conversion from big endian to little endian and initializing all internal
   variables.

   if it is not an XM module but a subset (such as MOD or S3M) we convert
   it to the internal (XM) format. possibly look into how different IT is
   ...and maybe MO3 also? =)

   possibly add ADPCM compression when that's been figured out (unless there's
   a patent on yamaha's algorithm?) actually, ADPCM will unfortunately not
   work because of looping :(

   also, recompressing of the patterns to conserve space? (nah, XM compression
   isnt the best, but it is probably good enough)

*/

sint32
dxm_load(module)
	uint8 *module;
{

#if defined (DEBUG) || defined(HOST) || defined(VERBOSE)
	printf("DXM-Loader v0.1 (c) 2001 Lars Olsson\n");
#endif	/* DEBUG + HOST + VERBOSE */

	/* check that this is a format we understand */
	if (strncmp(&module[0], "Extended Module: ", 17) == 0) {
		/* XM */
		return (load_xm(module));
	}
	else if (strncmp(&module[1080], "M.K.", 4) == 0) {
		/* 4 channel mod */
		return (load_mod(module, 4));
	}
	else if (strncmp(&module[1080], "M!K!", 4) == 0) {
		/* pro-tracker */
		return (load_mod(module, 4));
	}
	else if (strncmp(&module[1080], "6CHN", 4) == 0) {
		/* 6 channel mod */
		return (load_mod(module, 6));
	}
	else if (strncmp(&module[1080], "8CHN", 4) == 0) {
		/* 8 channel mod */
		return (load_mod(module, 8));
	}
	else if (strncmp(&module[1082], "CH", 2) == 0) {
		/* multichannel mod */
		return (load_mod(module, (module[1080] - '0') * 10 + (module[1081] - '0')));
	}
	else if (strncmp(&module[44], "SCRM", 4) == 0) {
		/* screamtracker mod */
		return (load_s3m(module));
	}

	/* unknown format */
#if defined (HOST) || defined (VERBOSE)
	printf("dxm: unknown format\n");
#endif	/* HOST || VERBOSE */
	return (-1);

}

/* converts from XM delta values to absolute values + generates inverted loop
   sequence if ping-pong loop is specified (since there is no known way of
   getting the AICA to play the sample backwards as far as i know)
   uploads to soundRAM while comverting

   upload is done on 32bit boundaries (rounded up) so remember to adjust
   sample address in sample header accordingly.

XXX: fix 16-bit sample...segfaulting because of something...

TODO: add support for converting to ADPCM-samples, for now only normal PCM
*/
static int
convert_waveform(dst, src, size, type, loop, start, end, compress)
	void *dst;
	void *src;
	uint32 size;
	uint32 type;
	uint32 loop;
	uint32 start;
	uint32 end;
	uint32 compress;
{

	uint32 i, j, k;

	switch (loop) {
		case 0:
			break;
		case 1:
			size = end;
			break;
		case 2:
			size = end>>1;
			break;
	}

	if (type == 0) {
		/* 8-bit samples */
		sint8 buf[32];
		sint8 old = 0;
		sint8 start_value = 0;
#ifdef DEBUG
		printf("8-bit sample\n");
#endif

		for (i = 0; i < size;) {
			for (j = 0; j < 256/8; j++) {
				if (i < size) {
					old = buf[j] = ((sint8 *)src)[i] + old;
					if (i == start) {
						start_value = old;
					}
					i++;
				} else {
					buf[j] = 0;
				}
			}
			/* upload to sound RAM here */
			spu_memcpy(dst + i, buf, 32);
		}
		/* check if we need to generate pingpong loop */
		if (loop == 2) {
#ifdef DEBUF
			printf("generating ping-pong loop\n");
#endif
			k = i;

			old = start_value;
			for (i = size; i > start;) {
				for (j = 0; j < 256/8; j++) {
					if (i > start) {
						old = buf[j] = ((sint8 *)src)[i] + old;
						i--;
					} else {
						buf[j] = 0;
					}
				}
				/* upload to sound RAM here */
				spu_memcpy(dst + k, buf, 32);
				k += 32;
			}
		}
	} else {
		/* 16-bit samples */
		sint16 buf[16];
		sint16 old = 0;
		sint16 start_value = 0;
#ifdef DEBUG
		printf("16-bit sample\n");
#endif

		for (i = 0; i < size;) {
			for (j = 0; j < 256/16; j++) {
				if (i < size) {
					old = buf[j] = (sint16)short2little((uint8 *)&((sint16 *)src)[i]) + old;
					if (i == start) {
						start_value = old;
					}
					i++;
				} else {
					buf[j] = 0;
				}
			}
			/* upload to sound RAM here */
			spu_memcpy(dst + (i<<1), buf, 32);
		}
		/* check if we need to generate pingpong loop */
		if (loop == 2) {
#ifdef DEBUG
			printf("generating ping-pong loop\n");
#endif
			k = i;

			old = start_value;
			for (i = size; i > start;) {
				for (j = 0; j < 256/16; j++) {
					if (i > start) {
						old = buf[j] = (sint16)short2little((uint8 *)&((sint16 *)src)[i]) + old;
						i--;
					} else {
						buf[j] = 0;
					}
				}
				/* upload to sound RAM here */
				spu_memcpy(dst + k, buf, 32);
				k += 32;
			}
		}
	}
	return (0);

}

static int
load_xm(module)
	uint8 *module;
{

	XM_HEADER xm_header;
	XM_PT_HEADER xm_pt_header;
	XM_XI_HEADER xm_xi_header;
	XM_XI_HEADER2 xm_xi_header2;
	XM_SM_HEADER xm_sm_header;

	uint32 version;

	uint32 mod_offset;
	uint32 tmp_offset;

	uint32 hdr_dst;
	uint32 pat_dst;
	uint32 inst_dst;
	uint32 pat_data_dst;
	uint32 inst2_dst;
	uint32 sample_dst;
	uint32 sample_data_dst;

	uint32 real_instruments, real_samples;

	uint32 i, j;

#if defined (DEBUG) || defined (HOST) || defined (VERBOSE)
	uint8 tmpbuf[256];
	uint32 headersize;
#endif	/* DEBUG || HOST || VERBOSE */

#if defined (DEBUG) || defined (HOST) || defined (VERBOSE)
	printf("XM-format\n");

	memset(tmpbuf, 0, sizeof(tmpbuf));
	memcpy(tmpbuf, &module[17], 20);
	printf("name: %s\n", tmpbuf);

	memset(tmpbuf, 0, sizeof(tmpbuf));
	memcpy(tmpbuf, &module[38], 20);
	printf("tracker: %s\n", tmpbuf);
#endif	/* DEBUG || HOST || VERBOSE */

	version = short2little(&module[58]);

#if defined (DEBUG) || defined (HOST) || defined (VERBOSE)
	printf("version: $%04x\n", version);
#endif	/* DEBUG || HOST || VERBOSE */

	if (version != 0x0104) {
#if defined (DEBUG) || defined (HOST) || defined (VERBOSE)
		printf("unsupported version\n");
#endif	/* DEBUG || HOST || VERBOSE */
		return (-1);
	}

#ifdef DEBUG
	headersize = word2little(&module[60]);
	printf("headersize: %d\n", headersize);
#endif	/* DEBUG */

	mod_offset = 60;
	hdr_dst = XM_HEADER_ADDR;
	pat_dst = hdr_dst + sizeof(XM_HEADER);

	/* setup header info */
	xm_header.song_length = short2little(&module[mod_offset+4]);
	xm_header.restart_pos = short2little(&module[mod_offset+6]);
	xm_header.channels = short2little(&module[mod_offset+8]);
	xm_header.patterns = short2little(&module[mod_offset+10]);
	/* now we know how big the pattern array will be */
	inst_dst = pat_dst + (sizeof(XM_PT_HEADER) * xm_header.patterns);
	xm_header.instruments = short2little(&module[mod_offset+12]);
	xm_header.flags = short2little(&module[mod_offset+14]);
	xm_header.tempo = short2little(&module[mod_offset+16]);
	xm_header.bpm = short2little(&module[mod_offset+18]);
	memcpy(xm_header.pattern_order_table, &module[mod_offset+20], 256);
	xm_header.hdr_pat = (XM_PT_HEADER *)pat_dst;
	xm_header.hdr_inst = (XM_XI_HEADER *)inst_dst;

#ifdef DEBUG
	printf("xm_header.song_length: %d\n", xm_header.song_length);
	printf("xm_header.restart_pos: %d\n", xm_header.restart_pos);
	printf("xm_header.channels: %d\n", xm_header.channels);
	printf("xm_header.patterns: %d\n", xm_header.patterns);
	printf("xm_header.instruments: %d\n", xm_header.instruments);
	printf("xm_header.flags: %d\n", xm_header.flags);
	printf("xm_header.tempo: %d\n", xm_header.tempo);
	printf("xm_header.bpm: %d\n", xm_header.bpm);
	printf("xm_header.patterns: 0x%08x\n", xm_header.hdr_pat);
	printf("xm_header.instruments: 0x%08x\n", xm_header.hdr_inst);
#endif	/* DEBUG */

	/* copy to sound RAM */
	spu_memcpy((void *)hdr_dst, &xm_header, sizeof(XM_HEADER));

	/* do patterns */
	mod_offset += 276;
	pat_data_dst = inst_dst + (sizeof(XM_XI_HEADER) * xm_header.instruments);
	for (i = 0; i < xm_header.patterns; i++) {
		xm_pt_header.rows = short2little(&module[mod_offset+5]);
		xm_pt_header.size = short2little(&module[mod_offset+7]);
		xm_pt_header.data = (uint8 *)pat_data_dst;
#ifdef DEBUG
		printf("xm_pt_header.rows: %d\n", xm_pt_header.rows);
		printf("xm_pt_header.size: %d\n", xm_pt_header.size);
		printf("xm_pt_header.data: 0x%08x\n", xm_pt_header.data);
#endif	/* DEBUG */
		/* copy structure to sound RAM */
		spu_memcpy((void *)pat_dst, &xm_pt_header, sizeof(XM_PT_HEADER));
		/* copy pattern data to sound RAM */
		if (xm_pt_header.size > 0) {
			spu_memcpy((void *)pat_data_dst,
					&module[mod_offset + 9],
					xm_pt_header.size);
		}

		/* get ready for next pattern */
		mod_offset += xm_pt_header.size + 9;
		pat_dst += sizeof(XM_PT_HEADER);
		/* 32-bit align */
		pat_data_dst += ((xm_pt_header.size + 3) & 0xfffffffc);
	}


	/* go through instrument list and check how many instruments
	   there really are (ie instruments that actually have sample(s).
	   we need this because we have to be able to calculate the
	   location of all the sound RAM buffers beforehand in order to
	   correctly fill out the structures...
	*/
	tmp_offset = mod_offset;
	real_instruments = 0;
	real_samples = 0;
	for (i = 0; i < xm_header.instruments; i++) {
		if (short2little(&module[tmp_offset + 27]) > 0) {
			uint32 samples;
			uint32 sample_hdr_length;
			uint32 total_sample_length;

			real_instruments++;
			sample_hdr_length = word2little(&module[tmp_offset + 29]);
			samples = short2little(&module[tmp_offset + 27]);
			real_samples += samples;
#ifdef DEBUG
			printf("instrument: %d\n", real_instruments);
			printf("samples: %d\n", samples);
			printf("sample_hdr_length: %d\n", sample_hdr_length);
#endif	/* DEBUG */
			tmp_offset += word2little(&module[tmp_offset]);
			total_sample_length = 0;
			for (j = 0; j < samples; j++) {
#ifdef DEBUG
				printf("samplelength: %d\n", word2little(&module[tmp_offset]));
				memset(tmpbuf, 0, sizeof(tmpbuf));
				memcpy(tmpbuf, &module[tmp_offset + 18], 22);
				printf("samplename: %s\n", tmpbuf);
#endif	/* DEBUG */
				total_sample_length += word2little(&module[tmp_offset]);
				tmp_offset += sample_hdr_length;
			}
			tmp_offset += total_sample_length;
		} else {
			tmp_offset += word2little(&module[tmp_offset]);
		}
	}

#ifdef DEBUG
	printf("number of real instruments: %d\n", real_instruments);
#endif	/* DEBUG */

	/* now do instruments */
	inst2_dst = pat_data_dst;	/* already added offset */
	sample_dst = inst2_dst + (sizeof(XM_XI_HEADER2) * real_instruments);
	sample_data_dst = sample_dst + (sizeof(XM_SM_HEADER) * real_samples);
	for (i = 0; i < xm_header.instruments; i++) {
		xm_xi_header.samples = short2little(&module[mod_offset + 27]);
#ifdef DEBUG
		printf("current instrument: %d\n", i+1);
		printf("xm_xi_header.samples: %d\n", xm_xi_header.samples);
#endif	/* DEBUG */
		if (xm_xi_header.samples > 0) {
			uint32 sample_hdr_length;
			uint32 tmp_sample_length, tmp_sample_length2;

			/* do extended xi header here - getting complex */
			xm_xi_header.instrument = (XM_XI_HEADER2 *)inst2_dst;
			/* fill out structure */
			memcpy(xm_xi_header2.note_sample_nr,
					&module[mod_offset + 33], 96);
			for (j = 0; j < 12; j++) {
				xm_xi_header2.vol_envelope[j].frame = short2little(&module[mod_offset + 129 + j*4]);
				xm_xi_header2.vol_envelope[j].value = short2little(&module[mod_offset + 131 + j*4]);
				xm_xi_header2.pan_envelope[j].frame = short2little(&module[mod_offset + 177 + j*4]);
				xm_xi_header2.pan_envelope[j].value = short2little(&module[mod_offset + 179 + j*4]);
			}
			xm_xi_header2.vol_points = module[mod_offset + 225];
			xm_xi_header2.pan_points = module[mod_offset + 226];
			xm_xi_header2.vol_sustain_point = module[mod_offset + 227];
			xm_xi_header2.vol_loop_start = module[mod_offset + 228];
			xm_xi_header2.vol_loop_end = module[mod_offset + 229];
			xm_xi_header2.pan_sustain_point = module[mod_offset + 230];
			xm_xi_header2.pan_loop_start = module[mod_offset + 231];
			xm_xi_header2.pan_loop_end = module[mod_offset + 232];
			xm_xi_header2.vol_type = module[mod_offset + 233];
			xm_xi_header2.pan_type = module[mod_offset + 234];
			xm_xi_header2.vibrato_type = module[mod_offset + 235];
			xm_xi_header2.vibrato_sweep = module[mod_offset + 236];
			xm_xi_header2.vibrato_depth = module[mod_offset + 237];
			xm_xi_header2.vibrato_rate = module[mod_offset + 238];
			xm_xi_header2.fadeout_vol = short2little(&module[mod_offset + 239]);
			xm_xi_header2.sample = (XM_SM_HEADER *)sample_dst;

#ifdef DEBUG
			printf("xm_xi_header2.vol_points: %d\n", xm_xi_header2.vol_points);
			printf("xm_xi_header2.pan_points: %d\n", xm_xi_header2.pan_points);
			printf("xm_xi_header2.vol_sustain_point: %d\n", xm_xi_header2.vol_sustain_point);
			printf("xm_xi_header2.vol_loop_start: %d\n", xm_xi_header2.vol_loop_start);
			printf("xm_xi_header2.vol_loop_end: %d\n", xm_xi_header2.vol_loop_end);
			printf("xm_xi_header2.pan_sustain_point: %d\n", xm_xi_header2.pan_sustain_point);
			printf("xm_xi_header2.pan_loop_start: %d\n", xm_xi_header2.pan_loop_start);
			printf("xm_xi_header2.pan_loop_end: %d\n", xm_xi_header2.pan_loop_end);
			printf("xm_xi_header2.vol_type: %d\n", xm_xi_header2.vol_type);
			printf("xm_xi_header2.pan_type: %d\n", xm_xi_header2.pan_type);
			printf("xm_xi_header2.vibrato_type: %d\n", xm_xi_header2.vibrato_type);
			printf("xm_xi_header2.vibrato_sweep: %d\n", xm_xi_header2.vibrato_sweep);
			printf("xm_xi_header2.vibrato_depth: %d\n", xm_xi_header2.vibrato_depth);
			printf("xm_xi_header2.vibrato_rate: %d\n", xm_xi_header2.vibrato_rate);
			printf("xm_xi_header2.fadeout_vol: %d\n", xm_xi_header2.fadeout_vol);
			printf("xm_xi_header2.sample: 0x%08x\n", xm_xi_header2.sample);
#endif

			/* copy structure to sound RAM */
			spu_memcpy((void *)inst2_dst, &xm_xi_header2,
					sizeof(XM_XI_HEADER2));

			/* prepare for next part */
			sample_hdr_length = word2little(&module[mod_offset + 29]);
			mod_offset += word2little(&module[mod_offset]);
			tmp_offset = mod_offset + sample_hdr_length
				* xm_xi_header.samples;
			inst2_dst += sizeof(XM_XI_HEADER2);

			/* do sample headers here */
			/* have to do both header + data in one pass here */
			for (j = 0; j < xm_xi_header.samples; j++) {
				tmp_sample_length = xm_sm_header.sample_length = word2little(&module[mod_offset]);
				xm_sm_header.loop_start = word2little(&module[mod_offset + 4]);
				xm_sm_header.loop_end = word2little(&module[mod_offset + 8]) + xm_sm_header.loop_start;
				xm_sm_header.volume = module[mod_offset + 12];
				xm_sm_header.finetune = module[mod_offset + 13];
				xm_sm_header.type = module[mod_offset + 14];
				/* add bits here depending on which case the sample belongs to; there are enough bits i think */
				xm_sm_header.pan = module[mod_offset + 15];
				xm_sm_header.relative_note = module[mod_offset + 16];
				xm_sm_header.data = (void *)sample_data_dst;

				/* if loop point is earlier than sample
				   end, cut sample since the last part
				   will never be played anyway */
				if ((xm_sm_header.type & 0x03) == 1) {
					xm_sm_header.sample_length = xm_sm_header.loop_end;
				/* if pingpong extend length to include
				   the reversed part of the loop */
				}
				if ((xm_sm_header.type & 0x03) == 2) {
					xm_sm_header.sample_length =
					      xm_sm_header.loop_end<<1;
					/* change loop end to include
					   the reverse-portion of sample
					   aswell */
					xm_sm_header.loop_end <<= 1;
				}

				tmp_sample_length2 = xm_sm_header.sample_length;


				/* change length + loop points to frames
				   instead of bytes which means dividing by 2
				   for 16-bit samples */
				if ((xm_sm_header.type & 0x10) == 0x10) {
					xm_sm_header.sample_length >>= 1;
					xm_sm_header.loop_start >>= 1;
					xm_sm_header.loop_end >>= 1;
				}

				/* clear any spuriously setted bits */
				xm_sm_header.type &= 0x1f;

				/* enter new sample type into the header to make long sample + loop processing easier */
				if ((xm_sm_header.sample_length < 65536) &&
					(xm_sm_header.type & 0x03) != 2) {
					/* small sample; all hardware */
					xm_sm_header.type |= 0<<5;
				}
				/* i guess it would cause problems if the sample is exactly 65536 frames (or just about)...maybe cut it if thats the case? */
				else if ((xm_sm_header.sample_length >= 65536)
					&& ((xm_sm_header.type & 0x03) != 0)
					&& (xm_sm_header.loop_end < 65536)) {
					/* long sample, short loop */
					xm_sm_header.type |= 1<<5;
				}
				else if ((xm_sm_header.sample_length >= 65536)
					&& ((xm_sm_header.type & 0x03) != 0)) {
					/* long sample, long loop */
					xm_sm_header.type |= 2<<5;
				} else {
					/* long sample, no loop */
					xm_sm_header.type |= 3<<5;
				}

				xm_sm_header.loop_end = xm_sm_header.sample_length;

#ifdef DEBUG
				printf("xm_sm_header.sample_length: %d\n", xm_sm_header.sample_length);
				printf("xm_sm_header.loop_start: %d\n", xm_sm_header.loop_start);
				printf("xm_sm_header.loop_end: %d\n", xm_sm_header.loop_end);
				printf("xm_sm_header.volume: %d\n", xm_sm_header.volume);
				printf("xm_sm_header.finetune: %d\n", xm_sm_header.finetune);
				printf("xm_sm_header.type: %d\n", xm_sm_header.type);
				printf("xm_sm_header.pan: %d\n", xm_sm_header.pan);
				printf("xm_sm_header.relative_note: %d\n", xm_sm_header.relative_note);
				printf("xm_sm_header.data: 0x%08x\n", xm_sm_header.data);
#endif	/* DEBUG */
				/* copy header to sound RAM */
				spu_memcpy((void *)sample_dst, &xm_sm_header, sizeof(XM_SM_HEADER));

				/* copy sample data to sound RAM */
				/* need to do delta2absolute conv here
				   possibly insert ADPCM compression later */
				/* i need to check loop type aswell and
				   manually copy+invert loop if pingpong */
				convert_waveform(sample_data_dst,
						&module[tmp_offset],
						xm_sm_header.sample_length,
						(xm_sm_header.type & 0x10)>>4,
						xm_sm_header.type & 0x03,
						xm_sm_header.loop_start,
						xm_sm_header.loop_end,
						PCM);

				/* prepare for next sample header */
				mod_offset += sample_hdr_length;
				tmp_offset += tmp_sample_length;
				sample_dst += sizeof(XM_SM_HEADER);
				/* 32-bit align */
				/* change here since size may be changed */
				sample_data_dst += (tmp_sample_length2 + 3)
					& 0xfffffffc;
			}
			/* skip the sampledata we have already transfered */
			mod_offset = tmp_offset;
		} else {
			xm_xi_header.instrument = NULL;
			mod_offset += word2little(&module[mod_offset]);
		}

		/* copy to sound RAM */
		spu_memcpy((void *)inst_dst, &xm_xi_header,
				sizeof(XM_XI_HEADER));

		/* get ready for next instrument */
		inst_dst += sizeof(XM_XI_HEADER);
	}
	return (0);

}

static sint32
load_mod(module, channel)
	uint8 *module;
	uint32 channel;
{
#if defined (DEBUG) || defined(HOST) || defined(VERBOSE)
	printf("MOD-format\n");
#endif	/* DEBUG + HOST + VERBOSE */
	return (0);
}

static sint32
load_s3m(module)
	uint8 *module;
{
#if defined (DEBUG) || defined(HOST) || defined(VERBOSE)
	printf("S3M-format\n");
#endif	/* DEBUG + HOST + VERBOSE */
	return (0);
}

#if defined (DEBUG) || defined (HOST)

int
main(argc, argv)
	int argc;
	char **argv;
{

	int fd;
	int i, j;
	char *module;

	struct stat st;

	if (argc != 3) {
		printf("usage: %s <input> <output>\n", argv[0]);
		exit (-1);
	}

	outputname = argv[2];

	if (stat(argv[1], &st) < 0) {
		printf("stat() failed\n");
		exit (-1);
	}

	if ((module = (char *)malloc(st.st_size)) == NULL) {
		printf("malloc() failed\n");
		exit (-1);
	}

	if ((fd = open(argv[1], O_RDONLY)) < 0) {
		printf("open() failed\n");
		exit (-1);
	}

	i = 0;
	while (i < st.st_size) {
		j = read(fd, &module[i], st.st_size);
		if (j < 0) {
			printf("read() failed\n");
			exit (-1);
		}
		if (j == 0)
			break;
		i += j;
	}

	unlink(outputname);

	dxm_load(module);

	free(module);

	printf("done\n");

	return (0);

}

#else
#ifndef VERBOSE
/* some libc-type routines thats needed */

/* memcpy.c - copy memory block */

static void *
memcpy(dst, src, n)
	void *dst;
	void *src;
	uint32 n;
{

	uint32 i;
	sint8 *s = (sint8 *)src, *d = (sint8 *)dst;

	for (i = 0; i < n; i++)
		*(d++) = *(s++);

	return (dst);

}

/* strncmp.c - compare two character strings w/ maximum length */

static sint8
strncmp(s1, s2, n)
	sint8 *s1;
	sint8 *s2;
	uint32 n;
{
	sint8 b1, b2;
	uint32 i = 0;

	do {
		i++;
		b1 = *(s1++);
		b2 = *(s2++);
	} while ((b1 == b2) && (b1 != '\0') && (b2 != '\0') && (i < n));

	return (b1 - b2);

}

#endif	/* !VERBOSE */
#endif
