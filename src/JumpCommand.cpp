#include "JumpCommand.hpp"

// Wykonuje komendę skoku na przekazanym obiekcie gracza
void JumpCommand::Execute(Player& player) {
    player.Jump();
}