CC = gcc
CFLAGS = -Wall -Wextra -std=c11

all: game2048

game2048: game2048.o utility.o
	$(CC) $(CFLAGS) -o $@ $^

game2048.o: game2048.c utility.h
	$(CC) $(CFLAGS) -c game2048.c

utility.o: utility.c utility.h
	$(CC) $(CFLAGS) -c utility.c

clean:
	rm -f *.o game2048