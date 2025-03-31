#pragma once
#include <SFML/Graphics.hpp>

class Command {
public:
    virtual ~Command() = default;
    virtual void execute(sf::RenderWindow& window) = 0;
};