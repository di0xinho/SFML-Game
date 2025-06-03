#pragma once
#include "Command.hpp"
#include "Player.hpp"

// Klasa polecenia skoku dla gracza (wzorzec Command)
class JumpCommand : public Command {
public:
    // Wykonuje komendê skoku na przekazanym obiekcie gracza
    void Execute(Player& player) override;
};