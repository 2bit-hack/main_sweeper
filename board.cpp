#include "board.h"

Board::Board()
{
    for(int i = 0; i < ROW_COUNT; i++) {
        for(int j = 0; j < COL_COUNT; j++) {
            this->gameBoard.emplace_back(Cell(i,j));
        }
    }
}

void Board::setup() {
    // TODO: randnum engine
    // TODO: set mines
    // TODO: set neighbor mine count
}
