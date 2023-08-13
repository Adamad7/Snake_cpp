#include "../include/snakePart.hpp"

SnakePart::SnakePart(unsigned int size, unsigned int posX, unsigned int posY, sf::Color color)
    : size(size), posX(posX), posY(posY), color(color)
{
    rectangle = sf::RectangleShape(sf::Vector2f(size, size));
    rectangle.setFillColor(color);
    rectangle.setPosition(sf::Vector2f(posX * size, posY * size));
};

void SnakePart::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(rectangle, states);
};
