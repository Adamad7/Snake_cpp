#include "../include/food.hpp"

Food::Food(unsigned int width, unsigned int height, unsigned int size, sf::Color color, int bonus)
{
    this->width = width;
    this->height = height;
    this->size = size;
    this->color = color;
    this->bonus = bonus;
    rectangle = sf::RectangleShape(sf::Vector2f(size, size));
    rectangle.setFillColor(color);
}

void Food::spawnNewFood(std::vector<sf::Vector2u> snakePositions)
{
    srand(time(NULL));
    bool isOnSnake = true;
    while (isOnSnake)
    {
        isOnSnake = false;
        this->foodPosition.x = rand() % (width / size);
        this->foodPosition.y = rand() % (height / size);
        for (auto &snakePart : snakePositions)
        {
            if (snakePart.x == this->foodPosition.x && snakePart.y == this->foodPosition.y)
            {
                isOnSnake = true;
                break;
            }
        }
    }
    rectangle.setPosition(sf::Vector2f(this->foodPosition.x * size, this->foodPosition.y * size));
}

void Food::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(rectangle);
}

sf::Vector2u Food::getFoodPosition()
{
    return this->foodPosition;
}