CC=gcc
CFLAGS=-Wall -Wextra -std=c11

all: game

game: main.o game.o board.o bot.o network_server.o network_client.o
	$(CC) $(CFLAGS) main.o game.o board.o bot.o network_server.o network_client.o -o game

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

game.o: game.c
	$(CC) $(CFLAGS) -c game.c

board.o: board.c
	$(CC) $(CFLAGS) -c board.c

bot.o: bot.c
	$(CC) $(CFLAGS) -c bot.c

network_server.o: network_server.c
	$(CC) $(CFLAGS) -c network_server.c

network_client.o: network_client.c
	$(CC) $(CFLAGS) -c network_client.c

clean:
	rm -f *.o game

run: game
	@./game

