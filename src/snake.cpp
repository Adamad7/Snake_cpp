#include "../include/snake.hpp"

Snake::Snake(unsigned int width, unsigned int height, unsigned int partSize, sf::Color color, Direction direction, int speed)
    : sizeX(width / partSize), sizeY(height / partSize), partSize(partSize), color(color), direction(direction), lastDirection(direction), speed(speed)
{
    parts.push_back(SnakePart(partSize, 2, 0, sf::Color(255, 255, 0)));
    parts.push_back(SnakePart(partSize, 1, 0, sf::Color(255, 0, 255)));
    parts.push_back(SnakePart(partSize, 0, 0, sf::Color(0, 255, 255)));
    frameCounter = 0;
    isAlive = true;
};

void Snake::move()
{
    if (frameCounter == 10 - speed)
    {
        frameCounter = 0;
        lastDirection = direction;
        grow();
        parts.pop_back();
        }
    else
    {
        frameCounter++;
    }
}

void Snake::grow()
{
    parts.insert(parts.begin(), SnakePart(partSize, calculatePosX(), calculatePosY(), color));
    checkIfAlive();
}
void Snake::changeDirection(Direction direction)
{
    if (lastDirection == UP && direction == DOWN || lastDirection == DOWN && direction == UP || lastDirection == LEFT && direction == RIGHT || lastDirection == RIGHT && direction == LEFT)
    {
        return;
    }
    this->direction = direction;
}

void Snake::speedUp()
{
    changeSpeed(speed + 1);
}

void Snake::speedDown()
{
    changeSpeed(speed - 1);
}

void Snake::changeSpeed(int speed)
{
    frameCounter = 0;
    this->speed = std::max(0, std::min(10, speed));
}

sf::Vector2u Snake::getHeadPosition()
{
    return sf::Vector2u(parts[0].posX, parts[0].posY);
}

void Snake::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (int i = 0; i < parts.size(); i++)
    {
        target.draw(parts[i], states);
    }
};

unsigned int Snake::calculatePosX()
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

unsigned int Snake::calculatePosY()
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

void Snake::checkIfAlive()
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

std::vector<sf::Vector2u> Snake::getSnakePositions()
{
    std::vector<sf::Vector2u> snakePositions;
    for (auto &part : parts)
    {
        snakePositions.push_back(sf::Vector2u(part.posX, part.posY));
    }
    return snakePositions;
}
