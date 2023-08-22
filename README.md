# Receiving Event Notifications

This project demonstrates how to receive event notifications using WMI (Windows Management Instrumentation) in C++.

## Dependencies

- Windows SDK

## Building

1. Open the project in Visual Studio.
2. Build the solution (Ctrl+Shift+B).

## Running

1. Open a command prompt with administrator privileges.
2. Navigate to the directory containing the compiled executable (./bin/).
3. Run the executable.

Execution CMD:
```g++ .\ReceivingEventNotifications.cpp .\eventsink.cpp -o output.exe -lole32 -loleaut32 -lws2_32 -lwbemuuid -std=c++11```

## Output

The program will output:
1. CSV file containing the received Events notifications.
2. JSON file for Mapped histogram for each process.
3. Insight for each process after analyzing the histogram.

## Sources:

https://learn.microsoft.com/en-gb/windows/win32/wmisdk/example--receiving-event-notifications-through-wmi-?redirectedfrom=MSDN

https://stackoverflow.com/questions/6705396/undefined-reference-to-imp-coinitialize4

https://stackoverflow.com/questions/51363689/qt5-mingw-undefined-reference-to-convertstringtobstr

https://learn.microsoft.com/en-us/windows/win32/api/wbemcli/nf-wbemcli-iwbemlocator-connectserver

https://stackoverflow.com/questions/16316485/how-to-get-data-iwbemclassobject