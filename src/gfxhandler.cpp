#include "../headers/gfxhandler.h"

GfxHandler::GfxHandler()
{
    this->window.create(sf::VideoMode(800, 600), "main_sweeper()");
    sf::CircleShape circle(50.0f);
    circle.setFillColor(sf::Color::Blue);
    while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear();
            window.draw(circle);
            window.display();
        }
}
