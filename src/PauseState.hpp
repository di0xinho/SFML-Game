#pragma once
#include "State.hpp"

// Deklaracja forward dla klasy StateMachine
class StateMachine;

class PauseState : public State {
public:
    PauseState(StateMachine& machine);

    void handleInput(sf::RenderWindow& window) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;

private:
    StateMachine& stateMachine;
    sf::Font font;
    sf::Text pauseText;
    sf::Text instructions;
};