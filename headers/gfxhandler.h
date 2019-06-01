#ifndef GFXHANDLER_H
#define GFXHANDLER_H

#include "board.h"
#include <SFML/Graphics.hpp>

class GfxHandler
{
private:
    sf::RenderWindow window;
public:
    sf::Color LightGreen = sf::Color(50, 205, 50);
    sf::Color DarkGreen = sf::Color(34, 139, 34);
    GfxHandler();
    void showWindow(Board&);
    void drawGameBoard(Board&);
    void handleClick(sf::Vector2i clickPos, Board& board);
    bool inBounds(int x, int y);
};

#endif // GFXHANDLER_H
