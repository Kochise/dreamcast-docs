/* #include <string.h> */

extern volatile unsigned long *debug;

/* Cheapo filesystem / malloc replacements */

#define NULL 0
typedef int FILE;
unsigned char *file_data = (unsigned char *)0x10000;
int where_in_file;

FILE *fs_open(char *fn, char *mode) {
	where_in_file = 0;
	return (FILE*)1;
}

void fs_close(FILE *f) { }

int fs_read(void *buffer, int size, int cnt, FILE *f) {
	unsigned char *outbuf = (unsigned char*)buffer;
	int i;
	for (i=0; i<size*cnt; i++) {
		outbuf[i] = file_data[where_in_file++];
	}
	return cnt;
}

#define SEEK_CUR 0
#define SEEK_SET 1
int fs_seek(FILE *f, int where, int whence) {
	switch(whence) {
		case SEEK_CUR:
			where_in_file += where;
			break;
		case SEEK_SET:
			where_in_file = where;
			break;
	}
	return where_in_file;
}

int fs_tell(FILE *f) {
	return where_in_file;
}

unsigned char *fs_tell_ram() {
	return file_data + where_in_file;
}

int fs_getc(FILE *f) {
	return file_data[where_in_file++];
}


/* Yeah, these are pretty wasteful, but what else are we going to
   do with the RAM?? =) */
void *malloc_base = (void*)0x100000;

void *malloc(int size) {
	void *base = malloc_base;
	malloc_base += (size/4)*4+1;
	return base;
}

void free(void *f) { }

/* Dummy var */
int S_SysVol = 0;

/* String operations */
void memcpy(char *dest, char *src, int len) {
	while (len > 0) {
		*dest++ = *src++;
		len--;
	}
}

void memset(char *dest, int what, int len) {
	while (len > 0) {
		*dest++ = what;
		len--;
	}
}

int strcmp(char *one, char *two) {
	while (*one != 0 && *two != 0) {
		if (*one != *two)
			return -1;
		one++; two++;
	}
	return 0;
}

/*********************************************************/
/* From here on down is my old S3M player with as few mods as possible
   to get it to run. If it looks like weird crusty code, well, that's
   because it is -- it's about 6-7 years old! =) I wrote this thing
   back when I was into PC demos. */


#define USECHANS 16
#define VOLDIV 4

// ================================================================ LOADER PART
typedef struct {
	char	*data;
	char	*patch;
	int	length;
	int	loopbeg;
	int	loopend;
	int	vol;
	int	flags;
	int	c4spd;
	char	smpname[32];
} InsStr;
#define FLAG_LOOP (1 << 0)

typedef struct {
	int	size;
	char	*data;
} PatStr;

PatStr	Pattern[256] = { {0,0} };
char	order[256];
char	loopto;
char	SongName[40];
char	Balance[16];
InsStr	Instr[100];
int	NumSamps = 0;
int	NumOrd = 0;
int	NumPats = 0;
int	Speed = 6, Tempo = 0x7d;
short	paraptn[256];
FILE	*f;

static int ReadS3MPat(int p) {
	int q, sz = 0, row = 0, ch, bp;
	char ci, *buf;

//   fs_seek(f,paraptn[p]*16L,SEEK_SET);
	fs_read(&sz, 2, 1, f);
	if (sz % 16)
		sz = ((sz & 0xFFF0) + 0x10);
	sz -= 2;
	buf = (char*)malloc(sz);
	if (!buf)
		return 0;
	fs_read(buf, sz, 1, f);

	Pattern[p].size = 5 * 32 * 64;
	Pattern[p].data = (char*)malloc(Pattern[p].size);
	if (!Pattern[p].data)
		return 0;

	for (q = 0; q < 32 * 64 * 5; q += 5) {
		Pattern[p].data[q] = 0xff;
		Pattern[p].data[q + 1] = 0;
		Pattern[p].data[q + 2] = 0xff;
		Pattern[p].data[q + 3] = 0xff;
		Pattern[p].data[q + 4] = 0;
	}

	for (bp = 0; bp < sz && row < 64;) {
		ci = buf[bp++];
		if (!ci)
			row++;
		else {
			ch = ci & 31;
			if (ci & 32) {
				Pattern[p].data[(row * 32 + ch) * 5] =
				    buf[bp++];	// note+ins
				Pattern[p].data[(row * 32 + ch) * 5 + 1] =
				    buf[bp++];
			}
			if (ci & 64) {
				Pattern[p].data[(row * 32 + ch) * 5 + 2] =
				    buf[bp++];	// vol
			}
			if (ci & 128) {
				Pattern[p].data[(row * 32 + ch) * 5 + 3] =
				    buf[bp++];	// command
				Pattern[p].data[(row * 32 + ch) * 5 + 4] =
				    buf[bp++];	// info
			}
		}
		q = q;
	}
	free(buf);

	return 1;
}

// Flags: +1=loop, +2=stereo ni, +4=16 bit (intel)
static int ReadS3MSmp(int q, char Signed) {
	int	i;

	Instr[q].patch = fs_tell_ram(NULL);
	fs_seek(NULL, Instr[q].length, SEEK_CUR);
	if (Instr[q].length && !Signed) {
		for (i=0; i<Instr[q].length; i++) {
			Instr[q].patch[i] ^= 0x80;
		}
	}
	return 1;
}

static int ReadS3MIns(int q) {
	char magic[] = "SCRS", qq;

	qq = fs_getc(f);
	if (qq != 1 && qq != 0)
		return 0;	// adl instrument
	fs_seek(f, 13, SEEK_CUR);	/* dosname */
	fs_getc(f);
	fs_getc(f);
	fs_read(&Instr[q].length, 4, 1, f);
	fs_read(&Instr[q].loopbeg, 4, 1, f);
	fs_read(&Instr[q].loopend, 4, 1, f);
	Instr[q].vol = fs_getc(f);
	if (Instr[q].vol > 63)
		Instr[q].vol = 63;
	fs_getc(f);
	if (fs_getc(f))
		return 0;	// ADPCM packed
	Instr[q].flags = fs_getc(f);
	fs_read(&Instr[q].c4spd, 4, 1, f);
	fs_seek(f, 4 * 3, SEEK_CUR);
	fs_read(Instr[q].smpname, 28, 1, f);
	Instr[q].smpname[27] = 0;
	fs_read(magic, 4, 1, f);
//   if (strcmp(magic,"SCRS")) return 0;
	return 1;
}

int s3m_load() {
	char Magic1[] = "SCRM";
	int q = 0;
	char Signed;
	char Chnset[32];
	short parains[256];

	f = fs_open("", "rb");
	if (!f)
		return 0;

// ******************************************** Read header
	fs_read(SongName, 28, 1, f);
	fs_getc(f);		// \x1a
	if (fs_getc(f) != 0x10) {
		fs_close(f);
		return 0;
	}
	fs_getc(f);
	fs_getc(f);		// dummies
	fs_read(&NumOrd, 2, 1, f);
	fs_read(&NumSamps, 2, 1, f);
	fs_read(&NumPats, 2, 1, f);
	fs_getc(f);
	fs_getc(f);		// song flags
	fs_getc(f);
	fs_getc(f);		// tracker version
	Signed = fs_getc(f);
	if (Signed == 2)
		Signed = 0;
	fs_getc(f);		// dummy
	fs_read(Magic1, 4, 1, f);
	if (strcmp(Magic1, "SCRM")) {
		fs_close(f);
		return 0;
	}
	S_SysVol = fs_getc(f) * 4 / VOLDIV;
	Speed = fs_getc(f);
	Tempo = fs_getc(f);
	fs_seek(f, 13, SEEK_CUR);
	fs_read(Chnset, 32, 1, f);
	for (q = 0; q < 16; q++)
		Balance[q] = Chnset[q] & 0x7f;
	fs_read(order, NumOrd, 1, f);
	fs_read(parains, 2 * NumSamps, 1, f);
	fs_read(paraptn, 2 * NumPats, 1, f);

	q = fs_tell(f);
	if (q % 16) {
		q = ((q & 0xFFF0) + 0x10);
		fs_seek(f, q, SEEK_SET);
	}
// ******************************************** Read instruments
	for (q = 0; q < NumSamps; q++) {
		fs_seek(f, parains[q] * 16L, SEEK_SET);
		if (!ReadS3MIns(q)) {
			fs_close(f);
			return 0;
		}
	}

// ******************************************** Read patterns
	for (q = 0; q < NumPats; q++) {
		fs_seek(f, paraptn[q] * 16L, SEEK_SET);
		if (!ReadS3MPat(q)) {
			fs_close(f);
			return 0;
		}
	}

// ******************************************** Read samples
	for (q = 0; q < NumSamps; q++)
		if (!ReadS3MSmp(q, Signed)) {
			fs_close(f);
			return 0;
		}

	return 1;
}

// ================================================================ PLAYER PART

int CurPattern, EditRow, CurOrder;
char *ptn;
int TPS, Frame = 0, CCnt = 4, patbrk = -1, ordbrk = -1;
#define cs ((EditRow*32+q)*5)
int period[12] = { 1712, 1616, 1524, 1440, 1356, 1280, 1208, 1140, 1076, 1016, 960, 906 };
int finec4[16] = { 7895, 7941, 7985, 8046, 8107, 8169, 8232, 8280, 8363, 8413, 8463,
	8529, 8581, 8651, 8723, 8757 };
	
#define HZ(q) (14317456/(q))
int VibTable[64] = {
	0, 24, 49, 74, 97, 120, 141, 161,
	180, 197, 212, 224, 235, 244, 250, 253,
	255, 253, 250, 244, 235, 224, 212, 197,
	180, 161, 141, 120, 97, 74, 49, 24,

	0, -24, -49, -74, -97, -120, -141, -161,
	-180, -197, -212, -224, -235, -244, -250, -253,
	-255, -253, -250, -244, -235, -224, -212, -197,
	-180, -161, -141, -120, -97, -74, -49, -24
};

static int fTPS(int x) {
	return x * 50 * 4 / 125;
}

static void Neushorter(int nc) {
	CurOrder = nc;
	if ((unsigned char)order[CurOrder] == 0xFE)
		CurOrder++;
	if ((unsigned char)order[CurOrder] == 0xFF)
		CurOrder = 0;
	CurPattern = order[CurOrder];
	ptn = Pattern[CurPattern].data;
	EditRow = 0;
}

static int s3mfreq(int note, int c4) {
	int f;

	if (c4)
		c4++;
	f = ((8363 * 16 * period[note & 0xF]) >> (note >> 4)) / c4;
	if (!f)
		f++;
	return f;
}

#define effc(q) ((q)-'A'+1)

typedef struct {
	int patch;		// 'current' status
	int freq;
	int vol;
	int kick, start;
	int pan;

	int eff, dat, note;	// status 'to be' and update counters
	int portspeed;
	int vpspeed;
	int tfreq;
	int vibpos;
	int vibspd;
	int vibdepth;
} chnststr;

chnststr chnstat[32];

static void DoNote(char *p, chnststr * stat) {
	char d = p[0], b = p[1];

	stat->eff = p[3];
	stat->dat = p[4];

	if (b) {
		b--;
		stat->patch = (int)b;
		stat->vol = Instr[(int)b].vol;
	}
	b = stat->patch;

	if ((unsigned char)p[2] != 0xFF)
		stat->vol = p[2];

	if ((unsigned char)d != 0xFF) {
		stat->note = d;
		if (d)
			stat->tfreq = s3mfreq(d, Instr[(int)b].c4spd);

		if (stat->eff == effc('G'))
			return;
		stat->freq = stat->tfreq;
		stat->kick = 1;
		stat->start = 0;
	}
}

static void DoVib(chnststr * stat) {
	int temp;

	temp = VibTable[(stat->vibpos >> 2) & 0x3f];
	temp *= stat->vibdepth;
	temp >>= 7;
	stat->freq = stat->tfreq + temp * 2;
	stat->vibpos += stat->vibspd;
}

static void DoVSld(chnststr * stat) {
	if ((stat->dat & 0x0F) == 0x0F && (stat->dat & 0xF0)) {	// FineVol up
		stat->vpspeed = stat->dat >> 4;
		stat->vol += stat->vpspeed;
		if (stat->vol > 63)
			stat->vol = 63;
		stat->eff = 0xFF;
		return;
	}
	if ((stat->dat & 0xF0) == 0xF0) {	// FineVol dn
		if (stat->dat & 0xF)
			stat->vpspeed = stat->dat & 0xF;
		stat->vol -= stat->vpspeed;
		if (stat->vol < 0)
			stat->vol = 0;
		stat->eff = 0xFF;
		return;
	}
	if (!(stat->dat & 0xF0)) {	// Volport dn
		if (stat->dat & 0xF)
			stat->vpspeed = stat->dat & 0xF;
		stat->vol -= stat->vpspeed;
		if (stat->vol < 0)
			stat->vol = 0;
		return;
	}
	if (!(stat->dat & 0x0F)) {	// Volport up
		if (stat->dat >> 4)
			stat->vpspeed = stat->dat >> 4;
		stat->vol += stat->vpspeed;
		if (stat->vol > 63)
			stat->vol = 63;
		return;
	}
}

static int DoPort(chnststr * stat) {
	if (stat->freq < stat->tfreq) {
		stat->freq += stat->portspeed;
		if (stat->freq >= stat->tfreq) {
			stat->freq = stat->tfreq;
			return 1;
		}
		return 0;
	}
	if (stat->freq > stat->tfreq) {
		stat->freq -= stat->portspeed;
		if (stat->freq <= stat->tfreq) {
			stat->freq = stat->tfreq;
			return 1;
		}
		return 0;
	}
	return 1;
}

static void DoEffects(chnststr * stat) {
	int eff, dat, p, f;

	eff = stat->eff;
	dat = stat->dat;
	if (eff == 0xFF)
		return;
	switch (eff) {
	case effc('A'):	// Set Speed
		Speed = dat;
		break;
	case effc('B'):	// Jump to new order
		ordbrk = dat;
		patbrk = 0;
		break;
	case effc('C'):	// Jump to next pattern
		patbrk = dat;
		break;
	case effc('D'):	// Volslds
		stat->eff = eff;
		stat->dat = dat;
		DoVSld(stat);
		eff = stat->eff;
		dat = stat->dat;
		break;
	case effc('E'):	// Pitchsld down
		switch (dat & 0xF0) {
		case 0xF0:	// FineSld down
			if (dat & 0xF) {
				stat->portspeed = (dat & 0xF) * 4;
				stat->freq += stat->portspeed;
			}
			eff = 0xFF;
			break;
		case 0xE0:	// ExFineSld down
			if (dat & 0xF) {
				stat->portspeed = (dat & 0xF);
				stat->freq += stat->portspeed;
			}
			eff = 0xFF;
			break;
		default:	// port dn
			if (dat)
				stat->portspeed = dat * 4;
			stat->freq += stat->portspeed;
			break;
		}
		break;
	case effc('F'):	// Pitchsld up
		switch (dat & 0xF0) {
		case 0xF0:	// FineSld up
			if (dat & 0xF) {
				stat->portspeed = (dat & 0xF) * 4;
				stat->freq -= stat->portspeed;
			}
			eff = 0xFF;
			break;
		case 0xE0:	// ExFineSld up
			if (dat & 0xF) {
				stat->portspeed = (dat & 0xF);
				stat->freq -= stat->portspeed;
			}
			eff = 0xFF;
			break;
		default:	// port up
			if (dat)
				stat->portspeed = dat * 4;
			stat->freq -= stat->portspeed;
			break;
		}
		break;
	case effc('G'):	// noteport
		if (dat)
			stat->portspeed = dat * 4;
		if (DoPort(stat)) {
			eff = 0xFF;
			dat = stat->dat;
		}
		break;
	case effc('H'):	// vibrato
		if (dat & 0x0F)
			stat->vibdepth = (dat & 0x0F);
		if (dat & 0xF0)
			stat->vibspd = (dat & 0xF0) >> 2;
		dat = 0;
		DoVib(stat);
		break;
	case effc('I'):
		break;
	case effc('J'):
		break;
	case effc('K'):
		stat->eff = eff;
		stat->dat = dat;
		DoVib(stat);
		DoVSld(stat);
		eff = stat->eff;
		dat = stat->dat;
		break;
	case effc('L'):
		stat->eff = eff;
		stat->dat = dat;
		DoPort(stat);
		DoVSld(stat);
		eff = stat->eff;
		dat = stat->dat;
		break;
	case effc('O'):
		stat->start = dat * 256;
		eff = 0xFF;
		break;
	case effc('Q'):
		switch (eff >> 4) {	// process the volume part of the cmd
		case 1:
			stat->vol--;
			break;
		case 2:
			stat->vol -= 2;
			break;
		case 3:
			stat->vol -= 4;
			break;
		case 4:
			stat->vol -= 8;
			break;
		case 5:
			stat->vol -= 16;
			break;
		case 6:
			stat->vol = stat->vol * 2 / 3;
			break;
		case 7:
			stat->vol /= 2;
			break;
		case 9:
			stat->vol++;
			break;
		case 0xA:
			stat->vol += 2;
			break;
		case 0xB:
			stat->vol += 4;
			break;
		case 0xC:
			stat->vol += 8;
			break;
		case 0xD:
			stat->vol += 16;
			break;
		case 0xE:
			stat->vol = stat->vol * 3 / 2;
			break;
		case 0xF:
			stat->vol = stat->vol * 2;
			break;
		}
		if (!(Frame % eff)) {
			stat->kick = 1;
			stat->start = 0;
		}
		break;
	case effc('R'):
		break;
	case effc('S'):
		switch (dat & 0xF0) {
		case 0x20:
			p = stat->patch;
			f = stat->freq * Instr[p].c4spd;
			stat->freq = f / finec4[dat & 0xF];
			break;
		case 0x80:
			stat->pan = dat & 0xF;
			break;
		case 0xC0:
			if (Frame == (dat & 0xF)) {
				stat->vol = 0;
				eff = 0xFF;
			}
			break;
		case 0xD0:
			if (Frame == (dat & 0xF)) {
				stat->kick = 1;
				stat->start = 0;
				eff = 0xFF;
			}
			break;
		}
		break;
	case effc('T'):
		Tempo = dat;
		break;
	case effc('V'):
		S_SysVol = dat * 4 / VOLDIV;
		break;
	case effc('X'):
		/* XHandler(dat); */
		eff = 0xFF;
		break;
	}
	stat->eff = eff;
	stat->dat = dat;
}

static void UpdatePlay() {
	int q;
	int loopst, loopend, loopflag, pan;
	unsigned long start;

	for (q = 0; q < USECHANS; q++) {
		if (!chnstat[q].freq)
			chnstat[q].freq++;
		if (chnstat[q].kick) {
			if (Instr[chnstat[q].patch].flags & FLAG_LOOP) {
				//loopst = chnstat[q].start;
				loopst = Instr[chnstat[q].patch].loopbeg;
				loopend = Instr[chnstat[q].patch].loopend;
				start = (unsigned long)Instr[chnstat[q].patch].patch;
				loopflag = 1;
			} else {
				loopst = 0;
				loopend = Instr[chnstat[q].patch].length;
				start = (unsigned long)Instr[chnstat[q].patch].patch;
				/*loopend = Instr[chnstat[q].patch].loopend
					- chnstat[q].start;
				start = (unsigned long)Instr[chnstat[q].patch].patch
					+ chnstat[q].start; */
				loopflag = 0;
			}
			
			if (debug[1])
				pan = 0x80;
			else
				pan = chnstat[q].pan * 16;
			aica_play(q, start, 1 /*SM_8BIT*/, loopst, loopend,
				HZ(chnstat[q].freq), chnstat[q].vol * 14 / 4,
				pan, loopflag);
			//debug[q] = 0xff;
			chnstat[q].kick = 0;
		} else {
			aica_vol(q, chnstat[q].vol * 14 / 4);
			aica_freq(q, HZ(chnstat[q].freq));
			if (!debug[1])
				aica_pan(q, chnstat[q].pan * 16);
		}
		
		TPS = fTPS(Tempo);
	}
}

/* cruftus hackus maximus */
void check_smp_iface() {
	static int channel = USECHANS;
	int where, size, hz;
	switch(debug[2]) {
		case 0: return;
		case 1:	/* Play sound effect */
			where = debug[3];
			size = debug[4];
			hz = debug[5];
			aica_stop(channel);
			aica_play(channel, where, 0 /* SM_16BIT */, 0, size,
				hz, 0xe0, 0x80, 0);
			channel++;
			if (channel >= 64) channel = USECHANS;
			break;
	}
	debug[2] = 0;
}

void PlayInt() {
	int q;

	check_smp_iface();

	CCnt--;
	if (CCnt) return;
	//CCnt=4;
	CCnt=3;

// Stuff that needs to be executed once per frame goes here
	for (q = 0; q < USECHANS; q++)
		DoEffects(&chnstat[q]);

// Actually do all the output to the soundcard
	UpdatePlay();

// Next count off frames
	Frame++;
	if (Frame < Speed)
		return;
	Frame = 0;

// Stuff that needs to be executed once per row goes here
	if (patbrk != -1) {
		Neushorter(CurOrder + 1);
		EditRow = patbrk;
		patbrk = -1;
	} else {
		if (EditRow == 64) {
			if (ordbrk != -1)
				Neushorter(ordbrk);
			else
				Neushorter(CurOrder + 1);
			ordbrk = -1;
		}
	}

	for (q = 0; q < USECHANS; q++)
		DoNote(ptn + cs, &chnstat[q]);
	EditRow++;
	UpdatePlay();
}


extern unsigned int jps;

void s3m_start_playback() {
	int q;
	int lasttps = -1;

	memset(chnstat, 0, sizeof(chnstat));

	if (debug[1]) {
		for (q=0; q<16; q++)
			Balance[q] = 8;
	} else {
		for (q = 0; q < 16; q += 2)
			Balance[q] = 2;
		for (q = 1; q < 16; q += 2)
			Balance[q] = 13;
	}
	for (q = 0; q < 16; q++) {
		aica_stop(q);
		aica_pan(q, Balance[q] * 16);
		chnstat[q].pan = Balance[q];
		aica_vol(q, 255);
		chnstat[q].vol = 63;
		//debug[q] = 0;
	}
	EditRow = 0;
	CurOrder = 0;
	CurPattern = order[0];
	ptn = Pattern[CurPattern].data;
	patbrk = -1;
	ordbrk = -1;
	TPS = fTPS(Tempo);

	/* *debug = 0x1000; */

	/* We'll play infinitely! =) */
	/*jps = 256 - (44100 / 4000);*/
	while (1) {
		PlayInt();
		
		if (TPS == 0) TPS++;
		/*if (lasttps != TPS) {
			jps = 256 - (44100 / (TPS * 6));
			lasttps = TPS;
		} */
		
		*debug = 0x1001 | (TPS << 16);
		
		//timer_wait(6);
		
		timer_wait(4410/TPS);
		
		/*for (q=0; q<16; q++)
			if (debug[q]>0) debug[q]--; */
		*debug = 0x1002 | (TPS << 16);
	}
}



