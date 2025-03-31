#pragma once
#include "Command.hpp"
#include <SFML/Graphics.hpp>
#include "StateMachine.hpp"
#include "PauseState.hpp"

class PauseCommand : public Command {
public:
    PauseCommand(StateMachine& machine) : stateMachine(machine) {}

    void execute(sf::RenderWindow& window) override {
        // Sprawdzamy, czy obecny stan to PauseState
        if (dynamic_cast<PauseState*>(stateMachine.getCurrentState())) {
            stateMachine.popState(); // Odpauzowanie
        }
        else {
            stateMachine.pushState(std::make_unique<PauseState>(stateMachine)); // Pauzowanie
        }
    }

private:
    StateMachine& stateMachine;
};