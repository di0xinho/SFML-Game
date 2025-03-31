#pragma once
#include <SFML/Graphics.hpp>

class State {
public:
    virtual ~State() = default;

    virtual void handleInput(sf::RenderWindow& window) = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
};