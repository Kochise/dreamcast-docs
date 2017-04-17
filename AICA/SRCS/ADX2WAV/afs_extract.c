/*
	afxcut
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int afs_extract(char *name)
{
	FILE *fp,*out;
	int i,n;
	char buf[0x8000];

	struct {
		char id[4];
		long num;
	} hdr;

	struct {
		long offset;
		long size;
	} *idx;

	char basename[256],*p;
	strcpy(basename,name);

	p = strrchr(basename,'.');
	if (p) *p=0;

	fp = fopen(name,"rb");
	if (fp==NULL) return -1;

	fread(&hdr,1,8,fp);
	if (memcmp(hdr.id,"AFS",4)) {
		fclose(fp);
		printf("not AFS\n");
		return -1;
	}
	n = hdr.num;

	printf("%s - %d\n",name,n);

	idx = malloc(sizeof(*idx)*n);

	fread(idx,8,n,fp);
	for(i=0;i<n;i++) {
		int size;
		char outfile[256];
		sprintf(outfile,"%s_%02d.adx",basename,i);

		out = fopen(outfile,"wb");

		fseek(fp,idx[i].offset,SEEK_SET);
		size = idx[i].size;

		printf("%s %08x %08x\n",outfile,idx[i].offset,size);

		while(size) {
			int rsize = size<sizeof(buf)?size:sizeof(buf);
			rsize = fread(buf,1,rsize,fp);
			fwrite(buf,1,rsize,out);
			size-=rsize;
		}

		fclose(out);
	//	putchar('.');
	}

	free(idx);

	fclose(fp);

	return -1;
}

int main(int argc,char **argv)
{
	int i;

	if (argc<2) {
		printf("DreamCast AFS extract ADX\n");
		return -1;
	}

	for(i=1;i<argc;i++)
		afs_extract(argv[i]);
	return 0;
}
