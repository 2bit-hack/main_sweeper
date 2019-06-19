#include "../headers/board.h"
#include "../headers/gfxhandler.h"
#include "../headers/audiohandler.h"

int main() {
    std::unique_ptr<Board> board = std::make_unique<Board>();
    std::unique_ptr<GfxHandler> gfx = std::make_unique<GfxHandler>();
    gfx->showWindow(*board);
    return 0;
}
