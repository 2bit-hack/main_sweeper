#include "../headers/gfxhandler.h"

GfxHandler::GfxHandler()
{
    this->window.create(sf::VideoMode(RESOLUTION*(ROW_COUNT-2), RESOLUTION*(COL_COUNT-2)),
                        "main_sweeper()");
    font.loadFromFile("assets/OpenSans-Light.ttf");
    neighborCount.setFont(font);
    neighborCount.setFillColor(DarkGreen);
    neighborCount.setOrigin(-10.0f, -2.0f);
    flagTexture.loadFromFile("assets/flag.png");
    flagSprite.setTexture(flagTexture);
    flagSprite.setScale(0.20f, 0.15f);
    flagSprite.setOrigin(-20.0f, -10.0f);
    mineTexture.loadFromFile("assets/mine-png-8.png");
    mineSprite.setTexture(mineTexture);
    mineSprite.setScale(0.025f, 0.025f);
    mineSprite.setOrigin(10.0f, 5.0f);
}

void GfxHandler::showWindow(Board& board) {
    while(this->window.isOpen() && board.gState == Board::GameState::IN_PROGRESS)
        {
            sf::Event event;
            while (this->window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    this->window.close();
            }
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                handleLeftClick(sf::Mouse::getPosition(this->window), board);
            if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
                handleRightClick(sf::Mouse::getPosition(this->window), board);
            this->window.clear();
            drawGameBoard(board);
            this->window.display();
            board.checkCompletion();
        }
    showAll(board);
//    std::string message = (board.gState == Board::GameState::WON)?"You won!\n":"You lost!\n";
//    std::cout << message;
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
                this->window.draw(tile);
                this->window.draw(neighborCount);
            }
        }
    }
}

bool GfxHandler::inBounds(int x, int y) {
    if(x < 1 || x >= ROW_COUNT-1 || y < 1 || y >= COL_COUNT-1)
        return false;
    return true;
}

void GfxHandler::handleLeftClick(sf::Vector2i clickPos, Board& board) {
    if(inBounds((clickPos.y/RESOLUTION)+1, (clickPos.x/RESOLUTION)+1)) {
        board.reveal((clickPos.y/RESOLUTION)+1, (clickPos.x/RESOLUTION)+1);
    }
}

void GfxHandler::handleRightClick(sf::Vector2i clickPos, Board &board) {
    if(inBounds((clickPos.y/RESOLUTION)+1, (clickPos.x/RESOLUTION)+1))
        board.toggleFlag((clickPos.y/RESOLUTION)+1, (clickPos.x/RESOLUTION)+1);
}

void GfxHandler::showAll(Board &board) {
    for(unsigned long i = 1; i < ROW_COUNT-1; i++) {
        for(unsigned long j = 1; j < COL_COUNT-1; j++) {
            board.gameBoard[(i*COL_COUNT)+j].setState(Cell::State::REVEALED);
        }
    }
}
