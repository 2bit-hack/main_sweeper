#include "../headers/board.h"

Board::Board()
{
    for(int i = 0; i < ROW_COUNT; i++) {
        for(int j = 0; j < COL_COUNT; j++) {
            this->gameBoard.emplace_back(Cell(i,j));
        }
    }
}

void Board::setup() {
    std::mt19937 mersenne(static_cast<std::mt19937::result_type>(std::time(nullptr)));
    std::uniform_int_distribution<> minePlaceRow(0, ROW_COUNT-1);
    std::uniform_int_distribution<> minePlaceCol(0, COL_COUNT-1);
    int numMines = MINE_COUNT;
    while(numMines) {
        unsigned long row = static_cast<unsigned long>(minePlaceRow(mersenne));
        unsigned long col = static_cast<unsigned long>(minePlaceCol(mersenne));
        if(this->gameBoard[row][col].mineCheck())  // already has a mine
            continue;
        this->gameBoard[row][col].setMine();
        numMines--;
    }
    // TODO: set neighbor mine count
}

void Board::debug_show() {
    for(unsigned long i = 0; i < ROW_COUNT; i++) {
        for(unsigned long j = 0; j < COL_COUNT; j++) {
            char sym;
            if(this->gameBoard[i][j].mineCheck())
                sym = 'X';
            else {
                sym = 'O';
            }
            std::cout << sym << " ";
        }
        std::cout << "\n";
    }
}
