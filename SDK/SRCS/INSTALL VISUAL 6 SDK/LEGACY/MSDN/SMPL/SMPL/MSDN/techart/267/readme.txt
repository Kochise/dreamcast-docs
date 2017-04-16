DdeExec command set
-------------------

The DdeExec DDE server supports the command set show below.  Connect
to the DrawRect topic of DdeExec and send one or more of the commands
to draw fascinating pictures.

Bunny.exe is a VB2 app which will draw a picture for you.

Xlart.xlm is an example of an Excel macro which will draw a picture.

Exec.exe is a VB2 app which will allow you enter commads directly
and see the result string as provided by the 'Execute Control 1'
protocol supported by this server.

Commands for Exec are entered individually or in groups as:

        [pen(red)]

or

        [pen(red)][line(0,0,50,50)]


The command set
---------------

Pen(RED|BLUE|GREEN|BLACK|WHITE|YELLOW|CYAN|MAGENTA)

    Example:  [pen(red)]

Brush(RED|BLUE|GREEN|BLACK|WHITE|YELLOW|CYAN|MAGENTA)

    Example: [brush(blue)]

Line(left,top,right,bottom)

    Example: [line(0,0,50,50)]

Ellipse(left,top,right,bottom)

    Example: [ellipse(0,0,50,50)]

Rectangle(left,top,right,bottom)

    Example: [rectangle(0,0,50,50)]

Erase()

    Example: [erase()]
    Example: [erase]

Text(x,y,text)

    Example: [text(10,10,"Hi there")]

    Text strings can contain quotes by including them twice:

    Example: [text(10,10,"Yo, ""Herman""!")]

    Other special characters can be included by using \ as
    an escape character

    Example: [text(10,10,"Yo, \"Herman\"!")]
