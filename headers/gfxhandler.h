#ifndef GFXHANDLER_H
#define GFXHANDLER_H

#include "board.h"
#include "audiohandler.h"
#include <SFML/Graphics.hpp>

class GfxHandler
{
private:
    sf::RenderWindow window;
public:
    std::unique_ptr<AudioHandler> aud;
    sf::Color LightGreen = sf::Color(50, 205, 50);
    sf::Color DarkGreen = sf::Color(34, 139, 34);
    sf::Font font;
    sf::Text neighborCount;
    sf::Image icon;
    sf::Texture flagTexture;
    sf::Sprite flagSprite;
    sf::Texture mineTexture;
    sf::Sprite mineSprite;
    GfxHandler();
    void showWindow(Board& board);
    void drawGameBoard(Board& board);
    void showAll(Board& board);
    int getX(sf::Vector2i pos);
    int getY(sf::Vector2i pos);
    void handleLeftClick(sf::Vector2i clickPos, Board& board);
    void handleRightClick(sf::Vector2i clickPos, Board& board);
    bool inBounds(int x, int y);
};

#endif // GFXHANDLER_H
