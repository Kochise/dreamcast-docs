/* KallistiOS ##version##

   isp-settings.c
   Copyright (C)2004 Dan Potter
*/

#include <kos.h>

/* This uses the new flashrom ISP settings code, which is based
   heavily on the info from Sam Steele. Thanks Sam! */

int main(int argc, char **argv) {
	flashrom_ispcfg_t cfg;

	// Get the flashrom config, if it's there.
	if (flashrom_get_ispcfg(&cfg) < 0) {
		printf("Couldn't find any IP-related config info!\n");
	} else {
		if (cfg.ip_valid) {
			static const char * methods[] = {
				"DHCP",
				"Static",
				"Dialup(?)",
				"Unused",
				"PPPoE"
			};
			printf("Method:   %s\n", methods[cfg.method]);
			printf("IP:       %i.%i.%i.%i\n", cfg.ip[0], cfg.ip[1], cfg.ip[2], cfg.ip[3]);
			printf("Netmask:  %i.%i.%i.%i\n", cfg.nm[0], cfg.nm[1], cfg.nm[2], cfg.nm[3]);
			printf("Gateway:  %i.%i.%i.%i\n", cfg.gw[0], cfg.gw[1], cfg.gw[2], cfg.gw[3]);
			printf("DNS 1:    %i.%i.%i.%i\n", cfg.dns[0][0], cfg.dns[0][1], cfg.dns[0][2], cfg.dns[0][3]);
			printf("DNS 2:    %i.%i.%i.%i\n", cfg.dns[1][0], cfg.dns[1][1], cfg.dns[1][2], cfg.dns[1][3]);
			printf("Hostname: '%s'\n",cfg.hostname);
		}
		if (cfg.email_valid) {
			printf("Email:    '%s'\n", cfg.email);
		}
		if (cfg.smtp_valid) {
			printf("SMTP:     '%s'\n", cfg.smtp);
		}
		if (cfg.pop3_valid) {
			printf("POP3:     '%s'\n", cfg.pop3);
		}
		if (cfg.pop3_login_valid) {
			printf("POP3 Login: '%s'\n", cfg.pop3_login);
		}
		if (cfg.pop3_passwd_valid) {
			printf("POP3 Pass:  '%s'\n", cfg.pop3_passwd);
			printf("Proxy Host: '%s'\n", cfg.proxy_host);
		}
		if (cfg.ppp_login_valid) {
			printf("Proxy Port: %d\n", cfg.proxy_port);
			printf("PPP Login:  '%s'\n", cfg.ppp_login);
		}
		if (cfg.ppp_passwd_valid) {
			printf("PPP Pass:   '%s'\n", cfg.ppp_passwd);
		}
        }
	return 0;
}


