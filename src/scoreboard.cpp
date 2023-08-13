#include "../include/scoreboard.hpp"

Scoreboard::Scoreboard(sf::Vector2f size,
                       sf::Vector2f position,
                       sf::Color backgroundColor,
                       sf::Color fontColor,
                       sf::Font &font,
                       unsigned int fontSize,
                       unsigned int initialScore = 0)
{
    this->size = size;
    this->position = position;
    this->backgroundColor = backgroundColor;
    this->textColor = fontColor;
    this->font = font;
    this->score = initialScore;
    this->fontSize = fontSize;

    clock.restart();

    background = sf::RectangleShape(size);
    background.setFillColor(backgroundColor);
    background.setPosition(position);

    scoreText.setFont(font);
    scoreText.setCharacterSize(fontSize);
    scoreText.setFillColor(textColor);
    updateScoreText();
    // scoreText.setPosition(sf::Vector2f(this->position.x, (this->position.y + this->size.y / 2) - scoreText.getLocalBounds().height / 2));
    scoreText.setPosition(sf::Vector2f(this->position.x + 20, (this->position.y + this->size.y / 2) - scoreText.getLocalBounds().height * 0.75));

    timeText.setFont(font);
    timeText.setCharacterSize(fontSize);
    timeText.setFillColor(textColor);
    updateTime();
    timeText.setPosition(sf::Vector2f((this->position.x + this->size.x) - timeText.getLocalBounds().width - 20, (this->position.y + this->size.y / 2) - timeText.getLocalBounds().height * 0.75));
}

void Scoreboard::updateTime()
{
    timeText.setString("Time: " + getTimeString(clock.getElapsedTime()));
}

sf::String Scoreboard::getTimeString(sf::Time time)
{
    unsigned int minutes = static_cast<unsigned int>(time.asSeconds()) / 60;
    unsigned int seconds = static_cast<unsigned int>(time.asSeconds()) % 60;
    return (minutes < 10 ? " " : "") + std::to_string(minutes) + (seconds < 10 ? ":0" : ":") + std::to_string(seconds);
}

void Scoreboard::increaseScore()
{
    this->score++;
    updateScoreText();
}
void Scoreboard::decreaseScore()
{
    this->score--;
    updateScoreText();
}
void Scoreboard::resetScore()
{
    this->score = 0;
    updateScoreText();
}
unsigned int Scoreboard::getScore()
{
    return this->score;
}
sf::Time Scoreboard::getTime()
{
    return this->clock.getElapsedTime();
}

void Scoreboard::draw(sf::RenderTarget &target, sf::RenderStates states) const
{

    target.draw(background, states);

    target.draw(scoreText, states);

    target.draw(timeText, states);
}

void Scoreboard::updateScoreText()
{
    scoreText.setString("Score: " + std::to_string(score));
}
