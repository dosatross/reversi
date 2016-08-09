CC=gcc
CFLAGS=-ansi -pedantic -Werror -c

all: reversi

reversi: reversi.o game.o gameboard.o player.o scoreboard.o utility.o
	$(CC)  reversi.o game.o gameboard.o player.o scoreboard.o utility.o -o reversi

reversi.o: reversi.c
	$(CC) $(CFLAGS) reversi.c

game.o: game.c
	$(CC) $(CFLAGS) game.c

gameboard.o: gameboard.c
	$(CC) $(CFLAGS) gameboard.c

player.o: player.c
	$(CC) $(CFLAGS) player.c

scoreboard.o: scoreboard.c
	$(CC) $(CFLAGS) scoreboard.c

utility.o: utility.c
	$(CC) $(CFLAGS) utility.c

clean:
	rm -rf *o reversi
