/* KallistiOS ##version##

   netcfg.c
   Copyright (C)2003 Dan Potter

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <kos/netcfg.h>

CVSID("$Id: netcfg.c,v 1.1 2003/07/15 07:58:28 bardtx Exp $");

int netcfg_load_from(const char * fn, netcfg_t * out) {
	FILE * f;
	char buf[64], *b;
	int l;

	assert( out );

	// Open the file
	f = fopen(fn, "rb");
	if (!f)
		return -1;

	// Read each line...
	while (fgets(buf, 64, f)) {
		// Skip comments and blank lines
		if (buf[0] == 0 || buf[0] == '#')
			continue;

		// Strip newlines
		l = strlen(buf);
		if (buf[l-1] == '\n') {
			buf[l-1] = 0;
			l--;
		}
		if (buf[l-1] == '\r') {
			buf[l-1] = 0;
			l--;
		}

		// Look for an equals
		b = strchr(buf, '=');
		if (!b)
			continue;

		*b = 0; b++;

		// What was the line type?
		if (!strcmp(buf, "driver")) {
			strcpy(out->driver, b);
		} else if (!strcmp(buf, "ip")) {
			out->ip = strtoul(b, NULL, 16);
		} else if (!strcmp(buf, "gateway")) {
			out->gateway = strtoul(b, NULL, 16);
		} else if (!strcmp(buf, "netmask")) {
			out->netmask = strtoul(b, NULL, 16);
		}
	}

	fclose(f);

	return 0;
}

int netcfg_load(netcfg_t * out) {
	file_t f;
	dirent_t * d;
	char buf[64];

	// Scan for VMUs
	f = fs_open("/vmu", O_RDONLY | O_DIR);
	if (f >= 0) {
		for ( ; ; ) {
			d = fs_readdir(f);
			if (!d) {
				fs_close(f);
				break;
			}

			sprintf(buf, "/vmu/%s/net.cfg", d->name);
			if (netcfg_load_from(buf, out) >= 0) {
				fs_close(f);
				return 0;
			}
		}
	}

	// Didn't work out.. try the current dir.
	if (netcfg_load_from("net.cfg", out) >= 0)
		return 0;

	// Finally, try the CD
	return netcfg_load_from("/cd/net.cfg", out);
}

int netcfg_save_to(const char * fn, const netcfg_t * cfg) {
	FILE * f;
	char buf[64];

	assert( cfg );

	// Open the output file
	f = fopen(fn, "wb");
	if (!f)
		return -1;

	// Write out each line...
	sprintf(buf, "# KOS Network Config written by netcfg_save_to\n");
	if (fwrite(buf, strlen(buf), 1, f) != 1)
		goto error;

	sprintf(buf, "driver=%s\n", cfg->driver);
	if (fwrite(buf, strlen(buf), 1, f) != 1)
		goto error;

	sprintf(buf, "ip=%08lx\n", cfg->ip);
	if (fwrite(buf, strlen(buf), 1, f) != 1)
		goto error;

	sprintf(buf, "gateway=%08lx\n", cfg->gateway);
	if (fwrite(buf, strlen(buf), 1, f) != 1)
		goto error;

	sprintf(buf, "netmask=%08lx\n", cfg->netmask);
	if (fwrite(buf, strlen(buf), 1, f) != 1)
		goto error;

	fclose(f);

	return 0;

error:
	fclose(f);
	return -1;
}

int netcfg_save(const netcfg_t * cfg) {
	file_t f;
	dirent_t * d;
	char buf[64];

	// Scan for a VMU
	f = fs_open("/vmu", O_RDONLY | O_DIR);
	if (f < 0)
		return -1;

	d = fs_readdir(f);
	if (!d) {
		fs_close(f);
		return -1;
	}

	sprintf(buf, "/vmu/%s/net.cfg", d->name);
	fs_close(f);

	return netcfg_save_to(buf, cfg);
}
