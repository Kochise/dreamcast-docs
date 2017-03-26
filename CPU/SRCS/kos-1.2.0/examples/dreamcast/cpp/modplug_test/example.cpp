#include <kos.h>
#include <modplug/stdafx.h>
#include <modplug/sndfile.h>

uint16 sound_buffer[65536] = {0};
CSoundFile *soundfile;

void *mod_callback(int len, int * actual)
{
	int res;
	
	res=soundfile->Read(sound_buffer, len)*4/*samplesize*/;
	//printf("res: %i, len: %i\n",res,len);
	if (res<len)
	{
		soundfile->SetCurrentPos(0);
		soundfile->Read(&sound_buffer[res], len-res);
	}
	*actual = len;
	
	return sound_buffer;
}

extern uint8 romdisk[];
KOS_INIT_ROMDISK(romdisk);

int main(int argc, char **argv) {
	cont_cond_t cond;
	uint8	c;
	uint8 *mod_buffer;
	uint32 hnd;
	char filename[]="/rd/NEVER.XM";

	printf("modplug_test beginning\n");

	hnd=fs_open(filename, O_RDONLY);
	if (!hnd) {
		printf("Error reading %s\n",filename);
		return 0;
	}

	printf("Filesize: %i\n",fs_total(hnd));
	mod_buffer=(uint8 *)malloc(fs_total(hnd));
	if (!mod_buffer) {
		printf("Not enough memory\n");
		return 0;
	}
	printf("Memory allocated\n");
	
	if (fs_read(hnd,mod_buffer,fs_total(hnd))!=fs_total(hnd))
	{
		printf("Read error\n");
		free(mod_buffer);
		return 0;
	}
	printf("File read\n");
	
	soundfile = new CSoundFile;
	if (!soundfile) {
		printf("Not enough memory\n");
		free(mod_buffer);
		return 0;
	}
	printf("CSoundFile created\n");
	if (!soundfile->Create(mod_buffer,fs_total(hnd))) {
		printf("Mod not loaded\n");
		free(mod_buffer);
		delete soundfile;
		return 0;
	}
	printf("Mod loaded\n");
	soundfile->SetWaveConfig(44100,16,2);
	printf("Type: %i\n",soundfile->GetType());
	printf("Title: %s\n",soundfile->GetTitle());

	/*fs_close(hnd);
	free(mod_buffer);*/

	snd_stream_init(mod_callback);
	snd_stream_start(44100,1);

	while(1) {
		/* Check key status */
		c = maple_first_controller();
		if (cont_get_cond(c, &cond) >= 0) {
			if (!(cond.buttons & CONT_START))
				break;
		}

		snd_stream_poll();
		
		timer_spin_sleep(10);
	}

	delete soundfile;

	return 0;
}
