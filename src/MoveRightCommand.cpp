#include "MoveRightCommand.hpp"

// Wykonuje komendę ruchu w prawo na przekazanym obiekcie gracza
void MoveRightCommand::Execute(Player& player)
{ 
	player.MoveRight();
}