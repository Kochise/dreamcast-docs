This sample is intended primarily to demonstrate http read range but can also 
be used for simple GET requests without ranges.  Application writers may be 
interested in plugging into the interface defined in range.h, one C call to 
initiate the request and one C callback to receive status and data.

Other interesting aspects include...

Urlmon
* use of urlmon from a console app (not required)
* correct use of IStream::Read return values 
* implementation of IHttpNegotiate to add request headers
* use of IWininetHttpInfo to parse response headers

Wininet
* passing INTERNET_FLAG_OFFLINE to InternetOpen
* calling InternetSetFilePointer in offline mode
* calling InternetTimeFromSystemTime

Files included in this sample...
    range.h         HttpReadRequest constants, structures, and prototypes.
    range.c         test stub (omit when linking app with remaining files)
    cache.cpp       HttpReadRequest entry point and wininet cache handling.
    download.cpp    HttpReadFromServer entry point and urlmon downloading.
    makefile        makefile for use with inetsdk.mak (note console=1)

Limitations
* Microsoft-IIS 2.0b2 may omit some boundaries between multiple ranges.
* Netscape-FastTrack 2.0b3 claims to accept ranges but never returns them.
