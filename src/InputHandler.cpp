#include "InputHandler.hpp"

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