#pragma once

#include "Command.hpp"
#include "Player.hpp"

// Komenda odpowiadająca za ruch gracza w prawo (wzorzec Command)
class MoveRightCommand : public Command {
public:
    // Wykonuje komendę ruchu w prawo na przekazanym obiekcie gracza
    void Execute(Player& player) override;
};