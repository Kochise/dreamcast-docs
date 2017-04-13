Networking (LAN Manager) API Sample


The following sample illustrates how to display error text associated with
Networking related error codes, in addition to displaying error text
associated with system related error codes.

If the supplied error number is in a specific range, the netmsg.dll
message module is loaded and used to lookup the specified error number
with the FormatMessage() Win32 API.
