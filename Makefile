# Compiler
CXX = g++
WASM_CXX = em++

# Compiler flags
CXXFLAGS = -Wall -Wextra
WASM_FLAGS = --no-entry

# Library name
LIBRARY = libchesscat.a

# Archiver
AR = ar
WASM_AR = emar

# Source files
SRC = chesscat.cpp

# Header files
HEADERS = pieces.hpp squares.hpp

# Object files
OBJS = $(SRC:.cpp=.o)

all: $(LIBRARY)


debug: $(LIBRARY)
debug: CXXFLAGS += -g

wasm: $(LIBRARY)
wasm: CXXFLAGS += $(WASM_FLAGS)
wasm: CXX = $(WASM_CXX)
wasm: AR = $(WASM_AR)

$(LIBRARY): $(OBJS)
	$(AR) rcs $@ $(OBJS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(LIBRARY)
