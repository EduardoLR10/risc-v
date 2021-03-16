# ============================== CONFIGURATIONS ============================== #
SYSTEMC_HOME=/usr/local/systemc-2.3.3

# Program name
EXECUTABLE=./riscv

# Definitions folder
IDIR=./include
# Sources folder
SDIR=./src
# Where to put the objs
ODIR=./obj

# Compiler/linker
CC=g++
# Extension of the definitions files
DEF_EXT=hpp
# Extension of the source files
SRC_EXT=cpp
# Compilation flags
CFLAGS=-Wall -g -I $(IDIR) -I$(SYSTEMC_HOME)/include -L$(SYSTEMC_HOME)/lib-linux64 -lsystemc
# Libs flags
LIBS=-lm

# All definitions sources
# NOTE: Update when adding .h files
DEPS != find $(IDIR)/ -name *.$(DEF_EXT)

# All compiled sources
# NOTE: Update when adding .cpp files
_OBJ != find $(SDIR)/ -name *.$(SRC_EXT) | sed -e 's/.$(SRC_EXT)/.o/g'
OBJ = $(patsubst $(SDIR)/%,$(ODIR)/%,$(_OBJ))

_FOLDERS != find $(SDIR)/ -name *.$(SRC_EXT) | cut -d "/" -f 3 | sed -e '/.cpp/d' | uniq
FOLDERS = $(patsubst %,$(ODIR)/%,$(_FOLDERS))

# ================================= TARGETS ================================== #

# Creates executable (linking)
$(EXECUTABLE): $(OBJ)
	$(CC) -o $@ $^ $(LIBS) $(CFLAGS)
# Creates objs for the executable
$(ODIR)/%.o: $(SDIR)/%.$(SRC_EXT) $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# Asks for a obj folder if needed
# the '|' tells to ignore the folder timestamp
$(OBJ): | $(ODIR) $(FOLDERS)

# Creates obj folder wheen needed
$(ODIR) $(FOLDERS):
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
