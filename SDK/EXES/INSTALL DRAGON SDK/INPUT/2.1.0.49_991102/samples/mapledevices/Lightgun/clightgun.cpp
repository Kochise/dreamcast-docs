/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    CLightgun.cpp

Abstract:

    Member functions for the CLightgun class.

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "Lightgun.hpp"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CLightgun::CLightgun

Description:

    Constructor for CLightgun Class.

Arguments:

    GUID        guidLightgun    - GUID of the Lightgun device

    CController *pcont     - Controller to which the Lightgun device is attached

Return Value:

    None

-------------------------------------------------------------------*/
CLightgun::CLightgun(GUID guidLightgun)
{
    m_guidLightgun = guidLightgun;
    m_plgunintf    = NULL;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CLightgun::~CLightgun

Description:

    Destructor for CLightgun class.

Arguments:

    None

Return Value:

    None

-------------------------------------------------------------------*/
CLightgun::~CLightgun()
{
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CLightgun::Initialize

Description:

    Initializes the CLightgun object.

Arguments:

    None

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL
CLightgun::Initialize()
{
    IUnknown *pIUnknown;

    g_errLast = MapleCreateDevice(&m_guidLightgun, &pIUnknown);
    if (CheckError(TEXT("Create Maple Device")))
        return FALSE;

    pIUnknown->QueryInterface(IID_ILGun, (PVOID*)&m_plgunintf);
    pIUnknown->Release();

    if (m_plgunintf == NULL)
        return FALSE;

    // Note, this event must be manually reset.
    m_hEvent = CreateEvent(NULL, TRUE, TRUE, NULL);

    return TRUE;
}
