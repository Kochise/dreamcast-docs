#define CLEARVCB(vcb) memset(&vcb, 0, sizeof(vcb))

#undef DEBUG
#undef DEBUGCALLS

#ifdef DEBUGCALLS
#define ASYNCAPPC(handle, vcbp, hasync) { 							\
	printf("asyncappc: %x . . . ", APPC_FLIPI(vcbp->hdr.opcode)); 	\
	hasync = WinAsyncAPPCEx(handle, (long) vcbp); 					\
	printf("done\n");												\
}
#else
#define ASYNCAPPC(handle, vcbp, hasync) 							\
	hasync = WinAsyncAPPCEx(handle, (long) vcbp)
#endif

#ifdef DEBUG
#define APPCDBG(x) x
#else
#define APPCDBG(x)
#endif

#define WINAPPCVERSION 0x0001

typedef union vcb_u {
	struct appc_hdr             	hdr;
    struct receive_allocate     	rcvalloc;
    struct mc_receive_and_wait  	rcvwait;
    struct tp_ended             	tpend;
	struct tp_started				tpstart;
	struct mc_allocate				allocate;
	struct mc_send_data				snddata;
	struct mc_flush					flush;
	struct mc_prepare_to_receive	torec;
	struct mc_confirm				confirm;
	struct mc_confirmed				confirmed;
	struct mc_deallocate			dealloc;
	struct mc_get_attributes		getattrib;
} vcb_t;

typedef struct tpconvid_st {
	/* TP ID and Conversation ID for read conversation */
	unsigned char				r_tp_id[8];
	unsigned long int 			r_conv_id;
	unsigned char				r_valid;
	/* TP ID and Conversation ID for write conversation */
	unsigned char				w_tp_id[8];
	unsigned long int			w_conv_id;
	unsigned char 				w_valid;
} *tpconvid_t;

// this has the fully qualified partner lu name and time used for identifing 
// incoming sessions
typedef struct name_time_st {
	unsigned char				fqplu_name[17];
	DWORD						time;
} name_time_t;

typedef struct readnode_st {
	name_time_t					name_time;
	tpconvid_t					tpconv;
} *readnode_t;

// --- error codes ---
#define APPCLIB_ERROR_BASE 0x20000000				// bit 29 is user error

#define APPCLIB_ASYNC_FAILED APPCLIB_ERROR_BASE + 0	// WinAPPCAsyncEx failed
#define APPCLIB_NO_INIT APPCLIB_ERROR_BASE + 1		// appcinit() wasn't called

// --- exported function prototypes ---
int appcinit(void);
BOOL WINAPI appcdestroy(void);
tpconvid_t appclisten(TCHAR *tpname);
tpconvid_t appcconnect(TCHAR *lu_alias, TCHAR *plu_alias, 
					   TCHAR *tp_name, TCHAR *loc_tp_name, TCHAR *mode_name);
int appcread(tpconvid_t tpconv, void *data, int maxlen);
void appcwrite(tpconvid_t tpconv, void *data, int len);
int appcvalid(tpconvid_t tpconv);
void appcclose(tpconvid_t tpconv);
