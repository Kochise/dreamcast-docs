/*=====================================================================
P I N G . C

This is the DOS side ping program.  It uses Novell's IPX/SPX APIs,
requiring their SDK. It will send/receive 1-n IPX packets.
======================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <nxtdos.h>

#define TIMER (unsigned long far *) 0x0000046cL

char *progname;
IPXHeader *ipx;
int send_socket=0;
int recv_socket;
int datasize = 1;
ECB send_ecb; 
ECB recv_ecb[10];
char mynodeaddr[6];
char sendb[2048];
char recvb[2048];

int ptype = 4;
int niters = 1;

/**
    This is the address we try to send to.  When
    we find a server, this address is replaced by the address
    of the exact server.  The address is made up of:
    bytes 1-4    = network number
    bytes 5-10   = node number
    bytes 11-12  = socket address

**/

char destaddr[12] = {
    0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x30, 0x00
};

/** Function Prototypes **/

void   hang_recvs(void);
void   cancel_recvs(void);
void   do_recv(int);
int    get_recv(void);
void   find_a_server(void);
void   print_address(char *);
void   print_network(char *);
void   print_nodeaddr(char *);
void   parse_cmd_line(int, char **);
void   swap_dwf(char *);
char * get_node_number(char * cmd);
char * get_network_number(char * cmd);
/********************************************************************
m a i n
*********************************************************************/
int main(int argc, char **argv)
{
    char *p;
    unsigned long start = *TIMER;
    unsigned long end;
    int cnt = 0;
    long sendpkt = 0L;
    long recvpkt = 0L;
    int ttime;
    float total = 0;

    progname = *argv;
    for (p = progname; *p; p++) {
    if (*p == '\\')
	progname = p + 1;
    }

    /** Make sure IPX is loaded **/

    if (IPXInitialize()) {
	printf("%s: IPX IS NOT LOADED\n", progname);
    exit(1);
    }
    recv_socket = *(short *)(destaddr + 10);
    parse_cmd_line(argc, argv);
    print_network(destaddr);
    print_nodeaddr(destaddr + 4);
    printf("packet type:    %d\n",ptype);
    printf("datasize:       %d\n", datasize);
    printf("n iterations:   %d\n", niters);    
    


    if (IPXOpenSocket(&send_socket, 0)) {
	printf("%s: ERROR: unable to open socket\n", progname);
	exit(1);
    }
    recv_socket = send_socket;
    if (IPXGetLocalTarget(destaddr, send_ecb.immediateAddress, &ttime)) {
	printf("%s: ERROR: unable to get local target\n", progname);
	exit(1);
    }

    memcpy(mynodeaddr, send_ecb.immediateAddress, 6);

    /** Go find a server **/

    find_a_server(); 
	hang_recvs();


    /** Do # iterations (default = 1) **/
	while (cnt < niters) {
	    int rcv;
	/** send a packet **/
	*(sendb + 5) = ptype;
	    memcpy(sendb + 6, destaddr, 12);
	    memcpy(send_ecb.immediateAddress, mynodeaddr, 6);
	    send_ecb.socketNumber = send_socket;
	    send_ecb.fragmentCount = 1;
	    send_ecb.fragmentDescriptor[0].address = sendb;
	    send_ecb.fragmentDescriptor[0].size = 30 + datasize;

	IPXSendPacket(&send_ecb);

	while (send_ecb.inUseFlag) /* wait for it to finish */
		;

	if (send_ecb.completionCode) {
		cancel_recvs();
			IPXCloseSocket(send_socket);
			printf("%s: Error sending packet: %d\n", progname, send_ecb.completionCode);
			exit(1);
		}

	    sendpkt++;
	    total += 30 + datasize;     /* Count the bytes */
	    printf("\rSend packet Number %d ", sendpkt);

	    if ((rcv = get_recv()) == -1)
			goto EXIT;

	    do_recv(rcv);
	    total += 30 + datasize;     /* Count the bytes */

	    cnt++;
	    recvpkt++;
	    printf(": Recv packet Number %d ", recvpkt);
	}

	/** We did 1000 packets - print KB per second **/
EXIT:
	end = *TIMER;
	end = (end - start) / 18.2; /* Num seconds it took */

	total = (float)((total / 1024.0) / end);

    /** All done - cancel recvs and exit **/
    cancel_recvs();
    IPXCloseSocket(send_socket);
    printf("\n%ld packets \n", recvpkt);
    if (recvpkt)
	printf("Average time per iteration: %5.3f\n",total/recvpkt);
    exit(0);
}

/*page**************************************************************
	h a n g _ r e c v s

	Arguments - None

	Returns - nothing
*******************************************************************/
void hang_recvs(void)
{
    int i;

    for (i = 0; i < 10; i++) {

	/** Don't hang recv on one that is already hung **/

	if (recv_ecb[i].inUseFlag)
	    continue;

	/** Hang a recv **/

	memset(&recv_ecb[i], 0, sizeof(ECB));
	recv_ecb[i].socketNumber = recv_socket;
	recv_ecb[i].fragmentCount = 1;
	recv_ecb[i].fragmentDescriptor[0].address = recvb;
	recv_ecb[i].fragmentDescriptor[0].size = 2048;
	IPXListenForPacket(&recv_ecb[i]);
    }

    /** All done **/

    return;
}

/*page**************************************************************
	c a n c e l _ r e c v s

	Arguments - None

	Returns - nothing
*******************************************************************/
void cancel_recvs(void)
{
    int i;

    for (i = 0; i < 10; i++) {

	/** If recv not in use - skip it **/

	if (!recv_ecb[i].inUseFlag)
	    continue;

	/** Cancel the recv **/

	IPXCancelEvent(&recv_ecb[i]);
    }

    /** All done **/

    return;
}

/*page**************************************************************
	d o _ r e c v

	Arguments - i = recv index to hang

	Returns - nothing
*******************************************************************/
void do_recv(int i)
{
    memset(&recv_ecb[i], 0, sizeof(ECB));
    recv_ecb[i].socketNumber = recv_socket;
    recv_ecb[i].fragmentCount = 1;
    recv_ecb[i].fragmentDescriptor[0].address = recvb;
    recv_ecb[i].fragmentDescriptor[0].size = 2048;
    IPXListenForPacket(&recv_ecb[i]);
    return;
}

/*page**************************************************************
	g e t _ r e c v

	Arguments - none

	Returns - -1 = User hit a key
		  else = recv index that was hit
*******************************************************************/
int get_recv(void)
{
    int i;

    /** **/

    while (!kbhit()) {
	for (i = 0; i < 10; i++) {
		if (!recv_ecb[i].inUseFlag)
		return i;
		}                        
//      try resending the bugger...maybe we be out of synch?..bug,bug,bug???    
    IPXSendPacket(&send_ecb);           
    }

    /** Return that user hit a key **/

    return -1;
}

/*******************************************************************
function name:      f i n d _ a _ s e r v e r
    Description:    make sure can find the machine we want to send to
    Arguments:      none
    Returns:        none
*********************************************************************/
void find_a_server(void)
{
    long start;
    long end;
    ECB send_ecb;
    ECB recv_ecb;

    /** Setup the recv ecb and listen for a packet **/

    memset(&recv_ecb, 0, sizeof(ECB));
    recv_ecb.socketNumber = recv_socket;
    recv_ecb.fragmentCount = 1;
    recv_ecb.fragmentDescriptor[0].address = recvb;
    recv_ecb.fragmentDescriptor[0].size = 31;
    IPXListenForPacket(&recv_ecb);

    memset(&send_ecb, 0, sizeof(ECB));
    memcpy(sendb + 6, destaddr, 12);
    send_ecb.socketNumber = send_socket;
    memcpy(send_ecb.immediateAddress, mynodeaddr, 6);
    send_ecb.fragmentCount = 1;
    send_ecb.fragmentDescriptor[0].address = sendb;
    send_ecb.fragmentDescriptor[0].size = 31;

    IPXSendPacket(&send_ecb);

    while (send_ecb.inUseFlag && !kbhit())
	;

    if (send_ecb.completionCode) {
	printf("%s: ERROR: send completion code 0x%02x\n", progname, send_ecb.completionCode);
	exit(1);
    }

    /** Wait awhile for the recv to pay off **/

    start = *TIMER;

    while (recv_ecb.inUseFlag && !kbhit() && (*TIMER - start) < 180L)
	;
    end = *TIMER;

    /** If we timed out - then we couldn't find a server **/

    if (end - start >= 180L) {
	IPXCancelEvent(&recv_ecb);
	IPXCloseSocket(send_socket);
	printf("%s: Unable to find a server\n", progname);
	exit(1);
    }

    /** If recv still in use - error **/

    if (recv_ecb.inUseFlag) {
	IPXCancelEvent(&recv_ecb);
	IPXCloseSocket(send_socket);
	printf("%s: Program terminated by a keystroke\n", progname);
	exit(1);
    }

    /** If recv error - clean up and exit **/

    if (recv_ecb.completionCode) {
	IPXCancelEvent(&recv_ecb);
	IPXCloseSocket(send_socket);
	printf("%s: Error receiving packet: %d\n", progname, recv_ecb.completionCode);
	exit(1);
    }

    /** Get the server address and print it out **/

    memcpy(destaddr, recvb + 18, 12);   /* Set the address to send to */
    memcpy(mynodeaddr, recv_ecb.immediateAddress, 6);
    printf("Found server: ");
    print_address(destaddr);

    /** All done **/

    return;
}

/********************************************************************
	p r i n t _ a d d r e s s

	Arguments - netaddr = ptr to 14 bytes address to print

	Returns - nothing
*********************************************************************/
void print_address(char *netaddr)
{
    int i;

    for (i = 0; i < 12; i++) {
	if ((i == 4) || (i == 10))
	    printf(" ");
	printf("%02X", (unsigned char) *(netaddr + i));
	}
    printf("\n");
    return;
}

void print_network(char *p)
{
    int i;
    printf("Network Number: ");
    for (i = 0; i < 4; i++)
	printf("%02X", (unsigned char) *p++);
    printf("\n");
    return;
}

void print_nodeaddr(char *p)
{
    int i;

    printf("Node Address:   ");
    for (i = 0; i < 6; i++)
	printf("%02X", (unsigned char) *p++);
    printf("\n");
    return;
}

/*-----------------------------------------------------------------
function name: parse_cmd_line
Description:
    Parse the command line for the parameters and host name.
Arguments:     
       -i <number of iterations>
       -p <packet type>
       -d <data size>
	  NOTE: must be < frame size - 14 (MAC length) - 30 (IPX header)
       -n <network number>
	  NOTE: you can ignore this if on the same subnet.  Must be 4 hex
		bytes
       -a <destination address>
	  NOTE: must be 6 hex bytes representing the physical NIC address of
		the remote machine.
       -s <socket>
	  Two byte socket number
Returns:        Nothing
----------------------------------------------------------------------*/
void parse_cmd_line(int argc, char **argv)
{
    short socket;

    argv++;                      /* skip to first arg */
    while (--argc) {             /* do all args */
	if (**argv == '-') {
	    ++(*argv);
	    switch(tolower(**argv)) {
		case 'i':
		    niters = atoi(++(*argv));
		    if (niters < 0) 
		       niters = 1;
		    break;   
		case 'p':
		    ptype = atoi(++(*argv));
		    if (ptype < 0 || ptype > 255) {
			ptype = 4;
			printf("%s: Invalid packet type.  Setting to default = %d\n",
			progname,ptype);
		    }
		    break;
		case 'd':  /*amount of data to send in a frame */
		    datasize = atoi(++(*argv));
		    if (!datasize) {
			datasize = 1;
			printf("%s: Datasize cannot be zero. Setting to default = 1\n", progname);
		    }
		    break;
		case 's':  /* socket number, default = 0x3000 */
		    socket = (short)strtol(++(*argv), NULL, 16);
		    printf("New socket = 0x%x\n", socket);
		    *(short *)(destaddr + 10) = socket;
		    swap_dwf(destaddr + 10);
		    break;
		case 'n':  /* network number, default = local net (= 0) */
		    ++(*argv);
		    memcpy(destaddr, get_network_number(*argv),4);
		    if (destaddr[0] == 'X') {
			printf("\n****!\n%s is an incorrect net number.\n****!\n", *argv);
			printf("%s E.G.: -nAABBCCDD (I.E.: 8 hex digits)\n");
			exit(1);
		    }
		    break;
		case 'a': /* remote address, have to know this */
		    ++(*argv);
		    memcpy(destaddr+4, get_node_number(*argv), 6);
		    if (*(destaddr+4) == 'X') {
		       printf("\n****!\n%s is an incorrect Node address.\n****!\n", *argv);
		       printf("\n E.G.: -a 023C8DAADDCC (12 hex digits)\n");
		       exit(1);
		    }
		    break;
		default:
		    printf("%s [-p] [-d] [-nxxxxxxxx] [-axxxxxxxxxxxx] [-sx]\n", progname);
		    printf("     -p - packet type\n");
		    printf("     -d - data size\n");
		    printf("     -n - network number (in hex)\n");
		    printf("     -a - address (in hex)\n");
		    printf("     -s - socket number (in hex)\n");
		    exit(0);
	    }
	    argv++;
	}
    }
    return;
}
/**********************************************************************
    g e t _ h e x _ b y t e

    Converts the character passed in to a hexadecimal nibble.

    Arguments:    char    character to convert

    Returns:      UCHAR   hex nibble
**************************************************************************/
char get_hex_byte(char ch)
{
    if (ch >= '0' && ch <= '9')
    return (ch - '0');

    if (ch >= 'A' && ch <= 'F')
    return ((ch - 'A') + 0x0A);

    return -1;
}
/**********************************************************************
    g e t _ h e x _ s t r i n g

    Reads in a character string containing hex digits and converts
    it to a hexadecimal number.

    Arguments:    src   => source string to convert
		  dest  => destination for hex number
		  num   => number of chars to convert

    Returns:      nothing
**************************************************************************/
char get_hex_string(char * src, char * dest, int num)
{
    char *   q = src;
    char     hexbyte1,hexbyte2;

    strupr(q);
    while (num--)
      {hexbyte1 = get_hex_byte(*q++);
       hexbyte2 = get_hex_byte(*q++);
       if ( (hexbyte1 < 0) || (hexbyte2 < 0) )
      return -1;
       *dest++ = (hexbyte1 << 4) + hexbyte2;
      }

    return(0);
}
/*************************************************************************
    g e t _ n o d e _ n u m b e r

    Reads a node number from the given string.

    Arguments:    cmd  => string to read from

    Returns:      hex node number
**************************************************************************/
char * get_node_number(char * cmd)
{
    static char hex_num[6];

    memset(hex_num, 0, 6);

    if (strlen(cmd) != 12){
    hex_num[0] = 'X';
    return hex_num;
       }

    if (get_hex_string(cmd, hex_num, 6) < 0)
    hex_num[0] = 'X';
    return hex_num;
}
/**************************************************************************
    g e t _ n e t w o k _ n u m b e r

    Reads a network number from the given string.

    Arguments:    cmd   string to read from

    Returns:      hex network number
**************************************************************************/
char * get_network_number(char * cmd)
{
    static char hex_num[4];

    memset(hex_num, 0, 4);

    if (strlen(cmd) != 8) {
    hex_num[0] = 'X';
    return(hex_num);
    }

    if (get_hex_string(cmd, hex_num, 4) < 0)
    hex_num[0] = 'X';

    return hex_num;
}
/*******************************************************************
	s w a p _ d w f

	Swap the bytes pointed to by p.

	Arguments - p = ptr to word to swap

	Returns - nothing
********************************************************************/
void swap_dwf(char *p)
{
    char tmp;

    tmp = *p;
    *p = *(p + 1);
    *(p + 1) = tmp;
    return;
}
