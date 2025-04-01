#include "PauseCommand.hpp"
#include "PauseState.hpp"

PauseCommand::PauseCommand(StateMachine& stateMachine)
    : stateMachine(stateMachine) {
}

void PauseCommand::execute(sf::RenderWindow& window) {
    if (auto* currentState = stateMachine.getCurrentState()) {
        if (dynamic_cast<PauseState*>(currentState)) {
            stateMachine.popState();
        }
        else {
            stateMachine.pushState(std::make_unique<PauseState>(stateMachine));
        }
    }
}