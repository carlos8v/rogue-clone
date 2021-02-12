CC = gcc
CFLAGS = -lncurses

SRCDIR = ./src/
OUTDIR = ./build/
OUT = nethack

SOURCES = ${SRCDIR}*.c

all: compile run clean

compile:
	${CC} ${SOURCES} ${CFLAGS} -o ${OUTDIR}${OUT}

run:
	${OUTDIR}${OUT}

clean:
	rm ${OUTDIR}*