# This is a makefile for the project described in the conversation with Bard.

# The compiler to use.
CC = g++

# The standard to use.
STD = c++23

# The flags to pass to the compiler.
# -Werror
CFLAGS = -std=$(STD) -Wall -Wextra -Wno-unknown-pragmas -Iinclude -g -no-pie -fno-pie -DBOOST_STACKTRACE_USE_BACKTRACE

# The external libraries used.
# Determine OS type and set libraries properly.
ifeq ($(OS),Windows_NT)
	LDLIBS = -lole32 -loleaut32 -lws2_32 -lwbemuuid -ljsoncpp -lglog -lgtest -lbacktrace
else
	LDLIBS = -ljsoncpp -lglog -lgtest -lbacktrace
endif

# The directories to search for source files.
# Determine OS type and set libraries properly.
SRC_DIR = src/

ifeq ($(OS),Windows_NT)
	SRCS = Config.cpp WriterCSV.cpp Cache.cpp EventSink.cpp Mapper.cpp ReaderCSV.cpp Analyzer.cpp WCollect.cpp main.cpp
else
	SRCS = UCollect.cpp main.cpp
endif

# The tests files
TESTS = src/Analyzer.cpp src/Mapper.cpp src/WriterCSV.cpp src/ReaderCSV.cpp test/TestMapper.cpp test/TestWriterCSV.cpp test/TestReaderCSV.cpp test/TestAnalyzer.cpp test/TestIntegration.cpp test/test.cpp

# The object files to create.
OBJ_DIR = obj/
OBJS = $(SRCS:.cpp=.o)
OOBJ=$(join $(addsuffix $(OBJ_DIR), $(dir $(SRCS))), $(notdir $(SRCS:.cpp=.o)))

# The executable file to create.
TARGET = bin/main.exe

# The test file to create.
TEST = bin/test.exe

# The rule for compiling a source file to an object file.
$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

# The rule for compiling tests
$(TEST):
	$(CC) $(CFLAGS) -o $(TEST) $(TESTS) $(LDLIBS)

# The rule for linking the object files to create the executable file.
$(TARGET): $(OOBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

# The rule for creating test executable
test: clean $(TEST)

# The default target.
all: clean $(TARGET)

# Clean up the object files and the executable file.
# Determine OS type and set libraries properly.
ifeq ($(OS),Windows_NT)
clean:
	if exist obj\*.o del obj\*.o
	if exist bin\*.exe del bin\*.exe
	if exist logs\*.log.* del logs\*.log.*
	if exist test_data\*.csv del test_data\*.csv
	if exist test_data\*.json del test_data\*.json
else
clean:
	rm -rf obj\*
	rm -rf bin\*
	rm -rf logs\*
	rm -rf test_data\*
endif