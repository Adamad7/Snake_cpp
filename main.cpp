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

class Snake : public sf::Drawable
{
public:
    Snake(unsigned int areaWidth, unsigned int areaHeight, unsigned int partSize, sf::Color color)
        : areaWidth(areaWidth), areaHeight(areaHeight), partSize(partSize), color(color)
    {
        positions.push_back(2);
        positions.push_back(1);
        positions.push_back(0);
    };
    //~Snake();
    void move()
    {
        grow();
        positions.pop_back();
    }
    void grow()
    {
        switch (direction)
        {
        case UP:
            positions.insert(positions.begin(), positions[0] - (areaWidth / partSize));
            break;
        case DOWN:
            positions.insert(positions.begin(), positions[0] + (areaWidth / partSize));
            break;
        case LEFT:
            positions.insert(positions.begin(), positions[0] - 1);
            break;
        case RIGHT:
            positions.insert(positions.begin(), positions[0] + 1);
            break;
        }
    }
    void changeDirection(Direction direction)
    {
        this->direction = direction;
    }

    unsigned int length() { return positions.size(); };
    Direction getDirection() { return direction; };

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        for (int i = 0; i < positions.size(); i++)
        {
            sf::RectangleShape snakePart = sf::RectangleShape(sf::Vector2f(partSize, partSize));
            snakePart.setFillColor(color);
            snakePart.setPosition(sf::Vector2f(positions[i] % (areaWidth / partSize) * partSize, positions[i] / (areaHeight / partSize) * partSize));
            target.draw(snakePart, states);
        }
    };
    unsigned int partSize;
    unsigned int areaWidth;
    unsigned int areaHeight;
    std::vector<int> positions;
    Direction direction = RIGHT;
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
    background.setFillColor(sf::Color(100, 0, 0));
    background.setPosition(sf::Vector2f(0, 0));

    Direction lastSnakeDirection = RIGHT;

    Snake snake = Snake(500, 500, 25, sf::Color(255, 255, 255));

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
                        snake.changeDirection(UP);
                    }
                    break;
                case sf::Keyboard::Down:
                    if (lastSnakeDirection != UP)
                    {
                        snake.changeDirection(DOWN);
                    }
                    break;
                case sf::Keyboard::Left:
                    if (lastSnakeDirection != RIGHT)
                    {
                        snake.changeDirection(LEFT);
                    }
                    break;
                case sf::Keyboard::Right:
                    if (lastSnakeDirection != LEFT)
                    {
                        snake.changeDirection(RIGHT);
                    }
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

        if (frameCounter > 3)
        {
            lastSnakeDirection = snake.getDirection();
            frameCounter = 0;
            snake.move();
        }
        else
        {
            frameCounter++;
        }

        window.clear();

        window.draw(background);
        window.draw(snake);
        window.draw(fpsCounter);
        window.display();
    }

    return 0;
}