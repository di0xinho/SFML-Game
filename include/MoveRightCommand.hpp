#pragma once
#include "Command.hpp"
#include <SFML/Graphics.hpp>

class MoveRightCommand : public Command {
public:
    MoveRightCommand(sf::RectangleShape& player) : player(player) {}
    void execute(sf::RenderWindow& window) override;

private:
    sf::RectangleShape& player;
};