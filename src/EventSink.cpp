// EventSink.cpp
#include "EventSink.h"

ULONG EventSink::AddRef()
{
    return InterlockedIncrement(&m_lRef);
}

ULONG EventSink::Release()
{
    LONG lRef = InterlockedDecrement(&m_lRef);
    if (lRef == 0)
        delete this;
    return lRef;
}

HRESULT EventSink::QueryInterface(REFIID riid, void **ppv)
{
    if (riid == IID_IUnknown || riid == IID_IWbemObjectSink)
    {
        *ppv = (IWbemObjectSink *)this;
        AddRef();
        return WBEM_S_NO_ERROR;
    }
    else
        return E_NOINTERFACE;
}

HRESULT EventSink::Indicate(long lObjectCount,
                            IWbemClassObject **apObjArray)
{
    SYSTEMTIME lt;
    GetLocalTime(&lt);
    HRESULT hres = S_OK;
    HRESULT hrs;
    _variant_t vtProp;
    _variant_t vtType;

    for (int i = 0; i < lObjectCount; i++)
    {
        LOG(INFO) << "Event occurred.";
        EventDetails tmp;
        tmp.time = lt;

        hrs = apObjArray[i]->Get(_bstr_t(L"__CLASS"), 0, &vtType, 0, 0);
        if (!FAILED(hrs))
        {
            try
            {
                // printf("Class : %S\n", vtType.bstrVal);
                tmp.type = _bstr_t(vtType.bstrVal).copy();
            }
            catch (std::exception &ex)
            {
                printf("Error %s\n", ex.what());
            }
        }

        hres = apObjArray[i]->Get(_bstr_t(L"TargetInstance"), 0, &vtProp, 0, 0);
        if (!FAILED(hres))
        {
            IUnknown *str = vtProp;

            // Getting the Process Name related to the event
            hres = str->QueryInterface(IID_IWbemClassObject, reinterpret_cast<void **>(&apObjArray[i]));
            if (SUCCEEDED(hres))
            {
                _variant_t cn;
                hres = apObjArray[i]->Get(L"Name", 0, &cn, NULL, NULL);
                if (SUCCEEDED(hres))
                {
                    try
                    {
                        tmp.name = _bstr_t(cn.bstrVal).copy();
                    }
                    catch (std::exception &ex)
                    {
                        printf("Error %s\n", ex.what());
                    }
                }
                VariantClear(&cn);
            }

            // Getting the Process ID related to the event
            hres = str->QueryInterface(IID_IWbemClassObject, reinterpret_cast<void **>(&apObjArray[i]));
            if (SUCCEEDED(hres))
            {
                _variant_t cpid;
                hres = apObjArray[i]->Get(L"ProcessId", 0, &cpid, NULL, NULL);
                if (SUCCEEDED(hres))
                {
                    try
                    {
                        tmp.pid = INT(cpid.intVal);
                    }
                    catch (std::exception &ex)
                    {
                        printf("Error %s\n", ex.what());
                    }
                }
                VariantClear(&cpid);
            }
        }
        cache.add(EventDetails(tmp));
        VariantClear(&vtProp);
        VariantClear(&vtType);
        printf("\n");
    }
    return WBEM_S_NO_ERROR;
}

HRESULT EventSink::SetStatus(
    /* [in] */ LONG lFlags,
    /* [in] */ HRESULT hResult,
    /* [in] */ __attribute__((unused)) BSTR strParam,
    /* [in] */ __attribute__((unused)) IWbemClassObject __RPC_FAR *pObjParam)
{
    if (lFlags == WBEM_STATUS_COMPLETE)
    {
        printf("Call complete. hResult = 0x%lx\n", hResult);
    }
    else if (lFlags == WBEM_STATUS_PROGRESS)
    {
        printf("Call in progress.\n");
    }

    return WBEM_S_NO_ERROR;
} // end of EventSink.cpp