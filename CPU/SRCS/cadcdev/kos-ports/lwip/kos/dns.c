/* KallistiOS ##version##

   lwip/dns.c
   Copyright (C)2004 Dan Potter
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "lwip/lwip.h"

/*
   This performs a simple DNS A-record query. It hasn't been tested extensively
   but so far it seems to work fine.

   This relies on the really sketchy UDP support in the KOS lwIP port, so it
   can be cleaned up later once that's improved.

   We really need to be setting errno in here too...
 */



/* Basic query process:

   - Send a DNS message to the server on port 53, with one query payload.
   - Receive DNS message from port 53 with one or more answer payloads (hopefully).
 */

// These structs were all taken from RFC1035, page 26.
typedef struct {
	uint16	id;		// Can be anything
	uint16	flags;		// Should have 0x0100 set for query, 0x8000 for response
	uint16	qdcount, ancount, nscount, arcount;
	uint8	data[0];	// Payload
} dnsmsg_t;

/* Flags:
  Query/Response (1 bit) -- 0 = Query, 1 = Response
  Opcode (4 bits) -- 0 = Standard, 1 = Inverse, 2 = Status
  AA (1 bit) -- authoritative answer
  TC (1 bit) -- truncated message
  RD (1 bit) -- recursion desired
  RA (1 bit) -- recursion available
  Z (1 bit) -- zero
  RCODE (4 bits) -- 0 = No Error, >0 = Error

  Generally a query will have 0x0100 here, and a typical
  response will have 0x8180.
*/

/* Query section. A standard DNS query will have one query section
   and no other payloads. There is no padding.

   QNAME: one or more "labels", representing a domain name. For
   example "yuna.dp.allusion.net" is "yuna, dp, allusion, net". Each
   label has one length byte followed by N data bytes. A zero
   length byte terminates.

   QTYPE: two-byte code specifying the RR type of the query. For a
   normal DNS query this should be 0x0001 (A).

   QCLASS: two-byte code specifying the class of the query. For a
   normal DNS query this should be 0x0001 (IN).

   Common RR types:
     A      1
     NS     2
     CNAME  5
     SOA    6
     PTR    12
     MX     15
     TXT    16
 */

// Construct a DNS query for an A record by host name. "buf" should
// be at least 1500 bytes, to make sure there's room.
static int dns_make_query(const char * host, dnsmsg_t * buf) {
	int i, o, ls, t;

	// Build up the header.
	buf->id = htons(rand() & 0xffff);
	buf->flags = htons(0x0100);
	buf->qdcount = htons(1);
	buf->ancount = htons(0);
	buf->nscount = htons(0);
	buf->arcount = htons(0);

	// Parse the host name into pieces.
	ls = 0; o = 1; t = strlen(host);
	for (i=0; i<=t; i++) {
		if (host[i] == '.' || i == t) {
			buf->data[ls] = (o - ls) - 1;
			ls = o; o++;
		} else {
			buf->data[o++] = host[i];
		}
	}
	buf->data[ls] = 0;

	// Might be unaligned now... so just build it by hand.
	buf->data[o++] = 0x00;
	buf->data[o++] = 0x01;
	buf->data[o++] = 0x00;
	buf->data[o++] = 0x01;

	// Return the full message size.
	return o + sizeof(dnsmsg_t);
}

/* Resource records. A standard DNS response will have one query
   section (the original one) plus an answer section. It may have
   other sections but these can be ignored.

   NAME: Same as QNAME, with one caveat (see below).
   TYPE: Two-byte RR code (same as QTYPE).
   CLASS: Two-byte class code (same as QCLASS).
   TTL: Four-byte time to live interval in seconds; this entry should
     not be cached longer than this.
   RDLENGTH: Two-byte response length (in bytes).
   RDATA: Response data, size is RDLENGTH.

   For "NAME", note that this may also be a "back pointer". This is
   to save space in DNS queries. Back pointers are 16-bit values with
   the upper two bits set to one, and the lower bits representing an
   offset within the full DNS message. So e.g., 0xc00c for the NAME
   means to look at offset 12 in the full message to find the NAME
   record.

   For A records, RDLENGTH is 4 and RDATA is a 4-byte IP address.

   When doing queries on the internet you may also get back CNAME
   entries. In these responses you may have more than one answer
   section (e.g. a 5 and a 1). The CNAME answer will contain the real
   name, and the A answer contains the address.
 */

// Scans through and skips a label in the data payload, starting
// at the given offset. The new offset (after the label) will be
// returned.
static int dns_skip_label(dnsmsg_t * resp, int o) {
	int cnt;

	// End of the label?
	while (resp->data[o] != 0) {
		// Is it a pointer?
		if ((resp->data[o] & 0xc0) == 0xc0)
			return o + 2;

		// Skip this part.
		cnt = resp->data[o++];
		o += cnt;
	}

	// Skip the terminator
	o++;

	return o;
}

// Scans through and copies out a label in the data payload,
// starting at the given offset. The new offset (after the label)
// will be returned as well as the label string.
static int dns_copy_label(dnsmsg_t * resp, int o, char * outbuf) {
	int cnt;
	int rv = -1;

	// Do each part.
	outbuf[0] = 0;
	for ( ; ; ) {
		// Is it a pointer?
		if ((resp->data[o] & 0xc0) == 0xc0) {
			int offs = ((resp->data[o] & ~0xc0) << 8) | resp->data[o+1];
			if (rv < 0)
				rv = o + 2;
			o = offs - sizeof(dnsmsg_t);
		} else {
			cnt = resp->data[o++];
			if (cnt) {
				if (outbuf[0] != 0)
					strcat(outbuf, ".");
				strncat(outbuf, resp->data + o, cnt);
				o += cnt;
			} else
				break;
		}
	}

	if (rv < 0)
		return o;
	else
		return rv;
}

// Parse a response packet from the DNS server. The IP address
// will be filled in upon a successful return, otherwise the
// return value will be <0.
static int dns_parse_response(dnsmsg_t * resp, uint8 * ipaddrout) {
	int i, o, arecs;
	uint16 flags;
	char tmp[64];

	// Check the flags first to see if it was successful.
	flags = ntohs(resp->flags);
	if (!(flags & 0x8000)) {
		// Not our response!
		return -1;
	}
	if (flags & 0x000f) {
		// Got an error...
		//printf("Response was error code %d\n", flags & 0x000f);
		return -1;
	}

	// Getting zero answers is also a failure.
	if (ntohs(resp->ancount) < 1) {
		//printf("No responses were returned.\n");
		return -1;
	}
	//printf("%d responses were returned.\n", ntohs(resp->ancount));

	// If we have any query sections (should have one anyway), skip 'em.
	o = 0;
	for (i=0; i<ntohs(resp->qdcount); i++) {
		// Skip the label.
		o = dns_skip_label(resp, o);

		// And the two type fields.
		o += 4;
	}

	// Ok, now the answer section (what we're interested in).
	//printf("skipped %d query sections, offset now %d\n",
	//	ntohs(resp->qdcount), o);
	arecs = 0;
	for (i=0; i<ntohs(resp->ancount); i++) {
		//printf("record at %d\n", o);
		// Copy out the label, in case we need it.
		o = dns_copy_label(resp, o, tmp);

		// Get the type code. If it's not A, skip it.
		if (resp->data[o] == 0x00 && resp->data[o+1] == 0x01) {
			uint16 len;

			//printf("Found A record for '%s'\n", tmp);
			o += 8;
			memcpy(&len, resp->data + o, 2);
			len = ntohs(len); o += 2;
			//printf("  record is %d bytes long: %d.%d.%d.%d", len,
			//	resp->data[o], resp->data[o+1], resp->data[o+2], resp->data[o+3]);
			ipaddrout[0] = resp->data[o];
			ipaddrout[1] = resp->data[o+1];
			ipaddrout[2] = resp->data[o+2];
			ipaddrout[3] = resp->data[o+3];
			o += len;
			arecs++;
		} else if (resp->data[o] == 0x00 && resp->data[o+1] == 0x05) {
			uint16 len;
			char tmp2[64];

			o += 8;
			memcpy(&len, resp->data + o, 2); o += 2;
			o = dns_copy_label(resp, o, tmp2);
			//printf("Skipping CNAME for '%s' (%s)\n", tmp, tmp2);
		} else {
			uint16 len;

			//printf("Skipping record type %d for '%s'\n", resp->data[o+1], tmp);
			o += 8;
			memcpy(&len, resp->data + o, 2);
			len = ntohs(len); o += 2+len;
		}
	}

	//printf("\ndone parsing\n");

	// Receive no A records is also a failure.
	return arecs > 0 ? 0 : -1;
}

int lwip_gethostbyname(const struct sockaddr_in * dnssrv, const char * name, uint8 * ipout) {
	struct sockaddr_in toaddr;
	socklen_t addrsize;
	uint8	qb[1500];
	int 	size, sock;

	// Setup a query
	size = dns_make_query(name, (dnsmsg_t *)qb);

	// Make a socket to talk to the DNS server.
	sock = socket(PF_INET, SOCK_DGRAM, 0);
	if (sock < 0)
		return -1;

	// Send the query to the server.
	memcpy(&toaddr, dnssrv, sizeof(struct sockaddr_in));
	toaddr.sin_family = AF_INET;
	addrsize = sizeof(toaddr);
	if (sendto(sock, qb, size, 0, (struct sockaddr *)&toaddr, addrsize) < 0)
		return -1;

	// Get the response.
	if ((size = recvfrom(sock, qb, 1500, 0, (struct sockaddr *)&toaddr, &addrsize)) < 0)
		return -1;

	// KOS doesn't fill these in correctly yet
	/*assert( toaddr.sin_port = dnssrv->port );
	assert( toaddr.sin_addr.s_addr = dnssrv->sin_addr.s_addr ); */

	// Parse the response
	dns_parse_response((dnsmsg_t *)qb, ipout);

	// Close the socket
	close(sock);

	return 0;
}

