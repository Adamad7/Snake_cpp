#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

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
    background.setFillColor(sf::Color(100, 100, 100));
    background.setPosition(sf::Vector2f(0, 0));

    std::vector<int> snakePositions;
    snakePositions.push_back(50);
    snakePositions.push_back(51);
    snakePositions.push_back(52);
    snakePositions.push_back(53);
    snakePositions.push_back(54);
    unsigned int snakeLength = 5;
    Direction snakeDirection = DOWN;
    Direction lastSnakeDirection = DOWN;

    sf::Clock clock;
    float lastTime = 0;
    unsigned int frameCounter = 0;
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
                    if (lastSnakeDirection != DOWN)
                    {
                        snakeDirection = UP;
                    }
                    break;
                case sf::Keyboard::Down:
                    if (lastSnakeDirection != UP)
                    {
                        snakeDirection = DOWN;
                    }
                    break;
                case sf::Keyboard::Left:
                    if (lastSnakeDirection != RIGHT)
                    {
                        snakeDirection = LEFT;
                    }
                    break;
                case sf::Keyboard::Right:
                    if (lastSnakeDirection != LEFT)
                    {
                        snakeDirection = RIGHT;
                    }
                    break;
                }
                break;
            case sf::Event::Closed:
                window.close();
                break;
            }
        }

        if (frameCounter > 3)
        {
            lastSnakeDirection = snakeDirection;
            frameCounter = 0;
            switch (snakeDirection)
            {
            case UP:
                snakePositions.insert(snakePositions.begin(), snakePositions[0] - 20);
                break;
            case DOWN:
                snakePositions.insert(snakePositions.begin(), snakePositions[0] + 20);
                break;
            case LEFT:
                snakePositions.insert(snakePositions.begin(), snakePositions[0] - 1);
                break;
            case RIGHT:
                snakePositions.insert(snakePositions.begin(), snakePositions[0] + 1);
                break;
            }
            snakePositions.pop_back();
        }
        else
        {
            frameCounter++;
        }

        window.clear();

        window.draw(background);
        for (int i = 0; i < snakeLength; i++)
        {
            sf::RectangleShape snakePart = sf::RectangleShape(sf::Vector2f(25, 25));
            snakePart.setFillColor(sf::Color(255, 255, 255));
            snakePart.setPosition(sf::Vector2f(snakePositions[i] % 20 * 25, snakePositions[i] / 20 * 25));
            window.draw(snakePart);
        }
        window.draw(fpsCounter);
        window.display();
    }

    return 0;
}