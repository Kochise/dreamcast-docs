#include <lwip/lwip.h>
#include <kos/exports.h>
#include <kos/netcfg.h>

/* extern export_sym_t lwip_symtab[];
static symtab_handler_t ls = {
	{ "sym/lwip",
	  0,
	  0x00010000,
	  0,
	  NMMGR_TYPE_SYMTAB,
	  NMMGR_LIST_INIT },
	lwip_symtab
}; */

struct ip_addr dfl_ip, dfl_gw, dfl_nm;

int lwip_get_ipaddr(struct ip_addr * out) {
	*out = dfl_ip;
	return 0;
}

int lwip_get_gateway(struct ip_addr * out) {
	*out = dfl_gw;
	return 0;
}

int lwip_get_netmask(struct ip_addr * out) {
	*out = dfl_nm;
	return 0;
}

static const char * sources[] = {
	"VMU",
	"flash",
	"cwd",
	"CD"
};

netcfg_t lwip_netcfg;

int lwip_kos_init() {
	if (netcfg_load(&lwip_netcfg) < 0) {
		printf("net_lwip: can't load config -- giving up!\n");
		return -1;
	}

#define SETIP(target, src) \
	IP4_ADDR(target, \
		(src >> 24) & 0xff, \
		(src >> 16) & 0xff, \
		(src >> 8) & 0xff, \
		(src >> 0) & 0xff)

	printf("net_lwip: initializing, ip %08lx mask %08lx gw %08lx src %s\n",
		lwip_netcfg.ip, lwip_netcfg.netmask, lwip_netcfg.gateway, sources[lwip_netcfg.src]);
	/* IP4_ADDR(&dfl_ip, 10,3,2,6);
	IP4_ADDR(&dfl_nm, 255,255,255,0);
	IP4_ADDR(&dfl_gw, 10,3,2,1); */
	SETIP(&dfl_ip, lwip_netcfg.ip);
	SETIP(&dfl_nm, lwip_netcfg.netmask);
	SETIP(&dfl_gw, lwip_netcfg.gateway);
	lwip_init_all_static(&dfl_ip, &dfl_nm, &dfl_gw);

	// nmmgr_handler_add(&ls.nmmgr);

	return 0;
}

int lwip_kos_shutdown() {
	printf("net_lwip: exiting\n");
	lwip_shutdown_all();

	// nmmgr_handler_remove(&ls.nmmgr);

	return 0;
}
