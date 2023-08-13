#include "SFML/Graphics.hpp"
#include <vector>
#include <iostream>
#include <algorithm>
#include "../include/snake.hpp"
#include "../include/scoreboard.hpp"
#include "../include/food.hpp"

#define PART_SIZE 10
#define WIDTH 500
#define HEIGHT 500

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT + 50), "Snake CPP");
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
    std::cout << "Testing std output" << std::endl;
    sf::RectangleShape background = sf::RectangleShape(sf::Vector2f(WIDTH, HEIGHT));
    background.setFillColor(sf::Color(10, 0, 0));
    background.setPosition(sf::Vector2f(0, 0));

    Snake snake = Snake(WIDTH, HEIGHT, PART_SIZE, sf::Color(255, 255, 255));

    Scoreboard scoreboard(sf::Vector2f(WIDTH, 50), sf::Vector2f(0, HEIGHT), sf::Color(10, 10, 100), sf::Color(255, 255, 255), font, 20, 0);
    Food food = Food(WIDTH, HEIGHT, PART_SIZE, sf::Color(255, 0, 0), 10);
    food.spawnNewFood(snake.getSnakePositions());

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
            scoreboard.updateTime();
        }

        if (snake.getHeadPosition().x == food.getFoodPosition().x && snake.getHeadPosition().y == food.getFoodPosition().y)
        {
            snake.grow();
            food.spawnNewFood(snake.getSnakePositions());
            scoreboard.increaseScore();
        }

        // std::cout << "Snake pos X: " << snake.getHeadPosition().x << " Snake pos Y: " << snake.getHeadPosition().y << std::endl;
        // std::cout << "Food pos X: " << food.getFoodPosition().x << " Food pos Y: " << food.getFoodPosition().y << std::endl;

        window.clear();
        window.draw(background);

        window.draw(snake);
        window.draw(food);
        // window.draw(fpsCounter);
        window.draw(scoreboard);

        window.display();
    }

    return 0;
}