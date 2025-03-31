#pragma once
#include "State.hpp"

class GameState : public State {
public:
    GameState();

    void handleInput(sf::RenderWindow& window) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;

private:
    sf::RectangleShape player;
    float velocityY;
    bool isJumping;
};