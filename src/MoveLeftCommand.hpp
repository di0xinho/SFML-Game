#pragma once
#include "Command.hpp"
#include <SFML/Graphics.hpp>

class MoveLeftCommand : public Command {
public:
    MoveLeftCommand(sf::RectangleShape& player) : player(player) {}
    void execute(sf::RenderWindow& window) override;

private:
    sf::RectangleShape& player;
};