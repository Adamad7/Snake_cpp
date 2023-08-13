#include <SFML/Graphics.hpp>
class SnakePart : public sf::Drawable
{
public:
    SnakePart(unsigned int size, unsigned int posX, unsigned int posY, sf::Color color);

    unsigned int posX;
    unsigned int posY;

private:
    unsigned int size;

    sf::RectangleShape rectangle;
    sf::Color color;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};