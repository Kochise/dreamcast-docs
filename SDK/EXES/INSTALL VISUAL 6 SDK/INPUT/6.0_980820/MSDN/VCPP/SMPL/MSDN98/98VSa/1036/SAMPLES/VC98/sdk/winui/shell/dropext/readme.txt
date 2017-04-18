Context Menu Extension


The DROPEXT sample demonstrates how to extend the drag-and-drop context 
menu.

To test DROPEXT.DLL, you must:

1. Build DROPEXT.DLL.

2. Copy DROPEXT.DLL to the system directory (for example, c:\windows\system).

   -or-

   Modify DROPEXT.REG file to points to a fully qualified path to the DLL.

3. Run the command: regedit dropext.reg.

4. Use the right mouse button to drag a file from one folder to another.
   You will see additional menu items for the drop operation.
