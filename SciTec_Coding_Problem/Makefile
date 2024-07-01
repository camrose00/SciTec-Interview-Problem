# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++17

# Target executable
TARGET = main

# Source files
SRCS = main.cpp VectorLogic.cpp ECEF.cpp LLA.cpp Converter.cpp
INCS = VectorLogic.hpp ECEF.hpp LLA.hpp Converter.hpp
# Object files
DEBUG = ./Debug

OBJS = $(SRCS:%.cpp=$(DEBUG)/%.o)


	
# Default rule
all: $(TARGET)

$(DEBUG):
	mkdir -p $(DEBUG)
#MAIN = main.cpp
# Rule to link object files to create the executable
$(TARGET): $(DEBUG) $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile source files into object files
$(DEBUG)/%.o: %.cpp  $(INCS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up the build directory
clean:
	rm -f $(TARGET) $(OBJS)
	rm -rf $(DEBUG)

# Phony targets
.PHONY: all clean
