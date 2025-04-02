#pragma once
#include "State.hpp"
#include "SoundManager.hpp"

class StateMachine;

class PauseState : public State {
public:
    PauseState(StateMachine& machine, SoundManager* soundManager);

    void handleInput(sf::RenderWindow& window) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;

private:
    StateMachine& stateMachine;
    SoundManager* soundManager;
    sf::Font font;
    sf::Text pauseText;
    sf::Text instructions;
};