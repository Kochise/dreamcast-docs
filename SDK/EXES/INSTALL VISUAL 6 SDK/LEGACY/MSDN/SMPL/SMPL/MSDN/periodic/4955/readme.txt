Readme for the Modelview Matrix Manipulator Program

The manipulator is a good example of how to
extend/override the default actions of the COpenGLView
class. In this case I needed two viewports, two
frustums, two modelview matrices, so that involved 
reworking the default program flow. In programming
terms you need to do the following;
For the left view
1) Set up a viewport
2) Set up a frustum
3) Set up a transformation matrix
4) Render the common scene
Then, for the right view, do the same. The common
scene is the same code, the only difference is that
the scene is rendered twice in two different viewports.
The viewing transformations can be different.

What the program is designed to show is how to manipulate the
Modelview matrix. Try out you hand at a transformation, then
a rotation. Reset and then try a rotation, then a translation.
You need to know how the values to put into the matrix (like the
sine and cosine of the angle you want to rotate about).


NOTE TO MSJ READERS

This code was not originally intended to be distributed
with my article. Dave Edson noticed I had a cool graphic
and demanded that I provide the source code to generate it.
The COpenGLView class that it was originaly defined for is
described from my OpenGL book, "OpenGL Programming for Windows
95 and Windows NT" published by Addision-Wesley. The CD that
comes with the book contains the full-blown COpenGLView class,
not the rather hastily hacked version you'll find here. The
one in the book covers animation, fonts, display-lists, etc.

To use this program you'll have to know something about how
to manipulate the Modelview matrix, something you can find either
from my book, the OpenGL Reference Manual, any good book on 3D
graphics, or one of the original articleson OpenGL featured in MSJ.
The way the program works is that you enter some actual values into
the matrix and then "apply" them. These values are multiplied onto
the Modelview matrix. You can either accumulate them or apply them
individually.
