CC = gcc
CFLAGS = -lncurses -lm -I$(IDIR)

IDIR = ./include
SRCDIR = ./src/
OUTDIR = ./build/
OUT = nethack

SOURCES = $(SRCDIR)*.c $(SRCDIR)*/*.c

all: clean compile run

compile:
	$(CC) $(SOURCES) $(CFLAGS) -o $(OUTDIR)$(OUT)

run:
	$(OUTDIR)$(OUT)

clean:
	rm $(OUTDIR)* -f
