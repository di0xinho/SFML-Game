#pragma once
#include <memory>
#include <stack>
#include <SFML/Graphics.hpp>
#include "State.hpp"

class StateMachine {
public:
    void pushState(std::unique_ptr<State> state);
    void popState();
    void changeState(std::unique_ptr<State> state);

    void handleInput(sf::RenderWindow& window);
    void update(float deltaTime);
    void render(sf::RenderWindow& window);

private:
    std::stack<std::unique_ptr<State>> states;
};