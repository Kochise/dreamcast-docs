#include <kos.h>
#include <lwip/lwip.h>
#include <unistd.h>

extern uint8 romdisk[];

void httpd();

int main(int argc, char **argv) {
	struct ip_addr ipaddr, gw, netmask;

	fs_romdisk_mount("/httprd", romdisk);

	httpd();

	return 0;
}





