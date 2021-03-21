# ============================== CONFIGURATIONS ============================== #

# Program name
EXECUTABLE=./simulator

# Definitions folder
IDIR=./include
# Sources folder
SDIR=./src
# Where to put the objs
ODIR=$(SDIR)/obj

# Compiler/linker
CC=g++
# Extension of the definitions files
DEF_EXT=h
# Extension of the source files
SRC_EXT=cpp
# Compilation flags
CFLAGS=-Wall -g -I $(IDIR) -std=c++17
# Libs flags
LIBS=-lm

# All definitions sources
# NOTE: Update when adding .h files
DEPS != ls $(IDIR)/*.$(DEF_EXT)

# All compiled sources
# NOTE: Update when adding .cpp files
_OBJ != ls $(SDIR)/*.$(SRC_EXT) | sed -e 's/.$(SRC_EXT)/.o/g'
OBJ = $(patsubst $(SDIR)/%,$(ODIR)/%,$(_OBJ))

# ================================= TARGETS ================================== #

# Creates executable (linking)
$(EXECUTABLE): $(OBJ)
	$(CC) -o $@ $^ $(LIBS) $(CFLAGS)

# Creates objs for the executable
$(ODIR)/%.o: $(SDIR)/%.$(SRC_EXT) $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# Asks for a obj folder if needed
# the '|' tells to ignore the folder timestamp
$(OBJ): | $(ODIR)

# Creates obj folder wheen needed
$(ODIR):
	mkdir -p $@

# Compiles all files
all: $(EXECUTABLE)

# Removel all compilation files
clean:
	rm -rf $(ODIR) $(EXECUTABLE)

# Runs the program
run: $(EXECUTABLE)
	./$<

.PHONY: run clean all

# ================================= THE END ================================== #
