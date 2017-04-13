======================================================
Notes for Active Documents "Framer" (Container) Sample
======================================================

Framer is intended to demonstrate simple Active Document Objects hosting as
a container.  That is, Framer demonstrates the basic support necessary to
host Active Documents.  It is implemented according to the guidlines in the
"Active Documents Specification" document and has been tested against
Microsoft Word and Microsoft Excel as well as a few other OLE-enabled
applications that do not support Active Documents.


Framer itself has almost nothing in the way of its own user interface such
as a more complete host would, such as the Office Binder.  Framer has these
menu commands available:

    Command     Description
    ----------------------------------------------------------------------
    File Open   Displays a File Open dialog and allows the user to select
                a file.  Framer will attempt to activate the file as an 
                Active Document.  Failing that it will create a standard
                embedded object and activate it in a separate window.
                This command is disabled when an object already exists.
                File/Close must be used before creating another object.

    File Close  Closes the document that is currently open; if the object
                is just an embedding it will destroy that object which has
                the effect of closing the server as well.  Try opening
                a .BMP file (which should activate PaintBrush, for instance)
                and use Close to see the effect.  There are some variations to
		this behavior (see next section below).

    File Exit   Performs File/Close if necessary and terminates Framer.

    Help About  Displays Framer's About box.  This command exists to
                demonstrate Active Document Help menu merging.


Whenever Framer knows it has an object it displays a small message in its
client area to remind you that you have to File/Close before creating another.


Creating and Activating an Object
---------------------------------

Framer allows you to open documents regardless of whether or not
there is a server that supports Active Documents for the document
type and regardless of whether or not the document server even knows
about Active Documents at all.  

When you "Open" a file in Framer, the code call OleCreateFromFile to create
an embedded object from the contents of the file.  This has two possible
results:

    1.  If there is an Active Documents server associated with the file,
        an embedded object initialized with the file contents is created.

    2.  If there is not an Active Documents server associated with the file,
        a package object is created.

Immediately after creation, Framer activates the object with IOleObject::DoVerb
passing OLEIVERB_SHOW.

If the object is a true embedding with server support, one of two things
will happen:

    1a. If the object doesn't know about Active Documents, it is activated in
        another window.  Using File/Close in this case will close the server.
        Closing the server itself will cause Framer to do the equivalent
        of File/Close, which frees the object and re-enables File/Open.
        See CImpIIAdviseSink::OnClose in iadvsink.cpp.  The closing
        sequence is in CFrame::Close in framer.cpp.  Using Framer with the
    	Paint application will demonstrate this behavior.

    1b. If the object has Active Document support, then its server will start
        activation sequence, primarily by calling IOleDocumentSite::ActivateMe
        which is found in idocsite.cpp.  Inside this member, Framer
        then performs the standard sequence of document object activation
        steps.  After these steps the Active Document will be fully
        interactive; using File/Close on the menu, which Framer still owns,
        will deactivate the object through CFrame::Close which performs the
        same set of steps as in #1b above.  Using Framer with Microsoft Word
	    will demonstrate this behavior.


If you activate a package object, the result is that you launch an application
and have it open the file.  Since the application has no OLE support in it
whatsoever, there is no communication link between Framer and that application.
This means that closing Framer will not close that other application.  This is
what one observes with opening a .TXT file in Framer which will launch Notepad.
Once Notepad is running, it's separate and disconnected from Framer.  You have
to close Notepad manually.

Framer might have been written to disallow insertion of files that do not have
Active Documents support.  Framer rather demonstrates how to view any file
regardless of server support.



Help Menu Merging
-----------------

Framer implements the container side of the Help menu merging protocol
described in the Active Documents Specification.  This involves the members
CFrame::InsertMenus, CFrame::SetMenu, and CFrame::RemoveMenus.  The
InsertMenus method will install Framer's Help menu in the correct location
on the shared menu.  The container-side popup used here is loaded from
Framer's resources on startup in CFrame::Init.

Inside CFrame::SetMenu, Framer checks if there's more than one item on
the menu added in InsertMenus.  If so, then Framer remembers this fact
for later message handling.  Otherwise Framer removes this menu from the
shared menu entirely as the dicument object itself isn't using this shared
capability.

Inside CFrame::RemoveMenus, Framer simply makes sure that its own Help
menu is removed as it should be.

The really interesting stuff happens in FrameWndProc (framer.cpp) in the
WM_INITMENU, WM_INITMENUPOPUP, WM_MENUSELECT, and WM_COMMAND cases.  Inside
WM_INITMENU Framer clears a flag that indicates whether the last popup menu
that was being used was the object's additions to the Help menu.  Inside
WM_MENUSELECT, Framer checks if the originating menu is a popup and if so,
it checks if that popup is on the shared "Help" popup, and if that is also
true then Framer checks if the item being used is the first one or some
other one.  The first item is what Framer knows to be its own Help item, so
it just handles the messages as usual.  Otherwise the user is working with
an Active Document-owned menu, so Framer sets the flag m_fInObjectHelp variable
to TRUE and forwards the message to the object's window (available from
IOleInPlaceObject::GetWindow).

As long as m_fInObjectHelp is set, Framer will forward WM_COMMAND,
WM_INITMENUPOPUP, and WM_MENUSELECT messages.  As soon as another
WM_MENUSELECT message is seen for another non-object menu, then Framer
will reset the flag and begin processing messages once again itself.

In this way you'll see, with Microsoft Word for example, the correct
behavior of a shared Help popup.  Note that Microsoft Excel does not
exhibit this shared Help menu behavior as it only displays its own
Help menus.



Known Feature Limitations
-------------------------
1.  Framer does not print so it does not use the IPrint interface nor does
    it implement IContinueCallback.

2.  Framer does nothing with command targets.

3.  Framer does not forward owner-draw menu messages to the object which
    means that if owner-draw menus are used in a DocObject help menu,
    this sample will not work correctly.

4.  Framer does not provide for actually saving any changes made to an
    Active Document.  Because an Active Document is an embedding, Framer has
    to provide an instance of IStorage through IPersistStorage::InitNew
    or IPersistStorage::Load.  It does this using a temporary Compound File
    that is deleted when Framer exits.  Therefore any changes made to the data
    in the Active Document will simply be discarded.


Potential for Better UI
-----------------------

The item #4 above takes a little more explanation.  When OleCreateFromFile is
used in the File/Open command, Framer is making a COPY of the file contents.
When an Active Document is activated with this content, the document has a copy
of the file contents, not the contents of the file itself.  Therefore any
changes made there will not be reflected back into the original file, although
Framer's UI suggests that this should happen.

A real Active Document container like the Office Binder actually stores all the
object data in its own Compound File, not as separate files.  If one needs
to have an Active Document save into a separate file, then the container needs
to either use command-targets or has to call IPersistFile::Save to accomplish
this step.

In short, Active Documents is not about activating the apps that manipulate
files; it's about activating embedded *documents* saved within the container
file *as if* those documents were stand alone.

Framer's UI, which is really inappropriate for DocObjects, exists as it does
for simplicity's sake.

A more appropraite container application would maintain its own "files" in
which it collected data from a number of other "documents" which are stored
simply as embedded objects.  The Office Binder does exactly this, where
a "Binder" is a Compound File with sub-storages for each "section" in the
document.

Certainly with some more work on UI, Framer could become such an application.
