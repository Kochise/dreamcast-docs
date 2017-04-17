Direct3D sample program -- Optimal
-----------------------------------------

* Purpose:
This sample demonstrates how to maximize polygon throughput on
Dreamcast using the Dreamcast sdk.  It creates a set of spheres, each of 
which is a single triangle strip, and rotates them on screen.  Each sphere
uses a separate vertex pool, and the world matrix is changed between
each sphere.  Each sphere is also lit by a single directional light
source.  These demonstrate that the sample does basically the
same thing as a game, and doesn't "cheat".

There are several command line parameters created to allow testing
other, less-optimal cases, such as using Triangle Lists or non-indexed
strips.

* Required Files\Parameters:
Usage: Optimal [options]
-?               Display usage information
-notex           Disable texture mapping  (default = texture mapping ON)
-dip             Use DrawIndexedPrimitive (default = use DrawPrimitive)
-list            use Triangle Lists       (default = use Triangle Strips)
-light #         Number of lights to display.  Must be 0, 1, 2, or 3.
                     Use '0' to use PreLit vertices  (default = 1)
-frames #        Number of frames to run before exiting.
                     Use '-1' for Infinite run (default == -1)
-output #        Number of frames to run between outputting information
                     use '-1' for no during-run output (default = -1)
-stripsize # #   Specify size of strip (Width, Height).  Numbers must be
                     divisible by two, and must be greater than two!
					 Technically, this is the number of vertices in each
					 dimension.  The number of polygons displayed will be
					 roughly (2 * Width * Height), since each 'square' in
					 the strip is 2 polygons (the number of polygons is
					 'roughly' that because there are also extra polygons
					 at the end of each row to allow us to use a single strip
					 for each sphere.  Look at the output of the program for
					 the exact number of polygons displayed). (Default;
					 width = 20, height = 20)
-stripnum #      Number of strips to display (default = 20)

* To exit this sample, press the 'Send ESC' button in DCTool or
press <Esc> on the keyboard
