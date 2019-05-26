#include "../headers/board.h"
#include "../headers/gfxhandler.h"

int main() {
    std::unique_ptr<Board> board = std::make_unique<Board>();
    std::unique_ptr<GfxHandler> gfx = std::make_unique<GfxHandler>();
    board->setup();
    board->debug_show();
    //board->debug_show_counts();
    //board->debug_play();
    return 0;
}
