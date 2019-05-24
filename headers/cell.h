#ifndef CELL_H
#define CELL_H

#define ROW_COUNT 10
#define COL_COUNT 10
#define MINE_COUNT 10

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
    Cell(int xPos=0, int yPos=0, bool isMine=false, int neighborCount=0, State state = State::UNREVEALED)
    :xPos(xPos), yPos(yPos), isMine(isMine), neighborCount(neighborCount), state(state){
    }
    int getPosX();
    int getPosY();
    bool mineCheck();
    void setMine();
    int neighbors();
    State getState();
    friend class Board;
};

#endif // CELL_H
