#pragma once
#include <memory>
#include <stack>
#include "State.hpp"

class StateMachine {
public:
    void pushState(std::unique_ptr<State> state);
    void popState();
    void changeState(std::unique_ptr<State> state); // Dodajemy deklaracj� metody
    State* getCurrentState(); // Dodajemy deklaracj� metody

    void handleInput(sf::RenderWindow& window);
    void update(float deltaTime);
    void render(sf::RenderWindow& window);

private:
    std::stack<std::unique_ptr<State>> states;
};