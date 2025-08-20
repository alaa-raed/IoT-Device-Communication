# Makefile

# Compiler
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -I inc

# Directories
SRC_DIR = src
INC_DIR = inc
CLIENT1_DIR = UDP_client1
CLIENT2_DIR = UDP_client2
SERVER_DIR = UDP_server

# Source files
CLIENT1_SRC = UDP_Client1.cpp
CLIENT2_SRC = UDP_Client2.cpp
SERVER_SRC = UDP_Server.cpp

# Object files
OBJS = $(SRC_DIR)/Channel.o $(SRC_DIR)/Channel_C_S.o $(SRC_DIR)/Socket.o $(SRC_DIR)/Socket_TCP_UDP.o

# Executables
CLIENT1_EXEC = $(CLIENT1_DIR)/UDP_Client1
CLIENT2_EXEC = $(CLIENT2_DIR)/UDP_Client2
SERVER_EXEC = $(SERVER_DIR)/UDP_Server

# Default target
all: $(CLIENT1_DIR) $(CLIENT2_DIR) $(SERVER_DIR) $(CLIENT1_EXEC) $(CLIENT2_EXEC) $(SERVER_EXEC)

# Create directories if they do not exist
$(CLIENT1_DIR):
	mkdir -p $@
	
$(CLIENT2_DIR):
	mkdir -p $@

$(SERVER_DIR):
	mkdir -p $@

# Compile and link the client 1
$(CLIENT1_EXEC): $(CLIENT1_SRC) $(OBJS) | $(CLIENT1_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $< $(OBJS)

# Compile and link the client 2
$(CLIENT2_EXEC): $(CLIENT2_SRC) $(OBJS) | $(CLIENT2_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $< $(OBJS)

# Compile and link the server
$(SERVER_EXEC): $(SERVER_SRC) $(OBJS) | $(SERVER_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $< $(OBJS)

# Compile source files into objects
$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up the build
clean:
	rm -rf $(SRC_DIR)/*.o $(CLIENT1_EXEC) $(CLIENT2_EXEC) $(SERVER_EXEC)

.PHONY: all clean

