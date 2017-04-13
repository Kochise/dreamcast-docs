#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winappc.h>
#include <wincsv.h>
#include "appclib.h"
#include "queue.h"

#define memalloc(size) LocalAlloc(LMEM_FIXED, size)
#define memfree(pointer) LocalFree(pointer)

// --- internal functions used by the module ---
void appcerror(vcb_t vcb);
BOOL callappc(vcb_t *vcb);
void conv_a_to_e(char *string, int length);
void memcpypad(char *dest, TCHAR *source, int length);
void memcpya2e(char *dest, TCHAR *source, int length);
int do_receive_and_wait(char *tp_id, unsigned long int conv_id,
					    void *data, int maxlen, BOOL *dealloc); 
void do_send_data(char *tp_id, unsigned long int conv_id, void *data, int len);
void do_confirm(char *tp_id, unsigned long int conv_id);
void do_prepare_to_receive(char *tp_id, unsigned long int conv_id);
void do_get_fqplu_name(char *tp_id, unsigned long int conv_id, 
					   char *fqplu_name);
void do_tp_started(TCHAR *lu_alias, TCHAR *tp_name, char *tp_id);
unsigned long int do_mc_allocate(TCHAR *lu_alias, TCHAR *tp_name, 
							     TCHAR *mode_name, char *tp_id);
void do_deallocate(char *tp_id, unsigned long int conv_id);
void do_tp_ended(char *tp_id);

queue       *pairq;                     // queue of sessions that have
                                        // both read and write established
HANDLE      hPairqSem;                  // semaphore of number of objects
                                        // in pairq;
HANDLE      hListenThread = NULL;       // handle to listenthread()
HANDLE		hShutdownEvent = NULL;		// event to signal that the application
										// is shutting down
int			outstanding;				// number of outstanding APPC reqs
HANDLE		hOutstandingZero = NULL;	// event set when outstanding goes to
										// zero
CRITICAL_SECTION    csPairq;            // critical section for pairq

/*
 * convert string from ascii to ebcdic (overwriting the original string).
 */
void conv_a_to_e(char *string, int length) {
    struct convert cnvt;

    memset(&cnvt, 0, sizeof(cnvt));
    cnvt.opcode = SV_CONVERT;
    cnvt.direction = SV_ASCII_TO_EBCDIC;
    cnvt.char_set = SV_AE;
    cnvt.len = length;
    cnvt.source = string;
    cnvt.target = string;

    ACSSVC_C((long) &cnvt);
}

/*
 * copy a string from <source> to <dest>, padding the end of it with spaces so
 * it takes <length> bytes.
 *
 * input is assumed to be Unicode if UNICODE is defined, output is always Ansi
 */
void memcpypad(char *dest, TCHAR *source, int length) {
#ifdef UNICODE
    char ansisrc[1024];

    // convert the source string from Unicode to ANSI
    wcstombs(ansisrc, source, 1024);

    // copy the ANSI string into the destination
    memset(dest, ' ', length);
    memcpy(dest, ansisrc, strlen(ansisrc));
#else
    memset(dest, ' ', length);
    memcpy(dest, source, strlen(source));
#endif
}

/*
 * copy a string from <source> to <dest>, padding the end of it with spaces 
 * so it takes <length> bytes.  convert the <dest> string from ascii to ebcdic
 *
 * input is assumed to be Unicode if UNICODE is defined, output is always Ansi
 */
void memcpya2e(char *dest, TCHAR *source, int length) {
#ifdef UNICODE
    char ansisrc[1024];

    // convert the source string from Unicode to ANSI
    wcstombs(ansisrc, source, 1024);

    // copy the ANSI string into the destination
    memset(dest, ' ', length);
    memcpy(dest, ansisrc, strlen(ansisrc));

    // convert ansi to ebcdic
    conv_a_to_e(dest, length);
#else
    memset(dest, ' ', length);
    memcpy(dest, source, strlen(source));
    conv_a_to_e(dest, length);
#endif
}

/*
 * a standard error handler for APPC errors.  prints out the last verb and the
 * two return codes
 */
void appcerror(vcb_t vcb) {
    char errorbuf[1024];

    printf("\nAPPC Error: Verb = 0x%0x   PriRC = 0x%0x   SecRC = 0x%0x\n",
        APPC_FLIPI(vcb.hdr.opcode), APPC_FLIPI(vcb.hdr.primary_rc), 
        APPC_FLIPL(vcb.hdr.secondary_rc));

    GetAppcReturnCode((struct appc_hdr *) &(vcb.hdr), 1024, errorbuf);

    printf("\n%s\n", errorbuf);

	appcdestroy();

    ExitProcess(1);
}

/*
 * initialize APPC.  all programs should call this before using any 
 * APPC functions
 */
int appcinit(void) {
    WAPPCDATA APPCData;

	// create the shutdown event
	hShutdownEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (hShutdownEvent == NULL) return -1;

	// create the event that is triggered when outstanding goes to zero
	// this only gets set when hShutdownEvent has been set and all requests
	// are being cancelled
	hOutstandingZero = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (hOutstandingZero == NULL) return -1;

    return WinAPPCStartup(WINAPPCVERSION, &APPCData);
}

/*
 * kill APPC.  this should be called when a program is done using APPC
 */
BOOL WINAPI appcdestroy(void) {
	// if there are any outstanding requests
	if (outstanding > 0) {
		// tell all threads to cancel their outstanding requests.  when the last
		// one cancels its request it will set hOutstandingZero.
		SetEvent(hShutdownEvent);
		// wait up to 60 seconds for all outstanding requests to be canceled
		while 
			((WaitForSingleObject(hOutstandingZero, 20000) == WAIT_OBJECT_0) &&
			 (outstanding > 0));
	}

	// tell WinAPPC that we're done with it
    return WinAPPCCleanup();
}

// a wrapper around APPC which handles hShutdownEvent for clean shutdowns
BOOL callappc(vcb_t *vcb) {
	HANDLE hAsync, objs[2];
	DWORD event;

	// create an event handle
	objs[0] = CreateEvent(NULL, FALSE, FALSE, NULL);

	InterlockedIncrement(&outstanding);

	// make the APPC call
	ASYNCAPPC(objs[0], vcb, hAsync);
	// see if the async APPC call failed
	if (hAsync == 0) {
		InterlockedDecrement(&outstanding);
		SetLastError(APPCLIB_ASYNC_FAILED);
		return FALSE;
	}

	// wait for either the APPC call to complete or the hShutdownEvent to be
	// triggered
	objs[1] = hShutdownEvent;
	event = WaitForMultipleObjects(2, objs, FALSE, INFINITE) - WAIT_OBJECT_0;
	switch (event) {
		case 0:							// APPC call completed
			InterlockedDecrement(&outstanding);
			break;
		case 1:							// shutdown event triggered
			// cancel the outstanding request
			WinAPPCCancelAsyncRequest(hAsync);
			// if this is the last cancel than let appcdestroy() know that
			if (InterlockedDecrement(&outstanding) <= 0) {
				SetEvent(hOutstandingZero);
			}
			break;
		case WAIT_FAILED:
			SetLastError(APPCLIB_NO_INIT);
			return FALSE;
	}
	CloseHandle(objs[0]);
	CloseHandle(hAsync);

	return TRUE;
}

/*
 * execute a MC_RECEIVE_AND_WAIT verb with the given TP ID and Conversation ID
 * data is copied into the buffer at <data> for a maximum of <maxlen> bytes.  
 * Returns the number of bytes actually read.
 *
 * If the sender requests confirmation a MC_CONFIRM verb is send to them.
 * if the conversation gets deallocated then dealloc is set to true.
 */
int do_receive_and_wait(char *tp_id, unsigned long int conv_id, 
                        void *data, int maxlen, BOOL *dealloc) {
    vcb_t vcb;
    int read;

    CLEARVCB(vcb);

    *dealloc = FALSE;

    vcb.rcvwait.opcode = AP_M_RECEIVE_AND_WAIT;
    vcb.rcvwait.opext = AP_MAPPED_CONVERSATION;
    memcpy(&(vcb.rcvwait.tp_id), tp_id, 8);
    vcb.rcvwait.conv_id = conv_id;
    vcb.rcvwait.rtn_status = AP_YES;
    vcb.rcvwait.max_len = maxlen;
    vcb.rcvwait.dptr = data;

    callappc(&vcb);                                         
    APPCDBG(printf("vcb.rcvwait.what_rcvd = 0x%x\n", APPC_FLIPI(vcb.rcvwait.what_rcvd)));
    APPCDBG(printf("vcb.rcvwait.primary_rc = 0x%x\n", APPC_FLIPI(vcb.rcvwait.primary_rc)));
    APPCDBG(printf("vcb.rcvwait.dlen = %i\n", vcb.rcvwait.dlen));
    read = vcb.rcvwait.dlen;

    if ((vcb.rcvwait.primary_rc == AP_DEALLOC_NORMAL) || 
        (vcb.rcvwait.primary_rc == AP_DEALLOC_ABEND)) {
        do_tp_ended(tp_id);
        *dealloc = TRUE;
    } else if (vcb.rcvwait.primary_rc != AP_OK) {
        appcerror(vcb);
    } else if ((vcb.rcvwait.what_rcvd == AP_CONFIRM_DEALLOCATE) ||
               (vcb.rcvwait.what_rcvd == AP_DATA_COMPLETE_CONFIRM_DEALL)) {
        /* confirm deallocation */
        CLEARVCB(vcb);
        vcb.confirmed.opcode = AP_M_CONFIRMED;
        vcb.confirmed.opext = AP_MAPPED_CONVERSATION;
        memcpy(vcb.confirmed.tp_id, tp_id, 8);
        vcb.confirmed.conv_id = conv_id;
        callappc(&vcb);
        if (vcb.confirmed.primary_rc != AP_OK) appcerror(vcb);

        do_tp_ended(tp_id);
        *dealloc = TRUE;
    } else if ((vcb.rcvwait.what_rcvd == AP_CONFIRM_WHAT_RECEIVED) || 
               (vcb.rcvwait.what_rcvd == AP_CONFIRM_SEND) ||
               (vcb.rcvwait.what_rcvd == AP_DATA_COMPLETE_CONFIRM) || 
               (vcb.rcvwait.what_rcvd == AP_DATA_CONFIRM)) {
        /* do a confirmation if one was requested */
        CLEARVCB(vcb);
        vcb.confirmed.opcode = AP_M_CONFIRMED;
        vcb.confirmed.opext = AP_MAPPED_CONVERSATION;
        memcpy(vcb.confirmed.tp_id, tp_id, 8);
        vcb.confirmed.conv_id = conv_id;
        callappc(&vcb);
        if (vcb.confirmed.primary_rc != AP_OK) appcerror(vcb);
    }
    
    return read;
}

/*
 * do a MC_SEND_DATA verb with the given TP ID, Conversation ID and <len> 
 * bytes of data at the <data> pointer.  asks for a confirmation upon
 * sending.
 */
void do_send_data(char *tp_id, unsigned long int conv_id, void *data, int len) {
    vcb_t vcb;

    CLEARVCB(vcb);

    vcb.snddata.opcode = AP_M_SEND_DATA;
    vcb.snddata.opext = AP_MAPPED_CONVERSATION;
    memcpy(vcb.snddata.tp_id, tp_id, 8);
    vcb.snddata.conv_id = conv_id;
    vcb.snddata.dlen = len;
    vcb.snddata.dptr = data;
    vcb.snddata.type = AP_SEND_DATA_CONFIRM;

    callappc(&vcb);

    if (vcb.snddata.primary_rc != AP_OK) appcerror(vcb);
}

/*
 * ask for a confirmation on a given TP ID and Conversation ID.  used for
 * syncronizing data flow.
 */
void do_confirm(char *tp_id, unsigned long int conv_id) {
    vcb_t vcb;

    CLEARVCB(vcb);
    vcb.confirm.opcode = AP_M_CONFIRM;
    vcb.confirm.opext = AP_MAPPED_CONVERSATION;
    memcpy(vcb.confirm.tp_id, tp_id, 8);
    vcb.confirm.conv_id = conv_id;
        
    callappc(&vcb);

    if (vcb.confirm.primary_rc != AP_OK) appcerror(vcb);
}

/*
 * switch the conversation into a receive state and ask the partner TP
 * to confirm this.
 */
void do_prepare_to_receive(char *tp_id, unsigned long int conv_id) {
    vcb_t vcb;

    CLEARVCB(vcb);
    vcb.torec.opcode = AP_M_PREPARE_TO_RECEIVE;
    vcb.torec.opext = AP_MAPPED_CONVERSATION;
    vcb.torec.ptr_type = AP_SYNC_LEVEL;
    vcb.torec.locks = AP_SHORT;
    memcpy(vcb.torec.tp_id, tp_id, 8);
    vcb.torec.conv_id = conv_id;
        
    callappc(&vcb);

    if (vcb.confirm.primary_rc != AP_OK) appcerror(vcb);
}   

/*
 * wait on a TP name for a MC_ALLOCATE request.  the TP ID is written into
 * the buffer at <tp_id>, the conversation ID is returned.
 */
void do_get_fqplu_name(char *tp_id, unsigned long int conv_id, 
                       char *fqplu_name) {
    vcb_t vcb;

    CLEARVCB(vcb);
    vcb.getattrib.opcode = AP_M_GET_ATTRIBUTES;
    vcb.getattrib.opext = AP_MAPPED_CONVERSATION;
    memcpy(vcb.getattrib.tp_id, tp_id, 8);
    vcb.getattrib.conv_id = conv_id;
    
    callappc(&vcb);
    if (vcb.rcvalloc.primary_rc != AP_OK) appcerror(vcb);

    memcpy(fqplu_name, vcb.getattrib.fqplu_name, 17);
}

/*
 * start a new TP.  this registers the LU alias and TP name for your TP
 * to use and returns a TP ID
 */
void do_tp_started(TCHAR *lu_alias, TCHAR *tp_name, char *tp_id) {
    vcb_t vcb;

    CLEARVCB(vcb);
    vcb.tpstart.opcode = AP_TP_STARTED;
    memcpypad(vcb.tpstart.lu_alias, lu_alias, 8);
    memcpya2e(vcb.tpstart.tp_name, tp_name, 64);

    callappc(&vcb);
    if (vcb.tpstart.primary_rc != AP_OK) appcerror(vcb);

    memcpy(tp_id, vcb.tpstart.tp_id, 8);
}

/*
 * allocate a conversation with a partner TP.  This takes the partner TP's
 * alias, tp name, mode name, and your TP ID and returns a conversation ID.
 *
 * it does a MC_CONFIRM directly afterwords to see if the conversation was
 * really allocated.  if it wasn't it sleeps for 100ms and tries again for
 * up to 20 retries (about 2 seconds).
 */
unsigned long int do_mc_allocate(TCHAR *lu_alias, TCHAR *tp_name, 
                                 TCHAR *mode_name, char *tp_id) {
    vcb_t vcb;
    int tries = 0;
    unsigned long int conv_id;

    do {
        CLEARVCB(vcb);
        vcb.allocate.opcode = AP_M_ALLOCATE;
        vcb.allocate.opext = AP_MAPPED_CONVERSATION;
        memcpy(vcb.allocate.tp_id, tp_id, 8);
        vcb.allocate.sync_level = AP_CONFIRM_SYNC_LEVEL;
        vcb.allocate.rtn_ctl = AP_WHEN_SESSION_ALLOCATED;
    
        memcpypad(vcb.allocate.plu_alias, lu_alias, 8);
        memcpya2e(vcb.allocate.mode_name, mode_name, 8);
        memcpya2e(vcb.allocate.tp_name, tp_name, 64);
        vcb.allocate.security = AP_NONE;

        callappc(&vcb);
        conv_id = vcb.allocate.conv_id;
        if (vcb.allocate.primary_rc != AP_OK) appcerror(vcb);

        if (vcb.allocate.primary_rc == AP_ALLOCATION_ERROR) Sleep(100);
    } while ((tries++ < 20) && 
             (vcb.allocate.primary_rc == AP_ALLOCATION_ERROR));
    
    if (vcb.allocate.primary_rc != AP_OK) appcerror(vcb);
               
    return conv_id;
}

/*
 * deallocate a conversation.  should only be called with a TP ID and
 * conversation ID that are in the send state.
 */
void do_deallocate(char *tp_id, unsigned long int conv_id) {
    vcb_t vcb;

    CLEARVCB(vcb);
    vcb.dealloc.opcode = AP_M_DEALLOCATE;
    vcb.dealloc.opext = AP_MAPPED_CONVERSATION;
    memcpy(vcb.confirm.tp_id, tp_id, 8);
    vcb.confirm.conv_id = conv_id;
    vcb.dealloc.dealloc_type = AP_SYNC_LEVEL;

    callappc(&vcb);

    if (vcb.dealloc.primary_rc != AP_OK) appcerror(vcb);
}

void do_tp_ended(char *tp_id) {
    vcb_t vcb;

    CLEARVCB(vcb);
    vcb.tpend.opcode = AP_TP_ENDED;
    vcb.tpend.type = AP_SOFT;
    memcpy(vcb.confirm.tp_id, tp_id, 8);

    callappc(&vcb);

    if (vcb.dealloc.primary_rc != AP_OK) appcerror(vcb);
}

DWORD WINAPI listenthread(TCHAR *tpname) {
    vcb_t       vcb_r, vcb_w;               // verb control block for each sess
    TCHAR       tpname_r[9], tpname_w[9];   // tp name for each session
    HANDLE      h_event_r, h_event_w;       // event handles for each session
    HANDLE      h_async_r, h_async_w;       // async task handles for each sess
    HANDLE      objs[3];                    // array of handles to wait for
    DWORD       event;                      // which event returned
    tpconvid_t  tpconv;                     // temporary tpconv pointer
    name_time_t name_time;                  // logical unit of work & time key
    int         dread;
    BOOL        dealloc;                    // deallocation flag on session
    queue       *readq;                     // queue of sessions that have
                                            // read establish, but not write
    readnode_t  readnode;                   // node for readq
    unsigned long int w_conv_id;            // conversation id for write sess
    unsigned char w_tp_id[8];               // tp_id for write session
    qnode       *n;                         // temp node for searching queues

    // create the event handles for each session
    h_event_r = CreateEvent(NULL, FALSE, FALSE, NULL);
    h_event_w = CreateEvent(NULL, FALSE, FALSE, NULL);
    if ((h_event_r == NULL) || (h_event_w == NULL)) {
        printf("appclib: CreateEvent() failed near line %i\n", __LINE__);
        return FALSE;
    }

    // create the q
    readq = newq();
    if (readq == NULL) {
        printf("appclib: newq() failed near line %i\n", __LINE__);
        return FALSE;
    }

    // we actually use two different TP names, one for each session.  
    // the name that the server reads on ends in a R, the name that the
    // server writes on ends in a W

	//
	// last minute change to ensure we work as an autostarted TP where
	// the tp name we issue in the rcv_alloc must match the TP name we
	// registered as with Service Control Manager.  On the Server read
	// tp we do not alter the name.  The server write TP is still altered.
	// will most likely not work if the TP name is 8 chars long and ends
	// in a W.
	//
    memcpy(tpname_r, tpname, 8 * sizeof(TCHAR)); 
//    tpname_r[7] = 0; 
//    lstrcat(tpname_r, TEXT("R"));
    
    memcpy(tpname_w, tpname, 7 * sizeof(TCHAR)); 
    tpname_w[7] = 0; 
    lstrcat(tpname_w, TEXT("W"));

    // start an receive_allocate on the read tp
	InterlockedIncrement(&outstanding);
    CLEARVCB(vcb_r);
    vcb_r.rcvalloc.opcode = AP_RECEIVE_ALLOCATE;
    memcpya2e(vcb_r.rcvalloc.tp_name, tpname_r, 64);
    ASYNCAPPC(h_event_r, &vcb_r, h_async_r);
    if (h_async_r == 0) {
		InterlockedDecrement(&outstanding);
        return FALSE;
    }
    
    // start an receive_allocate on the write tp
	InterlockedIncrement(&outstanding);
    CLEARVCB(vcb_w);
    vcb_w.rcvalloc.opcode = AP_RECEIVE_ALLOCATE;
    memcpya2e(vcb_w.rcvalloc.tp_name, tpname_w, 64);
    ASYNCAPPC(h_event_w, &vcb_w, h_async_w);
    if (h_async_w == 0) {
		InterlockedDecrement(&outstanding);
        printf("appclib: WinAsyncAPPCEx failed with verb 0x%x near line %i\n", 
            APPC_FLIPI(vcb_r.rcvalloc.opcode), __LINE__);
        return FALSE;
    }

    while (TRUE) {
        objs[0] = h_event_r;
        objs[1] = h_event_w;
		objs[2] = hShutdownEvent;
        event = WaitForMultipleObjects(3, objs, FALSE, INFINITE)-WAIT_OBJECT_0;
        switch (event) {
            case 0:						// someone connected to reader
				InterlockedDecrement(&outstanding);

				// check the APPC return codes
				if (vcb_r.rcvalloc.primary_rc != AP_OK) appcerror(vcb_r);

                // allocate a new readnode struct and the tpconv structure
                // inside it.  save the tp_id and conv_id into the tpconv 
                // structure
                readnode = (readnode_t) memalloc(sizeof(struct readnode_st));
                readnode->tpconv = 
					(tpconvid_t) memalloc(sizeof(struct tpconvid_st));
                memcpy(readnode->tpconv->r_tp_id, vcb_r.rcvalloc.tp_id, 8);
                readnode->tpconv->r_conv_id = vcb_r.rcvalloc.conv_id;
                
                // start another receive_allocate on the read TP
				InterlockedIncrement(&outstanding);
                CLEARVCB(vcb_r);
                vcb_r.rcvalloc.opcode = AP_RECEIVE_ALLOCATE;
                memcpya2e(vcb_r.rcvalloc.tp_name, tpname_r, 64);
                ASYNCAPPC(h_event_r, &vcb_r, h_async_r);
    			if (h_async_r == 0) {
					InterlockedDecrement(&outstanding);
			        return FALSE;
    			}

                // receive_and_wait for the name_time key for this session
                dread = do_receive_and_wait(readnode->tpconv->r_tp_id, 
                    readnode->tpconv->r_conv_id, &(readnode->name_time), 
                    sizeof(name_time_t), &dealloc);
                if ((dread != sizeof(name_time_t)) || (dealloc)) {
                    // close session
					memfree(readnode->tpconv);
					memfree(readnode);
                    break;
                }

                // add all of this to the readq
                addtoq(readq, (void *) readnode);
                break;
            case 1:							// someone connected to writer
				InterlockedDecrement(&outstanding);

				// check the APPC return codes
				if (vcb_w.rcvalloc.primary_rc != AP_OK) appcerror(vcb_w);

                // save the tp id and conversation id for this session
                memcpy(w_tp_id, vcb_w.rcvalloc.tp_id, 8);
                w_conv_id = vcb_w.rcvalloc.conv_id;

                // start another receive_allocate on the write TP
				InterlockedIncrement(&outstanding);
                CLEARVCB(vcb_w);
                vcb_w.rcvalloc.opcode = AP_RECEIVE_ALLOCATE;
                memcpya2e(vcb_w.rcvalloc.tp_name, tpname_w, 64);
                ASYNCAPPC(h_event_w, &vcb_w, h_async_w);
    			if (h_async_w == 0) {
					InterlockedDecrement(&outstanding);
			        return FALSE;
    			}

                // receive and wait for the name_time key for this session
                dread = do_receive_and_wait(w_tp_id, w_conv_id, &name_time,
                    sizeof(name_time_t), &dealloc);
                if ((dread != sizeof(name_time_t)) || (dealloc)) {
                    // close session
                    break;
                }

                // find the matching name_time key in the readq
                for (n = readq->head; n != NULL; n = n->next) {
                    if (memcmp(&name_time, 
                        &(((readnode_t) (n->ptr))->name_time), 
                        sizeof(name_time_t)) == 0) break;
                }
                if (n == NULL) {
                    // close session
                    break;
                }

                readnode = (readnode_t) removeqnodefromq(readq, n);
                tpconv = readnode->tpconv;
                memfree(readnode);
                memcpy(tpconv->w_tp_id, w_tp_id, 8);
                tpconv->w_conv_id = w_conv_id;
                tpconv->r_valid = TRUE;
                tpconv->w_valid = TRUE;

                // receive and wait to confirm data turnaround
                do_receive_and_wait(tpconv->w_tp_id, tpconv->w_conv_id, 
					NULL, 0, &dealloc);

                // add it to the pairq and signal that there is one more
                // pair available
                EnterCriticalSection(&csPairq);
                addtoq(pairq, (void *) tpconv);
                ReleaseSemaphore(hPairqSem, 1, NULL);
                LeaveCriticalSection(&csPairq);
                break;
			case 2:							// shutdown event
				WinAPPCCancelAsyncRequest(h_async_r);
				InterlockedDecrement(&outstanding);
				WinAPPCCancelAsyncRequest(h_async_w);
				if (InterlockedDecrement(&outstanding) <= 0) 
					SetEvent(hOutstandingZero);
				return FALSE;
        }
    }
}

/*
 * ---- functions to setup easy two-way APPC communication ----
 */

/*
 * listen on a TP name for incoming conversations.
 *
 * each TP can only listen to one tpname at a time (because this only
 * spawns one listenthread).  If a TP needs to be written that can handle
 * listening to multiple TP names in one run then this will need to be 
 * modified to make one listenthread() for each appclisten() that gets
 * called with a unique TP name.
 *
 * returns a tpconvid that can be used with appcread, appcwrite and 
 * appcclose.
 */
tpconvid_t appclisten(TCHAR *tpname) {
    tpconvid_t tpconv;
    DWORD tid;

    APPCDBG(printf("appclisten(%ws) starting\n", tpname));

    if (hListenThread == NULL) {
        APPCDBG(printf("appclisten: creating listenthread\n"));
        // create the semaphore for the pairq
        hPairqSem = CreateSemaphore(NULL, 0, 100000, NULL);
        if (hPairqSem == NULL) return NULL;

        // create the pairq
        pairq = newq();
        if (pairq == NULL) return NULL;

        // create a critical section for dealing with the pairq
        InitializeCriticalSection(&csPairq);
    
        // create the listen thread
        hListenThread = CreateThread(NULL, 0, 
            (LPTHREAD_START_ROUTINE) listenthread, tpname, 0, &tid);
        if (hListenThread == NULL) return NULL;
    }

    // wait for the listen thread to put a tpconv pair into the pairq
    WaitForSingleObject(hPairqSem, INFINITE);

    // remove the first tpconv pair from the pairq and return it
    EnterCriticalSection(&csPairq);
    tpconv = removeheadfromq(pairq);
    LeaveCriticalSection(&csPairq);

    APPCDBG(printf("appclisten done\n", tpname));

    return tpconv;
}

/*
 * connect to a remote server.  this allocates two conversations, one
 * to write on and one to read on.  
 *
 * the LU's should be listed as partners under SNA Admin with a mode name of
 * <mode_name> between them.
 *
 * returns a tpconvid which can be used with appcread, appcwrite, and 
 * appcclose.
 */
tpconvid_t appcconnect(TCHAR *lu_alias, TCHAR *plu_alias, 
                       TCHAR *tp_name, TCHAR *loc_tp_name, TCHAR *mode_name) {
    tpconvid_t  tpconv;
    name_time_t name_time;
    TCHAR       tpname_w[9], tpname_r[9];
    TCHAR       loctpname_w[9], loctpname_r[9];


    APPCDBG(printf("appcconnect(%ws, %ws, %ws, %ws) starting\n", lu_alias, plu_alias, tp_name, mode_name));

    // we actually use two different TP names, one for each session.  
    // the name that the server reads on ends in a R, the name that the
    // server writes on ends in a W
    memcpy(tpname_r, tp_name, 8 * sizeof(TCHAR)); 
//    tpname_r[7] = 0; 
//    lstrcat(tpname_r, TEXT("R"));
    
    memcpy(tpname_w, tp_name, 7 * sizeof(TCHAR)); 
    tpname_w[7] = 0; 
    lstrcat(tpname_w, TEXT("W"));

    memcpy(loctpname_r, loc_tp_name, 8 * sizeof(TCHAR)); 
//    loctpname_r[7] = 0; 
//    lstrcat(loctpname_r, TEXT("R"));
    
    memcpy(loctpname_w, loc_tp_name, 7 * sizeof(TCHAR)); 
	loctpname_w[7] = 0; 
    lstrcat(loctpname_w, TEXT("W"));

    tpconv = (tpconvid_t) memalloc(sizeof(struct tpconvid_st));
    if (tpconv == NULL) {
        printf("appclib: couldn't allocate memory for tpconvid_t\n");
        exit(1);
    }

    // connect the first session
    do_tp_started(lu_alias, loctpname_w, tpconv->w_tp_id);
    tpconv->w_conv_id = do_mc_allocate(plu_alias, tpname_r, mode_name, 
        tpconv->w_tp_id);
    // fill in the logical unit of work/time structure
    do_get_fqplu_name(tpconv->w_tp_id, tpconv->w_conv_id, name_time.fqplu_name);
    name_time.time = GetTickCount();
    // send the fqplu name/time information
    do_send_data(tpconv->w_tp_id, tpconv->w_conv_id, (void *) &name_time, 
        sizeof(name_time_t));
    tpconv->w_valid = TRUE;

    // connect the second session
    do_tp_started(lu_alias, loctpname_r, tpconv->r_tp_id);
    tpconv->r_conv_id = do_mc_allocate(plu_alias, tpname_w, mode_name, 
        tpconv->r_tp_id);
    // send the fqplu name/time information
    do_send_data(tpconv->r_tp_id, tpconv->r_conv_id, (void *) &name_time, 
        sizeof(name_time_t));
    // reverse the conversation
    do_prepare_to_receive(tpconv->r_tp_id, tpconv->r_conv_id);
    tpconv->r_valid = TRUE;

    APPCDBG(printf("appcconnect done\n"));

    return tpconv;
}

/*
 * read from a conversation setup by appcconnect() or appclisten().  
 * will read at most <maxlen> bytes into the buffer at <data>.
 */
int appcread(tpconvid_t tpconv, void *data, int maxlen) {
    BOOL dealloc;
    int read;

    APPCDBG(printf("appcread(tpconv, data, %i) starting\n", maxlen));

    if (!tpconv->r_valid) return -1;
    read = do_receive_and_wait(tpconv->r_tp_id, tpconv->r_conv_id, data, maxlen,
        &dealloc);
    if (dealloc) tpconv->r_valid = FALSE;

    APPCDBG(printf("appcread done, returning %i, dealloc = %i, tpconv->r_valid = %i\n", read, dealloc, tpconv->r_valid));

    return read;
}

/*
 * write to a conversation setup by appcconnect() or appclisten().
 * will write at most <maxlen> bytes into the buffer at <data>
 */
void appcwrite(tpconvid_t tpconv, void *data, int len) {
    APPCDBG(printf("appcwrite(tpconv, data, %i) starting\n", len));
    do_send_data(tpconv->w_tp_id, tpconv->w_conv_id, data, len);
    APPCDBG(printf("appcwrite done\n"));
}

int appcvalid(tpconvid_t tpconv) {
    int rc;

    APPCDBG(printf("appcvalid starting and done, returning %i\n", (tpconv->r_valid && tpconv->w_valid)));
    rc = (tpconv->r_valid && tpconv->w_valid);
    return rc;
}

void appcclose(tpconvid_t tpconv) {
    APPCDBG(printf("appcclose(tpconv) starting\n"));

    /* deallocate the write channel */
    if (tpconv->w_valid) {
        do_deallocate(tpconv->w_tp_id, tpconv->w_conv_id);
        do_tp_ended(tpconv->w_tp_id);
        tpconv->w_valid = FALSE;
    }

    APPCDBG(printf("appcclose done\n"));
}
