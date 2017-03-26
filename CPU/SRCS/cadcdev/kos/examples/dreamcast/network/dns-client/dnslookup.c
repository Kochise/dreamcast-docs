/* KallistiOS ##version##

   dnslookup.c
   Copyright (C)2004 Dan Potter

   Test DNS lookup util.

*/

// Use these for KOS usage.
#include <kos.h>
#include <lwip/lwip.h>

#include <stdio.h>

int main(int argc, char **argv) {
	uint8 ip[4];
	struct sockaddr_in dnssrv;

	// KOS code
	net_init();
	lwip_kos_init();

	// Do the query
	dnssrv.sin_family = AF_INET;
	dnssrv.sin_port = htons(53);
	dnssrv.sin_addr.s_addr = htonl(0x0a030202);
	if (lwip_gethostbyname(&dnssrv, "www.allusion.net", ip) < 0)
		perror("Can't look up name");
	else {
		printf("www.allusion.net is %d.%d.%d.%d\n",
			ip[0], ip[1], ip[2], ip[3]);
	}
	return 0;
}

