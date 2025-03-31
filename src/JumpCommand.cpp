#include "JumpCommand.hpp"

const float JUMP_SPEED = -300.0f;

void JumpCommand::execute(sf::RenderWindow& window) {
    if (!isJumping) {
        velocityY = JUMP_SPEED;
        isJumping = true;
    }
}