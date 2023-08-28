# This is a makefile for the project described in the conversation with Bard.

# The compiler to use.
CC = g++

# The standard to use.
STD = c++23

# The flags to pass to the compiler.
# -Werror
CFLAGS = -std=$(STD) -Wall -Wextra -Iinclude -g

# The external libraries used
LDLIBS = -lole32 -loleaut32 -lws2_32 -lwbemuuid -ljsoncpp -lglog -lgtest

# Config file path
CNFG = config/main.json

# The directories to search for source files.
SRC_DIR = src/
SRCS = main.cpp EventSink.cpp Mapper.cpp ReaderCSV.cpp WriterCSV.cpp

# The tests files
TESTS = src/Mapper.cpp src/ReaderCSV.cpp test/TestMapper.cpp test/TestReaderCSV.cpp test/test.cpp

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
all: clean $(TARGET) $(CNFG)

# Clean up the object files and the executable file.
# rm -rf $(OOBJ) $(TARGET) $(TEST) logs\* # For linux
clean:
	if exist obj\*.o del obj\*.o
	if exist bin\*.exe del bin\*.exe
	if exist logs\*.log del logs\*.log