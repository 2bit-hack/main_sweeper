#include "../headers/board.h"

Board::Board()
{
    this->gState = Board::GameState::IN_PROGRESS;
    this->nonMinesRemaining = ((ROW_COUNT-2) * (COL_COUNT-2)) - MINE_COUNT;
    this->mineRevealed = false;
    this->gameBoard.reserve(ROW_COUNT * COL_COUNT);
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
    // setting up prng and randomly selecting rows and cols
    std::mt19937 mersenne(static_cast<std::mt19937::result_type>(std::time(nullptr)));
    std::uniform_int_distribution<> minePlaceRow(1, ROW_COUNT-2);
    std::uniform_int_distribution<> minePlaceCol(1, COL_COUNT-2);
    int numMines = MINE_COUNT;
    // placing the mines
    while(numMines) {
        unsigned long row = static_cast<unsigned long>(minePlaceRow(mersenne));
        unsigned long col = static_cast<unsigned long>(minePlaceCol(mersenne));
        if(this->gameBoard[row*COL_COUNT + col].mineCheck()) {
            continue;
        }
        this->gameBoard[row*COL_COUNT + col].setMine();
        numMines--;
    }
    // incrementing neighbor count of nearby cells
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

void Board::reveal(int i, int j) {
    unsigned long _i = static_cast<unsigned long>(i);
    unsigned long _j = static_cast<unsigned long>(j);
    if(this->gameBoard[(_i*COL_COUNT)+_j].getState() == Cell::State::FLAGGED)
        return;
    if(this->gameBoard[(_i*COL_COUNT)+_j].getState() == Cell::State::REVEALED)
        return;
    if(this->gameBoard[(_i*COL_COUNT)+_j].mineCheck()) {
        this->gameBoard[(_i*COL_COUNT)+_j].setState(Cell::State::REVEALED);
        this->mineRevealed = true;
    }
    else if(this->gameBoard[(_i*COL_COUNT)+_j].neighbors() != 0) {
        this->gameBoard[(_i*COL_COUNT)+_j].setState(Cell::State::REVEALED);
        this->nonMinesRemaining--;
    }
    else {
        floodFill(_i, _j);
    }
}

void Board::toggleFlag(int i, int j) {
    unsigned long _i = static_cast<unsigned long>(i);
    unsigned long _j = static_cast<unsigned long>(j);
    if(this->gameBoard[(_i*COL_COUNT)+_j].getState() == Cell::State::REVEALED)
        return;
    else if(this->gameBoard[(_i*COL_COUNT)+_j].getState() == Cell::State::FLAGGED)
        this->gameBoard[(_i*COL_COUNT)+_j].setState(Cell::State::UNREVEALED);
    else {
        this->gameBoard[(_i*COL_COUNT)+_j].setState(Cell::State::FLAGGED);
    }
}

void Board::checkCompletion() {
    if(this->nonMinesRemaining == 0)
        triggerWinCondition();
    else if(this->mineRevealed)
        triggerLoseCondition();
}

void Board::triggerWinCondition() {
    this->gState = Board::GameState::WON;
}

void Board::triggerLoseCondition() {
    this->gState = Board::GameState::LOST;
}

void Board::floodFill(unsigned long i, unsigned long j) {
    // if it's a mine
    if(this->gameBoard[(i*COL_COUNT)+j].mineCheck()) {
        return;
    }
    // if it's a flag
    if(this->gameBoard[(i*COL_COUNT)+j].getState() == Cell::State::FLAGGED) {
        return;
    }
    // if it's already revealed
    if(this->gameBoard[(i*COL_COUNT)+j].getState() == Cell::State::REVEALED) {
        return;
    }
    // if it's an invalid position
    if(i < 1 || i >= ROW_COUNT-1 || j < 1 || j >= ROW_COUNT-1) {
        return;
    }
    // if it has non-zero neighbors
    if(this->gameBoard[(i*COL_COUNT)+j].neighbors() != 0) {
        this->gameBoard[(i*COL_COUNT)+j].setState(Cell::State::REVEALED);
        return;
    }
    this->gameBoard[(i*COL_COUNT)+j].setState(Cell::State::REVEALED);
    this->nonMinesRemaining--;
    floodFill(i-1, j-1);
    floodFill(i-1, j);
    floodFill(i-1, j+1);
    floodFill(i, j-1);
    floodFill(i, j+1);
    floodFill(i+1, j-1);
    floodFill(i+1, j);
    floodFill(i+1, j+1);
}


// debug functions go here

void Board::debug_set_revealed(int i, int j) {
    unsigned long _i = static_cast<unsigned long>(i);
    unsigned long _j = static_cast<unsigned long>(j);
    if(this->gameBoard[(_i*COL_COUNT)+_j].neighbors() != 0)
        this->gameBoard[(_i*COL_COUNT)+_j].setState(Cell::State::REVEALED);
    else if(this->gameBoard[(_i*COL_COUNT)+_j].mineCheck()) {
        this->gameBoard[(_i*COL_COUNT)+_j].setState(Cell::State::REVEALED);
    }
    else {
        floodFill(_i, _j);
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

void Board::debug_draw() {
    for(unsigned long i = 1; i < ROW_COUNT-1; i++) {
        for(unsigned long j = 1; j < COL_COUNT-1; j++) {
            if(this->gameBoard[(i*COL_COUNT)+j].getState() == Cell::State::UNREVEALED) {
                std::cout << "X" << " ";
            }
            else if(this->gameBoard[(i*COL_COUNT)+j].getState() == Cell::State::REVEALED
                    && this->gameBoard[(i*COL_COUNT)+j].mineCheck()) {
                std::cout << "!" << " ";
            }
            else {
                std::cout << this->gameBoard[(i*COL_COUNT)+j].neighbors() << " ";
            }
        }
        std::cout << "\n";
    }
}

void Board::debug_play() {
    int i, j;
    debug_draw();
    while(true) {
        std::cout << "Enter valid i, j:\n";
        std::cin >> i;
        std::cin >> j;
        if(i < 1 || i >= ROW_COUNT-1 || j < 1 || j >= ROW_COUNT-1)
            std::cout << "Invalid i|j\n";
        else {
            std::cout << "----------------------\n";
            debug_set_revealed(i, j);
            debug_draw();
        }
    }
}
