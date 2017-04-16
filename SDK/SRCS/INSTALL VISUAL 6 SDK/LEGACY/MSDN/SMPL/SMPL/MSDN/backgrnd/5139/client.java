// Client for Simple Microsoft Transaction Server sample application, written in Java
// Copyright (C) 1997 Microsoft Corporation
// All rights reserved.

import Hellojtx.*;

public class Client
{
	public static void main(String args[])
		{
		IHellojtx myHello;
		String strRet[] = { "<no returned data>" };
		int nRet;

		try
			{
			myHello = (IHellojtx) new CHellojtx();
			System.out.println("Calling SayHello..");
			nRet = myHello.SayHello(strRet);
			System.out.println("nRet = " + nRet);
			System.out.println("strRet = " + strRet[0]);
			}
		catch (Throwable t)
			{
			System.out.println("Exception: " + t.toString());	
			t.printStackTrace();
			System.exit(0);
			}
		try
			{
			System.out.println("Hit any key to exit..");
			System.in.read();
			myHello = null;
			System.gc();
			}
		catch (Exception e)
			{

			}
		}
}