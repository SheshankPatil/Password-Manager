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
CXX_SRCS = src/main.cpp src/password_id.cpp src/user_management.cpp src/encyrpt.cpp

# Object files directory
OBJ_DIR = obj
C_OBJS = $(C_SRCS:src/%.c=$(OBJ_DIR)/%.o)
CXX_OBJS = $(CXX_SRCS:src/%.cpp=$(OBJ_DIR)/%.o)
OBJS = $(C_OBJS) $(CXX_OBJS)

# Executable
TARGET = password_manager

# Database directory
DB_DIR = Database

# Default target
all: $(TARGET) create_db create_tables 

# Link the executable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)
	@clear

# Compile C++ source files
$(OBJ_DIR)/%.o: src/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile C source files
$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create object files directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Create database
create_db:
	$(MAKE) --no-print-directory -C $(DB_DIR) create_db
	@clear

# Create tables
create_tables:
	$(MAKE) --no-print-directory -C $(DB_DIR) create_tables
	@clear

# Clean up the build and database
clean: clean_db
	rm -f $(OBJS) $(TARGET)
	rm -rf $(OBJ_DIR)
	@clear

# Clean up the database
clean_db:
	$(MAKE) -C $(DB_DIR) clean
	@clear
