ActiveX Document Server Sample "DOServer"

DOServer is a very simple example of an ActiveX Document server. It
implements the minimum number of interfaces required to have an object
be an ActiveX Document. 

If the application is executed without the "/embedding" switch, a dialog
box will be displayed that has options for registering the server and
creating a working file. When Register Server is selected, the
application will make all of the required entries into the registry to
register the application as an ActiveX Document server. This must be
done at least once before attempting to load a working file into a
container.

If the Create File option is selected, the user can create a new file
that can be loaded into an ActiveX Document container (such as Internet
Explorer, Microsoft Office Binder or the Framer sample in this SDK).

This ActiveX Document only implements a color feature. Once the file is
loaded into the container, the color can be selected from the Color menu
that the server adds to the container's menu.

