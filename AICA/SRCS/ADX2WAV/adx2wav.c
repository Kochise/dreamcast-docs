/*
	adv2wav

	(c)2001 BERO

	http://www.geocities.co.jp/Playtown/2004/
	bero@geocities.co.jp

	adx info from: http://ku-www.ss.titech.ac.jp/~yatsushi/adx.html

*/


#include <stdio.h>
#include <string.h>
#include <fcntl.h>

long read_long(unsigned char *p)
{
	return (p[0]<<24)|(p[1]<<16)|(p[2]<<8)|p[3];
}

int read_word(unsigned char *p)
{
	return (p[0]<<8)|p[1];
}

typedef struct {
	int s1,s2;
} PREV;

//#define	BASEVOL	0x11e0
#define	BASEVOL	0x4000

int convert(short *out,unsigned char *in,PREV *prev)
{
	int scale = ((in[0]<<8)|(in[1]));
	int i;
	int s0,s1,s2,d;
//	int over=0;

	in+=2;
	s1 = prev->s1;
	s2 = prev->s2;
	for(i=0;i<16;i++) {
		d = in[i]>>4;
		if (d&8) d-=16;
		s0 = (BASEVOL*d*scale + 0x7298*s1 - 0x3350*s2)>>14;
	//	if (abs(s0)>32767) over=1;
		if (s0>32767) s0=32767;
		else if (s0<-32768) s0=-32768;
		*out++=s0;
		s2 = s1;
		s1 = s0;

		d = in[i]&15;
		if (d&8) d-=16;
		s0 = (BASEVOL*d*scale + 0x7298*s1 - 0x3350*s2)>>14;
	//	if (abs(s0)>32767) over=1;
		if (s0>32767) s0=32767;
		else if (s0<-32768) s0=-32768;
		*out++=s0;
		s2 = s1;
		s1 = s0;
	}
	prev->s1 = s1;
	prev->s2 = s2;

//	if (over) putchar('.');
}

int adx2wav(char *infile,char *outfile)
{
	FILE *in,*out;
	unsigned char buf[18*2];
	short outbuf[32*2];
	int offset;
	int channel,freq,size,wsize;
	PREV prev[2];

	static struct {
		char hdr1[4];
		long totalsize;

		char hdr2[8];
		long hdrsize;
 		short format;
		short channel;
		long freq;
		long byte_per_sec;
		short blocksize;
		short bits;

		char hdr3[4];
		long datasize;
	} wavhdr = {
		"RIFF",0,
		"WAVEfmt ",0x10,1/* PCM */,2,44100,44100*2*2,2*2,16,
		"data"
	};

	if (strcmp(infile,"-")==0)
		in = stdin;
	else
		in = fopen(infile,"rb");
	if (in==NULL) {
		printf("can't open infile %s\n",outfile);
		return -1;
	}

	fread(buf,1,16,in);

	channel = buf[7];
	freq = read_long(buf+8);
	size = read_long(buf+12);

	offset = read_word(buf+2)-2;
	fseek(in,offset,SEEK_SET);
	fread(buf+1,1,6,in);

	if (buf[0]!=0x80 || memcmp(buf+1,"(c)CRI",6)) {
		puts("not adx!");
		return -1;
	}

	wavhdr.channel = channel;
	wavhdr.freq = freq;
	wavhdr.blocksize = channel*sizeof(short);
	wavhdr.byte_per_sec = freq*wavhdr.blocksize;
	wavhdr.datasize = size*wavhdr.blocksize;
	wavhdr.totalsize = wavhdr.datasize + sizeof(wavhdr)-8;

	if (strcmp(outfile,"-")==0)
		out = stdout;
	else
		out = fopen(outfile,"wb");
	if (out==NULL) {
		printf("can't open outfile %s\n",outfile);
		return -1;
	}

	fwrite(&wavhdr,1,sizeof(wavhdr),out);

	prev[0].s1 = 0;
	prev[0].s2 = 0;
	prev[1].s1 = 0;
	prev[1].s2 = 0;


	if (channel==1)
	while(size) {
		fread(buf,1,18,in);
		convert(outbuf,buf,prev);
		if (size>32) wsize=32; else wsize = size;
		size-=wsize;
		fwrite(outbuf,1,wsize*2,out);
	}
	else if (channel==2)
	while(size) {
		short tmpbuf[32*2];
		int i;

		fread(buf,1,18*2,in);
		convert(tmpbuf,buf,prev);
		convert(tmpbuf+32,buf+18,prev+1);
		for(i=0;i<32;i++) {
			outbuf[i*2]   = tmpbuf[i];
			outbuf[i*2+1] = tmpbuf[i+32];
		}
		if (size>32) wsize=32; else wsize = size;
		size-=wsize;
		fwrite(outbuf,1,wsize*2*2,out);
	}
	fclose(in);
	fclose(out);

	return 0;
}

int main(int argc,char**argv)
{
	int i;
	if (argc<2) {
		puts("DC/SS adx to wav converter by bero\n adx2wav <infile>\n http://www.geocities.co.jp/Playtown/2004/");
		return -1;
	}

//	_fmode = O_BINARY;

	for(i=1;i<argc;i++) {
		char *infile = argv[i];
		char *p,outfile[256];

		p = strrchr(infile,'\\');
		if (p) p++; else p=infile;
		strcpy(outfile,p);

		p = strrchr(outfile,'.');
		if (!p) p = outfile+strlen(outfile);
		strcpy(p,".wav");

		printf("%s -> %s\n",infile,outfile);

		adx2wav(infile,outfile);
	}
	return 0;
}
