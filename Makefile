# Compiler and compiler options
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Libraries to link against
LIBS = -lssl -lcrypto

# Source files and the name of the executable
# Directory for source files
SRC_DIR = ./

# List of all .cpp files in the source directory
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)

# Generate corresponding object file names
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.cpp=%.o)

# OpenSSL library and include paths
OPENSSL_LIBS = -lssl -lcrypto
OPENSSL_INCLUDE = -I/usr/include/openssl

EXECUTABLE = aes_crypto

# Default target: build the executable
all: $(EXECUTABLE)

# Rule for building the executable
$(EXECUTABLE): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(OPENSSL_LIBS)

# Rule for compiling .cpp files into .o files
%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(OPENSSL_INCLUDE)

# Clean target: remove the executable and object files
clean:
	rm -f $(EXECUTABLE) $(OBJ_FILES)