#pragma once
#include <memory>
#include "SoundManager.hpp"
#include <stack>
#include "State.hpp"

class StateMachine {
public:
    void pushState(std::unique_ptr<State> state);
    void popState();
    void changeState(std::unique_ptr<State> state);
    State* getCurrentState();

    void handleInput(sf::RenderWindow& window);
    void update(float deltaTime);
    void render(sf::RenderWindow& window);

    SoundManager* getSoundManager(); // Dodajemy metodê do uzyskania SoundManagera

private:
    std::stack<std::unique_ptr<State>> states;
    SoundManager* soundManager; // Dodajemy wskaŸnik do SoundManagera
};