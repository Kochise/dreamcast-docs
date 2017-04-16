OFC Parse & Build
Version 2 Drop 27-June-1996

This drop contains an update to the OFC Parse and Build code that implements 
Version 2 of the DTD.  

Changes since 13-May-1996 drop:

We found a bug that caused an OFC_ERROR to be returned based on transaction ordering
changing.  The problem was order depedency in the parse and build code within the
MAINTRQ, MAINTRS, TRNRQ and TRNRS transactions.  The DTD only specifies ordering at
the level of SONRQ followed by MAINTRQ followed by TRNRQ but no order within MAINTRQ
and TRNRQ.  The code, however, demanded that within MAINTRQs for example, the order
be ACCTRQ - PAYEERQ - MAILRQ.  The following files changed because of this:

	build.c
	validlst.c 

Note that these changes may require you to make changes to your server code
if you had order dependencies in your code too. 

We added an szNAME to the GENTRN struture to match the DTD.  This required a change
to:
	ofcdtd.h
	parse.c
	pbanking.c


POSSIBLE BUGS:
We ran into a problem with isspace() not accepting some extended (>128) chars properly as
characters.  If you are compiling with Microsoft VC++ be sure to set the /J option to
cause all chars to go to unsigned chars.  If you are compiling with a different compiler
check your implementation of isspace(), if it sign-extends the char then you may have
to add casts to all isXXXX(*ptr) functions to be isXXXX((unsigned char)*ptr) to handle
top bit set chars. 



If you run into other problems contact Tim Harris (timha@microsoft.com) or 
Derek Hazeur (derekha@microsoft.com)






