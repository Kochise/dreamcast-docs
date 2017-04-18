
/*****************************************************************************
 *
 *   (C) Copyright MICROSOFT Corp., 1988-1990
 *
 *   Title:     PERF.H - Include file for perf monitor
 *
 *   Version:   1.00
 *
 *   Date:
 *
 *   Author:	FCF
 *
 *-----------------------------------------------------------------------------
 *
 *   Change log:
 *
 *   DATE        REV DESCRIPTION
 *   ----------- --- -----------------------------------------------------------
 */

/*  See dos\dos386\vxd\perf\example for a sample VxD that registers as */
/*  a perf server.                                                     */

/* defines */

#define MAXNAMELEN			50	/* maximum number of characters in
								   service name, stat name, or key names */
#define MAXCOMPLEXSUBSTAT	8	/* maximum number of stats making
								   up a complex stat */
	
/* structures and flags used for the ring-0 interface */

struct perf_server_0 {
    unsigned long	psrv0_Level;	/* Must be zero for this level */
    unsigned long	psrv0_Flags;
    char 	       *psrv0_pszServerName;
    char	       *psrv0_pszServerNodeName;
    void	       *psrv0_pControlFunc;
};

struct perf_stat_0 {
    unsigned long	pst0_Level;	/* Must be zero for this level */
    unsigned long	pst0_Flags;
    char	       *pst0_pszStatName;
    char	       *pst0_pszStatNodeName;
    char	       *pst0_pszStatUnitName;
    char	       *pst0_pszStatDescription;
    void	       *pst0_pStatFunc;
};

/* Values for psrv0_Flags follow */

/* Values for pst0_Flags follow */

/* pst0_pStatFunc points either directly to data (always a DWORD for now) */
/* or, if PSTF_FUNCPTR_BIT is set, to a _cdecl function.  This function   */
/* accepts a stat handle as it's argument and returns the stat in eax     */

#define PSTF_FUNCPTR		0x00000001

/* The data referenced by this stat is always a counter, e.g. number of   */
/* bytes read.  It is up to the client to differentiate this into a rate. */
/* If PSTF_RATE is set, then the text associated with this stat assumes   */
/* that the stat will be differentiated with respect to time.  It's 	  */
/* possible that two stats will refer to the same data - one with this    */
/* bit set and one without, with help text appropriate for each.          */

#define PSTF_COUNT		0x00000000
#define PSTF_RATE		0x00000002

/* A recommendation as to the frequency of update.  Bytes read/second     */
/* can change quite rapidly, but updating # of shares will not change     */
/* as often, and (currently) vcache cache size is static.  Perf clients   */
/* are free to ignore these values, and free to define update frequency.  */

#define PSTF_FREQ_HIGH		0x00000000
#define PSTF_FREQ_LOW		0x00000004
#define PSTF_FREQ_STATIC	0x00000008
#define PSTF_FREQ_MASK		(PSTF_FREQ_STATIC | PSTF_FREQ_LOW |	\
				 PSTF_FREQ_HIGH)


/* A recommendation as to the scale type.  Bytes read/second may be more  */
/* appropriately displayed on a log10 scale, while memory available might */
/* be better on a linear scale.  Perf clients are free to ignore this.    */

#define PSTF_SCALE_LINEAR	0x00000000
#define PSTF_SCALE_LOG10	0x00000010
#define PSTF_SCALE_LOG2		0x00000020
#define PSTF_SCALE_MASK		(PSTF_SCALE_LINEAR | PSTF_SCALE_LOG10 | \
				 PSTF_SCALE_LOG2)

/* XLATOFF */

unsigned long PERF_Server_Register( struct perf_server_0 * );
void PERF_Server_Deregister( unsigned long hReg );
unsigned long PERF_Server_Add_Stat( unsigned long hReg, struct perf_stat_0 );
void PERF_Server_Remove_Stat( unsigned long hStat );

/* XLATON */

/* Control messages sent to perf server's control function.  The control */
/* function is optional, set it to NULL if you don't want any control    */
/* messages.  Perf servers are free to ignore any messages they want.    */
/* Control functions take two DWORD parameters; a message (dwMsg) and a  */
/* DWORD of message-dependent data (dwData). 							 */

/* The following defines are values for dwMsg:							 */
#define PMSG_START_STAT				0x11
#define PMSG_STOP_STAT				0x12

/* PMSG_START_STAT: Notifies that a perf client is going to start        */
/*     watching this stat.  dwData contains the stat handle.             */
/* PMSG_STOP_STAT: Notifies that a perf client is no longer              */
/*     watching this stat.  dwData contains the stat handle.             */
/* Stats which are expensive to maintain should only be kept while some- */
/* one is watching them.  Note that there can be more than one stat      */
/* client, so don't just stop keeping track of a stat if you receive     */
/* a PMSG_STOP_STAT.  The server should keep a counter of the number     */
/* of PMSG_START_STAT's it receives for a particular counter, decrement  */
/* it for each PMSG_STOP_STAT and stop keeping track of the stat when the*/
/* counter reaches zero.                                                 */
/* Most stats are trivial to maintain and just involve incrementing a    */
/* counter.  For stats like these, perf servers should always increment  */
/* the counter and ignore messages to start and stop.                    */


/* IOCTL apis understood by perf (from ring 3 client) */

#define IOCTL_PERF_GET_STATS		0x10
#define IOCTL_PERF_START_STAT		0x11
#define IOCTL_PERF_STOP_STAT		0x12
/* On entry to the IOCTL_PERF_GET_STATS ioctl:
    lpvInBuffer 	pointer to array of DWORD stat handles
    cbInBuffer		size of array, in bytes
    lpvOutBuffer	pointer to result array (can be same as lpvInBuffer)
    cbOutBuffer		size of destination array
*/

/* ASM

; Ring-0 macros to aid stat registration

Reg_Perf_Srv MACRO level:REQ, flags:REQ, servername:REQ, nodename:REQ, controlfunc:REQ
	local	nothere
	VxDcall	PERF_Get_Version
	or	eax, eax
	jz	nothere

	IF (OPATTR(controlfunc)) AND 00010000y 	;; register
		push	controlfunc
	ELSE
		push	OFFSET32 controlfunc
	ENDIF

	IF (OPATTR(nodename)) AND 00010000y		;; register
		push	nodename
	ELSE
		push	OFFSET32 nodename
	ENDIF

	IF (OPATTR(servername)) AND 00010000y		;; register
		push	servername
	ELSE
		push	OFFSET32 servername
	ENDIF
	
	push	flags
        push	level
	push	esp
	VxDcall	PERF_Server_Register
	add	esp, 6*4
nothere:
	ENDM

Reg_Perf_Stat MACRO srvhandle:REQ, level:REQ, flags:REQ, name:REQ, nodename:REQ, unitname:REQ, desc:REQ, func:REQ
	IF (OPATTR(func)) AND 00010000y		;; register
		push	func
	ELSE
		push	OFFSET32 func
	ENDIF

	IF (OPATTR(desc)) AND 00010000y		;; register
		push	desc
	ELSE
		push	OFFSET32 desc
	ENDIF

	IF (OPATTR(unitname)) AND 00010000y	;; register
		push	unitname
	ELSE
		push	OFFSET32 unitname
	ENDIF

	IF (OPATTR(nodename)) AND 00010000y	;; register
		push	nodename
	ELSE
		push	OFFSET32 nodename
	ENDIF

	IF (OPATTR(name)) AND 00010000y		;; register
		push	name
	ELSE
		push	OFFSET32 name
	ENDIF
	
	push	flags
	push	level
	push	esp
	push	srvhandle
	VxDcall	PERF_Server_Add_Stat
	add	esp, 9*4
	ENDM

Begin_Service_Table PERF
PERF_Service PERF_Get_Version, LOCAL
PERF_Service PERF_Server_Register, LOCAL
PERF_Service PERF_Server_Deregister, LOCAL
PERF_Service PERF_Server_Add_Stat, LOCAL
PERF_Service PERF_Server_Remove_Stat, LOCAL
End_Service_Table PERF

*/

/* Registry constants follow.  A sample perf registry tree might look like
   this:

HKEY_LOCAL_MACHINE\STATS\VFAT			
			  NAME="32-bit file system"
			     \READS
		       +---    NAME="Reads per second"
		       |       HANDLE=<4 byte binary value>
	      Required |       DESCRIPTION="The number of file read requests
		       |                    per second"
		       |       VALUE=<some dynamic registry identifier>
		       +---    DIFFERENTIATE="TRUE"

		       +---    MIBID="1.3.4.7.3"
		       |       STARTSCALE=1000
	      Optional |       FREQUENCY="HIGH"
		       +---    SCALETYPE="LOG10"

*/

#define HKEY_PERF_ROOT			HKEY_LOCAL_MACHINE
#define PERF_REG_KEY			"STATS"
#define PERF_REG_NAME_SRV_NAME		"NAME"
#define PERF_REG_NAME_STAT_NAME		"NAME"
#define PERF_REG_NAME_STAT_FREQ		"FREQUENCY"
#define PERF_REG_NAME_STAT_HANDLE	"HANDLE"
#define PERF_REG_NAME_STAT_DESC		"DESCRIPTION"
#define PERF_REG_NAME_STAT_VALUE	"VALUE"
#define PERF_REG_NAME_STAT_DIFF		"DIFFERENTIATE"
#define PERF_REG_NAME_STAT_SCALETYPE	"SCALETYPE"
#define PERF_REG_NAME_STAT_STARTSCALE	"STARTSCALE"

#define PERF_REG_VAL_STAT_TRUE		"TRUE"
#define PERF_REG_VAL_STAT_FALSE		"FALSE"
#define PERF_REG_VAL_STAT_HIGH		"HIGH"
#define PERF_REG_VAL_STAT_LOW		"LOW"
#define PERF_REG_VAL_STAT_LINEAR	"LINEAR"
#define PERF_REG_VAL_STAT_LOG10		"LOG10"
#define PERF_STAT_PREFIX			"STAT"

/* complex stat defines */

#define PSTF_INT_COMPLEX	0x00000010
#define PSTF_EXT_COMPLEX	0x00000020
/* A complex statistic has no data value of its own-- it just defines two */
/* or more regular stats that may be added together to appear as a single */
/* value in the UI.  For example: VFAT->bytes written/sec and VFAT->bytes */
/* read/sec are simplex (normal) stats that each have a data counter.     */
/* VFAT->total bytes/sec is a complex stat made up of those two simplex   */
/* stats.  When the UI wants to display a complex stat's value, it gets   */
/* the data value for the simplex stats contained in it and adds those    */
/* values together.  To define a complex stat, set either PSTF_INT_COMPLEX*/
/* or PSTF_EXT_COMPLEX when registering the stat.  The pst0_pStatFunc     */
/* member should be set to point at a table of pointers to strings        */
/* containing the registry key names of the simplex stats.  The pointer   */
/* table should be null-terminated.  If PSTF_INT_COMPLEX is set, all	  */
/* stats must be internal to the VxD.  If PST_EXT_COMPLEX, the stats can  */
/* be from other VxDs (including the one registering the complex stat).   */
/* For internal complex stats, the key names in the table are the same	  */
/* as the key names used to register the stat.  For example: VFAT         */
/* registers itself with the "VFAT" key name, and registers two simple    */
/* stats with "BReadSec" and "BWriteSec" key names.  It then registers a  */
/* complex stat with a "BTotSec" key name, where the pst0_pStatFunc		  */
/* points to a table of pointers; the first pointer would point to        */
/* "BReadSec", the next pointer in the table would point to "BWriteSec",  */
/* and the next pointer would be NULL to signifiy the end of the list.    */
/* This is convenient because the "BReadSec" string already exists.  If   */
/* PSTF_EXT_COMPLEX is set, the strings that the pointer table points to  */
/* also have to contain the registry key name of the VxD which registered */
/* them.  In the above example, if VFAT were to set the PSTF_EXT_COMPLEX  */
/* flag the strings pointed to by the table would have to be              */
/* "VFAT\BReadSec" and "VFAT\BWriteSec".  The advantage of setting this   */
/* flag is that you can specify external stats, like "NDIS\PacketsSec".   */

/* This is complicated to explain, but very easy to do.                   */
/* See dos\dos386\vxd\perf\example\example.asm for an example of how to   */
/* register a complex stat.                                               */
