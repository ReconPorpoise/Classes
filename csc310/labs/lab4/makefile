# This is a comment line
CC=g++
# CFLAGS will be the options passed to the compiler.
CFLAGS= -c

all: prog

prog: library.o mp3.o
	$(CC) library.o mp3.o -o prog

library.o: library.cpp
	$(CC) $(CFLAGS) library.cpp

mp3.o: mp3.cpp
	$(CC) $(CFLAGS) mp3.cpp

clean:
	rm -rf *.o
