#pragma once

#include "Command.hpp"
#include "Player.hpp"

// Komenda odpowiadająca za ruch gracza w lewo (wzorzec Command)
class MoveLeftCommand : public Command {
public:
    // Wykonuje komendę ruchu w lewo na przekazanym obiekcie gracza
    void Execute(Player& player) override;
};