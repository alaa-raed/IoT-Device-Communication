# Compiler
CXX = g++
# Compiler flags
CXXFLAGS = -Iinc -Wall -Wextra -std=c++11

# Source files
SRCDIR = src
SOURCES = $(wildcard $(SRCDIR)/*.cpp)

# Output executables
CLIENT = tcp_client
SERVER = tcp_server

# Build rules
all: $(CLIENT) $(SERVER)

$(CLIENT): main_client.cpp $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $@ $< $(SOURCES)

$(SERVER): main_server.cpp $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $@ $< $(SOURCES)

# Clean rule to remove generated files
clean:
	rm -f $(CLIENT) $(SERVER)

# Phony targets
.PHONY: all clean

