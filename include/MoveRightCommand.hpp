#pragma once
#include "MoveCommand.hpp"

class MoveRightCommand : public MoveCommand {
public:
    MoveRightCommand(sf::RectangleShape& player)
        : MoveCommand(player, 5.0f) {
    }
};