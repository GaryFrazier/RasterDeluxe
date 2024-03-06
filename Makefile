CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBS = -lgdi32
SRCDIR = src
OUTPUTDIR = bin
SOURCES = $(shell find $(SRCDIR) -name '*.c')
OBJECTS = $(addprefix $(OUTPUTDIR)/,$(notdir $(SOURCES:.c=.o)))
EXECUTABLE = $(OUTPUTDIR)/rd.exe

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

$(OUTPUTDIR)/%.o: $(SOURCES)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OUTPUTDIR)/*
