Global Chat Sample for Windows Sockets 


SUMMARY
=======

The GLOBCHAT sample allows two clients to carry on a conversation using a 
server as the intermediary. By using the Name Resolution and Registration 
functions, the clients need not even have the same transport protocols 
loaded. The server acts as a gateway between the two clients, forwarding 
messages over the appropriate Windows Sockets interface.

MORE INFORMATION
================

To run Global Chat:

  - Load the server side, GLOBCHAT.EXE, on a Windows NT server. This machine 
    should run every protocol that a potential client might run.

  - On a client machine, run GLOBCL.EXE. Choose Connect from the Options 
    menu to get to the dialog box for selecting the protocol of your choice 
    and give yourself a name to be known by.

  - Once you enter the protocol and your name, the Global Chat Client finds 
    the server and gives you a list of other users who you can chat with. 
    Pick one, wait for them to accept your offer of a chat, and start 
    typing.

The Global Chat Server displays the protocols it is using, the number of 
client machines connected using each protocol, a list of all the client 
names currently connected, and the status of each.

Note: Some of the supported protocols simply use the first Global Chat 
Server that they find. This means that if more than one Global Chat Server 
is running on your network, you may not connect to the right one.

