#compiler and flags
CC=gcc
CFLAGS=-g -ansi -pedantic -Werror

#directories
SDIR=src
ODIR=obj
BDIR=bin

#program name
BNAME=reversi

#whitepace separated source files
SOURCES=$(wildcard $(SDIR)/*.c)
#whitepace separated object files
OBJECTS=$(patsubst $(SDIR)/%.c,$(ODIR)/%.o,$(SOURCES))
EXECUTABLE=$(BDIR)/$(BNAME).exe

all: installdirs $(EXECUTABLE)

#compile object to binary
$(EXECUTABLE):  $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

#compile source to object
$(OBJECTS): $(ODIR)/%.o : $(SDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

installdirs:
	@mkdir -p $(BDIR)
	@mkdir -p $(ODIR)

clean:
	-rm $(OBJECTS) $(EXECUTABLE)
