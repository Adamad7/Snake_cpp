#include <SFML/Graphics.hpp>
#include "snake.hpp"
#include "scoreboard.hpp"
#include "food.hpp"

class Gameboard : public sf::Drawable
{
public:
    Gameboard(unsigned int width,
              unsigned int height,
              unsigned int partSize,
              unsigned int scoreboardHeight,
              sf::Color snakeColor,
              sf::Color backgroundColor,
              sf::Color scoreboardColor,
              sf::Color scoreboardTextColor,
              sf::Color foodColor,
              sf::Font &font,
              int scoreboardTextSize);
    void update();
    void move(sf::Keyboard::Key key);

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    unsigned int width;
    unsigned int height;
    unsigned int partSize;
    sf::RectangleShape background;
    Snake snake;
    Scoreboard scoreboard;
    Food food;
    sf::Font font;
};