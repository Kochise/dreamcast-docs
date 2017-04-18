OLE Apartment Model Threading


SUMMARY
=======

The OLEAPT sample demonstrates OLE apartment model threading. The term 
"apartment" describes a thread with a message queue that supports OLE/COM 
objects. Objects within an apartment are reentrant in only the traditional 
Windows sense, similar to single-threaded OLE. Therefore, operations that 
yield to the message queue can cause further messages to be sent to any 
objects within the apartment. Apartment model threading allows there to be 
more than one "apartment" where previously there was only one: the main 
application thread.

MORE INFORMATION
================

This program is both a client and a server. It starts as a client by 
default, registering its executable as a server and creating another 
instance of itself to be the server.

The client does nothing interesting and is always shown as a minimized 
window. It simply creates an instance of its worker COM object in the 
server. When it shuts down, it releases its reference to the object.

The server registers a class-factory on the main application thread and also 
creates several worker threads. When requests arrive from clients to create 
instances of the class, the server class-factory picks a worker thread for 
the object (simply allocating them round-robin to the workers) and then goes 
through the process of having the object created within the thread and 
marshaled from the worker thread back to the class-factory, where it can be 
returned to the caller. Note that this marshaling to the main thread happens
during creation only; subsequent calls from the client to the object go 
straight from the client's process into the worker apartment.

The only mechanisms used here above-and-beyond Windows NT 3.5 are:

  - Ability to call CoInitialize in multiple threads
  - The use of the new marshaling flag, MSHCTX_INPROC, to marshall pointers
    between threads

This sample can be compiled as UNICODE or ANSI, so that it can run on both 
Windows NT 3.51 and Windows 95.
