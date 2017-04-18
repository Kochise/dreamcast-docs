********************************************************************
*                                                                  *
*    Writing Applications with the Microsoft Web Publishing SDK    *
*              Copyright (C) 1997 Microsoft Corporation            *
*                                                                  *
********************************************************************

If you are authoring an application which will use the Web Publishing
API or SPI, then go to the BIN directory of the Internet Client SDK and run
WPSDK.EXE to install the necessary DLLs on your system. Then consult
the API-usage sample in SAMPLES\WEBPOST\WBPOST.

If you are authoring a Web Publishing Service Provider for use with
the Web Publishing API, you should install the complete Web Publishing Wizard
so that you can test your provider (this SDK only contains the DLLs required
by authors writing to the Web Publishing API). The Wizard can be downloaded from
http://www.microsoft.com/windows/software/webpost.

This SDK includes the source code for a stubbed Service Provider 
(in SAMPLES\WEBPOST\STUBWPP). This code is ready to be compiled, and, when
registered with REGSVR32, will install an "empty" provider on your system
called "Web Publishing Service Provider Stub". All you need to do to implement
your own provider is fill in the implementations of the Service Provider
methods. More details are given in SAMPLES\WEBPOST\STUBWPP\README.TXT.
