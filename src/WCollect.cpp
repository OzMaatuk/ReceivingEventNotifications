#include <conio.h>
#include "Collect.h"
#include "EventSink.h"

Collect::Collect()
{
}

Collect::~Collect()
{
}

int Collect::main(Config c)
{
    HRESULT hres;

    // Step 1: --------------------------------------------------
    // Initialize COM. ------------------------------------------

    hres = CoInitializeEx(0, COINIT_MULTITHREADED);
    if (FAILED(hres))
    {
        std::cout << "Failed to initialize COM library. Error code = 0x"
                  << std::hex << hres << std::endl;
        return 1; // Program has failed.
    }

    // Step 2: --------------------------------------------------
    // Set general COM security levels --------------------------

    hres = CoInitializeSecurity(
        NULL,
        -1,                          // COM negotiates service
        NULL,                        // Authentication services
        NULL,                        // Reserved
        RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication
        RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation
        NULL,                        // Authentication info
        EOAC_NONE,                   // Additional capabilities
        NULL                         // Reserved
    );

    if (FAILED(hres))
    {
        std::cout << "Failed to initialize security. Error code = 0x"
                  << std::hex << hres << std::endl;
        CoUninitialize();
        return 1; // Program has failed.
    }

    // Step 3: ---------------------------------------------------
    // Obtain the initial locator to WMI -------------------------

    IWbemLocator *pLoc = NULL;

    hres = CoCreateInstance(
        CLSID_WbemLocator,
        0,
        CLSCTX_INPROC_SERVER,
        IID_IWbemLocator, (LPVOID *)&pLoc);

    if (FAILED(hres))
    {
        std::cout << "Failed to create IWbemLocator object. "
                  << "Err code = 0x"
                  << std::hex << hres << std::endl;
        CoUninitialize();
        return 1; // Program has failed.
    }

    // Step 4: ---------------------------------------------------
    // Connect to WMI through the IWbemLocator::ConnectServer method

    IWbemServices *pSvc = NULL;

    // Connect to the local root\cimv2 namespace
    // and obtain pointer pSvc to make IWbemServices calls.
    BSTR bstr_root = SysAllocString(L"ROOT\\CIMV2");
    hres = pLoc->ConnectServer(
        bstr_root,
        NULL,
        NULL,
        0,
        WBEM_FLAG_CONNECT_USE_MAX_WAIT,
        0,
        0,
        &pSvc);

    if (FAILED(hres))
    {
        std::cout << "Could not connect. Error code = 0x"
                  << std::hex << hres << std::endl;
        pLoc->Release();
        CoUninitialize();
        return 1; // Program has failed.
    }

    std::cout << "Connected to ROOT\\CIMV2 WMI namespace" << std::endl;

    // Step 5: --------------------------------------------------
    // Set security levels on the proxy -------------------------

    hres = CoSetProxyBlanket(
        pSvc,                        // Indicates the proxy to set
        RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx
        RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx
        NULL,                        // Server principal name
        RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx
        RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
        NULL,                        // client identity
        EOAC_NONE                    // proxy capabilities
    );

    if (FAILED(hres))
    {
        std::cout << "Could not set proxy blanket. Error code = 0x"
                  << std::hex << hres << std::endl;
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return 1; // Program has failed.
    }

    // Step 6: -------------------------------------------------
    // Receive event notifications -----------------------------

    // Use an unsecured apartment for security
    IUnsecuredApartment *pUnsecApp = NULL;

    hres = CoCreateInstance(CLSID_UnsecuredApartment, NULL,
                            CLSCTX_LOCAL_SERVER, IID_IUnsecuredApartment,
                            (void **)&pUnsecApp);

    EventSink *pSink = new EventSink;
    pSink->AddRef();

    IUnknown *pStubUnk = NULL;
    pUnsecApp->CreateObjectStub(pSink, &pStubUnk);

    IWbemObjectSink *pStubSink = NULL;
    pStubUnk->QueryInterface(IID_IWbemObjectSink,
                             (void **)&pStubSink);

    // The ExecNotificationQueryAsync method will call
    // The EventQuery::Indicate method when an event created
    BSTR bstr_wql_created = SysAllocString(L"WQL");
    BSTR bstr_query_created = SysAllocString(L"SELECT * "
                                             "FROM __InstanceCreationEvent WITHIN 1 "
                                             "WHERE TargetInstance ISA 'Win32_Process'");
    hres = pSvc->ExecNotificationQueryAsync(
        bstr_wql_created,
        bstr_query_created,
        WBEM_FLAG_SEND_STATUS,
        NULL,
        pStubSink);

    // Check for errors.
    if (FAILED(hres))
    {
        printf("ExecNotificationQueryAsync failed "
               "with = 0x%lx\n",
               hres);
        pSvc->Release();
        pLoc->Release();
        pUnsecApp->Release();
        pStubUnk->Release();
        pSink->Release();
        pStubSink->Release();
        CoUninitialize();
        return 1;
    }

    // The ExecNotificationQueryAsync method will call
    // The EventQuery::Indicate method when an event deleted
    BSTR bstr_wql_deleted = SysAllocString(L"WQL");
    BSTR bstr_query_deleted = SysAllocString(L"SELECT * "
                                             "FROM __InstanceDeletionEvent WITHIN 1 "
                                             "WHERE TargetInstance ISA 'Win32_Process'");
    hres = pSvc->ExecNotificationQueryAsync(
        bstr_wql_deleted,
        bstr_query_deleted,
        WBEM_FLAG_SEND_STATUS,
        NULL,
        pStubSink);

    // Check for errors.
    if (FAILED(hres))
    {
        printf("ExecNotificationQueryAsync failed "
               "with = 0x%lx\n",
               hres);
        pSvc->Release();
        pLoc->Release();
        pUnsecApp->Release();
        pStubUnk->Release();
        pSink->Release();
        pStubSink->Release();
        CoUninitialize();
        return 1;
    }

    Writer *writer = new Writer(c.events_file_path);
    Reader *reader = new Reader(c.events_file_path);
    Mapper *mapper = new Mapper();
    Analyzer *analyzer = new Analyzer(c);

    mapper->load(reader->start());
    // While asyc listening to events in background.
    while (!_kbhit())
    {
        try
        {
            const std::queue<EventDetails> &tmpQueue = pSink->cache.getAndClear();
            const std::list<std::vector<std::string>> &tmp = Cache<EventDetails>::cacheToStringList(tmpQueue, [](EventDetails* e)
                                                                                                    { return e->eventDetailsToStringVector(); });
            if (!tmp.empty())
            {
                auto asyncThread = std::async(std::launch::async, [&mapper, &tmp]()
                                              { return mapper->start(tmp); });
                asyncThread.wait();
                asyncThread = std::async(std::launch::async, [&analyzer, &mapper]()
                                         { return analyzer->start(mapper->getMap()); });
                asyncThread = std::async(std::launch::async, [&writer, &tmp]()
                                         { return writer->start(tmp); });
            }
            Sleep(c.sleep_interval);
        }
        catch (MyException &ex)
        {
            LOG(ERROR) << "My Exception thrown: " << ex.what() << std::endl;
        }
    }

    // hres = pSvc->CancelAsyncCall(pStubSink);

    // Cleanup
    // ========

    pSvc->Release();
    pLoc->Release();
    pUnsecApp->Release();
    pStubUnk->Release();
    pSink->Release();
    pStubSink->Release();
    CoUninitialize();

    delete reader;
    delete mapper;
    delete analyzer;
    delete writer;

    return 0; // Program successfully completed.
}