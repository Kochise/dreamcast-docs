DLC


SUMMARY
=======

The SIMPLEX sample is a single-threaded DLC program. You need two instances 
of this application: one to send and one to receive. This is the typical DLC 
situation: simplex or half-duplex. By default, both sides use SAP 4.

MORE INFORMATION
================

Start the receiver with the command:

    simplex

Start the transmitter with the command:

    simplex /t02608c4c970e

In this example, the node address is in canonical form (ethernet format) as 
displayed by the command "net config wksta", not the token-ring format that 
the DLC API expects. If the test application is being run over a token ring, 
then you would supply the token-ring format:

    simplex /t10005a7b08b4

Command line options are:

/a# - use adapter #
/b# - change the buffer pool size from the default 20K to #
/o  - options:
/or# - set receive READ option
/ot# - set transmit READ option
/r# - send to remote SAP # (transmitter only)
/s# - open local SAP #
/t# - send to station address # (transmitter only)
/z# - transmit packets of size #, else use random size (transmitter only)

