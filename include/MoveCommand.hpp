#pragma once
#include "Command.hpp"
#include <SFML/Graphics.hpp>

class MoveCommand : public Command {
public:
    MoveCommand(sf::RectangleShape& player, float offsetX)
        : player(player), offsetX(offsetX) {
    }

    virtual void execute(sf::RenderWindow& window) override {
        player.move(offsetX, 0.0f);
    }

protected:
    sf::RectangleShape& player;
    float offsetX;
};