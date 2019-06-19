IDIR=headers/
SDIR=src/

CC=g++

all: main.o cell.o board.o gfxhandler.o audiohandler.o
	$(CC) -o exec main.o cell.o board.o audiohandler.o gfxhandler.o -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system

main.o: src/main.cpp
	$(CC) -c src/main.cpp

cell.o: src/cell.cpp
	$(CC) -c src/cell.cpp

board.o: src/board.cpp
	$(CC) -c src/board.cpp

gfxhandler.o: src/gfxhandler.cpp
	$(CC) -c src/gfxhandler.cpp
	
audiohandler.o: src/audiohandler.cpp
	$(CC) -c src/audiohandler.cpp

.PHONY: clean

clean:
	rm -f main.o board.o cell.o gfxhandler.o audiohandler.o exec
