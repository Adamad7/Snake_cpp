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

class SnakePart : public sf::Drawable
{
public:
    SnakePart(unsigned int size, unsigned int posX, unsigned int posY, sf::Color color, Direction direction = RIGHT)
        : size(size), posX(posX), posY(posY), color(color), direction(direction){};

    void move(unsigned int speed)
    {
        switch (direction)
        {
        case UP:
            posY -= speed;
            break;
        case DOWN:
            posY += speed;
            break;
        case LEFT:
            posX -= speed;
            break;
        case RIGHT:
            posX += speed;
            break;
        }
    }

    unsigned int posX;
    unsigned int posY;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        sf::RectangleShape snakePart = sf::RectangleShape(sf::Vector2f(size, size));
        snakePart.setFillColor(color);
        snakePart.setPosition(sf::Vector2f(posX, posY));
        target.draw(snakePart, states);
    };

private:
    unsigned int size;

    sf::Color color;
    Direction direction;
};

class Snake : public sf::Drawable
{
public:
    Snake(unsigned int areaWidth, unsigned int areaHeight, unsigned int partSize, sf::Color color, Direction direction = RIGHT)
        : areaWidth(areaWidth), areaHeight(areaHeight), partSize(partSize), color(color), direction(direction), lastDirection(direction)
    {
        parts.push_back(SnakePart(25, 25, 0, sf::Color(255, 255, 0)));
        parts.push_back(SnakePart(25, 25, 0, sf::Color(255, 0, 255)));
        parts.push_back(SnakePart(25, 0, 0, sf::Color(0, 255, 255)));
        frameCounter = 0;
    };
    void move()
    {
        if (frameCounter == 20)
        {
            frameCounter = 0;
            parts.insert(parts.begin(), SnakePart(parts[0].posX, parts[0].posY, partSize, color, direction));
            parts.pop_back();
        }
        else if (frameCounter % 3 == 0)
        {
            frameCounter++;
            parts[0].move(3);
            parts[parts.size() - 1].move(3);
        }
        else
        {
            frameCounter++;
        }
    }
    void grow()
    {
        switch (direction)
        {
        case UP:
            parts.insert(parts.begin(), SnakePart(parts[0].posX, parts[0].posY - partSize, partSize, color, direction));
            break;
        case DOWN:
            parts.insert(parts.begin(), SnakePart(parts[0].posX, parts[0].posY + partSize, partSize, color, direction));
            break;
        case LEFT:
            parts.insert(parts.begin(), SnakePart(parts[0].posX - partSize, parts[0].posY, partSize, color, direction));
            break;
        case RIGHT:
            parts.insert(parts.begin(), SnakePart(parts[0].posX + partSize, parts[0].posY, partSize, color, direction));
            break;
        }
    }
    void changeDirection(Direction direction)
    {
        if (lastDirection == UP && direction == DOWN || lastDirection == DOWN && direction == UP || lastDirection == LEFT && direction == RIGHT || lastDirection == RIGHT && direction == LEFT)
        {
            return;
        }
        this->direction = direction;
    }

    unsigned int length() { return parts.size(); };
    Direction getDirection() { return direction; };
    unsigned int frameCounter;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {

        for (int i = 0; i < parts.size(); i++)
        {
            parts[i].draw(target, states);
        }
    };

    unsigned int partSize;
    unsigned int areaWidth;
    unsigned int areaHeight;
    unsigned int speed = 7;

    std::vector<SnakePart> parts;
    Direction direction = RIGHT;
    Direction lastDirection = RIGHT;
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

    SnakePart part = SnakePart(25, 50, 200, sf::Color(0, 0, 255));

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
                    snake.grow();
                    break;
                }

                break;
            case sf::Event::Closed:
                window.close();
                break;
            }
        }

        snake.move();
        part.move(3);
        window.clear();
        window.draw(background);

        window.draw(part);
        window.draw(snake);
        window.draw(fpsCounter);

        window.display();
    }

    return 0;
}