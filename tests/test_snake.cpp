#define CATCH_CONFIG_MAIN

#include "C:\Programowanie\Snake_cpp\catch2\catch.hpp"
#include "./../include/snake.h"
#include <iostream>

TEST_CASE("Snake is created correctly", "[snake]")
{
    std::cout << "Snake is created correctly" << std::endl;
    char a;
    std::cin >> a;
    Snake snake(100, 100, 10, sf::Color::Red);

    REQUIRE(snake.isAlive == true);
    REQUIRE(snake.getHeadPosition().x == 2);
    REQUIRE(snake.getHeadPosition().y == 0);
}
