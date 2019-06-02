#include "../headers/board.h"
#include "../headers/gfxhandler.h"

int main() {
    std::unique_ptr<Board> board = std::make_unique<Board>();
    board->setup();
    std::unique_ptr<GfxHandler> gfx = std::make_unique<GfxHandler>();
    gfx->showWindow(*board);
    return 0;
}
