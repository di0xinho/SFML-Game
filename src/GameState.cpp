#include "GameState.hpp"
#include "PauseState.hpp"
#include "StateMachine.hpp"
#include "ScoreManager.hpp"
#include "SoundManager.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>

const float GRAVITY = 500.0f;

GameState::GameState(StateMachine& machine, SoundManager* soundManager)
    : stateMachine(machine), soundManager(soundManager), velocityY(0.0f), isJumping(false), scoreManager(){
    player.setSize(sf::Vector2f(50.0f, 50.0f));
    player.setFillColor(sf::Color::Green);
    player.setPosition(375.0f, 500.0f);

    // Inicjalizacja mapowania klawiszy do komend w InputHandler
    inputHandler.initializeBindings(player, velocityY, isJumping, stateMachine);

    // £adowanie czcionki
    sf::Font font;
    if (!font.loadFromFile("../../../../Assets/Fonts/roboto.ttf")) {
        // Obs³uga b³êdu
    }
    scoreManager.setFont(font);
    scoreManager.setPosition(10.0f, 10.0f);

    soundManager->playMusic("game");
}

//void GameState::handleInput(sf::RenderWindow& window) {
//
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
//        stateMachine.pushState(std::make_unique<PauseState>(stateMachine, soundManager));
//    }
//
//    inputHandler.handleInput(window);
//}

void GameState::handleInput(sf::RenderWindow& window) {

    inputHandler.handleInput(window);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
                stateMachine.pushState(std::make_unique<PauseState>(stateMachine, soundManager));
                soundManager->pauseMusic("game");

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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
        stateMachine.pushState(std::make_unique<PauseState>(stateMachine, soundManager));
        std::cout << "Prze³aczam na pauze";
    }
    // Aktualizacja punktacji
    // scoreManager.addPoints(10); // Przyk³adowe dodanie punktów
}

void GameState::render(sf::RenderWindow& window) {
    window.draw(player);
    scoreManager.render(window);
}