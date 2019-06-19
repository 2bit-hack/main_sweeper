#include "../headers/gfxhandler.h"

GfxHandler::GfxHandler()
{
    // loading icon slows down render noticeably?
    this->window.create(sf::VideoMode(RESOLUTION*(ROW_COUNT-2), RESOLUTION*(COL_COUNT-2)),
                        "main_sweeper()");
    font.loadFromFile("assets/OpenSans-Light.ttf");
    aud = std::make_unique<AudioHandler>();
    neighborCount.setFont(font);
    neighborCount.setFillColor(sf::Color::Red);
    neighborCount.setOrigin(-10.0f, -2.0f);
    //TODO: set a better icon
    //icon.loadFromFile("assets/mine-png-8.png");
    flagTexture.loadFromFile("assets/flag.png");
    flagSprite.setTexture(flagTexture);
    flagSprite.setScale(0.20f, 0.15f);
    flagSprite.setOrigin(-20.0f, -10.0f);
    mineTexture.loadFromFile("assets/mine-png-8.png");
    mineSprite.setTexture(mineTexture);
    mineSprite.setScale(0.025f, 0.025f);
    mineSprite.setOrigin(10.0f, 5.0f);
    //this->window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

void GfxHandler::showWindow(Board& board) {
    while(this->window.isOpen() && board.gState == Board::GameState::IN_PROGRESS)
    {
        sf::Event event;
        while (this->window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                this->window.close();
            }

            if(event.type == sf::Event::MouseButtonPressed) {
                if(event.mouseButton.button == sf::Mouse::Left) {
                    if(board.isFirstClick) {
                        board.firstClickPos.first = getX(sf::Mouse::getPosition(this->window));
                        board.firstClickPos.second = getY(sf::Mouse::getPosition(this->window));
                        board.setup();
                        board.isFirstClick = false;
                    }
                    handleLeftClick(sf::Mouse::getPosition(this->window), board);
                    aud->playClick();
                }
                if(event.mouseButton.button == sf::Mouse::Right) {
                    handleRightClick(sf::Mouse::getPosition(this->window), board);
                    aud->playClick();
                }
            }
        }
        this->window.clear();
        drawGameBoard(board);
        this->window.display();
        board.checkCompletion();
    }
    showAll(board);
    while(this->window.isOpen()) {
        sf::Event event;
        while(this->window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                this->window.close();
        }
        this->window.clear();
        drawGameBoard(board);
        this->window.display();
    }
}

void GfxHandler::drawGameBoard(Board& board) {
    sf::Vector2f tileSize(RESOLUTION, RESOLUTION);
    sf::RectangleShape tile;
    tile.setSize(tileSize);
    for(int i = 1; i < ROW_COUNT-1; i++) {
        for(int j = 1; j < COL_COUNT-1; j++) {
            unsigned long _i = static_cast<unsigned long>(i);
            unsigned long _j = static_cast<unsigned long>(j);
            tile.setPosition((_j-1)*RESOLUTION, (_i-1)*RESOLUTION);
            if((i+j) % 2 == 0)
                tile.setFillColor(LightGreen);
            else
                tile.setFillColor(DarkGreen);
            if(board.gameBoard[(_i*COL_COUNT)+_j].getState() == Cell::State::UNREVEALED) {
                this->window.draw(tile);
            }
            else if(board.gameBoard[(_i*COL_COUNT)+_j].getState() == Cell::State::FLAGGED) {
                this->flagSprite.setPosition((_j-1)*RESOLUTION, (_i-1)*RESOLUTION);
                this->window.draw(tile);
                this->window.draw(flagSprite);
            }
            else if(board.gameBoard[(_i*COL_COUNT)+_j].getState() == Cell::State::REVEALED
                    && board.gameBoard[(_i*COL_COUNT)+_j].mineCheck()) {
                this->mineSprite.setPosition((_j-1)*RESOLUTION, (_i-1)*RESOLUTION);
                tile.setFillColor(sf::Color::White);
                this->window.draw(tile);
                this->window.draw(mineSprite);
            }
            else if(board.gameBoard[(_i*COL_COUNT)+_j].getState() == Cell::State::REVEALED
                    && board.gameBoard[(_i*COL_COUNT)+_j].neighbors() == 0){
                tile.setFillColor(sf::Color::White);
                this->window.draw(tile);
            }
            else {
                tile.setFillColor(sf::Color::White);
                neighborCount.setString(std::to_string(board.gameBoard[(_i*COL_COUNT)+_j].neighbors()));
                neighborCount.setPosition((_j-1)*RESOLUTION, (_i-1)*RESOLUTION);
                if(board.gameBoard[(_i*COL_COUNT)+_j].neighbors() == 1)
                    neighborCount.setFillColor(sf::Color(115, 242, 51));
                if(board.gameBoard[(_i*COL_COUNT)+_j].neighbors() == 2)
                    neighborCount.setFillColor(sf::Color(59, 155, 10));
                if(board.gameBoard[(_i*COL_COUNT)+_j].neighbors() == 3)
                    neighborCount.setFillColor(sf::Color(246, 255, 0));
                if(board.gameBoard[(_i*COL_COUNT)+_j].neighbors() == 4)
                    neighborCount.setFillColor(sf::Color(249, 181, 24));
                if(board.gameBoard[(_i*COL_COUNT)+_j].neighbors() == 5)
                    neighborCount.setFillColor(sf::Color(249, 99, 24));
                if(board.gameBoard[(_i*COL_COUNT)+_j].neighbors() == 6)
                    neighborCount.setFillColor(sf::Color(246, 54, 25));
                if(board.gameBoard[(_i*COL_COUNT)+_j].neighbors() == 7)
                    neighborCount.setFillColor(sf::Color(171, 8, 8));
                if(board.gameBoard[(_i*COL_COUNT)+_j].neighbors() == 8)
                    neighborCount.setFillColor(sf::Color(0, 0, 0));
                this->window.draw(tile);
                this->window.draw(neighborCount);
            }
        }
    }
}

int GfxHandler::getX(sf::Vector2i pos) {
    return (pos.y/RESOLUTION)+1;
}

int GfxHandler::getY(sf::Vector2i pos) {
    return (pos.x/RESOLUTION)+1;
}

bool GfxHandler::inBounds(int x, int y) {
    if(x < 1 || x >= ROW_COUNT-1 || y < 1 || y >= COL_COUNT-1)
        return false;
    return true;
}

void GfxHandler::handleLeftClick(sf::Vector2i clickPos, Board& board) {
    if(clickPos.x < 0 || clickPos.y < 0)
        return;
    if(inBounds(getX(clickPos), getY(clickPos))) {
        bool mineClicked = board.reveal(getX(clickPos), getY(clickPos));
        if(mineClicked)
            aud->playMine();
    }
}

void GfxHandler::handleRightClick(sf::Vector2i clickPos, Board &board) {
    if(clickPos.x < 0 || clickPos.y < 0)
        return;
    if(inBounds(getX(clickPos), getY(clickPos)))
        board.toggleFlag(getX(clickPos), getY(clickPos));
}

void GfxHandler::showAll(Board &board) {
    for(unsigned long i = 1; i < ROW_COUNT-1; i++) {
        for(unsigned long j = 1; j < COL_COUNT-1; j++) {
            board.gameBoard[(i*COL_COUNT)+j].setState(Cell::State::REVEALED);
        }
    }
}
