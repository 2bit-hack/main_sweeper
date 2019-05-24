#include "../headers/board.h"

Board::Board()
{
    this->gameBoard.reserve(100);
    for(unsigned long i = 0; i < ROW_COUNT; i++) {
        for(unsigned long j = 0; j < COL_COUNT; j++) {
            this->gameBoard.emplace_back(i, j);
        }
    }
}

Board::~Board() {
    this->gameBoard.clear();
}

void Board::setup() {
    std::mt19937 mersenne(static_cast<std::mt19937::result_type>(std::time(nullptr)));
    std::uniform_int_distribution<> minePlaceRow(1, ROW_COUNT-2);
    std::uniform_int_distribution<> minePlaceCol(1, COL_COUNT-2);
    int numMines = MINE_COUNT;
    while(numMines) {
        unsigned long row = static_cast<unsigned long>(minePlaceRow(mersenne));
        unsigned long col = static_cast<unsigned long>(minePlaceCol(mersenne));
        if(this->gameBoard[row*COL_COUNT + col].mineCheck()) {
            std::cout << "Will not add mine at " << row << ", " << col << "\n";
            continue;
        }
        this->gameBoard[row*COL_COUNT + col].setMine();
        std::cout << "Added mine at " << row << ", " << col << "\n";
        numMines--;
    }
    for(unsigned long i = 1; i < ROW_COUNT-1; i++) {
        for(unsigned long j = 1; j < COL_COUNT-1; j++) {
            if(this->gameBoard[i*COL_COUNT + j].mineCheck())
            {
                this->gameBoard[(i-1)*COL_COUNT + j-1].neighborCount++;
                this->gameBoard[(i-1)*COL_COUNT + j].neighborCount++;
                this->gameBoard[(i-1)*COL_COUNT + j+1].neighborCount++;
                this->gameBoard[i*COL_COUNT + j-1].neighborCount++;
                this->gameBoard[i*COL_COUNT + j+1].neighborCount++;
                this->gameBoard[(i+1)*COL_COUNT + j-1].neighborCount++;
                this->gameBoard[(i+1)*COL_COUNT + j].neighborCount++;
                this->gameBoard[(i+1)*COL_COUNT + j+1].neighborCount++;
            }
        }
    }
}

void Board::debug_show() {
    for(unsigned long i = 1; i < ROW_COUNT-1; i++) {
        for(unsigned long j = 1; j < COL_COUNT-1; j++) {
            char sym;
            if(this->gameBoard[i*COL_COUNT + j].mineCheck())
                sym = 'X';
            else {
                sym = 'O';
            }
            std::cout << sym << " ";
        }
        std::cout << "\n";
    }
}

void Board::debug_show_counts() {
    for(unsigned long i = 1; i < ROW_COUNT-1; i++) {
        for(unsigned long j = 1; j < COL_COUNT-1; j++) {
            std::cout << this->gameBoard[i*COL_COUNT + j].neighborCount << " ";
        }
        std::cout << "\n";
    }
}
