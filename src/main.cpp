#include "SFML/Graphics.hpp"
#include <vector>
#include <iostream>
#include <algorithm>
#include "../include/snake.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 550), "Snake CPP");
    // window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    sf::Font font;
    if (font.loadFromFile("resources/fonts/arial.ttf"))
    {
        std::cout << "Font loaded" << std::endl;
    }
    else
    {
        std::cout << "Font not loaded" << std::endl;
    }
    sf::Text fpsCounter("FPS: 0", font, 20);
    fpsCounter.setPosition(sf::Vector2f(220, 510));

    sf::RectangleShape background = sf::RectangleShape(sf::Vector2f(500, 500));
    background.setFillColor(sf::Color(10, 0, 0));
    background.setPosition(sf::Vector2f(0, 0));

    Snake snake = Snake(500, 500, 25, sf::Color(255, 255, 255));

    sf::Clock clock;
    float lastTime = 0;

    while (window.isOpen())
    {
        float currentTime = clock.restart().asSeconds();
        float fps = 1.f / currentTime;
        lastTime = currentTime;
        fpsCounter.setString("FPS: " + std::to_string(fps));
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::KeyPressed:
                switch (event.key.code)
                {
                case sf::Keyboard::Up:
                    snake.changeDirection(UP);
                    break;
                case sf::Keyboard::Down:
                    snake.changeDirection(DOWN);
                    break;
                case sf::Keyboard::Left:
                    snake.changeDirection(LEFT);
                    break;
                case sf::Keyboard::Right:
                    snake.changeDirection(RIGHT);
                    break;
                case sf::Keyboard::A:
                    snake.speedDown();
                    break;
                case sf::Keyboard::S:
                    snake.grow();
                    break;
                case sf::Keyboard::D:
                    snake.speedUp();
                    break;
                }

                break;
            case sf::Event::Closed:
                window.close();
                break;
            }
        }

        if (snake.isAlive)
        {
            snake.move();
        }
        window.clear();
        window.draw(background);

        window.draw(snake);
        window.draw(fpsCounter);

        window.display();
    }

    return 0;
}