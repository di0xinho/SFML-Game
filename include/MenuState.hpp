#pragma once
#include "State.hpp"
#include "SoundManager.hpp"

class StateMachine;

class MenuState : public State {
public:
    MenuState(StateMachine& machine, SoundManager* soundManager);

    void handleInput(sf::RenderWindow& window) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;

private:
    StateMachine& stateMachine;
    SoundManager* soundManager; // Dodajemy SoundManager jako sk³adow¹
    sf::Font font;
    sf::Text title;
    sf::Text instructions;
};