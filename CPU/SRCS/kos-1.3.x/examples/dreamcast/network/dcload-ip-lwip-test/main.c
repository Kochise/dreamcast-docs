#include <kos.h>
#include <lwip/lwip.h>

KOS_INIT_FLAGS(INIT_DEFAULT | INIT_NET);

int main(int argc, char **argv) 
{
    file_t d;
    dirent_t *de;

    cont_btn_callback(0, CONT_START, (cont_btn_callback_t)arch_exit);

    lwip_init_dcload();
    
    printf("this is a test of dcload-lwIP\n");

    d = fs_open("/pc", O_RDONLY | O_DIR);
    if (d == 0) {
	printf("Can't open /pc\r\n");
	return 0;
    }
    while ( (de = fs_readdir(d)) ) {
	printf("%s  /  ", de->name);
	if (de->size >= 0) {
	    printf("%d\r\n", de->size);
	} else {
	    printf("DIR\r\n");
	}
    }
    fs_close(d);

    return 0;
}





