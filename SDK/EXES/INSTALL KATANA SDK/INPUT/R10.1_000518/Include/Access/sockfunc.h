/************************************************************************/
/*    AVE-TCP Socket Library        sockfunc.h                          */
/*       Copyright (C) 1992 ACCESS CO.,LTD.                             */
/************************************************************************/

#ifdef __cplusplus /* Support for C++ */
extern "C" {
#endif /* __cplusplus */

/***   sock_lib.c   ***/
short	sock_find(short);
short	sock_h_find(short);
short	sock_empty(void);
short	sock_init(SOCK_ATRB *);

SOCK_RECV 	*recv_find(short),*recv_empty(short),*recv_search(short);
void	recv_delt_all(short);
void	recv_delt(SOCK_RECV *);
void	bcopy(char *, char *, int);
void	bzero(char *, int);


/***   acs_lib.c   ***/
char * a_strlwr( char * );
int	a_isspace(char);
char * a_strcat( char *, char * );
char	*a_strncpy( char *, char *, unsigned short);
int	a_atoi(unsigned char *);
void	a_getpsp(unsigned long *);
char	*a_getenv(unsigned long, char *);
short	a_getpath( unsigned char *, unsigned char *, short * );
/* void	a_waiting(int); */
char	*mygets(char *, short, short);
void	del_comment(unsigned char *);
unsigned char	*skipspace(unsigned char *);
unsigned char  *skipnonspace(unsigned char *);
short	myopen(char *);
void	myclose(short);
void	myrewind(short);

/***   api_lib.c   ***/
short	api_rsd_chk(void);
short	api_set(void);
u_short	tcp_stat(short,u_short *,u_short *,u_short *,u_short *);
short	tcp_ready(short);
short	tcp_lstn_ready(short);
short	get_ipaddr(u_long *);
u_long	notify_exec_for_socket(short,short);
void	accept_exec(short,short,short,short,short);
u_long	a_ntohl(u_long);
u_short	a_ntohs(u_short);

#if 0
short	tcp_open(u_short,u_long,u_short);
short	tcp_open_nw(u_short,u_long,u_short);
short	tcp_popen(u_short,u_long,u_short,u_short);
short	tcp_accept(short,u_long * ,u_short *); 
short	tcp_accept_nw(short,u_long * ,u_short *);
short	tcp_send(short,u_char *,short,short);
short	tcp_close(short);
short	tcp_shutdown(short);
short	tcp_send_nw(short,u_char *,short,short);
short	tcp_recv(short,u_char *,short,short);
short	tcp_recv_nw(short,u_char *,short,short);
short	tcp_getaddr(short,u_short *,u_long *,u_short * );
short	udp_open(u_short,u_long,u_short,char);
short	udp_send(short,u_long,u_short,u_char *,short);
short	udp_close(short);
#endif



/***   api_base.asm   ***/
void a_segr( struct SREGS * ); 
short a_int86x( short, union REGS * , union REGS *, struct SREGS * ); 
short a_intdos( union REGS *, union REGS *); 
short a_dos_open( char *, short, short *); 
short a_dos_close( short ); 
short a_dos_read( short, char FAR *, short,short *);
short a_dos_rewind( short );
short a_strlen( char *);
short a_strcmp( char *, char *);
char *a_strcpy( char *, char *);
short a_strncmp( char *, char *, unsigned short);
short	api_chk( void) ;
u_long	get_time(void);

extern	int	a_lock(void);
extern	int	a_unlock(void);

#ifdef __cplusplus
} /* End of extern "C" { */
#endif /* __cplusplus */
