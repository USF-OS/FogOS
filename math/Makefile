CC=gcc
CFLAGS=-Wall -Wextra -std=c11

all: run

test: test.o math.o
	$(CC) $(CFLAGS) -o test test.o math.o

test.o: test.c math.h
	$(CC) $(CFLAGS) -c test.c

math.o: math.c math.h
	$(CC) $(CFLAGS) -c math.c

run: test
	./test

clean:
	rm -f *.o test

