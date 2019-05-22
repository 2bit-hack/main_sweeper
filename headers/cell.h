#ifndef CELL_H
#define CELL_H

#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <memory>

// used exclusively for storing the state of a cell
// all actual computations should be handled by the Board class

class Cell {
private:
    enum class State {
        UNREVEALED,
        FLAGGED,
        REVEALED
    };
    int xPos, yPos;
    bool isMine;
    int neighborCount;
    State state;
public:
    Cell(int xPos=0, int yPos=0, bool isMine=false, int neighborCount=0)
    :xPos(xPos), yPos(yPos), isMine(isMine), neighborCount(neighborCount){}
    int getPosX();
    int getPosY();
    bool mineCheck();
    void setMine();
    int neighbors();
    State getState();
};

#endif // CELL_H
