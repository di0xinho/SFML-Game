#pragma once
#include <memory>
#include <stack>
#include "State.hpp"
#include "SoundManager.hpp"

class StateMachine {
public:
    StateMachine(SoundManager* soundManager);

    void pushState(std::unique_ptr<State> state);
    void popState();
    void changeState(std::unique_ptr<State> state);
    State* getCurrentState();

    void handleInput(sf::RenderWindow& window);
    void update(float deltaTime);
    void render(sf::RenderWindow& window);

private:
    std::stack<std::unique_ptr<State>> states;
    SoundManager* soundManager; // Dodajemy zmienn¹ soundManager
};