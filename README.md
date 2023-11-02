# Receiving Event Notifications

The ReceivingEventNotifications2 project is a C++ application designed to monitor process events on a Windows system. It utilizes Windows Management Instrumentation (WMI) to collect real-time data on process start and stop times. This data is then analyzed to create insights into process duration distribution. 

## Project Structure
The project is organized into the following main directories:

- `src/`: Contains the source code files (`.cpp`), which include `Config.cpp`, `WCollect.cpp`, `EventSink.cpp`, `Mapper.cpp`, `ReaderCSV.cpp`, `WriterCSV.cpp`, `Analyzer.cpp` and `main.cpp`.
- `include/`: Contains the header files (`.h`) for the project.
- `obj/`: Contains the object files (`.o`) generated during the build process.
- `bin/`: Contains the resulting executable files from the build process.
- `test/`: Contains the test source code files and test data.
- `logs/`: Contains log files generated during program execution.

## Dependencies
The project uses a variety of external libraries, which need to be installed for successful compilation:

- ole32 (only for Windows systems)
- oleaut32 (only for Windows systems)
- ws2_32 (only for Windows systems)
- wbemuuid (only for Windows systems)
- jsoncpp
- glog
- gtest
- backtrace
- inotify (only for Unix-based systems)
- libc (only for Unix-based systems)

## Execution Instructions
To compile and run the project, follow these steps:

1. Open a terminal window.
2. Navigate to the project directory.
3. Run the command `make all` to compile the project. This will create the executable files in the `bin/` directory.
4. To run the main program, execute the command `./bin/main.exe`.
5. To run the tests, execute the command `make test` followed by `./bin/test.exe`.

## Application Output

The program will output:
1. CSV file containing the received Events notifications.
2. JSON file for Mapped histogram for each process (optional).
3. Insight for each process after analyzing the histogram.
Files paths are specified in the application config.

## Notes:

Dedicated Git configuration been used to make no diffrence between windows - linux files format:

git config core.filemode false

git config --global core.autocrlf true

## Sources:

https://learn.microsoft.com/en-gb/windows/win32/wmisdk/example--receiving-event-notifications-through-wmi-?redirectedfrom=MSDN

https://stackoverflow.com/questions/6705396/undefined-reference-to-imp-coinitialize4

https://stackoverflow.com/questions/51363689/qt5-mingw-undefined-reference-to-convertstringtobstr

https://learn.microsoft.com/en-us/windows/win32/api/wbemcli/nf-wbemcli-iwbemlocator-connectserver

https://stackoverflow.com/questions/16316485/how-to-get-data-iwbemclassobject