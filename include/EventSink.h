// EventSink.h
#ifndef EVENTSINK_H // instead of pragma once
#define EVENTSINK_H

#define _WIN32_DCOM

#include <comdef.h>
#include <Wbemidl.h>
#include <iostream>
#include <list>
#include "EventDetails.h"

#pragma comment(lib, "wbemuuid.lib")

/**
 * @class EventSink
 * @brief A class that implements the IWbemObjectSink interface to receive event notifications.
 *
 * This class is responsible for receiving event notifications from WMI and storing them in a cache.
 */
class EventSink : public IWbemObjectSink
{
    LONG m_lRef;
    bool bDone;

public:
    std::list<EventDetails> cache;
    EventSink() { m_lRef = 0; }
   ~EventSink() { bDone = true; }

    virtual ULONG STDMETHODCALLTYPE AddRef();
    virtual ULONG STDMETHODCALLTYPE Release();        
    virtual HRESULT 
        STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppv);

    virtual HRESULT STDMETHODCALLTYPE Indicate( 
            LONG lObjectCount,
            IWbemClassObject __RPC_FAR *__RPC_FAR *apObjArray
            );
        
    virtual HRESULT STDMETHODCALLTYPE SetStatus( 
            /* [in] */ LONG lFlags,
            /* [in] */ HRESULT hResult,
            /* [in] */ BSTR strParam,
            /* [in] */ IWbemClassObject __RPC_FAR *pObjParam
            );
};

#endif    // end of EventSink.h