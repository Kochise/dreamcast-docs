/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    Error.cpp

Abstract:

    Error reporting mechanism.

-------------------------------------------------------------------*/

#include "DC.h"

static int CurrentErrorMessage=NO_ERROR_MESSAGE;

// Sets the current error message.
void SetErrorMessage(int Message)
{
	CurrentErrorMessage=Message;
}

// Returns the current error message and clears it to none.
int GetLastErrorMessage(void)
{
	int Message=CurrentErrorMessage;
	CurrentErrorMessage=NO_ERROR_MESSAGE;
	return Message;
}
