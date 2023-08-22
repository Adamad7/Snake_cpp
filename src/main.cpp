#include "SFML/Graphics.hpp"
#include <vector>
#include <iostream>
#include "../include/gameboard.hpp"
#include "../include/fontData.hpp"

#define PART_SIZE 10
#define WIDTH 500
#define HEIGHT 500
#define SCOREBOARD_HEIGHT 50

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT + SCOREBOARD_HEIGHT), "Snake CPP");
    // window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    sf::Font font;
    if (font.loadFromMemory(arial_ttf, arial_ttf_len))
    {
        std::cout << "Font loaded" << std::endl;
    }
    else
    {
        std::cout << "Font not loaded" << std::endl;
    }
    Gameboard gameboard = Gameboard(WIDTH, HEIGHT,
                                    PART_SIZE,
                                    SCOREBOARD_HEIGHT,
                                    sf::Color::Green,
                                    sf::Color::Black,
                                    sf::Color::White,
                                    sf::Color::Black,
                                    sf::Color::Red,
                                    font,
                                    20);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::KeyPressed:

                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
                else
                {
                    gameboard.move(event.key.code);
                }
                break;
            case sf::Event::Closed:
                window.close();
                break;
            }
        }

        gameboard.update();

        window.clear();

        window.draw(gameboard);

        window.display();
    }

    return 0;
}