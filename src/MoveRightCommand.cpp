#include "MoveRightCommand.hpp"

const float MOVE_SPEED = 200.0f;

void MoveRightCommand::execute(sf::RenderWindow& window) {
    player.move(MOVE_SPEED * 0.016f, 0.0f); // Przybli¿ony czas delta dla 60 FPS
}