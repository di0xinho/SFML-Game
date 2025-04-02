#pragma once
#include <SFML/Graphics.hpp>
#include "StateMachine.hpp"
#include <unordered_map>
#include <memory>
#include "Command.hpp"

class InputHandler {
public:
    void handleInput(sf::RenderWindow& window);
    void bindCommand(sf::Keyboard::Key key, std::unique_ptr<Command> command);
    void initializeBindings(sf::RectangleShape& player, float& velocityY, bool& isJumping, StateMachine& stateMachine);

private:
    std::unordered_map<sf::Keyboard::Key, std::unique_ptr<Command>> commandMap;
    bool pKeyPressed = false;

    bool isPKeyPressedOnce();
};