CC=cc
CFLAGS=-Wall -g -DNDEBUG

# Name of the main C file
MAIN=ex22_main.c

# Find all C source files in the current directory
SOURCES=$(filter-out $(MAIN), $(wildcard *.c))

# Generate object file names by replacing ".c" extension with ".o"
OBJECTS=$(SOURCES:.c=.o)

# Name of the executable
EXE=ex22_main

all: $(EXE)

# Compile each source file into an object file
$(OBJECTS): %.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

# Link all object files together with tha main to create the executable
$(EXE): $(MAIN) $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(wildcard *.o) $(EXE)
