/*++

Copyright 1997 - 1998 Microsoft Corporation

Module Name:

    qos.h - QoS definitions for NDIS components.

Abstract:

    This module defines the Quality of Service structures and types used
    by Winsock applications.

Revision History:

--*/

#ifndef __QOS_H_
#define __QOS_H_


/*
 *  Definitions for Service Type for each direction of data flow.
 */
typedef ULONG   SERVICETYPE;
#define SERVICETYPE_NOTRAFFIC               0x00000000  /* No data in this
                                                         * direction */
#define SERVICETYPE_BESTEFFORT              0x00000001  /* Best Effort */
#define SERVICETYPE_CONTROLLEDLOAD          0x00000002  /* Controlled Load */
#define SERVICETYPE_GUARANTEED              0x00000003  /* Guaranteed */
#define SERVICETYPE_NETWORK_UNAVAILABLE     0x00000004  /* Used to notify 
                                                         * change to user */
#define SERVICETYPE_GENERAL_INFORMATION     0x00000005  /* corresponds to 
                                                         * "General Parameters"
                                                         * defined by IntServ */
#define SERVICETYPE_NOCHANGE                0x00000006  /* used to indicate
                                                         * that the flow spec
                                                         * contains no change
                                                         * from any previous
                                                         * one */

/*
 * to turn on immediate traffic control, OR ( | ) this flag with the 
 * ServiceType field in the FLOWSPEC
 */
#define SERVICE_IMMEDIATE_TRAFFIC_CONTROL   0x80000000

/*
 * this flag can be used with the immediate traffic control flag above to
 * prevent any rsvp signaling messages from being sent. Local traffic 
 * control will be invoked, but no RSVP Path messages will be sent.This flag
 * can also be used in conjunction with a receiving flowspec to suppress 
 * the automatic generation of a Reserve message.  The application would 
 * receive notification that a Path  message had arrived and would then need
 * to alter the QOS by issuing WSAIoctl( SIO_SET_QOS ), to unset this flag 
 * and thereby cause Reserve messages to go out.
 */
#define SERVICE_NO_QOS_SIGNALING   0x40000000

/*
 *  Flow Specifications for each direction of data flow.
 */
typedef struct _flowspec
{
    ULONG       TokenRate;              /* In Bytes/sec */
    ULONG       TokenBucketSize;        /* In Bytes */
    ULONG       PeakBandwidth;          /* In Bytes/sec */
    ULONG       Latency;                /* In microseconds */
    ULONG       DelayVariation;         /* In microseconds */
    SERVICETYPE ServiceType;
    ULONG       MaxSduSize;             /* In Bytes */
    ULONG       MinimumPolicedSize;     /* In Bytes */

} FLOWSPEC, *PFLOWSPEC, * LPFLOWSPEC;

/*
 * the provider specific structure can have a number of objects in it.
 * Each next structure in the
 * ProviderSpecific will be the QOS_OBJECT_HDR struct that prefaces the actual
 * data with a type and length for that object.  This QOS_OBJECT struct can 
 * repeat several times if there are several objects.  This list of objects
 * terminates either when the buffer length has been reached ( WSABUF ) or
 * an object of type QOS_END_OF_LIST is encountered.
 */

/*
 * define the type of objects that can go into the ProviderSpecific buffer 
 * in the QOS structure
 */

typedef struct  {

    ULONG   ObjectType;
    ULONG   ObjectLength;  /* the length of object buffer INCLUDING 
                            * this header */

} QOS_OBJECT_HDR, *LPQOS_OBJECT_HDR;

/*
 * Definition of object Types
 *
 *
 * define the values for ObjectType above - RSVP Objects ids start at an 
 * offset from zero to allow for ATM objects that might be defined in the 
 * lower number range.
 */
#define   RSVP_OBJECT_ID_BASE         1000
#define   RSVP_OBJECT_STATUS_INFO     (0x00000000 + RSVP_OBJECT_ID_BASE)
          /* RSVP_STATUS_INFO structure passed */
#define   RSVP_OBJECT_RESERVE_INFO    (0x00000001 + RSVP_OBJECT_ID_BASE)
          /* RSVP_RESERVE_INFO structure passed */
#define   RSVP_OBJECT_ADSPEC          (0x00000002 + RSVP_OBJECT_ID_BASE)
          /* RSVP_ADSPEC structure passed */

/*
 * general QOS objects start at this offset from the base and have a range 
 * of 1000
 */
#define   QOS_GENERAL_ID_BASE         2000
#define   QOS_OBJECT_PRIORITY         (0x00000000 + QOS_GENERAL_ID_BASE)
          /* QOS_PRIORITY structure passed */
#define   QOS_OBJECT_END_OF_LIST      (0x00000001 + QOS_GENERAL_ID_BASE) 
          /* QOS_End_of_list structure passed */
#define   QOS_OBJECT_SD_MODE          (0x00000002 + QOS_GENERAL_ID_BASE) 
          /* QOS_ShapeDiscard structure passed */
#define   QOS_OBJECT_TRAFFIC_CLASS    (0x00000003 + QOS_GENERAL_ID_BASE) 
          /* QOS_Traffic class structure passed */

/*
 * this value can be used in the FLOWSPEC structure to instruct the Rsvp Service 
 * provider to derive the appropriate default value for the parameter.  Note 
 * that not all values in the FLOWSPEC structure can be defaults. In the
 * ReceivingFlowspec, all parameters can be defaulted except the ServiceType.  
 * In the SendingFlowspec, the MaxSduSize and MinimumPolicedSize can be
 * defaulted. Other defaults may be possible. Refer to the appropriate
 * documentation.
 */
#define QOS_NOT_SPECIFIED     0xFFFFFFFF

/*
 * define a value that can be used for the PeakBandwidth, which will map into 
 * positive infinity when the FLOWSPEC is converted into IntServ floating point 
 * format.  We can't use (-1) because that value was previously defined to mean
 * "select the default".
 */
#define   POSITIVE_INFINITY_RATE     0xFFFFFFFE

/* 
 * IPV6 addressing for RSVP FILTERSPECS
 */
typedef union _IN_ADDR_IPV4 {

    ULONG  Addr;
    UCHAR  AddrBytes[4];

} IN_ADDR_IPV4, *LPIN_ADDR_IPV4;

/*
 * IPV6 addressing for RSVP FILTERSPECS
 */
typedef struct _IN_ADDR_IPV6 {

    UCHAR  Addr[16];               //IPV6 address

} IN_ADDR_IPV6, *LPIN_ADDR_IPV6;

typedef const IN_ADDR_IPV6  *LPCIN_ADDR_IPV6;

/*
 * IPV4 addressing for RSVP FILTERSPECS
 */
typedef struct _RSVP_FILTERSPEC_V4 {

    IN_ADDR_IPV4    Address;
    USHORT          Unused;
    USHORT          Port;

} RSVP_FILTERSPEC_V4, *LPRSVP_FILTERSPEC_V4;

typedef struct _RSVP_FILTERSPEC_V6 {

    IN_ADDR_IPV6    Address;
    USHORT          UnUsed;
    USHORT          Port;

} RSVP_FILTERSPEC_V6, *LPRSVP_FILTERSPEC_V6;


typedef struct _RSVP_FILTERSPEC_V6_FLOW {

    IN_ADDR_IPV6    Address;
    UCHAR           UnUsed;
    UCHAR           FlowLabel[3];

} RSVP_FILTERSPEC_V6_FLOW, *LPRSVP_FILTERSPEC_V6_FLOW;

typedef struct _RSVP_FILTERSPEC_V4_GPI {

    IN_ADDR_IPV4    Address;
    ULONG           GeneralPortId;

} RSVP_FILTERSPEC_V4_GPI, *LPRSVP_FILTERSPEC_V4_GPI;

typedef struct _RSVP_FILTERSPEC_V6_GPI {

    IN_ADDR_IPV6    Address;
    ULONG           GeneralPortId;

} RSVP_FILTERSPEC_V6_GPI, *LPRSVP_FILTERSPEC_V6_GPI;


/*
 * FILTERSPEC TYPES used in making reservations.
 */
typedef enum {

        FILTERSPECV4 = 1,
        FILTERSPECV6,
        FILTERSPECV6_FLOW,
        FILTERSPECV4_GPI,
        FILTERSPECV6_GPI,
        FILTERSPEC_END

} FilterType;

typedef struct _RSVP_FILTERSPEC {

    FilterType   Type;

    union {
        RSVP_FILTERSPEC_V4      FilterSpecV4;
        RSVP_FILTERSPEC_V6      FilterSpecV6;
        RSVP_FILTERSPEC_V6_FLOW FilterSpecV6Flow;
        RSVP_FILTERSPEC_V4_GPI  FilterSpecV4Gpi;
        RSVP_FILTERSPEC_V6_GPI  FilterSpecV6Gpi;
    };

} RSVP_FILTERSPEC, *LPRSVP_FILTERSPEC;

/*
 * FLOWDESCRIPTOR Structure used for specifying one or more
 * Filters per Flowspec.
 */
typedef struct _FLOWDESCRIPTOR {

    FLOWSPEC            FlowSpec;
    ULONG               NumFilters;
    LPRSVP_FILTERSPEC   FilterList;

} FLOWDESCRIPTOR, *LPFLOWDESCRIPTOR;

/*
 * RSVP_POLICY contains undefined policy data.  RSVP transports this
 * data on behalf of the Policy Control component.
 */
typedef struct _RSVP_POLICY {

    HANDLE       Type;              /* Pointer to structure: TBD */

} RSVP_POLICY, *LPRSVP_POLICY;

typedef const RSVP_POLICY *LPCRSVP_POLICY;


/*
 * RSVP_RESERVE_INFO Structure used for storing RSVP specific
 * information for fine tuning interaction via the Winsock2
 * Generic QoS API via the provider specific buffer. This structure
 * includes the QOS_OBJECT_HDR structure directly
 */

typedef struct _RSVP_RESERVE_INFO {

    QOS_OBJECT_HDR      ObjectHdr;            /* type and length of this object */
    ULONG               Style;                /* RSVP Style (FF,WF,SE) */
    ULONG               ConfirmRequest;       /* Non Zero for Confirm Request */
    LPRSVP_POLICY       Policy;               /* Optional policy data */
    ULONG               NumFlowDesc;          /* Number of FlowDesc */
    LPFLOWDESCRIPTOR    FlowDescList;         /* FlowDesc list */

} RSVP_RESERVE_INFO, *LPRSVP_RESERVE_INFO;

typedef const RSVP_RESERVE_INFO *LPCRSVP_RESERVE_INFO;

/*
 * definitions for the ulStyle in the previous structure
 */
#define RSVP_WILDCARD_STYLE           0x00000001
#define RSVP_FIXED_FILTER_STYLE       0x00000002
#define RSVP_SHARED_EXPLICIT_STYLE    0x00000003

/*
 * RSVP_STATUS_INFO Structure used for storing RSVP specific
 * error of status indications.  This also serves as a header
 * for additional objects in the provider specific buffer when
 * interacting via Winsock2 Generic QoS API. This structure includes
 * the QOS_OBJECT_COUNT and QOS_OBJECT_HDR structures directly It is
 * expected to be the first structure in the provider specific structure
 * since it includes the QOS_OBJECT_COUNT
 */

typedef struct _RSVP_STATUS_INFO {

    QOS_OBJECT_HDR      ObjectHdr;      /* Object Hdr */
    ULONG               StatusCode;     /* Error or Status Information see 
                                         * Winsock2.h */
    ULONG               ExtendedStatus1;/* Provider specific status extension */
    ULONG               ExtendedStatus2;/* Provider specific status extension */

} RSVP_STATUS_INFO, *LPRSVP_STATUS_INFO;

typedef const RSVP_STATUS_INFO *LPCRSVP_STATUS_INFO;

/*
 * This structure defines the absolute priorty of the flow.  Priorities in the 
 * range of 0-7 are currently defined. Receive Priority is not currently used, 
 * but may at some point in the future.
 */
typedef struct _QOS_PRIORITY {

    QOS_OBJECT_HDR  ObjectHdr;
    UCHAR           SendPriority;     /* this gets mapped to layer 2 priority.*/
    UCHAR           SendFlags;        /* there are none currently defined.*/
    UCHAR           ReceivePriority;  /* this could be used to decide who 
                                       * gets forwarded up the stack first 
                                       * - not used now */
    UCHAR           Unused;

} QOS_PRIORITY, *LPQOS_PRIORITY;


/*
 * This structure is used to define the behaviour that the traffic
 * control packet shaper will apply to the flow.
 *
 * PS_NONCONF_BORROW - the flow will receive resources remaining 
 *  after all higher priority flows have been serviced. If a 
 *  TokenRate is specified, packets may be non-conforming and
 *  will be demoted to less than best-effort priority.
 *  
 * PS_NONCONF_SHAPE - TokenRate must be specified. Non-conforming
 *  packets will be retianed in the packet shaper until they become
 *  conforming.
 *
 * PS_NONCONF_DISCARD - TokenRate must be specified. Non-conforming
 *  packets will be discarded.
 *
 */


typedef struct _QOS_SD_MODE {

    QOS_OBJECT_HDR ObjectHdr;
    ULONG   ShapeDiscardMode;

} QOS_SD_MODE, *LPQOS_SD_MODE;

#define TC_NONCONF_BORROW   0
#define TC_NONCONF_SHAPE    1
#define TC_NONCONF_DISCARD  2

/*
 * This structure may carry an 802.1 TrafficClass parameter which 
 * has been provided to the host by a layer 2 network, for example, 
 * in an 802.1 extended RSVP RESV message. If this object is obtained
 * from the network, hosts will stamp the MAC headers of corresponding
 * transmitted packets, with the value in the object. Otherwise, hosts
 * may select a value based on the standard Intserv mapping of 
 * ServiceType to 802.1 TrafficClass.
 *
 */

typedef struct _QOS_TRAFFIC_CLASS {

    QOS_OBJECT_HDR ObjectHdr;
    ULONG   TrafficClass;

} QOS_TRAFFIC_CLASS, *LPQOS_TRAFFIC_CLASS;

/*
 * this structure defines the "General Characterization Parameters" contained in
 * the RSVP Adspec object
 */
typedef struct _AD_GENERAL_PARAMS{

    ULONG       IntServAwareHopCount;   /* number of hops that conform to
                                         * Integrated Services requirements */
    ULONG       PathBandwidthEstimate;  /* minimum bandwidth available from 
                                         * sender to receiver */
    ULONG       MinimumLatency;         /* sum of minimum latency of the packet
                                         * forwarding process in routers 
                                         * (in usec)*/
    ULONG       PathMTU;                /* max transmission unit end to end that
                                         * will not incur fragmentation */
    ULONG       Flags;                  /* used to hold break bits.*/

} AD_GENERAL_PARAMS, *LPAD_GENERAL_PARAMS;

/*
 * Minimum Latency may be set to this "undefined" value
 */
#define INDETERMINATE_LATENCY   0xFFFFFFFF;

/*
 * This Flag is used to indicate the existence of a network element not 
 * supporting  QoS control services somewhere in the data path. If this bit 
 * is set in the specific service override then it indicates that that
 * service was not supported at at least one hop.
 */
#define AD_FLAG_BREAK_BIT    0x00000001

/*
 * this structure describes the Guaranteed service parameters
 */
typedef struct _AD_GUARANTEED {

    ULONG       CTotal;
    ULONG       DTotal;
    ULONG       CSum;
    ULONG       DSum;

} AD_GUARANTEED, *LPAD_GUARANTEED;

/*
 * this structure describes the format of the parameter buffer that can be
 * included in the Service_Type structure below.  This structure allows an
 * application to include any valid Int Serv service parameter in the Buffer 
 * value, after providing the Int Serv parameter id in the ParameterId field.
 */
typedef struct _PARAM_BUFFER {

    ULONG   ParameterId;    /* Int Server parameter ID */
    ULONG   Length;         /* total length of this structure 
                             * ( 8 bytes + length of Buffer ) */
    UCHAR   Buffer[1];      /* Paramter itself */

} PARAM_BUFFER, *LPPARAM_BUFFER;

/*
 * this structure contains the service types supported
 */
typedef struct _CONTROL_SERVICE {

    /*
     * the length of this entire structure including the following buffer.  
     * This length value can be added to the ptr to the structure to get the ptr
     * to the next SERVICE_TYPE structure in the list, until the
     * NumberOfServices count has been exhausted.
     */
    ULONG               Length;

    SERVICETYPE         Service;
    AD_GENERAL_PARAMS   Overrides;

    /*
     * service specific information ( controlled load has no service specific 
     * info here )
     */
    union {
        AD_GUARANTEED   Guaranteed;
        PARAM_BUFFER    ParamBuffer[1];     /* allows for other services down 
                                             * the road */
    };

} CONTROL_SERVICE, *LPCONTROL_SERVICE;

/*
 * This structure defines the information which is carried in the Rsvp 
 * Adspec.  This Rsvp object typically indicates which service types are 
 * available ( Controlled Load and/or Guaranteed Service ), if a non-Rsvp
 * hop has been encountered by the Path message, and the minumum MTU along 
 * the path. The services array indicates which services are supported
 */
typedef struct _RSVP_ADSPEC  {

    QOS_OBJECT_HDR     ObjectHdr;
    AD_GENERAL_PARAMS  GeneralParams;      /* contains the general 
                                            * characterization paramters */
    ULONG              NumberOfServices;   /* count of the number of services */
    CONTROL_SERVICE    Services[1];        /* a list of the services 
                                            * supported/requested */

} RSVP_ADSPEC, *LPRSVP_ADSPEC;


#endif  /* __QOS_H_ */
