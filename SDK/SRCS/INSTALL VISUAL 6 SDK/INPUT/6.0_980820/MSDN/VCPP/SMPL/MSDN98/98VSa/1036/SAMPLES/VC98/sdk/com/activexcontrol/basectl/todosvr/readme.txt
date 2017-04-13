Before building the ToDoSvr sample, you must run setenv.bat to make 
sure the Platform SDK include, bin, and lib directories are included
first in your environment.

ToDoSvr depends on the FrameWrk sample, which must be built first. To 
build a debug version of the framework library, use the command line
   nmake 
from the FrameWrk directory. To build a retail version of the framework, 
use the command line
   nmake nodebug=1
from the FrameWrk directory. Libraries are placed in the ..\Lib directory.

After building the FrameWrk library, you can build the ToDoSvr control 
by moving to the ToDoSvr directory and entering the command
   nmake
to build a debug version, or 
   nmake nodebug=1
to build a retail version.

The ToDoSvr sample will be automatically registered as part of the 
build process.


ToDoSvr is a simple example of a combination OLE Control and Document Object 
server based on the OLE Controls Framework sample code. Generic extensions 
to the framework which would apply to any Document Object server are 
contained in the class CDocumentObject, which is defined in cdocobj.h. Any 
code which is specific to making ToDoSvr act as a Document Object is marked 
with a comment containing the word DOCOBJ. 

In its current state, ToDoSvr shows nothing more than the minimal amount of 
code required to act as a Document Object from within Office Binder. It does 
not manage any data and it doesn't display anything.

In its completed form, ToDoSvr will be a simple to-do list manager that can 
act as a Document Object within any Document Object container. ToDoSvr will 
expose a simple object model which lets you manage to-do information via OLE 
automation. In addition to providing hyperlinks to documents you are working 
on, ToDoSvr objects will act as hyperlink targets, so that you can easily 
jump to particular tasks.



