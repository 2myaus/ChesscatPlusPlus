# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra

# Library name
LIBRARY = libchesscat.a

# Source files
SRC = chesscat.cpp

# Header files
HEADERS = pieces.hpp squares.hpp

# Object files
OBJS = $(SRC:.cpp=.o)

all: $(LIBRARY)

$(LIBRARY): $(OBJS)
	ar rcs $@ $(OBJS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(LIBRARY)
