/*++

Copyright (c) 1996 Microsoft Corporation

Module Name:

    CMacro.h

Abstract:

Author:

Environment:

    User mode

Revision History :

--*/
#ifndef _CMACRO_H_
#define _CMACRO_H_

#define DEFINE_CONTAINED_IADs_Implementation(cls)                   \
STDMETHODIMP                                                          \
cls::get_Name(THIS_ BSTR FAR* retval)                                 \
{                                                                     \
    RRETURN(_pADs->get_Name(retval));                               \
}                                                                     \
                                                                      \
STDMETHODIMP                                                          \
cls::get_ADsPath(THIS_ BSTR FAR* retval)                            \
{                                                                     \
                                                                      \
    RRETURN(_pADs->get_ADsPath(retval));                          \
}                                                                     \
                                                                      \
STDMETHODIMP                                                          \
cls::get_Class(THIS_ BSTR FAR* retval)                                \
{                                                                     \
                                                                      \
    RRETURN(_pADs->get_Class(retval));                              \
}                                                                     \
                                                                      \
                                                                      \
STDMETHODIMP                                                          \
cls::get_Parent(THIS_ BSTR FAR* retval)                               \
{                                                                     \
    RRETURN(_pADs->get_Parent(retval));                             \
}                                                                     \
                                                                      \
STDMETHODIMP                                                          \
cls::get_Schema(THIS_ BSTR FAR* retval)                               \
{                                                                     \
    RRETURN(_pADs->get_Schema(retval));                             \
}                                                                     \
                                                                      \
STDMETHODIMP                                                          \
cls::get_GUID(THIS_ BSTR FAR* retval)                                 \
{                                                                     \
    RRETURN(_pADs->get_GUID(retval));                               \
}                                                                     \
                                                                      \
STDMETHODIMP                                                          \
cls::Get(THIS_ BSTR bstrName, VARIANT FAR* pvProp)                    \
{                                                                     \
    RRETURN(_pADs->Get(bstrName, pvProp));                          \
}                                                                     \
                                                                      \
STDMETHODIMP                                                          \
cls::Put(THIS_ BSTR bstrName, VARIANT vProp)                          \
{                                                                     \
    RRETURN(_pADs->Put(bstrName, vProp));                           \
}                                                                     \
                                                                      \
STDMETHODIMP                                                          \
cls::GetInfo(THIS_)                                                   \
{                                                                     \
    RRETURN(_pADs->GetInfo());                                      \
}                                                                     \
                                                                      \
STDMETHODIMP                                                          \
cls::SetInfo(THIS_ )                                                  \
{                                                                     \
    RRETURN(_pADs->SetInfo());                                      \
}

#endif

