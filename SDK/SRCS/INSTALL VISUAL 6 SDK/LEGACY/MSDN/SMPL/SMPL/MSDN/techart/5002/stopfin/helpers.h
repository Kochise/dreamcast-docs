// Helpers.h : Declarations of object safety category helper functions

#include "comcat.h"

HRESULT CreateComponentCategory(CATID catid, WCHAR* catDescription);
HRESULT RegisterCLSIDInCategory(REFCLSID clsid, CATID catid);
