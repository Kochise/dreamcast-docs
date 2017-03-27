/* player.c - the XM player...next to no hw-specifics in this file */

#include "types.h"
#include "dxm.h"

/* define this if debugging */
//#define DEBUG	1

/* comment this out if you want pan envelope. WARNING: player may be too slow */
/* #define NO_PAN_ENVELOPE	1 */

/* extern prototypes */
extern void hw_init(void);
extern void hw_play_waveform(XM_SM_HEADER *, uint32, uint32, uint32);
extern void hw_set_vol_pan_freq(uint8, uint8, uint8, uint8, uint32);
extern uint32 random(void);

/* prototypes */
void init_xm(uint32);
void play_xm(void);

/* private prototypes */
static uint16 convert_note(uint8, uint8, uint8);
static uint32 convert_period(uint16);
static uint8 convert_bpm(uint8);
static void process_volume_fx(uint8, uint8);
static void process_row_fx(uint8, uint8, uint8);
static void update_row(void);
static void update_effects(void);
static void update_envelopes(void);
static void set_final_vol_pan_freq(void);

static const char id[] __attribute__ ((section (".text"))) =
	"dxm $Id: player.c,v 1.1.1.1 2001/09/08 10:48:15 ejstans Exp $";

/* these should of course be in soundRAM */
static XM_INFO *xm_info = (XM_INFO *)XM_INFO_ADDR;
static XM_HEADER *xm_header = (XM_HEADER *)XM_HEADER_ADDR; 

/* this is just needed for AICA hw...really belongs in a different file */
sint32 FIQ_div = 88;		/* divisor for irq counter to get proper
				   tick rate */
				/* this seems a bit inaccurate in some
				   cases :( */

/* used for amiga periods */
static uint16 PeriodTab[] = {
	907,900,894,887,881,875,868,862,856,850,844,838,832,826,820,814,
	808,802,796,791,785,779,774,768,762,757,752,746,741,736,730,725,
	720,715,709,704,699,694,689,684,678,675,670,665,660,655,651,646,
	640,636,632,628,623,619,614,610,604,601,597,592,588,584,580,575,
	570,567,563,559,555,551,547,543,538,535,532,528,524,520,516,513,
	508,505,502,498,494,491,487,484,480,477,474,470,467,463,460,457,
};

/* used to convert linear periods to frequency - probably should think up
   a better way of doing this... */
static uint16 FreqTab[] = {
	493, 493, 494, 494, 495, 495, 496, 496, 496, 497, 497, 498, 498,
	499, 499, 500, 500, 500, 501, 501, 502, 502, 503, 503, 504, 504,
	505, 505, 505, 506, 506, 507, 507, 508, 508, 509, 509, 510, 510,
	511, 511, 511, 512, 512, 513, 513, 514, 514, 515, 515, 516, 516,
	517, 517, 517, 518, 518, 519, 519, 520, 520, 521, 521, 522, 522,
	523, 523, 524, 524, 525, 525, 526, 526, 526, 527, 527, 528, 528,
	529, 529, 530, 530, 531, 531, 532, 532, 533, 533, 534, 534, 535,
	535, 536, 536, 537, 537, 538, 538, 538, 539, 539, 540, 540, 541,
	541, 542, 542, 543, 543, 544, 544, 545, 545, 546, 546, 547, 547,
	548, 548, 549, 549, 550, 550, 551, 551, 552, 552, 553, 553, 554,
	554, 555, 555, 556, 556, 557, 557, 558, 558, 559, 559, 560, 560,
	561, 561, 562, 562, 563, 563, 564, 564, 565, 565, 566, 566, 567,
	567, 568, 568, 569, 569, 570, 571, 571, 572, 572, 573, 573, 574,
	574, 575, 575, 576, 576, 577, 577, 578, 578, 579, 579, 580, 580,
	581, 581, 582, 583, 583, 584, 584, 585, 585, 586, 586, 587, 587,
	588, 588, 589, 589, 590, 590, 591, 592, 592, 593, 593, 594, 594,
	595, 595, 596, 596, 597, 597, 598, 599, 599, 600, 600, 601, 601,
	602, 602, 603, 603, 604, 604, 605, 606, 606, 607, 607, 608, 608,
	609, 609, 610, 611, 611, 612, 612, 613, 613, 614, 614, 615, 615,
	616, 617, 617, 618, 618, 619, 619, 620, 621, 621, 622, 622, 623,
	623, 624, 624, 625, 626, 626, 627, 627, 628, 628, 629, 630, 630,
	631, 631, 632, 632, 633, 634, 634, 635, 635, 636, 636, 637, 638,
	638, 639, 639, 640, 640, 641, 642, 642, 643, 643, 644, 645, 645,
	646, 646, 647, 647, 648, 649, 649, 650, 650, 651, 652, 652, 653,
	653, 654, 654, 655, 656, 656, 657, 657, 658, 659, 659, 660, 660,
	661, 662, 662, 663, 663, 664, 665, 665, 666, 666, 667, 668, 668,
	669, 669, 670, 671, 671, 672, 672, 673, 674, 674, 675, 676, 676,
	677, 677, 678, 679, 679, 680, 680, 681, 682, 682, 683, 683, 684,
	685, 685, 686, 687, 687, 688, 688, 689, 690, 690, 691, 692, 692,
	693, 693, 694, 695, 695, 696, 697, 697, 698, 698, 699, 700, 700,
	701, 702, 702, 703, 704, 704, 705, 705, 706, 707, 707, 708, 709,
	709, 710, 711, 711, 712, 712, 713, 714, 714, 715, 716, 716, 717,
	718, 718, 719, 720, 720, 721, 722, 722, 723, 724, 724, 725, 725,
	726, 727, 727, 728, 729, 729, 730, 731, 731, 732, 733, 733, 734,
	735, 735, 736, 737, 737, 738, 739, 739, 740, 741, 741, 742, 743,
	743, 744, 745, 745, 746, 747, 747, 748, 749, 749, 750, 751, 751,
	752, 753, 754, 754, 755, 756, 756, 757, 758, 758, 759, 760, 760,
	761, 762, 762, 763, 764, 764, 765, 766, 767, 767, 768, 769, 769,
	770, 771, 771, 772, 773, 774, 774, 775, 776, 776, 777, 778, 778,
	779, 780, 781, 781, 782, 783, 783, 784, 785, 785, 786, 787, 788,
	788, 789, 790, 790, 791, 792, 793, 793, 794, 795, 795, 796, 797,
	798, 798, 799, 800, 801, 801, 802, 803, 803, 804, 805, 806, 806,
	807, 808, 809, 809, 810, 811, 811, 812, 813, 814, 814, 815, 816,
	817, 817, 818, 819, 820, 820, 821, 822, 823, 823, 824, 825, 825,
	826, 827, 828, 828, 829, 830, 831, 831, 832, 833, 834, 834, 835,
	836, 837, 837, 838, 839, 840, 841, 841, 842, 843, 844, 844, 845,
	846, 847, 847, 848, 849, 850, 850, 851, 852, 853, 854, 854, 855,
	856, 857, 857, 858, 859, 860, 860, 861, 862, 863, 864, 864, 865,
	866, 867, 868, 868, 869, 870, 871, 871, 872, 873, 874, 875, 875,
	876, 877, 878, 879, 879, 880, 881, 882, 883, 883, 884, 885, 886,
	887, 887, 888, 889, 890, 891, 891, 892, 893, 894, 895, 895, 896,
	897, 898, 899, 899, 900, 901, 902, 903, 903, 904, 905, 906, 907,
	908, 908, 909, 910, 911, 912, 913, 913, 914, 915, 916, 917, 917,
	918, 919, 920, 921, 922, 922, 923, 924, 925, 926, 927, 927, 928,
	929, 930, 931, 932, 933, 933, 934, 935, 936, 937, 938, 938, 939,
	940, 941, 942, 943, 944, 944, 945, 946, 947, 948, 949, 950, 950,
	951, 952, 953, 954, 955, 956, 956, 957, 958, 959, 960, 961, 962,
	962, 963, 964, 965, 966, 967, 968, 969, 969, 970, 971, 972, 973,
	974, 975, 976, 976, 977, 978, 979, 980, 981, 982, 983, 984, 984,
	985, 986, 987, 988, 989, 990, 991, 992, 992, 993, 994, 995, 996,
	997, 998, 999, 1000, 1001, 1001, 1002, 1003, 1004, 1005, 1006, 1007,
	1008, 1009, 1010, 1011, 1011, 1012, 1013, 1014, 1015, 1016, 1017, 1018,
	1019, 1020, 1021, 1022, 1022, 1023, 1024, 1025, 1026, 1027, 1028, 1029,
	1030, 1031, 1032, 1033, 1034, 1035, 1035, 1036, 1037, 1038, 1039, 1040,
	1041, 1042, 1043, 1044, 1045, 1046, 1047, 1048, 1049, 1050, 1051, 1052,
	1052, 1053, 1054, 1055, 1056, 1057, 1058, 1059, 1060, 1061, 1062, 1063,
	1064, 1065, 1066, 1067, 1068, 1069, 1070, 1071, 1072, 1073, 1074, 1075,
	1076, 1076, 1077, 1078, 1079, 1080, 1081, 1082, 1083, 1084, 1085, 1086,
	1087, 1088, 1089, 1090, 1091, 1092, 1093, 1094, 1095, 1096, 1097, 1098,
	1099, 1100, 1101, 1102, 1103, 1104, 1105, 1106, 
};

/* used for vibrato and tremolo */
static uint8 SinTab[] = {
	0, 24, 49, 74, 97, 120, 141, 161,
	180, 197, 212, 224, 235, 244, 250, 253,
	255, 253, 250, 244, 235, 224, 212, 197,
	180, 161, 141, 120, 97, 74, 49, 24,
};

/* called to re-initialize the module */
void
init_xm(order)
	uint32 order;
{

	sint32 i;
	uint8 *ptr = (uint8 *)&(xm_info->mvol);

	/* halt playing */
	xm_info->play = 0;

	/* clear rest of structure */
	for (i = 8; i < sizeof(XM_INFO); i++) {
		*(ptr++) = 0;
	}

	/* fill in some defaults */
	xm_info->mvol = 40;
	xm_info->inst = xm_header->instruments;
	xm_info->order = order;
	xm_info->speed = xm_header->tempo;
	xm_info->tick = xm_header->tempo;
	xm_info->bpm = xm_header->bpm;
	xm_info->gvol = 64;

	FIQ_div = convert_bpm(xm_header->bpm);

}

/* called every tick to play module */
void
play_xm()
{
	/* play waveform (for debugging) */
/*
	hw_play_waveform(&xm_header->hdr_inst[19-1].instrument->sample[0], 0, 0, 22050);

	while (1);
*/

	/* re-init module */
	if (xm_info->init != 0) {
		init_xm(xm_info->init - 1);
		xm_info->init = 0;
	}

	/* check if playing has started yet */
	if (xm_info->play == 0)
		return;
#ifdef DEBUG
	/* use to repeat a patter (for debugging) */
	xm_info->order = 9;
#endif	/* DEBUG */

	if (++xm_info->tick >= xm_info->speed) {
		xm_info->tick = 0;
		if (xm_info->pat_dly == 0) {
			update_row();
			xm_info->pbrk = 0;
			if (++xm_info->row >= xm_header->hdr_pat[xm_info->pattern].rows) {
				/* implement FT2 pattern loop bug */
				xm_info->row = xm_info->pat_loop_row;
				xm_info->row_ofs = xm_info->pat_loop_row_ofs;
				if (++xm_info->order >= xm_header->song_length) {
					xm_info->order = xm_header->restart_pos;
				}
			}
		} else {
			xm_info->pat_dly--;
		}
	} else {

		update_effects();
	}

	/* envelopes are global and processed for every tick */
	update_envelopes();

	/* calculate and set final values */
	set_final_vol_pan_freq();

}


static void
update_row()
{

	uint32 i;
	sint16 anot;
	uint8 cnot, cins, cvef, ceff, cefp;
	uint8 nnot;
	uint8 *ptr, *ptr2;
	uint32 period;
	sint32 pan;
	uint32 vol;
	uint32 sample;
	uint32 sample_offset = 0;

	XM_XI_HEADER2 *my_hdr;

	xm_info->pattern = xm_header->pattern_order_table[xm_info->order];
	ptr = (uint8 *)xm_header->hdr_pat[xm_info->pattern].data;
	ptr += xm_info->row_ofs;

	/* store first point in row of row offset for pattern loop effect */
	xm_info->pat_loop_tmp = xm_info->row_ofs;

	for (i = 0; i < xm_header->channels; i++) {
		/* best is probably to keep an offset for the row and
		   add to this for every row processed. since rows most
		   of the time grow incrementally 1 row at the time this
		   gives the least overhead. whenever we have a loop command
		   or pattern break we need extra processing though */
		cnot = cins = cvef = ceff = cefp = 0;
		nnot = 0;
		period = 0;
		pan = 0;
		vol = 0;
		sample_offset = 0;

		/* get compressed note information */
		if (ptr[0] & 0x80) {
			ptr2 = ptr + 1;
			if (ptr[0] & 0x01) {
				cnot = *(ptr2++);
			}
			if (ptr[0] & 0x02) {
				cins = *(ptr2++);
			}
			if (ptr[0] & 0x04) {
				cvef = *(ptr2++);
			}
			if (ptr[0] & 0x08) {
				ceff = *(ptr2++);
			}
			if (ptr[0] & 0x10) {
				cefp = *(ptr2++);
			}
			xm_info->row_ofs += ptr2 - ptr;
			ptr += ptr2 - ptr;
		} else {
			cnot = ptr[0];
			cins = ptr[1];
			cvef = ptr[2];
			ceff = ptr[3];
			cefp = ptr[4];
			xm_info->row_ofs += 5;
			ptr += 5;
		}

		/* reset vibrato delta */
		xm_info->cvib_per[i] = 0;

		/* check for new note */
		if (cnot > 0 && cnot < 97) {
			/* KeyOn event */
			nnot = 1;
			xm_info->cnot[i] = cnot--;
		}
		else if (cnot == 97) {
			/* KeyOff event */
			nnot = 2;
			xm_info->keyoff[i] = 1;
		} else {
			nnot = 0;
			cnot = xm_info->cnot[i] - 1;
		}

		/* check for new instrument */
		if (cins > 0) {
			xm_info->cins[i] = --cins;	/* set new instrument */
			my_hdr = (xm_header->hdr_inst[cins].instrument);
			sample = my_hdr->note_sample_nr[cnot];
			/* only reset if not tone porta effect */
			if (ceff != 0x03 && ceff != 0x05) {
				/* reset volume + pan */
				xm_info->cvol[i] = my_hdr->sample[sample].volume;
				xm_info->cpan[i] = my_hdr->sample[sample].pan;

				/* reset envelopes */
				xm_info->fadeout_vol[i] = 65536;	/* set default fadeout vol */
				xm_info->vol_cnt[i] = 0;	/* reset vol env */
				xm_info->pan_cnt[i] = 0;	/* reset pan env */
				xm_info->keyoff[i] = 0;		/* remove keyoff */
				xm_info->avib_pos[i] = 0;	/* reset vibrato pos */
			}
		} else {
			cins = xm_info->cins[i];	/* get old instrument */
			my_hdr = (xm_header->hdr_inst[cins].instrument);
			sample = my_hdr->note_sample_nr[cnot];
		}

		/* check if there was a new note */
		if (nnot == 1) {
			/* only reset if not tone porta effect */
			if (ceff != 0x03 && ceff != 0x05) {
				/* reset envelopes */
				xm_info->fadeout_vol[i] = 65536;	/* set default fadeout vol */
				xm_info->vol_cnt[i] = 0;	/* reset vol env */
				xm_info->pan_cnt[i] = 0;	/* reset pan env */
				xm_info->keyoff[i] = 0;		/* remove keyoff */
				xm_info->avib_pos[i] = 0;	/* reset vibrato pos */
			}

			/* get absolute note */
			anot = cnot + my_hdr->sample[sample].relative_note;
			/* clamp the values */
			if (anot < 1)
				anot = 1;
			if (anot > 119)
				anot = 119;

			/* convert from note to period */
			period = convert_note(anot, cins, sample);

			/* check for portamento to note effect */
			if (ceff == 0x03 || ceff == 0x05) {
				/* grab destination period */
				xm_info->ce031[i] = period;
				/* zero out speed (so we dont use old value) */
				xm_info->ce030[i] = 0;
			} else {
				/* otherwise set new period */
				xm_info->cper[i] = period;
			}
		}

		/* move effects before period calculation so we can use fine
		   tune from effect in this calculation (used for setfinetune
		   and glissando slide (maybe), vibrato, autovibrato */

		/* save volume column effect */
		xm_info->cvef[i] = cvef;
		/* save normal effect */
		xm_info->ceff[i] = ceff;

		/* check if there are any volume column effects first */
		if (cvef != 0) {
			/* do volume effects processing here */
			process_volume_fx(i, cvef);
		}

		/* check if there are any normal effects to process */
		if (ceff != 0 || cefp != 0) {
			/* only save parameter if there actually is one */
			if (cefp != 0) {
				xm_info->cefp[i] = cefp;
			}
			/* do row-based effects here */
			process_row_fx(i, ceff, cefp);

			/* process sample offset effect here instead */
			/* XXX: this is tricky - we cant just add the offset
			   to the waveform address if looping is on and loop
			   start happens to be before the offset :/ */
			if (ceff == 0x09) {
				sample_offset = cefp<<8;
			}
		}

		/* effect processing done! */

		/* check if we're supposed to play a new instrument here
		   and if so do the necessary processing */
		if (period > 0 || sample_offset > 0) {
			/* check for tone portamento or note delay */
			if (ceff != 0x03 && ceff != 0x05 && !(ceff == 0x0e && cefp == 0xd0)) {
				/* start playing the note */
				hw_play_waveform(&(my_hdr->sample[sample]),
						i, sample_offset,
						convert_period(period));
			}
		}
	}

}

static void
process_volume_fx(ch, eff)
	uint8 ch;
	uint8 eff;
{

	switch (eff & 0xf0) {
		case 0x10:
		case 0x20:
		case 0x30:
		case 0x40:
		case 0x50:
			/* set volume */
			xm_info->cvol[ch] = eff - 0x10;
			break;

		case 0x80:
			/* fine volume slide down */
			xm_info->cvol[ch] -= eff & 0x0f;
			break;

		case 0x90:
			/* fine volume slide up */
			xm_info->cvol[ch] += eff & 0x0f;
			break;

		case 0xa0:
			/* set vibrato speed */
			xm_info->ce04[ch] = ((xm_info->ce04[ch] & 0x0f) | (eff & 0x0f)<<4);
			break;

		case 0xb0:
			/* vibrato - set depth */
			xm_info->ce04[ch] = ((xm_info->ce04[ch] & 0xf0) | (eff & 0x0f));
			break;

		case 0xc0:
			/* set panning */
			xm_info->cpan[ch] = (eff & 0x0f)<<8;
			break;

		case 0xf0:
			/* portamento to note */
			if ((eff & 0x0f) != 0) {
				xm_info->ce030[ch] = eff & 0x0f;
			}
			break;

		default:
			break;
	}

}

static void
process_row_fx(ch, eff, param)
	uint8 ch;
	uint8 eff;
	uint8 param;
{

	switch (eff) {
		case 0x00:
			/* arpeggio - reset arpeggio counter */
			xm_info->carp[ch] = 0;
			break;

		case 0x01:
			/* portamento up - save parameter */
			if (param != 0) {
				xm_info->ce01[ch] = param;
			}
			break;

		case 0x02:
			/* portamento down - save parameter */
			if (param != 0) {
				xm_info->ce02[ch] = param;
			}
			break;

		case 0x03:
			/* portamento to note - save parameter (period already
			   saved in main routine) */
			if (param != 0) {
				xm_info->ce030[ch] = param;
			}
			break;

		case 0x04:
			/* vibrato - save parameters */
			if (param != 0) {
				xm_info->ce04[ch] = param;
			}
			break;

		case 0x05:
			/* portamento to note + volume slide - save parameter */
			if (param != 0) {
				xm_info->ce0a[ch] = param;
			}
			break;

		case 0x06:
			/* vibrato + volume slide - save parameter */
			if (param != 0) {
				xm_info->ce0a[ch] = param;
			}
			break;

		case 0x07:
			/* tremolo - save parameter */
			if (param != 0) {
				xm_info->ce07[ch] = param;
			}
			break;

		case 0x08:
			/* set panning */
			xm_info->cpan[ch] = param;
			break;

		case 0x0a:
			/* volume slide - save parameter here */
			if (param != 0) {
				xm_info->ce0a[ch] = param;
			}
			break;

		case 0x0b:
			/* position jump */
			xm_info->order = param;
			xm_info->row = 0;
			xm_info->row_ofs = 0;
			xm_info->pat_loop_row = 0;
			xm_info->pat_loop_row_ofs = 0;
			break;

		case 0x0c:
			/* set volume */
			xm_info->cvol[ch] = param;
			break;

		case 0x0d:
			/* pattern break */
			/* this is a drawback to XM-packed patterns since
			   a lot of extra processing is needed to find the
			   proper row offset */
			if (xm_info->pbrk == 0) {
				uint8 *ptr, *ptr2;
				uint32 i, j;

				/* reset pattern loop position */
				xm_info->pat_loop_row = 0;
				xm_info->pat_loop_row_ofs = 0;

				/* prevent multiple pattern breaks on the same
				   row from triggering more than once */
				xm_info->pbrk = 1;

				xm_info->order++;
				xm_info->row = ((param>>4) & 0x0f) * 10 + (param & 0x0f);
				xm_info->row_ofs = 0;

				xm_info->pattern = xm_header->pattern_order_table[xm_info->order];
				ptr = (uint8 *)xm_header->hdr_pat[xm_info->pattern].data;
				/* calculate correct row_ofs here */
				for (i = 0; i < xm_info->row; i++) {
					ptr += xm_info->row_ofs;
					for (j = 0; j < xm_header->channels; j++) {
						if (ptr[0] & 0x80) {
							ptr2 = ptr + 1;
							if (ptr[0] & 0x01) {
								ptr2++;
							}
							if (ptr[0] & 0x02) {
								ptr2++;
							}
							if (ptr[0] & 0x04) {
								ptr2++;
							}
							if (ptr[0] & 0x08) {
								ptr2++;
							}
							if (ptr[0] & 0x10) {
								ptr2++;
							}
							xm_info->row_ofs += ptr2 - ptr;
							ptr += ptr2 - ptr;
						} else {
							xm_info->row_ofs += 5;
							ptr += 5;
						}
					}
					xm_info->row++;
				}
			}
			break;

		case 0x0e:
			/* extended */
			switch (param & 0xf0) {
				case 0x10:
					/* fine portamento up */
					if (param & 0x0f) {
						xm_info->cper[ch] -= (param & 0x0f)<<2;
						xm_info->cee1[ch] = param & 0x0f;
					} else {
						xm_info->cper[ch] -= xm_info->cee1[ch]<<2;
					}
					break;

				case 0x20:
					/* fine portamento down */
					if (param & 0x0f) {
						xm_info->cper[ch] += (param & 0x0f)<<2;
						xm_info->cee2[ch] = param & 0x0f;
					} else {
						xm_info->cper[ch] += xm_info->cee2[ch]<<2;
					}
					break;

				case 0x30:
					/* set glissando control */
					xm_info->cee3[ch] = param & 0x0f;
					break;

				case 0x40:
					/* set vibrato control */
					if ((param & 0x0f) == 0x03) {
						xm_info->cee4[ch] = random() & 0x03;
					}
					else if ((param & 0x0f) == 0x07) {
						xm_info->cee4[ch] = (random() & 0x03)<<4;
					}
					else {
						xm_info->cee4[ch] = param & 0x0f;
					}
					break;

				case 0x50:
					/* set finetune */
					/* XXX: must change so this is
					   considered in main routine when
					   converting. now it is just skipped
					   over :( */
					xm_info->cfin[ch] = (param & 0x0f)<<8;
					break;

				case 0x60:
					/* pattern loop */
					if ((param & 0x0f) == 0) {
						/* set loop point */
						xm_info->pat_loop_row = xm_info->row;
						xm_info->pat_loop_row_ofs = xm_info->pat_loop_tmp;
						xm_info->pat_loop_cnt = 0;
					} else {
						if (xm_info->pat_loop_cnt != (param & 0x0f)) {
							xm_info->pat_loop_cnt++;
							xm_info->row = xm_info->pat_loop_row;
							xm_info->row_ofs = xm_info->pat_loop_row_ofs;
						}
					}
					break;

				case 0x70:
					/* set tremolo control */
					if ((param & 0x0f) == 0x03) {
						xm_info->cee7[ch] = random() & 0x03;
					}
					else if ((param & 0x0f) == 0x07) {
						xm_info->cee7[ch] = (random() & 0x03)<<4;
					}
					else {
						xm_info->cee7[ch] = param & 0x0f;
					}
					break;

				case 0xa0:
					/* fine volume slide up */
					if (param & 0x0f) {
						xm_info->cvol[ch] += param & 0x0f;
						xm_info->ceea[ch] = param & 0x0f;
					} else {
						xm_info->cvol[ch] += xm_info->ceea[ch];
					}
					break;

				case 0xb0:
					/* fine volume slide down */
					if (param & 0x0f) {
						xm_info->cvol[ch] -= param & 0x0f;
						xm_info->ceeb[ch] = param & 0x0f;
					} else {
						xm_info->cvol[ch] -= xm_info->ceeb[ch];
					}
					break;

				case 0xc0:
					/* cut note */
					xm_info->ceec[ch] = param;
					break;

				case 0xd0:
					/* delay note */
					xm_info->ceed[ch] = param;
					break;

				case 0xe0:
					/* pattern delay */
					xm_info->pat_dly = param;
					break;

				default:
					/* not processed */
					break;

			}
			break;

		case 0x0f:
			if (param < 32) {
				/* set tempo */
				xm_info->speed = param;
			} else {
				/* set BPM */
				xm_info->bpm = param;
				FIQ_div = convert_bpm(param);
			}
			break;

		case 0x10:
			/* set global volume */
			xm_info->gvol = param;
			break;

		case 0x11:
			/* global volume slide - save parameter */
			if (param) {
				xm_info->ce0h[ch] = param;
			}
			break;

		case 0x14:
			/* key off */
			xm_info->keyoff[ch] = 1;
			break;

		case 0x15:
			/* set envelope position */
			xm_info->vol_cnt[ch] = param;
			xm_info->pan_cnt[ch] = param;
			break;

		case 0x18:
			/* panning slide - save parameter */
			if (param) {
				xm_info->ce0p[ch] = param;
			}
			break;

		case 0x1a:
			/* multi retrig note */
			if (param) {
				xm_info->ce0r[ch] = param;
			}
			break;

		case 0x1c:
			/* tremor */
			if (param) {
				xm_info->ce0t[ch] = param;
			}
			break;

		case 0x1f:
			/* extended2 */
			switch (param & 0xf0) {
				case 0x10:
					/* extra fine portamento up */
					if (param & 0x0f) {
						xm_info->cper[ch] -= (param & 0x0f);
						xm_info->cex1[ch] = param & 0x0f;
					} else {
						xm_info->cper[ch] -= xm_info->cex1[ch];
					}
					break;

				case 0x20:
					/* extra fine portamento down */
					if (param & 0x0f) {
						xm_info->cper[ch] += (param & 0x0f);
						xm_info->cex2[ch] = param & 0x0f;
					} else {
						xm_info->cper[ch] += xm_info->cex2[ch];
					}
					break;

				default:
					/* not processed here */
					break;
			}
			break;

		default:
			/* not processed here */
			break;
	}

}

/* convert period to frequency */
static uint32
convert_period(period)
	uint16 period;
{

	uint32 freq;
	uint32 per = 7744 - period;

	if (xm_header->flags & 0x01) {
		/* linear period table */
		freq = (1<<(per / 768)) * FreqTab[per % 768];
	} else {
		/* amiga period table */
		freq = (8363 * 1712)/period;
	}

	return (freq);

}

/* convert note to period */
static uint16
convert_note(not, cins, sample)
	uint8 not;
	uint8 cins;
	uint8 sample;
{

	uint16 period;

	if ((xm_header->flags & 0x01) == 0) {
		/* amiga period */
		/* XXX: this is completely bugged!!!! dont know what i was
		        thinking... */
		sint32 finetune = xm_header->hdr_inst[cins].instrument->sample[sample].finetune;
		uint32 fracfine = finetune<<6;
		uint32 divfine = finetune/16;
		uint32 modnot = (not % 12)<<3;

		period = ((PeriodTab[modnot + divfine]
			* (1024 - fracfine)
			+ (PeriodTab[modnot + divfine]
			* fracfine))
			* (16 / (1<<(not / 12))))
			/ 1024;
	} else {
		/* linear period */
		sint32 finetune = xm_header->hdr_inst[cins].instrument->sample[sample].finetune;
		period = 7680 - (not<<6) - (finetune / 2);
	}

	return (period);
}

/* convert bpm to counter divisor value - really belongs in diff. file */
static uint8
convert_bpm(bpm)
	uint8 bpm;
{
	return (4410/((2 * bpm)/5));
}

/* process tick-based effects here */
static void
update_effects()
{

	uint32 i;
	uint8 cvef;

	for (i = 0; i < xm_header->channels; i++) {
		cvef = xm_info->cvef[i];
		/* do volume column effects first */
		switch (cvef & 0xf0) {
			case 0x60:
				/* volume slide down */
				xm_info->cvol[i] -= cvef & 0x0f;
				break;

			case 0x70:
				/* volume slide up */
				xm_info->cvol[i] += cvef & 0x0f;
				break;

			case 0xb0:
				/* vibrato */
				goto dovibrato;
				break;

			case 0xd0:
				/* panning slide left */
				xm_info->cpan[i] -= cvef & 0x0f;
				break;

				/* 17847259 */
			case 0xe0:
				/* panning slide right */
				xm_info->cpan[i] += cvef & 0x0f;
				break;

			case 0xf0:
				/* portamento to note */
				goto doportatonote;
				break;

			default:
				/* effect not processed here */
				break;
		}

		/* then process normal effects */
		switch (xm_info->ceff[i]) {
			case 0x00:
				/* arpeggio */
				if (++xm_info->carp[i] > 2) {
					xm_info->carp[i] = 0;
				}
				switch (xm_info->carp[i]) {
					case 0:
						/* XXX: left to implement */
						break;
					case 1:
						/* XXX: left to implement */
						break;
					default:
						/* XXX: left to implement */
						break;
				}
				break;

			case 0x01:
				/* portamento up */
				if (xm_info->cefp[i] != 0) {
					xm_info->cper[i] -= xm_info->cefp[i]<<2;
				} else {
					xm_info->cper[i] -= xm_info->ce01[i]<<2;
				}
				break;

			case 0x02:
				/* portamento down */
				if (xm_info->cefp[i] != 0) {
					xm_info->cper[i] += xm_info->cefp[i]<<2;
				} else {
					xm_info->cper[i] += xm_info->ce02[i]<<2;
				}
				break;

			case 0x03:
				/* portamento to note */
doportatonote:
				{
					uint16 slide;

					/* check if glissando is active */
					if (xm_info->cee3[i] == 0) {

						slide = xm_info->ce030[i]<<2;
					} else {
						/* XXX: do glissando slide later
						*/
						slide = xm_info->ce030[i];
					}

					if (xm_info->cper[i] > xm_info->ce031[i]) {
						xm_info->cper[i] -= slide;
						if (xm_info->cper[i] < xm_info->ce031[i]) {
							xm_info->cper[i] = xm_info->ce031[i];
						}
					}
					else if (xm_info->cper[i] < xm_info->ce031[i]) {
						xm_info->cper[i] += slide;
						if (xm_info->cper[i] > xm_info->ce031[i]) {
							xm_info->cper[i] = xm_info->ce031[i];
						}
					}
				}
				break;

			case 0x04:
				/* vibrato */
dovibrato:
				/* i suspect vibrato should rather use rate *
				   16th of semitone instead of just directly
				   modifying the period like this since when
				   using amiga-periods, depth will depend on
				   frequency :/ */
				{
					uint8 rate = (xm_info->vib_pos[i] & 0x3f);
					uint8 depth = (xm_info->ce04[i] & 0x0f);

					xm_info->vib_pos[i] = rate + ((xm_info->ce04[i]>>4) & 0x0f);
					switch (xm_info->cee4[i]) {
						case 0:
						case 4:
							/* sine */
							if (rate < 32) {
								xm_info->cvib_per[i] = xm_info->cvib_per[i] + ((SinTab[rate] * depth)>>7);
							} else {
								xm_info->cvib_per[i] = xm_info->cvib_per[i] - ((SinTab[rate & 0x1f] * depth)>>7);
							}
							break;
						case 1:
						case 5:
							/* ramp down */
							xm_info->cvib_per[i] = xm_info->cvib_per[i] + (((depth<<8) - ((depth * rate)<<3))>>7);
	
							break;
						case 2:
						case 6:
							/* square */
							if (rate < 32) {
								xm_info->cvib_per[i] = (xm_info->cvib_per[i] + (depth)*2);
							} else {
								xm_info->cvib_per[i] = (xm_info->cvib_per[i] - (depth)*2);
							}
							break;

						default:
							break;
					}
				}
				break;

			case 0x05:	/* portamento to note + volume slide */
			case 0x06:	/* vibrato + volume slide */
			case 0x0a:	/* volume slide */
				{
					uint8 cefp;

					if (xm_info->cefp[i] == 0) {
						cefp = xm_info->ce0a[i];
					} else {
						cefp = xm_info->cefp[i];
					}
					if (cefp & 0xf0) {
						xm_info->cvol[i] += cefp & 0xf0;
					}
					else if (cefp & 0x0f) {
						xm_info->cvol[i] -= cefp & 0x0f;
					}
				}
				switch (xm_info->ceff[i]) {
					case 0x05:
						goto doportatonote;
						break;
					case 0x06:
						goto dovibrato;
						break;
					case 0x0a:
						break;
				}
				break;

			case 0x07:
				/* tremolo */
				{
					uint8 rate = (xm_info->trm_pos[i] & 0x3f);
					uint8 depth = (xm_info->ce07[i] & 0x0f);

					xm_info->trm_pos[i] = rate + ((xm_info->ce07[i]>>4) & 0x0f);

					switch (xm_info->cee7[i]) {
						case 0:
						case 4:
							/* sine */
							if (rate < 32) {
								xm_info->cvol[i] = xm_info->cvol[i] + ((SinTab[rate] * depth)>>6);
							} else {
								xm_info->cvol[i] = xm_info->cvol[i] - ((SinTab[rate & 0x1f] * depth)>>6);
							}
							break;
						case 1:
						case 5:
							/* ramp down */
							xm_info->cvol[i] = xm_info->cvol[i] + (((depth<<8) - ((depth * rate)<<3))>>6);
	
							break;
						case 2:
						case 6:
							/* square */
							if (rate < 32) {
								xm_info->cvol[i] = (xm_info->cvol[i] + (depth*2));
							} else {
								xm_info->cvol[i] = (xm_info->cvol[i] - (depth*2));
							}
							break;
						default:
							break;
					}
				}
				break;

			case 0x0e:
				/* extended effect */
				switch (xm_info->cefp[i] & 0xf0) {
					case 0x90:
						/* retrig note */
						if ((xm_info->tick % (xm_info->cefp[i] & 0x0f)) == 0) {
							/* nice long line... */
							hw_play_waveform(&xm_header->hdr_inst[xm_info->cins[i]].instrument->sample[xm_header->hdr_inst[xm_info->cins[i]].instrument->note_sample_nr[xm_info->cnot[i]]], i, 0, convert_period(xm_info->cper[i]));
						}
						break;

					case 0xc0:
						/* cut note */
						if (xm_info->tick == xm_info->ceec[i]) {
							xm_info->cvol[i] = 0;
						}
						break;

					case 0xd0:
						/* delay note */
						if (xm_info->tick == xm_info->ceed[i]) {
							hw_play_waveform(&xm_header->hdr_inst[xm_info->cins[i]].instrument->sample[xm_header->hdr_inst[xm_info->cins[i]].instrument->note_sample_nr[xm_info->cnot[i]]], i, 0, convert_period(xm_info->cper[i]));
						}
						break;

					default:
						/* effect not processed here */
						break;
				}
				break;

			case 0x11:
				/* global volume slide */
				{
					uint8 cefp;

					if (xm_info->cefp[i] == 0) {
						cefp = xm_info->ce0h[i];
					} else {
						cefp = xm_info->cefp[i];
					}
					if (cefp & 0xf0) {
						xm_info->gvol += cefp & 0xf0;
					}
					else if (cefp & 0x0f) {
						xm_info->gvol -= cefp & 0x0f;
					}
				}
				break;

			case 0x18:
				/* panning slide */
				{
					uint8 cefp;

					if (xm_info->cefp[i] == 0) {
						cefp = xm_info->ce0p[i];
					} else {
						cefp = xm_info->cefp[i];
					}
					if (cefp & 0xf0) {
						xm_info->cpan[i] += cefp & 0xf0;
					}
					else if (cefp & 0x0f) {
						xm_info->cpan[i] -= cefp & 0x0f;
					}
				}
				break;

			case 0x1a:
				/* multi-retrig-note */
				if ((xm_info->tick % (xm_info->cefp[i] & 0x0f)) == 0) {
					switch (xm_info->cefp[i] & 0x0f) {
						case 0x00:
							break;
						case 0x01:
							xm_info->cvol[i] -= 1;
							break;
						case 0x02:
							xm_info->cvol[i] -= 2;
							break;
						case 0x03:
							xm_info->cvol[i] -= 4;
							break;
						case 0x04:
							xm_info->cvol[i] -= 8;
							break;
						case 0x05:
							xm_info->cvol[i] -= 16;
							break;
						case 0x06:
							xm_info->cvol[i] = (xm_info->cvol[i] * 2)/3;
							break;
						case 0x07:
							xm_info->cvol[i] >>= 1;
							break;
						case 0x08:
							break;
						case 0x09:
							xm_info->cvol[i] += 1;
							break;
						case 0x0a:
							xm_info->cvol[i] += 2;
							break;
						case 0x0b:
							xm_info->cvol[i] += 4;
							break;
						case 0x0c:
							xm_info->cvol[i] += 8;
							break;
						case 0x0d:
							xm_info->cvol[i] += 16;
							break;
						case 0x0e:
							xm_info->cvol[i] = (xm_info->cvol[i] * 3)>>1;
							break;
						case 0x0f:
							xm_info->cvol[i] <<= 1;
							break;
					}
					hw_play_waveform(&xm_header->hdr_inst[xm_info->cins[i]].instrument->sample[xm_header->hdr_inst[xm_info->cins[i]].instrument->note_sample_nr[xm_info->cnot[i]]], i, 0, convert_period(xm_info->cper[i]));
				}
				break;

			case 0x1c:
				/* tremor - need to find out exactly how this
				            works...should it trigger just
				            once or cycle through the on-time/
				            off-time repeatedly? */
				break;

			default:
				/* effect not processed here */
				break;
		}
	}

}

static void
update_envelopes()
{
	uint32 i, j;
	XM_XI_HEADER2 *my_hdr;
	sint32 x1, x2;
	uint8 y1, y2;
	uint8 type;
	uint8 depth;
	uint8 rate;

	/* loop through all the channels */
	for (i = 0; i < xm_header->channels; i++) {
		/* get the instrument on the channel */
		my_hdr = (xm_header->hdr_inst[xm_info->cins[i]].instrument);
		/* check if instrument is playing */
		if (xm_info->cnot[i] > 0) {
			type = my_hdr->vol_type;
			/* volume envelope enabled? */
			if (type & 0x01) {
				/* check if we've reached last env. point */
				if (xm_info->vol_cnt[i] < my_hdr->vol_envelope[my_hdr->vol_points-1].frame) {
					/* no, check if sustain is enabled */
					if (type & 0x02) {
						if ((xm_info->keyoff[i] != 0)
							|| (xm_info->vol_cnt[i] < my_hdr->vol_envelope[my_hdr->vol_sustain_point].frame) ) {
							xm_info->vol_cnt[i]++;
						}
					} else {
						xm_info->vol_cnt[i]++;
					}
				}
				/* envelope looping */
				if (type & 0x04) {
					if (xm_info->vol_cnt[i] >= my_hdr->vol_envelope[my_hdr->vol_loop_end].frame) {
						xm_info->vol_cnt[i] = my_hdr->vol_envelope[my_hdr->vol_loop_start].frame;
					}
				}

				/* volume envelope processing */
				if (my_hdr->vol_points == 1) {
					xm_info->env_vol[i] = my_hdr->vol_envelope[0].value;
				} else {
					for (j = 1; j < my_hdr->vol_points; j++) {
						if ((xm_info->vol_cnt[i] < my_hdr->vol_envelope[j].frame) && (xm_info->vol_cnt[i] >= my_hdr->vol_envelope[j-1].frame)) {
							break;
						}
					}
					x1 = my_hdr->vol_envelope[j-1].frame;
					y1 = my_hdr->vol_envelope[j-1].value;
					x2 = my_hdr->vol_envelope[j].frame;
					y2 = my_hdr->vol_envelope[j].value;

					/* set final volume */
					xm_info->env_vol[i] = (((y2 - y1) * (xm_info->vol_cnt[i] - x1)) / (x2 - x1)) + y1;
				}

			} else {
				xm_info->env_vol[i] = 64;
			}

			/* fadeout volume */
			if (xm_info->keyoff[i] != 0) {
				if (xm_info->fadeout_vol[i] < my_hdr->fadeout_vol) {
					xm_info->fadeout_vol[i] = 0;
				} else {
					xm_info->fadeout_vol[i] -= my_hdr->fadeout_vol;
				}
			}


/*
   Bah...ARM is too slow to handle 32 voices + full envelope processing so
   pan_env can been removed...we shall see if i can improve code enough later...
*/

#ifndef NO_PAN_ENVELOPE

			/* pan envelope enabled? */
			type = my_hdr->pan_type;
			if (type & 0x01) {
				/* check if we've reached last env. point */
				if (xm_info->pan_cnt[i] < my_hdr->pan_envelope[my_hdr->pan_points-1].frame) {
					/* no, check if sustain is enabled */
					if (type & 0x02) {
						if ((xm_info->keyoff[i] != 0)
							|| (xm_info->pan_cnt[i] < my_hdr->pan_envelope[my_hdr->pan_sustain_point ].frame) ) {
							xm_info->pan_cnt[i]++;
						}
					} else {
						xm_info->pan_cnt[i]++;
					}
				}
				/* envelope looping */
				if (type & 0x04) {
					if (xm_info->pan_cnt[i] > my_hdr->pan_envelope[my_hdr->pan_loop_end].frame) {
						xm_info->pan_cnt[i] = my_hdr->pan_envelope[my_hdr->pan_loop_start].frame;
					}
				}

				/* pan envelope processing */
				if (my_hdr->pan_points == 1) {
					xm_info->env_vol[i] = my_hdr->pan_envelope[0].value;
				} else {
					for (j = 1; j < my_hdr->pan_points; j++) {
						if ((xm_info->pan_cnt[i] < my_hdr->pan_envelope[j].frame) && (xm_info->pan_cnt[i] >= my_hdr->pan_envelope[j-1].frame)) {
							break;
						}
					}
					x1 = my_hdr->pan_envelope[j-1].frame;
					y1 = my_hdr->pan_envelope[j-1].value;
					x2 = my_hdr->pan_envelope[j].frame;
					y2 = my_hdr->pan_envelope[j].value;

					/* set final pan */
					xm_info->env_pan[i] = (((y2 - y1) * (xm_info->pan_cnt[i] - x1)) / (x2 - x1)) + y1;
				}

			} else {
				xm_info->env_pan[i] = 0;
			}
#else
			xm_info->env_pan[i] = 0;
#endif	/* NO_PAN_ENVELOPE */

			/* auto-vibrato */
			/* ok..not sure this is correct...found old mod-doc
			   which states something about y/16 of a semitone etc
			   which is different :/ */
			if (my_hdr->vibrato_depth != 0) {
				if (xm_info->keyoff[i] == 0) {
					if (xm_info->avib_cnt[i] < my_hdr->vibrato_sweep) {
						depth = ((xm_info->avib_cnt[i]++) * my_hdr->vibrato_depth) / my_hdr->vibrato_sweep;
					} else {
						depth = my_hdr->vibrato_depth;
					}
				} else {
					depth = (xm_info->avib_cnt[i] * my_hdr->vibrato_depth) / my_hdr->vibrato_sweep;
				}
				/* update vibrato position */
				rate = xm_info->avib_pos[i] & 0x3f;
				xm_info->avib_pos[i] = rate + my_hdr->vibrato_rate;

				/* depth is now set */
				switch (my_hdr->vibrato_type) {
					/* square */
					case 1:
						if (rate < 32) {
							xm_info->cvib_per[i] = (xm_info->cvib_per[i] + (depth<<1));
						} else {
							xm_info->cvib_per[i] = (xm_info->cvib_per[i] - ((depth)<<1));
						}
						break;
					/* ramp-down */
					case 2:
						xm_info->cvib_per[i] = xm_info->cvib_per[i] + (((depth<<8) - ((depth * rate)<<3))>>7);
						break;
					/* ramp-up */
					case 3:
						xm_info->cvib_per[i] = xm_info->cvib_per[i] - (((depth<<8) - ((depth * rate)<<3))>>7);
						break;
					/* sine */
					default:
						if (rate < 32) {
							xm_info->cvib_per[i] = xm_info->cvib_per[i] + ((SinTab[rate] * depth)>>7);
						} else {
							xm_info->cvib_per[i] = xm_info->cvib_per[i] - ((SinTab[rate & 0x1f] * depth)>>7);
						}
						break;
				}
			}
		}
	}
}

static void
set_final_vol_pan_freq()
{

	uint32 i;
	uint8 finalvol;
	sint8 finalpan;
	sint16 pan, absp;

	/* clamp global volumes */
	if (xm_info->gvol > 64) {
		xm_info->gvol = 64;
	}
	if (xm_info->gvol < 0) {
		xm_info->gvol = 0;
	}
	if (xm_info->mvol > 64) {
		xm_info->mvol = 64;
	}
	if (xm_info->mvol < 0) {
		xm_info->mvol = 0;
	}

	for (i = 0; i < xm_header->channels; i++) {
		if (xm_info->stereo) {
			pan = absp = xm_info->cpan[i];

			absp -= 128;
			if (absp < 0) {
				absp = -absp;
			}

			finalpan = pan + (((xm_info->env_pan[i] - 32)*(128-absp)) / 32);
		} else {
			finalpan = 127;	/* for mono, pan everything to left */
		}

		/* clamp volume */
		if (xm_info->cvol[i] > 64) {
			xm_info->cvol[i] = 64;
		}
		if (xm_info->cvol[i] < 0) {
			xm_info->cvol[i] = 0;
		}

		finalvol = ((xm_info->fadeout_vol[i]>>10) * xm_info->env_vol[i]
			* xm_info->gvol * xm_info->cvol[i])>>18;

		hw_set_vol_pan_freq(i, xm_info->mvol, finalvol, finalpan,
				convert_period(xm_info->cper[i]) + xm_info->cvib_per[i]);
	}

}
