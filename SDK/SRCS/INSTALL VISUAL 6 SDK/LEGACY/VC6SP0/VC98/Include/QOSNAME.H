/*++

Copyright 1997 - 1998 Microsoft Corporation

Module Name:

    qosname.h

Abstract:

    This module contains the type definitions for the QOS name management routines, such as
    WSAInstallQOSTemplate etc.

Author:

    Jim Stewart     July 2, 1997

Revision History:

--*/

#define WSCINSTALL_QOS_TEMPLATE     "WSCInstallQOSTemplate"
#define WSCREMOVE_QOS_TEMPLATE      "WSCRemoveQOSTemplate"
#define WPUGET_QOS_TEMPLATE         "WPUGetQOSTemplate"

typedef
BOOL
(APIENTRY * WSC_INSTALL_QOS_TEMPLATE )(
    IN  const LPGUID    Guid,
    IN  LPWSABUF        QosName,
    IN  LPQOS           Qos
    );

typedef
BOOL
(APIENTRY * WSC_REMOVE_QOS_TEMPLATE )(
    IN  const LPGUID    Guid,
    IN  LPWSABUF        QosName
    );

typedef
BOOL
(APIENTRY * WPU_GET_QOS_TEMPLATE )(
    IN  const LPGUID    Guid,
    IN  LPWSABUF        QosName,
    IN  LPQOS           Qos
    );


