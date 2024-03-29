CC = gcc
CFLAGS = -Werror
LIBS = -lSDL2 
LIBDIR= -L./lib
INCLUDEDIR= -I./include
SRCDIR = src
OUTPUTDIR = bin
SOURCES = $(shell find $(SRCDIR) -name '*.c')
OBJECTS = $(addprefix $(OUTPUTDIR)/,$(notdir $(SOURCES:.c=.o)))
EXECUTABLE = $(OUTPUTDIR)/rd.exe

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@  $(LIBDIR) $(LIBS)

$(OUTPUTDIR)/%.o: $(SOURCES)
	$(CC) $(INCLUDEDIR) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OUTPUTDIR)/*
