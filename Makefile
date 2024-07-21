# Compiler
CXX = g++
CC = gcc

# Compiler flags
CXXFLAGS = -I../include
CFLAGS = -I../include

# Linker flags
LDFLAGS = -lmysqlclient

# Source files
C_SRCS = src/database.c
CXX_SRCS = src/main.cpp src/password_id.cpp src/user_management.cpp

# Object files
OBJS = $(C_SRCS:.c=.o) $(CXX_SRCS:.cpp=.o)

# Executable
TARGET = password_manager

# Default target
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compile C++ source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile C source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up the build
clean:
	rm -f $(OBJS) $(TARGET)
