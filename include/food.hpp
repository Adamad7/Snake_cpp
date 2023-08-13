#include <SFML/Graphics.hpp>
#include <vector>
class Food : public sf::Drawable
{
public:
    Food(unsigned int width, unsigned int height, unsigned int size, sf::Color color, int bonus);
    void spawnNewFood(std::vector<sf::Vector2u> snakePositions);
    sf::Vector2u getFoodPosition();

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    unsigned int width;
    unsigned int height;
    unsigned int size;
    sf::Color color;
    int bonus;
    sf::Vector2u foodPosition;
    sf::RectangleShape rectangle;
};
