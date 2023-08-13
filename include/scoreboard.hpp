#include <SFML/Graphics.hpp>

class Scoreboard : public sf::Drawable
{
public:
    Scoreboard(sf::Vector2f size,
               sf::Vector2f position,
               sf::Color backgroundColor,
               sf::Color fontColor,
               sf::Font &font,
               unsigned int fontSize,
               unsigned int initialScore);
    void increaseScore();
    void decreaseScore();
    void resetScore();
    unsigned int getScore();
    sf::Time getTime();
    void updateTime();

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    unsigned int score;
    sf::Vector2f size;
    sf::Vector2f position;
    sf::Color backgroundColor;
    sf::Color textColor;
    sf::Font font;
    unsigned int fontSize;
    sf::RectangleShape background;
    sf::Text scoreText;
    sf::Text timeText;
    void updateScoreText();
    sf::Clock clock;
    sf::String getTimeString(sf::Time time);
};