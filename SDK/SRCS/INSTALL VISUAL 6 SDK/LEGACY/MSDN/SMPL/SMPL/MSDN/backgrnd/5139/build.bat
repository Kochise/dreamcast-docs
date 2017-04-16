

MIDL hellojtx.idl

JAVATLB /d . /p Hellojtx /p:b- hellojtx.tlb

cd Hellojtx
JAVAGUID CHellojtx.class IHellojtx.class 
cd ..

JVC Hellojtx\HelloObj.java

C:\MTX\TOOLS\EXEGEN /d /r /out:hellojtx.dll hellojtx.tlb *.class