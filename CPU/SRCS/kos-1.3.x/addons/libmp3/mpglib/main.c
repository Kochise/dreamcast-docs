#include <stdio.h>
#include <fcntl.h>
#include "mpg123.h"
#include "mpglib.h"

char buf[16384];
struct mpstr mp;

int main(int argc,char **argv)
{
	int size;
	char out[8192];
	int len,ret;
	int f, fo;

	f = open(argv[1], O_RDONLY);
	fo = open(argv[2], O_CREAT | O_WRONLY);
	printf("f %d fo %d\n", f, fo);

	InitMP3(&mp);

	while(1) {
		len = read(f,buf,16384);
		if(len <= 0)
			break;
		ret = decodeMP3(&mp,buf,len,out,8192,&size);
		while(ret == MP3_OK) {
			write(fo,out,size);
			ret = decodeMP3(&mp,NULL,0,out,8192,&size);
		}
	}

	close(f);
	close(fo);

  return 0;

}

