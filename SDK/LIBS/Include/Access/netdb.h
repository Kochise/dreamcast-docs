/************************************************************************/
/*    AVE-TCP Socket Library        netdb.h           92/04/15          */
/*       Copyright (C) 1992 ACCESS CO.,LTD.                             */
/************************************************************************/
#ifdef __cplusplus /* Support for C++ */
extern "C" {
#endif /* __cplusplus */

#ifndef	NETDB_H
#define NETDB_H
/* Structures returned by network
* data base libraly. All addresses
* are supplied in host order, and
* returned in network order (suitalbe
* for use in system calls).
*/
struct	hostent {
	char	*h_name;	/* official name of host */
	char	**h_aliases;	/* alias list */
	int	h_addrtype;	/* host address type */
	int	h_length;	/* length of address */
	char	**h_addr_list;	/* list of addresses from name server */
#define	h_addr	h_addr_list[0]	/* address, for backward compatiblity */
};

/*
 * Assumption here is that a network number
 * fits in 32 bits -- probably a poor one.
 */
struct netent {
	char	*n_name;	/* official name of net */
	char		**n_aliases;	/* alias list */
	int		n_addrtype;	/* net address type */
	unsigned long	n_net;		/* network # */
};

struct	servent {
	char	*s_name;	/* officail service name */
	char	**s_aliases;	/* alias list */
	int	s_port;		/* port # */
	char	*s_proto;	/*protocol to use */
};

struct	protoent {
	char	*p_name;	/* official protocol name */
	char	**p_aliases;	/* alias list */
	int	p_proto;	/* protocol # */
};

struct rpcent {
	char	*r_name;	/* name of server for this rpc program */
	char	**r_aliases;	/* alias list */
	int	r_number; 	/* rpc program number */
};

/* struct hostent	*gethostbyname(), *gethostbyaddr(), *gethostent();
 * struct netent	*getnetbyname(), *getnetbyaddr(), *getnetent();
 * struct servent	*getservbyname(), *getservbyport(), *getservent();
 * struct protoent	*getprotobyname(), *getprotobynumber(), *getprotoent();
 * struct rpcent	*getrpcbyname(), *getrpcbynumber(), *getrpcent();
 */

/*
 * Error return codes from gethostbyname() and gethostbyaddr()
 * (when using the resolver)
 */

extern	int	h_errno;

#define	HOST_NOT_FOUND	1	/* Authoritive Answer Host not found */
#define TRY_AGAIN	2	/* Non_Authoritive Host not foundm or 
				 * SERVERFAIL */
#define NO_RECOVERY	3	/* Non recoverable errors, FORMERR, REFUSED,
				 * NOTIMP */
#define NO_DATA		4	/* Valid name, no data record of requested 
				 * type */
#define NO_ADDRESS	NO_DATA	/* no address, look for MX record */

#endif

#ifdef __cplusplus
} /* End of extern "C" { */
#endif /* __cplusplus */
