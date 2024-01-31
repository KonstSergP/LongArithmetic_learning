
CC = g++

# Compiler flags:
CFLAGS = \
	-std=c++17 \
	-Wall      \
	-Wextra    \
	-Werror


# Color codes:
BRED    = \033[1;31m
BGREEN  = \033[1;32m
BYELLOW = \033[1;33m
GREEN   = \033[1;35m
BCYAN   = \033[1;36m
RESET   = \033[0m

#-------
# Files
#-------

INCLUDES = include/longArithmetic.hpp include/longNumbers.hpp

# Add "include" folder to header search path:
CFLAGS += -I $(abspath include)

VPATH = src

# List of sources:
SOURCES = longNumbers.cpp longArithmetic.cpp test.cpp

OBJECTS = longNumbers.o longArithmetic.o test.o

EXECUTABLE = test

#---------------
# Build process
#---------------

default: $(EXECUTABLE)


$(EXECUTABLE): $(OBJECTS)
	@printf "$(BYELLOW)Linking executable $(BCYAN)$@$(RESET)\n"
	@printf "$(BYELLOW)Linking executable $(BCYAN)$(SOURCES)$(RESET)\n"
	@printf "$(BYELLOW)Linking executable $(BCYAN)$(OBJECTS)$(RESET)\n"
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o: src/%.cpp $(INCLUDES)
	@printf "$(BYELLOW)Building object file $(BCYAN)$@$(RESET)\n"
	@mkdir -p build
	$(CC) -c $< $(CFLAGS) -o build/$@


#--------------
# Test scripts
#--------------

# Run program:
run: $(EXECUTABLE)
	./$(EXECUTABLE)

#---------------
# Other utils
#---------------

clean:
	@printf "$(BYELLOW)Cleaning build and resource directories$(RESET)\n"
	rm -rf build

# List of non-file targets:
.PHONY: run clean default