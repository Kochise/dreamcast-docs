/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    CLightgun.hpp

Abstract:

   CLightgun class declaration

-------------------------------------------------------------------*/

// ++++ Global Variables ++++++++++++++++++++++++++++++++++++++++++++

enum ELightgunCommands
{
    ecmdReadLoc,
};

// ++++ Classes +++++++++++++++++++++++++++++++++++++++++++++++++++++

class CController;

class CLightgun
{
public:
    CLightgun(GUID LightgunGuid);
    ~CLightgun();

    // Initialize the Lightgun object
    BOOL Initialize(void);

    HANDLE m_hEvent;

    // LGun interface
    PLGUN m_plgunintf;

    // Last position the gun was fired at
    LGUN_POSITION m_lgunpos;

private:
    // The GUID of the Lightgun device
    GUID m_guidLightgun;
};    

