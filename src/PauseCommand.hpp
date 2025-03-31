#pragma once
#include "Command.hpp"
#include <SFML/Graphics.hpp>
#include "StateMachine.hpp"
#include "PauseState.hpp"

class PauseCommand : public Command {
public:
    PauseCommand(StateMachine& machine) : stateMachine(machine) {}

    void execute(sf::RenderWindow& window) override {
        // Implementacja pauzy
        stateMachine.pushState(std::make_unique<PauseState>(stateMachine));
    }

private:
    StateMachine& stateMachine;
};