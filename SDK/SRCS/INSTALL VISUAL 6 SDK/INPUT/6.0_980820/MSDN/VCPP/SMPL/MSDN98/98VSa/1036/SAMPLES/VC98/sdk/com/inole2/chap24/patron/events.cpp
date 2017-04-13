/*
 * EVENTS.CPP
 * Patron Chapter 24
 *
 * Implementation of the Events dialog box, the CEventMap class,
 * and the events IDispatch on a tenant control site.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "patron.h"


/*
 * EventsDlgProc
 *
 * Purpose:
 *  Dialog procedure for the dialog in which the user can assign
 *  actions to events.
 */

BOOL APIENTRY EventsDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam
    , LPARAM lParam)
    {
    PCEventMap      pEM=NULL;
    HWND            hList;
    UINT            i, iEvent;

    COMMANDPARAMS(wID, wCode, hWndMsg);

   #ifdef WIN32
    pEM=(PCEventMap)GetProp(hDlg, PROP_POINTER);
   #else
    WORD            w1, w2;

    w1=(WORD)GetProp(hDlg, PROP_SELECTOR);
    w2=(WORD)GetProp(hDlg, PROP_OFFSET);

    pEM=(PCEventMap)MAKELP(w1, w2);
   #endif

    switch (iMsg)
        {
        case WM_INITDIALOG:
            pEM=(PCEventMap)lParam;

           #ifdef WIN32
            SetProp(hDlg, PROP_POINTER, (HANDLE)pEM);
           #else
            SetProp(hDlg, PROP_SELECTOR, (HANDLE)SELECTOROF(pEM));
            SetProp(hDlg, PROP_OFFSET,   (HANDLE)OFFSETOF(pEM));
           #endif

            /*
             * Fill the listbox with events and select the first
             * one.  The selection will cause an LBN_SELCHANGE
             * notification which will set the appropriate
             * radiobutton for the action.
             */

            hList=GetDlgItem(hDlg, IDC_EVENTLIST);

            for (i=0; i < pEM->m_cEvents; i++)
                {
                //Add the name of the event to the list
               #ifdef WIN32ANSI
                char        szTemp[40];

                WideCharToMultiByte(CP_ACP, 0
                    , pEM->m_pEventMap[i].bstrName, -1, szTemp
                    , 40, NULL, NULL);
                iEvent=(UINT)SendMessage(hList, LB_ADDSTRING, 0
                    , (LONG)(LPSTR)szTemp);
               #else
                iEvent=(UINT)SendMessage(hList, LB_ADDSTRING, 0
                    , (LONG)(LPSTR)pEM->m_pEventMap[i].bstrName);
               #endif

                if (LB_ERR!=iEvent)
                    {
                    //Give that item a pointer to the map data
                    SendMessage(hList, LB_SETITEMDATA, iEvent
                        , (LONG)&pEM->m_pEventMap[i]);
                    }
                }

            //Set the initial action for the first item
            SendMessage(hList, LB_SETCURSEL, 0, 0L);
            CheckAction(hDlg, hList);
            return TRUE;

        case WM_COMMAND:
            hList=GetDlgItem(hDlg, IDC_EVENTLIST);

            switch (wID)
                {
                case IDOK:
                    EndDialog(hDlg, 1);
                    break;

                case ID_TEST:
                    TestSelection(hList);
                    break;

                case IDC_EVENTLIST:
                    //Update the radiobuttons
                    if (LBN_SELCHANGE==wCode)
                        CheckAction(hDlg, hWndMsg);

                    //Double-click, same as hitting Test button
                    if (LBN_DBLCLK==wCode)
                        TestSelection(GetDlgItem(hDlg, IDC_EVENTLIST));
                    break;

                case IDC_BEEPNONE:
                case IDC_BEEPDEFAULT:
                case IDC_BEEPEXCLAMATION:
                case IDC_BEEPASTERISK:
                case IDC_BEEPHAND:
                case IDC_BEEPQUESTION:
                    UpdateAction(hList, wID);
                    break;
                }
            return TRUE;
        }

    return FALSE;
    }



/*
 * CheckAction
 *
 * Purpose:
 *  Sets the appropriate radiobutton for the current listbox
 *  selection
 *
 * Parameters:
 *  hDlg            HWND of the dialog.
 *  hList           HWND of the event list.
 *
 * Return Value:
 *  None
 */

void CheckAction(HWND hDlg, HWND hList)
    {
    UINT        i, idControl;
    PEVENTMAP   pMap;

    i=(UINT)SendMessage(hList, LB_GETCURSEL, 0, 0L);
    pMap=(PEVENTMAP)SendMessage(hList, LB_GETITEMDATA, i, 0L);

    if (LB_ERR==(LONG)pMap)
        return;

    //Map the action to the button
    switch (pMap->iAction)
        {
        case ACTION_NONE:            idControl=IDC_BEEPNONE; break;
        case ACTION_BEEPDEFAULT:     idControl=IDC_BEEPDEFAULT; break;
        case ACTION_BEEPASTERISK:    idControl=IDC_BEEPASTERISK; break;
        case ACTION_BEEPEXCLAMATION: idControl=IDC_BEEPEXCLAMATION; break;
        case ACTION_BEEPHAND:        idControl=IDC_BEEPHAND; break;
        case ACTION_BEEPQUESTION:    idControl=IDC_BEEPQUESTION; break;
        default:                     idControl=IDC_BEEPNONE; break;
        }

    CheckRadioButton(hDlg, IDC_BEEPNONE, IDC_BEEPQUESTION, idControl);
    return;
    }



/*
 * UpdateAction
 *
 * Purpose:
 *  Sets the appropriate action in the event map for the
 *  selected radiobutton.
 *
 * Parameters:
 *  hList           HWND of the event list.
 *  idControl       UINT identifier of the selected action control
 *
 * Return Value:
 *  None
 */

void UpdateAction(HWND hList, UINT idControl)
    {
    UINT        i;
    PEVENTMAP   pMap;

    i=(UINT)SendMessage(hList, LB_GETCURSEL, 0, 0L);
    pMap=(PEVENTMAP)SendMessage(hList, LB_GETITEMDATA, i, 0L);

    if (LB_ERR==(LONG)pMap)
        return;

    //Map the button to the action
    switch (idControl)
        {
        case IDC_BEEPNONE:        pMap->iAction=ACTION_NONE; break;
        case IDC_BEEPDEFAULT:     pMap->iAction=ACTION_BEEPDEFAULT; break;
        case IDC_BEEPASTERISK:    pMap->iAction=ACTION_BEEPASTERISK; break;
        case IDC_BEEPEXCLAMATION: pMap->iAction=ACTION_BEEPEXCLAMATION; break;
        case IDC_BEEPHAND:        pMap->iAction=ACTION_BEEPHAND; break;
        case IDC_BEEPQUESTION:    pMap->iAction=ACTION_BEEPQUESTION; break;
        default:                  pMap->iAction=ACTION_NONE; break;
        }

    return;
    }





/*
 * TestSelection
 *
 * Purpose:
 *  Executes the action associated with the currently selected
 *  event.
 *
 * Parameters:
 *  hList           HWND of the event list.
 *
 * Return Value:
 *  None
 */

void TestSelection(HWND hList)
    {
    UINT        i;
    PEVENTMAP   pMap;

    i=(UINT)SendMessage(hList, LB_GETCURSEL, 0, 0L);
    pMap=(PEVENTMAP)SendMessage(hList, LB_GETITEMDATA, i, 0L);

    //Event values corresond to MessageBeep values.
    if (LB_ERR!=(LONG)pMap)
        MessageBeep(pMap->iAction);

    return;
    }




//CEventMap implementations


/*
 * CEventMap::CEventMap
 * CEventMap::~CEventMap
 *
 * Parameters (Constructor):
 *  pITypeInfo      LPTYPEINFO from which to read event names.
 */

CEventMap::CEventMap(LPTYPEINFO pITypeInfo)
    {
    m_cEvents=0;
    m_pITypeInfo=pITypeInfo;
    
    if (NULL!=m_pITypeInfo)
        m_pITypeInfo->AddRef();

    m_pEventMap=NULL;
    return;
    }




CEventMap::~CEventMap(void)
    {
    if (NULL!=m_pITypeInfo)
        m_pITypeInfo->Release();

    if (NULL!=m_pEventMap)
        {
        UINT        i;

        //Be sure to clean up allocated BSTRs
        for (i=0; i < m_cEvents; i++)
            SysFreeString(m_pEventMap[i].bstrName);

        delete [] m_pEventMap;
        }

    return;
    }



/*
 * CEventMap::Init
 *
 * Purpose:
 *  Initializes the event map with any operation prone to failure.
 *  If this function fails, the caller should delete this object
 *  immediately as it is unusable.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if initialization succeeded, FALSE otherwise
 */

BOOL CEventMap::Init(void)
    {
    LPTYPEATTR      pTA;
    UINT            i;

    if (NULL==m_pITypeInfo)
        return FALSE;

    if (FAILED(m_pITypeInfo->GetTypeAttr(&pTA)))
        return FALSE;

    m_cEvents=pTA->cFuncs;
    m_pITypeInfo->ReleaseTypeAttr(pTA);

    m_pEventMap=new EVENTMAP[m_cEvents];

    if (NULL==m_pEventMap)
        {
        m_cEvents=0;
        return FALSE;
        }

    for (i=0; i < m_cEvents; i++)
        {
        LPFUNCDESC     pFD;

        m_pEventMap[i].id=0;
        m_pEventMap[i].bstrName=NULL;
        m_pEventMap[i].iAction=ACTION_NONE;

        /*
         * The only piece of information we want from for each
         * event is the function name using ITypeInfo::GetNames.
         *
         * A more sophisticated container will probably save
         * more information about each event here (such as
         * parameter names and so forth) or access it dynamically
         * when the end user wants to write code for events.
         */

        if (SUCCEEDED(m_pITypeInfo->GetFuncDesc(i, &pFD)))
            {
            UINT        cNames;
            HRESULT     hr;

            /*
             * Since we only want the function name, we ask
             * ITypeInfo::GetNames for only one function and pass
             * the address of our one BSTR to it.  If we wanted all
             * the names from ITypeInfo, then we'd allocate an
             * array of BSTRs with "new BSTR[pFD->cParams+1]"
             * and pass pFD->cParams+1 to GetNames below instead
             * of just 1.  In either case, GetNames allocates
             * the string and stores the pointer to it in our
             * variable.
             */

            m_pEventMap[i].id=pFD->memid;

            hr=m_pITypeInfo->GetNames(pFD->memid
                , &m_pEventMap[i].bstrName, 1, &cNames);

            m_pITypeInfo->ReleaseFuncDesc(pFD);
            }
        }

    return TRUE;
    }




/*
 * CEventMap::Set
 *
 * Purpose:
 *  Sets the event mapping of a specific ID to a given action.
 *  To clear an event, call this function with the ID and
 *  ACTION_NONE.
 *
 * Parameters:
 *  id              DISPID of the event ID.
 *  iAction         EVENTACTION to assign.
 *
 * Return Value:
 *  BOOL            TRUE if the assignment happened, FALSE otherwise.
 */

BOOL CEventMap::Set(DISPID id, EVENTACTION iAction)
    {
    BOOL        fRet=FALSE;

    if (NULL!=m_pEventMap)
        {
        UINT        i;

        for (i=0; i < m_cEvents; i++)
            {
            if (m_pEventMap[i].id==id)
                {
                m_pEventMap[i].iAction=iAction;
                fRet=TRUE;
                }
            }
        }

    return fRet;
    }




/*
 * CEventMap::Get
 *
 * Purpose:
 *  Retrieves the event assignment for a given ID.
 *
 * Parameters:
 *  id              DISPID of the event ID.
 *
 * Return Value:
 *  EVENTACTION     The action assigned to this ID.  ACTION_NONE
 *                  if the ID is invalid.
 */

EVENTACTION CEventMap::Get(DISPID id)
    {
    EVENTACTION iAction=ACTION_NONE;

    if (NULL!=m_pEventMap)
        {
        UINT        i;

        //Scan the list looking for the event
        for (i=0; i < m_cEvents; i++)
            {
            if (m_pEventMap[i].id==id)
                {
                iAction=m_pEventMap[i].iAction;
                break;
                }
            }
        }

    return iAction;
    }




/*
 * CEventMap::Serialize
 * CEventMap::Deserialize
 *
 * Purpose:
 *  Writes or reads the mappings from DISPID to actions
 *  into or from a stream.
 *
 * Parameters:
 *  pIStream        LPSTREAM into which to write or from which to
 *                  read.
 *
 * Return Value:
 *  None
 */

void CEventMap::Serialize(LPSTREAM pIStream)
    {
    EVENTMAP        emTemp;
    ULONG           cbWrite=sizeof(DISPID)+sizeof(EVENTACTION);

    if (NULL==pIStream)
        return;

    /*
     * Loop through all the IDs and write the ID and the action
     * mapping only.  We don't need the event name because that
     * will be retrieved when the control is again loaded.
     *
     * Writing these pieces of info means writing the first
     * so many bytes of each EVENTMAP structure, ignoring the
     * BSTR of the name.
     */

    if (NULL!=m_pEventMap)
        {
        UINT        i;

        for (i=0; i < m_cEvents; i++)
            pIStream->Write(&m_pEventMap[i], cbWrite, NULL);
        }

    /*
     * Finish off by writing a terminating EVENTMAP structure
     * where the action is ACTION_TAILING which only have
     * meaning here.  The ID is ignored in this tail.
     */

    emTemp.id=0;
    emTemp.iAction=ACTION_TAILING;
    pIStream->Write(&emTemp, cbWrite, NULL);

    return;
    }



void CEventMap::Deserialize(LPSTREAM pIStream)
    {
    if (NULL==pIStream)
        return;

    /*
     * When reading back the event mappings we have to be
     * careful:  the control's event set might have changed
     * in the meantime so some events may no longer exist and
     * there may be new events.  Therefore we read each mapping
     * one at a time (until we hit the tailing map) and find
     * the ID in the current memory event map.  When we find
     * a match we update the action in memory.
     */

    if (NULL==m_pEventMap)
        return;

    while (TRUE)
        {
        ULONG       cbRead=sizeof(DISPID)+sizeof(EVENTACTION);
        HRESULT     hr;
        EVENTMAP    em;

        hr=pIStream->Read(&em, cbRead, NULL);

        //Failure to read means a stream problem, to abort
        if (FAILED(hr))
            break;

        //If we hit the tail, we're done
        if (ACTION_TAILING==em.iAction)
            break;

        //Assign the action to the ID, if it exists
        Set(em.id, em.iAction);
        }

    return;
    }





//Events IDispatch

/*
 * CDispatchEvents::CDispatchEvents
 * CDispatchEvents::~CDispatchEvents
 *
 * Parameters (Constructor):
 *  pTen            PCTenant of the tenant we're in.
 */

CDispatchEvents::CDispatchEvents(PCTenant pTen)
    {
    m_cRef=0;
    m_pTen=pTen;
    return;
    }

CDispatchEvents::~CDispatchEvents(void)
    {
    return;
    }




/*
 * CDispatchEvents::QueryInterface
 * CDispatchEvents::AddRef
 * CDispatchEvents::Release
 *
 * Purpose:
 *  IUnknown members for CDispatchEvents object.
 */

STDMETHODIMP CDispatchEvents::QueryInterface(REFIID riid, PPVOID ppv)
    {
    *ppv=NULL;

    if (IID_IUnknown==riid || IID_IDispatch==riid
        || m_pTen->m_iidEvents==riid)
        *ppv=this;

    if (NULL!=*ppv)
        {
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
        }

    return ResultFromScode(E_NOINTERFACE);
    }

STDMETHODIMP_(ULONG) CDispatchEvents::AddRef(void)
    {
    return ++m_cRef;
    }

STDMETHODIMP_(ULONG) CDispatchEvents::Release(void)
    {
    if (0!=--m_cRef)
        return m_cRef;

    delete this;
    return 0;
    }





/*
 * CDispatchEvents::GetTypeInfoCount
 * CDispatchEvents::GetTypeInfo
 * CDispatchEvents::GetIDsOfNames
 *
 * Purpose:
 *  These type-information functions are not implemented.  The
 *  only caller of this interface is a control which is the source
 *  of the type information itself.  A control will not have a
 *  need to call these functions.
 *
 * Return Value:
 *  HRESULT         E_NOTIMPL in all cases.
 */

STDMETHODIMP CDispatchEvents::GetTypeInfoCount(UINT *pctInfo)
    {
    *pctInfo=NULL;
    return ResultFromScode(E_NOTIMPL);
    }

STDMETHODIMP CDispatchEvents::GetTypeInfo(UINT itinfo
    , LCID lcid, ITypeInfo **pptInfo)
    {
    *pptInfo=NULL;
    return ResultFromScode(E_NOTIMPL);
    }

STDMETHODIMP CDispatchEvents::GetIDsOfNames(REFIID riid
    , OLECHAR **rgszNames, UINT cNames, LCID lcid, DISPID *rgDispID)
    {
    *rgszNames=NULL;
    *rgDispID=NULL;
    return ResultFromScode(E_NOTIMPL);
    }




/*
 * CDispatchEvents::Invoke
 *
 * Purpose:
 *  Notifies the container of the event in the control.  In this
 *  container we look in the event mapping for this particular
 *  site and execute the appropriate action recorded in that
 *  mapping.  If there is no event handler set up, then nothing
 *  happens.
 *
 * Parameters:
 *  dispIDMember    DISPID of the method or property of interest.
 *  riid            REFIID reserved, must be NULL.
 *  lcid            LCID of the locale.
 *  wFlags          USHORT describing the context of the invocation.
 *  pDispParams     DISPPARAMS * to the array of arguments.
 *  pVarResult      VARIANT * in which to store the result.  Is
 *                  NULL if the caller is not interested.
 *  pExcepInfo      EXCEPINFO * to exception information.
 *  puArgErr        UINT * in which to store the index of an
 *                  invalid parameter if DISP_E_TYPEMISMATCH
 *                  is returned.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error code.
 */


STDMETHODIMP CDispatchEvents::Invoke(DISPID dispIDMember, REFIID riid
    , LCID lcid, unsigned short wFlags, DISPPARAMS * pDispParams
    , VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr)
    {
    HRESULT     hr;
    VARIANT     varResult;
    EVENTACTION iAction;
    UINT        i;
    PEVENTMAP  pEM;

    ODSlu("Events IDispatch called with ID=%lu", dispIDMember);

    if (IID_NULL!=riid)
        return ResultFromScode(E_INVALIDARG);

    /*
     * We ignore lcid in this function.  A multilingual application
     * might use it to determine the meaning of certain parameters
     * or perhaps as an indication of how to format data like
     * time, date, and currency or any other language or locale-
     * sensitive data.
     */

    /*
     * Variable handling:  we don't actually do anything with any
     * of the variables from the control's events, so we don't have
     * any VARIANTARG variables to initialize.
     */

    /*
     * We don't handle the return value of any events if
     * events have them.  We should, however, initialize an
     * empty return value just so it's not garbage.
     */
    if(NULL==pVarResult)
      pVarResult=&varResult;

    VariantInit(pVarResult);
    V_VT(pVarResult)=VT_EMPTY;


    //Only method calls are valid.
    if (!(DISPATCH_METHOD & wFlags))
        return ResultFromScode(DISP_E_MEMBERNOTFOUND);

    /*
     * Process the event by looking for dispIDMember in the
     * list maintained in the tenant that maps event IDs to
     * actions.  If we find the ID, then we execute the action,
     * otherwise we do nothing.
     *
     * Control containers that allow more sophisticated programming
     * for events would do something on the same order but process
     * parameters and call user-implemented functions instead of
     * something simple like MessageBeep.
     */

    iAction=ACTION_NONE;
    pEM=m_pTen->m_pEventMap->m_pEventMap;

    for (i=0; i < m_pTen->m_pEventMap->m_cEvents; i++)
        {
        if (dispIDMember==pEM[i].id)
            {
            iAction=pEM[i].iAction;
            break;
            }
        }

    if (ACTION_NONE==iAction)
        hr=ResultFromScode(DISP_E_MEMBERNOTFOUND);
    else
        {
        MessageBeep((UINT)iAction);
        hr=NOERROR;
        }

    return hr;
    }
