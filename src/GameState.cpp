#include "GameState.hpp"

const float GRAVITY = 500.0f; // Zwiêkszone wartoœci dla lepszej widocznoœci
const float JUMP_SPEED = -300.0f;
const float MOVE_SPEED = 200.0f;

GameState::GameState(StateMachine& machine)
    : stateMachine(machine), velocityY(0.0f), isJumping(false) {
    player.setSize(sf::Vector2f(50.0f, 50.0f));
    player.setFillColor(sf::Color::Green);
    player.setPosition(375.0f, 500.0f);
}

void GameState::handleInput(sf::RenderWindow& window) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        player.move(-MOVE_SPEED * 0.016f, 0.0f); // Przybli¿ony czas delta dla 60 FPS
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        player.move(MOVE_SPEED * 0.016f, 0.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !isJumping) {
        velocityY = JUMP_SPEED;
        isJumping = true;
    }
}

void GameState::update(float deltaTime) {
    // Grawitacja
    velocityY += GRAVITY * deltaTime;
    player.move(0.0f, velocityY * deltaTime);

    // Sprawdzenie kolizji z pod³o¿em
    if (player.getPosition().y + player.getSize().y >= 550.0f) {
        player.setPosition(player.getPosition().x, 550.0f - player.getSize().y);
        velocityY = 0.0f;
        isJumping = false;
    }
}

void GameState::render(sf::RenderWindow& window) {
    window.draw(player);
}