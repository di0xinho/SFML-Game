#pragma once
#include "Command.hpp"
#include <SFML/Graphics.hpp>

class JumpCommand : public Command {
public:
    JumpCommand(sf::RectangleShape& player, float& velocityY, bool& isJumping)
        : player(player), velocityY(velocityY), isJumping(isJumping) {
    }
    void execute(sf::RenderWindow& window) override;

private:
    sf::RectangleShape& player;
    float& velocityY;
    bool& isJumping;
};