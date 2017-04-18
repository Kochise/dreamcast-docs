Miscellaneous sample program -- RAS
-----------------------------------------

* Purpose:
This sample demonstrates RAS API's. It allows you to establish a PPP session
to a remote computer. It also displays the status of the current connections
and enumerates all RAS entries.

* Required Files\Parameters:
Usage:
    s ras entryname [username [password]] [/DOMAIN:domain] [/DEBUG:num]
    s ras [entryname] /DISCONNECT
    s ras

Run ras.exe without any parameter to enumerate all RAS entries available in
the system. 

* MRASENTRY usage
MRASENTRY is a utility to create a RAS entry based on a file
description of the entry. The file can be in the image or in %_FLATRELEASEDIR%,
which in this case is loaded over a remote shell. The file consists of a
series of Labels=Value lines. Be careful with trailing spaces (especially for
user names and passwords).

Fields Supported     Data Type   Description
---------------------------------------------------
Name                 String      entry name
Phone                String      phone number
SpecificIpAddr       Boolean     "Y" to specify a default IP address using
                                 IpAddr in case server never assigns one
                                 "N" to use IP address assigned by the remote
                                 server
IpAddr               IpAddr      IP address, e.g., 204.70.127.127
SpecificNameServers  Boolean     "Y" to specify DNS server addresses using
                                 DnsAddr and AltDnsAddr
                                 "N" to use DNS servers assigned by server
DnsAddr              IpAddr      IP address of primary DNS server
AltDnsAddr           IpAddr      IP address of secondary DNS server
DeviceType           String      modem device type, i.e.,
                                 "modem" for a modem device,
                                 "direct" for a null-modem device
DeviceName           String      modem name, e.g., NullModem or
                                 Sega-DreamcastBuiltIn
IpHeaderCompression  Boolean     compress IP header
SwCompression        Boolean     compress data
UserName             String      logon name
Password             String      logon password
Domain               String      NT domain name


Usage: mrasentry [-dNUM] [-l] file
  -dNUM  : set debug flag to NUM (default 0)
  -l     : read file locally (default is over a remote shell)
  Example: mrasentry isp.ras

---------- Sample Description for MSN ----------
Name=MSN
Phone=441-2632
SpecificIpAddr=N
SpecificNameServers=N
DeviceType=modem
DeviceName=Sega-DreamcastBuiltIn
SwCompression=Y
IpHeaderCompression=Y
UserName=MSN/logon_name
Password=SECRET
Domain=

---------- Sample Description for Win9x Direct Cable Connection ----------
Name=Serial
SpecificIpAddr=Y
IpAddr=192.100.100.2
SpecificNameServers=N
DeviceType=direct
DeviceName=NullModem
SwCompression=Y
IpHeaderCompression=Y
UserName=guest
Password=
Domain=

* This sample exits automatically after performing the specified functionality.