Demonstrating GDI and USER Functions in Fractals


SUMMARY
=======

The MANDEL sample demonstrates GDI and USER functions by working with 
fractals. The Mandelbrot Dream provides the following features:

  - Drawing the Mandelbrot set and the corresponding Julia set.
  - Zooming into any of the sets.
  - MDI fractal drawing windows.
  - Floating point math and fixed point math.
  - Shifting color table entries.
  - Changing palette entries and animating palette (color cycling).
  - Loading and saving bitmaps created with special effects.
  - Changing bitmap colors with flood fill.
  - Boundary tracing and creating a clip region for special effects.
  - Enumerating printers.
  - Loading RLE (or converting .bmp files to RLE) for playing in viewer.
  - Saving the RLE in memory to disk.

Note: The sample makes use of 64-bit integers for its fixed point math.

MORE INFORMATION
================

Drawing the Mandelbrot Set and the Corresponding Julia Set

  - Choose the Mandelbrot Set menu item from the Create menu to create an 
    MDI child window to draw the set in, if one has not already been 
    created.

  - Choose either "use Fix Point math" or "use Floating Point math" from the 
    Draw menu to decide if floating point or fixed point math is to be used.
    Fixed point is faster, however, you lose resolution sooner as you zoom 
    in.

  - Choose the number of iterations from the Iteration menu item and choose 
    Step from the Draw menu. The higher the number of iterations, the more 
    detail in the picture, but the more time it takes to generate the 
    picture. The step determines whether every scan line is drawn. The more 
    scan lines, the better the picture, but the longer it takes to generate 
    the picture.

  - Choose Draw Set from the Draw menu.

  - Use the right mouse button to select a point in the Mandelbrot set (the 
    drawing surface of the Mandlebrot window). A new Julia MDI window is 
    created. Choose Draw Set from the Draw menu to start drawing.

  - The point selected with the right mouse button determines the complex 
    constant to use for the Julia Set.

Zooming Into Any of the Sets

  - Click, drag and release with the left mouse button to describe the zoom 
    in the region. A new MDI child of the same type as the parent 
    (Mandelbrot window or Julia window) is created.

  - Choose Draw Set from the Draw menu to start drawing.

MDI Fractal Drawing Windows

  - Choose either Mandelbrot Set or Julia Set from the Create menu to create 
    a new MDI window for drawing.

  - Or, use the left mouse button to describe a zoom-in region in either a 
    Mandelbrot or Julia MDI window to create a new MDI window for drawing.

  - Or, click on the Mandelbrot window with the right mouse button to create 
    a Julia MDI window corresponding to the mouse click position in the 
    Mandelbrot window.

Floating Point Math and Fixed Point Math

Choose the appropriate menu item ("Floating Point math" or "Fix Point math") 
from the Draw menu. The Fix Point math uses 20.11 fixed point integer 
arithmetic for calculations.

Shifting Color Table Entries

Choose Shift from the Color menu or hit F10 to shift the color table entry. 
The picture of the active MDI window is updated.

Changing Palette Entries and Animating Palette (Color Cycling)

Choose Cycle from the Color menu or hit F11 to start color cycling the 
picture. The menu item is grayed if the display device does not support 
palette management.

Loading and Saving Bitmaps Created With Special Effects

Choose Load Bitmap from the Bitmap menu to load a bitmap into the active 
child window. Or, choose Save Bitmap As to save the picture in the active 
MDI child window.

Changing Bitmap Colors With Flood Fill

Choose Custom from the Color menu to select a color. The cursor is changed 
to a paint can over the active child window. Click with the left mouse 
button on the picture; the old color under the cursor is changed to the new 
color.

Boundary Tracing and Creating a Clip Region For Special Effects

From any active Mandelbrot window, choose Set Mandelbrot Clip region from 
the Region menu. The boundary of the escape region is traced. The region is 
then selected as a clip region. Thus, if you load a bitmap for display, the 
bitmap only shows through the clip region. The new picture can then be 
saved. To remove the clip region, choose Remove Clip Region from the Region 
menu.

Note:  The boundary tracing algorithm may trace out a small island of only 
several pixels and stop. If that happens, change the size of the window or
create another zoom window and trace again. 

Enumerating Printers

On start up, the Mandelbrot Dream enumerates the printers and inserts the 
printers into the Print menu. Selecting the printer on the Print menu prints
the picture in the active MDI window.

Loading RLE (or convert .bmp files to RLE) for Playing in Viewer

  - Choose the Viewer item from the Create menu to create a viewer window or 
    bring any existing viewer window to the top.

  - Select Load Bitmap(s) from the File menu for loading RLE or .bmp files 
    into the memory from disk.

  - Select Play or Play Continuously from the Options menu for viewing.

  - For a demonstration, load the .\rsc\julia.rle file and select Play 
    Continuously. The Julia.rle is a collection of the various julia sets 
    along the boundary of escaping and non-escaping points of the Mandelbrot 
    Set.

Saving the RLE in Memory to Disk

  - Choose the Viewer item from the Create menu to create a viewer window or 
    bring any existing viewer window to the top.
  
  - Select Save Bitmap(s) from the File menu for saving the RLE(s) from 
    memory to disk.
