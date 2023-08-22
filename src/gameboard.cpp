#include "../include/gameboard.hpp"

Gameboard::Gameboard(unsigned int width,
                     unsigned int height,
                     unsigned int partSize,
                     unsigned int scoreboardHeight,
                     sf::Color snakeColor,
                     sf::Color backgroundColor,
                     sf::Color scoreboardColor,
                     sf::Color scoreboardTextColor,
                     sf::Color foodColor,
                     sf::Font &font,
                     int scoreboardTextSize)
    : width(width),
      height(height),
      partSize(partSize),
      background(sf::Vector2f(width, height)),
      snake(width, height, partSize, snakeColor),
      scoreboard(sf::Vector2f(width, scoreboardHeight), sf::Vector2f(0, height), scoreboardColor, scoreboardTextColor, font, scoreboardTextSize, 0),
      food(width, height, partSize, foodColor, 1),
      font(font)
{
    background.setFillColor(backgroundColor);
    background.setPosition(sf::Vector2f(0, 0));
    food.spawnNewFood(snake.getSnakePositions());
}

void Gameboard::update()
{
    if (snake.isAlive)
    {
        snake.move();
        scoreboard.updateTime();
    }

    if (snake.getHeadPosition().x == food.getPosition().x && snake.getHeadPosition().y == food.getPosition().y)
    {
        snake.grow();
        food.spawnNewFood(snake.getSnakePositions());
        scoreboard.increaseScore();
    }
}

void Gameboard::move(sf::Keyboard::Key key)
{
    switch (key)
    {
    case sf::Keyboard::Up:
        snake.changeDirection(UP);
        break;
    case sf::Keyboard::Down:
        snake.changeDirection(DOWN);
        break;
    case sf::Keyboard::Left:
        snake.changeDirection(LEFT);
        break;
    case sf::Keyboard::Right:
        snake.changeDirection(RIGHT);
        break;
    case sf::Keyboard::A:
        snake.speedDown();
        break;
    case sf::Keyboard::S:
        snake.grow();
        break;
    case sf::Keyboard::D:
        snake.speedUp();
        break;
    }
}

void Gameboard::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(background);
    target.draw(snake);
    target.draw(food);
    target.draw(scoreboard);
}