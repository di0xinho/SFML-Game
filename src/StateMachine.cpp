#include "StateMachine.hpp"

void StateMachine::pushState(std::unique_ptr<State> state) {
    states.push(std::move(state));
}

void StateMachine::popState() {
    if (!states.empty()) {
        states.pop();
    }
}

void StateMachine::changeState(std::unique_ptr<State> state) {
    if (!states.empty()) {
        states.pop();
    }
    states.push(std::move(state));
}

void StateMachine::handleInput(sf::RenderWindow& window) {
    if (!states.empty()) {
        states.top()->handleInput(window);
    }
}

void StateMachine::update(float deltaTime) {
    if (!states.empty()) {
        states.top()->update(deltaTime);
    }
}

void StateMachine::render(sf::RenderWindow& window) {
    if (!states.empty()) {
        states.top()->render(window);
    }
}