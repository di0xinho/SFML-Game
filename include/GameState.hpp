#pragma once
#include "State.hpp"
#include "InputHandler.hpp"

class StateMachine;

class GameState : public State {
public:
    GameState(StateMachine& machine);

    void handleInput(sf::RenderWindow& window) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;

private:
    StateMachine& stateMachine;
    InputHandler inputHandler;
    sf::RectangleShape player;
    float velocityY;
    bool isJumping;
};