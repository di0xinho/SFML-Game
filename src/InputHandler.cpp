#include "InputHandler.hpp"
#include "StateMachine.hpp"
#include "MoveLeftCommand.hpp"
#include "MoveRightCommand.hpp"
#include "JumpCommand.hpp"
#include "PauseCommand.hpp"

void InputHandler::handleInput(sf::RenderWindow& window) {
    for (const auto& [key, command] : commandMap) {
        if (key == sf::Keyboard::P) {
            if (isPKeyPressedOnce()) {
                command->execute(window);
            }
        }
        else {
            if (sf::Keyboard::isKeyPressed(key)) {
                command->execute(window);
            }
        }
    }
}

void InputHandler::bindCommand(sf::Keyboard::Key key, std::unique_ptr<Command> command) {
    commandMap[key] = std::move(command);
}

void InputHandler::initializeBindings(sf::RectangleShape& player, float& velocityY, bool& isJumping, StateMachine& stateMachine) {
    // U¿ycie obiektu klasy InputHandler do wywo³ania metody bindCommand
    bindCommand(sf::Keyboard::Left, std::make_unique<MoveLeftCommand>(player));
    bindCommand(sf::Keyboard::Right, std::make_unique<MoveRightCommand>(player));
    bindCommand(sf::Keyboard::Space, std::make_unique<JumpCommand>(player, velocityY, isJumping));
    bindCommand(sf::Keyboard::P, std::make_unique<PauseCommand>(stateMachine));
}

bool InputHandler::isPKeyPressedOnce() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
        if (!pKeyPressed) {
            pKeyPressed = true;
            return true;
        }
    }
    else {
        pKeyPressed = false;
    }
    return false;
}