#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <algorithm>

enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class SnakePart : public sf::Drawable
{
public:
    SnakePart(unsigned int size, unsigned int posX, unsigned int posY, sf::Color color)
        : size(size), posX(posX), posY(posY), color(color)
    {
        rectangle = sf::RectangleShape(sf::Vector2f(size, size));
        rectangle.setFillColor(color);
        rectangle.setPosition(sf::Vector2f(posX * size, posY * size));
    };

    unsigned int posX;
    unsigned int posY;

private:
    unsigned int size;

    sf::RectangleShape rectangle;
    sf::Color color;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        target.draw(rectangle, states);
    };
};

class Snake : public sf::Drawable
{
public:
    Snake(unsigned int width, unsigned int height, unsigned int partSize, sf::Color color, Direction direction = RIGHT, int speed = 5)
        : sizeX(width / partSize), sizeY(height / partSize), partSize(partSize), color(color), direction(direction), lastDirection(direction), speed(speed)
    {
        parts.push_back(SnakePart(25, 2, 0, sf::Color(255, 255, 0)));
        parts.push_back(SnakePart(25, 1, 0, sf::Color(255, 0, 255)));
        parts.push_back(SnakePart(25, 0, 0, sf::Color(0, 255, 255)));
        frameCounter = 0;
        isAlive = true;
    };

    void move()
    {
        if (frameCounter == 10 - speed)
        {
            frameCounter = 0;
            lastDirection = direction;
            grow();
            parts.pop_back();
            checkIfAlive();
        }
        else
        {
            frameCounter++;
        }
    }

    void grow()
    {
        parts.insert(parts.begin(), SnakePart(partSize, calculatePosX(), calculatePosY(), color));
    }
    void changeDirection(Direction direction)
    {
        if (lastDirection == UP && direction == DOWN || lastDirection == DOWN && direction == UP || lastDirection == LEFT && direction == RIGHT || lastDirection == RIGHT && direction == LEFT)
        {
            return;
        }
        this->direction = direction;
    }

    void speedUp()
    {
        changeSpeed(speed + 1);
    }

    void speedDown()
    {
        changeSpeed(speed - 1);
    }

    void changeSpeed(int speed)
    {
        frameCounter = 0;
        this->speed = std::max(0, std::min(10, speed));
    }

    sf::Vector2u getHeadPosition()
    {
        return sf::Vector2u(parts[0].posX, parts[0].posY);
    }

    bool isAlive;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        for (int i = 0; i < parts.size(); i++)
        {
            target.draw(parts[i], states);
        }
    };

    unsigned int calculatePosX()
    {
        switch (direction)
        {
        case LEFT:
            if (parts[0].posX == 0)
            {
                return sizeX - 1;
            }
            else
            {
                return parts[0].posX - 1;
            }
            break;
        case RIGHT:
            if (parts[0].posX == sizeX - 1)
            {
                return 0;
            }
            else
            {
                return parts[0].posX + 1;
            }
            break;
        default:
            return parts[0].posX;
        }
    }

    unsigned int calculatePosY()
    {
        switch (direction)
        {
        case UP:
            if (parts[0].posY == 0)
            {
                return sizeY - 1;
            }
            else
            {
                return parts[0].posY - 1;
            }
            break;
        case DOWN:
            if (parts[0].posY == sizeY - 1)
            {
                return 0;
            }
            else
            {
                return parts[0].posY + 1;
            }
            break;
        default:
            return parts[0].posY;
        }
    }

    void checkIfAlive()
    {
        for (int i = 1; i < parts.size(); i++)
        {
            if (parts[0].posX == parts[i].posX && parts[0].posY == parts[i].posY)
            {
                isAlive = false;
                return;
            }
        }
        isAlive = true;
    }

    unsigned int partSize;
    unsigned int sizeX;
    unsigned int sizeY;
    int speed;
    unsigned int frameCounter;

    std::vector<SnakePart> parts;
    Direction direction;
    Direction lastDirection;
    sf::Color color;
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