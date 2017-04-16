//
//  Define Macro's External API's
//
SRV_CONFIG *
    SRVAPI srv_getconfig( SRV_SERVER * server );

SRV_SERVER *
    SRVAPI srv_getserver( SRV_PROC   * srvproc );

BOOL
    SRVAPI srv_got_attention( SRV_PROC * srvproc );

void *
    SRVAPI srv_eventdata( SRV_PROC * srvproc);

//
//  Define Macro's
//
#define SRV_GETCONFIG(a)	srv_getconfig	  ( a )
#define SRV_GETSERVER(a)	srv_getserver	  ( a )
#define SRV_GOT_ATTENTION(a)	srv_got_attention ( a )
#define	SRV_EVENTDATA(a)	srv_eventdata	  ( a )
#define	SRV_IODEAD(a)		srv_iodead	  ( a )
#define	SRV_TDSVERSION(a)	srv_tdsversion	  ( a )

//
//  Define Other External API's
//
void *
    SRVAPI srv_alloc( DBINT size );

int
    SRVAPI srv_bmove( void  * from,
		      void  * to,
		      DBINT	  count );

int
    SRVAPI srv_bzero( void  * location,
		      DBINT	  count );

int
    SRVAPI srv_config( SRV_CONFIG * config,
		       DBINT		option,
		       DBCHAR	  * value,
		       int		valuelen );

SRV_CONFIG *
    SRVAPI srv_config_alloc( void );

int
    SRVAPI srv_convert( SRV_PROC * srvproc,
			int	       srctype,
			void	 * src,
			DBINT	       srclen,
			int	       desttype,
			void	 * dest,
			DBINT	       destlen );

int
    SRVAPI srv_describe( SRV_PROC * srvproc,
			 int		colnumber,
			 DBCHAR *	columnname,
			 int		namelen,
			 DBINT		desttype,
			 DBINT		destlen,
			 DBINT		srctype,
			 DBINT		srclen,
			 void	*	srcdata );

int
	(* SRVAPI srv_errhandle( int (CDECL *handler)
				 ( SRV_SERVER * server,
				   SRV_PROC *   srvproc,
				   int		    srverror,
				   BYTE 	    severity,
				   BYTE 	    state,
				   int		    oserrnum,
				   DBCHAR *     errtext,
				   int		    errtextlen,
				   DBCHAR *     oserrtext,
				   int		    oserrtextlen) ))
				 ( SRV_SERVER * server,
				   SRV_PROC *   srvproc,
				   int		    srverror,
				   BYTE 	    severity,
				   BYTE 	    state,
				   int		    oserrnum,
				   DBCHAR *     errtext,
				   int		    errtextlen,
				   DBCHAR *     oserrtext,
				   int		    oserrtextlen );

int
    SRVAPI srv_event( SRV_PROC * srvproc,
		      int	     event,
		      BYTE     * data );

int
    SRVAPI srv_free( void * ptr );

void *
    SRVAPI srv_getuserdata( SRV_PROC * srvproc);

int
    SRVAPI srv_getbindtoken( SRV_PROC * srvproc, char * token_buf );

int
	SRVAPI srv_getdtcxact( SRV_PROC * srvproc, void** ppv);

int
    (* SRVAPI srv_handle( SRV_SERVER * server,
			      DBINT	       event,
				  int (CDECL *handler)(void *) ))
			      (void *);

int
    SRVAPI srv_impersonate_client( SRV_PROC * srvproc );

SRV_SERVER *
    SRVAPI srv_init( SRV_CONFIG * config,
		     DBCHAR	* connectname,
		     int	      namelen );

BOOL
    SRVAPI srv_iodead( SRV_PROC * srvproc );

long
    SRVAPI srv_langcpy( SRV_PROC *	srvproc,
			long		start,
			long		nbytes,
			DBCHAR	 *	buffer );

long
    SRVAPI srv_langlen( SRV_PROC * srvproc );

void *
    SRVAPI srv_langptr( SRV_PROC *srvproc );

int
    SRVAPI srv_log( SRV_SERVER * server,
		    BOOL	     datestamp,
		    DBCHAR     * msg,
		    int 	     msglen );

void *
    SRVAPI srv_paramdata( SRV_PROC * srvproc,
			  int		 n );

int
    SRVAPI srv_paramlen( SRV_PROC * srvproc,
			 int		n );

int
    SRVAPI srv_parammaxlen( SRV_PROC * srvproc,
			    int 	   n );

DBCHAR *
    SRVAPI srv_paramname( SRV_PROC * srvproc,
			  int		 n,
			  int	   * len );

int
    SRVAPI srv_paramnumber( SRV_PROC * srvproc,
			    DBCHAR   * name,
			    int 	   len );

int
    SRVAPI srv_paramset( SRV_PROC * srvproc,
			 int		n,
			 void	  * data,
			 int		len );

int
    SRVAPI srv_paramstatus( SRV_PROC * srvproc,
			    int 	   n );

int
    SRVAPI srv_paramtype( SRV_PROC * srvproc,
			  int		 n );


DBCHAR *
    SRVAPI srv_pfield( SRV_PROC * srvproc,
		       int	      field,
		       int	* len );

int
    SRVAPI srv_returnval( SRV_PROC * srvproc,
			  DBCHAR   * valuename,
			  int		 len,
			  BYTE		 status,
			  DBINT 	 type,
			  DBINT 	 maxlen,
			  DBINT 	 datalen,
			  void	   * value );

int
    SRVAPI srv_revert_to_self( SRV_PROC * srvproc );

DBCHAR *
    SRVAPI srv_rpcdb( SRV_PROC * srvproc,
		      int      * len );

DBCHAR *
    SRVAPI srv_rpcname( SRV_PROC * srvproc,
			int	 * len );

int
    SRVAPI srv_rpcnumber( SRV_PROC * srvproc );

DBUSMALLINT
    SRVAPI srv_rpcoptions( SRV_PROC * srvproc );

DBCHAR *
    SRVAPI srv_rpcowner( SRV_PROC * srvproc,
			 int	  * len );

int
    SRVAPI srv_rpcparams( SRV_PROC * srvproc );

int
    SRVAPI srv_run( SRV_SERVER * server );

int
	SRVAPI srv_senddone( SRV_PROC * srvproc,
			 DBUSMALLINT	status,
			 DBUSMALLINT	curcmd,
			 DBINT		count);

int
    SRVAPI srv_sendmsg( SRV_PROC * srvproc,
			int	       msgtype,
			DBINT	       msgnum,
			DBTINYINT      msgclass,
			DBTINYINT      state,
			DBCHAR	 * rpcname,
			int	       rpcnamelen,
			DBUSMALLINT    linenum,
			DBCHAR	 * message,
			int	       msglen );

int
    SRVAPI srv_sendrow( SRV_PROC * srvproc );

int
    SRVAPI srv_sendstatus( SRV_PROC * srvproc,
			   DBINT	  status );

int
    SRVAPI srv_setcoldata( SRV_PROC * srvproc,
			   int		  column,
			   void     * data);

int
    SRVAPI srv_setcollen( SRV_PROC * srvproc,
			  int		 column,
			  int	 len );

int
    SRVAPI srv_setuserdata( SRV_PROC * srvproc,
			    void *	   ptr);

int
    SRVAPI srv_setutype( SRV_PROC * srvproc,
			 int		column,
			 DBINT		usertype );

DBCHAR *
    SRVAPI srv_sfield( SRV_SERVER * server,
		       int		field,
		       int	  * len );
DBCHAR *
    SRVAPI srv_symbol( int	 type,
		       int	 symbol,
		       int * len );

int
    SRVAPI srv_tdsversion( SRV_PROC * srvproc );

BOOL
    SRVAPI srv_willconvert( int srctype,
			    int desttype );
int 
    SRVAPI srv_writebuf( SRV_PROC * srvproc,
             void * ptr,
             WORD count );

int
    SRVAPI srv_get_text( SRV_PROC * srvproc,
			 long * outlen);

void
    SRVAPI srv_ackattention( SRV_PROC * srvproc);

int
    SRVAPI srv_terminatethread( SRV_PROC * srvproc);

int
    SRVAPI srv_sendstatistics( SRV_PROC * srvproc);

int
    SRVAPI srv_clearstatistics( SRV_PROC * srvproc);

int
    SRVAPI srv_setevent( SRV_SERVER * server, int event);

int 
	SRVAPI srv_message_handler(SRV_PROC * srvproc, int errornum, BYTE severity,
		BYTE state, int oserrnum, char *errtext, int errtextlen, 
		char *oserrtext, int oserrtextlen);

int
     SRVAPI srv_pre_handle(SRV_SERVER * server,
			     SRV_PROC * srvproc,
			     DBINT event,
				 int (CDECL *handler)(void *),
			     BOOL remove);
int
     SRVAPI srv_post_handle(SRV_SERVER * server,
			    SRV_PROC * srvproc,
			    DBINT event,
				int (CDECL *handler)(void *),
			    BOOL remove);

int
    SRVAPI srv_ansi_sendmsg( SRV_PROC * srvproc,
			int	       msgtype,
			DBINT	       msgnum,
			DBTINYINT      msgclass,
			DBTINYINT      state,
			DBCHAR	 * rpcname,
			int	       rpcnamelen,
			DBUSMALLINT    linenum,
			DBCHAR	 * message,
			int	       msglen );

int
    SRVAPI srv_post_completion_queue( SRV_PROC * srvproc,
			DBCHAR	 * inbuf,
			int	 inbuflen );
