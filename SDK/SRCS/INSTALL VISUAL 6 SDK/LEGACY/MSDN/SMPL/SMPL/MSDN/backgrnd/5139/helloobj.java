
// Simple Microsoft Transaction Server sample application, written in Java
// Copyright (C) 1997 Microsoft Corporation
// All rights reserved.

package Hellojtx;

import com.ms.mtx.*;


public class HelloObj implements IHellojtx
{
	public int SayHello(String[] result)
	{
		try
		{	
			result[0] = "Hello from simple MTS Java sample";
			MTx.GetObjectContext().SetComplete();
			return 0;
		}

		catch(Exception e)
		{	
			MTx.GetObjectContext().SetAbort();	
			return -1;
		}
	}
}

