#include "../headers/board.h"

int main() {
    std::unique_ptr<Board> board = std::make_unique<Board>();
    board->setup();
    board->debug_show();
    board->debug_show_counts();
    return 0;
}
