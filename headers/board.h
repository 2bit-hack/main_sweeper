#ifndef BOARD_H
#define BOARD_H

#include "cell.h"
// a grid of cells
// does all game related computations

class Board
{
private:
    std::vector<std::vector<Cell>> gameBoard;
    bool hasWon, hasLost;
    int minesRemaining;
public:
    Board();
    void setup();
};

#endif // BOARD_H
