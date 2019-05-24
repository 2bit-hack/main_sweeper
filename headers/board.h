#ifndef BOARD_H
#define BOARD_H

#include "cell.h"

// a grid of cells
// does all game related computations

class Board
{
private:
    std::vector<Cell> gameBoard;
    bool hasWon, hasLost;
    int minesRemaining;
public:
    Board();
    ~Board();
    void setup();
    void debug_show();
    void debug_show_counts();
};

#endif // BOARD_H
