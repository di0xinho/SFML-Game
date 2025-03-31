#pragma once
#include "State.hpp"

class StateMachine;

class MenuState : public State {
public:
    MenuState(StateMachine& machine);

    void handleInput(sf::RenderWindow& window) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;

private:
    StateMachine& stateMachine;
    sf::Font font;
    sf::Text title;
    sf::Text instructions;
};