#include "GameState.hpp"
#include "PauseState.hpp"
#include "StateMachine.hpp"
#include "MoveLeftCommand.hpp"
#include "MoveRightCommand.hpp"
#include "JumpCommand.hpp"
#include "PauseCommand.hpp"

const float GRAVITY = 500.0f;

GameState::GameState(StateMachine& machine)
    : stateMachine(machine), velocityY(0.0f), isJumping(false) {
    player.setSize(sf::Vector2f(50.0f, 50.0f));
    player.setFillColor(sf::Color::Green);
    player.setPosition(375.0f, 500.0f);

    // Mapowanie klawiszy do komend
    inputHandler.bindCommand(sf::Keyboard::Left, std::make_unique<MoveLeftCommand>(player));
    inputHandler.bindCommand(sf::Keyboard::Right, std::make_unique<MoveRightCommand>(player));
    inputHandler.bindCommand(sf::Keyboard::Space, std::make_unique<JumpCommand>(player, velocityY, isJumping));
    inputHandler.bindCommand(sf::Keyboard::P, std::make_unique<PauseCommand>(stateMachine));
}

void GameState::handleInput(sf::RenderWindow& window) {
    inputHandler.handleInput(window);
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