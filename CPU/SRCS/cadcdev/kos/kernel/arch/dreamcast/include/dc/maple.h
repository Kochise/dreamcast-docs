/* KallistiOS ##version##

   kernel/arch/dreamcast/include/dc/maple.h
   (C)2002 Dan Potter

   $Id: maple.h,v 1.10 2003/04/24 03:14:47 bardtx Exp $

   This new driver's design is based loosely on the LinuxDC maple
   bus driver.
*/

#ifndef __DC_MAPLE_H
#define __DC_MAPLE_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>
#include <sys/queue.h>

/* Enabling this line will add massive amounts of processing time
   to the maple system, but it can verify DMA errors */
#define MAPLE_DMA_DEBUG	0

/* Enabling this will turn on intra-interrupt debugging messages, which
   can cause problems if you're using a dc-load console rather than raw
   serial output. Disable for normal usage. */
#define MAPLE_IRQ_DEBUG 0

/* Maple Bus registers */
#define MAPLE_BASE	0xa05f6c00
#define MAPLE_DMAADDR	(MAPLE_BASE+0x04)
#define MAPLE_RESET2	(MAPLE_BASE+0x10)
#define MAPLE_ENABLE	(MAPLE_BASE+0x14)
#define MAPLE_STATE	(MAPLE_BASE+0x18)
#define MAPLE_SPEED	(MAPLE_BASE+0x80)
#define MAPLE_RESET1	(MAPLE_BASE+0x8c)

/* Some register define values */
#define MAPLE_RESET2_MAGIC	0
#define MAPLE_ENABLE_ENABLED	1
#define MAPLE_ENABLE_DISABLED	0
#define MAPLE_STATE_IDLE	0
#define MAPLE_STATE_DMA		1
#define MAPLE_SPEED_2MBPS	0
#define MAPLE_SPEED_TIMEOUT(n)	((n) << 16)
#define MAPLE_RESET1_MAGIC	0x6155404f

/* Command and response codes */
#define MAPLE_RESPONSE_FILEERR		-5
#define MAPLE_RESPONSE_AGAIN 		-4
#define MAPLE_RESPONSE_BADCMD		-3
#define MAPLE_RESPONSE_BADFUNC		-2
#define MAPLE_RESPONSE_NONE		-1
#define MAPLE_COMMAND_DEVINFO		1
#define MAPLE_COMMAND_ALLINFO		2
#define MAPLE_COMMAND_RESET		3
#define MAPLE_COMMAND_KILL		4
#define MAPLE_RESPONSE_DEVINFO		5
#define MAPLE_RESPONSE_ALLINFO		6
#define MAPLE_RESPONSE_OK		7
#define MAPLE_RESPONSE_DATATRF		8
#define MAPLE_COMMAND_GETCOND		9
#define MAPLE_COMMAND_GETMINFO		10
#define MAPLE_COMMAND_BREAD		11
#define MAPLE_COMMAND_BWRITE		12
#define MAPLE_COMMAND_BSYNC		13
#define MAPLE_COMMAND_SETCOND		14
#define MAPLE_COMMAND_MICCONTROL    15

/* Function codes; most sources claim that these numbers are little
   endian, and for all I know, they might be; but since it's a bitmask
   it doesn't really make much different. We'll just reverse our constants
   from the "big-endian" version. */
#define MAPLE_FUNC_PURUPURU		0x00010000
#define MAPLE_FUNC_MOUSE		0x00020000
#define MAPLE_FUNC_CAMERA		0x00080000
#define MAPLE_FUNC_CONTROLLER		0x01000000
#define MAPLE_FUNC_MEMCARD		0x02000000
#define MAPLE_FUNC_LCD			0x04000000
#define MAPLE_FUNC_CLOCK		0x08000000
#define MAPLE_FUNC_MICROPHONE		0x10000000
#define MAPLE_FUNC_ARGUN		0x20000000
#define MAPLE_FUNC_KEYBOARD		0x40000000
#define MAPLE_FUNC_LIGHTGUN		0x80000000

/* Pre-define list/queue types */
struct maple_frame;
TAILQ_HEAD(maple_frame_queue, maple_frame);

struct maple_driver;
LIST_HEAD(maple_driver_list, maple_driver);

/* Maple frame to be queued for transport */
typedef struct maple_frame {
	/* Send queue handle */
	TAILQ_ENTRY(maple_frame)	frameq;

	int	cmd;			/* Command (defined above) */
	int	dst_port, dst_unit;	/* Maple destination address */
	int	length;			/* Data transfer length in 32-bit words */
	volatile int	state;			/* Has this frame been sent / responded to? */
	volatile int	queued;			/* Are we on the queue? */

	void	*send_buf;		/* The data which will be sent (if any) */
	uint8	*recv_buf;		/* Points into recv_buf_arr, but 32-byte aligned */

	struct maple_device	*dev;	/* Does this belong to a device? */

	void	(*callback)(struct maple_frame *);	/* Response callback */

#if MAPLE_DMA_DEBUG
	uint8	recv_buf_arr[1024 + 1024 + 32];		/* Response receive area */
#else
	uint8	recv_buf_arr[1024 + 32];		/* Response receive area */
#endif
} maple_frame_t;

#define MAPLE_FRAME_VACANT	0	/* Ready to be used */
#define MAPLE_FRAME_UNSENT	1	/* Ready to be sent */
#define MAPLE_FRAME_SENT	2	/* Frame has been sent, but no response yet */
#define MAPLE_FRAME_RESPONDED	3	/* Frame has a response */

/* Maple device info structure (used by hardware) */
typedef struct maple_devinfo {
	uint32		functions;
	uint32		function_data[3];
	uint8		area_code;
	uint8		connector_direction;
	char		product_name[30];
	char		product_license[60];
	uint16		standby_power;
	uint16		max_power;
} maple_devinfo_t;

/* Response frame structure (used by hardware) */
typedef struct maple_response {
	int8		response;		/* Response */
	uint8		dst_addr;		/* Destination address */
	uint8		src_addr;		/* Source address */
	uint8		data_len;		/* Data length (in 32-bit words) */
	uint8		data[0];		/* Data (if any) */
} maple_response_t;

/* One maple device; note that we duplicate the port/unit info which
   is normally somewhat implicit so that we can pass around a pointer
   to a particular device struct. */
typedef struct maple_device {
	/* Public */
	int			valid;		/* Is this a valid device? */
	int			port, unit;	/* Maple address */
	maple_devinfo_t		info;		/* Device info struct */

	/* Private */
	int			dev_mask;	/* Device-present mask for unit 0's */
	maple_frame_t		frame;		/* Give each device one rx/tx frame */
	struct maple_driver *	drv;		/* Driver which handles this device */

	volatile int		status_valid;	/* Have we got our first status update? */
	uint8			status[1024];	/* Status buffer (for pollable devices) */
} maple_device_t;

/* One maple port; each maple port can contain up to 6 devices, the first
   one of which is always the port itself. */
#define MAPLE_PORT_COUNT	4
#define MAPLE_UNIT_COUNT	6
typedef struct maple_port {
	int		port;				/* Port ID */
	maple_device_t	units[MAPLE_UNIT_COUNT];	/* Pointers to active units */
} maple_port_t;

/* A maple device driver; anything which is added to this list is capable
   of handling one or more maple device types. When a device of the given
   type is connected (includes startup "connection"), the driver is
   invoked. This same process happens for disconnection, response
   receipt, and on a periodic interval (for normal updates). */
typedef struct maple_driver {
	/* Driver list handle */
	LIST_ENTRY(maple_driver)	drv_list;

	uint32		functions;	/* One or more MAPLE_FUNC_* or'd together */
	const char *	name;		/* The driver name */

	/* Callbacks, to be filled in by the driver */
	void	(*periodic)(struct maple_driver *drv);
	int	(*attach)(struct maple_driver *drv, maple_device_t *dev);
	void	(*detach)(struct maple_driver *drv, maple_device_t *dev);
} maple_driver_t;

/* Maple state structure; we put everything in here to keep from
   polluting the global namespace too much */
typedef struct maple_state_str {
	/* Maple device driver list; NOTE: Do not manipulate directly */
	struct maple_driver_list	driver_list;

	/* Maple frame submission queue; NOTE: Do not manipulate directly */
	struct maple_frame_queue	frame_queue;

	/* Maple device info structure */
	maple_port_t			ports[MAPLE_PORT_COUNT];

	/* Interrupt counters */
	volatile int			dma_cntr, vbl_cntr;

	/* DMA send buffer */
	uint8				*dma_buffer;
	volatile int			dma_in_progress;

	/* Next unit which will be auto-detected */
	int				detect_port_next;
	int				detect_unit_next;
	volatile int			detect_wrapped;

	/* Our vblank handler handle */
	int				vbl_handle;
} maple_state_t;

/* Maple DMA buffer size; increase if you do a _LOT_ of maple stuff
   on every periodic interrupt */
#define MAPLE_DMA_SIZE 16384

/* Maple memory read/write functions; these are just hooks in case
   we need to do something else later */
#define maple_read(A) ( *((vuint32*)(A)) )
#define maple_write(A, V) ( *((vuint32*)(A)) = (V) )

/* Return codes from maple access functions */
#define MAPLE_EOK	0
#define MAPLE_EFAIL	-1
#define MAPLE_EAGAIN	-2
#define MAPLE_EINVALID	-3
#define MAPLE_ENOTSUPP	-4
#define MAPLE_ETIMEOUT	-5

/**************************************************************************/
/* maple_globals.c */

/* Global state info */
extern maple_state_t maple_state;

/**************************************************************************/
/* maple_utils.c */

/* Enable / Disable the bus */
void maple_bus_enable();
void maple_bus_disable();

/* Start / Stop DMA */
void maple_dma_start();
void maple_dma_stop();
int maple_dma_in_progress();

/* Set DMA address */
void maple_dma_addr(void *ptr);

/* Return a "maple address" for a port,unit pair */
uint8 maple_addr(int port, int unit);

/* Decompose a "maple address" into a port,unit pair */
/* WARNING: Won't work on multi-cast addresses! */
void maple_raddr(uint8 addr, int * port, int * unit);

/* Return a string with the capabilities of a given driver; NOT THREAD SAFE */
const char * maple_pcaps(uint32 functions);

/* Return a string representing the maple response code */
const char * maple_perror(int response);

/* Determine if a given device is valid */
int maple_dev_valid(int p, int u);

#if MAPLE_DMA_DEBUG
/* Debugging help */
void maple_sentinel_setup(void * buffer, int bufsize);
void maple_sentinel_verify(const char * bufname, void * buffer, int bufsize);
#endif

/**************************************************************************/
/* maple_queue.c */

/* Send all queued frames */
void maple_queue_flush();

/* Submit a frame for queueing; this will generally be called inside the
   periodic interrupt; however, if you need to do something asynchronously
   (e.g., VMU access) then it might cause some problems. In this case, the
   function will automatically do locking by disabling interrupts 
   temporarily. In any case, the callback will be done inside an IRQ context. */
int maple_queue_frame(maple_frame_t *frame);

/* Remove a used frame from the queue; same semantics as above */
int maple_queue_remove(maple_frame_t *frame);

/* Initialize a new frame to prepare it to be placed on the queue; call
   this _before_ you fill it in */
void maple_frame_init(maple_frame_t *frame);

/* Lock a frame so that someone else can't use it in the mean time; if the
   frame is already locked, an error will be returned. */
int maple_frame_lock(maple_frame_t *frame);

/* Unlock a frame */
void maple_frame_unlock(maple_frame_t *frame);

/**************************************************************************/
/* maple_driver.c */

/* Register a maple device driver; do this before maple_init() */
int maple_driver_reg(maple_driver_t *driver);

/* Unregister a maple device driver */
int maple_driver_unreg(maple_driver_t *driver);

/* Attach a maple device to a driver, if possible */
int maple_driver_attach(maple_frame_t *det);

/* Detach an attached maple device */
int maple_driver_detach(int p, int u);

/* For each device which the given driver controls, call the callback */
int maple_driver_foreach(maple_driver_t *drv, int (*callback)(maple_device_t *));

/**************************************************************************/
/* maple_irq.c */

/* Called on every VBL (~60fps) */
void maple_vbl_irq_hnd(uint32 code);

/* Called after a Maple DMA send / receive pair completes */
void maple_dma_irq_hnd(uint32 code);

/**************************************************************************/
/* maple_enum.c */

/* Return the number of connected devices */
int maple_enum_count();

/* Return a raw device info struct for the given device */
maple_device_t * maple_enum_dev(int p, int u);

/* Return the Nth device of the requested type (where N is zero-indexed) */
maple_device_t * maple_enum_type(int n, uint32 func);

/* Get the status struct for the requested maple device; wait until it's
   valid before returning. Cast to the appropriate type you're expecting. */
void * maple_dev_status(maple_device_t *dev);

/**************************************************************************/
/* maple_compat.h */

/* Utility function used by other compat functions */
int maple_compat_resolve(uint8 addr, maple_device_t **dev, uint32 funcs);

/* Retrieve function code... */
uint32 maple_device_func(int port, int unit);

/* First with a given function code... */
uint8 maple_first_device(int code);

/* First controller */
uint8 maple_first_controller();

/* First mouse */
uint8 maple_first_mouse();

/* First keyboard */
uint8 maple_first_kb();

/* First LCD unit */
uint8 maple_first_lcd();

/* First VMU */ 
uint8 maple_first_vmu();

/* NOP now */
#define maple_rescan_bus(Q)	/* NADA */

/* Renamed */
#define maple_create_addr(A, B) maple_addr(A, B)

/**************************************************************************/
/* maple_init.c */

/* Init / Shutdown */
int	maple_init();
void	maple_shutdown();

/* Wait for the initial bus scan to complete */
void	maple_wait_scan();

/**************************************************************************/
/* Convienence macros */

/* A "foreach" loop to scan all maple devices of a given type. It is used
   like this:

   MAPLE_FOREACH_BEGIN(MAPLE_FUNC_CONTROLLER, cont_state_t, st)
   	if (st->buttons & CONT_START)
   		return -1;
   MAPLE_FOREACH_END()

   The peripheral index can be obtained with __i, and the raw device struct
   with __dev. The code inside the loop is guaranteed to be inside a block
   (i.e., { code })
 */

#define MAPLE_FOREACH_BEGIN(TYPE, VARTYPE, VAR) \
do { \
	maple_device_t	* __dev; \
	VARTYPE * VAR; \
	int	__i; \
\
	__i = 0; \
	while ( (__dev = maple_enum_type(__i, TYPE)) ) { \
		VAR = (VARTYPE *)maple_dev_status(__dev); \
		do {
		
#define MAPLE_FOREACH_END() \
		} while(0); \
		__i++; \
	} \
} while(0);
	

__END_DECLS

#endif /* __DC_MAPLE_H */

