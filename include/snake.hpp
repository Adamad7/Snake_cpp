#include <SFML/Graphics.hpp>
#include "snakePart.hpp"

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
    Snake(unsigned int width, unsigned int height, unsigned int partSize, sf::Color color, Direction direction = RIGHT, int speed = 5);

    void move();

    void grow();
    void changeDirection(Direction direction);

    void speedUp();

    void speedDown();

    void changeSpeed(int speed);

    sf::Vector2u getHeadPosition();
    std::vector<sf::Vector2u> getSnakePositions();

    bool isAlive;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    unsigned int calculatePosX();

    unsigned int calculatePosY();

    void checkIfAlive();

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