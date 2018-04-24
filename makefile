CC=g++
#CFLAGS=-c -Wall -g
CFLAGS=-c

all: game

game: main.o functions.o snake.o
	$(CC) main.o functions.o snake.o -o game -lncurses
main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp
functions.o: functions.cpp
	$(CC) $(CFLAGS) functions.cpp
snake.o: snake.cpp
	$(CC) $(CFLAGS) snake.cpp
clean:
	rm *o game