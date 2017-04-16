/*++

Copyright (c) 1996 Microsoft Corporation

Module Name:

    mq.h

Abstract:

    Master include file for Message Queue applications

--*/

#ifndef __MQ_H__
#define __MQ_H__

//
//  Clients that need transactions should include transact.h before mq.h
//  For the clients not needing transactions - ITransaction is  opaque
//
#ifndef __transact_h__
typedef void ITransaction;
#endif

//
//	Support version older than VC4.2
//
#if defined(_MSC_VER) && (_MSC_VER < 1020)

typedef struct tagMQPROPVARIANT MQPROPVARIANT;

#define TYPEDEF_CA(type, name) \
    typedef struct tag##name {\
        ULONG cElems;\
        type * pElems;\
    } name

#ifndef _tagCAUB_DEFINED
#define _tagCAUB_DEFINED
TYPEDEF_CA(unsigned char, CAUB);
#endif

#ifndef _tagCAI_DEFINED
#define _tagCAI_DEFINED
TYPEDEF_CA(short, CAI);
#endif

#ifndef _tagCAUI_DEFINED
#define _tagCAUI_DEFINED
TYPEDEF_CA(USHORT, CAUI);
#endif

#ifndef _tagCAL_DEFINED
#define _tagCAL_DEFINED
TYPEDEF_CA(long, CAL);
#endif

#ifndef _tagCAUL_DEFINED
#define _tagCAUL_DEFINED
TYPEDEF_CA(ULONG, CAUL);
#endif

#ifndef _tagCACLSID_DEFINED
#define _tagCACLSID_DEFINED
TYPEDEF_CA(CLSID, CACLSID);
#endif

#ifndef _tagCABSTR_DEFINED
#define _tagCABSTR_DEFINED
TYPEDEF_CA(LPOLESTR, CABSTR);
#endif

#ifndef _tagCALPWSTR_DEFINED
#define _tagCALPWSTR_DEFINED
TYPEDEF_CA(LPWSTR, CALPWSTR);
#endif

#ifndef _tagCAMQPROPVARIANT_DEFINED
#define _tagCAMQPROPVARIANT_DEFINED
TYPEDEF_CA(MQPROPVARIANT, CAMQPROPVARIANT);
#endif

struct tagMQPROPVARIANT {
    VARTYPE vt;
    WORD wReserved1;
    WORD wReserved2;
    WORD wReserved3;
    /*[switch_is((unsigned short)vt)]*/ union {
      /*[case(VT_EMPTY, VT_NULL)];*/
      /*[case(VT_UI1)]*/               UCHAR bVal;
      /*[case(VT_I2)]*/                short iVal;
      /*[case(VT_UI2)]*/               USHORT uiVal;
      /*[case(VT_BOOL)]*/              VARIANT_BOOL boolVal;
      /*[case(VT_I4)]*/                long lVal;
      /*[case(VT_UI4)]*/               ULONG ulVal;
      /*[case(VT_HRESULT)]*/           SCODE scode;
      /*[case(VT_DATE)]*/              DATE date;
      /*[case(VT_CLSID)]*/             CLSID  *puuid;
      /*[case(VT_BLOB)]*/              BLOB blob;
      /*[case(VT_BSTR)]*/              LPOLESTR bstrVal;
      /*[case(VT_LPSTR)]*/             LPSTR pszVal;
      /*[case(VT_LPWSTR)]*/            LPWSTR pwszVal;
      /*[case(VT_VECTOR | VT_UI1)]*/   CAUB caub;
      /*[case(VT_VECTOR | VT_I2)]*/    CAI cai;
      /*[case(VT_VECTOR | VT_UI2)]*/   CAUI caui;
      /*[case(VT_VECTOR | VT_I4)]*/    CAL cal;
      /*[case(VT_VECTOR | VT_UI4)]*/   CAUL caul;
      /*[case(VT_VECTOR | VT_CLSID)]*/ CACLSID cauuid;
      /*[case(VT_VECTOR | VT_BSTR)]*/  CABSTR cabstr;
      /*[case(VT_VECTOR | VT_LPWSTR)]*/CALPWSTR calpwstr;
      /*[case(VT_VARIANT)]*/           CAMQPROPVARIANT capropvar;
    };
};

#else // defined(_MSC_VER) && (_MSC_VER < 1020)

typedef struct tagPROPVARIANT tagMQPROPVARIANT;

typedef tagMQPROPVARIANT MQPROPVARIANT;

#endif // defined(_MSC_VER) && (_MSC_VER < 1020)

#define	PRLT	( 0 )

#define	PRLE	( 1 )

#define	PRGT	( 2 )

#define	PRGE	( 3 )

#define	PREQ	( 4 )

#define	PRNE	( 5 )

typedef struct  tagMQPROPERTYRESTRICTION
    {
    ULONG rel;
    PROPID prop;
    MQPROPVARIANT prval;
    }	MQPROPERTYRESTRICTION;

typedef struct  tagMQRESTRICTION
    {
    ULONG cRes;
    /* [size_is] */ MQPROPERTYRESTRICTION __RPC_FAR *paPropRes;
    }	MQRESTRICTION;

typedef struct  tagMQCOLUMNSET
    {
    ULONG cCol;
    /* [size_is] */ PROPID __RPC_FAR *aCol;
    }	MQCOLUMNSET;

#define	QUERY_SORTASCEND	( 0 )

#define	QUERY_SORTDESCEND	( 1 )

typedef struct  tagMQSORTKEY
    {
    PROPID propColumn;
    ULONG dwOrder;
    }	MQSORTKEY;

typedef struct  tagMQSORTSET
    {
    ULONG cCol;
    /* [size_is] */ MQSORTKEY __RPC_FAR *aCol;
    }	MQSORTSET;


#define MQ_MAX_Q_NAME_LEN      124   // Maximal WCHAR length of a queue name.
#define MQ_MAX_Q_LABEL_LEN     124
#define MQ_MAX_MSG_LABEL_LEN   250

typedef HANDLE QUEUEHANDLE;


typedef PROPID          MSGPROPID;
typedef PROPID          QUEUEPROPID;
typedef PROPID          QMPROPID;

typedef struct tagMQMSGPROPS
{
    DWORD           cProp;
    MSGPROPID*      aPropID;
    MQPROPVARIANT*  aPropVar;
    HRESULT*        aStatus;
} MQMSGPROPS;

typedef struct tagMQQUEUEPROPS
{
    DWORD           cProp;
    QUEUEPROPID*    aPropID;
    MQPROPVARIANT*  aPropVar;
    HRESULT*        aStatus;
} MQQUEUEPROPS;

typedef struct tagMQQMPROPS
{
    DWORD           cProp;
    QMPROPID*       aPropID;
    MQPROPVARIANT*  aPropVar;
    HRESULT*        aStatus;
} MQQMPROPS;



//********************************************************************
//  API FLAGS
//********************************************************************

//
//  MQOpenQueue - Access values
//
#define MQ_RECEIVE_ACCESS       0x00000001
#define MQ_SEND_ACCESS          0x00000002
#define MQ_PEEK_ACCESS          0x00000020

//
//  MQOpenQueue - Share values
//
#define MQ_DENY_NONE            0x00000000
#define MQ_DENY_RECEIVE_SHARE   0x00000001

//
//  MQReceiveMessage - Action values
//
#define MQ_ACTION_RECEIVE       0x00000000
#define MQ_ACTION_PEEK_CURRENT  0x80000000
#define MQ_ACTION_PEEK_NEXT     0x80000001

//
// MQSendMessage,  MQReceiveMessage:  special cases for the transaction parameter
//
#define MQ_NO_TRANSACTION             NULL
#define MQ_MTS_TRANSACTION            (ITransaction *)1
#define MQ_XA_TRANSACTION             (ITransaction *)2
#define MQ_SINGLE_MESSAGE             (ITransaction *)3

//********************************************************************
//  PRIORITY LIMITS
//********************************************************************

//
//  Message priorities
//
#define MQ_MIN_PRIORITY          0    // Minimal message priority
#define MQ_MAX_PRIORITY          7    // Maximal message priority


//********************************************************************
//  MESSAGE PROPERTIES
//********************************************************************
#define PROPID_M_BASE                0
#define PROPID_M_CLASS               (PROPID_M_BASE + 1)     /* VT_UI2           */
#define PROPID_M_MSGID               (PROPID_M_BASE + 2)     /* VT_UI1|VT_VECTOR */
#define PROPID_M_CORRELATIONID       (PROPID_M_BASE + 3)     /* VT_UI1|VT_VECTOR */
#define PROPID_M_PRIORITY            (PROPID_M_BASE + 4)     /* VT_UI1           */
#define PROPID_M_DELIVERY            (PROPID_M_BASE + 5)     /* VT_UI1           */
#define PROPID_M_ACKNOWLEDGE         (PROPID_M_BASE + 6)     /* VT_UI1           */
#define PROPID_M_JOURNAL             (PROPID_M_BASE + 7)     /* VT_UI1           */
#define PROPID_M_APPSPECIFIC         (PROPID_M_BASE + 8)     /* VT_UI4           */
#define PROPID_M_BODY                (PROPID_M_BASE + 9)     /* VT_UI1|VT_VECTOR */
#define PROPID_M_BODY_SIZE           (PROPID_M_BASE + 10)    /* VT_UI4           */
#define PROPID_M_LABEL               (PROPID_M_BASE + 11)    /* VT_LPWSTR        */
#define PROPID_M_LABEL_LEN           (PROPID_M_BASE + 12)    /* VT_UI4           */
#define PROPID_M_TIME_TO_REACH_QUEUE (PROPID_M_BASE + 13)    /* VT_UI4           */
#define PROPID_M_TIME_TO_BE_RECEIVED (PROPID_M_BASE + 14)    /* VT_UI4           */
#define PROPID_M_RESP_QUEUE          (PROPID_M_BASE + 15)    /* VT_LPWSTR        */
#define PROPID_M_RESP_QUEUE_LEN      (PROPID_M_BASE + 16)    /* VT_UI4           */
#define PROPID_M_ADMIN_QUEUE         (PROPID_M_BASE + 17)    /* VT_LPWSTR        */
#define PROPID_M_ADMIN_QUEUE_LEN     (PROPID_M_BASE + 18)    /* VT_UI4           */
#define PROPID_M_VERSION             (PROPID_M_BASE + 19)    /* VT_UI4           */
#define PROPID_M_SENDERID            (PROPID_M_BASE + 20)    /* VT_UI1|VT_VECTOR */
#define PROPID_M_SENDERID_LEN        (PROPID_M_BASE + 21)    /* VT_UI4           */
#define PROPID_M_SENDERID_TYPE       (PROPID_M_BASE + 22)    /* VT_UI4           */
#define PROPID_M_PRIV_LEVEL          (PROPID_M_BASE + 23)    /* VT_UI4           */
#define PROPID_M_AUTH_LEVEL          (PROPID_M_BASE + 24)    /* VT_UI4           */
#define PROPID_M_AUTHENTICATED       (PROPID_M_BASE + 25)    /* VT_UI1           */
#define PROPID_M_HASH_ALG            (PROPID_M_BASE + 26)    /* VT_UI4           */
#define PROPID_M_ENCRYPTION_ALG      (PROPID_M_BASE + 27)    /* VT_UI4           */
#define PROPID_M_SENDER_CERT         (PROPID_M_BASE + 28)    /* VT_UI1|VT_VECTOR */
#define PROPID_M_SENDER_CERT_LEN     (PROPID_M_BASE + 29)    /* VT_UI4           */
#define PROPID_M_SRC_MACHINE_ID      (PROPID_M_BASE + 30)    /* VT_CLSID         */
#define PROPID_M_SENTTIME            (PROPID_M_BASE + 31)    /* VT_UI4           */
#define PROPID_M_ARRIVEDTIME         (PROPID_M_BASE + 32)    /* VT_UI4           */
#define PROPID_M_DEST_QUEUE          (PROPID_M_BASE + 33)    /* VT_LPWSTR        */
#define PROPID_M_DEST_QUEUE_LEN      (PROPID_M_BASE + 34)    /* VT_UI4           */
#define PROPID_M_EXTENSION           (PROPID_M_BASE + 35)    /* VT_UI1|VT_VECTOR */
#define PROPID_M_EXTENSION_LEN       (PROPID_M_BASE + 36)    /* VT_UI4           */
#define PROPID_M_SECURITY_CONTEXT    (PROPID_M_BASE + 37)    /* VT_UI4           */
#define PROPID_M_CONNECTOR_TYPE      (PROPID_M_BASE + 38)    /* VT_CLSID         */
#define PROPID_M_XACT_STATUS_QUEUE   (PROPID_M_BASE + 39)    /* VT_LPWSTR        */
#define PROPID_M_XACT_STATUS_QUEUE_LEN (PROPID_M_BASE + 40)  /* VT_UI4           */
#define PROPID_M_TRACE               (PROPID_M_BASE + 41)    /* VT_UI1           */
#define PROPID_M_BODY_TYPE           (PROPID_M_BASE + 42)    /* VT_UI4           */
#define PROPID_M_DEST_SYMM_KEY       (PROPID_M_BASE + 43)    /* VT_UI1|VT_VECTOR */
#define PROPID_M_DEST_SYMM_KEY_LEN   (PROPID_M_BASE + 44)    /* VT_UI4           */
#define PROPID_M_SIGNATURE           (PROPID_M_BASE + 45)    /* VT_UI1|VT_VECTOR */
#define PROPID_M_SIGNATURE_LEN       (PROPID_M_BASE + 46)    /* VT_UI4           */
#define PROPID_M_PROV_TYPE           (PROPID_M_BASE + 47)    /* VT_UI4           */
#define PROPID_M_PROV_NAME           (PROPID_M_BASE + 48)    /* VT_LPWSTR        */
#define PROPID_M_PROV_NAME_LEN       (PROPID_M_BASE + 49)    /* VT_UI4           */


//
// Message Property Size
//
#define PROPID_M_MSGID_SIZE         20
#define PROPID_M_CORRELATIONID_SIZE 20


//********************************************************************
//  MESSAGE CLASS VALUES
//********************************************************************
//
//  Message Class Values are 16 bits layed out as follows:
//
//   1 1 1 1 1 1
//   5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +-+-+-----------+---------------+
//  |S|R| Reserved  |  Class code   |
//  +-+-+-----------+---------------+
//
//  where
//
//      S - is the severity flag
//          0 - Normal Message/Positive Acknowledgment (ACK)
//          1 - Negative Acknowledgment (NACK)
//
//      R - is the receive flag
//          0 - Arrival ACK/NACK
//          1 - Receive ACK/NACK
//
#define MQCLASS_CODE(s, r, code) ((USHORT)(((s) << 15) | ((r) << 14) | (code)))
#define MQCLASS_NACK(c)     ((c) & 0x8000)
#define MQCLASS_RECEIVE(c)  ((c) & 0x4000)

//
//  Normal message
//
#define MQMSG_CLASS_NORMAL                      MQCLASS_CODE(0, 0, 0x00)

//
//  Report message
//
#define MQMSG_CLASS_REPORT                      MQCLASS_CODE(0, 0, 0x01)

//
//  Arrival acknowledgment. The message has reached the destination queue
//
#define MQMSG_CLASS_ACK_REACH_QUEUE             MQCLASS_CODE(0, 0, 0x02)

//
//  Receive acknowledgment. The message has been received by the application
//
#define MQMSG_CLASS_ACK_RECEIVE                 MQCLASS_CODE(0, 1, 0x00)


//-----------------------------------------------
//
//  Negative arrival acknowledgments
//

//
//  Destination queue can not be reached, the queue may have been deleted
//
#define MQMSG_CLASS_NACK_BAD_DST_Q              MQCLASS_CODE(1, 0, 0x00)

//
//  The message was purged before reaching the destination queue
//
#define MQMSG_CLASS_NACK_PURGED                 MQCLASS_CODE(1, 0, 0x01)

//
//  Time to reach queue has expired
//
#define MQMSG_CLASS_NACK_REACH_QUEUE_TIMEOUT    MQCLASS_CODE(1, 0, 0x02)

//
//  The message has exceeded the queue quota
//
#define MQMSG_CLASS_NACK_Q_EXCEED_QUOTA         MQCLASS_CODE(1, 0, 0x03)

//
//  The sender does not have send access rights on the queue.
//
#define MQMSG_CLASS_NACK_ACCESS_DENIED          MQCLASS_CODE(1, 0, 0x04)

//
//  The message hop count exceeded
//
#define MQMSG_CLASS_NACK_HOP_COUNT_EXCEEDED     MQCLASS_CODE(1, 0, 0x05)

//
//  The message signature is bad. The message could not be authenticated.
//
#define MQMSG_CLASS_NACK_BAD_SIGNATURE          MQCLASS_CODE(1, 0, 0x06)

//
//  The message could not be decrypted.
//
#define MQMSG_CLASS_NACK_BAD_ENCRYPTION         MQCLASS_CODE(1, 0, 0x07)

//
//  The message could not be encrypted for the destination.
//
#define MQMSG_CLASS_NACK_COULD_NOT_ENCRYPT      MQCLASS_CODE(1, 0, 0x08)

//
//  The message was sent to a non-transactional queue within a transaction.
//
#define MQMSG_CLASS_NACK_NOT_TRANSACTIONAL_Q    MQCLASS_CODE(1, 0, 0x09)

//
//  The message was sent to a transactional queue not within a transaction.
//
#define MQMSG_CLASS_NACK_NOT_TRANSACTIONAL_MSG  MQCLASS_CODE(1, 0, 0x0A)


//-----------------------------------------------
//
//  Negative receive acknowledgments
//

//
//  The queue was deleted, after the message has arrived
//
#define MQMSG_CLASS_NACK_Q_DELETED              MQCLASS_CODE(1, 1, 0x00)

//
//  The message was purged at the destination queue
//
#define MQMSG_CLASS_NACK_Q_PURGED               MQCLASS_CODE(1, 1, 0x01)

//
//  Time to receive has expired, while the message is in the queue
//
#define MQMSG_CLASS_NACK_RECEIVE_TIMEOUT        MQCLASS_CODE(1, 1, 0x02)


//------ PROPID_M_ACKNOWLEDGE ---------------
#define MQMSG_ACKNOWLEDGMENT_NONE           0x00

#define MQMSG_ACKNOWLEDGMENT_POS_ARRIVAL    0x01
#define MQMSG_ACKNOWLEDGMENT_POS_RECEIVE    0x02
#define MQMSG_ACKNOWLEDGMENT_NEG_ARRIVAL    0x04
#define MQMSG_ACKNOWLEDGMENT_NEG_RECEIVE    0x08

#define MQMSG_ACKNOWLEDGMENT_NACK_REACH_QUEUE ((UCHAR)( \
            MQMSG_ACKNOWLEDGMENT_NEG_ARRIVAL ))

#define MQMSG_ACKNOWLEDGMENT_FULL_REACH_QUEUE ((UCHAR)( \
            MQMSG_ACKNOWLEDGMENT_NEG_ARRIVAL |  \
            MQMSG_ACKNOWLEDGMENT_POS_ARRIVAL ))

#define MQMSG_ACKNOWLEDGMENT_NACK_RECEIVE ((UCHAR)( \
            MQMSG_ACKNOWLEDGMENT_NEG_ARRIVAL |  \
            MQMSG_ACKNOWLEDGMENT_NEG_RECEIVE ))

#define MQMSG_ACKNOWLEDGMENT_FULL_RECEIVE ((UCHAR)( \
            MQMSG_ACKNOWLEDGMENT_NEG_ARRIVAL |  \
            MQMSG_ACKNOWLEDGMENT_NEG_RECEIVE |  \
            MQMSG_ACKNOWLEDGMENT_POS_RECEIVE ))

//------ PROPID_M_DELIVERY ------------------
#define MQMSG_DELIVERY_EXPRESS              0
#define MQMSG_DELIVERY_RECOVERABLE          1

//----- PROPID_M_JOURNAL --------------------
#define MQMSG_JOURNAL_NONE                  0
#define MQMSG_DEADLETTER                    1
#define MQMSG_JOURNAL                       2

//----- PROPID_M_TRACE ----------------------
#define MQMSG_TRACE_NONE                    0
#define MQMSG_SEND_ROUTE_TO_REPORT_QUEUE    1

//----- PROPID_M_SENDERID_TYPE --------------
#define MQMSG_SENDERID_TYPE_NONE            0
#define MQMSG_SENDERID_TYPE_SID             1

//----- PROPID_M_PRIV_LEVEL -----------------
#define MQMSG_PRIV_LEVEL_NONE               0
#define MQMSG_PRIV_LEVEL_BODY               1

//----- PROPID_M_AUTH_LEVEL -----------------
#define MQMSG_AUTH_LEVEL_NONE               0
#define MQMSG_AUTH_LEVEL_ALWAYS             1


//********************************************************************
//  QUEUE PROPERTIES
//********************************************************************
#define PROPID_Q_BASE           100
#define PROPID_Q_INSTANCE       (PROPID_Q_BASE +  1)  /* VT_CLSID     */
#define PROPID_Q_TYPE           (PROPID_Q_BASE +  2)  /* VT_CLSID     */
#define PROPID_Q_PATHNAME       (PROPID_Q_BASE +  3)  /* VT_LPWSTR    */
#define PROPID_Q_JOURNAL        (PROPID_Q_BASE +  4)  /* VT_UI1       */
#define PROPID_Q_QUOTA          (PROPID_Q_BASE +  5)  /* VT_UI4       */
#define PROPID_Q_BASEPRIORITY   (PROPID_Q_BASE +  6)  /* VT_I2        */
#define PROPID_Q_JOURNAL_QUOTA  (PROPID_Q_BASE +  7)  /* VT_UI4       */
#define PROPID_Q_LABEL          (PROPID_Q_BASE +  8)  /* VT_LPWSTR    */
#define PROPID_Q_CREATE_TIME    (PROPID_Q_BASE +  9)  /* VT_I4        */
#define PROPID_Q_MODIFY_TIME    (PROPID_Q_BASE + 10)  /* VT_I4        */
#define PROPID_Q_AUTHENTICATE   (PROPID_Q_BASE + 11)  /* VT_UI1       */
#define PROPID_Q_PRIV_LEVEL     (PROPID_Q_BASE + 12)  /* VT_UI4       */
#define PROPID_Q_TRANSACTION    (PROPID_Q_BASE + 13)  /* VT_UI1       */

//----- PROPID_Q_JOURNAL ------------------
#define MQ_JOURNAL_NONE     (unsigned char)0
#define MQ_JOURNAL          (unsigned char)1

//----- PROPID_Q_TYPE ------------------
//  {55EE8F32-CCE9-11cf-B108-0020AFD61CE9}
#define MQ_QTYPE_REPORT {0x55ee8f32, 0xcce9, 0x11cf, \
                        {0xb1, 0x8, 0x0, 0x20, 0xaf, 0xd6, 0x1c, 0xe9}}

//  {55EE8F33-CCE9-11cf-B108-0020AFD61CE9}
#define MQ_QTYPE_TEST   {0x55ee8f33, 0xcce9, 0x11cf, \
                        {0xb1, 0x8, 0x0, 0x20, 0xaf, 0xd6, 0x1c, 0xe9}}

//----- PROPID_Q_TRANSACTION ------------------
#define MQ_TRANSACTIONAL_NONE     (unsigned char)0
#define MQ_TRANSACTIONAL          (unsigned char)1

//----- PROPID_Q_AUTHENTICATE ------------------
#define MQ_AUTHENTICATE_NONE      (unsigned char)0
#define MQ_AUTHENTICATE           (unsigned char)1

//----- PROPID_Q_PRIV_LEVEL ------------------
#define MQ_PRIV_LEVEL_NONE        (unsigned long)0
#define MQ_PRIV_LEVEL_OPTIONAL    (unsigned long)1
#define MQ_PRIV_LEVEL_BODY        (unsigned long)2


//********************************************************************
//  MACHINE PROPERTIES
//********************************************************************
#define PROPID_QM_BASE 200

#define PROPID_QM_SITE_ID       (PROPID_QM_BASE + 1)  /* VT_CLSID            */
#define PROPID_QM_MACHINE_ID    (PROPID_QM_BASE + 2)  /* VT_CLSID            */
#define PROPID_QM_PATHNAME      (PROPID_QM_BASE + 3)  /* VT_LPWSTR           */
#define PROPID_QM_CONNECTION    (PROPID_QM_BASE + 4)  /* VT_LPWSTR|VT_VECTOR */
#define PROPID_QM_ENCRYPTION_PK (PROPID_QM_BASE + 5)  /* VT_BLOB             */

//
// LONG_LIVED is the default for PROPID_M_TIME_TO_REACH_QUEUE. If call
// to MQSendMessage() specify this value, or not give this property at
// all, then the actual timeout is taken from MQIS database.
//
#define LONG_LIVED    0xfffffffe

//
// Success
//
#define MQ_OK                       0L


#ifndef FACILITY_MSMQ
#define FACILITY_MSMQ               0x0E
#endif


//
//  Error
//

//
//  Values are 32 bit values layed out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//


//
// Define the severity codes
//


//
// MessageId: MQ_ERROR
//
// MessageText:
//
//  GenericError
//
#define MQ_ERROR                         0xC00E0001L

//
// MessageId: MQ_ERROR_PROPERTY
//
// MessageText:
//
//  One or more of the passed properties are invalid.
//
#define MQ_ERROR_PROPERTY                0xC00E0002L

//
// MessageId: MQ_ERROR_QUEUE_NOT_FOUND
//
// MessageText:
//
//  The queue is not registered in the DS
//
#define MQ_ERROR_QUEUE_NOT_FOUND         0xC00E0003L

//
// MessageId: MQ_ERROR_QUEUE_EXISTS
//
// MessageText:
//
//  A queue with the same pathname is already registered
//
#define MQ_ERROR_QUEUE_EXISTS            0xC00E0005L

//
// MessageId: MQ_ERROR_INVALID_PARAMETER
//
// MessageText:
//
//  An invalid parameter passed to a function.
//
#define MQ_ERROR_INVALID_PARAMETER       0xC00E0006L

//
// MessageId: MQ_ERROR_INVALID_HANDLE
//
// MessageText:
//
//  An invalid handle passed to a function.
//
#define MQ_ERROR_INVALID_HANDLE          0xC00E0007L

//
// MessageId: MQ_ERROR_OPERATION_CANCELLED
//
// MessageText:
//
//  The operation was cancelled before it could be completed.
//
#define MQ_ERROR_OPERATION_CANCELLED     0xC00E0008L

//
// MessageId: MQ_ERROR_SHARING_VIOLATION
//
// MessageText:
//
//  Sharing violation. The queue is already opened for exclusive receive.
//
#define MQ_ERROR_SHARING_VIOLATION       0xC00E0009L

//
// MessageId: MQ_ERROR_SERVICE_NOT_AVAILABLE
//
// MessageText:
//
//  The Message Queues service is not available
//
#define MQ_ERROR_SERVICE_NOT_AVAILABLE   0xC00E000BL

//
// MessageId: MQ_ERROR_MACHINE_NOT_FOUND
//
// MessageText:
//
//  The specified machine could not be found.
//
#define MQ_ERROR_MACHINE_NOT_FOUND       0xC00E000DL

//
// MessageId: MQ_ERROR_ILLEGAL_SORT
//
// MessageText:
//
//  Illegal sort specified in MQLocateBegin (e.g., duplicate columns).
//
#define MQ_ERROR_ILLEGAL_SORT            0xC00E0010L

//
// MessageId: MQ_ERROR_ILLEGAL_USER
//
// MessageText:
//
//  The user is an illegal user.
//
#define MQ_ERROR_ILLEGAL_USER            0xC00E0011L

//
// MessageId: MQ_ERROR_NO_DS
//
// MessageText:
//
//  No connection with this site's controller(s).
//
#define MQ_ERROR_NO_DS                   0xC00E0013L

//
// MessageId: MQ_ERROR_ILLEGAL_QUEUE_PATHNAME
//
// MessageText:
//
//  Illegal queue path name.
//
#define MQ_ERROR_ILLEGAL_QUEUE_PATHNAME  0xC00E0014L

//
// MessageId: MQ_ERROR_ILLEGAL_PROPERTY_VALUE
//
// MessageText:
//
//  Illegal property value.
//
#define MQ_ERROR_ILLEGAL_PROPERTY_VALUE  0xC00E0018L

//
// MessageId: MQ_ERROR_ILLEGAL_PROPERTY_VT
//
// MessageText:
//
//  Invalid VARTYPE value.
//
#define MQ_ERROR_ILLEGAL_PROPERTY_VT     0xC00E0019L

//
// MessageId: MQ_ERROR_BUFFER_OVERFLOW
//
// MessageText:
//
//  The buffer supplied to MQReceiveMessage for message body retrieval
//  was too small. The message is not removed from the queue and part
//  of the message body that fits in the buffer was copied.
//
#define MQ_ERROR_BUFFER_OVERFLOW         0xC00E001AL

//
// MessageId: MQ_ERROR_IO_TIMEOUT
//
// MessageText:
//
//  The MQReceiveMessage timeout has expired
//
#define MQ_ERROR_IO_TIMEOUT              0xC00E001BL

//
// MessageId: MQ_ERROR_ILLEGAL_CURSOR_ACTION
//
// MessageText:
//
//  MQ_ACTION_PEEK_NEXT specified to MQReceiveMessage can not be used with
//  the current cursor position.
//
#define MQ_ERROR_ILLEGAL_CURSOR_ACTION   0xC00E001CL

//
// MessageId: MQ_ERROR_MESSAGE_ALREADY_RECEIVED
//
// MessageText:
//
//  A message that is currently pointed at by the cursor has been removed from
//  the queue by another process or by another call to MQReceiveMessage
//  without the use of this cursor.
//
#define MQ_ERROR_MESSAGE_ALREADY_RECEIVED 0xC00E001DL

//
// MessageId: MQ_ERROR_ILLEGAL_FORMATNAME
//
// MessageText:
//
//  The given format name is invalid.
//
#define MQ_ERROR_ILLEGAL_FORMATNAME      0xC00E001EL

//
// MessageId: MQ_ERROR_FORMATNAME_BUFFER_TOO_SMALL
//
// MessageText:
//
//  The format name buffer supplied to the API was too small
//  to fit the format name
//
#define MQ_ERROR_FORMATNAME_BUFFER_TOO_SMALL 0xC00E001FL

//
// MessageId: MQ_ERROR_UNSUPPORTED_FORMATNAME_OPERATION
//
// MessageText:
//
//  The requested operation for the specified format name is not
//  supported (e.g., delete a direct queue format name).
//
#define MQ_ERROR_UNSUPPORTED_FORMATNAME_OPERATION 0xC00E0020L

//
// MessageId: MQ_ERROR_ILLEGAL_SECURITY_DESCRIPTOR
//
// MessageText:
//
//  The specified security descriptor is not a valid security descriptor.
//
#define MQ_ERROR_ILLEGAL_SECURITY_DESCRIPTOR 0xC00E0021L

//
// MessageId: MQ_ERROR_SENDERID_BUFFER_TOO_SMALL
//
// MessageText:
//
//  The passed buffer for the user ID property is too small.
//
#define MQ_ERROR_SENDERID_BUFFER_TOO_SMALL 0xC00E0022L

//
// MessageId: MQ_ERROR_SECURITY_DESCRIPTOR_TOO_SMALL
//
// MessageText:
//
//  The size of the buffer passed to MQGetQueueSecurity is too small.
//
#define MQ_ERROR_SECURITY_DESCRIPTOR_TOO_SMALL 0xC00E0023L

//
// MessageId: MQ_ERROR_CANNOT_IMPERSONATE_CLIENT
//
// MessageText:
//
//  The RPC server can not impersonate the client application, hence security
//  credentials could not be verified.
//
#define MQ_ERROR_CANNOT_IMPERSONATE_CLIENT 0xC00E0024L

//
// MessageId: MQ_ERROR_ACCESS_DENIED
//
// MessageText:
//
//  Access is denied.
//
#define MQ_ERROR_ACCESS_DENIED           0xC00E0025L

//
// MessageId: MQ_ERROR_PRIVILEGE_NOT_HELD
//
// MessageText:
//
//  Client does not have the required privileges to perform the operation.
//
#define MQ_ERROR_PRIVILEGE_NOT_HELD      0xC00E0026L

//
// MessageId: MQ_ERROR_INSUFFICIENT_RESOURCES
//
// MessageText:
//
//  Insufficient resources to perform operation.
//
#define MQ_ERROR_INSUFFICIENT_RESOURCES  0xC00E0027L

//
// MessageId: MQ_ERROR_USER_BUFFER_TOO_SMALL
//
// MessageText:
//
//  Request failed because user buffer is too small to hold the returned information
//
#define MQ_ERROR_USER_BUFFER_TOO_SMALL   0xC00E0028L

//
// MessageId: MQ_ERROR_MESSAGE_STORAGE_FAILED
//
// MessageText:
//
//  Could not store a recoverable or journal message. Message was not sent
//
#define MQ_ERROR_MESSAGE_STORAGE_FAILED  0xC00E002AL

//
// MessageId: MQ_ERROR_SENDER_CERT_BUFFER_TOO_SMALL
//
// MessageText:
//
//  The passed buffer for the user certificate property is too small.
//
#define MQ_ERROR_SENDER_CERT_BUFFER_TOO_SMALL 0xC00E002BL

//
// MessageId: MQ_ERROR_INVALID_CERTIFICATE
//
// MessageText:
//
//  The user certificate is not valid.
//
#define MQ_ERROR_INVALID_CERTIFICATE     0xC00E002CL

//
// MessageId: MQ_ERROR_CORRUPTED_INTERNAL_CERTIFICATE
//
// MessageText:
//
//  The internal MSMQ certificate is corrupted.
//
#define MQ_ERROR_CORRUPTED_INTERNAL_CERTIFICATE 0xC00E002DL


//
// MessageId: MQ_ERROR_NO_INTERNAL_USER_CERT
//
// MessageText:
//
//  The internal MSMQ certificate for the user does not exist.
//
#define MQ_ERROR_NO_INTERNAL_USER_CERT   0xC00E002FL

//
// MessageId: MQ_ERROR_CORRUPTED_SECURITY_DATA
//
// MessageText:
//
//  A cryptogrphic function has failed.
//
#define MQ_ERROR_CORRUPTED_SECURITY_DATA 0xC00E0030L

//
// MessageId: MQ_ERROR_CORRUPTED_PERSONAL_CERT_STORE
//
// MessageText:
//
//  The personal certificate store is corrupted.
//
#define MQ_ERROR_CORRUPTED_PERSONAL_CERT_STORE 0xC00E0031L

//
// MessageId: MQ_ERROR_COMPUTER_DOES_NOT_SUPPORT_ENCRYPTION
//
// MessageText:
//
//  The computer does not support encryption operations.
//
#define MQ_ERROR_COMPUTER_DOES_NOT_SUPPORT_ENCRYPTION 0xC00E0033L

//
// MessageId: MQ_ERROR_BAD_SECURITY_CONTEXT
//
// MessageText:
//
//  Bad security context.
//
#define MQ_ERROR_BAD_SECURITY_CONTEXT    0xC00E0035L

//
// MessageId: MQ_ERROR_COULD_NOT_GET_USER_SID
//
// MessageText:
//
//  Could not get the SID information out of the thread token.
//
#define MQ_ERROR_COULD_NOT_GET_USER_SID  0xC00E0036L

//
// MessageId: MQ_ERROR_COULD_NOT_GET_ACCOUNT_INFO
//
// MessageText:
//
//  Could not get the account information for the user.
//
#define MQ_ERROR_COULD_NOT_GET_ACCOUNT_INFO 0xC00E0037L

//
// MessageId: MQ_ERROR_ILLEGAL_MQCOLUMNS
//
// MessageText:
//
//  Invalid MQCOLUMNS parameter
//
#define MQ_ERROR_ILLEGAL_MQCOLUMNS       0xC00E0038L

//
// MessageId: MQ_ERROR_ILLEGAL_PROPID
//
// MessageText:
//
//  Invalid propid value
//
#define MQ_ERROR_ILLEGAL_PROPID          0xC00E0039L

//
// MessageId: MQ_ERROR_ILLEGAL_RELATION
//
// MessageText:
//
//  Invalid relation value in restriction
//
#define MQ_ERROR_ILLEGAL_RELATION        0xC00E003AL

//
// MessageId: MQ_ERROR_ILLEGAL_PROPERTY_SIZE
//
// MessageText:
//
//  Illegal property buffer size
//
#define MQ_ERROR_ILLEGAL_PROPERTY_SIZE   0xC00E003BL

//
// MessageId: MQ_ERROR_ILLEGAL_RESTRICTION_PROPID
//
// MessageText:
//
//  Invalid propid value in MQRESTRICTION parameter
//
#define MQ_ERROR_ILLEGAL_RESTRICTION_PROPID 0xC00E003CL

//
// MessageId: MQ_ERROR_ILLEGAL_MQQUEUEPROPS
//
// MessageText:
//
//  Illegal MQQUEUEPROPS parameter, either null or with zero properties
//
#define MQ_ERROR_ILLEGAL_MQQUEUEPROPS    0xC00E003DL

//
// MessageId: MQ_ERROR_PROPERTY_NOTALLOWED
//
// MessageText:
//
//  Invalid propid for the requested operation (e.g. PROPID_Q_INSTANCE
//  in MQSetQueueProperties)
//
#define MQ_ERROR_PROPERTY_NOTALLOWED     0xC00E003EL

//
// MessageId: MQ_ERROR_INSUFFICIENT_PROPERTIES
//
// MessageText:
//
//  Not all the required properties for the operation were specified
//  in the input parameters
//
#define MQ_ERROR_INSUFFICIENT_PROPERTIES 0xC00E003FL

//
// MessageId: MQ_ERROR_MACHINE_EXISTS
//
// MessageText:
//
//  Computer with the same name already exists in the site.
//
#define MQ_ERROR_MACHINE_EXISTS          0xC00E0040L

//
// MessageId: MQ_ERROR_ILLEGAL_MQQMPROPS
//
// MessageText:
//
//  Illegal MQQMPROPS parameter, either null or with zero properties
//
#define MQ_ERROR_ILLEGAL_MQQMPROPS       0xC00E0041L

//
// MessageId: MQ_ERROR_DS_IS_FULL
//
// MessageText:
//
//  DS is full
//
#define MQ_ERROR_DS_IS_FULL              0xC00E0042L

//
// MessageId: MQ_ERROR_DS_ERROR
//
// MessageText:
//
//  Internal DS error.
//
#define MQ_ERROR_DS_ERROR                0xC00E0043L

//
// MessageId: MQ_ERROR_INVALID_OWNER
//
// MessageText:
//
//  Invalid object owner. For example MQCreateQueue failed because the QM
//  object is invalid
//
#define MQ_ERROR_INVALID_OWNER           0xC00E0044L

//
// MessageId: MQ_ERROR_UNSUPPORTED_ACCESS_MODE
//
// MessageText:
//
//  The specified access mode is not supported.
//
#define MQ_ERROR_UNSUPPORTED_ACCESS_MODE 0xC00E0045L

//
// MessageId: MQ_ERROR_RESULT_BUFFER_TOO_SMALL
//
// MessageText:
//
//  The supplied result buffer is too small
//
#define MQ_ERROR_RESULT_BUFFER_TOO_SMALL 0xC00E0046L

//
// MessageId: MQ_ERROR_DELETE_CN_IN_USE
//
// MessageText:
//
//  The Connected Network can not be deleted, it is in use.
//
#define MQ_ERROR_DELETE_CN_IN_USE        0xC00E0048L

//
// MessageId: MQ_ERROR_NO_RESPONSE_FROM_OBJECT_SERVER
//
// MessageText:
//
//  No response from object owner.
//
#define MQ_ERROR_NO_RESPONSE_FROM_OBJECT_SERVER 0xC00E0049L

//
// MessageId: MQ_ERROR_OBJECT_SERVER_NOT_AVAILABLE
//
// MessageText:
//
//  Object owner is not reachable.
//
#define MQ_ERROR_OBJECT_SERVER_NOT_AVAILABLE 0xC00E004AL

//
// MessageId: MQ_ERROR_QUEUE_NOT_AVAILABLE
//
// MessageText:
//
//  Error while reading from a queue residing on a remote computer
//
#define MQ_ERROR_QUEUE_NOT_AVAILABLE     0xC00E004BL

//
// MessageId: MQ_ERROR_DTC_CONNECT
//
// MessageText:
//
//  Cannot connect to MS DTC
//
#define MQ_ERROR_DTC_CONNECT             0xC00E004CL

//
// MessageId: MQ_ERROR_TRANSACTION_IMPORT
//
// MessageText:
//
//  Cannot import the transaction
//
#define MQ_ERROR_TRANSACTION_IMPORT      0xC00E004EL

//
// MessageId: MQ_ERROR_TRANSACTION_USAGE
//
// MessageText:
//
//  Wrong transaction usage
//
#define MQ_ERROR_TRANSACTION_USAGE       0xC00E0050L

//
// MessageId: MQ_ERROR_TRANSACTION_SEQUENCE
//
// MessageText:
//
//  Wrong transaction operations sequence
//
#define MQ_ERROR_TRANSACTION_SEQUENCE    0xC00E0051L

//
// MessageId: MQ_ERROR_MISSING_CONNECTOR_TYPE
//
// MessageText:
//
//  Connector Type is mandatory when sending Acknowledgment or secure message
//
#define MQ_ERROR_MISSING_CONNECTOR_TYPE  0xC00E0055L

//
// MessageId: MQ_ERROR_STALE_HANDLE
//
// MessageText:
//
//  The Queue manager service has been restarted. The queue handle
//  is stale, and should be closed.
//
#define MQ_ERROR_STALE_HANDLE            0xC00E0056L

//
// MessageId: MQ_ERROR_TRANSACTION_ENLIST
//
// MessageText:
//
//  Cannot enlist the transaction
//
#define MQ_ERROR_TRANSACTION_ENLIST      0xC00E0058L

//
// MessageId: MQ_ERROR_QUEUE_DELETED
//
// MessageText:
//
//  The queue was deleted. Messages can not be received anymore using this
//  queue handle. The handle should be closed
//
#define MQ_ERROR_QUEUE_DELETED           0xC00E005AL

//
// MessageId: MQ_ERROR_ILLEGAL_CONTEXT
//
// MessageText:
//
//  Invalid context parameter (MQLocateBegin).
//
#define MQ_ERROR_ILLEGAL_CONTEXT         0xC00E005BL

//
// MessageId: MQ_ERROR_ILLEGAL_SORT_PROPID
//
// MessageText:
//
//  Invalid propid value in MQSORTSET
//
#define MQ_ERROR_ILLEGAL_SORT_PROPID     0xC00E005CL

//
// MessageId: MQ_ERROR_LABEL_TOO_LONG
//
// MessageText:
//
//  The passed label is too long. It should be less or equal to MQ_MAX_MSG_LABEL_LEN
//
#define MQ_ERROR_LABEL_TOO_LONG          0xC00E005DL

//
// MessageId: MQ_ERROR_LABEL_BUFFER_TOO_SMALL
//
// MessageText:
//
//  The label buffer supplied to the API was too small
//
#define MQ_ERROR_LABEL_BUFFER_TOO_SMALL  0xC00E005EL

//
// MessageId: MQ_ERROR_MQIS_SERVER_EMPTY
//
// MessageText:
//
//  The list of MQIS servers (in registry) is empty.
//
#define MQ_ERROR_MQIS_SERVER_EMPTY       0xC00E005FL

//
// MessageId: MQ_ERROR_MQIS_READONLY_MODE
//
// MessageText:
//
//  MQIS database is in read-only mode.
//
#define MQ_ERROR_MQIS_READONLY_MODE      0xC00E0060L

//
// MessageId: MQ_ERROR_SYMM_KEY_BUFFER_TOO_SMALL
//
// MessageText:
//
//  The passed buffer for the Symmetric key property is too small.
//
#define MQ_ERROR_SYMM_KEY_BUFFER_TOO_SMALL 0xC00E0061L

//
// MessageId: MQ_ERROR_SIGNATURE_BUFFER_TOO_SMALL
//
// MessageText:
//
//  The passed buffer for the Signature property is too small.
//
#define MQ_ERROR_SIGNATURE_BUFFER_TOO_SMALL 0xC00E0062L

//
// MessageId: MQ_ERROR_PROV_NAME_BUFFER_TOO_SMALL
//
// MessageText:
//
//  The passed buffer for the Provider name property is too small.
//
#define MQ_ERROR_PROV_NAME_BUFFER_TOO_SMALL 0xC00E0063L

//
// MessageId: MQ_ERROR_ILLEGAL_OPERATION
//
// MessageText:
//
//  The operation is illegal on foreign message queuing system
//
#define MQ_ERROR_ILLEGAL_OPERATION       0xC00E0064L

//
// MessageId: MQ_ERROR_WRITE_NOT_ALLOWED
//
// MessageText:
//
//  Another MQIS server is being installed, write operations to the
//  database are not allowed at this stage.
//
#define MQ_ERROR_WRITE_NOT_ALLOWED       0xC00E0065L

//
// MessageId: MQ_ERROR_WKS_CANT_SERVE_CLIENT
//
// MessageText:
//
//  MSMQ independent clients cannot serve MSMQ dependent clients.
//
#define MQ_ERROR_WKS_CANT_SERVE_CLIENT   0xC00E0066L

//
//
// MessageId: MQ_ERROR_DEPEND_WKS_LICENSE_OVERFLOW
//
// MessageText:
//
//  The number of dependent clients served by this MSMQ server reached
//  its upper limit.
//
#define MQ_ERROR_DEPEND_WKS_LICENSE_OVERFLOW 0xC00E0067L

//
//
// MessageId: MQ_CORRUPTED_QUEUE_WAS_DELETED
//
// MessageText:
//
//  Ini file for queue %1 in LQS was deleted because it was corrupted.
//
#define MQ_CORRUPTED_QUEUE_WAS_DELETED   0xC00E0068L

//
//
// MessageId: MQ_ERROR_REMOTE_MACHINE_NOT_AVAILABLE
//
// MessageText:
//
//  The remote machine is not available.
//
#define MQ_ERROR_REMOTE_MACHINE_NOT_AVAILABLE 0xC00E0069L

//
// Informational
//
//
// MessageId: MQ_INFORMATION_PROPERTY
//
// MessageText:
//
//  One or more of the passed properties resulted in warning but the
//  function completed.
//
#define MQ_INFORMATION_PROPERTY          0x400E0001L

//
// MessageId: MQ_INFORMATION_ILLEGAL_PROPERTY
//
// MessageText:
//
//  Invalid property id.
//
#define MQ_INFORMATION_ILLEGAL_PROPERTY  0x400E0002L

//
// MessageId: MQ_INFORMATION_PROPERTY_IGNORED
//
// MessageText:
//
//  The specified property is ignored in this operation
//  (e.g., PROPID_M_SENDERID in SendMessage().
//
#define MQ_INFORMATION_PROPERTY_IGNORED  0x400E0003L

//
// MessageId: MQ_INFORMATION_UNSUPPORTED_PROPERTY
//
// MessageText:
//
//  The specified property is not supported and is ignored in this operation
//
#define MQ_INFORMATION_UNSUPPORTED_PROPERTY 0x400E0004L

//
// MessageId: MQ_INFORMATION_DUPLICATE_PROPERTY
//
// MessageText:
//
//  The specified property already appeared in the propid array, and is
//  ignored in this operation
//
#define MQ_INFORMATION_DUPLICATE_PROPERTY 0x400E0005L

//
// MessageId: MQ_INFORMATION_OPERATION_PENDING
//
// MessageText:
//
//  Asynchronous operation is currently pending.
//
#define MQ_INFORMATION_OPERATION_PENDING 0x400E0006L

//
// MessageId: MQ_INFORMATION_FORMATNAME_BUFFER_TOO_SMALL
//
// MessageText:
//
//  The format name buffer supplied to MQCreateQueue was too small
//  to fit the format name. Queue was created successfully
//
#define MQ_INFORMATION_FORMATNAME_BUFFER_TOO_SMALL 0x400E0009L



//********************************************************************
//  SECURITY FLAGS
//********************************************************************
#define MQSEC_DELETE_MESSAGE                0x1
#define MQSEC_PEEK_MESSAGE                  0x2
#define MQSEC_WRITE_MESSAGE                 0x4
#define MQSEC_DELETE_JOURNAL_MESSAGE        0x8
#define MQSEC_SET_QUEUE_PROPERTIES          0x10
#define MQSEC_GET_QUEUE_PROPERTIES          0x20
#define MQSEC_DELETE_QUEUE                  DELETE
#define MQSEC_GET_QUEUE_PERMISSIONS         READ_CONTROL
#define MQSEC_CHANGE_QUEUE_PERMISSIONS      WRITE_DAC
#define MQSEC_TAKE_QUEUE_OWNERSHIP          WRITE_OWNER

#define MQSEC_RECEIVE_MESSAGE               (MQSEC_DELETE_MESSAGE | \
                                             MQSEC_PEEK_MESSAGE)

#define MQSEC_RECEIVE_JOURNAL_MESSAGE       (MQSEC_DELETE_JOURNAL_MESSAGE | \
                                             MQSEC_PEEK_MESSAGE)

#define MQSEC_QUEUE_GENERIC_READ            (MQSEC_GET_QUEUE_PROPERTIES | \
                                             MQSEC_GET_QUEUE_PERMISSIONS | \
                                             MQSEC_RECEIVE_MESSAGE | \
                                             MQSEC_RECEIVE_JOURNAL_MESSAGE)

#define MQSEC_QUEUE_GENERIC_WRITE           (MQSEC_GET_QUEUE_PROPERTIES | \
                                             MQSEC_GET_QUEUE_PERMISSIONS | \
                                             MQSEC_WRITE_MESSAGE)

#define MQSEC_QUEUE_GENERIC_EXECUTE         0

#define MQSEC_QUEUE_GENERIC_ALL             (MQSEC_RECEIVE_MESSAGE | \
                                             MQSEC_RECEIVE_JOURNAL_MESSAGE | \
                                             MQSEC_WRITE_MESSAGE | \
                                             MQSEC_SET_QUEUE_PROPERTIES | \
                                             MQSEC_GET_QUEUE_PROPERTIES | \
                                             MQSEC_DELETE_QUEUE | \
                                             MQSEC_GET_QUEUE_PERMISSIONS | \
                                             MQSEC_CHANGE_QUEUE_PERMISSIONS | \
                                             MQSEC_TAKE_QUEUE_OWNERSHIP)

#ifdef __cplusplus
extern "C"
{
#endif

//********************************************************************
//  RECEIVE CALLBACK
//********************************************************************

typedef
VOID
(APIENTRY *PMQRECEIVECALLBACK)(
    HRESULT hrStatus,
    QUEUEHANDLE hSource,
    DWORD dwTimeout,
    DWORD dwAction,
    MQMSGPROPS* pMessageProps,
    LPOVERLAPPED lpOverlapped,
    HANDLE hCursor
    );


//********************************************************************
// MSMQ API
//********************************************************************

HRESULT
APIENTRY
MQCreateQueue(
    IN PSECURITY_DESCRIPTOR pSecurityDescriptor,
    IN OUT MQQUEUEPROPS* pQueueProps,
    OUT LPWSTR lpwcsFormatName,
    IN OUT LPDWORD lpdwFormatNameLength
    );

HRESULT
APIENTRY
MQDeleteQueue(
    IN LPCWSTR lpwcsFormatName
    );

HRESULT
APIENTRY
MQLocateBegin(
    IN LPCWSTR lpwcsContext,
    IN MQRESTRICTION* pRestriction,
    IN MQCOLUMNSET* pColumns,
    IN MQSORTSET* pSort,
    OUT PHANDLE phEnum
    );

HRESULT
APIENTRY
MQLocateNext(
    IN HANDLE hEnum,
    IN OUT DWORD* pcProps,
    OUT MQPROPVARIANT aPropVar[]
    );

HRESULT
APIENTRY
MQLocateEnd(
    IN HANDLE hEnum
    );

HRESULT
APIENTRY
MQOpenQueue(
    IN LPCWSTR lpwcsFormatName,
    IN DWORD dwAccess,
    IN DWORD dwShareMode,
    OUT QUEUEHANDLE* phQueue
    );

HRESULT
APIENTRY
MQSendMessage(
    IN QUEUEHANDLE hDestinationQueue,
    IN MQMSGPROPS* pMessageProps,
    IN ITransaction *pTransaction
    );

HRESULT
APIENTRY
MQReceiveMessage(
    IN QUEUEHANDLE hSource,
    IN DWORD dwTimeout,
    IN DWORD dwAction,
    IN OUT MQMSGPROPS* pMessageProps,
    IN OUT LPOVERLAPPED lpOverlapped,
    IN PMQRECEIVECALLBACK fnReceiveCallback,
    IN HANDLE hCursor,
    IN ITransaction* pTransaction
    );

HRESULT
APIENTRY
MQCreateCursor(
    IN QUEUEHANDLE hQueue,
    OUT PHANDLE phCursor
    );

HRESULT
APIENTRY
MQCloseCursor(
    IN HANDLE hCursor
    );

HRESULT
APIENTRY
MQCloseQueue(
    IN HANDLE hQueue
    );

HRESULT
APIENTRY
MQSetQueueProperties(
    IN LPCWSTR lpwcsFormatName,
    IN MQQUEUEPROPS* pQueueProps
    );

HRESULT
APIENTRY
MQGetQueueProperties(
    IN LPCWSTR lpwcsFormatName,
    OUT MQQUEUEPROPS* pQueueProps
    );

HRESULT
APIENTRY
MQGetQueueSecurity(
    IN LPCWSTR lpwcsFormatName,
    IN SECURITY_INFORMATION RequestedInformation,
    OUT PSECURITY_DESCRIPTOR pSecurityDescriptor,
    IN DWORD nLength,
    OUT LPDWORD lpnLengthNeeded
    );

HRESULT
APIENTRY
MQSetQueueSecurity(
    IN LPCWSTR lpwcsFormatName,
    IN SECURITY_INFORMATION SecurityInformation,
    IN PSECURITY_DESCRIPTOR pSecurityDescriptor
    );

HRESULT
APIENTRY
MQPathNameToFormatName(
    IN LPCWSTR lpwcsPathName,
    OUT LPWSTR lpwcsFormatName,
    IN OUT LPDWORD lpdwFormatNameLength
    );

HRESULT
APIENTRY
MQHandleToFormatName(
    IN QUEUEHANDLE hQueue,
    OUT LPWSTR lpwcsFormatName,
    IN OUT LPDWORD lpdwFormatNameLength
    );

HRESULT
APIENTRY
MQInstanceToFormatName(
    IN GUID* pGuid,
    OUT LPWSTR lpwcsFormatName,
    IN OUT LPDWORD lpdwFormatNameLength
    );

void
APIENTRY
MQFreeMemory(
    IN PVOID pvMemory
    );

HRESULT
APIENTRY
MQGetMachineProperties(
    IN LPCWSTR lpwcsMachineName,
    IN const GUID* pguidMachineId,
    IN OUT MQQMPROPS* pQMProps
    );

HRESULT
APIENTRY
MQGetSecurityContext(
    IN PVOID lpCertBuffer,
    IN DWORD dwCertBufferLength,
    OUT HANDLE* hSecurityContext
    );

void
APIENTRY
MQFreeSecurityContext(
    IN HANDLE hSecurityContext
    );

HRESULT
APIENTRY
MQBeginTransaction(
    OUT ITransaction **ppTransaction
    );


#ifdef __cplusplus
}
#endif

#endif // __MQ_H__

