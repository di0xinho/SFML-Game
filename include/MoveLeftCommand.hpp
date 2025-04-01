#pragma once
#include "MoveCommand.hpp"

class MoveLeftCommand : public MoveCommand {
public:
    MoveLeftCommand(sf::RectangleShape& player)
        : MoveCommand(player, -5.0f) {
    }
};