// EventSink.h
#ifndef EVENTSINK_H // instead of pragma once
#define EVENTSINK_H

#define _WIN32_DCOM

#include "Cache.h"
#include <Wbemidl.h>
#include <iostream>


#pragma comment(lib, "wbemuuid.lib")

/**
 * @class EventSink
 * @brief A class that implements the IWbemObjectSink interface to receive event notifications.
 *
 * This class is responsible for receiving event notifications from WMI and storing them in a cache.
 */
class EventSink : public IWbemObjectSink
{
    LONG m_lRef; // Reference counter
    bool bDone; // A flag indicating whether eventsink is finished

public:
    Cache cache; // Cache object to store the received events
    EventSink() : cache() { m_lRef = 0; }
    virtual ~EventSink() { bDone = true; }

    // Overridden from IWbemObjectSink. Handles reference count.
    virtual ULONG STDMETHODCALLTYPE AddRef();
    
    // Overridden from IWbemObjectSink. Decrements reference count, and delete self if no more references exist
    virtual ULONG STDMETHODCALLTYPE Release();
    
    // Overridden from IWbemObjectSink. Obtains pointers to the supported interfaces
    virtual HRESULT
        STDMETHODCALLTYPE
        QueryInterface(REFIID riid, void **ppv);

    // Overridden from IWbemObjectSink. Called by WMI to deliver events or objects
    virtual HRESULT STDMETHODCALLTYPE Indicate(
        LONG lObjectCount,
        IWbemClassObject __RPC_FAR *__RPC_FAR *apObjArray);

    // Overridden from IWbemObjectSink. Called by WMI to report the completion status or error status
    virtual HRESULT STDMETHODCALLTYPE SetStatus(
        /* [in] */ LONG lFlags,
        /* [in] */ HRESULT hResult,
        /* [in] */ BSTR strParam,
        /* [in] */ IWbemClassObject __RPC_FAR *pObjParam);
};

#endif // end of EventSink.h