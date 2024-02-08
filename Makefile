
#-----------------------
# Compiler/linker flags
#-----------------------

CXX = g++

# Compiler flags:
CXXFLAGS = \
	-std=c++17 \
	-Wall      \
	-Wextra    \
	-Werror    \
	-O2

# Linker flags:
# LDFLAGS =

# Select build mode:
ifeq ($(DEBUG),1)
	CXXFLAGS += -g
else
	CXXFLAGS  += -flto
	LDFLAGS += -flto
endif

#--------
# Colors
#--------

# Use ANSI color codes:
BRED    = \033[1;31m
BGREEN  = \033[1;32m
BYELLOW = \033[1;33m
GREEN   = \033[1;35m
BCYAN   = \033[1;36m
RESET   = \033[0m

#-------
# Files
#-------


# Add "include" folder to header search path:
#CXXFLAGS += -I $(abspath include)

INCLUDES = $(wildcard *.hpp) $(wildcard */*.hpp) $(wildcard */*/*.hpp)

SOURCES = $(wildcard *.cpp) $(wildcard */*.cpp) $(wildcard */*/*.cpp)

VPATH = $(dir $(SOURCES))

OBJDIR = ./build
OBJECTS := $(notdir $(SOURCES))
OBJECTS := $(patsubst %.cpp,$(OBJDIR)/%.o,$(OBJECTS))

EXECUTABLE = build/test

#---------------
# Build process
#---------------

default: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@printf "$(BYELLOW)Linking executable $(BCYAN)$@$(RESET)\n"
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@


$(OBJDIR)/%.o: %.cpp $(INCLUDES) Makefile
	@printf "$(BYELLOW)Building object file $(BCYAN)$@$(RESET)\n"
	@mkdir -p build
	$(CXX) -c $< $(CXXFLAGS) -o $@

#--------------
# Test scripts
#--------------

# Run program:
run: $(EXECUTABLE)
	./$(EXECUTABLE)

#---------------
# Other tools
#---------------

clean:
	@printf "$(BYELLOW)Cleaning build directory $(RESET)\n"
	rm -rf build

# List of non-file targets:
.PHONY: run clean default