SHELL=/bin/sh
LIB_WFA=$(FOLDER_LIB)/libwfa.a

OBJS= main.o fuzzy.o perfect.o sequence.format.o
CXXFLAGS = -O3 -Wall -std=c++17
CC = g++
LIBS=-fopenmp -lm -lz

BLISTR: ${OBJS}
	${CC} ${CXXFLAGS} -o $@ ${OBJS} ${LIBS}
clean:
	-rm -rf *.o BLISTR
