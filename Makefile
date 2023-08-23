# This is a makefile for the project described in the conversation with Bard.

# The compiler to use.
CC = g++

# The standard to use.
STD = c++20

# The flags to pass to the compiler.
# -Werror
CFLAGS = -std=$(STD) -Wall -Wextra -Iinclude -g

# The external libraries used
LDLIBS = -lole32 -loleaut32 -lws2_32 -lwbemuuid -ljsoncpp -lglog -lgtest

# The directories to search for source files.
SRC_DIR = src/
SRCS = main.cpp EventSink.cpp Mapper.cpp ReaderCSV.cpp WriterCSV.cpp

# The object files to create.
OBJ_DIR = obj/
OBJS = $(SRCS:.cpp=.o)
OOBJ=$(join $(addsuffix $(OBJ_DIR), $(dir $(SRCS))), $(notdir $(SRCS:.cpp=.o)))

# The executable file to create.
TARGET = bin/main.exe

# The rule for compiling a source file to an object file.
$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

# The rule for linking the object files to create the executable file.
$(TARGET): $(OOBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

# The default target.
all: $(TARGET)

# Clean up the object files and the executable file.
# rm -f $(OOBJ) $(TARGET)
clean:
	if exist obj\*.o del obj\*.o
	if exist bin\main.exe del bin\main.exe