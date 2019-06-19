#ifndef BOARD_H
#define BOARD_H

#include "cell.h"

// a grid of cells
// does all game related computations

class Board
{
private:
    enum class GameState {
      IN_PROGRESS, WON, LOST
    };
    std::vector<Cell> gameBoard;
    bool isFirstClick; std::pair<int, int> firstClickPos;
    int nonMinesRemaining; bool mineRevealed;
    GameState gState;
public:
    Board();
    ~Board();
    void setup();
    bool reveal(int i, int j);
    void toggleFlag(int i, int j);
    void floodFill(unsigned long i, unsigned long j);
    void checkCompletion();
    void triggerWinCondition();
    void triggerLoseCondition();
    friend class GfxHandler;
    // debug functions only
    void debug_set_revealed(int i, int j);
    void debug_show();
    void debug_show_counts();
    void debug_draw();
    [[noreturn]] void debug_play();
};

#endif // BOARD_H
