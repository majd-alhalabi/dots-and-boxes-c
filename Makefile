CC=gcc
CFLAGS=-Wall -Wextra -std=c11

all: game

run:
	@./game

game: main.o game.o board.o
	$(CC) $(CFLAGS) main.o game.o board.o -o game

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

game.o: game.c
	$(CC) $(CFLAGS) -c game.c

board.o: board.c
	$(CC) $(CFLAGS) -c board.c

clean:
	rm -f *.o game
