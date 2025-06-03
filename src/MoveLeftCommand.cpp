#include "MoveLeftCommand.hpp"

// Wykonuje komendę ruchu w lewo na przekazanym obiekcie gracza
void MoveLeftCommand::Execute(Player& player) {
    player.MoveLeft();
}