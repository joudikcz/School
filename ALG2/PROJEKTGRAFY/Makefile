# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -Wno-unused-result -Wdangling-pointer=1 -Werror=uninitialized -Werror=return-type -Werror=vla

# Target executable
TARGET = app

# Source files
SRCS = main.cpp graph.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile .cpp to .o
%.o: %.cpp graph.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJS) $(TARGET)