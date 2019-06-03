# main_sweeper
## A simple minesweeper clone written in C++ using SFML

Still very much a work in progress

The makefile hasn't been written yet, in the primary directory, compile with
```
g++ -c src/cell.cpp src/board.cpp src/gfxhandler.cpp src/main.cpp
g++ -o exec main.o cell.o board.o gfxhandler.o -lsfml-graphics -lsfml-window -lsfml-system
```
Then run exec

Beware of any potentially hazardous code, you have been warned

Will update readme once a stable release is out
