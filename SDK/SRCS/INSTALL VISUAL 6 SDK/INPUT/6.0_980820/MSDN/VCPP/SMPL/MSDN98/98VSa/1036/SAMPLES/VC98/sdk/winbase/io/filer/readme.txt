File I/O API Demonstration


SUMMARY
=======

The FILER sample is a basic file management applet, such as File Manager or
Norton Commander. It demonstrates many of the new File I/O API, and their
related algorithms, such as drive enumeration, .EXE version information
retrieval, and directory tree walking. It also demonstrates many intensive
User algorithms, such as child management, subclassing, synchronization and
control window management.

MORE INFORMATION
================

FILER presents the user with two fixed child windows, each of which the user 
may associate with a drive from the drives available on the system. The 
Drive toolbar describes the available drives on the system. Users select 
drives from the toolbar or the Drives menu. The Function toolbar corresponds 
to the file I/O options in the File menu.

Each of the Drive child windows contains a Directory ListBox, and a File 
ListBox, for browsing through the files on the selected drive.

FILER gives the user the option to open (execute or edit), copy, delete, 
move, and rename files, create and remove directories, and display any 
version information embedded in the files. The active Drive child acts as 
the source, and the inactive Drive child acts as the default destination 
of file I/O operations.

The Drive children may also be configured side by side or with one above the 
other, and the File and Directory ListBoxes in each may swap positions.

All features of FILER may be selected from the mouse, keyboard, or menu 
items.
