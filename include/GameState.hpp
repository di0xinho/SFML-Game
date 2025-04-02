#pragma once
#include "State.hpp"
#include "InputHandler.hpp"
#include "ScoreManager.hpp"
#include "SoundManager.hpp"

class StateMachine;

class GameState : public State {
public:
    GameState(StateMachine& machine, SoundManager* soundManager);

    void handleInput(sf::RenderWindow& window) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;

private:
    StateMachine& stateMachine;
    InputHandler inputHandler;
    sf::RectangleShape player;
    float velocityY;
    bool isJumping;
    ScoreManager scoreManager; // Dodajemy brakuj¹c¹ sk³adow¹
    SoundManager* soundManager; // Dodajemy SoundManager jako sk³adow¹
};