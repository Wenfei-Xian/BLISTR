SHELL=/bin/sh

OBJS= main.o fuzzy.o perfect.o sequence.format.o
CXXFLAGS = -O3 -Wall -std=c++17
CC = g++
LIBS=-lz

BLISTR: ${OBJS}
	${CC} ${CXXFLAGS} -o $@ ${OBJS} ${LIBS}
clean:
	-rm -rf *.o BLISTR
