CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCDIR = src
OUTPUTDIR = bin
SOURCES = $(shell find $(SRCDIR) -name '*.c')
OBJECTS = $(addprefix $(OUTPUTDIR)/,$(notdir $(SOURCES:.c=.o)))
EXECUTABLE = $(OUTPUTDIR)/rd.exe

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

$(OUTPUTDIR)/%.o: $(SOURCES)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OUTPUTDIR)/*
