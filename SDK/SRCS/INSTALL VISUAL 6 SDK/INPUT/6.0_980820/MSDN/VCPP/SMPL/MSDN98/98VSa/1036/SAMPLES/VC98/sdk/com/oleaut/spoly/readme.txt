OLE Automation Sample


SUMMARY
=======

The SPoly sample draws polygons. The only way to make SPoly draw a polygon 
is to use its programmability interface.

One OLE automation object is exposed by Spoly: spoly.application.
The object spoly.application is associated with SPoly's main application 
window. It controls drawing polygons and clearing the display.

MORE INFORMATION
================

SPoly implements IDispatch for spoly.application.

Methods defined on spoly.application
-----------------------------------

Name                        Description

Draw                        Draw the polygon.
Reset                       Delete all points from the polygon.
AddPoint(X, Y)              Add a point with coordinates (x,y) to the 
                            polygon.
EnumPoints as VT_ENUM       Return a collection of the polygon's points.
GetXOrigin as short         Get the X origin of the polygon.
SetXOrigin(x as short)      Set the X origin of the polygon.
GetYOrigin as short         Get the Y origin of the polygon.
SetYOrigin(y as short)      Set the Y origin of the polygon.
GetWidth as short           Get the line width of the polygon.
SetWidth(width as short)    Set the line width of the polygon.

Shortcomings of this sample
---------------------------

Many items in this sample should be properties. Instead, they are 
implemented as methods. Anything that behaves like an attribute of the 
object should be a property.

This is not a good example of how to implement a collection.
