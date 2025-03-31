#include "InputHandler.hpp"

void InputHandler::handleInput(sf::RenderWindow& window) {
    for (const auto& [key, command] : commandMap) {
        if (sf::Keyboard::isKeyPressed(key)) {
            command->execute(window);
        }
    }
}

void InputHandler::bindCommand(sf::Keyboard::Key key, std::unique_ptr<Command> command) {
    commandMap[key] = std::move(command);
}