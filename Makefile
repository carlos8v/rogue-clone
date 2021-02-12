CC = gcc
CFLAGS = -lncurses

SRCDIR = ./src/
OUTDIR = ./build/
OUT = nethack

SOURCES = ${SRCDIR}*.c

all: clean compile run

compile:
	${CC} ${SOURCES} ${CFLAGS} -o ${OUTDIR}${OUT}

run:
	${OUTDIR}${OUT}

clean:
	rm ${OUTDIR}* -f
