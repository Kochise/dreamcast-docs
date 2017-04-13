Dynamic Data Exchange (DDE) Event and Status Viewer


SUMMARY
=======

The DDESPY tool allows you to view information about the status of dynamic 
data exchange (DDE) conversations.

MORE INFORMATION
================

The DDESPY tool demonstrates how to monitor DDE messages by setting up an 
APPCLASS_MONITOR callback function. The DDESPY-monitored data can be 
selected and filtered through various options. The information is 
represented in up to four selectable tracks for String Handles, 
Conversations, Links and Services, each displayed in different overlapped 
windows. DDESPY records the messages and displays them on the related 
window. DDESPY is useful in debugging to verify DDE data and messages.

DDESPY demonstrates the following techniques:

  - Using a DDE APPCLASS_ MONITOR.
  - Using a DDE callback routine.
  - Creating ownerdraw multi-column list boxes (sorted by column).
  - Creating a string class window to spool endless text.

To use DDESPY to monitor messages, do the following:

 1. Choose the Outputs menu to select the Output device.
 2. Choose the Monitor menu to select the data you wish to monitor.
 3. Choose the Track menu to select the track to be displayed.
 4. Install a client server DDE conversation, such as \ddeml\client and 
    \ddeml\server.
